#include <iostream>
#include <vector>
#include <map>
#include <cstring>

#include "token.hpp"

const std::map<std::string, int> INSTRUCTIONS = {
    {"nop", 0},
    {"mov", 2},
    {"ldw", 2},
    {"psh", 1},
    {"pop", 1},
    {"add", 2},
    {"and", 2},
    {"or", 2},
    {"not", 1},
    {"jnz", 1},
    {"hlt", 0}
};
std::string REGISTERS[] = {"a", "b", "c", "d", "f", "sp"};

std::vector<Token> lex(const std::string line) {
	std::vector<Token> tokens;

	std::string mneumonic = line.substr(0, line.find(" "));

	if (INSTRUCTIONS.count(mneumonic) > 0) {
		tokens.push_back((Token) {
			.type = MNEUMONIC,
			.value = mneumonic
		});
	}
	else {

	}

	std::string args[INSTRUCTIONS.find(mneumonic)->second];

	std::string params = line.substr(line.find(" ")+1);
	int arg = 0;
	for (int i = 0; i < params.length(); i++) {
		if (params.at(i) != ' ') {
			args[arg] += params.at(i);
		}
		else {
			arg += 1;
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
