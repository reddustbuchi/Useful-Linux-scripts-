/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4D_CUSTOMGUIDATA_H
#define __C4D_CUSTOMGUIDATA_H

#include "c4d_basedata.h"

class String;
class BaseContainer;
class BaseDocument;
class BaseBitmap;
struct CUSTOMGUIPLUGIN;

class CDialog;

// 'info' for CustomGui registration
#define CUSTOMGUI_SUPPORT_LAYOUTSWITCH 1
#define CUSTOMGUI_SUPPORT_LAYOUTDATA	 2

#define CUSTOMGUIARRAY_SIZE(A) (sizeof(A) / sizeof(A[0]))

enum CUSTOMTYPE
{
	CUSTOMTYPE_END,
	CUSTOMTYPE_FLAG,
	CUSTOMTYPE_LONG,
	CUSTOMTYPE_REAL,
	CUSTOMTYPE_STRING,
	CUSTOMTYPE_VECTOR
} ENUM_END_LIST(CUSTOMTYPE);

#define CUSTOMTYPE_HIDE_ID (1 << 30)

struct CustomProperty
{
	CUSTOMTYPE	type;
	Int32				id;	// use CUSTOMTYPE_HIDE_ID to hide this prop in the AM userdata manager (e.g. compatiblity option)
	const Char* ident;
};

class CustomGuiData : public BaseData
{
public:
	virtual Int32 GetId() = 0;
	virtual CDialog*						Alloc(const BaseContainer& settings) = 0;
	virtual void Free(CDialog* dlg, void* userdata) = 0;
	virtual const Char*					GetResourceSym() = 0;
	virtual CustomProperty*			GetProperties();
	virtual Int32	GetResourceDataType(Int32*& table);

	CUSTOMGUIPLUGIN*						GetPlugin();
};

Bool RegisterCustomGuiPlugin(const String& str, Int32 info, CustomGuiData* dat);

#endif
