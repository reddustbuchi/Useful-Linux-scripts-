/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DOBJECTDATA_H
#define __C4DOBJECTDATA_H

#include "c4d_nodedata.h"
#include "operatingsystem.h"

class	SplineObject;
class	BaseBitmap;
class	BaseDraw;
class	BaseDrawHelp;
class	Particle;
class	BaseThread;
class	HierarchyHelp;
class	BaseObject;
class	PriorityList;
class	BaseDraw;
struct	BaseParticle;

enum HANDLECONSTRAINTTYPE
{
	HANDLECONSTRAINTTYPE_INVALID	 = -1,
	HANDLECONSTRAINTTYPE_LINEAR		 = 0,
	HANDLECONSTRAINTTYPE_PLANAR		 = 1,
	HANDLECONSTRAINTTYPE_FREE			 = 2,
	HANDLECONSTRAINTTYPE_RADIAL		 = 3,
	HANDLECONSTRAINTTYPE_SPHERICAL = 4
} ENUM_END_LIST(HANDLECONSTRAINTTYPE);

class HandleInfo
{
public:
	HandleInfo(void)
	{
		position	= Vector(0.0);
		direction = Vector(0.0);
		center = Vector(0.0);
		radius = 100.0;
		type = HANDLECONSTRAINTTYPE_LINEAR;
	}
	~HandleInfo(void)
	{

	}

	Vector							 position;
	Vector							 direction;
	Vector							 center;
	Float								 radius;
	HANDLECONSTRAINTTYPE type;

	Vector CalculateNewPosition(BaseDraw* bd, const Matrix& mg, const Vector& mouse_pos) const;
};

class ObjectData : public NodeData
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

	virtual void GetDimension(BaseObject* op, Vector* mp, Vector* rad);
	virtual DRAWRESULT Draw(BaseObject* op, DRAWPASS drawpass, BaseDraw* bd, BaseDrawHelp* bh);
	virtual DRAWRESULT DrawShadow(BaseObject* op, BaseDraw* bd, BaseDrawHelp* bh);
	virtual Int32 DetectHandle(BaseObject* op, BaseDraw* bd, Int32 x, Int32 y, QUALIFIER qualifier);
	virtual Bool MoveHandle(BaseObject* op, BaseObject* undo, const Vector& mouse_pos, Int32 hit_id, QUALIFIER qualifier, BaseDraw* bd);
	virtual Bool AddToExecution(BaseObject* op, PriorityList* list);
	virtual EXECUTIONRESULT Execute(BaseObject* op, BaseDocument* doc, BaseThread* bt, Int32 priority, EXECUTIONFLAGS flags);
	virtual void GetModelingAxis(BaseObject* op, BaseDocument* doc, Matrix& axis);

	// generator
	virtual BaseObject* GetVirtualObjects(BaseObject* op, HierarchyHelp* hh);

	// modifier
	virtual Bool ModifyObject(BaseObject* mod, BaseDocument* doc, BaseObject* op, const Matrix& op_mg, const Matrix& mod_mg, Float lod, Int32 flags, BaseThread* thread);
	virtual void CheckDirty(BaseObject* op, BaseDocument* doc);

	// spline
	virtual SplineObject* GetContour(BaseObject* op, BaseDocument* doc, Float lod, BaseThread* bt);

	// particle
	virtual void ModifyParticles(BaseObject* op, Particle* pp, BaseParticle* ss, Int32 pcnt, Float diff);

	// helper routines
	virtual Int32 GetHandleCount(BaseObject* op);
	virtual void GetHandle(BaseObject* op, Int32 i, HandleInfo& info);
	virtual void SetHandle(BaseObject* op, Int32 i, Vector p, const HandleInfo& info);
};

Bool RegisterObjectPlugin(Int32 id, const String& str, Int32 info, DataAllocator* g, const String& description, BaseBitmap* icon, Int32 disklevel);

#endif
