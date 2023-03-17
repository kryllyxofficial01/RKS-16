#ifndef MEM
#define MEM

#include "basic.h"

struct Memory {
    std::vector<uint16_t> RAM = std::vector<uint16_t>(65535, 0);
    std::vector<std::string> ProgramROM = std::vector<std::string>(65535, "");
    std::stack<uint16_t> stack;
};

#endif