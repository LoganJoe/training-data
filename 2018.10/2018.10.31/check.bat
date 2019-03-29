@echo off
:loop
data.exe
force2.exe
path.exe
fc path.out path.ans
if not errorlevel 1 goto loop
pause
goto loop