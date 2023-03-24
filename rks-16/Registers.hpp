#ifndef REGS
#define REGS

struct rks::Registers {
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