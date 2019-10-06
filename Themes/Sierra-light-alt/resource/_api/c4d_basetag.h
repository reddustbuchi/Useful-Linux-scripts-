/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DBASETAG_H
#define __C4DBASETAG_H

#ifdef __API_INTERN__
abc def xyz
#endif

#include "c4d_baselist.h"
#include "operatingsystem.h"

class BaseObject;
class BaseSelect;
class GvNodeMaster;

#define TAG_VISIBLE			 (1 << 0)
#define TAG_MULTIPLE		 (1 << 1)
#define TAG_HIERARCHICAL (1 << 2)
#define TAG_EXPRESSION	 (1 << 3)
#define TAG_TEMPORARY		 (1 << 4)
#define TAG_MODIFYOBJECT (1 << 6)

class BaseTag : public BaseList2D
{
private:
	BaseTag();
	~BaseTag();

public:
	BaseObject* GetObject(void) { return (BaseObject*)AtCall(GetMain) (); }

	BaseTag* GetNext(void) { return (BaseTag*)AtCall(GetNext) (); }
	BaseTag* GetPred(void) { return (BaseTag*)AtCall(GetPred) (); }

	BaseTag* GetOrigin();

	static BaseTag* Alloc(Int32 type);
	static void Free(BaseTag*& bl);
};

class VariableTag : public BaseTag
{
private:
	VariableTag();
	~VariableTag();

public:
	Int32	GetDataCount	(void);
	Int32	GetDataSize		(void);

	const void*	GetLowlevelDataAddressR(void);	// only use these routines if you exactly know what you're doing
	void*				GetLowlevelDataAddressW(void);	//

	static VariableTag* Alloc(Int32 type, Int32 count);
	static void Free(VariableTag*& bl);
};

class PointTag : public VariableTag
{
private:
	PointTag();
	~PointTag();

public:
	const Vector*	GetDataAddressR(void);
	Vector*				GetDataAddressW(void);
};

class VertexMapTag : public VariableTag
{
private:
	VertexMapTag();
	~VertexMapTag();

public:
	const Float32*	GetDataAddressR(void);
	Float32*				GetDataAddressW(void);

	static VertexMapTag* Alloc(Int32 count);
	static void Free(VertexMapTag*& bl);
};

class SegmentTag : public VariableTag
{
private:
	SegmentTag();
	~SegmentTag();

public:
	const Segment*	GetDataAddressR(void);
	Segment*				GetDataAddressW(void);
};

class TangentTag : public VariableTag
{
private:
	TangentTag();
	~TangentTag();

public:
	const Tangent*	GetDataAddressR(void);
	Tangent*				GetDataAddressW(void);
};

class PolygonTag : public VariableTag
{
private:
	PolygonTag();
	~PolygonTag();

public:
	const CPolygon*	GetDataAddressR(void);
	CPolygon*				GetDataAddressW(void);
};

class SelectionTag : public BaseTag
{
private:
	SelectionTag();
	~SelectionTag();

public:
	BaseSelect* GetBaseSelect(void);

	static SelectionTag* Alloc(Int32 type);
	static void Free(SelectionTag*& bl);
};

class UVWTag : public VariableTag
{
private:
	UVWTag();
	~UVWTag();

public:
	UVWStruct GetSlow(Int32 i) { UVWStruct us; C4DOS.Tg->UvGet(this, i, &us); return us; }
	void SetSlow(Int32 i, const UVWStruct& s) { C4DOS.Tg->UvSet(this, i, (UVWStruct*) &s); }
	void CpySlow(Int32 dst, UVWTag* srctag, Int32 src) { C4DOS.Tg->UvCpy(this, dst, srctag, src); }

	ConstUVWHandle GetDataAddressR(void);
	UVWHandle	GetDataAddressW(void);

	static void Get(ConstUVWHandle dataptr, Int32 i, UVWStruct& res) { C4DOS.Tg->UvGet2(dataptr, i, &res); }
	static void Set(UVWHandle dataptr, Int32 i, const UVWStruct& s) { C4DOS.Tg->UvSet2(dataptr, i, s); }
	static void Copy(UVWHandle destptr, Int32 dst, ConstUVWHandle srcptr, Int32 src) { C4DOS.Tg->UvCpy2(srcptr, src, destptr, dst); }

	static UVWTag* Alloc(Int32 count);
	static void Free(UVWTag*& bl);
};

class NormalTag : public VariableTag
{
private:
	NormalTag();
	~NormalTag();

public:
	ConstNormalHandle	GetDataAddressR(void);
	NormalHandle GetDataAddressW(void);

	static void Get(ConstNormalHandle dataptr, Int32 i, NormalStruct& res) { C4DOS.Tg->NrmGet(dataptr, i, &res); }
	static void Set(NormalHandle dataptr, Int32 i, const NormalStruct& s) { C4DOS.Tg->NrmSet(dataptr, i, s); }
	static void Copy(NormalHandle destptr, Int32 dst, ConstNormalHandle srcptr, Int32 src) { C4DOS.Tg->NrmCpy(srcptr, src, destptr, dst); }

	static NormalTag* Alloc(Int32 count);
	static void Free(NormalTag*& bl);
};

class TextureTag : public BaseTag
{
private:
	TextureTag();
	~TextureTag();

public:
	Vector GetPos(void);
	Vector GetScale(void);
	Vector GetRot(void);
	Matrix GetMl(void);
	void SetPos(const Vector& v);
	void SetScale(const Vector& v);
	void SetRot(const Vector& v);
	void SetMl(const Matrix& m);

	BaseMaterial* GetMaterial(Bool ignoredoc = false);
	void SetMaterial(BaseMaterial* mat);

	static TextureTag* Alloc();
	static void Free(TextureTag*& bl);
};

class StickTextureTag : public VariableTag
{
private:
	StickTextureTag();
	~StickTextureTag();

public:
	const Vector*	GetDataAddressR(void);
	Vector*				GetDataAddressW(void);

	Bool Record(BaseObject* op, Bool always);

	static StickTextureTag* Alloc(Int32 type);
	static void Free(StickTextureTag*& bl);
};

class XPressoTag : public BaseTag
{
private:
	XPressoTag();
	~XPressoTag();

public:
	GvNodeMaster* GetNodeMaster(void);

	static XPressoTag* Alloc();
	static void Free(XPressoTag*& bl);
};

struct PolyWeight
{
	Float32 a, b, c, d;	// weights of the edges, (for triangles a, b and d contain valid data)
};

struct HNData
{
	HNData() { points = polys = nullptr; pointweight = nullptr; polyweight = nullptr; changed = nullptr; }

	Int32*			 points, *polys;
	Float32**		 pointweight;
	PolyWeight** polyweight;
	Bool*				 changed;
};

struct HNSubdiv
{
	PolygonObject* op;			// the polygonobject that is to be subdivided
	Float					 lod;			// level of detail
	Int32					 subdiv;	// subdivision level of op
};

class HNWeightTag : public BaseTag
{
private:
	HNWeightTag();
	~HNWeightTag();

public:
	Bool GetTagData(HNData* data);	// fills the members of this class

	static HNWeightTag* Alloc();
	static void Free(HNWeightTag*& bl);
};

#define BAKEPARTICLETAG_FROM	 1001	// Int32
#define BAKEPARTICLETAG_TO		 1002	// Int32
#define BAKEPARTICLETAG_STEP	 1003	// Int32
#define BAKEPARTICLETAG_IGNORE 1004	// BOOL

#endif
