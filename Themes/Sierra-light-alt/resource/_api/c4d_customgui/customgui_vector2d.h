/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _CUSTOMGUI_VECTOR2D_H_
#define _CUSTOMGUI_VECTOR2D_H_

#ifdef _INTERNAL_VECTOR2D
	#define _INTERNAL_BASECUSTOM_
#endif

#include "customgui_base.h"
#include "c4d_basecontainer.h"
#include "c4d_customdatatype.h"
#include "lib_description.h"

#define CUSTOMGUI_VECTOR2D								200000101

#define VECTOR2D_BORDER										'brdr'
#define VECTOR2D_VERTICAL									'vert'
#define VECTOR2D_XYZCOMBO									'xyzc'

class BaseList2D;

class Vector2dCustomGui : public BaseCustomGui<CUSTOMGUI_VECTOR2D>
{
	private:
		Vector2dCustomGui();
		~Vector2dCustomGui();

	public:
};





// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#ifndef _INTERNAL_VECTOR2D
	class iVector2dCustomGui : public iBaseCustomGui
	{
		iVector2dCustomGui(const BaseContainer &settings,CUSTOMGUIPLUGIN *plugin) : iBaseCustomGui(settings,plugin) { }
	};
#else
	class iVector2dCustomGui;
#endif

struct Vector2dLib : public BaseCustomGuiLib
{
//	Bool		(iVector2dCustomGui::*SetImageA			)(BaseBitmap *bmp,Bool copybmp,Bool secondstate);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif
