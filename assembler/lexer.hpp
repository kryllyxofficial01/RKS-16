#ifndef LEXER
#define LEXER

#include <iostream>
#include <vector>
#include <map>

#include "token.hpp"
#include "error.hpp"
#include "rks.hpp"

inline const std::map<std::string, int> INSTRUCTIONS = {
    {"nop", 0},
    {"mov", 2},
    {"ldw", 2},
    {"psh", 1},
    {"pop", 1},
    {"add", 2},
    {"and", 2},
    {"or", 2},
    {"not", 1},
    {"jnz", 1},
    {"hlt", 0}
};
inline const std::string REGISTERS[] = {"a", "b", "c", "d", "f", "sp"};

std::vector<Token> lex(const Instruction instruction, Error error);

#endif
