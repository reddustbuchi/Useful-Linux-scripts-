/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _CUSTOMGUI_UNITSCALE_H_
#define _CUSTOMGUI_UNITSCALE_H_

#include "customgui_base.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"
#include "c4d_customdatatype.h"



#define CUSTOMGUI_UNITSCALE               200000274
#define CUSTOMDATATYPE_UNITSCALE      		200000275

// subdesc ids
#define UNITSCALE_SCALE		1 // real
#define UNITSCALE_UNIT		2 // long

enum DOCUMENT_UNIT
{
	DOCUMENT_UNIT_UNDEF								= 0,
	DOCUMENT_UNIT_KM									= 1,
	DOCUMENT_UNIT_M										= 2,
	DOCUMENT_UNIT_CM									= 3,
	DOCUMENT_UNIT_MM									= 4,
	DOCUMENT_UNIT_MICRO								= 5,
	DOCUMENT_UNIT_NM									= 6,
	DOCUMENT_UNIT_MILE								= 7,
	DOCUMENT_UNIT_YARD								= 8,
	DOCUMENT_UNIT_FOOT								= 9,
	DOCUMENT_UNIT_INCH								= 10
} ENUM_END_LIST(DOCUMENT_UNIT);

class UnitScaleCustomGui : public BaseCustomGui<CUSTOMGUI_UNITSCALE>
{
private:
	UnitScaleCustomGui();
	~UnitScaleCustomGui();
public:
	Bool SetValue(const UnitScaleData *data); // returns false on valueID <-> data type mismatch
	Bool GetValue(UnitScaleData *data) const;
};

class UnitScaleData : public CustomDataType
{
private:
	UnitScaleData();
	~UnitScaleData();
public:
	Bool SetUnitScale(Float scale, DOCUMENT_UNIT unit); // same like above
	Bool GetUnitScale(Float &scale, DOCUMENT_UNIT &unit) const;
	Bool operator == (const UnitScaleData& b) const;
	Bool operator != (const UnitScaleData& b) const;

	static UnitScaleData* Alloc();
	static void Free(UnitScaleData *&data);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF


#ifndef _INTERNAL_DEF_
	class iUnitScaleCustomGui : public iBaseCustomGui
	{
		iUnitScaleCustomGui(const BaseContainer &settings,CUSTOMGUIPLUGIN *plugin) : iBaseCustomGui(settings,plugin) { }
	};
	class iUnitScaleData {};
#else
	class iUnitScaleCustomGui;
	class iUnitScaleData;
#endif

struct UnitScaleCustomGuiLib : public BaseCustomGuiLib
{
	Bool    				(iUnitScaleCustomGui::*SetValue)(const UnitScaleData *data);
	Bool						(iUnitScaleCustomGui::*GetValue)(UnitScaleData *data) const;
	Bool    				(iUnitScaleData::*SetUnitScale)(Float scale, DOCUMENT_UNIT unit);
	Bool						(iUnitScaleData::*GetUnitScale)(Float &scale, DOCUMENT_UNIT &unit) const;
	Bool						(iUnitScaleData::*UnitScaleEqual)(const iUnitScaleData &b) const;
	UnitScaleData*	(*iUnitScaleData_Alloc)();
	void						(*iUnitScaleData_Free)(UnitScaleData *&data);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF


#endif
