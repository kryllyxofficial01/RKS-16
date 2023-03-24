#ifndef PORTS
#define PORTS

#include <iostream>

namespace ports {
	class IO {
		public:
			static inline void output(const uint16_t, const uint16_t);
	};
}

#endif