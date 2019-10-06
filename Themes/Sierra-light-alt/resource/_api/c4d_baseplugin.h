/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4D_BASEPLUGIN_H
#define __C4D_BASEPLUGIN_H

#include "ge_math.h"
#include "c4d_basedata.h"
#include "c4d_baselist.h"

class String;

#define PLUGINFLAG_HIDE						(1 << 29)
#define PLUGINFLAG_SMALLNODE			(1 << 30)
#define PLUGINFLAG_COFFEE					(1 << 31)
#define PLUGINFLAG_HIDEPLUGINMENU	(1 << 28)
#define PLUGINFLAG_REFRESHALWAYS	(1 << 25)

#ifdef __MAC
	#define C4DPL_MEMBERMULTIPLIER 2
#elif defined __PC
	#define	C4DPL_MEMBERMULTIPLIER 1
#else
	#define	C4DPL_MEMBERMULTIPLIER 2
#endif

struct BASEPLUGIN
{
	Int32	info;

	void	(BaseData::*Destructor)(void);

	void*	reserved[(8 - 1) * C4DPL_MEMBERMULTIPLIER - 1];
};

struct STATICPLUGIN : public BASEPLUGIN
{
	BaseData* adr;

	void*	reserved[(8 - 0) * C4DPL_MEMBERMULTIPLIER - 1];
};

#ifndef __API_INTERN__

class BasePlugin : public BaseList2D
{
private:
	BasePlugin();
	~BasePlugin();

public:
	BasePlugin* GetNext    (void) { return (BasePlugin*)AtCall(GetNext)(); }
	BasePlugin* GetPred    (void) { return (BasePlugin*)AtCall(GetPred)(); }
	BasePlugin* GetUp      (void) { return (BasePlugin*)AtCall(GetUp)(); }
	BasePlugin* GetDown    (void) { return (BasePlugin*)AtCall(GetDown)(); }
	BasePlugin* GetDownLast(void) { return (BasePlugin*)AtCall(GetDownLast)(); }

	// Int32 GetType() inherited
	void*			GetPluginStructure();
	Int32			GetInfo();
	Filename 	GetFilename();
	Int32			GetID();
	PLUGINTYPE GetPluginType() const { return (PLUGINTYPE)GetType(); }
};

class AtomArray;

BasePlugin* FindPlugin(Int32 id, PLUGINTYPE type);
void RemovePlugin(BasePlugin* plug);
BasePlugin*	GetFirstPlugin();
Bool FilterPluginList(AtomArray& arr, PLUGINTYPE type, Bool sortbyname);
void BuildGlobalTagPluginContainer(BaseContainer* plugincontainer, Int32* id);
Int32 ResolveGlobalTagPluginContainer(Int32* id);
Filename* GetLocalFilename();
BasePlugin* CreatePluginEntry(const String& foldername, BasePlugin* bp);
void SetLocalHierarchy(BasePlugin* parent, BasePlugin* pred);

#else
	#include "plugin.h"
#endif

#endif
