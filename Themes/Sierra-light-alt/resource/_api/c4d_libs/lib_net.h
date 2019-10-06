/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

//---------------------------------------------------
#ifndef _C4D_NETRENDER_H_
#define _C4D_NETRENDER_H_

// Used for ::CoreMessage to detect if a NET message did arrive
#define EVMSG_NETMESSAGE				300002188

// Triggered when the machine list was changed
#define MSG_UPDATEDMACHINE			300002175
#define MSG_ADDEDMACHINE				300002176
#define MSG_REMOVEDMACHINE			300002177

// Triggered when the state of a NET instance changed
#define NET_SERVICESTATECHANGE	300002172

// used in NetGeSyncMessage/NetSpecialEventAdd/NetSendData and comes in NetRenderService::Message
#define MSG_NETRENDER_GETSTATE									300002130
#define MSG_NETRENDER_SECURITYTOKENCHANGED			300002131
#define MSG_NETRENDER_INFORMABOUTUNVERIFICATION 300002167
#define MSG_NETRENDER_RESTART										300002138
#define MSG_NETRENDER_PING											300002139

#define MSG_NETRENDER_BUCKET_INFO			0x1000	// Render Bucket Info (Client->Server, blocking expects result)
#define MSG_NETRENDER_BUCKET_INDEX		0x1001	// Render Bucket Index (Client->Server, blocking expects result)
#define MSG_NETRENDER_BUCKET_STARTED	0x1002	// Render Bucket Started (Client->Server, non blocking)
#define MSG_NETRENDER_BUCKET_FINISHED	0x1003	// Render Bucket Finished (Client->Server, non blocking)
#define MSG_NETRENDER_BUCKET_REQUEST	0x1004	// Render Bucket Requested (Client->Server, non blocking)
#define MSG_NETRENDER_CACHE_GET_CACHE	0x1010	// Render Cache Get Cache (Client->Server, blocking expects result)
#define MSG_NETRENDER_CACHE_GET_TASK	0x1011	// Render Cache Get Task (Client->Server, blocking expects result)
#define MSG_NETRENDER_CACHE_SEND_TASK	0x1012	// Render Cache Send Task (Client->Server, non blocking)
#define MSG_NETRENDER_CACHE_PROGRESS	0x1013	// Render Cache Progress (Server->Server, blocking expects result)
#define MSG_NETRENDER_CACHE_PREPASS		0x1014	// Render Cache Prepass State (Client->Server, blocking expects result)

#define MSG_NETRENDER_ANIMATION_RANGE	0x1100	// Get the next animation range (Client->Server, blocking expects results)
	#define CONTAINER_JOBUUID					1002		// C4DUuid
	#define CONTAINER_RANGE_AVAILABLE	1200		// Bool
	#define CONTAINER_RANGE_FROM			1300		// Int32
	#define CONTAINER_RANGE_TO				1140		// Int32

#define MSG_NETRENDER_WENTONLINE 300002135
	#define MSG_NETRENDER_WENTONLINE_NEWPORT						1000
	#define MSG_NETRENDER_WENTONLINE_RESULT_VERIFIESME	2000
	#define MSG_NETRENDER_WENTONLINE_RESULT_SHARED			3000

#define MSG_NETRENDER_REDISTRIBUTED 300002166
	#define MSG_NETRENDER_REDISTRIBUTED_JOBUUID 1000

#define MSG_NETRENDER_SENDSTATE 300002129
	#define MSG_NETRENDER_SENDSTATE_STATE		1000
	#define MSG_NETRENDER_SENDSTATE_COUNTER 1001
	#define MSG_NETRENDER_SENDSTATE_SERVERUUID 1002

#define MSG_NETRENDER_MACHINENAMECHANGED 300002132
	#define MSG_NETRENDER_MACHINENAMECHANGED_NAME 1000

#define MSG_NETRENDER_SENDERROR 300002134
	#define MSG_NETRENDER_SENDERROR_UUID			1001
	#define MSG_NETRENDER_SENDERROR_MESSAGE		1000
	#define MSG_NETRENDER_SENDERROR_ISWARNING 1002
	#define MSG_NETRENDER_SENDERROR_FRAMENUMBER 1003

#define MSG_NETRENDER_PORTCHANGED 300002147
	#define MSG_NETRENDER_PORTCHANGED_PORT 1000

#define ID_GLOBALMACHINELIST 300002136

#ifdef __API_INTERN__
	#include "intbaselist.h"
	
	#include "c4d_basetime.h"
	#include "c4d_library.h"
	#include "c4d_gui.h"
	
	#include "hyperfile.h"
	#include "ge_string.h"
	#include "ge_uuid.h"
	#include "ge_prepass.h"
	#include "customgui_listview.h"
	#include "lib_py.h"
#else
	#include "c4d.h"
	#include "customgui_listview.h"
	#include "lib_py.h"
#endif

class Task
{
public:
	C4DUuid _serverUuid;					// uuid of server which has a job
	maxon::BaseArray<JOBCOMMAND> _commands;

	Task() : _serverUuid(DC) { }
	Task(const Task& task) : _serverUuid(task._serverUuid) { _commands.CopyFrom(task._commands); }
};

#ifndef __API_INTERN__
	#ifdef __NET_LIB__
		#include "net_renderservice.h"
	#endif
#endif

#define C4D_NETRENDER_LIBRARY_ID		1027247

Bool IsNetRenderInstalled();

class PictureViewer;
class NetRenderService;
class Repository;
class Asset;
class UserPool;

