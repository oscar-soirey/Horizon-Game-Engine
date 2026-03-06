@echo off
REM Aller dans le dossier build
cd build || exit /b

REM Compiler le projet
mingw32-make
IF ERRORLEVEL 1 (
    echo Compilation failed!
    pause
    exit /b
)

REM Copier les fichiers de copy-build vers build
robocopy "..\copy-build" "." /S /E /NFL /NDL /NJH /NJS /nc /ns /np

REM Lancer l'executable
start editor.exe