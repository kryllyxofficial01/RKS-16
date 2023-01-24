from utils.compiler import Compiler
from utils.error import Error

filename = "../tests/test.rks"
file = open(filename, 'r')
bin_file = open(filename[:-4], 'w')

print("Compiling...")
instructions = file.readlines()
lineno = 0
for instruction in instructions:
	error = Error(instruction, lineno, file.name)
	compiler = Compiler(instruction, error)
	bin_file.write("".join(compiler.compile()) + "\n")
 
	lineno += 1