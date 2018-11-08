#include <iostream>
#include "executor.h"

uint_16 op(uint_16 o)
{
    return ((uint_16 *)((uint_8[2]) {((pointer) &o)[1], ((pointer) &o)[0]}))[0];
}

int main() {
    MvM::Init();
    uint_16 for_loop[] = {
            op(iconst_0),
            op(istore_0),
            op(iconst_12),
            op(istore_1),

            op(mark), 0,
            op(iload_0),
            op(iload_1),

            op(icmple_i),
            op(if_t), 0, 20,

            op(iconst_6),
            op(iload_0),
            op(imul_i),
            op(printi),
            op(newline),

            op(iinc_1), 0, 0,

            op(jumptomark), 0,
            op(iconst_0),
            op(printi)
    };

//    uint_16 ops[] = {op(bconst_6), op(printb)};
    uint_64 length = sizeof(for_loop);

    pointer base = new unsigned char[4];
    Stack stack;

    MvM::execute(new OP_STACK[2], new MochaNativeInterface*[2], base, base, stack, OP_STACK((uint_8*) for_loop, length));

    return 0;
}