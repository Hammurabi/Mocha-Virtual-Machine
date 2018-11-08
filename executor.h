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

/**
 * All MochaXX types
 */

#include "types.h"
#include "endianness.h"

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
};

struct std_stack : public std::stack<uint_8>
{
    using std::stack<unsigned char>::c;

    uint_8& operator[] (const unsigned int index)
    {
        return c[index];
    }
};

struct Stack{
//    unsigned char* stack;
//    unsigned long  size;
//    unsigned long  address;
//
//    Stack(unsigned long max_size) : stack()
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
//        uint_8 h = peek();
//        uint_8 g = peek();
//        uint_8 f = peek();
//        uint_8 e = peek();
//        uint_8 d = peek();
//        uint_8 c = peek();
//        uint_8 b = peek();
//        uint_8 a = peek();
        return int_128();//*((uint_64 *) ((uint_8[8]) {a, b, c, d, e, f, g, h}));
    }

    uint_128 peekUnsignedLongInt()
    {
        /** stack[int[a, b, c, d, e, f, g, h]] **/
//        uint_8 h = peek();
//        uint_8 g = peek();
//        uint_8 f = peek();
//        uint_8 e = peek();
//        uint_8 d = peek();
//        uint_8 c = peek();
//        uint_8 b = peek();
//        uint_8 a = peek();
        return uint_128();//*((uint_64 *) ((uint_8[8]) {a, b, c, d, e, f, g, h}));
    }

    int_256 peekLongLong()
    {
        /** stack[int[a, b, c, d, e, f, g, h]] **/
//        uint_8 h = peek();
//        uint_8 g = peek();
//        uint_8 f = peek();
//        uint_8 e = peek();
//        uint_8 d = peek();
//        uint_8 c = peek();
//        uint_8 b = peek();
//        uint_8 a = peek();
        return int_256();//*((uint_64 *) ((uint_8[8]) {a, b, c, d, e, f, g, h}));
    }

    uint_256 peekUnsignedLongLong()
    {
        /** stack[int[a, b, c, d, e, f, g, h]] **/
//        uint_8 h = peek();
//        uint_8 g = peek();
//        uint_8 f = peek();
//        uint_8 e = peek();
//        uint_8 d = peek();
//        uint_8 c = peek();
//        uint_8 b = peek();
//        uint_8 a = peek();
        return uint_256();//*((uint_64 *) ((uint_8[8]) {a, b, c, d, e, f, g, h}));
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

struct MochaNativeInterface{
    virtual void execute(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack stack_main, OP_STACK ops)
    {
    }
};

struct LocalVariableTable{
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

extern bool Endianness;


namespace MvM{
    bool IsLittleEndian();

    bool IsBigEndian();

    void Init();

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

    void execute(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack stack_main, OP_STACK ops);
}

#endif //MVM_EXECUTOR_H
