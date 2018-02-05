/**
 * <interfacename>CmpRouter</interfacename>
 * <description> 
 *	Interface for the communication router component.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpRouter')

REF_ITF(`CmpCommunicationLibItf.m4')
REF_ITF(`CmpBlkDrvItf.m4')

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 *	Max. number of router instances. If more block driver instances available as configured for router
 *	main and sub nets, then there is created a router instance for each of this available block driver instances
 *  until this limit is reached. If a runtime system has a fixed number of interfaces, then this value
 *  should be set to the max. number of blockdriver instances, which are available on this system.
 *  Allowed value range: 1..15.
 * </description>
 */
#define ROUTERKEY_INT_MAX_ROUTERS								"MaxRouters"
#define ROUTERKEY_INT_MAX_ROUTERS_DEFAULT						7

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 *	Configures the parallel routing feature.
 *  By default there is no communication possible between the router instances. For server implementations
 *  above the router layer (CmpChannelServer or CmpNameServiceServer - typically used in the runtime system) 
 *  this is not necessary at all, because the server implementations listen on all router instances. 
 *  But on client side the implementations (CmpChannelClient or CmpNameServiceClient) are always bound
 *  to the first router instance. This means without the parallel routing feature a communication client
 *  (Gateway, PLCHandler, OPC Server, DataServer, ...) can only communciate to PLCs which are connected to
 *  a mainnet or subnet of the first local router instance of the client.
 *  Another aspect of parallel routing is the package forwarding. On PLCs all block driver instances are assigend
 *  to a mainnet of the router instances. But also on the Gateway there are typically at least a few router instances
 *  available. If a PLC or Gateway should forward a received package to a PLC which is connected to another interface, 
 *  there is also the parallel routing feature needed.
 *  Allowed values: 
 *  0: Parallel routing is completely disabled. Should only be used on PLCs without any client functionality or
 *     to limit the local client communication very hard to the first router instance.  
 *  1: Parallel routing is enabled for forwarding received packages to another interface and also local client
 *     implemantations can communicate to all networks on all router instances. Is typically be used on PLCs
 *     to allow complex PLC networks. Furthermore this was for a long time also the default for the Gateway.
 *  2 (default): Parallel routing is enabled for the local client to let him communicate to all networks on 
 *     all router instances, but received packages are not forwarded to other interfaces. If there are no
 *     special routing requirements, this default value should be used.
 * </description>
 */
#define ROUTERKEY_INT_PARALLEL_ROUTING							"EnableParallelRouting"
#ifndef ROUTERKEY_INT_PARALLEL_ROUTING_DEFAULT
	#define ROUTERKEY_INT_PARALLEL_ROUTING_DEFAULT				2
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 *	Enables/disables loop detection for broadcast packets. 
 *  Should only be disabled for debugging purposes.  
 * </description>
 */
#define ROUTERKEY_INT_LOOP_DETECTION							"EnableLoopDetection"
#define ROUTERKEY_INT_LOOP_DETECTION_DEFAULT					1

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 *	Name of the router instance (Example: 0.Name=Router1).
 *  There is usually no need to configure this.
 * </description>
 */
#define ROUTERKEY_STRING_INSTANCE_NAME							"Name"
#ifndef ROUTERKEY_STRING_INSTANCE_NAME_DEFAULT_PREFIX
	#define ROUTERKEY_STRING_INSTANCE_NAME_DEFAULT_PREFIX			"Router"
#endif 

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 *	Name of the router's mainnet (Example: 0.MainNet=ether 0).
 *  Is used to bind a block driver instance to a router instance. On client side (Gateway) the first
 *  router instance needs no parallel routing to communicate to a peer. All devices connected to this
 *  mainnet return shorter addresses in the network scan.
 *	If the name is set to "ether x", then the first registered instance of the CmpBlkDrvUdp is used. 
 * </description>
 */
#define ROUTERKEY_STRING_MAINNET								"MainNet"

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 *	Number of the routers's subnets.
 *  Allowed value range: 1..15.
 *  Thanks parallel routing subnets are typically not neccessary anymore. Must only be used on client side (Gateway)
 * </description>
 */
#define ROUTERKEY_INT_NUMSUBNETS								"NumSubnets"
#define ROUTERKEY_INT_NUMSUBNETS_DEFAULT						0

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 *	Prefix for subnet settings. (Example: 0.Subnet.1.Interface=ether 2)
 * </description>
 */
#define ROUTERKEY_STRING_SUBNET_PREFIX							"Subnet"

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 *	Name of the router's subnet. (Example: 0.Subnet.1.Interface=ether 2)
 *	Note: The CmpBlkDrvTcp or "ether x" cannot be used in a subnet configuration.
 * </description>
 */
#define ROUTERKEY_STRING_SUBNET_INTERFACE						"Interface"

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 *	Address update interval in seconds of a router subnet or mainnet. 
 *  The value 0 disables the address update service for this net.
 *  There is usually no need to configure this. 
 *  Examples: 
 *	0.MainNet.AddressUpdateInterval=60
 *	0.Subnet.1.AddressUpdateInterval=60
 * </description>
 */
#define ROUTERKEY_INT_ADDR_UPDATE_INTERVAL						"AddressUpdateInterval"
#define ROUTERKEY_INT_ADDR_UPDATE_INTERVAL_DEFAULT				60

enum tagProtocolId
{
	PID_ADDRESSREQUEST = 1,		
	PID_ADDRESSNOTIFICATION = 2,
	PID_NAMINGREQUEST = 3,
	PID_NAMINGRESPONSE = 4,

	PID_LAYER4 = 64,
	MAXPROTOCOLID = 65			/* max. value for MAXPROTOCOLID: 255 */
};

typedef enum tagRouterPriority
{
	RPRIO_LOW = 0,
	RPRIO_NORMAL = 1,
	RPRIO_HIGH = 2,
	RPRIO_EMERGENCY = 3
} ROUTERPRIORITY;

/* -- Interface exported to blockdrivers -- */

#define MAX_ROUTERNAME 20
#define MAX_BLOCKSIZE 512
#define MAX_INTERFACE_NAME 20

/**
 * <description> Open a block driver </description>
 * <param name="hInterface" type="IN">Handle to the interface</param>
 * <result>error code</result>
 */
/* static RTS_RESULT CDECL BdOpen(RTS_HANDLE hInterface); */
typedef RTS_RESULT (CDECL * PFBDOPEN) (RTS_HANDLE hInterface);

/**
 * <description> Close a block driver </description>
 * <param name="hInterface" type="IN">Handle to the interface</param>
 * <result>error code</result>
 */
/* static RTS_RESULT CDECL BdClose(RTS_HANDLE hInterface); */
typedef RTS_RESULT (CDECL * PFBDCLOSE) (RTS_HANDLE hInterface);

/**
 * <description> Send data over a blockdriver. Received reply is sent directly to the router </description>
 * <param name="hInterface" type="IN">Handle to the interface</param>
 * <param name="addrReceiver" type="IN">Logical address of receiver</param>
 * <param name="pduData" type="IN">Pointer to block to sent</param>
 * <result>error code. ERR_NOBUFFER, if the blockdriver can temporary not send. In this case
 * the higher layers try to send the same block again.</result>
 */
/* static RTS_RESULT CDECL BdSend(RTS_HANDLE hInterface, NETWORKADDRESS addrReceiver, PROTOCOL_DATA_UNIT pduData); */
typedef RTS_RESULT (CDECL * PFBDSEND) (RTS_HANDLE hInterface, NETWORKADDRESS addrReceiver, PROTOCOL_DATA_UNIT pduData);

typedef struct
{
	PFBDSEND pfBDSend;
		/* pointer to the blockdrivers send method */
	RTS_HANDLE hInterface;
		/* Interfacehandle within the blockdriver. This handle is passed to all calls to the blockdriver */
	int nMaxBlockSize;
		/* The maximum size of a block that may be sent over this device. */
	int nNetworkAddressBitSize;
		/* Number of bits occupied by an address of this driver */
	int bServiceChannel;
		/* If TRUE, this device provides a service channel. */
	NETWORKADDRESS addrDevice;
		/* address of the device within it's subnet (CAN-Node ID, etc.) */
	char szName[MAX_INTERFACE_NAME]; 
		/* human readable name of the device. Must be unique.  */
		/* Could be something like "eth0" or "Ethernetcard #1"  */
} NETWORKINTERFACEINFO;

