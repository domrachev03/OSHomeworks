counter=0
while [ $counter -lt 100 ]
do
    num=`tail -1 file.txt`
    let num+=1
    echo $num >> file.txt
    let counter+=1
done
