import os

from utils.compiler import Compiler
from utils.error import *

filename = os.path.abspath("../tests/test.rks")
file = open(filename, 'r')
bin_file = open(filename[:-4], 'w')

print("Compiling...")
instructions = Compiler.clean(file.readlines())
labels, instructions = Compiler.collect(instructions, filename)
instructions = [temp.strip() for temp in instructions]

print(labels)

variables = {}
lineno = 1
for instruction in instructions:
	error = Error(instruction, lineno, filename)

	if instruction.startswith("#"):
		directive = instruction[1:].split(" ")
		if directive[0].lower() == "def":
			try: variables[directive[1]] = Compiler.getValue(directive[2])
			except PrefixError: error.print_stacktrace("ArgError", f"Unknown argument prefix '{directive[2][0]}'")
			except ImmediateValueError: error.print_stacktrace("ValueError", f"Invalid immediate '{directive[2][1:]}'")
			except BaseValueError: error.print_stacktrace(
				"ValueError", f"'{directive[2][2:]}' is not valid " +
				("binary" if directive[2][1] == "b" else f"'hexadecimal")
			)
			except BaseTypeError: error.print_stacktrace("ArgError", f"Unknown base '{directive[2][0:2]}'")
			except CharTerminationError: error.print_stacktrace("CharError", "Missing closing \"'\"")
			except CharContentError: error.print_stacktrace("CharError", f"Expected 1 character, but found {len(directive[2][1:-1])}")

	compiler = Compiler(instruction, labels, variables, instructions, error)
	compiled = "".join(compiler.compile())
	if compiled != "": bin_file.write(compiled + "\n")

	lineno += 1