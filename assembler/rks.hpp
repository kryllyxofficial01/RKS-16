#ifndef RKS
#define RKS

#include <iostream>

struct Line {
    std::string line;
    int lineno;
    std::string file;
};

inline const std::string INSTRUCTIONS[] = {
    "nop", "mov", "stw", "ldw", "psh", "pop",
    "add", "and", "or", "not", "jnz", "hlt"
};

inline const int ARG_COUNTS[] = {
    0, 2, 2, 1, 1, 2, 2, 2, 1, 1, 0
};

enum Opcode {
    NOP = 0x0000,
    MOV = 0x0001,
    STW = 0x0002,
    LDW = 0x0003,
    PSH = 0x0004,
    POP = 0x0005,
    ADD = 0x0006,
    AND = 0x0007,
    OR = 0x0008,
    NOT = 0x0009,
    JNZ = 0x000A,
    HLT = 0x000B
};

struct Instruction {
    std::string name;
    Opcode opcode;
    int argc;
    std::string args[2];
};

inline const std::string REGISTERS[] = {
    "a", "b", "c", "d", "f", "sp"
};

enum Register {
    A = 0x00,
    B = 0x01,
    C = 0x02,
    D = 0x03,
    F = 0x04,
    SP = 0x05
};

#endif