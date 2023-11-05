cmake_minimum_required(VERSION 3.26)
project(mercury)

set(CMAKE_CXX_STANDARD 17)

add_executable(mercury src/main.cpp src/vm/cpu.cpp
        src/vm/opcode.cpp)
