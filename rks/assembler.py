from error import Error

# Hardcoded constants I'm not entirely sure how to get rid of
BITWIDTH = 16
NOREGS = ("nop", "jmp", "jz", "jo", "jn", "ret", "hlt")
HASIMM = ("ldi", "poke", "peek", "jmp", "jz", "jo", "jn")

# Assembler class
class Assembler:
	instructions = {
		"nop": 0,
		"ldi": 2,
		"mov": 2,
		"swp": 2,
		"poke": 2,
		"peek": 2,
		"psh": 1,
		"pop": 1,
		"add": 2,
		"sub": 2,
		"mul": 2,
		"div": 2,
		"and": 2,
		"or": 2,
		"not": 2,
		"cmp": 2,
		"jmp": 1,
		"jz": 1,
		"jo": 1,
		"jn": 1,
		"ret": 0,
		"hlt": 0
	}

	registers = [
		"a",
		"b",
		"c",
		"d",
		"f",
		"pc"
	]

	def __init__(self, instruction: str, labels: dict[str, int], directives: dict, error: Error) -> None:
		self.instruction = instruction
		self.labels = labels
		self.directives = directives
		self.error = error

	# Assembles the current instruction
	def assemble(self) -> list[str]:
		instruction = self.instruction.split(" ")
		mneumonic = instruction[0].lower()
		args = instruction[1:]
		opcode_width = len(bin(len(self.instructions))[2:])
		binary = []

		try: opcode = list(self.instructions.keys()).index(mneumonic)
		except ValueError: self.error.print_stacktrace(
			"MneumonicError",
			f"Invalid instruction '{mneumonic}'"
		)

		opcode_bin = bin(int(opcode))[2:]
		opcode = "0"*(opcode_width-len(opcode_bin)) + opcode_bin
		binary.append(opcode)

		print(f"Current instruction: {mneumonic} -> {opcode}")

		if len(args) > self.instructions[mneumonic]:
			extra = [f"'{arg}'" for arg in args[self.instructions[mneumonic]:]]
			self.error.print_stacktrace(
				"ArgError",
				f"Extra argument(s) {', '.join(extra)}"
			)

		for arg in args:
			prefix = arg[0]
			if prefix == "@":
				try: register_id = self.registers.index(arg[1:].lower())
				except ValueError: self.error.print_stacktrace(
					"RegisterError",
					f"Invalid register ID '{arg[1:]}'"
				)

				register_bin = bin(register_id)[2:]
				binary.append("0"*((BITWIDTH-opcode_width)-len(register_bin)) + register_bin)

			elif prefix == "$":
				try:
					immediate_bin = bin(self.directives["variables"][arg[1:]])[2:]
					binary.append("\n" +"0"*(BITWIDTH-len(immediate_bin)) + immediate_bin)

				except ValueError:
					try: immediate_bin = bin(self.labels[arg])[2:]
					except KeyError:
						self.error.print_stacktrace(
							"ArgError",
							f"Invalid argument '{arg}'"
						)

					binary.append("\n" +"0"*(BITWIDTH-len(immediate_bin)) + immediate_bin)

				except KeyError:
					self.error.print_stacktrace(
						"ArgError",
						f"Unknown variable '{arg[1:]}'"
					)

			else:
				try:
					immediate_bin = bin(int(arg, base=0))[2:]
					binary.append("\n" +"0"*(BITWIDTH-len(immediate_bin)) + immediate_bin)

				except ValueError:
					try: immediate_bin = bin(self.labels[arg])[2:]
					except KeyError: self.error.print_stacktrace(
						"ArgError",
						f"Invalid argument '{arg}'"
					)

					binary.append("\n" +"0"*(16-len(immediate_bin)) + immediate_bin)

		if not any(arg[0] == "\n" for arg in binary[1:]) and len(binary[1:]) >= 2:
			args_bitwidth = BITWIDTH-opcode_width
			binary.insert(1, "-"*(args_bitwidth % 2))

			for i in range(len(binary[1:])):
				if binary[i+1][0] != "\n" and binary[i+1] != "-":
					arg = binary[i+1].lstrip("0")
					arg_width = 0

					if args_bitwidth % 2 == 0: arg_width = int(args_bitwidth/2)
					else: arg_width = int((args_bitwidth - (args_bitwidth % 2))/2)

					binary[i+1] = "0"*(arg_width-len(arg)) + arg

		elif mneumonic in NOREGS:
			try: binary.insert(1, "0"*(BITWIDTH-opcode_width))
			except IndexError: binary.append("0"*(BITWIDTH-opcode_width))

		return [
			compiled.replace("-", "0")
			if "-" in compiled
			else compiled
			for compiled in binary
		]

	# Strip the instructions of all padded whitespace
	@staticmethod
	def clean(instructions: list[str]) -> list[str]:
		for i in range(len(instructions)):
			instructions[i] = instructions[i].strip()
			if instructions[i].strip() == "" or instructions[i].strip()[0] == ";":
				instructions[i] = ""

		return [instruction for instruction in instructions if instruction != ""]

	# Get all labels and save their location
	@staticmethod
	def handleLabels(instructions: list[str]) -> dict[str, int]:
		labels = {}

		for i in range(len(instructions)):
			if instructions[i].startswith("."):
				labels[instructions[i][1:]] = i
				instructions[i] = ""

		return labels, [instruction for instruction in instructions if instruction != ""]

	# Expand all the directives
	@staticmethod
	def handleDirectives(instructions: list[str], filename: str) -> dict:
		directives = {
			"variables": {}
		}

		for i in range(len(instructions)):
			if instructions[i].startswith("#"):
				directive = instructions[i][1:].split(" ")

				if directive[0] == "define":
					try: directives["variables"][directive[1]] = int(directive[2], base=0)
					except ValueError: Error(instructions[i], i+1, filename).print_stacktrace(
						"ArgError",
						f"Invalid immediate '{directive[2]}'"
					)
					except IndexError: Error(instructions[i], i+1, filename).print_stacktrace(
						"ArgError",
						"Missing immediate value"
					)

				else:
					Error(instructions[i], i+1, filename).print_stacktrace(
						"DirectiveError",
						f"Unknown directive '{directive[0]}'"
					)

				instructions[i] = ""

		return directives