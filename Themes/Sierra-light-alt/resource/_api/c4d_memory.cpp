#include <string.h>
#include <stdlib.h>

#include "c4d_memory.h"
#include "operatingsystem.h"
#include "c4d_general.h"

void _GeFree(void** Daten)
{
	if (*Daten)
	{
		C4DOS.Ge->Free(*Daten);
	}
	*Daten = nullptr;
}

// only for debug purposes
void _GeCheckAllMemory()
{
	C4DOS.Ge->GeCheckMem((void*)(UInt)0xdeadbeef);
}

void _GeCheck(void* memptr)
{
	if (memptr)
	{
		C4DOS.Ge->GeCheckMem(memptr);
	}
}

Bool GeGetAllocSize(void* p, Int* out_size)
{
	return C4DOS.Ge->GetAllocSize(p, out_size);
}

// allocator is either nullptr (current thread's allocator as used by NewMem, NewObj etc.) or a pool created via GeAllocPool
Bool GeGetAllocatorStatistics(BaseContainer& stat, void* allocator)
{
	return C4DOS.Ge->GeGetAllocatorStatistics(stat, allocator);
}

// try to estimate how much physical memory is still unused
UInt GeMemGetFreePhysicalMemoryEstimate(void)
{
	return C4DOS.Ge->GeMemGetFreePhysicalMemoryEstimate();
}


#define	STDLIB_MEM_MAGIC -1
Bool stdlib_mem_used = false;	// changed to true if static constructors have allocated memory before c4d's memory management was available

Bool IsAlienMem(void* p)
{
	if (p)
	{
		if (((Int*)p)[-1] == STDLIB_MEM_MAGIC)	// is this a block for the stdlib?
			return true;
	}
	return false;
}

namespace maxon
{

static void* AlienMem(size_t s, Bool clear)
{
	if (s < 1)
		s = 1;

	void* p = malloc(s + sizeof(Int));
	if (!p)
		return nullptr;

	if (clear)
		memset(p, 0, s + sizeof(Int));
	*(Int*) p = STDLIB_MEM_MAGIC;
	p = (void*) ((UChar*)p + sizeof(Int));
	stdlib_mem_used = true;	// static constructor has allocated memory
	return p;
}

void* GeNewMem(std::size_t s, int line, const char* file, bool clear)	// noexcept
{
	if (t_C4DOS)
	{
		if (clear)
			return C4DOS.Ge->Alloc(s < 1 ? 1 : s, line, file);
		else
			return C4DOS.Ge->AllocNC(s < 1 ? 1 : s, line, file);
	}

	return AlienMem(s, clear);
}

void GeDeleteMem(void* p)	// noexcept
{
	if (p)
	{
		void* temp = p;

		if (stdlib_mem_used)											// memory allocated by static constructors?
		{
			if (((Int*)p)[-1] == STDLIB_MEM_MAGIC)	// is this a block for the stdlib?
			{
				free((void*)((UChar*)p - sizeof(Int)));
				return;
			}
		}
		C4DOS.Ge->Free(temp);
	}
}

}
