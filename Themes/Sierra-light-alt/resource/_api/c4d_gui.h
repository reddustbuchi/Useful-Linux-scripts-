/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DGUI_H
#define __C4DGUI_H

#ifndef __API_INTERN__
	#include "ge_math.h"
	#include "c4d_string.h"
	#include "gui.h"
	#define IDC_OK		 1
	#define IDC_CANCEL 2
	#include "c4d_gedata.h"
	#include "c4d_thread.h"
enum
{
	FORMAT_FLOAT	 = 'frea',
	FORMAT_INT		 = 'flng',
	FORMAT_PERCENT = 'fpct',
	FORMAT_DEGREE	 = 'fdgr',
	FORMAT_METER	 = 'fmet',
	FORMAT_FRAMES	 = 'ffrm',
	FORMAT_SECONDS = 'fsec',
	FORMAT_SMPTE	 = 'fsmp'
};

#else
	#include "ge_math.h"
	#include "ge_string.h"
	#include "gui_defs.h"
	#include "gui_newdialog.h"
	#include "gui_coredefs.h"
	#include "c4d_basetime.h"
	#include "operatingsystem.h"
#endif

class BaseBitmap;
class BaseContainer;
class GeResource;
class Filename;
class SubDialog;
class BaseDocument;
class GeDialog;
struct CUSTOMGUIPLUGIN;

typedef UChar OBSOLETE;

// for popupcreation
#define FIRST_POPUP_ID (900000)

#define IDM_CM_CLOSEWINDOW 12097

#define MAXTIME	108000	// maximum time value equal 1.0 hours at 30fps //x2.77x hours!

#define COREMSG_CINEMA_GETCOMMANDNAME				200000033
#define COREMSG_CINEMA_GETCOMMANDENABLED		200000035
#define COREMSG_CINEMA_GETCOMMANDCHECKED		300000115
#define COREMSG_CINEMA_EXECUTEEDITORCOMMAND 200000023
#define COREMSG_CINEMA_EXECUTESUBID					300001036
#define COREMSG_CINEMA_EXECUTEOPTIONMODE		300001037
#define COREMSG_CINEMA_GETCOMMANDHELP				200000234

#define COREMSG_CINEMA_FORCE_AM_UPDATE 1001077	// CoreMesage: Force AM update
#define COREMSG_UPDATECOMMANDSMESSAGE	 200000100

#define C4DGUIPTR		(-1)
#define C4DGUINOPTR	(-2)

class C4DGadget
{
public:
};

class GadgetPtr
{
	Int32			 _id;
	C4DGadget* gad;

public:
	GadgetPtr(Int32 t_id) { _id = t_id; gad = nullptr; }
	GadgetPtr(C4DGadget* t_gad) { _id = C4DGUIPTR; gad = t_gad; }

	Int32 Id() const { return _id; };
	C4DGadget* Ptr() const { return gad; }
};

class GeUserArea
{
	friend class GeDialog;

private:
	Bool			 owncu;
	CUserArea* cu;

protected:
	GeDialog* dlg;

public:
	GeUserArea(void);
	virtual ~GeUserArea(void);

	CUserArea* Get() { return cu; }
	void Set(CUserArea* t_cu) { cu = t_cu; owncu = true; }
	GeDialog* GetDialog(void) { return dlg; }

	// for overriding (for easy message handling)
	virtual Bool Init         (void);
	virtual Bool InitValues   (void);
	virtual Bool GetMinSize   (Int32& w, Int32& h);
	virtual void Sized        (Int32 w, Int32 h);
	virtual OBSOLETE Draw     (Int32 x1, Int32 y1, Int32 x2, Int32 y2);
	virtual void DrawMsg      (Int32 x1, Int32 y1, Int32 x2, Int32 y2, const BaseContainer& msg);
	virtual Bool InputEvent   (const BaseContainer& msg);
	virtual Bool CoreMessage  (Int32 id, const BaseContainer& msg);
	virtual void Timer        (const BaseContainer& msg);

	// for overriding (for special message handling)
	virtual Int32 Message      (const BaseContainer& msg, BaseContainer& result);

	// functions to call
	void Redraw               (Bool threaded = false);
	Bool SendParentMessage    (const BaseContainer& msg);

	Int32 GetId                (void);
	Int32 GetWidth             (void);
	Int32 GetHeight            (void);
	Bool IsEnabled						(void);
	Bool HasFocus							(void);

	// input events and tTimer
	void SetTimer             (Int32 timer);
	Bool GetInputState        (Int32 askdevice, Int32 askchannel, BaseContainer& res);
	Bool GetInputEvent        (Int32 askdevice, BaseContainer& res);
	void KillEvents           (void);
	Bool IsHotkeyDown					(Int32 id);

	// pens
	void DrawSetPen           (const Vector& color);
	void DrawSetPen           (Int32 id);
	void DrawSetPen           (const GeData& d);
	void DrawSetTextCol       (Int32 fg, Int32 bg);
	void DrawSetTextCol       (const Vector& fg, Int32 bg);
	void DrawSetTextCol       (Int32 fg, const Vector& bg);
	void DrawSetTextCol       (const Vector& fg, const Vector& bg);
	void DrawSetTextCol       (const GeData& fg, const GeData& bg);
	Bool GetColorRGB          (Int32 colorid, Int32& r, Int32& g, Int32& b);
	void ActivateFading				(Int32 milliseconds);
	void AdjustColor					(Int32 colorid, Int32 highlightid, Float percent);

	// draw functions
	void DrawLine             (Int32 x1, Int32 y1, Int32 x2, Int32 y2);
	void DrawRectangle        (Int32 x1, Int32 y1, Int32 x2, Int32 y2);
	void DrawBitmap           (BaseBitmap* bmp, Int32 wx, Int32 wy, Int32 ww, Int32 wh, Int32 x, Int32 y, Int32 w, Int32 h, Int32 mode);
#define	DRAWTEXT_HALIGN_LEFT	 0
#define	DRAWTEXT_HALIGN_CENTER 1
#define	DRAWTEXT_HALIGN_RIGHT	 2
#define	DRAWTEXT_HALIGN_MASK	 0x000f
#define	DRAWTEXT_VALIGN_TOP		 (0 << 4)
#define	DRAWTEXT_VALIGN_CENTER (1 << 4)
#define	DRAWTEXT_VALIGN_BOTTOM (2 << 4)
#define	DRAWTEXT_VALIGN_MASK	 0x00f0
#define	DRAWTEXT_STD_ALIGN		 (DRAWTEXT_HALIGN_LEFT | DRAWTEXT_VALIGN_TOP)
	void DrawText             (const String& txt, Int32 x, Int32 y, Int32 flags = DRAWTEXT_STD_ALIGN);
#define DRAWBEZIER_BX	0
#define DRAWBEZIER_BY	1
#define DRAWBEZIER_CX	2
#define DRAWBEZIER_CY	3
#define DRAWBEZIER_DX	4
#define DRAWBEZIER_DY	5
	void DrawBezier						(Float sx, Float sy, Float* p, Int32 len, Bool closed, Bool filled);
	void FillBitmapBackground (BaseBitmap* bmp, Int32 offsetx, Int32 offsety);

	// fonts
	void DrawSetFont          (Int32 fontid);
	Int32 DrawGetTextWidth     (const String& text);
	Int32 DrawGetTextWidth_ListNodeName(BaseList2D* node, Int32 fontid = FONT_STANDARD);
	Int32 DrawGetFontHeight    (void);
	Int32 DrawGetFontBaseLine	(void);
	void DrawSetTextRotation	(Float textrotation);	// degree, cw, dont forget to reset it to 0 afterwards

	// others
	void SetClippingRegion    (Int32 x, Int32 y, Int32 w, Int32 h);
	void ClearClippingRegion  (void);
	Bool OffScreenOn          (void);
	Bool OffScreenOn					(Int32 x, Int32 y, Int32 w, Int32 h);
	void ScrollArea           (Int32 xdiff, Int32 ydiff, Int32 x, Int32 y, Int32 w, Int32 h);

	Float GetPixelRatio        () const;
	Bool Local2Global         (Int32* x, Int32* y);
	Bool Global2Local         (Int32* x, Int32* y);
	Bool Local2Screen         (Int32* x, Int32* y);
	Bool Screen2Local         (Int32* x, Int32* y);

	void LayoutChanged        (void);

	Bool GetDragPosition      (const BaseContainer& msg, Int32* x, Int32* y);
	Bool GetDragObject        (const BaseContainer& msg, Int32* type, void** object);
	Bool HandleMouseDrag      (const BaseContainer& msg, Int32 type, void* data, Int32 dragflags);
	Bool SetDragDestination   (Int32 cursor);
	void GetBorderSize        (Int32 type, Int32* l, Int32* t, Int32* r, Int32* b);
	void DrawBorder           (Int32 type, Int32 x1, Int32 y1, Int32 x2, Int32 y2);

#ifdef __API_INTERN__
	Bool OpenPopUpMenu				(Int32 menuid, Int32 localx, Int32 localy, Int32 watchhotkey);
#endif

	Bool CheckDropArea        (const BaseContainer& msg, Bool horiz, Bool vert);

	void MouseDragStart				(Int32 button, Float mx, Float my, MOUSEDRAGFLAGS flag);
	MOUSEDRAGRESULT MouseDrag	(Float* mx, Float* my, BaseContainer* channels);
	MOUSEDRAGRESULT MouseDragEnd(void);

	Bool IsR2L                (void);

#define MOUSEMOVE_DELTA_TABLET 6.0
#define MOUSEMOVE_DELTA_MOUSE	 2.0

	// LassoSelection is working with GeDialog & GeUserArea
};


template <class TYPE> class TriState
{
	Int32 tri;
	TYPE	value;

public:
	TriState()							{ tri = -1; value = TYPE(); }
	TriState(const TYPE& val) { tri = 0; value = val; }
	Bool GetTri() const	{ return tri == 1; }
	const TYPE& GetValue() const { return value; }
	Bool HasChanged() const { return tri != -1; }
	void Add(TYPE val)
	{
		if (tri == -1)
		{
			tri = 0;
			value = val;
		}
		else if (tri == 0 && value != val)
		{
			tri = 1;
		}
	}
	void Add(BaseContainer* bc, Int32 id);
	Int32 Check(GeDialog* dlg, const BaseContainer& msg, Int32 cid, Int32 gid);
	Int32 CheckVector(GeDialog* dlg, const BaseContainer& msg, Int32 current_id, Int32 gidx, Int32 gidy, Int32 gidz);
	Int32 CheckBaseTime(GeDialog* dlg, const BaseContainer& msg, BaseDocument* doc, Int32 cid, Int32 gid);
};

#define GUI_MAXRANGE	( 1.0e18)
#define GUI_MINRANGE	(-1.0e18)

class GeDialog
{
	friend class GeUserArea;
	friend class _GeListView;

private:
	CDialog* cd;
	Int32		 t_lastcoremsg;

protected:
	Bool createlayout;

public:
	GeDialog(void);
	virtual ~GeDialog(void);

	CDialog* Get() { return cd; }
#ifdef __API_INTERN__
	Bool dontfree;
	void Set(CDialog* set);
#endif

	// for overriding (for easy message handling)
	virtual Bool CreateLayout (void);
	virtual Bool InitValues   (void);
	virtual Bool CoreMessage  (Int32 id, const BaseContainer& msg);
	virtual Bool Command      (Int32 id, const BaseContainer& msg);
	virtual Bool AskClose     (void);
	virtual void Timer        (const BaseContainer& msg);
	virtual void DestroyWindow(void);	// use this function to set all pointers to userareas/customgui elements to nullptr

	// for overriding (for special message handling)
	virtual Int32 Message      (const BaseContainer& msg, BaseContainer& result);

	// functions to call
	Bool Open                 (DLG_TYPE dlgtype, Int32 pluginid, Int32 xpos = -1, Int32 ypos = -1, Int32 defaultw = 0, Int32 defaulth = 0, Int32 subid = 0);
	Bool Close                (void);
	Bool Close                (Bool dummy);
	GeData SendMessage        (const GadgetPtr& id, const BaseContainer& msg);
	Bool SendParentMessage    (const BaseContainer& msg);
	Int32 GetId                (void);
	Bool IsOpen								();
	Bool IsVisible						();

	void SetTimer             (Int32 timer);
	void SetTitle							(const String& title);

	Bool GetInputState				(Int32 askdevice, Int32 askchannel, BaseContainer& res);
	Bool GetInputEvent				(Int32 askdevice, BaseContainer& res);
	void KillEvents						(void);

