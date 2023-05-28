#include "assembler.hpp"

Instruction assemble(std::vector<Token> tokens, Error error) {
    Instruction instruction;

    // Iterate through each token
    for (Token token: tokens) {
        // Check the type of a token
        switch (token.type) {
            // If the type is an instruction name...
            case MNEUMONIC: {
                // Check if the token value is a valid instruction
                auto index = std::find(
                    MNEUMONICS.begin(),
                    MNEUMONICS.end(),
                    token.value
                );

                if (index != MNEUMONICS.end()) {
                    // Set the instruction opcode to be the index of the instruction name
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

            // If the type is a register name...
            case REGISTER: {
                // Check if the name is valid
                auto index = std::find(
                    REGISTER_IDS.begin(),
                    REGISTER_IDS.end(),
                    token.value
                );

                if (index != REGISTER_IDS.end()) {
                    // Set the register ID to be the index of the register name
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

            // If the type is a 16-bit immediate...
            case IMM16: {
                char* ptr;
                int immediate = std::strtol(
                    token.value.c_str(), &ptr, 0
                );

                // Check if it is a valid number
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

    // Check if the number of provided arguments matches the instruction's arg count
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

    // Iterate through each line and check if it is a valid label declaration
    for (int lineno = 0; lineno < lines->size(); lineno++) {
        // If it is, save the name and location
        if (lines->at(lineno).line.at(0) == '.') {
            labels.push_back(
                std::make_pair(
                    lines->at(lineno).line.substr(1),
                    lineno
                )
            );

            lines->erase(lines->begin()+lineno);
            lineno--;
        }
    }

    // Iterate through the lines again, and find out what each label should be offset by
    std::vector<std::pair<std::string, int>> offsets;
    for (int lineno = 0; lineno < lines->size(); lineno++) {
        for (int i = 0; i < labels.size(); i++) {
            if (labels.at(i).second > lineno) {
                offsets.push_back(
                    std::make_pair(
                        labels.at(i).first, lineno
                    )
                );
            }
        }
    }

    // Change the location of the labels to account for the extra bytes used by instruction arguments
    for (auto offset: offsets) {
        std::string mneumonic = lines->at(offset.second).line.substr(
            0, lines->at(offset.second).line.find_first_of(" ")
        );
        int index = std::find(
            MNEUMONICS.begin(),
            MNEUMONICS.end(),
            mneumonic
        ) - MNEUMONICS.begin();

        int argc = ARG_COUNTS[index];

        for (int i = 0; i < labels.size(); i++) {
            if (labels.at(i).first == offset.first) {
                labels.at(i) = std::make_pair(
                    labels.at(i).first,
                    labels.at(i).second + argc
                );
            }
        }
    }

    // Replace all occurences of a label name with its location
    for (int i = 0; i < lines->size(); i++) {
        for (auto label: labels) {
            lines->at(i).line = std::regex_replace(
                lines->at(i).line,
                std::regex(label.first),
                std::to_string(label.second)
            );
        }
    }
}