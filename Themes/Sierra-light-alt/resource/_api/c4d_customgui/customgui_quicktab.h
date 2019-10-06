/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _CUSTOMGUI_QUICKTAB_H_
#define _CUSTOMGUI_QUICKTAB_H_

#ifdef _INTERNAL_QUICKTAB_
	#define _INTERNAL_BASECUSTOM_
#endif

#include "customgui_base.h"
#include "c4d_basecontainer.h"



#define CUSTOMGUI_QUICKTAB				1000495 // user gadget


#define QUICKTAB_BAR							C4D_FOUR_BYTE(0,'b','a','r')  // Bool
#define QUICKTAB_BARTITLE					'btit' // String
#define QUICKTAB_SHOWSINGLE				'ssgl' // Bool
#define QUICKTAB_SPRINGINGFOLDERS	'sprn' // Bool: d&d springing folder like
#define QUICKTAB_SEPARATOR				'sepa' // Bool: draw separator?
#define QUICKTAB_BARSUBGROUP			'subg' // Bool: handle as subgroup
#define QUICKTAB_BARLAYERCOLOR		'lycl' // Bool: show layer color
#define QUICKTAB_NOLINEBREAK			'nobk' // Bool: no line break for tabs inside scrollgroups
#define QUICKTAB_BGCOLOR					'bgco' // Vector/Int32: Color RGB or ID
#define QUICKTAB_NOMULTISELECT		'noml' // Bool: no multiple selection
#define QUICKTAB_ALTERNATIVECOLOR 'altc' // Int32: use an alternative color (colorid from colorprefs)

class QuickTabCustomGui : public BaseCustomGui<CUSTOMGUI_QUICKTAB>
{
		QuickTabCustomGui();
		~QuickTabCustomGui();

	public:

		void ClearStrings();
		void AppendString(Int32 id,const String &str,Bool checked);
		void DoLayoutChange();
		Bool IsSelected(Int32 id);
		void SetTextColor(Int32 id,Int32 col);
		void SetLayerColor(Int32 id,Bool show, const Vector &col);
		Bool Select(Int32 id, Bool b);
};





// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#ifndef _INTERNAL_QUICKTAB_
	class iQuickTabCustomGui : public iBaseCustomGui
	{
		iQuickTabCustomGui(const BaseContainer &settings,CUSTOMGUIPLUGIN *plugin) : iBaseCustomGui(settings,plugin) { }
	};
#else
	class iQuickTabCustomGui;
#endif

struct QuickTabLib : public BaseCustomGuiLib
{
	void		(iQuickTabCustomGui::*ClearStrings		)();
	void		(iQuickTabCustomGui::*AppendString		)(Int32 id,const String &str,Bool checked);
	void		(iQuickTabCustomGui::*DoLayoutChange	)();
	Bool		(iQuickTabCustomGui::*IsSelected			)(Int32 id);
	void		(iQuickTabCustomGui::*SetTextColor		)(Int32 id,Int32 col);
	Bool		(iQuickTabCustomGui::*Select		      )(Int32 id, Bool b);
	void		(iQuickTabCustomGui::*SetLayerColor		)(Int32 id,Bool show, const Vector &col);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif
