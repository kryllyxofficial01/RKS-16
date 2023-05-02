#include "lexer.hpp"

std::vector<Token> lex(std::string line, Error error) {
	std::vector<Token> tokens;

	std::string mneumonic;
	int i = 0;
	while (line.at(i) != ' ') {
		mneumonic += line.at(i);
		i++;
	}

	tokens.push_back((Token) {
		.type = MNEUMONIC,
		.value = mneumonic
	});

	std::vector<std::string> args;
	for (i = i; i < line.length(); i++) {
		if (line.at(i) != ' ') {
			args.back() += line.at(i);
		}
		else {
			args.push_back("");
		}
	}

	for (std::string arg: args) {

	}

	return tokens;
}
