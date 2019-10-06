#include "ge_math.h"
#include "c4d_tools.h"
#include "c4d_file.h"
#include "c4d_basecontainer.h"
#include "c4d_general.h"

#ifndef __API_INTERN__
	#include "c4d_basedocument.h"
#endif

Vector32 s_empty;
Vector64 l_empty;

Vector32::Vector32(const Vector64& v) : x((Float32)v.x), y((Float32)v.y), z((Float32)v.z) { }

Matrix32::Matrix32(const Matrix64& m) : off((Vector32)m.off), v1((Vector32)m.v1), v2((Vector32)m.v2), v3((Vector32)m.v3) { }

Matrix MatrixMove(const Vector& t)
{
	Matrix erg;
	erg.off = t;
	return erg;
}

Matrix MatrixScale(const Vector& s)
{
	Matrix erg;

	erg.v1.x = s.x;
	erg.v2.y = s.y;
	erg.v3.z = s.z;
	return erg;
}

Matrix MatrixRotX(Float w)
{
	Matrix erg;
	Float	 cs = Cos(w), sn = Sin(w);

	erg.v3.z = cs;
	erg.v2.z = -sn;
	erg.v3.y = sn;
	erg.v2.y = cs;
	return erg;
}

Matrix MatrixRotY(Float w)
{
	Matrix erg;
	Float	 cs = Cos(w), sn = Sin(w);

	erg.v1.x = cs;
	erg.v3.x = -sn;
	erg.v1.z = sn;
	erg.v3.z = cs;
	return erg;
}

Matrix MatrixRotZ(Float w)
{
	Matrix erg;
	Float	 cs = Cos(w), sn = Sin(w);

	erg.v1.x = cs;
	erg.v2.x = sn;
	erg.v1.y = -sn;
	erg.v2.y = cs;
	return erg;
}

static Float GetNear(Float alt, Float* neu)
{
	Float diff = (*neu - alt) / (Float) PI2;
	diff = (diff - Floor(diff)) * (Float) PI2;
	*neu = diff + alt;

	if (diff >= (Float) PI)
	{
		diff -= (Float) PI2;
		*neu -= (Float) PI2;
	}

	return diff;
}

Vector GetOptimalAngle(const Vector& orot, const Vector& nrot, ROTATIONORDER order)
{
	Vector d1, d2, n2, n1 = nrot;

	switch (order)
	{
		case ROTATIONORDER_XYZGLOBAL:
		case ROTATIONORDER_ZYXGLOBAL:					n2 = Vector((Float) PI + nrot.x, (Float) PI - nrot.y, (Float) PI + nrot.z);	break;
		case ROTATIONORDER_YZXGLOBAL:
		case ROTATIONORDER_XZYGLOBAL:					n2 = Vector((Float) PI + nrot.x, (Float) PI + nrot.y, (Float) PI - nrot.z);	break;

		case ROTATIONORDER_YXZGLOBAL:
		case ROTATIONORDER_ZXYGLOBAL:					n2 = Vector((Float) PI - nrot.x, (Float) PI + nrot.y, (Float) PI + nrot.z);	break;

		default:
		case ROTATIONORDER_HPB:								n2 = Vector((Float) PI + nrot.x, (Float) PI - nrot.y, (Float) PI + nrot.z);	break;
	}

	d1.x = GetNear(orot.x, &n1.x);
	d1.y = GetNear(orot.y, &n1.y);
	d1.z = GetNear(orot.z, &n1.z);

	d2.x = GetNear(orot.x, &n2.x);
	d2.y = GetNear(orot.y, &n2.y);
	d2.z = GetNear(orot.z, &n2.z);

	if (Abs(d2.x) + Abs(d2.y) + Abs(d2.z) < Abs(d1.x) + Abs(d1.y) + Abs(d1.z))
		return n2;
	else
		return n1;
}

// Winkel eines Punkts bestimmen
Vector VectorToHPB(const Vector& p)
{
	Float	 l;
	Vector rot;

	l = Sqrt(p.x * p.x + p.z * p.z);

	if (l < 0.00001)
	{
		if (p.y > 0.0)
			rot = Vector(0.0, (Float) PI05, 0.0);
		else
			rot = Vector(0.0, -(Float) PI05, 0.0);
	}
	else
	{
		if (p.z > 0.0)
			rot.x = -ASin(p.x / l);
		else
			rot.x = (Float) PI + ASin(p.x / l);
		rot.y = ATan(p.y / l);
		rot.z = 0.0;
	}
	return rot;
}

Vector MatrixToHPB(const Matrix& m, ROTATIONORDER rot_order)
{
	Vector64 rot, v1 = !((Vector64)m.v1), v2 = !((Vector64)m.v2), v3 = !((Vector64)m.v3);	// v1 has to be normalized
	Float64	 tsin = 0.0, tcos = 0.0;

	switch (rot_order)
	{
		case ROTATIONORDER_YXZGLOBAL:
		{
			rot.x = ASin(-v2.z);	//h
			Float64 a = -Cos(rot.x);
			if (Abs(a) > 0.005)
			{
				tsin	= v1.z;								// / a;
				tcos	= v3.z;								// / a;
				rot.y = atan2(tsin, tcos);	//p
				tsin	= v2.x;								// / a;
				tcos	= v2.y;								// / a;
				rot.z = atan2(tsin, tcos);	//b
			}
			else
			{
				rot.z = (Float) 0.0;
				tsin	= v1.y;	//V
				tcos	= v1.x;	//W
				rot.y = atan2(tsin, tcos);
				if (v2.z > 0)
					rot.y = PI2 - rot.y;
			}
			break;
		}

		case ROTATIONORDER_YZXGLOBAL:
		{
			rot.z = ASin(v2.x);
			Float64 e = Cos(rot.z);
			if (Abs(e) > 0.005)
			{
				tsin	= -v2.z;	// / e;
				tcos	= v2.y;		// / e;
				rot.x = atan2(tsin, tcos);
				tsin	= -v3.x;	// / e;
				tcos	= v1.x;		// / e;
				rot.y = atan2(tsin, tcos);
			}
			else
			{
				rot.x = (Float) 0.0;
				tsin	= v1.z;		//V
				tcos	= -v1.y;	//W
				rot.y = atan2(tsin, tcos);
				if (v2.x < 0)
					rot.y = PI - rot.y;
			}
			break;
		}

		case ROTATIONORDER_ZYXGLOBAL:
		{
			rot.y = ASin(-v3.x);
			Float64 c = Cos(rot.y);
			if (Abs(c) > 0.005)
			{
				tsin	= v2.x;	// / c; //f
				tcos	= v1.x;	// / c; //e
				rot.z = atan2(tsin, tcos);
				tsin	= v3.y;	// / c; //b
				tcos	= v3.z;	// / c; //a
				rot.x = atan2(tsin, tcos);
			}
			else
			{
				rot.z = (Float) 0.0;
				tsin	= -v1.y;	//V
				tcos	= v2.y;		//W
				rot.x = atan2(tsin, tcos);
				if (v3.x < 0)
					rot.x = -rot.x;
			}
			break;
		}

		case ROTATIONORDER_XZYGLOBAL:
		{
			rot.z = ASin(-v1.y);
			Float64 e = -Cos(rot.z);
			if (Abs(e) > 0.005)
			{
				tsin	= v1.z;	// / e; //d
				tcos	= v1.x;	// / e; //c
				rot.y = atan2(tsin, tcos);
				tsin	= v3.y;	// / e; //b
				tcos	= v2.y;	// / e; //a
				rot.x = atan2(tsin, tcos);
			}
			else
			{
				rot.y = (Float) 0.0;
				tsin	= v3.x;	//V
				tcos	= v2.x;	//W
				rot.x = atan2(tsin, tcos);
				if (v1.y > 0)
					rot.x += PI;
			}
			break;
		}

		case ROTATIONORDER_XYZGLOBAL:
		{
			rot.y = ASin(v1.z);
			Float64 c = Cos(rot.y);
			if (Abs(c) > 0.005)
			{
				tsin	= -v1.y;	// / c; //f
				tcos	= v1.x;		// / c; //e
				rot.z = atan2(tsin, tcos);
				tsin	= -v2.z;	// / c; //b
				tcos	= v3.z;		// / c; //a
				rot.x = atan2(tsin, tcos);
			}
			else
			{
				rot.z = (Float) 0.0;
				tsin	= v2.x;		//V
				tcos	= -v3.x;	//W
				rot.x = atan2(tsin, tcos);
				if (v1.z < 0.0)
					rot.x -= PI;
			}
			break;
		}

		case ROTATIONORDER_ZXYGLOBAL:
		{
			rot.x = ASin(v3.y);
			Float64 a = Cos(rot.x);
			if (Abs(a) > 0.005)
			{
				tsin	= -v3.x;	// / a; //d
				tcos	= v3.z;		// / a; //c
				rot.y = atan2(tsin, tcos);
				tsin	= -v1.y;	// / a; //f
				tcos	= v2.y;		// / a; //e
				rot.z = atan2(tsin, tcos);
			}
			else
			{
				rot.z = (Float) 0.0;
				tsin	= v2.x;	//V
				tcos	= v1.x;	//W
				rot.y = atan2(tsin, tcos);
				if (v3.y < 0.0)
					rot.y = -rot.y;
			}
			break;
		}

		case ROTATIONORDER_HPB:
		default:
		{
			Float64 l = Sqrt(v3.x * v3.x + v3.z * v3.z);

			if (l < 0.00001)
			{
				rot.x = 0.0;
				rot.z = ACos(Dot(Vector64(1.0, 0.0, 0.0), v1));

				if (v3.y > 0.0)
				{
					rot.y = PI05;
					if (v1.z < 0.0)
						rot.z = PI2 - rot.z;
				}
				else
				{
					rot.y = -PI05;
					if (v1.z > 0.0)
						rot.z = PI2 - rot.z;
				}
			}
			else
			{
				if (v3.z > 0.0)
					rot.x = -ASin(v3.x / l);
				else
					rot.x = PI + ASin(v3.x / l);

				if (rot.x < 0.0)
					rot.x += PI2;
				rot.y = ATan((Float64)v3.y / l);
				rot.z = ACos(Dot(Vector64(Cos(rot.x), 0.0, Sin(rot.x)), v1));

				if (v1.y > 0.0)
					rot.z = PI2 - rot.z;
			}
			break;
		}
	}

	return (Vector)rot;
}

// angles in Rad-/Euler system
Matrix HPBToMatrix(const Vector& w, ROTATIONORDER rot_order)
{
	if (w == 0.0)
		return Matrix();	// speedup

	Float a, b, c, d, e, f, cosksinn, sinksinn;

	if (rot_order == ROTATIONORDER_DEFAULT)
	{
		SinCos(w.x, d, c);	//y = h
		SinCos(w.y, b, a);	//x = p
	}
	else
	{
		SinCos(w.x, b, a);	//y = y
		SinCos(w.y, d, c);	//x = x
	}
	SinCos(w.z, f, e);		//z = b

	switch (rot_order)
	{
		case ROTATIONORDER_YXZGLOBAL:
		{
			sinksinn = d * b;
			cosksinn = c * b;

			return Matrix(Vector(0.0),
							 Vector(c * e + sinksinn * f, -c * f + sinksinn * e, d * a),
							 Vector(a * f, a * e, -b),
							 Vector(-d * e + cosksinn * f, d * f + cosksinn * e, c * a));
		} break;
		case ROTATIONORDER_YZXGLOBAL:
		{
			sinksinn = c * f;
			cosksinn = d * f;

			return Matrix(Vector(0.0),
							 Vector(c * e, -sinksinn * a + d * b, sinksinn * b + d * a),
							 Vector(f, e * a, -e * b),
							 Vector(-d * e, cosksinn * a + c * b, -cosksinn * b + c * a));
		} break;
		case ROTATIONORDER_ZYXGLOBAL:
		{
			sinksinn = e * d;
			cosksinn = f * d;

			return Matrix(Vector(0.0),
							 Vector(e * c, -f * a + sinksinn * b, f * b + sinksinn * a),
							 Vector(f * c, e * a + cosksinn * b, -e * b + cosksinn * a),
							 Vector(-d, c * b, c * a));
		} break;
		case ROTATIONORDER_XZYGLOBAL:
		{
			sinksinn = a * f;
			cosksinn = b * f;

			return Matrix(Vector(0.0),
							 Vector(e * c, -f, e * d),
							 Vector(sinksinn * c + b * d, a * e, sinksinn * d - b * c),
							 Vector(cosksinn * c - a * d, b * e, cosksinn * d + a * c));
		} break;
		case ROTATIONORDER_XYZGLOBAL:
		{
			sinksinn = b * d;
			cosksinn = a * d;

			return Matrix(Vector(0.0),
							 Vector(c * e, -c * f, d),
							 Vector(sinksinn * e + a * f, -sinksinn * f + a * e, -b * c),
							 Vector(-cosksinn * e + b * f, cosksinn * f + b * e, a * c));
		} break;

		default:
			// make the compiler happy
			break;
	}

	// ROTATIONORDER_DEFAULT / ROTATIONORDER_HPB / ROTATIONORDER_YXZLOCAL / ROTATIONORDER_ZXYGLOBAL
	cosksinn = e * b;
	sinksinn = f * b;

	return Matrix(Vector(0.0),
					 Vector(e * c - sinksinn * d, -f * a, e * d + sinksinn * c),
					 Vector(f * c + cosksinn * d, e * a, f * d - cosksinn * c),
					 Vector(-a * d, b, a * c));
}

