//
// Created by michael on 22/10/23.
//

#include <map>
#include <iostream>
#include "cpu.h"

#define opdef_2(name) \
    { opc2(opcode::_##name, addressing::register_direct, addressing::register_direct), &cpu::_##name }, \
    { opc2(opcode::_##name, addressing::direct, addressing::register_direct), &cpu::_##name }, \
    { opc2(opcode::_##name, addressing::register_direct, addressing::register_direct), &cpu::_##name }, \
    { opc2(opcode::_##name, addressing::register_direct, addressing::direct), &cpu::_##name }, \
    { opc2(opcode::_##name, addressing::register_direct, addressing::immediate), &cpu::_##name }, \
    { opc2(opcode::_##name, addressing::register_indirect, addressing::immediate), &cpu::_##name }, \
    { opc2(opcode::_##name, addressing::direct, addressing::immediate), &cpu::_##name }


namespace mercury {

    std::map<uint32_t, opcode_func> cpu::_opcode_table = {
            opdef_2(adc),
            opdef_2(add),
            opdef_2(and),
            opdef_2(cmp),
            opdef_2(or),
            opdef_2(xor),
            opdef_2(rcl),
            opdef_2(rcr),
            opdef_2(rol),
            opdef_2(ror),
            opdef_2(sal),
            opdef_2(sar),
            opdef_2(shl),
            opdef_2(shr),
            opdef_2(sub),
            opdef_2(xor),


            { opc0(opcode::_nop), &cpu::_nop},
            { opc0(opcode::_hlt), &cpu::_hlt},
    };

}