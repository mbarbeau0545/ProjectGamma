@echo off
REM Spécifiez le chemin vers l'exécutable Python si nécessaire
set PYTHON_PATH=C:/Users/mbarb/AppData/Local/Programs/Python/Python311/python.exe

cd /d %~dp0\..\..

where python
python -m pip show openpyxl

REM Exécuter le script Python avec des arguments fixes
"%PYTHON_PATH%" Doc/ConfigPrj/PythonTool_CodeGen/main.py ^
Doc\ConfigPrj\ExcelCfg\STM32G474RE\STM32G474RE_HwCfg.xlsx ^
Doc\ConfigPrj\GammaCfg\Project_SoftwareCfg.xlsm

echo Press any key to continue...
pause