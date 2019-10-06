/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

//---------------------------------------------------
//Spline Helper Class :: Header
//Routines to generate a full set of spline matrices
//incorporating a correct normal
//and accurate spline length to realworld length controls
//---------------------------------------------------
#ifndef _C4D_SPLINEHELP_H_
#define _C4D_SPLINEHELP_H_

#include "ge_math.h"
#include "c4d_library.h"

#ifndef __API_INTERN__
#include "c4d_baseobject.h"
#endif

#define C4D_SPLINEHELP_LIBRARY_ID		1019534

class SplineHelp
{
private:
	SplineHelp();
	~SplineHelp();
public:
	// autoalloc
	static SplineHelp *Alloc(void);
	static void				Free(SplineHelp *&node);

	Bool							InitSpline(BaseObject *op, Vector upvector=Vector(0.0), BaseObject *rail = nullptr, Bool target_rail = true, Bool use_deformed_points = false, Bool force_update = false, Bool use_global_space = true); //must be called before any other command, optional up-vector
	void							FreeSpline(void); //must be called afterwards to free data
	//-----------------------------------------------------
	//helper routines
	Bool							Exists(void);
	Int32							GetSegmentCount(void);
	Float							GetSplineLength(void);
	Float							GetSegmentLength(Int32 segment);
	Matrix						GetVertexMatrix(Int32 index);
	Float							GetPointValue(Float offset, Int32 segment);
	Int32							GetPointIndex(Float offset, Int32 segment);
	Vector						GetPosition(Float offset, Int32 segment = 0, Bool smooth = true, Bool realoffset = false);
	Vector						GetTangent(Float offset, Int32 segment = 0, Bool smooth = true, Bool realoffset = false);
	Vector						GetNormal(Float offset, Int32 segment = 0, Bool smooth = true, Bool realoffset = false);
	Vector						GetCrossNormal(Float offset, Int32 segment = 0, Bool smooth = true, Bool realoffset = false);
	Float							GetOffsetFromUnit(Float unitoffset, Int32 segment = 0);
	Float							GetOffsetFromReal(Float offset, Int32 segment = 0);
	Matrix						GetMatrix(Float offset, Int32 segment = 0, Bool smooth = true, Bool realoffset = false);
	void							GetLinePointSegment(Int32 index, Float *offset, Int32 *ind, Int32 *segment);
	void							GetSplinePointSegment(Int32 index, Float *offset, Int32 *ind, Int32 *segment);
	void							GlobalToLocal(Float offset, Float *off, Int32 *segment, Bool realoffset = false);
	Int32							SplineToLineIndex(Int32 index);

	Float							GetSize(Float offset, Int32 segment = 0, Bool smooth = true, Bool realoffset = false);
	Float							GetVertexSize(Int32 index);
	Int32							GetVertexCount(Int32 segment = NOTOK);
	Matrix						GetVertexMatrix(Int32 segment, Int32 index);

	Bool							IsClosed(Int32 segment = 0);
	SPLINETYPE				GetType(void);

	Bool							CopyTo(SplineHelp *dest);

	Int32							GetPointCount(void);

	void							SetOwner(BaseObject *op);
};


//---------------------------------------------------
//	---INTERNAL STUFF
class iSplineHelp;

struct SplineHelpLibrary : public C4DLibrary
{
	iSplineHelp*			(*Alloc)();
	void							(*Free)(iSplineHelp *&node);


	Bool							(iSplineHelp::*InitSplineEx)(SplineObject *op, Vector upvector);

	void							(iSplineHelp::*FreeSpline)();
	Bool							(iSplineHelp::*Exists)();
	Int32							(iSplineHelp::*GetSegmentCount)();
	Float							(iSplineHelp::*GetSplineLength)();
	Float							(iSplineHelp::*GetSegmentLength)(Int32 segment);
	Float							(iSplineHelp::*GetPointValue)(Float offset, Int32 segment);
	Int32							(iSplineHelp::*GetPointIndex)(Float offset, Int32 segment);

	Vector						(iSplineHelp::*GetPositionEx)(Float offset, Int32 segment, Bool smooth);
	Vector						(iSplineHelp::*GetTangentEx)(Float offset, Int32 segment, Bool smooth);
	Vector						(iSplineHelp::*GetNormalEx)(Float offset, Int32 segment, Bool smooth);
	Vector						(iSplineHelp::*GetCrossNormalEx)(Float offset, Int32 segment, Bool smooth);

	Float							(iSplineHelp::*GetOffsetFromUnit)(Float unitoffset, Int32 segment);
	Float							(iSplineHelp::*GetOffsetFromReal)(Float offset, Int32 segment);

	Matrix						(iSplineHelp::*GetMatrix)(Float offset, Int32 segment, Bool smooth, Bool realoffset);
	void							(iSplineHelp::*GetLinePointSegment)(Int32 index, Float *offset, Int32 *ind, Int32 *segment);
	void							(iSplineHelp::*GetSplinePointSegment)(Int32 index, Float *offset, Int32 *ind, Int32 *segment);
	void							(iSplineHelp::*GlobalToLocal)(Float offset, Float *off, Int32 *segment, Bool realoffset);
	Matrix						(iSplineHelp::*GetVertexMatrix)(Int32 index);
	Int32							(iSplineHelp::*SplineToLineIndex)(Int32 index);

	//MoGraph 2 Updates
	Bool							(iSplineHelp::*InitSpline)(BaseObject *op, Vector upvector, BaseObject *rail, Bool target_rail, Bool use_deformed_points, Bool force_update, Bool use_global_space);
	Vector						(iSplineHelp::*GetPosition)(Float offset, Int32 segment, Bool smooth, Bool realoffset);
	Vector						(iSplineHelp::*GetTangent)(Float offset, Int32 segment, Bool smooth, Bool realoffset);
	Vector						(iSplineHelp::*GetNormal)(Float offset, Int32 segment, Bool smooth, Bool realoffset);
	Vector						(iSplineHelp::*GetCrossNormal)(Float offset, Int32 segment, Bool smooth, Bool realoffset);
	Float							(iSplineHelp::*GetSize)(Float offset, Int32 segment, Bool smooth, Bool realoffset);
	Float							(iSplineHelp::*GetVertexSize)(Int32 index);
	Int32							(iSplineHelp::*GetVertexCount)(Int32 segment);
	Matrix						(iSplineHelp::*GetVertexMatrix2)(Int32 segment, Int32 index);
	Bool							(iSplineHelp::*IsClosed)(Int32 segment);
	SPLINETYPE				(iSplineHelp::*GetType)();
	Bool							(iSplineHelp::*CopyTo)(iSplineHelp *dest);

	Int32							(iSplineHelp::*GetPointCount)();
	void							(iSplineHelp::*SetOwner)(BaseObject *op);
};

#ifdef __API_INTERN__
#include "lib_splinehelp.cpp"
#endif

//	---INTERNAL STUFF
//---------------------------------------------------


#endif


