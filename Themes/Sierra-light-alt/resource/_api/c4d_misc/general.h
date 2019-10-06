#ifdef USE_API_MAXON

Error

#elif !defined(C4DMISC_APIBASE_H__)
#define C4DMISC_APIBASE_H__

/// @file
/// Main include file

#undef  _HAS_EXCEPTIONS
#define _HAS_EXCEPTIONS 0

#include <stddef.h>
#include <string.h>
#include <math.h>
#include <new>

#include "utilities/compilerdetection.h"



#ifndef APIBASE_H__
class String;
#endif

namespace maxon {

/// \defgroup STRUCTURES Data Structures
/// @{
/// @}

// Use C4D_MISC_DLL_PUBLIC in the declaration of a variable or function to export symbols (project settings make them private by default), e.g.
// C4D_MISC_DLL_PUBLIC int variable;
// extern "C" C4D_MISC_DLL_PUBLIC void function();

#ifdef __PC
	#define	C4D_MISC_DLL_PUBLIC				__declspec(dllexport)
	#define	C4D_MISC_NO_INLINE				__declspec(noinline)
	#define C4D_MISC_ALIGN(_x_, _a_)	__declspec(align(_a_)) _x_
	#define	ATTRIBUTE_USED
#elif defined __ANDROID
	#define	C4D_MISC_DLL_PUBLIC				__attribute__((visibility("default")))
	#define	C4D_MISC_NO_INLINE				__attribute__ ((noinline))
	#define C4D_MISC_ALIGN(_x_, _a_)	_x_ __attribute__((aligned(_a_)))
	#define	ATTRIBUTE_USED						__attribute__((used))
#else
	#define	C4D_MISC_DLL_PUBLIC				__attribute__((visibility("default")))
	#define	C4D_MISC_NO_INLINE				__attribute__ ((noinline))
	#define C4D_MISC_ALIGN(_x_, _a_)	_x_ __attribute__((aligned(_a_)))

	// use ATTRIBUTE_USED to tell the linker it must not dead-strip a function or static variable (even if it determines that the rest of the program does not refer to the object)
	#define	ATTRIBUTE_USED						__attribute__((used))
#endif

#if (__LP64__ || _WIN64) && !defined(__C4D_64BIT)
	#define __C4D_64BIT
#endif

typedef short int						Int16;
typedef unsigned short int	UInt16;
typedef signed int					Int32;
typedef unsigned int				UInt32;
typedef signed long long		Int64;
typedef unsigned long long	UInt64;

typedef bool                Bool;			///< boolean type, possible values are only false/true, 8 bit
typedef float								Float32;	///< 32 bit floating point value (float)
typedef double							Float64;	///< 64 bit floating point value (double)
typedef char								Char;			///< signed 8 bit character
typedef unsigned char				UChar;		///< unsigned 8 bit character

#ifdef __C4D_64BIT
	typedef Int64							Int;
	typedef UInt64						UInt;
#else
	typedef Int32							Int;			///< signed 32/64 bit int, size depends on the platform
	typedef UInt32						UInt;			///< unsigned 32/64 bit int, size depends on the platform
#endif

/// current floating point model.
/// right now it's adjusted to Float64==64 bit but maybe it's redefined to Float32 anytime
#ifdef __iOS
	typedef Float32 Float;
	#define __FLOAT_32_BIT
#else
	typedef Float64 Float;
#endif

// Type value ranges, math constants and trigonometric functions
#include "utilities/apibasemath.h"

static const Int InvalidArrayIndex = -1;	///< invalid array index (e.g. for array index out of bounds)

/// This statement needs to be used for any case in a switch the contains code, but does not call break.
/// An example:
/// @code
/// switch(condition)
/// {
///   case 0:
///     ...do something...
///   // SWITCH_FALLTHROUGH
///
///   case 1:
///     ...do something...
///		  break;
///  }
/// @endcode
#define SWITCH_FALLTHROUGH

#ifndef DISALLOW_COPY_AND_ASSIGN
/// This statement needs to be used at the beginning of any class that cannot be copied
/// An example:
/// @code
/// class MyClass
/// {
///   DISALLOW_COPY_AND_ASSIGN(MyClass);
///	  ...
///	};
///	@endcode

