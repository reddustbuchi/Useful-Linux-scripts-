/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _C4D_LISTVIEW_H_
#define _C4D_LISTVIEW_H_

#ifndef __API_INTERN__
	#include "operatingsystem.h"
	#include "c4d_string.h"

class GeDialog;

inline void* _ReturnString(const String& v)
{
	String* cpy = C4DOS.St->Alloc();
	if (!cpy)
		return nullptr;
	C4DOS.St->CopyTo(&v, cpy);
	return cpy;
}


struct MouseDownInfo
{
	Int32								 xpos, ypos, width, height;
	Int32								 line, col;

	Float								 mx;
	Float								 my;
	const BaseContainer* msg;
};


	#define ReturnLong(v)		{ res_type = LV_RES_INT; result = (void*)(Int)(v); return; }
	#define ReturnBitmap(v) { res_type = LV_RES_BITMAP; result = (void*)(v); return; }
	#define ReturnNull()		{ res_type = LV_RES_NIL; result = nullptr; return; }
	#define ReturnString(v) { res_type = LV_RES_STRING; result = _ReturnString(v); return; }
	#define ReturnVector(v) { res_type = LV_RES_VECTOR; result = _ReturnVector(v); return; }



class GeListView
{
protected:
	_GeListView* lv;
	GeDialog*		 cd;

public:
	GeListView(void);
	virtual ~GeListView(void);

	virtual void LvCallBack(Int32& res_type, void*& result, void* secret, Int32 cmd, Int32 line, Int32 col, void* data1);

	Int LvCallBackLong(void* secret, Int32 cmd, Int32 line, Int32 col, void* data1);
	void LvSuperCall(Int32& res_type, void*& result, void* secret, Int32 cmd, Int32 line, Int32 col);
	void Redraw(void);
	void DataChanged(void);
	Bool SendParentMessage(const BaseContainer& msg);
	Int32 GetId(void);

	Bool ExtractMouseInfo(void* secret, MouseDownInfo& info, Int32 size);
	Bool ExtractDrawInfo(void* secret, DrawInfo& info, Int32 size);

	Bool AttachListView(GeDialog* cd, Int32 id);

	void ShowCell(Int32 line, Int32 col);
};

// for SetProperty & GetProperty
	#define SLV_MULTIPLESELECTION 1

class SimpleListView : public GeListView
{
public:
	SimpleListView();
	virtual ~SimpleListView();

	Bool SetLayout(Int32 columns, const BaseContainer& data);
	Bool SetItem(Int32 id, const BaseContainer& data);
	Bool GetItem(Int32 id, BaseContainer* data);
	Int32 GetItemCount(void);
	Bool GetItemLine(Int32 num, Int32* id, BaseContainer* data);
	Bool RemoveItem(Int32 id);
	Int32 GetSelection(BaseSelect* selection);
	Bool SetSelection(BaseSelect* selection);
	Int32 GetProperty(Int32 id);
	Bool SetProperty(Int32 id, Int32 val);

	virtual void LvCallBack(Int32& res_type, void*& result, void* secret, Int32 cmd, Int32 line, Int32 col, void* data1);

	void ShowCell(Int32 line, Int32 col);
};

#else

	#include "c4d_gui.h"
	#include "intbaselist.h"

	#define GeListView		 _GeListView
	#define SimpleListView _SimpleListView

	#include "operatingsystem.h"
	#include "baseselect.h"


class SimpleListNode;


struct MouseDownInfo
{
	Int32								 xpos, ypos, width, height;
	Int32								 line, col;

	Float								 mx;
	Float								 my;
	const BaseContainer* msg;
};



	#define ReturnLong(v)		{ res_type = LV_RES_INT; result = (void*)(Int)(v); return; }
	#define ReturnBitmap(v) { res_type = LV_RES_BITMAP; result = (void*)(v); return; }
	#define ReturnString(v) { res_type = LV_RES_STRING; result = (void*)NewObjClear(String, v); return; }
	#define ReturnNull()		{ res_type = LV_RES_NIL; result = nullptr; return; }
	#define ReturnVector(v) { res_type = LV_RES_VECTOR; result = (void*)NewObjClear(Vector, v); return; }


class GeListView
{
	friend class GeDialog;

private:
	CUserArea*				cu;
	ListViewCallBack* callback;
	void*							userdata;

public:
	GeListView(void);
	virtual ~GeListView(void);

	virtual void LvCallBack(Int32& res_type, void*& result, void* secret, Int32 cmd, Int32 line, Int32 col, void* data1);

	Int LvCallBackLong(void* secret, Int32 cmd, Int32 line, Int32 col, void* data1);
	void LvSuperCall(Int32& res_type, void*& result, void* secret, Int32 cmd, Int32 line, Int32 col);

	void Redraw(void);
	void DataChanged(void);
	void ShowCell(Int32 id, Int32 col);

	Bool SendParentMessage(BaseContainer* msg);
	Bool ExtractMouseInfo(void* secret, MouseDownInfo& info, Int32 size);
	Bool ExtractDrawInfo(void* secret, DrawInfo& info, Int32 size);
	Int32 GetId(void);

	Bool AttachListView(CDialog* cd, Int32 id, ListViewCallBack* callback = nullptr, void* userdata = nullptr);
};



class SimpleRoot : public GeListHead
{
public:
	Int32 GetCount(void);
	SimpleListNode* FindId(Int32 id);
	SimpleListNode* GetNumber(Int32 num);
	Int32 GetNumber(SimpleListNode* node);
};

// for SetProperty & GetProperty
	#define SLV_MULTIPLESELECTION 1

class SimpleListView : public GeListView
{
	BaseSelect select;
	Int32			 focus;

	Int32			 columns;
	Int32*		 layout;
	Int32*		 colidx;
	Bool			 multipleselection;

	SimpleRoot items;

public:
	SimpleListView();
	virtual ~SimpleListView();

	Bool SetLayout(Int32 columns, const BaseContainer& data);
	Bool SetItem(Int32 id, const BaseContainer& data);
	Bool GetItem(Int32 id, BaseContainer* data);
	Int32 GetItemCount(void);
	Bool GetItemLine(Int32 num, Int32* id, BaseContainer* data);

	Bool SetProperty(Int32 id, Int32 val);
	Int32 GetProperty(Int32 id);

	Bool RemoveItem(Int32 id);
	Int32 GetSelection(BaseSelect* selection);
	Bool SetSelection(BaseSelect* selection);
	void ShowCell(Int32 line, Int32 col);

	virtual void LvCallBack(Int32& res_type, void*& result, void* secret, Int32 cmd, Int32 line, Int32 col, void* data1);
};

#endif

#endif
