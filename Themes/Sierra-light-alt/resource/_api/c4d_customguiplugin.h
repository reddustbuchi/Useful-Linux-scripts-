/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4D_CUSTOMGUIPLUGIN_H
#define __C4D_CUSTOMGUIPLUGIN_H

#include "ge_math.h"
#include "c4d_customguidata.h"
#include "c4d_baseplugin.h"

struct CUSTOMGUIPLUGIN : public STATICPLUGIN
{
	CDialog*						(CustomGuiData::*Alloc							)(const BaseContainer &settings);
	void								(CustomGuiData::*Free								)(CDialog *dlg,void *userdata);
	const Char*					(CustomGuiData::*GetResourceSym			)();
	CustomProperty*			(CustomGuiData::*GetProperties			)();
	Int32								(CustomGuiData::*GetResourceDataType)(Int32 *&table);

	void*	reserved[(32-5)*C4DPL_MEMBERMULTIPLIER];
};

CUSTOMGUIPLUGIN *FindCustomGuiPlugin(Int32 type);

#define CallCustomGuiCmd(plug,fnc) (((CustomGuiData*)(((CUSTOMGUIPLUGIN *)plug->GetPluginStructure())->adr))->*((CUSTOMGUIPLUGIN *)plug->GetPluginStructure())->fnc)

#endif
