class Compiler:
	instructions = {
		"nop": (0, 0),
		"lda": (1, 1),
		"ldb": (2, 1),
		"ldc": (3, 1),
		"ldd": (4, 1)
	}
	
	def __init__(self, instruction):
		self.instruction = instruction

	def compile(self) -> list:
		binary = []
		
		instruction = [i.strip().lower() for i in self.instruction.split(" ")]
		print(f"Current Instruction: {instruction[0]} -> {'0'*(6-len(bin(self.instructions[instruction[0]][0])[2:])) + bin(self.instructions[instruction[0]][0])[2:]}")
		
		binary.append("0"*(6-len(bin(self.instructions[instruction[0]][0])[2:])) + bin(self.instructions[instruction[0]][0])[2:])		
		for arg in instruction[1:]:
			argBin = ""
			if arg[0] == "!":
				if arg[1:].isnumeric():
					argBin = "0"*(10-len(bin(int(arg[1:]))[2:])) + bin(int(arg[1:]))[2:]

			binary.append(argBin)

		return binary