#ifndef __NET_LIB__

	struct NetRenderBuffer;
	struct NetRenderDocumentContext;

	class MachineGroup : public BaseList2D
	{
#ifndef __API_INTERN__
	private:
		MachineGroup();
		~MachineGroup();
#endif
	};

	class NetRenderData
	{
	private:
		NetRenderData();
		~NetRenderData();

	public:
		String					GetName() const;

		Bool						IsSingleFrameRendering() const;
		Int32						GetRealFps() const;
		Float						GetFps() const;
		BaseTime				GetFrameFrom() const;
		BaseTime				GetFrameTo() const;
		Int32						GetWidth() const;
		Int32						GetHeight() const;
		Int32						GetFrameRange() const;
		Int32						GetNameFormat() const;
		Int32						GetFrameStep() const;
		BaseContainer		GetData() const;
		Bool						UseFrameNumberAsSuffix() const;
		Bool						ShowHud() const;

		Bool						SaveImage() const;
		Int32						GetImageFormat() const;
		Filename				GetImageFilename() const;
		Filename				GetImageAbsResultFolder() const;
		Bool						GetImageFormatIsMovie() const;

		Bool						SaveMultipass() const;
		Int32						GetMultipassImageFormat() const;
		Filename				GetMultipassFilename() const;
		Filename				GetMultipassAbsResultFolder() const;
		Bool						GetMultipassFormatIsMovie() const;
		Bool						GetMultipassSaveMultilayer() const;

		Bool						ShowTextureError() const;

		NETRENDERFLAGS	GetFlags() const;
		Filename				GetB3dTempFolder() const;
	};

	class Machine : public BaseList2D
	{
#ifndef __API_INTERN__
	private:
		Machine();
		~Machine();
#endif
	public:
		Machine* GetNext() const { return (Machine*)AtCall(GetNext)(); }
		Machine* GetPred() const { return (Machine*)AtCall(GetPred)(); }

		const C4DUuid GetUuid() const;
		void SetUuid(const C4DUuid& uid);

		Vector GetColor(const Vector* bgColor = nullptr) const;
		void SetColor(const Vector& color);

		Bool GetGlobalSelected() const;
		void SetGlobalSelected(Bool globalSelected);

		void FoundViaZeroConf(Bool foundViaZeroConf);
		Bool FoundViaZeroConf() const;

		String GetFullyQualifiedDomainName(Bool* isPrivate) const;

		OPERATINGSYSTEM GetOperatingSystem();
		void SetOperatingSystem(OPERATINGSYSTEM operatingSystem);

		const BaseContainer& GetMachineFeatures() const;
		void SetMachineFeatures(const BaseContainer& t_bc);

		JOBCOMMAND GetCurrentJobCommand(C4DUuid* rendersFor = nullptr) const;

		void SetMacAddress(const maxon::BaseArray<UChar>& macAddress);
		void GetMacAddress(maxon::BaseArray<UChar>& macAddress) const;

		void ClearVerificationBit(VERIFICATIONBIT state);
		Bool GetVerificationBit(VERIFICATIONBIT state) const;
		void SetVerificationBit(VERIFICATIONBIT state);
	};

	class Client : public BaseList2D
	{
#ifndef __API_INTERN__
	private:
		Client();
		~Client();
#endif
	};

	class Server : public BaseList2D
	{
#ifndef __API_INTERN__
	private:
		Server();
		~Server();
#endif
	};

	class RenderJob : public BaseList2D
	{
#ifndef __API_INTERN__
	private:
		RenderJob();
		~RenderJob();
#endif

	public:
		JOBSTATE						GetState() const;
		void								SetState(JOBSTATE state, Bool sendSignal = TRUE);
		const C4DUuid				GetUuid() const;
		const C4DUuid				GetCreatorUuid() const;
		void								SetCreatorUuid(const C4DUuid& creatorUuid);
		const C4DUuid				GetServerUuid() const;
		void								SetServerUuid(const C4DUuid& serverUuid);

		Bool								AddMachine(const C4DUuid& machineUuid);
		Bool								AddMachines(const maxon::BaseArray<C4DUuid>& machineUuids, Bool flush = false);
		Bool								RemoveMachine(const C4DUuid& machineUuid);
		Bool								RemoveMachines(const maxon::BaseArray<C4DUuid>& machineUuids);
		void								GetMachines(maxon::BaseArray<C4DUuid>& machineUuids) const;
		void								UpdateProgress(Float progress, Bool completed);
		const NetRenderData*	GetRenderData() const;

		NetRenderService*		GetNetRenderService() const;
		RelativeFilename		GetProjectFolder() const;
		Asset*							GetFirstAsset() const;

		ProgressHook*				GetProgressHook(void*& context);
		WriteProgressHook*	GetWriteProgressHook(void*& context);
	};

	class NetService
	{
	};

	class Asset : public BaseList2D
	{
#ifndef __API_INTERN__
	private:
		Asset();
		~Asset();
#endif

	public:
		Asset* GetNext() const { return (Asset*)AtCall(GetNext)(); }
		Asset* GetPred() const { return (Asset*)AtCall(GetPred)(); }
	};

	class Repository
	{
	public:
		Filename GetRepositoryPath() const;
		Filename GetJobsPath(Bool server) const;
		void SetRepositoryPath(const Filename& repositoryPath);
		Filename ConvertRelative2AbsolutePath(RenderJob* job, Asset* asset) const;
		Bool ConvertAbsolute2RelativePath(const Filename &absolutePath, RelativeFilename &relativePath, Bool server) const;
	};

	class UserPool
	{
	public:
		Bool AddUser(const String& username, const String& password, const String& description, Bool isAdmin);
		Bool DeleteUser(const String& username);
		Bool ChangePassword(const String& username, const String& oldPassword, const String& newPassword);
		Bool CheckUserCredentials(const String& username, const String& password) const;
	};

	class NetRenderService : public NetService
	{
	public:
		MachineGroup* GetOnlineHead() const;
		MachineGroup* GetOfflineHead() const;
		Machine* GetFirstOnline() const;
		Machine* GetFirstOffline() const;
		Machine* FindMachine(const C4DUuid& uid, MACHINELIST list, VERIFICATIONBIT bits = VERIFICATIONBIT_0) const;
		GeRWSpinlock& GetMachineLock();
		void GetAllMachineUuids(maxon::BaseArray<C4DUuid>& machineUuids, MACHINELIST list, VERIFICATIONBIT bits, Bool includeLocalMachine, Bool includeZeroConfMachines);
		RenderJob* FindRenderJob(const C4DUuid& jobUuid, Bool lookInServerList) const;
		const C4DUuid GetUuid() const;
		void GetMacAddress(maxon::BaseArray<UChar>& macAddress) const;
		Int32 GetInternalPort() const;
		Int32 GetExternalPort() const;
		void CopyClientTasksFrom(maxon::BaseArray<Task>& task);
		Repository& GetRepository();
		UserPool& GetUserPool();
		GeRWSpinlock& GetClientRenderJobLock();
		String GetName() const;
		Bool IsRunning();
		void NetConsoleOutput(maxon::OUTPUT flags, const String& value);

		//client
		String				GetCurrentJobCommandAsString();
		RenderJob*		GetActive() const;

		// server
		CREATEJOBRESULT CreateRenderJob(const String& docName, C4DUuid& jobUuid, RENDERJOBCREATOR creator, const C4DUuid& userUuid, BaseThread* bt = nullptr, Filename* watchFolderName = nullptr);
		RENDERRESULT InitRendering(BaseDocument* doc, const BaseContainer& rdata, const C4DUuid& jobUuid, NETRENDERFLAGS flags, PictureViewer* pv, const BaseContainer& machines, MultipassBitmap* bmp = nullptr, ProgressHook* prog = nullptr, WriteProgressHook* wprog = nullptr, void* context = nullptr, Bool* useFrameNumberAsSuffix = nullptr, Filename* dispname = nullptr, const maxon::BaseArray<Bool>* renderTasks = nullptr);
		RENDERRESULT StartRendering(THREADMODE mode, BaseDocument* doc, const C4DUuid& jobUuid, BaseThread* bt);
		Bool VerifyServerOnClient(THREADMODE mode, const C4DUuid& machineUuid, const String& securityToken, Bool setClientAsGlobalSelected, Bool doLock = true, Int32 waitUntilExecutionInMs = 0);
		Bool DeleteRenderJob(const C4DUuid& jobUuid, Bool informClients);
		Bool GetGlobalSelected(maxon::BaseArray<C4DUuid>& machines);
		Bool GetJsonJobs(PyList* list) const;
		void GetGlobalSelectedMachines(maxon::BaseArray<C4DUuid>& machines, Bool& atLeastOneMachineOnline);
	};

	NetRenderService* GetGlobalNetRenderService();

	String GetMachineDescription(NetRenderService* service, Machine* m);
	String VerificationBitToString(VERIFICATIONBIT state);
	String JobCommandToString(JOBCOMMAND jobCommand);
	String GetDebugStringOfMachine(Machine* m);
	
	MESSAGERESULT NetSpecialEventAdd(NetRenderService* service, const C4DUuid& remoteUuid, const BaseContainer& msg, Bool targetMightBeMarkedAsOffline = false);
	MESSAGERESULT NetGeSyncMessage(NetRenderService* service, const C4DUuid& remoteUuid, const BaseContainer& msg, BaseContainer& result, BaseThread* bt = nullptr, Bool forceConnect = false);
	MESSAGERESULT NetSendData(NetRenderService* service, const C4DUuid& remoteUuid, NetRenderBuffer *data, NetRenderBuffer *result, BaseThread* bt = nullptr);

	Bool NetRenderCacheGet(NetRenderDocumentContext* context, Bool isServer, Int32 cacheID, void* &data, Int32 &size);
	Bool NetRenderCacheGetTask(NetRenderDocumentContext* context, Bool isServer, Int32 cacheID, Int32 &taskID, Int32 &taskSubdivisions);
	Bool NetRenderCacheSendTask(NetRenderDocumentContext* context, Bool isServer, Int32 cacheID, Int32 taskID, void *data, Int32 size, Bool progress);
	Bool NetRenderCacheProgress(NetRenderDocumentContext* context, Int32 cacheID, Int32 lastIndex, void* &data, Int32 &size, BaseThread* thread);
	Bool NetRenderCachePrepass(NetRenderDocumentContext* context, Int32 cacheID, Bool &completed);
	Bool NetRenderGetFileFromServer(NetRenderService* context, const Filename& assetName, const Filename& destination, BaseThread* bt = nullptr);

#endif
//---------------------------------------------------
//	---INTERNAL STUFF

// Net Bucket Border Dimensions
#define NET_BUCKET_BORDER						4
#define NET_BUCKET_BORDER_2					8

// Net C4D Cache IDs (always register your own IDs to avoid potential conflicts)
#define NET_CACHE_ID_SSS_POINTS			0x1100
#define NET_CACHE_ID_SSS_IRRADIANCE	0x1101
//
#define NET_CACHE_ID_GI_COMPLETE		0x1200
#define NET_CACHE_ID_GI_PREPASS			0x1201
#define NET_CACHE_ID_GI_PASSES			0x1210 // All 16 are reserved
#define NET_CACHE_ID_GI_PROGRESS		0x1220 // All 16 are reserved
//
#define NET_CACHE_ID_AO_COMPLETE		0x1300
#define NET_CACHE_ID_AO_PREPASS			0x1301
#define NET_CACHE_ID_AO_PASSES			0x1310 // All 16 are reserved
#define NET_CACHE_ID_AO_PROGRESS		0x1320 // All 16 are reserved
//
#define NET_CACHE_ID_LM_COMPLETE		0x1400
#define NET_CACHE_ID_LM_PREPASS			0x1401
#define NET_CACHE_ID_LM_PASSES			0x1402
#define NET_CACHE_ID_LM_PROGRESS		0x1403
//
#define NET_CACHE_ID_RM_COMPLETE		0x1500
#define NET_CACHE_ID_RM_PREPASS			0x1501
#define NET_CACHE_ID_RM_PASSES			0x1502
#define NET_CACHE_ID_RM_PROGRESS		0x1503


struct NetRenderBuffer
{
	Int32									id;
	C4DUuid								job;
	Int32									size;
	void*									data;

	NetRenderBuffer() : id(0), job(DC), size(0), data(nullptr)
	{
	}

	void MoveTo(NetRenderBuffer& dst)
	{
		dst.id = id;
		dst.job = job;
		dst.size = size;
		dst.data = data;
		data = nullptr;
	}

	~NetRenderBuffer()
	{
		if (data)
			DeleteMem(data);
	}
};

struct NetRenderMsgBucketInfo
{ 
	Bool									weightData;
	Int32									bucketSize;
};

struct NetRenderMsgBucketIndex
{
	Int32									bucketID;
};

struct NetRenderMsgBucketStarted
{
	Int32									bucketID;

	Int32									regionX1;
	Int32									regionX2;
	Int32									regionY1;
	Int32									regionY2;
};

struct NetRenderMsgBucketFinished
{
	Int32									bucketID;

	Int32									offsetX;
	Int32									offsetY;
	Int32									sizeX;
	Int32									sizeY;
	Int32									borderX;
	Int32									borderY;

	Int32									tilex;
	Int32									tiley;
	Int32									passCount;

	Int32									bufferSize;
	Int32									fragmentsSize;
	Int32									weightMapSize;
	Int32									glowSize;
	Int32									lensDataSize;

	Float32*							buffer;
	UChar*								fragments;
	Bool*									weightMap;
	UChar*								glow;
	Float32*							lensData;
};

struct NetRenderMsgCacheGetCache
{
	Int32									cacheID;

	Bool									cacheValid;
	Int32									cacheSize;
	void*									cacheData;
};

struct NetRenderMsgCacheGetTask
{
	Int32									cacheID;

	Int32									taskID;
	Int32									taskSubdivisions;
};

struct NetRenderMsgCacheSendTask
{
	Int32									cacheID;

	Int32									taskID;
	Int32									taskSize;
	void*									taskData;
	Bool									taskProgress;
};

struct NetRenderMsgCacheProgress
{
	Int32									cacheID;
	Int32									lastIndex;
	BaseThread*						threadPtr;

	Int32									progressSize;
	void*									progressData;
};

struct NetRenderMsgCachePrepass
{
	Int32									cacheID;

	Bool									completed;
};

struct NetRenderDocumentContext
{
	DISALLOW_COPY_AND_ASSIGN(NetRenderDocumentContext);

