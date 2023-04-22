#include <iostream>
#include <vector>

#include "token.hpp"
#include "isa.hpp"

std::vector<Token> lex(std::string line) {
	std::vector<Token> tokens;

	std::string mneumonic = line.substr(0, line.find(" "));

	if (INSTRUCTIONS.count(mneumonic)) {
		tokens.push_back((Token) {
			.type = MNEUMONIC,
			.value = mneumonic
		});
	}
	else {

	}

	std::string args[INSTRUCTIONS.find(mneumonic)->second];

	return tokens;
}
