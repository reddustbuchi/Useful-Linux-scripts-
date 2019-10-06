/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _CUSTOMGUI_PRIORITY_H_
#define _CUSTOMGUI_PRIORITY_H_

#include "customgui_base.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"
#include "c4d_customdatatype.h"



#define CUSTOMGUI_PRIORITY                1009364
#define CUSTOMGUI_PRIORITY_DATA       		1009369

#define PRIORITY_FLAG_NOCAMERA						1000

#define PRIORITYVALUE_MODE								0
#define PRIORITYVALUE_PRIORITY						1
#define PRIORITYVALUE_CAMERADEPENDENT			2

#define CYCLE_INITIAL                     0
#define CYCLE_ANIMATION                   1
#define CYCLE_EXPRESSION                  2
#define CYCLE_DYNAMICS                    3
#define CYCLE_GENERATORS                  4

class PriorityCustomGui : public BaseCustomGui<CUSTOMGUI_PRIORITY>
{
private:
	PriorityCustomGui();
	~PriorityCustomGui();
public:
	Bool SetValue(Int32 lValueID, const GeData &data); // returns false on valueID <-> data type mismatch
	GeData GetValue(Int32 lValueID) const;
};

class PriorityData : public CustomDataType
{
private:
	PriorityData();
	~PriorityData();
public:
	Bool SetPriorityValue(Int32 lValueID, const GeData &data); // same like above
	GeData GetPriorityValue(Int32 lValueID) const;
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF


#ifndef _INTERNAL_DEF_
	class iPriorityCustomGui : public iBaseCustomGui
	{
		iPriorityCustomGui(const BaseContainer &settings,CUSTOMGUIPLUGIN *plugin) : iBaseCustomGui(settings,plugin) { }
	};
	class iPriorityData {};
#else
	class iPriorityCustomGui;
	class iPriorityData;
#endif

struct PriorityCustomGuiLib : public BaseCustomGuiLib
{
	Bool    (iPriorityCustomGui::*SetValue)(Int32 lValueID, const GeData &data);
	GeData  (iPriorityCustomGui::*GetValue)(Int32 lValueID) const;
	Bool    (iPriorityData::*SetPriorityValue)(Int32 lValueID, const GeData &data);
	GeData  (iPriorityData::*GetPriorityValue)(Int32 lValueID) const;
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF


#endif
