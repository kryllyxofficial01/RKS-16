#ifndef ASSEMBLER
#define ASSEMBLER

#include <iostream>
#include <vector>
#include <algorithm>

#include "token.hpp"
#include "error.hpp"
#include "utils.hpp"

Instruction assemble(std::vector<Token> tokens, Error error);

#endif