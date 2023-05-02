#ifndef RKS
#define RKS

#include <iostream>
#include <vector>
#include <bitset>

struct Line {
    std::string line;
    int lineno;
    std::string file;
};

inline const std::vector<std::string> INSTRUCTIONS = {
    "nop", "mov", "stw", "ldw", "psh", "pop",
    "add", "and", "or", "not", "jnz", "hlt"
};

const inline int opcode_len = (
    (INSTRUCTIONS.back().find_first_not_of("0") == std::string::npos)
    ? "" : INSTRUCTIONS.back().substr(INSTRUCTIONS.back().find_first_not_of("0"))
).length();

const inline int ARG_COUNTS[] = {
    0, 2, 2, 1, 1, 2, 2, 2, 1, 1, 0
};

struct Instruction {
    int opcode;
    int args[2];
};

const inline std::vector<std::string> REGISTERS = {
    "a", "b", "c", "d", "f", "sp"
};

const inline int registerID_len = (
    (REGISTERS.back().find_first_not_of("0") == std::string::npos)
    ? "" : REGISTERS.back().substr(REGISTERS.back().find_first_not_of("0"))
).length();

#endif