/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DBASEDRAW_H
#define __C4DBASEDRAW_H

#ifdef __API_INTERN__
abc def xyz
#endif

#include "ge_math.h"
#include "c4d_baselist.h"
#include "c4d_basecontainer.h"
#include "c4d_general.h"
#include "matrix4.h"

class BaseDrawHelp
{
private:
	BaseDrawHelp();
	~BaseDrawHelp();

public:
	BaseDocument* GetDocument(void)             { return C4DOS.Br->BbGetDocument(this); }
	BaseTag* GetActiveTag(void)            { return C4DOS.Br->BbGetActiveTag(this); }
	const Matrix&	GetMg(void)                    { return C4DOS.Br->BbGetMg(this); }
	BaseContainer	GetDisplay(void)               { BaseContainer bc; C4DOS.Br->BbGetDisplay(this, &bc); return bc; }
	void SetDisplay(BaseContainer* bc)  { C4DOS.Br->BbSetDisplay(this, bc); }
	void SetMg(const Matrix& mg)        { C4DOS.Br->BbSetMg(this, mg); }
	DRAWFLAGS	GetViewSchedulerFlags() const { return C4DOS.Br->BbGetViewSchedulerFlags(this); }
	Bool IsActive() const { return C4DOS.Br->BbIsActive(this); }
	Bool IsHighlight() const { return C4DOS.Br->BbIsHighlight(this); }

	static BaseDrawHelp* Alloc(BaseDraw* bd, BaseDocument* doc);
	static void Free(BaseDrawHelp*& p);
};

#define SET_PEN_USE_PROFILE_COLOR	1

#define MAX_Z	1000000

#define VIEW_NEARCLIPPING	0.01

enum OITMODE
{
	OITMODE_OFF		 = 0,
	OITMODE_FIRST	 = 1,
	OITMODE_MIDDLE = 2,
	OITMODE_LAST	 = 3
} ENUM_END_LIST(OITMODE);

struct OITInfo
{
	OITMODE		 mode;
	Int32			 lPass;
	C4DGLuint	 nDepthTexture;
	void*			 pData;
	Vector4d32 vScaleOff;
};

struct BDSetSceneCameraMsg
{
	BaseObject* op;
	Bool				animate;
};

#define DRAW_STATISTIC_TRIANGLES			 0
#define DRAW_STATISTIC_QUADS					 1
#define DRAW_STATISTIC_LINES					 2
#define DRAW_STATISTIC_POINTS					 3
#define DRAW_STATISTIC_TRIANGLE_STRIPS 4
#define DRAW_STATISTIC_LINE_STRIPS		 5

class BaseView : public BaseList2D
{
private:
	BaseView();
	~BaseView();

public:
	void GetFrame(Int32* cl, Int32* ct, Int32* cr, Int32* cb);
	void GetSafeFrame(Int32* cl, Int32* ct, Int32* cr, Int32* cb);
	void GetViewParameter(Vector* offset, Vector* scale, Vector* scale_z) const;
	Matrix GetMg(void) { return C4DOS.Bv->GetMg(this); }
	Matrix GetMi(void) { return C4DOS.Bv->GetMi(this); }
	const Matrix& GetBaseMatrix() const { return C4DOS.Bv->GetBaseMatrix(this); }
	void SetBaseMatrix(const Matrix& m) { C4DOS.Bv->SetBaseMatrix(this, m); }
	Float GetPlanarRotation() const { return C4DOS.Bv->GetPlanarRotation(this); }
	void SetPlanarRotation(Float r) { C4DOS.Bv->SetPlanarRotation(this, r); }
	Int32 GetProjection(void) { return C4DOS.Bv->GetProjection(this); }
	Bool TestPoint(Float x, Float y) { return C4DOS.Bv->TestPoint(this, x, y); }
	Bool TestPointZ(const Vector& p) { return C4DOS.Bv->TestPointZ(this, p); }
	Bool TestClipping3D(const Vector& mp, const Vector& rad, const Matrix& mg, Bool* clip2d, Bool* clipz);
	Bool ClipLine2D(Vector* p1, Vector* p2) { return C4DOS.Bv->ClipLine2D(this, p1, p2); }
	Bool ClipLineZ(Vector* p1, Vector* p2) { return C4DOS.Bv->ClipLineZ(this, p1, p2); }
	Vector WS(const Vector& p) { return C4DOS.Bv->WS(this, p); }
	Vector SW(const Vector& p) { return C4DOS.Bv->SW(this, p); }
	Vector SW_Reference(Float x, Float y, const Vector& wp) { return C4DOS.Bv->SW_R(this, x, y, wp); }
	Vector WC(const Vector& p) { return C4DOS.Bv->WC(this, p); }
	Vector CW(const Vector& p) { return C4DOS.Bv->CW(this, p); }
	Vector SC(const Vector& p) { return C4DOS.Bv->SC(this, p); }
	Vector CS(const Vector& p, Bool z_inverse) { return C4DOS.Bv->CS(this, p, z_inverse); }
	Vector WC_V(const Vector& v) { return C4DOS.Bv->WC_V(this, v); }
	Vector CW_V(const Vector& v) { return C4DOS.Bv->CW_V(this, v); }
	Bool BackfaceCulling(const Vector& n, const Vector& p) { return C4DOS.Bv->BackfaceCulling(this, n, p); }
	Bool ZSensitiveNear(void) { return C4DOS.Bv->ZSensitiveNear(this); }
	Float ZSensitiveNearClipping(void) { return C4DOS.Bv->ZSensitiveNearClipping(this); }
	StereoCameraInfo* GetStereoInfo() const { return C4DOS.Bv->GetStereoInfo(this); }
	Bool ZSensitiveFar(void) { return C4DOS.Bv->ZSensitiveFar(this); }
	Float ZSensitiveFarClipping(void) { return C4DOS.Bv->ZSensitiveFarClipping(this); }

