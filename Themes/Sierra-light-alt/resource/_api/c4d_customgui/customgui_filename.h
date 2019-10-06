/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _CUSTOMGUI_FILENAME_H_
#define _CUSTOMGUI_FILENAME_H_

#include "customgui_base.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"



#define CUSTOMGUI_FILENAME			1000478
#define FILENAME_DIRECTORY			10000	// Bool directory chooser mode
#define FILENAME_TEXTURE				10001	// Bool texture mode
#define FILENAME_SAVE						10002 // Bool save mode for chooser
#define FILENAME_READONLY				10003 // Bool read only mode for the field
#define FILENAME_NOSELECT					10004 // Bool hide fileselect button



class FilenameCustomGui : public BaseCustomGui<CUSTOMGUI_FILENAME>
{
		FilenameCustomGui();
		~FilenameCustomGui();

	public:
};





// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF


#ifndef _INTERNAL_DEF_
	class iFilenameCustomGui : public iBaseCustomGui
	{
		iFilenameCustomGui(const BaseContainer &settings,CUSTOMGUIPLUGIN *plugin) : iBaseCustomGui(settings,plugin) { }
	};
#else
	class iFilenameCustomGui;
#endif

struct CustomGuiFilenameLib : public BaseCustomGuiLib
{
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif
