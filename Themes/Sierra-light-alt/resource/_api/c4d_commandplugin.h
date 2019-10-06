/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4D_COMMANDPLUGIN_H
#define __C4D_COMMANDPLUGIN_H

#include "ge_math.h"
#include "c4d_commanddata.h"
#include "c4d_baseplugin.h"

struct COMMANDPLUGIN : public STATICPLUGIN
{
	String*			help;
	BaseBitmap* command_icon;

	Bool				(CommandData::*Execute)(BaseDocument* doc);
	Int32				(CommandData::*GetState)(BaseDocument* doc);
	Bool				(CommandData::*RestoreLayout)(void* secret);
	void				(CommandData::*MessageEx)(const BaseContainer& bc);
	String			(CommandData::*GetScriptName)(void);
	Bool				(CommandData::*GetSubContainer)(BaseDocument* doc, BaseContainer& submenu);
	Bool				(CommandData::*ExecuteSubID)(BaseDocument* doc, Int32 subid);
	Bool				(CommandData::*Message)(Int32 type, void* data);
	Bool				(CommandData::*ExecuteOptionID)(BaseDocument* doc, Int32 plugid, Int32 subid);

	void*				reserved[(32 - 9) * C4DPL_MEMBERMULTIPLIER - 2];
};

struct MANAGERINFORMATION : public STATICPLUGIN
{
	Int32 info;

	void*	reserved[32 * C4DPL_MEMBERMULTIPLIER - 1];
};

#endif
