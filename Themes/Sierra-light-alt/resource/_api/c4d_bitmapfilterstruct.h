/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4D_BITMAPFILTERSTRUCT_H
#define __C4D_BITMAPFILTERSTRUCT_H

struct BM_TILE;
struct BM_INFO;
typedef BM_INFO* BM_REF;
struct RECT32;
typedef Int32	PROGRESS_ID;

struct C4D_BitmapFilter
{
	BM_TILE*		(*BitmapTileGet)(BM_REF bm, const RECT32 *src_rect, Int32 width, Int32 height, Int32 tile_mode, Int32 flags, Int32 unused);
	Int32				(*BitmapTileDetach)(BM_REF bm, BM_TILE* tile_buf, Int32 flags);
	Bool				(*ConvertTileToBasebmp)(const BM_TILE* tile, const RECT32* tile_rect, BaseBitmap* bmp, Int32 zero);

	Int32				(*DiscardChanges)(BM_REF bm);
	Int32				(*UpdateView)(BM_REF bm);

	PROGRESS_ID	(*ProgressNewEx)(void);
	Int32				(*ProgressDeleteEx)(PROGRESS_ID pid);
	Int32				(*ProgressUpdateEx)(PROGRESS_ID pid, Int32 current_value, Int32 max_value, const String* text);

	Bool				(*GetGlobalFilterPrefs)(BaseContainer* prefs);
	Bool				(*SetGlobalFilterPrefs)(const BaseContainer* prefs);

	void*				(*GetEditorWindow)(void);								// returns the hwnd of the editor window
	Bool				(*IsHostWindow)(void* win);						// check if the hwnd is one of cinema windows
	Bool				(*Mac_hostProcessEvent)(void* event);	// call mac event proc, return true programm should stop

	PROGRESS_ID	(*ProgressNew)(BM_REF bm);
	Int32				(*ProgressDelete)(BM_REF bm, PROGRESS_ID pid);
	Int32				(*ProgressUpdate)(BM_REF bm, PROGRESS_ID pid, Int32 current_value, Int32 max_value, const String* text);
};

#endif
