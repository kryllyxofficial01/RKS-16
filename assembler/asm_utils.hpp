#ifndef ASM_UTILS
#define ASM_UTILS

#include <string>
#include <vector>

struct Line {
    std::string line;
    int lineno;
    std::string file;
};

enum ArgTypes {
    REG,
    IMM
};

struct Arg {
    ArgTypes type;
    long value;
};

struct Instruction {
    int opcode;
    std::vector<Arg> args;
};

const inline int ARG_COUNTS[] = {
    0, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1, 1, 1, 0
};

#endif