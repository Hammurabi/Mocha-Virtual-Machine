//
// Created by Riverssen on 05.11.18.
//

#ifndef MVM_EXECUTOR_H
#define MVM_EXECUTOR_H

#include <stack>
#include <map>
#include "opcodes.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>

/**
 * All MochaXX types
 */

#include "types.h"
#include "endianness.h"

struct mmstring{
    const uint_16 length;
    const char *  string;

    mmstring(uint_16 size, const char * data) : length(size), string(data)
    {
    }

    ~mmstring()
    {
        delete (string);
    }
};

/**
 * Not a real stack, acts as a queue.
 */
struct OP_STACK {
    unsigned char* ops;
    unsigned long  length;
    unsigned long  address;
    EndianMachine  endianMachine;
    OP_STACK() : ops(nullptr), length(0), address(0) {}
    OP_STACK(unsigned char * ops_p, unsigned long ops_l) : ops(ops_p), length(ops_l), address(0) {}
    OP_STACK(const OP_STACK& o) : ops(o.ops), length(o.length), address(o.address) {}

    uint_8 getUnsignedByte()
    {
        return ops[address ++];
    }
    uint_16 getUnsignedShort()
    {
        return endianMachine.UnsignedShortFromBytes(ops[address++], ops[address++]);
    }
    uint_32 getUnsignedInt()
    {
        return endianMachine.UnsignedIntFromBytes(ops[address++], ops[address++], ops[address++], ops[address++]);
    }
    uint_64 getUnsignedLong()
    {
        return endianMachine.UnsignedLongFromBytes(ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++]);
    }
    uint_128 getUnsignedLongInt()
    {
        return endianMachine.UnsignedLongIntFromBytes(ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++]);
    }
    uint_256 getUnsignedLongLong()
    {
        return endianMachine.UnsignedLongLongFromBytes(ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++], ops[address++]);
    }

    int_8 getByte()
    {
            return ops[address ++];
    }
    int_16 getShort()
    {
        return endianMachine.ShortFromBytes(ops[address ++], ops[address ++]);
    }
    int_32 getInt()
    {
        return endianMachine.IntFromBytes(ops[address ++], ops[address ++], ops[address ++], ops[address ++]);
    }
    int_64 getLong()
    {
        return endianMachine.LongFromBytes(ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++]);
    }
    int_128 getLongInt()
    {
        return endianMachine.LongIntFromBytes(ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++]);
    }
    int_256 getLongLong()
    {
        return endianMachine.LongLongFromBytes(ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++]);
    }

    flt_128 getDoubleFloat()
    {
        return endianMachine.DoubleFloatFromBytes(ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++]);
    }
    flt_256 getDoubleDouble()
    {
        return endianMachine.DoubleDoubleFromBytes(ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++]);
    }

    flt_32 getFloat()
    {
        return endianMachine.FloatFromBytes(ops[address ++], ops[address ++], ops[address ++], ops[address ++]);
    }
    flt_64 getDouble()
    {
        return endianMachine.DoubleFromBytes(ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++], ops[address ++]);
    }
    pointer getPointer()
    {
        return (pointer) (intptr_t) getUnsignedLong();
    }
    Op getOp()
    {
        return static_cast<Op>(getUnsignedShort());
    }
    uint_40 getUnsignedInt40()
    {
        return endianMachine.UnsignedInt40FromBytes(getUnsignedByte(), getUnsignedByte(), getUnsignedByte(), getUnsignedByte(), getUnsignedByte());
    }

    unsigned long getRemaining()
    {
        return length - address;
    }
    unsigned long getLength()
    {
        return length;
    }
    pointer getMMString()
    {
        uint_16 length = getUnsignedShort();
        char * str = new char[length];

        for (int i = 0; i < length; i ++)
            str[i] = getByte();

        mmstring* string = new mmstring(length, str);

        return (pointer) string;
    }
};
/**
 * A modified stack with a subscript operator.
 */
#ifdef MACRO_STACK_DEF
struct std_stack : public std::stack<uint_8>
{
    using std::stack<unsigned char>::c;

    uint_8& operator[] (const unsigned int index)
    {
        return c[index];
    }
};
#else
struct std_stack : public std::stack<uint_64>
{
    using std::stack<uint_64>::c;

    uint_64& operator[] (const unsigned int index)
    {
        return c[index];
    }
};
#endif

/**
 * A higher level stack to peek/pop/push all native mocha types.
 */
#ifdef MACRO_STACK_DEF
struct Stack{
    std_stack stack;

    void swapBytes()
    {
        uint_8 b = pop();
        uint_8 a = pop();

        push(b);
        push(a);
    }

    void push(uint_8 c)
    {
        stack.push(c);
    }

    void pushByte(int_8 c)
    {
        stack.push(static_cast<uint_8> (c));
    }

    void pushUnsignedByte(uint_8 c)
    {
        stack.push(c);
    }

    void pushUnsignedShort(uint_16 s)
    {
        push(((unsigned char*) (&s)) [0]);
        push(((unsigned char*) (&s)) [1]);
    }

    void pushUnsignedInt(uint_32 s)
    {
        push(((unsigned char*) (&s)) [0]);
        push(((unsigned char*) (&s)) [1]);
        push(((unsigned char*) (&s)) [2]);
        push(((unsigned char*) (&s)) [3]);
    }

    void pushUnsignedLong(uint_64 s)
    {
        push(((unsigned char*) (&s)) [0]);
        push(((unsigned char*) (&s)) [1]);
        push(((unsigned char*) (&s)) [2]);
        push(((unsigned char*) (&s)) [3]);
        push(((unsigned char*) (&s)) [4]);
        push(((unsigned char*) (&s)) [5]);
        push(((unsigned char*) (&s)) [6]);
        push(((unsigned char*) (&s)) [7]);
    }

    void pushUnsignedLongInt(uint_128 s)
    {
        push(((unsigned char*) (&s)) [0]);
        push(((unsigned char*) (&s)) [1]);
        push(((unsigned char*) (&s)) [2]);
        push(((unsigned char*) (&s)) [3]);
        push(((unsigned char*) (&s)) [4]);
        push(((unsigned char*) (&s)) [5]);
        push(((unsigned char*) (&s)) [6]);
        push(((unsigned char*) (&s)) [7]);
    }

    void pushUnsignedLongLong(uint_256 s)
    {
        push(((unsigned char*) (&s)) [0]);
        push(((unsigned char*) (&s)) [1]);
        push(((unsigned char*) (&s)) [2]);
        push(((unsigned char*) (&s)) [3]);
        push(((unsigned char*) (&s)) [4]);
        push(((unsigned char*) (&s)) [5]);
        push(((unsigned char*) (&s)) [6]);
        push(((unsigned char*) (&s)) [7]);
    }

    void pushShort(int_16 s)
    {
        push(((unsigned char*) (&s)) [0]);
        push(((unsigned char*) (&s)) [1]);
    }

    void pushInt(int_32 s)
    {
        push(((unsigned char*) (&s)) [0]);
        push(((unsigned char*) (&s)) [1]);
        push(((unsigned char*) (&s)) [2]);
        push(((unsigned char*) (&s)) [3]);
    }

    void pushLong(int_64 s)
    {
        push(((unsigned char*) (&s)) [0]);
        push(((unsigned char*) (&s)) [1]);
        push(((unsigned char*) (&s)) [2]);
        push(((unsigned char*) (&s)) [3]);
        push(((unsigned char*) (&s)) [4]);
        push(((unsigned char*) (&s)) [5]);
        push(((unsigned char*) (&s)) [6]);
        push(((unsigned char*) (&s)) [7]);
    }

    void pushLongInt(int_128 s)
    {
        push(((unsigned char*) (&s)) [0]);
        push(((unsigned char*) (&s)) [1]);
        push(((unsigned char*) (&s)) [2]);
        push(((unsigned char*) (&s)) [3]);
        push(((unsigned char*) (&s)) [4]);
        push(((unsigned char*) (&s)) [5]);
        push(((unsigned char*) (&s)) [6]);
        push(((unsigned char*) (&s)) [7]);
    }

    void pushLongLong(int_256 s)
    {
        push(((unsigned char*) (&s)) [0]);
        push(((unsigned char*) (&s)) [1]);
        push(((unsigned char*) (&s)) [2]);
        push(((unsigned char*) (&s)) [3]);
        push(((unsigned char*) (&s)) [4]);
        push(((unsigned char*) (&s)) [5]);
        push(((unsigned char*) (&s)) [6]);
        push(((unsigned char*) (&s)) [7]);
    }

    void pushFloat(flt_32 s)
    {
        push(static_cast<uint_8>(((unsigned char*) (&s)) [0]));
        push(static_cast<uint_8>(((unsigned char*) (&s)) [1]));
        push(static_cast<uint_8>(((unsigned char*) (&s)) [2]));
        push(static_cast<uint_8>(((unsigned char*) (&s)) [3]));
    }

    void pushDouble(flt_64 s)
    {
        push(static_cast<uint_8>(((unsigned char*) (&s)) [0]));
        push(static_cast<uint_8>(((unsigned char*) (&s)) [1]));
        push(static_cast<uint_8>(((unsigned char*) (&s)) [2]));
        push(static_cast<uint_8>(((unsigned char*) (&s)) [3]));
        push(static_cast<uint_8>(((unsigned char*) (&s)) [4]));
        push(static_cast<uint_8>(((unsigned char*) (&s)) [5]));
        push(static_cast<uint_8>(((unsigned char*) (&s)) [6]));
        push(static_cast<uint_8>(((unsigned char*) (&s)) [7]));
    }

    void pushDoubleFloat(flt_64 s)
    {
        push(static_cast<uint_8>(((unsigned char*) (&s)) [0]));
        push(static_cast<uint_8>(((unsigned char*) (&s)) [1]));
        push(static_cast<uint_8>(((unsigned char*) (&s)) [2]));
        push(static_cast<uint_8>(((unsigned char*) (&s)) [3]));
        push(static_cast<uint_8>(((unsigned char*) (&s)) [4]));
        push(static_cast<uint_8>(((unsigned char*) (&s)) [5]));
        push(static_cast<uint_8>(((unsigned char*) (&s)) [6]));
        push(static_cast<uint_8>(((unsigned char*) (&s)) [7]));
    }

    void pushDoubleDouble(flt_64 s)
    {
        push(static_cast<uint_8>(((unsigned char*) (&s)) [0]));
        push(static_cast<uint_8>(((unsigned char*) (&s)) [1]));
        push(static_cast<uint_8>(((unsigned char*) (&s)) [2]));
        push(static_cast<uint_8>(((unsigned char*) (&s)) [3]));
        push(static_cast<uint_8>(((unsigned char*) (&s)) [4]));
        push(static_cast<uint_8>(((unsigned char*) (&s)) [5]));
        push(static_cast<uint_8>(((unsigned char*) (&s)) [6]));
        push(static_cast<uint_8>(((unsigned char*) (&s)) [7]));
    }

    void pushPointer(pointer p)
    {
        pushUnsignedLong((uint_64)(intptr_t)p);
    }

    uint_8 pop()
    {
        if (stack.size() <= 0)
        {
            std::cerr << "stack underflow" << std::endl;
            exit(0);
        }
        uint_8 c = stack.top();
        stack.pop();
        return c;
    }

    uint_8 popUnsignedByte()
    {
        return pop();
    }

    uint_16 popUnsignedShort()
    {
        /** stack[short[a, b]] **/
        uint_8 b = pop();
        uint_8 a = pop();
        return *((uint_16 *) ((uint_8[2]) {a, b}));
    }

    uint_32 popUnsignedInt()
    {
        /** stack[int[a, b, c, d]] **/
        uint_8 d = pop();
        uint_8 c = pop();
        uint_8 b = pop();
        uint_8 a = pop();
        return *((uint_32 *) ((uint_8[4]) {a, b, c, d}));
    }

    uint_64 popUnsignedLong()
    {
        /** stack[int[a, b, c, d, e, f, g, h]] **/
        uint_8 h = pop();
        uint_8 g = pop();
        uint_8 f = pop();
        uint_8 e = pop();
        uint_8 d = pop();
        uint_8 c = pop();
        uint_8 b = pop();
        uint_8 a = pop();
        return *((uint_64 *) ((uint_8[8]) {a, b, c, d, e, f, g, h}));
    }

    uint_128 popUnsignedLongInt()
    {
        /** stack[int[a, b, c, d, e, f, g, h]] **/
        uint_8 h = pop();
        uint_8 g = pop();
        uint_8 f = pop();
        uint_8 e = pop();
        uint_8 d = pop();
        uint_8 c = pop();
        uint_8 b = pop();
        uint_8 a = pop();
        return uint_128();//*((uint_64 *) ((uint_8[8]) {a, b, c, d, e, f, g, h}));
    }

    uint_256 popUnsignedLongLong()
    {
        /** stack[int[a, b, c, d, e, f, g, h]] **/
        uint_8 h = pop();
        uint_8 g = pop();
        uint_8 f = pop();
        uint_8 e = pop();
        uint_8 d = pop();
        uint_8 c = pop();
        uint_8 b = pop();
        uint_8 a = pop();
        return uint_256();//*((uint_64 *) ((uint_8[8]) {a, b, c, d, e, f, g, h}));
    }


    int_8 popByte()
    {
        return static_cast<int_8> (pop());
    }

    int_16 popShort()
    {
        /** stack[short[a, b]] **/
        uint_8 b = pop();
        uint_8 a = pop();
        return *((int_16 *) ((uint_8[2]) {a, b}));
    }

    int_32 popInt()
    {
        /** stack[int[a, b, c, d]] **/
        uint_8 d = pop();
        uint_8 c = pop();
        uint_8 b = pop();
        uint_8 a = pop();
        return *((int_32 *) ((uint_8[4]) {a, b, c, d}));
    }

    int_64 popLong()
    {
        /** stack[int[a, b, c, d, e, f, g, h]] **/
        uint_8 h = pop();
        uint_8 g = pop();
        uint_8 f = pop();
        uint_8 e = pop();
        uint_8 d = pop();
        uint_8 c = pop();
        uint_8 b = pop();
        uint_8 a = pop();
        return *((int_64 *) ((uint_8[8]) {a, b, c, d, e, f, g, h}));
    }

    int_128 popLongInt()
    {
        /** stack[int[a, b, c, d, e, f, g, h]] **/
        uint_8 h = pop();
        uint_8 g = pop();
        uint_8 f = pop();
        uint_8 e = pop();
        uint_8 d = pop();
        uint_8 c = pop();
        uint_8 b = pop();
        uint_8 a = pop();
        return int_128();//*((uint_64 *) ((uint_8[8]) {a, b, c, d, e, f, g, h}));
    }

    int_256 popLongLong()
    {
        /** stack[int[a, b, c, d, e, f, g, h]] **/
        uint_8 h = pop();
        uint_8 g = pop();
        uint_8 f = pop();
        uint_8 e = pop();
        uint_8 d = pop();
        uint_8 c = pop();
        uint_8 b = pop();
        uint_8 a = pop();
        return int_256();//*((uint_64 *) ((uint_8[8]) {a, b, c, d, e, f, g, h}));
    }

    flt_32 popFloat()
    {
        /** stack[int[a, b, c, d]] **/
        uint_8 d = pop();
        uint_8 c = pop();
        uint_8 b = pop();
        uint_8 a = pop();
        return *((flt_32 *) ((uint_8[4]) {a, b, c, d}));
    }

    flt_64 popDouble()
    {
        /** stack[int[a, b, c, d, e, f, g, h]] **/
        uint_8 h = pop();
        uint_8 g = pop();
        uint_8 f = pop();
        uint_8 e = pop();
        uint_8 d = pop();
        uint_8 c = pop();
        uint_8 b = pop();
        uint_8 a = pop();
        return *((flt_64 *) ((uint_8[8]) {a, b, c, d, e, f, g, h}));
    }

    flt_128 popDoubleFloat()
    {
        /** stack[int[a, b, c, d, e, f, g, h]] **/
        uint_8 h = pop();
        uint_8 g = pop();
        uint_8 f = pop();
        uint_8 e = pop();
        uint_8 d = pop();
        uint_8 c = pop();
        uint_8 b = pop();
        uint_8 a = pop();
        return flt_128();//*((flt_64 *) ((uint_8[8]) {a, b, c, d, e, f, g, h}));
    }

    flt_256 popDoubleDouble()
    {
        /** stack[int[a, b, c, d, e, f, g, h]] **/
        uint_8 h = pop();
        uint_8 g = pop();
        uint_8 f = pop();
        uint_8 e = pop();
        uint_8 d = pop();
        uint_8 c = pop();
        uint_8 b = pop();
        uint_8 a = pop();
        return flt_256();//*((flt_64 *) ((uint_8[8]) {a, b, c, d, e, f, g, h}));
    }

    pointer popPointer()
    {
        return (pointer) (intptr_t) popUnsignedLong();
    }

    uint_8 peek()
    {
        uint_8 c = stack.top();
        return c;
    }

    int_8 peekByte()
    {
        int_8 c = static_cast<int_8> (stack.top());

        return c;
    }

    uint_8 peekUnsignedByte()
    {
        uint_8 c = stack.top();
        return c;
    }

    int_16 peekShort()
    {
        /** stack[short[a, b]] **/
        uint_8 b = peek();
        uint_8 a = stack[stack.size() - 2];
        return *((int_16 *) ((uint_8[2]) {a, b}));
    }

    uint_16 peekUnsignedShort()
    {
        /** stack[short[a, b]] **/
        uint_8 b = peek();
        uint_8 a = stack[stack.size() - 2];
        return *((uint_16 *) ((uint_8[2]) {a, b}));
    }

    int_32 peekInt()
    {
        /** stack[int[a, b, c, d]] **/
        uint_8 d = peek();
        uint_8 c = stack[stack.size() - 2];
        uint_8 b = stack[stack.size() - 3];
        uint_8 a = stack[stack.size() - 4];
        return *((int_32 *) ((uint_8[4]) {a, b, c, d}));
    }

    uint_32 peekUnsignedInt()
    {
        /** stack[int[a, b, c, d]] **/
        uint_8 d = peek();
        uint_8 c = stack[stack.size() - 2];
        uint_8 b = stack[stack.size() - 3];
        uint_8 a = stack[stack.size() - 4];
        return *((uint_32 *) ((uint_8[4]) {a, b, c, d}));
    }

    int_64 peekLong()
    {
        /** stack[int[a, b, c, d, e, f, g, h]] **/
        uint_8 h = peek();
        uint_8 g = stack[stack.size() - 2];
        uint_8 f = stack[stack.size() - 3];
        uint_8 e = stack[stack.size() - 4];
        uint_8 d = stack[stack.size() - 5];
        uint_8 c = stack[stack.size() - 6];
        uint_8 b = stack[stack.size() - 7];
        uint_8 a = stack[stack.size() - 8];
        return *((int_64 *) ((uint_8[8]) {a, b, c, d, e, f, g, h}));
    }

    uint_64 peekUnsignedLong()
    {
        /** stack[int[a, b, c, d, e, f, g, h]] **/
        uint_8 h = peek();
        uint_8 g = stack[stack.size() - 2];
        uint_8 f = stack[stack.size() - 3];
        uint_8 e = stack[stack.size() - 4];
        uint_8 d = stack[stack.size() - 5];
        uint_8 c = stack[stack.size() - 6];
        uint_8 b = stack[stack.size() - 7];
        uint_8 a = stack[stack.size() - 8];
        return *((uint_64 *) ((uint_8[8]) {a, b, c, d, e, f, g, h}));
    }

    int_128 peekLongInt()
    {
        /** stack[int[a, b, c, d, e, f, g, h]] **/
        uint_8 h = peek();
        uint_8 g = stack[stack.size() - 2];
        uint_8 f = stack[stack.size() - 3];
        uint_8 e = stack[stack.size() - 4];
        uint_8 d = stack[stack.size() - 5];
        uint_8 c = stack[stack.size() - 6];
        uint_8 b = stack[stack.size() - 7];
        uint_8 a = stack[stack.size() - 8];
        return *((int_128 *) ((uint_8[8]) {a, b, c, d, e, f, g, h}));
    }

    uint_128 peekUnsignedLongInt()
    {
        /** stack[int[a, b, c, d, e, f, g, h]] **/
        uint_8 h = peek();
        uint_8 g = stack[stack.size() - 2];
        uint_8 f = stack[stack.size() - 3];
        uint_8 e = stack[stack.size() - 4];
        uint_8 d = stack[stack.size() - 5];
        uint_8 c = stack[stack.size() - 6];
        uint_8 b = stack[stack.size() - 7];
        uint_8 a = stack[stack.size() - 8];
        return *((uint_128 *) ((uint_8[8]) {a, b, c, d, e, f, g, h}));
    }

    int_256 peekLongLong()
    {
        /** stack[int[a, b, c, d, e, f, g, h]] **/
        uint_8 h = peek();
        uint_8 g = stack[stack.size() - 2];
        uint_8 f = stack[stack.size() - 3];
        uint_8 e = stack[stack.size() - 4];
        uint_8 d = stack[stack.size() - 5];
        uint_8 c = stack[stack.size() - 6];
        uint_8 b = stack[stack.size() - 7];
        uint_8 a = stack[stack.size() - 8];
        return *((int_256 *) ((uint_8[8]) {a, b, c, d, e, f, g, h}));
    }

    uint_256 peekUnsignedLongLong()
    {
        /** stack[int[a, b, c, d, e, f, g, h]] **/
        uint_8 h = peek();
        uint_8 g = stack[stack.size() - 2];
        uint_8 f = stack[stack.size() - 3];
        uint_8 e = stack[stack.size() - 4];
        uint_8 d = stack[stack.size() - 5];
        uint_8 c = stack[stack.size() - 6];
        uint_8 b = stack[stack.size() - 7];
        uint_8 a = stack[stack.size() - 8];
        return *((uint_256 *) ((uint_8[8]) {a, b, c, d, e, f, g, h}));
    }

    flt_32 peekFloat()
    {
        /** stack[int[a, b, c, d]] **/
        uint_8 d = peek();
        uint_8 c = stack[stack.size() - 2];
        uint_8 b = stack[stack.size() - 3];
        uint_8 a = stack[stack.size() - 4];
        return *((flt_32 *) ((uint_8[4]) {a, b, c, d}));
    }

    flt_64 peekDouble()
    {
        /** stack[int[a, b, c, d, e, f, g, h]] **/
        uint_8 h = peek();
        uint_8 g = stack[stack.size() - 2];
        uint_8 f = stack[stack.size() - 3];
        uint_8 e = stack[stack.size() - 4];
        uint_8 d = stack[stack.size() - 5];
        uint_8 c = stack[stack.size() - 6];
        uint_8 b = stack[stack.size() - 7];
        uint_8 a = stack[stack.size() - 8];
        return *((flt_64 *) ((uint_8[8]) {a, b, c, d, e, f, g, h}));
    }

    flt_128 peekDoubleFloat()
    {
        /** stack[int[a, b, c, d, e, f, g, h]] **/
        uint_8 h = peek();
        uint_8 g = stack[stack.size() - 2];
        uint_8 f = stack[stack.size() - 3];
        uint_8 e = stack[stack.size() - 4];
        uint_8 d = stack[stack.size() - 5];
        uint_8 c = stack[stack.size() - 6];
        uint_8 b = stack[stack.size() - 7];
        uint_8 a = stack[stack.size() - 8];
        return *((flt_64 *) ((uint_8[8]) {a, b, c, d, e, f, g, h}));
    }

    flt_256 peekDoubleDouble()
    {
        /** stack[int[a, b, c, d, e, f, g, h]] **/
        uint_8 h = peek();
        uint_8 g = stack[stack.size() - 2];
        uint_8 f = stack[stack.size() - 3];
        uint_8 e = stack[stack.size() - 4];
        uint_8 d = stack[stack.size() - 5];
        uint_8 c = stack[stack.size() - 6];
        uint_8 b = stack[stack.size() - 7];
        uint_8 a = stack[stack.size() - 8];
        return *((flt_64 *) ((uint_8[8]) {a, b, c, d, e, f, g, h}));
    }

    pointer peekPointer();
};
#else
struct Stack{
    std_stack stack;

    void swapBytes()
    {
        uint_64 b = popUnsignedLong();
        uint_64 a = popUnsignedLong();

        push(b);
        push(a);
    }

    void push(uint_8 c)
    {
        pushUnsignedLong(c);
    }

    void pushByte(int_8 c)
    {
        pushUnsignedLong(c);
    }

    void pushUnsignedByte(uint_8 c)
    {
        pushUnsignedLong(c);
    }

    void pushUnsignedShort(uint_16 s)
    {
        pushUnsignedLong(s);
    }

    void pushUnsignedInt(uint_32 s)
    {
        pushUnsignedLong(s);
    }

    void pushUnsignedLong(uint_64 s)
    {
        stack.push(s);
    }

    void pushUnsignedLongInt(uint_128 s)
    {
    }

    void pushUnsignedLongLong(uint_256 s)
    {
    }

    void pushShort(int_16 s)
    {
        pushUnsignedLong(s);
    }

    void pushInt(int_32 s)
    {
        pushUnsignedLong(s);
    }

    void pushLong(int_64 s)
    {
        pushUnsignedLong(s);
    }

    void pushLongInt(int_128 s)
    {
    }

    void pushLongLong(int_256 s)
    {
    }

    void pushFloat(flt_32 s)
    {
        pointer p = (pointer) &s;
        pushUnsignedLong(*((uint_64 *) ((uint_8[8]) {p[0], p[1], p[2], p[3], 0, 0, 0, 0})));
    }

    void pushDouble(flt_64 s)
    {
        pointer p = (pointer) &s;
        pushUnsignedLong(*((uint_64 *) ((uint_8[8]) {p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]})));
    }

    void pushDoubleFloat(flt_64 s)
    {
    }

    void pushDoubleDouble(flt_64 s)
    {
    }

    void pushPointer(pointer p)
    {
        pushUnsignedLong((uint_64)(intptr_t)p);
    }

    uint_8 pop()
    {
        if (stack.size() <= 0)
        {
            std::cerr << "stack underflow" << std::endl;
            exit(0);
        }
        uint_8 c = stack.top();
        stack.pop();
        return c;
    }

    uint_8 popUnsignedByte()
    {
        return (uint_8)popUnsignedLong();
    }

    uint_16 popUnsignedShort()
    {
        return (uint_16)popUnsignedLong();
    }

    uint_32 popUnsignedInt()
    {
        return (uint_32)popUnsignedLong();
    }

    uint_64 popUnsignedLong()
    {
        uint_64 l = stack.top();
        stack.pop();
        return l;
    }

    uint_128 popUnsignedLongInt()
    {
        return popUnsignedLong();
    }

    uint_256 popUnsignedLongLong()
    {
        return popUnsignedLong();
    }


    int_8 popByte()
    {
        return (int_8)popUnsignedLong();
    }

    int_16 popShort()
    {
        return (int_16)popUnsignedLong();
    }

    int_32 popInt()
    {
        return (int_32)popUnsignedLong();
    }

    int_64 popLong()
    {
        return popUnsignedLong();
    }

    int_128 popLongInt()
    {
        return popUnsignedLong();
    }

    int_256 popLongLong()
    {
        return popUnsignedLong();
    }

    flt_32 popFloat()
    {
        uint_64 l = popUnsignedLong();
        pointer p = (pointer) &l;
        return *((flt_32 *) ((uint_8[8]) {p[0], p[1], p[2], p[3]}));
    }

    flt_64 popDouble()
    {
        uint_64 l = popUnsignedLong();
        pointer p = (pointer) &l;
        return *((flt_64 *) ((uint_8[8]) {p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]}));
    }

    flt_128 popDoubleFloat()
    {
        return flt_128();//*((flt_64 *) ((uint_8[8]) {a, b, c, d, e, f, g, h}));
    }

    flt_256 popDoubleDouble()
    {
        return flt_256();//*((flt_64 *) ((uint_8[8]) {a, b, c, d, e, f, g, h}));
    }

    pointer popPointer()
    {
        return (pointer) (intptr_t) popUnsignedLong();
    }

    uint_8 peek()
    {
        return (uint_8) peekUnsignedLong();
    }

    int_8 peekByte()
    {
        return (int_8) stack.top();
    }

    uint_8 peekUnsignedByte()
    {
        return (uint_8)stack.top();
    }

    int_16 peekShort()
    {
        return (int_16)stack.top();
    }

    uint_16 peekUnsignedShort()
    {
        return (uint_16)stack.top();
    }

    int_32 peekInt()
    {
        return (int_32)stack.top();
    }

    uint_32 peekUnsignedInt()
    {
        return (uint_32)stack.top();
    }

    int_64 peekLong()
    {
        return stack.top();
    }

    uint_64 peekUnsignedLong()
    {
        return stack.top();
    }

    int_128 peekLongInt()
    {
        return popUnsignedLong();
    }

    uint_128 peekUnsignedLongInt()
    {
        return popUnsignedLong();
    }

    int_256 peekLongLong()
    {
        return popUnsignedLong();
    }

    uint_256 peekUnsignedLongLong()
    {
        return popUnsignedLong();
    }

    flt_32 peekFloat()
    {
        uint_64 l = peekUnsignedLong();
        pointer p = (pointer) &l;
        return *((flt_32 *) ((uint_8[8]) {p[0], p[1], p[2], p[3]}));
    }

    flt_64 peekDouble()
    {
        uint_64 l = peekUnsignedLong();
        pointer p = (pointer) &l;
        return *((flt_64 *) ((uint_8[8]) {p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]}));
    }

    flt_128 peekDoubleFloat()
    {
        return *((flt_64 *) ((uint_8[8]) {0, 0, 0, 0, 0, 0, 0, 0}));
    }

    flt_256 peekDoubleDouble()
    {
        return *((flt_64 *) ((uint_8[8]) {0, 0, 0, 0, 0, 0, 0, 0}));
    }

    pointer peekPointer();
};
#endif

struct MochaNativeInterface{
    virtual void execute(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main)
    {
    }
};

struct Field{
    enum {
                UINT_8, UINT_16, UINT_32, UINT_64, UINT_128, UINT_256,
                INT_8, INT_16, INT_32, INT_64, INT_128, INT_256,
                POINTER, FLOAT, DOUBLE, FLOAT_128, FLOAT_256, BYTEARRAY,
                GCOBJECT
                }
            type;
    uint_32 address;
};

struct GenericClassInfo{
    const short             numParents;
    const GenericClassInfo**parents;
    const std::string       name;
    const short             numFields;
    const Field*            fields;
};

struct ObjectInfo{
    const GenericClassInfo* info;

    ObjectInfo()
    {
    }

    ObjectInfo(const ObjectInfo& o)
    {
    }
};

struct GCObject{
    ObjectInfo* info;
    pointer     data;

    GCObject(ObjectInfo i) : info(new ObjectInfo(i))
    {
    }
};

/**
 * The method's "scope"/
 */
struct Scope{
//    /**
//     * All operations
//     */
//    OP_STACK ops;
    /**
     * A stack that contains all objects within the scope.
     */
    Stack stack;
    /**
     * A local variable table that contains all objects and fields created inside a method (including arguments).
     */
    std::map<uint_32, localvarelement> lvt;
    /**
     * A local checkpoint table for easy jump instructions.
     */
    std::map<uint_32, uint_64> CHECK_POINTS;

