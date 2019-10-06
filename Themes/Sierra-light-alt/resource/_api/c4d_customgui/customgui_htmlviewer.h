/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _CUSTOMGUI_HTMLVIEWER_H_
#define _CUSTOMGUI_HTMLVIEWER_H_

#include "customgui_base.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"



#define CUSTOMGUI_HTMLVIEWER 200000114


#define WEBPAGE_GOBACK		0
#define WEBPAGE_GOFORWARD	1
#define WEBPAGE_GOHOME		2
#define WEBPAGE_SEARCH		3
#define WEBPAGE_REFRESH		4
#define WEBPAGE_STOP			5

#define	URL_ENCODING_UTF16		0															// A string containing umlauts and spaces. The last # following the last slash is regarded as start of the anchor (the anchor following the hash mark must be escaped!)
#define	URL_ENCODING_ESCAPED	1															// String contains an escaped url (all umlauts, spaces and other stuff that does not belong there is % according to RFC 2396(?))

typedef void	HtmlViewerCustomGuiURLCallback( void *user_data, const String &url, Int32 encoding, void *reserved );

class HtmlViewerCustomGui : public BaseCustomGui<CUSTOMGUI_HTMLVIEWER>
{
	HtmlViewerCustomGui();
	~HtmlViewerCustomGui();

public:
	void	SetUrl( const String &url, Int32 encoding );
	void	SetText( const String &url );
	void	DoAction( Int32 action );
	void	SetURLCallback( HtmlViewerCustomGuiURLCallback *callback, void *user_data );
	String GetTextArea(const String &id);

	static String FilenameToURL( const Filename &f, Int32 *encoding );
};


// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF


#ifndef _INTERNAL_DEF_
	class iHtmlViewerCustomGui : public iBaseCustomGui
	{
		iHtmlViewerCustomGui(const BaseContainer &settings,CUSTOMGUIPLUGIN *plugin) : iBaseCustomGui(settings,plugin) { }
	};
#else
	class iHtmlViewerCustomGui;
#endif

struct CustomGuiHtmlViewerLib : public BaseCustomGuiLib
{
	void (iHtmlViewerCustomGui::*SetUrl)( const String &url, Int32 encoding );
	void (iHtmlViewerCustomGui::*DoAction)(Int32 action);
	void (iHtmlViewerCustomGui::*SetURLCallback)( HtmlViewerCustomGuiURLCallback *callback, void *user_data );
	void (iHtmlViewerCustomGui::*SetText)( const String &url );
	String (*FilenameToURL)( const Filename &f, Int32 *encoding );
	String (iHtmlViewerCustomGui::*GetTextArea)(const String &id);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif
