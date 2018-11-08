//
// Created by Riverssen on 08.11.18.
//

#ifndef MOCHAVM_TYPES_H
#define MOCHAVM_TYPES_H

#include <cstring>

typedef unsigned char   uint_8;
typedef unsigned short  uint_16;
typedef unsigned int    uint_32;
typedef unsigned long   uint_64;

typedef char            int_8;
typedef short           int_16;
typedef int             int_32;
typedef long            int_64;

typedef float           flt_32;
typedef double          flt_64;

typedef unsigned char*  pointer;
typedef unsigned long   pointer_literal_type;

//class int_128{
//};
//class int_256{};
//class uint_128{};
//class uint_256{};
//
//class flt_128{};
//class flt_256{};

typedef long long int_128;
typedef unsigned long long uint_128;

typedef long long int_256;
typedef unsigned long long uint_256;

typedef double flt_128;
typedef double flt_256;

union uint_40 {
    uint_8 i[5];
    unsigned long l;

public:
    uint_40(uint_64 v) : l(v)
    {
    }
    uint_40(uint_8 v[5]) : l(0)
    {
        memcpy(i, v, 5);
    }
    uint_40(const uint_40& o) : l(o.l)
    {
    }
};

#endif //MOCHAVM_TYPES_H
