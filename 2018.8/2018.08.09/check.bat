@echo off
:loop
data.exe 
force.exe 
GCD.exe 
fc test.out test.ans 
if not errorlevel 1 goto loop
pause
goto loop