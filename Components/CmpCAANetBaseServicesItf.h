 
	
	
#ifndef _CMPCAANETBASESERVICESITF_H_
#define _CMPCAANETBASESERVICESITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAAAsyncMan.h"
#include "CAAMemBlockMan.h"
#include "CAANetBaseServices.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>nbs_udp_getdatasize_struct</description>
 */
typedef struct nbs_udp_getdatasize_struct_tag
{
CAA_HANDLE hPeer;					/* VAR_INPUT */
      CAA_ERROR *peError;               /* VAR_INPUT */
      CAA_SIZE UDP_GetDataSize;     /* VAR_OUTPUT */
} nbs_udp_getdatasize_struct; 

void CDECL CDECL_EXT nbs_udp_getdatasize(nbs_udp_getdatasize_struct *p);
typedef void (CDECL CDECL_EXT* PFNBS_UDP_GETDATASIZE_IEC) (nbs_udp_getdatasize_struct *p);
#if defined(CMPCAANETBASESERVICES_NOTIMPLEMENTED) || defined(NBS_UDP_GETDATASIZE_NOTIMPLEMENTED)
	#define USE_nbs_udp_getdatasize
	#define EXT_nbs_udp_getdatasize
	#define GET_nbs_udp_getdatasize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_nbs_udp_getdatasize(p0) 
	#define CHK_nbs_udp_getdatasize  FALSE
	#define EXP_nbs_udp_getdatasize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_nbs_udp_getdatasize
	#define EXT_nbs_udp_getdatasize
	#define GET_nbs_udp_getdatasize(fl)  CAL_CMGETAPI( "nbs_udp_getdatasize" ) 
	#define CAL_nbs_udp_getdatasize  nbs_udp_getdatasize
	#define CHK_nbs_udp_getdatasize  TRUE
	#define EXP_nbs_udp_getdatasize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nbs_udp_getdatasize", (RTS_UINTPTR)nbs_udp_getdatasize, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAANETBASESERVICES_EXTERNAL)
	#define USE_nbs_udp_getdatasize
	#define EXT_nbs_udp_getdatasize
	#define GET_nbs_udp_getdatasize(fl)  CAL_CMGETAPI( "nbs_udp_getdatasize" ) 
	#define CAL_nbs_udp_getdatasize  nbs_udp_getdatasize
	#define CHK_nbs_udp_getdatasize  TRUE
	#define EXP_nbs_udp_getdatasize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nbs_udp_getdatasize", (RTS_UINTPTR)nbs_udp_getdatasize, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAANetBaseServicesnbs_udp_getdatasize
	#define EXT_CmpCAANetBaseServicesnbs_udp_getdatasize
	#define GET_CmpCAANetBaseServicesnbs_udp_getdatasize  ERR_OK
	#define CAL_CmpCAANetBaseServicesnbs_udp_getdatasize  nbs_udp_getdatasize
	#define CHK_CmpCAANetBaseServicesnbs_udp_getdatasize  TRUE
	#define EXP_CmpCAANetBaseServicesnbs_udp_getdatasize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nbs_udp_getdatasize", (RTS_UINTPTR)nbs_udp_getdatasize, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_nbs_udp_getdatasize
	#define EXT_nbs_udp_getdatasize
	#define GET_nbs_udp_getdatasize(fl)  CAL_CMGETAPI( "nbs_udp_getdatasize" ) 
	#define CAL_nbs_udp_getdatasize  nbs_udp_getdatasize
	#define CHK_nbs_udp_getdatasize  TRUE
	#define EXP_nbs_udp_getdatasize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nbs_udp_getdatasize", (RTS_UINTPTR)nbs_udp_getdatasize, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_nbs_udp_getdatasize  PFNBS_UDP_GETDATASIZE_IEC pfnbs_udp_getdatasize;
	#define EXT_nbs_udp_getdatasize  extern PFNBS_UDP_GETDATASIZE_IEC pfnbs_udp_getdatasize;
	#define GET_nbs_udp_getdatasize(fl)  s_pfCMGetAPI2( "nbs_udp_getdatasize", (RTS_VOID_FCTPTR *)&pfnbs_udp_getdatasize, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_nbs_udp_getdatasize  pfnbs_udp_getdatasize
	#define CHK_nbs_udp_getdatasize  (pfnbs_udp_getdatasize != NULL)
	#define EXP_nbs_udp_getdatasize   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"nbs_udp_getdatasize", (RTS_UINTPTR)nbs_udp_getdatasize, 1, 0x0, 0x0) 
#endif


CAA_ERROR CDECL NBS_WorkerInit(void);
typedef CAA_ERROR (CDECL * PFNBS_WORKERINIT) (void);
#if defined(CMPCAANETBASESERVICES_NOTIMPLEMENTED) || defined(NBS_WORKERINIT_NOTIMPLEMENTED)
	#define USE_NBS_WorkerInit
	#define EXT_NBS_WorkerInit
	#define GET_NBS_WorkerInit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_NBS_WorkerInit()  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_NBS_WorkerInit  FALSE
	#define EXP_NBS_WorkerInit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_NBS_WorkerInit
	#define EXT_NBS_WorkerInit
	#define GET_NBS_WorkerInit(fl)  CAL_CMGETAPI( "NBS_WorkerInit" ) 
	#define CAL_NBS_WorkerInit  NBS_WorkerInit
	#define CHK_NBS_WorkerInit  TRUE
	#define EXP_NBS_WorkerInit  CAL_CMEXPAPI( "NBS_WorkerInit" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAANETBASESERVICES_EXTERNAL)
	#define USE_NBS_WorkerInit
	#define EXT_NBS_WorkerInit
	#define GET_NBS_WorkerInit(fl)  CAL_CMGETAPI( "NBS_WorkerInit" ) 
	#define CAL_NBS_WorkerInit  NBS_WorkerInit
	#define CHK_NBS_WorkerInit  TRUE
	#define EXP_NBS_WorkerInit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NBS_WorkerInit", (RTS_UINTPTR)NBS_WorkerInit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAANetBaseServicesNBS_WorkerInit
	#define EXT_CmpCAANetBaseServicesNBS_WorkerInit
	#define GET_CmpCAANetBaseServicesNBS_WorkerInit  ERR_OK
	#define CAL_CmpCAANetBaseServicesNBS_WorkerInit pICmpCAANetBaseServices->INBS_WorkerInit
	#define CHK_CmpCAANetBaseServicesNBS_WorkerInit (pICmpCAANetBaseServices != NULL)
	#define EXP_CmpCAANetBaseServicesNBS_WorkerInit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_NBS_WorkerInit
	#define EXT_NBS_WorkerInit
	#define GET_NBS_WorkerInit(fl)  CAL_CMGETAPI( "NBS_WorkerInit" ) 
	#define CAL_NBS_WorkerInit pICmpCAANetBaseServices->INBS_WorkerInit
	#define CHK_NBS_WorkerInit (pICmpCAANetBaseServices != NULL)
	#define EXP_NBS_WorkerInit  CAL_CMEXPAPI( "NBS_WorkerInit" ) 
#else /* DYNAMIC_LINK */
	#define USE_NBS_WorkerInit  PFNBS_WORKERINIT pfNBS_WorkerInit;
	#define EXT_NBS_WorkerInit  extern PFNBS_WORKERINIT pfNBS_WorkerInit;
	#define GET_NBS_WorkerInit(fl)  s_pfCMGetAPI2( "NBS_WorkerInit", (RTS_VOID_FCTPTR *)&pfNBS_WorkerInit, (fl), 0, 0)
	#define CAL_NBS_WorkerInit  pfNBS_WorkerInit
	#define CHK_NBS_WorkerInit  (pfNBS_WorkerInit != NULL)
	#define EXP_NBS_WorkerInit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NBS_WorkerInit", (RTS_UINTPTR)NBS_WorkerInit, 0, 0) 
#endif



