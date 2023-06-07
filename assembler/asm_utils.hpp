#ifndef ASM_UTILS
#define ASM_UTILS

#include <string>
#include <vector>

// Holds details about a specific line in an assembly program
struct Line {
    std::string line;
    int lineno;
    std::string file;
};

// The different types of arguments an instruction can have
enum ArgTypes {
    REG,
    IMM
};

// Holds details about an instruction argument
struct Arg {
    ArgTypes type;
    long long value;
};

// Holds details about an instruction
struct Instruction {
    int opcode;
    std::vector<Arg> args;
};

// The arguments counts for each instruction
const inline int ARG_COUNTS[] = {
    0, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1, 1, 1, 0
};

#endif