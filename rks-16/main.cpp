#include "basic.h"

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
	RKS16 cpu(memory, registers);
	cpu.run();
}