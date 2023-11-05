/**
 * @file cpu.h
 * @brief Interface for the CPU
*/

#ifndef __mercury_vm_cpu_h__

#define __mercury_vm_cpu_h__

#include <cstdint>
#include <cassert>
#include <algorithm>
#include <map>

#include "bus.h"

#include "../exc/addr_exc.h"
#include "../exc/halted_exc.h"
#include "./opcode.h"

namespace mercury {

    /**
     * @brief Defines a register
     */
    union reg {
        uint64_t q;
        double   f;
        uint32_t d[2];
        uint16_t w[4];
        uint8_t  b[8];
    };

    /**
     * @brief CPU state flags
     */
    enum cpu_flag {
        carry     = 0x01,
        zero      = 0x02,
        interrupt = 0x04,
        decimal   = 0x08,
        _break    = 0x10,
        unused    = 0x20,
        overflow  = 0x40,
        negative  = 0x80,
        illegal   = 0x100,
    };

    /**
     * @brief CPU register indices
     */
    enum cpu_reg {
        r0 = 0,
        r1 = 1,
        r2 = 2,
        r3 = 3,
        r4 = 4,
        r5 = 5,
        r6 = 6,
        r7 = 7,
        sp = 8,
        pc = 9,
        flags = 10
    };

    /**
     * @brief FPU register indices
     */
    enum fpu_reg {
        f0 = 0,
        f1 = 1,
        f2 = 2,
        f3 = 3,
        f4 = 4,
        f5 = 5,
        f6 = 6,
        f7 = 7,
    };

    /**
     * @brief CPU state
     */
    enum cpu_state {
        init,
        running,
        halted,
        error,
    };

    class cpu;
    typedef std::shared_ptr<cpu> cpu_ptr;

    typedef std::function<void(cpu*)> opcode_func;

    /**
     * @brief The CPU
     */
    class cpu {
    private:
        static constexpr uint64_t stack_base = 0x100;
        static constexpr uint64_t irq_vector = 0xfffe;
        static constexpr uint64_t nmi_vector = 0xfffa;

    public:
        cpu(void) = default;
        virtual ~cpu(void) = default;

        /**
         * @brief Resets the state of the cpu
         */
        void reset(void);

        /**
         * @brief Halts the cpu
         */
        void halt(void);

        /**
         * @brief Steps the cpu through one instruction
         */
        void step(void);

        /**
         * @brief Runs the cpu until it halts
         */
        void run(void);

        /**
         * @brief Retrieves the current state
         * @return The current state
         */
        const cpu_state state(void) const { return this->_state; }


    private:
        /** Arithmetic instructions */
        static void _adc(cpu *cpu);
        static void _add(cpu *cpu);
        static void _and(cpu *cpu);
        static void _bswap(cpu *cpu);
        static void _bt(cpu *cpu);
        static void _btc(cpu *cpu);
        static void _btr(cpu *cpu);
        static void _bts(cpu *cpu);
        static void _cmp(cpu *cpu);
        static void _cmpsb(cpu *cpu);
        static void _cmpsw(cpu *cpu);
        static void _cmpsd(cpu *cpu);
        static void _cmpsq(cpu *cpu);
        static void _cmpxchg(cpu *cpu);
        static void _cmpxchg8b(cpu *cpu);
        static void _dec(cpu *cpu);
        static void _div(cpu *cpu);
        static void _idiv(cpu *cpu);
        static void _imul(cpu *cpu);
        static void _inc(cpu *cpu);
        static void _mod(cpu *cpu);
        static void _mul(cpu *cpu);
        static void _neg(cpu *cpu);
        static void _not(cpu *cpu);
        static void _or(cpu *cpu);
        static void _rcl(cpu *cpu);
        static void _rcr(cpu *cpu);
        static void _rol(cpu *cpu);
        static void _ror(cpu *cpu);
        static void _sal(cpu *cpu);
        static void _sar(cpu *cpu);
        static void _sbb(cpu *cpu);
        static void _shl(cpu *cpu);
        static void _shr(cpu *cpu);
        static void _sub(cpu *cpu);
        static void _test(cpu *cpu);
        static void _xadd(cpu *cpu);
        static void _xchg(cpu *cpu);
        static void _xor(cpu *cpu);



        /** Control flow instructions */
        static void _hlt(cpu *cpu);

