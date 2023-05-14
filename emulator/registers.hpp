#ifndef REGISTERS
#define REGISTERS

#include <iostream>

class Registers {
    public:
        static u_int16_t A;
        static u_int16_t B;
        static u_int16_t C;
        static u_int16_t D;
        static u_int8_t F;
        static u_int8_t SP;
        static u_int16_t PC;
};

#endif