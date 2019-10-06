/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DBASEMATERIAL_H
#define __C4DBASEMATERIAL_H

#ifdef __API_INTERN__
abc def xyz
#endif

#include "operatingsystem.h"
#include "c4d_baselist.h"

#define MatCall(fnc) (this->*C4DOS.Mt->fnc)

class BaseMaterial : public BaseList2D
{
private:
	BaseMaterial();
	~BaseMaterial();

public:
	BaseMaterial* GetNext(void) { return (BaseMaterial*)AtCall(GetNext) (); }
	BaseMaterial* GetPred(void) { return (BaseMaterial*)AtCall(GetPred) (); }

	void Update(Bool preview, Bool rttm);

	BaseChannel* GetChannel(Int32 id) { return C4DOS.Mt->GetChannel(this, id); }
	BaseBitmap* GetPreview(Int32 flags);

	Bool Compare(BaseMaterial* snd);

	Vector GetAverageColor(Int32 channel = NOTOK);

	void Displace(VolumeData* sd) { MatCall(Displace) (sd); }
	void ChangeNormal(VolumeData* sd) { MatCall(ChangeNormal) (sd); }
	void CalcSurface(VolumeData* sd) { MatCall(CalcSurface) (sd); }
	void CalcTransparency(VolumeData* sd) { MatCall(CalcTransparency) (sd); }
	void CalcAlpha(VolumeData* sd) { MatCall(CalcAlpha) (sd); }
	void CalcVolumetric(VolumeData* sd) { MatCall(CalcVolumetric) (sd); }
	void InitCalculation(VolumeData* sd, INITCALCULATION type) { MatCall(InitCalculation) (sd, type); }
	VOLUMEINFO GetRenderInfo(void) { return MatCall(GetRenderInfo) (); }
	GL_MESSAGE GlMessage(Int32 type, void* data = nullptr) { return MatCall(GlMessage) (type, data); }
	Bool HasEditorTransparency() { return MatCall(HasEditorTransparency) (); }

	static BaseMaterial* Alloc(Int32 type);
	static void Free(BaseMaterial*& mat);
};

class Material : public BaseMaterial
{
private:
	Material();
	~Material();

public:
	Bool GetChannelState(Int32 channel) { return C4DOS.Mt->GetChannelState(this, channel); }
	void SetChannelState(Int32 channel, Bool state) { C4DOS.Mt->SetChannelState(this, channel, state); }

	static Material* Alloc();
	static void Free(Material*& mat);
};

#endif
