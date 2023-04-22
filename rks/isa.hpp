#ifndef ISA
#define ISA

#include <iostream>
#include <map>

const std::map<std::string, int> INSTRUCTIONS = {
    {"nop", 0},
    {"mov", 2},
    {"ldw", 2},
    {"psh", 1},
    {"pop", 1},
    {"add", 2},
    {"and", 2},
    {"or", 2},
    {"not", 1},
    {"jnz", 1},
    {"hlt", 0}
};
std::string REGISTERS[] = {"a", "b", "c", "d", "f", "sp"};

#endif