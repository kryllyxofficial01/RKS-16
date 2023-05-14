#ifndef MEMORY
#define MEMORY

#include <iostream>
#include <vector>

struct Memory {
    std::vector<u_int16_t> main;
    std::vector<std::string> program_rom;
};

#endif