/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

//----------------------------------------------------
//Falloff controller system
#ifndef _C4D_FALLOFFDATA_H_
#define _C4D_FALLOFFDATA_H_

#ifdef __API_INTERN__
abc def xyz
#endif

#include "c4d.h"

#define FALLOFFCAGE		 Vector(1.0f, 1.0f, 0.0f)
#define FALLOFFFALLOFF Vector(0.7f, 0.1f, 0.0f)

#define	ID_C4DFALLDATALIB	1019551
#define ID_C4DFALLOFFLIB	1019541

struct FalloffDataData
{
public:
	FalloffDataData(void)
	{
		mat	 = Matrix();
		imat = ~mat;
		falloff = scale = strength = 1.0;
		size = Vector(1.0);
		invert	= clamped = usespline = false;
		visible = true;

		axis	= 0;
		slice = torusRadius = radius = iradius = ifalloff = 1.0;
		function	= FALLOFF_FUNCTION_SPLINE;
		spherical = false;

		userdata = nullptr;
	}
	~FalloffDataData(void) { }

	Bool operator==(const FalloffDataData& b)
	{
		return mat == b.mat && imat == b.imat && falloff == b.falloff && scale == b.scale && strength == b.strength
					 && size == b.size && invert == b.invert && clamped == b.clamped && visible == b.visible && usespline == b.usespline
					 && nodemat == b.nodemat && inodemat == b.inodemat && offset == b.offset && axis == b.axis && slice == b.slice
					 && torusRadius == b.torusRadius && function == b.function && spherical == b.spherical && radius == b.radius
					 && iradius == b.iradius && ifalloff == b.ifalloff && userdata == b.userdata;
	}

	Bool operator!=(const FalloffDataData& b)
	{
		return !(*this == b);
	}

	Matrix mat, imat;
	Float	 falloff, scale, strength;
	Vector size;
	Bool	 invert, clamped, visible, usespline;
	Matrix nodemat, inodemat;
	Vector offset;
	Int32	 axis;
	Float	 slice;
	Float	 torusRadius;
	Int32	 function;
	Bool	 spherical;
	Float	 radius, iradius;
	Float	 ifalloff;
	void*	 userdata;
};

class FalloffData : public BaseData
{
public:
	virtual Bool Init(FalloffDataData& falldata, BaseContainer* bc);
	virtual Bool InitFalloff(BaseContainer* bc, FalloffDataData& falldata);
	virtual void Sample(const Vector& p, const FalloffDataData& data, Float* res);
	virtual void FreeFalloff(FalloffDataData& falldata);
	virtual Bool CheckDirty(BaseContainer* bc);
	virtual Bool GetDVisible(DescID& id, BaseContainer* bc, BaseContainer* desc_bc);
	virtual Int32	GetHandleCount(BaseContainer* bc, const FalloffDataData& data);
	virtual void GetHandle(BaseContainer* bc, Int32 i, HandleInfo& info, const FalloffDataData& data);
	virtual void SetHandle(BaseContainer* bc, Int32 i, Vector p, const FalloffDataData& data);
	virtual Bool Draw(const FalloffDataData& data, DRAWPASS drawpass, BaseDraw* bd, BaseDrawHelp* bh);
	virtual Bool Message(Int32 type, BaseContainer* bc, void* m_data);
};

class C4D_Falloff
{
private:
	C4D_Falloff(void) { }
	~C4D_Falloff(void) { }

public:
	BaseContainer*					GetContainerInstance(void);

	void SetDirty(void);
	Int32	GetDirty(BaseContainer* bc = nullptr);
	void SetMg(Matrix mg);
	Matrix GetMg(void);
	void SetData(FalloffDataData falldata);
	FalloffDataData	GetData(void);
	Bool SetMode(Int32 type, BaseContainer* bc = nullptr);
	Int32	GetMode(void);
	void SetTime(BaseTime time, BaseContainer* bc = nullptr);

	Bool InitFalloff(BaseContainer* bc = nullptr, BaseDocument* doc = nullptr, BaseObject* op = nullptr);
	void Sample(const Vector& p, Float* result, Bool usespline = true, Float weight = 0.0);

	void MultiSample(const Vector* p, Float* result, Int32 count, Bool usespline = true, Float weight = 0.0);

	Bool AddFalloffToDescription(Description* description, BaseContainer* bc = nullptr);

	Bool Message(Int32 id, BaseContainer* bc = nullptr, void* m_data = nullptr);
	Int32	GetHandleCount(BaseContainer* bc = nullptr);
	void GetHandle(Int32 i, BaseContainer* bc, HandleInfo& info);
	void SetHandle(Int32 i, Vector p, BaseContainer* bc, const HandleInfo& info);
	Bool Draw(BaseDraw* bd, BaseDrawHelp* bh, DRAWPASS drawpass, BaseContainer* bc = nullptr);
	Bool CopyTo(C4D_Falloff* dest);

	//Autoallocation code
	static C4D_Falloff*			Alloc(void);
	static void	Free(C4D_Falloff*& node);
};

struct FALLOFFPLUGIN;

typedef FalloffData* FalloffDataAllocator (void);

void FillFalloffPlugin(FALLOFFPLUGIN* fp, Int32 info, FalloffDataAllocator* g);
Bool RegisterFalloffPlugin(Int32 id, const String& str, Int32 info, FalloffDataAllocator* g, const String& description);
void* AllocFalloff(Int32 type);

#endif
