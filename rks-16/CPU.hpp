#pragma once

#include <iostream>
#include <vector>

class CPU {
	public:
		CPU(std::vector<std::string>);
		void start();

	private:
		std::vector<std::string> instructions;
};

CPU::CPU(std::vector<std::string> instructions) {
	this->instructions = instructions;
}

void CPU::start() {
	
}