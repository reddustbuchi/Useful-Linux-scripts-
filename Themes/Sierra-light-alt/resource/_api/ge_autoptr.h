/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _AUTOPTR_H_

// c4d_memory must be included first
#ifndef __C4D_MEMORY_H

#include "c4d_memory.h"

#else

#define _AUTOPTR_H_

#include "ge_math.h"
#include "c4d_memory.h"

template <class TYPE> class AutoAlloc
{
	TYPE* ptr;

private:
	const AutoAlloc<TYPE>& operator = (const AutoAlloc<TYPE>& p);
	AutoAlloc(const AutoAlloc<TYPE>& p);

public:
	AutoAlloc()												{ ptr = TYPE::Alloc(); }
	AutoAlloc(Int32 id)								{ ptr = TYPE::Alloc(id); }
	AutoAlloc(Int32 p1, Int32 p2)				{ ptr = TYPE::Alloc(p1, p2); }
	AutoAlloc(TYPE* initptr)					{ ptr = initptr; }
	~AutoAlloc()											{ TYPE::Free(ptr); ptr = nullptr; }
	operator TYPE*() const { return ptr; }
	operator TYPE&() const { return *ptr; }
	TYPE* operator -> () const { return ptr; }
	TYPE* const* operator & () const { return &ptr; }
	TYPE* Release()										{ TYPE* tmp = ptr; ptr = nullptr; return tmp; }
	void Free()												{ TYPE::Free(ptr); ptr = nullptr; }
	void Assign(TYPE* p)							{ ptr = p; }
};

template <class TYPE> class AutoNew
{
	TYPE* ptr;

private:
	const AutoNew<TYPE>& operator = (const AutoNew<TYPE>& p);
	AutoNew(const AutoNew<TYPE>& p);

public:
	AutoNew()													{ ptr = NewObjClear(TYPE); }
	~AutoNew()												{ DeleteObj(ptr); }
	operator TYPE*()
	{
		return ptr;
	}
	operator TYPE&()
	{
		return *ptr;
	}
	TYPE* operator -> () const { return ptr; }
	TYPE* const* operator & () const { return &ptr; }
	TYPE* Release()										{ TYPE* tmp = ptr; ptr = nullptr; return tmp; }
	void Free()												{ DeleteObj(ptr); }
	void Assign(TYPE* p)							{ ptr = p; }
};

template <class TYPE> class AutoPtrArray
{
	TYPE* ptr;

private:
	const AutoPtrArray<TYPE>& operator = (const AutoPtrArray<TYPE>& p);
	AutoPtrArray(const AutoPtrArray<TYPE>& p);

public:
	AutoPtrArray(TYPE* p)							{ ptr = p; }
	~AutoPtrArray()										{ bDelete(ptr); }
	operator TYPE*() const { return ptr; }
	operator TYPE&() const { return *ptr; }
	TYPE* operator -> () const { return ptr; }
	TYPE* const* operator & () const { return &ptr; }
	TYPE* Release()										{ TYPE* tmp = ptr; ptr = nullptr; return tmp; }
	void Free()												{ bDelete(ptr); }
	void Assign(TYPE* p)							{ ptr = p; }
	TYPE* Get() { return ptr; }
};

template <class TYPE> class AutoPtr
{
	TYPE* ptr;

private:
	const AutoPtr<TYPE>& operator = (const AutoPtr<TYPE>& p);
	AutoPtr(const AutoPtr<TYPE>& p);

public:
	AutoPtr(TYPE* p)									{ ptr = p; }
	~AutoPtr()												{ DeleteObj(ptr); }
	operator TYPE*() const { return ptr; }
	operator TYPE&() const { return *ptr; }
	TYPE* operator -> () const { return ptr; }
	TYPE* const* operator & () const { return &ptr; }
	TYPE* Release()										{ TYPE* tmp = ptr; ptr = nullptr; return tmp; }
	void Free()												{ DeleteObj(ptr); }
	void Assign(TYPE* p)							{ ptr = p; }
	TYPE* Get() { return ptr; }
};

template <class TYPE> class AutoFree
{
	TYPE* ptr;

private:
	const AutoFree<TYPE>& operator = (const AutoFree<TYPE>& p);
	AutoFree(const AutoFree<TYPE>& p);

public:
	AutoFree()												{ ptr = nullptr; }
	AutoFree(TYPE* p)									{ ptr = p; }
	~AutoFree()												{ TYPE::Free(ptr); ptr = nullptr; }
	void Set(TYPE* p)									{ ptr = p; }
	operator TYPE*() const { return ptr; }
	operator TYPE&() const { return *ptr; }
	TYPE* operator -> () const { return ptr; }
	TYPE* const* operator & () const { return &ptr; }
	TYPE* Release()										{ TYPE* tmp = ptr; ptr = nullptr; return tmp; }
	void Free()												{ TYPE::Free(ptr); ptr = nullptr; }
	void Assign(TYPE* p)							{ ptr = p; }
};

template <class TYPE> class AutoGeFree
{
	TYPE* ptr;

private:
	TYPE* operator = (TYPE* p);

public:
	AutoGeFree()												{ ptr = nullptr; }
	AutoGeFree(TYPE* p)									{ ptr = p; }
	~AutoGeFree()												{ DeleteMem(ptr); ptr = nullptr; }
	void Set(TYPE* p)									{ ptr = p; }
	operator TYPE*() const { return ptr; }
	TYPE* operator -> () const { return ptr; }
	TYPE* const* operator & () const { return &ptr; }
	TYPE* Release()										{ TYPE* tmp = ptr; ptr = nullptr; return tmp; }
	void Free()												{ DeleteMem(ptr); ptr = nullptr; }
	void Assign(TYPE* p)							{ ptr = p; }
};

#endif
#endif
