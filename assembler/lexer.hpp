#ifndef LEXER
#define LEXER

#include <iostream>
#include <vector>

#include "token.hpp"
#include "error.hpp"

std::vector<Token> lex(std::string line, Error error);

#endif
