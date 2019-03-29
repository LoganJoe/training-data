g++ -g data.cpp -o data
g++ -g force.cpp -o force
g++ -g max.cpp -o max

while true; do
    ./data
    ./force
    ./max

    diff bf.out max.out || break
       echo -n "."
done
