@echo off
echo clean...
del %~dp0*.exe /q /s
del %~dp0tempCodeRunnerFile.c /q /s
del %~dp0a.out /q /s
del %~dp0*.o /q /s
echo end...press
pause >nul
exit