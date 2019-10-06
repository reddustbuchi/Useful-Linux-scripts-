/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4D_TOOLPLUGIN_H
#define __C4D_TOOLPLUGIN_H

#include "ge_math.h"
#include "c4d_tooldata.h"
#include "c4d_baseplugin.h"

struct TOOLPLUGIN : public STATICPLUGIN
{
	String			*help;
	BaseBitmap	*command_icon;

	Bool				(ToolData::*InitTool			)(BaseDocument *doc, BaseContainer &data, BaseThread *bt);
	void				(ToolData::*FreeTool			)(BaseDocument *doc, BaseContainer &data);

	Bool				(ToolData::*MouseInput		)(BaseDocument *doc, BaseContainer &data, BaseDraw *bd, EditorWindow *win, const BaseContainer &msg);
	Int32				(ToolData::*GetState			)(BaseDocument *doc);
	Bool        (ToolData::*GetCursorInfo )(BaseDocument *doc, BaseContainer &data, BaseDraw *bd, Float x, Float y, BaseContainer &bc);
	TOOLDRAW    (ToolData::*Draw          )(BaseDocument *doc, BaseContainer &data, BaseDraw *bd, BaseDrawHelp *bh, BaseThread *bt, TOOLDRAWFLAGS flags);

	CDialog*		(ToolData::*AllocDialog   )(BaseContainer *bc, CDialog *cd_parent, Int32 dlg_id);
	void				(ToolData::*FreeDialog    )(CDialog *cd);

	Bool				(ToolData::*InitDisplayControl)(BaseDocument *doc, BaseContainer &data, BaseDraw *bd, const AtomArray *active);
	void				(ToolData::*FreeDisplayControl)(void);
	Bool				(ToolData::*DisplayControlEx	)(BaseDocument *doc, BaseObject *op, BaseObject *chainstart, BaseDraw *bd, BaseDrawHelp *bh, ControlDisplayStruct &cds);

	Bool				(ToolData::*KeyboardInput	)(BaseDocument *doc, BaseContainer &data, BaseDraw *bd, EditorWindow *win, const BaseContainer &msg);
	Bool				(ToolData::*GetDDescription)(BaseDocument *doc, BaseContainer &data, Description *description,DESCFLAGS_DESC &flags);
	Bool				(ToolData::*GetDParameter )(BaseDocument *doc, BaseContainer &data, const DescID &id,GeData &t_data,DESCFLAGS_GET &flags);
	Bool				(ToolData::*GetDEnabling	)(BaseDocument *doc, BaseContainer &data, const DescID &id,const GeData &t_data,DESCFLAGS_ENABLE flags,const BaseContainer *itemdesc);
	Bool				(ToolData::*SetDParameter	)(BaseDocument *doc, BaseContainer &data, const DescID &id,const GeData &t_data,DESCFLAGS_SET &flags);
	Bool				(ToolData::*Message				)(BaseDocument *doc, BaseContainer &data, Int32 type, void *t_data);
	void				(ToolData::*InitDefaultSettings)(BaseDocument *pDoc, BaseContainer &data);
	Bool				(ToolData::*DoCommand			)(ModelingCommandData &mdat);
	const String (ToolData::*GetResourceSymbol)();

	Bool				(ToolData::*DisplayControl		)(BaseDocument *doc, BaseObject *op, BaseObject *chainstart, BaseDraw *bd, BaseDrawHelp *bh, ControlDisplayStruct &cds);

	void*	reserved[(32-21)*C4DPL_MEMBERMULTIPLIER-2];
};

#endif
