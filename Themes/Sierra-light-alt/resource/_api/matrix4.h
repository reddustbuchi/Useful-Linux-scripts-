#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include "ge_math.h"
#include "vector4.h"

template <class TYPE> class _Matrix4
{
public:
	_Matrix4(_DONTCONSTRUCT v)
	{
	}

	_Matrix4()
	{
		_00 = 1.0f; _01 = 0.0f; _02 = 0.0f; _03 = 0.0f;
		_10 = 0.0f; _11 = 1.0f; _12 = 0.0f; _13 = 0.0f;
		_20 = 0.0f; _21 = 0.0f; _22 = 1.0f; _23 = 0.0f;
		_30 = 0.0f; _31 = 0.0f; _32 = 0.0f; _33 = 1.0f;
	}

	_Matrix4(TYPE m00, TYPE m01, TYPE m02, TYPE m03,
					 TYPE m10, TYPE m11, TYPE m12, TYPE m13,
					 TYPE m20, TYPE m21, TYPE m22, TYPE m23,
					 TYPE m30, TYPE m31, TYPE m32, TYPE m33)
	{
		_00 = m00; _01 = m01; _02 = m02; _03 = m03;
		_10 = m10; _11 = m11; _12 = m12; _13 = m13;
		_20 = m20; _21 = m21; _22 = m22; _23 = m23;
		_30 = m30; _31 = m31; _32 = m32; _33 = m33;
	}

	explicit _Matrix4(TYPE* p)
	{
		Int32 i;
		for (i = 0; i < 16; i++)
			m_prArray[i] = p[i];
	}

	_Matrix4(const _Matrix4& m)
	{
		Int32 i;
		for (i = 0; i < 16; i++)
			m_prArray[i] = m.m_prArray[i];
	}

	explicit _Matrix4(const Matrix32& m)
	{
		_00 = (TYPE)m.v1.x; _01 = (TYPE)m.v2.x; _02 = (TYPE)m.v3.x; _03 = (TYPE)m.off.x;
		_10 = (TYPE)m.v1.y; _11 = (TYPE)m.v2.y; _12 = (TYPE)m.v3.y; _13 = (TYPE)m.off.y;
		_20 = (TYPE)m.v1.z; _21 = (TYPE)m.v2.z; _22 = (TYPE)m.v3.z; _23 = (TYPE)m.off.z;
		_30 = (TYPE)0.0; _31 = (TYPE)0.0; _32 = (TYPE)0.0; _33 = (TYPE)1.0;
	}

	explicit _Matrix4(const Matrix64& m)
	{
		_00 = (TYPE)m.v1.x; _01 = (TYPE)m.v2.x; _02 = (TYPE)m.v3.x; _03 = (TYPE)m.off.x;
		_10 = (TYPE)m.v1.y; _11 = (TYPE)m.v2.y; _12 = (TYPE)m.v3.y; _13 = (TYPE)m.off.y;
		_20 = (TYPE)m.v1.z; _21 = (TYPE)m.v2.z; _22 = (TYPE)m.v3.z; _23 = (TYPE)m.off.z;
		_30 = (TYPE)0.0; _31 = (TYPE)0.0; _32 = (TYPE)0.0; _33 = (TYPE)1.0;
	}

	Matrix32 GetSMatrix()
	{
		Matrix32 m(DC);
		m.v1.x = (Float32)_00; m.v2.x = (Float32)_01; m.v3.x = (Float32)_02; m.off.x = (Float32)_03;
		m.v1.y = (Float32)_10; m.v2.y = (Float32)_11; m.v3.y = (Float32)_12; m.off.y = (Float32)_13;
		m.v1.z = (Float32)_20; m.v2.z = (Float32)_21; m.v3.z = (Float32)_22; m.off.z = (Float32)_23;
		return m;
	}

	Matrix64 GetLMatrix()
	{
		Matrix64 m(DC);
		m.v1.x = (Float64)_00; m.v2.x = (Float64)_01; m.v3.x = (Float64)_02; m.off.x = (Float64)_03;
		m.v1.y = (Float64)_10; m.v2.y = (Float64)_11; m.v3.y = (Float64)_12; m.off.y = (Float64)_13;
		m.v1.z = (Float64)_20; m.v2.z = (Float64)_21; m.v3.z = (Float64)_22; m.off.z = (Float64)_23;
		return m;
	}

	friend const _Matrix4 operator * (const _Matrix4& m1, const _Matrix4& m2)
	{
		Int32		 i, j, k;
		_Matrix4 r(DC);
		r.SetZero();

		for (i = 0; i < 4; i++)
		{
			for (k = 0; k < 4; k++)
			{
				for (j = 0; j < 4; j++)
				{
					r.m_prElements[i][j] += m1.m_prElements[i][k] * m2.m_prElements[k][j];
				}
			}
		}
		return r;
	}

	friend const Vector4d64 operator * (const _Matrix4& m, const Vector4d64& v)
	{
		Vector4d64 r(0.0f);
		Int32			 i, k;

		for (i = 0; i < 4; i++)
		{
			for (k = 0; k < 4; k++)
			{
				r.m_prElements[i] += m.m_prElements[i][k] * v.m_prElements[k];
			}
		}
		return r;
	}

	friend const Vector4d32 operator * (const _Matrix4& m, const Vector4d32& v)
	{
		Vector4d32 r(0.0f);
		Int32			 i, k;

		for (i = 0; i < 4; i++)
		{
			for (k = 0; k < 4; k++)
			{
				r.m_prElements[i] += m.m_prElements[i][k] * v.m_prElements[k];
			}
		}
		return r;
	}

	friend const Vector32 operator * (const _Matrix4& m, const Vector32& v)
	{
		Vector4d32 t(v);
		Vector4d32 r(0.0f);
		Int32			 i, k;

		for (i = 0; i < 4; i++)
		{
			for (k = 0; k < 4; k++)
			{
				r.m_prElements[i] += m.m_prElements[i][k] * t.m_prElements[k];
			}
		}
		r.MakeVector3();
		return Vector32(r.x, r.y, r.z);
	}

	friend const Vector64 operator * (const _Matrix4& m, const Vector64& v)
	{
		Vector4d64 t(v);
		Vector4d64 r(0.0);
		Int32			 i, k;

		for (i = 0; i < 4; i++)
		{
			for (k = 0; k < 4; k++)
			{
				r.m_prElements[i] += m.m_prElements[i][k] * t.m_prElements[k];
			}
		}
		r.MakeVector3();
		return Vector64(r.x, r.y, r.z);
	}

	_Matrix4 GetTranspose() const
	{
		_Matrix4 r(DC);
		Int32		 i, j;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
				r.m_prElements[i][j] = m_prElements[j][i];
		}
		return r;
	}

	friend const _Matrix4 operator ! (const _Matrix4& m)
	{
		_Matrix4 r(DC);

		r._00 =  Det(m._11, m._12, m._13, m._21, m._22, m._23, m._31, m._32, m._33);
		r._01 = -Det(m._01, m._02, m._03, m._21, m._22, m._23, m._31, m._32, m._33);
		r._02 =  Det(m._01, m._02, m._03, m._11, m._12, m._13, m._31, m._32, m._33);
		r._03 = -Det(m._01, m._02, m._03, m._11, m._12, m._13, m._21, m._22, m._23);
		r._10 = -Det(m._10, m._12, m._13, m._20, m._22, m._23, m._30, m._32, m._33);
		r._11 =  Det(m._00, m._02, m._03, m._20, m._22, m._23, m._30, m._32, m._33);
		r._12 = -Det(m._00, m._02, m._03, m._10, m._12, m._13, m._30, m._32, m._33);
		r._13 =  Det(m._00, m._02, m._03, m._10, m._12, m._13, m._20, m._22, m._23);
		r._20 =  Det(m._10, m._11, m._13, m._20, m._21, m._23, m._30, m._31, m._33);
		r._21 = -Det(m._00, m._01, m._03, m._20, m._21, m._23, m._30, m._31, m._33);
		r._22 =  Det(m._00, m._01, m._03, m._10, m._11, m._13, m._30, m._31, m._33);
		r._23 = -Det(m._00, m._01, m._03, m._10, m._11, m._13, m._20, m._21, m._23);
		r._30 = -Det(m._10, m._11, m._12, m._20, m._21, m._22, m._30, m._31, m._32);
		r._31 =  Det(m._00, m._01, m._02, m._20, m._21, m._22, m._30, m._31, m._32);
		r._32 = -Det(m._00, m._01, m._02, m._10, m._11, m._12, m._30, m._31, m._32);
		r._33 =  Det(m._00, m._01, m._02, m._10, m._11, m._12, m._20, m._21, m._22);
		TYPE det = m._00 * r._00 + m._10 * r._01 + m._20 * r._02 + m._30 * r._03;
		if (det == 0)
		{
			r = _Matrix4();
			return r;
		}
		det = 1.0f / det;
		r = det * r;
		return r;
	}

	friend const _Matrix4 operator * (const TYPE s, const _Matrix4& m)
	{
		_Matrix4 r(DC);
		Int32		 i;
		for (i = 0; i < 16; i++)
			r.m_prArray[i] = m.m_prArray[i] * s;
		return r;
	}

	friend Bool operator == (const _Matrix4& a, const _Matrix4& b)
	{
		for (Int32 l = 0; l < 16; l++)
		{
			if (a.m_prArray[l] != b.m_prArray[l])
				return false;
		}
		return true;
	}

	friend Bool operator != (const _Matrix4& a, const _Matrix4& b)
	{
		for (Int32 l = 0; l < 16; l++)
		{
			if (a.m_prArray[l] != b.m_prArray[l])
				return true;
		}
		return false;
	}

	void SetZero()
	{
		_00 = _01 = _02 = _03 = 0.0f;
		_10 = _11 = _12 = _13 = 0.0f;
		_20 = _21 = _22 = _23 = 0.0f;
		_30 = _31 = _32 = _33 = 0.0f;
	}

	void SetOffset(const Vector& v)
	{
		_03 = v.x;
		_13 = v.y;
		_23 = v.z;
	}

	void Scale(TYPE r)
	{
		_33 /= r;
	}

	void ScaleDirections(TYPE r)
	{
		_00 *= r; _01 *= r; _02 *= r;
		_10 *= r; _11 *= r; _12 *= r;
		_20 *= r; _21 *= r; _22 *= r;
	}

	Bool IsInvertable()
	{
		_Matrix4 r(DC);

		r._00 =  Det(_11, _12, _13, _21, _22, _23, _31, _32, _33);
		r._01 = -Det(_01, _02, _03, _21, _22, _23, _31, _32, _33);
		r._02 =  Det(_01, _02, _03, _11, _12, _13, _31, _32, _33);
		r._03 = -Det(_01, _02, _03, _11, _12, _13, _21, _22, _23);
		r._10 = -Det(_10, _12, _13, _20, _22, _23, _30, _32, _33);
		r._11 =  Det(_00, _02, _03, _20, _22, _23, _30, _32, _33);
		r._12 = -Det(_00, _02, _03, _10, _12, _13, _30, _32, _33);
		r._13 =  Det(_00, _02, _03, _10, _12, _13, _20, _22, _23);
		r._20 =  Det(_10, _11, _13, _20, _21, _23, _30, _31, _33);
		r._21 = -Det(_00, _01, _03, _20, _21, _23, _30, _31, _33);
		r._22 =  Det(_00, _01, _03, _10, _11, _13, _30, _31, _33);
		r._23 = -Det(_00, _01, _03, _10, _11, _13, _20, _21, _23);
		r._30 = -Det(_10, _11, _12, _20, _21, _22, _30, _31, _32);
		r._31 =  Det(_00, _01, _02, _20, _21, _22, _30, _31, _32);
		r._32 = -Det(_00, _01, _02, _10, _11, _12, _30, _31, _32);
		r._33 =  Det(_00, _01, _02, _10, _11, _12, _20, _21, _22);
		TYPE det = _00 * r._00 + _10 * r._01 + _20 * r._02 + _30 * r._03;
		if (det == 0.0)
		{
			return false;
		}
		return true;
	}

	union
	{
		struct { TYPE _00, _01, _02, _03,
									_10, _11, _12, _13,
									_20, _21, _22, _23,
									_30, _31, _32, _33; };
		TYPE m_prElements[4][4];
		TYPE m_prArray[16];
	};

