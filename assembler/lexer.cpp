#include "lexer.hpp"

std::vector<Token> lex(std::string line) {
	std::vector<Token> tokens;

	// Get the instruction name
	std::string mneumonic;
	int i = 0;
	while (!(i == line.length() || line.at(i) == ' ')) {
		mneumonic += line.at(i);
		i++;
	}

	tokens.push_back((Token) {
		.type = MNEUMONIC,
		.value = mneumonic
	});

	// Get all of the arguments
	std::vector<std::string> args;
	for (i = i; i < line.length(); i++) {
		if (line.at(i) != ' ') {
			args.back() += line.at(i);
		}
		else {
			args.push_back("");
		}
	}

	// Attempt to figure out the arguments' type
	for (std::string arg: args) {
		if (arg.at(0) == '@') {
			tokens.push_back((Token) {
				.type = REGISTER,
				.value = arg.substr(1)
			});
		}
		else {
			tokens.push_back((Token) {
				.type = IMM16,
				.value = arg
			});
		}
	}

	return tokens;
}
