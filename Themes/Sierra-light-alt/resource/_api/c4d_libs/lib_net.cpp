/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) 1989-2009 MAXON Computer GmbH, all rights reserved  //
/////////////////////////////////////////////////////////////

#include "lib_prefs.h"
#include "lib_net.h"

static NetLibrary* net_lib_cache = nullptr;

static NetLibrary* CheckNetRenderLib(Int32 offset)
{
	return (NetLibrary*)CheckLib(C4D_NETRENDER_LIBRARY_ID, offset, (C4DLibrary**)&net_lib_cache);
}

Bool IsNetRenderInstalled()
{
	return IsLibraryInstalled(C4D_NETRENDER_LIBRARY_ID);
}

#ifndef __NET_LIB__

JOBSTATE RenderJob::GetState() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, RenderJobGetState));
	if (!lib || !lib->RenderJobGetState) return (JOBSTATE)0;
	return (((RenderJob*)this)->*(lib->RenderJobGetState))();
}

void RenderJob::SetState(JOBSTATE state, Bool sendSignal)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, RenderJobSetState));
	if (!lib || !lib->RenderJobSetState) return;
	(((RenderJob*)this)->*(lib->RenderJobSetState))(state, sendSignal);
}

NetRenderService* RenderJob::GetNetRenderService() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetNetRenderService));
	if (!lib || !lib->GetNetRenderService) return nullptr;
	return (((RenderJob*)this)->*(lib->GetNetRenderService))();
}

const C4DUuid RenderJob::GetUuid() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, RenderJobGetUuid));
	if (!lib || !lib->RenderJobGetUuid) return C4DUuid(DC);
	return (((RenderJob*)this)->*(lib->RenderJobGetUuid))();
}

ProgressHook* RenderJob::GetProgressHook(void*& context)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetProgressHook));
	if (!lib || !lib->GetProgressHook) return nullptr;
	return (((RenderJob*)this)->*(lib->GetProgressHook))(context);
}

WriteProgressHook* RenderJob::GetWriteProgressHook(void*& context)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetWriteProgressHook));
	if (!lib || !lib->GetWriteProgressHook) return nullptr;
	return (((RenderJob*)this)->*(lib->GetWriteProgressHook))(context);
}

const C4DUuid RenderJob::GetCreatorUuid() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, RenderJobGetCreatorUuid));
	if (!lib || !lib->RenderJobGetCreatorUuid) return C4DUuid(DC);
	return (((RenderJob*)this)->*(lib->RenderJobGetCreatorUuid))();
}

void RenderJob::SetCreatorUuid(const C4DUuid& creatorUuid)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, RenderJobSetCreatorUuid));
	if (!lib || !lib->RenderJobGetServerUuid) return;
	(((RenderJob*)this)->*(lib->RenderJobSetCreatorUuid))(creatorUuid);
}

const C4DUuid RenderJob::GetServerUuid() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, RenderJobGetServerUuid));
	if (!lib || !lib->RenderJobGetServerUuid) return C4DUuid(DC);
	return (((RenderJob*)this)->*(lib->RenderJobGetServerUuid))();
}

void RenderJob::SetServerUuid(const C4DUuid& serverUuid)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, RenderJobSetServerUuid));
	if (!lib || !lib->RenderJobSetServerUuid) return;
	(((RenderJob*)this)->*(lib->RenderJobSetServerUuid))(serverUuid);
}

void RenderJob::UpdateProgress(Float progress, Bool completed)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, UpdateProgress));
	if (!lib || !lib->UpdateProgress) return;
	(((RenderJob*)this)->*(lib->UpdateProgress))(progress, completed);
}

const NetRenderData* RenderJob::GetRenderData() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetRenderData));
	if (!lib || !lib->GetRenderData) return nullptr;
	return (((RenderJob*)this)->*(lib->GetRenderData))();
}

RelativeFilename RenderJob::GetProjectFolder() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetProjectFolder));
	if (!lib || !lib->GetProjectFolder) return RelativeFilename();
	return (((RenderJob*)this)->*(lib->GetProjectFolder))();
}

MESSAGERESULT NetSpecialEventAdd(NetRenderService* service, const C4DUuid& remoteUuid, const BaseContainer& msg, Bool targetMightBeMarkedAsOffline)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, NetSpecialEventAdd));
	if (!lib || !lib->NetSpecialEventAdd) return MESSAGERESULT_MEMORYERROR;
	return (lib->NetSpecialEventAdd)(service, remoteUuid, msg, targetMightBeMarkedAsOffline);
}

MESSAGERESULT NetGeSyncMessage(NetRenderService* service, const C4DUuid& remoteUuid, const BaseContainer& msg, BaseContainer& result, BaseThread* bt, Bool forceConnect)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, NetGeSyncMessage));
	if (!lib || !lib->NetGeSyncMessage) return MESSAGERESULT_MEMORYERROR;
	return (lib->NetGeSyncMessage)(service, remoteUuid, msg, result, bt, forceConnect);
}

MESSAGERESULT NetSendData(NetRenderService* service, const C4DUuid& remoteUuid, NetRenderBuffer *data, NetRenderBuffer *result, BaseThread* bt)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, NetSendData));
	if (!lib || !lib->NetSendData) return MESSAGERESULT_MEMORYERROR;
	return (lib->NetSendData)(service, remoteUuid, data, result, bt);
}

Bool NetRenderCacheGet(NetRenderDocumentContext* context, Bool isServer, Int32 cacheID, void* &data, Int32 &size)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, NetRenderCacheGet));
	if (!lib || !lib->NetRenderCacheGet) return false;
	return (lib->NetRenderCacheGet)(context, isServer, cacheID, data, size);
}

Bool NetRenderCacheGetTask(NetRenderDocumentContext* context, Bool isServer, Int32 cacheID, Int32 &taskID, Int32 &taskSubdivisions)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, NetRenderCacheGetTask));
	if (!lib || !lib->NetRenderCacheGetTask) return false;
	return (lib->NetRenderCacheGetTask)(context, isServer, cacheID, taskID, taskSubdivisions);
}

Bool NetRenderCacheSendTask(NetRenderDocumentContext* context, Bool isServer, Int32 cacheID, Int32 taskID, void *data, Int32 size, Bool progress)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, NetRenderCacheSendTask));
	if (!lib || !lib->NetRenderCacheSendTask) return false;
	return (lib->NetRenderCacheSendTask)(context, isServer, cacheID, taskID, data, size, progress);
}

Bool NetRenderCacheProgress(NetRenderDocumentContext* context, Int32 cacheID, Int32 lastIndex, void* &data, Int32 &size, BaseThread* thread)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, NetRenderCacheProgress));
	if (!lib || !lib->NetRenderCacheProgress) return false;
	return (lib->NetRenderCacheProgress)(context, cacheID, lastIndex, data, size, thread);
}

Bool NetRenderCachePrepass(NetRenderDocumentContext* context, Int32 cacheID, Bool &completed)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, NetRenderCachePrepass));
	if (!lib || !lib->NetRenderCachePrepass) return false;
	return (lib->NetRenderCachePrepass)(context, cacheID, completed);
}

Bool NetRenderGetFileFromServer(NetRenderService* client, const Filename& assetName, const Filename& destination, BaseThread* bt)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, NetRenderGetFileFromServer));
	if (!lib || !lib->NetRenderGetFileFromServer) return false;
	return (lib->NetRenderGetFileFromServer)(client, assetName, destination, bt);
}

NetRenderService* GetGlobalNetRenderService()
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetGlobalNetRenderService));
	if (!lib || !lib->GetGlobalNetRenderService) return nullptr;
	return (lib->GetGlobalNetRenderService)();
}

String GetMachineDescription(NetRenderService* service, Machine* m)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetMachineDescription));
	if (!lib || !lib->GetMachineDescription) return String();
	return (lib->GetMachineDescription)(service, m);
}

String VerificationBitToString(VERIFICATIONBIT state)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, VerificationBitToString));
	if (!lib || !lib->VerificationBitToString) return String();
	return (lib->VerificationBitToString)(state);
}

String JobCommandToString(JOBCOMMAND state)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, JobCommandToString));
	if (!lib || !lib->JobCommandToString) return String();
	return (lib->JobCommandToString)(state);
}

String GetDebugStringOfMachine(Machine* m)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetDebugStringOfMachine));
	if (!lib || !lib->GetDebugStringOfMachine) return String();
	return (lib->GetDebugStringOfMachine)(m);
}

String NetRenderService::GetName() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetName));
	if (!lib || !lib->GetName) return String();
	return (((NetRenderService*)this)->*(lib->GetName))();
}

Bool NetRenderService::IsRunning()
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, IsRunning));
	if (!lib || !lib->IsRunning) return false;
	return (((NetRenderService*)this)->*(lib->IsRunning))();
}

void NetRenderService::GetAllMachineUuids(maxon::BaseArray<C4DUuid>& machineUuids, MACHINELIST list, VERIFICATIONBIT bits, Bool includeLocalMachine, Bool includeZeroConfMachines)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetAllMachineUuids));
	if (!lib || !lib->GetAllMachineUuids) return;
	(((NetRenderService*)this)->*(lib->GetAllMachineUuids))(machineUuids, list, bits, includeLocalMachine, includeZeroConfMachines);
}

UserPool& NetRenderService::GetUserPool()
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetUserPool));
	if (!lib || !lib->GetUserPool) { CriticalStop(); }
	return (((NetRenderService*)this)->*(lib->GetUserPool))();
}

Bool NetRenderService::GetJsonJobs(PyList* list) const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetJsonJobs));
	if (!lib || !lib->GetJsonJobs) { CriticalStop(); }
	return (((NetRenderService*)this)->*(lib->GetJsonJobs))(list);
}

RenderJob* NetRenderService::FindRenderJob(const C4DUuid& jobUuid, Bool lookInServerList) const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, FindRenderJob));
	if (!lib || !lib->FindRenderJob) return nullptr;
	return (((NetRenderService*)this)->*(lib->FindRenderJob))(jobUuid, lookInServerList);
}

MachineGroup* NetRenderService::GetOnlineHead() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetOnlineHead));
	if (!lib || !lib->GetOnlineHead) return nullptr;
	return (((NetRenderService*)this)->*(lib->GetOnlineHead))();
}

MachineGroup* NetRenderService::GetOfflineHead() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetOfflineHead));
	if (!lib || !lib->GetOfflineHead) return nullptr;
	return (((NetRenderService*)this)->*(lib->GetOfflineHead))();
}

Machine* NetRenderService::GetFirstOnline() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetFirstOnline));
	if (!lib || !lib->GetFirstOnline) return nullptr;
	return (((NetRenderService*)this)->*(lib->GetFirstOnline))();
}

Machine* NetRenderService::GetFirstOffline() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetFirstOffline));
	if (!lib || !lib->GetFirstOffline) return nullptr;
	return (((NetRenderService*)this)->*(lib->GetFirstOffline))();
}

Machine* NetRenderService::FindMachine(const C4DUuid& uid, MACHINELIST list, VERIFICATIONBIT bits) const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, FindMachine));
	if (!lib || !lib->FindMachine) return nullptr;
	return (((NetRenderService*)this)->*(lib->FindMachine))(uid, list, bits);
}

GeRWSpinlock& NetRenderService::GetMachineLock()
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetMachineLock));
	return (((NetRenderService*)this)->*(lib->GetMachineLock))();
}

const C4DUuid NetRenderService::GetUuid() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetUuid2));
	if (!lib || !lib->GetUuid2) return C4DUuid();
	return (((NetRenderService*)this)->*(lib->GetUuid2))();
}

void NetRenderService::GetMacAddress(maxon::BaseArray<UChar>& macAddress) const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetMacAddress2));
	if (!lib || !lib->GetMacAddress2) return;
	return (((NetRenderService*)this)->*(lib->GetMacAddress2))(macAddress);
}

void NetRenderService::GetGlobalSelectedMachines(maxon::BaseArray<C4DUuid>& machines, Bool& atLeastOneMachineOnline)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetGlobalSelectedMachines));
	if (!lib || !lib->GetGlobalSelectedMachines) return;
	(((NetRenderService*)this)->*(lib->GetGlobalSelectedMachines))(machines, atLeastOneMachineOnline);
}

Int32 NetRenderService::GetInternalPort() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetInternalPort));
	if (!lib || !lib->GetUuid2) return 0;
	return (((NetRenderService*)this)->*(lib->GetInternalPort))();
}

Int32 NetRenderService::GetExternalPort() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetExternalPort));
	if (!lib || !lib->GetExternalPort) return 0;
	return (((NetRenderService*)this)->*(lib->GetExternalPort))();
}

void NetRenderService::CopyClientTasksFrom(maxon::BaseArray<Task>& task)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, CopyClientTasksFrom));
	if (!lib || !lib->CopyClientTasksFrom) return;
	(((NetRenderService*)this)->*(lib->CopyClientTasksFrom))(task);
}

