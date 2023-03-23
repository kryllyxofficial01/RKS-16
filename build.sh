#!/bin/bash

main() {
    echo -n "Enter filepath: "
    read filepath
    export SOURCE=$filepath
}

assemble() {
    cd rks
    python main.py $SOURCE
    cd ..
}

emulate() {
    rom=${SOURCE%""."$(echo $SOURCE | awk -F "." '{print $NF}')"}
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

main
assemble
clean
echo -e "\n========================================\n"
emulate