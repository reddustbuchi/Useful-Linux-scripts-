/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _CUSTOMGUI_TEXTURENAME_H_
#define _CUSTOMGUI_TEXTURENAME_H_

#include "customgui_base.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"



#define CUSTOMGUI_TEXTURENAME			1000484



class TexturenameCustomGui : public BaseCustomGui<CUSTOMGUI_TEXTURENAME>
{
		TexturenameCustomGui();
		~TexturenameCustomGui();

	public:
};





// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF


#ifndef _INTERNAL_DEF_
	class iTexturenameCustomGui : public iBaseCustomGui
	{
		iTexturenameCustomGui(const BaseContainer &settings,CUSTOMGUIPLUGIN *plugin) : iBaseCustomGui(settings,plugin) { }
	};
#else
	class iTexturenameCustomGui;
#endif

struct CustomGuiTexturenameLib : public BaseCustomGuiLib
{
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif
