#include "ge_math.h"	// place before #ifdef

#ifndef __GELMATRIX_H
	#define __GELMATRIX_H

struct Matrix64
{
	Vector64 off, v1, v2, v3;

	Matrix64()
	{
		off = Vector64(0.0, 0.0, 0.0);
		v1	= Vector64(1.0, 0.0, 0.0);
		v2	= Vector64(0.0, 1.0, 0.0);
		v3	= Vector64(0.0, 0.0, 1.0);
	}
	explicit Matrix64(const Vector64& off_in, const Vector64& v1_in, const Vector64& v2_in, const Vector64& v3_in)
	{
		off = off_in;
		v1	= v1_in;
		v2	= v2_in;
		v3	= v3_in;
	}
	explicit Matrix64(_DONTCONSTRUCT v) : off(v), v1(v), v2(v), v3(v){ }
	explicit Matrix64(const Matrix32& m) : off((Vector64)m.off), v1((Vector64)m.v1), v2((Vector64)m.v3), v3((Vector64)m.v3) { }

#ifdef __LEGACY_API
	friend const Matrix64 operator ! (const Matrix64& m) { return ~m; }
	Vector32 Mul(const Vector32& v) const { Float64 x = v.x, y = v.y, z = v.z; return Vector32(Float32(off.x + v1.x * x + v2.x * y + v3.x * z), Float32(off.y + v1.y * x + v2.y * y + v3.y * z), Float32(off.z + v1.z * x + v2.z * y + v3.z * z)); }
	Vector64 Mul(const Vector64& v) const { return Vector64(off.x + v1.x * v.x + v2.x * v.y + v3.x * v.z, off.y + v1.y * v.x + v2.y * v.y + v3.y * v.z, off.z + v1.z * v.x + v2.z * v.y + v3.z * v.z); }
	Vector32 MulV(const Vector32& v) const { Float64 x = v.x, y = v.y, z = v.z; return Vector32(Float32(v1.x * x + v2.x * y + v3.x * z), Float32(v1.y * x + v2.y * y + v3.y * z), Float32(v1.z * x + v2.z * y + v3.z * z)); }
	Vector64 MulV(const Vector64& v) const { return Vector64(v1.x * v.x + v2.x * v.y + v3.x * v.z, v1.y * v.x + v2.y * v.y + v3.y * v.z, v1.z * v.x + v2.z * v.y + v3.z * v.z); }
	friend const Vector64 operator ^ (const Vector64& v, const Matrix64& m) { return Vector64(m.v1.x * v.x + m.v2.x * v.y + m.v3.x * v.z, m.v1.y * v.x + m.v2.y * v.y + m.v3.y * v.z, m.v1.z * v.x + m.v2.z * v.y + m.v3.z * v.z); }
	friend const Vector64 operator * (const Vector64& v, const Matrix64& m) { return Vector64(m.off.x + m.v1.x * v.x + m.v2.x * v.y + m.v3.x * v.z, m.off.y + m.v1.y * v.x + m.v2.y * v.y + m.v3.y * v.z, m.off.z + m.v1.z * v.x + m.v2.z * v.y + m.v3.z * v.z); }
	inline const Matrix32	 ToSM() const { return Matrix32((Vector32)off, (Vector32)v1, (Vector32)v2, (Vector32)v3); }
	inline const Matrix64& ToLM() const { return *this; }
	inline const Matrix64& ToRM() const { return *this; }
#endif

	/// Multiplies two matrices.
	/// The rule is m1 AFTER m2
	/// If you transform a point with the result matrix this is identical to first transforming with m2 and then with m1
	Matrix64 operator *(const Matrix64& m2) const
	{
		return Matrix64(off + v1 * m2.off.x + v2 * m2.off.y + v3 * m2.off.z,
						 v1 * m2.v1.x + v2 * m2.v1.y + v3 * m2.v1.z,
						 v1 * m2.v2.x + v2 * m2.v2.y + v3 * m2.v2.z,
						 v1 * m2.v3.x + v2 * m2.v3.y + v3 * m2.v3.z);
	}

	/// Transforms a point by a matrix
	Vector64 operator *(const Vector64& v) const
	{
		return Vector64(off.x + v1.x * v.x + v2.x * v.y + v3.x * v.z,
						 off.y + v1.y * v.x + v2.y * v.y + v3.y * v.z,
						 off.z + v1.z * v.x + v2.z * v.y + v3.z * v.z);
	}

	/// Scales all matrix components by a scalar value
	friend Matrix64 operator *(Float64 s, const Matrix64& m)
	{
		return Matrix64(s * m.off, s * m.v1, s * m.v2, s * m.v3);
	}

	/// Scales all matrix components by a scalar value
	Matrix64 operator *(Float64 s) const
	{
		return Matrix64(off * s, v1 * s, v2 * s, v3 * s);
	}

	Vector64 TransformVector(const Vector64& v) const
	{
		return Vector64(v1.x * v.x + v2.x * v.y + v3.x * v.z, v1.y * v.x + v2.y * v.y + v3.y * v.z, v1.z * v.x + v2.z * v.y + v3.z * v.z);
	}

	friend const Matrix64 operator / (const Matrix64& m, const Float64 s)
	{
		return Matrix64(m.off / s, m.v1 / s, m.v2 / s, m.v3 / s);
	}

	friend const Matrix64 operator + (const Matrix64& m1, const Matrix64& m2)
	{
		return Matrix64(m1.off + m2.off, m1.v1 + m2.v1, m1.v2 + m2.v2, m1.v3 + m2.v3);
	}

	friend const Matrix64 operator - (const Matrix64& m1, const Matrix64& m2)
	{
		return Matrix64(m1.off - m2.off, m1.v1 - m2.v1, m1.v2 - m2.v2, m1.v3 - m2.v3);
	}

	friend Bool operator == (const Matrix64& m1, const Matrix64& m2)
	{
		return (m1.off == m2.off) && (m1.v1 == m2.v1) && (m1.v2 == m2.v2) && (m1.v3 == m2.v3);
	}

	friend Bool operator != (const Matrix64& m1, const Matrix64& m2)
	{
		return !(m1 == m2);
	}

	friend const Matrix64 operator ~ (const Matrix64& m)
	{
		Matrix64 mi(DC);

		Float64 det = (m.v1.x * (m.v2.y * m.v3.z - m.v3.y * m.v2.z) +
									 m.v2.x * (m.v3.y * m.v1.z - m.v1.y * m.v3.z) +
									 m.v3.x * (m.v1.y * m.v2.z - m.v2.y * m.v1.z));
		if (det == 0.0)
			return Matrix64();

		det = 1.0 / det;
		mi.off.x = (m.v2.x * (m.off.y * m.v3.z - m.v3.y * m.off.z) +
								m.v3.x * (m.off.z * m.v2.y - m.off.y * m.v2.z) +
								m.off.x * (m.v3.y * m.v2.z - m.v2.y * m.v3.z)) * det;
		mi.off.y = (m.v3.x * (m.off.y * m.v1.z - m.v1.y * m.off.z) +
								m.off.x * (m.v1.y * m.v3.z - m.v3.y * m.v1.z) +
								m.v1.x * (m.v3.y * m.off.z - m.off.y * m.v3.z)) * det;
		mi.off.z = (m.off.x * (m.v2.y * m.v1.z - m.v1.y * m.v2.z) +
								m.v1.x * (m.v2.z * m.off.y - m.v2.y * m.off.z) +
								m.v2.x * (m.off.z * m.v1.y - m.off.y * m.v1.z)) * det;

		mi.v1.x = (m.v2.y * m.v3.z - m.v3.y * m.v2.z) * det;
		mi.v1.y = (m.v3.y * m.v1.z - m.v1.y * m.v3.z) * det;
		mi.v1.z = (m.v1.y * m.v2.z - m.v2.y * m.v1.z) * det;

		mi.v2.x = (m.v2.z * m.v3.x - m.v3.z * m.v2.x) * det;
		mi.v2.y = (m.v3.z * m.v1.x - m.v1.z * m.v3.x) * det;
		mi.v2.z = (m.v1.z * m.v2.x - m.v2.z * m.v1.x) * det;

		mi.v3.x = (m.v2.x * m.v3.y - m.v3.x * m.v2.y) * det;
		mi.v3.y = (m.v3.x * m.v1.y - m.v1.x * m.v3.y) * det;
		mi.v3.z = (m.v1.x * m.v2.y - m.v2.x * m.v1.y) * det;

		return mi;
	}

	void Normalize(void)
	{
		v1.Normalize();
		v2.Normalize();
		v3.Normalize();
	}

	Matrix64 GetTensorMatrix(void) const
	{
		return Matrix64(Vector64(0.0), Vector64(v3.z * v2.y - v3.y * v2.z, v3.x * v2.z - v3.z * v2.x, v3.y * v2.x - v3.x * v2.y), Vector64(v3.y * v1.z - v1.y * v3.z, v3.z * v1.x - v3.x * v1.z, v1.y * v3.x - v3.y * v1.x), Vector64(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x));
	}

	void Scale(const Vector64& v)
	{
		v1 *= v.x;
		v2 *= v.y;
		v3 *= v.z;
	}

	void Scale(Float64 r)
	{
		v1 *= r;
		v2 *= r;
		v3 *= r;
	}

	Vector64& operator [](Int32 i) const { return ((Vector64*)this)[i & 3]; }

	Vector64 Scale(void) const { return Vector64(Len(v1), Len(v2), Len(v3)); }
};

	#ifdef __LEGACY_API
inline const Vector64& Vector64::operator *= (const Matrix64& m) { Float64 xx = m.off.x + m.v1.x * x + m.v2.x * y + m.v3.x * z; Float64 yy = m.off.y + m.v1.y * x + m.v2.y * y + m.v3.y * z; Float64 zz = m.off.z + m.v1.z * x + m.v2.z * y + m.v3.z * z; x = xx; y = yy; z = zz; return *this; }
inline const Vector64& Vector64::operator ^= (const Matrix64& m) { Float64 xx = m.v1.x * x + m.v2.x * y + m.v3.x * z; Float64 yy = m.v1.y * x + m.v2.y * y + m.v3.y * z; Float64 zz = m.v1.z * x + m.v2.z * y + m.v3.z * z; x = xx; y = yy; z = zz; return *this; }
inline const Matrix64 Matrix32::ToLM() const { return Matrix64((Vector64)off, (Vector64)v1, (Vector64)v2, (Vector64)v3); }
inline const Matrix64 Matrix32::ToRM() const { return Matrix64((Vector64)off, (Vector64)v1, (Vector64)v2, (Vector64)v3); }
	#endif

#endif
