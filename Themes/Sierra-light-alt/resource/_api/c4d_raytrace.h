/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4D_RAYTRACE_H
#define __C4D_RAYTRACE_H

#include "ge_math.h"
#include "c4d_shader.h"

// texture projection types
#define P_SPHERICAL		 0
#define P_CYLINDRICAL	 1
#define P_FLAT				 2
#define P_CUBIC				 3
#define P_FRONTAL			 4
#define P_SPATIAL			 5
#define P_UVW					 6
#define P_SHRINKWRAP	 7
#define P_CAMERAMAP		 8
#define P_VOLUMESHADER 10

// object types
#define O_FLOOR		0
#define O_SKY			1
#define O_SPHERE	2
#define O_POLYGON	3

// field rendering
#define FIELD_NONE 0
#define FIELD_EVEN 1
#define FIELD_ODD	 2

// depth of field
#define DOF_NONE	0
#define DOF_BOTH	1
#define DOF_FRONT	2
#define DOF_BACK	3

// anti-aliasing
#define ANTI_NONE			0
#define ANTI_GEOMETRY	1
#define ANTI_BEST			2

// camera types
#define CAMERA_PERSPECTIVE 0
#define CAMERA_PARALLEL		 1
#define CAMERA_AXONOMETRIC 2
#define CAMERA_VRPANORAMA	 3
#define CAMERA_CUSTOMLENS	 4

// light types
#define RT_LT_OMNI				0
#define RT_LT_SPOT				1
#define RT_LT_SPOTRECT		2
#define RT_LT_DISTANT			3
#define RT_LT_PARALLEL		4
#define RT_LT_PARSPOT			5
#define RT_LT_PARSPOTRECT	6
#define RT_LT_AREA				8
#define RT_LT_PHOTOMETRIC	9
#define RT_LT_AMBIENT			50	// only for OpenGL fragment programs
#define RT_LT_DEFAULT			51	// only for OpenGL fragment programs

// shadow types
#define RT_SHADOW_NONE 0
#define RT_SHADOW_SOFT 1
#define RT_SHADOW_HARD 2
#define RT_SHADOW_AREA 3

// light visibility
#define	RT_VL_NONE					0
#define RT_VL_VISIBLE				1
#define RT_VL_VOLUMETRIC		2
#define RT_VL_INVVOLUMETRIC	3

// light falloff
#define RT_FALLOFF_NONE						 0
#define RT_FALLOFF_INVERSE_CLAMPED 6
#define RT_FALLOFF_SQUARE_CLAMPED	 7
#define RT_FALLOFF_LINEAR					 8
#define RT_FALLOFF_INVERSE				 9
#define RT_FALLOFF_SQUARE					 10
#define RT_FALLOFF_STEP						 5

// light noise
#define RT_VN_NONE	0
#define RT_VN_ILLUM	1
#define RT_VN_VISIB	2
#define RT_VN_BOTH	3

// light noise type
#define RT_VN_NOISE					 0
#define RT_VN_SOFTTURBULENCE 1
#define RT_VN_HARDTURBULENCE 2
#define RT_VN_WAVYTURBULENCE 3

// GetRayData
#define RAY_PARAMETER		0
#define RAY_ENVIRONMENT	1
#define RAY_CAMERA			2
#define RAY_SKY					3
#define RAY_FOREGROUND	4
#define RAY_BACKGROUND	5

// pixel fragment oversampling
#define OVERSAMPLING 16

// raypolystate bits
#define RAYPOLYSTATE_TRIANGLE		1
#define RAYPOLYSTATE_QUADRANGLE	2
#define RAYPOLYSTATE_SPLIT			4

struct RayPolygon
{
	Int32 a, b, c, d;
};

class BaseObject;
struct TexList;
struct RayFragment;
struct PixelFragment;
class Gradient;

#define LIGHTRESTRICTION_NODIFFUSE	(1 << 0)
#define LIGHTRESTRICTION_NOSPECULAR	(1 << 1)
#define LIGHTRESTRICTION_NOSHADOW		(1 << 2)

#define OBJECTRESTRICTION_TRANSPARENCY (1 << 0)
#define OBJECTRESTRICTION_REFRACTION	 (1 << 1)
#define OBJECTRESTRICTION_REFLECTION	 (1 << 2)
#define OBJECTRESTRICTION_AO					 (1 << 4)

#define OBJECTRESTRICTION_TRANSPARENCY_INUSE (1 << 3)

struct ObjectRestriction
{
	UChar* object;
	Int32	 object_cnt;
};

struct RayObjectInstanceData
{
	Int32				instance_of_index;	// index to rayobject
	Matrix64		transform, transform_inverse;
	Matrix64		transform_tensor;
	BaseObject* link;	// link to the virtual instance parent
};

struct RayObject
{
protected:
	RayObject(void);

public:
	Char	 type;								// object type

	Char	 flag_phong;					// phong flag
	Char	 flag_castshadow;			// cast shadow flag
	Char	 flag_receiveshadow;	// receive shadow flag
	Char	 flag_seenbycamera;		// seen by camera flag
	Char	 flag_compositing;		// compositing flag - catches shadows
	Char	 flag_selfshadow;			// self shadowing flag
	Char	 flag_seenbygi;				// seen by GI flag
	Char	 flag_matteobject;		// object is matte object
	Char	 flag_seenbydetails;	// detail flags, OBJECTRESTRICTION_xxx
	Char	 flag_instanced;

	Vector v2;
	Vector mp;					// center of bounding box
	Vector rad;					// radius of bounding box

	Float	 visibility;	// object visibility
	Float	 phong_angle;	// phong angle

	// points
	Vector* padr;	// point address
	Int32		pcnt;	// point count

	// polygons
	const RayPolygon* vadr;	// polygon address
	Int32							vcnt;	// polygon count

	// textures
	TexList* texadr;	// texture address
	Int32		 texcnt;	// texture count

	// uvw
	const void** uvwadr;	// uvw field
	Int32				 uvwcnt;	// uvw entries

	// polygon restriction
	UInt32**							 rsadr;					// restriction field
	Int32									 rscnt;					// restriction entries

	BaseObject*						 link;					// link to real C4D object

	Matrix64							 mg;						// object matrix
	Matrix64							 mg_inverse;		// inverse object matrix

	Matrix								 motion_delta;	// transformation matrix: oldmg * !newmg
	Float									 oblurlen;			// object blur strength

	Char									 aa_minlevel;		// min/max antialiasing level
	Char									 aa_maxlevel;
	Float									 aa_threshold;

	Int16									 channelid[12];			// object channel ID

	BaseObject*						 texture_link;			// link to real C4D object that inherited texture tag
	Vector								 default_color;			// object default color

	Int32									 restriction_index;	// index to light/object restriction table

	UChar*								 edges;							// bits 0..3: hiding, bits 4..7: phong
	Int16*								 psum;							// phong normals - access depends on mode

	Int32									 spd_displacement;	// displacement subdivision
	Float									 spd_height;				// maximum displacement height
	Char									 spd_keepedges;			// subpixel keep edge setting
	Char									 spd_distribution;	// subpixel distribution setting
	Char									 spd_round;					// subpixel round setting
	Char									 spd_roundcontour;	// subpixel round contour setting
	Char									 spd_hqremapping;		// subpixel high quality remapping setting
	Char									 spd_mapresult;			// subpixel map geometry setting

	void*									 userdata;					// only to be used by plugin renderer

	ObjectRestriction			 rr;								// compositing tag restriction

	RayObjectInstanceData* instance;					// instance data

	Int16**								 tex_tsum;					// tangent vectors for each uv channel - access depends on mode, can be nullptr
	Char									 flag_compositing_gi;
};

struct PolyVector
{
	Vector a, b, c, d;
};

struct RayPolyWeight
{
	Float wa, wb, wc, wd;
};

struct RayLightNoise
{
protected:
	RayLightNoise(void);

public:
	Int32	 type;					// noise algorithm
	Float	 octaves;				// noise octaves
	Float	 velocity;			// noise speed
	Float	 brightness;		// noise brightness
	Float	 contrast;			// noise contrast
	Bool	 local;					// local noise
	Vector scale;					// noise scale
	Float	 iscale;				// illumination scale
	Vector wind;					// wind effect
	Float	 windvelocity;	// wind velocity
};

struct RayLightCaustics
{
protected:
	RayLightCaustics(void);

public:
	Bool	cs_enable;		// enable surface caustics
	Float	cs_energy;		// caustic energy
	Int32	cs_photons;		// number of photons

	Bool	vcs_enable;		// enable volume caustics
	Float	vcs_energy;		// volume caustic energy
	Int32	vcs_photons;	// number of volume photons

	Int32	falloff;			// caustic light falloff
	Float	innerradius;	// inner radius
	Float	outerradius;	// outer radius
};

struct RayLightShadow
{
protected:
	RayLightShadow(void);

public:
	Float	 density;							// shadow density
	Vector color;								// shadow color
	Bool	 transparency;				// shadow supports transparency
	Bool	 clippinginfluence;		// evaluate clipping areas

	Int32	 mapsizex, mapsizey;	// soft shadow map resolution
	Float	 bias;								// soft shadow bias
	Bool	 absolute;						// absolute bias
	Int32	 sampleradius;				// soft shadow sample radius
	Float	 parallelwidth;				// soft shadow parallel width
	Bool	 outline;							// outline soft shadow

	Bool	 shadowcone;					// soft shadow cone
	Float	 coneangle;						// soft shadow cone angle
	Bool	 softcone;						// soft falloff at edges

	Float	 accuracy;						// area shadow accuracy
	Int32	 minsamples;					// area shadow min samples
	Int32	 maxsamples;					// area shadow max samples
};

struct RayLightVisible
{
protected:
	RayLightVisible(void);

public:
	Bool			falloff;								// falloff
	Float			strength;								// falloff strength
	Bool			edgefalloff;						// edge falloff
	Float			edgestrength;						// edge falloff strength
	Bool			colfalloff;							// colored edge falloff
	Float			innerdistance;					// inner distance
	Vector		outerdistance;					// outer distance
	Float			sampledistance;					// sample distance
	Float			brightness_multiplier;	// brightness
	Float			dust;										// dust effect
	Float			dithering;							// dithering
	Bool			adaptbrightness;				// adapt brightness (angle based brightness scale)
	Bool			additive;								// additive visible light
	Vector		color;

	Gradient* gradient;
};

struct RayLight
{
protected:
	RayLight(void);

public:
	RayLightNoise*		ln;								// pointer to noise structure
	RayLightShadow*		ls;								// pointer to shadow structure
	RayLightVisible*	lv;								// pointer to visible light structure
	BaseObject*				link;							// link to real C4D object

	Bool							calc_illum;				// light source illuminates
	Matrix64					m;								// light matrix
	Matrix64					m_inverse;				// inverse matrix

	Int32							type;							// type of light
	Int32							stype;						// shadow type
	Int32							vtype;						// type of visible light
	Int32							ntype;						// type of noise
	Int32							falloff;					// type of light falloff
	Float							innerangle;				// inner angle of light cone
	Float							outerangle;				// outer angle of light cone
	Float							innerradius;			// inner radius of light
	Float							outerradius;			// outer radius of light
	Float							aspectratio;			// Y distortion
	Bool							arealight;				// acts as area light
	Bool							ambient;					// ambient flag
	Bool							nodiffuse;				// affects no diffuse
	Bool							nospecular;				// affects no specular
	Bool							nogi;							// affects no gi
	Bool							innercolor;				// inner color different
	Bool							colfalloff;				// edge color falloff
	Bool							negative;					// negative light source
	Float							contrast;					// light contrast
	Float							innerdist;				// inner distance
	Float							outerdist;				// outer distance
	Vector						color;						// light color
	Bool							nearclip;					// near clipping
	Bool							farclip;					// far clipping
	Float							nearfrom;					// near clipping start
	Float							nearto;						// near clipping end
	Float							farfrom;					// far clipping start
	Float							farto;						// far clipping end
	Vector						lens_color;				// color for lensflares

	RayLightCaustics* lc;								// pointer to caustics structure
	Bool							separatepass;			// render as separate multipass
	Float							trn;							// Exp(-contrast)
	Int32							multipass_index;	// index into multipass light field (or NOTOK)

	ObjectRestriction	lr;								// light restriction

	void*							userdata;					// only to be used by plugin renderer

	Bool							onlyz;

	Vector						arearadius;
	Int32							areashape;
	Int32							areasamples;
	Bool							areaaddgrain;
	Bool							areanoiselock_ex;	// no longer used, the RayParameter::lock_noise is used instead

	const Vector*			area_padr;
	Int32							area_pcnt;
	const RayPolygon*	area_vadr;
	Int32							area_vcnt;
	BaseObject*				area_link;
	Matrix*						area_matrix;
	Bool							shadowcaster;
	Float							area_falloffangle;
	Float							area_infiniteangle;
	Bool							area_showinrender;
	Bool							area_showinreflection;

	Gradient*					gradient;
	Float							gradient_multiplier;
	Float							lens_imul;

	TexList*					texadr;
	Int32							texcnt;
};

struct RayParameter
{
protected:
	RayParameter(void);

public:
	Int32										 xres, yres;								// image resolution
	Int32										 left, top, right, bottom;	// marquee render
	Float										 pixelaspect;								// aspect ratio of pixels

	Int32										 antialiasing;							// antialiasing level
	Int32										 oversample;								// antialiasing oversampling (1 or 16)
	Float										 unused1;										// antialiasing softness

	Int32										 reflection;								// reflection level (0: none, 1: floor and sky, 2: full)
	Int32										 transparency;							// transparency level (0: none, 1: no refraction, 2: full)
	Bool										 shadow;
	Bool										 onlysoftshadow;

	Int32										 raydepth;				// maximum ray depth
	Int32										 reflectiondepth;	// maximum reflection depth
	Int32										 shadowdepth;			// maximum ray depth for shadow calculations
	Float										 threshold;				// minimum intensity of a ray

	Bool										 gi_reflectivecaustics;
	Bool										 gi_refractivecaustics;
	Int32										 field;																				// field rendering
	Bool										 volumetriclighting;													// volumetric effects
	Bool										 straightalpha;																// straight alpha
	Bool										 textures;																		// textures
	Bool										 textureerror;																// stop if texture error
	Bool										 enable_blurry;
	Bool										 dithering;																		// true color dithering

	Bool										 gi_enablediffuse, gi_prepass;								// radiosity options
	Bool										 cs_enablecaustics, cs_enablevolumecaustics;	// caustics options

	Int32										 aa_filter;																		// antialiasing filter
	Float										 aa_threshold;																// antialiasing threshold
	Int32										 aa_minlevel;																	// antialiasing minimum level
	Int32										 aa_maxlevel;																	// antialiasing maximum level
	Bool										 aa_useobject;																// enable local antialiasing
	Float										 aa_globalmip;																// global MIP scale

	RENDERFLAGS							 renderflags;																	// renderflags passed to RenderDocument

	Bool										 showhud;																			// show head up display
	Bool										 cacheshadowmaps;															// enable shadow map caching
	Bool										 enablespd;
	Float										 global_brightness;
	Bool										 apply_ambientocclusion;
	Bool										 aa_considermultipasses;

	Bool										 linear_workflow;
	COLORSPACETRANSFORMATION colorspacetransformation;

	Float										 unitscale;												// 1.0 unit equals 'unitscale' meters in real life

	Float										 aa_filtersizex, aa_filtersizey;	// AA filter settings
	Bool										 aa_customfiltersize, aa_clipnegative;

	Bool										 gi_ambientocclusion;	// GI computes AO

	Bool										 gi_radiance_enabled;	// GI computes Radiance Maps
	Int32										 gi_radiance_mode;
	Int32										 gi_radiance_samples;
	Float										 gi_radiance_density;

	Bool										 lock_noise;	// Identical Noise Distribution
	Bool										 enable_sss;

	Float										 gi_radiance_intensity;
	Float										 gi_radiance_saturation;

	Bool										 gi_lightmapping_enabled;	// GI computes Light Mapping
	Bool										 gi_lightmapping_direct;
	Bool										 gi_lightmapping_prepass;
	Int32										 gi_lightmapping_mode;

	Bool										 net_caches_sss;	// NET Cache options
	Bool										 net_caches_ao;
	Bool										 net_caches_gi;
	Bool										 net_caches_rm;
	Bool										 net_caches_lm;
};

struct RayEnvironment
{
protected:
	RayEnvironment(void);

public:
	Vector ambient;			// ambient environment color
	Bool	 fogenable;		// environment fog flag
	Vector fog;					// environment fog color
	Float	 fogdistance;	// environment fog distance
	Bool	 fogaffectbg;
};

struct RayCamera
{
protected:
	RayCamera(void);

public:
	Matrix64		m;	// camera matrix
	Matrix64		m_inverse;

	Float64			zoom;	// zoom factor (focal length divided by aperture width for parallel projections)

	Int32				type;	// camera type (e.g. CAMERA_PERSPECTIVE)
	Bool				infinite_ex;

	Int32				depthoffield;									// type of depth of field (e.g. DOF_NONE)
	Float				front_end, middle, rear_end;	// depth of field sharpness ranges

	Float				qtvr_hstart;									// horizontal start angle for QuickTime VR panorama
	Float				qtvr_hend;										// horizontal end	angle for QuickTime VR panorama
	Float				qtvr_vfov;										// vertical field of view for QuickTime VR panorama

	BaseObject* link;													// link to real C4D camera

	Vector64		off, scale;										// camera offset and scale

	Float				front_start, rear_start, front_dlt, rear_dlt;
	Int32				xdlt, ydlt;			// x/y offset for internal render

	Matrix			motion_delta;		// transformation matrix: oldmg * !newmg
	Float64			near_clipping;	// Z clipping depth if near_clipping_enabled

	Vector64		kscale;					// camera image scale
	Vector64		kscale_z;				// camera image Z scale (for axonometric projections)

	Float64			far_clipping;
	Bool				near_clipping_enabled, far_clipping_enabled;

	Float				fDOFAperture;	// real DOF
};

struct SurfaceData
{
	Vector	 col, refl, trans;
	Float		 alpha;
	Ray			 rray, tray;
	Vector64 bumpn;
	Float		 cs_generate_strength, cs_receive_strength;
	Vector	 comp_color;
	Vector	 comp_specular;
	Vector	 comp_luminance;
};

struct SurfaceDataEx
{
	Vector	 col, refl, trans;
	Float		 alpha;
	Ray			 rray, tray;
	Vector64 bumpn;
	Float		 cs_generate_strength, cs_receive_strength;
};

struct RayLightComponent
{
	RayLight* light;	// read-only
	Vector64	lv;			// read-only
	Vector		col;		// read-only
	Vector		rdiffuse, rspecular;
};

struct RayLightCache
{
	RayLightComponent** comp;									// read-only
	Int32								cnt;									// read-only
	Vector							radiosity, caustics;	// read-only
	Vector							diffuse, specular;		// read and write
	Vector							ao;										// read-only
};

struct RaySampler
{
	void*	 guid;	// read-only
	UInt32 depth;	// read-only
	UInt32 index;	// read and write
};

struct RayHemiSample
{
	Vector dir;					// read-only (in normal vector frame space)
	Vector col;					// write
	Float	 dist_sum;		// write
	Float	 dist_weight;	// write
	Float	 cos_theta;		// read-only
	Float	 sin_theta;		// real-only
};

struct RayHemisphere
{
	RayHemiSample* samples;					// read-only
	UInt32				 size_m;					// read-only
	UInt32				 size_n;					// read-only

	UInt32				 depth;						// read-only
	UInt32				 count_hs;				// read-only
	UInt32				 count_area;			// read-only
	UInt32				 count_sky;				// read-only
	Bool					 sample_hs;				// read-only
	Bool					 sample_area;			// read-only
	Bool					 sample_sky;			// read-only
	Bool					 no_hs;						// read-only
	Bool					 no_area;					// read-only
	Bool					 no_sky;					// read-only
	Bool					 gradients;				// read-only
	Bool					 per_pixel;				// read-only
	Bool					 radiance_area;		// read-only
	Bool					 radiance_sky;		// read-only

	Bool					 ao_only;					// read-only
	Float					 ao_dist_min;			// read-only
	Float					 ao_dist_max;			// read-only
	Bool					 ao_trans;				// read-only
	Bool					 ao_self;					// read-only

	Vector				 color;						// write (when gradients are not used)
	Bool					 cache_mode;			// read-only
	Float					 cache_dist;			// write
	Float					 cache_r;					// write
	Float					 cache_r_real;		// write

	Bool					 details;					// read-only
	Bool					 details_found;		// write
	Float					 details_radius;	// read-only
	Float					 details_ratios;	// write
	Float					 details_sum;			// write
};

struct RayRadiancePoly
{
	Vector32*	map_front;
	Vector32*	map_back;
	Int32			size_u;
	Int32			size_v;
};

struct RayRadianceObject
{
	RayRadiancePoly* polys;
	Int32						 count;
};

struct PixelFragment
{
#ifdef __API_INTERN__
	RayFragment*	 next, *cluster;
#else
	PixelFragment* next, *cluster;
#endif

	RayHitID id;

	union
	{
		UInt16 mask [OVERSAMPLING];
		UInt32 lmask[OVERSAMPLING / 2];
	};

	Float32	 z, u, v;
	Vector32 col;
	Vector	 n;

	Int32		 subid;	// for polygon objects: subpixel displacement ID
									// for sphere objects: boolean value (true for back side)
};

struct IlluminanceSurfacePointData;

typedef void IlluminanceSurfacePointModel (VolumeData * sd, RayLightCache * rlc, IlluminanceSurfacePointData * dat);
typedef void IlluminationModel (VolumeData * sd, RayLightCache * rlc, void* dat);

struct IlluminanceSurfacePointData
{
	Vector64											p, bumpn, phongn, orign, ray_vector;
	Float													specular_exponent;
	Bool													receive_gi, receive_caustics, cosine_cutoff, calc_shadow;
	RAYBIT												raybits;
	RayHitID											lhit;

	void*													local_mat;

	IlluminanceSurfacePointModel*	model;
	void*													customdata;
};


#endif