	RenderJob*						_renderJob;
	NetRenderService*			_service;
	Bool									_singleImageDistribution;				// If true it's Distributed Rendering, otherwise Animation Rendering
	Int32									_cpuCount;
	Bool									_redistributed;
	Bool									_valid;
	Int32									_currentFrame;
	NetRenderDocumentContext() : _renderJob(nullptr), _service(nullptr), _singleImageDistribution(false), _cpuCount(GeGetCPUCount()), _redistributed(false), _valid(true), _currentFrame(NOTOK) { }
	~NetRenderDocumentContext() { _valid = false; }
};

struct NetLibrary : public C4DLibrary
{
	JOBSTATE							(RenderJob::*RenderJobGetState)						() const;
	void									(RenderJob::*RenderJobSetState)						(JOBSTATE state, Bool sendSignal);
	const C4DUuid					(RenderJob::*RenderJobGetUuid)						() const;
	const C4DUuid					(RenderJob::*RenderJobGetCreatorUuid)			() const;
	void									(RenderJob::*RenderJobSetCreatorUuid)			(const C4DUuid& creatorUuid);
	const C4DUuid					(RenderJob::*RenderJobGetServerUuid)			() const;
	void									(RenderJob::*RenderJobSetServerUuid)			(const C4DUuid& serverUuid);
	NetRenderService*			(RenderJob::*GetNetRenderService)					() const;
	const NetRenderData*	(RenderJob::*GetRenderData)								() const;

	Bool									(RenderJob::*AddMachine)									(const C4DUuid& machineUuid);
	Bool									(RenderJob::*AddMachines)									(const maxon::BaseArray<C4DUuid>& machineUuids, Bool flush);
	Bool									(RenderJob::*RemoveMachine)								(const C4DUuid& machineUuid);
	Bool									(RenderJob::*RemoveMachines)							(const maxon::BaseArray<C4DUuid>& machineUuids);
	void									(RenderJob::*GetMachines)									(maxon::BaseArray<C4DUuid>& machineUuids) const;

	void									(RenderJob::*UpdateProgress)							(Float progress, Bool completed);

	const C4DUuid					(Machine::*GetUuid)												() const;
	void									(Machine::*SetUuid)												(const C4DUuid& uid);
	Vector								(Machine::*GetColor)											(const Vector* bgColor) const;
	void									(Machine::*SetColor)											(const Vector& color);
	void									(Machine::*FoundViaZeroConf)							(Bool foundViaZeroConf);
	Bool									(Machine::*FoundViaZeroConf2)							() const;
	OPERATINGSYSTEM				(Machine::*GetOperatingSystem)						();
	void									(Machine::*SetOperatingSystem)						(OPERATINGSYSTEM operatingSystem);
	const BaseContainer&	(Machine::*GetMachineFeatures)						() const;
	void									(Machine::*SetMachineFeatures)						(const BaseContainer& t_bc);
	JOBCOMMAND						(Machine::*GetCurrentJobCommand)					(C4DUuid* rendersFor) const;
	void									(Machine::*SetMacAddress)									(const maxon::BaseArray<UChar>& macAddress);
	void									(Machine::*GetMacAddress)									(maxon::BaseArray<UChar>& macAddress) const;
	String								(Machine::*GetFullyQualifiedDomainName)		(Bool* isPrivate) const;
	void									(Machine::*ClearVerificationBit)					(VERIFICATIONBIT state);
	Bool									(Machine::*GetVerificationBit)						(VERIFICATIONBIT state) const;
	void									(Machine::*SetVerificationBit)						(VERIFICATIONBIT state);
	Bool									(Machine::*GetGlobalSelected)							() const;
	void									(Machine::*SetGlobalSelected)							(Bool globalSelected);

