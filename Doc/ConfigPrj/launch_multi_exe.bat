@echo off
setlocal EnableDelayedExpansion

set "SCRIPT_DIR=%~dp0"
set "CONFIG_JSON=%SCRIPT_DIR%ecus_config.json"
set "LAUNCH_PS1=%SCRIPT_DIR%launch_multi_exe_from_json.ps1"
set "FW_EXE=.pio\build\pc_sim_debug\program.exe"
set "SAFE_EXE=D:\Project\Software\STM32\Gamma\Gamma_Safety_AddCfg\.pio\build\pc_sim_debug\program.exe"
set "COMMON_ARGS=--sleep-ms 1"
set "PYTHON_EXE=python"
set "USE_WT_LAYOUT=1"
set "DRY_RUN=0"

if not exist "%CONFIG_JSON%" (
  echo [ERROR] Config not found: %CONFIG_JSON%
  exit /b 2
)
if not exist "%LAUNCH_PS1%" (
  echo [ERROR] Launcher script not found: %LAUNCH_PS1%
  exit /b 2
)

set "WT_OPT="
set "DRY_OPT="
if "%USE_WT_LAYOUT%"=="1" set "WT_OPT=-UseWindowsTerminal"
if "%DRY_RUN%"=="1" set "DRY_OPT=-DryRun"

powershell -NoProfile -ExecutionPolicy Bypass -File "%LAUNCH_PS1%" ^
  -ConfigJson "%CONFIG_JSON%" ^
  -FwExe "%FW_EXE%" ^
  -SafeExe "%SAFE_EXE%" ^
  -CommonArgs "%COMMON_ARGS%" ^
  -PythonExe "%PYTHON_EXE%" ^
  %WT_OPT% %DRY_OPT%

set "RC=%ERRORLEVEL%"
if not "%RC%"=="0" echo launch_multi_exe failed with code %RC%
pause 
