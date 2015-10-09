#ifndef __INCL_TYPES
#define __INCL_TYPES

#include "memory.hpp"
#include "string.hpp"
#include "exception.hpp"

/*
types.h - creates a consistent naming system for all the different types used in mod3.
*/

namespace mod3 {
	typedef signed char Int8;
	typedef byte UInt8;
	typedef short Int16;
	typedef unsigned short UInt16;
	typedef int Int32;
	typedef unsigned int UInt32;
	typedef long Int64;
	typedef unsigned long UInt64;
	typedef char Char;
	typedef string String;
	typedef exception Exception;
}

#endif