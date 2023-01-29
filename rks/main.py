import os

from utils.compiler import Compiler
from utils.error import Error

filename = "../tests/test.rks"
file = open(filename, 'r')
bin_file = open(filename[:-4], 'w')

print("Compiling...")
instructions = Compiler.clean(file.readlines())
labels = Compiler.collect(instructions)
instructions = Compiler.clean(instructions)

print(instructions)

lineno = 1
for instruction in instructions:
	error = Error(instruction, lineno, os.path.abspath(filename))
	compiler = Compiler(instruction, error)
	bin_file.write("".join(compiler.compile()) + "\n")
 
	lineno += 1