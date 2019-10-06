/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4D_BITMAPFILTER_H
#define __C4D_BITMAPFILTER_H

#include "x4d_filter.h"

class BaseBitmap;

// bitmap stuff
BM_TILE* BfBitmapTileGet(BM_REF bm, const RECT32* src_rect, Int32 width, Int32 height, Int32 tile_mode, Int32 flags);
Int32	BfBitmapTileDetach(BM_REF bm, BM_TILE* tile_buf, Int32 flags);
Int32	BfDiscardChanges(BM_REF bm);
Int32	BfUpdateView(BM_REF bm);
Bool BfConvertTileToBasebmp(const BM_TILE* tile, const RECT32* tile_rect, BaseBitmap* bmp, Int32 zero);
Bool BfBitmapTileScale(BM_REF bm, BM_TILE* src_bm, BM_TILE* dst_bm, RECT32* src_rect, RECT32* dst_rect);

// progress functions
PROGRESS_ID	BfProgressNew(BM_REF bm);
Int32	BfProgressDelete(BM_REF bm, PROGRESS_ID pid);
Int32	BfProgressUpdate(BM_REF bm, PROGRESS_ID pid, Int32 current_value, Int32 max_value, const String& text);

BaseContainer GetGlobalFilterPrefs(Int32 pluginid);
Bool SetGlobalFilterPrefs(Int32 pluginid, const BaseContainer& prefs);

void* GetEditorWindow(void);						// get system window handle of the editor window
Bool IsHostWindow(void* win);						// check if the windowhandle is one of the cinema windows
#ifdef __MAC
Bool Mac_hostProcessEvent(void* event);	// mac event routing
#endif



#endif
