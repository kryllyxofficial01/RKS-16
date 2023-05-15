#ifndef EMULATOR
#define EMULATOR

#include <iostream>
#include <vector>
#include <bitset>

#include "memory.hpp"
#include "registers.hpp"
#include "../common/utils.hpp"
#include "../common/constants.hpp"

void emulate();
void updateRegister(int id, u_int16_t value);
u_int16_t getRegister(int id);

#endif