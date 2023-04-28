#include "error.hpp"

Error::Error(std::string line, int lineno, std::string filepath) {
    this->line = line;
    this->lineno = lineno;
    this->filepath = filepath;
}

void Error::print_stacktrace(std::string error_name, std::string reason) {
    std::cout << "\x1b[31mError - at line " << this->lineno << " in <" << this->filepath << ">" << std::endl;;
    std::cout << "\t" << this->line << std::endl;
    std::cout << error_name << ": " << reason << "\x1b[0m" <<std::endl;

    std::exit(-1);
}