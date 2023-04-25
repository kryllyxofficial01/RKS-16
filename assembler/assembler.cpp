#include <iostream>

#include "assembler.hpp"
#include "token.hpp"
#include "error.hpp"

void assemble(std::vector<Token> tokens, std::string filepath, Error error) {
    for (Token token: tokens) {
        std::cout << "Token Type: " << token.type << "\nValue: " << token.value << std::endl << std::endl;
    }
}