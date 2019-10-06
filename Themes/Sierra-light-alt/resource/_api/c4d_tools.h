/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DTOOLS_H
#define __C4DTOOLS_H

#include "ge_math.h"
#include "operatingsystem.h"

#ifndef __API_INTERN__
	#include "c4d_string.h"
	#include "c4d_raytrace.h"
	#include "c4d_shader.h"
	#include "c4d_videopostplugin.h"
#endif

#define COLOR		255.99	// converting from vectors to integers
#define PERCENT 100.00
#define THIRD		0.333333333333333333
#define SIXTH		0.166666666666666666

#define MAXRANGE		1.0e20		// maximum value for metric data
#define MAXELEMENTS 100000000	// maximum number of points
#define MIN_EPSILON 0.001			// epsilon value

class Filename;

inline Float64 StepEx(Float64 a, Float64 x)
{
	if (x >= a)
		return 1.0;
	else
		return 0.0;
}

inline Float32 Boxstep(Float32 a, Float32 b, Float32 x)
{
	if (b == a)
	{
		if (x < a)
			return (Float32) 0.0;
		else
			return (Float32) 1.0;
	}
	x = (x - a) / (b - a);
	return x < (Float32) 0.0 ? (Float32) 0.0 : (x > (Float32) 1.0 ? (Float32) 1.0 : x);
}

inline Float64 Boxstep(Float64 a, Float64 b, Float64 x)
{
	if (b == a)
	{
		if (x < a)
			return 0.0;
		else
			return 1.0;
	}
	x = (x - a) / (b - a);
	return x < 0.0 ? 0.0 : (x > 1.0 ? 1.0 : x);
}

inline Float32 Smoothstep(Float32 a, Float32 b, Float32 x)
{
	if (x < a)
		return (Float32) 0.0;
	if (x >= b)
		return (Float32) 1.0;

	x = (x - a) / (b - a);	// normalize to [0,1]

	return x * x * ((Float32) 3.0 - (Float32) 2.0 * x);
}

inline Float64 Smoothstep(Float64 a, Float64 b, Float64 x)
{
	if (x < a)
		return 0.0;
	if (x >= b)
		return 1.0;

	x = (x - a) / (b - a);	// normalize to [0,1]

	return x * x * (3.0 - 2.0 * x);
}

inline Float32 Modulo(Float32 a, Float32 b)
{
	if (b == 0.0)
		return 0.0;
	Int32 n = (Int32) (a / b);

	a -= n * b;
	if (a < 0.0)
		a += b;

	return a;
}

inline Float64 Modulo(Float64 a, Float64 b)
{
	if (b == 0.0)
		return 0.0;
	Int32 n = (Int32) (a / b);

	a -= n * b;
	if (a < 0.0)
		a += b;

	return a;
}

inline Int32 LModulo(Int32 a, Int32 b)
{
	if (!b)
		return 0;
	if (a >= 0)
		return a % b;

	a -= (a / b) * b;
	if (a < 0)
		a += b;

	return a;
}

inline Int64 LModulo(Int64 a, Int64 b)
{
	if (!b)
		return 0;
	if (a >= 0)
		return a % b;

	a -= (a / b) * b;
	if (a < 0)
		a += b;

	return a;
}

inline Float32 Bias(Float32 b, Float32 x)
{
	return Pow(x, Float32(-Ln(b) / (Float32) 0.693147180559945309));
}

inline Float64 Bias(Float64 b, Float64 x)
{
	return Pow(x, Float64(-Ln(b) / 0.693147180559945309));
}

inline Float32 Truncate(Float32 x)
{
	if (x >= (Float32) 0.0)
		return Floor(x);
	else
		return Ceil(x);
}

inline Float64 Truncate(Float64 x)
{
	if (x >= 0.0)
		return Floor(x);
	else
		return Ceil(x);
}

Matrix MatrixMove  (const Vector& t);
Matrix MatrixScale (const Vector& s);
Matrix MatrixRotX  (Float w);
Matrix MatrixRotY  (Float w);
Matrix MatrixRotZ  (Float w);

Vector MatrixToHPB			(const Matrix& m, ROTATIONORDER rot_order);														// calculate euler angles from Matrix
Vector VectorToHPB			(const Vector& p);																										// calculate euler angles from vector, bank always 0.0
Matrix HPBToMatrix			(const Vector& hpb, ROTATIONORDER rot_order);													// construct Matrix from euler angles
void MatrixToRotAxis  (const Matrix& m, Vector* v, Float* w);																	// calculate rotation axis v and angle w from matrix m
Matrix RotAxisToMatrix  (const Vector& v, Float w);																						// calculate matrix from rotation axis v and angle w
Vector GetOptimalAngle  (const Vector& hpb_old, const Vector& hpb_new, ROTATIONORDER order);	// calculate optimal angles between two angle values
Vector PointLineDistance(const Vector& p0, const Vector& v, const Vector& p);
Vector64 ReflectRay(const Vector64& v, const Vector64& n);
Matrix RebuildMatrix(const Matrix& m);

class LMinMax
{
private:
	Vector64 min, max;
	Bool		 used;

public:
	LMinMax(void) { min = Vector64(MAXVALUE_FLOAT64); max = Vector64(MINVALUE_FLOAT64); used = false; }
	LMinMax(const Vector64& v) { min = max = v; used = true; }
	inline void Init(void) { min = Vector64(MAXVALUE_FLOAT64); max = Vector64(MINVALUE_FLOAT64); used = false; }	// reset min and max
	inline void Init(const Vector64& v) { min = max = v; used = true; }
	inline void AddPoint(const Vector64& p)																																				// add point and recalculate min and max
	{
		if (used)
		{
			if (p.x < min.x)
				min.x = p.x;
			if (p.y < min.y)
				min.y = p.y;
			if (p.z < min.z)
				min.z = p.z;
			if (p.x > max.x)
				max.x = p.x;
			if (p.y > max.y)
				max.y = p.y;
			if (p.z > max.z)
				max.z = p.z;
		}
		else
		{
			min	 = max = p;
			used = true;
		}
	}
	inline void AddPoints(const Vector64& a, const Vector64& b)	// add point and recalculate min and max
	{
		used = true;
		if (a.x < min.x)
			min.x = a.x;
		if (a.y < min.y)
			min.y = a.y;
		if (a.z < min.z)
			min.z = a.z;
		if (b.x > max.x)
			max.x = b.x;
		if (b.y > max.y)
			max.y = b.y;
		if (b.z > max.z)
			max.z = b.z;
	}
	inline void Set(const Vector64& a, const Vector64& b)
	{
		used = true;
		min	 = a;
		max	 = b;
	}

	inline Bool Content(void)	const { return used; }
	inline const Vector64& GetMin (void) const
	{
		extern Vector64 l_empty;
		if (used)
			return min;
		else
			return l_empty;
	}
	inline const Vector64& GetMax (void) const
	{
		extern Vector64 l_empty;
		if (used)
			return max;
		else
			return l_empty;
	}
	inline Vector64 GetMp  (void) const
	{
		if (used)
			return (min + max) * 0.5;
		else
			return Vector64(0.0);
	}	// middle between min and max
	inline Vector64 GetRad (void) const
	{
		if (used)
			return (max - min) * 0.5;
		else
			return Vector64(0.0);
	}	// half distance between min and max
	inline void GetMpRad(Vector64* mp, Vector64* rad) const
	{
		if (used)
		{
			*mp = (min + max) * 0.5; *rad = max - *mp;
		}
		else
		{
			*mp = *rad = Vector64(0.0);
		}
	}	// half distance between min and max
};

class SMinMax
{
private:
	Vector32 min, max;
	Bool		 used;

public:
	SMinMax(void) { min = Vector32(MAXVALUE_FLOAT32); max = Vector32(MINVALUE_FLOAT32); used = false; }
	SMinMax(const Vector32& v) { min = max = v; used = true; }
	inline void Init(void) { min = Vector32(MAXVALUE_FLOAT32); max = Vector32(MINVALUE_FLOAT32); used = false; }	// reset min and max
	inline void Init(const Vector32& v) { min = max = v; used = true; }
	inline void AddPoint(const Vector32& p)																																				// add point and recalculate min and max
	{
		if (used)
		{
			if (p.x < min.x)
				min.x = p.x;
			if (p.y < min.y)
				min.y = p.y;
			if (p.z < min.z)
				min.z = p.z;
			if (p.x > max.x)
				max.x = p.x;
			if (p.y > max.y)
				max.y = p.y;
			if (p.z > max.z)
				max.z = p.z;
		}
		else
		{
			min	 = max = p;
			used = true;
		}
	}
	inline void AddPoints(const Vector32& a, const Vector32& b)	// add point and recalculate min and max
	{
		used = true;
		if (a.x < min.x)
			min.x = a.x;
		if (a.y < min.y)
			min.y = a.y;
		if (a.z < min.z)
			min.z = a.z;
		if (b.x > max.x)
			max.x = b.x;
		if (b.y > max.y)
			max.y = b.y;
		if (b.z > max.z)
			max.z = b.z;
	}
	inline void Set(const Vector32& a, const Vector32& b)
	{
		used = true;
		min	 = a;
		max	 = b;
	}

	inline Bool Content(void)	const { return used; }
	inline const Vector32& GetMin (void) const
	{
		extern Vector32 s_empty;
		if (used)
			return min;
		else
			return s_empty;
	}
	inline const Vector32& GetMax (void) const
	{
		extern Vector32 s_empty;
		if (used)
			return max;
		else
			return s_empty;
	}
	inline Vector32 GetMp  (void) const
	{
		if (used)
			return (min + max) * (Float32) 0.5;
		else
			return Vector32(0.0);
	}	// middle between min and max
	inline Vector32 GetRad (void) const
	{
		if (used)
			return (max - min) * (Float32) 0.5;
		else
			return Vector32(0.0);
	}	// half distance between min and max
	inline void GetMpRad(Vector32* mp, Vector32* rad) const
	{
		if (used)
		{
			*mp = (min + max) * (Float32) 0.5; *rad = max - *mp;
		}
		else
		{
			*mp = *rad = Vector32(0.0);
		}
	}	// half distance between min and max
};

#ifdef __FLOAT_32_BIT
typedef SMinMax MinMax;
#else
typedef LMinMax MinMax;
#endif


class Random
{
private:
	UInt32 seed;
	Int32	 iset;
	Float	 gset;

public:
	Random(void);

	void Init(UInt32 s);

	Float Get01(void);	// return random value between 0 and +1
	Float Get11(void);	// return random value between -1 and +1

	Float GetG01(void);	// return random value between 0 and +1 with gaussian distribution
	Float GetG11(void);	// return random value between -1 and +1 with gaussian distribution

	Int32 GetSeed(void) { return seed; }
};

Vector RGBToHSV(const Vector& col);
Vector HSVToRGB(const Vector& col);
Vector RGBToHSL(const Vector& col);
Vector HSLtoRGB(const Vector& col);

struct RayShaderStackElement
{
	TexList* texture;
	void*		 texture_link;
	Float32	 visibility;
};

struct MsgGICSExData
{
	Int32			action;	// 0: load; 1: save; 2:flush
	Filename* fn;
	Bool			success;
};

struct MsgGINewData
{
	Int32						 action;	// 0: Animation Prepass, 1 - Net Cache File Notify, 2 - NET Cache File, 3 - Cache Reload, 10 - Baker State
	VideoPostStruct* vps;
	Filename*				 fn;
	Bool						 success;
	Int32						 state;
	Float						 scale;
};

#ifndef __API_INTERN__

inline Vector TransformColor(const Vector& v, COLORSPACETRANSFORMATION colortransformation) { return C4DOS.Sh->TransformColor(v, colortransformation); }

class Stratified2DRandom
{
private:
	Stratified2DRandom();
	~Stratified2DRandom();

public:
	Bool Init(Int32 initial_value, Bool reset) { return (this->*C4DOS.Sh->SNInit)(initial_value, reset); }
	void GetNext(Float* xx, Float* yy) { (this->*C4DOS.Sh->SNGetNext)(xx, yy); }

	static Stratified2DRandom* Alloc(void) { return C4DOS.Sh->SNAlloc(); }
	static void Free(Stratified2DRandom*& rnd) { C4DOS.Sh->SNFree(rnd); rnd = nullptr; }
};

inline Float SNoise(const Vector& p) { return C4DOS.Sh->SNoise(p); }
inline Float SNoise(const Vector& p, Float t) { return C4DOS.Sh->SNoiseT(p, t); }
inline Float Noise(const Vector& p) { return C4DOS.Sh->Noise(p); }
inline Float Noise(const Vector& p, Float t) { return C4DOS.Sh->NoiseT(p, t); }
inline Float PNoise(const Vector& p, const Vector& d) { return C4DOS.Sh->PNoise(p, d); }
inline Float PNoise(const Vector& p, Float t, const Vector& d, Float dt) { return C4DOS.Sh->PNoiseT(p, t, d, dt); }
inline Float Turbulence(const Vector& p, Float oct, Bool abs) { return C4DOS.Sh->Turbulence(p, oct, abs); }
inline Float Turbulence(const Vector& p, Float t, Float oct, Bool abs)  { return C4DOS.Sh->TurbulenceT(p, t, oct, abs); }
inline Float WavyTurbulence(const Vector& p, Float t, Float oct, Float start)  { return C4DOS.Sh->WavyTurbulence(p, t, oct, start); }
inline void	InitFbm(Float* table, Int32 max_octaves, Float lacunarity, Float h)  { C4DOS.Sh->InitFbm(table, max_octaves, lacunarity, h); }
inline Float Fbm(Float* table, const Vector& p, Float oct) { return C4DOS.Sh->Fbm(table, p, oct); }
inline Float Fbm(Float* table, const Vector& p, Float t, Float oct)  { return C4DOS.Sh->FbmT(table, p, t, oct); }
inline Float RidgedMultifractal(Float* table, const Vector& p, Float oct, Float offset, Float gain)  { return C4DOS.Sh->RidgedMultifractal(table, p, oct, offset, gain); }
inline Float CalcSpline(Float x, Float* knot, Int32 nknots)  { return C4DOS.Sh->CalcSpline(x, knot, nknots); }
inline Vector	CalcSpline(Float x, Vector* knot, Int32 nknots)  { return C4DOS.Sh->CalcSplineV(x, knot, nknots); }

	#define NOISE_RESOLUTION 1024

inline Float SNoiseP(Vector p, Float t, Int32 t_repeat) { return C4DOS.Sh->SNoiseP(p, t, t_repeat); }
inline Float TurbulenceP(Vector p, Float t, Float oct, Bool abs, Int32 t_repeat) { return C4DOS.Sh->TurbulenceP(p, t, oct, abs, t_repeat); }
inline Float FbmP(Float* table, Vector p, Float t, Float oct, Int32 t_repeat) { return C4DOS.Sh->FbmP(table, p, t, oct, t_repeat); }
inline Float RidgedMultifractalP(Float* table, Vector p, Float t, Float oct, Float offset, Float gain, Int32 t_repeat) { return C4DOS.Sh->RidgedMultifractalP(table, p, t, oct, offset, gain, t_repeat); }

struct DisplaceInfo
{
	DisplaceInfo()
	{
		dispn = nullptr;
		displacenum = nullptr;
	};
	Vector* dispn;
	Int32*	displacenum;
};

struct VolumeData : public BaseVolumeData
{
private:
	VolumeData();
	~VolumeData();

public:
	// illumination functions
	void CalcArea(RayLight* light, Bool nodiffuse, Bool nospecular, Float specular_exponent, const Vector64& ray_vector, const Vector64& p, const Vector64& bumpn, const Vector64& orign, RAYBIT raybits, Vector* diffuse, Vector* specular) { C4DOS.Sh->CalcArea(this, light, nodiffuse, nospecular, specular_exponent, ray_vector, p, bumpn, orign, raybits, diffuse, specular); }
	Vector CalcShadow(RayLight* l, const Vector64& p, const Vector64& bumpn, const Vector64& phongn, const Vector64& orign, const Vector64& rayv, Bool transparency, const RayHitID& hitid, RAYBIT raybits) { return C4DOS.Sh->CalcShadow(this, l, p, bumpn, phongn, orign, rayv, transparency, hitid, raybits); }

	Bool IlluminateSurfacePoint(RayLight* rl, Vector* col, Vector64* light_vector, const Vector64& p, const Vector64& bumpn, const Vector64& phongn, const Vector64& orign, const Vector64& ray_vector, ILLUMINATEFLAGS flags, const RayHitID& hitid, RAYBIT raybits, Bool cosine_cutoff) { return C4DOS.Sh->Illuminate(this, rl, col, light_vector, p, bumpn, phongn, orign, ray_vector, flags, hitid, raybits, cosine_cutoff, nullptr); }
	Bool IlluminateAnyPoint    (RayLight* rl, Vector* col, Vector64* light_vector, const Vector64& p, ILLUMINATEFLAGS flags, RAYBIT raybits) { return C4DOS.Sh->Illuminate(this, rl, col, light_vector, p, Vector64(0.0), Vector64(0.0), Vector64(0.0), Vector64(0.0), flags, RayHitID(), raybits, false, nullptr); }

