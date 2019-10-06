/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _CUSTOMGUI_BASE_H_
#define _CUSTOMGUI_BASE_H_

#include "c4d_library.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"
#include "c4d_baseplugin.h"

struct BaseCustomGuiLib;

// general properties for CustomGui's
#define CUSTOMGUI_LAYOUTMODE					'laym'
#define CUSTOMGUI_DEFAULTEDITHEIGHT		'defh'
#define CUSTOMGUI_SAVEDLAYOUTDATA			'slda'

class _BaseCustomGui
{
	private:
		_BaseCustomGui();
		~_BaseCustomGui();

	public:

		Int32 GetWidth(Int32 plugid);
		Int32 GetHeight(Int32 plugid);
		void Redraw(Int32 plugid);
		Bool LayoutChanged(Int32 plugid);
		Bool Activate(Int32 plugid);
		Bool SetDefaultForResEdit(Int32 plugid);
		Bool SetData(Int32 plugid,const TriState<GeData> &tristate);
		TriState<GeData> GetData(Int32 plugid);
		void SetLayoutMode(Int32 plugid,Int32 mode);
		Int32 GetLayoutMode(Int32 plugid);
		Bool SupportLayoutSwitch(Int32 plugid);
};

template <Int32 plugid> class BaseCustomGui : public _BaseCustomGui
{
	private:
		BaseCustomGui();
		~BaseCustomGui();

	public:

		Int32 GetWidth()																		{ return _BaseCustomGui::GetWidth(plugid);	}
		Int32 GetHeight()																	{ return _BaseCustomGui::GetHeight(plugid); }
		void Redraw()																			{ _BaseCustomGui::Redraw(plugid);		}
		Bool LayoutChanged()															{ return _BaseCustomGui::LayoutChanged(plugid); }
		Bool Activate()																		{ return _BaseCustomGui::Activate(plugid); }
		Bool SetDefaultForResEdit()												{ return _BaseCustomGui::SetDefaultForResEdit(plugid); }
		Bool SetData(const TriState<GeData> &tristate)		{	return _BaseCustomGui::SetData(plugid,tristate);}
		TriState<GeData> GetData()												{	return _BaseCustomGui::GetData(plugid);	}
		void SetLayoutMode(Int32 mode)											{	_BaseCustomGui::SetLayoutMode(plugid,mode); }
		Int32 GetLayoutMode()															{	return _BaseCustomGui::GetLayoutMode(plugid);	}
		Bool SupportLayoutSwitch()												{	return _BaseCustomGui::SupportLayoutSwitch(plugid);	}
};


void FillBaseCustomGui(BaseCustomGuiLib &lib);



// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#ifndef _INTERNAL_BASECUSTOM_
	class iBaseCustomGui : public iCustomGui
	{
		public:
			iBaseCustomGui(const BaseContainer &settings,CUSTOMGUIPLUGIN *plugin) : iCustomGui(settings,plugin) { }
			virtual Bool SetObjects(const AtomArray &ar);
	};
#else
	class iBaseCustomGui : public iCustomGui
	{
		public:
			iBaseCustomGui(const BaseContainer &settings,CUSTOMGUIPLUGIN *plugin) : iCustomGui(settings,plugin) { }
			virtual Bool SetObjects(const AtomArray &ar);
	};
#endif

struct BaseCustomGuiLib : public C4DLibrary
{
	void							(iBaseCustomGui::*Redraw								)();
	Bool							(iBaseCustomGui::*LayoutChanged					)();
	Int32							(iBaseCustomGui::*GetWidth							)();
	Int32							(iBaseCustomGui::*GetHeight							)();
	Bool							(iBaseCustomGui::*Activate							)();
	Bool							(iBaseCustomGui::*SetDefaultForResEdit	)();
	Bool							(iBaseCustomGui::*SetData)(const TriState<GeData> &tristate);
	TriState<GeData>	(iBaseCustomGui::*GetData)();
	void							(iBaseCustomGui::*SetLayoutMode)(Int32 mode);
	Int32							(iBaseCustomGui::*GetLayoutMode)();
	Bool							(iBaseCustomGui::*SupportLayoutSwitch)();
	Bool							(iBaseCustomGui::*SetObjects)(const AtomArray &ar);

	void*		reserved[(32-12)*C4DPL_MEMBERMULTIPLIER];
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif
