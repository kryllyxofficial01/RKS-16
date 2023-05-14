#ifndef MEMORY
#define MEMORY

#include <iostream>
#include <vector>

class Memory {
    public:
        static std::vector<u_int16_t> main;
        static std::vector<std::string> program_rom;
};

#endif