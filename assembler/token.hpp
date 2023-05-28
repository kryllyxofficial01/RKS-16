#ifndef TOKEN
#define TOKEN

#include <string>

// Each of the different token types
enum TokenTypes {
	MNEUMONIC,
	REGISTER,
	IMM16
};

// Holds details about a token
typedef struct {
	TokenTypes type;
	std::string value;
} Token;

#endif
