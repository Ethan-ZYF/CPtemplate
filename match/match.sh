#compile a.cpp and b.cpp
g++-13 -std=c++20 -o me.out Zme.cpp
g++-13 -std=c++20 -o ac.out Zac.cpp


# loop 100 times, and compare a.out and b.out
for i in {1..100}
do
    #generate input.txt
    python3 make_input.py > input.txt
    ./me.out < input.txt > me.txt
    ./ac.out < input.txt > ac.txt
    if [ $? -ne 0 ]; then
        printf '|%3s|: ' "$i"
        echo "WA"
        exit 1
    else
        printf '|%3s|: ' "$i" 
        echo "AC"
    fi
done
rm me.out ac.out