	#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
		TypeName(const TypeName&); \
		void operator =(const TypeName&);
#endif

#ifndef MOVE_ASSIGNMENT_OPERATOR
/// This statement automatically creates a move assignment operator from an existing move constructor. It needs to be written in the public: section.
/// An example:
/// @code
/// class MyClass
/// {
///   DISALLOW_COPY_AND_ASSIGN(MyClass);
/// public:
///   MOVE_ASSIGNMENT_OPERATOR(MyClass);
///	  ...
///	};
///	@endcode

	#define MOVE_ASSIGNMENT_OPERATOR(TypeName) \
		TypeName& operator =(TypeName&& src) \
		{ \
			if (this != &src) \
			{ \
				this->~TypeName(); \
				new (this) TypeName(std::move(src)); \
			} \
			return *this; \
		}
#endif

//----------------------------------------------------------------------------------------
/// Automatic detection of CopyFrom() method using SFINAE.
/// If a class implements Bool CopyFrom(T& src) the constant TestForCopyFromMember<T>::IsSupported
/// will be true.
/// For this case the template argument deduction prefers the conversion of 0 to a pointer
/// (using Char TestForCopyFromFunction(TestForCopyFromWrapper<T, &T::CopyFrom>*)) over
/// binding to an ellipsis parameter (Int16 TestForCopyFromFunction(...)).
/// If a class does not implement CopyFrom() only Int16 TestForCopyFromFunction(...) is available.
/// Both cases can be distinguished by having different size return values.
//----------------------------------------------------------------------------------------
template <typename T, Bool (T::*f)(const T&)> struct TestForCopyFromWrapper {};
template <typename T> Char  TestForCopyFromFunction(TestForCopyFromWrapper<T, &T::CopyFrom>*);	// template argument can only be dededuced if T contains a CopyFrom() method
template <typename T> Int16 TestForCopyFromFunction(...);		// default case for classes without CopyFrom(), must have different size return value
template <typename T> struct TestForCopyFromMember
{
	static const bool isSupported = sizeof(TestForCopyFromFunction<T>(0)) == sizeof(Char);
};

template <typename T, Bool hasCopyFrom> class ObjectConstructor
{
};

// for classes with copy constructor that cannot fail (may or may not support move semantics)
template <typename T> class ObjectConstructor<T, false>
{
public:
	//----------------------------------------------------------------------------------------
	/// Construct an object using new (dst) T(src), cannot fail.
	/// @param[out] dst								Copied object will be placed here (can be nullptr)
	/// @param[in] src								Object to be copied.
	/// @return												Same as dst.
	//----------------------------------------------------------------------------------------
	static T* Copy(T* dst, const T&src)
	{
		return new (dst) T(src);
	}

	//----------------------------------------------------------------------------------------
	/// Copy assignment, cannot fail.
	/// @param[out] dst								Copy will be placed here (dst must have already been constructed)
	/// @param[in] src								Object to be copied.
	/// @return												Always true.
	//----------------------------------------------------------------------------------------
	static Bool AssignCopy(T& dst, const T& src)
	{
		dst = src;
		return true;
	}
};

// for classes with complex copy constructor (implements CopyFrom() and move constructor)
template <typename T> class ObjectConstructor<T, true>
{
public:
	//----------------------------------------------------------------------------------------
	/// Construct an object using CopyFrom() (like new (dst) T(src) but with error check)
	/// If copy construction fails the object will be automatically destructed, dst will
	/// point to uninitialized memory like before the call.
	/// @param[out] dst								Copied object will be placed here (can be nullptr)
	/// @param[in] src								Object to be copied.
	/// @return												Same as dst or nullptr (CopyFrom() failed)
	//----------------------------------------------------------------------------------------
	static T* Copy(T* dst, const T&src)
	{
		if (dst)
		{
			new (dst) T();																				// initialize T
			if (dst->CopyFrom(src) == false)											// copy failed?
			{
				dst->~T();																					// destruct
				dst = nullptr;
			}
		}
		return dst;
	}

	//----------------------------------------------------------------------------------------
	/// Copy assignment using CopyFrom()
	/// @param[out] dst								Copy will be placed here (dst must have already been constructed)
	/// @param[in] src								Object to be moved.
	/// @return												True if successful.
	//----------------------------------------------------------------------------------------
	static Bool AssignCopy(T& dst, const T& src)
	{
		return dst.CopyFrom(src);
	}
};

//----------------------------------------------------------------------------------------
/// call new (dst) T(src) or dst->CopyFrom(src) for non-trivial objector copy constructor
//----------------------------------------------------------------------------------------
template <typename T> inline T* NewCopy(T* dst, const T& src)
{
	return ObjectConstructor<T, TestForCopyFromMember<T>::isSupported>::Copy(dst, src);
}

//----------------------------------------------------------------------------------------
/// copy assignment
//----------------------------------------------------------------------------------------
template <typename T> inline Bool AssignCopy(T& dst, const T& src)
{
	return ObjectConstructor<T, TestForCopyFromMember<T>::isSupported>::AssignCopy(dst, src);
}

template <typename T> struct AlwaysFalse { static bool const value = false; };

#ifndef DOXYGEN_SHOULD_SKIP_THIS

inline Int Align(Int value, Int alignment)
{
	return (value + (alignment - 1)) & ~(alignment - 1);
}

template <typename T> inline T* Align(T* value, Int alignment)
{
	return (T*) Align((Int) value, alignment);
}

// use this in a statement like
// DerivedFromAssertion<T, B>();
// to assert at compile-time that T is derived from B (or the same)
template<typename T, typename B> struct DerivedFromAssertion
{
	static void Check(B* b) {}
	DerivedFromAssertion() {Check((T*) nullptr);}
};


typedef Char FalseType;
typedef Int TrueType;

#define IS_TRUE_TYPE(E) (sizeof(E) == sizeof(maxon::TrueType))

// use Select<b, T, F>::Type to choose type T for b==true and type F for b==false
template <Bool, typename, typename> class Select;

template <typename T, typename F> class Select<false, T, F>
{
public:
	typedef F Type;
};

template <typename T, typename F> class Select<true, T, F>
{
public:
	typedef T Type;
};


// use ConstIf<b, T>::Type to choose type const T for b==true and type T for b==false
template <Bool, typename> class ConstIf;

template <typename T> class ConstIf<true, T>
{
public:
	typedef const T Type;
};

template <typename T> class ConstIf<false, T>
{
public:
	typedef T Type;
};


template <typename T, typename Check> class SFINAEHelper
{
public:
	typedef T Type;
};



// the following types and functions are needed for the NewObj macro

struct IsAllocType_False
{
	template <typename T> IsAllocType_False(const T&);
	IsAllocType_False();
};

struct IsAllocType_True: public IsAllocType_False
{
};

FalseType IsAllocType(IsAllocType_False);
TrueType IsAllocType(IsAllocType_True);


struct IsImplementationType_False
{
	template <typename T> IsImplementationType_False(const T&);
	IsImplementationType_False();
};

struct IsImplementationType_True: public IsImplementationType_False
{
};

FalseType IsImplementationType(IsImplementationType_False);
TrueType IsImplementationType(IsImplementationType_True);


// use C4D_MISC_ISEMPTY(__VA_ARGS__) to check if the arguments are empty (result will be 1) or not (result will be 0)

#ifdef _MSC_VER

// from http://stackoverflow.com/questions/2124339/c-preprocessor-va-args-number-of-arguments
#define C4D_MISC_ISEMPTY(...) _C4D_MISC_ISEMPTY((_C4D_MISC_ISEMPTY_PREFIX ## __VA_ARGS__ ## _C4D_MISC_ISEMPTY_POSTFIX, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0))
#define _C4D_MISC_ISEMPTY(__args) _C4D_MISC_ISEMPTY2 __args
#define _C4D_MISC_ISEMPTY_PREFIX_MISC_ISEMPTY_POSTFIX ,,,,, ,,,,, 1
#define _C4D_MISC_ISEMPTY2(__p0,__p1,__p2,__p3,__p4,__p5,__p6,__p7,__p8,__p9,__n,...) __n

#else

// from http://gustedt.wordpress.com/2010/06/08/detect-empty-macro-arguments/
#define C4D_MISC_ISEMPTY(...) _C4D_MISC_ISEMPTY( \
	_C4D_MISC_HAS_COMMA(__VA_ARGS__), /* test if there is just one argument, eventually an empty one */ \
	_C4D_MISC_HAS_COMMA(_C4D_MISC_TRIGGER_PARENTHESIS_ __VA_ARGS__), /* test if _TRIGGER_PARENTHESIS_ together with the argument adds a comma (if __VA_ARGS__ is parenthesized) */ \
	_C4D_MISC_HAS_COMMA(__VA_ARGS__ (~)), /* test if the argument together with a parenthesis adds a comma */ \
	_C4D_MISC_HAS_COMMA(_C4D_MISC_TRIGGER_PARENTHESIS_ __VA_ARGS__ (~))) /* this will have a comma if __VA_ARGS__ is empty (but also for other cases) */

