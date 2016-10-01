preINN=$(stat ./naiveFastSort.h | grep Change)
while true
do
    sleep 1s
    nowINN=$(stat ./naiveFastSort.h | grep Change)
    if [ "$nowINN" != "${preINN}" ];then
        tput reset
        echo "The filed has been changed"
        echo $nowINN
        rm -rf main
        g++ -std=c++11 -o main main.cpp
        ./main
    fi
    preINN=${nowINN}
done
