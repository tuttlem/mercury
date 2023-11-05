# Instructions

The instruction layout is as follows.

```
[ -- 16 bits --][ -- 16 bits --][64 bits][64 bits][64 bits]
[  instruction ][  addressing  ][operand][operand][operand]
```

The instruction itself dictates the number of operands that are required. So
these are optional parts of the layout.

## Addressing Modes

There are a number of addressing modes that are available on the cpu.
These align pretty closely to the x86 addressing modes.

The layout for addressing is covered by a full 16-bits. Only 9 bits are
currently used. The remaining 7 bits are reserved for future use.

```
[ -- 7 bits -- ][-- 3 bits --][-- 3 bits --][-- 3 bits --]
[    unused    ][ operand 3  ][ operand 2  ][ operand 1  ]
16 . . . . . . 9 . . . . . . 6 . . . . . . 3 . . . . . . 0
```
Addressing modes are encoded into these three bits and instruct
the cpu how to interpret the data that's found in the operand 64-bit
chunks that follow.

The following addressing modes are available.

| Addressing Mode | Value | Description                                               | Example |
|-----------------|-------|-----------------------------------------------------------|---------|
| immediate       | 0x00  | The operand is a literal value                            | `0x01` |
| direct          | 0x01  | The operand is a literal address                          | `[0x01]` |
| register_direct | 0x02  | The operand is a register holding a literal value         | `b` |
| register_indirect | 0x03 | The operand is a register holding an address              | `[b]` |
| indexed         | 0x04  | The operand is an index register                          | `[x]` |
| based_indexed   | 0x05  | The operand is the index regisrter and displacement value | `0x100[b]` |


## Instruction Set

The first 16-bits of the instruction layout is the instruction itself. This is just
a lookup into the instruction table.

### Data Transfer Instructions

| Instruction | Description | Implemented |
|-------------|-------------|------------|
| aaa         | ASCII Adjust After Addition | No         |
| aad         | ASCII Adjust Register AX Before Division | No         |
| aam         | ASCII Adjust AX Register After Multiplication | No         |
| aas         | ASCII Adjust AL Register After Subtraction | No         |
| arpl        | Adjust Requester Privilege Level of Selector | No         |
| bound       | Check Array Index Against Bounds | No         |
| cbw         | Convert Byte to Word | No         |
| cdq         | Convert Doubleword to Quad-Word | No         |
| clc         | Clear Carry Flag (CF) | No         |
| cld         | Clear Direction Flag (DF) | No         |
| cli         | Clear Interrupt Flag (IF) | No         |
| clts        | Clear Task-Switched Flag in Control Register Zero | No         |
| cmc         | Complement Carry Flag (CF) | No         |
| cwd         | Convert Word to Doubleword | No         |
| cwde        | Convert Word to Extended Doubleword | No         |
| daa         | Decimal Adjust Register After Addition | No         |
| das         | Decimal Adjust AL Register After Subtraction | No         |
| enter       | Make Stack Frame for Procedure Parameter | No         |
| lahf        | Load Flags into AH Register | No         |
| lds         | Load Pointer Using DS | No         |
| les         | Load Pointer Using ES | No         |
| lfs         | Load Pointer Using FS | No         |
| lgs         | Load Pointer Using GS | No         |
| lss         | Load Pointer Using SS | No         |
| lea         | Load Effective Address | No         |
| lsl         | Load Segment Limit | No         |
| mov         | Move Data | No         |
| movsb       | Move Byte | No         |
| movsw       | Move Word | No         |
| movsd       | Move Doubleword | No         |
| movsx       | Move with Sign Extension | No         |
| movzx       | Move with Zero Extension | No         |
| push        | Push Operand onto Stack | No         |
| pushw       | PUSH Word | No         |
| pushd       | PUSH Double Word | No         |
| pusha       | PUSH All Registers | No         |
| pushad      | PUSH All Registers - 32-bit Mode | No         |
| pushf       | PUSH FLAGS | No         |
| pushfd      | PUSH EFLAGS | No         |
| pop         | Pop a Word from the Stack | No         |
| popa        | POP All Registers | No         |
| popad       | POP All Registers - 32-bit Mode | No         |
| popf        | POP Stack into FLAGS | No         |
| popfd       | POP Stack into EFLAGS | No         |
| xchg        | Exchange | No         |
| xlat        | Translate | No         |

