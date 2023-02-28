#pragma once

#include <iostream>
#include <vector>

#include "Registers.hpp"

class CPU {
	public:
		CPU(std::vector<std::string>, Registers);
		void start();

	private:
		std::vector<std::string> instructions;
		Registers registers;
};

CPU::CPU(std::vector<std::string> instructions, Registers registers) {
	this->instructions = instructions;
	this->registers = registers;
}

void CPU::start() {
	
}