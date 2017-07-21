for i in `seq 0 $1`
do
	nc -l -w1 -u 1234
	echo "\n"
done

