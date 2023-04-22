#ifndef TOKEN
#define TOKEN

#include <iostream>

enum TokenTypes {
	MNEUMONIC = 0x0,
	REGISTER = 0x1,
	IMM16 = 0x2,
	POINTER = 0x3
};

typedef struct {
	uint8_t type;
	std::string value;
} Token;

#endif