#define _C4D_MISC_ARG16(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, ...) _15
#define _C4D_MISC_HAS_COMMA(...) _C4D_MISC_ARG16(__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0)
#define _C4D_MISC_TRIGGER_PARENTHESIS_(...) ,
#define _C4D_MISC_PASTE5(_0, _1, _2, _3, _4) _0 ## _1 ## _2 ## _3 ## _4
#define _C4D_MISC_ISEMPTY(_0, _1, _2, _3) _C4D_MISC_HAS_COMMA(_C4D_MISC_PASTE5(_C4D_MISC_IS_EMPTY_CASE_, _0, _1, _2, _3))
#define _C4D_MISC_IS_EMPTY_CASE_0001 ,

#endif


#define _C4D_MISC_PASTE(x, y) x ## y
#define C4D_MISC_PASTE(x, y) _C4D_MISC_PASTE(x, y)


typedef void (*DeleteFunction) (void* object);

template <typename T> inline DeleteFunction ToDeleteFunction(void (*fn) (T*))
{
	return (DeleteFunction) fn;
}

// Templates to avoid unwanted enum usage/conversion
#include "utilities/enumflags.h"
#endif


#ifdef APIBASE_H__
class String;
#endif

#if defined(__MAC) || defined(__LINUX)
	#define __debugbreak()	__asm__("int $3\n" : :);
#elif defined(__iOS)
	#if defined(__i386__) || defined(__x86_64__)
		#define __debugbreak()	__asm__("int $3\n" : :);
	#else
	#define __debugbreak()	//__asm__ __volatile__ ("mov r0, %0\nmov r1, %1\nmov r12, #37\nswi 128\n" : : "r" (getpid ()), "r" (SIGINT) : "r12", "r0", "r1", "cc");
	#endif
#elif !defined(__PC)
	#define __debugbreak()	{}
#endif

// debugging section

/// output flags for console output
enum OUTPUT
{
	OUTPUT_DIAGNOSTIC		= (1<<0),	 ///< diagnostic output, shows up if this group of output is activated. This is also the default
	OUTPUT_WARNING			= (1<<1),	 ///< warning output, shows up if this group of output is activated
	OUTPUT_CRITICAL			= (1<<2),	 ///< critical output, shows up if this group of output is activated

	OUTPUT_NOLINEBREAK  = (1<<29), ///< if set, no line break is added
	OUTPUT_HEADER				= (1<<30)  ///< if set, header with line number and file name is added
} ENUM_FLAGS(OUTPUT);

/// determines, whether a debugging environment is present. Note that this value will be false if the debugger was attached to a process
extern maxon::Bool	g_isDebuggerPresent;

/// determines, whether debug breaks will be executed. Note that g_isDebuggerPresent needs to be true, too in order to have an effect.
extern maxon::Bool	g_enableDebugBreak;

// _ConsoleOutputC4D version without additional parameters prints argument to str as it is (no special treatment of %)
void _ConsoleOutputC4D(OUTPUT flags, const Char* str, Int line, const Char* file);
void _ConsoleOutputC4D(OUTPUT flags, const String& str, Int line, const Char* file);

// volatile qualifier for file just to avoid ambiguosity between _ConsoleOutputC4D overloads: if no additional parameter is provided,
// the version without ... is chosen as it is a better match
void _ConsoleOutputC4D(OUTPUT flags, const Char* fmt, Int line, const volatile Char* file, ...);
void _ConsoleOutputC4D(OUTPUT flags, const String& fmt, Int line, const volatile Char* file, ...);

// All routines that start with Debug (DebugOutput, DebugStop, DebugAssert) result in empty (non-speed critical) code in a release build

/// DebugOutput outputs text into the console.
/// It only has any effect in debug builds and does not cost any time in release builds.
/// It should be used for temporary output that must not be visible to a customer or external developer.
/// The full <a href="http://www.cplusplus.com/reference/clibrary/cstdio/printf">printf syntax</a> can be used for the format string.
/// THREADSAFE.
#ifdef _DEBUG
	#define DebugOutput(flags,fmt,...) maxon::_ConsoleOutputC4D(flags,fmt,__LINE__,__FILE__,##__VA_ARGS__)
#else
	#define DebugOutput(flags,fmt,...) do { } while(false)
#endif

/// DiagnosticOutput outputs text into the console.
/// The output is visible in debug builds or in a release build when the debug console with diagnostic output is activated.
/// The full <a href="http://www.cplusplus.com/reference/clibrary/cstdio/printf">printf syntax</a> can be used for the format string.
/// THREADSAFE.
#define DiagnosticOutput(fmt,...) maxon::_ConsoleOutputC4D(maxon::OUTPUT_DIAGNOSTIC,fmt,__LINE__,__FILE__,##__VA_ARGS__)

/// OutputWithFlags outputs text into the console.
/// The output is visible in debug builds or in a release build when the debug console with diagnostic output is activated.
/// The full <a href="http://www.cplusplus.com/reference/clibrary/cstdio/printf">printf syntax</a> can be used for the format string.
/// THREADSAFE.
#define OutputWithFlags(flags,fmt,...) maxon::_ConsoleOutputC4D(flags,fmt,__LINE__,__FILE__,##__VA_ARGS__)

/// WarningOutput outputs text into the console.
/// The output is visible in debug builds or in a release build when the debug console with warning output is activated.
/// It should only be used to output unexpected, non-critical conditions.
/// It automatically shows header information and adds a line break.
/// The full <a href="http://www.cplusplus.com/reference/clibrary/cstdio/printf">printf syntax</a> can be used for the format string.
/// THREADSAFE.
#define WarningOutput(fmt,...) maxon::_ConsoleOutputC4D(maxon::OUTPUT_WARNING|maxon::OUTPUT_HEADER,fmt,__LINE__,__FILE__,##__VA_ARGS__)

/// CriticalOutput outputs text into the console.
/// The output is visible in debug builds or in a release build when the debug console with critical output is activated.
/// It should only be used to output unexpected, critical conditions that would most likely result in instability, e.g. an illegal array access or corrupt object structure.
/// It can also be used for unexpected events, e.g. if a necessary module cannot be initialized.
/// It automatically shows header information and adds a line break.
/// It automatically stops the debugger if present.
/// The full <a href="http://www.cplusplus.com/reference/clibrary/cstdio/printf">printf syntax</a> can be used for the format string.
/// THREADSAFE.
#define CriticalOutput(fmt,...) do { maxon::_ConsoleOutputC4D(maxon::OUTPUT_CRITICAL|maxon::OUTPUT_HEADER,fmt,__LINE__,__FILE__,##__VA_ARGS__); if (maxon::g_isDebuggerPresent && maxon::g_enableDebugBreak) __debugbreak(); } while(false)

inline const Char* AssertHelper(size_t len, const Char* msg1, const Char* msg2)
{
	return (strlen(msg2) > len) ? msg2 : msg1;
}

