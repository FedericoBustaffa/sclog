#!/bin/bash


if [ $# -eq 0 ]; then
    bt=Debug
else
    bt=$1
fi

./run.sh $bt

if [ "$bt" == "Debug" ]; then
    valgrind --tool=helgrind ./build/test/test
else
    ./build/test/test
fi
