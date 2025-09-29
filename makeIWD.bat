@echo off
setlocal

REM Path to script (same folder as this .bat)
set "SCRIPT=%~dp0makeIWDs.ps1"

REM First, make sure pwsh.exe exists on PATH
where pwsh.exe >nul 2>&1
if errorlevel 1 (
    echo [ERROR] PowerShell 7.x not found on PATH.
    echo If installed from Microsoft Store, ensure the "App Execution Aliases"
    echo option for PowerShell is enabled in Windows Settings.
    pause
    exit /b 1
)

echo Launching makeIWDs.ps1 with PowerShell 7...
pwsh.exe -NoLogo -NoProfile -ExecutionPolicy Bypass -File "%SCRIPT%"

endlocal
