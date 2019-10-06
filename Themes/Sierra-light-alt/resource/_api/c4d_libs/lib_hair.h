/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __LIB_HAIR_H__
#define __LIB_HAIR_H__

#include "c4d_library.h"

#ifdef __API_INTERN__
#include "pluginobject.h"
#include "plugintag.h"
#include "pluginvideopost.h"
#else
#include "c4d_baseobject.h"
#include "c4d_basetag.h"
#include "c4d_videopost.h"
#endif

//////////////////////////////////////////////////////////////////////////

class ChainBase;
class HairManager;

//////////////////////////////////////////////////////////////////////////

#define Ohair						1017305
#define Thairselection	1017746
#define Thairvertex			1018329
#define VPhair					1017325
#define Mhair						1017730
#define Thairmaterial		1017729
#define Thaircollider		1017326
#define Thairtangent		1017671
#define Thairlight			1017874

//////////////////////////////////////////////////////////////////////////

#define HAIR_ROOT_TYPE_INVALID	 -1
#define HAIR_ROOT_TYPE_NONE				0
#define HAIR_ROOT_TYPE_VERTEX			1
#define HAIR_ROOT_TYPE_POLY				2
#define HAIR_ROOT_TYPE_SEGMENT		3
#define HAIR_ROOT_TYPE_SPLINE2D		4
#define HAIR_ROOT_TYPE_SPLINE3D		5
#define HAIR_ROOT_TYPE_GUIDES			6
#define HAIR_ROOT_TYPE_NULL				7
#define HAIR_ROOT_TYPE_CLONE			8

#define HAIR_GENERATE_FLAGS_NONE			0
#define HAIR_GENERATE_FLAGS_NO_MATERIAL		(1<<0)
#define HAIR_GENERATE_FLAGS_NO_DYNAMICS		(1<<1)
#define HAIR_GENERATE_FLAGS_NO_TRANSFORM	(1<<2)
#define HAIR_GENERATE_FLAGS_NO_DEFORMERS	(1<<3)

#define HAIR_MODE_LOCKED	-2
#define HAIR_MODE_HIDDEN	-1

#define HAIR_MODE_TIPS		0
#define HAIR_MODE_POINTS	1
#define HAIR_MODE_GUIDES	2
#define HAIR_MODE_ROOTS		3
#define HAIR_MODE_VERTEX	4

#define HAIR_MPARAMETER_THICKNESS			1
#define HAIR_MPARAMETER_COLOR					2
#define HAIR_MPARAMETER_BACKCOLOR			3
#define HAIR_MPARAMETER_TRANSPARENCY	4

#define HAIR_LOCK_FLAGS_ANIMATING			(1<<2)
#define HAIR_LOCK_FLAGS_FULL_UPDATE		(1<<4)
#define HAIR_LOCK_FLAGS_NO_TRANSFORM	(1<<5)

//////////////////////////////////////////////////////////////////////////
class Neighbor;
class HairGuides;
class HairObject;
class iHairCollider;
class HairColliderData;

struct HairRootData
{
	HairRootData() { m_Type=HAIR_ROOT_TYPE_INVALID; }

	Int32	m_ID,m_Type;
	Float	m_S,m_T;
	Vector	m_P,m_N;
};

struct HairPolygonHit
{
	BaseObject *m_pObject;	// object that was hit

	Int32 m_gID;				// guide ID
	Int32 m_sID;				// segment ID
	Float m_sT;				// position along segment;

	Int32 m_ID;				// polygon index
	Vector m_P;				// hit point

	Vector m_Vin,m_Vout;	// velocity in/out of hit
	Float	m_T;			// frame delta of hit
};

struct RootObjectData
{
	BaseObject *pObject;
	BaseTag *pTag;

	Neighbor *pNeighbor;

	const Vector *pPoint;
	const Vector *pOriginPoints;

	const CPolygon *pPolygon;
	const Segment *pSegment;
};

class HairGuideWeight
{
public:
	HairGuideWeight() { m_Index=NOTOK; m_Weight=0.0; }

	Int32 m_Index;
	Float m_Weight;
};

class HairInterpolationMap
{
	friend class ChainBase;
	friend class HairManager;

public:
	HairInterpolationMap()
	{
		m_pMap=nullptr;
		m_GuideCount=0;
		m_Count=0;
		m_WeightCount=0;
	}
	~HairInterpolationMap()
	{
		Free();
	}

	void Free()
	{
		DeleteMem(m_pMap);
		m_GuideCount=0;
		m_Count=0;
		m_WeightCount=0;
	}

	HairGuideWeight *GetMap() { return m_pMap; }
	HairGuideWeight *GetGuides(Int32 index)
	{
		if (!m_pMap) return nullptr;
		return &m_pMap[index*m_WeightCount];
	}
	Int32 GetHairCount() { return m_Count; }
	Int32 GetGuideCount() { return m_GuideCount; }
	Int32 GetWeightCount() { return m_WeightCount; }

	Float64 GetTotalWeight(Int32 index);
	Float64 GetTotalInvWeight(Int32 index);

	Float64 GetInterpolateReal(Int32 index, Float64 *v);
	Float32 GetInterpolateReal(Int32 index, Float32 *v);
	Vector32 GetInterpolatedVector(Int32 index, Vector32 *v);
	Vector64 GetInterpolatedVector(Int32 index, Vector64 *v);

private:

	HairGuideWeight *m_pMap;

	Int32 m_WeightCount;
	Int32 m_GuideCount;
	Int32 m_Count;
};

//////////////////////////////////////////////////////////////////////////

class HairMaterialData
{
private:
	HairMaterialData();
	~HairMaterialData();
public:
	Int32 GetCount();
	Int32 GetGuideMaterial(Int32 i, Int32 prev=NOTOK);

	BaseTag *GetMaterialTag(Int32 i);

	Bool ApplyMaterial(Int32 i, HairGuides *guides, VolumeData *vd=nullptr, Int32 vindex=0);
	Bool ApplyMaterials(HairGuides *guides, VolumeData *vd=nullptr, Int32 vindex=0);

	Float GetThickness(Int32 guide, Float t, Int32 i=NOTOK);
	Vector GetColor(Int32 guide, Float t, const Vector &r, const Vector &wp, const Vector &p, const Vector &n, VolumeData *vd, const RayHitID &plyid, Int32 i=NOTOK);
	Vector GetBackColor(Int32 guide, Float t, const Vector &col, const Vector &r, const Vector &wp, const Vector &p, const Vector &n, VolumeData *vd, const RayHitID &plyid, Int32 i=NOTOK);
	Bool GetSpecularColor(Int32 guide, Float t, const Vector &wp, const Vector &p, const Vector &n, VolumeData *vd, const RayHitID &plyid, Vector &speccol, Vector &ispeccol);
	Float GetTransparency(Int32 guide, Float t, const Vector &p, const Vector &n, VolumeData* vd, Int32 i=NOTOK);

	Bool GetTagSelection(Int32 i, BaseSelect *bs);

	Bool GetMaterialData(Int32 guide, Float &shadows, Float &selfshadows, Float &backshadows, Float &transparency, Float &diffuse, Float &reflect, Float &transmit, Bool &roughenable, Float &roughvar, Float &roughness, Bool &specularenable, Float &specular, Float &specularpower, Float &specularback, Bool &ispecularenable, Bool &ispecularshader, Float &ispecular, Float &ispecularpower, Float &ispecularmix, Float &ispecularblend);
	Bool GetGIData(Int32 guide, Bool &receive, Float &strength);
	Bool AdjustHUV(Int32 guide, Vector &huv, Float tline);
};

class HairGuideDynamics
{
private:
	HairGuideDynamics();
	~HairGuideDynamics();
public:
	HairGuides *GetGuides();

	Vector GetPosition(Int32 i);
	void SetPosition(Int32 i, const Vector &p);

	Vector GetLastPosition(Int32 i);
	void SetLastPosition(Int32 i, const Vector &p);

	Vector GetVelocity(Int32 i);
	void SetVelocity(Int32 i, const Vector &v);

	Float GetMass(Int32 i);
	void SetMass(Int32 i, Float m);

	Vector GetForce(Int32 i);
	void AddForce(Int32 i, const Vector &f);

	Int32 GetPolygonIntersections(HairPolygonHit **hits);	// returned 'hits' need to be free'd with DeleteMem, returns the number of hits or NOTOK for an error
};

#define HAIR_GUIDE_FLAGS_LOCAL		(1<<0)	// chains are in local object space
#define HAIR_GUIDE_FLAGS_AS_GUIDES	(1<<1)	// special case guides
#define HAIR_GUIDE_FLAGS_INITIAL	(1<<3)	// chains are in their original initial space (like a sticktexturetag)
#define HAIR_GUIDE_FLAGS_HAIRS		(1<<4)	// created for hairs
#define HAIR_GUIDE_FLAGS_INITIALAXIS	(1<<6)	// initial space and root axis aligned

class HairGuides
{
private:
	HairGuides();
	~HairGuides();
public:
	static HairGuides *Alloc(Int32 count, Int32 segments);
	static void Free(HairGuides *&guides);

	Int32 GetCount();	// number of guides
	Int32 GetSegmentCount();	// number of segments per guide (number of points is +1)
	Int32 GetPointCount() { return GetCount()*GetGuidePointCount(); }
	Int32 GetGuidePointCount() { Int32 s=GetSegmentCount(); return (s==0)?0:(s+1); }	// number of points per segment

	Vector *GetPoints();	// get a pointer to the point vectors for the guides
	HairGuideDynamics *GetDynamics();	// get the dynamics (can be nullptr)

	Matrix GetMg();
	void SetMg(const Matrix &mg);

	HairRootData GetRoot(Int32 index);
	void SetRoot(Int32 index, const HairRootData &root, Bool update);

	HairObject *GetObject();

	Bool GetSelected(Int32 mode, BaseSelect *select);
	Bool SetSelected(Int32 mode, BaseSelect *select);
	Bool ConvertSelection(Int32 from_mode, Int32 to_mode, BaseSelect *from_select, BaseSelect *to_select);

	Bool CopyFrom(const HairGuides *src);

	Vector GetTangent(Int32 guide, Int32 segment, Float t);

	SplineObject *CreateSpline();

	void ToLocal();
	void ToWorld();
	void ToInitial(Bool align);

	void UndisplaceRoots();
	void DisplaceRoots();

	Bool GetRootAxis(Int32 index, Matrix &m, Bool bAlign=false, Bool bLocal=true, Bool bInitial=false, Bool bZAxis=false);
	Vector GetRootUV(Int32 index);

	Bool GetRootData(Int32 index, Vector *p=nullptr, Vector *n=nullptr, Int32 *ply_id=nullptr, Bool bLocal=true, Bool bDisplaced=true, Bool bInitial=false);

	Matrix *GetTransformMatrix();
	void SetTransformMatrix(Matrix *tm);

	Bool Delete(BaseSelect *bs);
	Bool AddRoot(Int32 ply_id, Float s, Float t, Float len);

	Bool GetRootObject(RootObjectData *pData);

	Bool LinkToObject(HairObject *pHair);

	Int32 GetFlags();
	Int32 SetFlags(Int32 flags);
};

class HairObject : public BaseObject
{
#ifndef __API_INTERN__
private:
	HairObject();
	~HairObject();
public:
	static HairObject *Alloc() { return (HairObject*)BaseObject::Alloc(Ohair); }
	static void Free(HairObject *&pObject) { BaseObject *op=pObject; BaseObject::Free(op); pObject=nullptr; }

	Bool Lock(BaseDocument *pDoc, BaseThread *pThread, Bool bValidate, Int32 flags);
	Bool IsLocked();
	void Unlock();

#else
public:
#endif

	HairGuides *GetGuides();
	HairGuides *GetDynamicGuides();
	HairGuides *GenerateHair(Int32 flags=HAIR_GENERATE_FLAGS_NONE, Int32 count=NOTOK, Int32 segments=NOTOK, HairMaterialData **pMaterial=nullptr, HairInterpolationMap *pMap=nullptr);

	Bool GetRootObject(BaseObject **pObject, BaseTag **pTag, RootObjectData *pData);

	Bool SetGuides(HairGuides *guides, Bool clone);
	void RemoveGuides();

	Bool Update(BaseDocument *doc);	// do NOT use within a Lock()

	HairMaterialData *InitMaterials(const InitRenderStruct &irs, BaseDocument *pDoc, HairGuides *guides=nullptr, VolumeData *vd=nullptr);
	void FreeMaterials(HairMaterialData *&pMaterials);
};

class HairVertexMapTag : public BaseTag
{
#ifndef __API_INTERN__
private:
	HairVertexMapTag();
	~HairVertexMapTag();
public:
	static HairVertexMapTag *Alloc() { return (HairVertexMapTag*)BaseTag::Alloc(Thairvertex); }
	static void Free(HairVertexMapTag *&pTag) { BaseTag *tag=pTag; BaseTag::Free(tag); pTag=nullptr; }
#else
public:
#endif

	Int32 GetCount();
	Int32 GetSegments();
	Int32 GetPointCount();
	UInt16 *GetMap();				// to get the real value divide by 65535.0
};

class HairSelectionTag : public BaseTag
{
#ifndef __API_INTERN__
private:
	HairSelectionTag();
	~HairSelectionTag();

public:
	static HairSelectionTag *Alloc() { return (HairSelectionTag*)BaseTag::Alloc(Thairselection); }
	static void Free(HairSelectionTag *&pTag) { BaseTag *tag=pTag; BaseTag::Free(tag); pTag=nullptr; }
#else
public:
#endif

	Bool GetSelected(BaseSelect *bs);
	Bool SetSelected(BaseSelect *bs);

	Int32 GetSelectionType();
	void SetSelectionType(Int32 mode);

	Int32 GetCount();
	Int32 GetSegments();
};

class HairTangentTag : public BaseTag
{
#ifndef __API_INTERN__
private:
	HairTangentTag();
	~HairTangentTag();
public:
	static HairTangentTag *Alloc() { return (HairTangentTag*)BaseTag::Alloc(Thairtangent); }
	static void Free(HairTangentTag *&pTag) { BaseTag *tag=pTag; BaseTag::Free(tag); pTag=nullptr; }
#else
public:
#endif

	Int32 GetPolygonsSegments();
	Int32 GetPointCount();
	Int32 GetCount();
	Int32 GetSegments();
	Vector *GetTangent();
};

class HairRenderObjectEx
{
public:
	HairObject *m_pGuideObject;
	HairObject *m_pHairObject;
	HairGuides *m_pHair;
	BaseList2D *m_pBase;
	RayObject *m_pRayObject;
	HairMaterialData *m_pMaterial;
	Float		*m_pThickness;
};

class HairRenderObject
{
public:
	HairObject *m_pGuideObject;
	HairObject *m_pHairObject;
	HairGuides *m_pHair;
	BaseList2D *m_pBase;
	RayObject *m_pRayObject;
	RayObject *m_pRayObjectHair;
	HairMaterialData *m_pMaterial;
	Float		*m_pThickness;
};

struct HairFragment
{
	Vector col;
	Float trans;
	Float z;
};

struct HairFragmentLink
{
	Vector col;
	Float trans;
	Float z;
	void *link;
};

struct HairHitData
{
	Int32 oindex;
	Int32 lid;
	Int32 seg;
	Int32 p;
	HairGuides *hair;
	BaseList2D *object;
};

#define HAIR_VP_FLAG_NOHOOKS	(1<<0)

class HairVideoPost : public BaseVideoPost
{
#ifndef __API_INTERN__
private:
	HairVideoPost();
	~HairVideoPost();
public:
	static HairVideoPost *Alloc() { return (HairVideoPost*)BaseVideoPost::Alloc(VPhair); }
	static void Free(HairVideoPost *&pPost) { BaseVideoPost *vp=pPost; BaseVideoPost::Free(vp); pPost=nullptr; }
#else
public:
#endif

	Int32 GetObjectCount();
	void GetObject(Int32 i, HairRenderObject *hro);
	Int32 FindObject(BaseList2D *bl);

	Bool TracerEnabled();
	Int32 TraceRay(const Vector &p, const Vector &v, Vector &hit, Float &d, Int32 cpu, Float tf, Int32 flags);

	void Sample(Int32 oindex, VolumeData *vd, Int32 cpu, Int32 lid, Int32 seg, Int32 p, Float lined, const Vector &linep, const Vector &v, Vector &col, const Vector &n, const Vector &lp, const Vector &t, const Vector &r, Vector huv, Int32 flags);
	Float SampleTransparency(Int32 oindex, VolumeData *vd, Int32 lid, Int32 seg, Int32 p, Float lined, const Vector &n, const Vector &linep, const Vector &lp, Vector huv, Int32 cpu, Int32 flags, RayLight *light);
	Float SampleShadow(VolumeData *vd, RayLight *light, const Vector &p, Float delta, Int32 cpu, Int32 flags);

	Bool GetTopFragment(Int32 x, Int32 y, HairFragment *frag, Int32 cpu);
	Bool GetFragmentLink(Int32 x, Int32 y, HairFragmentLink *frag, Int32 cpu, Bool first);
	HairFragment *GetFragments(Int32 x, Int32 y, Int32 &cnt, Int32 cpu);
	Bool SetFragments(Int32 x, Int32 y, HairFragment *frag, Int32 cnt, Int32 cpu);

	Bool InsertFragment(Int32 x, Int32 y, HairFragment *frag, Int32 cnt, Int32 cpu);
	Bool InsertFragmentLine(Int32 x, Int32 y, Int32 xcnt, HairFragment **frag, Int32 *cnt, Int32 cpu);

	void GetHitInfo(Int32 id, HairHitData *hdata);
	Bool IsLightEnabled(Int32 oindex, RayLight *light, Bool *nodiff, Bool *nospec);
	Bool ShadowsEnabled();
	UInt32 GetCompositeFlags(Int32 oindex);
};

//////////////////////////////////////////////////////////////////////////

#define MSG_HAIR_GET_OBJECT_TYPE	1018952		// HairPluginMessageData
#define MSG_HAIR_GET_OBJECTS		1018959		// AtomArray

#define HAIR_CALC_FLAG_APPLYMATERIALS	(1<<0)
#define HAIR_CALC_FLAG_APPLYDEFORMERS	(1<<1)
#define HAIR_CALC_FLAG_DISPLACE			(1<<2)
#define HAIR_CALC_FLAG_SKIP				(1<<3)
#define HAIR_CALC_FLAG_NOMEMORY			(1<<4)
#define HAIR_CALC_FLAG_BREAK			(1<<5)

#define HAIR_PLUGIN_TYPE_FORCE		1
#define HAIR_PLUGIN_TYPE_CONSTRAINT	2
#define HAIR_PLUGIN_TYPE_COLLIDER	3
#define HAIR_PLUGIN_TYPE_DEFORMER	4
#define HAIR_PLUGIN_TYPE_GENERATOR	5
#define HAIR_PLUGIN_TYPE_SHADER		6
#define HAIR_PLUGIN_TYPE_STYLING	7

#define HAIR_GENERATE_PASS_INIT			0
#define HAIR_GENERATE_PASS_BUILD		1
#define HAIR_GENERATE_PASS_FREE			2
#define HAIR_GENERATE_PASS_THICKNESS	3

#define HAIR_GENERATE_HOOK_BUILD		1
#define HAIR_GENERATE_HOOK_DYNAMICS		2

#define HAIR_HOOK_TYPE_SAMPLE_COLOR		1
#define HAIR_HOOK_TYPE_SAMPLE_TRANS		2
#define HAIR_HOOK_TYPE_SAMPLE_SHADOWS	3
#define HAIR_HOOK_TYPE_GENERATE_HAIR	4
#define HAIR_HOOK_TYPE_ILLUMINATE		5

#define HAIR_RENDER_INIT_PASS_PRE		1
#define HAIR_RENDER_INIT_PASS_BUILD		2
#define HAIR_RENDER_INIT_PASS_POST		3

typedef Bool (*HrDeform)(BaseDocument *doc, BaseList2D *op, HairObject *hair, HairGuides *guides, Vector *padr, Int32 cnt, Int32 scnt);
typedef Bool (*HrStyle)(BaseDocument *doc, BaseList2D *op, HairObject *hair, HairGuides *guides, Vector *padr, Int32 cnt, Int32 scnt);
typedef Bool (*HrForce)(BaseDocument *doc, BaseList2D *op, HairObject *hair, HairGuides *guides, HairGuideDynamics *dyn, Vector *force, Float *invmass, Vector *padr, Int32 pcnt, Int32 cnt, Int32 scnt, Float t1, Float t2);
typedef Bool (*HrConstraint)(BaseDocument *doc, BaseList2D *op, HairObject *hair, HairGuides *guides, HairGuideDynamics *dyn, Vector *oldpnt, Vector *newpnt, Float *invmass, Int32 pcnt, Int32 cnt, Int32 scnt);
typedef Bool (*HrCollision)(BaseDocument *doc, BaseList2D *op, HairObject *hair, HairGuides *guides, HairGuideDynamics *dyn, const Vector &bmin, const Vector &bmax, Float t1, Float t2, Float pr, Vector *oldpnt, Vector *newpnt, Vector *vel, Float *invmass, Int32 pcnt, Int32 cnt, Int32 scnt);

typedef HairGuides *(*HrGenerate)(BaseDocument *doc, BaseList2D *op, HairObject *hair, BaseThread *thd, VolumeData *vd, Int32 pass, void *data);
typedef Int32 (*HrCalcHair)(Int32 index, Int32 oindex, NodeData *node, HairGuides *guides, Vector *guide_pnts, Vector *rend_pnts, Float *thickness, VolumeData *vd, Vector *n);
typedef Int32 (*HrGenerateAdd)(BaseDocument *doc, BaseList2D *op);
typedef Vector (*HrGenerateColor)(HairVideoPost *vp, Int32 oindex, HairMaterialData *mat, RayObject *ro, HairObject *op, HairGuides *guides, BaseList2D *bl, Float *thk, VolumeData *vd, Int32 cpu, Int32 lid, Int32 seg, Int32 p, Float lined, const Vector &linep, const Vector &v, const Vector &n, const Vector &lp, const Vector &t, const Vector &r, const Vector &huv, const RayHitID &ply_hit);
typedef Float (*HrGenerateTransparency)(HairVideoPost *vp, Int32 oindex, HairMaterialData *mat, RayObject *ro, HairObject *op, HairGuides *guides, BaseList2D *bl, Float *thk, VolumeData *vd, Int32 cpu, Int32 lid, Int32 seg, Int32 p, Float lined, const Vector &linep, const Vector &n, const Vector &lp, const Vector &huv, const RayHitID &ply_hit, RayLight *light);

typedef Vector (*HrSampleExt)(BaseShader *shader, NodeData *node, ChannelData* cd, HairGuides *guides, Int32 i, Float t);

typedef Vector (*HrSampleHairColorHook)(HairVideoPost *vp, Int32 oindex, HairMaterialData *mat, RayObject *ro, HairObject *op, HairGuides *guides, BaseList2D *bl, Float *thk, VolumeData *vd, Int32 cpu, Int32 lid, Int32 seg, Int32 p, Float lined, const Vector &linep, const Vector &v, const Vector &n, const Vector &lp, const Vector &t, const Vector &r, const Vector &huv, const RayHitID &ply_hit);
typedef Float (*HrSampleHairTransparencyHook)(HairVideoPost *vp, Int32 oindex, HairMaterialData *mat, RayObject *ro, HairObject *op, HairGuides *guides, BaseList2D *bl, Float *thk, VolumeData *vd, Int32 cpu, Int32 lid, Int32 seg, Int32 p, Float lined, const Vector &linep, const Vector &n, const Vector &lp, const Vector &huv, const RayHitID &ply_hit, RayLight *light);
typedef Float (*HrSampleShadowBufferHook)(HairVideoPost *vp, VolumeData *vd, RayLight *light, const Vector &p, Float delta, Int32 cpu);

typedef Bool (*HrGenerateHairHook)(HairObject *op, HairGuides *guides, HairGuides *hair, Int32 pass);
typedef Bool (*HrIlluminateHook)(HairVideoPost *vp, VolumeData *vd, RayLight *light, Vector &colshad, Vector &col, Vector &lv, const Vector &p, const Vector &v);

typedef Bool (*HrInitRender)(HairVideoPost *vp, VolumeData *vd, BaseDocument *doc, BaseList2D *bl, HairObject *op, HairGuides *guides, Int32 oindex, Int32 pass);
typedef void (*HrFreeRender)(HairVideoPost *vp, BaseList2D *bl);

typedef Float (*HrModifyHairShadowTransparency)(HairVideoPost *vp, Int32 oindex, HairMaterialData *mat, RayObject *ro, HairObject *op, HairGuides *guides, BaseList2D *bl, Float *thk, VolumeData *vd, Int32 cpu, Int32 lid, Int32 seg, Int32 p, Float lined, const Vector &linep, const Vector &n, const Vector &lp, const Vector &huv, const RayHitID &ply_hit, RayLight *light, Float trans);

#define HAIR_PLUGIN_DATA_VERSION	1000

class HairPluginObjectData
{
public:
	HairPluginObjectData()
	{
		ClearMem(this,sizeof(HairPluginObjectData));
		version=HAIR_PLUGIN_DATA_VERSION;
		size=sizeof(HairPluginObjectData);
	}

	Int32 version,size;
	Int32 flags;

	//////////////////////////////////////////////////////////////////////////

	HrForce			calc_force;
	HrConstraint	calc_constraint;
	HrCollision		calc_collision;
	HrDeform		calc_deform;
	HrGenerate		calc_generate;
	HrGenerateAdd	add_generate;
	HrCalcHair		calc_hair;
	HrSampleExt		calc_sample;
	HrGenerateColor	calc_col;
	HrGenerateTransparency	calc_trans;
	HrStyle			calc_style;
	HrInitRender	init_render;
	HrFreeRender	free_render;
	HrModifyHairShadowTransparency calc_shad;
};

#define HAIR_MSG_DATA_VERSION	1000

enum HAIR_MSG_DATA_FLAG
{
	HAIR_MSG_DATA_FLAG_TEXTURETAG=(1<<0),
	//////////////////////////////////////////////////////////////////////////
	HAIR_MSG_DATA_FLAG_0=0
} ENUM_END_FLAGS(HAIR_MSG_DATA_FLAG);

enum HAIR_MSG_DATA_TYPE
{
	HAIR_MSG_DATA_TYPE_GETMATERIAL = 1,
	HAIR_MSG_DATA_TYPE_ADDOBJECT = 2,
	HAIR_MSG_DATA_TYPE_INIT = 3,
	HAIR_MSG_DATA_TYPE_INITRENDER = 4,
	HAIR_MSG_DATA_TYPE_FREERENDER = 5,
	//////////////////////////////////////////////////////////////////////////
	HAIR_MSG_DATA_TYPE_0 = 0
} ENUM_END_LIST(HAIR_MSG_DATA_TYPE);

