/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4D_FILTERDATA_H
#define __C4D_FILTERDATA_H

#include "c4d_nodedata.h"
#include "c4d_file.h"

class Filename;
class String;
class BaseContainer;
class BaseDocument;
class BaseBitmap;
class BaseSceneLoader;
class BaseSceneSaver;
class PluginMovieData;
class BaseThread;
class BaseSound;

#define PLUGINFLAG_BITMAPLOADER_MOVIE	(1 << 6)

struct BitmapLoaderAnimatedData
{
	BitmapLoaderAnimatedData()
	{
		Int32 i; for (i = 0; i < 16; i++)
			moviedata[i] = nullptr;
	}

	Filename moviename;
	void*		 moviedata[16];
};

enum BITMAPLOADERACTION
{
	BITMAPLOADERACTION_INIT	= 1,
	BITMAPLOADERACTION_LOAD	= 2,
	BITMAPLOADERACTION_FREE	= 3
} ENUM_END_LIST(BITMAPLOADERACTION);

class BitmapLoaderData : public BaseData
{
public:
	virtual Bool Identify(const Filename& name, UChar* probe, Int32 size) = 0;
	virtual IMAGERESULT Load(const Filename& name, BaseBitmap* bm, Int32 frame) = 0;
	virtual Int32 GetSaver(void);
	virtual Bool GetInformation(const Filename& name, Int32* frames, Float* fps);
	virtual IMAGERESULT LoadAnimated(BitmapLoaderAnimatedData* bd, BITMAPLOADERACTION action, BaseBitmap* bm, Int32 frame);
	virtual IMAGERESULT ExtractSound(BitmapLoaderAnimatedData* bd, BaseSound* snd);
	virtual IMAGERESULT HasSound(BitmapLoaderAnimatedData* bd);
};

#define PLUGINFLAG_BITMAPSAVER_SUPPORT_8BIT					 (1 << 1)
#define PLUGINFLAG_BITMAPSAVER_SUPPORT_16BIT				 (1 << 2)
#define PLUGINFLAG_BITMAPSAVER_SUPPORT_32BIT				 (1 << 0)
#define PLUGINFLAG_BITMAPSAVER_SUPPORT_8BIT_LAYERS	 (1 << 3)
#define PLUGINFLAG_BITMAPSAVER_SUPPORT_16BIT_LAYERS	 (1 << 4)
#define PLUGINFLAG_BITMAPSAVER_SUPPORT_32BIT_LAYERS	 (1 << 5)
#define PLUGINFLAG_BITMAPSAVER_MOVIE								 (1 << 6)
#define PLUGINFLAG_BITMAPSAVER_SUPPORT_COLORPROFILES (1 << 7)

#define PLUGINFLAG_BITMAPSAVER_ALLOWOPTIONS	(1 << 27)
#define PLUGINFLAG_BITMAPSAVER_FORCESUFFIX	(1 << 26)

class BitmapSaverData : public BaseData
{
public:
	virtual IMAGERESULT Save(const Filename& name, BaseBitmap* bm, BaseContainer* data, SAVEBIT savebits);
	virtual Bool Edit(BaseContainer* data);
	virtual Int32 GetMaxAlphas(BaseContainer* data);
	virtual Int32 GetMaxResolution(Bool layers);

	// additional calls for movie saver
	virtual IMAGERESULT Open(PluginMovieData*& md, const Filename& name, BaseBitmap* bm, BaseContainer* data, SAVEBIT savebits, Int32 fps);
	virtual IMAGERESULT Write(PluginMovieData* md, BaseBitmap* bm);
	virtual void Close(PluginMovieData*& md);
	virtual IMAGERESULT AddSound(PluginMovieData* md, BaseSound* snd);
};

#define PLUGINFLAG_SCENELOADER_MERGEORIGINAL (1 << 26)
#define PLUGINFLAG_SCENEFILTER_DIALOGCONTROL (1 << 27)

class SceneLoaderData : public NodeData
{
public:
	virtual Bool Identify(BaseSceneLoader* node, const Filename& name, UChar* probe, Int32 size) = 0;
	virtual FILEERROR Load(BaseSceneLoader* node, const Filename& name, BaseDocument* doc, SCENEFILTER filterflags, String* error, BaseThread* bt) = 0;

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
};

class SceneSaverData : public NodeData
{
public:
	virtual FILEERROR Save(BaseSceneSaver* node, const Filename& name, BaseDocument* doc, SCENEFILTER filterflags) = 0;

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
};

Bool RegisterBitmapLoaderPlugin(Int32 id, const String& str, Int32 info, BitmapLoaderData* dat);
Bool RegisterBitmapSaverPlugin(Int32 id, const String& str, Int32 info, BitmapSaverData* dat, const String& suffix);
Bool RegisterSceneLoaderPlugin(Int32 id, const String& str, Int32 info, DataAllocator* g, const String& description, void* emulation = nullptr);
Bool RegisterSceneSaverPlugin(Int32 id, const String& str, Int32 info, DataAllocator* g, const String& description, const String& suffix, void* emulation = nullptr);

#endif
