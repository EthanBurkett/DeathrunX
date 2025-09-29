@echo off
setlocal

REM Always run from this script's directory
cd /d "%~dp0"

REM Try common make executables (avoid matching this .bat)
set "MAKECMD="
for %%M in (make.exe mingw32-make.exe gmake.exe nmake.exe) do (
    where /Q %%M
    if not errorlevel 1 (
        set "MAKECMD=%%M"
        goto :found_make
    )
)

REM No make on PATH -> fallback to batch builders
echo [INFO] No 'make' found on PATH. Running makeIWD.bat and makeMod.bat...
if exist "makeIWD.bat" (
    call makeIWD.bat
) else (
    echo [WARN] makeIWD.bat not found.
)

if exist "makeMod.bat" (
    call makeMod.bat
) else (
    echo [WARN] makeMod.bat not found.
)
goto :eof

:found_make
echo [INFO] Found %%MAKECMD%% — running it...
"%MAKECMD%" %*
endlocal
