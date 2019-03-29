@echo off
:loop
data2.exe 
force2.exe 
yukari.exe 
fc yukari.out yukari.ans 
if not errorlevel 1 goto loop
pause
goto loop