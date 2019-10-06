#include "c4d_commandplugin.h"
#include "c4d_memory.h"
#include "c4d_basebitmap.h"
#include "c4d_file.h"
#include "c4d_general.h"
#include "c4d_gui.h"

Bool CommandData::Execute(BaseDocument* doc)
{
	return true;
}

Int32 CommandData::GetState(BaseDocument* doc)
{
	return CMD_ENABLED;
}

Bool CommandData::RestoreLayout(void* secret)
{
	return true;
}

Bool CommandData::Message(Int32 type, void* data)
{
	return true;
}

String CommandData::GetScriptName(void)
{
	return String();
}

Bool CommandData::ExecuteSubID(BaseDocument* doc, Int32 subid)
{
	return false;
}

Bool CommandData::ExecuteOptionID(BaseDocument* doc, Int32 plugid, Int32 subid)
{
	return false;
}

Bool CommandData::GetSubContainer(BaseDocument* doc, BaseContainer& submenu)
{
	return false;
}

#ifndef __API_INTERN__
Bool RegisterCommandPlugin(Int32 id, const String& str, Int32 info, String iconname, const String& help, CommandData* dat)
{
	if (!dat)
		return false;

	Bool ok = false;

	if (iconname.Content())
	{
		AutoAlloc<BaseBitmap> icon;
		if (icon && icon->Init(GeGetPluginPath() + String("res") + iconname) == IMAGERESULT_OK)
			ok = RegisterCommandPlugin(id, str, info, icon, help, dat);
	}
	else
	{
		ok = RegisterCommandPlugin(id, str, info, nullptr, help, dat);
	}

	return ok;
}
#endif

Bool RegisterCommandPlugin(Int32 id, const String& str, Int32 info, BaseBitmap* icon, const String& help, CommandData* dat)
{
	if (!dat)
		return false;

	COMMANDPLUGIN np;
	ClearMem(&np, sizeof(np));

	np.adr	= dat;
	np.help	= (String*)&help;
	np.command_icon	= icon;
	np.info	= info;
	np.Destructor	= &CommandData::Destructor;
	np.Execute	= &CommandData::Execute;
	np.GetState	= &CommandData::GetState;
	np.RestoreLayout = &CommandData::RestoreLayout;
	np.Message = &CommandData::Message;
	np.GetScriptName = &CommandData::GetScriptName;
	np.GetSubContainer = &CommandData::GetSubContainer;
	np.ExecuteSubID = &CommandData::ExecuteSubID;
	np.ExecuteOptionID = &CommandData::ExecuteOptionID;

	return GeRegisterPlugin(PLUGINTYPE_COMMAND, id, str, &np, sizeof(np));
}

Bool RegisterManagerInformation(Int32 id, const String& str, Int32 info)
{
	MANAGERINFORMATION np;
	ClearMem(&np, sizeof(np));

	np.adr	= nullptr;
	np.info	= info;

	return GeRegisterPlugin(PLUGINTYPE_MANAGERINFORMATION, id, str, &np, sizeof(np));
}