Repository& NetRenderService::GetRepository()
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetRepository));
	if (!lib || !lib->GetRepository) { CriticalStop(); }
	return (((NetRenderService*)this)->*(lib->GetRepository))();
}

Bool NetRenderService::GetGlobalSelected(maxon::BaseArray<C4DUuid>& machines)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetGlobalSelected2));
	if (!lib || !lib->GetGlobalSelected2) return false;
	return (((NetRenderService*)this)->*(lib->GetGlobalSelected2))(machines);
}

CREATEJOBRESULT NetRenderService::CreateRenderJob(const String& docName, C4DUuid& jobUuid, RENDERJOBCREATOR creator, const C4DUuid& userUuid, BaseThread* bt, Filename* watchFolderName)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, CreateRenderJob));
	if (!lib || !lib->CreateRenderJob) return (CREATEJOBRESULT)0;
	return (((NetRenderService*)this)->*(lib->CreateRenderJob))(docName, jobUuid, creator, userUuid, bt, watchFolderName);
}

RENDERRESULT NetRenderService::StartRendering(THREADMODE mode, BaseDocument* doc, const C4DUuid& jobUuid, BaseThread* bt)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, StartRendering));
	if (!lib || !lib->StartRendering) return (RENDERRESULT)0;
	return (((NetRenderService*)this)->*(lib->StartRendering))(mode, doc, jobUuid, bt);
}

RENDERRESULT NetRenderService::InitRendering(BaseDocument* doc, const BaseContainer& rdata, const C4DUuid& jobUuid, NETRENDERFLAGS flags, PictureViewer* pv, const BaseContainer& machines, MultipassBitmap* bmp, ProgressHook* prog, WriteProgressHook* wprog, void* context, Bool* useFrameNumberAsSuffix, Filename* dispname, const maxon::BaseArray<Bool>* renderTasks)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, InitRendering));
	if (!lib || !lib->InitRendering) return RENDERRESULT_OUTOFMEMORY;
	return (((NetRenderService*)this)->*(lib->InitRendering))(doc, rdata, jobUuid, flags, pv, machines, bmp, prog, wprog, context, useFrameNumberAsSuffix, dispname, renderTasks);
}

Bool NetRenderService::VerifyServerOnClient(THREADMODE mode, const C4DUuid& machineUuid, const String& securityToken, Bool setClientAsGlobalSelected, Bool doLock, Int32 waitUntilExecutionInMs)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, VerifyServerOnClient));
	if (!lib || !lib->VerifyServerOnClient) return false;
	return (((NetRenderService*)this)->*(lib->VerifyServerOnClient))(mode, machineUuid, securityToken, setClientAsGlobalSelected, doLock, waitUntilExecutionInMs);
}

Bool NetRenderService::DeleteRenderJob(const C4DUuid& jobUuid, Bool informClients)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, DeleteRenderJob));
	if (!lib || !lib->DeleteRenderJob) return false;
	return (((NetRenderService*)this)->*(lib->DeleteRenderJob))(jobUuid, informClients);
}

void NetRenderService::NetConsoleOutput(maxon::OUTPUT flags, const String& value)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, NetConsoleOutput));
	if (!lib || !lib->NetConsoleOutput) return;
	return (((NetRenderService*)this)->*(lib->NetConsoleOutput))(flags, value);
}

String NetRenderService::GetCurrentJobCommandAsString()
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetCurrentJobCommandAsString));
	if (!lib || !lib->GetCurrentJobCommandAsString) return String();
	return (((NetRenderService*)this)->*(lib->GetCurrentJobCommandAsString))();
}

RenderJob* NetRenderService::GetActive() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetActive));
	if (!lib || !lib->GetActive) return nullptr;
	return (((NetRenderService*)this)->*(lib->GetActive))();
}

GeRWSpinlock& NetRenderService::GetClientRenderJobLock()
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetClientRenderJobLock));
	if (!lib || !lib->GetClientRenderJobLock) CriticalStop();
	return (((NetRenderService*)this)->*(lib->GetClientRenderJobLock))();
}

const C4DUuid Machine::GetUuid() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetUuid));
	if (!lib || !lib->GetUuid) return C4DUuid();
	return (((Machine*)this)->*(lib->GetUuid))();
}

Bool Machine::GetGlobalSelected() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetGlobalSelected));
	if (!lib || !lib->GetGlobalSelected) return false;
	return (((Machine*)this)->*(lib->GetGlobalSelected))();
}

