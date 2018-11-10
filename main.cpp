#include <iostream>
#include "executor.h"
#include "executorfuncs.h"

#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>

uint_16 op(uint_16 o)
{
    EndianMachine e;
    if (e.isBigEndian())
        return o;

    return ((uint_16 *)((uint_8[2]) {((pointer) &o)[1], ((pointer) &o)[0]}))[0];
}

int main(int count, const char** in) {
    MvM::Init();
    uint_16 for_loop[] = {
            op(iconst_0),
            op(istore_0),
            op(iconst_12),
            op(istore_1),
//
            op(mark), 0,
            op(iload_0),
            op(iload_1),
//
            op(icmple_i),
            op(if_t), 0, op(18),

            op(iconst_6),
            op(iload_0),
            op(imul_i),
            op(iprint),
            op(newline),

            op(iinc_1), 0,

            op(jumptomark), 0,

            op(iconst_12),
            op(iconst_12),
            op(imul_i),
            op(iprint)
    };

//    uint_16 ops[] = {op(iconst), op(0), op(20), op(iprint)};
    uint_64 length = sizeof(for_loop);

    pointer base = new unsigned char[4];
    Stack stack;




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

    std::vector<std::vector<uint_8>> ops;
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

            ops.push_back(prog);
        } else { std::cerr << "opcode error 0x01 with opcode " << op << "\n"; }
    }

    OP_STACK* opStack = new OP_STACK[ops.size()];

    for (uint_64 i = 0; i < ops.size(); i ++)
        opStack[i] = OP_STACK(ops[i].data(), ops[i].size());

//    uint_16 tests[] = {op(bconst_6), op(bprint)};
//    OP_STACK o;

//std::cout << ops.size() << " programs found.\n";

    Stack stack_;

    uint_64 index = 0;

    funcs::getAllImplementations(index);

    MvM::execute(opStack, new MochaNativeInterface*[2], base, base, stack, opStack[entryPoint]);

    return 0;
}