/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4D_TOOLDATA_H
#define __C4D_TOOLDATA_H

#include "c4d_basedata.h"
#include "customgui_description.h"

class AtomArray;
class String;
class BaseContainer;
class BaseBitmap;
class BaseDocument;
class BaseObject;
class BaseDraw;
class BaseDrawHelp;
class BaseThread;
class CDialog;
class EditorWindow;
class SubDialog;

struct ControlDisplayStruct
{
	ControlDisplayStruct() : displaymode(DISPLAYMODE_UNKNOWN), backface_culling(false), editmode(false), vertex_color(nullptr), dontfreevertexcolor(false), vertex_color_shading(false) { }

	DISPLAYMODE	displaymode;
	Bool				backface_culling;
	Bool				editmode;
	Vector32*		vertex_color;
	Bool				dontfreevertexcolor;	// false = the caller frees the vertex_color memory, true = the called function owns the memory, don't free memory
	Bool				vertex_color_shading;
};

class EditorWindow
{
private:
	EditorWindow();
	~EditorWindow();

public:
	void DrawXORLine(Int32 x1, Int32 y1, Int32 x2, Int32 y2);

	void MouseDragStart(Int32 button, Float mx, Float my, MOUSEDRAGFLAGS flag);	// button: BFM_INPUT_xxx
	MOUSEDRAGRESULT MouseDrag(Float* mx, Float* my, BaseContainer* channels);
	MOUSEDRAGRESULT MouseDragEnd(void);

	Bool BfGetInputState(Int32 askdevice, Int32 askchannel, BaseContainer* res);	// device: BFM_INPUT_MOUSE,BFM_INPUT_KEYBOARD, channel: BFM_INPUT_MOUSE_xxx
	Bool BfGetInputEvent(Int32 askdevice, BaseContainer* res);										// device: BFM_INPUT_MOUSE,BFM_INPUT_KEYBOARD,
	Bool IsHotkeyDown(Int32 id);

	void StatusSetText(const String& str);

	Bool Screen2Local(Int32* x, Int32* y);
	Bool Local2Screen(Int32* x, Int32* y);
	Bool Global2Local(Int32* x, Int32* y);
	Bool Local2Global(Int32* x, Int32* y);
};

// MouseDrag channel values
enum
{
	PENPRESSURE					 = 1,
	PENTILT							 = 2,
	PENROTATION					 = 3,
	PENDRAWROTATION			 = 4,
	PENDRAWRANDOMNESS		 = 5,
	PENDRAWWHEELROTATION = 6,
	PENDRAWWHEELPRESSURE = 7,
	PENDRAWDISTANCE			 = 8,
	PENFINGERWHEEL			 = 9
};

#define PLUGINFLAG_TOOL_EVALUATEHANDLES		 (1 << 1)
#define PLUGINFLAG_TOOL_DRAW_MULTIPLANE		 (1 << 2)
#define PLUGINFLAG_TOOL_TWEAK							 (1 << 3)
#define PLUGINFLAG_TOOL_HIGHLIGHT					 (1 << 4)
#define PLUGINFLAG_TOOL_EDITSTATES				 (1 << 5)
#define PLUGINFLAG_TOOL_SNAPSETTINGS			 (1 << 6)
#define PLUGINFLAG_TOOL_SINGLECLICK				 (1 << 7)
#define PLUGINFLAG_TOOL_TWEAK_NO_HIGHLIGHT ((1 << 3) | (1 << 8))
#define PLUGINFLAG_TOOL_NO_WIREFRAME			 (1 << 9)
#define PLUGINFLAG_TOOL_SCULPTBRUSH				 (1 << 10)
#define PLUGINFLAG_TOOL_NO_OBJECTOUTLINE	 (1 << 11)	// hide outline for selected objects
#define PLUGINFLAG_TOOL_OBJECTHIGHLIGHT		 (1 << 12)	// show outline during mouseover

class ToolData : public BaseData
{
	friend Bool RegisterToolPlugin(Int32 id, const String& str, Int32 info, BaseBitmap* icon, const String& help, ToolData* dat);

private:
	virtual CDialog*	AllocDialog(BaseContainer* bc, CDialog* cd_parent, Int32 dlg_id);
	virtual void FreeDialog(CDialog* cd);

public:
	virtual Bool InitTool(BaseDocument* doc, BaseContainer& data, BaseThread* bt);
	virtual void FreeTool(BaseDocument* doc, BaseContainer& data);

	virtual Bool DoCommand(ModelingCommandData& mdat);
	virtual void InitDefaultSettings(BaseDocument* pDoc, BaseContainer& data);

	virtual const String GetResourceSymbol();

	virtual Bool MouseInput(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg);
	virtual Bool KeyboardInput(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg);

	virtual Int32	GetState(BaseDocument* doc);
	virtual Bool GetCursorInfo(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, Float x, Float y, BaseContainer& bc);
	virtual TOOLDRAW Draw(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, BaseDrawHelp* bh, BaseThread* bt, TOOLDRAWFLAGS flags);

	virtual Bool InitDisplayControl(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, const AtomArray* active);
	virtual void FreeDisplayControl(void);
	virtual Bool DisplayControl(BaseDocument* doc, BaseObject* op, BaseObject* chainstart, BaseDraw* bd, BaseDrawHelp* bh, ControlDisplayStruct& cds);

	virtual SubDialog*	AllocSubDialog(BaseContainer* bc);

	virtual Bool GetDDescription(BaseDocument* doc, BaseContainer& data, Description* description, DESCFLAGS_DESC& flags);
	virtual Bool GetDParameter(BaseDocument* doc, BaseContainer& data, const DescID& id, GeData& t_data, DESCFLAGS_GET& flags);
	virtual Bool GetDEnabling(BaseDocument* doc, BaseContainer& data, const DescID& id, const GeData& t_data, DESCFLAGS_ENABLE flags, const BaseContainer* itemdesc);
	virtual Bool SetDParameter(BaseDocument* doc, BaseContainer& data, const DescID& id, const GeData& t_data, DESCFLAGS_SET& flags);
	virtual Bool Message(BaseDocument* doc, BaseContainer& data, Int32 type, void* t_data);
};

BaseContainer* GetToolData(BaseDocument* doc, Int32 pluginid);
Float GetToolScale(BaseDraw* bd, AtomArray* arr, Bool all, Int32 mode = NOTOK);

Bool RegisterToolPlugin(Int32 id, const String& str, Int32 info, BaseBitmap* icon, const String& help, ToolData* dat);

#endif
