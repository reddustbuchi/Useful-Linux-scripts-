/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _CUSTOMGUI_TREEVIEW_H_
#define _CUSTOMGUI_TREEVIEW_H_

#include "customgui_base.h"
#include "c4d_basecontainer.h"



#define CUSTOMGUI_TREEVIEW		1000475 // user gadget


#define TREEVIEW_BORDER             'brdr'
#define TREEVIEW_OUTSIDE_DROP       'tvod' // true, if object may be dropped under all objects in the tree view
#define TREEVIEW_HIDE_LINES         'tvhl' // true, if no lines should be drawn
#define TREEVIEW_CTRL_DRAG          'ctdr' // true, if item may be duplicated by Ctrl + Drag
#define TREEVIEW_NO_MULTISELECT     'tvnm' // true, if no multi select is allowed
#define TREEVIEW_HAS_HEADER         'tvhh' // true, if the tree view may have a header line
#define TREEVIEW_RESIZE_HEADER      'tvrh' // true, if the column width can be changed by the user
#define TREEVIEW_MOVE_COLUMN        'tvmc' // true, if the user can move a column
#define TREEVIEW_FIXED_LAYOUT       'tvfl' // true, if all lines have the same height
#define TREEVIEW_NOAUTOCOLUMNS			'noau' // true, only the first line is asked for the columnswidth -> huge speedup!
#define TREEVIEW_NO_OPEN_CTRLCLK    'tvcd' // true, if it's not allowed to open the complete tree with ctrl + click
#define TREEVIEW_ALT_DRAG           'tvad' // use alt instead of Ctrl for Drag & Drop, implies item may be duplicated by Alt + Drag
#define TREEVIEW_NO_BACK_DELETE     'tvnb' // Disable DeletePressed messages if Backspace was hit
#define TREEVIEW_ALTERNATE_BG       'tvab' // Alternate background color per line
#define TREEVIEW_CURSORKEYS         'tvck' // Process cursor keys (set the focus item nullptr if you delete it and this flag is set)
#define TREEVIEW_NOENTERRENAME			'tver' // Does not open a rename popup when the user presses enter

#define TREEVIEW_DRAGSTART_ALLOW		1
#define TREEVIEW_DRAGSTART_SELECT		2

#define LV_TREE				'tree'
#define LV_USERTREE		'ustr'
#define LV_USER				'user'
#define LV_CHECKBOX		'cbox'
	#define LV_CHECKBOX_ENABLED		1
	#define LV_CHECKBOX_CHECKED		2
	#define LV_CHECKBOX_TRISTATE	4
	#define LV_CHECKBOX_HIDE			8

#define ACCEPT_DRAG_OBJECT_FORCE_COPY	(1 << 30) // Use this to force a copy cursor. The next InsertObject call will have set bCopy = true
#define LISTVIEW_TABLE_SIZE						47

class TreeViewCustomGui;

class GeUserArea;

struct CellInfo
{
	GeUserArea *frame;

	Int32 xpos,ypos,width,height;
	Int32 line,col;
};

struct DrawInfo : public CellInfo
{
	GeData bgCol;
};

#define MOUSEINFO_BUTTON_LEFT		0
#define MOUSEINFO_BUTTON_RIGHT	1
#define MOUSEINFO_BUTTON_MIDDLE	2
struct MouseInfo : public CellInfo
{
	Float mx;
	Float my;
	Int32 button;
	Float mxRelative; // use this in LV_USERTREE
	Bool startDrag;
	Bool startpaint, inpaint;
	const BaseContainer *inputmsg; // the container that was passed to InputEvent, always != nullptr
};

struct DragInfo : public CellInfo
{
	Float	mx;
	Float	my;
	BaseContainer msg;

	void	*dragobject;
	Int32	dragtype;
};

// if bCont is false, the branch is not visited any more
typedef Bool (*VisitChildrenCallback)(void* root, void* obj, void* userdata, void* data1, void* data2, Bool &bCont);

enum
{
	ID_TREEVIEW_CONTEXT_DISABLE = 1000,				// return empty container with Id == ID_TREEVIEW_CONTEXT_DISABLE to disable context menu in treeview
	ID_TREEVIEW_CONTEXT_REMOVE = FIRST_POPUP_ID,
	ID_TREEVIEW_CONTEXT_RESET,
	ID_TREEVIEW_FIRST_NEW_ID = FIRST_POPUP_ID + 10
};

class TreeViewFunctions
{
	public:
		virtual ~TreeViewFunctions() { }

		// Navigation Functions
		virtual void*		GetFirst(void *root,void *userdata) = 0;
		virtual void*		GetDown(void *root,void *userdata,void *obj) = 0;
		virtual void*		GetNext(void *root,void *userdata,void *obj) = 0;
		virtual void*		GetPred(void *root,void *userdata,void *obj); // only for drag&drop check

		// Layout&Draw functions
		virtual Int32		GetColumnWidth(void *root,void *userdata,void *obj,Int32 col, GeUserArea* area);
		virtual Int32		GetHeaderColumnWidth(void *root,void *userdata,Int32 col, GeUserArea* area); // return a negative number for auto header width
		virtual Int32		GetMinHeaderHeight(void *root,void *userdata, GeUserArea* area); // return < 0 for auto header height
		virtual Int32		GetLineHeight(void *root,void *userdata,void *obj,Int32 col, GeUserArea* area); // always return a value > 0 !
		virtual void		GetColors(void *root,void *userdata,void *obj, GeData* pNormal, GeData* pSelected);
		virtual void		GetBackgroundColor(void* root, void* userdata, void* obj, Int32 line, GeData* col);
		virtual void		DrawCell(void *root,void *userdata,void *obj,Int32 col,DrawInfo *drawinfo, const GeData &bgColor);
		virtual Bool		DrawHeaderCell(void *root, void *userdata, Int32 col, DrawInfo *drawinfo); // return false if the header should be drawn by the tree view

		// Get Functions
		virtual Bool		IsSelected(void *root,void *userdata,void *obj) = 0;
		virtual Bool		IsOpened(void *root,void *userdata,void *obj) = 0;
		virtual String	GetName(void *root,void *userdata,void *obj) = 0;
		virtual Int		GetId(void *root,void *userdata,void *obj) = 0;
		virtual Int32		GetDragType(void *root,void *userdata,void *obj) = 0; // return NOTOK to disable D&D
		virtual Int32		DragStart(void *root,void *userdata,void *obj);
		virtual Int32		IsChecked(void *root,void *userdata,void *obj, Int32 lColumn); // for checkboxes (return a combination of LV_CHECKBOX_* or NOTOK if you don't want to show the checkbox)
		virtual Bool		IsTristate(void *root, void *userdata);

		// Set Functions
		virtual void		Open(void *root,void *userdata,void *obj,Bool onoff);
		virtual void		SetName(void *root,void *userdata,void *obj, const String &str);
		virtual void		Select(void *root,void *userdata,void *obj,Int32 mode);
		virtual Int32		AcceptDragObject(void *root,void *userdata,void *obj,Int32 dragtype,void *dragobject, Bool &bAllowCopy); // return INSERT_xxx
		// if obj == nullptr, the dragobject should be inserted as a child of the root
		virtual void		InsertObject(void *root,void *userdata,void *obj,Int32 dragtype,void *dragobject,Int32 insertmode, Bool bCopy);
#define INSERT_BEFORE		(1<<0)
#define INSERT_AFTER		(1<<1)
#define INSERT_UNDER		(1<<2)
		virtual void		SetCheck(void *root,void *userdata,void *obj, Int32 lColumn, Bool bCheck, const BaseContainer& bcMsg); // for checkboxes

		// GUI and Drag&Drop
		// bc already contains a delete element, you may delete the contents of bc. Your own elements should start at ID_TREEVIEW_FIRST_NEW_ID
		virtual void		CreateContextMenu(void *root, void *userdata, void *obj, Int32 lColumn, BaseContainer* bc);
		virtual void		SetDragObject(void *root,void *userdata,void *obj);
		virtual void		GenerateDragArray(void *root,void *userdata,void *obj, AtomArray* ar);
		virtual void		GenerateDragData(void *root, void *userdata, void* obj, void **dragdata);
		virtual void		FreeDragData(void *root, void *userdata, void *dragdata);
		virtual Int32		GetHeaderSortArrow(void *root, void *userdata, Int32 lColID);
		virtual Bool		IsResizeColAllowed(void *root, void *userdata, Int32 lColID);
		virtual Bool		IsMoveColAllowed(void *root, void *userdata, Int32 lColID);

		virtual Bool		InputEvent(void* root, void* userdata, GeUserArea* pArea, const BaseContainer &msg);
		virtual Bool		MouseDown(void *root,void *userdata,void *obj,Int32 col,MouseInfo *mouseinfo, Bool rightButton);
		virtual Bool		DoubleClick(void *root,void *userdata,void *obj,Int32 col,MouseInfo *mouseinfo); // return false, if you want to open the rename dialog
		virtual void		DeletePressed(void *root, void *userdata);

		// notifications
		virtual void		Scrolled(void *root, void *userdata, Int32 h, Int32 v, Int32 x, Int32 y);
		virtual void		PaintFinished(void *root, void *userdata);
		virtual Bool		ColumnMoved(void *root, void *userdata, Int32 lColID, Int32 lInsertBeforeCol, Int32* plIndexMap, const BaseContainer* pbcLayout);
		virtual void		SelectionChanged(void *root, void *userdata);
		virtual Bool		HeaderClick(void *root, void *userdata, Int32 lColID, Int32 lChannel, Bool bDblClk); // return true, if the tree view needs to be updated
		// return true, if you proceeded the command and the data needs to be updated
		virtual Bool		ContextMenuCall(void *root,void *userdata,void *obj, Int32 lColumn, Int32 lCommand); // called by a command in the context menu, return true if you processed the message

		// called after the user released the cursor, return false if you want to cancel the layout change
		// NOTE : lInsertBeforeCol is the index of the column
		virtual void		InitCache(void *root, void *userdata);
		virtual Bool		PythonCleanup(void *root, void *userdata); // private

		// non-overridable

		// calls fn for obj and all its children
		Bool VisitChildren(void* root, void* obj, VisitChildrenCallback fn, void* userdata, void* data1, void* data2);
};


// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

class TreeViewF
{
public:
	Int32		GetTableSize() { return LISTVIEW_TABLE_SIZE; }

	// Navigation Functions
	void*		GetFirst(TreeViewFunctions* pFuncs, void *root,void *userdata);
	void*		GetDown(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj);
	void*		GetNext(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj);
	void*		GetPred(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj);

	// Layout&Draw functions
	Int32		GetColumnWidth(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj,Int32 col, GeUserArea* area);
	Int32		GetHeaderColumnWidth(TreeViewFunctions* pFuncs, void *root,void *userdata,Int32 col, GeUserArea* area);
	Int32		GetMinHeaderHeight(TreeViewFunctions* pFuncs, void *root,void *userdata, GeUserArea* area);
	Int32		GetLineHeight(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj,Int32 col, GeUserArea* area);
	void		GetColors(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj, GeData* pNormal, GeData* pSelected);
	void		GetBackgroundColor(TreeViewFunctions* pFuncs, void* root, void* userdata, void* obj, Int32 line, GeData* col);
	void		DrawCell(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj,Int32 col,DrawInfo *drawinfo, const GeData& bgColor);
	Bool		DrawHeaderCell(TreeViewFunctions* pFuncs, void *root,void *userdata,Int32 col,DrawInfo *drawinfo);

	// Get Functions
	Bool		IsSelected(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj);
	Bool		IsOpened(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj);
	String	GetName(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj);
	Int		GetId(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj);
	Int32		GetDragType(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj);
	Int32		DragStart(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj);
	Int32		IsChecked(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj, Int32 lColumn);
	Bool		IsTristate(TreeViewFunctions* pFuncs, void *root, void *userdata);

	// Set Functions
	void		Open(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj,Bool onoff);
	void		SetName(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj, const String &str);
	void		Select(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj,Int32 mode);
	Int32		AcceptDragObject(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj,Int32 dragtype,void *dragobject, Bool &bAllowCopy);
	void		InsertObject(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj,Int32 dragtype,void *dragobject,Int32 insertmode, Bool bCopy);
	void		SetCheck(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj, Int32 lColumn, Bool bCheck, const BaseContainer& bcMsg);

	// GUI and Drag&Drop
	void		CreateContextMenu(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj, Int32 lColumn, BaseContainer* bc);
	void		SetDragObject(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj);
	void		GenerateDragArray(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj, AtomArray* ar);
	void		GenerateDragData(TreeViewFunctions* pFuncs, void *root, void *userdata, void* obj, void **dragdata);
	void		FreeDragData(TreeViewFunctions* pFuncs, void *root, void *userdata, void *dragdata);
	Int32		GetHeaderSortArrow(TreeViewFunctions* pFuncs, void *root, void *userdata, Int32 lColID);
	Bool		IsResizeColAllowed(TreeViewFunctions* pFuncs, void *root, void *userdata, Int32 lColID);
	Bool		IsMoveColAllowed(TreeViewFunctions* pFuncs, void *root, void *userdata, Int32 lColID);

	Bool		InputEvent(TreeViewFunctions* pFuncs, void* root, void* userdata, GeUserArea* pArea, const BaseContainer &msg);
	Bool		MouseDown(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj,Int32 col,MouseInfo *mouseinfo, Bool rightButton);
	Bool		DoubleClick(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj,Int32 col,MouseInfo *mouseinfo);
	void		DeletePressed(TreeViewFunctions* pFuncs, void *root, void *userdata);

	// notifications
	void		Scrolled(TreeViewFunctions* pFuncs, void *root, void *userdata, Int32 h, Int32 v, Int32 x, Int32 y);
	void		PaintFinished(TreeViewFunctions* pFuncs, void *root, void *userdata);
	Bool		ColumnMoved(TreeViewFunctions* pFuncs, void *root, void *userdata, Int32 lColID, Int32 lInsertBeforeCol, Int32* plIndexMap, const BaseContainer* pbcLayout);
	void		SelectionChanged(TreeViewFunctions* pFuncs, void *root, void *userdata);
	Bool		HeaderClick(TreeViewFunctions* pFuncs, void *root, void *userdata, Int32 lColID, Int32 lChannel, Bool bDbl);
	Bool		ContextMenuCall(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj, Int32 lColumn, Int32 lCommand);

	void		InitCache(TreeViewFunctions* pFuncs, void *root,void *userdata);
	Bool		PythonCleanup(TreeViewFunctions* pFuncs, void *root, void *userdata);
};

struct InternalFunctionTable
{
	/* 1*/ Int32			(TreeViewF::*GetTableSize)();

	// Navigation Functions
	/* 2*/ void*		(TreeViewF::*GetFirst)(TreeViewFunctions* pFuncs, void *root,void *userdata);
	/* 3*/ void*		(TreeViewF::*GetDown)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj);
	/* 4*/ void*		(TreeViewF::*GetNext)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj);
	/* 5*/ void*		(TreeViewF::*GetPred)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj); // only for drag&drop check

	// Layout&Draw functions
	/* 6*/ Int32			(TreeViewF::*GetColumnWidth)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj,Int32 col, GeUserArea* area);
	/* 7*/ Int32			(TreeViewF::*GetHeaderColumnWidth)(TreeViewFunctions* pFuncs, void *root,void *userdata,Int32 col, GeUserArea* area);
	/* 8*/ Int32			(TreeViewF::*GetMinHeaderHeight)(TreeViewFunctions* pFuncs, void *root,void *userdata, GeUserArea* area);
	/* 9*/ Int32			(TreeViewF::*GetLineHeight)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj,Int32 col, GeUserArea* area);
	/*10*/ void			(TreeViewF::*GetColors)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj, GeData* pNormal, GeData* pSelected);
	/*11*/ void			(TreeViewF::*GetBackgroundColor)(TreeViewFunctions* pFuncs, void* root, void* userdata, void* obj, Int32 line, GeData* col);
	/*12*/ void			(TreeViewF::*DrawCell)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj,Int32 col,DrawInfo *drawinfo, const GeData &bgColor);
	/*13*/ Bool			(TreeViewF::*DrawHeaderCell)(TreeViewFunctions* pFuncs, void *root,void *userdata,Int32 col,DrawInfo *drawinfo);

	// Get Functions
	/*14*/ Bool			(TreeViewF::*IsSelected)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj);
	/*15*/ Bool			(TreeViewF::*IsOpened)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj);
	/*16*/ String		(TreeViewF::*GetName)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj);
	/*17*/ Int		(TreeViewF::*GetId)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj);
	/*18*/ Int32			(TreeViewF::*GetDragType)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj); // return NOTOK to disable D&D
	/*19*/ Int32			(TreeViewF::*DragStart)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj);
	/*20*/ Int32			(TreeViewF::*IsChecked)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj, Int32 lColumn);
	/*21*/ Bool			(TreeViewF::*IsTristate)(TreeViewFunctions* pFuncs, void *root, void *userdata);

	// Set Functions
	/*22*/ void			(TreeViewF::*Open)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj,Bool onoff);
	/*23*/ void			(TreeViewF::*SetName)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj, const String &str);
	/*24*/ void			(TreeViewF::*Select)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj,Int32 mode);
	/*25*/ Int32			(TreeViewF::*AcceptDragObject)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj,Int32 dragtype,void *dragobject, Bool &bAllowCopy); // retrun INSERT_xxx
	/*26*/ void			(TreeViewF::*InsertObject)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj,Int32 dragtype,void *dragobject,Int32 insertmode, Bool bCopy);
	/*27*/ void			(TreeViewF::*SetCheck)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj, Int32 lColumn, Bool bCheck, const BaseContainer& bcMsg);

	// GUI and Drag&Drop
	/*28*/ void			(TreeViewF::*CreateContextMenu)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj, Int32 lColumn, BaseContainer* bc);
	/*29*/ void			(TreeViewF::*SetDragObject)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj);
	/*30*/ void			(TreeViewF::*GenerateDragArray)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj, AtomArray* ar);
	/*31*/ void			(TreeViewF::*GenerateDragData)(TreeViewFunctions* pFuncs, void *root, void *userdata, void* obj, void **dragdata);
	/*32*/ void			(TreeViewF::*FreeDragData)(TreeViewFunctions* pFuncs, void *root, void *userdata, void *dragdata);
	/*33*/ Int32			(TreeViewF::*GetHeaderSortArrow)(TreeViewFunctions* pFuncs, void *root, void *userdata, Int32 lColID);
	/*34*/ Bool			(TreeViewF::*IsResizeColAllowed)(TreeViewFunctions* pFuncs, void *root, void *userdata, Int32 lColID);
	/*35*/ Bool			(TreeViewF::*IsMoveColAllowed)(TreeViewFunctions* pFuncs, void *root, void *userdata, Int32 lColID);

	/*36*/ Bool			(TreeViewF::*InputEvent)(TreeViewFunctions* pFuncs, void* root, void* userdata, GeUserArea* pArea, const BaseContainer &msg);
	/*37*/ Bool			(TreeViewF::*MouseDown)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj,Int32 col,MouseInfo *mouseinfo, Bool rightButton);
	/*38*/ Bool			(TreeViewF::*DoubleClick)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj,Int32 col,MouseInfo *mouseinfo); // return false, if you want to open the rename dialog
	/*39*/ void			(TreeViewF::*DeletePressed)(TreeViewFunctions* pFuncs, void *root, void *userdata);

	// notifications
	/*40*/ void			(TreeViewF::*Scrolled)(TreeViewFunctions* pFuncs, void *root, void *userdata, Int32 h, Int32 v, Int32 x, Int32 y);
	/*41*/ void			(TreeViewF::*PaintFinished)(TreeViewFunctions* pFuncs, void *root, void *userdata);
	/*42*/ Bool			(TreeViewF::*ColumnMoved)(TreeViewFunctions* pFuncs, void *root, void *userdata, Int32 lColID, Int32 lInsertBeforeCol, Int32* plIndexMap, const BaseContainer* pbcLayout);
	/*43*/ void			(TreeViewF::*SelectionChanged)(TreeViewFunctions* pFuncs, void *root, void *userdata);
	/*44*/ Bool			(TreeViewF::*HeaderClick)(TreeViewFunctions* pFuncs, void *root, void *userdata, Int32 lColID, Int32 lChannel, Bool bDbl);
	/*45*/ Bool			(TreeViewF::*ContextMenuCall)(TreeViewFunctions* pFuncs, void *root,void *userdata,void *obj, Int32 lColumn, Int32 lCommand); // called by the delete command in the context menu

	/*46*/ void			(TreeViewF::*InitCache)(TreeViewFunctions* pFuncs, void *root,void *userdata);
	/*47*/ Bool			(TreeViewF::*PythonCleanup)(TreeViewFunctions* pFuncs, void *root,void *userdata);
};




// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF


class TreeViewCustomGui : public BaseCustomGui<CUSTOMGUI_TREEVIEW>
{
		TreeViewCustomGui();
		~TreeViewCustomGui();

	public:
		Bool		SetRoot(void *root,TreeViewFunctions *functions,void *userdata);
		Bool		SetLayout(Int32 columns,const BaseContainer &data);
		Bool		SetHeaderText(Int32 lColumnID, const String &str);
		GeUserArea* GetTreeViewArea();
		GeUserArea* GetHeaderArea();
		void		Refresh();
		Int32		GetAutoColumnWidth(Int32 lColID); // the auto-width of the column
		Int32		GetColumnWidthUser(Int32 lColID); // the size the user has set

		Int32		GetRealColumnWidth(Int32 lColID); // the real column width
		Bool		SetColumnWidthUser(Int32 lColID, Int32 lWidth);
		Bool		MakeVisible(void* pObj); // scrolls to pObj and expands the tree if necessary
		Bool		ShowObject(void* pObj); // expands the tree to pObj
		Bool		GetCellPosition(void* pObj, Int32 lColID, GeUserArea *&pArea, Int32 &x, Int32 &y, Int32 &w, Int32 &h, Int32 &lTextOffset);
		Bool		IsFocusItem(void* pObj);
		void*		GetFocusItem();
		void		SetFocusItem(void* pItem);
		const BaseContainer* GetLayout();
		void*		GetObject(Int32 line, Int32 *level);
		void*		GetSelectionItem();
		void		SetSelectionItem(void* pItem);
};



// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF


#ifndef _INTERNAL_DEF_
	class iTreeViewCustomGui
	{
	};
#else
	class iTreeViewCustomGui;
#endif

struct TreeViewLib : public BaseCustomGuiLib
{
	Bool    (iTreeViewCustomGui::*SetRoot		)(void *root, InternalFunctionTable* f, void *userdata, Int32 lSize, TreeViewF* pControl, TreeViewFunctions* pFunctions);
	void		(iTreeViewCustomGui::*Refresh		)();
	Bool		(iTreeViewCustomGui::*SetLayout	)(Int32 columns,const BaseContainer &data);
	Bool		(iTreeViewCustomGui::*ShowObject)(void *o);
	Bool    (iTreeViewCustomGui::*SetHeaderText)(Int32 lColumnID, const String &str);
	GeUserArea* (iTreeViewCustomGui::*GetTreeViewArea)();
	GeUserArea* (iTreeViewCustomGui::*GetHeaderArea)();
	Int32    (iTreeViewCustomGui::*GetAutoColumnWidth)(Int32 lColID);
	Int32    (iTreeViewCustomGui::*GetColumnWidthUser)(Int32 lColID);
	Int32    (iTreeViewCustomGui::*GetRealColumnWidth)(Int32 lColID);
	Bool    (iTreeViewCustomGui::*SetColumnWidthUser)(Int32 lColID, Int32 lWidth);
	Bool    (iTreeViewCustomGui::*MakeVisible)(void* pObj);
	Bool		(iTreeViewCustomGui::*GetCellPosition)(void* pObj, Int32 lColID, GeUserArea *&pArea, Int32 &x, Int32 &y, Int32 &w, Int32 &h, Int32 &lTextOffset);
	Bool		(iTreeViewCustomGui::*IsFocusItem)(void* pObj);
	void*		(iTreeViewCustomGui::*GetFocusItem)();
	void		(iTreeViewCustomGui::*SetFocusItem)(void* pItem);
	const BaseContainer*	(iTreeViewCustomGui::*GetLayout)();
	void*		(iTreeViewCustomGui::*GetObject)(Int32 line, Int32 *level);
	void*		(iTreeViewCustomGui::*GetSelectionItem)();
	void		(iTreeViewCustomGui::*SetSelectionItem)(void* pItem);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif
