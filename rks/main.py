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

variables = {}
lineno = 1
for instruction in instructions:
	error = Error(instruction, lineno, filename)

	if instruction.startswith("#"):
		directive = instruction[1:].split(" ")
		if directive[0].lower() == "def":
			variables[directive[1]] = int(directive[2])

	compiler = Compiler(instruction, labels, variables, instructions, error)
	compiled = "".join(compiler.compile())
	if compiled != "": bin_file.write(compiled + "\n")

	lineno += 1