/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _LIB_INTERSECT_H_
#define _LIB_INTERSECT_H_

#include <stdarg.h>

#include "c4d_library.h"

#define LIBRARY_INTERSECT	1029406 

enum INTERSECTTYPE
{
	INTERSECTTYPE_BVH
} ENUM_END_LIST(INTERSECTTYPE);


struct IntersectHitData
{
	Vector localHitPoint;			// Location of the hitpoint on the surface of the object in the objects local coordinate system
	Vector32 localHitNormal;		// The Normal of the hitpoint on the surface of the object in the objects local coordinate system
	Int32 selectedPolygon;			// The polygon that was hit
	Float distance;					// The distance from rayp
	Bool backface;					// The hit polygon was a backfacing polygon
	PolygonObject *pObject;			// The PolygonObject that was hit
};

class IIntersect
{
private:
	IIntersect();
	~IIntersect();

public:

	//----------------------------------------------------------------------------------------
	/// Create a new intersection object
	/// @param[in] bd							The type of intersection object to create
	/// @return									The new Intersection Object.
	//----------------------------------------------------------------------------------------
	static IIntersect *Alloc(INTERSECTTYPE type);

	//----------------------------------------------------------------------------------------
	/// Free the intersection object
	/// @param[in] isect						The Intersection object to free.
	//----------------------------------------------------------------------------------------
	static void Free(IIntersect*& isect);

	//----------------------------------------------------------------------------------------
	/// Add the PolygonObject to the data structure for intersection testing against the triangles.
	/// Internally this calls Clear() before. 
	/// @param[in] pObject						The PolygonObject to set.
	/// @return									True if the successful, false if not (due to not enough memory).
	//----------------------------------------------------------------------------------------
	Bool Init(PolygonObject *pObject); 

	//----------------------------------------------------------------------------------------
	/// Add another object
	/// @param[in] pObject						The PolygonObject to add.
	/// @return									True if the successful, false if not (due to not enough memory).
	//----------------------------------------------------------------------------------------
	Bool AddObject(PolygonObject *pObject); 

	//----------------------------------------------------------------------------------------
	/// Clear all the data 
	//----------------------------------------------------------------------------------------
	void Clear();

	//----------------------------------------------------------------------------------------
	/// From a viewport cast a ray, in screen space, onto the SculptObject and return any data if the ray hits the object.
	/// This will return the closest hit point if multiple intersections are found. If backfaces is enabled, and the back facing hit point is closer than the front hit point, then it will be returned.
	/// @param[in] bd							The BaseDraw that the user is casting the ray from
	/// @param[in] mx							The x coordinate (IE mouse coordinate) in screen space
	/// @param[in] my							The y coordinate (IE mouse coordinate) in screen space
	/// @param[in] backfaces					Allow back facing polygons to be hit tested.
	/// @param[out] hitData						The intersection data will be filled out if the object was hit
	/// @return									True if the SculptObject was hit, False if not.
	//----------------------------------------------------------------------------------------
	Bool Hit(BaseDraw* bd, Float mx, Float my, Bool backfaces, IntersectHitData  &hitData);

	//----------------------------------------------------------------------------------------
	/// Given a ray in object space do a hit intersection against the SculptObject and return any data if the ray hits the object.
	/// This will return the closest hit point if multiple intersections are found. If backfaces is enabled, and the back facing hit point is closer than the front hit point, then it will be returned.
	/// @param[in] rayp							The starting position of the ray in object space.
	/// @param[in] rayv							The direction the ray is pointing.
	/// @param[in] backfaces					Allow back facing polygons to be hit tested.
	/// @param[out] hitData						The intersection data will be filled out if the object was hit.
	/// @return									True if the SculptObject was hit, False if not.
	//----------------------------------------------------------------------------------------
	Bool Hit(const Vector &rayp, const Vector &rayv, Bool backfaces, IntersectHitData  &hitData);
};

struct IntersectLibrary : public C4DLibrary
{
	IIntersect*				(*intersectAlloc)(INTERSECTTYPE type);
	void					(*intersectFree)(IIntersect *&isect);
	Bool					(*intersectInit)(IIntersect *isect, PolygonObject *pPoly);
	Bool					(*intersectAddObject)(IIntersect *isect, PolygonObject *pPoly);
	void					(*intersectClear)(IIntersect *isect);
	Bool					(*intersectHitScreen)(IIntersect *isect,BaseDraw* bd, Float mx, Float my, Bool backfaces, IntersectHitData &hitData);
	Bool					(*intersectHitObject)(IIntersect *isect,const Vector &rayp, const Vector &rayv, Bool backfaces, IntersectHitData &hitData);
};


#endif
