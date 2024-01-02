# Cuba's Reference Manual of the 6502
I am writing this to organize all the information I find into one location I can look back on instead of flipping between 10 different books, web pages and asking chat gpt.

The website used in [the tutorial](https://www.youtube.com/watch?v=qJgsuQoy9bc) looked very useful but sadly is no longer up.  I will be copying information found from there into this document as well as from other sources which I will list.

Note: This will not be a comprehensive manual and only for personal use

Useful resources:
- [c64 wiki](https://www.c64-wiki.com/wiki/Main_Page)
- [6502.org](http://www.6502.org)

## Registers
The 6502 has only a small number of registers compared to other processor of the same era. This makes it especially challenging to program as algorithms must make efficient use of both registers and memory.

### Program Counter
The program counter is a 16 bit register which points to the next instruction to be executed.  The value of program counter is modified automatically as instructions are executed.

The value of the program counter can be modified by executing a jump, a relative branch or a subroutine call to another memory address by returning from a subroutine or interrupt.

### Stack Pointer
The processor supports a 256 byte stack located between $0100 and $01FF.  The stack pointer is an 8 bit reigster and holds the low 8 bits of the next free location on the stack.  The location of the stack is fixed and cannot be moved.

Pushing bytes to the stack causes the stack pointer to be decremented.  Conversely pulling bytes causes it to be incremented.

The CPU does not detect if the stack is overflowed by excessive pushing or pulling operations and will most likely result in the program crashing.

### Accumulator
The 8 bit accumulator is used with(?) all arithmetic and logical operations (with the exception of increments and decrements).  The contents of the accumulator can be stored and retrieved either from memory or the stack.

Most complex operations will need to use the accumulator for arithmetic and efficient optimissation of its use is a key feature of time critical routines.

### Index Register X
The 8 bit index registeri s most commmonly used to hold counters or offsets for accessing memory.  The value of the X register can be loaded and saved in memory, compared with values held in memory or incremented and decremented.

The X register has one special function.  It can be used to get  a copy of the stack pointer or change its value.

### Index Register Y
The Y register is similar to the X register in that it is available for holding counter or offsets memory access and supports the same set of memory load, save and compare operations as well as increments and decrements.  It has no special functions.

### Processor Status
As instructions are executed a set of processor flags are set or clear to record the results of the operation.  This flags and some additional control flags are held in a special register.  Each flag has a single bit within the register.

Instructions exist to test the values of the various bits, to set or clear some of them and to push or pull the entire set to or from the stack.

- Carry Flag
The carry flag is set if the last operation caused an overflow from bit 7 of the result orr an unferflow from bit 0.  This condition is set during arithmetic, comparison and during logical shifts.  It can be explicitly set using the 'Set Carry Flag' ([SEC]()) instruction and cleared with the 'Clear Carry Flag' ([CLC]()).

- Zero Flag
The zero flag is set if the result of the last operation was zero.

- Interrupt Disable
The interrupt disable flag is set if the program has executed a 'Set Interrupt Disable' ([SEI]()) instruction.  While this flag is set the processor will not respond to interrrupts from devices until it is cleared by a 'Clear Interrupt Disable' ([CLI]()) instruction. 

- Decimal Mode
While the decimal mode flag is set the processor will obey the rrules of Binary Coded Decmial (BCD) arithmetic during addition and subtraction.  The flag can be explicitly set using 'Set Decimal Flag ([SED]()) and cleared with 'Clear Decimal Flag' ([CLD]()).

- Break Command
The break command bit is set when a [BRK]() instruction has been executed and an interrupt has been generated to process it.

- Overflow Flag
The overflow flag is set during arithmetic operations if the result has yielded an invalid 2's compliment reuslt (e.g. adding two positive numbers and ending up with a negative result: 64 + 64 => -128).  It is determined by looking at the carry between bits 6 and 7 and between bit 7 and the carry flag.

- Negative Flag
The negative flag is set if the result of the last operation had bit 7 set to a one.

## The Instruction Set
The 6502 has a relatively basic set of instructions, many having similar functions (e.g. memory access, arithmetic, etc.).  The following sections list the complete set of 56 instructions in functional groups.

### Load/Store Operations
These instructions transfer a single byte between memory and one of the registers.  Load operations set the negative ([N]()) and zero ([Z]()) flags depending on the value of transferred.  Store operations do not affect the flag settings.

| Instruction | Name | Flag Affected |
| --- | --- | --- |
| [LDA]() | Load Accumulator | [N, Z]() |
| [LDX]() | Load X Register | [N, Z]() |
| [LDY]() | Load Y Register | [N, Z]() |
| [STA]() | Store Accumulator |  |
| [STX]() | Store X Register |  |
| [STY]() | Store Y Register |  |

### Register Transfers
The contents of the X and Y registers can be moved to or from the accumulator, setting the negative ([N]()) and zero ([Z]()) flags as appropriate.

| Instruction | Name | Flag Affected |
| --- | --- | --- |
| [TAX]() | Transfer accumulator to X | [N, Z]() |
| [TAY]() | Transfer accumulator to Y | [N, Z]() |
| [TXA]() | Transfer X to accumulator | [N, Z]() |
| [TYA]() | Transfer Y to accumulator | [N, Z]() |

### Stack Operations
The 6502 microprocessor supports a 256 byte stack fixed between memory locations $0100 and $01FF.  A special 8-bit register, S, is used to keep track of the next free byte of stack space.  Pushing a byte on ot the stack causes the value to be stored at the current free location (e.g. $0100, S) and then the stack pointer is post decremented. Pull operations reverse this procedure.

The stack register can only be accessed by transferring its value to or from the X register.  Its value is automatically modified by pull/push instructions, subroutine calls and returns, interrupts and returns from interrupts.

| Instruction | Name | Flag Affected |
| --- | --- | --- |
| [TSX]() | Transfer stack pointer to X | [N, Z]() |