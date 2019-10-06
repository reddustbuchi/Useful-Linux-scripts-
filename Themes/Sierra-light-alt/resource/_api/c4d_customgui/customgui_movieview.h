/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _CUSTOMGUI_MOVIEVIEW_H_
#define _CUSTOMGUI_MOVIEVIEW_H_

#include "customgui_base.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"

#define CUSTOMGUI_MOVIEVIEW	1022263

class MovieViewCustomGui : public BaseCustomGui<CUSTOMGUI_MOVIEVIEW>
{
	MovieViewCustomGui();
	~MovieViewCustomGui();

public:
	Bool	SetMovie( const Filename &f );
};


// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF


#ifndef _INTERNAL_DEF_
	class iMovieViewCustomGui : public iBaseCustomGui
	{
		iMovieViewCustomGui(const BaseContainer &settings,CUSTOMGUIPLUGIN *plugin) : iBaseCustomGui(settings,plugin) { }
	};
#else
	class iMovieViewCustomGui;
#endif

struct CustomGuiMovieViewLib : public BaseCustomGuiLib
{
	Bool	(iMovieViewCustomGui::*SetMovie)( const Filename &f );
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif
