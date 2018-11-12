//
// Created by Riverssen on 10.11.18.
//

#include "executorfuncs.h"
#include "executor.h"

implptr_t impl::impl_funcs;

void funcs::func_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * (This opcode won't be interpreted) it creates a marker for an OP_STACK (must end with a return_op of some kind).
 */

	
	

}
void funcs::hash_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * perform a hash on pointer data.
 */

	
	

}
void funcs::timens_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a (uint_64) current time in nanoseconds.
 */

	stack.pushUnsignedLong(static_cast<uint_64> (MvM::gtimens()));
	

}
void funcs::timems_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a (uint_64) current time in milliseconds.
 */

	stack.pushUnsignedLong(static_cast<uint_64> (MvM::gtimems()));
	

}
void funcs::strconst_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a constant string.
 */

	{ uint_16 size_ = stack.popUnsignedShort(); pointer str = static_cast<pointer> (calloc(size_ * 2 + 2, size_ * 2 + 2)); MvM::accessMemoryAndSetUnsignedShort(str, 0, size_); stack.pushPointer(str);}
	

}
void funcs::strload_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * load a string.
 */

	stack.pushUnsignedLong(lvt[ops.getUnsignedShort()].UnsignedLong);
	

}
void funcs::strstore_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a string.
 */

	lvt[ops.getUnsignedShort()] = MvM::lve_Long(stack.popUnsignedLong());
	

}
void funcs::strsizeof_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a string.
 */

	stack.pushUnsignedLong(static_cast<uint_64> (MvM::accessMemoryAndGetUnsignedShort(stack.popPointer(), 0)));
	

}
void funcs::strcast_a_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * cast a string to a pointer.
 */

	{ pointer s = stack.popPointer(); uint_16 l = MvM::accessMemoryAndGetUnsignedShort(s, 0); pointer b = static_cast<pointer> (calloc(l * 2, l * 2)); memcpy(b, s + 2, l * 2); stack.pushPointer(b); }
	

}
void funcs::strcast_ba_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * cast a string to a byte array.
 */

	{ pointer s = stack.popPointer(); uint_16 l = MvM::accessMemoryAndGetUnsignedShort(s, 0); pointer b = static_cast<pointer> (calloc(l * 2 + 6, l * 2 + 6)); memcpy(b + 6, s, l * 2); MvM::accessMemoryAndSetUnsignedLong(b, 0, static_cast<uint_64> (l)); stack.pushPointer(b); }
	

}
void funcs::strprint_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * print a string.
 */

	MvM::printString(stack.popPointer());
	

}
void funcs::strreturn_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * return a string from scope.
 */

	stack_main.pushUnsignedLong(stack.popUnsignedLong()); return;
	

}
void funcs::mark_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * mark a specific location.
 */

	CHECK_POINTS[ops.getUnsignedShort()] = ops.address + 2;
	

}
void funcs::jump_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * jump to a specific location.
 */

	ops.address = ops.getUnsignedLong();
	

}
void funcs::jumptomark_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * jump to a specific marked location.
 */

	ops.address = CHECK_POINTS[ops.getUnsignedShort()];
	

}
void funcs::newline_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * print a \n character into the console.
 */

	std::cout<<std::endl;
	

}
void funcs::ret_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * return from this scope.
 */

	ops.address = ops.length; return;
	

}
void funcs::invoke_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * invoke a method.
 */

	MvM::execute(globalTable, nativeTable, globalPointer, globalPointer, stack, globalTable[ops.getUnsignedLong()]);
	

}
void funcs::invokedynamic_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * dynamically invoke a method using function pointers.
 */

	MvM::execute(globalTable, nativeTable, globalPointer, globalPointer, stack, globalTable[stack.popUnsignedLong()]);
	

}
void funcs::invokespecial_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * invoke a native method using function pointers.
 */

	nativeTable[stack.popUnsignedLong()]->execute(globalTable, nativeTable, globalPointer, globalPointer, stack, globalTable[stack.popUnsignedLong()]);
	

}
void funcs::if_t_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * if true.
 */

	{ uint_32 jump = ops.getUnsignedInt(); if (stack.popByte() == 0) ops.address += jump; }
	

}
void funcs::if_f_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * if not true.
 */

	{ uint_32 jump = ops.getUnsignedInt(); if (stack.popByte() > 0) ops.address += jump; }
	

}
void funcs::invert_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * invert a boolean.
 */

	stack.pushByte(!((bool) stack.popByte()));
	

}
void funcs::amemcpy_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * copy memory to destination from source.
 */

	memcpy(stack.popPointer(), stack.popPointer(), stack.popUnsignedLong());
	

}
void funcs::bspmemcpy_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * copy memory to destination from base pointer.
 */

	memcpy(stack.popPointer(), base, stack.popUnsignedLong());
	

}
void funcs::amemcpybsp_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * copy memory to pointer from source.
 */

	memcpy(base, stack.popPointer(), stack.popUnsignedLong());
	

}
void funcs::amalloc_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const pointer to the stack.
 */

	stack.pushPointer(static_cast<pointer> (malloc(stack.popUnsignedLong())));
	

}
void funcs::acalloc_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const pointer to the stack.
 */

	stack.pushPointer(static_cast<pointer> (calloc(stack.popUnsignedLong(), stack.popUnsignedLong())));
	

}
void funcs::amallocs_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const pointer to the stack from size_int16_t.
 */

	stack.pushPointer(static_cast<pointer> (malloc(stack.popUnsignedShort())));
	

}
void funcs::acallocs_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const pointer to the stack from size_int16_t.
 */

	stack.pushPointer(static_cast<pointer> (calloc(stack.popUnsignedShort(), stack.popUnsignedShort())));
	

}
void funcs::adelete_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * delete a pointer.
 */

	delete (stack.popPointer());
	

}
void funcs::baconst_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a byte array.
 */

	{ uint_64 length = stack.popUnsignedLong(); pointer p = static_cast<pointer> (calloc(length, length)); stack.pushPointer(p); MvM::accessMemoryAndSetUnsignedLong(p, 0, length); }
	

}
void funcs::baconsts_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a byte array using size_int16_t
 */

	{ uint_64 length = static_cast<uint_64> (stack.popUnsignedShort()); pointer p = static_cast<pointer> (calloc(length, length)); stack.pushPointer(p); MvM::accessMemoryAndSetUnsignedLong(p, 0, length); }
	

}
void funcs::baconsti_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a byte array using size_int32_t
 */

	{ uint_64 length = static_cast<uint_64> (stack.popUnsignedInt()); pointer p = static_cast<pointer> (calloc(length, length)); stack.pushPointer(p); MvM::accessMemoryAndSetUnsignedLong(p, 0, length); }
	

}
void funcs::bacast_a_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * cast a byte array into a pointer
 */

	{ stack.pushPointer(stack.popPointer() + 8); }
	

}
void funcs::basizeof_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push the size of a byte array to stack
 */

	{ stack.pushUnsignedLong(static_cast<uint_64> (MvM::accessMemoryAndGetLong(stack.popPointer(), 0))); }
	

}
void funcs::printba_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * print a byte array.
 */

	{ pointer bytearray = stack.popPointer(); uint_64 bytearraysize   = static_cast<uint_64> (MvM::accessMemoryAndGetLong(bytearray, 0)); std::string data = "["; for (uint_64 i = 0; i < bytearraysize; i ++) data += std::to_string(MvM::accessMemoryAndGetByte(bytearray + 8, i)) + ((i < bytearraysize - 1) ? ", " : "]"); MvM::log(data); }
	

}
void funcs::cmpl_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * compare a long less than long.
 */

	{
	int_64 b = stack.popLong();
	int_64 a = stack.popLong();
	stack.pushByte((a < b) ? 1 : 0);
	}
	

}
void funcs::cmpg_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * compare a long greater than long.
 */

	{
	int_64 b = stack.popLong();
	int_64 a = stack.popLong();
	stack.pushByte((a > b) ? 1 : 0);
	}
	

}
void funcs::cmpe_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * compare a long equal with long.
 */

	{
	int_64 b = stack.popLong();
	int_64 a = stack.popLong();
	stack.pushByte((a == b) ? 1 : 0);
	}
	

}
void funcs::cmple_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * compare a long less than or equal to long.
 */

	{
	int_64 b = stack.popLong();
	int_64 a = stack.popLong();
	stack.pushByte((a <= b) ? 1 : 0);
	}
	

}
void funcs::cmpge_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * compare a long greater than or equal to long.
 */

	{
	int_64 b = stack.popLong();
	int_64 a = stack.popLong();
	stack.pushByte((a >= b) ? 1 : 0);
	}
	

}
void funcs::cmpne_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * compare a long not equal with long.
 */

	{
	int_64 b = stack.popLong();
	int_64 a = stack.popLong();
	stack.pushByte((a != b) ? 1 : 0);
	}
	

}
void funcs::ucmp_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * compare a ulong int with another ulong.
 */

	{
	uint_64 b = stack.popUnsignedLong();
	uint_64 a = stack.popUnsignedLong();
	stack.pushByte((a < b) ? -1 : ((a > b) ? 1 : 0));
	}
	

}
void funcs::cmpu_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * compare a long int with a ulong.
 */

	{
	uint_64 b = stack.popUnsignedLong();
	uint_64 a = stack.popLong();
	stack.pushByte((a < b) ? -1 : ((a > b) ? 1 : 0));
	}
	

}
void funcs::cmpll_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * compare a 256bit int with another 256bit int.
 */

	{
	int_256 b = stack.popLongLong();
	int_256 a = stack.popLongLong();
	stack.pushByte((a < b) ? -1 : ((a > b) ? 1 : 0));
	}
	

}
void funcs::ucmpll_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * compare a u256bit int with another u256bit int.
 */

	{
	uint_256 b = stack.popUnsignedLongLong();
	uint_256 a = stack.popUnsignedLongLong();
	stack.pushByte((a < b) ? -1 : ((a > b) ? 1 : 0));
	}
	

}
void funcs::cmpull_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * compare a 256bit int with a u256bit int.
 */

	{
	uint_256 b = stack.popUnsignedLongLong();
	int_256 a = stack.popLongLong();
	stack.pushByte((a < b) ? -1 : ((a > b) ? 1 : 0));
	}
	

}
void funcs::dcmpl_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * compare a double less than double.
 */

	{
	flt_64 b = stack.popDouble();
	flt_64 a = stack.popDouble();
	stack.pushByte((a < b) ? 1 : 0);
	}
	

}
void funcs::dcmpg_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * compare a double greater than double.
 */

	{
	flt_64 b = stack.popDouble();
	flt_64 a = stack.popDouble();
	stack.pushByte((a > b) ? 1 : 0);
	}
	

}
void funcs::dcmpe_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * compare a double equal with double.
 */

	{
	flt_64 b = stack.popDouble();
	flt_64 a = stack.popDouble();
	stack.pushByte((a == b) ? 1 : 0);
	}
	

}
void funcs::dcmple_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * compare a double less than or equal to double.
 */

	{
	flt_64 b = stack.popDouble();
	flt_64 a = stack.popDouble();
	stack.pushByte((a <= b) ? 1 : 0);
	}
	

}
void funcs::dcmpge_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * compare a double greater than or equal to double.
 */

	{
	flt_64 b = stack.popDouble();
	flt_64 a = stack.popDouble();
	stack.pushByte((a >= b) ? 1 : 0);
	}
	

}
void funcs::dcmpne_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * compare a double not equal with double.
 */

	{
	flt_64 b = stack.popDouble();
	flt_64 a = stack.popDouble();
	stack.pushByte((a != b) ? 1 : 0);
	}
	

}
void funcs::mod_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * mod an int with an int.
 */

	{
	stack.pushLong(stack.popLong() % stack.popLong());
	}
	

}
void funcs::llmod_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * mod an int 256 with an int 256.
 */

	{
	stack.pushUnsignedLongLong(stack.popUnsignedLongLong() % stack.popUnsignedLongLong());
	}
	

}
void funcs::and__impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * bitwise and int with int.
 */

	{
	stack.pushUnsignedLong(stack.popUnsignedLong() & stack.popUnsignedLong());
	}
	

}
void funcs::or__impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * bitwise or int with int.
 */

	{
	stack.pushUnsignedLong(stack.popUnsignedLong() | stack.popUnsignedLong());
	}
	

}
void funcs::xor__impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * bitwise xor int with int.
 */

	{
	stack.pushUnsignedLong(stack.popUnsignedLong() ^ stack.popUnsignedLong());
	}
	

}
void funcs::not__impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * bitwise not int with int.
 */

	{
	stack.pushUnsignedLong(stack.popUnsignedLong() ^ stack.popUnsignedLong());
	}
	

}
void funcs::rshft__impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * right shift int with byte.
 */

	{
	stack.pushUnsignedLong(stack.popUnsignedLong() >> stack.popUnsignedByte());
	}
	

}
void funcs::lshft__impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * left shift int with byte.
 */

	{
	stack.pushUnsignedLong(stack.popUnsignedLong() << stack.popUnsignedByte());
	}
	

}
void funcs::dup_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * duplicate an element on the stack.
 */

	stack.pushUnsignedLong(stack.peekUnsignedLong());
	

}
void funcs::dup2_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * duplicate an element 2 times on the stack.
 */

	stack.pushUnsignedLong(stack.peekUnsignedLong());stack.pushUnsignedLong(stack.peekUnsignedLong());
	

}
void funcs::dup3_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * duplicate an element 3 times on the stack.
 */

	stack.pushUnsignedLong(stack.peekUnsignedLong());stack.pushUnsignedLong(stack.peekUnsignedLong());stack.pushUnsignedLong(stack.peekUnsignedLong());
	

}
void funcs::swap_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * swap the 2 topmost elements.
 */

	{ uint_64 a = stack.popUnsignedLong(); uint_64 b = stack.popUnsignedLong(); stack.pushUnsignedLong(a); stack.pushUnsignedLong(b); }
	

}
void funcs::pret_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * return the top element into the main stack.
 */

	ops.address = ops.length; stack_main.pushUnsignedLong(stack.popUnsignedLong()); return;
	

}
void funcs::pret2_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * return the top 2 elements (128bit) into the main stack.
 */

	ops.address = ops.length; stack_main.pushUnsignedLongInt(stack.popUnsignedLongInt()); return;
	

}
void funcs::pret4_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * return the top 4 elements (256bit) into the main stack.
 */

	ops.address = ops.length; stack_main.pushUnsignedLongLong(stack.popUnsignedLongLong()); return;
	

}
void funcs::bconst_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_8 into the stack.
 */

	stack.pushByte(ops.getByte());
	

}
void funcs::bconst_0_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_8 into the stack (value = 0).
 */

	stack.pushByte(0);
	

}
void funcs::bload_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * load a int_8 into the stack from local variable.
 */

	stack.pushByte(lvt[ops.getUnsignedShort()].Byte);
	

}
void funcs::bstore_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_8 from stack into local variable.
 */

	lvt[ops.getUnsignedShort()] = MvM::lve_Byte(stack.popByte());
	

}
void funcs::bset_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * set a int_8 from stack into a field on pointer.
 */

	MvM::accessMemoryAndSetByte(stack.popPointer(), stack.popUnsignedLong(), stack.popByte());
	

}
void funcs::bget_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * get a int_8 from a field on a pointer to stack.
 */

	stack.pushByte(MvM::accessMemoryAndGetByte(stack.popPointer(), stack.popUnsignedLong()));
	

}
void funcs::bmainst_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_8 from main stack in a local variable..
 */

	lvt[ops.getUnsignedShort()].Byte = stack_main.popByte();
	

}
void funcs::bprint_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * print a int_8 from stack.
 */

	MvM::log(std::to_string(stack.popByte()));
	

}
void funcs::buprint_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * print a unsigned uint_8 from stack.
 */
 
	MvM::log(std::to_string(stack.popUnsignedByte()));
	;
}
void funcs::sconst_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_16 into the stack.
 */

	stack.pushShort(ops.getShort());
	

}
void funcs::sconst_0_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_16 into the stack (value = 0).
 */

	stack.pushShort(0);
	

}
void funcs::sload_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * load a int_16 into the stack from local variable.
 */

	stack.pushShort(lvt[ops.getUnsignedShort()].Short);
	

}
void funcs::sstore_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_16 from stack into local variable.
 */

	lvt[ops.getUnsignedShort()] = MvM::lve_Short(stack.popShort());
	

}
void funcs::sset_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * set a int_16 from stack into a field on pointer.
 */

	MvM::accessMemoryAndSetShort(stack.popPointer(), stack.popUnsignedLong(), stack.popShort());
	

}
void funcs::sget_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * get a int_16 from a field on a pointer to stack.
 */

	stack.pushShort(MvM::accessMemoryAndGetShort(stack.popPointer(), stack.popUnsignedLong()));
	

}
void funcs::smainst_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_16 from main stack in a local variable..
 */

	lvt[ops.getUnsignedShort()].Short = stack_main.popShort();
	

}
void funcs::sprint_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * print a int_16 from stack.
 */

	MvM::log(std::to_string(stack.popShort()));
	

}
void funcs::suprint_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * print a unsigned uint_16 from stack.
 */
 
	MvM::log(std::to_string(stack.popUnsignedShort()));
	;
}
void funcs::iconst_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_32 into the stack.
 */

	stack.pushInt(ops.getInt());
	

}
void funcs::iconst_0_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_32 into the stack (value = 0).
 */

	stack.pushInt(0);
	

}
void funcs::iconst_1_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_32 into the stack (value = 1).
 */

	stack.pushInt(1);
	

}
void funcs::iconst_2_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_32 into the stack (value = 2).
 */

	stack.pushInt(2);
	

}
void funcs::iconst_3_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_32 into the stack (value = 3).
 */

	stack.pushInt(3);
	

}
void funcs::iconst_4_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_32 into the stack (value = 4).
 */

	stack.pushInt(4);
	

}
void funcs::iconst_5_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_32 into the stack (value = 5).
 */

	stack.pushInt(5);
	

}
void funcs::iconst_6_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_32 into the stack (value = 6).
 */

	stack.pushInt(6);
	

}
void funcs::iconst_9_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_32 into the stack (value = 9).
 */

	stack.pushInt(9);
	

}
void funcs::iconst_10_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_32 into the stack (value = 10).
 */

	stack.pushInt(10);
	

}
void funcs::iconst_11_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_32 into the stack (value = 11).
 */

	stack.pushInt(11);
	

}
void funcs::iconst_12_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_32 into the stack (value = 12).
 */

	stack.pushInt(12);
	

}
void funcs::iload_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * load a int_32 into the stack from local variable.
 */

	stack.pushInt(lvt[ops.getUnsignedShort()].Int);
	

}
void funcs::iload_0_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * load a int_32 into the stack from local variable 0.
 */

	stack.pushInt(lvt[0].Int);
	

}
void funcs::iload_1_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * load a int_32 into the stack from local variable 1.
 */

	stack.pushInt(lvt[1].Int);
	

}
void funcs::iload_2_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * load a int_32 into the stack from local variable 2.
 */

	stack.pushInt(lvt[2].Int);
	

}
void funcs::iload_3_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * load a int_32 into the stack from local variable 3.
 */

	stack.pushInt(lvt[3].Int);
	

}
void funcs::iload_4_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * load a int_32 into the stack from local variable 4.
 */

	stack.pushInt(lvt[4].Int);
	

}
void funcs::istore_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_32 from stack into local variable.
 */

	lvt[ops.getUnsignedShort()] = MvM::lve_Int(stack.popInt());
	

}
void funcs::istore_0_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_32 from stack into local variable 0.
 */

	lvt[0] = MvM::lve_Int(stack.popInt());
	

}
void funcs::istore_1_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_32 from stack into local variable 1.
 */

	lvt[1] = MvM::lve_Int(stack.popInt());
	

}
void funcs::istore_2_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_32 from stack into local variable 2.
 */

	lvt[2] = MvM::lve_Int(stack.popInt());
	

}
void funcs::istore_3_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_32 from stack into local variable 3.
 */

	lvt[3] = MvM::lve_Int(stack.popInt());
	

}
void funcs::istore_4_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_32 from stack into local variable 4.
 */

	lvt[4] = MvM::lve_Int(stack.popInt());
	

}
void funcs::iadd_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * add two Ints.
 */

	stack.pushInt(stack.popInt() + stack.popInt());
	

}
void funcs::iuadd_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * add two UnsignedUnsignedInts.
 */
 
	stack.pushUnsignedInt(stack.popUnsignedInt() + stack.popUnsignedInt());
	;
}
void funcs::isub_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * subtract two Ints.
 */

	stack.pushInt(stack.popInt() - stack.popInt());
	

}
void funcs::iusub_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * subtract two UnsignedUnsignedInts.
 */
 
	stack.pushUnsignedInt(stack.popUnsignedInt() - stack.popUnsignedInt());
	;
}
void funcs::imul_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * multiply two Ints.
 */

	stack.pushInt(stack.popInt() * stack.popInt());
	

}
void funcs::iumul_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * multiply two UnsignedUnsignedInts.
 */
 
	stack.pushUnsignedInt(stack.popUnsignedInt() * stack.popUnsignedInt());
	;
}
void funcs::idiv_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * divide two Ints.
 */

	stack.pushInt(stack.popInt() / stack.popInt());
	

}
void funcs::iudiv_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * divide two UnsignedUnsignedInts.
 */
 
	stack.pushUnsignedInt(stack.popUnsignedInt() / stack.popUnsignedInt());
	;
}
void funcs::iset_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * set a int_32 from stack into a field on pointer.
 */

	MvM::accessMemoryAndSetInt(stack.popPointer(), stack.popUnsignedLong(), stack.popInt());
	

}
void funcs::iget_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * get a int_32 from a field on a pointer to stack.
 */

	stack.pushInt(MvM::accessMemoryAndGetInt(stack.popPointer(), stack.popUnsignedLong()));
	

}
void funcs::iinc1_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * increment a local variable int_32 by 1.
 */

	{ uint_16 point = ops.getUnsignedShort(); lvt[point].Int = lvt[point].Int + 1; }
	

}
void funcs::iinc2_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * increment a local variable int_32 by 2.
 */

	{ uint_16 point = ops.getUnsignedShort(); lvt[point].Int = lvt[point].Int + 2; }
	

}
void funcs::imainst_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_32 from main stack in a local variable..
 */

	lvt[ops.getUnsignedShort()].Int = stack_main.popInt();
	

}
void funcs::imainst_0_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_32 from main stack in local variable 0.
 */

	lvt[0].Int = stack_main.popInt();;
	

}
void funcs::imainst_1_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_32 from main stack in local variable 1.
 */

	lvt[1].Int = stack_main.popInt();;
	

}
void funcs::imainst_2_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_32 from main stack in local variable 2.
 */

	lvt[2].Int = stack_main.popInt();;
	

}
void funcs::imainst_3_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_32 from main stack in local variable 3.
 */

	lvt[3].Int = stack_main.popInt();;
	

}
void funcs::iprint_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * print a int_32 from stack.
 */

	MvM::log(std::to_string(stack.popInt()));
	

}
void funcs::iuprint_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * print a unsigned uint_32 from stack.
 */
 
	MvM::log(std::to_string(stack.popUnsignedInt()));
	;
}
void funcs::lconst_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_64 into the stack.
 */

	stack.pushLong(ops.getLong());
	

}
void funcs::lconst_0_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_64 into the stack (value = 0).
 */

	stack.pushLong(0);
	

}
void funcs::lconst_1_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_64 into the stack (value = 1).
 */

	stack.pushLong(1);
	

}
void funcs::lconst_2_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_64 into the stack (value = 2).
 */

	stack.pushLong(2);
	

}
void funcs::lconst_3_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_64 into the stack (value = 3).
 */

	stack.pushLong(3);
	

}
void funcs::lconst_4_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_64 into the stack (value = 4).
 */

	stack.pushLong(4);
	

}
void funcs::lconst_5_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_64 into the stack (value = 5).
 */

	stack.pushLong(5);
	

}
void funcs::lconst_6_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_64 into the stack (value = 6).
 */

	stack.pushLong(6);
	

}
void funcs::lconst_9_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_64 into the stack (value = 9).
 */

	stack.pushLong(9);
	

}
void funcs::lconst_10_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_64 into the stack (value = 10).
 */

	stack.pushLong(10);
	

}
void funcs::lconst_11_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_64 into the stack (value = 11).
 */

	stack.pushLong(11);
	

}
void funcs::lconst_12_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_64 into the stack (value = 12).
 */

	stack.pushLong(12);
	

}
void funcs::lload_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * load a int_64 into the stack from local variable.
 */

	stack.pushLong(lvt[ops.getUnsignedShort()].Long);
	

}
void funcs::lload_0_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * load a int_64 into the stack from local variable 0.
 */

	stack.pushLong(lvt[0].Long);
	

}
void funcs::lload_1_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * load a int_64 into the stack from local variable 1.
 */

	stack.pushLong(lvt[1].Long);
	

}
void funcs::lload_2_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * load a int_64 into the stack from local variable 2.
 */

	stack.pushLong(lvt[2].Long);
	

}
void funcs::lload_3_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * load a int_64 into the stack from local variable 3.
 */

	stack.pushLong(lvt[3].Long);
	

}
void funcs::lload_4_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * load a int_64 into the stack from local variable 4.
 */

	stack.pushLong(lvt[4].Long);
	

}
void funcs::lstore_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_64 from stack into local variable.
 */

	lvt[ops.getUnsignedShort()] = MvM::lve_Long(stack.popLong());
	

}
void funcs::lstore_0_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_64 from stack into local variable 0.
 */

	lvt[0] = MvM::lve_Long(stack.popLong());
	

}
void funcs::lstore_1_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_64 from stack into local variable 1.
 */

	lvt[1] = MvM::lve_Long(stack.popLong());
	

}
void funcs::lstore_2_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_64 from stack into local variable 2.
 */

	lvt[2] = MvM::lve_Long(stack.popLong());
	

}
void funcs::lstore_3_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_64 from stack into local variable 3.
 */

	lvt[3] = MvM::lve_Long(stack.popLong());
	

}
void funcs::lstore_4_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_64 from stack into local variable 4.
 */

	lvt[4] = MvM::lve_Long(stack.popLong());
	

}
void funcs::ladd_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * add two Longs.
 */

	stack.pushLong(stack.popLong() + stack.popLong());
	

}
void funcs::luadd_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * add two UnsignedUnsignedLongs.
 */
 
	stack.pushUnsignedLong(stack.popUnsignedLong() + stack.popUnsignedLong());
	;
}
void funcs::lsub_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * subtract two Longs.
 */

	stack.pushLong(stack.popLong() - stack.popLong());
	

}
void funcs::lusub_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * subtract two UnsignedUnsignedLongs.
 */
 
	stack.pushUnsignedLong(stack.popUnsignedLong() - stack.popUnsignedLong());
	;
}
void funcs::lmul_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * multiply two Longs.
 */

	stack.pushLong(stack.popLong() * stack.popLong());
	

}
void funcs::lumul_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * multiply two UnsignedUnsignedLongs.
 */
 
	stack.pushUnsignedLong(stack.popUnsignedLong() * stack.popUnsignedLong());
	;
}
void funcs::ldiv_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * divide two Longs.
 */

	stack.pushLong(stack.popLong() / stack.popLong());
	

}
void funcs::ludiv_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * divide two UnsignedUnsignedLongs.
 */
 
	stack.pushUnsignedLong(stack.popUnsignedLong() / stack.popUnsignedLong());
	;
}
void funcs::lset_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * set a int_64 from stack into a field on pointer.
 */

	MvM::accessMemoryAndSetLong(stack.popPointer(), stack.popUnsignedLong(), stack.popLong());
	

}
void funcs::lget_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * get a int_64 from a field on a pointer to stack.
 */

	stack.pushLong(MvM::accessMemoryAndGetLong(stack.popPointer(), stack.popUnsignedLong()));
	

}
void funcs::linc1_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * increment a local variable int_64 by 1.
 */

	{ uint_16 point = ops.getUnsignedShort(); lvt[point].Long = lvt[point].Long + 1; }
	

}
void funcs::linc2_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * increment a local variable int_64 by 2.
 */

	{ uint_16 point = ops.getUnsignedShort(); lvt[point].Long = lvt[point].Long + 2; }
	

}
void funcs::lmainst_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_64 from main stack in a local variable..
 */

	lvt[ops.getUnsignedShort()].Long = stack_main.popLong();
	

}
void funcs::lmainst_0_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_64 from main stack in local variable 0.
 */

	lvt[0].Long = stack_main.popLong();;
	

}
void funcs::lmainst_1_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_64 from main stack in local variable 1.
 */

	lvt[1].Long = stack_main.popLong();;
	

}
void funcs::lmainst_2_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_64 from main stack in local variable 2.
 */

	lvt[2].Long = stack_main.popLong();;
	

}
void funcs::lmainst_3_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_64 from main stack in local variable 3.
 */

	lvt[3].Long = stack_main.popLong();;
	

}
void funcs::lprint_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * print a int_64 from stack.
 */

	MvM::log(std::to_string(stack.popLong()));
	

}
void funcs::luprint_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * print a unsigned uint_64 from stack.
 */
 
	MvM::log(std::to_string(stack.popUnsignedLong()));
	;
}
void funcs::liconst_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_128 into the stack.
 */

	stack.pushLongInt(ops.getLongInt());
	

}
void funcs::liconst_0_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_128 into the stack (value = 0).
 */

	stack.pushLongInt(0);
	

}
void funcs::liload_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * load a int_128 into the stack from local variable.
 */

	stack.pushLongInt(lvt[ops.getUnsignedShort()].LongInt);
	

}
void funcs::listore_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_128 from stack into local variable.
 */

	lvt[ops.getUnsignedShort()] = MvM::lve_LongInt(stack.popLongInt());
	

}
void funcs::liadd_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * add two LongInts.
 */

	stack.pushLongInt(stack.popLongInt() + stack.popLongInt());
	

}
void funcs::liuadd_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * add two UnsignedUnsignedLongInts.
 */
 
	stack.pushUnsignedLongInt(stack.popUnsignedLongInt() + stack.popUnsignedLongInt());
	;
}
void funcs::lisub_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * subtract two LongInts.
 */

	stack.pushLongInt(stack.popLongInt() - stack.popLongInt());
	

}
void funcs::liusub_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * subtract two UnsignedUnsignedLongInts.
 */
 
	stack.pushUnsignedLongInt(stack.popUnsignedLongInt() - stack.popUnsignedLongInt());
	;
}
void funcs::limul_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * multiply two LongInts.
 */

	stack.pushLongInt(stack.popLongInt() * stack.popLongInt());
	

}
void funcs::liumul_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * multiply two UnsignedUnsignedLongInts.
 */
 
	stack.pushUnsignedLongInt(stack.popUnsignedLongInt() * stack.popUnsignedLongInt());
	;
}
void funcs::lidiv_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * divide two LongInts.
 */

	stack.pushLongInt(stack.popLongInt() / stack.popLongInt());
	

}
void funcs::liudiv_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * divide two UnsignedUnsignedLongInts.
 */
 
	stack.pushUnsignedLongInt(stack.popUnsignedLongInt() / stack.popUnsignedLongInt());
	;
}
void funcs::liset_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * set a int_128 from stack into a field on pointer.
 */

	MvM::accessMemoryAndSetLongInt(stack.popPointer(), stack.popUnsignedLong(), stack.popLongInt());
	

}
void funcs::liget_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * get a int_128 from a field on a pointer to stack.
 */

	stack.pushLongInt(MvM::accessMemoryAndGetLongInt(stack.popPointer(), stack.popUnsignedLong()));
	

}
void funcs::limainst_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_128 from main stack in a local variable..
 */

	lvt[ops.getUnsignedShort()].LongInt = stack_main.popLongInt();
	

}
void funcs::liprint_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * print a int_128 from stack.
 */

	MvM::log(std::to_string(stack.popLongInt()));
	

}
void funcs::liuprint_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * print a unsigned uint_128 from stack.
 */
 
	MvM::log(std::to_string(stack.popUnsignedLongInt()));
	;
}
void funcs::llconst_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_256 into the stack.
 */

	stack.pushLongLong(ops.getLongLong());
	

}
void funcs::llconst_0_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const int_256 into the stack (value = 0).
 */

	stack.pushLongLong(0);
	

}
void funcs::llload_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * load a int_256 into the stack from local variable.
 */

	stack.pushLongLong(lvt[ops.getUnsignedShort()].LongLong);
	

}
void funcs::llstore_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_256 from stack into local variable.
 */

	lvt[ops.getUnsignedShort()] = MvM::lve_LongLong(stack.popLongLong());
	

}
void funcs::lladd_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * add two LongLongs.
 */

	stack.pushLongLong(stack.popLongLong() + stack.popLongLong());
	

}
void funcs::lluadd_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * add two UnsignedUnsignedLongLongs.
 */
 
	stack.pushUnsignedLongLong(stack.popUnsignedLongLong() + stack.popUnsignedLongLong());
	;
}
void funcs::llsub_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * subtract two LongLongs.
 */

	stack.pushLongLong(stack.popLongLong() - stack.popLongLong());
	

}
void funcs::llusub_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * subtract two UnsignedUnsignedLongLongs.
 */
 
	stack.pushUnsignedLongLong(stack.popUnsignedLongLong() - stack.popUnsignedLongLong());
	;
}
void funcs::llmul_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * multiply two LongLongs.
 */

	stack.pushLongLong(stack.popLongLong() * stack.popLongLong());
	

}
void funcs::llumul_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * multiply two UnsignedUnsignedLongLongs.
 */
 
	stack.pushUnsignedLongLong(stack.popUnsignedLongLong() * stack.popUnsignedLongLong());
	;
}
void funcs::lldiv_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * divide two LongLongs.
 */

	stack.pushLongLong(stack.popLongLong() / stack.popLongLong());
	

}
void funcs::lludiv_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * divide two UnsignedUnsignedLongLongs.
 */
 
	stack.pushUnsignedLongLong(stack.popUnsignedLongLong() / stack.popUnsignedLongLong());
	;
}
void funcs::llset_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * set a int_256 from stack into a field on pointer.
 */

	MvM::accessMemoryAndSetLongLong(stack.popPointer(), stack.popUnsignedLong(), stack.popLongLong());
	

}
void funcs::llget_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * get a int_256 from a field on a pointer to stack.
 */

	stack.pushLongLong(MvM::accessMemoryAndGetLongLong(stack.popPointer(), stack.popUnsignedLong()));
	

}
void funcs::llmainst_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a int_256 from main stack in a local variable..
 */

	lvt[ops.getUnsignedShort()].LongLong = stack_main.popLongLong();
	

}
void funcs::llprint_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * print a int_256 from stack.
 */

	MvM::log(std::to_string(stack.popLongLong()));
	

}
void funcs::lluprint_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * print a unsigned uint_256 from stack.
 */
 
	MvM::log(std::to_string(stack.popUnsignedLongLong()));
	;
}
void funcs::fconst_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const flt_32 into the stack.
 */

	stack.pushFloat(ops.getFloat());
	

}
void funcs::fconst_0_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const flt_32 into the stack (value = 0).
 */

	stack.pushFloat(0);
	

}
void funcs::fload_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * load a flt_32 into the stack from local variable.
 */

	stack.pushFloat(lvt[ops.getUnsignedShort()].Float);
	

}
void funcs::fstore_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a flt_32 from stack into local variable.
 */

	lvt[ops.getUnsignedShort()] = MvM::lve_Float(stack.popFloat());
	

}
void funcs::fset_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * set a flt_32 from stack into a field on pointer.
 */

	MvM::accessMemoryAndSetFloat(stack.popPointer(), stack.popUnsignedLong(), stack.popFloat());
	

}
void funcs::fget_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * get a flt_32 from a field on a pointer to stack.
 */

	stack.pushFloat(MvM::accessMemoryAndGetFloat(stack.popPointer(), stack.popUnsignedLong()));
	

}
void funcs::fmainst_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a flt_32 from main stack in a local variable..
 */

	lvt[ops.getUnsignedShort()].Float = stack_main.popFloat();
	

}
void funcs::dconst_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const flt_64 into the stack.
 */

	stack.pushDouble(ops.getDouble());
	

}
void funcs::dconst_0_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const flt_64 into the stack (value = 0).
 */

	stack.pushDouble(0);
	

}
void funcs::dload_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * load a flt_64 into the stack from local variable.
 */

	stack.pushDouble(lvt[ops.getUnsignedShort()].Double);
	

}
void funcs::dstore_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a flt_64 from stack into local variable.
 */

	lvt[ops.getUnsignedShort()] = MvM::lve_Double(stack.popDouble());
	

}
void funcs::dset_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * set a flt_64 from stack into a field on pointer.
 */

	MvM::accessMemoryAndSetDouble(stack.popPointer(), stack.popUnsignedLong(), stack.popDouble());
	

}
void funcs::dget_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * get a flt_64 from a field on a pointer to stack.
 */

	stack.pushDouble(MvM::accessMemoryAndGetDouble(stack.popPointer(), stack.popUnsignedLong()));
	

}
void funcs::dmainst_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a flt_64 from main stack in a local variable..
 */

	lvt[ops.getUnsignedShort()].Double = stack_main.popDouble();
	

}
void funcs::dfconst_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const flt_128 into the stack.
 */

	stack.pushDoubleFloat(ops.getDoubleFloat());
	

}
void funcs::dfconst_0_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const flt_128 into the stack (value = 0).
 */

	stack.pushDoubleFloat(0);
	

}
void funcs::dfload_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * load a flt_128 into the stack from local variable.
 */

	stack.pushDoubleFloat(lvt[ops.getUnsignedShort()].DoubleFloat);
	

}
void funcs::dfstore_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a flt_128 from stack into local variable.
 */

	lvt[ops.getUnsignedShort()] = MvM::lve_DoubleFloat(stack.popDoubleFloat());
	

}
void funcs::dfset_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * set a flt_128 from stack into a field on pointer.
 */

	MvM::accessMemoryAndSetDoubleFloat(stack.popPointer(), stack.popUnsignedLong(), stack.popDoubleFloat());
	

}
void funcs::dfget_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * get a flt_128 from a field on a pointer to stack.
 */

	stack.pushDoubleFloat(MvM::accessMemoryAndGetDoubleFloat(stack.popPointer(), stack.popUnsignedLong()));
	

}
void funcs::dfmainst_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a flt_128 from main stack in a local variable..
 */

	lvt[ops.getUnsignedShort()].DoubleFloat = stack_main.popDoubleFloat();
	

}
void funcs::ddconst_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const flt_256 into the stack.
 */

	stack.pushDoubleDouble(ops.getDoubleDouble());
	

}
void funcs::ddconst_0_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const flt_256 into the stack (value = 0).
 */

	stack.pushDoubleDouble(0);
	

}
void funcs::ddload_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * load a flt_256 into the stack from local variable.
 */

	stack.pushDoubleDouble(lvt[ops.getUnsignedShort()].DoubleDouble);
	

}
void funcs::ddstore_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a flt_256 from stack into local variable.
 */

	lvt[ops.getUnsignedShort()] = MvM::lve_DoubleDouble(stack.popDoubleDouble());
	

}
void funcs::ddset_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * set a flt_256 from stack into a field on pointer.
 */

	MvM::accessMemoryAndSetDoubleDouble(stack.popPointer(), stack.popUnsignedLong(), stack.popDoubleDouble());
	

}
void funcs::ddget_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * get a flt_256 from a field on a pointer to stack.
 */

	stack.pushDoubleDouble(MvM::accessMemoryAndGetDoubleDouble(stack.popPointer(), stack.popUnsignedLong()));
	

}
void funcs::ddmainst_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a flt_256 from main stack in a local variable..
 */

	lvt[ops.getUnsignedShort()].DoubleDouble = stack_main.popDoubleDouble();
	

}
void funcs::aconst_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const pointer into the stack.
 */

	stack.pushPointer(ops.getPointer());
	

}
void funcs::aconst_0_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * push a const pointer into the stack (value = 0).
 */

	stack.pushPointer(0);
	

}
void funcs::aload_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * load a pointer into the stack from local variable.
 */

	stack.pushPointer(lvt[ops.getUnsignedShort()].Pointer);
	

}
void funcs::astore_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a pointer from stack into local variable.
 */

	lvt[ops.getUnsignedShort()] = MvM::lve_Pointer(stack.popPointer());
	

}
void funcs::aset_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * set a pointer from stack into a field on pointer.
 */

	MvM::accessMemoryAndSetPointer(stack.popPointer(), stack.popUnsignedLong(), stack.popPointer());
	

}
void funcs::aget_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * get a pointer from a field on a pointer to stack.
 */

	stack.pushPointer(MvM::accessMemoryAndGetPointer(stack.popPointer(), stack.popUnsignedLong()));
	

}
void funcs::amainst_impl(OP_STACK* globalTable, MochaNativeInterface** nativeTable, pointer globalPointer, pointer basePointer, Stack& stack_main, Stack& stack, OP_STACK& ops, std::map<uint_32, localvarelement>& lvt, std::map<uint_32, uint_64>& CHECK_POINTS, pointer base)
{	/**
 * store a pointer from main stack in a local variable..
 */

	lvt[ops.getUnsignedShort()].Pointer = stack_main.popPointer();
	

}




void funcs::getAllImplementations(uint_64& _opfuncindex_)
{
    #define impl_funcs impl::impl_funcs
    
    impl_funcs[0] = &func_impl;
    impl_funcs[1] = &hash_impl;
    impl_funcs[2] = &timens_impl;
    impl_funcs[3] = &timems_impl;
    impl_funcs[4] = &strconst_impl;
    impl_funcs[5] = &strload_impl;
    impl_funcs[6] = &strstore_impl;
    impl_funcs[7] = &strsizeof_impl;
    impl_funcs[8] = &strcast_a_impl;
    impl_funcs[9] = &strcast_ba_impl;
    impl_funcs[10] = &strprint_impl;
    impl_funcs[11] = &strreturn_impl;
    impl_funcs[12] = &mark_impl;
    impl_funcs[13] = &jump_impl;
    impl_funcs[14] = &jumptomark_impl;
    impl_funcs[15] = &newline_impl;
    impl_funcs[16] = &ret_impl;
    impl_funcs[17] = &invoke_impl;
    impl_funcs[18] = &invokedynamic_impl;
    impl_funcs[19] = &invokespecial_impl;
    impl_funcs[20] = &if_t_impl;
    impl_funcs[21] = &if_f_impl;
    impl_funcs[22] = &invert_impl;
    impl_funcs[23] = &amemcpy_impl;
    impl_funcs[24] = &bspmemcpy_impl;
    impl_funcs[25] = &amemcpybsp_impl;
    impl_funcs[26] = &amalloc_impl;
    impl_funcs[27] = &acalloc_impl;
    impl_funcs[28] = &amallocs_impl;
    impl_funcs[29] = &acallocs_impl;
    impl_funcs[30] = &adelete_impl;
    impl_funcs[31] = &baconst_impl;
    impl_funcs[32] = &baconsts_impl;
    impl_funcs[33] = &baconsti_impl;
    impl_funcs[34] = &bacast_a_impl;
    impl_funcs[35] = &basizeof_impl;
    impl_funcs[36] = &printba_impl;
    impl_funcs[37] = &cmpl_impl;
    impl_funcs[38] = &cmpg_impl;
    impl_funcs[39] = &cmpe_impl;
    impl_funcs[40] = &cmple_impl;
    impl_funcs[41] = &cmpge_impl;
    impl_funcs[42] = &cmpne_impl;
    impl_funcs[43] = &ucmp_impl;
    impl_funcs[44] = &cmpu_impl;
    impl_funcs[45] = &cmpll_impl;
    impl_funcs[46] = &ucmpll_impl;
    impl_funcs[47] = &cmpull_impl;
    impl_funcs[48] = &dcmpl_impl;
    impl_funcs[49] = &dcmpg_impl;
    impl_funcs[50] = &dcmpe_impl;
    impl_funcs[51] = &dcmple_impl;
    impl_funcs[52] = &dcmpge_impl;
    impl_funcs[53] = &dcmpne_impl;
    impl_funcs[54] = &mod_impl;
    impl_funcs[55] = &llmod_impl;
    impl_funcs[56] = &and__impl;
    impl_funcs[57] = &or__impl;
    impl_funcs[58] = &xor__impl;
    impl_funcs[59] = &not__impl;
    impl_funcs[60] = &rshft__impl;
    impl_funcs[61] = &lshft__impl;
    impl_funcs[62] = &dup_impl;
    impl_funcs[63] = &dup2_impl;
    impl_funcs[64] = &dup3_impl;
    impl_funcs[65] = &swap_impl;
    impl_funcs[66] = &pret_impl;
    impl_funcs[67] = &pret2_impl;
    impl_funcs[68] = &pret4_impl;
    impl_funcs[69] = &bconst_impl;
    impl_funcs[70] = &bconst_0_impl;
    impl_funcs[71] = &bload_impl;
    impl_funcs[72] = &bstore_impl;
    impl_funcs[73] = &bset_impl;
    impl_funcs[74] = &bget_impl;
    impl_funcs[75] = &bmainst_impl;
    impl_funcs[76] = &bprint_impl;
    impl_funcs[77] = &buprint_impl;
    impl_funcs[78] = &sconst_impl;
    impl_funcs[79] = &sconst_0_impl;
    impl_funcs[80] = &sload_impl;
    impl_funcs[81] = &sstore_impl;
    impl_funcs[82] = &sset_impl;
    impl_funcs[83] = &sget_impl;
    impl_funcs[84] = &smainst_impl;
    impl_funcs[85] = &sprint_impl;
    impl_funcs[86] = &suprint_impl;
    impl_funcs[87] = &iconst_impl;
    impl_funcs[88] = &iconst_0_impl;
    impl_funcs[89] = &iconst_1_impl;
    impl_funcs[90] = &iconst_2_impl;
    impl_funcs[91] = &iconst_3_impl;
    impl_funcs[92] = &iconst_4_impl;
    impl_funcs[93] = &iconst_5_impl;
    impl_funcs[94] = &iconst_6_impl;
    impl_funcs[95] = &iconst_9_impl;
    impl_funcs[96] = &iconst_10_impl;
    impl_funcs[97] = &iconst_11_impl;
    impl_funcs[98] = &iconst_12_impl;
    impl_funcs[99] = &iload_impl;
    impl_funcs[100] = &iload_0_impl;
    impl_funcs[101] = &iload_1_impl;
    impl_funcs[102] = &iload_2_impl;
    impl_funcs[103] = &iload_3_impl;
    impl_funcs[104] = &iload_4_impl;
    impl_funcs[105] = &istore_impl;
    impl_funcs[106] = &istore_0_impl;
    impl_funcs[107] = &istore_1_impl;
    impl_funcs[108] = &istore_2_impl;
    impl_funcs[109] = &istore_3_impl;
    impl_funcs[110] = &istore_4_impl;
    impl_funcs[111] = &iadd_impl;
    impl_funcs[112] = &iuadd_impl;
    impl_funcs[113] = &isub_impl;
    impl_funcs[114] = &iusub_impl;
    impl_funcs[115] = &imul_impl;
    impl_funcs[116] = &iumul_impl;
    impl_funcs[117] = &idiv_impl;
    impl_funcs[118] = &iudiv_impl;
    impl_funcs[119] = &iset_impl;
    impl_funcs[120] = &iget_impl;
    impl_funcs[121] = &iinc1_impl;
    impl_funcs[122] = &iinc2_impl;
    impl_funcs[123] = &imainst_impl;
    impl_funcs[124] = &imainst_0_impl;
    impl_funcs[125] = &imainst_1_impl;
    impl_funcs[126] = &imainst_2_impl;
    impl_funcs[127] = &imainst_3_impl;
    impl_funcs[128] = &iprint_impl;
    impl_funcs[129] = &iuprint_impl;
    impl_funcs[130] = &lconst_impl;
    impl_funcs[131] = &lconst_0_impl;
    impl_funcs[132] = &lconst_1_impl;
    impl_funcs[133] = &lconst_2_impl;
    impl_funcs[134] = &lconst_3_impl;
    impl_funcs[135] = &lconst_4_impl;
    impl_funcs[136] = &lconst_5_impl;
    impl_funcs[137] = &lconst_6_impl;
    impl_funcs[138] = &lconst_9_impl;
    impl_funcs[139] = &lconst_10_impl;
    impl_funcs[140] = &lconst_11_impl;
    impl_funcs[141] = &lconst_12_impl;
    impl_funcs[142] = &lload_impl;
    impl_funcs[143] = &lload_0_impl;
    impl_funcs[144] = &lload_1_impl;
    impl_funcs[145] = &lload_2_impl;
    impl_funcs[146] = &lload_3_impl;
    impl_funcs[147] = &lload_4_impl;
    impl_funcs[148] = &lstore_impl;
    impl_funcs[149] = &lstore_0_impl;
    impl_funcs[150] = &lstore_1_impl;
    impl_funcs[151] = &lstore_2_impl;
    impl_funcs[152] = &lstore_3_impl;
    impl_funcs[153] = &lstore_4_impl;
    impl_funcs[154] = &ladd_impl;
    impl_funcs[155] = &luadd_impl;
    impl_funcs[156] = &lsub_impl;
    impl_funcs[157] = &lusub_impl;
    impl_funcs[158] = &lmul_impl;
    impl_funcs[159] = &lumul_impl;
    impl_funcs[160] = &ldiv_impl;
    impl_funcs[161] = &ludiv_impl;
    impl_funcs[162] = &lset_impl;
    impl_funcs[163] = &lget_impl;
    impl_funcs[164] = &linc1_impl;
    impl_funcs[165] = &linc2_impl;
    impl_funcs[166] = &lmainst_impl;
    impl_funcs[167] = &lmainst_0_impl;
    impl_funcs[168] = &lmainst_1_impl;
    impl_funcs[169] = &lmainst_2_impl;
    impl_funcs[170] = &lmainst_3_impl;
    impl_funcs[171] = &lprint_impl;
    impl_funcs[172] = &luprint_impl;
    impl_funcs[173] = &liconst_impl;
    impl_funcs[174] = &liconst_0_impl;
    impl_funcs[175] = &liload_impl;
    impl_funcs[176] = &listore_impl;
    impl_funcs[177] = &liadd_impl;
    impl_funcs[178] = &liuadd_impl;
    impl_funcs[179] = &lisub_impl;
    impl_funcs[180] = &liusub_impl;
    impl_funcs[181] = &limul_impl;
    impl_funcs[182] = &liumul_impl;
    impl_funcs[183] = &lidiv_impl;
    impl_funcs[184] = &liudiv_impl;
    impl_funcs[185] = &liset_impl;
    impl_funcs[186] = &liget_impl;
    impl_funcs[187] = &limainst_impl;
    impl_funcs[188] = &liprint_impl;
    impl_funcs[189] = &liuprint_impl;
    impl_funcs[190] = &llconst_impl;
    impl_funcs[191] = &llconst_0_impl;
    impl_funcs[192] = &llload_impl;
    impl_funcs[193] = &llstore_impl;
    impl_funcs[194] = &lladd_impl;
    impl_funcs[195] = &lluadd_impl;
    impl_funcs[196] = &llsub_impl;
    impl_funcs[197] = &llusub_impl;
    impl_funcs[198] = &llmul_impl;
    impl_funcs[199] = &llumul_impl;
    impl_funcs[200] = &lldiv_impl;
    impl_funcs[201] = &lludiv_impl;
    impl_funcs[202] = &llset_impl;
    impl_funcs[203] = &llget_impl;
    impl_funcs[204] = &llmainst_impl;
    impl_funcs[205] = &llprint_impl;
    impl_funcs[206] = &lluprint_impl;
    impl_funcs[207] = &fconst_impl;
    impl_funcs[208] = &fconst_0_impl;
    impl_funcs[209] = &fload_impl;
    impl_funcs[210] = &fstore_impl;
    impl_funcs[211] = &fset_impl;
    impl_funcs[212] = &fget_impl;
    impl_funcs[213] = &fmainst_impl;
    impl_funcs[214] = &dconst_impl;
    impl_funcs[215] = &dconst_0_impl;
    impl_funcs[216] = &dload_impl;
    impl_funcs[217] = &dstore_impl;
    impl_funcs[218] = &dset_impl;
    impl_funcs[219] = &dget_impl;
    impl_funcs[220] = &dmainst_impl;
    impl_funcs[221] = &dfconst_impl;
    impl_funcs[222] = &dfconst_0_impl;
    impl_funcs[223] = &dfload_impl;
    impl_funcs[224] = &dfstore_impl;
    impl_funcs[225] = &dfset_impl;
    impl_funcs[226] = &dfget_impl;
    impl_funcs[227] = &dfmainst_impl;
    impl_funcs[228] = &ddconst_impl;
    impl_funcs[229] = &ddconst_0_impl;
    impl_funcs[230] = &ddload_impl;
    impl_funcs[231] = &ddstore_impl;
    impl_funcs[232] = &ddset_impl;
    impl_funcs[233] = &ddget_impl;
    impl_funcs[234] = &ddmainst_impl;
    impl_funcs[235] = &aconst_impl;
    impl_funcs[236] = &aconst_0_impl;
    impl_funcs[237] = &aload_impl;
    impl_funcs[238] = &astore_impl;
    impl_funcs[239] = &aset_impl;
    impl_funcs[240] = &aget_impl;
    impl_funcs[241] = &amainst_impl;
}
