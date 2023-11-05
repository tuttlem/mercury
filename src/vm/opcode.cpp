//
// Created by michael on 22/10/23.
//

#include <map>
#include <iostream>
#include "cpu.h"

namespace mercury {

    std::map<uint32_t, opcode_func> cpu::_opcode_table = {
            { opc2(opcode::_add, addressing::direct, addressing::immediate), &cpu::_add },
            { opc2(opcode::_add, addressing::register_direct, addressing::immediate), &cpu::_add },

            { opc0(opcode::_nop), &cpu::_nop},
            { opc0(opcode::_hlt), &cpu::_hlt},
    };

    void cpu::_nop(cpu *cpu) {
        // no-operation
        std::cout << "nop" << std::endl;
    }

    void cpu::_hlt(cpu *cpu) {
        cpu->halt();
    }

    void cpu::_add(cpu *cpu) {
        auto p1 = cpu->get_op_1();
        auto p2 = cpu->get_op_2();

        cpu->set_op_1(p1 + p2);
    }

}