counter=0
while [ $counter -lt 20 ]
do
    if test ! -f file_no_racing.txt.lock; then
        ln file_no_racing.txt file_no_racing.txt.lock
        num=`tail -1 file_no_racing.txt`
        let num+=1
        echo $num >> file_no_racing.txt
        let counter+=1
        rm file_no_racing.txt.lock
    fi
done
