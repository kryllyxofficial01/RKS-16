#ifndef RKS16_HPP
#define RKS16_HPP

#include "Constants.hpp"
#include "Memory.hpp"
#include "Registers.hpp"
#include "Ports.hpp"

void ports::IO::output(const uint16_t address, const uint16_t value) {
	if (address == 0xFFFF) {
		std::cout << char(value);
	}
}

class RKS16 {
	public:
		RKS16(Memory, Registers);
		inline void run();

	private:
		Memory memory;
		Registers registers;
};

RKS16::RKS16(Memory memory, Registers registers) {
	this->memory = memory;
	this->registers = registers;
}

void RKS16::run() {
	while (this->memory.ProgramROM.at(this->registers.PC) != "" && this->registers.PC != UINT16_MAX) {
		std::string instruction = this->memory.ProgramROM.at(this->registers.PC);
		std::string opcode = instruction.substr(0, OPCODE);
		std::string parameter = instruction.substr(OPCODE);

		switch (std::bitset<OPCODE>(opcode).to_ulong()) {
			case 0: break;
			
			case 1: {
				int registerID = std::bitset<PARAMETER/2>(parameter).to_ulong();
				std::string immediate = this->memory.ProgramROM.at(++this->registers.PC);
				this->registers[registerID] = (uint16_t) std::bitset<BITS>(immediate).to_ulong();
				break;
			}
			
			case 2: {
				int copiedRegister = std::bitset<PARAMETER/2>(parameter.substr(0, (PARAMETER)/2)).to_ulong();
				int destinationRegister = std::bitset<(PARAMETER)/2>(parameter.substr((PARAMETER)/2)).to_ulong();
				this->registers[destinationRegister] = this->registers[copiedRegister];
				break;
			}

			case 3: {
				int firstRegister = std::bitset<PARAMETER/2>(parameter.substr(0, (PARAMETER)/2)).to_ulong();
				int secondRegister = std::bitset<PARAMETER/2>(parameter.substr((PARAMETER)/2)).to_ulong();
				std::swap(this->registers[firstRegister], this->registers[secondRegister]);
				break;
			}

			case 4: {
				int registerID = std::bitset<PARAMETER>(parameter).to_ulong();
				std::string immediate = this->memory.ProgramROM.at(++this->registers.PC);
				this->memory.RAM[std::bitset<BITS>(immediate).to_ulong()] = this->registers[registerID];

				ports::IO::output(
					std::bitset<BITS>(immediate).to_ulong(),
					this->memory.RAM[std::bitset<BITS>(immediate).to_ulong()]
				);

				break;
			}

			case 5: {
				int registerID = std::bitset<PARAMETER/2>(parameter).to_ulong();
				std::string immediate = this->memory.ProgramROM.at(++this->registers.PC);
				this->registers[registerID] = this->memory.RAM[std::bitset<BITS>(immediate).to_ulong()];
				break;
			}

			case 6: {
				int registerID = std::bitset<PARAMETER>(parameter).to_ulong();
				this->memory.stack.push(this->registers[registerID]);
				break;
			}

			case 7: {
				int registerID = std::bitset<PARAMETER>(parameter).to_ulong();
				this->registers[registerID] = this->memory.stack.top();
				this->memory.stack.pop();
				break;
			}

			case 8: {
				int firstRegister = std::bitset<PARAMETER/2>(parameter.substr(0, (PARAMETER)/2)).to_ulong();
				int secondRegister = std::bitset<PARAMETER/2>(parameter.substr((PARAMETER)/2)).to_ulong();
				this->registers.updateFlags(this->registers[firstRegister] + this->registers[secondRegister]);
				this->registers[firstRegister] += this->registers[secondRegister];
				break;
			}

			case 9: {
				int firstRegister = std::bitset<PARAMETER/2>(parameter.substr(0, (PARAMETER)/2)).to_ulong();
				int secondRegister = std::bitset<PARAMETER/2>(parameter.substr((PARAMETER)/2)).to_ulong();
				this->registers.updateFlags(this->registers[firstRegister] - this->registers[secondRegister]);
				this->registers[firstRegister] -= this->registers[secondRegister];
				break;
			}

			case 10: {
				int firstRegister = std::bitset<PARAMETER/2>(parameter.substr(0, (PARAMETER)/2)).to_ulong();
				int secondRegister = std::bitset<PARAMETER/2>(parameter.substr((PARAMETER)/2)).to_ulong();
				this->registers.updateFlags(this->registers[firstRegister] * this->registers[secondRegister]);
				this->registers[firstRegister] *= this->registers[secondRegister];
				break;
			}

			case 11: {
				int firstRegister = std::bitset<PARAMETER/2>(parameter.substr(0, (PARAMETER)/2)).to_ulong();
				int secondRegister = std::bitset<PARAMETER/2>(parameter.substr((PARAMETER)/2)).to_ulong();
				this->registers.updateFlags(this->registers[firstRegister] / this->registers[secondRegister]);
				this->registers[firstRegister] /= this->registers[secondRegister];
				break;
			}

			case 12: {
				int firstRegister = std::bitset<PARAMETER/2>(parameter.substr(0, (PARAMETER)/2)).to_ulong();
				int secondRegister = std::bitset<PARAMETER/2>(parameter.substr((PARAMETER)/2)).to_ulong();
				this->registers.updateFlags(this->registers[firstRegister] & this->registers[secondRegister]);
				this->registers[firstRegister] &= this->registers[secondRegister];
				break;
			}

			case 13: {
				int firstRegister = std::bitset<PARAMETER/2>(parameter.substr(0, (PARAMETER)/2)).to_ulong();
				int secondRegister = std::bitset<PARAMETER/2>(parameter.substr((PARAMETER)/2)).to_ulong();
				this->registers.updateFlags(this->registers[firstRegister] | this->registers[secondRegister]);
				this->registers[firstRegister] |= this->registers[secondRegister];
				break;
			}

			case 14: {
				int registerID = std::bitset<PARAMETER>(parameter).to_ulong();
				this->registers.updateFlags(~this->registers[registerID]);
				this->registers[registerID] = ~this->registers[registerID];
				break;
			}

			case 15: {
				int firstRegister = std::bitset<PARAMETER/2>(parameter.substr(0, (PARAMETER)/2)).to_ulong();
				int secondRegister = std::bitset<PARAMETER/2>(parameter.substr((PARAMETER)/2)).to_ulong();
				this->registers.updateFlags(this->registers[firstRegister] - this->registers[secondRegister]);
				break;
			}

			case 16: {
				std::string immediate = this->memory.ProgramROM.at(++this->registers.PC);
				this->registers.PC = std::bitset<16>(immediate).to_ulong();
				break;
			}

			case 17: {
				std::string immediate = this->memory.ProgramROM.at(++this->registers.PC);
				std::string flags = std::bitset<3>(this->registers.F).to_string();
				this->registers.PC = flags[0] == '1' ? std::bitset<16>(immediate).to_ulong() : this->registers.PC;
				break;
			}

			case 18: {
				std::string immediate = this->memory.ProgramROM.at(++this->registers.PC);
				std::string flags = std::bitset<3>(this->registers.F).to_string();
				this->registers.PC = flags[1] == '1' ? std::bitset<16>(immediate).to_ulong() : this->registers.PC;
				break;
			}

			case 19: {
				std::string immediate = this->memory.ProgramROM.at(++this->registers.PC);
				std::string flags = std::bitset<3>(this->registers.F).to_string();
				this->registers.PC = flags[2] == '1' ? std::bitset<16>(immediate).to_ulong() : this->registers.PC;
				break;
			}

			case 20: {
				std::cout << "\u001b[33mHalted CPU." << std::endl; 
				std::exit(0);
				break;
			}
		}

		this->registers.PC++;
	}
}

#endif