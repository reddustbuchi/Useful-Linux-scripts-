#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#include "ge_math.h"

template <class TYPE> class _Vector4
{
public:
	_Vector4(_DONTCONSTRUCT dc)
	{
	}

	_Vector4()
	{
		m_prElements[0] = (TYPE)0.0; m_prElements[1] = (TYPE)0.0; m_prElements[2] = (TYPE)0.0; m_prElements[3] = (TYPE)1.0;
	}

	_Vector4(TYPE x, TYPE y, TYPE z, TYPE w)
	{
		m_prElements[0] = x; m_prElements[1] = y; m_prElements[2] = z; m_prElements[3] = w;
	}

	explicit _Vector4(TYPE v)
	{
		// sets all (including w) elements to v
		m_prElements[0] = m_prElements[1] = m_prElements[2] = m_prElements[3] = v;
	}

	explicit _Vector4(const Vector32& v)
	{
		m_prElements[0] = (TYPE)v.x; m_prElements[1] = (TYPE)v.y; m_prElements[2] = (TYPE)v.z; m_prElements[3] = (TYPE)1.0;
	}

	explicit _Vector4(const Vector32& v, Float32 r)
	{
		m_prElements[0] = (TYPE)v.x; m_prElements[1] = (TYPE)v.y; m_prElements[2] = (TYPE)v.z; m_prElements[3] = (TYPE)r;
	}

	explicit _Vector4(const Vector64& v)
	{
		m_prElements[0] = (TYPE)v.x; m_prElements[1] = (TYPE)v.y; m_prElements[2] = (TYPE)v.z; m_prElements[3] = (TYPE)1.0;
	}

	explicit _Vector4(const Vector64& v, Float64 r)
	{
		m_prElements[0] = (TYPE)v.x; m_prElements[1] = (TYPE)v.y; m_prElements[2] = (TYPE)v.z; m_prElements[3] = (TYPE)r;
	}

	void SetZero()
	{
		m_prElements[0] = m_prElements[1] = m_prElements[2] = m_prElements[3] = (TYPE)0.0;
	}

	// dot product: this . b
	const TYPE Dot(const _Vector4& b)
	{
		return x * b.x + y * b.y + z * b.z + w * b.w;
	}

	// normalize the vector so that w is 1
	void MakeVector3()
	{
		if (m_prElements[3] == (TYPE)0.0)
		{
			m_prElements[0] = MAXVALUE_FLOAT32;
			m_prElements[1] = MAXVALUE_FLOAT32;
			m_prElements[2] = MAXVALUE_FLOAT32;
		}
		else
		{
			m_prElements[0] /= m_prElements[3];
			m_prElements[1] /= m_prElements[3];
			m_prElements[2] /= m_prElements[3];
		}
		m_prElements[3] = (TYPE)1.0;
	}

	friend const _Vector4 operator - (const _Vector4& a, const _Vector4& b)
	{
		return _Vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}

	friend const _Vector4 operator + (const _Vector4& a, const _Vector4& b)
	{
		return _Vector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}

	const _Vector4& operator += (const _Vector4& a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
		w += a.w;
		return *this;
	}

	// multiply each vector component by a scalar
#ifdef __PC
	__forceinline
#else
	__attribute((always_inline))
#endif
	const _Vector4 &operator *=(const Float a)
	{
		x *= (TYPE)a;
		y *= (TYPE)a;
		z *= (TYPE)a;
		w *= (TYPE)a;
		return *this;
	}

	// multiply vectors componentwise
	friend const _Vector4 operator ^ (const _Vector4& a, const _Vector4& b)
	{
		return _Vector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
	}

	// dot product: a . b
	friend const TYPE Dot(const _Vector4& a, const _Vector4& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	// multiply each vector component by a scalar
	friend const _Vector4 operator * (const _Vector4& a, TYPE b)
	{
		return _Vector4(a.x * b, a.y * b, a.z * b, a.w * b);
	}

	friend const Vector& GetVector3(const _Vector4& v)
	{
		return *((Vector*)(v.m_prElements));
	}

	friend Bool operator == (const _Vector4& a, const _Vector4& b)
	{
		return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
	}

	union
	{
		struct { TYPE x, y, z, w; };
		TYPE m_prElements[4];
	};
};

typedef _Vector4<Float32> Vector4d32;
typedef _Vector4<Float64> Vector4d64;

#ifdef __FLOAT_32_BIT
	#define Vector4d Vector4d32
	#define RVtoSV4(x) (x)
#else
	#define Vector4d Vector4d64
	#define RVtoSV4(_x_) Vector4d32((Float32)_x_.x, (Float32)_x_.y, (Float32)_x_.z, (Float32)_x_.w)
#endif

#endif	// _VECTOR4_H_
