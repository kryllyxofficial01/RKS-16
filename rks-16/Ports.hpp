#ifndef PORTS
#define PORTS

namespace rks::ports {
	class IO {
		public:
			static inline void output(const uint16_t, const uint16_t);
	};
}

#endif