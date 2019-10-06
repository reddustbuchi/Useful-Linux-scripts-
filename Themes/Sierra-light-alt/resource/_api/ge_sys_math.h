#ifndef __SYSMATH_H
#define __SYSMATH_H

#include <math.h>
#ifdef USE_API_MAXON
	#include "apibase.h"
#else
	#include "c4d_misc/general.h"
#endif

#ifdef __PC
	#pragma warning(disable:4805)	// boolean
	#pragma warning(error: 4265)	// non-virtual destructor of virtual classes

	#define __TYPES_READY
#endif

#if defined(__LINUX) || defined (__MAC)
	#define GCC34T this->
#endif

#ifndef TRUE
	#define TRUE 1
#endif

#ifndef FALSE
	#define FALSE	0
#endif

#ifndef NULL
	#define NULL 0
#endif

typedef int Bool;
typedef void*								Hndl;
typedef int	INT;
typedef unsigned int UINT;

typedef maxon::Char Char;
typedef maxon::UChar	UChar;
typedef maxon::Int16	Int16;
typedef maxon::UInt16 UInt16;
typedef maxon::Int32	Int32;
typedef maxon::UInt32 UInt32;
typedef maxon::Int64	Int64;
typedef maxon::UInt64 UInt64;
typedef maxon::Int	Int;
typedef maxon::UInt UInt;
typedef maxon::Float	Float;
typedef maxon::Float64	Float64;
typedef maxon::Float32	Float32;

#define EPSILON90	0.997	//EPSILON for 90 degrees
#define EPSILON		0.0001
#define EPSILON5	1e-5	//0.00001
#define EPSILON6	1e-6
#define EPSILON7	1e-7
#define EPSILON8	1e-8
#define EPSILON10 1e-10
#define EPSILON12 1e-12
#define EPSILON16	1e-16

inline Float32 FMin(Float32 a, Float32 b)
{
	if (a < b)
		return a;
	return b;
}
inline Float64 FMin(Float64 a, Float64 b)
{
	if (a < b)
		return a;
	return b;
}
inline Int32 LMin(Int32 a, Int32 b)
{
	if (a < b)
		return a;
	return b;
}
inline Int VMin(Int a, Int b)
{
	if (a < b)
		return a;
	return b;
}

inline Float32 FMax(Float32 a, Float32 b)
{
	if (a < b)
		return b;
	return a;
}
inline Float64 FMax(Float64 a, Float64 b)
{
	if (a < b)
		return b;
	return a;
}
inline Int32 LMax(Int32 a, Int32 b)
{
	if (a < b)
		return b;
	return a;
}
inline Int VMax(Int a, Int b)
{
	if (a < b)
		return b;
	return a;
}

inline Int32 LCut(Int32 a, Int32 b, Int32 c)
{
	if (a < b)
		return b;
	if (a > c)
		return c;
	return a;
}
inline Int VCut(Int a, Int b, Int c)
{
	if (a < b)
		return b;
	if (a > c)
		return c;
	return a;
}

/// Calculates the sign of a value. If the value is 0 or positive the result is 1, otherwise -1.
template <typename X> inline Int Sign(X f)
{
	if (f < (X)0)
		return -1;
	return 1;
}

template <typename T, typename U> inline T Mod(T a, U b)
{
	return a < 0 ? a - (((a - b + 1) / b) * b) : a % b;
}

#ifndef NOTOK
	#define NOTOK -1
#endif

// Type value ranges, math constants and trigonometric functions into global namespace
#include "c4d_misc/utilities/apibasemath.h"

#if 0
	#define ENUM_END_FLAGS ENUM_FLAGS
	#define ENUM_END_LIST	 ENUM_LIST
#else
class IllegalEnumAccess
{
public:
	IllegalEnumAccess() { }
};

class IllegalFlagAccess
{
public:
	IllegalFlagAccess() { }
};

#define ENUM_END_FLAGS(X) ;\
	inline X operator | (X a, X b) { return X(UInt32(a) | UInt32(b)); }	\
	inline X operator & (X a, X b) { return X(UInt32(a) & UInt32(b)); }	\
	inline X operator ^ (X a, X b) { return X(UInt32(a) ^ UInt32(b)); }	\
	inline X operator >> (X a, X b) { return X(UInt32(a) << UInt32(b)); }	\
	inline X operator << (X a, X b) { return X(UInt32(a) >> UInt32(b)); }	\
	inline X operator ~ (X a) { return X(~UInt32(a)); }	\
	inline X& operator |= (X& a, const X& b) { a = X(UInt32(a) | UInt32(b)); return a; } \
	inline X& operator &= (X& a, const X& b) { a = X(UInt32(a) & UInt32(b)); return a; } \
	inline X& operator ^= (X& a, const X& b) { a = X(UInt32(a) ^ UInt32(b)); return a; } \
	inline IllegalFlagAccess operator ++ (X a) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator ++ (X a, int) { return IllegalFlagAccess(); }	\
	inline IllegalFlagAccess operator -- (X a) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator -- (X a, int) { return IllegalFlagAccess(); }	\
	inline IllegalFlagAccess operator != (X s1, Int32 s2) { return IllegalFlagAccess(); }	\
	inline IllegalFlagAccess operator != (Int32 s2, X s1) { return IllegalFlagAccess(); }	\
	inline IllegalFlagAccess operator == (X s1, Int32 s2) { return IllegalFlagAccess(); }	\
	inline IllegalFlagAccess operator == (Int32 s2, X s1) { return IllegalFlagAccess(); }	\
	inline IllegalFlagAccess operator < (X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator < (X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator < (Int32 s2, X s1) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator <= (X s1, X s2) { return IllegalFlagAccess(); }	\
	inline IllegalFlagAccess operator <= (X s1, Int32 s2) { return IllegalFlagAccess(); }	\
	inline IllegalFlagAccess operator <= (Int32 s2, X s1) { return IllegalFlagAccess(); }	\
	inline IllegalFlagAccess operator > (X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator > (X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator > (Int32 s2, X s1) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator >= (X s1, Int32 s2) { return IllegalFlagAccess(); }	\
	inline IllegalFlagAccess operator >= (X s1, X s2) { return IllegalFlagAccess(); }	\
	inline IllegalFlagAccess operator >= (Int32 s2, X s1) { return IllegalFlagAccess(); }	\
	inline IllegalFlagAccess operator + (X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator + (X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator + (Int32 s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator - (X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator - (X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator - (Int32 s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator * (X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator * (X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator * (Int32 s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator / (X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator / (X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator / (Int32 s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator % (X s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator % (X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator % (Int32 s1, X s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator ^ (X s1, Int32 s2) { return IllegalFlagAccess(); } \
	inline IllegalFlagAccess operator ^ (Int32 s1, X s2) { return IllegalFlagAccess(); }	// -V524

	#define ENUM_END_LIST(X) ; \
	inline IllegalEnumAccess operator | (X a, X b) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator & (X a, X b) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator ~ (X a) { return IllegalEnumAccess(); }	\
	inline IllegalEnumAccess operator ++ (X a) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator ++ (X a, int) { return IllegalEnumAccess(); }	\
	inline IllegalEnumAccess operator -- (X a) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator -- (X a, int) { return IllegalEnumAccess(); }	\
	inline IllegalEnumAccess operator == (X s1, Int32 s2) { return IllegalEnumAccess(); }	\
	inline IllegalEnumAccess operator == (Int32 s2, X s1) { return IllegalEnumAccess(); }	\
	inline IllegalEnumAccess operator != (X s1, Int32 s2) { return IllegalEnumAccess(); }	\
	inline IllegalEnumAccess operator != (Int32 s2, X s1) { return IllegalEnumAccess(); }	\
	inline IllegalEnumAccess operator ! (X a) { return IllegalEnumAccess(); }	\
	inline IllegalEnumAccess operator + (X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator + (Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator - (X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator - (Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator * (X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator * (Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator / (X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator / (Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator % (X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator % (Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator < (X s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator < (X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator < (Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator > (X s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator > (X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator > (Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator <= (X s1, X s2) { return IllegalEnumAccess(); }	\
	inline IllegalEnumAccess operator <= (X s1, Int32 s2) { return IllegalEnumAccess(); }	\
	inline IllegalEnumAccess operator <= (Int32 s1, X s2) { return IllegalEnumAccess(); }	\
	inline IllegalEnumAccess operator >= (X s1, X s2) { return IllegalEnumAccess(); }	\
	inline IllegalEnumAccess operator >= (X s1, Int32 s2) { return IllegalEnumAccess(); }	\
	inline IllegalEnumAccess operator >= (Int32 s1, X s2) { return IllegalEnumAccess(); }	\
	inline IllegalEnumAccess operator << (X s1, Int32 s2) { return IllegalEnumAccess(); }	\
	inline IllegalEnumAccess operator << (Int32 s1, X s2) { return IllegalEnumAccess(); }	\
	inline IllegalEnumAccess operator >> (X s1, Int32 s2) { return IllegalEnumAccess(); }	\
	inline IllegalEnumAccess operator >> (Int32 s1, X s2) { return IllegalEnumAccess(); }	\
	inline IllegalEnumAccess operator ^ (X s1, Int32 s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator ^ (Int32 s1, X s2) { return IllegalEnumAccess(); } \
	inline IllegalEnumAccess operator || (X s1, X s2) { return IllegalEnumAccess(); }	\
	inline IllegalEnumAccess operator || (X s1, Int32 s2) { return IllegalEnumAccess(); }	\
	inline IllegalEnumAccess operator || (Int32 s1, X s2) { return IllegalEnumAccess(); }	\
	inline IllegalEnumAccess operator && (X s1, X s2) { return IllegalEnumAccess(); }	\
	inline IllegalEnumAccess operator && (X s1, Int32 s2) { return IllegalEnumAccess(); }	\
	inline IllegalEnumAccess operator && (Int32 s1, X s2) { return IllegalEnumAccess(); }	// -V524
#endif

#endif