	Float PW_S(Float z, Bool horizontal);					//Pixel Unit to World Unit with screen z
	Float WP_S(Float z, Bool horizontal);					//World Unit to Pixel Unit with screen z
	Float PW_W(const Vector& p, Bool horizontal);	//Pixel Unit at world position to World Unit
	Float WP_W(const Vector& p, Bool horizontal);	//World Unit at world position to Pixel Unit

	Vector ProjectPointOnLine(const Vector& p, const Vector& v, Float mouse_x, Float mouse_y, Float* offset = nullptr, Int32* err = nullptr);
	Vector ProjectPointOnPlane(const Vector& p, const Vector& v, Float mouse_x, Float mouse_y, Int32* err = nullptr);
};

// for GetViewMatrix
#define DRAW_GET_VIEWMATRIX_PROJECTION					 0
#define DRAW_GET_VIEWMATRIX_PROJECTION_LARGE_Z	 1
#define DRAW_GET_VIEWMATRIX_INV_CAMERA					 2
#define DRAW_GET_VIEWMATRIX_MODELVIEW_PROJECTION 3	// slow

class BaseDraw : public BaseView
{
private:
	BaseDraw();
	~BaseDraw();

	// only access through GetParameter/SetParameter!!!
	BaseContainer GetData(void);
	void SetData(const BaseContainer& bc, Bool add = true);
	BaseContainer* GetDataInstance(void);

public:
	GeData GetParameterData(Int32 id);

public:
	static BaseDraw* Alloc() { return C4DOS.Br->AllocBaseDraw(); }
	static void Free(BaseDraw*& bd) { C4DOS.Br->FreeBaseDraw(bd); }

	Int32 GetFrameScreen(Int32* cl, Int32* ct, Int32* cr, Int32* cb);	// runs only with activated OpenGL, -2: no OpenGL window, -1: offscreen view, 0: system error, 1: success
	Bool HasCameraLink(void) { return C4DOS.Br->HasCameraLink(this); }
	void SetSceneCamera(BaseObject* op, Bool animate = false)  { C4DOS.Br->SetSceneCamera(this, op, animate); }
	BaseObject* GetSceneCamera(const BaseDocument* doc)  { return C4DOS.Br->GetSceneCamera(this, doc); }
	BaseObject* GetEditorCamera(void)  { return C4DOS.Br->GetEditorCamera(this); }
	DISPLAYFILTER GetDisplayFilter() { return C4DOS.Br->GetDisplayFilter(this); }
	DISPLAYEDITSTATE GetEditState() { return C4DOS.Br->GetEditState(this); }
	Bool IsViewOpen(BaseDocument* doc)  { return C4DOS.Br->IsViewOpen(this, doc); }

#define INIT_CLIPBOX_ADJUSTGLSIZE	1
	void InitClipbox(Int32 left, Int32 top, Int32 right, Int32 bottom, Int32 flags) { C4DOS.Br->InitClipbox(this, left, top, right, bottom, flags); }
	void InitView(BaseContainer* camera, const Matrix& op_m, Float sv, Float pix_x, Float pix_y, Bool fitview) { C4DOS.Br->InitView(this, camera, op_m, sv, pix_x, pix_y, fitview); }
	void InitializeView(BaseDocument* doc, BaseObject* cam, Bool editorsv) { C4DOS.Br->InitializeView(this, doc, cam, editorsv); }
	void AddMessageHook(BaseDrawMessageHook fn) { C4DOS.Br->AddMessageHook(this, fn); }

	Bool AddToPostPass(BaseObject* op, BaseDrawHelp* bh)  { return C4DOS.Br->AddToPostPass(this, op, bh, 0); }

	Vector GetObjectColor(BaseDrawHelp* bh, BaseObject* op, Bool lines = false)  { return C4DOS.Br->GetObjectColor(this, op, bh, lines); }
	Vector CheckColor(const Vector& col)  { return C4DOS.Br->CheckColor(this, col); }

	void SetTransparency(Int32 trans)  { C4DOS.Br->SetTransparency(this, trans); }
	Int32 GetTransparency(void)  { return C4DOS.Br->GetTransparency(this); }

	Bool PointInRange(const Vector& p, Int32 x, Int32 y)  { return C4DOS.Br->PointInRange(this, p, x, y); }
	void SetPen(const Vector& col, Int32 flags = 0)  { C4DOS.Br->SetPen(this, col, flags); }
	void SetPointSize(Float pointsize) { C4DOS.Br->SetPointSize(this, pointsize); }
	Vector ConvertColor(const Vector& c) { return C4DOS.Br->ConvertColor(this, c); }
	Vector ConvertColorReverse(const Vector& c) { return C4DOS.Br->ConvertColorReverse(this, c); }
	Float SimpleShade(const Vector& p, const Vector& n)  { return C4DOS.Br->SimpleShade(this, p, n); }

	void LineZOffset(Int32 offset) { C4DOS.Br->LineZOffset(this, offset); }
	void SetDepth(Bool enable) { C4DOS.Br->SetDepth(this, enable); }
	void SetMatrix_Projection() { C4DOS.Br->SetMatrix_Projection(this); }																														// sets the projection matrix
	void SetMatrix_Screen() { C4DOS.Br->SetMatrix_Screen(this); }																																		// sets the transformation matrix to screencoordinates
	void SetMatrix_Screen(Int32 zoffset) { C4DOS.Br->SetMatrix_ScreenO(this, zoffset); }																						// sets the transformation matrix to screencoordinates
	void SetMatrix_Screen(Int32 zoffset, const Matrix4d* m) { C4DOS.Br->SetMatrix_ScreenOM(this, zoffset, m); }											// sets the transformation matrix to screencoordinates
	void SetMatrix_Camera() { C4DOS.Br->SetMatrix_Camera(this); }																																		// sets the transformation matrix to camerasystem
	void SetMatrix_Matrix(BaseObject* op, const Matrix& mg) { C4DOS.Br->SetMatrix_Matrix(this, op, mg); }														// sets the transformation matrix to the given matrix
	void SetMatrix_Matrix(BaseObject* op, const Matrix& mg, Int32 zoffset) { C4DOS.Br->SetMatrix_MatrixO(this, op, mg, zoffset); }	// sets the transformation matrix to the given matrix
	void SetClipPlaneOffset(Float o) { C4DOS.Br->SetClipPlaneOffset(this, o); }
	// flags for DrawLine,LineStrip,DrawHandle,DrawPoly,...
#define NOCLIP_D 1	// clip against the view border
#define NOCLIP_Z 2	// z clipping
	void LineStripBegin() { C4DOS.Br->LineStripBegin(this); }
	void LineStrip(const Vector& vp, const Vector& vc, Int32 flags) { C4DOS.Br->LineStrip(this, vp, vc, flags); }
	void LineStripEnd() { C4DOS.Br->LineStripEnd(this); }

