/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DVIDEOPOST_H
#define __C4DVIDEOPOST_H

#include "c4d_baselist.h"
#include "c4d_videopostplugin.h"

class BaseVideoPost : public BaseList2D
{
private:
	BaseVideoPost();
	~BaseVideoPost();

public:
	BaseVideoPost* GetNext(void) { return (BaseVideoPost*)AtCall(GetNext) (); }
	BaseVideoPost* GetPred(void) { return (BaseVideoPost*)AtCall(GetPred) (); }

	// reuse the container IDs from RDATA_STEREO_*
	Bool StereoMergeImages(BaseBitmap* dest, const BaseBitmap* const* source, Int32 cnt, const BaseContainer& settings, COLORSPACETRANSFORMATION transform);
	Int32 StereoGetCameraCountEditor(BaseDocument* doc, BaseDraw* bd);
	Int32 StereoGetCameraCountRenderer(BaseDocument* doc, RenderData* rd);
	Bool StereoGetCameraInfo(BaseDocument* doc, BaseDraw* bd, RenderData* rd, Int32 index, StereoCameraInfo& info);

	Bool RenderEngineCheck(Int32 id);

	static BaseVideoPost* Alloc(Int32 type);
	static void Free(BaseVideoPost*& bl);
};

#endif
