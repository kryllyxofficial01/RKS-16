#include "assembler.hpp"

Instruction assemble(std::vector<Token> tokens, Error error) {
    Instruction instruction;

    for (Token token: tokens) {
        switch (token.type) {
            case MNEUMONIC: {
                auto index = std::find(MNEUMONICS.begin(), MNEUMONICS.end(), token.value);
                if (index != MNEUMONICS.end()) {
                    instruction.opcode = index - MNEUMONICS.begin();
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
                auto index = std::find(REGISTER_IDS.begin(), REGISTER_IDS.end(), token.value);
                if (index != REGISTER_IDS.end()) {
                    instruction.args.push_back((Arg) {
                        .type = REG,
                        .value = index - REGISTER_IDS.begin()
                    });
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
                    instruction.args.push_back((Arg) {
                        .type = IMM,
                        .value = immediate
                    });
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

    if (instruction.args.size() > ARG_COUNTS[instruction.opcode]) {
        error.print_stacktrace(
            "ArgError",
            "Too many arguments passed. Found "
            + std::to_string(instruction.args.size())
            + ", expected " + std::to_string(ARG_COUNTS[instruction.opcode])
        );
    }
    else if (instruction.args.size() < ARG_COUNTS[instruction.opcode]) {
        error.print_stacktrace(
            "ArgError",
            "Too few arguments passed. Found "
            + std::to_string(instruction.args.size())
            + ", expected " + std::to_string(ARG_COUNTS[instruction.opcode])
        );
    }

    return instruction;
}

void handleLabels(std::vector<Line>* lines) {
    std::vector<std::pair<std::string, int>> labels;

    for (int lineno = 0; lineno < lines->size(); lineno++) {
        if (lines->at(lineno).line.at(0) == '.') {
            labels.push_back(
                std::make_pair(lines->at(lineno).line.substr(1), lineno)
            );
            lines->erase(lines->begin()+lineno);
            lineno--;
        }
    }

    for (int lineno = 0; lineno < lines->size(); lineno++) {
        std::string mneumonic = lines->at(lineno).line.substr(0, lines->at(lineno).line.find_first_of(" "));
        int argc = ARG_COUNTS[std::find(MNEUMONICS.begin(), MNEUMONICS.end(), mneumonic) - MNEUMONICS.begin()];

        for (int i = 0; i < labels.size(); i++) {
            if (lineno - labels.at(i).second < 0) {
                labels.at(i) = std::make_pair(labels.at(i).first, labels.at(i).second + argc);
            }
        }
    }
}