import os

from utils.compiler import Compiler
from utils.error import Error

filename = "../tests/test.rks"
file = open(filename, 'r')
bin_file = open(filename[:-4], 'w')

print("Compiling...")
instructions = file.readlines()
lineno = 1
for instruction in instructions:
	if instruction != "\n" and instruction[0] != ";":
		error = Error(instruction, lineno, os.path.abspath(filename))
		compiler = Compiler(instruction, error)
		bin_file.write("".join(compiler.compile()) + "\n")
 
	lineno += 1