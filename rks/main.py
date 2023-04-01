import os
import sys

from error import Error
from assembler import Assembler

filename = os.path.abspath(sys.argv[-1])
file = open(filename, 'r')
bin_file = open(filename[:-4], 'w')

instructions = file.readlines()
instructions = Assembler.clean(instructions)
labels, instructions = Assembler.handleLabels(instructions)
variables = Assembler.handleDirectives(instructions, filename)
Assembler.updateLabels(instructions, labels)

print("\nAssembling...")
for lineno in range(len(instructions)):
    if instructions[lineno] != "":
        error = Error(
            instructions[lineno],
            lineno+1,
            filename
        )

        assembler = Assembler(instructions[lineno], labels, variables, error)
        binary = assembler.assemble()

        bin_file.write("".join(binary) + "\n")