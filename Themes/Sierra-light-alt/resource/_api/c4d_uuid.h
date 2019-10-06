/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef C4D_C4DUUID_H__
#define C4D_C4DUUID_H__

#ifdef __API_INTERN__
abc def xyz
#endif

#include "ge_math.h"
#include "c4d_misc.h"

#define UuidCall(fnc) (this->*C4DOS.Gu->fnc)

class C4DUuid
{
public:
	// constructors
	C4DUuid()
	{
		C4DOS.Gu->Init(this);
	}

	C4DUuid(_DONTCONSTRUCT n)
	{
	}

	C4DUuid(_EMPTYCONSTRUCT n)
	{
		ClearMem(dummy, C4DUUID_SIZE);
	}

	C4DUuid(const C4DUuid& uid)
	{
		UuidCall(CopyFromUuid) (uid);
	}

	UInt32 GetHashCode() const
	{
		return UuidCall(GetHashCode) ();
	}

	void Reset(Bool clear)
	{
		if (clear)
			ClearMem(dummy, C4DUUID_SIZE);
		else
			C4DOS.Gu->Init(this);
	}

	String GetString() const
	{
		return UuidCall(GetString)();
	}

	Bool Content() const
	{
		return *this != C4DUuid(EC);
	}

	void CopyTo(UChar* buf) const
	{
		UuidCall(CopyTo) (buf);
	}

	void CopyFrom(UChar* buf)
	{
		UuidCall(CopyFrom) (buf);
	}

	Bool CopyFrom(const C4DUuid& src)
	{
		UuidCall(CopyFromUuid) (src);
		return true;
	}

	Bool CopyFrom(const String& uuid)
	{
		return UuidCall(CopyFromString) (uuid);
	}

	void CopyTo(const C4DUuid& dst) const
	{
		UuidCall(CopyToUuid) (dst);
	}

	Bool operator ==(const C4DUuid& k) const
	{
		return UuidCall(Compare) (k);
	}

	Bool operator !=(const C4DUuid& k) const
	{
		return !UuidCall(Compare) (k);
	}

private:
	C4D_RESERVE_PRIVATE_TYPE(UChar, dummy[C4DUUID_SIZE]);

};

#endif	// C4D_C4DUUID_H__
