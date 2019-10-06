/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DBASESOUND_H
#define __C4DBASESOUND_H

#ifdef __API_INTERN__
abc def xyz
#endif

#include "ge_math.h"
#include "c4d_basetime.h"
#include "c4d_baselist.h"

class BaseKey;
class Filename;
class BaseBitmap;
class GeSndInfo;

struct SDataEx
{
	Int16 l;	// left channel
	Int16 r;	// right channel
};

class BaseSound : public C4DAtom
{
private:
	BaseSound();
	~BaseSound();

public:
	BaseSound* GetClone(void);
	Bool CopyTo(BaseSound* dest);

	Bool Init(Int sample_cnt, Float frequency, Int32 channel_cnt);
	void FlushAll(void);
	Bool Load(const Filename& fn);
	Bool Save(const Filename& fn);

	void GetSoundInfo(GeSndInfo* info) const;

	void GetSampleEx(Int32 i, SDataEx* data);
	void SetSampleEx(Int32 i, const SDataEx& data);

	BaseBitmap* GetBitmap(Int32 width, Int32 height, const BaseTime& start, const BaseTime& stop);
	BaseBitmap* GetBitmap(Int32 width, Int32 height, const BaseTime& start, const BaseTime& stop, const Vector& draw_col, const Vector& back_col);

	Bool WriteIt(HyperFile* hf);
	Bool ReadIt (HyperFile* hf, Int32 level);

	GeListHead* GetMarkerRoot(void);

	BaseSound* GetClonePart(const BaseTime& start, const BaseTime& stop, Bool reverse);

	static BaseSound* Alloc(void);
	static void Free(BaseSound*& v);
};

#endif
