#include "lib_sculptbrush.h"
#include "c4d.h"

SculptBrushBaseLibrary *lib_SculptBrushBase = nullptr;

static SculptBrushBaseLibrary *CheckSculptBrushBaseLibrary(Int32 offset)
{
	return (SculptBrushBaseLibrary*)CheckLib(LIBRARY_SCULPTBRUSH,offset,(C4DLibrary**)&lib_SculptBrushBase);
}

#define SculptBrushBaseLibraryCall(b) 		SculptBrushBaseLibrary *lib = CheckSculptBrushBaseLibrary(LIBOFFSET(SculptBrushBaseLibrary, b)); \
															if (!lib || !lib->b) return; \
															(((iSculptBrushBase*)this)->*lib->b)

#define SculptBrushBaseLibraryCallR(a,b)  SculptBrushBaseLibrary *lib = CheckSculptBrushBaseLibrary(LIBOFFSET(SculptBrushBaseLibrary, b)); \
															if (!lib || !lib->b) return a; \
															return (((iSculptBrushBase*)this)->*lib->b)

#define BrushLibraryCall(b) 	SculptBrushBaseLibrary *lib = CheckSculptBrushBaseLibrary(LIBOFFSET(SculptBrushBaseLibrary, b)); \
	if (!lib || !lib->b) return; \
	(lib->b)

#define BrushLibraryCallR(a,b)  SculptBrushBaseLibrary *lib = CheckSculptBrushBaseLibrary(LIBOFFSET(SculptBrushBaseLibrary, b)); \
	if (!lib || !lib->b) return a; \
	return (lib->b)


