#!/bin/bash

cd ./build/
cmake .. -DCMAKE_BUILD_TYPE=$1
make
cd ..
valgrind ./build/test/test --tool=hellgrind
