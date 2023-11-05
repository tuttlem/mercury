#ifndef __mercury_exc_halted_exc_h__

#define __mercury_exc_halted_exc_h__

#include <cstdint>
#include <string>
#include <exception>

namespace mercury {

    class halted_exception : public std::exception {
    public:
        halted_exception() {}

        const char* what() const throw() override {
            return "CPU is halted";
        }
    };

}

#endif /* __mercury_exc_halted_exc_h__ */