#include <iostream>
#include <vector>
#include <fstream>

#include "CPU.hpp"
#include "Memory.hpp"
#include "Registers.hpp"

using namespace std;

int main() {
	string filepath;
	Registers registers;
	Memory memory;

	// cout << "Enter the filepath: ";
	// cin >> filepath;

	ifstream reader("../tests/test");

	cout << "Reading binary..." << endl;
	string line;
	int i = 0;
	while (getline(reader, line)) {
		memory.ProgramROM.at(i) = line;
		i++;
	}

	cout << "Executing instructions...\n" << endl;
	CPU cpu(memory, registers);
	cpu.start();
}