#ifdef USE_API_MAXON

	#error "Please check your project include paths or your relative include path."

#elif !defined(C4DMISC_BASEARRAY_H__)
#define C4DMISC_BASEARRAY_H__

#include "../memory/defaultallocator.h"
#include "autoiterator.h"

/// @file

namespace maxon {

/// @addtogroup STRUCTURES
/// @{

/// Flags for the behaviour of BaseArray when moving objects
enum BASEARRAYFLAGS
{
	BASEARRAYFLAGS_0									= 0,										///< always use constructor/destructor or move operator, never memcpy, memmove or realloc
	BASEARRAYFLAGS_MOVEANDCOPYOBJECTS	= (1 << 0)							///< elements are PODs and can be copied using memcpy and moved using memmove/realloc (for Resize, Insert, Erase, Append etc.)
} ENUM_FLAGS(BASEARRAYFLAGS);


/// Flags for BaseArray::Resize(), these flags are BaseArray specific
enum BASEARRAYRESIZEFLAGS
{
	BASEARRAYRESIZEFLAGS_0												= 0,

	BASEARRAYRESIZEFLAGS_ON_SHRINK_KEEP_CAPACITY	= 0,				///< don't change capacity
	BASEARRAYRESIZEFLAGS_ON_SHRINK_FIT_TO_SIZE		= (1 << 0),	///< copy the array to a new memory block that is as asmall as possible to hold the data

	BASEARRAYRESIZEFLAGS_ON_GROW_RESERVE_CAPACITY	= 0,				///< allocate some extra capacity (based on ComputeArraySize())
	BASEARRAYRESIZEFLAGS_ON_GROW_FIT_TO_SIZE			= (1 << 1),	///< grow the array exactly to the requested size

	BASEARRAYRESIZEFLAGS_ON_GROW_UNINITIALIZED		= (1 << 2),	///< do not initialize PODs when resizing the array

