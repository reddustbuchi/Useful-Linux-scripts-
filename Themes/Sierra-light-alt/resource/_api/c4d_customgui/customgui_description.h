/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _CUSTOMGUI_DESCRIPTION_H_
#define _CUSTOMGUI_DESCRIPTION_H_

#include "customgui_base.h"
#include "c4d_basecontainer.h"



#define CUSTOMGUI_DESCRIPTION		1000469 // user gadget



class AtomArray;
class DescID;
class Description;
struct DescriptionGuiLib;

// resourceflags
#define DESCRIPTION_ALLOWFOLDING				'fldg'		// bool: "ALLOWFOLDING"
#define DESCRIPTION_SHOWTITLE						'titl'		// bool: "SHOWTITLE"
#define DESCRIPTION_NOUNDO							'noun'		// bool: "DESCRIPTION_NOUNDO"
#define DESCRIPTION_OBJECTSNOTINDOC			'onid'		// bool: Object are not localted in document (smartpointer thing)
#define DESCRIPTION_MODALMODE						'modl'		// Int32: mode for modal dialogs, 1==normal, 2==no scrollareas
#define DESCRIPTION_LEFTMATEDITREGION		'lmer'		// bool: mode for left materialmanager region
#define DESCRIPTION_STORAGE							'stor'		// BaseContainer*: pointer to layout storage stored as VOID!!!!
#define DESCRIPTION_FOLDERSTORE					'fsto'		// BaseContainer*: pointer to layout storage stored as VOID!!!!
#define DESCRIPTION_SCALE_ALL_ELEMENTS	'sael'		// scale all elements
#define DESCRIPTION_NO_SHOW_SUBCHANNELS	'nssc'		// remove "show subchannels" from the menu
#define DESCRIPTION_OPEN_ALL_GROUPS			'opag'		// opens all groups by default

typedef GeData MasterCallBackFunc(GeDialog *master, const BaseContainer &msg);
#define MCB_NAVIGATIONCHANGED					'navc'
#define MCB_SETATOMARRAY							'seta'

#define MM_HASOBJECTS									'haso'

struct DescriptionFilter
{
	Bool (*FilterID)(const Description *desc, const DescID &id, const BaseContainer &bc, Bool &subfilter, Bool &hide);
};

enum AMFILTERFLAGS
{
	AMFILTERFLAGS_0							= 0,
	AMFILTERFLAGS_SHOWHIDDEN		= 1<<0,
	AMFILTERFLAGS_SHOWANIMONLY	= 1<<1,
	AMFILTERFLAGS_SHOWLOCKED		= 1<<2
} ENUM_END_FLAGS(AMFILTERFLAGS);

#ifndef _INTERNAL_DEF_CUSTOMGUI_DESCRIPTION

class DescriptionCustomGui : public BaseCustomGui<CUSTOMGUI_DESCRIPTION>
{
		DescriptionCustomGui();
		~DescriptionCustomGui();

	public:
		void SetMaster(GeDialog *dlg,MasterCallBackFunc *func);
		GeData MasterMessage(const BaseContainer &msg);

		void SetObjectList(const AtomArray &list);
		void SetObject(C4DAtom *op);

		Bool GetObjectList(AtomArray &list);

		void SetFilter(DescriptionFilter *flt);
		Int32 HighlightDescID(Int32 id, Bool check);
		void SetActiveTabPage(const DescID &activetab);
		Bool GetDescIDSelection(BaseContainer &selection);

		String GetFilterString(AMFILTERFLAGS &flags);
		void SetFilterString(const String &filter, AMFILTERFLAGS flags);
};

#endif

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#if !defined _INTERNAL_DEF_ && !defined __API_INTERN__
	class iDescriptionCustomGui
	{
	};
#else
	class iDescriptionCustomGui;
#endif

struct DescriptionGuiLib : public BaseCustomGuiLib
{
	void			(iDescriptionCustomGui::*SetObjectList)(const AtomArray &list);
	void			(iDescriptionCustomGui::*SetObject)(C4DAtom *op);
	Bool			(iDescriptionCustomGui::*GetObjectList)(AtomArray &list);
	void			(iDescriptionCustomGui::*SetMaster)(GeDialog *dlg,MasterCallBackFunc *func);
	GeData		(iDescriptionCustomGui::*MasterMessage)(const BaseContainer &msg);
	void			(iDescriptionCustomGui::*SetFilter)(DescriptionFilter *flt);
	Int32			(iDescriptionCustomGui::*HighlightDescID)(Int32 id, Bool check);
	void			(iDescriptionCustomGui::*SetActiveTabPage)(const DescID &activetab);
	Bool			(iDescriptionCustomGui::*GetDescIDSelection)(BaseContainer &selection);
	void			(iDescriptionCustomGui::*SetFilterString)(const String &str, AMFILTERFLAGS flags);
	String		(iDescriptionCustomGui::*GetFilterString)(AMFILTERFLAGS &flags);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif
