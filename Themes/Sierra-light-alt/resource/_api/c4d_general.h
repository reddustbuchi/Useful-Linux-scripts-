/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DGENERAL_H
#define __C4DGENERAL_H

#ifdef __API_INTERN__
#include "ge_math.h"
#include "operatingsystem.h"

class String;

Bool GeRegisterPlugin(PLUGINTYPE type, Int32 id, const String& str, void* data, Int32 datasize);
Bool RenameDialog(String* str);

#define POPUPEDITTEXTCALLBACK_TEXTCHANGED	1
#define POPUPEDITTEXTCALLBACK_CLOSED			2
#define POPUPEDITTEXTCALLBACK_CANCELED		3
#define POPUPEDITTEXTCALLBACK_CURSOR_UP		4
#define POPUPEDITTEXTCALLBACK_CURSOR_DOWN	5

typedef void PopupEditTextCallback (Int32 mode, const String &text, void* userdata);
Bool PopupEditText(Int32 screenx, Int32 screeny, Int32 width, Int32 height, const String& changeme, Int32 flags, PopupEditTextCallback* func, void* userdata);
#else

#include "c4d_string.h"
#include "operatingsystem.h"
#include "c4d_baselist.h"
#include "c4d_misc.h"

class Filename;
class GeDialog;
class GeUserArea;
class GeListHead;
class BaseList2D;

#define NEWPARSERERROR_BADSTRING		(1 << 0)
#define NEWPARSERERROR_BADEXECUTION	(1 << 1)
#define NEWPARSERERROR_MEMORYERROR	(1 << 2)
#define NEWPARSERERROR_NUMBERERROR	(1 << 3)

#define UNIT_NONE	0
#define UNIT_KM		1
#define UNIT_M		2
#define UNIT_CM		3
#define UNIT_MM		4
#define UNIT_UM		5
#define UNIT_NM		6
#define UNIT_MILE	7
#define UNIT_YARD	8
#define UNIT_FEET	9
#define UNIT_INCH	10

#define ANGLE_DEG	0
#define ANGLE_RAD 1

enum Result
{
	RES_FALSE	 =0,	// function result not ok
	RES_TRUE	 =1,	// function result ok
	RES_MEM_ERR=2,	// memory error
	RES_STOP	 =3,	// stop execution (e.g. user break) but no mem error

	RES_DUM
} ENUM_END_LIST(Result);

class ParserCache
{
private:
	ParserCache();
	~ParserCache(void);

public:
	Bool CopyTo(ParserCache* dest);

	static ParserCache* Alloc(void);
	static void Free(ParserCache*& p);
};

class Parser
{
private:
	Parser();
	~Parser();

public:
	Bool Eval(const String& str, Int32* error, Float* res, Int32 unit = UNIT_NONE, Int32 angletype = ANGLE_DEG, Int32 basis = 10);
	Bool EvalLong(const String& str, Int32* error, Int32* res, Int32 unit, Int32 basis);

	static Parser* Alloc(void);
	static void Free(Parser*& pr);

	Bool AddVar(const String& str, Float* value, Bool case_sensitive = false);
	Bool RemoveVar(const String& s, Bool case_sensitive = false);
	Bool RemoveAllVars(void);
	void GetParserData(ParserCache* p);

	Bool Init(const String& s, Int32* error, Int32 unit = UNIT_NONE, Int32 angle_unit = ANGLE_DEG, Int32 base = 10);
	Bool ReEval(Float* result, Int32* error);
	Bool Calculate(const ParserCache* pdat, Float* result, Int32* error);

	Bool AddVarLong(const String& str, Int32* value, Bool case_sensitive = false);
	Bool ReEvalLong(Int32* result, Int32* error);
	Bool CalculateLong(const ParserCache* pdat, Int32* result, Int32* error);

	Bool Reset(ParserCache* p = nullptr);
};

struct SerialInfo
{
	String nr, name, organization, street, city, country;
};

