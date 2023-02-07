#pragma once

#include <iostream>
#include <bitset>

class Flags {
    public:
        static uint16_t updateFlags(uint16_t flagReg, int result);
};

uint16_t Flags::updateFlags(uint16_t flagReg, int result) {
    std::string flags = std::bitset<3>(flagReg).to_string();
    flags[0] = result == 0 ? '1' : '0';
    flags[1] = result < 0 ? '1' : '0';
    flags[2] = result > UINT16_MAX ? '1' : '0';
    
    return (uint16_t) std::bitset<3>(flags).to_ulong();
}