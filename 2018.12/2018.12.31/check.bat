@echo off
:loop
data1.exe
force1.exe
a.exe
fc a.ans a.out
if not errorlevel 1 goto loop
pause
goto loop