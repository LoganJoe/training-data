@echo off
:loop
data1.exe
a.exe
force1.exe
fc a.out a.ans
if not errorlevel 1 goto loop
pause
goto loop
