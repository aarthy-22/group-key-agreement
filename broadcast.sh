#broadcast the XOR sums
for i in $@
do
    echo "$i" | socat - udp-datagram:10.**.**.***:1234,broadcast 
done
