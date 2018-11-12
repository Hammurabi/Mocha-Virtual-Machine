//
// Created by Riverssen on 05.11.18.
//

#ifndef MVM_OPCODES_H
#define MVM_OPCODES_H
enum Op{
//    /**
//     * The following opcodes are not interpreted during runtime, they are used for positioning.
//     */
//    sfunc,
//    nfunc,
//    /**
//     * Interpreted opcodes start here
//     */
//    bsp,
//    sbp,
//    gbp,
//
//    sha256,
//    sha3,
//    ripemd160,
//    keccak256,

    func = 0            ,/** (This opcode won't be interpreted) it creates a marker for an OP_STACK (must end with a return_op of some kind). **/
    hash = 1            ,/** perform a hash on pointer data. **/
    timens = 2          ,/** push a (uint_64) current time in nanoseconds. **/
    timems = 3          ,/** push a (uint_64) current time in milliseconds. **/
    strconst = 4        ,/** push a constant string. **/
    strload = 5         ,/** load a string. **/
    strstore = 6        ,/** store a string. **/
    strsizeof = 7       ,/** store a string. **/
    strcast_a = 8       ,/** cast a string to a pointer. **/
    strcast_ba = 9      ,/** cast a string to a byte array. **/
    strprint = 10       ,/** print a string. **/
    strreturn = 11      ,/** return a string from scope. **/
    mark = 12           ,/** mark a specific location. **/
    jump = 13           ,/** jump to a specific location. **/
    jumptomark = 14     ,/** jump to a specific marked location. **/
    newline = 15        ,/** print a \n character into the console. **/
    ret = 16            ,/** return from this scope. **/
    invoke = 17         ,/** invoke a method. **/
    invokedynamic = 18  ,/** dynamically invoke a method using function pointers. **/
    invokespecial = 19  ,/** invoke a native method using function pointers. **/
    if_t = 20           ,/** if true. **/
    if_f = 21           ,/** if not true. **/
    invert = 22         ,/** invert a boolean. **/
    amemcpy = 23        ,/** copy memory to destination from source. **/
    bspmemcpy = 24      ,/** copy memory to destination from base pointer. **/
    amemcpybsp = 25     ,/** copy memory to pointer from source. **/
    amalloc = 26        ,/** push a const pointer to the stack. **/
    acalloc = 27        ,/** push a const pointer to the stack. **/
    amallocs = 28       ,/** push a const pointer to the stack from size_int16_t. **/
    acallocs = 29       ,/** push a const pointer to the stack from size_int16_t. **/
    adelete = 30        ,/** delete a pointer. **/
    baconst = 31        ,/** push a byte array. **/
    baconsts = 32       ,/** push a byte array using size_int16_t **/
    baconsti = 33       ,/** push a byte array using size_int32_t **/
    bacast_a = 34       ,/** cast a byte array into a pointer **/
    basizeof = 35       ,/** push the size of a byte array to stack **/
    printba = 36        ,/** print a byte array. **/
    cmpl = 37           ,/** compare a long less than long. **/
    cmpg = 38           ,/** compare a long greater than long. **/
    cmpe = 39           ,/** compare a long equal with long. **/
    cmple = 40          ,/** compare a long less than or equal to long. **/
    cmpge = 41          ,/** compare a long greater than or equal to long. **/
    cmpne = 42          ,/** compare a long not equal with long. **/
    ucmp = 43           ,/** compare a ulong int with another ulong. **/
    cmpu = 44           ,/** compare a long int with a ulong. **/
    cmpll = 45          ,/** compare a 256bit int with another 256bit int. **/
    ucmpll = 46         ,/** compare a u256bit int with another u256bit int. **/
    cmpull = 47         ,/** compare a 256bit int with a u256bit int. **/
    dcmpl = 48          ,/** compare a double less than double. **/
    dcmpg = 49          ,/** compare a double greater than double. **/
    dcmpe = 50          ,/** compare a double equal with double. **/
    dcmple = 51         ,/** compare a double less than or equal to double. **/
    dcmpge = 52         ,/** compare a double greater than or equal to double. **/
    dcmpne = 53         ,/** compare a double not equal with double. **/
    mod = 54            ,/** mod an int with an int. **/
    llmod = 55          ,/** mod an int 256 with an int 256. **/
    and_ = 56            ,/** bitwise and int with int. **/
    or_ = 57             ,/** bitwise or int with int. **/
    xor_ = 58            ,/** bitwise xor int with int. **/
    not_ = 59            ,/** bitwise not int with int. **/
    rshft = 60          ,/** right shift int with byte. **/
    lshft = 61          ,/** left shift int with byte. **/
    dup = 62            ,/** duplicate a %t on the stack. **/
    dup2 = 63           ,/** duplicate a %t 2 times on the stack. **/
    dup3 = 64           ,/** duplicate a %t 3 times on the stack. **/
    swap = 65           ,/** swap the 2 topmost elements. **/
    pret = 66           ,/** return the top element into the main stack. **/
    pret2 = 67          ,/** return the top 2 elements (128bit) into the main stack. **/
    pret4 = 68          ,/** return the top 4 elements (256bit) into the main stack. **/
    bconst = 69         ,/** push a const int_8 into the stack. **/
    bconst_0 = 70       ,/** push a const int_8 into the stack (value = 0). **/
    bload = 71          ,/** load a int_8 into the stack from local variable. **/
    bstore = 72         ,/** store a int_8 from stack into local variable. **/
    bset = 73           ,/** set a int_8 from stack into a field on pointer. **/
    bget = 74           ,/** get a int_8 from a field on a pointer to stack. **/
    bmainst = 75        ,/** store a int_8 from main stack in a local variable.. **/
    bprint = 76         ,/** print a int_8 from stack. **/
    buprint = 77        ,/** print a unsigned uint_8 from stack. **/
    sconst = 78         ,/** push a const int_16 into the stack. **/
    sconst_0 = 79       ,/** push a const int_16 into the stack (value = 0). **/
    sload = 80          ,/** load a int_16 into the stack from local variable. **/
    sstore = 81         ,/** store a int_16 from stack into local variable. **/
    sset = 82           ,/** set a int_16 from stack into a field on pointer. **/
    sget = 83           ,/** get a int_16 from a field on a pointer to stack. **/
    smainst = 84        ,/** store a int_16 from main stack in a local variable.. **/
    sprint = 85         ,/** print a int_16 from stack. **/
    suprint = 86        ,/** print a unsigned uint_16 from stack. **/
    iconst = 87         ,/** push a const int_32 into the stack. **/
    iconst_0 = 88       ,/** push a const int_32 into the stack (value = 0). **/
    iconst_1 = 89       ,/** push a const int_32 into the stack (value = 1). **/
    iconst_2 = 90       ,/** push a const int_32 into the stack (value = 2). **/
    iconst_3 = 91       ,/** push a const int_32 into the stack (value = 3). **/
    iconst_4 = 92       ,/** push a const int_32 into the stack (value = 4). **/
    iconst_5 = 93       ,/** push a const int_32 into the stack (value = 5). **/
    iconst_6 = 94       ,/** push a const int_32 into the stack (value = 6). **/
    iconst_9 = 95       ,/** push a const int_32 into the stack (value = 9). **/
    iconst_10 = 96      ,/** push a const int_32 into the stack (value = 10). **/
    iconst_11 = 97      ,/** push a const int_32 into the stack (value = 11). **/
    iconst_12 = 98      ,/** push a const int_32 into the stack (value = 12). **/
    iload = 99          ,/** load a int_32 into the stack from local variable. **/
    iload_0 = 100       ,/** load a int_32 into the stack from local variable 0. **/
    iload_1 = 101       ,/** load a int_32 into the stack from local variable 1. **/
    iload_2 = 102       ,/** load a int_32 into the stack from local variable 2. **/
    iload_3 = 103       ,/** load a int_32 into the stack from local variable 3. **/
    iload_4 = 104       ,/** load a int_32 into the stack from local variable 4. **/
    istore = 105        ,/** store a int_32 from stack into local variable. **/
    istore_0 = 106      ,/** store a int_32 from stack into local variable 0. **/
    istore_1 = 107      ,/** store a int_32 from stack into local variable 1. **/
    istore_2 = 108      ,/** store a int_32 from stack into local variable 2. **/
    istore_3 = 109      ,/** store a int_32 from stack into local variable 3. **/
    istore_4 = 110      ,/** store a int_32 from stack into local variable 4. **/
    iadd = 111          ,/** add two Ints. **/
    iuadd = 112         ,/** add two UnsignedUnsignedInts. **/
    isub = 113          ,/** subtract two Ints. **/
    iusub = 114         ,/** subtract two UnsignedUnsignedInts. **/
    imul = 115          ,/** multiply two Ints. **/
    iumul = 116         ,/** multiply two UnsignedUnsignedInts. **/
    idiv = 117          ,/** divide two Ints. **/
    iudiv = 118         ,/** divide two UnsignedUnsignedInts. **/
    iset = 119          ,/** set a int_32 from stack into a field on pointer. **/
    iget = 120          ,/** get a int_32 from a field on a pointer to stack. **/
    iinc1 = 121         ,/** increment a local variable int_32 by 1. **/
    iinc2 = 122         ,/** increment a local variable int_32 by 2. **/
    imainst = 123       ,/** store a int_32 from main stack in a local variable.. **/
    imainst_0 = 124     ,/** store a int_32 from main stack in local variable 0. **/
    imainst_1 = 125     ,/** store a int_32 from main stack in local variable 1. **/
    imainst_2 = 126     ,/** store a int_32 from main stack in local variable 2. **/
    imainst_3 = 127     ,/** store a int_32 from main stack in local variable 3. **/
    iprint = 128        ,/** print a int_32 from stack. **/
    iuprint = 129       ,/** print a unsigned uint_32 from stack. **/
    lconst = 130        ,/** push a const int_64 into the stack. **/
    lconst_0 = 131      ,/** push a const int_64 into the stack (value = 0). **/
    lconst_1 = 132      ,/** push a const int_64 into the stack (value = 1). **/
    lconst_2 = 133      ,/** push a const int_64 into the stack (value = 2). **/
    lconst_3 = 134      ,/** push a const int_64 into the stack (value = 3). **/
    lconst_4 = 135      ,/** push a const int_64 into the stack (value = 4). **/
    lconst_5 = 136      ,/** push a const int_64 into the stack (value = 5). **/
    lconst_6 = 137      ,/** push a const int_64 into the stack (value = 6). **/
    lconst_9 = 138      ,/** push a const int_64 into the stack (value = 9). **/
    lconst_10 = 139     ,/** push a const int_64 into the stack (value = 10). **/
    lconst_11 = 140     ,/** push a const int_64 into the stack (value = 11). **/
    lconst_12 = 141     ,/** push a const int_64 into the stack (value = 12). **/
    lload = 142         ,/** load a int_64 into the stack from local variable. **/
    lload_0 = 143       ,/** load a int_64 into the stack from local variable 0. **/
    lload_1 = 144       ,/** load a int_64 into the stack from local variable 1. **/
    lload_2 = 145       ,/** load a int_64 into the stack from local variable 2. **/
    lload_3 = 146       ,/** load a int_64 into the stack from local variable 3. **/
    lload_4 = 147       ,/** load a int_64 into the stack from local variable 4. **/
    lstore = 148        ,/** store a int_64 from stack into local variable. **/
    lstore_0 = 149      ,/** store a int_64 from stack into local variable 0. **/
    lstore_1 = 150      ,/** store a int_64 from stack into local variable 1. **/
    lstore_2 = 151      ,/** store a int_64 from stack into local variable 2. **/
    lstore_3 = 152      ,/** store a int_64 from stack into local variable 3. **/
    lstore_4 = 153      ,/** store a int_64 from stack into local variable 4. **/
    ladd = 154          ,/** add two Longs. **/
    luadd = 155         ,/** add two UnsignedUnsignedLongs. **/
    lsub = 156          ,/** subtract two Longs. **/
    lusub = 157         ,/** subtract two UnsignedUnsignedLongs. **/
    lmul = 158          ,/** multiply two Longs. **/
    lumul = 159         ,/** multiply two UnsignedUnsignedLongs. **/
    ldiv_ = 160          ,/** divide two Longs. **/
    ludiv = 161         ,/** divide two UnsignedUnsignedLongs. **/
    lset = 162          ,/** set a int_64 from stack into a field on pointer. **/
    lget = 163          ,/** get a int_64 from a field on a pointer to stack. **/
    linc1 = 164         ,/** increment a local variable int_64 by 1. **/
    linc2 = 165         ,/** increment a local variable int_64 by 2. **/
    lmainst = 166       ,/** store a int_64 from main stack in a local variable.. **/
    lmainst_0 = 167     ,/** store a int_64 from main stack in local variable 0. **/
    lmainst_1 = 168     ,/** store a int_64 from main stack in local variable 1. **/
    lmainst_2 = 169     ,/** store a int_64 from main stack in local variable 2. **/
    lmainst_3 = 170     ,/** store a int_64 from main stack in local variable 3. **/
    lprint = 171        ,/** print a int_64 from stack. **/
    luprint = 172       ,/** print a unsigned uint_64 from stack. **/
    liconst = 173       ,/** push a const int_128 into the stack. **/
    liconst_0 = 174     ,/** push a const int_128 into the stack (value = 0). **/
    liload = 175        ,/** load a int_128 into the stack from local variable. **/
    listore = 176       ,/** store a int_128 from stack into local variable. **/
    liadd = 177         ,/** add two LongInts. **/
    liuadd = 178        ,/** add two UnsignedUnsignedLongInts. **/
    lisub = 179         ,/** subtract two LongInts. **/
    liusub = 180        ,/** subtract two UnsignedUnsignedLongInts. **/
    limul = 181         ,/** multiply two LongInts. **/
    liumul = 182        ,/** multiply two UnsignedUnsignedLongInts. **/
    lidiv = 183         ,/** divide two LongInts. **/
    liudiv = 184        ,/** divide two UnsignedUnsignedLongInts. **/
    liset = 185         ,/** set a int_128 from stack into a field on pointer. **/
    liget = 186         ,/** get a int_128 from a field on a pointer to stack. **/
    limainst = 187      ,/** store a int_128 from main stack in a local variable.. **/
    liprint = 188       ,/** print a int_128 from stack. **/
    liuprint = 189      ,/** print a unsigned uint_128 from stack. **/
    llconst = 190       ,/** push a const int_256 into the stack. **/
    llconst_0 = 191     ,/** push a const int_256 into the stack (value = 0). **/
    llload = 192        ,/** load a int_256 into the stack from local variable. **/
    llstore = 193       ,/** store a int_256 from stack into local variable. **/
    lladd = 194         ,/** add two LongLongs. **/
    lluadd = 195        ,/** add two UnsignedUnsignedLongLongs. **/
    llsub = 196         ,/** subtract two LongLongs. **/
    llusub = 197        ,/** subtract two UnsignedUnsignedLongLongs. **/
    llmul = 198         ,/** multiply two LongLongs. **/
    llumul = 199        ,/** multiply two UnsignedUnsignedLongLongs. **/
    lldiv_ = 200         ,/** divide two LongLongs. **/
    lludiv = 201        ,/** divide two UnsignedUnsignedLongLongs. **/
    llset = 202         ,/** set a int_256 from stack into a field on pointer. **/
    llget = 203         ,/** get a int_256 from a field on a pointer to stack. **/
    llmainst = 204      ,/** store a int_256 from main stack in a local variable.. **/
    llprint = 205       ,/** print a int_256 from stack. **/
    lluprint = 206      ,/** print a unsigned uint_256 from stack. **/
    fconst = 207        ,/** push a const flt_32 into the stack. **/
    fconst_0 = 208      ,/** push a const flt_32 into the stack (value = 0). **/
    fload = 209         ,/** load a flt_32 into the stack from local variable. **/
    fstore = 210        ,/** store a flt_32 from stack into local variable. **/
    fset = 211          ,/** set a flt_32 from stack into a field on pointer. **/
    fget = 212          ,/** get a flt_32 from a field on a pointer to stack. **/
    fmainst = 213       ,/** store a flt_32 from main stack in a local variable.. **/
    dconst = 214        ,/** push a const flt_64 into the stack. **/
    dconst_0 = 215      ,/** push a const flt_64 into the stack (value = 0). **/
    dload = 216         ,/** load a flt_64 into the stack from local variable. **/
    dstore = 217        ,/** store a flt_64 from stack into local variable. **/
    dset = 218          ,/** set a flt_64 from stack into a field on pointer. **/
    dget = 219          ,/** get a flt_64 from a field on a pointer to stack. **/
    dmainst = 220       ,/** store a flt_64 from main stack in a local variable.. **/
    dfconst = 221       ,/** push a const flt_128 into the stack. **/
    dfconst_0 = 222     ,/** push a const flt_128 into the stack (value = 0). **/
    dfload = 223        ,/** load a flt_128 into the stack from local variable. **/
    dfstore = 224       ,/** store a flt_128 from stack into local variable. **/
    dfset = 225         ,/** set a flt_128 from stack into a field on pointer. **/
    dfget = 226         ,/** get a flt_128 from a field on a pointer to stack. **/
    dfmainst = 227      ,/** store a flt_128 from main stack in a local variable.. **/
    ddconst = 228       ,/** push a const flt_256 into the stack. **/
    ddconst_0 = 229     ,/** push a const flt_256 into the stack (value = 0). **/
    ddload = 230        ,/** load a flt_256 into the stack from local variable. **/
    ddstore = 231       ,/** store a flt_256 from stack into local variable. **/
    ddset = 232         ,/** set a flt_256 from stack into a field on pointer. **/
    ddget = 233         ,/** get a flt_256 from a field on a pointer to stack. **/
    ddmainst = 234      ,/** store a flt_256 from main stack in a local variable.. **/
    aconst = 235        ,/** push a const pointer into the stack. **/
    aconst_0 = 236      ,/** push a const pointer into the stack (value = 0). **/
    aload = 237         ,/** load a pointer into the stack from local variable. **/
    astore = 238        ,/** store a pointer from stack into local variable. **/
    aset = 239          ,/** set a pointer from stack into a field on pointer. **/
    aget = 240          ,/** get a pointer from a field on a pointer to stack. **/
    amainst = 241       ,/** store a pointer from main stack in a local variable.. **/
};

#endif //MVM_OPCODES_H