	Machine*							(NetRenderService::*FindMachine)					(const C4DUuid& uid, MACHINELIST list, VERIFICATIONBIT bits) const;
	MachineGroup*					(NetRenderService::*GetOnlineHead)				() const;
	MachineGroup*					(NetRenderService::*GetOfflineHead)				() const;
	Machine*							(NetRenderService::*GetFirstOnline)				() const;
	Machine*							(NetRenderService::*GetFirstOffline)			() const;
	GeRWSpinlock&					(NetRenderService::*GetMachineLock)				();
	void									(NetRenderService::*GetAllMachineUuids)		(maxon::BaseArray<C4DUuid>& machineUuids, MACHINELIST list, VERIFICATIONBIT bits, Bool includeLocalMachine, Bool includeZeroConfMachines);
	RenderJob*						(NetRenderService::*FindRenderJob)				(const C4DUuid& jobUuid, Bool lookInServerList) const;
	const C4DUuid					(NetRenderService::*GetUuid2)							() const;
	void									(NetRenderService::*GetMacAddress2)				(maxon::BaseArray<UChar>& macAddress) const;
	Int32									(NetRenderService::*GetInternalPort)			() const;
	Int32									(NetRenderService::*GetExternalPort)			() const;
	String								(NetRenderService::*GetHostname)					() const;
	void									(NetRenderService::*CopyClientTasksFrom)	(maxon::BaseArray<Task>& task) const;
	Repository&						(NetRenderService::*GetRepository)				();
	GeRWSpinlock&					(NetRenderService::*GetClientRenderJobLock)();
	RENDERRESULT					(NetRenderService::*InitRendering)				(BaseDocument* doc, const BaseContainer& rdata, const C4DUuid& jobUuid, NETRENDERFLAGS flags, PictureViewer* pv, const BaseContainer& machines, MultipassBitmap* bmp, ProgressHook* prog, WriteProgressHook* wprog, void* context, Bool* useFrameNumberAsSuffix, Filename* dispname, const maxon::BaseArray<Bool>* renderTasks);
	CREATEJOBRESULT				(NetRenderService::*CreateRenderJob)			(const String& docName, C4DUuid& jobUuid, RENDERJOBCREATOR creator, const C4DUuid& userUuid, BaseThread* bt, Filename* watchFolderName);
	RENDERRESULT					(NetRenderService::*StartRendering)				(THREADMODE mode, BaseDocument* doc, const C4DUuid& jobUuid, BaseThread* bt);
	Bool									(NetRenderService::*VerifyServerOnClient)	(THREADMODE mode, const C4DUuid& machineUuid, const String& securityToken, Bool setClientAsGlobalSelected, Bool doLock, Int32 waitUntilExecutionInMs);
	Bool									(NetRenderService::*DeleteRenderJob)			(const C4DUuid& jobUuid, Bool informClients);
	Bool									(NetRenderService::*GetGlobalSelected2)		(maxon::BaseArray<C4DUuid>& machines);
	UserPool&							(NetRenderService::*GetUserPool)					();
	Bool									(NetRenderService::*GetJsonJobs)					(PyList* list) const;
	void									(NetRenderService::*GetGlobalSelectedMachines)(maxon::BaseArray<C4DUuid>& machines, Bool& atLeastOneMachineOnline);

	String								(NetRenderService::*GetCurrentJobCommandAsString)	();

	MESSAGERESULT					(*NetSpecialEventAdd)											(NetRenderService* service, const C4DUuid& remoteUuid, const BaseContainer& msg, Bool forceConnect);
	MESSAGERESULT					(*NetGeSyncMessage)												(NetRenderService* service, const C4DUuid& remoteUuid, const BaseContainer& msg, BaseContainer& result, BaseThread* bt, Bool forceConnect);
	MESSAGERESULT					(*NetSendData)														(NetRenderService* service, const C4DUuid& remoteUuid, NetRenderBuffer *data, NetRenderBuffer *result, BaseThread* bt);
	
	Bool									(*NetRenderCacheGet)											(NetRenderDocumentContext* context, Bool isServer, Int32 cacheID, void* &data, Int32 &size);
	Bool									(*NetRenderCacheGetTask)									(NetRenderDocumentContext* context, Bool isServer, Int32 cacheID, Int32 &taskID, Int32 &taskSubdivisions);
	Bool									(*NetRenderCacheSendTask)									(NetRenderDocumentContext* context, Bool isServer, Int32 cacheID, Int32 taskID, void *data, Int32 size, Bool progress);
	Bool									(*NetRenderCacheProgress)									(NetRenderDocumentContext* context, Int32 cacheID, Int32 lastIndex, void* &data, Int32 &size, BaseThread* thread);
	Bool									(*NetRenderCachePrepass)									(NetRenderDocumentContext* context, Int32 cacheID, Bool &completed);
	Bool									(*NetRenderGetFileFromServer)							(NetRenderService* client, const Filename& assetName, const Filename& destination, BaseThread* bt);

