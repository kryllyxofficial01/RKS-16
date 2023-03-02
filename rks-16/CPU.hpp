#pragma once

#define BITS 16
#define OPCODE 4
#define PARAMETER BITS-OPCODE

#include <iostream>
#include <vector>
#include <bitset>

#include "Registers.hpp"
#include "Memory.hpp"

class CPU {
	public:
		CPU(Memory, Registers);
		void start();

	private:
		Memory memory;
		Registers registers;
};

CPU::CPU(Memory memory, Registers registers) {
	this->memory = memory;
	this->registers = registers;
}

void CPU::start() {
	while (this->memory.ProgramROM.at(this->registers.PC) != "" && this->registers.PC != UINT16_MAX) {
		std::string instruction = this->memory.ProgramROM.at(this->registers.PC);
		std::string opcode = instruction.substr(0, OPCODE);
		std::string parameter = instruction.substr(OPCODE);

		switch (std::bitset<4>(opcode).to_ulong()) {
			case 0: break;
			
			case 1: {
				int registerID = std::bitset<PARAMETER/2>(parameter).to_ulong();
				std::string immediate = this->memory.ProgramROM.at(++this->registers.PC);
				this->registers[registerID] = (uint16_t) std::bitset<BITS>(immediate).to_ulong();
				break;
			}
			
			case 2: {
				int copiedRegister = std::bitset<PARAMETER/2>(parameter.substr(0, (PARAMETER)/2)).to_ulong();
				int destinationRegister = std::bitset<(PARAMETER)/2>(parameter.substr((PARAMETER)/2)).to_ulong();
				this->registers[destinationRegister] = this->registers[copiedRegister];
				break;
			}

			case 3: {
				int firstRegister = std::bitset<PARAMETER/2>(parameter.substr(0, (PARAMETER)/2)).to_ulong();
				int secondRegister = std::bitset<PARAMETER/2>(parameter.substr((PARAMETER)/2)).to_ulong();
				std::swap(this->registers[firstRegister], this->registers[secondRegister]);
				break;
			}

			case 4: {
				int registerID = std::bitset<PARAMETER>(parameter).to_ulong();
				std::string immediate = this->memory.ProgramROM.at(++this->registers.PC);
				this->memory.RAM[std::bitset<BITS>(immediate).to_ulong()] = this->registers[registerID];
				break;
			}

			case 5: {
				int registerID = std::bitset<PARAMETER/2>(parameter).to_ulong();
				std::string immediate = this->memory.ProgramROM.at(++this->registers.PC);
				this->registers[registerID] = this->memory.RAM[std::bitset<BITS>(immediate).to_ulong()];
				break;
			}

			case 6: {
				int registerID = std::bitset<PARAMETER>(parameter).to_ulong();
				this->memory.stack.push(this->registers[registerID]);
				break;
			}

			case 7: {
				int registerID = std::bitset<PARAMETER>(parameter).to_ulong();
				this->registers[registerID] = this->memory.stack.top();
				this->memory.stack.pop();
				break;
			}

			case 8: {
				int firstRegister = std::bitset<PARAMETER/2>(parameter.substr(0, (PARAMETER)/2)).to_ulong();
				int secondRegister = std::bitset<PARAMETER/2>(parameter.substr((PARAMETER)/2)).to_ulong();
				this->registers[firstRegister] &= this->registers[secondRegister];
				break;
			}

			case 9: {
				int firstRegister = std::bitset<PARAMETER/2>(parameter.substr(0, (PARAMETER)/2)).to_ulong();
				int secondRegister = std::bitset<PARAMETER/2>(parameter.substr((PARAMETER)/2)).to_ulong();
				this->registers[firstRegister] |= this->registers[secondRegister];
				break;
			}
			
			case 10: {
				int registerID = std::bitset<PARAMETER>(parameter).to_ulong();
				this->registers[registerID] = ~this->registers[registerID];
				break;
			}
		}

		this->registers.PC++;
	}

	std::cout << this->registers[0] << std::endl;
}