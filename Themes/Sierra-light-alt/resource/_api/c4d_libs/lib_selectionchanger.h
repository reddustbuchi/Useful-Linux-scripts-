/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

//Convenience class for changing BaseSelect selections from one mode to another
#ifndef _C4D_SELECTIONCHANGER_H_
#define _C4D_SELECTIONCHANGER_H_

#include "c4d.h"

#define	C4DSELECTIONCHANGER_LIB_ID		1019533

class SelectionChanger
{
private:
	SelectionChanger(void)	{ }
	~SelectionChanger(void)	{	}
public:

	//Init via tag (convenience)
	Bool										InitFromTag(BaseTag *targtag, PolygonObject *op = nullptr);
	//Init from raw selection Mpoints Medges Mpolygons for the selection_mode
	Bool										InitFromSelection(BaseSelect *selection, Int32 selection_mode, PolygonObject *op = nullptr);
	//Retrieve converted selections
	BaseSelect							*GetPointS(void);
	BaseSelect							*GetEdgeS(void);
	BaseSelect							*GetPolygonS(void);

	static SelectionChanger *Alloc(void);
	static void							Free(SelectionChanger *&node);
};


//---------------------------
//	---INTERNAL STUFF
class iSelectionChanger;

struct SelectionChangerLibrary : public C4DLibrary
{
	Bool							(iSelectionChanger::*InitFromTag			)(BaseTag *targtag, PolygonObject *op);
	Bool							(iSelectionChanger::*InitFromSelection)(BaseSelect *selection, Int32 selection_mode, PolygonObject *op);
	BaseSelect*				(iSelectionChanger::*GetPointS				)();
	BaseSelect*				(iSelectionChanger::*GetEdgeS					)();
	BaseSelect*				(iSelectionChanger::*GetPolygonS			)();

	iSelectionChanger*(*Alloc	)();
	void							(*Free	)(iSelectionChanger *&node);
};
//	---INTERNAL STUFF
//---------------------------

#endif
