/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _C4D_BASESNAPPLUGIN_H_
#define _C4D_BASESNAPPLUGIN_H_

#include "c4d_snapdata.h"
#include "c4d_baseplugin.h"
#include "c4d_library.h"

//--------------------------------------------------------
//	--- Internal Stuff

struct SNAPPLUGIN : public STATICPLUGIN
{
	String					*help;
	BaseBitmap			*command_icon;
	Int32						parent_mode;
	SNAPPRIORITY		priority;

	SnapData*				(*Allocator										)(void);

	Bool						(SnapData::*Init							)();
	void						(SnapData::*Free							)();
	Bool						(SnapData::*InitSnap					)(const SnapStruct &ss);
	Bool						(SnapData::*Snap							)(const Vector &p, const SnapStruct &ss, SnapPoint &result);
	Bool						(SnapData::*Intersect					)(const Vector &p, const Vector &n, Bool plane, const SnapStruct &ss, SnapPoint &result);
	void						(SnapData::*FreeSnap					)(const SnapStruct &ss);
	Bool						(SnapData::*Draw							)(const SnapStruct &ss, BaseDocument *doc, BaseDraw *bd, BaseDrawHelp *bh, BaseThread *bt);
	Bool						(SnapData::*GetCursorInfo			)(const SnapStruct &ss, BaseDocument *doc, BaseDraw *bd, Float x, Float y, BaseContainer &result);
	Bool						(SnapData::*MouseInput				)(const SnapStruct &ss, BaseDocument *doc, BaseDraw *bd, EditorWindow *win, const BaseContainer &msg);
	Bool						(SnapData::*KeyboardInput			)(const SnapStruct &ss, BaseDocument *doc, BaseDraw *bd, EditorWindow *win, const BaseContainer &msg);

	void*	reserved[((32-10)*C4DPL_MEMBERMULTIPLIER) - 5];
};

class iSnapCore;

struct SnapCoreLib : public C4DLibrary
{
	Bool						(iSnapCore::*Init							)(BaseDocument *doc, BaseDraw *bd, AtomArray *exclude);
	Bool						(iSnapCore::*Update						)();
	Bool						(iSnapCore::*Snap							)(const Vector &p, SnapResult &result, SNAPFLAGS flags);
	Bool						(iSnapCore::*Intersect				)(const Vector &p, const Vector &n, Bool plane, SnapResult &result, SNAPFLAGS flags);
	BaseObject*			(iSnapCore::*AddInferred			)(BaseDocument *doc, const Matrix &mat, INFERREDGUIDETYPE type);
	Bool						(iSnapCore::*FlushInferred		)();
	void						(iSnapCore::*SetToolObject		)(BaseObject *op);

	iSnapCore*			(*Alloc												)();
	void						(*Free												)(iSnapCore *&p);

	void*	reserved1[((32-7)*C4DPL_MEMBERMULTIPLIER) - 2];

	Bool						(*GeRegisterSnapModePlugin		)(Int32 id, const String &str, BaseBitmap *icon, const String &help, Int32 parent, SNAPPLUGIN &np, Int32 flags);

	Bool						(*IsSnapEnabled								)(Int32 mode, BaseDocument *doc);
	void						(*EnableSnap									)(Int32 mode, Bool state, BaseDocument *doc);
	BaseContainer		(*GetSnapSettings							)(BaseDocument *doc, Int32 snapmode);
	void						(*SetSnapSettings							)(BaseDocument *doc, const BaseContainer &bc, Int32 snapmode);

	Bool						(*IsQuantizeEnabled						)(BaseDocument *doc);
	Float						(*GetQuantizeStep							)(BaseDocument *doc, BaseDraw *bd, Int32 quantize_mode);
	void						(*SetQuantizeStep							)(BaseDocument *doc, BaseDraw *bd, Int32 quantize_mode, Float val);

	void*	reserved2[(32*C4DPL_MEMBERMULTIPLIER) - 8];

	Bool						(*GetConstructionPlane				)(BaseDraw *bd, Matrix *mg, Vector *scale, BaseObject **op);
	BaseObject*			(*GetWorkplaneObject					)(BaseDocument *doc);

	Bool						(*GetWorkplaneLock						)(BaseDocument *doc);
	void						(*SetWorkplaneLock						)(BaseDraw *bd, Bool locked);
	Matrix					(*GetWorkplaneMatrix					)(BaseDocument*doc, BaseDraw *bd);

	void*	reserved3[(32*C4DPL_MEMBERMULTIPLIER) - 5];
};

//	--- Internal Stuff
//--------------------------------------------------------

#endif
