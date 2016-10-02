if [ "$#" -ne 1 ];
then
    echo "Usage: $0 <.fa>"
    mf1=/home/tongust/Program/cpp/sbwt/sbwa-buildIndex/genomes/rand.fa
else
    mf1=$1
fi
rm -rf release 
$1=$mf1
mkdir release
cd ./release
cmake ..
tput reset
make
rm -rf Makefile CMakeCache.txt CMakeFiles/ cmake_install.cmake
cd ../
cp ./release/ZEBRA ./
./ZEBRA $mf1


#rm -rf ../backup/sbwa-buildIndex
#cp -a ../sbwa-buildIndex ../backup/
