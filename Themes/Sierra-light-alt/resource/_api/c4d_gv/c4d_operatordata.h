/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DOPERATORDATA_H
#define __C4DOPERATORDATA_H

////////////////////////////////

#include "c4d_nodedata.h"
#include "c4d_graphview.h"

////////////////////////////////

class GvOperatorData : public NodeData
{
	public:
		////inherited from NodeData////
		virtual Bool Init(GeListNode *node);
		//virtual void Free(GeListNode *node);
		//virtual Bool Read(GeListNode *node, HyperFile *hf, Int32 level);
		//virtual Bool Write(GeListNode *node, HyperFile *hf);
		//virtual Bool Message(GeListNode *node, Int32 type, void *data);
		//virtual Bool CopyTo(NodeData *dest, GeListNode *snode, GeListNode *dnode, COPYFLAGS flags, AliasTrans *trn);
		//static NodeData *Alloc(void) { return NewObjClear(MyNodeData); }
		virtual Bool GetDDescription(GeListNode *node, Description *description, DESCFLAGS_DESC &flags);
		virtual Bool GetDParameter(GeListNode *node, const DescID &id,GeData &t_data,DESCFLAGS_GET &flags);
		virtual Bool GetDEnabling(GeListNode *node, const DescID &id,const GeData &t_data,DESCFLAGS_ENABLE flags,const BaseContainer *itemdesc);
		virtual Bool SetDParameter(GeListNode *node, const DescID &id,const GeData &t_data,DESCFLAGS_SET &flags);
		////inherited from NodeData////

		virtual void					iGetPortList(GvNode *bn, GvPortIO port, GvPortList &portlist);
		virtual Bool				  iGetPortDescription(GvNode *bn, GvPortIO port, Int32 id, GvPortDescription *pd);
		virtual Bool					iCreateOperator(GvNode *bn);

		virtual Bool					CreatePortDescriptionCache(GvNode *bn, Bool lock_only = false);
		virtual void					FreePortDescriptionCache(GvNode *bn);

		virtual const String  GetDetailedText(GvNode *bn);
		virtual const String	GetText(GvNode *bn);
		virtual const String	GetTitle(GvNode *bn);
		virtual BaseBitmap*		GetPortIcon(GvNode *bn, Int32 id, GvLayoutType layout_type);
		virtual void					GetBodySize(GvNode *bn, Int32 *width, Int32 *height);
		virtual const Vector	GetBodyColor(GvNode *bn);
		virtual void					EditorDraw(GvNode *bn, GvNodeGUI* gui, GeUserArea *da, Int32 x1, Int32 y1, Int32 x2, Int32 y2);
		virtual Bool				  GetOperatorDescription(GvNode *bn, GvOperatorDescription *od);
		virtual Bool					QueryCalculation(GvNode *bn, GvQuery *query);
		virtual Bool					InitCalculation(GvNode *bn, GvCalc *calc, GvRun *run);
		virtual void					FreeCalculation(GvNode *bn, GvCalc *calc);
		virtual Bool					Calculate(GvNode *bn, GvPort *port, GvRun *run, GvCalc *calc);
		virtual Bool					AddToCalculationTable(GvNode *bn, GvRun *run);
		virtual Bool					SetRecalculate(GvNode *bn, GvPort *port, GvRun *run, Bool force_set = false);
		virtual Bool					SetData(GvNode *bn, GvDataType type, void *data, GvOpSetDataMode mode = GV_OP_SET);
		virtual Bool					IsSetDataAllowed(GvNode *bn, GvDataType type, void *data, GvOpSetDataMode mode = GV_OP_SET);
		virtual Int32					FillPortMenu(GvNode *bn, BaseContainer &menu, Int32 port_id, Int32 first_menu_id);
		virtual Bool					PortMenuCommand(GvNode *bn, Int32 menu_id, Int32 port_id, Int32 mx, Int32 my);
		virtual Int32					FillOperatorMenu(GvNode *bn, BaseContainer &menu, Int32 first_menu_id);
		virtual Bool					OperatorMenuCommand(GvNode *bn, Int32 menu_id, Int32 mx, Int32 my);
		virtual Int32					FillPortsMenu(GvNode *bn, BaseContainer &names, BaseContainer &ids, GvValueID value_type, GvPortIO port, Int32 first_menu_id);
		virtual Bool					BodyMessage(GvNode* bn, GvNodeGUI *gui, Int32 x, Int32 y, Int32 chn, Int32 qua, const BaseContainer &msg);
		virtual Bool					EditSettings(GvNode* bn, GvNodeGUI *gui);
		virtual const String  GetErrorString(GvNode *bn, Int32 error);
		virtual Bool					SceneDraw(GvNode *bn, BaseDraw *bd, BaseDrawHelp *bh, BaseThread *bt, Int32 flags, void *data, UInt32 counter);

		virtual	Int32					GetMainID(GvNode *bn, GvPortIO io, const DescID &desc_id);
		virtual const DescID	GetDescID(GvNode *bn, GvPortIO io, Int32 main_id);
};

////////////////////////////////

Bool GvRegisterOperatorPlugin(GvOperatorID id, const String &str, Int32 info, DataAllocator *at, const String &description, Int32 disklevel, GvOpClassID op_class, GvOpGroupID op_group, Int32 op_owner, BaseBitmap *icon);

////////////////////////////////

#endif //__C4DOPERATORDATA_H

////////////////////////////////
