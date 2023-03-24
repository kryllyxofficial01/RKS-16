#include <iostream>
#include <fstream>

#include "CPU.hpp"
#include "Memory.hpp"
#include "Registers.hpp"
#include "Ports.hpp"
#include "Constants.hpp"

using namespace std;

rks::CPU::CPU(Memory memory, Registers registers) {
	this->memory = memory;
	this->registers = registers;
}

void rks::CPU::run() {
	while (this->memory.ProgramROM.at(this->registers.PC) != "" && this->registers.PC != UINT16_MAX) {
		string instruction = this->memory.ProgramROM.at(this->registers.PC);
		string opcode = instruction.substr(0, OPCODE);
		string parameter = instruction.substr(OPCODE);

		switch (bitset<OPCODE>(opcode).to_ulong()) {
			case 0: break;
			
			case 1: {
				int registerID = bitset<PARAMETER/2>(parameter).to_ulong();
				string immediate = this->memory.ProgramROM.at(++this->registers.PC);
				this->registers[registerID] = (uint16_t) bitset<BITS>(immediate).to_ulong();
				break;
			}
			
			case 2: {
				int copiedRegister = bitset<PARAMETER/2>(parameter.substr(0, (PARAMETER)/2)).to_ulong();
				int destinationRegister = bitset<(PARAMETER)/2>(parameter.substr((PARAMETER)/2)).to_ulong();
				this->registers[destinationRegister] = this->registers[copiedRegister];
				break;
			}

			case 3: {
				int firstRegister = bitset<PARAMETER/2>(parameter.substr(0, (PARAMETER)/2)).to_ulong();
				int secondRegister = bitset<PARAMETER/2>(parameter.substr((PARAMETER)/2)).to_ulong();
				std::swap(this->registers[firstRegister], this->registers[secondRegister]);
				break;
			}

			case 4: {
				int registerID = bitset<PARAMETER>(parameter).to_ulong();
				string immediate = this->memory.ProgramROM.at(++this->registers.PC);
				this->memory.RAM[bitset<BITS>(immediate).to_ulong()] = this->registers[registerID];

				rks::ports::IO::output(
					bitset<BITS>(immediate).to_ulong(),
					this->memory.RAM[bitset<BITS>(immediate).to_ulong()]
				);

				break;
			}

			case 5: {
				int registerID = bitset<PARAMETER/2>(parameter).to_ulong();
				string immediate = this->memory.ProgramROM.at(++this->registers.PC);
				this->registers[registerID] = this->memory.RAM[bitset<BITS>(immediate).to_ulong()];
				break;
			}

			case 6: {
				int registerID = bitset<PARAMETER>(parameter).to_ulong();
				this->memory.stack.push(this->registers[registerID]);
				break;
			}

			case 7: {
				int registerID = bitset<PARAMETER>(parameter).to_ulong();
				this->registers[registerID] = this->memory.stack.top();
				this->memory.stack.pop();
				break;
			}

			case 8: {
				int firstRegister = bitset<PARAMETER/2>(parameter.substr(0, (PARAMETER)/2)).to_ulong();
				int secondRegister = bitset<PARAMETER/2>(parameter.substr((PARAMETER)/2)).to_ulong();
				this->registers.updateFlags(this->registers[firstRegister] + this->registers[secondRegister]);
				this->registers[firstRegister] += this->registers[secondRegister];
				break;
			}

			case 9: {
				int firstRegister = bitset<PARAMETER/2>(parameter.substr(0, (PARAMETER)/2)).to_ulong();
				int secondRegister = bitset<PARAMETER/2>(parameter.substr((PARAMETER)/2)).to_ulong();
				this->registers.updateFlags(this->registers[firstRegister] - this->registers[secondRegister]);
				this->registers[firstRegister] -= this->registers[secondRegister];
				break;
			}

			case 10: {
				int firstRegister = bitset<PARAMETER/2>(parameter.substr(0, (PARAMETER)/2)).to_ulong();
				int secondRegister = bitset<PARAMETER/2>(parameter.substr((PARAMETER)/2)).to_ulong();
				this->registers.updateFlags(this->registers[firstRegister] * this->registers[secondRegister]);
				this->registers[firstRegister] *= this->registers[secondRegister];
				break;
			}

			case 11: {
				int firstRegister = bitset<PARAMETER/2>(parameter.substr(0, (PARAMETER)/2)).to_ulong();
				int secondRegister = bitset<PARAMETER/2>(parameter.substr((PARAMETER)/2)).to_ulong();
				this->registers.updateFlags(this->registers[firstRegister] / this->registers[secondRegister]);
				this->registers[firstRegister] /= this->registers[secondRegister];
				break;
			}

			case 12: {
				int firstRegister = bitset<PARAMETER/2>(parameter.substr(0, (PARAMETER)/2)).to_ulong();
				int secondRegister = bitset<PARAMETER/2>(parameter.substr((PARAMETER)/2)).to_ulong();
				this->registers.updateFlags(this->registers[firstRegister] & this->registers[secondRegister]);
				this->registers[firstRegister] &= this->registers[secondRegister];
				break;
			}

			case 13: {
				int firstRegister = bitset<PARAMETER/2>(parameter.substr(0, (PARAMETER)/2)).to_ulong();
				int secondRegister = bitset<PARAMETER/2>(parameter.substr((PARAMETER)/2)).to_ulong();
				this->registers.updateFlags(this->registers[firstRegister] | this->registers[secondRegister]);
				this->registers[firstRegister] |= this->registers[secondRegister];
				break;
			}

			case 14: {
				int registerID = bitset<PARAMETER>(parameter).to_ulong();
				this->registers.updateFlags(~this->registers[registerID]);
				this->registers[registerID] = ~this->registers[registerID];
				break;
			}

			case 15: {
				int firstRegister = bitset<PARAMETER/2>(parameter.substr(0, (PARAMETER)/2)).to_ulong();
				int secondRegister = bitset<PARAMETER/2>(parameter.substr((PARAMETER)/2)).to_ulong();
				this->registers.updateFlags(this->registers[firstRegister] - this->registers[secondRegister]);
				break;
			}

			case 16: {
				string immediate = this->memory.ProgramROM.at(++this->registers.PC);
				this->registers.PC = bitset<16>(immediate).to_ulong();
				break;
			}

			case 17: {
				string immediate = this->memory.ProgramROM.at(++this->registers.PC);
				string flags = bitset<3>(this->registers.F).to_string();
				this->registers.PC = flags[0] == '1' ? bitset<16>(immediate).to_ulong() : this->registers.PC;
				break;
			}

			case 18: {
				string immediate = this->memory.ProgramROM.at(++this->registers.PC);
				string flags = bitset<3>(this->registers.F).to_string();
				this->registers.PC = flags[1] == '1' ? bitset<16>(immediate).to_ulong() : this->registers.PC;
				break;
			}

			case 19: {
				string immediate = this->memory.ProgramROM.at(++this->registers.PC);
				string flags = bitset<3>(this->registers.F).to_string();
				this->registers.PC = flags[2] == '1' ? bitset<16>(immediate).to_ulong() : this->registers.PC;
				break;
			}

			case 20: {
				cout << "\u001b[33mHalted CPU." << std::endl; 
				std::exit(0);
				break;
			}
		}

		this->registers.PC++;
	}
}

inline uint16_t &rks::Registers::operator[](const int index) {
	return (&this->A)[index];
}

void rks::Registers::updateFlags(const int result) {
	string flags = bitset<FLAGS>(this->F).to_string();
	flags[0] = result == 0 ? '1' : '0'; // Zero Flag
	flags[1] = result > UINT16_MAX ? '1' : '0'; // Overflow
	flags[2] = result < 0 ? '1' : '0'; // Negative
	this->F = bitset<FLAGS>(flags).to_ulong();
}

void rks::ports::IO::output(const uint16_t address, const uint16_t value) {
	if (address == 0xFFFF) {
		cout << char(value);
	}
}

int main(int argc, char* argv[]) {
	rks::Registers registers;
	rks::Memory memory;
	memory.RAM = vector<uint16_t>(65536, 0);
    memory.ProgramROM = vector<string>(65536, "");

	string filepath;
	ifstream reader(argv[1]);

	cout << "Reading binary..." << endl;
	string line;
	int i = 0;
	while (getline(reader, line)) {
		memory.ProgramROM.at(i) = line;
		i++;
	}

	cout << "Executing instructions...\n" << endl;
	rks::CPU cpu(memory, registers);
	cpu.run();
}