/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _LIB_CLIPMAP_H_
#define _LIB_CLIPMAP_H_

#include "c4d_library.h"

#ifdef __API_INTERN__

#include "ge_file.h"
#include	"ge_cp2d.h"

#define iGeClipMap	GeClipMap

#else

#include "c4d_file.h"

enum GE_CM_CLIPREGION
{
	GE_CM_CLIPREGION_EVENODD		= 1,
	GE_CM_CLIPREGION_WINDING		= 2
} ENUM_END_LIST(GE_CM_CLIPREGION);

enum GE_CM_DRAWMODE
{
	GE_CM_DRAWMODE_COPY			= 0,
	GE_CM_DRAWMODE_BLEND		= 1,
	GE_CM_DRAWMODE_MASK			= 2
} ENUM_END_LIST(GE_CM_DRAWMODE);

#ifndef GE_CM_SRC_MAX_OPACITY
#define	GE_CM_SRC_MAX_OPACITY	256														// this is the maximum source opacity for GE_CM_DRAWMODE_BLEND and equals 1.0 which means opaque, 128 equals 0.5 and so on ...
#endif

enum GE_CM_BLIT
{
	GE_CM_BLIT_COPY			= 0,																	// source overwrites destination
	GE_CM_BLIT_COL			= 1,																	// source overwrites destination wherever source doesn't equal the background color
	GE_CM_BLIT_FG				= 2																		// sets pixels to the foreground color if the color is not the background color
} ENUM_END_LIST(GE_CM_BLIT);

enum GE_CM_ARCSEGMENT
{
	GE_CM_ARCSEGMENT_RIGHTTOP    = 0, // (x1,y1) -> (x2,y1) -> (x2,y2)
	GE_CM_ARCSEGMENT_RIGHTBOTTOM = 1, // (x2,y1) -> (x2,y2) -> (x1,y2)
	GE_CM_ARCSEGMENT_LEFTBOTTOM  = 2, // (x2,y2) -> (x1,y2) -> (x1,y1)
	GE_CM_ARCSEGMENT_LEFTTOP     = 3  // (x1,y2) -> (x1,y1) -> (x2,y1)
} ENUM_END_LIST(GE_CM_ARCSEGMENT);

enum GE_CM_FONTSORT
{
	GE_CM_FONTSORT_FLAT					= 0,
	GE_CM_FONTSORT_HIERARCHICAL	= 1
} ENUM_END_LIST(GE_CM_FONTSORT);

class BaseBitmap;

typedef struct _NGV_DRAW_PORT*		NGVH_DP;
typedef struct _NGV_RGN*					NGVH_RGN;

struct GE_POINT2D
{
	Int32 x;
	Int32 y;
};

enum GeFontNameType
{
	GE_FONT_NAME_DISPLAY = 0,																	// human readable font name (e.g. "Helvetica Bold")
	GE_FONT_NAME_FAMILY = 1,																	// font family name (e.g. "Helvetica")
	GE_FONT_NAME_STYLE = 2,																		// font style name (e.g. "Bold")
	GE_FONT_NAME_POSTSCRIPT = 3																// font postscript name (e.g. "Helvetica-Bold")
};

enum GeFontDefaultType
{
	GE_FONT_DEFAULT_SYSTEM = 0,																// the c4d system font
	GE_FONT_DEFAULT_MONOSPACED = 1														// the c4d monospaced font
};

enum GeFontSizeType
{
	GE_FONT_SIZE_INTERNAL = 0																	// the unit of the font size is not specified (OS or context dependent) it is NOT guaranteed to be pixels or points or whatever, you can only use it to compare the size of two font descriptions
};

class GeClipMap
{
	public:
		static GeClipMap* Alloc();
		static void Free       (GeClipMap *&data);

	private:
		GeClipMap();
		~GeClipMap();

	public:
		IMAGERESULT	Init			(Int32 w, Int32 h, Int32 bits);
		IMAGERESULT	Init   		(BaseBitmap *bm);
		IMAGERESULT	Init   		(BaseBitmap *bm, BaseBitmap *alpha_channel);
		IMAGERESULT	Init      (const Filename &name, Int32 frame, Bool *ismovie);
		IMAGERESULT	Init   		(const IconData& iconData);
		void	Destroy					();

		void	GetDim					(Int32 *w, Int32 *h) const;
		Int32	GetBw						() const;
		Int32	GetBh						() const;

		BaseBitmap* GetBitmap	();

		void	BeginDraw				();
		void	EndDraw					();

		void	SetOffset				(Int32 off_x, Int32 off_y);

		void	SetDrawMode			(GE_CM_DRAWMODE mode, UInt32 par);

		void	SetColor				(Int32 r, Int32 g, Int32 b, Int32 a = 255);

		void	SetPixel				(Int32 x, Int32 y);
		void	Line						(Int32 x1, Int32 y1, Int32 x2, Int32 y2);
		void	PolyLine				(Int32 cnt, GE_POINT2D *points);
		void	FillPolygon			(Int32 cnt, GE_POINT2D *points);
		void	Rect						(Int32 x1, Int32 y1, Int32 x2, Int32 y2);
		void	FillRect				(Int32 x1, Int32 y1, Int32 x2, Int32 y2);
		void	Arc							(Int32 x1, Int32 y1, Int32 x2, Int32 y2, GE_CM_ARCSEGMENT seg);
		void	FillArc					(Int32 x1, Int32 y1, Int32 x2, Int32 y2, GE_CM_ARCSEGMENT seg);
		void	Ellipse					(Int32 x1, Int32 y1, Int32 x2, Int32 y2);
		void	FillEllipse			(Int32 x1, Int32 y1, Int32 x2, Int32 y2);

		void	SetPixelRGBA		(Int32 x, Int32 y, Int32 r, Int32 g, Int32 b, Int32 a = 255);
		void	GetPixelRGBA		(Int32 x, Int32 y, Int32 *r, Int32 *g, Int32 *b, Int32 *a);

		void	TextAt					(Int32 x, Int32 y, const String &txt);
		Int32	GetTextWidth		(const String &txt);
		Int32	GetTextHeight		();
		Int32	GetTextAscent		();

		void	Blit						(Int32 dx, Int32 dy, const GeClipMap &s_dp, Int32 sx1, Int32 sy1, Int32 sx2, Int32 sy2, GE_CM_BLIT rop);

		void	SetClipRgn			(Int32 left, Int32 top, Int32 right, Int32 bottom);
		void	SetClipRgn			(GE_POINT2D *points, Int32 count, GE_CM_CLIPREGION mode);

		Bool	ClipPoint				(Int32 x, Int32 y);
		Int32	ClipArea				(Int32 x1, Int32 y1, Int32 x2, Int32 y2);

		Bool	SetFont( BaseContainer const *font_description, Float font_size = 0.0 );
		Float	GetFont( BaseContainer *font_description );
		static Bool	GetFontName( BaseContainer const *font_description, GeFontNameType type, String *dst );
		static Bool	GetFontDescription( String const &name, GeFontNameType type, BaseContainer *dst );
		static void	EnumerateFonts( BaseContainer *dst, GE_CM_FONTSORT sort_mode );
		static Bool	GetDefaultFont( GeFontDefaultType type, BaseContainer *font_description );
		static Bool	GetFontSize( BaseContainer const *font_description, GeFontSizeType type, Float *size );
		static Bool	SetFontSize( BaseContainer *font_description, GeFontSizeType type, Float size );
};

class iGeClipMap;

#endif

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#define LIB_CLIPMAP 		1000494

struct GeClipMapLib : public C4DLibrary
{
		GeClipMap*	(*Alloc)											();
		void				(*Free)												(GeClipMap *&data);

		IMAGERESULT	(iGeClipMap::*Init)						(Int32 w, Int32 h, Int32 bits);
		IMAGERESULT	(iGeClipMap::*InitWith)				(BaseBitmap *bm);
		IMAGERESULT	(iGeClipMap::*InitFrom)				(BaseBitmap *bm, BaseBitmap *alpha_channel);
		IMAGERESULT	(iGeClipMap::*InitFromFile)		(const Filename &name, Int32 frame, Bool *ismovie);
		void				(iGeClipMap::*Destroy)					();
		void				(iGeClipMap::*GetDim)					(Int32 *w, Int32 *h) const;
		BaseBitmap*	(iGeClipMap::*GetBitmap)				();
		void				(iGeClipMap::*BeginDraw)				();
		void				(iGeClipMap::*EndDraw)					();
		void				(iGeClipMap::*SetOffset)				(Int32 off_x, Int32 off_y);
		void				(iGeClipMap::*SetDrawMode)			(GE_CM_DRAWMODE mode, UInt32 par);
		void				(iGeClipMap::*SetColor)				(Int32 r, Int32 g, Int32 b, Int32 a);
		void				(iGeClipMap::*SetPixel)				(Int32 x, Int32 y);
		void				(iGeClipMap::*CMLine)				 	(Int32 x1, Int32 y1, Int32 x2, Int32 y2);
		void				(iGeClipMap::*PolyLine)        (Int32 cnt, GE_POINT2D *points);
		void				(iGeClipMap::*FillPolygon)			(Int32 cnt, GE_POINT2D *points);
		void				(iGeClipMap::*Rect)						(Int32 x1, Int32 y1, Int32 x2, Int32 y2);
		void				(iGeClipMap::*FillRect)				(Int32 x1, Int32 y1, Int32 x2, Int32 y2);
		void				(iGeClipMap::*Arc)							(Int32 x1, Int32 y1, Int32 x2, Int32 y2, GE_CM_ARCSEGMENT seg);
		void				(iGeClipMap::*FillArc)					(Int32 x1, Int32 y1, Int32 x2, Int32 y2, GE_CM_ARCSEGMENT seg);
		void				(iGeClipMap::*Ellipse)					(Int32 x1, Int32 y1, Int32 x2, Int32 y2);
		void				(iGeClipMap::*FillEllipse)			(Int32 x1, Int32 y1, Int32 x2, Int32 y2);
		void				(iGeClipMap::*SetPixelRGBA)		(Int32 x, Int32 y, Int32 r, Int32 g, Int32 b, Int32 a);
		void				(iGeClipMap::*GetPixelRGBA)		(Int32 x, Int32 y, Int32 *r, Int32 *g, Int32 *b, Int32 *a);
		void				(iGeClipMap::*TextAt)					(Int32 x, Int32 y, const String &txt);
		Int32				(iGeClipMap::*GetTextWidth)		(const String &txt);
		Int32				(iGeClipMap::*GetTextHeight)		();
		Int32				(iGeClipMap::*GetTextAscent)		();
		void				(iGeClipMap::*Blit)						(Int32 dx, Int32 dy, const iGeClipMap &s_dp, Int32 sx1, Int32 sy1, Int32 sx2, Int32 sy2, GE_CM_BLIT rop);
		void				(iGeClipMap::*SetClipRgn)			(Int32 left, Int32 top, Int32 right, Int32 bottom);
		void				(iGeClipMap::*SetClipRgn2)			(GE_POINT2D *points, Int32 count, GE_CM_CLIPREGION mode);
		Bool				(iGeClipMap::*ClipPoint)				(Int32 x, Int32 y);
		Int32				(iGeClipMap::*ClipArea)				(Int32 x1, Int32 y1, Int32 x2, Int32 y2);
		Int32				(iGeClipMap::*GetBw)						() const;
		Int32				(iGeClipMap::*GetBh)						() const;
		Bool				(iGeClipMap::*SetFont				  )( BaseContainer const *font_description, Float font_size );
		Float				(iGeClipMap::*GetFont				  )( BaseContainer *font_description );
		Bool				(*GetFontName									)( BaseContainer const *font_description, GeFontNameType type, String *dst );
		Bool				(*GetFontDescription					)( String const &name, GeFontNameType type, BaseContainer *dst );
		void				(*EnumerateFonts							)( BaseContainer *dst, GE_CM_FONTSORT sort_mode );
		Bool				(*GetDefaultFont							)( GeFontDefaultType type, BaseContainer *font_description );
		Bool				(*GetFontSize									)( BaseContainer const *font_description, GeFontSizeType type, Float *size );
		Bool				(*SetFontSize									)( BaseContainer *font_description, GeFontSizeType type, Float size );
		IMAGERESULT	(iGeClipMap::*InitWithIconData)(const IconData& iconData);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif
