#ifndef ERROR
#define ERROR

#include <iostream>

class Error {
    public:
        Error(std::string line, int lineno, std::string filepath);
        void print_stacktrace(std::string error_name, std::string reason);

    private:
        std::string line;
        int lineno;
        std::string filepath;
};

#endif