/**
 * <interfacename>CmpChannelMgr</interfacename>
 * <description>
 *	Interface for the channel manager.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpChannelMgr')

REF_ITF(`CmpRouterItf.m4')

#define L4_VERSION_MAJOR  0x01
#define L4_VERSION_MINOR  0x01

#ifdef INTEL_BYTE_ORDER
	#define L4_VERSION ((L4_VERSION_MAJOR<<8)|L4_VERSION_MINOR)
#elif defined MOTOROLA_BYTE_ORDER
	#define L4_VERSION ((L4_VERSION_MINOR<<8)|L4_VERSION_MAJOR)
#else
	#error "No byte order defined for the current target"
#endif

#define KEEPALIVE_INTERVAL (1000UL) 
	/* Defines the idle-time (ms) after which to send a keepalive package */

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to modify the default value of the channel timeout. A channel is closed, if for the specified time 
 *  no package (data, ACK or keep alive) is received on this channel.
 * </description>
 */
#define CHMGRKEY_INT_CHANNEL_TIMEOUT					"ChannelTimeoutMs"
#ifndef CHMGRKEY_INT_CHANNEL_TIMEOUT_DEFAULT
	#define CHMGRKEY_INT_CHANNEL_TIMEOUT_DEFAULT		(30UL * KEEPALIVE_INTERVAL)
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to setup the logfilter for sent/received packages. See category package logfilter for details.
 *  The default value enables only the duplicate block message. 
 * </description>
 */
#define CHMGRKEY_INT_PACKAGE_LOGFILTER					"PackageLogFilter"
#ifndef CHMGRKEY_INT_PACKAGE_LOGFILTER_DEFAULT
	#define CHMGRKEY_INT_PACKAGE_LOGFILTER_DEFAULT		PKG_LOG_DUPLICATE
#endif

/**
 * <category>Package logfilter</category>
 * <description>Package info log entry filters for the CmpChannelMgr</description>
 * <element name="PKG_LOG_NONE" type="Log nothing"></element>
 * <element name="PKG_LOG_DUPLICATE" type="Log duplicate received blocks"></element>
 * <element name="PKG_LOG_RX" type="Log all received packages"></element>
 * <element name="PKG_LOG_TX" type="Log all sent packages"></element>
 * <element name="PKG_LOG_ACK_TRIG_NUM" type="Log sent ACKs, triggerd by the number of privious received data packages"></element>
 * <element name="PKG_LOG_ACK_TRIG_TO" type="Log sent ACKs, triggerd by timeout"></element>
 * <element name="PKG_LOG_IN_ORDER_BLOCK" type="Log in order received blocks"></element>
 * <element name="PKG_LOG_COMPRESS_BLOCK" type="Log compressing of blocks, if a missing block was received"></element>
 * <element name="PKG_LOG_OUT_OF_ORDER_BLOCK" type="Log out of order received blocks"></element>
 */
#define PKG_LOG_NONE				UINT32_C(0x00000000)
#define PKG_LOG_DUPLICATE			UINT32_C(0x00000001)
#define PKG_LOG_RX					UINT32_C(0x00000002)
#define PKG_LOG_TX					UINT32_C(0x00000004)
#define PKG_LOG_ACK_TRIG_NUM		UINT32_C(0x00000010)
#define PKG_LOG_ACK_TRIG_TO			UINT32_C(0x00000020)
#define PKG_LOG_IN_ORDER_BLOCK		UINT32_C(0x00000040)
#define PKG_LOG_COMPRESS_BLOCK		UINT32_C(0x00000080)
#define PKG_LOG_OUT_OF_ORDER_BLOCK	UINT32_C(0x00000100)


/* -- Package types --*/

/* L7-communication packages */
#define	PT_DATA             0x01
#define PT_ACK              0x02
#define PT_KEEPALIVE        0x03

/* Meta-packages */
#define PT_NOTIFICATION     (0x80 + 0x01)
#define PT_RTSINFO          (0x80 + 0x02)
#define PT_OPENCHANNEL      (0x80 + 0x03)
#define PT_CLOSECHANNEL     (0x80 + 0x04)

/* Meta-packages from client to server (requests) */
#define PT_RTSINFO_REQ      (0xC0 + 0x02)
#define PT_OPENCHANNEL_REQ  (0xC0 + 0x03)
#define PT_CLOSECHANNEL_REQ (0xC0 + 0x04)

/* Metapackages are marked with their highest bit set */
#define ISMETAPACKAGE(pkgType) ((pkgType & 0x80) == 0x80)
/* Request packages are metapackages (highest bit set)
   and marked with the second highest bit set */
#define ISREQUEST(pkgType)     ((pkgType & 0xC0) == 0xC0)

/* -- Flags for package types -- */

#define PTF_FIRSTPACKAGE    0x01
	/* Used in PT_DATA packages. Marks this package as being the first
	   package of a layer-7 message 
	*/
#define PTF_MISSINGPACKAGE  0x02
	/* Used in PT_DATA and PT_ACK packages. Signals that the next package after
	   the acknowledged package probably has been lost and should be retransmitted
	*/
#define PTF_DATADIRTOSERVER 0x80
	/* Used for channel (DATA, ACK, KEEPALIVE, ...) packages. 
	   Set if the package is directed from client to server.
	*/

/* -- Structure of network packages. All of these packages must be packed. -- */

#ifndef NO_PRAGMA_PACK
	#pragma pack(1)
#endif

/* The basic header for each layer4 package */
typedef struct
{
#ifdef RTS_SIXTEENBITBYTES
	unsigned short usTypeAndFlags;
#else
	unsigned char byPkgType;
		/* Type of this pkg (one of the PT_ constants) */
	unsigned char byFlags;
		/* Flags dependent on the PkgType */
#endif
} L4PACKAGE;

/* Header for a data acknowledge (PT_ACK) package (an extension of L4PACKAGE)*/
typedef struct
{
	L4PACKAGE L4Pkg;
	unsigned short wChannelId;
	RTS_UI32  dwAckBlock;
		/* number of last acknowledged block */
/*	RTS_UI32  dwChecksum; */
		/* CRC-32 */
} L4ACKNOWLEDGE;

/* Header for layer4 data package (an extension of L4PACKAGE) */
typedef struct
{
	L4PACKAGE L4Pkg;
	unsigned short wChannelId;
	RTS_UI32 dwBlock;
	RTS_UI32 dwAckBlock;
	unsigned char byData[1];
} L4DATA;

/* Header for the first layer4 data package of a layer 7 message (an extension of L4PACKAGE) */
typedef struct
{
	L4PACKAGE L4Pkg;
	unsigned short wChannelId;
	RTS_UI32 dwBlock;
	RTS_UI32 dwAckBlock;
	RTS_UI32 dwMsgLength;
	RTS_UI32 dwMsgChecksum;
	unsigned char byData[1];
} L4DATAFIRST;

typedef struct
{
	L4PACKAGE L4Pkg;
	unsigned short wChannelId;
} L4KEEPALIVE;

/* Header for all layer4 meta packages (an extension of L4PACKAGE) */
typedef struct
{
	L4PACKAGE L4Pkg;
	unsigned short wVersion;  
		/* Protocol version */
	RTS_UI32  dwChecksum; 
		/* CRC-32 */
} L4METAPACKAGE;

/* Header of a request for runtimesystem information(an extension on L4METAPACKAGE) */
typedef struct
{
	L4METAPACKAGE metaPkg;
}L4RTSINFO_REQ;

/* Header of a response package to the L4RTSINFO_REQ */
typedef struct
{
	L4METAPACKAGE metaPkg;
	unsigned short wMaxChannels;
}L4RTSINFO_RESP;

/* Header of a request for a new channel */
typedef struct
{
	L4METAPACKAGE metaPkg;
	RTS_UI32 dwRequestId;
	RTS_UI32 dwCommBufferSize; 
		/* requested size of communication buffer */
}L4OPENCHANNEL_REQ;

/* Header of a request for a new channel, used in version 0x0101 */
typedef struct
{
	L4METAPACKAGE metaPkg;
	RTS_UI32 dwRequestId;
	RTS_UI32 dwCommBufferSize; /* requested size of communication buffer */
#ifdef RTS_SIXTEENBITBYTES
	RTS_UI16	  usMaxAddressSize;
#else
	RTS_UI8       byMaxAddressSize; 
	RTS_UI8       byDummy;
#endif
	RTS_UI16      wDummy;
}L4OPENCHANNEL_REQ_2;

/* Definitions for the result of an open channel req */
#define OPENC_SUCCESS       0  /* Channel has been created */
#define OPENC_NOFREECHANNEL 1  /* All available channels already in use */
#define OPENC_NOTSERVER     2  /* This is not a server - you cannot open a channel to this node */

#define CHF_BIGENDIAN       0x01 /* "Motorola byteorder" */

typedef struct
{
	L4METAPACKAGE metaPkg;
	RTS_UI32 dwRequestId;
		/* references the request */
	RTS_UI16 wResult;
		/* One of the OPENC_xxx constants */
	RTS_UI16 wChannelId; 
		/* The id of the created channel. */
	RTS_UI32 dwCommBufferSize; 
		/* granted size of communication buffer. Less or equal to the requested size */
}L4OPENCHANNEL_RESP_1_0;

/* Header of a response to an open channel request, used in version 0x0101 */
typedef struct
{
	L4METAPACKAGE metaPkg;

	/* references the request */
	RTS_UI32 dwRequestId;
	
	/* One of the OPENC_xxx constants */
	RTS_UI16 wResult;
	
	/* The id of the created channel. */
	RTS_UI16 wChannelId; 
	
	/* granted size of communication buffer. Less or equal to the requested size */
	RTS_UI32 dwCommBufferSize; 

#ifdef RTS_SIXTEENBITBYTES
	RTS_UI16 usFlagsAndMaxAddrSize;
#else	
	/* A combination of the CHF_xxx flags */
	RTS_UI8  byFlags; 

	/* Stores the sum of sender and receiver address lengths */
	RTS_UI8  byMaxAddressSize;
#endif
	/* Dummy alignment word. Must be zero */
	RTS_UI16 wDummy;
}L4OPENCHANNEL_RESP;
typedef struct
{
	L4METAPACKAGE metaPkg;
	unsigned short wChannelId;
	unsigned short wError;  /* The cause for closing the channel (ERR_OK for normal shutdown)*/
}L4CLOSECHANNEL_REQ;

#ifndef NO_PRAGMA_PACK
	#ifdef USE_PRAGMA_PACK_0
		#pragma pack(0)
	#else
		#pragma pack()
	#endif	
#endif

/* -- Internal datastructures -- */


#define BF_SENT     0x01
#define BF_RECEIVED 0x02
#define BF_REPEATED 0x04  /* Set if the block was sent more then once */
typedef struct 
{
	RTS_UI32 dwTimeStamp;
	RTS_UI32 dwStartByte;
	RTS_UI32 dwBlockNr;
	unsigned short wLength;
	unsigned short wFlags; /* Combination of the BF_xxx flags */
}BLOCKINFO;

#define CF_SERVERCHANNEL			0x01	/* Channel resides on the server side */
#define CF_BIT_SERVERCHANNEL		0		/* Bit number of previous value */
#define CF_SENDMODE					0x02	/* Channel is currently in send mode */
#define CF_BIT_SENDMODE				1		/* Bit number of previous value */
#define CF_ADDRRELATIVE				0x04	/* Relative addressing is used */
#define CF_BIT_ADDRRELATIVE			2		/* Bit number of previous value */
#define CF_SEND_BLOCKS_ACTIVE		0x08	/* Flag to avoid reentrance in send routine */ 
#define CF_BIT_SEND_BLOCKS_ACTIVE	3		/* Bit number of previous value */
#define CF_REPEAT_APP_CALL			0x10	/* If this flag is set, the app (CmpSrv) is called cyclically until the service is handled. */ 
#define CF_BIT_REPEAT_APP_CALL		4		/* Bit number of previous value */

typedef struct
{
	RTS_UI32 dwNextByte;
	RTS_UI32 dwLastAck;
	RTS_UI32 dwLastBlock;
	RTS_UI32 dwMsgSize;
	RTS_UI32 dwMsgChecksum;
	RTS_UI32 dwLastTime; /* Last time a package was received. */
}CHANNELRECEIVESTATE;

typedef struct
{
	RTS_UI32 dwNextByte;
	RTS_UI32 dwNextAck;
	RTS_UI32 dwNextBlock;
	RTS_UI32 dwMsgSize;
	RTS_UI32 dwMsgChecksum;
	RTS_UI32 dwLastTime; /* Last time a package was sent. */
}CHANNELSENDSTATE;

