preINN=$(stat *.h *.cpp | grep Change)
while true
do
    sleep 1s
    nowINN=$(stat *.h *.cpp | grep Change)
    if [ "$nowINN" != "${preINN}" ];then
        rm -rf ./ZEBRA
        tput reset
        echo "The filed has been changed"
        sh build.sh
#        echo $nowINN
#        rm -rf main
#        g++ -std=c++11 -o main main.cpp
#        ./main
    fi
    preINN=${nowINN}
done
