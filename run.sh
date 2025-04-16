#!/bin/bash


if [ $# -eq 0 ]; then
    bt=Debug
else
    bt=$1
fi

./compile.sh $bt

if [ "$bt" == "Debug" ]; then
    valgrind --tool=helgrind -s ./build/test/test $2
else
    ./build/test/test $2
fi
