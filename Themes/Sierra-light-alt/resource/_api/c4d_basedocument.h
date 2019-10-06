/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DBASEDOCUMENT_H
#define __C4DBASEDOCUMENT_H

#ifdef __API_INTERN__
abc def xyz
#endif

#include "c4d_baselist.h"
#include "c4d_file.h"
#include "c4d_tools.h"
#include "operatingsystem.h"

class BaseTag;
class TextureTag;
class BaseObject;
class BaseMaterial;
class C4DThread;
class BaseSound;

class BaseSceneHook : public BaseList2D
{
private:
	BaseSceneHook();
	~BaseSceneHook();
};

class MultipassObject : public BaseList2D
{
private:
	MultipassObject();
	~MultipassObject();

public:
	MultipassObject* GetNext(void) { return (MultipassObject*)AtCall(GetNext) (); }
	MultipassObject* GetPred(void) { return (MultipassObject*)AtCall(GetPred) (); }
};

class RenderData : public BaseList2D
{
private:
	RenderData();
	~RenderData();

public:
	RenderData* GetNext(void) { return (RenderData*)AtCall(GetNext) (); }
	RenderData* GetPred(void) { return (RenderData*)AtCall(GetPred) (); }
	RenderData* GetDown    (void) { return (RenderData*)AtCall(GetDown) (); }
	RenderData* GetUp      (void) { return (RenderData*)AtCall(GetUp) (); }
	RenderData* GetDownLast(void) { return (RenderData*)AtCall(GetDownLast) (); }

	BaseVideoPost* GetFirstVideoPost();
	void InsertVideoPost(BaseVideoPost* pvp, BaseVideoPost* pred = nullptr);
	void InsertVideoPostLast(BaseVideoPost* pvp);

	MultipassObject* GetFirstMultipass();
	void InsertMultipass(MultipassObject* obj, MultipassObject* pred = nullptr);

	static RenderData* Alloc(void);
	static void Free(RenderData*& v);
};

//---------------------- LAYERS --------------------------------------------------------
class LayerObject : public BaseList2D
{
private:
	LayerObject();
	~LayerObject();

public:
	LayerObject* GetNext    (void) { return (LayerObject*)AtCall(GetNext) (); }
	LayerObject* GetPred    (void) { return (LayerObject*)AtCall(GetPred) (); }
	LayerObject* GetDown    (void) { return (LayerObject*)AtCall(GetDown) (); }
	LayerObject* GetUp      (void) { return (LayerObject*)AtCall(GetUp) (); }
	LayerObject* GetDownLast(void) { return (LayerObject*)AtCall(GetDownLast) (); }

	static LayerObject* Alloc(void);
	static void Free(LayerObject*& v);
};

struct LayerData
{
	Bool	 solo;				// solo mode
	Bool	 view;				// visible in editor view
	Bool	 render;			// visible in render view
	Bool	 manager;			// visible in scene browser, timeline
	Bool	 locked;			// not selectable, nece no modification possible - greyed out in Scene Browser
	Bool	 generators;	// generators on /off
	Bool	 deformers;		// deformers on /off
	Bool	 expressions;	// expressions on /off
	Bool	 animation;		// animation on/off

	Vector color;

	Bool	 xref;	// import with xref

	LayerData()
	{
		view = true;
		render	= true;
		manager	= true;
		locked	= false;
		deformers		= true;
		generators	= true;
		expressions = true;
		animation		= true;
		xref	= true;
		color	= Vector(1.0);
	}
};


//--------------------------------------------------------------------------------------

#define SELECTION_NEW	0
#define SELECTION_ADD	1
#define SELECTION_SUB	2

struct PickSessionDataStruct;

typedef void (*PickSessionCallBack)(Int32 flags, const PickSessionDataStruct* psd);
#define PICKSESSION_FLAG_CANCELED	1

struct PickSessionDataStruct
{
	AtomArray*					active;
	PickSessionCallBack	callback;
	void*								userdata;
	Bool								multi;

	PickSessionDataStruct()
	{
		active = AtomArray::Alloc();
	}
	~PickSessionDataStruct()
	{
		AtomArray::Free(active);
	}
};

class BaseDocument : public BaseList2D
{
private:
	BaseDocument();
	~BaseDocument();

public:
	BaseDocument* GetNext(void) { return (BaseDocument*)AtCall(GetNext) (); }
	BaseDocument* GetPred(void) { return (BaseDocument*)AtCall(GetPred) (); }

	BaseContainer GetData(DOCUMENTSETTINGS type);
	void SetData(DOCUMENTSETTINGS type, const BaseContainer& bc);
	BaseContainer* GetSettingsInstance(Int32 type);

	BaseObject* GetFirstObject(void);
	BaseMaterial* GetFirstMaterial(void);
	RenderData* GetFirstRenderData(void);

	void InsertRenderData(RenderData* rd, RenderData* parent, RenderData* pred);
	void InsertRenderDataLast(RenderData* rd);
	void InsertMaterial(BaseMaterial* mat, BaseMaterial* pred = nullptr, Bool checknames = false);
	void InsertObject(BaseObject* op, BaseObject* parent, BaseObject* pred, Bool checknames = false);

	RenderData* GetActiveRenderData(void);
	BaseObject* GetActiveObject  (void);
	BaseMaterial* GetActiveMaterial(void);
	BaseTag* GetActiveTag     (void);
	BaseObject* GetRealActiveObject(AtomArray* help, Bool* multi);

	void GetActiveObjects  (AtomArray& selection, GETACTIVEOBJECTFLAGS flags) const;
	void GetActivePolygonObjects(AtomArray& selection, Bool children) const;
	void GetActiveObjectsFilter(AtomArray& selection, Bool children, Int32 type, Int32 instanceof) const;
	void GetActiveTags     (AtomArray& selection) const;
	void GetActiveMaterials(AtomArray& selection) const;
	void GetSelection      (AtomArray& selection) const;

	void SetActiveObject    (BaseObject* op, Int32 mode = SELECTION_NEW);
	void SetActiveTag       (BaseTag* tag, Int32 mode = SELECTION_NEW);
	void SetActiveMaterial  (BaseMaterial* mp, Int32 mode = SELECTION_NEW);
	void SetActiveRenderData(RenderData* rd);
	void SetSelection       (BaseList2D* bl, Int32 mode = SELECTION_NEW);

	void Flush(void);

	BaseObject* GetHighest(Int32 type, Bool editor);

	BaseMaterial* SearchMaterial   (const String& str);
	BaseMaterial* SearchMaterialInc(const String& str);
	BaseObject* SearchObject     (const String& str);
	BaseObject* SearchObjectInc  (const String& str);

	BaseObject* GetHelperAxis(void);

	BaseContainer	GetAllTextures(const AtomArray* ar);

	Bool GetChanged(void);
	void SetChanged(void);

	Filename GetDocumentName(void);
	Filename GetDocumentPath(void);
	void SetDocumentName(const Filename& fn);
	void SetDocumentPath(const Filename& path);

	Float	GetLOD(void);
	void SetLOD(Float lod);

	Int32	GetFps(void) const;
	void SetFps(Int32 fps);

	BaseTime GetMinTime(void);
	void SetMinTime(const BaseTime& t);

	BaseTime GetMaxTime(void);
	void SetMaxTime(const BaseTime& t);

	BaseTime GetUsedMinTime(BaseList2D* check);
	BaseTime GetUsedMaxTime(BaseList2D* check);

	BaseTime GetLoopMinTime(void);
	void SetLoopMinTime(const BaseTime& t);

	BaseTime GetLoopMaxTime(void);
	void SetLoopMaxTime(const BaseTime& t);

	Bool GetRenderLod(void);
	void SetRenderLod(Bool lod);

	BaseTime GetTime(void);
	void SetTime(const BaseTime& t);

	Int32	GetMode(void);
	void SetMode(Int32 m);

	Int32	GetAction(void);
	void SetAction(Int32 a);

	Bool IsEditMode(void);

	Bool StartUndo(void);
	Bool EndUndo(void);
	Bool AddUndo(UNDOTYPE type, void* data, Bool allowFromThread = false);
	Bool AddUndo(BaseDraw* bd);
	Bool DoUndo(Bool multiple = false);
	Bool DoRedo(void);
	void FlushUndoBuffer(void) { C4DOS.Bd->FlushUndoBuffer(this); }
	BaseList2D* GetUndoPtr() { return C4DOS.Bd->GetUndoPtr(this); }
	BaseList2D* FindUndoPtr(BaseList2D* bl, UNDOTYPE type) { return C4DOS.Bd->FindUndoPtr(this, bl, type); }
	void AutoKey(BaseList2D* undo, BaseList2D* op, Bool recursive, Bool pos, Bool scale, Bool rot, Bool param, Bool pla) { C4DOS.Bd->AutoKey(this, undo, op, recursive, pos, scale, rot, param, pla); }
	Bool RecordKey(BaseList2D* op, const BaseTime& time, const DescID& id, BaseList2D* undo, Bool eval_attribmanager, Bool autokeying, Bool allow_linking){ return C4DOS.Bd->RecordKey(this, op, time, id, undo, eval_attribmanager, autokeying, allow_linking); }
	void Record(void) { C4DOS.Bd->Record(this); }

	void AnimateObject(BaseList2D* op, const BaseTime& time, ANIMATEFLAGS flags);

	BaseDocument* Polygonize(Bool keepanimation = false);

	BaseDraw* GetActiveBaseDraw(void);
	BaseDraw* GetRenderBaseDraw(void);
	BaseDraw* GetBaseDraw(Int32 num);
	Int32	GetBaseDrawCount();
	Int32 GetSplinePlane(void);

	void SetRewind(Int32 flags = 0);

	BaseSceneHook* FindSceneHook(Int32 id) const { return C4DOS.Bd->FindSceneHook(this, id); }

	static BaseDocument* Alloc(void);
	static void Free(BaseDocument*& v);

	Bool IsCacheBuilt(Bool force = false) { return C4DOS.Bd->IsCacheBuilt(this, force); }

	void ForceCreateBaseDraw(void);

	// layers
	GeListHead* GetLayerObjectRoot(void);
	Bool HandleSelectedTextureFilename(BaseChannel* bc, const Filename& fn, Filename* resfilename, Bool undo, GEMB_R* already_answered);
	Bool ReceiveMaterials  (BaseObject* op, AtomArray* mat, Bool clearfirst);
	Bool ReceiveNewTexture (BaseObject* op, const Filename& filename, Bool sdown, GEMB_R* already_answered);

	Bool CollectSounds(BaseSound* snd, const BaseTime& from, const BaseTime& to);
	// only internal!!!
	void RecordZero(void) { C4DOS.Bd->RecordZero(this); }
	void RecordNoEvent(void) { C4DOS.Bd->RecordNoEvent(this); }

	Int32 GetDrawTime() { return C4DOS.Bd->GetDrawTime(this); }

	// compute expressions, caches etc
	Bool ExecutePasses(BaseThread* bt, Bool animation, Bool expressions, Bool caches, BUILDFLAGS flags);

	const PickSessionDataStruct* GetPickSession() const;
	void StartPickSession(PickSessionDataStruct* psd);
	void StopPickSession(Bool cancel);

	Bool GetDefaultKey(CKey* pKey, Bool& bOverdub) const;
	void SetDefaultKey(CKey* pKey, Bool bOverdub);

	void SendInfo(Int32 type, Int32 format, const Filename& fn, BaseList2D* bl, Bool hooks_only) { return C4DOS.Bd->SendInfo(this, type, format, fn, bl, hooks_only); }

	void SetHighlightedObject(BaseObject* op, Int32 mode = SELECTION_NEW);
	void SetHighlightedObjects(AtomArray& selection, Int32 mode = SELECTION_NEW);
	void GetHighlightedObjects(AtomArray& selection) const;

	Bool IsAxisEnabled(void);

	BaseBitmap* GetDocPreviewBitmap();
};

class Hierarchy
{
private:
	BaseDocument* doc;
	BaseThread*		bt;

public:
	virtual void* Alloc(void) = 0;
	virtual void Free(void* data) = 0;
	virtual void CopyTo(void* src, void* dst) = 0;
	virtual Bool Do(void* data, BaseObject* op, const Matrix& mg, Bool controlobject) = 0;

	Bool Run(BaseDocument* doc, Bool spheres, Float lod, Bool uselod, BUILDFLAGS flags, void* startdata, BaseThread* bt);
};

class PriorityList
{
private:
	PriorityList();
	~PriorityList();

public:
	void Add(GeListNode* node, Int32 priority, EXECUTIONFLAGS flags) { C4DOS.Bd->PrAdd(this, node, priority, flags); }
};

BaseDocument* GetActiveDocument(void);
BaseDocument* GetFirstDocument(void);
Bool LoadFile(const Filename& name);

void InsertBaseDocument	(BaseDocument* doc);
void SetActiveDocument	(BaseDocument* doc);
void KillDocument				(BaseDocument*& doc);

BaseDocument* LoadDocument(const Filename& name, SCENEFILTER loadflags, BaseThread* thread, String* errorString = nullptr);
Bool MergeDocument(BaseDocument* doc, const Filename& name, SCENEFILTER loadflags, BaseThread* thread, String* errorString = nullptr);

Bool SaveDocument(BaseDocument* doc, const Filename& name, SAVEDOCUMENTFLAGS saveflags, Int32 format);

BaseDocument*	IsolateObjects(BaseDocument* doc, const AtomArray& t_objects);

RENDERRESULT RenderDocument(BaseDocument* doc, const BaseContainer& rdata, ProgressHook* prog, void* private_data, BaseBitmap* bmp, RENDERFLAGS renderflags, BaseThread* th, WriteProgressHook* wprog = nullptr, void* data = nullptr);

Bool SaveProject(BaseDocument* doc, SAVEPROJECT flags, Filename targetPath, maxon::BaseArray<AssetEntry>* assets = nullptr, maxon::BaseArray<AssetEntry>* missingAssets = nullptr);
Bool GetAllAssets(BaseDocument* doc, Bool allowDialogs, maxon::BaseArray<AssetEntry>& assets, Filename& lastPath);

// editor modes
enum
{
	Mcamera				 = 0,
	Mobject				 = 1,
	Mtexture			 = 3,
	Mtextureaxis	 = 4,
	Mpoints				 = 5,
	Medges				 = 6,
	Mpolygons			 = 7,
	Manimation		 = 9,
	Mkinematic		 = 10,
	Mmodel				 = 11,
	Mpaint				 = 12,
	Muvpoints			 = 13,
	Muvpolygons		 = 14,
	Mpolyedgepoint = 15,	// private
	Medgepoint		 = 16,	// private
	Mworkplane		 = 17,
	Mdrag					 = 1000	// for dragging of handles
};

Bool InteractiveModeling_Rewind(BaseDocument* doc);
Bool InteractiveModeling_Restart(BaseDocument* doc);

void RunAnimation(BaseDocument* doc, Bool forward, Bool stop);
void SetDocumentTime(BaseDocument* doc, const BaseTime& time);
Bool CloseAllDocuments();
Bool StopExternalRenderer();

#endif
