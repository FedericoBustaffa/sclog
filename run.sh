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

if make; then
    cd ..
    ./build/test/test
else
    echo "compilation failed"
    exit 1
fi