	// set/get functions
	Bool Enable               (const GadgetPtr& id, Bool enabled);
	Bool IsEnabled            (const GadgetPtr& id);
	Bool SetBool              (const GadgetPtr& id, Bool value, Int32 tristate = 0);
	Bool SetInt32             (const GadgetPtr& id, Int32 value, Int32 min = LIMIT<Int32>::MIN, Int32 max = LIMIT<Int32>::MAX, Int32 step = 1, Int32 tristate = 0, Int32 min2 = LIMIT<Int32>::MIN, Int32 max2 = LIMIT<Int32>::MAX);
	Bool SetFloat             (const GadgetPtr& id, Float value, Float min = GUI_MINRANGE, Float max = GUI_MAXRANGE, Float step = 1.0, Int32 format = FORMAT_FLOAT, Float min2 = 0.0, Float max2 = 0.0, Bool quadscale = false, Int32 tristate = 0);
	Bool SetMeter             (const GadgetPtr& id, Float value, Float min = GUI_MINRANGE, Float max = GUI_MAXRANGE, Float step = 1.0, Int32 tristate = 0);
	Bool SetDegree            (const GadgetPtr& id, Float radians_value, Float min = GUI_MINRANGE, Float max = GUI_MAXRANGE, Float step = 1.0, Int32 tristate = 0);
	Bool SetPercent           (const GadgetPtr& id, Float value, Float min = 0.0, Float max = 100.0, Float step = 1.0, Int32 tristate = 0);
	Bool SetTime							(const GadgetPtr& id, const BaseDocument* doc, const BaseTime& value, const BaseTime& min = BaseTime(-MAXTIME, 1), const BaseTime& max = BaseTime(MAXTIME, 1), Int32 stepframes = 1, Int32 tristate = 0);
	Bool SetString            (const GadgetPtr& id, const String& text, Int32 tristate = 0, Int32 flags = 0);
	Bool SetColorField        (const GadgetPtr& id, const Vector& color, Float brightness, Float maxbrightness, Int32 flags);
	Bool SetFilename          (const GadgetPtr& id, const Filename& fn, Int32 tristate = 0);

	Bool GetBool              (const GadgetPtr& id, Bool& value) const;
	Bool GetInt32              (const GadgetPtr& id, Int32& value) const;
	Bool GetFloat              (const GadgetPtr& id, Float& value) const;
	Bool GetVector            (const GadgetPtr& id_x, const GadgetPtr& id_y, const GadgetPtr& id_z, Vector& value) const;
	Bool GetString            (const GadgetPtr& id, String& text) const;
	Bool GetColorField        (const GadgetPtr& id, Vector& color, Float& brightness) const;
	Bool GetTime							(const GadgetPtr& id, const BaseDocument* doc, BaseTime& time) const;
	Bool GetFilename          (const GadgetPtr& id, Filename& fn) const;

	Bool CheckTristateChange	(const GadgetPtr& id);	// return wheter the gadget content has been changed since the last SetXXX or not

	// container set/get functions
	Bool SetBool              (const GadgetPtr& id, const BaseContainer* bc, Int32 bcid);
	Bool SetInt32              (const GadgetPtr& id, const BaseContainer* bc, Int32 bcid, Int32 min = LIMIT<Int32>::MIN, Int32 max = LIMIT<Int32>::MAX, Int32 step = 1, Int32 min2 = LIMIT<Int32>::MIN, Int32 max2 = LIMIT<Int32>::MAX);
	Bool SetFloat              (const GadgetPtr& id, const BaseContainer* bc, Int32 bcid, Float min = GUI_MINRANGE, Float max = GUI_MAXRANGE, Float step = 1.0, Int32 format = FORMAT_FLOAT, Float min2 = 0.0, Float max2 = 0.0, Bool quadscale = false);
	Bool SetMeter             (const GadgetPtr& id, const BaseContainer* bc, Int32 bcid, Float min = GUI_MINRANGE, Float max = GUI_MAXRANGE, Float step = 1.0);
	Bool SetDegree            (const GadgetPtr& id, const BaseContainer* bc, Int32 bcid, Float min = GUI_MINRANGE, Float max = GUI_MAXRANGE, Float step = 1.0);
	Bool SetPercent           (const GadgetPtr& id, const BaseContainer* bc, Int32 bcid, Float min = 0.0, Float max = 100.0, Float step = 1.0);
	Bool SetTime							(const GadgetPtr& id, const BaseDocument* doc, const BaseContainer* bc, Int32 bcid, const BaseTime& min = BaseTime(-MAXTIME, 1), const BaseTime& max = BaseTime(MAXTIME, 1), Int32 stepframes = 1);

	Bool SetString            (const GadgetPtr& id, const BaseContainer* bc, Int32 bcid, Int32 flags = 0);
	Bool SetFilename          (const GadgetPtr& id, const BaseContainer* bc, Int32 bcid);
	Bool SetColorField        (const GadgetPtr& id, const BaseContainer* bc, Int32 bc_colid, Int32 bc_brightnessid, Float maxbrightness, Int32 flags);

	Bool GetBool              (const GadgetPtr& id, BaseContainer* bc, Int32 bcid) const;
	Bool GetInt32              (const GadgetPtr& id, BaseContainer* bc, Int32 bcid) const;
	Bool GetFloat              (const GadgetPtr& id, BaseContainer* bc, Int32 bcid) const;
	Bool GetTime							(const GadgetPtr& id, const BaseDocument* doc, BaseContainer* bc, Int32 bcid) const;
	Bool GetVector            (const GadgetPtr& id_x, const GadgetPtr& id_y, const GadgetPtr& id_z, BaseContainer* bc, Int32 bcid) const;
	Bool GetString            (const GadgetPtr& id, BaseContainer* bc, Int32 bcid) const;
	Bool GetFilename          (const GadgetPtr& id, BaseContainer* bc, Int32 bcid) const;
	Bool GetColorField        (const GadgetPtr& id, BaseContainer* bc, Int32 bc_colid, Int32 bc_brightnessid) const;

	// set/get functions for tristates
	Bool SetBool              (const GadgetPtr& id, const TriState<Bool>& tri);
	Bool SetInt32              (const GadgetPtr& id, const TriState<Int32>& tri, Int32 min = LIMIT<Int32>::MIN, Int32 max = LIMIT<Int32>::MAX, Int32 step = 1, Int32 min2 = LIMIT<Int32>::MIN, Int32 max2 = LIMIT<Int32>::MAX);
	Bool SetFloat              (const GadgetPtr& id, const TriState<Float>& tri, Float min = GUI_MINRANGE, Float max = GUI_MAXRANGE, Float step = 1.0, Int32 format = FORMAT_FLOAT, Float min2 = 0.0, Float max2 = 0.0, Bool quadscale = false);
	Bool SetMeter             (const GadgetPtr& id, const TriState<Float>& tri, Float min = GUI_MINRANGE, Float max = GUI_MAXRANGE, Float step = 1.0);
	Bool SetDegree            (const GadgetPtr& id, const TriState<Float>& tri, Float min = GUI_MINRANGE, Float max = GUI_MAXRANGE, Float step = 1.0);
	Bool SetPercent           (const GadgetPtr& id, const TriState<Float>& tri, Float min = 0.0, Float max = 100.0, Float step = 1.0);
	Bool SetTime							(const GadgetPtr& id, const BaseDocument* doc, const TriState<BaseTime>& tri, const BaseTime& min = BaseTime(-MAXTIME, 1), const BaseTime& max = BaseTime(MAXTIME, 1), Int32 stepframes = 1);
	Bool SetString            (const GadgetPtr& id, const TriState<String>& tri, Int32 flags = 0);
#define FLAG_CENTER_HORIZ	1
#define FLAG_CENTER_VERT	2
#define FLAG_ALIGN_RIGHT	4
	Bool SetMultiLinePos			(const GadgetPtr& id, Int32 line, Int32 pos);

	Bool SetColorField        (const GadgetPtr& id, const TriState<Vector>& tri, Float brightness, Float maxbrightness, Int32 flags);

	Bool CheckValueRanges     (void);

	Float GetPixelRatio        () const;

	Bool Local2Global         (Int32* x, Int32* y);
	Bool Global2Local         (Int32* x, Int32* y);
	Bool Screen2Local					(Int32* x, Int32* y);
	Bool Local2Screen					(Int32* x, Int32* y);
	Bool GetColorRGB          (Int32 colorid, Int32& r, Int32& g, Int32& b);
	void SetDefaultColor			(const GadgetPtr& id, Int32 colorid, Int32 mapid);
	void SetDefaultColor			(const GadgetPtr& id, Int32 colorid, const Vector& color);

	// layout stuff
	Bool LoadDialogResource   (Int32 id, GeResource* lr, Int32 flags);

	C4DGadget* AddCheckbox          (Int32 id, Int32 flags, Int32 initw, Int32 inith, const String& name);
	C4DGadget* AddButton            (Int32 id, Int32 flags, Int32 initw, Int32 inith, const String& name);
	C4DGadget* AddStaticText        (Int32 id, Int32 flags, Int32 initw, Int32 inith, const String& name, Int32 borderstyle);
	C4DGadget* AddArrowButton       (Int32 id, Int32 flags, Int32 initw, Int32 inith, Int32 arrowtype);
	C4DGadget* AddEditText          (Int32 id, Int32 flags, Int32 initw = 0, Int32 inith = 0, Int32 editflags = 0);
	C4DGadget* AddMultiLineEditText (Int32 id, Int32 flags, Int32 initw = 0, Int32 inith = 0, Int32 style = 0);
	C4DGadget* AddEditNumber        (Int32 id, Int32 flags, Int32 initw = 80, Int32 inith = 0);
	C4DGadget* AddEditNumberArrows  (Int32 id, Int32 flags, Int32 initw = 70, Int32 inith = 0);
	C4DGadget* AddEditSlider        (Int32 id, Int32 flags, Int32 initw = 80, Int32 inith = 0);
	C4DGadget* AddSlider            (Int32 id, Int32 flags, Int32 initw = 90, Int32 inith = 0);
	C4DGadget* AddColorField        (Int32 id, Int32 flags, Int32 initw = 0, Int32 inith = 0, Int32 colorflags = 0/*DR_COLORFIELD_ICC_xxxx*/);
	C4DGadget* AddColorChooser      (Int32 id, Int32 flags, Int32 initw = 0, Int32 inith = 0, Int32 layoutflags = 0);
	C4DGadget* AddRadioButton				(Int32 id, Int32 flags, Int32 initw, Int32 inith, const String& name);
	C4DGadget* AddRadioText					(Int32 id, Int32 flags, Int32 initw, Int32 inith, const String& name);
	C4DGadget* AddEditShortcut      (Int32 id, Int32 flags, Int32 initw = 0, Int32 inith = 0, Int32 shortcutflags = 0);

	C4DGadget* AddSeparatorH        (Int32 initw, Int32 flags = BFH_FIT);
	C4DGadget* AddSeparatorV        (Int32 inith, Int32 flags = BFV_FIT);

	Bool AddRadioGroup							(Int32 id, Int32 flags, Int32 columns = 1, Int32 rows = 0);
	C4DGadget* AddComboBox          (Int32 id, Int32 flags, Int32 initw = 0, Int32 inith = 0, Bool specialalign = false);
	C4DGadget* AddComboButton				(Int32 id, Int32 flags, Int32 initw = 0, Int32 inith = 0, Bool specialalign = false);
	C4DGadget* AddPopupButton				(Int32 id, Int32 flags, Int32 initw = 0, Int32 inith = 0);
	Bool AddListView								(Int32 id, Int32 flags, Int32 initw = 0, Int32 inith = 0);

	Bool AddChild             (const GadgetPtr& id, Int32 subid, const String& child);
	Bool FreeChildren         (const GadgetPtr& id);
	Bool SetPopup							(const GadgetPtr& id, const BaseContainer& bc);
	Bool AddChildren					(const GadgetPtr& id, const BaseContainer& bc);

	C4DGadget* AddUserArea          (Int32 id, Int32 flags, Int32 initw = 0, Int32 inith = 0);
	Bool AttachUserArea							(GeUserArea& ua, const GadgetPtr& id, USERAREAFLAGS userareaflags = USERAREA_COREMESSAGE);

	Bool AddSubDialog					(Int32 id, Int32 flags, Int32 initw = 0, Int32 inith = 0);
	Bool AttachSubDialog      (SubDialog* userdlg, Int32 id);

	Bool AddDlgGroup          (Int32 type);

	Bool GroupBeginInMenuLine	();
	Bool TabGroupBegin        (Int32 id, Int32 flags, Int32 tabtype = TAB_TABS);
	Bool GroupBegin           (Int32 id, Int32 flags, Int32 cols, Int32 rows, const String& title, Int32 groupflags, Int32 initw = 0, Int32 inith = 0);
	Bool GroupEnd             (void);
	Bool GroupSpace           (Int32 spacex, Int32 spacey);
	Bool GroupBorder          (UInt32 borderstyle);
	Bool GroupBorderNoTitle		(UInt32 borderstyle);
	Bool GroupBorderSpace     (Int32 left, Int32 top, Int32 right, Int32 bottom);
	Bool GroupWeightsSave			(const GadgetPtr& id, BaseContainer& weights);
	Bool GroupWeightsLoad			(const GadgetPtr& id, const BaseContainer& weights);
	// flags for GroupWeights
#define GROUPWEIGHTS_PERCENT_W_CNT 2000
#define GROUPWEIGHTS_PERCENT_W_VAL (GROUPWEIGHTS_PERCENT_W_CNT + 1)
#define GROUPWEIGHTS_PERCENT_H_CNT 3000
#define GROUPWEIGHTS_PERCENT_H_VAL (GROUPWEIGHTS_PERCENT_H_CNT + 1)

	Bool GetItemDim           (const GadgetPtr& id, Int32* x, Int32* y, Int32* w, Int32* h);
	Bool GetDragPosition      (const BaseContainer& msg, Int32* x, Int32* y);
	Bool GetDragObject        (const BaseContainer& msg, Int32* type, void** object);
	Bool SetDragDestination   (Int32 cursor, Int32 gadgetid = 0);

	Bool GetVisibleArea       (Int32 scrollgroupid, Int32* x1, Int32* y1, Int32* x2, Int32* y2);
	Bool SetVisibleArea       (Int32 scrollgroupid, Int32 x1, Int32 y1, Int32 x2, Int32 y2);
	Bool ScrollGroupBegin     (Int32 id, Int32 flags, Int32 scrollflags, Int32 initw = 0, Int32 inith = 0);

	Bool LayoutChanged        (const GadgetPtr& id);
	Bool LayoutChangedNoRedraw(const GadgetPtr& id);
	Bool Activate             (const GadgetPtr& id);

	Bool LayoutFlushGroup     (const GadgetPtr& id);
	Bool RemoveElement				(const GadgetPtr& id);
	Bool HideElement					(const GadgetPtr& id, Bool hide);

	Bool RestoreLayout				(Int32 pluginid, Int32 subid, void* secret);

	Bool MenuFlushAll         (void);														// call to create a complete new menu
	Bool MenuSubBegin         (const String& string);						// create a new menugroup
	Bool MenuSubEnd           (void);														// close a menugroup
	Bool MenuAddCommand       (Int32 cmdid);										// add a command to the menugroup
	Bool MenuAddString        (Int32 id, const String& string);	// add a string to the menugroup
	Bool MenuAddSeparator     (void);														// add a separator
	Bool MenuFinished         (void);														// call when finished the menulayout
	Bool MenuInitString       (Int32 id, Bool enabled, Bool checked);

	Bool CheckClose						(void);

	void* FindCustomGui				(Int32 id, Int32 pluginid);
	void* AddCustomGui				(Int32 id, Int32 pluginid, const String& name, Int32 flags, Int32 minw, Int32 minh, const BaseContainer& customdata);
	Bool ReleaseLink();

	Bool MenuSetResource      (Int32 id);
#ifdef __API_INTERN__
	Bool OpenPopUpMenu				(Int32 menuid, Int32 localx, Int32 localy, Int32 watchhotkey);
#endif

	Bool CheckDropArea        (const GadgetPtr& id, const BaseContainer& msg, Bool horiz, Bool vert);
	Bool CheckCoreMessage			(const BaseContainer& msg, Int32* ownlastcoremsg = nullptr);	// speedup for CoreMessages, return true if new, false if it's a message of the same age

	static void HandleHelpString(const BaseContainer& msg, BaseContainer& result, const String& sym);

	// for private use only!!!
	void* GetWindowHandle			();
	// for private use only!!!

	//multiline text gadget
	Bool SetMultiLineMode(const GadgetPtr& id, SCRIPTMODE mode);
	Bool SetMultiLineLock(const GadgetPtr& id, Bool lock);
};

class GeModalDialog : public GeDialog
{
private:
	Bool dlg_result;
	Bool close;

public:
	GeModalDialog(void);
	virtual ~GeModalDialog(void);

	Bool Open(Int32 xpos = -1, Int32 ypos = -1, Int32 defaultw = 0, Int32 defaulth = 0, Bool resizable = false);
	Bool Close(Bool result);
	Bool GetResult(void) { return dlg_result; }

	// for overriding (for special message handling)
	virtual Int32 Message(const BaseContainer& msg, BaseContainer& result);

	void CheckLong(Int32 id, CHECKVALUERANGE type, Int32 val, Int32 x, Int32 y);
	void CheckReal(Int32 id, CHECKVALUERANGE type, Float val, Float x, Float y, CHECKVALUEFORMAT format = CHECKVALUEFORMAT_NOTHING);
	void CheckMeter(Int32 id, CHECKVALUERANGE type, Float val, Float x, Float y);
	void CheckPercent(Int32 id, CHECKVALUERANGE type, Float val, Float x, Float y);
	void CheckDegree(Int32 id, CHECKVALUERANGE type, Float val, Float x, Float y);
};

class SubDialog : public GeDialog
{
	Bool dlg_result;

public:
	SubDialog(void);
	virtual ~SubDialog(void);
	virtual Int32 Message(const BaseContainer& msg, BaseContainer& result);
};

class iCustomGui : public SubDialog
{
	Int32						 layoutmode;
	Int32						 editheight;
	CUSTOMGUIPLUGIN* plugin;

public:
	iCustomGui(const BaseContainer& settings, CUSTOMGUIPLUGIN* t_plugin);

	virtual Int32 Message(const BaseContainer& msg, BaseContainer& result);

	virtual Int32 CustomGuiWidth();
	virtual Int32 CustomGuiHeight();
	virtual void CustomGuiRedraw();
	virtual Bool CustomGuiLayoutChanged();
	virtual Bool CustomGuiActivate();
	virtual Bool SetDefaultForResEdit();

	virtual Bool SetData(const TriState<GeData>& tristate);
	virtual TriState<GeData> GetData();

	// for overriding
	virtual Bool SupportLayoutSwitch();
	virtual void LayoutModeChanged();

	// NOT needed to override
	virtual void SetLayoutMode(Int32 mode);
	virtual Int32 GetLayoutMode();
#define LAYOUTMODE_NONE			 0	// does not support layoutmodes
#define LAYOUTMODE_MINIMIZED 1
#define LAYOUTMODE_MAXIMIZED 2

	Int32 GetEditHeight() { return editheight; }

	CUSTOMGUIPLUGIN* GetPlugin() { return plugin; }
};

inline Int32 SizePixChr(Int32 pixels, Int32 chars) { return (pixels << 14) + chars; }
inline Int32 SizePix(Int32 pixels)               { return SizePixChr(pixels, 0); }
inline Int32 SizeChr(Int32 chars)                { return SizePixChr(0, chars); }

#ifndef __API_INTERN__
void MessageDialog(const String& str);
void MessageDialog(Int32 id);
void MessageDialog(Int32 id, const String& p1);
void MessageDialog(Int32 id, const String& p1, const String& p2);
Bool QuestionDialog(const String& str);
Bool QuestionDialog(Int32 id);
Bool QuestionDialog(Int32 id, const String& p1);
Bool QuestionDialog(Int32 id, const String& p1, const String& p2);
Bool GetInputEvent(Int32 askdevice, BaseContainer& res);
Bool GetInputState(Int32 askdevice, Int32 askchannel, BaseContainer& res);
#endif

#define MOUSEPOS (0x7FFFFFFF)	// use this value for screenx/screeny
Int32 ShowPopupMenu(CDialog* cd, Int32 screenx, Int32 screeny, const BaseContainer& bc, Int32 flags = POPUP_RIGHT | POPUP_EXECUTECOMMANDS, Int32* res_mainid = nullptr);

Bool RemoveLastCursorInfo(LASTCURSORINFOFUNC func);

String Shortcut2String(Int32 shortqual, Int32 shortkey);
String Shortcut2String(const BaseContainer& sc);

inline Vector GetGuiWorldColor(Int32 cid) { return C4DOS.Ge->GetGuiWorldColor(cid); }

Bool GetIconCoordInfo(Int32& id, const Char* ident);
#define INTERFACE_ICON_TYPE_NORMAL	 0
#define INTERFACE_ICON_TYPE_DISABLED 1
#define INTERFACE_ICON_TYPE_FOCUS		 2
Bool GetInterfaceIcon(Int32 type, Int32 id_x, Int32 id_y, Int32 id_w, Int32 id_h, IconData& d);
GeClipMap* GetInterfaceScheme(Int32 type);

//-------------------------------------------------------------------------------------------------
class ProgressDialog;
#ifdef __API_INTERN__
	#define C4DThread BaseThread
#endif

class ProgressThread : public C4DThread
{
public:
	ProgressDialog* dlg;

	virtual void Main(void);
	virtual const Char* GetThreadName(void);
};

class ProgressDialog : public GeModalDialog
{
private:
	ProgressThread thread;
	Float					 percent;
	GeSpinlock		 callback_lock;
	void*					 (*callback)( void* context );
	void*					 callback_context;
	void*					 callback_result;

public:
	// from GeModalDialog
	virtual Bool CreateLayout(void);
	virtual Bool InitValues(void);
	virtual void Timer(const BaseContainer& msg);
	virtual Int32 Message(const BaseContainer& msg, BaseContainer& result);
	virtual Bool Command(Int32 id, const BaseContainer& msg);
	virtual Bool AskClose(void);

	// for use in inherited class
	void SetPercent(Float p);
	C4DThread* GetThread(void);
	void* CallFromMainThread(void*(*fn)( void* context ), void* context);

	// for overriding
	virtual void Main(C4DThread* bt) = 0;
	virtual String GetTitle(void) = 0;
};

#endif
