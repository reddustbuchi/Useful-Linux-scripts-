/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4D_SCENEHOOKPLUGIN_H
#define __C4D_SCENEHOOKPLUGIN_H

#include "ge_math.h"
#include "c4d_scenehookdata.h"
#include "c4d_nodeplugin.h"

struct SCENEHOOKPLUGIN : public NODEPLUGIN
{
	public:
		Int32	draw_priority;

		Bool	(SceneHookData::*MouseInput			)(BaseSceneHook *node, BaseDocument *doc, BaseDraw *bd, EditorWindow *win, const BaseContainer &msg);
		Bool  (SceneHookData::*GetCursorInfo	)(BaseSceneHook *node, BaseDocument *doc, BaseDraw *bd, Float x, Float y, BaseContainer &bc);
		Bool  (SceneHookData::*Draw						)(BaseSceneHook *node, BaseDocument *doc, BaseDraw *bd, BaseDrawHelp *bh, BaseThread *bt, SCENEHOOKDRAW flags);

		Bool	(SceneHookData::*AddToExecution )(BaseSceneHook *node, PriorityList *list);
		EXECUTIONRESULT (SceneHookData::*InitSceneHook	)(BaseSceneHook *node, BaseDocument *doc, BaseThread *bt);
		void	(SceneHookData::*FreeSceneHook	)(BaseSceneHook *node, BaseDocument *doc);
		EXECUTIONRESULT (SceneHookData::*Execute				)(BaseSceneHook *node, BaseDocument *doc, BaseThread *bt, Int32 priority, EXECUTIONFLAGS flags);

		Bool	(SceneHookData::*KeyboardInput	)(BaseSceneHook *node, BaseDocument *doc, BaseDraw *bd, EditorWindow *win, const BaseContainer &msg);

		Bool	(SceneHookData::*DisplayControlEx)(BaseDocument *doc, BaseObject *op, BaseObject *chainstart, BaseDraw *bd, BaseDrawHelp *bh, ControlDisplayStruct &cds);
		Bool	(SceneHookData::*InitDisplayControl)(BaseSceneHook *node, BaseDocument* doc, BaseDraw* bd, const AtomArray* active);
		void	(SceneHookData::*FreeDisplayControl)(void);

		Bool	(SceneHookData::*DisplayControl)(BaseDocument *doc, BaseObject *op, BaseObject *chainstart, BaseDraw *bd, BaseDrawHelp *bh, ControlDisplayStruct &cds);

		void*	reserved[(32-12)*C4DPL_MEMBERMULTIPLIER-1];
};

#endif
