#ifndef ASSEMBLER
#define ASSEMBLER

#include <vector>
#include <string>
#include <algorithm>
#include <regex>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <tuple>

#include "token.hpp"
#include "error.hpp"
#include "asm_utils.hpp"
#include "../common/constants.hpp"
#include "../common/utils.hpp"

// Assemble an instruction
Instruction assemble(std::vector<Token> tokens, Error error);

// Handle directives
void handleDirectives(std::vector<Line>* lines);

// Handle all includes
void handleIncludes(std::vector<Line>* lines);

// Handle macro definitions
void handleMacros(std::vector<Line>* lines);

// Handles all label declarations and usages
void handleLabels(std::vector<Line>* lines);

// Grab the contents of a file
std::vector<Line> include(Line line, std::string file);

#endif