        /** Other instructions */
        static void _nop(cpu *cpu);

        /**
         * @brief Sets the value of an addressed value
         * @param addr {addressing} The addressing mode to use
         * @param value {uint64_t} The value to address
         * @param data {uint64_t} The data to set the addressed value to
         */
        void set_addressed_value(addressing addr, uint64_t value, uint64_t data);

        /**
         * @brief Gets the value of an addressed value
         * @param addr {addressing} The addressing mode to use
         * @param value {uint64_t} The value to address
         * @return {uint64_t} The addressed value
         */
        uint64_t get_addressed_value(addressing addr, uint64_t value);

        inline uint64_t get_op_1(void) {
            return this->get_addressed_value(
                static_cast<addressing>((this->_bus->read16(this->_r[cpu_reg::pc].q + 2)) & 0x7),
                this->_bus->read64(this->_r[cpu_reg::pc].q + 1)
            );
        }

        inline void set_op_1(uint64_t value) {
            this->set_addressed_value(
                    static_cast<addressing>((this->_bus->read16(this->_r[cpu_reg::pc].q + 2)) & 0x7),
                    this->_bus->read64(this->_r[cpu_reg::pc].q + 1),
                    value
            );
        }

        inline uint64_t get_op_2(void) {
            return this->get_addressed_value(
                static_cast<addressing>((this->_bus->read16(this->_r[cpu_reg::pc].q + 2) >> 3) & 0x7),
                this->_bus->read64(this->_r[cpu_reg::pc].q + 2)
            );
        }

        inline void set_op_2(uint64_t value) {
            this->set_addressed_value(
                    static_cast<addressing>((this->_bus->read16(this->_r[cpu_reg::pc].q + 2) >> 3) & 0x7),
                    this->_bus->read64(this->_r[cpu_reg::pc].q + 2),
                    value
            );
        }


        inline uint64_t get_op_3(void) {
            return this->get_addressed_value(
                static_cast<addressing>((this->_bus->read16(this->_r[cpu_reg::pc].q + 2) >> 6) & 0x7),
                this->_bus->read64(this->_r[cpu_reg::pc].q + 3)
            );
        }


        /**
         * @brief Sets the state of the cpu
         * @param state The state to set the cpu to
         */
        void set_state(cpu_state state);

        /**
         * @brief Sets the value of a flag
         * @param flag The flag to set
         * @param value The value to set the flag to
         */
        void set_flag(cpu_flag flag, uint8_t value);

        /**
         * @brief Gets the value of a flag
         * @param flag The flag to get
         * @return The value of the flag
         */
        uint8_t get_flag(cpu_flag flag);

        /**
         * @brief Pushes a value onto the stack
         * @param value The value to push onto the stack
         */
        void push(uint64_t value);

        /**
         * @brief Pops a value off of the stack
         * @return The value popped off of the stack
         */
        uint64_t pop(void);

        /**
         * @brief Interrupts the cpu to execute a request
         */
        void irq(const uint8_t vector);

        /**
         * @brief Non-maskable interrupt
         */
        void nmi(const uint8_t vector);

    public:
        inline reg &r0(void) { return this->_r[cpu_reg::r0]; }
        inline reg &r1(void) { return this->_r[cpu_reg::r1]; }
        inline reg &r2(void) { return this->_r[cpu_reg::r2]; }
        inline reg &r3(void) { return this->_r[cpu_reg::r3]; }
        inline reg &r4(void) { return this->_r[cpu_reg::r4]; }
        inline reg &r5(void) { return this->_r[cpu_reg::r5]; }

        inline reg &r6(void) { return this->_r[cpu_reg::r6]; }
        inline reg &r7(void) { return this->_r[cpu_reg::r7]; }

        inline reg &sp(void) { return this->_r[cpu_reg::sp]; }
        inline reg &pc(void) { return this->_r[cpu_reg::pc]; }

        inline reg &flags(void) { return this->_r[cpu_reg::flags]; }

    private:
        opcode_func get_opcode_func(const uint32_t opcode);

    public:
        std::array<reg, 11> _r;             /* general purpose registers */

        bus_ptr _bus;                       /* the system bus */

        cpu_state _state;                   /* the state of the cpu */

        static std::map<uint32_t , opcode_func> _opcode_table;   /* the table of opcode implementations */
    };
}

#endif /* __mercury_vm_cpu_h__ */