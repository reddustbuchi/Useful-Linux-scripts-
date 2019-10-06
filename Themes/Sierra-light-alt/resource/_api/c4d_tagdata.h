/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DTAGDATA_H
#define __C4DTAGDATA_H

#include "c4d_nodedata.h"
#include "operatingsystem.h"

class BaseTag;
class BaseObject;
class BaseDraw;
class BaseDrawHelp;
class BaseDocument;
class BaseBitmap;
class String;
class BaseThread;
class PriorityList;
class GeClipMap;

class TagData : public NodeData
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

	virtual Bool Draw(BaseTag* tag, BaseObject* op, BaseDraw* bd, BaseDrawHelp* bh);
	virtual EXECUTIONRESULT Execute(BaseTag* tag, BaseDocument* doc, BaseObject* op, BaseThread* bt, Int32 priority, EXECUTIONFLAGS flags);
	virtual Bool AddToExecution(BaseTag* tag, PriorityList* list);
	virtual Bool GetModifiedObjects(BaseTag* tag, BaseDocument* doc, BaseObject*& op, Bool& pluginownedop, const Matrix& op_mg, Float lod, Int32 flags, BaseThread* thread);
};

Bool RegisterTagPlugin(Int32 id, const String& str, Int32 info, DataAllocator* g, const String& description, BaseBitmap* icon, Int32 disklevel);

#endif
