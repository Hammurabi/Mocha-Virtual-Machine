#include <iostream>
#include <vector>

#include "src/vm_structs.h"
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>

uint_16 op(uint_16 o)
{
    EndianMachine e;
    if (e.isBigEndian())
        return o;

    return ((uint_16 *)((uint_8[2]) {((pointer) &o)[1], ((pointer) &o)[0]}))[0];
}

void loadDLLs(std::vector<env::n_func>& funcs, int count, const char** in)
{
    for (int i = 0; i < count; i ++)
    {
        if (strcmp(in[i], "-d") == 0)
        {
            if (i + 1 < count)
            {
                i ++;
            }
        }
    }
}

int main(int count, const char** in)
{
//    OP_STACK ops_(ops, 1);
//    stack potat;
//    pointer ptr = static_cast<pointer>(malloc(4));
//
//    potat.pushByte(3);
//    potat.pushPointer(ptr);
//    potat.pushByte(24);
//
////    alu::subtractors[unsigned_bit](potat);
//
//    mem::init();
//
//
//    melement_t e(0.4);
//
//    mem::registers[mem::spv](potat, ops_, e, 0);

// open the file:
    std::ifstream file(in[1], std::ios::binary);

    // Stop eating new lines in binary mode!!!
    file.unsetf(std::ios::skipws);

    // get its size:
    std::streampos fileSize;

    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // reserve capacity
    std::vector<unsigned char> vec;
    vec.reserve(fileSize);

    // read the data:
    vec.insert(vec.begin(),
               std::istream_iterator<unsigned char>(file),
               std::istream_iterator<unsigned char>());

    int entryPoint = 0;

    std::vector<std::vector<uint_8>> operators;
    OP_STACK program(vec.data(), vec.size());

    while (program.getRemaining() > 0)
    {
        Op op = program.getOp();

        if (op == func)
        {
            std::vector<uint_8> prog;
            uint_64 end = program.getUnsignedLong();


            while (program.address < end)
                prog.push_back(program.getUnsignedByte());

            operators.push_back(prog);
        } else { std::cerr << "opcode " << op << " is not a valid opcode.\n"; }
    }

    OP_STACK* opStack = new OP_STACK[operators.size()];

    for (uint_64 i = 0; i < operators.size(); i ++)
        opStack[i] = OP_STACK(operators[i].data(), operators[i].size());

    std::vector<env::n_func> nFuncVector;

    loadDLLs(nFuncVector, count, in);

    env::n_func* nFuncs = new env::n_func[nFuncVector.size()];
    for (int i = 0; i < nFuncVector.size(); i ++)
        nFuncs[i] = nFuncVector[i];

    env genv(opStack, nFuncs);
    genv.execute();

    return 0;
}