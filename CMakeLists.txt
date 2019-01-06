cmake_minimum_required(VERSION 3.12)
project(Mochaxx)

set(CMAKE_CXX_STANDARD 17)

add_executable(Mochaxx main.cpp src/endianness.cpp src/endianness.h src/types.h src/vm_structs.cpp src/vm_structs.h src/ops.h)