#ifndef REG
#define REG

#include "basic.h"

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

	void updateFlags(int result) {
		std::string flags = std::bitset<FLAGS>(this->F).to_string();
		flags[0] = result == 0 ? '1' : '0';              // Zero Flag
		flags[1] = result > UINT16_MAX ? '1' : '0';      // Overflow
		flags[2] = result < 0 ? '1' : '0';               // Negative
		this->F = std::bitset<FLAGS>(flags).to_ulong();
	}
};

#endif