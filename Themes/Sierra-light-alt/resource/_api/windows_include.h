#ifndef __WINDOWS_INCLUDE_H
#define __WINDOWS_INCLUDE_H

// rename windows LONG/ULONG datatype as it collides with c4d's new definition
#define LONG	WinLONG
#define ULONG WinULONG

// prevent include of Windows dialog definitions that will collide with c4d types
#define	WIN32_LEAN_AND_MEAN

#include <windows.h>

#undef LONG
#undef ULONG

#endif	// __WINDOWS_INCLUDE_H