class HairPluginMessageData
{
public:
	HairPluginMessageData()
	{
		size=sizeof(HairPluginMessageData);
		version=HAIR_MSG_DATA_VERSION;
		data=nullptr;
		flags=HAIR_MSG_DATA_FLAG_0;
		bl=nullptr;
		type=HAIR_MSG_DATA_TYPE_0;
	}

	Int32	version,size;		// READ ONLY

	Int32	flags;
	void	*data;

	HAIR_MSG_DATA_TYPE type;
	BaseList2D *bl;
};

class HairLibrary
{
public:
	Int32 GetMode(BaseDocument *doc);
	void SetMode(BaseDocument *doc, Int32 mode);

	Bool GetHairGlobal(BaseDocument* doc);
	void SetHairGlobal(BaseDocument* doc, Bool enable);

	Vector BlendColors(Int32 mode, const Vector &colA, const Vector &colB);

	Vector MixST(Float s, Float t, const Vector &pa, const Vector &pb, const Vector &pc, const Vector &pd, Bool bQuad);
	Float MixST(Float s, Float t, Float va, Float vb, Float vc, Float vd, Bool bQuad);
	void GetPolyPointST(const Vector &p, Float &s, Float &t, const Vector &pa, const Vector &pb, const Vector &pc, const Vector &pd, Bool bQuad);

	void *GetHook(BaseDocument *doc, Int32 type);
	void *SetHook(BaseDocument *doc, Int32 type, void *fn);

	BaseContainer *GetPrefsInstance();

	Int32 GetHairVersion();
};

//////////////////////////////////////////////////////////////////////////

class HairCollider
{
private:
	HairColliderData *m_pData;

	HairCollider();
	~HairCollider();
public:
	static HairCollider *Alloc();
	static void Free(HairCollider *&p);

	Bool Init(HairGuides *hair);
	void Release();

