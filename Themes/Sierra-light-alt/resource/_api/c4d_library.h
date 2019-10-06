/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _C4D_LIBRARY_
#define _C4D_LIBRARY_

#include "operatingsystem.h"

#define LIBOFFSET(s, m) (Int32)((UInt)(&(((s*)0)->m)))

struct C4DLibrary
{
	Int32	version;
	Int32	size;
};

Bool InstallLibrary(Int32 id, C4DLibrary* lib, Int32 version, Int32 size);
Bool UninstallLibrary(C4DLibrary* lib, Int32 version, Int32 size);
C4DLibrary* CheckLib(Int32 id, Int offset, C4DLibrary** store);
Bool IsLibraryInstalled(Int32 id);

#endif
