#ifndef _C4D_BASELINK_ARRAY_H_
#define _C4D_BASELINK_ARRAY_H_

#ifdef __API_INTERN__
	#include "c4d_alias.h"
#endif

#include "ge_autoptr.h"
#include "c4d_misc.h"
#ifdef USE_API_MAXON
	#include "basearray.h"
#endif

class BaseLinkArray : public maxon::BaseArray<BaseLink*>
{
public:
	~BaseLinkArray()
	{
		FlushAll();
	}

	void FlushAll()
	{
		BaseLink* c; Int32 i;

		for (i = 0; i < GetCount(); ++i)
		{
			c = (*this)[i];
			if (!c)
				continue;
			BaseLink::Free(c);
		}
		Reset();
	}

	Int32 Find(C4DAtomGoal* bl, BaseDocument* doc) const
	{
		Int32 i;
		for (i = 0; i < GetCount(); i++)
		{
			BaseLink* l = (*this)[i];
			if (!l)
				continue;
			C4DAtomGoal* b = l->GetLink(doc);
			if (!b)
				continue;
			if (b == bl)
				return i;
		}
		return NOTOK;
	}

	BaseLink* GetIndexLink(Int32 i) const
	{
		if (i < 0 || i >= GetCount())
			return nullptr;

		return (*this)[i];
	}

	C4DAtomGoal* GetIndex(Int32 i, BaseDocument* doc) const
	{
		if (i < 0 || i >= GetCount())
			return nullptr;

		BaseLink* l = (*this)[i];
		if (!l)
			return nullptr;
		return l->GetLinkAtom(doc);
	}

	BaseList2D* GetIndexBl(Int32 i, BaseDocument* doc, Int32 instanceof = Tbaselist2d) const
	{
		if (i < 0 || i >= GetCount())
			return nullptr;

		BaseLink* l = (*this)[i];
		if (!l)
			return nullptr;
		return (BaseList2D*)l->GetLinkAtom(doc, instanceof);
	}

	Bool Remove(Int32 n)
	{
		if (n < 0 || n >= GetCount())
			return false;

		BaseLink* l = (*this)[n];
		if (l)
			BaseLink::Free(l);

		Erase(n);

		return true;
	}

	Bool Append(C4DAtomGoal* bl)
	{
		BaseLink* l = BaseLink::Alloc();
		if (!l)
			return false;
		l->SetLink(bl);
		return maxon::BaseArray<BaseLink*>::Append(l) != nullptr;
	}

	Int32 GetRealCount(BaseDocument* doc) const
	{
		Int32 realcnt = 0;
		Int32 i, cnt = GetCount();
		for (i = 0; i < cnt; i++)
		{
			C4DAtomGoal* bl = GetIndex(i, doc);
			if (bl)
				realcnt++;
		}
		return realcnt;
	}

	void GetAtomArray(BaseDocument* doc, AtomArray& res) const
	{
		Int32 i, cnt = GetCount();
		for (i = 0; i < cnt; i++)
		{
			C4DAtomGoal* bl = GetIndex(i, doc);
			if (bl)
				res.Append(bl);
		}
	}

	void FromAtomArray(const AtomArray& ar)
	{
		FlushAll();
		Int32 i, cnt = ar.GetCount();
		for (i = 0; i < cnt; i++)
		{
			Append((C4DAtomGoal*)ar.GetIndex(i));
		}
	}
};

#endif
