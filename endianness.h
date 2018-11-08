//
// Created by Riverssen on 08.11.18.
//

#ifndef MOCHAVM_ENDIANNESS_H
#define MOCHAVM_ENDIANNESS_H

#include "types.h"

/**
 * This class assumes all input is in BigEndian order,
 * if it isn't, errors will occur;
 * however any input will be converted to the
 * machines native endianness.
 */
class EndianMachine
{
private:
    bool bigEndian;
public:
    EndianMachine();
    uint_16     FixUnsignedShortEndianness(uint_16);
    uint_32     FixUnsignedIntEndianness(uint_32);
    uint_64     FixUnsignedLongEndianness(uint_64);
    uint_128    FixUnsignedLongIntEndianness(uint_128);
    uint_256    FixUnsignedLongLongEndianness(uint_256);

    int_16     FixShortEndianness(int_16);
    int_32     FixIntEndianness(int_32);
    int_64     FixLongEndianness(int_64);
    int_128    FixLongIntEndianness(int_128);
    int_256    FixLongLongEndianness(int_256);

    flt_32     FixFloatEndianness(flt_32);
    flt_64     FixDoubleEndianness(flt_64);
    flt_128    FixDoubleFloatEndianness(flt_128);
    flt_256    FixDoubleDoubleEndianness(flt_256);

    /** return an unsigned short from BigEndian ordered bytes **/
    uint_16 UnsignedShortFromBytes(uint_8 a, uint_8 b);
    /** return an unsigned int from BigEndian ordered bytes **/
    uint_32 UnsignedIntFromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d);
    /** return an unsigned long from BigEndian ordered bytes **/
    uint_64 UnsignedLongFromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d, uint_8 e, uint_8 f, uint_8 g, uint_8 h);
    /** return an unsigned long int from BigEndian ordered bytes **/
    uint_128 UnsignedLongIntFromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d, uint_8 e, uint_8 f, uint_8 g, uint_8 h,
                                      uint_8 i, uint_8 j, uint_8 k, uint_8 l, uint_8 m, uint_8 n, uint_8 o, uint_8 p);
    /** return an unsigned long long from BigEndian ordered bytes **/
    uint_256 UnsignedLongLongFromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d, uint_8 e, uint_8 f, uint_8 g, uint_8 h,
                                       uint_8 i, uint_8 j, uint_8 k, uint_8 l, uint_8 m, uint_8 n, uint_8 o, uint_8 p);
    /** return a short from BigEndian ordered bytes **/
    int_16 ShortFromBytes(uint_8 a, uint_8 b);
    /** return an int from BigEndian ordered bytes **/
    int_32 IntFromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d);
    /** return a long from BigEndian ordered bytes **/
    int_64 LongFromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d, uint_8 e, uint_8 f, uint_8 g, uint_8 h);
    /** return a long int from BigEndian ordered bytes **/
    int_128 LongIntFromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d, uint_8 e, uint_8 f, uint_8 g, uint_8 h, uint_8 i, uint_8 j, uint_8 k, uint_8 l, uint_8 m, uint_8 n, uint_8 o, uint_8 p);
    /** return a long long from BigEndian ordered bytes **/
    int_256 LongLongFromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d, uint_8 e, uint_8 f, uint_8 g, uint_8 h, uint_8 i, uint_8 j, uint_8 k, uint_8 l, uint_8 m, uint_8 n, uint_8 o, uint_8 p);
    /** return a float from BigEndian ordered bytes **/
    flt_32 FloatFromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d);
    /** return a double from BigEndian ordered bytes **/
    flt_64 DoubleFromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d, uint_8 e, uint_8 f, uint_8 g, uint_8 h);
    /** return a double float from BigEndian ordered bytes **/
    flt_128 DoubleFloatFromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d, uint_8 e, uint_8 f, uint_8 g, uint_8 h, uint_8 i, uint_8 j, uint_8 k, uint_8 l, uint_8 m, uint_8 n, uint_8 o, uint_8 p);
    /** return a double double from BigEndian ordered bytes **/
    flt_256 DoubleDoubleFromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d, uint_8 e, uint_8 f, uint_8 g, uint_8 h, uint_8 i, uint_8 j, uint_8 k, uint_8 l, uint_8 m, uint_8 n, uint_8 o, uint_8 p);

    uint_40 UnsignedInt40FromBytes(uint_8 a, uint_8 b, uint_8 c, uint_8 d, uint_8 e);
};


#endif //MOCHAVM_ENDIANNESS_H
