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
add* <reg> <reg>   : Add two registers together
sub* <reg> <reg>   : Subtract a register from another
mul* <reg> <reg>   : Multiply two registers together
div* <reg> <reg>   : Subtract a register by another
and* <reg> <reg>   : Bitwise AND two registers
or* <reg> <reg>   : Bitwise OR two registers
not <reg>          : Bitwise NOT a register
cmp <reg> <reg>    : Performs subtraction, but only updates flags
jmp <label>        : Unconditional jump
jz <label>         : Jump if Zero Flag is 1
jo <label>         : Jump if Overflow Flag is 1
jn <label>         : Jump if Negative Flag is 1
hlt                : Halt the CPU

Argument Types:
1. Registers
    - Format is the name of the register preceded by an "@"
    - @a, @b, etc.

2. 16-Bit Immediate
    - Can be either an integer, hexadecimal, or binary.
    - If not base-10, it must be preceded by the corresponding prefix
        - 0x for hexadecimal
        - 0b for binary
    - Max value is 65535/0xFFFF/0b1111111111111111

3. Label
    - Any user defined label.
    - See "docs/Branching.md" for more details.

4. Variables
    - Any user defined variable
    - See "docs/Directives.md" for more details


*Result is stored in first specified register
```

## I/O
| Port              | RAM Address | Purpose           |
|:-----------------:|:-----------:|:-----------------:|
| Output Character  | 0xFFFF      | Print a character |
| Output Number     | 0xFFFE      | Print a number    |

For all ports, all that is needed is to just store the value at the corresponding adress. The port(s) will then update if the address is the right one.

---
## Credits
[Carlsonen](https://github.com/Carlsonen)
[Verlio-H](https://github.com/Verlio-H)
[Matthias1590](https://github.com/Matthias1590)
[Nano112](https://github.com/Nano112)
Tape#8369
