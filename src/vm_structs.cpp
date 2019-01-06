//
// Created by Riverssen on 12.12.18.
// Copyright (c) 2018 Riverssen GmbH. All rights reserved.
//

#include "vm_structs.h"

template <typename T> T &std_stack<T>::operator[](const unsigned int index)
{
    return c[index];
}

void stack::pushByte(int_8 i)
{
    m_stack.push(static_cast<stack_elementsize_t>(i));
}

void stack::pushUnsignedByte(uint_8 i)
{
    m_stack.push(static_cast<stack_elementsize_t>(i));
}

void stack::pushShort(int_16 i)
{
    m_stack.push(static_cast<stack_elementsize_t>(i));
}

void stack::pushUnsignedShort(uint_16 i)
{
    m_stack.push(static_cast<stack_elementsize_t>(i));
}

void stack::pushInt(int_32 i)
{
    m_stack.push(static_cast<stack_elementsize_t>(i));
}

void stack::pushUnsignedInt(uint_32 i)
{
    m_stack.push(static_cast<stack_elementsize_t>(i));
}

void stack::pushLong(int_64 i)
{
    m_stack.push(static_cast<stack_elementsize_t>(i));
}

void stack::pushUnsignedLong(uint_64 i)
{
    m_stack.push(static_cast<stack_elementsize_t>(i));
}

void stack::pushFloat(float i)
{
    pushDouble(static_cast<double>(i));
}

void stack::pushDouble(double i)
{
    pointer p = (pointer) &i;
    pushUnsignedLong(*((uint_64 *) ((uint_8[8]) {p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]})));
}

void stack::pushPointer(pointer ptr)
{
    m_stack.push(static_cast<stack_elementsize_t>(ptr_touint(ptr)));
}

stack_elementsize_t stack::pop()
{
    stack_elementsize_t i = m_stack.top();
    m_stack.pop();
    return i;
}

flt_32 stack::popFloat()
{
    return static_cast<float>(popDouble());
}

flt_64 stack::popDouble()
{
    stack_elementsize_t i = pop();

    pointer p = (pointer) &i;
    return (*((double *) ((uint_8[8]) {p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]})));
}

pointer stack::popPointer()
{
    return uint_toptr(pop());
}

stack_elementsize_t stack::peek()
{
    return m_stack.top();
}

flt_32 stack::peekFloat()
{
    return static_cast<float>(peekDouble());
}

flt_64 stack::peekDouble()
{
    stack_elementsize_t i = peek();

    pointer p = (pointer) &i;
    return (*((double *) ((uint_8[8]) {p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]})));
}

pointer stack::peekPointer()
{
    return uint_toptr(peek());
}

void stack::rot()
{
    stack_elementsize_t element_a = m_stack[m_stack.size() - 1];
    stack_elementsize_t element_b = m_stack[m_stack.size() - 2];
    m_stack[m_stack.size() - 2] = element_a;
    m_stack[m_stack.size() - 1] = element_b;
}

void stack::rot3()
{
    stack_elementsize_t element_a = m_stack[m_stack.size() - 1];
    stack_elementsize_t element_b = m_stack[m_stack.size() - 3];

    m_stack[m_stack.size() - 3] = element_a;
    m_stack[m_stack.size() - 1] = element_b;
}

void stack::rot4()
{
    stack_elementsize_t element_a = m_stack[m_stack.size() - 1];
    stack_elementsize_t element_b = m_stack[m_stack.size() - 4];

    m_stack[m_stack.size() - 4] = element_a;
    m_stack[m_stack.size() - 1] = element_b;
}

void stack::rot5()
{
    stack_elementsize_t element_a = m_stack[m_stack.size() - 1];
    stack_elementsize_t element_b = m_stack[m_stack.size() - 5];

    m_stack[m_stack.size() - 5] = element_a;
    m_stack[m_stack.size() - 1] = element_b;
}

