@echo off
if "%1"=="" goto SYNTAX

echo on
copy cat\cat.exe %1
copy chmod\chmod.exe %1
copy chown\chown.exe %1
copy cp\cp.exe %1
copy elvis\vi.exe %1
copy find\find.exe %1
copy grep\grep.exe %1
copy ln\ln.exe %1
copy ls\ls.exe %1
copy mkdir\mkdir.exe %1
copy mv\mv.exe %1
copy rm\rm.exe %1
copy rmdir\rmdir.exe %1
copy sh\sh\sh.exe %1
copy touch\touch.exe %1
copy wc\wc.exe %1
goto END

:SYNTAX
echo PPOSIX [target directory]
echo The files will be copied to the target directory.
goto END

:END
