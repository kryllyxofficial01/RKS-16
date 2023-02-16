# Introduction to RKS-16
RKS-16 is a virtual CPU with a 16-Bit architecture, and a custom assembly language for scripting.

## Specs:
- 16-Bit architecture
- 38 total instructions
- Memory:
    - 131.072 KB of RAM total
    - 65280 slots dedicated to main memory
    - 256 slots dedicated to stack
- Can execute up to roughly 60K instructions<sup>1</sup>
- 6 total registers
    - 4 General Purpose Registers: A, B, C, D
    - 2 System Registers: PC (Program Counter), F (Flags)

---
<p style="font-size:12px"><sup>1</sup> <i>This is relative. While most instructions only need 16 bits, some instructions like jumps require 32. So the more jumps you have, the less instructions you can have. Fortunately, the number of total instructions you can have is still large enough to where it isn't much of a problem.</i>
