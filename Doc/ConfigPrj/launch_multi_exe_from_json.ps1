param(
    [Parameter(Mandatory = $true)][string]$ConfigJson,
    [Parameter(Mandatory = $true)][string]$FwExe,
    [Parameter(Mandatory = $true)][string]$SafeExe,
    [string]$CommonArgs = "",
    [string]$PythonExe = "python",
    [switch]$UseWindowsTerminal,
    [switch]$DryRun
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"
Add-Type -AssemblyName System.Globalization

function Resolve-AbsolutePath {
    param(
        [Parameter(Mandatory = $true)][string]$InputPath,
        [Parameter(Mandatory = $true)][string]$Label,
        [switch]$MustExist,
        [ValidateSet("Leaf", "Container")] [string]$PathType = "Leaf"
    )

    if ([string]::IsNullOrWhiteSpace($InputPath)) {
        throw "$Label is empty"
    }

    $repoRoot = [System.IO.Path]::GetFullPath((Join-Path $PSScriptRoot "..\.."))
    $candidates = [System.Collections.Generic.List[string]]::new()

    if ([System.IO.Path]::IsPathRooted($InputPath)) {
        $candidates.Add([System.IO.Path]::GetFullPath($InputPath))
    } else {
        $candidates.Add([System.IO.Path]::GetFullPath((Join-Path (Get-Location).Path $InputPath)))
        $candidates.Add([System.IO.Path]::GetFullPath((Join-Path $repoRoot $InputPath)))
        $candidates.Add([System.IO.Path]::GetFullPath((Join-Path $PSScriptRoot $InputPath)))
    }

    $resolved = [System.Collections.Generic.List[string]]::new()
    foreach ($candidate in $candidates) {
        if (-not $resolved.Contains($candidate)) {
            $resolved.Add($candidate)
        }
    }

    foreach ($candidate in $resolved) {
        if (Test-Path -LiteralPath $candidate -PathType $PathType) {
            return $candidate
        }
    }

    if ($MustExist) {
        $tested = ($resolved -join ", ")
        throw "$Label not found: $InputPath (tested: $tested)"
    }

    return $resolved[0]
}

$ConfigJson = Resolve-AbsolutePath -InputPath $ConfigJson -Label "Config" -MustExist -PathType Leaf
$FwExe = Resolve-AbsolutePath -InputPath $FwExe -Label "Firmware executable" -PathType Leaf
$SafeExe = Resolve-AbsolutePath -InputPath $SafeExe -Label "Safety executable" -PathType Leaf
$RepoRoot = [System.IO.Path]::GetFullPath((Join-Path $PSScriptRoot "..\.."))

$cfg = Get-Content -Raw -LiteralPath $ConfigJson | ConvertFrom-Json
if (-not $cfg.ecus) {
    throw "No ecus[] in ecus_config.json"
}

function Convert-ToBool {
    param(
        [Parameter(Mandatory = $false)]$Value,
        [bool]$Default = $false
    )
    if ($null -eq $Value) {
        return $Default
    }
    if ($Value -is [bool]) {
        return [bool]$Value
    }
    $norm = ([string]$Value).Trim().ToLowerInvariant()
    if ($norm -in @("1", "true", "yes", "on")) { return $true }
    if ($norm -in @("0", "false", "no", "off")) { return $false }
    return $Default
}

function Get-BoolProp {
    param(
        [Parameter(Mandatory = $true)]$Obj,
        [Parameter(Mandatory = $true)][string]$Name,
        [bool]$Default = $false
    )
    $prop = $Obj.PSObject.Properties[$Name]
    if ($null -eq $prop) {
        return $Default
    }
    return (Convert-ToBool -Value $prop.Value -Default $Default)
}

function Test-BrokerAlive {
    param(
        [int]$Port,
        [int]$TimeoutMs = 200
    )
    try {
        $client = New-Object System.Net.Sockets.UdpClient
        $client.Client.ReceiveTimeout = $TimeoutMs
        $client.Connect("127.0.0.1", $Port)
        $payload = [System.Text.Encoding]::ASCII.GetBytes("PING")
        [void]$client.Send($payload, $payload.Length)
        $remote = New-Object System.Net.IPEndPoint([System.Net.IPAddress]::Any, 0)
        $resp = $client.Receive([ref]$remote)
        $txt = [System.Text.Encoding]::ASCII.GetString($resp).Trim()
        $client.Close()
        return ($txt -eq "PONG")
    } catch {
        return $false
    }
}

function Test-BrokerProcessRunning {
    param(
        [Parameter(Mandatory = $true)][string]$BrokerScriptPath
    )

    try {
        $scriptNorm = [System.IO.Path]::GetFullPath($BrokerScriptPath).ToLowerInvariant()
        $procs = Get-CimInstance Win32_Process -ErrorAction Stop
        foreach ($proc in $procs) {
            $name = ([string]$proc.Name).ToLowerInvariant()
            if ($name -notin @("python.exe", "pythonw.exe", "py.exe")) {
                continue
            }

            $cmd = [string]$proc.CommandLine
            if ([string]::IsNullOrWhiteSpace($cmd)) {
                continue
            }
            $cmdNorm = $cmd.ToLowerInvariant()
            if (($cmdNorm.Contains("can_broker.py")) -and ($cmdNorm.Contains($scriptNorm) -or $cmdNorm.Contains("tools\\multiecumonitor\\can_broker.py"))) {
                return $true
            }
        }
    } catch {
        return $false
    }

    return $false
}

function Start-BrokerIfNeeded {
    param(
        $CfgObj,
        [string]$ConfigPath,
        [string]$RepoRootPath,
        [string]$PyExe,
        [switch]$Dry
    )

    $generalProp = $CfgObj.PSObject.Properties["general"]
    if ($null -eq $generalProp -or $null -eq $generalProp.Value) {
        return
    }
    $general = $generalProp.Value
    $brokerProp = $general.PSObject.Properties["can_broker"]
    if ($null -eq $brokerProp -or $null -eq $brokerProp.Value) {
        return
    }
    $broker = $brokerProp.Value
    $enabled = $false
    $enabledProp = $broker.PSObject.Properties["enabled"]
    if ($null -ne $enabledProp -and $null -ne $enabledProp.Value) {
        $enabled = [bool]$enabledProp.Value
    }
    if (-not $enabled) {
        return
    }

    $pcsimEnabledCount = 0
    foreach ($ecu in $CfgObj.ecus) {
        $ecuEnabled = Get-BoolProp -Obj $ecu -Name "enable_ecu" -Default $true
        $ecuInDebug = Get-BoolProp -Obj $ecu -Name "ecu_in_debug" -Default $false
        if ($ecuEnabled -and $ecuInDebug) {
            throw "Invalid config for ECU '$($ecu.name)': enable_ecu=true and ecu_in_debug=true"
        }
        $activeForBus = ($ecuEnabled -or $ecuInDebug)
        $gate = ""
        $gateProp = $ecu.PSObject.Properties["can_gate"]
        if ($null -ne $gateProp -and $null -ne $gateProp.Value) {
            $gate = ([string]$gateProp.Value).Trim().ToUpperInvariant()
        }
        if ($activeForBus -and $gate -eq "PCSIM") {
            $pcsimEnabledCount++
        }
    }
    if ($pcsimEnabledCount -lt 2) {
        Write-Host "[BROKER] skipped (need at least 2 enabled PCSIM ECUs)"
        return
    }

    $port = 19600
    $portProp = $broker.PSObject.Properties["control_port"]
    if ($null -ne $portProp -and $null -ne $portProp.Value) {
        $port = [int]$portProp.Value
    }

    $brokerScript = Join-Path $RepoRootPath "tools\MultiEcuMonitor\can_broker.py"
    if (-not (Test-Path -LiteralPath $brokerScript -PathType Leaf)) {
        Write-Warning "Broker script not found: $brokerScript"
        return
    }

    if (Test-BrokerProcessRunning -BrokerScriptPath $brokerScript) {
        Write-Host "[BROKER] already running (process detected)"
        return
    }
    if (Test-BrokerAlive -Port $port) {
        Write-Host "[BROKER] already running on 127.0.0.1:$port"
        return
    }

    Write-Host "[BROKER] start requested on 127.0.0.1:$port"
    if ($Dry) {
        return
    }

    Start-Process -FilePath $PyExe `
                  -WorkingDirectory $RepoRootPath `
                  -ArgumentList @($brokerScript, "--config", $ConfigPath) `
                  -WindowStyle Minimized | Out-Null

    $brokerStarted = $false
    for ($attempt = 0; $attempt -lt 20; $attempt++) {
        Start-Sleep -Milliseconds 200
        if (Test-BrokerAlive -Port $port) {
            $brokerStarted = $true
            break
        }
    }
    if ($brokerStarted) {
        Write-Host "[BROKER] started"
    } else {
        if (Test-BrokerProcessRunning -BrokerScriptPath $brokerScript) {
            Write-Host "[BROKER] process detected after start (no second launch)"
            return
        }
        Write-Warning "Broker did not respond on port $port after start"
    }
}

Start-BrokerIfNeeded -CfgObj $cfg -ConfigPath $ConfigJson -RepoRootPath $RepoRoot -PyExe $PythonExe -Dry:$DryRun

$launches = @()
foreach ($ecu in $cfg.ecus) {
    $enabled = Get-BoolProp -Obj $ecu -Name "enable_ecu" -Default $true
    $inDebug = Get-BoolProp -Obj $ecu -Name "ecu_in_debug" -Default $false
    if ($enabled -and $inDebug) {
        throw "Invalid config for ECU '$($ecu.name)': enable_ecu=true and ecu_in_debug=true"
    }
    if ($inDebug) {
        Write-Host ("[DEBUG ECU] {0} => exe launch skipped (ecu_in_debug=true)" -f [string]$ecu.name)
        continue
    }
    if (-not $enabled) {
        continue
    }

    $nameProp = $ecu.PSObject.Properties["name"]
    if ($null -eq $nameProp -or [string]::IsNullOrWhiteSpace([string]$nameProp.Value)) {
        throw "Missing name for one ECU entry"
    }
    $name = [string]$nameProp.Value

    $port = $null
    $udpPortProp = $ecu.PSObject.Properties["udp_port"]
    $udpProp = $ecu.PSObject.Properties["udp"]
    if ($null -ne $udpPortProp -and $null -ne $udpPortProp.Value) {
        $port = [int]$udpPortProp.Value
    } elseif ($null -ne $udpProp -and $null -ne $udpProp.Value) {
        $udpObj = $udpProp.Value
        $udpInnerPortProp = $udpObj.PSObject.Properties["port"]
        if ($null -ne $udpInnerPortProp -and $null -ne $udpInnerPortProp.Value) {
            $port = [int]$udpInnerPortProp.Value
        }
    }
    if ($null -eq $port) {
        throw "Missing udp_port (or udp.port) for ECU $name"
    }
    $ecuAnaProp = $ecu.PSObject.Properties["ecu_ana"]
    if ($null -eq $ecuAnaProp -or $null -eq $ecuAnaProp.Value) {
        throw "Missing ecu_ana for ECU $name"
    }
    $ecuAnaObj = $ecuAnaProp.Value
    $anaIdxProp = $ecuAnaObj.PSObject.Properties["idx"]
    if ($null -eq $anaIdxProp -or $null -eq $anaIdxProp.Value) {
        throw "Missing ecu_ana.idx for ECU $name"
    }
    $anaValProp = $ecuAnaObj.PSObject.Properties["value_mv"]
    if ($null -eq $anaValProp -or $null -eq $anaValProp.Value) {
        throw "Missing ecu_ana.value_mv for ECU $name"
    }

    $anaIdx = [int]$anaIdxProp.Value
    $anaVal = [int]$anaValProp.Value
    $isSafe = $name -match "SAFE"
    $exe = if ($isSafe) { $SafeExe } else { $FwExe }
    if (-not (Test-Path -LiteralPath $exe -PathType Leaf)) {
        throw "Executable not found: $exe"
    }

    $argParts = @(
        "--udp-port", "$port",
        "--ana", "$anaIdx", "$anaVal"
    )

    $encModesProp = $ecu.PSObject.Properties["encoder_modes"]
    if ($null -ne $encModesProp -and $null -ne $encModesProp.Value) {
        foreach ($encMode in $encModesProp.Value) {
            if ($null -eq $encMode) {
                continue
            }

            $modeProp = $encMode.PSObject.Properties["mode"]
            $modeStr = ""
            if ($null -ne $modeProp -and $null -ne $modeProp.Value) {
                $modeStr = ([string]$modeProp.Value).Trim().ToLowerInvariant()
            }
            if ($modeStr -ne "encdr_based_pulse") {
                continue
            }

            $idxProp = $encMode.PSObject.Properties["idx"]
            $pwmProp = $encMode.PSObject.Properties["sig_pwm"]
            $pprProp = $encMode.PSObject.Properties["pulses_per_revolution"]

            if (($null -eq $idxProp) -or ($null -eq $idxProp.Value) -or
                ($null -eq $pwmProp) -or ($null -eq $pwmProp.Value) -or
                ($null -eq $pprProp) -or ($null -eq $pprProp.Value)) {
                Write-Warning "ECU ${name}: encoder_modes entry 'encdr_based_pulse' ignored (missing idx/sig_pwm/pulses_per_revolution)"
                continue
            }

            $encIdx = [int]$idxProp.Value
            $pwmIdx = [int]$pwmProp.Value
            $pprVal = [double]$pprProp.Value
            $pprStr = $pprVal.ToString([System.Globalization.CultureInfo]::InvariantCulture)

            $argParts += @("--enc-map", "$encIdx", "$pwmIdx", "$pprStr")
        }
    }

    if (-not [string]::IsNullOrWhiteSpace($CommonArgs)) {
        $argParts += @($CommonArgs.Trim())
    }

    $title = "PCSIM $name - UDP $port"
    $argLine = ($argParts -join " ").Trim()
    $cmdLine = ('title {0} && ""{1}"" {2}' -f $title, $exe, $argLine)
    $workDir = Split-Path -Parent $exe

    $launches += [pscustomobject]@{
        Name    = $name
        Title   = $title
        Exe     = $exe
        Args    = $argLine
        CmdLine = $cmdLine
        WorkDir = $workDir
    }
}

foreach ($l in $launches) {
    Write-Host ("[LAUNCH] {0} => {1} {2}" -f $l.Title, $l.Exe, $l.Args)
}

if ($launches.Count -eq 0) {
    Write-Host "[INFO] No ECU executable to launch (enable_ecu=false or ecu_in_debug=true for all)."
    return
}

if ($DryRun) {
    return
}

$wtCmd = Get-Command wt.exe -ErrorAction SilentlyContinue
if ($UseWindowsTerminal -and ($null -ne $wtCmd)) {
    $chunkSize = 4
    $firstChunk = $true

    for ($idx = 0; $idx -lt $launches.Count; $idx += $chunkSize) {
        $end = [Math]::Min($idx + $chunkSize - 1, $launches.Count - 1)
        $chunk = $launches[$idx..$end]

        $wtArgs = @("new-tab", "cmd", "/k", $chunk[0].CmdLine)

        if ($chunk.Count -ge 2) {
            $wtArgs += @(";", "split-pane", "-H", "cmd", "/k", $chunk[1].CmdLine)
        }
        if ($chunk.Count -ge 3) {
            # 3 panes: left side split in 2, right side single -> "2 et 1"
            $wtArgs += @(";", "focus-pane", "-t", "0")
            $wtArgs += @(";", "split-pane", "-V", "cmd", "/k", $chunk[2].CmdLine)
        }
        if ($chunk.Count -ge 4) {
            # 4 panes: split right side too -> 2x2
            $wtArgs += @(";", "focus-pane", "-t", "1")
            $wtArgs += @(";", "split-pane", "-V", "cmd", "/k", $chunk[3].CmdLine)
        }

        if ($firstChunk) {
            Start-Process -FilePath "wt.exe" -ArgumentList $wtArgs | Out-Null
            $firstChunk = $false
        } else {
            Start-Process -FilePath "wt.exe" -ArgumentList (@("-w", "0") + $wtArgs) | Out-Null
        }
    }
} else {
    foreach ($l in $launches) {
        Start-Process -FilePath "cmd.exe" -WorkingDirectory $l.WorkDir -ArgumentList "/k", $l.CmdLine | Out-Null
    }
}
