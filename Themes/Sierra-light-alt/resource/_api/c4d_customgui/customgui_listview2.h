#ifndef __CUSTOMGUI_LISTVIEW2_H__
#define __CUSTOMGUI_LISTVIEW2_H__

//////////////////////////////////////////////////////////////////////////

//#include "c4d_customguidata.h"
//#include "c4d_string.h"
//#include "c4d_memory.h"
//#include "c4d_gui.h"
//#include "c4d_basecontainer.h"
//#include "c4d_baselist.h"
//#include "c4d_basebitmap.h"
//#include "c4d_baseselect.h"
//#include "c4d_basematerial.h"
//#include "c4d_basedocument.h"
//#include "c4d_baseobject.h"
#include "lib_description.h"
//#include "c4d_general.h"
//#include "c4d_resource.h"
//#include "c4d_colors.h"
#include "customgui_base.h"

//////////////////////////////////////////////////////////////////////////

#define CUSTOMDATA_LISTVIEW	1018397
#define CUSTOMGUI_LISTVIEW 1018398

class iListViewData;

class ListViewData : public CustomDataType
{
private:
	ListViewData();
	~ListViewData();
public:
	static ListViewData* Alloc();
	static void Free(ListViewData *&pData);

	Bool AddItem(Int32 id, const String &name, const GeData &data);
	Bool UpdateItem(Int32 id, const String &name, const GeData &data);
	void RemoveItem(Int32 id);

	Int32 GetCount();
	Int32 GetSelected();
	void Select(Int32 index);

	GeData GetData(Int32 index);
	String GetName(Int32 index);
	Int32 GetID(Int32 index);

	void SetData(Int32 index, const GeData &data);
	void SetName(Int32 index, const String &name);
	void SetID(Int32 index, Int32 id);

	Int32 FindIndex(Int32 id);
};

//////////////////////////////////////////////////////////////////////////

struct CustomGuiListViewLib : public BaseCustomGuiLib
{
	iListViewData *(*Alloc)();
	void (*Free)(iListViewData *&pData);

	Bool (iListViewData::*AddItem)(Int32 id, const String &name, const GeData &data);
	Bool (iListViewData::*UpdateItem)(Int32 id, const String &name, const GeData &data);
	void (iListViewData::*RemoveItem)(Int32 id);
	Int32 (iListViewData::*GetCount)();
	Int32 (iListViewData::*GetSelected)();
	void (iListViewData::*Select)(Int32 index);
	GeData (iListViewData::*GetData)(Int32 index);
	String (iListViewData::*GetName)(Int32 index);
	Int32 (iListViewData::*GetID)(Int32 index);
	void (iListViewData::*SetData)(Int32 index, const GeData &data);
	void (iListViewData::*SetName)(Int32 index, const String &name);
	void (iListViewData::*SetID)(Int32 index, Int32 id);
	Int32 (iListViewData::*FindIndex)(Int32 id);
};

//////////////////////////////////////////////////////////////////////////

#endif // __CUSTOMGUI_LISTVIEW_H__
