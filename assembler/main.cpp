#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

#include "lexer.hpp"
#include "assembler.hpp"
#include "token.hpp"
#include "error.hpp"
#include "utils.hpp"

using namespace std;

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

	ofstream binfile(filepath.substr(0, filepath.find_last_of(".")) + ".bin");
	for (Line line: lines) {
		Error error(
			line.line,
			line.lineno,
			line.file
		);

		vector<Token> tokens = lex(line.line);
		Instruction instruction = assemble(tokens, error);

		int opcode_len = lstrip(dectobin(INSTRUCTIONS.size(), 8), "0").length();
		switch (instruction.opcode) {
			case 0:
			case 11: {
				binfile << "00000000";

				binfile << dectobin(
					instruction.opcode,
					opcode_len
				) + string(8-opcode_len, '0');

				break;
			}
		}
	}

	return 0;
}
