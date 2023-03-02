from error import Error

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
		"hlt": 1
	}
	
	registers = [
		"a",
		"b",
		"c",
		"d",
		"f",
		"pc"
	]
	
	def __init__(self, instruction: str, error: Error) -> None:
		self.instruction = instruction
		self.error = error
	
	def assemble(self) -> list[str]:
		instruction = self.instruction.split(" ")
		mneumonic = instruction[0]
		args = instruction[1:]
		opcode_width = len(bin(len(self.instructions))[2:])
		binary = []
		
		opcode = list(self.instructions.keys()).index(mneumonic)
		opcode_bin = bin(int(opcode))[2:]
		opcode = "0"*(opcode_width-len(opcode_bin)) + opcode_bin
		binary.append(opcode)

		print(f"Current instruction: {mneumonic} -> {opcode}")
	
		for arg in args:
			prefix = arg[0]
			if prefix == "@":
				register_id = self.registers.index(arg[1:])
				register_bin = bin(register_id)[2:]
				binary.append("0"*((16-opcode_width)-len(register_bin)) + register_bin)
	
			else:
				immediate_bin = bin(int(arg, base=0))[2:]
				binary.append("\n" +"0"*(16-len(immediate_bin)) + immediate_bin)

		if not any(arg[0] == "\n" for arg in binary[1:]) and len(binary[1:]) >= 2:
			args_bitwidth = 16-opcode_width
			binary.insert(1, "-"*(args_bitwidth % 2))

			for i in range(len(binary[1:])):
				if binary[i+1][0] != "\n" and binary[i+1] != "-":
					arg = binary[i+1].lstrip("0")
					arg_width = 0
					
					if args_bitwidth % 2 == 0: arg_width = int(args_bitwidth/2)
					else: arg_width = int((args_bitwidth - (args_bitwidth % 2))/2)

					binary[i+1] = "0"*(arg_width-len(arg)) + arg
	
		elif len(binary[1:]) == 0: binary.append("0"*(16-opcode_width))

		return [compiled.replace("-", "0") if "-" in compiled else compiled for compiled in binary] # wtf is this
	
	@staticmethod
	def clean(instructions: list[str]) -> None:
		for i in range(len(instructions)):
			instructions[i] = instructions[i].strip()
			if instructions[i].strip()[0] == ";":
				instructions[i] = ""