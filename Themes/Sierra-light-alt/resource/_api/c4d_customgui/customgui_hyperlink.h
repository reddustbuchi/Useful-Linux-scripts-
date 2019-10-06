/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _CUSTOMGUI_HYPERLINK_STATIC_H_
#define _CUSTOMGUI_HYPERLINK_STATIC_H_

#ifdef _INTERNAL_HYPERLINK_STATIC_
	#define _INTERNAL_BASECUSTOM_
#endif

#include "customgui_base.h"
#include "c4d_customguidata.h"
#include "c4d_basecontainer.h"
#include "c4d_customdatatype.h"



#define CUSTOMGUI_HYPER_LINK_STATIC   1009180 // user gadget
#define CUSTOMDATATYPE_HYPER_LINK_STATIC   1009617



//#define HyperLinkStatic_BORDER 'brdr'
//#define HyperLinkStatic_BUTTON 'butt'

#define HYPERLINK_LINK_TEXT     'hllt' // the static text (string ID)
#define HYPERLINK_LINK_DEST     'hlld' // link destination (string ID)
#define HYPERLINK_IS_LINK       'hlil' // true, if this is a real hyperlink, static text otherwise
#define HYPERLINK_ALIGN_LEFT    'hlal'
#define HYPERLINK_ALIGN_RIGHT   'hlar'
#define HYPERLINK_NO_UNDERLINE	'hlnl'


class HyperLinkData : public CustomDataType
{
private:
	HyperLinkData();
	~HyperLinkData();

public:
	void SetStrings(const String* pStrLink, const String* pStrText);
	void GetStrings(String* pStrLink, String* pStrText);
};


class HyperLinkCustomGui : public BaseCustomGui<CUSTOMGUI_HYPER_LINK_STATIC>
{
	private:
		HyperLinkCustomGui();
		~HyperLinkCustomGui();

	public:
		Bool SetLinkString(const String* pStrLink, const String *pStrText);
		Bool GetLinkString(String* pStrLink, String *pStrText);
		Bool SetLinkStringThreaded(const String* pStrLink, const String *pStrText); // only redraw, no layout change
};





// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#ifndef _INTERNAL_HYPERLINK_STATIC_
	class iHyperLinkCustomGui : public iBaseCustomGui
	{
		iHyperLinkCustomGui(const BaseContainer &settings,CUSTOMGUIPLUGIN *plugin) : iBaseCustomGui(settings,plugin) { }
	};
	class iHyperLinkData;
#else
	class iHyperLinkCustomGui;
	class iHyperLinkData;
#endif

struct HyperLinkStaticLib : public BaseCustomGuiLib
{
	Bool		(iHyperLinkCustomGui::*SetLinkString)(const String* pStrLink, const String *pStrText);
	Bool		(iHyperLinkCustomGui::*GetLinkString)(String* pStrLink, String *pStrText);
	void		(iHyperLinkData::*SetStrings)(const String* pStrLink, const String* pStrText);
	void		(iHyperLinkData::*GetStrings)(String* pStrLink, String* pStrText);
	Bool    (iHyperLinkCustomGui::*SetLinkStringThreaded)(const String* pStrLink, const String *pStrText);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif // _CUSTOMGUI_HYPERLINK_STATIC_H_
