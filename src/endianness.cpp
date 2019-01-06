#include "endianness.h"

//
// Created by Riverssen on 12.12.18.
//

EndianMachine::EndianMachine()
{
    int i = 1;
    bigEndian =!((int) *((unsigned char *) &i) == 1);
}

uint_16 EndianMachine::FixUnsignedShortEndianness(uint_16 r)
{
    if (bigEndian) return r;

    uint_16 o;
    ((pointer) (&o))[0] = ((pointer) (&r))[1];
    ((pointer) (&o))[1] = ((pointer) (&r))[0];
    return o;
}

uint_32 EndianMachine::FixUnsignedIntEndianness(uint_32 r)
{
    if (bigEndian) return r;

    uint_32 o;
    ((pointer) (&o))[0] = ((pointer) (&r))[3];
    ((pointer) (&o))[1] = ((pointer) (&r))[2];
    ((pointer) (&o))[2] = ((pointer) (&r))[1];
    ((pointer) (&o))[3] = ((pointer) (&r))[0];

    return o;
}

uint_64 EndianMachine::FixUnsignedLongEndianness(uint_64 r)
{
    if (bigEndian) return r;

    uint_64 o;
    ((pointer) (&o))[0] = ((pointer) (&r))[7];
    ((pointer) (&o))[1] = ((pointer) (&r))[6];
    ((pointer) (&o))[2] = ((pointer) (&r))[5];
    ((pointer) (&o))[3] = ((pointer) (&r))[4];
    ((pointer) (&o))[4] = ((pointer) (&r))[3];
    ((pointer) (&o))[5] = ((pointer) (&r))[2];
    ((pointer) (&o))[6] = ((pointer) (&r))[1];
    ((pointer) (&o))[7] = ((pointer) (&r))[0];

    return o;
}

int_16 EndianMachine::FixShortEndianness(int_16 r)
{
    if (bigEndian) return r;

    int_16 o;
    ((pointer) (&o))[0] = ((pointer) (&r))[1];
    ((pointer) (&o))[1] = ((pointer) (&r))[0];
    return o;
}

int_32 EndianMachine::FixIntEndianness(int_32 r)
{
    if (bigEndian) return r;

    int_32 o;
    ((pointer) (&o))[0] = ((pointer) (&r))[3];
    ((pointer) (&o))[1] = ((pointer) (&r))[2];
    ((pointer) (&o))[2] = ((pointer) (&r))[1];
    ((pointer) (&o))[3] = ((pointer) (&r))[0];

    return o;
}

int_64 EndianMachine::FixLongEndianness(int_64 r)
{
    if (bigEndian) return r;

    int_64 o;
    ((pointer) (&o))[0] = ((pointer) (&r))[7];
    ((pointer) (&o))[1] = ((pointer) (&r))[6];
    ((pointer) (&o))[2] = ((pointer) (&r))[5];
    ((pointer) (&o))[3] = ((pointer) (&r))[4];
    ((pointer) (&o))[4] = ((pointer) (&r))[3];
    ((pointer) (&o))[5] = ((pointer) (&r))[2];
    ((pointer) (&o))[6] = ((pointer) (&r))[1];
    ((pointer) (&o))[7] = ((pointer) (&r))[0];

    return o;
}

uint_128 EndianMachine::FixUnsignedLongIntEndianness(uint_128 r)
{
    if (bigEndian) return r;

    uint_128 o;
    ((pointer) (&o))[0] = ((pointer) (&r))[7];
    ((pointer) (&o))[1] = ((pointer) (&r))[6];
    ((pointer) (&o))[2] = ((pointer) (&r))[5];
    ((pointer) (&o))[3] = ((pointer) (&r))[4];
    ((pointer) (&o))[4] = ((pointer) (&r))[3];
    ((pointer) (&o))[5] = ((pointer) (&r))[2];
    ((pointer) (&o))[6] = ((pointer) (&r))[1];
    ((pointer) (&o))[7] = ((pointer) (&r))[0];

    return o;
}

int_128 EndianMachine::FixLongIntEndianness(int_128 r)
{
    if (bigEndian) return r;

    int_128 o;
    ((pointer) (&o))[0] = ((pointer) (&r))[7];
    ((pointer) (&o))[1] = ((pointer) (&r))[6];
    ((pointer) (&o))[2] = ((pointer) (&r))[5];
    ((pointer) (&o))[3] = ((pointer) (&r))[4];
    ((pointer) (&o))[4] = ((pointer) (&r))[3];
    ((pointer) (&o))[5] = ((pointer) (&r))[2];
    ((pointer) (&o))[6] = ((pointer) (&r))[1];
    ((pointer) (&o))[7] = ((pointer) (&r))[0];

    return o;
}

uint_256 EndianMachine::FixUnsignedLongLongEndianness(uint_256 r)
{
    if (bigEndian) return r;

    uint_256 o;
    ((pointer) (&o))[0] = ((pointer) (&r))[7];
    ((pointer) (&o))[1] = ((pointer) (&r))[6];
    ((pointer) (&o))[2] = ((pointer) (&r))[5];
    ((pointer) (&o))[3] = ((pointer) (&r))[4];
    ((pointer) (&o))[4] = ((pointer) (&r))[3];
    ((pointer) (&o))[5] = ((pointer) (&r))[2];
    ((pointer) (&o))[6] = ((pointer) (&r))[1];
    ((pointer) (&o))[7] = ((pointer) (&r))[0];

    return o;
}

int_256 EndianMachine::FixLongLongEndianness(int_256 r)
{
    if (bigEndian) return r;

    int_128 o;
    ((pointer) (&o))[0] = ((pointer) (&r))[7];
    ((pointer) (&o))[1] = ((pointer) (&r))[6];
    ((pointer) (&o))[2] = ((pointer) (&r))[5];
    ((pointer) (&o))[3] = ((pointer) (&r))[4];
    ((pointer) (&o))[4] = ((pointer) (&r))[3];
    ((pointer) (&o))[5] = ((pointer) (&r))[2];
    ((pointer) (&o))[6] = ((pointer) (&r))[1];
    ((pointer) (&o))[7] = ((pointer) (&r))[0];

    return o;
}

flt_32 EndianMachine::FixFloatEndianness(flt_32 r)
{
    if (bigEndian) return r;

    flt_32 o;
    ((pointer) (&o))[0] = ((pointer) (&r))[3];
    ((pointer) (&o))[1] = ((pointer) (&r))[2];
    ((pointer) (&o))[2] = ((pointer) (&r))[1];
    ((pointer) (&o))[3] = ((pointer) (&r))[0];

    return o;
}

flt_64 EndianMachine::FixDoubleEndianness(flt_64 r)
{
    if (bigEndian) return r;

    flt_64 o;
    ((pointer) (&o))[0] = ((pointer) (&r))[7];
    ((pointer) (&o))[1] = ((pointer) (&r))[6];
    ((pointer) (&o))[2] = ((pointer) (&r))[5];
    ((pointer) (&o))[3] = ((pointer) (&r))[4];
    ((pointer) (&o))[4] = ((pointer) (&r))[3];
    ((pointer) (&o))[5] = ((pointer) (&r))[2];
    ((pointer) (&o))[6] = ((pointer) (&r))[1];
    ((pointer) (&o))[7] = ((pointer) (&r))[0];

    return o;
}

flt_128 EndianMachine::FixDoubleFloatEndianness(flt_128 r)
{
    if (bigEndian) return r;

    flt_128 o;
    ((pointer) (&o))[0] = ((pointer) (&r))[7];
    ((pointer) (&o))[1] = ((pointer) (&r))[6];
    ((pointer) (&o))[2] = ((pointer) (&r))[5];
    ((pointer) (&o))[3] = ((pointer) (&r))[4];
    ((pointer) (&o))[4] = ((pointer) (&r))[3];
    ((pointer) (&o))[5] = ((pointer) (&r))[2];
    ((pointer) (&o))[6] = ((pointer) (&r))[1];
    ((pointer) (&o))[7] = ((pointer) (&r))[0];

    return o;
}

flt_256 EndianMachine::FixDoubleDoubleEndianness(flt_256 r)
{
    if (bigEndian) return r;

    flt_256 o;
    ((pointer) (&o))[0] = ((pointer) (&r))[7];
    ((pointer) (&o))[1] = ((pointer) (&r))[6];
    ((pointer) (&o))[2] = ((pointer) (&r))[5];
    ((pointer) (&o))[3] = ((pointer) (&r))[4];
    ((pointer) (&o))[4] = ((pointer) (&r))[3];
    ((pointer) (&o))[5] = ((pointer) (&r))[2];
    ((pointer) (&o))[6] = ((pointer) (&r))[1];
    ((pointer) (&o))[7] = ((pointer) (&r))[0];

    return o;
}

uint_16 EndianMachine::UnsignedShortFromBytes(uint_8 a, uint_8 b)
{
    if (bigEndian) return ((uint_16*) ((uint_8[2]) {a, b}))[0];
    return ((uint_16*) ((uint_8[2]) {b, a}))[0];
}

uint_32 EndianMachine::UnsignedIntFromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d)
{
    if (bigEndian) return ((uint_32*) ((uint_8[4]) {a, b, c, d}))[0];
    return ((uint_32*) ((uint_8[4]) {d, c, b, a}))[0];
}

uint_64 EndianMachine::UnsignedLongFromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d, uint_8 e, uint_8 f, uint_8 g,
                                             uint_8 h)
{
    if (bigEndian) return ((uint_64*) ((uint_8[8]) {a, b, c, d, e, f, g, h}))[0];
    return ((uint_64*) ((uint_8[8]) {h, g, f, e, d, c, b, a}))[0];
}