void Machine::SetGlobalSelected(Bool globalSelected)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, SetGlobalSelected));
	if (!lib || !lib->SetGlobalSelected) return;
	(((Machine*)this)->*(lib->SetGlobalSelected))(globalSelected);
}

String Machine::GetFullyQualifiedDomainName(Bool* isPrivate) const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetFullyQualifiedDomainName));
	if (!lib || !lib->GetFullyQualifiedDomainName) return String();
	return (((Machine*)this)->*(lib->GetFullyQualifiedDomainName))(isPrivate);
}

void Machine::ClearVerificationBit(VERIFICATIONBIT state)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, ClearVerificationBit));
	if (!lib || !lib->ClearVerificationBit) return;
	return (((Machine*)this)->*(lib->ClearVerificationBit))(state);
}

Bool Machine::GetVerificationBit(VERIFICATIONBIT state) const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetVerificationBit));
	if (!lib || !lib->GetVerificationBit) return false;
	return (((Machine*)this)->*(lib->GetVerificationBit))(state);
}

void Machine::SetVerificationBit(VERIFICATIONBIT state)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, SetVerificationBit));
	if (!lib || !lib->SetVerificationBit) return;
	return (((Machine*)this)->*(lib->SetVerificationBit))(state);
}

void Machine::SetUuid(const C4DUuid& uid)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, SetUuid));
	if (!lib || !lib->GetUuid) return;
	(((Machine*)this)->*(lib->SetUuid))(uid);
}

void Machine::SetMacAddress(const maxon::BaseArray<UChar>& macAddress)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, SetMacAddress));
	if (!lib || !lib->SetMacAddress) return;
	(((Machine*)this)->*(lib->SetMacAddress))(macAddress);
}

void Machine::GetMacAddress(maxon::BaseArray<UChar>& macAddress) const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetMacAddress));
	if (!lib || !lib->GetMacAddress) return;
	return (((Machine*)this)->*(lib->GetMacAddress))(macAddress);
}

Vector Machine::GetColor(const Vector* bgColor) const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetColor));
	if (!lib || !lib->GetColor) return Vector();
	return (((Machine*)this)->*(lib->GetColor))(bgColor);
}

void Machine::SetColor(const Vector& color)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, SetColor));
	if (!lib || !lib->SetColor) return;
	(((Machine*)this)->*(lib->SetColor))(color);
}

void Machine::FoundViaZeroConf(Bool foundViaZeroConf)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, FoundViaZeroConf));
	if (!lib || !lib->FoundViaZeroConf) return;
	(((Machine*)this)->*(lib->FoundViaZeroConf))(foundViaZeroConf);
}

Bool Machine::FoundViaZeroConf() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, FoundViaZeroConf2));
	if (!lib || !lib->FoundViaZeroConf2) return false;
	return (((Machine*)this)->*(lib->FoundViaZeroConf2))();
}

OPERATINGSYSTEM Machine::GetOperatingSystem()
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetOperatingSystem));
	if (!lib || !lib->GetOperatingSystem) return (OPERATINGSYSTEM)0;
	return (((Machine*)this)->*(lib->GetOperatingSystem))();
}

void Machine::SetOperatingSystem(OPERATINGSYSTEM operatingSystem)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, SetOperatingSystem));
	if (!lib || !lib->SetOperatingSystem) return;
	(((Machine*)this)->*(lib->SetOperatingSystem))(operatingSystem);
}

const BaseContainer& Machine::GetMachineFeatures() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetMachineFeatures));
	return (((Machine*)this)->*(lib->GetMachineFeatures))();
}

void Machine::SetMachineFeatures(const BaseContainer& t_bc)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, SetMachineFeatures));
	if (!lib || !lib->SetMachineFeatures) return;
	(((Machine*)this)->*(lib->SetMachineFeatures))(t_bc);
}

JOBCOMMAND Machine::GetCurrentJobCommand(C4DUuid* rendersFor) const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetCurrentJobCommand));
	if (!lib || !lib->GetCurrentJobCommand) return (JOBCOMMAND)0;
	return (((Machine*)this)->*(lib->GetCurrentJobCommand))(rendersFor);
}

Filename Repository::GetRepositoryPath() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetRepositoryPath));
	if (!lib || !lib->GetRepositoryPath) return Filename();
	return (((Repository*)this)->*(lib->GetRepositoryPath))();
}

