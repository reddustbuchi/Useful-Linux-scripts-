/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _LIB_SN_H_
#define _LIB_SN_H_

#include "c4d_library.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"

#define SN_OKAY					0		// >=0 means okay
#define SN_WRONGNUMBER	-1
#define SN_EXPIRED			-2
#define SN_EXPIRE_14		-100
#define SN_NET					-4

#define SNFLAG_OWN			1	// use own sn scheme
#define SNFLAG_PRIV			2 // don't use
#define SNFLAG_CLIPID		4 // hook provides clipid

// public stuff
struct SNHook
{
	void					*thisptr;
	Int32					flags;

	Int32					(*SN_Check)(SNHook *snhook,const String &c4dsn,const String &sn,Int32 regdate,Int32 curdate);
	const String&	(*SN_GetTitle)(SNHook *snhook);
	const Char*		(*SN_GetClipID)(SNHook *snhook);
};

// a class for convenience, DO NOT STORE STATIC !!!
class SNHookClass
{
		SNHook hook;

	public:

		SNHookClass();

		Bool Register(Int32 id,Int32 flags);

		virtual Int32 SNCheck(const String &c4dsn,const String &sn,Int32 regdate,Int32 curdate);
		virtual const String& GetTitle();
		virtual const Char* GetClipID();
};

// public class

Bool SN_Register(Int32 id,SNHook *snhook);
SNHook *SN_FindHook(Int32 id);

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#define LIBRARY_SN	200000008

struct SNLib : public C4DLibrary
{
	Bool    (*SN_Register   )(Int32 id,SNHook *snhook);
	SNHook*	(*SN_FindHook		)(Int32 id);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif
