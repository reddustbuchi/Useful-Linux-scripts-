// MatrixExtrudeDialolg.h :  Interface definition of class SmoothShiftToolDialog
//
//////////////////////////////////////////////////////////////////////

#ifndef DESCRIPTIONDIALOG_H
#define DESCRIPTIONDIALOG_H

#ifdef __API_INTERN__
abc def xyz
#endif

class DescriptionToolData : public ToolData
{
	INSTANCEOF(DescriptionToolData, ToolData)

protected:
	Bool	firstaction;
	Int32	last_dirty;

public:
	virtual void InitDefaultSettings(BaseDocument* pDoc, BaseContainer& data);

	virtual Bool GetDDescription(BaseDocument* doc, BaseContainer& data, Description* description, DESCFLAGS_DESC& flags);
	virtual Bool GetDEnabling(BaseDocument* doc, BaseContainer& data, const DescID& id, const GeData& t_data, DESCFLAGS_ENABLE flags, const BaseContainer* itemdesc);
	virtual Bool Message(BaseDocument* doc, BaseContainer& data, Int32 type, void* t_data);

	virtual Int32	GetToolPluginId() = 0;
	virtual const String GetResourceSymbol() = 0;

	virtual Bool InitTool(BaseDocument* doc, BaseContainer& data, BaseThread* bt);
	virtual void FreeTool(BaseDocument* doc, BaseContainer& data);

	Bool InteractiveModeling_Restart(BaseDocument* doc);


	//		virtual Bool			DoCommand(ModelingCommandData &mdat);
	//
	//		virtual Bool			MouseInput(BaseDocument *doc, BaseContainer &data, BaseDraw *bd, EditorWindow *win, const BaseContainer &msg);
	//		virtual Bool			KeyboardInput(BaseDocument *doc, BaseContainer &data, BaseDraw *bd, EditorWindow *win, const BaseContainer &msg);
	//
	//		virtual Int32			GetState(BaseDocument *doc);
	//		virtual Bool      GetCursorInfo(BaseDocument *doc, BaseContainer &data, BaseDraw *bd, Float x, Float y, BaseContainer &bc);
	//		virtual TOOLDRAW  Draw(BaseDocument *doc, BaseContainer &data, BaseDraw *bd, BaseDrawHelp *bh, BaseThread *bt,TOOLDRAWFLAGS flags);
	//
	//		virtual Bool			InitDisplayControl(BaseDocument *doc, BaseContainer &data, BaseDraw *bd, const AtomArray *active);
	//		virtual void			FreeDisplayControl(void);
	//		virtual Bool			DisplayControl(BaseDocument *doc, BaseObject *op, BaseObject *chainstart, BaseDraw *bd, BaseDrawHelp *bh, ControlDisplayStruct &cds);
	//
	//		virtual Bool			GetDParameter(BaseDocument *doc, BaseContainer &data, const DescID &id,GeData &t_data,DESCFLAGS_GET &flags);
	//		virtual Bool			GetDEnabling(BaseDocument *doc, BaseContainer &data, const DescID &id,const GeData &t_data,DESCFLAGS_ENABLE flags,const BaseContainer *itemdesc);
	//		virtual Bool			SetDParameter(BaseDocument *doc, BaseContainer &data, const DescID &id,const GeData &t_data,DESCFLAGS_SET &flags);
};


#endif