typedef struct
{
	/* Channel "name"*/
	unsigned char ucAddrOffset; /* Offset of relative addresses. Valid iff CF_ADDRRELATIVE is set in wFlags */
	unsigned char ucAddrPeerLen;
	ADDRESSCOMPONENT  addrPeer[MAX_NODEADDR_LEN]; /* address of the communication partner */
	unsigned short wChannelId;
	RTS_HANDLE hRouter;

	/* Channel properties (static)*/
	RTS_UI32  dwCommBufferSize;
	unsigned short wNumBlockBuffers;
	unsigned short wMaxBlockSize;  /* maximum size of a l4 package */
	unsigned short wFlags;		   /* Combination of the CF_xxx constants */
	
	/* Connection properties (dynamic)*/
	unsigned short wCWnd;
	unsigned short wCWndCheckCount;
	unsigned short wLastCWnd;
	unsigned short wGoodCWnd;
	unsigned short wGoodCWndCount;
	RTS_UI32  dwCWndFreezeTime;
	RTS_UI32  dwRTT;
	RTS_UI32  dwRTO;

	/* The channels buffers */
	unsigned char *pReceiveBuffer; /* Calculate as described in comment to blockBuffer field */
	unsigned char *pSendBuffer;

	CHANNELSENDSTATE sendState;
	CHANNELRECEIVESTATE recState;

	BLOCKINFO blockBuffer[1]; 
		/* The communication buffer starts after the last element of the blockBuffer array.
		   To achieve correct alignment, calculate the address of the comm-buffer as:
		    & (blockBuffer[blockBufferLength]) 
		   i.e. the first element after the blockBuffer. This should be aligned on a 4 byte boundary.
		*/
}CHANNELBUFFER;


#ifdef RTS_SIXTEENBITBYTES

	#define sizeof_BLOCKINFO			RTS_GET_BYTE_SIZE(sizeof(BLOCKINFO))
	#define sizeof_L4PACKAGE			RTS_GET_BYTE_SIZE(sizeof(L4PACKAGE))
	#define sizeof_L4ACKNOWLEDGE		RTS_GET_BYTE_SIZE(sizeof(L4ACKNOWLEDGE))
	#define sizeof_L4METAPACKAGE		RTS_GET_BYTE_SIZE(sizeof(L4METAPACKAGE))
	#define sizeof_L4KEEPALIVE			RTS_GET_BYTE_SIZE(sizeof(L4KEEPALIVE))
	#define sizeof_L4OPENCHANNEL_REQ_2	RTS_GET_BYTE_SIZE(sizeof(L4OPENCHANNEL_REQ_2))
	#define sizeof_L4OPENCHANNEL_RESP	RTS_GET_BYTE_SIZE(sizeof(L4OPENCHANNEL_RESP))
	#define sizeof_L4CLOSECHANNEL_REQ	RTS_GET_BYTE_SIZE(sizeof(L4CLOSECHANNEL_REQ))

	/* L4PACKAGE */
	#define GET_L4PACKAGE_TYPE(pkg)	(unsigned char)(((L4PACKAGE*)pkg)->usTypeAndFlags & 0x00FF)
	#define GET_L4PACKAGE_FLAGS(pkg)	(unsigned char)((((L4PACKAGE*)pkg)->usTypeAndFlags >> 8) & 0x00FF)
	#define SET_L4PACKAGE_TYPE(pkg,nType)	((L4PACKAGE*)pkg)->usTypeAndFlags = ((unsigned short) (nType) & 0x00FF) | (((L4PACKAGE*)pkg)->usTypeAndFlags & 0xFF00)
	#define CLEAR_L4PACKAGE_FLAGS(pkg)		((L4PACKAGE*)pkg)->usTypeAndFlags = (((L4PACKAGE*)pkg)->usTypeAndFlags & 0x00FF)
	#define SET_L4PACKAGE_FLAG(pkg,nFlag)	((L4PACKAGE*)pkg)->usTypeAndFlags = (((unsigned short)(GET_L4PACKAGE_FLAGS(pkg) | (nFlag)) << 8) & 0xFF00) | (((L4PACKAGE*)pkg)->usTypeAndFlags & 0x00FF)

	/* L4OPENCHANNEL_REQ_2 */
	#define GET_L4OPENCHANNEL_REQ_2_MAX_ADDR_SIZE(pkg)	(RTS_UI8)(((L4OPENCHANNEL_REQ_2*)pkg)->usMaxAddressSize & 0x00FF)
	#define SET_L4OPENCHANNEL_REQ_2_MAX_ADDR_SIZE(pkg,nMaxAddrSize)	((L4OPENCHANNEL_REQ_2*)pkg)->byMaxAddressSize = (RTS_UI16) (nMaxAddrSize & 0x00FF) | (RTS_UI16)(((L4OPENCHANNEL_REQ_2*)pkg)->byMaxAddressSize & 0xFF00)

	/* L4OPENCHANNEL_RESP */
	#define GET_L4OPENCHANNEL_RESP_FLAGS(pkg)	(RTS_UI8)(((L4OPENCHANNEL_RESP*)pkg)->usFlagsAndMaxAddrSize & 0x00FF)
	#define GET_L4OPENCHANNEL_RESP_MAX_ADDR_SIZE(pkg)	(RTS_UI8)((((L4OPENCHANNEL_RESP*)pkg)->usFlagsAndMaxAddrSize >> 8) & 0x00FF)
	#define CLEAR_L4OPENCHANNEL_RESP_FLAGS(pkg)		((L4OPENCHANNEL_RESP*)pkg)->usFlagsAndMaxAddrSize = (((L4OPENCHANNEL_RESP*)pkg)->usFlagsAndMaxAddrSize & 0xFF00)
	#define SET_L4OPENCHANNEL_RESP_FLAG(pkg,nFlag)	((L4OPENCHANNEL_RESP*)pkg)->usFlagsAndMaxAddrSize = (((unsigned short)(GET_L4PACKAGE_FLAGS(pkg) | nFlag)) & 0x00FF) | (((L4OPENCHANNEL_RESP*)pkg)->usFlagsAndMaxAddrSize & 0xFF00)
	#define SET_L4OPENCHANNEL_RESP_MAX_ADDR_SIZE(pkg,nMaxAddrSize)	((L4OPENCHANNEL_RESP*)pkg)->usFlagsAndMaxAddrSize = (RTS_UI16)((nMaxAddrSize << 8) & 0xFF00) | (RTS_UI16)(((L4OPENCHANNEL_RESP*)pkg)->usFlagsAndMaxAddrSize & 0x00FF)															

#else

	/* L4PACKAGE */
	#define GET_L4PACKAGE_TYPE(pkg) 	(unsigned char)((L4PACKAGE*)pkg)->byPkgType
	#define GET_L4PACKAGE_FLAGS(pkg) 	(unsigned char)((L4PACKAGE*)pkg)->byFlags
	#define SET_L4PACKAGE_TYPE(pkg,nType) 	((L4PACKAGE*)pkg)->byPkgType = (unsigned char) nType
	#define CLEAR_L4PACKAGE_FLAGS(pkg)		((L4PACKAGE*)pkg)->byFlags = 0
	#define SET_L4PACKAGE_FLAG(pkg,nFlag)	((L4PACKAGE*)pkg)->byFlags |= nFlag

	/* L4OPENCHANNEL_REQ_2 */
	#define GET_L4OPENCHANNEL_REQ_2_MAX_ADDR_SIZE(pkg)	(RTS_UI8)((L4OPENCHANNEL_REQ_2*)pkg)->byMaxAddressSize
	#define SET_L4OPENCHANNEL_REQ_2_MAX_ADDR_SIZE(pkg,nMaxAddrSize)	((L4OPENCHANNEL_REQ_2*)pkg)->byMaxAddressSize = (RTS_UI8) nMaxAddrSize

	/* L4OPENCHANNEL_RESP */
	#define GET_L4OPENCHANNEL_RESP_FLAGS(pkg)	(RTS_UI8)((L4OPENCHANNEL_RESP*)pkg)->byFlags
	#define GET_L4OPENCHANNEL_RESP_MAX_ADDR_SIZE(pkg)	(RTS_UI8)((L4OPENCHANNEL_RESP*)pkg)->byMaxAddressSize
	#define CLEAR_L4OPENCHANNEL_RESP_FLAGS(pkg)		((L4OPENCHANNEL_RESP*)pkg)->byFlags = 0
	#define SET_L4OPENCHANNEL_RESP_FLAG(pkg,nFlag)	((L4OPENCHANNEL_RESP*)pkg)->byFlags |= nFlag
	#define SET_L4OPENCHANNEL_RESP_MAX_ADDR_SIZE(pkg,nMaxAddrSize)	((L4OPENCHANNEL_RESP*)pkg)->byMaxAddressSize = (RTS_UI8) nMaxAddrSize

#endif /* RTS_SIXTEENBITBYTES */

/* -- Functions exported to the Router component */

	/** <description> Protocol handler of CmpChannelMgr.
	*   Attention: Must only be called by CmpRouter to forward an incoming data package.</description>
	* <param name="hRouter" type="IN">Handle of router instance calling this function.
	*   For L4 client implementations, by default it is called by the router instance 0.
	*   For L4 server implementations, it is called by the router instance which has received the package originally.</param>
	* <param name="hNetworkInterface" type="IN">Handle of the network interface receiving originally the package</param>
	* <param name="byServiceId" type="IN">The protocol id of the package</param>
	* <param name="byMessageId" type="IN">The message id of the package</param>
	* <param name="addrSender"	type="IN"> Sender address.
	*   The pointer within will not be valid after this function returns.</param>
	* <param name="addrReceiver" type="IN">
	*   Receiver address (either the address of this node or a broadcast address).
	*   The pointer within will not be valid after this function returns.</param>
	* <param name="pduData" type="IN">
	*   The received data. The data pointer will not be valid after this function returns.</param>
	* <param name="nRouterError" type="IN">
	*   If this value is not ERR_OK, then this message has been generated by an intermediate node in response to a
	*   message previously sent by this node, that could not be delivered.
	*   nRouterError identifies the kind of error that happened.
	*   pduData then contains a detailed error description depending on the kind of error.
	* </param>
	* <result>error code</result>
	*/
