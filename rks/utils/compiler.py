class Compiler:
	instructions = {
		"nop": (0, 0),
		"lda": (1, 1),
		"ldb": (2, 1),
		"ldc": (3, 1),
		"ldd": (4, 1),
		"swp": (5, 2),
		"mov": (6, 2),
		"sta": (7, 1),
		"stb": (8, 1),
		"stc": (9, 1),
		"std": (10, 1),
		"lra": (11, 0),
		"lrb": (12, 1),
		"lrc": (13, 1),
		"lrd": (14, 1),
		"psh": (15, 1),
		"pop": (16, 2),
		"isp": (17, 2),
		"dsp": (18, 1),
		"add": (19, 2),
		"sub": (20, 2),
		"mul": (21, 2),
		"div": (22, 2),
		"and": (23, 2),
		"or": (24, 2),
		"nor": (25, 2),
		"xor": (26, 2),
  		"not": (27, 1),
		"inc": (28, 1),
		"dec": (29, 1),
		"jmp": (30, 1),
		"cmp": (31, 2),
		"jz": (32, 1),
		"jnz": (33, 1),
		"jn": (34, 1),
		"jnn": (35, 1),
		"jo": (36, 1),
		"jno": (37, 1),
		"out": (38, 1),
		"hlt": (39, 1),
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
	
	def __init__(self, instruction, error):
		self.instruction = instruction
		self.error = error

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
					else:
						self.error.print_stacktrace("ValueError", f"Invalid immediate '{arg[1:]}'")
				
				elif arg[0] == "@":
					if arg[1:] in self.registers.keys():
						argBin = "0"*(10-len(bin(self.registers[arg[1:]])[2:])) + bin(self.registers[arg[1:]])[2:]
					else:
						self.error.print_stacktrace("RegisterError", f"Unknown register ID '{arg[1:]}'")
      
				elif arg[0] == "0":
					base = arg[0:2]
					if base == "0b":
						try:
							temp = int(arg[2:], 2)
						except ValueError:
							self.error.print_stacktrace("ValueError", f"'{arg[2:]}' is not valid binary")
						else:
							argBin = "0"*(10-len(arg[2:])) + arg[2:].lstrip("0")
    			
				else:
					self.error.print_stacktrace("ArgError", f"Unknown argument prefix '{arg[0]}'")

				binary.append(argBin)
	
			if len(binary[1:]) == 2:
				args = binary[1:]
				for i in range(len(args)):
					args[i] = "0"*(5-len(args[i].lstrip("0"))) + args[i].lstrip("0")
		
				binary = list(binary[0]) + args
    
		else:
			extra = ", ".join([f"'{arg}'" for arg in instruction[1:][-(len(instruction[1:]) - self.instructions[instruction[0]][1]):]])
			self.error.print_stacktrace("ArgError", f"Extra arguments {extra}")

		return binary