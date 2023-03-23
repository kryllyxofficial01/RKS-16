#!/bin/bash

echo -n "Enter filepath: "
read filepath

assemble() {
    cd rks
    python main.py $filepath
    cd ..
}

emulate() {
    rom=${filepath%""."$(echo $filepath | awk -F "." '{print $NF}')"}
    cd "rks-16"
    g++ -std=c++17 -o "./build/main" main.cpp
    ./build/main $rom
    cd ..
}

clean() {
    cd "rks-16"
    if [ ! -d "./build" ]; then mkdir "./build"; fi
	find "./build/" -mindepth 1 -delete
    cd ..
}

assemble
clean
echo -e "\n========================================\n"
emulate