uint_128 EndianMachine::UnsignedLongIntFromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d, uint_8 e, uint_8 f, uint_8 g,
                                                 uint_8 h, uint_8 i, uint_8 j, uint_8 k, uint_8 l, uint_8 m, uint_8 n,
                                                 uint_8 o, uint_8 p)
{
    if (bigEndian) return ((uint_64*) ((uint_8[8]) {a, b, c, d, e, f, g, h}))[0];
    return ((uint_64*) ((uint_8[8]) {h, g, f, e, d, c, b, a}))[0];
}

uint_256 EndianMachine::UnsignedLongLongFromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d, uint_8 e, uint_8 f, uint_8 g,
                                                  uint_8 h, uint_8 i, uint_8 j, uint_8 k, uint_8 l, uint_8 m, uint_8 n,
                                                  uint_8 o, uint_8 p)
{
    if (bigEndian) return ((uint_64*) ((uint_8[8]) {a, b, c, d, e, f, g, h}))[0];
    return ((uint_64*) ((uint_8[8]) {h, g, f, e, d, c, b, a}))[0];
}


int_16 EndianMachine::ShortFromBytes(uint_8 a, uint_8 b)
{
    if (bigEndian) return ((int_16*) ((uint_8[2]) {a, b}))[0];
    return ((int_16*) ((uint_8[2]) {b, a}))[0];
}

int_32 EndianMachine::IntFromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d)
{
    if (bigEndian) return ((int_32*) ((uint_8[4]) {a, b, c, d}))[0];
    return ((int_32*) ((uint_8[4]) {d, c, b, a}))[0];
}

int_64 EndianMachine::LongFromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d, uint_8 e, uint_8 f, uint_8 g, uint_8 h)
{
    if (bigEndian) return ((int_64*) ((uint_8[8]) {a, b, c, d, e, f, g, h}))[0];
    return ((int_64*) ((uint_8[8]) {h, g, f, e, d, c, b, a}))[0];
}

int_128 EndianMachine::LongIntFromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d, uint_8 e, uint_8 f, uint_8 g, uint_8 h, uint_8 i, uint_8 j, uint_8 k, uint_8 l, uint_8 m, uint_8 n, uint_8 o, uint_8 p)
{
    if (bigEndian) return ((int_64*) ((uint_8[8]) {a, b, c, d, e, f, g, h}))[0];
    return ((int_64*) ((uint_8[8]) {h, g, f, e, d, c, b, a}))[0];
}

int_256 EndianMachine::LongLongFromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d, uint_8 e, uint_8 f, uint_8 g, uint_8 h, uint_8 i, uint_8 j, uint_8 k, uint_8 l, uint_8 m, uint_8 n, uint_8 o, uint_8 p)
{
    if (bigEndian) return ((int_64*) ((uint_8[8]) {a, b, c, d, e, f, g, h}))[0];
    return ((int_64*) ((uint_8[8]) {h, g, f, e, d, c, b, a}))[0];
}

flt_32 EndianMachine::FloatFromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d)
{
    if (bigEndian) return ((flt_32*) ((uint_8[4]) {a, b, c, d}))[0];
    return ((flt_32*) ((uint_8[4]) {d, c, b, a}))[0];
}

flt_64 EndianMachine::DoubleFromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d, uint_8 e, uint_8 f, uint_8 g, uint_8 h)
{
    if (bigEndian) return ((flt_64*) ((uint_8[8]) {a, b, c, d, e, f, g, h}))[0];
    return ((flt_64*) ((uint_8[8]) {h, g, f, e, d, c, b, a}))[0];
}

flt_128 EndianMachine::DoubleFloatFromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d, uint_8 e, uint_8 f, uint_8 g, uint_8 h, uint_8 i, uint_8 j, uint_8 k, uint_8 l, uint_8 m, uint_8 n, uint_8 o, uint_8 p)
{
    if (bigEndian) return ((flt_64*) ((uint_8[8]) {a, b, c, d, e, f, g, h}))[0];
    return ((flt_64*) ((uint_8[8]) {h, g, f, e, d, c, b, a}))[0];
}

flt_256 EndianMachine::DoubleDoubleFromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d, uint_8 e, uint_8 f, uint_8 g, uint_8 h, uint_8 i, uint_8 j, uint_8 k, uint_8 l, uint_8 m, uint_8 n, uint_8 o, uint_8 p)
{
    if (bigEndian) return ((flt_64*) ((uint_8[8]) {a, b, c, d, e, f, g, h}))[0];
    return ((flt_64*) ((uint_8[8]) {h, g, f, e, d, c, b, a}))[0];
}

uint_40 EndianMachine::UnsignedInt40FromBytes(uint_8 d, uint_8 e, uint_8 f, uint_8 g, uint_8 h)
{
    if (bigEndian) return uint_40(((uint_64*) ((uint_8[8]) {0, 0, 0, d, e, f, g, h}))[0]);
    return uint_40(((uint_64*) ((uint_8[8]) {h, g, f, e, d, 0, 0, 0}))[0]);
}

bool EndianMachine::isBigEndian()
{
    return bigEndian;
}
