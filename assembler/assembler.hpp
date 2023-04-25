#ifndef ASSEMBLER
#define ASSEMBLER

#include <iostream>
#include <vector>

#include "token.hpp"
#include "error.hpp"

void assemble(std::vector<Token> tokens, std::string filepath, Error error);

#endif