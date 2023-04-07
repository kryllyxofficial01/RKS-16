#ifndef MEM
#define MEM

#include <iostream>
#include <vector>
#include <stack>

#include "RKS-16.hpp"

// Container for all memory
struct rks16::Memory {
    std::vector<uint16_t> RAM;
    std::vector<std::string> ProgramROM;
    std::stack<uint16_t> Stack;
    std::stack<uint16_t> CallStack;
};

#endif