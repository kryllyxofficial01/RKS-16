#!/bin/bash

set -o errexit
echo -n "Enter filepath: "
read filepath

assemble() {
    python rks/main.py $filepath
}

emulate() {
    rom=${filepath%""."$(echo $filepath | awk -F "." '{print $NF}')"}
    g++ -std=c++17 -o rks-16/build/main rks-16/main.cpp
    rks-16/build/main $rom
    cd ..
}

clean() {
    if [ ! -d "rks-16/build" ]; then mkdir build; fi
	find "rks-16/build/" -mindepth 1 -delete
}

assemble
clean
echo -e "\n========================================\n"
emulate