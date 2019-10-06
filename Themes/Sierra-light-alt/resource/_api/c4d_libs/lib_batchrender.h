/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

//---------------------------------------------------
#ifndef _C4D_BATCHRENDER_H_
#define _C4D_BATCHRENDER_H_

#ifdef __API_INTERN__
#include "c4d_basetime.h"
#include "ge_string.h"
#include "c4d_library.h"
#include "c4d_gui.h"
#include "lib_py.h"
#else
#include "c4d.h"
#include "lib_py.h"
#endif

class GeListNode;
class Filename;
class BaseBitmap;
class BaseDocument;
class String;
class BaseSound;

#define C4D_BATCHRENDER_LIBRARY_ID		465003507

#define BR_STOP		1
#define BR_START	2

//render flags
enum
{
	RM_PROGRESS = 1000,
	RM_FINISHED,
	RM_STOPPED,
	RM_ERROR,
	RM_ERROR2,
	RM_PAUSED,
	RM_QUEUE, //means is in queue but not rendered yet
	RM_WARNING,

	RM_NONE,
};

class BatchRender
{
	private:
		BatchRender();
		~BatchRender();
	public:
		Bool Open(void);
		Bool AddFile(const Filename &File, Int32 number);
		Bool DelFile(const Filename &File);

		Bool IsRendering();
		void SetRendering(Int32 set);
		Bool SetNetError(Int32 n, const String& machineName, const String& errorString, Bool isWarning);

		Int32 GetElementCount();

		Filename GetElement(Int32 n);
		void EnableElement(Int32 n, Bool bSet);
		Bool GetEnableElement(Int32 n);

		Int32 GetElementStatus(Int32 n);

		void GetJsonJobs(PyList* list);
		BaseBitmap* GetFrameBitmap(const C4DUuid& nodeUuid, const C4DUuid& frameUuid);
};

BatchRender* GetBatchRender();

//---------------------------------------------------
//	---INTERNAL STUFF

class iBatchRender;

struct BatchRenderLibrary : public C4DLibrary
{
	iBatchRender*	(*GetBatchRender)();

	Bool					(iBatchRender::*Open)								();
	Bool					(iBatchRender::*AddFile)						(const Filename &File, Int32 number);
	Bool					(iBatchRender::*DelFile)						(const Filename &File);

	Bool					(iBatchRender::*IsRendering)				();
	void					(iBatchRender::*SetRendering)				(Int32 set);


	Int32					(iBatchRender::*GetElementCount)		();

	Filename			(iBatchRender::*GetElement)					(Int32 n);
	void					(iBatchRender::*EnableElement)			(Int32 n, Bool bSet);
	Bool					(iBatchRender::*GetEnableElement)		(Int32 n);

	Int32					(iBatchRender::*GetElementStatus)		(Int32 n);

	Bool					(iBatchRender::*SetNetError)				(Int32 n, const String& machineName, const String& errorString, Bool isWarning);
	void					(iBatchRender::*GetJsonJobs)				(PyList* list);
	BaseBitmap*		(iBatchRender::*GetFrameBitmap)			(const C4DUuid& nodeUuid, const C4DUuid& frameUuid);
};

#endif

