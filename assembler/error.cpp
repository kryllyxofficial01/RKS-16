#include "error.hpp"

Error::Error(std::string line, int lineno, std::string filepath) {
    this->line = line;
    this->lineno = lineno;
    this->filepath = filepath;
}

void Error::print_stacktrace(std::string error_name, std::string reason) {
    printf("\x1b[31mError - at line %i in <%s>\n", this->lineno, this->filepath.c_str());
    printf("\t%s\n", this->line.c_str());
    printf("%s: %s\x1b[0m\n", error_name.c_str(), reason.c_str());

    std::exit(-1);
}