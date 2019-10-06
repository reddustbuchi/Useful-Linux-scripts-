/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4D_SHADER_H
#define __C4D_SHADER_H

#include "ge_math.h"
#include "c4d_file.h"
#include "c4d_basetime.h"
#include "ge_prepass.h"	// important

#define TEX_TILE	 0x01	// texture tile enabled
#define TEX_MIRROR 0x02	// texture mirroring enabled
#define TEX_ALPHA	 0x04	// texture uses alpha channel (for use within channel shaders)
#define TEX_BUMP	 0x08	// bump calculation

#define GET_TEX_BUMP_SAMPLE(texflag) (((texflag) >> 4) & 3)
#define GET_TEX_CHANNEL(texflag)		 (((texflag) >> 6) & 15)

inline Int32 CALC_TEXINFO(Int32 texflag, Int32 channel) { return (texflag & ~0x3f0) | (channel << 6); }
inline Int32 CALC_TEXINFO_BUMP(Int32 texflag, Int32 channel, Int32 sample) { return (texflag & ~0x3f0) | ((sample & 3) << 4) | (channel << 6); }

class CDialog;
class HyperFile;
class BaseChannel;
class BaseDocument;
class BaseObject;
class BaseTag;
class BaseDraw;
class BaseDrawHelp;
class BaseThread;
class Filename;
class String;
class BaseView;
class BaseContainer;
class Raytracer;
class RootTextureString;
struct RayObj;
struct RayLight;
struct RayObject;
struct VolumeData;

// channels
#define MAX_MATERIALCHANNELS 14	// channels in C4D material

#define CHANNEL_ANY	-1					// unlabeled plugin channel

#define CHANNEL_COLOR					0
#define CHANNEL_LUMINANCE			1
#define CHANNEL_TRANSPARENCY	2
#define CHANNEL_REFLECTION		3
#define CHANNEL_ENVIRONMENT		4
#define CHANNEL_FOG						5
#define CHANNEL_BUMP					6
#define CHANNEL_ALPHA					7
#define CHANNEL_SPECULAR			8
#define CHANNEL_SPECULARCOLOR 9
#define CHANNEL_GLOW					10
#define CHANNEL_DISPLACEMENT	11
#define CHANNEL_DIFFUSION			12
#define CHANNEL_NORMAL				13

#define BASECHANNEL_COLOR_EX			 1000		// VECTOR
#define BASECHANNEL_BRIGHTNESS_EX	 1001		// REAL
#define BASECHANNEL_MIXMODE_EX		 1006		// Int32
#define BASECHANNEL_MIXSTRENGTH_EX 1007		// REAL

#define BASECHANNEL_TEXTURE					1002	// STRING
#define BASECHANNEL_BLUR_OFFSET			1003	// REAL
#define BASECHANNEL_BLUR_STRENGTH		1004	// REAL
#define BASECHANNEL_INTERPOLATION		1005	// Int32
#define BASECHANNEL_TIME_FROM				1008	// Int32
#define BASECHANNEL_TIME_TO					1009	// Int32
#define BASECHANNEL_TIME_FPS				1010	// Int32
#define BASECHANNEL_TIME_MODE				1011	// Int32
#define BASECHANNEL_TIME_TIMING			1012	// Int32
#define BASECHANNEL_TIME_START			1013	// BASETIME
#define BASECHANNEL_TIME_END				1014	// BASETIME
#define BASECHANNEL_TIME_LOOPS			1015	// Int32
#define BASECHANNEL_SHADERID				1016	// Int32
#define BASECHANNEL_SUGGESTEDFOLDER	1017	// FILENAME

enum INITRENDERFLAG
{
	INITRENDERFLAG_0						 = 0,
	INITRENDERFLAG_TEXTURES			 = (1 << 0),
	INITRENDERFLAG_PAINTERNOMIP	 = (1 << 1),
	INITRENDERFLAG_NOMIP				 = (1 << 2),
	INITRENDERFLAG_PREVIEWRENDER = (1 << 3),
	INITRENDERFLAG_IRR					 = (1 << 4)
} ENUM_END_FLAGS(INITRENDERFLAG);

Vector TransformColor(const Vector& input, COLORSPACETRANSFORMATION colortransformation);

struct InitRenderStruct
{
	InitRenderStruct()
	{
		version = 0;
		fps = 30;
		docpath = nullptr;
		errorlist = nullptr;
		matname = nullptr;
		vd	= nullptr;
		doc = nullptr;
		thread = nullptr;
		flags	 = INITRENDERFLAG_TEXTURES;
		linear_workflow = false;
		document_colorprofile = DOCUMENT_COLORPROFILE_SRGB;
	}

	explicit InitRenderStruct(BaseDocument* t_doc) { Init(t_doc); }

	void Init(BaseDocument* t_doc);

	Int32							 version;
	BaseTime					 time;
	Int32							 fps;
	Filename					 docpath;
	String*						 matname;
	RootTextureString* errorlist;
	VolumeData*				 vd;
	BaseDocument*			 doc;
	BaseThread*				 thread;
	INITRENDERFLAG		 flags;

	Bool							 linear_workflow;
	Int32							 document_colorprofile;

	Int32 GetThreadCount() const;

	Vector TransformColor(const Vector& input) const
	{
		if (document_colorprofile == DOCUMENT_COLORPROFILE_SRGB && linear_workflow)
			return ::TransformColor(input, COLORSPACETRANSFORMATION_SRGB_TO_LINEAR);
		else if (document_colorprofile == DOCUMENT_COLORPROFILE_LINEAR && !linear_workflow)
			return ::TransformColor(input, COLORSPACETRANSFORMATION_LINEAR_TO_SRGB);

		return input;
	}
};

// TexData::side
#define SIDE_FRONT_AND_BACK	0
#define SIDE_FRONT					1
#define SIDE_BACK						2

// texture information, read-only
struct TexData
{
private:
	TexData();
	~TexData();

public:
	Matrix			m, im;
	Char				texflag;
	Char				additive, proj, side;
	Int32	restrict;
	Float				ox, oy, lenx, leny, repetitionx, repetitiony;
	GeListNode* mp;
	Int32				uvwind;
	BaseView*		camera;
	Char				uvbump;
	BaseTag*		link;

	static TexData* Alloc();
	static void Free(TexData*& td);
	void Init(void);
};

// ray structure
struct Ray
{
	Ray() : p(DC), v(DC) { ior = 1.0; }

	// read and write
	Vector64 p, v;	// ray position and vector
	Float		 ior;		// current index of refraction
	Vector	 pp[3];	// 3 additional ray points for MIP-Mapping
	Vector	 vv[3];	// 3 additional ray vectors for MIP-Mapping

	// read-only
	Vector transport;	// current intensity (for special shadow calculation)
};

#define L_SPLIT_BIT	(1 << 31)

struct RayHitID
{
private:
	Int32 rayobject;
	Int32 polygon;

public:
	RayHitID() { rayobject = polygon = 0; }
	RayHitID(_DONTCONSTRUCT DC) { }
	RayHitID(const RayHitID& other) { rayobject = other.rayobject; polygon = other.polygon; }
	RayHitID(RayObject* t_rayobject, Int32 t_polygon, Bool second) { Set(t_rayobject, t_polygon, second); }

	inline Bool IsEqual(const RayHitID& snd) const { return rayobject == snd.rayobject && polygon == snd.polygon; }

	inline Bool Content() const { return rayobject != 0; }
	inline void Clear() { rayobject = polygon = 0; }

#ifdef __API_INTERN__
	void Set(RayObject* t_rayobject, Int32 t_polygon, Bool second);
	RayObj* GetObject(Raytracer* rt) const;
	inline Int32 GetPolygonPlus() const { return (rayobject & L_SPLIT_BIT) | polygon; }
#else
	inline void Set(RayObject* t_rayobject, Int32 t_polygon, Bool second)
	{
		rayobject = C4DOS.Sh->Obj_to_Num(nullptr, t_rayobject) + 1;
		polygon = t_polygon;
		if (second)
			rayobject |= L_SPLIT_BIT;
	}

	inline RayObject* GetObject(VolumeData* vd) const
	{
		return C4DOS.Sh->ID_to_Obj(vd, *this);
	}
#endif

	inline Int32 GetPolygon() const { return polygon; }
	inline Bool GetSecond() const { return (rayobject & L_SPLIT_BIT) != 0; }

	inline void ClearSecond() { rayobject &= ~L_SPLIT_BIT; }
	inline void SetSecond() { rayobject |= L_SPLIT_BIT; }

	inline void SetPrivateData(Int32 t_rayobject, Int32 t_polygon) { rayobject = t_rayobject; polygon = t_polygon; }
	inline void GetPrivateData(Int32* t_rayobject, Int32* t_polygon) const {* t_rayobject = rayobject; * t_polygon = polygon; }
};

// intersection structure
struct SurfaceIntersection
{
	SurfaceIntersection() { sid = 0; par_u = par_v = 0.0; }
	SurfaceIntersection(_DONTCONSTRUCT dc) : id(DC), p(DC), n(DC) { }

#ifdef __API_INTERN__
	RayObj*		 op;	// intersected object
#else
	RayObject* op;	// intersected object
#endif

	RayHitID id;						// ray hit ID
	Vector64 p, n;					// point and normal
	Int32		 sid;						// sub ID, only used for SPD
	Float		 par_u, par_v;	// barycentric coordinates, only used for SPD
};

class VPBitmap;

struct Multipass
{
	VPBitmap** bmp;
	Int32*		 ind;
	Float*		 result;
	Int32			 cnt, cmp;

	Vector**	 diffuse;
	Int32			 diffuse_cnt;

	Vector**	 specular;
	Int32			 specular_cnt;

	Vector**	 shadow;
	Int32			 shadow_cnt;

	RayLight** light;
	Int32			 light_cnt;

	Float**		 ochannel;
	Int32*		 ochannelid;
	Int32			 ochannel_cnt;

	Vector*		 vp_ambient, *vp_diffuse, *vp_specular, *vp_shadow, *vp_reflection, *vp_transparency;
	Vector*		 vp_radiosity, *vp_caustics, *vp_illumination;
	Vector*		 vp_mat_color, *vp_mat_luminance, *vp_mat_transparency, *vp_mat_reflection;
	Vector*		 vp_mat_environment, *vp_mat_specularcolor, *vp_atmosphere;
	Float*		 vp_depth, *vp_mat_specular, *vp_mat_diffusion, *vp_atmosphere_mul;
	Vector*		 vp_ambientocclusion, *vp_mat_uv, *vp_mat_normal, *vp_motionvector;
};

// main volume shader structure
struct BaseVolumeData
{
protected:
	BaseVolumeData(void);

public:
	// read-only
	Int32	 version;	// version number of structure
	Int32	 fps;			// frames per second
	Vector ambient;	// global ambient component
	Float	 time;		// current time in seconds

	// read and write
	// returnable data: color, transparency, reflection, alpha color, transparent and reflectant ray, point and normal
	Vector	 col;					// set the calculated color here
	Vector	 trans;				// set the calculated transparency here
	Vector	 refl;				// set the calculated reflection here
	Float		 alpha;				// set the calculated alpha here
	Ray*		 tray, *rray;	// read and write the transparency/reflection rays; NEVER change the pointers
	Vector64 p;						// surface point - may only be modified by Displace
	Vector64 bumpn;				// surface phong & bump normal

	// read-only
	Ray*			 ray;					// current eye ray
	Vector64	 orign;				// original surface normal
	Vector64	 n;						// surface phong normal
	Vector64	 dispn;				// suggested displacement direction
	Float64		 dist;				// distance from eye to surface point
	Float64		 cosc;				// angle beween ray vector and unbumped normal

	Vector		 uvw;					// surface uvw coordinates - INVALID for volumetric shaders
	Vector		 delta;				// MIP sample radius
	RayHitID	 lhit;				// surface identity
	TexData*	 tex;					// surface texture, NEVER change pointer
	Vector		 ddu, ddv;		// bump mapping basis vectors
	Int32			 raydepth;		// depth of actual ray

	Int32			 calc_trans;	// specifies, if transparency shall be rendered
	Int32			 calc_refl;		// specifies, if reflections shall be rendered
	Bool			 calc_shadow;	// specifies, if shadows shall be rendered
	Int32			 calc_illum;	// specifies, if illumination shall be rendered
	Int32			 calc_mip;		// specifies, if mip calculations shall be done

	Vector		 pp[3];				// MIP corner points in global space
	Vector		 nn[3];				// MIP normals of the three other corner points

	RAYBIT		 raybits;			// ray information
	RayLight*	 xlight;			// lightsource during shadow evaluation
	RayObject* op;					// object

	// read and write
	Int32			 recursion_id;		// plugin ID of data passed through recursion
	void*			 recursion_data;	// address of data passed through recursion
	Multipass* multipass;				// to be filled for multipasses

	// read only
	Vector back_p;			// set VOLUMEINFO_TRANSFORM   (CHANNELINFO_TRANSFORM) to access this value
	Vector back_delta;	// set VOLUMEINFO_TRANSFORM   (CHANNELINFO_TRANSFORM) to access this value; local space

	Float	 global_mip;	// global MIP scale

	Int32	 sid;					// subpolygon information: subpolygon and barycentric coordinates
	Float	 par_u, par_v;

	// read only
	SurfaceIntersection* intersection;	// intersection data (can be nullptr)

	// read only
	Float	mb_offset;	// motion blur time offset (between 0 and 1, only valid in Physical Render)

	// read and write
	Vector comp_color;			// diffuse component of the calculated color
	Vector comp_specular;		// specular component of the calculated color
	Vector comp_luminance;	// luminance component of the calculated color
};

// main channel shader structure
struct ChannelData
{
	ChannelData() { }
	ChannelData(BaseVolumeData* t_vd) : p(t_vd->uvw), n((Vector)t_vd->n), d(t_vd->delta) { t = t_vd->time; texflag = 0; vd = (VolumeData*)t_vd; off = 0.0; scale = t_vd->global_mip; }

	// read-only
	Vector			p;					// texture position in UVW coordinates
	Vector			n;					// surface normal
	Vector			d;					// MIP sample radius in UVW coordinates
	Float				t;					// current time in seconds
	Int32				texflag;		// texture flags
	VolumeData* vd;					// pointer to volume information, can be nullptr
	Float				off, scale;	// blur offset and scale
};

#define MSG_GETALLASSETS	 112004
#define MSG_SHADERV5TOV6	 112005
#define MSG_SHADERV6TOV7	 112006
#define MSG_SHADERREAD		 112009
#define MSG_RENAMETEXTURES 112010

struct RenameTextureMessage
{
	RenameTextureMessage() : doc(nullptr), changecnt(0), noundo(false) { }
	Filename			oldname;
	Filename			newname;
	BaseDocument* doc;
	Int32					changecnt;
	Bool					noundo;
};

struct VPFragment
{
	RayHitID		id;
	UChar				subx, suby;
	Int16				weight;
	RayObject*	op;

	Vector32		color;

	Float				z;
	Vector			p;
	Vector			n;

	VPFragment* next;
};

struct ShaderReadData
{
	HyperFile*		 hf;
	Int32					 oldid;
	Float*				 data;
	Int32					 oldlevel;
	BaseContainer* oldctr;
};

#endif
