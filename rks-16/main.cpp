#include <iostream>
#include <vector>
#include <fstream>

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

	for (string instruction: instructions) {
		cout << instruction << endl;
	}
}