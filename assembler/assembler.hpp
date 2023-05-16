#ifndef ASSEMBLER
#define ASSEMBLER

#include <vector>
#include <string>
#include <algorithm>

#include "token.hpp"
#include "error.hpp"
#include "asm_utils.hpp"
#include "../common/constants.hpp"

Instruction assemble(std::vector<Token> tokens, Error error);
void handleLabels(std::vector<Line>* lines);

#endif