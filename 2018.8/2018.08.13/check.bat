@echo off
:loop
data.exe 
force.exe 
message.exe 
fc message.out message.ans 
if not errorlevel 1 goto loop
pause
goto loop