void GeGetSerialInfo(SERIALINFO type, SerialInfo* si);
VERSIONTYPE GeGetVersionType(void);
inline Bool IsNet() { VERSIONTYPE t = GeGetVersionType(); return t == VERSIONTYPE_NET_CLIENT || t == VERSIONTYPE_NET_SERVER_3 || t == VERSIONTYPE_NET_SERVER_UNLIMITED; }
inline Bool IsServer() { VERSIONTYPE t = GeGetVersionType(); return t == VERSIONTYPE_NET_SERVER_3 || t == VERSIONTYPE_NET_SERVER_UNLIMITED; }
inline Bool IsClient() { VERSIONTYPE t = GeGetVersionType(); return t == VERSIONTYPE_NET_CLIENT; }
SYSTEMINFO GeGetSystemInfo(void);
void GeShowMouse(Int32 v);
Bool GeGetScreenDimensions(Int32 x, Int32 y, Bool whole_screen, Int32* sx1, Int32* sy1, Int32* sx2, Int32* sy2);
inline Int32 GeGetTimer(void) { return C4DOS.Ge->GetTimer(); }
inline Float64 GeGetMilliSeconds(void) { return C4DOS.Ge->GeGetMilliSeconds(); }
String GeGetLineEnd(void);
Int32 GeGetDefaultFPS(void);
UInt32 GeGetCinemaInfo(CINEMAINFO info);
GEMB_R GeOutString(const String& str, GEMB flags);
OPERATINGSYSTEM GeGetCurrentOS(void);
BYTEORDER GeGetByteOrder(void);
void GeGetGray(Int32* r, Int32* g, Int32* b);
Bool GeChooseColor(Vector* col, Int32 flags);
Bool GeOpenHTML(const String& webaddress);
Bool GeChooseFont(BaseContainer* bc);
Bool GeRegisterPlugin(PLUGINTYPE type, Int32 id, const String& str, void* data, Int32 datasize);
void GePrint(const String& str);
void GeConsoleOut(const String& str);
Bool GeGetMovieInfo(const Filename& fn, Int32* frames, Float* fps);
Bool RenameDialog(String* str);
inline Int32 GetC4DVersion(void) { return C4DOS.version; }
String GeGetDegreeChar();
String GeGetPercentChar();

inline void lSwap (void* adr, Int cnt = 1) { C4DOS.Ge->lSwap(adr, cnt); }
inline void wSwap (void* adr, Int cnt = 1) { C4DOS.Ge->wSwap(adr, cnt); }
inline void lIntel(void* adr, Int cnt = 1) { C4DOS.Ge->lIntel(adr, cnt); }
inline void wIntel(void* adr, Int cnt = 1) { C4DOS.Ge->wIntel(adr, cnt); }
inline void lMotor(void* adr, Int cnt = 1) { C4DOS.Ge->lMotor(adr, cnt); }
inline void wMotor(void* adr, Int cnt = 1) { C4DOS.Ge->wMotor(adr, cnt); }
inline void llSwap (void* adr, Int cnt = 1) { C4DOS.Ge->llSwap(adr, cnt); }
inline void llIntel(void* adr, Int cnt = 1) { C4DOS.Ge->llIntel(adr, cnt); }
inline void llMotor(void* adr, Int cnt = 1) { C4DOS.Ge->llMotor(adr, cnt); }

inline void vlSwap (void* adr, Int32 cnt = 1)
{
#ifdef __C4D_64BIT
	C4DOS.Ge->llSwap(adr, cnt);
#else
	C4DOS.Ge->lSwap(adr, cnt);
#endif
}

inline void vlIntel(void* adr, Int32 cnt = 1)
{
#ifdef __C4D_64BIT
	C4DOS.Ge->llIntel(adr, cnt);
#else
	C4DOS.Ge->lIntel(adr, cnt);
#endif
}

