/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __X4D_SCALE_BLT__
#define __X4D_SCALE_BLT__

#include	"miniblt.h"

//----------------------------------------------------------------------------------------
// Ausgabefunktionen
//----------------------------------------------------------------------------------------
extern Int32 scale_blt(BLT_MEM* bfn,
											 const BM_TILE* in_src_bm, const BM_TILE* in_dst_bm,
											 const RECT32* src_rect, const RECT32* dst_rect,
											 const RECT32* clip_rect);

#endif
