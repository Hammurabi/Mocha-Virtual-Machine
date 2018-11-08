//
// Created by Riverssen on 05.11.18.
//

#ifndef MVM_OPCODES_H
#define MVM_OPCODES_H
enum Op{
    /**
     * The following opcodes are not interpreted during runtime, they are used for positioning.
     */
    sfunc,
    nfunc,
    /**
     * Interpreted opcodes start here
     */
    bsp,
    sbp,
    gbp,

    sha256,
    sha3,
    ripemd160,
    keccak256,



    mark,/** mark a specific location. **/
    jump,/** jump to a specific location. **/
    jumptomark,/** jump to a specific marked location. **/
    newline,/** print a \n character into the console. **/
    invokestatic,/** invoke a static method. **/
    invokedynamic,/** dynamically invoke a method using function pointers. **/
    invokenative,/** invoke a native method using function pointers. **/
    if_t,/** if true. **/
    if_f,/** if not true. **/
    amemcpy,/** copy memory to destination from source. **/
    bspmemcpy,/** copy memory to destination from base pointer. **/
    amemcpybsp,/** copy memory to pointer from source. **/
    amalloc,/** push a const pointer to the stack. **/
    acalloc,/** push a const pointer to the stack. **/
    amallocs,/** push a const pointer to the stack from size_int16_t. **/
    acallocs,/** push a const pointer to the stack from size_int16_t. **/
    abload,/** load an int_8 from a pointer. **/
    asload,/** load an int_16 from a pointer. **/
    aiload,/** load an int_32 from a pointer. **/
    alload,/** load an int_64 from a pointer. **/
    aliload,/** load an int_128 from a pointer. **/
    allload,/** load an int_256 from a pointer. **/
    afload,/** load an flt_32 from a pointer. **/
    adload,/** load an flt_64 from a pointer. **/
    adfload,/** load an flt_128 from a pointer. **/
    addload,/** load an flt_256 from a pointer. **/
    aaload,/** load a pointer from a pointer. **/
    abstore,/** store an int_8 in a pointer. **/
    asstore,/** store an int_16 in a pointer. **/
    aistore,/** store an int_32 in a pointer. **/
    alstore,/** store an int_64 in a pointer. **/
    alistore,/** store an int_128 in a pointer. **/
    allstore,/** store an int_256 in a pointer. **/
    afstore,/** store an flt_32 in a pointer. **/
    adstore,/** store an flt_64 in a pointer. **/
    adfstore,/** store an flt_128 in a pointer. **/
    addstore,/** store an flt_256 in a pointer. **/
    aastore,/** store a pointer in a pointer. **/
    baconst,/** push a byte array. **/
    baconsts,/** push a byte array using size_int16_t **/
    baconsti,/** push a byte array using size_int32_t **/
    bacast_a,/** cast a byte array into a pointer **/
    basizeof,/** push the size of a byte array to stack **/
    bprintba            ,/** print a byte array. **/
    bconst              ,/** push a const int_8 into the stack. **/
    bconst_0            ,/** push a const int_8 into the stack (value = 0). **/
    bconst_1            ,/** push a const int_8 into the stack (value = 1). **/
    bconst_2            ,/** push a const int_8 into the stack (value = 2). **/
    bconst_3            ,/** push a const int_8 into the stack (value = 3). **/
    bconst_4            ,/** push a const int_8 into the stack (value = 4). **/
    bconst_5            ,/** push a const int_8 into the stack (value = 5). **/
    bconst_6            ,/** push a const int_8 into the stack (value = 6). **/
    bconst_9            ,/** push a const int_8 into the stack (value = 9). **/
    bconst_10           ,/** push a const int_8 into the stack (value = 10). **/
    bconst_11           ,/** push a const int_8 into the stack (value = 11). **/
    bconst_12           ,/** push a const int_8 into the stack (value = 12). **/
    bload               ,/** load a int_8 into the stack from local variable. **/
    bload_0             ,/** load a int_8 into the stack from local variable 0. **/
    bload_1             ,/** load a int_8 into the stack from local variable 1. **/
    bload_2             ,/** load a int_8 into the stack from local variable 2. **/
    bload_3             ,/** load a int_8 into the stack from local variable 3. **/
    bload_4             ,/** load a int_8 into the stack from local variable 4. **/
    bstore              ,/** store a int_8 from stack into local variable. **/
    bstore_0            ,/** store a int_8 from stack into local variable 0. **/
    bstore_1            ,/** store a int_8 from stack into local variable 1. **/
    bstore_2            ,/** store a int_8 from stack into local variable 2. **/
    bstore_3            ,/** store a int_8 from stack into local variable 3. **/
    bstore_4            ,/** store a int_8 from stack into local variable 4. **/
    bcast_b             ,/** cast int_8 to type Byte. **/
    bucast_b            ,/** cast unsigned uint_8 to type Byte. **/
    badd_b              ,/** add int_8 with type Byte. **/
    buadd_b             ,/** add unsigned uint_8 with type Byte. **/
    bsub_b              ,/** subtract int_8 with type Byte. **/
    busub_b             ,/** subtract unsigned uint_8 with type Byte. **/
    bmul_b              ,/** multiply int_8 with type Byte. **/
    bumul_b             ,/** multiply unsigned uint_8 with type Byte. **/
    bdiv_b              ,/** divide int_8 with type Byte. **/
    budiv_b             ,/** divide unsigned uint_8 with type Byte. **/
    bcmpl_b             ,/** compare int_8 less than type Byte. **/
    bucmpl_b            ,/** compare unsigned uint_8 less than type Byte. **/
    bcmpg_b             ,/** compare int_8 greater than type Byte. **/
    bucmpg_b            ,/** compare unsigned uint_8 greater than type Byte. **/
    bcmpe_b             ,/** compare int_8 equal with type Byte. **/
    bucmpe_b            ,/** compare unsigned uint_8 equal with type Byte. **/
    bcmple_b            ,/** compare int_8 less than or equal to type Byte. **/
    bucmple_b           ,/** compare unsigned uint_8 less than or equal to type Byte. **/
    bcmpge_b            ,/** compare int_8 greater than or equal to type Byte. **/
    bucmpge_b           ,/** compare unsigned uint_8 greater than or equal to type Byte. **/
    bcmpne_b            ,/** compare int_8 not equal with type Byte. **/
    bucmpne_b           ,/** compare unsigned uint_8 not equal with type Byte. **/
    bcast_s             ,/** cast int_8 to type Short. **/
    bucast_s            ,/** cast unsigned uint_8 to type Short. **/
    badd_s              ,/** add int_8 with type Short. **/
    buadd_s             ,/** add unsigned uint_8 with type Short. **/
    bsub_s              ,/** subtract int_8 with type Short. **/
    busub_s             ,/** subtract unsigned uint_8 with type Short. **/
    bmul_s              ,/** multiply int_8 with type Short. **/
    bumul_s             ,/** multiply unsigned uint_8 with type Short. **/
    bdiv_s              ,/** divide int_8 with type Short. **/
    budiv_s             ,/** divide unsigned uint_8 with type Short. **/
    bcmpl_s             ,/** compare int_8 less than type Short. **/
    bucmpl_s            ,/** compare unsigned uint_8 less than type Short. **/
    bcmpg_s             ,/** compare int_8 greater than type Short. **/
    bucmpg_s            ,/** compare unsigned uint_8 greater than type Short. **/
    bcmpe_s             ,/** compare int_8 equal with type Short. **/
    bucmpe_s            ,/** compare unsigned uint_8 equal with type Short. **/
    bcmple_s            ,/** compare int_8 less than or equal to type Short. **/
    bucmple_s           ,/** compare unsigned uint_8 less than or equal to type Short. **/
    bcmpge_s            ,/** compare int_8 greater than or equal to type Short. **/
    bucmpge_s           ,/** compare unsigned uint_8 greater than or equal to type Short. **/
    bcmpne_s            ,/** compare int_8 not equal with type Short. **/
    bucmpne_s           ,/** compare unsigned uint_8 not equal with type Short. **/
    bcast_i             ,/** cast int_8 to type Int. **/
    bucast_i            ,/** cast unsigned uint_8 to type Int. **/
    badd_i              ,/** add int_8 with type Int. **/
    buadd_i             ,/** add unsigned uint_8 with type Int. **/
    bsub_i              ,/** subtract int_8 with type Int. **/
    busub_i             ,/** subtract unsigned uint_8 with type Int. **/
    bmul_i              ,/** multiply int_8 with type Int. **/
    bumul_i             ,/** multiply unsigned uint_8 with type Int. **/
    bdiv_i              ,/** divide int_8 with type Int. **/
    budiv_i             ,/** divide unsigned uint_8 with type Int. **/
    bcmpl_i             ,/** compare int_8 less than type Int. **/
    bucmpl_i            ,/** compare unsigned uint_8 less than type Int. **/
    bcmpg_i             ,/** compare int_8 greater than type Int. **/
    bucmpg_i            ,/** compare unsigned uint_8 greater than type Int. **/
    bcmpe_i             ,/** compare int_8 equal with type Int. **/
    bucmpe_i            ,/** compare unsigned uint_8 equal with type Int. **/
    bcmple_i            ,/** compare int_8 less than or equal to type Int. **/
    bucmple_i           ,/** compare unsigned uint_8 less than or equal to type Int. **/
    bcmpge_i            ,/** compare int_8 greater than or equal to type Int. **/
    bucmpge_i           ,/** compare unsigned uint_8 greater than or equal to type Int. **/
    bcmpne_i            ,/** compare int_8 not equal with type Int. **/
    bucmpne_i           ,/** compare unsigned uint_8 not equal with type Int. **/
    bcast_l             ,/** cast int_8 to type Long. **/
    bucast_l            ,/** cast unsigned uint_8 to type Long. **/
    badd_l              ,/** add int_8 with type Long. **/
    buadd_l             ,/** add unsigned uint_8 with type Long. **/
    bsub_l              ,/** subtract int_8 with type Long. **/
    busub_l             ,/** subtract unsigned uint_8 with type Long. **/
    bmul_l              ,/** multiply int_8 with type Long. **/
    bumul_l             ,/** multiply unsigned uint_8 with type Long. **/
    bdiv_l              ,/** divide int_8 with type Long. **/
    budiv_l             ,/** divide unsigned uint_8 with type Long. **/
    bcmpl_l             ,/** compare int_8 less than type Long. **/
    bucmpl_l            ,/** compare unsigned uint_8 less than type Long. **/
    bcmpg_l             ,/** compare int_8 greater than type Long. **/
    bucmpg_l            ,/** compare unsigned uint_8 greater than type Long. **/
    bcmpe_l             ,/** compare int_8 equal with type Long. **/
    bucmpe_l            ,/** compare unsigned uint_8 equal with type Long. **/
    bcmple_l            ,/** compare int_8 less than or equal to type Long. **/
    bucmple_l           ,/** compare unsigned uint_8 less than or equal to type Long. **/
    bcmpge_l            ,/** compare int_8 greater than or equal to type Long. **/
    bucmpge_l           ,/** compare unsigned uint_8 greater than or equal to type Long. **/
    bcmpne_l            ,/** compare int_8 not equal with type Long. **/
    bucmpne_l           ,/** compare unsigned uint_8 not equal with type Long. **/
    bcast_li            ,/** cast int_8 to type LongInt. **/
    bucast_li           ,/** cast unsigned uint_8 to type LongInt. **/
    badd_li             ,/** add int_8 with type LongInt. **/
    buadd_li            ,/** add unsigned uint_8 with type LongInt. **/
    bsub_li             ,/** subtract int_8 with type LongInt. **/
    busub_li            ,/** subtract unsigned uint_8 with type LongInt. **/
    bmul_li             ,/** multiply int_8 with type LongInt. **/
    bumul_li            ,/** multiply unsigned uint_8 with type LongInt. **/
    bdiv_li             ,/** divide int_8 with type LongInt. **/
    budiv_li            ,/** divide unsigned uint_8 with type LongInt. **/
    bcmpl_li            ,/** compare int_8 less than type LongInt. **/
    bucmpl_li           ,/** compare unsigned uint_8 less than type LongInt. **/
    bcmpg_li            ,/** compare int_8 greater than type LongInt. **/
    bucmpg_li           ,/** compare unsigned uint_8 greater than type LongInt. **/
    bcmpe_li            ,/** compare int_8 equal with type LongInt. **/
    bucmpe_li           ,/** compare unsigned uint_8 equal with type LongInt. **/
    bcmple_li           ,/** compare int_8 less than or equal to type LongInt. **/
    bucmple_li          ,/** compare unsigned uint_8 less than or equal to type LongInt. **/
    bcmpge_li           ,/** compare int_8 greater than or equal to type LongInt. **/
    bucmpge_li          ,/** compare unsigned uint_8 greater than or equal to type LongInt. **/
    bcmpne_li           ,/** compare int_8 not equal with type LongInt. **/
    bucmpne_li          ,/** compare unsigned uint_8 not equal with type LongInt. **/
    bcast_ll            ,/** cast int_8 to type LongLong. **/
    bucast_ll           ,/** cast unsigned uint_8 to type LongLong. **/
    badd_ll             ,/** add int_8 with type LongLong. **/
    buadd_ll            ,/** add unsigned uint_8 with type LongLong. **/
    bsub_ll             ,/** subtract int_8 with type LongLong. **/
    busub_ll            ,/** subtract unsigned uint_8 with type LongLong. **/
    bmul_ll             ,/** multiply int_8 with type LongLong. **/
    bumul_ll            ,/** multiply unsigned uint_8 with type LongLong. **/
    bdiv_ll             ,/** divide int_8 with type LongLong. **/
    budiv_ll            ,/** divide unsigned uint_8 with type LongLong. **/
    bcmpl_ll            ,/** compare int_8 less than type LongLong. **/
    bucmpl_ll           ,/** compare unsigned uint_8 less than type LongLong. **/
    bcmpg_ll            ,/** compare int_8 greater than type LongLong. **/
    bucmpg_ll           ,/** compare unsigned uint_8 greater than type LongLong. **/
    bcmpe_ll            ,/** compare int_8 equal with type LongLong. **/
    bucmpe_ll           ,/** compare unsigned uint_8 equal with type LongLong. **/
    bcmple_ll           ,/** compare int_8 less than or equal to type LongLong. **/
    bucmple_ll          ,/** compare unsigned uint_8 less than or equal to type LongLong. **/
    bcmpge_ll           ,/** compare int_8 greater than or equal to type LongLong. **/
    bucmpge_ll          ,/** compare unsigned uint_8 greater than or equal to type LongLong. **/
    bcmpne_ll           ,/** compare int_8 not equal with type LongLong. **/
    bucmpne_ll          ,/** compare unsigned uint_8 not equal with type LongLong. **/
    bcast_f             ,/** cast int_8 to type Float. **/
    bucast_f            ,/** cast unsigned uint_8 to type Float. **/
    badd_f              ,/** add int_8 with type Float. **/
    buadd_f             ,/** add unsigned uint_8 with type Float. **/
    bsub_f              ,/** subtract int_8 with type Float. **/
    busub_f             ,/** subtract unsigned uint_8 with type Float. **/
    bmul_f              ,/** multiply int_8 with type Float. **/
    bumul_f             ,/** multiply unsigned uint_8 with type Float. **/
    bdiv_f              ,/** divide int_8 with type Float. **/
    budiv_f             ,/** divide unsigned uint_8 with type Float. **/
    bcmpl_f             ,/** compare int_8 less than type Float. **/
    bucmpl_f            ,/** compare unsigned uint_8 less than type Float. **/
    bcmpg_f             ,/** compare int_8 greater than type Float. **/
    bucmpg_f            ,/** compare unsigned uint_8 greater than type Float. **/
    bcmpe_f             ,/** compare int_8 equal with type Float. **/
    bucmpe_f            ,/** compare unsigned uint_8 equal with type Float. **/
    bcmple_f            ,/** compare int_8 less than or equal to type Float. **/
    bucmple_f           ,/** compare unsigned uint_8 less than or equal to type Float. **/
    bcmpge_f            ,/** compare int_8 greater than or equal to type Float. **/
    bucmpge_f           ,/** compare unsigned uint_8 greater than or equal to type Float. **/
    bcmpne_f            ,/** compare int_8 not equal with type Float. **/
    bucmpne_f           ,/** compare unsigned uint_8 not equal with type Float. **/
    bcast_d             ,/** cast int_8 to type Double. **/
    bucast_d            ,/** cast unsigned uint_8 to type Double. **/
    badd_d              ,/** add int_8 with type Double. **/
    buadd_d             ,/** add unsigned uint_8 with type Double. **/
    bsub_d              ,/** subtract int_8 with type Double. **/
    busub_d             ,/** subtract unsigned uint_8 with type Double. **/
    bmul_d              ,/** multiply int_8 with type Double. **/
    bumul_d             ,/** multiply unsigned uint_8 with type Double. **/
    bdiv_d              ,/** divide int_8 with type Double. **/
    budiv_d             ,/** divide unsigned uint_8 with type Double. **/
    bcmpl_d             ,/** compare int_8 less than type Double. **/
    bucmpl_d            ,/** compare unsigned uint_8 less than type Double. **/
    bcmpg_d             ,/** compare int_8 greater than type Double. **/
    bucmpg_d            ,/** compare unsigned uint_8 greater than type Double. **/
    bcmpe_d             ,/** compare int_8 equal with type Double. **/
    bucmpe_d            ,/** compare unsigned uint_8 equal with type Double. **/
    bcmple_d            ,/** compare int_8 less than or equal to type Double. **/
    bucmple_d           ,/** compare unsigned uint_8 less than or equal to type Double. **/
    bcmpge_d            ,/** compare int_8 greater than or equal to type Double. **/
    bucmpge_d           ,/** compare unsigned uint_8 greater than or equal to type Double. **/
    bcmpne_d            ,/** compare int_8 not equal with type Double. **/
    bucmpne_d           ,/** compare unsigned uint_8 not equal with type Double. **/
    bcast_df            ,/** cast int_8 to type DoubleFloat. **/
    bucast_df           ,/** cast unsigned uint_8 to type DoubleFloat. **/
    badd_df             ,/** add int_8 with type DoubleFloat. **/
    buadd_df            ,/** add unsigned uint_8 with type DoubleFloat. **/
    bsub_df             ,/** subtract int_8 with type DoubleFloat. **/
    busub_df            ,/** subtract unsigned uint_8 with type DoubleFloat. **/
    bmul_df             ,/** multiply int_8 with type DoubleFloat. **/
    bumul_df            ,/** multiply unsigned uint_8 with type DoubleFloat. **/
    bdiv_df             ,/** divide int_8 with type DoubleFloat. **/
    budiv_df            ,/** divide unsigned uint_8 with type DoubleFloat. **/
    bcmpl_df            ,/** compare int_8 less than type DoubleFloat. **/
    bucmpl_df           ,/** compare unsigned uint_8 less than type DoubleFloat. **/
    bcmpg_df            ,/** compare int_8 greater than type DoubleFloat. **/
    bucmpg_df           ,/** compare unsigned uint_8 greater than type DoubleFloat. **/
    bcmpe_df            ,/** compare int_8 equal with type DoubleFloat. **/
    bucmpe_df           ,/** compare unsigned uint_8 equal with type DoubleFloat. **/
    bcmple_df           ,/** compare int_8 less than or equal to type DoubleFloat. **/
    bucmple_df          ,/** compare unsigned uint_8 less than or equal to type DoubleFloat. **/
    bcmpge_df           ,/** compare int_8 greater than or equal to type DoubleFloat. **/
    bucmpge_df          ,/** compare unsigned uint_8 greater than or equal to type DoubleFloat. **/
    bcmpne_df           ,/** compare int_8 not equal with type DoubleFloat. **/
    bucmpne_df          ,/** compare unsigned uint_8 not equal with type DoubleFloat. **/
    bcast_dd            ,/** cast int_8 to type DoubleDouble. **/
    bucast_dd           ,/** cast unsigned uint_8 to type DoubleDouble. **/
    badd_dd             ,/** add int_8 with type DoubleDouble. **/
    buadd_dd            ,/** add unsigned uint_8 with type DoubleDouble. **/
    bsub_dd             ,/** subtract int_8 with type DoubleDouble. **/
    busub_dd            ,/** subtract unsigned uint_8 with type DoubleDouble. **/
    bmul_dd             ,/** multiply int_8 with type DoubleDouble. **/
    bumul_dd            ,/** multiply unsigned uint_8 with type DoubleDouble. **/
    bdiv_dd             ,/** divide int_8 with type DoubleDouble. **/
    budiv_dd            ,/** divide unsigned uint_8 with type DoubleDouble. **/
    bcmpl_dd            ,/** compare int_8 less than type DoubleDouble. **/
    bucmpl_dd           ,/** compare unsigned uint_8 less than type DoubleDouble. **/
    bcmpg_dd            ,/** compare int_8 greater than type DoubleDouble. **/
    bucmpg_dd           ,/** compare unsigned uint_8 greater than type DoubleDouble. **/
    bcmpe_dd            ,/** compare int_8 equal with type DoubleDouble. **/
    bucmpe_dd           ,/** compare unsigned uint_8 equal with type DoubleDouble. **/
    bcmple_dd           ,/** compare int_8 less than or equal to type DoubleDouble. **/
    bucmple_dd          ,/** compare unsigned uint_8 less than or equal to type DoubleDouble. **/
    bcmpge_dd           ,/** compare int_8 greater than or equal to type DoubleDouble. **/
    bucmpge_dd          ,/** compare unsigned uint_8 greater than or equal to type DoubleDouble. **/
    bcmpne_dd           ,/** compare int_8 not equal with type DoubleDouble. **/
    bucmpne_dd          ,/** compare unsigned uint_8 not equal with type DoubleDouble. **/
    bmod_b              ,/** modulo int_8 with type Byte. **/
    bcast_ub            ,/** cast int_8 to unsigned type Byte. **/
    bucast_ub           ,/** cast unsigned uint_8 to unsigned type Byte. **/
    badd_ub             ,/** add int_8 with unsigned type Byte. **/
    buadd_ub            ,/** add unsigned uint_8 with unsigned type Byte. **/
    bsub_ub             ,/** subtract int_8 with unsigned type Byte. **/
    busub_ub            ,/** subtract unsigned uint_8 with unsigned type Byte. **/
    bmul_ub             ,/** multiply int_8 with unsigned type Byte. **/
    bumul_ub            ,/** multiply unsigned uint_8 with unsigned type Byte. **/
    bdiv_ub             ,/** divide int_8 with unsigned type Byte. **/
    budiv_ub            ,/** divide unsigned uint_8 with unsigned type Byte. **/
    bcmpl_ub            ,/** compare int_8 less than unsigned type Byte. **/
    bucmpl_ub           ,/** compare unsigned uint_8 less than unsigned type Byte. **/
    bcmpg_ub            ,/** compare int_8 greater than unsigned type Byte. **/
    bucmpg_ub           ,/** compare unsigned uint_8 greater than unsigned type Byte. **/
    bcmpe_ub            ,/** compare int_8 equal with unsigned type Byte. **/
    bucmpe_ub           ,/** compare unsigned uint_8 equal with unsigned type Byte. **/
    bcmple_ub           ,/** compare int_8 less than or equal to unsigned type Byte. **/
    bucmple_ub          ,/** compare unsigned uint_8 less than or equal to unsigned type Byte. **/
    bcmpge_ub           ,/** compare int_8 greater than or equal to unsigned type Byte. **/
    bucmpge_ub          ,/** compare unsigned uint_8 greater than or equal to unsigned type Byte. **/
    bcmpne_ub           ,/** compare int_8 not equal with unsigned type Byte. **/
    bucmpne_ub          ,/** compare unsigned uint_8 not equal with unsigned type Byte. **/
    bmod_s              ,/** modulo int_8 with type Short. **/
    bcast_us            ,/** cast int_8 to unsigned type Short. **/
    bucast_us           ,/** cast unsigned uint_8 to unsigned type Short. **/
    badd_us             ,/** add int_8 with unsigned type Short. **/
    buadd_us            ,/** add unsigned uint_8 with unsigned type Short. **/
    bsub_us             ,/** subtract int_8 with unsigned type Short. **/
    busub_us            ,/** subtract unsigned uint_8 with unsigned type Short. **/
    bmul_us             ,/** multiply int_8 with unsigned type Short. **/
    bumul_us            ,/** multiply unsigned uint_8 with unsigned type Short. **/
    bdiv_us             ,/** divide int_8 with unsigned type Short. **/
    budiv_us            ,/** divide unsigned uint_8 with unsigned type Short. **/
    bcmpl_us            ,/** compare int_8 less than unsigned type Short. **/
    bucmpl_us           ,/** compare unsigned uint_8 less than unsigned type Short. **/
    bcmpg_us            ,/** compare int_8 greater than unsigned type Short. **/
    bucmpg_us           ,/** compare unsigned uint_8 greater than unsigned type Short. **/
    bcmpe_us            ,/** compare int_8 equal with unsigned type Short. **/
    bucmpe_us           ,/** compare unsigned uint_8 equal with unsigned type Short. **/
    bcmple_us           ,/** compare int_8 less than or equal to unsigned type Short. **/
    bucmple_us          ,/** compare unsigned uint_8 less than or equal to unsigned type Short. **/
    bcmpge_us           ,/** compare int_8 greater than or equal to unsigned type Short. **/
    bucmpge_us          ,/** compare unsigned uint_8 greater than or equal to unsigned type Short. **/
    bcmpne_us           ,/** compare int_8 not equal with unsigned type Short. **/
    bucmpne_us          ,/** compare unsigned uint_8 not equal with unsigned type Short. **/
    bmod_i              ,/** modulo int_8 with type Int. **/
    bcast_ui            ,/** cast int_8 to unsigned type Int. **/
    bucast_ui           ,/** cast unsigned uint_8 to unsigned type Int. **/
    badd_ui             ,/** add int_8 with unsigned type Int. **/
    buadd_ui            ,/** add unsigned uint_8 with unsigned type Int. **/
    bsub_ui             ,/** subtract int_8 with unsigned type Int. **/
    busub_ui            ,/** subtract unsigned uint_8 with unsigned type Int. **/
    bmul_ui             ,/** multiply int_8 with unsigned type Int. **/
    bumul_ui            ,/** multiply unsigned uint_8 with unsigned type Int. **/
    bdiv_ui             ,/** divide int_8 with unsigned type Int. **/
    budiv_ui            ,/** divide unsigned uint_8 with unsigned type Int. **/
    bcmpl_ui            ,/** compare int_8 less than unsigned type Int. **/
    bucmpl_ui           ,/** compare unsigned uint_8 less than unsigned type Int. **/
    bcmpg_ui            ,/** compare int_8 greater than unsigned type Int. **/
    bucmpg_ui           ,/** compare unsigned uint_8 greater than unsigned type Int. **/
    bcmpe_ui            ,/** compare int_8 equal with unsigned type Int. **/
    bucmpe_ui           ,/** compare unsigned uint_8 equal with unsigned type Int. **/
    bcmple_ui           ,/** compare int_8 less than or equal to unsigned type Int. **/
    bucmple_ui          ,/** compare unsigned uint_8 less than or equal to unsigned type Int. **/
    bcmpge_ui           ,/** compare int_8 greater than or equal to unsigned type Int. **/
    bucmpge_ui          ,/** compare unsigned uint_8 greater than or equal to unsigned type Int. **/
    bcmpne_ui           ,/** compare int_8 not equal with unsigned type Int. **/
    bucmpne_ui          ,/** compare unsigned uint_8 not equal with unsigned type Int. **/
    bmod_l              ,/** modulo int_8 with type Long. **/
    bcast_ul            ,/** cast int_8 to unsigned type Long. **/
    bucast_ul           ,/** cast unsigned uint_8 to unsigned type Long. **/
    badd_ul             ,/** add int_8 with unsigned type Long. **/
    buadd_ul            ,/** add unsigned uint_8 with unsigned type Long. **/
    bsub_ul             ,/** subtract int_8 with unsigned type Long. **/
    busub_ul            ,/** subtract unsigned uint_8 with unsigned type Long. **/
    bmul_ul             ,/** multiply int_8 with unsigned type Long. **/
    bumul_ul            ,/** multiply unsigned uint_8 with unsigned type Long. **/
    bdiv_ul             ,/** divide int_8 with unsigned type Long. **/
    budiv_ul            ,/** divide unsigned uint_8 with unsigned type Long. **/
    bcmpl_ul            ,/** compare int_8 less than unsigned type Long. **/
    bucmpl_ul           ,/** compare unsigned uint_8 less than unsigned type Long. **/
    bcmpg_ul            ,/** compare int_8 greater than unsigned type Long. **/
    bucmpg_ul           ,/** compare unsigned uint_8 greater than unsigned type Long. **/
    bcmpe_ul            ,/** compare int_8 equal with unsigned type Long. **/
    bucmpe_ul           ,/** compare unsigned uint_8 equal with unsigned type Long. **/
    bcmple_ul           ,/** compare int_8 less than or equal to unsigned type Long. **/
    bucmple_ul          ,/** compare unsigned uint_8 less than or equal to unsigned type Long. **/
    bcmpge_ul           ,/** compare int_8 greater than or equal to unsigned type Long. **/
    bucmpge_ul          ,/** compare unsigned uint_8 greater than or equal to unsigned type Long. **/
    bcmpne_ul           ,/** compare int_8 not equal with unsigned type Long. **/
    bucmpne_ul          ,/** compare unsigned uint_8 not equal with unsigned type Long. **/
    bmod_li             ,/** modulo int_8 with type LongInt. **/
    bcast_uli           ,/** cast int_8 to unsigned type LongInt. **/
    bucast_uli          ,/** cast unsigned uint_8 to unsigned type LongInt. **/
    badd_uli            ,/** add int_8 with unsigned type LongInt. **/
    buadd_uli           ,/** add unsigned uint_8 with unsigned type LongInt. **/
    bsub_uli            ,/** subtract int_8 with unsigned type LongInt. **/
    busub_uli           ,/** subtract unsigned uint_8 with unsigned type LongInt. **/
    bmul_uli            ,/** multiply int_8 with unsigned type LongInt. **/
    bumul_uli           ,/** multiply unsigned uint_8 with unsigned type LongInt. **/
    bdiv_uli            ,/** divide int_8 with unsigned type LongInt. **/
    budiv_uli           ,/** divide unsigned uint_8 with unsigned type LongInt. **/
    bcmpl_uli           ,/** compare int_8 less than unsigned type LongInt. **/
    bucmpl_uli          ,/** compare unsigned uint_8 less than unsigned type LongInt. **/
    bcmpg_uli           ,/** compare int_8 greater than unsigned type LongInt. **/
    bucmpg_uli          ,/** compare unsigned uint_8 greater than unsigned type LongInt. **/
    bcmpe_uli           ,/** compare int_8 equal with unsigned type LongInt. **/
    bucmpe_uli          ,/** compare unsigned uint_8 equal with unsigned type LongInt. **/
    bcmple_uli          ,/** compare int_8 less than or equal to unsigned type LongInt. **/
    bucmple_uli         ,/** compare unsigned uint_8 less than or equal to unsigned type LongInt. **/
    bcmpge_uli          ,/** compare int_8 greater than or equal to unsigned type LongInt. **/
    bucmpge_uli         ,/** compare unsigned uint_8 greater than or equal to unsigned type LongInt. **/
    bcmpne_uli          ,/** compare int_8 not equal with unsigned type LongInt. **/
    bucmpne_uli         ,/** compare unsigned uint_8 not equal with unsigned type LongInt. **/
    bmod_ll             ,/** modulo int_8 with type LongLong. **/
    bcast_ull           ,/** cast int_8 to unsigned type LongLong. **/
    bucast_ull          ,/** cast unsigned uint_8 to unsigned type LongLong. **/
    badd_ull            ,/** add int_8 with unsigned type LongLong. **/
    buadd_ull           ,/** add unsigned uint_8 with unsigned type LongLong. **/
    bsub_ull            ,/** subtract int_8 with unsigned type LongLong. **/
    busub_ull           ,/** subtract unsigned uint_8 with unsigned type LongLong. **/
    bmul_ull            ,/** multiply int_8 with unsigned type LongLong. **/
    bumul_ull           ,/** multiply unsigned uint_8 with unsigned type LongLong. **/
    bdiv_ull            ,/** divide int_8 with unsigned type LongLong. **/
    budiv_ull           ,/** divide unsigned uint_8 with unsigned type LongLong. **/
    bcmpl_ull           ,/** compare int_8 less than unsigned type LongLong. **/
    bucmpl_ull          ,/** compare unsigned uint_8 less than unsigned type LongLong. **/
    bcmpg_ull           ,/** compare int_8 greater than unsigned type LongLong. **/
    bucmpg_ull          ,/** compare unsigned uint_8 greater than unsigned type LongLong. **/
    bcmpe_ull           ,/** compare int_8 equal with unsigned type LongLong. **/
    bucmpe_ull          ,/** compare unsigned uint_8 equal with unsigned type LongLong. **/
    bcmple_ull          ,/** compare int_8 less than or equal to unsigned type LongLong. **/
    bucmple_ull         ,/** compare unsigned uint_8 less than or equal to unsigned type LongLong. **/
    bcmpge_ull          ,/** compare int_8 greater than or equal to unsigned type LongLong. **/
    bucmpge_ull         ,/** compare unsigned uint_8 greater than or equal to unsigned type LongLong. **/
    bcmpne_ull          ,/** compare int_8 not equal with unsigned type LongLong. **/
    bucmpne_ull         ,/** compare unsigned uint_8 not equal with unsigned type LongLong. **/
    band_b              ,/** bitwise and int_8 with type Byte. **/
    bor_b               ,/** bitwise or int_8 with type Byte. **/
    bxor_b              ,/** bitwise xor int_8 with type Byte. **/
    bshftr_b            ,/** shift right int_8 with type Byte. **/
    bshftl_b            ,/** shift left xor int_8 with type Byte. **/
    band_s              ,/** bitwise and int_8 with type Short. **/
    bor_s               ,/** bitwise or int_8 with type Short. **/
    bxor_s              ,/** bitwise xor int_8 with type Short. **/
    bshftr_s            ,/** shift right int_8 with type Short. **/
    bshftl_s            ,/** shift left xor int_8 with type Short. **/
    band_i              ,/** bitwise and int_8 with type Int. **/
    bor_i               ,/** bitwise or int_8 with type Int. **/
    bxor_i              ,/** bitwise xor int_8 with type Int. **/
    bshftr_i            ,/** shift right int_8 with type Int. **/
    bshftl_i            ,/** shift left xor int_8 with type Int. **/
    band_l              ,/** bitwise and int_8 with type Long. **/
    bor_l               ,/** bitwise or int_8 with type Long. **/
    bxor_l              ,/** bitwise xor int_8 with type Long. **/
    bshftr_l            ,/** shift right int_8 with type Long. **/
    bshftl_l            ,/** shift left xor int_8 with type Long. **/
    band_li             ,/** bitwise and int_8 with type LongInt. **/
    bor_li              ,/** bitwise or int_8 with type LongInt. **/
    bxor_li             ,/** bitwise xor int_8 with type LongInt. **/
    bshftr_li           ,/** shift right int_8 with type LongInt. **/
    bshftl_li           ,/** shift left xor int_8 with type LongInt. **/
    band_ll             ,/** bitwise and int_8 with type LongLong. **/
    bor_ll              ,/** bitwise or int_8 with type LongLong. **/
    bxor_ll             ,/** bitwise xor int_8 with type LongLong. **/
    bshftr_ll           ,/** shift right int_8 with type LongLong. **/
    bshftl_ll           ,/** shift left xor int_8 with type LongLong. **/
    bdup                ,/** duplicate a int_8 on the stack. **/
    bdup2               ,/** duplicate a int_8 2 times on the stack. **/
    bdup3               ,/** duplicate a int_8 3 times on the stack. **/
    bdup4               ,/** duplicate a int_8 4 times on the stack. **/
    bdup5               ,/** duplicate a int_8 5 times on the stack. **/
    bset                ,/** set a int_8 from stack into a field on base pointer. **/
    bget                ,/** get a int_8 from a field on base pointer to stack. **/
    bvset               ,/** set a int_8 from value into a field on base pointer. **/
    bsget               ,/** get a int_8 from a field on base pointer to stack using address from stack. **/
    bsset               ,/** set a int_8 from stack into a field on base pointer using address from stack. **/
    bsetl               ,/** set a int_8 from local variable into a field on base pointer. **/
    binc_1              ,/** increment int_8 by 1 on stack. **/
    binc_2              ,/** increment int_8 by 2 on stack. **/
    bstinc_1            ,/** increment int_8 by 1 on stack. **/
    bstinc_2            ,/** increment int_8 by 2 on stack. **/
    breturn             ,/** return a int_8 into the main stack. **/
    bmainst             ,/** store a int_8 from main stack in a local variable.. **/
    bmainst_0           ,/** store a int_8 from main stack in local variable 0. **/
    bmainst_1           ,/** store a int_8 from main stack in local variable 1. **/
    bmainst_2           ,/** store a int_8 from main stack in local variable 2. **/
    bmainst_3           ,/** store a int_8 from main stack in local variable 3. **/
    bprint              ,/** print a int_8 from stack. **/
    buprint             ,/** print a unsigned uint_8 from stack. **/
    sprintba            ,/** print a byte array. **/
    sconst              ,/** push a const int_16 into the stack. **/
    sconst_0            ,/** push a const int_16 into the stack (value = 0). **/
    sconst_1            ,/** push a const int_16 into the stack (value = 1). **/
    sconst_2            ,/** push a const int_16 into the stack (value = 2). **/
    sconst_3            ,/** push a const int_16 into the stack (value = 3). **/
    sconst_4            ,/** push a const int_16 into the stack (value = 4). **/
    sconst_5            ,/** push a const int_16 into the stack (value = 5). **/
    sconst_6            ,/** push a const int_16 into the stack (value = 6). **/
    sconst_9            ,/** push a const int_16 into the stack (value = 9). **/
    sconst_10           ,/** push a const int_16 into the stack (value = 10). **/
    sconst_11           ,/** push a const int_16 into the stack (value = 11). **/
    sconst_12           ,/** push a const int_16 into the stack (value = 12). **/
    sload               ,/** load a int_16 into the stack from local variable. **/
    sload_0             ,/** load a int_16 into the stack from local variable 0. **/
    sload_1             ,/** load a int_16 into the stack from local variable 1. **/
    sload_2             ,/** load a int_16 into the stack from local variable 2. **/
    sload_3             ,/** load a int_16 into the stack from local variable 3. **/
    sload_4             ,/** load a int_16 into the stack from local variable 4. **/
    sstore              ,/** store a int_16 from stack into local variable. **/
    sstore_0            ,/** store a int_16 from stack into local variable 0. **/
    sstore_1            ,/** store a int_16 from stack into local variable 1. **/
    sstore_2            ,/** store a int_16 from stack into local variable 2. **/
    sstore_3            ,/** store a int_16 from stack into local variable 3. **/
    sstore_4            ,/** store a int_16 from stack into local variable 4. **/
    scast_b             ,/** cast int_16 to type Byte. **/
    sucast_b            ,/** cast unsigned uint_16 to type Byte. **/
    sadd_b              ,/** add int_16 with type Byte. **/
    suadd_b             ,/** add unsigned uint_16 with type Byte. **/
    ssub_b              ,/** subtract int_16 with type Byte. **/
    susub_b             ,/** subtract unsigned uint_16 with type Byte. **/
    smul_b              ,/** multiply int_16 with type Byte. **/
    sumul_b             ,/** multiply unsigned uint_16 with type Byte. **/
    sdiv_b              ,/** divide int_16 with type Byte. **/
    sudiv_b             ,/** divide unsigned uint_16 with type Byte. **/
    scmpl_b             ,/** compare int_16 less than type Byte. **/
    sucmpl_b            ,/** compare unsigned uint_16 less than type Byte. **/
    scmpg_b             ,/** compare int_16 greater than type Byte. **/
    sucmpg_b            ,/** compare unsigned uint_16 greater than type Byte. **/
    scmpe_b             ,/** compare int_16 equal with type Byte. **/
    sucmpe_b            ,/** compare unsigned uint_16 equal with type Byte. **/
    scmple_b            ,/** compare int_16 less than or equal to type Byte. **/
    sucmple_b           ,/** compare unsigned uint_16 less than or equal to type Byte. **/
    scmpge_b            ,/** compare int_16 greater than or equal to type Byte. **/
    sucmpge_b           ,/** compare unsigned uint_16 greater than or equal to type Byte. **/
    scmpne_b            ,/** compare int_16 not equal with type Byte. **/
    sucmpne_b           ,/** compare unsigned uint_16 not equal with type Byte. **/
    scast_s             ,/** cast int_16 to type Short. **/
    sucast_s            ,/** cast unsigned uint_16 to type Short. **/
    sadd_s              ,/** add int_16 with type Short. **/
    suadd_s             ,/** add unsigned uint_16 with type Short. **/
    ssub_s              ,/** subtract int_16 with type Short. **/
    susub_s             ,/** subtract unsigned uint_16 with type Short. **/
    smul_s              ,/** multiply int_16 with type Short. **/
    sumul_s             ,/** multiply unsigned uint_16 with type Short. **/
    sdiv_s              ,/** divide int_16 with type Short. **/
    sudiv_s             ,/** divide unsigned uint_16 with type Short. **/
    scmpl_s             ,/** compare int_16 less than type Short. **/
    sucmpl_s            ,/** compare unsigned uint_16 less than type Short. **/
    scmpg_s             ,/** compare int_16 greater than type Short. **/
    sucmpg_s            ,/** compare unsigned uint_16 greater than type Short. **/
    scmpe_s             ,/** compare int_16 equal with type Short. **/
    sucmpe_s            ,/** compare unsigned uint_16 equal with type Short. **/
    scmple_s            ,/** compare int_16 less than or equal to type Short. **/
    sucmple_s           ,/** compare unsigned uint_16 less than or equal to type Short. **/
    scmpge_s            ,/** compare int_16 greater than or equal to type Short. **/
    sucmpge_s           ,/** compare unsigned uint_16 greater than or equal to type Short. **/
    scmpne_s            ,/** compare int_16 not equal with type Short. **/
    sucmpne_s           ,/** compare unsigned uint_16 not equal with type Short. **/
    scast_i             ,/** cast int_16 to type Int. **/
    sucast_i            ,/** cast unsigned uint_16 to type Int. **/
    sadd_i              ,/** add int_16 with type Int. **/
    suadd_i             ,/** add unsigned uint_16 with type Int. **/
    ssub_i              ,/** subtract int_16 with type Int. **/
    susub_i             ,/** subtract unsigned uint_16 with type Int. **/
    smul_i              ,/** multiply int_16 with type Int. **/
    sumul_i             ,/** multiply unsigned uint_16 with type Int. **/
    sdiv_i              ,/** divide int_16 with type Int. **/
    sudiv_i             ,/** divide unsigned uint_16 with type Int. **/
    scmpl_i             ,/** compare int_16 less than type Int. **/
    sucmpl_i            ,/** compare unsigned uint_16 less than type Int. **/
    scmpg_i             ,/** compare int_16 greater than type Int. **/
    sucmpg_i            ,/** compare unsigned uint_16 greater than type Int. **/
    scmpe_i             ,/** compare int_16 equal with type Int. **/
    sucmpe_i            ,/** compare unsigned uint_16 equal with type Int. **/
    scmple_i            ,/** compare int_16 less than or equal to type Int. **/
    sucmple_i           ,/** compare unsigned uint_16 less than or equal to type Int. **/
    scmpge_i            ,/** compare int_16 greater than or equal to type Int. **/
    sucmpge_i           ,/** compare unsigned uint_16 greater than or equal to type Int. **/
    scmpne_i            ,/** compare int_16 not equal with type Int. **/
    sucmpne_i           ,/** compare unsigned uint_16 not equal with type Int. **/
    scast_l             ,/** cast int_16 to type Long. **/
    sucast_l            ,/** cast unsigned uint_16 to type Long. **/
    sadd_l              ,/** add int_16 with type Long. **/
    suadd_l             ,/** add unsigned uint_16 with type Long. **/
    ssub_l              ,/** subtract int_16 with type Long. **/
    susub_l             ,/** subtract unsigned uint_16 with type Long. **/
    smul_l              ,/** multiply int_16 with type Long. **/
    sumul_l             ,/** multiply unsigned uint_16 with type Long. **/
    sdiv_l              ,/** divide int_16 with type Long. **/
    sudiv_l             ,/** divide unsigned uint_16 with type Long. **/
    scmpl_l             ,/** compare int_16 less than type Long. **/
    sucmpl_l            ,/** compare unsigned uint_16 less than type Long. **/
    scmpg_l             ,/** compare int_16 greater than type Long. **/
    sucmpg_l            ,/** compare unsigned uint_16 greater than type Long. **/
    scmpe_l             ,/** compare int_16 equal with type Long. **/
    sucmpe_l            ,/** compare unsigned uint_16 equal with type Long. **/
    scmple_l            ,/** compare int_16 less than or equal to type Long. **/
    sucmple_l           ,/** compare unsigned uint_16 less than or equal to type Long. **/
    scmpge_l            ,/** compare int_16 greater than or equal to type Long. **/
    sucmpge_l           ,/** compare unsigned uint_16 greater than or equal to type Long. **/
    scmpne_l            ,/** compare int_16 not equal with type Long. **/
    sucmpne_l           ,/** compare unsigned uint_16 not equal with type Long. **/
    scast_li            ,/** cast int_16 to type LongInt. **/
    sucast_li           ,/** cast unsigned uint_16 to type LongInt. **/
    sadd_li             ,/** add int_16 with type LongInt. **/
    suadd_li            ,/** add unsigned uint_16 with type LongInt. **/
    ssub_li             ,/** subtract int_16 with type LongInt. **/
    susub_li            ,/** subtract unsigned uint_16 with type LongInt. **/
    smul_li             ,/** multiply int_16 with type LongInt. **/
    sumul_li            ,/** multiply unsigned uint_16 with type LongInt. **/
    sdiv_li             ,/** divide int_16 with type LongInt. **/
    sudiv_li            ,/** divide unsigned uint_16 with type LongInt. **/
    scmpl_li            ,/** compare int_16 less than type LongInt. **/
    sucmpl_li           ,/** compare unsigned uint_16 less than type LongInt. **/
    scmpg_li            ,/** compare int_16 greater than type LongInt. **/
    sucmpg_li           ,/** compare unsigned uint_16 greater than type LongInt. **/
    scmpe_li            ,/** compare int_16 equal with type LongInt. **/
    sucmpe_li           ,/** compare unsigned uint_16 equal with type LongInt. **/
    scmple_li           ,/** compare int_16 less than or equal to type LongInt. **/
    sucmple_li          ,/** compare unsigned uint_16 less than or equal to type LongInt. **/
    scmpge_li           ,/** compare int_16 greater than or equal to type LongInt. **/
    sucmpge_li          ,/** compare unsigned uint_16 greater than or equal to type LongInt. **/
    scmpne_li           ,/** compare int_16 not equal with type LongInt. **/
    sucmpne_li          ,/** compare unsigned uint_16 not equal with type LongInt. **/
    scast_ll            ,/** cast int_16 to type LongLong. **/
    sucast_ll           ,/** cast unsigned uint_16 to type LongLong. **/
    sadd_ll             ,/** add int_16 with type LongLong. **/
    suadd_ll            ,/** add unsigned uint_16 with type LongLong. **/
    ssub_ll             ,/** subtract int_16 with type LongLong. **/
    susub_ll            ,/** subtract unsigned uint_16 with type LongLong. **/
    smul_ll             ,/** multiply int_16 with type LongLong. **/
    sumul_ll            ,/** multiply unsigned uint_16 with type LongLong. **/
    sdiv_ll             ,/** divide int_16 with type LongLong. **/
    sudiv_ll            ,/** divide unsigned uint_16 with type LongLong. **/
    scmpl_ll            ,/** compare int_16 less than type LongLong. **/
    sucmpl_ll           ,/** compare unsigned uint_16 less than type LongLong. **/
    scmpg_ll            ,/** compare int_16 greater than type LongLong. **/
    sucmpg_ll           ,/** compare unsigned uint_16 greater than type LongLong. **/
    scmpe_ll            ,/** compare int_16 equal with type LongLong. **/
    sucmpe_ll           ,/** compare unsigned uint_16 equal with type LongLong. **/
    scmple_ll           ,/** compare int_16 less than or equal to type LongLong. **/
    sucmple_ll          ,/** compare unsigned uint_16 less than or equal to type LongLong. **/
    scmpge_ll           ,/** compare int_16 greater than or equal to type LongLong. **/
    sucmpge_ll          ,/** compare unsigned uint_16 greater than or equal to type LongLong. **/
    scmpne_ll           ,/** compare int_16 not equal with type LongLong. **/
    sucmpne_ll          ,/** compare unsigned uint_16 not equal with type LongLong. **/
    scast_f             ,/** cast int_16 to type Float. **/
    sucast_f            ,/** cast unsigned uint_16 to type Float. **/
    sadd_f              ,/** add int_16 with type Float. **/
    suadd_f             ,/** add unsigned uint_16 with type Float. **/
    ssub_f              ,/** subtract int_16 with type Float. **/
    susub_f             ,/** subtract unsigned uint_16 with type Float. **/
    smul_f              ,/** multiply int_16 with type Float. **/
    sumul_f             ,/** multiply unsigned uint_16 with type Float. **/
    sdiv_f              ,/** divide int_16 with type Float. **/
    sudiv_f             ,/** divide unsigned uint_16 with type Float. **/
    scmpl_f             ,/** compare int_16 less than type Float. **/
    sucmpl_f            ,/** compare unsigned uint_16 less than type Float. **/
    scmpg_f             ,/** compare int_16 greater than type Float. **/
    sucmpg_f            ,/** compare unsigned uint_16 greater than type Float. **/
    scmpe_f             ,/** compare int_16 equal with type Float. **/
    sucmpe_f            ,/** compare unsigned uint_16 equal with type Float. **/
    scmple_f            ,/** compare int_16 less than or equal to type Float. **/
    sucmple_f           ,/** compare unsigned uint_16 less than or equal to type Float. **/
    scmpge_f            ,/** compare int_16 greater than or equal to type Float. **/
    sucmpge_f           ,/** compare unsigned uint_16 greater than or equal to type Float. **/
    scmpne_f            ,/** compare int_16 not equal with type Float. **/
    sucmpne_f           ,/** compare unsigned uint_16 not equal with type Float. **/
    scast_d             ,/** cast int_16 to type Double. **/
    sucast_d            ,/** cast unsigned uint_16 to type Double. **/
    sadd_d              ,/** add int_16 with type Double. **/
    suadd_d             ,/** add unsigned uint_16 with type Double. **/
    ssub_d              ,/** subtract int_16 with type Double. **/
    susub_d             ,/** subtract unsigned uint_16 with type Double. **/
    smul_d              ,/** multiply int_16 with type Double. **/
    sumul_d             ,/** multiply unsigned uint_16 with type Double. **/
    sdiv_d              ,/** divide int_16 with type Double. **/
    sudiv_d             ,/** divide unsigned uint_16 with type Double. **/
    scmpl_d             ,/** compare int_16 less than type Double. **/
    sucmpl_d            ,/** compare unsigned uint_16 less than type Double. **/
    scmpg_d             ,/** compare int_16 greater than type Double. **/
    sucmpg_d            ,/** compare unsigned uint_16 greater than type Double. **/
    scmpe_d             ,/** compare int_16 equal with type Double. **/
    sucmpe_d            ,/** compare unsigned uint_16 equal with type Double. **/
    scmple_d            ,/** compare int_16 less than or equal to type Double. **/
    sucmple_d           ,/** compare unsigned uint_16 less than or equal to type Double. **/
    scmpge_d            ,/** compare int_16 greater than or equal to type Double. **/
    sucmpge_d           ,/** compare unsigned uint_16 greater than or equal to type Double. **/
    scmpne_d            ,/** compare int_16 not equal with type Double. **/
    sucmpne_d           ,/** compare unsigned uint_16 not equal with type Double. **/
    scast_df            ,/** cast int_16 to type DoubleFloat. **/
    sucast_df           ,/** cast unsigned uint_16 to type DoubleFloat. **/
    sadd_df             ,/** add int_16 with type DoubleFloat. **/
    suadd_df            ,/** add unsigned uint_16 with type DoubleFloat. **/
    ssub_df             ,/** subtract int_16 with type DoubleFloat. **/
    susub_df            ,/** subtract unsigned uint_16 with type DoubleFloat. **/
    smul_df             ,/** multiply int_16 with type DoubleFloat. **/
    sumul_df            ,/** multiply unsigned uint_16 with type DoubleFloat. **/
    sdiv_df             ,/** divide int_16 with type DoubleFloat. **/
    sudiv_df            ,/** divide unsigned uint_16 with type DoubleFloat. **/
    scmpl_df            ,/** compare int_16 less than type DoubleFloat. **/
    sucmpl_df           ,/** compare unsigned uint_16 less than type DoubleFloat. **/
    scmpg_df            ,/** compare int_16 greater than type DoubleFloat. **/
    sucmpg_df           ,/** compare unsigned uint_16 greater than type DoubleFloat. **/
    scmpe_df            ,/** compare int_16 equal with type DoubleFloat. **/
    sucmpe_df           ,/** compare unsigned uint_16 equal with type DoubleFloat. **/
    scmple_df           ,/** compare int_16 less than or equal to type DoubleFloat. **/
    sucmple_df          ,/** compare unsigned uint_16 less than or equal to type DoubleFloat. **/
    scmpge_df           ,/** compare int_16 greater than or equal to type DoubleFloat. **/
    sucmpge_df          ,/** compare unsigned uint_16 greater than or equal to type DoubleFloat. **/
    scmpne_df           ,/** compare int_16 not equal with type DoubleFloat. **/
    sucmpne_df          ,/** compare unsigned uint_16 not equal with type DoubleFloat. **/
    scast_dd            ,/** cast int_16 to type DoubleDouble. **/
    sucast_dd           ,/** cast unsigned uint_16 to type DoubleDouble. **/
    sadd_dd             ,/** add int_16 with type DoubleDouble. **/
    suadd_dd            ,/** add unsigned uint_16 with type DoubleDouble. **/
    ssub_dd             ,/** subtract int_16 with type DoubleDouble. **/
    susub_dd            ,/** subtract unsigned uint_16 with type DoubleDouble. **/
    smul_dd             ,/** multiply int_16 with type DoubleDouble. **/
    sumul_dd            ,/** multiply unsigned uint_16 with type DoubleDouble. **/
    sdiv_dd             ,/** divide int_16 with type DoubleDouble. **/
    sudiv_dd            ,/** divide unsigned uint_16 with type DoubleDouble. **/
    scmpl_dd            ,/** compare int_16 less than type DoubleDouble. **/
    sucmpl_dd           ,/** compare unsigned uint_16 less than type DoubleDouble. **/
    scmpg_dd            ,/** compare int_16 greater than type DoubleDouble. **/
    sucmpg_dd           ,/** compare unsigned uint_16 greater than type DoubleDouble. **/
    scmpe_dd            ,/** compare int_16 equal with type DoubleDouble. **/
    sucmpe_dd           ,/** compare unsigned uint_16 equal with type DoubleDouble. **/
    scmple_dd           ,/** compare int_16 less than or equal to type DoubleDouble. **/
    sucmple_dd          ,/** compare unsigned uint_16 less than or equal to type DoubleDouble. **/
    scmpge_dd           ,/** compare int_16 greater than or equal to type DoubleDouble. **/
    sucmpge_dd          ,/** compare unsigned uint_16 greater than or equal to type DoubleDouble. **/
    scmpne_dd           ,/** compare int_16 not equal with type DoubleDouble. **/
    sucmpne_dd          ,/** compare unsigned uint_16 not equal with type DoubleDouble. **/
    smod_b              ,/** modulo int_16 with type Byte. **/
    scast_ub            ,/** cast int_16 to unsigned type Byte. **/
    sucast_ub           ,/** cast unsigned uint_16 to unsigned type Byte. **/
    sadd_ub             ,/** add int_16 with unsigned type Byte. **/
    suadd_ub            ,/** add unsigned uint_16 with unsigned type Byte. **/
    ssub_ub             ,/** subtract int_16 with unsigned type Byte. **/
    susub_ub            ,/** subtract unsigned uint_16 with unsigned type Byte. **/
    smul_ub             ,/** multiply int_16 with unsigned type Byte. **/
    sumul_ub            ,/** multiply unsigned uint_16 with unsigned type Byte. **/
    sdiv_ub             ,/** divide int_16 with unsigned type Byte. **/
    sudiv_ub            ,/** divide unsigned uint_16 with unsigned type Byte. **/
    scmpl_ub            ,/** compare int_16 less than unsigned type Byte. **/
    sucmpl_ub           ,/** compare unsigned uint_16 less than unsigned type Byte. **/
    scmpg_ub            ,/** compare int_16 greater than unsigned type Byte. **/
    sucmpg_ub           ,/** compare unsigned uint_16 greater than unsigned type Byte. **/
    scmpe_ub            ,/** compare int_16 equal with unsigned type Byte. **/
    sucmpe_ub           ,/** compare unsigned uint_16 equal with unsigned type Byte. **/
    scmple_ub           ,/** compare int_16 less than or equal to unsigned type Byte. **/
    sucmple_ub          ,/** compare unsigned uint_16 less than or equal to unsigned type Byte. **/
    scmpge_ub           ,/** compare int_16 greater than or equal to unsigned type Byte. **/
    sucmpge_ub          ,/** compare unsigned uint_16 greater than or equal to unsigned type Byte. **/
    scmpne_ub           ,/** compare int_16 not equal with unsigned type Byte. **/
    sucmpne_ub          ,/** compare unsigned uint_16 not equal with unsigned type Byte. **/
    smod_s              ,/** modulo int_16 with type Short. **/
    scast_us            ,/** cast int_16 to unsigned type Short. **/
    sucast_us           ,/** cast unsigned uint_16 to unsigned type Short. **/
    sadd_us             ,/** add int_16 with unsigned type Short. **/
    suadd_us            ,/** add unsigned uint_16 with unsigned type Short. **/
    ssub_us             ,/** subtract int_16 with unsigned type Short. **/
    susub_us            ,/** subtract unsigned uint_16 with unsigned type Short. **/
    smul_us             ,/** multiply int_16 with unsigned type Short. **/
    sumul_us            ,/** multiply unsigned uint_16 with unsigned type Short. **/
    sdiv_us             ,/** divide int_16 with unsigned type Short. **/
    sudiv_us            ,/** divide unsigned uint_16 with unsigned type Short. **/
    scmpl_us            ,/** compare int_16 less than unsigned type Short. **/
    sucmpl_us           ,/** compare unsigned uint_16 less than unsigned type Short. **/
    scmpg_us            ,/** compare int_16 greater than unsigned type Short. **/
    sucmpg_us           ,/** compare unsigned uint_16 greater than unsigned type Short. **/
    scmpe_us            ,/** compare int_16 equal with unsigned type Short. **/
    sucmpe_us           ,/** compare unsigned uint_16 equal with unsigned type Short. **/
    scmple_us           ,/** compare int_16 less than or equal to unsigned type Short. **/
    sucmple_us          ,/** compare unsigned uint_16 less than or equal to unsigned type Short. **/
    scmpge_us           ,/** compare int_16 greater than or equal to unsigned type Short. **/
    sucmpge_us          ,/** compare unsigned uint_16 greater than or equal to unsigned type Short. **/
    scmpne_us           ,/** compare int_16 not equal with unsigned type Short. **/
    sucmpne_us          ,/** compare unsigned uint_16 not equal with unsigned type Short. **/
    smod_i              ,/** modulo int_16 with type Int. **/
    scast_ui            ,/** cast int_16 to unsigned type Int. **/
    sucast_ui           ,/** cast unsigned uint_16 to unsigned type Int. **/
    sadd_ui             ,/** add int_16 with unsigned type Int. **/
    suadd_ui            ,/** add unsigned uint_16 with unsigned type Int. **/
    ssub_ui             ,/** subtract int_16 with unsigned type Int. **/
    susub_ui            ,/** subtract unsigned uint_16 with unsigned type Int. **/
    smul_ui             ,/** multiply int_16 with unsigned type Int. **/
    sumul_ui            ,/** multiply unsigned uint_16 with unsigned type Int. **/
    sdiv_ui             ,/** divide int_16 with unsigned type Int. **/
    sudiv_ui            ,/** divide unsigned uint_16 with unsigned type Int. **/
    scmpl_ui            ,/** compare int_16 less than unsigned type Int. **/
    sucmpl_ui           ,/** compare unsigned uint_16 less than unsigned type Int. **/
    scmpg_ui            ,/** compare int_16 greater than unsigned type Int. **/
    sucmpg_ui           ,/** compare unsigned uint_16 greater than unsigned type Int. **/
    scmpe_ui            ,/** compare int_16 equal with unsigned type Int. **/
    sucmpe_ui           ,/** compare unsigned uint_16 equal with unsigned type Int. **/
    scmple_ui           ,/** compare int_16 less than or equal to unsigned type Int. **/
    sucmple_ui          ,/** compare unsigned uint_16 less than or equal to unsigned type Int. **/
    scmpge_ui           ,/** compare int_16 greater than or equal to unsigned type Int. **/
    sucmpge_ui          ,/** compare unsigned uint_16 greater than or equal to unsigned type Int. **/
    scmpne_ui           ,/** compare int_16 not equal with unsigned type Int. **/
    sucmpne_ui          ,/** compare unsigned uint_16 not equal with unsigned type Int. **/
    smod_l              ,/** modulo int_16 with type Long. **/
    scast_ul            ,/** cast int_16 to unsigned type Long. **/
    sucast_ul           ,/** cast unsigned uint_16 to unsigned type Long. **/
    sadd_ul             ,/** add int_16 with unsigned type Long. **/
    suadd_ul            ,/** add unsigned uint_16 with unsigned type Long. **/
    ssub_ul             ,/** subtract int_16 with unsigned type Long. **/
    susub_ul            ,/** subtract unsigned uint_16 with unsigned type Long. **/
    smul_ul             ,/** multiply int_16 with unsigned type Long. **/
    sumul_ul            ,/** multiply unsigned uint_16 with unsigned type Long. **/
    sdiv_ul             ,/** divide int_16 with unsigned type Long. **/
    sudiv_ul            ,/** divide unsigned uint_16 with unsigned type Long. **/
    scmpl_ul            ,/** compare int_16 less than unsigned type Long. **/
    sucmpl_ul           ,/** compare unsigned uint_16 less than unsigned type Long. **/
    scmpg_ul            ,/** compare int_16 greater than unsigned type Long. **/
    sucmpg_ul           ,/** compare unsigned uint_16 greater than unsigned type Long. **/
    scmpe_ul            ,/** compare int_16 equal with unsigned type Long. **/
    sucmpe_ul           ,/** compare unsigned uint_16 equal with unsigned type Long. **/
    scmple_ul           ,/** compare int_16 less than or equal to unsigned type Long. **/
    sucmple_ul          ,/** compare unsigned uint_16 less than or equal to unsigned type Long. **/
    scmpge_ul           ,/** compare int_16 greater than or equal to unsigned type Long. **/
    sucmpge_ul          ,/** compare unsigned uint_16 greater than or equal to unsigned type Long. **/
    scmpne_ul           ,/** compare int_16 not equal with unsigned type Long. **/
    sucmpne_ul          ,/** compare unsigned uint_16 not equal with unsigned type Long. **/
    smod_li             ,/** modulo int_16 with type LongInt. **/
    scast_uli           ,/** cast int_16 to unsigned type LongInt. **/
    sucast_uli          ,/** cast unsigned uint_16 to unsigned type LongInt. **/
    sadd_uli            ,/** add int_16 with unsigned type LongInt. **/
    suadd_uli           ,/** add unsigned uint_16 with unsigned type LongInt. **/
    ssub_uli            ,/** subtract int_16 with unsigned type LongInt. **/
    susub_uli           ,/** subtract unsigned uint_16 with unsigned type LongInt. **/
    smul_uli            ,/** multiply int_16 with unsigned type LongInt. **/
    sumul_uli           ,/** multiply unsigned uint_16 with unsigned type LongInt. **/
    sdiv_uli            ,/** divide int_16 with unsigned type LongInt. **/
    sudiv_uli           ,/** divide unsigned uint_16 with unsigned type LongInt. **/
    scmpl_uli           ,/** compare int_16 less than unsigned type LongInt. **/
    sucmpl_uli          ,/** compare unsigned uint_16 less than unsigned type LongInt. **/
    scmpg_uli           ,/** compare int_16 greater than unsigned type LongInt. **/
    sucmpg_uli          ,/** compare unsigned uint_16 greater than unsigned type LongInt. **/
    scmpe_uli           ,/** compare int_16 equal with unsigned type LongInt. **/
    sucmpe_uli          ,/** compare unsigned uint_16 equal with unsigned type LongInt. **/
    scmple_uli          ,/** compare int_16 less than or equal to unsigned type LongInt. **/
    sucmple_uli         ,/** compare unsigned uint_16 less than or equal to unsigned type LongInt. **/
    scmpge_uli          ,/** compare int_16 greater than or equal to unsigned type LongInt. **/
    sucmpge_uli         ,/** compare unsigned uint_16 greater than or equal to unsigned type LongInt. **/
    scmpne_uli          ,/** compare int_16 not equal with unsigned type LongInt. **/
    sucmpne_uli         ,/** compare unsigned uint_16 not equal with unsigned type LongInt. **/
    smod_ll             ,/** modulo int_16 with type LongLong. **/
    scast_ull           ,/** cast int_16 to unsigned type LongLong. **/
    sucast_ull          ,/** cast unsigned uint_16 to unsigned type LongLong. **/
    sadd_ull            ,/** add int_16 with unsigned type LongLong. **/
    suadd_ull           ,/** add unsigned uint_16 with unsigned type LongLong. **/
    ssub_ull            ,/** subtract int_16 with unsigned type LongLong. **/
    susub_ull           ,/** subtract unsigned uint_16 with unsigned type LongLong. **/
    smul_ull            ,/** multiply int_16 with unsigned type LongLong. **/
    sumul_ull           ,/** multiply unsigned uint_16 with unsigned type LongLong. **/
    sdiv_ull            ,/** divide int_16 with unsigned type LongLong. **/
    sudiv_ull           ,/** divide unsigned uint_16 with unsigned type LongLong. **/
    scmpl_ull           ,/** compare int_16 less than unsigned type LongLong. **/
    sucmpl_ull          ,/** compare unsigned uint_16 less than unsigned type LongLong. **/
    scmpg_ull           ,/** compare int_16 greater than unsigned type LongLong. **/
    sucmpg_ull          ,/** compare unsigned uint_16 greater than unsigned type LongLong. **/
    scmpe_ull           ,/** compare int_16 equal with unsigned type LongLong. **/
    sucmpe_ull          ,/** compare unsigned uint_16 equal with unsigned type LongLong. **/
    scmple_ull          ,/** compare int_16 less than or equal to unsigned type LongLong. **/
    sucmple_ull         ,/** compare unsigned uint_16 less than or equal to unsigned type LongLong. **/
    scmpge_ull          ,/** compare int_16 greater than or equal to unsigned type LongLong. **/
    sucmpge_ull         ,/** compare unsigned uint_16 greater than or equal to unsigned type LongLong. **/
    scmpne_ull          ,/** compare int_16 not equal with unsigned type LongLong. **/
    sucmpne_ull         ,/** compare unsigned uint_16 not equal with unsigned type LongLong. **/
    sand_b              ,/** bitwise and int_16 with type Byte. **/
    sor_b               ,/** bitwise or int_16 with type Byte. **/
    sxor_b              ,/** bitwise xor int_16 with type Byte. **/
    sshftr_b            ,/** shift right int_16 with type Byte. **/
    sshftl_b            ,/** shift left xor int_16 with type Byte. **/
    sand_s              ,/** bitwise and int_16 with type Short. **/
    sor_s               ,/** bitwise or int_16 with type Short. **/
    sxor_s              ,/** bitwise xor int_16 with type Short. **/
    sshftr_s            ,/** shift right int_16 with type Short. **/
    sshftl_s            ,/** shift left xor int_16 with type Short. **/
    sand_i              ,/** bitwise and int_16 with type Int. **/
    sor_i               ,/** bitwise or int_16 with type Int. **/
    sxor_i              ,/** bitwise xor int_16 with type Int. **/
    sshftr_i            ,/** shift right int_16 with type Int. **/
    sshftl_i            ,/** shift left xor int_16 with type Int. **/
    sand_l              ,/** bitwise and int_16 with type Long. **/
    sor_l               ,/** bitwise or int_16 with type Long. **/
    sxor_l              ,/** bitwise xor int_16 with type Long. **/
    sshftr_l            ,/** shift right int_16 with type Long. **/
    sshftl_l            ,/** shift left xor int_16 with type Long. **/
    sand_li             ,/** bitwise and int_16 with type LongInt. **/
    sor_li              ,/** bitwise or int_16 with type LongInt. **/
    sxor_li             ,/** bitwise xor int_16 with type LongInt. **/
    sshftr_li           ,/** shift right int_16 with type LongInt. **/
    sshftl_li           ,/** shift left xor int_16 with type LongInt. **/
    sand_ll             ,/** bitwise and int_16 with type LongLong. **/
    sor_ll              ,/** bitwise or int_16 with type LongLong. **/
    sxor_ll             ,/** bitwise xor int_16 with type LongLong. **/
    sshftr_ll           ,/** shift right int_16 with type LongLong. **/
    sshftl_ll           ,/** shift left xor int_16 with type LongLong. **/
    sdup                ,/** duplicate a int_16 on the stack. **/
    sdup2               ,/** duplicate a int_16 2 times on the stack. **/
    sdup3               ,/** duplicate a int_16 3 times on the stack. **/
    sdup4               ,/** duplicate a int_16 4 times on the stack. **/
    sdup5               ,/** duplicate a int_16 5 times on the stack. **/
    sset                ,/** set a int_16 from stack into a field on base pointer. **/
    sget                ,/** get a int_16 from a field on base pointer to stack. **/
    svset               ,/** set a int_16 from value into a field on base pointer. **/
    ssget               ,/** get a int_16 from a field on base pointer to stack using address from stack. **/
    ssset               ,/** set a int_16 from stack into a field on base pointer using address from stack. **/
    ssetl               ,/** set a int_16 from local variable into a field on base pointer. **/
    sinc_1              ,/** increment int_16 by 1 on stack. **/
    sinc_2              ,/** increment int_16 by 2 on stack. **/
    sstinc_1            ,/** increment int_16 by 1 on stack. **/
    sstinc_2            ,/** increment int_16 by 2 on stack. **/
    sreturn             ,/** return a int_16 into the main stack. **/
    smainst             ,/** store a int_16 from main stack in a local variable.. **/
    smainst_0           ,/** store a int_16 from main stack in local variable 0. **/
    smainst_1           ,/** store a int_16 from main stack in local variable 1. **/
    smainst_2           ,/** store a int_16 from main stack in local variable 2. **/
    smainst_3           ,/** store a int_16 from main stack in local variable 3. **/
    sprint              ,/** print a int_16 from stack. **/
    suprint             ,/** print a unsigned uint_16 from stack. **/
    iprintba            ,/** print a byte array. **/
    iconst              ,/** push a const int_32 into the stack. **/
    iconst_0            ,/** push a const int_32 into the stack (value = 0). **/
    iconst_1            ,/** push a const int_32 into the stack (value = 1). **/
    iconst_2            ,/** push a const int_32 into the stack (value = 2). **/
    iconst_3            ,/** push a const int_32 into the stack (value = 3). **/
    iconst_4            ,/** push a const int_32 into the stack (value = 4). **/
    iconst_5            ,/** push a const int_32 into the stack (value = 5). **/
    iconst_6            ,/** push a const int_32 into the stack (value = 6). **/
    iconst_9            ,/** push a const int_32 into the stack (value = 9). **/
    iconst_10           ,/** push a const int_32 into the stack (value = 10). **/
    iconst_11           ,/** push a const int_32 into the stack (value = 11). **/
    iconst_12           ,/** push a const int_32 into the stack (value = 12). **/
    iload               ,/** load a int_32 into the stack from local variable. **/
    iload_0             ,/** load a int_32 into the stack from local variable 0. **/
    iload_1             ,/** load a int_32 into the stack from local variable 1. **/
    iload_2             ,/** load a int_32 into the stack from local variable 2. **/
    iload_3             ,/** load a int_32 into the stack from local variable 3. **/
    iload_4             ,/** load a int_32 into the stack from local variable 4. **/
    istore              ,/** store a int_32 from stack into local variable. **/
    istore_0            ,/** store a int_32 from stack into local variable 0. **/
    istore_1            ,/** store a int_32 from stack into local variable 1. **/
    istore_2            ,/** store a int_32 from stack into local variable 2. **/
    istore_3            ,/** store a int_32 from stack into local variable 3. **/
    istore_4            ,/** store a int_32 from stack into local variable 4. **/
    icast_b             ,/** cast int_32 to type Byte. **/
    iucast_b            ,/** cast unsigned uint_32 to type Byte. **/
    iadd_b              ,/** add int_32 with type Byte. **/
    iuadd_b             ,/** add unsigned uint_32 with type Byte. **/
    isub_b              ,/** subtract int_32 with type Byte. **/
    iusub_b             ,/** subtract unsigned uint_32 with type Byte. **/
    imul_b              ,/** multiply int_32 with type Byte. **/
    iumul_b             ,/** multiply unsigned uint_32 with type Byte. **/
    idiv_b              ,/** divide int_32 with type Byte. **/
    iudiv_b             ,/** divide unsigned uint_32 with type Byte. **/
    icmpl_b             ,/** compare int_32 less than type Byte. **/
    iucmpl_b            ,/** compare unsigned uint_32 less than type Byte. **/
    icmpg_b             ,/** compare int_32 greater than type Byte. **/
    iucmpg_b            ,/** compare unsigned uint_32 greater than type Byte. **/
    icmpe_b             ,/** compare int_32 equal with type Byte. **/
    iucmpe_b            ,/** compare unsigned uint_32 equal with type Byte. **/
    icmple_b            ,/** compare int_32 less than or equal to type Byte. **/
    iucmple_b           ,/** compare unsigned uint_32 less than or equal to type Byte. **/
    icmpge_b            ,/** compare int_32 greater than or equal to type Byte. **/
    iucmpge_b           ,/** compare unsigned uint_32 greater than or equal to type Byte. **/
    icmpne_b            ,/** compare int_32 not equal with type Byte. **/
    iucmpne_b           ,/** compare unsigned uint_32 not equal with type Byte. **/
    icast_s             ,/** cast int_32 to type Short. **/
    iucast_s            ,/** cast unsigned uint_32 to type Short. **/
    iadd_s              ,/** add int_32 with type Short. **/
    iuadd_s             ,/** add unsigned uint_32 with type Short. **/
    isub_s              ,/** subtract int_32 with type Short. **/
    iusub_s             ,/** subtract unsigned uint_32 with type Short. **/
    imul_s              ,/** multiply int_32 with type Short. **/
    iumul_s             ,/** multiply unsigned uint_32 with type Short. **/
    idiv_s              ,/** divide int_32 with type Short. **/
    iudiv_s             ,/** divide unsigned uint_32 with type Short. **/
    icmpl_s             ,/** compare int_32 less than type Short. **/
    iucmpl_s            ,/** compare unsigned uint_32 less than type Short. **/
    icmpg_s             ,/** compare int_32 greater than type Short. **/
    iucmpg_s            ,/** compare unsigned uint_32 greater than type Short. **/
    icmpe_s             ,/** compare int_32 equal with type Short. **/
    iucmpe_s            ,/** compare unsigned uint_32 equal with type Short. **/
    icmple_s            ,/** compare int_32 less than or equal to type Short. **/
    iucmple_s           ,/** compare unsigned uint_32 less than or equal to type Short. **/
    icmpge_s            ,/** compare int_32 greater than or equal to type Short. **/
    iucmpge_s           ,/** compare unsigned uint_32 greater than or equal to type Short. **/
    icmpne_s            ,/** compare int_32 not equal with type Short. **/
    iucmpne_s           ,/** compare unsigned uint_32 not equal with type Short. **/
    icast_i             ,/** cast int_32 to type Int. **/
    iucast_i            ,/** cast unsigned uint_32 to type Int. **/
    iadd_i              ,/** add int_32 with type Int. **/
    iuadd_i             ,/** add unsigned uint_32 with type Int. **/
    isub_i              ,/** subtract int_32 with type Int. **/
    iusub_i             ,/** subtract unsigned uint_32 with type Int. **/
    imul_i              ,/** multiply int_32 with type Int. **/
    iumul_i             ,/** multiply unsigned uint_32 with type Int. **/
    idiv_i              ,/** divide int_32 with type Int. **/
    iudiv_i             ,/** divide unsigned uint_32 with type Int. **/
    icmpl_i             ,/** compare int_32 less than type Int. **/
    iucmpl_i            ,/** compare unsigned uint_32 less than type Int. **/
    icmpg_i             ,/** compare int_32 greater than type Int. **/
    iucmpg_i            ,/** compare unsigned uint_32 greater than type Int. **/
    icmpe_i             ,/** compare int_32 equal with type Int. **/
    iucmpe_i            ,/** compare unsigned uint_32 equal with type Int. **/
    icmple_i            ,/** compare int_32 less than or equal to type Int. **/
    iucmple_i           ,/** compare unsigned uint_32 less than or equal to type Int. **/
    icmpge_i            ,/** compare int_32 greater than or equal to type Int. **/
    iucmpge_i           ,/** compare unsigned uint_32 greater than or equal to type Int. **/
    icmpne_i            ,/** compare int_32 not equal with type Int. **/
    iucmpne_i           ,/** compare unsigned uint_32 not equal with type Int. **/
    icast_l             ,/** cast int_32 to type Long. **/
    iucast_l            ,/** cast unsigned uint_32 to type Long. **/
    iadd_l              ,/** add int_32 with type Long. **/
    iuadd_l             ,/** add unsigned uint_32 with type Long. **/
    isub_l              ,/** subtract int_32 with type Long. **/
    iusub_l             ,/** subtract unsigned uint_32 with type Long. **/
    imul_l              ,/** multiply int_32 with type Long. **/
    iumul_l             ,/** multiply unsigned uint_32 with type Long. **/
    idiv_l              ,/** divide int_32 with type Long. **/
    iudiv_l             ,/** divide unsigned uint_32 with type Long. **/
    icmpl_l             ,/** compare int_32 less than type Long. **/
    iucmpl_l            ,/** compare unsigned uint_32 less than type Long. **/
    icmpg_l             ,/** compare int_32 greater than type Long. **/
    iucmpg_l            ,/** compare unsigned uint_32 greater than type Long. **/
    icmpe_l             ,/** compare int_32 equal with type Long. **/
    iucmpe_l            ,/** compare unsigned uint_32 equal with type Long. **/
    icmple_l            ,/** compare int_32 less than or equal to type Long. **/
    iucmple_l           ,/** compare unsigned uint_32 less than or equal to type Long. **/
    icmpge_l            ,/** compare int_32 greater than or equal to type Long. **/
    iucmpge_l           ,/** compare unsigned uint_32 greater than or equal to type Long. **/
    icmpne_l            ,/** compare int_32 not equal with type Long. **/
    iucmpne_l           ,/** compare unsigned uint_32 not equal with type Long. **/
    icast_li            ,/** cast int_32 to type LongInt. **/
    iucast_li           ,/** cast unsigned uint_32 to type LongInt. **/
    iadd_li             ,/** add int_32 with type LongInt. **/
    iuadd_li            ,/** add unsigned uint_32 with type LongInt. **/
    isub_li             ,/** subtract int_32 with type LongInt. **/
    iusub_li            ,/** subtract unsigned uint_32 with type LongInt. **/
    imul_li             ,/** multiply int_32 with type LongInt. **/
    iumul_li            ,/** multiply unsigned uint_32 with type LongInt. **/
    idiv_li             ,/** divide int_32 with type LongInt. **/
    iudiv_li            ,/** divide unsigned uint_32 with type LongInt. **/
    icmpl_li            ,/** compare int_32 less than type LongInt. **/
    iucmpl_li           ,/** compare unsigned uint_32 less than type LongInt. **/
    icmpg_li            ,/** compare int_32 greater than type LongInt. **/
    iucmpg_li           ,/** compare unsigned uint_32 greater than type LongInt. **/
    icmpe_li            ,/** compare int_32 equal with type LongInt. **/
    iucmpe_li           ,/** compare unsigned uint_32 equal with type LongInt. **/
    icmple_li           ,/** compare int_32 less than or equal to type LongInt. **/
    iucmple_li          ,/** compare unsigned uint_32 less than or equal to type LongInt. **/
    icmpge_li           ,/** compare int_32 greater than or equal to type LongInt. **/
    iucmpge_li          ,/** compare unsigned uint_32 greater than or equal to type LongInt. **/
    icmpne_li           ,/** compare int_32 not equal with type LongInt. **/
    iucmpne_li          ,/** compare unsigned uint_32 not equal with type LongInt. **/
    icast_ll            ,/** cast int_32 to type LongLong. **/
    iucast_ll           ,/** cast unsigned uint_32 to type LongLong. **/
    iadd_ll             ,/** add int_32 with type LongLong. **/
    iuadd_ll            ,/** add unsigned uint_32 with type LongLong. **/
    isub_ll             ,/** subtract int_32 with type LongLong. **/
    iusub_ll            ,/** subtract unsigned uint_32 with type LongLong. **/
    imul_ll             ,/** multiply int_32 with type LongLong. **/
    iumul_ll            ,/** multiply unsigned uint_32 with type LongLong. **/
    idiv_ll             ,/** divide int_32 with type LongLong. **/
    iudiv_ll            ,/** divide unsigned uint_32 with type LongLong. **/
    icmpl_ll            ,/** compare int_32 less than type LongLong. **/
    iucmpl_ll           ,/** compare unsigned uint_32 less than type LongLong. **/
    icmpg_ll            ,/** compare int_32 greater than type LongLong. **/
    iucmpg_ll           ,/** compare unsigned uint_32 greater than type LongLong. **/
    icmpe_ll            ,/** compare int_32 equal with type LongLong. **/
    iucmpe_ll           ,/** compare unsigned uint_32 equal with type LongLong. **/
    icmple_ll           ,/** compare int_32 less than or equal to type LongLong. **/
    iucmple_ll          ,/** compare unsigned uint_32 less than or equal to type LongLong. **/
    icmpge_ll           ,/** compare int_32 greater than or equal to type LongLong. **/
    iucmpge_ll          ,/** compare unsigned uint_32 greater than or equal to type LongLong. **/
    icmpne_ll           ,/** compare int_32 not equal with type LongLong. **/
    iucmpne_ll          ,/** compare unsigned uint_32 not equal with type LongLong. **/
    icast_f             ,/** cast int_32 to type Float. **/
    iucast_f            ,/** cast unsigned uint_32 to type Float. **/
    iadd_f              ,/** add int_32 with type Float. **/
    iuadd_f             ,/** add unsigned uint_32 with type Float. **/
    isub_f              ,/** subtract int_32 with type Float. **/
    iusub_f             ,/** subtract unsigned uint_32 with type Float. **/
    imul_f              ,/** multiply int_32 with type Float. **/
    iumul_f             ,/** multiply unsigned uint_32 with type Float. **/
    idiv_f              ,/** divide int_32 with type Float. **/
    iudiv_f             ,/** divide unsigned uint_32 with type Float. **/
    icmpl_f             ,/** compare int_32 less than type Float. **/
    iucmpl_f            ,/** compare unsigned uint_32 less than type Float. **/
    icmpg_f             ,/** compare int_32 greater than type Float. **/
    iucmpg_f            ,/** compare unsigned uint_32 greater than type Float. **/
    icmpe_f             ,/** compare int_32 equal with type Float. **/
    iucmpe_f            ,/** compare unsigned uint_32 equal with type Float. **/
    icmple_f            ,/** compare int_32 less than or equal to type Float. **/
    iucmple_f           ,/** compare unsigned uint_32 less than or equal to type Float. **/
    icmpge_f            ,/** compare int_32 greater than or equal to type Float. **/
    iucmpge_f           ,/** compare unsigned uint_32 greater than or equal to type Float. **/
    icmpne_f            ,/** compare int_32 not equal with type Float. **/
    iucmpne_f           ,/** compare unsigned uint_32 not equal with type Float. **/
    icast_d             ,/** cast int_32 to type Double. **/
    iucast_d            ,/** cast unsigned uint_32 to type Double. **/
    iadd_d              ,/** add int_32 with type Double. **/
    iuadd_d             ,/** add unsigned uint_32 with type Double. **/
    isub_d              ,/** subtract int_32 with type Double. **/
    iusub_d             ,/** subtract unsigned uint_32 with type Double. **/
    imul_d              ,/** multiply int_32 with type Double. **/
    iumul_d             ,/** multiply unsigned uint_32 with type Double. **/
    idiv_d              ,/** divide int_32 with type Double. **/
    iudiv_d             ,/** divide unsigned uint_32 with type Double. **/
    icmpl_d             ,/** compare int_32 less than type Double. **/
    iucmpl_d            ,/** compare unsigned uint_32 less than type Double. **/
    icmpg_d             ,/** compare int_32 greater than type Double. **/
    iucmpg_d            ,/** compare unsigned uint_32 greater than type Double. **/
    icmpe_d             ,/** compare int_32 equal with type Double. **/
    iucmpe_d            ,/** compare unsigned uint_32 equal with type Double. **/
    icmple_d            ,/** compare int_32 less than or equal to type Double. **/
    iucmple_d           ,/** compare unsigned uint_32 less than or equal to type Double. **/
    icmpge_d            ,/** compare int_32 greater than or equal to type Double. **/
    iucmpge_d           ,/** compare unsigned uint_32 greater than or equal to type Double. **/
    icmpne_d            ,/** compare int_32 not equal with type Double. **/
    iucmpne_d           ,/** compare unsigned uint_32 not equal with type Double. **/
    icast_df            ,/** cast int_32 to type DoubleFloat. **/
    iucast_df           ,/** cast unsigned uint_32 to type DoubleFloat. **/
    iadd_df             ,/** add int_32 with type DoubleFloat. **/
    iuadd_df            ,/** add unsigned uint_32 with type DoubleFloat. **/
    isub_df             ,/** subtract int_32 with type DoubleFloat. **/
    iusub_df            ,/** subtract unsigned uint_32 with type DoubleFloat. **/
    imul_df             ,/** multiply int_32 with type DoubleFloat. **/
    iumul_df            ,/** multiply unsigned uint_32 with type DoubleFloat. **/
    idiv_df             ,/** divide int_32 with type DoubleFloat. **/
    iudiv_df            ,/** divide unsigned uint_32 with type DoubleFloat. **/
    icmpl_df            ,/** compare int_32 less than type DoubleFloat. **/
    iucmpl_df           ,/** compare unsigned uint_32 less than type DoubleFloat. **/
    icmpg_df            ,/** compare int_32 greater than type DoubleFloat. **/
    iucmpg_df           ,/** compare unsigned uint_32 greater than type DoubleFloat. **/
    icmpe_df            ,/** compare int_32 equal with type DoubleFloat. **/
    iucmpe_df           ,/** compare unsigned uint_32 equal with type DoubleFloat. **/
    icmple_df           ,/** compare int_32 less than or equal to type DoubleFloat. **/
    iucmple_df          ,/** compare unsigned uint_32 less than or equal to type DoubleFloat. **/
    icmpge_df           ,/** compare int_32 greater than or equal to type DoubleFloat. **/
    iucmpge_df          ,/** compare unsigned uint_32 greater than or equal to type DoubleFloat. **/
    icmpne_df           ,/** compare int_32 not equal with type DoubleFloat. **/
    iucmpne_df          ,/** compare unsigned uint_32 not equal with type DoubleFloat. **/
    icast_dd            ,/** cast int_32 to type DoubleDouble. **/
    iucast_dd           ,/** cast unsigned uint_32 to type DoubleDouble. **/
    iadd_dd             ,/** add int_32 with type DoubleDouble. **/
    iuadd_dd            ,/** add unsigned uint_32 with type DoubleDouble. **/
    isub_dd             ,/** subtract int_32 with type DoubleDouble. **/
    iusub_dd            ,/** subtract unsigned uint_32 with type DoubleDouble. **/
    imul_dd             ,/** multiply int_32 with type DoubleDouble. **/
    iumul_dd            ,/** multiply unsigned uint_32 with type DoubleDouble. **/
    idiv_dd             ,/** divide int_32 with type DoubleDouble. **/
    iudiv_dd            ,/** divide unsigned uint_32 with type DoubleDouble. **/
    icmpl_dd            ,/** compare int_32 less than type DoubleDouble. **/
    iucmpl_dd           ,/** compare unsigned uint_32 less than type DoubleDouble. **/
    icmpg_dd            ,/** compare int_32 greater than type DoubleDouble. **/
    iucmpg_dd           ,/** compare unsigned uint_32 greater than type DoubleDouble. **/
    icmpe_dd            ,/** compare int_32 equal with type DoubleDouble. **/
    iucmpe_dd           ,/** compare unsigned uint_32 equal with type DoubleDouble. **/
    icmple_dd           ,/** compare int_32 less than or equal to type DoubleDouble. **/
    iucmple_dd          ,/** compare unsigned uint_32 less than or equal to type DoubleDouble. **/
    icmpge_dd           ,/** compare int_32 greater than or equal to type DoubleDouble. **/
    iucmpge_dd          ,/** compare unsigned uint_32 greater than or equal to type DoubleDouble. **/
    icmpne_dd           ,/** compare int_32 not equal with type DoubleDouble. **/
    iucmpne_dd          ,/** compare unsigned uint_32 not equal with type DoubleDouble. **/
    imod_b              ,/** modulo int_32 with type Byte. **/
    icast_ub            ,/** cast int_32 to unsigned type Byte. **/
    iucast_ub           ,/** cast unsigned uint_32 to unsigned type Byte. **/
    iadd_ub             ,/** add int_32 with unsigned type Byte. **/
    iuadd_ub            ,/** add unsigned uint_32 with unsigned type Byte. **/
    isub_ub             ,/** subtract int_32 with unsigned type Byte. **/
    iusub_ub            ,/** subtract unsigned uint_32 with unsigned type Byte. **/
    imul_ub             ,/** multiply int_32 with unsigned type Byte. **/
    iumul_ub            ,/** multiply unsigned uint_32 with unsigned type Byte. **/
    idiv_ub             ,/** divide int_32 with unsigned type Byte. **/
    iudiv_ub            ,/** divide unsigned uint_32 with unsigned type Byte. **/
    icmpl_ub            ,/** compare int_32 less than unsigned type Byte. **/
    iucmpl_ub           ,/** compare unsigned uint_32 less than unsigned type Byte. **/
    icmpg_ub            ,/** compare int_32 greater than unsigned type Byte. **/
    iucmpg_ub           ,/** compare unsigned uint_32 greater than unsigned type Byte. **/
    icmpe_ub            ,/** compare int_32 equal with unsigned type Byte. **/
    iucmpe_ub           ,/** compare unsigned uint_32 equal with unsigned type Byte. **/
    icmple_ub           ,/** compare int_32 less than or equal to unsigned type Byte. **/
    iucmple_ub          ,/** compare unsigned uint_32 less than or equal to unsigned type Byte. **/
    icmpge_ub           ,/** compare int_32 greater than or equal to unsigned type Byte. **/
    iucmpge_ub          ,/** compare unsigned uint_32 greater than or equal to unsigned type Byte. **/
    icmpne_ub           ,/** compare int_32 not equal with unsigned type Byte. **/
    iucmpne_ub          ,/** compare unsigned uint_32 not equal with unsigned type Byte. **/
    imod_s              ,/** modulo int_32 with type Short. **/
    icast_us            ,/** cast int_32 to unsigned type Short. **/
    iucast_us           ,/** cast unsigned uint_32 to unsigned type Short. **/
    iadd_us             ,/** add int_32 with unsigned type Short. **/
    iuadd_us            ,/** add unsigned uint_32 with unsigned type Short. **/
    isub_us             ,/** subtract int_32 with unsigned type Short. **/
    iusub_us            ,/** subtract unsigned uint_32 with unsigned type Short. **/
    imul_us             ,/** multiply int_32 with unsigned type Short. **/
    iumul_us            ,/** multiply unsigned uint_32 with unsigned type Short. **/
    idiv_us             ,/** divide int_32 with unsigned type Short. **/
    iudiv_us            ,/** divide unsigned uint_32 with unsigned type Short. **/
    icmpl_us            ,/** compare int_32 less than unsigned type Short. **/
    iucmpl_us           ,/** compare unsigned uint_32 less than unsigned type Short. **/
    icmpg_us            ,/** compare int_32 greater than unsigned type Short. **/
    iucmpg_us           ,/** compare unsigned uint_32 greater than unsigned type Short. **/
    icmpe_us            ,/** compare int_32 equal with unsigned type Short. **/
    iucmpe_us           ,/** compare unsigned uint_32 equal with unsigned type Short. **/
    icmple_us           ,/** compare int_32 less than or equal to unsigned type Short. **/
    iucmple_us          ,/** compare unsigned uint_32 less than or equal to unsigned type Short. **/
    icmpge_us           ,/** compare int_32 greater than or equal to unsigned type Short. **/
    iucmpge_us          ,/** compare unsigned uint_32 greater than or equal to unsigned type Short. **/
    icmpne_us           ,/** compare int_32 not equal with unsigned type Short. **/
    iucmpne_us          ,/** compare unsigned uint_32 not equal with unsigned type Short. **/
    imod_i              ,/** modulo int_32 with type Int. **/
    icast_ui            ,/** cast int_32 to unsigned type Int. **/
    iucast_ui           ,/** cast unsigned uint_32 to unsigned type Int. **/
    iadd_ui             ,/** add int_32 with unsigned type Int. **/
    iuadd_ui            ,/** add unsigned uint_32 with unsigned type Int. **/
    isub_ui             ,/** subtract int_32 with unsigned type Int. **/
    iusub_ui            ,/** subtract unsigned uint_32 with unsigned type Int. **/
    imul_ui             ,/** multiply int_32 with unsigned type Int. **/
    iumul_ui            ,/** multiply unsigned uint_32 with unsigned type Int. **/
    idiv_ui             ,/** divide int_32 with unsigned type Int. **/
    iudiv_ui            ,/** divide unsigned uint_32 with unsigned type Int. **/
    icmpl_ui            ,/** compare int_32 less than unsigned type Int. **/
    iucmpl_ui           ,/** compare unsigned uint_32 less than unsigned type Int. **/
    icmpg_ui            ,/** compare int_32 greater than unsigned type Int. **/
    iucmpg_ui           ,/** compare unsigned uint_32 greater than unsigned type Int. **/
    icmpe_ui            ,/** compare int_32 equal with unsigned type Int. **/
    iucmpe_ui           ,/** compare unsigned uint_32 equal with unsigned type Int. **/
    icmple_ui           ,/** compare int_32 less than or equal to unsigned type Int. **/
    iucmple_ui          ,/** compare unsigned uint_32 less than or equal to unsigned type Int. **/
    icmpge_ui           ,/** compare int_32 greater than or equal to unsigned type Int. **/
    iucmpge_ui          ,/** compare unsigned uint_32 greater than or equal to unsigned type Int. **/
    icmpne_ui           ,/** compare int_32 not equal with unsigned type Int. **/
    iucmpne_ui          ,/** compare unsigned uint_32 not equal with unsigned type Int. **/
    imod_l              ,/** modulo int_32 with type Long. **/
    icast_ul            ,/** cast int_32 to unsigned type Long. **/
    iucast_ul           ,/** cast unsigned uint_32 to unsigned type Long. **/
    iadd_ul             ,/** add int_32 with unsigned type Long. **/
    iuadd_ul            ,/** add unsigned uint_32 with unsigned type Long. **/
    isub_ul             ,/** subtract int_32 with unsigned type Long. **/
    iusub_ul            ,/** subtract unsigned uint_32 with unsigned type Long. **/
    imul_ul             ,/** multiply int_32 with unsigned type Long. **/
    iumul_ul            ,/** multiply unsigned uint_32 with unsigned type Long. **/
    idiv_ul             ,/** divide int_32 with unsigned type Long. **/
    iudiv_ul            ,/** divide unsigned uint_32 with unsigned type Long. **/
    icmpl_ul            ,/** compare int_32 less than unsigned type Long. **/
    iucmpl_ul           ,/** compare unsigned uint_32 less than unsigned type Long. **/
    icmpg_ul            ,/** compare int_32 greater than unsigned type Long. **/
    iucmpg_ul           ,/** compare unsigned uint_32 greater than unsigned type Long. **/
    icmpe_ul            ,/** compare int_32 equal with unsigned type Long. **/
    iucmpe_ul           ,/** compare unsigned uint_32 equal with unsigned type Long. **/
    icmple_ul           ,/** compare int_32 less than or equal to unsigned type Long. **/
    iucmple_ul          ,/** compare unsigned uint_32 less than or equal to unsigned type Long. **/
    icmpge_ul           ,/** compare int_32 greater than or equal to unsigned type Long. **/
    iucmpge_ul          ,/** compare unsigned uint_32 greater than or equal to unsigned type Long. **/
    icmpne_ul           ,/** compare int_32 not equal with unsigned type Long. **/
    iucmpne_ul          ,/** compare unsigned uint_32 not equal with unsigned type Long. **/
    imod_li             ,/** modulo int_32 with type LongInt. **/
    icast_uli           ,/** cast int_32 to unsigned type LongInt. **/
    iucast_uli          ,/** cast unsigned uint_32 to unsigned type LongInt. **/
    iadd_uli            ,/** add int_32 with unsigned type LongInt. **/
    iuadd_uli           ,/** add unsigned uint_32 with unsigned type LongInt. **/
    isub_uli            ,/** subtract int_32 with unsigned type LongInt. **/
    iusub_uli           ,/** subtract unsigned uint_32 with unsigned type LongInt. **/
    imul_uli            ,/** multiply int_32 with unsigned type LongInt. **/
    iumul_uli           ,/** multiply unsigned uint_32 with unsigned type LongInt. **/
    idiv_uli            ,/** divide int_32 with unsigned type LongInt. **/
    iudiv_uli           ,/** divide unsigned uint_32 with unsigned type LongInt. **/
    icmpl_uli           ,/** compare int_32 less than unsigned type LongInt. **/
    iucmpl_uli          ,/** compare unsigned uint_32 less than unsigned type LongInt. **/
    icmpg_uli           ,/** compare int_32 greater than unsigned type LongInt. **/
    iucmpg_uli          ,/** compare unsigned uint_32 greater than unsigned type LongInt. **/
    icmpe_uli           ,/** compare int_32 equal with unsigned type LongInt. **/
    iucmpe_uli          ,/** compare unsigned uint_32 equal with unsigned type LongInt. **/
    icmple_uli          ,/** compare int_32 less than or equal to unsigned type LongInt. **/
    iucmple_uli         ,/** compare unsigned uint_32 less than or equal to unsigned type LongInt. **/
    icmpge_uli          ,/** compare int_32 greater than or equal to unsigned type LongInt. **/
    iucmpge_uli         ,/** compare unsigned uint_32 greater than or equal to unsigned type LongInt. **/
    icmpne_uli          ,/** compare int_32 not equal with unsigned type LongInt. **/
    iucmpne_uli         ,/** compare unsigned uint_32 not equal with unsigned type LongInt. **/
    imod_ll             ,/** modulo int_32 with type LongLong. **/
    icast_ull           ,/** cast int_32 to unsigned type LongLong. **/
    iucast_ull          ,/** cast unsigned uint_32 to unsigned type LongLong. **/
    iadd_ull            ,/** add int_32 with unsigned type LongLong. **/
    iuadd_ull           ,/** add unsigned uint_32 with unsigned type LongLong. **/
    isub_ull            ,/** subtract int_32 with unsigned type LongLong. **/
    iusub_ull           ,/** subtract unsigned uint_32 with unsigned type LongLong. **/
    imul_ull            ,/** multiply int_32 with unsigned type LongLong. **/
    iumul_ull           ,/** multiply unsigned uint_32 with unsigned type LongLong. **/
    idiv_ull            ,/** divide int_32 with unsigned type LongLong. **/
    iudiv_ull           ,/** divide unsigned uint_32 with unsigned type LongLong. **/
    icmpl_ull           ,/** compare int_32 less than unsigned type LongLong. **/
    iucmpl_ull          ,/** compare unsigned uint_32 less than unsigned type LongLong. **/
    icmpg_ull           ,/** compare int_32 greater than unsigned type LongLong. **/
    iucmpg_ull          ,/** compare unsigned uint_32 greater than unsigned type LongLong. **/
    icmpe_ull           ,/** compare int_32 equal with unsigned type LongLong. **/
    iucmpe_ull          ,/** compare unsigned uint_32 equal with unsigned type LongLong. **/
    icmple_ull          ,/** compare int_32 less than or equal to unsigned type LongLong. **/
    iucmple_ull         ,/** compare unsigned uint_32 less than or equal to unsigned type LongLong. **/
    icmpge_ull          ,/** compare int_32 greater than or equal to unsigned type LongLong. **/
    iucmpge_ull         ,/** compare unsigned uint_32 greater than or equal to unsigned type LongLong. **/
    icmpne_ull          ,/** compare int_32 not equal with unsigned type LongLong. **/
    iucmpne_ull         ,/** compare unsigned uint_32 not equal with unsigned type LongLong. **/
    iand_b              ,/** bitwise and int_32 with type Byte. **/
    ior_b               ,/** bitwise or int_32 with type Byte. **/
    ixor_b              ,/** bitwise xor int_32 with type Byte. **/
    ishftr_b            ,/** shift right int_32 with type Byte. **/
    ishftl_b            ,/** shift left xor int_32 with type Byte. **/
    iand_s              ,/** bitwise and int_32 with type Short. **/
    ior_s               ,/** bitwise or int_32 with type Short. **/
    ixor_s              ,/** bitwise xor int_32 with type Short. **/
    ishftr_s            ,/** shift right int_32 with type Short. **/
    ishftl_s            ,/** shift left xor int_32 with type Short. **/
    iand_i              ,/** bitwise and int_32 with type Int. **/
    ior_i               ,/** bitwise or int_32 with type Int. **/
    ixor_i              ,/** bitwise xor int_32 with type Int. **/
    ishftr_i            ,/** shift right int_32 with type Int. **/
    ishftl_i            ,/** shift left xor int_32 with type Int. **/
    iand_l              ,/** bitwise and int_32 with type Long. **/
    ior_l               ,/** bitwise or int_32 with type Long. **/
    ixor_l              ,/** bitwise xor int_32 with type Long. **/
    ishftr_l            ,/** shift right int_32 with type Long. **/
    ishftl_l            ,/** shift left xor int_32 with type Long. **/
    iand_li             ,/** bitwise and int_32 with type LongInt. **/
    ior_li              ,/** bitwise or int_32 with type LongInt. **/
    ixor_li             ,/** bitwise xor int_32 with type LongInt. **/
    ishftr_li           ,/** shift right int_32 with type LongInt. **/
    ishftl_li           ,/** shift left xor int_32 with type LongInt. **/
    iand_ll             ,/** bitwise and int_32 with type LongLong. **/
    ior_ll              ,/** bitwise or int_32 with type LongLong. **/
    ixor_ll             ,/** bitwise xor int_32 with type LongLong. **/
    ishftr_ll           ,/** shift right int_32 with type LongLong. **/
    ishftl_ll           ,/** shift left xor int_32 with type LongLong. **/
    idup                ,/** duplicate a int_32 on the stack. **/
    idup2               ,/** duplicate a int_32 2 times on the stack. **/
    idup3               ,/** duplicate a int_32 3 times on the stack. **/
    idup4               ,/** duplicate a int_32 4 times on the stack. **/
    idup5               ,/** duplicate a int_32 5 times on the stack. **/
    iset                ,/** set a int_32 from stack into a field on base pointer. **/
    iget                ,/** get a int_32 from a field on base pointer to stack. **/
    ivset               ,/** set a int_32 from value into a field on base pointer. **/
    isget               ,/** get a int_32 from a field on base pointer to stack using address from stack. **/
    isset               ,/** set a int_32 from stack into a field on base pointer using address from stack. **/
    isetl               ,/** set a int_32 from local variable into a field on base pointer. **/
    iinc_1              ,/** increment int_32 by 1 on stack. **/
    iinc_2              ,/** increment int_32 by 2 on stack. **/
    istinc_1            ,/** increment int_32 by 1 on stack. **/
    istinc_2            ,/** increment int_32 by 2 on stack. **/
    ireturn             ,/** return a int_32 into the main stack. **/
    imainst             ,/** store a int_32 from main stack in a local variable.. **/
    imainst_0           ,/** store a int_32 from main stack in local variable 0. **/
    imainst_1           ,/** store a int_32 from main stack in local variable 1. **/
    imainst_2           ,/** store a int_32 from main stack in local variable 2. **/
    imainst_3           ,/** store a int_32 from main stack in local variable 3. **/
    iprint              ,/** print a int_32 from stack. **/
    iuprint             ,/** print a unsigned uint_32 from stack. **/
    lprintba            ,/** print a byte array. **/
    lconst              ,/** push a const int_64 into the stack. **/
    lconst_0            ,/** push a const int_64 into the stack (value = 0). **/
    lconst_1            ,/** push a const int_64 into the stack (value = 1). **/
    lconst_2            ,/** push a const int_64 into the stack (value = 2). **/
    lconst_3            ,/** push a const int_64 into the stack (value = 3). **/
    lconst_4            ,/** push a const int_64 into the stack (value = 4). **/
    lconst_5            ,/** push a const int_64 into the stack (value = 5). **/
    lconst_6            ,/** push a const int_64 into the stack (value = 6). **/
    lconst_9            ,/** push a const int_64 into the stack (value = 9). **/
    lconst_10           ,/** push a const int_64 into the stack (value = 10). **/
    lconst_11           ,/** push a const int_64 into the stack (value = 11). **/
    lconst_12           ,/** push a const int_64 into the stack (value = 12). **/
    lload               ,/** load a int_64 into the stack from local variable. **/
    lload_0             ,/** load a int_64 into the stack from local variable 0. **/
    lload_1             ,/** load a int_64 into the stack from local variable 1. **/
    lload_2             ,/** load a int_64 into the stack from local variable 2. **/
    lload_3             ,/** load a int_64 into the stack from local variable 3. **/
    lload_4             ,/** load a int_64 into the stack from local variable 4. **/
    lstore              ,/** store a int_64 from stack into local variable. **/
    lstore_0            ,/** store a int_64 from stack into local variable 0. **/
    lstore_1            ,/** store a int_64 from stack into local variable 1. **/
    lstore_2            ,/** store a int_64 from stack into local variable 2. **/
    lstore_3            ,/** store a int_64 from stack into local variable 3. **/
    lstore_4            ,/** store a int_64 from stack into local variable 4. **/
    lcast_b             ,/** cast int_64 to type Byte. **/
    lucast_b            ,/** cast unsigned uint_64 to type Byte. **/
    ladd_b              ,/** add int_64 with type Byte. **/
    luadd_b             ,/** add unsigned uint_64 with type Byte. **/
    lsub_b              ,/** subtract int_64 with type Byte. **/
    lusub_b             ,/** subtract unsigned uint_64 with type Byte. **/
    lmul_b              ,/** multiply int_64 with type Byte. **/
    lumul_b             ,/** multiply unsigned uint_64 with type Byte. **/
    ldiv_b              ,/** divide int_64 with type Byte. **/
    ludiv_b             ,/** divide unsigned uint_64 with type Byte. **/
    lcmpl_b             ,/** compare int_64 less than type Byte. **/
    lucmpl_b            ,/** compare unsigned uint_64 less than type Byte. **/
    lcmpg_b             ,/** compare int_64 greater than type Byte. **/
    lucmpg_b            ,/** compare unsigned uint_64 greater than type Byte. **/
    lcmpe_b             ,/** compare int_64 equal with type Byte. **/
    lucmpe_b            ,/** compare unsigned uint_64 equal with type Byte. **/
    lcmple_b            ,/** compare int_64 less than or equal to type Byte. **/
    lucmple_b           ,/** compare unsigned uint_64 less than or equal to type Byte. **/
    lcmpge_b            ,/** compare int_64 greater than or equal to type Byte. **/
    lucmpge_b           ,/** compare unsigned uint_64 greater than or equal to type Byte. **/
    lcmpne_b            ,/** compare int_64 not equal with type Byte. **/
    lucmpne_b           ,/** compare unsigned uint_64 not equal with type Byte. **/
    lcast_s             ,/** cast int_64 to type Short. **/
    lucast_s            ,/** cast unsigned uint_64 to type Short. **/
    ladd_s              ,/** add int_64 with type Short. **/
    luadd_s             ,/** add unsigned uint_64 with type Short. **/
    lsub_s              ,/** subtract int_64 with type Short. **/
    lusub_s             ,/** subtract unsigned uint_64 with type Short. **/
    lmul_s              ,/** multiply int_64 with type Short. **/
    lumul_s             ,/** multiply unsigned uint_64 with type Short. **/
    ldiv_s              ,/** divide int_64 with type Short. **/
    ludiv_s             ,/** divide unsigned uint_64 with type Short. **/
    lcmpl_s             ,/** compare int_64 less than type Short. **/
    lucmpl_s            ,/** compare unsigned uint_64 less than type Short. **/
    lcmpg_s             ,/** compare int_64 greater than type Short. **/
    lucmpg_s            ,/** compare unsigned uint_64 greater than type Short. **/
    lcmpe_s             ,/** compare int_64 equal with type Short. **/
    lucmpe_s            ,/** compare unsigned uint_64 equal with type Short. **/
    lcmple_s            ,/** compare int_64 less than or equal to type Short. **/
    lucmple_s           ,/** compare unsigned uint_64 less than or equal to type Short. **/
    lcmpge_s            ,/** compare int_64 greater than or equal to type Short. **/
    lucmpge_s           ,/** compare unsigned uint_64 greater than or equal to type Short. **/
    lcmpne_s            ,/** compare int_64 not equal with type Short. **/
    lucmpne_s           ,/** compare unsigned uint_64 not equal with type Short. **/
    lcast_i             ,/** cast int_64 to type Int. **/
    lucast_i            ,/** cast unsigned uint_64 to type Int. **/
    ladd_i              ,/** add int_64 with type Int. **/
    luadd_i             ,/** add unsigned uint_64 with type Int. **/
    lsub_i              ,/** subtract int_64 with type Int. **/
    lusub_i             ,/** subtract unsigned uint_64 with type Int. **/
    lmul_i              ,/** multiply int_64 with type Int. **/
    lumul_i             ,/** multiply unsigned uint_64 with type Int. **/
    ldiv_i              ,/** divide int_64 with type Int. **/
    ludiv_i             ,/** divide unsigned uint_64 with type Int. **/
    lcmpl_i             ,/** compare int_64 less than type Int. **/
    lucmpl_i            ,/** compare unsigned uint_64 less than type Int. **/
    lcmpg_i             ,/** compare int_64 greater than type Int. **/
    lucmpg_i            ,/** compare unsigned uint_64 greater than type Int. **/
    lcmpe_i             ,/** compare int_64 equal with type Int. **/
    lucmpe_i            ,/** compare unsigned uint_64 equal with type Int. **/
    lcmple_i            ,/** compare int_64 less than or equal to type Int. **/
    lucmple_i           ,/** compare unsigned uint_64 less than or equal to type Int. **/
    lcmpge_i            ,/** compare int_64 greater than or equal to type Int. **/
    lucmpge_i           ,/** compare unsigned uint_64 greater than or equal to type Int. **/
    lcmpne_i            ,/** compare int_64 not equal with type Int. **/
    lucmpne_i           ,/** compare unsigned uint_64 not equal with type Int. **/
    lcast_l             ,/** cast int_64 to type Long. **/
    lucast_l            ,/** cast unsigned uint_64 to type Long. **/
    ladd_l              ,/** add int_64 with type Long. **/
    luadd_l             ,/** add unsigned uint_64 with type Long. **/
    lsub_l              ,/** subtract int_64 with type Long. **/
    lusub_l             ,/** subtract unsigned uint_64 with type Long. **/
    lmul_l              ,/** multiply int_64 with type Long. **/
    lumul_l             ,/** multiply unsigned uint_64 with type Long. **/
    ldiv_l              ,/** divide int_64 with type Long. **/
    ludiv_l             ,/** divide unsigned uint_64 with type Long. **/
    lcmpl_l             ,/** compare int_64 less than type Long. **/
    lucmpl_l            ,/** compare unsigned uint_64 less than type Long. **/
    lcmpg_l             ,/** compare int_64 greater than type Long. **/
    lucmpg_l            ,/** compare unsigned uint_64 greater than type Long. **/
    lcmpe_l             ,/** compare int_64 equal with type Long. **/
    lucmpe_l            ,/** compare unsigned uint_64 equal with type Long. **/
    lcmple_l            ,/** compare int_64 less than or equal to type Long. **/
    lucmple_l           ,/** compare unsigned uint_64 less than or equal to type Long. **/
    lcmpge_l            ,/** compare int_64 greater than or equal to type Long. **/
    lucmpge_l           ,/** compare unsigned uint_64 greater than or equal to type Long. **/
    lcmpne_l            ,/** compare int_64 not equal with type Long. **/
    lucmpne_l           ,/** compare unsigned uint_64 not equal with type Long. **/
    lcast_li            ,/** cast int_64 to type LongInt. **/
    lucast_li           ,/** cast unsigned uint_64 to type LongInt. **/
    ladd_li             ,/** add int_64 with type LongInt. **/
    luadd_li            ,/** add unsigned uint_64 with type LongInt. **/
    lsub_li             ,/** subtract int_64 with type LongInt. **/
    lusub_li            ,/** subtract unsigned uint_64 with type LongInt. **/
    lmul_li             ,/** multiply int_64 with type LongInt. **/
    lumul_li            ,/** multiply unsigned uint_64 with type LongInt. **/
    ldiv_li             ,/** divide int_64 with type LongInt. **/
    ludiv_li            ,/** divide unsigned uint_64 with type LongInt. **/
    lcmpl_li            ,/** compare int_64 less than type LongInt. **/
    lucmpl_li           ,/** compare unsigned uint_64 less than type LongInt. **/
    lcmpg_li            ,/** compare int_64 greater than type LongInt. **/
    lucmpg_li           ,/** compare unsigned uint_64 greater than type LongInt. **/
    lcmpe_li            ,/** compare int_64 equal with type LongInt. **/
    lucmpe_li           ,/** compare unsigned uint_64 equal with type LongInt. **/
    lcmple_li           ,/** compare int_64 less than or equal to type LongInt. **/
    lucmple_li          ,/** compare unsigned uint_64 less than or equal to type LongInt. **/
    lcmpge_li           ,/** compare int_64 greater than or equal to type LongInt. **/
    lucmpge_li          ,/** compare unsigned uint_64 greater than or equal to type LongInt. **/
    lcmpne_li           ,/** compare int_64 not equal with type LongInt. **/
    lucmpne_li          ,/** compare unsigned uint_64 not equal with type LongInt. **/
    lcast_ll            ,/** cast int_64 to type LongLong. **/
    lucast_ll           ,/** cast unsigned uint_64 to type LongLong. **/
    ladd_ll             ,/** add int_64 with type LongLong. **/
    luadd_ll            ,/** add unsigned uint_64 with type LongLong. **/
    lsub_ll             ,/** subtract int_64 with type LongLong. **/
    lusub_ll            ,/** subtract unsigned uint_64 with type LongLong. **/
    lmul_ll             ,/** multiply int_64 with type LongLong. **/
    lumul_ll            ,/** multiply unsigned uint_64 with type LongLong. **/
    ldiv_ll             ,/** divide int_64 with type LongLong. **/
    ludiv_ll            ,/** divide unsigned uint_64 with type LongLong. **/
    lcmpl_ll            ,/** compare int_64 less than type LongLong. **/
    lucmpl_ll           ,/** compare unsigned uint_64 less than type LongLong. **/
    lcmpg_ll            ,/** compare int_64 greater than type LongLong. **/
    lucmpg_ll           ,/** compare unsigned uint_64 greater than type LongLong. **/
    lcmpe_ll            ,/** compare int_64 equal with type LongLong. **/
    lucmpe_ll           ,/** compare unsigned uint_64 equal with type LongLong. **/
    lcmple_ll           ,/** compare int_64 less than or equal to type LongLong. **/
    lucmple_ll          ,/** compare unsigned uint_64 less than or equal to type LongLong. **/
    lcmpge_ll           ,/** compare int_64 greater than or equal to type LongLong. **/
    lucmpge_ll          ,/** compare unsigned uint_64 greater than or equal to type LongLong. **/
    lcmpne_ll           ,/** compare int_64 not equal with type LongLong. **/
    lucmpne_ll          ,/** compare unsigned uint_64 not equal with type LongLong. **/
    lcast_f             ,/** cast int_64 to type Float. **/
    lucast_f            ,/** cast unsigned uint_64 to type Float. **/
    ladd_f              ,/** add int_64 with type Float. **/
    luadd_f             ,/** add unsigned uint_64 with type Float. **/
    lsub_f              ,/** subtract int_64 with type Float. **/
    lusub_f             ,/** subtract unsigned uint_64 with type Float. **/
    lmul_f              ,/** multiply int_64 with type Float. **/
    lumul_f             ,/** multiply unsigned uint_64 with type Float. **/
    ldiv_f              ,/** divide int_64 with type Float. **/
    ludiv_f             ,/** divide unsigned uint_64 with type Float. **/
    lcmpl_f             ,/** compare int_64 less than type Float. **/
    lucmpl_f            ,/** compare unsigned uint_64 less than type Float. **/
    lcmpg_f             ,/** compare int_64 greater than type Float. **/
    lucmpg_f            ,/** compare unsigned uint_64 greater than type Float. **/
    lcmpe_f             ,/** compare int_64 equal with type Float. **/
    lucmpe_f            ,/** compare unsigned uint_64 equal with type Float. **/
    lcmple_f            ,/** compare int_64 less than or equal to type Float. **/
    lucmple_f           ,/** compare unsigned uint_64 less than or equal to type Float. **/
    lcmpge_f            ,/** compare int_64 greater than or equal to type Float. **/
    lucmpge_f           ,/** compare unsigned uint_64 greater than or equal to type Float. **/
    lcmpne_f            ,/** compare int_64 not equal with type Float. **/
    lucmpne_f           ,/** compare unsigned uint_64 not equal with type Float. **/
    lcast_d             ,/** cast int_64 to type Double. **/
    lucast_d            ,/** cast unsigned uint_64 to type Double. **/
    ladd_d              ,/** add int_64 with type Double. **/
    luadd_d             ,/** add unsigned uint_64 with type Double. **/
    lsub_d              ,/** subtract int_64 with type Double. **/
    lusub_d             ,/** subtract unsigned uint_64 with type Double. **/
    lmul_d              ,/** multiply int_64 with type Double. **/
    lumul_d             ,/** multiply unsigned uint_64 with type Double. **/
    ldiv_d              ,/** divide int_64 with type Double. **/
    ludiv_d             ,/** divide unsigned uint_64 with type Double. **/
    lcmpl_d             ,/** compare int_64 less than type Double. **/
    lucmpl_d            ,/** compare unsigned uint_64 less than type Double. **/
    lcmpg_d             ,/** compare int_64 greater than type Double. **/
    lucmpg_d            ,/** compare unsigned uint_64 greater than type Double. **/
    lcmpe_d             ,/** compare int_64 equal with type Double. **/
    lucmpe_d            ,/** compare unsigned uint_64 equal with type Double. **/
    lcmple_d            ,/** compare int_64 less than or equal to type Double. **/
    lucmple_d           ,/** compare unsigned uint_64 less than or equal to type Double. **/
    lcmpge_d            ,/** compare int_64 greater than or equal to type Double. **/
    lucmpge_d           ,/** compare unsigned uint_64 greater than or equal to type Double. **/
    lcmpne_d            ,/** compare int_64 not equal with type Double. **/
    lucmpne_d           ,/** compare unsigned uint_64 not equal with type Double. **/
    lcast_df            ,/** cast int_64 to type DoubleFloat. **/
    lucast_df           ,/** cast unsigned uint_64 to type DoubleFloat. **/
    ladd_df             ,/** add int_64 with type DoubleFloat. **/
    luadd_df            ,/** add unsigned uint_64 with type DoubleFloat. **/
    lsub_df             ,/** subtract int_64 with type DoubleFloat. **/
    lusub_df            ,/** subtract unsigned uint_64 with type DoubleFloat. **/
    lmul_df             ,/** multiply int_64 with type DoubleFloat. **/
    lumul_df            ,/** multiply unsigned uint_64 with type DoubleFloat. **/
    ldiv_df             ,/** divide int_64 with type DoubleFloat. **/
    ludiv_df            ,/** divide unsigned uint_64 with type DoubleFloat. **/
    lcmpl_df            ,/** compare int_64 less than type DoubleFloat. **/
    lucmpl_df           ,/** compare unsigned uint_64 less than type DoubleFloat. **/
    lcmpg_df            ,/** compare int_64 greater than type DoubleFloat. **/
    lucmpg_df           ,/** compare unsigned uint_64 greater than type DoubleFloat. **/
    lcmpe_df            ,/** compare int_64 equal with type DoubleFloat. **/
    lucmpe_df           ,/** compare unsigned uint_64 equal with type DoubleFloat. **/
    lcmple_df           ,/** compare int_64 less than or equal to type DoubleFloat. **/
    lucmple_df          ,/** compare unsigned uint_64 less than or equal to type DoubleFloat. **/
    lcmpge_df           ,/** compare int_64 greater than or equal to type DoubleFloat. **/
    lucmpge_df          ,/** compare unsigned uint_64 greater than or equal to type DoubleFloat. **/
    lcmpne_df           ,/** compare int_64 not equal with type DoubleFloat. **/
    lucmpne_df          ,/** compare unsigned uint_64 not equal with type DoubleFloat. **/
    lcast_dd            ,/** cast int_64 to type DoubleDouble. **/
    lucast_dd           ,/** cast unsigned uint_64 to type DoubleDouble. **/
    ladd_dd             ,/** add int_64 with type DoubleDouble. **/
    luadd_dd            ,/** add unsigned uint_64 with type DoubleDouble. **/
    lsub_dd             ,/** subtract int_64 with type DoubleDouble. **/
    lusub_dd            ,/** subtract unsigned uint_64 with type DoubleDouble. **/
    lmul_dd             ,/** multiply int_64 with type DoubleDouble. **/
    lumul_dd            ,/** multiply unsigned uint_64 with type DoubleDouble. **/
    ldiv_dd             ,/** divide int_64 with type DoubleDouble. **/
    ludiv_dd            ,/** divide unsigned uint_64 with type DoubleDouble. **/
    lcmpl_dd            ,/** compare int_64 less than type DoubleDouble. **/
    lucmpl_dd           ,/** compare unsigned uint_64 less than type DoubleDouble. **/
    lcmpg_dd            ,/** compare int_64 greater than type DoubleDouble. **/
    lucmpg_dd           ,/** compare unsigned uint_64 greater than type DoubleDouble. **/
    lcmpe_dd            ,/** compare int_64 equal with type DoubleDouble. **/
    lucmpe_dd           ,/** compare unsigned uint_64 equal with type DoubleDouble. **/
    lcmple_dd           ,/** compare int_64 less than or equal to type DoubleDouble. **/
    lucmple_dd          ,/** compare unsigned uint_64 less than or equal to type DoubleDouble. **/
    lcmpge_dd           ,/** compare int_64 greater than or equal to type DoubleDouble. **/
    lucmpge_dd          ,/** compare unsigned uint_64 greater than or equal to type DoubleDouble. **/
    lcmpne_dd           ,/** compare int_64 not equal with type DoubleDouble. **/
    lucmpne_dd          ,/** compare unsigned uint_64 not equal with type DoubleDouble. **/
    lmod_b              ,/** modulo int_64 with type Byte. **/
    lcast_ub            ,/** cast int_64 to unsigned type Byte. **/
    lucast_ub           ,/** cast unsigned uint_64 to unsigned type Byte. **/
    ladd_ub             ,/** add int_64 with unsigned type Byte. **/
    luadd_ub            ,/** add unsigned uint_64 with unsigned type Byte. **/
    lsub_ub             ,/** subtract int_64 with unsigned type Byte. **/
    lusub_ub            ,/** subtract unsigned uint_64 with unsigned type Byte. **/
    lmul_ub             ,/** multiply int_64 with unsigned type Byte. **/
    lumul_ub            ,/** multiply unsigned uint_64 with unsigned type Byte. **/
    ldiv_ub             ,/** divide int_64 with unsigned type Byte. **/
    ludiv_ub            ,/** divide unsigned uint_64 with unsigned type Byte. **/
    lcmpl_ub            ,/** compare int_64 less than unsigned type Byte. **/
    lucmpl_ub           ,/** compare unsigned uint_64 less than unsigned type Byte. **/
    lcmpg_ub            ,/** compare int_64 greater than unsigned type Byte. **/
    lucmpg_ub           ,/** compare unsigned uint_64 greater than unsigned type Byte. **/
    lcmpe_ub            ,/** compare int_64 equal with unsigned type Byte. **/
    lucmpe_ub           ,/** compare unsigned uint_64 equal with unsigned type Byte. **/
    lcmple_ub           ,/** compare int_64 less than or equal to unsigned type Byte. **/
    lucmple_ub          ,/** compare unsigned uint_64 less than or equal to unsigned type Byte. **/
    lcmpge_ub           ,/** compare int_64 greater than or equal to unsigned type Byte. **/
    lucmpge_ub          ,/** compare unsigned uint_64 greater than or equal to unsigned type Byte. **/
    lcmpne_ub           ,/** compare int_64 not equal with unsigned type Byte. **/
    lucmpne_ub          ,/** compare unsigned uint_64 not equal with unsigned type Byte. **/
    lmod_s              ,/** modulo int_64 with type Short. **/
    lcast_us            ,/** cast int_64 to unsigned type Short. **/
    lucast_us           ,/** cast unsigned uint_64 to unsigned type Short. **/
    ladd_us             ,/** add int_64 with unsigned type Short. **/
    luadd_us            ,/** add unsigned uint_64 with unsigned type Short. **/
    lsub_us             ,/** subtract int_64 with unsigned type Short. **/
    lusub_us            ,/** subtract unsigned uint_64 with unsigned type Short. **/
    lmul_us             ,/** multiply int_64 with unsigned type Short. **/
    lumul_us            ,/** multiply unsigned uint_64 with unsigned type Short. **/
    ldiv_us             ,/** divide int_64 with unsigned type Short. **/
    ludiv_us            ,/** divide unsigned uint_64 with unsigned type Short. **/
    lcmpl_us            ,/** compare int_64 less than unsigned type Short. **/
    lucmpl_us           ,/** compare unsigned uint_64 less than unsigned type Short. **/
    lcmpg_us            ,/** compare int_64 greater than unsigned type Short. **/
    lucmpg_us           ,/** compare unsigned uint_64 greater than unsigned type Short. **/
    lcmpe_us            ,/** compare int_64 equal with unsigned type Short. **/
    lucmpe_us           ,/** compare unsigned uint_64 equal with unsigned type Short. **/
    lcmple_us           ,/** compare int_64 less than or equal to unsigned type Short. **/
    lucmple_us          ,/** compare unsigned uint_64 less than or equal to unsigned type Short. **/
    lcmpge_us           ,/** compare int_64 greater than or equal to unsigned type Short. **/
    lucmpge_us          ,/** compare unsigned uint_64 greater than or equal to unsigned type Short. **/
    lcmpne_us           ,/** compare int_64 not equal with unsigned type Short. **/
    lucmpne_us          ,/** compare unsigned uint_64 not equal with unsigned type Short. **/
    lmod_i              ,/** modulo int_64 with type Int. **/
    lcast_ui            ,/** cast int_64 to unsigned type Int. **/
    lucast_ui           ,/** cast unsigned uint_64 to unsigned type Int. **/
    ladd_ui             ,/** add int_64 with unsigned type Int. **/
    luadd_ui            ,/** add unsigned uint_64 with unsigned type Int. **/
    lsub_ui             ,/** subtract int_64 with unsigned type Int. **/
    lusub_ui            ,/** subtract unsigned uint_64 with unsigned type Int. **/
    lmul_ui             ,/** multiply int_64 with unsigned type Int. **/
    lumul_ui            ,/** multiply unsigned uint_64 with unsigned type Int. **/
    ldiv_ui             ,/** divide int_64 with unsigned type Int. **/
    ludiv_ui            ,/** divide unsigned uint_64 with unsigned type Int. **/
    lcmpl_ui            ,/** compare int_64 less than unsigned type Int. **/
    lucmpl_ui           ,/** compare unsigned uint_64 less than unsigned type Int. **/
    lcmpg_ui            ,/** compare int_64 greater than unsigned type Int. **/
    lucmpg_ui           ,/** compare unsigned uint_64 greater than unsigned type Int. **/
    lcmpe_ui            ,/** compare int_64 equal with unsigned type Int. **/
    lucmpe_ui           ,/** compare unsigned uint_64 equal with unsigned type Int. **/
    lcmple_ui           ,/** compare int_64 less than or equal to unsigned type Int. **/
    lucmple_ui          ,/** compare unsigned uint_64 less than or equal to unsigned type Int. **/
    lcmpge_ui           ,/** compare int_64 greater than or equal to unsigned type Int. **/
    lucmpge_ui          ,/** compare unsigned uint_64 greater than or equal to unsigned type Int. **/
    lcmpne_ui           ,/** compare int_64 not equal with unsigned type Int. **/
    lucmpne_ui          ,/** compare unsigned uint_64 not equal with unsigned type Int. **/
    lmod_l              ,/** modulo int_64 with type Long. **/
    lcast_ul            ,/** cast int_64 to unsigned type Long. **/
    lucast_ul           ,/** cast unsigned uint_64 to unsigned type Long. **/
    ladd_ul             ,/** add int_64 with unsigned type Long. **/
    luadd_ul            ,/** add unsigned uint_64 with unsigned type Long. **/
    lsub_ul             ,/** subtract int_64 with unsigned type Long. **/
    lusub_ul            ,/** subtract unsigned uint_64 with unsigned type Long. **/
    lmul_ul             ,/** multiply int_64 with unsigned type Long. **/
    lumul_ul            ,/** multiply unsigned uint_64 with unsigned type Long. **/
    ldiv_ul             ,/** divide int_64 with unsigned type Long. **/
    ludiv_ul            ,/** divide unsigned uint_64 with unsigned type Long. **/
    lcmpl_ul            ,/** compare int_64 less than unsigned type Long. **/
    lucmpl_ul           ,/** compare unsigned uint_64 less than unsigned type Long. **/
    lcmpg_ul            ,/** compare int_64 greater than unsigned type Long. **/
    lucmpg_ul           ,/** compare unsigned uint_64 greater than unsigned type Long. **/
    lcmpe_ul            ,/** compare int_64 equal with unsigned type Long. **/
    lucmpe_ul           ,/** compare unsigned uint_64 equal with unsigned type Long. **/
    lcmple_ul           ,/** compare int_64 less than or equal to unsigned type Long. **/
    lucmple_ul          ,/** compare unsigned uint_64 less than or equal to unsigned type Long. **/
    lcmpge_ul           ,/** compare int_64 greater than or equal to unsigned type Long. **/
    lucmpge_ul          ,/** compare unsigned uint_64 greater than or equal to unsigned type Long. **/
    lcmpne_ul           ,/** compare int_64 not equal with unsigned type Long. **/
    lucmpne_ul          ,/** compare unsigned uint_64 not equal with unsigned type Long. **/
    lmod_li             ,/** modulo int_64 with type LongInt. **/
    lcast_uli           ,/** cast int_64 to unsigned type LongInt. **/
    lucast_uli          ,/** cast unsigned uint_64 to unsigned type LongInt. **/
    ladd_uli            ,/** add int_64 with unsigned type LongInt. **/
    luadd_uli           ,/** add unsigned uint_64 with unsigned type LongInt. **/
    lsub_uli            ,/** subtract int_64 with unsigned type LongInt. **/
    lusub_uli           ,/** subtract unsigned uint_64 with unsigned type LongInt. **/
    lmul_uli            ,/** multiply int_64 with unsigned type LongInt. **/
    lumul_uli           ,/** multiply unsigned uint_64 with unsigned type LongInt. **/
    ldiv_uli            ,/** divide int_64 with unsigned type LongInt. **/
    ludiv_uli           ,/** divide unsigned uint_64 with unsigned type LongInt. **/
    lcmpl_uli           ,/** compare int_64 less than unsigned type LongInt. **/
    lucmpl_uli          ,/** compare unsigned uint_64 less than unsigned type LongInt. **/
    lcmpg_uli           ,/** compare int_64 greater than unsigned type LongInt. **/
    lucmpg_uli          ,/** compare unsigned uint_64 greater than unsigned type LongInt. **/
    lcmpe_uli           ,/** compare int_64 equal with unsigned type LongInt. **/
    lucmpe_uli          ,/** compare unsigned uint_64 equal with unsigned type LongInt. **/
    lcmple_uli          ,/** compare int_64 less than or equal to unsigned type LongInt. **/
    lucmple_uli         ,/** compare unsigned uint_64 less than or equal to unsigned type LongInt. **/
    lcmpge_uli          ,/** compare int_64 greater than or equal to unsigned type LongInt. **/
    lucmpge_uli         ,/** compare unsigned uint_64 greater than or equal to unsigned type LongInt. **/
    lcmpne_uli          ,/** compare int_64 not equal with unsigned type LongInt. **/
    lucmpne_uli         ,/** compare unsigned uint_64 not equal with unsigned type LongInt. **/
    lmod_ll             ,/** modulo int_64 with type LongLong. **/
    lcast_ull           ,/** cast int_64 to unsigned type LongLong. **/
    lucast_ull          ,/** cast unsigned uint_64 to unsigned type LongLong. **/
    ladd_ull            ,/** add int_64 with unsigned type LongLong. **/
    luadd_ull           ,/** add unsigned uint_64 with unsigned type LongLong. **/
    lsub_ull            ,/** subtract int_64 with unsigned type LongLong. **/
    lusub_ull           ,/** subtract unsigned uint_64 with unsigned type LongLong. **/
    lmul_ull            ,/** multiply int_64 with unsigned type LongLong. **/
    lumul_ull           ,/** multiply unsigned uint_64 with unsigned type LongLong. **/
    ldiv_ull            ,/** divide int_64 with unsigned type LongLong. **/
    ludiv_ull           ,/** divide unsigned uint_64 with unsigned type LongLong. **/
    lcmpl_ull           ,/** compare int_64 less than unsigned type LongLong. **/
    lucmpl_ull          ,/** compare unsigned uint_64 less than unsigned type LongLong. **/
    lcmpg_ull           ,/** compare int_64 greater than unsigned type LongLong. **/
    lucmpg_ull          ,/** compare unsigned uint_64 greater than unsigned type LongLong. **/
    lcmpe_ull           ,/** compare int_64 equal with unsigned type LongLong. **/
    lucmpe_ull          ,/** compare unsigned uint_64 equal with unsigned type LongLong. **/
    lcmple_ull          ,/** compare int_64 less than or equal to unsigned type LongLong. **/
    lucmple_ull         ,/** compare unsigned uint_64 less than or equal to unsigned type LongLong. **/
    lcmpge_ull          ,/** compare int_64 greater than or equal to unsigned type LongLong. **/
    lucmpge_ull         ,/** compare unsigned uint_64 greater than or equal to unsigned type LongLong. **/
    lcmpne_ull          ,/** compare int_64 not equal with unsigned type LongLong. **/
    lucmpne_ull         ,/** compare unsigned uint_64 not equal with unsigned type LongLong. **/
    land_b              ,/** bitwise and int_64 with type Byte. **/
    lor_b               ,/** bitwise or int_64 with type Byte. **/
    lxor_b              ,/** bitwise xor int_64 with type Byte. **/
    lshftr_b            ,/** shift right int_64 with type Byte. **/
    lshftl_b            ,/** shift left xor int_64 with type Byte. **/
    land_s              ,/** bitwise and int_64 with type Short. **/
    lor_s               ,/** bitwise or int_64 with type Short. **/
    lxor_s              ,/** bitwise xor int_64 with type Short. **/
    lshftr_s            ,/** shift right int_64 with type Short. **/
    lshftl_s            ,/** shift left xor int_64 with type Short. **/
    land_i              ,/** bitwise and int_64 with type Int. **/
    lor_i               ,/** bitwise or int_64 with type Int. **/
    lxor_i              ,/** bitwise xor int_64 with type Int. **/
    lshftr_i            ,/** shift right int_64 with type Int. **/
    lshftl_i            ,/** shift left xor int_64 with type Int. **/
    land_l              ,/** bitwise and int_64 with type Long. **/
    lor_l               ,/** bitwise or int_64 with type Long. **/
    lxor_l              ,/** bitwise xor int_64 with type Long. **/
    lshftr_l            ,/** shift right int_64 with type Long. **/
    lshftl_l            ,/** shift left xor int_64 with type Long. **/
    land_li             ,/** bitwise and int_64 with type LongInt. **/
    lor_li              ,/** bitwise or int_64 with type LongInt. **/
    lxor_li             ,/** bitwise xor int_64 with type LongInt. **/
    lshftr_li           ,/** shift right int_64 with type LongInt. **/
    lshftl_li           ,/** shift left xor int_64 with type LongInt. **/
    land_ll             ,/** bitwise and int_64 with type LongLong. **/
    lor_ll              ,/** bitwise or int_64 with type LongLong. **/
    lxor_ll             ,/** bitwise xor int_64 with type LongLong. **/
    lshftr_ll           ,/** shift right int_64 with type LongLong. **/
    lshftl_ll           ,/** shift left xor int_64 with type LongLong. **/
    ldup                ,/** duplicate a int_64 on the stack. **/
    ldup2               ,/** duplicate a int_64 2 times on the stack. **/
    ldup3               ,/** duplicate a int_64 3 times on the stack. **/
    ldup4               ,/** duplicate a int_64 4 times on the stack. **/
    ldup5               ,/** duplicate a int_64 5 times on the stack. **/
    lset                ,/** set a int_64 from stack into a field on base pointer. **/
    lget                ,/** get a int_64 from a field on base pointer to stack. **/
    lvset               ,/** set a int_64 from value into a field on base pointer. **/
    lsget               ,/** get a int_64 from a field on base pointer to stack using address from stack. **/
    lsset               ,/** set a int_64 from stack into a field on base pointer using address from stack. **/
    lsetl               ,/** set a int_64 from local variable into a field on base pointer. **/
    linc_1              ,/** increment int_64 by 1 on stack. **/
    linc_2              ,/** increment int_64 by 2 on stack. **/
    lstinc_1            ,/** increment int_64 by 1 on stack. **/
    lstinc_2            ,/** increment int_64 by 2 on stack. **/
    lreturn             ,/** return a int_64 into the main stack. **/
    lmainst             ,/** store a int_64 from main stack in a local variable.. **/
    lmainst_0           ,/** store a int_64 from main stack in local variable 0. **/
    lmainst_1           ,/** store a int_64 from main stack in local variable 1. **/
    lmainst_2           ,/** store a int_64 from main stack in local variable 2. **/
    lmainst_3           ,/** store a int_64 from main stack in local variable 3. **/
    lprint              ,/** print a int_64 from stack. **/
    luprint             ,/** print a unsigned uint_64 from stack. **/
    liprintba           ,/** print a byte array. **/
    liconst             ,/** push a const int_128 into the stack. **/
    liconst_0           ,/** push a const int_128 into the stack (value = 0). **/
    liconst_1           ,/** push a const int_128 into the stack (value = 1). **/
    liconst_2           ,/** push a const int_128 into the stack (value = 2). **/
    liconst_3           ,/** push a const int_128 into the stack (value = 3). **/
    liconst_4           ,/** push a const int_128 into the stack (value = 4). **/
    liconst_5           ,/** push a const int_128 into the stack (value = 5). **/
    liconst_6           ,/** push a const int_128 into the stack (value = 6). **/
    liconst_9           ,/** push a const int_128 into the stack (value = 9). **/
    liconst_10          ,/** push a const int_128 into the stack (value = 10). **/
    liconst_11          ,/** push a const int_128 into the stack (value = 11). **/
    liconst_12          ,/** push a const int_128 into the stack (value = 12). **/
    liload              ,/** load a int_128 into the stack from local variable. **/
    liload_0            ,/** load a int_128 into the stack from local variable 0. **/
    liload_1            ,/** load a int_128 into the stack from local variable 1. **/
    liload_2            ,/** load a int_128 into the stack from local variable 2. **/
    liload_3            ,/** load a int_128 into the stack from local variable 3. **/
    liload_4            ,/** load a int_128 into the stack from local variable 4. **/
    listore             ,/** store a int_128 from stack into local variable. **/
    listore_0           ,/** store a int_128 from stack into local variable 0. **/
    listore_1           ,/** store a int_128 from stack into local variable 1. **/
    listore_2           ,/** store a int_128 from stack into local variable 2. **/
    listore_3           ,/** store a int_128 from stack into local variable 3. **/
    listore_4           ,/** store a int_128 from stack into local variable 4. **/
    licast_b            ,/** cast int_128 to type Byte. **/
    liucast_b           ,/** cast unsigned uint_128 to type Byte. **/
    liadd_b             ,/** add int_128 with type Byte. **/
    liuadd_b            ,/** add unsigned uint_128 with type Byte. **/
    lisub_b             ,/** subtract int_128 with type Byte. **/
    liusub_b            ,/** subtract unsigned uint_128 with type Byte. **/
    limul_b             ,/** multiply int_128 with type Byte. **/
    liumul_b            ,/** multiply unsigned uint_128 with type Byte. **/
    lidiv_b             ,/** divide int_128 with type Byte. **/
    liudiv_b            ,/** divide unsigned uint_128 with type Byte. **/
    licmpl_b            ,/** compare int_128 less than type Byte. **/
    liucmpl_b           ,/** compare unsigned uint_128 less than type Byte. **/
    licmpg_b            ,/** compare int_128 greater than type Byte. **/
    liucmpg_b           ,/** compare unsigned uint_128 greater than type Byte. **/
    licmpe_b            ,/** compare int_128 equal with type Byte. **/
    liucmpe_b           ,/** compare unsigned uint_128 equal with type Byte. **/
    licmple_b           ,/** compare int_128 less than or equal to type Byte. **/
    liucmple_b          ,/** compare unsigned uint_128 less than or equal to type Byte. **/
    licmpge_b           ,/** compare int_128 greater than or equal to type Byte. **/
    liucmpge_b          ,/** compare unsigned uint_128 greater than or equal to type Byte. **/
    licmpne_b           ,/** compare int_128 not equal with type Byte. **/
    liucmpne_b          ,/** compare unsigned uint_128 not equal with type Byte. **/
    licast_s            ,/** cast int_128 to type Short. **/
    liucast_s           ,/** cast unsigned uint_128 to type Short. **/
    liadd_s             ,/** add int_128 with type Short. **/
    liuadd_s            ,/** add unsigned uint_128 with type Short. **/
    lisub_s             ,/** subtract int_128 with type Short. **/
    liusub_s            ,/** subtract unsigned uint_128 with type Short. **/
    limul_s             ,/** multiply int_128 with type Short. **/
    liumul_s            ,/** multiply unsigned uint_128 with type Short. **/
    lidiv_s             ,/** divide int_128 with type Short. **/
    liudiv_s            ,/** divide unsigned uint_128 with type Short. **/
    licmpl_s            ,/** compare int_128 less than type Short. **/
    liucmpl_s           ,/** compare unsigned uint_128 less than type Short. **/
    licmpg_s            ,/** compare int_128 greater than type Short. **/
    liucmpg_s           ,/** compare unsigned uint_128 greater than type Short. **/
    licmpe_s            ,/** compare int_128 equal with type Short. **/
    liucmpe_s           ,/** compare unsigned uint_128 equal with type Short. **/
    licmple_s           ,/** compare int_128 less than or equal to type Short. **/
    liucmple_s          ,/** compare unsigned uint_128 less than or equal to type Short. **/
    licmpge_s           ,/** compare int_128 greater than or equal to type Short. **/
    liucmpge_s          ,/** compare unsigned uint_128 greater than or equal to type Short. **/
    licmpne_s           ,/** compare int_128 not equal with type Short. **/
    liucmpne_s          ,/** compare unsigned uint_128 not equal with type Short. **/
    licast_i            ,/** cast int_128 to type Int. **/
    liucast_i           ,/** cast unsigned uint_128 to type Int. **/
    liadd_i             ,/** add int_128 with type Int. **/
    liuadd_i            ,/** add unsigned uint_128 with type Int. **/
    lisub_i             ,/** subtract int_128 with type Int. **/
    liusub_i            ,/** subtract unsigned uint_128 with type Int. **/
    limul_i             ,/** multiply int_128 with type Int. **/
    liumul_i            ,/** multiply unsigned uint_128 with type Int. **/
    lidiv_i             ,/** divide int_128 with type Int. **/
    liudiv_i            ,/** divide unsigned uint_128 with type Int. **/
    licmpl_i            ,/** compare int_128 less than type Int. **/
    liucmpl_i           ,/** compare unsigned uint_128 less than type Int. **/
    licmpg_i            ,/** compare int_128 greater than type Int. **/
    liucmpg_i           ,/** compare unsigned uint_128 greater than type Int. **/
    licmpe_i            ,/** compare int_128 equal with type Int. **/
    liucmpe_i           ,/** compare unsigned uint_128 equal with type Int. **/
    licmple_i           ,/** compare int_128 less than or equal to type Int. **/
    liucmple_i          ,/** compare unsigned uint_128 less than or equal to type Int. **/
    licmpge_i           ,/** compare int_128 greater than or equal to type Int. **/
    liucmpge_i          ,/** compare unsigned uint_128 greater than or equal to type Int. **/
    licmpne_i           ,/** compare int_128 not equal with type Int. **/
    liucmpne_i          ,/** compare unsigned uint_128 not equal with type Int. **/
    licast_l            ,/** cast int_128 to type Long. **/
    liucast_l           ,/** cast unsigned uint_128 to type Long. **/
    liadd_l             ,/** add int_128 with type Long. **/
    liuadd_l            ,/** add unsigned uint_128 with type Long. **/
    lisub_l             ,/** subtract int_128 with type Long. **/
    liusub_l            ,/** subtract unsigned uint_128 with type Long. **/
    limul_l             ,/** multiply int_128 with type Long. **/
    liumul_l            ,/** multiply unsigned uint_128 with type Long. **/
    lidiv_l             ,/** divide int_128 with type Long. **/
    liudiv_l            ,/** divide unsigned uint_128 with type Long. **/
    licmpl_l            ,/** compare int_128 less than type Long. **/
    liucmpl_l           ,/** compare unsigned uint_128 less than type Long. **/
    licmpg_l            ,/** compare int_128 greater than type Long. **/
    liucmpg_l           ,/** compare unsigned uint_128 greater than type Long. **/
    licmpe_l            ,/** compare int_128 equal with type Long. **/
    liucmpe_l           ,/** compare unsigned uint_128 equal with type Long. **/
    licmple_l           ,/** compare int_128 less than or equal to type Long. **/
    liucmple_l          ,/** compare unsigned uint_128 less than or equal to type Long. **/
    licmpge_l           ,/** compare int_128 greater than or equal to type Long. **/
    liucmpge_l          ,/** compare unsigned uint_128 greater than or equal to type Long. **/
    licmpne_l           ,/** compare int_128 not equal with type Long. **/
    liucmpne_l          ,/** compare unsigned uint_128 not equal with type Long. **/
    licast_li           ,/** cast int_128 to type LongInt. **/
    liucast_li          ,/** cast unsigned uint_128 to type LongInt. **/
    liadd_li            ,/** add int_128 with type LongInt. **/
    liuadd_li           ,/** add unsigned uint_128 with type LongInt. **/
    lisub_li            ,/** subtract int_128 with type LongInt. **/
    liusub_li           ,/** subtract unsigned uint_128 with type LongInt. **/
    limul_li            ,/** multiply int_128 with type LongInt. **/
    liumul_li           ,/** multiply unsigned uint_128 with type LongInt. **/
    lidiv_li            ,/** divide int_128 with type LongInt. **/
    liudiv_li           ,/** divide unsigned uint_128 with type LongInt. **/
    licmpl_li           ,/** compare int_128 less than type LongInt. **/
    liucmpl_li          ,/** compare unsigned uint_128 less than type LongInt. **/
    licmpg_li           ,/** compare int_128 greater than type LongInt. **/
    liucmpg_li          ,/** compare unsigned uint_128 greater than type LongInt. **/
    licmpe_li           ,/** compare int_128 equal with type LongInt. **/
    liucmpe_li          ,/** compare unsigned uint_128 equal with type LongInt. **/
    licmple_li          ,/** compare int_128 less than or equal to type LongInt. **/
    liucmple_li         ,/** compare unsigned uint_128 less than or equal to type LongInt. **/
    licmpge_li          ,/** compare int_128 greater than or equal to type LongInt. **/
    liucmpge_li         ,/** compare unsigned uint_128 greater than or equal to type LongInt. **/
    licmpne_li          ,/** compare int_128 not equal with type LongInt. **/
    liucmpne_li         ,/** compare unsigned uint_128 not equal with type LongInt. **/
    licast_ll           ,/** cast int_128 to type LongLong. **/
    liucast_ll          ,/** cast unsigned uint_128 to type LongLong. **/
    liadd_ll            ,/** add int_128 with type LongLong. **/
    liuadd_ll           ,/** add unsigned uint_128 with type LongLong. **/
    lisub_ll            ,/** subtract int_128 with type LongLong. **/
    liusub_ll           ,/** subtract unsigned uint_128 with type LongLong. **/
    limul_ll            ,/** multiply int_128 with type LongLong. **/
    liumul_ll           ,/** multiply unsigned uint_128 with type LongLong. **/
    lidiv_ll            ,/** divide int_128 with type LongLong. **/
    liudiv_ll           ,/** divide unsigned uint_128 with type LongLong. **/
    licmpl_ll           ,/** compare int_128 less than type LongLong. **/
    liucmpl_ll          ,/** compare unsigned uint_128 less than type LongLong. **/
    licmpg_ll           ,/** compare int_128 greater than type LongLong. **/
    liucmpg_ll          ,/** compare unsigned uint_128 greater than type LongLong. **/
    licmpe_ll           ,/** compare int_128 equal with type LongLong. **/
    liucmpe_ll          ,/** compare unsigned uint_128 equal with type LongLong. **/
    licmple_ll          ,/** compare int_128 less than or equal to type LongLong. **/
    liucmple_ll         ,/** compare unsigned uint_128 less than or equal to type LongLong. **/
    licmpge_ll          ,/** compare int_128 greater than or equal to type LongLong. **/
    liucmpge_ll         ,/** compare unsigned uint_128 greater than or equal to type LongLong. **/
    licmpne_ll          ,/** compare int_128 not equal with type LongLong. **/
    liucmpne_ll         ,/** compare unsigned uint_128 not equal with type LongLong. **/
    licast_f            ,/** cast int_128 to type Float. **/
    liucast_f           ,/** cast unsigned uint_128 to type Float. **/
    liadd_f             ,/** add int_128 with type Float. **/
    liuadd_f            ,/** add unsigned uint_128 with type Float. **/
    lisub_f             ,/** subtract int_128 with type Float. **/
    liusub_f            ,/** subtract unsigned uint_128 with type Float. **/
    limul_f             ,/** multiply int_128 with type Float. **/
    liumul_f            ,/** multiply unsigned uint_128 with type Float. **/
    lidiv_f             ,/** divide int_128 with type Float. **/
    liudiv_f            ,/** divide unsigned uint_128 with type Float. **/
    licmpl_f            ,/** compare int_128 less than type Float. **/
    liucmpl_f           ,/** compare unsigned uint_128 less than type Float. **/
    licmpg_f            ,/** compare int_128 greater than type Float. **/
    liucmpg_f           ,/** compare unsigned uint_128 greater than type Float. **/
    licmpe_f            ,/** compare int_128 equal with type Float. **/
    liucmpe_f           ,/** compare unsigned uint_128 equal with type Float. **/
    licmple_f           ,/** compare int_128 less than or equal to type Float. **/
    liucmple_f          ,/** compare unsigned uint_128 less than or equal to type Float. **/
    licmpge_f           ,/** compare int_128 greater than or equal to type Float. **/
    liucmpge_f          ,/** compare unsigned uint_128 greater than or equal to type Float. **/
    licmpne_f           ,/** compare int_128 not equal with type Float. **/
    liucmpne_f          ,/** compare unsigned uint_128 not equal with type Float. **/
    licast_d            ,/** cast int_128 to type Double. **/
    liucast_d           ,/** cast unsigned uint_128 to type Double. **/
    liadd_d             ,/** add int_128 with type Double. **/
    liuadd_d            ,/** add unsigned uint_128 with type Double. **/
    lisub_d             ,/** subtract int_128 with type Double. **/
    liusub_d            ,/** subtract unsigned uint_128 with type Double. **/
    limul_d             ,/** multiply int_128 with type Double. **/
    liumul_d            ,/** multiply unsigned uint_128 with type Double. **/
    lidiv_d             ,/** divide int_128 with type Double. **/
    liudiv_d            ,/** divide unsigned uint_128 with type Double. **/
    licmpl_d            ,/** compare int_128 less than type Double. **/
    liucmpl_d           ,/** compare unsigned uint_128 less than type Double. **/
    licmpg_d            ,/** compare int_128 greater than type Double. **/
    liucmpg_d           ,/** compare unsigned uint_128 greater than type Double. **/
    licmpe_d            ,/** compare int_128 equal with type Double. **/
    liucmpe_d           ,/** compare unsigned uint_128 equal with type Double. **/
    licmple_d           ,/** compare int_128 less than or equal to type Double. **/
    liucmple_d          ,/** compare unsigned uint_128 less than or equal to type Double. **/
    licmpge_d           ,/** compare int_128 greater than or equal to type Double. **/
    liucmpge_d          ,/** compare unsigned uint_128 greater than or equal to type Double. **/
    licmpne_d           ,/** compare int_128 not equal with type Double. **/
    liucmpne_d          ,/** compare unsigned uint_128 not equal with type Double. **/
    licast_df           ,/** cast int_128 to type DoubleFloat. **/
    liucast_df          ,/** cast unsigned uint_128 to type DoubleFloat. **/
    liadd_df            ,/** add int_128 with type DoubleFloat. **/
    liuadd_df           ,/** add unsigned uint_128 with type DoubleFloat. **/
    lisub_df            ,/** subtract int_128 with type DoubleFloat. **/
    liusub_df           ,/** subtract unsigned uint_128 with type DoubleFloat. **/
    limul_df            ,/** multiply int_128 with type DoubleFloat. **/
    liumul_df           ,/** multiply unsigned uint_128 with type DoubleFloat. **/
    lidiv_df            ,/** divide int_128 with type DoubleFloat. **/
    liudiv_df           ,/** divide unsigned uint_128 with type DoubleFloat. **/
    licmpl_df           ,/** compare int_128 less than type DoubleFloat. **/
    liucmpl_df          ,/** compare unsigned uint_128 less than type DoubleFloat. **/
    licmpg_df           ,/** compare int_128 greater than type DoubleFloat. **/
    liucmpg_df          ,/** compare unsigned uint_128 greater than type DoubleFloat. **/
    licmpe_df           ,/** compare int_128 equal with type DoubleFloat. **/
    liucmpe_df          ,/** compare unsigned uint_128 equal with type DoubleFloat. **/
    licmple_df          ,/** compare int_128 less than or equal to type DoubleFloat. **/
    liucmple_df         ,/** compare unsigned uint_128 less than or equal to type DoubleFloat. **/
    licmpge_df          ,/** compare int_128 greater than or equal to type DoubleFloat. **/
    liucmpge_df         ,/** compare unsigned uint_128 greater than or equal to type DoubleFloat. **/
    licmpne_df          ,/** compare int_128 not equal with type DoubleFloat. **/
    liucmpne_df         ,/** compare unsigned uint_128 not equal with type DoubleFloat. **/
    licast_dd           ,/** cast int_128 to type DoubleDouble. **/
    liucast_dd          ,/** cast unsigned uint_128 to type DoubleDouble. **/
    liadd_dd            ,/** add int_128 with type DoubleDouble. **/
    liuadd_dd           ,/** add unsigned uint_128 with type DoubleDouble. **/
    lisub_dd            ,/** subtract int_128 with type DoubleDouble. **/
    liusub_dd           ,/** subtract unsigned uint_128 with type DoubleDouble. **/
    limul_dd            ,/** multiply int_128 with type DoubleDouble. **/
    liumul_dd           ,/** multiply unsigned uint_128 with type DoubleDouble. **/
    lidiv_dd            ,/** divide int_128 with type DoubleDouble. **/
    liudiv_dd           ,/** divide unsigned uint_128 with type DoubleDouble. **/
    licmpl_dd           ,/** compare int_128 less than type DoubleDouble. **/
    liucmpl_dd          ,/** compare unsigned uint_128 less than type DoubleDouble. **/
    licmpg_dd           ,/** compare int_128 greater than type DoubleDouble. **/
    liucmpg_dd          ,/** compare unsigned uint_128 greater than type DoubleDouble. **/
    licmpe_dd           ,/** compare int_128 equal with type DoubleDouble. **/
    liucmpe_dd          ,/** compare unsigned uint_128 equal with type DoubleDouble. **/
    licmple_dd          ,/** compare int_128 less than or equal to type DoubleDouble. **/
    liucmple_dd         ,/** compare unsigned uint_128 less than or equal to type DoubleDouble. **/
    licmpge_dd          ,/** compare int_128 greater than or equal to type DoubleDouble. **/
    liucmpge_dd         ,/** compare unsigned uint_128 greater than or equal to type DoubleDouble. **/
    licmpne_dd          ,/** compare int_128 not equal with type DoubleDouble. **/
    liucmpne_dd         ,/** compare unsigned uint_128 not equal with type DoubleDouble. **/
    limod_b             ,/** modulo int_128 with type Byte. **/
    licast_ub           ,/** cast int_128 to unsigned type Byte. **/
    liucast_ub          ,/** cast unsigned uint_128 to unsigned type Byte. **/
    liadd_ub            ,/** add int_128 with unsigned type Byte. **/
    liuadd_ub           ,/** add unsigned uint_128 with unsigned type Byte. **/
    lisub_ub            ,/** subtract int_128 with unsigned type Byte. **/
    liusub_ub           ,/** subtract unsigned uint_128 with unsigned type Byte. **/
    limul_ub            ,/** multiply int_128 with unsigned type Byte. **/
    liumul_ub           ,/** multiply unsigned uint_128 with unsigned type Byte. **/
    lidiv_ub            ,/** divide int_128 with unsigned type Byte. **/
    liudiv_ub           ,/** divide unsigned uint_128 with unsigned type Byte. **/
    licmpl_ub           ,/** compare int_128 less than unsigned type Byte. **/
    liucmpl_ub          ,/** compare unsigned uint_128 less than unsigned type Byte. **/
    licmpg_ub           ,/** compare int_128 greater than unsigned type Byte. **/
    liucmpg_ub          ,/** compare unsigned uint_128 greater than unsigned type Byte. **/
    licmpe_ub           ,/** compare int_128 equal with unsigned type Byte. **/
    liucmpe_ub          ,/** compare unsigned uint_128 equal with unsigned type Byte. **/
    licmple_ub          ,/** compare int_128 less than or equal to unsigned type Byte. **/
    liucmple_ub         ,/** compare unsigned uint_128 less than or equal to unsigned type Byte. **/
    licmpge_ub          ,/** compare int_128 greater than or equal to unsigned type Byte. **/
    liucmpge_ub         ,/** compare unsigned uint_128 greater than or equal to unsigned type Byte. **/
    licmpne_ub          ,/** compare int_128 not equal with unsigned type Byte. **/
    liucmpne_ub         ,/** compare unsigned uint_128 not equal with unsigned type Byte. **/
    limod_s             ,/** modulo int_128 with type Short. **/
    licast_us           ,/** cast int_128 to unsigned type Short. **/
    liucast_us          ,/** cast unsigned uint_128 to unsigned type Short. **/
    liadd_us            ,/** add int_128 with unsigned type Short. **/
    liuadd_us           ,/** add unsigned uint_128 with unsigned type Short. **/
    lisub_us            ,/** subtract int_128 with unsigned type Short. **/
    liusub_us           ,/** subtract unsigned uint_128 with unsigned type Short. **/
    limul_us            ,/** multiply int_128 with unsigned type Short. **/
    liumul_us           ,/** multiply unsigned uint_128 with unsigned type Short. **/
    lidiv_us            ,/** divide int_128 with unsigned type Short. **/
    liudiv_us           ,/** divide unsigned uint_128 with unsigned type Short. **/
    licmpl_us           ,/** compare int_128 less than unsigned type Short. **/
    liucmpl_us          ,/** compare unsigned uint_128 less than unsigned type Short. **/
    licmpg_us           ,/** compare int_128 greater than unsigned type Short. **/
    liucmpg_us          ,/** compare unsigned uint_128 greater than unsigned type Short. **/
    licmpe_us           ,/** compare int_128 equal with unsigned type Short. **/
    liucmpe_us          ,/** compare unsigned uint_128 equal with unsigned type Short. **/
    licmple_us          ,/** compare int_128 less than or equal to unsigned type Short. **/
    liucmple_us         ,/** compare unsigned uint_128 less than or equal to unsigned type Short. **/
    licmpge_us          ,/** compare int_128 greater than or equal to unsigned type Short. **/
    liucmpge_us         ,/** compare unsigned uint_128 greater than or equal to unsigned type Short. **/
    licmpne_us          ,/** compare int_128 not equal with unsigned type Short. **/
    liucmpne_us         ,/** compare unsigned uint_128 not equal with unsigned type Short. **/
    limod_i             ,/** modulo int_128 with type Int. **/
    licast_ui           ,/** cast int_128 to unsigned type Int. **/
    liucast_ui          ,/** cast unsigned uint_128 to unsigned type Int. **/
    liadd_ui            ,/** add int_128 with unsigned type Int. **/
    liuadd_ui           ,/** add unsigned uint_128 with unsigned type Int. **/
    lisub_ui            ,/** subtract int_128 with unsigned type Int. **/
    liusub_ui           ,/** subtract unsigned uint_128 with unsigned type Int. **/
    limul_ui            ,/** multiply int_128 with unsigned type Int. **/
    liumul_ui           ,/** multiply unsigned uint_128 with unsigned type Int. **/
    lidiv_ui            ,/** divide int_128 with unsigned type Int. **/
    liudiv_ui           ,/** divide unsigned uint_128 with unsigned type Int. **/
    licmpl_ui           ,/** compare int_128 less than unsigned type Int. **/
    liucmpl_ui          ,/** compare unsigned uint_128 less than unsigned type Int. **/
    licmpg_ui           ,/** compare int_128 greater than unsigned type Int. **/
    liucmpg_ui          ,/** compare unsigned uint_128 greater than unsigned type Int. **/
    licmpe_ui           ,/** compare int_128 equal with unsigned type Int. **/
    liucmpe_ui          ,/** compare unsigned uint_128 equal with unsigned type Int. **/
    licmple_ui          ,/** compare int_128 less than or equal to unsigned type Int. **/
    liucmple_ui         ,/** compare unsigned uint_128 less than or equal to unsigned type Int. **/
    licmpge_ui          ,/** compare int_128 greater than or equal to unsigned type Int. **/
    liucmpge_ui         ,/** compare unsigned uint_128 greater than or equal to unsigned type Int. **/
    licmpne_ui          ,/** compare int_128 not equal with unsigned type Int. **/
    liucmpne_ui         ,/** compare unsigned uint_128 not equal with unsigned type Int. **/
    limod_l             ,/** modulo int_128 with type Long. **/
    licast_ul           ,/** cast int_128 to unsigned type Long. **/
    liucast_ul          ,/** cast unsigned uint_128 to unsigned type Long. **/
    liadd_ul            ,/** add int_128 with unsigned type Long. **/
    liuadd_ul           ,/** add unsigned uint_128 with unsigned type Long. **/
    lisub_ul            ,/** subtract int_128 with unsigned type Long. **/
    liusub_ul           ,/** subtract unsigned uint_128 with unsigned type Long. **/
    limul_ul            ,/** multiply int_128 with unsigned type Long. **/
    liumul_ul           ,/** multiply unsigned uint_128 with unsigned type Long. **/
    lidiv_ul            ,/** divide int_128 with unsigned type Long. **/
    liudiv_ul           ,/** divide unsigned uint_128 with unsigned type Long. **/
    licmpl_ul           ,/** compare int_128 less than unsigned type Long. **/
    liucmpl_ul          ,/** compare unsigned uint_128 less than unsigned type Long. **/
    licmpg_ul           ,/** compare int_128 greater than unsigned type Long. **/
    liucmpg_ul          ,/** compare unsigned uint_128 greater than unsigned type Long. **/
    licmpe_ul           ,/** compare int_128 equal with unsigned type Long. **/
    liucmpe_ul          ,/** compare unsigned uint_128 equal with unsigned type Long. **/
    licmple_ul          ,/** compare int_128 less than or equal to unsigned type Long. **/
    liucmple_ul         ,/** compare unsigned uint_128 less than or equal to unsigned type Long. **/
    licmpge_ul          ,/** compare int_128 greater than or equal to unsigned type Long. **/
    liucmpge_ul         ,/** compare unsigned uint_128 greater than or equal to unsigned type Long. **/
    licmpne_ul          ,/** compare int_128 not equal with unsigned type Long. **/
    liucmpne_ul         ,/** compare unsigned uint_128 not equal with unsigned type Long. **/
    limod_li            ,/** modulo int_128 with type LongInt. **/
    licast_uli          ,/** cast int_128 to unsigned type LongInt. **/
    liucast_uli         ,/** cast unsigned uint_128 to unsigned type LongInt. **/
    liadd_uli           ,/** add int_128 with unsigned type LongInt. **/
    liuadd_uli          ,/** add unsigned uint_128 with unsigned type LongInt. **/
    lisub_uli           ,/** subtract int_128 with unsigned type LongInt. **/
    liusub_uli          ,/** subtract unsigned uint_128 with unsigned type LongInt. **/
    limul_uli           ,/** multiply int_128 with unsigned type LongInt. **/
    liumul_uli          ,/** multiply unsigned uint_128 with unsigned type LongInt. **/
    lidiv_uli           ,/** divide int_128 with unsigned type LongInt. **/
    liudiv_uli          ,/** divide unsigned uint_128 with unsigned type LongInt. **/
    licmpl_uli          ,/** compare int_128 less than unsigned type LongInt. **/
    liucmpl_uli         ,/** compare unsigned uint_128 less than unsigned type LongInt. **/
    licmpg_uli          ,/** compare int_128 greater than unsigned type LongInt. **/
    liucmpg_uli         ,/** compare unsigned uint_128 greater than unsigned type LongInt. **/
    licmpe_uli          ,/** compare int_128 equal with unsigned type LongInt. **/
    liucmpe_uli         ,/** compare unsigned uint_128 equal with unsigned type LongInt. **/
    licmple_uli         ,/** compare int_128 less than or equal to unsigned type LongInt. **/
    liucmple_uli        ,/** compare unsigned uint_128 less than or equal to unsigned type LongInt. **/
    licmpge_uli         ,/** compare int_128 greater than or equal to unsigned type LongInt. **/
    liucmpge_uli        ,/** compare unsigned uint_128 greater than or equal to unsigned type LongInt. **/
    licmpne_uli         ,/** compare int_128 not equal with unsigned type LongInt. **/
    liucmpne_uli        ,/** compare unsigned uint_128 not equal with unsigned type LongInt. **/
    limod_ll            ,/** modulo int_128 with type LongLong. **/
    licast_ull          ,/** cast int_128 to unsigned type LongLong. **/
    liucast_ull         ,/** cast unsigned uint_128 to unsigned type LongLong. **/
    liadd_ull           ,/** add int_128 with unsigned type LongLong. **/
    liuadd_ull          ,/** add unsigned uint_128 with unsigned type LongLong. **/
    lisub_ull           ,/** subtract int_128 with unsigned type LongLong. **/
    liusub_ull          ,/** subtract unsigned uint_128 with unsigned type LongLong. **/
    limul_ull           ,/** multiply int_128 with unsigned type LongLong. **/
    liumul_ull          ,/** multiply unsigned uint_128 with unsigned type LongLong. **/
    lidiv_ull           ,/** divide int_128 with unsigned type LongLong. **/
    liudiv_ull          ,/** divide unsigned uint_128 with unsigned type LongLong. **/
    licmpl_ull          ,/** compare int_128 less than unsigned type LongLong. **/
    liucmpl_ull         ,/** compare unsigned uint_128 less than unsigned type LongLong. **/
    licmpg_ull          ,/** compare int_128 greater than unsigned type LongLong. **/
    liucmpg_ull         ,/** compare unsigned uint_128 greater than unsigned type LongLong. **/
    licmpe_ull          ,/** compare int_128 equal with unsigned type LongLong. **/
    liucmpe_ull         ,/** compare unsigned uint_128 equal with unsigned type LongLong. **/
    licmple_ull         ,/** compare int_128 less than or equal to unsigned type LongLong. **/
    liucmple_ull        ,/** compare unsigned uint_128 less than or equal to unsigned type LongLong. **/
    licmpge_ull         ,/** compare int_128 greater than or equal to unsigned type LongLong. **/
    liucmpge_ull        ,/** compare unsigned uint_128 greater than or equal to unsigned type LongLong. **/
    licmpne_ull         ,/** compare int_128 not equal with unsigned type LongLong. **/
    liucmpne_ull        ,/** compare unsigned uint_128 not equal with unsigned type LongLong. **/
    liand_b             ,/** bitwise and int_128 with type Byte. **/
    lior_b              ,/** bitwise or int_128 with type Byte. **/
    lixor_b             ,/** bitwise xor int_128 with type Byte. **/
    lishftr_b           ,/** shift right int_128 with type Byte. **/
    lishftl_b           ,/** shift left xor int_128 with type Byte. **/
    liand_s             ,/** bitwise and int_128 with type Short. **/
    lior_s              ,/** bitwise or int_128 with type Short. **/
    lixor_s             ,/** bitwise xor int_128 with type Short. **/
    lishftr_s           ,/** shift right int_128 with type Short. **/
    lishftl_s           ,/** shift left xor int_128 with type Short. **/
    liand_i             ,/** bitwise and int_128 with type Int. **/
    lior_i              ,/** bitwise or int_128 with type Int. **/
    lixor_i             ,/** bitwise xor int_128 with type Int. **/
    lishftr_i           ,/** shift right int_128 with type Int. **/
    lishftl_i           ,/** shift left xor int_128 with type Int. **/
    liand_l             ,/** bitwise and int_128 with type Long. **/
    lior_l              ,/** bitwise or int_128 with type Long. **/
    lixor_l             ,/** bitwise xor int_128 with type Long. **/
    lishftr_l           ,/** shift right int_128 with type Long. **/
    lishftl_l           ,/** shift left xor int_128 with type Long. **/
    liand_li            ,/** bitwise and int_128 with type LongInt. **/
    lior_li             ,/** bitwise or int_128 with type LongInt. **/
    lixor_li            ,/** bitwise xor int_128 with type LongInt. **/
    lishftr_li          ,/** shift right int_128 with type LongInt. **/
    lishftl_li          ,/** shift left xor int_128 with type LongInt. **/
    liand_ll            ,/** bitwise and int_128 with type LongLong. **/
    lior_ll             ,/** bitwise or int_128 with type LongLong. **/
    lixor_ll            ,/** bitwise xor int_128 with type LongLong. **/
    lishftr_ll          ,/** shift right int_128 with type LongLong. **/
    lishftl_ll          ,/** shift left xor int_128 with type LongLong. **/
    lidup               ,/** duplicate a int_128 on the stack. **/
    lidup2              ,/** duplicate a int_128 2 times on the stack. **/
    lidup3              ,/** duplicate a int_128 3 times on the stack. **/
    lidup4              ,/** duplicate a int_128 4 times on the stack. **/
    lidup5              ,/** duplicate a int_128 5 times on the stack. **/
    liset               ,/** set a int_128 from stack into a field on base pointer. **/
    liget               ,/** get a int_128 from a field on base pointer to stack. **/
    livset              ,/** set a int_128 from value into a field on base pointer. **/
    lisget              ,/** get a int_128 from a field on base pointer to stack using address from stack. **/
    lisset              ,/** set a int_128 from stack into a field on base pointer using address from stack. **/
    lisetl              ,/** set a int_128 from local variable into a field on base pointer. **/
    liinc_1             ,/** increment int_128 by 1 on stack. **/
    liinc_2             ,/** increment int_128 by 2 on stack. **/
    listinc_1           ,/** increment int_128 by 1 on stack. **/
    listinc_2           ,/** increment int_128 by 2 on stack. **/
    lireturn            ,/** return a int_128 into the main stack. **/
    limainst            ,/** store a int_128 from main stack in a local variable.. **/
    limainst_0          ,/** store a int_128 from main stack in local variable 0. **/
    limainst_1          ,/** store a int_128 from main stack in local variable 1. **/
    limainst_2          ,/** store a int_128 from main stack in local variable 2. **/
    limainst_3          ,/** store a int_128 from main stack in local variable 3. **/
    liprint             ,/** print a int_128 from stack. **/
    liuprint            ,/** print a unsigned uint_128 from stack. **/
    llprintba           ,/** print a byte array. **/
    llconst             ,/** push a const int_256 into the stack. **/
    llconst_0           ,/** push a const int_256 into the stack (value = 0). **/
    llconst_1           ,/** push a const int_256 into the stack (value = 1). **/
    llconst_2           ,/** push a const int_256 into the stack (value = 2). **/
    llconst_3           ,/** push a const int_256 into the stack (value = 3). **/
    llconst_4           ,/** push a const int_256 into the stack (value = 4). **/
    llconst_5           ,/** push a const int_256 into the stack (value = 5). **/
    llconst_6           ,/** push a const int_256 into the stack (value = 6). **/
    llconst_9           ,/** push a const int_256 into the stack (value = 9). **/
    llconst_10          ,/** push a const int_256 into the stack (value = 10). **/
    llconst_11          ,/** push a const int_256 into the stack (value = 11). **/
    llconst_12          ,/** push a const int_256 into the stack (value = 12). **/
    llload              ,/** load a int_256 into the stack from local variable. **/
    llload_0            ,/** load a int_256 into the stack from local variable 0. **/
    llload_1            ,/** load a int_256 into the stack from local variable 1. **/
    llload_2            ,/** load a int_256 into the stack from local variable 2. **/
    llload_3            ,/** load a int_256 into the stack from local variable 3. **/
    llload_4            ,/** load a int_256 into the stack from local variable 4. **/
    llstore             ,/** store a int_256 from stack into local variable. **/
    llstore_0           ,/** store a int_256 from stack into local variable 0. **/
    llstore_1           ,/** store a int_256 from stack into local variable 1. **/
    llstore_2           ,/** store a int_256 from stack into local variable 2. **/
    llstore_3           ,/** store a int_256 from stack into local variable 3. **/
    llstore_4           ,/** store a int_256 from stack into local variable 4. **/
    llcast_b            ,/** cast int_256 to type Byte. **/
    llucast_b           ,/** cast unsigned uint_256 to type Byte. **/
    lladd_b             ,/** add int_256 with type Byte. **/
    lluadd_b            ,/** add unsigned uint_256 with type Byte. **/
    llsub_b             ,/** subtract int_256 with type Byte. **/
    llusub_b            ,/** subtract unsigned uint_256 with type Byte. **/
    llmul_b             ,/** multiply int_256 with type Byte. **/
    llumul_b            ,/** multiply unsigned uint_256 with type Byte. **/
    lldiv_b             ,/** divide int_256 with type Byte. **/
    lludiv_b            ,/** divide unsigned uint_256 with type Byte. **/
    llcmpl_b            ,/** compare int_256 less than type Byte. **/
    llucmpl_b           ,/** compare unsigned uint_256 less than type Byte. **/
    llcmpg_b            ,/** compare int_256 greater than type Byte. **/
    llucmpg_b           ,/** compare unsigned uint_256 greater than type Byte. **/
    llcmpe_b            ,/** compare int_256 equal with type Byte. **/
    llucmpe_b           ,/** compare unsigned uint_256 equal with type Byte. **/
    llcmple_b           ,/** compare int_256 less than or equal to type Byte. **/
    llucmple_b          ,/** compare unsigned uint_256 less than or equal to type Byte. **/
    llcmpge_b           ,/** compare int_256 greater than or equal to type Byte. **/
    llucmpge_b          ,/** compare unsigned uint_256 greater than or equal to type Byte. **/
    llcmpne_b           ,/** compare int_256 not equal with type Byte. **/
    llucmpne_b          ,/** compare unsigned uint_256 not equal with type Byte. **/
    llcast_s            ,/** cast int_256 to type Short. **/
    llucast_s           ,/** cast unsigned uint_256 to type Short. **/
    lladd_s             ,/** add int_256 with type Short. **/
    lluadd_s            ,/** add unsigned uint_256 with type Short. **/
    llsub_s             ,/** subtract int_256 with type Short. **/
    llusub_s            ,/** subtract unsigned uint_256 with type Short. **/
    llmul_s             ,/** multiply int_256 with type Short. **/
    llumul_s            ,/** multiply unsigned uint_256 with type Short. **/
    lldiv_s             ,/** divide int_256 with type Short. **/
    lludiv_s            ,/** divide unsigned uint_256 with type Short. **/
    llcmpl_s            ,/** compare int_256 less than type Short. **/
    llucmpl_s           ,/** compare unsigned uint_256 less than type Short. **/
    llcmpg_s            ,/** compare int_256 greater than type Short. **/
    llucmpg_s           ,/** compare unsigned uint_256 greater than type Short. **/
    llcmpe_s            ,/** compare int_256 equal with type Short. **/
    llucmpe_s           ,/** compare unsigned uint_256 equal with type Short. **/
    llcmple_s           ,/** compare int_256 less than or equal to type Short. **/
    llucmple_s          ,/** compare unsigned uint_256 less than or equal to type Short. **/
    llcmpge_s           ,/** compare int_256 greater than or equal to type Short. **/
    llucmpge_s          ,/** compare unsigned uint_256 greater than or equal to type Short. **/
    llcmpne_s           ,/** compare int_256 not equal with type Short. **/
    llucmpne_s          ,/** compare unsigned uint_256 not equal with type Short. **/
    llcast_i            ,/** cast int_256 to type Int. **/
    llucast_i           ,/** cast unsigned uint_256 to type Int. **/
    lladd_i             ,/** add int_256 with type Int. **/
    lluadd_i            ,/** add unsigned uint_256 with type Int. **/
    llsub_i             ,/** subtract int_256 with type Int. **/
    llusub_i            ,/** subtract unsigned uint_256 with type Int. **/
    llmul_i             ,/** multiply int_256 with type Int. **/
    llumul_i            ,/** multiply unsigned uint_256 with type Int. **/
    lldiv_i             ,/** divide int_256 with type Int. **/
    lludiv_i            ,/** divide unsigned uint_256 with type Int. **/
    llcmpl_i            ,/** compare int_256 less than type Int. **/
    llucmpl_i           ,/** compare unsigned uint_256 less than type Int. **/
    llcmpg_i            ,/** compare int_256 greater than type Int. **/
    llucmpg_i           ,/** compare unsigned uint_256 greater than type Int. **/
    llcmpe_i            ,/** compare int_256 equal with type Int. **/
    llucmpe_i           ,/** compare unsigned uint_256 equal with type Int. **/
    llcmple_i           ,/** compare int_256 less than or equal to type Int. **/
    llucmple_i          ,/** compare unsigned uint_256 less than or equal to type Int. **/
    llcmpge_i           ,/** compare int_256 greater than or equal to type Int. **/
    llucmpge_i          ,/** compare unsigned uint_256 greater than or equal to type Int. **/
    llcmpne_i           ,/** compare int_256 not equal with type Int. **/
    llucmpne_i          ,/** compare unsigned uint_256 not equal with type Int. **/
    llcast_l            ,/** cast int_256 to type Long. **/
    llucast_l           ,/** cast unsigned uint_256 to type Long. **/
    lladd_l             ,/** add int_256 with type Long. **/
    lluadd_l            ,/** add unsigned uint_256 with type Long. **/
    llsub_l             ,/** subtract int_256 with type Long. **/
    llusub_l            ,/** subtract unsigned uint_256 with type Long. **/
    llmul_l             ,/** multiply int_256 with type Long. **/
    llumul_l            ,/** multiply unsigned uint_256 with type Long. **/
    lldiv_l             ,/** divide int_256 with type Long. **/
    lludiv_l            ,/** divide unsigned uint_256 with type Long. **/
    llcmpl_l            ,/** compare int_256 less than type Long. **/
    llucmpl_l           ,/** compare unsigned uint_256 less than type Long. **/
    llcmpg_l            ,/** compare int_256 greater than type Long. **/
    llucmpg_l           ,/** compare unsigned uint_256 greater than type Long. **/
    llcmpe_l            ,/** compare int_256 equal with type Long. **/
    llucmpe_l           ,/** compare unsigned uint_256 equal with type Long. **/
    llcmple_l           ,/** compare int_256 less than or equal to type Long. **/
    llucmple_l          ,/** compare unsigned uint_256 less than or equal to type Long. **/
    llcmpge_l           ,/** compare int_256 greater than or equal to type Long. **/
    llucmpge_l          ,/** compare unsigned uint_256 greater than or equal to type Long. **/
    llcmpne_l           ,/** compare int_256 not equal with type Long. **/
    llucmpne_l          ,/** compare unsigned uint_256 not equal with type Long. **/
    llcast_li           ,/** cast int_256 to type LongInt. **/
    llucast_li          ,/** cast unsigned uint_256 to type LongInt. **/
    lladd_li            ,/** add int_256 with type LongInt. **/
    lluadd_li           ,/** add unsigned uint_256 with type LongInt. **/
    llsub_li            ,/** subtract int_256 with type LongInt. **/
    llusub_li           ,/** subtract unsigned uint_256 with type LongInt. **/
    llmul_li            ,/** multiply int_256 with type LongInt. **/
    llumul_li           ,/** multiply unsigned uint_256 with type LongInt. **/
    lldiv_li            ,/** divide int_256 with type LongInt. **/
    lludiv_li           ,/** divide unsigned uint_256 with type LongInt. **/
    llcmpl_li           ,/** compare int_256 less than type LongInt. **/
    llucmpl_li          ,/** compare unsigned uint_256 less than type LongInt. **/
    llcmpg_li           ,/** compare int_256 greater than type LongInt. **/
    llucmpg_li          ,/** compare unsigned uint_256 greater than type LongInt. **/
    llcmpe_li           ,/** compare int_256 equal with type LongInt. **/
    llucmpe_li          ,/** compare unsigned uint_256 equal with type LongInt. **/
    llcmple_li          ,/** compare int_256 less than or equal to type LongInt. **/
    llucmple_li         ,/** compare unsigned uint_256 less than or equal to type LongInt. **/
    llcmpge_li          ,/** compare int_256 greater than or equal to type LongInt. **/
    llucmpge_li         ,/** compare unsigned uint_256 greater than or equal to type LongInt. **/
    llcmpne_li          ,/** compare int_256 not equal with type LongInt. **/
    llucmpne_li         ,/** compare unsigned uint_256 not equal with type LongInt. **/
    llcast_ll           ,/** cast int_256 to type LongLong. **/
    llucast_ll          ,/** cast unsigned uint_256 to type LongLong. **/
    lladd_ll            ,/** add int_256 with type LongLong. **/
    lluadd_ll           ,/** add unsigned uint_256 with type LongLong. **/
    llsub_ll            ,/** subtract int_256 with type LongLong. **/
    llusub_ll           ,/** subtract unsigned uint_256 with type LongLong. **/
    llmul_ll            ,/** multiply int_256 with type LongLong. **/
    llumul_ll           ,/** multiply unsigned uint_256 with type LongLong. **/
    lldiv_ll            ,/** divide int_256 with type LongLong. **/
    lludiv_ll           ,/** divide unsigned uint_256 with type LongLong. **/
    llcmpl_ll           ,/** compare int_256 less than type LongLong. **/
    llucmpl_ll          ,/** compare unsigned uint_256 less than type LongLong. **/
    llcmpg_ll           ,/** compare int_256 greater than type LongLong. **/
    llucmpg_ll          ,/** compare unsigned uint_256 greater than type LongLong. **/
    llcmpe_ll           ,/** compare int_256 equal with type LongLong. **/
    llucmpe_ll          ,/** compare unsigned uint_256 equal with type LongLong. **/
    llcmple_ll          ,/** compare int_256 less than or equal to type LongLong. **/
    llucmple_ll         ,/** compare unsigned uint_256 less than or equal to type LongLong. **/
    llcmpge_ll          ,/** compare int_256 greater than or equal to type LongLong. **/
    llucmpge_ll         ,/** compare unsigned uint_256 greater than or equal to type LongLong. **/
    llcmpne_ll          ,/** compare int_256 not equal with type LongLong. **/
    llucmpne_ll         ,/** compare unsigned uint_256 not equal with type LongLong. **/
    llcast_f            ,/** cast int_256 to type Float. **/
    llucast_f           ,/** cast unsigned uint_256 to type Float. **/
    lladd_f             ,/** add int_256 with type Float. **/
    lluadd_f            ,/** add unsigned uint_256 with type Float. **/
    llsub_f             ,/** subtract int_256 with type Float. **/
    llusub_f            ,/** subtract unsigned uint_256 with type Float. **/
    llmul_f             ,/** multiply int_256 with type Float. **/
    llumul_f            ,/** multiply unsigned uint_256 with type Float. **/
    lldiv_f             ,/** divide int_256 with type Float. **/
    lludiv_f            ,/** divide unsigned uint_256 with type Float. **/
    llcmpl_f            ,/** compare int_256 less than type Float. **/
    llucmpl_f           ,/** compare unsigned uint_256 less than type Float. **/
    llcmpg_f            ,/** compare int_256 greater than type Float. **/
    llucmpg_f           ,/** compare unsigned uint_256 greater than type Float. **/
    llcmpe_f            ,/** compare int_256 equal with type Float. **/
    llucmpe_f           ,/** compare unsigned uint_256 equal with type Float. **/
    llcmple_f           ,/** compare int_256 less than or equal to type Float. **/
    llucmple_f          ,/** compare unsigned uint_256 less than or equal to type Float. **/
    llcmpge_f           ,/** compare int_256 greater than or equal to type Float. **/
    llucmpge_f          ,/** compare unsigned uint_256 greater than or equal to type Float. **/
    llcmpne_f           ,/** compare int_256 not equal with type Float. **/
    llucmpne_f          ,/** compare unsigned uint_256 not equal with type Float. **/
    llcast_d            ,/** cast int_256 to type Double. **/
    llucast_d           ,/** cast unsigned uint_256 to type Double. **/
    lladd_d             ,/** add int_256 with type Double. **/
    lluadd_d            ,/** add unsigned uint_256 with type Double. **/
    llsub_d             ,/** subtract int_256 with type Double. **/
    llusub_d            ,/** subtract unsigned uint_256 with type Double. **/
    llmul_d             ,/** multiply int_256 with type Double. **/
    llumul_d            ,/** multiply unsigned uint_256 with type Double. **/
    lldiv_d             ,/** divide int_256 with type Double. **/
    lludiv_d            ,/** divide unsigned uint_256 with type Double. **/
    llcmpl_d            ,/** compare int_256 less than type Double. **/
    llucmpl_d           ,/** compare unsigned uint_256 less than type Double. **/
    llcmpg_d            ,/** compare int_256 greater than type Double. **/
    llucmpg_d           ,/** compare unsigned uint_256 greater than type Double. **/
    llcmpe_d            ,/** compare int_256 equal with type Double. **/
    llucmpe_d           ,/** compare unsigned uint_256 equal with type Double. **/
    llcmple_d           ,/** compare int_256 less than or equal to type Double. **/
    llucmple_d          ,/** compare unsigned uint_256 less than or equal to type Double. **/
    llcmpge_d           ,/** compare int_256 greater than or equal to type Double. **/
    llucmpge_d          ,/** compare unsigned uint_256 greater than or equal to type Double. **/
    llcmpne_d           ,/** compare int_256 not equal with type Double. **/
    llucmpne_d          ,/** compare unsigned uint_256 not equal with type Double. **/
    llcast_df           ,/** cast int_256 to type DoubleFloat. **/
    llucast_df          ,/** cast unsigned uint_256 to type DoubleFloat. **/
    lladd_df            ,/** add int_256 with type DoubleFloat. **/
    lluadd_df           ,/** add unsigned uint_256 with type DoubleFloat. **/
    llsub_df            ,/** subtract int_256 with type DoubleFloat. **/
    llusub_df           ,/** subtract unsigned uint_256 with type DoubleFloat. **/
    llmul_df            ,/** multiply int_256 with type DoubleFloat. **/
    llumul_df           ,/** multiply unsigned uint_256 with type DoubleFloat. **/
    lldiv_df            ,/** divide int_256 with type DoubleFloat. **/
    lludiv_df           ,/** divide unsigned uint_256 with type DoubleFloat. **/
    llcmpl_df           ,/** compare int_256 less than type DoubleFloat. **/
    llucmpl_df          ,/** compare unsigned uint_256 less than type DoubleFloat. **/
    llcmpg_df           ,/** compare int_256 greater than type DoubleFloat. **/
    llucmpg_df          ,/** compare unsigned uint_256 greater than type DoubleFloat. **/
    llcmpe_df           ,/** compare int_256 equal with type DoubleFloat. **/
    llucmpe_df          ,/** compare unsigned uint_256 equal with type DoubleFloat. **/
    llcmple_df          ,/** compare int_256 less than or equal to type DoubleFloat. **/
    llucmple_df         ,/** compare unsigned uint_256 less than or equal to type DoubleFloat. **/
    llcmpge_df          ,/** compare int_256 greater than or equal to type DoubleFloat. **/
    llucmpge_df         ,/** compare unsigned uint_256 greater than or equal to type DoubleFloat. **/
    llcmpne_df          ,/** compare int_256 not equal with type DoubleFloat. **/
    llucmpne_df         ,/** compare unsigned uint_256 not equal with type DoubleFloat. **/
    llcast_dd           ,/** cast int_256 to type DoubleDouble. **/
    llucast_dd          ,/** cast unsigned uint_256 to type DoubleDouble. **/
    lladd_dd            ,/** add int_256 with type DoubleDouble. **/
    lluadd_dd           ,/** add unsigned uint_256 with type DoubleDouble. **/
    llsub_dd            ,/** subtract int_256 with type DoubleDouble. **/
    llusub_dd           ,/** subtract unsigned uint_256 with type DoubleDouble. **/
    llmul_dd            ,/** multiply int_256 with type DoubleDouble. **/
    llumul_dd           ,/** multiply unsigned uint_256 with type DoubleDouble. **/
    lldiv_dd            ,/** divide int_256 with type DoubleDouble. **/
    lludiv_dd           ,/** divide unsigned uint_256 with type DoubleDouble. **/
    llcmpl_dd           ,/** compare int_256 less than type DoubleDouble. **/
    llucmpl_dd          ,/** compare unsigned uint_256 less than type DoubleDouble. **/
    llcmpg_dd           ,/** compare int_256 greater than type DoubleDouble. **/
    llucmpg_dd          ,/** compare unsigned uint_256 greater than type DoubleDouble. **/
    llcmpe_dd           ,/** compare int_256 equal with type DoubleDouble. **/
    llucmpe_dd          ,/** compare unsigned uint_256 equal with type DoubleDouble. **/
    llcmple_dd          ,/** compare int_256 less than or equal to type DoubleDouble. **/
    llucmple_dd         ,/** compare unsigned uint_256 less than or equal to type DoubleDouble. **/
    llcmpge_dd          ,/** compare int_256 greater than or equal to type DoubleDouble. **/
    llucmpge_dd         ,/** compare unsigned uint_256 greater than or equal to type DoubleDouble. **/
    llcmpne_dd          ,/** compare int_256 not equal with type DoubleDouble. **/
    llucmpne_dd         ,/** compare unsigned uint_256 not equal with type DoubleDouble. **/
    llmod_b             ,/** modulo int_256 with type Byte. **/
    llcast_ub           ,/** cast int_256 to unsigned type Byte. **/
    llucast_ub          ,/** cast unsigned uint_256 to unsigned type Byte. **/
    lladd_ub            ,/** add int_256 with unsigned type Byte. **/
    lluadd_ub           ,/** add unsigned uint_256 with unsigned type Byte. **/
    llsub_ub            ,/** subtract int_256 with unsigned type Byte. **/
    llusub_ub           ,/** subtract unsigned uint_256 with unsigned type Byte. **/
    llmul_ub            ,/** multiply int_256 with unsigned type Byte. **/
    llumul_ub           ,/** multiply unsigned uint_256 with unsigned type Byte. **/
    lldiv_ub            ,/** divide int_256 with unsigned type Byte. **/
    lludiv_ub           ,/** divide unsigned uint_256 with unsigned type Byte. **/
    llcmpl_ub           ,/** compare int_256 less than unsigned type Byte. **/
    llucmpl_ub          ,/** compare unsigned uint_256 less than unsigned type Byte. **/
    llcmpg_ub           ,/** compare int_256 greater than unsigned type Byte. **/
    llucmpg_ub          ,/** compare unsigned uint_256 greater than unsigned type Byte. **/
    llcmpe_ub           ,/** compare int_256 equal with unsigned type Byte. **/
    llucmpe_ub          ,/** compare unsigned uint_256 equal with unsigned type Byte. **/
    llcmple_ub          ,/** compare int_256 less than or equal to unsigned type Byte. **/
    llucmple_ub         ,/** compare unsigned uint_256 less than or equal to unsigned type Byte. **/
    llcmpge_ub          ,/** compare int_256 greater than or equal to unsigned type Byte. **/
    llucmpge_ub         ,/** compare unsigned uint_256 greater than or equal to unsigned type Byte. **/
    llcmpne_ub          ,/** compare int_256 not equal with unsigned type Byte. **/
    llucmpne_ub         ,/** compare unsigned uint_256 not equal with unsigned type Byte. **/
    llmod_s             ,/** modulo int_256 with type Short. **/
    llcast_us           ,/** cast int_256 to unsigned type Short. **/
    llucast_us          ,/** cast unsigned uint_256 to unsigned type Short. **/
    lladd_us            ,/** add int_256 with unsigned type Short. **/
    lluadd_us           ,/** add unsigned uint_256 with unsigned type Short. **/
    llsub_us            ,/** subtract int_256 with unsigned type Short. **/
    llusub_us           ,/** subtract unsigned uint_256 with unsigned type Short. **/
    llmul_us            ,/** multiply int_256 with unsigned type Short. **/
    llumul_us           ,/** multiply unsigned uint_256 with unsigned type Short. **/
    lldiv_us            ,/** divide int_256 with unsigned type Short. **/
    lludiv_us           ,/** divide unsigned uint_256 with unsigned type Short. **/
    llcmpl_us           ,/** compare int_256 less than unsigned type Short. **/
    llucmpl_us          ,/** compare unsigned uint_256 less than unsigned type Short. **/
    llcmpg_us           ,/** compare int_256 greater than unsigned type Short. **/
    llucmpg_us          ,/** compare unsigned uint_256 greater than unsigned type Short. **/
    llcmpe_us           ,/** compare int_256 equal with unsigned type Short. **/
    llucmpe_us          ,/** compare unsigned uint_256 equal with unsigned type Short. **/
    llcmple_us          ,/** compare int_256 less than or equal to unsigned type Short. **/
    llucmple_us         ,/** compare unsigned uint_256 less than or equal to unsigned type Short. **/
    llcmpge_us          ,/** compare int_256 greater than or equal to unsigned type Short. **/
    llucmpge_us         ,/** compare unsigned uint_256 greater than or equal to unsigned type Short. **/
    llcmpne_us          ,/** compare int_256 not equal with unsigned type Short. **/
    llucmpne_us         ,/** compare unsigned uint_256 not equal with unsigned type Short. **/
    llmod_i             ,/** modulo int_256 with type Int. **/
    llcast_ui           ,/** cast int_256 to unsigned type Int. **/
    llucast_ui          ,/** cast unsigned uint_256 to unsigned type Int. **/
    lladd_ui            ,/** add int_256 with unsigned type Int. **/
    lluadd_ui           ,/** add unsigned uint_256 with unsigned type Int. **/
    llsub_ui            ,/** subtract int_256 with unsigned type Int. **/
    llusub_ui           ,/** subtract unsigned uint_256 with unsigned type Int. **/
    llmul_ui            ,/** multiply int_256 with unsigned type Int. **/
    llumul_ui           ,/** multiply unsigned uint_256 with unsigned type Int. **/
    lldiv_ui            ,/** divide int_256 with unsigned type Int. **/
    lludiv_ui           ,/** divide unsigned uint_256 with unsigned type Int. **/
    llcmpl_ui           ,/** compare int_256 less than unsigned type Int. **/
    llucmpl_ui          ,/** compare unsigned uint_256 less than unsigned type Int. **/
    llcmpg_ui           ,/** compare int_256 greater than unsigned type Int. **/
    llucmpg_ui          ,/** compare unsigned uint_256 greater than unsigned type Int. **/
    llcmpe_ui           ,/** compare int_256 equal with unsigned type Int. **/
    llucmpe_ui          ,/** compare unsigned uint_256 equal with unsigned type Int. **/
    llcmple_ui          ,/** compare int_256 less than or equal to unsigned type Int. **/
    llucmple_ui         ,/** compare unsigned uint_256 less than or equal to unsigned type Int. **/
    llcmpge_ui          ,/** compare int_256 greater than or equal to unsigned type Int. **/
    llucmpge_ui         ,/** compare unsigned uint_256 greater than or equal to unsigned type Int. **/
    llcmpne_ui          ,/** compare int_256 not equal with unsigned type Int. **/
    llucmpne_ui         ,/** compare unsigned uint_256 not equal with unsigned type Int. **/
    llmod_l             ,/** modulo int_256 with type Long. **/
    llcast_ul           ,/** cast int_256 to unsigned type Long. **/
    llucast_ul          ,/** cast unsigned uint_256 to unsigned type Long. **/
    lladd_ul            ,/** add int_256 with unsigned type Long. **/
    lluadd_ul           ,/** add unsigned uint_256 with unsigned type Long. **/
    llsub_ul            ,/** subtract int_256 with unsigned type Long. **/
    llusub_ul           ,/** subtract unsigned uint_256 with unsigned type Long. **/
    llmul_ul            ,/** multiply int_256 with unsigned type Long. **/
    llumul_ul           ,/** multiply unsigned uint_256 with unsigned type Long. **/
    lldiv_ul            ,/** divide int_256 with unsigned type Long. **/
    lludiv_ul           ,/** divide unsigned uint_256 with unsigned type Long. **/
    llcmpl_ul           ,/** compare int_256 less than unsigned type Long. **/
    llucmpl_ul          ,/** compare unsigned uint_256 less than unsigned type Long. **/
    llcmpg_ul           ,/** compare int_256 greater than unsigned type Long. **/
    llucmpg_ul          ,/** compare unsigned uint_256 greater than unsigned type Long. **/
    llcmpe_ul           ,/** compare int_256 equal with unsigned type Long. **/
    llucmpe_ul          ,/** compare unsigned uint_256 equal with unsigned type Long. **/
    llcmple_ul          ,/** compare int_256 less than or equal to unsigned type Long. **/
    llucmple_ul         ,/** compare unsigned uint_256 less than or equal to unsigned type Long. **/
    llcmpge_ul          ,/** compare int_256 greater than or equal to unsigned type Long. **/
    llucmpge_ul         ,/** compare unsigned uint_256 greater than or equal to unsigned type Long. **/
    llcmpne_ul          ,/** compare int_256 not equal with unsigned type Long. **/
    llucmpne_ul         ,/** compare unsigned uint_256 not equal with unsigned type Long. **/
    llmod_li            ,/** modulo int_256 with type LongInt. **/
    llcast_uli          ,/** cast int_256 to unsigned type LongInt. **/
    llucast_uli         ,/** cast unsigned uint_256 to unsigned type LongInt. **/
    lladd_uli           ,/** add int_256 with unsigned type LongInt. **/
    lluadd_uli          ,/** add unsigned uint_256 with unsigned type LongInt. **/
    llsub_uli           ,/** subtract int_256 with unsigned type LongInt. **/
    llusub_uli          ,/** subtract unsigned uint_256 with unsigned type LongInt. **/
    llmul_uli           ,/** multiply int_256 with unsigned type LongInt. **/
    llumul_uli          ,/** multiply unsigned uint_256 with unsigned type LongInt. **/
    lldiv_uli           ,/** divide int_256 with unsigned type LongInt. **/
    lludiv_uli          ,/** divide unsigned uint_256 with unsigned type LongInt. **/
    llcmpl_uli          ,/** compare int_256 less than unsigned type LongInt. **/
    llucmpl_uli         ,/** compare unsigned uint_256 less than unsigned type LongInt. **/
    llcmpg_uli          ,/** compare int_256 greater than unsigned type LongInt. **/
    llucmpg_uli         ,/** compare unsigned uint_256 greater than unsigned type LongInt. **/
    llcmpe_uli          ,/** compare int_256 equal with unsigned type LongInt. **/
    llucmpe_uli         ,/** compare unsigned uint_256 equal with unsigned type LongInt. **/
    llcmple_uli         ,/** compare int_256 less than or equal to unsigned type LongInt. **/
    llucmple_uli        ,/** compare unsigned uint_256 less than or equal to unsigned type LongInt. **/
    llcmpge_uli         ,/** compare int_256 greater than or equal to unsigned type LongInt. **/
    llucmpge_uli        ,/** compare unsigned uint_256 greater than or equal to unsigned type LongInt. **/
    llcmpne_uli         ,/** compare int_256 not equal with unsigned type LongInt. **/
    llucmpne_uli        ,/** compare unsigned uint_256 not equal with unsigned type LongInt. **/
    llmod_ll            ,/** modulo int_256 with type LongLong. **/
    llcast_ull          ,/** cast int_256 to unsigned type LongLong. **/
    llucast_ull         ,/** cast unsigned uint_256 to unsigned type LongLong. **/
    lladd_ull           ,/** add int_256 with unsigned type LongLong. **/
    lluadd_ull          ,/** add unsigned uint_256 with unsigned type LongLong. **/
    llsub_ull           ,/** subtract int_256 with unsigned type LongLong. **/
    llusub_ull          ,/** subtract unsigned uint_256 with unsigned type LongLong. **/
    llmul_ull           ,/** multiply int_256 with unsigned type LongLong. **/
    llumul_ull          ,/** multiply unsigned uint_256 with unsigned type LongLong. **/
    lldiv_ull           ,/** divide int_256 with unsigned type LongLong. **/
    lludiv_ull          ,/** divide unsigned uint_256 with unsigned type LongLong. **/
    llcmpl_ull          ,/** compare int_256 less than unsigned type LongLong. **/
    llucmpl_ull         ,/** compare unsigned uint_256 less than unsigned type LongLong. **/
    llcmpg_ull          ,/** compare int_256 greater than unsigned type LongLong. **/
    llucmpg_ull         ,/** compare unsigned uint_256 greater than unsigned type LongLong. **/
    llcmpe_ull          ,/** compare int_256 equal with unsigned type LongLong. **/
    llucmpe_ull         ,/** compare unsigned uint_256 equal with unsigned type LongLong. **/
    llcmple_ull         ,/** compare int_256 less than or equal to unsigned type LongLong. **/
    llucmple_ull        ,/** compare unsigned uint_256 less than or equal to unsigned type LongLong. **/
    llcmpge_ull         ,/** compare int_256 greater than or equal to unsigned type LongLong. **/
    llucmpge_ull        ,/** compare unsigned uint_256 greater than or equal to unsigned type LongLong. **/
    llcmpne_ull         ,/** compare int_256 not equal with unsigned type LongLong. **/
    llucmpne_ull        ,/** compare unsigned uint_256 not equal with unsigned type LongLong. **/
    lland_b             ,/** bitwise and int_256 with type Byte. **/
    llor_b              ,/** bitwise or int_256 with type Byte. **/
    llxor_b             ,/** bitwise xor int_256 with type Byte. **/
    llshftr_b           ,/** shift right int_256 with type Byte. **/
    llshftl_b           ,/** shift left xor int_256 with type Byte. **/
    lland_s             ,/** bitwise and int_256 with type Short. **/
    llor_s              ,/** bitwise or int_256 with type Short. **/
    llxor_s             ,/** bitwise xor int_256 with type Short. **/
    llshftr_s           ,/** shift right int_256 with type Short. **/
    llshftl_s           ,/** shift left xor int_256 with type Short. **/
    lland_i             ,/** bitwise and int_256 with type Int. **/
    llor_i              ,/** bitwise or int_256 with type Int. **/
    llxor_i             ,/** bitwise xor int_256 with type Int. **/
    llshftr_i           ,/** shift right int_256 with type Int. **/
    llshftl_i           ,/** shift left xor int_256 with type Int. **/
    lland_l             ,/** bitwise and int_256 with type Long. **/
    llor_l              ,/** bitwise or int_256 with type Long. **/
    llxor_l             ,/** bitwise xor int_256 with type Long. **/
    llshftr_l           ,/** shift right int_256 with type Long. **/
    llshftl_l           ,/** shift left xor int_256 with type Long. **/
    lland_li            ,/** bitwise and int_256 with type LongInt. **/
    llor_li             ,/** bitwise or int_256 with type LongInt. **/
    llxor_li            ,/** bitwise xor int_256 with type LongInt. **/
    llshftr_li          ,/** shift right int_256 with type LongInt. **/
    llshftl_li          ,/** shift left xor int_256 with type LongInt. **/
    lland_ll            ,/** bitwise and int_256 with type LongLong. **/
    llor_ll             ,/** bitwise or int_256 with type LongLong. **/
    llxor_ll            ,/** bitwise xor int_256 with type LongLong. **/
    llshftr_ll          ,/** shift right int_256 with type LongLong. **/
    llshftl_ll          ,/** shift left xor int_256 with type LongLong. **/
    lldup               ,/** duplicate a int_256 on the stack. **/
    lldup2              ,/** duplicate a int_256 2 times on the stack. **/
    lldup3              ,/** duplicate a int_256 3 times on the stack. **/
    lldup4              ,/** duplicate a int_256 4 times on the stack. **/
    lldup5              ,/** duplicate a int_256 5 times on the stack. **/
    llset               ,/** set a int_256 from stack into a field on base pointer. **/
    llget               ,/** get a int_256 from a field on base pointer to stack. **/
    llvset              ,/** set a int_256 from value into a field on base pointer. **/
    llsget              ,/** get a int_256 from a field on base pointer to stack using address from stack. **/
    llsset              ,/** set a int_256 from stack into a field on base pointer using address from stack. **/
    llsetl              ,/** set a int_256 from local variable into a field on base pointer. **/
    llinc_1             ,/** increment int_256 by 1 on stack. **/
    llinc_2             ,/** increment int_256 by 2 on stack. **/
    llstinc_1           ,/** increment int_256 by 1 on stack. **/
    llstinc_2           ,/** increment int_256 by 2 on stack. **/
    llreturn            ,/** return a int_256 into the main stack. **/
    llmainst            ,/** store a int_256 from main stack in a local variable.. **/
    llmainst_0          ,/** store a int_256 from main stack in local variable 0. **/
    llmainst_1          ,/** store a int_256 from main stack in local variable 1. **/
    llmainst_2          ,/** store a int_256 from main stack in local variable 2. **/
    llmainst_3          ,/** store a int_256 from main stack in local variable 3. **/
    llprint             ,/** print a int_256 from stack. **/
    lluprint            ,/** print a unsigned uint_256 from stack. **/
    fprintba            ,/** print a byte array. **/
    fconst              ,/** push a const flt_32 into the stack. **/
    fconst_0            ,/** push a const flt_32 into the stack (value = 0). **/
    fload               ,/** load a flt_32 into the stack from local variable. **/
    fload_0             ,/** load a flt_32 into the stack from local variable 0. **/
    fload_1             ,/** load a flt_32 into the stack from local variable 1. **/
    fload_2             ,/** load a flt_32 into the stack from local variable 2. **/
    fload_3             ,/** load a flt_32 into the stack from local variable 3. **/
    fload_4             ,/** load a flt_32 into the stack from local variable 4. **/
    fstore              ,/** store a flt_32 from stack into local variable. **/
    fstore_0            ,/** store a flt_32 from stack into local variable 0. **/
    fstore_1            ,/** store a flt_32 from stack into local variable 1. **/
    fstore_2            ,/** store a flt_32 from stack into local variable 2. **/
    fstore_3            ,/** store a flt_32 from stack into local variable 3. **/
    fstore_4            ,/** store a flt_32 from stack into local variable 4. **/
    fdup                ,/** duplicate a flt_32 on the stack. **/
    fdup2               ,/** duplicate a flt_32 2 times on the stack. **/
    fdup3               ,/** duplicate a flt_32 3 times on the stack. **/
    fdup4               ,/** duplicate a flt_32 4 times on the stack. **/
    fdup5               ,/** duplicate a flt_32 5 times on the stack. **/
    fset                ,/** set a flt_32 from stack into a field on base pointer. **/
    fget                ,/** get a flt_32 from a field on base pointer to stack. **/
    fvset               ,/** set a flt_32 from value into a field on base pointer. **/
    fsget               ,/** get a flt_32 from a field on base pointer to stack using address from stack. **/
    fsset               ,/** set a flt_32 from stack into a field on base pointer using address from stack. **/
    fsetl               ,/** set a flt_32 from local variable into a field on base pointer. **/
    finc_1              ,/** increment flt_32 by 1 on stack. **/
    finc_2              ,/** increment flt_32 by 2 on stack. **/
    fstinc_1            ,/** increment flt_32 by 1 on stack. **/
    fstinc_2            ,/** increment flt_32 by 2 on stack. **/
    freturn             ,/** return a flt_32 into the main stack. **/
    fmainst             ,/** store a flt_32 from main stack in a local variable.. **/
    fmainst_0           ,/** store a flt_32 from main stack in local variable 0. **/
    fmainst_1           ,/** store a flt_32 from main stack in local variable 1. **/
    fmainst_2           ,/** store a flt_32 from main stack in local variable 2. **/
    fmainst_3           ,/** store a flt_32 from main stack in local variable 3. **/
    dprintba            ,/** print a byte array. **/
    dconst              ,/** push a const flt_64 into the stack. **/
    dconst_0            ,/** push a const flt_64 into the stack (value = 0). **/
    dload               ,/** load a flt_64 into the stack from local variable. **/
    dload_0             ,/** load a flt_64 into the stack from local variable 0. **/
    dload_1             ,/** load a flt_64 into the stack from local variable 1. **/
    dload_2             ,/** load a flt_64 into the stack from local variable 2. **/
    dload_3             ,/** load a flt_64 into the stack from local variable 3. **/
    dload_4             ,/** load a flt_64 into the stack from local variable 4. **/
    dstore              ,/** store a flt_64 from stack into local variable. **/
    dstore_0            ,/** store a flt_64 from stack into local variable 0. **/
    dstore_1            ,/** store a flt_64 from stack into local variable 1. **/
    dstore_2            ,/** store a flt_64 from stack into local variable 2. **/
    dstore_3            ,/** store a flt_64 from stack into local variable 3. **/
    dstore_4            ,/** store a flt_64 from stack into local variable 4. **/
    ddup                ,/** duplicate a flt_64 on the stack. **/
    ddup2               ,/** duplicate a flt_64 2 times on the stack. **/
    ddup3               ,/** duplicate a flt_64 3 times on the stack. **/
    ddup4               ,/** duplicate a flt_64 4 times on the stack. **/
    ddup5               ,/** duplicate a flt_64 5 times on the stack. **/
    dset                ,/** set a flt_64 from stack into a field on base pointer. **/
    dget                ,/** get a flt_64 from a field on base pointer to stack. **/
    dvset               ,/** set a flt_64 from value into a field on base pointer. **/
    dsget               ,/** get a flt_64 from a field on base pointer to stack using address from stack. **/
    dsset               ,/** set a flt_64 from stack into a field on base pointer using address from stack. **/
    dsetl               ,/** set a flt_64 from local variable into a field on base pointer. **/
    dinc_1              ,/** increment flt_64 by 1 on stack. **/
    dinc_2              ,/** increment flt_64 by 2 on stack. **/
    dstinc_1            ,/** increment flt_64 by 1 on stack. **/
    dstinc_2            ,/** increment flt_64 by 2 on stack. **/
    dreturn             ,/** return a flt_64 into the main stack. **/
    dmainst             ,/** store a flt_64 from main stack in a local variable.. **/
    dmainst_0           ,/** store a flt_64 from main stack in local variable 0. **/
    dmainst_1           ,/** store a flt_64 from main stack in local variable 1. **/
    dmainst_2           ,/** store a flt_64 from main stack in local variable 2. **/
    dmainst_3           ,/** store a flt_64 from main stack in local variable 3. **/
    dfprintba           ,/** print a byte array. **/
    dfconst             ,/** push a const flt_128 into the stack. **/
    dfconst_0           ,/** push a const flt_128 into the stack (value = 0). **/
    dfload              ,/** load a flt_128 into the stack from local variable. **/
    dfload_0            ,/** load a flt_128 into the stack from local variable 0. **/
    dfload_1            ,/** load a flt_128 into the stack from local variable 1. **/
    dfload_2            ,/** load a flt_128 into the stack from local variable 2. **/
    dfload_3            ,/** load a flt_128 into the stack from local variable 3. **/
    dfload_4            ,/** load a flt_128 into the stack from local variable 4. **/
    dfstore             ,/** store a flt_128 from stack into local variable. **/
    dfstore_0           ,/** store a flt_128 from stack into local variable 0. **/
    dfstore_1           ,/** store a flt_128 from stack into local variable 1. **/
    dfstore_2           ,/** store a flt_128 from stack into local variable 2. **/
    dfstore_3           ,/** store a flt_128 from stack into local variable 3. **/
    dfstore_4           ,/** store a flt_128 from stack into local variable 4. **/
    dfdup               ,/** duplicate a flt_128 on the stack. **/
    dfdup2              ,/** duplicate a flt_128 2 times on the stack. **/
    dfdup3              ,/** duplicate a flt_128 3 times on the stack. **/
    dfdup4              ,/** duplicate a flt_128 4 times on the stack. **/
    dfdup5              ,/** duplicate a flt_128 5 times on the stack. **/
    dfset               ,/** set a flt_128 from stack into a field on base pointer. **/
    dfget               ,/** get a flt_128 from a field on base pointer to stack. **/
    dfvset              ,/** set a flt_128 from value into a field on base pointer. **/
    dfsget              ,/** get a flt_128 from a field on base pointer to stack using address from stack. **/
    dfsset              ,/** set a flt_128 from stack into a field on base pointer using address from stack. **/
    dfsetl              ,/** set a flt_128 from local variable into a field on base pointer. **/
    dfinc_1             ,/** increment flt_128 by 1 on stack. **/
    dfinc_2             ,/** increment flt_128 by 2 on stack. **/
    dfstinc_1           ,/** increment flt_128 by 1 on stack. **/
    dfstinc_2           ,/** increment flt_128 by 2 on stack. **/
    dfreturn            ,/** return a flt_128 into the main stack. **/
    dfmainst            ,/** store a flt_128 from main stack in a local variable.. **/
    dfmainst_0          ,/** store a flt_128 from main stack in local variable 0. **/
    dfmainst_1          ,/** store a flt_128 from main stack in local variable 1. **/
    dfmainst_2          ,/** store a flt_128 from main stack in local variable 2. **/
    dfmainst_3          ,/** store a flt_128 from main stack in local variable 3. **/
    ddprintba           ,/** print a byte array. **/
    ddconst             ,/** push a const flt_256 into the stack. **/
    ddconst_0           ,/** push a const flt_256 into the stack (value = 0). **/
    ddload              ,/** load a flt_256 into the stack from local variable. **/
    ddload_0            ,/** load a flt_256 into the stack from local variable 0. **/
    ddload_1            ,/** load a flt_256 into the stack from local variable 1. **/
    ddload_2            ,/** load a flt_256 into the stack from local variable 2. **/
    ddload_3            ,/** load a flt_256 into the stack from local variable 3. **/
    ddload_4            ,/** load a flt_256 into the stack from local variable 4. **/
    ddstore             ,/** store a flt_256 from stack into local variable. **/
    ddstore_0           ,/** store a flt_256 from stack into local variable 0. **/
    ddstore_1           ,/** store a flt_256 from stack into local variable 1. **/
    ddstore_2           ,/** store a flt_256 from stack into local variable 2. **/
    ddstore_3           ,/** store a flt_256 from stack into local variable 3. **/
    ddstore_4           ,/** store a flt_256 from stack into local variable 4. **/
    dddup               ,/** duplicate a flt_256 on the stack. **/
    dddup2              ,/** duplicate a flt_256 2 times on the stack. **/
    dddup3              ,/** duplicate a flt_256 3 times on the stack. **/
    dddup4              ,/** duplicate a flt_256 4 times on the stack. **/
    dddup5              ,/** duplicate a flt_256 5 times on the stack. **/
    ddset               ,/** set a flt_256 from stack into a field on base pointer. **/
    ddget               ,/** get a flt_256 from a field on base pointer to stack. **/
    ddvset              ,/** set a flt_256 from value into a field on base pointer. **/
    ddsget              ,/** get a flt_256 from a field on base pointer to stack using address from stack. **/
    ddsset              ,/** set a flt_256 from stack into a field on base pointer using address from stack. **/
    ddsetl              ,/** set a flt_256 from local variable into a field on base pointer. **/
    ddinc_1             ,/** increment flt_256 by 1 on stack. **/
    ddinc_2             ,/** increment flt_256 by 2 on stack. **/
    ddstinc_1           ,/** increment flt_256 by 1 on stack. **/
    ddstinc_2           ,/** increment flt_256 by 2 on stack. **/
    ddreturn            ,/** return a flt_256 into the main stack. **/
    ddmainst            ,/** store a flt_256 from main stack in a local variable.. **/
    ddmainst_0          ,/** store a flt_256 from main stack in local variable 0. **/
    ddmainst_1          ,/** store a flt_256 from main stack in local variable 1. **/
    ddmainst_2          ,/** store a flt_256 from main stack in local variable 2. **/
    ddmainst_3          ,/** store a flt_256 from main stack in local variable 3. **/
    aprintba            ,/** print a byte array. **/
    aconst              ,/** push a const pointer into the stack. **/
    aconst_0            ,/** push a const pointer into the stack (value = 0). **/
    aload               ,/** load a pointer into the stack from local variable. **/
    aload_0             ,/** load a pointer into the stack from local variable 0. **/
    aload_1             ,/** load a pointer into the stack from local variable 1. **/
    aload_2             ,/** load a pointer into the stack from local variable 2. **/
    aload_3             ,/** load a pointer into the stack from local variable 3. **/
    aload_4             ,/** load a pointer into the stack from local variable 4. **/
    astore              ,/** store a pointer from stack into local variable. **/
    astore_0            ,/** store a pointer from stack into local variable 0. **/
    astore_1            ,/** store a pointer from stack into local variable 1. **/
    astore_2            ,/** store a pointer from stack into local variable 2. **/
    astore_3            ,/** store a pointer from stack into local variable 3. **/
    astore_4            ,/** store a pointer from stack into local variable 4. **/
    adup                ,/** duplicate a pointer on the stack. **/
    adup2               ,/** duplicate a pointer 2 times on the stack. **/
    adup3               ,/** duplicate a pointer 3 times on the stack. **/
    adup4               ,/** duplicate a pointer 4 times on the stack. **/
    adup5               ,/** duplicate a pointer 5 times on the stack. **/
    aset                ,/** set a pointer from stack into a field on base pointer. **/
    aget                ,/** get a pointer from a field on base pointer to stack. **/
    avset               ,/** set a pointer from value into a field on base pointer. **/
    asget               ,/** get a pointer from a field on base pointer to stack using address from stack. **/
    asset               ,/** set a pointer from stack into a field on base pointer using address from stack. **/
    asetl               ,/** set a pointer from local variable into a field on base pointer. **/
    ainc_1              ,/** increment pointer by 1 on stack. **/
    ainc_2              ,/** increment pointer by 2 on stack. **/
    astinc_1            ,/** increment pointer by 1 on stack. **/
    astinc_2            ,/** increment pointer by 2 on stack. **/
    areturn             ,/** return a pointer into the main stack. **/
    amainst             ,/** store a pointer from main stack in a local variable.. **/
    amainst_0           ,/** store a pointer from main stack in local variable 0. **/
    amainst_1           ,/** store a pointer from main stack in local variable 1. **/
    amainst_2           ,/** store a pointer from main stack in local variable 2. **/
    amainst_3           ,/** store a pointer from main stack in local variable 3. **/
};

#endif //MVM_OPCODES_H