/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4D_MEMORY_H
#define __C4D_MEMORY_H

#ifdef __API_INTERN__
	#include "ge_memory.h"
#else

#include <new>
#ifdef __MAC
	using namespace std;
#elif !defined __PC
	#include <stddef.h>
#endif

#include <string.h>
#include <stdlib.h>
#include "c4d_plugin.h"
#include "operatingsystem.h"

namespace maxon
{
	void* GeNewMem(std::size_t s, int line, const char* file, bool clear);	// noexcept
	void GeDeleteMem(void* p);																							// noexcept
}


void _GeCheck(void* memptr);	// only for debug purposes
void _GeCheckAllMemory();			// only for debug purposes
void _GeFree(void** Daten);
Bool GeGetAllocSize(void* p, Int* out_size);
Bool IsAlienMem(void* p);

Bool GeGetAllocatorStatistics(BaseContainer& stat, void* allocator = nullptr);
#define	C4D_ALLOCATOR_STAT_CNT				1	// Int32
#define	C4D_ALLOCATOR_STAT_TOTAL_USED	2	// Int64
#define	C4D_ALLOCATOR_STAT_TOTAL_FREE	3	// Int64
#define	C4D_ALLOCATOR_INFO_CONTAINER	4	// BaseContainer
#define	C4D_ALLOCATOR_INFO_SLOT_SIZE	1	// Int32
#define	C4D_ALLOCATOR_INFO_SLOT_USED	2	// Int64
#define	C4D_ALLOCATOR_INFO_SLOT_FREE	3	// Int64

UInt GeMemGetFreePhysicalMemoryEstimate(void);

#ifdef __LEGACY_API
	#define GeAlloc(x)							 (C4DOS.Ge->Alloc((x), __LINE__, __FILE__))
	#define GeAllocNC(x)						 (C4DOS.Ge->AllocNC((x), __LINE__, __FILE__))
	#define GeReallocNC(p, s)				 (C4DOS.Ge->ReallocNC((p), (s), __LINE__, __FILE__))
	#define GeReallocTypeNC(t, p, s) (t*)(C4DOS.Ge->ReallocNC((p), sizeof(t) * (s), __LINE__, __FILE__))
	#define GeAllocType(t, x)				 (t*)(C4DOS.Ge->Alloc(sizeof(t) * (x), __LINE__, __FILE__))
	#define GeAllocTypeNC(t, x)			 (t*)(C4DOS.Ge->AllocNC(sizeof(t) * (x), __LINE__, __FILE__))
	#define GeFree(x)								 _GeFree((void**)(&(x)))
#endif

#define _GeAlloc(s, l, f)				 (C4DOS.Ge->Alloc((s), (l), (f)))
#define _GeAllocNC(s, l, f)			 (C4DOS.Ge->AllocNC((s), (l), (f)))
#define _GeReallocNC(p, s, l, f) (C4DOS.Ge->ReallocNC((p), (s), (l), (f)))

#ifdef _DEBUG
	#define GeCheck(x) _GeCheck(x)
#else
	#define GeCheck(x)
#endif

#ifdef USE_API_MAXON
	#include "defaultallocator.h"
#else
	#include "c4d_misc/memory/defaultallocator.h"
#endif

#ifdef __C4D_64BIT
	#define	__C4D_MEM_ALIGNMENT_MASK__ 15	// memory returned by NewMem() is guaranteed to be at least aligned to a 16 byte boundary
#else
	#define	__C4D_MEM_ALIGNMENT_MASK__ 7	// memory returned by NewMem() is guaranteed to be at least aligned to and 8 byte boundary
#endif

#ifndef C4D_ALIGN
	#if defined __PC
		#define C4D_ALIGN(_x_, _a_)	__declspec(align(_a_)) _x_
	#else
		#define C4D_ALIGN(_x_, _a_)	_x_ __attribute__((aligned(_a_)))
	#endif
#endif

inline void ClearMem(void* d, Int size, Int32 value = 0)
{
	memset(d, value & 0xFF, size);
}

inline void CopyMem(const void* s, void* d, Int size)
{
	if (s && d && size)
		memcpy(d, s, size);
}

inline void MemCopy(void* d, const void* s, Int size)
{
	if (s && d && size)
		memcpy(d, s, size);
}

template <class T, class U> inline void	FillMemTypeTemplate(T* data_ptr, Int size, const U* check_type, Int32 value)
{
#ifdef _DEBUG
	if (check_type != data_ptr)	// this will cause a compile time error if the types are different
		return;
#endif

	memset(data_ptr, value, size);
}

#define	FillMemType(t, d, x, v) FillMemTypeTemplate(d, sizeof(t) * (x), ((t*) d), v)

//----------------------------------------------------------------------------------------
/// Clears memory of a datatype with pattern, if size >0.
/// @param[out] data_ptr					Address of the datatype.
/// @param[in] cnt								Number of elements t be filled with pattern (>1 e.g. for arrays), can be 0.
/// @param[in] value							(optional) fill value.
/// THREADSAFE
//----------------------------------------------------------------------------------------
template <typename T> inline void ClearMemType(T* data_ptr, Int cnt)
{
	memset(data_ptr, 0, size_t(cnt * sizeof(T)));
}

//----------------------------------------------------------------------------------------
/// Copies the content of a datatype to another of the same kind
/// source and destination memory must not overlap.
/// @param[in] src_ptr						Source address of datatype.
/// @param[out] dst_ptr						Destination address of datatype.
/// @param[in] cnt								Number of elements to be copied (>1 e.g. for arrays), can be 0.
/// THREADSAFE
//----------------------------------------------------------------------------------------
template <typename T> inline void CopyMemType(const T* src_ptr, T* dst_ptr, Int cnt)
{
	memcpy(dst_ptr, src_ptr, size_t(cnt * sizeof(T)));
}

#ifndef	__C4D_NO_NEW_DELETE__	// use c4d's fast new/delete operators?
#if defined(__MAC)
inline void* operator	new(std::size_t s) throw (std::bad_alloc)
{
	return maxon::GeNewMem(s, 0, nullptr, true);
}

inline void* operator	new[](std::size_t s) throw (std::bad_alloc)
{
	return maxon::GeNewMem(s, 0, nullptr, true);
}
#else
inline void* operator	new(std::size_t s)
{
	return maxon::GeNewMem(s, 0, nullptr, true);
}

inline void* operator	new[](std::size_t s)
{
	return maxon::GeNewMem(s, 0, nullptr, true);
}
#endif

inline void* operator	new(std::size_t s, const std::nothrow_t&) throw()
{
	return maxon::GeNewMem(s, 0, nullptr, true);
}

inline void* operator	new[](std::size_t s, const std::nothrow_t&) throw()
{
	return maxon::GeNewMem(s, 0, nullptr, true);
}

inline void	operator	delete(void* p) throw()
{
	maxon::GeDeleteMem(p);
}

inline void	operator	delete[](void* p) throw()
{
	maxon::GeDeleteMem(p);
}

inline void	operator	delete(void* p, const std::nothrow_t&) throw()
{
	maxon::GeDeleteMem(p);
}

inline void	operator	delete[](void* p, const std::nothrow_t&) throw()
{
	maxon::GeDeleteMem(p);
}
#endif

// these are c4d's new/delete operators that don't replace the default operators
inline void* operator	new(std::size_t s, const std::nothrow_t&, int line, const Char* file) throw()
{
	return maxon::GeNewMem(s, line, file, true);
}

inline void* operator	new[](std::size_t s, const std::nothrow_t&, int line, const Char* file) throw()
{
	return maxon::GeNewMem(s, line, file, true);
}

inline void	operator	delete(void* p, const std::nothrow_t&, int line, const Char* file) throw()
{
	maxon::GeDeleteMem(p);
}

inline void	operator	delete[](void* p, const std::nothrow_t&, int line, const Char* file) throw()
{
	maxon::GeDeleteMem(p);
}

#ifdef __LEGACY_API
	#define gNew new(std::nothrow, __LINE__, __FILE__)
	#define bNew new(std::nothrow, __LINE__, __FILE__)
#endif
#define bNewDeprecatedUseArraysInstead new(std::nothrow, __LINE__, __FILE__)

#ifndef	__C4D_NO_NEW_DELETE__	// use c4d's fast new/delete operators?

// gDelete/bDelete do not call delete with (std::nothrow) because this is not supported
#ifdef __LEGACY_API
	#define gDelete(v) { if (v) delete v; v = 0; }
#endif
#define bDelete(v) { if (v) delete[] v; v = 0; }

#define	gDelete_TEMPLATE

#else	// do not redefine the new/delete operators, new/delete can be used by 3rd party code which requires the default operators and or exceptions

// Instead of replacing the delete operator use a template which calls the destructor manually and frees the memory
template <typename T> void gDelete(T*& v)
{
	if (v)
	{
		v->~T();
		C4DOS.Ge->Free(v);	// operator delete( v, std::nothrow, 0, nullptr );
		v = nullptr;
	}
}

// Instead of replacing the delete[] operator use a template which calls the destructors manually and frees the memory
// This is _not_ exactly portable and kosher but works reliable with gcc, icc, msvc
template <typename T> void bDelete(T*& v)
{
	if (v)
	{
		UInt32* d;

		d = (UInt32*) (((UInt) v) & ~__C4D_MEM_ALIGNMENT_MASK__);
		if (d != (UInt32*) v)	// object count for destructor stored?
		{
			UInt32 cnt;
			UInt32 i;

#ifdef __ppc64__	// big endian
			cnt = d[1];
#else
			cnt = *d;	// object count
#endif
			for (i = 0; i < cnt; i++)
				v[i].~T();
		}
		C4DOS.Ge->Free(d);	//operator delete[]( d , std::nothrow, 0, nullptr );
		v = nullptr;
	}
}

// template for classes with a private delete operator
#define	gDelete_TEMPLATE		\
template <typename T> static void gDelete(T * &v)	\
{	\
	if (v)	\
	{	\
		v->~T();	\
		operator delete(v, std::nothrow, 0, nullptr);	\
		v = nullptr;	\
	}	\
}

#endif

#include "ge_autoptr.h"

#define MEMORYPOOL_DEFAULT_BLOCKSIZE 0x80000

class DeprecatedMemoryPool
{
private:
	DeprecatedMemoryPool();
	~DeprecatedMemoryPool();

public:
	static DeprecatedMemoryPool* Alloc(Int block_size) { return C4DOS.Pl->Alloc(block_size); }
	static DeprecatedMemoryPool* Alloc() { return C4DOS.Pl->Alloc(MEMORYPOOL_DEFAULT_BLOCKSIZE); }
	static void Free(DeprecatedMemoryPool*& pool)
	{
		if (pool)
			C4DOS.Pl->Free(pool);
		pool = nullptr;
	}

	void* MemAlloc(Int size, Bool clear = true) { return C4DOS.Pl->AllocElement(this, size, clear); }
	void MemFree(void* mem, Int size) { C4DOS.Pl->FreeElement(this, mem, size); }
	void* MemAllocS(Int size, Bool clear = true) { return C4DOS.Pl->AllocElementS(this, size, clear); }
	void MemFreeS(void* mem) { C4DOS.Pl->FreeElementS(this, mem); }
	void* MemReAllocS(void* old, Int size, Bool clear = true) { return C4DOS.Pl->ReAllocElementS(this, old, size, clear); }
};

#endif

#endif
