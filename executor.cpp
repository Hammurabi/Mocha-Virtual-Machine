
#include "executor.h"

bool Endianness;

// struct bytearray{
    // uint_64 length;
    // pointer array;
// };

//
// Created by Riverssen on 07.11.18.
//
void MvM::execute(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack stack_main, OP_STACK ops)
{
    Stack stack;
    std::map<unsigned int, localvarelement> lvt;
    std::map<unsigned int, unsigned long long> CHECK_POINTS;
    pointer base = basePointer;

    while (ops.getRemaining() > 0)
    {
        Op op_undefinedcurrent = ops.getOp();
//        std::cout << op_undefinedcurrent << " " << ops.address << std::endl;

        switch (op_undefinedcurrent)
        {
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
 *invoke a static method.
 */
            case invokestatic:
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
            case invokenative:
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
 *load an int_8 from a pointer.
 */
            case abload:
                stack.pushByte(accessMemoryAndGetByte(stack.popPointer(), stack.popUnsignedLong()));
                break;
/**
 *load an int_16 from a pointer.
 */
            case asload:
                stack.pushShort(accessMemoryAndGetShort(stack.popPointer(), stack.popUnsignedLong()));
                break;
/**
 *load an int_32 from a pointer.
 */
            case aiload:
                stack.pushInt(accessMemoryAndGetInt(stack.popPointer(), stack.popUnsignedLong()));
                break;
/**
 *load an int_64 from a pointer.
 */
            case alload:
                stack.pushLong(accessMemoryAndGetLong(stack.popPointer(), stack.popUnsignedLong()));
                break;
/**
 *load an int_128 from a pointer.
 */
            case aliload:
                stack.pushLongInt(accessMemoryAndGetLongInt(stack.popPointer(), stack.popUnsignedLong()));
                break;
/**
 *load an int_256 from a pointer.
 */
            case allload:
                stack.pushLongLong(accessMemoryAndGetLongLong(stack.popPointer(), stack.popUnsignedLong()));
                break;
/**
 *load an flt_32 from a pointer.
 */
            case afload:
                stack.pushFloat(accessMemoryAndGetFloat(stack.popPointer(), stack.popUnsignedLong()));
                break;
/**
 *load an flt_64 from a pointer.
 */
            case adload:
                stack.pushDouble(accessMemoryAndGetDouble(stack.popPointer(), stack.popUnsignedLong()));
                break;
/**
 *load an flt_128 from a pointer.
 */
            case adfload:
                stack.pushDoubleFloat(accessMemoryAndGetDoubleFloat(stack.popPointer(), stack.popUnsignedLong()));
                break;
/**
 *load an flt_256 from a pointer.
 */
            case addload:
                stack.pushDoubleDouble(accessMemoryAndGetDoubleDouble(stack.popPointer(), stack.popUnsignedLong()));
                break;
/**
 *load a pointer from a pointer.
 */
            case aaload:
                stack.pushPointer(accessMemoryAndGetPointer(stack.popPointer(), stack.popUnsignedLong()));
                break;
/**
 *store an int_8 in a pointer.
 */
            case abstore:
                (accessMemoryAndSetByte(stack.popPointer(), stack.popUnsignedLong(), stack.popByte()));
                break;
/**
 *store an int_16 in a pointer.
 */
            case asstore:
                (accessMemoryAndSetShort(stack.popPointer(), stack.popUnsignedLong(), stack.popShort()));
                break;
/**
 *store an int_32 in a pointer.
 */
            case aistore:
                (accessMemoryAndSetInt(stack.popPointer(), stack.popUnsignedLong(), stack.popInt()));
                break;
/**
 *store an int_64 in a pointer.
 */
            case alstore:
                (accessMemoryAndSetLong(stack.popPointer(), stack.popUnsignedLong(), stack.popLong()));
                break;
/**
 *store an int_128 in a pointer.
 */
            case alistore:
                (accessMemoryAndSetLongInt(stack.popPointer(), stack.popUnsignedLong(), stack.popLongInt()));
                break;
/**
 *store an int_256 in a pointer.
 */
            case allstore:
                (accessMemoryAndSetLongLong(stack.popPointer(), stack.popUnsignedLong(), stack.popLongLong()));
                break;
/**
 *store an flt_32 in a pointer.
 */
            case afstore:
                (accessMemoryAndSetFloat(stack.popPointer(), stack.popUnsignedLong(), stack.popFloat()));
                break;
/**
 *store an flt_64 in a pointer.
 */
            case adstore:
                (accessMemoryAndSetDouble(stack.popPointer(), stack.popUnsignedLong(), stack.popDouble()));
                break;
/**
 *store an flt_128 in a pointer.
 */
            case adfstore:
                (accessMemoryAndSetDoubleFloat(stack.popPointer(), stack.popUnsignedLong(), stack.popDoubleFloat()));
                break;
/**
 *store an flt_256 in a pointer.
 */
            case addstore:
                (accessMemoryAndSetDoubleDouble(stack.popPointer(), stack.popUnsignedLong(), stack.popDoubleDouble()));
                break;
/**
 *store a pointer in a pointer.
 */
            case aastore:
                (accessMemoryAndSetPointer(stack.popPointer(), stack.popUnsignedLong(), stack.popPointer()));
                break;
/**
 *push a byte array.
 */
            case baconst:
            { uint_64 length = stack.popUnsignedLong(); pointer p = static_cast<pointer> (calloc(length, length)); stack.pushPointer(p); accessMemoryAndSetUnsignedLong(p, 0, length); }
                break;
/**
 *push a byte array using size_int16_t
 */
            case baconsts:
            { uint_64 length = static_cast<uint_64> (stack.popUnsignedShort()); pointer p = static_cast<pointer> (calloc(length, length)); stack.pushPointer(p); accessMemoryAndSetUnsignedLong(p, 0, length); }
                break;
/**
 *push a byte array using size_int32_t
 */
            case baconsti:
            { uint_64 length = static_cast<uint_64> (stack.popUnsignedInt()); pointer p = static_cast<pointer> (calloc(length, length)); stack.pushPointer(p); accessMemoryAndSetUnsignedLong(p, 0, length); }
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
            { stack.pushUnsignedLong(static_cast<uint_64> (accessMemoryAndGetLong(stack.popPointer(), 0))); }
                break;
/**
 *print a byte array.
 */
            case printba:
            { pointer bytearray = stack.popPointer(); uint_64 bytearraysize   = static_cast<uint_64> (accessMemoryAndGetLong(bytearray, 0)); std::string data = "["; for (uint_64 i = 0; i < bytearraysize; i ++) data += std::to_string(accessMemoryAndGetByte(bytearray + 8, i)) + ((i < bytearraysize - 1) ? ", " : "]"); log(data); }
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
 * push a const int_8 into the stack (value = 1).
 */
            case bconst_1:
                stack.pushByte(1);
                break;
/**
 * push a const int_8 into the stack (value = 2).
 */
            case bconst_2:
                stack.pushByte(2);
                break;
/**
 * push a const int_8 into the stack (value = 3).
 */
            case bconst_3:
                stack.pushByte(3);
                break;
/**
 * push a const int_8 into the stack (value = 4).
 */
            case bconst_4:
                stack.pushByte(4);
                break;
/**
 * push a const int_8 into the stack (value = 5).
 */
            case bconst_5:
                stack.pushByte(5);
                break;
/**
 * push a const int_8 into the stack (value = 6).
 */
            case bconst_6:
                stack.pushByte(6);
                break;
/**
 * push a const int_8 into the stack (value = 9).
 */
            case bconst_9:
                stack.pushByte(9);
                break;
/**
 * push a const int_8 into the stack (value = 10).
 */
            case bconst_10:
                stack.pushByte(10);
                break;
/**
 * push a const int_8 into the stack (value = 11).
 */
            case bconst_11:
                stack.pushByte(11);
                break;
/**
 * push a const int_8 into the stack (value = 12).
 */
            case bconst_12:
                stack.pushByte(12);
                break;
/**
 * load a int_8 into the stack from local variable.
 */
            case bload:
                stack.pushByte(lvt[ops.getUnsignedShort()].Byte);
                break;
/**
 * load a int_8 into the stack from local variable 0.
 */
            case bload_0:
                stack.pushByte(lvt[0].Byte);
                break;
/**
 * load a int_8 into the stack from local variable 1.
 */
            case bload_1:
                stack.pushByte(lvt[1].Byte);
                break;
/**
 * load a int_8 into the stack from local variable 2.
 */
            case bload_2:
                stack.pushByte(lvt[2].Byte);
                break;
/**
 * load a int_8 into the stack from local variable 3.
 */
            case bload_3:
                stack.pushByte(lvt[3].Byte);
                break;
/**
 * load a int_8 into the stack from local variable 4.
 */
            case bload_4:
                stack.pushByte(lvt[4].Byte);
                break;
/**
 * store a int_8 from stack into local variable.
 */
            case bstore:
                lvt[ops.getUnsignedShort()] = lve_Byte(stack.popByte());
                break;
/**
 * store a int_8 from stack into local variable 0.
 */
            case bstore_0:
                lvt[0] = lve_Byte(stack.popByte());
                break;
/**
 * store a int_8 from stack into local variable 1.
 */
            case bstore_1:
                lvt[1] = lve_Byte(stack.popByte());
                break;
/**
 * store a int_8 from stack into local variable 2.
 */
            case bstore_2:
                lvt[2] = lve_Byte(stack.popByte());
                break;
/**
 * store a int_8 from stack into local variable 3.
 */
            case bstore_3:
                lvt[3] = lve_Byte(stack.popByte());
                break;
/**
 * store a int_8 from stack into local variable 4.
 */
            case bstore_4:
                lvt[4] = lve_Byte(stack.popByte());
                break;
/**
 * cast int_8 to type Byte.
 */
            case bcast_b:
                stack.pushByte(static_cast<int_8> (stack.popByte()));
                break;
/**
 * cast unsigned uint_8 to type Byte.
 */
            case bucast_b:
                stack.pushByte(static_cast<int_8> (stack.popUnsignedByte()));
                break;
/**
 * add int_8 with type Byte.
 */
            case badd_b:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popByte();
                stack.pushByte(a + b);
            }
                break;
/**
 * add unsigned uint_8 with type Byte.
 */
            case buadd_b:
            {
                uint_8 b = stack.popUnsignedByte();
                int_8 a = stack.popByte();
                stack.pushByte(a + b);
            }
                break;
/**
 * subtract int_8 with type Byte.
 */
            case bsub_b:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popByte();
                stack.pushByte(a - b);
            }
                break;
/**
 * subtract unsigned uint_8 with type Byte.
 */
            case busub_b:
            {
                uint_8 b = stack.popUnsignedByte();
                int_8 a = stack.popByte();
                stack.pushByte(a - b);
            }
                break;
/**
 * multiply int_8 with type Byte.
 */
            case bmul_b:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popByte();
                stack.pushByte(a * b);
            }
                break;
/**
 * multiply unsigned uint_8 with type Byte.
 */
            case bumul_b:
            {
                uint_8 b = stack.popUnsignedByte();
                int_8 a = stack.popByte();
                stack.pushByte(a * b);
            }
                break;
/**
 * divide int_8 with type Byte.
 */
            case bdiv_b:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popByte();
                stack.pushByte(a / b);
            }
                break;
/**
 * divide unsigned uint_8 with type Byte.
 */
            case budiv_b:
            {
                uint_8 b = stack.popUnsignedByte();
                int_8 a = stack.popByte();
                stack.pushByte(a / b);
            }
                break;
/**
 * compare int_8 less than type Byte.
 */
            case bcmpl_b:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popByte();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than type Byte.
 */
            case bucmpl_b:
            {
                uint_8 b = stack.popUnsignedByte();
                int_8 a = stack.popByte();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than type Byte.
 */
            case bcmpg_b:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popByte();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than type Byte.
 */
            case bucmpg_b:
            {
                uint_8 b = stack.popUnsignedByte();
                int_8 a = stack.popByte();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 equal with type Byte.
 */
            case bcmpe_b:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popByte();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 equal with type Byte.
 */
            case bucmpe_b:
            {
                uint_8 b = stack.popUnsignedByte();
                int_8 a = stack.popByte();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 less than or equal to type Byte.
 */
            case bcmple_b:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popByte();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than or equal to type Byte.
 */
            case bucmple_b:
            {
                uint_8 b = stack.popUnsignedByte();
                int_8 a = stack.popByte();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than or equal to type Byte.
 */
            case bcmpge_b:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popByte();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than or equal to type Byte.
 */
            case bucmpge_b:
            {
                uint_8 b = stack.popUnsignedByte();
                int_8 a = stack.popByte();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 not equal with type Byte.
 */
            case bcmpne_b:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popByte();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 not equal with type Byte.
 */
            case bucmpne_b:
            {
                uint_8 b = stack.popUnsignedByte();
                int_8 a = stack.popByte();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_8 to type Short.
 */
            case bcast_s:
                stack.pushShort(static_cast<int_16> (stack.popByte()));
                break;
/**
 * cast unsigned uint_8 to type Short.
 */
            case bucast_s:
                stack.pushShort(static_cast<int_16> (stack.popUnsignedByte()));
                break;
/**
 * add int_8 with type Short.
 */
            case badd_s:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popShort();
                stack.pushShort(a + b);
            }
                break;
/**
 * add unsigned uint_8 with type Short.
 */
            case buadd_s:
            {
                uint_8 b = stack.popUnsignedByte();
                int_16 a = stack.popShort();
                stack.pushShort(a + b);
            }
                break;
/**
 * subtract int_8 with type Short.
 */
            case bsub_s:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popShort();
                stack.pushShort(a - b);
            }
                break;
/**
 * subtract unsigned uint_8 with type Short.
 */
            case busub_s:
            {
                uint_8 b = stack.popUnsignedByte();
                int_16 a = stack.popShort();
                stack.pushShort(a - b);
            }
                break;
/**
 * multiply int_8 with type Short.
 */
            case bmul_s:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popShort();
                stack.pushShort(a * b);
            }
                break;
/**
 * multiply unsigned uint_8 with type Short.
 */
            case bumul_s:
            {
                uint_8 b = stack.popUnsignedByte();
                int_16 a = stack.popShort();
                stack.pushShort(a * b);
            }
                break;
/**
 * divide int_8 with type Short.
 */
            case bdiv_s:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popShort();
                stack.pushShort(a / b);
            }
                break;
/**
 * divide unsigned uint_8 with type Short.
 */
            case budiv_s:
            {
                uint_8 b = stack.popUnsignedByte();
                int_16 a = stack.popShort();
                stack.pushShort(a / b);
            }
                break;
/**
 * compare int_8 less than type Short.
 */
            case bcmpl_s:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popShort();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than type Short.
 */
            case bucmpl_s:
            {
                uint_8 b = stack.popUnsignedByte();
                int_16 a = stack.popShort();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than type Short.
 */
            case bcmpg_s:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popShort();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than type Short.
 */
            case bucmpg_s:
            {
                uint_8 b = stack.popUnsignedByte();
                int_16 a = stack.popShort();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 equal with type Short.
 */
            case bcmpe_s:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popShort();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 equal with type Short.
 */
            case bucmpe_s:
            {
                uint_8 b = stack.popUnsignedByte();
                int_16 a = stack.popShort();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 less than or equal to type Short.
 */
            case bcmple_s:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popShort();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than or equal to type Short.
 */
            case bucmple_s:
            {
                uint_8 b = stack.popUnsignedByte();
                int_16 a = stack.popShort();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than or equal to type Short.
 */
            case bcmpge_s:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popShort();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than or equal to type Short.
 */
            case bucmpge_s:
            {
                uint_8 b = stack.popUnsignedByte();
                int_16 a = stack.popShort();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 not equal with type Short.
 */
            case bcmpne_s:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popShort();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 not equal with type Short.
 */
            case bucmpne_s:
            {
                uint_8 b = stack.popUnsignedByte();
                int_16 a = stack.popShort();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_8 to type Int.
 */
            case bcast_i:
                stack.pushInt(static_cast<int_32> (stack.popByte()));
                break;
/**
 * cast unsigned uint_8 to type Int.
 */
            case bucast_i:
                stack.pushInt(static_cast<int_32> (stack.popUnsignedByte()));
                break;
/**
 * add int_8 with type Int.
 */
            case badd_i:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popInt();
                stack.pushInt(a + b);
            }
                break;
/**
 * add unsigned uint_8 with type Int.
 */
            case buadd_i:
            {
                uint_8 b = stack.popUnsignedByte();
                int_32 a = stack.popInt();
                stack.pushInt(a + b);
            }
                break;
/**
 * subtract int_8 with type Int.
 */
            case bsub_i:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popInt();
                stack.pushInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_8 with type Int.
 */
            case busub_i:
            {
                uint_8 b = stack.popUnsignedByte();
                int_32 a = stack.popInt();
                stack.pushInt(a - b);
            }
                break;
/**
 * multiply int_8 with type Int.
 */
            case bmul_i:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popInt();
                stack.pushInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_8 with type Int.
 */
            case bumul_i:
            {
                uint_8 b = stack.popUnsignedByte();
                int_32 a = stack.popInt();
                stack.pushInt(a * b);
            }
                break;
/**
 * divide int_8 with type Int.
 */
            case bdiv_i:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popInt();
                stack.pushInt(a / b);
            }
                break;
/**
 * divide unsigned uint_8 with type Int.
 */
            case budiv_i:
            {
                uint_8 b = stack.popUnsignedByte();
                int_32 a = stack.popInt();
                stack.pushInt(a / b);
            }
                break;
/**
 * compare int_8 less than type Int.
 */
            case bcmpl_i:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than type Int.
 */
            case bucmpl_i:
            {
                uint_8 b = stack.popUnsignedByte();
                int_32 a = stack.popInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than type Int.
 */
            case bcmpg_i:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than type Int.
 */
            case bucmpg_i:
            {
                uint_8 b = stack.popUnsignedByte();
                int_32 a = stack.popInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 equal with type Int.
 */
            case bcmpe_i:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 equal with type Int.
 */
            case bucmpe_i:
            {
                uint_8 b = stack.popUnsignedByte();
                int_32 a = stack.popInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 less than or equal to type Int.
 */
            case bcmple_i:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than or equal to type Int.
 */
            case bucmple_i:
            {
                uint_8 b = stack.popUnsignedByte();
                int_32 a = stack.popInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than or equal to type Int.
 */
            case bcmpge_i:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than or equal to type Int.
 */
            case bucmpge_i:
            {
                uint_8 b = stack.popUnsignedByte();
                int_32 a = stack.popInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 not equal with type Int.
 */
            case bcmpne_i:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 not equal with type Int.
 */
            case bucmpne_i:
            {
                uint_8 b = stack.popUnsignedByte();
                int_32 a = stack.popInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_8 to type Long.
 */
            case bcast_l:
                stack.pushLong(static_cast<int_64> (stack.popByte()));
                break;
/**
 * cast unsigned uint_8 to type Long.
 */
            case bucast_l:
                stack.pushLong(static_cast<int_64> (stack.popUnsignedByte()));
                break;
/**
 * add int_8 with type Long.
 */
            case badd_l:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popLong();
                stack.pushLong(a + b);
            }
                break;
/**
 * add unsigned uint_8 with type Long.
 */
            case buadd_l:
            {
                uint_8 b = stack.popUnsignedByte();
                int_64 a = stack.popLong();
                stack.pushLong(a + b);
            }
                break;
/**
 * subtract int_8 with type Long.
 */
            case bsub_l:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popLong();
                stack.pushLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_8 with type Long.
 */
            case busub_l:
            {
                uint_8 b = stack.popUnsignedByte();
                int_64 a = stack.popLong();
                stack.pushLong(a - b);
            }
                break;
/**
 * multiply int_8 with type Long.
 */
            case bmul_l:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popLong();
                stack.pushLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_8 with type Long.
 */
            case bumul_l:
            {
                uint_8 b = stack.popUnsignedByte();
                int_64 a = stack.popLong();
                stack.pushLong(a * b);
            }
                break;
/**
 * divide int_8 with type Long.
 */
            case bdiv_l:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popLong();
                stack.pushLong(a / b);
            }
                break;
/**
 * divide unsigned uint_8 with type Long.
 */
            case budiv_l:
            {
                uint_8 b = stack.popUnsignedByte();
                int_64 a = stack.popLong();
                stack.pushLong(a / b);
            }
                break;
/**
 * compare int_8 less than type Long.
 */
            case bcmpl_l:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than type Long.
 */
            case bucmpl_l:
            {
                uint_8 b = stack.popUnsignedByte();
                int_64 a = stack.popLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than type Long.
 */
            case bcmpg_l:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than type Long.
 */
            case bucmpg_l:
            {
                uint_8 b = stack.popUnsignedByte();
                int_64 a = stack.popLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 equal with type Long.
 */
            case bcmpe_l:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 equal with type Long.
 */
            case bucmpe_l:
            {
                uint_8 b = stack.popUnsignedByte();
                int_64 a = stack.popLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 less than or equal to type Long.
 */
            case bcmple_l:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than or equal to type Long.
 */
            case bucmple_l:
            {
                uint_8 b = stack.popUnsignedByte();
                int_64 a = stack.popLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than or equal to type Long.
 */
            case bcmpge_l:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than or equal to type Long.
 */
            case bucmpge_l:
            {
                uint_8 b = stack.popUnsignedByte();
                int_64 a = stack.popLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 not equal with type Long.
 */
            case bcmpne_l:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 not equal with type Long.
 */
            case bucmpne_l:
            {
                uint_8 b = stack.popUnsignedByte();
                int_64 a = stack.popLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_8 to type LongInt.
 */
            case bcast_li:
                stack.pushLongInt(static_cast<int_128> (stack.popByte()));
                break;
/**
 * cast unsigned uint_8 to type LongInt.
 */
            case bucast_li:
                stack.pushLongInt(static_cast<int_128> (stack.popUnsignedByte()));
                break;
/**
 * add int_8 with type LongInt.
 */
            case badd_li:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a + b);
            }
                break;
/**
 * add unsigned uint_8 with type LongInt.
 */
            case buadd_li:
            {
                uint_8 b = stack.popUnsignedByte();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a + b);
            }
                break;
/**
 * subtract int_8 with type LongInt.
 */
            case bsub_li:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_8 with type LongInt.
 */
            case busub_li:
            {
                uint_8 b = stack.popUnsignedByte();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a - b);
            }
                break;
/**
 * multiply int_8 with type LongInt.
 */
            case bmul_li:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_8 with type LongInt.
 */
            case bumul_li:
            {
                uint_8 b = stack.popUnsignedByte();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a * b);
            }
                break;
/**
 * divide int_8 with type LongInt.
 */
            case bdiv_li:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a / b);
            }
                break;
/**
 * divide unsigned uint_8 with type LongInt.
 */
            case budiv_li:
            {
                uint_8 b = stack.popUnsignedByte();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a / b);
            }
                break;
/**
 * compare int_8 less than type LongInt.
 */
            case bcmpl_li:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than type LongInt.
 */
            case bucmpl_li:
            {
                uint_8 b = stack.popUnsignedByte();
                int_128 a = stack.popLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than type LongInt.
 */
            case bcmpg_li:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than type LongInt.
 */
            case bucmpg_li:
            {
                uint_8 b = stack.popUnsignedByte();
                int_128 a = stack.popLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 equal with type LongInt.
 */
            case bcmpe_li:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 equal with type LongInt.
 */
            case bucmpe_li:
            {
                uint_8 b = stack.popUnsignedByte();
                int_128 a = stack.popLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 less than or equal to type LongInt.
 */
            case bcmple_li:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than or equal to type LongInt.
 */
            case bucmple_li:
            {
                uint_8 b = stack.popUnsignedByte();
                int_128 a = stack.popLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than or equal to type LongInt.
 */
            case bcmpge_li:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than or equal to type LongInt.
 */
            case bucmpge_li:
            {
                uint_8 b = stack.popUnsignedByte();
                int_128 a = stack.popLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 not equal with type LongInt.
 */
            case bcmpne_li:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 not equal with type LongInt.
 */
            case bucmpne_li:
            {
                uint_8 b = stack.popUnsignedByte();
                int_128 a = stack.popLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_8 to type LongLong.
 */
            case bcast_ll:
                stack.pushLongLong(static_cast<int_256> (stack.popByte()));
                break;
/**
 * cast unsigned uint_8 to type LongLong.
 */
            case bucast_ll:
                stack.pushLongLong(static_cast<int_256> (stack.popUnsignedByte()));
                break;
/**
 * add int_8 with type LongLong.
 */
            case badd_ll:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_8 with type LongLong.
 */
            case buadd_ll:
            {
                uint_8 b = stack.popUnsignedByte();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * subtract int_8 with type LongLong.
 */
            case bsub_ll:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_8 with type LongLong.
 */
            case busub_ll:
            {
                uint_8 b = stack.popUnsignedByte();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * multiply int_8 with type LongLong.
 */
            case bmul_ll:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_8 with type LongLong.
 */
            case bumul_ll:
            {
                uint_8 b = stack.popUnsignedByte();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * divide int_8 with type LongLong.
 */
            case bdiv_ll:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_8 with type LongLong.
 */
            case budiv_ll:
            {
                uint_8 b = stack.popUnsignedByte();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * compare int_8 less than type LongLong.
 */
            case bcmpl_ll:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than type LongLong.
 */
            case bucmpl_ll:
            {
                uint_8 b = stack.popUnsignedByte();
                int_256 a = stack.popLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than type LongLong.
 */
            case bcmpg_ll:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than type LongLong.
 */
            case bucmpg_ll:
            {
                uint_8 b = stack.popUnsignedByte();
                int_256 a = stack.popLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 equal with type LongLong.
 */
            case bcmpe_ll:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 equal with type LongLong.
 */
            case bucmpe_ll:
            {
                uint_8 b = stack.popUnsignedByte();
                int_256 a = stack.popLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 less than or equal to type LongLong.
 */
            case bcmple_ll:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than or equal to type LongLong.
 */
            case bucmple_ll:
            {
                uint_8 b = stack.popUnsignedByte();
                int_256 a = stack.popLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than or equal to type LongLong.
 */
            case bcmpge_ll:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than or equal to type LongLong.
 */
            case bucmpge_ll:
            {
                uint_8 b = stack.popUnsignedByte();
                int_256 a = stack.popLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 not equal with type LongLong.
 */
            case bcmpne_ll:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 not equal with type LongLong.
 */
            case bucmpne_ll:
            {
                uint_8 b = stack.popUnsignedByte();
                int_256 a = stack.popLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_8 to type Float.
 */
            case bcast_f:
                stack.pushFloat(static_cast<flt_32> (stack.popByte()));
                break;
/**
 * cast unsigned uint_8 to type Float.
 */
            case bucast_f:
                stack.pushFloat(static_cast<flt_32> (stack.popUnsignedByte()));
                break;
/**
 * add int_8 with type Float.
 */
            case badd_f:
            {
                int_8 b = stack.popByte();
                flt_32 a = stack.popFloat();
                stack.pushFloat(a + b);
            }
                break;
/**
 * add unsigned uint_8 with type Float.
 */
            case buadd_f:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_32 a = stack.popFloat();
                stack.pushFloat(a + b);
            }
                break;
/**
 * subtract int_8 with type Float.
 */
            case bsub_f:
            {
                int_8 b = stack.popByte();
                flt_32 a = stack.popFloat();
                stack.pushFloat(a - b);
            }
                break;
/**
 * subtract unsigned uint_8 with type Float.
 */
            case busub_f:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_32 a = stack.popFloat();
                stack.pushFloat(a - b);
            }
                break;
/**
 * multiply int_8 with type Float.
 */
            case bmul_f:
            {
                int_8 b = stack.popByte();
                flt_32 a = stack.popFloat();
                stack.pushFloat(a * b);
            }
                break;
/**
 * multiply unsigned uint_8 with type Float.
 */
            case bumul_f:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_32 a = stack.popFloat();
                stack.pushFloat(a * b);
            }
                break;
/**
 * divide int_8 with type Float.
 */
            case bdiv_f:
            {
                int_8 b = stack.popByte();
                flt_32 a = stack.popFloat();
                stack.pushFloat(a / b);
            }
                break;
/**
 * divide unsigned uint_8 with type Float.
 */
            case budiv_f:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_32 a = stack.popFloat();
                stack.pushFloat(a / b);
            }
                break;
/**
 * compare int_8 less than type Float.
 */
            case bcmpl_f:
            {
                int_8 b = stack.popByte();
                flt_32 a = stack.popFloat();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than type Float.
 */
            case bucmpl_f:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_32 a = stack.popFloat();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than type Float.
 */
            case bcmpg_f:
            {
                int_8 b = stack.popByte();
                flt_32 a = stack.popFloat();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than type Float.
 */
            case bucmpg_f:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_32 a = stack.popFloat();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 equal with type Float.
 */
            case bcmpe_f:
            {
                int_8 b = stack.popByte();
                flt_32 a = stack.popFloat();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 equal with type Float.
 */
            case bucmpe_f:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_32 a = stack.popFloat();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 less than or equal to type Float.
 */
            case bcmple_f:
            {
                int_8 b = stack.popByte();
                flt_32 a = stack.popFloat();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than or equal to type Float.
 */
            case bucmple_f:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_32 a = stack.popFloat();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than or equal to type Float.
 */
            case bcmpge_f:
            {
                int_8 b = stack.popByte();
                flt_32 a = stack.popFloat();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than or equal to type Float.
 */
            case bucmpge_f:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_32 a = stack.popFloat();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 not equal with type Float.
 */
            case bcmpne_f:
            {
                int_8 b = stack.popByte();
                flt_32 a = stack.popFloat();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 not equal with type Float.
 */
            case bucmpne_f:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_32 a = stack.popFloat();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_8 to type Double.
 */
            case bcast_d:
                stack.pushDouble(static_cast<flt_64> (stack.popByte()));
                break;
/**
 * cast unsigned uint_8 to type Double.
 */
            case bucast_d:
                stack.pushDouble(static_cast<flt_64> (stack.popUnsignedByte()));
                break;
/**
 * add int_8 with type Double.
 */
            case badd_d:
            {
                int_8 b = stack.popByte();
                flt_64 a = stack.popDouble();
                stack.pushDouble(a + b);
            }
                break;
/**
 * add unsigned uint_8 with type Double.
 */
            case buadd_d:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_64 a = stack.popDouble();
                stack.pushDouble(a + b);
            }
                break;
/**
 * subtract int_8 with type Double.
 */
            case bsub_d:
            {
                int_8 b = stack.popByte();
                flt_64 a = stack.popDouble();
                stack.pushDouble(a - b);
            }
                break;
/**
 * subtract unsigned uint_8 with type Double.
 */
            case busub_d:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_64 a = stack.popDouble();
                stack.pushDouble(a - b);
            }
                break;
/**
 * multiply int_8 with type Double.
 */
            case bmul_d:
            {
                int_8 b = stack.popByte();
                flt_64 a = stack.popDouble();
                stack.pushDouble(a * b);
            }
                break;
/**
 * multiply unsigned uint_8 with type Double.
 */
            case bumul_d:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_64 a = stack.popDouble();
                stack.pushDouble(a * b);
            }
                break;
/**
 * divide int_8 with type Double.
 */
            case bdiv_d:
            {
                int_8 b = stack.popByte();
                flt_64 a = stack.popDouble();
                stack.pushDouble(a / b);
            }
                break;
/**
 * divide unsigned uint_8 with type Double.
 */
            case budiv_d:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_64 a = stack.popDouble();
                stack.pushDouble(a / b);
            }
                break;
/**
 * compare int_8 less than type Double.
 */
            case bcmpl_d:
            {
                int_8 b = stack.popByte();
                flt_64 a = stack.popDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than type Double.
 */
            case bucmpl_d:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_64 a = stack.popDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than type Double.
 */
            case bcmpg_d:
            {
                int_8 b = stack.popByte();
                flt_64 a = stack.popDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than type Double.
 */
            case bucmpg_d:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_64 a = stack.popDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 equal with type Double.
 */
            case bcmpe_d:
            {
                int_8 b = stack.popByte();
                flt_64 a = stack.popDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 equal with type Double.
 */
            case bucmpe_d:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_64 a = stack.popDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 less than or equal to type Double.
 */
            case bcmple_d:
            {
                int_8 b = stack.popByte();
                flt_64 a = stack.popDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than or equal to type Double.
 */
            case bucmple_d:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_64 a = stack.popDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than or equal to type Double.
 */
            case bcmpge_d:
            {
                int_8 b = stack.popByte();
                flt_64 a = stack.popDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than or equal to type Double.
 */
            case bucmpge_d:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_64 a = stack.popDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 not equal with type Double.
 */
            case bcmpne_d:
            {
                int_8 b = stack.popByte();
                flt_64 a = stack.popDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 not equal with type Double.
 */
            case bucmpne_d:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_64 a = stack.popDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_8 to type DoubleFloat.
 */
            case bcast_df:
                stack.pushDoubleFloat(static_cast<flt_128> (stack.popByte()));
                break;
/**
 * cast unsigned uint_8 to type DoubleFloat.
 */
            case bucast_df:
                stack.pushDoubleFloat(static_cast<flt_128> (stack.popUnsignedByte()));
                break;
/**
 * add int_8 with type DoubleFloat.
 */
            case badd_df:
            {
                int_8 b = stack.popByte();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a + b);
            }
                break;
/**
 * add unsigned uint_8 with type DoubleFloat.
 */
            case buadd_df:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a + b);
            }
                break;
/**
 * subtract int_8 with type DoubleFloat.
 */
            case bsub_df:
            {
                int_8 b = stack.popByte();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a - b);
            }
                break;
/**
 * subtract unsigned uint_8 with type DoubleFloat.
 */
            case busub_df:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a - b);
            }
                break;
/**
 * multiply int_8 with type DoubleFloat.
 */
            case bmul_df:
            {
                int_8 b = stack.popByte();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a * b);
            }
                break;
/**
 * multiply unsigned uint_8 with type DoubleFloat.
 */
            case bumul_df:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a * b);
            }
                break;
/**
 * divide int_8 with type DoubleFloat.
 */
            case bdiv_df:
            {
                int_8 b = stack.popByte();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a / b);
            }
                break;
/**
 * divide unsigned uint_8 with type DoubleFloat.
 */
            case budiv_df:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a / b);
            }
                break;
/**
 * compare int_8 less than type DoubleFloat.
 */
            case bcmpl_df:
            {
                int_8 b = stack.popByte();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than type DoubleFloat.
 */
            case bucmpl_df:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than type DoubleFloat.
 */
            case bcmpg_df:
            {
                int_8 b = stack.popByte();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than type DoubleFloat.
 */
            case bucmpg_df:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 equal with type DoubleFloat.
 */
            case bcmpe_df:
            {
                int_8 b = stack.popByte();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 equal with type DoubleFloat.
 */
            case bucmpe_df:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 less than or equal to type DoubleFloat.
 */
            case bcmple_df:
            {
                int_8 b = stack.popByte();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than or equal to type DoubleFloat.
 */
            case bucmple_df:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than or equal to type DoubleFloat.
 */
            case bcmpge_df:
            {
                int_8 b = stack.popByte();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than or equal to type DoubleFloat.
 */
            case bucmpge_df:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 not equal with type DoubleFloat.
 */
            case bcmpne_df:
            {
                int_8 b = stack.popByte();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 not equal with type DoubleFloat.
 */
            case bucmpne_df:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_8 to type DoubleDouble.
 */
            case bcast_dd:
                stack.pushDoubleDouble(static_cast<flt_256> (stack.popByte()));
                break;
/**
 * cast unsigned uint_8 to type DoubleDouble.
 */
            case bucast_dd:
                stack.pushDoubleDouble(static_cast<flt_256> (stack.popUnsignedByte()));
                break;
/**
 * add int_8 with type DoubleDouble.
 */
            case badd_dd:
            {
                int_8 b = stack.popByte();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a + b);
            }
                break;
/**
 * add unsigned uint_8 with type DoubleDouble.
 */
            case buadd_dd:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a + b);
            }
                break;
/**
 * subtract int_8 with type DoubleDouble.
 */
            case bsub_dd:
            {
                int_8 b = stack.popByte();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a - b);
            }
                break;
/**
 * subtract unsigned uint_8 with type DoubleDouble.
 */
            case busub_dd:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a - b);
            }
                break;
/**
 * multiply int_8 with type DoubleDouble.
 */
            case bmul_dd:
            {
                int_8 b = stack.popByte();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a * b);
            }
                break;
/**
 * multiply unsigned uint_8 with type DoubleDouble.
 */
            case bumul_dd:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a * b);
            }
                break;
/**
 * divide int_8 with type DoubleDouble.
 */
            case bdiv_dd:
            {
                int_8 b = stack.popByte();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a / b);
            }
                break;
/**
 * divide unsigned uint_8 with type DoubleDouble.
 */
            case budiv_dd:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a / b);
            }
                break;
/**
 * compare int_8 less than type DoubleDouble.
 */
            case bcmpl_dd:
            {
                int_8 b = stack.popByte();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than type DoubleDouble.
 */
            case bucmpl_dd:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than type DoubleDouble.
 */
            case bcmpg_dd:
            {
                int_8 b = stack.popByte();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than type DoubleDouble.
 */
            case bucmpg_dd:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 equal with type DoubleDouble.
 */
            case bcmpe_dd:
            {
                int_8 b = stack.popByte();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 equal with type DoubleDouble.
 */
            case bucmpe_dd:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 less than or equal to type DoubleDouble.
 */
            case bcmple_dd:
            {
                int_8 b = stack.popByte();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than or equal to type DoubleDouble.
 */
            case bucmple_dd:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than or equal to type DoubleDouble.
 */
            case bcmpge_dd:
            {
                int_8 b = stack.popByte();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than or equal to type DoubleDouble.
 */
            case bucmpge_dd:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 not equal with type DoubleDouble.
 */
            case bcmpne_dd:
            {
                int_8 b = stack.popByte();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 not equal with type DoubleDouble.
 */
            case bucmpne_dd:
            {
                uint_8 b = stack.popUnsignedByte();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_8 with type Byte.
 */
            case bmod_b:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popUnsignedByte();
                stack.pushUnsignedByte(a % b);
            }
                break;
/**
 * cast int_8 to unsigned type Byte.
 */
            case bcast_ub:
                stack.pushUnsignedByte(static_cast<uint_8> (stack.popByte()));
                break;
/**
 * cast unsigned uint_8 to unsigned type Byte.
 */
            case bucast_ub:
                stack.pushUnsignedByte(static_cast<uint_8> (stack.popUnsignedByte()));
                break;
/**
 * add int_8 with unsigned type Byte.
 */
            case badd_ub:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popUnsignedByte();
                stack.pushUnsignedByte(a + b);
            }
                break;
/**
 * add unsigned uint_8 with unsigned type Byte.
 */
            case buadd_ub:
            {
                uint_8 b = stack.popUnsignedByte();
                int_8 a = stack.popUnsignedByte();
                stack.pushUnsignedByte(a + b);
            }
                break;
/**
 * subtract int_8 with unsigned type Byte.
 */
            case bsub_ub:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popUnsignedByte();
                stack.pushUnsignedByte(a - b);
            }
                break;
/**
 * subtract unsigned uint_8 with unsigned type Byte.
 */
            case busub_ub:
            {
                uint_8 b = stack.popUnsignedByte();
                int_8 a = stack.popUnsignedByte();
                stack.pushUnsignedByte(a - b);
            }
                break;
/**
 * multiply int_8 with unsigned type Byte.
 */
            case bmul_ub:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popUnsignedByte();
                stack.pushUnsignedByte(a * b);
            }
                break;
/**
 * multiply unsigned uint_8 with unsigned type Byte.
 */
            case bumul_ub:
            {
                uint_8 b = stack.popUnsignedByte();
                int_8 a = stack.popUnsignedByte();
                stack.pushUnsignedByte(a * b);
            }
                break;
/**
 * divide int_8 with unsigned type Byte.
 */
            case bdiv_ub:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popUnsignedByte();
                stack.pushUnsignedByte(a / b);
            }
                break;
/**
 * divide unsigned uint_8 with unsigned type Byte.
 */
            case budiv_ub:
            {
                uint_8 b = stack.popUnsignedByte();
                int_8 a = stack.popUnsignedByte();
                stack.pushUnsignedByte(a / b);
            }
                break;
/**
 * compare int_8 less than unsigned type Byte.
 */
            case bcmpl_ub:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popUnsignedByte();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than unsigned type Byte.
 */
            case bucmpl_ub:
            {
                uint_8 b = stack.popUnsignedByte();
                int_8 a = stack.popUnsignedByte();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than unsigned type Byte.
 */
            case bcmpg_ub:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popUnsignedByte();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than unsigned type Byte.
 */
            case bucmpg_ub:
            {
                uint_8 b = stack.popUnsignedByte();
                int_8 a = stack.popUnsignedByte();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 equal with unsigned type Byte.
 */
            case bcmpe_ub:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popUnsignedByte();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 equal with unsigned type Byte.
 */
            case bucmpe_ub:
            {
                uint_8 b = stack.popUnsignedByte();
                int_8 a = stack.popUnsignedByte();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 less than or equal to unsigned type Byte.
 */
            case bcmple_ub:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popUnsignedByte();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than or equal to unsigned type Byte.
 */
            case bucmple_ub:
            {
                uint_8 b = stack.popUnsignedByte();
                int_8 a = stack.popUnsignedByte();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than or equal to unsigned type Byte.
 */
            case bcmpge_ub:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popUnsignedByte();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than or equal to unsigned type Byte.
 */
            case bucmpge_ub:
            {
                uint_8 b = stack.popUnsignedByte();
                int_8 a = stack.popUnsignedByte();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 not equal with unsigned type Byte.
 */
            case bcmpne_ub:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popUnsignedByte();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 not equal with unsigned type Byte.
 */
            case bucmpne_ub:
            {
                uint_8 b = stack.popUnsignedByte();
                int_8 a = stack.popUnsignedByte();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_8 with type Short.
 */
            case bmod_s:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a % b);
            }
                break;
/**
 * cast int_8 to unsigned type Short.
 */
            case bcast_us:
                stack.pushUnsignedShort(static_cast<uint_16> (stack.popByte()));
                break;
/**
 * cast unsigned uint_8 to unsigned type Short.
 */
            case bucast_us:
                stack.pushUnsignedShort(static_cast<uint_16> (stack.popUnsignedByte()));
                break;
/**
 * add int_8 with unsigned type Short.
 */
            case badd_us:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a + b);
            }
                break;
/**
 * add unsigned uint_8 with unsigned type Short.
 */
            case buadd_us:
            {
                uint_8 b = stack.popUnsignedByte();
                int_16 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a + b);
            }
                break;
/**
 * subtract int_8 with unsigned type Short.
 */
            case bsub_us:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a - b);
            }
                break;
/**
 * subtract unsigned uint_8 with unsigned type Short.
 */
            case busub_us:
            {
                uint_8 b = stack.popUnsignedByte();
                int_16 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a - b);
            }
                break;
/**
 * multiply int_8 with unsigned type Short.
 */
            case bmul_us:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a * b);
            }
                break;
/**
 * multiply unsigned uint_8 with unsigned type Short.
 */
            case bumul_us:
            {
                uint_8 b = stack.popUnsignedByte();
                int_16 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a * b);
            }
                break;
/**
 * divide int_8 with unsigned type Short.
 */
            case bdiv_us:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a / b);
            }
                break;
/**
 * divide unsigned uint_8 with unsigned type Short.
 */
            case budiv_us:
            {
                uint_8 b = stack.popUnsignedByte();
                int_16 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a / b);
            }
                break;
/**
 * compare int_8 less than unsigned type Short.
 */
            case bcmpl_us:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popUnsignedShort();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than unsigned type Short.
 */
            case bucmpl_us:
            {
                uint_8 b = stack.popUnsignedByte();
                int_16 a = stack.popUnsignedShort();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than unsigned type Short.
 */
            case bcmpg_us:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popUnsignedShort();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than unsigned type Short.
 */
            case bucmpg_us:
            {
                uint_8 b = stack.popUnsignedByte();
                int_16 a = stack.popUnsignedShort();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 equal with unsigned type Short.
 */
            case bcmpe_us:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popUnsignedShort();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 equal with unsigned type Short.
 */
            case bucmpe_us:
            {
                uint_8 b = stack.popUnsignedByte();
                int_16 a = stack.popUnsignedShort();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 less than or equal to unsigned type Short.
 */
            case bcmple_us:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popUnsignedShort();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than or equal to unsigned type Short.
 */
            case bucmple_us:
            {
                uint_8 b = stack.popUnsignedByte();
                int_16 a = stack.popUnsignedShort();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than or equal to unsigned type Short.
 */
            case bcmpge_us:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popUnsignedShort();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than or equal to unsigned type Short.
 */
            case bucmpge_us:
            {
                uint_8 b = stack.popUnsignedByte();
                int_16 a = stack.popUnsignedShort();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 not equal with unsigned type Short.
 */
            case bcmpne_us:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popUnsignedShort();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 not equal with unsigned type Short.
 */
            case bucmpne_us:
            {
                uint_8 b = stack.popUnsignedByte();
                int_16 a = stack.popUnsignedShort();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_8 with type Int.
 */
            case bmod_i:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a % b);
            }
                break;
/**
 * cast int_8 to unsigned type Int.
 */
            case bcast_ui:
                stack.pushUnsignedInt(static_cast<uint_32> (stack.popByte()));
                break;
/**
 * cast unsigned uint_8 to unsigned type Int.
 */
            case bucast_ui:
                stack.pushUnsignedInt(static_cast<uint_32> (stack.popUnsignedByte()));
                break;
/**
 * add int_8 with unsigned type Int.
 */
            case badd_ui:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a + b);
            }
                break;
/**
 * add unsigned uint_8 with unsigned type Int.
 */
            case buadd_ui:
            {
                uint_8 b = stack.popUnsignedByte();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a + b);
            }
                break;
/**
 * subtract int_8 with unsigned type Int.
 */
            case bsub_ui:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_8 with unsigned type Int.
 */
            case busub_ui:
            {
                uint_8 b = stack.popUnsignedByte();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a - b);
            }
                break;
/**
 * multiply int_8 with unsigned type Int.
 */
            case bmul_ui:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_8 with unsigned type Int.
 */
            case bumul_ui:
            {
                uint_8 b = stack.popUnsignedByte();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a * b);
            }
                break;
/**
 * divide int_8 with unsigned type Int.
 */
            case bdiv_ui:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a / b);
            }
                break;
/**
 * divide unsigned uint_8 with unsigned type Int.
 */
            case budiv_ui:
            {
                uint_8 b = stack.popUnsignedByte();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a / b);
            }
                break;
/**
 * compare int_8 less than unsigned type Int.
 */
            case bcmpl_ui:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than unsigned type Int.
 */
            case bucmpl_ui:
            {
                uint_8 b = stack.popUnsignedByte();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than unsigned type Int.
 */
            case bcmpg_ui:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than unsigned type Int.
 */
            case bucmpg_ui:
            {
                uint_8 b = stack.popUnsignedByte();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 equal with unsigned type Int.
 */
            case bcmpe_ui:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 equal with unsigned type Int.
 */
            case bucmpe_ui:
            {
                uint_8 b = stack.popUnsignedByte();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 less than or equal to unsigned type Int.
 */
            case bcmple_ui:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than or equal to unsigned type Int.
 */
            case bucmple_ui:
            {
                uint_8 b = stack.popUnsignedByte();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than or equal to unsigned type Int.
 */
            case bcmpge_ui:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than or equal to unsigned type Int.
 */
            case bucmpge_ui:
            {
                uint_8 b = stack.popUnsignedByte();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 not equal with unsigned type Int.
 */
            case bcmpne_ui:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 not equal with unsigned type Int.
 */
            case bucmpne_ui:
            {
                uint_8 b = stack.popUnsignedByte();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_8 with type Long.
 */
            case bmod_l:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a % b);
            }
                break;
/**
 * cast int_8 to unsigned type Long.
 */
            case bcast_ul:
                stack.pushUnsignedLong(static_cast<uint_64> (stack.popByte()));
                break;
/**
 * cast unsigned uint_8 to unsigned type Long.
 */
            case bucast_ul:
                stack.pushUnsignedLong(static_cast<uint_64> (stack.popUnsignedByte()));
                break;
/**
 * add int_8 with unsigned type Long.
 */
            case badd_ul:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a + b);
            }
                break;
/**
 * add unsigned uint_8 with unsigned type Long.
 */
            case buadd_ul:
            {
                uint_8 b = stack.popUnsignedByte();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a + b);
            }
                break;
/**
 * subtract int_8 with unsigned type Long.
 */
            case bsub_ul:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_8 with unsigned type Long.
 */
            case busub_ul:
            {
                uint_8 b = stack.popUnsignedByte();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a - b);
            }
                break;
/**
 * multiply int_8 with unsigned type Long.
 */
            case bmul_ul:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_8 with unsigned type Long.
 */
            case bumul_ul:
            {
                uint_8 b = stack.popUnsignedByte();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a * b);
            }
                break;
/**
 * divide int_8 with unsigned type Long.
 */
            case bdiv_ul:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a / b);
            }
                break;
/**
 * divide unsigned uint_8 with unsigned type Long.
 */
            case budiv_ul:
            {
                uint_8 b = stack.popUnsignedByte();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a / b);
            }
                break;
/**
 * compare int_8 less than unsigned type Long.
 */
            case bcmpl_ul:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than unsigned type Long.
 */
            case bucmpl_ul:
            {
                uint_8 b = stack.popUnsignedByte();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than unsigned type Long.
 */
            case bcmpg_ul:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than unsigned type Long.
 */
            case bucmpg_ul:
            {
                uint_8 b = stack.popUnsignedByte();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 equal with unsigned type Long.
 */
            case bcmpe_ul:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 equal with unsigned type Long.
 */
            case bucmpe_ul:
            {
                uint_8 b = stack.popUnsignedByte();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 less than or equal to unsigned type Long.
 */
            case bcmple_ul:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than or equal to unsigned type Long.
 */
            case bucmple_ul:
            {
                uint_8 b = stack.popUnsignedByte();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than or equal to unsigned type Long.
 */
            case bcmpge_ul:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than or equal to unsigned type Long.
 */
            case bucmpge_ul:
            {
                uint_8 b = stack.popUnsignedByte();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 not equal with unsigned type Long.
 */
            case bcmpne_ul:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 not equal with unsigned type Long.
 */
            case bucmpne_ul:
            {
                uint_8 b = stack.popUnsignedByte();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_8 with type LongInt.
 */
            case bmod_li:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a % b);
            }
                break;
/**
 * cast int_8 to unsigned type LongInt.
 */
            case bcast_uli:
                stack.pushUnsignedLongInt(static_cast<uint_128> (stack.popByte()));
                break;
/**
 * cast unsigned uint_8 to unsigned type LongInt.
 */
            case bucast_uli:
                stack.pushUnsignedLongInt(static_cast<uint_128> (stack.popUnsignedByte()));
                break;
/**
 * add int_8 with unsigned type LongInt.
 */
            case badd_uli:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a + b);
            }
                break;
/**
 * add unsigned uint_8 with unsigned type LongInt.
 */
            case buadd_uli:
            {
                uint_8 b = stack.popUnsignedByte();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a + b);
            }
                break;
/**
 * subtract int_8 with unsigned type LongInt.
 */
            case bsub_uli:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_8 with unsigned type LongInt.
 */
            case busub_uli:
            {
                uint_8 b = stack.popUnsignedByte();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a - b);
            }
                break;
/**
 * multiply int_8 with unsigned type LongInt.
 */
            case bmul_uli:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_8 with unsigned type LongInt.
 */
            case bumul_uli:
            {
                uint_8 b = stack.popUnsignedByte();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a * b);
            }
                break;
/**
 * divide int_8 with unsigned type LongInt.
 */
            case bdiv_uli:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a / b);
            }
                break;
/**
 * divide unsigned uint_8 with unsigned type LongInt.
 */
            case budiv_uli:
            {
                uint_8 b = stack.popUnsignedByte();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a / b);
            }
                break;
/**
 * compare int_8 less than unsigned type LongInt.
 */
            case bcmpl_uli:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than unsigned type LongInt.
 */
            case bucmpl_uli:
            {
                uint_8 b = stack.popUnsignedByte();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than unsigned type LongInt.
 */
            case bcmpg_uli:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than unsigned type LongInt.
 */
            case bucmpg_uli:
            {
                uint_8 b = stack.popUnsignedByte();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 equal with unsigned type LongInt.
 */
            case bcmpe_uli:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 equal with unsigned type LongInt.
 */
            case bucmpe_uli:
            {
                uint_8 b = stack.popUnsignedByte();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 less than or equal to unsigned type LongInt.
 */
            case bcmple_uli:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than or equal to unsigned type LongInt.
 */
            case bucmple_uli:
            {
                uint_8 b = stack.popUnsignedByte();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than or equal to unsigned type LongInt.
 */
            case bcmpge_uli:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than or equal to unsigned type LongInt.
 */
            case bucmpge_uli:
            {
                uint_8 b = stack.popUnsignedByte();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 not equal with unsigned type LongInt.
 */
            case bcmpne_uli:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 not equal with unsigned type LongInt.
 */
            case bucmpne_uli:
            {
                uint_8 b = stack.popUnsignedByte();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_8 with type LongLong.
 */
            case bmod_ll:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a % b);
            }
                break;
/**
 * cast int_8 to unsigned type LongLong.
 */
            case bcast_ull:
                stack.pushUnsignedLongLong(static_cast<uint_256> (stack.popByte()));
                break;
/**
 * cast unsigned uint_8 to unsigned type LongLong.
 */
            case bucast_ull:
                stack.pushUnsignedLongLong(static_cast<uint_256> (stack.popUnsignedByte()));
                break;
/**
 * add int_8 with unsigned type LongLong.
 */
            case badd_ull:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_8 with unsigned type LongLong.
 */
            case buadd_ull:
            {
                uint_8 b = stack.popUnsignedByte();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a + b);
            }
                break;
/**
 * subtract int_8 with unsigned type LongLong.
 */
            case bsub_ull:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_8 with unsigned type LongLong.
 */
            case busub_ull:
            {
                uint_8 b = stack.popUnsignedByte();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a - b);
            }
                break;
/**
 * multiply int_8 with unsigned type LongLong.
 */
            case bmul_ull:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_8 with unsigned type LongLong.
 */
            case bumul_ull:
            {
                uint_8 b = stack.popUnsignedByte();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a * b);
            }
                break;
/**
 * divide int_8 with unsigned type LongLong.
 */
            case bdiv_ull:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_8 with unsigned type LongLong.
 */
            case budiv_ull:
            {
                uint_8 b = stack.popUnsignedByte();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a / b);
            }
                break;
/**
 * compare int_8 less than unsigned type LongLong.
 */
            case bcmpl_ull:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than unsigned type LongLong.
 */
            case bucmpl_ull:
            {
                uint_8 b = stack.popUnsignedByte();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than unsigned type LongLong.
 */
            case bcmpg_ull:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than unsigned type LongLong.
 */
            case bucmpg_ull:
            {
                uint_8 b = stack.popUnsignedByte();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 equal with unsigned type LongLong.
 */
            case bcmpe_ull:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 equal with unsigned type LongLong.
 */
            case bucmpe_ull:
            {
                uint_8 b = stack.popUnsignedByte();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 less than or equal to unsigned type LongLong.
 */
            case bcmple_ull:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 less than or equal to unsigned type LongLong.
 */
            case bucmple_ull:
            {
                uint_8 b = stack.popUnsignedByte();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 greater than or equal to unsigned type LongLong.
 */
            case bcmpge_ull:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 greater than or equal to unsigned type LongLong.
 */
            case bucmpge_ull:
            {
                uint_8 b = stack.popUnsignedByte();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_8 not equal with unsigned type LongLong.
 */
            case bcmpne_ull:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_8 not equal with unsigned type LongLong.
 */
            case bucmpne_ull:
            {
                uint_8 b = stack.popUnsignedByte();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * bitwise and int_8 with type Byte.
 */
            case band_b:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popByte();
                stack.pushByte(a & b);
            }
                break;
/**
 * bitwise or int_8 with type Byte.
 */
            case bor_b:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popByte();
                stack.pushByte(a | b);
            }
                break;
/**
 * bitwise xor int_8 with type Byte.
 */
            case bxor_b:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popByte();
                stack.pushByte(a ^ b);
            }
                break;
/**
 * shift right int_8 with type Byte.
 */
            case bshftr_b:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popByte();
                stack.pushByte(a >> b);
            }
                break;
/**
 * shift left xor int_8 with type Byte.
 */
            case bshftl_b:
            {
                int_8 b = stack.popByte();
                int_8 a = stack.popByte();
                stack.pushByte(a << b);
            }
                break;
/**
 * bitwise and int_8 with type Short.
 */
            case band_s:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popShort();
                stack.pushShort(a & b);
            }
                break;
/**
 * bitwise or int_8 with type Short.
 */
            case bor_s:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popShort();
                stack.pushShort(a | b);
            }
                break;
/**
 * bitwise xor int_8 with type Short.
 */
            case bxor_s:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popShort();
                stack.pushShort(a ^ b);
            }
                break;
/**
 * shift right int_8 with type Short.
 */
            case bshftr_s:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popShort();
                stack.pushShort(a >> b);
            }
                break;
/**
 * shift left xor int_8 with type Short.
 */
            case bshftl_s:
            {
                int_8 b = stack.popByte();
                int_16 a = stack.popShort();
                stack.pushShort(a << b);
            }
                break;
/**
 * bitwise and int_8 with type Int.
 */
            case band_i:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popInt();
                stack.pushInt(a & b);
            }
                break;
/**
 * bitwise or int_8 with type Int.
 */
            case bor_i:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popInt();
                stack.pushInt(a | b);
            }
                break;
/**
 * bitwise xor int_8 with type Int.
 */
            case bxor_i:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popInt();
                stack.pushInt(a ^ b);
            }
                break;
/**
 * shift right int_8 with type Int.
 */
            case bshftr_i:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popInt();
                stack.pushInt(a >> b);
            }
                break;
/**
 * shift left xor int_8 with type Int.
 */
            case bshftl_i:
            {
                int_8 b = stack.popByte();
                int_32 a = stack.popInt();
                stack.pushInt(a << b);
            }
                break;
/**
 * bitwise and int_8 with type Long.
 */
            case band_l:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popLong();
                stack.pushLong(a & b);
            }
                break;
/**
 * bitwise or int_8 with type Long.
 */
            case bor_l:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popLong();
                stack.pushLong(a | b);
            }
                break;
/**
 * bitwise xor int_8 with type Long.
 */
            case bxor_l:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popLong();
                stack.pushLong(a ^ b);
            }
                break;
/**
 * shift right int_8 with type Long.
 */
            case bshftr_l:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popLong();
                stack.pushLong(a >> b);
            }
                break;
/**
 * shift left xor int_8 with type Long.
 */
            case bshftl_l:
            {
                int_8 b = stack.popByte();
                int_64 a = stack.popLong();
                stack.pushLong(a << b);
            }
                break;
/**
 * bitwise and int_8 with type LongInt.
 */
            case band_li:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a & b);
            }
                break;
/**
 * bitwise or int_8 with type LongInt.
 */
            case bor_li:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a | b);
            }
                break;
/**
 * bitwise xor int_8 with type LongInt.
 */
            case bxor_li:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a ^ b);
            }
                break;
/**
 * shift right int_8 with type LongInt.
 */
            case bshftr_li:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a >> b);
            }
                break;
/**
 * shift left xor int_8 with type LongInt.
 */
            case bshftl_li:
            {
                int_8 b = stack.popByte();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a << b);
            }
                break;
/**
 * bitwise and int_8 with type LongLong.
 */
            case band_ll:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a & b);
            }
                break;
/**
 * bitwise or int_8 with type LongLong.
 */
            case bor_ll:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a | b);
            }
                break;
/**
 * bitwise xor int_8 with type LongLong.
 */
            case bxor_ll:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a ^ b);
            }
                break;
/**
 * shift right int_8 with type LongLong.
 */
            case bshftr_ll:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a >> b);
            }
                break;
/**
 * shift left xor int_8 with type LongLong.
 */
            case bshftl_ll:
            {
                int_8 b = stack.popByte();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a << b);
            }
                break;
/**
 * duplicate a int_8 on the stack.
 */
            case bdup:
                stack.pushByte(stack.peekByte());
                break;
/**
 * duplicate a int_8 2 times on the stack.
 */
            case bdup2:
                stack.pushByte(stack.peekByte());stack.pushByte(stack.peekByte());
                break;
/**
 * duplicate a int_8 3 times on the stack.
 */
            case bdup3:
                stack.pushByte(stack.peekByte());stack.pushByte(stack.peekByte());stack.pushByte(stack.peekByte());
                break;
/**
 * duplicate a int_8 4 times on the stack.
 */
            case bdup4:
                stack.pushByte(stack.peekByte());stack.pushByte(stack.peekByte());stack.pushByte(stack.peekByte());stack.pushByte(stack.peekByte());
                break;
/**
 * duplicate a int_8 5 times on the stack.
 */
            case bdup5:
                stack.pushByte(stack.peekByte());stack.pushByte(stack.peekByte());stack.pushByte(stack.peekByte());stack.pushByte(stack.peekByte());stack.pushByte(stack.peekByte());
                break;
/**
 * set a int_8 from stack into a field on base pointer.
 */
            case bset:
                accessMemoryAndSetByte(base, ops.getUnsignedInt(), stack.popByte());
                break;
/**
 * get a int_8 from a field on base pointer to stack.
 */
            case bget:
                stack.pushByte(accessMemoryAndGetByte(base, ops.getUnsignedInt()));
                break;
/**
 * set a int_8 from value into a field on base pointer.
 */
            case bvset:
                accessMemoryAndSetByte(base, ops.getUnsignedInt(), ops.getByte());
                break;
/**
 * get a int_8 from a field on base pointer to stack using address from stack.
 */
            case bsget:
                stack.pushByte(accessMemoryAndGetByte(base, stack.popUnsignedInt()));
                break;
/**
 * set a int_8 from stack into a field on base pointer using address from stack.
 */
            case bsset:
                accessMemoryAndSetByte(base, stack.popUnsignedInt(), stack.popByte());
                break;
/**
 * set a int_8 from local variable into a field on base pointer.
 */
            case bsetl:
                accessMemoryAndSetByte(base, ops.getUnsignedInt(), lvt[ops.getUnsignedShort()].Byte);
                break;
/**
 * increment int_8 by 1 on stack.
 */
            case binc_1:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].Byte = lvt[point].Byte + 1; }
                break;
/**
 * increment int_8 by 2 on stack.
 */
            case binc_2:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].Byte = lvt[point].Byte + 2; }
                break;
/**
 * increment int_8 by 1 on stack.
 */
            case bstinc_1:
                stack.pushByte(stack.popByte() + 1);
                break;
/**
 * increment int_8 by 2 on stack.
 */
            case bstinc_2:
                stack.pushByte(stack.popByte() + 2);
                break;
/**
 * return a int_8 into the main stack.
 */
            case breturn:
                stack_main.pushByte(stack.popByte());
                break;
/**
 * store a int_8 from main stack in a local variable..
 */
            case bmainst:
                lvt[ops.getUnsignedShort()].Byte = stack_main.popByte();
                break;
/**
 * store a int_8 from main stack in local variable 0.
 */
            case bmainst_0:
                lvt[0].Byte = stack_main.popByte();;
                break;
/**
 * store a int_8 from main stack in local variable 1.
 */
            case bmainst_1:
                lvt[1].Byte = stack_main.popByte();;
                break;
/**
 * store a int_8 from main stack in local variable 2.
 */
            case bmainst_2:
                lvt[2].Byte = stack_main.popByte();;
                break;
/**
 * store a int_8 from main stack in local variable 3.
 */
            case bmainst_3:
                lvt[3].Byte = stack_main.popByte();;
                break;
/**
 * print a int_8 from stack.
 */
            case bprint:
                log(std::to_string(stack.popByte()));
                break;
/**
 * print a unsigned uint_8 from stack.
 */
            case buprint:
                log(std::to_string(stack.popUnsignedByte()));
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
 * push a const int_16 into the stack (value = 1).
 */
            case sconst_1:
                stack.pushShort(1);
                break;
/**
 * push a const int_16 into the stack (value = 2).
 */
            case sconst_2:
                stack.pushShort(2);
                break;
/**
 * push a const int_16 into the stack (value = 3).
 */
            case sconst_3:
                stack.pushShort(3);
                break;
/**
 * push a const int_16 into the stack (value = 4).
 */
            case sconst_4:
                stack.pushShort(4);
                break;
/**
 * push a const int_16 into the stack (value = 5).
 */
            case sconst_5:
                stack.pushShort(5);
                break;
/**
 * push a const int_16 into the stack (value = 6).
 */
            case sconst_6:
                stack.pushShort(6);
                break;
/**
 * push a const int_16 into the stack (value = 9).
 */
            case sconst_9:
                stack.pushShort(9);
                break;
/**
 * push a const int_16 into the stack (value = 10).
 */
            case sconst_10:
                stack.pushShort(10);
                break;
/**
 * push a const int_16 into the stack (value = 11).
 */
            case sconst_11:
                stack.pushShort(11);
                break;
/**
 * push a const int_16 into the stack (value = 12).
 */
            case sconst_12:
                stack.pushShort(12);
                break;
/**
 * load a int_16 into the stack from local variable.
 */
            case sload:
                stack.pushShort(lvt[ops.getUnsignedShort()].Short);
                break;
/**
 * load a int_16 into the stack from local variable 0.
 */
            case sload_0:
                stack.pushShort(lvt[0].Short);
                break;
/**
 * load a int_16 into the stack from local variable 1.
 */
            case sload_1:
                stack.pushShort(lvt[1].Short);
                break;
/**
 * load a int_16 into the stack from local variable 2.
 */
            case sload_2:
                stack.pushShort(lvt[2].Short);
                break;
/**
 * load a int_16 into the stack from local variable 3.
 */
            case sload_3:
                stack.pushShort(lvt[3].Short);
                break;
/**
 * load a int_16 into the stack from local variable 4.
 */
            case sload_4:
                stack.pushShort(lvt[4].Short);
                break;
/**
 * store a int_16 from stack into local variable.
 */
            case sstore:
                lvt[ops.getUnsignedShort()] = lve_Short(stack.popShort());
                break;
/**
 * store a int_16 from stack into local variable 0.
 */
            case sstore_0:
                lvt[0] = lve_Short(stack.popShort());
                break;
/**
 * store a int_16 from stack into local variable 1.
 */
            case sstore_1:
                lvt[1] = lve_Short(stack.popShort());
                break;
/**
 * store a int_16 from stack into local variable 2.
 */
            case sstore_2:
                lvt[2] = lve_Short(stack.popShort());
                break;
/**
 * store a int_16 from stack into local variable 3.
 */
            case sstore_3:
                lvt[3] = lve_Short(stack.popShort());
                break;
/**
 * store a int_16 from stack into local variable 4.
 */
            case sstore_4:
                lvt[4] = lve_Short(stack.popShort());
                break;
/**
 * cast int_16 to type Byte.
 */
            case scast_b:
                stack.pushByte(static_cast<int_8> (stack.popShort()));
                break;
/**
 * cast unsigned uint_16 to type Byte.
 */
            case sucast_b:
                stack.pushByte(static_cast<int_8> (stack.popUnsignedShort()));
                break;
/**
 * add int_16 with type Byte.
 */
            case sadd_b:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popByte();
                stack.pushShort(a + b);
            }
                break;
/**
 * add unsigned uint_16 with type Byte.
 */
            case suadd_b:
            {
                uint_16 b = stack.popUnsignedShort();
                int_8 a = stack.popByte();
                stack.pushShort(a + b);
            }
                break;
/**
 * subtract int_16 with type Byte.
 */
            case ssub_b:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popByte();
                stack.pushShort(a - b);
            }
                break;
/**
 * subtract unsigned uint_16 with type Byte.
 */
            case susub_b:
            {
                uint_16 b = stack.popUnsignedShort();
                int_8 a = stack.popByte();
                stack.pushShort(a - b);
            }
                break;
/**
 * multiply int_16 with type Byte.
 */
            case smul_b:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popByte();
                stack.pushShort(a * b);
            }
                break;
/**
 * multiply unsigned uint_16 with type Byte.
 */
            case sumul_b:
            {
                uint_16 b = stack.popUnsignedShort();
                int_8 a = stack.popByte();
                stack.pushShort(a * b);
            }
                break;
/**
 * divide int_16 with type Byte.
 */
            case sdiv_b:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popByte();
                stack.pushShort(a / b);
            }
                break;
/**
 * divide unsigned uint_16 with type Byte.
 */
            case sudiv_b:
            {
                uint_16 b = stack.popUnsignedShort();
                int_8 a = stack.popByte();
                stack.pushShort(a / b);
            }
                break;
/**
 * compare int_16 less than type Byte.
 */
            case scmpl_b:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popByte();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than type Byte.
 */
            case sucmpl_b:
            {
                uint_16 b = stack.popUnsignedShort();
                int_8 a = stack.popByte();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than type Byte.
 */
            case scmpg_b:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popByte();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than type Byte.
 */
            case sucmpg_b:
            {
                uint_16 b = stack.popUnsignedShort();
                int_8 a = stack.popByte();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 equal with type Byte.
 */
            case scmpe_b:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popByte();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 equal with type Byte.
 */
            case sucmpe_b:
            {
                uint_16 b = stack.popUnsignedShort();
                int_8 a = stack.popByte();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 less than or equal to type Byte.
 */
            case scmple_b:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popByte();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than or equal to type Byte.
 */
            case sucmple_b:
            {
                uint_16 b = stack.popUnsignedShort();
                int_8 a = stack.popByte();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than or equal to type Byte.
 */
            case scmpge_b:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popByte();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than or equal to type Byte.
 */
            case sucmpge_b:
            {
                uint_16 b = stack.popUnsignedShort();
                int_8 a = stack.popByte();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 not equal with type Byte.
 */
            case scmpne_b:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popByte();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 not equal with type Byte.
 */
            case sucmpne_b:
            {
                uint_16 b = stack.popUnsignedShort();
                int_8 a = stack.popByte();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_16 to type Short.
 */
            case scast_s:
                stack.pushShort(static_cast<int_16> (stack.popShort()));
                break;
/**
 * cast unsigned uint_16 to type Short.
 */
            case sucast_s:
                stack.pushShort(static_cast<int_16> (stack.popUnsignedShort()));
                break;
/**
 * add int_16 with type Short.
 */
            case sadd_s:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popShort();
                stack.pushShort(a + b);
            }
                break;
/**
 * add unsigned uint_16 with type Short.
 */
            case suadd_s:
            {
                uint_16 b = stack.popUnsignedShort();
                int_16 a = stack.popShort();
                stack.pushShort(a + b);
            }
                break;
/**
 * subtract int_16 with type Short.
 */
            case ssub_s:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popShort();
                stack.pushShort(a - b);
            }
                break;
/**
 * subtract unsigned uint_16 with type Short.
 */
            case susub_s:
            {
                uint_16 b = stack.popUnsignedShort();
                int_16 a = stack.popShort();
                stack.pushShort(a - b);
            }
                break;
/**
 * multiply int_16 with type Short.
 */
            case smul_s:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popShort();
                stack.pushShort(a * b);
            }
                break;
/**
 * multiply unsigned uint_16 with type Short.
 */
            case sumul_s:
            {
                uint_16 b = stack.popUnsignedShort();
                int_16 a = stack.popShort();
                stack.pushShort(a * b);
            }
                break;
/**
 * divide int_16 with type Short.
 */
            case sdiv_s:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popShort();
                stack.pushShort(a / b);
            }
                break;
/**
 * divide unsigned uint_16 with type Short.
 */
            case sudiv_s:
            {
                uint_16 b = stack.popUnsignedShort();
                int_16 a = stack.popShort();
                stack.pushShort(a / b);
            }
                break;
/**
 * compare int_16 less than type Short.
 */
            case scmpl_s:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popShort();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than type Short.
 */
            case sucmpl_s:
            {
                uint_16 b = stack.popUnsignedShort();
                int_16 a = stack.popShort();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than type Short.
 */
            case scmpg_s:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popShort();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than type Short.
 */
            case sucmpg_s:
            {
                uint_16 b = stack.popUnsignedShort();
                int_16 a = stack.popShort();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 equal with type Short.
 */
            case scmpe_s:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popShort();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 equal with type Short.
 */
            case sucmpe_s:
            {
                uint_16 b = stack.popUnsignedShort();
                int_16 a = stack.popShort();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 less than or equal to type Short.
 */
            case scmple_s:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popShort();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than or equal to type Short.
 */
            case sucmple_s:
            {
                uint_16 b = stack.popUnsignedShort();
                int_16 a = stack.popShort();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than or equal to type Short.
 */
            case scmpge_s:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popShort();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than or equal to type Short.
 */
            case sucmpge_s:
            {
                uint_16 b = stack.popUnsignedShort();
                int_16 a = stack.popShort();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 not equal with type Short.
 */
            case scmpne_s:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popShort();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 not equal with type Short.
 */
            case sucmpne_s:
            {
                uint_16 b = stack.popUnsignedShort();
                int_16 a = stack.popShort();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_16 to type Int.
 */
            case scast_i:
                stack.pushInt(static_cast<int_32> (stack.popShort()));
                break;
/**
 * cast unsigned uint_16 to type Int.
 */
            case sucast_i:
                stack.pushInt(static_cast<int_32> (stack.popUnsignedShort()));
                break;
/**
 * add int_16 with type Int.
 */
            case sadd_i:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popInt();
                stack.pushInt(a + b);
            }
                break;
/**
 * add unsigned uint_16 with type Int.
 */
            case suadd_i:
            {
                uint_16 b = stack.popUnsignedShort();
                int_32 a = stack.popInt();
                stack.pushInt(a + b);
            }
                break;
/**
 * subtract int_16 with type Int.
 */
            case ssub_i:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popInt();
                stack.pushInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_16 with type Int.
 */
            case susub_i:
            {
                uint_16 b = stack.popUnsignedShort();
                int_32 a = stack.popInt();
                stack.pushInt(a - b);
            }
                break;
/**
 * multiply int_16 with type Int.
 */
            case smul_i:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popInt();
                stack.pushInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_16 with type Int.
 */
            case sumul_i:
            {
                uint_16 b = stack.popUnsignedShort();
                int_32 a = stack.popInt();
                stack.pushInt(a * b);
            }
                break;
/**
 * divide int_16 with type Int.
 */
            case sdiv_i:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popInt();
                stack.pushInt(a / b);
            }
                break;
/**
 * divide unsigned uint_16 with type Int.
 */
            case sudiv_i:
            {
                uint_16 b = stack.popUnsignedShort();
                int_32 a = stack.popInt();
                stack.pushInt(a / b);
            }
                break;
/**
 * compare int_16 less than type Int.
 */
            case scmpl_i:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than type Int.
 */
            case sucmpl_i:
            {
                uint_16 b = stack.popUnsignedShort();
                int_32 a = stack.popInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than type Int.
 */
            case scmpg_i:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than type Int.
 */
            case sucmpg_i:
            {
                uint_16 b = stack.popUnsignedShort();
                int_32 a = stack.popInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 equal with type Int.
 */
            case scmpe_i:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 equal with type Int.
 */
            case sucmpe_i:
            {
                uint_16 b = stack.popUnsignedShort();
                int_32 a = stack.popInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 less than or equal to type Int.
 */
            case scmple_i:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than or equal to type Int.
 */
            case sucmple_i:
            {
                uint_16 b = stack.popUnsignedShort();
                int_32 a = stack.popInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than or equal to type Int.
 */
            case scmpge_i:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than or equal to type Int.
 */
            case sucmpge_i:
            {
                uint_16 b = stack.popUnsignedShort();
                int_32 a = stack.popInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 not equal with type Int.
 */
            case scmpne_i:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 not equal with type Int.
 */
            case sucmpne_i:
            {
                uint_16 b = stack.popUnsignedShort();
                int_32 a = stack.popInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_16 to type Long.
 */
            case scast_l:
                stack.pushLong(static_cast<int_64> (stack.popShort()));
                break;
/**
 * cast unsigned uint_16 to type Long.
 */
            case sucast_l:
                stack.pushLong(static_cast<int_64> (stack.popUnsignedShort()));
                break;
/**
 * add int_16 with type Long.
 */
            case sadd_l:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popLong();
                stack.pushLong(a + b);
            }
                break;
/**
 * add unsigned uint_16 with type Long.
 */
            case suadd_l:
            {
                uint_16 b = stack.popUnsignedShort();
                int_64 a = stack.popLong();
                stack.pushLong(a + b);
            }
                break;
/**
 * subtract int_16 with type Long.
 */
            case ssub_l:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popLong();
                stack.pushLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_16 with type Long.
 */
            case susub_l:
            {
                uint_16 b = stack.popUnsignedShort();
                int_64 a = stack.popLong();
                stack.pushLong(a - b);
            }
                break;
/**
 * multiply int_16 with type Long.
 */
            case smul_l:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popLong();
                stack.pushLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_16 with type Long.
 */
            case sumul_l:
            {
                uint_16 b = stack.popUnsignedShort();
                int_64 a = stack.popLong();
                stack.pushLong(a * b);
            }
                break;
/**
 * divide int_16 with type Long.
 */
            case sdiv_l:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popLong();
                stack.pushLong(a / b);
            }
                break;
/**
 * divide unsigned uint_16 with type Long.
 */
            case sudiv_l:
            {
                uint_16 b = stack.popUnsignedShort();
                int_64 a = stack.popLong();
                stack.pushLong(a / b);
            }
                break;
/**
 * compare int_16 less than type Long.
 */
            case scmpl_l:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than type Long.
 */
            case sucmpl_l:
            {
                uint_16 b = stack.popUnsignedShort();
                int_64 a = stack.popLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than type Long.
 */
            case scmpg_l:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than type Long.
 */
            case sucmpg_l:
            {
                uint_16 b = stack.popUnsignedShort();
                int_64 a = stack.popLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 equal with type Long.
 */
            case scmpe_l:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 equal with type Long.
 */
            case sucmpe_l:
            {
                uint_16 b = stack.popUnsignedShort();
                int_64 a = stack.popLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 less than or equal to type Long.
 */
            case scmple_l:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than or equal to type Long.
 */
            case sucmple_l:
            {
                uint_16 b = stack.popUnsignedShort();
                int_64 a = stack.popLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than or equal to type Long.
 */
            case scmpge_l:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than or equal to type Long.
 */
            case sucmpge_l:
            {
                uint_16 b = stack.popUnsignedShort();
                int_64 a = stack.popLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 not equal with type Long.
 */
            case scmpne_l:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 not equal with type Long.
 */
            case sucmpne_l:
            {
                uint_16 b = stack.popUnsignedShort();
                int_64 a = stack.popLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_16 to type LongInt.
 */
            case scast_li:
                stack.pushLongInt(static_cast<int_128> (stack.popShort()));
                break;
/**
 * cast unsigned uint_16 to type LongInt.
 */
            case sucast_li:
                stack.pushLongInt(static_cast<int_128> (stack.popUnsignedShort()));
                break;
/**
 * add int_16 with type LongInt.
 */
            case sadd_li:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a + b);
            }
                break;
/**
 * add unsigned uint_16 with type LongInt.
 */
            case suadd_li:
            {
                uint_16 b = stack.popUnsignedShort();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a + b);
            }
                break;
/**
 * subtract int_16 with type LongInt.
 */
            case ssub_li:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_16 with type LongInt.
 */
            case susub_li:
            {
                uint_16 b = stack.popUnsignedShort();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a - b);
            }
                break;
/**
 * multiply int_16 with type LongInt.
 */
            case smul_li:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_16 with type LongInt.
 */
            case sumul_li:
            {
                uint_16 b = stack.popUnsignedShort();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a * b);
            }
                break;
/**
 * divide int_16 with type LongInt.
 */
            case sdiv_li:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a / b);
            }
                break;
/**
 * divide unsigned uint_16 with type LongInt.
 */
            case sudiv_li:
            {
                uint_16 b = stack.popUnsignedShort();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a / b);
            }
                break;
/**
 * compare int_16 less than type LongInt.
 */
            case scmpl_li:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than type LongInt.
 */
            case sucmpl_li:
            {
                uint_16 b = stack.popUnsignedShort();
                int_128 a = stack.popLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than type LongInt.
 */
            case scmpg_li:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than type LongInt.
 */
            case sucmpg_li:
            {
                uint_16 b = stack.popUnsignedShort();
                int_128 a = stack.popLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 equal with type LongInt.
 */
            case scmpe_li:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 equal with type LongInt.
 */
            case sucmpe_li:
            {
                uint_16 b = stack.popUnsignedShort();
                int_128 a = stack.popLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 less than or equal to type LongInt.
 */
            case scmple_li:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than or equal to type LongInt.
 */
            case sucmple_li:
            {
                uint_16 b = stack.popUnsignedShort();
                int_128 a = stack.popLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than or equal to type LongInt.
 */
            case scmpge_li:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than or equal to type LongInt.
 */
            case sucmpge_li:
            {
                uint_16 b = stack.popUnsignedShort();
                int_128 a = stack.popLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 not equal with type LongInt.
 */
            case scmpne_li:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 not equal with type LongInt.
 */
            case sucmpne_li:
            {
                uint_16 b = stack.popUnsignedShort();
                int_128 a = stack.popLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_16 to type LongLong.
 */
            case scast_ll:
                stack.pushLongLong(static_cast<int_256> (stack.popShort()));
                break;
/**
 * cast unsigned uint_16 to type LongLong.
 */
            case sucast_ll:
                stack.pushLongLong(static_cast<int_256> (stack.popUnsignedShort()));
                break;
/**
 * add int_16 with type LongLong.
 */
            case sadd_ll:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_16 with type LongLong.
 */
            case suadd_ll:
            {
                uint_16 b = stack.popUnsignedShort();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * subtract int_16 with type LongLong.
 */
            case ssub_ll:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_16 with type LongLong.
 */
            case susub_ll:
            {
                uint_16 b = stack.popUnsignedShort();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * multiply int_16 with type LongLong.
 */
            case smul_ll:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_16 with type LongLong.
 */
            case sumul_ll:
            {
                uint_16 b = stack.popUnsignedShort();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * divide int_16 with type LongLong.
 */
            case sdiv_ll:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_16 with type LongLong.
 */
            case sudiv_ll:
            {
                uint_16 b = stack.popUnsignedShort();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * compare int_16 less than type LongLong.
 */
            case scmpl_ll:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than type LongLong.
 */
            case sucmpl_ll:
            {
                uint_16 b = stack.popUnsignedShort();
                int_256 a = stack.popLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than type LongLong.
 */
            case scmpg_ll:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than type LongLong.
 */
            case sucmpg_ll:
            {
                uint_16 b = stack.popUnsignedShort();
                int_256 a = stack.popLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 equal with type LongLong.
 */
            case scmpe_ll:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 equal with type LongLong.
 */
            case sucmpe_ll:
            {
                uint_16 b = stack.popUnsignedShort();
                int_256 a = stack.popLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 less than or equal to type LongLong.
 */
            case scmple_ll:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than or equal to type LongLong.
 */
            case sucmple_ll:
            {
                uint_16 b = stack.popUnsignedShort();
                int_256 a = stack.popLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than or equal to type LongLong.
 */
            case scmpge_ll:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than or equal to type LongLong.
 */
            case sucmpge_ll:
            {
                uint_16 b = stack.popUnsignedShort();
                int_256 a = stack.popLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 not equal with type LongLong.
 */
            case scmpne_ll:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 not equal with type LongLong.
 */
            case sucmpne_ll:
            {
                uint_16 b = stack.popUnsignedShort();
                int_256 a = stack.popLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_16 to type Float.
 */
            case scast_f:
                stack.pushFloat(static_cast<flt_32> (stack.popShort()));
                break;
/**
 * cast unsigned uint_16 to type Float.
 */
            case sucast_f:
                stack.pushFloat(static_cast<flt_32> (stack.popUnsignedShort()));
                break;
/**
 * add int_16 with type Float.
 */
            case sadd_f:
            {
                int_16 b = stack.popShort();
                flt_32 a = stack.popFloat();
                stack.pushFloat(a + b);
            }
                break;
/**
 * add unsigned uint_16 with type Float.
 */
            case suadd_f:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_32 a = stack.popFloat();
                stack.pushFloat(a + b);
            }
                break;
/**
 * subtract int_16 with type Float.
 */
            case ssub_f:
            {
                int_16 b = stack.popShort();
                flt_32 a = stack.popFloat();
                stack.pushFloat(a - b);
            }
                break;
/**
 * subtract unsigned uint_16 with type Float.
 */
            case susub_f:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_32 a = stack.popFloat();
                stack.pushFloat(a - b);
            }
                break;
/**
 * multiply int_16 with type Float.
 */
            case smul_f:
            {
                int_16 b = stack.popShort();
                flt_32 a = stack.popFloat();
                stack.pushFloat(a * b);
            }
                break;
/**
 * multiply unsigned uint_16 with type Float.
 */
            case sumul_f:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_32 a = stack.popFloat();
                stack.pushFloat(a * b);
            }
                break;
/**
 * divide int_16 with type Float.
 */
            case sdiv_f:
            {
                int_16 b = stack.popShort();
                flt_32 a = stack.popFloat();
                stack.pushFloat(a / b);
            }
                break;
/**
 * divide unsigned uint_16 with type Float.
 */
            case sudiv_f:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_32 a = stack.popFloat();
                stack.pushFloat(a / b);
            }
                break;
/**
 * compare int_16 less than type Float.
 */
            case scmpl_f:
            {
                int_16 b = stack.popShort();
                flt_32 a = stack.popFloat();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than type Float.
 */
            case sucmpl_f:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_32 a = stack.popFloat();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than type Float.
 */
            case scmpg_f:
            {
                int_16 b = stack.popShort();
                flt_32 a = stack.popFloat();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than type Float.
 */
            case sucmpg_f:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_32 a = stack.popFloat();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 equal with type Float.
 */
            case scmpe_f:
            {
                int_16 b = stack.popShort();
                flt_32 a = stack.popFloat();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 equal with type Float.
 */
            case sucmpe_f:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_32 a = stack.popFloat();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 less than or equal to type Float.
 */
            case scmple_f:
            {
                int_16 b = stack.popShort();
                flt_32 a = stack.popFloat();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than or equal to type Float.
 */
            case sucmple_f:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_32 a = stack.popFloat();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than or equal to type Float.
 */
            case scmpge_f:
            {
                int_16 b = stack.popShort();
                flt_32 a = stack.popFloat();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than or equal to type Float.
 */
            case sucmpge_f:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_32 a = stack.popFloat();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 not equal with type Float.
 */
            case scmpne_f:
            {
                int_16 b = stack.popShort();
                flt_32 a = stack.popFloat();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 not equal with type Float.
 */
            case sucmpne_f:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_32 a = stack.popFloat();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_16 to type Double.
 */
            case scast_d:
                stack.pushDouble(static_cast<flt_64> (stack.popShort()));
                break;
/**
 * cast unsigned uint_16 to type Double.
 */
            case sucast_d:
                stack.pushDouble(static_cast<flt_64> (stack.popUnsignedShort()));
                break;
/**
 * add int_16 with type Double.
 */
            case sadd_d:
            {
                int_16 b = stack.popShort();
                flt_64 a = stack.popDouble();
                stack.pushDouble(a + b);
            }
                break;
/**
 * add unsigned uint_16 with type Double.
 */
            case suadd_d:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_64 a = stack.popDouble();
                stack.pushDouble(a + b);
            }
                break;
/**
 * subtract int_16 with type Double.
 */
            case ssub_d:
            {
                int_16 b = stack.popShort();
                flt_64 a = stack.popDouble();
                stack.pushDouble(a - b);
            }
                break;
/**
 * subtract unsigned uint_16 with type Double.
 */
            case susub_d:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_64 a = stack.popDouble();
                stack.pushDouble(a - b);
            }
                break;
/**
 * multiply int_16 with type Double.
 */
            case smul_d:
            {
                int_16 b = stack.popShort();
                flt_64 a = stack.popDouble();
                stack.pushDouble(a * b);
            }
                break;
/**
 * multiply unsigned uint_16 with type Double.
 */
            case sumul_d:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_64 a = stack.popDouble();
                stack.pushDouble(a * b);
            }
                break;
/**
 * divide int_16 with type Double.
 */
            case sdiv_d:
            {
                int_16 b = stack.popShort();
                flt_64 a = stack.popDouble();
                stack.pushDouble(a / b);
            }
                break;
/**
 * divide unsigned uint_16 with type Double.
 */
            case sudiv_d:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_64 a = stack.popDouble();
                stack.pushDouble(a / b);
            }
                break;
/**
 * compare int_16 less than type Double.
 */
            case scmpl_d:
            {
                int_16 b = stack.popShort();
                flt_64 a = stack.popDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than type Double.
 */
            case sucmpl_d:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_64 a = stack.popDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than type Double.
 */
            case scmpg_d:
            {
                int_16 b = stack.popShort();
                flt_64 a = stack.popDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than type Double.
 */
            case sucmpg_d:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_64 a = stack.popDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 equal with type Double.
 */
            case scmpe_d:
            {
                int_16 b = stack.popShort();
                flt_64 a = stack.popDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 equal with type Double.
 */
            case sucmpe_d:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_64 a = stack.popDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 less than or equal to type Double.
 */
            case scmple_d:
            {
                int_16 b = stack.popShort();
                flt_64 a = stack.popDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than or equal to type Double.
 */
            case sucmple_d:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_64 a = stack.popDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than or equal to type Double.
 */
            case scmpge_d:
            {
                int_16 b = stack.popShort();
                flt_64 a = stack.popDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than or equal to type Double.
 */
            case sucmpge_d:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_64 a = stack.popDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 not equal with type Double.
 */
            case scmpne_d:
            {
                int_16 b = stack.popShort();
                flt_64 a = stack.popDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 not equal with type Double.
 */
            case sucmpne_d:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_64 a = stack.popDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_16 to type DoubleFloat.
 */
            case scast_df:
                stack.pushDoubleFloat(static_cast<flt_128> (stack.popShort()));
                break;
/**
 * cast unsigned uint_16 to type DoubleFloat.
 */
            case sucast_df:
                stack.pushDoubleFloat(static_cast<flt_128> (stack.popUnsignedShort()));
                break;
/**
 * add int_16 with type DoubleFloat.
 */
            case sadd_df:
            {
                int_16 b = stack.popShort();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a + b);
            }
                break;
/**
 * add unsigned uint_16 with type DoubleFloat.
 */
            case suadd_df:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a + b);
            }
                break;
/**
 * subtract int_16 with type DoubleFloat.
 */
            case ssub_df:
            {
                int_16 b = stack.popShort();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a - b);
            }
                break;
/**
 * subtract unsigned uint_16 with type DoubleFloat.
 */
            case susub_df:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a - b);
            }
                break;
/**
 * multiply int_16 with type DoubleFloat.
 */
            case smul_df:
            {
                int_16 b = stack.popShort();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a * b);
            }
                break;
/**
 * multiply unsigned uint_16 with type DoubleFloat.
 */
            case sumul_df:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a * b);
            }
                break;
/**
 * divide int_16 with type DoubleFloat.
 */
            case sdiv_df:
            {
                int_16 b = stack.popShort();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a / b);
            }
                break;
/**
 * divide unsigned uint_16 with type DoubleFloat.
 */
            case sudiv_df:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a / b);
            }
                break;
/**
 * compare int_16 less than type DoubleFloat.
 */
            case scmpl_df:
            {
                int_16 b = stack.popShort();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than type DoubleFloat.
 */
            case sucmpl_df:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than type DoubleFloat.
 */
            case scmpg_df:
            {
                int_16 b = stack.popShort();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than type DoubleFloat.
 */
            case sucmpg_df:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 equal with type DoubleFloat.
 */
            case scmpe_df:
            {
                int_16 b = stack.popShort();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 equal with type DoubleFloat.
 */
            case sucmpe_df:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 less than or equal to type DoubleFloat.
 */
            case scmple_df:
            {
                int_16 b = stack.popShort();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than or equal to type DoubleFloat.
 */
            case sucmple_df:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than or equal to type DoubleFloat.
 */
            case scmpge_df:
            {
                int_16 b = stack.popShort();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than or equal to type DoubleFloat.
 */
            case sucmpge_df:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 not equal with type DoubleFloat.
 */
            case scmpne_df:
            {
                int_16 b = stack.popShort();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 not equal with type DoubleFloat.
 */
            case sucmpne_df:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_16 to type DoubleDouble.
 */
            case scast_dd:
                stack.pushDoubleDouble(static_cast<flt_256> (stack.popShort()));
                break;
/**
 * cast unsigned uint_16 to type DoubleDouble.
 */
            case sucast_dd:
                stack.pushDoubleDouble(static_cast<flt_256> (stack.popUnsignedShort()));
                break;
/**
 * add int_16 with type DoubleDouble.
 */
            case sadd_dd:
            {
                int_16 b = stack.popShort();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a + b);
            }
                break;
/**
 * add unsigned uint_16 with type DoubleDouble.
 */
            case suadd_dd:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a + b);
            }
                break;
/**
 * subtract int_16 with type DoubleDouble.
 */
            case ssub_dd:
            {
                int_16 b = stack.popShort();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a - b);
            }
                break;
/**
 * subtract unsigned uint_16 with type DoubleDouble.
 */
            case susub_dd:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a - b);
            }
                break;
/**
 * multiply int_16 with type DoubleDouble.
 */
            case smul_dd:
            {
                int_16 b = stack.popShort();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a * b);
            }
                break;
/**
 * multiply unsigned uint_16 with type DoubleDouble.
 */
            case sumul_dd:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a * b);
            }
                break;
/**
 * divide int_16 with type DoubleDouble.
 */
            case sdiv_dd:
            {
                int_16 b = stack.popShort();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a / b);
            }
                break;
/**
 * divide unsigned uint_16 with type DoubleDouble.
 */
            case sudiv_dd:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a / b);
            }
                break;
/**
 * compare int_16 less than type DoubleDouble.
 */
            case scmpl_dd:
            {
                int_16 b = stack.popShort();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than type DoubleDouble.
 */
            case sucmpl_dd:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than type DoubleDouble.
 */
            case scmpg_dd:
            {
                int_16 b = stack.popShort();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than type DoubleDouble.
 */
            case sucmpg_dd:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 equal with type DoubleDouble.
 */
            case scmpe_dd:
            {
                int_16 b = stack.popShort();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 equal with type DoubleDouble.
 */
            case sucmpe_dd:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 less than or equal to type DoubleDouble.
 */
            case scmple_dd:
            {
                int_16 b = stack.popShort();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than or equal to type DoubleDouble.
 */
            case sucmple_dd:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than or equal to type DoubleDouble.
 */
            case scmpge_dd:
            {
                int_16 b = stack.popShort();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than or equal to type DoubleDouble.
 */
            case sucmpge_dd:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 not equal with type DoubleDouble.
 */
            case scmpne_dd:
            {
                int_16 b = stack.popShort();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 not equal with type DoubleDouble.
 */
            case sucmpne_dd:
            {
                uint_16 b = stack.popUnsignedShort();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_16 with type Byte.
 */
            case smod_b:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a % b);
            }
                break;
/**
 * cast int_16 to unsigned type Byte.
 */
            case scast_ub:
                stack.pushUnsignedByte(static_cast<uint_8> (stack.popShort()));
                break;
/**
 * cast unsigned uint_16 to unsigned type Byte.
 */
            case sucast_ub:
                stack.pushUnsignedByte(static_cast<uint_8> (stack.popUnsignedShort()));
                break;
/**
 * add int_16 with unsigned type Byte.
 */
            case sadd_ub:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a + b);
            }
                break;
/**
 * add unsigned uint_16 with unsigned type Byte.
 */
            case suadd_ub:
            {
                uint_16 b = stack.popUnsignedShort();
                int_8 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a + b);
            }
                break;
/**
 * subtract int_16 with unsigned type Byte.
 */
            case ssub_ub:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a - b);
            }
                break;
/**
 * subtract unsigned uint_16 with unsigned type Byte.
 */
            case susub_ub:
            {
                uint_16 b = stack.popUnsignedShort();
                int_8 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a - b);
            }
                break;
/**
 * multiply int_16 with unsigned type Byte.
 */
            case smul_ub:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a * b);
            }
                break;
/**
 * multiply unsigned uint_16 with unsigned type Byte.
 */
            case sumul_ub:
            {
                uint_16 b = stack.popUnsignedShort();
                int_8 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a * b);
            }
                break;
/**
 * divide int_16 with unsigned type Byte.
 */
            case sdiv_ub:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a / b);
            }
                break;
/**
 * divide unsigned uint_16 with unsigned type Byte.
 */
            case sudiv_ub:
            {
                uint_16 b = stack.popUnsignedShort();
                int_8 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a / b);
            }
                break;
/**
 * compare int_16 less than unsigned type Byte.
 */
            case scmpl_ub:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popUnsignedShort();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than unsigned type Byte.
 */
            case sucmpl_ub:
            {
                uint_16 b = stack.popUnsignedShort();
                int_8 a = stack.popUnsignedShort();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than unsigned type Byte.
 */
            case scmpg_ub:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popUnsignedShort();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than unsigned type Byte.
 */
            case sucmpg_ub:
            {
                uint_16 b = stack.popUnsignedShort();
                int_8 a = stack.popUnsignedShort();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 equal with unsigned type Byte.
 */
            case scmpe_ub:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popUnsignedShort();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 equal with unsigned type Byte.
 */
            case sucmpe_ub:
            {
                uint_16 b = stack.popUnsignedShort();
                int_8 a = stack.popUnsignedShort();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 less than or equal to unsigned type Byte.
 */
            case scmple_ub:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popUnsignedShort();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than or equal to unsigned type Byte.
 */
            case sucmple_ub:
            {
                uint_16 b = stack.popUnsignedShort();
                int_8 a = stack.popUnsignedShort();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than or equal to unsigned type Byte.
 */
            case scmpge_ub:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popUnsignedShort();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than or equal to unsigned type Byte.
 */
            case sucmpge_ub:
            {
                uint_16 b = stack.popUnsignedShort();
                int_8 a = stack.popUnsignedShort();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 not equal with unsigned type Byte.
 */
            case scmpne_ub:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popUnsignedShort();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 not equal with unsigned type Byte.
 */
            case sucmpne_ub:
            {
                uint_16 b = stack.popUnsignedShort();
                int_8 a = stack.popUnsignedShort();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_16 with type Short.
 */
            case smod_s:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a % b);
            }
                break;
/**
 * cast int_16 to unsigned type Short.
 */
            case scast_us:
                stack.pushUnsignedShort(static_cast<uint_16> (stack.popShort()));
                break;
/**
 * cast unsigned uint_16 to unsigned type Short.
 */
            case sucast_us:
                stack.pushUnsignedShort(static_cast<uint_16> (stack.popUnsignedShort()));
                break;
/**
 * add int_16 with unsigned type Short.
 */
            case sadd_us:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a + b);
            }
                break;
/**
 * add unsigned uint_16 with unsigned type Short.
 */
            case suadd_us:
            {
                uint_16 b = stack.popUnsignedShort();
                int_16 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a + b);
            }
                break;
/**
 * subtract int_16 with unsigned type Short.
 */
            case ssub_us:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a - b);
            }
                break;
/**
 * subtract unsigned uint_16 with unsigned type Short.
 */
            case susub_us:
            {
                uint_16 b = stack.popUnsignedShort();
                int_16 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a - b);
            }
                break;
/**
 * multiply int_16 with unsigned type Short.
 */
            case smul_us:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a * b);
            }
                break;
/**
 * multiply unsigned uint_16 with unsigned type Short.
 */
            case sumul_us:
            {
                uint_16 b = stack.popUnsignedShort();
                int_16 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a * b);
            }
                break;
/**
 * divide int_16 with unsigned type Short.
 */
            case sdiv_us:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a / b);
            }
                break;
/**
 * divide unsigned uint_16 with unsigned type Short.
 */
            case sudiv_us:
            {
                uint_16 b = stack.popUnsignedShort();
                int_16 a = stack.popUnsignedShort();
                stack.pushUnsignedShort(a / b);
            }
                break;
/**
 * compare int_16 less than unsigned type Short.
 */
            case scmpl_us:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popUnsignedShort();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than unsigned type Short.
 */
            case sucmpl_us:
            {
                uint_16 b = stack.popUnsignedShort();
                int_16 a = stack.popUnsignedShort();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than unsigned type Short.
 */
            case scmpg_us:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popUnsignedShort();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than unsigned type Short.
 */
            case sucmpg_us:
            {
                uint_16 b = stack.popUnsignedShort();
                int_16 a = stack.popUnsignedShort();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 equal with unsigned type Short.
 */
            case scmpe_us:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popUnsignedShort();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 equal with unsigned type Short.
 */
            case sucmpe_us:
            {
                uint_16 b = stack.popUnsignedShort();
                int_16 a = stack.popUnsignedShort();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 less than or equal to unsigned type Short.
 */
            case scmple_us:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popUnsignedShort();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than or equal to unsigned type Short.
 */
            case sucmple_us:
            {
                uint_16 b = stack.popUnsignedShort();
                int_16 a = stack.popUnsignedShort();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than or equal to unsigned type Short.
 */
            case scmpge_us:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popUnsignedShort();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than or equal to unsigned type Short.
 */
            case sucmpge_us:
            {
                uint_16 b = stack.popUnsignedShort();
                int_16 a = stack.popUnsignedShort();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 not equal with unsigned type Short.
 */
            case scmpne_us:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popUnsignedShort();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 not equal with unsigned type Short.
 */
            case sucmpne_us:
            {
                uint_16 b = stack.popUnsignedShort();
                int_16 a = stack.popUnsignedShort();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_16 with type Int.
 */
            case smod_i:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a % b);
            }
                break;
/**
 * cast int_16 to unsigned type Int.
 */
            case scast_ui:
                stack.pushUnsignedInt(static_cast<uint_32> (stack.popShort()));
                break;
/**
 * cast unsigned uint_16 to unsigned type Int.
 */
            case sucast_ui:
                stack.pushUnsignedInt(static_cast<uint_32> (stack.popUnsignedShort()));
                break;
/**
 * add int_16 with unsigned type Int.
 */
            case sadd_ui:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a + b);
            }
                break;
/**
 * add unsigned uint_16 with unsigned type Int.
 */
            case suadd_ui:
            {
                uint_16 b = stack.popUnsignedShort();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a + b);
            }
                break;
/**
 * subtract int_16 with unsigned type Int.
 */
            case ssub_ui:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_16 with unsigned type Int.
 */
            case susub_ui:
            {
                uint_16 b = stack.popUnsignedShort();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a - b);
            }
                break;
/**
 * multiply int_16 with unsigned type Int.
 */
            case smul_ui:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_16 with unsigned type Int.
 */
            case sumul_ui:
            {
                uint_16 b = stack.popUnsignedShort();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a * b);
            }
                break;
/**
 * divide int_16 with unsigned type Int.
 */
            case sdiv_ui:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a / b);
            }
                break;
/**
 * divide unsigned uint_16 with unsigned type Int.
 */
            case sudiv_ui:
            {
                uint_16 b = stack.popUnsignedShort();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a / b);
            }
                break;
/**
 * compare int_16 less than unsigned type Int.
 */
            case scmpl_ui:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than unsigned type Int.
 */
            case sucmpl_ui:
            {
                uint_16 b = stack.popUnsignedShort();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than unsigned type Int.
 */
            case scmpg_ui:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than unsigned type Int.
 */
            case sucmpg_ui:
            {
                uint_16 b = stack.popUnsignedShort();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 equal with unsigned type Int.
 */
            case scmpe_ui:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 equal with unsigned type Int.
 */
            case sucmpe_ui:
            {
                uint_16 b = stack.popUnsignedShort();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 less than or equal to unsigned type Int.
 */
            case scmple_ui:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than or equal to unsigned type Int.
 */
            case sucmple_ui:
            {
                uint_16 b = stack.popUnsignedShort();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than or equal to unsigned type Int.
 */
            case scmpge_ui:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than or equal to unsigned type Int.
 */
            case sucmpge_ui:
            {
                uint_16 b = stack.popUnsignedShort();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 not equal with unsigned type Int.
 */
            case scmpne_ui:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 not equal with unsigned type Int.
 */
            case sucmpne_ui:
            {
                uint_16 b = stack.popUnsignedShort();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_16 with type Long.
 */
            case smod_l:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a % b);
            }
                break;
/**
 * cast int_16 to unsigned type Long.
 */
            case scast_ul:
                stack.pushUnsignedLong(static_cast<uint_64> (stack.popShort()));
                break;
/**
 * cast unsigned uint_16 to unsigned type Long.
 */
            case sucast_ul:
                stack.pushUnsignedLong(static_cast<uint_64> (stack.popUnsignedShort()));
                break;
/**
 * add int_16 with unsigned type Long.
 */
            case sadd_ul:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a + b);
            }
                break;
/**
 * add unsigned uint_16 with unsigned type Long.
 */
            case suadd_ul:
            {
                uint_16 b = stack.popUnsignedShort();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a + b);
            }
                break;
/**
 * subtract int_16 with unsigned type Long.
 */
            case ssub_ul:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_16 with unsigned type Long.
 */
            case susub_ul:
            {
                uint_16 b = stack.popUnsignedShort();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a - b);
            }
                break;
/**
 * multiply int_16 with unsigned type Long.
 */
            case smul_ul:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_16 with unsigned type Long.
 */
            case sumul_ul:
            {
                uint_16 b = stack.popUnsignedShort();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a * b);
            }
                break;
/**
 * divide int_16 with unsigned type Long.
 */
            case sdiv_ul:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a / b);
            }
                break;
/**
 * divide unsigned uint_16 with unsigned type Long.
 */
            case sudiv_ul:
            {
                uint_16 b = stack.popUnsignedShort();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a / b);
            }
                break;
/**
 * compare int_16 less than unsigned type Long.
 */
            case scmpl_ul:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than unsigned type Long.
 */
            case sucmpl_ul:
            {
                uint_16 b = stack.popUnsignedShort();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than unsigned type Long.
 */
            case scmpg_ul:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than unsigned type Long.
 */
            case sucmpg_ul:
            {
                uint_16 b = stack.popUnsignedShort();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 equal with unsigned type Long.
 */
            case scmpe_ul:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 equal with unsigned type Long.
 */
            case sucmpe_ul:
            {
                uint_16 b = stack.popUnsignedShort();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 less than or equal to unsigned type Long.
 */
            case scmple_ul:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than or equal to unsigned type Long.
 */
            case sucmple_ul:
            {
                uint_16 b = stack.popUnsignedShort();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than or equal to unsigned type Long.
 */
            case scmpge_ul:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than or equal to unsigned type Long.
 */
            case sucmpge_ul:
            {
                uint_16 b = stack.popUnsignedShort();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 not equal with unsigned type Long.
 */
            case scmpne_ul:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 not equal with unsigned type Long.
 */
            case sucmpne_ul:
            {
                uint_16 b = stack.popUnsignedShort();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_16 with type LongInt.
 */
            case smod_li:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a % b);
            }
                break;
/**
 * cast int_16 to unsigned type LongInt.
 */
            case scast_uli:
                stack.pushUnsignedLongInt(static_cast<uint_128> (stack.popShort()));
                break;
/**
 * cast unsigned uint_16 to unsigned type LongInt.
 */
            case sucast_uli:
                stack.pushUnsignedLongInt(static_cast<uint_128> (stack.popUnsignedShort()));
                break;
/**
 * add int_16 with unsigned type LongInt.
 */
            case sadd_uli:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a + b);
            }
                break;
/**
 * add unsigned uint_16 with unsigned type LongInt.
 */
            case suadd_uli:
            {
                uint_16 b = stack.popUnsignedShort();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a + b);
            }
                break;
/**
 * subtract int_16 with unsigned type LongInt.
 */
            case ssub_uli:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_16 with unsigned type LongInt.
 */
            case susub_uli:
            {
                uint_16 b = stack.popUnsignedShort();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a - b);
            }
                break;
/**
 * multiply int_16 with unsigned type LongInt.
 */
            case smul_uli:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_16 with unsigned type LongInt.
 */
            case sumul_uli:
            {
                uint_16 b = stack.popUnsignedShort();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a * b);
            }
                break;
/**
 * divide int_16 with unsigned type LongInt.
 */
            case sdiv_uli:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a / b);
            }
                break;
/**
 * divide unsigned uint_16 with unsigned type LongInt.
 */
            case sudiv_uli:
            {
                uint_16 b = stack.popUnsignedShort();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a / b);
            }
                break;
/**
 * compare int_16 less than unsigned type LongInt.
 */
            case scmpl_uli:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than unsigned type LongInt.
 */
            case sucmpl_uli:
            {
                uint_16 b = stack.popUnsignedShort();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than unsigned type LongInt.
 */
            case scmpg_uli:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than unsigned type LongInt.
 */
            case sucmpg_uli:
            {
                uint_16 b = stack.popUnsignedShort();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 equal with unsigned type LongInt.
 */
            case scmpe_uli:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 equal with unsigned type LongInt.
 */
            case sucmpe_uli:
            {
                uint_16 b = stack.popUnsignedShort();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 less than or equal to unsigned type LongInt.
 */
            case scmple_uli:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than or equal to unsigned type LongInt.
 */
            case sucmple_uli:
            {
                uint_16 b = stack.popUnsignedShort();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than or equal to unsigned type LongInt.
 */
            case scmpge_uli:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than or equal to unsigned type LongInt.
 */
            case sucmpge_uli:
            {
                uint_16 b = stack.popUnsignedShort();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 not equal with unsigned type LongInt.
 */
            case scmpne_uli:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 not equal with unsigned type LongInt.
 */
            case sucmpne_uli:
            {
                uint_16 b = stack.popUnsignedShort();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_16 with type LongLong.
 */
            case smod_ll:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a % b);
            }
                break;
/**
 * cast int_16 to unsigned type LongLong.
 */
            case scast_ull:
                stack.pushUnsignedLongLong(static_cast<uint_256> (stack.popShort()));
                break;
/**
 * cast unsigned uint_16 to unsigned type LongLong.
 */
            case sucast_ull:
                stack.pushUnsignedLongLong(static_cast<uint_256> (stack.popUnsignedShort()));
                break;
/**
 * add int_16 with unsigned type LongLong.
 */
            case sadd_ull:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_16 with unsigned type LongLong.
 */
            case suadd_ull:
            {
                uint_16 b = stack.popUnsignedShort();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a + b);
            }
                break;
/**
 * subtract int_16 with unsigned type LongLong.
 */
            case ssub_ull:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_16 with unsigned type LongLong.
 */
            case susub_ull:
            {
                uint_16 b = stack.popUnsignedShort();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a - b);
            }
                break;
/**
 * multiply int_16 with unsigned type LongLong.
 */
            case smul_ull:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_16 with unsigned type LongLong.
 */
            case sumul_ull:
            {
                uint_16 b = stack.popUnsignedShort();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a * b);
            }
                break;
/**
 * divide int_16 with unsigned type LongLong.
 */
            case sdiv_ull:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_16 with unsigned type LongLong.
 */
            case sudiv_ull:
            {
                uint_16 b = stack.popUnsignedShort();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a / b);
            }
                break;
/**
 * compare int_16 less than unsigned type LongLong.
 */
            case scmpl_ull:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than unsigned type LongLong.
 */
            case sucmpl_ull:
            {
                uint_16 b = stack.popUnsignedShort();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than unsigned type LongLong.
 */
            case scmpg_ull:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than unsigned type LongLong.
 */
            case sucmpg_ull:
            {
                uint_16 b = stack.popUnsignedShort();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 equal with unsigned type LongLong.
 */
            case scmpe_ull:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 equal with unsigned type LongLong.
 */
            case sucmpe_ull:
            {
                uint_16 b = stack.popUnsignedShort();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 less than or equal to unsigned type LongLong.
 */
            case scmple_ull:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 less than or equal to unsigned type LongLong.
 */
            case sucmple_ull:
            {
                uint_16 b = stack.popUnsignedShort();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 greater than or equal to unsigned type LongLong.
 */
            case scmpge_ull:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 greater than or equal to unsigned type LongLong.
 */
            case sucmpge_ull:
            {
                uint_16 b = stack.popUnsignedShort();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_16 not equal with unsigned type LongLong.
 */
            case scmpne_ull:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_16 not equal with unsigned type LongLong.
 */
            case sucmpne_ull:
            {
                uint_16 b = stack.popUnsignedShort();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * bitwise and int_16 with type Byte.
 */
            case sand_b:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popByte();
                stack.pushShort(a & b);
            }
                break;
/**
 * bitwise or int_16 with type Byte.
 */
            case sor_b:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popByte();
                stack.pushShort(a | b);
            }
                break;
/**
 * bitwise xor int_16 with type Byte.
 */
            case sxor_b:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popByte();
                stack.pushShort(a ^ b);
            }
                break;
/**
 * shift right int_16 with type Byte.
 */
            case sshftr_b:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popByte();
                stack.pushShort(a >> b);
            }
                break;
/**
 * shift left xor int_16 with type Byte.
 */
            case sshftl_b:
            {
                int_16 b = stack.popShort();
                int_8 a = stack.popByte();
                stack.pushShort(a << b);
            }
                break;
/**
 * bitwise and int_16 with type Short.
 */
            case sand_s:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popShort();
                stack.pushShort(a & b);
            }
                break;
/**
 * bitwise or int_16 with type Short.
 */
            case sor_s:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popShort();
                stack.pushShort(a | b);
            }
                break;
/**
 * bitwise xor int_16 with type Short.
 */
            case sxor_s:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popShort();
                stack.pushShort(a ^ b);
            }
                break;
/**
 * shift right int_16 with type Short.
 */
            case sshftr_s:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popShort();
                stack.pushShort(a >> b);
            }
                break;
/**
 * shift left xor int_16 with type Short.
 */
            case sshftl_s:
            {
                int_16 b = stack.popShort();
                int_16 a = stack.popShort();
                stack.pushShort(a << b);
            }
                break;
/**
 * bitwise and int_16 with type Int.
 */
            case sand_i:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popInt();
                stack.pushInt(a & b);
            }
                break;
/**
 * bitwise or int_16 with type Int.
 */
            case sor_i:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popInt();
                stack.pushInt(a | b);
            }
                break;
/**
 * bitwise xor int_16 with type Int.
 */
            case sxor_i:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popInt();
                stack.pushInt(a ^ b);
            }
                break;
/**
 * shift right int_16 with type Int.
 */
            case sshftr_i:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popInt();
                stack.pushInt(a >> b);
            }
                break;
/**
 * shift left xor int_16 with type Int.
 */
            case sshftl_i:
            {
                int_16 b = stack.popShort();
                int_32 a = stack.popInt();
                stack.pushInt(a << b);
            }
                break;
/**
 * bitwise and int_16 with type Long.
 */
            case sand_l:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popLong();
                stack.pushLong(a & b);
            }
                break;
/**
 * bitwise or int_16 with type Long.
 */
            case sor_l:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popLong();
                stack.pushLong(a | b);
            }
                break;
/**
 * bitwise xor int_16 with type Long.
 */
            case sxor_l:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popLong();
                stack.pushLong(a ^ b);
            }
                break;
/**
 * shift right int_16 with type Long.
 */
            case sshftr_l:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popLong();
                stack.pushLong(a >> b);
            }
                break;
/**
 * shift left xor int_16 with type Long.
 */
            case sshftl_l:
            {
                int_16 b = stack.popShort();
                int_64 a = stack.popLong();
                stack.pushLong(a << b);
            }
                break;
/**
 * bitwise and int_16 with type LongInt.
 */
            case sand_li:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a & b);
            }
                break;
/**
 * bitwise or int_16 with type LongInt.
 */
            case sor_li:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a | b);
            }
                break;
/**
 * bitwise xor int_16 with type LongInt.
 */
            case sxor_li:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a ^ b);
            }
                break;
/**
 * shift right int_16 with type LongInt.
 */
            case sshftr_li:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a >> b);
            }
                break;
/**
 * shift left xor int_16 with type LongInt.
 */
            case sshftl_li:
            {
                int_16 b = stack.popShort();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a << b);
            }
                break;
/**
 * bitwise and int_16 with type LongLong.
 */
            case sand_ll:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a & b);
            }
                break;
/**
 * bitwise or int_16 with type LongLong.
 */
            case sor_ll:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a | b);
            }
                break;
/**
 * bitwise xor int_16 with type LongLong.
 */
            case sxor_ll:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a ^ b);
            }
                break;
/**
 * shift right int_16 with type LongLong.
 */
            case sshftr_ll:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a >> b);
            }
                break;
/**
 * shift left xor int_16 with type LongLong.
 */
            case sshftl_ll:
            {
                int_16 b = stack.popShort();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a << b);
            }
                break;
/**
 * duplicate a int_16 on the stack.
 */
            case sdup:
                stack.pushShort(stack.peekShort());
                break;
/**
 * duplicate a int_16 2 times on the stack.
 */
            case sdup2:
                stack.pushShort(stack.peekShort());stack.pushShort(stack.peekShort());
                break;
/**
 * duplicate a int_16 3 times on the stack.
 */
            case sdup3:
                stack.pushShort(stack.peekShort());stack.pushShort(stack.peekShort());stack.pushShort(stack.peekShort());
                break;
/**
 * duplicate a int_16 4 times on the stack.
 */
            case sdup4:
                stack.pushShort(stack.peekShort());stack.pushShort(stack.peekShort());stack.pushShort(stack.peekShort());stack.pushShort(stack.peekShort());
                break;
/**
 * duplicate a int_16 5 times on the stack.
 */
            case sdup5:
                stack.pushShort(stack.peekShort());stack.pushShort(stack.peekShort());stack.pushShort(stack.peekShort());stack.pushShort(stack.peekShort());stack.pushShort(stack.peekShort());
                break;
/**
 * set a int_16 from stack into a field on base pointer.
 */
            case sset:
                accessMemoryAndSetShort(base, ops.getUnsignedInt(), stack.popShort());
                break;
/**
 * get a int_16 from a field on base pointer to stack.
 */
            case sget:
                stack.pushShort(accessMemoryAndGetShort(base, ops.getUnsignedInt()));
                break;
/**
 * set a int_16 from value into a field on base pointer.
 */
            case svset:
                accessMemoryAndSetShort(base, ops.getUnsignedInt(), ops.getShort());
                break;
/**
 * get a int_16 from a field on base pointer to stack using address from stack.
 */
            case ssget:
                stack.pushShort(accessMemoryAndGetShort(base, stack.popUnsignedInt()));
                break;
/**
 * set a int_16 from stack into a field on base pointer using address from stack.
 */
            case ssset:
                accessMemoryAndSetShort(base, stack.popUnsignedInt(), stack.popShort());
                break;
/**
 * set a int_16 from local variable into a field on base pointer.
 */
            case ssetl:
                accessMemoryAndSetShort(base, ops.getUnsignedInt(), lvt[ops.getUnsignedShort()].Short);
                break;
/**
 * increment int_16 by 1 on stack.
 */
            case sinc_1:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].Short = lvt[point].Short + 1; }
                break;
/**
 * increment int_16 by 2 on stack.
 */
            case sinc_2:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].Short = lvt[point].Short + 2; }
                break;
/**
 * increment int_16 by 1 on stack.
 */
            case sstinc_1:
                stack.pushShort(stack.popShort() + 1);
                break;
/**
 * increment int_16 by 2 on stack.
 */
            case sstinc_2:
                stack.pushShort(stack.popShort() + 2);
                break;
/**
 * return a int_16 into the main stack.
 */
            case sreturn:
                stack_main.pushShort(stack.popShort());
                break;
/**
 * store a int_16 from main stack in a local variable..
 */
            case smainst:
                lvt[ops.getUnsignedShort()].Short = stack_main.popShort();
                break;
/**
 * store a int_16 from main stack in local variable 0.
 */
            case smainst_0:
                lvt[0].Short = stack_main.popShort();;
                break;
/**
 * store a int_16 from main stack in local variable 1.
 */
            case smainst_1:
                lvt[1].Short = stack_main.popShort();;
                break;
/**
 * store a int_16 from main stack in local variable 2.
 */
            case smainst_2:
                lvt[2].Short = stack_main.popShort();;
                break;
/**
 * store a int_16 from main stack in local variable 3.
 */
            case smainst_3:
                lvt[3].Short = stack_main.popShort();;
                break;
/**
 * print a int_16 from stack.
 */
            case sprint:
                log(std::to_string(stack.popShort()));
                break;
/**
 * print a unsigned uint_16 from stack.
 */
            case suprint:
                log(std::to_string(stack.popUnsignedShort()));
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
                lvt[ops.getUnsignedShort()] = lve_Int(stack.popInt());
                break;
/**
 * store a int_32 from stack into local variable 0.
 */
            case istore_0:
                lvt[0] = lve_Int(stack.popInt());
                break;
/**
 * store a int_32 from stack into local variable 1.
 */
            case istore_1:
                lvt[1] = lve_Int(stack.popInt());
                break;
/**
 * store a int_32 from stack into local variable 2.
 */
            case istore_2:
                lvt[2] = lve_Int(stack.popInt());
                break;
/**
 * store a int_32 from stack into local variable 3.
 */
            case istore_3:
                lvt[3] = lve_Int(stack.popInt());
                break;
/**
 * store a int_32 from stack into local variable 4.
 */
            case istore_4:
                lvt[4] = lve_Int(stack.popInt());
                break;
/**
 * cast int_32 to type Byte.
 */
            case icast_b:
                stack.pushByte(static_cast<int_8> (stack.popInt()));
                break;
/**
 * cast unsigned uint_32 to type Byte.
 */
            case iucast_b:
                stack.pushByte(static_cast<int_8> (stack.popUnsignedInt()));
                break;
/**
 * add int_32 with type Byte.
 */
            case iadd_b:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popByte();
                stack.pushInt(a + b);
            }
                break;
/**
 * add unsigned uint_32 with type Byte.
 */
            case iuadd_b:
            {
                uint_32 b = stack.popUnsignedInt();
                int_8 a = stack.popByte();
                stack.pushInt(a + b);
            }
                break;
/**
 * subtract int_32 with type Byte.
 */
            case isub_b:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popByte();
                stack.pushInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_32 with type Byte.
 */
            case iusub_b:
            {
                uint_32 b = stack.popUnsignedInt();
                int_8 a = stack.popByte();
                stack.pushInt(a - b);
            }
                break;
/**
 * multiply int_32 with type Byte.
 */
            case imul_b:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popByte();
                stack.pushInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_32 with type Byte.
 */
            case iumul_b:
            {
                uint_32 b = stack.popUnsignedInt();
                int_8 a = stack.popByte();
                stack.pushInt(a * b);
            }
                break;
/**
 * divide int_32 with type Byte.
 */
            case idiv_b:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popByte();
                stack.pushInt(a / b);
            }
                break;
/**
 * divide unsigned uint_32 with type Byte.
 */
            case iudiv_b:
            {
                uint_32 b = stack.popUnsignedInt();
                int_8 a = stack.popByte();
                stack.pushInt(a / b);
            }
                break;
/**
 * compare int_32 less than type Byte.
 */
            case icmpl_b:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popByte();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than type Byte.
 */
            case iucmpl_b:
            {
                uint_32 b = stack.popUnsignedInt();
                int_8 a = stack.popByte();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than type Byte.
 */
            case icmpg_b:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popByte();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than type Byte.
 */
            case iucmpg_b:
            {
                uint_32 b = stack.popUnsignedInt();
                int_8 a = stack.popByte();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 equal with type Byte.
 */
            case icmpe_b:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popByte();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 equal with type Byte.
 */
            case iucmpe_b:
            {
                uint_32 b = stack.popUnsignedInt();
                int_8 a = stack.popByte();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 less than or equal to type Byte.
 */
            case icmple_b:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popByte();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than or equal to type Byte.
 */
            case iucmple_b:
            {
                uint_32 b = stack.popUnsignedInt();
                int_8 a = stack.popByte();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than or equal to type Byte.
 */
            case icmpge_b:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popByte();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than or equal to type Byte.
 */
            case iucmpge_b:
            {
                uint_32 b = stack.popUnsignedInt();
                int_8 a = stack.popByte();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 not equal with type Byte.
 */
            case icmpne_b:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popByte();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 not equal with type Byte.
 */
            case iucmpne_b:
            {
                uint_32 b = stack.popUnsignedInt();
                int_8 a = stack.popByte();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_32 to type Short.
 */
            case icast_s:
                stack.pushShort(static_cast<int_16> (stack.popInt()));
                break;
/**
 * cast unsigned uint_32 to type Short.
 */
            case iucast_s:
                stack.pushShort(static_cast<int_16> (stack.popUnsignedInt()));
                break;
/**
 * add int_32 with type Short.
 */
            case iadd_s:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popShort();
                stack.pushInt(a + b);
            }
                break;
/**
 * add unsigned uint_32 with type Short.
 */
            case iuadd_s:
            {
                uint_32 b = stack.popUnsignedInt();
                int_16 a = stack.popShort();
                stack.pushInt(a + b);
            }
                break;
/**
 * subtract int_32 with type Short.
 */
            case isub_s:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popShort();
                stack.pushInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_32 with type Short.
 */
            case iusub_s:
            {
                uint_32 b = stack.popUnsignedInt();
                int_16 a = stack.popShort();
                stack.pushInt(a - b);
            }
                break;
/**
 * multiply int_32 with type Short.
 */
            case imul_s:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popShort();
                stack.pushInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_32 with type Short.
 */
            case iumul_s:
            {
                uint_32 b = stack.popUnsignedInt();
                int_16 a = stack.popShort();
                stack.pushInt(a * b);
            }
                break;
/**
 * divide int_32 with type Short.
 */
            case idiv_s:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popShort();
                stack.pushInt(a / b);
            }
                break;
/**
 * divide unsigned uint_32 with type Short.
 */
            case iudiv_s:
            {
                uint_32 b = stack.popUnsignedInt();
                int_16 a = stack.popShort();
                stack.pushInt(a / b);
            }
                break;
/**
 * compare int_32 less than type Short.
 */
            case icmpl_s:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popShort();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than type Short.
 */
            case iucmpl_s:
            {
                uint_32 b = stack.popUnsignedInt();
                int_16 a = stack.popShort();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than type Short.
 */
            case icmpg_s:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popShort();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than type Short.
 */
            case iucmpg_s:
            {
                uint_32 b = stack.popUnsignedInt();
                int_16 a = stack.popShort();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 equal with type Short.
 */
            case icmpe_s:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popShort();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 equal with type Short.
 */
            case iucmpe_s:
            {
                uint_32 b = stack.popUnsignedInt();
                int_16 a = stack.popShort();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 less than or equal to type Short.
 */
            case icmple_s:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popShort();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than or equal to type Short.
 */
            case iucmple_s:
            {
                uint_32 b = stack.popUnsignedInt();
                int_16 a = stack.popShort();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than or equal to type Short.
 */
            case icmpge_s:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popShort();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than or equal to type Short.
 */
            case iucmpge_s:
            {
                uint_32 b = stack.popUnsignedInt();
                int_16 a = stack.popShort();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 not equal with type Short.
 */
            case icmpne_s:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popShort();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 not equal with type Short.
 */
            case iucmpne_s:
            {
                uint_32 b = stack.popUnsignedInt();
                int_16 a = stack.popShort();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_32 to type Int.
 */
            case icast_i:
                stack.pushInt(static_cast<int_32> (stack.popInt()));
                break;
/**
 * cast unsigned uint_32 to type Int.
 */
            case iucast_i:
                stack.pushInt(static_cast<int_32> (stack.popUnsignedInt()));
                break;
/**
 * add int_32 with type Int.
 */
            case iadd_i:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popInt();
                stack.pushInt(a + b);
            }
                break;
/**
 * add unsigned uint_32 with type Int.
 */
            case iuadd_i:
            {
                uint_32 b = stack.popUnsignedInt();
                int_32 a = stack.popInt();
                stack.pushInt(a + b);
            }
                break;
/**
 * subtract int_32 with type Int.
 */
            case isub_i:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popInt();
                stack.pushInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_32 with type Int.
 */
            case iusub_i:
            {
                uint_32 b = stack.popUnsignedInt();
                int_32 a = stack.popInt();
                stack.pushInt(a - b);
            }
                break;
/**
 * multiply int_32 with type Int.
 */
            case imul_i:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popInt();
                stack.pushInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_32 with type Int.
 */
            case iumul_i:
            {
                uint_32 b = stack.popUnsignedInt();
                int_32 a = stack.popInt();
                stack.pushInt(a * b);
            }
                break;
/**
 * divide int_32 with type Int.
 */
            case idiv_i:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popInt();
                stack.pushInt(a / b);
            }
                break;
/**
 * divide unsigned uint_32 with type Int.
 */
            case iudiv_i:
            {
                uint_32 b = stack.popUnsignedInt();
                int_32 a = stack.popInt();
                stack.pushInt(a / b);
            }
                break;
/**
 * compare int_32 less than type Int.
 */
            case icmpl_i:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than type Int.
 */
            case iucmpl_i:
            {
                uint_32 b = stack.popUnsignedInt();
                int_32 a = stack.popInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than type Int.
 */
            case icmpg_i:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than type Int.
 */
            case iucmpg_i:
            {
                uint_32 b = stack.popUnsignedInt();
                int_32 a = stack.popInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 equal with type Int.
 */
            case icmpe_i:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 equal with type Int.
 */
            case iucmpe_i:
            {
                uint_32 b = stack.popUnsignedInt();
                int_32 a = stack.popInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 less than or equal to type Int.
 */
            case icmple_i:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than or equal to type Int.
 */
            case iucmple_i:
            {
                uint_32 b = stack.popUnsignedInt();
                int_32 a = stack.popInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than or equal to type Int.
 */
            case icmpge_i:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than or equal to type Int.
 */
            case iucmpge_i:
            {
                uint_32 b = stack.popUnsignedInt();
                int_32 a = stack.popInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 not equal with type Int.
 */
            case icmpne_i:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 not equal with type Int.
 */
            case iucmpne_i:
            {
                uint_32 b = stack.popUnsignedInt();
                int_32 a = stack.popInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_32 to type Long.
 */
            case icast_l:
                stack.pushLong(static_cast<int_64> (stack.popInt()));
                break;
/**
 * cast unsigned uint_32 to type Long.
 */
            case iucast_l:
                stack.pushLong(static_cast<int_64> (stack.popUnsignedInt()));
                break;
/**
 * add int_32 with type Long.
 */
            case iadd_l:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popLong();
                stack.pushLong(a + b);
            }
                break;
/**
 * add unsigned uint_32 with type Long.
 */
            case iuadd_l:
            {
                uint_32 b = stack.popUnsignedInt();
                int_64 a = stack.popLong();
                stack.pushLong(a + b);
            }
                break;
/**
 * subtract int_32 with type Long.
 */
            case isub_l:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popLong();
                stack.pushLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_32 with type Long.
 */
            case iusub_l:
            {
                uint_32 b = stack.popUnsignedInt();
                int_64 a = stack.popLong();
                stack.pushLong(a - b);
            }
                break;
/**
 * multiply int_32 with type Long.
 */
            case imul_l:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popLong();
                stack.pushLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_32 with type Long.
 */
            case iumul_l:
            {
                uint_32 b = stack.popUnsignedInt();
                int_64 a = stack.popLong();
                stack.pushLong(a * b);
            }
                break;
/**
 * divide int_32 with type Long.
 */
            case idiv_l:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popLong();
                stack.pushLong(a / b);
            }
                break;
/**
 * divide unsigned uint_32 with type Long.
 */
            case iudiv_l:
            {
                uint_32 b = stack.popUnsignedInt();
                int_64 a = stack.popLong();
                stack.pushLong(a / b);
            }
                break;
/**
 * compare int_32 less than type Long.
 */
            case icmpl_l:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than type Long.
 */
            case iucmpl_l:
            {
                uint_32 b = stack.popUnsignedInt();
                int_64 a = stack.popLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than type Long.
 */
            case icmpg_l:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than type Long.
 */
            case iucmpg_l:
            {
                uint_32 b = stack.popUnsignedInt();
                int_64 a = stack.popLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 equal with type Long.
 */
            case icmpe_l:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 equal with type Long.
 */
            case iucmpe_l:
            {
                uint_32 b = stack.popUnsignedInt();
                int_64 a = stack.popLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 less than or equal to type Long.
 */
            case icmple_l:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than or equal to type Long.
 */
            case iucmple_l:
            {
                uint_32 b = stack.popUnsignedInt();
                int_64 a = stack.popLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than or equal to type Long.
 */
            case icmpge_l:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than or equal to type Long.
 */
            case iucmpge_l:
            {
                uint_32 b = stack.popUnsignedInt();
                int_64 a = stack.popLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 not equal with type Long.
 */
            case icmpne_l:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 not equal with type Long.
 */
            case iucmpne_l:
            {
                uint_32 b = stack.popUnsignedInt();
                int_64 a = stack.popLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_32 to type LongInt.
 */
            case icast_li:
                stack.pushLongInt(static_cast<int_128> (stack.popInt()));
                break;
/**
 * cast unsigned uint_32 to type LongInt.
 */
            case iucast_li:
                stack.pushLongInt(static_cast<int_128> (stack.popUnsignedInt()));
                break;
/**
 * add int_32 with type LongInt.
 */
            case iadd_li:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a + b);
            }
                break;
/**
 * add unsigned uint_32 with type LongInt.
 */
            case iuadd_li:
            {
                uint_32 b = stack.popUnsignedInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a + b);
            }
                break;
/**
 * subtract int_32 with type LongInt.
 */
            case isub_li:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_32 with type LongInt.
 */
            case iusub_li:
            {
                uint_32 b = stack.popUnsignedInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a - b);
            }
                break;
/**
 * multiply int_32 with type LongInt.
 */
            case imul_li:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_32 with type LongInt.
 */
            case iumul_li:
            {
                uint_32 b = stack.popUnsignedInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a * b);
            }
                break;
/**
 * divide int_32 with type LongInt.
 */
            case idiv_li:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a / b);
            }
                break;
/**
 * divide unsigned uint_32 with type LongInt.
 */
            case iudiv_li:
            {
                uint_32 b = stack.popUnsignedInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a / b);
            }
                break;
/**
 * compare int_32 less than type LongInt.
 */
            case icmpl_li:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than type LongInt.
 */
            case iucmpl_li:
            {
                uint_32 b = stack.popUnsignedInt();
                int_128 a = stack.popLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than type LongInt.
 */
            case icmpg_li:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than type LongInt.
 */
            case iucmpg_li:
            {
                uint_32 b = stack.popUnsignedInt();
                int_128 a = stack.popLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 equal with type LongInt.
 */
            case icmpe_li:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 equal with type LongInt.
 */
            case iucmpe_li:
            {
                uint_32 b = stack.popUnsignedInt();
                int_128 a = stack.popLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 less than or equal to type LongInt.
 */
            case icmple_li:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than or equal to type LongInt.
 */
            case iucmple_li:
            {
                uint_32 b = stack.popUnsignedInt();
                int_128 a = stack.popLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than or equal to type LongInt.
 */
            case icmpge_li:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than or equal to type LongInt.
 */
            case iucmpge_li:
            {
                uint_32 b = stack.popUnsignedInt();
                int_128 a = stack.popLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 not equal with type LongInt.
 */
            case icmpne_li:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 not equal with type LongInt.
 */
            case iucmpne_li:
            {
                uint_32 b = stack.popUnsignedInt();
                int_128 a = stack.popLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_32 to type LongLong.
 */
            case icast_ll:
                stack.pushLongLong(static_cast<int_256> (stack.popInt()));
                break;
/**
 * cast unsigned uint_32 to type LongLong.
 */
            case iucast_ll:
                stack.pushLongLong(static_cast<int_256> (stack.popUnsignedInt()));
                break;
/**
 * add int_32 with type LongLong.
 */
            case iadd_ll:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_32 with type LongLong.
 */
            case iuadd_ll:
            {
                uint_32 b = stack.popUnsignedInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * subtract int_32 with type LongLong.
 */
            case isub_ll:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_32 with type LongLong.
 */
            case iusub_ll:
            {
                uint_32 b = stack.popUnsignedInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * multiply int_32 with type LongLong.
 */
            case imul_ll:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_32 with type LongLong.
 */
            case iumul_ll:
            {
                uint_32 b = stack.popUnsignedInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * divide int_32 with type LongLong.
 */
            case idiv_ll:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_32 with type LongLong.
 */
            case iudiv_ll:
            {
                uint_32 b = stack.popUnsignedInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * compare int_32 less than type LongLong.
 */
            case icmpl_ll:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than type LongLong.
 */
            case iucmpl_ll:
            {
                uint_32 b = stack.popUnsignedInt();
                int_256 a = stack.popLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than type LongLong.
 */
            case icmpg_ll:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than type LongLong.
 */
            case iucmpg_ll:
            {
                uint_32 b = stack.popUnsignedInt();
                int_256 a = stack.popLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 equal with type LongLong.
 */
            case icmpe_ll:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 equal with type LongLong.
 */
            case iucmpe_ll:
            {
                uint_32 b = stack.popUnsignedInt();
                int_256 a = stack.popLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 less than or equal to type LongLong.
 */
            case icmple_ll:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than or equal to type LongLong.
 */
            case iucmple_ll:
            {
                uint_32 b = stack.popUnsignedInt();
                int_256 a = stack.popLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than or equal to type LongLong.
 */
            case icmpge_ll:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than or equal to type LongLong.
 */
            case iucmpge_ll:
            {
                uint_32 b = stack.popUnsignedInt();
                int_256 a = stack.popLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 not equal with type LongLong.
 */
            case icmpne_ll:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 not equal with type LongLong.
 */
            case iucmpne_ll:
            {
                uint_32 b = stack.popUnsignedInt();
                int_256 a = stack.popLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_32 to type Float.
 */
            case icast_f:
                stack.pushFloat(static_cast<flt_32> (stack.popInt()));
                break;
/**
 * cast unsigned uint_32 to type Float.
 */
            case iucast_f:
                stack.pushFloat(static_cast<flt_32> (stack.popUnsignedInt()));
                break;
/**
 * add int_32 with type Float.
 */
            case iadd_f:
            {
                int_32 b = stack.popInt();
                flt_32 a = stack.popFloat();
                stack.pushInt(a + b);
            }
                break;
/**
 * add unsigned uint_32 with type Float.
 */
            case iuadd_f:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_32 a = stack.popFloat();
                stack.pushInt(a + b);
            }
                break;
/**
 * subtract int_32 with type Float.
 */
            case isub_f:
            {
                int_32 b = stack.popInt();
                flt_32 a = stack.popFloat();
                stack.pushInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_32 with type Float.
 */
            case iusub_f:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_32 a = stack.popFloat();
                stack.pushInt(a - b);
            }
                break;
/**
 * multiply int_32 with type Float.
 */
            case imul_f:
            {
                int_32 b = stack.popInt();
                flt_32 a = stack.popFloat();
                stack.pushInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_32 with type Float.
 */
            case iumul_f:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_32 a = stack.popFloat();
                stack.pushInt(a * b);
            }
                break;
/**
 * divide int_32 with type Float.
 */
            case idiv_f:
            {
                int_32 b = stack.popInt();
                flt_32 a = stack.popFloat();
                stack.pushInt(a / b);
            }
                break;
/**
 * divide unsigned uint_32 with type Float.
 */
            case iudiv_f:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_32 a = stack.popFloat();
                stack.pushInt(a / b);
            }
                break;
/**
 * compare int_32 less than type Float.
 */
            case icmpl_f:
            {
                int_32 b = stack.popInt();
                flt_32 a = stack.popFloat();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than type Float.
 */
            case iucmpl_f:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_32 a = stack.popFloat();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than type Float.
 */
            case icmpg_f:
            {
                int_32 b = stack.popInt();
                flt_32 a = stack.popFloat();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than type Float.
 */
            case iucmpg_f:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_32 a = stack.popFloat();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 equal with type Float.
 */
            case icmpe_f:
            {
                int_32 b = stack.popInt();
                flt_32 a = stack.popFloat();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 equal with type Float.
 */
            case iucmpe_f:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_32 a = stack.popFloat();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 less than or equal to type Float.
 */
            case icmple_f:
            {
                int_32 b = stack.popInt();
                flt_32 a = stack.popFloat();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than or equal to type Float.
 */
            case iucmple_f:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_32 a = stack.popFloat();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than or equal to type Float.
 */
            case icmpge_f:
            {
                int_32 b = stack.popInt();
                flt_32 a = stack.popFloat();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than or equal to type Float.
 */
            case iucmpge_f:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_32 a = stack.popFloat();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 not equal with type Float.
 */
            case icmpne_f:
            {
                int_32 b = stack.popInt();
                flt_32 a = stack.popFloat();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 not equal with type Float.
 */
            case iucmpne_f:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_32 a = stack.popFloat();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_32 to type Double.
 */
            case icast_d:
                stack.pushDouble(static_cast<flt_64> (stack.popInt()));
                break;
/**
 * cast unsigned uint_32 to type Double.
 */
            case iucast_d:
                stack.pushDouble(static_cast<flt_64> (stack.popUnsignedInt()));
                break;
/**
 * add int_32 with type Double.
 */
            case iadd_d:
            {
                int_32 b = stack.popInt();
                flt_64 a = stack.popDouble();
                stack.pushDouble(a + b);
            }
                break;
/**
 * add unsigned uint_32 with type Double.
 */
            case iuadd_d:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_64 a = stack.popDouble();
                stack.pushDouble(a + b);
            }
                break;
/**
 * subtract int_32 with type Double.
 */
            case isub_d:
            {
                int_32 b = stack.popInt();
                flt_64 a = stack.popDouble();
                stack.pushDouble(a - b);
            }
                break;
/**
 * subtract unsigned uint_32 with type Double.
 */
            case iusub_d:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_64 a = stack.popDouble();
                stack.pushDouble(a - b);
            }
                break;
/**
 * multiply int_32 with type Double.
 */
            case imul_d:
            {
                int_32 b = stack.popInt();
                flt_64 a = stack.popDouble();
                stack.pushDouble(a * b);
            }
                break;
/**
 * multiply unsigned uint_32 with type Double.
 */
            case iumul_d:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_64 a = stack.popDouble();
                stack.pushDouble(a * b);
            }
                break;
/**
 * divide int_32 with type Double.
 */
            case idiv_d:
            {
                int_32 b = stack.popInt();
                flt_64 a = stack.popDouble();
                stack.pushDouble(a / b);
            }
                break;
/**
 * divide unsigned uint_32 with type Double.
 */
            case iudiv_d:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_64 a = stack.popDouble();
                stack.pushDouble(a / b);
            }
                break;
/**
 * compare int_32 less than type Double.
 */
            case icmpl_d:
            {
                int_32 b = stack.popInt();
                flt_64 a = stack.popDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than type Double.
 */
            case iucmpl_d:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_64 a = stack.popDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than type Double.
 */
            case icmpg_d:
            {
                int_32 b = stack.popInt();
                flt_64 a = stack.popDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than type Double.
 */
            case iucmpg_d:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_64 a = stack.popDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 equal with type Double.
 */
            case icmpe_d:
            {
                int_32 b = stack.popInt();
                flt_64 a = stack.popDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 equal with type Double.
 */
            case iucmpe_d:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_64 a = stack.popDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 less than or equal to type Double.
 */
            case icmple_d:
            {
                int_32 b = stack.popInt();
                flt_64 a = stack.popDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than or equal to type Double.
 */
            case iucmple_d:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_64 a = stack.popDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than or equal to type Double.
 */
            case icmpge_d:
            {
                int_32 b = stack.popInt();
                flt_64 a = stack.popDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than or equal to type Double.
 */
            case iucmpge_d:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_64 a = stack.popDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 not equal with type Double.
 */
            case icmpne_d:
            {
                int_32 b = stack.popInt();
                flt_64 a = stack.popDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 not equal with type Double.
 */
            case iucmpne_d:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_64 a = stack.popDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_32 to type DoubleFloat.
 */
            case icast_df:
                stack.pushDoubleFloat(static_cast<flt_128> (stack.popInt()));
                break;
/**
 * cast unsigned uint_32 to type DoubleFloat.
 */
            case iucast_df:
                stack.pushDoubleFloat(static_cast<flt_128> (stack.popUnsignedInt()));
                break;
/**
 * add int_32 with type DoubleFloat.
 */
            case iadd_df:
            {
                int_32 b = stack.popInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a + b);
            }
                break;
/**
 * add unsigned uint_32 with type DoubleFloat.
 */
            case iuadd_df:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a + b);
            }
                break;
/**
 * subtract int_32 with type DoubleFloat.
 */
            case isub_df:
            {
                int_32 b = stack.popInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a - b);
            }
                break;
/**
 * subtract unsigned uint_32 with type DoubleFloat.
 */
            case iusub_df:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a - b);
            }
                break;
/**
 * multiply int_32 with type DoubleFloat.
 */
            case imul_df:
            {
                int_32 b = stack.popInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a * b);
            }
                break;
/**
 * multiply unsigned uint_32 with type DoubleFloat.
 */
            case iumul_df:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a * b);
            }
                break;
/**
 * divide int_32 with type DoubleFloat.
 */
            case idiv_df:
            {
                int_32 b = stack.popInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a / b);
            }
                break;
/**
 * divide unsigned uint_32 with type DoubleFloat.
 */
            case iudiv_df:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a / b);
            }
                break;
/**
 * compare int_32 less than type DoubleFloat.
 */
            case icmpl_df:
            {
                int_32 b = stack.popInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than type DoubleFloat.
 */
            case iucmpl_df:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than type DoubleFloat.
 */
            case icmpg_df:
            {
                int_32 b = stack.popInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than type DoubleFloat.
 */
            case iucmpg_df:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 equal with type DoubleFloat.
 */
            case icmpe_df:
            {
                int_32 b = stack.popInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 equal with type DoubleFloat.
 */
            case iucmpe_df:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 less than or equal to type DoubleFloat.
 */
            case icmple_df:
            {
                int_32 b = stack.popInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than or equal to type DoubleFloat.
 */
            case iucmple_df:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than or equal to type DoubleFloat.
 */
            case icmpge_df:
            {
                int_32 b = stack.popInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than or equal to type DoubleFloat.
 */
            case iucmpge_df:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 not equal with type DoubleFloat.
 */
            case icmpne_df:
            {
                int_32 b = stack.popInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 not equal with type DoubleFloat.
 */
            case iucmpne_df:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_32 to type DoubleDouble.
 */
            case icast_dd:
                stack.pushDoubleDouble(static_cast<flt_256> (stack.popInt()));
                break;
/**
 * cast unsigned uint_32 to type DoubleDouble.
 */
            case iucast_dd:
                stack.pushDoubleDouble(static_cast<flt_256> (stack.popUnsignedInt()));
                break;
/**
 * add int_32 with type DoubleDouble.
 */
            case iadd_dd:
            {
                int_32 b = stack.popInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a + b);
            }
                break;
/**
 * add unsigned uint_32 with type DoubleDouble.
 */
            case iuadd_dd:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a + b);
            }
                break;
/**
 * subtract int_32 with type DoubleDouble.
 */
            case isub_dd:
            {
                int_32 b = stack.popInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a - b);
            }
                break;
/**
 * subtract unsigned uint_32 with type DoubleDouble.
 */
            case iusub_dd:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a - b);
            }
                break;
/**
 * multiply int_32 with type DoubleDouble.
 */
            case imul_dd:
            {
                int_32 b = stack.popInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a * b);
            }
                break;
/**
 * multiply unsigned uint_32 with type DoubleDouble.
 */
            case iumul_dd:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a * b);
            }
                break;
/**
 * divide int_32 with type DoubleDouble.
 */
            case idiv_dd:
            {
                int_32 b = stack.popInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a / b);
            }
                break;
/**
 * divide unsigned uint_32 with type DoubleDouble.
 */
            case iudiv_dd:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a / b);
            }
                break;
/**
 * compare int_32 less than type DoubleDouble.
 */
            case icmpl_dd:
            {
                int_32 b = stack.popInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than type DoubleDouble.
 */
            case iucmpl_dd:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than type DoubleDouble.
 */
            case icmpg_dd:
            {
                int_32 b = stack.popInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than type DoubleDouble.
 */
            case iucmpg_dd:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 equal with type DoubleDouble.
 */
            case icmpe_dd:
            {
                int_32 b = stack.popInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 equal with type DoubleDouble.
 */
            case iucmpe_dd:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 less than or equal to type DoubleDouble.
 */
            case icmple_dd:
            {
                int_32 b = stack.popInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than or equal to type DoubleDouble.
 */
            case iucmple_dd:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than or equal to type DoubleDouble.
 */
            case icmpge_dd:
            {
                int_32 b = stack.popInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than or equal to type DoubleDouble.
 */
            case iucmpge_dd:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 not equal with type DoubleDouble.
 */
            case icmpne_dd:
            {
                int_32 b = stack.popInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 not equal with type DoubleDouble.
 */
            case iucmpne_dd:
            {
                uint_32 b = stack.popUnsignedInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_32 with type Byte.
 */
            case imod_b:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a % b);
            }
                break;
/**
 * cast int_32 to unsigned type Byte.
 */
            case icast_ub:
                stack.pushUnsignedByte(static_cast<uint_8> (stack.popInt()));
                break;
/**
 * cast unsigned uint_32 to unsigned type Byte.
 */
            case iucast_ub:
                stack.pushUnsignedByte(static_cast<uint_8> (stack.popUnsignedInt()));
                break;
/**
 * add int_32 with unsigned type Byte.
 */
            case iadd_ub:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a + b);
            }
                break;
/**
 * add unsigned uint_32 with unsigned type Byte.
 */
            case iuadd_ub:
            {
                uint_32 b = stack.popUnsignedInt();
                int_8 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a + b);
            }
                break;
/**
 * subtract int_32 with unsigned type Byte.
 */
            case isub_ub:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_32 with unsigned type Byte.
 */
            case iusub_ub:
            {
                uint_32 b = stack.popUnsignedInt();
                int_8 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a - b);
            }
                break;
/**
 * multiply int_32 with unsigned type Byte.
 */
            case imul_ub:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_32 with unsigned type Byte.
 */
            case iumul_ub:
            {
                uint_32 b = stack.popUnsignedInt();
                int_8 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a * b);
            }
                break;
/**
 * divide int_32 with unsigned type Byte.
 */
            case idiv_ub:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a / b);
            }
                break;
/**
 * divide unsigned uint_32 with unsigned type Byte.
 */
            case iudiv_ub:
            {
                uint_32 b = stack.popUnsignedInt();
                int_8 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a / b);
            }
                break;
/**
 * compare int_32 less than unsigned type Byte.
 */
            case icmpl_ub:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popUnsignedInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than unsigned type Byte.
 */
            case iucmpl_ub:
            {
                uint_32 b = stack.popUnsignedInt();
                int_8 a = stack.popUnsignedInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than unsigned type Byte.
 */
            case icmpg_ub:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popUnsignedInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than unsigned type Byte.
 */
            case iucmpg_ub:
            {
                uint_32 b = stack.popUnsignedInt();
                int_8 a = stack.popUnsignedInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 equal with unsigned type Byte.
 */
            case icmpe_ub:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popUnsignedInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 equal with unsigned type Byte.
 */
            case iucmpe_ub:
            {
                uint_32 b = stack.popUnsignedInt();
                int_8 a = stack.popUnsignedInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 less than or equal to unsigned type Byte.
 */
            case icmple_ub:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popUnsignedInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than or equal to unsigned type Byte.
 */
            case iucmple_ub:
            {
                uint_32 b = stack.popUnsignedInt();
                int_8 a = stack.popUnsignedInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than or equal to unsigned type Byte.
 */
            case icmpge_ub:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popUnsignedInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than or equal to unsigned type Byte.
 */
            case iucmpge_ub:
            {
                uint_32 b = stack.popUnsignedInt();
                int_8 a = stack.popUnsignedInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 not equal with unsigned type Byte.
 */
            case icmpne_ub:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popUnsignedInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 not equal with unsigned type Byte.
 */
            case iucmpne_ub:
            {
                uint_32 b = stack.popUnsignedInt();
                int_8 a = stack.popUnsignedInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_32 with type Short.
 */
            case imod_s:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a % b);
            }
                break;
/**
 * cast int_32 to unsigned type Short.
 */
            case icast_us:
                stack.pushUnsignedShort(static_cast<uint_16> (stack.popInt()));
                break;
/**
 * cast unsigned uint_32 to unsigned type Short.
 */
            case iucast_us:
                stack.pushUnsignedShort(static_cast<uint_16> (stack.popUnsignedInt()));
                break;
/**
 * add int_32 with unsigned type Short.
 */
            case iadd_us:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a + b);
            }
                break;
/**
 * add unsigned uint_32 with unsigned type Short.
 */
            case iuadd_us:
            {
                uint_32 b = stack.popUnsignedInt();
                int_16 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a + b);
            }
                break;
/**
 * subtract int_32 with unsigned type Short.
 */
            case isub_us:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_32 with unsigned type Short.
 */
            case iusub_us:
            {
                uint_32 b = stack.popUnsignedInt();
                int_16 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a - b);
            }
                break;
/**
 * multiply int_32 with unsigned type Short.
 */
            case imul_us:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_32 with unsigned type Short.
 */
            case iumul_us:
            {
                uint_32 b = stack.popUnsignedInt();
                int_16 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a * b);
            }
                break;
/**
 * divide int_32 with unsigned type Short.
 */
            case idiv_us:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a / b);
            }
                break;
/**
 * divide unsigned uint_32 with unsigned type Short.
 */
            case iudiv_us:
            {
                uint_32 b = stack.popUnsignedInt();
                int_16 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a / b);
            }
                break;
/**
 * compare int_32 less than unsigned type Short.
 */
            case icmpl_us:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popUnsignedInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than unsigned type Short.
 */
            case iucmpl_us:
            {
                uint_32 b = stack.popUnsignedInt();
                int_16 a = stack.popUnsignedInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than unsigned type Short.
 */
            case icmpg_us:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popUnsignedInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than unsigned type Short.
 */
            case iucmpg_us:
            {
                uint_32 b = stack.popUnsignedInt();
                int_16 a = stack.popUnsignedInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 equal with unsigned type Short.
 */
            case icmpe_us:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popUnsignedInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 equal with unsigned type Short.
 */
            case iucmpe_us:
            {
                uint_32 b = stack.popUnsignedInt();
                int_16 a = stack.popUnsignedInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 less than or equal to unsigned type Short.
 */
            case icmple_us:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popUnsignedInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than or equal to unsigned type Short.
 */
            case iucmple_us:
            {
                uint_32 b = stack.popUnsignedInt();
                int_16 a = stack.popUnsignedInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than or equal to unsigned type Short.
 */
            case icmpge_us:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popUnsignedInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than or equal to unsigned type Short.
 */
            case iucmpge_us:
            {
                uint_32 b = stack.popUnsignedInt();
                int_16 a = stack.popUnsignedInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 not equal with unsigned type Short.
 */
            case icmpne_us:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popUnsignedInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 not equal with unsigned type Short.
 */
            case iucmpne_us:
            {
                uint_32 b = stack.popUnsignedInt();
                int_16 a = stack.popUnsignedInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_32 with type Int.
 */
            case imod_i:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a % b);
            }
                break;
/**
 * cast int_32 to unsigned type Int.
 */
            case icast_ui:
                stack.pushUnsignedInt(static_cast<uint_32> (stack.popInt()));
                break;
/**
 * cast unsigned uint_32 to unsigned type Int.
 */
            case iucast_ui:
                stack.pushUnsignedInt(static_cast<uint_32> (stack.popUnsignedInt()));
                break;
/**
 * add int_32 with unsigned type Int.
 */
            case iadd_ui:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a + b);
            }
                break;
/**
 * add unsigned uint_32 with unsigned type Int.
 */
            case iuadd_ui:
            {
                uint_32 b = stack.popUnsignedInt();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a + b);
            }
                break;
/**
 * subtract int_32 with unsigned type Int.
 */
            case isub_ui:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_32 with unsigned type Int.
 */
            case iusub_ui:
            {
                uint_32 b = stack.popUnsignedInt();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a - b);
            }
                break;
/**
 * multiply int_32 with unsigned type Int.
 */
            case imul_ui:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_32 with unsigned type Int.
 */
            case iumul_ui:
            {
                uint_32 b = stack.popUnsignedInt();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a * b);
            }
                break;
/**
 * divide int_32 with unsigned type Int.
 */
            case idiv_ui:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a / b);
            }
                break;
/**
 * divide unsigned uint_32 with unsigned type Int.
 */
            case iudiv_ui:
            {
                uint_32 b = stack.popUnsignedInt();
                int_32 a = stack.popUnsignedInt();
                stack.pushUnsignedInt(a / b);
            }
                break;
/**
 * compare int_32 less than unsigned type Int.
 */
            case icmpl_ui:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than unsigned type Int.
 */
            case iucmpl_ui:
            {
                uint_32 b = stack.popUnsignedInt();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than unsigned type Int.
 */
            case icmpg_ui:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than unsigned type Int.
 */
            case iucmpg_ui:
            {
                uint_32 b = stack.popUnsignedInt();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 equal with unsigned type Int.
 */
            case icmpe_ui:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 equal with unsigned type Int.
 */
            case iucmpe_ui:
            {
                uint_32 b = stack.popUnsignedInt();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 less than or equal to unsigned type Int.
 */
            case icmple_ui:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than or equal to unsigned type Int.
 */
            case iucmple_ui:
            {
                uint_32 b = stack.popUnsignedInt();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than or equal to unsigned type Int.
 */
            case icmpge_ui:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than or equal to unsigned type Int.
 */
            case iucmpge_ui:
            {
                uint_32 b = stack.popUnsignedInt();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 not equal with unsigned type Int.
 */
            case icmpne_ui:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 not equal with unsigned type Int.
 */
            case iucmpne_ui:
            {
                uint_32 b = stack.popUnsignedInt();
                int_32 a = stack.popUnsignedInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_32 with type Long.
 */
            case imod_l:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a % b);
            }
                break;
/**
 * cast int_32 to unsigned type Long.
 */
            case icast_ul:
                stack.pushUnsignedLong(static_cast<uint_64> (stack.popInt()));
                break;
/**
 * cast unsigned uint_32 to unsigned type Long.
 */
            case iucast_ul:
                stack.pushUnsignedLong(static_cast<uint_64> (stack.popUnsignedInt()));
                break;
/**
 * add int_32 with unsigned type Long.
 */
            case iadd_ul:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a + b);
            }
                break;
/**
 * add unsigned uint_32 with unsigned type Long.
 */
            case iuadd_ul:
            {
                uint_32 b = stack.popUnsignedInt();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a + b);
            }
                break;
/**
 * subtract int_32 with unsigned type Long.
 */
            case isub_ul:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_32 with unsigned type Long.
 */
            case iusub_ul:
            {
                uint_32 b = stack.popUnsignedInt();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a - b);
            }
                break;
/**
 * multiply int_32 with unsigned type Long.
 */
            case imul_ul:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_32 with unsigned type Long.
 */
            case iumul_ul:
            {
                uint_32 b = stack.popUnsignedInt();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a * b);
            }
                break;
/**
 * divide int_32 with unsigned type Long.
 */
            case idiv_ul:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a / b);
            }
                break;
/**
 * divide unsigned uint_32 with unsigned type Long.
 */
            case iudiv_ul:
            {
                uint_32 b = stack.popUnsignedInt();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a / b);
            }
                break;
/**
 * compare int_32 less than unsigned type Long.
 */
            case icmpl_ul:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than unsigned type Long.
 */
            case iucmpl_ul:
            {
                uint_32 b = stack.popUnsignedInt();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than unsigned type Long.
 */
            case icmpg_ul:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than unsigned type Long.
 */
            case iucmpg_ul:
            {
                uint_32 b = stack.popUnsignedInt();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 equal with unsigned type Long.
 */
            case icmpe_ul:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 equal with unsigned type Long.
 */
            case iucmpe_ul:
            {
                uint_32 b = stack.popUnsignedInt();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 less than or equal to unsigned type Long.
 */
            case icmple_ul:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than or equal to unsigned type Long.
 */
            case iucmple_ul:
            {
                uint_32 b = stack.popUnsignedInt();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than or equal to unsigned type Long.
 */
            case icmpge_ul:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than or equal to unsigned type Long.
 */
            case iucmpge_ul:
            {
                uint_32 b = stack.popUnsignedInt();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 not equal with unsigned type Long.
 */
            case icmpne_ul:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 not equal with unsigned type Long.
 */
            case iucmpne_ul:
            {
                uint_32 b = stack.popUnsignedInt();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_32 with type LongInt.
 */
            case imod_li:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a % b);
            }
                break;
/**
 * cast int_32 to unsigned type LongInt.
 */
            case icast_uli:
                stack.pushUnsignedLongInt(static_cast<uint_128> (stack.popInt()));
                break;
/**
 * cast unsigned uint_32 to unsigned type LongInt.
 */
            case iucast_uli:
                stack.pushUnsignedLongInt(static_cast<uint_128> (stack.popUnsignedInt()));
                break;
/**
 * add int_32 with unsigned type LongInt.
 */
            case iadd_uli:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a + b);
            }
                break;
/**
 * add unsigned uint_32 with unsigned type LongInt.
 */
            case iuadd_uli:
            {
                uint_32 b = stack.popUnsignedInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a + b);
            }
                break;
/**
 * subtract int_32 with unsigned type LongInt.
 */
            case isub_uli:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_32 with unsigned type LongInt.
 */
            case iusub_uli:
            {
                uint_32 b = stack.popUnsignedInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a - b);
            }
                break;
/**
 * multiply int_32 with unsigned type LongInt.
 */
            case imul_uli:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_32 with unsigned type LongInt.
 */
            case iumul_uli:
            {
                uint_32 b = stack.popUnsignedInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a * b);
            }
                break;
/**
 * divide int_32 with unsigned type LongInt.
 */
            case idiv_uli:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a / b);
            }
                break;
/**
 * divide unsigned uint_32 with unsigned type LongInt.
 */
            case iudiv_uli:
            {
                uint_32 b = stack.popUnsignedInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a / b);
            }
                break;
/**
 * compare int_32 less than unsigned type LongInt.
 */
            case icmpl_uli:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than unsigned type LongInt.
 */
            case iucmpl_uli:
            {
                uint_32 b = stack.popUnsignedInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than unsigned type LongInt.
 */
            case icmpg_uli:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than unsigned type LongInt.
 */
            case iucmpg_uli:
            {
                uint_32 b = stack.popUnsignedInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 equal with unsigned type LongInt.
 */
            case icmpe_uli:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 equal with unsigned type LongInt.
 */
            case iucmpe_uli:
            {
                uint_32 b = stack.popUnsignedInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 less than or equal to unsigned type LongInt.
 */
            case icmple_uli:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than or equal to unsigned type LongInt.
 */
            case iucmple_uli:
            {
                uint_32 b = stack.popUnsignedInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than or equal to unsigned type LongInt.
 */
            case icmpge_uli:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than or equal to unsigned type LongInt.
 */
            case iucmpge_uli:
            {
                uint_32 b = stack.popUnsignedInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 not equal with unsigned type LongInt.
 */
            case icmpne_uli:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 not equal with unsigned type LongInt.
 */
            case iucmpne_uli:
            {
                uint_32 b = stack.popUnsignedInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_32 with type LongLong.
 */
            case imod_ll:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a % b);
            }
                break;
/**
 * cast int_32 to unsigned type LongLong.
 */
            case icast_ull:
                stack.pushUnsignedLongLong(static_cast<uint_256> (stack.popInt()));
                break;
/**
 * cast unsigned uint_32 to unsigned type LongLong.
 */
            case iucast_ull:
                stack.pushUnsignedLongLong(static_cast<uint_256> (stack.popUnsignedInt()));
                break;
/**
 * add int_32 with unsigned type LongLong.
 */
            case iadd_ull:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_32 with unsigned type LongLong.
 */
            case iuadd_ull:
            {
                uint_32 b = stack.popUnsignedInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a + b);
            }
                break;
/**
 * subtract int_32 with unsigned type LongLong.
 */
            case isub_ull:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_32 with unsigned type LongLong.
 */
            case iusub_ull:
            {
                uint_32 b = stack.popUnsignedInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a - b);
            }
                break;
/**
 * multiply int_32 with unsigned type LongLong.
 */
            case imul_ull:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_32 with unsigned type LongLong.
 */
            case iumul_ull:
            {
                uint_32 b = stack.popUnsignedInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a * b);
            }
                break;
/**
 * divide int_32 with unsigned type LongLong.
 */
            case idiv_ull:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_32 with unsigned type LongLong.
 */
            case iudiv_ull:
            {
                uint_32 b = stack.popUnsignedInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a / b);
            }
                break;
/**
 * compare int_32 less than unsigned type LongLong.
 */
            case icmpl_ull:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than unsigned type LongLong.
 */
            case iucmpl_ull:
            {
                uint_32 b = stack.popUnsignedInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than unsigned type LongLong.
 */
            case icmpg_ull:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than unsigned type LongLong.
 */
            case iucmpg_ull:
            {
                uint_32 b = stack.popUnsignedInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 equal with unsigned type LongLong.
 */
            case icmpe_ull:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 equal with unsigned type LongLong.
 */
            case iucmpe_ull:
            {
                uint_32 b = stack.popUnsignedInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 less than or equal to unsigned type LongLong.
 */
            case icmple_ull:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 less than or equal to unsigned type LongLong.
 */
            case iucmple_ull:
            {
                uint_32 b = stack.popUnsignedInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 greater than or equal to unsigned type LongLong.
 */
            case icmpge_ull:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 greater than or equal to unsigned type LongLong.
 */
            case iucmpge_ull:
            {
                uint_32 b = stack.popUnsignedInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_32 not equal with unsigned type LongLong.
 */
            case icmpne_ull:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_32 not equal with unsigned type LongLong.
 */
            case iucmpne_ull:
            {
                uint_32 b = stack.popUnsignedInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * bitwise and int_32 with type Byte.
 */
            case iand_b:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popByte();
                stack.pushInt(a & b);
            }
                break;
/**
 * bitwise or int_32 with type Byte.
 */
            case ior_b:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popByte();
                stack.pushInt(a | b);
            }
                break;
/**
 * bitwise xor int_32 with type Byte.
 */
            case ixor_b:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popByte();
                stack.pushInt(a ^ b);
            }
                break;
/**
 * shift right int_32 with type Byte.
 */
            case ishftr_b:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popByte();
                stack.pushInt(a >> b);
            }
                break;
/**
 * shift left xor int_32 with type Byte.
 */
            case ishftl_b:
            {
                int_32 b = stack.popInt();
                int_8 a = stack.popByte();
                stack.pushInt(a << b);
            }
                break;
/**
 * bitwise and int_32 with type Short.
 */
            case iand_s:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popShort();
                stack.pushInt(a & b);
            }
                break;
/**
 * bitwise or int_32 with type Short.
 */
            case ior_s:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popShort();
                stack.pushInt(a | b);
            }
                break;
/**
 * bitwise xor int_32 with type Short.
 */
            case ixor_s:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popShort();
                stack.pushInt(a ^ b);
            }
                break;
/**
 * shift right int_32 with type Short.
 */
            case ishftr_s:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popShort();
                stack.pushInt(a >> b);
            }
                break;
/**
 * shift left xor int_32 with type Short.
 */
            case ishftl_s:
            {
                int_32 b = stack.popInt();
                int_16 a = stack.popShort();
                stack.pushInt(a << b);
            }
                break;
/**
 * bitwise and int_32 with type Int.
 */
            case iand_i:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popInt();
                stack.pushInt(a & b);
            }
                break;
/**
 * bitwise or int_32 with type Int.
 */
            case ior_i:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popInt();
                stack.pushInt(a | b);
            }
                break;
/**
 * bitwise xor int_32 with type Int.
 */
            case ixor_i:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popInt();
                stack.pushInt(a ^ b);
            }
                break;
/**
 * shift right int_32 with type Int.
 */
            case ishftr_i:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popInt();
                stack.pushInt(a >> b);
            }
                break;
/**
 * shift left xor int_32 with type Int.
 */
            case ishftl_i:
            {
                int_32 b = stack.popInt();
                int_32 a = stack.popInt();
                stack.pushInt(a << b);
            }
                break;
/**
 * bitwise and int_32 with type Long.
 */
            case iand_l:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popLong();
                stack.pushLong(a & b);
            }
                break;
/**
 * bitwise or int_32 with type Long.
 */
            case ior_l:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popLong();
                stack.pushLong(a | b);
            }
                break;
/**
 * bitwise xor int_32 with type Long.
 */
            case ixor_l:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popLong();
                stack.pushLong(a ^ b);
            }
                break;
/**
 * shift right int_32 with type Long.
 */
            case ishftr_l:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popLong();
                stack.pushLong(a >> b);
            }
                break;
/**
 * shift left xor int_32 with type Long.
 */
            case ishftl_l:
            {
                int_32 b = stack.popInt();
                int_64 a = stack.popLong();
                stack.pushLong(a << b);
            }
                break;
/**
 * bitwise and int_32 with type LongInt.
 */
            case iand_li:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a & b);
            }
                break;
/**
 * bitwise or int_32 with type LongInt.
 */
            case ior_li:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a | b);
            }
                break;
/**
 * bitwise xor int_32 with type LongInt.
 */
            case ixor_li:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a ^ b);
            }
                break;
/**
 * shift right int_32 with type LongInt.
 */
            case ishftr_li:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a >> b);
            }
                break;
/**
 * shift left xor int_32 with type LongInt.
 */
            case ishftl_li:
            {
                int_32 b = stack.popInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a << b);
            }
                break;
/**
 * bitwise and int_32 with type LongLong.
 */
            case iand_ll:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a & b);
            }
                break;
/**
 * bitwise or int_32 with type LongLong.
 */
            case ior_ll:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a | b);
            }
                break;
/**
 * bitwise xor int_32 with type LongLong.
 */
            case ixor_ll:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a ^ b);
            }
                break;
/**
 * shift right int_32 with type LongLong.
 */
            case ishftr_ll:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a >> b);
            }
                break;
/**
 * shift left xor int_32 with type LongLong.
 */
            case ishftl_ll:
            {
                int_32 b = stack.popInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a << b);
            }
                break;
/**
 * duplicate a int_32 on the stack.
 */
            case idup:
                stack.pushInt(stack.peekInt());
                break;
/**
 * duplicate a int_32 2 times on the stack.
 */
            case idup2:
                stack.pushInt(stack.peekInt());stack.pushInt(stack.peekInt());
                break;
/**
 * duplicate a int_32 3 times on the stack.
 */
            case idup3:
                stack.pushInt(stack.peekInt());stack.pushInt(stack.peekInt());stack.pushInt(stack.peekInt());
                break;
/**
 * duplicate a int_32 4 times on the stack.
 */
            case idup4:
                stack.pushInt(stack.peekInt());stack.pushInt(stack.peekInt());stack.pushInt(stack.peekInt());stack.pushInt(stack.peekInt());
                break;
/**
 * duplicate a int_32 5 times on the stack.
 */
            case idup5:
                stack.pushInt(stack.peekInt());stack.pushInt(stack.peekInt());stack.pushInt(stack.peekInt());stack.pushInt(stack.peekInt());stack.pushInt(stack.peekInt());
                break;
/**
 * set a int_32 from stack into a field on base pointer.
 */
            case iset:
                accessMemoryAndSetInt(base, ops.getUnsignedInt(), stack.popInt());
                break;
/**
 * get a int_32 from a field on base pointer to stack.
 */
            case iget:
                stack.pushInt(accessMemoryAndGetInt(base, ops.getUnsignedInt()));
                break;
/**
 * set a int_32 from value into a field on base pointer.
 */
            case ivset:
                accessMemoryAndSetInt(base, ops.getUnsignedInt(), ops.getInt());
                break;
/**
 * get a int_32 from a field on base pointer to stack using address from stack.
 */
            case isget:
                stack.pushInt(accessMemoryAndGetInt(base, stack.popUnsignedInt()));
                break;
/**
 * set a int_32 from stack into a field on base pointer using address from stack.
 */
            case isset:
                accessMemoryAndSetInt(base, stack.popUnsignedInt(), stack.popInt());
                break;
/**
 * set a int_32 from local variable into a field on base pointer.
 */
            case isetl:
                accessMemoryAndSetInt(base, ops.getUnsignedInt(), lvt[ops.getUnsignedShort()].Int);
                break;
/**
 * increment int_32 by 1 on stack.
 */
            case iinc_1:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].Int = lvt[point].Int + 1; }
                break;
/**
 * increment int_32 by 2 on stack.
 */
            case iinc_2:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].Int = lvt[point].Int + 2; }
                break;
/**
 * increment int_32 by 1 on stack.
 */
            case istinc_1:
                stack.pushInt(stack.popInt() + 1);
                break;
/**
 * increment int_32 by 2 on stack.
 */
            case istinc_2:
                stack.pushInt(stack.popInt() + 2);
                break;
/**
 * return a int_32 into the main stack.
 */
            case ireturn:
                stack_main.pushInt(stack.popInt());
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
                log(std::to_string(stack.popInt()));
                break;
/**
 * print a unsigned uint_32 from stack.
 */
            case iuprint:
                log(std::to_string(stack.popUnsignedInt()));
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
                lvt[ops.getUnsignedShort()] = lve_Long(stack.popLong());
                break;
/**
 * store a int_64 from stack into local variable 0.
 */
            case lstore_0:
                lvt[0] = lve_Long(stack.popLong());
                break;
/**
 * store a int_64 from stack into local variable 1.
 */
            case lstore_1:
                lvt[1] = lve_Long(stack.popLong());
                break;
/**
 * store a int_64 from stack into local variable 2.
 */
            case lstore_2:
                lvt[2] = lve_Long(stack.popLong());
                break;
/**
 * store a int_64 from stack into local variable 3.
 */
            case lstore_3:
                lvt[3] = lve_Long(stack.popLong());
                break;
/**
 * store a int_64 from stack into local variable 4.
 */
            case lstore_4:
                lvt[4] = lve_Long(stack.popLong());
                break;
/**
 * cast int_64 to type Byte.
 */
            case lcast_b:
                stack.pushByte(static_cast<int_8> (stack.popLong()));
                break;
/**
 * cast unsigned uint_64 to type Byte.
 */
            case lucast_b:
                stack.pushByte(static_cast<int_8> (stack.popUnsignedLong()));
                break;
/**
 * add int_64 with type Byte.
 */
            case ladd_b:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popByte();
                stack.pushLong(a + b);
            }
                break;
/**
 * add unsigned uint_64 with type Byte.
 */
            case luadd_b:
            {
                uint_64 b = stack.popUnsignedLong();
                int_8 a = stack.popByte();
                stack.pushLong(a + b);
            }
                break;
/**
 * subtract int_64 with type Byte.
 */
            case lsub_b:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popByte();
                stack.pushLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_64 with type Byte.
 */
            case lusub_b:
            {
                uint_64 b = stack.popUnsignedLong();
                int_8 a = stack.popByte();
                stack.pushLong(a - b);
            }
                break;
/**
 * multiply int_64 with type Byte.
 */
            case lmul_b:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popByte();
                stack.pushLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_64 with type Byte.
 */
            case lumul_b:
            {
                uint_64 b = stack.popUnsignedLong();
                int_8 a = stack.popByte();
                stack.pushLong(a * b);
            }
                break;
/**
 * divide int_64 with type Byte.
 */
            case ldiv_b:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popByte();
                stack.pushLong(a / b);
            }
                break;
/**
 * divide unsigned uint_64 with type Byte.
 */
            case ludiv_b:
            {
                uint_64 b = stack.popUnsignedLong();
                int_8 a = stack.popByte();
                stack.pushLong(a / b);
            }
                break;
/**
 * compare int_64 less than type Byte.
 */
            case lcmpl_b:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popByte();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than type Byte.
 */
            case lucmpl_b:
            {
                uint_64 b = stack.popUnsignedLong();
                int_8 a = stack.popByte();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than type Byte.
 */
            case lcmpg_b:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popByte();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than type Byte.
 */
            case lucmpg_b:
            {
                uint_64 b = stack.popUnsignedLong();
                int_8 a = stack.popByte();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 equal with type Byte.
 */
            case lcmpe_b:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popByte();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 equal with type Byte.
 */
            case lucmpe_b:
            {
                uint_64 b = stack.popUnsignedLong();
                int_8 a = stack.popByte();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 less than or equal to type Byte.
 */
            case lcmple_b:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popByte();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than or equal to type Byte.
 */
            case lucmple_b:
            {
                uint_64 b = stack.popUnsignedLong();
                int_8 a = stack.popByte();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than or equal to type Byte.
 */
            case lcmpge_b:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popByte();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than or equal to type Byte.
 */
            case lucmpge_b:
            {
                uint_64 b = stack.popUnsignedLong();
                int_8 a = stack.popByte();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 not equal with type Byte.
 */
            case lcmpne_b:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popByte();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 not equal with type Byte.
 */
            case lucmpne_b:
            {
                uint_64 b = stack.popUnsignedLong();
                int_8 a = stack.popByte();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_64 to type Short.
 */
            case lcast_s:
                stack.pushShort(static_cast<int_16> (stack.popLong()));
                break;
/**
 * cast unsigned uint_64 to type Short.
 */
            case lucast_s:
                stack.pushShort(static_cast<int_16> (stack.popUnsignedLong()));
                break;
/**
 * add int_64 with type Short.
 */
            case ladd_s:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popShort();
                stack.pushLong(a + b);
            }
                break;
/**
 * add unsigned uint_64 with type Short.
 */
            case luadd_s:
            {
                uint_64 b = stack.popUnsignedLong();
                int_16 a = stack.popShort();
                stack.pushLong(a + b);
            }
                break;
/**
 * subtract int_64 with type Short.
 */
            case lsub_s:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popShort();
                stack.pushLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_64 with type Short.
 */
            case lusub_s:
            {
                uint_64 b = stack.popUnsignedLong();
                int_16 a = stack.popShort();
                stack.pushLong(a - b);
            }
                break;
/**
 * multiply int_64 with type Short.
 */
            case lmul_s:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popShort();
                stack.pushLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_64 with type Short.
 */
            case lumul_s:
            {
                uint_64 b = stack.popUnsignedLong();
                int_16 a = stack.popShort();
                stack.pushLong(a * b);
            }
                break;
/**
 * divide int_64 with type Short.
 */
            case ldiv_s:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popShort();
                stack.pushLong(a / b);
            }
                break;
/**
 * divide unsigned uint_64 with type Short.
 */
            case ludiv_s:
            {
                uint_64 b = stack.popUnsignedLong();
                int_16 a = stack.popShort();
                stack.pushLong(a / b);
            }
                break;
/**
 * compare int_64 less than type Short.
 */
            case lcmpl_s:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popShort();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than type Short.
 */
            case lucmpl_s:
            {
                uint_64 b = stack.popUnsignedLong();
                int_16 a = stack.popShort();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than type Short.
 */
            case lcmpg_s:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popShort();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than type Short.
 */
            case lucmpg_s:
            {
                uint_64 b = stack.popUnsignedLong();
                int_16 a = stack.popShort();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 equal with type Short.
 */
            case lcmpe_s:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popShort();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 equal with type Short.
 */
            case lucmpe_s:
            {
                uint_64 b = stack.popUnsignedLong();
                int_16 a = stack.popShort();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 less than or equal to type Short.
 */
            case lcmple_s:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popShort();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than or equal to type Short.
 */
            case lucmple_s:
            {
                uint_64 b = stack.popUnsignedLong();
                int_16 a = stack.popShort();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than or equal to type Short.
 */
            case lcmpge_s:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popShort();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than or equal to type Short.
 */
            case lucmpge_s:
            {
                uint_64 b = stack.popUnsignedLong();
                int_16 a = stack.popShort();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 not equal with type Short.
 */
            case lcmpne_s:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popShort();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 not equal with type Short.
 */
            case lucmpne_s:
            {
                uint_64 b = stack.popUnsignedLong();
                int_16 a = stack.popShort();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_64 to type Int.
 */
            case lcast_i:
                stack.pushInt(static_cast<int_32> (stack.popLong()));
                break;
/**
 * cast unsigned uint_64 to type Int.
 */
            case lucast_i:
                stack.pushInt(static_cast<int_32> (stack.popUnsignedLong()));
                break;
/**
 * add int_64 with type Int.
 */
            case ladd_i:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popInt();
                stack.pushLong(a + b);
            }
                break;
/**
 * add unsigned uint_64 with type Int.
 */
            case luadd_i:
            {
                uint_64 b = stack.popUnsignedLong();
                int_32 a = stack.popInt();
                stack.pushLong(a + b);
            }
                break;
/**
 * subtract int_64 with type Int.
 */
            case lsub_i:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popInt();
                stack.pushLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_64 with type Int.
 */
            case lusub_i:
            {
                uint_64 b = stack.popUnsignedLong();
                int_32 a = stack.popInt();
                stack.pushLong(a - b);
            }
                break;
/**
 * multiply int_64 with type Int.
 */
            case lmul_i:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popInt();
                stack.pushLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_64 with type Int.
 */
            case lumul_i:
            {
                uint_64 b = stack.popUnsignedLong();
                int_32 a = stack.popInt();
                stack.pushLong(a * b);
            }
                break;
/**
 * divide int_64 with type Int.
 */
            case ldiv_i:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popInt();
                stack.pushLong(a / b);
            }
                break;
/**
 * divide unsigned uint_64 with type Int.
 */
            case ludiv_i:
            {
                uint_64 b = stack.popUnsignedLong();
                int_32 a = stack.popInt();
                stack.pushLong(a / b);
            }
                break;
/**
 * compare int_64 less than type Int.
 */
            case lcmpl_i:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than type Int.
 */
            case lucmpl_i:
            {
                uint_64 b = stack.popUnsignedLong();
                int_32 a = stack.popInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than type Int.
 */
            case lcmpg_i:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than type Int.
 */
            case lucmpg_i:
            {
                uint_64 b = stack.popUnsignedLong();
                int_32 a = stack.popInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 equal with type Int.
 */
            case lcmpe_i:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 equal with type Int.
 */
            case lucmpe_i:
            {
                uint_64 b = stack.popUnsignedLong();
                int_32 a = stack.popInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 less than or equal to type Int.
 */
            case lcmple_i:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than or equal to type Int.
 */
            case lucmple_i:
            {
                uint_64 b = stack.popUnsignedLong();
                int_32 a = stack.popInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than or equal to type Int.
 */
            case lcmpge_i:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than or equal to type Int.
 */
            case lucmpge_i:
            {
                uint_64 b = stack.popUnsignedLong();
                int_32 a = stack.popInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 not equal with type Int.
 */
            case lcmpne_i:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 not equal with type Int.
 */
            case lucmpne_i:
            {
                uint_64 b = stack.popUnsignedLong();
                int_32 a = stack.popInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_64 to type Long.
 */
            case lcast_l:
                stack.pushLong(static_cast<int_64> (stack.popLong()));
                break;
/**
 * cast unsigned uint_64 to type Long.
 */
            case lucast_l:
                stack.pushLong(static_cast<int_64> (stack.popUnsignedLong()));
                break;
/**
 * add int_64 with type Long.
 */
            case ladd_l:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popLong();
                stack.pushLong(a + b);
            }
                break;
/**
 * add unsigned uint_64 with type Long.
 */
            case luadd_l:
            {
                uint_64 b = stack.popUnsignedLong();
                int_64 a = stack.popLong();
                stack.pushLong(a + b);
            }
                break;
/**
 * subtract int_64 with type Long.
 */
            case lsub_l:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popLong();
                stack.pushLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_64 with type Long.
 */
            case lusub_l:
            {
                uint_64 b = stack.popUnsignedLong();
                int_64 a = stack.popLong();
                stack.pushLong(a - b);
            }
                break;
/**
 * multiply int_64 with type Long.
 */
            case lmul_l:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popLong();
                stack.pushLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_64 with type Long.
 */
            case lumul_l:
            {
                uint_64 b = stack.popUnsignedLong();
                int_64 a = stack.popLong();
                stack.pushLong(a * b);
            }
                break;
/**
 * divide int_64 with type Long.
 */
            case ldiv_l:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popLong();
                stack.pushLong(a / b);
            }
                break;
/**
 * divide unsigned uint_64 with type Long.
 */
            case ludiv_l:
            {
                uint_64 b = stack.popUnsignedLong();
                int_64 a = stack.popLong();
                stack.pushLong(a / b);
            }
                break;
/**
 * compare int_64 less than type Long.
 */
            case lcmpl_l:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than type Long.
 */
            case lucmpl_l:
            {
                uint_64 b = stack.popUnsignedLong();
                int_64 a = stack.popLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than type Long.
 */
            case lcmpg_l:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than type Long.
 */
            case lucmpg_l:
            {
                uint_64 b = stack.popUnsignedLong();
                int_64 a = stack.popLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 equal with type Long.
 */
            case lcmpe_l:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 equal with type Long.
 */
            case lucmpe_l:
            {
                uint_64 b = stack.popUnsignedLong();
                int_64 a = stack.popLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 less than or equal to type Long.
 */
            case lcmple_l:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than or equal to type Long.
 */
            case lucmple_l:
            {
                uint_64 b = stack.popUnsignedLong();
                int_64 a = stack.popLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than or equal to type Long.
 */
            case lcmpge_l:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than or equal to type Long.
 */
            case lucmpge_l:
            {
                uint_64 b = stack.popUnsignedLong();
                int_64 a = stack.popLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 not equal with type Long.
 */
            case lcmpne_l:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 not equal with type Long.
 */
            case lucmpne_l:
            {
                uint_64 b = stack.popUnsignedLong();
                int_64 a = stack.popLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_64 to type LongInt.
 */
            case lcast_li:
                stack.pushLongInt(static_cast<int_128> (stack.popLong()));
                break;
/**
 * cast unsigned uint_64 to type LongInt.
 */
            case lucast_li:
                stack.pushLongInt(static_cast<int_128> (stack.popUnsignedLong()));
                break;
/**
 * add int_64 with type LongInt.
 */
            case ladd_li:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a + b);
            }
                break;
/**
 * add unsigned uint_64 with type LongInt.
 */
            case luadd_li:
            {
                uint_64 b = stack.popUnsignedLong();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a + b);
            }
                break;
/**
 * subtract int_64 with type LongInt.
 */
            case lsub_li:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_64 with type LongInt.
 */
            case lusub_li:
            {
                uint_64 b = stack.popUnsignedLong();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a - b);
            }
                break;
/**
 * multiply int_64 with type LongInt.
 */
            case lmul_li:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_64 with type LongInt.
 */
            case lumul_li:
            {
                uint_64 b = stack.popUnsignedLong();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a * b);
            }
                break;
/**
 * divide int_64 with type LongInt.
 */
            case ldiv_li:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a / b);
            }
                break;
/**
 * divide unsigned uint_64 with type LongInt.
 */
            case ludiv_li:
            {
                uint_64 b = stack.popUnsignedLong();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a / b);
            }
                break;
/**
 * compare int_64 less than type LongInt.
 */
            case lcmpl_li:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than type LongInt.
 */
            case lucmpl_li:
            {
                uint_64 b = stack.popUnsignedLong();
                int_128 a = stack.popLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than type LongInt.
 */
            case lcmpg_li:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than type LongInt.
 */
            case lucmpg_li:
            {
                uint_64 b = stack.popUnsignedLong();
                int_128 a = stack.popLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 equal with type LongInt.
 */
            case lcmpe_li:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 equal with type LongInt.
 */
            case lucmpe_li:
            {
                uint_64 b = stack.popUnsignedLong();
                int_128 a = stack.popLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 less than or equal to type LongInt.
 */
            case lcmple_li:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than or equal to type LongInt.
 */
            case lucmple_li:
            {
                uint_64 b = stack.popUnsignedLong();
                int_128 a = stack.popLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than or equal to type LongInt.
 */
            case lcmpge_li:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than or equal to type LongInt.
 */
            case lucmpge_li:
            {
                uint_64 b = stack.popUnsignedLong();
                int_128 a = stack.popLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 not equal with type LongInt.
 */
            case lcmpne_li:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 not equal with type LongInt.
 */
            case lucmpne_li:
            {
                uint_64 b = stack.popUnsignedLong();
                int_128 a = stack.popLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_64 to type LongLong.
 */
            case lcast_ll:
                stack.pushLongLong(static_cast<int_256> (stack.popLong()));
                break;
/**
 * cast unsigned uint_64 to type LongLong.
 */
            case lucast_ll:
                stack.pushLongLong(static_cast<int_256> (stack.popUnsignedLong()));
                break;
/**
 * add int_64 with type LongLong.
 */
            case ladd_ll:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_64 with type LongLong.
 */
            case luadd_ll:
            {
                uint_64 b = stack.popUnsignedLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * subtract int_64 with type LongLong.
 */
            case lsub_ll:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_64 with type LongLong.
 */
            case lusub_ll:
            {
                uint_64 b = stack.popUnsignedLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * multiply int_64 with type LongLong.
 */
            case lmul_ll:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_64 with type LongLong.
 */
            case lumul_ll:
            {
                uint_64 b = stack.popUnsignedLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * divide int_64 with type LongLong.
 */
            case ldiv_ll:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_64 with type LongLong.
 */
            case ludiv_ll:
            {
                uint_64 b = stack.popUnsignedLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * compare int_64 less than type LongLong.
 */
            case lcmpl_ll:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than type LongLong.
 */
            case lucmpl_ll:
            {
                uint_64 b = stack.popUnsignedLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than type LongLong.
 */
            case lcmpg_ll:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than type LongLong.
 */
            case lucmpg_ll:
            {
                uint_64 b = stack.popUnsignedLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 equal with type LongLong.
 */
            case lcmpe_ll:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 equal with type LongLong.
 */
            case lucmpe_ll:
            {
                uint_64 b = stack.popUnsignedLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 less than or equal to type LongLong.
 */
            case lcmple_ll:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than or equal to type LongLong.
 */
            case lucmple_ll:
            {
                uint_64 b = stack.popUnsignedLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than or equal to type LongLong.
 */
            case lcmpge_ll:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than or equal to type LongLong.
 */
            case lucmpge_ll:
            {
                uint_64 b = stack.popUnsignedLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 not equal with type LongLong.
 */
            case lcmpne_ll:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 not equal with type LongLong.
 */
            case lucmpne_ll:
            {
                uint_64 b = stack.popUnsignedLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_64 to type Float.
 */
            case lcast_f:
                stack.pushFloat(static_cast<flt_32> (stack.popLong()));
                break;
/**
 * cast unsigned uint_64 to type Float.
 */
            case lucast_f:
                stack.pushFloat(static_cast<flt_32> (stack.popUnsignedLong()));
                break;
/**
 * add int_64 with type Float.
 */
            case ladd_f:
            {
                int_64 b = stack.popLong();
                flt_32 a = stack.popFloat();
                stack.pushLong(a + b);
            }
                break;
/**
 * add unsigned uint_64 with type Float.
 */
            case luadd_f:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_32 a = stack.popFloat();
                stack.pushLong(a + b);
            }
                break;
/**
 * subtract int_64 with type Float.
 */
            case lsub_f:
            {
                int_64 b = stack.popLong();
                flt_32 a = stack.popFloat();
                stack.pushLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_64 with type Float.
 */
            case lusub_f:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_32 a = stack.popFloat();
                stack.pushLong(a - b);
            }
                break;
/**
 * multiply int_64 with type Float.
 */
            case lmul_f:
            {
                int_64 b = stack.popLong();
                flt_32 a = stack.popFloat();
                stack.pushLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_64 with type Float.
 */
            case lumul_f:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_32 a = stack.popFloat();
                stack.pushLong(a * b);
            }
                break;
/**
 * divide int_64 with type Float.
 */
            case ldiv_f:
            {
                int_64 b = stack.popLong();
                flt_32 a = stack.popFloat();
                stack.pushLong(a / b);
            }
                break;
/**
 * divide unsigned uint_64 with type Float.
 */
            case ludiv_f:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_32 a = stack.popFloat();
                stack.pushLong(a / b);
            }
                break;
/**
 * compare int_64 less than type Float.
 */
            case lcmpl_f:
            {
                int_64 b = stack.popLong();
                flt_32 a = stack.popFloat();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than type Float.
 */
            case lucmpl_f:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_32 a = stack.popFloat();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than type Float.
 */
            case lcmpg_f:
            {
                int_64 b = stack.popLong();
                flt_32 a = stack.popFloat();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than type Float.
 */
            case lucmpg_f:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_32 a = stack.popFloat();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 equal with type Float.
 */
            case lcmpe_f:
            {
                int_64 b = stack.popLong();
                flt_32 a = stack.popFloat();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 equal with type Float.
 */
            case lucmpe_f:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_32 a = stack.popFloat();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 less than or equal to type Float.
 */
            case lcmple_f:
            {
                int_64 b = stack.popLong();
                flt_32 a = stack.popFloat();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than or equal to type Float.
 */
            case lucmple_f:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_32 a = stack.popFloat();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than or equal to type Float.
 */
            case lcmpge_f:
            {
                int_64 b = stack.popLong();
                flt_32 a = stack.popFloat();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than or equal to type Float.
 */
            case lucmpge_f:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_32 a = stack.popFloat();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 not equal with type Float.
 */
            case lcmpne_f:
            {
                int_64 b = stack.popLong();
                flt_32 a = stack.popFloat();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 not equal with type Float.
 */
            case lucmpne_f:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_32 a = stack.popFloat();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_64 to type Double.
 */
            case lcast_d:
                stack.pushDouble(static_cast<flt_64> (stack.popLong()));
                break;
/**
 * cast unsigned uint_64 to type Double.
 */
            case lucast_d:
                stack.pushDouble(static_cast<flt_64> (stack.popUnsignedLong()));
                break;
/**
 * add int_64 with type Double.
 */
            case ladd_d:
            {
                int_64 b = stack.popLong();
                flt_64 a = stack.popDouble();
                stack.pushLong(a + b);
            }
                break;
/**
 * add unsigned uint_64 with type Double.
 */
            case luadd_d:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_64 a = stack.popDouble();
                stack.pushLong(a + b);
            }
                break;
/**
 * subtract int_64 with type Double.
 */
            case lsub_d:
            {
                int_64 b = stack.popLong();
                flt_64 a = stack.popDouble();
                stack.pushLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_64 with type Double.
 */
            case lusub_d:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_64 a = stack.popDouble();
                stack.pushLong(a - b);
            }
                break;
/**
 * multiply int_64 with type Double.
 */
            case lmul_d:
            {
                int_64 b = stack.popLong();
                flt_64 a = stack.popDouble();
                stack.pushLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_64 with type Double.
 */
            case lumul_d:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_64 a = stack.popDouble();
                stack.pushLong(a * b);
            }
                break;
/**
 * divide int_64 with type Double.
 */
            case ldiv_d:
            {
                int_64 b = stack.popLong();
                flt_64 a = stack.popDouble();
                stack.pushLong(a / b);
            }
                break;
/**
 * divide unsigned uint_64 with type Double.
 */
            case ludiv_d:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_64 a = stack.popDouble();
                stack.pushLong(a / b);
            }
                break;
/**
 * compare int_64 less than type Double.
 */
            case lcmpl_d:
            {
                int_64 b = stack.popLong();
                flt_64 a = stack.popDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than type Double.
 */
            case lucmpl_d:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_64 a = stack.popDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than type Double.
 */
            case lcmpg_d:
            {
                int_64 b = stack.popLong();
                flt_64 a = stack.popDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than type Double.
 */
            case lucmpg_d:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_64 a = stack.popDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 equal with type Double.
 */
            case lcmpe_d:
            {
                int_64 b = stack.popLong();
                flt_64 a = stack.popDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 equal with type Double.
 */
            case lucmpe_d:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_64 a = stack.popDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 less than or equal to type Double.
 */
            case lcmple_d:
            {
                int_64 b = stack.popLong();
                flt_64 a = stack.popDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than or equal to type Double.
 */
            case lucmple_d:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_64 a = stack.popDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than or equal to type Double.
 */
            case lcmpge_d:
            {
                int_64 b = stack.popLong();
                flt_64 a = stack.popDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than or equal to type Double.
 */
            case lucmpge_d:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_64 a = stack.popDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 not equal with type Double.
 */
            case lcmpne_d:
            {
                int_64 b = stack.popLong();
                flt_64 a = stack.popDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 not equal with type Double.
 */
            case lucmpne_d:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_64 a = stack.popDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_64 to type DoubleFloat.
 */
            case lcast_df:
                stack.pushDoubleFloat(static_cast<flt_128> (stack.popLong()));
                break;
/**
 * cast unsigned uint_64 to type DoubleFloat.
 */
            case lucast_df:
                stack.pushDoubleFloat(static_cast<flt_128> (stack.popUnsignedLong()));
                break;
/**
 * add int_64 with type DoubleFloat.
 */
            case ladd_df:
            {
                int_64 b = stack.popLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a + b);
            }
                break;
/**
 * add unsigned uint_64 with type DoubleFloat.
 */
            case luadd_df:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a + b);
            }
                break;
/**
 * subtract int_64 with type DoubleFloat.
 */
            case lsub_df:
            {
                int_64 b = stack.popLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a - b);
            }
                break;
/**
 * subtract unsigned uint_64 with type DoubleFloat.
 */
            case lusub_df:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a - b);
            }
                break;
/**
 * multiply int_64 with type DoubleFloat.
 */
            case lmul_df:
            {
                int_64 b = stack.popLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a * b);
            }
                break;
/**
 * multiply unsigned uint_64 with type DoubleFloat.
 */
            case lumul_df:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a * b);
            }
                break;
/**
 * divide int_64 with type DoubleFloat.
 */
            case ldiv_df:
            {
                int_64 b = stack.popLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a / b);
            }
                break;
/**
 * divide unsigned uint_64 with type DoubleFloat.
 */
            case ludiv_df:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushDoubleFloat(a / b);
            }
                break;
/**
 * compare int_64 less than type DoubleFloat.
 */
            case lcmpl_df:
            {
                int_64 b = stack.popLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than type DoubleFloat.
 */
            case lucmpl_df:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than type DoubleFloat.
 */
            case lcmpg_df:
            {
                int_64 b = stack.popLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than type DoubleFloat.
 */
            case lucmpg_df:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 equal with type DoubleFloat.
 */
            case lcmpe_df:
            {
                int_64 b = stack.popLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 equal with type DoubleFloat.
 */
            case lucmpe_df:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 less than or equal to type DoubleFloat.
 */
            case lcmple_df:
            {
                int_64 b = stack.popLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than or equal to type DoubleFloat.
 */
            case lucmple_df:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than or equal to type DoubleFloat.
 */
            case lcmpge_df:
            {
                int_64 b = stack.popLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than or equal to type DoubleFloat.
 */
            case lucmpge_df:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 not equal with type DoubleFloat.
 */
            case lcmpne_df:
            {
                int_64 b = stack.popLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 not equal with type DoubleFloat.
 */
            case lucmpne_df:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_64 to type DoubleDouble.
 */
            case lcast_dd:
                stack.pushDoubleDouble(static_cast<flt_256> (stack.popLong()));
                break;
/**
 * cast unsigned uint_64 to type DoubleDouble.
 */
            case lucast_dd:
                stack.pushDoubleDouble(static_cast<flt_256> (stack.popUnsignedLong()));
                break;
/**
 * add int_64 with type DoubleDouble.
 */
            case ladd_dd:
            {
                int_64 b = stack.popLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a + b);
            }
                break;
/**
 * add unsigned uint_64 with type DoubleDouble.
 */
            case luadd_dd:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a + b);
            }
                break;
/**
 * subtract int_64 with type DoubleDouble.
 */
            case lsub_dd:
            {
                int_64 b = stack.popLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a - b);
            }
                break;
/**
 * subtract unsigned uint_64 with type DoubleDouble.
 */
            case lusub_dd:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a - b);
            }
                break;
/**
 * multiply int_64 with type DoubleDouble.
 */
            case lmul_dd:
            {
                int_64 b = stack.popLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a * b);
            }
                break;
/**
 * multiply unsigned uint_64 with type DoubleDouble.
 */
            case lumul_dd:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a * b);
            }
                break;
/**
 * divide int_64 with type DoubleDouble.
 */
            case ldiv_dd:
            {
                int_64 b = stack.popLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a / b);
            }
                break;
/**
 * divide unsigned uint_64 with type DoubleDouble.
 */
            case ludiv_dd:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a / b);
            }
                break;
/**
 * compare int_64 less than type DoubleDouble.
 */
            case lcmpl_dd:
            {
                int_64 b = stack.popLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than type DoubleDouble.
 */
            case lucmpl_dd:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than type DoubleDouble.
 */
            case lcmpg_dd:
            {
                int_64 b = stack.popLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than type DoubleDouble.
 */
            case lucmpg_dd:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 equal with type DoubleDouble.
 */
            case lcmpe_dd:
            {
                int_64 b = stack.popLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 equal with type DoubleDouble.
 */
            case lucmpe_dd:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 less than or equal to type DoubleDouble.
 */
            case lcmple_dd:
            {
                int_64 b = stack.popLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than or equal to type DoubleDouble.
 */
            case lucmple_dd:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than or equal to type DoubleDouble.
 */
            case lcmpge_dd:
            {
                int_64 b = stack.popLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than or equal to type DoubleDouble.
 */
            case lucmpge_dd:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 not equal with type DoubleDouble.
 */
            case lcmpne_dd:
            {
                int_64 b = stack.popLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 not equal with type DoubleDouble.
 */
            case lucmpne_dd:
            {
                uint_64 b = stack.popUnsignedLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_64 with type Byte.
 */
            case lmod_b:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a % b);
            }
                break;
/**
 * cast int_64 to unsigned type Byte.
 */
            case lcast_ub:
                stack.pushUnsignedByte(static_cast<uint_8> (stack.popLong()));
                break;
/**
 * cast unsigned uint_64 to unsigned type Byte.
 */
            case lucast_ub:
                stack.pushUnsignedByte(static_cast<uint_8> (stack.popUnsignedLong()));
                break;
/**
 * add int_64 with unsigned type Byte.
 */
            case ladd_ub:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a + b);
            }
                break;
/**
 * add unsigned uint_64 with unsigned type Byte.
 */
            case luadd_ub:
            {
                uint_64 b = stack.popUnsignedLong();
                int_8 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a + b);
            }
                break;
/**
 * subtract int_64 with unsigned type Byte.
 */
            case lsub_ub:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_64 with unsigned type Byte.
 */
            case lusub_ub:
            {
                uint_64 b = stack.popUnsignedLong();
                int_8 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a - b);
            }
                break;
/**
 * multiply int_64 with unsigned type Byte.
 */
            case lmul_ub:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_64 with unsigned type Byte.
 */
            case lumul_ub:
            {
                uint_64 b = stack.popUnsignedLong();
                int_8 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a * b);
            }
                break;
/**
 * divide int_64 with unsigned type Byte.
 */
            case ldiv_ub:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a / b);
            }
                break;
/**
 * divide unsigned uint_64 with unsigned type Byte.
 */
            case ludiv_ub:
            {
                uint_64 b = stack.popUnsignedLong();
                int_8 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a / b);
            }
                break;
/**
 * compare int_64 less than unsigned type Byte.
 */
            case lcmpl_ub:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popUnsignedLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than unsigned type Byte.
 */
            case lucmpl_ub:
            {
                uint_64 b = stack.popUnsignedLong();
                int_8 a = stack.popUnsignedLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than unsigned type Byte.
 */
            case lcmpg_ub:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popUnsignedLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than unsigned type Byte.
 */
            case lucmpg_ub:
            {
                uint_64 b = stack.popUnsignedLong();
                int_8 a = stack.popUnsignedLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 equal with unsigned type Byte.
 */
            case lcmpe_ub:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popUnsignedLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 equal with unsigned type Byte.
 */
            case lucmpe_ub:
            {
                uint_64 b = stack.popUnsignedLong();
                int_8 a = stack.popUnsignedLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 less than or equal to unsigned type Byte.
 */
            case lcmple_ub:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popUnsignedLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than or equal to unsigned type Byte.
 */
            case lucmple_ub:
            {
                uint_64 b = stack.popUnsignedLong();
                int_8 a = stack.popUnsignedLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than or equal to unsigned type Byte.
 */
            case lcmpge_ub:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popUnsignedLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than or equal to unsigned type Byte.
 */
            case lucmpge_ub:
            {
                uint_64 b = stack.popUnsignedLong();
                int_8 a = stack.popUnsignedLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 not equal with unsigned type Byte.
 */
            case lcmpne_ub:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popUnsignedLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 not equal with unsigned type Byte.
 */
            case lucmpne_ub:
            {
                uint_64 b = stack.popUnsignedLong();
                int_8 a = stack.popUnsignedLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_64 with type Short.
 */
            case lmod_s:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a % b);
            }
                break;
/**
 * cast int_64 to unsigned type Short.
 */
            case lcast_us:
                stack.pushUnsignedShort(static_cast<uint_16> (stack.popLong()));
                break;
/**
 * cast unsigned uint_64 to unsigned type Short.
 */
            case lucast_us:
                stack.pushUnsignedShort(static_cast<uint_16> (stack.popUnsignedLong()));
                break;
/**
 * add int_64 with unsigned type Short.
 */
            case ladd_us:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a + b);
            }
                break;
/**
 * add unsigned uint_64 with unsigned type Short.
 */
            case luadd_us:
            {
                uint_64 b = stack.popUnsignedLong();
                int_16 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a + b);
            }
                break;
/**
 * subtract int_64 with unsigned type Short.
 */
            case lsub_us:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_64 with unsigned type Short.
 */
            case lusub_us:
            {
                uint_64 b = stack.popUnsignedLong();
                int_16 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a - b);
            }
                break;
/**
 * multiply int_64 with unsigned type Short.
 */
            case lmul_us:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_64 with unsigned type Short.
 */
            case lumul_us:
            {
                uint_64 b = stack.popUnsignedLong();
                int_16 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a * b);
            }
                break;
/**
 * divide int_64 with unsigned type Short.
 */
            case ldiv_us:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a / b);
            }
                break;
/**
 * divide unsigned uint_64 with unsigned type Short.
 */
            case ludiv_us:
            {
                uint_64 b = stack.popUnsignedLong();
                int_16 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a / b);
            }
                break;
/**
 * compare int_64 less than unsigned type Short.
 */
            case lcmpl_us:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popUnsignedLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than unsigned type Short.
 */
            case lucmpl_us:
            {
                uint_64 b = stack.popUnsignedLong();
                int_16 a = stack.popUnsignedLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than unsigned type Short.
 */
            case lcmpg_us:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popUnsignedLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than unsigned type Short.
 */
            case lucmpg_us:
            {
                uint_64 b = stack.popUnsignedLong();
                int_16 a = stack.popUnsignedLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 equal with unsigned type Short.
 */
            case lcmpe_us:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popUnsignedLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 equal with unsigned type Short.
 */
            case lucmpe_us:
            {
                uint_64 b = stack.popUnsignedLong();
                int_16 a = stack.popUnsignedLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 less than or equal to unsigned type Short.
 */
            case lcmple_us:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popUnsignedLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than or equal to unsigned type Short.
 */
            case lucmple_us:
            {
                uint_64 b = stack.popUnsignedLong();
                int_16 a = stack.popUnsignedLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than or equal to unsigned type Short.
 */
            case lcmpge_us:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popUnsignedLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than or equal to unsigned type Short.
 */
            case lucmpge_us:
            {
                uint_64 b = stack.popUnsignedLong();
                int_16 a = stack.popUnsignedLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 not equal with unsigned type Short.
 */
            case lcmpne_us:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popUnsignedLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 not equal with unsigned type Short.
 */
            case lucmpne_us:
            {
                uint_64 b = stack.popUnsignedLong();
                int_16 a = stack.popUnsignedLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_64 with type Int.
 */
            case lmod_i:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a % b);
            }
                break;
/**
 * cast int_64 to unsigned type Int.
 */
            case lcast_ui:
                stack.pushUnsignedInt(static_cast<uint_32> (stack.popLong()));
                break;
/**
 * cast unsigned uint_64 to unsigned type Int.
 */
            case lucast_ui:
                stack.pushUnsignedInt(static_cast<uint_32> (stack.popUnsignedLong()));
                break;
/**
 * add int_64 with unsigned type Int.
 */
            case ladd_ui:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a + b);
            }
                break;
/**
 * add unsigned uint_64 with unsigned type Int.
 */
            case luadd_ui:
            {
                uint_64 b = stack.popUnsignedLong();
                int_32 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a + b);
            }
                break;
/**
 * subtract int_64 with unsigned type Int.
 */
            case lsub_ui:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_64 with unsigned type Int.
 */
            case lusub_ui:
            {
                uint_64 b = stack.popUnsignedLong();
                int_32 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a - b);
            }
                break;
/**
 * multiply int_64 with unsigned type Int.
 */
            case lmul_ui:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_64 with unsigned type Int.
 */
            case lumul_ui:
            {
                uint_64 b = stack.popUnsignedLong();
                int_32 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a * b);
            }
                break;
/**
 * divide int_64 with unsigned type Int.
 */
            case ldiv_ui:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a / b);
            }
                break;
/**
 * divide unsigned uint_64 with unsigned type Int.
 */
            case ludiv_ui:
            {
                uint_64 b = stack.popUnsignedLong();
                int_32 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a / b);
            }
                break;
/**
 * compare int_64 less than unsigned type Int.
 */
            case lcmpl_ui:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popUnsignedLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than unsigned type Int.
 */
            case lucmpl_ui:
            {
                uint_64 b = stack.popUnsignedLong();
                int_32 a = stack.popUnsignedLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than unsigned type Int.
 */
            case lcmpg_ui:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popUnsignedLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than unsigned type Int.
 */
            case lucmpg_ui:
            {
                uint_64 b = stack.popUnsignedLong();
                int_32 a = stack.popUnsignedLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 equal with unsigned type Int.
 */
            case lcmpe_ui:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popUnsignedLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 equal with unsigned type Int.
 */
            case lucmpe_ui:
            {
                uint_64 b = stack.popUnsignedLong();
                int_32 a = stack.popUnsignedLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 less than or equal to unsigned type Int.
 */
            case lcmple_ui:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popUnsignedLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than or equal to unsigned type Int.
 */
            case lucmple_ui:
            {
                uint_64 b = stack.popUnsignedLong();
                int_32 a = stack.popUnsignedLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than or equal to unsigned type Int.
 */
            case lcmpge_ui:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popUnsignedLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than or equal to unsigned type Int.
 */
            case lucmpge_ui:
            {
                uint_64 b = stack.popUnsignedLong();
                int_32 a = stack.popUnsignedLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 not equal with unsigned type Int.
 */
            case lcmpne_ui:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popUnsignedLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 not equal with unsigned type Int.
 */
            case lucmpne_ui:
            {
                uint_64 b = stack.popUnsignedLong();
                int_32 a = stack.popUnsignedLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_64 with type Long.
 */
            case lmod_l:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a % b);
            }
                break;
/**
 * cast int_64 to unsigned type Long.
 */
            case lcast_ul:
                stack.pushUnsignedLong(static_cast<uint_64> (stack.popLong()));
                break;
/**
 * cast unsigned uint_64 to unsigned type Long.
 */
            case lucast_ul:
                stack.pushUnsignedLong(static_cast<uint_64> (stack.popUnsignedLong()));
                break;
/**
 * add int_64 with unsigned type Long.
 */
            case ladd_ul:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a + b);
            }
                break;
/**
 * add unsigned uint_64 with unsigned type Long.
 */
            case luadd_ul:
            {
                uint_64 b = stack.popUnsignedLong();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a + b);
            }
                break;
/**
 * subtract int_64 with unsigned type Long.
 */
            case lsub_ul:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_64 with unsigned type Long.
 */
            case lusub_ul:
            {
                uint_64 b = stack.popUnsignedLong();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a - b);
            }
                break;
/**
 * multiply int_64 with unsigned type Long.
 */
            case lmul_ul:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_64 with unsigned type Long.
 */
            case lumul_ul:
            {
                uint_64 b = stack.popUnsignedLong();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a * b);
            }
                break;
/**
 * divide int_64 with unsigned type Long.
 */
            case ldiv_ul:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a / b);
            }
                break;
/**
 * divide unsigned uint_64 with unsigned type Long.
 */
            case ludiv_ul:
            {
                uint_64 b = stack.popUnsignedLong();
                int_64 a = stack.popUnsignedLong();
                stack.pushUnsignedLong(a / b);
            }
                break;
/**
 * compare int_64 less than unsigned type Long.
 */
            case lcmpl_ul:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than unsigned type Long.
 */
            case lucmpl_ul:
            {
                uint_64 b = stack.popUnsignedLong();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than unsigned type Long.
 */
            case lcmpg_ul:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than unsigned type Long.
 */
            case lucmpg_ul:
            {
                uint_64 b = stack.popUnsignedLong();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 equal with unsigned type Long.
 */
            case lcmpe_ul:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 equal with unsigned type Long.
 */
            case lucmpe_ul:
            {
                uint_64 b = stack.popUnsignedLong();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 less than or equal to unsigned type Long.
 */
            case lcmple_ul:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than or equal to unsigned type Long.
 */
            case lucmple_ul:
            {
                uint_64 b = stack.popUnsignedLong();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than or equal to unsigned type Long.
 */
            case lcmpge_ul:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than or equal to unsigned type Long.
 */
            case lucmpge_ul:
            {
                uint_64 b = stack.popUnsignedLong();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 not equal with unsigned type Long.
 */
            case lcmpne_ul:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 not equal with unsigned type Long.
 */
            case lucmpne_ul:
            {
                uint_64 b = stack.popUnsignedLong();
                int_64 a = stack.popUnsignedLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_64 with type LongInt.
 */
            case lmod_li:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a % b);
            }
                break;
/**
 * cast int_64 to unsigned type LongInt.
 */
            case lcast_uli:
                stack.pushUnsignedLongInt(static_cast<uint_128> (stack.popLong()));
                break;
/**
 * cast unsigned uint_64 to unsigned type LongInt.
 */
            case lucast_uli:
                stack.pushUnsignedLongInt(static_cast<uint_128> (stack.popUnsignedLong()));
                break;
/**
 * add int_64 with unsigned type LongInt.
 */
            case ladd_uli:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a + b);
            }
                break;
/**
 * add unsigned uint_64 with unsigned type LongInt.
 */
            case luadd_uli:
            {
                uint_64 b = stack.popUnsignedLong();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a + b);
            }
                break;
/**
 * subtract int_64 with unsigned type LongInt.
 */
            case lsub_uli:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_64 with unsigned type LongInt.
 */
            case lusub_uli:
            {
                uint_64 b = stack.popUnsignedLong();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a - b);
            }
                break;
/**
 * multiply int_64 with unsigned type LongInt.
 */
            case lmul_uli:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_64 with unsigned type LongInt.
 */
            case lumul_uli:
            {
                uint_64 b = stack.popUnsignedLong();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a * b);
            }
                break;
/**
 * divide int_64 with unsigned type LongInt.
 */
            case ldiv_uli:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a / b);
            }
                break;
/**
 * divide unsigned uint_64 with unsigned type LongInt.
 */
            case ludiv_uli:
            {
                uint_64 b = stack.popUnsignedLong();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a / b);
            }
                break;
/**
 * compare int_64 less than unsigned type LongInt.
 */
            case lcmpl_uli:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than unsigned type LongInt.
 */
            case lucmpl_uli:
            {
                uint_64 b = stack.popUnsignedLong();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than unsigned type LongInt.
 */
            case lcmpg_uli:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than unsigned type LongInt.
 */
            case lucmpg_uli:
            {
                uint_64 b = stack.popUnsignedLong();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 equal with unsigned type LongInt.
 */
            case lcmpe_uli:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 equal with unsigned type LongInt.
 */
            case lucmpe_uli:
            {
                uint_64 b = stack.popUnsignedLong();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 less than or equal to unsigned type LongInt.
 */
            case lcmple_uli:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than or equal to unsigned type LongInt.
 */
            case lucmple_uli:
            {
                uint_64 b = stack.popUnsignedLong();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than or equal to unsigned type LongInt.
 */
            case lcmpge_uli:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than or equal to unsigned type LongInt.
 */
            case lucmpge_uli:
            {
                uint_64 b = stack.popUnsignedLong();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 not equal with unsigned type LongInt.
 */
            case lcmpne_uli:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 not equal with unsigned type LongInt.
 */
            case lucmpne_uli:
            {
                uint_64 b = stack.popUnsignedLong();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_64 with type LongLong.
 */
            case lmod_ll:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a % b);
            }
                break;
/**
 * cast int_64 to unsigned type LongLong.
 */
            case lcast_ull:
                stack.pushUnsignedLongLong(static_cast<uint_256> (stack.popLong()));
                break;
/**
 * cast unsigned uint_64 to unsigned type LongLong.
 */
            case lucast_ull:
                stack.pushUnsignedLongLong(static_cast<uint_256> (stack.popUnsignedLong()));
                break;
/**
 * add int_64 with unsigned type LongLong.
 */
            case ladd_ull:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_64 with unsigned type LongLong.
 */
            case luadd_ull:
            {
                uint_64 b = stack.popUnsignedLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a + b);
            }
                break;
/**
 * subtract int_64 with unsigned type LongLong.
 */
            case lsub_ull:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_64 with unsigned type LongLong.
 */
            case lusub_ull:
            {
                uint_64 b = stack.popUnsignedLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a - b);
            }
                break;
/**
 * multiply int_64 with unsigned type LongLong.
 */
            case lmul_ull:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_64 with unsigned type LongLong.
 */
            case lumul_ull:
            {
                uint_64 b = stack.popUnsignedLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a * b);
            }
                break;
/**
 * divide int_64 with unsigned type LongLong.
 */
            case ldiv_ull:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_64 with unsigned type LongLong.
 */
            case ludiv_ull:
            {
                uint_64 b = stack.popUnsignedLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a / b);
            }
                break;
/**
 * compare int_64 less than unsigned type LongLong.
 */
            case lcmpl_ull:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than unsigned type LongLong.
 */
            case lucmpl_ull:
            {
                uint_64 b = stack.popUnsignedLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than unsigned type LongLong.
 */
            case lcmpg_ull:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than unsigned type LongLong.
 */
            case lucmpg_ull:
            {
                uint_64 b = stack.popUnsignedLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 equal with unsigned type LongLong.
 */
            case lcmpe_ull:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 equal with unsigned type LongLong.
 */
            case lucmpe_ull:
            {
                uint_64 b = stack.popUnsignedLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 less than or equal to unsigned type LongLong.
 */
            case lcmple_ull:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 less than or equal to unsigned type LongLong.
 */
            case lucmple_ull:
            {
                uint_64 b = stack.popUnsignedLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 greater than or equal to unsigned type LongLong.
 */
            case lcmpge_ull:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 greater than or equal to unsigned type LongLong.
 */
            case lucmpge_ull:
            {
                uint_64 b = stack.popUnsignedLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_64 not equal with unsigned type LongLong.
 */
            case lcmpne_ull:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_64 not equal with unsigned type LongLong.
 */
            case lucmpne_ull:
            {
                uint_64 b = stack.popUnsignedLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * bitwise and int_64 with type Byte.
 */
            case land_b:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popByte();
                stack.pushLong(a & b);
            }
                break;
/**
 * bitwise or int_64 with type Byte.
 */
            case lor_b:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popByte();
                stack.pushLong(a | b);
            }
                break;
/**
 * bitwise xor int_64 with type Byte.
 */
            case lxor_b:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popByte();
                stack.pushLong(a ^ b);
            }
                break;
/**
 * shift right int_64 with type Byte.
 */
            case lshftr_b:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popByte();
                stack.pushLong(a >> b);
            }
                break;
/**
 * shift left xor int_64 with type Byte.
 */
            case lshftl_b:
            {
                int_64 b = stack.popLong();
                int_8 a = stack.popByte();
                stack.pushLong(a << b);
            }
                break;
/**
 * bitwise and int_64 with type Short.
 */
            case land_s:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popShort();
                stack.pushLong(a & b);
            }
                break;
/**
 * bitwise or int_64 with type Short.
 */
            case lor_s:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popShort();
                stack.pushLong(a | b);
            }
                break;
/**
 * bitwise xor int_64 with type Short.
 */
            case lxor_s:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popShort();
                stack.pushLong(a ^ b);
            }
                break;
/**
 * shift right int_64 with type Short.
 */
            case lshftr_s:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popShort();
                stack.pushLong(a >> b);
            }
                break;
/**
 * shift left xor int_64 with type Short.
 */
            case lshftl_s:
            {
                int_64 b = stack.popLong();
                int_16 a = stack.popShort();
                stack.pushLong(a << b);
            }
                break;
/**
 * bitwise and int_64 with type Int.
 */
            case land_i:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popInt();
                stack.pushLong(a & b);
            }
                break;
/**
 * bitwise or int_64 with type Int.
 */
            case lor_i:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popInt();
                stack.pushLong(a | b);
            }
                break;
/**
 * bitwise xor int_64 with type Int.
 */
            case lxor_i:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popInt();
                stack.pushLong(a ^ b);
            }
                break;
/**
 * shift right int_64 with type Int.
 */
            case lshftr_i:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popInt();
                stack.pushLong(a >> b);
            }
                break;
/**
 * shift left xor int_64 with type Int.
 */
            case lshftl_i:
            {
                int_64 b = stack.popLong();
                int_32 a = stack.popInt();
                stack.pushLong(a << b);
            }
                break;
/**
 * bitwise and int_64 with type Long.
 */
            case land_l:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popLong();
                stack.pushLong(a & b);
            }
                break;
/**
 * bitwise or int_64 with type Long.
 */
            case lor_l:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popLong();
                stack.pushLong(a | b);
            }
                break;
/**
 * bitwise xor int_64 with type Long.
 */
            case lxor_l:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popLong();
                stack.pushLong(a ^ b);
            }
                break;
/**
 * shift right int_64 with type Long.
 */
            case lshftr_l:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popLong();
                stack.pushLong(a >> b);
            }
                break;
/**
 * shift left xor int_64 with type Long.
 */
            case lshftl_l:
            {
                int_64 b = stack.popLong();
                int_64 a = stack.popLong();
                stack.pushLong(a << b);
            }
                break;
/**
 * bitwise and int_64 with type LongInt.
 */
            case land_li:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a & b);
            }
                break;
/**
 * bitwise or int_64 with type LongInt.
 */
            case lor_li:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a | b);
            }
                break;
/**
 * bitwise xor int_64 with type LongInt.
 */
            case lxor_li:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a ^ b);
            }
                break;
/**
 * shift right int_64 with type LongInt.
 */
            case lshftr_li:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a >> b);
            }
                break;
/**
 * shift left xor int_64 with type LongInt.
 */
            case lshftl_li:
            {
                int_64 b = stack.popLong();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a << b);
            }
                break;
/**
 * bitwise and int_64 with type LongLong.
 */
            case land_ll:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a & b);
            }
                break;
/**
 * bitwise or int_64 with type LongLong.
 */
            case lor_ll:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a | b);
            }
                break;
/**
 * bitwise xor int_64 with type LongLong.
 */
            case lxor_ll:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a ^ b);
            }
                break;
/**
 * shift right int_64 with type LongLong.
 */
            case lshftr_ll:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a >> b);
            }
                break;
/**
 * shift left xor int_64 with type LongLong.
 */
            case lshftl_ll:
            {
                int_64 b = stack.popLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a << b);
            }
                break;
/**
 * duplicate a int_64 on the stack.
 */
            case ldup:
                stack.pushLong(stack.peekLong());
                break;
/**
 * duplicate a int_64 2 times on the stack.
 */
            case ldup2:
                stack.pushLong(stack.peekLong());stack.pushLong(stack.peekLong());
                break;
/**
 * duplicate a int_64 3 times on the stack.
 */
            case ldup3:
                stack.pushLong(stack.peekLong());stack.pushLong(stack.peekLong());stack.pushLong(stack.peekLong());
                break;
/**
 * duplicate a int_64 4 times on the stack.
 */
            case ldup4:
                stack.pushLong(stack.peekLong());stack.pushLong(stack.peekLong());stack.pushLong(stack.peekLong());stack.pushLong(stack.peekLong());
                break;
/**
 * duplicate a int_64 5 times on the stack.
 */
            case ldup5:
                stack.pushLong(stack.peekLong());stack.pushLong(stack.peekLong());stack.pushLong(stack.peekLong());stack.pushLong(stack.peekLong());stack.pushLong(stack.peekLong());
                break;
/**
 * set a int_64 from stack into a field on base pointer.
 */
            case lset:
                accessMemoryAndSetLong(base, ops.getUnsignedInt(), stack.popLong());
                break;
/**
 * get a int_64 from a field on base pointer to stack.
 */
            case lget:
                stack.pushLong(accessMemoryAndGetLong(base, ops.getUnsignedInt()));
                break;
/**
 * set a int_64 from value into a field on base pointer.
 */
            case lvset:
                accessMemoryAndSetLong(base, ops.getUnsignedInt(), ops.getLong());
                break;
/**
 * get a int_64 from a field on base pointer to stack using address from stack.
 */
            case lsget:
                stack.pushLong(accessMemoryAndGetLong(base, stack.popUnsignedInt()));
                break;
/**
 * set a int_64 from stack into a field on base pointer using address from stack.
 */
            case lsset:
                accessMemoryAndSetLong(base, stack.popUnsignedInt(), stack.popLong());
                break;
/**
 * set a int_64 from local variable into a field on base pointer.
 */
            case lsetl:
                accessMemoryAndSetLong(base, ops.getUnsignedInt(), lvt[ops.getUnsignedShort()].Long);
                break;
/**
 * increment int_64 by 1 on stack.
 */
            case linc_1:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].Long = lvt[point].Long + 1; }
                break;
/**
 * increment int_64 by 2 on stack.
 */
            case linc_2:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].Long = lvt[point].Long + 2; }
                break;
/**
 * increment int_64 by 1 on stack.
 */
            case lstinc_1:
                stack.pushLong(stack.popLong() + 1);
                break;
/**
 * increment int_64 by 2 on stack.
 */
            case lstinc_2:
                stack.pushLong(stack.popLong() + 2);
                break;
/**
 * return a int_64 into the main stack.
 */
            case lreturn:
                stack_main.pushLong(stack.popLong());
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
                log(std::to_string(stack.popLong()));
                break;
/**
 * print a unsigned uint_64 from stack.
 */
            case luprint:
                log(std::to_string(stack.popUnsignedLong()));
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
 * push a const int_128 into the stack (value = 1).
 */
            case liconst_1:
                stack.pushLongInt(1);
                break;
/**
 * push a const int_128 into the stack (value = 2).
 */
            case liconst_2:
                stack.pushLongInt(2);
                break;
/**
 * push a const int_128 into the stack (value = 3).
 */
            case liconst_3:
                stack.pushLongInt(3);
                break;
/**
 * push a const int_128 into the stack (value = 4).
 */
            case liconst_4:
                stack.pushLongInt(4);
                break;
/**
 * push a const int_128 into the stack (value = 5).
 */
            case liconst_5:
                stack.pushLongInt(5);
                break;
/**
 * push a const int_128 into the stack (value = 6).
 */
            case liconst_6:
                stack.pushLongInt(6);
                break;
/**
 * push a const int_128 into the stack (value = 9).
 */
            case liconst_9:
                stack.pushLongInt(9);
                break;
/**
 * push a const int_128 into the stack (value = 10).
 */
            case liconst_10:
                stack.pushLongInt(10);
                break;
/**
 * push a const int_128 into the stack (value = 11).
 */
            case liconst_11:
                stack.pushLongInt(11);
                break;
/**
 * push a const int_128 into the stack (value = 12).
 */
            case liconst_12:
                stack.pushLongInt(12);
                break;
/**
 * load a int_128 into the stack from local variable.
 */
            case liload:
                stack.pushLongInt(lvt[ops.getUnsignedShort()].LongInt);
                break;
/**
 * load a int_128 into the stack from local variable 0.
 */
            case liload_0:
                stack.pushLongInt(lvt[0].LongInt);
                break;
/**
 * load a int_128 into the stack from local variable 1.
 */
            case liload_1:
                stack.pushLongInt(lvt[1].LongInt);
                break;
/**
 * load a int_128 into the stack from local variable 2.
 */
            case liload_2:
                stack.pushLongInt(lvt[2].LongInt);
                break;
/**
 * load a int_128 into the stack from local variable 3.
 */
            case liload_3:
                stack.pushLongInt(lvt[3].LongInt);
                break;
/**
 * load a int_128 into the stack from local variable 4.
 */
            case liload_4:
                stack.pushLongInt(lvt[4].LongInt);
                break;
/**
 * store a int_128 from stack into local variable.
 */
            case listore:
                lvt[ops.getUnsignedShort()] = lve_LongInt(stack.popLongInt());
                break;
/**
 * store a int_128 from stack into local variable 0.
 */
            case listore_0:
                lvt[0] = lve_LongInt(stack.popLongInt());
                break;
/**
 * store a int_128 from stack into local variable 1.
 */
            case listore_1:
                lvt[1] = lve_LongInt(stack.popLongInt());
                break;
/**
 * store a int_128 from stack into local variable 2.
 */
            case listore_2:
                lvt[2] = lve_LongInt(stack.popLongInt());
                break;
/**
 * store a int_128 from stack into local variable 3.
 */
            case listore_3:
                lvt[3] = lve_LongInt(stack.popLongInt());
                break;
/**
 * store a int_128 from stack into local variable 4.
 */
            case listore_4:
                lvt[4] = lve_LongInt(stack.popLongInt());
                break;
/**
 * cast int_128 to type Byte.
 */
            case licast_b:
                stack.pushByte(static_cast<int_8> (stack.popLongInt()));
                break;
/**
 * cast unsigned uint_128 to type Byte.
 */
            case liucast_b:
                stack.pushByte(static_cast<int_8> (stack.popUnsignedLongInt()));
                break;
/**
 * add int_128 with type Byte.
 */
            case liadd_b:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popByte();
                stack.pushLongInt(a + b);
            }
                break;
/**
 * add unsigned uint_128 with type Byte.
 */
            case liuadd_b:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_8 a = stack.popByte();
                stack.pushLongInt(a + b);
            }
                break;
/**
 * subtract int_128 with type Byte.
 */
            case lisub_b:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popByte();
                stack.pushLongInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_128 with type Byte.
 */
            case liusub_b:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_8 a = stack.popByte();
                stack.pushLongInt(a - b);
            }
                break;
/**
 * multiply int_128 with type Byte.
 */
            case limul_b:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popByte();
                stack.pushLongInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_128 with type Byte.
 */
            case liumul_b:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_8 a = stack.popByte();
                stack.pushLongInt(a * b);
            }
                break;
/**
 * divide int_128 with type Byte.
 */
            case lidiv_b:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popByte();
                stack.pushLongInt(a / b);
            }
                break;
/**
 * divide unsigned uint_128 with type Byte.
 */
            case liudiv_b:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_8 a = stack.popByte();
                stack.pushLongInt(a / b);
            }
                break;
/**
 * compare int_128 less than type Byte.
 */
            case licmpl_b:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popByte();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than type Byte.
 */
            case liucmpl_b:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_8 a = stack.popByte();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than type Byte.
 */
            case licmpg_b:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popByte();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than type Byte.
 */
            case liucmpg_b:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_8 a = stack.popByte();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 equal with type Byte.
 */
            case licmpe_b:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popByte();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 equal with type Byte.
 */
            case liucmpe_b:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_8 a = stack.popByte();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 less than or equal to type Byte.
 */
            case licmple_b:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popByte();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than or equal to type Byte.
 */
            case liucmple_b:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_8 a = stack.popByte();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than or equal to type Byte.
 */
            case licmpge_b:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popByte();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than or equal to type Byte.
 */
            case liucmpge_b:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_8 a = stack.popByte();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 not equal with type Byte.
 */
            case licmpne_b:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popByte();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 not equal with type Byte.
 */
            case liucmpne_b:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_8 a = stack.popByte();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_128 to type Short.
 */
            case licast_s:
                stack.pushShort(static_cast<int_16> (stack.popLongInt()));
                break;
/**
 * cast unsigned uint_128 to type Short.
 */
            case liucast_s:
                stack.pushShort(static_cast<int_16> (stack.popUnsignedLongInt()));
                break;
/**
 * add int_128 with type Short.
 */
            case liadd_s:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popShort();
                stack.pushLongInt(a + b);
            }
                break;
/**
 * add unsigned uint_128 with type Short.
 */
            case liuadd_s:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_16 a = stack.popShort();
                stack.pushLongInt(a + b);
            }
                break;
/**
 * subtract int_128 with type Short.
 */
            case lisub_s:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popShort();
                stack.pushLongInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_128 with type Short.
 */
            case liusub_s:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_16 a = stack.popShort();
                stack.pushLongInt(a - b);
            }
                break;
/**
 * multiply int_128 with type Short.
 */
            case limul_s:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popShort();
                stack.pushLongInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_128 with type Short.
 */
            case liumul_s:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_16 a = stack.popShort();
                stack.pushLongInt(a * b);
            }
                break;
/**
 * divide int_128 with type Short.
 */
            case lidiv_s:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popShort();
                stack.pushLongInt(a / b);
            }
                break;
/**
 * divide unsigned uint_128 with type Short.
 */
            case liudiv_s:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_16 a = stack.popShort();
                stack.pushLongInt(a / b);
            }
                break;
/**
 * compare int_128 less than type Short.
 */
            case licmpl_s:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popShort();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than type Short.
 */
            case liucmpl_s:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_16 a = stack.popShort();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than type Short.
 */
            case licmpg_s:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popShort();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than type Short.
 */
            case liucmpg_s:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_16 a = stack.popShort();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 equal with type Short.
 */
            case licmpe_s:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popShort();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 equal with type Short.
 */
            case liucmpe_s:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_16 a = stack.popShort();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 less than or equal to type Short.
 */
            case licmple_s:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popShort();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than or equal to type Short.
 */
            case liucmple_s:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_16 a = stack.popShort();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than or equal to type Short.
 */
            case licmpge_s:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popShort();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than or equal to type Short.
 */
            case liucmpge_s:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_16 a = stack.popShort();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 not equal with type Short.
 */
            case licmpne_s:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popShort();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 not equal with type Short.
 */
            case liucmpne_s:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_16 a = stack.popShort();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_128 to type Int.
 */
            case licast_i:
                stack.pushInt(static_cast<int_32> (stack.popLongInt()));
                break;
/**
 * cast unsigned uint_128 to type Int.
 */
            case liucast_i:
                stack.pushInt(static_cast<int_32> (stack.popUnsignedLongInt()));
                break;
/**
 * add int_128 with type Int.
 */
            case liadd_i:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popInt();
                stack.pushLongInt(a + b);
            }
                break;
/**
 * add unsigned uint_128 with type Int.
 */
            case liuadd_i:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_32 a = stack.popInt();
                stack.pushLongInt(a + b);
            }
                break;
/**
 * subtract int_128 with type Int.
 */
            case lisub_i:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popInt();
                stack.pushLongInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_128 with type Int.
 */
            case liusub_i:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_32 a = stack.popInt();
                stack.pushLongInt(a - b);
            }
                break;
/**
 * multiply int_128 with type Int.
 */
            case limul_i:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popInt();
                stack.pushLongInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_128 with type Int.
 */
            case liumul_i:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_32 a = stack.popInt();
                stack.pushLongInt(a * b);
            }
                break;
/**
 * divide int_128 with type Int.
 */
            case lidiv_i:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popInt();
                stack.pushLongInt(a / b);
            }
                break;
/**
 * divide unsigned uint_128 with type Int.
 */
            case liudiv_i:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_32 a = stack.popInt();
                stack.pushLongInt(a / b);
            }
                break;
/**
 * compare int_128 less than type Int.
 */
            case licmpl_i:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than type Int.
 */
            case liucmpl_i:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_32 a = stack.popInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than type Int.
 */
            case licmpg_i:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than type Int.
 */
            case liucmpg_i:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_32 a = stack.popInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 equal with type Int.
 */
            case licmpe_i:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 equal with type Int.
 */
            case liucmpe_i:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_32 a = stack.popInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 less than or equal to type Int.
 */
            case licmple_i:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than or equal to type Int.
 */
            case liucmple_i:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_32 a = stack.popInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than or equal to type Int.
 */
            case licmpge_i:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than or equal to type Int.
 */
            case liucmpge_i:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_32 a = stack.popInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 not equal with type Int.
 */
            case licmpne_i:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 not equal with type Int.
 */
            case liucmpne_i:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_32 a = stack.popInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_128 to type Long.
 */
            case licast_l:
                stack.pushLong(static_cast<int_64> (stack.popLongInt()));
                break;
/**
 * cast unsigned uint_128 to type Long.
 */
            case liucast_l:
                stack.pushLong(static_cast<int_64> (stack.popUnsignedLongInt()));
                break;
/**
 * add int_128 with type Long.
 */
            case liadd_l:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popLong();
                stack.pushLongInt(a + b);
            }
                break;
/**
 * add unsigned uint_128 with type Long.
 */
            case liuadd_l:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_64 a = stack.popLong();
                stack.pushLongInt(a + b);
            }
                break;
/**
 * subtract int_128 with type Long.
 */
            case lisub_l:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popLong();
                stack.pushLongInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_128 with type Long.
 */
            case liusub_l:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_64 a = stack.popLong();
                stack.pushLongInt(a - b);
            }
                break;
/**
 * multiply int_128 with type Long.
 */
            case limul_l:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popLong();
                stack.pushLongInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_128 with type Long.
 */
            case liumul_l:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_64 a = stack.popLong();
                stack.pushLongInt(a * b);
            }
                break;
/**
 * divide int_128 with type Long.
 */
            case lidiv_l:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popLong();
                stack.pushLongInt(a / b);
            }
                break;
/**
 * divide unsigned uint_128 with type Long.
 */
            case liudiv_l:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_64 a = stack.popLong();
                stack.pushLongInt(a / b);
            }
                break;
/**
 * compare int_128 less than type Long.
 */
            case licmpl_l:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than type Long.
 */
            case liucmpl_l:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_64 a = stack.popLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than type Long.
 */
            case licmpg_l:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than type Long.
 */
            case liucmpg_l:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_64 a = stack.popLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 equal with type Long.
 */
            case licmpe_l:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 equal with type Long.
 */
            case liucmpe_l:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_64 a = stack.popLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 less than or equal to type Long.
 */
            case licmple_l:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than or equal to type Long.
 */
            case liucmple_l:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_64 a = stack.popLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than or equal to type Long.
 */
            case licmpge_l:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than or equal to type Long.
 */
            case liucmpge_l:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_64 a = stack.popLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 not equal with type Long.
 */
            case licmpne_l:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 not equal with type Long.
 */
            case liucmpne_l:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_64 a = stack.popLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_128 to type LongInt.
 */
            case licast_li:
                stack.pushLongInt(static_cast<int_128> (stack.popLongInt()));
                break;
/**
 * cast unsigned uint_128 to type LongInt.
 */
            case liucast_li:
                stack.pushLongInt(static_cast<int_128> (stack.popUnsignedLongInt()));
                break;
/**
 * add int_128 with type LongInt.
 */
            case liadd_li:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a + b);
            }
                break;
/**
 * add unsigned uint_128 with type LongInt.
 */
            case liuadd_li:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a + b);
            }
                break;
/**
 * subtract int_128 with type LongInt.
 */
            case lisub_li:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_128 with type LongInt.
 */
            case liusub_li:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a - b);
            }
                break;
/**
 * multiply int_128 with type LongInt.
 */
            case limul_li:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_128 with type LongInt.
 */
            case liumul_li:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a * b);
            }
                break;
/**
 * divide int_128 with type LongInt.
 */
            case lidiv_li:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a / b);
            }
                break;
/**
 * divide unsigned uint_128 with type LongInt.
 */
            case liudiv_li:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a / b);
            }
                break;
/**
 * compare int_128 less than type LongInt.
 */
            case licmpl_li:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than type LongInt.
 */
            case liucmpl_li:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_128 a = stack.popLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than type LongInt.
 */
            case licmpg_li:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than type LongInt.
 */
            case liucmpg_li:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_128 a = stack.popLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 equal with type LongInt.
 */
            case licmpe_li:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 equal with type LongInt.
 */
            case liucmpe_li:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_128 a = stack.popLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 less than or equal to type LongInt.
 */
            case licmple_li:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than or equal to type LongInt.
 */
            case liucmple_li:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_128 a = stack.popLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than or equal to type LongInt.
 */
            case licmpge_li:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than or equal to type LongInt.
 */
            case liucmpge_li:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_128 a = stack.popLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 not equal with type LongInt.
 */
            case licmpne_li:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 not equal with type LongInt.
 */
            case liucmpne_li:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_128 a = stack.popLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_128 to type LongLong.
 */
            case licast_ll:
                stack.pushLongLong(static_cast<int_256> (stack.popLongInt()));
                break;
/**
 * cast unsigned uint_128 to type LongLong.
 */
            case liucast_ll:
                stack.pushLongLong(static_cast<int_256> (stack.popUnsignedLongInt()));
                break;
/**
 * add int_128 with type LongLong.
 */
            case liadd_ll:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_128 with type LongLong.
 */
            case liuadd_ll:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * subtract int_128 with type LongLong.
 */
            case lisub_ll:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_128 with type LongLong.
 */
            case liusub_ll:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * multiply int_128 with type LongLong.
 */
            case limul_ll:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_128 with type LongLong.
 */
            case liumul_ll:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * divide int_128 with type LongLong.
 */
            case lidiv_ll:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_128 with type LongLong.
 */
            case liudiv_ll:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * compare int_128 less than type LongLong.
 */
            case licmpl_ll:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than type LongLong.
 */
            case liucmpl_ll:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_256 a = stack.popLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than type LongLong.
 */
            case licmpg_ll:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than type LongLong.
 */
            case liucmpg_ll:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_256 a = stack.popLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 equal with type LongLong.
 */
            case licmpe_ll:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 equal with type LongLong.
 */
            case liucmpe_ll:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_256 a = stack.popLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 less than or equal to type LongLong.
 */
            case licmple_ll:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than or equal to type LongLong.
 */
            case liucmple_ll:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_256 a = stack.popLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than or equal to type LongLong.
 */
            case licmpge_ll:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than or equal to type LongLong.
 */
            case liucmpge_ll:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_256 a = stack.popLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 not equal with type LongLong.
 */
            case licmpne_ll:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 not equal with type LongLong.
 */
            case liucmpne_ll:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_256 a = stack.popLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_128 to type Float.
 */
            case licast_f:
                stack.pushFloat(static_cast<flt_32> (stack.popLongInt()));
                break;
/**
 * cast unsigned uint_128 to type Float.
 */
            case liucast_f:
                stack.pushFloat(static_cast<flt_32> (stack.popUnsignedLongInt()));
                break;
/**
 * add int_128 with type Float.
 */
            case liadd_f:
            {
                int_128 b = stack.popLongInt();
                flt_32 a = stack.popFloat();
                stack.pushLongInt(a + b);
            }
                break;
/**
 * add unsigned uint_128 with type Float.
 */
            case liuadd_f:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_32 a = stack.popFloat();
                stack.pushLongInt(a + b);
            }
                break;
/**
 * subtract int_128 with type Float.
 */
            case lisub_f:
            {
                int_128 b = stack.popLongInt();
                flt_32 a = stack.popFloat();
                stack.pushLongInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_128 with type Float.
 */
            case liusub_f:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_32 a = stack.popFloat();
                stack.pushLongInt(a - b);
            }
                break;
/**
 * multiply int_128 with type Float.
 */
            case limul_f:
            {
                int_128 b = stack.popLongInt();
                flt_32 a = stack.popFloat();
                stack.pushLongInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_128 with type Float.
 */
            case liumul_f:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_32 a = stack.popFloat();
                stack.pushLongInt(a * b);
            }
                break;
/**
 * divide int_128 with type Float.
 */
            case lidiv_f:
            {
                int_128 b = stack.popLongInt();
                flt_32 a = stack.popFloat();
                stack.pushLongInt(a / b);
            }
                break;
/**
 * divide unsigned uint_128 with type Float.
 */
            case liudiv_f:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_32 a = stack.popFloat();
                stack.pushLongInt(a / b);
            }
                break;
/**
 * compare int_128 less than type Float.
 */
            case licmpl_f:
            {
                int_128 b = stack.popLongInt();
                flt_32 a = stack.popFloat();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than type Float.
 */
            case liucmpl_f:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_32 a = stack.popFloat();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than type Float.
 */
            case licmpg_f:
            {
                int_128 b = stack.popLongInt();
                flt_32 a = stack.popFloat();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than type Float.
 */
            case liucmpg_f:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_32 a = stack.popFloat();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 equal with type Float.
 */
            case licmpe_f:
            {
                int_128 b = stack.popLongInt();
                flt_32 a = stack.popFloat();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 equal with type Float.
 */
            case liucmpe_f:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_32 a = stack.popFloat();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 less than or equal to type Float.
 */
            case licmple_f:
            {
                int_128 b = stack.popLongInt();
                flt_32 a = stack.popFloat();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than or equal to type Float.
 */
            case liucmple_f:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_32 a = stack.popFloat();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than or equal to type Float.
 */
            case licmpge_f:
            {
                int_128 b = stack.popLongInt();
                flt_32 a = stack.popFloat();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than or equal to type Float.
 */
            case liucmpge_f:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_32 a = stack.popFloat();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 not equal with type Float.
 */
            case licmpne_f:
            {
                int_128 b = stack.popLongInt();
                flt_32 a = stack.popFloat();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 not equal with type Float.
 */
            case liucmpne_f:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_32 a = stack.popFloat();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_128 to type Double.
 */
            case licast_d:
                stack.pushDouble(static_cast<flt_64> (stack.popLongInt()));
                break;
/**
 * cast unsigned uint_128 to type Double.
 */
            case liucast_d:
                stack.pushDouble(static_cast<flt_64> (stack.popUnsignedLongInt()));
                break;
/**
 * add int_128 with type Double.
 */
            case liadd_d:
            {
                int_128 b = stack.popLongInt();
                flt_64 a = stack.popDouble();
                stack.pushLongInt(a + b);
            }
                break;
/**
 * add unsigned uint_128 with type Double.
 */
            case liuadd_d:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_64 a = stack.popDouble();
                stack.pushLongInt(a + b);
            }
                break;
/**
 * subtract int_128 with type Double.
 */
            case lisub_d:
            {
                int_128 b = stack.popLongInt();
                flt_64 a = stack.popDouble();
                stack.pushLongInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_128 with type Double.
 */
            case liusub_d:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_64 a = stack.popDouble();
                stack.pushLongInt(a - b);
            }
                break;
/**
 * multiply int_128 with type Double.
 */
            case limul_d:
            {
                int_128 b = stack.popLongInt();
                flt_64 a = stack.popDouble();
                stack.pushLongInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_128 with type Double.
 */
            case liumul_d:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_64 a = stack.popDouble();
                stack.pushLongInt(a * b);
            }
                break;
/**
 * divide int_128 with type Double.
 */
            case lidiv_d:
            {
                int_128 b = stack.popLongInt();
                flt_64 a = stack.popDouble();
                stack.pushLongInt(a / b);
            }
                break;
/**
 * divide unsigned uint_128 with type Double.
 */
            case liudiv_d:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_64 a = stack.popDouble();
                stack.pushLongInt(a / b);
            }
                break;
/**
 * compare int_128 less than type Double.
 */
            case licmpl_d:
            {
                int_128 b = stack.popLongInt();
                flt_64 a = stack.popDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than type Double.
 */
            case liucmpl_d:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_64 a = stack.popDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than type Double.
 */
            case licmpg_d:
            {
                int_128 b = stack.popLongInt();
                flt_64 a = stack.popDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than type Double.
 */
            case liucmpg_d:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_64 a = stack.popDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 equal with type Double.
 */
            case licmpe_d:
            {
                int_128 b = stack.popLongInt();
                flt_64 a = stack.popDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 equal with type Double.
 */
            case liucmpe_d:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_64 a = stack.popDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 less than or equal to type Double.
 */
            case licmple_d:
            {
                int_128 b = stack.popLongInt();
                flt_64 a = stack.popDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than or equal to type Double.
 */
            case liucmple_d:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_64 a = stack.popDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than or equal to type Double.
 */
            case licmpge_d:
            {
                int_128 b = stack.popLongInt();
                flt_64 a = stack.popDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than or equal to type Double.
 */
            case liucmpge_d:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_64 a = stack.popDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 not equal with type Double.
 */
            case licmpne_d:
            {
                int_128 b = stack.popLongInt();
                flt_64 a = stack.popDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 not equal with type Double.
 */
            case liucmpne_d:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_64 a = stack.popDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_128 to type DoubleFloat.
 */
            case licast_df:
                stack.pushDoubleFloat(static_cast<flt_128> (stack.popLongInt()));
                break;
/**
 * cast unsigned uint_128 to type DoubleFloat.
 */
            case liucast_df:
                stack.pushDoubleFloat(static_cast<flt_128> (stack.popUnsignedLongInt()));
                break;
/**
 * add int_128 with type DoubleFloat.
 */
            case liadd_df:
            {
                int_128 b = stack.popLongInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushLongInt(a + b);
            }
                break;
/**
 * add unsigned uint_128 with type DoubleFloat.
 */
            case liuadd_df:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushLongInt(a + b);
            }
                break;
/**
 * subtract int_128 with type DoubleFloat.
 */
            case lisub_df:
            {
                int_128 b = stack.popLongInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushLongInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_128 with type DoubleFloat.
 */
            case liusub_df:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushLongInt(a - b);
            }
                break;
/**
 * multiply int_128 with type DoubleFloat.
 */
            case limul_df:
            {
                int_128 b = stack.popLongInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushLongInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_128 with type DoubleFloat.
 */
            case liumul_df:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushLongInt(a * b);
            }
                break;
/**
 * divide int_128 with type DoubleFloat.
 */
            case lidiv_df:
            {
                int_128 b = stack.popLongInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushLongInt(a / b);
            }
                break;
/**
 * divide unsigned uint_128 with type DoubleFloat.
 */
            case liudiv_df:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushLongInt(a / b);
            }
                break;
/**
 * compare int_128 less than type DoubleFloat.
 */
            case licmpl_df:
            {
                int_128 b = stack.popLongInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than type DoubleFloat.
 */
            case liucmpl_df:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than type DoubleFloat.
 */
            case licmpg_df:
            {
                int_128 b = stack.popLongInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than type DoubleFloat.
 */
            case liucmpg_df:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 equal with type DoubleFloat.
 */
            case licmpe_df:
            {
                int_128 b = stack.popLongInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 equal with type DoubleFloat.
 */
            case liucmpe_df:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 less than or equal to type DoubleFloat.
 */
            case licmple_df:
            {
                int_128 b = stack.popLongInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than or equal to type DoubleFloat.
 */
            case liucmple_df:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than or equal to type DoubleFloat.
 */
            case licmpge_df:
            {
                int_128 b = stack.popLongInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than or equal to type DoubleFloat.
 */
            case liucmpge_df:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 not equal with type DoubleFloat.
 */
            case licmpne_df:
            {
                int_128 b = stack.popLongInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 not equal with type DoubleFloat.
 */
            case liucmpne_df:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_128 to type DoubleDouble.
 */
            case licast_dd:
                stack.pushDoubleDouble(static_cast<flt_256> (stack.popLongInt()));
                break;
/**
 * cast unsigned uint_128 to type DoubleDouble.
 */
            case liucast_dd:
                stack.pushDoubleDouble(static_cast<flt_256> (stack.popUnsignedLongInt()));
                break;
/**
 * add int_128 with type DoubleDouble.
 */
            case liadd_dd:
            {
                int_128 b = stack.popLongInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a + b);
            }
                break;
/**
 * add unsigned uint_128 with type DoubleDouble.
 */
            case liuadd_dd:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a + b);
            }
                break;
/**
 * subtract int_128 with type DoubleDouble.
 */
            case lisub_dd:
            {
                int_128 b = stack.popLongInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a - b);
            }
                break;
/**
 * subtract unsigned uint_128 with type DoubleDouble.
 */
            case liusub_dd:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a - b);
            }
                break;
/**
 * multiply int_128 with type DoubleDouble.
 */
            case limul_dd:
            {
                int_128 b = stack.popLongInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a * b);
            }
                break;
/**
 * multiply unsigned uint_128 with type DoubleDouble.
 */
            case liumul_dd:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a * b);
            }
                break;
/**
 * divide int_128 with type DoubleDouble.
 */
            case lidiv_dd:
            {
                int_128 b = stack.popLongInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a / b);
            }
                break;
/**
 * divide unsigned uint_128 with type DoubleDouble.
 */
            case liudiv_dd:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushDoubleDouble(a / b);
            }
                break;
/**
 * compare int_128 less than type DoubleDouble.
 */
            case licmpl_dd:
            {
                int_128 b = stack.popLongInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than type DoubleDouble.
 */
            case liucmpl_dd:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than type DoubleDouble.
 */
            case licmpg_dd:
            {
                int_128 b = stack.popLongInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than type DoubleDouble.
 */
            case liucmpg_dd:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 equal with type DoubleDouble.
 */
            case licmpe_dd:
            {
                int_128 b = stack.popLongInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 equal with type DoubleDouble.
 */
            case liucmpe_dd:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 less than or equal to type DoubleDouble.
 */
            case licmple_dd:
            {
                int_128 b = stack.popLongInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than or equal to type DoubleDouble.
 */
            case liucmple_dd:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than or equal to type DoubleDouble.
 */
            case licmpge_dd:
            {
                int_128 b = stack.popLongInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than or equal to type DoubleDouble.
 */
            case liucmpge_dd:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 not equal with type DoubleDouble.
 */
            case licmpne_dd:
            {
                int_128 b = stack.popLongInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 not equal with type DoubleDouble.
 */
            case liucmpne_dd:
            {
                uint_128 b = stack.popUnsignedLongInt();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_128 with type Byte.
 */
            case limod_b:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a % b);
            }
                break;
/**
 * cast int_128 to unsigned type Byte.
 */
            case licast_ub:
                stack.pushUnsignedByte(static_cast<uint_8> (stack.popLongInt()));
                break;
/**
 * cast unsigned uint_128 to unsigned type Byte.
 */
            case liucast_ub:
                stack.pushUnsignedByte(static_cast<uint_8> (stack.popUnsignedLongInt()));
                break;
/**
 * add int_128 with unsigned type Byte.
 */
            case liadd_ub:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a + b);
            }
                break;
/**
 * add unsigned uint_128 with unsigned type Byte.
 */
            case liuadd_ub:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_8 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a + b);
            }
                break;
/**
 * subtract int_128 with unsigned type Byte.
 */
            case lisub_ub:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_128 with unsigned type Byte.
 */
            case liusub_ub:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_8 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a - b);
            }
                break;
/**
 * multiply int_128 with unsigned type Byte.
 */
            case limul_ub:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_128 with unsigned type Byte.
 */
            case liumul_ub:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_8 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a * b);
            }
                break;
/**
 * divide int_128 with unsigned type Byte.
 */
            case lidiv_ub:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a / b);
            }
                break;
/**
 * divide unsigned uint_128 with unsigned type Byte.
 */
            case liudiv_ub:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_8 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a / b);
            }
                break;
/**
 * compare int_128 less than unsigned type Byte.
 */
            case licmpl_ub:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popUnsignedLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than unsigned type Byte.
 */
            case liucmpl_ub:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_8 a = stack.popUnsignedLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than unsigned type Byte.
 */
            case licmpg_ub:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popUnsignedLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than unsigned type Byte.
 */
            case liucmpg_ub:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_8 a = stack.popUnsignedLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 equal with unsigned type Byte.
 */
            case licmpe_ub:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popUnsignedLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 equal with unsigned type Byte.
 */
            case liucmpe_ub:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_8 a = stack.popUnsignedLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 less than or equal to unsigned type Byte.
 */
            case licmple_ub:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popUnsignedLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than or equal to unsigned type Byte.
 */
            case liucmple_ub:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_8 a = stack.popUnsignedLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than or equal to unsigned type Byte.
 */
            case licmpge_ub:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popUnsignedLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than or equal to unsigned type Byte.
 */
            case liucmpge_ub:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_8 a = stack.popUnsignedLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 not equal with unsigned type Byte.
 */
            case licmpne_ub:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popUnsignedLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 not equal with unsigned type Byte.
 */
            case liucmpne_ub:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_8 a = stack.popUnsignedLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_128 with type Short.
 */
            case limod_s:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a % b);
            }
                break;
/**
 * cast int_128 to unsigned type Short.
 */
            case licast_us:
                stack.pushUnsignedShort(static_cast<uint_16> (stack.popLongInt()));
                break;
/**
 * cast unsigned uint_128 to unsigned type Short.
 */
            case liucast_us:
                stack.pushUnsignedShort(static_cast<uint_16> (stack.popUnsignedLongInt()));
                break;
/**
 * add int_128 with unsigned type Short.
 */
            case liadd_us:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a + b);
            }
                break;
/**
 * add unsigned uint_128 with unsigned type Short.
 */
            case liuadd_us:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_16 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a + b);
            }
                break;
/**
 * subtract int_128 with unsigned type Short.
 */
            case lisub_us:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_128 with unsigned type Short.
 */
            case liusub_us:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_16 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a - b);
            }
                break;
/**
 * multiply int_128 with unsigned type Short.
 */
            case limul_us:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_128 with unsigned type Short.
 */
            case liumul_us:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_16 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a * b);
            }
                break;
/**
 * divide int_128 with unsigned type Short.
 */
            case lidiv_us:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a / b);
            }
                break;
/**
 * divide unsigned uint_128 with unsigned type Short.
 */
            case liudiv_us:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_16 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a / b);
            }
                break;
/**
 * compare int_128 less than unsigned type Short.
 */
            case licmpl_us:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popUnsignedLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than unsigned type Short.
 */
            case liucmpl_us:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_16 a = stack.popUnsignedLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than unsigned type Short.
 */
            case licmpg_us:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popUnsignedLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than unsigned type Short.
 */
            case liucmpg_us:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_16 a = stack.popUnsignedLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 equal with unsigned type Short.
 */
            case licmpe_us:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popUnsignedLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 equal with unsigned type Short.
 */
            case liucmpe_us:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_16 a = stack.popUnsignedLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 less than or equal to unsigned type Short.
 */
            case licmple_us:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popUnsignedLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than or equal to unsigned type Short.
 */
            case liucmple_us:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_16 a = stack.popUnsignedLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than or equal to unsigned type Short.
 */
            case licmpge_us:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popUnsignedLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than or equal to unsigned type Short.
 */
            case liucmpge_us:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_16 a = stack.popUnsignedLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 not equal with unsigned type Short.
 */
            case licmpne_us:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popUnsignedLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 not equal with unsigned type Short.
 */
            case liucmpne_us:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_16 a = stack.popUnsignedLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_128 with type Int.
 */
            case limod_i:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a % b);
            }
                break;
/**
 * cast int_128 to unsigned type Int.
 */
            case licast_ui:
                stack.pushUnsignedInt(static_cast<uint_32> (stack.popLongInt()));
                break;
/**
 * cast unsigned uint_128 to unsigned type Int.
 */
            case liucast_ui:
                stack.pushUnsignedInt(static_cast<uint_32> (stack.popUnsignedLongInt()));
                break;
/**
 * add int_128 with unsigned type Int.
 */
            case liadd_ui:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a + b);
            }
                break;
/**
 * add unsigned uint_128 with unsigned type Int.
 */
            case liuadd_ui:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_32 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a + b);
            }
                break;
/**
 * subtract int_128 with unsigned type Int.
 */
            case lisub_ui:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_128 with unsigned type Int.
 */
            case liusub_ui:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_32 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a - b);
            }
                break;
/**
 * multiply int_128 with unsigned type Int.
 */
            case limul_ui:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_128 with unsigned type Int.
 */
            case liumul_ui:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_32 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a * b);
            }
                break;
/**
 * divide int_128 with unsigned type Int.
 */
            case lidiv_ui:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a / b);
            }
                break;
/**
 * divide unsigned uint_128 with unsigned type Int.
 */
            case liudiv_ui:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_32 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a / b);
            }
                break;
/**
 * compare int_128 less than unsigned type Int.
 */
            case licmpl_ui:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popUnsignedLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than unsigned type Int.
 */
            case liucmpl_ui:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_32 a = stack.popUnsignedLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than unsigned type Int.
 */
            case licmpg_ui:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popUnsignedLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than unsigned type Int.
 */
            case liucmpg_ui:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_32 a = stack.popUnsignedLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 equal with unsigned type Int.
 */
            case licmpe_ui:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popUnsignedLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 equal with unsigned type Int.
 */
            case liucmpe_ui:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_32 a = stack.popUnsignedLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 less than or equal to unsigned type Int.
 */
            case licmple_ui:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popUnsignedLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than or equal to unsigned type Int.
 */
            case liucmple_ui:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_32 a = stack.popUnsignedLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than or equal to unsigned type Int.
 */
            case licmpge_ui:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popUnsignedLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than or equal to unsigned type Int.
 */
            case liucmpge_ui:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_32 a = stack.popUnsignedLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 not equal with unsigned type Int.
 */
            case licmpne_ui:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popUnsignedLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 not equal with unsigned type Int.
 */
            case liucmpne_ui:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_32 a = stack.popUnsignedLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_128 with type Long.
 */
            case limod_l:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a % b);
            }
                break;
/**
 * cast int_128 to unsigned type Long.
 */
            case licast_ul:
                stack.pushUnsignedLong(static_cast<uint_64> (stack.popLongInt()));
                break;
/**
 * cast unsigned uint_128 to unsigned type Long.
 */
            case liucast_ul:
                stack.pushUnsignedLong(static_cast<uint_64> (stack.popUnsignedLongInt()));
                break;
/**
 * add int_128 with unsigned type Long.
 */
            case liadd_ul:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a + b);
            }
                break;
/**
 * add unsigned uint_128 with unsigned type Long.
 */
            case liuadd_ul:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_64 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a + b);
            }
                break;
/**
 * subtract int_128 with unsigned type Long.
 */
            case lisub_ul:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_128 with unsigned type Long.
 */
            case liusub_ul:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_64 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a - b);
            }
                break;
/**
 * multiply int_128 with unsigned type Long.
 */
            case limul_ul:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_128 with unsigned type Long.
 */
            case liumul_ul:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_64 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a * b);
            }
                break;
/**
 * divide int_128 with unsigned type Long.
 */
            case lidiv_ul:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a / b);
            }
                break;
/**
 * divide unsigned uint_128 with unsigned type Long.
 */
            case liudiv_ul:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_64 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a / b);
            }
                break;
/**
 * compare int_128 less than unsigned type Long.
 */
            case licmpl_ul:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popUnsignedLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than unsigned type Long.
 */
            case liucmpl_ul:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_64 a = stack.popUnsignedLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than unsigned type Long.
 */
            case licmpg_ul:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popUnsignedLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than unsigned type Long.
 */
            case liucmpg_ul:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_64 a = stack.popUnsignedLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 equal with unsigned type Long.
 */
            case licmpe_ul:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popUnsignedLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 equal with unsigned type Long.
 */
            case liucmpe_ul:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_64 a = stack.popUnsignedLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 less than or equal to unsigned type Long.
 */
            case licmple_ul:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popUnsignedLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than or equal to unsigned type Long.
 */
            case liucmple_ul:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_64 a = stack.popUnsignedLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than or equal to unsigned type Long.
 */
            case licmpge_ul:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popUnsignedLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than or equal to unsigned type Long.
 */
            case liucmpge_ul:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_64 a = stack.popUnsignedLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 not equal with unsigned type Long.
 */
            case licmpne_ul:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popUnsignedLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 not equal with unsigned type Long.
 */
            case liucmpne_ul:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_64 a = stack.popUnsignedLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_128 with type LongInt.
 */
            case limod_li:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a % b);
            }
                break;
/**
 * cast int_128 to unsigned type LongInt.
 */
            case licast_uli:
                stack.pushUnsignedLongInt(static_cast<uint_128> (stack.popLongInt()));
                break;
/**
 * cast unsigned uint_128 to unsigned type LongInt.
 */
            case liucast_uli:
                stack.pushUnsignedLongInt(static_cast<uint_128> (stack.popUnsignedLongInt()));
                break;
/**
 * add int_128 with unsigned type LongInt.
 */
            case liadd_uli:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a + b);
            }
                break;
/**
 * add unsigned uint_128 with unsigned type LongInt.
 */
            case liuadd_uli:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a + b);
            }
                break;
/**
 * subtract int_128 with unsigned type LongInt.
 */
            case lisub_uli:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a - b);
            }
                break;
/**
 * subtract unsigned uint_128 with unsigned type LongInt.
 */
            case liusub_uli:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a - b);
            }
                break;
/**
 * multiply int_128 with unsigned type LongInt.
 */
            case limul_uli:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a * b);
            }
                break;
/**
 * multiply unsigned uint_128 with unsigned type LongInt.
 */
            case liumul_uli:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a * b);
            }
                break;
/**
 * divide int_128 with unsigned type LongInt.
 */
            case lidiv_uli:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a / b);
            }
                break;
/**
 * divide unsigned uint_128 with unsigned type LongInt.
 */
            case liudiv_uli:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushUnsignedLongInt(a / b);
            }
                break;
/**
 * compare int_128 less than unsigned type LongInt.
 */
            case licmpl_uli:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than unsigned type LongInt.
 */
            case liucmpl_uli:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than unsigned type LongInt.
 */
            case licmpg_uli:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than unsigned type LongInt.
 */
            case liucmpg_uli:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 equal with unsigned type LongInt.
 */
            case licmpe_uli:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 equal with unsigned type LongInt.
 */
            case liucmpe_uli:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 less than or equal to unsigned type LongInt.
 */
            case licmple_uli:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than or equal to unsigned type LongInt.
 */
            case liucmple_uli:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than or equal to unsigned type LongInt.
 */
            case licmpge_uli:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than or equal to unsigned type LongInt.
 */
            case liucmpge_uli:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 not equal with unsigned type LongInt.
 */
            case licmpne_uli:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 not equal with unsigned type LongInt.
 */
            case liucmpne_uli:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_128 a = stack.popUnsignedLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_128 with type LongLong.
 */
            case limod_ll:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a % b);
            }
                break;
/**
 * cast int_128 to unsigned type LongLong.
 */
            case licast_ull:
                stack.pushUnsignedLongLong(static_cast<uint_256> (stack.popLongInt()));
                break;
/**
 * cast unsigned uint_128 to unsigned type LongLong.
 */
            case liucast_ull:
                stack.pushUnsignedLongLong(static_cast<uint_256> (stack.popUnsignedLongInt()));
                break;
/**
 * add int_128 with unsigned type LongLong.
 */
            case liadd_ull:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_128 with unsigned type LongLong.
 */
            case liuadd_ull:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a + b);
            }
                break;
/**
 * subtract int_128 with unsigned type LongLong.
 */
            case lisub_ull:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_128 with unsigned type LongLong.
 */
            case liusub_ull:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a - b);
            }
                break;
/**
 * multiply int_128 with unsigned type LongLong.
 */
            case limul_ull:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_128 with unsigned type LongLong.
 */
            case liumul_ull:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a * b);
            }
                break;
/**
 * divide int_128 with unsigned type LongLong.
 */
            case lidiv_ull:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_128 with unsigned type LongLong.
 */
            case liudiv_ull:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a / b);
            }
                break;
/**
 * compare int_128 less than unsigned type LongLong.
 */
            case licmpl_ull:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than unsigned type LongLong.
 */
            case liucmpl_ull:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than unsigned type LongLong.
 */
            case licmpg_ull:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than unsigned type LongLong.
 */
            case liucmpg_ull:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 equal with unsigned type LongLong.
 */
            case licmpe_ull:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 equal with unsigned type LongLong.
 */
            case liucmpe_ull:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 less than or equal to unsigned type LongLong.
 */
            case licmple_ull:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 less than or equal to unsigned type LongLong.
 */
            case liucmple_ull:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 greater than or equal to unsigned type LongLong.
 */
            case licmpge_ull:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 greater than or equal to unsigned type LongLong.
 */
            case liucmpge_ull:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_128 not equal with unsigned type LongLong.
 */
            case licmpne_ull:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_128 not equal with unsigned type LongLong.
 */
            case liucmpne_ull:
            {
                uint_128 b = stack.popUnsignedLongInt();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * bitwise and int_128 with type Byte.
 */
            case liand_b:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popByte();
                stack.pushLongInt(a & b);
            }
                break;
/**
 * bitwise or int_128 with type Byte.
 */
            case lior_b:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popByte();
                stack.pushLongInt(a | b);
            }
                break;
/**
 * bitwise xor int_128 with type Byte.
 */
            case lixor_b:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popByte();
                stack.pushLongInt(a ^ b);
            }
                break;
/**
 * shift right int_128 with type Byte.
 */
            case lishftr_b:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popByte();
                stack.pushLongInt(a >> b);
            }
                break;
/**
 * shift left xor int_128 with type Byte.
 */
            case lishftl_b:
            {
                int_128 b = stack.popLongInt();
                int_8 a = stack.popByte();
                stack.pushLongInt(a << b);
            }
                break;
/**
 * bitwise and int_128 with type Short.
 */
            case liand_s:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popShort();
                stack.pushLongInt(a & b);
            }
                break;
/**
 * bitwise or int_128 with type Short.
 */
            case lior_s:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popShort();
                stack.pushLongInt(a | b);
            }
                break;
/**
 * bitwise xor int_128 with type Short.
 */
            case lixor_s:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popShort();
                stack.pushLongInt(a ^ b);
            }
                break;
/**
 * shift right int_128 with type Short.
 */
            case lishftr_s:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popShort();
                stack.pushLongInt(a >> b);
            }
                break;
/**
 * shift left xor int_128 with type Short.
 */
            case lishftl_s:
            {
                int_128 b = stack.popLongInt();
                int_16 a = stack.popShort();
                stack.pushLongInt(a << b);
            }
                break;
/**
 * bitwise and int_128 with type Int.
 */
            case liand_i:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popInt();
                stack.pushLongInt(a & b);
            }
                break;
/**
 * bitwise or int_128 with type Int.
 */
            case lior_i:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popInt();
                stack.pushLongInt(a | b);
            }
                break;
/**
 * bitwise xor int_128 with type Int.
 */
            case lixor_i:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popInt();
                stack.pushLongInt(a ^ b);
            }
                break;
/**
 * shift right int_128 with type Int.
 */
            case lishftr_i:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popInt();
                stack.pushLongInt(a >> b);
            }
                break;
/**
 * shift left xor int_128 with type Int.
 */
            case lishftl_i:
            {
                int_128 b = stack.popLongInt();
                int_32 a = stack.popInt();
                stack.pushLongInt(a << b);
            }
                break;
/**
 * bitwise and int_128 with type Long.
 */
            case liand_l:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popLong();
                stack.pushLongInt(a & b);
            }
                break;
/**
 * bitwise or int_128 with type Long.
 */
            case lior_l:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popLong();
                stack.pushLongInt(a | b);
            }
                break;
/**
 * bitwise xor int_128 with type Long.
 */
            case lixor_l:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popLong();
                stack.pushLongInt(a ^ b);
            }
                break;
/**
 * shift right int_128 with type Long.
 */
            case lishftr_l:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popLong();
                stack.pushLongInt(a >> b);
            }
                break;
/**
 * shift left xor int_128 with type Long.
 */
            case lishftl_l:
            {
                int_128 b = stack.popLongInt();
                int_64 a = stack.popLong();
                stack.pushLongInt(a << b);
            }
                break;
/**
 * bitwise and int_128 with type LongInt.
 */
            case liand_li:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a & b);
            }
                break;
/**
 * bitwise or int_128 with type LongInt.
 */
            case lior_li:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a | b);
            }
                break;
/**
 * bitwise xor int_128 with type LongInt.
 */
            case lixor_li:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a ^ b);
            }
                break;
/**
 * shift right int_128 with type LongInt.
 */
            case lishftr_li:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a >> b);
            }
                break;
/**
 * shift left xor int_128 with type LongInt.
 */
            case lishftl_li:
            {
                int_128 b = stack.popLongInt();
                int_128 a = stack.popLongInt();
                stack.pushLongInt(a << b);
            }
                break;
/**
 * bitwise and int_128 with type LongLong.
 */
            case liand_ll:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a & b);
            }
                break;
/**
 * bitwise or int_128 with type LongLong.
 */
            case lior_ll:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a | b);
            }
                break;
/**
 * bitwise xor int_128 with type LongLong.
 */
            case lixor_ll:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a ^ b);
            }
                break;
/**
 * shift right int_128 with type LongLong.
 */
            case lishftr_ll:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a >> b);
            }
                break;
/**
 * shift left xor int_128 with type LongLong.
 */
            case lishftl_ll:
            {
                int_128 b = stack.popLongInt();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a << b);
            }
                break;
/**
 * duplicate a int_128 on the stack.
 */
            case lidup:
                stack.pushLongInt(stack.peekLongInt());
                break;
/**
 * duplicate a int_128 2 times on the stack.
 */
            case lidup2:
                stack.pushLongInt(stack.peekLongInt());stack.pushLongInt(stack.peekLongInt());
                break;
/**
 * duplicate a int_128 3 times on the stack.
 */
            case lidup3:
                stack.pushLongInt(stack.peekLongInt());stack.pushLongInt(stack.peekLongInt());stack.pushLongInt(stack.peekLongInt());
                break;
/**
 * duplicate a int_128 4 times on the stack.
 */
            case lidup4:
                stack.pushLongInt(stack.peekLongInt());stack.pushLongInt(stack.peekLongInt());stack.pushLongInt(stack.peekLongInt());stack.pushLongInt(stack.peekLongInt());
                break;
/**
 * duplicate a int_128 5 times on the stack.
 */
            case lidup5:
                stack.pushLongInt(stack.peekLongInt());stack.pushLongInt(stack.peekLongInt());stack.pushLongInt(stack.peekLongInt());stack.pushLongInt(stack.peekLongInt());stack.pushLongInt(stack.peekLongInt());
                break;
/**
 * set a int_128 from stack into a field on base pointer.
 */
            case liset:
                accessMemoryAndSetLongInt(base, ops.getUnsignedInt(), stack.popLongInt());
                break;
/**
 * get a int_128 from a field on base pointer to stack.
 */
            case liget:
                stack.pushLongInt(accessMemoryAndGetLongInt(base, ops.getUnsignedInt()));
                break;
/**
 * set a int_128 from value into a field on base pointer.
 */
            case livset:
                accessMemoryAndSetLongInt(base, ops.getUnsignedInt(), ops.getLongInt());
                break;
/**
 * get a int_128 from a field on base pointer to stack using address from stack.
 */
            case lisget:
                stack.pushLongInt(accessMemoryAndGetLongInt(base, stack.popUnsignedInt()));
                break;
/**
 * set a int_128 from stack into a field on base pointer using address from stack.
 */
            case lisset:
                accessMemoryAndSetLongInt(base, stack.popUnsignedInt(), stack.popLongInt());
                break;
/**
 * set a int_128 from local variable into a field on base pointer.
 */
            case lisetl:
                accessMemoryAndSetLongInt(base, ops.getUnsignedInt(), lvt[ops.getUnsignedShort()].LongInt);
                break;
/**
 * increment int_128 by 1 on stack.
 */
            case liinc_1:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].LongInt = lvt[point].LongInt + 1; }
                break;
/**
 * increment int_128 by 2 on stack.
 */
            case liinc_2:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].LongInt = lvt[point].LongInt + 2; }
                break;
/**
 * increment int_128 by 1 on stack.
 */
            case listinc_1:
                stack.pushLongInt(stack.popLongInt() + 1);
                break;
/**
 * increment int_128 by 2 on stack.
 */
            case listinc_2:
                stack.pushLongInt(stack.popLongInt() + 2);
                break;
/**
 * return a int_128 into the main stack.
 */
            case lireturn:
                stack_main.pushLongInt(stack.popLongInt());
                break;
/**
 * store a int_128 from main stack in a local variable..
 */
            case limainst:
                lvt[ops.getUnsignedShort()].LongInt = stack_main.popLongInt();
                break;
/**
 * store a int_128 from main stack in local variable 0.
 */
            case limainst_0:
                lvt[0].LongInt = stack_main.popLongInt();;
                break;
/**
 * store a int_128 from main stack in local variable 1.
 */
            case limainst_1:
                lvt[1].LongInt = stack_main.popLongInt();;
                break;
/**
 * store a int_128 from main stack in local variable 2.
 */
            case limainst_2:
                lvt[2].LongInt = stack_main.popLongInt();;
                break;
/**
 * store a int_128 from main stack in local variable 3.
 */
            case limainst_3:
                lvt[3].LongInt = stack_main.popLongInt();;
                break;
/**
 * print a int_128 from stack.
 */
            case liprint:
                log(std::to_string(stack.popLongInt()));
                break;
/**
 * print a unsigned uint_128 from stack.
 */
            case liuprint:
                log(std::to_string(stack.popUnsignedLongInt()));
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
 * push a const int_256 into the stack (value = 1).
 */
            case llconst_1:
                stack.pushLongLong(1);
                break;
/**
 * push a const int_256 into the stack (value = 2).
 */
            case llconst_2:
                stack.pushLongLong(2);
                break;
/**
 * push a const int_256 into the stack (value = 3).
 */
            case llconst_3:
                stack.pushLongLong(3);
                break;
/**
 * push a const int_256 into the stack (value = 4).
 */
            case llconst_4:
                stack.pushLongLong(4);
                break;
/**
 * push a const int_256 into the stack (value = 5).
 */
            case llconst_5:
                stack.pushLongLong(5);
                break;
/**
 * push a const int_256 into the stack (value = 6).
 */
            case llconst_6:
                stack.pushLongLong(6);
                break;
/**
 * push a const int_256 into the stack (value = 9).
 */
            case llconst_9:
                stack.pushLongLong(9);
                break;
/**
 * push a const int_256 into the stack (value = 10).
 */
            case llconst_10:
                stack.pushLongLong(10);
                break;
/**
 * push a const int_256 into the stack (value = 11).
 */
            case llconst_11:
                stack.pushLongLong(11);
                break;
/**
 * push a const int_256 into the stack (value = 12).
 */
            case llconst_12:
                stack.pushLongLong(12);
                break;
/**
 * load a int_256 into the stack from local variable.
 */
            case llload:
                stack.pushLongLong(lvt[ops.getUnsignedShort()].LongLong);
                break;
/**
 * load a int_256 into the stack from local variable 0.
 */
            case llload_0:
                stack.pushLongLong(lvt[0].LongLong);
                break;
/**
 * load a int_256 into the stack from local variable 1.
 */
            case llload_1:
                stack.pushLongLong(lvt[1].LongLong);
                break;
/**
 * load a int_256 into the stack from local variable 2.
 */
            case llload_2:
                stack.pushLongLong(lvt[2].LongLong);
                break;
/**
 * load a int_256 into the stack from local variable 3.
 */
            case llload_3:
                stack.pushLongLong(lvt[3].LongLong);
                break;
/**
 * load a int_256 into the stack from local variable 4.
 */
            case llload_4:
                stack.pushLongLong(lvt[4].LongLong);
                break;
/**
 * store a int_256 from stack into local variable.
 */
            case llstore:
                lvt[ops.getUnsignedShort()] = lve_LongLong(stack.popLongLong());
                break;
/**
 * store a int_256 from stack into local variable 0.
 */
            case llstore_0:
                lvt[0] = lve_LongLong(stack.popLongLong());
                break;
/**
 * store a int_256 from stack into local variable 1.
 */
            case llstore_1:
                lvt[1] = lve_LongLong(stack.popLongLong());
                break;
/**
 * store a int_256 from stack into local variable 2.
 */
            case llstore_2:
                lvt[2] = lve_LongLong(stack.popLongLong());
                break;
/**
 * store a int_256 from stack into local variable 3.
 */
            case llstore_3:
                lvt[3] = lve_LongLong(stack.popLongLong());
                break;
/**
 * store a int_256 from stack into local variable 4.
 */
            case llstore_4:
                lvt[4] = lve_LongLong(stack.popLongLong());
                break;
/**
 * cast int_256 to type Byte.
 */
            case llcast_b:
                stack.pushByte(static_cast<int_8> (stack.popLongLong()));
                break;
/**
 * cast unsigned uint_256 to type Byte.
 */
            case llucast_b:
                stack.pushByte(static_cast<int_8> (stack.popUnsignedLongLong()));
                break;
/**
 * add int_256 with type Byte.
 */
            case lladd_b:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popByte();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_256 with type Byte.
 */
            case lluadd_b:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_8 a = stack.popByte();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * subtract int_256 with type Byte.
 */
            case llsub_b:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popByte();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_256 with type Byte.
 */
            case llusub_b:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_8 a = stack.popByte();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * multiply int_256 with type Byte.
 */
            case llmul_b:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popByte();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_256 with type Byte.
 */
            case llumul_b:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_8 a = stack.popByte();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * divide int_256 with type Byte.
 */
            case lldiv_b:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popByte();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_256 with type Byte.
 */
            case lludiv_b:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_8 a = stack.popByte();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * compare int_256 less than type Byte.
 */
            case llcmpl_b:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popByte();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than type Byte.
 */
            case llucmpl_b:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_8 a = stack.popByte();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than type Byte.
 */
            case llcmpg_b:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popByte();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than type Byte.
 */
            case llucmpg_b:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_8 a = stack.popByte();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 equal with type Byte.
 */
            case llcmpe_b:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popByte();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 equal with type Byte.
 */
            case llucmpe_b:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_8 a = stack.popByte();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 less than or equal to type Byte.
 */
            case llcmple_b:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popByte();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than or equal to type Byte.
 */
            case llucmple_b:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_8 a = stack.popByte();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than or equal to type Byte.
 */
            case llcmpge_b:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popByte();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than or equal to type Byte.
 */
            case llucmpge_b:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_8 a = stack.popByte();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 not equal with type Byte.
 */
            case llcmpne_b:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popByte();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 not equal with type Byte.
 */
            case llucmpne_b:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_8 a = stack.popByte();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_256 to type Short.
 */
            case llcast_s:
                stack.pushShort(static_cast<int_16> (stack.popLongLong()));
                break;
/**
 * cast unsigned uint_256 to type Short.
 */
            case llucast_s:
                stack.pushShort(static_cast<int_16> (stack.popUnsignedLongLong()));
                break;
/**
 * add int_256 with type Short.
 */
            case lladd_s:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popShort();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_256 with type Short.
 */
            case lluadd_s:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_16 a = stack.popShort();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * subtract int_256 with type Short.
 */
            case llsub_s:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popShort();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_256 with type Short.
 */
            case llusub_s:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_16 a = stack.popShort();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * multiply int_256 with type Short.
 */
            case llmul_s:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popShort();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_256 with type Short.
 */
            case llumul_s:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_16 a = stack.popShort();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * divide int_256 with type Short.
 */
            case lldiv_s:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popShort();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_256 with type Short.
 */
            case lludiv_s:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_16 a = stack.popShort();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * compare int_256 less than type Short.
 */
            case llcmpl_s:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popShort();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than type Short.
 */
            case llucmpl_s:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_16 a = stack.popShort();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than type Short.
 */
            case llcmpg_s:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popShort();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than type Short.
 */
            case llucmpg_s:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_16 a = stack.popShort();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 equal with type Short.
 */
            case llcmpe_s:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popShort();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 equal with type Short.
 */
            case llucmpe_s:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_16 a = stack.popShort();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 less than or equal to type Short.
 */
            case llcmple_s:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popShort();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than or equal to type Short.
 */
            case llucmple_s:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_16 a = stack.popShort();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than or equal to type Short.
 */
            case llcmpge_s:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popShort();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than or equal to type Short.
 */
            case llucmpge_s:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_16 a = stack.popShort();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 not equal with type Short.
 */
            case llcmpne_s:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popShort();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 not equal with type Short.
 */
            case llucmpne_s:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_16 a = stack.popShort();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_256 to type Int.
 */
            case llcast_i:
                stack.pushInt(static_cast<int_32> (stack.popLongLong()));
                break;
/**
 * cast unsigned uint_256 to type Int.
 */
            case llucast_i:
                stack.pushInt(static_cast<int_32> (stack.popUnsignedLongLong()));
                break;
/**
 * add int_256 with type Int.
 */
            case lladd_i:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popInt();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_256 with type Int.
 */
            case lluadd_i:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_32 a = stack.popInt();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * subtract int_256 with type Int.
 */
            case llsub_i:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popInt();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_256 with type Int.
 */
            case llusub_i:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_32 a = stack.popInt();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * multiply int_256 with type Int.
 */
            case llmul_i:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popInt();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_256 with type Int.
 */
            case llumul_i:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_32 a = stack.popInt();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * divide int_256 with type Int.
 */
            case lldiv_i:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popInt();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_256 with type Int.
 */
            case lludiv_i:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_32 a = stack.popInt();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * compare int_256 less than type Int.
 */
            case llcmpl_i:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than type Int.
 */
            case llucmpl_i:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_32 a = stack.popInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than type Int.
 */
            case llcmpg_i:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than type Int.
 */
            case llucmpg_i:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_32 a = stack.popInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 equal with type Int.
 */
            case llcmpe_i:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 equal with type Int.
 */
            case llucmpe_i:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_32 a = stack.popInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 less than or equal to type Int.
 */
            case llcmple_i:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than or equal to type Int.
 */
            case llucmple_i:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_32 a = stack.popInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than or equal to type Int.
 */
            case llcmpge_i:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than or equal to type Int.
 */
            case llucmpge_i:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_32 a = stack.popInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 not equal with type Int.
 */
            case llcmpne_i:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 not equal with type Int.
 */
            case llucmpne_i:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_32 a = stack.popInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_256 to type Long.
 */
            case llcast_l:
                stack.pushLong(static_cast<int_64> (stack.popLongLong()));
                break;
/**
 * cast unsigned uint_256 to type Long.
 */
            case llucast_l:
                stack.pushLong(static_cast<int_64> (stack.popUnsignedLongLong()));
                break;
/**
 * add int_256 with type Long.
 */
            case lladd_l:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popLong();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_256 with type Long.
 */
            case lluadd_l:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_64 a = stack.popLong();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * subtract int_256 with type Long.
 */
            case llsub_l:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popLong();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_256 with type Long.
 */
            case llusub_l:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_64 a = stack.popLong();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * multiply int_256 with type Long.
 */
            case llmul_l:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popLong();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_256 with type Long.
 */
            case llumul_l:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_64 a = stack.popLong();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * divide int_256 with type Long.
 */
            case lldiv_l:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popLong();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_256 with type Long.
 */
            case lludiv_l:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_64 a = stack.popLong();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * compare int_256 less than type Long.
 */
            case llcmpl_l:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than type Long.
 */
            case llucmpl_l:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_64 a = stack.popLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than type Long.
 */
            case llcmpg_l:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than type Long.
 */
            case llucmpg_l:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_64 a = stack.popLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 equal with type Long.
 */
            case llcmpe_l:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 equal with type Long.
 */
            case llucmpe_l:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_64 a = stack.popLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 less than or equal to type Long.
 */
            case llcmple_l:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than or equal to type Long.
 */
            case llucmple_l:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_64 a = stack.popLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than or equal to type Long.
 */
            case llcmpge_l:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than or equal to type Long.
 */
            case llucmpge_l:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_64 a = stack.popLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 not equal with type Long.
 */
            case llcmpne_l:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 not equal with type Long.
 */
            case llucmpne_l:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_64 a = stack.popLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_256 to type LongInt.
 */
            case llcast_li:
                stack.pushLongInt(static_cast<int_128> (stack.popLongLong()));
                break;
/**
 * cast unsigned uint_256 to type LongInt.
 */
            case llucast_li:
                stack.pushLongInt(static_cast<int_128> (stack.popUnsignedLongLong()));
                break;
/**
 * add int_256 with type LongInt.
 */
            case lladd_li:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popLongInt();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_256 with type LongInt.
 */
            case lluadd_li:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_128 a = stack.popLongInt();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * subtract int_256 with type LongInt.
 */
            case llsub_li:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popLongInt();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_256 with type LongInt.
 */
            case llusub_li:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_128 a = stack.popLongInt();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * multiply int_256 with type LongInt.
 */
            case llmul_li:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popLongInt();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_256 with type LongInt.
 */
            case llumul_li:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_128 a = stack.popLongInt();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * divide int_256 with type LongInt.
 */
            case lldiv_li:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popLongInt();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_256 with type LongInt.
 */
            case lludiv_li:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_128 a = stack.popLongInt();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * compare int_256 less than type LongInt.
 */
            case llcmpl_li:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than type LongInt.
 */
            case llucmpl_li:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_128 a = stack.popLongInt();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than type LongInt.
 */
            case llcmpg_li:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than type LongInt.
 */
            case llucmpg_li:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_128 a = stack.popLongInt();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 equal with type LongInt.
 */
            case llcmpe_li:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 equal with type LongInt.
 */
            case llucmpe_li:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_128 a = stack.popLongInt();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 less than or equal to type LongInt.
 */
            case llcmple_li:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than or equal to type LongInt.
 */
            case llucmple_li:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_128 a = stack.popLongInt();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than or equal to type LongInt.
 */
            case llcmpge_li:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than or equal to type LongInt.
 */
            case llucmpge_li:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_128 a = stack.popLongInt();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 not equal with type LongInt.
 */
            case llcmpne_li:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 not equal with type LongInt.
 */
            case llucmpne_li:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_128 a = stack.popLongInt();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_256 to type LongLong.
 */
            case llcast_ll:
                stack.pushLongLong(static_cast<int_256> (stack.popLongLong()));
                break;
/**
 * cast unsigned uint_256 to type LongLong.
 */
            case llucast_ll:
                stack.pushLongLong(static_cast<int_256> (stack.popUnsignedLongLong()));
                break;
/**
 * add int_256 with type LongLong.
 */
            case lladd_ll:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_256 with type LongLong.
 */
            case lluadd_ll:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * subtract int_256 with type LongLong.
 */
            case llsub_ll:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_256 with type LongLong.
 */
            case llusub_ll:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * multiply int_256 with type LongLong.
 */
            case llmul_ll:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_256 with type LongLong.
 */
            case llumul_ll:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * divide int_256 with type LongLong.
 */
            case lldiv_ll:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_256 with type LongLong.
 */
            case lludiv_ll:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * compare int_256 less than type LongLong.
 */
            case llcmpl_ll:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than type LongLong.
 */
            case llucmpl_ll:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than type LongLong.
 */
            case llcmpg_ll:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than type LongLong.
 */
            case llucmpg_ll:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 equal with type LongLong.
 */
            case llcmpe_ll:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 equal with type LongLong.
 */
            case llucmpe_ll:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 less than or equal to type LongLong.
 */
            case llcmple_ll:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than or equal to type LongLong.
 */
            case llucmple_ll:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than or equal to type LongLong.
 */
            case llcmpge_ll:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than or equal to type LongLong.
 */
            case llucmpge_ll:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 not equal with type LongLong.
 */
            case llcmpne_ll:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 not equal with type LongLong.
 */
            case llucmpne_ll:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_256 a = stack.popLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_256 to type Float.
 */
            case llcast_f:
                stack.pushFloat(static_cast<flt_32> (stack.popLongLong()));
                break;
/**
 * cast unsigned uint_256 to type Float.
 */
            case llucast_f:
                stack.pushFloat(static_cast<flt_32> (stack.popUnsignedLongLong()));
                break;
/**
 * add int_256 with type Float.
 */
            case lladd_f:
            {
                int_256 b = stack.popLongLong();
                flt_32 a = stack.popFloat();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_256 with type Float.
 */
            case lluadd_f:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_32 a = stack.popFloat();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * subtract int_256 with type Float.
 */
            case llsub_f:
            {
                int_256 b = stack.popLongLong();
                flt_32 a = stack.popFloat();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_256 with type Float.
 */
            case llusub_f:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_32 a = stack.popFloat();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * multiply int_256 with type Float.
 */
            case llmul_f:
            {
                int_256 b = stack.popLongLong();
                flt_32 a = stack.popFloat();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_256 with type Float.
 */
            case llumul_f:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_32 a = stack.popFloat();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * divide int_256 with type Float.
 */
            case lldiv_f:
            {
                int_256 b = stack.popLongLong();
                flt_32 a = stack.popFloat();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_256 with type Float.
 */
            case lludiv_f:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_32 a = stack.popFloat();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * compare int_256 less than type Float.
 */
            case llcmpl_f:
            {
                int_256 b = stack.popLongLong();
                flt_32 a = stack.popFloat();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than type Float.
 */
            case llucmpl_f:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_32 a = stack.popFloat();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than type Float.
 */
            case llcmpg_f:
            {
                int_256 b = stack.popLongLong();
                flt_32 a = stack.popFloat();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than type Float.
 */
            case llucmpg_f:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_32 a = stack.popFloat();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 equal with type Float.
 */
            case llcmpe_f:
            {
                int_256 b = stack.popLongLong();
                flt_32 a = stack.popFloat();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 equal with type Float.
 */
            case llucmpe_f:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_32 a = stack.popFloat();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 less than or equal to type Float.
 */
            case llcmple_f:
            {
                int_256 b = stack.popLongLong();
                flt_32 a = stack.popFloat();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than or equal to type Float.
 */
            case llucmple_f:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_32 a = stack.popFloat();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than or equal to type Float.
 */
            case llcmpge_f:
            {
                int_256 b = stack.popLongLong();
                flt_32 a = stack.popFloat();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than or equal to type Float.
 */
            case llucmpge_f:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_32 a = stack.popFloat();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 not equal with type Float.
 */
            case llcmpne_f:
            {
                int_256 b = stack.popLongLong();
                flt_32 a = stack.popFloat();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 not equal with type Float.
 */
            case llucmpne_f:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_32 a = stack.popFloat();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_256 to type Double.
 */
            case llcast_d:
                stack.pushDouble(static_cast<flt_64> (stack.popLongLong()));
                break;
/**
 * cast unsigned uint_256 to type Double.
 */
            case llucast_d:
                stack.pushDouble(static_cast<flt_64> (stack.popUnsignedLongLong()));
                break;
/**
 * add int_256 with type Double.
 */
            case lladd_d:
            {
                int_256 b = stack.popLongLong();
                flt_64 a = stack.popDouble();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_256 with type Double.
 */
            case lluadd_d:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_64 a = stack.popDouble();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * subtract int_256 with type Double.
 */
            case llsub_d:
            {
                int_256 b = stack.popLongLong();
                flt_64 a = stack.popDouble();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_256 with type Double.
 */
            case llusub_d:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_64 a = stack.popDouble();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * multiply int_256 with type Double.
 */
            case llmul_d:
            {
                int_256 b = stack.popLongLong();
                flt_64 a = stack.popDouble();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_256 with type Double.
 */
            case llumul_d:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_64 a = stack.popDouble();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * divide int_256 with type Double.
 */
            case lldiv_d:
            {
                int_256 b = stack.popLongLong();
                flt_64 a = stack.popDouble();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_256 with type Double.
 */
            case lludiv_d:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_64 a = stack.popDouble();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * compare int_256 less than type Double.
 */
            case llcmpl_d:
            {
                int_256 b = stack.popLongLong();
                flt_64 a = stack.popDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than type Double.
 */
            case llucmpl_d:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_64 a = stack.popDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than type Double.
 */
            case llcmpg_d:
            {
                int_256 b = stack.popLongLong();
                flt_64 a = stack.popDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than type Double.
 */
            case llucmpg_d:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_64 a = stack.popDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 equal with type Double.
 */
            case llcmpe_d:
            {
                int_256 b = stack.popLongLong();
                flt_64 a = stack.popDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 equal with type Double.
 */
            case llucmpe_d:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_64 a = stack.popDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 less than or equal to type Double.
 */
            case llcmple_d:
            {
                int_256 b = stack.popLongLong();
                flt_64 a = stack.popDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than or equal to type Double.
 */
            case llucmple_d:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_64 a = stack.popDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than or equal to type Double.
 */
            case llcmpge_d:
            {
                int_256 b = stack.popLongLong();
                flt_64 a = stack.popDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than or equal to type Double.
 */
            case llucmpge_d:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_64 a = stack.popDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 not equal with type Double.
 */
            case llcmpne_d:
            {
                int_256 b = stack.popLongLong();
                flt_64 a = stack.popDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 not equal with type Double.
 */
            case llucmpne_d:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_64 a = stack.popDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_256 to type DoubleFloat.
 */
            case llcast_df:
                stack.pushDoubleFloat(static_cast<flt_128> (stack.popLongLong()));
                break;
/**
 * cast unsigned uint_256 to type DoubleFloat.
 */
            case llucast_df:
                stack.pushDoubleFloat(static_cast<flt_128> (stack.popUnsignedLongLong()));
                break;
/**
 * add int_256 with type DoubleFloat.
 */
            case lladd_df:
            {
                int_256 b = stack.popLongLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_256 with type DoubleFloat.
 */
            case lluadd_df:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * subtract int_256 with type DoubleFloat.
 */
            case llsub_df:
            {
                int_256 b = stack.popLongLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_256 with type DoubleFloat.
 */
            case llusub_df:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * multiply int_256 with type DoubleFloat.
 */
            case llmul_df:
            {
                int_256 b = stack.popLongLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_256 with type DoubleFloat.
 */
            case llumul_df:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * divide int_256 with type DoubleFloat.
 */
            case lldiv_df:
            {
                int_256 b = stack.popLongLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_256 with type DoubleFloat.
 */
            case lludiv_df:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * compare int_256 less than type DoubleFloat.
 */
            case llcmpl_df:
            {
                int_256 b = stack.popLongLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than type DoubleFloat.
 */
            case llucmpl_df:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than type DoubleFloat.
 */
            case llcmpg_df:
            {
                int_256 b = stack.popLongLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than type DoubleFloat.
 */
            case llucmpg_df:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 equal with type DoubleFloat.
 */
            case llcmpe_df:
            {
                int_256 b = stack.popLongLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 equal with type DoubleFloat.
 */
            case llucmpe_df:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 less than or equal to type DoubleFloat.
 */
            case llcmple_df:
            {
                int_256 b = stack.popLongLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than or equal to type DoubleFloat.
 */
            case llucmple_df:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than or equal to type DoubleFloat.
 */
            case llcmpge_df:
            {
                int_256 b = stack.popLongLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than or equal to type DoubleFloat.
 */
            case llucmpge_df:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 not equal with type DoubleFloat.
 */
            case llcmpne_df:
            {
                int_256 b = stack.popLongLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 not equal with type DoubleFloat.
 */
            case llucmpne_df:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_128 a = stack.popDoubleFloat();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * cast int_256 to type DoubleDouble.
 */
            case llcast_dd:
                stack.pushDoubleDouble(static_cast<flt_256> (stack.popLongLong()));
                break;
/**
 * cast unsigned uint_256 to type DoubleDouble.
 */
            case llucast_dd:
                stack.pushDoubleDouble(static_cast<flt_256> (stack.popUnsignedLongLong()));
                break;
/**
 * add int_256 with type DoubleDouble.
 */
            case lladd_dd:
            {
                int_256 b = stack.popLongLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_256 with type DoubleDouble.
 */
            case lluadd_dd:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushLongLong(a + b);
            }
                break;
/**
 * subtract int_256 with type DoubleDouble.
 */
            case llsub_dd:
            {
                int_256 b = stack.popLongLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_256 with type DoubleDouble.
 */
            case llusub_dd:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushLongLong(a - b);
            }
                break;
/**
 * multiply int_256 with type DoubleDouble.
 */
            case llmul_dd:
            {
                int_256 b = stack.popLongLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_256 with type DoubleDouble.
 */
            case llumul_dd:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushLongLong(a * b);
            }
                break;
/**
 * divide int_256 with type DoubleDouble.
 */
            case lldiv_dd:
            {
                int_256 b = stack.popLongLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_256 with type DoubleDouble.
 */
            case lludiv_dd:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushLongLong(a / b);
            }
                break;
/**
 * compare int_256 less than type DoubleDouble.
 */
            case llcmpl_dd:
            {
                int_256 b = stack.popLongLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than type DoubleDouble.
 */
            case llucmpl_dd:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than type DoubleDouble.
 */
            case llcmpg_dd:
            {
                int_256 b = stack.popLongLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than type DoubleDouble.
 */
            case llucmpg_dd:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 equal with type DoubleDouble.
 */
            case llcmpe_dd:
            {
                int_256 b = stack.popLongLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 equal with type DoubleDouble.
 */
            case llucmpe_dd:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 less than or equal to type DoubleDouble.
 */
            case llcmple_dd:
            {
                int_256 b = stack.popLongLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than or equal to type DoubleDouble.
 */
            case llucmple_dd:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than or equal to type DoubleDouble.
 */
            case llcmpge_dd:
            {
                int_256 b = stack.popLongLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than or equal to type DoubleDouble.
 */
            case llucmpge_dd:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 not equal with type DoubleDouble.
 */
            case llcmpne_dd:
            {
                int_256 b = stack.popLongLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 not equal with type DoubleDouble.
 */
            case llucmpne_dd:
            {
                uint_256 b = stack.popUnsignedLongLong();
                flt_256 a = stack.popDoubleDouble();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_256 with type Byte.
 */
            case llmod_b:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a % b);
            }
                break;
/**
 * cast int_256 to unsigned type Byte.
 */
            case llcast_ub:
                stack.pushUnsignedByte(static_cast<uint_8> (stack.popLongLong()));
                break;
/**
 * cast unsigned uint_256 to unsigned type Byte.
 */
            case llucast_ub:
                stack.pushUnsignedByte(static_cast<uint_8> (stack.popUnsignedLongLong()));
                break;
/**
 * add int_256 with unsigned type Byte.
 */
            case lladd_ub:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_256 with unsigned type Byte.
 */
            case lluadd_ub:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_8 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a + b);
            }
                break;
/**
 * subtract int_256 with unsigned type Byte.
 */
            case llsub_ub:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_256 with unsigned type Byte.
 */
            case llusub_ub:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_8 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a - b);
            }
                break;
/**
 * multiply int_256 with unsigned type Byte.
 */
            case llmul_ub:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_256 with unsigned type Byte.
 */
            case llumul_ub:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_8 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a * b);
            }
                break;
/**
 * divide int_256 with unsigned type Byte.
 */
            case lldiv_ub:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_256 with unsigned type Byte.
 */
            case lludiv_ub:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_8 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a / b);
            }
                break;
/**
 * compare int_256 less than unsigned type Byte.
 */
            case llcmpl_ub:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popUnsignedLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than unsigned type Byte.
 */
            case llucmpl_ub:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_8 a = stack.popUnsignedLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than unsigned type Byte.
 */
            case llcmpg_ub:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popUnsignedLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than unsigned type Byte.
 */
            case llucmpg_ub:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_8 a = stack.popUnsignedLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 equal with unsigned type Byte.
 */
            case llcmpe_ub:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popUnsignedLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 equal with unsigned type Byte.
 */
            case llucmpe_ub:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_8 a = stack.popUnsignedLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 less than or equal to unsigned type Byte.
 */
            case llcmple_ub:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popUnsignedLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than or equal to unsigned type Byte.
 */
            case llucmple_ub:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_8 a = stack.popUnsignedLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than or equal to unsigned type Byte.
 */
            case llcmpge_ub:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popUnsignedLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than or equal to unsigned type Byte.
 */
            case llucmpge_ub:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_8 a = stack.popUnsignedLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 not equal with unsigned type Byte.
 */
            case llcmpne_ub:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popUnsignedLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 not equal with unsigned type Byte.
 */
            case llucmpne_ub:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_8 a = stack.popUnsignedLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_256 with type Short.
 */
            case llmod_s:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a % b);
            }
                break;
/**
 * cast int_256 to unsigned type Short.
 */
            case llcast_us:
                stack.pushUnsignedShort(static_cast<uint_16> (stack.popLongLong()));
                break;
/**
 * cast unsigned uint_256 to unsigned type Short.
 */
            case llucast_us:
                stack.pushUnsignedShort(static_cast<uint_16> (stack.popUnsignedLongLong()));
                break;
/**
 * add int_256 with unsigned type Short.
 */
            case lladd_us:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_256 with unsigned type Short.
 */
            case lluadd_us:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_16 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a + b);
            }
                break;
/**
 * subtract int_256 with unsigned type Short.
 */
            case llsub_us:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_256 with unsigned type Short.
 */
            case llusub_us:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_16 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a - b);
            }
                break;
/**
 * multiply int_256 with unsigned type Short.
 */
            case llmul_us:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_256 with unsigned type Short.
 */
            case llumul_us:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_16 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a * b);
            }
                break;
/**
 * divide int_256 with unsigned type Short.
 */
            case lldiv_us:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_256 with unsigned type Short.
 */
            case lludiv_us:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_16 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a / b);
            }
                break;
/**
 * compare int_256 less than unsigned type Short.
 */
            case llcmpl_us:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popUnsignedLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than unsigned type Short.
 */
            case llucmpl_us:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_16 a = stack.popUnsignedLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than unsigned type Short.
 */
            case llcmpg_us:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popUnsignedLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than unsigned type Short.
 */
            case llucmpg_us:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_16 a = stack.popUnsignedLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 equal with unsigned type Short.
 */
            case llcmpe_us:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popUnsignedLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 equal with unsigned type Short.
 */
            case llucmpe_us:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_16 a = stack.popUnsignedLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 less than or equal to unsigned type Short.
 */
            case llcmple_us:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popUnsignedLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than or equal to unsigned type Short.
 */
            case llucmple_us:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_16 a = stack.popUnsignedLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than or equal to unsigned type Short.
 */
            case llcmpge_us:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popUnsignedLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than or equal to unsigned type Short.
 */
            case llucmpge_us:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_16 a = stack.popUnsignedLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 not equal with unsigned type Short.
 */
            case llcmpne_us:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popUnsignedLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 not equal with unsigned type Short.
 */
            case llucmpne_us:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_16 a = stack.popUnsignedLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_256 with type Int.
 */
            case llmod_i:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a % b);
            }
                break;
/**
 * cast int_256 to unsigned type Int.
 */
            case llcast_ui:
                stack.pushUnsignedInt(static_cast<uint_32> (stack.popLongLong()));
                break;
/**
 * cast unsigned uint_256 to unsigned type Int.
 */
            case llucast_ui:
                stack.pushUnsignedInt(static_cast<uint_32> (stack.popUnsignedLongLong()));
                break;
/**
 * add int_256 with unsigned type Int.
 */
            case lladd_ui:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_256 with unsigned type Int.
 */
            case lluadd_ui:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_32 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a + b);
            }
                break;
/**
 * subtract int_256 with unsigned type Int.
 */
            case llsub_ui:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_256 with unsigned type Int.
 */
            case llusub_ui:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_32 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a - b);
            }
                break;
/**
 * multiply int_256 with unsigned type Int.
 */
            case llmul_ui:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_256 with unsigned type Int.
 */
            case llumul_ui:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_32 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a * b);
            }
                break;
/**
 * divide int_256 with unsigned type Int.
 */
            case lldiv_ui:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_256 with unsigned type Int.
 */
            case lludiv_ui:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_32 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a / b);
            }
                break;
/**
 * compare int_256 less than unsigned type Int.
 */
            case llcmpl_ui:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popUnsignedLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than unsigned type Int.
 */
            case llucmpl_ui:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_32 a = stack.popUnsignedLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than unsigned type Int.
 */
            case llcmpg_ui:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popUnsignedLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than unsigned type Int.
 */
            case llucmpg_ui:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_32 a = stack.popUnsignedLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 equal with unsigned type Int.
 */
            case llcmpe_ui:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popUnsignedLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 equal with unsigned type Int.
 */
            case llucmpe_ui:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_32 a = stack.popUnsignedLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 less than or equal to unsigned type Int.
 */
            case llcmple_ui:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popUnsignedLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than or equal to unsigned type Int.
 */
            case llucmple_ui:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_32 a = stack.popUnsignedLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than or equal to unsigned type Int.
 */
            case llcmpge_ui:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popUnsignedLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than or equal to unsigned type Int.
 */
            case llucmpge_ui:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_32 a = stack.popUnsignedLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 not equal with unsigned type Int.
 */
            case llcmpne_ui:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popUnsignedLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 not equal with unsigned type Int.
 */
            case llucmpne_ui:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_32 a = stack.popUnsignedLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_256 with type Long.
 */
            case llmod_l:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a % b);
            }
                break;
/**
 * cast int_256 to unsigned type Long.
 */
            case llcast_ul:
                stack.pushUnsignedLong(static_cast<uint_64> (stack.popLongLong()));
                break;
/**
 * cast unsigned uint_256 to unsigned type Long.
 */
            case llucast_ul:
                stack.pushUnsignedLong(static_cast<uint_64> (stack.popUnsignedLongLong()));
                break;
/**
 * add int_256 with unsigned type Long.
 */
            case lladd_ul:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_256 with unsigned type Long.
 */
            case lluadd_ul:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_64 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a + b);
            }
                break;
/**
 * subtract int_256 with unsigned type Long.
 */
            case llsub_ul:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_256 with unsigned type Long.
 */
            case llusub_ul:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_64 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a - b);
            }
                break;
/**
 * multiply int_256 with unsigned type Long.
 */
            case llmul_ul:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_256 with unsigned type Long.
 */
            case llumul_ul:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_64 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a * b);
            }
                break;
/**
 * divide int_256 with unsigned type Long.
 */
            case lldiv_ul:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_256 with unsigned type Long.
 */
            case lludiv_ul:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_64 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a / b);
            }
                break;
/**
 * compare int_256 less than unsigned type Long.
 */
            case llcmpl_ul:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popUnsignedLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than unsigned type Long.
 */
            case llucmpl_ul:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_64 a = stack.popUnsignedLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than unsigned type Long.
 */
            case llcmpg_ul:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popUnsignedLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than unsigned type Long.
 */
            case llucmpg_ul:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_64 a = stack.popUnsignedLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 equal with unsigned type Long.
 */
            case llcmpe_ul:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popUnsignedLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 equal with unsigned type Long.
 */
            case llucmpe_ul:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_64 a = stack.popUnsignedLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 less than or equal to unsigned type Long.
 */
            case llcmple_ul:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popUnsignedLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than or equal to unsigned type Long.
 */
            case llucmple_ul:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_64 a = stack.popUnsignedLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than or equal to unsigned type Long.
 */
            case llcmpge_ul:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popUnsignedLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than or equal to unsigned type Long.
 */
            case llucmpge_ul:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_64 a = stack.popUnsignedLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 not equal with unsigned type Long.
 */
            case llcmpne_ul:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popUnsignedLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 not equal with unsigned type Long.
 */
            case llucmpne_ul:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_64 a = stack.popUnsignedLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_256 with type LongInt.
 */
            case llmod_li:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a % b);
            }
                break;
/**
 * cast int_256 to unsigned type LongInt.
 */
            case llcast_uli:
                stack.pushUnsignedLongInt(static_cast<uint_128> (stack.popLongLong()));
                break;
/**
 * cast unsigned uint_256 to unsigned type LongInt.
 */
            case llucast_uli:
                stack.pushUnsignedLongInt(static_cast<uint_128> (stack.popUnsignedLongLong()));
                break;
/**
 * add int_256 with unsigned type LongInt.
 */
            case lladd_uli:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_256 with unsigned type LongInt.
 */
            case lluadd_uli:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_128 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a + b);
            }
                break;
/**
 * subtract int_256 with unsigned type LongInt.
 */
            case llsub_uli:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_256 with unsigned type LongInt.
 */
            case llusub_uli:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_128 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a - b);
            }
                break;
/**
 * multiply int_256 with unsigned type LongInt.
 */
            case llmul_uli:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_256 with unsigned type LongInt.
 */
            case llumul_uli:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_128 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a * b);
            }
                break;
/**
 * divide int_256 with unsigned type LongInt.
 */
            case lldiv_uli:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_256 with unsigned type LongInt.
 */
            case lludiv_uli:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_128 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a / b);
            }
                break;
/**
 * compare int_256 less than unsigned type LongInt.
 */
            case llcmpl_uli:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popUnsignedLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than unsigned type LongInt.
 */
            case llucmpl_uli:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_128 a = stack.popUnsignedLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than unsigned type LongInt.
 */
            case llcmpg_uli:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popUnsignedLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than unsigned type LongInt.
 */
            case llucmpg_uli:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_128 a = stack.popUnsignedLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 equal with unsigned type LongInt.
 */
            case llcmpe_uli:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popUnsignedLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 equal with unsigned type LongInt.
 */
            case llucmpe_uli:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_128 a = stack.popUnsignedLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 less than or equal to unsigned type LongInt.
 */
            case llcmple_uli:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popUnsignedLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than or equal to unsigned type LongInt.
 */
            case llucmple_uli:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_128 a = stack.popUnsignedLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than or equal to unsigned type LongInt.
 */
            case llcmpge_uli:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popUnsignedLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than or equal to unsigned type LongInt.
 */
            case llucmpge_uli:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_128 a = stack.popUnsignedLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 not equal with unsigned type LongInt.
 */
            case llcmpne_uli:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popUnsignedLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 not equal with unsigned type LongInt.
 */
            case llucmpne_uli:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_128 a = stack.popUnsignedLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * modulo int_256 with type LongLong.
 */
            case llmod_ll:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a % b);
            }
                break;
/**
 * cast int_256 to unsigned type LongLong.
 */
            case llcast_ull:
                stack.pushUnsignedLongLong(static_cast<uint_256> (stack.popLongLong()));
                break;
/**
 * cast unsigned uint_256 to unsigned type LongLong.
 */
            case llucast_ull:
                stack.pushUnsignedLongLong(static_cast<uint_256> (stack.popUnsignedLongLong()));
                break;
/**
 * add int_256 with unsigned type LongLong.
 */
            case lladd_ull:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a + b);
            }
                break;
/**
 * add unsigned uint_256 with unsigned type LongLong.
 */
            case lluadd_ull:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a + b);
            }
                break;
/**
 * subtract int_256 with unsigned type LongLong.
 */
            case llsub_ull:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a - b);
            }
                break;
/**
 * subtract unsigned uint_256 with unsigned type LongLong.
 */
            case llusub_ull:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a - b);
            }
                break;
/**
 * multiply int_256 with unsigned type LongLong.
 */
            case llmul_ull:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a * b);
            }
                break;
/**
 * multiply unsigned uint_256 with unsigned type LongLong.
 */
            case llumul_ull:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a * b);
            }
                break;
/**
 * divide int_256 with unsigned type LongLong.
 */
            case lldiv_ull:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a / b);
            }
                break;
/**
 * divide unsigned uint_256 with unsigned type LongLong.
 */
            case lludiv_ull:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushUnsignedLongLong(a / b);
            }
                break;
/**
 * compare int_256 less than unsigned type LongLong.
 */
            case llcmpl_ull:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than unsigned type LongLong.
 */
            case llucmpl_ull:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a < b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than unsigned type LongLong.
 */
            case llcmpg_ull:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than unsigned type LongLong.
 */
            case llucmpg_ull:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a > b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 equal with unsigned type LongLong.
 */
            case llcmpe_ull:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 equal with unsigned type LongLong.
 */
            case llucmpe_ull:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a == b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 less than or equal to unsigned type LongLong.
 */
            case llcmple_ull:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 less than or equal to unsigned type LongLong.
 */
            case llucmple_ull:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a <= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 greater than or equal to unsigned type LongLong.
 */
            case llcmpge_ull:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 greater than or equal to unsigned type LongLong.
 */
            case llucmpge_ull:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a >= b) ? 1 : 0);
            }
                break;
/**
 * compare int_256 not equal with unsigned type LongLong.
 */
            case llcmpne_ull:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * compare unsigned uint_256 not equal with unsigned type LongLong.
 */
            case llucmpne_ull:
            {
                uint_256 b = stack.popUnsignedLongLong();
                int_256 a = stack.popUnsignedLongLong();
                stack.pushByte((a != b) ? 1 : 0);
            }
                break;
/**
 * bitwise and int_256 with type Byte.
 */
            case lland_b:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popByte();
                stack.pushLongLong(a & b);
            }
                break;
/**
 * bitwise or int_256 with type Byte.
 */
            case llor_b:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popByte();
                stack.pushLongLong(a | b);
            }
                break;
/**
 * bitwise xor int_256 with type Byte.
 */
            case llxor_b:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popByte();
                stack.pushLongLong(a ^ b);
            }
                break;
/**
 * shift right int_256 with type Byte.
 */
            case llshftr_b:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popByte();
                stack.pushLongLong(a >> b);
            }
                break;
/**
 * shift left xor int_256 with type Byte.
 */
            case llshftl_b:
            {
                int_256 b = stack.popLongLong();
                int_8 a = stack.popByte();
                stack.pushLongLong(a << b);
            }
                break;
/**
 * bitwise and int_256 with type Short.
 */
            case lland_s:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popShort();
                stack.pushLongLong(a & b);
            }
                break;
/**
 * bitwise or int_256 with type Short.
 */
            case llor_s:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popShort();
                stack.pushLongLong(a | b);
            }
                break;
/**
 * bitwise xor int_256 with type Short.
 */
            case llxor_s:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popShort();
                stack.pushLongLong(a ^ b);
            }
                break;
/**
 * shift right int_256 with type Short.
 */
            case llshftr_s:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popShort();
                stack.pushLongLong(a >> b);
            }
                break;
/**
 * shift left xor int_256 with type Short.
 */
            case llshftl_s:
            {
                int_256 b = stack.popLongLong();
                int_16 a = stack.popShort();
                stack.pushLongLong(a << b);
            }
                break;
/**
 * bitwise and int_256 with type Int.
 */
            case lland_i:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popInt();
                stack.pushLongLong(a & b);
            }
                break;
/**
 * bitwise or int_256 with type Int.
 */
            case llor_i:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popInt();
                stack.pushLongLong(a | b);
            }
                break;
/**
 * bitwise xor int_256 with type Int.
 */
            case llxor_i:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popInt();
                stack.pushLongLong(a ^ b);
            }
                break;
/**
 * shift right int_256 with type Int.
 */
            case llshftr_i:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popInt();
                stack.pushLongLong(a >> b);
            }
                break;
/**
 * shift left xor int_256 with type Int.
 */
            case llshftl_i:
            {
                int_256 b = stack.popLongLong();
                int_32 a = stack.popInt();
                stack.pushLongLong(a << b);
            }
                break;
/**
 * bitwise and int_256 with type Long.
 */
            case lland_l:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popLong();
                stack.pushLongLong(a & b);
            }
                break;
/**
 * bitwise or int_256 with type Long.
 */
            case llor_l:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popLong();
                stack.pushLongLong(a | b);
            }
                break;
/**
 * bitwise xor int_256 with type Long.
 */
            case llxor_l:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popLong();
                stack.pushLongLong(a ^ b);
            }
                break;
/**
 * shift right int_256 with type Long.
 */
            case llshftr_l:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popLong();
                stack.pushLongLong(a >> b);
            }
                break;
/**
 * shift left xor int_256 with type Long.
 */
            case llshftl_l:
            {
                int_256 b = stack.popLongLong();
                int_64 a = stack.popLong();
                stack.pushLongLong(a << b);
            }
                break;
/**
 * bitwise and int_256 with type LongInt.
 */
            case lland_li:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popLongInt();
                stack.pushLongLong(a & b);
            }
                break;
/**
 * bitwise or int_256 with type LongInt.
 */
            case llor_li:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popLongInt();
                stack.pushLongLong(a | b);
            }
                break;
/**
 * bitwise xor int_256 with type LongInt.
 */
            case llxor_li:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popLongInt();
                stack.pushLongLong(a ^ b);
            }
                break;
/**
 * shift right int_256 with type LongInt.
 */
            case llshftr_li:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popLongInt();
                stack.pushLongLong(a >> b);
            }
                break;
/**
 * shift left xor int_256 with type LongInt.
 */
            case llshftl_li:
            {
                int_256 b = stack.popLongLong();
                int_128 a = stack.popLongInt();
                stack.pushLongLong(a << b);
            }
                break;
/**
 * bitwise and int_256 with type LongLong.
 */
            case lland_ll:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a & b);
            }
                break;
/**
 * bitwise or int_256 with type LongLong.
 */
            case llor_ll:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a | b);
            }
                break;
/**
 * bitwise xor int_256 with type LongLong.
 */
            case llxor_ll:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a ^ b);
            }
                break;
/**
 * shift right int_256 with type LongLong.
 */
            case llshftr_ll:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a >> b);
            }
                break;
/**
 * shift left xor int_256 with type LongLong.
 */
            case llshftl_ll:
            {
                int_256 b = stack.popLongLong();
                int_256 a = stack.popLongLong();
                stack.pushLongLong(a << b);
            }
                break;
/**
 * duplicate a int_256 on the stack.
 */
            case lldup:
                stack.pushLongLong(stack.peekLongLong());
                break;
/**
 * duplicate a int_256 2 times on the stack.
 */
            case lldup2:
                stack.pushLongLong(stack.peekLongLong());stack.pushLongLong(stack.peekLongLong());
                break;
/**
 * duplicate a int_256 3 times on the stack.
 */
            case lldup3:
                stack.pushLongLong(stack.peekLongLong());stack.pushLongLong(stack.peekLongLong());stack.pushLongLong(stack.peekLongLong());
                break;
/**
 * duplicate a int_256 4 times on the stack.
 */
            case lldup4:
                stack.pushLongLong(stack.peekLongLong());stack.pushLongLong(stack.peekLongLong());stack.pushLongLong(stack.peekLongLong());stack.pushLongLong(stack.peekLongLong());
                break;
/**
 * duplicate a int_256 5 times on the stack.
 */
            case lldup5:
                stack.pushLongLong(stack.peekLongLong());stack.pushLongLong(stack.peekLongLong());stack.pushLongLong(stack.peekLongLong());stack.pushLongLong(stack.peekLongLong());stack.pushLongLong(stack.peekLongLong());
                break;
/**
 * set a int_256 from stack into a field on base pointer.
 */
            case llset:
                accessMemoryAndSetLongLong(base, ops.getUnsignedInt(), stack.popLongLong());
                break;
/**
 * get a int_256 from a field on base pointer to stack.
 */
            case llget:
                stack.pushLongLong(accessMemoryAndGetLongLong(base, ops.getUnsignedInt()));
                break;
/**
 * set a int_256 from value into a field on base pointer.
 */
            case llvset:
                accessMemoryAndSetLongLong(base, ops.getUnsignedInt(), ops.getLongLong());
                break;
/**
 * get a int_256 from a field on base pointer to stack using address from stack.
 */
            case llsget:
                stack.pushLongLong(accessMemoryAndGetLongLong(base, stack.popUnsignedInt()));
                break;
/**
 * set a int_256 from stack into a field on base pointer using address from stack.
 */
            case llsset:
                accessMemoryAndSetLongLong(base, stack.popUnsignedInt(), stack.popLongLong());
                break;
/**
 * set a int_256 from local variable into a field on base pointer.
 */
            case llsetl:
                accessMemoryAndSetLongLong(base, ops.getUnsignedInt(), lvt[ops.getUnsignedShort()].LongLong);
                break;
/**
 * increment int_256 by 1 on stack.
 */
            case llinc_1:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].LongLong = lvt[point].LongLong + 1; }
                break;
/**
 * increment int_256 by 2 on stack.
 */
            case llinc_2:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].LongLong = lvt[point].LongLong + 2; }
                break;
/**
 * increment int_256 by 1 on stack.
 */
            case llstinc_1:
                stack.pushLongLong(stack.popLongLong() + 1);
                break;
/**
 * increment int_256 by 2 on stack.
 */
            case llstinc_2:
                stack.pushLongLong(stack.popLongLong() + 2);
                break;
/**
 * return a int_256 into the main stack.
 */
            case llreturn:
                stack_main.pushLongLong(stack.popLongLong());
                break;
/**
 * store a int_256 from main stack in a local variable..
 */
            case llmainst:
                lvt[ops.getUnsignedShort()].LongLong = stack_main.popLongLong();
                break;
/**
 * store a int_256 from main stack in local variable 0.
 */
            case llmainst_0:
                lvt[0].LongLong = stack_main.popLongLong();;
                break;
/**
 * store a int_256 from main stack in local variable 1.
 */
            case llmainst_1:
                lvt[1].LongLong = stack_main.popLongLong();;
                break;
/**
 * store a int_256 from main stack in local variable 2.
 */
            case llmainst_2:
                lvt[2].LongLong = stack_main.popLongLong();;
                break;
/**
 * store a int_256 from main stack in local variable 3.
 */
            case llmainst_3:
                lvt[3].LongLong = stack_main.popLongLong();;
                break;
/**
 * print a int_256 from stack.
 */
            case llprint:
                log(std::to_string(stack.popLongLong()));
                break;
/**
 * print a unsigned uint_256 from stack.
 */
            case lluprint:
                log(std::to_string(stack.popUnsignedLongLong()));
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
 * load a flt_32 into the stack from local variable 0.
 */
            case fload_0:
                stack.pushFloat(lvt[0].Float);
                break;
/**
 * load a flt_32 into the stack from local variable 1.
 */
            case fload_1:
                stack.pushFloat(lvt[1].Float);
                break;
/**
 * load a flt_32 into the stack from local variable 2.
 */
            case fload_2:
                stack.pushFloat(lvt[2].Float);
                break;
/**
 * load a flt_32 into the stack from local variable 3.
 */
            case fload_3:
                stack.pushFloat(lvt[3].Float);
                break;
/**
 * load a flt_32 into the stack from local variable 4.
 */
            case fload_4:
                stack.pushFloat(lvt[4].Float);
                break;
/**
 * store a flt_32 from stack into local variable.
 */
            case fstore:
                lvt[ops.getUnsignedShort()] = lve_Float(stack.popFloat());
                break;
/**
 * store a flt_32 from stack into local variable 0.
 */
            case fstore_0:
                lvt[0] = lve_Float(stack.popFloat());
                break;
/**
 * store a flt_32 from stack into local variable 1.
 */
            case fstore_1:
                lvt[1] = lve_Float(stack.popFloat());
                break;
/**
 * store a flt_32 from stack into local variable 2.
 */
            case fstore_2:
                lvt[2] = lve_Float(stack.popFloat());
                break;
/**
 * store a flt_32 from stack into local variable 3.
 */
            case fstore_3:
                lvt[3] = lve_Float(stack.popFloat());
                break;
/**
 * store a flt_32 from stack into local variable 4.
 */
            case fstore_4:
                lvt[4] = lve_Float(stack.popFloat());
                break;
/**
 * duplicate a flt_32 on the stack.
 */
            case fdup:
                stack.pushFloat(stack.peekFloat());
                break;
/**
 * duplicate a flt_32 2 times on the stack.
 */
            case fdup2:
                stack.pushFloat(stack.peekFloat());stack.pushFloat(stack.peekFloat());
                break;
/**
 * duplicate a flt_32 3 times on the stack.
 */
            case fdup3:
                stack.pushFloat(stack.peekFloat());stack.pushFloat(stack.peekFloat());stack.pushFloat(stack.peekFloat());
                break;
/**
 * duplicate a flt_32 4 times on the stack.
 */
            case fdup4:
                stack.pushFloat(stack.peekFloat());stack.pushFloat(stack.peekFloat());stack.pushFloat(stack.peekFloat());stack.pushFloat(stack.peekFloat());
                break;
/**
 * duplicate a flt_32 5 times on the stack.
 */
            case fdup5:
                stack.pushFloat(stack.peekFloat());stack.pushFloat(stack.peekFloat());stack.pushFloat(stack.peekFloat());stack.pushFloat(stack.peekFloat());stack.pushFloat(stack.peekFloat());
                break;
/**
 * set a flt_32 from stack into a field on base pointer.
 */
            case fset:
                accessMemoryAndSetFloat(base, ops.getUnsignedInt(), stack.popFloat());
                break;
/**
 * get a flt_32 from a field on base pointer to stack.
 */
            case fget:
                stack.pushFloat(accessMemoryAndGetFloat(base, ops.getUnsignedInt()));
                break;
/**
 * set a flt_32 from value into a field on base pointer.
 */
            case fvset:
                accessMemoryAndSetFloat(base, ops.getUnsignedInt(), ops.getFloat());
                break;
/**
 * get a flt_32 from a field on base pointer to stack using address from stack.
 */
            case fsget:
                stack.pushFloat(accessMemoryAndGetFloat(base, stack.popUnsignedInt()));
                break;
/**
 * set a flt_32 from stack into a field on base pointer using address from stack.
 */
            case fsset:
                accessMemoryAndSetFloat(base, stack.popUnsignedInt(), stack.popFloat());
                break;
/**
 * set a flt_32 from local variable into a field on base pointer.
 */
            case fsetl:
                accessMemoryAndSetFloat(base, ops.getUnsignedInt(), lvt[ops.getUnsignedShort()].Float);
                break;
/**
 * increment flt_32 by 1 on stack.
 */
            case finc_1:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].Float = lvt[point].Float + 1; }
                break;
/**
 * increment flt_32 by 2 on stack.
 */
            case finc_2:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].Float = lvt[point].Float + 2; }
                break;
/**
 * increment flt_32 by 1 on stack.
 */
            case fstinc_1:
                stack.pushFloat(stack.popFloat() + 1);
                break;
/**
 * increment flt_32 by 2 on stack.
 */
            case fstinc_2:
                stack.pushFloat(stack.popFloat() + 2);
                break;
/**
 * return a flt_32 into the main stack.
 */
            case freturn:
                stack_main.pushFloat(stack.popFloat());
                break;
/**
 * store a flt_32 from main stack in a local variable..
 */
            case fmainst:
                lvt[ops.getUnsignedShort()].Float = stack_main.popFloat();
                break;
/**
 * store a flt_32 from main stack in local variable 0.
 */
            case fmainst_0:
                lvt[0].Float = stack_main.popFloat();;
                break;
/**
 * store a flt_32 from main stack in local variable 1.
 */
            case fmainst_1:
                lvt[1].Float = stack_main.popFloat();;
                break;
/**
 * store a flt_32 from main stack in local variable 2.
 */
            case fmainst_2:
                lvt[2].Float = stack_main.popFloat();;
                break;
/**
 * store a flt_32 from main stack in local variable 3.
 */
            case fmainst_3:
                lvt[3].Float = stack_main.popFloat();;
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
 * load a flt_64 into the stack from local variable 0.
 */
            case dload_0:
                stack.pushDouble(lvt[0].Double);
                break;
/**
 * load a flt_64 into the stack from local variable 1.
 */
            case dload_1:
                stack.pushDouble(lvt[1].Double);
                break;
/**
 * load a flt_64 into the stack from local variable 2.
 */
            case dload_2:
                stack.pushDouble(lvt[2].Double);
                break;
/**
 * load a flt_64 into the stack from local variable 3.
 */
            case dload_3:
                stack.pushDouble(lvt[3].Double);
                break;
/**
 * load a flt_64 into the stack from local variable 4.
 */
            case dload_4:
                stack.pushDouble(lvt[4].Double);
                break;
/**
 * store a flt_64 from stack into local variable.
 */
            case dstore:
                lvt[ops.getUnsignedShort()] = lve_Double(stack.popDouble());
                break;
/**
 * store a flt_64 from stack into local variable 0.
 */
            case dstore_0:
                lvt[0] = lve_Double(stack.popDouble());
                break;
/**
 * store a flt_64 from stack into local variable 1.
 */
            case dstore_1:
                lvt[1] = lve_Double(stack.popDouble());
                break;
/**
 * store a flt_64 from stack into local variable 2.
 */
            case dstore_2:
                lvt[2] = lve_Double(stack.popDouble());
                break;
/**
 * store a flt_64 from stack into local variable 3.
 */
            case dstore_3:
                lvt[3] = lve_Double(stack.popDouble());
                break;
/**
 * store a flt_64 from stack into local variable 4.
 */
            case dstore_4:
                lvt[4] = lve_Double(stack.popDouble());
                break;
/**
 * duplicate a flt_64 on the stack.
 */
            case ddup:
                stack.pushDouble(stack.peekDouble());
                break;
/**
 * duplicate a flt_64 2 times on the stack.
 */
            case ddup2:
                stack.pushDouble(stack.peekDouble());stack.pushDouble(stack.peekDouble());
                break;
/**
 * duplicate a flt_64 3 times on the stack.
 */
            case ddup3:
                stack.pushDouble(stack.peekDouble());stack.pushDouble(stack.peekDouble());stack.pushDouble(stack.peekDouble());
                break;
/**
 * duplicate a flt_64 4 times on the stack.
 */
            case ddup4:
                stack.pushDouble(stack.peekDouble());stack.pushDouble(stack.peekDouble());stack.pushDouble(stack.peekDouble());stack.pushDouble(stack.peekDouble());
                break;
/**
 * duplicate a flt_64 5 times on the stack.
 */
            case ddup5:
                stack.pushDouble(stack.peekDouble());stack.pushDouble(stack.peekDouble());stack.pushDouble(stack.peekDouble());stack.pushDouble(stack.peekDouble());stack.pushDouble(stack.peekDouble());
                break;
/**
 * set a flt_64 from stack into a field on base pointer.
 */
            case dset:
                accessMemoryAndSetDouble(base, ops.getUnsignedInt(), stack.popDouble());
                break;
/**
 * get a flt_64 from a field on base pointer to stack.
 */
            case dget:
                stack.pushDouble(accessMemoryAndGetDouble(base, ops.getUnsignedInt()));
                break;
/**
 * set a flt_64 from value into a field on base pointer.
 */
            case dvset:
                accessMemoryAndSetDouble(base, ops.getUnsignedInt(), ops.getDouble());
                break;
/**
 * get a flt_64 from a field on base pointer to stack using address from stack.
 */
            case dsget:
                stack.pushDouble(accessMemoryAndGetDouble(base, stack.popUnsignedInt()));
                break;
/**
 * set a flt_64 from stack into a field on base pointer using address from stack.
 */
            case dsset:
                accessMemoryAndSetDouble(base, stack.popUnsignedInt(), stack.popDouble());
                break;
/**
 * set a flt_64 from local variable into a field on base pointer.
 */
            case dsetl:
                accessMemoryAndSetDouble(base, ops.getUnsignedInt(), lvt[ops.getUnsignedShort()].Double);
                break;
/**
 * increment flt_64 by 1 on stack.
 */
            case dinc_1:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].Double = lvt[point].Double + 1; }
                break;
/**
 * increment flt_64 by 2 on stack.
 */
            case dinc_2:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].Double = lvt[point].Double + 2; }
                break;
/**
 * increment flt_64 by 1 on stack.
 */
            case dstinc_1:
                stack.pushDouble(stack.popDouble() + 1);
                break;
/**
 * increment flt_64 by 2 on stack.
 */
            case dstinc_2:
                stack.pushDouble(stack.popDouble() + 2);
                break;
/**
 * return a flt_64 into the main stack.
 */
            case dreturn:
                stack_main.pushDouble(stack.popDouble());
                break;
/**
 * store a flt_64 from main stack in a local variable..
 */
            case dmainst:
                lvt[ops.getUnsignedShort()].Double = stack_main.popDouble();
                break;
/**
 * store a flt_64 from main stack in local variable 0.
 */
            case dmainst_0:
                lvt[0].Double = stack_main.popDouble();;
                break;
/**
 * store a flt_64 from main stack in local variable 1.
 */
            case dmainst_1:
                lvt[1].Double = stack_main.popDouble();;
                break;
/**
 * store a flt_64 from main stack in local variable 2.
 */
            case dmainst_2:
                lvt[2].Double = stack_main.popDouble();;
                break;
/**
 * store a flt_64 from main stack in local variable 3.
 */
            case dmainst_3:
                lvt[3].Double = stack_main.popDouble();;
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
 * load a flt_128 into the stack from local variable 0.
 */
            case dfload_0:
                stack.pushDoubleFloat(lvt[0].DoubleFloat);
                break;
/**
 * load a flt_128 into the stack from local variable 1.
 */
            case dfload_1:
                stack.pushDoubleFloat(lvt[1].DoubleFloat);
                break;
/**
 * load a flt_128 into the stack from local variable 2.
 */
            case dfload_2:
                stack.pushDoubleFloat(lvt[2].DoubleFloat);
                break;
/**
 * load a flt_128 into the stack from local variable 3.
 */
            case dfload_3:
                stack.pushDoubleFloat(lvt[3].DoubleFloat);
                break;
/**
 * load a flt_128 into the stack from local variable 4.
 */
            case dfload_4:
                stack.pushDoubleFloat(lvt[4].DoubleFloat);
                break;
/**
 * store a flt_128 from stack into local variable.
 */
            case dfstore:
                lvt[ops.getUnsignedShort()] = lve_DoubleFloat(stack.popDoubleFloat());
                break;
/**
 * store a flt_128 from stack into local variable 0.
 */
            case dfstore_0:
                lvt[0] = lve_DoubleFloat(stack.popDoubleFloat());
                break;
/**
 * store a flt_128 from stack into local variable 1.
 */
            case dfstore_1:
                lvt[1] = lve_DoubleFloat(stack.popDoubleFloat());
                break;
/**
 * store a flt_128 from stack into local variable 2.
 */
            case dfstore_2:
                lvt[2] = lve_DoubleFloat(stack.popDoubleFloat());
                break;
/**
 * store a flt_128 from stack into local variable 3.
 */
            case dfstore_3:
                lvt[3] = lve_DoubleFloat(stack.popDoubleFloat());
                break;
/**
 * store a flt_128 from stack into local variable 4.
 */
            case dfstore_4:
                lvt[4] = lve_DoubleFloat(stack.popDoubleFloat());
                break;
/**
 * duplicate a flt_128 on the stack.
 */
            case dfdup:
                stack.pushDoubleFloat(stack.peekDoubleFloat());
                break;
/**
 * duplicate a flt_128 2 times on the stack.
 */
            case dfdup2:
                stack.pushDoubleFloat(stack.peekDoubleFloat());stack.pushDoubleFloat(stack.peekDoubleFloat());
                break;
/**
 * duplicate a flt_128 3 times on the stack.
 */
            case dfdup3:
                stack.pushDoubleFloat(stack.peekDoubleFloat());stack.pushDoubleFloat(stack.peekDoubleFloat());stack.pushDoubleFloat(stack.peekDoubleFloat());
                break;
/**
 * duplicate a flt_128 4 times on the stack.
 */
            case dfdup4:
                stack.pushDoubleFloat(stack.peekDoubleFloat());stack.pushDoubleFloat(stack.peekDoubleFloat());stack.pushDoubleFloat(stack.peekDoubleFloat());stack.pushDoubleFloat(stack.peekDoubleFloat());
                break;
/**
 * duplicate a flt_128 5 times on the stack.
 */
            case dfdup5:
                stack.pushDoubleFloat(stack.peekDoubleFloat());stack.pushDoubleFloat(stack.peekDoubleFloat());stack.pushDoubleFloat(stack.peekDoubleFloat());stack.pushDoubleFloat(stack.peekDoubleFloat());stack.pushDoubleFloat(stack.peekDoubleFloat());
                break;
/**
 * set a flt_128 from stack into a field on base pointer.
 */
            case dfset:
                accessMemoryAndSetDoubleFloat(base, ops.getUnsignedInt(), stack.popDoubleFloat());
                break;
/**
 * get a flt_128 from a field on base pointer to stack.
 */
            case dfget:
                stack.pushDoubleFloat(accessMemoryAndGetDoubleFloat(base, ops.getUnsignedInt()));
                break;
/**
 * set a flt_128 from value into a field on base pointer.
 */
            case dfvset:
                accessMemoryAndSetDoubleFloat(base, ops.getUnsignedInt(), ops.getDoubleFloat());
                break;
/**
 * get a flt_128 from a field on base pointer to stack using address from stack.
 */
            case dfsget:
                stack.pushDoubleFloat(accessMemoryAndGetDoubleFloat(base, stack.popUnsignedInt()));
                break;
/**
 * set a flt_128 from stack into a field on base pointer using address from stack.
 */
            case dfsset:
                accessMemoryAndSetDoubleFloat(base, stack.popUnsignedInt(), stack.popDoubleFloat());
                break;
/**
 * set a flt_128 from local variable into a field on base pointer.
 */
            case dfsetl:
                accessMemoryAndSetDoubleFloat(base, ops.getUnsignedInt(), lvt[ops.getUnsignedShort()].DoubleFloat);
                break;
/**
 * increment flt_128 by 1 on stack.
 */
            case dfinc_1:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].DoubleFloat = lvt[point].DoubleFloat + 1; }
                break;
/**
 * increment flt_128 by 2 on stack.
 */
            case dfinc_2:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].DoubleFloat = lvt[point].DoubleFloat + 2; }
                break;
/**
 * increment flt_128 by 1 on stack.
 */
            case dfstinc_1:
                stack.pushDoubleFloat(stack.popDoubleFloat() + 1);
                break;
/**
 * increment flt_128 by 2 on stack.
 */
            case dfstinc_2:
                stack.pushDoubleFloat(stack.popDoubleFloat() + 2);
                break;
/**
 * return a flt_128 into the main stack.
 */
            case dfreturn:
                stack_main.pushDoubleFloat(stack.popDoubleFloat());
                break;
/**
 * store a flt_128 from main stack in a local variable..
 */
            case dfmainst:
                lvt[ops.getUnsignedShort()].DoubleFloat = stack_main.popDoubleFloat();
                break;
/**
 * store a flt_128 from main stack in local variable 0.
 */
            case dfmainst_0:
                lvt[0].DoubleFloat = stack_main.popDoubleFloat();;
                break;
/**
 * store a flt_128 from main stack in local variable 1.
 */
            case dfmainst_1:
                lvt[1].DoubleFloat = stack_main.popDoubleFloat();;
                break;
/**
 * store a flt_128 from main stack in local variable 2.
 */
            case dfmainst_2:
                lvt[2].DoubleFloat = stack_main.popDoubleFloat();;
                break;
/**
 * store a flt_128 from main stack in local variable 3.
 */
            case dfmainst_3:
                lvt[3].DoubleFloat = stack_main.popDoubleFloat();;
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
 * load a flt_256 into the stack from local variable 0.
 */
            case ddload_0:
                stack.pushDoubleDouble(lvt[0].DoubleDouble);
                break;
/**
 * load a flt_256 into the stack from local variable 1.
 */
            case ddload_1:
                stack.pushDoubleDouble(lvt[1].DoubleDouble);
                break;
/**
 * load a flt_256 into the stack from local variable 2.
 */
            case ddload_2:
                stack.pushDoubleDouble(lvt[2].DoubleDouble);
                break;
/**
 * load a flt_256 into the stack from local variable 3.
 */
            case ddload_3:
                stack.pushDoubleDouble(lvt[3].DoubleDouble);
                break;
/**
 * load a flt_256 into the stack from local variable 4.
 */
            case ddload_4:
                stack.pushDoubleDouble(lvt[4].DoubleDouble);
                break;
/**
 * store a flt_256 from stack into local variable.
 */
            case ddstore:
                lvt[ops.getUnsignedShort()] = lve_DoubleDouble(stack.popDoubleDouble());
                break;
/**
 * store a flt_256 from stack into local variable 0.
 */
            case ddstore_0:
                lvt[0] = lve_DoubleDouble(stack.popDoubleDouble());
                break;
/**
 * store a flt_256 from stack into local variable 1.
 */
            case ddstore_1:
                lvt[1] = lve_DoubleDouble(stack.popDoubleDouble());
                break;
/**
 * store a flt_256 from stack into local variable 2.
 */
            case ddstore_2:
                lvt[2] = lve_DoubleDouble(stack.popDoubleDouble());
                break;
/**
 * store a flt_256 from stack into local variable 3.
 */
            case ddstore_3:
                lvt[3] = lve_DoubleDouble(stack.popDoubleDouble());
                break;
/**
 * store a flt_256 from stack into local variable 4.
 */
            case ddstore_4:
                lvt[4] = lve_DoubleDouble(stack.popDoubleDouble());
                break;
/**
 * duplicate a flt_256 on the stack.
 */
            case dddup:
                stack.pushDoubleDouble(stack.peekDoubleDouble());
                break;
/**
 * duplicate a flt_256 2 times on the stack.
 */
            case dddup2:
                stack.pushDoubleDouble(stack.peekDoubleDouble());stack.pushDoubleDouble(stack.peekDoubleDouble());
                break;
/**
 * duplicate a flt_256 3 times on the stack.
 */
            case dddup3:
                stack.pushDoubleDouble(stack.peekDoubleDouble());stack.pushDoubleDouble(stack.peekDoubleDouble());stack.pushDoubleDouble(stack.peekDoubleDouble());
                break;
/**
 * duplicate a flt_256 4 times on the stack.
 */
            case dddup4:
                stack.pushDoubleDouble(stack.peekDoubleDouble());stack.pushDoubleDouble(stack.peekDoubleDouble());stack.pushDoubleDouble(stack.peekDoubleDouble());stack.pushDoubleDouble(stack.peekDoubleDouble());
                break;
/**
 * duplicate a flt_256 5 times on the stack.
 */
            case dddup5:
                stack.pushDoubleDouble(stack.peekDoubleDouble());stack.pushDoubleDouble(stack.peekDoubleDouble());stack.pushDoubleDouble(stack.peekDoubleDouble());stack.pushDoubleDouble(stack.peekDoubleDouble());stack.pushDoubleDouble(stack.peekDoubleDouble());
                break;
/**
 * set a flt_256 from stack into a field on base pointer.
 */
            case ddset:
                accessMemoryAndSetDoubleDouble(base, ops.getUnsignedInt(), stack.popDoubleDouble());
                break;
/**
 * get a flt_256 from a field on base pointer to stack.
 */
            case ddget:
                stack.pushDoubleDouble(accessMemoryAndGetDoubleDouble(base, ops.getUnsignedInt()));
                break;
/**
 * set a flt_256 from value into a field on base pointer.
 */
            case ddvset:
                accessMemoryAndSetDoubleDouble(base, ops.getUnsignedInt(), ops.getDoubleDouble());
                break;
/**
 * get a flt_256 from a field on base pointer to stack using address from stack.
 */
            case ddsget:
                stack.pushDoubleDouble(accessMemoryAndGetDoubleDouble(base, stack.popUnsignedInt()));
                break;
/**
 * set a flt_256 from stack into a field on base pointer using address from stack.
 */
            case ddsset:
                accessMemoryAndSetDoubleDouble(base, stack.popUnsignedInt(), stack.popDoubleDouble());
                break;
/**
 * set a flt_256 from local variable into a field on base pointer.
 */
            case ddsetl:
                accessMemoryAndSetDoubleDouble(base, ops.getUnsignedInt(), lvt[ops.getUnsignedShort()].DoubleDouble);
                break;
/**
 * increment flt_256 by 1 on stack.
 */
            case ddinc_1:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].DoubleDouble = lvt[point].DoubleDouble + 1; }
                break;
/**
 * increment flt_256 by 2 on stack.
 */
            case ddinc_2:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].DoubleDouble = lvt[point].DoubleDouble + 2; }
                break;
/**
 * increment flt_256 by 1 on stack.
 */
            case ddstinc_1:
                stack.pushDoubleDouble(stack.popDoubleDouble() + 1);
                break;
/**
 * increment flt_256 by 2 on stack.
 */
            case ddstinc_2:
                stack.pushDoubleDouble(stack.popDoubleDouble() + 2);
                break;
/**
 * return a flt_256 into the main stack.
 */
            case ddreturn:
                stack_main.pushDoubleDouble(stack.popDoubleDouble());
                break;
/**
 * store a flt_256 from main stack in a local variable..
 */
            case ddmainst:
                lvt[ops.getUnsignedShort()].DoubleDouble = stack_main.popDoubleDouble();
                break;
/**
 * store a flt_256 from main stack in local variable 0.
 */
            case ddmainst_0:
                lvt[0].DoubleDouble = stack_main.popDoubleDouble();;
                break;
/**
 * store a flt_256 from main stack in local variable 1.
 */
            case ddmainst_1:
                lvt[1].DoubleDouble = stack_main.popDoubleDouble();;
                break;
/**
 * store a flt_256 from main stack in local variable 2.
 */
            case ddmainst_2:
                lvt[2].DoubleDouble = stack_main.popDoubleDouble();;
                break;
/**
 * store a flt_256 from main stack in local variable 3.
 */
            case ddmainst_3:
                lvt[3].DoubleDouble = stack_main.popDoubleDouble();;
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
 * load a pointer into the stack from local variable 0.
 */
            case aload_0:
                stack.pushPointer(lvt[0].Pointer);
                break;
/**
 * load a pointer into the stack from local variable 1.
 */
            case aload_1:
                stack.pushPointer(lvt[1].Pointer);
                break;
/**
 * load a pointer into the stack from local variable 2.
 */
            case aload_2:
                stack.pushPointer(lvt[2].Pointer);
                break;
/**
 * load a pointer into the stack from local variable 3.
 */
            case aload_3:
                stack.pushPointer(lvt[3].Pointer);
                break;
/**
 * load a pointer into the stack from local variable 4.
 */
            case aload_4:
                stack.pushPointer(lvt[4].Pointer);
                break;
/**
 * store a pointer from stack into local variable.
 */
            case astore:
                lvt[ops.getUnsignedShort()] = lve_Pointer(stack.popPointer());
                break;
/**
 * store a pointer from stack into local variable 0.
 */
            case astore_0:
                lvt[0] = lve_Pointer(stack.popPointer());
                break;
/**
 * store a pointer from stack into local variable 1.
 */
            case astore_1:
                lvt[1] = lve_Pointer(stack.popPointer());
                break;
/**
 * store a pointer from stack into local variable 2.
 */
            case astore_2:
                lvt[2] = lve_Pointer(stack.popPointer());
                break;
/**
 * store a pointer from stack into local variable 3.
 */
            case astore_3:
                lvt[3] = lve_Pointer(stack.popPointer());
                break;
/**
 * store a pointer from stack into local variable 4.
 */
            case astore_4:
                lvt[4] = lve_Pointer(stack.popPointer());
                break;
/**
 * duplicate a pointer on the stack.
 */
            case adup:
                stack.pushPointer(stack.peekPointer());
                break;
/**
 * duplicate a pointer 2 times on the stack.
 */
            case adup2:
                stack.pushPointer(stack.peekPointer());stack.pushPointer(stack.peekPointer());
                break;
/**
 * duplicate a pointer 3 times on the stack.
 */
            case adup3:
                stack.pushPointer(stack.peekPointer());stack.pushPointer(stack.peekPointer());stack.pushPointer(stack.peekPointer());
                break;
/**
 * duplicate a pointer 4 times on the stack.
 */
            case adup4:
                stack.pushPointer(stack.peekPointer());stack.pushPointer(stack.peekPointer());stack.pushPointer(stack.peekPointer());stack.pushPointer(stack.peekPointer());
                break;
/**
 * duplicate a pointer 5 times on the stack.
 */
            case adup5:
                stack.pushPointer(stack.peekPointer());stack.pushPointer(stack.peekPointer());stack.pushPointer(stack.peekPointer());stack.pushPointer(stack.peekPointer());stack.pushPointer(stack.peekPointer());
                break;
/**
 * set a pointer from stack into a field on base pointer.
 */
            case aset:
                accessMemoryAndSetPointer(base, ops.getUnsignedInt(), stack.popPointer());
                break;
/**
 * get a pointer from a field on base pointer to stack.
 */
            case aget:
                stack.pushPointer(accessMemoryAndGetPointer(base, ops.getUnsignedInt()));
                break;
/**
 * set a pointer from value into a field on base pointer.
 */
            case avset:
                accessMemoryAndSetPointer(base, ops.getUnsignedInt(), ops.getPointer());
                break;
/**
 * get a pointer from a field on base pointer to stack using address from stack.
 */
            case asget:
                stack.pushPointer(accessMemoryAndGetPointer(base, stack.popUnsignedInt()));
                break;
/**
 * set a pointer from stack into a field on base pointer using address from stack.
 */
            case asset:
                accessMemoryAndSetPointer(base, stack.popUnsignedInt(), stack.popPointer());
                break;
/**
 * set a pointer from local variable into a field on base pointer.
 */
            case asetl:
                accessMemoryAndSetPointer(base, ops.getUnsignedInt(), lvt[ops.getUnsignedShort()].Pointer);
                break;
/**
 * increment pointer by 1 on stack.
 */
            case ainc_1:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].Pointer = lvt[point].Pointer + 1; }
                break;
/**
 * increment pointer by 2 on stack.
 */
            case ainc_2:
            { uint_16 point = ops.getUnsignedShort(); lvt[point].Pointer = lvt[point].Pointer + 2; }
                break;
/**
 * increment pointer by 1 on stack.
 */
            case astinc_1:
                stack.pushPointer(stack.popPointer() + 1);
                break;
/**
 * increment pointer by 2 on stack.
 */
            case astinc_2:
                stack.pushPointer(stack.popPointer() + 2);
                break;
/**
 * return a pointer into the main stack.
 */
            case areturn:
                stack_main.pushPointer(stack.popPointer());
                break;
/**
 * store a pointer from main stack in a local variable..
 */
            case amainst:
                lvt[ops.getUnsignedShort()].Pointer = stack_main.popPointer();
                break;
/**
 * store a pointer from main stack in local variable 0.
 */
            case amainst_0:
                lvt[0].Pointer = stack_main.popPointer();;
                break;
/**
 * store a pointer from main stack in local variable 1.
 */
            case amainst_1:
                lvt[1].Pointer = stack_main.popPointer();;
                break;
/**
 * store a pointer from main stack in local variable 2.
 */
            case amainst_2:
                lvt[2].Pointer = stack_main.popPointer();;
                break;
/**
 * store a pointer from main stack in local variable 3.
 */
            case amainst_3:
                lvt[3].Pointer = stack_main.popPointer();;
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

pointer Stack::peekPointer()
{
    return (pointer) (intptr_t) peekUnsignedLong();
}
