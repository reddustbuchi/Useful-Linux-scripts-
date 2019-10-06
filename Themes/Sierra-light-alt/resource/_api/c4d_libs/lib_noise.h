/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _LIB_NOISE_H_
#define _LIB_NOISE_H_

// for the NOISE GUI
#define NOISE_OFFSET					2000

// Note : SLA must be installed to use this class
#define NOISE_LIB         1011190

#include "c4d_library.h"

#ifdef __API_INTERN__
#include "intbaselist.h"
#endif

enum NoiseType
{
	NOISE_UNKNOWN               =  0,
	// 2D & 3D
	NOISE_BOX_NOISE             =  1,
	NOISE_BLIST_TURB            =  2,
	NOISE_BUYA                  =  3,
	NOISE_CELL_NOISE            =  4,
	NOISE_CRANAL                =  5,
	NOISE_DENTS                 =  6,
	NOISE_DISPL_TURB            =  7,
	NOISE_FBM                   =  8,
	NOISE_HAMA                  =  9,
	NOISE_LUKA                  = 10,
	NOISE_MOD_NOISE             = 11,
	NOISE_NAKI                  = 12,
	NOISE_NOISE                 = 13,
	NOISE_NUTOUS                = 14,
	NOISE_OBER                  = 15,
	NOISE_PEZO                  = 16,
	NOISE_POXO                  = 17,
	NOISE_RANDOM                = 18,
	NOISE_SEMA                  = 19,
	NOISE_STUPL                 = 20,
	NOISE_TURBULENCE            = 21,
	NOISE_VL_NOISE              = 22,
	NOISE_WAVY_TURB             = 23,
	NOISE_CELL_VORONOI          = 24,
	NOISE_DISPL_VORONOI         = 25,
	NOISE_SPARSE_CONV           = 26,
	NOISE_VORONOI_1             = 27,
	NOISE_VORONOI_2             = 28,
	NOISE_VORONOI_3             = 29,
	NOISE_ZADA                  = 30,
	NOISE_FIRE                  = 31,
	NOISE_ELECTRIC              = 32,
	NOISE_GASEOUS               = 33,

	NOISE_NONE                  = 99
};

class BaseContainer;
struct NoiseGradient;

class C4DNoise
{
private:
	C4DNoise();
	~C4DNoise();
public:
	static C4DNoise* Alloc(Int32 seed);
	static C4DNoise* Alloc2(Int32 seed);
	static void Free(C4DNoise *&p);

	static BaseContainer CreateMenuContainer(Bool bIncludeNone = false);
	static Bool HasOctaves(NoiseType t);
	static Bool HasAbsolute(NoiseType t);
	static Bool HasCycles(NoiseType t);
	static void EvaluateSampleOffset(NoiseType type, Float rOctaves, Float rDelta, Float &rSampleOffset);
	static void GetNoisePreview(NoiseType t, IconData &dat, String *str = nullptr);

	Float Noise(NoiseType t, Bool two_d, const Vector &p, Float time = 0.0, Float octaves = 4.0, Bool absolute = false, Float sampleRad = 0.25, Float detailAtt = 0.25, Int32 t_repeat=0);
	Bool InitFbm(Int32 lMaxOctaves, Float rLacunarity, Float h);

	const Float* GetFBMTable();
	const Float* GetValueTable();
	const Float* GetImpulseTable();
	static const UChar* GetPermutationTable();
	const Int32* GetTPPermutationTable();
	const NoiseGradient* GetNoiseGradient();
	const Int32* GetPermutationTableA();

	Float SNoise(Vector p);
	Float SNoise(Vector p, Float t, Int32 lRepeat);
	Float Turbulence(Vector p, Float t, Float rOctaves, Bool bAbsolute, Int32 lRepeat);
	Float Fbm(Vector p, Float t, Float rOctaves, Int32 lRepeat);
	Float RidgedMultifractal(Vector p, Float t, Float rOctaves, Float rOffset, Float rGain, Int32 lRepeat);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

class iNoise;

struct NoiseLib : public C4DLibrary
{
	iNoise*       (*NoiseLib_Alloc)(Int32 seed);
	void          (*NoiseLib_Free)(iNoise *&p);

	Float          (iNoise::*NoiseLib_Noise2D)(const NoiseType t, const Vector &p, const Float time, const Float octaves, const Bool absolute, const Float sampleRad, const Float detailAtt);
	Float          (iNoise::*NoiseLib_Noise3D)(const NoiseType t, const Vector &p, const Float time, const Float octaves, const Bool absolute, const Float sampleRad, const Float detailAtt);
	Bool          (iNoise::*NoiseLib_InitFbm)(Int32 lMaxOctaves, Float rLacunarity, Float h);
	BaseContainer (*NoiseLib_CreateMenuContainer)(Bool bIncludeNone);
	Bool          (*NoiseLib_HasOctaves)(NoiseType t);
	void          (*NoiseLib_EvaluateSampleOffset)(NoiseType type, Float rOctaves, Float rDelta, Float &rSampleOffset);
	void          (*NoiseLib_GetNoisePreview)(NoiseType t, IconData &dat, String *str);
	Float          (iNoise::*NoiseLib_Noise)(NoiseType t, Bool two_d, const Vector &p, Float time, Float octaves, Bool absolute, Float sampleRad, Float detailAtt, Int32 t_repeat);
	const Float*   (iNoise::*NoiseLib_GetFBMTable)();
	const Float*   (iNoise::*NoiseLib_GetValueTable)();
	const Float*   (iNoise::*NoiseLib_GetImpulseTable)();
	const UChar*  (*NoiseLib_GetPermutationTable)();
	Bool          (*NoiseLib_HasAbsolute)(NoiseType t);
	Bool          (*NoiseLib_HasCycles)(NoiseType t);
	Float					(iNoise::*SNoiseR)(Vector p, Float t, Int32 lRepeat);
	Float					(iNoise::*SNoise)(Vector p);
	Float					(iNoise::*Turbulence)(Vector p, Float t, Float rOctaves, Bool bAbsolute, Int32 lRepeat);
	Float					(iNoise::*Fbm)(Vector p, Float t, Float rOctaves, Int32 lRepeat);
	Float					(iNoise::*RidgedMultifractal)(Vector p, Float t, Float rOctaves, Float rOffset, Float rGain, Int32 lRepeat);

	iNoise*       (*NoiseLib_Alloc2)(Int32 seed);
	const NoiseGradient* (iNoise::*NoiseLib_GetNoiseGradient)();
	const Int32*		(iNoise::*NoiseLib_GetPermutationTableA)();
};


// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF



#endif // _LIB_NOISE_H_
