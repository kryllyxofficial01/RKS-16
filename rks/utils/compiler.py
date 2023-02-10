from .error import Error

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
		"cmp": (30, 2),
		"jmp": (31, 1),
		"jz": (32, 1),
		"jnz": (33, 1),
		"jn": (34, 1),
		"jnn": (35, 1),
		"jo": (36, 1),
		"jno": (37, 1),
		"call": (38, 1),
		"ret": (39, 0),
		"out": (40, 1),
		"hlt": (41, 1),
	}
	registers = {
		"a": 0,
		"b": 1,
		"c": 2,
		"d": 3,
		"f": 4,
		"pc": 5,
		"sp": 6,
		"cs": 7
	}

	def __init__(self, instruction: str, labels: dict[str, tuple[int, list[str]]], macros: dict[str, tuple[int, list[str]]], lines: list[str], error: Error) -> None:
		self.instruction = instruction
		self.labels = labels
		self.macros = macros
		self.lines = lines
		self.error = error

	def compile(self) -> list[str]:
		binary = []
		start = 1
		word = ""

		instruction = [i.strip().lower() for i in self.instruction.split(" ")]
		instruction_idx = self.lines.index(self.instruction)
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
					base = arg[1]
					start = 0
					if base == "b":
						try:
							temp = int(arg[2:], 2)
						except ValueError:
							self.error.print_stacktrace("ValueError", f"'{arg[2:]}' is not valid binary")
						else:
							argBin = "0"*(10-len(bin(temp)[2:].lstrip("0"))) + bin(temp)[2:].lstrip("0")

					elif base == "x":
						try:
							temp = int(arg[2:].lower(), 16)
						except ValueError:
							self.error.print_stacktrace("ValueError", f"'{arg[2:]}' is not valid hexadecimal")
						else:
							argBin = "0"*(10-len(bin(temp)[2:].lstrip("0"))) + bin(temp)[2:].lstrip("0")

					else:
						self.error.print_stacktrace("ArgError", f"Unknown base '{arg[0:2]}'")

				elif arg[0] == ".":
					try:
						for label in self.labels.keys():
							if self.labels[label][0] > instruction_idx:
								self.labels[label] = (self.labels[label][0]+1, self.labels[label][1],)
        
						word = "0"*(16-len(bin(self.labels[arg[1:]][0])[2:])) + bin(self.labels[arg[1:]][0])[2:]
						argBin = "0"*10

					except KeyError: self.error.print_stacktrace("LabelError", f"Unknown label '{arg[1:]}'")
				
				elif arg[0] == "$":
					try:
						for macro in self.macros.keys():
							if self.macros[macro][0] > instruction_idx:
								self.macros[macro] = (self.labels[macro][0]+1, self.labels[macro][1],)

						word = "0"*(16-len(bin(self.macros[arg[1:]][0])[2:])) + bin(self.macros[arg[1:]][0])[2:]
						argBin = "0"*10

					except KeyError: self.error.print_stacktrace("MacroError", f"Unknown macro '{arg[1:]}'")

				else:
					self.error.print_stacktrace("ArgError", f"Unknown argument prefix '{arg[0]}'")

				if len(argBin) > 10:
					self.error.print_stacktrace("ValueError", f"Argument bit width goes over 10-bit limit: '{arg[start:]}' -> '{argBin}'")

				binary.append(argBin)

			if len(binary[1:]) == 2:
				args = binary[1:]
				for i in range(len(args)):
					args[i] = "0"*(5-len(args[i].lstrip("0"))) + args[i].lstrip("0")

				binary = list(binary[0]) + args

		else:
			extra = ", ".join([f"'{arg}'" for arg in instruction[1:][-(len(instruction[1:]) - self.instructions[instruction[0]][1]):]])
			self.error.print_stacktrace("ArgError", f"Extra arguments {extra}")
   
		if len(binary) == 1:
			binary.append("0"*10)

		return (binary + ["\n" + word]) if word else binary

	@classmethod
	def clean(cls, instructions: list[str]) -> list[str]:
		for i in range(len(instructions)):
			if instructions[i] == "\n" or instructions[i].startswith(";"): instructions[i] = ""
			else: instructions[i] = instructions[i].rstrip()
		return instructions

	@classmethod
	def collect(cls, lines: list[str], location: str) -> tuple[dict[str, tuple[int, list[str]]], dict[str, tuple[int, list[str]]] , list[str]]:
		labels = {}
		macros = {}
		instructions = []

		inLabel = False
		labelName = ""
		inMacro = False
		macroName = ""

		idx = 0
		for i in range(len(lines)):
			if lines[i].startswith("."):
				header = [temp.strip().lower() for temp in lines[i][1:].split(" ")]
				if header[0] == "label":
					labels[header[1]] = (idx, [])
					inLabel = True
					labelName = header[1]

				elif header[0] == "macro":
					macros[header[1]] = (idx, [])
					inMacro = True
					macroName = header[1]

				else: Error(lines[i], i+1, location).print_stacktrace("HeaderError", f"Unknown header type '{header[0]}'")

			elif lines[i] != "":
				if inLabel:
					if lines[i].startswith("    "): labels[labelName][1].append(lines[i].strip())
					else: inLabel = False
				
				elif inMacro:
					if lines[i] != "    ret": macros[macroName][1].append(lines[i].strip())
					else: inMacro = False

				instructions.append(lines[i])
				idx += 1

		return labels, macros, instructions