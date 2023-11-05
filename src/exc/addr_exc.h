#ifndef __mercury_exc_addr_exc_h__

#define __mercury_exc_addr_exc_h__

#include <cstdint>
#include <string>
#include <exception>

namespace mercury {

    class addressing_exception : public std::exception {
    public:
        addressing_exception(uint8_t mode) : _mode(mode) {}

        uint8_t mode() const {
            return _mode;
        }

        const char* what() const throw() override {
            return "Addressing mode is invalid";
        }

    private:
        uint8_t _mode;
    };

}

#endif /* __mercury_exc_addr_exc_h__ */