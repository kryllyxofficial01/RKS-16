#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <filesystem>

#include "rks.hpp"
#include "lexer.hpp"
#include "error.hpp"
#include "token.hpp"

#define WHITESPACE " \n\r\t\f\v"

using namespace std;

string trim(const string &str) {
	size_t start = str.find_first_not_of(WHITESPACE);
	string lstripped = (start == string::npos) ? "" : str.substr(start);

	size_t end = lstripped.find_last_not_of(WHITESPACE);
    return (end == string::npos) ? "" : lstripped.substr(0, end + 1);
}

int main() {
	string filepath = "tests/test.rks";
	vector<Instruction> instructions;

	ifstream reader(filepath);
	string line;
	int lineno = 1;
	while (getline(reader, line)) {
		instructions.push_back((Instruction) {
			.line = trim(line),
			.lineno = lineno,
			.file = filesystem::absolute(filepath)
		});

		lineno++;
	}

	for (Instruction instruction: instructions) {
		Error error(
			instruction.line,
			instruction.lineno,
			instruction.file
		);
		vector<Token> tokens = lex(instruction, error);

		for (Token token: tokens) {
			cout << "Token Type: " << token.type << "\nValue: " << token.value << endl << endl;;
		}
	}

	return 0;
}
