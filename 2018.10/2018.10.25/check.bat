@echo off
:loop
data3.exe 
force3.exe 
t3.exe 
fc snowman.out snowman.ans
if not errorlevel 1 goto loop
pause
goto loop