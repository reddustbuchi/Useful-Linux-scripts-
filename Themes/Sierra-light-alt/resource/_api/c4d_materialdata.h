/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DMATERIALDATA_H
#define __C4DMATERIALDATA_H

#include "c4d_nodedata.h"
#include "operatingsystem.h"

class BaseMaterial;
class BaseObject;
class BaseDraw;
class BaseDrawHelp;
class BaseDocument;
class BaseBitmap;
class String;
class BaseTag;
class BaseThread;
struct InitRenderStruct;
struct VolumeData;

#define PLUGINFLAG_MATERIAL_GLIMAGE									(1 << 0)
#define PLUGINFLAG_MATERIAL_NO_MATERIALEDITOR				(1 << 1)
#define PLUGINFLAG_MATERIAL_HIDE_IN_MATERIALMANAGER	(1 << 2)
#define PLUGINFLAG_MATERIAL_GLIMAGE_TIMECHANGE			(1 << 3)
#define PLUGINFLAG_MATERIAL_GLIMAGE_WITH_ALPHA			((1 << 0) | (1 << 3))	/* implies PLUGINFLAG_MATERIAL_GLIMAGE*/

class MaterialData : public NodeData
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

	virtual	Bool Draw(BaseMaterial* mat, BaseObject* op, BaseTag* tag, BaseDraw* bd, BaseDrawHelp* bh);

	virtual	VOLUMEINFO GetRenderInfo(BaseMaterial* mat);

	virtual	INITRENDERRESULT InitRender(BaseMaterial* mat, const InitRenderStruct& irs);
	virtual	void FreeRender(BaseMaterial* mat);

	virtual	void InitCalculation(BaseMaterial* mat, VolumeData* vd, INITCALCULATION type);
	virtual	void Displace(BaseMaterial* mat, VolumeData* vd);
	virtual	void ChangeNormal(BaseMaterial* mat, VolumeData* vd);
	virtual	void CalcSurface(BaseMaterial* mat, VolumeData* vd);
	virtual	void CalcTransparency(BaseMaterial* mat, VolumeData* vd);
	virtual	void CalcAlpha(BaseMaterial* mat, VolumeData* vd);
	virtual	void CalcVolumetric(BaseMaterial* mat, VolumeData* vd);
	virtual Bool InitGLImage(BaseMaterial* mat, BaseDocument* doc, BaseThread* th, BaseBitmap* bmp, Int32 doccolorspace, Bool linearworkflow);
	virtual GL_MESSAGE GlMessage(BaseMaterial* mat, Int32 type, void* data);
};

Bool RegisterMaterialPlugin(Int32 id, const String& str, Int32 info, DataAllocator* g, const String& description, Int32 disklevel, void* emulation = nullptr);

#endif
