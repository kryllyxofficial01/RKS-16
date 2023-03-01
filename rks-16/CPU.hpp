#pragma once

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
		std::string opcode = instruction.substr(0, 4);
		std::string parameter = instruction.substr(4);
		std::string immediate = this->memory.ProgramROM.at(++this->registers.PC);

		switch (std::bitset<4>(opcode).to_ulong()) {
			case 0: break;
			
			case 1: {
				int registerID = std::bitset<12>(parameter).to_ulong();
				this->registers[registerID] = (uint16_t) std::bitset<16>(immediate).to_ulong();
				break;
			}
			
			case 2: {
				int copiedRegister = std::bitset<6>(parameter.substr(0, 6)).to_ulong();
				int destinationRegister = std::bitset<6>(parameter.substr(6)).to_ulong();
				this->registers[destinationRegister] = this->registers[copiedRegister];
				break;
			}

			case 3: {
				int firstRegister = std::bitset<6>(parameter.substr(0, 6)).to_ulong();
				int secondRegister = std::bitset<6>(parameter.substr(6)).to_ulong();
				std::swap(this->registers[firstRegister], this->registers[secondRegister]);
				break;
			}

			case 4: {
				int registerID = std::bitset<12>(parameter).to_ulong();
				this->memory.RAM[std::bitset<16>(immediate).to_ulong()] = this->registers[registerID];
				break;
			}

			case 5: {
				int registerID = std::bitset<12>(parameter).to_ulong();
				this->registers[registerID] = this->memory.RAM[std::bitset<16>(immediate).to_ulong()];
				break;
			}
		}

		this->registers.PC++;
	}

	std::cout << this->registers[1] << std::endl;
}