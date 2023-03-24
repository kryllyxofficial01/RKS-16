#ifndef MEM
#define MEM

#include <iostream>
#include <vector>
#include <stack>

struct Memory {
    std::vector<uint16_t> RAM = std::vector<uint16_t>(65536, 0);
    std::vector<std::string> ProgramROM = std::vector<std::string>(65536, "");
    std::stack<uint16_t> stack;
};

#endif