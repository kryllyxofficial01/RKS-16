#include <iostream>
#include <fstream>

#include "RKS-16.hpp"
#include "Memory.hpp"
#include "Registers.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	string filepath;
	Registers registers;
	Memory memory;

	ifstream reader(argv[1]);

	cout << "Reading binary..." << endl;
	string line;
	int i = 0;
	while (getline(reader, line)) {
		memory.ProgramROM.at(i) = line;
		i++;
	}

	cout << "Executing instructions...\n" << endl;
	RKS16 cpu(memory, registers);
	cpu.run();
}