/// DebugStop stops the execution of the application if it is a debug build and a debugger is present. In case of a debug build the file and line number are output (critical output category).
/// A C string can be passed as argument that will be output as well.
/// THREADSAFE.
#ifdef _DEBUG
	#define DebugStop(...)	do { DebugOutput(maxon::OUTPUT_CRITICAL|maxon::OUTPUT_HEADER,maxon::AssertHelper(strlen("Debug Stop: "), "Debug Stop", "Debug Stop: " __VA_ARGS__)); if (maxon::g_isDebuggerPresent && maxon::g_enableDebugBreak) __debugbreak(); } while (false)
#else
	#define DebugStop(...)	do { } while(false)
#endif

/// CriticalStop stops the execution of the application if a debugger is present. The file and line number are output (critical output category).
/// A C string can be passed as argument that will be output as well.
/// THREADSAFE.
#define CriticalStop(...) do { CriticalOutput(maxon::AssertHelper(strlen("Stop: "), "Stop", "Stop: " __VA_ARGS__)); } while (false)

#ifdef __MAC
#define	__DEBUGGING__																				// avoid conflicts with DebugAssert() definition for the Mac
#endif

/// DebugAssert is a conditional DebugStop. It does the same as DebugStop() if 'condition' is false. A C string can be passed as optional argument for output.
/// THREADSAFE.
#if defined _DEBUG
	#define DebugAssert(condition, ...) do { if (!(condition)) { DebugOutput(maxon::OUTPUT_CRITICAL|maxon::OUTPUT_HEADER,maxon::AssertHelper(strlen("Debug Assertion failed: "), "Debug Assertion failed: " #condition, "Debug Assertion failed: " __VA_ARGS__)); if (maxon::g_isDebuggerPresent && maxon::g_enableDebugBreak) __debugbreak(); } } while(false)
#else
	#define DebugAssert(condition, ...) do { } while(false)
#endif

/// CriticalAssert is a conditional CriticalStop. It does the same as CriticalStop() if 'condition' is false. A C string can be passed as optional argument for output.
/// THREADSAFE.
#define CriticalAssert(condition, ...) do { if (!(condition)) { CriticalOutput(maxon::AssertHelper(strlen("Assertion failed: "), "Assertion failed: " #condition, "Assertion failed: " __VA_ARGS__)); } } while(false)

/// SizeAssert is a static assert verified at compile-time. It checks if the passed type is of size 's'.
/// On failure an exception of negative STATICASSERT_CONDITION_FALSE is raised.
/// THREADSAFE.
#define SizeAssert(type,s) static_assert(sizeof(type)==s,"type is not of passed size")

/// data type for comparison results
enum COMPARERESULT
{
	COMPARERESULT_LESS			= -1,			///< result is less than
	COMPARERESULT_EQUAL			=  0,			///< result is equal
	COMPARERESULT_GREATER		=  1,			///< result is greater than
	COMPARERESULT_ILLEGAL		= -1000		///< compare doesn't exist for an operator
} ENUM_LIST(COMPARERESULT);


class DefaultCompare
{
public:

	template <typename T> static inline COMPARERESULT Compare(const T& a, const T& b)
	{
		CriticalStop();
		return COMPARERESULT_ILLEGAL;

// will end up in endless recursion ...
// 		const DataTypeInfo *typeInfo = GetTypeInfo<T>();
// 		if (!typeInfo)
// 		{
// 			CriticalAssert(false);
// 			return COMPARERESULT_ILLEGAL;
// 		}
// 		return typeInfo->_compare(&a,&b);
	}

	static inline COMPARERESULT Compare(Bool a, Bool b)
	{
		return (a < b) ? COMPARERESULT_LESS : ((a > b) ? COMPARERESULT_GREATER : COMPARERESULT_EQUAL );
	}

	static inline COMPARERESULT Compare(Char a, Char b)
	{
		return (a < b) ? COMPARERESULT_LESS : ((a > b) ? COMPARERESULT_GREATER : COMPARERESULT_EQUAL );
	}

	static inline COMPARERESULT Compare(UChar a, UChar b)
	{
		return (a < b) ? COMPARERESULT_LESS : ((a > b) ? COMPARERESULT_GREATER : COMPARERESULT_EQUAL );
	}

	static inline COMPARERESULT Compare(Int16 a, Int16 b)
	{
		return (a < b) ? COMPARERESULT_LESS : (a > b) ? COMPARERESULT_GREATER : COMPARERESULT_EQUAL;
	}

	static inline COMPARERESULT Compare(UInt16 a, UInt16 b)
	{
		return (a < b) ? COMPARERESULT_LESS : (a > b) ? COMPARERESULT_GREATER : COMPARERESULT_EQUAL;
	}

	static inline COMPARERESULT Compare(Int32 a, Int32 b)
	{
		return (a < b) ? COMPARERESULT_LESS : (a > b) ? COMPARERESULT_GREATER : COMPARERESULT_EQUAL;
	}

	static inline COMPARERESULT Compare(UInt32 a, UInt32 b)
	{
		return (a < b) ? COMPARERESULT_LESS : (a > b) ? COMPARERESULT_GREATER : COMPARERESULT_EQUAL;
	}

	static inline COMPARERESULT Compare(Int64 a, Int64 b)
	{
		return (a < b) ? COMPARERESULT_LESS : (a > b) ? COMPARERESULT_GREATER : COMPARERESULT_EQUAL;
	}

	static inline COMPARERESULT Compare(UInt64 a, UInt64 b)
	{
		return (a < b) ? COMPARERESULT_LESS : (a > b) ? COMPARERESULT_GREATER : COMPARERESULT_EQUAL;
	}

	static inline COMPARERESULT Compare(Float32 a, Float32 b)
	{
		return (a < b) ? COMPARERESULT_LESS : (a > b) ? COMPARERESULT_GREATER : COMPARERESULT_EQUAL;
	}

	static inline COMPARERESULT Compare(Float64 a, Float64 b)
	{
		return (a < b) ? COMPARERESULT_LESS : (a > b) ? COMPARERESULT_GREATER : COMPARERESULT_EQUAL;
	}

	static inline COMPARERESULT Compare(const Char* a, const Char* b)
	{
		int res = strcmp(a,b);
		return (res < 0) ? COMPARERESULT_LESS : (res > 0) ? COMPARERESULT_GREATER : COMPARERESULT_EQUAL;
	}

};


/// data type for uninitialized classes.
/// special datatype to implement uninitialized classes. e.g. Vectors usally init all components with (0,0,0). Vector v(DC); will create an uninitialized vector
enum _DONTCONSTRUCT
{
	DC
};

//////////////////////////////////////////////////////////////////////////

struct MemoryAllocLocationPOD
{
	const Char*	file;
	Int	lineAndFlags;
	const Char*	name;
};

class MemoryAllocLocation : public MemoryAllocLocationPOD
{
public:
	MemoryAllocLocation(const Char* f, Int l, const Char* objectName = nullptr)
	{
		file = f;
		lineAndFlags = l;
		name = objectName;
	}

	const Char*	GetFile() const { return file; }
	Int	GetLine() const { return lineAndFlags & LINE_NUMBER_MASK; }
	Bool	HasFrameInfo() const { return (lineAndFlags & FRAME_INFO_FLAG) != 0; }

	enum { FRAME_INFO_FLAG = 0x1000000, LINE_NUMBER_MASK = 0xffffff };	// struct carries extended debug info if FRAME_INFO_FLAG is set
};

#define	C4D_MISC_ALLOC_LOCATION		maxon::MemoryAllocLocation(__FILE__, __LINE__)
#define	C4D_MISC_ALLOC_LOCATION_DECLARATION	const maxon::MemoryAllocLocation& allocLocation
#define C4D_MISC_ALLOC_LOCATION_FORWARD			allocLocation

//clashes with C4D
//#define GOTO_ERROR; { DebugOutput(maxon::OUTPUT_DIAGNOSTIC|maxon::OUTPUT_HEADER,"Error Exit", __FILE__, __LINE__); goto Error; }
//#define RETURN_FALSE { DebugOutput(maxon::OUTPUT_DIAGNOSTIC|maxon::OUTPUT_HEADER,"Returned false", __FILE__, __LINE__); return false; }

} // C4D_MISC_END

#endif
