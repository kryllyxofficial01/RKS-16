#ifndef TOKEN
#define TOKEN

#include <string>

enum TokenTypes {
	MNEUMONIC,
	REGISTER,
	IMM16
};

typedef struct {
	TokenTypes type;
	std::string value;
} Token;

#endif
