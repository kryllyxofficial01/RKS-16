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

		binfile << string(8, '0');
		binfile << dectobin(
			instruction.opcode,
			opcode_len
		);

		if (instruction.args.size() == 0) {
			binfile << string(8-opcode_len, '0');
			binfile << "\n";
		}
		else if (instruction.args.size() == 1) {
			if (instruction.args.front().type == REG) {
				binfile << "0";
				binfile << dectobin(instruction.args.front().value, 7-opcode_len);
			}
			else if (instruction.args.front().type == IMM) {
				binfile << "1";
				binfile << string(7-opcode_len, '0') << "\n";
				binfile << dectobin(instruction.args.front().value, 16);
			}

			binfile << "\n";
		}
		else if (instruction.args.size() == 2) {
			if (instruction.args.back().type == REG) {
				binfile << "0";
			}
			else if (instruction.args.back().type == IMM) {
				binfile << "1";
			}

			binfile << string(7-opcode_len, '0') << "\n";
			for (Arg arg: instruction.args) {
				binfile << dectobin(arg.value, 16) << "\n";
			}
		}
	}

	return 0;
}
