// Tutorial from https://www.youtube.com/watch?v=qJgsuQoy9bc

#include <stdio.h>
#include <stdlib.h>

using Byte = unsigned char;
using Word = unsigned short;
using u32 = unsigned int;

struct Mem {
    static constexpr u32 MAX_MEM = 1024 * 64;
    Byte Data[MAX_MEM];

    void initialize() {
        for (u32 i = 0; i < MAX_MEM; i++) { Data[i] = 0; }
    }
};

struct CPU {
    

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

    void reset(Mem& memory) {
        PC = 0xFFFC;
        SP = 0x0100;
        C = Z = I = D = 0;
        B = V = N = 0;
        memory.initialize();
    }

    void execute(u32 cycles, Mem& memory) {

    }
};

int main() {
    Mem mem;
    CPU cpu;
    cpu.reset(mem);
    cpu.execute(2, mem);
    return 0;
}