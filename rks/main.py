from utils.compiler import Compiler

filename = "../tests/test.rks"
file = open(filename, 'r')
bin_file = open(filename[:-4], 'w')

print("Compiling...")
instructions = file.readlines()
for instruction in instructions:
	compiler = Compiler(instruction)
	bin_file.write("".join(compiler.compile()) + "\n")