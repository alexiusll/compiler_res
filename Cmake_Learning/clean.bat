@echo off
echo 清理所有的构建 clean...
rmdir %~dp0**/build /q /s
echo end...press
pause >nul
exit