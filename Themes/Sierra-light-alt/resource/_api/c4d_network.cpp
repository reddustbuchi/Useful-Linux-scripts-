#include "operatingsystem.h"
#include "c4d_general.h"
#include "c4d_network.h"
#include "c4d_basecontainer.h"

const IpAddrPort& IpConnection::GetRemoteAddr() const
{
	return IpCall(GetRemoteAddr) ();
}

Int64 IpConnection::GetTransferedBytes() const
{
	return IpCall(GetTransferedBytes) ();
}

const IpAddrPort& IpConnection::GetHostAddr() const
{
	return IpCall(GetHostAddr) ();
}


// only for inherited sdk init!
IpAddr::IpAddr(_DONTCONSTRUCT v)
{
}

IpAddr::IpAddr()
{
	IpCall(SDKAlloc)();
}

IpAddr::IpAddr(const IpAddr& a)
{
	IpCall(SDKAlloc2)(a);
}

IpAddr::IpAddr(UChar a, UChar b, UChar c, UChar d)
{
	IpCall(SDKAlloc)();
	IpCall(SetIPv4)(a, b, c, d);
}

IpAddr::IpAddr(Int16 x1, Int16 x2, Int16 x3, Int16 x4, Int16 x5, Int16 x6, Int16 x7, Int16 x8)
{
	IpCall(SDKAlloc)();
	IpCall(SetIPv6)(x1, x2, x3, x4, x5, x6, x7, x8);
}

IpAddr::~IpAddr()
{
	IpCall(SDKFree)();
}

void IpAddr::Flush()
{
	IpCall(Flush)();
}

Bool IpAddr::SetIPv4(UChar a, UChar b, UChar c, UChar d)
{
	return IpCall(SetIPv4)(a, b, c, d);
}

Bool IpAddr::SetIPv6(Int16 x1, Int16 x2, Int16 x3, Int16 x4, Int16 x5, Int16 x6, Int16 x7, Int16 x8)
{
	return IpCall(SetIPv6)(x1, x2, x3, x4, x5, x6, x7, x8);
}

Bool IpAddr::GetIPv4(UChar& a, UChar& b, UChar& c, UChar& d) const
{
	return IpCall(GetIPv4)(a, b, c, d);
}

Bool IpAddr::GetIPv6(Int16& x1, Int16& x2, Int16& x3, Int16& x4, Int16& x5, Int16& x6, Int16& x7, Int16& x8) const
{
	return IpCall(GetIPv6)(x1, x2, x3, x4, x5, x6, x7, x8);
}

Bool IpAddr::IsPrivateAddress() const
{
	return IpCall(IsPrivateAddress)();
}

int IpAddr::GetNativeProtocol() const
{
	return IpCall(GetNativeProtocol)();
}

Bool IpAddr::CopyTo(IpAddr& adr) const
{
	return IpCall(CopyTo)(adr);
}

Bool IpAddr::IsEmpty() const
{
	return IpCall(IsEmpty)();
}

Bool IpAddr::Write(HyperFile* hf) const
{
	return IpCall(Write)(hf);
}

Bool IpAddr::Read(HyperFile* hf)
{
	return IpCall(Read)(hf);
}

Bool IpAddr::Compare(const IpAddr& adr) const
{
	return IpCall(Compare)(adr);
}

String IpAddr::GetString(Int port) const
{
	return IpCall(GetString)(port);
}

PROTOCOL IpAddr::GetProtocol() const
{
	return IpCall(GetProtocol)();
}

const GeSockAddrIn* IpAddr::GetGeSockAddrIn() const
{
	return IpCall(GetGeSockAddrIn)();
}

const IpAddrPort IpAddr::operator + (Int port)
{
	return IpAddrPort(*this, port);
}

const IpAddr& IpAddr::operator =(const IpAddr& source)
{
	source.CopyTo(*this);
	return *this;
}


IpAddrPort::IpAddrPort() : IpAddr(DC)
{
	IpCall(SDKAllocPort)();
}

IpAddrPort::IpAddrPort(const IpAddr& a, Int port) : IpAddr(DC)
{
	IpCall(SDKAllocPort2)(a, port);
}

IpAddrPort::IpAddrPort(UChar a, UChar b, UChar c, UChar d, Int port) : IpAddr(DC)
{
	IpCall(SDKAllocPort)();
	IpCall(SetIPv4)(a, b, c, d);
	IpCall(SetPort)(port);
}

