from utils.compiler import Compiler

filename = "../tests/test.rks"
file = open(filename, 'r')

instructions = file.readlines()
for instruction in instructions:
	compiler = Compiler(instruction)
	binary = compiler.compile()

	print(binary)