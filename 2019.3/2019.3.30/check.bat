g++ -o baoli baoli.cpp
g++ -o data2 data2.cpp
g++ -o magic magic.cpp
:loop
data2.exe
baoli.exe
magic.exe
fc magic.out magic.ans
if not errorlevel 1 goto loop
pause
goto loop

pause