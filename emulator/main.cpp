#include <iostream>
#include <vector>
#include <fstream>

#include "emulator.hpp"

using namespace std;

int main() {
    RKS16 machine;

    // Setup the CPU
    setup(&machine);

    // Read from the binary file
    string filepath = "tests/test.bin";
    ifstream reader(filepath);
    string line;
    int lineno = 0;
    while(getline(reader, line)) {
        machine.memory.program_rom.at(lineno) = line;
        lineno++;
    }

    // Start the emulator
    emulate(&machine);

    return 0;
}