/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _GERESOURCE_H
#define _GERESOURCE_H

#ifndef __API_INTERN__
	#include "ge_math.h"
	#include "c4d_string.h"
	#include "c4d_file.h"
#else
	#include "ge_math.h"
	#include "ge_string.h"
#endif

class Filename;
class BaseContainer;
class GeData;

class GeResource
{
private:
	class LocalResource * lr;
	Bool			state, glob;
	Filename* initfn;
	Bool			_regardIsStopped;

public:
	GeResource();
	~GeResource();

	Bool Init();
	Bool Init(const Filename& path, Bool regardIsStopped = true);
	Bool InitAsGlobal();
	const String& LoadString(Int32 id);
	Bool ReloadResource();	// dangerous! don't use this in release code!!!
	void Free();

	LocalResource* Get() { return lr; }
};

const String& GeLoadString(Int32 id);
String GeLoadString(Int32 id, const String& p1);
String GeLoadString(Int32 id, const String& p1, const String& p2);
String GeLoadString(Int32 id, const String& p1, const String& p2, const String& p3);
String GeLoadString(Int32 id, const String& p1, const String& p2, const String& p3, const String& p4);

Bool RegisterDescription(Int32 id, const String& idstr, LocalResource* res = nullptr);

BaseContainer* GetMenuResource(const String& menuname);
Bool SearchMenuResource(BaseContainer* bc, const String& searchstr);
GeData* SearchPluginMenuResource(const String& identifier = String("IDS_EDITOR_PLUGINS"));
GeData* SearchPluginSubMenuResource(const String& identifier = String("IDS_EDITOR_PLUGINS"), BaseContainer* bc = nullptr);

void UpdateMenus(void);

extern GeResource resource;
void FreeResource();

#endif
