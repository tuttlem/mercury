
#include "./cpu.h"

#include <iostream>

namespace mercury {

    /**
     * @brief Resets the state of the cpu
     */
    void cpu::reset(void) {
        this->set_state(cpu_state::init);

        this->_r.fill({.q = 0});

        // todo: reset the stack pointer
        // todo: reset the program counter
        // todo: reset the flags

        this->_bus = nullptr;
    }

    opcode_func cpu::get_opcode_func(const uint32_t opcode) {
        return cpu::_opcode_table[opcode];
    }

    /**
     * @brief Steps the cpu through one instruction
     */
    void cpu::step(void) {
        assert(this->_state == cpu_state::running);

        auto opcode = this->_bus->read32(this->pc().q);
        auto func = this->get_opcode_func(opcode);

        if (func == nullptr) {
            this->set_flag(cpu_flag::illegal, 1);
            this->halt();

            return;
        }

        func(this);
        this->pc().q += 2;
    }

    /**
     * @brief Gets the value of an addressed value
     * @param addr {addressing} The addressing mode to use
     * @param value {uint64_t} The value to address
     * @return {uint64_t} The addressed value
     */
    uint64_t cpu::get_addressed_value(addressing addr, uint64_t value) {
        switch (addr) {
            case addressing::immediate:
                return value;

            case addressing::direct:
                return this->_bus->read64(value);

            case addressing::register_direct:
                return this->_r[value].q;

            case addressing::register_indirect:
                return this->_bus->read64(this->_r[value].q);

            case addressing::indexed:
                return this->_bus->read64(this->_r[cpu_reg::r6].q + value);

            case addressing::based_indexed:
                return this->_bus->read64(this->_r[cpu_reg::r6].q + this->_r[value].q);

            default:
                throw addressing_exception(value);
        }
    }

    /**
     * @brief Sets the value of an addressed value
     * @param addr {addressing} The addressing mode to use
     * @param value {uint64_t} The value to address
     * @param data {uint64_t} The data to set the addressed value to
     */
    void cpu::set_addressed_value(addressing addr, uint64_t value, uint64_t data) {
        switch (addr) {
            case addressing::immediate:
                throw addressing_exception(value);

            case addressing::direct:
                this->_bus->write64(value, data);
                break;

            case addressing::register_direct:
                this->_r[value].q = data;
                break;

            case addressing::register_indirect:
                this->_bus->write64(this->_r[value].q, data);
                break;

            case addressing::indexed:
                this->_bus->write64(this->_r[cpu_reg::r6].q + value, data);
                break;

            case addressing::based_indexed:
                this->_bus->write64(this->_r[cpu_reg::r6].q + this->_r[value].q, data);
                break;

            default:
                throw addressing_exception(value);
        }
    }

    /**
     * @brief Runs the cpu until it halts
     */
    void cpu::run(void) {
        assert(this->_state == cpu_state::init);

        this->set_state(cpu_state::running);

        while (this->_state == cpu_state::running) {
           this->step();
        }
    }

    /**
     * @brief Halts the cpu
     */
    void cpu::halt(void) {
        this->set_state(cpu_state::halted);

        throw halted_exception();
    }

    /**
     * @brief Sets the state of the cpu
     * @param state The state to set the cpu to
     */
    void cpu::set_state(cpu_state state) {
        this->_state = state;
    }

    /**
     * @brief Sets the value of a flag
     * @param flag The flag to set
     * @param value The value to set the flag to
     */
    void cpu::set_flag(cpu_flag flag, uint8_t value) {
        if (value) {
            this->_r[cpu_reg::flags].q |= flag;
        } else {
            this->_r[cpu_reg::flags].q &= ~flag;
        }
    }

    /**
     * @brief Gets the value of a flag
     * @param flag The flag to get
     * @return The value of the flag
     */
    uint8_t cpu::get_flag(cpu_flag flag) {
        return (this->_r[cpu_reg::flags].q & flag) > 0;
    }

    /**
     * @brief Pushes a value onto the stack
     * @param value The value to push onto the stack
     */
    void cpu::push(uint64_t value) {
        assert(this->_bus != nullptr);

        this->_bus->write64(--this->_r[cpu_reg::sp].q, value);
    }

    /**
     * @brief Pops a value off of the stack
     * @return The value popped off of the stack
     */
    uint64_t cpu::pop(void) {
        assert(this->_bus != nullptr);

        return this->_bus->read64(this->_r[cpu_reg::sp].q++);
    }

    /**
     * @brief Interrupts the cpu to execute a request
     * @param vector The vector to interrupt with
     */
    void cpu::irq(const uint8_t vector) {
        if (this->get_flag(cpu_flag::interrupt)) {
            this->push(this->_r[cpu_reg::pc].q);
            this->push(this->_r[cpu_reg::flags].q);

            this->set_flag(cpu_flag::interrupt, 1);
            this->set_flag(cpu_flag::_break, 0);

            // jump to the address of the requested vector
            this->_r[cpu_reg::pc].q = this->_bus->read64(
            cpu::irq_vector + vector
            );
        }
    }

    /**
     * @brief Non-maskable interrupt
     * @param vector The vector to interrupt with
     */
    void cpu::nmi(const uint8_t vector) {
        this->push(this->_r[cpu_reg::pc].q);
        this->push(this->_r[cpu_reg::flags].q);

        this->set_flag(cpu_flag::interrupt, 1);

        // jump to the address of the requested vector
        this->_r[cpu_reg::pc].q = this->_bus->read64(
        cpu::nmi_vector + vector
        );
    }

}