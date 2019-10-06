/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DBASESELECT_H
#define __C4DBASESELECT_H

#ifdef __API_INTERN__
	#include "baseselect.h"
#else

#include "operatingsystem.h"
#include "c4d_file.h"

struct BaseSelectData
{
	Int32 a, b;
};

class BaseSelect
{
private:
	BaseSelect();
	~BaseSelect();

public:
	Int32 GetCount(void) const;
	Int32 GetSegments(void) const;

	Bool Select(Int32 num);
	Bool SelectAll(Int32 min, Int32 max);

	Bool Deselect(Int32 num);
	Bool DeselectAll(void);

	Bool Toggle(Int32 num);
	Bool ToggleAll(Int32 min, Int32 max);

	Bool GetRange(Int32 seg, Int32 maxElements, Int32* a, Int32* b) const;	// pass maxElements to make sure the returned values for a and b are < maxElements or LIMIT<Int32>::MAX for no additional checks

	Bool IsSelected(Int32 num) const { return C4DOS.Bs->IsSelected(this, num); }

	Bool CopyTo(BaseSelect* dest) const;
	Bool Merge(const BaseSelect* src);
	Bool Deselect(const BaseSelect* src);
	Bool Cross(const BaseSelect* src);
	BaseSelect* GetClone(void) const;

	Bool FromArray(UChar* selection, Int32 count);
	UChar* ToArray(Int32 count) const;

	void Write(HyperFile* hf);
	Bool Read(HyperFile* hf);

	static BaseSelect* Alloc(void);
	static void Free(BaseSelect*& bs);

	Bool FindSegment(Int32 num, Int32* segment) const { return C4DOS.Bs->FindSegment(this, num, segment); }
	BaseSelectData* GetData()  { return C4DOS.Bs->GetData(this); }
	Bool CopyFrom(BaseSelectData* ndata, Int32 ncnt) { return C4DOS.Bs->CopyFrom(this, ndata, ncnt); }

	Int32 GetDirty() const { return C4DOS.Bs->GetDirty(this); }

	Int32 GetLastElement(void) const { return C4DOS.Bs->GetLastElement(this); }
};

#endif

#endif
