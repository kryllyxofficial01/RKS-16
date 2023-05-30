#include "assembler.hpp"

Instruction assemble(std::vector<Token> tokens, Error error) {
    Instruction instruction;

    // Iterate through each token
    for (Token token: tokens) {
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

void handleDirectives(std::vector<Line>* lines) {
    std::vector<std::pair<std::string, int>> defines;

    // Iterate through each line and check if it is a directive
    for (int lineno = 0; lineno < lines->size(); lineno++) {
        if (lines->at(lineno).line.at(0) == '#') {
            // Get the name of the directive
            std::string directive = lines->at(lineno).line.substr(
                1, lines->at(lineno).line.find_first_of(" ")-1
            );

            // Get the arguments
            std::stringstream stream(
                lines->at(lineno).line.substr(
                    lines->at(lineno).line.find_first_of(" ")+1
                )
            );

            std::string arg;
            std::vector<std::string> args;

            while(std::getline(stream, arg, ' ')) {
                args.push_back(arg);
            }

            // Check the directive name
            if (directive == "define") {
                char* ptr;
                int immediate = std::strtol(
                    args.at(1).c_str(), &ptr, 0
                );

                // Check if it is a valid number
                if (!(*ptr)) {
                    defines.push_back(
                        std::make_pair(
                            args.at(0),
                            (u_int16_t)immediate
                        )
                    );
                }
                else {
                    Error::print_stacktrace(
                        lines->at(lineno).line,
                        lines->at(lineno).lineno,
                        lines->at(lineno).file,
                        "ArgError",
                        "Invalid immediate '" + args.at(1) + "'"
                    );
                }
            }

            lines->erase(lines->begin()+lineno);
            lineno--;
        }
    }

    // Find all usages of defines and replace their names with their values
    if (defines.size() > 0) {
        for (int i = 0; i < lines->size(); i++) {
            for (auto define: defines) {
                lines->at(i).line = std::regex_replace(
                    lines->at(i).line,
                    std::regex("\\$" + define.first), // regexes are weird
                    std::to_string(define.second)
                );
            }
        }
    }
}

void handleIncludes(std::vector<Line>* lines) {
    // Iterate through each line and check if it is a directive
    for (int lineno = 0; lineno < lines->size(); lineno++) {
        if (lines->at(lineno).line.at(0) == '#') {
            // Get the name of the directive
            std::string directive = lines->at(lineno).line.substr(
                1, lines->at(lineno).line.find_first_of(" ")-1
            );

            // Check if the directive is an include
            if (directive == "include") {
                // Read from the included file
                std::vector<Line> _lines = include(
                    lines->at(lineno),
                    lines->at(lineno).line.substr(
                        lines->at(lineno).line.find_first_of(" ")+1
                    )
                );

                lines->erase(lines->begin()+lineno);

                // Insert the included lines
                for (Line line: _lines) {
                    lines->insert(lines->begin()+(lineno+line.lineno), line);
                }

                lineno--;
            }
        }
    }
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
                    ) // Screw never-nesters
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
        ) - MNEUMONICS.begin(); // I'm not sure if the word "mneumonic" has been typed enough times

        int argc = ARG_COUNTS[index];

        // Update the label location
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
    if (labels.size() > 0) {
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
}

std::vector<Line> include(Line line, std::string file) {
    std::vector<Line> lines;

    // Verify there are quotation marks
    if (file.at(0) == '"' && file.at(file.size()-1) == '"') {
        file = file.substr(1, file.size()-2);
        std::string source_dir = std::filesystem::path(line.file).parent_path().string();

        // Add the path separator based on what OS the user is on
        #ifdef __linux__
        source_dir += "/";
        #elif _WIN32 || _WIN64
        source_dir += "\\";
        #endif

        // Read from the included file
        std::string filepath = source_dir + file;
        std::ifstream reader(filepath);
        std::string line;

        int lineno = 1;
        while (getline(reader, line)) {
            if (line != "" && line.front() != ';') {
                lines.push_back((Line) {
                    .line = trim(line),
                    .lineno = lineno,
                    .file = filepath
                });
            }

            lineno++;
        }
    }
    else {
        Error::print_stacktrace(
            line.line,
            line.lineno,
            line.file,
            "ArgError",
            "Missing quotation mark(s)"
        ); // Static method calls go brr
    }

    return lines;
}