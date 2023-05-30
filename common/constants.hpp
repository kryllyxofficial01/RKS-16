#ifndef CONSTANTS
#define CONSTANTS

#include <vector>
#include <string>

// The starting location of the stack
#define STACK_OFFSET 0x4000

// Whitespace characters
#define WHITESPACE " \n\r\t\f\v"

// Each of the instruction names
const inline std::vector<std::string> MNEUMONICS = {
    "nop", "mov", "stw", "ldw", "psh", "pop", "add",
    "and", "or", "not", "jmp", "jz", "jc", "hlt"
};

// Each of the register names
const inline std::vector<std::string> REGISTER_IDS = {
    "a", "b", "c", "d", "f", "sp"
};

#endif