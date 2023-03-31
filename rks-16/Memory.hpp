#ifndef MEM
#define MEM

#include <iostream>
#include <vector>
#include <stack>

#include "RKS-16.hpp"

struct rks::Memory {
    std::vector<uint16_t> RAM;
    std::vector<std::string> ProgramROM;
    std::stack<uint16_t> stack;
};

#endif