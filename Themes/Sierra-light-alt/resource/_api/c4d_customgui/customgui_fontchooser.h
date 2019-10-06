/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _FONTCHOOSER_H_
#define _FONTCHOOSER_H_

#define CUSTOMGUI_FONTCHOOSER	1009371
#define FONTCHOOSER_DATA      1009372

#include "customgui_base.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"
#include "c4d_customdatatype.h"

enum
{
	FONTCHOOSER_ENABLE_SIZE = 'size'													// BOOL: true if the size popup should be displayed
};

class FontchooserCustomGui : public BaseCustomGui<CUSTOMGUI_FONTCHOOSER>
{
private:
		FontchooserCustomGui();
		~FontchooserCustomGui();

	public:
		BaseContainer GetFont();
		void SetFont(BaseContainer* bc);
};


class FontData : public CustomDataType
{
private:
	FontData(void);
	~FontData(void);

public:
	BaseContainer GetFont() const;
	void SetFont(BaseContainer *bc);
};


// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF


#ifndef _FONTCHOOSER_INTERNAL_DEF_
	class iFontChooserGUI : public iBaseCustomGui
	{
		iFontChooserGUI(const BaseContainer &settings,CUSTOMGUIPLUGIN *plugin) : iBaseCustomGui(settings,plugin) { }
	};
	class iFontData
	{
	};
#else
	class iFontChooserGUI;
	class iFontData;
#endif

struct FontchooserLib : public BaseCustomGuiLib
{
	BaseContainer    (iFontChooserGUI::*GetFont)() const;
	void             (iFontChooserGUI::*SetFont)(BaseContainer* bc);
	BaseContainer    (iFontData::*GetFontData)() const;
	void             (iFontData::*SetFontData)(BaseContainer* bc);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF


#endif // _FONTCHOOSER_H_
