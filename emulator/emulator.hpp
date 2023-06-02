#ifndef EMULATOR
#define EMULATOR

#include <iostream>
#include <vector>
#include <bitset>

#include "../common/utils.hpp"
#include "../common/constants.hpp"

// Container for the registers
struct Registers {
    u_int16_t A;
    u_int16_t B;
    u_int16_t C;
    u_int16_t D;
    u_int8_t F;
    u_int8_t SP;
    u_int16_t PC;
};

// Container for all memory
struct Memory {
    std::vector<u_int16_t> main;
    std::vector<std::string> program_rom;
};

// The entire CPU
struct RKS16 {
    Registers registers;
    Memory memory;
};

// Execute the program
void emulate(RKS16* machine);

// Setup registers and memory
void setup(RKS16* machine);

// Get a register value
u_int16_t getRegister(RKS16* machine, int id);

// Update a register
void updateRegister(RKS16* machine, int id, u_int16_t value);

// Update the flags register based on a value
void updateFlags(RKS16* machine, int value);

// Update a port
void updatePorts(RKS16* machine, u_int16_t port);

#endif