	Int32 GetClosestPoint(const Vector &p);
	Bool GetClosestSegment(const Vector &p, Int32 *guide, Int32* segment, Float* segt);
	Bool GetParticleIntersection(const Vector &p, const Vector &v, Float r, Int32 *guide, Int32 *segment, Float *segt, Float *rayt);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

//////////////////////////////////////////////////////////////////////////
#define LIBRARY_HAIR			1018173
#define LIBRARY_HAIR_COLLIDER	1018174
//////////////////////////////////////////////////////////////////////////

struct HairObjectLib : public C4DLibrary
{
	HairGuides *(*GetGuides)(BaseObject *hop);
	HairGuides *(*GetDynamicGuides)(BaseObject *hop);
	Bool (*GetRootObject)(BaseObject *hop, BaseObject **pObject, BaseTag **pTag, RootObjectData *pData);
	Bool (*Lock)(BaseObject *hop, BaseDocument *pDoc, BaseThread *pThread, Bool bValidate, Int32 flags);
	void (*Unlock)(BaseObject *hop);
	HairGuides *(*GenerateHair)(BaseObject *hop, Int32 flags, Int32 count, Int32 segments, HairMaterialData **pMaterial, HairInterpolationMap *pMap);
	Bool (*SetGuides)(BaseObject *hop, HairGuides *guides, Bool clone);
	void (*RemoveGuides)(BaseObject *hop);
	HairMaterialData *(*InitMaterials)(const InitRenderStruct &irs, BaseObject *hop, BaseDocument *pDoc, HairGuides *guides, VolumeData *vd);
	void (*FreeMaterials)(BaseObject *hop, HairMaterialData *&pMaterials);
	Int32 (*GetGuideCount)(HairGuides *guides);
	Int32 (*GetGuideSegmentCount)(HairGuides *guides);
	Vector *(*GetGuidePoints)(HairGuides *guides);
	HairGuideDynamics *(*GetGuideDynamics)(HairGuides *guides);
	Matrix (*GetGuideMg)(HairGuides *guides);
	void (*SetGuideMg)(HairGuides *guides, const Matrix &mg);
	HairRootData (*GetGuideRoot)(HairGuides *guides, Int32 index);
	void (*SetGuideRoot)(HairGuides *guides, Int32 index, const HairRootData &root, Bool update);
	HairObject *(*GetGuideObject)(HairGuides *guides);
	HairGuides *(*AllocGuides)(Int32 count, Int32 segments);
	void (*FreeGuides)(HairGuides *&guides);
	Bool (*GetGuideSelected)(HairGuides *guides, Int32 mode, BaseSelect *select);
	Bool (*CopyGuidesFrom)(HairGuides *guides, const HairGuides *src);
	Bool (*SetGuideSelected)(HairGuides *guides, Int32 mode, BaseSelect *select);
	Bool (*ConvertGuideSelection)(HairGuides *guides, Int32 from_mode, Int32 to_mode, BaseSelect *from_select, BaseSelect *to_select);
	Vector (*GetGuideTangent)(HairGuides *guides, Int32 guide, Int32 segment, Float t);
	SplineObject *(*CreateGuideSpline)(HairGuides *guides);
	void (*guideToLocal)(HairGuides *guides);
	void (*guideToWorld)(HairGuides *guides);
	void (*guideToInitial)(HairGuides *guides, Bool align);
	void (*guideUndisplaceRoots)(HairGuides *guides);
	void (*guideDisplaceRoots)(HairGuides *guides);
	Bool (*guideGetRootAxis)(HairGuides *guides, Int32 index, Matrix &m, Bool bAlign, Bool bLocal, Bool bInitial, Bool bZAxis);
	Vector (*guideGetRootUV)(HairGuides *guides, Int32 index);
	Bool (*guideGetRootData)(HairGuides *guides, Int32 index, Vector *p, Vector *n, Int32 *ply_id, Bool bLocal, Bool bDisplaced, Bool bInitial);
	Matrix *(*guideGetTransformMatrix)(HairGuides *guides);
	void (*guideSetTransformMatrix)(HairGuides *guides, Matrix *tm);
	Bool (*guideDelete)(HairGuides *guides, BaseSelect *bs);
	Bool (*guideAddRoot)(HairGuides *guides, Int32 ply_id, Float s, Float t, Float len);
	Bool (*guideGetRootObject)(HairGuides *guides, RootObjectData *pData);
	HairGuides *(*GetDynamicsGuides)(HairGuideDynamics *dynamics);
	Vector (*GetDynamicsPosition)(HairGuideDynamics *dynamics, Int32 i);
	void (*SetDynamicsPosition)(HairGuideDynamics *dynamics, Int32 i, const Vector &p);
	Vector (*GetDynamicsLastPosition)(HairGuideDynamics *dynamics, Int32 i);
	void (*SetDynamicsLastPosition)(HairGuideDynamics *dynamics, Int32 i, const Vector &p);
	Vector (*GetDynamicsVelocity)(HairGuideDynamics *dynamics, Int32 i);
	void (*SetDynamicsVelocity)(HairGuideDynamics *dynamics, Int32 i, const Vector &v);
	Float (*GetDynamicsMass)(HairGuideDynamics *dynamics, Int32 i);
	void (*SetDynamicsMass)(HairGuideDynamics *dynamics, Int32 i, Float m);
	Vector (*GetDynamicsForce)(HairGuideDynamics *dynamics, Int32 i);
	void (*AddDynamicsForce)(HairGuideDynamics *dynamics, Int32 i, const Vector &f);
	Int32 (*GetDynamicsPolygonIntersections)(HairGuideDynamics *dynamics, HairPolygonHit **hits);
	Int32 (*hairGetMode)(BaseDocument *doc);
	void (*hairSetMode)(BaseDocument *doc, Int32 mode);
	Bool (*hairGetHairGlobal)(BaseDocument* doc);
	void (*hairSetHairGlobal)(BaseDocument* doc, Bool enable);
	Vector (*hairBlendColors)(Int32 mode, const Vector &colA, const Vector &colB);
	Vector (*hairMixST)(Float s, Float t, const Vector &pa, const Vector &pb, const Vector &pc, const Vector &pd, Bool bQuad);
	Float (*hairMixSTReal)(Float s, Float t, Float va, Float vb, Float vc, Float vd, Bool bQuad);
	void (*hairGetPolyPointST)(const Vector &p, Float &s, Float &t, const Vector &pa, const Vector &pb, const Vector &pc, const Vector &pd, Bool bQuad);
	Bool (*HairSelectionGetSelected)(HairSelectionTag *stag, BaseSelect *bs);
	Bool (*HairSelectionSetSelected)(HairSelectionTag *stag, BaseSelect *bs);
	Int32 (*HairSelectionGetType)(HairSelectionTag *stag);
	void (*HairSelectionSetType)(HairSelectionTag *stag, Int32 mode);
	Int32 (*HairSelectionGetCount)(HairSelectionTag *stag);
	Int32 (*HairSelectionGetSegments)(HairSelectionTag *stag);
	Int32 (*HairVertexGetCount)(HairVertexMapTag *vtag);
	Int32 (*HairVertexGetSegments)(HairVertexMapTag *vtag);
	Int32 (*HairVertexGetPointCount)(HairVertexMapTag *vtag);
	UInt16 *(*HairVertexGetMap)(HairVertexMapTag *vtag);
	Int32 (*matGetCount)(HairMaterialData *mat);
	Int32 (*matGetGuideMaterial)(HairMaterialData *mat, Int32 i, Int32 prev);
	BaseTag *(*matGetMaterialTag)(HairMaterialData *mat, Int32 i);
	Bool (*matApplyMaterial)(HairMaterialData *mat, Int32 i, HairGuides *guides, VolumeData *vd, Int32 vindex);
	Bool (*matApplyMaterials)(HairMaterialData *mat, HairGuides *guides, VolumeData *vd, Int32 vindex);
	Float (*matGetThickness)(HairMaterialData *mat, Int32 guide, Float t, Int32 i);
	Vector (*matGetColor)(HairMaterialData *mat, Int32 guide, Float t, const Vector &r, const Vector &wp, const Vector &p, const Vector &n, VolumeData *vd, const RayHitID &plyid, Int32 i);
	Vector (*matGetBackColor)(HairMaterialData *mat, Int32 guide, Float t, const Vector &col, const Vector &r, const Vector &wp, const Vector &p, const Vector &n, VolumeData *vd, const RayHitID &plyid, Int32 i);
	Bool (*matGetSpecularColor)(HairMaterialData *mat, Int32 guide, Float t, const Vector &wp, const Vector &p, const Vector &n, VolumeData *vd, const RayHitID &plyid, Vector &speccol, Vector &ispeccol);
	Float (*matGetTransparencyEx)(HairMaterialData *mat, Int32 guide, Float t, const Vector &p, const Vector &n, Int32 i);
	Bool (*matGetTagSelection)(HairMaterialData *mat, Int32 i, BaseSelect *bs);
	Bool (*matGetMaterialData)(HairMaterialData *mat, Int32 guide, Float &shadows, Float &selfshadows, Float &backshadows, Float &transparency, Float &diffuse, Float &reflect, Float &transmit, Bool &roughenable, Float &roughvar, Float &roughness, Bool &specularenable, Float &specular, Float &specularpower, Float &specularback, Bool &ispecularenable, Bool &ispecularshader, Float &ispecular, Float &ispecularpower, Float &ispecularmix, Float &ispecularblend);
	Bool (*matGetGIData)(HairMaterialData *mat, Int32 guide, Bool &receive, Float &strength);
	Bool (*matAdjustHUV)(HairMaterialData *mat, Int32 guide, Vector &huv, Float tline);
	Int32 (*HairTangentGetPolygonsSegments)(HairTangentTag *ttag);
	Int32 (*HairTangentGetPointCount)(HairTangentTag *ttag);
	Int32 (*HairTangentGetCount)(HairTangentTag *ttag);
	Int32 (*HairTangentGetSegments)(HairTangentTag *ttag);
	Vector *(*HairTangentGetTangent)(HairTangentTag *ttag);
	void *(*hairGetHook)(BaseDocument *doc, Int32 type);
	void *(*hairSetHook)(BaseDocument *doc, Int32 type, void *fn);
	BaseContainer *(*hairGetPrefsInstance)();
	Int32 (*vpGetObjectCount)(HairVideoPost *vp);
	void (*vpGetObjectEx)(HairVideoPost *vp, Int32 i, HairRenderObjectEx *hro);
	Int32 (*vpFindObject)(HairVideoPost *vp, BaseList2D *bl);
	Bool (*vpTracerEnabled)(HairVideoPost *vp);
	Int32 (*vpTraceRay)(HairVideoPost *vp, const Vector &p, const Vector &v, Vector &hit, Float &d, Int32 cpu, Float tf, Int32 flags);
	Bool (*hairIsLocked)(HairObject *op);
	Bool (*guideLinkToObject)(HairGuides *guide, HairObject *pHair);
	void (*vpSample)(HairVideoPost *vp, Int32 oindex, VolumeData *vd, Int32 cpu, Int32 lid, Int32 seg, Int32 p, Float lined, const Vector &linep, const Vector &v, Vector &col, const Vector &n, const Vector &lp, const Vector &t, const Vector &r, Vector huv, Int32 flags);
	Float (*vpSampleTransparency)(HairVideoPost *vp, Int32 oindex, VolumeData *vd, Int32 lid, Int32 seg, Int32 p, Float lined, const Vector &n, const Vector &linep, const Vector &lp, Vector huv, Int32 cpu, Int32 flags, RayLight *light);
	Float (*vpSampleShadow)(HairVideoPost *vp, VolumeData *vd, RayLight *light, const Vector &p, Float delta, Int32 cpu, Int32 flags);
	Bool (*vpGetTopFragment)(HairVideoPost *vp, Int32 x, Int32 y, HairFragment *frag, Int32 cpu);
	Bool (*vpSetFragments)(HairVideoPost *vp, Int32 x, Int32 y, HairFragment *frag, Int32 cnt, Int32 cpu);
	Bool (*vpGetFragmentLink)(HairVideoPost *vp, Int32 x, Int32 y, HairFragmentLink *frag, Int32 cpu, Bool first);
	HairFragment *(*vpGetFragments)(HairVideoPost *vp, Int32 x, Int32 y, Int32 &cnt, Int32 cpu);
	Bool (*vpInsertFragment)(HairVideoPost *vp, Int32 x, Int32 y, HairFragment *frag, Int32 cnt, Int32 cpu);
	Bool (*vpInsertFragmentLine)(HairVideoPost *vp, Int32 x, Int32 y, Int32 xcnt, HairFragment **frag, Int32 *cnt, Int32 cpu);
	Int32 (*hairGetHairVersion)();
	Int32 (*guideGetFlags)(HairGuides *guide);
	Int32 (*guideSetFlags)(HairGuides *guide, Int32 flags);
	void (*vpGetHitInfo)(HairVideoPost *vp, Int32 id, HairHitData *hdata);
	Bool (*vpIsLightEnabled)(HairVideoPost *vp, Int32 oindex, RayLight *light, Bool *nodiff, Bool *nospec);
	Bool (*vpShadowsEnabled)(HairVideoPost *vp);
	UInt32 (*vpGetCompositeFlags)(HairVideoPost *vp, Int32 oindex);
	void (*vpGetObject)(HairVideoPost *vp, Int32 i, HairRenderObject *hro);
	Float (*matGetTransparency)(HairMaterialData *mat, Int32 guide, Float t, const Vector &p, const Vector &n, VolumeData *vd, Int32 i);
};

struct HairColliderLib : public C4DLibrary
{
	iHairCollider *(*Alloc)();
	void (*Free)(iHairCollider *&p);

	Bool (iHairCollider::*Init)(HairGuides *hair);
	void (iHairCollider::*Release)();
	Int32 (iHairCollider::*GetClosestPoint)(const Vector &p);
	Bool (iHairCollider::*GetClosestSegment)(const Vector &p, Int32 *guide, Int32* segment, Float* segt);
	Bool (iHairCollider::*GetParticleIntersection)(const Vector &p, const Vector &v, Float r, Int32 *guide, Int32 *segment, Float *segt, Float *rayt);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif	// __LIB_HAIR_H__
