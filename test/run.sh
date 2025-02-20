#!/bin/bash

cd build/
cmake .. -DCMAKE_BUILD_TYPE=$1
make
valgrind ./test/test --tool=hellgrind
cd ..
