mkdir ../week01
touch ../week01/file.txt
echo "Egor Kuziakov" >> ../week01/file.txt
link ../week01/file.txt _ex2.txt
ls -i ../week01/file.txt
find .. -inum 1056851  >> ex2.txt
find .. -inum 1056851 -exec rm {} \; >> ex2.txt
