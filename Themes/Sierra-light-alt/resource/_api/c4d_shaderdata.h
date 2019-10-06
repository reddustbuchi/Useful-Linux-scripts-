/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DSHADERDATA_H
#define __C4DSHADERDATA_H

#include "ge_prepass.h"
#include "c4d_nodedata.h"
#include "operatingsystem.h"

class BaseShader;
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
struct ChannelData;

class ShaderData : public NodeData
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

	// for use with glProgramFactory::GetDescriptionData
	//static void* AllocCgDescription();
	//static void FreeCgDescription(void* pData);
	//static Bool ReadCgDescription(GlReadDescriptionData* pFile, void* pData);
	//static Bool WriteCgDescription(GlWriteDescriptionData* pFile, const void* pData);
	//

	virtual	Bool Draw(BaseShader* sh, BaseObject* op, BaseTag* tag, BaseDraw* bd, BaseDrawHelp* bh);

	virtual	SHADERINFO GetRenderInfo(BaseShader* sh);

	virtual	INITRENDERRESULT InitRender(BaseShader* sh, const InitRenderStruct& irs);
	virtual	void FreeRender(BaseShader* sh);

	virtual	Vector Output(BaseShader* sh, ChannelData* cd);
	virtual GL_MESSAGE GlMessage(BaseShader* sh, Int32 type, void* msgdata);
	virtual Int32 InitGLImage(BaseShader* sh, BaseDocument* doc, BaseThread* th, BaseBitmap* bmp, Bool alpha, Int32 doccolorspace, Bool linearworkflow);
	virtual void DestroyGLImage(BaseShader* sh, BaseDocument* doc);
	virtual void InvalidateGLImage(BaseShader* sh, BaseDocument* doc);
	virtual Bool GetGLImageSize(BaseShader* sh, BaseDocument* doc, Int32 s, Bool noScale, Int32& w, Int32& h);

	virtual BaseShader* GetSubsurfaceShader(BaseShader* sh, Float& bestmpl);
};

Bool RegisterShaderPlugin(Int32 id, const String& str, Int32 info, DataAllocator* g, const String& description, Int32 disklevel, void* emulation = nullptr);

#endif
