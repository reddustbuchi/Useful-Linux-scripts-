#include "ge_math.h"	// place before #ifdef

#ifndef __GEVECTOR_H
	#define __GEVECTOR_H

struct Vector64;

struct Vector32
{
	Float32 x, y, z;

	Vector32() : x(0.0f), y(0.0f), z(0.0f) { }
	explicit Vector32(Float32 ix, Float32 iy, Float32 iz)  : x(ix), y(iy), z(iz) { }
	explicit Vector32(_DONTCONSTRUCT v){ }
	explicit Vector32(const Vector64& v);

#ifndef __LEGACY_API
	explicit Vector32(Float32 in) : x(in), y(in), z(in) { }
#else
	Vector32(Float32 in) : x(in), y(in), z(in) { }
	Float32								 Dot(const Vector32& v2) const { return x * v2.x + y * v2.y + z * v2.z; }
	Vector32							 Cross(const Vector32& v2) const { return Vector32(y * v2.z - z * v2.y, z * v2.x - x * v2.z, x * v2.y - y * v2.x); }
	inline const Vector64 ToLV() const;
	inline const Vector32& ToSV() const { return *this; }
	inline const Vector64 ToRV() const;
	friend Float32 operator * (const Vector32& v1, const Vector32& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }
	friend const Vector32 operator % (const Vector32& v1, const Vector32& v2) { return Vector32(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x); }
	inline const Vector32& operator *= (const Matrix32& m);
	inline const Vector32& operator ^= (const Matrix32& m);
	const Vector32&				 operator ^= (const Vector32& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
	friend const Vector32 operator ^ (const Vector32& v1, const Vector32& v2) { return Vector32(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z); }
#endif

	/// Checks if each component is zero.
	Bool IsZero() const
	{
		return (x == 0.0f) && (y == 0.0f) && (z == 0.0f);
	}

	/// Checks if one of the components is not zero.
	Bool IsNotZero() const
	{
		return (x != 0.0f) || (y != 0.0f) || (z != 0.0f);
	}

	/// Sets all components to zero.
	void SetZero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	/// Tests component-wise if the difference is no bigger than 'epsilon'
	Bool IsEqual(const Vector32& v2, const Float32& epsilon = 0.01f) const
	{
		return Abs(x - v2.x) < epsilon && Abs(y - v2.y) < epsilon && Abs(z - v2.z) < epsilon;
	}

	/// Calculates the average value of 'x', 'y' and 'z'
	Float32 GetAverage() const
	{
		return (x + y + z) * Float32(1.0 / 3.0);
	}

	/// Calculates the sum of 'x', 'y' and 'z'
	Float32 GetSum() const
	{
		return x + y + z;
	}

	/// Returns the minimum of 'x', 'y' and 'z'
	Float32 GetMin() const
	{
		if (x < y)
		{
			return (z < x) ? z : x;
		}
		else
		{
			return (z < y) ? z : y;
		}
	}

	/// Returns the maximum of 'x', 'y' and 'z'
	Float32 GetMax() const
	{
		if (x > y)
		{
			return (z > x) ? z : x;
		}
		else
		{
			return (z > y) ? z : y;
		}
	}

	/// Returns a vector that is clamped to the range [0.0 .. 1.0]
	Vector32 Clamp01() const
	{
		return Vector32(::Clamp01(x), ::Clamp01(y), ::Clamp01(z));
	}

	/// Calculates angle (in radians) between v1 and v2
	friend Float32 GetAngle(const Vector32& v1, const Vector32& v2)
	{
		Float32 il = Inverse(v1.GetSquaredLength() * v2.GetSquaredLength());
		return ACos((v1.x * v2.x + v1.y * v2.y + v1.z * v2.z) * Sqrt(il));
	}

	/// Calculates dot product of v1 and v2
	friend Float32 Dot(const Vector32& v1, const Vector32& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	/// Calculates cross product of v1 and v2
	friend Vector32	Cross(const Vector32& v1, const Vector32& v2)
	{
		return Vector32(v1.y * v2.z - v1.z * v2.y,
						 v1.z * v2.x - v1.x * v2.z,
						 v1.x * v2.y - v1.y * v2.x);
	}

	/// Returns the length of the vector
	Float32	GetLength(void) const
	{
		return Sqrt(x * x + y * y + z * z);
	}

	/// Returns the squared length of the vector
	Float32	GetSquaredLength(void) const
	{
		return x * x + y * y + z * z;
	}

	/// Returns a normalized vector, so that GetLength(vector)==1.0
	Vector32 GetNormalized(void) const
	{
		Float32 l = GetLength();

		if (l == 0.0f)
			return Vector32(0.0f, 0.0f, 0.0f);

		l = 1.0f / l;
		return Vector32(x * l, y * l, z * l);
	}

	/// Normalizes this vector, so that GetLength()==1.0
	void Normalize(void)
	{
		Float32 l = Sqrt(x * x + y * y + z * z);
		if (l != 0.0f)
		{
			l	 = 1.0f / l;
			x *= l;
			y *= l;
			z *= l;
		}
	}


	const Vector32& operator += (Float32 s)
	{
		x += s;
		y += s;
		z += s;
		return *this;
	}

	const Vector32& operator += (const Vector32& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	const Vector32& operator -= (Float32 s)
	{
		x -= s;
		y -= s;
		z -= s;
		return *this;
	}

	const Vector32& operator -= (const Vector32& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	// multiply each vector component by a scalar
	const Vector32& operator *= (Float32 s)
	{
		x *= s;
		y *= s;
		z *= s;

		return *this;
	}

	// divide each vector component by a scalar
	const Vector32& operator /= (Float32 s)
	{
		if (s)
		{
			s	 = 1.0f / s;
			x *= s;
			y *= s;
			z *= s;
		}
		else
		{
			x = y = z = 0.0f;
		}

		return *this;
	}

#ifndef __LEGACY_API
	// multiply vectors componentwise
	const Vector32& operator *= (const Vector32& v)
	{
		x *= v.x; y *= v.y; z *= v.z;
		return *this;
	}
#endif

	// GetLength()
	friend Float32 Len(const Vector32& v)
	{
		return Sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	// normalized operator (GetNormalized)
	friend const Vector32 operator ! (const Vector32& v)
	{
		Float32 l = Sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
		if (l == 0.0f)
			return Vector32(0.0f);
		l = 1.0f / l;
		return Vector32(v.x * l, v.y * l, v.z * l);
	}

	// multiply each vector component by a scalar
	friend const Vector32 operator * (Float32 s, const Vector32& v)
	{
		return Vector32(v.x * s, v.y * s, v.z * s);
	}

	// multiply each vector component by a scalar
	friend const Vector32 operator * (const Vector32& v, Float32 s)
	{
		return Vector32(v.x * s, v.y * s, v.z * s);
	}

	// divide each vector component by a scalar
	friend const Vector32 operator / (const Vector32& v, Float32 s)
	{
		if (s)
		{
			s = 1.0f / s;
			return Vector32(v.x * s, v.y * s, v.z * s);
		}
		return Vector32(0.0f);
	}

#ifndef __LEGACY_API
	// multiply vectors componentwise
	friend const Vector32 operator * (const Vector32& v1, const Vector32& v2)
	{
		return Vector32(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
	}
#endif

	friend const Vector32 operator + (Float32 s, const Vector32& v)
	{
		return Vector32(v.x + s, v.y + s, v.z + s);
	}

	friend const Vector32 operator + (const Vector32& v, Float32 s)
	{
		return Vector32(v.x + s, v.y + s, v.z + s);
	}

	friend const Vector32 operator + (const Vector32& v1, const Vector32& v2)
	{
		return Vector32(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}

	friend const Vector32 operator - (Float32 s, const Vector32& v)
	{
		return Vector32(s - v.x, s - v.y, s - v.z);
	}

	friend const Vector32 operator - (const Vector32& v, Float32 s)
	{
		return Vector32(v.x - s, v.y - s, v.z - s);
	}

	friend const Vector32 operator - (const Vector32& v1, const Vector32& v2)
	{
		return Vector32(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}

	friend const Vector32 operator - (const Vector32& v)
	{
		return Vector32(-v.x, -v.y, -v.z);
	}

	friend Bool operator == (const Vector32& v1, const Vector32& v2)
	{
		return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
	}

	friend Bool operator == (const Vector32& v1, Float32 r)
	{
		return (v1.x == r) && (v1.y == r) && (v1.z == r);
	}

	friend Bool operator != (const Vector32& v1, Float32 r)
	{
		return (v1.x != r) || (v1.y != r) || (v1.z != r);
	}

	friend Bool operator != (const Vector32& v1, const Vector32& v2)
	{
		return (v1.x != v2.x) || (v1.y != v2.y) || (v1.z != v2.z);
	}

	/// access vector component: index 0 is 'x', index 1 is 'y', index 2 is 'z'. All other values must not be used and will crash
	Float32& operator [](Int l)
	{
		return (&x)[l];
	}

	/// access vector component: index 0 is 'x', index 1 is 'y', index 2 is 'z'.  All other values must not be used and will crash
	const Float32& operator [](Int l) const
	{
		return (&x)[l];
	}
};

#endif
