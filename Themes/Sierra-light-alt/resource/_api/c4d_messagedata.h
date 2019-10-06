/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4D_MESSAGEDATA_H
#define __C4D_MESSAGEDATA_H

#include "c4d_basedata.h"

class String;
class BaseContainer;
class BaseDocument;
class BaseBitmap;

class MessageData : public BaseData
{
public:
	virtual Int32 GetTimer(void);
	virtual Bool CoreMessage(Int32 id, const BaseContainer& bc) = 0;
};

Bool RegisterMessagePlugin(Int32 id, const String& str, Int32 info, MessageData* dat);

#endif
