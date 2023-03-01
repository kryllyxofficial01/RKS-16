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
	while (this->memory.ProgramROM.at(this->registers.PC) != "" && this->registers.PC != this->memory.ProgramROM.size()) {
		std::string instruction = this->memory.ProgramROM.at(this->registers.PC);
		std::string opcode = instruction.substr(0, 4);
		std::string parameter = instruction.substr(4);
		std::string immediate = this->memory.ProgramROM.at(++this->registers.PC);

		switch (std::bitset<4>(opcode).to_ulong()) {
			case 0: break;
			case 1:
				int registerID = std::bitset<12>(parameter).to_ulong();
				this->registers[registerID] = (uint16_t) std::bitset<16>(immediate).to_ulong();
				break;
		}

		this->registers.PC++;
	}
}