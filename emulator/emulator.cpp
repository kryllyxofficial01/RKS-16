#include "emulator.hpp"

void emulate() {
    while (Registers::PC <= __UINT16_MAX__ && Memory::program_rom.at(Registers::PC) != "") {
        std::string binary = Memory::program_rom.at(Registers::PC);

        int opcode_len = lstrip(dectobin(MNEUMONICS.size(), 8), "0").length();
        std::string opcode = binary.substr(8, opcode_len);

        std::cout << opcode << std::endl;

        Registers::PC++;
    }
}