cd ..
mkdir -p Week01
touch Week01/file.txt
echo "Ivan" >> Week01/file.txt
link Week01/file.txt Week10/_ex2.txt
find . -inum $( ls -li Week01/file.txt | awk '{print $1}' ) >> Week10/ex2.txt
find . -inum $( ls -li Week01/file.txt | awk '{print $1}' ) -exec rm {} \; >> Week10/ex2.txt

cat Week10/ex2.txt



