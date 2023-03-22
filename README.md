# RKS-16

## Details
- 16-Bit Architecture
- 21 Total Instructions
- 262.144 KB Total Memory
    - 131.07 KB of RAM
    - 131.07 KB of Program Memory (ROM)
- Infinitely expandable stack (technically)
- 4 General Use 16-Bit Registers + 2 System Registers
    - A
    - B
    - C
    - D
    - F (Flags)
    - PC (Program Counter)
- 3 Flags that support all boolean operations
    - Zero
    - Overflow
    - Negative
- Memory-mapped I/O


## Instruction Set
```
nop                : No operation
ldi <reg> <imm16>  : Load a 16 bit immediate into a register
mov <reg> <reg>    : Copy the value from a register to another
swp <reg> <reg>    : Swap the values of two registers
poke <reg> <imm16> : Store a register at an address
peek <reg> <imm16> : Load a value from an address into a register
psh <reg>          : Push a register's value onto the stack
pop <reg>          : Pop the top value of the stack into a register
add <reg> <reg>    : Add two registers together
sub <reg> <reg>    : Subtract a register from another
mul <reg> <reg>    : Multiply two registers together
div <reg> <reg>    : Subtract a register by another
and <reg> <reg>    : Bitwise AND two registers
and <reg> <reg>    : Bitwise OR two registers
not <reg>          : Bitwise NOT a register
cmp <reg> <reg>    : Performs subtraction, but only updates flags
jmp <label>        : Unconditional jump
jz <label>         : Jump if Zero Flag is 1
jo <label>         : Jump if Overflow Flag is 1
jn <label>         : Jump if Negative Flag is 1
hlt                : Halt the CPU
```

*NOTE:* All ALU operations store the result in the first specified register

## I/O
| Port     | RAM Address |
|:--------:|:-----------:|
| Output   | 0xFFFF      |

---
## Credits
[@Carlsonen](https://github.com/Carlsonen)
[@Verlio-H](https://github.com/Verlio-H)
[@Matthias1590](https://github.com/Matthias1590)
Tape#8369