#!/bin/bash


if [ $# -eq 0 ]; then
    bt=Debug
else
    bt=$1
fi

./compile.sh $bt

# ./build/test/test # run with -fsanitize=thread

if [ "$bt" == "Debug" ]; then
    valgrind --tool=helgrind -s ./build/test/test
else
    ./build/test/test
fi
