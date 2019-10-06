/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DCTRACKDATA_H
#define __C4DCTRACKDATA_H

#include "c4d_nodedata.h"

class CTrack;
class BaseList2D;
class BaseKey;
class BaseDocument;
class BaseTime;
class GeClipMap;
class CAnimInfo;

class CTrackData : public NodeData
{
public:
	////inherited from NodeData////
	//virtual Bool Init(GeListNode *node);
	//virtual void Free(GeListNode *node);
	//virtual Bool Read(GeListNode *node, HyperFile *hf, Int32 level);
	//virtual Bool Write(GeListNode *node, HyperFile *hf);
	//virtual Bool Message(GeListNode *node, Int32 type, void *data);
	//virtual Bool CopyTo(NodeData *dest, GeListNode *snode, GeListNode *dnode, COPYFLAGS flags, AliasTrans *trn);
	//virtual void GetBubbleHelp(GeListNode *node, String &str);
	//virtual BaseDocument* GetDocument(GeListNode *node);
	//virtual Int32 GetBranchInfo(GeListNode *node, BranchInfo *info, Int32 max, GETBRANCHINFO flags);
	//virtual Bool GetDDescription(GeListNode *node, Description *description, DESCFLAGS_DESC &flags);
	//virtual Bool GetDParameter(GeListNode *node, const DescID &id,GeData &t_data,DESCFLAGS_GET &flags);
	//virtual Bool GetDEnabling(GeListNode *node, const DescID &id,const GeData &t_data,DESCFLAGS_ENABLE flags,const BaseContainer *itemdesc);
	//virtual Bool SetDParameter(GeListNode *node, const DescID &id,const GeData &t_data,DESCFLAGS_SET &flags);
	//static NodeData *Alloc(void) { return NewObjClear(MyNodeData); }
	////inherited from NodeData////

	virtual Bool Animate			 (CTrack* track, const CAnimInfo* info, Bool* chg, void* data);
	virtual Int32	GuiMessage		(CTrack* track, const BaseContainer& msg, BaseContainer& result);
	virtual Bool Draw					 (CTrack* track, GeClipMap* map, const BaseTime& clip_left, const BaseTime& clip_right);
	virtual Int32	GetHeight			(CTrack* track);
	virtual Bool FillKey			 (CTrack* track, BaseDocument* doc, BaseList2D* bl, CKey* key);
	virtual Bool TrackInformation(CTrack* track, BaseDocument* doc, CKey* key, String* str, Bool set);

	virtual Bool KeyMessage				 (CTrack* track, CKey* node, Int32 type, void* data);
	virtual Bool KeyGetDDescription(CTrack* track, CKey* node, Description* description, DESCFLAGS_DESC& flags);
	virtual Bool KeyGetDParameter	 (CTrack* track, CKey* node, const DescID& id, GeData& t_data, DESCFLAGS_GET& flags);
	virtual Bool KeyGetDEnabling	 (CTrack* track, CKey* node, const DescID& id, const GeData& t_data, DESCFLAGS_ENABLE flags, const BaseContainer* itemdesc);
	virtual Bool KeySetDParameter	 (CTrack* track, CKey* node, const DescID& id, const GeData& t_data, DESCFLAGS_SET& flags);
};

Bool RegisterCTrackPlugin(Int32 id, const String& str, Int32 info, DataAllocator* npalloc, const String& description, Int32 disklevel);

#endif
