#ifndef __C4D_MEMORY_MP_H
#define __C4D_MEMORY_MP_H


// --- Use to enable vtune api functions
//#define _USE_VTUNE_

// ---
#include "c4d_thread.h"
#include "c4d_misc.h"
#ifdef USE_API_MAXON
	#include "basearray.h"
#endif

// advanced mp array class
template <class TYPE> class MPAlloc
{
	maxon::BaseArray<TYPE*> ptr;
	MPAlloc(const MPAlloc&);

public:
	MPAlloc()
	{
	}

	~MPAlloc()
	{
		Free();
	}

	Bool Init(Int32 maxthreads)
	{
		Free();

		if (!ptr.Resize(maxthreads))
			return false;

		Int32 i;
		for (i = 0; i < maxthreads; i++)
		{
			Char* p = (Char*)C4DOS.Ge->AllocTH(i/*passthreadnum*/, sizeof(TYPE), true);
			if (!p)
			{
				Free();
				return false;
			}
			TYPE* res = new(p)TYPE;
			if (res != (TYPE*)p)
			{
				// must never happen!
				// it's not allowed to use array types for MPAlloc<>, e.g. MPAlloc<Char> is fine, MPAlloc<Char[1000]> will not work
				// the reason is that the compiler adds the arraysize infront of the memoryblock. the destructor is also not called
				CriticalStop();
				Free();
				return false;
			}
			ptr[i] = res;
		}
		return true;
	}

	void Free()
	{
		Int32 i;
		for (i = 0; i < ptr.GetCount(); i++)
		{
			if (!ptr[i])
				continue;
			ptr[i]->~TYPE();
			void* dat = ptr[i];
			C4DOS.Ge->FreeTH(i, dat);
			ptr[i] = nullptr;
		}
		ptr.Flush();
	}

	const TYPE& operator [](Int32 i) const { return *ptr[i]; }
	TYPE& operator [](Int32 i) { return *ptr[i]; }

	MPAlloc& operator =(const MPAlloc& src)
	{
		Free();
		if (!Init(src.ptr.GetCount()))
			return *this;

		Int32 i, cnt = LMin(ptr.GetCount(), src.ptr.GetCount());
		for (i = 0; i < cnt; i++)
		{
			if (ptr[i] && src.ptr[i])
				*ptr[i] = *src.ptr[i];
		}
		return *this;
	}

	Int32 GetCount() const { return ptr.GetCount(); }
};

#endif
