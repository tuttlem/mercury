# mercury

An x86-like virtual machine written in C++.

## Building

```bash
$ git clone git@github.com:tuttlem/mercury.git
$ cd mercury
$ cmake .
$ make
```

## Virtual Machine

The virtual machine is a stack-based machine with 32-bit registers. It has a
small instruction set and a small number of registers. The virtual machine
supports 32-bit signed integers and 32-bit floating point numbers.

### Registers

The virtual machine has 8 general purpose registers that can
be treated as integer and floating point data types.

| Register | Description | Size |
| -------- | ----------- | ---- |
| `r0`     | General purpose register | 64-bit |
| `r1`     | General purpose register |64-bit |
| `r2`     | General purpose register |64-bit |
| `r3`     | General purpose register |64-bit |
| `r4`     | General purpose register |64-bit |
| `r5`     | General purpose register |64-bit |
| `r6`     | General purpose register |64-bit |
| `r7`     | General purpose register |64-bit |

### Instruction Set

#### Data Transfer Instructions

| Instruction | Description |
|-------------|-------------|
| aaa         | ASCII Adjust After Addition |
| aad         | ASCII Adjust Register AX Before Division |
| aam         | ASCII Adjust AX Register After Multiplication |
| aas         | ASCII Adjust AL Register After Subtraction |
| arpl        | Adjust Requester Privilege Level of Selector |
| bound       | Check Array Index Against Bounds |
| cbw         | Convert Byte to Word |
| cdq         | Convert Doubleword to Quad-Word |
| clc         | Clear Carry Flag (CF) |
| cld         | Clear Direction Flag (DF) |
| cli         | Clear Interrupt Flag (IF) |
| clts        | Clear Task-Switched Flag in Control Register Zero |
| cmc         | Complement Carry Flag (CF) |
| cwd         | Convert Word to Doubleword |
| cwde        | Convert Word to Extended Doubleword |
| daa         | Decimal Adjust Register After Addition |
| das         | Decimal Adjust AL Register After Subtraction |
| dec         | Decrement by One |
| enter       | Make Stack Frame for Procedure Parameter |
| lahf        | Load Flags into AH Register |
| lds         | Load Pointer Using DS |
| les         | Load Pointer Using ES |
| lfs         | Load Pointer Using FS |
| lgs         | Load Pointer Using GS |
| lss         | Load Pointer Using SS |
| lea         | Load Effective Address |
| lsl         | Load Segment Limit |
| mov         | Move Data |
| movsb       | Move Byte |
| movsw       | Move Word |
| movsd       | Move Doubleword |
| movsx       | Move with Sign Extension |
| movzx       | Move with Zero Extension |
| push        | Push Operand onto Stack |
| pushw       | PUSH Word |
| pushd       | PUSH Double Word |
| pusha       | PUSH All Registers |
| pushad      | PUSH All Registers - 32-bit Mode |
| pushf       | PUSH FLAGS |
| pushfd      | PUSH EFLAGS |
| pop         | Pop a Word from the Stack |
| popa        | POP All Registers |
| popad       | POP All Registers - 32-bit Mode |
| popf        | POP Stack into FLAGS |
| popfd       | POP Stack into EFLAGS |
| xchg        | Exchange |
| xlat        | Translate |

#### Arithmetic and Logic Instructions

| Instruction | Description |
|-------------|-------------|
| adc         | Add Integers with Carry |
| add         | Add Integers |
| and         | Logical AND |
| bswap       | Byte swap |
| bt          | Bit Test |
| btc         | Bit Test and Complement |
| btr         | Bit Test and Reset |
| bts         | Bit Test and Set |
| cmp         | Compare |
| cmpsb       | Compare String - Byte |
| cmpsw       | Compare String - Word |
| cmpsd       | Compare String - Doubleword |
| cmpxchg     | Compare and Exchange |
| cmpxchg8b   | Compare and Exchange 8 Bytes |
| cpuid       | CPU Identification code to EAX |
| div         | Unsigned Integer Divide |
| imul        | Signed Integer Multiply |
| idiv        | Signed Divide |
| inc         | Increment by One |
| mul         | Unsigned Integer Multiply of AL, AX or EAX |
| neg         | Negate (Two's Complement) |
| not         | Negate (One's Complement) |
| or          | Logical Inclusive OR |
| sbb         | Subtract Integers with Borrow |
| test        | Test Operands |
| xor         | Exclusive-OR |

#### Control Transfer Instructions

| Instruction | Description                              |
|-------------|------------------------------------------|
| call        | Call Procedure                           |
| jmp         | Jump                                     |
| jc          | Jump if Carry (CF=1)                     |
| jcxz        | Jump if CX is Zero                       |
| je          | Jump if Equal (ZF=1)                     |
| jg          | Jump if Greater (ZF=0 & SF=OF)           |
| jge         | Jump if Greater or Equal (SF=OF)         |
| jl          | Jump if Less (SF!=OF)                    |
| jle         | Jump if Less or Equal (ZF=1 or SF!=OF)   |
| jna         | Jump if Not Above (CF=1 or ZF=1)         |
| jnae        | Jump if Not Above or Equal (CF=1)        |
| jnb         | Jump if Not Below (CF=0)                 |
| jnbe        | Jump if Not Below or Equal (CF=0 & ZF=0) |
| jnc         | Jump if Not Carry (CF=0)                 |
| jne         | Jump if Not Equal (ZF=0)                 |
| jng         | Jump if Not Greater (ZF=1 or SF!=OF)     |
| jnge        | Jump if Not Greater or Equal (ZF=1)      |
| jnl         | Jump if Not Less (SF=OF)                 |
| jnle        | Jump if Not Less or Equal (ZF=0 & SF=OF) |
| jno         | Jump if Not Overflow (OF=0)              |
| jnp         | Jump if Not Parity (PF=0)                |
| jns         | Jump if Not Sign (SF=0)                  |
| jnz         | Jump if Not Zero (ZF=0)                  |
| jo          | Jump if Overflow (OF=1)                  |
| jp          | Jump if Parity (PF=1)                    |
| jpe         | Jump if Parity Even (PF=1)               |
| jpo         | Jump if Parity Odd  (PF=0)               |
| js          | Jump if Sign (SF=1)                      |
| jz          | Jump if Zero (ZF=1)                      |
| loop        | Loop with ECX Counter                    |
| loope       | Loop with ECX Counter while Equal        |
| loopz       | Loop with ECX Counter while Zero         |
| loopne      | Loop with ECX Counter while Not Equal    |
| loopnz      | Loop with ECX Counter while Not Zero     |
| iret        | Return from Interrupt                    |
| iretd       | Return from Interrupt - 32-bit Mode      |
| hlt         | Halt                                     |
| int         | Call to Interrupt Procedure              |
| into        | Interrupt on Overflow                    |
| invd        | Invalidate data cache                    |
| invlpg      | Invalidate TBL entry                     |
| iret        | Return from Interrupt                    |
| iretd       | Return from Interrupt - 32-bit Mode      |
| rep         | Repeat String Operation Prefix           |
| repe        | Repeat String Operation Prefix           |
| repne       | Repeat String Operation Prefix           |
| repnz       | Repeat String Operation Prefix           |
| repz        | Repeat String Operation Prefix           |
| ret         | Return from Subprocedure                 |
| retf        | Return from Subprocedure                 |
| retn        | Return from Subprocedure                 |
| syscall     | System Call                              |
| sysenter    | Fast System Call                         |
| sysexit     | Fast Return from Fast System Call        |
| sysret      | Fast Return from Fast System Call        |

#### Flag Control Instructions

| Instruction | Description                                       |
|-------------|---------------------------------------------------|
| cld         | Clear Direction Flag (DF)                         |
| cli         | Clear Interrupt Flag (IF)                         |
| clts        | Clear Task-Switched Flag in Control Register Zero |
| cmc         | Complement Carry Flag (CF)                        |
| stc         | Set Carry Flag (CF)                               |
| std         | Set Direction Flag (DF)                           |
| sti         | Set Interrupt Flag (IF)                           |

#### String Instructions

| Instruction | Description                    |
|-------------|--------------------------------|
| lodsb       | Load Byte                      |
| lodsw       | Load Word                      |
| lodsd       | Load Doubleword                |
| movsb       | Move Byte                      |
| movsw       | Move Word                      |
| movsd       | Move Doubleword                |
| scasb       | Compare Byte                   |
| scasw       | Compare Word                   |
| scasd       | Compare Doubleword             |
| stosb       | Store String Data Byte         |
| stosw       | Store String Data Word         |
| stosd       | Store String Data DoubleWord   |
| cmpsb       | Compare String - Byte          |
| cmpsw       | Compare String - Word          |
| cmpsd       | Compare String - Doubleword    |
| rep         | Repeat String Operation Prefix |
| repe        | Repeat String Operation Prefix |
| repne       | Repeat String Operation Prefix |
| repnz       | Repeat String Operation Prefix |
| repz        | Repeat String Operation Prefix |

#### Floating Point Instructions

| Instruction | Description                                           |
|-------------|-------------------------------------------------------|
| f2xm1       | Compute 2x-1                                          |
| fabs        | Absolute Value                                        |
| fadd        | Add                                                   |
| faddp       | Add and Pop                                           |
| fbld        | Load Binary Coded Decimal                             |
| fbstp       | Store BCD Integer and Pop                             |
| fchs        | Change Sign                                           |
| fclex       | Clear Exceptions                                      |
| fcom        | Compare Floating Point Values                         |
| fcomp       | Compare Floating Point Values and Pop                 |
| fcompp      | Compare Floating Point Values and Pop Twice           |
| fcos        | Cosine                                                |
| fdecstp     | Decrement Stack-Top Pointer                           |
| fdiv        | Divide                                                |
| fdivp       | Divide and Pop                                        |
| fdivr       | Reverse Divide                                        |
| fdivrp      | Reverse Divide and Pop                                |
| ffree       | Free Floating-Point Register                          |
| fiadd       | Add                                                   |
| ficom       | Compare Integer                                       |
| ficomp      | Compare Integer and Pop                               |
| fidiv       | Divide                                                |
| fidivr      | Reverse Divide                                        |
| fild        | Load Integer                                          |
| fimul       | Multiply                                              |
| fincstp     | Increment Stack-Top Pointer                           |
| finit       | Initialize Floating-Point Unit                        |
| fist        | Store Integer                                         |
| fistp       | Store Integer and Pop                                 |
| fisub       | Subtract                                              |
| fisubr      | Reverse Subtract                                      |
| fld         | Load Floating Point Value                             |
| fld1        | Load Constant 1.0                                     |
| fldcw       | Load x87 FPU Control Word                             |
| fldenv      | Load x87 FPU Environment                              |
| fldl2e      | Load Constant log2e                                   |
| fldl2t      | Load Constant log210                                  |
| fldlg2      | Load Constant loge2                                   |
| fldln2      | Load Constant ln2                                     |
| fldpi       | Load Constant pi                                      |
| fldz        | Load Constant 0.0                                     |
| fmul        | Multiply                                              |
| fmulp       | Multiply and Pop                                      |
| fnclex      | Clear Exceptions                                      |
| fninit      | Initialize Floating-Point Unit                        |
| fnop        | No Operation                                          |
| fpatan      | Partial Arctangent                                    |
| fprem       | Partial Remainder                                     |
| fprem1      | Partial Remainder                                     |
| fptan       | Partial Tangent                                       |
| frndint     | Round to Integer                                      |
| frstor      | Restore x87 FPU State                                 |
| fsave       | Store x87 FPU State                                   |
| fscale      | Scale by Power of Two                                 |
| fsin        | Sine                                                  |
| fsincos     | Sine and Cosine                                       |
| fsqrt       | Square Root                                           |
| fst         | Store Floating Point Value                            |
| fstcw       | Store x87 FPU Control Word                            |
| fstenv      | Store x87 FPU Environment                             |
| fstp        | Store Floating Point Value and Pop                    |
| fstsw       | Store x87 FPU Status Word                             |
| ftst        | Test                                                  |
| fucom       | Unordered Compare Floating Point Values               |
| fucomp      | Unordered Compare Floating Point Values and Pop       |
| fucompp     | Unordered Compare Floating Point Values and Pop Twice |
| fxam        | Examine                                               |
| fxch        | Exchange Register Contents                            |
| fxrstor     | Restore x87 FPU, MMX, XMM, and MXCSR State            |
| fxsave      | Save x87 FPU, MMX Technology, and SSE State           |
| fxtract     | Extract Exponent and Significand                      |
| fyl2x       | Compute y * log2x                                     |
| fyl2xp1     | Compute y * log2(x+1)                                 |

#### System Instructions

| Instruction | Description                          |
|-------------|--------------------------------------|
| invd        | Invalidate data cache                |
| invlpg      | Invalidate TBL entry                 |
| wbinvd      | Write Back and Invalidate Data Cache |
| rdmsr       | Read from Model Specific Register    |
| wrmsr       | Write to Model Specific Register     |
| rdpmc       | Read Performance Monitor Counter     |
| rsm         | Return from System Management mode   |

#### Other Instructions

| Instruction | Description                             |
|-------------|-----------------------------------------|
| emms        | Empty MMX Technology State              |
| fnclex      | Clear Exceptions                        |
| fninit      | Initialize Floating-Point Unit          |
| fnop        | No Operation                            |
| wait        | Wait for FPU                            |
| nop         | No Operation                            |
| ud2         | Undefined Instruction (Raise Exception) |