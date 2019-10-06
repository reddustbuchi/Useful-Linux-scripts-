/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _LIB_ICON_COLLECTION_H_
#define _LIB_ICON_COLLECTION_H_

#include "c4d_library.h"

enum ICONFLAG
{
	ICONFLAG_0					= 0,
	ICONFLAG_COPY				= (1<<0),
	ICONFLAG_OVERWRITE	= (1<<1),
	ICONFLAG_2X					= (1<<2)
} ENUM_END_FLAGS(ICONFLAG);

Bool RegisterIcon(Int32 lIconID, BaseBitmap *pBmp, Int32 x = 0, Int32 y = 0, Int32 w = -1, Int32 h = -1, ICONFLAG lFlags = ICONFLAG_0);
Bool RegisterIcon(Int32 lIconID, Filename fn, Int32 x = 0, Int32 y = 0, Int32 w = -1, Int32 h = -1, ICONFLAG lFlags = ICONFLAG_0); // always creates a copy (ICONFLAG_COPY set)
Bool GetIcon(Int32 lIconID, IconData* pData);
Bool UnregisterIcon(Int32 lIconID);

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF


#define LIBRARY_ICON_COLLECTION     1009310

struct IconCollectionLib : public C4DLibrary
{
	Bool        (*RegisterIconBitmap)(Int32 lIconID, BaseBitmap *pBmp, Int32 x, Int32 y, Int32 w, Int32 h, ICONFLAG lFlags);
	Bool        (*RegisterIconFile)(Int32 lIconID, Filename fn, Int32 x, Int32 y, Int32 w, Int32 h, ICONFLAG lFlags);
	Bool        (*GetIcon)(Int32 lIconID, IconData* pData);
	Bool        (*UnregisterIcon)(Int32 lIconID);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif // _LIB_ICON_COLLECTION_H_
