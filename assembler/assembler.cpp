#include "assembler.hpp"

Instruction assemble(std::vector<Token> tokens, Error error) {
    Instruction instruction;

    for (Token token: tokens) {
        switch (token.type) {
            case MNEUMONIC:
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

            case REGISTER:
                break;

            case IMM16:
                break;
        }
    }

    return instruction;
}