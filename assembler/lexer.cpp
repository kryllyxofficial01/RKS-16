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
	int arg_idxs[INSTRUCTIONS.find(mneumonic)->second];

	std::string params = line.substr(line.find(" ")+1);
	int argp = 0;
	int idx = 0;
	for (int i = 0; i < params.length(); i++) {
		if (params.at(i) != ' ' && params.at(i) != '\0') {
			args[argp] += params.at(i);

			if (instruction.line.at(line.find(" ")+idx) == ' ') {
				arg_idxs[argp] = line.find(" ")+idx+1;
			}
		}
		else {
			argp += 1;
		}

		idx++;
	}

	char* ptr;
	int i = 0;
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
				error.print_stacktrace(
					"ArgError",
					"Unknown register '" + instruction.line.substr(arg_idxs[i]+1, arg.length()-1) + "'"
				);
			}
		}
		else if (!(*ptr)) {
			tokens.push_back((Token) {
				.type = IMM16,
				.value = std::to_string(immediate)
			});
		}
		else {
			error.print_stacktrace(
				"ArgError",
				"Invalid immediate '" + instruction.line.substr(arg_idxs[i], arg.length()) + "'"
			);
		}

		i++;
	}

	return tokens;
}
