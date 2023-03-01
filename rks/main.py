import os

from error import Error
from assembler import Assembler

filename = os.path.abspath("../tests/test.rks")
file = open(filename, 'r')
bin_file = open(filename[:-4], 'w')

instructions = file.readlines()
Assembler.clean(instructions)

print("Assembling...")
for lineno in range(len(instructions)):
    if instructions[lineno] != "":
        error = Error(
            instructions[lineno],
            lineno+1,
            filename
        )

        assembler = Assembler(instructions[lineno], error)
        binary = assembler.assemble()

        bin_file.write("".join(binary) + "\n")