    /** at the end of each round, the scope ptrs gets popped out of the stack and the shared_ptr references get released **/
    /**
     * Thus, all memory related instructions will check with scope_ptrs for safety,
     * whenever a pointer is returned and or set into a field, it will be removed from scope_ptrs
     * so it does not get deleted, however the usage of pointers in object fields will automatically
     * stop the automatic collection of pointers, and leave the rest to the programmer.
     *
     *
     * struct {
     * int * colours;
     * }
     *
     * void set()
     * {
     *          //This is unsafe.
     *  colours = getPointer();
     * }
     *
     * void set()
     * {
     *              //This is safe because the GC will handle the pointer when it goes out of scope.
     *  int * colours = getPointer();
     * }
     */
    #define scope_ptr_map std::map<uint_64, std::shared_ptr<uint_8>>
    #define ptr_touint(x) (uint_64) (intptr_t) x
    scope_ptr_map scope_ptrs;

//    pointer basePointer;
//    Scope* parent;
public:
//    Scope(pointer bp, Scope* pt) : basePointer(bp), parent(pt) {}
    Scope() {}
    Scope(const Scope& o) : stack(o.stack), lvt(o.lvt), CHECK_POINTS(o.CHECK_POINTS), scope_ptrs(o.scope_ptrs) /**basePointer(o.basePointer), parent(o.parent)**/ {}
    void erasepointer(pointer p)
    {
        scope_ptr_map::iterator ptr = scope_ptrs.find(ptr_touint(p));
        if (ptr != scope_ptrs.end())
            scope_ptrs.erase(ptr);
    }
    void amalloc(uint_64 s)
    {
        pointer p = (pointer) malloc(s);
        stack.pushPointer(p);
        scope_ptrs[(uint_64) (intptr_t) p] = (std::shared_ptr<uint_8 >(p));
    }
    void acalloc(uint_64 s, uint_64 l)
    {
        pointer p = (pointer) calloc(s, l);
        stack.pushPointer(p);
        scope_ptrs[(uint_64) (intptr_t) p] = (std::shared_ptr<uint_8 >(p));
    }
    void adelete(uint_64 s, uint_64 l)
    {
        pointer p = stack.popPointer();
        erasepointer(p);

        delete (p);
    }
    pointer returnPointer()
    {
        pointer p = stack.popPointer();
        erasepointer(p);

        return p;
    }

    inline void pushPointerSAFE(pointer p)
    {
        scope_ptrs[(uint_64) (intptr_t) p] = (std::shared_ptr<uint_8 >(p));
        stack.pushPointer(p);
    }

    inline void pushPointerUNSAFE(pointer p) { stack.pushPointer(p); }

    inline void pushByte(int_8 byte) { stack.pushByte(byte); }
    inline void pushUnsignedByte(uint_8 byte) { stack.pushUnsignedByte(byte); }
    inline void pushShort(int_16 byte) { stack.pushShort(byte); }
    inline void pushUnsignedShort(uint_16 byte) { stack.pushUnsignedShort(byte); }
    inline void pushInt(int_32 byte) { stack.pushInt(byte); }
    inline void pushUnsignedInt(uint_32 byte) { stack.pushUnsignedInt(byte); }
    inline void pushLong(int_64 byte) { stack.pushLong(byte); }
    inline void pushUnsignedLong(uint_64 byte) { stack.pushUnsignedLong(byte); }
    inline void pushLongInt(int_128 byte) { stack.pushLongInt(byte); }
    inline void pushUnsignedLongInt(uint_128 byte) { stack.pushUnsignedLongInt(byte); }
    inline void pushLongLong(int_256 byte) { stack.pushLongLong(byte); }
    inline void pushUnsignedLongLong(uint_256 byte) { stack.pushUnsignedLongLong(byte); }
//    inline void pushPointer(pointer p) { stack.pushPointer(p); }
    inline void pushFloat(flt_32 byte) { stack.pushFloat(byte); }
    inline void pushDouble(flt_64 byte) { stack.pushDouble(byte); }
    inline void pushDoubleFloat(flt_128 byte) { stack.pushDoubleFloat(byte); }
    inline void pushDoubleDouble(flt_256 byte) { stack.pushDoubleDouble(byte); }

    inline int_8    popByte() { return stack.popByte(); }
    inline uint_8   popUnsignedByte() { return stack.popUnsignedByte(); }
    inline int_16   popShort() { return stack.popShort(); }
    inline uint_16  popUnsignedShort() { return stack.popUnsignedShort(); }
    inline int_32   popInt() { return stack.popInt(); }
    inline uint_32  popUnsignedInt() { return stack.popUnsignedInt(); }
    inline int_64   popLong() { return stack.popLong(); }
    inline uint_64  popUnsignedLong() { return stack.popUnsignedLong(); }
    inline int_128  popLongInt() { return stack.popLongInt(); }
    inline uint_128 popUnsignedLongInt() { return stack.popUnsignedLongInt(); }
    inline int_256  popLongLong() { return stack.popLongLong(); }
    inline uint_256 popUnsignedLongLong() { return stack.popUnsignedLongLong(); }
    inline pointer  popPointer() { return stack.popPointer(); }
    inline flt_32   popFloat() { return stack.popFloat(); }
    inline flt_64   popDouble() { return stack.popDouble(); }
    inline flt_128  popDoubleFloat() { return stack.popDoubleFloat(); }
    inline flt_256  popDoubleDouble() { return stack.popDoubleDouble(); }

    inline void     storeByte(int_8 byte, uint_16 index) { localvarelement lve;             lve.Byte = byte;                            lvt[index] = lve; }
    inline void     storeUnsignedByte(uint_8 byte, uint_16 index) { localvarelement lve;    lve.UnsignedByte = byte;                    lvt[index] = lve; }
    inline void     storeShort(int_16 byte, uint_16 index) { localvarelement lve;           lve.Short = byte;                           lvt[index] = lve; }
    inline void     storeUnsignedShort(uint_16 byte, uint_16 index) { localvarelement lve;  lve.UnsignedShort = byte;                   lvt[index] = lve; }
    inline void     storeInt(int_32 byte, uint_16 index) { localvarelement lve;             lve.Int = byte;                             lvt[index] = lve; }
    inline void     storeUnsignedInt(uint_32 byte, uint_16 index) { localvarelement lve;    lve.UnsignedInt = byte;                     lvt[index] = lve; }
    inline void     storeLong(int_64 byte, uint_16 index) { localvarelement lve;            lve.Long = byte;                            lvt[index] = lve; }
    inline void     storeUnsignedLong(uint_64 byte, uint_16 index) { localvarelement lve;   lve.UnsignedLong = byte;                    lvt[index] = lve; }
    inline void     storeLongInt(int_128 byte, uint_16 index) { localvarelement lve;        lve.LongInt = byte;                         lvt[index] = lve; }
    inline void     storeUnsignedLongInt(uint_128 byte, uint_16 index) { localvarelement lve; lve.UnsignedLongInt = byte;               lvt[index] = lve; }
    inline void     storeLongLong(int_256 byte, uint_16 index) { localvarelement lve;       lve.LongLong = byte;                        lvt[index] = lve; }
    inline void     storeUnsignedLongLong(uint_256 byte, uint_16 index) { localvarelement   lve; lve.UnsignedLongLong = byte;           lvt[index] = lve; }
    inline void     storeFloat(flt_32 byte, uint_16 index) { localvarelement lve;           lve.Float = byte;                           lvt[index] = lve; }
    inline void     storeDouble(flt_64 byte, uint_16 index) { localvarelement lve;          lve.Double = byte;                          lvt[index] = lve; }
    inline void     storeDoubleFloat(flt_128 byte, uint_16 index) { localvarelement lve;    lve.DoubleFloat = byte;                     lvt[index] = lve; }
    inline void     storeDoubleDouble(flt_256 byte, uint_16 index) { localvarelement lve;   lve.DoubleDouble = byte;                    lvt[index] = lve; }
    inline void     storePointer(pointer byte, uint_16 index) { localvarelement lve;        lve.Pointer = byte;                         lvt[index] = lve; }

