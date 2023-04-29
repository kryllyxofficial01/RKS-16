#include "assembler.hpp"

Instruction assemble(std::vector<Token> tokens, Error error) {
    Instruction instruction;

    int argp = 0;
    for (Token token: tokens) {
        switch (token.type) {
            case MNEUMONIC: {
                auto index = std::find(INSTRUCTIONS.begin(), INSTRUCTIONS.end(), token.value);
                if (index != INSTRUCTIONS.end()) {
                    instruction.opcode = index - INSTRUCTIONS.begin();
                }
                else {
                    error.print_stacktrace(
                        "MneumonicError",
                        "Unknown mneumonic '" + token.value + "'"
                    );
                }

                break;
            }

            case REGISTER: {
                auto index = std::find(REGISTERS.begin(), REGISTERS.end(), token.value);
                if (index != REGISTERS.end()) {
                    instruction.args[argp] = index - REGISTERS.begin();
                }
                else {
                    error.print_stacktrace(
                        "ArgError",
                        "Unknown register '" + token.value + "'"
                    );
                }

                argp++;

                break;
            }

            case IMM16: {
                char* ptr;
                short immediate = (short) std::strtol(token.value.c_str(), &ptr, 0);
                instruction.args[argp] = immediate;

                argp++;

                break;
            }
        }
    }

    return instruction;
}