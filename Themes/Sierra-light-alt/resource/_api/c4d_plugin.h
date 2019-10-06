/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __c4d_plugin_h__
#define __c4d_plugin_h__

#include "ge_math.h"

#define C4DPL_VERSION								 0x0005
#define C4DPL_SINGLEPRECISION_PLUGIN 0x1000

// error
#define C4DPL_ERROR					-1
#define C4DPL_ERROR_TYPE		-2
#define C4DPL_ERROR_VERSION	-3
#define C4DPL_ERROR_OS			-4
#define C4DPL_ERROR_MEM			-5

// action
#define C4DPL_INIT_SYS		 1
#define C4DPL_INIT				 2
#define C4DPL_END					 3
#define C4DPL_INIT_VERSION 4
#define C4DPL_MESSAGE			 6

#define C4DMSG_PRIORITY 0
#define C4DPL_BUILDMENU 1001188

// priorities
#define C4DPL_INIT_PRIORITY_XTENSIONS			 20000
#define C4DPL_INIT_PRIORITY_OBJECTS				 19000
#define C4DPL_INIT_PRIORITY_MODELING			 18500
#define C4DPL_INIT_PRIORITY_SHADER				 18000
#define C4DPL_INIT_PRIORITY_ADVANCEDRENDER 17000
#define C4DPL_INIT_PRIORITY_MOCCA					 15000
#define C4DPL_INIT_PRIORITY_NEWMAN				 12000
#define C4DPL_INIT_PRIORITY_SLA						 850

#define C4DPL_INIT_PRIORITY_MODULES 10000
#define C4DPL_INIT_PRIORITY_PLUGINS 0

// messages
#define C4DPL_STARTACTIVITY				 1000
#define C4DPL_ENDACTIVITY					 1001
#define C4DPL_COMMANDLINEARGS			 1002
#define C4DPL_ENDPLUGINACTIVITY0	 1026848
#define C4DPL_ENDPLUGINACTIVITY1	 200000272
#define C4DPL_ENDPLUGINACTIVITY2	 200000276
#define C4DPL_CHANGEDSECURITYTOKEN 300002143
#define C4DPL_SHUTDOWNTHREADS			 300002148
#define C4DPL_LAYOUTCHANGED				 300002164
#define C4DPL_RELOADPYTHONPLUGINS	 1026963
struct C4DPL_CommandLineArgs
{
	Int32					argc;
	char**				argv;
	Int32					argc_w;	// only available on Windows - unicode encoding of the parameters
	UInt16**			argv_w;
	const char*		orig;
	const UInt16* orig_w;
};
#define C4DPL_EDITIMAGE	1003
struct C4DPL_EditImage
{
	class Filename * imagefn;
	Bool return_processed;
};

#define C4DPL_ENDPROGRAM	 1001084
#define C4DPL_DEVICECHANGE 1001190
struct C4DPL_DeviceChange
{
	class String* name;
	Bool eject;
};

#define C4DPL_NETWORK_CHANGE	310002007
#define C4DPL_SYSTEM_SLEEP		310002008
#define C4DPL_SYSTEM_WAKE			310002009
#define C4DPL_PROGRAM_STARTED	450000215

#define C4DPL_REGISTERPYPLUG	1026805		//private
#define C4DPL_NETRENDERRESULT 310002006	//private
struct C4DPL_NetRenderResult
{
	Int32 result;
	void* node;
};

// the interface
Bool PluginStart(void);
void PluginEnd(void);
Bool PluginMessage(Int32 id, void* data);

#define SetPluginPriority(data, i) { *((Int32*)(data)) = i; }

#endif
