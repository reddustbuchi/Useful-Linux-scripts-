/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _CUSTOMGUI_LENSGLOW_H_
#define _CUSTOMGUI_LENSGLOW_H_

#include "c4d_library.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"
#include "c4d_customdatatype.h"
#include "customgui_base.h"


#define CUSTOMGUI_LENSGLOW			1000996
#define CUSTOMDATATYPE_LENSGLOW 1000997

#define MAXGLOW_CNT		5
#define MAXSTREAK_CNT	5

struct Streak
{
	Bool		random,randomlen,star;
	Int32		cnt,holecnt;
	Float		size,sv,holewidth,thickness,rot;
	Vector	col;
	Int32		type;
};

struct Glow
{
	Float		size,sv;
	Vector	col;
	Int32		type;
};

struct Halo
{
	Float		size,sv;
	Vector	col;
	Int32		type;
};

class LensGlowStruct : public CustomDataType
{
	public:
		Glow	 glow  [MAXGLOW_CNT];
		Streak streak[MAXSTREAK_CNT];
		Halo	 halo;
};

class LensGlowCustomGui : public BaseCustomGui<CUSTOMGUI_LENSGLOW>
{
		LensGlowCustomGui();
		~LensGlowCustomGui();
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#ifndef _INTERNAL_DEF_
	class iLensGlowCustomGui
	{
	};
#else
	class iLensGlowCustomGui;
#endif

struct CustomGuiLensGlowLib : public BaseCustomGuiLib
{
};

#endif
