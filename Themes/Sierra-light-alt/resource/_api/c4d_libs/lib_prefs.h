/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _LIB_PREFS_H_
#define _LIB_PREFS_H_

#include "c4d_library.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"
#include "c4d_nodedata.h"
#include "c4d_nodeplugin.h"
#include "lib_description.h"

#define PREFS_PRI_COMMON			10000200
#define PREFS_PRI_DOCUMENT		10000190
#define PREFS_PRI_INTERFACE		10000180
#define PREFS_PRI_THEME				10000170
#define PREFS_PRI_MOUSE				10000160
#define PREFS_PRI_OPENGL			10000150
#define PREFS_PRI_VIEWPORT		10000140
#define PREFS_PRI_FILES				10000130
#define PREFS_PRI_UNITS				10000120
#define PREFS_PRI_MEMORY			10000110
#define PREFS_PRI_INTERNET		10000100
#define PREFS_PRI_RENDER			10000090
#define PREFS_PRI_BODYPAINT3D	10000080
#define PREFS_PRI_MODULES			10000070
#define PREFS_PRI_IMEXPORT		10000060
#define PREFS_PRI_ADVANCED		10000050
#define PREFS_PRI_NET					10000040

#define	MSG_UPDATE_PREFERENCE_DLG	1022551

class CDialog;
class SubDialog;

// public stuff
struct PrefsDialogHook
{
	void *thisptr;

	CDialog *(*SubDialog_Alloc    )(PrefsDialogHook *thi,void *&userdata);
	void    (*SubDialog_Free      )(PrefsDialogHook *thi,void *userdata);
	void		(*SubDialog_EditStart )(PrefsDialogHook *thi,void *userdata,BaseContainer *bc);
	void		(*SubDialog_EditApply	)(PrefsDialogHook *thi,void *userdata,const BaseContainer &originaldata);
	void		(*SubDialog_EditUndo	)(PrefsDialogHook *thi,void *userdata,const BaseContainer &originaldata);
	void		(*InitPrefs						)(PrefsDialogHook *thi,BaseContainer *bc);
};

Bool PrefsLib_InitPrefs();
Bool PrefsLib_OpenDialog(Int32 page);

// helper function for InitPrefs Callback
inline void CheckPrefsData(BaseContainer *worldcontainer,Int32 containerid, const GeData &defaultvalue)
{
	if (!worldcontainer) return;
#ifdef __API_INTERN__
	if (worldcontainer->GetDataPointer(containerid)!=nullptr) return;
#else
	if (worldcontainer->FindIndex(containerid)!=NOTOK) return;
#endif
	worldcontainer->SetData(containerid,defaultvalue);
}

struct PrefsMapTable
{
	Int32 guiid;
	Int32 prefsid;
};

class PrefsDialogObject : public NodeData
{
protected:

	void SetPrefsValue(Int32 id, const GeData &data, DESCFLAGS_SET &flags, Bool refresh = false);
	void SetPrefsValue(Int32 id, Int32 data, DESCFLAGS_SET &flags, const PrefsMapTable *table);
	void GetPrefsValue(Int32 id, GeData &data, DESCFLAGS_GET &flags);
	void GetPrefsValue(Int32 id, GeData &data, DESCFLAGS_GET &flags, const PrefsMapTable *table);

	void InitPrefsValue(Int32 id,const GeData &data, Description* desc,const DescID &descid,  BaseContainer* pBC = nullptr);

	virtual Bool InitValues(const DescID &id, Description *description = nullptr) {return true;}

public:

	enum
	{
		IDPREFS_SORTID = 700,
		IDPREFS_PARENTID
	};

	PrefsDialogObject();

	static BasePlugin* Register(Int32 id, DataAllocator *allocfunc, const String &name, const String &description, Int32 parentid, Int32 sortid);

	virtual GeListNode* GetMappedObject() { return nullptr; }
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#define LIBRARY_PREFS					1000466

struct PrefsLib : public C4DLibrary
{
	Bool		(*PrefsLib_InitPrefs	)();
	Bool		(*PrefsLib_OpenDialog )(Int32 page);
};

struct PREFSPLUGIN : public NODEPLUGIN
{
	BaseBitmap		*icon;

	void*	reserved[(32-0)*C4DPL_MEMBERMULTIPLIER-1];
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif
