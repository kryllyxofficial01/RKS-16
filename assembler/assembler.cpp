#include "assembler.hpp"

Instruction assemble(std::vector<Token> tokens, Error error) {
    Instruction instruction;

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
                        "Unknown instruction '" + token.value + "'"
                    );
                }

                break;
            }

            case REGISTER: {
                auto index = std::find(REGISTERS.begin(), REGISTERS.end(), token.value);
                if (index != REGISTERS.end()) {
                    instruction.args.push_back(index - REGISTERS.begin());
                }
                else {
                    error.print_stacktrace(
                        "ArgError",
                        "Unknown register '" + token.value + "'"
                    );
                }

                break;
            }

            case IMM16: {
                char* ptr;
                int immediate = std::strtol(token.value.c_str(), &ptr, 0);

                if (!(*ptr)) {
                    instruction.args.push_back(immediate);
                }
                else {
                    error.print_stacktrace(
                        "ArgError",
                        "Invalid immediate '" + token.value + "'"
                    );
                }
            }
        }
    }

    return instruction;
}