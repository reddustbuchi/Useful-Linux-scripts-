/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _CUSTOMGUI_SPLINE_H_
#define _CUSTOMGUI_SPLINE_H_

#include "customgui_base.h"
#include "c4d_customdatatype.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"


#define CUSTOMGUI_SPLINE        1009059
#define CUSTOMDATATYPE_SPLINE   1009060
#define ID_SPLINEGUI_BROWSERPRESET	1027658
#define ID_SPLINEGUI_POPUPDIALOG		1027659

class SplineCustomGui;
typedef Bool (*SplineDataCallback)(Int32 id, const void* d);

#define SPLINE_CALLBACK_DRAW					0
#define SPLINE_CALLBACK_CURSORINFO		1
#define SPLINE_CALLBACK_CORE_MESSAGE	2

#ifndef _INTERNAL_DEF_
#define IDC_SPLINE_PRESET_POPUPMENU		1023
#define IDC_SPLINE_FRAME_ALL					900016
#define IDC_SPLINE_FRAME_SEL					900017
#define IDC_SPLINE_FRAME_MINMAX				900023
#endif

struct SplineDataCallbackDraw
{
	void* pCallbackData;						// data that you passed to SetUserCallback
	SplineCustomGui* pGUI;					// Spline custom GUI custom gui that shows the spline
	GeUserArea* pUserArea;					// its user area
	const BaseContainer* pObjects;	// an array of links that hold the objects
	const DescID* pDescID;					// the DescID of the spline GUI
	const BaseContainer* pDrawMsg;	// the container that was originally passed to ::DrawMsg
	GeClipMap* pClipmap;						// the clipmap where you can draw to
};

struct SplineDataCallbackCursorInfo
{
	void* pCallbackData;						// data that you passed to SetUserCallback
	SplineCustomGui* pGUI;					// Spline custom GUI custom gui that shows the spline
	GeUserArea* pUserArea;					// its user area
	const BaseContainer* pObjects;	// an array of links that hold the objects
	const DescID* pDescID;					// the DescID of the spline GUI
	Int32 x, y;											// cursor position in local space
};

struct SplineDataCallbackCoreMessage
{
	void* pCallbackData;						// data that you passed to SetUserCallback
	SplineCustomGui* pGUI;					// Spline custom GUI custom gui that shows the spline
	GeUserArea* pUserArea;					// its user area
	const BaseContainer* pObjects;	// an array of links that hold the objects
	const DescID* pDescID;					// the DescID of the spline GUI
	Int32 lID;												// message ID
	const BaseContainer* pMessage;	// the original container
};

enum
{
	SPLINECONTROL_GRID_H          = 10000,   // shows the horizontal grid
	SPLINECONTROL_GRID_V,                    // shows the vertical grid
	SPLINECONTROL_VALUE_EDIT_H,              // show X edit box
	SPLINECONTROL_VALUE_EDIT_V,              // show Y edit box
	SPLINECONTROL_VALUE_LABELS_H,            // show labels on the X axis
	SPLINECONTROL_VALUE_LABELS_V,            // show labels on the Y axis
	SPLINECONTROL_X_MIN,                     // min. X
	SPLINECONTROL_X_MAX,                     // max. X
	SPLINECONTROL_X_STEPS,                   // X steps (for the edit box)
	SPLINECONTROL_Y_MIN,                     // min. Y
	SPLINECONTROL_Y_MAX,                     // max. Y
	SPLINECONTROL_Y_STEPS,                   // Y steps (for the edit box)
	SPLINECONTROL_PRESET_BTN,                // has preset button
	SPLINECONTROL_ROUND_SLIDER,              // has tension slider
	SPLINECONTROL_GRIDLINES_H,               // number of horizontal grid lines
	SPLINECONTROL_GRIDLINES_V,               // number of vertical grid lines
	SPLINECONTROL_MINSIZE_H,                 // minimal horizontal size
	SPLINECONTROL_MINSIZE_V,                 // minimal vertical size
	SPLINECONTROL_X_MIN_TEXT,                // xmin label text
	SPLINECONTROL_X_MAX_TEXT,                // xmax label text
	SPLINECONTROL_Y_MIN_TEXT,                // xmin label text
	SPLINECONTROL_Y_MAX_TEXT,                // xmax label text
	SPLINECONTROL_X_TEXT,                    // x label text
	SPLINECONTROL_Y_TEXT,                    // y label text
	SPLINECONTROL_NEW_NO_HORIZ,              // new knots can't be moved horizontally
	SPLINECONTROL_NEW_NO_VERT,               // new knots can't be moved vertically

	SPLINECONTROL_HIDE_GRID_H,               // hide the horizontal grid
	SPLINECONTROL_HIDE_GRID_V,               // hide the vertical grid
	SPLINECONTROL_HIDE_PRESET_BTN,           // hide preset button
	SPLINECONTROL_HIDE_ROUND_SLIDER,         // hide tension slider
	SPLINECONTROL_HIDE_VALUE_EDIT_H,         // hide X edit box
	SPLINECONTROL_HIDE_VALUE_EDIT_V,         // hide Y edit box
	SPLINECONTROL_HIDE_VALUE_LABELS_H,       // hide labels on the X axis
	SPLINECONTROL_HIDE_VALUE_LABELS_V,       // hide labels on the Y axis

	SPLINECONTROL_ALLOW_HORIZ_SCALE_MOVE,    // allow horizontal scale and move
	SPLINECONTROL_ALLOW_VERT_SCALE_MOVE,     // allow vertical scale and move

	SPLINECONTROL_OPTIMAL, //use optimal area
	SPLINECONTROL_OPTIMAL_X_MIN, //optimal x min
	SPLINECONTROL_OPTIMAL_Y_MIN, //optimal y min
	SPLINECONTROL_OPTIMAL_X_MAX, //optimal x max
	SPLINECONTROL_OPTIMAL_Y_MAX, //optimal y max

	SPLINECONTROL_SQUARE,

	SPLINECONTROL_CUSTOMCOLOR_SET,
	SPLINECONTROL_CUSTOMCOLOR_COL,

	SPLINECONTROL_NO_FLOATING_WINDOW,
	SPLINECONTROL_NO_PRESETS,

	_SPLINECONTROL_DUMMY_
};

#define FLAG_KNOT_T_BREAK							(1<<4)
#define FLAG_KNOT_LOCK_X							(1<<5)
#define FLAG_KNOT_LOCK_Y							(1<<6)
#define FLAG_KNOT_T_LOCK_A							(1<<7)
#define FLAG_KNOT_T_LOCK_L							(1<<8)
#define FLAG_KNOT_T_KEEPVISUALANGLE							(1<<9)
#define ADD_KNOT_ADAPT_TANGENTS					(1 << 16)

#define SPLINE_KNOT_GET_ID(flags)          ((flags >> 16) & 0x0000ffff)
#define SPLINE_KNOT_SET_ID(flags, flag_id) (flags = (flags & 65535) | ((flag_id & 0x0000ffff) << 16))

enum CustomSplineKnotInterpolation { CustomSplineKnotInterpolationBezier, CustomSplineKnotInterpolationLinear, CustomSplineKnotInterpolationCubic };
struct CustomSplineKnot
{
	CustomSplineKnot()
	{
		bSelect = false;
		interpol = CustomSplineKnotInterpolationBezier;
	}

	Vector vPos;
	Int32 lFlagsSettings; // the upper 16 bits are used for the point index - do not modify these bits
	Bool bSelect; // internal select state - DO NOT USE
	Vector vTangentLeft, vTangentRight;
	CustomSplineKnotInterpolation interpol;

	Bool operator == (CustomSplineKnot& k);
	Bool operator != (CustomSplineKnot& k);
};

enum
{
	SPLINE_TYPE_SOFT = 0,
	SPLINE_TYPE_EASEIN,
	SPLINE_TYPE_EASEOUT,
	SPLINE_TYPE_EASEEASE,
	SPLINE_TYPE_ZERO,
	SPLINE_TYPE_UNIFY
};

class SplineData : public CustomDataType
{
private:
	SplineData();
	~SplineData();
public:
	static SplineData* Alloc();
	static void Free(SplineData *&pData);

	Int32 GetKnotCount() const;
	CustomSplineKnot* GetKnot(Int32 l);
	Bool SetKnot(Int32 l, const CustomSplineKnot& knot);

	Vector GetPoint(Float r) const;

	void DeleteAllPoints();
	Bool MakePointBuffer(Int32 lPoints = -1);

	Bool MakeLinearSplineLinear(Int32 lPoints = -1);
	Bool MakeLinearSplineBezier(Int32 lPoints = -1);
	Bool MakeSquareSpline(Int32 lPoints = -1);
	Bool MakeCubicSpline(Int32 lPoints = -1);
	Bool MakeRootSpline(Int32 lPoints = -1);
	Bool MakeInversSpline(Int32 lPoints = -1);
	Bool MakeSinSpline(Int32 lPoints = -1);
	Bool MakeAbsCosSpline(Int32 lPoints = -1);
	Bool MakeUserSpline(const String &str, Int32 lPoints = -1);

	void SelectAll();
	void Flip();
	void Mirror();
	void Maximum();
	void Minimum();

	Bool SetZero(Bool bY, Bool bAll = false);
	Bool SetType(Int32 id, Bool bAll = false);
	Bool InitDefaultFlag(Int32 flag);

	void SortKnots(Int32 &lActiveKnot);
	Int32 GetSelectCount() const;
// 	Bool SetBackgoundImage(BaseBitmap* pBmp);
// 	BaseBitmap* GetBackgroundImage();

	// only used if the spline is shown in the spline gui
	Bool GetRange(Float* xmin, Float* xmax, Float* xsteps, Float* ymin, Float* ymax, Float* ysteps) const; // returns false if no values were set before
	void SetRange(Float xmin, Float xmax, Float xsteps, Float ymin, Float ymax, Float ysteps);
	void AdaptRange(Float xmin, Float xmax, Float xsteps, Float ymin, Float ymax, Float ysteps);

	Int32 InsertKnot(Float x, Float y, Int32 lFlags = 0);
	Bool DeleteKnot(Int32 a);

	SplineDataCallback GetUserCallback(void *&pData) const;
	void SetUserCallback(SplineDataCallback fn, void* pData);
	Bool CopyTo(SplineData* pDest);

};

class SplineControlMessages
{
public:
	virtual void KnotMoved(Float x, Float y) { }
	virtual void KnotInserted(Int32 lKnot, Float x, Float y) { }
	virtual void LeftTangentMoved(Float x, Float y) { }
	virtual void RightTangentMoved(Float x, Float y) { }
};

class SplineCustomGui : public BaseCustomGui<CUSTOMGUI_SPLINE>
{
	SplineCustomGui();
	~SplineCustomGui();

public:
	void SetMessageFunctions(SplineControlMessages* pFuncs);

	SplineData* GetSplineData(void);
	Bool SetSpline(SplineData* pData);
	void SetGridLineCountH(Int32 l);
	void SetGridLineCountV(Int32 l);
	Int32 GetGridLineCountH() const;
	Int32 GetGridLineCountV() const;
	void SetLabelText(String* strXMin = nullptr, String* strXMax = nullptr, String* strYMin = nullptr, String* strYMax = nullptr, String* strX = nullptr, String* strY = nullptr);
	void SetCustomColor(Bool bSet= false, Vector col = Vector(0.0,0.0,0.0));
	void GetScreenPosition(const Vector &v, Int32 &x, Int32 &y) const;
	void GetValue(const Int32 x, const Int32 y, Vector &v) const;
	Bool Command(Int32 id,const BaseContainer &msg);
};



// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

class SplineControlMessagesF
{
public:
	// version 0
	void KnotMoved(SplineControlMessages* pFuncs, Float x, Float y);
	void KnotInserted(SplineControlMessages* pFuncs, Int32 l, Float x, Float y);
	// version 1
	void LeftTangentMoved(SplineControlMessages* pFuncs, Float x, Float y);
	void RightTangentMoved(SplineControlMessages* pFuncs, Float x, Float y);
};

struct SplineControlFunctionTable
{
	// spline control version 0
	void    (SplineControlMessagesF::*KnotMoved)(SplineControlMessages* pFuncs, Float x, Float y);
	void    (SplineControlMessagesF::*KnotInserted)(SplineControlMessages* pFuncs, Int32 l, Float x, Float y);

	// version 1
	void    (SplineControlMessagesF::*LeftTangentMoved)(SplineControlMessages* pFuncs, Float x, Float y);
	void    (SplineControlMessagesF::*RightTangentMoved)(SplineControlMessages* pFuncs, Float x, Float y);

	void* dummy[(15 - 4) * C4DPL_MEMBERMULTIPLIER];
};

#ifndef _INTERNAL_DEF_
	class iSplineCustomGui
	{
	};
	class iSpline
	{
	};
#else
	class iSplineCustomGui;
	class iSpline;
#endif

struct CustomGuiSplineLib : public BaseCustomGuiLib
{
	Int32              (iSpline::*GetKnotCount)() const;
	CustomSplineKnot* (iSpline::*GetKnot)(Int32 l);

	Vector            (iSpline::*GetPoint)(Float r) const;
	Vector            (iSpline::*GetPointFromX)(Float r, Int32 lMaxIter, Float rMaxEps) const;

	void              (iSpline::*DeleteAllPoints)();
	Bool              (iSpline::*MakePointBuffer)(Int32 lPoints);

	Bool              (iSpline::*MakeLinearSplineBezier)(Int32 lPoints);
	Bool              (iSpline::*MakeSquareSpline)(Int32 lPoints);
	Bool              (iSpline::*MakeCubicSpline)(Int32 lPoints);
	Bool              (iSpline::*MakeRootSpline)(Int32 lPoints);
	Bool              (iSpline::*MakeInversSpline)(Int32 lPoints);
	Bool              (iSpline::*MakeSinSpline)(Int32 lPoints);
	Bool              (iSpline::*MakeAbsCosSpline)(Int32 lPoints);


	void              (iSpline::*Flip)();
	void              (iSpline::*Mirror)();
	void              (iSpline::*Maximum)();
	void              (iSpline::*Minimum)();

	void              (iSpline::*SetRoundEx)(Float r);
	Float              (iSpline::*GetRoundEx)() const;
	void              (iSpline::*SortKnots)(Int32 &lActiveKnot);

	Int32              (iSpline::*InsertKnot)(Float x, Float y, Int32 lFlags);
	Bool              (iSpline::*DeleteKnot)(Int32 a);
	Int32              (iSpline::*GetSelectCount)() const;

	void          (iSplineCustomGui::*SetMessageFunctions)(SplineControlFunctionTable* f, Int32 lSize, SplineControlMessagesF *pControl, SplineControlMessages* pFunctions);
	SplineData*   (iSplineCustomGui::*GetSplineData)(void);
	Bool          (iSplineCustomGui::*SetSpline)(SplineData* pData);
	void          (iSplineCustomGui::*SetGridLineCountH)(Int32 l);
	void          (iSplineCustomGui::*SetGridLineCountV)(Int32 l);
	Int32          (iSplineCustomGui::*GetGridLineCountH)() const;
	Int32          (iSplineCustomGui::*GetGridLineCountV)() const;
	void          (iSplineCustomGui::*SetLabelText)(String* strXMin, String* strXMax, String* strYMin, String* strYMax, String* strX, String* strY);

	Bool          (iSpline::*GetRange)(Float* xmin, Float* xmax, Float* xsteps, Float* ymin, Float* ymax, Float* ysteps) const;
	void          (iSpline::*SetRange)(Float xmin, Float xmax, Float xsteps, Float ymin, Float ymax, Float ysteps);

	SplineData*   (*Spline_Alloc)();
	void          (*Spline_Free)(SplineData *&pData);
	void          (iSpline::*SelectAll)();
	Bool          (iSpline::*MakeUserSpline)(const String &str, Int32 lPoints);
// 	BaseBitmap*   (iSpline::*GetBackgroundImage)() const;
// 	Bool          (iSpline::*SetBackgoundImage)(BaseBitmap* pBmp);
	Bool          (iSpline::*SetZero)(Bool bY, Bool bAll);
	Bool          (iSpline::*SetType)(Int32 id, Bool bAll);
	Bool          (iSpline::*MakeLinearSplineLinear)(Int32 lPoints);
	void          (iSpline::*AdaptRange)(Float xmin, Float xmax, Float xsteps, Float ymin, Float ymax, Float ysteps);

	void          (iSpline::*SetUserCallback)(SplineDataCallback fn, void* pData);
	SplineDataCallback (iSpline::*GetUserCallback)(void *&pData) const;
	void					(iSplineCustomGui::*GetScreenPosition)(const Vector &v, Int32 &x, Int32 &y) const;
	void					(iSplineCustomGui::*GetValue)(const Int32 x, const Int32 y, Vector &v) const;

	Bool					(iSpline::*InitDefaultFlag)(Int32 flag);

	void          (iSplineCustomGui::*SetCustomColor)(Bool bSet, Vector col);
	Bool					(iSpline::*CopyTo)(SplineData* pDest);

	Bool					(iSplineCustomGui::*Command)(Int32 id,const BaseContainer &msg);
	Bool					(iSpline::*SetKnot)(Int32 l, const CustomSplineKnot& knot);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif
