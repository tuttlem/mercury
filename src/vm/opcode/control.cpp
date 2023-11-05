/**
 * @brief Control flow opcode implementations
 */

#include "../cpu.h"

namespace mercury {

    void cpu::_hlt(cpu *cpu) {
        cpu->halt();
    }
}