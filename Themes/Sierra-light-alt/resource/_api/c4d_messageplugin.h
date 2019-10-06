/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4D_MESSAGEPLUGIN_H
#define __C4D_MESSAGEPLUGIN_H

#include "ge_math.h"
#include "c4d_messagedata.h"
#include "c4d_baseplugin.h"

#define MSG_TIMER					112008

struct MESSAGEPLUGIN : public STATICPLUGIN
{
	Int32 (MessageData::*GetTimer		)(void);
	Bool (MessageData::*CoreMessage	)(Int32 id, const BaseContainer &bc);

	void*	reserved[(32-2)*C4DPL_MEMBERMULTIPLIER];
};

#endif