Filename Repository::GetJobsPath(Bool server) const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetJobsPath));
	if (!lib || !lib->GetJobsPath) return Filename();
	return (((Repository*)this)->*(lib->GetJobsPath))(server);
}

void Repository::SetRepositoryPath(const Filename& repositoryPath)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, SetRepositoryPath));
	if (!lib || !lib->SetRepositoryPath) return;
	return (((Repository*)this)->*(lib->SetRepositoryPath))(repositoryPath);
}

Filename Repository::ConvertRelative2AbsolutePath(RenderJob* job, Asset* asset) const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, ConvertRelative2AbsolutePath));
	if (!lib || !lib->ConvertRelative2AbsolutePath) return Filename();
	return (((Repository*)this)->*(lib->ConvertRelative2AbsolutePath))(job, asset);
}

Bool Repository::ConvertAbsolute2RelativePath(const Filename &absolutePath, RelativeFilename &relativePath, Bool server) const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, ConvertAbsolute2RelativePath));
	if (!lib || !lib->ConvertAbsolute2RelativePath) return false;
	return (((Repository*)this)->*(lib->ConvertAbsolute2RelativePath))(absolutePath, relativePath, server);
}

Asset* RenderJob::GetFirstAsset() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetFirstAsset));
	if (!lib || !lib->GetFirstAsset) return nullptr;
	return (((RenderJob*)this)->*(lib->GetFirstAsset))();
}

Bool UserPool::AddUser(const String& username, const String& password, const String& description, Bool isAdmin)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, AddUser));
	if (!lib || !lib->AddUser) return false;
	return (((UserPool*)this)->*(lib->AddUser))(username, password, description, isAdmin);
}

Bool UserPool::DeleteUser(const String& username)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, DeleteUser));
	if (!lib || !lib->DeleteUser) return false;
	return (((UserPool*)this)->*(lib->DeleteUser))(username);
}

Bool UserPool::ChangePassword(const String& username, const String& oldPassword, const String& newPassword)
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, ChangePassword));
	if (!lib || !lib->ChangePassword) return false;
	return (((UserPool*)this)->*(lib->ChangePassword))(username, oldPassword, newPassword);
}

Bool UserPool::CheckUserCredentials(const String& username, const String& password) const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, ChangePassword));
	if (!lib || !lib->CheckUserCredentials) return false;
	return (((UserPool*)this)->*(lib->CheckUserCredentials))(username, password);
}

String NetRenderData::GetName() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetName2));
	if (!lib || !lib->GetName2) return String();
	return (((NetRenderData*)this)->*(lib->GetName2))();
}


Bool NetRenderData::IsSingleFrameRendering() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, IsSingleFrameRendering));
	if (!lib || !lib->IsSingleFrameRendering) return false;
	return (((NetRenderData*)this)->*(lib->IsSingleFrameRendering))();
}

Int32 NetRenderData::GetRealFps() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetRealFps));
	if (!lib || !lib->GetRealFps) return 0;
	return (((NetRenderData*)this)->*(lib->GetRealFps))();
}

Float NetRenderData::GetFps() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetFps));
	if (!lib || !lib->GetFps) return 0;
	return (((NetRenderData*)this)->*(lib->GetFps))();
}

BaseTime NetRenderData::GetFrameFrom() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetFrameFrom));
	if (!lib || !lib->GetFrameFrom) return BaseTime();
	return (((NetRenderData*)this)->*(lib->GetFrameFrom))();
}

BaseTime NetRenderData::GetFrameTo() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetFrameTo));
	if (!lib || !lib->GetFrameTo) return BaseTime();
	return (((NetRenderData*)this)->*(lib->GetFrameTo))();
}

Int32 NetRenderData::GetWidth() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetWidth));
	if (!lib || !lib->GetWidth) return 0;
	return (((NetRenderData*)this)->*(lib->GetWidth))();
}

Int32  NetRenderData::GetHeight() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetHeight));
	if (!lib || !lib->GetHeight) return 0;
	return (((NetRenderData*)this)->*(lib->GetHeight))();
}

Int32 NetRenderData::GetFrameRange() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetFrameRange));
	if (!lib || !lib->GetFrameRange) return 0;
	return (((NetRenderData*)this)->*(lib->GetFrameRange))();
}

Int32 NetRenderData::GetNameFormat() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetNameFormat));
	if (!lib || !lib->GetNameFormat) return 0;
	return (((NetRenderData*)this)->*(lib->GetNameFormat))();
}

