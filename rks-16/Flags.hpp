#pragma once

#include <iostream>
#include <bitset>

#include "RKS-16.hpp"

class Flags {
    public:
        static uint16_t updateFlags(int result, Registers registers) {
            std::string flags = std::bitset<FLAGS>(registers.F).to_string();
            flags[0] = result == 0 ? '1' : '0'; // Zero Flag
            flags[1] = result > UINT16_MAX ? '1' : '0'; // Overflow
            flags[2] = result < 0 ? '1' : '0'; // Negative
            return std::bitset<FLAGS>(flags).to_ulong();
        }
};