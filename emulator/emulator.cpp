#include "emulator.hpp"

void emulate() {
    while (Registers::PC <= __UINT16_MAX__ && Memory::program_rom.at(Registers::PC) != "") {
        std::cout << Memory::program_rom.at(Registers::PC) << std::endl;

        Registers::PC++;
    }
}