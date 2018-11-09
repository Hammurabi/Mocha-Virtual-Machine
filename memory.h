//
// Created by Riverssen on 08.11.18.
//

#ifndef MOCHA_VIRTUAL_MACHINE_MEMORY_H
#define MOCHA_VIRTUAL_MACHINE_MEMORY_H

#include <map>
#include "types.h"

class AnnouncedMemory
{
    std::map<long, pointer> memory;
public:
    /**
     * @param size pointer size.
     * @return A GC smart pointer that can be monitored by the VM.
     *
     *
     * Smart pointers are 40 bit integers (5 bytes) in big endian order.
     * The first byte of the 3 left-most bytes specifies the type of pointer (0x03).
     * The second and third bytes contain pointer flags.
     * The remaining 5 bytes are an index of a native pointer.
     *
     * The use of 40 bits allows 2^40 different addresses or access to a maximum of 1099,511627776 Gb of memory.
     */
    uint_64 genPointer(uint_64 size);
};


#endif //MOCHA_VIRTUAL_MACHINE_MEMORY_H