Matrix RebuildMatrix(const Matrix& mg)
{
	Matrix m = mg;

	Bool	collapsed[3] = { m.v1 == 0.0, m.v2 == 0.0, m.v3 == 0.0 };
	Int32 ccnt = collapsed[0] + collapsed[1] + collapsed[2], i = 0;

	switch (ccnt)
	{
		default:
		case 0: return m; break;
		case 3: m = Matrix(); break;
		case 2:
		{
			for (i = 0; i < 3; i++)
			{
				if (!collapsed[i])
				{
					m = RotAxisToMatrix(m[i + 1], 0.0);
					break;
				}
			}
		} break;
		case 1:
		{
			m.Normalize();
			if (collapsed[0])
			{
				m.v1 = Cross(m.v3, m.v2);
				if (m.v1 == 0.0)
					m.v1.x = 1.0;
			}
			if (collapsed[1])
			{
				m.v2 = Cross(m.v3, m.v1);
				if (m.v2 == 0.0)
					m.v2.y = 1.0;
			}
			if (collapsed[2])
			{
				m.v3 = Cross(m.v1, m.v2);
				if (m.v3 == 0.0)
					m.v3.z = 1.0;
			}
			m = m.GetTensorMatrix();
		} break;
	}

	for (i = 0; i < 3; i++)
	{
		if (!collapsed[i])
			m[i + 1] *= Len(mg[i + 1]);
	}

	m.off = mg.off;

	return m;
}


void MatrixToRotAxis(const Matrix& mm, Vector* v, Float* w)
{
	Matrix m = mm;
	// MatrixVectoren MUESSEN normiert sein!!!
	m.v1 = !m.v1;
	m.v2 = !m.v2;
	m.v3 = !m.v3;

	// Winkel berechnen
	*w = ACos((m.v1.x + m.v2.y + m.v3.z - (Float) 1.0) / (Float) 2.0);

	// Achse berechnen
	v->x = m.v2.z - m.v3.y;
	v->y = m.v3.x - m.v1.z;
	v->z = m.v1.y - m.v2.x;
	*v = !(*v);

	if (*v == 0.0)
	{
		*v = Vector(0.0, 1.0, 0.0);
		*w = 0.0;
	}
}

