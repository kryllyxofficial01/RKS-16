#ifndef PORTS
#define PORTS

#include <iostream>

#include "RKS-16.hpp"

namespace rks::ports {
	class IO {
		public:
			static inline void output(const uint16_t, const uint16_t);
	};
}

#endif