### Arithmetic and Logic Instructions

| Instruction | Description                                | Implemented |
|-------------|--------------------------------------------|-------------|
| adc         | Add Integers with Carry                    | Yes         |
| add         | Add Integers                               | Yes         |
| and         | Logical AND                                | Yes         |
| bswap       | Byte swap                                  | No          |
| bt          | Bit Test                                   | No          |
| btc         | Bit Test and Complement                    | No          |
| btr         | Bit Test and Reset                         | No          |
| bts         | Bit Test and Set                           | No          |
| cmp         | Compare                                    | Yes         |
| cmpsb       | Compare String - Byte                      | No          |
| cmpsw       | Compare String - Word                      | No          |
| cmpsd       | Compare String - Doubleword                | No          |
| cmpxchg     | Compare and Exchange                       | No          |
| cmpxchg8b   | Compare and Exchange 8 Bytes               | No          |
| dec         | Decrement by One                           | No          |
| div         | Unsigned Integer Divide                    | No          |
| imul        | Signed Integer Multiply                    | No          |
| idiv        | Signed Divide                              | No          |
| inc         | Increment by One                           | No          |
| mul         | Unsigned Integer Multiply of AL, AX or EAX | No          |
| neg         | Negate (Two's Complement)                  | No          |
| not         | Negate (One's Complement)                  | No          |
| or          | Logical Inclusive OR                       | Yes         |
| rcl         | Rotate Left with Carry                     | Yes         |
| rcr         | Rotate Right with Carry                    | Yes         |
| rol         | Rotate Left                                | Yes         |
| ror         | Rotate Right                               | Yes         |
| sal         | Shift Arithmetic Left                      | Yes         |
| sar         | Shift Arithmetic Right                     | Yes         |
| sbb         | Subtract Integers with Borrow              | No          |
| shl         | Shift bits left                            | Yes         |
| shr         | Shift bits right                           | Yes         |
| sub         | Subtract integers                          | Yes         |
| test        | Test Operands                              | No          |
| xor         | Exclusive-OR                               | Yes         |

### Control Transfer Instructions

| Instruction | Description                              | Implemented |
|-------------|------------------------------------------|-------------|
| call        | Call Procedure                           | No          |
| jmp         | Jump                                     | No          |
| jc          | Jump if Carry (CF=1)                     | No          |
| jcxz        | Jump if CX is Zero                       | No          |
| je          | Jump if Equal (ZF=1)                     | No          |
| jg          | Jump if Greater (ZF=0 & SF=OF)           | No          |
| jge         | Jump if Greater or Equal (SF=OF)         | No          |
| jl          | Jump if Less (SF!=OF)                    | No          |
| jle         | Jump if Less or Equal (ZF=1 or SF!=OF)   | No          |
| jna         | Jump if Not Above (CF=1 or ZF=1)         | No          |
| jnae        | Jump if Not Above or Equal (CF=1)        | No          |
| jnb         | Jump if Not Below (CF=0)                 | No          |
| jnbe        | Jump if Not Below or Equal (CF=0 & ZF=0) | No          |
| jnc         | Jump if Not Carry (CF=0)                 | No          |
| jne         | Jump if Not Equal (ZF=0)                 | No          |
| jng         | Jump if Not Greater (ZF=1 or SF!=OF)     | No          |
| jnge        | Jump if Not Greater or Equal (ZF=1)      | No          |
| jnl         | Jump if Not Less (SF=OF)                 | No          |
| jnle        | Jump if Not Less or Equal (ZF=0 & SF=OF) | No          |
| jno         | Jump if Not Overflow (OF=0)              | No          |
| jnp         | Jump if Not Parity (PF=0)                | No          |
| jns         | Jump if Not Sign (SF=0)                  | No          |
| jnz         | Jump if Not Zero (ZF=0)                  | No          |
| jo          | Jump if Overflow (OF=1)                  | No          |
| jp          | Jump if Parity (PF=1)                    | No          |
| jpe         | Jump if Parity Even (PF=1)               | No          |
| jpo         | Jump if Parity Odd  (PF=0)               | No          |
| js          | Jump if Sign (SF=1)                      | No          |
| jz          | Jump if Zero (ZF=1)                      | No          |
| loop        | Loop with ECX Counter                    | No          |
| loope       | Loop with ECX Counter while Equal        | No          |
| loopz       | Loop with ECX Counter while Zero         | No          |
| loopne      | Loop with ECX Counter while Not Equal    | No          |
| loopnz      | Loop with ECX Counter while Not Zero     | No          |
| iret        | Return from Interrupt                    | No          |
| iretd       | Return from Interrupt - 32-bit Mode      | No          |
| hlt         | Halt                                     | Yes         |
| int         | Call to Interrupt Procedure              | No          |
| into        | Interrupt on Overflow                    | No          |
| invd        | Invalidate data cache                    | No          |
| invlpg      | Invalidate TBL entry                     | No          |
| iret        | Return from Interrupt                    | No          |
| iretd       | Return from Interrupt - 32-bit Mode      | No          |
| rep         | Repeat String Operation Prefix           | No          |
| repe        | Repeat String Operation Prefix           | No          |
| repne       | Repeat String Operation Prefix           | No          |
| repnz       | Repeat String Operation Prefix           | No          |
| repz        | Repeat String Operation Prefix           | No          |
| ret         | Return from Subprocedure                 | No          |
| retf        | Return from Subprocedure                 | No          |
| retn        | Return from Subprocedure                 | No          |
| syscall     | System Call                              | No          |
| sysenter    | Fast System Call                         | No          |
| sysexit     | Fast Return from Fast System Call        | No          |
| sysret      | Fast Return from Fast System Call        | No          |

### Flag Control Instructions

| Instruction | Description                                       | Implemented |
|-------------|---------------------------------------------------|-------------|
| cld         | Clear Direction Flag (DF)                         | No          |
| cli         | Clear Interrupt Flag (IF)                         | No          |
| clts        | Clear Task-Switched Flag in Control Register Zero | No          | 
| cmc         | Complement Carry Flag (CF)                        | No          |
| stc         | Set Carry Flag (CF)                               | No          |
| std         | Set Direction Flag (DF)                           | No          |
| sti         | Set Interrupt Flag (IF)                           | No          |

### String Instructions

| Instruction | Description                    | Implemented |
|-------------|--------------------------------|-------------|
| lodsb       | Load Byte                      | No          |
| lodsw       | Load Word                      | No          |
| lodsd       | Load Doubleword                | No          |
| movsb       | Move Byte                      | No          |
| movsw       | Move Word                      | No          |
| movsd       | Move Doubleword                | No          |
| scasb       | Compare Byte                   | No          |
| scasw       | Compare Word                   | No          |
| scasd       | Compare Doubleword             | No          |
| stosb       | Store String Data Byte         | No          |
| stosw       | Store String Data Word         | No          |
| stosd       | Store String Data DoubleWord   | No          |
| cmpsb       | Compare String - Byte          | No          |
| cmpsw       | Compare String - Word          | No          |
| cmpsd       | Compare String - Doubleword    | No          |
| rep         | Repeat String Operation Prefix | No          |
| repe        | Repeat String Operation Prefix | No          |
| repne       | Repeat String Operation Prefix | No          |
| repnz       | Repeat String Operation Prefix | No          |
| repz        | Repeat String Operation Prefix | No          |

### Floating Point Instructions

| Instruction | Description                                           | Implemented |
|-------------|-------------------------------------------------------|-|
| f2xm1       | Compute 2x-1                                          | No          |
| fabs        | Absolute Value                                        | No          |
| fadd        | Add                                                   | No          |
| faddp       | Add and Pop                                           | No          |
| fbld        | Load Binary Coded Decimal                             | No          |
| fbstp       | Store BCD Integer and Pop                             | No          |
| fchs        | Change Sign                                           | No          |
| fclex       | Clear Exceptions                                      | No          |
| fcom        | Compare Floating Point Values                         | No          |
| fcomp       | Compare Floating Point Values and Pop                 | No          |
| fcompp      | Compare Floating Point Values and Pop Twice           | No          |
| fcos        | Cosine                                                | No          |
| fdecstp     | Decrement Stack-Top Pointer                           | No          |
| fdiv        | Divide                                                | No          |
| fdivp       | Divide and Pop                                        | No          |
| fdivr       | Reverse Divide                                        | No          |
| fdivrp      | Reverse Divide and Pop                                | No          |
| ffree       | Free Floating-Point Register                          | No          |
| fiadd       | Add                                                   | No          |
| ficom       | Compare Integer                                       | No          |
| ficomp      | Compare Integer and Pop                               | No          |
| fidiv       | Divide                                                | No          |
| fidivr      | Reverse Divide                                        | No          |
| fild        | Load Integer                                          | No          |
| fimul       | Multiply                                              | No          |
| fincstp     | Increment Stack-Top Pointer                           | No          |
| finit       | Initialize Floating-Point Unit                        | No          |
| fist        | Store Integer                                         | No          |
| fistp       | Store Integer and Pop                                 | No          |
| fisub       | Subtract                                              | No          |
| fisubr      | Reverse Subtract                                      | No          |
| fld         | Load Floating Point Value                             | No          |
| fld1        | Load Constant 1.0                                     | No          |
| fldcw       | Load x87 FPU Control Word                             | No          |
| fldenv      | Load x87 FPU Environment                              | No          |
| fldl2e      | Load Constant log2e                                   | No          |
| fldl2t      | Load Constant log210                                  | No          |
| fldlg2      | Load Constant loge2                                   | No          |
| fldln2      | Load Constant ln2                                     | No          |
| fldpi       | Load Constant pi                                      | No          |
| fldz        | Load Constant 0.0                                     | No          |
| fmul        | Multiply                                              | No          |
| fmulp       | Multiply and Pop                                      | No          |
| fnclex      | Clear Exceptions                                      | No          |
| fninit      | Initialize Floating-Point Unit                        | No          |
| fnop        | No Operation                                          | No          |
| fpatan      | Partial Arctangent                                    | No          |
| fprem       | Partial Remainder                                     | No          |
| fprem1      | Partial Remainder                                     | No          |
| fptan       | Partial Tangent                                       | No          |
| frndint     | Round to Integer                                      | No          |
| frstor      | Restore x87 FPU State                                 | No          |
| fsave       | Store x87 FPU State                                   | No          |
| fscale      | Scale by Power of Two                                 | No          |
| fsin        | Sine                                                  | No          |
| fsincos     | Sine and Cosine                                       | No          |
| fsqrt       | Square Root                                           | No          |
| fst         | Store Floating Point Value                            | No          |
| fstcw       | Store x87 FPU Control Word                            | No          |
| fstenv      | Store x87 FPU Environment                             | No          |
| fstp        | Store Floating Point Value and Pop                    | No          |
| fstsw       | Store x87 FPU Status Word                             | No          |
| ftst        | Test                                                  | No          |
| fucom       | Unordered Compare Floating Point Values               | No          |
| fucomp      | Unordered Compare Floating Point Values and Pop       | No          |
| fucompp     | Unordered Compare Floating Point Values and Pop Twice | No          |
| fxam        | Examine                                               | No          |
| fxch        | Exchange Register Contents                            | No          |
| fxrstor     | Restore x87 FPU, MMX, XMM, and MXCSR State            | No          |
| fxsave      | Save x87 FPU, MMX Technology, and SSE State           | No          |
| fxtract     | Extract Exponent and Significand                      | No          |
| fyl2x       | Compute y * log2x                                     | No          |
| fyl2xp1     | Compute y * log2(x+1)                                 | No          |

### System Instructions

| Instruction | Description                          | Implemented |
|-------------|--------------------------------------|-------------|
| cpuid       | CPU Identification code to EAX       | No          |
| invd        | Invalidate data cache                | No          |
| invlpg      | Invalidate TBL entry                 | No          |
| wbinvd      | Write Back and Invalidate Data Cache | No          |
| rdmsr       | Read from Model Specific Register    | No          |
| wrmsr       | Write to Model Specific Register     | No          |
| rdpmc       | Read Performance Monitor Counter     | No          |
| rsm         | Return from System Management mode   | No          |

### Other Instructions

| Instruction | Description                             | Implemented |
|-------------|-----------------------------------------|-------------|
| emms        | Empty MMX Technology State              | No          |
| fnclex      | Clear Exceptions                        | No          |
| fninit      | Initialize Floating-Point Unit          | No          |
| fnop        | No Operation                            | No          |
| wait        | Wait for FPU                            | No          |
| nop         | No Operation                            | Yes         |
| ud2         | Undefined Instruction (Raise Exception) | No          |