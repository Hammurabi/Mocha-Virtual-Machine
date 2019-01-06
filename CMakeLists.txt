cmake_minimum_required(VERSION 3.12)
project(Mocha_Virtual_Machine)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Mocha_Virtual_Machine
        endianness.cpp
        endianness.h
        executor.cpp
        executor.h
        LICENSE
        main.cpp
        opcodes.h
        README.md
        types.h memory.cpp memory.h executorfuncs.cpp executorfuncs.h nucleus.h src/mxxvm.cpp src/mxxvm.h)
