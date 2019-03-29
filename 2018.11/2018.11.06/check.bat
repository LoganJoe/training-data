:loop
data.exe
xjbt1.exe
merchant.exe
fc merchant.out merchant.ans
if not errorlevel 1 goto loop
pause
goto loop