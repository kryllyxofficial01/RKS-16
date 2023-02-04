import os

from utils.compiler import Compiler
from utils.error import Error

filename = os.path.abspath("../tests/test.rks")
file = open(filename, 'r')
bin_file = open(filename[:-4], 'w')

print("Compiling...")
instructions = Compiler.clean(file.readlines())
labels, instructions = Compiler.collect(instructions, filename)
instructions = [temp.strip() for temp in instructions]

lineno = 1
for instruction in instructions:
	error = Error(instruction, lineno, filename)
	compiler = Compiler(instruction, labels, instructions, error)
	bin_file.write("".join(compiler.compile()) + "\n")

	lineno += 1