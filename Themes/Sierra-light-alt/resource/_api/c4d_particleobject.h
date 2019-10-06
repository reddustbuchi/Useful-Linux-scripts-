/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DPARTICLEOBJECT_H
#define __C4DPARTICLEOBJECT_H

#ifdef __API_INTERN__
abc def xyz
#endif

#include "c4d_baseobject.h"
#include "c4d_basetag.h"

struct BaseParticle
{
	Vector v;
	Int32	 count;
};

class Particle
{
public:
	Vector				off, v1, v3;
	Float					t;
	PARTICLEFLAGS bits;
};

struct ParticleDetails
{
	Matrix m;
	Float	 lifetime;
};

class ParticleTag : public VariableTag
{
private:
	ParticleTag();
	~ParticleTag();
};

class ParticleObject : public BaseObject
{
private:
	ParticleObject();
	~ParticleObject();

public:
	Int32 GetParticleCount(void);
	Bool IsMatrixAvailable(void);
	Float GetLifetime(void);

	const Particle* GetParticleR(ParticleTag* pt, Int32 i) { return C4DOS.Bo->PrGetParticleR(this, pt, i); }
	Particle* GetParticleW(ParticleTag* pt, Int32 i) { return C4DOS.Bo->PrGetParticleW(this, pt, i); }
	ParticleDetails* GetParticleDetails(BaseDocument* doc);
};

static inline Matrix CalcParticleMatrix(Particle* cp)
{
	Matrix m;
	m.v1	= !cp->v1;
	m.v3	= !cp->v3;
	m.v2	= !Cross(m.v3, m.v1);
	m.off = cp->off;
	return m;
}

#endif
