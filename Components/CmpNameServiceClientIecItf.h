 /**
 * <interfacename>CmpNameServiceClientIec</interfacename>
 * <description> 
 *	Iec interface to the naming service client.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPNAMESERVICECLIENTIECITF_H_
#define _CMPNAMESERVICECLIENTIECITF_H_

#include "CmpStd.h"

 

 




#include "CmpNameService.h"

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Constants</description>
 */
#define MAXNODEADDRLENGTH		0xF	

/**
 * <description>NSC_AddrComponent</description>
 */
typedef struct tagNSC_AddrComponent
{
	RTS_IEC_BYTE Component[2];		
} NSC_AddrComponent;

/**
 * <description>NSC_NodeAddress</description>
 */
typedef struct tagNSC_NodeAddress
{
	RTS_IEC_UDINT nAddrComponentCount;		
	NSC_AddrComponent AddrComponents[MAXNODEADDRLENGTH - 1 + 1];		
} NSC_NodeAddress;

/**
 * This is the structure as it is passed from the callback function
 */
typedef struct tagNSC_NodeInfoExt
{
	RTS_IEC_UINT uiMaxChannels;		
	RTS_IEC_BOOL bIntelByteOrder;		
	RTS_IEC_USINT byDummy;		
	RTS_IEC_UINT uiParentAddrSize;		
	RTS_IEC_UINT uiNodeNameLength;		
	RTS_IEC_UINT uiDeviceNameLength;		
	RTS_IEC_UINT uiVendorNameLength;		
	RTS_IEC_UDINT udiTargetType;		
	RTS_IEC_UDINT udiTargetId;		
	RTS_IEC_UDINT udiTargetVersion;		
	RTS_IEC_BYTE *pDynamicLengthData;		/* The dynamic fields are (in this order):
   - addrParent (wParentAddrSize NSC_AddrComponent components) followed by
   - node name (zero terminated wide-char string) followed by
   - device name (zero terminated wide-char string) followed by
   - type description (zero terminated wide-char string)
   If wParentAddrSize is zero (i.e. node has no parent) then the node name
   starts immediatly at position offsetof(addrParent).
 */
} NSC_NodeInfoExt;

/**
 * Close an instance of the nameservice client. Callbacks that arrive after the client has been closed will no longer be forwarded.
 * Returns the result of the operation, ERR_OK if a valid instance has been given in.
 */
typedef struct tagnsclientclose_struct
{
	RTS_IEC_HANDLE hNSClient;			/* VAR_INPUT */	/* Handle of the nameservice client that is to be closed */
	RTS_IEC_RESULT NSClientClose;		/* VAR_OUTPUT */	
} nsclientclose_struct;

void CDECL CDECL_EXT nsclientclose(nsclientclose_struct *p);
typedef void (CDECL CDECL_EXT* PFNSCLIENTCLOSE_IEC) (nsclientclose_struct *p);
#if defined(CMPNAMESERVICECLIENTIEC_NOTIMPLEMENTED) || defined(NSCLIENTCLOSE_NOTIMPLEMENTED)
	#define USE_nsclientclose
	#define EXT_nsclientclose
	#define GET_nsclientclose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_nsclientclose(p0) 
	#define CHK_nsclientclose  FALSE
	#define EXP_nsclientclose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_nsclientclose
	#define EXT_nsclientclose
	#define GET_nsclientclose(fl)  CAL_CMGETAPI( "nsclientclose" ) 
	#define CAL_nsclientclose  nsclientclose
	#define CHK_nsclientclose  TRUE
	#define EXP_nsclientclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nsclientclose", (RTS_UINTPTR)nsclientclose, 1, RTSITF_GET_SIGNATURE(0, 0x739FD2C5), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPNAMESERVICECLIENTIEC_EXTERNAL)
	#define USE_nsclientclose
	#define EXT_nsclientclose
	#define GET_nsclientclose(fl)  CAL_CMGETAPI( "nsclientclose" ) 
	#define CAL_nsclientclose  nsclientclose
	#define CHK_nsclientclose  TRUE
	#define EXP_nsclientclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nsclientclose", (RTS_UINTPTR)nsclientclose, 1, RTSITF_GET_SIGNATURE(0, 0x739FD2C5), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpNameServiceClientIecnsclientclose
	#define EXT_CmpNameServiceClientIecnsclientclose
	#define GET_CmpNameServiceClientIecnsclientclose  ERR_OK
	#define CAL_CmpNameServiceClientIecnsclientclose  nsclientclose
	#define CHK_CmpNameServiceClientIecnsclientclose  TRUE
	#define EXP_CmpNameServiceClientIecnsclientclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nsclientclose", (RTS_UINTPTR)nsclientclose, 1, RTSITF_GET_SIGNATURE(0, 0x739FD2C5), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_nsclientclose
	#define EXT_nsclientclose
	#define GET_nsclientclose(fl)  CAL_CMGETAPI( "nsclientclose" ) 
	#define CAL_nsclientclose  nsclientclose
	#define CHK_nsclientclose  TRUE
	#define EXP_nsclientclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nsclientclose", (RTS_UINTPTR)nsclientclose, 1, RTSITF_GET_SIGNATURE(0, 0x739FD2C5), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_nsclientclose  PFNSCLIENTCLOSE_IEC pfnsclientclose;
	#define EXT_nsclientclose  extern PFNSCLIENTCLOSE_IEC pfnsclientclose;
	#define GET_nsclientclose(fl)  s_pfCMGetAPI2( "nsclientclose", (RTS_VOID_FCTPTR *)&pfnsclientclose, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x739FD2C5), 0x03050500)
	#define CAL_nsclientclose  pfnsclientclose
	#define CHK_nsclientclose  (pfnsclientclose != NULL)
	#define EXP_nsclientclose   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nsclientclose", (RTS_UINTPTR)nsclientclose, 1, RTSITF_GET_SIGNATURE(0, 0x739FD2C5), 0x03050500) 
#endif


/**
 * Opens an instance of the nameservice client. Returns the handle to the created name service client.
 */
typedef struct tagnsclientopen_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Will optionally receive an error code if the creation of a nameservice client has failed. Otherwise ERR_OK will be returned. */
	RTS_IEC_HANDLE NSClientOpen;		/* VAR_OUTPUT */	
} nsclientopen_struct;

void CDECL CDECL_EXT nsclientopen(nsclientopen_struct *p);
typedef void (CDECL CDECL_EXT* PFNSCLIENTOPEN_IEC) (nsclientopen_struct *p);
#if defined(CMPNAMESERVICECLIENTIEC_NOTIMPLEMENTED) || defined(NSCLIENTOPEN_NOTIMPLEMENTED)
	#define USE_nsclientopen
	#define EXT_nsclientopen
	#define GET_nsclientopen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_nsclientopen(p0) 
	#define CHK_nsclientopen  FALSE
	#define EXP_nsclientopen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_nsclientopen
	#define EXT_nsclientopen
	#define GET_nsclientopen(fl)  CAL_CMGETAPI( "nsclientopen" ) 
	#define CAL_nsclientopen  nsclientopen
	#define CHK_nsclientopen  TRUE
	#define EXP_nsclientopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nsclientopen", (RTS_UINTPTR)nsclientopen, 1, RTSITF_GET_SIGNATURE(0, 0xD17DF797), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPNAMESERVICECLIENTIEC_EXTERNAL)
	#define USE_nsclientopen
	#define EXT_nsclientopen
	#define GET_nsclientopen(fl)  CAL_CMGETAPI( "nsclientopen" ) 
	#define CAL_nsclientopen  nsclientopen
	#define CHK_nsclientopen  TRUE
	#define EXP_nsclientopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nsclientopen", (RTS_UINTPTR)nsclientopen, 1, RTSITF_GET_SIGNATURE(0, 0xD17DF797), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpNameServiceClientIecnsclientopen
	#define EXT_CmpNameServiceClientIecnsclientopen
	#define GET_CmpNameServiceClientIecnsclientopen  ERR_OK
	#define CAL_CmpNameServiceClientIecnsclientopen  nsclientopen
	#define CHK_CmpNameServiceClientIecnsclientopen  TRUE
	#define EXP_CmpNameServiceClientIecnsclientopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nsclientopen", (RTS_UINTPTR)nsclientopen, 1, RTSITF_GET_SIGNATURE(0, 0xD17DF797), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_nsclientopen
	#define EXT_nsclientopen
	#define GET_nsclientopen(fl)  CAL_CMGETAPI( "nsclientopen" ) 
	#define CAL_nsclientopen  nsclientopen
	#define CHK_nsclientopen  TRUE
	#define EXP_nsclientopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nsclientopen", (RTS_UINTPTR)nsclientopen, 1, RTSITF_GET_SIGNATURE(0, 0xD17DF797), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_nsclientopen  PFNSCLIENTOPEN_IEC pfnsclientopen;
	#define EXT_nsclientopen  extern PFNSCLIENTOPEN_IEC pfnsclientopen;
	#define GET_nsclientopen(fl)  s_pfCMGetAPI2( "nsclientopen", (RTS_VOID_FCTPTR *)&pfnsclientopen, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xD17DF797), 0x03050500)
	#define CAL_nsclientopen  pfnsclientopen
	#define CHK_nsclientopen  (pfnsclientopen != NULL)
	#define EXP_nsclientopen   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nsclientopen", (RTS_UINTPTR)nsclientopen, 1, RTSITF_GET_SIGNATURE(0, 0xD17DF797), 0x03050500) 
#endif


/**
 * Initiates the resolving of all available runtimes. Returns the result of the operation.
 */
typedef struct tagnsclientresolveall_struct
{
	RTS_IEC_HANDLE hNSClient;			/* VAR_INPUT */	/* The instance of a nameservice client that shall to do the nameresolving */
	RTS_IEC_UXINT udiReqId;				/* VAR_INPUT */	/* Identifies the request. */
	RTS_IEC_BYTE *pfnResponseCallback;	/* VAR_INPUT */	/* Prototype see NSClientResponseCallback. This callback will be triggered for each available node */
	RTS_IEC_RESULT NSClientResolveAll;	/* VAR_OUTPUT */	
} nsclientresolveall_struct;

void CDECL CDECL_EXT nsclientresolveall(nsclientresolveall_struct *p);
typedef void (CDECL CDECL_EXT* PFNSCLIENTRESOLVEALL_IEC) (nsclientresolveall_struct *p);
#if defined(CMPNAMESERVICECLIENTIEC_NOTIMPLEMENTED) || defined(NSCLIENTRESOLVEALL_NOTIMPLEMENTED)
	#define USE_nsclientresolveall
	#define EXT_nsclientresolveall
	#define GET_nsclientresolveall(fl)  ERR_NOTIMPLEMENTED
	#define CAL_nsclientresolveall(p0) 
	#define CHK_nsclientresolveall  FALSE
	#define EXP_nsclientresolveall  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_nsclientresolveall
	#define EXT_nsclientresolveall
	#define GET_nsclientresolveall(fl)  CAL_CMGETAPI( "nsclientresolveall" ) 
	#define CAL_nsclientresolveall  nsclientresolveall
	#define CHK_nsclientresolveall  TRUE
	#define EXP_nsclientresolveall  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nsclientresolveall", (RTS_UINTPTR)nsclientresolveall, 1, RTSITF_GET_SIGNATURE(0, 0xF500D28F), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPNAMESERVICECLIENTIEC_EXTERNAL)
	#define USE_nsclientresolveall
	#define EXT_nsclientresolveall
	#define GET_nsclientresolveall(fl)  CAL_CMGETAPI( "nsclientresolveall" ) 
	#define CAL_nsclientresolveall  nsclientresolveall
	#define CHK_nsclientresolveall  TRUE
	#define EXP_nsclientresolveall  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nsclientresolveall", (RTS_UINTPTR)nsclientresolveall, 1, RTSITF_GET_SIGNATURE(0, 0xF500D28F), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpNameServiceClientIecnsclientresolveall
	#define EXT_CmpNameServiceClientIecnsclientresolveall
	#define GET_CmpNameServiceClientIecnsclientresolveall  ERR_OK
	#define CAL_CmpNameServiceClientIecnsclientresolveall  nsclientresolveall
	#define CHK_CmpNameServiceClientIecnsclientresolveall  TRUE
	#define EXP_CmpNameServiceClientIecnsclientresolveall  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nsclientresolveall", (RTS_UINTPTR)nsclientresolveall, 1, RTSITF_GET_SIGNATURE(0, 0xF500D28F), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_nsclientresolveall
	#define EXT_nsclientresolveall
	#define GET_nsclientresolveall(fl)  CAL_CMGETAPI( "nsclientresolveall" ) 
	#define CAL_nsclientresolveall  nsclientresolveall
	#define CHK_nsclientresolveall  TRUE
	#define EXP_nsclientresolveall  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nsclientresolveall", (RTS_UINTPTR)nsclientresolveall, 1, RTSITF_GET_SIGNATURE(0, 0xF500D28F), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_nsclientresolveall  PFNSCLIENTRESOLVEALL_IEC pfnsclientresolveall;
	#define EXT_nsclientresolveall  extern PFNSCLIENTRESOLVEALL_IEC pfnsclientresolveall;
	#define GET_nsclientresolveall(fl)  s_pfCMGetAPI2( "nsclientresolveall", (RTS_VOID_FCTPTR *)&pfnsclientresolveall, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xF500D28F), 0x03050500)
	#define CAL_nsclientresolveall  pfnsclientresolveall
	#define CHK_nsclientresolveall  (pfnsclientresolveall != NULL)
	#define EXP_nsclientresolveall   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nsclientresolveall", (RTS_UINTPTR)nsclientresolveall, 1, RTSITF_GET_SIGNATURE(0, 0xF500D28F), 0x03050500) 
#endif


/**
 * This is only a prototype for the function that will be called when a node has been found.
 * Only used to export the callback interface for generating the m4 runtime system files.
 * There is no implementation behind that....
 * Must not be called!!!
 */
typedef struct tagnsclientresponsecallback_struct
{
	RTS_IEC_RESULT udiResult;			/* VAR_INPUT */	
	NSC_NodeAddress addrNode;			/* VAR_INPUT */	
	NSC_NodeInfoExt *pNodeInfo;			/* VAR_INPUT */	
	RTS_IEC_WORD wVersion;				/* VAR_INPUT */	
	RTS_IEC_UXINT udiReqId;				/* VAR_INPUT */	
	RTS_IEC_BOOL bComplete;				/* VAR_INPUT */	
	RTS_IEC_UDINT NSClientResponseCallback;	/* VAR_OUTPUT */	
} nsclientresponsecallback_struct;


/* DEF_API(`void',`CDECL',`nsclientresponsecallback',`(nsclientresponsecallback_struct *p)',1,0,0x03050500) */
/* Callback interfaces are not yet supported by the CODESYS m4 export, therefore the type is manually defined here. */ 
typedef void (CDECL *PFNSCLIENTRESPONSECALLBACK_IEC) (nsclientresponsecallback_struct *p);


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/



typedef struct
{
	IBase_C *pBase;
} ICmpNameServiceClientIec_C;

#ifdef CPLUSPLUS
class ICmpNameServiceClientIec : public IBase
{
	public:
};
	#ifndef ITF_CmpNameServiceClientIec
		#define ITF_CmpNameServiceClientIec static ICmpNameServiceClientIec *pICmpNameServiceClientIec = NULL;
	#endif
	#define EXTITF_CmpNameServiceClientIec
#else	/*CPLUSPLUS*/
	typedef ICmpNameServiceClientIec_C		ICmpNameServiceClientIec;
	#ifndef ITF_CmpNameServiceClientIec
		#define ITF_CmpNameServiceClientIec
	#endif
	#define EXTITF_CmpNameServiceClientIec
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPNAMESERVICECLIENTIECITF_H_*/
