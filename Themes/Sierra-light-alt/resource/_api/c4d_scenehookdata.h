/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4D_SCENEHOOKDATA_H
#define __C4D_SCENEHOOKDATA_H

#include "c4d_nodedata.h"
#include "operatingsystem.h"

class String;
class BaseContainer;
class BaseBitmap;
class BaseDocument;
class BaseObject;
class BaseDraw;
class BaseDrawHelp;
class BaseThread;
class CDialog;
class PriorityList;
class EditorWindow;
class BaseSceneHook;
struct ControlDisplayStruct;

#define PLUGINFLAG_SCENEHOOK_NOTDRAGGABLE									(1 << 0)
#define PLUGINFLAG_SCENEHOOK_SUPPORT_DOCUMENT_DESCRIPTION	(1 << 1)
#define PLUGINFLAG_SCENEHOOK_SUPPORT_ANIMATION						(1 << 2)

class SceneHookData : public NodeData
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

	virtual Bool MouseInput			(BaseSceneHook* node, BaseDocument* doc, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg);
	virtual Bool KeyboardInput	(BaseSceneHook* node, BaseDocument* doc, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg);
	virtual Bool GetCursorInfo	(BaseSceneHook* node, BaseDocument* doc, BaseDraw* bd, Float x, Float y, BaseContainer& bc);
	virtual Bool Draw						(BaseSceneHook* node, BaseDocument* doc, BaseDraw* bd, BaseDrawHelp* bh, BaseThread* bt, SCENEHOOKDRAW flags);
	virtual Bool DisplayControl (BaseDocument* doc, BaseObject* op, BaseObject* chainstart, BaseDraw* bd, BaseDrawHelp* bh, ControlDisplayStruct& cds);
	virtual Bool InitDisplayControl(BaseSceneHook* node, BaseDocument* doc, BaseDraw* bd, const AtomArray* active);
	virtual void FreeDisplayControl(void);

	virtual Bool AddToExecution (BaseSceneHook* node, PriorityList* list);
	virtual EXECUTIONRESULT InitSceneHook	(BaseSceneHook* node, BaseDocument* doc, BaseThread* bt);
	virtual void FreeSceneHook	(BaseSceneHook* node, BaseDocument* doc);
	virtual EXECUTIONRESULT Execute(BaseSceneHook* node, BaseDocument* doc, BaseThread* bt, Int32 priority, EXECUTIONFLAGS flags);
};

Bool RegisterSceneHookPlugin(Int32 id, const String& str, Int32 info, DataAllocator* g, Int32 priority, Int32 disklevel, void* emulation = nullptr);

#endif
