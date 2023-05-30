#ifndef ERROR
#define ERROR

#include <iostream>

// Handles all program errors
class Error {
    public:
        Error(std::string line, int lineno, std::string filepath);

        // Print an error message
        void print_stacktrace(std::string error_name, std::string reason) const;

        // Print an error message
        static void print_stacktrace(
            std::string line,
            int lineno,
            std::string filepath,
            std::string error_name,
            std::string reason
        );

    private:
        std::string line;
        int lineno;
        std::string filepath;
};

#endif