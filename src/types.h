#ifndef MOCHAXX_TYPES_H
#define MOCHAXX_TYPES_H

//
// Created by Riverssen on 12.12.18.
//

#include <cstring>

typedef unsigned char           uint_8;
typedef unsigned short          uint_16;
typedef unsigned int            uint_32;
typedef unsigned long long      uint_64;

typedef char                    int_8;
typedef short                   int_16;
typedef int                     int_32;
typedef long                    int_64;

typedef float                   flt_32;
typedef double                  flt_64;

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

union localvarelement{
    uint_8  UnsignedByte;
    uint_16 UnsignedShort;
    uint_32 UnsignedInt;
    uint_40 UnsignedInt40;
    uint_64 UnsignedLong;

    flt_32  Float;
    flt_64  Double;
    int_128 LongInt;
    int_256 LongLong;
    uint_128 UnsignedLongInt;
    uint_256 UnsignedLongLong;
    flt_128  DoubleFloat;
    flt_256  DoubleDouble;

    int_8  Byte;
    int_16 Short;
    int_32 Int;
    int_64 Long;
    pointer Pointer;

    uint_8 maximumSize[32];

public:
    localvarelement()
    {
    }

    localvarelement(const localvarelement& o)
    {
        memcpy(maximumSize, o.maximumSize, 32);
    }

    void operator = (const localvarelement& o)
    {
        memcpy(maximumSize, o.maximumSize, 32);
    }
};

#endif //MOCHAXX_TYPES_H
