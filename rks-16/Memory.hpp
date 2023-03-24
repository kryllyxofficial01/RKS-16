#ifndef MEM
#define MEM

#include <vector>
#include <stack>

struct rks::Memory {
    std::vector<uint16_t> RAM;
    std::vector<std::string> ProgramROM;
    std::stack<uint16_t> stack;
};

#endif