Int32 NetRenderData::GetFrameStep() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetFrameStep));
	if (!lib || !lib->GetFrameStep) return 0;
	return (((NetRenderData*)this)->*(lib->GetFrameStep))();
}

BaseContainer NetRenderData::GetData() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetData));
	if (!lib || !lib->GetData) return BaseContainer();
	return (((NetRenderData*)this)->*(lib->GetData))();
}

Bool NetRenderData::UseFrameNumberAsSuffix() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, UseFrameNumberAsSuffix));
	if (!lib || !lib->UseFrameNumberAsSuffix) return false;
	return (((NetRenderData*)this)->*(lib->UseFrameNumberAsSuffix))();
}

Bool NetRenderData::ShowHud() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, ShowHud));
	if (!lib || !lib->ShowHud) return false;
	return (((NetRenderData*)this)->*(lib->ShowHud))();
}

Bool NetRenderData::SaveImage() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, SaveImage));
	if (!lib || !lib->SaveImage) return false;
	return (((NetRenderData*)this)->*(lib->SaveImage))();
}

Int32 NetRenderData::GetImageFormat() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetImageFormat));
	if (!lib || !lib->GetImageFormat) return 0;
	return (((NetRenderData*)this)->*(lib->GetImageFormat))();
}

Filename NetRenderData::GetImageFilename() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetImageFilename));
	if (!lib || !lib->GetImageFilename) return Filename();
	return (((NetRenderData*)this)->*(lib->GetImageFilename))();
}

Filename NetRenderData::GetImageAbsResultFolder() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetImageAbsResultFolder));
	if (!lib || !lib->GetImageAbsResultFolder) return Filename();
	return (((NetRenderData*)this)->*(lib->GetImageAbsResultFolder))();
}

Bool NetRenderData::GetImageFormatIsMovie() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetImageFormatIsMovie));
	if (!lib || !lib->GetImageFormatIsMovie) return false;
	return (((NetRenderData*)this)->*(lib->GetImageFormatIsMovie))();
}


Bool NetRenderData::SaveMultipass() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, SaveMultipass));
	if (!lib || !lib->SaveMultipass) return false;
	return (((NetRenderData*)this)->*(lib->SaveMultipass))();
}

Int32 NetRenderData::GetMultipassImageFormat() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetMultipassImageFormat));
	if (!lib || !lib->GetMultipassImageFormat) return false;
	return (((NetRenderData*)this)->*(lib->GetMultipassImageFormat))();
}

Filename NetRenderData::GetMultipassFilename() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetMultipassFilename));
	if (!lib || !lib->GetMultipassFilename) return Filename();
	return (((NetRenderData*)this)->*(lib->GetMultipassFilename))();
}

Filename NetRenderData::GetMultipassAbsResultFolder() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetMultipassAbsResultFolder));
	if (!lib || !lib->GetMultipassAbsResultFolder) return Filename();
	return (((NetRenderData*)this)->*(lib->GetMultipassAbsResultFolder))();
}

Bool NetRenderData::GetMultipassFormatIsMovie() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetMultipassFormatIsMovie));
	if (!lib || !lib->GetMultipassFormatIsMovie) return false;
	return (((NetRenderData*)this)->*(lib->GetMultipassFormatIsMovie))();
}

Bool NetRenderData::GetMultipassSaveMultilayer() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetMultipassSaveMultilayer));
	if (!lib || !lib->GetMultipassSaveMultilayer) return false;
	return (((NetRenderData*)this)->*(lib->GetMultipassSaveMultilayer))();
}

Bool NetRenderData::ShowTextureError() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, ShowTextureError));
	if (!lib || !lib->ShowTextureError) return false;
	return (((NetRenderData*)this)->*(lib->ShowTextureError))();
}

NETRENDERFLAGS NetRenderData::GetFlags() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetFlags));
	if (!lib || !lib->GetFlags) return NETRENDERFLAGS_0;
	return (((NetRenderData*)this)->*(lib->GetFlags))();
}

Filename NetRenderData::GetB3dTempFolder() const
{
	NetLibrary *lib = CheckNetRenderLib(LIBOFFSET(NetLibrary, GetB3dTempFolder));
	if (!lib || !lib->GetB3dTempFolder) return Filename();
	return (((NetRenderData*)this)->*(lib->GetB3dTempFolder))();
}

#endif
