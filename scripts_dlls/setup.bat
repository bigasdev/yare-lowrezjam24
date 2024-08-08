@echo off

echo Workspace Directory: %cd%

mkdir bin
mkdir .build
mkdir .release
mkdir .web

xcopy "scripts_dlls\dev_dlls\SDL2.dll" ".build"
xcopy "scripts_dlls\dev_dlls\SDL2_image.dll" ".build" /i
xcopy "scripts_dlls\dev_dlls\SDL2_ttf.dll" ".build" /i
xcopy "libwinpthread-1.dll" ".build" /i
xcopy "res" ".build/res/" /i /e /y

xcopy "scripts_dlls\SDL2.dll" ".release" /i
xcopy "scripts_dlls\SDL2_image.dll" ".release" /i
xcopy "scripts_dlls\SDL2_ttf.dll" ".release" /i
xcopy "libwinpthread-1.dll" ".release" /i
xcopy "res" ".release/res/" /i /e /y
