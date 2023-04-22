#include <iostream>
#include <vector>

#include "token.hpp"

std::vector<Token> lex(std::string line) {
	std::vector<Token> tokens;

	tokens.push_back(
		(Token) {
			.type = MNEUMONIC,
			.value = line
		}
	);

	return tokens;
}
