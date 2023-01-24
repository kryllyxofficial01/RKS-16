class Compiler:
	instructions = {
		"nop": (0, 0),
		"lda": (1, 1),
		"ldb": (2, 1),
		"ldc": (3, 1),
		"ldd": (4, 1),
		"swp": (5, 2),
		"mov": (6, 2),
	}
	registers = {
		"a": 0,
		"b": 1,
		"c": 2,
		"d": 3,
		"f": 4,
		"pc": 5,
		"sp": 6
	}
	
	def __init__(self, instruction):
		self.instruction = instruction

	def compile(self) -> list:
		binary = []
		
		instruction = [i.strip().lower() for i in self.instruction.split(" ")]
		print(f"Current Instruction: {instruction[0]} -> {'0'*(6-len(bin(self.instructions[instruction[0]][0])[2:])) + bin(self.instructions[instruction[0]][0])[2:]}")
		
		if len(instruction[1:]) <= self.instructions[instruction[0]][1]:
			binary.append("0"*(6-len(bin(self.instructions[instruction[0]][0])[2:])) + bin(self.instructions[instruction[0]][0])[2:])		
			for arg in instruction[1:]:
				argBin = ""
				if arg[0] == "!":
					if arg[1:].isnumeric():
						argBin = "0"*(10-len(bin(int(arg[1:]))[2:])) + bin(int(arg[1:]))[2:]
				
				elif arg[0] == "@":
					if arg[1:] in self.registers.keys():
						argBin = "0"*(10-len(bin(self.registers[arg[1:]])[2:])) + bin(self.registers[arg[1:]])[2:]

				binary.append(argBin)
	
			if len(binary[1:]) == 2:
				args = binary[1:]
				for i in range(len(args)):
					args[i] = "0"*(5-len(args[i].lstrip("0"))) + args[i].lstrip("0")
		
				binary = list(binary[0]) + args
    
		else:
			pass

		return binary