/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DPAINTER_H
#define __C4DPAINTER_H

#include "c4d_string.h"
#include "c4d_baselist.h"
#include "c4d_basebitmap.h"
#include "operatingsystem.h"

class BaseDocument;

void* SendPainterCommand(Int32 command, BaseDocument* doc, PaintTexture* tex, BaseContainer* bc);
	#define PAINTER_SAVETEXTURE					1000 // save textures (if doc -> all doc associated, if -> tex only tex, otherwise all textures)
		#define PAINTER_SAVETEXTURE_FLAGS						1
			#define PAINTER_SAVEBIT_SAVEAS						(1<<0)
			#define PAINTER_SAVEBIT_SAVECOPY					(1<<1)
			#define PAINTER_SAVEBIT_SAVEALLOWWARNING	(1<<2)
			#define PAINTER_SAVEBIT_RENAMEINSCENE			(1<<3)
	#define	PAINTER_BRINGTOFRONT				1001 // brings the bp window to front
	#define PAINTER_LOADTEXTURE					1002 // load texture to BP2
		#define LOADTEXTURE_FILENAME				1		// bc arguments
	#define PAINTER_FORCECLOSETEXTURE		1003 // remove the texture from memory
	#define PAINTER_CLOSETEXTURE				1004 // remove the texture from memory, but ask if texture is unsaved
	#define PAINTER_SAVETEXTURE_DIRECT	1005 // save textures
	#define PAINTER_RELOADTEXTURE				1006 // reload a texture in BP and c4d locklist for renderer!
		#define RELOADTEXTURE_FILENAME			1		// bc arguments
//-------
// new in BP2
//-------

struct TempUVHandle
{
private:
	TempUVHandle();
	~TempUVHandle();

public:
	// not allowed to change
	Int32 GetMode();
	const Vector* GetPoint();
	const CPolygon* GetPoly();
	BaseSelect* GetPolySel();
	BaseSelect* GetUVPointSel();	// 4*polycnt!!! 0..3 = a,b,c,d
	Int32 GetPointCount();
	Int32 GetPolyCount();
	BaseObject* GetBaseObject();
	Bool IsEditable();

	// allowed to change
	UVWStruct* GetUVW();

	Bool SetUVW(UVWStruct* uv);
};

TempUVHandle* GetActiveUVSet(BaseDocument* doc, Int32 flags);
	#define GETACTIVEUVSET_CHECKENABLING				(1<<0)
	#define GETACTIVEUVSET_UVWS									(1<<1)
	#define GETACTIVEUVSET_POLYS								(1<<2)
	#define GETACTIVEUVSET_POLYSELECTION				(1<<3)
	#define GETACTIVEUVSET_POINTS								(1<<4)
	#define GETACTIVEUVSET_POINTSELECTION				(1<<5)
	#define GETACTIVEUVSET_OBJECT								(1<<6)
	#define GETACTIVEUVSET_MODE									(1<<7)

	#define GETACTIVEUVSET_ALL_CHECKENABLING		(0xFFFF)
	#define GETACTIVEUVSET_ALL									(0xFFFF & ~GETACTIVEUVSET_CHECKENABLING)

void FreeActiveUVSet(TempUVHandle* handle);

//-------

//-------


Bool CallUVCommand(const Vector* padr, Int32 PointCount, const CPolygon* polys, Int32 lPolyCount, UVWStruct* uvw, BaseSelect* polyselection,
									 BaseSelect* pointselection, BaseObject* op, Int32 mode, Int32 cmdid, const BaseContainer& settings);
#define UVCOMMAND_OPTIMALMAPPING		10000
#define UVCOMMAND_OPTIMALCUBICMAPPING			10001
#define UVCOMMAND_REALIGN           10002
	#define OPTIMALMAPPING_PRESERVEORIENTATION	1000	// BOOL (c, a, r)
	#define OPTIMALMAPPING_STRETCHTOFIT					1001	// BOOL (c, a, r)
	#define OPTIMALMAPPING_DISTORTION						1002	// REAL (a)
	#define OPTIMALMAPPING_SPACING							1003	// REAL (c, a, r)
	#define OPTIMALMAPPING_AREAFAK							1004  // REAL (c)
	#define OPTIMALMAPPING_TWOD									1005  // BOOL (c)
	#define OPTIMALMAPPING_PROGRESSBAR          1006  // BOOL (c, a, r)
	#define OPTIMALMAPPING_RELAXCOUNT           1007  // Int32 (c, a)
	#define OPTIMALMAPPING_EQUALIZEAREA					1008	// Bool
#define UVCOMMAND_RELAX               10003
	#define RELAXUV_KEEP_BORDER                 1010  // BOOL
	#define RELAXUV_KEEP_NEIGHBORS              1011  // BOOL
	#define RELAXUV_KEEP_POINTSEL               1012  // BOOL
	#define RELAXUV_CUT_EDGESEL                 1013  // BOOL
	#define RELAXUV_EDGESEL_POINTER             1022  // BaseSelect*
	#define RELAXUV_MAX_ITERATIONS              1014  // Int32
	#define RELAXUV_MODE                        1024  // Int32
		#define RELAXUV_MODE_LSCM 0
		#define RELAXUV_MODE_ABF  1

#define UVCOMMAND_COPY_UV           10004
#define UVCOMMAND_PASTE_UV          10005
#define UVCOMMAND_MAX_UV            10006
#define UVCOMMAND_FLIP_SEQUENCE     10007
#define UVCOMMAND_MOVE_DOWN_SEQUENCE  10008
#define UVCOMMAND_MOVE_UP_SEQUENCE    10009
#define UVCOMMAND_TERRACE           10010
#define UVCOMMAND_FIT_TO_CANVAS     10011
#define UVCOMMAND_TRANSFORM         10012
	#define UVCOMMAND_TRANSFORM_MOVE_X          1020 // REAL
	#define UVCOMMAND_TRANSFORM_MOVE_Y          1021 // REAL
	#define UVCOMMAND_TRANSFORM_SCALE_X         1022 // REAL
	#define UVCOMMAND_TRANSFORM_SCALE_Y         1023 // REAL
	#define UVCOMMAND_TRANSFORM_ANGLE           1024 // REAL (Angle in Radians)
#define UVCOMMAND_LINEUP            10013
#define UVCOMMAND_UNSTITCH          10014
#define UVCOMMAND_BOUNDARY2SHAPE    10015
	#define UVCOMMAND_BOUNDARY2SHAPE_MODE       1000 // Int32
		#define UVCOMMAND_BOUNDARY2SHAPE_CIRCLE     0
		#define UVCOMMAND_BOUNDARY2SHAPE_QUAD       1


//-------

Int32 IdentifyImage(const Filename& texpath);
Bool BPSetupWizardWithParameters(BaseDocument* doc, const BaseContainer& settings, AtomArray& objects, AtomArray& material);
	// automatic mapsize interpolation
	#define AMSI_CREATE_MISSING_MATERIALS		4000	// Bool: create materials and texturetag if missing
	#define AMSI_CREATE_MISSING_CHANNELS		4001	// Bool: create missing texture channels
	#define AMSI_AUTOSELECT_MATERIALS				4002	// Bool: autoselect materials from object selection
	#define AMSI_AUTOSELECT_OBJECTS					4003	// Bool: autoselect objects from materials selection
	#define AMSI_DELETE_BROKENMATERIALTAGS	4004	// Bool: autoselect objects from materials selection
	#define AMSI_ENABLEMATERIALS						4005  // Bool: enable all materials for painting
	#define AMSI_SINGLEMATERIAL							4006	// Bool: join uvw's in one material

	#define CREATE_CHANNEL/*+CHANNEL_xxx*/	4100 // -4199 Bool: create missing texture channels
	#define CREATE_CHANNEL_C/*+CHANNEL_xxx*/4200 // -4299 Vector: channel color

	#define AMSI_ENABLED										5000  // Bool: automatic mapsize interpolation enabled, otherwise minsize == texsize
	#define AMSI_TEXW												5001  // Int32: fixed texsize
	#define AMSI_TEXH												5002  // Int32: fixed texsize
	#define AMSI_TEXMIN											5003  // Int32: min texturesize w/h
	#define AMSI_TEXMAX											5004  // Int32: max texturesize w/h
	#define AMSI_QUANTIZE										5005	// Int32: quantize texturesize
	#define AMSI_RESCALE_EXISTING						5006	// Bool: rescale existing material channels
	#define AMSI_USE_SAME_RES								5007  // Bool: if already one channel exists, use the same texturesize

	#define AMSI_UV_CALC_METHOD							6000	// Int32: calculation mode
		#define UV_CALC_METHOD_OPTIMAL1					1
		#define UV_CALC_METHOD_OPTIMAL2					2
		#define UV_CALC_METHOD_REALIGN					3
	#define AMSI_UV_CALC_EXISTING						6001	// calculate uvs
	#define AMSI_UV_RELAXATION							6002

struct TextureSize
{
	Float w, h;
};

Bool CalculateTextureSize(BaseDocument* doc, AtomArray& materials, TextureSize*& sizes/* must be freed with DeleteMem */);

// new for 9.1

// GetType() returns this for bodypaint objects
#define OBJECT_PAINTLAYERBMP		(501)
#define OBJECT_PAINTTEXTURE			(502)
#define OBJECT_PAINTBITMAP			(543)	// for use of InstanceOf
#define OBJECT_PAINTLAYERFOLDER	(542)
#define OBJECT_PAINTLAYER				(544)

#ifndef __API_INTERN__

#define UPDATE_CHILDREN				(1<<0)
#define UPDATE_PARENTS				(1<<1)
#define UPDATE_PREVIEW				(1<<2)
#define UPDATE_REFRESH2D			(1<<3)
#define UPDATE_RECALC					(1<<4)
#define UPDATE_NOSAVECHG			(1<<6)
#define UPDATE_NOOFFSET				(1<<7) // especially for layermasks
#define UPDATE_REFRESH3D			(1<<8)
#define UPDATE_REFRESHCURSOR	(1<<9)
#define UPDATE_NOSTOPTHREADS	(1<<10)

#define UPDATE_STD        (UPDATE_PARENTS|UPDATE_PREVIEW|UPDATE_REFRESH2D|UPDATE_REFRESH3D|UPDATE_RECALC)

class PaintBitmap : public BaseList2D
{
private:
	PaintBitmap();
	~PaintBitmap();

public:
	Int32 GetBw() { return C4DOS.Pa->PB_GetBw(this); }
	Int32 GetBh() { return C4DOS.Pa->PB_GetBh(this); }

	PaintTexture* GetPaintTexture() { return C4DOS.Pa->PB_GetPaintTexture(this); }
	PaintBitmap* GetParent()				{ return C4DOS.Pa->PB_GetParent(this); }

	PaintLayer* GetLayerDownFirst() { return C4DOS.Pa->PB_GetLayerDownFirst(this); }
	PaintLayer* GetLayerDownLast()  { return C4DOS.Pa->PB_GetLayerDownLast(this); }

	PaintLayer* GetAlphaFirst()			{ return C4DOS.Pa->PB_GetAlphaFirst(this); }
	PaintLayer* GetAlphaLast()			{ return C4DOS.Pa->PB_GetAlphaLast(this); }

	PaintLayerBmp* AddAlphaChannel(Int32 bitdepth/* BITDEPTH_xxx */, PaintLayer* prev = nullptr, Bool undo = true, Bool activate = true) { return C4DOS.Pa->PB_AddAlphaChannel(this, bitdepth, prev, undo, activate); }
	Bool AskApplyAlphaMask()				{ return C4DOS.Pa->PB_AskApplyAlphaMask(this); }
	void ApplyAlphaMask(Int32 x, Int32 y, Int32 cnt, PIX* bits, Int32 mode/* MODE_xxx */, Bool inverted, Int32 flags/* GETPIXEL_xxx */) { C4DOS.Pa->PB_ApplyAlphaMask(this, x, y, cnt, bits, mode, inverted, flags); }

	PaintLayerMask* FindSelectionMask(PaintBitmap** toplevel, Int32* bitdepth) { return C4DOS.Pa->PB_FindSelectionMask(this, toplevel, bitdepth); }

	Int32 GetColorMode()	{ return C4DOS.Pa->PB_GetColorMode(this); };
	UInt32 GetDirty(DIRTYFLAGS flags) { return C4DOS.Pa->PB_GetDirty(this, flags); }

	void UpdateRefresh(Int32 xmin, Int32 ymin, Int32 xmax, Int32 ymax, UInt32 flags/* UPDATE_xxx */) { C4DOS.Pa->PB_UpdateRefresh(this, xmin, ymin, xmax, ymax, flags); }

	void UpdateRefreshAll(UInt32 flags/* UPDATE_xxx */, Bool reallyall) { C4DOS.Pa->PB_UpdateRefreshAll(this, flags, reallyall); }

	Bool ReCalc(BaseThread* thread, Int32 x1, Int32 y1, Int32 x2, Int32 y2, BaseBitmap* bmp, Int32 flags/* RECALC_xxx */, UInt32 showbit)  { return C4DOS.Pa->PB_ReCalc(this, thread, x1, y1, x2, y2, bmp, flags, showbit); }
	#define RECALC_NOGRID	 1
	#define RECALC_INITBMP 2

	// static
	static Bool ConvertBits(Int32 cnt, const PIX* src, Int32 srcinc, COLORMODE srcmode/* MODE_xxx */, PIX* dst, Int32 dstinc, COLORMODE dstmode/* MODE_xxx */, Int32 dithery, Int32 ditherx) { return C4DOS.Pa->PB_ConvertBits(cnt, src, srcinc, srcmode, dst, dstinc, dstmode, dithery, ditherx); }
};

class PaintLayer : public PaintBitmap
{
private:
	PaintLayer();
	~PaintLayer();

public:
	Bool GetShowBit(Bool hierarchy, UInt32 bit) { return C4DOS.Pa->PL_GetShowBit(this, hierarchy, bit); }
	Bool SetShowBit(Bool onoff, UInt32 bit) { return C4DOS.Pa->PL_SetShowBit(this, onoff, bit); }
};

class PaintLayerMask : public PaintLayer
{
private:
	PaintLayerMask();
	~PaintLayerMask();

public:
};

class PaintLayerFolder : public PaintLayer
{
private:
	PaintLayerFolder();
	~PaintLayerFolder();

public:
};

// Flags for GetPixelCnt
#define GETPIXEL_ALPHAMASKS					(1<<0) // calculate alpha masks
#define GETPIXEL_USEBLENDING				(1<<1) // calculate transparent value of layer
#define GETPIXEL_ALL								(GETPIXEL_ALPHAMASKS|GETPIXEL_USEBLENDING)
#define GETPIXEL_NOMASK							(1<<2) // calculate no mask
#define GETPIXEL_CACHE							(1<<3) // internal flag
#define GETPIXEL_NOWORK							(1<<4) // no work layer
#define GETPIXEL_ONLYWORK						(1<<5) // no work layer
#define GETPIXEL_TILE_BOTH					(GETPIXEL_TILE_U|GETPIXEL_TILE_V) // activate tiling
#define GETPIXEL_DONTAPPLYMASK			(1<<7) // do not apply mask on work
#define GETPIXEL_USESELECTED				(1<<8) // calculate no mask
#define GETPIXEL_DITHERING					(1<<9) // use dithering
#define GETPIXEL_PROJECTIONPIXEL		(1<<10) // use special projection paint RGBA color, a kind of hack
#define GETPIXEL_RECALCBRUSHSTROKE	(1<<11) // special flag for brushs stroke
#define GETPIXEL_VOXELCACHING				(1<<12) // use voxel caching
#define GETPIXEL_MERGE							(1<<13) // only merge, no get at collect
#define GETPIXEL_TILE_U							(1<<15) // activate tiling in u dir
#define GETPIXEL_TILE_V							(1<<16) // activate tiling in v dir

class PaintLayerBmp : public PaintLayer
{
private:
	PaintLayerBmp();
	~PaintLayerBmp();

public:
	// copies the content of BaseBitmap into the layer
	Bool ImportFromBaseBitmap(BaseBitmap* bmp, Bool usealpha) { return C4DOS.Pa->PLB_ImportFromBaseBitmap(this, bmp, usealpha); }
	Bool ImportFromBaseBitmapAlpha(BaseBitmap* bmp, BaseBitmap* channel) { return C4DOS.Pa->PLB_ImportFromBaseBitmapAlpha(this, bmp, channel); }

	Bool GetPixelCnt(Int32 x, Int32 y, Int32 cnt, PIX* dst, COLORMODE dstmode, PIXELCNT flags) { return C4DOS.Pa->PLB_GetPixelCnt(this, x, y, cnt, dst, dstmode, flags); }
	void SetPixelCnt(Int32 x, Int32 y, Int32 cnt, const PIX* src, Int32 incsrc, COLORMODE srcmode, PIXELCNT flags) { C4DOS.Pa->PLB_SetPixelCnt(this, x, y, cnt, src, incsrc, srcmode, flags); }

	void GetBoundingBox(Int32& x1, Int32& y1, Int32& x2, Int32& y2, Bool hasselectionpixels = false) { C4DOS.Pa->PLB_GetBoundingBox(this, x1, y1, x2, y2, hasselectionpixels); }
};

class PaintTexture : public PaintBitmap
{
private:
	PaintTexture();
	~PaintTexture();

public:
	PaintLayer* GetFirstLayer() { return C4DOS.Pa->PB_GetLayerDownFirst(this); }
	PaintLayer* GetLastLayer() { return C4DOS.Pa->PB_GetLayerDownLast(this); }

	// adds a layer to this texture
	PaintLayerBmp* AddLayerBmp(PaintLayer* insertafter, PaintLayer* layerset = nullptr, COLORMODE mode = COLORMODE_ARGB, Bool useundo = true, Bool activate = true) { return C4DOS.Pa->PT_AddLayerBmp(this, insertafter, layerset, mode, useundo, activate); }
	PaintLayerFolder* AddLayerFolder(PaintLayer* insertafter, PaintLayer* insertunder, Bool useundo = true, Bool activate = true) { return C4DOS.Pa->PT_AddLayerFolder(this, insertafter, insertunder, useundo, activate); }

	void SetActiveLayer(PaintLayer* layer, Bool activatetexture, Bool show = true) { C4DOS.Pa->PT_SetActiveLayer(this, layer, activatetexture, show); }
	PaintLayer* GetActive() { return C4DOS.Pa->PT_GetActive(this); }
	void GetLinkLayers(AtomArray& layers, Bool addfolders) { C4DOS.Pa->PT_GetLinkLayers(this, layers, addfolders); }

	void SetColorMode(COLORMODE newcolormode, Bool doundo) { C4DOS.Pa->PT_SetColorMode(this, newcolormode, doundo); }

	const Filename GetFilename() { return C4DOS.Pa->PT_GetFilename(this); }

	Int32 GetLayerCount() const;
	Int32 GetAlphaCount() const;

	// static functions
	static GeListHead* GetPaintTextureHead() { return C4DOS.Pa->PT_GetPaintTextureHead(); }

	static PaintTexture* CreateNewTexture(const Filename& path, const BaseContainer& settings);
	static Bool GetTextureDefaults(Int32 channel, BaseContainer& settings);

	// resolves the painttexture used in a basechannel
	static inline PaintTexture* GetPaintTextureOfBaseChannel(BaseDocument* doc, BaseChannel* bc) { return C4DOS.Pa->GetPaintTextureOfBaseChannel(doc, bc); }

	static Bool SetSelected_Texture(PaintBitmap* bmp, PaintMaterial* preferred) { return C4DOS.Pa->PT_SetSelected_Texture(bmp, preferred); }
	static PaintTexture* GetSelectedTexture() { return C4DOS.Pa->PT_GetSelectedTexture(); }
	static PaintTexture* GetSelectedTexturePP(PaintMaterial** ppmat = nullptr) { return C4DOS.Pa->PT_GetSelectedTexturePP(ppmat); }
};

class PaintMaterial : public PaintBitmap
{
private:
	PaintMaterial();
	~PaintMaterial();

public:
	void EnableMaterial(BaseDocument* doc, Bool on, Bool suppressevent = false, Bool domaterialundo = true) { C4DOS.Pa->PM_EnableMaterial(this, doc, on, suppressevent, domaterialundo); }

	// static functions
	static PaintMaterial* GetActivePaintMaterial(BaseDocument* doc = nullptr, BaseMaterial** mat = nullptr) { return C4DOS.Pa->PM_GetActivePaintMaterial(doc, mat); }
	static PaintMaterial* GetPaintMaterialFromTexture(PaintTexture* tex, Bool onlyeditable) { return C4DOS.Pa->PM_GetPaintMaterialFromTexture(tex, onlyeditable); }
	static PaintMaterial* GetPaintMaterial(BaseDocument* doc, BaseMaterial* material, Bool create) { return C4DOS.Pa->PM_GetPaintMaterial(doc, material, create); }
	static Bool UnloadPaintMaterial(BaseDocument* doc, BaseMaterial* material, Bool forcesave) { return C4DOS.Pa->PM_UnloadPaintMaterial(doc, material, forcesave); }
	static Bool SaveDocument(BaseDocument* doc, Bool& cancel) { return C4DOS.Pa->PM_SaveDocument(doc, cancel); }
	static Bool AskNeedToSave(BaseDocument* doc) { return C4DOS.Pa->PM_AskNeedToSave(doc); }
};

#endif

// flags for PaintTexture::CreateNewTexture and PaintTexture::GetTextureDefaults
#define TEXTURE_FILEFORMAT			1000	// Int32
#define TEXTURE_WIDTH						1001	// Int32
#define TEXTURE_HEIGHT					1002	// Int32
#define TEXTURE_MODE						1003	// allowed COLORMODE_GRAY,COLORMODE_RGB,COLORMODE_RGBw,COLORMODE_GRAYw,COLORMODE_RGBf,COLORMODE_GRAYf
#define TEXTURE_COLOR						1004	// vector
#define TEXTURE_SAVE_IMMEDIATLY	1005	// bool: flag if save immediately, otherwise it's only created in memory

#define GETALLSTRINGS_FILESTRING		 1
#define GETALLSTRINGS_SUGGESTED_PATH 2
#define GETALLSTRINGS_CHANNEL_ID		 3
Bool GetAllStrings_AddTexture(const void* msgdata, const BaseContainer& d);

void PainterActivateChannel(Int32 channel, Bool multi, Bool enable);
PaintTexture*	PainterCreateNewTextureDialog(String& result, Filename& resultdirectory, Int32 channelid, BaseMaterial* bmat);

#endif
