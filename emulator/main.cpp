#include <iostream>
#include <vector>
#include <fstream>

#include "emulator.hpp"

using namespace std;

int main() {
    RKS16 machine;

    machine.memory.main = vector<u_int16_t>(__UINT16_MAX__+1, 0);
    machine.memory.program_rom = vector<std::string>(__UINT16_MAX__+1, "");

    string filepath = "tests/test.bin";
    ifstream reader(filepath);

    string line;
    int lineno = 0;
    while(getline(reader, line)) {
        machine.memory.program_rom.at(lineno) = line;
        lineno++;
    }

    emulate(&machine);

    return 0;
}