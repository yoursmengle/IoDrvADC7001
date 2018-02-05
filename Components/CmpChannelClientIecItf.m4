/**
 * <interfacename>CmpChannelClientIec</interfacename>
 * <description>
 *	Interface for the IEC channel client.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpChannelClientIec')

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Constants</description>
 */
#define MAX_NODE_ADDR_LEN		RTS_IEC_INT_C(0xF)	

/**
 * <description>Enum: CHCAddressType</description>
 */
#define CHCADDRESSTYPE_ABSOLUTE    RTS_IEC_DINT_C(0x0)	
#define CHCADDRESSTYPE_RELATIVE    RTS_IEC_DINT_C(0x1)	
/* Typed enum definition */
#define CHCADDRESSTYPE    RTS_IEC_DINT

/**
 * <description>Enum: Test_State</description>
 */
#define TEST_STATE_START    RTS_IEC_INT_C(0x0)	
#define TEST_STATE_CREATINGCHANNEL    RTS_IEC_INT_C(0x1)	
#define TEST_STATE_CHANNELCREATED    RTS_IEC_INT_C(0x2)	
#define TEST_STATE_SENDING    RTS_IEC_INT_C(0x3)	
#define TEST_STATE_RECEIVED    RTS_IEC_INT_C(0x4)	
#define TEST_STATE_CLOSING    RTS_IEC_INT_C(0x5)	
#define TEST_STATE_CLOSED    RTS_IEC_INT_C(0x6)	
#define TEST_STATE_ERROR    RTS_IEC_INT_C(0x7)	
/* Typed enum definition */
#define TEST_STATE    RTS_IEC_INT

/**
 * <description>CHCAddressComponent</description>
 */
typedef struct tagCHCAddressComponent
{
	RTS_IEC_BYTE Components[2];		
} CHCAddressComponent;

/**
 * <description>CHCPeerAddress</description>
 */
typedef struct tagCHCPeerAddress
{
	RTS_IEC_DWORD dwStructSize;		
	RTS_IEC_DINT addrType;		/* / Determines whether the specified address is a relative OR an absolute address. */
	RTS_IEC_DINT nAddrOffset;		/* Only valid, if type==AT_RELATIVE. Contains the negative number of address components
 to move up in the node tree, before going down the path specified in pAddress.
 (e.g. "-1" to move up one level).
 This field specifies the initial value of AdrIndex in router package header. */
	RTS_IEC_UDINT nAddrLength;		/* Number of valid elements in array pointed to by pAddress */
	RTS_IEC_UDINT nAddrComponentCount;		/* For possible extensibility of further address components */
	CHCAddressComponent addrComponents[MAX_NODE_ADDR_LEN - 1 + 1];		
} CHCPeerAddress;

/**
 * <description>CHCProtocolDataUnit</description>
 */
typedef struct tagCHCProtocolDataUnit
{
	RTS_IEC_DWORD dwSize;		
	RTS_IEC_BYTE *pData;		
} CHCProtocolDataUnit;

/**
 * <description>netclientclosechannel</description>
 */
typedef struct tagnetclientclosechannel_struct
{
	RTS_IEC_WORD wChannelHandle;		/* VAR_INPUT */	
	RTS_IEC_UDINT NetClientCloseChannel;	/* VAR_OUTPUT */	
} netclientclosechannel_struct;

DEF_API(`void',`CDECL',`netclientclosechannel',`(netclientclosechannel_struct *p)',1,0xCA4B05BB,0x03030128)

/**
 * <description>netclientopenchannel</description>
 */
typedef struct tagnetclientopenchannel_struct
{
	CHCPeerAddress addr;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwCommBuffSize;		/* VAR_INPUT */	
	RTS_IEC_DWORD *pdwReqId;			/* VAR_INPUT */	
	RTS_IEC_BYTE *pfnReceiveCallback;	/* VAR_INPUT */	/* Prototype see NetClientReplyReceivedProc */
	RTS_IEC_BYTE *pfnChannelErrorCallback;	/* VAR_INPUT */	/* Prototype see NetClientOpenChannelResult */
	RTS_IEC_UDINT NetClientOpenChannel;	/* VAR_OUTPUT */	
} netclientopenchannel_struct;

DEF_API(`void',`CDECL',`netclientopenchannel',`(netclientopenchannel_struct *p)',1,0x541D2FB1,0x03030128)

/**
 * <description>netclientopenchannelresult</description>
 */
typedef struct tagnetclientopenchannelresult_struct
{
	RTS_IEC_DWORD dwRequestId;			/* VAR_INPUT */	
	RTS_IEC_WORD *pwChannelHandle;		/* VAR_INPUT */	
	RTS_IEC_DWORD *pdwCommBufferSize;	/* VAR_INPUT */	
	RTS_IEC_BOOL *pbBigEndianByteOrder;	/* VAR_INPUT */	
	RTS_IEC_UDINT NetClientOpenChannelResult;	/* VAR_OUTPUT */	
} netclientopenchannelresult_struct;

DEF_API(`void',`CDECL',`netclientopenchannelresult',`(netclientopenchannelresult_struct *p)',1,0x0552486B,0x03030128)

/**
 * <description>netclientsend</description>
 */
typedef struct tagnetclientsend_struct
{
	RTS_IEC_WORD wChannelHandle;		/* VAR_INPUT */	
	CHCProtocolDataUnit data;			/* VAR_INPUT */	
	RTS_IEC_UDINT NetClientSend;		/* VAR_OUTPUT */	
} netclientsend_struct;

DEF_API(`void',`CDECL',`netclientsend',`(netclientsend_struct *p)',1,0xF0001053,0x03030128)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

/* callback to IEC. See prototypes of NetClientChannelError and NetClientReplyReceivedProc */
typedef struct tagnetclientchannelerror_struct
{
	RTS_IEC_WORD wChannelHandle;
	RTS_IEC_UDINT diError;
    RTS_IEC_UDINT NetClientChannelError;
} netclientchannelerror_struct;

typedef struct tagnetclientreplyreceivedproc_struct
{
	RTS_IEC_WORD wChannelHandle;
	CHCProtocolDataUnit data;
    RTS_IEC_UDINT NetClientReplyReceivedProc;
} netclientreplyreceivedproc_struct;


typedef void (CDECL *PFNETCLIENTREPLYRECEIVEDCALLBACK)(netclientreplyreceivedproc_struct* p);
typedef void (CDECL *PFNETCLIENTCHANNELERRORCALLBACK)(netclientchannelerror_struct* p);
