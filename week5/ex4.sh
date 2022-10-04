gcc -o ex4 ex4.c -pthread
#./ex4 $1 $2
for m in 1 2 4 10 100
do
    echo "m=$m"
    time ./ex4 10000000 $m
    echo ""
done