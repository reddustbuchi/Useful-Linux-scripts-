/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _GUI_TEXBOX_H_
#define _GUI_TEXBOX_H_

#include "customgui_base.h"
#include "c4d_basecontainer.h"

#define CUSTOMGUI_TEXBOX                1001066

#define TEXBOX_POPUP_ONLY               'tbpo'      // Bool
#define TEXBOX_ALPHAMODE								'talp'      // Bool

class TexBoxGui : public BaseCustomGui<CUSTOMGUI_TEXBOX>
{
		TexBoxGui();
		~TexBoxGui();

	public:
		BaseList2D* GetLink(const BaseDocument* doc);
		BaseList2D* GetLink(const BaseDocument* doc, Int32 type);
		Bool SetLink(const BaseList2D* obj);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#ifndef _INTERNAL_TEXBOX_DEF_
	class iTexBoxGui
	{
	};
#else
	class iTexBoxGui;
#endif

struct CustomGuiTexBoxLib : public BaseCustomGuiLib
{
	BaseList2D* (iTexBoxGui::*GetLink)(const BaseDocument* doc);
	BaseList2D* (iTexBoxGui::*GetLinkType)(const BaseDocument* doc, Int32 type);
	Bool        (iTexBoxGui::*SetLink)(const BaseList2D* obj);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif // _GUI_LINKBOX_H_
