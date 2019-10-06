/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _LIB_NGON_H_
#define _LIB_NGON_H_

#include "c4d_library.h"

class iNgonBase;
class NgonCache;
class HyperFile;
struct VariableChanged;
class PolygonObject;

//////////////////////////////////////////////////////////////////////////

class Ngon
{
public:

	Ngon();
	~Ngon();
	Ngon(const CPolygon &ply);
	Ngon(const Ngon &src);

	Ngon &operator=(const Ngon &src);

	Bool Alloc(Int32 cnt, Int32 scnt);
	void Free();
	Bool CopyFrom(const Ngon *src);
	Bool CopyFrom(Int32 cnt, Int32 scnt, Int32* pts, Int32* segs);
	void Release();

	Float CalcArea(Int32 seg, const Vector* p, Matrix& m);

	//

	Int32	*points;
	Int32	*segments;
	Int32	count;
	Int32	segcount;
};

//////////////////////////////////////////////////////////////////////////

#ifndef NOTINDEX
#define NOTINDEX				(LIMIT<Int32>::MAX)
#endif

#define PGONEDGE_REPEAT			(0x80000000)
#define PGONEDGE_RESET			(0x7FFFFFFF)
#define PGONEDGE_NOEDGES		(0x40000000)
#define PGONEDGE_EDGEINDEX		(0x1FFFFFFF)
#define PGONEDGE_ENDSEGMENT		(0x20000000)

class PgonEdge
{
public:
	inline Bool IsFirst()	// true if this is the first occurrence of a polygon in the group
	{
		return !(edge_index&PGONEDGE_REPEAT);
	}
	inline Bool IsSegmentEnd()
	{
		return (edge_index&PGONEDGE_ENDSEGMENT);
	}
	inline Int32 ID()
	{
		return (edge_index&PGONEDGE_EDGEINDEX)/4;
	}
	inline Int32 State()
	{
		Int32 edge=Edge();
		if (edge==NOTOK) return 0;
		return 1<<edge;
	}
	inline Int32 Edge()
	{
		if (edge_index&PGONEDGE_NOEDGES) return NOTOK;
		return (edge_index&PGONEDGE_EDGEINDEX)%4;
	}
	inline Int32 EdgeIndex()
	{
		if (edge_index&PGONEDGE_NOEDGES) return NOTOK;
		return (edge_index&PGONEDGE_EDGEINDEX);
	}
	void GetEdge(const CPolygon *vadr, Int32 &p1, Int32 &p2);
	void RemapPolygon(Int32 new_poly, Int32 new_edge);

	UInt32 edge_index;
};

#ifndef NGONBASE_H__
class Pgon
{
public:

	Vector CalcNormal(const Vector* padr, const CPolygon* polys) const;
	void GetMpRad(const Vector* padr, const CPolygon* polys, Vector &mp, Vector &rad) const;
	inline Int32 GetCount() const { return m_Count; }
	inline PgonEdge *GetEdge(Int32 i) { if (m_Edge) return &m_Edge[i]; else return nullptr; }
	inline Int32 ID(Int32 i) const { return m_Edge[i].ID(); }
	inline Int32 State(Int32 i) const { return m_Edge[i].State(); }
	inline Int32 Edge(Int32 i) const { return m_Edge[i].Edge(); }
	inline Int32 EdgeIndex(Int32 i) const { return m_Edge[i].EdgeIndex(); }
	inline Int32 IsFirst(Int32 i) const { return m_Edge[i].IsFirst(); }
	inline Int32 IsSegmentEnd(Int32 i) const { return m_Edge[i].IsSegmentEnd(); }
	inline Int32 GetIdentity() const { return (m_Count>0)?m_Edge[0].ID():NOTOK; }
	Int32 GetSegmentCount() const;
	Int32 GetSegmentLen(Int32 startedge) const;
	void GetEdge(Int32 i, const CPolygon *vadr, Int32 &p1, Int32 &p2) { m_Edge[i].GetEdge(vadr,p1,p2); }
	Int32 FindPolygon(Int32 id) const;
	UChar GetEdgeState(Int32 id) const;
	Int32 GetPointCount() const;
	Int32 GetPolygonCount() const;
	void UpdateStates();

private:

	PgonEdge	*m_Edge;
	Int32		m_Count;
	UInt32		m_CRC;
};
#endif

//////////////////////////////////////////////////////////////////////////

#define NGON_TOSELECTION_POLYGONS	1
#define NGON_TOSELECTION_OUTLINE	2
#define NGON_TOSELECTION_OUTEREDGES	3
#define NGON_TOSELECTION_INNEREDGES	4
#define NGON_TOSELECTION_HOLES		5

#define NGON_FLAG_NOVALIDATION	(1<<0)	// block ngons from validating when you know their polygon indexes have no changed
										// or you are going to be changing this immediately so don't want them validated
										// this flag is auto removed when the ngons try to validate

#define NGON_FLAG_NOCHANGE		(1<<1)	// (same as _NOVALIDATION) does not auto remove so must be manually removed when not needed (WARNING: DO NOT LEAVE IT SET BEYOND YOUR FUNCTION)

#define NGON_FLAG_NOTRANSLATE	(1<<2)	// block the ngons from translating their polygon indexes when resizeobject is called
										// this flag is not auto remove so must be manually it when not needed (WARNING: DO NOT LEAVE IT SET BEYOND YOUR FUNCTION)

#define NGON_FLAG_SETASVALID	(1<<3)	// block ngons from validating completely but let them update their validation data
										// set ONLY if the polygon indexes might have changed but are known to be valid ngons
										// this flag is auto removed once used

#define NGON_VERIFY_FLAG_REPAIR	(1<<0)	// repair any illegal ngons (removes them)

class NgonBase
{
	friend class ModelingKernelBase;

private:

	NgonBase();
	~NgonBase();

	NgonCache *m_pNgonBase;

public:

	static NgonBase *Alloc();
	static void Free(NgonBase *&p);

	Bool CopyTo(NgonBase *dst);
	Bool Write(HyperFile *hf);
	Bool Read(HyperFile *hf, Int32 id, Int32 level);
	Bool Translate(VariableChanged *vc);
	Bool Changed(PolygonObject *op);

	UChar GetEdgeStates(Int32 id) const;
	Int32 GetCount() const;
	Pgon *GetNgons();

	Bool Resize(Int32 cnt);
	Int32 FindPolygon(Int32 id, Int32 l=-1) const;
	Bool CompactPgons();
	void CheckPoints(PolygonObject *op);
	void UpdateNgons(PolygonObject *op);

	Bool ResetPoints(PolygonObject *op);
	void SetFlags(Int32 flgs);
	Int32 GetFlags() const;
	Int32 GetDirtyCount() const;

	void Dirty();

	void InitMap();
	void FreeMap();

	Bool Remove(Int32 id, Bool force);
	Bool ToSelect(BaseSelect *pSelect, Int32 mode);
	void GetCenter(Int32 id, const CPolygon *vadr, const Vector *padr, Vector *ip, Vector *in);
	Bool RemapEdge(Int32 oedge, Int32 *nedges, Int32 ncnt);
	Bool Create(UInt32 *nedges, Int32 ncnt);
	Bool RemapPolygon(Int32 oply, Int32 nply);
	Bool Copy(Pgon *src, Pgon *dst);

	Bool Validate(PolygonObject *op);
	Bool IsValidNgon(Pgon *pgon, const CPolygon *vadr);

	Int32 BuildNgon(Int32 *inner, Int32 *outer, Int32 icnt, Int32 ocnt, const CPolygon *vadr, const Vector *padr);
	Int32 BuildNgonFromPolys(Int32 *polys, Int32 *outer, Int32 pcnt, Int32 ocnt, const CPolygon *vadr, const Vector *padr);

	Bool Verify(const CPolygon *vadr, Int32 vcnt, UInt32 flags, Pgon *pgon=nullptr);

	Pgon *AllocNgon(Int32 edge_cnt);
	void FreeNgon(Pgon *&pgon);

	Bool SetNgon(Int32 index, Pgon *src);
	Bool SetNgon(Int32 index, UInt32 *edges, Int32 edge_cnt);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#define LIBRARY_NGON	1015903

struct NgonBaseLib : public C4DLibrary
{
	iNgonBase *(*Alloc)();
	void (*Free)(iNgonBase *&p);

	Bool (iNgonBase::*CopyTo)(iNgonBase *dst);
	Bool (iNgonBase::*Write)(HyperFile *hf);
	Bool (iNgonBase::*Read)(HyperFile *hf, Int32 id, Int32 level);
	Bool (iNgonBase::*Translate)(VariableChanged *vc);
	Bool (iNgonBase::*Changed)(PolygonObject *op);

	UChar (iNgonBase::*GetEdgeStates)(Int32 id) const;
	Int32 (iNgonBase::*GetCount)() const;
	Pgon *(iNgonBase::*GetNgons)();

	Bool (iNgonBase::*Resize)(Int32 cnt);
	Int32 (iNgonBase::*FindPolygon)(Int32 id, Int32 l) const;
	Bool (iNgonBase::*CompactPgons)();
	void (iNgonBase::*CheckPoints)(PolygonObject *op);
	void (iNgonBase::*UpdateNgons)(PolygonObject *op);

	Bool (iNgonBase::*ResetPoints)(PolygonObject *op);
	void (iNgonBase::*SetFlags)(Int32 flgs);
	Int32 (iNgonBase::*GetFlags)() const;
	Int32 (iNgonBase::*GetDirtyCount)() const;

	void (iNgonBase::*Dirty)();

	void (iNgonBase::*InitMap)();
	void (iNgonBase::*FreeMap)();

	Bool (iNgonBase::*Remove)(Int32 id, Bool force);
	Bool (iNgonBase::*ToSelect)(BaseSelect *pSelect, Int32 mode);
	void (iNgonBase::*GetCenter)(Int32 id, const CPolygon *vadr, const Vector *padr, Vector *ip, Vector *in);
	Bool (iNgonBase::*RemapEdge)(Int32 oedge, Int32 *nedges, Int32 ncnt);
	Bool (iNgonBase::*Create)(UInt32 *nedges, Int32 ncnt);
	Bool (iNgonBase::*RemapPolygon)(Int32 oply, Int32 nply);
	Bool (iNgonBase::*Copy)(Pgon *src, Pgon *dst);

	Bool (iNgonBase::*Validate)(PolygonObject *op);
	Bool (iNgonBase::*IsValidNgon)(Pgon *pgon, const CPolygon *vadr);

	Int32 (iNgonBase::*BuildNgon)(Int32 *inner, Int32 *outer, Int32 icnt, Int32 ocnt, const CPolygon *vadr, const Vector *padr);
	Int32 (iNgonBase::*BuildNgonFromPolys)(Int32 *polys, Int32 *outer, Int32 pcnt, Int32 ocnt, const CPolygon *vadr, const Vector *padr);

	Bool (iNgonBase::*Verify)(const CPolygon *vadr, Int32 vcnt, UInt32 flags, Pgon *pgon);

	Pgon *(iNgonBase::*AllocNgon)(Int32 edge_cnt);
	void (iNgonBase::*FreeNgon)(Pgon *&pgon);
	Bool (iNgonBase::*SetNgon)(Int32 index, Pgon *src);
	Bool (iNgonBase::*SetNgonE)(Int32 index, UInt32 *edges, Int32 edge_cnt);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif	// _LIB_NGON_H_
