cd build
mingw32-make
copy \Y libhge.a ../editor/lib/libhge.a
cd ..
robocopy "src" "editor\third_party\hge" *.h /S
cd editor
call build-editor.bat
pause