inline void vlMotor(void* adr, Int32 cnt = 1)
{
#ifdef __C4D_64BIT
	C4DOS.Ge->llMotor(adr, cnt);
#else
	C4DOS.Ge->lMotor(adr, cnt);
#endif
}

void GeAddBackgroundHandler(BackgroundHandler* handler, void* tdata, Int32 typeclass, Int32 priority);
Bool GeRemoveBackgroundHandler(void* tdata, Int32 typeclass);
void GeStopBackgroundThreads(Int32 typeclass, BACKGROUNDHANDLERFLAGS flags);
Bool GeCheckBackgroundThreadsRunning(Int32 typeclass, Bool all);
void GeProcessBackgroundThreads(Int32 typeclass);

void SetMousePointer(Int32);
Bool ShowBitmap(const Filename& fn);
Bool ShowBitmap(BaseBitmap* bm);
void StopAllThreads(void);
Bool ShutdownThreads(Bool shutdown);

void StatusClear(void);
void StatusSetSpin(void);
void StatusSetBar(Int32 p);
void StatusSetText(const String& str);

void StatusNetClear(void);
void StatusSetNetLoad(STATUSNETSTATE status);
void StatusSetNetBar(Int32 p, const GeData& dat);
void StatusSetNetText(const String& str);

void SpecialEventAdd(Int32 messageid, UInt p1 = 0, UInt p2 = 0);
void EventAdd(EVENT eventflag = EVENT_0);
Bool GeSyncMessage(Int32 messageid, Int32 destid = 0, UInt p1 = 0, UInt p2 = 0);
Bool DrawViews(DRAWFLAGS flags, BaseDraw* bd = nullptr);
Bool SendModelingCommand(Int32 command, ModelingCommandData& data);
Filename GetGlobalTexturePath(Int32 i);
void SetGlobalTexturePath(Int32 i, const Filename& fn);
Bool GenerateTexturePath(const Filename& docpath, const Filename& srcname, const Filename& suggestedfolder, Filename* dstname, NetRenderService* service = nullptr, BaseThread* bt = nullptr);
Bool IsInSearchPath(const Filename& texfilename, const Filename& docpath);
void FlushTexture(const Filename& docpath, const String& name, const Filename& suggestedfolder);
void FlushUnusedTextures(void);
BaseContainer GetWorldContainer(void);
BaseContainer* GetWorldContainerInstance(void);
void SaveWorldPreferences();
void SetWorldContainer(const BaseContainer& bc);
Vector GetViewColor(Int32 colid);
void SetViewColor(Int32 colid, const Vector& col);
void ErrorStringDialog(CHECKVALUERANGE type, Float x, Float y, CHECKVALUEFORMAT is);
Bool ReadPluginInfo(Int32 pluginid, void* buffer, Int32 size);
Bool WritePluginInfo(Int32 pluginid, void* buffer, Int32 size);
Bool ReadRegInfo(Int32 pluginid, void* buffer, Int32 size);
Bool WriteRegInfo(Int32 pluginid, void* buffer, Int32 size);
BaseContainer* GetWorldPluginData(Int32 id);
Bool SetWorldPluginData(Int32 id, const BaseContainer& bc, Bool add = true);
BaseContainer* GetToolPluginData(BaseDocument* doc, Int32 id);
Bool GeIsActiveToolEnabled(void);
Bool GeGetLanguage(Int32 index, String* extension, String* name, Bool* default_language);
Filename GeFilterSetSuffix(const Filename& name, Int32 id);
IDENTIFYFILE GeIdentifyFile(const Filename& name, UChar* probe, Int32 probesize, IDENTIFYFILE recognition, BasePlugin** bp);

GeListHead* GetScriptHead(Int32 type);
Int32 GetDynamicScriptID(BaseList2D* bl);
Bool GetCommandLineArgs(C4DPL_CommandLineArgs& args);

String GetObjectName(Int32 type);
String GetTagName(Int32 type);
Int32 GetObjectType(const String& name);
Int32 GetTagType(const String& name);

