END=$1
for i in $(seq 1 $END); 
do
    echo "--------$i" 
    rm -rf tmpf
    python genRandDnas.py > tmpf 
    fromCpp=$(cat tmpf | ./nFS)
    fromPy=$(cat tmpf | python testbwa.py)
    if [ "$fromCpp" = "$fromPy" ];then
        echo "Yes"
    fi
done
