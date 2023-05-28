#ifndef ASSEMBLER
#define ASSEMBLER

#include <vector>
#include <string>
#include <algorithm>
#include <regex>

#include "token.hpp"
#include "error.hpp"
#include "asm_utils.hpp"
#include "../common/constants.hpp"
#include "../common/utils.hpp"

// Assemble an instruction
Instruction assemble(std::vector<Token> tokens, Error error);

// Handles all label declarations and usages
void handleLabels(std::vector<Line>* lines);

#endif