    inline void     storeByte(uint_16 index) { localvarelement lve;                         lve.Byte = stack.popByte();                 lvt[index] = lve; }
    inline void     storeUnsignedByte(uint_16 index) { localvarelement lve;                 lve.UnsignedByte = stack.popUnsignedByte(); lvt[index] = lve; }
    inline void     storeShort(uint_16 index) { localvarelement lve;           lve.Short = stack.popShort();                           lvt[index] = lve; }
    inline void     storeUnsignedShort(uint_16 index) { localvarelement lve;  lve.UnsignedShort = stack.popUnsignedShort();                   lvt[index] = lve; }
    inline void     storeInt(uint_16 index) { localvarelement lve;             lve.Int = stack.popInt();                             lvt[index] = lve; }
    inline void     storeUnsignedInt(uint_16 index) { localvarelement lve;    lve.UnsignedInt = stack.popUnsignedInt();                     lvt[index] = lve; }
    inline void     storeLong(uint_16 index) { localvarelement lve;            lve.Long = stack.popLong();                            lvt[index] = lve; }
    inline void     storeUnsignedLong(uint_16 index) { localvarelement lve;   lve.UnsignedLong = stack.popUnsignedLong();                    lvt[index] = lve; }
    inline void     storeLongInt(uint_16 index) { localvarelement lve;        lve.LongInt = stack.popLongInt();                         lvt[index] = lve; }
    inline void     storeUnsignedLongInt(uint_16 index) { localvarelement lve; lve.UnsignedLongInt = stack.popUnsignedLongInt();               lvt[index] = lve; }
    inline void     storeLongLong(uint_16 index) { localvarelement lve;       lve.LongLong = stack.popLongLong();                        lvt[index] = lve; }
    inline void     storeUnsignedLongLong(uint_16 index) { localvarelement   lve; lve.UnsignedLongLong = stack.popUnsignedLongLong();           lvt[index] = lve; }
    inline void     storeFloat(uint_16 index) { localvarelement lve;           lve.Float = stack.popFloat();                           lvt[index] = lve; }
    inline void     storeDouble(uint_16 index) { localvarelement lve;          lve.Double = stack.popDouble();                          lvt[index] = lve; }
    inline void     storeDoubleFloat(uint_16 index) { localvarelement lve;    lve.DoubleFloat = stack.popDoubleFloat();                     lvt[index] = lve; }
    inline void     storeDoubleDouble(uint_16 index) { localvarelement lve;   lve.DoubleDouble = stack.popDoubleDouble();                    lvt[index] = lve; }
    inline void     storePointer(uint_16 index) { localvarelement lve;        lve.Pointer = stack.popPointer();                         lvt[index] = lve; }
//    inline void     storePointerSAFE(uint_16 index) { localvarelement lve;        lve.Pointer = returnPointer();                         lvt[index] = lve; }

    inline int_8    mloadByte(uint_16 index) { return lvt[index].Byte; }
    inline uint_8   mloadUnsignedByte(uint_16 index) { return lvt[index].UnsignedByte; }
    inline int_16   mloadShort(uint_16 index) { return lvt[index].Short; }
    inline uint_16  mloadUnsignedShort(uint_16 index) { return lvt[index].UnsignedShort; }
    inline int_32   mloadInt(uint_16 index) { return lvt[index].Int; }
    inline uint_32  mloadUnsignedInt(uint_16 index) { return lvt[index].UnsignedInt; }
    inline int_64   mloadLong(uint_16 index) { return lvt[index].Long; }
    inline uint_64  mloadUnsignedLong(uint_16 index) { return lvt[index].UnsignedLong; }
    inline int_128  mloadLongInt(uint_16 index) { return lvt[index].LongInt; }
    inline uint_128 mloadUnsignedLongInt(uint_16 index) { return lvt[index].UnsignedLongInt; }
    inline int_256  mloadLongLong(uint_16 index) { return lvt[index].LongLong; }
    inline uint_256 mloadUnsignedLongLong(uint_16 index) { return lvt[index].UnsignedLongLong; }
    inline void     setCheckPoint(uint_16 checkPoint, uint_64 index) { CHECK_POINTS[checkPoint] = index; }
    inline uint_64  getCheckPointer(uint_16 p) { return CHECK_POINTS[p]; }

    inline void     loadByte(uint_16 index) { stack.pushByte(lvt[index].Byte); }
    inline void     loadUnsignedByte(uint_16 index) { stack.pushUnsignedByte(lvt[index].UnsignedByte); }

    inline void     loadShort(uint_16 index) { stack.pushShort(lvt[index].Short); }
    inline void     loadUnsignedShort(uint_16 index) { stack.pushUnsignedShort(lvt[index].UnsignedShort); }

    inline void     loadInt(uint_16 index) { stack.pushUnsignedInt(lvt[index].Int); }
    inline void     loadUnsignedInt(uint_16 index) { stack.pushUnsignedInt(lvt[index].UnsignedInt); }

    inline void     loadLong(uint_16 index) { stack.pushLong(lvt[index].Long); }
    inline void     loadUnsignedLong(uint_16 index) { stack.pushUnsignedLong(lvt[index].UnsignedLong); }

    inline void     loadLongInt(uint_16 index) { stack.pushLongInt(lvt[index].LongInt); }
    inline void     loadUnsignedLongInt(uint_16 index) { stack.pushUnsignedLongInt(lvt[index].UnsignedLongInt); }

    inline void     loadLongLong(uint_16 index) { stack.pushLongLong(lvt[index].LongLong); }
    inline void     loadUnsignedLongLong(uint_16 index) { stack.pushUnsignedLongLong(lvt[index].UnsignedLongLong); }

    inline void     loadFloat(uint_16 index) { stack.pushFloat(lvt[index].Float); }
    inline void     loadDouble(uint_16 index) { stack.pushDouble(lvt[index].Double); }

    inline void     loadDoubleFloat(uint_16 index) { stack.pushDoubleFloat(lvt[index].DoubleFloat); }
    inline void     loadDoubleDouble(uint_16 index) { stack.pushDoubleDouble(lvt[index].DoubleDouble); }

    inline void     loadPointer(uint_16 index) { stack.pushPointer(lvt[index].Pointer); }

    inline void load(uint_16 i)
    {
        stack.pushLong(lvt[i].Long);
    }

    inline void loadm2(uint_16 i)
    {
    }

    inline void loadm4(uint_16 i)
    {
    }

    inline void store(uint_16 i)
    {
        localvarelement lve;
        lve.Long = stack.popLong();
        lvt[i] = lve;
    }

    inline void storem2(uint_16 i)
    {
    }

    inline void storem4(uint_16 i)
    {
    }

    inline void swap_1(){}
    inline void swap_2(){}
    inline void swap_3(){}
    inline void swap_4(){}
    inline void swap_5(){}
    inline void swap_6(){}
    inline void swap_7(){}
    inline void swap_8(){}
    inline void swap_9(){}
    inline void swap_x(){}
    inline void swap_x1(){}

    inline void pushBool(bool b)
    {
        stack.pushByte(b);
    }

    inline bool popBool()
    {
        return stack.popByte();
    }

//    inline pointer getBasePointer()
//    {
//        return basePointer;
//    }
//
//    inline Scope* getParentScope()
//    {
//        return parent;
//    }
};

extern bool Endianness;

namespace MvM{
    bool IsLittleEndian();

    bool IsBigEndian();

    void Init();

    int_256 pow_big(int_256 a, int_256 b);
    flt_256 pow_bigf(flt_256 a, flt_256 b);

    localvarelement lve_Byte(int_8 byte);

    localvarelement lve_Short(int_16 byte);

    localvarelement lve_Int(int_32 byte);

    localvarelement lve_Long(int_64 byte);

    localvarelement lve_LongInt(int_128 byte);

    localvarelement lve_LongLong(int_256 byte);

    localvarelement lve_Float(flt_32 byte);

    localvarelement lve_Double(flt_64 byte);

    localvarelement lve_DoubleFloat(flt_128 byte);

    localvarelement lve_DoubleDouble(flt_256 byte);

    localvarelement lve_Pointer(pointer byte);



    localvarelement lve_UnsignedByte(uint_8 byte);

    localvarelement lve_UnsignedShort(uint_16 byte);

    localvarelement lve_UnsignedInt(uint_32 byte);

    localvarelement lve_UnsignedLong(uint_64 byte);

    localvarelement lve_UnsignedLongInt(uint_128 byte);

    localvarelement lve_UnsignedLongLong(uint_256 byte);

    struct SmartContract{
        bool loaded = false;
        std::vector<OP_STACK> ops;
        /** a script to lock funds directed to this contract **/
        OP_STACK beneficiaryScript;
    };

    void accessExternalContract(SmartContract* contract);

    void accessMemoryAndSetByte(pointer base, uint_32 address, int_8 byte);
    int_8 accessMemoryAndGetByte(pointer base, int_32 address);


    void accessMemoryAndSetUnsignedByte(pointer base, uint_32 address, uint_8 byte);
    uint_8 accessMemoryAndGetUnsignedtByte(pointer base, uint_32 address);


    /** pointer fields are written in the machines byte order for easy access **/
    void accessMemoryAndSetShort(pointer base, uint_32 address, int_16 byte);
    int_16 accessMemoryAndGetShort(pointer base, uint_32 address);


    void accessMemoryAndSetUnsignedShort(pointer base, uint_32 address, uint_16 byte);
    uint_16 accessMemoryAndGetUnsignedShort(pointer base, uint_32 address);


    void accessMemoryAndSetInt(pointer base, uint_32 address, int_32 byte);
    int_32 accessMemoryAndGetInt(pointer base, uint_32 address);


    void accessMemoryAndSetUnsignedInt(pointer base, uint_32 address, uint_32 byte);
    uint_32 accessMemoryAndGetUnsignedInt(pointer base, uint_32 address);


    void accessMemoryAndSetLong(pointer base, uint_32 address, int_64 byte);
    int_64 accessMemoryAndGetLong(pointer base, uint_32 address);


    void accessMemoryAndSetUnsignedLong(pointer base, uint_32 address, uint_64 byte);
    uint_64 accessMemoryAndGetUnsignedLong(pointer base, uint_32 address);


    void accessMemoryAndSetLongInt(pointer base, uint_32 address, int_128 byte);
    int_128 accessMemoryAndGetLongInt(pointer base, uint_32 address);


    void accessMemoryAndSetUnsignedLongInt(pointer base, uint_32 address, uint_128 byte);
    uint_128 accessMemoryAndGetUnsignedLongInt(pointer base, uint_32 address);


    void accessMemoryAndSetLongLong(pointer base, uint_32 address, int_256 byte);
    int_256 accessMemoryAndGetLongLong(pointer base, uint_32 address);


    void accessMemoryAndSetUnsignedLongLong(pointer base, uint_32 address, uint_256 byte);
    uint_256 accessMemoryAndGetUnsignedLongLong(pointer base, uint_32 address);


    void accessMemoryAndSetFloat(pointer base, uint_32 address, flt_32 byte);
    flt_32 accessMemoryAndGetFloat(pointer base, uint_32 address);


    void accessMemoryAndSetDouble(pointer base, uint_32 address, flt_64 byte);
    flt_64 accessMemoryAndGetDouble(pointer base, uint_32 address);


    void accessMemoryAndSetDoubleFloat(pointer base, uint_32 address, flt_128 byte);
    flt_128 accessMemoryAndGetDoubleFloat(pointer base, uint_32 address);

    void accessMemoryAndSetDoubleDouble(pointer base, uint_32 address, flt_256 byte);
    flt_256 accessMemoryAndGetDoubleDouble(pointer base, uint_32 address);

    void accessMemoryAndSetPointer(pointer base, uint_32 address, pointer byte);
    pointer accessMemoryAndGetPointer(pointer base, uint_32 address);

    void log(const std::string msg);
    void log_err(const std::string msg);
    void printString(const pointer string);
    long long int gtimens();
    long long int gtimems();

    /**
     * @param globalTable a global table containing all non-native functions.
     * @param nativeTable a global table containing all native functions.
     * @param globalPointer the global pointer containing any global variables.
     * @param basePointer the base pointer of this function (self), if it's static, pass the globalpointer.
     * @param stack_main the stack of the previous scope.
     * @param ops the opcodes; all opcodes must be passed in bigendian order, other-wise errors will occur, use "EndianMachine" to fix endianness.
     */
    void execute(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Scope& parent, OP_STACK ops);
}

#endif //MVM_EXECUTOR_H