	BASEARRAYRESIZEFLAGS_FIT_TO_SIZE							= BASEARRAYRESIZEFLAGS_ON_SHRINK_FIT_TO_SIZE | BASEARRAYRESIZEFLAGS_ON_GROW_FIT_TO_SIZE,	///< fits the array to the requested size for growing and shrinking
	BASEARRAYRESIZEFLAGS_DEFAULT									= BASEARRAYRESIZEFLAGS_ON_SHRINK_KEEP_CAPACITY | BASEARRAYRESIZEFLAGS_ON_GROW_FIT_TO_SIZE,	///< the default is to keep capacity on shrink and fit to size when growing the array
	BASEARRAYRESIZEFLAGS_POD_UNINITIALIZED				= BASEARRAYRESIZEFLAGS_DEFAULT | BASEARRAYRESIZEFLAGS_ON_GROW_UNINITIALIZED
} ENUM_FLAGS(BASEARRAYRESIZEFLAGS);

static const Int BASEARRAY_DEFAULT_CHUNK_SIZE = 16;

// Helper class that implements MoveFrom(), CopyFrom() and TryRealloc() depending on whether
// T can be moved or copied byte-wise (using memmove(), memcpy() or realloc()) or the
// move and copy constructors have to be used to do so.
template <typename T, class ALLOCATOR, Bool MOVE_AND_COPY_MEMORY> class BaseArrayHelper
{
};

// T can be moved or copied using memmove() and memcpy()
template <typename T, class ALLOCATOR> class BaseArrayHelper<T, ALLOCATOR, true>
{
public:
	// used to move objects within the array or from one array to another, cannot fail
	// it is assumed that the elements dst points to are not constructed, if dst and src
	// overlap the elements are moved in the right order
	static void MoveFrom(T* src, T* dst, Int moveCnt)
	{
		memmove(dst, src, (size_t) moveCnt * SIZEOF(T));
	}

	// used by BaseArray::Insert() to copy multiple elements
	// it is assumed that the elements dst points to are not constructed, if dst and src
	// returns dst or nullptr if CopyFrom() failed
	static T* CopyFrom(const T* src, T* dst, Int copyCnt)
	{
		return (T*) memcpy(dst, src, size_t(copyCnt * SIZEOF(T)));
	}

	static T* TryRealloc(ALLOCATOR& a, T* ptr, Int s, Bool& isRealloc)
	{
		isRealloc = true;																				// indicates data has been moved to the new memmory location
		return (T*) a.Realloc(ptr, s, C4D_MISC_ALLOC_LOCATION);
	}
};

// T must be moved or copied using move and copy constructors
template <typename T, class ALLOCATOR> class BaseArrayHelper<T, ALLOCATOR, false>
{
public:
	// used to move objects within the array or from one array to another, cannot fail
	// it is assumed that the elements dst points to are not constructed, if dst and src
	// overlap the elements are moved in the right order
	static void MoveFrom(T* src, T* dst, Int moveCnt)
	{
		if (src > dst)
		{
			for (Int i = 0; i < moveCnt; i++)
			{
				new (dst) T(std::move(*src));												// call move constructor if available, otherwise the old element will be copied
				src->~T();																					// if the move constructor is available the compiler might be able to omit the destructor call

				src++;
				dst++;
			}
		}
		else
		{
			src += moveCnt;
			dst += moveCnt;

			for (Int i = 0; i < moveCnt; i++)
			{
				src--;
				dst--;

				new (dst) T(std::move(*src));												// call move constructor if available, otherwise the old element will be copied
				src->~T();																					// if the move constructor is available the compiler might be able to omit the destructor call
			}
		}
	}

	// used by BaseArray::Insert() to copy multiple elements
	// it is assumed that the elements dst points to are not constructed, if dst and src
	// returns dst or nullptr if CopyFrom() failed
	static T* CopyFrom(const T* src, T* dst, Int copyCnt)
	{
		for (Int i = 0; i < copyCnt; i++)
		{
			if (NewCopy(&dst[i], src[i]) == nullptr)							// copy failed?
			{
				for (i--; i >= 0; i--)
					dst[i].~T();																			// destruct already copied objects

				dst = nullptr;
				break;
			}
		}

		return dst;
	}

	static T* TryRealloc(ALLOCATOR& a, T* ptr, Int s, Bool& isRealloc)
	{
		isRealloc = false;																			// indicates that ptr is still valid and elements have to be moved from there using MoveFrom()
		return (T*) a.Alloc(s, C4D_MISC_ALLOC_LOCATION);
	}
};

// special handling for char
template <class ALLOCATOR> class BaseArrayHelper<char, ALLOCATOR, false>
{
public:
	static void	MoveFrom(const char* src, char* dst, Int moveCnt)																							{ memmove(dst, src, size_t(moveCnt * SIZEOF(char))); }
	static char* CopyFrom(const char* src, char* dst, Int copyCnt)																						{ return (char*) memcpy(dst, src, size_t(copyCnt * SIZEOF(char))); }
	static char*TryRealloc(ALLOCATOR& a, char* ptr, Int s, Bool& isRealloc)																		{ isRealloc = true; return (char*) a.Realloc(ptr, s, C4D_MISC_ALLOC_LOCATION); }
};

// special handling for short
template <class ALLOCATOR> class BaseArrayHelper<short, ALLOCATOR, false>
{
public:
	static void MoveFrom(const short* src, short* dst, Int moveCnt)																						{ memmove(dst, src, size_t(moveCnt * SIZEOF(short))); }
	static short* CopyFrom(const short* src, short* dst, Int copyCnt)																					{ return (short*) memcpy(dst, src, size_t(copyCnt * SIZEOF(short))); }
	static short* TryRealloc(ALLOCATOR& a, short* ptr, Int s, Bool& isRealloc)																{ isRealloc = true; return (short*) a.Realloc(ptr, s, C4D_MISC_ALLOC_LOCATION); }
};

// special handling for int
template <class ALLOCATOR> class BaseArrayHelper<int, ALLOCATOR, false>
{
public:
	static void MoveFrom(const int* src, int* dst, Int moveCnt)																								{ memmove(dst, src, size_t(moveCnt * SIZEOF(int))); }
	static int*	CopyFrom(const int* src, int* dst, Int copyCnt)																								{ return (int*) memcpy(dst, src, size_t(copyCnt * SIZEOF(int))); }
	static int*	TryRealloc(ALLOCATOR& a, int* ptr, Int s, Bool& isRealloc)																		{ isRealloc = true; return (int*) a.Realloc(ptr, s, C4D_MISC_ALLOC_LOCATION); }
};

// special handling for long
template <class ALLOCATOR> class BaseArrayHelper<long, ALLOCATOR, false>
{
public:
	static void MoveFrom(const long* src, long* dst, Int moveCnt)																							{ memmove(dst, src, size_t(moveCnt * SIZEOF(long))); }
	static long* CopyFrom(const long* src, long* dst, Int copyCnt)																						{ return (long*) memcpy(dst, src, size_t(copyCnt * SIZEOF(long))); }
	static long* TryRealloc(ALLOCATOR& a, long* ptr, Int s, Bool& isRealloc)																	{ isRealloc = true; return (long*) a.Realloc(ptr, s, C4D_MISC_ALLOC_LOCATION); }
};

// special handling for long long
template <class ALLOCATOR> class BaseArrayHelper<long long, ALLOCATOR, false>
{
public:
	static void MoveFrom(const long long* src, long long* dst, Int moveCnt)																		{ memmove(dst, src, size_t(moveCnt * SIZEOF(long long))); }
	static long long* CopyFrom(const long long* src, long long* dst, Int copyCnt)															{ return (long long*) memcpy(dst, src, size_t(copyCnt * SIZEOF(long long))); }
	static long long* TryRealloc(ALLOCATOR& a, long long* ptr, Int s, Bool& isRealloc)												{ isRealloc = true; return (long long*) a.Realloc(ptr, s, C4D_MISC_ALLOC_LOCATION); }
};

// special handling for unsigned char
template <class ALLOCATOR> class BaseArrayHelper<unsigned char, ALLOCATOR, false>
{
public:
	static void MoveFrom(const unsigned char* src, unsigned char* dst, Int moveCnt)														{ memmove(dst, src, size_t(moveCnt * SIZEOF(unsigned char))); }
	static unsigned char*				CopyFrom(const unsigned char* src, unsigned char* dst, Int copyCnt)						{ return (unsigned char*) memcpy(dst, src, size_t(copyCnt * SIZEOF(unsigned char))); }
	static unsigned char*				TryRealloc(ALLOCATOR& a, unsigned char* ptr, Int s, Bool& isRealloc)					{ isRealloc = true; return (unsigned char*) a.Realloc(ptr, s, C4D_MISC_ALLOC_LOCATION); }
};

// special handling for unsigned short
template <class ALLOCATOR> class BaseArrayHelper<unsigned short, ALLOCATOR, false>
{
public:
	static void MoveFrom(const unsigned short* src, unsigned short* dst, Int moveCnt)													{ memmove(dst, src, size_t(moveCnt * SIZEOF(unsigned short))); }
	static unsigned short*			CopyFrom(const unsigned short* src, unsigned short* dst, Int copyCnt)					{ return (unsigned short*) memcpy(dst, src, size_t(copyCnt * SIZEOF(unsigned short))); }
	static unsigned short*			TryRealloc(ALLOCATOR& a, unsigned short* ptr, Int s, Bool& isRealloc)					{ isRealloc = true; return (unsigned short*) a.Realloc(ptr, s, C4D_MISC_ALLOC_LOCATION); }
};

// special handling for unsigned int
template <class ALLOCATOR> class BaseArrayHelper<unsigned int, ALLOCATOR, false>
{
public:
	static void MoveFrom(const unsigned int* src, unsigned int* dst, Int moveCnt)															{ memmove(dst, src, size_t(moveCnt * SIZEOF(unsigned int))); }
	static unsigned int*				CopyFrom(const unsigned int* src, unsigned int* dst, Int copyCnt)							{ return (unsigned int*) memcpy(dst, src, size_t(copyCnt * SIZEOF(unsigned int))); }
	static unsigned int*				TryRealloc(ALLOCATOR& a, unsigned int* ptr, Int s, Bool& isRealloc)						{ isRealloc = true; return (unsigned int*) a.Realloc(ptr, s, C4D_MISC_ALLOC_LOCATION); }
};

// special handling for unsigned long
template <class ALLOCATOR> class BaseArrayHelper<unsigned long, ALLOCATOR, false>
{
public:
	static void MoveFrom(const unsigned long* src, unsigned long* dst, Int moveCnt)														{ memmove(dst, src, size_t(moveCnt * SIZEOF(unsigned long))); }
	static unsigned long* CopyFrom(const unsigned long* src, unsigned long* dst, Int copyCnt)									{ return (unsigned long*) memcpy(dst, src, size_t(copyCnt * SIZEOF(unsigned long))); }
	static unsigned long* TryRealloc(ALLOCATOR& a, unsigned long* ptr, Int s, Bool& isRealloc)								{ isRealloc = true; return (unsigned long*) a.Realloc(ptr, s, C4D_MISC_ALLOC_LOCATION); }
};

// special handling for unsigned long long
template <class ALLOCATOR> class BaseArrayHelper<unsigned long long, ALLOCATOR, false>
{
public:
	static void MoveFrom(const unsigned long long* src, unsigned long long* dst, Int moveCnt)									{ memmove(dst, src, size_t(moveCnt * SIZEOF(unsigned long long))); }
	static unsigned long long*	CopyFrom(const unsigned long long* src, unsigned long long* dst, Int copyCnt)	{ return (unsigned long long*) memcpy(dst, src, size_t(copyCnt * SIZEOF(unsigned long long))); }
	static unsigned long long*	TryRealloc(ALLOCATOR& a, unsigned long long* ptr, Int s, Bool& isRealloc)			{ isRealloc = true; return (unsigned long long*) a.Realloc(ptr, s, C4D_MISC_ALLOC_LOCATION); }
};

// special handling for float
template <class ALLOCATOR> class BaseArrayHelper<float, ALLOCATOR, false>
{
public:
	static void MoveFrom(const float* src, float* dst, Int moveCnt)																						{ memmove(dst, src, size_t(moveCnt * SIZEOF(float))); }
	static float* CopyFrom(const float* src, float* dst, Int copyCnt)																					{ return (float*) memcpy(dst, src, size_t(copyCnt * SIZEOF(float))); }
	static float* TryRealloc(ALLOCATOR& a, float* ptr, Int s, Bool& isRealloc)																{ isRealloc = true; return (float*) a.Realloc(ptr, s, C4D_MISC_ALLOC_LOCATION); }
};

// special handling for double
template <class ALLOCATOR> class BaseArrayHelper<double, ALLOCATOR, false>
{
public:
	// special handling for standard types that can be moved with realloc
	static void MoveFrom(const double* src, double* dst, Int moveCnt)																					{ memmove(dst, src, size_t(moveCnt * SIZEOF(double))); }
	static double* CopyFrom(const double* src, double* dst, Int copyCnt)																			{ return (double*) memcpy(dst, src, size_t(copyCnt * SIZEOF(double))); }
	static double* TryRealloc(ALLOCATOR& a, double* ptr, Int s, Bool& isRealloc)															{ isRealloc = true; return (double*) a.Realloc(ptr, s, C4D_MISC_ALLOC_LOCATION); }
};

// special handling for pointers of T
template <typename T, class ALLOCATOR> class BaseArrayHelper<T*, ALLOCATOR, false>
{
public:
	static void MoveFrom(T* const* src, T** dst, Int moveCnt)																									{ memmove(dst, src, size_t(moveCnt * SIZEOF(T*))); }
	static T**	CopyFrom(T* const* src, T** dst, Int copyCnt)																									{ return (T**) memcpy(dst, src, size_t(copyCnt * SIZEOF(T*))); }
	static T**	TryRealloc(ALLOCATOR& a, T** ptr, Int s, Bool& isRealloc)																			{ isRealloc = true; return (T**) a.Realloc(ptr, s, C4D_MISC_ALLOC_LOCATION); }
};

//----------------------------------------------------------------------------------------
///	Basic array template.
/// The array consists of one continuous block of memory. The block will have a minimum
/// size of MINCHUNKSIZE elements of type T as soon as the first element is added.
///
/// The elements may be copied and change their memory address when the array grows. If
/// your objects cannot be copied or need a constant address use the BlockArray template.
///
/// If you need a specific alignment you may have to use a non-default allocator. C4D's
/// allocators align on a 8 byte boundary for 32 bit code and on a 16 byte boundary
/// for 64 bit code. If you need a different alignment or custom resize behaviour
/// (default is grow rate of 1.5) you may use your own allocator instead.
///
///
/// @tparam T											Type of the array elements.
/// @tparam MINCHUNKSIZE					The minimum number of elements upon array creation.
/// @tparam MEMFLAGS							Use BASEARRAYFLAGS_0 unless you know the object can be moved and/or copied.
/// @tparam ALLOCATOR							Class for memory allocation.
///
/// @note Note that the array element class has special requirements regarding @link movecopy copy and move constructors @endlink.
//----------------------------------------------------------------------------------------
template <typename T, Int MINCHUNKSIZE = BASEARRAY_DEFAULT_CHUNK_SIZE, BASEARRAYFLAGS MEMFLAGS = BASEARRAYFLAGS_0, typename ALLOCATOR = DefaultAllocator> class BaseArray : protected ALLOCATOR
{
	DISALLOW_COPY_AND_ASSIGN(BaseArray);

	typedef BaseArrayHelper<T, ALLOCATOR, MEMFLAGS == BASEARRAYFLAGS_MOVEANDCOPYOBJECTS> Helper;

public:
	typedef T ValueType;
	typedef ALLOCATOR AllocatorType;

	template <Bool CONSTITERATOR> class IteratorTemplate;

	/// Iterator allows read and write access to array elements
	typedef IteratorTemplate<false> Iterator;

	/// Iterator for read-only access to array elements
	typedef IteratorTemplate<true> ConstIterator;


	BaseArray() : _ptr(nullptr), _cnt(0), _capacity(0)
	{
	}

	/// this constructor has to be used if an array should use a custom allocator with member variables
	explicit BaseArray(const ALLOCATOR& a) : ALLOCATOR(a), _ptr(nullptr), _cnt(0), _capacity(0)
	{
	}

	~BaseArray()
	{
		Reset();
	}

	/// move constructor
	BaseArray(BaseArray&& src) : ALLOCATOR(std::move(src)), _ptr(src._ptr), _cnt(src._cnt), _capacity(src._capacity)
	{
		src._ptr = nullptr;
		src._cnt = 0;
		src._capacity = 0;
	}

	/// move assignment operator
	MOVE_ASSIGNMENT_OPERATOR(BaseArray)

	//----------------------------------------------------------------------------------------
	/// Deletes all elements (calls destructors and frees memory)
	//----------------------------------------------------------------------------------------
	void Reset()
	{
		if (_ptr)
		{
			for (Int i = _cnt - 1; i >= 0; i--)
				_ptr[i].~T();

			this->Free(_ptr);
			_ptr = nullptr;
		}
		_capacity = 0;
		_cnt = 0;
	}

	//----------------------------------------------------------------------------------------
	/// Deletes all elements, but doesn't free memory (calls destructors though)
	//----------------------------------------------------------------------------------------
	void Flush()
	{
		if (_ptr)
		{
			for (Int i = _cnt - 1; i >= 0; i--)
				_ptr[i].~T();
		}
		_cnt = 0;
	}

	//----------------------------------------------------------------------------------------
	/// Gets the number of array elements.
	/// @return												Number of array elements.
	//----------------------------------------------------------------------------------------
	Int GetCount() const
	{
		return _cnt;
	}

	//----------------------------------------------------------------------------------------
	/// Gets the number of elements for which memory has been allocated (this is usually bigger than GetCount())
	/// @return												Number of array elements for which memory has been allocated.
	//----------------------------------------------------------------------------------------
	Int GetCapacityCount() const
	{
		return _capacity;
	}

	//----------------------------------------------------------------------------------------
	/// Array (subscript) operator for const objects.
	/// @param[in] idx								Element index (if it's out of bounds you will get an error in debug code only, otherwise it will crash)
	/// @return												Array element.
	//----------------------------------------------------------------------------------------
	const T& operator [](Int idx) const
	{
		DebugAssert(UInt(idx) < UInt(_cnt));
		return _ptr[idx];
	}

	//----------------------------------------------------------------------------------------
	/// Array (subscript) operator for non-const objects.
	/// @param[in] idx								Element index (if it's out of bounds you will get an error in debug code only, otherwise it will crash)
	/// @return												Array element.
	//----------------------------------------------------------------------------------------
	// this is duplicate code but casting constness away for this case is plain ugly
	T& operator [](Int idx)
	{
		DebugAssert(UInt(idx) < UInt(_cnt));
		return _ptr[idx];
	}

	//----------------------------------------------------------------------------------------
	/// Adds a new element at the end of the array.
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Append()
	{
		return new (AppendWithoutConstructor()) T();						// no null check needed because placement new does this implicitely (see defaultallocator.h for details)
	}

	//----------------------------------------------------------------------------------------
	/// Adds a new element at the end of the array and initializes it with a copy of x.
	/// @param[in] x									Value to be copied.
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Append(const T& x)
	{
		T* buf = AppendWithoutConstructor();
		T* element = ObjectConstructor<T, TestForCopyFromMember<T>::isSupported>::Copy(buf, x);
		if (TestForCopyFromMember<T>::isSupported && element != buf)	// CopyFrom() failed (element is nullptr)?
			_cnt--;																									// correct counter
		return element;
	}

	//----------------------------------------------------------------------------------------
	/// Adds a new element at the end of the array and moves the content of x to it.
	/// @param[in] x									Value to be moved.
	/// @return												Element pointer or nullptr (allocation failed)
	//----------------------------------------------------------------------------------------
	T* Append(T&& x)
	{
		return new (AppendWithoutConstructor()) T(std::move(x));	// no null check needed because placement new does this implicitely (see defaultallocator.h for details)
	}

	//----------------------------------------------------------------------------------------
	/// Inserts a new default element at index position.
	/// @param[in] position						Insert index (the array size will increase and the existing elements are moved)
	/// @return												Element pointer or nullptr (allocation failed or position out of boundaries)
	//----------------------------------------------------------------------------------------
	T* Insert(Int position)
	{
		return new (InsertWithoutConstructor(position)) T();		// no null check needed because placement new does this implicitely (see defaultallocator.h for details)
	}

	//----------------------------------------------------------------------------------------
	/// Inserts a new default element at iterator position.
	/// @param[in] position						Insert position.
	/// @return												Iterator for the new element (IsValid() == false if allocation failed)
	//----------------------------------------------------------------------------------------
	Iterator Insert(Iterator position)
	{
		return Iterator(Insert(position - Begin()));
	}

	//----------------------------------------------------------------------------------------
	/// Inserts a new element at index position and initializes it with a copy of x.
	/// @param[in] position						Insert index (the array size will increase and the existing elements are moved)
	/// @param[in] x									Value to be copied.
	/// @return												Element pointer or nullptr (allocation failed or position out of boundaries)
	//----------------------------------------------------------------------------------------
	T* Insert(Int position, const T& x)
	{
		T* buf = InsertWithoutConstructor(position);
		T* element = ObjectConstructor<T, TestForCopyFromMember<T>::isSupported>::Copy(buf, x);
		if (TestForCopyFromMember<T>::isSupported && element != buf)	// CopyFrom() failed (element is nullptr)?
		{
			_cnt--;																									// correct counter
			Helper::MoveFrom(buf + 1, buf, _cnt - position);				// move elements back
		}
		return element;
	}

	//----------------------------------------------------------------------------------------
	/// Inserts a new element at iterator position and initializes it with a copy of x.
	/// @param[in] position						Insert position.
	/// @param[in] x									Value to be copied.
	/// @return												Iterator for the new element (IsValid() == false if allocation failed)
	//----------------------------------------------------------------------------------------
	Iterator Insert(Iterator position, const T& x)
	{
		return Iterator(Insert(position - Begin(), x));
	}

	//----------------------------------------------------------------------------------------
	/// Inserts a new element at index position and moves the content of x to it.
	/// @param[in] position						Insert index (the array size will increase and the existing elements are moved)
	/// @param[in] x									Value to be moved.
	/// @return												Element pointer or nullptr (allocation failed or position out of boundaries)
	//----------------------------------------------------------------------------------------
	T* Insert(Int position, T&& x)
	{
		return new (InsertWithoutConstructor(position)) T(std::move(x)); // no null check needed because placement new does this implicitely (see defaultallocator.h for details)
	}

	//----------------------------------------------------------------------------------------
	/// Inserts a new element at iterator position and moves the content of x to it.
	/// @param[in] position						Insert position.
	/// @param[in] x									Value to be moved.
	/// @return												Iterator for the new element (IsValid() == false if allocation failed)
	//----------------------------------------------------------------------------------------
	Iterator Insert(Iterator position, T&& x)
	{
		return Iterator(Insert(position - Begin(), std::move(x)));
	}

	//----------------------------------------------------------------------------------------
	/// Inserts new elements at index position (all elements from position on are moved by insertCnt)
	/// @param[in] position						Insert index (the array size will increase and the existing elements are moved)
	/// @param[in] x									Array with values to be copied or nullptr (in this case you have to call the constructor manually)
	/// @param[in] insertCnt					Number of elements to be inserted.
	/// @return												Element pointer or nullptr (allocation failed or position out of boundaries)
	//----------------------------------------------------------------------------------------
	T* Insert(Int position, const T* x, Int insertCnt)
	{
		T* element = InsertWithoutConstructor(position, insertCnt);
		if (element && x)
		{
			element = Helper::CopyFrom(x, element, insertCnt);
			if (TestForCopyFromMember<T>::isSupported && element == nullptr)	// CopyFrom() failed?
			{
				_cnt -= insertCnt;																		// correct counter
				Helper::MoveFrom(_ptr + position + insertCnt, _ptr + position, _cnt - position);	// move elements back
			}
		}
		return element;
	}

	//----------------------------------------------------------------------------------------
	/// Inserts new elements at iterator position (all elements from position on are moved by insertCnt)
	/// @param[in] position						Insert position.
	/// @param[in] x									Array with values to be copied or nullptr (in this case you have to call the constructor manually)
	/// @param[in] insertCnt					Number of elements to be inserted.
	/// @return												Iterator for the new element (IsValid() == false if allocation failed)
	//----------------------------------------------------------------------------------------
	Iterator Insert(Iterator position, const T* x, Int insertCnt)
	{
		return Iterator(Insert(position - Begin(), x, insertCnt));
	}

	//----------------------------------------------------------------------------------------
	/// Erases (removes and deletes) elements.
	/// @param[in] position						Erase index (Erase() will fail if out of bounds and return nullptr)
	/// @param[in] eraseCnt						Number of elements to be erased (if eraseCnt is higher than what is available at position Erase() will succeed, but remove only the number of available elements)
	/// @return												Pointer to the element that is now at position or nullptr (no more element at position, either because position is out of bounds or the last element was erased)
	//----------------------------------------------------------------------------------------
	T* Erase(Int position, Int eraseCnt = 1)
	{
		T*	element = _ptr + position;
		Int endIdx	= position + eraseCnt;

		if (UInt(position) >= UInt(_cnt))
		{
			DebugAssert(eraseCnt == 0);
			return nullptr;
		}

		if (UInt(endIdx) > UInt(_cnt))
		{
			DebugStop();
			eraseCnt = _cnt - position;
			endIdx = _cnt;
		}

		for (T* destruct = element + eraseCnt - 1; destruct >= element; destruct--)
			destruct->~T();

		Helper::MoveFrom(element + eraseCnt, element, _cnt - endIdx);
		_cnt -= eraseCnt;

		return (_cnt == position) ? nullptr : element;
	}

	//----------------------------------------------------------------------------------------
	/// Erases (removes and deletes) elements.
	/// @param[in] position						Erase position.
	/// @param[in] eraseCnt						Number of elements to be erased (if eraseCnt is higher than what is available at position Erase() will succeed, but remove only the number of available elements)
	/// @return												Iterator for the element that is now at position (IsValid() == false if something failed)
	//----------------------------------------------------------------------------------------
	Iterator Erase(Iterator position, Int eraseCnt = 1)
	{
		T*	element = position.GetPtr();
		Int idx = position - Begin();
		Int endIdx = idx + eraseCnt;

		if (UInt(endIdx) > UInt(_cnt))
		{
			DebugStop();
			eraseCnt = _cnt - idx;
			endIdx = _cnt;
		}

		for (T* destruct = element + eraseCnt - 1; destruct >= element; destruct--)
			destruct->~T();

		Helper::MoveFrom(element + eraseCnt, element, _cnt - endIdx);
		_cnt -= eraseCnt;

		return position;
	}

	//----------------------------------------------------------------------------------------
	/// Returns the first element of the array.
	/// @return												Pointer to the first element (null if the array is empty)
	//----------------------------------------------------------------------------------------
	const T* GetFirst() const
	{
		return (_cnt > 0) ? _ptr : nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// Returns the first element of the array.
	/// @return												Pointer to the first element (null if the array is empty)
	//----------------------------------------------------------------------------------------
	T* GetFirst()
	{
		return (_cnt > 0) ? _ptr : nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// Returns the last element of the array.
	/// @return												Pointer to the last element (null if the array is empty)
	//----------------------------------------------------------------------------------------
	const T* GetLast() const
	{
		return (_cnt > 0) ? &_ptr[_cnt - 1] : nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// Returns the last element of the array.
	/// @return												Pointer to the last element (null if the array is empty)
	//----------------------------------------------------------------------------------------
	T* GetLast()
	{
		return (_cnt > 0) ? &_ptr[_cnt - 1] : nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// Resizes the array to contain newCnt elements
	/// If newCnt is smaller than GetCount() all extra elements are being deleted. If it is
	/// greater the array is expanded and the default constructor is called for new elements.
	/// @param[in] newCnt							New array size.
	/// @param[in] resizeFlags				BaseArray specific: see BASEARRAYRESIZEFLAGS.
	/// @return												False if allocation failed.
	//----------------------------------------------------------------------------------------
	Bool Resize(Int newCnt, BASEARRAYRESIZEFLAGS resizeFlags = BASEARRAYRESIZEFLAGS_DEFAULT)
	{
		Int	increment = newCnt - _cnt;
		T*	element = _ptr + _cnt;

		if (increment <= 0)																			// decrease array size (or fit to size if equal)?
		{
			if (newCnt >= 0)
			{
				for (; increment < 0; increment++)
					(--element)->~T();

				_cnt = newCnt;

				if (resizeFlags & BASEARRAYRESIZEFLAGS_ON_SHRINK_FIT_TO_SIZE)
					FitToSize(newCnt);
			}
			else
				DebugStop();
		}
		else																										// increase array size
		{
			if (newCnt > _capacity)																// increase memory block size?
			{
				Int	 totalCapacity = newCnt;
				Bool isRealloc;

				if ((resizeFlags & BASEARRAYRESIZEFLAGS_ON_GROW_FIT_TO_SIZE) == BASEARRAYRESIZEFLAGS_0)
					totalCapacity = this->ComputeArraySize(_capacity, increment, MINCHUNKSIZE);

				element = Helper::TryRealloc(GetAllocator(), _ptr, totalCapacity * SIZEOF(T), isRealloc);
				if (element)
				{
					if (isRealloc == false && _ptr)										// allocated new memory block (no realloc)?
					{
						Helper::MoveFrom(_ptr, element, _cnt);					// move elements to new memory block
						this->Free(_ptr);
					}
					_ptr = element;
					_capacity = totalCapacity;
					element += _cnt;
				}
			}

			if (element)
			{
				if ((resizeFlags & BASEARRAYRESIZEFLAGS_ON_GROW_UNINITIALIZED) == BASEARRAYRESIZEFLAGS_0)
				{
					for (; increment > 0; increment--)
						new (element++) T();
				}
				_cnt = newCnt;
			}
		}

		return _cnt == newCnt;
	}

	//----------------------------------------------------------------------------------------
	/// Deletes the last element.
	/// @param[out] dst								Nullptr or pointer to return value.
	/// @return												True if successful.
	//----------------------------------------------------------------------------------------
	Bool Pop(T* dst = nullptr)
	{
		if (_cnt > 0)
		{
			_cnt--;
			if (dst)
				*dst = std::move(_ptr[_cnt]);												// call move operator if available

			_ptr[_cnt].~T();
			return true;
		}
		return false;
	}

	//----------------------------------------------------------------------------------------
	/// Gets the index of the element. The element must be part of the array, otherwise (e.g.
	/// if x is a copy of an array element) InvalidArrayIndex will be returned.
	/// @return												Index of element or InvalidArrayIndex (not element of this)
	//----------------------------------------------------------------------------------------
	Int GetIndex(const T& x) const
	{
		if ((&x >= _ptr) && (&x < _ptr + GetCount()))
			return Int(&x - _ptr);

		return InvalidArrayIndex;
	}

	//----------------------------------------------------------------------------------------
	/// Increases the internal capacity of this array (if necessary) so that it can hold at least the given number of elements without further memory allocations.
	/// @param[in] requestedCapacity	The desired internal capacity.
	/// @return												False if allocation failed.
	//----------------------------------------------------------------------------------------
	Bool EnsureCapacity(Int requestedCapacity)
	{
		Int	increment = requestedCapacity - _cnt;
		if (increment > 0)																			// increase array size?
		{
			Int cnt = _cnt;
			if (AppendWithoutConstructor(increment) == nullptr)
				return false;
			_cnt = cnt;																						// AppendWithoutConstructor increases _cnt, this is not wanted here
		}
		return true;
	}

	//----------------------------------------------------------------------------------------
	/// Copies an array.
	/// @param[in] src								Source array.
	/// @param[in] fitToSize					If true the array will be copied to a new memory block that is as small as possible to hold the data.
	/// @return												True if successful.
	//----------------------------------------------------------------------------------------
	template <typename SourceArray> Bool CopyFrom(const SourceArray& src, Bool fitToSize = true)
	{
		Reset();

		_capacity = fitToSize ? src.GetCount() : src.GetCapacityCount();
		T* element = (T*) this->Alloc(_capacity * SIZEOF(T), C4D_MISC_ALLOC_LOCATION);
		if (element)
		{
			typename SourceArray::ConstIterator it(src);
			_ptr = element;
			_cnt = src.GetCount();

			for (Int i = 0; i < _cnt; i++, it++, element++)
			{
				if (NewCopy(element, *it) == nullptr)								// CopyFrom() failed?
				{
					_cnt = i - 1;
					Reset();
					break;
				}
			}
		}
		return _cnt == src.GetCount();
	}

	//----------------------------------------------------------------------------------------
	/// Copies an array: specialization for BaseArray.
	/// @param[in] src								Source array.
	/// @param[in] fitToSize					If true the array will be copied to a new memory block that is as small as possible to hold the data.
	/// @return												True if successful.
	//----------------------------------------------------------------------------------------
	Bool CopyFrom(const BaseArray& src, Bool fitToSize)
	{
		Reset();

		_capacity = fitToSize ? src._cnt : src._capacity;
		T* element = (T*) this->Alloc(_capacity * SIZEOF(T), C4D_MISC_ALLOC_LOCATION);
		if (element)
		{
			_ptr = element;
			_cnt = src._cnt;
			if (Helper::CopyFrom(src._ptr, element, _cnt) == nullptr)	// CopyFrom() failed?
			{
				_cnt = 0;
				Reset();
			}
		}
		return _cnt == src._cnt;
	}

	//----------------------------------------------------------------------------------------
	/// Default CopyFrom() method.
	/// @param[in] src								Source array.
	/// @return												True if successful.
	//----------------------------------------------------------------------------------------
	Bool CopyFrom(const BaseArray& src)
	{
		return CopyFrom(src, true);
	}

	//----------------------------------------------------------------------------------------
	/// Swaps elements a and b (equivalent to global Swap(array[a], array[b])
	/// @param[in] a									Position of element to be swapped.
	/// @param[in] b									Position of element to be swapped.
	//----------------------------------------------------------------------------------------
	void Swap(Iterator a, Iterator b)
	{
		maxon::Swap(*a, *b);
	}

	//----------------------------------------------------------------------------------------
	/// Gets an iterator for the first element
	/// When you modify the array Begin() will change, it is not a constant value.
	/// @return												Iterator for the first element (equal to End() if the array is empty)
	//----------------------------------------------------------------------------------------
	ConstIterator Begin() const
	{
		return ConstIterator(_ptr);
	}

	//----------------------------------------------------------------------------------------
	/// Gets an iterator for the first element
	/// When you modify the array Begin() will change, it is not a constant value.
	/// @return												Iterator for the first element (equal to End() if the array is empty)
	//----------------------------------------------------------------------------------------
	Iterator Begin()
	{
		return Iterator(_ptr);
	}

	//----------------------------------------------------------------------------------------
	/// Gets an iterator for the end (End() - 1 is the last element if the array is not empty)
	/// When you modify the array End() will change, it is not a constant value.
	/// @return												Iterator for the array end (this is behind the last element)
	//----------------------------------------------------------------------------------------
	ConstIterator End() const
	{
		return ConstIterator(_ptr + GetCount());
	}

	//----------------------------------------------------------------------------------------
	/// Gets an iterator for the end (End() - 1 is the last element if the array is not empty)
	/// When you modify the array End() will change, it is not a constant value.
	/// @return												Iterator for the array end (this is behind the last element)
	//----------------------------------------------------------------------------------------
	Iterator End()
	{
		return Iterator(_ptr + GetCount());
	}

	//----------------------------------------------------------------------------------------
	///	The BaseArray iterator internally is a pointer and using it to iterate over an array
	/// or parts of it is as efficient as using a real pointer (for more ease of use you may
	/// want to invoke this via AutoIterator).
	///
	/// As already said you can use an Iterator almost like a pointer, e.g.
	/// @code
	/// it++;								// go to the next element
	/// it--;								// go to the previous element
	/// it += 5;						// advance by 5 elements
	/// it -= 3;						// go back 3 elements
	/// cnt = itB - itA;		// number of elements from itA to itB
	/// it = array.Begin();	// iterator to the first element of the array
	/// *it = value;				// assign value to the elements referenced by the iterator
	/// value = *it;				// get value of the element referenced by the iterator
	/// @endcode
	///
	/// Please note that using a postfix operator access (*it++ or *it--) can be slower than
	/// using the prefix form or a separate assignment. E.g.
	/// @code	value = *it++; @endcode is most likely slower than
	/// @code	value = it; ++it; @endcode or @code	value = it; it++; @endcode
	///	because *it++ requires a temporary copy of the iterator that the compiler may not
	/// be able to remove during optimization. As long as you only use the iterator's postfix
	/// operator without assignment it should be fine because the compiler will remove the
	/// temporary copy.
	//----------------------------------------------------------------------------------------
	template <Bool CONSTITERATOR> class IteratorTemplate
	{
	public:
		// For a const iterator, both the BaseArray and its values have to be const within the iterator, otherwise they are non-const.
		// These typedefs have to be used throughout the iterator code instead of just BaseArray or T.
		typedef typename ConstIf<CONSTITERATOR, BaseArray>::Type CollectionType;
		typedef typename ConstIf<CONSTITERATOR, T>::Type ValueType;
		static const Bool isLinearIterator = true;

		explicit IteratorTemplate(CollectionType& a, Int start = 0) : _data(a.GetFirst() + start)
		{
		}
		explicit IteratorTemplate(ValueType* pos = nullptr) : _data(pos)
		{
		}

		IteratorTemplate(const IteratorTemplate& src) : _data(src._data)
		{
		}
		IteratorTemplate& operator =(const IteratorTemplate& src)
		{
			_data = src._data;																		// self assignment is no problem here, therefore no check if (this != &src)
			return *this;
		}

#ifdef __INTEL_COMPILER
	#pragma warning disable 597
#endif
		operator ConstIterator&()
		{
			return *(ConstIterator*) this;
		}
#ifdef __INTEL_COMPILER
	#pragma warning enable 597
#endif

		//----------------------------------------------------------------------------------------
		/// @return												true if the iterator points to an element (Iterator().IsValid() will return false)
		//----------------------------------------------------------------------------------------
		Bool IsValid() const
		{
			return _data != nullptr;
		}

		ValueType* GetPtr() const
		{
			return _data;
		}
		ValueType& operator *() const
		{
			return *_data;
		}
		ValueType* operator ->() const
		{
			return _data;
		}

		Bool operator ==(const IteratorTemplate& b) const
		{
			return _data == b._data;
		}
		Bool operator !=(const IteratorTemplate& b) const
		{
			return _data != b._data;
		}
		Bool operator >=(const IteratorTemplate& b) const
		{
			return _data >= b._data;
		}
		Bool operator <=(const IteratorTemplate& b) const
		{
			return _data <= b._data;
		}
		Bool operator <(const IteratorTemplate& b) const
		{
			return _data < b._data;
		}
		Bool operator >(const IteratorTemplate& b) const
		{
			return _data > b._data;
		}

		IteratorTemplate& operator ++()																	// prefix operator ++ (increment and fetch)
		{
			_data++;
			return *this;
		}
		const IteratorTemplate operator ++(int)													// postfix operator ++ (fetch and increment)
		{
			ValueType* tmp = _data;
			_data++;
			return IteratorTemplate(tmp);																	// use RVO
		}
		IteratorTemplate& operator +=(Int i)														// operator +=
		{
			_data += i;
			return *this;
		}
		IteratorTemplate& operator --()																	// prefix operator -- (decrement and fetch)
		{
			_data--;
			return *this;
		}
		const IteratorTemplate operator --(int)													// postfix operator -- (fetch and decrement)
		{
			ValueType* tmp = _data;
			_data--;
			return IteratorTemplate(tmp);																	// use RVO
		}
		IteratorTemplate& operator -=(Int i)														// operator -=
		{
			_data -= i;
			return *this;
		}
		IteratorTemplate operator +(Int i) const												// operator +
		{
			return IteratorTemplate(_data + i);														// use RVO
		}
		IteratorTemplate operator -(Int i) const
		{
			return IteratorTemplate(_data - i);														// use RVO
		}
		Int operator -(const IteratorTemplate& b) const
		{
			return _data - b._data;
		}

	private:
		ValueType* _data;
	};

	// Move elements to another (empty array)
	Bool MoveAndShrink(BaseArray<T, MINCHUNKSIZE, MEMFLAGS, ALLOCATOR>& dst, Int position, Int moveCnt)
	{
		if (dst.GetCount() == 0 && dst.EnsureCapacity(moveCnt))
		{
			if (position + moveCnt <= GetCount())
			{
				// move elements to destination array
				Helper::MoveFrom(_ptr + position, dst._ptr, moveCnt);
				dst._cnt = moveCnt;

				// close gap
				Helper::MoveFrom(_ptr + position + moveCnt, _ptr + position, _cnt - (position + moveCnt));
				_cnt -= moveCnt;
				return true;
			}
		}
		return false;
	}

	//----------------------------------------------------------------------------------------
	/// Disconnects the array's memory buffer and returns its address and size.
	/// @param[out] dst								Nullptr or pointer to return value.
	/// @return												Allocator reference.
	//----------------------------------------------------------------------------------------
	T* Disconnect(Int* dst = nullptr)
	{
		T* data = _ptr;

		if (dst)
			*dst = _cnt;

		_ptr = nullptr;
		_cnt = 0;
		_capacity = 0;

		return data;
	}

	//----------------------------------------------------------------------------------------
	/// Returns the allocator as reference. Typically this is used by the arrays and other
	/// base classes when multiple of them are "stitched" together as one big object all
	/// shall use one main allocator.
	/// @return												Allocator reference.
	//----------------------------------------------------------------------------------------
	ALLOCATOR& GetAllocator()
	{
		return *this;
	}

	//----------------------------------------------------------------------------------------
	/// BaseArray specific: Appends uninitialized element(s) at the end of the array. <B> This
	/// does not call the constructor! Use Append() unless you deal with PODs that shall not
	/// be initialized for a very good reason! </B>
	/// @param[in] increment					Number of elements to be appended.
	/// @return												Pointer to the element (the constructor hasn't been called yet) or nullptr.
	//----------------------------------------------------------------------------------------
	T* AppendWithoutConstructor(Int increment = 1)
	{
		Int	requestedCapacity = _cnt + increment;
		T*	result = _ptr + _cnt;

		if (requestedCapacity > _capacity)											// increase memory block size?
		{
			Bool isRealloc;
			Int	totalCapacity = this->ComputeArraySize(_capacity, increment, MINCHUNKSIZE);
			result = Helper::TryRealloc(GetAllocator(), _ptr, totalCapacity * SIZEOF(T), isRealloc);
			if (result)
			{
				if (isRealloc == false && _ptr)											// allocated new memory block (no realloc)?
				{
					Helper::MoveFrom(_ptr, result, _cnt);							// move elements to new memory block
					this->Free(_ptr);
				}
				_ptr = result;
				_capacity = totalCapacity;
				result += _cnt;
			}
			else
				requestedCapacity = _cnt;
		}

		_cnt = requestedCapacity;
		return result;
	}

	//----------------------------------------------------------------------------------------
	/// BaseArray specific: Inserts uninitialized element(s) at the specified index. <B> This does
	/// not call the constructor! Use Insert() unless you deal with PODs that shall not be
	/// initialized for a very good reason! </B>
	/// @param[in] idx								Index at which elements shall be inserted (0 <= idx <= cnt)
	/// @param[in] increment					Number of elements to be inserted.
	/// @return												Pointer to the element (the constructor hasn't been called yet) or nullptr.
	//----------------------------------------------------------------------------------------
	T* InsertWithoutConstructor(Int idx, Int increment = 1)
	{
		Bool isInsert = UInt(idx) < UInt(_cnt);									// if idx == cnt the elements will be appended

		if (UInt(idx) > UInt(_cnt))
		{
			DebugStop();																					// check for invalid position
			return nullptr;
		}

		if (_cnt + increment > _capacity)												// resize the array?
		{
			Bool isRealloc;
			Int	 newCapacity = this->ComputeArraySize(_cnt, increment, MINCHUNKSIZE);
			T*	 newArray = Helper::TryRealloc(GetAllocator(), _ptr, newCapacity * SIZEOF(T), isRealloc);

			if (newArray == nullptr)
				return nullptr;

			if (isRealloc == false)																// allocated new memory block?
			{
				Helper::MoveFrom(_ptr, newArray, idx);
				if (isInsert)																				// insert in the array?
					Helper::MoveFrom(_ptr + idx, newArray + idx + increment, _cnt - idx);

				this->Free(_ptr);
				isInsert = false;																		// already done the work
			}
			_ptr = newArray;
			_capacity = newCapacity;
		}

		T* element = _ptr + idx;																// pointer to the inserted/appended element
		if (isInsert)																						// insert in the array?
			Helper::MoveFrom(element, element + increment, _cnt - idx);
		_cnt += increment;

		return element;
	}

protected:
	Bool FitToSize(Int newCapacity)
	{
		if (newCapacity >= _cnt)
		{
			if (newCapacity == _capacity)
				return true;

			T* newArray = (T*) this->Alloc(newCapacity * SIZEOF(T), C4D_MISC_ALLOC_LOCATION);	// using Realloc() wouldn't work because it won't shrink an existing block (furthermore if it would we'd have problems with the constructors)
			if (newArray)
			{
				// at this point we could check the real size of newArray and possibly skip the rest if it isn't smaller
				Helper::MoveFrom(_ptr, newArray, _cnt);
				this->Free(_ptr);
				_capacity = newCapacity;
				_ptr = newArray;
				return true;
			}
		}
		return false;
	}

protected:
	T*	_ptr;
	Int _cnt;																									// number of used array elements
	Int _capacity;																						// number of allocated array elements
};


/// @}

} // C4D_MISC_END

#endif	// BASEARRAY_H__
