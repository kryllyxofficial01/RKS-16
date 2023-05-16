#include "emulator.hpp"

void emulate() {
    while (Registers::PC <= __UINT16_MAX__ && Memory::program_rom.at(Registers::PC) != "") {
        std::string binary = Memory::program_rom.at(Registers::PC);

        int opcode_len = lstrip(dectobin(MNEUMONICS.size(), 8), "0").length();
        std::string opcode = binary.substr(8, opcode_len);
        int type = binary.at(8+opcode_len) - '0';

        switch (std::bitset<8>(opcode).to_ulong()) {
            case 0: break;

            case 1: {
                std::string destination = Memory::program_rom.at(++Registers::PC);
                std::string source = Memory::program_rom.at(++Registers::PC);

                updateRegister(
                    std::bitset<16>(destination).to_ulong(),
                    type ? std::bitset<16>(source).to_ulong() : getRegister(std::bitset<16>(source).to_ulong())
                );

                break;
            }

            case 2: {
                std::string destination = Memory::program_rom.at(++Registers::PC);
                std::string source = Memory::program_rom.at(++Registers::PC);

                Memory::main.at(std::bitset<16>(destination).to_ulong()) = type ?
                    std::bitset<16>(source).to_ulong() :
                    getRegister(std::bitset<16>(source).to_ulong()
                );

                break;
            }

            case 3: {
                std::string destination = Memory::program_rom.at(++Registers::PC);
                std::string source = Memory::program_rom.at(++Registers::PC);

                updateRegister(
                    std::bitset<16>(destination).to_ulong(),
                    Memory::main.at(
                        type ? std::bitset<16>(source).to_ulong() :
                        getRegister(std::bitset<16>(source).to_ulong())
                    )
                );

                break;
            }

            case 4: {
                std::string source = type ? Memory::program_rom.at(++Registers::PC) : binary.substr(9+opcode_len);

                Memory::main.at(Registers::SP + STACK_OFFSET) = type ? std::bitset<16>(source).to_ulong() :
                    getRegister(std::bitset<16>(source).to_ulong());
                Registers::SP--;

                break;
            }

            case 5: {
                std::string destination = binary.substr(9+opcode_len);

                updateRegister(std::bitset<8>(destination).to_ulong(), Memory::main.at(++Registers::SP + STACK_OFFSET));
                Memory::main.at(Registers::SP-1 + STACK_OFFSET) = 0;

                break;
            }

            case 6: {
                std::string a = Memory::program_rom.at(++Registers::PC);
                std::string b = Memory::program_rom.at(++Registers::PC);

                u_int16_t result = getRegister(std::bitset<16>(a).to_ulong()) + (
                    type ? std::bitset<16>(b).to_ulong() : getRegister(std::bitset<16>(b).to_ulong())
                );
                updateRegister(std::bitset<16>(a).to_ulong(), result);

                break;
            }

            case 7: {
                std::string a = Memory::program_rom.at(++Registers::PC);
                std::string b = Memory::program_rom.at(++Registers::PC);

                u_int16_t result = getRegister(std::bitset<16>(a).to_ulong()) & (
                    type ? std::bitset<16>(b).to_ulong() : getRegister(std::bitset<16>(b).to_ulong())
                );
                updateRegister(std::bitset<16>(a).to_ulong(), result);

                break;
            }

            case 8: {
                std::string a = Memory::program_rom.at(++Registers::PC);
                std::string b = Memory::program_rom.at(++Registers::PC);

                u_int16_t result = getRegister(std::bitset<16>(a).to_ulong()) | (
                    type ? std::bitset<16>(b).to_ulong() : getRegister(std::bitset<16>(b).to_ulong())
                );
                updateRegister(std::bitset<16>(a).to_ulong(), result);

                break;
            }

            case 9: {
                std::string a = Memory::program_rom.at(++Registers::PC);
                std::string b = Memory::program_rom.at(++Registers::PC);

                u_int16_t result = ~getRegister(std::bitset<16>(a).to_ulong());
                updateRegister(std::bitset<16>(a).to_ulong(), result);

                break;
            }

            case 10: {
                // TODO: Implement labels

                break;
            }

            case 11: std::exit(0); break;
        }

        Registers::PC++;
    }

    std::cout << Registers::A << std::endl;
}

void updateRegister(int id, u_int16_t value) {
    switch (id) {
        case 0: Registers::A = value; break;
        case 1: Registers::B = value; break;
        case 2: Registers::C = value; break;
        case 3: Registers::D = value; break;
        case 4: Registers::F = value; break;
        case 5: Registers::SP = value; break;
    }
}

u_int16_t getRegister(int id) {
    int value;

    switch (id) {
        case 0: value = Registers::A; break;
        case 1: value = Registers::B; break;
        case 2: value = Registers::C; break;
        case 3: value = Registers::D; break;
        case 4: value = Registers::F; break;
        case 5: value = Registers::SP; break;
    }

    return value;
}