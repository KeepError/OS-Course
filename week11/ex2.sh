sudo chmod 777 lofsdisk

cd lofsdisk
echo "Egor" > file1
echo "Kuziakov" > file2

mkdir bin
for binname in "bash" "cat" "echo" "ls"
do
  # Copy file from bin
  cp /bin/$binname ./bin

  # Copy its libraries
  libs=$(ldd /bin/$binname | grep -o "/usr/lib\S*")
  for libfile in $libs
  do
    libdirectory=$(echo $libfile | grep -o ".*/")
    mkdir -p ".$libdirectory"
    cp "$libfile" ".$libdirectory"
  done
done

gcc ../ex2.c -static -o ex2
sudo chroot . ./ex2 > ../ex2.txt
