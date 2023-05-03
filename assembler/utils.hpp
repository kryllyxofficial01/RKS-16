#ifndef RKS
#define RKS

#include <iostream>
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

const inline std::vector<std::string> INSTRUCTIONS = {
    "nop", "mov", "stw", "ldw", "psh", "pop",
    "add", "and", "or", "not", "jnz", "hlt"
};

const inline std::vector<std::string> REGISTERS = {
    "a", "b", "c", "d", "f", "sp"
};

const inline int ARG_COUNTS[] = {
    0, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1, 0
};

#define WHITESPACE " \n\r\t\f\v"

std::string dectobin(int integer, int width);
std::string trim(const std::string &str);
std::string lstrip(const std::string &str, std::string trimmed);

#endif