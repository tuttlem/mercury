//
// Created by michael on 5/11/23.
//

#ifndef __mercury_vm_opcode_h__
#define __mercury_vm_opcode_h__

#define opc0(op)                (((uint32_t)op) << 16 | 0)
#define opc1(op, p1)            (((uint32_t)op) << 16 | (p1))
#define opc2(op, p1, p2)        (((uint32_t)op) << 16 | p1 | p2 << 3)
#define opc3(op, p1, p2, p3)    (((uint32_t)op) << 16 | p1 | p2 << 3 | p3 << 6)

namespace mercury {

    /**
     * @brief Addressing modes
     */
    enum addressing {
        none = 0,

        /**
         * @brief Immediate addressing
         * @details The operand is a literal value: 0x01
         */
        immediate,

        /**
         * @brief Direct addressing
         * @details The operand is a literal address: [0x01]
         */
        direct,

        /**
         * @brief Register direct addressing
         * @details The operand is the register holding a literal value: b
         */
        register_direct,

        /**
         * @brief Register indirect addressing
         * @details The operand is the register holding an address to the value: [b]
         */
        register_indirect,

        /**
         * @brief Indexed addressing
         * @details The operand is and index register: [x]
         */
        indexed,

        /**
         * @brief Register relative addressing
         * @details The operand is the register and displacement value: 0x100[b]
         */
        //register_relative,

        /**
         * @brief Indexed relative addressing
         * @details The operand is the index register and displacement value: [b][x]
         */
        based_indexed,

        /**
         * @brief Relative based indexed addressing
         * @details The operand is the index register and displacement value: 0x100[b][x]
         */
        //relative_based_indexed,
    };

