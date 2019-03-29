@echo off
:loop
data.exe
A.exe
force1.exe
fc a.ans a.out
if not errorlevel 1 goto loop
pause
goto loop