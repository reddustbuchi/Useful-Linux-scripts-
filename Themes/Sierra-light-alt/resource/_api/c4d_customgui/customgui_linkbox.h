/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _GUI_LINKBOX_H_
#define _GUI_LINKBOX_H_

#include "customgui_base.h"
#include "c4d_basecontainer.h"

#define CUSTOMGUI_LINKBOX                 1009415
#define CUSTOMGUI_INLINE								300001044

enum
{
	LINKBOX_HIDE_ICON         = 10000,
	LINKBOX_LAYERMODE         = 10001
};

#define LINKBOX_ACCEPT_MESSAGE_TYPE         1       // Int32  - the type of the item dragged in the link box
#define LINKBOX_ACCEPT_MESSAGE_ELEMENT      2       // a pointer (BaseList2D*) to the object
#define LINKBOX_ACCEPT_MESSAGE_ACCEPT       3       // a pointer to a Bool, (set this value to true, if you want to accept the object)
#define LINKBOX_ACCEPT_MESSAGE_CONTROL_ID   4       // the ID of the control that sent the message


class LinkBoxGui : public BaseCustomGui<CUSTOMGUI_LINKBOX>
{
		LinkBoxGui();
		~LinkBoxGui();

	public:
		BaseList2D* GetLink(const BaseDocument* doc);
		Bool SetLink(const BaseList2D* obj);
		BaseList2D* GetLink(const BaseDocument* doc, Int32 instance);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#ifndef _INTERNAL_LINKBOX_DEF_
	class iLinkBoxGui
	{
	};
#else
	class iLinkBoxGui;
#endif

struct CustomGuiLinkBoxLib : public BaseCustomGuiLib
{
	BaseList2D* (iLinkBoxGui::*GetLink)(const BaseDocument* doc);
	Bool        (iLinkBoxGui::*SetLink)(const BaseList2D* obj);
	BaseList2D* (iLinkBoxGui::*GetLinkI)(const BaseDocument* doc, Int32 instance);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF


#endif // _GUI_LINKBOX_H_
