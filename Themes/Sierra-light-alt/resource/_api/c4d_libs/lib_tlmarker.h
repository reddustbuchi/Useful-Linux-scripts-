/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

//---------------------------------------------------
#ifndef _C4D_TLMARKER_H_
#define _C4D_TLMARKER_H_

#ifdef __API_INTERN__
#include "c4d_basetime.h"
#include "ge_string.h"
#include "c4d_library.h"
#include "c4d_gui.h"
#else
#include "c4d.h"
#endif


#define C4D_TLMARKER_LIBRARY_ID		465001534


BaseList2D* GetFirstMarker(BaseDocument* doc);
BaseList2D* AddMarker(BaseDocument* doc,BaseList2D* pPred,BaseTime time,String name);

//---------------------------------------------------
//	---INTERNAL STUFF


struct TLMarkerLibrary : public C4DLibrary
{
	BaseList2D*	(*GetFirstMarker)(BaseDocument* doc);
	BaseList2D*	(*AddMarker)(BaseDocument* doc,BaseList2D* pPred,BaseTime time,String name);
};

#endif