	void IlluminanceSurfacePoint(IlluminanceSurfacePointData* f, Vector* diffuse, Vector* specular) { C4DOS.Sh->IlluminanceSurfacePoint(this, f, diffuse, specular); }
	Vector IlluminanceAnyPoint(const Vector64& p, ILLUMINATEFLAGS flags, RAYBIT raybits) { return C4DOS.Sh->IlluminanceAnyPoint(this, p, flags, raybits); }
	void IlluminanceSimple(Vector* diffuse, Vector* specular, Float exponent, IlluminationModel* model, void* data)
	{
		if (data)
			C4DOS.Sh->Illuminance(this, diffuse, specular, model, data);
		else
			C4DOS.Sh->Illuminance1(this, diffuse, specular, exponent);
	}

	Int32 GetCurrentCPU(void) { return C4DOS.Sh->GetCurrentCPU(this); }
	Int32 GetCPUCount(void) { return C4DOS.Sh->GetCPUCount(this); }
	Int32	Obj_to_Num(RayObject* obj) { return C4DOS.Sh->Obj_to_Num(this, obj); }
	RayObject* GetObj(Int32 index) { return C4DOS.Sh->GetObj(this, index); }
	Int32 GetObjCount(void) { return C4DOS.Sh->GetObjCount(this); }
	void GetUVW(RayObject* op, Int32 uvwind, Int32 local_id, PolyVector* uvw) { C4DOS.Sh->GetUVW(this, op, uvwind, local_id, uvw); }
	void GetNormals(RayObject* op, Int32 local_id, PolyVector* norm) { C4DOS.Sh->GetNormals(this, op, local_id, norm); }
	TexData* GetTexData(RayObject* op, Int32 index) { return C4DOS.Sh->GetTexData(this, op, index); }
	Vector64 GetNormal(RayObject* op, Int32 polygon, Bool second) { return C4DOS.Sh->GetNormal(this, op, polygon, second); }
	Int32	GetRayPolyState(RayObject* op, Int32 local_id) { return C4DOS.Sh->GetRayPolyState(this, op, local_id); }
	Int32* GetUniqueID(RayObject* op, Int32& length) { return C4DOS.Sh->GetUniqueID(this, op, length); }
	Vector64 GetSmoothedNormal(const RayHitID& hitid, const Vector64& p) { return C4DOS.Sh->GetSmoothedNormal(this, hitid, p); }
	Bool GetRS(const RayHitID& hitid, const Vector64& p, Float* r, Float* s) { return C4DOS.Sh->GetRS(this, hitid, p, r, s); }
	void GetWeights(const RayHitID& hitid, const Vector64& p, RayPolyWeight* wgt) { C4DOS.Sh->GetWeights(this, hitid, p, wgt); }
	RayLight* GetLight(Int32 index) { return C4DOS.Sh->GetLight(this, index); }
	Int32 GetLightCount(void) { return C4DOS.Sh->GetLightCount(this); }
	Int32	Light_to_Num(RayLight* light) { return C4DOS.Sh->Light_to_Num(this, light); }
	void* GetRayData(Int32 i) { return C4DOS.Sh->GetRayData(this, i); }
	RayCamera* GetRayCamera(void) { return (RayCamera*)C4DOS.Sh->GetRayData(this, RAY_CAMERA); }
	RayParameter* GetRayParameter(void) { return (RayParameter*)C4DOS.Sh->GetRayData(this, RAY_PARAMETER); }
	RayEnvironment* GetRayEnvironment(void) { return (RayEnvironment*)C4DOS.Sh->GetRayData(this, RAY_ENVIRONMENT); }
	RayObject* GetRaySky(void) { return (RayObject*)C4DOS.Sh->GetRayData(this, RAY_SKY); }
	RayObject* GetRayForeground(void) { return (RayObject*)C4DOS.Sh->GetRayData(this, RAY_FOREGROUND); }
	RayObject* GetRayBackground(void) { return (RayObject*)C4DOS.Sh->GetRayData(this, RAY_BACKGROUND); }
	void GetRay(Float x, Float y, Ray* ray) { C4DOS.Sh->GetRay(this, x, y, ray); }
	Vector64 ScreenToCamera(const Vector64& p) { return C4DOS.Sh->ScreenToCamera(this, p); }
	Vector64 CameraToScreen(const Vector64& p) { return C4DOS.Sh->CameraToScreen(this, p); }
	Vector CalcHardShadow(const Vector64& p1, const Vector64& p2, CALCHARDSHADOW flags, const RayHitID& last_hit, Int32 recursion_id = 0, void* recursion_data = nullptr) { return C4DOS.Sh->CalcHardShadow(this, p1, p2, flags, last_hit, recursion_id, recursion_data); }
	Vector GetPointUVW(TexData* tdp, const RayHitID& hit, const Vector64& p) { return C4DOS.Sh->GetPointUVW(this, tdp, hit, p); }
	Bool ProjectPoint(TexData* tdp, const RayHitID& hit, const Vector64& p, const Vector64& n, Vector* uv) { return C4DOS.Sh->ProjectPoint(this, tdp, hit, p, n, uv); }
	void StatusSetText(const String& str) { C4DOS.Sh->StatusSetText(this, &str); }
	void StatusSetBar(Float percentage) { C4DOS.Sh->StatusSetBar(this, percentage); }
	void StatusSetSpinMode(Bool on) { C4DOS.Sh->StatusSetSpinMode(this, on); }
	Vector CalcVisibleLight(Ray* ray, Float maxdist, Vector* trans) { return C4DOS.Sh->CalcVisibleLight(this, ray, maxdist, trans); }
	void GetXY(Int32* x, Int32* y, Int32* scale) { C4DOS.Sh->GetXY(this, x, y, scale); }
	void SetXY(Float x, Float y) { C4DOS.Sh->SetXY(this, x, y); }
	MinMax GetSceneBoundaries(void) { Vector64 min, max; MinMax MM; C4DOS.Sh->GetSceneBoundaries(this, min, max); MM.Set(min, max); return MM; }
	void CopyTo(VolumeData* dst) { C4DOS.Sh->CopyVolumeData(this, dst); }
	void Init(VolumeData* from) { C4DOS.Sh->InitVolumeData(from, this); }
	void OutOfMemory(void) { C4DOS.Sh->OutOfMemory(this); }
	Bool CalcFgBg(Bool foreground, Int32 x, Int32 y, Int32 subx, Int32 suby, Vector* color, Float* alpha) { return C4DOS.Sh->CalcFgBg(this, foreground, x, y, subx, suby, color, alpha); }
	Float	GetLightFalloff(Int32 falloff, Float inner, Float outer, Float dist) { return C4DOS.Sh->GetLightFalloff(falloff, inner, outer, dist); }
	Bool TestBreak(void) { return C4DOS.Sh->TestBreak(this); }
	BaseVideoPost* GetVideoPost(Int32 nth) { return C4DOS.Sh->FindVideoPost(this, nth, true); }
	BaseVideoPost* FindVideoPost(Int32 id) { return C4DOS.Sh->FindVideoPost(this, id, false); }
	VPFragment** GetFragments(Int32 x, Int32 y, Int32 cnt, VPGETFRAGMENTS flags) { return C4DOS.Sh->VPGetFragments(this, x, y, cnt, flags); }
	Bool AddLensGlow(LensGlowStruct* lgs, Vector* lgs_pos, Int32 lgs_cnt, Float intensity, Bool linear_workflow) { return C4DOS.Sh->AddLensGlow(this, lgs, lgs_pos, lgs_cnt, intensity, linear_workflow); }
	Bool SampleLensFX(VPBuffer* rgba, VPBuffer* fx, BaseThread* bt) { return C4DOS.Sh->SampleLensFX(this, rgba, fx, bt); }
	Int32	TranslateObjIndex(Int32 index, Bool old_to_new) { return C4DOS.Sh->TranslateObjIndex(this, index, old_to_new); }
	Bool TranslatePolygon(RayObject* op, Int32 local_index, Vector* previous_points) { return C4DOS.Sh->TranslatePolygon(this, op, local_index, previous_points); }

	Vector TraceColor(Ray* ray, Float maxdist, const RayHitID& last_hit, SurfaceIntersection* si) { return C4DOS.Sh->TraceColor(this, ray, maxdist, last_hit, si); }
	Vector TraceColorDirect(Ray* ray, Float maxdist, Int32 raydepth, RAYBIT raybits, const RayHitID& last_hit, Vector64* oldray, SurfaceIntersection* si) { return C4DOS.Sh->TraceColorDirect(this, ray, maxdist, raydepth, raybits, last_hit, oldray, si); }
	Bool TraceGeometry(Ray* ray, Float maxdist, const RayHitID& last_hit, SurfaceIntersection* si)  { return C4DOS.Sh->TraceGeometry(this, ray, maxdist, last_hit, si); }
	Bool TraceGeometryEnhanced(Ray* ray, Float maxdist, const RayHitID& last_hit, Int32 raydepth, RAYBIT raybits, Vector64* oldray, SurfaceIntersection* si)  { return C4DOS.Sh->TraceGeometryEnhanced(this, ray, maxdist, last_hit, raydepth, raybits, oldray, si); }
	void GetSurfaceData(SurfaceData* cd, Bool calc_illum, Bool calc_shadow, Bool calc_refl, Bool calc_trans, Ray* ray, const SurfaceIntersection& si) { C4DOS.Sh->GetSurfaceData(this, cd, calc_illum, calc_shadow, calc_refl, calc_trans, ray, si); }
	Vector CentralDisplacePointUV(RayObject* op, Int32 local_id, Int32 uu, Int32 vv) { return C4DOS.Sh->CentralDisplacePointUV(this, op, local_id, uu, vv); }
	Vector CalcDisplacementNormals(Float par_u, Float par_v, Int32 u0, Int32 v0, Int32 u1, Int32 v1, Int32 u2, Int32 v2, const Vector& a, const Vector& b, const Vector& c, RayObject* op, Int32 polynum) { return C4DOS.Sh->CalcDisplacementNormals(this, par_u, par_v, u0, v0, u1, v1, u2, v2, a, b, c, op, polynum); }
	Vector CentralDisplaceUVGetNormal(RayObject* op, Int32 local_id, Int32 uu, Int32 vv) { return C4DOS.Sh->CentralDisplaceUVGetNormal(this, op, local_id, uu, vv); }
	Bool CentralDisplacePointUVGetBarycentric(RayObject *op, Int32& local_id, Int32& uu, Int32& vv, RayPolyWeight& bary, Bool& displaceQuad) { return C4DOS.Sh->CentralDisplacePointUVGetBarycentric(this, op, local_id, uu, vv, bary, displaceQuad); }
	Bool GetDisplaceInfo(const RayObject* op, DisplaceInfo& info) { return C4DOS.Sh->GetDisplaceInfo(this, op, info); }
	Int32	GetDisplaceNeighbor(const RayObject* op, Int32 local_id, Int32 side) { return C4DOS.Sh->GetDisplaceNeighbor(this, op, local_id, side); }
	void CorrectLocalID(const RayObject* op, Int32& local_id) { C4DOS.Sh->CorrectLocalID(this, op, local_id); }
	Vector CalcBackTransformPoint() { return C4DOS.Sh->CalcBackTransformPoint(this); }

	void SkipRenderProcess(void) { C4DOS.Sh->SkipRenderProcess(this); }

	Render* GetRenderInstance(void) { return C4DOS.Sh->GetRenderInstance(this); }

	void GetDUDV(TexData* tex, const Vector64& p, const Vector64& phongn, const Vector64& orign, const RayHitID& hit, Bool forceuvw, Vector* ddu, Vector* ddv, Bool usetangents) { C4DOS.Sh->GetDUDV(this, tex, p, phongn, orign, hit, forceuvw, ddu, ddv, usetangents); }

	void InitSurfacePointProperties(TexData* td) { C4DOS.Sh->InitSurfacePointProperties(this, td); }

	Bool AttachVolumeDataFake(BaseObject* camera, const BaseContainer& renderdata) { return C4DOS.Sh->AttachVolumeDataFake(this, camera, renderdata, nullptr); }

	Bool SaveShaderStack(RayShaderStackElement*& stack, Int32& stack_cnt) { return C4DOS.Sh->SaveShaderStack(this, stack, stack_cnt); }
	Bool RestoreShaderStack(RayShaderStackElement* stack, Int32 stack_cnt) { return C4DOS.Sh->RestoreShaderStack(this, stack, stack_cnt); }

	RayObject* GetRaySky(Int32 index) { return C4DOS.Sh->GetSky(this, index); }
	Int32	GetRaySkyCount(void) { return C4DOS.Sh->GetSkyCount(this); }

	RaySampler* GetRaySampler(void* guid, Int32 depth) { return C4DOS.Sh->GetSampler(this, guid, depth); }
	Float	GetRayWeight() { return C4DOS.Sh->GetRayWeight(this); }

	Float	CalcAmbientOcclusion(SurfaceIntersection* si, RaySampler* sampler, Float minlength, Float maxlength, Float index, Bool self, Bool trans, Float weight) { return C4DOS.Sh->CalcAmbientOcclusion(this, si, sampler, minlength, maxlength, index, self, trans, weight); }
	Vector CalcSubsurfaceScattering(Vector scattering, Vector absorption, Vector diffuse, Float ior) { return C4DOS.Sh->CalcSubsurfaceScattering(this, scattering, absorption, diffuse, ior); }

	Int32	GetStreamCount() { return C4DOS.Sh->GetStreamCount(this); }
	void GetStreamRay(Int32 stream, Float x, Float y, Ray* ray) { C4DOS.Sh->GetStreamRay(this, stream, x, y, ray); }

	Bool CalcIndirectIllumination(RayHemisphere* hs, Float weight) { return C4DOS.Sh->CalcIndirectIllumination(this, hs, weight); }
	Bool CalcIndirectPDF(const Vector& point, const Vector& normal, const Vector& ray_in, const Vector& ray_out, Float& pdf_qmc, Float& pdf_area, Float& pdf_portal, Float& pdf_sky) { return C4DOS.Sh->CalcIndirectPDF(this, point, normal, ray_in, ray_out, pdf_qmc, pdf_area, pdf_portal, pdf_sky); }
	Bool CalcIndirectPath(VolumeData* sd, const Vector& dir, void* source, void* target) { return C4DOS.Sh->CalcIndirectPath(this, dir, source, target); }

	RayRadianceObject* CreateRadianceMaps() { return C4DOS.Sh->CreateRadianceMaps(this); }
	RayRadianceObject* GetRadianceMaps() { return C4DOS.Sh->GetRadianceMaps(this); }
	Vector CalcRadianceValue(Ray* ray, const SurfaceIntersection& si) { return C4DOS.Sh->CalcRadianceValue(this, ray, si); }
	Vector CalcRadiancePoly(RayRadianceObject* obj, SurfaceIntersection* si, Int32 poly, Int32 u, Int32 v, Bool back) { return C4DOS.Sh->CalcRadiancePoly(this, obj, si, poly, u, v, back); }

	Bool IsPhysicalRender() { return C4DOS.Sh->IsPhysicalRender(this); }
	Float	GetPhysicalCameraIntensity() { return C4DOS.Sh->GetPhysicalCameraIntensity(this); }

	void SetPhysicalRayTime(Float time) { return C4DOS.Sh->SetPhysicalRayTime(this, time); }

	static VolumeData* Alloc(void);	// should normally NOT be used
	static void Free(VolumeData*& vd);
};

RayObject* AllocRayObject(Int32 tex_cnt);
void FreeRayObject(RayObject*& op);

RayLight* AllocRayLight(BaseDocument* doc, BaseObject* op);
void FreeRayLight(RayLight*& lgt);
Bool IlluminateRayLight(RayLight* rl, Vector* color, Vector64* light_vector, const Vector64& p, const Vector64& n);

class VPBuffer
{
private:
	VPBuffer();
	~VPBuffer();

public:
	Int32 GetInfo(VPGETINFO type);
	Bool GetLine(Int32 x, Int32 y, Int32 cnt, void* data, Int32 bitdepth, Bool dithering);
	Bool SetLine(Int32 x, Int32 y, Int32 cnt, void* data, Int32 bitdepth, Bool dithering);

	Int32 GetBw(void) { return C4DOS.Sh->VPGetInfo(this, VPGETINFO_XRESOLUTION); }
	Int32 GetBh(void) { return C4DOS.Sh->VPGetInfo(this, VPGETINFO_YRESOLUTION); }
	Int32 GetBt(void) { return C4DOS.Sh->VPGetInfo(this, VPGETINFO_BITDEPTH); }
	Int32 GetCpp(void) { return C4DOS.Sh->VPGetInfo(this, VPGETINFO_CPP); }
	Bool GetVisibleBit(void) { return C4DOS.Sh->VPGetInfo(this, VPGETINFO_VISIBLE); }
};

struct VideoPostStruct : public BaseVideoPostStruct
{
private:
	VideoPostStruct();
	~VideoPostStruct();
};

class Render
{
private:
	Render();
	~Render();

public:
	Bool AllocateBuffer(Int32 id, Int32 subid, Int32 bitdepth, Bool visible);
	Int32	AllocateBufferFX(Int32 id, const String& name, Int32 bitdepth, Bool visible);
	VPBuffer* GetBuffer(Int32 id, Int32 subid);
	BaseContainer GetRenderData(void);
	void SetRenderData(const BaseContainer& bc);
	VolumeData* GetInitialVolumeData(Int32 cpu);
	void*					GetPrivateData(void);
	Bool SetRenderProperty(Int32 id, const GeData& dat);
	void IccConvert(void* data, Int32 xcnt, Int32 components, Bool inverse);
};

void CalcRestrictionInc(ObjectRestriction* lr, RayObject* op, Bool& nodif, Bool& nospec);


enum BakeTexEnums
{
	// data container
	BAKE_TEX_USE_CAMERA_VECTOR										 = 1006,	// bool
	BAKE_TEX_USE_POLYSELECTION										 = 1007,	// bool
	BAKE_TEX_AMBIENT_OCCLUSION										 = 1009,	// bool
	BAKE_TEX_NORMAL																 = 1010,	// bool
	BAKE_TEX_SURFACECOLOR													 = 1011,	// bool
	BAKE_TEX_COLOR																 = 1012,	// bool
	BAKE_TEX_DIFFUSION														 = 1013,	// bool
	BAKE_TEX_LUMINANCE														 = 1014,	// bool
	BAKE_TEX_ALPHA																 = 1015,	// bool
	BAKE_TEX_ILLUMINATION													 = 1016,	// bool
	BAKE_TEX_SHADOWS															 = 1017,	// bool
	BAKE_TEX_BUMP																	 = 1018,	// bool
	BAKE_TEX_TRANSPARENCY													 = 1019,	// bool
	BAKE_TEX_UVMAP																 = 1040,	// bool
	BAKE_TEX_REFLECTION														 = 1041,	// bool
	BAKE_TEX_DISPLACEMENT													 = 1042,	// bool

	BAKE_TEX_WIDTH																 = 1020,	// long
	BAKE_TEX_HEIGHT																 = 1021,	// long
	BAKE_TEX_PIXELBORDER													 = 1022,	// long
	BAKE_TEX_FILL_COLOR														 = 1023,	// vector
	BAKE_TEX_UV_LEFT															 = 1024,	// real
	BAKE_TEX_UV_RIGHT															 = 1025,	// real
	BAKE_TEX_UV_TOP																 = 1026,	// real
	BAKE_TEX_UV_BOTTOM														 = 1027,	// real
	BAKE_TEX_SUPERSAMPLING												 = 1030,	// long
	BAKE_TEX_USE_BUMP															 = 1031,	// bool
	BAKE_TEX_NO_GI																 = 1032,	// bool
	BAKE_TEX_CONTINUE_UV													 = 1033,	// bool
	BAKE_TEX_USE_PHONG_TAG												 = 1034,	// bool (only needed if BAKE_TEX_CONTINUE_UV is set)
	BAKE_TEX_COLORPROFILE													 = 1035,	// color profile
	// 1400 to 1500 is reserved
	BAKE_TEX_SHOW_STATUS													 = 2000,	// bool
	BAKE_TEX_PROGRESS_BITMAP											 = 2001,	// bool set it true, if you want to show the bitmap in a preview during baking
	BAKE_TEX_GENERATE_UNDO												 = 2002,	// bool
	BAKE_TEX_PREVIEW															 = 2003,	// bool

	BAKE_TEX_COLOR_ILLUM													 = 2100,	// bool
	BAKE_TEX_COLOR_SHADOWS												 = 2101,	// bool
	BAKE_TEX_COLOR_LUMINANCE											 = 2102,	// bool
	BAKE_TEX_COLOR_DIFFUSION											 = 2103,	// bool

	BAKE_TEX_LUMINANCE_DIFFUSION									 = 2110,	// bool

	BAKE_TEX_ILLUMINATION_SHADOWS									 = 2120,	// bool

	BAKE_TEX_NORMAL_METHOD												 = 2130,	// long
	BAKE_TEX_NORMAL_METHOD_OBJECT									 = 1,
	BAKE_TEX_NORMAL_METHOD_TANGENT								 = 2,
	BAKE_TEX_NORMAL_METHOD_WORLD									 = 3,
	BAKE_TEX_NORMAL_FLIP_X												 = 2131,	// bool
	BAKE_TEX_NORMAL_FLIP_Y												 = 2132,	// bool
	BAKE_TEX_NORMAL_FLIP_Z												 = 2133,	// bool
	BAKE_TEX_NORMAL_SWAP_YZ												 = 2134,	// bool
	BAKE_TEX_NORMAL_SOURCE												 = 2135,	// link

	BAKE_TEX_SURFACE_ILLUMINATION									 = 2140,	// bool

	BAKE_TEX_AO_VERTEX_MAP												 = 2150,	// bool
	BAKE_TEX_AO_SELFINTERSECTION									 = 2151,	// bool
	BAKE_TEX_AO_VERTEXMAPS												 = 2152,	// pointer to a BaseContainer that stores all new generated vertex maps

	BAKE_TEX_DISPLACEMENT_SOURCE									 = 2160,	// link to the source object (high-res)
	BAKE_TEX_DISPLACEMENT_HEIGHT									 = 2161,	// a pointer to a Float that will receive the Displacement height
	BAKE_TEX_DISPLACEMENT_METHOD									 = 2163,	// long
	BAKE_TEX_DISPLACEMENT_METHOD_OBJECT						 = 0,
	BAKE_TEX_DISPLACEMENT_METHOD_WORLD						 = 1,
	BAKE_TEX_DISPLACEMENT_METHOD_TANGENT					 = 2,
	BAKE_TEX_DISPLACEMENT_METHOD_INTENSITY				 = 3,
	BAKE_TEX_DISPLACEMENT_METHOD_CENTEREDINTENSITY = 4,
	BAKE_TEX_DISPLACEMENT_METHOD_REDGREEN					 = 5,
	BAKE_TEX_DISPLACEMENT_SUBPOLY									 = 2435,	// bool
	BAKE_TEX_DISPLACEMENT_SUBPOLY_SUBDIVISION			 = 2436,	// long
	BAKE_TEX_DISPLACEMENT_SUBPOLY_ROUND						 = 2437,	// bool
	BAKE_TEX_DISPLACEMENT_SUBPOLY_ROUNDCONTOUR		 = 2438,	// bool
	BAKE_TEX_DISPLACEMENT_SUBPOLY_HQREMAPPING			 = 2439,	// bool
	BAKE_TEX_DISPLACEMENT_SUBPOLY_MAPRESULT				 = 2440,	// bool
	BAKE_TEX_DISPLACEMENT_SUBPOLY_KEEPEDGES				 = 2441,	// bool
	BAKE_TEX_DISPLACEMENT_SUBPOLY_DISTRIBUTION		 = 2442,	// bool

	BAKE_TEX_OPTIMAL_MAPPING											 = 2200,	// long
	BAKE_TEX_OPTIMAL_MAPPING_OFF									 = 0,
	BAKE_TEX_OPTIMAL_MAPPING_CUBIC								 = 1,
	BAKE_TEX_OPTIMAL_MAPPING_ANGLE								 = 2,
	BAKE_TEX_OPTIMAL_MAPPING_RELAXCOUNT						 = 2207,	// long
	BAKE_TEX_OPTIMAL_MAPPING_PREVIEW							 = 2201,	// long

	BAKE_TEX_NO_INIT_BITMAP												 = 5000,	// use this if the MultipassBitmap is already initialized
	BAKE_TEX_AUTO_SIZE														 = 5001,	// bool
	BAKE_TEX_AUTO_SIZE_MIN												 = 5002,	// long
	BAKE_TEX_AUTO_SIZE_MAX												 = 5003,	// long
	BAKE_TEX_AUTO_PIXEL_SIZE											 = 5004,	// real

	BAKE_TEX_STATUSBAR														 = 5005,	// string

	BAKE_TEX_DUMMY
};

enum BAKE_STATE
{
	BAKE_STATE_NONE					= 0,
	BAKE_STATE_PREPARE			= 10000,
	BAKE_STATE_GI_PREPASS		= 10001,
	BAKE_STATE_FILL_IMAGE		= 10002,
	BAKE_STATE_COMPLETE			= 10003,
	BAKE_STATE_INITIALIZE		= 10004,

	BAKE_STATE_RESIZENOTIFY = 19999
} ENUM_END_LIST(BAKE_STATE);

/*
textag : the texture tag you want to bake (must be assigned to an object)
data : bake parameters - see below
bmp : the destination bitmap, if this points to a MultipassBitmap, it must be initialized with the correct width and height before BakeTexture is called
th : the current thread
texuvw : must be valid, if UVW projection is selected in the tag, ignored otherwise
destuvw : if not nullptr, the current projection is transformed into the uvw tag
the only allowed modes for multipass bitmaps are COLORMODE_RGB, COLORMODE_RGBA, COLORMODE_RGBw, COLORMODE_RGBAw, COLORMODE_RGBf, COLORMODE_RGBAf
MultipassBitmaps must be used if BAKE_TEX_AMBIENT_OCCLUSION is set
*/

struct BakeProgressInfo
{
	BakeProgressInfo() { private_data = nullptr; state = BAKE_STATE_NONE; data = nullptr; timedelta = 0; r = 0.0; starttime = 0; version = 2; }
	Int32			 version;
	void*			 private_data;
	BAKE_STATE state;
	void*			 data;	// data is only used in case of a BAKE_STATE_RESIZENOTIFY message
	Int32			 timedelta;
	Float			 r;
	Int32			 starttime;	// the milliseconds when baking started
};

struct BakeTextureResizeNotify
{
	Int32				 w, h;
	BaseBitmap** cake;
	Bool				 result;
};

class GeCipher256
{
private:
	void* hnd;

public:
	GeCipher256();
	~GeCipher256();

	Bool Open(const void* key, Int32 klength, Bool stream);
	void Close();
	void Encrypt(void* mem, Int32 size);
	void Decrypt(void* mem, Int32 size);
};


BAKE_TEX_ERR BakeTexture(BaseDocument* doc, const BaseContainer& data, BaseBitmap* bmp, BaseThread* th, BakeProgressHook* hook, BakeProgressInfo* info);	// data may not be deleted during baking
BaseDocument* InitBakeTexture(BaseDocument* doc, TextureTag* textag, UVWTag* texuvw, UVWTag* destuvw, const BaseContainer& bc, BAKE_TEX_ERR* err = nullptr, BaseThread* th = nullptr);
BaseDocument* InitBakeTexture(BaseDocument* doc, TextureTag** textags, UVWTag** texuvws, UVWTag** destuvws, Int32 cnt, const BaseContainer& bc, BAKE_TEX_ERR* err = nullptr, BaseThread* th = nullptr);
#endif

#endif
