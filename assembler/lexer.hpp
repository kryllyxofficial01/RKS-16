#ifndef LEXER
#define LEXER

#include <vector>

#include "token.hpp"

// Turn a program line into a series of tokens
std::vector<Token> lex(std::string line);

#endif
