gcc -o ex3 ex3.c -pthread
#./ex3 $1 $2
for m in 1 2 4 10 100
do
    echo "m=$m"
    time ./ex3 10000000 $m
    echo ""
done
