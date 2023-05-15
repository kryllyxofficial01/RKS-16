#ifndef UTILS
#define UTILS

#include <string>

#include "constants.hpp"

std::string dectobin(int integer, int width);
std::string trim(const std::string &str);
std::string lstrip(const std::string &str, std::string trimmed);

#endif