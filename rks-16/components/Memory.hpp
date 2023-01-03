#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <bitset>
#include <stdlib.h>

#include "Registers.hpp"

using string = std::string;

/**
 * @brief Handles all memory.
 */
class Memory {
	public:
		class ProgramMemory;
		struct RAM;
};

/**
 * @brief Container for both main memory and stack.
 */
struct Memory::RAM {
	std::vector<uint16_t> main;
	std::vector<uint16_t> stack;
};

/**
 * @brief Controls the execution of the compiled instruction binary.
 */
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

/**
 * @brief Executes the instructions.
 */
void Memory::ProgramMemory::execute() {
	while (this->registers.registers.find(5)->second < this->instructions.size()) {
		string instruction = this->instructions.at(this->registers.registers.find(5)->second);

		if (instruction == "") {
			break;
		}

		string op_code = instruction.substr(0, 6);
		int code = (int) std::bitset<6>(op_code).to_ulong();

		uint16_t x = (uint16_t) std::bitset<10>(instruction.substr(6)).to_ulong();
		uint16_t y = (uint16_t) std::bitset<5>(instruction.substr(6, 5)).to_ulong();
		uint16_t z = (uint16_t) std::bitset<5>(instruction.substr(instruction.size()-5)).to_ulong();

		switch (code) {
			case 0: break;
			case 1: this->registers.registers.find(0)->second = x; break;
			case 2: this->registers.registers.find(1)->second = x; break;
			case 3: this->registers.registers.find(2)->second = x; break;
			case 4: this->registers.registers.find(3)->second = x; break;
			case 5: std::swap(this->registers.registers.find(y)->second, this->registers.registers.find(z)->second); break;
			case 6: this->registers.registers.find(z)->second = this->registers.registers.find(y)->second; this->registers.registers.find(y)->second = 0; break;
			case 7: this->ram.main[this->registers.registers.find(x)->second] = this->registers.registers.find(0)->second; break;
			case 8: this->ram.main[this->registers.registers.find(x)->second] = this->registers.registers.find(1)->second; break;
			case 9: this->ram.main[this->registers.registers.find(x)->second] = this->registers.registers.find(2)->second; break;
			case 10: this->ram.main[this->registers.registers.find(x)->second] = this->registers.registers.find(3)->second; break;
			case 11: this->registers.registers.find(0)->second = this->ram.main[this->registers.registers.find(x)->second]; break;
			case 12: this->registers.registers.find(1)->second = this->ram.main[this->registers.registers.find(x)->second]; break;
			case 13: this->registers.registers.find(2)->second = this->ram.main[this->registers.registers.find(x)->second]; break;
			case 14: this->registers.registers.find(3)->second = this->ram.main[this->registers.registers.find(x)->second]; break;
			case 15: this->ram.stack[this->registers.registers.find(6)->second] = this->registers.registers.find(x)->second; break;
			case 16: this->registers.registers.find(x)->second = this->ram.stack[this->registers.registers.find(6)->second]; break;
			case 17: this->registers.registers.find(6)->second += x; break;
			case 18: this->registers.registers.find(6)->second += x; break;
			case 19: this->registers.registers.find(y)->second += this->registers.registers.find(z)->second; break;
			case 20: this->registers.registers.find(y)->second -= this->registers.registers.find(z)->second; break;
			case 21: this->registers.registers.find(y)->second *= this->registers.registers.find(z)->second; break;
			case 22: this->registers.registers.find(y)->second /= this->registers.registers.find(z)->second; break;
			case 23: this->registers.registers.find(y)->second &= this->registers.registers.find(z)->second; break;
			case 24: this->registers.registers.find(y)->second |= this->registers.registers.find(z)->second; break;
			case 25: this->registers.registers.find(y)->second = ~(this->registers.registers.find(y)->second | this->registers.registers.find(z)->second); break;
			case 26: this->registers.registers.find(y)->second ^= this->registers.registers.find(z)->second; break;
			case 27: this->registers.registers.find(x)->second = ~(this->registers.registers.find(x)->second); break;
			case 28: this->registers.registers.find(x)->second++; break;
			case 29: this->registers.registers.find(x)->second--; break;

			case 35: std::cout << this->registers.registers.find(x)->second << std::endl; break;
			case 36: std::cout << "\u001b[33mExited with code: " << x << "\u001b[0m" << std::endl; std::exit(x);
		}

		this->registers.registers.find(5)->second++;
	}
}