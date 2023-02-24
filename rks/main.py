import os

from utils.lexer import Lexer
from utils.error import Error

filename = os.path.abspath("../tests/test.rks")
file = open(filename, 'r')
bin_file = open(filename[:-4], 'w')

instructions = file.readlines()
lineno = 1
for instruction in instructions:
	error = Error(instruction, lineno, filename)
	lexer = Lexer(instruction, error)
	print(lexer.lex())