@echo off
cd build || exit /b

mingw32-make
IF ERRORLEVEL 1 (
    echo Compilation failed!
    pause
    exit /b
)

robocopy "..\copy-build" "." /S /E /NFL /NDL /NJH /NJS /nc /ns /np

editor.exe