/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _LIB_FILTERTREE_H_
#define _LIB_FILTERTREE_H_

#define ID_LIB_FILTERTREE				200000124

enum ManagerType
{
	SB_MANAGER = 1,
	TL_MANAGER = 2,
	MAT_MANAGER = 3,

	DUM_MANAGER
};

enum ManagerNum
{
	MANAGER_NOTOK = -1,
	MANAGER_1 = 0,
	MANAGER_2 = 1,
	MANAGER_3 = 2,
	MANAGER_4 = 3,

	DUM_MANNI
};

class ManagerInfo
{
		friend void iUpdateManagerInfo(ManagerInfo *minfo);

	private:
		ManagerType type;
		ManagerNum  num;
		NBIT				foldbit;

	private:
		Int32				imanagernum; // cached id

		void UpdateManagerInfo();

	public:
		ManagerInfo() : type(DUM_MANAGER), num(MANAGER_NOTOK), foldbit(NBIT_0) { UpdateManagerInfo(); }
		ManagerInfo(ManagerType t_type, ManagerNum t_num, NBIT t_foldbit) : type(t_type), num(t_num), foldbit(t_foldbit) { UpdateManagerInfo(); }

		ManagerType GetManagerType() const { return type; }
		ManagerNum GetManagerNum() const { return num; }
		NBIT GetFoldBit() const { return foldbit; }
		Int32 GetMNum() const { return imanagernum; }

		void SetManagerType(ManagerType t_type) { if (t_type==type) return; type = t_type; UpdateManagerInfo(); }
		void SetManagerNum(ManagerNum t_num) { if (t_num==num) return; num = t_num; UpdateManagerInfo(); }
		void SetFoldBit(NBIT t_bit) { if (t_bit==foldbit) return; foldbit = t_bit; UpdateManagerInfo(); }
};

Bool ShowObjectArt(BaseDocument *doc, Int32 art, const ManagerInfo &minfo);
Bool IsObjectHidden(BaseDocument *doc, BaseList2D *bl, const ManagerInfo &minfo);
Bool IsObjectSearchable(BaseDocument *doc, BaseList2D *bl, const ManagerInfo &minfo);
Bool IsLayerHidden(BaseDocument *doc, LayerObject *op, const ManagerInfo &minfo);
Bool SetLayerHidden(BaseDocument *doc, LayerObject *op, const ManagerInfo &minfo, Bool hide);
Bool BuildFilterList(BaseDocument *doc);

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

struct FilterTreeLib : public C4DLibrary
{
	Bool					(*ShowObjectArt				)(BaseDocument *doc, Int32 art,       const ManagerInfo &minfo);
	Bool					(*IsObjectHidden			)(BaseDocument *doc, BaseList2D *bl, const ManagerInfo &minfo);
	Bool					(*IsObjectSearchable	)(BaseDocument *doc, BaseList2D *bl, const ManagerInfo &minfo);
	Bool					(*IsLayerHidden				)(BaseDocument *doc, LayerObject *op, const ManagerInfo &minfo);
	Bool					(*SetLayerHidden			)(BaseDocument *doc, LayerObject *op, const ManagerInfo &minfo, Bool hide);
	Bool					(*BuildFilterList			)(BaseDocument *doc);
	void					(*UpdateManagerInfo		)(ManagerInfo *minfo);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF


#endif // _LIB_FILTERTREE_H_
