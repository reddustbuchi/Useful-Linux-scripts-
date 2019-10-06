/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _GUI_BITMAPBOOL_H_
#define _GUI_BITMAPBOOL_H_

#include "customgui_base.h"
#include "c4d_basecontainer.h"

#define CUSTOMGUI_BITMAPBOOL              450000130

#define BITMAPBOOL_ACTIVE			1000
#define BITMAPBOOL_INACTIVE		1001
#define BITMAPBOOL_TRISTATE		1002

class BitmapBoolGui : public BaseCustomGui<CUSTOMGUI_BITMAPBOOL>
{
private:
	BitmapBoolGui();
	~BitmapBoolGui();
public:
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#ifndef _INTERNAL_BITMAPBOOL_DEF_
	class iBitmapBoolGui
	{
	};
#else
	class iBitmapBoolGui;
#endif

struct CustomGuiBitmapBoolLib : public BaseCustomGuiLib
{
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif // _GUI_BITMAPBOOL_H_

