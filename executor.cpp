
#include <vector>
#include "executor.h"
#include <set>
#include <cmath>

bool Endianness;

// Created by Riverssen on 07.11.18.

#ifdef _DEBUG_

#ifndef __debugmaps__
#define __debugmaps__


#endif

#endif

//#define _DEBUG_

void MvM::execute(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Scope& parent, OP_STACK ops)
{
#ifdef _DEBUG_

    std::map<int, const char *> _dopmap_;

_dopmap_[7] = "add";
_dopmap_[11] = "sdiv";
_dopmap_[8] = "sub";
_dopmap_[9] = "mul";
_dopmap_[10] = "udiv";
_dopmap_[163] = "store";
_dopmap_[157] = "load";
_dopmap_[12] = "mod";
_dopmap_[103] = "liget";
_dopmap_[107] = "dfget";
_dopmap_[108] = "ddget";
_dopmap_[104] = "llget";
_dopmap_[105] = "fget";
_dopmap_[106] = "dget";
_dopmap_[48] = "push";
_dopmap_[99] = "bget";
_dopmap_[101] = "iget";
_dopmap_[102] = "lget";
_dopmap_[100] = "sget";
_dopmap_[95] = "dset";
_dopmap_[97] = "ddset";
_dopmap_[98] = "aget";
_dopmap_[96] = "dfset";
_dopmap_[91] = "lset";
_dopmap_[93] = "llset";
_dopmap_[94] = "fset";
_dopmap_[92] = "liset";
_dopmap_[87] = "aset";
_dopmap_[89] = "sset";
_dopmap_[90] = "iset";
_dopmap_[88] = "bset";
_dopmap_[173] = "inc";
_dopmap_[174] = "dec";
_dopmap_[3] = "invoke";
_dopmap_[72] = "dconst";
_dopmap_[154] = "mspsh";
_dopmap_[155] = "m2psh";
_dopmap_[156] = "m4psh";
_dopmap_[143] = "brnf";
_dopmap_[127] = "newline";
_dopmap_[142] = "brnt";
_dopmap_[128] = "negate";
_dopmap_[166] = "store_2";
_dopmap_[176] = "lddec";
_dopmap_[175] = "ldinc";
_dopmap_[167] = "store_3";
_dopmap_[168] = "store_4";
_dopmap_[159] = "load_1";
_dopmap_[160] = "load_2";
_dopmap_[165] = "store_1";
_dopmap_[164] = "store_0";
_dopmap_[161] = "load_3";
_dopmap_[162] = "load_4";
_dopmap_[130] = "cmpg";
_dopmap_[158] = "load_0";
_dopmap_[146] = "mark";
_dopmap_[138] = "ucmpge";
_dopmap_[144] = "jump";
_dopmap_[145] = "jmpm";
_dopmap_[33] = "fmul";
_dopmap_[34] = "fdiv";
_dopmap_[135] = "ucmpg";
_dopmap_[137] = "ucmple";
_dopmap_[136] = "ucmpe";
_dopmap_[131] = "cmpe";
_dopmap_[133] = "cmpge";
_dopmap_[134] = "ucmpl";
_dopmap_[132] = "cmple";
_dopmap_[31] = "fadd";
_dopmap_[129] = "cmpl";
_dopmap_[32] = "fsub";
_dopmap_[27] = "aret";
_dopmap_[29] = "mret2";
_dopmap_[30] = "mret4";
_dopmap_[28] = "mret";
_dopmap_[26] = "ret";
_dopmap_[5] = "invokedynamic";
_dopmap_[49] = "push_0";
_dopmap_[140] = "ifcmpl";
_dopmap_[141] = "ifcmpg";
_dopmap_[76] = "l2d";
_dopmap_[153] = "strprint";
_dopmap_[147] = "dcmp";
_dopmap_[149] = "cmpub";
_dopmap_[148] = "cmpb";
_dopmap_[4] = "invokespecial";
_dopmap_[139] = "ifcmpe";
_dopmap_[13] = "expt";
_dopmap_[38] = "bmul";
_dopmap_[39] = "bdiv";
_dopmap_[37] = "bsub";
_dopmap_[40] = "bsdiv";
_dopmap_[36] = "badd";
_dopmap_[16] = "_xor";
_dopmap_[14] = "_and";
_dopmap_[58] = "swap";
_dopmap_[25] = "blshift";
_dopmap_[20] = "band";
_dopmap_[24] = "brshift";
_dopmap_[23] = "bnot";
_dopmap_[22] = "bxor";
_dopmap_[150] = "strconst";
_dopmap_[21] = "bor";
_dopmap_[152] = "strload";
_dopmap_[17] = "_not";
_dopmap_[15] = "_or";
_dopmap_[35] = "fexp";
_dopmap_[151] = "strstore";
_dopmap_[70] = "llconst";
_dopmap_[69] = "liconst";
_dopmap_[44] = "dsub";
_dopmap_[6] = "invokeexternal";
_dopmap_[41] = "bmod";
_dopmap_[73] = "dfconst";
_dopmap_[47] = "dexp";
_dopmap_[43] = "dadd";
_dopmap_[45] = "dmul";
_dopmap_[18] = "rshift";
_dopmap_[42] = "bexp";
_dopmap_[74] = "ddconst";
_dopmap_[19] = "lshift";
_dopmap_[46] = "ddiv";
_dopmap_[55] = "dup";
_dopmap_[50] = "push_1";
_dopmap_[125] = "dfprint";
_dopmap_[123] = "fprint";
_dopmap_[112] = "cprint";
_dopmap_[85] = "ll2dd";
_dopmap_[121] = "uliprint";
_dopmap_[115] = "liprint";
_dopmap_[113] = "iprint";
_dopmap_[54] = "pop";
_dopmap_[110] = "bprint";
_dopmap_[111] = "sprint";
_dopmap_[109] = "aprint";
_dopmap_[126] = "ddprint";
_dopmap_[59] = "swap2";
_dopmap_[86] = "dd2ll";
_dopmap_[122] = "ullprint";
_dopmap_[124] = "dprint";
_dopmap_[118] = "usprint";
_dopmap_[120] = "uprint";
_dopmap_[119] = "uiprint";
_dopmap_[117] = "ubprint";
_dopmap_[116] = "llprint";
_dopmap_[114] = "print";
_dopmap_[82] = "l2ll";
_dopmap_[53] = "push_4";
_dopmap_[52] = "push_3";
_dopmap_[79] = "d2f";
_dopmap_[75] = "l2f";
_dopmap_[83] = "ll2l";
_dopmap_[84] = "li2l";
_dopmap_[81] = "l2li";
_dopmap_[80] = "d2l";
_dopmap_[78] = "f2l";
_dopmap_[77] = "f2d";
_dopmap_[51] = "push_2";
_dopmap_[60] = "swap3";
_dopmap_[71] = "fconst";
_dopmap_[61] = "swap4";
_dopmap_[1] = "timens";
_dopmap_[62] = "swap5";
_dopmap_[63] = "swap6";
_dopmap_[56] = "dup2";
_dopmap_[57] = "dup3";
_dopmap_[64] = "swap7";
_dopmap_[2] = "timems";
_dopmap_[0] = "func";
_dopmap_[177] = "halt";
_dopmap_[66] = "swap9";
_dopmap_[67] = "swapx";
_dopmap_[169] = "loadm2";
_dopmap_[172] = "storem4";
_dopmap_[171] = "storem2";
_dopmap_[170] = "loadm4";
_dopmap_[68] = "swapx1";
_dopmap_[65] = "swap8";

#endif
    Scope scope;
    pointer base = basePointer;

    while (ops.getRemaining() > 0)
    {
        Op undefined = ops.getOp();
#ifdef _DEBUG_
        std::cout << std::endl << _dopmap_[undefined] << " stack: " << scope.stack.stack.size() << std::endl;
#endif

        switch (undefined)
        {
            /**integer addition**/
            case add:
            {scope.pushLong(scope.popLong() + scope.popLong());}
                break;
                /**integer signed division**/
            case sdiv:
            {scope.pushLong(scope.popLong() / scope.popLong());}
                break;
                /**integer subtraction**/
            case sub:
            {scope.pushLong(scope.popLong() - scope.popLong());}
                break;
                /**integer multiplication**/
            case mul:
            {scope.pushLong(scope.popLong() * scope.popLong());}
                break;
                /**integer unsigned division**/
            case udiv:
            {scope.pushUnsignedLong(scope.popUnsignedLong() / scope.popUnsignedLong());}
                break;
                /**store max length data**/
            case store:
            {scope.store(ops.getUnsignedShort());}
                break;
                /**load max length data**/
            case load:
            {scope.load(ops.getUnsignedShort());}
                break;
                /**integer modulo**/
            case mod:
            {scope.pushLong(scope.popLong() / scope.popLong());}
                break;
                /**push long int from memory**/
            case liget:
            {scope.pushLongInt(accessMemoryAndGetLongInt(scope.popPointer(), scope.popUnsignedLong()));}
                break;
                /**push double float from memory**/
            case dfget:
            {scope.pushDoubleFloat(accessMemoryAndGetDoubleFloat(scope.popPointer(), scope.popUnsignedLong()));}
                break;
                /**push double double from memory**/
            case ddget:
            {scope.pushDoubleDouble(accessMemoryAndGetDoubleDouble(scope.popPointer(), scope.popUnsignedLong()));}
                break;
                /**push long long from mempory**/
            case llget:
            {scope.pushLongLong(accessMemoryAndGetLongLong(scope.popPointer(), scope.popUnsignedLong()));}
                break;
                /**push float from memory**/
            case fget:
            {scope.pushFloat(accessMemoryAndGetFloat(scope.popPointer(), scope.popUnsignedLong()));}
                break;
                /**push double from memory**/
            case dget:
            {scope.pushDouble(accessMemoryAndGetDouble(scope.popPointer(), scope.popUnsignedLong()));}
                break;
                /**push long data**/
            case push:
            {scope.pushLong(ops.getLong());}
                break;
                /**push byte from memory**/
            case bget:
            {scope.pushByte(accessMemoryAndGetByte(scope.popPointer(), scope.popUnsignedLong()));}
                break;
                /**push int from memory**/
            case iget:
            {scope.pushInt(accessMemoryAndGetInt(scope.popPointer(), scope.popUnsignedLong()));}
                break;
                /**push long from memory**/
            case lget:
            {scope.pushLong(accessMemoryAndGetLong(scope.popPointer(), scope.popUnsignedLong()));}
                break;
                /**push short from memory**/
            case sget:
            {scope.pushShort(accessMemoryAndGetShort(scope.popPointer(), scope.popUnsignedLong()));}
                break;
                /**set point in memory to a double**/
            case dset:
            {accessMemoryAndSetDouble(scope.popPointer(), scope.popUnsignedLong(), scope.popDouble());}
                break;
                /**set point in memory to a double double**/
            case ddset:
            {accessMemoryAndSetDoubleDouble(scope.popPointer(), scope.popUnsignedLong(), scope.popDoubleDouble());}
                break;
                /**push pointer from memory**/
            case aget:
            {scope.pushPointerUNSAFE(accessMemoryAndGetPointer(scope.popPointer(), scope.popUnsignedLong()));}
                break;
                /**set point in memory to a double float**/
            case dfset:
            {accessMemoryAndSetDoubleFloat(scope.popPointer(), scope.popUnsignedLong(), scope.popDoubleFloat());}
                break;
                /**set point in memory to a long**/
            case lset:
            {accessMemoryAndSetLong(scope.popPointer(), scope.popUnsignedLong(), scope.popLong());}
                break;
                /**set point in memory to a long long**/
            case llset:
            {accessMemoryAndSetLongLong(scope.popPointer(), scope.popUnsignedLong(), scope.popLongLong());}
                break;
                /**set point in memory to a float**/
            case fset:
            {accessMemoryAndSetFloat(scope.popPointer(), scope.popUnsignedLong(), scope.popFloat());}
                break;
                /**set point in memory to a long int**/
            case liset:
            {accessMemoryAndSetLongInt(scope.popPointer(), scope.popUnsignedLong(), scope.popLongInt());}
                break;
                /**set point in memory to a pointer**/
            case aset:
            {
                std::cerr<<"unsupported operation: 'aset'\n";
                exit(-12);
                accessMemoryAndSetPointer(scope.returnPointer().get(), scope.popUnsignedLong(), scope.popPointer());}
                break;
                /**set point in memory to a short**/
            case sset:
            {accessMemoryAndSetShort(scope.popPointer(), scope.popUnsignedLong(), scope.popShort());}
                break;
                /**set point in memory to an int**/
            case iset:
            {accessMemoryAndSetInt(scope.popPointer(), scope.popUnsignedLong(), scope.popInt());}
                break;
                /**set point in memory to a byte**/
            case bset:
            {accessMemoryAndSetByte(scope.popPointer(), scope.popUnsignedLong(), scope.popByte());}
                break;
                /**increment an integer**/
            case inc:
            {scope.pushLong(scope.popLong() + 1);}
                break;
                /**increment an integer**/
            case dec:
            {scope.pushLong(scope.popLong() - 1);}
                break;
                /**invoke a function (static or otherwise)] p=12 {execute(globalTable, nativeTable, globalPointer, basePointer, scope, globalTable[ops.getUnsignedLong()**/
            case invoke:
            {execute(globalTable, nativeTable, globalPointer, basePointer, scope, globalTable[ops.getUnsignedLong()]);}
                break;
                /**push a double**/
            case dconst:
            {scope.pushDouble(ops.getDouble());}
                break;
                /**push a max length value from parent scope**/
            case mspsh:
            {scope.pushLong(parent.popLong());}
                break;
                /**push two max length values from parent scope**/
            case m2psh:
            {scope.pushLongInt(parent.popLongInt());}
                break;
                /**push four max length values from parent scope**/
            case m4psh:
            {scope.pushLongLong(parent.popLongLong());}
                break;
                /**branch if false**/
            case brnf:
            {uint_32 j = ops.getUnsignedInt(); if (scope.popBool()) ops.address += j;}
                break;

            case newline:
            {std::cout << std::endl;}
                break;
                /**branch if true**/
            case brnt:
            {uint_32 j = ops.getUnsignedInt(); if (!scope.popBool()) ops.address += j;}
                break;
                /**negate a byte**/
            case negate:
            {scope.pushBool(!scope.popBool());}
                break;
                /**store max length data**/
            case store_2:
            {scope.store(2);}
                break;
                /**increment an integer in local var #**/
            case lddec:
            {uint_16 loc; scope.pushLong(scope.mloadLong(loc = ops.getUnsignedShort()) - 1); scope.store(loc);}
                break;
                /**increment an integer in local var #**/
            case ldinc:
            {uint_16 loc; scope.pushLong(scope.mloadLong(loc = ops.getUnsignedShort()) + 1); scope.store(loc);}
                break;
                /**store max length data**/
            case store_3:
            {scope.store(3);}
                break;
                /**store max length data**/
            case store_4:
            {scope.store(4);}
                break;
                /**load max length data**/
            case load_1:
            {scope.load(1);}
                break;
                /**load max length data**/
            case load_2:
            {scope.load(2);}
                break;
                /**store max length data**/
            case store_1:
            {scope.store(1);}
                break;
                /**store max length data**/
            case store_0:
            {scope.store(0);}
                break;
                /**load max length data**/
            case load_3:
            {scope.load(3);}
                break;
                /**load max length data**/
            case load_4:
            {scope.load(4);}
                break;
                /**compare greater**/
            case cmpg:
            {scope.pushBool(scope.popLong() > scope.popLong());}
                break;
                /**load max length data] p=11**/
            case load_0:
            {scope.load(0);}
                break;
                /**mark a check-point**/
            case mark:
            {scope.setCheckPoint(ops.getUnsignedShort(), ops.address);}
                break;
                /**compare greater or equal**/
            case ucmpge:
            {scope.pushBool(scope.popUnsignedLong() >= scope.popUnsignedLong());}
                break;
                /**jump to a point**/
            case jump:
            {ops.address = ops.getUnsignedLong();}
                break;
                /**jump to a marked point**/
            case jmpm:
            {ops.address = scope.getCheckPointer(ops.getUnsignedShort());}
                break;
                /**double multiplication**/
            case fmul:
            {scope.pushDouble(scope.popDouble() * scope.popDouble());}
                break;
                /**double division**/
            case fdiv:
            {scope.pushDouble(scope.popDouble() / scope.popDouble());}
                break;
                /**compare greater**/
            case ucmpg:
            {scope.pushBool(scope.popUnsignedLong() > scope.popUnsignedLong());}
                break;
                /**compare less or equal**/
            case ucmple:
            {scope.pushBool(scope.popUnsignedLong() <= scope.popUnsignedLong());}
                break;
                /**compare equal**/
            case ucmpe:
            {scope.pushBool(scope.popUnsignedLong() == scope.popUnsignedLong());}
                break;
                /**compare equal**/
            case cmpe:
            {scope.pushBool(scope.popLong() == scope.popLong());}
                break;
                /**compare greater or equal**/
            case cmpge:
            {scope.pushBool(scope.popLong() >= scope.popLong());}
                break;
                /**compare less**/
            case ucmpl:
            {scope.pushBool(scope.popUnsignedLong() < scope.popUnsignedLong());}
                break;
                /**compare less or equal**/
            case cmple:
            {scope.pushBool(scope.popLong() <= scope.popLong());}
                break;
                /**double addition**/
            case fadd:
            {scope.pushDouble(scope.popDouble() + scope.popDouble());}
                break;
                /**compare less**/
            case cmpl:
            {scope.pushBool(scope.popLong() < scope.popLong());}
                break;
                /**double subtraction**/
            case fsub:
            {scope.pushDouble(scope.popDouble() - scope.popDouble());}
                break;
                /**return a pointer**/
            case aret:
            {parent.pushPointerSAFE(scope.returnPointer()); return;}
                break;
                /**return two max_size elements (x128)**/
            case mret2:
            {parent.pushLongInt(scope.popLongInt()); return;}
                break;
                /**return four max_size elements (x256)**/
            case mret4:
            {parent.pushLongLong(scope.popLongLong()); return;}
                break;
                /**return max_size element**/
            case mret:
            {parent.pushLong(scope.popLong()); return;}
                break;
                /**return from scope**/
            case ret:
            {return;}
                break;
                /**invoke a function using a function pointer] p=10 {execute(globalTable, nativeTable, globalPointer, basePointer, scope, globalTable[scope.popUnsignedLong()**/
            case invokedynamic:
            {execute(globalTable, nativeTable, globalPointer, basePointer, scope, globalTable[scope.popUnsignedLong()]);}
                break;
                /**push 0L**/
            case push_0:
            {scope.pushLong(0);}
                break;

            case ifcmpl:
            {if (scope.popLong() > scope.popLong()) ops.address += ops.getUnsignedInt();}
                break;

            case ifcmpg:
            {if (scope.popLong() < scope.popLong()) ops.address += ops.getUnsignedInt();}
                break;
                /**cast long to short**/
            case l2d:
            {scope.pushDouble(static_cast<double> (scope.popLong()));}
                break;

            case strprint:
            {std::cout << ((mmstring*)scope.popPointer())->string;}
                break;
                /**compare two double doubles**/
            case dcmp:
            {}
                break;
                /**compare two unsigned long longs**/
            case cmpub:
            {}
                break;
                /**compare two long longs**/
            case cmpb:
            {}
                break;
                /**invoke a native function] p=10 {nativeTable[ops.getUnsignedLong()**/
            case invokespecial:
            {nativeTable[ops.getUnsignedLong()]->execute(globalTable, nativeTable, globalPointer, basePointer, scope.stack);}
                break;

            case ifcmpe:
            {if (scope.popLong() != scope.popLong()) ops.address += ops.getUnsignedInt();}
                break;
                /**integer pow(x, y)**/
            case expt:
            {scope.pushLong(pow(scope.popLong(), scope.popLong()));}
                break;
                /**x256 int multiplication**/
            case bmul:
            {scope.pushLongLong(scope.popLongLong() * scope.popLongLong());}
                break;
                /**x256 int unsigned division**/
            case bdiv:
            {scope.pushUnsignedLongLong(scope.popUnsignedLongLong() / scope.popUnsignedLongLong());}
                break;
                /**x256 int subtraction**/
            case bsub:
            {scope.pushLongLong(scope.popLongLong() - scope.popLongLong());}
                break;
                /**x256 int signed division**/
            case bsdiv:
            {scope.pushLongLong(scope.popLongLong() / scope.popLongLong());}
                break;
                /**x256 int addition**/
            case badd:
            {scope.pushLongLong(scope.popLongLong() + scope.popLongLong());}
                break;
                /**bitwise xor**/
            case _xor:
            {scope.pushLong(scope.popLong() ^ scope.popLong());}
                break;
                /**bitwise and**/
            case _and:
            {scope.pushLong(scope.popLong() & scope.popLong());}
                break;
                /**swap top 2 elements**/
            case swap:
            {scope.swap_1();}
                break;
                /**x256 left shift**/
            case blshift:
            {scope.pushLongLong(scope.popLongLong() << scope.popUnsignedByte());}
                break;
                /**x256 bitwise and**/
            case band:
            {scope.pushLongLong(scope.popLongLong() & scope.popLongLong());}
                break;
                /**x256 right shift**/
            case brshift:
            {scope.pushLongLong(scope.popLongLong() >> scope.popUnsignedByte());}
                break;
                /**x256 bitwise not**/
            case bnot:
            {scope.pushLongLong(~scope.popLongLong());}
                break;
                /**x256 bitwise xor**/
            case bxor:
            {scope.pushLongLong(scope.popLongLong() & scope.popLongLong());}
                break;

            case strconst:
            {scope.pushPointerSAFE(ops.getMMString());}
                break;
                /**x256 bitwise or**/
            case bor:
            {scope.pushLongLong(scope.popLongLong() | scope.popLongLong());}
                break;

            case strload:
            {scope.loadPointer(ops.getUnsignedShort());}
                break;
                /**bitwise not**/
            case _not:
            {scope.pushLong(~scope.popLong());}
                break;
                /**bitwise or**/
            case _or:
            {scope.pushLong(scope.popLong() | scope.popLong());}
                break;
                /**double pow(x, y)**/
            case fexp:
            {scope.pushDouble(pow(scope.popDouble(), scope.popDouble()));}
                break;

            case strstore:
            {scope.storePointer(ops.getUnsignedShort());}
                break;
                /**push a long long**/
            case llconst:
            {scope.pushLongLong(ops.getLongLong());}
                break;
                /**push a long int**/
            case liconst:
            {scope.pushLongInt(ops.getLongInt());}
                break;
                /**x256 double subtraction**/
            case dsub:
            {scope.pushDoubleDouble(scope.popDoubleDouble() - scope.popDoubleDouble());}
                break;
                /**invoke an external function from an online script**/
            case invokeexternal:
            {}
                break;
                /**x256 int modulo**/
            case bmod:
            {scope.pushLongLong(scope.popLongLong() % scope.popLongLong());}
                break;
                /**push a double float**/
            case dfconst:
            {scope.pushDoubleFloat(ops.getDoubleFloat());}
                break;
                /**x256 double division**/
            case dexp:
            {scope.pushDoubleDouble(pow_bigf(scope.popDoubleDouble(), scope.popDoubleDouble()));}
                break;
                /**x256 double addition**/
            case dadd:
            {scope.pushDoubleDouble(scope.popDoubleDouble() + scope.popDoubleDouble());}
                break;
                /**x256 double multiplication**/
            case dmul:
            {scope.pushDoubleDouble(scope.popDoubleDouble() * scope.popDoubleDouble());}
                break;
                /**right shift**/
            case rshift:
            {scope.pushLong(scope.popLong() >> scope.popUnsignedByte());}
                break;
                /**x256 int pow(x, y)**/
            case bexp:
            {scope.pushLongLong(pow_big(scope.popLongLong(), scope.popLongLong()));}
                break;
                /**push a double double**/
            case ddconst:
            {scope.pushDoubleDouble(ops.getDoubleDouble());}
                break;
                /**left shift**/
            case lshift:
            {scope.pushLong(scope.popLong() << scope.popUnsignedByte());}
                break;
                /**x256 double division**/
            case ddiv:
            {scope.pushDoubleDouble(scope.popDoubleDouble() / scope.popDoubleDouble());}
                break;
                /**duplicate a max element**/
            case dup:
            {scope.stack.pushLong(scope.stack.peekLong());}
                break;
                /**push 1L**/
            case push_1:
            {scope.pushLong(1);}
                break;

            case dfprint:
            {std::cout << scope.popDoubleFloat();}
                break;

            case fprint:
            {std::cout << scope.popFloat();}
                break;

            case cprint:
            {std::cout << (char) scope.popShort();}
                break;
                /**cast long to double double**/
            case ll2dd:
            {scope.pushDoubleDouble(static_cast<flt_256> (scope.popLongLong()));}
                break;

            case uliprint:
            {std::cout << scope.popUnsignedLongInt();}
                break;

            case liprint:
            {std::cout << scope.popLongInt();}
                break;

            case iprint:
            {std::cout << scope.popInt();}
                break;
                /**pop max element (x64)**/
            case pop:
            {scope.popLong();}
                break;

            case bprint:
            {std::cout << scope.popByte();}
                break;

            case sprint:
            {std::cout << scope.popShort();}
                break;

            case aprint:
            {std::cout << scope.popPointer();}
                break;

            case ddprint:
            {std::cout << scope.popDoubleDouble();}
                break;
                /**swap the first and 3rd elements**/
            case swap2:
            {scope.swap_2();}
                break;
                /**cast long to double double**/
            case dd2ll:
            {scope.pushLongLong(static_cast<int_256> (scope.popDoubleDouble()));}
                break;

            case ullprint:
            {std::cout << scope.popUnsignedLongLong();}
                break;

            case dprint:
            {std::cout << scope.popDouble();}
                break;

            case usprint:
            {std::cout << scope.popUnsignedShort();}
                break;

            case uprint:
            {std::cout << scope.popUnsignedLong();}
                break;

            case uiprint:
            {std::cout << scope.popUnsignedInt();}
                break;

            case ubprint:
            {std::cout << scope.popUnsignedByte();}
                break;

            case llprint:
            {std::cout << scope.popLongLong();}
                break;

            case print:
            {std::cout << scope.popLong();}
                break;
                /**cast long to long long**/
            case l2ll:
            {scope.pushLongLong(static_cast<int_256> (scope.popLong()));}
                break;
                /**push 4L**/
            case push_4:
            {scope.pushLong(4);}
                break;
                /**push 3L**/
            case push_3:
            {scope.pushLong(3);}
                break;
                /**cast double to float**/
            case d2f:
            {scope.pushFloat(static_cast<float> (scope.popDouble()));}
                break;
                /**cast long to byte**/
            case l2f:
            {scope.pushFloat(static_cast<float> (scope.popLong()));}
                break;
                /**cast long to long long**/
            case ll2l:
            {scope.pushLong(static_cast<long> (scope.popLongLong()));}
                break;
                /**cast long to long long**/
            case li2l:
            {scope.pushLong(static_cast<long> (scope.popLongInt()));}
                break;
                /**cast long to long int**/
            case l2li:
            {scope.pushLongInt(static_cast<int_128> (scope.popLong()));}
                break;
                /**cast double to long**/
            case d2l:
            {scope.pushLong(static_cast<long> (scope.popDouble()));}
                break;
                /**cast float to long**/
            case f2l:
            {scope.pushLong(static_cast<long> (scope.popFloat()));}
                break;
                /**cast float to double**/
            case f2d:
            {scope.pushDouble(static_cast<double> (scope.popFloat()));}
                break;
                /**push 2L**/
            case push_2:
            {scope.pushLong(2);}
                break;
                /**swap the first and 4th elements**/
            case swap3:
            {scope.swap_3();}
                break;
                /**push a double**/
            case fconst:
            {scope.pushDouble(static_cast<double> (ops.getFloat()));}
                break;
                /**swap the first and 5th elements**/
            case swap4:
            {scope.swap_4();}
                break;
                /**push time in nano seconds**/
            case timens:
            {scope.pushLong(gtimens());}
                break;
                /**swap the first and 6th elements**/
            case swap5:
            {scope.swap_5();}
                break;
                /**swap the first and 7th elements**/
            case swap6:
            {scope.swap_6();}
                break;
                /**duplicate a max element twice**/
            case dup2:
            {long l; scope.stack.pushLong((l = scope.stack.peekLong())); scope.stack.pushLong(l);}
                break;
                /**duplicate a max element twice**/
            case dup3:
            {long l; scope.stack.pushLong((l = scope.stack.peekLong())); scope.stack.pushLong(l); scope.stack.pushLong(l);}
                break;
                /**swap the first and 8th elements**/
            case swap7:
            {scope.swap_7();}
                break;
                /**push time in milliseconds**/
            case timems:
            {scope.pushLong(gtimems());}
                break;

            case halt:
            {exit(-1);}
                break;
                /**swap the first and 10th elements**/
            case swap9:
            {scope.swap_9();}
                break;
                /**swap the first and 11th elements**/
            case swapx:
            {scope.swap_x();}
                break;
                /**load two max length datas**/
            case loadm2:
            {scope.loadm2(ops.getUnsignedShort());}
                break;
                /**store four max length datas**/
            case storem4:
            {scope.storem4(ops.getUnsignedShort());}
                break;
                /**store two max length datas**/
            case storem2:
            {scope.storem2(ops.getUnsignedShort());}
                break;
                /**load four max length datas**/
            case loadm4:
            {scope.loadm4(ops.getUnsignedShort());}
                break;
                /**swap the first and 12th elements**/
            case swapx1:
            {scope.swap_x1();}
                break;
                /**swap the first and 9th elements**/
            case swap8:
            {scope.swap_8();}
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

int_256 MvM::pow_big(int_256 a, int_256 b)
{
    return 0;
}

flt_256 MvM::pow_bigf(flt_256 a, flt_256 b)
{
    return 0;
}

void MvM::accessExternalContract(MvM::SmartContract *contract)
{
}

pointer Stack::peekPointer()
{
    return (pointer) (intptr_t) peekUnsignedLong();
}