CAA_ERROR CDECL NBS_WorkerExit(void);
typedef CAA_ERROR (CDECL * PFNBS_WORKEREXIT) (void);
#if defined(CMPCAANETBASESERVICES_NOTIMPLEMENTED) || defined(NBS_WORKEREXIT_NOTIMPLEMENTED)
	#define USE_NBS_WorkerExit
	#define EXT_NBS_WorkerExit
	#define GET_NBS_WorkerExit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_NBS_WorkerExit()  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_NBS_WorkerExit  FALSE
	#define EXP_NBS_WorkerExit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_NBS_WorkerExit
	#define EXT_NBS_WorkerExit
	#define GET_NBS_WorkerExit(fl)  CAL_CMGETAPI( "NBS_WorkerExit" ) 
	#define CAL_NBS_WorkerExit  NBS_WorkerExit
	#define CHK_NBS_WorkerExit  TRUE
	#define EXP_NBS_WorkerExit  CAL_CMEXPAPI( "NBS_WorkerExit" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAANETBASESERVICES_EXTERNAL)
	#define USE_NBS_WorkerExit
	#define EXT_NBS_WorkerExit
	#define GET_NBS_WorkerExit(fl)  CAL_CMGETAPI( "NBS_WorkerExit" ) 
	#define CAL_NBS_WorkerExit  NBS_WorkerExit
	#define CHK_NBS_WorkerExit  TRUE
	#define EXP_NBS_WorkerExit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NBS_WorkerExit", (RTS_UINTPTR)NBS_WorkerExit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAANetBaseServicesNBS_WorkerExit
	#define EXT_CmpCAANetBaseServicesNBS_WorkerExit
	#define GET_CmpCAANetBaseServicesNBS_WorkerExit  ERR_OK
	#define CAL_CmpCAANetBaseServicesNBS_WorkerExit pICmpCAANetBaseServices->INBS_WorkerExit
	#define CHK_CmpCAANetBaseServicesNBS_WorkerExit (pICmpCAANetBaseServices != NULL)
	#define EXP_CmpCAANetBaseServicesNBS_WorkerExit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_NBS_WorkerExit
	#define EXT_NBS_WorkerExit
	#define GET_NBS_WorkerExit(fl)  CAL_CMGETAPI( "NBS_WorkerExit" ) 
	#define CAL_NBS_WorkerExit pICmpCAANetBaseServices->INBS_WorkerExit
	#define CHK_NBS_WorkerExit (pICmpCAANetBaseServices != NULL)
	#define EXP_NBS_WorkerExit  CAL_CMEXPAPI( "NBS_WorkerExit" ) 
#else /* DYNAMIC_LINK */
	#define USE_NBS_WorkerExit  PFNBS_WORKEREXIT pfNBS_WorkerExit;
	#define EXT_NBS_WorkerExit  extern PFNBS_WORKEREXIT pfNBS_WorkerExit;
	#define GET_NBS_WorkerExit(fl)  s_pfCMGetAPI2( "NBS_WorkerExit", (RTS_VOID_FCTPTR *)&pfNBS_WorkerExit, (fl), 0, 0)
	#define CAL_NBS_WorkerExit  pfNBS_WorkerExit
	#define CHK_NBS_WorkerExit  (pfNBS_WorkerExit != NULL)
	#define EXP_NBS_WorkerExit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NBS_WorkerExit", (RTS_UINTPTR)NBS_WorkerExit, 0, 0) 
#endif



CAA_SIZE CDECL NBS_UDP_GetDataSize(CAA_HANDLE hPeer, CAA_ERROR* peError);
typedef CAA_SIZE (CDECL * PFNBS_UDP_GETDATASIZE) (CAA_HANDLE hPeer, CAA_ERROR* peError);
#if defined(CMPCAANETBASESERVICES_NOTIMPLEMENTED) || defined(NBS_UDP_GETDATASIZE_NOTIMPLEMENTED)
	#define USE_NBS_UDP_GetDataSize
	#define EXT_NBS_UDP_GetDataSize
	#define GET_NBS_UDP_GetDataSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_NBS_UDP_GetDataSize(p0,p1)  (CAA_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_NBS_UDP_GetDataSize  FALSE
	#define EXP_NBS_UDP_GetDataSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_NBS_UDP_GetDataSize
	#define EXT_NBS_UDP_GetDataSize
	#define GET_NBS_UDP_GetDataSize(fl)  CAL_CMGETAPI( "NBS_UDP_GetDataSize" ) 
	#define CAL_NBS_UDP_GetDataSize  NBS_UDP_GetDataSize
	#define CHK_NBS_UDP_GetDataSize  TRUE
	#define EXP_NBS_UDP_GetDataSize  CAL_CMEXPAPI( "NBS_UDP_GetDataSize" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAANETBASESERVICES_EXTERNAL)
	#define USE_NBS_UDP_GetDataSize
	#define EXT_NBS_UDP_GetDataSize
	#define GET_NBS_UDP_GetDataSize(fl)  CAL_CMGETAPI( "NBS_UDP_GetDataSize" ) 
	#define CAL_NBS_UDP_GetDataSize  NBS_UDP_GetDataSize
	#define CHK_NBS_UDP_GetDataSize  TRUE
	#define EXP_NBS_UDP_GetDataSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NBS_UDP_GetDataSize", (RTS_UINTPTR)NBS_UDP_GetDataSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAANetBaseServicesNBS_UDP_GetDataSize
	#define EXT_CmpCAANetBaseServicesNBS_UDP_GetDataSize
	#define GET_CmpCAANetBaseServicesNBS_UDP_GetDataSize  ERR_OK
	#define CAL_CmpCAANetBaseServicesNBS_UDP_GetDataSize pICmpCAANetBaseServices->INBS_UDP_GetDataSize
	#define CHK_CmpCAANetBaseServicesNBS_UDP_GetDataSize (pICmpCAANetBaseServices != NULL)
	#define EXP_CmpCAANetBaseServicesNBS_UDP_GetDataSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_NBS_UDP_GetDataSize
	#define EXT_NBS_UDP_GetDataSize
	#define GET_NBS_UDP_GetDataSize(fl)  CAL_CMGETAPI( "NBS_UDP_GetDataSize" ) 
	#define CAL_NBS_UDP_GetDataSize pICmpCAANetBaseServices->INBS_UDP_GetDataSize
	#define CHK_NBS_UDP_GetDataSize (pICmpCAANetBaseServices != NULL)
	#define EXP_NBS_UDP_GetDataSize  CAL_CMEXPAPI( "NBS_UDP_GetDataSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_NBS_UDP_GetDataSize  PFNBS_UDP_GETDATASIZE pfNBS_UDP_GetDataSize;
	#define EXT_NBS_UDP_GetDataSize  extern PFNBS_UDP_GETDATASIZE pfNBS_UDP_GetDataSize;
	#define GET_NBS_UDP_GetDataSize(fl)  s_pfCMGetAPI2( "NBS_UDP_GetDataSize", (RTS_VOID_FCTPTR *)&pfNBS_UDP_GetDataSize, (fl), 0, 0)
	#define CAL_NBS_UDP_GetDataSize  pfNBS_UDP_GetDataSize
	#define CHK_NBS_UDP_GetDataSize  (pfNBS_UDP_GetDataSize != NULL)
	#define EXP_NBS_UDP_GetDataSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"NBS_UDP_GetDataSize", (RTS_UINTPTR)NBS_UDP_GetDataSize, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFNBS_WORKERINIT INBS_WorkerInit;
 	PFNBS_WORKEREXIT INBS_WorkerExit;
 	PFNBS_UDP_GETDATASIZE INBS_UDP_GetDataSize;
 } ICmpCAANetBaseServices_C;

#ifdef CPLUSPLUS
class ICmpCAANetBaseServices : public IBase
{
	public:
		virtual CAA_ERROR CDECL INBS_WorkerInit(void) =0;
		virtual CAA_ERROR CDECL INBS_WorkerExit(void) =0;
		virtual CAA_SIZE CDECL INBS_UDP_GetDataSize(CAA_HANDLE hPeer, CAA_ERROR* peError) =0;
};
	#ifndef ITF_CmpCAANetBaseServices
		#define ITF_CmpCAANetBaseServices static ICmpCAANetBaseServices *pICmpCAANetBaseServices = NULL;
	#endif
	#define EXTITF_CmpCAANetBaseServices
#else	/*CPLUSPLUS*/
	typedef ICmpCAANetBaseServices_C		ICmpCAANetBaseServices;
	#ifndef ITF_CmpCAANetBaseServices
		#define ITF_CmpCAANetBaseServices
	#endif
	#define EXTITF_CmpCAANetBaseServices
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCAANETBASESERVICESITF_H_*/
