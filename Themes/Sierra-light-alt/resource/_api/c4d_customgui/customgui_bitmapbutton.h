/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _CUSTOMGUI_BITMAPBUTTON_H_
#define _CUSTOMGUI_BITMAPBUTTON_H_

#ifdef _INTERNAL_BITMAPBUTTON_
	#define _INTERNAL_BASECUSTOM_
#endif

#include "customgui_base.h"
#include "c4d_basecontainer.h"
#include "c4d_customdatatype.h"
#include "lib_description.h"

#define CUSTOMGUI_BITMAPBUTTON			1000479
#define CUSTOMDATATYPE_BITMAPBUTTON 1001053

#define BITMAPBUTTON_BORDER								'brdr'
#define BITMAPBUTTON_BUTTON								'butt'
#define BITMAPBUTTON_TOGGLE								'togg'
#define BITMAPBUTTON_IGNORE_BITMAP_WIDTH	'ignw'
#define BITMAPBUTTON_IGNORE_BITMAP_HEIGHT	'ignh'
#define BITMAPBUTTON_DRAWPOPUPBUTTON			'popu'
#define BITMAPBUTTON_TOOLTIP							'ttip'
#define BITMAPBUTTON_ICONID1							'ico1'
#define BITMAPBUTTON_ICONID2							'ico2'
#define BITMAPBUTTON_FORCE_SIZE						'size'
#define BITMAPBUTTON_SPECIAL							'spec'
#define BITMAPBUTTON_NOBORDERDRAW					'nbrd'
#define BITMAPBUTTON_OUTBORDER						'obrd'
#define BITMAPBUTTON_BACKCOLOR						'bkcl'
#define BITMAPBUTTON_MIRROR								'mirr'

class BaseList2D;

class BitmapButtonStruct : public CustomDataType
{
	public:
		BitmapButtonStruct() { op=nullptr; dirty=reserved=0; }
		BitmapButtonStruct(BaseList2D *t_op, const DescID &t_id, Int32 t_dirty) { op=t_op; _id=t_id; dirty=t_dirty; reserved=0; }

		BaseList2D	*op;
		DescID			_id;
		Int32				dirty;
		Int32				reserved;
};

struct BitmapButtonCallback
{
	void	*data;
	void	(*ShowPopup)(void *data);
};

class BitmapButtonCustomGui : public BaseCustomGui<CUSTOMGUI_BITMAPBUTTON>
{
	private:
		BitmapButtonCustomGui();
		~BitmapButtonCustomGui();

	public:

		Bool SetImage(BaseBitmap *bmp,Bool copybmp,Bool secondstate=false);
		Bool SetImage(const Filename &name,Bool secondstate=false);
		Bool SetImage(IconData *bmp,Bool secondstate=false); // implies copy
		Bool SetImage(Int32 icon_id,Bool secondstate=false); // implies copy
		void SetToggleState(Bool set);
		void SetDragArray(const AtomArray *bl);
		void SetCallback(const BitmapButtonCallback &cb);
		void SetCommandDragId(Int32 cmdid);
};





// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#ifndef _INTERNAL_BITMAPBUTTON_
	class iBitmapButtonCustomGui : public iBaseCustomGui
	{
		iBitmapButtonCustomGui(const BaseContainer &settings,CUSTOMGUIPLUGIN *plugin) : iBaseCustomGui(settings,plugin) { }
	};
#else
	class iBitmapButtonCustomGui;
#endif

struct BitmapButtonLib : public BaseCustomGuiLib
{
	Bool		(iBitmapButtonCustomGui::*SetImageA			)(BaseBitmap *bmp,Bool copybmp,Bool secondstate);
	Bool		(iBitmapButtonCustomGui::*SetImageB			)(const Filename &name,Bool secondstate);
	void		(iBitmapButtonCustomGui::*SetToggleState)(Bool set);
	void		(iBitmapButtonCustomGui::*SetDragArray	)(const AtomArray *bl);
	void		(iBitmapButtonCustomGui::*SetCallback		)(const BitmapButtonCallback &cb);
	Bool		(iBitmapButtonCustomGui::*SetImageC			)(IconData *bmp,Bool secondstate);
	void		(iBitmapButtonCustomGui::*SetCommandDragId)(Int32 cmdid);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif
