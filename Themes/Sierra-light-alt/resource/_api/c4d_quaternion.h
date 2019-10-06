/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __QUATERNION_H
#define __QUATERNION_H

#include "ge_math.h"

class Quaternion
{
public:
	Quaternion() : w(0.0), v(1.0, 0.0, 0.0) { }
	Quaternion(_DONTCONSTRUCT v) : v(DC) { }

	Float64	 w;											// angle
	Vector64 v;											// direction vector

	Matrix64 GetMatrix(void) const	// derive rotation matrix from quaternion
	{
		Matrix64 m(DC);
		m.off = Vector64(0, 0, 0);
		m.v1	= Vector64(1.0 - 2.0 * (v.y * v.y + v.z * v.z), 2.0 * (v.x * v.y - w * v.z), 2.0 * (v.x * v.z + w * v.y));
		m.v2	= Vector64(2.0 * (v.x * v.y + w * v.z), 1.0 - 2.0 * (v.x * v.x + v.z * v.z), 2.0 * (v.y * v.z - w * v.x));
		m.v3	= Vector64(2.0 * (v.x * v.z - w * v.y), 2.0 * (v.y * v.z + w * v.x), 1.0 - 2.0 * (v.x * v.x + v.y * v.y));
		return m;
	}

	void SetMatrix(const Matrix64& _m)
	{
		Matrix64 m = _m;

		m.v1 = !m.v1;
		m.v2 = !m.v2;
		m.v3 = !m.v3;

		SetMatrixNorm(m);
	}

	void SetMatrixNorm(const Matrix64& m)
	{
		Float64 trace = m.v1.x + m.v2.y + m.v3.z;

		if (trace > 0.0)
		{
			Float64 s = 0.5 / Sqrt(trace + 1.0);
			w = 0.25 / s;
			v.x = m.v2.z - m.v3.y;
			v.y = m.v3.x - m.v1.z;
			v.z = m.v1.y - m.v2.x;

			v *= s;
			v	 = -v;
		}
		else
		{
			if ((m.v1.x > m.v2.y) && (m.v1.x > m.v3.z))
			{
				Float64 s = 2.0 * Sqrt(1.0 + m.v1.x - m.v2.y - m.v3.z);
				v.x = 0.25 * s;
				Float64 s1 = 1.0 / s;
				v.y = (m.v2.x + m.v1.y) * s1;
				v.z = (m.v3.x + m.v1.z) * s1;
				w = (m.v3.y - m.v2.z) * s1;
			}
			else if (m.v2.y > m.v3.z)
			{
				Float64 s	 = 2.0 * Sqrt(1.0 + m.v2.y - m.v1.x - m.v3.z);
				Float64 s1 = 1.0 / s;
				v.x = (m.v2.x + m.v1.y) * s1;
				v.y = 0.25 * s;
				v.z = (m.v3.y + m.v2.z) * s1;
				w = -(m.v3.x - m.v1.z) * s1;
			}
			else
			{
				Float64 s	 = 2.0 * Sqrt(1.0 + m.v3.z - m.v1.x - m.v2.y);
				Float64 s1 = 1.0 / s;
				v.x = (m.v3.x + m.v1.z) * s1;
				v.y = (m.v3.y + m.v2.z) * s1;
				v.z = 0.25 * s;
				w = (m.v2.x - m.v1.y) * s1;
			}
		}
	}

	void SetHPB(const Vector64& hpb);

	void SetAxis(const Vector64& ax, const Float64 ww)
	{
		v = (!ax) * Sin(0.5 * ww);
		w = Cos(0.5 * ww);
	}
};


// linear interpolation
Quaternion QSlerp (const Quaternion& q1, const Quaternion& q2, Float64 alfa);	// linear interpolation between two quaternions

// cubic interpolation, q0 = i-1, q1 = i, q2 = i+1, q3 = i+2
Quaternion QSquad (const Quaternion& q0, const Quaternion& q1, const Quaternion& q2, const Quaternion& q3, Float64 alfa);

// real smooth quaternion blending
Quaternion QBlend(const Quaternion& q1, const Quaternion& q2, const Float64 r);
Quaternion QNorm  (const Quaternion& q);
Quaternion QMul   (const Quaternion& q1, const Quaternion& q2);
Quaternion QMul   (const Quaternion& q, Float64 s);
Quaternion QAdd   (const Quaternion& q1, const Quaternion& q2);
Quaternion QSub   (const Quaternion& q1, const Quaternion& q2);
Quaternion QInvert(const Quaternion& q);
Quaternion QDeriv (const Quaternion& q, const Vector64& w);

Quaternion QLogN(const Quaternion& q);
Quaternion QExpQ(const Quaternion& q);
Quaternion QSpline(const Quaternion& qn_m1, const Quaternion& qn, const Quaternion& qn_p1, const Quaternion& qn_p2, Float64 t);
Vector64 Matrix64ToHPB(const Matrix64& m);
Matrix64 LHPBToMatrix(const Vector64& w);

#endif
