/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DBASETIME_H
#define __C4DBASETIME_H

#include "ge_math.h"

class BaseTime
{
	friend class BaseFile;
	friend class AESFile;

private:
	Float numerator;
	Float denominator;
	void Reduce(void);

public:
	BaseTime(void) { numerator = 0; denominator = 1; }

	explicit BaseTime(Float r);
	explicit BaseTime(Float z, Float n);

	Float Get(void) const
	{
		if (denominator == 0.0)
			return 0.0;
		return numerator / denominator;
	}

	Float GetNumerator(void) const { return numerator; }
	Float GetDenominator(void) const { return denominator; }

	void SetNumerator(Float r) { numerator = r;	}
	void SetDenominator(Float r);

	Int32 GetFrame(Float fps) const { return Int32(Floor(numerator * fps) / Floor(denominator)); }
	void Quantize(Float fps);

	friend const BaseTime operator *  (const BaseTime& t1, const BaseTime& t2);
	friend const BaseTime operator /  (const BaseTime& t1, const BaseTime& t2);

	friend const BaseTime operator +  (const BaseTime& t1, const BaseTime& t2);
	friend const BaseTime operator -  (const BaseTime& t1, const BaseTime& t2);

	friend Bool operator == (const BaseTime& t1, const BaseTime& t2);
	friend Bool operator <  (const BaseTime& t1, const BaseTime& t2);
	friend Bool operator != (const BaseTime& t1, const BaseTime& t2);
	friend Bool operator <= (const BaseTime& t1, const BaseTime& t2);
	friend Bool operator >= (const BaseTime& t1, const BaseTime& t2);
	friend Bool operator >  (const BaseTime& t1, const BaseTime& t2);

	Int32 TimeDif(const BaseTime& t2) const
	{
		Float n1 = GetNumerator();
		Float n2 = t2.GetNumerator();
		Float d1 = GetDenominator();
		Float d2 = t2.GetDenominator();
		if (n1 == n2 && d1 == d2)
			return 0;

		Float nd1 = Floor(n1 * d2);
		Float nd2 = Floor(n2 * d1);
		if (nd1 < nd2)
			return -1;
		else if (nd1 > nd2)
			return 1;
		return 0;
	}
};

inline const BaseTime operator * (const BaseTime& t1, const BaseTime& t2)
{
	return BaseTime(t1.numerator * t2.numerator, t1.denominator * t2.denominator);
}

inline const BaseTime operator / (const BaseTime& t1, const BaseTime& t2)
{
	return BaseTime(t1.numerator * t2.denominator, t1.denominator * t2.numerator);
}

inline const BaseTime operator + (const BaseTime& t1, const BaseTime& t2)
{
	return BaseTime(t1.numerator * t2.denominator + t2.numerator * t1.denominator, t1.denominator * t2.denominator);
}

inline const BaseTime operator - (const BaseTime& t1, const BaseTime& t2)
{
	return BaseTime(t1.numerator * t2.denominator - t2.numerator * t1.denominator, t1.denominator * t2.denominator);
}

inline Bool operator == (const BaseTime& t1, const BaseTime& t2)
{
	if (t1.numerator == t2.numerator && t1.denominator == t2.denominator)
		return true;	// massive problems otherwise (compiler miscalculating floor)
	return Floor(t1.numerator * t2.denominator) == Floor(t2.numerator * t1.denominator);
}

inline Bool operator < (const BaseTime& t1, const BaseTime& t2)
{
	if (t1.numerator == t2.numerator && t1.denominator == t2.denominator)
		return false;		// massive problems otherwise (compiler miscalculating floor)
	return Floor(t1.numerator * t2.denominator) < Floor(t2.numerator * t1.denominator);
}

inline Bool operator != (const BaseTime& t1, const BaseTime& t2)
{
	if (t1.numerator == t2.numerator && t1.denominator == t2.denominator)
		return false;		// massive problems otherwise (compiler miscalculating floor)
	return Floor(t1.numerator * t2.denominator) != Floor(t2.numerator * t1.denominator);
}

inline Bool operator <= (const BaseTime& t1, const BaseTime& t2)
{
	if (t1.numerator == t2.numerator && t1.denominator == t2.denominator)
		return true;	// massive problems otherwise (compiler miscalculating floor)
	return Floor(t1.numerator * t2.denominator) <= Floor(t2.numerator * t1.denominator);
}

inline Bool operator >= (const BaseTime& t1, const BaseTime& t2)
{
	if (t1.numerator == t2.numerator && t1.denominator == t2.denominator)
		return true;	// massive problems otherwise (compiler miscalculating floor)
	return Floor(t1.numerator * t2.denominator) >= Floor(t2.numerator * t1.denominator);
}

inline Bool operator > (const BaseTime& t1, const BaseTime& t2)
{
	if (t1.numerator == t2.numerator && t1.denominator == t2.denominator)
		return false;		// massive problems otherwise (compiler miscalculating floor)
	return Floor(t1.numerator * t2.denominator) > Floor(t2.numerator * t1.denominator);
}

#endif