DEF_ITF_API(`RTS_RESULT',`CDECL',`ChannelMgrHandleData',`(RTS_HANDLE hRouter, RTS_HANDLE hNetworkInterface, RTS_UI8 byServiceId, RTS_UI8 byMessageId, PEERADDRESS addrSender, PEERADDRESS addrReceiver, PROTOCOL_DATA_UNIT pduData, RTS_RESULT nRouterError)')


/* -- Functions exported to the NetClient and NetServer components */

#ifdef __cplusplus
extern "C" {
#endif

/* Used as callback in foreachChannel - calls. 
   pChBuffer  IN    pointer to the channel
   pParam     INOUT A In/Out parameter passed on each call.
*/
typedef int (*PFCHANNELHANDLER)( CHANNELBUFFER * pChBuffer, void * pParam);

/**
 * <description> 
 *   Given a fixed size for the communication buffer return the required size of the
 *   channel buffer.
 * </description>
 * <param name="dwCommBufferSize" type="IN">Requested size of the communication buffer</param>
 * <param name="wMaxBlockSize" type="IN">  
 *    Maximum size of a layer4 block (as returned by RouterGetMaxBlockSize)
 * </param>
 * <param name="pnNumBlocks" type="OUT">Required number of block buffers</param>
 * <result>
 *   The size of the channel buffer in bytes.
 * </result>
*/
DEF_ITF_API(`RTS_UI32',`CDECL',`NetworkGetChBufferSize',`( RTS_UI32 dwCommBufferSize, unsigned short wMaxBlockSize, int *pnNumBlocks)')

/**
 * <description>
 * Initialize the provided channelbuffer. 
 * </description>
 * <param name = "pChBuffer" type="IN"></param>
 * <param name = "dwBufferSize" type="IN"> Size of pChBuffer. </param>
 * <param name = "wChannelId" type="IN"> The id of the channel.</param>
 * <param name = "addrSender" type="IN"> The 3S-address of this channels peer. </param>
 * <param name = "byFlags" type="IN"> 
 *   Initial channel flags (CF_SERVERCHANNEL for a serverchannel, CF_SENDMODE for a clientchannel)
 * </param>
 * <param name = "dwMaxCommBuffer" type="IN">  
 *   Maximum size of the communication buffer to use (usually the requested communication buffer)
 * </param>
 * <result>
 *   The size of the communication buffer for this channelbuffer.
 * </result>
*/
DEF_ITF_API(`RTS_UI32',`CDECL',`NetworkInitChannelBuffer',`(CHANNELBUFFER *pChBuffer, RTS_HANDLE hRouter, RTS_UI32 dwBufferSize, unsigned short wChannelId, PEERADDRESS addrSender, unsigned char byChFlags, RTS_UI32 dwMaxCommBuffer)')

/**
 * <description>
 * Initialize the provided channelbuffer with a given maximum Blocksize. 
 * </description>
 * <param name = "pChBuffer" type="IN"></param>
 * <param name = "dwBufferSize" type="IN"> Size of pChBuffer. </param>
 * <param name = "wChannelId" type="IN"> The id of the channel.</param>
 * <param name = "addrSender" type="IN"> The 3S-address of this channels peer. </param>
 * <param name = "byFlags" type="IN"> 
 *   Initial channel flags (CF_SERVERCHANNEL for a serverchannel, CF_SENDMODE for a clientchannel)
 * </param>
 * <param name = "dwMaxCommBuffer" type="IN">  
 *   Maximum size of the communication buffer to use (usually the requested communication buffer)
 * </param>
 * <param name = "wMaxBlockSize" type="IN">  
 *   Maximum size of one block
 * </param>
 * <result>
 *   The size of the communication buffer for this channelbuffer.
 * </result>
*/
DEF_ITF_API(`RTS_UI32',`CDECL',`NetworkInitChannelBuffer2',`(CHANNELBUFFER *pChBuffer, RTS_HANDLE hRouter, RTS_UI32 dwBufferSize, unsigned short wChannelId, PEERADDRESS addrSender, unsigned char byChFlags, RTS_UI32 dwMaxCommBuffer, unsigned short wMaxBlockSize)')

/**
 * <description>
 *   Send metaPkg to addrReceiver. Sets the checksum field of the metaPkg before sending.
 * </description>
 * <param name="addrReceiver" type="IN"> Address of the receiver </param>
 * <param name="pMetaPkg" type="IN"> The package to be sent</param>
 * <param name="nPkgSize" type="IN"> Size of pMetaPkg</param>
 * <result>
 *   An error code.
 * </result>
*/
DEF_ITF_API(`int',`CDECL',`NetworkSendMetaPkg',`(RTS_HANDLE hRouter, PEERADDRESS addrReceiver, L4METAPACKAGE *pMetaPkg, int nPkgSize)')

/**
 * <description>
 *   Send a message over the provided channel.
 *   A channel can't be receiving and sending at the same time. Thus this function
 *   will fail with ERR_CHANNELMODE if the channel is currently in receive mode.
 * </description>
 *
 * <result>
 *   <ul>
 *    <li>ERR_CHANNELMODE if the channel is in receive mode.</li>
 *    <li>ERR_CHC_MESSAGESIZE/ERR_CHS_MESSAGESIZE if the size of the data is greater then the CommBuffer size.</li>
 *   </ul>
 * </result>
 */
DEF_ITF_API(`int',`CDECL',`NetworkSendMessage',`(CHANNELBUFFER *pChBuffer, PROTOCOL_DATA_UNIT pduData)')

/**
 *	<description>
 *		Get the current status of an active channel.
 *	</description>
 *	<param name="pChBuffer" type="IN"> 
 *		The channel for which to retrieve the status 
 *	</param>
 *	<param name="pusStatus" type="OUT">
 *		Is set to the current progress state. The PROGRESS_xxx constants define valied values.
 *	</param>
 *  <param name="pbyScalingFactor" type="OUT">
 *		Provides the scaling factor for pnItemsComplete and pnTotalItems. These values have been scaled
 *		down by dividing them through 2^ScalingFactor 
 *		(i.e. they have been right shifted by ScalingFactor bits).
 *  </param>
 *	<param name="pnItemsComplete" type="OUT">
 *		Number of items completed (eg. the number of bytes transfered).
 *  </param>
 * 	<param name="pnTotalItems" type="OUT">
 *		Total number of item. Is set to -1 if unknown.
 *  </param> */ 
DEF_API(`int',`CDECL',`NetworkGetStatus',`(CHANNELBUFFER *pChBuffer, RTS_UI16 *pusStatus, RTS_UI8 *pbyScalingFactor, RTS_I32 *pnItemsComplete, RTS_I32 *pnTotalItems)')

/** 
 * <description>
 *   Returns a copy of the internal channel structure. This function is intended for information purpoeses only.
 * </description>
 * <param name="pChBuffer" type="IN">The channel for which to retrieve the status.</param>
 * <param name="pChInfoBuffer" type="INOUT">Caller allocated buffer, to which the content of the internal channel buffer structure is copied to.</param>
 * <param name="psiBufferLen" type="INOUT">Pointer to the size of the buffer in bytes, returns the number of copied bytes.</param>
 * <result>error code</result>
*/
DEF_ITF_API(`RTS_RESULT',`CDECL',`NetworkGetChannelInfo',`(CHANNELBUFFER *pChBuffer, CHANNELBUFFER *pChInfoBuffer, RTS_SIZE *psiBufferLen)')

#ifdef __cplusplus
}
#endif
