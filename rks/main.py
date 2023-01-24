from utils.compiler import Compiler

filename = "../tests/test.rks"
file = open(filename, 'r')
bin_file = open(filename[:-4], 'w')

instructions = file.readlines()
for instruction in instructions:
	compiler = Compiler(instruction)