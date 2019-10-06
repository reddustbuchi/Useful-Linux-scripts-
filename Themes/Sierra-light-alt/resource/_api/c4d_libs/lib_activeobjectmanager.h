/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _LIB_ACTIVEOBJECTMANAGER_H_
#define _LIB_ACTIVEOBJECTMANAGER_H_

#include "c4d_library.h"
#include "c4d_string.h"
#include "lib_description.h"

class AtomArray;

// predefined Modes
enum ACTIVEOBJECTMODE
{
	ACTIVEOBJECTMODE_NONE,

	ACTIVEOBJECTMODE_OBJECT,
	ACTIVEOBJECTMODE_TAG,
	ACTIVEOBJECTMODE_MATERIAL,
	ACTIVEOBJECTMODE_SHADER,
	ACTIVEOBJECTMODE_NODE,
	ACTIVEOBJECTMODE_TIMELINE,
	ACTIVEOBJECTMODE_FCURVE,
	ACTIVEOBJECTMODE_BITMAPINFO, // for BODYPAINT 2
	ACTIVEOBJECTMODE_TOOL,
	ACTIVEOBJECTMODE_VIEW,
	ACTIVEOBJECTMODE_INFOTAB,
	ACTIVEOBJECTMODE_CAMERA,
	ACTIVEOBJECTMODE_RENDERDATA,
	ACTIVEOBJECTMODE_DOCUMENT,
	ACTIVEOBJECTMODE_MODELING,

	ACTIVEOBJECTMODE_
} ENUM_END_LIST(ACTIVEOBJECTMODE);

typedef GeData MESSAGEHOOK(const BaseContainer &msg,void *data);

struct ActiveModeInfo
{
	ACTIVEOBJECTMODE	id;
	String						name;
	MESSAGEHOOK				*hook;
};

// ids for message hook
#define AOM_MSG_ISENABLED				'aoen'
#define AOM_MSG_GETATOMLIST			'geta'
#define AOM_MSG_GETSUBDIALOG		'osub'
#define AOM_MSG_FREESUBDIALOG		'fsub'

#define ACTIVEOBJECTMANAGER_SETOBJECTS_OPEN						1
#define ACTIVEOBJECTMANAGER_SETOBJECTS_NOMODESWITCH		2

Bool ActiveObjectManager_RegisterMode(ACTIVEOBJECTMODE id,const String &text,MESSAGEHOOK *hook);
void ActiveObjectManager_SetMode(ACTIVEOBJECTMODE id,Bool openmanager);
void ActiveObjectManager_SetObjects(ACTIVEOBJECTMODE id,const AtomArray &objects,Int32 flags, const DescID &activepage=DescID());
void ActiveObjectManager_SetObject(ACTIVEOBJECTMODE id,C4DAtom *op,Int32 flags, const DescID &activepage=DescID());
void ActiveObjectManager_Open();

Bool EditObjectModal(const AtomArray &objects,const String &dlgtitle);
Bool EditObjectModal(C4DAtom *op,const String &dlgtitle);
Bool EditDescription(C4DAtom *bl, const DescID &id);

Bool ActiveObjectManager_GetObjects(ACTIVEOBJECTMODE id,AtomArray &objects);
Bool ActiveObjectManager_GetModeInfo(ACTIVEOBJECTMODE id,ActiveModeInfo &info);
Int32 ActiveObjectManager_GetModeCount();
Bool ActiveObjectManager_GetModeInfoIdx(Int32 idx,ActiveModeInfo &info);
ACTIVEOBJECTMODE ActiveObjectManager_GetLastMode();



// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF


#define LIBRARY_ACTIVEOBJECTMANAGER	1000473

struct ActiveObjectManagerLib : public C4DLibrary
{
	Bool							(*RegisterMode			)(ACTIVEOBJECTMODE id,const String &text,MESSAGEHOOK *hook);
	void							(*SetMode						)(ACTIVEOBJECTMODE id,Bool openmanager);
	void							(*SetObjectsEx			)(ACTIVEOBJECTMODE id,const AtomArray &objects,Int32 flags);
	void							(*Open							)();
	Bool							(*EditObjectModal		)(const AtomArray &objects,const String &dlgtitle);
	Bool							(*EditDescriptionOld)(DynamicDescription *dd,BaseContainer &bc);

	Bool							(*GetObjects				)(ACTIVEOBJECTMODE id,AtomArray &objects);
	Bool							(*GetModeInfo				)(ACTIVEOBJECTMODE id,ActiveModeInfo &info);
	Int32							(*GetModeCount			)();
	Bool							(*GetModeInfoIdx		)(Int32 idx,ActiveModeInfo &info);
	ACTIVEOBJECTMODE	(*GetLastMode				)();
	Bool							(*EditDescription		)(C4DAtom *bl, const DescID &id);
	void							(*SetObjects				)(ACTIVEOBJECTMODE id, const AtomArray &objects, Int32 flags, const DescID &activepage);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif
