
#include "executor.h"
#include "executorfuncs.h"

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
    pointer base = basePointer;
//    ops.address = 0;

    while (ops.getRemaining() > 0)
    {
        Op op_undefinedcurrent = ops.getOp();//ops.getOp();
//        std::cout << std::endl<< op_undefinedcurrent << " " << ops.address << " " << stack.stack.size() << std::endl;
//        implptr_t[op_undefinedcurrent]();

                (impl::impl_funcs[op_undefinedcurrent])
                        (globalTable, nativeTable, globalPointer, basePointer, stack_main, stack, ops,
                                lvt, CHECK_POINTS, base);
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
