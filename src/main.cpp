#include <iostream>

#include "./vm/cpu.h"

using namespace std;

uint64_t memory[1024];

class debug_bus : public mercury::bus {
public:
    void write8(uint64_t address, uint8_t value) override {
        cout << "write8: " << address << " " << value << endl;
        ((uint8_t *)memory)[address] = value;
    }

    void write16(uint64_t address, uint16_t value) override {
        cout << "write16: " << address << " " << value << endl;
        ((uint16_t *)memory)[address] = value;
    }

    void write32(uint64_t address, uint32_t value) override {
        cout << "write32: " << address << " " << value << endl;
        ((uint32_t *)memory)[address] = value;
    }

    void write64(uint64_t address, uint64_t value) override {
        cout << "write64: " << address << " " << value << endl;
        ((uint64_t *)memory)[address] = value;
    }

    uint8_t read8(uint64_t address) override {
        cout << "read8: " << address << endl;
        return ((uint8_t *)memory)[address];
    }

    uint16_t read16(uint64_t address) override {
        cout << "read16: " << address << endl;
        return ((uint16_t *)memory)[address];
    }

    uint32_t read32(uint64_t address) override {
        cout << "read32: " << address << endl;
        return ((uint32_t *)memory)[address];
    }

    uint64_t read64(uint64_t address) override {
        cout << "read64: " << address << endl;
        return ((uint64_t *)memory)[address];
    }
};

int main() {
    auto cpu = std::make_shared<mercury::cpu>();

    try {


        cout << "state: " << cpu->state() << endl;

        cpu->reset();
        cout << "state: " << cpu->state() << endl;

        cpu->_bus = std::make_shared<debug_bus>();

        // nop
        memory[0] = opc0(mercury::opcode::_nop);

        // add r0, 50
        memory[1] = opc2(mercury::opcode::_shl, mercury::addressing::register_direct, mercury::addressing::immediate);
        memory[3] = 0x0000000000000001;
        memory[4] = 1;

        // hlt
        memory[5] = opc0(mercury::opcode::_hlt);

        cpu->r1().q = 4;

        cpu->run();
    } catch (const mercury::addressing_exception &e) {
        cout << "Addressing exception: " << e.mode() << endl;
    } catch (const mercury::halted_exception &e) {
        cout << "System halted!" << endl;

        cout << "state: " << cpu->state() << endl;
        cout << "r1: " << cpu->r1().q << endl;
    };


    return 0;
}
