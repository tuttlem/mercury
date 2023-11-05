/**
 * @brief Arithmetic opcode implementations
 */

#include "../cpu.h"

namespace mercury {

    void cpu::_adc(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        cpu->set_op_1(p1 + p2 + cpu->get_flag(cpu_flag::carry));
    }

    void cpu::_add(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        cpu->set_op_1(p1 + p2);
    }

    void cpu::_and(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        cpu->set_op_1(p1 & p2);
    }

    void cpu::_bswap(cpu *cpu) {
        auto p1 = cpu->get_op_1();

        cpu->set_op_1(
            ((p1 & 0xff00000000000000) >> 56) |
            ((p1 & 0x00ff000000000000) >> 40) |
            ((p1 & 0x0000ff0000000000) >> 24) |
            ((p1 & 0x000000ff00000000) >> 8) |
            ((p1 & 0x00000000ff000000) << 8) |
            ((p1 & 0x0000000000ff0000) << 24) |
            ((p1 & 0x000000000000ff00) << 40) |
            ((p1 & 0x00000000000000ff) << 56)
        );
    }

    void cpu::_bt(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        cpu->set_flag(cpu_flag::carry, (p1 >> p2) & 1);
    }

    void cpu::_btc(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        cpu->set_flag(cpu_flag::carry, (p1 >> p2) & 1);
        cpu->set_op_1(p1 ^ (1 << p2));
    }

    void cpu::_btr(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        cpu->set_flag(cpu_flag::carry, (p1 >> p2) & 1);
        cpu->set_op_1(p1 & ~(1 << p2));
    }

    void cpu::_bts(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        cpu->set_flag(cpu_flag::carry, (p1 >> p2) & 1);
        cpu->set_op_1(p1 | (1 << p2));
    }

    void cpu::_cmp(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        cpu->set_flag(cpu_flag::zero, p1 == p2);
        cpu->set_flag(cpu_flag::negative, p1 < p2);
    }

    void cpu::_cmpsb(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        cpu->_bus->write8(cpu->_r[cpu_reg::r6].q, cpu->_bus->read8(cpu->_r[cpu_reg::r7].q));
        cpu->_r[cpu_reg::r6].q += p1;
        cpu->_r[cpu_reg::r7].q += p2;
    }

    void cpu::_cmpsw(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        cpu->_bus->write16(cpu->_r[cpu_reg::r6].q, cpu->_bus->read16(cpu->_r[cpu_reg::r7].q));
        cpu->_r[cpu_reg::r6].q += p1;
        cpu->_r[cpu_reg::r7].q += p2;
    }

    void cpu::_cmpsd(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        cpu->_bus->write32(cpu->_r[cpu_reg::r6].q, cpu->_bus->read32(cpu->_r[cpu_reg::r7].q));
        cpu->_r[cpu_reg::r6].q += p1;
        cpu->_r[cpu_reg::r7].q += p2;
    }

    void cpu::_cmpsq(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        cpu->_bus->write64(cpu->_r[cpu_reg::r6].q, cpu->_bus->read64(cpu->_r[cpu_reg::r7].q));
        cpu->_r[cpu_reg::r6].q += p1;
        cpu->_r[cpu_reg::r7].q += p2;
    }

    void cpu::_cmpxchg(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        if (p1 == cpu->_r[cpu_reg::r0].q) {
            cpu->_r[cpu_reg::r0].q = p2;
            cpu->set_flag(cpu_flag::zero, 1);
        } else {
            cpu->set_flag(cpu_flag::zero, 0);
        }
    }

    void cpu::_cmpxchg8b(cpu *cpu) {
        auto p1 = cpu->get_op_1();

        if (p1 == cpu->_r[cpu_reg::r0].q) {
            cpu->_r[cpu_reg::r0].q = cpu->get_op_2();
            cpu->set_flag(cpu_flag::zero, 1);
        } else {
            cpu->set_flag(cpu_flag::zero, 0);
        }
    }

    void cpu::_dec(cpu *cpu) {
        auto p1 = cpu->get_op_1();

        cpu->set_op_1(p1 - 1);
    }

