#include <iostream>
#include <vector>
#include <fstream>

#include "components/Memory.hpp"
#include "components/Registers.hpp"
#include "components/Flags.hpp"

using namespace std;

int main() {
	string filepath;

	// cout << "Enter the filepath: ";
	// cin >> filepath;

	ifstream reader("../tests/test");
	vector<string> instructions;

	cout << "Reading binary..." << endl;
	string line;
	while (getline(reader, line)) {
		instructions.push_back(line);
	}

	if (instructions.size() > UINT16_MAX) {
		cout << "\u001b[33mWARNING: INSTRUCTION FILE GOES OVER 16-BIT LIMIT. EXTRA INSTRUCTIONS WILL BE SKIPPED DURING EXECUTION\u001b[0m\n" << endl;
	}

	instructions.resize(UINT16_MAX);

	cout << "Setting up components..." << endl;
	Registers registers;
	Memory::RAM ram;
	ram.main.resize(65024);

	cout << "Executing instructions...\n" << endl;
	Memory::ProgramMemory programMemory(instructions, registers, ram);
	programMemory.execute();
}