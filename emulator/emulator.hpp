#ifndef EMULATOR
#define EMULATOR

#include <iostream>
#include <vector>
#include <bitset>

#include "../common/utils.hpp"
#include "../common/constants.hpp"

struct Registers {
    u_int16_t A;
    u_int16_t B;
    u_int16_t C;
    u_int16_t D;
    u_int8_t F;
    u_int8_t SP;
    u_int16_t PC;
};

struct Memory {
    std::vector<u_int16_t> main;
    std::vector<std::string> program_rom;
};

struct RKS16 {
    Registers registers;
    Memory memory;
};

void emulate(RKS16* machine);
void setup(RKS16* machine);
u_int16_t getRegister(RKS16* machine, int id);
void updateRegister(RKS16* machine, int id, u_int16_t value);

#endif