    void cpu::_div(cpu *cpu) {
        auto p1 = cpu->get_op_1();

        cpu->_r[cpu_reg::r0].q /= p1;
        cpu->_r[cpu_reg::r1].q %= p1;
    }

    void cpu::_idiv(cpu *cpu) {
        auto p1 = cpu->get_op_1();

        cpu->_r[cpu_reg::r0].q /= p1;
        cpu->_r[cpu_reg::r1].q %= p1;
    }

    void cpu::_imul(cpu *cpu) {
        auto p1 = cpu->get_op_1();

        cpu->_r[cpu_reg::r0].q *= p1;
    }

    void cpu::_inc(cpu *cpu) {
        auto p1 = cpu->get_op_1();

        cpu->set_op_1(p1 + 1);
    }

    void cpu::_mod(cpu *cpu) {
        auto p1 = cpu->get_op_1();

        cpu->_r[cpu_reg::r0].q %= p1;
    }

    void cpu::_mul(cpu *cpu) {
        auto p1 = cpu->get_op_1();

        cpu->_r[cpu_reg::r0].q *= p1;
    }

    void cpu::_neg(cpu *cpu) {
        auto p1 = cpu->get_op_1();

        cpu->set_op_1(-p1);
    }

    void cpu::_not(cpu *cpu) {
        auto p1 = cpu->get_op_1();

        cpu->set_op_1(~p1);
    }

    void cpu::_or(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        cpu->set_op_1(p1 | p2);
    }

    void cpu::_rcl(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        for (auto i = 0; i < p2; i++) {
            auto carry = cpu->get_flag(cpu_flag::carry);

            cpu->set_flag(cpu_flag::carry, (p1 >> (64 - 1)) & 1);
            p1 = (p1 << 1) | carry;
        }

        cpu->set_op_1(p1);
    }

    void cpu::_rcr(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        for (auto i = 0; i < p2; i++) {
            auto carry = cpu->get_flag(cpu_flag::carry);

            cpu->set_flag(cpu_flag::carry, p1 & 1);
            p1 = (p1 >> 1) | (carry << (64 - 1));
        }

        cpu->set_op_1(p1);
    }

    void cpu::_rol(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        for (auto i = 0; i < p2; i++) {
            auto carry = cpu->get_flag(cpu_flag::carry);

            cpu->set_flag(cpu_flag::carry, (p1 >> (64 - 1)) & 1);
            p1 = (p1 << 1) | carry;
        }

        cpu->set_op_1(p1);
    }

    void cpu::_ror(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        for (auto i = 0; i < p2; i++) {
            auto carry = cpu->get_flag(cpu_flag::carry);

            cpu->set_flag(cpu_flag::carry, p1 & 1);
            p1 = (p1 >> 1) | (carry << (64 - 1));
        }

        cpu->set_op_1(p1);
    }

    void cpu::_sal(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        cpu->set_flag(cpu_flag::carry, (p1 >> (64 - p2)) & 1);
        cpu->set_op_1(p1 << p2);
    }

    void cpu::_sar(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        cpu->set_flag(cpu_flag::carry, (p1 >> (p2 - 1)) & 1);
        cpu->set_op_1(p1 >> p2);
    }

    void cpu::_sbb(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        cpu->set_op_1(p1 - p2 - cpu->get_flag(cpu_flag::carry));
    }

    void cpu::_shl(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        cpu->set_flag(cpu_flag::carry, (p1 >> (64 - p2)) & 1);
        cpu->set_op_1(p1 << p2);
    }

    void cpu::_shr(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        cpu->set_flag(cpu_flag::carry, (p1 >> (p2 - 1)) & 1);
        cpu->set_op_1(p1 >> p2);
    }

    void cpu::_sub(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        cpu->set_op_1(p1 - p2);
    }

    void cpu::_test(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        cpu->set_flag(cpu_flag::zero, p1 & p2);
        cpu->set_flag(cpu_flag::negative, p1 < p2);
    }

    void cpu::_xadd(mercury::cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        cpu->set_op_2(p1);
        cpu->set_op_1(p1 + p2);
    }

    void cpu::_xchg(mercury::cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        cpu->set_op_2(p1);
        cpu->set_op_1(p2);
    }

    void cpu::_xor(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        cpu->set_op_1(p1 ^ p2);
    }

}