void stack::rot6()
{
    stack_elementsize_t element_a = m_stack[m_stack.size() - 1];
    stack_elementsize_t element_b = m_stack[m_stack.size() - 6];

    m_stack[m_stack.size() - 6] = element_a;
    m_stack[m_stack.size() - 1] = element_b;
}

void stack::rot7()
{
    stack_elementsize_t element_a = m_stack[m_stack.size() - 1];
    stack_elementsize_t element_b = m_stack[m_stack.size() - 7];

    m_stack[m_stack.size() - 7] = element_a;
    m_stack[m_stack.size() - 1] = element_b;
}

void stack::rot8()
{
    stack_elementsize_t element_a = m_stack[m_stack.size() - 1];
    stack_elementsize_t element_b = m_stack[m_stack.size() - 8];

    m_stack[m_stack.size() - 8] = element_a;
    m_stack[m_stack.size() - 1] = element_b;
}

void stack::rot9()
{
    stack_elementsize_t element_a = m_stack[m_stack.size() - 1];
    stack_elementsize_t element_b = m_stack[m_stack.size() - 9];

    m_stack[m_stack.size() - 9] = element_a;
    m_stack[m_stack.size() - 1] = element_b;
}

void stack::rot10()
{
    stack_elementsize_t element_a = m_stack[m_stack.size() - 1];
    stack_elementsize_t element_b = m_stack[m_stack.size() - 10];

    m_stack[m_stack.size() - 10] = element_a;
    m_stack[m_stack.size() - 1] = element_b;
}

void stack::rot11()
{
    stack_elementsize_t element_a = m_stack[m_stack.size() - 1];
    stack_elementsize_t element_b = m_stack[m_stack.size() - 11];

    m_stack[m_stack.size() - 11] = element_a;
    m_stack[m_stack.size() - 1] = element_b;
}

void stack::rot12()
{
    stack_elementsize_t element_a = m_stack[m_stack.size() - 1];
    stack_elementsize_t element_b = m_stack[m_stack.size() - 12];

    m_stack[m_stack.size() - 12] = element_a;
    m_stack[m_stack.size() - 1] = element_b;
}

void stack::rot13()
{
    stack_elementsize_t element_a = m_stack[m_stack.size() - 1];
    stack_elementsize_t element_b = m_stack[m_stack.size() - 13];

    m_stack[m_stack.size() - 13] = element_a;
    m_stack[m_stack.size() - 1] = element_b;
}

void stack::rot14()
{
    stack_elementsize_t element_a = m_stack[m_stack.size() - 1];
    stack_elementsize_t element_b = m_stack[m_stack.size() - 14];

    m_stack[m_stack.size() - 14] = element_a;
    m_stack[m_stack.size() - 1] = element_b;
}

void stack::rot15()
{
    stack_elementsize_t element_a = m_stack[m_stack.size() - 1];
    stack_elementsize_t element_b = m_stack[m_stack.size() - 15];

    m_stack[m_stack.size() - 15] = element_a;
    m_stack[m_stack.size() - 1] = element_b;
}

void stack::rot16()
{
    stack_elementsize_t element_a = m_stack[m_stack.size() - 1];
    stack_elementsize_t element_b = m_stack[m_stack.size() - 16];

    m_stack[m_stack.size() - 16] = element_a;
    m_stack[m_stack.size() - 1] = element_b;
}

void stack::rot17()
{
    stack_elementsize_t element_a = m_stack[m_stack.size() - 1];
    stack_elementsize_t element_b = m_stack[m_stack.size() - 17];

    m_stack[m_stack.size() - 17] = element_a;
    m_stack[m_stack.size() - 1] = element_b;
}

void stack::rot18()
{
    stack_elementsize_t element_a = m_stack[m_stack.size() - 1];
    stack_elementsize_t element_b = m_stack[m_stack.size() - 18];

    m_stack[m_stack.size() - 18] = element_a;
    m_stack[m_stack.size() - 1] = element_b;
}

