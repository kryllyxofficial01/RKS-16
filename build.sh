#!/bin/bash

echo -n "Enter filepath: "
read filepath

assemble() {
    cd rks
    python main.py $filepath
}

emulate() {
    rom=${filepath%""."$(echo $filepath | awk -F "." '{print $NF}')"}
    cd "../rks-16"
    g++ -std=c++17 -o "./build/main" main.cpp
    ./build/main $rom
}

clean() {
    if [ ! -d "../rks-16/build" ]; then mkdir rks-16/build; fi
	find "../rks-16/build/" -mindepth 1 -delete
}

assemble
clean
echo -e "\n========================================\n"
emulate