    /**
     * @brief Opcodes
     */
    enum opcode {
        _aaa,	        /* ASCII Adjust After Addition */
        _aad,	        /* ASCII Adjust Register AX Before Division */
        _aam,	        /* ASCII Adjust AX Register After Multiplication */
        _aas,	        /* ASCII Adjust AL Register After Substraction */
        _adc,	        /* Add Integers with Carry */
        _add,	        /* Add Integers */
        _and,	        /* Logical AND */
        _arpl,	        /* Adjust Requester Privilege Level of Selector */
        _bound,	        /* Check Array Index Against Bounds */
        _bsf,	        /* Bit Scan Forward */
        _bsr,	        /* Bit Scan Reverse */
        _bswap,	        /* Byte swap */
        _bt,	        /* Bit Test */
        _btc,	        /* Bit Test and Complement */
        _btr,	        /* Bit Test and Reset */
        _bts,	        /* Bit Test and Set */
        _call,	        /* Call Procedure */
        _cbw,	        /* Convert Byte to Word */
        _cdq,	        /* Convert Doubleword to Quad-Word */
        _clc,	        /* Clear Carry Flag (CF) */
        _cld,	        /* Clear Direction Flag (DF) */
        _cli,	        /* Clear Interrupt Flag (IF) */
        _clts,	        /* Clear Task-Switched Flag in Control Register Zero */
        _cmc,	        /* Complementer Carry Flag (CF) */
        _cmovcc,	    /* Conditional Move */
        _cmp,	        /* Compare */
        _cmpsb,	        /* Compare String - Byte */
        _cmpsw,	        /* Compare String - Word */
        _cmpsd,	        /* Compare String - Doubleword */
        _cmpxchg,	    /* Compare and Exchange */
        _cmpxchg8b,	    /* Compare and Exchange 8 Bytes */
        _cpuid, 	    /* CPU Identification code to EAX */
        _cwd,	        /* Convert Word to Doubleword */
        _cwde,	        /* Convert Word to Extended Doubleword */
        _daa,	        /* Decimal Adjust Register After Addition */
        _das,	        /* Decimal Adjust AL Register After Substraction */
        _dec,	        /* Decrement by One */
        _div,	        /* Unsigned Integer Divide */
        _emms,	        /* Empty MMX Technology State */
        _enter,	        /* Make Stack Frame for Procedure Parameter */
        _f2xm1,	        /* Compute 2x-1 */
        _fabs,	        /* Absolute Value */
        _fadd,	        /* Add */
        _faddp,	        /* Add and Pop */
        _fbld,	        /* Load Binary Coded Decimal */
        _fbstp,	        /* Store BCD Integer and Pop */
        _fchs,	        /* Change Sign */
        _fclex,	        /* Clear Exceptions */
        _fcmovcc,	    /* Floating-Point Conditional Move */
        _fcom,	        /* Compare Floating Point Values */
        _fcomp,	        /* Compare Floating Point Values and Pop */
        _fcompp,	    /* Compare Floating Point Values and Pop Twice */
        _fcos,	        /* Cosine */
        _fdecstp,	    /* Decrement Stack-Top Pointer */
        _fdiv,	        /* Divide */
        _fdivp,	        /* Divide and Pop */
        _fdivr,	        /* Reverse Divide */
        _fdivrp,	    /* Reverse Divide and Pop */
        _ffree,	        /* Free Floating-Point Register */
        _fiadd,	        /* Add */
        _ficom,	        /* Compare Integer */
        _ficomp,	    /* Compare Integer and Pop */
        _fidiv,	        /* Divide */
        _fidivr,	    /* Reverse Divide */
        _fild,	        /* Load Integer */
        _fimul,	        /* Multiply */
        _fincstp,	    /* Increment Stack-Top Pointer */
        _finit,	        /* Initialize Floating-Point Unit */
        _fist,	        /* Store Integer */
        _fistp,	        /* Store Integer and Pop */
        _fisub,	        /* Subtract */
        _fisubr,	    /* Reverse Subtract */
        _fld,	        /* Load Floating Point Value */
        _fld1,	        /* Load Constant 1.0 */
        _fldcw,	        /* Load x87 FPU Control Word */
        _fldenv,	    /* Load x87 FPU Environment */
        _fldl2e,	    /* Load Constant log2e */
        _fldl2t,	    /* Load Constant log210 */
        _fldlg2,	    /* Load Constant loge2 */
        _fldln2,	    /* Load Constant ln2 */
        _fldpi,	        /* Load Constant pi */
        _fldz,	        /* Load Constant 0.0 */
        _fmul,	        /* Multiply */
        _fmulp,	        /* Multiply and Pop */
        _fnclex,	    /* Clear Exceptions */
        _fninit,	    /* Initialize Floating-Point Unit */
        _fnop,	        /* No Operation */
        _fpatan,	    /* Partial Arctangent */
        _fprem,	        /* Partial Remainder */
        _fprem1,	    /* Partial Remainder */
        _fptan,	        /* Partial Tangent */
        _frndint,	    /* Round to Integer */
        _frstor,	    /* Restore x87 FPU State */
        _fsave,	        /* Store x87 FPU State */
        _fscale,	    /* Scale by Power of Two */
        _fsin,	        /* Sine */
        _fsincos,	    /* Sine and Cosine */
        _fsqrt,	        /* Square Root */
        _fst,	        /* Store Floating Point Value */
        _fstcw,	        /* Store x87 FPU Control Word */
        _fstenv,	    /* Store x87 FPU Environment */
        _fstp,	        /* Store Floating Point Value and Pop */
        _fstsw,	        /* Store x87 FPU Status Word */
        _fsub,	        /* Subtract */
        _fsubp,	        /* Subtract and Pop */
        _fsubr,	        /* Reverse Subtract */
        _fsubrp,	    /* Reverse Subtract and Pop */
        _ftst,	        /* Test */
        _fucom,	        /* Unordered Compare Floating Point Values */
        _fucomp,	    /* Unordered Compare Floating Point Values and Pop */
        _fucompp,	    /* Unordered Compare Floating Point Values and Pop Twice */
        _fxam,	        /* Examine */
        _fxch,	        /* Exchange Register Contents */
        _fxrstor,	    /* Restore x87 FPU, MMX, XMM, and MXCSR State */
        _fxsave,	    /* Save x87 FPU, MMX Technology, and SSE State */
        _fxtract,	    /* Extract Exponent and Significand */
        _fyl2x,	        /* Compute y * log2x */
        _fyl2xp1,	    /* Compute y * log2(x+1) */
        _hlt,	        /* Halt */
        _idiv,	        /* Signed Divide */
        _imul,	        /* Signed Integer Multiply */
        _in,	        /* Input from Port */
        _inc,	        /* Increment by 1 */
        _insb,	        /* Input Byte */
        _insw,	        /* Input Word */
        _insd,	        /* Input DoubleWord */
        _int,	        /* Call to Interrupt Procedure */
        _into,	        /* Interrupt on Overflow */
        _invd,	        /* Invalidate data cache */
        _invlpg,	    /* Invalidate TBL entry */
        _iret,	        /* Return from Interrupt */
        _iretd,	        /* Return from Interrupt - 32-bit Mode */
        _ja,	        /* Jump if Above (CF=0 & ZF=0) */
        _jae,	        /* Jump if Above or Equal (CF=0) */
        _jb,	        /* Jump if Below (CF=1) */
        _jbe,	        /* Jump if Below or Equal (CF=1 | ZF=1) */
        _jc,	        /* Jump if Carry (CF=1) */
        _jcxz,	        /* Jump if CX is Zero */
        _je,	        /* Jump if Equal (ZF=1) */
        _jecxz,	        /* Jump if ECX is Zero */
        _jg,	        /* Jump if Greater (ZF=0 & SF=OF) */
        _jge,	        /* Jump if Greater or Equal (SF=OF) */
        _jl,	        /* Jump if Less (SF!=OF) */
        _jle,	        /* Jump if Less or Equal (ZF=1 | SF!=OF) */
        _jna,	        /* Jump if Not Above (CF=1 | ZF=1) */
        _jnae,	        /* Jump if Not Above or Equal (CF=1) */
        _jnb,	        /* Jump if Not Below (CF=0) */
        _jnbe,	        /* Jump if Not Below or Equal (CF=0 & ZF=0) */
        _jnc,	        /* Jump if Not Carry (CF=0) */
        _jne,	        /* Jump if Not Equal (ZF=0) */
        _jng,	        /* Jump if Not Greater (ZF=1 | SF!=OF) */
        _jnge,	        /* Jump if Not Greater or Equal (ZF=1) */
        _jnl,	        /* Jump if Not Less (SF=OF) */
        _jnle,	        /* Jump if Not Less or Equal (ZF=0 & SF=OF) */
        _jno,	        /* Jump if Not Overflow (OF=0) */
        _jnp,	        /* Jump if Not Parity (PF=0) */
        _jns,	        /* Jump if Not Sign (SF=0) */
        _jnz,	        /* Jump if Not Zero (ZF=0) */
        _jo,	        /* Jump if Overflow (OF=1) */
        _jp,	        /* Jump if Parity (PF=1) */
        _jpe,	        /* Jump if Parity Even (PF=1) */
        _jpo,	        /* Jump if Parity Odd  (PF=0) */
        _js,	        /* Jump if Sign (SF=1) */
        _jz,	        /* Jump if Zero (ZF=1) */
        _lahf,	        /* Load Flags into AH Register */
        _lar,	        /* Load Access Rights Byte */
        _lds,	        /* Load Pointer Using DS */
        _les,	        /* Load Pointer Using ES */
        _lfs,	        /* Load Pointer Using FS */
        _lgs,	        /* Load Pointer Using GS */
        _lss,	        /* Load Pointer Using SS */
        _lea,	        /* Load Effective Address */
        _leave,	        /* High Level Procedure Exit */
        _lgdt,	        /* Load Global Descriptor Table */
        _lidt,	        /* Load Interrupt Descriptor Table */
        _lldt,	        /* Load Local Descriptor Table */
        _lmsw,	        /* Load Machine Status Word */
        _lock,	        /* Assert Lock# Signal Prefix */
        _lodsb,	        /* Load Byte */
        _lodsw,	        /* Load Word */
        _lodsd,	        /* Load Doubleword */
        _loop,	        /* Loop with ECX Counter */
        _loope,	        /* Loop with ECX Counter while Equal */
        _loopz,	        /* Loop with ECX Counter while Zero */
        _loopne,	    /* Loop with ECX Counter while Not Equal */
        _loopnz,	    /* Loop with ECX Counter while Not Zero */
        _lsl,	        /* Load Segment Limit */
        _ltr,	        /* Load Task Register */
        _mov,	        /* Move Data */
        _movsb,	        /* Move Byte */
        _movsw,	        /* Move Word */
        _movsd,	        /* Move Doubleword */
        _movsx,	        /* Move with Sign Extension */
        _movzx,	        /* Move with Zero Extension */
        _mul,	        /* Unsigned Integer Multiply of AL, AX or EAX */
        _neg,	        /* Negate(Two's Complement) */
        _nop,	        /* No Operation */
        _not,	        /* Negate(One's Complement) */
        _or,	        /* Logical Inclusive OR */
        _out,	        /* Output To Port */
        _outsb,	        /* Output Byte */
        _outsw,	        /* Output Word */
        _outsd,	        /* Output Doubleword */
        _pop,	        /* Pop a Word from the Stack */
        _popa,	        /* POP All Registers */
        _popad,	        /* POP All Registers - 32-bit Mode */
        _popf,	        /* POP Stack into FLAGS */
        _popfd,	        /* POP Stack into EFLAGS */
        _push,	        /* Push Operand onto Stack */
        _pushw,	        /* PUSH Word */
        _pushd,	        /* PUSH Double Word */
        _pusha,	        /* PUSH All Registers */
        _pushad,	    /* PUSH All Registers - 32-bit Mode */
        _pushf,	        /* PUSH FLAGS */
        _pushfd,	    /* PUSH EFLAGS */
        _rcl,	        /* Rotate Left through Carry - Uses CF for Extension */
        _rcr,	        /* Rotate Right through Carry - Uses CF for Extension */
        _rdmsr,	        /* Read from Model Specific Register */
        _rep,	        /* Repeat String Operation Prefix */
        _repe,	        /* Repeat String Operation Prefix */
        _repne,	        /* Repeat String Operation Prefix */
        _repnz,	        /* Repeat String Operation Prefix */
        _repz,	        /* Repeat String Operation Prefix */
        _ret,	        /* Return from subprocedure */
        _retf,	        /* Return from subprocedure */
        _retn,	        /* Return from subprocedure */
        _rdpmc,	        /* Read Performance Monitor Counter */
        _rol,	        /* Rotate Left through Carry - Wrap bits around */
        _ror,	        /* Rotate Right through Carry - Wrap bits around */
        _rsm,	        /* Return from System Management mode */
        _salc,	        /* Set AL on Carry */
        _sahf,	        /* Load Flags into AH Register */
        _sal,	        /* Shift Arithmetic Left */
        _sar,	        /* Shift Arithmetic Right */
        _setcc,	        /* Set Byte on Condition Code */
        _shl,	        /* Shift Logic Left */
        _shr,	        /* Shift Logic Right */
        _sbb,	        /* Substract Integers with Borrow */
        _scasb,	        /* Compare Byte */
        _scasw,	        /* Compare Word */
        _scasd,	        /* Compare Doubleword */
        _sgdt,	        /* Store Global Descriptor Table */
        _shld,	        /* Double Precision Shift Left */
        _shrd,	        /* Double Precision Shift Right */
        _sidt,	        /* Store Interrupt Descriptor Table */
        _sldt,	        /* Store Local Descriptor Table Register (LDTR) */
        _smsw,	        /* Store Machine Status Word */
        _stc,	        /* Set Carry Flag(CF) */
        _std,	        /* Set Direction Flag(DF) */
        _sti,	        /* Set Interrupt Flag(IF) */
        _stosb,	        /* Store String Data Byte */
        _stosw,	        /* Store String Data Word */
        _stosd,	        /* Store String Data DoubleWord */
        _str,	        /* Store Task Register */
        _sub,	        /* Subtract */
        _test,	        /* Test Operands */
        _verr,	        /* Verify Read */
        _verw,	        /* Verify Write */
        _wait,	        /* Wait for FPU */
        _wbinvd,	    /* Write Back and Invalidate Data Cache */
        _wrmsr,	        /* Write to Model Specific Register */
        _xadd,	        /* Exchange and Add */
        _xchg,	        /* Exchange */
        _xlat,	        /* Translate */
        _xor,	        /* Exclusive-OR */
    };

}

#endif // __mercury_vm_opcode_h__
