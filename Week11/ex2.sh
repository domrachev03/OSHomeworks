sudo chmod 777 lofsdisk

gcc ex2.c -o ex2.out
cp ex2.out lofsdisk

cd lofsdisk

echo "Ivan" > file1
echo "Domrachev" > /file2

mkdir bin
mkdir lib64
mkdir usr
mkdir usr/lib
mkdir usr/lib64

cd ..

cp /bin/bash lofsdisk/bin
ldd /bin/bash | awk '{print $3}' | xargs -I {} cp -v {} lofsdisk{}
cp lofsdisk/usr/lib/* lofsdisk/lib
cp lofsdisk/usr/lib64/* lofsdisk/lib64


udo chroot lofsdisk /ex2.out > ex2.txt
./ex2.out >> ex2.txt
