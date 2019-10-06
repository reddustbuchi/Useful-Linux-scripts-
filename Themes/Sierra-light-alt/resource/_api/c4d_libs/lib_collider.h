/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _LIB_COLIDERCACHE_H_
#define _LIB_COLIDERCACHE_H_

#include "c4d_library.h"

#include "ge_math.h"

// API Return Values

#define COL_OK													 0
#define COL_ERR_OUT_OF_MEMORY						-1
#define COL_ERR_UNPROCESSED_MODEL				-2
#define COL_ERR_WRONG_BUILD_ORDER				-3
#define COL_ERR_EMPTY_OBJECT						-4

// Flags for DoCollide

#define COL_ALL_CONTACTS		1
#define COL_FIRST_CONTACT		2


// Collision Cache

#ifndef _INTERNAL_DEF_COLLIDER_

class GeColliderCache
{
	private:
		GeColliderCache();
		~GeColliderCache();

	public:

		static GeColliderCache* Alloc();
		static void Free(GeColliderCache *&data);

		Bool CopyTo(GeColliderCache *dest);

		Int32 BeginInput(Int32 cnt_tris);
		Int32 AddTriangle(const Vector& p1, const Vector& p2, const Vector& p3, Int32 id);
		Int32 EndInput();
};


// The Collision Engine

class GeColliderEngine
{
	private:
		GeColliderEngine();
		~GeColliderEngine();

	public:

		static GeColliderEngine* Alloc();
		static void Free(GeColliderEngine *&data);

		Int32 DoCollide(const Matrix& M1, GeColliderCache *o1, const Matrix& M2, GeColliderCache *o2, Int32 flag);
		Int32 DoPolyPairs(const Matrix& M1, GeColliderCache *o1, const Matrix& M2, GeColliderCache *o2, Float tolerance);
		Int32 DoTolerance(const Matrix& M1, GeColliderCache *o1, const Matrix& M2, GeColliderCache *o2, Float tolerance);
		Int32 DoDistance(const Matrix& M1, GeColliderCache *o1, const Matrix& M2, GeColliderCache *o2, Float rel_err, Float abs_err);

		void FreePairsList();


	// Results for Collison Query

		Int32 GetNumPairs();
		Int32 GetId1(Int32 k);
		Int32 GetId2(Int32 k);


	// Results for Tolerance Query

		Bool IsCloser();


	// Results for Distance & Tolerance Query

		Float GetDistance();
		const Vector& GetP1();
		const Vector& GetP2();


	// RayCollider API

		Int32 DoRayCollide(GeColliderCache *o1, const Vector &ray_p, const Vector &ray_dir, Float ray_length);
};

struct GeRayColResult
{
		Int32		face_id;
		Int32		tri_face_id;	// if > 0 then face_id + 1 else - (face_id + 1)

		Vector	hitpos;
		Float		distance;
		Vector	s_normal;			// phong normal
		Vector	f_normal;			// face normal
		Vector	barrycoords;	// x = u, y = v, z = d;
		Bool		backface;
};

class GeRayCollider
{
	private:
		GeRayCollider();
		~GeRayCollider();

	public:

		static GeRayCollider* Alloc();
		static void Free(GeRayCollider *&data);

		Bool Init(BaseObject *goal, Bool force = false); // force == true overwrites the (not) dirty flag

		Bool Intersect(const Vector &ray_p, const Vector &ray_dir, Float ray_length, Bool only_test = false);

		Int32 GetIntersectionCount();
		Bool GetIntersection(Int32 number, GeRayColResult *res);
		Bool GetNearestIntersection(GeRayColResult *res);
};

#else

#define GeColliderCache GeColliderCacheI
#define GeColliderEngine GeColliderEngineI
#define GeRayCollider GeRayColliderI

#endif

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF


#define LIB_COLLIDERCACHE 1000487

struct ColliderCacheLib : public C4DLibrary
{
		GeColliderCache*		(*Alloc														)();
		void								(*Free														)(GeColliderCache *&data);
		Bool								(GeColliderCache::*CopyTo					)(GeColliderCache *dest);
		Int32								(GeColliderCache::*BeginInput			)(Int32 cnt_tris);
		Int32								(GeColliderCache::*AddTriangle		)(const Vector& p1, const Vector& p2, const Vector& p3, Int32 id);
		Int32								(GeColliderCache::*EndInput				)();
};

#define LIB_COLLIDERENGINE 1000488

struct ColliderEngineLib : public C4DLibrary
{
		GeColliderEngine*		(*Alloc														)();
		void								(*Free														)(GeColliderEngine *&data);

		Int32								(GeColliderEngine::*DoCollide			)(const Matrix& M1, GeColliderCache *o1, const Matrix& M2, GeColliderCache *o2, Int32 flag);
		Int32								(GeColliderEngine::*DoPolyPairs		)(const Matrix& M1, GeColliderCache *o1, const Matrix& M2, GeColliderCache *o2, Float tolerance);
		Int32								(GeColliderEngine::*DoTolerance		)(const Matrix& M1, GeColliderCache *o1, const Matrix& M2, GeColliderCache *o2, Float tolerance);
		Int32								(GeColliderEngine::*DoDistance		)(const Matrix& M1, GeColliderCache *o1, const Matrix& M2, GeColliderCache *o2, Float rel_err, Float abs_err);
		void								(GeColliderEngine::*FreePairsList	)();
		Int32								(GeColliderEngine::*GetNumPairs		)();
		Int32								(GeColliderEngine::*GetId1				)(Int32 k);
		Int32								(GeColliderEngine::*GetId2				)(Int32 k);
		Bool								(GeColliderEngine::*IsCloser			)();
		Float								(GeColliderEngine::*GetDistance		)();
		const Vector&				(GeColliderEngine::*GetP1					)();
		const Vector&				(GeColliderEngine::*GetP2					)();
		Int32								(GeColliderEngine::*DoRayCollide	)(GeColliderCache *o1, const Vector &ray_p, const Vector &ray_dir, Float ray_lengt);
};

#define LIB_RAYCOLLIDER 1000499

struct RayColliderLib : public C4DLibrary
{
		GeRayCollider*	(*Alloc																)();
		void						(*Free																)(GeRayCollider *&data);

		Bool						(GeRayCollider::*Init									)(BaseObject *goal, Bool force);
		Bool						(GeRayCollider::*Intersect						)(const Vector &ray_p, const Vector &ray_dir, Float ray_length, Bool only_test);
		Int32						(GeRayCollider::*GetIntersectionCount	)();
		Bool						(GeRayCollider::*GetIntersection			)(Int32 number, GeRayColResult *res);
		Bool						(GeRayCollider::*GetNearestIntersection)(GeRayColResult *res);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif
