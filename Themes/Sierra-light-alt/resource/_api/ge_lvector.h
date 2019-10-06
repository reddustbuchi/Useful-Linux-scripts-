#include "ge_math.h"	// place before #ifdef

#ifndef __GELVECTOR_H
	#define __GELVECTOR_H

struct Vector64
{
	Float64 x, y, z;

	Vector64() : x(0.0), y(0.0), z(0.0) { }
	explicit Vector64(Float64 ix, Float64 iy, Float64 iz)  : x(ix), y(iy), z(iz) { }
	explicit Vector64(_DONTCONSTRUCT v) { }
	explicit Vector64(const Vector32& v) : x(v.x), y(v.y), z(v.z) { }

#ifndef __LEGACY_API
	explicit Vector64(Float64 in) : x(in), y(in), z(in) { }
#else
	Vector64(Float64 in) : x(in), y(in), z(in) { }
	Float64								 Dot(const Vector32& v) const { return x * Float64(v.x) + y* Float64(v.y) + z* Float64(v.z); }
	Float64								 Dot(const Vector64& v2) const { return x * v2.x + y * v2.y + z * v2.z; }
	Vector64							 Cross(const Vector64& v2) const { return Vector64(y * v2.z - z * v2.y, z * v2.x - x * v2.z, x * v2.y - y * v2.x); }
	inline const Vector32	 ToSV() const { return Vector32((Float32)x, (Float32)y, (Float32)z); }
	inline const Vector64& ToLV() const { return *this; }
	inline const Vector64& ToRV() const { return *this; }
	friend Float64 operator * (const Vector64& v1, const Vector64& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }
	friend const Vector64 operator % (const Vector64& v1, const Vector64& v2) { return Vector64(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x); }
	inline const Vector64& operator *= (const Matrix64& m);
	inline const Vector64& operator ^= (const Matrix64& m);
	const Vector64&				 operator ^= (const Vector64& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
	friend const Vector64 operator ^ (const Vector64& v1, const Vector64& v2) { return Vector64(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z); }
#endif

	/// Checks if each component is zero.
	Bool IsZero() const
	{
		return (x == 0.0) && (y == 0.0) && (z == 0.0);
	}

	/// Checks if one of the components is not zero.
	Bool IsNotZero() const
	{
		return (x != 0.0) || (y != 0.0) || (z != 0.0);
	}

	/// Sets all components to zero.
	void SetZero()
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}

	/// Tests component-wise if the difference is no bigger than 'epsilon'
	Bool IsEqual(const Vector64& v2, const Float64& epsilon = 0.01) const
	{
		return Abs(x - v2.x) < epsilon && Abs(y - v2.y) < epsilon && Abs(z - v2.z) < epsilon;
	}

	/// Calculates the average value of 'x', 'y' and 'z'
	Float64 GetAverage() const
	{
		return (x + y + z) * (1.0 / 3.0);
	}

	/// Calculates the sum of 'x', 'y' and 'z'
	Float64 GetSum() const
	{
		return x + y + z;
	}

	/// Returns the minimum of 'x', 'y' and 'z'
	Float64 GetMin() const
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
	Float64 GetMax() const
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
	Vector64 Clamp01() const
	{
		return Vector64(::Clamp01(x), ::Clamp01(y), ::Clamp01(z));
	}

	/// Calculates angle (in radians) between v1 and v2
	friend Float64 GetAngle(const Vector64& v1, const Vector64& v2)
	{
		Float64 il = Inverse(v1.GetSquaredLength() * v2.GetSquaredLength());
		return ACos((v1.x * v2.x + v1.y * v2.y + v1.z * v2.z) * Sqrt(il));
	}

	/// Calculates dot product of v1 and v2
	friend Float64 Dot(const Vector64& v1, const Vector64& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	/// Calculates cross product of v1 and v2
	friend Vector64	Cross(const Vector64& v1, const Vector64& v2)
	{
		return Vector64(v1.y * v2.z - v1.z * v2.y,
						 v1.z * v2.x - v1.x * v2.z,
						 v1.x * v2.y - v1.y * v2.x);
	}

	/// Returns the length of the vector
	Float64	GetLength(void) const
	{
		return Sqrt(x * x + y * y + z * z);
	}

	/// Returns the squared length of the vector
	Float64	GetSquaredLength(void) const
	{
		return x * x + y * y + z * z;
	}

	/// Returns a normalized vector, so that GetLength(vector)==1.0
	Vector64 GetNormalized(void) const
	{
		Float64 l = GetLength();

		if (l == 0.0)
			return Vector64(0.0, 0.0, 0.0);

		l = 1.0 / l;
		return Vector64(x * l, y * l, z * l);
	}

	/// Normalizes this vector, so that GetLength()==1.0
	void Normalize(void)
	{
		Float64 l = Sqrt(x * x + y * y + z * z);
		if (l != 0.0)
		{
			l	 = 1.0 / l;
			x *= l;
			y *= l;
			z *= l;
		}
	}


	const Vector64& operator += (Float64 s)
	{
		x += s;
		y += s;
		z += s;
		return *this;
	}

	const Vector64& operator += (const Vector64& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	const Vector64& operator -= (Float64 s)
	{
		x -= s;
		y -= s;
		z -= s;
		return *this;
	}

	const Vector64& operator -= (const Vector64& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	// multiply each vector component by a scalar
	const Vector64& operator *= (Float64 s)
	{
		x *= s;
		y *= s;
		z *= s;

		return *this;
	}

	// divide each vector component by a scalar
	const Vector64& operator /= (Float64 s)
	{
		if (s)
		{
			s	 = 1.0 / s;
			x *= s;
			y *= s;
			z *= s;
		}
		else
		{
			x = y = z = 0.0;
		}

		return *this;
	}

#ifndef __LEGACY_API
	// multiply vectors componentwise
	const Vector64& operator *= (const Vector64& v)
	{
		x *= v.x; y *= v.y; z *= v.z;
		return *this;
	}
#endif

	// GetLength()
	friend Float64 Len(const Vector64& v)
	{
		return Sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	// normalized operator (GetNormalized)
	friend const Vector64 operator ! (const Vector64& v)
	{
		Float64 l = Sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
		if (l == 0.0)
			return Vector64(0.0);
		l = 1.0 / l;
		return Vector64(v.x * l, v.y * l, v.z * l);
	}

	// multiply each vector component by a scalar
	friend const Vector64 operator * (Float64 s, const Vector64& v)
	{
		return Vector64(v.x * s, v.y * s, v.z * s);
	}

	// multiply each vector component by a scalar
	friend const Vector64 operator * (const Vector64& v, Float64 s)
	{
		return Vector64(v.x * s, v.y * s, v.z * s);
	}

	// divide each vector component by a scalar
	friend const Vector64 operator / (const Vector64& v, Float64 s)
	{
		if (s)
		{
			s = 1.0 / s;
			return Vector64(v.x * s, v.y * s, v.z * s);
		}
		return Vector64(0.0);
	}

#ifndef __LEGACY_API
	// multiply vectors componentwise
	friend const Vector64 operator * (const Vector64& v1, const Vector64& v2)
	{
		return Vector64(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
	}
#endif

	friend const Vector64 operator + (Float64 s, const Vector64& v)
	{
		return Vector64(v.x + s, v.y + s, v.z + s);
	}

	friend const Vector64 operator + (const Vector64& v, Float64 s)
	{
		return Vector64(v.x + s, v.y + s, v.z + s);
	}

	friend const Vector64 operator + (const Vector64& v1, const Vector64& v2)
	{
		return Vector64(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}

	friend const Vector64 operator - (Float64 s, const Vector64& v)
	{
		return Vector64(s - v.x, s - v.y, s - v.z);
	}

	friend const Vector64 operator - (const Vector64& v, Float64 s)
	{
		return Vector64(v.x - s, v.y - s, v.z - s);
	}

	friend const Vector64 operator - (const Vector64& v1, const Vector64& v2)
	{
		return Vector64(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}

	friend const Vector64 operator - (const Vector64& v)
	{
		return Vector64(-v.x, -v.y, -v.z);
	}

	friend Bool operator == (const Vector64& v1, const Vector64& v2)
	{
		return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
	}

	friend Bool operator == (const Vector64& v1, Float64 r)
	{
		return (v1.x == r) && (v1.y == r) && (v1.z == r);
	}

	friend Bool operator != (const Vector64& v1, Float64 r)
	{
		return (v1.x != r) || (v1.y != r) || (v1.z != r);
	}

	friend Bool operator != (const Vector64& v1, const Vector64& v2)
	{
		return (v1.x != v2.x) || (v1.y != v2.y) || (v1.z != v2.z);
	}

	/// access vector component: index 0 is 'x', index 1 is 'y', index 2 is 'z'. All other values must not be used and will crash
	Float64& operator [](Int l)
	{
		return (&x)[l];
	}

	/// access vector component: index 0 is 'x', index 1 is 'y', index 2 is 'z'.  All other values must not be used and will crash
	const Float64& operator [](Int l) const
	{
		return (&x)[l];
	}
};

	#ifdef __LEGACY_API
inline const Vector64 Vector32::ToLV() const { return Vector64((Float64)x, (Float64)y, (Float64)z); }
inline const Vector64 Vector32::ToRV() const { return Vector64((Float64)x, (Float64)y, (Float64)z); }
	#endif

#endif
