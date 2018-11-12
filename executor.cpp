
#include <vector>
#include "executor.h"
#include "executorfuncs.h"
#include <set>

bool Endianness;

// struct bytearray{
    // uint_64 length;
    // pointer array;
// };

//
// Created by Riverssen on 07.11.18.
//
void MvM::execute(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, OP_STACK ops)
{
    Stack stack;
    std::map<uint_32, localvarelement> lvt;
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
     *
     *
     *
     *
     * void set()
     * {
     *              //This is safe because the GC will handle the pointer when it goes out of scope.
     *  int * colours = getPointer();
     * }
     */
    std::map<uint_32, std::shared_ptr<uint_8>> scope_ptrs;

    pointer base = basePointer;
//    ops.address = 0;

    while (ops.getRemaining() > 0)
    {
        Op op_undefinedcurrent = ops.getOp();//ops.getOp();
//        std::cout << std::endl<< op_undefinedcurrent << " " << ops.address << " " << stack.stack.size() << std::endl;
//        implptr_t[op_undefinedcurrent]();

//                (impl::impl_funcs[op_undefinedcurrent])
//                        (globalTable, nativeTable, globalPointer, basePointer, stack_main, stack, ops,
//                                lvt, CHECK_POINTS, base);

        switch (op_undefinedcurrent)
        {
            /**
 *(This opcode won't be interpreted) it creates a marker for an OP_STACK (must end with a return_op of some kind).
 */
            case func:

                break;
/**
 *perform a hash on pointer data.
 */
            case hash:

                break;
/**
 *push a (uint_64) current time in nanoseconds.
 */
            case timens:
                stack.pushUnsignedLong(static_cast<uint_64> (MvM::gtimens()));
                break;
/**
 *push a (uint_64) current time in milliseconds.
 */
            case timems:
                stack.pushUnsignedLong(static_cast<uint_64> (MvM::gtimems()));
                break;
/**
 *push a constant string.
 */
            case strconst:
            { uint_16 size_ = stack.popUnsignedShort(); pointer str = static_cast<pointer> (calloc(size_ * 2 + 2, size_ * 2 + 2)); MvM::accessMemoryAndSetUnsignedShort(str, 0, size_); stack.pushPointer(str);}
                break;
/**
 *load a string.
 */
            case strload:
                stack.pushUnsignedLong(lvt[ops.getUnsignedShort()].UnsignedLong);
                break;
/**
 *store a string.
 */
            case strstore:
                lvt[ops.getUnsignedShort()] = MvM::lve_Long(stack.popUnsignedLong());
                break;
/**
 *store a string.
 */
            case strsizeof:
                stack.pushUnsignedLong(static_cast<uint_64> (MvM::accessMemoryAndGetUnsignedShort(stack.popPointer(), 0)));
                break;
/**
 *cast a string to a pointer.
 */
            case strcast_a:
            { pointer s = stack.popPointer(); uint_16 l = MvM::accessMemoryAndGetUnsignedShort(s, 0); pointer b = static_cast<pointer> (calloc(l * 2, l * 2)); memcpy(b, s + 2, l * 2); stack.pushPointer(b); }
                break;
/**
 *cast a string to a byte array.
 */
            case strcast_ba:
            { pointer s = stack.popPointer(); uint_16 l = MvM::accessMemoryAndGetUnsignedShort(s, 0); pointer b = static_cast<pointer> (calloc(l * 2 + 6, l * 2 + 6)); memcpy(b + 6, s, l * 2); MvM::accessMemoryAndSetUnsignedLong(b, 0, static_cast<uint_64> (l)); stack.pushPointer(b); }
                break;
/**
 *print a string.
 */
            case strprint:
                MvM::printString(stack.popPointer());
                break;
/**
 *return a string from scope.
 */
            case strreturn:
                stack_main.pushUnsignedLong(stack.popUnsignedLong()); return;
                break;
/**
 *mark a specific location.
 */
            case mark:
                CHECK_POINTS[ops.getUnsignedShort()] = ops.address + 2;
                break;
/**
 *jump to a specific location.
 */
            case jump:
                ops.address = ops.getUnsignedLong();
                break;
/**
 *jump to a specific marked location.
 */
            case jumptomark:
                ops.address = CHECK_POINTS[ops.getUnsignedShort()];
                break;
/**
 *print a \n character into the console.
 */
            case newline:
                std::cout<<std::endl;
                break;
/**
 *return from this scope.
 */
            case ret:
                return;
                break;
/**
 *invoke a method.
 */
            case invoke:
                execute(globalTable, nativeTable, globalPointer, globalPointer, stack, globalTable[ops.getUnsignedLong()]);
                break;
/**
 *dynamically invoke a method using function pointers.
 */
            case invokedynamic:
                execute(globalTable, nativeTable, globalPointer, globalPointer, stack, globalTable[stack.popUnsignedLong()]);
                break;
/**
 *invoke a native method using function pointers.
 */
            case invokespecial:
                nativeTable[stack.popUnsignedLong()]->execute(globalTable, nativeTable, globalPointer, globalPointer, stack, globalTable[stack.popUnsignedLong()]);
                break;
/**
 *if true.
 */
            case if_t:
            { uint_32 jump = ops.getUnsignedInt(); if (stack.popByte() == 0) ops.address += jump; }
                break;
/**
 *if not true.
 */
            case if_f:
            { uint_32 jump = ops.getUnsignedInt(); if (stack.popByte() > 0) ops.address += jump; }
                break;
/**
 *invert a boolean.
 */
            case invert:
                stack.pushByte(!((bool) stack.popByte()));
                break;
/**
 *copy memory to destination from source.
 */
            case amemcpy:
                memcpy(stack.popPointer(), stack.popPointer(), stack.popUnsignedLong());
                break;
/**
 *copy memory to destination from base pointer.
 */
            case bspmemcpy:
                memcpy(stack.popPointer(), base, stack.popUnsignedLong());
                break;
/**
 *copy memory to pointer from source.
 */
            case amemcpybsp:
                memcpy(base, stack.popPointer(), stack.popUnsignedLong());
                break;
/**
 *push a const pointer to the stack.
 */
            case amalloc:
                stack.pushPointer(static_cast<pointer> (malloc(stack.popUnsignedLong())));
                break;
/**
 *push a const pointer to the stack.
 */
            case acalloc:
                stack.pushPointer(static_cast<pointer> (calloc(stack.popUnsignedLong(), stack.popUnsignedLong())));
                break;
/**
 *push a const pointer to the stack from size_int16_t.
 */
            case amallocs:
                stack.pushPointer(static_cast<pointer> (malloc(stack.popUnsignedShort())));
                break;
/**
 *push a const pointer to the stack from size_int16_t.
 */
            case acallocs:
                stack.pushPointer(static_cast<pointer> (calloc(stack.popUnsignedShort(), stack.popUnsignedShort())));
                break;
/**
 *delete a pointer.
 */
            case adelete:
                delete (stack.popPointer());
                break;
/**
 *push a byte array.
 */
            case baconst:
            { uint_64 length = stack.popUnsignedLong(); pointer p = static_cast<pointer> (calloc(length, length)); stack.pushPointer(p); MvM::accessMemoryAndSetUnsignedLong(p, 0, length); }
                break;
/**
 *push a byte array using size_int16_t
 */
            case baconsts:
            { uint_64 length = static_cast<uint_64> (stack.popUnsignedShort()); pointer p = static_cast<pointer> (calloc(length, length)); stack.pushPointer(p); MvM::accessMemoryAndSetUnsignedLong(p, 0, length); }
                break;
/**
 *push a byte array using size_int32_t
 */
            case baconsti:
            { uint_64 length = static_cast<uint_64> (stack.popUnsignedInt()); pointer p = static_cast<pointer> (calloc(length, length)); stack.pushPointer(p); MvM::accessMemoryAndSetUnsignedLong(p, 0, length); }
                break;
/**
 *cast a byte array into a pointer
 */
            case bacast_a:
            { stack.pushPointer(stack.popPointer() + 8); }
                break;
/**
 *push the size of a byte array to stack
 */
            case basizeof:
            { stack.pushUnsignedLong(static_cast<uint_64> (MvM::accessMemoryAndGetLong(stack.popPointer(), 0))); }
                break;
/**
 *print a byte array.
 */
            case printba:
            { pointer bytearray = stack.popPointer(); uint_64 bytearraysize   = static_cast<uint_64> (MvM::accessMemoryAndGetLong(bytearray, 0)); std::string data = "["; for (uint_64 i = 0; i < bytearraysize; i ++) data += std::to_string(MvM::accessMemoryAndGetByte(bytearray + 8, i)) + ((i < bytearraysize - 1) ? ", " : "]"); MvM::log(data); }
                break;
/**
 *compare a long less than long.
 */
            case cmpl:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 *compare a long greater than long.
 */
            case cmpg:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 *compare a long equal with long.
 */
            case cmpe:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 *compare a long less than or equal to long.
 */
            case cmple:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 *compare a long greater than or equal to long.
 */
            case cmpge:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 *compare a long not equal with long.
 */
            case cmpne:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 *compare a ulong int with another ulong.
 */
            case ucmp:
            {
                uint_64 b = stack.popUnsignedLong();
                uint_64 a = stack.popUnsignedLong();
                stack.pushByte((a < b) ? -1 : ((a > b) ? 1 : 0));
            }
                break;
/**
 *compare a long int with a ulong.
 */
            case cmpu:
            {
                uint_64 b = stack.popUnsignedLong();
                uint_64 a = stack.popLong();
                stack.pushByte((a < b) ? -1 : ((a > b) ? 1 : 0));
            }
                break;
/**
 *compare a 256bit int with another 256bit int.
 */
            case cmpll:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a < b) ? -1 : ((a > b) ? 1 : 0));
            }
                break;
/**
 *compare a u256bit int with another u256bit int.
 */
            case ucmpll:
            {
                uint_256 b = stack.popUnsignedLongLong();
                uint_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a < b) ? -1 : ((a > b) ? 1 : 0));
            }
                break;
/**
 *compare a 256bit int with a u256bit int.
 */
            case cmpull:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a < b) ? -1 : ((a > b) ? 1 : 0));
            }
                break;
/**
 *compare a double less than double.
 */
            case dcmpl:
            {
                flt_64 b = stack.popDouble();
                flt_64 a = stack.popDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 *compare a double greater than double.
 */
            case dcmpg:
            {
                flt_64 b = stack.popDouble();
                flt_64 a = stack.popDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 *compare a double equal with double.
 */
            case dcmpe:
            {
                flt_64 b = stack.popDouble();
                flt_64 a = stack.popDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 *compare a double less than or equal to double.
 */
            case dcmple:
            {
                flt_64 b = stack.popDouble();
                flt_64 a = stack.popDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 *compare a double greater than or equal to double.
 */
            case dcmpge:
            {
                flt_64 b = stack.popDouble();
                flt_64 a = stack.popDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 *compare a double not equal with double.
 */
            case dcmpne:
            {
                flt_64 b = stack.popDouble();
                flt_64 a = stack.popDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 *mod an int with an int.
 */
            case mod:
            {
                stack.pushLong(stack.popLong() % stack.popLong());
            }
                break;
/**
 *mod an int 256 with an int 256.
 */
            case llmod:
            {
                stack.pushUnsignedLongLong(stack.popUnsignedLongLong() % stack.popUnsignedLongLong());
            }
                break;
/**
 *bitwise and int with int.
 */
            case and_:
                {
                    stack.pushUnsignedLong(stack.popUnsignedLong() & stack.popUnsignedLong());
                }
                break;
/**
 *bitwise or int with int.
 */
            case or_:
                {
                    stack.pushUnsignedLong(stack.popUnsignedLong() | stack.popUnsignedLong());
                }
                break;
/**
 *bitwise xor int with int.
 */
            case xor_:
            {
                stack.pushUnsignedLong(stack.popUnsignedLong() ^ stack.popUnsignedLong());
            }
                break;
/**
 *bitwise not int with int.
 */
            case not_:
            {
//                stack.pushUnsignedLong(stack.popUnsignedLong() ~ stack.popUnsignedLong());
            }
                break;
/**
 *right shift int with byte.
 */
            case rshft:
            {
                stack.pushUnsignedLong(stack.popUnsignedLong() >> stack.popUnsignedByte());
            }
                break;
/**
 *left shift int with byte.
 */
            case lshft:
            {
                stack.pushUnsignedLong(stack.popUnsignedLong() << stack.popUnsignedByte());
            }
                break;
/**
 *duplicate a %t on the stack.
 */
            case dup:
                stack.pushUnsignedLong(stack.peekUnsignedLong());
                break;
/**
 *duplicate a %t 2 times on the stack.
 */
            case dup2:
                stack.pushUnsignedLong(stack.peekUnsignedLong());stack.pushUnsignedLong(stack.peekUnsignedLong());
                break;
/**
 *duplicate a %t 3 times on the stack.
 */
            case dup3:
                stack.pushUnsignedLong(stack.peekUnsignedLong());stack.pushUnsignedLong(stack.peekUnsignedLong());stack.pushUnsignedLong(stack.peekUnsignedLong());
                break;
/**
 *swap the 2 topmost elements.
 */
            case swap:
            { uint_64 a = stack.popUnsignedLong(); uint_64 b = stack.popUnsignedLong(); stack.pushUnsignedLong(a); stack.pushUnsignedLong(b); }
                break;
/**
 *return the top element into the main stack.
 */
            case pret:
                stack_main.pushUnsignedLong(stack.popUnsignedLong()); return;
                break;
/**
 *return the top 2 elements (128bit) into the main stack.
 */
            case pret2:
                stack_main.pushUnsignedLongInt(stack.popUnsignedLongInt()); return;
                break;
/**
 *return the top 4 elements (256bit) into the main stack.
 */
            case pret4:
                stack_main.pushUnsignedLongLong(stack.popUnsignedLongLong()); return;
                break;
/**
 * push a const int_8 into the stack.
 */
            case bconst:
                stack.pushByte(ops.getByte());
                break;
/**
 * push a const int_8 into the stack (value = 0).
 */
            case bconst_0:
                stack.pushByte(0);
                break;
/**
 * load a int_8 into the stack from local variable.
 */
            case bload:
                stack.pushByte(lvt[ops.getUnsignedShort()].Byte);
                break;
/**
 * store a int_8 from stack into local variable.
 */
            case bstore:
                lvt[ops.getUnsignedShort()] = MvM::lve_Byte(stack.popByte());
                break;
/**
 * set a int_8 from stack into a field on pointer.
 */
            case bset:
                MvM::accessMemoryAndSetByte(stack.popPointer(), stack.popUnsignedLong(), stack.popByte());
                break;
/**
 * get a int_8 from a field on a pointer to stack.
 */
            case bget:
                stack.pushByte(MvM::accessMemoryAndGetByte(stack.popPointer(), stack.popUnsignedLong()));
                break;
/**
 * store a int_8 from main stack in a local variable..
 */
            case bmainst:
                lvt[ops.getUnsignedShort()].Byte = stack_main.popByte();
                break;
/**
 * print a int_8 from stack.
 */
            case bprint:
                MvM::log(std::to_string(stack.popByte()));
                break;
/**
 * print a unsigned uint_8 from stack.
 */
            case buprint:
                MvM::log(std::to_string(stack.popUnsignedByte()));
                break;
/**
 * push a const int_16 into the stack.
 */
            case sconst:
                stack.pushShort(ops.getShort());
                break;
/**
 * push a const int_16 into the stack (value = 0).
 */
            case sconst_0:
                stack.pushShort(0);
                break;
/**
 * load a int_16 into the stack from local variable.
 */
            case sload:
                stack.pushShort(lvt[ops.getUnsignedShort()].Short);
                break;
/**
 * store a int_16 from stack into local variable.
 */
            case sstore:
                lvt[ops.getUnsignedShort()] = MvM::lve_Short(stack.popShort());
                break;
/**
 * set a int_16 from stack into a field on pointer.
 */
            case sset:
                MvM::accessMemoryAndSetShort(stack.popPointer(), stack.popUnsignedLong(), stack.popShort());
                break;
/**
 * get a int_16 from a field on a pointer to stack.
 */
            case sget:
                stack.pushShort(MvM::accessMemoryAndGetShort(stack.popPointer(), stack.popUnsignedLong()));
                break;
/**
 * store a int_16 from main stack in a local variable..
 */
            case smainst:
                lvt[ops.getUnsignedShort()].Short = stack_main.popShort();
                break;
/**
 * print a int_16 from stack.
 */
            case sprint:
                MvM::log(std::to_string(stack.popShort()));
                break;
/**
 * print a unsigned uint_16 from stack.
 */
            case suprint:
                MvM::log(std::to_string(stack.popUnsignedShort()));
                break;
/**
 * push a const int_32 into the stack.
 */
            case iconst:
                stack.pushInt(ops.getInt());
                break;
/**
 * push a const int_32 into the stack (value = 0).
 */
            case iconst_0:
                stack.pushInt(0);
                break;
/**
 * push a const int_32 into the stack (value = 1).
 */
            case iconst_1:
                stack.pushInt(1);
                break;
/**
 * push a const int_32 into the stack (value = 2).
 */
            case iconst_2:
                stack.pushInt(2);
                break;
/**
 * push a const int_32 into the stack (value = 3).
 */
            case iconst_3:
                stack.pushInt(3);
                break;
/**
 * push a const int_32 into the stack (value = 4).
 */
            case iconst_4:
                stack.pushInt(4);
                break;
/**
 * push a const int_32 into the stack (value = 5).
 */
            case iconst_5:
                stack.pushInt(5);
                break;
/**
 * push a const int_32 into the stack (value = 6).
 */
            case iconst_6:
                stack.pushInt(6);
                break;
/**
 * push a const int_32 into the stack (value = 9).
 */
            case iconst_9:
                stack.pushInt(9);
                break;
/**
 * push a const int_32 into the stack (value = 10).
 */
            case iconst_10:
                stack.pushInt(10);
                break;
/**
 * push a const int_32 into the stack (value = 11).
 */
            case iconst_11:
                stack.pushInt(11);
                break;
/**
 * push a const int_32 into the stack (value = 12).
 */
            case iconst_12:
                stack.pushInt(12);
                break;
/**
 * load a int_32 into the stack from local variable.
 */
            case iload:
                stack.pushInt(lvt[ops.getUnsignedShort()].Int);
                break;
/**
 * load a int_32 into the stack from local variable 0.
 */
            case iload_0:
                stack.pushInt(lvt[0].Int);
                break;
/**
 * load a int_32 into the stack from local variable 1.
 */
            case iload_1:
                stack.pushInt(lvt[1].Int);
                break;
/**
 * load a int_32 into the stack from local variable 2.
 */
            case iload_2:
                stack.pushInt(lvt[2].Int);
                break;
/**
 * load a int_32 into the stack from local variable 3.
 */
            case iload_3:
                stack.pushInt(lvt[3].Int);
                break;
/**
 * load a int_32 into the stack from local variable 4.
 */
            case iload_4:
                stack.pushInt(lvt[4].Int);
                break;
/**
 * store a int_32 from stack into local variable.
 */
            case istore:
                lvt[ops.getUnsignedShort()] = MvM::lve_Int(stack.popInt());
                break;
/**
 * store a int_32 from stack into local variable 0.
 */
            case istore_0:
                lvt[0] = MvM::lve_Int(stack.popInt());
                break;
/**
 * store a int_32 from stack into local variable 1.
 */
            case istore_1:
                lvt[1] = MvM::lve_Int(stack.popInt());
                break;
/**
 * store a int_32 from stack into local variable 2.
 */
            case istore_2:
                lvt[2] = MvM::lve_Int(stack.popInt());
                break;
/**
 * store a int_32 from stack into local variable 3.
 */
            case istore_3:
                lvt[3] = MvM::lve_Int(stack.popInt());
                break;
/**
 * store a int_32 from stack into local variable 4.
 */
            case istore_4:
                lvt[4] = MvM::lve_Int(stack.popInt());
                break;
/**
 * add two Ints.
 */
            case iadd:
                stack.pushInt(stack.popInt() + stack.popInt());
                break;
/**
 * add two UnsignedUnsignedInts.
 */
            case iuadd:
                stack.pushUnsignedInt(stack.popUnsignedInt() + stack.popUnsignedInt());
                break;
/**
 * subtract two Ints.
 */
            case isub:
                stack.pushInt(stack.popInt() - stack.popInt());
                break;
/**
 * subtract two UnsignedUnsignedInts.
 */
            case iusub:
                stack.pushUnsignedInt(stack.popUnsignedInt() - stack.popUnsignedInt());
                break;
/**
 * multiply two Ints.
 */
            case imul:
                stack.pushInt(stack.popInt() * stack.popInt());
                break;
/**
 * multiply two UnsignedUnsignedInts.
 */
            case iumul:
                stack.pushUnsignedInt(stack.popUnsignedInt() * stack.popUnsignedInt());
                break;
/**
 * divide two Ints.
 */
            case idiv:
                stack.pushInt(stack.popInt() / stack.popInt());
                break;
/**
 * divide two UnsignedUnsignedInts.
 */
            case iudiv:
                stack.pushUnsignedInt(stack.popUnsignedInt() / stack.popUnsignedInt());
                break;
/**
 * set a int_32 from stack into a field on pointer.
 */
            case iset:
                MvM::accessMemoryAndSetInt(stack.popPointer(), stack.popUnsignedLong(), stack.popInt());
                break;
/**
 * get a int_32 from a field on a pointer to stack.
 */
            case iget:
                stack.pushInt(MvM::accessMemoryAndGetInt(stack.popPointer(), stack.popUnsignedLong()));
                break;
/**
 * increment a local variable int_32 by 1.
 */
            case iinc1:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].Int = lvt[point].Int + 1; }
                break;
/**
 * increment a local variable int_32 by 2.
 */
            case iinc2:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].Int = lvt[point].Int + 2; }
                break;
/**
 * store a int_32 from main stack in a local variable..
 */
            case imainst:
                lvt[ops.getUnsignedShort()].Int = stack_main.popInt();
                break;
/**
 * store a int_32 from main stack in local variable 0.
 */
            case imainst_0:
                lvt[0].Int = stack_main.popInt();;
                break;
/**
 * store a int_32 from main stack in local variable 1.
 */
            case imainst_1:
                lvt[1].Int = stack_main.popInt();;
                break;
/**
 * store a int_32 from main stack in local variable 2.
 */
            case imainst_2:
                lvt[2].Int = stack_main.popInt();;
                break;
/**
 * store a int_32 from main stack in local variable 3.
 */
            case imainst_3:
                lvt[3].Int = stack_main.popInt();;
                break;
/**
 * print a int_32 from stack.
 */
            case iprint:
                MvM::log(std::to_string(stack.popInt()));
                break;
/**
 * print a unsigned uint_32 from stack.
 */
            case iuprint:
                MvM::log(std::to_string(stack.popUnsignedInt()));
                break;
/**
 * push a const int_64 into the stack.
 */
            case lconst:
                stack.pushLong(ops.getLong());
                break;
/**
 * push a const int_64 into the stack (value = 0).
 */
            case lconst_0:
                stack.pushLong(0);
                break;
/**
 * push a const int_64 into the stack (value = 1).
 */
            case lconst_1:
                stack.pushLong(1);
                break;
/**
 * push a const int_64 into the stack (value = 2).
 */
            case lconst_2:
                stack.pushLong(2);
                break;
/**
 * push a const int_64 into the stack (value = 3).
 */
            case lconst_3:
                stack.pushLong(3);
                break;
/**
 * push a const int_64 into the stack (value = 4).
 */
            case lconst_4:
                stack.pushLong(4);
                break;
/**
 * push a const int_64 into the stack (value = 5).
 */
            case lconst_5:
                stack.pushLong(5);
                break;
/**
 * push a const int_64 into the stack (value = 6).
 */
            case lconst_6:
                stack.pushLong(6);
                break;
/**
 * push a const int_64 into the stack (value = 9).
 */
            case lconst_9:
                stack.pushLong(9);
                break;
/**
 * push a const int_64 into the stack (value = 10).
 */
            case lconst_10:
                stack.pushLong(10);
                break;
/**
 * push a const int_64 into the stack (value = 11).
 */
            case lconst_11:
                stack.pushLong(11);
                break;
/**
 * push a const int_64 into the stack (value = 12).
 */
            case lconst_12:
                stack.pushLong(12);
                break;
/**
 * load a int_64 into the stack from local variable.
 */
            case lload:
                stack.pushLong(lvt[ops.getUnsignedShort()].Long);
                break;
/**
 * load a int_64 into the stack from local variable 0.
 */
            case lload_0:
                stack.pushLong(lvt[0].Long);
                break;
/**
 * load a int_64 into the stack from local variable 1.
 */
            case lload_1:
                stack.pushLong(lvt[1].Long);
                break;
/**
 * load a int_64 into the stack from local variable 2.
 */
            case lload_2:
                stack.pushLong(lvt[2].Long);
                break;
/**
 * load a int_64 into the stack from local variable 3.
 */
            case lload_3:
                stack.pushLong(lvt[3].Long);
                break;
/**
 * load a int_64 into the stack from local variable 4.
 */
            case lload_4:
                stack.pushLong(lvt[4].Long);
                break;
/**
 * store a int_64 from stack into local variable.
 */
            case lstore:
                lvt[ops.getUnsignedShort()] = MvM::lve_Long(stack.popLong());
                break;
/**
 * store a int_64 from stack into local variable 0.
 */
            case lstore_0:
                lvt[0] = MvM::lve_Long(stack.popLong());
                break;
/**
 * store a int_64 from stack into local variable 1.
 */
            case lstore_1:
                lvt[1] = MvM::lve_Long(stack.popLong());
                break;
/**
 * store a int_64 from stack into local variable 2.
 */
            case lstore_2:
                lvt[2] = MvM::lve_Long(stack.popLong());
                break;
/**
 * store a int_64 from stack into local variable 3.
 */
            case lstore_3:
                lvt[3] = MvM::lve_Long(stack.popLong());
                break;
/**
 * store a int_64 from stack into local variable 4.
 */
            case lstore_4:
                lvt[4] = MvM::lve_Long(stack.popLong());
                break;
/**
 * add two Longs.
 */
            case ladd:
                stack.pushLong(stack.popLong() + stack.popLong());
                break;
/**
 * add two UnsignedUnsignedLongs.
 */
            case luadd:
                stack.pushUnsignedLong(stack.popUnsignedLong() + stack.popUnsignedLong());
                break;
/**
 * subtract two Longs.
 */
            case lsub:
                stack.pushLong(stack.popLong() - stack.popLong());
                break;
/**
 * subtract two UnsignedUnsignedLongs.
 */
            case lusub:
                stack.pushUnsignedLong(stack.popUnsignedLong() - stack.popUnsignedLong());
                break;
/**
 * multiply two Longs.
 */
            case lmul:
                stack.pushLong(stack.popLong() * stack.popLong());
                break;
/**
 * multiply two UnsignedUnsignedLongs.
 */
            case lumul:
                stack.pushUnsignedLong(stack.popUnsignedLong() * stack.popUnsignedLong());
                break;
/**
 * divide two Longs.
 */
            case ldiv_:
                stack.pushLong(stack.popLong() / stack.popLong());
                break;
/**
 * divide two UnsignedUnsignedLongs.
 */
            case ludiv:
                stack.pushUnsignedLong(stack.popUnsignedLong() / stack.popUnsignedLong());
                break;
/**
 * set a int_64 from stack into a field on pointer.
 */
            case lset:
                MvM::accessMemoryAndSetLong(stack.popPointer(), stack.popUnsignedLong(), stack.popLong());
                break;
/**
 * get a int_64 from a field on a pointer to stack.
 */
            case lget:
                stack.pushLong(MvM::accessMemoryAndGetLong(stack.popPointer(), stack.popUnsignedLong()));
                break;
/**
 * increment a local variable int_64 by 1.
 */
            case linc1:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].Long = lvt[point].Long + 1; }
                break;
/**
 * increment a local variable int_64 by 2.
 */
            case linc2:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].Long = lvt[point].Long + 2; }
                break;
/**
 * store a int_64 from main stack in a local variable..
 */
            case lmainst:
                lvt[ops.getUnsignedShort()].Long = stack_main.popLong();
                break;
/**
 * store a int_64 from main stack in local variable 0.
 */
            case lmainst_0:
                lvt[0].Long = stack_main.popLong();;
                break;
/**
 * store a int_64 from main stack in local variable 1.
 */
            case lmainst_1:
                lvt[1].Long = stack_main.popLong();;
                break;
/**
 * store a int_64 from main stack in local variable 2.
 */
            case lmainst_2:
                lvt[2].Long = stack_main.popLong();;
                break;
/**
 * store a int_64 from main stack in local variable 3.
 */
            case lmainst_3:
                lvt[3].Long = stack_main.popLong();;
                break;
/**
 * print a int_64 from stack.
 */
            case lprint:
                MvM::log(std::to_string(stack.popLong()));
                break;
/**
 * print a unsigned uint_64 from stack.
 */
            case luprint:
                MvM::log(std::to_string(stack.popUnsignedLong()));
                break;
/**
 * push a const int_128 into the stack.
 */
            case liconst:
                stack.pushLongInt(ops.getLongInt());
                break;
/**
 * push a const int_128 into the stack (value = 0).
 */
            case liconst_0:
                stack.pushLongInt(0);
                break;
/**
 * load a int_128 into the stack from local variable.
 */
            case liload:
                stack.pushLongInt(lvt[ops.getUnsignedShort()].LongInt);
                break;
/**
 * store a int_128 from stack into local variable.
 */
            case listore:
                lvt[ops.getUnsignedShort()] = MvM::lve_LongInt(stack.popLongInt());
                break;
/**
 * add two LongInts.
 */
            case liadd:
                stack.pushLongInt(stack.popLongInt() + stack.popLongInt());
                break;
/**
 * add two UnsignedUnsignedLongInts.
 */
            case liuadd:
                stack.pushUnsignedLongInt(stack.popUnsignedLongInt() + stack.popUnsignedLongInt());
                break;
/**
 * subtract two LongInts.
 */
            case lisub:
                stack.pushLongInt(stack.popLongInt() - stack.popLongInt());
                break;
/**
 * subtract two UnsignedUnsignedLongInts.
 */
            case liusub:
                stack.pushUnsignedLongInt(stack.popUnsignedLongInt() - stack.popUnsignedLongInt());
                break;
/**
 * multiply two LongInts.
 */
            case limul:
                stack.pushLongInt(stack.popLongInt() * stack.popLongInt());
                break;
/**
 * multiply two UnsignedUnsignedLongInts.
 */
            case liumul:
                stack.pushUnsignedLongInt(stack.popUnsignedLongInt() * stack.popUnsignedLongInt());
                break;
/**
 * divide two LongInts.
 */
            case lidiv:
                stack.pushLongInt(stack.popLongInt() / stack.popLongInt());
                break;
/**
 * divide two UnsignedUnsignedLongInts.
 */
            case liudiv:
                stack.pushUnsignedLongInt(stack.popUnsignedLongInt() / stack.popUnsignedLongInt());
                break;
/**
 * set a int_128 from stack into a field on pointer.
 */
            case liset:
                MvM::accessMemoryAndSetLongInt(stack.popPointer(), stack.popUnsignedLong(), stack.popLongInt());
                break;
/**
 * get a int_128 from a field on a pointer to stack.
 */
            case liget:
                stack.pushLongInt(MvM::accessMemoryAndGetLongInt(stack.popPointer(), stack.popUnsignedLong()));
                break;
/**
 * store a int_128 from main stack in a local variable..
 */
            case limainst:
                lvt[ops.getUnsignedShort()].LongInt = stack_main.popLongInt();
                break;
/**
 * print a int_128 from stack.
 */
            case liprint:
                MvM::log(std::to_string(stack.popLongInt()));
                break;
/**
 * print a unsigned uint_128 from stack.
 */
            case liuprint:
                MvM::log(std::to_string(stack.popUnsignedLongInt()));
                break;
/**
 * push a const int_256 into the stack.
 */
            case llconst:
                stack.pushLongLong(ops.getLongLong());
                break;
/**
 * push a const int_256 into the stack (value = 0).
 */
            case llconst_0:
                stack.pushLongLong(0);
                break;
/**
 * load a int_256 into the stack from local variable.
 */
            case llload:
                stack.pushLongLong(lvt[ops.getUnsignedShort()].LongLong);
                break;
/**
 * store a int_256 from stack into local variable.
 */
            case llstore:
                lvt[ops.getUnsignedShort()] = MvM::lve_LongLong(stack.popLongLong());
                break;
/**
 * add two LongLongs.
 */
            case lladd:
                stack.pushLongLong(stack.popLongLong() + stack.popLongLong());
                break;
/**
 * add two UnsignedUnsignedLongLongs.
 */
            case lluadd:
                stack.pushUnsignedLongLong(stack.popUnsignedLongLong() + stack.popUnsignedLongLong());
                break;
/**
 * subtract two LongLongs.
 */
            case llsub:
                stack.pushLongLong(stack.popLongLong() - stack.popLongLong());
                break;
/**
 * subtract two UnsignedUnsignedLongLongs.
 */
            case llusub:
                stack.pushUnsignedLongLong(stack.popUnsignedLongLong() - stack.popUnsignedLongLong());
                break;
/**
 * multiply two LongLongs.
 */
            case llmul:
                stack.pushLongLong(stack.popLongLong() * stack.popLongLong());
                break;
/**
 * multiply two UnsignedUnsignedLongLongs.
 */
            case llumul:
                stack.pushUnsignedLongLong(stack.popUnsignedLongLong() * stack.popUnsignedLongLong());
                break;
/**
 * divide two LongLongs.
 */
            case lldiv_:
                stack.pushLongLong(stack.popLongLong() / stack.popLongLong());
                break;
/**
 * divide two UnsignedUnsignedLongLongs.
 */
            case lludiv:
                stack.pushUnsignedLongLong(stack.popUnsignedLongLong() / stack.popUnsignedLongLong());
                break;
/**
 * set a int_256 from stack into a field on pointer.
 */
            case llset:
                MvM::accessMemoryAndSetLongLong(stack.popPointer(), stack.popUnsignedLong(), stack.popLongLong());
                break;
/**
 * get a int_256 from a field on a pointer to stack.
 */
            case llget:
                stack.pushLongLong(MvM::accessMemoryAndGetLongLong(stack.popPointer(), stack.popUnsignedLong()));
                break;
/**
 * store a int_256 from main stack in a local variable..
 */
            case llmainst:
                lvt[ops.getUnsignedShort()].LongLong = stack_main.popLongLong();
                break;
/**
 * print a int_256 from stack.
 */
            case llprint:
                MvM::log(std::to_string(stack.popLongLong()));
                break;
/**
 * print a unsigned uint_256 from stack.
 */
            case lluprint:
                MvM::log(std::to_string(stack.popUnsignedLongLong()));
                break;
/**
 * push a const flt_32 into the stack.
 */
            case fconst:
                stack.pushFloat(ops.getFloat());
                break;
/**
 * push a const flt_32 into the stack (value = 0).
 */
            case fconst_0:
                stack.pushFloat(0);
                break;
/**
 * load a flt_32 into the stack from local variable.
 */
            case fload:
                stack.pushFloat(lvt[ops.getUnsignedShort()].Float);
                break;
/**
 * store a flt_32 from stack into local variable.
 */
            case fstore:
                lvt[ops.getUnsignedShort()] = MvM::lve_Float(stack.popFloat());
                break;
/**
 * set a flt_32 from stack into a field on pointer.
 */
            case fset:
                MvM::accessMemoryAndSetFloat(stack.popPointer(), stack.popUnsignedLong(), stack.popFloat());
                break;
/**
 * get a flt_32 from a field on a pointer to stack.
 */
            case fget:
                stack.pushFloat(MvM::accessMemoryAndGetFloat(stack.popPointer(), stack.popUnsignedLong()));
                break;
/**
 * store a flt_32 from main stack in a local variable..
 */
            case fmainst:
                lvt[ops.getUnsignedShort()].Float = stack_main.popFloat();
                break;
/**
 * push a const flt_64 into the stack.
 */
            case dconst:
                stack.pushDouble(ops.getDouble());
                break;
/**
 * push a const flt_64 into the stack (value = 0).
 */
            case dconst_0:
                stack.pushDouble(0);
                break;
/**
 * load a flt_64 into the stack from local variable.
 */
            case dload:
                stack.pushDouble(lvt[ops.getUnsignedShort()].Double);
                break;
/**
 * store a flt_64 from stack into local variable.
 */
            case dstore:
                lvt[ops.getUnsignedShort()] = MvM::lve_Double(stack.popDouble());
                break;
/**
 * set a flt_64 from stack into a field on pointer.
 */
            case dset:
                MvM::accessMemoryAndSetDouble(stack.popPointer(), stack.popUnsignedLong(), stack.popDouble());
                break;
/**
 * get a flt_64 from a field on a pointer to stack.
 */
            case dget:
                stack.pushDouble(MvM::accessMemoryAndGetDouble(stack.popPointer(), stack.popUnsignedLong()));
                break;
/**
 * store a flt_64 from main stack in a local variable..
 */
            case dmainst:
                lvt[ops.getUnsignedShort()].Double = stack_main.popDouble();
                break;
/**
 * push a const flt_128 into the stack.
 */
            case dfconst:
                stack.pushDoubleFloat(ops.getDoubleFloat());
                break;
/**
 * push a const flt_128 into the stack (value = 0).
 */
            case dfconst_0:
                stack.pushDoubleFloat(0);
                break;
/**
 * load a flt_128 into the stack from local variable.
 */
            case dfload:
                stack.pushDoubleFloat(lvt[ops.getUnsignedShort()].DoubleFloat);
                break;
/**
 * store a flt_128 from stack into local variable.
 */
            case dfstore:
                lvt[ops.getUnsignedShort()] = MvM::lve_DoubleFloat(stack.popDoubleFloat());
                break;
/**
 * set a flt_128 from stack into a field on pointer.
 */
            case dfset:
                MvM::accessMemoryAndSetDoubleFloat(stack.popPointer(), stack.popUnsignedLong(), stack.popDoubleFloat());
                break;
/**
 * get a flt_128 from a field on a pointer to stack.
 */
            case dfget:
                stack.pushDoubleFloat(MvM::accessMemoryAndGetDoubleFloat(stack.popPointer(), stack.popUnsignedLong()));
                break;
/**
 * store a flt_128 from main stack in a local variable..
 */
            case dfmainst:
                lvt[ops.getUnsignedShort()].DoubleFloat = stack_main.popDoubleFloat();
                break;
/**
 * push a const flt_256 into the stack.
 */
            case ddconst:
                stack.pushDoubleDouble(ops.getDoubleDouble());
                break;
/**
 * push a const flt_256 into the stack (value = 0).
 */
            case ddconst_0:
                stack.pushDoubleDouble(0);
                break;
/**
 * load a flt_256 into the stack from local variable.
 */
            case ddload:
                stack.pushDoubleDouble(lvt[ops.getUnsignedShort()].DoubleDouble);
                break;
/**
 * store a flt_256 from stack into local variable.
 */
            case ddstore:
                lvt[ops.getUnsignedShort()] = MvM::lve_DoubleDouble(stack.popDoubleDouble());
                break;
/**
 * set a flt_256 from stack into a field on pointer.
 */
            case ddset:
                MvM::accessMemoryAndSetDoubleDouble(stack.popPointer(), stack.popUnsignedLong(), stack.popDoubleDouble());
                break;
/**
 * get a flt_256 from a field on a pointer to stack.
 */
            case ddget:
                stack.pushDoubleDouble(MvM::accessMemoryAndGetDoubleDouble(stack.popPointer(), stack.popUnsignedLong()));
                break;
/**
 * store a flt_256 from main stack in a local variable..
 */
            case ddmainst:
                lvt[ops.getUnsignedShort()].DoubleDouble = stack_main.popDoubleDouble();
                break;
/**
 * push a const pointer into the stack.
 */
            case aconst:
                stack.pushPointer(ops.getPointer());
                break;
/**
 * push a const pointer into the stack (value = 0).
 */
            case aconst_0:
                stack.pushPointer(0);
                break;
/**
 * load a pointer into the stack from local variable.
 */
            case aload:
                stack.pushPointer(lvt[ops.getUnsignedShort()].Pointer);
                break;
/**
 * store a pointer from stack into local variable.
 */
            case astore:
                lvt[ops.getUnsignedShort()] = MvM::lve_Pointer(stack.popPointer());
                break;
/**
 * set a pointer from stack into a field on pointer.
 */
            case aset:
                MvM::accessMemoryAndSetPointer(stack.popPointer(), stack.popUnsignedLong(), stack.popPointer());
                break;
/**
 * get a pointer from a field on a pointer to stack.
 */
            case aget:
                stack.pushPointer(MvM::accessMemoryAndGetPointer(stack.popPointer(), stack.popUnsignedLong()));
                break;
/**
 * store a pointer from main stack in a local variable..
 */
            case amainst:
                lvt[ops.getUnsignedShort()].Pointer = stack_main.popPointer();
                break;

        }
    }
}

void MvM::log_err(const std::string msg)
{
    std::cerr << msg;
}

void MvM::log(const std::string msg)
{
    std::cout << msg;
}

pointer MvM::accessMemoryAndGetPointer(pointer base, uint_32 address)
{
    return *((pointer*) (base + address));
}

void MvM::accessMemoryAndSetPointer(pointer base, uint_32 address, pointer byte)
{
    *((pointer*) (base + address)) = byte;
}

flt_256 MvM::accessMemoryAndGetDoubleDouble(pointer base, uint_32 address)
{
    return *((flt_256*) (base + address));
}

void MvM::accessMemoryAndSetDoubleDouble(pointer base, uint_32 address, flt_256 byte)
{
    *((flt_256*) (base + address)) = byte;
}

flt_128 MvM::accessMemoryAndGetDoubleFloat(pointer base, uint_32 address)
{
    return *((flt_128*) (base + address));
}

void MvM::accessMemoryAndSetDoubleFloat(pointer base, uint_32 address, flt_128 byte)
{
    *((flt_128*) (base + address)) = byte;
}

flt_64 MvM::accessMemoryAndGetDouble(pointer base, uint_32 address)
{
    return *((flt_64*) (base + address));
}

void MvM::accessMemoryAndSetDouble(pointer base, uint_32 address, flt_64 byte)
{
    *((flt_64*) (base + address)) = byte;
}

flt_32 MvM::accessMemoryAndGetFloat(pointer base, uint_32 address)
{
    return *((flt_32*) (base + address));
}

void MvM::accessMemoryAndSetFloat(pointer base, uint_32 address, flt_32 byte)
{
    *((flt_32*) (base + address)) = byte;
}

uint_256 MvM::accessMemoryAndGetUnsignedLongLong(pointer base, uint_32 address)
{
    return *((uint_256*) (base + address));
}

void MvM::accessMemoryAndSetUnsignedLongLong(pointer base, uint_32 address, uint_256 byte)
{
    *((uint_256*) (base + address)) = byte;
}

int_256 MvM::accessMemoryAndGetLongLong(pointer base, uint_32 address)
{
    return *((int_256*) (base + address));
}

void MvM::accessMemoryAndSetLongLong(pointer base, uint_32 address, int_256 byte)
{
    *((int_256*) (base + address)) = byte;
}

uint_128 MvM::accessMemoryAndGetUnsignedLongInt(pointer base, uint_32 address)
{
    return *((uint_128*) (base + address));
}

void MvM::accessMemoryAndSetUnsignedLongInt(pointer base, uint_32 address, uint_128 byte)
{
    *((uint_128*) (base + address)) = byte;
}

int_128 MvM::accessMemoryAndGetLongInt(pointer base, uint_32 address)
{
    return *((int_128*) (base + address));
}

void MvM::accessMemoryAndSetLongInt(pointer base, uint_32 address, int_128 byte)
{
    *((int_128*) (base + address)) = byte;
}

uint_64 MvM::accessMemoryAndGetUnsignedLong(pointer base, uint_32 address)
{
    return *((int_64*) (base + address));
}

void MvM::accessMemoryAndSetUnsignedLong(pointer base, uint_32 address, uint_64 byte)
{
    *((uint_64*) (base + address)) = byte;
}

int_64 MvM::accessMemoryAndGetLong(pointer base, uint_32 address)
{
    return *((int_64*) (base + address));
}

void MvM::accessMemoryAndSetLong(pointer base, uint_32 address, int_64 byte)
{
    *((int_64*) (base + address)) = byte;
}

uint_32 MvM::accessMemoryAndGetUnsignedInt(pointer base, uint_32 address)
{
    return *((int_32*) (base + address));
}

void MvM::accessMemoryAndSetUnsignedInt(pointer base, uint_32 address, uint_32 byte)
{
    *((uint_32*) (base + address)) = byte;
}

int_32 MvM::accessMemoryAndGetInt(pointer base, uint_32 address)
{
    return *((int_32*) (base + address));
}

void MvM::accessMemoryAndSetInt(pointer base, uint_32 address, int_32 byte)
{
    *((int_32*) (base + address)) = byte;
}

uint_16 MvM::accessMemoryAndGetUnsignedShort(pointer base, uint_32 address)
{
    return *((uint_16*) (base + address));
}

void MvM::accessMemoryAndSetUnsignedShort(pointer base, uint_32 address, uint_16 byte)
{
    *((uint_16*) (base + address)) = byte;
}

int_16 MvM::accessMemoryAndGetShort(pointer base, uint_32 address)
{
    return *((int_16*) (base + address));
}

void MvM::accessMemoryAndSetShort(pointer base, uint_32 address, int_16 byte)
{
    *((int_16*) (base + address)) = byte;
}

uint_8 MvM::accessMemoryAndGetUnsignedtByte(pointer base, uint_32 address)
{
    return *(base + address);
}

void MvM::accessMemoryAndSetUnsignedByte(pointer base, uint_32 address, uint_8 byte)
{
    *(base + address) = byte;
}

int_8 MvM::accessMemoryAndGetByte(pointer base, int_32 address)
{
    return *(base + address);
}

void MvM::accessMemoryAndSetByte(pointer base, uint_32 address, int_8 byte)
{
    *(base + address) = byte;
}

localvarelement MvM::lve_UnsignedLongLong(uint_256 byte)
{
    localvarelement localvarelement1;
//        localvarelement1.unsignedByte = byte;

    return localvarelement1;
}

localvarelement MvM::lve_UnsignedLongInt(uint_128 byte)
{
    localvarelement localvarelement1;
//        localvarelement1.unsignedByte = byte;

    return localvarelement1;
}

localvarelement MvM::lve_UnsignedLong(uint_64 byte)
{
    localvarelement localvarelement1;
    localvarelement1.UnsignedLong = byte;

    return localvarelement1;
}

localvarelement MvM::lve_UnsignedInt(uint_32 byte)
{
    localvarelement localvarelement1;
    localvarelement1.UnsignedInt = byte;

    return localvarelement1;
}

localvarelement MvM::lve_UnsignedShort(uint_16 byte)
{
    localvarelement localvarelement1;
    localvarelement1.UnsignedShort = byte;

    return localvarelement1;
}

localvarelement MvM::lve_UnsignedByte(uint_8 byte)
{
    localvarelement localvarelement1;
    localvarelement1.UnsignedByte = byte;

    return localvarelement1;
}

localvarelement MvM::lve_Pointer(pointer byte)
{
    localvarelement result;
    return result;
}

localvarelement MvM::lve_DoubleDouble(flt_256 byte)
{
    localvarelement localvarelement1;
//        localvarelement1.unsignedByte = byte;

    return localvarelement1;
}

localvarelement MvM::lve_DoubleFloat(flt_128 byte)
{
    localvarelement localvarelement1;
//        localvarelement1.signedInt = byte;

    return localvarelement1;
}

localvarelement MvM::lve_Double(flt_64 byte)
{
    localvarelement localvarelement1;
    localvarelement1.Double = byte;

    return localvarelement1;
}

localvarelement MvM::lve_Float(flt_32 byte)
{
    localvarelement localvarelement1;
    localvarelement1.Float = byte;

    return localvarelement1;
}

localvarelement MvM::lve_LongLong(int_256 byte)
{
    localvarelement localvarelement1;
//        localvarelement1.unsignedByte = byte;

    return localvarelement1;
}

localvarelement MvM::lve_LongInt(int_128 byte)
{
    localvarelement localvarelement1;
//        localvarelement1.unsignedByte = byte;

    return localvarelement1;
}

localvarelement MvM::lve_Long(int_64 byte)
{
    localvarelement localvarelement1;
    localvarelement1.Long = byte;

    return localvarelement1;
}

localvarelement MvM::lve_Int(int_32 byte)
{
    localvarelement localvarelement1;
    localvarelement1.Int = byte;

    return localvarelement1;
}

localvarelement MvM::lve_Short(int_16 byte)
{
    localvarelement localvarelement1;
    localvarelement1.Short = byte;

    return localvarelement1;
}

localvarelement MvM::lve_Byte(int_8 byte)
{
    localvarelement localvarelement1;
    localvarelement1.Byte = byte;

    return localvarelement1;
}

void MvM::Init()
{
    if (IsBigEndian())
        Endianness = true;
    else Endianness = false;
}

bool MvM::IsBigEndian()
{
    return !IsLittleEndian();
}

bool MvM::IsLittleEndian()
{
    int i = 1;

    return (int) *((unsigned char *) &i) == 1;
}

void MvM::printString(const pointer string)
{
    uint_16 length = accessMemoryAndGetUnsignedShort(string, 0);

    for (int i = 0; i < length; i ++)
        std::cout << ((unsigned char) accessMemoryAndGetUnsignedtByte(string, 2 + i));
}

long long int MvM::gtimens()
{
    return std::chrono::duration_cast< std::chrono::nanoseconds >(std::chrono::system_clock::now().time_since_epoch()).count();
}

long long int MvM::gtimems()
{
    return std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count();
}

pointer Stack::peekPointer()
{
    return (pointer) (intptr_t) peekUnsignedLong();
}
