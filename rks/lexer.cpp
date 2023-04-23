#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#include "lexer.hpp"
#include "token.hpp"
#include "error.hpp"
#include "rks.hpp"

std::vector<Token> lex(const Instruction instruction, Error error) {
	std::vector<Token> tokens;

	std::string line = instruction.line;
	transform(line.begin(), line.end(), line.begin(), ::tolower);

	std::string mneumonic = line.substr(0, line.find(" "));

	if (INSTRUCTIONS.count(mneumonic) > 0) {
		tokens.push_back((Token) {
			.type = MNEUMONIC,
			.value = mneumonic
		});
	}
	else {
		error.print_stacktrace(
			"MneumonicError",
			"Unknown instruction '" + instruction.line.substr(0, line.find(" ")) + "'"
		);
	}

	std::string args[INSTRUCTIONS.find(mneumonic)->second];

	std::string params = line.substr(line.find(" ")+1);
	int argp = 0;
	for (int i = 0; i < params.length(); i++) {
		if (params.at(i) != ' ') {
			args[argp] += params.at(i);
		}
		else {
			argp += 1;
		}
	}

	char* ptr;
	for (std::string arg: args) {
		long immediate = std::strtol(arg.c_str(), &ptr, 0);

		if (arg.at(0) == '@') {
			if (REGISTERS->find(arg.substr(1)) != std::string::npos) {
				tokens.push_back((Token) {
					.type = REGISTER,
					.value = arg.substr(1)
				});
			}
			else {

			}
		}
		else if (!(*ptr)) {
			tokens.push_back((Token) {
				.type = IMM16,
				.value = std::to_string(immediate)
			});
		}
		else {

		}
	}

	return tokens;
}
