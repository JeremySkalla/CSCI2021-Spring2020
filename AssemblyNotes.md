# Jeremy's x86 Assembly notes

### Syntax

* Comments: One line starting with #
* Statements: One line does one thing
    * Example: movq     %rdx, %rbx | That moves rdx register to rbx
* ".globl   multstore" notifies linker of location multstore
* at some point (one or two lines down normally), "multstore:" will start its own line
* Variables: Registers and memory, sometimes named locations
* Assignments: Instructions that put bits in registers/memory
* Functions: Code locations that are labled and global
* Conditionals/Iteration: Assembly instructions that jump to code locations
* Aggregate Data: NONE, need to use stack/multiple registers
* Library System: link to other code

### Register Functions

| Movement Functions        |                                    |
|-------------------------- |------------------------------------|
| movX                      | Moves Memory                       |
| pushX, popX               | Stack Functions                    |
| **Arithmetic Functions**  |                                    |
| addX, subX                | Addition/Subtraction               |
| mulX, divX                | Multiplication/Division (Unsigned) |
| imulX, idivX              | Multiplication/Division (Signed)   |
| incX, decX                | =+1/-1                             |
| negX                      | Negate                             |
| notX                      | Complement (~A)                    |
| **Bitwise Functions**     |                                    |
| andX, orX, xorX, notX     | Bitwise Logicals                   |
| salX, shlX                | Left Shifts (Identical)            |
| sarX                      | Right Shift (Signed)               |
| shrX                      | Right Shift (Unsigned)             |
| **Conditionals**          |                                    |
| cmpX, testX               | Compare and Test                   |
| jmp                       | Unconditional Jump                 |
| je, jne                   | Jump If (Not) Equal To             |
| jl, jg                    | Jump if Less Than/Greater Than     |
| cmoveX, cmovneX           | Move if (Not) Equal To             |
| cmovlX, cmovgX            | Move If Less Than/Greater Than     |
| **Others**                |                                    |
| call, ret                 | Call, Return                       |
| Syscall                   | SEE NOTE                           |
| leaX                      | SEE NOTE                           |

NOTE: syscall - Place system call number in %rax, and then args in normal order, then then syscall

NOTE: leaX - Load Address Into (Address-Of) - Ex: leaq 8(%rdx),%rax # rax = rdx+1 = \#1032

NOTE: movX - If moving to a pointer (%rbx), pointers are always 64 bits

### Register Overview

| **Bits**  | **Suffix**    | **Naming Convention**     |
| :-------- | :------------ | :------------------------ |
| 8         | -b            | %al, %bl, %cl, etc.       |
| 16        | -w            | %ax, %bx, %cx, etc.       |
| 32        | -l            | %eax, %ebx, %ecx, etc.    |
| 64        | -q            | %rax, %rbx, %rcx, etc.    |

### Use of Each Variable

| **Use**    | **64-bit**   | **32-bit**    | **16-bit**    | **8-bit** |
| :--------- | :----------- | :------------ | :------------ | :-------- |
| Return Val | %rax         | %eax          | %ax           | %al       |
| Arg 1      | %rdi         | %edi          | %di           | %dil      |
| Arg 2      | %rsi         | %esi          | %si           | %sil      |
| Arg 3      | %rdx         | %edx          | %dx           | %dl       |
| Arg 4      | %rcx         | %ecx          | %cx           | %cl       |
| Arg 5      | %r8          | %r8d          | %r8w          | %r8b      |
| Arg 6      | %r9          | %r9d          | %r8w          | %r8b      |
| Stack Ptr  | %rsp         | %esp          | %sp           | %spl      |
| Base Ptr   | %rbp         | %ebp          | %bp           | %bpl      |

NOTE: Base Ptr might not exist, optimized out by compiler a lot of times

### Operands and Addressing Modes

| **Style**         | **Mode**      | **C-equivalent**      |
| :---------------- | :------------ | :-------------------- |
| $21/$0xD2         | Immediate     | 21/0xD2 (210)         |
| %rax              | Register      | rax                   |
| (%rax)            | Indirect      | *rax                  |
| 8(%rax)           | Displaced     | *(rax+2)              |
| (%rax, %rbx)      | Indexed       | *(rax+rbx)            |
| (%rax, %rbx, 4)   | Scaled index  | *rax[rbx] (size of 4) |
| 1024              | Absolute      | ... (Address #1024)   |

blah