class Registry : public GeListNode
{
private:
	Registry();
	~Registry();

public:
	Registry* GetNext(void) { return (Registry*)AtCall(GetNext) (); }
	Registry* GetPred(void) { return (Registry*)AtCall(GetPred) (); }

	REGISTRYTYPE GetMainID(void);
	Int32 GetSubID(void);
	void* GetData(void);
};

Bool GeRegistryAdd(Int32 sub_id, REGISTRYTYPE main_id, void* data);
Bool GeRegistryRemove(Int32 sub_id, REGISTRYTYPE main_id);
Registry* GeRegistryFind(Int32 sub_id, REGISTRYTYPE main_id);
Registry* GeRegistryGetLast(REGISTRYTYPE main_id);
Registry* GeRegistryGetFirst(REGISTRYTYPE main_id);
Bool GeRegistryGetAutoID(Int32* id);
Bool GePluginMessage(Int32 id, void* data);

Bool CheckIsRunning(CHECKISRUNNING type);

String GeGetDefaultFilename(Int32 id);

void FindInManager(BaseList2D* bl);
void GeSleep(Int32 milliseconds);

Bool GeIsMainThread(void);

Int32	GeDebugSetFloatingPointChecks(Int32 on);

// The following class is a tool to disable floating point exceptions in debug mode
// use as
//	{
//		GeDebugDisableFPExceptions	disable_exceptions;
//		... do something here (3rd party code with divisions by zero etc.)
//	}
// in a code block to disable floating point exceptions in debug mode
class	GeDebugDisableFPExceptions
{
public:
	// constructor will disable fp exceptions
	GeDebugDisableFPExceptions(void)
	{
		restore = GeDebugSetFloatingPointChecks(false);
	}

	// destructor will restore the previous state
	~GeDebugDisableFPExceptions(void)
	{
		GeDebugSetFloatingPointChecks(restore);
	}

private:
	Int32	restore;
};

inline void _GeDebugBreak(Int32 line, const Char* file) { C4DOS.Ge->GeDebugBreak(line, file); }

void GeDebugOut(const Char* s, ...);	// Warning to Console
void GeDebugOut(const String& s);

	#include <stdio.h>
	#include <stdarg.h>
inline int sprintf_safe(char* _DstBuf, int _MaxCount, const char* _Format, ...)
{
	if (_MaxCount <= 0)
		return 0;

	va_list arp;
	va_start(arp, _Format);
	int res = vsnprintf(_DstBuf, _MaxCount, _Format, arp);
	if (res < 0 || res >= _MaxCount - 1)
	{
		if (res < 0)
			CriticalStop();
		_DstBuf[_MaxCount - 1] = 0;
		res = _MaxCount - 1;
	}
	va_end(arp);
	return res;
}
inline int vsprintf_safe(char* _DstBuf, int _MaxCount, const char* _Format, va_list _ArgList)
{
	if (_MaxCount <= 0)
		return 0;

	int res = vsnprintf(_DstBuf, _MaxCount, _Format, _ArgList);
	if (res < 0 || res >= _MaxCount - 1)
	{
		if (res < 0)
			CriticalStop();
		_DstBuf[_MaxCount - 1] = 0;
		res = _MaxCount - 1;
	}
	return res;
}

class LassoSelection
{
private:
	LassoSelection();
	~LassoSelection();

public:
	Bool Start(GeDialog& dlg, Int32 mode, Int32 start_x = NOTOK, Int32 start_y = NOTOK, Int32 start_button = NOTOK, Int32 sx1 = NOTOK, Int32 sy1 = NOTOK, Int32 sx2 = NOTOK, Int32 sy2 = NOTOK);
	Bool Start(GeUserArea& ua, Int32 mode, Int32 start_x = NOTOK, Int32 start_y = NOTOK, Int32 start_button = NOTOK, Int32 sx1 = NOTOK, Int32 sy1 = NOTOK, Int32 sx2 = NOTOK, Int32 sy2 = NOTOK);
	Bool Start(EditorWindow* win, Int32 mode, Int32 start_x = NOTOK, Int32 start_y = NOTOK, Int32 start_button = NOTOK, Int32 sx1 = NOTOK, Int32 sy1 = NOTOK, Int32 sx2 = NOTOK, Int32 sy2 = NOTOK);

	Bool CheckSingleClick();
	Bool Test(Int32 x, Int32 y);
	Bool TestPolygon(const Vector& pa, const Vector& pb, const Vector& pc, const Vector& pd);
	Int32	GetMode();
	Bool GetRectangle(Float& x1, Float& y1, Float& x2, Float& y2);

	static LassoSelection* Alloc();
	static void Free(LassoSelection*& ls);
};

GeData SendCoreMessage(Int32 coreid, const BaseContainer& msg, Int32 eventid = 0);
	#define COREMSG_CINEMA 'CMci'	// request to C4D core

String GetMacModel(const String& machinemodel);
BaseContainer GetMachineFeatures();
#define COREMSG_CINEMA_GETMACHINEFEATURES			'gOGL'
	#define OPENGL_SUPPORT_DUALPLANE_ARB									1001
	#define OPENGL_SUPPORT_DUALPLANE_KTX									1002
	#define OPENGL_EXTENSION_STRING												1003
	#define OPENGL_SUPPORT_GL_EXT_SEPARATE_SPECULAR_COLOR	1004
	#define OPENGL_SUPPORT_ENHANCED												1005
	#define OPENGL_RENDERER_NAME													1006
	#define OPENGL_VERSION_STRING													1007
	#define OPENGL_VENDOR_NUM															1008
		#define OPENGL_VENDOR_UNKNOWN												0
		#define OPENGL_VENDOR_NVIDIA												1
		#define OPENGL_VENDOR_ATI														2
		#define OPENGL_VENDOR_INTEL													3
		#define OPENGL_VENDOR_APPLE													4
	#define OPENGL_VENDOR_NAME														1009
	#define OPENGL_SHADING_LANGUAGE_VERSION_STRING				1010
	#define OPENGL_VERTEXBUFFER_OBJECT										1011
	#define OPENGL_FRAMEBUFFER_OBJECT											1012
	#define OPENGL_MULTITEXTURE														1013
	#define OPENGL_MAX_2DTEXTURE_SIZE											1014
	#define OPENGL_MAX_3DTEXTURE_SIZE											1015
	#define OPENGL_MAX_TEXCOORD														1016
	#define OPENGL_MAX_TEX_IMAGE_UNITS_VERTEX							1017
	#define OPENGL_MAX_TEX_IMAGE_UNITS_FRAGMENT						1018
	#define OPENGL_MAX_VP_INSTRUCTIONS										1019
	#define OPENGL_MAX_FP_INSTRUCTIONS										1020
	#define OPENGL_FLOATINGPOINT_TEXTURE									1021
	#define OPENGL_NONPOWEROF2_TEXTURE										1022
	#define OPENGL_DEPTH_TEXTURE													1023
	#define OPENGL_CG_TOOLKIT															1024
	#define OPENGL_MAX_TEXTURE_INDIRECTIONS								1025
	#define OPENGL_CG_LATEST_VERTEX_PROFILE								1026
	#define OPENGL_CG_LATEST_FRAGMENT_PROFILE							1027
	#define OPENGL_CG_LATEST_VERTEX_PROFILE_NAME					1028
	#define OPENGL_CG_LATEST_FRAGMENT_PROFILE_NAME				1029
	#define OPENGL_DRIVER_VERSION_STRING									1030	// only supported on Windows
	#define OPENGL_CG_VERSION_STRING											1031
	#define OPENGL_FBO_Z_DEPTH														1033
	#define OPENGL_FRAMEBUFFER_OBJECT_MULTISAMPLE					1034	// Int32 - max. samples
	#define OPENGL_MAX_ELEMENT_VERTICES										1035
	#define OPENGL_MAX_ELEMENT_INDICES										1036
	#define OPENGL_MAX_TEX_IMAGE_UNITS_GEOMETRY						1037
	#define OPENGL_CG_LATEST_GEOMETRY_PROFILE							1038
	#define OPENGL_CG_LATEST_GEOMETRY_PROFILE_NAME				1039
	#define OPENGL_VERSION_INT														1040
	#define OPENGL_GLSL_VERSION_INT												1041
	#define OPENGL_MAX_RENDERBUFFER_SAMPLES								1042
	#define OPENGL_RENDERBUFFER_MASK											1043	// UInt64
	#define OPENGL_RENDER_TO_FP16_TEXTURE									1044
	#define OPENGL_RENDER_TO_FP32_TEXTURE									1045
	#define OPENGL_STEREO_BUFFER													1046
	#define OPENGL_DRIVER_OUTDATED												1047	// only supported on Windows

	#define MACHINEINFO_OSTYPE						 2000
	#define MACHINEINFO_OSVERSION					 2001
	#define MACHINEINFO_PROCESSORTYPE			 2002
	#define MACHINEINFO_PROCESSORNAME			 2003
	#define MACHINEINFO_PROCESSORFEATURES	 2004
	#define MACHINEINFO_NUMBEROFPROCESSORS 2005
	#define MACHINEINFO_MACHINEMODEL			 2006
	#define MACHINEINFO_COMPUTERNAME			 2007
	#define MACHINEINFO_USERNAME					 2008
	#define MACHINEINFO_PROCESSORSPEED_MHZ 2009	// Float, MHz
	#define MACHINEINFO_C4DBUILDID				 2010	// String
	#define MACHINEINFO_C4DTYPE						 2011	// String
	#define MACHINEINFO_PROCESSORHTCOUNT	 2012	// Int32, number of logical processors per core, 1==no ht
	#define MACHINEINFO_PHYSICAL_RAM_SIZE	 2013	// Int64, physical memory size

	#define MACHINEINFO_LOADEDPLUGINS	3000

