#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <bitset>

#include "Registers.hpp"

using string = std::string;

class Memory {
	public:
		class ProgramMemory;
		struct RAM;
};

struct Memory::RAM {
	std::vector<uint16_t> main;
	std::vector<uint16_t> stack;
};

class Memory::ProgramMemory {
	public:
		ProgramMemory(std::vector<string> instructions, Registers registers, Memory::RAM ram);
		void execute();
	
	private:
		std::vector<string> instructions;
		Registers registers;
		Memory::RAM ram;
};

Memory::ProgramMemory::ProgramMemory(std::vector<string> instructions, Registers registers, Memory::RAM ram) {
	this->instructions = instructions;
	this->registers = registers;
	this->ram = ram;
}

void Memory::ProgramMemory::execute() {
	for (string instruction: this->instructions) {
		string op_code = instruction.substr(0, 6);
		int code = (int) std::bitset<6>(op_code).to_ulong();

		uint16_t arg = (uint16_t) std::bitset<10>(instruction.substr(6)).to_ulong(); // Used for instructions that take in only 1 arguments
		uint16_t arg1 = (uint16_t) std::bitset<5>(instruction.substr(6, 5)).to_ulong(); // This, along with "arg2", is used for instructions with 2 arguments
		uint16_t arg2 = (uint16_t) std::bitset<5>(instruction.substr(instruction.size()-5)).to_ulong();

		switch (code) {
			case 0: break;                                                                                                                                                // NOP
			case 1: this->registers.registers.find(0)->second = arg; break;                                                                                               // LDA
			case 2: this->registers.registers.find(1)->second = arg; break;                                                                                               // LDB
			case 3: this->registers.registers.find(2)->second = arg; break;                                                                                               // LDC
			case 4: this->registers.registers.find(3)->second = arg; break;                                                                                               // LDD
			case 5: std::swap(this->registers.registers.find(arg1)->second, this->registers.registers.find(arg2)->second); break;                                         // SWP
			case 6: this->registers.registers.find(arg2)->second = this->registers.registers.find(arg1)->second; this->registers.registers.find(arg1)->second = 0; break; // MOV
			case 7: this->ram.main[this->registers.registers.find(arg)->second] = this->registers.registers.find(0)->second; break;                                       // STA
			case 8: this->ram.main[this->registers.registers.find(arg)->second] = this->registers.registers.find(1)->second; break;                                       // STB
			case 9: this->ram.main[this->registers.registers.find(arg)->second] = this->registers.registers.find(2)->second; break;                                       // STC
			case 10: this->ram.main[this->registers.registers.find(arg)->second] = this->registers.registers.find(3)->second; break;                                      // STD
			case 11: this->ram.main[this->registers.registers.find(arg)->second] = this->registers.registers.find(4)->second; break;                                      // STAO
			case 12: this->registers.registers.find(0)->second = this->ram.main[this->registers.registers.find(arg)->second]; break;                                      // LRA
			case 13: this->registers.registers.find(1)->second = this->ram.main[this->registers.registers.find(arg)->second]; break;                                      // LRB
			case 14: this->registers.registers.find(2)->second = this->ram.main[this->registers.registers.find(arg)->second]; break;                                      // LRC
			case 15: this->registers.registers.find(3)->second = this->ram.main[this->registers.registers.find(arg)->second]; break;                                      // LRD
			case 16: this->ram.stack[this->registers.registers.find(7)->second] = this->registers.registers.find(arg)->second; break;                                     // PSH
			case 17: this->registers.registers.find(arg)->second = this->ram.stack[this->registers.registers.find(7)->second]; break;                                     // PUL
			case 18: this->registers.registers.find(7)->second++; break;
			case 19: this->registers.registers.find(7)->second--; break;
		}

		this->registers.registers.find(6)->second++;
	}

	std::cout << this->ram.stack.at(2) << std::endl;
}