typedef struct
{
	PFBDSEND pfBDSend;
		/* pointer to the blockdrivers send method */
	RTS_HANDLE hInterface;
		/* Interfacehandle within the blockdriver. This handle is passed to all calls to the blockdriver */
	int nMaxBlockSize;
		/* The maximum size of a block that may be sent over this device. */
	int nNetworkAddressBitSize;
		/* Number of bits occupied by an address of this driver */
	int bServiceChannel;
		/* If TRUE, this device provides a service channel. */
	NETWORKADDRESS addrDevice;
		/* address of the device within it's subnet (CAN-Node ID, etc.) */
	char szName[MAX_INTERFACE_NAME]; 
		/* human readable name of the device. Must be unique.  */
		/* Could be something like "eth0" or "Ethernetcard #1"  */
	RTS_UI16 usType;
		/* Type of the adapter, see CmpCommunicationLibItf.h. */
		/* Can be set to RTS_BLK_DRV_TYPE_NONE, if no device specific information is provided */
	RTS_UI16 usDummy;
		/* Not used at the moment, must be 0 for future compatibility. */
	void *pTypeSpecific;
		/* Pointer to the typespecific information, must be NULL, if no further information is available. */ 
} NETWORKINTERFACEINFO2;

typedef struct
{	
	PFBDOPEN  pfBDOpen;
	PFBDCLOSE pfBDClose;
} ONDEMANDNETWORKINTERFACE;


#ifdef __cplusplus
extern "C" {
#endif

/** <description>
 *   Called by a blockdriver to register one of it's devices with the router. Allows also
 *   to provide some block driver typ specific information.
 * </description>
 * <param name="pDeviceInfo" type="IN">Describes the device to register </param>
 * <param name="phSubnet" type="OUT">
 *   Is set to the subnet handle that refers to this interface. The
 *   blockdriver must provide this value in each call to 
 *   RouterHandleData or RouterUnregisterNetworkInterface.
 * </param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`RouterRegisterNetworkInterface2',`(NETWORKINTERFACEINFO2 *pInterfaceInfo, RTS_HANDLE * phSubnet)')

/** <description>
 *   Called by a blockdriver to register one of it's devices with the router.
 * </description>
 * <param name="pDeviceInfo" type="IN">Describes the device to register </param>
 * <param name="phSubnet" type="OUT">
 *   Is set to the subnet handle that refers to this interface. The
 *   blockdriver must provide this value in each call to 
 *   RouterHandleData or RouterUnregisterNetworkInterface.
 * </param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`RouterRegisterNetworkInterface',`(NETWORKINTERFACEINFO *pInterfaceInfo, RTS_HANDLE * phSubnet)')

/** <description>
 *   At the moment pOnDemandInfo IS NOT USED by the CmpRouter!
 * 
 *   Called by an on-demand blockdriver to register one of it's devices with the router. An on-demand blockdriver
 *   is a blockdriver that is able to shutdown/open its connection on demand. Eg. for serial blockdrivers, so they
 *   can release their hardware interface as long as it isn't needed and open it only, when their is data to be sent.
 *   The blockdriver is supposed to be initially closed.
 * </description>
 * <param name="pDeviceInfo" type="IN">
 *    Describes the device to register 
 * </param>
 * <param name="pOnDemandInfo" type="IN">
 *    Contains additional functions, that allow for opening and closing of the interface.
 * </param>
 * <param name="phSubnet" type="OUT">
 *   Is set to the subnet handle that refers to this interface. The
 *   blockdriver must provide this value in each call to 
 *   RouterHandleData or RouterUnregisterNetworkInterface.
 * </param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL',`RouterRegisterOnDemandNWInterface', `(NETWORKINTERFACEINFO *pInterfaceInfo, ONDEMANDNETWORKINTERFACE *pOnDemandInfo, RTS_HANDLE * phSubnet)')

/** <description>
 *   Called by a blockdriver to unregister one of it's devices
 * </description>
 * <param name="hSubnet" type="IN">
 *   Subnet handle of the interface, which should be unregistered.
 * </param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`RouterUnregisterNetworkInterface',`(RTS_HANDLE hSubnet)')

/** <description>
 *   Called whenever the blockdriver receives a valid data package 
 * </description>
 * <param name="phSubnet" type="IN">
 *   The subnetid assigned to the receiving device during RouterRegisterDevice
 * </param>
 * <param name="addrSender" type="IN">
 *   The device address of the sender within the subnet
 * </param>
 * <param name="pduData" type="IN">The received data package</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`RouterHandleData', `(RTS_HANDLE phSubnet, NETWORKADDRESS sender, PROTOCOL_DATA_UNIT pduData, int bIsBroadcast)')

/** <description>
 *   Called by a blockdriver to get the addresses of a data package. 
 * </description>
 * <param name="pduData" type="IN">
 *   Data package, from which the addresses should be read.
 * </param>
 * <param name="pAddrReceiver" type="OUT">
 *   The function returns here the address of the receiver.
 * </param>
 * <param name="pAddrSender" type="OUT">
 *   The function returns here the address of the sender.
 * </param>
 * <param name="piDataOffset" type="OUT">
 *   If not NULL, the function returns here the offset (start) of the pay load. .
 * </param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`RouterGetBlkAddresses', `(PROTOCOL_DATA_UNIT pduData, PEERADDRESS *pAddrReceiver, PEERADDRESS *pAddrSender, RTS_I32 *piDataOffset)')

/** <description>
 *   Called by a blockdriver to compare two peer addresses. 
 * </description>
 * <param name="pAddr1" type="IN">
 *   First address to compare
 * </param>
 * <param name="pAddr2" type="IN">
 *   Second address to compare
 * </param>
 * <result>TRUE if the addresses are equal, else FALSE</result>
 */
DEF_ITF_API(`RTS_BOOL',`CDECL',`RouterCompareAddresses', `(PEERADDRESS *pAddr1, PEERADDRESS *pAddr2)')

/* -- Interface exported to protocol handlers -- */

/** <description> Inform a protocol handler about an incoming data package </description>
 * <param name="hRouter" type="IN">Handle to the router</param>
 * <param name="nServiceId" type="IN">The protocol id of the package</param>
 * <param name="addrSender"	type="IN">
 *   Sender address. If the protocol handler wants to store the address, 
 *   it must copy the addrSender.address array. The pointer will not be valid
 *   after this function returns.
 * </param>
 * <param name="addrReceiver" type="IN">
 *   Receiver address (either the address of this node or a broadcast address)
 *   Please read the remarks in addrSender before storing this address.
 * </param>
 * <param name="pduData" type="IN">
 *   The received data. If a protocol handler wants to use the data 
 *   after returning from this call, it must copy the data. The data pointer
 *   will not be valid after this function returns.
 * </param>
 * <param name="nRouterError" type="IN">
 *   If this value is not ERR_OK, then this message has been generated by an intermediate node in response to a 
 *   message previously sent by this node, that could not be delivered. 
 *   nRouterError identifies the kind of error that happened.
 *   pduData then contains a detailed error description depending on the kind of error.
 * </param>
 * <result>error code</result>
 */
typedef RTS_RESULT (*PFPHHandleData) (RTS_HANDLE hRouter, int nServiceId, PEERADDRESS addrSender, PEERADDRESS addrReceiver, PROTOCOL_DATA_UNIT pduData, RTS_UI8 nMessageId, RTS_RESULT nRouterError);

/** <description>
 * <p>Obsolete: Register the protocol/service handler on CmpSrv instead. Will be removed in future versions!</p>
 *   Layer 4 protocol handlers calls this function to register itself at the CmpRouter during startup of the RTS. 
 *   Is not used anymore. The known L4 handlers are called directly by the CmpRouter.
 * </description>
 * <param name="protocolId" type="IN">The id of the protocol assigned to this handler</param>
 * <param name="pfPHHandleData" type="IN">
 *   Pointer to the function to be called by the router whenever a package arrives
 * </param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`RouterRegisterProtocolHandler',`(int nProtocolId, PFPHHandleData pfPHHandleData)')

/* -- General Router Interface -- */

/** <description>
 *   Let the router calculate the CoDeSys peer address of a node. This works only for block drivers, which
 *   have a unique instance, e. g. the BlkDrvTcp. The given network address conains in this case the ip-address
 *	 and the port of the node, in the  block driver specific format.
 *   Additionally this function can be used to get the address of the first router instance of the own 
 *   runtime system.
 * </description>
 * <param name="usBlkDrvType" type="IN">
 *   Type of the block driver, see CmpCommunicationLibItf.h.
 *   If set to RTS_BLK_DRV_TYPE_NONE, the address of the first router instance is returned. In this case
 *   the next two parameters are ignored.
 * </param>
 * <param name="byNetworkAddressBitSize" type="IN">
 *   Length of the specified network address in bits. Must match to the setting in the blockdriver.
 *   Should be 0, if RTS_BLK_DRV_TYPE_NONE is used to get the own router address.
 * </param>
 * <param name="pNetworkAddr" type="IN">
 *   Networkaddress of the node, for which the peer address should be calcualted.
 *   Should be NULL, if RTS_BLK_DRV_TYPE_NONE is used to get the own router address.
 * </param>
 * <param name="pNodeAddr" type="OUT">
 *   The function returns here the calculated node address.
 * </param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`RouterCalculateNodeAddr', `(RTS_UI16 usBlkDrvType, RTS_UI8 byNetworkAddressBitSize, NETWORKADDRESS *pNetworkAddr, NODEADDRESS *pNodeAddr)')

/**
 * <description>
 *   Get the handle to the routerinstance with the provided name.
 * </description>
 * <param name="szName" type="IN">
 *	Name of the router. This parameter may be NULL to request a handle to the default router.
 * </param>
 * <param name="phRouter" type="OUT">
 *  If a router exists with the specified name, then the handle of the router is written into this
 *  parameter. Otherwise it is set to RTS_INVALID_HANDLE.
 * </param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`RouterGetInstanceByName',`(char *szName, RTS_HANDLE *phRouter)')

/**
 * <description>
 *   Get the name of a router specified by handle
 * </description>
 * <param name="hRouter" type="IN">Handle to router</param>
 * <param name="pszName" type="OUT">Pointer to get router name</param>
 * <param name="nMaxLen" type="IN">Maximum buffer length of pszName</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`RouterGetName',`(RTS_HANDLE hRouter, char *pszName, int nMaxLen)')

/**
 * <description>
 *   Get the max. size of messages, which can be sent by higher layers to this peer address
 * </description>
 * <param name="hRouter" type="IN">Handle to router. If set to RTS_INVALID_HANDLE, the first router instance is used.</param>
 * <param name="addrPeer" type="IN">Address to check</param>
 * <param name="byMaxSize" type="OUT">Max payload of the router message.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`RouterGetMaxMessageSize',`(RTS_HANDLE hRouter, PEERADDRESS addrPeer, RTS_UI16 *usMaxSize)')

/**
 * <description>
 *   Get the max. size of messages, which can be sent by higher layers to this peer address
 * </description>
 * <param name="hRouter" type="IN">Handle to router</param>
 * <param name="usSumAddrLen" type="IN">Sum of sender and receiver address length</param>
 * <param name="byMaxSize" type="OUT">Max payload of the router message.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`RouterGetMaxMessageSizeByAddressLength',`(RTS_HANDLE hRouter, RTS_UI16 usSumAddrLen, RTS_UI16 *usMaxSize)')

/**
 * <description>
 *   Get the sum of the address lengths of the current router and the addrPeer.
 * </description>
 * <param name="hRouter" type="IN">Handle to router. If set to RTS_INVALID_HANDLE, the first router instance is used.</param>
 * <param name="addrPeer" type="IN">Address to check</param>
 * <param name="byMaxSize" type="OUT">Sum of router address and addrPeer length</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`RouterGetMaxAddressSize',`(RTS_HANDLE hRouter, PEERADDRESS addrPeer, RTS_UI8 *byMaxSize)')

/** <description>
 *   Protocol handlers call this function to send a data package.
 * </description>
 * <param name="hRouter" type="IN">Handle to the router</param>
 * <param name="addrReceiver" type="IN">
 *   Address of the receiver. Relative addresses are allowed as well as absolute ones.
 * </param>
 * <param name="nProtocolId" type="IN">Identifies the protocol handler on the receiving host.</param>
 * <param name="byMessageId" type="IN">typically 0</param>
 * <param name="prio" type="IN">Priority of the message.</param>
 * <param name="pduData" type="IN">The data to be sent.</param>
 * <param name="bUseQueue" type="IN">Defines if the message should be queued, if it can not be send at once.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`RouterSend2',`(RTS_HANDLE hRouter, PEERADDRESS addrReceiver, int nProtocolId, RTS_UI8 byMessageId, ROUTERPRIORITY prio, PROTOCOL_DATA_UNIT pduData, RTS_BOOL bUseQueue)')

/** <description>
 *   Protocol handlers call this function to send a data package.
 * </description>
 * <param name="hRouter" type="IN">Handle to the router</param>
 * <param name="addrReceiver" type="IN">
 *   Address of the receiver. Relative addresses are allowed as well as absolute ones.
 * </param>
 * <param name="nProtocolId" type="IN">Identifies the protocol handler on the receiving host.</param>
 * <param name="byMessageId" type="IN">typically 0</param>
 * <param name="prio" type="IN">Priority of the message.</param>
 * <param name="pduData" type="IN">The data to be sent.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`RouterSend',`(RTS_HANDLE hRouter, PEERADDRESS addrReceiver, int nProtocolId, RTS_UI8 byMessageId, ROUTERPRIORITY prio, PROTOCOL_DATA_UNIT pduData)')

/** <description>
 *   Get the routers nodeaddress.
 * </description>
 * <param name="hRouter" typ="IN">Handle to router. If set to RTS_INVALID_HANDLE, the first router instance is used.</param>
 * <param name="pAddrRouter" type="OUT">Is set to the nodeaddress of the router</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`RouterGetHostAddress',`(RTS_HANDLE hRouter, NODEADDRESS *pAddrRouter)')

/** <description>
 *   Get the nodeaddress of the parent node.
 * </description>
 * <param name="hRouter" typ="IN">Handle to router. If set to RTS_INVALID_HANDLE, the first router instance is used.</param>
 * <param name="pAddrParent" type="OUT">Is set to the nodeaddress of the router</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`RouterGetParentAddress',`(RTS_HANDLE hRouter, NODEADDRESS *pAddrParent)')

/** <description>
*   Get the block driver type RTS_BLK_DRV_TYPE_xxx of the refered network interface. See CmpCommunicationLibItf.
* </description>
* <param name="hNetworkInterface" typ="IN">Handle of network instance.</param>
* <param name="pbyBlkDrvType" type="OUT">Pointer to return block driver type of the network interface.</param>
* <result>error code</result>
*/
DEF_ITF_API(`RTS_RESULT',`CDECL',`RouterGetBlkDrvType',`(RTS_HANDLE hNetworkInterface, RTS_UI8 *pbyBlkDrvType)')

/* -- Interface of the router provided for access by iec -- */

/**
 * <description>RTR_AddrComponent</description>
 */
typedef struct tagRTR_AddrComponent
{
	RTS_IEC_BYTE Component[2];
} RTR_AddrComponent;

/**
 * <description>RTR_NodeAddress</description>
 */
typedef struct tagRTR_NodeAddress
{
	RTS_IEC_UDINT nAddrComponentCount;
	RTR_AddrComponent AddrComponents[15];
} RTR_NodeAddress;

/**
 * <description>routergetinstancebyname</description>
 */
typedef struct tagroutergetinstancebyname_struct
{
	RTS_IEC_STRING *pstName;			/* VAR_INPUT */
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */
	RTS_IEC_BYTE *RouterGetInstanceByName;	/* VAR_OUTPUT */
} routergetinstancebyname_struct;

DEF_API(`void',`CDECL',`routergetinstancebyname',`(routergetinstancebyname_struct *p)',1,0xBA8CBF9D,0x3020000)

/**
 * <description>routergetname</description>
 */
typedef struct tagroutergetname_struct
{
	RTS_IEC_BYTE *hRouter;				/* VAR_INPUT */
	RTS_IEC_BYTE *pBuffer;				/* VAR_INPUT */
	RTS_IEC_INT nBufferSize;			/* VAR_INPUT */
	RTS_IEC_UDINT RouterGetName;		/* VAR_OUTPUT */
} routergetname_struct;

DEF_API(`void',`CDECL',`routergetname',`(routergetname_struct *p)',1,0xE4FB4AAA,0x3020000)

/**
 * <description>routergethostaddress</description>
 */
typedef struct tagroutergethostaddress_struct
{
	RTS_IEC_BYTE *hRouter;				/* VAR_INPUT */
	RTR_NodeAddress *resAddr;			/* VAR_IN_OUT */
	RTS_IEC_UDINT RouterGetHostAddress;	/* VAR_OUTPUT */
} routergethostaddress_struct;

DEF_API(`void',`CDECL',`routergethostaddress',`(routergethostaddress_struct *p)',1,0xC47F4C13,0x3020000)

/**
 * <description>routergetparentaddress</description>
 */
typedef struct tagroutergetparentaddress_struct
{
	RTS_IEC_BYTE *hRouter;				/* VAR_INPUT */
	RTR_NodeAddress *resAddr;			/* VAR_IN_OUT */
	RTS_IEC_UDINT RouterGetParentAddress;	/* VAR_OUTPUT */
} routergetparentaddress_struct;

DEF_API(`void',`CDECL',`routergetparentaddress',`(routergetparentaddress_struct *p)',1,0xD64907DE,0x3020000)

#ifdef __cplusplus
}
#endif
