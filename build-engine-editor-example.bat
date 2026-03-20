REM @echo off
cd build
mingw32-make

copy /Y libhge.dll ..\editor\copy-build\libhge.dll
copy /Y libhge.dll.a ..\editor\lib\libhge.dll.a

cd ..
robocopy "src" "editor\third_party\hge" *.h /S
robocopy "src" "example\third_party\hge" *.h /S

cd editor
call nested-build.bat

cd ..
cd example
call build-example.bat

pause