Bool GeGetMemoryStat(BaseContainer& stat);
#define C4D_MEMORY_STAT_MEMORY_INUSE							1		// Int64: bytes
#define C4D_MEMORY_STAT_MEMORY_PEAK								2		// Int64: bytes
#define C4D_MEMORY_STAT_NO_OF_ALLOCATIONS_TOTAL		3		// Int64: count
#define C4D_MEMORY_STAT_NO_OF_ALLOCATIONS_CURRENT	4		// Int64: count
#define C4D_MEMORY_STAT_EOGL_TEXBUFFER						5		// Int64: bytes
#define C4D_MEMORY_STAT_EOGL_VERTEXBUFFER					6		// Int64: bytes
#define C4D_MEMORY_STAT_LOWMEMCNT									7		// Int32: count
#define C4D_MEMORY_STAT_EOGL_VERTEXBUFFER_CNT			8		// Int32: number of VBOs
#define C4D_MEMORY_STAT_EOGL_TEXTUREBUFFER_CNT		9		// Int32: number of textures
#define C4D_MEMORY_STAT_OPENGL_TOTAL							10	// Int32: total OpenGL memory in KiB
#define C4D_MEMORY_STAT_OPENGL_FREE								11	// Int32: free OpenGL memory in KiB

#define POPUPEDITTEXTCALLBACK_TEXTCHANGED	1
#define POPUPEDITTEXTCALLBACK_CLOSED			2
#define POPUPEDITTEXTCALLBACK_CANCELED		3
#define POPUPEDITTEXTCALLBACK_CURSOR_UP		4
#define POPUPEDITTEXTCALLBACK_CURSOR_DOWN	5

Bool PopupEditText(Int32 screenx, Int32 screeny, Int32 width, Int32 height, const String& changeme, Int32 flags, PopupEditTextCallback* func, void* userdata);

void StartEditorRender(Bool active_only, Bool raybrush, Int32 x1, Int32 y1, Int32 x2, Int32 y2, BaseThread* bt, BaseDraw* bd, Bool newthread);
String FormatNumber(const GeData& val, Int32 format, Int32 fps, Bool bUnit = true);
GeData StringToNumber(const String& text, Int32 format, Int32 fps, const LENGTHUNIT* lengthunit = nullptr);

void CallCommand(Int32 id, Int32 subid = 0);
String GetCommandName(Int32 id);
String GetCommandHelp(Int32 id);
Bool IsCommandEnabled(Int32 id);
Bool IsCommandChecked(Int32 id);

Bool SendMailAvailable();
Bool SendMail(const String& t_subject, const String* t_to, const String* t_cc, const String* t_bcc, Filename* t_attachments, const String& t_body, Int32 flags);
	#define SENDMAIL_SENDDIRECTLY	1

Bool GetSystemEnvironmentVariable(const String& varname, String& result);
Bool AskForAdministratorPrivileges(const String& msg, const String& caption, Bool allowsuperuser, void** token);
void EndAdministratorPrivileges();
void RestartApplication(const UInt16* param = nullptr, Int32 exitcode = 0, const UInt16** path = nullptr);
void SetExitCode(Int32 exitCode);

void GeUpdateUI();

class DebugTimer
{
	Int32 m_lasttime;
	Char* m_str;

public:
	DebugTimer(Char* str)
	{
		m_lasttime = GeGetTimer();
		m_str = str;
	}
	~DebugTimer()
	{
		if (m_lasttime != 0)
			GeDebugOut(m_str, GeGetTimer() - m_lasttime);
	}
};

#define SHORTCUT_PLUGINID		1000
#define SHORTCUT_ADDRESS		1001
#define SHORTCUT_OPTIONMODE	1002

Int32 GetShortcutCount();
BaseContainer GetShortcut(Int32 index);
Bool AddShortcut(const BaseContainer& bc);
Bool RemoveShortcut(Int32 index);
Bool LoadShortcutSet(const Filename& fn, Bool add);
Bool SaveShortcutSet(const Filename& fn);
Int32 FindShortcutsFromID(Int32 pluginid, Int32* indexarray, Int32 maxarrayelements);
Int32 FindShortcuts(const BaseContainer& scut, Int32* idarray, Int32 maxarrayelements);
Bool CheckCommandShortcut(Int32 id, Int32 key, Int32 qual);

void InsertCreateObject(BaseDocument* doc, BaseObject* op, BaseObject* activeobj = nullptr);

// support for OS clipboard
//-------------------------------------------------------------------------------------------------
// enum CLIPBOARDTYPE
// {
//  CLIPBOARDTYPE_EMPTY  =0,
//  CLIPBOARDTYPE_STRING =1,
//  CLIPBOARDTYPE_BITMAP =2
// };

// copyToClipboard/GetC4DClipboardOwner
#define CLIPBOARDOWNER_BODYPAINT		 200000243
#define CLIPBOARDOWNER_PICTUREVIEWER 200000244

void CopyToClipboard(const String& text);
void CopyToClipboard(BaseBitmap* map, Int32 ownerid);

Bool GetStringFromClipboard(String* txt);
Bool GetBitmapFromClipboard(BaseBitmap* map);

CLIPBOARDTYPE GetClipboardType(void);
Int32 GetC4DClipboardOwner(void);
//-------------------------------------------------------------------------------------------------

void BrowserLibraryPopup(Int32 mx, Int32 my, Int32 defw, Int32 defh, Int32 pluginwindowid, Int32 presettypeid, void* userdata, BrowserPopupCallback callback);
const BaseBitmap* GetCursorBitmap(Int32 type, Int32& hotspotx, Int32& hotspoty);

#endif

#endif
