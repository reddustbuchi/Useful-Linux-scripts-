#ifndef __OSX_INCLUDE_H
#define __OSX_INCLUDE_H

// avoid a conflict between UInt (in OSTypes.h) and in ge_sys_math.h
#define UInt OSXUInt

#include <Carbon/Carbon.h>

#undef UInt

#endif	// __OSX_INCLUDE_H