IpAddrPort::IpAddrPort(Int16 x1, Int16 x2, Int16 x3, Int16 x4, Int16 x5, Int16 x6, Int16 x7, Int16 x8, Int port) : IpAddr(DC)
{
	IpCall(SDKAllocPort)();
	IpCall(SetIPv6)(x1, x2, x3, x4, x5, x6, x7, x8);
	IpCall(SetPort)(port);
}

Bool IpAddrPort::Write(HyperFile* hf) const
{
	return IpCall(WriteAP)(hf);
}

Bool IpAddrPort::Read(HyperFile* hf)
{
	return IpCall(ReadAP)(hf);
}

Bool IpAddrPort::IsValid() const
{
	return IpCall(IsValid2)();
}

String IpAddrPort::GetString(Bool getPort) const
{
	return IpCall(GetStringAP)(getPort);
}

void IpAddrPort::SetPort(Int port)
{
	IpCall(SetPort)(port);
}

Int IpAddrPort::GetPort() const
{
	return IpCall(GetPort)();
}

Bool IpAddrPort::operator ==(const IpAddrPort& a) const
{
	return IpCall(CompareAP)(a);
}

Bool IpAddrPort::operator !=(const IpAddrPort& a) const
{
	return IpCall(CompareAP)(a);
}


Int NetworkInterface::GetInterfaceIndex() const
{
	return IpCall(GetInterfaceIndex) ();
}

String NetworkInterface::GetInterfaceName() const
{
	return IpCall(GetInterfaceName) ();
}

void NetworkInterface::GetMacAddress(maxon::BaseArray<UChar>& macAddress) const
{
	return IpCall(GetMacAddress) (macAddress);
}

String NetworkInterface::GetDescription() const
{
	return IpCall(GetDescription) ();
}

Int NetworkInterface::GetCountAddress() const
{
	return IpCall(GetCountAddress) ();
}

Bool NetworkInterface::IsLoopback() const
{
	return IpCall(IsLoopback) ();
}

IpAddr NetworkInterface::GetIpAddress(Int i) const
{
	return IpCall(GetIpAddress) (i);
}

IpAddr NetworkInterface::GetBroadcastAddress(Int i) const
{
	return IpCall(GetBroadcastAddress) (i);
}

Bool NetworkInterface::Append(const IpAddr& ipAddr, const IpAddr& broadcastAddress, const IpAddr& subnetMask)
{
	return IpCall(Append) (ipAddr, broadcastAddress, subnetMask);
}

IpAddr NetworkInterface::GetSubnetMask(Int i) const
{
	return IpCall(GetSubnetMask) (i);
}

NetworkInterface* NetworkInterface::GetClone() const
{
	return IpCall(NetworkInterfaceGetClone) ();
}

Bool NetworkInterface::CopyTo(NetworkInterface& networkInterface) const
{
	return IpCall(NetworkInterfaceCopyTo) (networkInterface);
}

BaseContainer NetworkInterface::GetCustomData() const
{
	return IpCall(GetCustomData) ();
}

void NetworkInterface::SetCustomData(const BaseContainer& customData)
{
	return IpCall(SetCustomData) (customData);
}

Bool NetworkInterface::Write(HyperFile* hf) const
{
	return IpCall(NetworkInterfaceWrite) (hf);
}

Bool NetworkInterface::Read(HyperFile* hf)
{
	return IpCall(NetworkInterfaceRead) (hf);
}

IpConnection*	GeIpOpenListener(const IpAddrPort& adr, BaseThread* thread, Int timeout, Bool useNagleAlgorithm, Int* ferr)
{
	return NetCall(IpOpenListener) (adr, thread, timeout, useNagleAlgorithm, ferr);
}

IpConnection*	GeIpOpenListener(const String& adr, BaseThread* thread, Int timeout, Bool useNagleAlgorithm, Int* ferr)
{
	return NetCall(IpOpenListenerString) (adr, thread, timeout, useNagleAlgorithm, ferr);
}

ZeroConfBrowser* StartZeroConfBrowser(const String& serviceType, ZeroConfBrowserCallback browseCallback, ZeroConfBrowserResolvedCallback resolveCallback, void* context)
{
	return NetCall(StartZeroConfBrowser) (serviceType, browseCallback, resolveCallback, context, true);
}

Bool GetBonjourVersion(Int& versionNumber, Int& revisionNumber, Bool& isRunning)
{
	return NetCall(GetBonjourVersion) (versionNumber, revisionNumber, isRunning);
}

void StopZeroConfBrowser(ZeroConfBrowser* browser)
{
	return NetCall(StopZeroConfBrowser) (browser);
}

ZeroConfService* RegisterZeroConfService(String serviceName, const String& serviceType, Int lInterface, Int port, const String& domainName)
{
	return NetCall(RegisterZeroConfService) (serviceName, serviceType, lInterface, port, domainName, true);
}

void DeregisterZeroConfService(ZeroConfService* service)
{
	NetCall(DeregisterZeroConfService) (service);
}

Bool ZeroConfService::SetTXTRecord(const String* keys, const String* values, Int cnt)
{
	return NetCall(SetTXTRecord) (this, keys, values, cnt);
}

Bool ZeroConfService::RemoveTXTRecord()
{
	return NetCall(RemoveTXTRecord) (this);
}

Bool WakeOnLan(const maxon::BaseArray<UChar>& macAddress, const IpAddr& broadcast)
{
	return NetCall(WakeOnLan) (macAddress, broadcast);
}

Bool GetMacAddress(maxon::BaseArray<UChar>& macAddress)
{
	return NetCall(GetMacAddress2) (macAddress);
}

String GetHostname()
{
	return NetCall(GetHostname)();
}

String GetHostname(const IpAddr& ipAddr)
{
	return NetCall(GetHostname2)(ipAddr);
}

Int GetInterfaceIndex(const String& identifier)
{
	return NetCall(GetInterfaceIndex2) (identifier);
}

Bool GetAllNetworkInterfaces(maxon::BaseArray<NetworkInterface*>& networkInterfaces)
{
	return NetCall(GetAllNetworkInterfaces) (networkInterfaces);
}

NetworkInterface* GetBestNetworkInterface(PROTOCOL protocol)
{
	return NetCall(GetBestNetworkInterface) (protocol);
}

IpConnection*	GeIpWaitForIncoming(IpConnection* listener, BaseThread* connection, Int* error)
{
	return NetCall(IpWaitForIncoming) (listener, connection, error);
}

IpConnection* GeIpOpenOutgoing(const IpAddrPort& adr, BaseThread* thread, Int initialTimeout, Int timeout, Bool useNagleAlgorithm, Int* error)
{
	return NetCall(IpOpenOutgoing) (adr, thread, initialTimeout, timeout, useNagleAlgorithm, error);
}

IpConnection* GeIpOpenOutgoing(const String& adr, BaseThread* thread, Int initialTimeout, Int timeout, Bool useNagleAlgorithm, Int* error)
{
	return NetCall(IpOpenOutgoingString) (adr, thread, initialTimeout, timeout, useNagleAlgorithm, error);
}

RESOLVERESULT ResolveHostname(const String& address, PROTOCOL protocol, maxon::BaseArray<IpAddr>& addrs, Bool firstMatch, Bool forceResolve)
{
	return NetCall(ResolveHostname) (address, protocol, addrs, firstMatch, forceResolve);
}

Bool SplitAddress(String address, String* scheme, String* host, Int* port)
{
	return NetCall(SplitAddress) (address, scheme, host, port);
}

Bool GetIpAddress(const String& address, IpAddr& a, Bool resolve, Bool forceResolve)
{
	return NetCall(GetIpAddress2) (address, a, resolve, forceResolve);
}

Bool GetIpAddress(const String& address, IpAddrPort& a, Bool resolve, Bool forceResolve)
{
	return NetCall(GetIpAddress3) (address, a, resolve, forceResolve);
}

void GeIpCloseConnection(IpConnection*& ipc)
{
	if (ipc)
		NetCall(IpCloseConnection) (ipc);
	ipc = nullptr;
}

void GeIpKillConnection(IpConnection*& ipc)
{
	NetCall(IpKillConnection) (ipc);
}

Int GeIpBytesInInputBuffer(IpConnection* ipc)
{
	return NetCall(IpBytesInInputBuffer) (ipc);
}

Int GeIpReadBytes(IpConnection* ipc, void* buf, Int size)
{
	return NetCall(IpReadBytes) (ipc, buf, size);
}

Int GeIpSendBytes(IpConnection* ipc, const void* buf, Int size)
{
	return NetCall(IpSendBytes) (ipc, (void*)buf, size);
}
