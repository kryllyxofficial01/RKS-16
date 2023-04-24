#ifndef TOKEN
#define TOKEN

#include <iostream>

enum TokenTypes {
	MNEUMONIC,
	REGISTER,
	IMM16,
	POINTER
};

typedef struct {
	TokenTypes type;
	std::string value;
} Token;

#endif
