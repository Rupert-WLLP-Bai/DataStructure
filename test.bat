mkdir build

cd build

mkdir Release
cd Release
cmake -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles" ../..
mingw32-make

cd ..

mkdir Debug
cd Debug
cmake -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles" ../..
mingw32-make

cd ..
