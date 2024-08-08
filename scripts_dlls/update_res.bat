@echo off

xcopy "res" ".build/res/" /i /e /y
xcopy "res" ".release/res/" /i /e /y
xcopy "res" ".web/res/" /i /e /y
exit
