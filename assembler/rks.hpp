#ifndef RKS
#define RKS

#include <iostream>
#include <vector>

struct Line {
    std::string line;
    int lineno;
    std::string file;
};

inline const std::vector<std::string> INSTRUCTIONS = {
    "nop", "mov", "stw", "ldw", "psh", "pop",
    "add", "and", "or", "not", "jnz", "hlt"
};

inline const int ARG_COUNTS[] = {
    0, 2, 2, 1, 1, 2, 2, 2, 1, 1, 0
};

struct Instruction {
    int opcode;
    int args[2];
};

inline const std::vector<std::string> REGISTERS = {
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