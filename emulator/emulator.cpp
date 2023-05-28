#include "emulator.hpp"

void emulate(RKS16* machine) {
    while (machine->registers.PC <= __UINT16_MAX__ && machine->memory.program_rom.at(machine->registers.PC) != "") {
        std::string binary = machine->memory.program_rom.at(machine->registers.PC);

        int opcode_len = lstrip(dectobin(MNEUMONICS.size(), 8), "0").length();
        std::string opcode = binary.substr(8, opcode_len);
        int type = binary.at(8+opcode_len) - '0';

        switch (std::bitset<8>(opcode).to_ulong()) {
            // nop
            case 0: break;

            // mov
            case 1: {
                std::string destination = machine->memory.program_rom.at(++machine->registers.PC);
                std::string source = machine->memory.program_rom.at(++machine->registers.PC);

                updateRegister(
                    machine,
                    std::bitset<16>(destination).to_ulong(),
                    type ? std::bitset<16>(source).to_ulong() : getRegister(machine, std::bitset<16>(source).to_ulong())
                );

                break;
            }

            // stw
            case 2: {
                std::string destination = machine->memory.program_rom.at(++machine->registers.PC);
                std::string source = machine->memory.program_rom.at(++machine->registers.PC);

                machine->memory.main.at(std::bitset<16>(destination).to_ulong()) = (
                    type ? std::bitset<16>(source).to_ulong() : getRegister(machine, std::bitset<16>(source).to_ulong())
                );

                break;
            }

            // ldw
            case 3: {
                std::string destination = machine->memory.program_rom.at(++machine->registers.PC);
                std::string source = machine->memory.program_rom.at(++machine->registers.PC);

                updateRegister(
                    machine,
                    std::bitset<16>(destination).to_ulong(),
                    machine->memory.main.at(
                        type ? std::bitset<16>(source).to_ulong() : getRegister(machine, std::bitset<16>(source).to_ulong())
                    )
                );

                break;
            }

            // psh
            case 4: {
                std::string source = type ? machine->memory.program_rom.at(++machine->registers.PC) : binary.substr(9+opcode_len);

                machine->memory.main.at(machine->registers.SP + STACK_OFFSET) = (
                    type ? std::bitset<16>(source).to_ulong() : getRegister(machine, std::bitset<16>(source).to_ulong())
                );
                machine->registers.SP--;

                break;
            }

            // pop
            case 5: {
                std::string destination = machine->memory.program_rom.at(++machine->registers.PC);

                updateRegister(
                    machine,
                    std::bitset<16>(destination).to_ulong(),
                    machine->memory.main.at(++machine->registers.SP + STACK_OFFSET)
                );
                machine->memory.main.at(machine->registers.SP-1 + STACK_OFFSET) = 0;

                break;
            }

            // add
            case 6: {
                std::string a = machine->memory.program_rom.at(++machine->registers.PC);
                std::string b = machine->memory.program_rom.at(++machine->registers.PC);

                int result = getRegister(machine, std::bitset<16>(a).to_ulong()) + (
                    type ? std::bitset<16>(b).to_ulong() : getRegister(machine, std::bitset<16>(b).to_ulong())
                );

                updateRegister(machine, std::bitset<16>(a).to_ulong(), result);
				updateFlags(machine, result);

                break;
            }

            // and
            case 7: {
                std::string a = machine->memory.program_rom.at(++machine->registers.PC);
                std::string b = machine->memory.program_rom.at(++machine->registers.PC);

                int result = getRegister(machine, std::bitset<16>(a).to_ulong()) & (
                    type ? std::bitset<16>(b).to_ulong() : getRegister(machine, std::bitset<16>(b).to_ulong())
                );
                updateRegister(machine, std::bitset<16>(a).to_ulong(), result);
				updateFlags(machine, result);

                break;
            }

            // or
            case 8: {
                std::string a = machine->memory.program_rom.at(++machine->registers.PC);
                std::string b = machine->memory.program_rom.at(++machine->registers.PC);

                int result = getRegister(machine, std::bitset<16>(a).to_ulong()) | (
                    type ? std::bitset<16>(b).to_ulong() : getRegister(machine, std::bitset<16>(b).to_ulong())
                );
                updateRegister(machine, std::bitset<16>(a).to_ulong(), result);
				updateFlags(machine, result);

                break;
            }

            // not
            case 9: {
                std::string a = machine->memory.program_rom.at(++machine->registers.PC);

                int result = ~getRegister(machine, std::bitset<16>(a).to_ulong());
                updateRegister(machine, std::bitset<16>(a).to_ulong(), result);
				updateFlags(machine, result);

                break;
            }

            // jmp
            case 10: {
                std::string label = machine->memory.program_rom.at(++machine->registers.PC);

                machine->registers.PC = std::bitset<16>(label).to_ulong()-1;

                break;
            }

            // jz
            case 11: {
				std::string label = machine->memory.program_rom.at(++machine->registers.PC);
                std::string flags = std::bitset<8>(machine->registers.F).to_string();

                machine->registers.PC = (flags[flags.size()-2] == '1') ? std::bitset<16>(label).to_ulong()-1 : machine->registers.PC;

                break;
            }

            // jc
            case 12 : {
                std::string label = machine->memory.program_rom.at(++machine->registers.PC);
                std::string flags = std::bitset<8>(machine->registers.F).to_string();

                machine->registers.PC = (flags.back() == '1') ? std::bitset<16>(label).to_ulong()-1 : machine->registers.PC;

                break;
            }

            // hlt
            case 13: goto done;
        }

        machine->registers.PC++;
    }

    done: return;
}

void setup(RKS16* machine) {
    machine->memory.main = std::vector<u_int16_t>(__UINT16_MAX__+1, 0);
    machine->memory.program_rom = std::vector<std::string>(__UINT16_MAX__+1, "");

    for (int i = 0; i < REGISTER_IDS.size(); i++) {
        updateRegister(machine, i, 0);
    }
    machine->registers.PC = 0;
}

u_int16_t getRegister(RKS16* machine, int id) {
    u_int16_t value;

    switch (id) {
        case 0: value = machine->registers.A; break;
        case 1: value = machine->registers.B; break;
        case 2: value = machine->registers.C; break;
        case 3: value = machine->registers.D; break;
        case 4: value = machine->registers.F; break;
        case 5: value = machine->registers.SP; break;
    }

    return value;
}

void updateRegister(RKS16* machine, int id, u_int16_t value) {
    switch (id) {
        case 0: machine->registers.A = value; break;
        case 1: machine->registers.B = value; break;
        case 2: machine->registers.C = value; break;
        case 3: machine->registers.D = value; break;
        case 4: machine->registers.F = value; break;
        case 5: machine->registers.SP = value; break;
    }
}

void updateFlags(RKS16* machine, int value) {
	std::string flags = std::bitset<8>(machine->registers.F).to_string();

    if (value < 0) value = (u_int16_t)value;

    flags[flags.size()-2] = (value == 0 || value == __UINT16_MAX__+1) ? '1' : '0';
	flags[flags.size()-1] = (value > __UINT16_MAX__) ? '1' : '0';

	updateRegister(machine, 4, std::bitset<8>(flags).to_ulong());
}
