/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DNETWORK_H_
#define __C4DNETWORK_H_

#ifndef __API_INTERN__
	#include "c4d_string.h"
	#include "c4d_basecontainer.h"
	#include "ge_prepass.h"
#else
	#include "ge_string.h"
#endif

#include "ge_math.h"
#ifdef USE_API_MAXON
	#include "basearray.h"
#else
	#include "c4d_misc/datastructures/basearray.h"
#endif

class IpAddrPort;
class ZeroConfTask;
class IpConnection;

#ifndef __PC
	#define INVALID_SOCKET -1
#endif

#define NETWORK_INTERFACE_ANY	0

#ifndef AF_INET
	#define AF_INET 2
#endif

#ifndef AF_INET6
	#define AF_INET6 30
#endif

//--Common Network API--

#define NetCall(fnc) (*C4DOS.Ne->fnc)
#define IpCall(fnc)	 (this->*C4DOS.Ne->fnc)

#define IPV4_SIZE 4		//IPv4 32-Bit
#define IPV6_SIZE 16	//IPv6 128-Bit

union GeSockAddrIn
{
	UChar ipv4[IPV4_SIZE];
	UChar ipv6[IPV6_SIZE];
};

class IpAddr
{
protected:
	IpAddr(_DONTCONSTRUCT v);

public:
	IpAddr();
	IpAddr(const IpAddr& a);
	IpAddr(UChar a, UChar b, UChar c, UChar d);
	IpAddr(Int16 x1, Int16 x2, Int16 x3, Int16 x4, Int16 x5, Int16 x6, Int16 x7, Int16 x8);

	~IpAddr();

	void Flush();

	Bool SetIPv4(UChar a, UChar b, UChar c, UChar d);
	Bool SetIPv6(Int16 x1, Int16 x2, Int16 x3, Int16 x4, Int16 x5, Int16 x6, Int16 x7, Int16 x8);

	Bool GetIPv4(UChar& a, UChar& b, UChar& c, UChar& d) const;
	Bool GetIPv6(Int16& x1, Int16& x2, Int16& x3, Int16& x4, Int16& x5, Int16& x6, Int16& x7, Int16& x8) const;

	Bool IsEmpty() const;
	Bool Compare(const IpAddr& adr) const;

	int GetNativeProtocol() const;	//AF_INET, AF_INET6

	Bool Write(HyperFile* hf) const;
	Bool Read(HyperFile* hf);

	Bool CopyTo(IpAddr& adr) const;

	Bool IsPrivateAddress() const;

	Bool IsValid() const;
	String GetString(Int port = NOTOK) const;
	PROTOCOL GetProtocol() const;

	const IpAddr& operator =(const IpAddr& source);

	Bool operator ==(const IpAddr& adr) const { return Compare(adr); }
	Bool operator !=(const IpAddr& adr) const { return !Compare(adr); }

	const IpAddrPort operator +(Int port);

	const GeSockAddrIn* GetGeSockAddrIn() const;

private:
	C4D_RESERVE_PRIVATE_TYPE(GeSockAddrIn, dummy1);
	C4D_RESERVE_PRIVATE_TYPE(PROTOCOL, dummy2);
};

class IpAddrPort : public IpAddr
{
	typedef IpAddr SUPER;

public:
	IpAddrPort();
	IpAddrPort(const IpAddr& a, Int port);
	IpAddrPort(UChar a, UChar b, UChar c, UChar d, Int port);
	IpAddrPort(Int16 x1, Int16 x2, Int16 x3, Int16 x4, Int16 x5, Int16 x6, Int16 x7, Int16 x8, Int port);

	Bool Write(HyperFile* hf) const;
	Bool Read(HyperFile* hf);

	Bool IsValid() const;
	String GetString(Bool getPort = true) const;

	void SetPort(Int port);
	Int GetPort() const;

	Bool operator ==(const IpAddrPort& a) const;
	Bool operator !=(const IpAddrPort& a) const;

private:
	C4D_RESERVE_PRIVATE_TYPE(Int, dummy3);
};

class NetworkInterface
{
public:
	void SetInterfaceIndex(Int interfaceIndex);
	Int GetInterfaceIndex() const;

	void SetInterfaceName(const String& interfaceName);
	String GetInterfaceName() const;

	void GetMacAddress(maxon::BaseArray<UChar>& macAddress) const;

	String GetDescription() const;
	void SetDescription(const String& description);

	Bool IsLoopback() const;
	void SetLoopback(Bool isLoopback);

	Int GetCountAddress() const;

	Bool Append(const IpAddr& ipAddr, const IpAddr& broadcastAddress, const IpAddr& subnetMask);

	IpAddr GetIpAddress(Int i) const;
	IpAddr GetBroadcastAddress(Int i) const;
	IpAddr GetSubnetMask(Int i) const;

	Bool Write(HyperFile* hf) const;
	Bool Read(HyperFile* hf);
	Bool CopyTo(NetworkInterface& networkInterface) const;

	BaseContainer GetCustomData() const;
	void SetCustomData(const BaseContainer& customData);

	NetworkInterface* GetClone() const;

	static NetworkInterface* Alloc() { return NetCall(NetworkInterfaceAlloc) (); }
	static void Free(NetworkInterface*& p) { NetCall(NetworkInterfaceFree) (p); }

private:
	NetworkInterface();
	~NetworkInterface();
};

class ZeroConfService
{
public:
	Bool SetTXTRecord(const String* keys, const String* values, Int cnt);
	Bool RemoveTXTRecord();
};

class IpConnection
{
public:
	const IpAddrPort& GetRemoteAddr() const;
	const IpAddrPort& GetHostAddr() const;

	Int64 GetTransferedBytes() const;
};

//----------------------------------------------------
/// Wakes a computer up by WOL (Wake-On-LAN). Currently only IPv4 is supported. To get
/// WOL to work, a broadcast message on port '9' will be sent.
//
/// @return									true on success if the message was sent, otherwise false
/// @param macAddress				mac address of the target machine
/// @param broadcastAddress	broadcast address where the message should be send to
//----------------------------------------------------
Bool WakeOnLan(const maxon::BaseArray<UChar>& macAddress, const IpAddr& broadcast);

//---------------------------------------------------------------
/// Get the mac address of the machine. When this function returns false an error occurred, but then macAddress is filled at least with a
/// random-generated macAddress. The random-generated mac address will be changed after a restart of the host application.
/// @return								true on success, otherwise false
/// @param macAddress			filled with the mac address
/// @param bufSize				buffer size, maximum of length 6 bytes
//---------------------------------------------------------------
Bool GetMacAddress(maxon::BaseArray<UChar>& macAddress);

//---------------------------------------------------------------------------
/// Returns the best network interface to the specified protocol.
/// @return												true if a network interface was found
/// @param protocol								specified protocol
/// @param[out] networkInterface	assigned the found network interface
//---------------------------------------------------------------------------
NetworkInterface* GetBestNetworkInterface(PROTOCOL protocol = PROTOCOL_IPV4);

//----------------------------------------------------------
/// Returns all current active network interface objects.
/// @param[out] networkInterfaces							Assigned all network interfaces
//----------------------------------------------------------
Bool GetAllNetworkInterfaces(maxon::BaseArray<NetworkInterface*>& networkInterfaces);

//--------------------------
/// Returns the host name of the local machine.
/// @return			the name
//--------------------------
String GetHostname();

//--------------------------
/// Returns the host name of the given ip address.
/// @return												The host name. Can be empty if the address could not be resolved.
//--------------------------
String GetHostname(const IpAddr& ipAddr);

//----------------------------------------------------------
/// Returns the interface index. The interface name "all" returns 0.
/// @return									The index
/// @param interfaceIndex		The name
//----------------------------------------------------------
Int GetInterfaceIndex(const String& interfaceName);

//-------------------------------------------------------------------------------------------------------------------------
/// Resolves a host name. If the address object can be an ip address object, you should use GetIpAddress(address, a, true) instead.
/// @return							Returns RESOLVERESULT_OK on success, otherwise the resolve operation failed
/// @param address			host name to resolve
/// @param ptype				pass PROTOCOL_IPV4 if the result should just contain IPv4 address, same for PROTOCOL_IPV6 with IPv6 address and PROTOCOL_ALL for all addresses
/// @param[out] addrs		contains the addresses of the host name when the function succeeded
/// @param firstMatch		address array has a maximum size of 1 element
/// @param forceResolve	if false use the DNS cache if the address is a host name and already known. Use true for an automatic mode.
//-------------------------------------------------------------------------------------------------------------------------
RESOLVERESULT ResolveHostname(const String& address, PROTOCOL ptype, maxon::BaseArray<IpAddr>& addrs, Bool firstMatch = true, Bool forceResolve = false);

//-------------------------------------------------------------------------------------
/// Converts a host name, IPv4 or IPv6 address into an ip address object. A port value in the address will be ignored. When the resolve
/// option is enabled, the call blocks and waits for the DNS system when the address is a host name. E.g:
///			address: Sebastians-Macbook-Pro.local (DNS system used, call blocks)
///			address: 192.168.10.1 (no DNS system used, call does not block)
///
/// @return					true on success, otherwise false
/// @param address	IP address or host name. If the string is a host name, resolve must be set to true otherwise the function fails
/// @param[out] a		assigned ip address object.
/// @param resolve	set to true to resolve the address via the DNS system
//-------------------------------------------------------------------------------------
Bool GetIpAddress(const String& address, IpAddr& a, Bool resolve = false, Bool forceResolve = false);

//----------------------------------------------------------------------------
/// Converts a host name, IPv4 or IPv6 address into an ip address object. The address can have a port value. When the resolve option is enabled, the
/// call blocks and waits for the DNS system when the address is a host name. E.g:
///			address: Sebastians-Macbook-Pro.local:1234 (DNS system used, call blocks)
///			address: 192.168.10.1:1234 (no DNS system used, call does not block)

/// @return					true on success, otherwise false
/// @param address	IP address or host name. If the string is a host name, resolve must be set to true otherwise the function fails
/// @param[out] a		assigned IP address object
/// @param resolve	set to true to resolve the address via the DNS system
//----------------------------------------------------------------------------
Bool GetIpAddress(const String& address, IpAddrPort& a, Bool resolve = false, Bool forceResolve = false);

//-------------------------------------------------------------------------------------
/// Split a specified scheme with host name and port into it's components. Can handle IPv4, IPv6 addresses and host names.
/// For instance:
//
//		http://127.0.0.1:8080
//		http://[AB:AB:AB:AB:AB:AB]:1234
//		192.168.10.1
//		Sebastians-Macbook-Pro.local:80
//
/// @address				The host name to split. Can optionally contain a scheme, host and port
/// @scheme					The assigned scheme, can be empty if no scheme was found
/// @host						The assigned address/host name without port scheme and port number.
/// @port						The port, if no port was found port NOTOK is assigned.
//-------------------------------------------------------------------------------------
Bool SplitAddress(String address, String* scheme, String* host, Int* port);

//--------------------------------------------------------------------------------------------------------------------------------------
/// Opens a connection. Supports IPv4.
/// @return										connection object for the outgoing connection. Must be freed with GeIpCloseConnection
/// @param adr								destination address to connect to.
/// @param initialTimeout			timeout in seconds for the initial connection
/// @param timeout						timeout in seconds for receive and send operations
/// @param useNagleAlgorithm	pass true to set the TCP/IP flag for TCP_NODELAY. For more information see: http://msdn.microsoft.com/en-us/library/ms817942.aspx
/// @param error							assigned error if the connection failed
//--------------------------------------------------------------------------------------------------------------------------------------
IpConnection* GeIpOpenOutgoing(const IpAddrPort& adr, BaseThread* thread = nullptr, Int initialTimeout = 30, Int timeout = 10, Bool useNagleAlgorithm = true, Int* error = nullptr);

//--------------------------------------------------------------------------------------------------------------------------------------
/// Opens a connection. Supports IPv4.
/// @return										connection object for the outgoing connection. Must be freed with GeIpCloseConnection
/// @param adr								destination address to connect to (ipv4 address or host name)
/// @param initialTimeout			timeout in seconds for the initial connection
/// @param timeout						timeout in seconds for receive and send operations
/// @param useNagleAlgorithm	pass true to set the TCP/IP flag for TCP_NODELAY. For more information see: http://msdn.microsoft.com/en-us/library/ms817942.aspx
/// @param error							assigned error if the connection failed
//--------------------------------------------------------------------------------------------------------------------------------------
IpConnection* GeIpOpenOutgoing(const String& adr, BaseThread* thread = nullptr, Int initialTimeout = 30, Int timeout = 10, Bool useNagleAlgorithm = true, Int* error = nullptr);

Int GeIpBytesInInputBuffer(IpConnection* ipc);
Int GeIpReadBytes(IpConnection* ipc, void* buf, Int size);
Int GeIpSendBytes(IpConnection* ipc, const void* buf, Int size);
IpConnection* GeIpOpenListener(const IpAddrPort& adr, BaseThread* thread, Int timeout, Bool dontwait, Int* error);
IpConnection* GeIpOpenListener(const String& adr, BaseThread* thread, Int timeout, Bool useNagleAlgorithm, Int* error);
IpConnection* GeIpWaitForIncoming(IpConnection* listener, BaseThread* connection, Int* error);
void GeIpKillConnection(IpConnection*& ipc);
void GeIpCloseConnection(IpConnection*& ipc);

//--ZeroConf API--

//------------------------------------------------------------------
/// Get the version number of the bonjour version.
/// @return												true if Bonjour is installed, otherwise false.
/// @param versionNumber[out]			The main version number of bonjour.
/// @param revisionNumber[out]		The revision number
/// @param isRunning[out]					If the function returns false, isRunning can be true to indicate that the bonjour service is running but this process cannot connect to it.
/// 															This can happen if the process is blocked by a firewall to connect to 127.0.0.1/localhost.
//------------------------------------------------------------------
Bool GetBonjourVersion(Int& versionNumber, Int& revisionNumber, Bool& isRunning);

ZeroConfBrowser* StartZeroConfBrowser(const String& serviceType, ZeroConfBrowserCallback browseCallback, ZeroConfBrowserResolvedCallback resolveCallback, void* context);
void StopZeroConfBrowser(ZeroConfBrowser* browser);

ZeroConfService* RegisterZeroConfService(String serviceName, const String& serviceType, Int lInterface, Int port, const String& domainName = String());
void DeregisterZeroConfService(ZeroConfService* service);

#endif
