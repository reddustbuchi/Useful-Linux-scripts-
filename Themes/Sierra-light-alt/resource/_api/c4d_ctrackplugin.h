/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4D_CTRACKPLUGIN_H
#define __C4D_CTRACKPLUGIN_H

#include "ge_math.h"
#include "c4d_ctrackdata.h"
#include "c4d_nodeplugin.h"

struct CTRACKPLUGIN : public NODEPLUGIN
{
	Bool	(CTrackData::*Animate)(CTrack* track, const CAnimInfo* info, Bool* chg, void* data);
	Int32	(CTrackData::*GuiMessage)(CTrack* track, const BaseContainer& msg, BaseContainer& result);
	Bool	(CTrackData::*Draw)(CTrack* track, GeClipMap* map, const BaseTime& clip_left, const BaseTime& clip_right);
	Int32	(CTrackData::*GetHeight)(CTrack* track);
	Bool	(CTrackData::*FillKey)(CTrack* track, BaseDocument* doc, BaseList2D* bl, CKey* key);
	Bool	(CTrackData::*TrackInformation)(CTrack* track, BaseDocument* doc, CKey* key, String* str, Bool set);

	Bool	(CTrackData::*KeyMessage)(CTrack* track, CKey* node, Int32 type, void* data);
	Bool	(CTrackData::*KeyGetDDescription)(CTrack* track, CKey* node, Description* description, DESCFLAGS_DESC& flags);
	Bool	(CTrackData::*KeyGetDParameter)(CTrack* track, CKey* node, const DescID& id, GeData& t_data, DESCFLAGS_GET& flags);
	Bool	(CTrackData::*KeyGetDEnabling)(CTrack* track, CKey* node, const DescID& id, const GeData& t_data, DESCFLAGS_ENABLE flags, const BaseContainer* itemdesc);
	Bool	(CTrackData::*KeySetDParameter)(CTrack* track, CKey* node, const DescID& id, const GeData& t_data, DESCFLAGS_SET& flags);

	void*	reserved[(32 - 11) * C4DPL_MEMBERMULTIPLIER];
};

#endif
