@echo off
::if exist %SIV3D_0_6_14% goto ExitProgram
if exist "%cd%/OpenSiv3D_SDK_0.6.14" goto ExitProgram

:SetupProject
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0InstallOpenSiv.ps1"
echo Project Setup completed...
pause

:ExitProgram
echo Project is already installed...
pause
