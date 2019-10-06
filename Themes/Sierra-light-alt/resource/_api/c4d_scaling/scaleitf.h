/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __X4D_SCALE_ITF__
#define __X4D_SCALE_ITF__

#include "x4d_filter.h"

extern Int32 scale_bm(const BM_TILE* src_bm, const BM_TILE* dst_bm,
											const RECT32* src_rect, const RECT32* dst_rect,
											const RECT32* clip_rect);

#endif
