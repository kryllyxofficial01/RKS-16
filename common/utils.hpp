#ifndef UTILS
#define UTILS

#include <string>

#include "constants.hpp"

// Covert a decimal number to binary
std::string dectobin(int integer, int width);

// Remove all leading a trailing whitespace
std::string trim(const std::string &str);

// Remove all leading whitespace
std::string lstrip(const std::string &str, std::string trimmed);

#endif