Matrix RotAxisToMatrix(const Vector& v, Float w)
{
	Matrix m;

	if ((v.x == 0.0 && v.y == 0.0 && v.z == 0.0) || w == 0.0)
		return m;

	//	// zuerst mal den Vector normieren ...
	//	m.v2 = !v;
	//
	//	// jetzt ein rechtes KS basteln
	//	m.v1 = m.v2%Vector(0.0,0.0,1.0);
	//
	//	if (Len(m.v1)>MIN_EPSILON)
	//	{
	//		m.v3 = m.v1%m.v2;
	//	}
	//	else
	//	{
	//		m.v3 = Vector(1.0,0.0,0.0)%m.v2;
	//		m.v1 = m.v2%m.v3;
	//	}
	//
	//	// Rotationsmatrix im Pleft- und Rechtssystem um Y ist gleich
	//	m = (m*MatrixRotY(w)) * !m;

	// faster version:
	Float whalf = 0.5 * w;
	Float hsin	= Sin(whalf);
	Float hcos	= Cos(whalf);

	Vector vn = !v * hsin;

	Float fTx	 = 2.0 * vn.x;
	Float fTy	 = 2.0 * vn.y;
	Float fTz	 = 2.0 * vn.z;
	Float fTwx = fTx * hcos;
	Float fTwy = fTy * hcos;
	Float fTwz = fTz * hcos;
	Float fTxx = fTx * vn.x;
	Float fTxy = fTy * vn.x;
	Float fTxz = fTz * vn.x;
	Float fTyy = fTy * vn.y;
	Float fTyz = fTz * vn.y;
	Float fTzz = fTz * vn.z;

	m.v1 = Vector(1.0 - (fTyy + fTzz), fTxy - fTwz, fTxz + fTwy);
	m.v2 = Vector(fTxy + fTwz, 1.0 - (fTxx + fTzz), fTyz - fTwx);
	m.v3 = Vector(fTxz - fTwy, fTyz + fTwx, 1.0 - (fTxx + fTyy));

	return m;
}

Random::Random(void)
{
	Init(100);
}

void Random::Init(UInt32 s)
{
	iset = 0;
	seed = s;
}

Float Random::Get01(void)
{
	const Float teiler = Float(2147483648.0 + 1.0);	// +1.0, falls evtl. Ungenauigkeiten auftreten

	seed = ((seed + 1) * 69069) & 0x7FFFFFFF;
	return Float(seed) / teiler;
}

Float Random::Get11(void)
{
	return Get01() * (Float) 2.0 - (Float) 1.0;
}

Float Random::GetG01(void)
{
	Float fac, rsq, v1, v2;

	if (iset == 0)
	{
		do
		{
			v1	= Get11();
			v2	= Get11();
			rsq = v1 * v1 + v2 * v2;
		}	while (rsq >= 1.0 || rsq == 0.0);

		fac	 = Sqrt((Float) - 2.0 * Ln(rsq) / rsq);
		gset = v1 * fac;
		iset = 1;
		return v2 * fac * (Float) 0.09 + (Float) 0.5;
	}
	else
	{
		iset = 0;
		return gset * (Float) 0.09 + (Float) 0.5;
	}
}

Float Random::GetG11(void)
{
	Float fac, rsq, v1, v2;

	if (iset == 0)
	{
		do
		{
			v1	= Get11();
			v2	= Get11();
			rsq = v1 * v1 + v2 * v2;
		}	while (rsq >= 1.0 || rsq == 0.0);

		fac	 = Sqrt((Float) - 2.0 * Ln(rsq) / rsq);
		gset = v1 * fac;
		iset = 1;
		return v2 * fac * (Float) 0.18;
	}
	else
	{
		iset = 0;
		return gset * (Float) 0.18;
	}
}

Vector64 ReflectRay(const Vector64& v, const Vector64& n)
{
	return v - n * (2.0 * Dot(n, v));
}

Vector RGBToHSV(const Vector& col)
{
	Float r, g, b, h, s, v, delta, max, min;

	r = col.x;
	g = col.y;
	b = col.z;

	max = r;
	if (g > max)
		max = g;
	if (b > max)
		max = b;
	min = r;
	if (g < min)
		min = g;
	if (b < min)
		min = b;

	v = max;
	if (max > 0.0)
	{
		s = (Float) 1.0 - min / max;

		if (s < MIN_EPSILON)
		{
			return Vector(0.0, 0.0, min);
		}
	}
	else
	{
		return Vector(0.0);
	}

	delta = max - min;
	if (r == max)
		h = (g - b) / delta;
	else if (g == max)
		h = (Float) 2.0 + (b - r) / delta;
	else
		h = (Float) 4.0 + (r - g) / delta;

	h /= 6.0;
	if (h < 0.0)
		h += 1.0;
	return Vector(h, s, v);
}

Vector HSVToRGB(const Vector& col)
{
	Float r = 0.0, g = 0.0, b = 0.0, h, s, v, f, p, q, t, i;
	Int32 j;

	h = col.x;
	s = col.y;
	v = col.z;

	if (s < MIN_EPSILON)
	{
		r = g = b = v;
	}
	else
	{
		if (h == 1.0)
			h = 0.0;

		h *= (Float) 6.0;
		i	 = Floor(h);
		f	 = h - i;
		p	 = v * ((Float) 1.0 - s);
		q	 = v * ((Float) 1.0 - s * f);
		t	 = v * ((Float) 1.0 - s * ((Float) 1.0 - f));
		j	 = (Int32)i;
		switch (j)
		{
			default:
			case 0: r = v; g = t; b = p; break;
			case 1: r = q; g = v; b = p; break;
			case 2: r = p; g = v; b = t; break;
			case 3: r = p; g = q; b = v; break;
			case 4: r = t; g = p; b = v; break;
			case 5: r = v; g = p; b = q; break;
		}
	}
	return Vector(r, g, b);
}

Vector RGBToHSL(const Vector& col)
{
	Float r, g, b, v, m, vm, r2, g2, b2, h, s, l;

	r = col.x;
	g = col.y;
	b = col.z;

	v = FMax(r, g);
	v = FMax(v, b);
	m = FMin(r, g);
	m = FMin(m, b);

	l = (m + v) * (Float) 0.5;

	if (l <= (Float) 0.0)
	{
		s = (Float) 0.0;
		h = (Float) 0.0;
	}
	else
	{
		s = vm = v - m;
		if (s <= (Float) 0.0)
		{
			h = s = (Float) 0.0;
			return Vector((Float) 0.0);
		}

		Float div = (l <= (Float) 0.5) ? (v + m) : ((Float) 2.0 - v - m);
		if (div != (Float) 0.0)
			s /= div;

		if (vm != (Float) 0.0)
		{
			r2 = (v - r) / vm;
			g2 = (v - g) / vm;
			b2 = (v - b) / vm;
		}
		else
		{
			r2 = (Float) 0.0;
			g2 = (Float) 0.0;
			b2 = (Float) 0.0;
		}

		if (r == v)
			h = (g == m ? (Float) 5.0 + b2 : (Float) 1.0 - g2);
		else if (g == v)
			h = (b == m ? (Float) 1.0 + r2 : (Float) 3.0 - b2);
		else
			h = (r == m ? (Float) 3.0 + g2 : (Float) 5.0 - r2);

		h /= (Float) 6.0;	// Convert hue to 0.0 ... 1.0
	}

	return Vector(h, s, l);
}

inline Float HSLtoRGB_value(Float nl, Float n2, Float hue)
{
	if (hue > (Float) 360.0)
		hue -= (Float) 360.0;
	else if (hue < (Float) 0.0)
		hue += (Float) 360.0;
	if (hue < (Float) 60.0)
		return nl + (n2 - nl) * hue / (Float) 60.0;
	if (hue < (Float) 180.0)
		return n2;
	if (hue < (Float) 240.0)
		return nl + (n2 - nl) * ((Float) 240 - hue) / (Float) 60.0;
	return nl;
}

Vector HSLtoRGB(const Vector& col)
{
	Float h, s, l, m1, m2, r, g, b;

	h = col.x * (Float) 360.0;
	s = col.y;
	l = col.z;

	if (l <= (Float) 0.5)
		m2 = l * ((Float) 1.0 + s);
	else
		m2 = l + s - l * s;
	m1 = (Float) 2.0 * l - m2;
	if (s == (Float) 0.0 || h == (Float) - 1.0)
	{
		r = g = b = l;
	}
	else
	{
		r = HSLtoRGB_value(m1, m2, h + (Float) 120.0);
		g = HSLtoRGB_value(m1, m2, h);
		b = HSLtoRGB_value(m1, m2, h - (Float) 120.0);
	}

	return Vector(r, g, b);
}

Vector PointLineDistance(const Vector& p0, const Vector& v, const Vector& p)
{
	Float vsquare = Dot(v, v);
	if (vsquare == 0.0)
		return Vector(0.0);
	return p - (p0 + Dot(p - p0, v) / vsquare * v);
}

#ifndef __API_INTERN__

VolumeData* VolumeData::Alloc(void)
{
	return C4DOS.Sh->AllocVolumeData();
}

void VolumeData::Free(VolumeData*& vd)
{
	C4DOS.Sh->FreeVolumeData(vd);
	vd = nullptr;
}

TexData* TexData::Alloc(void)
{
	return C4DOS.Sh->AllocTexData();
}

void TexData::Free(TexData*& vd)
{
	C4DOS.Sh->FreeTexData(vd);
	vd = nullptr;
}

void TexData::Init(void)
{
	C4DOS.Sh->InitTexData(this);
}

Int32 VPBuffer::GetInfo(VPGETINFO type)
{
	return C4DOS.Sh->VPGetInfo(this, type);
}

Bool VPBuffer::GetLine(Int32 x, Int32 y, Int32 cnt, void* data, Int32 bitdepth, Bool dithering)
{
	return C4DOS.Sh->VPGetLine(this, x, y, cnt, data, bitdepth, dithering);
}

Bool VPBuffer::SetLine(Int32 x, Int32 y, Int32 cnt, void* data, Int32 bitdepth, Bool dithering)
{
	return C4DOS.Sh->VPSetLine(this, x, y, cnt, data, bitdepth, dithering);
}

Bool Render::AllocateBuffer(Int32 id, Int32 subid, Int32 bitdepth, Bool visible)
{
	return C4DOS.Sh->VPAllocateBuffer(this, id, subid, bitdepth, visible);
}

Int32 Render::AllocateBufferFX(Int32 id, const String& name, Int32 bitdepth, Bool visible)
{
	return C4DOS.Sh->VPAllocateBufferFX(this, id, name, bitdepth, visible);
}

void Render::IccConvert(void* data, Int32 xcnt, Int32 components, Bool inverse)
{
	C4DOS.Sh->VPIccConvert(this, data, xcnt, components, inverse);
}

VPBuffer* Render::GetBuffer(Int32 id, Int32 subid)
{
	return C4DOS.Sh->VPGetBuffer(this, id, subid);
}

BaseContainer Render::GetRenderData(void)
{
	BaseContainer bc;
	C4DOS.Sh->VPGetRenderData(this, &bc);
	return bc;
}

void Render::SetRenderData(const BaseContainer& ct)
{
	C4DOS.Sh->VPSetRenderData(this, &ct);
}

VolumeData* Render::GetInitialVolumeData(Int32 cpu)
{
	return C4DOS.Sh->VPGetInitialVolumeData(this, cpu);
}

void* Render::GetPrivateData(void)
{
	return C4DOS.Sh->VPGetPrivateData(this);
}

Bool Render::SetRenderProperty(Int32 id, const GeData& dat)
{
	return C4DOS.Sh->SetRenderProperty(this, id, dat);
}

RayObject* AllocRayObject(Int32 tex_cnt)
{
	return C4DOS.Sh->AllocRayObject(tex_cnt, nullptr);
}

void FreeRayObject(RayObject*& op)
{
	C4DOS.Sh->FreeRayObject(op);
	op = nullptr;
}

RayLight* AllocRayLight(BaseDocument* doc, BaseObject* op)
{
	return C4DOS.Sh->AllocRayLight(doc, op);
}

void FreeRayLight(RayLight*& lgt)
{
	C4DOS.Sh->FreeRayLight(lgt);
	lgt = nullptr;
}

Bool IlluminateRayLight(RayLight* rl, Vector* color, Vector64* light_vector, const Vector64& p, const Vector64& n)
{
	return C4DOS.Sh->Illuminate(nullptr, rl, color, light_vector, p, n, n, n, Vector64(0.0), ILLUMINATEFLAGS_0, RayHitID(), RAYBIT_0, false, nullptr);
}

void CalcRestrictionInc(ObjectRestriction* lr, RayObject* op, Bool& nodif, Bool& nospec)
{
	if (!op || !op->link || op->restriction_index >= lr->object_cnt)
		return;
	if (lr->object[op->restriction_index] & LIGHTRESTRICTION_NODIFFUSE)
		nodif = true;
	if (lr->object[op->restriction_index] & LIGHTRESTRICTION_NOSPECULAR)
		nospec = true;
}

BAKE_TEX_ERR BakeTexture(BaseDocument* doc, const BaseContainer& data, BaseBitmap* bmp, BaseThread* th, BakeProgressHook* hook, BakeProgressInfo* info)
{
	return C4DOS.Sh->BakeTexture(doc, data, bmp, th, hook, info);
}

BaseDocument* InitBakeTexture(BaseDocument* doc, TextureTag* textag, UVWTag* texuvw, UVWTag* destuvw, const BaseContainer& bc, BAKE_TEX_ERR* err, BaseThread* th)
{
	return C4DOS.Sh->InitBakeTexture(doc, textag, texuvw, destuvw, bc, err, th);
}

BaseDocument* InitBakeTexture(BaseDocument* doc, TextureTag** textags, UVWTag** texuvws, UVWTag** destuvws, Int32 cnt, const BaseContainer& bc, BAKE_TEX_ERR* err, BaseThread* th)
{
	return C4DOS.Sh->InitBakeTextureA(doc, textags, texuvws, destuvws, cnt, bc, err, th);
}

GeCipher256::GeCipher256()
{
	hnd = nullptr;
}

GeCipher256::~GeCipher256()
{
	if (hnd)
		Close();
}

Bool GeCipher256::Open(const void* key, Int32 klength, Bool stream)
{
	if (hnd)
		Close();
	hnd = C4DOS.Ge->GeCipher256Open((const UChar*)key, klength, stream);
	return hnd != nullptr;
}

void GeCipher256::Close()
{
	if (hnd)
	{
		C4DOS.Ge->GeCipher256Close(hnd);
		hnd = nullptr;
	}
}

void GeCipher256::Encrypt(void* mem, Int32 bytes)
{
	if (hnd)
		C4DOS.Ge->GeCipher256Encrypt(hnd, (UChar*)mem, bytes);
}

void GeCipher256::Decrypt(void* mem, Int32 bytes)
{
	if (hnd)
		C4DOS.Ge->GeCipher256Decrypt(hnd, (UChar*)mem, bytes);
}

Int32 InitRenderStruct::GetThreadCount() const
{
	return vd ? vd->GetCPUCount() : 1;
}

void InitRenderStruct::Init(BaseDocument* t_doc)
{
	version = GetC4DVersion();
	doc = t_doc;
	errorlist = nullptr;
	matname = nullptr;
	vd = nullptr;
	thread = nullptr;
	flags	 = INITRENDERFLAG_TEXTURES;
	linear_workflow = false;
	document_colorprofile = DOCUMENT_COLORPROFILE_SRGB;

	if (t_doc)
	{
		docpath = t_doc->GetDocumentPath();
		fps	 = t_doc->GetFps();
		time = t_doc->GetTime();

		BaseContainer* bc = t_doc->GetDataInstance();
		if (bc)
		{
			linear_workflow = bc->GetBool(DOCUMENT_LINEARWORKFLOW);
			document_colorprofile = bc->GetInt32(DOCUMENT_COLORPROFILE);
		}
	}
	else
	{
		fps = 30;
	}
}
#endif
