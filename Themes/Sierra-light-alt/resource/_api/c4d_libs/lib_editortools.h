/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _LIB_EDITORTOOLS_H_
#define _LIB_EDITORTOOLS_H_

#include "c4d_library.h"

class LassoSelection;

class C4DObjectList
{
	private:
		C4DObjectList();
		~C4DObjectList();
	public:
		static C4DObjectList* Alloc();
		static void Free(C4DObjectList *&ptr);

		// GetCount() - returns the number of objects
		// GetObject() - returns the object
		// GetZ() - returns the Z depth of the object from the camera
		// AddObject() - adds an object to the list
		// Flush() - deletes the contents of the list

		Int32 GetCount();
		BaseObject*	GetObject(Int32 num);
		Float GetZ(Int32 num);
		Int32 GetPolyIdx(Int32 num);

		Bool AddObject(BaseObject *op, Float z, Int32 polynum);
		void Flush();
};

// SelectionListCreate:
// creates a valid objectlist for a given coordinate (mx,my) for a specific basedraw (bd)
// return: true = successful, false: any kind of error,
// list the contains a sorted list of all objects [0] is the closest object [cnt-1] the farest object
// the lasso selection class is optional
Bool SelectionListCreate(BaseDocument *doc, BaseObject *parent, BaseDraw *bd, Float mx, Float my, LassoSelection *ls, C4DObjectList *list, Bool use_selection_filter = true, Bool use_display_filter = true);

// SelectionListCreate:
// creates a valid objectlist for a given coordinate (mx,my) for a specific basedraw (bd) from the array passed
// return: true = successful, false: any kind of error,
// list the contains a sorted list of all objects [0] is the closest object [cnt-1] the farest object
// the lasso selection class is optional
Bool FilteredSelectionListCreate(BaseDocument *doc, AtomArray *arr, BaseDraw *bd, Float mx, Float my, LassoSelection *ls, C4DObjectList *list, Bool use_selection_filter = true, Bool use_display_filter = true);


// SelectionListShowMenu:
// shows a popupmenu with of the given objectlist and lets the user choose
// screenx&y = "MOUSEPOS" means automatic position
// result: the number of the element in the objectlist, -1 means nothing or aborted
Int32 SelectionListShowMenu(BaseDocument *doc, Float screenx, Float screeny, C4DObjectList *list);





// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#define LIBRARY_OBJECTLIST		1000464

class C4DObjectList;

struct ObjectListLib : public C4DLibrary
{
	C4DObjectList* (*ObjectList_Alloc      )();
	void        (*ObjectList_Free       )(C4DObjectList *ptr);
	Int32				(*ObjectList_GetCount   )(C4DObjectList *ptr);
	BaseObject*	(*ObjectList_GetObject  )(C4DObjectList *ptr, Int32 num);
	Float				(*ObjectList_GetZ       )(C4DObjectList *ptr, Int32 num);
	Bool        (*ObjectList_AddObjectEx)(C4DObjectList *ptr, BaseObject *op, Float z);
	Bool        (*ObjectList_AddObject  )(C4DObjectList *ptr, BaseObject *op, Float z, Int32 polynum);
	Int32				(*ObjectList_GetPolyIdx )(C4DObjectList *ptr, Int32 num);
	void				(*ObjectList_Flush			)(C4DObjectList *ptr);
};

// example implementation editor tools, internal stuff

#define LIBRARY_EDITORTOOLS		1000465

struct EditorToolLib : public C4DLibrary
{
	Bool				(*SelectionListCreateEx )(BaseDocument *doc, BaseObject *parent, BaseDraw *bd, Float mx, Float my, LassoSelection *ls, C4DObjectList *list);
	Int32        (*SelectionListShowMenu )(BaseDocument *doc, Float screenx, Float screeny, C4DObjectList *list);
	Bool				(*SelectionListCreate   )(BaseDocument *doc, BaseObject *parent, BaseDraw *bd, Float mx, Float my, LassoSelection *ls, C4DObjectList *list, Bool use_selection_filter, Bool use_display_filter);
	Bool				(*FilteredSelectionListCreate   )(BaseDocument *doc, AtomArray *arr, BaseDraw *bd, Float mx, Float my, LassoSelection *ls, C4DObjectList *list, Bool use_selection_filter, Bool use_display_filter);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif
