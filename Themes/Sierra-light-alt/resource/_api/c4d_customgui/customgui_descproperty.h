/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _CUSTOMGUI_DESCRIPTIONPROPERTY_H_
#define _CUSTOMGUI_DESCRIPTIONPROPERTY_H_

#include "customgui_base.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"
#include "lib_description.h"

class AtomArray;

#define CUSTOMGUI_DESCRIPTIONPROPERTY			1000485

#define DESCRIPTIONPROPERTY_SHOWBUTTON					10005 // Bool: show special button
#define DESCRIPTIONPROPERTY_INDENT							10006 // Bool: indent text
#define DESCRIPTIONPROPERTY_BPDOT								10007 // Bool: Use Bodypaint Dot

#define DESCRIPTIONPROPERTY_PARENTMSG						20000

#define SETTING_AUTOIDENT			(1) // ident text if animationsymbol is visible
#define SETTING_HEIGHT				(2) // height

// BFM_ACTION props
#define BFM_ACTION_DP_MENUCLICK		'menu'
#define BFM_ACTION_DP_ADDSELECT		'adds'
#define BFM_ACTION_DP_SUBSELECT		'subs'
#define BFM_ACTION_DP_FOCUS				'dpfc'
#define BFM_ACTION_DP_ANIMCLICK		'anim'
#define BFM_ACTION_DP_BUTTONCLICK	'butt'
#define BFM_ACTION_QUAL						'qual'

// flags for Get/SetState
#define DESCPROP_SEQUENCE						(1<<0)
#define DESCPROP_KEY								(1<<1)
#define DESCPROP_AUTOKEY_ACTIVE			(1<<2)
#define DESCPROP_AUTOKEY_INACTIVE		(1<<3)
#define DESCPROP_NOANIM							(1<<4)
#define DESCPROP_ENABLED						(1<<5)
#define DESCPROP_ANIM_NOT_ALLOWED		(1<<6)
#define DESCPROP_GLOBAL_PARAMETER		(1<<7)
//#define DESCPROP_MAXFONTBIT					(1<<8) // not really needed ITEM#44996 Custom GUI Font
#define DESCPROP_KEY_CHANGED				(1<<9)
#define DESCPROP_HIDDEN							(1<<10)
#define DESCPROP_LOCKED							(1<<11)
#define DESCPROP_KEY_MUTED          (1<<12)
#define DESCPROP_PORTIN							(1<<13)	///< port used by xpresso as inport
#define DESCPROP_PORTIN_CONNECTED		(1<<14)	///< port used by xpresso as connected inport
#define DESCPROP_PORTOUT						(1<<15)	///< port used by xpresso as outport
#define DESCPROP_PORTOUT_CONNECTED	(1<<16)	///< port used by xpresso as connected outport

struct DescPropertyDragData
{
	AtomArray *arr;
	DescID		did;
};

class DescriptionPropertyCustomGui : public BaseCustomGui<CUSTOMGUI_DESCRIPTIONPROPERTY>
{
		DescriptionPropertyCustomGui();
		~DescriptionPropertyCustomGui();

	public:

		void SetDescID(const DescID &id);
		void SetState(Int32 flags);
		Int32 GetState();

		Int32 GetPartCount();
		void GetPartInfo(Int32 part,String &str,DescID &id,Bool &onoff);
		void SetSelection(const DescID &id,Bool onoff);
		void ChangeSettings(const BaseContainer &settings);
};





// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF


#ifndef _INTERNAL_DEF_
	class iDescriptionPropertyCustomGui : public iBaseCustomGui
	{
		iDescriptionPropertyCustomGui(const BaseContainer &settings,CUSTOMGUIPLUGIN *plugin) : iBaseCustomGui(settings,plugin) { }
	};
#else
	class iDescriptionPropertyCustomGui;
#endif

struct CustomGuiDescriptionPropertyLib : public BaseCustomGuiLib
{
	void (iDescriptionPropertyCustomGui::*SetState			)(Int32 flags);
	Int32 (iDescriptionPropertyCustomGui::*GetState			)();
	void (iDescriptionPropertyCustomGui::*SetDescID			)(const DescID &id);
	Int32 (iDescriptionPropertyCustomGui::*GetPartCount	)();
	void (iDescriptionPropertyCustomGui::*GetPartInfo		)(Int32 part,String &str,DescID &id,Bool &onoff);
	void (iDescriptionPropertyCustomGui::*SetSelection	)(const DescID &id,Bool onoff);
	void (iDescriptionPropertyCustomGui::*ChangeSettings)(const BaseContainer &settings);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif
