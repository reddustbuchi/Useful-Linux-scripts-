/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DNODEDATA_H
#define __C4DNODEDATA_H

#include "c4d_basedata.h"
#include "ge_prepass.h"

class C4DAtom;
class GeListNode;
class HyperFile;
class AliasTrans;
class BaseDocument;
class String;
class Description;
class DescID;
class GeData;
class BaseContainer;
class BaseBitmap;
struct NODEPLUGIN;
struct BranchInfo;

class NodeData : public BaseData
{
protected:
	GeListNode* private_link;

public:
	GeListNode* Get(void) const { return private_link; }

	virtual Bool Init(GeListNode* node);
	virtual void Free(GeListNode* node);
	virtual Bool Read(GeListNode* node, HyperFile* hf, Int32 level);
	virtual Bool Write(GeListNode* node, HyperFile* hf);
	virtual Bool Message(GeListNode* node, Int32 type, void* data);
	virtual Bool CopyTo(NodeData* dest, GeListNode* snode, GeListNode* dnode, COPYFLAGS flags, AliasTrans* trn);
	virtual void GetBubbleHelp(GeListNode* node, String& str);
	virtual BaseDocument* GetDocument(GeListNode* node);
	virtual Int32 GetBranchInfo(GeListNode* node, BranchInfo* info, Int32 max, GETBRANCHINFO flags);
	virtual Bool IsInstanceOf(const GeListNode* node, Int32 type) const;

	virtual Bool GetDDescription(GeListNode* node, Description* description, DESCFLAGS_DESC& flags);
	virtual Bool GetDParameter(GeListNode* node, const DescID& id, GeData& t_data, DESCFLAGS_GET& flags);
	virtual Bool GetDEnabling(GeListNode* node, const DescID& id, const GeData& t_data, DESCFLAGS_ENABLE flags, const BaseContainer* itemdesc);
	virtual Bool SetDParameter(GeListNode* node, const DescID& id, const GeData& t_data, DESCFLAGS_SET& flags);
	virtual Bool TranslateDescID(GeListNode* node, const DescID& id, DescID& res_id, C4DAtom*& res_at);
	virtual Bool IsDocumentRelated(const GeListNode* node, Bool& docrelated) const;
};

typedef NodeData* DataAllocator (void);

void FillNodePlugin(NODEPLUGIN* np, Int32 info, DataAllocator* g, BaseBitmap* icon, Int32 disklevel, void* emulation = nullptr);
Bool RegisterNodePlugin(Int32 id, const String& str, Int32 info, DataAllocator* g, BaseBitmap* icon, Int32 disklevel, Int32* fallback);

#endif
