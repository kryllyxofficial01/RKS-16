#include <iostream>
#include <vector>
#include <fstream>

#include "components/Memory.hpp"

using namespace std;

int main() {
	string filepath;

	// cout << "Enter the filepath: ";
	// cin >> filepath;

	ifstream reader("../tests/test");
	vector<string> instructions;

	string line;
	while (getline(reader, line)) {
		instructions.push_back(line);
	}

	Registers registers;
	Memory::RAM ram;
	ram.main.resize(65536);
	
	Memory::ProgramMemory programMemory(instructions, registers, ram);
	programMemory.execute();
}