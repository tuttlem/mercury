/**
 * @file bus.h
 * @brief Interface for the system bus
*/

#ifndef __mercury_vm_bus_h__

#define __mercury_vm_bus_h__

#include <cstdint>

#include <memory>

namespace mercury {

    /**
     * @brief Interface for the system bus
     */
    class bus {
    public:
        /**
         * @brief Write a value to the bus
         * @param address The address to write to
         * @param value The value to write
         */
        virtual void write8(uint64_t address, uint8_t value) = 0;

        /**
         * @brief Write a value to the bus
         * @param address The address to write to
         * @param value The value to write
         */
        virtual void write16(uint64_t address, uint16_t value) = 0;

        /**
         * @brief Write a value to the bus
         * @param address The address to write to
         * @param value The value to write
         */
        virtual void write32(uint64_t address, uint32_t value) = 0;

        /**
         * @brief Write a value to the bus
         * @param address The address to write to
         * @param value The value to write
         */
        virtual void write64(uint64_t address, uint64_t value) = 0;

        /**
         * @brief Read a value from the bus
         * @param address The address to read from
         * @return The value read from the bus
         */
        virtual uint8_t read8(uint64_t address) = 0;

        /**
         * @brief Read a value from the bus
         * @param address The address to read from
         * @return The value read from the bus
         */
        virtual uint16_t read16(uint64_t address) = 0;

        /**
         * @brief Read a value from the bus
         * @param address The address to read from
         * @return The value read from the bus
         */
        virtual uint32_t read32(uint64_t address) = 0;

        /**
         * @brief Read a value from the bus
         * @param address The address to read from
         * @return The value read from the bus
         */
        virtual uint64_t read64(uint64_t address) = 0;
    };

    typedef std::shared_ptr<bus> bus_ptr;

}

#endif /* __mercury_vm_bus_h__ */