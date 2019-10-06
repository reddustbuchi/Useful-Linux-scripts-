/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DVIDEOPOSTDATA_H
#define __C4DVIDEOPOSTDATA_H

#include "ge_math.h"
#include "c4d_nodedata.h"
#include "operatingsystem.h"

class BaseVideoPost;
class BaseContainer;
class BaseDocument;
class BaseObject;
class BaseDraw;
class BaseDrawHelp;
class BaseDocument;
class BaseBitmap;
class String;
class CDialog;
class Render;
class RenderJob;
class GlFrameBuffer;
class NetRenderData;
struct Multipass;
struct PixelPost;
struct VideoPostStruct;
struct VolumeData;
struct RayFragment;
struct Ray;
struct NetRenderBuffer;
struct NetRenderDocumentContext;

enum VIDEOPOSTCALL
{
	VIDEOPOSTCALL_FRAMESEQUENCE	= 1,	// called when the renderer prepares to render a sequence of images
	VIDEOPOSTCALL_FRAME					= 2,	// called when the renderer prepares to render a frame
	VIDEOPOSTCALL_SUBFRAME			= 3,	// called when the renderer prepares to render a subframe
	VIDEOPOSTCALL_RENDER				= 4,	// called before the rendering process starts and before shaders are initialized
	VIDEOPOSTCALL_INNER					= 5		// called immediately before rendering starts
} ENUM_END_LIST(VIDEOPOSTCALL);

struct BaseVideoPostStruct
{
	// C4D version number
	Int32	version;

	// VP_xxx type
	VIDEOPOSTCALL vp;

	// true if it is an opener, false if it is a closer
	Bool open;

	// current time
	BaseTime time;

	// render frame rate (this may be different to doc->GetFps())
	Int32	fps;

	// pointer to RenderResult containing RAY_xxx states
	RENDERRESULT* error;

	// pointer to VolumeData; may be nullptr
	VolumeData* vd;

	// document
	BaseDocument* doc;

	// thread; use thread->TestBreak() to check for a user break
	BaseThread* thread;

	// current subframe and number of subframes
	Int32	subframe, subframe_cnt;

	// current field and number of fields
	Int32	field, field_cnt;

	// render instance
	Render* render;

	// renderflags passed to RenderDocument
	RENDERFLAGS renderflags;

	// color management information
	Bool										 linear_workflow;
	COLORSPACETRANSFORMATION colorspacetransformation;

	// net render document context
	NetRenderDocumentContext* net;
	Bool											net_server;
};

// common buffers
#define VPBUFFER_RGBA						1
#define VPBUFFER_AMBIENT				2
#define VPBUFFER_DIFFUSE				3
#define VPBUFFER_SPECULAR				4
#define VPBUFFER_SHADOW					5
#define VPBUFFER_REFLECTION			6
#define VPBUFFER_TRANSPARENCY		7
#define VPBUFFER_RADIOSITY			8
#define VPBUFFER_CAUSTICS				9
#define VPBUFFER_ATMOSPHERE			10
#define VPBUFFER_ATMOSPHERE_MUL	11
#define VPBUFFER_ALLPOSTEFFECTS	12

#define VPBUFFER_IMAGEBUILDING_PASS	32

// special buffers
#define VPBUFFER_DEPTH						 100
#define VPBUFFER_MAT_COLOR				 101
#define VPBUFFER_MAT_DIFFUSION		 102
#define VPBUFFER_MAT_LUMINANCE		 103
#define VPBUFFER_MAT_TRANSPARENCY	 104
#define VPBUFFER_MAT_REFLECTION		 105
#define VPBUFFER_MAT_ENVIRONMENT	 106
#define VPBUFFER_MAT_SPECULAR			 107
#define VPBUFFER_MAT_SPECULARCOLOR 108
#define VPBUFFER_ILLUMINATION			 109
#define VPBUFFER_OBJECTBUFFER			 110

#define VPBUFFER_POSTEFFECT				111
#define VPBUFFER_POSTEFFECT_MUL		112
#define VPBUFFER_AMBIENTOCCLUSION	113
#define VPBUFFER_MAT_NORMAL				114
#define VPBUFFER_MAT_UV						115
#define VPBUFFER_MOTIONVECTOR			116
#define VPBUFFER_SAMPLER					117

#define VPBUFFER_BLEND			1000
#define VPBUFFER_LIGHTBLEND	1001	// private ID
#define VPBUFFER_ALPHA			1002	// for sdk request only
#define VPBUFFER_BLENDCH		1003	// private ID

struct PixelPost
{
#ifdef __API_INTERN__
	RayFragment**		frag;
	RayFragment**		frag_nx;
#else
	PixelFragment** frag;
	PixelFragment** frag_nx;
#endif
	VolumeData*			vd;
	Float32*				col;
	Multipass*			mp;
	Bool						aa, valid_line;
	Int32						comp;
	Int32						cpu_num;
	Int32						xmin, xmax, line;
};

#define VPlenseffects							1001049
#define VPobjectglow							1001007
#define VPcolorcorrection					1001008
#define VPcomic										1001009
#define VPscenemotionblur					1001010
#define VPsoftfilter							1001012
#define VPsharpenfilter						1001013
#define VPmedianfilter						1001014
#define VPremote									1001015
#define VPopticsuite_depthoffield 1001400
#define VPopticsuite_glow					1001401
#define VPopticsuite_highlights		1001402
#define VPambientocclusion				300001045
#define VPxmbsampler							1023342

#define VPPRIORITY_OBJECTGLOW				500
#define VPPRIORITY_OBJECTMOTIONBLUR 400
#define VPPRIORITY_DEPTHOFFIELD			300
#define VPPRIORITY_LENSEFFECTS			200
#define VPPRIORITY_FILTERSOFT				100
#define VPPRIORITY_FILTERSHARPEN		100
#define VPPRIORITY_FILTERMEDIAN			100

#define VPPRIORITY_COMIC					 600
#define VPPRIORITY_COLORCORRECTION 500
#define VPPRIORITY_SCENEMOTIONBLUR 100
#define VPPRIORITY_EXTERNAL				 100

// info flags
#define PLUGINFLAG_VIDEOPOST_MULTIPLE					(1 << 0)																																					// allow multiple effects of this type
#define PLUGINFLAG_VIDEOPOST_INHERENT					(1 << 1)																																					// VP always is present
#define PLUGINFLAG_VIDEOPOST_GL								(1 << 2)																																					// post effect supports OpenGL drawing
#define PLUGINFLAG_VIDEOPOST_ISRENDERER				(1 << 3)
#define PLUGINFLAG_VIDEOPOST_STEREO_EDITOR		(1 << 4)																																					// stereo display in editor (PLUGINFLAG_VIDEOPOST_GL is required)
#define PLUGINFLAG_VIDEOPOST_STEREO_RENDERING	(1 << 5)																																					// stereo display in rendering
#define PLUGINFLAG_VIDEOPOST_STEREO						((PLUGINFLAG_VIDEOPOST_STEREO_EDITOR) | (PLUGINFLAG_VIDEOPOST_STEREO_RENDERING))	// stereo display in rendering
#define PLUGINFLAG_VIDEOPOST_ISRENDERER_NET		(1 << 6)																																					// post effect supports Team Render/NET (PLUGINFLAG_VIDEOPOST_ISRENDERER is required)

enum VIDEOPOST_GLINFO
{
	VIDEOPOST_GLINFO_0															= 0x00000000,
	VIDEOPOST_GLINFO_CUSTOM_MOUSE										= 0x00000001,
	VIDEOPOST_GLINFO_ALLOC_UVW_BUFFER								= 0x00000002,
	VIDEOPOST_GLINFO_ALLOC_UVW_BUFFER_FLOAT32				= 0x00100002,
	VIDEOPOST_GLINFO_ALLOC_DU_BUFFER								= 0x00000004,
	VIDEOPOST_GLINFO_ALLOC_DV_BUFFER								= 0x00000008,
	VIDEOPOST_GLINFO_ALLOC_NORMAL_BUFFER						= 0x00000010,
	VIDEOPOST_GLINFO_ALLOC_MATERIAL_ID							= 0x00000020,	// requires the GL_EXT_texture_integer extension, this must be an integer texture
	VIDEOPOST_GLINFO_ALLOC_NORMAL_BUFFER_FLOAT16		= 0x00100010,	// implies VIDEOPOST_GLINFO_ALLOC_NORMAL_BUFFER
	VIDEOPOST_GLINFO_ALLOC_NORMAL_BUFFER_FLOAT32		= 0x00200010,	// implies VIDEOPOST_GLINFO_ALLOC_NORMAL_BUFFER
	VIDEOPOST_GLINFO_ALLOC_WORLCOORD_BUFFER					= 0x00000040,
	VIDEOPOST_GLINFO_ALLOC_OBJECTID_BUFFER					= 0x00000080,	// requires the GL_EXT_texture_integer extension, this must be an integer texture
	VIDEOPOST_GLINFO_PREPASS												= 0x01000000,	// GlDraw(VIDEOPOST_GLDRAW_PREPASS)
	VIDEOPOST_GLINFO_DRAW														= 0x02000000,	// GlDraw(VIDEOPOST_GLDRAW_DRAW)
	VIDEOPOST_GLINFO_3DSTEREO												= 0x04000000,	// GlDraw(VIDEOPOST_GLDRAW_DRAW)
	VIDEOPOST_GLINFO_ALLOC_UVW_MATID_BUFFER_FLOAT32 = 0x00000100,
	VIDEOPOST_GLINFO_DISABLED												= 0x80000000
} ENUM_END_FLAGS(VIDEOPOST_GLINFO);

// GlDraw flags
enum VIDEOPOST_GLDRAW
{
	VIDEOPOST_GLDRAW_0								 = 0,
	VIDEOPOST_GLDRAW_CUSTOM_MOUSE_INIT = (1 << 0),
	VIDEOPOST_GLDRAW_CUSTOM_MOUSE_DRAW = (1 << 1),
	VIDEOPOST_GLDRAW_PREPASS					 = (1 << 2),
	VIDEOPOST_GLDRAW_DRAW							 = (1 << 3)
} ENUM_END_FLAGS(VIDEOPOST_GLDRAW);

// message ID
#define MSG_VIDEOPOST_TIMESHIFT						300000106
#define MSG_GLOBALILLUMINATIONINFORMATION	300001050

struct GlobalIlluminationInformation
{
	Bool	reflective_caustics;
	Bool	refractive_caustics;
	Float refractive_cutoff;
	Bool	ambient_occlusion;
	Bool	radiance_enabled;
	Int32 radiance_mode;
	Int32 radiance_samples;
	Float radiance_density;
	Float radiance_intensity;
	Float radiance_saturation;
	Bool	lightmapping_enabled;
	Bool	lightmapping_direct;
	Int32 lightmapping_mode;
};

struct StereoCameraInfo
{
	Matrix m;
	Float	 off_x, off_y;
	String strName;
};

// set render properties
#define RENDERPROPERTY_CLUSTERFRAGMENTS	1
#define RENDERPROPERTY_BUCKETOVERLAP		2

class VideoPostData : public NodeData
{
public:
	////inherited from NodeData////
	//virtual Bool Init(GeListNode *node);
	//virtual void Free(GeListNode *node);
	//virtual Bool Read(GeListNode *node, HyperFile *hf, Int32 level);
	//virtual Bool Write(GeListNode *node, HyperFile *hf);
	//virtual Bool Message(GeListNode *node, Int32 type, void *data);
	//virtual Bool CopyTo(NodeData *dest, GeListNode *snode, GeListNode *dnode, COPYFLAGS flags, AliasTrans *trn);
	//virtual void GetBubbleHelp(GeListNode *node, String &str);
	//virtual BaseDocument* GetDocument(GeListNode *node);
	//virtual Int32 GetBranchInfo(GeListNode *node, BranchInfo *info, Int32 max, GETBRANCHINFO flags);
	//virtual Bool GetDDescription(GeListNode *node, Description *description, DESCFLAGS_DESC &flags);
	//virtual Bool GetDParameter(GeListNode *node, const DescID &id,GeData &t_data,DESCFLAGS_GET &flags);
	//virtual Bool GetDEnabling(GeListNode *node, const DescID &id,const GeData &t_data,DESCFLAGS_ENABLE flags,const BaseContainer *itemdesc);
	//virtual Bool SetDParameter(GeListNode *node, const DescID &id,const GeData &t_data,DESCFLAGS_SET &flags);
	//static NodeData *Alloc(void) { return NewObjClear(MyNodeData); }
	////inherited from NodeData////

	virtual Bool Draw(BaseVideoPost* node, BaseDraw* bd, BaseDrawHelp* bh);
	virtual void AllocateBuffers(BaseVideoPost* node, Render* render, BaseDocument* doc);
	virtual VIDEOPOSTINFO GetRenderInfo(BaseVideoPost* node);

	virtual RENDERRESULT Execute(BaseVideoPost* node, VideoPostStruct* vps);
	virtual void ExecuteLine(BaseVideoPost* node, PixelPost* pp);
	virtual void ExecutePixel(BaseVideoPost* node, PixelPost* pp, Int32 x, Int32 subx, Int32 suby);

	virtual void CalcVolumetric(BaseVideoPost* node, VolumeData* vd);
	virtual void CalcShadow(BaseVideoPost* node, VolumeData* vd);
	virtual Bool GlDraw(BaseVideoPost* node, BaseDraw* bd, GlFrameBuffer* fbuf, Int32 colortex, Int32 depthtex, VIDEOPOST_GLDRAW flags);
	virtual VIDEOPOST_GLINFO GetGlInfo(BaseVideoPost* node, BaseDocument* doc, BaseDraw* bd);

	virtual Vector ComputeDiffuseGI(BaseVideoPost* node, VolumeData* vd, Float receive_strength);
	virtual Vector ComputeDiffuseCaustic(BaseVideoPost* node, VolumeData* vd, Float sampleradius, Int32 accuracy);
	virtual Vector ComputeVolumeCaustic(BaseVideoPost* node, const Vector64& p, Int32 cpu_index);

	virtual void CreateRay(Ray* dst, Float x, Float y);
	virtual Int32 StereoGetCameraCountEditor(BaseVideoPost* node, BaseDocument* doc, BaseDraw* bd);
	virtual Int32 StereoGetCameraCountRenderer(BaseVideoPost* node, BaseDocument* doc, RenderData* rd);
	virtual Bool StereoGetCameraInfo(BaseVideoPost* node, BaseDocument* doc, BaseDraw* bd, RenderData* rd, Int32 index, StereoCameraInfo& info);
	virtual Int32 StereoGetSceneHookID(BaseVideoPost* node);
	virtual Bool StereoMergeImages(BaseVideoPost* node, BaseBitmap* dest, const BaseBitmap* const* source, Int32 cnt, const BaseContainer& settings, COLORSPACETRANSFORMATION transform);

	// test for allowed VP effects (in case of render engine) or for allowed render engine (in case of VP effect)
	virtual Bool RenderEngineCheck(BaseVideoPost* node, Int32 id);

	// set diffuse weight to control gi quality
	virtual void SetDiffuseWeight(BaseVideoPost* node, Int32 cpu_index, Float weight);

	// allows vp to create an extended ray for physical render
	virtual void CreateExtendedRay(Ray* dst, Float x, Float y, Float lensx, Float lensy, Float time);

	// net single frame functions
	virtual Bool NetFrameInit(BaseVideoPost* node, BaseDocument* doc, RenderJob* job, Int32 assignedClients, const NetRenderData* renderData, MultipassBitmap* frameBmp, BaseThread* bt, Int32& realdepth);
	virtual void NetFrameFree(BaseVideoPost* node);
	virtual Bool NetFrameMessage(BaseVideoPost* node, const C4DUuid& remoteUuid, const NetRenderBuffer& data, NetRenderBuffer* result);

	// net post buffers
	virtual Bool NetCreateBuffer(BaseVideoPost* node, VideoPostStruct* vps, Int32 x, Int32 y, Int32 sizex, Int32 sizey, Int32& id, Int32& subid);
};

Bool RegisterVideoPostPlugin(Int32 id, const String& str, Int32 info, DataAllocator* g, const String& description, Int32 disklevel, Int32 priority, void* emulation = nullptr);

#endif
