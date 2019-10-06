/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4D_TAGPLUGIN_H
#define __C4D_TAGPLUGIN_H

#include "ge_math.h"
#include "c4d_tagdata.h"
#include "c4d_nodeplugin.h"

struct TAGPLUGIN : public NODEPLUGIN
{
	Bool						(TagData::*Draw								)(BaseTag *tag, BaseObject *op, BaseDraw *bd, BaseDrawHelp *bh);
	EXECUTIONRESULT (TagData::*Execute					)(BaseTag *tag, BaseDocument *doc, BaseObject *op, BaseThread *bt, Int32 priority, EXECUTIONFLAGS flags);
	Bool						(TagData::*AddToExecution			)(BaseTag *tag, PriorityList *list);
	Bool						(TagData::*GetOmanagerIconEx	)(BaseTag *tag, GeClipMap *map);
	Bool						(TagData::*GetModifiedObjects	)(BaseTag *tag, BaseDocument *doc, BaseObject *&op, Bool &pluginownedop, const Matrix &op_mg, Float lod, Int32 flags, BaseThread *thread);

	void*	reserved[(32-5)*C4DPL_MEMBERMULTIPLIER-0];
};

#endif
