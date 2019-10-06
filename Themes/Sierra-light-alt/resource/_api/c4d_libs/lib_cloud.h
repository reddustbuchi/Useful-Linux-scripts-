#ifndef _LIB_CLOUD_H_
#define _LIB_CLOUD_H_

#include "c4d_baseobject.h"
#include "customgui_splinecontrol.h"

#define CLOUD_NODE						1011196
#define CLOUD_GROUP_NODE			1011194
#define SKY_OBJECT						1011146
#define MSG_SKY_INIALIZED			450000094

#define CLOUD_CELL_SIZE_X   150
#define CLOUD_CELL_SIZE_Y   150
#define CLOUD_CELL_SIZE_Z   150

BaseObject* FindSkyObject(BaseDocument* pDoc);

class CloudObject;

#ifndef __API_INTERN__
typedef Bool (*CloudDrawFn)(BaseObject* op, BaseDraw* pDraw, BaseDrawHelp* pDrawHelp, Int32 lGrid, Float rQuality, const Vector &vScale, BaseObject* pSun, Bool bDrawPlane);
typedef void* (*CloudDataAllocator)(BaseObject* pCloud);
typedef void (*ClodDataDeleter)(BaseObject* pCloud, void* &pData);
#endif

class CloudObject : public BaseObject
{
private:
	CloudObject();
	~CloudObject();

public:
	static CloudObject* Alloc();
	static void Free(CloudObject *&pObj);
	static void SetDrawHook(CloudDrawFn fn);

	void GetSize(Vector& vSize);
	void GetSize(Int32 &x, Int32 &y, Int32 &z); // the cloud has (x + 1) * (y + 1) * (z + 1) grid points
	UChar* GetDensity();
	UChar* GetToolData();
	Int GetDensitySize();

	Bool AllocToolData();
	void FreeToolData();

	Float GetAltitude(BaseObject* pCloudGroup);

	Bool Resize(Int32 x, Int32 y, Int32 z, Bool bResample);
	Bool SmoothBorders(Float rDist, Float rVariance, SplineData* pSpline);
	Bool SmoothAll(Float rStrength, Float rVariance);
	void Clear(UChar chDensity);
	void FillPlane(Float rRadius, UChar chDensity);
	void FillSphere(Float rRadius, UChar chDensity);
	Bool IsVisible(Bool bEditor, Bool &bDrawBox, BaseObject *&pSkyObject, BaseObject** ppGroup = nullptr);
	Bool IsLocked();
	void Draw(BaseDraw* pBaseDraw, BaseDrawHelp* pDrawHelp, Int32 lGrid, Float rQuality, Bool bDrawPlane);

	Int32 GetPlaneIndex();
	void SetPlaneIndex(Int32 lPlane);
	Int32 GetPlanePosition();
	void SetPlanePosition(Int32 lPos);

	void* GetPrivateData(CloudDataAllocator fnAlloc, ClodDataDeleter fnFree);
};

#define LIB_CLOUD		450000111
class iCloudObject;

struct CloudObjectLib : public C4DLibrary
{
	CloudObject*	(*Alloc)();
	void					(*Free)(CloudObject *&pObj);
	void					(*SetDrawHook)(CloudDrawFn fn);

	void					(iCloudObject::*GetSize1)(Vector& vSize);
	void					(iCloudObject::*GetSize2)(Int32 &x, Int32 &y, Int32 &z);
	UChar*				(iCloudObject::*GetDensity)();
	UChar*				(iCloudObject::*GetToolData)();
	Bool					(iCloudObject::*AllocToolData)();
	void					(iCloudObject::*FreeToolData)();
	Int					(iCloudObject::*GetDensitySize)();

	Float					(iCloudObject::*GetAltitude)(BaseObject* pCloudGroup);

	Bool					(iCloudObject::*Resize)(Int32 x, Int32 y, Int32 z, Bool bResample);
	Bool					(iCloudObject::*SmoothBorders)(Float rDist, Float rVariance, SplineData* pSpline);
	Bool					(iCloudObject::*SmoothAll)(Float rStrength, Float rVariance);
	void					(iCloudObject::*Clear)(UChar chDensity);
	void					(iCloudObject::*FillPlane)(Float rRadius, UChar chDensity);
	void					(iCloudObject::*FillSphere)(Float rRadius, UChar chDensity);
	Bool					(iCloudObject::*IsVisible)(Bool bEditor, Bool &bDrawBox, BaseObject *&pSkyObject, BaseObject** ppGroup);
	Bool					(iCloudObject::*IsLocked)();
	Int32					(iCloudObject::*GetPlaneIndex)();
	void					(iCloudObject::*SetPlaneIndex)(Int32 lPlane);
	Int32					(iCloudObject::*GetPlanePosition)();
	void					(iCloudObject::*SetPlanePosition)(Int32 lPos);
	void					(iCloudObject::*Draw)(BaseDraw* pBaseDraw, BaseDrawHelp* pDrawHelp, Int32 lGrid, Float rQuality, Bool bDrawPlane);

	BaseObject*		(*FindSkyObject)(BaseDocument* pDoc);
	void*					(iCloudObject::*GetPrivateData)(CloudDataAllocator fnAlloc, ClodDataDeleter fnFree);
};

#endif // _LIB_CLOUD_H_
