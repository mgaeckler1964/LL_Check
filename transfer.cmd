@echo on

if "%1."=="." goto usage
if "%2."=="." goto usage
if "%3."=="." goto usage

set EXPCMD=exp
set IMPCMD=imp

rem delete status file
if exist sqlnet.log del sqlnet.log

rem delete old backups
if exist %1_old.dmp del %1_old.dmp
if exist %2_old.dmp del %2_old.dmp

rem create backups
if exist %1.dmp rename %1.dmp %1_old.dmp
if exist %2.dmp rename %2.dmp %2_old.dmp

rem export source
%EXPCMD% userid=%3/%3@%1 file=%1.dmp owner=%3 log=export.log
if errorlevel 1 goto error
if exist sqlnet.log goto error
if not exist %1.dmp goto error

rem make backup of destination
%EXPCMD% userid=%3/%3@%2 file=%2.dmp owner=%3 log=backup.log
if errorlevel 1 goto error
if exist sqlnet.log goto error
if not exist %2.dmp goto error

rem clear destination 
sqlplus %3/%3@%2 @drop.sql
if errorlevel 1 goto error
if exist sqlnet.log goto error

rem import source to destination 
%IMPCMD% userid=%3/%3@%2 file=%1.dmp full=Y log=import.log
if errorlevel 1 goto error
if exist sqlnet.log goto error

goto end
:usage
echo usage transfer sourceDB destinationDB userId/password
pause
goto end

:error
type sqlnet.log
pause

:end
