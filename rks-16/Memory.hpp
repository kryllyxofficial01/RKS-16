#ifndef MEM_HPP
#define MEM_HPP

#include "Constants.hpp"

struct Memory {
    std::vector<uint16_t> RAM = std::vector<uint16_t>(65536, 0);
    std::vector<std::string> ProgramROM = std::vector<std::string>(65536, "");
    std::stack<uint16_t> stack;
};

#endif