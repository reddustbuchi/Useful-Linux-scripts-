/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4D_COMMANDDATA_H
#define __C4D_COMMANDDATA_H

#include "c4d_basedata.h"

class String;
class BaseContainer;
class BaseDocument;
class BaseBitmap;

struct RestoreLayoutSecret
{
	Int32 subid;
};

#define PLUGINFLAG_COMMAND_HOTKEY				 (1 << 27)
#define PLUGINFLAG_COMMAND_OPTION_DIALOG (1 << 26)
#define PLUGINFLAG_COMMAND_STICKY				 (1 << 25)
#define PLUGINFLAG_COMMAND_ICONGADGET		 (1 << 24)

#define MSG_COMMANDINFORMATION 300001001
#define TOOLHOTKEY_RECEIVER		 200000290	// special tool overwrite for plugins
#define MSG_BODYPAINTEXCHANGE	 300001002

struct CommandInformationData
{
	Int32 command_id;		// read

	Int32 managergroup;	// write
	Int32 parentid;
};

class CommandData : public BaseData
{
public:
	virtual Bool Execute(BaseDocument* doc);
	virtual Bool ExecuteSubID(BaseDocument* doc, Int32 subid);
	virtual Bool ExecuteOptionID(BaseDocument* doc, Int32 plugid, Int32 subid);

	virtual Int32 GetState(BaseDocument* doc);
	virtual Bool GetSubContainer(BaseDocument* doc, BaseContainer& submenu);

	virtual Bool RestoreLayout(void* secret);
	virtual String GetScriptName(void);

	virtual Bool Message(Int32 type, void* data);
};

#ifndef __API_INTERN__
Bool RegisterCommandPlugin(Int32 id, const String& str, Int32 info, BaseBitmap* icon, const String& help, CommandData* dat);
#endif

Bool RegisterManagerInformation(Int32 id, const String& str, Int32 info);

#endif