	void DrawPoint2D(const Vector& p)  { C4DOS.Br->DrawPoint2D(this, p); }
	void DrawLine2D(const Vector& p1, const Vector& p2)  { C4DOS.Br->DrawLine2D(this, p1, p2); }
	void DrawHandle2D(const Vector& p, DRAWHANDLE type = DRAWHANDLE_SMALL) { C4DOS.Br->DrawHandle2D(this, p, type); }
	void DrawCircle2D(Int32 mx, Int32 my, Float rad) { C4DOS.Br->DrawCircle2D(this, mx, my, rad); }
	void DrawHandle(const Vector& vp, DRAWHANDLE type, Int32 flags) { C4DOS.Br->DrawHandle(this, vp, type, flags); }
	void DrawPointArray(Int32 cnt, const Vector32* vp, const Float32* vc = nullptr, Int32 colcnt = 0, const Vector32* vn = nullptr) { C4DOS.Br->DrawPointArray(this, cnt, vp, vc, colcnt, vn); }
	void DrawLine(const Vector& p1, const Vector& p2, Int32 flags) { C4DOS.Br->DrawLine(this, p1, p2, flags); }
	void DrawArc(const Vector& pos, Float radius, Float angle_start, Float angle_end, Int32 subdiv = 32, Int32 flags = 0) { C4DOS.Br->DrawArc(this, pos, radius, angle_start, angle_end, subdiv, flags); }
	void DrawPoly(Vector* vp, Vector* vf, Vector* vn, Int32 anz, Int32 flags) { C4DOS.Br->DrawPoly(this, vp, vf, vn, anz, flags); }
	void DrawTexture(const BaseBitmap* bmp, Vector* padr4, Vector* cadr, Vector* vnadr, Vector* uvadr, Int32 pntcnt, DRAW_ALPHA alphamode, DRAW_TEXTUREFLAGS flags) { C4DOS.Br->DrawTexture(this, bmp, padr4, cadr, vnadr, uvadr, pntcnt, alphamode, flags); }
	void DrawTexture(C4DGLuint bmp, Vector* padr4, Vector* cadr, Vector* vnadr, Vector* uvadr, Int32 pntcnt, DRAW_ALPHA alphamode) { C4DOS.Br->DrawTexture1(this, bmp, padr4, cadr, vnadr, uvadr, pntcnt, alphamode); }
	void DrawCircle(const Matrix& m) { C4DOS.Br->DrawCircle(this, m); }
	void DrawBox(const Matrix& m, Float size, const Vector& col, Bool wire) { C4DOS.Br->DrawBox(this, m, size, col, wire); }
	void DrawPolygon(Vector* p, Vector* f, Bool quad) { C4DOS.Br->DrawPolygon(this, p, f, quad); }
	void DrawSphere(const Vector& off, const Vector& size, const Vector& col, Int32 flags) { C4DOS.Br->DrawSphere(this, off, size, col, flags); }
#define BDRAW_DRAW_SPHERE_FLAGS_NO_SHADING 1
	void DrawArrayEnd() { C4DOS.Br->DrawArrayEnd(this); }
	DRAWRESULT DrawPolygonObject(BaseDrawHelp* bh, BaseObject* op, DRAWOBJECT flags, BaseObject* parent = nullptr, const Vector& col = Vector(.5)) { return C4DOS.Br->DrawPObject(this, bh, op, flags, DRAWPASS_OBJECT, parent, col); }
	DRAWRESULT DrawObject(BaseDrawHelp* bh, BaseObject* op, DRAWOBJECT flags, DRAWPASS drawpass, BaseObject* parent = nullptr, const Vector& col = Vector(.5)) { return C4DOS.Br->DrawPObject(this, bh, op, flags | DRAWOBJECT_PRIVATE_ANY, drawpass, parent, col); }
	Bool DrawScene(Int32 flags) { return C4DOS.Br->DrawScene(this, flags); }
	DISPLAYMODE GetReductionMode() const { return C4DOS.Br->GetReductionMode(this); }
	Bool GetHighlightPassColor(const BaseDrawHelp& bh, Bool lineObject, Vector& col) const { return C4DOS.Br->GetHighlightPassColor(this, bh, lineObject, col); }
	GlFrameBuffer* GetHighlightFramebuffer(const Vector32& vMin = Vector32(-1.0f), const Vector32& vMax = Vector32(1.0f)) { return C4DOS.Br->GetHighlightFramebuffer(this, vMin, vMax); }

	Bool InitDrawXORPolyLine() { return C4DOS.Br->InitDrawXORLine(this); }
	void FreeDrawXORPolyLine() { C4DOS.Br->FreeDrawXORLine(this); }
	void DrawXORPolyLine(const Float32* p, Int32 cnt) { C4DOS.Br->DrawXORPolyLine(this, p, cnt); }
	void BeginDrawXORPolyLine() { C4DOS.Br->BeginDrawXORPolyLine(this); }
	void EndDrawXORPolyLine(Bool blit) { C4DOS.Br->EndDrawXORPolyLine(this, blit); }

	void SetLightList(Int32 mode) { C4DOS.Br->SetLightList(this, mode); }
#define BDRAW_SETLIGHTLIST_NOLIGHTS			-1
#define BDRAW_SETLIGHTLIST_SCENELIGHTS	0
#define BDRAW_SETLIGHTLIST_QUICKSHADING	1

	void InitUndo(BaseDocument* doc) { C4DOS.Br->InitUndo(this, doc); }
	void DoUndo(BaseDocument* doc) { C4DOS.Br->DoUndo(this, doc); }

	void SetDrawParam(Int32 id, const GeData& data) { C4DOS.Br->SetDrawParam(this, id, data); }
	GeData GetDrawParam(Int32 id) { return C4DOS.Br->GetDrawParam(this, id); }
#define DRAW_PARAMETER_LINEWIDTH				1000	// [SET/GET] Float LineWidth
#define DRAW_PARAMETER_ALPHA_THRESHOLD	1002	// [SET/GET] Float 0 ... 1.0 (make sure to set old value after change!
#define DRAW_PARAMETER_SETZ							2
	#define DRAW_Z_LOWEREQUAL	0
	#define DRAW_Z_GREATER		1
	#define DRAW_Z_ALWAYS			2
	#define DRAW_Z_EQUAL			3
	#define DRAW_Z_LOWER			4
#define DRAW_PARAMETER_OGL_CULLING			10
	#define DRAW_PARAMETER_OGL_CULLING_OFF				0
	#define DRAW_PARAMETER_OGL_CULLING_FRONT			1
	#define DRAW_PARAMETER_OGL_CULLING_BACK				2
	#define DRAW_PARAMETER_OGL_CULLING_FRONT_AND_BACK 3
#define DRAW_PARAMETER_USE_Z						11
#define DRAW_PARAMETER_OGL_PRIMITIVERESTARTINDEX	14 //UInt16

	// use with BASEDRAW_DRAWPORTTYPE
#define DRAWPORT_TYPE_SOFTWARE 0
	//#define DRAWPORT_TYPE_OGL								1
#define DRAWPORT_TYPE_OGL_HQ 2

	Bool TestBreak() { return C4DOS.Br->TestBreak(this); }
	OITInfo& GetOITInfo() { return C4DOS.Br->GetOITInfo(this); }
	Bool GetFullscreenPolygonVectors(Int32& lAttributeCount, const GlVertexBufferAttributeInfo* const*& ppAttibuteInfo, Int32& lVectorInfoCount, const GlVertexBufferVectorInfo* const*& ppVectorInfo)
	{ return C4DOS.Br->GetFullscreenPolygonVectors(this, lAttributeCount, ppAttibuteInfo, lVectorInfoCount, ppVectorInfo); }
	Bool DrawFullscreenPolygon(Int32 lVectorInfoCount, const GlVertexBufferVectorInfo* const* ppVectorInfo)
	{ return C4DOS.Br->DrawFullscreenPolygon(this, lVectorInfoCount, ppVectorInfo); }
	Int32 GetGlLightCount() const { return C4DOS.Br->GetGlLightCount(this); }
	const GlLight* GetGlLight(Int32 lIndex) const { return C4DOS.Br->GetGlLight(this, lIndex); }
	Bool GetDrawStatistics(BaseContainer& bc) const { return C4DOS.Br->GetDrawStatistics(this, bc); }
	DRAWPASS GetDrawPass() const { return C4DOS.Br->GetDrawPass(this); }

	const Matrix4d& GetViewMatrix(Int32 n);

	EditorWindow* GetEditorWindow()  { return C4DOS.Br->GetEditorWindow(this); }
	void SetTexture(BaseBitmap* bm, Bool tile, DRAW_ALPHA alphamode, DRAW_TEXTUREFLAGS flags) { return C4DOS.Br->SetTexture(this, bm, tile, alphamode, flags); }
	void OverrideCamera(StereoCameraInfo* si) { C4DOS.Bv->OverrideCamera(this, si); }

	void GetGridStep(Float& step, Float& fade) { C4DOS.Br->GetGridStep(this, step, fade); }
};

struct ViewportPixel
{
	BaseObject*		 op;		// the object
	Float					 z;			// z coordinate of current element
	Int32					 i;			// element index (may be point, polygon, edge (4*polygon+edge) or spline point (segment offset + point))
	ViewportPixel* next;	// next element
};

#define VIEWPORT_CLEAR_POINT	 1
#define VIEWPORT_CLEAR_POLYGON 2
#define VIEWPORT_CLEAR_EDGE		 4

class ViewportSelect
{
private:
	ViewportSelect();
	~ViewportSelect();

public:
	static ViewportSelect* Alloc();
	static void Free(ViewportSelect*& p);

	static Bool PickObject(BaseDraw* bd, BaseDocument* doc, Int32 x, Int32 y, Int32 rad, VIEWPORT_PICK_FLAGS flags, LassoSelection* ls, C4DObjectList* list, Matrix4d* m = nullptr);
	// the i member of ViewportPixel is unused; x1, x2, y1 and y2 are inclusive; VIEWPORT_PICK_FLAGS_ALLOW_OGL must be set
	static Bool PickObject(BaseDraw* bd, BaseDocument* doc, Int32 x, Int32 y, Int32 rad, Int32& xr, Int32& yr, Int32& wr, Int32& hr, ViewportPixel**& pixels, VIEWPORT_PICK_FLAGS flags, LassoSelection* ls, C4DObjectList* list, Matrix4d* m = nullptr);
	static Bool PickObject(BaseDraw* bd, BaseDocument* doc, Int32 x1, Int32 y1, Int32 x2, Int32 y2, Int32& xr, Int32& yr, Int32& wr, Int32& hr, ViewportPixel**& pixels, VIEWPORT_PICK_FLAGS flags, LassoSelection* ls, C4DObjectList* list, Matrix4d* m = nullptr);

	Bool Init(Int32 w, Int32 h, BaseDraw* bd, BaseObject* op, Int32 mode, Bool onlyvisible, VIEWPORTSELECTFLAGS flags = VIEWPORTSELECTFLAGS_0);
	Bool Init(Int32 w, Int32 h, BaseDraw* bd, AtomArray* ar, Int32 mode, Bool onlyvisible, VIEWPORTSELECTFLAGS flags = VIEWPORTSELECTFLAGS_0);

	ViewportPixel* GetPixelInfoPoint(Int32 x, Int32 y);
	ViewportPixel* GetPixelInfoPolygon(Int32 x, Int32 y);
	ViewportPixel* GetPixelInfoEdge(Int32 x, Int32 y);
	ViewportPixel* GetNearestPoint(BaseObject* op, Int32& x, Int32& y, Int32 maxrad = LIMIT<Int32>::MAX, Bool onlyselected = false, Int32* ignorelist = nullptr, Int32 ignorecnt = 0);
	ViewportPixel* GetNearestPolygon(BaseObject* op, Int32& x, Int32& y, Int32 maxrad = LIMIT<Int32>::MAX, Bool onlyselected = false, Int32* ignorelist = nullptr, Int32 ignorecnt = 0);
	ViewportPixel* GetNearestEdge(BaseObject* op, Int32& x, Int32& y, Int32 maxrad = LIMIT<Int32>::MAX, Bool onlyselected = false, Int32* ignorelist = nullptr, Int32 ignorecnt = 0);

	// points must be in camera space
	Bool DrawPolygon(const Vector* p, Int32 ptcnt, Int32 i, BaseObject* op, Bool onlyvisible = -1);
	Bool DrawHandle(const Vector& p, Int32 i, BaseObject* op, Bool onlyvisible = -1);

	void ShowHotspot(EditorWindow* bw, Int32 x, Int32 y);
	void SetBrushRadius(Int32 r);
	static void ShowHotspot(EditorWindow* bw, Int32 x, Int32 y, Int32 rad, Bool bRemove);
	void ClearPixelInfo(Int32 x, Int32 y, UChar mask);
	Bool GetCameraCoordinates(Float x, Float y, Float z, Vector& v);
};

#endif
