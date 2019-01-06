//
// Created by Riverssen on 12.12.18.
// Copyright (c) 2018 Riverssen GmbH. All rights reserved.
//

#ifndef MOCHAXX_VM_STRUCTS_H
#define MOCHAXX_VM_STRUCTS_H

#include <map>
#include <stack>
#include "types.h"
#include "endianness.h"
#include "ops.h"
#include <memory>

typedef uint_64 stack_elementsize_t;
typedef uint_32 optable_size_t;

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

    stack_elementsize_t getStackElement()
    {
        return getUnsignedLong();
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

template <typename T>
struct std_stack : public std::stack<T>
{
    using std::stack<T>::c;

    T& operator[] (const unsigned int index);
};


#define scope_ptr_map std::map<uint_64, std::shared_ptr<int_8>>
#define ptr_touint(x) ((uint_64) (intptr_t) x)
#define uint_toptr(x) ((pointer) (intptr_t) x)

class stack{
private:
    std_stack<stack_elementsize_t> m_stack;
public:
    void pushByte(int_8 i);
    void pushUnsignedByte(uint_8 i);

    void pushShort(int_16 i);
    void pushUnsignedShort(uint_16 i);

    void pushInt(int_32 i);
    void pushUnsignedInt(uint_32 i);

    void pushLong(int_64 i);
    void pushUnsignedLong(uint_64 i);

    void pushFloat(float i);
    void pushDouble(double i);

    void push(stack_elementsize_t est);

    void pushPointer(pointer ptr);

    stack_elementsize_t pop();
    flt_32 popFloat();
    flt_64 popDouble();
    pointer popPointer();

    stack_elementsize_t peek();
    flt_32 peekFloat();
    flt_64 peekDouble();
    pointer peekPointer();

    stack_elementsize_t& operator[] (const unsigned int index);

    unsigned long size();

    void rot();
    void rot3();
    void rot4();
    void rot5();
    void rot6();
    void rot7();
    void rot8();
    void rot9();
    void rot10();
    void rot11();
    void rot12();
    void rot13();
    void rot14();
    void rot15();
    void rot16();
    void rot17();
    void rot18();
    void rot19();
    void rot20();

    void swap(uint_64 position);
};

struct scope{
    scope*                                      m_parent;
    std::map<optable_size_t, optable_size_t>    m_jumptable;
    std::map<uint_64, std::shared_ptr<int_8>>   m_scopegc;
    stack                                       m_stack;

    scope(scope* parent);
    uint_64 m_malloc(uint_64 size);
    uint_64 m_calloc(uint_64 size);
    void    m_delete(uint_64 p);


    inline void pushByte(int_8 i);
    inline void pushUnsignedByte(uint_8 i);
    inline void pushShort(int_16 i);
    inline void pushUnsignedShort(uint_16 i);
    inline void pushInt(int_32 i);
    inline void pushUnsignedInt(uint_32 i);
    inline void pushLong(int_64 i);
    inline void pushUnsignedLong(uint_64 i);
    inline void pushFloat(float i);
    inline void pushDouble(double i);
    inline void pushPointer(pointer ptr);
    inline stack_elementsize_t pop();
    inline flt_32 popFloat();
    inline flt_64 popDouble();
    inline pointer popPointer();
    inline stack_elementsize_t peek();
    inline flt_32 peekFloat();
    inline flt_64 peekDouble();
    inline pointer peekPointer();




    inline void add();
    inline void sub();
    inline void div();
    inline void udiv();
    inline void mod();
    inline void expt();

    /**
     * Any bitwise operations should be
     * done on integer elements, however
     * the following operations are the
     * same for float/integer.
     */
    inline void _and();
    inline void _or();
    inline void _xor();
    inline void _not();
    inline void rshift();
    inline void lshift();

    /**
     * This function will handle casting
     * from float/double to long.
     *
     * The result is always a signed long.
     */
    inline void float_to_integer();
};

#define sign_bit 0
#define unsigned_bit 1
#define float_bits 2
#define alu_pointer 3

struct alu{
    static void add_unsigned(stack& esp) { esp.pushUnsignedLong(esp.pop() + esp.pop()); }
    static void sub_unsigned(stack& esp) { esp.pushUnsignedLong(esp.pop() - esp.pop()); }
    static void mul_unsigned(stack& esp) { esp.pushUnsignedLong(esp.pop() * esp.pop()); }
    static void div_unsigned(stack& esp) { esp.pushUnsignedLong(esp.pop() / esp.pop()); }
//    static void mod_unsigned(stack& esp) { esp.pushUnsignedLong(esp.pop() % esp.pop()); }

    static void add_signed(stack& esp) { esp.pushLong(static_cast<int_64>(esp.pop()) + static_cast<int_64>(esp.pop())); }
    static void sub_signed(stack& esp) { esp.pushLong(static_cast<int_64>(esp.pop()) - static_cast<int_64>(esp.pop())); }
    static void mul_signed(stack& esp) { esp.pushLong(static_cast<int_64>(esp.pop()) * static_cast<int_64>(esp.pop())); }
    static void div_signed(stack& esp) { esp.pushLong(static_cast<int_64>(esp.pop()) / static_cast<int_64>(esp.pop())); }
//    static void mod_signed(stack& esp) { esp.pushLong(static_cast<int_64>(esp.pop()) % static_cast<int_64>(esp.pop())); }

    static void add_float(stack& esp) { esp.pushDouble(esp.popDouble() + esp.popDouble()); }
    static void sub_float(stack& esp) { esp.pushDouble(esp.popDouble() - esp.popDouble()); }
    static void mul_float(stack& esp) { esp.pushDouble(esp.popDouble() * esp.popDouble()); }
    static void div_float(stack& esp) { esp.pushDouble(esp.popDouble() / esp.popDouble()); }

#define sign(x) (static_cast<long> (x))

    static void cmp_equal(stack& esp)//  int equal = 0;
    {
        esp.push(sign(esp.pop()) == sign(esp.pop()));
    }

    static void cmp_il(stack& esp)//         int int_l = 129; //0b1000_0001
    {
        esp.push(sign(esp.pop()) < sign(esp.pop()));
    }
    static void cmp_ig(stack& esp) //     int int_g = 130; //0b1000_0010
    {
        esp.push(sign(esp.pop()) > sign(esp.pop()));
    }
    static void cmp_ile(stack& esp)//        int int_le = 132; //0b1000_0100
    {
        esp.push(sign(esp.pop()) <= sign(esp.pop()));
    }
    static void cmp_ige(stack& esp) //    int int_ge = 136; //0b1000_1000
    {
        esp.push(sign(esp.pop()) >= sign(esp.pop()));
    }

    static void cmp_uil(stack& esp) //       int uint_l = 193; //0b1100_0001
    {
        esp.push(esp.pop() < esp.pop());
    }
    static void cmp_uig(stack& esp)   //  int uint_g = 194; //0b1100_0010
    {
        esp.push(esp.pop() > esp.pop());
    }
    static void cmp_uile(stack& esp) //      int uint_le = 196; //0b1100_0100
    {
        esp.push(esp.pop() <= esp.pop());
    }
    static void cmp_uige(stack& esp) //   int uint_ge = 200; //0b1100_1000
    {
        esp.push(esp.pop() >= esp.pop());
    }

    static void cmp_fl(stack& esp)   //      int f_l = 1;
    {
        esp.push(esp.popDouble() < esp.popDouble());
    }
    static void cmp_fg(stack& esp)   //   int f_g = 2;
    {
        esp.push(esp.popDouble() > esp.popDouble());
    }
    static void cmp_fle(stack& esp)  //      int f_le = 4;
    {
        esp.push(esp.popDouble() <= esp.popDouble());
    }
    static void cmp_fge(stack& esp)//     int f_ge = 8;
    {
        esp.push(esp.popDouble() >= esp.popDouble());
    }

#define _cmp_equal 0
#define _cmp_il 1
#define _cmp_ig 2
#define _cmp_ile 3
#define _cmp_ige 4

#define _cmp_uil 5
#define _cmp_uig 6
#define _cmp_uile 7
#define _cmp_uige 8

#define _cmp_fl 9
#define _cmp_fg 10
#define _cmp_fle 11
#define _cmp_fge 12

//    static void mod_float(stack& esp) { esp.pushDouble(esp.popDouble() % esp.popDouble()); }

    static void _and_(stack& esp) { esp.pushLong(esp.pop() & esp.pop()); }
    static void _or_(stack& esp) { esp.pushLong(esp.pop() | esp.pop()); }
    static void _xor_(stack& esp) { esp.pushLong(esp.pop() ^ esp.pop()); }
    static void _not_(stack& esp) { esp.pushLong(~esp.pop()); }
    static void _rshift_(stack& esp) { esp.pushLong(esp.pop() >> esp.pop()); }
    static void _lshift_(stack& esp) { esp.pushLong(esp.pop() << esp.pop()); }

    static void (*adders[3])(stack&);
    static void (*multipliers[3])(stack&);
    static void (*dividers[3])(stack&);
    static void (*subtractors[3])(stack&);
    static void (*comparators[13])(stack&);
//    static void (*moduloss[3])(stack&);
};

struct mem_rcarry{
    long a;
    long b;
    long c;
    long d;

    mem_rcarry(long _a)
    : a(_a)
    {
    }

    mem_rcarry(long _a, long _b)
            : a(_a), b(_b)
    {
    }

    mem_rcarry(long _a, long _b, long _c)
            : a(_a), b(_b), c(_c)
    {
    }

    mem_rcarry(long _a, long _b, long _c, long _d)
            : a(_a), b(_b), c(_c), d(_d)
    {
    }
};

union melement_t
{
    uint_32     UnsignedInt;
    uint_64     UnsignedLong;
    int_32      Int;
    int_64      Long;
    float       Float;
    double      Double;
    stack_elementsize_t sest;

    melement_t(stack_elementsize_t e) : sest(e) {}
    melement_t(float e) : Float(e) {}
    melement_t(double e) : Double(e) {}
};

struct _int_128dts_{
    long a;
    long b;

    _int_128dts_(long _a_, long _b_)
    : a(_a_), b(_b_)
    {
    }
};

struct _int_256dts_{
    long a;
    long b;
    long c;
    long d;

    _int_256dts_(long _a_, long _b_, long _c_, long _d_)
            : a(_a_), b(_b_), c(_c_), d(_d_)
    {
    }
};

union melemente_t
{
    _int_128dts_ bel;
    uint_32     UnsignedInt;
    uint_64     UnsignedLong;
    int_32      Int;
    int_64      Long;
    float       Float;
    double      Double;

    melemente_t(long a, long b)
    : bel(a, b)
    {
    }
};

union melementx_t
{
    _int_256dts_ gxl;
    _int_128dts_ bel;
    melemente_t  mele;
    melement_t  melv;
    uint_32     UnsignedInt;
    uint_64     UnsignedLong;
    int_32      Int;
    int_64      Long;
    float       Float;
    double      Double;

    melementx_t(long a, long b, long c, long d)
            : gxl(a, b, c, d)
    {
    }
};

#define Access(y, x) (*((y*) x))
#define AccessByte(x) (*((char*) x))
#define AccessShort(x) (*((short*) x))
#define AccessInt(x) (*((int*) x))
#define AccessLong(x) (*((long*) x))
#define AccessFloat(x) (*((float*) x))
#define AccessDouble(x) (*((double*) x))

#define mel_esp(a, b) (melemente_t(b, a))
#define mxl_esp(a, b, c, d) (melementx_t(d, c, b, a))

#define El_esp(a, b) b, a
#define Xl_esp(a, b, c, d) d, c, b, a

#include <stdarg.h>

struct mem{
    /**
     * Every pop operation returns a stack_elementsize_t
     */
    enum reg_pop{
        spv = 0, //stack pop (1x stack_elementsize_t) --lower case v contains one corner;
        spe = 1, //stack pop (2x stack_elementsize_t) --lower case e contains two corners;
        spx = 2, //stack pop (4x stack_elementsize_t) --lower case x contains four corners;
//        espv = 3, //stack pop byte
//        espe = 4, //stack pop short
//        espx = 5, //stack pop integer
//        espf = 5, //stack pop float
//        espd = 5, //stack pop double
    };

    enum cast_{
        /** cast a an integer to float **/
        itf = 3,

        /** cast an integer to double **/
        itd = 4,

        /** cast a single stack_elementsize_t to float (this assumes its a double)**/
        etf = 5,
    };

    /**
     * All push operations take a stack_elementsize_t
     *
     * stack.push ops.pop
     */
    enum reg_push{
        psv = 6, //stack push (1x stack_elementsize_t) --lower case v contains one corner;
        pse = 7, //stack push (2x stack_elementsize_t) --lower case e contains two corners;
        psx = 8, //stack push (4x stack_elementsize_t) --lower case x contains four corners;
    };

    /**
     * basepointer->set();
     */
    enum reg_insert{
        bpb = 9, //basepointer set (byte)
        bps = 10, //basepointer set (2 byte)
        bpi = 11, //basepointer set (4 byte)
        bpv = 12, //basepointer set (8 byte)
        bpe = 13, //basepointer set (16 byte)
        bpx = 14, //basepointer set (32 byte)
    };

    /**
     * stack.push basepointer->get();
     * sin = 1
     *
     * pgb + sin = (6 + 1) = 7 (pgb_signed)
     *
     * correct usage
     * mov [pb? + sin] (stack.pushSigned(mem.get()))
     */
    enum reg_get{
        pgb = 15, //basepointer get (byte)
        pgb_s = 16, //basepointer get (byte)

        pgs = 17, //basepointer get (2 byte)
        pgs_s = 18, //basepointer get (2 byte)

        pgi = 19, //basepointer get (4 byte)
        pgi_s = 20, //basepointer get (4 byte)

        pgv = 21, //basepointer get (8 byte)
        pgv_s = 22, //basepointer get (8 byte)

        pge = 23, //basepointer get (16 byte)
        pge_s = 24, //basepointer get (16 byte)

        pgx = 25, //basepointer get (32 byte)
        pgx_s = 26, //basepointer get (32 byte)

        pgf = 27, //basepointer get float
    };

    static void (*registers[28])(stack&, OP_STACK&, melement_t&, void*);

    static void init();

    struct ereg{
        melement_t  melement;
        melemente_t melemente;
        melementx_t melementx;

        inline void v(stack_elementsize_t e)
        {
            melement.sest = e;
        }
    };

    /**
     * Stack pop.
     * mov [sp?] [dest]
     */
    static void mov_spv(stack& esp, OP_STACK& ops, melement_t& reg_e, void* v) { melement_t el(esp.pop()); registers[ops.getUnsignedByte()](esp, ops, el, 0); }
    static void mov_spe(stack& esp, OP_STACK& ops, melement_t& reg_e, void* v) { /**melement_t a(esp.pop()), b(esp.pop()); registers[ops.getUnsignedByte()](esp, ops, El_esp(a, b));**/ }
    static void mov_spx(stack& esp, OP_STACK& ops, melement_t& reg_e, void* v) { /**melement_t a(esp.pop()), b(esp.pop()), c(esp.pop()), d(esp.pop()); registers[ops.getUnsignedByte()](esp, ops, Xl_esp(a, b, c, d));**/ }

    static void mov_itf(stack& esp, OP_STACK& ops, melement_t& reg_e, void* v)
    {
        melement_t el(static_cast<float>(reg_e.Long));
        registers[ops.getUnsignedByte()](esp, ops, el, 0);
    }
    static void mov_itd(stack& esp, OP_STACK& ops, melement_t& reg_e, void* v)
    {
        melement_t el(static_cast<double>(reg_e.Long));
        registers[ops.getUnsignedByte()](esp, ops, el, 0);
    }
    static void mov_etf(stack& esp, OP_STACK& ops, melement_t& reg_e, void* v)
    {
        melement_t el(static_cast<float>(reg_e.Double));
        registers[ops.getUnsignedByte()](esp, ops, el, 0);
    }

//    /**
//     * Stack copy.
//     * mov [sc?] [dest]
//     */
//    static void mov_scv(stack& esp, OP_STACK& ops, mem_rcarry& carry) { registers[ops.getUnsignedByte()](esp, ops, esp.peek()); }
//    static void mov_sce(stack& esp, OP_STACK& ops, mem_rcarry& carry) { registers[ops.getUnsignedByte()](esp, ops, esp.peek(), esp[esp.size() - 2]); }
//    static void mov_scx(stack& esp, OP_STACK& ops, mem_rcarry& carry) { registers[ops.getUnsignedByte()](esp, ops, esp.peek(), esp[esp.size() - 2], esp[esp.size() - 3], esp[esp.size() - 4]); }

    /**
     * Stack push.
     * mov [mcmd] [ps?]
     */
    static void mov_psv(stack& esp, OP_STACK& ops, melement_t& e, void* v) { esp.pushLong(e.UnsignedLong); }
    static void mov_pse(stack& esp, OP_STACK& ops, melement_t& e0, void* v)
    {
        esp.pushLong(e0.UnsignedLong); esp.pushLong(e0.UnsignedLong);
    }
    static void mov_psx(stack& esp, OP_STACK& ops, melement_t& e0, void* v) { esp.pushLong(e0.UnsignedLong); esp.pushLong(e0.UnsignedLong); esp.pushLong(e0.UnsignedLong); esp.pushLong(e0.UnsignedLong); }


    /**
     * basepointer set
     */
    static void mov_bpb(stack& esp, OP_STACK& ops, melement_t& e, void* v) { AccessByte(esp.popPointer())        =  e.UnsignedLong;}
    static void mov_bps(stack& esp, OP_STACK& ops, melement_t& e, void* v) { AccessShort(esp.popPointer())       =  e.UnsignedLong; }
    static void mov_bpi(stack& esp, OP_STACK& ops, melement_t& e, void* v) { AccessInt(esp.popPointer())         =  e.UnsignedLong; }
    static void mov_bpv(stack& esp, OP_STACK& ops, melement_t& e, void* v) { AccessLong(esp.popPointer())        =  e.UnsignedLong; }
    static void mov_bpe(stack& esp, OP_STACK& ops, melement_t& e, void* v) {  }
    static void mov_bpx(stack& esp, OP_STACK& ops, melement_t& e, void* v) {  }


    /**
     * basepointer get
     */
    static void mov_pgb(stack& esp, OP_STACK& ops, melement_t&, void* v)  {       melement_t t(static_cast<stack_elementsize_t> (Access(unsigned char, esp.popPointer()))); registers[ops.getUnsignedByte()](esp, ops, t, 0); }
    static void mov_pgbs(stack& esp, OP_STACK& ops, melement_t&, void* v) {       melement_t t(static_cast<stack_elementsize_t> (Access(char, esp.popPointer()))); registers[ops.getUnsignedByte()](esp, ops, t, 0); }

    static void mov_pgs(stack& esp, OP_STACK& ops, melement_t&, void* v)  {       melement_t t(static_cast<stack_elementsize_t> (Access(unsigned short, esp.popPointer()))); registers[ops.getUnsignedByte()](esp, ops, t, 0); }
    static void mov_pgss(stack& esp, OP_STACK& ops, melement_t&, void* v) {       melement_t t(static_cast<stack_elementsize_t> (Access(short, esp.popPointer()))); registers[ops.getUnsignedByte()](esp, ops, t, 0); }

    static void mov_pgi(stack& esp, OP_STACK& ops, melement_t&, void* v)  {       melement_t t(static_cast<stack_elementsize_t> (Access(unsigned int, esp.popPointer()))); registers[ops.getUnsignedByte()](esp, ops, t, 0); }
    static void mov_pgis(stack& esp, OP_STACK& ops, melement_t&, void* v) {       melement_t t(static_cast<stack_elementsize_t> (Access(int, esp.popPointer()))); registers[ops.getUnsignedByte()](esp, ops, t, 0); }

    static void mov_pgv(stack& esp, OP_STACK& ops, melement_t&, void* v)  {       melement_t t(static_cast<stack_elementsize_t> (Access(unsigned long, esp.popPointer()))); registers[ops.getUnsignedByte()](esp, ops, t, 0); }
    static void mov_pgvs(stack& esp, OP_STACK& ops, melement_t&, void* v) {       melement_t t(static_cast<stack_elementsize_t> (Access(long, esp.popPointer()))); registers[ops.getUnsignedByte()](esp, ops, t, 0); }
    static void mov_pgf(stack& esp, OP_STACK& ops, melement_t&, void* v) {        melement_t t(static_cast<double> (Access(float, esp.popPointer()))); registers[ops.getUnsignedByte()](esp, ops, t, 0); }

    static void mov_pge(stack& esp, OP_STACK& ops, melement_t&, void* v)  { }
    static void mov_pges(stack& esp, OP_STACK& ops, melement_t&, void* v) { }
    static void mov_pgx(stack& esp, OP_STACK& ops, melement_t&, void* v)  { }
    static void mov_pgxs(stack& esp, OP_STACK& ops, melement_t&, void* v) { }

    static void mov(stack& esp, OP_STACK& ops)
    {
        melement_t el(stack_elementsize_t(0));
        registers[ops.getUnsignedByte()](esp, ops, el, 0);
    }
};

struct env{
    typedef void                (*n_func)(env&);
    OP_STACK*           operand_table;
    n_func*             special_table;
    std_stack<scope>    mem_scope;

    env(OP_STACK* o, n_func* nft);

    inline void execute();
    inline void execute(OP_STACK& operand_stack);
};

#endif //MOCHAXX_VM_STRUCTS_H
