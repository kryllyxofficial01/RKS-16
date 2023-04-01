#ifndef PORTS
#define PORTS

#include <iostream>

#include "RKS-16.hpp"

// Handler for ports
namespace rks16::ports {
	class IO {
		public:
			static inline void output(const uint16_t, const uint16_t);
	};
}

#endif