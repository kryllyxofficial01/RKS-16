import os

from error import Error
from assembler import Assembler

filename = os.path.abspath("../tests/test.rks")
file = open(filename, 'r')
bin_file = open(filename[:-4], 'w')

instructions = file.readlines()
Assembler.clean(instructions)

print(instructions)