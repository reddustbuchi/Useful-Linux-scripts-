/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DBASECHANNEL_H
#define __C4DBASECHANNEL_H

#ifdef __API_INTERN__
abc def xyz
#endif

#include "ge_math.h"
#include "c4d_basebitmap.h"
#include "c4d_gui.h"
#include "c4d_baselist.h"

class Filename;
class BaseBitmap;
class BaseContainer;
class GeDialog;
struct VolumeData;

#define PsBaCall(fnc) (this->*C4DOS.Ba->fnc)

class BaseShader : public BaseList2D
{
private:
	BaseShader();
	~BaseShader();

public:
	INITRENDERRESULT InitRender(const InitRenderStruct& is) { return PsBaCall(InitRender) (is); }
	void FreeRender(void) { PsBaCall(FreeRender) (); }
	Vector Sample(ChannelData* cd) { return PsBaCall(Sample) (cd); }
	Vector SampleBump(ChannelData* cd, SAMPLEBUMP bumpflags) { return PsBaCall(SampleBump) (cd, bumpflags); }
	BaseBitmap* GetBitmap(void) { return PsBaCall(GetBitmap) (); }
	SHADERINFO GetRenderInfo(void) { return PsBaCall(GetRenderInfo) (); }
	Bool Compare(BaseShader* dst) { return PsBaCall(PsCompare) (dst); }
	GL_MESSAGE GlMessage(Int32 type, void* data) { return PsBaCall(GlMessage) (type, data); }
	Bool IsColorManagementOff(BaseDocument* doc) { return PsBaCall(IsColorManagementOff) (doc); }
	void DestroyGLImage(BaseDocument* doc) { PsBaCall(DestroyGLImage) (doc); }
	void InvalidateGLImage(BaseDocument* doc) { PsBaCall(InvalidateGLImage) (doc); }
	BaseShader* GetSubsurfaceShader(Float& bestmpl) { return PsBaCall(GetSubsurfaceShader) (bestmpl); }

	BaseShader* GetNext(void) { return (BaseShader*)AtCall(GetNext) (); }
	BaseShader* GetPred(void) { return (BaseShader*)AtCall(GetPred) (); }
	BaseShader* GetUp  (void) { return (BaseShader*)AtCall(GetUp) (); }
	BaseShader* GetDown(void) { return (BaseShader*)AtCall(GetDown) (); }
	BaseShader* GetDownLast(void) { return (BaseShader*)AtCall(GetDownLast) (); }

	static BaseShader* Alloc(Int32 type);
	static void Free(BaseShader*& ps);
};

class BaseChannel : public C4DAtom
{
private:
	BaseChannel();
	~BaseChannel();

public:
	Bool Compare(BaseChannel* dst);

	INITRENDERRESULT InitTexture(const InitRenderStruct& irs);
	void FreeTexture(void);

	BaseContainer	GetData(void);
	void SetData(const BaseContainer& ct);

	Int32	GetShaderID(void);
	BaseShader*		GetShader(void);
	BaseBitmap*			GetBitmap(void) { return C4DOS.Ba->BCGetBitmap(this); }

	Vector Sample(VolumeData* vd, Vector* p, Vector* delta, Vector* n, Float t, Int32 tflag, Float off, Float scale) { return C4DOS.Ba->BcSample(this, vd, p, delta, n, t, tflag, off, scale); }

	Bool Attach(GeListNode* element);

	static BaseChannel* Alloc(void);
	static void Free(BaseChannel*& bc);
};

inline Bool HandleShaderPopupI   (BaseList2D* parent, BaseShader*& current, Int32 value, Int param) { return C4DOS.Ba->HandleShaderPopupI(parent, current, value, param); }
inline Bool BuildShaderPopupMenuI(BaseContainer* menu, BaseList2D* parent, BaseShader* current, Int param) { return C4DOS.Ba->BuildShaderPopupMenuI(menu, parent, current, param); }

inline Bool HandleShaderPopup    (const BaseContainer& bc, const DescID& descid, Int32 value, Int param) { return C4DOS.Ba->HandleShaderPopup(bc, descid, value, param); }
inline Bool BuildShaderPopupMenu (BaseContainer* menu, const BaseContainer& bc, const DescID& descid, Int param) { return C4DOS.Ba->BuildShaderPopupMenu(menu, bc, descid, param); }

inline String GetChannelName(Int32 channelid) { return C4DOS.Ba->GetChannelName(channelid); }

#endif
