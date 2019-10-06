/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __LIB_SDS_H__
#define __LIB_SDS_H__

#include "c4d_library.h"
#ifdef __API_INTERN__
#include "baseobject.h"
#else
#include "c4d_baseobject.h"
#include "c4d_basetag.h"
#endif

class PolygonObject;

#ifdef __API_INTERN__
#include "hntag.h"
#endif

struct SDSSubdivisionMask
{
	Int32 p; // one of the original polygons
	Int32 e1, e2, e3, e4; // original edge
};

class SDSObject : public BaseObject
{
private:
	SDSObject();
	~SDSObject();
public:
	Int32 GetDivision(BaseObject *op);
	PolygonObject *GetSDSMesh(BaseObject *op);
	Bool TransformPoint(BaseObject *op, Int32 ply, Float &s, Float &t, Vector *p);
	Bool GetNormal(BaseObject *op, Int32 ply, Vector *p, Vector *n);
	static Float32 *GetPointWeights(BaseTag *pTag);
	static PolyWeight *GetEdgeWeights(BaseTag *pTag);
	SDSSubdivisionMask* GetSubdivisionMask(BaseObject *op, Int32 &maskcnt, Int32 *&polymap, Bool &ngonsubdiv);
	void *GetCreationData(BaseObject *op);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

//////////////////////////////////////////////////////////////////////////
#define LIBRARY_SDS	1016122
//////////////////////////////////////////////////////////////////////////

struct SDSObjectLib : public C4DLibrary
{
	Int32 *(*GetEdgeMap)(BaseObject *sds, BaseObject *op);
	Int32 *(*GetPolygonMap)(BaseObject *sds, BaseObject *op);
	Int32 (*GetDivision)(BaseObject *sds, BaseObject *op);
	PolygonObject *(*GetSDSMesh)(BaseObject *sds, BaseObject *op);
	Bool (*TransformPoint)(BaseObject *sds, BaseObject *op, Int32 ply, Float &s, Float &t, Vector *p);
	Bool (*GetNormal)(BaseObject *sds, BaseObject *op, Int32 ply, Vector *p, Vector *n);
	Float32 *(*GetPointWeights)(BaseTag *pTag);
	PolyWeight *(*GetEdgeWeights)(BaseTag *pTag);
	SDSSubdivisionMask* (*GetSubdivisionMask)(BaseObject *sds, BaseObject *op, Int32 &maskcnt, Int32 *&polymap, Bool &ngonsubdiv);
	void *(*GetCreationData)(BaseObject *sds, BaseObject *op);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif	// __LIB_SDS_H__
