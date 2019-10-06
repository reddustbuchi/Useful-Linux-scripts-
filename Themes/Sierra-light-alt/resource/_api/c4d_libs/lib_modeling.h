/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _LIB_MODELLING_H_
#define _LIB_MODELLING_H_

#include "c4d_library.h"
#include "c4d_memory.h"

class iModeling;
class ModelingBase;
class ModelingKernel;
class Ngon;

//////////////////////////////////////////////////////////////////////////

#ifndef NOTINDEX
#define NOTINDEX				(LIMIT<Int32>::MAX)
#endif

struct PointMove
{
	PointMove(Int32 index) { i=index; }

	Int32	i;
	Vector	p;
};

#define TRANSMAP_FLAG_NEW		(1<<0)
#define TRANSMAP_FLAG_CLONE		(1<<1)
#define TRANSMAP_FLAG_MOVED		(1<<2)
#define TRANSMAP_FLAG_DELETED	(1<<3)
#define TRANSMAP_FLAG_UNION		(1<<4)

#define TRANSMAP_PNTFLAG_INTER	(1<<20)
#define TRANSMAP_PNTFLAG_DELTA	(1<<21)
#define TRANSMAP_PNTFLAG_WELDED	(1<<22)

#define TRANSMAP_PLYFLAG_MELTED	(1<<20)
#define TRANSMAP_PLYFLAG_PGON	(1<<21)

struct TransIndexMapData
{
	TransIndexMapData(Int32 oindex) { oIndex=oindex; }
	TransIndexMapData(Int32 oindex, Int32 nindex) { oIndex=oindex; nIndex=nindex; }

	Int32 oIndex;
	Int32 nIndex;
};

struct TransMapData : public TransIndexMapData
{
	TransMapData(Int32 oindex) : TransIndexMapData(oindex) { }
	TransMapData(Int32 oindex, Int32 nindex) : TransIndexMapData(oindex,nindex)  { }

	Int32 lFlags;
	Int32 mIndex;
};

struct TransMapNewData
{
	TransMapNewData(Int32 nindex) { nIndex=nindex; }

	Int32 nIndex;
	Int32 mIndex;
};

struct TransPointInterData
{
	Int32 p1;
	Int32 p2;
	Float t;
};

struct TransPointDeltaData
{
	Vector opnt;
	Vector dlt;
};

class TranslationMaps
{
public:
	TranslationMaps(void)
	{
		ClearMem(this, sizeof(TranslationMaps), 0);
	}

	Int32 FindOriginalPoint(Int32 index);
	Int32 FindOriginalPolygon(Int32 index);
	Int32 FindOriginalPgon(Int32 index);
	Int32 FindOriginalSegment(Int32 index);

	Int32 FindNewPoint(Int32 index);
	Int32 FindNewPolygon(Int32 index);
	Int32 FindNewPgon(Int32 index);
	Int32 FindNewSegment(Int32 index);

	Int32 FindWeldPoint(Int32 index);
	Int32 FindMeltPolygon(Int32 index);

	//////////////////////////////////////////////////////////////////////////

	Int32 m_oPointCount;
	Int32 m_oPolygonCount;
	Int32 m_oPgonCount;
	Int32 m_oSegmentCount;

	Int32 m_nPointCount;
	Int32 m_nPolygonCount;
	Int32 m_nPgonCount;
	Int32 m_nSegmentCount;

	Int32 m_mPointCount;
	Int32 m_mPolygonCount;
	Int32 m_mPgonCount;
	Int32 m_mSegmentCount;

	Int32 m_mWeldCount;
	Int32 m_mMeltCount;

	//////////////////////////////////////////////////////////////////////////

	TransMapData		*m_pPointMap;
	TransMapData		*m_pPolygonMap;
	TransMapData		*m_pPgonMap;
	TransMapData		*m_pSegmentMap;

	TransIndexMapData	*m_pWeldMap;
	TransIndexMapData	*m_pMeltMap;

	TransMapNewData		*m_pNewPointMap;
	TransMapNewData		*m_pNewPolygonMap;
	TransMapNewData		*m_pNewPgonMap;
	TransMapNewData		*m_pNewSegmentMap;

	TransPointInterData *m_pInterpolatedPoints;
	TransPointDeltaData	*m_pDeltaPoints;
};

//////////////////////////////////////////////////////////////////////////

#define	MODELING_ERROR_UNKNOWN			(-1)
#define	MODELING_ERROR_NONE				(0)
#define	MODELING_ERROR_FAILED			(1)
#define	MODELING_ERROR_NOMEMORY			(2)
#define	MODELING_ERROR_NOTFOUND			(3)
#define	MODELING_ERROR_INVALIDOP		(4)
#define	MODELING_ERROR_FATAL			(5)
#define	MODELING_ERROR_INVALIDOBJECT	(6)
#define	MODELING_ERROR_ILLEGAL			(7)
#define	MODELING_ERROR_TRIANGULATION	(8)
#define	MODELING_ERROR_INVALIDKERNEL	(9)
#define	MODELING_ERROR_INTERNAL			(10)
#define	MODELING_ERROR_BADARGS			(11)
#define	MODELING_ERROR_CORRUPTOBJECT	(12)
#define	MODELING_ERROR_MSGFAIL			(13)

#define MODELING_COMMIT_NONE		0
#define MODELING_COMMIT_UPDATE		1
#define MODELING_COMMIT_CREATEMAP	2
#define MODELING_COMMIT_REFRESH		4
#define MODELING_COMMIT_TRINGONS	8
#define MODELING_COMMIT_RESTORE		16
#define MODELING_COMMIT_ADDUNDO		32
#define MODELING_COMMIT_QUADS		64
#define MODELING_COMMIT_NOVALIDATION	128
#define MODELING_COMMIT_QUADLIMIT		256
#define MODELING_COMMIT_NO_NGONS  (MODELING_COMMIT_TRINGONS | MODELING_COMMIT_QUADS)

#define MODELING_SETPOINT_FLAG_EMPTY	0
#define MODELING_SETPOINT_FLAG_NODIRTY	1
#define MODELING_SETPOINT_FLAG_UNION	2

#define MODELING_SETNGON_FLAG_EMPTY			0
#define MODELING_SETNGON_FLAG_TRIANGULATE	1
#define MODELING_SETNGON_FLAG_FIXEDQUADS	2
#define MODELING_SETNGON_FLAG_NGONQUADS		4
#define MODELING_SETNGON_FLAG_QUADS			8
#define MODELING_SETNGON_FLAG_UNION			16
#define MODELING_SETNGON_FLAG_NOROTATE		32

#define MODELING_GETNGON_FLAG_EMPTY			0
#define MODELING_GETNGON_FLAG_READONLY		1

//////////////////////////////////////////////////////////////////////////

struct CPolygon;

typedef Bool (*TriangulateHook)(BaseObject *pObj, Int32 lNgonID, Ngon *ngon, const Vector *pvPoints, Int32 lPointCount, CPolygon *&pPolys, Int32 &lPolyCount, Bool &bTriang, void *pData);

//////////////////////////////////////////////////////////////////////////

class Modeling
{
private:
	Modeling();
	~Modeling();

	ModelingBase	*m_pBase;
	ModelingKernel	*m_pKernelCache;
	C4DAtom			*m_pObjectCache;

public:

	static Modeling *Alloc();
	static void Free(Modeling *&p);

	//////////////////////////////////////////////////////////////////////////

	Bool InitArray(AtomArray *objs, Int32 flags=0);
	Bool InitObject(C4DAtom *op, Int32 flags=0);
	Bool Commit(C4DAtom *op=nullptr, Int32 flags=0 , BaseObject* cobj = nullptr);
	void Release();
	void ReleaseObject(C4DAtom *op);

	//////////////////////////////////////////////////////////////////////////

	// Maps

	Bool GetPointMap(C4DAtom *op, Int32 **map, Int32 *count);
	Bool GetNgonMap(C4DAtom *op, Int32 **map, Int32 *count);
	Bool ReleaseMap(C4DAtom *op, Int32 *map);
	Bool FreeMap(C4DAtom *op, Int32 *map);

	// Points

	Int32 AddPoint(C4DAtom *op, const Vector &p);
	Int32 ClonePoint(C4DAtom *op, Int32 index);
	Bool DeletePoint(C4DAtom *op, Int32 index);
	Bool GetPoint(C4DAtom *op, Int32 index, Vector *p);
	Bool SetPoint(C4DAtom *op, Int32 index, const Vector &p, Int32 flags=MODELING_SETPOINT_FLAG_EMPTY);
	Bool SetEdgePoint(C4DAtom *op, Int32 index, Float l, Int32 flags=MODELING_SETPOINT_FLAG_EMPTY);
	Bool SetPoints(C4DAtom *op, PointMove *pnts, Int32 cnt, Bool commit=false, Int32 flags=MODELING_SETPOINT_FLAG_EMPTY);
	Bool GetPointInfo(C4DAtom *op, Int32 index, Int32 &ia, Int32 &ib, Float &t);
	Bool GetOriginPoint(C4DAtom *op, Int32 index, Int32 &ci);
	Bool SetPointInfo(C4DAtom *op, Int32 index, Int32 ia, Int32 ib, Float t);
	Bool SetOriginPoint(C4DAtom *op, Int32 index, Int32 ci);
	Int32 GetPointFlags(C4DAtom *op, Int32 index);
	Int32 SetPointFlags(C4DAtom *op, Int32 index, Int32 flags);
	Bool GetPointOrigin(C4DAtom *op, Int32 index, Vector &opnt);
	Bool SetPointOrigin(C4DAtom *op, Int32 index, Vector opnt, Int32 flags);
	Bool SetInterPoint(C4DAtom *op, Int32 index, Vector npnt, Float t, Int32 flags=MODELING_SETPOINT_FLAG_EMPTY);
	Bool SetInterPoint(C4DAtom *op, Int32 index, const Vector &move, const Vector &offset, Int32 flags=MODELING_SETPOINT_FLAG_EMPTY);

	// Polygon/Ngon

	Int32 NewNgon(C4DAtom *op, Int32 flags=MODELING_SETNGON_FLAG_EMPTY);
	Int32 AddNgon(C4DAtom *op, const Ngon &ngon, Int32 flags=MODELING_SETNGON_FLAG_EMPTY);
	Int32 CreateNgon(C4DAtom *op, Int32 *padr, Int32 cnt, Int32 flags=MODELING_SETNGON_FLAG_EMPTY);
	Bool DeleteNgon(C4DAtom *op, Int32 index, Bool points);
	Int32 CloneNgon(C4DAtom *op, Int32 index, Int32 flags=MODELING_SETNGON_FLAG_EMPTY);
	Bool GetNgon(C4DAtom *op, Int32 index, Ngon *ngon, Int32 flags=MODELING_GETNGON_FLAG_EMPTY);
	Bool SetNgon(C4DAtom *op, Int32 index, Ngon &ngon, Int32 flags=MODELING_SETNGON_FLAG_EMPTY);
	Bool GetNgonNormal(C4DAtom *op, Int32 index, Vector *n);
	Bool FlipNgonNormal(C4DAtom *op, Int32 index);
	Bool GetOriginNgon(C4DAtom *op, Int32 index, Int32 &ci);
	Bool SetOriginNgon(C4DAtom *op, Int32 index, Int32 ci);
	Int32 GetNgonFlags(C4DAtom *op, Int32 index);
	Int32 SetNgonFlags(C4DAtom *op, Int32 index, Int32 flags);
	Bool ResizeNgon(C4DAtom *op, Int32 index, Int32 pcnt, Int32 scnt);

	// Operations

	Bool WeldPoints(C4DAtom *op, Int32 source, Int32 dest);
	Bool InsertFacePoint(C4DAtom *op, Int32 pa, Int32 p1);
	Bool CreateHole(C4DAtom *op, Int32 index, const Ngon &ngon);
	Bool CreateHole(C4DAtom *op, Int32 index, Int32 *pnts, Int32 pcnt);

	Int32 SplitEdge(C4DAtom *op, Int32 p1, Int32 p2, Float l);
	Bool DeleteEdge(C4DAtom *op, Int32 index, Int32 p1, Int32 p2);

	Bool MeltEdgeBetween(C4DAtom *op, Int32 pa, Int32 pb, Int32 p1, Int32 p2);
	Bool MeltEdge(C4DAtom *op, Int32 pa, Int32 p1, Int32 p2);
	Bool MeltPoint(C4DAtom *op, Int32 p);
	Bool MeltNgon(C4DAtom *op, Int32 pa);

	Int32 SplitPolygon(C4DAtom *op, Int32 index, Int32 p1, Int32 p2);
	Bool MergePolygons(C4DAtom *op, Int32 pa, Int32 pb);

	Bool IsValidEdge(C4DAtom *op, Int32 index, Int32 p1, Int32 p2);
	Bool IsValidNgon(C4DAtom *op, Int32 index);
	Bool IsValidPoint(C4DAtom *op, Int32 index);

	Int32 *GetEdgeNgons(C4DAtom *op, Int32 p1, Int32 p2, Int32 &pcnt);
	Int32 *GetPointNgons(C4DAtom *op, Int32 p, Int32 &pcnt, Bool clone=true);
	Int32 *GetNeighborNgons(C4DAtom *op, Int32 index, Int32 &pcnt);
	Int32 *GetPointEdges(C4DAtom *op, Int32 p, Int32 &ecnt);

	Bool FindNgon(C4DAtom *op, Int32 p1, Int32 p2, Int32 &index);
	Bool GetEdgeSegment(C4DAtom *op, Int32 pa, Int32 p1, Int32 p2, Int32 *seg, Int32 *s1, Int32 *s2, Bool rel);

	Bool GetOriginalEdgePoints(C4DAtom *op, Int32 edge, Int32 &p1, Int32 &p2);

	Bool IsEdgeDeleted(C4DAtom *op, Int32 p1, Int32 p2);
	Bool IsPointDeleted(C4DAtom *op, Int32 index);
	Bool IsFaceDeleted(C4DAtom *op, Int32 index);

	Int32 TranslateNgonIndex(C4DAtom *op, Int32 index, Bool tovirtual=false);
	Int32 TranslatePointIndex(C4DAtom *op, Int32 index, Bool tovirtual=false);

	Bool GetFaceSelection(C4DAtom *op, BaseSelect *select, BaseSelect *faceselect, BaseSelect *hidden=nullptr);
	Bool GetEdgeSelection(C4DAtom *op, BaseSelect *select, BaseSelect *edgeselect, BaseSelect *hidden=nullptr);
	Int32 *GetEdgeSelectionArray(C4DAtom *op, BaseSelect *select, Int32 &ecnt, BaseSelect *hidden=nullptr, Bool tovirtual=true);

	// Information

	Int32 GetLastError(C4DAtom *op);
	Bool IsModified(C4DAtom *op);

	// Management

	void FreeTable(C4DAtom *op, void *table);

	// Helper

	Bool PointInFace(C4DAtom *op, Int32 index, const Vector &p);
	Bool PointInFace(C4DAtom *op, const Ngon &ngon, const Vector &p);
	Bool LineFaceIntersection(C4DAtom *op, Int32 index, const Vector &p1, const Vector &p2);
	Bool LineFaceIntersection(C4DAtom *op, const Ngon &ngon, const Vector &p1, const Vector &p2);

	// Hooks

	void SetTriangulateHook(C4DAtom *op, TriangulateHook pHook, void *pData);
	void GetTriangulateHook(C4DAtom *op, TriangulateHook *ppHook, void **ppData);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

//////////////////////////////////////////////////////////////////////////
#define LIBRARY_MODELLING	1015814
//////////////////////////////////////////////////////////////////////////

struct ModelingLib : public C4DLibrary
{
	iModeling *(*Alloc)();
	void (*Free)(iModeling *&p);

	Bool (iModeling::*InitArray)(AtomArray *objs, Int32 flags);
	Bool (iModeling::*InitObject)(C4DAtom *op, Int32 flags);
	Bool (iModeling::*Commit)(C4DAtom *op, Int32 flags, BaseObject* cobj);
	void (iModeling::*Release)();
	void (iModeling::*ReleaseObject)(C4DAtom *op);

	Int32 (iModeling::*AddPoint)(C4DAtom *op, const Vector &p);
	Int32 (iModeling::*ClonePoint)(C4DAtom *op, Int32 index);
	Bool (iModeling::*DeletePoint)(C4DAtom *op, Int32 index);
	Bool (iModeling::*GetPoint)(C4DAtom *op, Int32 index, Vector *p);
	Bool (iModeling::*SetPoint)(C4DAtom *op, Int32 index, const Vector &p, Int32 flags);
	Bool (iModeling::*SetEdgePoint)(C4DAtom *op, Int32 index, Float l, Int32 flags);
	Bool (iModeling::*SetPoints)(C4DAtom *op, PointMove *pnts, Int32 cnt, Bool commit, Int32 flags);

	Int32 (iModeling::*NewNgon)(C4DAtom *op, Int32 flags);
	Int32 (iModeling::*AddNgon)(C4DAtom *op, const Ngon &ngon, Int32 flags);
	Int32 (iModeling::*CreateNgon)(C4DAtom *op, Int32 *padr, Int32 cnt, Int32 flags);
	Bool (iModeling::*DeleteNgon)(C4DAtom *op, Int32 index, Bool points);
	Int32 (iModeling::*CloneNgon)(C4DAtom *op, Int32 index, Int32 flags);
	Bool (iModeling::*GetNgon)(C4DAtom *op, Int32 index, Ngon *ngon, Int32 flags);
	Bool (iModeling::*SetNgon)(C4DAtom *op, Int32 index, Ngon &ngon, Int32 flags);
	Bool (iModeling::*GetNgonNormal)(C4DAtom *op, Int32 index, Vector *n);
	Bool (iModeling::*FlipNgonNormal)(C4DAtom *op, Int32 index);

	Int32 (iModeling::*SplitEdge)(C4DAtom *op, Int32 p1, Int32 p2, Float l);
	Bool (iModeling::*DeleteEdge)(C4DAtom *op, Int32 index, Int32 p1, Int32 p2);

	Bool (iModeling::*MeltEdgeBetween)(C4DAtom *op, Int32 pa, Int32 pb, Int32 p1, Int32 p2);
	Bool (iModeling::*MeltEdge)(C4DAtom *op, Int32 pa, Int32 p1, Int32 p2);
	Bool (iModeling::*MeltPoint)(C4DAtom *op, Int32 p);

	Int32 (iModeling::*SplitPolygon)(C4DAtom *op, Int32 index, Int32 p1, Int32 p2);
	Bool (iModeling::*MergePolygons)(C4DAtom *op, Int32 pa, Int32 pb);

	Bool (iModeling::*IsValidEdge)(C4DAtom *op, Int32 index, Int32 p1, Int32 p2);
	Bool (iModeling::*IsValidNgon)(C4DAtom *op, Int32 index);
	Bool (iModeling::*IsValidPoint)(C4DAtom *op, Int32 index);

	Int32 *(iModeling::*GetEdgeNgons)(C4DAtom *op, Int32 p1, Int32 p2, Int32 &pcnt);
	Int32 *(iModeling::*GetPointNgons)(C4DAtom *op, Int32 p, Int32 &pcnt, Bool clone);
	Int32 *(iModeling::*GetNeighborNgons)(C4DAtom *op, Int32 index, Int32 &pcnt);
	Int32 *(iModeling::*GetPointEdges)(C4DAtom *op, Int32 p, Int32 &ecnt);
	Bool (iModeling::*FindNgon)(C4DAtom *op, Int32 p1, Int32 p2, Int32 &index);

	Bool (iModeling::*GetOriginalEdgePoints)(C4DAtom *op, Int32 edge, Int32 &p1, Int32 &p2);
	Bool (iModeling::*IsEdgeDeleted)(C4DAtom *op, Int32 p1, Int32 p2);

	Int32 (iModeling::*TranslateNgonIndex)(C4DAtom *op, Int32 index, Bool tovirtual);
	Int32 (iModeling::*TranslatePointIndex)(C4DAtom *op, Int32 index, Bool tovirtual);

	Bool (iModeling::*GetPointMap)(C4DAtom *op, Int32 **map, Int32 *count);
	Bool (iModeling::*GetNgonMap)(C4DAtom *op, Int32 **map, Int32 *count);
	Bool (iModeling::*ReleaseMap)(C4DAtom *op, Int32 *map);
	Bool (iModeling::*FreeMap)(C4DAtom *op, Int32 *map);

	Int32 (iModeling::*GetLastError)(C4DAtom *op);
	Bool (iModeling::*IsModified)(C4DAtom *op);

	Bool (iModeling::*GetPointInfo)(C4DAtom *op, Int32 index, Int32 &ia, Int32 &ib, Float &t);
	Bool (iModeling::*GetOriginPoint)(C4DAtom *op, Int32 index, Int32 &ci);
	Bool (iModeling::*GetOriginNgon)(C4DAtom *op, Int32 index, Int32 &ci);

	Bool (iModeling::*SetOriginNgon)(C4DAtom *op, Int32 index, Int32 ci);
	Int32 (iModeling::*GetNgonFlags)(C4DAtom *op, Int32 index);
	Int32 (iModeling::*SetNgonFlags)(C4DAtom *op, Int32 index, Int32 flags);

	Bool (iModeling::*SetPointInfo)(C4DAtom *op, Int32 index, Int32 ia, Int32 ib, Float t);
	Bool (iModeling::*SetOriginPoint)(C4DAtom *op, Int32 index, Int32 ci);
	Int32 (iModeling::*GetPointFlags)(C4DAtom *op, Int32 index);
	Int32 (iModeling::*SetPointFlags)(C4DAtom *op, Int32 index, Int32 flags);

	Bool (iModeling::*GetPointOrigin)(C4DAtom *op, Int32 index, Vector &opnt);
	Bool (iModeling::*SetPointOrigin)(C4DAtom *op, Int32 index, Vector opnt, Int32 flags);
	Bool (iModeling::*SetInterPointBetween)(C4DAtom *op, Int32 index, Vector npnt, Float t, Int32 flags);
	Bool (iModeling::*WeldPoints)(C4DAtom *op, Int32 source, Int32 dest);
	Bool (iModeling::*MeltNgon)(C4DAtom *op, Int32 pa);

	Bool (iModeling::*IsPointDeleted)(C4DAtom *op, Int32 index);
	Bool (iModeling::*IsFaceDeleted)(C4DAtom *op, Int32 index);

	Bool (iModeling::*SetInterPointMove)(C4DAtom *op, Int32 index, const Vector &move, const Vector &offset, Int32 flags);

	Bool (iModeling::*GetFaceSelection)(C4DAtom *op, BaseSelect *select, BaseSelect *faceselect, BaseSelect *hidden);
	Bool (iModeling::*GetEdgeSelection)(C4DAtom *op, BaseSelect *select, BaseSelect *edgeselect, BaseSelect *hidden);
	Int32 *(iModeling::*GetEdgeSelectionArray)(C4DAtom *op, BaseSelect *select, Int32 &ecnt, BaseSelect *hidden, Bool tovirtual);
	Bool (iModeling::*InsertFacePoint)(C4DAtom *op, Int32 pa, Int32 p1);
	Bool (iModeling::*CreateHole)(C4DAtom *op, Int32 index, const Ngon &ngon);
	Bool (iModeling::*CreateHoleFromPoints)(C4DAtom *op, Int32 index, Int32 *pnts, Int32 pcnt);
	Bool (iModeling::*ResizeNgon)(C4DAtom *op, Int32 index, Int32 pcnt, Int32 scnt);
	Bool (iModeling::*GetEdgeSegment)(C4DAtom *op, Int32 pa, Int32 p1, Int32 p2, Int32 *seg, Int32 *s1, Int32 *s2, Bool rel);

	void (iModeling::*FreeTable)(void *table);

	Bool (iModeling::*PointInFace)(C4DAtom *op, Int32 index, const Vector &p);
	Bool (iModeling::*PointInFaceNgon)(C4DAtom *op, const Ngon &ngon, const Vector &p);
	Bool (iModeling::*LineFaceIntersection)(C4DAtom *op, Int32 index, const Vector &p1, const Vector &p2);
	Bool (iModeling::*LineFaceIntersectionNgon)(C4DAtom *op, const Ngon &ngon, const Vector &p1, const Vector &p2);

	void (iModeling::*SetTriangulateHook)(C4DAtom *op, TriangulateHook pHook, void *pData);
	void (iModeling::*GetTriangulateHook)(C4DAtom *op, TriangulateHook *ppHook, void **ppData);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif
