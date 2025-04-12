#!/bin/bash


if [ $# -eq 0 ]; then
    bt=Debug
else
    bt=$1
fi

if [[ ! -d "./build/" ]]; then
    mkdir "build"
fi

cd ./build/
cmake .. -DCMAKE_BUILD_TYPE=$bt
make
cd ..

if [ "$bt" == "Debug" ]; then
    valgrind --tool=helgrind ./build/test/test
else
    ./build/test/test
fi
