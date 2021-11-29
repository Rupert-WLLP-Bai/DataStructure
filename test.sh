#########################################################################
# File Name: test.sh
# Author: ma6174
# mail: ma6174@163.com
# Created Time: Mon 29 Nov 2021 09:24:31 PM CST
#########################################################################
#!/bin/bash

# build
mkdir build
cd build
# release
mkdir Release
cd Release
cmake -DCMAKE_BUILD_TYPE=Release ../..
make

cd ..

# debug
mkdir Debug
cd Debug
cmake -DCMAKE_BUILD_TYPE=Debug ../..
make

cd ..
