#ifndef EMU
#define EMU

#include <iostream>
#include <bitset>

#include"RKS-16.hpp"
#include "Memory.hpp"
#include "Registers.hpp"

// Main CPU class
class rks16::CPU {
	public:
		CPU(Memory, Registers);
		void run();

	private:
		Memory memory;
		Registers registers;
};

#endif