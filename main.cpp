// Tutorial from https://www.youtube.com/watch?v=qJgsuQoy9bc

#include <stdio.h>
#include <stdlib.h>

struct CPU {
    using Byte = unsigned char;
    using Word = unsigned short;

    Word PC;  // Program Counter
    Word SP;  // Stack Pointer

    Byte A, X, Y; // Registers

    // Status flags
    Byte C : 1;  // Carry Flag
    Byte Z : 1;  // Zero Flag
    Byte I : 1;  // Interrupt Disable
    Byte D : 1;  // Decimal Mode
    Byte B : 1;  // Break Command
    Byte V : 1;  // Overflow Flag
    Byte N : 1;  // Negative Flag

    void reset() {

    }
};

int main() {

    CPU cpu;
    cpu.reset();
    return 0;
}