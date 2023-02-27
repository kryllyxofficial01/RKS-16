#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <bitset>
#include <stdlib.h>
#include <typeinfo>

#include "Registers.hpp"
#include "Flags.hpp"

using string = std::string;

class Memory {
	public:
		class ProgramMemory;
};

class Memory::ProgramMemory {
	public:
		ProgramMemory(std::vector<string>, Registers);
		void execute();
	
	private:
		std::vector<string> instructions;
		Registers registers;
};

Memory::ProgramMemory::ProgramMemory(std::vector<string> instructions, Registers registers) {
	this->instructions = instructions;
	this->registers = registers;
}

void Memory::ProgramMemory::execute() {
	while (this->registers.registers.find(5)->second < this->instructions.size() && this->instructions.at(this->registers.registers.find(5)->second) != "") {
		string instruction = this->instructions.at(this->registers.registers.find(5)->second);

		this->registers.registers.find(5)->second++;
	}
}
