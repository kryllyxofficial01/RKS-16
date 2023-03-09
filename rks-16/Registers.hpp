#pragma once

#include <iostream>

struct Registers {
	uint16_t A = 0;
	uint16_t B = 0;
	uint16_t C = 0;
	uint16_t D = 0;
	uint16_t F = 0;	
	uint16_t PC = 0;

	inline uint16_t& operator[](int index) {
		return (&A)[index];
	}
};