void stack::rot19()
{
    stack_elementsize_t element_a = m_stack[m_stack.size() - 1];
    stack_elementsize_t element_b = m_stack[m_stack.size() - 19];

    m_stack[m_stack.size() - 19] = element_a;
    m_stack[m_stack.size() - 1] = element_b;
}

void stack::rot20()
{
    stack_elementsize_t element_a = m_stack[m_stack.size() - 1];
    stack_elementsize_t element_b = m_stack[m_stack.size() - 20];

    m_stack[m_stack.size() - 20] = element_a;
    m_stack[m_stack.size() - 1] = element_b;
}

unsigned long stack::size()
{
    return m_stack.size();
}

stack_elementsize_t &stack::operator[](const unsigned int index)
{
    return m_stack[index];
}

void stack::push(stack_elementsize_t est)
{
    m_stack.push(est);
}

void stack::swap(uint_64 position)
{
    stack_elementsize_t temp = stack_elementsize_t (m_stack[position]);
    m_stack[position] = stack_elementsize_t (m_stack[size() - 1]);
    m_stack[size() - 1] = temp;
}

scope::scope(scope *parent) : m_parent(parent)
{
}

void scope::float_to_integer()
{
    m_stack.pushLong(static_cast<int_64> (m_stack.popDouble()));
}

void (*alu::adders[3])(stack&)          {add_signed, add_unsigned, add_float};
void (*alu::multipliers[3])(stack&)     {mul_signed, mul_unsigned, mul_float};
void (*alu::dividers[3])(stack&)        {div_signed, div_unsigned, div_float};
void (*alu::subtractors[3])(stack&)     {sub_signed, sub_unsigned, sub_float};
void (*alu::comparators[13])(stack&)     {cmp_equal, cmp_il, cmp_ig, cmp_ile, cmp_ige, cmp_uil, cmp_uig, cmp_uile, cmp_uige, cmp_fl, cmp_fg, cmp_fle, cmp_fge};
//void (*alu::moduloss[3])(stack&)        {mod_signed, mod_unsigned, mod_float};


void (*mem::registers[28])(stack&, OP_STACK&, melement_t&, void*);


void mem::init()
{
    registers[spv] = mov_spv;
    registers[spe] = mov_spe;
    registers[spx] = mov_spx;

    registers[itf] = mov_itf;
    registers[itd] = mov_itd;
    registers[etf] = mov_etf;

    registers[psv] = mov_psv;
    registers[pse] = mov_pse;
    registers[psx] = mov_psx;

    registers[bpb] = mov_bpb;
    registers[bps] = mov_bps;
    registers[bpi] = mov_bpi;
    registers[bpv] = mov_bpv;
    registers[bpe] = mov_bpe;
    registers[bpx] = mov_bpx;

    registers[pgb] = mov_pgb;
    registers[pgb_s] = mov_pgbs;

    registers[pgs] = mov_pgs;
    registers[pgs_s] = mov_pgss;

    registers[pgi] = mov_pgi;
    registers[pgi_s] = mov_pgis;

    registers[pgv] = mov_pgv;
    registers[pgv_s] = mov_pgvs;

    registers[pge] = mov_pge;
    registers[pge_s] = mov_pges;

    registers[pgx] = mov_pgx;
    registers[pgx_s] = mov_pgxs;
    registers[pgf] = mov_pgf;
}

env::env(OP_STACK *o, n_func* nft)
:operand_table(o), special_table(nft)
{
    mem_scope.push(scope(0));
}

void env::execute()
{
    execute(operand_table[0]);
}

#define pushscope mem_scope.push(scope(& s_scope));
#define popscope mem_scope.pop();

#define quick_op(x) s_stack.push(s_stack.pop() x s_stack.pop());

void env::execute(OP_STACK& operand_stack)
{
    scope&    s_scope = mem_scope.top();
    stack&    s_stack = mem_scope.top().m_stack;

    while (operand_stack.getRemaining() > 0)
    {
        Op operand = operand_stack.getOp();

        /** Most common Operands should be closest to the top of the switch statement **/
        switch (operand)
        {
            case Op::swap:
                s_stack.swap(operand_stack.getUnsignedLong());
                break;
            case Op::add:
                alu::adders[operand_stack.getUnsignedByte()](s_stack);
                break;
            case Op::mul:
                alu::multipliers[operand_stack.getUnsignedByte()](s_stack);
                break;
            case Op::sub:
                alu::subtractors[operand_stack.getUnsignedByte()](s_stack);
                break;
            case Op::div:
                alu::dividers[operand_stack.getUnsignedByte()](s_stack);
                break;

            case Op::push_0:
                s_stack.push(0L);
                break;
            case Op::push:
                s_stack.push(operand_stack.getStackElement());
                break;

            case Op::ret:
                return;
            case Op::mret:
                s_scope.m_parent->m_stack.push(s_stack.pop());
                break;

            case Op::invoke:
                pushscope
                execute(operand_table[operand_stack.getUnsignedInt()]);
                popscope
                break;



            case Op::mov:
                mem::mov(s_stack, operand_stack);
                break;

            case m_alloc:
                s_stack.pushPointer(static_cast<pointer>(malloc(s_stack.pop())));
                break;

            case m_delete:
                delete (s_stack.popPointer());
                break;

            case Op::idynmc:
                pushscope
                execute(operand_table[s_stack.pop()]);
                popscope
                break;
            case Op::ispcal:
                pushscope
                special_table[s_stack.pop()];
                popscope
                break;

            case Op::branch:
                if (s_stack.pop())
                    break;
                operand_stack.address = operand_stack.getUnsignedInt();
                break;
            case Op::jump:
                operand_stack.address = operand_stack.getUnsignedInt();
                break;


            case Op::cmp:
                //---0 0 0 0 0 0 0 0
                //---^ first bit indicates whether the
                //---  comparison is between integers or floats.
                //---              ^ last bit == less
                //---            ^ second to last bit == equal
                //---          ^ third to last bit == greater
                //---        ^ fourth to last bit == less than or equal
                //---      ^ fifth to last bit == more than or equal

                alu::comparators[operand_stack.getUnsignedByte()](s_stack);
                break;

            case Op::mod:
                s_stack.push(s_stack.pop() % s_stack.pop());
                break;


            case Op::push_1:
                s_stack.push(1L);
                break;

            case Op::and_:
                quick_op(&);
                break;
            case Op::or_:
                quick_op(|);
                break;
            case Op::xor_:
                quick_op(^);
                break;
            case Op::not_:
                s_stack.push(~ s_stack.pop());
                break;
            case Op::rshift:
                quick_op(>>);
                break;
            case Op::lshift:
                quick_op(<<);
                break;

            case m_calloc:
                s_stack.pushPointer(static_cast<pointer>(calloc(s_stack.pop(), s_stack.pop())));
                break;

            case Op::hpush:
                s_stack.push(operand_stack.getInt());
                break;

            case Op::cast_itf:
                s_stack.pushDouble(static_cast<double> (s_stack.pop()));
                break;
            case Op::cast_fti:
                s_stack.pushLong(static_cast<long> (s_stack.popDouble()));

            case Op::cast:
                exit(-1);

            case Op::mark:
                s_scope.m_jumptable[operand_stack.getUnsignedShort()] = operand_stack.getUnsignedInt();
                break;
            case Op::gto:
                operand_stack.address = s_scope.m_jumptable[operand_stack.getUnsignedShort()];
                break;



            case Op::dup:
                s_stack.push(s_stack.peek());
                break;

            case Op::pop:
                s_stack.pop();
                break;
            case Op::halt:
                exit(s_stack.pop());

            case Op::mret2:
            case Op::mret4:
                exit(-1);
        }
    }
}
