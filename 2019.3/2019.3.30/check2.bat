g++ -o baoli1 baoli1.cpp
g++ -o data1 data1.cpp
g++ -o lcs lcs.cpp
:loop
data1.exe
baoli1.exe
lcs.exe
fc lcs.out lcs.ans
if not errorlevel 1 goto loop
pause
goto loop