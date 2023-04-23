#ifndef LEXER
#define LEXER

#include <iostream>
#include <vector>

#include "rks.hpp"
#include "error.hpp"
#include "token.hpp"

std::vector<Token> lex(const Instruction instruction, Error error);

#endif
