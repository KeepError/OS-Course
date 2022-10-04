gcc -o publisher publisher.c
gcc -o subscriber subscriber.c
for ((i=1; i<=$1; i++))
do
    gnome-terminal -- ./subscriber $
done
./publisher