@echo off
:loop
data.exe 
force.exe 
spaceship.exe 
fc spaceship.out spaceship.ans 
if not errorlevel 1 goto loop
pause
goto loop
