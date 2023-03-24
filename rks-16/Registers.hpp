#ifndef REGS
#define REGS

#include <bitset>

#include "RKS-16.hpp"

struct rks::Registers {
	// uint16_t A = 0;
	// uint16_t B = 0;
	// uint16_t C = 0;
	// uint16_t D = 0;
	// uint16_t F = 0;	
	// uint16_t PC = 0;

	uint16_t A;
	uint16_t B;
	uint16_t C;
	uint16_t D;
	uint16_t F;	
	uint16_t PC;

	inline uint16_t &operator[](const int);
	void updateFlags(const int);
};

#endif