import os, sys

from error import Error
from assembler import Assembler

filename = os.path.abspath("../tests/test.rks")
file = open(filename, 'r')
bin_file = open(filename[:-4], 'w')

instructions = file.readlines()
instructions = Assembler.clean(instructions)
labels, instructions = Assembler.collect(instructions)
Assembler.updateLabels(instructions, labels)

print(labels)

print("Assembling...")
for lineno in range(len(instructions)):
    if instructions[lineno] != "":
        error = Error(
            instructions[lineno],
            lineno+1,
            filename
        )

        assembler = Assembler(instructions[lineno], labels, error)
        binary = assembler.assemble()

        bin_file.write("".join(binary) + "\n")