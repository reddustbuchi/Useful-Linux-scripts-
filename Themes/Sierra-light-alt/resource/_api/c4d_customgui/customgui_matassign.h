/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _CUSTOMGUI_MATASSIGN_H_
#define _CUSTOMGUI_MATASSIGN_H_

#include "customgui_base.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"
#include "c4d_customdatatype.h"

class BaseDocument;

#define CUSTOMGUI_MATASSIGN						  200000026
#define CUSTOMDATATYPE_MATASSIGN				200000027

#define MATASSIGN_TAG_ID                1000
#define MATASSIGN_CONTAINER_ID          1001
#define MATASSIGN_MATERIAL_ID           1002

class MatAssignTable;

class MatAssignData : public CustomDataType
{
private:
	MatAssignData();
	~MatAssignData();
public:

	void SetMaterial(const AtomArray &materials);
	Bool InsertObject(BaseList2D* pObject, Int32 lFlags);
	Bool DeleteObject(BaseDocument *doc, BaseList2D* pObject) { return DeleteObject(GetObjectIndex(doc,pObject)); }

	Bool GetMaterial(BaseDocument *doc, AtomArray &materials);
	Int32 GetObjectIndex(BaseDocument *doc, BaseList2D* pObject);
	Int32 GetFlags(Int32 lIndex);
	Int32 GetFlags(BaseDocument *doc, BaseList2D* pObject) { return GetFlags(GetObjectIndex(doc,pObject)); }
	BaseContainer* GetData(Int32 lIndex);
	BaseContainer* GetData(BaseDocument *doc, BaseList2D* pObject) { return GetData(GetObjectIndex(doc, pObject)); }
	BaseList2D* ObjectFromIndex(BaseDocument *doc, Int32 lIndex);

	// returns a table that contains all included objects. Delete the list by calling FreeInclusionTable(table)
	// hierarchy_bit starts at 0
	MatAssignTable *BuildInclusionTable(BaseDocument *doc, Int32 hierarchy_bit = NOTOK);

	Bool DeleteObject(Int32 lIndex);
	Int32 GetObjectCount();
};

class MatAssignTable
{
private:
	MatAssignTable();
	~MatAssignTable();

public:
	Bool Check(BaseList2D *op);
	Int32 GetObjectCount();
	BaseList2D* GetObject(Int32 lIndex);
};

void FreeInclusionTable(MatAssignTable*& pTable);

class MatAssignCustomGui : public BaseCustomGui<CUSTOMGUI_MATASSIGN>
{
private:
	MatAssignCustomGui();
	~MatAssignCustomGui();
public:
};





// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF


#ifndef _INTERNAL_DEF_
	class iMatAssignCustomGui : public iBaseCustomGui
	{
		iMatAssignCustomGui(const BaseContainer &settings,CUSTOMGUIPLUGIN *plugin) : iBaseCustomGui(settings,plugin) { }
	};
	class iMatAssignData {};
	class iMatAssignTable {};
#else
	class iMatAssignCustomGui;
	class iMatAssignData;
	class iMatAssignTable;
#endif

struct CustomGuiMatAssignLib : public BaseCustomGuiLib
{
	Bool            (iMatAssignData::*InsertObject)(BaseList2D* pObject, Int32 lFlags);
	Int32            (iMatAssignData::*GetObjectIndex)(BaseDocument *doc, BaseList2D* pObject);
	Bool            (iMatAssignData::*DeleteObject)(Int32 lIndex);
	Int32            (iMatAssignData::*GetObjectCount)();
	BaseList2D*     (iMatAssignData::*ObjectFromIndex)(BaseDocument *doc, Int32 lIndex);

	Bool            (iMatAssignTable::*Check)(BaseList2D *op);
	Int32            (iMatAssignTable::*GetObjectCountT)();
	BaseList2D*     (iMatAssignTable::*GetObject)(Int32 lIndex);
	void            (*LIB_FreeInclusionTable)(iMatAssignTable *pTable);
	BaseContainer*  (iMatAssignData::*GetData)(Int32 lIndex);
	void						(iMatAssignData::*SetMaterial)(const AtomArray &materials);
	Bool						(iMatAssignData::*GetMaterial)(BaseDocument *doc,AtomArray &materials);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif // _CUSTOMGUI_MATASSIGN_H_
