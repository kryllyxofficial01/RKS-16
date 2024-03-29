#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

#include "lexer.hpp"
#include "assembler.hpp"
#include "token.hpp"
#include "error.hpp"
#include "asm_utils.hpp"
#include "../common/constants.hpp"
#include "../common/utils.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	string filepath = argv[1];
	vector<Line> lines;

	// Read all of the lines from the source file into a vector of Lines
	ifstream reader(filepath);
	string line;
	int lineno = 1;
	while (getline(reader, line)) {
		if (line != "" && line.front() != ';') {
			lines.push_back((Line) {
				.line = trim(line),
				.lineno = lineno,
				.file = filesystem::absolute(filepath).string()
			});
		}

		lineno++;
	}

	// Import standard macros
	std::string std = filesystem::absolute("assembler/std.rks").string();
	ifstream std_reader(std);
	line = "";
	lineno = 1;
	while (getline(std_reader, line)) {
		if (line != "" && line.front() != ';') {
			lines.push_back((Line) {
				.line = trim(line),
				.lineno = lineno,
				.file = std
			});
		}

		lineno++;
	}

	// Format the source code so all that is left is just the basic instructions
	handleIncludes(&lines);
	handleDirectives(&lines);
	handleMacros(&lines);
	handleLabels(&lines);

	ofstream binfile(
		filepath.substr(
			0, filepath.find_last_of(".")
		) + ".bin"
	);

	// Lex and assemble each line
	for (Line line: lines) {
		Error error(
			line.line,
			line.lineno,
			line.file
		);

		vector<Token> tokens = lex(line.line);
		Instruction instruction = assemble(tokens, error);

		// Write the instruction opcode
		int opcode_len = lstrip(
			dectobin(MNEUMONICS.size(), 8), "0"
		).length();

		binfile << string(8, '0');
		binfile << dectobin(
			instruction.opcode,
			opcode_len
		);

		// Write the binary for each argument
		if (instruction.args.size() == 0) {
			binfile << string(8-opcode_len, '0');
			binfile << "\n";
		}
		else if (instruction.args.size() == 1 || instruction.args.size() == 2) {
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