private:
	static TYPE Det(TYPE a1, TYPE a2, TYPE a3, TYPE b1, TYPE b2, TYPE b3, TYPE c1, TYPE c2, TYPE c3)
	{
		return a1 * (b2 * c3 - b3 * c2) - b1 * (a2 * c3 - a3 * c2) + c1 * (a2 * b3 - a3 * b2);
	}
};

typedef _Matrix4<Float32> Matrix4d32;
typedef _Matrix4<Float64> Matrix4d64;

#ifdef __FLOAT_32_BIT
	#define Matrix4d Matrix4d32
	#define RMtoSM4(x) (x)
	#define SMtoRM4(x) (x)
	inline Matrix4d64 RMtoLM4(const Matrix4d& m)
	{
		return Matrix4d64((Float64)m._00, (Float64)m._01, (Float64)m._02, (Float64)m._03,
										(Float64)m._10, (Float64)m._11, (Float64)m._12, (Float64)m._13,
										(Float64)m._20, (Float64)m._21, (Float64)m._22, (Float64)m._23,
										(Float64)m._30, (Float64)m._31, (Float64)m._32, (Float64)m._33);
	}
#else
	#define Matrix4d Matrix4d64
	inline Matrix4d32 RMtoSM4(const Matrix4d& m)
	{
		return Matrix4d32((Float32)m._00, (Float32)m._01, (Float32)m._02, (Float32)m._03,
										(Float32)m._10, (Float32)m._11, (Float32)m._12, (Float32)m._13,
										(Float32)m._20, (Float32)m._21, (Float32)m._22, (Float32)m._23,
										(Float32)m._30, (Float32)m._31, (Float32)m._32, (Float32)m._33);
	}
	inline Matrix4d SMtoRM4(const Matrix4d32& m)
	{
		return Matrix4d((Float)m._00, (Float)m._01, (Float)m._02, (Float)m._03,
										(Float)m._10, (Float)m._11, (Float)m._12, (Float)m._13,
										(Float)m._20, (Float)m._21, (Float)m._22, (Float)m._23,
										(Float)m._30, (Float)m._31, (Float)m._32, (Float)m._33);
	}
	#define RMtoLM4(m) (m)
#endif

#endif	// _MATRIX4_H_
