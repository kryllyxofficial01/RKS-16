#include <iostream>
#include <vector>
#include <fstream>

#include "emulator.hpp"
#include "memory.hpp"

using namespace std;

vector<u_int16_t> Memory::main = vector<u_int16_t>(__UINT16_MAX__+1, 0);
vector<string> Memory::program_rom = vector<string>(__UINT16_MAX__+1, "");

u_int16_t Registers::A = 0;
u_int16_t Registers::B = 0;
u_int16_t Registers::C = 0;
u_int16_t Registers::D = 0;
u_int8_t Registers::F = 0;
u_int8_t Registers::SP = 0xff;
u_int16_t Registers::PC = 0;

int main() {
    string filepath = "tests/test.bin";
    ifstream reader(filepath);

    string line;
    int lineno = 0;
    while(getline(reader, line)) {
        Memory::program_rom.at(lineno) = line;
        lineno++;
    }

    emulate();

    return 0;
}