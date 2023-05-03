#include "utils.hpp"

std::string dectobin(int integer, int width) {
    std::string binary;

	for (int i = width-1; i >= 0; i--) {
		int bit = integer >> i;
		if (bit & 1) {
			binary += "1";
		}
		else {
			binary += "0";
		}
	}

	return binary;
}

std::string trim(const std::string &str) {
	size_t start = str.find_first_not_of(WHITESPACE);
	std::string lstripped = (start == std::string::npos) ? "" : str.substr(start);

	size_t end = lstripped.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : lstripped.substr(0, end + 1);
}

std::string lstrip(const std::string &str, std::string trimmed) {
	size_t start = str.find_first_not_of(trimmed);
    return (start == std::string::npos) ? "" : str.substr(start);
}