//================================================
//BrushDabData
//================================================
const BaseContainer *	BrushDabData::GetData()				{ BrushLibraryCallR(nullptr,brushDabDataGetData)(this); }
const SculptObject *	BrushDabData::GetObject()			{ BrushLibraryCallR(nullptr,brushDabDataGetObject)(this); }
const BrushPointData *	BrushDabData::GetPointData()		{ BrushLibraryCallR(nullptr,brushDabDataGetPointData)(this); }
const BrushPolyData *	BrushDabData::GetPolyData()			{ BrushLibraryCallR(nullptr,brushDabDataGetPolyData)(this); }
PolygonObject *			BrushDabData::GetPolygonObject()	{ BrushLibraryCallR(nullptr,brushDabDataGetPolygonObject)(this); }
PolygonObject *			BrushDabData::GetBaseObject()		{ BrushLibraryCallR(nullptr,brushDabDataGetBaseObject)(this); }
Int32					BrushDabData::GetPointCount()		{ BrushLibraryCallR(0,brushDabDataGetPointCount)(this); }
Int32					BrushDabData::GetPolyCount()		{ BrushLibraryCallR(0,brushDabDataGetPolyCount)(this); }
Neighbor *				BrushDabData::GetNeighbor()			{ BrushLibraryCallR(nullptr,brushDabDataGetNeighbor)(this); }
SculptLayer *			BrushDabData::GetLayer()			{ BrushLibraryCallR(nullptr,brushDabDataGetLayer)(this); }
const Vector *			BrushDabData::GetPoints()			{ BrushLibraryCallR(nullptr,brushDabDataGetPoints)(this); }
const Vector32 *		BrushDabData::GetOriginalPoints()	{ BrushLibraryCallR(nullptr,brushDabDataGetOriginalPoints)(this); }
Vector					BrushDabData::GetNormal()			{ BrushLibraryCallR(Vector(),brushDabDataGetNormal)(this); }
Float					BrushDabData::GetBrushStrength()	{ BrushLibraryCallR(0,brushDabDataGetBrushStrength)(this); }
Float					BrushDabData::GetBrushRadius()		{ BrushLibraryCallR(0,brushDabDataGetBrushRadius)(this); }
Vector					BrushDabData::GetMousePos3D()		{ BrushLibraryCallR(Vector(),brushDabDataGetMousePos3D)(this); }
Vector					BrushDabData::GetHitPoint()			{ BrushLibraryCallR(Vector(),brushDabDataGetHitPoint)(this); }
Vector					BrushDabData::GetLastHitPoint()		{ BrushLibraryCallR(Vector(),brushDabDataGetLastHitPoint)(this); }
Vector					BrushDabData::GetEyePoint()			{ BrushLibraryCallR(Vector(),brushDabDataGetEyePoint)(this); }
Bool					BrushDabData::IsMirroredDab()		{ BrushLibraryCallR(false,brushDabDataIsMirroredDab)(this); }
Int32					BrushDabData::GetBrushOverride()	{ BrushLibraryCallR(0,brushDabDataGetBrushOverride)(this); }
BaseDraw *				BrushDabData::GetBaseDraw()			{ BrushLibraryCallR(nullptr,brushDabDataGetBaseDraw)(this); }
void					BrushDabData::GetAveragePointAndNormal(Vector &averagePoint, Vector &normal) { BrushLibraryCall(brushDabDataGetAveragePointAndNormal)(this,averagePoint,normal); }
Float					BrushDabData::GetBrushFalloff(Int32 index, Vector32 *pRetStencilColor, Float *pCustomDistance) { BrushLibraryCallR(0,brushDabDataGetBrushFalloff)(this,index,pRetStencilColor, pCustomDistance); }
Float					BrushDabData::GetBrushFalloffFromPos(const Vector &pos) { BrushLibraryCallR(0,brushDabDataGetBrushFalloffFromPos)(this,pos); }
void					BrushDabData::OffsetPoint(Int32 index, const Vector &offset, Vector32 *pVertexColor, SCULPTOFFSETFLAGS flags) { BrushLibraryCall(brushDabDataOffsetPoint)(this,index, offset, pVertexColor, flags); }
Bool					BrushDabData::IsPreviewDab() { BrushLibraryCallR(false,brushDabDataIsPreviewDab)(this); }
void					BrushDabData::OffsetPreviewPoint(Int32 index, const Vector &offset, SCULPTOFFSETFLAGS flags) { BrushLibraryCall(brushDabDataOffsetPreviewPoint)(this,index,offset,flags); }
void					BrushDabData::ApplySmooth()	{ BrushLibraryCall(brushDabDataApplySmooth)(this); }
const Vector32*			BrushDabData::GetVertexNormals() { BrushLibraryCallR(nullptr,brushDabDataGetVertexNormals)(this); }
Float					BrushDabData::GetAutoScaleValue(Bool noRadius) { BrushLibraryCallR(1,brushDabDataGetAutoScaleValue)(this,noRadius); }
void					BrushDabData::DirtyAllPoints(SCULPTBRUSHDATATYPE type) { BrushLibraryCall(brushDabDataDirtyAllPoints)(this, type); }
Bool					BrushDabData::IsPointModified(Int32 index) { BrushLibraryCallR(false,brushDabDataIsPointModified)(this, index); }
Float					BrushDabData::GetStencilColor(const Vector &point, Vector32 *pRetColor, Vector32 *pRetCoords, SAMPLEMODE mode) { BrushLibraryCallR(0,brushDabDataGetStencilColor)(this, point, pRetColor, pRetCoords, mode); }
Float					BrushDabData::GetStampColor(const Vector &point, Float distanceFromHitPoint, Vector32 *pRetColor, Vector32 *pRetCoords, SAMPLEMODE mode) { BrushLibraryCallR(0,brushDabDataGetStampColor)(this, point, distanceFromHitPoint, pRetColor, pRetCoords, mode); }
const BaseBitmap* BrushDabData::GetStamp() { BrushLibraryCallR(nullptr,brushDabDataGetStamp)(this); }
const BaseBitmap* BrushDabData::GetStencil() { BrushLibraryCallR(nullptr,brushDabDataGetStencil)(this); }
SculptBrushToolData*	BrushDabData::GetBrush() { BrushLibraryCallR(nullptr,brushDabDataGetBrush)(this);}
Int32					BrushDabData::GetStrokeInstanceID() { BrushLibraryCallR(0,brushDabDataGetStrokeInstanceID)(this);}
Bool					BrushDabData::IsSculptObject() { BrushLibraryCallR(false,brushDabDataIsSculptObject)(this); }

//================================================
//CustomSculptBrushBase
//================================================
CustomSculptBrushBase* CustomSculptBrushBase::Alloc()
{
	SculptBrushBaseLibrary *lib = CheckSculptBrushBaseLibrary(LIBOFFSET(SculptBrushBaseLibrary,Alloc)); if (!lib) return nullptr;
	return (CustomSculptBrushBase*)lib->Alloc();
}

void CustomSculptBrushBase::Free(CustomSculptBrushBase *&p)
{
	if (!p) return;
	SculptBrushBaseLibrary *lib = CheckSculptBrushBaseLibrary(LIBOFFSET(SculptBrushBaseLibrary,Free)); if (!lib) return;
	iSculptBrushBase* i = (iSculptBrushBase*)p;
	lib->Free(i);
	p = nullptr;
}

Bool CustomSculptBrushBase::InitTool(BaseDocument* doc, BaseContainer& data, BaseThread* bt, SculptBrushToolData *tool) { SculptBrushBaseLibraryCallR(false,InitTool)(doc,data,bt,tool); }
void CustomSculptBrushBase::FreeTool(BaseDocument* doc, BaseContainer& data, SculptBrushToolData *tool) { SculptBrushBaseLibraryCall(FreeTool)(doc,data,tool); }
void CustomSculptBrushBase::InitDefaultSettings(BaseDocument *doc, BaseContainer &data, SculptBrushToolData *tool) { SculptBrushBaseLibraryCall(InitDefaultSettings)(doc,data, tool); }
Bool CustomSculptBrushBase::GetDEnabling(BaseDocument* doc, BaseContainer& data, const DescID& id, const GeData& t_data, DESCFLAGS_ENABLE flags, const BaseContainer* itemdesc, SculptBrushToolData *tool) { SculptBrushBaseLibraryCallR(false,GetDEnabling)(doc,data,id,t_data,flags,itemdesc,tool); }
Bool CustomSculptBrushBase::SetDParameter(BaseDocument* doc, BaseContainer& data, const DescID& id, const GeData& t_data, DESCFLAGS_SET& flags, SculptBrushToolData *tool) { SculptBrushBaseLibraryCallR(false,SetDParameter)(doc,data,id,t_data,flags,tool); }
Bool CustomSculptBrushBase::GetDDescription(BaseDocument* doc, BaseContainer& data, Description* description, DESCFLAGS_DESC& flags, SculptBrushToolData *tool) { SculptBrushBaseLibraryCallR(false,GetDDescription)(doc,data,description,flags,tool); }
Bool CustomSculptBrushBase::Message(BaseDocument *doc, BaseContainer &data, Int32 type, void *t_data, SculptBrushToolData *tool) { SculptBrushBaseLibraryCallR(false,Message)(doc,data,type,t_data,tool); }
Bool CustomSculptBrushBase::GetCursorInfo(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, Float x, Float y, BaseContainer& bc, SculptBrushToolData *tool) { SculptBrushBaseLibraryCallR(false,GetCursorInfo)(doc,data,bd,x,y,bc,tool); }
Bool CustomSculptBrushBase::MouseInput(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg, SculptBrushToolData *tool) { SculptBrushBaseLibraryCallR(false,MouseInput)(doc,data,bd,win,msg,tool); }
Bool CustomSculptBrushBase::KeyboardInput(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg, SculptBrushToolData *tool) { SculptBrushBaseLibraryCallR(false,KeyboardInput)(doc,data,bd,win,msg,tool); }
Int32 CustomSculptBrushBase::GetState(BaseDocument *doc, SculptBrushToolData *tool) { SculptBrushBaseLibraryCallR(0,GetState)(doc,tool); }
TOOLDRAW CustomSculptBrushBase::Draw(BaseDocument *doc, BaseContainer &data, BaseDraw *bd, BaseDrawHelp *bh, BaseThread *bt,TOOLDRAWFLAGS flags, SculptBrushToolData *tool) { SculptBrushBaseLibraryCallR(TOOLDRAW_0,Draw)(doc,data,bd,bh,bt,flags,tool); }
Bool CustomSculptBrushBase::GetDParameter(BaseDocument* doc, BaseContainer& data, const DescID& id, GeData& t_data, DESCFLAGS_GET& flags, SculptBrushToolData *tool) { SculptBrushBaseLibraryCallR(true,GetDParameter)(doc,data,id,t_data,flags,tool); }
Bool CustomSculptBrushBase::DisplayControl(BaseDocument* doc, BaseObject* op, BaseObject* chainstart, BaseDraw* bd, BaseDrawHelp* bh, ControlDisplayStruct& cds, SculptBrushToolData *tool) { SculptBrushBaseLibraryCallR(true,DisplayControl)(doc, op, chainstart, bd, bh, cds,tool); }
Bool CustomSculptBrushBase::InitDisplayControl(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, const AtomArray* active, SculptBrushToolData *tool) { SculptBrushBaseLibraryCallR(true,InitDisplayControl)(doc, data, bd,active,tool); }
void CustomSculptBrushBase::FreeDisplayControl(SculptBrushToolData *tool) { SculptBrushBaseLibraryCall(FreeDisplayControl)(tool); }

//Virtual
void CustomSculptBrushBase::StartStroke(Int32 strokeCount, const BaseContainer &data)  { SculptBrushBaseLibraryCall(StartStroke)(strokeCount, data); }
void CustomSculptBrushBase::StartStrokeInstance(Int32 strokeInstanceID)  { SculptBrushBaseLibraryCall(StartStrokeInstance)(strokeInstanceID); }
void CustomSculptBrushBase::StartSymmetry()  { SculptBrushBaseLibraryCall(StartSymmetry)(); }
void CustomSculptBrushBase::StartStrokeInstanceDabs(Int32 strokeInstanceID)  { SculptBrushBaseLibraryCall(StartStrokeInstanceDabs)(strokeInstanceID); }
void CustomSculptBrushBase::StartDab(Int32 strokeInstanceID)  { SculptBrushBaseLibraryCall(StartDab)(strokeInstanceID); }
void CustomSculptBrushBase::EndDab(Int32 strokeInstanceID)  { SculptBrushBaseLibraryCall(EndDab)(strokeInstanceID); }
void CustomSculptBrushBase::EndStrokeInstanceDabs(Int32 strokeInstanceID)  { SculptBrushBaseLibraryCall(EndStrokeInstanceDabs)(strokeInstanceID); }
void CustomSculptBrushBase::EndSymmetry()  { SculptBrushBaseLibraryCall(EndSymmetry)(); }
void CustomSculptBrushBase::EndStrokeInstance(Int32 strokeInstanceID)  { SculptBrushBaseLibraryCall(EndStrokeInstance)(strokeInstanceID); }
void CustomSculptBrushBase::EndStroke()  { SculptBrushBaseLibraryCall(EndStroke)(); }

void CustomSculptBrushBase::OverwriteLoadedPresetSettings(BaseContainer &data) { SculptBrushBaseLibraryCall(OverwriteLoadedPresetSettings)(data); }
void CustomSculptBrushBase::PostInitDefaultSettings(BaseDocument *doc, BaseContainer &data) { SculptBrushBaseLibraryCall(PostInitDefaultSettings)(doc,data); }
Bool CustomSculptBrushBase::GetEnabling(Int32 id) { SculptBrushBaseLibraryCallR(true,GetEnabling)(id); }
Bool CustomSculptBrushBase::HandleNonModelPickMode(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg) { SculptBrushBaseLibraryCallR(true,HandleNonModelPickMode)(doc, data, bd, win, msg); }
Bool CustomSculptBrushBase::HandleFillTool(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg) { SculptBrushBaseLibraryCallR(true,HandleFillTool)(doc, data, bd, win, msg); }

Bool CustomSculptBrushBase::DrawNonModelPickMode(BaseDocument *doc, BaseContainer &data, BaseDraw *bd, BaseDrawHelp *bh, BaseThread *bt,TOOLDRAWFLAGS flags) { SculptBrushBaseLibraryCallR(true,DrawNonModelPickMode)(doc, data, bd, bh, bt,flags); }
void CustomSculptBrushBase::FloodSelectedLayer(SculptObject *pSculpt, SculptLayer *pLayer, const BaseContainer& brushData, Int32 function, Bool preview, Float *customStrength, const Vector32 *pVertexNormals) { SculptBrushBaseLibraryCall(FloodSelectedLayer)(pSculpt, pLayer, brushData, function, preview, customStrength, pVertexNormals); }
Bool CustomSculptBrushBase::HasDrawMode(Int32 mode) { SculptBrushBaseLibraryCallR(true,HasDrawMode)(mode); }

//Non-Virtual 
Bool CustomSculptBrushBase::Flood(BaseDocument* doc, BaseDraw* bd, const BaseContainer& brushData, Int32 button) { SculptBrushBaseLibraryCallR(false,Flood)(doc, bd,brushData,button); }
void CustomSculptBrushBase::EnableSpecialDrawGizmo(){ SculptBrushBaseLibraryCall(EnableSpecialDrawGizmo)(); }
void CustomSculptBrushBase::DisableSpecialDrawGizmo(){ SculptBrushBaseLibraryCall(DisableSpecialDrawGizmo)(); }
void CustomSculptBrushBase::SetMouseDrag(Bool value){ SculptBrushBaseLibraryCall(SetMouseDrag)(value); }
Bool CustomSculptBrushBase::IsMouseDrag(){ SculptBrushBaseLibraryCallR(false,IsMouseDrag)(); }
void CustomSculptBrushBase::CacheObjects(BaseDocument *doc) { SculptBrushBaseLibraryCall(CacheObjects)(doc); }
Int32 CustomSculptBrushBase::GetSelectionCacheCount(){ SculptBrushBaseLibraryCallR(0,GetSelectionCacheCount)(); }
BaseList2D *CustomSculptBrushBase::GetSelectionCacheObject(Int32 index){ SculptBrushBaseLibraryCallR(nullptr,GetSelectionCacheObject)(index); }
Float CustomSculptBrushBase::GetBrushStrength(Bool original){ SculptBrushBaseLibraryCallR(0,GetBrushStrength)(original); }
void CustomSculptBrushBase::InitZoomScale(BaseDocument *doc){ SculptBrushBaseLibraryCall(InitZoomScale)(doc); }

//Presets
Bool CustomSculptBrushBase::WritePresetData(HyperFile *hf)				{ SculptBrushBaseLibraryCallR(false,WritePresetData)(hf); }
Bool CustomSculptBrushBase::ReadPresetData(HyperFile *hf,Int32 level)	{ SculptBrushBaseLibraryCallR(false,ReadPresetData)(hf,level); }
Bool CustomSculptBrushBase::WriteStampPresetData(HyperFile *hf)			{ SculptBrushBaseLibraryCallR(false,WriteStampPresetData)(hf); }
Bool CustomSculptBrushBase::ReadStampPresetData(HyperFile *hf,Int32 level) { SculptBrushBaseLibraryCallR(false,ReadStampPresetData)(hf,level); }
Bool CustomSculptBrushBase::WriteSplinePresetData(HyperFile *hf)			{ SculptBrushBaseLibraryCallR(false,WriteSplinePresetData)(hf); }
Bool CustomSculptBrushBase::ReadSplinePresetData(HyperFile *hf,Int32 level) { SculptBrushBaseLibraryCallR(false,ReadSplinePresetData)(hf,level); }
void CustomSculptBrushBase::UpdateSettingsAfterPresetLoad(BaseContainer *data) { SculptBrushBaseLibraryCall(UpdateSettingsAfterPresetLoad)(data); }

const BaseBitmap *CustomSculptBrushBase::GetStamp() { SculptBrushBaseLibraryCallR(nullptr,GetStamp)(); }
const BaseBitmap *CustomSculptBrushBase::GetStencil() { SculptBrushBaseLibraryCallR(nullptr,GetStencil)(); }

//////////////////////////////////////////////////////////////////////////

Bool SculptBrushToolData::InitTool(BaseDocument* doc, BaseContainer& data, BaseThread* bt)
{
	if (!m_pBrushBase) m_pBrushBase=CustomSculptBrushBase::Alloc();
	if (!m_pBrushBase) return false;
	return m_pBrushBase->InitTool(doc,data,bt,this);
}

void SculptBrushToolData::FreeTool(BaseDocument* doc, BaseContainer& data)
{
	if (m_pBrushBase) m_pBrushBase->FreeTool(doc,data,this);
}

void SculptBrushToolData::InitDefaultSettings(BaseDocument *doc, BaseContainer &data)
{
	if (!m_pBrushBase) m_pBrushBase=CustomSculptBrushBase::Alloc();
	if (m_pBrushBase) m_pBrushBase->InitDefaultSettings(doc,data, this);
}

Bool SculptBrushToolData::GetDEnabling(BaseDocument* doc, BaseContainer& data, const DescID& id, const GeData& t_data, DESCFLAGS_ENABLE flags, const BaseContainer* itemdesc) 
{ 
	if (!SUPER::GetDEnabling(doc,data,id,t_data,flags,itemdesc)) return false;
	if(!GetEnabling(id[0].id)) return false;
	return (m_pBrushBase)?m_pBrushBase->GetDEnabling(doc,data,id,t_data,flags,itemdesc,this):false; 
}

Bool SculptBrushToolData::SetDParameter(BaseDocument* doc, BaseContainer& data, const DescID& id, const GeData& t_data, DESCFLAGS_SET& flags) 
{ 
	return (m_pBrushBase)?m_pBrushBase->SetDParameter(doc,data,id,t_data,flags,this):false; 
}

Bool SculptBrushToolData::GetDDescription(BaseDocument* doc, BaseContainer& data, Description* description, DESCFLAGS_DESC& flags)
{
	if (!m_pBrushBase) m_pBrushBase=CustomSculptBrushBase::Alloc();	
	if (!SUPER::GetDDescription(doc,data,description,flags)) return false;
	return (m_pBrushBase)?m_pBrushBase->GetDDescription(doc,data,description,flags,this):false;
}
Bool SculptBrushToolData::Message(BaseDocument *doc, BaseContainer &data, Int32 type, void *t_data) 
{ 
	Bool ret = (m_pBrushBase)?m_pBrushBase->Message(doc,data,type,t_data,this):false; 
	if(!ret) ret = SUPER::Message(doc,data,type,t_data);
	return ret;
}

Bool SculptBrushToolData::GetCursorInfo(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, Float x, Float y, BaseContainer& bc) 
{ 
	return (m_pBrushBase)?m_pBrushBase->GetCursorInfo(doc,data,bd,x,y,bc,this):false; 
}

Bool SculptBrushToolData::MouseInput(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg) 
{ 
	Bool ret = (m_pBrushBase)?m_pBrushBase->MouseInput(doc,data,bd,win,msg,this):false; 
	if(!ret) ret = SUPER::MouseInput(doc,data,bd,win,msg);
	return ret;
}

Bool SculptBrushToolData::KeyboardInput(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg) 
{ 
	Bool ret = (m_pBrushBase)?m_pBrushBase->KeyboardInput(doc,data,bd,win,msg,this):false; 
	if(!ret) ret = SUPER::KeyboardInput(doc,data,bd,win,msg);
	return ret;
}

Int32 SculptBrushToolData::GetState(BaseDocument *doc)
{
	if (!m_pBrushBase) m_pBrushBase=CustomSculptBrushBase::Alloc();	
	return (m_pBrushBase)?m_pBrushBase->GetState(doc, this) : 0;
}

TOOLDRAW SculptBrushToolData::Draw(BaseDocument *doc, BaseContainer &data, BaseDraw *bd, BaseDrawHelp *bh, BaseThread *bt,TOOLDRAWFLAGS flags)
{
	return (m_pBrushBase)?m_pBrushBase->Draw(doc,data,bd,bh,bt,flags, this) : TOOLDRAW_0;
}

Bool SculptBrushToolData::GetDParameter(BaseDocument* doc, BaseContainer& data, const DescID& id, GeData& t_data, DESCFLAGS_GET& flags)
{
	return (m_pBrushBase)?m_pBrushBase->GetDParameter(doc,data,id,t_data,flags, this) : true;
}

Bool SculptBrushToolData::DisplayControl(BaseDocument* doc, BaseObject* op, BaseObject* chainstart, BaseDraw* bd, BaseDrawHelp* bh, ControlDisplayStruct& cds)
{
	return (m_pBrushBase)?m_pBrushBase->DisplayControl(doc,op,chainstart,bd,bh,cds, this) : true;
}

Bool SculptBrushToolData::InitDisplayControl(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, const AtomArray* active)
{
	return (m_pBrushBase)?m_pBrushBase->InitDisplayControl(doc,data,bd,active, this) : true;
}

void SculptBrushToolData::FreeDisplayControl(void)
{
	if(m_pBrushBase) m_pBrushBase->FreeDisplayControl(this);
}

void SculptBrushToolData::StartStroke(Int32 strokeCount, const BaseContainer &data)
{
	if(m_pBrushBase) m_pBrushBase->StartStroke(strokeCount, data);
}

void SculptBrushToolData::EndStroke()
{
	if(m_pBrushBase) m_pBrushBase->EndStroke();
}

void SculptBrushToolData::StartStrokeInstance(Int32 strokeInstanceID)
{
	if(m_pBrushBase) m_pBrushBase->StartStrokeInstance(strokeInstanceID);
}

void SculptBrushToolData::EndStrokeInstance(Int32 strokeInstanceID)
{
	if(m_pBrushBase) m_pBrushBase->EndStrokeInstance(strokeInstanceID);
}

void SculptBrushToolData::StartStrokeInstanceDabs(Int32 strokeInstanceID)
{
	if(m_pBrushBase) m_pBrushBase->StartStrokeInstanceDabs(strokeInstanceID);
}

void SculptBrushToolData::EndStrokeInstanceDabs(Int32 strokeInstanceID)
{
	if(m_pBrushBase) m_pBrushBase->EndStrokeInstanceDabs(strokeInstanceID);
}

void SculptBrushToolData::StartSymmetry()
{
	if(m_pBrushBase) m_pBrushBase->StartSymmetry();
}

void SculptBrushToolData::EndSymmetry()
{
	if(m_pBrushBase) m_pBrushBase->EndSymmetry();
}

void SculptBrushToolData::StartDab(Int32 strokeInstanceID)
{
	if(m_pBrushBase) m_pBrushBase->StartDab(strokeInstanceID);
}

void SculptBrushToolData::EndDab(Int32 strokeInstanceID)
{
	if(m_pBrushBase) m_pBrushBase->EndDab(strokeInstanceID);
}

void SculptBrushToolData::OverwriteLoadedPresetSettings(BaseContainer &data)
{
	if(m_pBrushBase) m_pBrushBase->OverwriteLoadedPresetSettings(data);
}

void SculptBrushToolData::PostInitDefaultSettings(BaseDocument *doc, BaseContainer &data)
{
	if(m_pBrushBase) m_pBrushBase->PostInitDefaultSettings(doc,data);
}

Bool SculptBrushToolData::GetEnabling(Int32 id)
{
	return (m_pBrushBase)?m_pBrushBase->GetEnabling(id) : false;
}

Bool SculptBrushToolData::HandleFillTool(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg)
{
	return (m_pBrushBase)?m_pBrushBase->HandleFillTool(doc,data,bd,win,msg) : true;
}

Bool SculptBrushToolData::HandleNonModelPickMode(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg)
{
	return (m_pBrushBase)?m_pBrushBase->HandleNonModelPickMode(doc,data,bd,win,msg) : true;
}

Bool SculptBrushToolData::DrawNonModelPickMode(BaseDocument *doc, BaseContainer &data, BaseDraw *bd, BaseDrawHelp *bh, BaseThread *bt,TOOLDRAWFLAGS flags)
{
	return (m_pBrushBase)?m_pBrushBase->DrawNonModelPickMode(doc,data,bd,bh,bt,flags) : true;
}

void SculptBrushToolData::FloodSelectedLayer(SculptObject *pSculpt, SculptLayer *pLayer, const BaseContainer& brushData, Int32 function, Bool preview, Float *customStrength, const Vector32 *pVertexNormals)
{
	if(m_pBrushBase) m_pBrushBase->FloodSelectedLayer(pSculpt, pLayer, brushData, function, preview, customStrength,pVertexNormals);
}

Bool SculptBrushToolData::HasDrawMode(Int32 mode)
{
	if(m_pBrushBase) return m_pBrushBase->HasDrawMode(mode);
	return false;
}

//Non Virtual
Bool SculptBrushToolData::Flood(BaseDocument* doc, BaseDraw* bd, const BaseContainer& brushData, Int32 button)
{
	return (m_pBrushBase)?m_pBrushBase->Flood(doc, bd, brushData,button) : false;
}

void SculptBrushToolData::EnableSpecialDrawGizmo()
{
	if(m_pBrushBase) m_pBrushBase->EnableSpecialDrawGizmo();
}

void SculptBrushToolData::DisableSpecialDrawGizmo()
{
	if(m_pBrushBase) m_pBrushBase->DisableSpecialDrawGizmo();
}

void SculptBrushToolData::SetMouseDrag(Bool value)
{
	if(m_pBrushBase) m_pBrushBase->SetMouseDrag(value);
}

Bool SculptBrushToolData::IsMouseDrag()
{
	return (m_pBrushBase)?m_pBrushBase->IsMouseDrag() : false;
}

void SculptBrushToolData::CacheObjects(BaseDocument *doc)
{
	if(m_pBrushBase) m_pBrushBase->CacheObjects(doc);
}

Int32 SculptBrushToolData::GetSelectionCacheCount()
{
	return (m_pBrushBase)?m_pBrushBase->GetSelectionCacheCount() : 0;
}

BaseList2D *SculptBrushToolData::GetSelectionCacheObject(Int32 index)
{
	return (m_pBrushBase)?m_pBrushBase->GetSelectionCacheObject(index) : nullptr;
}

Float SculptBrushToolData::GetBrushStrength(Bool original)
{
	return (m_pBrushBase)?m_pBrushBase->GetBrushStrength(original) : 1.0;
}

void SculptBrushToolData::InitZoomScale(BaseDocument *doc)
{
	if(m_pBrushBase) m_pBrushBase->InitZoomScale(doc);
}

//Presets
Bool SculptBrushToolData::WritePresetData(HyperFile *hf)				{ 	if(m_pBrushBase) { return m_pBrushBase->WritePresetData(hf); } return false; }
Bool SculptBrushToolData::ReadPresetData(HyperFile *hf,Int32 level)		{ 	if(m_pBrushBase) { return m_pBrushBase->ReadPresetData(hf,level); } return false; }
Bool SculptBrushToolData::WriteStampPresetData(HyperFile *hf)			{ 	if(m_pBrushBase) { return m_pBrushBase->WriteStampPresetData(hf); } return false; }
Bool SculptBrushToolData::ReadStampPresetData(HyperFile *hf,Int32 level) { 	if(m_pBrushBase) { return m_pBrushBase->ReadStampPresetData(hf,level); } return false; }
Bool SculptBrushToolData::WriteSplinePresetData(HyperFile *hf)			{ 	if(m_pBrushBase) { return m_pBrushBase->WriteSplinePresetData(hf); } return false; }
Bool SculptBrushToolData::ReadSplinePresetData(HyperFile *hf,Int32 level) { 	if(m_pBrushBase) { return m_pBrushBase->ReadSplinePresetData(hf,level); } return false; }
void SculptBrushToolData::UpdateSettingsAfterPresetLoad(BaseContainer *data) { 	if(m_pBrushBase) m_pBrushBase->UpdateSettingsAfterPresetLoad(data); }
const BaseBitmap *SculptBrushToolData::GetStamp()							 { 	if(m_pBrushBase) { return m_pBrushBase->GetStamp(); } return nullptr; }
const BaseBitmap *SculptBrushToolData::GetStencil()							 { 	if(m_pBrushBase) { return m_pBrushBase->GetStencil(); } return nullptr; }


//================================================
// SculptBrushParams
//================================================
SculptBrushParams* SculptBrushParams::Alloc() { BrushLibraryCallR(nullptr,sculptbrushparamsAlloc)(); }
void SculptBrushParams::Free(SculptBrushParams *&params) { BrushLibraryCall(sculptbrushparamsFree)(params); }
void SculptBrushParams::EnableStencil(Bool enable) { BrushLibraryCall(sculptbrushparamsEnableStencil)(this,enable); }
void SculptBrushParams::EnableStamp(Bool enable) { BrushLibraryCall(sculptbrushparamsEnableStamp)(this,enable); }
void SculptBrushParams::EnableInvertCheckbox(Bool enable) { BrushLibraryCall(sculptbrushparamsEnableInvertCheckbox)(this,enable); }
void SculptBrushParams::EnableBuildup(Bool enable) { BrushLibraryCall(sculptbrushparamsEnableBuildup)(this,enable); }
void SculptBrushParams::EnableNonModelPickMode(Bool enable) { BrushLibraryCall(sculptbrushparamsEnableNonModelPickMode)(this,enable); }
void SculptBrushParams::EnableFlood(Bool enable) { BrushLibraryCall(sculptbrushparamsEnableFlood)(this,enable); }
void SculptBrushParams::EnableMultiThreading(Bool enable) { BrushLibraryCall(sculptbrushparamsEnableMultiThreading)(this,enable); }
void SculptBrushParams::EnableToolSpecificSmooth(Bool enable) { BrushLibraryCall(sculptbrushparamsEnableToolSpecificSmooth)(this,enable); }
void SculptBrushParams::EnableBrushAccess(Bool enable) { BrushLibraryCall(sculptbrushparamsEnableBrushAccess)(this,enable); }

void SculptBrushParams::SetFloodType(SCULPTBRUSHDATATYPE type) { BrushLibraryCall(sculptbrushparamsSetFloodType)(this,type); }
void SculptBrushParams::SetBrushMode(SCULPTBRUSHMODE mode) { BrushLibraryCall(sculptbrushparamsSetBrushMode)(this,mode); }
void SculptBrushParams::SetFirstHitPointType(FIRSTHITPPOINTTYPE type) { BrushLibraryCall(sculptbrushparamsSetFirstHitPointType)(this,type); }
void SculptBrushParams::SetUndoType(SCULPTBRUSHDATATYPE type) { BrushLibraryCall(sculptbrushparamsSetUndoType)(this,type); }
void SculptBrushParams::SetMovePointFunc(Bool (*surfaceMovePointFunc)(BrushDabData *dab)) { BrushLibraryCall(sculptbrushparamsSetMovePointFunc)(this,surfaceMovePointFunc); }



Bool IsSculptBrush(Int32 toolID)
{
	BasePlugin *pPlugin = FindPlugin(toolID,PLUGINTYPE_TOOL);
	if(pPlugin)
	{
		return (pPlugin->GetInfo() & PLUGINFLAG_TOOL_SCULPTBRUSH);
	}
	return false;
}

SculptBrushToolData *GetSelectedSculptBrush(BaseDocument *doc)
{
	if(!doc) 
		return nullptr;

	Int32 toolID = doc->GetAction();
	BasePlugin* pPlugin = FindPlugin(toolID,PLUGINTYPE_TOOL);
	if(!pPlugin) 
		return nullptr;

	Bool isSculptBrush = pPlugin->GetInfo() & PLUGINFLAG_TOOL_SCULPTBRUSH;
	if(!isSculptBrush) 
		return nullptr;

	TOOLPLUGIN *toolPlugin = (TOOLPLUGIN *)pPlugin->GetPluginStructure();
	if (toolPlugin)
	{
		return (SculptBrushToolData*)toolPlugin->adr;
	}

	return nullptr;
}
