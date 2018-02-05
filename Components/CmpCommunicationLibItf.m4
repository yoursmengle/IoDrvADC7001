/**
 * <interfacename>CmpCommunicationLib</interfacename>
 * <description>
 *	Interface for the communication library.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpCommunicationLib')

#include "CmpStd.h"
#include "CmpItf.h"
#include "CmpErrors.h"

#ifdef __cplusplus
	extern "C" {
#endif 


/*  Block Driver Types 
*	Used to identify the type of a blockdriver to handle its specific information or features.
*	Example usecase: Ask the router to convert an ip address to a CoDeSys address for the 
*	CmpBlkDrvTcp Instance. 
*/
#define RTS_BLK_DRV_TYPE_NONE			0x00
#define RTS_BLK_DRV_TYPE_TCP			0x01
#define RTS_BLK_DRV_TYPE_COM			0x02
#define RTS_BLK_DRV_TYPE_USB			0x03
#define RTS_BLK_DRV_TYPE_SHM			0x04
#define RTS_BLK_DRV_TYPE_UDP			0x05
#define RTS_BLK_DRV_TYPE_CAN_CLIENT		0x06
#define RTS_BLK_DRV_TYPE_CAN_SERVER		0x07
#define RTS_BLK_DRV_TYPE_DIRECT_CALL	0x08

#define RTS_BLK_DRV_TYPE_OEM_BEGIN		0x40
#define RTS_BLK_DRV_TYPE_OEM_END		0x7F


/* Block Driver Flags
 * These flags are used to handle specific information or features for a particular blockdriver type (see above).
 * Example usecase: Specify if the device to look for is a gateway or a PLC.
 */
 #define RTS_BLK_DRV_FLAGS_PLC 0
 #define RTS_BLK_DRV_FLAGS_GATEWAY 1
 #define RTS_BLK_DRV_FLAGS_DIRECT_ADDRESS 2


/* Name service package flags 
 * These flags are used to describe device features in the name service answer. 
 */
#define NSPF_ENCRYPTED_COMM_SUPPORTED		0x00000001 /* device supports encrypted online communication */
#define NSPF_ENCRYPTED_COMM_REQUIRED		0x00000002 /* device requires encrypted online communication */


/* One component of a 3S address */
typedef RTS_UI8 ADDRESSCOMPONENT[2]; 

/* Maximum number of ADDRESSCOMPONENTS in a nodeaddress*/
#define MAX_NODEADDR_LEN 0x0F

/* Maximum number of bytes in a networkaddress */
#define MAX_NETWORKADDR_LEN 8

/* -- IDs describing the progress of a service in the communication system -- */
#define PROGRESS_INVALID        0x0000
#define PROGRESS_IDLE           0x0001 /* No pending requests. A new request may be sent. Progress is 0 */
	/* The service is currently in the communication system (usually between gateway and target */
#define PROGRESS_CHSENDING      0x0010 /* A request is being sent from gateway to target. Progress is related to the number of bytes to be sent. */
#define PROGRESS_CHRECEIVING    0x0011 /* While receiving a reply. Progress is related to the number of bytes received */
	/* The service is currently transferred between the client and the gateway */
#define PROGRESS_GWSENDING		0x0020 /* Sending a request to the gateway. Progress is related to the number of bytes sent */
#define PROGRESS_GWRECEIVING	0x0021 /* Receiving a reply from the gateway. Progress is related to the number of bytes received */
#define PROGRESS_GWPROCESSING   0x0022 /* The service has been sent to the gateway, which is currently working on the service.*/
	/* The service has been delivered to the target, which is now processing the service */
#define PROGRESS_TRGPROCESSING  0x1000 /* Target is processing the service. No further information. */
#define PROGRESS_SVCSPECIFIC    0x1001 /* Service specific progress IDs start here */
#define PROGRESS_USER           0x8000 /* Customer specific progress IDs start here */

/**
* <category>Channel server state</category>
* <description>
*	<ul>
*		<li>CSSTATE_FREE:		Channel is free</li>
*		<li>CSSTATE_OPEN:		Channel is open (in use)</li>
*		<li>CSSTATE_CLOSING:	Channel should be closed after removing all references</li>
*	</ul>
* </description>
*/
#define CSSTATE_FREE		UINT32_C(0x00000000)
#define CSSTATE_OPEN		UINT32_C(0x00000001)
#define CSSTATE_CLOSING		UINT32_C(0x00000002)

/* Channel information, which can be retrieved from higher layers. */
typedef struct
{
	RTS_UI8 ui8AddrOffset;			/* offset of relative addresses - valid if bAddrRelative is TRUE */
	RTS_UI8 ui8AddrPeerLen;			/* length of peer address */
	ADDRESSCOMPONENT  addrPeer[MAX_NODEADDR_LEN]; /* address of the communication partner */
	RTS_BOOL bAddrRelative;			/* peer address is a relativ address */
	RTS_BOOL bSecureChannel;		/* communication channel is encrypted */
	RTS_UI32 ui32ChannelHandle;		/* handle (id) of communication channel */
	RTS_UI32 ui32CommBufferSize;	/* effective buffer size of communication channel */
	RTS_UI32 ui32LastRecvTime;		/* last time a package was received on this channel */
	RTS_UI32 ui32LastSendTime;		/* last time a package was sent on this channel */
}CHANNELINFO;


typedef enum
{
	AT_ABSOLUTE = 0,
	AT_RELATIVE = 1
}ADDRESSTYPE;

typedef struct
{
	RTS_UI32 nLength;
	ADDRESSCOMPONENT address[MAX_NODEADDR_LEN];
} NODEADDRESS;

typedef struct
{
	RTS_UI32 nLength;
	ADDRESSCOMPONENT *pAddress;
} NODEADDRESSREF;

/* Describes the adress of a communication partner within the network tree. 
 * Examples:
 * (1) type=AT_ABSOLUTE, nAddrOffset=<any>, pAddress={2,3,4}, nLength=3 :
 *     specifies the node 2:3:4
 * (2) type=AT_RELATIVE, nAddrOffset=2, pAddress={5,6}, nLength=2 :
 *     "Move up two nodes, then go down to child 5 followed by child 6."
 *     If used on node 1:2:3 this address specifies the node 1:5:6.
 */
typedef struct
{
		/* Determines whether the specified address is a relative or an absolute address. */
	ADDRESSTYPE type;

		/* Only valid, if type==AT_RELATIVE. Contains the negative number of address components
		   to move up in the node tree, before going down the path specified in pAddress.
		   (e.g. "-1" to move up one level).
		   This field specifies the initial value of AdrIndex in router package header.
		*/
	RTS_I32 nAddrOffset;

		/* Number of valid elements in array pointed to by pAddress */
	RTS_UI32 nLength;

		/* Address of the node. Either the complete address (if type==AT_ABSOLUTE)
		   or the way down from the deepest common parent node 
		*/
	ADDRESSCOMPONENT *pAddress;
} PEERADDRESS;   


/* Describe the local address of a network interface, as used by its blockdriver.
 * A blockdriver provides the length L of an interface address in bits. 
 * In the first byte of pAddress only the x lowest bits may be used, where x = L % 8.
 * 
 * Eg.: 
 * ----
 *   L = 18 bit
 *  then nLength = 3 and bits 0 through 1 of pAddress[0] may be used.
 *  bits 2 through 7 of pAddress[0] are reserved and must be '0'.  
 */
typedef struct
{
 		/* length of the address. */
	RTS_UI32 nLength;
 		/* An array of bytes. */
	RTS_UI8 address[MAX_NETWORKADDR_LEN];
}NETWORKADDRESS;

/* This struct carries data between communication layers */
typedef struct 
{
	void * pData;
	RTS_UI32 ulCount;
} PROTOCOL_DATA_UNIT;


/** 
 * <description>
 * </description>
 * <result>
 *	Returns TRUE if addr1 == addr2, FALSE else 
 * </result>
 */
DEF_ITF_API(`RTS_BOOL',`CDECL',`AddrEquals',`(NODEADDRESS addr1, NODEADDRESS addr2)')

/** 
 * <description>
 * </description>
 * <result>
 *  Returns TRUE, if addr1 equals the address described by pBufAddr2 and nlenAddr2
 * </result>
 */
DEF_ITF_API(`RTS_BOOL',`CDECL',`AddrEqualsBuffer',`(NODEADDRESS addr1, ADDRESSCOMPONENT *pBufAddr2, RTS_UI32 nLenAddr2)') 

/* Copy the address in src to dest. 
 * <description>
 *  Copy the address in src to dest. 
 * </description>
 * <param name="pBufDest" type="OUT">Buffer, that will receive the copy of the address</param>
 * <param name="pnLenDest"  type="INOUT"> 
 *  Must be the maximum length of pDestBuf. Will be set to wSrcLen.
 * </param>
 * <param name="pBufSrc" type="IN">Contains the address to be copied.</param>
 * <param name="nLenSrc" type="IN">Length of the address to be copied.</param>
 * <result>
 * </result>
*/
DEF_ITF_API(`RTS_RESULT',`CDECL',`CopyAddrToBuffer',`(ADDRESSCOMPONENT *pBufDest, RTS_UI32 *pnLenDest, const ADDRESSCOMPONENT *pBufSrc, RTS_UI32 nLenSrc)')


#ifdef __cplusplus
	}
#endif 
