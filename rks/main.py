import os
import sys

from error import Error
from assembler import Assembler

# Get the instructions
filename = os.path.abspath(sys.argv[-1])
file = open(filename, 'r')
bin_file = open(filename[:-4], 'w')

# Configure instructions before assembling
instructions = file.readlines()
instructions = Assembler.clean(instructions)
labels, instructions = Assembler.handleLabels(instructions)
directives = Assembler.handleDirectives(instructions, filename)
Assembler.updateLabels(instructions, labels)

# Assemble the program and write the machine code to the bin file
print("\nAssembling...")
for lineno in range(len(instructions)):
    if instructions[lineno] != "":
        error = Error(
            instructions[lineno],
            lineno+1,
            filename
        )

        assembler = Assembler(instructions[lineno], labels, directives, error)
        binary = assembler.assemble()

        bin_file.write("".join(binary) + "\n")