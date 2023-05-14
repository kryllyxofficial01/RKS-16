#include <iostream>
#include <vector>
#include <fstream>

#include "memory.hpp"

using namespace std;

int main() {
    Memory memory;
    memory.main = vector<u_int16_t>(65536, 0);
    memory.program_rom = vector<string>(65536, "");

    string filepath = "tests/test.bin";
    ifstream reader(filepath);

    string line;
    while(getline(reader, line)) {
        memory.program_rom.push_back(line);
    }

    return 0;
}