#ifndef __GE_MATH_H
#define __GE_MATH_H

#include "ge_sys_math.h"

#ifndef GCC34T
	#define GCC34T
#endif

typedef UChar PIX;
typedef UChar PIX_C;
typedef UInt16 PIX_W;
typedef Float32 PIX_F;

Bool CompareFloatTolerant(Float32 a, Float32 b);
Bool CompareFloatTolerant(Float64 a, Float64 b);

// true for FP_NORMAL, FP_SUBNORMAL, FP_ZERO
// false for FP_NAN, FP_INFINITE
inline Bool CheckFloat(Float32 r)
{
	union { Float32 f; UInt32 u; } u = { r };

	return ((u.u >> 23) & 0xff) != 0xff;
}

inline Bool CheckFloat(Float64 r)
{
	union { Float64 f; UInt64 u; } u = { r };

	return ((~u.u >> 52) & 0x7ff) != 0;
}

// Only NANs and Infinity are corrected - denormalized numbers not
inline Float32 RepairFloat(Float32 r)
{
	if (!CheckFloat(r))
		return 0.0;

	return r;
}

inline Float64 RepairFloat(Float64 r)
{
	if (!CheckFloat(r))
		return 0.0;

	return r;
}

extern Bool __NET;
extern Bool __SERVER;
extern Bool __CLIENT;
extern Bool __BODYPAINT;
extern Bool __STUDENT;
extern Bool __PARALLEL;
extern Bool __UPDATER;
extern Bool __INSTALLER;
extern Bool __LICENSESERVER;
extern Bool __MEDIZINI;
extern Bool __LITE;

#define C4D_FOUR_BYTE(x1, x2, x3, x4)			((x1 << 24) | (x2 << 16) | (x3 << 8) | x4)
#define	C4D_RESERVE_PRIVATE_TYPE(type, x)	type x

struct Vector64;
struct Matrix64;
struct Vector32;
struct Matrix32;

enum _DONTCONSTRUCT
{
	DC
};

enum _EMPTYCONSTRUCT
{
	EC
};

// necessary to import in exactly this order
#include "ge_vector.h"
#include "ge_lvector.h"
#include "ge_matrix.h"
#include "ge_lmatrix.h"

#ifdef __FLOAT_32_BIT
typedef Vector32 Vector;
typedef Matrix32 Matrix;
#else
typedef Vector64 Vector;
typedef Matrix64 Matrix;
#endif

#include "legacy.h"

#endif
