#ifndef ASSEMBLER
#define ASSEMBLER

#include <vector>
#include <algorithm>

#include "token.hpp"
#include "error.hpp"
#include "asm_utils.hpp"
#include "../common/constants.hpp"

Instruction assemble(std::vector<Token> tokens, Error error);

#endif