	NetRenderService*			(*GetGlobalNetRenderService)							();
	String								(*GetMachineDescription)									(NetRenderService* service, Machine* m);
	String								(*VerificationBitToString)								(VERIFICATIONBIT state);
	String								(*JobCommandToString)											(JOBCOMMAND jobCommand);
	String								(*GetDebugStringOfMachine)								(Machine* m);

	Filename							(Repository::*GetRepositoryPath)						() const;
	Filename							(Repository::*GetJobsPath)									(Bool server) const;
	void									(Repository::*SetRepositoryPath)						(const Filename& repositoryPath);
	Bool									(Repository::*ConvertAbsolute2RelativePath)	(const Filename &absolutePath, RelativeFilename &relativePath, Bool server) const;
	Filename							(Repository::*ConvertRelative2AbsolutePath)	(RenderJob* job, Asset* asset) const;

	RenderJob*						(NetRenderService::*GetActive)							() const;
	RelativeFilename			(RenderJob::*GetProjectFolder)							() const;
	Asset*								(RenderJob::*GetFirstAsset)									() const;

	Bool									(UserPool::*AddUser)												(const String& username, const String& password, const String& description, Bool isAdmin);
	Bool									(UserPool::*DeleteUser)											(const String& username);
	Bool									(UserPool::*ChangePassword)									(const String& username, const String& oldPassword, const String& newPassword);
	Bool									(UserPool::*CheckUserCredentials)						(const String& username, const String& password) const;

	ProgressHook*					(RenderJob::*GetProgressHook)								(void*& context);
	WriteProgressHook*		(RenderJob::*GetWriteProgressHook)					(void*& context);
	String								(NetRenderService::*GetName)								() const;
	Bool									(NetRenderService::*IsRunning)							();

	String								(NetRenderData::*GetName2)										() const;
	Bool									(NetRenderData::*IsSingleFrameRendering)			() const;
	Int32									(NetRenderData::*GetRealFps)									() const;
	Float									(NetRenderData::*GetFps)											() const;
	BaseTime							(NetRenderData::*GetFrameFrom)								() const;
	BaseTime							(NetRenderData::*GetFrameTo)									() const;
	Int32									(NetRenderData::*GetWidth)										() const;
	Int32									(NetRenderData::*GetHeight)										() const;
	Int32									(NetRenderData::*GetFrameRange)								() const;
	Int32									(NetRenderData::*GetNameFormat)								() const;
	Int32									(NetRenderData::*GetFrameStep)								() const;
	BaseContainer					(NetRenderData::*GetData)											() const;
	Bool									(NetRenderData::*UseFrameNumberAsSuffix)			() const;
	Bool									(NetRenderData::*ShowHud)											() const;
	Bool									(NetRenderData::*SaveImage)										() const;
	Int32									(NetRenderData::*GetImageFormat)							() const;
	Filename							(NetRenderData::*GetImageFilename)						() const;
	Filename							(NetRenderData::*GetImageAbsResultFolder)			() const;
	Bool									(NetRenderData::*GetImageFormatIsMovie)				() const;
	Bool									(NetRenderData::*SaveMultipass)								() const;
	Int32									(NetRenderData::*GetMultipassImageFormat)			() const;
	Filename							(NetRenderData::*GetMultipassFilename)				() const;
	Filename							(NetRenderData::*GetMultipassAbsResultFolder)	() const;
	Bool									(NetRenderData::*GetMultipassFormatIsMovie) 	() const;
	Bool									(NetRenderData::*GetMultipassSaveMultilayer)	() const;
	Bool									(NetRenderData::*ShowTextureError)						() const;
	NETRENDERFLAGS				(NetRenderData::*GetFlags)										() const;
	Filename							(NetRenderData::*GetB3dTempFolder)						() const;

	void									(NetRenderService::*NetConsoleOutput)					(maxon::OUTPUT flags, const String& value);
};

#endif

