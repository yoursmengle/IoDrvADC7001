 /**
 * <interfacename>CmpChannelClientIec</interfacename>
 * <description>
 *	Interface for the IEC channel client.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPCHANNELCLIENTIECITF_H_
#define _CMPCHANNELCLIENTIECITF_H_

#include "CmpStd.h"

 

 




/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

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

void CDECL CDECL_EXT netclientclosechannel(netclientclosechannel_struct *p);
typedef void (CDECL CDECL_EXT* PFNETCLIENTCLOSECHANNEL_IEC) (netclientclosechannel_struct *p);
#if defined(CMPCHANNELCLIENTIEC_NOTIMPLEMENTED) || defined(NETCLIENTCLOSECHANNEL_NOTIMPLEMENTED)
	#define USE_netclientclosechannel
	#define EXT_netclientclosechannel
	#define GET_netclientclosechannel(fl)  ERR_NOTIMPLEMENTED
	#define CAL_netclientclosechannel(p0) 
	#define CHK_netclientclosechannel  FALSE
	#define EXP_netclientclosechannel  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_netclientclosechannel
	#define EXT_netclientclosechannel
	#define GET_netclientclosechannel(fl)  CAL_CMGETAPI( "netclientclosechannel" ) 
	#define CAL_netclientclosechannel  netclientclosechannel
	#define CHK_netclientclosechannel  TRUE
	#define EXP_netclientclosechannel  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"netclientclosechannel", (RTS_UINTPTR)netclientclosechannel, 1, 0xCA4B05BB, 0x03030128) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELCLIENTIEC_EXTERNAL)
	#define USE_netclientclosechannel
	#define EXT_netclientclosechannel
	#define GET_netclientclosechannel(fl)  CAL_CMGETAPI( "netclientclosechannel" ) 
	#define CAL_netclientclosechannel  netclientclosechannel
	#define CHK_netclientclosechannel  TRUE
	#define EXP_netclientclosechannel  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"netclientclosechannel", (RTS_UINTPTR)netclientclosechannel, 1, 0xCA4B05BB, 0x03030128) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelClientIecnetclientclosechannel
	#define EXT_CmpChannelClientIecnetclientclosechannel
	#define GET_CmpChannelClientIecnetclientclosechannel  ERR_OK
	#define CAL_CmpChannelClientIecnetclientclosechannel  netclientclosechannel
	#define CHK_CmpChannelClientIecnetclientclosechannel  TRUE
	#define EXP_CmpChannelClientIecnetclientclosechannel  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"netclientclosechannel", (RTS_UINTPTR)netclientclosechannel, 1, 0xCA4B05BB, 0x03030128) 
#elif defined(CPLUSPLUS)
	#define USE_netclientclosechannel
	#define EXT_netclientclosechannel
	#define GET_netclientclosechannel(fl)  CAL_CMGETAPI( "netclientclosechannel" ) 
	#define CAL_netclientclosechannel  netclientclosechannel
	#define CHK_netclientclosechannel  TRUE
	#define EXP_netclientclosechannel  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"netclientclosechannel", (RTS_UINTPTR)netclientclosechannel, 1, 0xCA4B05BB, 0x03030128) 
#else /* DYNAMIC_LINK */
	#define USE_netclientclosechannel  PFNETCLIENTCLOSECHANNEL_IEC pfnetclientclosechannel;
	#define EXT_netclientclosechannel  extern PFNETCLIENTCLOSECHANNEL_IEC pfnetclientclosechannel;
	#define GET_netclientclosechannel(fl)  s_pfCMGetAPI2( "netclientclosechannel", (RTS_VOID_FCTPTR *)&pfnetclientclosechannel, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xCA4B05BB, 0x03030128)
	#define CAL_netclientclosechannel  pfnetclientclosechannel
	#define CHK_netclientclosechannel  (pfnetclientclosechannel != NULL)
	#define EXP_netclientclosechannel   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"netclientclosechannel", (RTS_UINTPTR)netclientclosechannel, 1, 0xCA4B05BB, 0x03030128) 
#endif


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

void CDECL CDECL_EXT netclientopenchannel(netclientopenchannel_struct *p);
typedef void (CDECL CDECL_EXT* PFNETCLIENTOPENCHANNEL_IEC) (netclientopenchannel_struct *p);
#if defined(CMPCHANNELCLIENTIEC_NOTIMPLEMENTED) || defined(NETCLIENTOPENCHANNEL_NOTIMPLEMENTED)
	#define USE_netclientopenchannel
	#define EXT_netclientopenchannel
	#define GET_netclientopenchannel(fl)  ERR_NOTIMPLEMENTED
	#define CAL_netclientopenchannel(p0) 
	#define CHK_netclientopenchannel  FALSE
	#define EXP_netclientopenchannel  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_netclientopenchannel
	#define EXT_netclientopenchannel
	#define GET_netclientopenchannel(fl)  CAL_CMGETAPI( "netclientopenchannel" ) 
	#define CAL_netclientopenchannel  netclientopenchannel
	#define CHK_netclientopenchannel  TRUE
	#define EXP_netclientopenchannel  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"netclientopenchannel", (RTS_UINTPTR)netclientopenchannel, 1, 0x541D2FB1, 0x03030128) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELCLIENTIEC_EXTERNAL)
	#define USE_netclientopenchannel
	#define EXT_netclientopenchannel
	#define GET_netclientopenchannel(fl)  CAL_CMGETAPI( "netclientopenchannel" ) 
	#define CAL_netclientopenchannel  netclientopenchannel
	#define CHK_netclientopenchannel  TRUE
	#define EXP_netclientopenchannel  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"netclientopenchannel", (RTS_UINTPTR)netclientopenchannel, 1, 0x541D2FB1, 0x03030128) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelClientIecnetclientopenchannel
	#define EXT_CmpChannelClientIecnetclientopenchannel
	#define GET_CmpChannelClientIecnetclientopenchannel  ERR_OK
	#define CAL_CmpChannelClientIecnetclientopenchannel  netclientopenchannel
	#define CHK_CmpChannelClientIecnetclientopenchannel  TRUE
	#define EXP_CmpChannelClientIecnetclientopenchannel  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"netclientopenchannel", (RTS_UINTPTR)netclientopenchannel, 1, 0x541D2FB1, 0x03030128) 
#elif defined(CPLUSPLUS)
	#define USE_netclientopenchannel
	#define EXT_netclientopenchannel
	#define GET_netclientopenchannel(fl)  CAL_CMGETAPI( "netclientopenchannel" ) 
	#define CAL_netclientopenchannel  netclientopenchannel
	#define CHK_netclientopenchannel  TRUE
	#define EXP_netclientopenchannel  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"netclientopenchannel", (RTS_UINTPTR)netclientopenchannel, 1, 0x541D2FB1, 0x03030128) 
#else /* DYNAMIC_LINK */
	#define USE_netclientopenchannel  PFNETCLIENTOPENCHANNEL_IEC pfnetclientopenchannel;
	#define EXT_netclientopenchannel  extern PFNETCLIENTOPENCHANNEL_IEC pfnetclientopenchannel;
	#define GET_netclientopenchannel(fl)  s_pfCMGetAPI2( "netclientopenchannel", (RTS_VOID_FCTPTR *)&pfnetclientopenchannel, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x541D2FB1, 0x03030128)
	#define CAL_netclientopenchannel  pfnetclientopenchannel
	#define CHK_netclientopenchannel  (pfnetclientopenchannel != NULL)
	#define EXP_netclientopenchannel   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"netclientopenchannel", (RTS_UINTPTR)netclientopenchannel, 1, 0x541D2FB1, 0x03030128) 
#endif


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

void CDECL CDECL_EXT netclientopenchannelresult(netclientopenchannelresult_struct *p);
typedef void (CDECL CDECL_EXT* PFNETCLIENTOPENCHANNELRESULT_IEC) (netclientopenchannelresult_struct *p);
#if defined(CMPCHANNELCLIENTIEC_NOTIMPLEMENTED) || defined(NETCLIENTOPENCHANNELRESULT_NOTIMPLEMENTED)
	#define USE_netclientopenchannelresult
	#define EXT_netclientopenchannelresult
	#define GET_netclientopenchannelresult(fl)  ERR_NOTIMPLEMENTED
	#define CAL_netclientopenchannelresult(p0) 
	#define CHK_netclientopenchannelresult  FALSE
	#define EXP_netclientopenchannelresult  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_netclientopenchannelresult
	#define EXT_netclientopenchannelresult
	#define GET_netclientopenchannelresult(fl)  CAL_CMGETAPI( "netclientopenchannelresult" ) 
	#define CAL_netclientopenchannelresult  netclientopenchannelresult
	#define CHK_netclientopenchannelresult  TRUE
	#define EXP_netclientopenchannelresult  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"netclientopenchannelresult", (RTS_UINTPTR)netclientopenchannelresult, 1, 0x0552486B, 0x03030128) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELCLIENTIEC_EXTERNAL)
	#define USE_netclientopenchannelresult
	#define EXT_netclientopenchannelresult
	#define GET_netclientopenchannelresult(fl)  CAL_CMGETAPI( "netclientopenchannelresult" ) 
	#define CAL_netclientopenchannelresult  netclientopenchannelresult
	#define CHK_netclientopenchannelresult  TRUE
	#define EXP_netclientopenchannelresult  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"netclientopenchannelresult", (RTS_UINTPTR)netclientopenchannelresult, 1, 0x0552486B, 0x03030128) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelClientIecnetclientopenchannelresult
	#define EXT_CmpChannelClientIecnetclientopenchannelresult
	#define GET_CmpChannelClientIecnetclientopenchannelresult  ERR_OK
	#define CAL_CmpChannelClientIecnetclientopenchannelresult  netclientopenchannelresult
	#define CHK_CmpChannelClientIecnetclientopenchannelresult  TRUE
	#define EXP_CmpChannelClientIecnetclientopenchannelresult  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"netclientopenchannelresult", (RTS_UINTPTR)netclientopenchannelresult, 1, 0x0552486B, 0x03030128) 
#elif defined(CPLUSPLUS)
	#define USE_netclientopenchannelresult
	#define EXT_netclientopenchannelresult
	#define GET_netclientopenchannelresult(fl)  CAL_CMGETAPI( "netclientopenchannelresult" ) 
	#define CAL_netclientopenchannelresult  netclientopenchannelresult
	#define CHK_netclientopenchannelresult  TRUE
	#define EXP_netclientopenchannelresult  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"netclientopenchannelresult", (RTS_UINTPTR)netclientopenchannelresult, 1, 0x0552486B, 0x03030128) 
#else /* DYNAMIC_LINK */
	#define USE_netclientopenchannelresult  PFNETCLIENTOPENCHANNELRESULT_IEC pfnetclientopenchannelresult;
	#define EXT_netclientopenchannelresult  extern PFNETCLIENTOPENCHANNELRESULT_IEC pfnetclientopenchannelresult;
	#define GET_netclientopenchannelresult(fl)  s_pfCMGetAPI2( "netclientopenchannelresult", (RTS_VOID_FCTPTR *)&pfnetclientopenchannelresult, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0552486B, 0x03030128)
	#define CAL_netclientopenchannelresult  pfnetclientopenchannelresult
	#define CHK_netclientopenchannelresult  (pfnetclientopenchannelresult != NULL)
	#define EXP_netclientopenchannelresult   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"netclientopenchannelresult", (RTS_UINTPTR)netclientopenchannelresult, 1, 0x0552486B, 0x03030128) 
#endif


/**
 * <description>netclientsend</description>
 */
typedef struct tagnetclientsend_struct
{
	RTS_IEC_WORD wChannelHandle;		/* VAR_INPUT */	
	CHCProtocolDataUnit data;			/* VAR_INPUT */	
	RTS_IEC_UDINT NetClientSend;		/* VAR_OUTPUT */	
} netclientsend_struct;

void CDECL CDECL_EXT netclientsend(netclientsend_struct *p);
typedef void (CDECL CDECL_EXT* PFNETCLIENTSEND_IEC) (netclientsend_struct *p);
#if defined(CMPCHANNELCLIENTIEC_NOTIMPLEMENTED) || defined(NETCLIENTSEND_NOTIMPLEMENTED)
	#define USE_netclientsend
	#define EXT_netclientsend
	#define GET_netclientsend(fl)  ERR_NOTIMPLEMENTED
	#define CAL_netclientsend(p0) 
	#define CHK_netclientsend  FALSE
	#define EXP_netclientsend  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_netclientsend
	#define EXT_netclientsend
	#define GET_netclientsend(fl)  CAL_CMGETAPI( "netclientsend" ) 
	#define CAL_netclientsend  netclientsend
	#define CHK_netclientsend  TRUE
	#define EXP_netclientsend  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"netclientsend", (RTS_UINTPTR)netclientsend, 1, 0xF0001053, 0x03030128) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELCLIENTIEC_EXTERNAL)
	#define USE_netclientsend
	#define EXT_netclientsend
	#define GET_netclientsend(fl)  CAL_CMGETAPI( "netclientsend" ) 
	#define CAL_netclientsend  netclientsend
	#define CHK_netclientsend  TRUE
	#define EXP_netclientsend  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"netclientsend", (RTS_UINTPTR)netclientsend, 1, 0xF0001053, 0x03030128) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelClientIecnetclientsend
	#define EXT_CmpChannelClientIecnetclientsend
	#define GET_CmpChannelClientIecnetclientsend  ERR_OK
	#define CAL_CmpChannelClientIecnetclientsend  netclientsend
	#define CHK_CmpChannelClientIecnetclientsend  TRUE
	#define EXP_CmpChannelClientIecnetclientsend  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"netclientsend", (RTS_UINTPTR)netclientsend, 1, 0xF0001053, 0x03030128) 
#elif defined(CPLUSPLUS)
	#define USE_netclientsend
	#define EXT_netclientsend
	#define GET_netclientsend(fl)  CAL_CMGETAPI( "netclientsend" ) 
	#define CAL_netclientsend  netclientsend
	#define CHK_netclientsend  TRUE
	#define EXP_netclientsend  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"netclientsend", (RTS_UINTPTR)netclientsend, 1, 0xF0001053, 0x03030128) 
#else /* DYNAMIC_LINK */
	#define USE_netclientsend  PFNETCLIENTSEND_IEC pfnetclientsend;
	#define EXT_netclientsend  extern PFNETCLIENTSEND_IEC pfnetclientsend;
	#define GET_netclientsend(fl)  s_pfCMGetAPI2( "netclientsend", (RTS_VOID_FCTPTR *)&pfnetclientsend, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xF0001053, 0x03030128)
	#define CAL_netclientsend  pfnetclientsend
	#define CHK_netclientsend  (pfnetclientsend != NULL)
	#define EXP_netclientsend   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"netclientsend", (RTS_UINTPTR)netclientsend, 1, 0xF0001053, 0x03030128) 
#endif


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



typedef struct
{
	IBase_C *pBase;
} ICmpChannelClientIec_C;

#ifdef CPLUSPLUS
class ICmpChannelClientIec : public IBase
{
	public:
};
	#ifndef ITF_CmpChannelClientIec
		#define ITF_CmpChannelClientIec static ICmpChannelClientIec *pICmpChannelClientIec = NULL;
	#endif
	#define EXTITF_CmpChannelClientIec
#else	/*CPLUSPLUS*/
	typedef ICmpChannelClientIec_C		ICmpChannelClientIec;
	#ifndef ITF_CmpChannelClientIec
		#define ITF_CmpChannelClientIec
	#endif
	#define EXTITF_CmpChannelClientIec
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCHANNELCLIENTIECITF_H_*/
