#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <filesystem>

#include "rks.hpp"
#include "lexer.hpp"
#include "assembler.hpp"
#include "token.hpp"
#include "error.hpp"

#define WHITESPACE " \n\r\t\f\v"

using namespace std;

string trim(const string &str) {
	size_t start = str.find_first_not_of(WHITESPACE);
	string lstripped = (start == string::npos) ? "" : str.substr(start);

	size_t end = lstripped.find_last_not_of(WHITESPACE);
    return (end == string::npos) ? "" : lstripped.substr(0, end + 1);
}

string dectobin(int integer, int width) {
	string binary;

	for (int i = width-1; i >= 0; i--) {
		int bit = integer >> i;
		if (bit & 1) {
			binary += "1";
		}
		else {
			binary += "0";
		}
	}

	return binary;
}

int main() {
	string filepath = "tests/test.rks";
	vector<Line> lines;

	ifstream reader(filepath);
	string line;
	int lineno = 1;
	while (getline(reader, line)) {
		lines.push_back((Line) {
			.line = trim(line),
			.lineno = lineno,
			.file = filesystem::absolute(filepath)
		});
	}

	ofstream binfile(filepath.substr(0, filepath.find_last_of(".")));
	for (Line line: lines) {
		Error error(
			line.line,
			line.lineno,
			line.file
		);

		vector<Token> tokens = lex(line.line, error);
		Instruction instruction = assemble(tokens, error);

		string opcode = dectobin(instruction.opcode, opcode_len);

		binfile << opcode;
	}

	return 0;
}
