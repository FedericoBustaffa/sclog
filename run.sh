#!/bin/bash


if [ $# -eq 0 ]; then
	bt=Debug
else
	bt=$1
fi

echo "Build project ..."
cd ./build/
cmake .. -DCMAKE_BUILD_TYPE=$bt

if make; then
	cd ..
	if [ $bt == "Debug" ]; then
		valgrind ./build/test/test --leak-check=full --track-origins=yes
	else
		./build/test/test
	fi
else
	echo "compilation failed"
	exit 1
fi
