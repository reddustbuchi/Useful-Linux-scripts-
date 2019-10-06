/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _GUI_LONG_LAT_H_
#define _GUI_LONG_LAT_H_

#include "customgui_base.h"
#include "c4d_basecontainer.h"

#define CUSTOMGUI_LONG_LAT              1011148

#define LONG_LAT_LONGITUDE 1000

class LongLatGui : public BaseCustomGui<CUSTOMGUI_LONG_LAT>
{
private:
	LongLatGui();
	~LongLatGui();
public:
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#ifndef _INTERNAL_LONGLAT_DEF_
	class iLongLatGui
	{
	};
#else
	class iLongLatGui;
#endif

struct CustomGuiLongLatLib : public BaseCustomGuiLib
{
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif // _GUI_LONG_LAT_H_

