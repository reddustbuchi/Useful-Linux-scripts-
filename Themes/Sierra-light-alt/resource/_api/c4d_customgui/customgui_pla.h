/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _CUSTOMGUI_PLA_H_
#define _CUSTOMGUI_PLA_H_

#ifdef _INTERNAL_PLA_
	#define _INTERNAL_BASECUSTOM_
#endif

#include "customgui_base.h"
#include "c4d_customguidata.h"
#include "c4d_basecontainer.h"
#include "c4d_customdatatype.h"
#include "lib_ca.h"

#define CUSTOMDATATYPE_PLA       100004811
#define CUSTOMDATATYPE_MT_TAG    100004838 // also defined in newman

class PLAData : public CustomDataType
{
private:
	PLAData();
	~PLAData();

public:
	void GetVariableTags(PointTag *&ptag, TangentTag *&htag);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

class mttag_data : public CustomDataType
{
private:
	mttag_data();
	~mttag_data();

public:
	GeListHead* GetLayerHead(void);
};


class mtlayer_data : public CustomDataType
{
private:
	mtlayer_data();
	~mtlayer_data();

public:
	Bool        IsAnimationLayer(void);
	GeListHead* GetAnimationHead(void);
	GeListHead* GetClipHead(void);
};

class iPLAData;
class MT_TagData;
class MT_LayerData;

Bool AnimateNLA(BaseDocument *doc, BaseObject *op, const BaseTime &time, ANIMATEFLAGS flags);

struct PLALib : public BaseCustomGuiLib
{
	void		    (iPLAData::*GetVariableTags )(PointTag *&ptag, TangentTag *&htag);
	GeListHead* (*xGetLayerHead)    (MT_TagData*);
	Bool        (*xIsAnimationLayer)(MT_LayerData*);
	GeListHead*	(*xGetAnimationHead)(MT_LayerData*);
	GeListHead*	(*xGetClipHead)(MT_LayerData*);

	Bool        (*xAnimateNLA      )(BaseDocument *doc, BaseObject *op, const BaseTime &time, ANIMATEFLAGS flags);
};


// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif
