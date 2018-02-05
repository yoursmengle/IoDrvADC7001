 /**
 * <interfacename>CmpCAAAsyncMan</interfacename>
 * <description> 
 *	<p>CAA Technik Work Group: Asnyc Manager.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPCAAASYNCMANITF_H_
#define _CMPCAAASYNCMANITF_H_

#include "CmpStd.h"

 

 




/**
 * <description>
 *   The CAA Asycn Manager provides an asynchronous job handling.
 *   Please see the CAA documentation CAA_AsyncManager.pdf for any further
 *   information.
 * </description>
 */    

#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAAAsyncMan.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Interface functions of CAA Async Man*/
CAA_HANDLE CDECL ASM_JobOpenEx(CAA_UDINT udiId, CAA_PVOID pParams, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFASM_JOBOPENEX) (CAA_UDINT udiId, CAA_PVOID pParams, CAA_ERROR* peError);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_JOBOPENEX_NOTIMPLEMENTED)
	#define USE_ASM_JobOpenEx
	#define EXT_ASM_JobOpenEx
	#define GET_ASM_JobOpenEx(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ASM_JobOpenEx(p0,p1,p2)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_ASM_JobOpenEx  FALSE
	#define EXP_ASM_JobOpenEx  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ASM_JobOpenEx
	#define EXT_ASM_JobOpenEx
	#define GET_ASM_JobOpenEx(fl)  CAL_CMGETAPI( "ASM_JobOpenEx" ) 
	#define CAL_ASM_JobOpenEx  ASM_JobOpenEx
	#define CHK_ASM_JobOpenEx  TRUE
	#define EXP_ASM_JobOpenEx  CAL_CMEXPAPI( "ASM_JobOpenEx" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_ASM_JobOpenEx
	#define EXT_ASM_JobOpenEx
	#define GET_ASM_JobOpenEx(fl)  CAL_CMGETAPI( "ASM_JobOpenEx" ) 
	#define CAL_ASM_JobOpenEx  ASM_JobOpenEx
	#define CHK_ASM_JobOpenEx  TRUE
	#define EXP_ASM_JobOpenEx  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_JobOpenEx", (RTS_UINTPTR)ASM_JobOpenEx, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManASM_JobOpenEx
	#define EXT_CmpCAAAsyncManASM_JobOpenEx
	#define GET_CmpCAAAsyncManASM_JobOpenEx  ERR_OK
	#define CAL_CmpCAAAsyncManASM_JobOpenEx pICmpCAAAsyncMan->IASM_JobOpenEx
	#define CHK_CmpCAAAsyncManASM_JobOpenEx (pICmpCAAAsyncMan != NULL)
	#define EXP_CmpCAAAsyncManASM_JobOpenEx  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ASM_JobOpenEx
	#define EXT_ASM_JobOpenEx
	#define GET_ASM_JobOpenEx(fl)  CAL_CMGETAPI( "ASM_JobOpenEx" ) 
	#define CAL_ASM_JobOpenEx pICmpCAAAsyncMan->IASM_JobOpenEx
	#define CHK_ASM_JobOpenEx (pICmpCAAAsyncMan != NULL)
	#define EXP_ASM_JobOpenEx  CAL_CMEXPAPI( "ASM_JobOpenEx" ) 
#else /* DYNAMIC_LINK */
	#define USE_ASM_JobOpenEx  PFASM_JOBOPENEX pfASM_JobOpenEx;
	#define EXT_ASM_JobOpenEx  extern PFASM_JOBOPENEX pfASM_JobOpenEx;
	#define GET_ASM_JobOpenEx(fl)  s_pfCMGetAPI2( "ASM_JobOpenEx", (RTS_VOID_FCTPTR *)&pfASM_JobOpenEx, (fl), 0, 0)
	#define CAL_ASM_JobOpenEx  pfASM_JobOpenEx
	#define CHK_ASM_JobOpenEx  (pfASM_JobOpenEx != NULL)
	#define EXP_ASM_JobOpenEx  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_JobOpenEx", (RTS_UINTPTR)ASM_JobOpenEx, 0, 0) 
#endif



CAA_HANDLE CDECL ASM_JobOpen(RTS_IEC_UDINT udiId, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFASM_JOBOPEN) (RTS_IEC_UDINT udiId, CAA_ERROR* peError);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_JOBOPEN_NOTIMPLEMENTED)
	#define USE_ASM_JobOpen
	#define EXT_ASM_JobOpen
	#define GET_ASM_JobOpen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ASM_JobOpen(p0,p1)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_ASM_JobOpen  FALSE
	#define EXP_ASM_JobOpen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ASM_JobOpen
	#define EXT_ASM_JobOpen
	#define GET_ASM_JobOpen(fl)  CAL_CMGETAPI( "ASM_JobOpen" ) 
	#define CAL_ASM_JobOpen  ASM_JobOpen
	#define CHK_ASM_JobOpen  TRUE
	#define EXP_ASM_JobOpen  CAL_CMEXPAPI( "ASM_JobOpen" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_ASM_JobOpen
	#define EXT_ASM_JobOpen
	#define GET_ASM_JobOpen(fl)  CAL_CMGETAPI( "ASM_JobOpen" ) 
	#define CAL_ASM_JobOpen  ASM_JobOpen
	#define CHK_ASM_JobOpen  TRUE
	#define EXP_ASM_JobOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_JobOpen", (RTS_UINTPTR)ASM_JobOpen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManASM_JobOpen
	#define EXT_CmpCAAAsyncManASM_JobOpen
	#define GET_CmpCAAAsyncManASM_JobOpen  ERR_OK
	#define CAL_CmpCAAAsyncManASM_JobOpen pICmpCAAAsyncMan->IASM_JobOpen
	#define CHK_CmpCAAAsyncManASM_JobOpen (pICmpCAAAsyncMan != NULL)
	#define EXP_CmpCAAAsyncManASM_JobOpen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ASM_JobOpen
	#define EXT_ASM_JobOpen
	#define GET_ASM_JobOpen(fl)  CAL_CMGETAPI( "ASM_JobOpen" ) 
	#define CAL_ASM_JobOpen pICmpCAAAsyncMan->IASM_JobOpen
	#define CHK_ASM_JobOpen (pICmpCAAAsyncMan != NULL)
	#define EXP_ASM_JobOpen  CAL_CMEXPAPI( "ASM_JobOpen" ) 
#else /* DYNAMIC_LINK */
	#define USE_ASM_JobOpen  PFASM_JOBOPEN pfASM_JobOpen;
	#define EXT_ASM_JobOpen  extern PFASM_JOBOPEN pfASM_JobOpen;
	#define GET_ASM_JobOpen(fl)  s_pfCMGetAPI2( "ASM_JobOpen", (RTS_VOID_FCTPTR *)&pfASM_JobOpen, (fl), 0, 0)
	#define CAL_ASM_JobOpen  pfASM_JobOpen
	#define CHK_ASM_JobOpen  (pfASM_JobOpen != NULL)
	#define EXP_ASM_JobOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_JobOpen", (RTS_UINTPTR)ASM_JobOpen, 0, 0) 
#endif



CAA_ERROR CDECL ASM_JobClose(CAA_HANDLE hJob);
typedef CAA_ERROR (CDECL * PFASM_JOBCLOSE) (CAA_HANDLE hJob);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_JOBCLOSE_NOTIMPLEMENTED)
	#define USE_ASM_JobClose
	#define EXT_ASM_JobClose
	#define GET_ASM_JobClose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ASM_JobClose(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_ASM_JobClose  FALSE
	#define EXP_ASM_JobClose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ASM_JobClose
	#define EXT_ASM_JobClose
	#define GET_ASM_JobClose(fl)  CAL_CMGETAPI( "ASM_JobClose" ) 
	#define CAL_ASM_JobClose  ASM_JobClose
	#define CHK_ASM_JobClose  TRUE
	#define EXP_ASM_JobClose  CAL_CMEXPAPI( "ASM_JobClose" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_ASM_JobClose
	#define EXT_ASM_JobClose
	#define GET_ASM_JobClose(fl)  CAL_CMGETAPI( "ASM_JobClose" ) 
	#define CAL_ASM_JobClose  ASM_JobClose
	#define CHK_ASM_JobClose  TRUE
	#define EXP_ASM_JobClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_JobClose", (RTS_UINTPTR)ASM_JobClose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManASM_JobClose
	#define EXT_CmpCAAAsyncManASM_JobClose
	#define GET_CmpCAAAsyncManASM_JobClose  ERR_OK
	#define CAL_CmpCAAAsyncManASM_JobClose pICmpCAAAsyncMan->IASM_JobClose
	#define CHK_CmpCAAAsyncManASM_JobClose (pICmpCAAAsyncMan != NULL)
	#define EXP_CmpCAAAsyncManASM_JobClose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ASM_JobClose
	#define EXT_ASM_JobClose
	#define GET_ASM_JobClose(fl)  CAL_CMGETAPI( "ASM_JobClose" ) 
	#define CAL_ASM_JobClose pICmpCAAAsyncMan->IASM_JobClose
	#define CHK_ASM_JobClose (pICmpCAAAsyncMan != NULL)
	#define EXP_ASM_JobClose  CAL_CMEXPAPI( "ASM_JobClose" ) 
#else /* DYNAMIC_LINK */
	#define USE_ASM_JobClose  PFASM_JOBCLOSE pfASM_JobClose;
	#define EXT_ASM_JobClose  extern PFASM_JOBCLOSE pfASM_JobClose;
	#define GET_ASM_JobClose(fl)  s_pfCMGetAPI2( "ASM_JobClose", (RTS_VOID_FCTPTR *)&pfASM_JobClose, (fl), 0, 0)
	#define CAL_ASM_JobClose  pfASM_JobClose
	#define CHK_ASM_JobClose  (pfASM_JobClose != NULL)
	#define EXP_ASM_JobClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_JobClose", (RTS_UINTPTR)ASM_JobClose, 0, 0) 
#endif



CAA_ERROR CDECL ASM_JobExecute(CAA_HANDLE hJob);
typedef CAA_ERROR (CDECL * PFASM_JOBEXECUTE) (CAA_HANDLE hJob);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_JOBEXECUTE_NOTIMPLEMENTED)
	#define USE_ASM_JobExecute
	#define EXT_ASM_JobExecute
	#define GET_ASM_JobExecute(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ASM_JobExecute(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_ASM_JobExecute  FALSE
	#define EXP_ASM_JobExecute  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ASM_JobExecute
	#define EXT_ASM_JobExecute
	#define GET_ASM_JobExecute(fl)  CAL_CMGETAPI( "ASM_JobExecute" ) 
	#define CAL_ASM_JobExecute  ASM_JobExecute
	#define CHK_ASM_JobExecute  TRUE
	#define EXP_ASM_JobExecute  CAL_CMEXPAPI( "ASM_JobExecute" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_ASM_JobExecute
	#define EXT_ASM_JobExecute
	#define GET_ASM_JobExecute(fl)  CAL_CMGETAPI( "ASM_JobExecute" ) 
	#define CAL_ASM_JobExecute  ASM_JobExecute
	#define CHK_ASM_JobExecute  TRUE
	#define EXP_ASM_JobExecute  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_JobExecute", (RTS_UINTPTR)ASM_JobExecute, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManASM_JobExecute
	#define EXT_CmpCAAAsyncManASM_JobExecute
	#define GET_CmpCAAAsyncManASM_JobExecute  ERR_OK
	#define CAL_CmpCAAAsyncManASM_JobExecute pICmpCAAAsyncMan->IASM_JobExecute
	#define CHK_CmpCAAAsyncManASM_JobExecute (pICmpCAAAsyncMan != NULL)
	#define EXP_CmpCAAAsyncManASM_JobExecute  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ASM_JobExecute
	#define EXT_ASM_JobExecute
	#define GET_ASM_JobExecute(fl)  CAL_CMGETAPI( "ASM_JobExecute" ) 
	#define CAL_ASM_JobExecute pICmpCAAAsyncMan->IASM_JobExecute
	#define CHK_ASM_JobExecute (pICmpCAAAsyncMan != NULL)
	#define EXP_ASM_JobExecute  CAL_CMEXPAPI( "ASM_JobExecute" ) 
#else /* DYNAMIC_LINK */
	#define USE_ASM_JobExecute  PFASM_JOBEXECUTE pfASM_JobExecute;
	#define EXT_ASM_JobExecute  extern PFASM_JOBEXECUTE pfASM_JobExecute;
	#define GET_ASM_JobExecute(fl)  s_pfCMGetAPI2( "ASM_JobExecute", (RTS_VOID_FCTPTR *)&pfASM_JobExecute, (fl), 0, 0)
	#define CAL_ASM_JobExecute  pfASM_JobExecute
	#define CHK_ASM_JobExecute  (pfASM_JobExecute != NULL)
	#define EXP_ASM_JobExecute  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_JobExecute", (RTS_UINTPTR)ASM_JobExecute, 0, 0) 
#endif



CAA_ERROR CDECL ASM_JobReset(CAA_HANDLE hJob);
typedef CAA_ERROR (CDECL * PFASM_JOBRESET) (CAA_HANDLE hJob);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_JOBRESET_NOTIMPLEMENTED)
	#define USE_ASM_JobReset
	#define EXT_ASM_JobReset
	#define GET_ASM_JobReset(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ASM_JobReset(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_ASM_JobReset  FALSE
	#define EXP_ASM_JobReset  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ASM_JobReset
	#define EXT_ASM_JobReset
	#define GET_ASM_JobReset(fl)  CAL_CMGETAPI( "ASM_JobReset" ) 
	#define CAL_ASM_JobReset  ASM_JobReset
	#define CHK_ASM_JobReset  TRUE
	#define EXP_ASM_JobReset  CAL_CMEXPAPI( "ASM_JobReset" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_ASM_JobReset
	#define EXT_ASM_JobReset
	#define GET_ASM_JobReset(fl)  CAL_CMGETAPI( "ASM_JobReset" ) 
	#define CAL_ASM_JobReset  ASM_JobReset
	#define CHK_ASM_JobReset  TRUE
	#define EXP_ASM_JobReset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_JobReset", (RTS_UINTPTR)ASM_JobReset, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManASM_JobReset
	#define EXT_CmpCAAAsyncManASM_JobReset
	#define GET_CmpCAAAsyncManASM_JobReset  ERR_OK
	#define CAL_CmpCAAAsyncManASM_JobReset pICmpCAAAsyncMan->IASM_JobReset
	#define CHK_CmpCAAAsyncManASM_JobReset (pICmpCAAAsyncMan != NULL)
	#define EXP_CmpCAAAsyncManASM_JobReset  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ASM_JobReset
	#define EXT_ASM_JobReset
	#define GET_ASM_JobReset(fl)  CAL_CMGETAPI( "ASM_JobReset" ) 
	#define CAL_ASM_JobReset pICmpCAAAsyncMan->IASM_JobReset
	#define CHK_ASM_JobReset (pICmpCAAAsyncMan != NULL)
	#define EXP_ASM_JobReset  CAL_CMEXPAPI( "ASM_JobReset" ) 
#else /* DYNAMIC_LINK */
	#define USE_ASM_JobReset  PFASM_JOBRESET pfASM_JobReset;
	#define EXT_ASM_JobReset  extern PFASM_JOBRESET pfASM_JobReset;
	#define GET_ASM_JobReset(fl)  s_pfCMGetAPI2( "ASM_JobReset", (RTS_VOID_FCTPTR *)&pfASM_JobReset, (fl), 0, 0)
	#define CAL_ASM_JobReset  pfASM_JobReset
	#define CHK_ASM_JobReset  (pfASM_JobReset != NULL)
	#define EXP_ASM_JobReset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_JobReset", (RTS_UINTPTR)ASM_JobReset, 0, 0) 
#endif



CAA_ERROR CDECL ASM_JobAbort(CAA_HANDLE hJob);
typedef CAA_ERROR (CDECL * PFASM_JOBABORT) (CAA_HANDLE hJob);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_JOBABORT_NOTIMPLEMENTED)
	#define USE_ASM_JobAbort
	#define EXT_ASM_JobAbort
	#define GET_ASM_JobAbort(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ASM_JobAbort(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_ASM_JobAbort  FALSE
	#define EXP_ASM_JobAbort  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ASM_JobAbort
	#define EXT_ASM_JobAbort
	#define GET_ASM_JobAbort(fl)  CAL_CMGETAPI( "ASM_JobAbort" ) 
	#define CAL_ASM_JobAbort  ASM_JobAbort
	#define CHK_ASM_JobAbort  TRUE
	#define EXP_ASM_JobAbort  CAL_CMEXPAPI( "ASM_JobAbort" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_ASM_JobAbort
	#define EXT_ASM_JobAbort
	#define GET_ASM_JobAbort(fl)  CAL_CMGETAPI( "ASM_JobAbort" ) 
	#define CAL_ASM_JobAbort  ASM_JobAbort
	#define CHK_ASM_JobAbort  TRUE
	#define EXP_ASM_JobAbort  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_JobAbort", (RTS_UINTPTR)ASM_JobAbort, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManASM_JobAbort
	#define EXT_CmpCAAAsyncManASM_JobAbort
	#define GET_CmpCAAAsyncManASM_JobAbort  ERR_OK
	#define CAL_CmpCAAAsyncManASM_JobAbort pICmpCAAAsyncMan->IASM_JobAbort
	#define CHK_CmpCAAAsyncManASM_JobAbort (pICmpCAAAsyncMan != NULL)
	#define EXP_CmpCAAAsyncManASM_JobAbort  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ASM_JobAbort
	#define EXT_ASM_JobAbort
	#define GET_ASM_JobAbort(fl)  CAL_CMGETAPI( "ASM_JobAbort" ) 
	#define CAL_ASM_JobAbort pICmpCAAAsyncMan->IASM_JobAbort
	#define CHK_ASM_JobAbort (pICmpCAAAsyncMan != NULL)
	#define EXP_ASM_JobAbort  CAL_CMEXPAPI( "ASM_JobAbort" ) 
#else /* DYNAMIC_LINK */
	#define USE_ASM_JobAbort  PFASM_JOBABORT pfASM_JobAbort;
	#define EXT_ASM_JobAbort  extern PFASM_JOBABORT pfASM_JobAbort;
	#define GET_ASM_JobAbort(fl)  s_pfCMGetAPI2( "ASM_JobAbort", (RTS_VOID_FCTPTR *)&pfASM_JobAbort, (fl), 0, 0)
	#define CAL_ASM_JobAbort  pfASM_JobAbort
	#define CHK_ASM_JobAbort  (pfASM_JobAbort != NULL)
	#define EXP_ASM_JobAbort  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_JobAbort", (RTS_UINTPTR)ASM_JobAbort, 0, 0) 
#endif



CAA_PVOID CDECL ASM_JobGetParams(CAA_HANDLE hJob, CAA_ERROR* peError);
typedef CAA_PVOID (CDECL * PFASM_JOBGETPARAMS) (CAA_HANDLE hJob, CAA_ERROR* peError);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_JOBGETPARAMS_NOTIMPLEMENTED)
	#define USE_ASM_JobGetParams
	#define EXT_ASM_JobGetParams
	#define GET_ASM_JobGetParams(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ASM_JobGetParams(p0,p1)  (CAA_PVOID)ERR_NOTIMPLEMENTED
	#define CHK_ASM_JobGetParams  FALSE
	#define EXP_ASM_JobGetParams  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ASM_JobGetParams
	#define EXT_ASM_JobGetParams
	#define GET_ASM_JobGetParams(fl)  CAL_CMGETAPI( "ASM_JobGetParams" ) 
	#define CAL_ASM_JobGetParams  ASM_JobGetParams
	#define CHK_ASM_JobGetParams  TRUE
	#define EXP_ASM_JobGetParams  CAL_CMEXPAPI( "ASM_JobGetParams" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_ASM_JobGetParams
	#define EXT_ASM_JobGetParams
	#define GET_ASM_JobGetParams(fl)  CAL_CMGETAPI( "ASM_JobGetParams" ) 
	#define CAL_ASM_JobGetParams  ASM_JobGetParams
	#define CHK_ASM_JobGetParams  TRUE
	#define EXP_ASM_JobGetParams  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_JobGetParams", (RTS_UINTPTR)ASM_JobGetParams, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManASM_JobGetParams
	#define EXT_CmpCAAAsyncManASM_JobGetParams
	#define GET_CmpCAAAsyncManASM_JobGetParams  ERR_OK
	#define CAL_CmpCAAAsyncManASM_JobGetParams pICmpCAAAsyncMan->IASM_JobGetParams
	#define CHK_CmpCAAAsyncManASM_JobGetParams (pICmpCAAAsyncMan != NULL)
	#define EXP_CmpCAAAsyncManASM_JobGetParams  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ASM_JobGetParams
	#define EXT_ASM_JobGetParams
	#define GET_ASM_JobGetParams(fl)  CAL_CMGETAPI( "ASM_JobGetParams" ) 
	#define CAL_ASM_JobGetParams pICmpCAAAsyncMan->IASM_JobGetParams
	#define CHK_ASM_JobGetParams (pICmpCAAAsyncMan != NULL)
	#define EXP_ASM_JobGetParams  CAL_CMEXPAPI( "ASM_JobGetParams" ) 
#else /* DYNAMIC_LINK */
	#define USE_ASM_JobGetParams  PFASM_JOBGETPARAMS pfASM_JobGetParams;
	#define EXT_ASM_JobGetParams  extern PFASM_JOBGETPARAMS pfASM_JobGetParams;
	#define GET_ASM_JobGetParams(fl)  s_pfCMGetAPI2( "ASM_JobGetParams", (RTS_VOID_FCTPTR *)&pfASM_JobGetParams, (fl), 0, 0)
	#define CAL_ASM_JobGetParams  pfASM_JobGetParams
	#define CHK_ASM_JobGetParams  (pfASM_JobGetParams != NULL)
	#define EXP_ASM_JobGetParams  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_JobGetParams", (RTS_UINTPTR)ASM_JobGetParams, 0, 0) 
#endif



CAA_ERROR CDECL ASM_JobGetState(CAA_HANDLE hJob, ASM_STATE* pstateJob);
typedef CAA_ERROR (CDECL * PFASM_JOBGETSTATE) (CAA_HANDLE hJob, ASM_STATE* pstateJob);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_JOBGETSTATE_NOTIMPLEMENTED)
	#define USE_ASM_JobGetState
	#define EXT_ASM_JobGetState
	#define GET_ASM_JobGetState(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ASM_JobGetState(p0,p1)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_ASM_JobGetState  FALSE
	#define EXP_ASM_JobGetState  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ASM_JobGetState
	#define EXT_ASM_JobGetState
	#define GET_ASM_JobGetState(fl)  CAL_CMGETAPI( "ASM_JobGetState" ) 
	#define CAL_ASM_JobGetState  ASM_JobGetState
	#define CHK_ASM_JobGetState  TRUE
	#define EXP_ASM_JobGetState  CAL_CMEXPAPI( "ASM_JobGetState" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_ASM_JobGetState
	#define EXT_ASM_JobGetState
	#define GET_ASM_JobGetState(fl)  CAL_CMGETAPI( "ASM_JobGetState" ) 
	#define CAL_ASM_JobGetState  ASM_JobGetState
	#define CHK_ASM_JobGetState  TRUE
	#define EXP_ASM_JobGetState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_JobGetState", (RTS_UINTPTR)ASM_JobGetState, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManASM_JobGetState
	#define EXT_CmpCAAAsyncManASM_JobGetState
	#define GET_CmpCAAAsyncManASM_JobGetState  ERR_OK
	#define CAL_CmpCAAAsyncManASM_JobGetState pICmpCAAAsyncMan->IASM_JobGetState
	#define CHK_CmpCAAAsyncManASM_JobGetState (pICmpCAAAsyncMan != NULL)
	#define EXP_CmpCAAAsyncManASM_JobGetState  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ASM_JobGetState
	#define EXT_ASM_JobGetState
	#define GET_ASM_JobGetState(fl)  CAL_CMGETAPI( "ASM_JobGetState" ) 
	#define CAL_ASM_JobGetState pICmpCAAAsyncMan->IASM_JobGetState
	#define CHK_ASM_JobGetState (pICmpCAAAsyncMan != NULL)
	#define EXP_ASM_JobGetState  CAL_CMEXPAPI( "ASM_JobGetState" ) 
#else /* DYNAMIC_LINK */
	#define USE_ASM_JobGetState  PFASM_JOBGETSTATE pfASM_JobGetState;
	#define EXT_ASM_JobGetState  extern PFASM_JOBGETSTATE pfASM_JobGetState;
	#define GET_ASM_JobGetState(fl)  s_pfCMGetAPI2( "ASM_JobGetState", (RTS_VOID_FCTPTR *)&pfASM_JobGetState, (fl), 0, 0)
	#define CAL_ASM_JobGetState  pfASM_JobGetState
	#define CHK_ASM_JobGetState  (pfASM_JobGetState != NULL)
	#define EXP_ASM_JobGetState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_JobGetState", (RTS_UINTPTR)ASM_JobGetState, 0, 0) 
#endif



RTS_IEC_UDINT CDECL ASM_JobGetId(CAA_HANDLE hJob, CAA_ERROR* peError);
typedef RTS_IEC_UDINT (CDECL * PFASM_JOBGETID) (CAA_HANDLE hJob, CAA_ERROR* peError);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_JOBGETID_NOTIMPLEMENTED)
	#define USE_ASM_JobGetId
	#define EXT_ASM_JobGetId
	#define GET_ASM_JobGetId(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ASM_JobGetId(p0,p1)  (RTS_IEC_UDINT)ERR_NOTIMPLEMENTED
	#define CHK_ASM_JobGetId  FALSE
	#define EXP_ASM_JobGetId  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ASM_JobGetId
	#define EXT_ASM_JobGetId
	#define GET_ASM_JobGetId(fl)  CAL_CMGETAPI( "ASM_JobGetId" ) 
	#define CAL_ASM_JobGetId  ASM_JobGetId
	#define CHK_ASM_JobGetId  TRUE
	#define EXP_ASM_JobGetId  CAL_CMEXPAPI( "ASM_JobGetId" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_ASM_JobGetId
	#define EXT_ASM_JobGetId
	#define GET_ASM_JobGetId(fl)  CAL_CMGETAPI( "ASM_JobGetId" ) 
	#define CAL_ASM_JobGetId  ASM_JobGetId
	#define CHK_ASM_JobGetId  TRUE
	#define EXP_ASM_JobGetId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_JobGetId", (RTS_UINTPTR)ASM_JobGetId, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManASM_JobGetId
	#define EXT_CmpCAAAsyncManASM_JobGetId
	#define GET_CmpCAAAsyncManASM_JobGetId  ERR_OK
	#define CAL_CmpCAAAsyncManASM_JobGetId pICmpCAAAsyncMan->IASM_JobGetId
	#define CHK_CmpCAAAsyncManASM_JobGetId (pICmpCAAAsyncMan != NULL)
	#define EXP_CmpCAAAsyncManASM_JobGetId  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ASM_JobGetId
	#define EXT_ASM_JobGetId
	#define GET_ASM_JobGetId(fl)  CAL_CMGETAPI( "ASM_JobGetId" ) 
	#define CAL_ASM_JobGetId pICmpCAAAsyncMan->IASM_JobGetId
	#define CHK_ASM_JobGetId (pICmpCAAAsyncMan != NULL)
	#define EXP_ASM_JobGetId  CAL_CMEXPAPI( "ASM_JobGetId" ) 
#else /* DYNAMIC_LINK */
	#define USE_ASM_JobGetId  PFASM_JOBGETID pfASM_JobGetId;
	#define EXT_ASM_JobGetId  extern PFASM_JOBGETID pfASM_JobGetId;
	#define GET_ASM_JobGetId(fl)  s_pfCMGetAPI2( "ASM_JobGetId", (RTS_VOID_FCTPTR *)&pfASM_JobGetId, (fl), 0, 0)
	#define CAL_ASM_JobGetId  pfASM_JobGetId
	#define CHK_ASM_JobGetId  (pfASM_JobGetId != NULL)
	#define EXP_ASM_JobGetId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_JobGetId", (RTS_UINTPTR)ASM_JobGetId, 0, 0) 
#endif



CAA_ERROR CDECL ASM_WorkerRegister(RTS_IEC_UDINT udiId, ASM_IWORKER* pwiItf);
typedef CAA_ERROR (CDECL * PFASM_WORKERREGISTER) (RTS_IEC_UDINT udiId, ASM_IWORKER* pwiItf);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_WORKERREGISTER_NOTIMPLEMENTED)
	#define USE_ASM_WorkerRegister
	#define EXT_ASM_WorkerRegister
	#define GET_ASM_WorkerRegister(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ASM_WorkerRegister(p0,p1)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_ASM_WorkerRegister  FALSE
	#define EXP_ASM_WorkerRegister  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ASM_WorkerRegister
	#define EXT_ASM_WorkerRegister
	#define GET_ASM_WorkerRegister(fl)  CAL_CMGETAPI( "ASM_WorkerRegister" ) 
	#define CAL_ASM_WorkerRegister  ASM_WorkerRegister
	#define CHK_ASM_WorkerRegister  TRUE
	#define EXP_ASM_WorkerRegister  CAL_CMEXPAPI( "ASM_WorkerRegister" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_ASM_WorkerRegister
	#define EXT_ASM_WorkerRegister
	#define GET_ASM_WorkerRegister(fl)  CAL_CMGETAPI( "ASM_WorkerRegister" ) 
	#define CAL_ASM_WorkerRegister  ASM_WorkerRegister
	#define CHK_ASM_WorkerRegister  TRUE
	#define EXP_ASM_WorkerRegister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_WorkerRegister", (RTS_UINTPTR)ASM_WorkerRegister, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManASM_WorkerRegister
	#define EXT_CmpCAAAsyncManASM_WorkerRegister
	#define GET_CmpCAAAsyncManASM_WorkerRegister  ERR_OK
	#define CAL_CmpCAAAsyncManASM_WorkerRegister pICmpCAAAsyncMan->IASM_WorkerRegister
	#define CHK_CmpCAAAsyncManASM_WorkerRegister (pICmpCAAAsyncMan != NULL)
	#define EXP_CmpCAAAsyncManASM_WorkerRegister  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ASM_WorkerRegister
	#define EXT_ASM_WorkerRegister
	#define GET_ASM_WorkerRegister(fl)  CAL_CMGETAPI( "ASM_WorkerRegister" ) 
	#define CAL_ASM_WorkerRegister pICmpCAAAsyncMan->IASM_WorkerRegister
	#define CHK_ASM_WorkerRegister (pICmpCAAAsyncMan != NULL)
	#define EXP_ASM_WorkerRegister  CAL_CMEXPAPI( "ASM_WorkerRegister" ) 
#else /* DYNAMIC_LINK */
	#define USE_ASM_WorkerRegister  PFASM_WORKERREGISTER pfASM_WorkerRegister;
	#define EXT_ASM_WorkerRegister  extern PFASM_WORKERREGISTER pfASM_WorkerRegister;
	#define GET_ASM_WorkerRegister(fl)  s_pfCMGetAPI2( "ASM_WorkerRegister", (RTS_VOID_FCTPTR *)&pfASM_WorkerRegister, (fl), 0, 0)
	#define CAL_ASM_WorkerRegister  pfASM_WorkerRegister
	#define CHK_ASM_WorkerRegister  (pfASM_WorkerRegister != NULL)
	#define EXP_ASM_WorkerRegister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_WorkerRegister", (RTS_UINTPTR)ASM_WorkerRegister, 0, 0) 
#endif



CAA_ERROR CDECL ASM_WorkerRegister2(RTS_IEC_UDINT udiId, ASM_IWORKER2* pwiItf2);
typedef CAA_ERROR (CDECL * PFASM_WORKERREGISTER2) (RTS_IEC_UDINT udiId, ASM_IWORKER2* pwiItf2);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_WORKERREGISTER2_NOTIMPLEMENTED)
	#define USE_ASM_WorkerRegister2
	#define EXT_ASM_WorkerRegister2
	#define GET_ASM_WorkerRegister2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ASM_WorkerRegister2(p0,p1)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_ASM_WorkerRegister2  FALSE
	#define EXP_ASM_WorkerRegister2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ASM_WorkerRegister2
	#define EXT_ASM_WorkerRegister2
	#define GET_ASM_WorkerRegister2(fl)  CAL_CMGETAPI( "ASM_WorkerRegister2" ) 
	#define CAL_ASM_WorkerRegister2  ASM_WorkerRegister2
	#define CHK_ASM_WorkerRegister2  TRUE
	#define EXP_ASM_WorkerRegister2  CAL_CMEXPAPI( "ASM_WorkerRegister2" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_ASM_WorkerRegister2
	#define EXT_ASM_WorkerRegister2
	#define GET_ASM_WorkerRegister2(fl)  CAL_CMGETAPI( "ASM_WorkerRegister2" ) 
	#define CAL_ASM_WorkerRegister2  ASM_WorkerRegister2
	#define CHK_ASM_WorkerRegister2  TRUE
	#define EXP_ASM_WorkerRegister2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_WorkerRegister2", (RTS_UINTPTR)ASM_WorkerRegister2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManASM_WorkerRegister2
	#define EXT_CmpCAAAsyncManASM_WorkerRegister2
	#define GET_CmpCAAAsyncManASM_WorkerRegister2  ERR_OK
	#define CAL_CmpCAAAsyncManASM_WorkerRegister2 pICmpCAAAsyncMan->IASM_WorkerRegister2
	#define CHK_CmpCAAAsyncManASM_WorkerRegister2 (pICmpCAAAsyncMan != NULL)
	#define EXP_CmpCAAAsyncManASM_WorkerRegister2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ASM_WorkerRegister2
	#define EXT_ASM_WorkerRegister2
	#define GET_ASM_WorkerRegister2(fl)  CAL_CMGETAPI( "ASM_WorkerRegister2" ) 
	#define CAL_ASM_WorkerRegister2 pICmpCAAAsyncMan->IASM_WorkerRegister2
	#define CHK_ASM_WorkerRegister2 (pICmpCAAAsyncMan != NULL)
	#define EXP_ASM_WorkerRegister2  CAL_CMEXPAPI( "ASM_WorkerRegister2" ) 
#else /* DYNAMIC_LINK */
	#define USE_ASM_WorkerRegister2  PFASM_WORKERREGISTER2 pfASM_WorkerRegister2;
	#define EXT_ASM_WorkerRegister2  extern PFASM_WORKERREGISTER2 pfASM_WorkerRegister2;
	#define GET_ASM_WorkerRegister2(fl)  s_pfCMGetAPI2( "ASM_WorkerRegister2", (RTS_VOID_FCTPTR *)&pfASM_WorkerRegister2, (fl), 0, 0)
	#define CAL_ASM_WorkerRegister2  pfASM_WorkerRegister2
	#define CHK_ASM_WorkerRegister2  (pfASM_WorkerRegister2 != NULL)
	#define EXP_ASM_WorkerRegister2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_WorkerRegister2", (RTS_UINTPTR)ASM_WorkerRegister2, 0, 0) 
#endif



CAA_ERROR CDECL ASM_WorkerUnregister(RTS_IEC_UDINT udiId);
typedef CAA_ERROR (CDECL * PFASM_WORKERUNREGISTER) (RTS_IEC_UDINT udiId);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_WORKERUNREGISTER_NOTIMPLEMENTED)
	#define USE_ASM_WorkerUnregister
	#define EXT_ASM_WorkerUnregister
	#define GET_ASM_WorkerUnregister(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ASM_WorkerUnregister(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_ASM_WorkerUnregister  FALSE
	#define EXP_ASM_WorkerUnregister  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ASM_WorkerUnregister
	#define EXT_ASM_WorkerUnregister
	#define GET_ASM_WorkerUnregister(fl)  CAL_CMGETAPI( "ASM_WorkerUnregister" ) 
	#define CAL_ASM_WorkerUnregister  ASM_WorkerUnregister
	#define CHK_ASM_WorkerUnregister  TRUE
	#define EXP_ASM_WorkerUnregister  CAL_CMEXPAPI( "ASM_WorkerUnregister" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_ASM_WorkerUnregister
	#define EXT_ASM_WorkerUnregister
	#define GET_ASM_WorkerUnregister(fl)  CAL_CMGETAPI( "ASM_WorkerUnregister" ) 
	#define CAL_ASM_WorkerUnregister  ASM_WorkerUnregister
	#define CHK_ASM_WorkerUnregister  TRUE
	#define EXP_ASM_WorkerUnregister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_WorkerUnregister", (RTS_UINTPTR)ASM_WorkerUnregister, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManASM_WorkerUnregister
	#define EXT_CmpCAAAsyncManASM_WorkerUnregister
	#define GET_CmpCAAAsyncManASM_WorkerUnregister  ERR_OK
	#define CAL_CmpCAAAsyncManASM_WorkerUnregister pICmpCAAAsyncMan->IASM_WorkerUnregister
	#define CHK_CmpCAAAsyncManASM_WorkerUnregister (pICmpCAAAsyncMan != NULL)
	#define EXP_CmpCAAAsyncManASM_WorkerUnregister  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ASM_WorkerUnregister
	#define EXT_ASM_WorkerUnregister
	#define GET_ASM_WorkerUnregister(fl)  CAL_CMGETAPI( "ASM_WorkerUnregister" ) 
	#define CAL_ASM_WorkerUnregister pICmpCAAAsyncMan->IASM_WorkerUnregister
	#define CHK_ASM_WorkerUnregister (pICmpCAAAsyncMan != NULL)
	#define EXP_ASM_WorkerUnregister  CAL_CMEXPAPI( "ASM_WorkerUnregister" ) 
#else /* DYNAMIC_LINK */
	#define USE_ASM_WorkerUnregister  PFASM_WORKERUNREGISTER pfASM_WorkerUnregister;
	#define EXT_ASM_WorkerUnregister  extern PFASM_WORKERUNREGISTER pfASM_WorkerUnregister;
	#define GET_ASM_WorkerUnregister(fl)  s_pfCMGetAPI2( "ASM_WorkerUnregister", (RTS_VOID_FCTPTR *)&pfASM_WorkerUnregister, (fl), 0, 0)
	#define CAL_ASM_WorkerUnregister  pfASM_WorkerUnregister
	#define CHK_ASM_WorkerUnregister  (pfASM_WorkerUnregister != NULL)
	#define EXP_ASM_WorkerUnregister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_WorkerUnregister", (RTS_UINTPTR)ASM_WorkerUnregister, 0, 0) 
#endif



CAA_ERROR CDECL ASM_JobSetState(CAA_HANDLE hJob, ASM_STATE stateJob);
typedef CAA_ERROR (CDECL * PFASM_JOBSETSTATE) (CAA_HANDLE hJob, ASM_STATE stateJob);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_JOBSETSTATE_NOTIMPLEMENTED)
	#define USE_ASM_JobSetState
	#define EXT_ASM_JobSetState
	#define GET_ASM_JobSetState(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ASM_JobSetState(p0,p1)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_ASM_JobSetState  FALSE
	#define EXP_ASM_JobSetState  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ASM_JobSetState
	#define EXT_ASM_JobSetState
	#define GET_ASM_JobSetState(fl)  CAL_CMGETAPI( "ASM_JobSetState" ) 
	#define CAL_ASM_JobSetState  ASM_JobSetState
	#define CHK_ASM_JobSetState  TRUE
	#define EXP_ASM_JobSetState  CAL_CMEXPAPI( "ASM_JobSetState" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_ASM_JobSetState
	#define EXT_ASM_JobSetState
	#define GET_ASM_JobSetState(fl)  CAL_CMGETAPI( "ASM_JobSetState" ) 
	#define CAL_ASM_JobSetState  ASM_JobSetState
	#define CHK_ASM_JobSetState  TRUE
	#define EXP_ASM_JobSetState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_JobSetState", (RTS_UINTPTR)ASM_JobSetState, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManASM_JobSetState
	#define EXT_CmpCAAAsyncManASM_JobSetState
	#define GET_CmpCAAAsyncManASM_JobSetState  ERR_OK
	#define CAL_CmpCAAAsyncManASM_JobSetState pICmpCAAAsyncMan->IASM_JobSetState
	#define CHK_CmpCAAAsyncManASM_JobSetState (pICmpCAAAsyncMan != NULL)
	#define EXP_CmpCAAAsyncManASM_JobSetState  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ASM_JobSetState
	#define EXT_ASM_JobSetState
	#define GET_ASM_JobSetState(fl)  CAL_CMGETAPI( "ASM_JobSetState" ) 
	#define CAL_ASM_JobSetState pICmpCAAAsyncMan->IASM_JobSetState
	#define CHK_ASM_JobSetState (pICmpCAAAsyncMan != NULL)
	#define EXP_ASM_JobSetState  CAL_CMEXPAPI( "ASM_JobSetState" ) 
#else /* DYNAMIC_LINK */
	#define USE_ASM_JobSetState  PFASM_JOBSETSTATE pfASM_JobSetState;
	#define EXT_ASM_JobSetState  extern PFASM_JOBSETSTATE pfASM_JobSetState;
	#define GET_ASM_JobSetState(fl)  s_pfCMGetAPI2( "ASM_JobSetState", (RTS_VOID_FCTPTR *)&pfASM_JobSetState, (fl), 0, 0)
	#define CAL_ASM_JobSetState  pfASM_JobSetState
	#define CHK_ASM_JobSetState  (pfASM_JobSetState != NULL)
	#define EXP_ASM_JobSetState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_JobSetState", (RTS_UINTPTR)ASM_JobSetState, 0, 0) 
#endif



unsigned short CDECL ASM_GetSupplierVersion(CAA_BOOL xDummy);
typedef unsigned short (CDECL * PFASM_GETSUPPLIERVERSION) (CAA_BOOL xDummy);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_GETSUPPLIERVERSION_NOTIMPLEMENTED)
	#define USE_ASM_GetSupplierVersion
	#define EXT_ASM_GetSupplierVersion
	#define GET_ASM_GetSupplierVersion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ASM_GetSupplierVersion(p0)  (unsigned short)ERR_NOTIMPLEMENTED
	#define CHK_ASM_GetSupplierVersion  FALSE
	#define EXP_ASM_GetSupplierVersion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ASM_GetSupplierVersion
	#define EXT_ASM_GetSupplierVersion
	#define GET_ASM_GetSupplierVersion(fl)  CAL_CMGETAPI( "ASM_GetSupplierVersion" ) 
	#define CAL_ASM_GetSupplierVersion  ASM_GetSupplierVersion
	#define CHK_ASM_GetSupplierVersion  TRUE
	#define EXP_ASM_GetSupplierVersion  CAL_CMEXPAPI( "ASM_GetSupplierVersion" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_ASM_GetSupplierVersion
	#define EXT_ASM_GetSupplierVersion
	#define GET_ASM_GetSupplierVersion(fl)  CAL_CMGETAPI( "ASM_GetSupplierVersion" ) 
	#define CAL_ASM_GetSupplierVersion  ASM_GetSupplierVersion
	#define CHK_ASM_GetSupplierVersion  TRUE
	#define EXP_ASM_GetSupplierVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_GetSupplierVersion", (RTS_UINTPTR)ASM_GetSupplierVersion, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManASM_GetSupplierVersion
	#define EXT_CmpCAAAsyncManASM_GetSupplierVersion
	#define GET_CmpCAAAsyncManASM_GetSupplierVersion  ERR_OK
	#define CAL_CmpCAAAsyncManASM_GetSupplierVersion pICmpCAAAsyncMan->IASM_GetSupplierVersion
	#define CHK_CmpCAAAsyncManASM_GetSupplierVersion (pICmpCAAAsyncMan != NULL)
	#define EXP_CmpCAAAsyncManASM_GetSupplierVersion  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ASM_GetSupplierVersion
	#define EXT_ASM_GetSupplierVersion
	#define GET_ASM_GetSupplierVersion(fl)  CAL_CMGETAPI( "ASM_GetSupplierVersion" ) 
	#define CAL_ASM_GetSupplierVersion pICmpCAAAsyncMan->IASM_GetSupplierVersion
	#define CHK_ASM_GetSupplierVersion (pICmpCAAAsyncMan != NULL)
	#define EXP_ASM_GetSupplierVersion  CAL_CMEXPAPI( "ASM_GetSupplierVersion" ) 
#else /* DYNAMIC_LINK */
	#define USE_ASM_GetSupplierVersion  PFASM_GETSUPPLIERVERSION pfASM_GetSupplierVersion;
	#define EXT_ASM_GetSupplierVersion  extern PFASM_GETSUPPLIERVERSION pfASM_GetSupplierVersion;
	#define GET_ASM_GetSupplierVersion(fl)  s_pfCMGetAPI2( "ASM_GetSupplierVersion", (RTS_VOID_FCTPTR *)&pfASM_GetSupplierVersion, (fl), 0, 0)
	#define CAL_ASM_GetSupplierVersion  pfASM_GetSupplierVersion
	#define CHK_ASM_GetSupplierVersion  (pfASM_GetSupplierVersion != NULL)
	#define EXP_ASM_GetSupplierVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_GetSupplierVersion", (RTS_UINTPTR)ASM_GetSupplierVersion, 0, 0) 
#endif



CAA_ERROR CDECL ASM_JobExecQueue(void);
typedef CAA_ERROR (CDECL * PFASM_JOBEXECQUEUE) (void);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_JOBEXECQUEUE_NOTIMPLEMENTED)
	#define USE_ASM_JobExecQueue
	#define EXT_ASM_JobExecQueue
	#define GET_ASM_JobExecQueue(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ASM_JobExecQueue()  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_ASM_JobExecQueue  FALSE
	#define EXP_ASM_JobExecQueue  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ASM_JobExecQueue
	#define EXT_ASM_JobExecQueue
	#define GET_ASM_JobExecQueue(fl)  CAL_CMGETAPI( "ASM_JobExecQueue" ) 
	#define CAL_ASM_JobExecQueue  ASM_JobExecQueue
	#define CHK_ASM_JobExecQueue  TRUE
	#define EXP_ASM_JobExecQueue  CAL_CMEXPAPI( "ASM_JobExecQueue" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_ASM_JobExecQueue
	#define EXT_ASM_JobExecQueue
	#define GET_ASM_JobExecQueue(fl)  CAL_CMGETAPI( "ASM_JobExecQueue" ) 
	#define CAL_ASM_JobExecQueue  ASM_JobExecQueue
	#define CHK_ASM_JobExecQueue  TRUE
	#define EXP_ASM_JobExecQueue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_JobExecQueue", (RTS_UINTPTR)ASM_JobExecQueue, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManASM_JobExecQueue
	#define EXT_CmpCAAAsyncManASM_JobExecQueue
	#define GET_CmpCAAAsyncManASM_JobExecQueue  ERR_OK
	#define CAL_CmpCAAAsyncManASM_JobExecQueue pICmpCAAAsyncMan->IASM_JobExecQueue
	#define CHK_CmpCAAAsyncManASM_JobExecQueue (pICmpCAAAsyncMan != NULL)
	#define EXP_CmpCAAAsyncManASM_JobExecQueue  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ASM_JobExecQueue
	#define EXT_ASM_JobExecQueue
	#define GET_ASM_JobExecQueue(fl)  CAL_CMGETAPI( "ASM_JobExecQueue" ) 
	#define CAL_ASM_JobExecQueue pICmpCAAAsyncMan->IASM_JobExecQueue
	#define CHK_ASM_JobExecQueue (pICmpCAAAsyncMan != NULL)
	#define EXP_ASM_JobExecQueue  CAL_CMEXPAPI( "ASM_JobExecQueue" ) 
#else /* DYNAMIC_LINK */
	#define USE_ASM_JobExecQueue  PFASM_JOBEXECQUEUE pfASM_JobExecQueue;
	#define EXT_ASM_JobExecQueue  extern PFASM_JOBEXECQUEUE pfASM_JobExecQueue;
	#define GET_ASM_JobExecQueue(fl)  s_pfCMGetAPI2( "ASM_JobExecQueue", (RTS_VOID_FCTPTR *)&pfASM_JobExecQueue, (fl), 0, 0)
	#define CAL_ASM_JobExecQueue  pfASM_JobExecQueue
	#define CHK_ASM_JobExecQueue  (pfASM_JobExecQueue != NULL)
	#define EXP_ASM_JobExecQueue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ASM_JobExecQueue", (RTS_UINTPTR)ASM_JobExecQueue, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>asm_jobabort</description>
 */
typedef struct tagasm_jobabort_struct
{
	CAA_HANDLE hJob;					/* VAR_INPUT */	/* Handle of a Job */
	CAA_ERROR ASM_JobAbort;				/* VAR_OUTPUT */	
} asm_jobabort_struct;

void CDECL CDECL_EXT asm_jobabort(asm_jobabort_struct *p);
typedef void (CDECL CDECL_EXT* PFASM_JOBABORT_IEC) (asm_jobabort_struct *p);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_JOBABORT_NOTIMPLEMENTED)
	#define USE_asm_jobabort
	#define EXT_asm_jobabort
	#define GET_asm_jobabort(fl)  ERR_NOTIMPLEMENTED
	#define CAL_asm_jobabort(p0) 
	#define CHK_asm_jobabort  FALSE
	#define EXP_asm_jobabort  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_asm_jobabort
	#define EXT_asm_jobabort
	#define GET_asm_jobabort(fl)  CAL_CMGETAPI( "asm_jobabort" ) 
	#define CAL_asm_jobabort  asm_jobabort
	#define CHK_asm_jobabort  TRUE
	#define EXP_asm_jobabort  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobabort", (RTS_UINTPTR)asm_jobabort, 1, RTSITF_GET_SIGNATURE(0, 0x5050C65B), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_asm_jobabort
	#define EXT_asm_jobabort
	#define GET_asm_jobabort(fl)  CAL_CMGETAPI( "asm_jobabort" ) 
	#define CAL_asm_jobabort  asm_jobabort
	#define CHK_asm_jobabort  TRUE
	#define EXP_asm_jobabort  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobabort", (RTS_UINTPTR)asm_jobabort, 1, RTSITF_GET_SIGNATURE(0, 0x5050C65B), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManasm_jobabort
	#define EXT_CmpCAAAsyncManasm_jobabort
	#define GET_CmpCAAAsyncManasm_jobabort  ERR_OK
	#define CAL_CmpCAAAsyncManasm_jobabort  asm_jobabort
	#define CHK_CmpCAAAsyncManasm_jobabort  TRUE
	#define EXP_CmpCAAAsyncManasm_jobabort  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobabort", (RTS_UINTPTR)asm_jobabort, 1, RTSITF_GET_SIGNATURE(0, 0x5050C65B), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_asm_jobabort
	#define EXT_asm_jobabort
	#define GET_asm_jobabort(fl)  CAL_CMGETAPI( "asm_jobabort" ) 
	#define CAL_asm_jobabort  asm_jobabort
	#define CHK_asm_jobabort  TRUE
	#define EXP_asm_jobabort  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobabort", (RTS_UINTPTR)asm_jobabort, 1, RTSITF_GET_SIGNATURE(0, 0x5050C65B), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_asm_jobabort  PFASM_JOBABORT_IEC pfasm_jobabort;
	#define EXT_asm_jobabort  extern PFASM_JOBABORT_IEC pfasm_jobabort;
	#define GET_asm_jobabort(fl)  s_pfCMGetAPI2( "asm_jobabort", (RTS_VOID_FCTPTR *)&pfasm_jobabort, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x5050C65B), 0x03050528)
	#define CAL_asm_jobabort  pfasm_jobabort
	#define CHK_asm_jobabort  (pfasm_jobabort != NULL)
	#define EXP_asm_jobabort   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobabort", (RTS_UINTPTR)asm_jobabort, 1, RTSITF_GET_SIGNATURE(0, 0x5050C65B), 0x03050528) 
#endif


/**
 * <description>asm_jobclose</description>
 */
typedef struct tagasm_jobclose_struct
{
	CAA_HANDLE hJob;					/* VAR_INPUT */	/* Handle of a Job */
	CAA_ERROR ASM_JobClose;				/* VAR_OUTPUT */	
} asm_jobclose_struct;

void CDECL CDECL_EXT asm_jobclose(asm_jobclose_struct *p);
typedef void (CDECL CDECL_EXT* PFASM_JOBCLOSE_IEC) (asm_jobclose_struct *p);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_JOBCLOSE_NOTIMPLEMENTED)
	#define USE_asm_jobclose
	#define EXT_asm_jobclose
	#define GET_asm_jobclose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_asm_jobclose(p0) 
	#define CHK_asm_jobclose  FALSE
	#define EXP_asm_jobclose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_asm_jobclose
	#define EXT_asm_jobclose
	#define GET_asm_jobclose(fl)  CAL_CMGETAPI( "asm_jobclose" ) 
	#define CAL_asm_jobclose  asm_jobclose
	#define CHK_asm_jobclose  TRUE
	#define EXP_asm_jobclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobclose", (RTS_UINTPTR)asm_jobclose, 1, RTSITF_GET_SIGNATURE(0, 0xE8BCA52A), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_asm_jobclose
	#define EXT_asm_jobclose
	#define GET_asm_jobclose(fl)  CAL_CMGETAPI( "asm_jobclose" ) 
	#define CAL_asm_jobclose  asm_jobclose
	#define CHK_asm_jobclose  TRUE
	#define EXP_asm_jobclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobclose", (RTS_UINTPTR)asm_jobclose, 1, RTSITF_GET_SIGNATURE(0, 0xE8BCA52A), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManasm_jobclose
	#define EXT_CmpCAAAsyncManasm_jobclose
	#define GET_CmpCAAAsyncManasm_jobclose  ERR_OK
	#define CAL_CmpCAAAsyncManasm_jobclose  asm_jobclose
	#define CHK_CmpCAAAsyncManasm_jobclose  TRUE
	#define EXP_CmpCAAAsyncManasm_jobclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobclose", (RTS_UINTPTR)asm_jobclose, 1, RTSITF_GET_SIGNATURE(0, 0xE8BCA52A), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_asm_jobclose
	#define EXT_asm_jobclose
	#define GET_asm_jobclose(fl)  CAL_CMGETAPI( "asm_jobclose" ) 
	#define CAL_asm_jobclose  asm_jobclose
	#define CHK_asm_jobclose  TRUE
	#define EXP_asm_jobclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobclose", (RTS_UINTPTR)asm_jobclose, 1, RTSITF_GET_SIGNATURE(0, 0xE8BCA52A), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_asm_jobclose  PFASM_JOBCLOSE_IEC pfasm_jobclose;
	#define EXT_asm_jobclose  extern PFASM_JOBCLOSE_IEC pfasm_jobclose;
	#define GET_asm_jobclose(fl)  s_pfCMGetAPI2( "asm_jobclose", (RTS_VOID_FCTPTR *)&pfasm_jobclose, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xE8BCA52A), 0x03050528)
	#define CAL_asm_jobclose  pfasm_jobclose
	#define CHK_asm_jobclose  (pfasm_jobclose != NULL)
	#define EXP_asm_jobclose   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobclose", (RTS_UINTPTR)asm_jobclose, 1, RTSITF_GET_SIGNATURE(0, 0xE8BCA52A), 0x03050528) 
#endif


/**
 * <description>asm_jobexecute</description>
 */
typedef struct tagasm_jobexecute_struct
{
	CAA_HANDLE hJob;					/* VAR_INPUT */	/* Handle of a Job */
	CAA_ERROR ASM_JobExecute;			/* VAR_OUTPUT */	
} asm_jobexecute_struct;

void CDECL CDECL_EXT asm_jobexecute(asm_jobexecute_struct *p);
typedef void (CDECL CDECL_EXT* PFASM_JOBEXECUTE_IEC) (asm_jobexecute_struct *p);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_JOBEXECUTE_NOTIMPLEMENTED)
	#define USE_asm_jobexecute
	#define EXT_asm_jobexecute
	#define GET_asm_jobexecute(fl)  ERR_NOTIMPLEMENTED
	#define CAL_asm_jobexecute(p0) 
	#define CHK_asm_jobexecute  FALSE
	#define EXP_asm_jobexecute  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_asm_jobexecute
	#define EXT_asm_jobexecute
	#define GET_asm_jobexecute(fl)  CAL_CMGETAPI( "asm_jobexecute" ) 
	#define CAL_asm_jobexecute  asm_jobexecute
	#define CHK_asm_jobexecute  TRUE
	#define EXP_asm_jobexecute  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobexecute", (RTS_UINTPTR)asm_jobexecute, 1, RTSITF_GET_SIGNATURE(0, 0x35D667D5), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_asm_jobexecute
	#define EXT_asm_jobexecute
	#define GET_asm_jobexecute(fl)  CAL_CMGETAPI( "asm_jobexecute" ) 
	#define CAL_asm_jobexecute  asm_jobexecute
	#define CHK_asm_jobexecute  TRUE
	#define EXP_asm_jobexecute  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobexecute", (RTS_UINTPTR)asm_jobexecute, 1, RTSITF_GET_SIGNATURE(0, 0x35D667D5), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManasm_jobexecute
	#define EXT_CmpCAAAsyncManasm_jobexecute
	#define GET_CmpCAAAsyncManasm_jobexecute  ERR_OK
	#define CAL_CmpCAAAsyncManasm_jobexecute  asm_jobexecute
	#define CHK_CmpCAAAsyncManasm_jobexecute  TRUE
	#define EXP_CmpCAAAsyncManasm_jobexecute  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobexecute", (RTS_UINTPTR)asm_jobexecute, 1, RTSITF_GET_SIGNATURE(0, 0x35D667D5), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_asm_jobexecute
	#define EXT_asm_jobexecute
	#define GET_asm_jobexecute(fl)  CAL_CMGETAPI( "asm_jobexecute" ) 
	#define CAL_asm_jobexecute  asm_jobexecute
	#define CHK_asm_jobexecute  TRUE
	#define EXP_asm_jobexecute  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobexecute", (RTS_UINTPTR)asm_jobexecute, 1, RTSITF_GET_SIGNATURE(0, 0x35D667D5), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_asm_jobexecute  PFASM_JOBEXECUTE_IEC pfasm_jobexecute;
	#define EXT_asm_jobexecute  extern PFASM_JOBEXECUTE_IEC pfasm_jobexecute;
	#define GET_asm_jobexecute(fl)  s_pfCMGetAPI2( "asm_jobexecute", (RTS_VOID_FCTPTR *)&pfasm_jobexecute, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x35D667D5), 0x03050528)
	#define CAL_asm_jobexecute  pfasm_jobexecute
	#define CHK_asm_jobexecute  (pfasm_jobexecute != NULL)
	#define EXP_asm_jobexecute   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobexecute", (RTS_UINTPTR)asm_jobexecute, 1, RTSITF_GET_SIGNATURE(0, 0x35D667D5), 0x03050528) 
#endif


/**
 * <description>asm_jobgetid</description>
 */
typedef struct tagasm_jobgetid_struct
{
	CAA_HANDLE hJob;					/* VAR_INPUT */	/* Handle of a Job */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	RTS_IEC_UDINT ASM_JobGetId;			/* VAR_OUTPUT */	
} asm_jobgetid_struct;

void CDECL CDECL_EXT asm_jobgetid(asm_jobgetid_struct *p);
typedef void (CDECL CDECL_EXT* PFASM_JOBGETID_IEC) (asm_jobgetid_struct *p);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_JOBGETID_NOTIMPLEMENTED)
	#define USE_asm_jobgetid
	#define EXT_asm_jobgetid
	#define GET_asm_jobgetid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_asm_jobgetid(p0) 
	#define CHK_asm_jobgetid  FALSE
	#define EXP_asm_jobgetid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_asm_jobgetid
	#define EXT_asm_jobgetid
	#define GET_asm_jobgetid(fl)  CAL_CMGETAPI( "asm_jobgetid" ) 
	#define CAL_asm_jobgetid  asm_jobgetid
	#define CHK_asm_jobgetid  TRUE
	#define EXP_asm_jobgetid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobgetid", (RTS_UINTPTR)asm_jobgetid, 1, RTSITF_GET_SIGNATURE(0, 0x4C69332D), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_asm_jobgetid
	#define EXT_asm_jobgetid
	#define GET_asm_jobgetid(fl)  CAL_CMGETAPI( "asm_jobgetid" ) 
	#define CAL_asm_jobgetid  asm_jobgetid
	#define CHK_asm_jobgetid  TRUE
	#define EXP_asm_jobgetid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobgetid", (RTS_UINTPTR)asm_jobgetid, 1, RTSITF_GET_SIGNATURE(0, 0x4C69332D), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManasm_jobgetid
	#define EXT_CmpCAAAsyncManasm_jobgetid
	#define GET_CmpCAAAsyncManasm_jobgetid  ERR_OK
	#define CAL_CmpCAAAsyncManasm_jobgetid  asm_jobgetid
	#define CHK_CmpCAAAsyncManasm_jobgetid  TRUE
	#define EXP_CmpCAAAsyncManasm_jobgetid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobgetid", (RTS_UINTPTR)asm_jobgetid, 1, RTSITF_GET_SIGNATURE(0, 0x4C69332D), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_asm_jobgetid
	#define EXT_asm_jobgetid
	#define GET_asm_jobgetid(fl)  CAL_CMGETAPI( "asm_jobgetid" ) 
	#define CAL_asm_jobgetid  asm_jobgetid
	#define CHK_asm_jobgetid  TRUE
	#define EXP_asm_jobgetid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobgetid", (RTS_UINTPTR)asm_jobgetid, 1, RTSITF_GET_SIGNATURE(0, 0x4C69332D), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_asm_jobgetid  PFASM_JOBGETID_IEC pfasm_jobgetid;
	#define EXT_asm_jobgetid  extern PFASM_JOBGETID_IEC pfasm_jobgetid;
	#define GET_asm_jobgetid(fl)  s_pfCMGetAPI2( "asm_jobgetid", (RTS_VOID_FCTPTR *)&pfasm_jobgetid, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x4C69332D), 0x03050528)
	#define CAL_asm_jobgetid  pfasm_jobgetid
	#define CHK_asm_jobgetid  (pfasm_jobgetid != NULL)
	#define EXP_asm_jobgetid   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobgetid", (RTS_UINTPTR)asm_jobgetid, 1, RTSITF_GET_SIGNATURE(0, 0x4C69332D), 0x03050528) 
#endif


/**
 * <description>asm_jobgetparams</description>
 */
typedef struct tagasm_jobgetparams_struct
{
	CAA_HANDLE hJob;					/* VAR_INPUT */	/* Handle of a Job */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_PVOID ASM_JobGetParams;			/* VAR_OUTPUT */	
} asm_jobgetparams_struct;

void CDECL CDECL_EXT asm_jobgetparams(asm_jobgetparams_struct *p);
typedef void (CDECL CDECL_EXT* PFASM_JOBGETPARAMS_IEC) (asm_jobgetparams_struct *p);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_JOBGETPARAMS_NOTIMPLEMENTED)
	#define USE_asm_jobgetparams
	#define EXT_asm_jobgetparams
	#define GET_asm_jobgetparams(fl)  ERR_NOTIMPLEMENTED
	#define CAL_asm_jobgetparams(p0) 
	#define CHK_asm_jobgetparams  FALSE
	#define EXP_asm_jobgetparams  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_asm_jobgetparams
	#define EXT_asm_jobgetparams
	#define GET_asm_jobgetparams(fl)  CAL_CMGETAPI( "asm_jobgetparams" ) 
	#define CAL_asm_jobgetparams  asm_jobgetparams
	#define CHK_asm_jobgetparams  TRUE
	#define EXP_asm_jobgetparams  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobgetparams", (RTS_UINTPTR)asm_jobgetparams, 1, RTSITF_GET_SIGNATURE(0, 0x77004163), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_asm_jobgetparams
	#define EXT_asm_jobgetparams
	#define GET_asm_jobgetparams(fl)  CAL_CMGETAPI( "asm_jobgetparams" ) 
	#define CAL_asm_jobgetparams  asm_jobgetparams
	#define CHK_asm_jobgetparams  TRUE
	#define EXP_asm_jobgetparams  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobgetparams", (RTS_UINTPTR)asm_jobgetparams, 1, RTSITF_GET_SIGNATURE(0, 0x77004163), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManasm_jobgetparams
	#define EXT_CmpCAAAsyncManasm_jobgetparams
	#define GET_CmpCAAAsyncManasm_jobgetparams  ERR_OK
	#define CAL_CmpCAAAsyncManasm_jobgetparams  asm_jobgetparams
	#define CHK_CmpCAAAsyncManasm_jobgetparams  TRUE
	#define EXP_CmpCAAAsyncManasm_jobgetparams  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobgetparams", (RTS_UINTPTR)asm_jobgetparams, 1, RTSITF_GET_SIGNATURE(0, 0x77004163), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_asm_jobgetparams
	#define EXT_asm_jobgetparams
	#define GET_asm_jobgetparams(fl)  CAL_CMGETAPI( "asm_jobgetparams" ) 
	#define CAL_asm_jobgetparams  asm_jobgetparams
	#define CHK_asm_jobgetparams  TRUE
	#define EXP_asm_jobgetparams  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobgetparams", (RTS_UINTPTR)asm_jobgetparams, 1, RTSITF_GET_SIGNATURE(0, 0x77004163), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_asm_jobgetparams  PFASM_JOBGETPARAMS_IEC pfasm_jobgetparams;
	#define EXT_asm_jobgetparams  extern PFASM_JOBGETPARAMS_IEC pfasm_jobgetparams;
	#define GET_asm_jobgetparams(fl)  s_pfCMGetAPI2( "asm_jobgetparams", (RTS_VOID_FCTPTR *)&pfasm_jobgetparams, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x77004163), 0x03050528)
	#define CAL_asm_jobgetparams  pfasm_jobgetparams
	#define CHK_asm_jobgetparams  (pfasm_jobgetparams != NULL)
	#define EXP_asm_jobgetparams   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobgetparams", (RTS_UINTPTR)asm_jobgetparams, 1, RTSITF_GET_SIGNATURE(0, 0x77004163), 0x03050528) 
#endif


/**
 * <description>asm_jobgetstate</description>
 */
typedef struct tagasm_jobgetstate_struct
{
	CAA_HANDLE hJob;					/* VAR_INPUT */	/* Handle of a Job */
	ASM_STATE *pStateJob;				/* VAR_INPUT */	
	CAA_ERROR ASM_JobGetState;			/* VAR_OUTPUT */	
} asm_jobgetstate_struct;

void CDECL CDECL_EXT asm_jobgetstate(asm_jobgetstate_struct *p);
typedef void (CDECL CDECL_EXT* PFASM_JOBGETSTATE_IEC) (asm_jobgetstate_struct *p);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_JOBGETSTATE_NOTIMPLEMENTED)
	#define USE_asm_jobgetstate
	#define EXT_asm_jobgetstate
	#define GET_asm_jobgetstate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_asm_jobgetstate(p0) 
	#define CHK_asm_jobgetstate  FALSE
	#define EXP_asm_jobgetstate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_asm_jobgetstate
	#define EXT_asm_jobgetstate
	#define GET_asm_jobgetstate(fl)  CAL_CMGETAPI( "asm_jobgetstate" ) 
	#define CAL_asm_jobgetstate  asm_jobgetstate
	#define CHK_asm_jobgetstate  TRUE
	#define EXP_asm_jobgetstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobgetstate", (RTS_UINTPTR)asm_jobgetstate, 1, RTSITF_GET_SIGNATURE(0, 0xBA2A911E), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_asm_jobgetstate
	#define EXT_asm_jobgetstate
	#define GET_asm_jobgetstate(fl)  CAL_CMGETAPI( "asm_jobgetstate" ) 
	#define CAL_asm_jobgetstate  asm_jobgetstate
	#define CHK_asm_jobgetstate  TRUE
	#define EXP_asm_jobgetstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobgetstate", (RTS_UINTPTR)asm_jobgetstate, 1, RTSITF_GET_SIGNATURE(0, 0xBA2A911E), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManasm_jobgetstate
	#define EXT_CmpCAAAsyncManasm_jobgetstate
	#define GET_CmpCAAAsyncManasm_jobgetstate  ERR_OK
	#define CAL_CmpCAAAsyncManasm_jobgetstate  asm_jobgetstate
	#define CHK_CmpCAAAsyncManasm_jobgetstate  TRUE
	#define EXP_CmpCAAAsyncManasm_jobgetstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobgetstate", (RTS_UINTPTR)asm_jobgetstate, 1, RTSITF_GET_SIGNATURE(0, 0xBA2A911E), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_asm_jobgetstate
	#define EXT_asm_jobgetstate
	#define GET_asm_jobgetstate(fl)  CAL_CMGETAPI( "asm_jobgetstate" ) 
	#define CAL_asm_jobgetstate  asm_jobgetstate
	#define CHK_asm_jobgetstate  TRUE
	#define EXP_asm_jobgetstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobgetstate", (RTS_UINTPTR)asm_jobgetstate, 1, RTSITF_GET_SIGNATURE(0, 0xBA2A911E), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_asm_jobgetstate  PFASM_JOBGETSTATE_IEC pfasm_jobgetstate;
	#define EXT_asm_jobgetstate  extern PFASM_JOBGETSTATE_IEC pfasm_jobgetstate;
	#define GET_asm_jobgetstate(fl)  s_pfCMGetAPI2( "asm_jobgetstate", (RTS_VOID_FCTPTR *)&pfasm_jobgetstate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xBA2A911E), 0x03050528)
	#define CAL_asm_jobgetstate  pfasm_jobgetstate
	#define CHK_asm_jobgetstate  (pfasm_jobgetstate != NULL)
	#define EXP_asm_jobgetstate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobgetstate", (RTS_UINTPTR)asm_jobgetstate, 1, RTSITF_GET_SIGNATURE(0, 0xBA2A911E), 0x03050528) 
#endif


/**
 * <description>asm_jobopen</description>
 */
typedef struct tagasm_jobopen_struct
{
	RTS_IEC_UDINT udiId;				/* VAR_INPUT */	/* Unique Identifier, see Praefix.pdf */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE ASM_JobOpen;				/* VAR_OUTPUT */	
} asm_jobopen_struct;

void CDECL CDECL_EXT asm_jobopen(asm_jobopen_struct *p);
typedef void (CDECL CDECL_EXT* PFASM_JOBOPEN_IEC) (asm_jobopen_struct *p);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_JOBOPEN_NOTIMPLEMENTED)
	#define USE_asm_jobopen
	#define EXT_asm_jobopen
	#define GET_asm_jobopen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_asm_jobopen(p0) 
	#define CHK_asm_jobopen  FALSE
	#define EXP_asm_jobopen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_asm_jobopen
	#define EXT_asm_jobopen
	#define GET_asm_jobopen(fl)  CAL_CMGETAPI( "asm_jobopen" ) 
	#define CAL_asm_jobopen  asm_jobopen
	#define CHK_asm_jobopen  TRUE
	#define EXP_asm_jobopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobopen", (RTS_UINTPTR)asm_jobopen, 1, RTSITF_GET_SIGNATURE(0, 0x0D083D90), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_asm_jobopen
	#define EXT_asm_jobopen
	#define GET_asm_jobopen(fl)  CAL_CMGETAPI( "asm_jobopen" ) 
	#define CAL_asm_jobopen  asm_jobopen
	#define CHK_asm_jobopen  TRUE
	#define EXP_asm_jobopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobopen", (RTS_UINTPTR)asm_jobopen, 1, RTSITF_GET_SIGNATURE(0, 0x0D083D90), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManasm_jobopen
	#define EXT_CmpCAAAsyncManasm_jobopen
	#define GET_CmpCAAAsyncManasm_jobopen  ERR_OK
	#define CAL_CmpCAAAsyncManasm_jobopen  asm_jobopen
	#define CHK_CmpCAAAsyncManasm_jobopen  TRUE
	#define EXP_CmpCAAAsyncManasm_jobopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobopen", (RTS_UINTPTR)asm_jobopen, 1, RTSITF_GET_SIGNATURE(0, 0x0D083D90), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_asm_jobopen
	#define EXT_asm_jobopen
	#define GET_asm_jobopen(fl)  CAL_CMGETAPI( "asm_jobopen" ) 
	#define CAL_asm_jobopen  asm_jobopen
	#define CHK_asm_jobopen  TRUE
	#define EXP_asm_jobopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobopen", (RTS_UINTPTR)asm_jobopen, 1, RTSITF_GET_SIGNATURE(0, 0x0D083D90), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_asm_jobopen  PFASM_JOBOPEN_IEC pfasm_jobopen;
	#define EXT_asm_jobopen  extern PFASM_JOBOPEN_IEC pfasm_jobopen;
	#define GET_asm_jobopen(fl)  s_pfCMGetAPI2( "asm_jobopen", (RTS_VOID_FCTPTR *)&pfasm_jobopen, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x0D083D90), 0x03050528)
	#define CAL_asm_jobopen  pfasm_jobopen
	#define CHK_asm_jobopen  (pfasm_jobopen != NULL)
	#define EXP_asm_jobopen   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobopen", (RTS_UINTPTR)asm_jobopen, 1, RTSITF_GET_SIGNATURE(0, 0x0D083D90), 0x03050528) 
#endif


/**
 * <description>asm_jobopenex</description>
 */
typedef struct tagasm_jobopenex_struct
{
	RTS_IEC_UDINT udiId;				/* VAR_INPUT */	/* Unique Identifier, see Praefix.pdf */
	CAA_PVOID pParams;					/* VAR_INPUT */	/* Pointer to Parameters */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE ASM_JobOpenEx;			/* VAR_OUTPUT */	
} asm_jobopenex_struct;

void CDECL CDECL_EXT asm_jobopenex(asm_jobopenex_struct *p);
typedef void (CDECL CDECL_EXT* PFASM_JOBOPENEX_IEC) (asm_jobopenex_struct *p);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_JOBOPENEX_NOTIMPLEMENTED)
	#define USE_asm_jobopenex
	#define EXT_asm_jobopenex
	#define GET_asm_jobopenex(fl)  ERR_NOTIMPLEMENTED
	#define CAL_asm_jobopenex(p0) 
	#define CHK_asm_jobopenex  FALSE
	#define EXP_asm_jobopenex  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_asm_jobopenex
	#define EXT_asm_jobopenex
	#define GET_asm_jobopenex(fl)  CAL_CMGETAPI( "asm_jobopenex" ) 
	#define CAL_asm_jobopenex  asm_jobopenex
	#define CHK_asm_jobopenex  TRUE
	#define EXP_asm_jobopenex  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobopenex", (RTS_UINTPTR)asm_jobopenex, 1, RTSITF_GET_SIGNATURE(0, 0x1B44DB2C), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_asm_jobopenex
	#define EXT_asm_jobopenex
	#define GET_asm_jobopenex(fl)  CAL_CMGETAPI( "asm_jobopenex" ) 
	#define CAL_asm_jobopenex  asm_jobopenex
	#define CHK_asm_jobopenex  TRUE
	#define EXP_asm_jobopenex  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobopenex", (RTS_UINTPTR)asm_jobopenex, 1, RTSITF_GET_SIGNATURE(0, 0x1B44DB2C), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManasm_jobopenex
	#define EXT_CmpCAAAsyncManasm_jobopenex
	#define GET_CmpCAAAsyncManasm_jobopenex  ERR_OK
	#define CAL_CmpCAAAsyncManasm_jobopenex  asm_jobopenex
	#define CHK_CmpCAAAsyncManasm_jobopenex  TRUE
	#define EXP_CmpCAAAsyncManasm_jobopenex  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobopenex", (RTS_UINTPTR)asm_jobopenex, 1, RTSITF_GET_SIGNATURE(0, 0x1B44DB2C), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_asm_jobopenex
	#define EXT_asm_jobopenex
	#define GET_asm_jobopenex(fl)  CAL_CMGETAPI( "asm_jobopenex" ) 
	#define CAL_asm_jobopenex  asm_jobopenex
	#define CHK_asm_jobopenex  TRUE
	#define EXP_asm_jobopenex  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobopenex", (RTS_UINTPTR)asm_jobopenex, 1, RTSITF_GET_SIGNATURE(0, 0x1B44DB2C), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_asm_jobopenex  PFASM_JOBOPENEX_IEC pfasm_jobopenex;
	#define EXT_asm_jobopenex  extern PFASM_JOBOPENEX_IEC pfasm_jobopenex;
	#define GET_asm_jobopenex(fl)  s_pfCMGetAPI2( "asm_jobopenex", (RTS_VOID_FCTPTR *)&pfasm_jobopenex, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x1B44DB2C), 0x03050528)
	#define CAL_asm_jobopenex  pfasm_jobopenex
	#define CHK_asm_jobopenex  (pfasm_jobopenex != NULL)
	#define EXP_asm_jobopenex   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobopenex", (RTS_UINTPTR)asm_jobopenex, 1, RTSITF_GET_SIGNATURE(0, 0x1B44DB2C), 0x03050528) 
#endif


/**
 * <description>asm_jobreset</description>
 */
typedef struct tagasm_jobreset_struct
{
	CAA_HANDLE hJob;					/* VAR_INPUT */	/* Handle of a Job */
	CAA_ERROR ASM_JobReset;				/* VAR_OUTPUT */	
} asm_jobreset_struct;

void CDECL CDECL_EXT asm_jobreset(asm_jobreset_struct *p);
typedef void (CDECL CDECL_EXT* PFASM_JOBRESET_IEC) (asm_jobreset_struct *p);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_JOBRESET_NOTIMPLEMENTED)
	#define USE_asm_jobreset
	#define EXT_asm_jobreset
	#define GET_asm_jobreset(fl)  ERR_NOTIMPLEMENTED
	#define CAL_asm_jobreset(p0) 
	#define CHK_asm_jobreset  FALSE
	#define EXP_asm_jobreset  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_asm_jobreset
	#define EXT_asm_jobreset
	#define GET_asm_jobreset(fl)  CAL_CMGETAPI( "asm_jobreset" ) 
	#define CAL_asm_jobreset  asm_jobreset
	#define CHK_asm_jobreset  TRUE
	#define EXP_asm_jobreset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobreset", (RTS_UINTPTR)asm_jobreset, 1, RTSITF_GET_SIGNATURE(0, 0xE9F7DD31), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_asm_jobreset
	#define EXT_asm_jobreset
	#define GET_asm_jobreset(fl)  CAL_CMGETAPI( "asm_jobreset" ) 
	#define CAL_asm_jobreset  asm_jobreset
	#define CHK_asm_jobreset  TRUE
	#define EXP_asm_jobreset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobreset", (RTS_UINTPTR)asm_jobreset, 1, RTSITF_GET_SIGNATURE(0, 0xE9F7DD31), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManasm_jobreset
	#define EXT_CmpCAAAsyncManasm_jobreset
	#define GET_CmpCAAAsyncManasm_jobreset  ERR_OK
	#define CAL_CmpCAAAsyncManasm_jobreset  asm_jobreset
	#define CHK_CmpCAAAsyncManasm_jobreset  TRUE
	#define EXP_CmpCAAAsyncManasm_jobreset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobreset", (RTS_UINTPTR)asm_jobreset, 1, RTSITF_GET_SIGNATURE(0, 0xE9F7DD31), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_asm_jobreset
	#define EXT_asm_jobreset
	#define GET_asm_jobreset(fl)  CAL_CMGETAPI( "asm_jobreset" ) 
	#define CAL_asm_jobreset  asm_jobreset
	#define CHK_asm_jobreset  TRUE
	#define EXP_asm_jobreset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobreset", (RTS_UINTPTR)asm_jobreset, 1, RTSITF_GET_SIGNATURE(0, 0xE9F7DD31), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_asm_jobreset  PFASM_JOBRESET_IEC pfasm_jobreset;
	#define EXT_asm_jobreset  extern PFASM_JOBRESET_IEC pfasm_jobreset;
	#define GET_asm_jobreset(fl)  s_pfCMGetAPI2( "asm_jobreset", (RTS_VOID_FCTPTR *)&pfasm_jobreset, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xE9F7DD31), 0x03050528)
	#define CAL_asm_jobreset  pfasm_jobreset
	#define CHK_asm_jobreset  (pfasm_jobreset != NULL)
	#define EXP_asm_jobreset   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobreset", (RTS_UINTPTR)asm_jobreset, 1, RTSITF_GET_SIGNATURE(0, 0xE9F7DD31), 0x03050528) 
#endif


/**
 * Implementation Note: This function should be called only from a Worker
 */
typedef struct tagasm_jobsetstate_struct
{
	CAA_HANDLE hJob;					/* VAR_INPUT */	/* Handle of a Job */
	ASM_STATE StateJob;					/* VAR_INPUT */	
	CAA_ERROR ASM_JobSetState;			/* VAR_OUTPUT */	
} asm_jobsetstate_struct;

void CDECL CDECL_EXT asm_jobsetstate(asm_jobsetstate_struct *p);
typedef void (CDECL CDECL_EXT* PFASM_JOBSETSTATE_IEC) (asm_jobsetstate_struct *p);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_JOBSETSTATE_NOTIMPLEMENTED)
	#define USE_asm_jobsetstate
	#define EXT_asm_jobsetstate
	#define GET_asm_jobsetstate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_asm_jobsetstate(p0) 
	#define CHK_asm_jobsetstate  FALSE
	#define EXP_asm_jobsetstate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_asm_jobsetstate
	#define EXT_asm_jobsetstate
	#define GET_asm_jobsetstate(fl)  CAL_CMGETAPI( "asm_jobsetstate" ) 
	#define CAL_asm_jobsetstate  asm_jobsetstate
	#define CHK_asm_jobsetstate  TRUE
	#define EXP_asm_jobsetstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobsetstate", (RTS_UINTPTR)asm_jobsetstate, 1, RTSITF_GET_SIGNATURE(0, 0x5F95B914), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_asm_jobsetstate
	#define EXT_asm_jobsetstate
	#define GET_asm_jobsetstate(fl)  CAL_CMGETAPI( "asm_jobsetstate" ) 
	#define CAL_asm_jobsetstate  asm_jobsetstate
	#define CHK_asm_jobsetstate  TRUE
	#define EXP_asm_jobsetstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobsetstate", (RTS_UINTPTR)asm_jobsetstate, 1, RTSITF_GET_SIGNATURE(0, 0x5F95B914), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManasm_jobsetstate
	#define EXT_CmpCAAAsyncManasm_jobsetstate
	#define GET_CmpCAAAsyncManasm_jobsetstate  ERR_OK
	#define CAL_CmpCAAAsyncManasm_jobsetstate  asm_jobsetstate
	#define CHK_CmpCAAAsyncManasm_jobsetstate  TRUE
	#define EXP_CmpCAAAsyncManasm_jobsetstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobsetstate", (RTS_UINTPTR)asm_jobsetstate, 1, RTSITF_GET_SIGNATURE(0, 0x5F95B914), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_asm_jobsetstate
	#define EXT_asm_jobsetstate
	#define GET_asm_jobsetstate(fl)  CAL_CMGETAPI( "asm_jobsetstate" ) 
	#define CAL_asm_jobsetstate  asm_jobsetstate
	#define CHK_asm_jobsetstate  TRUE
	#define EXP_asm_jobsetstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobsetstate", (RTS_UINTPTR)asm_jobsetstate, 1, RTSITF_GET_SIGNATURE(0, 0x5F95B914), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_asm_jobsetstate  PFASM_JOBSETSTATE_IEC pfasm_jobsetstate;
	#define EXT_asm_jobsetstate  extern PFASM_JOBSETSTATE_IEC pfasm_jobsetstate;
	#define GET_asm_jobsetstate(fl)  s_pfCMGetAPI2( "asm_jobsetstate", (RTS_VOID_FCTPTR *)&pfasm_jobsetstate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x5F95B914), 0x03050528)
	#define CAL_asm_jobsetstate  pfasm_jobsetstate
	#define CHK_asm_jobsetstate  (pfasm_jobsetstate != NULL)
	#define EXP_asm_jobsetstate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_jobsetstate", (RTS_UINTPTR)asm_jobsetstate, 1, RTSITF_GET_SIGNATURE(0, 0x5F95B914), 0x03050528) 
#endif


/**
 * Implementation Note: A Worker must be implemented in C or in C++, IEC is not supported
 */
typedef struct tagasm_workerregister_struct
{
	RTS_IEC_UDINT udiId;				/* VAR_INPUT */	/* Unique Identifier, see Praefix.pdf */
	ASM_IWORKER *pwItf;					/* VAR_INPUT */	/* Pointer to Worker Interface */
	CAA_ERROR ASM_WorkerRegister;		/* VAR_OUTPUT */	
} asm_workerregister_struct;

void CDECL CDECL_EXT asm_workerregister(asm_workerregister_struct *p);
typedef void (CDECL CDECL_EXT* PFASM_WORKERREGISTER_IEC) (asm_workerregister_struct *p);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_WORKERREGISTER_NOTIMPLEMENTED)
	#define USE_asm_workerregister
	#define EXT_asm_workerregister
	#define GET_asm_workerregister(fl)  ERR_NOTIMPLEMENTED
	#define CAL_asm_workerregister(p0) 
	#define CHK_asm_workerregister  FALSE
	#define EXP_asm_workerregister  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_asm_workerregister
	#define EXT_asm_workerregister
	#define GET_asm_workerregister(fl)  CAL_CMGETAPI( "asm_workerregister" ) 
	#define CAL_asm_workerregister  asm_workerregister
	#define CHK_asm_workerregister  TRUE
	#define EXP_asm_workerregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_workerregister", (RTS_UINTPTR)asm_workerregister, 1, RTSITF_GET_SIGNATURE(0, 0x75B6C708), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_asm_workerregister
	#define EXT_asm_workerregister
	#define GET_asm_workerregister(fl)  CAL_CMGETAPI( "asm_workerregister" ) 
	#define CAL_asm_workerregister  asm_workerregister
	#define CHK_asm_workerregister  TRUE
	#define EXP_asm_workerregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_workerregister", (RTS_UINTPTR)asm_workerregister, 1, RTSITF_GET_SIGNATURE(0, 0x75B6C708), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManasm_workerregister
	#define EXT_CmpCAAAsyncManasm_workerregister
	#define GET_CmpCAAAsyncManasm_workerregister  ERR_OK
	#define CAL_CmpCAAAsyncManasm_workerregister  asm_workerregister
	#define CHK_CmpCAAAsyncManasm_workerregister  TRUE
	#define EXP_CmpCAAAsyncManasm_workerregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_workerregister", (RTS_UINTPTR)asm_workerregister, 1, RTSITF_GET_SIGNATURE(0, 0x75B6C708), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_asm_workerregister
	#define EXT_asm_workerregister
	#define GET_asm_workerregister(fl)  CAL_CMGETAPI( "asm_workerregister" ) 
	#define CAL_asm_workerregister  asm_workerregister
	#define CHK_asm_workerregister  TRUE
	#define EXP_asm_workerregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_workerregister", (RTS_UINTPTR)asm_workerregister, 1, RTSITF_GET_SIGNATURE(0, 0x75B6C708), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_asm_workerregister  PFASM_WORKERREGISTER_IEC pfasm_workerregister;
	#define EXT_asm_workerregister  extern PFASM_WORKERREGISTER_IEC pfasm_workerregister;
	#define GET_asm_workerregister(fl)  s_pfCMGetAPI2( "asm_workerregister", (RTS_VOID_FCTPTR *)&pfasm_workerregister, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x75B6C708), 0x03050528)
	#define CAL_asm_workerregister  pfasm_workerregister
	#define CHK_asm_workerregister  (pfasm_workerregister != NULL)
	#define EXP_asm_workerregister   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_workerregister", (RTS_UINTPTR)asm_workerregister, 1, RTSITF_GET_SIGNATURE(0, 0x75B6C708), 0x03050528) 
#endif


/**
 * Implementation Note: A Worker must be implemented in C or in C++, IEC is not supported
 */
typedef struct tagasm_workerunregister_struct
{
	RTS_IEC_UDINT udiId;				/* VAR_INPUT */	/* Unique Identifier, see Praefix.pdf */
	CAA_ERROR ASM_WorkerUnregister;		/* VAR_OUTPUT */	
} asm_workerunregister_struct;

void CDECL CDECL_EXT asm_workerunregister(asm_workerunregister_struct *p);
typedef void (CDECL CDECL_EXT* PFASM_WORKERUNREGISTER_IEC) (asm_workerunregister_struct *p);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_WORKERUNREGISTER_NOTIMPLEMENTED)
	#define USE_asm_workerunregister
	#define EXT_asm_workerunregister
	#define GET_asm_workerunregister(fl)  ERR_NOTIMPLEMENTED
	#define CAL_asm_workerunregister(p0) 
	#define CHK_asm_workerunregister  FALSE
	#define EXP_asm_workerunregister  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_asm_workerunregister
	#define EXT_asm_workerunregister
	#define GET_asm_workerunregister(fl)  CAL_CMGETAPI( "asm_workerunregister" ) 
	#define CAL_asm_workerunregister  asm_workerunregister
	#define CHK_asm_workerunregister  TRUE
	#define EXP_asm_workerunregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_workerunregister", (RTS_UINTPTR)asm_workerunregister, 1, RTSITF_GET_SIGNATURE(0, 0x4ECC5BAB), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_asm_workerunregister
	#define EXT_asm_workerunregister
	#define GET_asm_workerunregister(fl)  CAL_CMGETAPI( "asm_workerunregister" ) 
	#define CAL_asm_workerunregister  asm_workerunregister
	#define CHK_asm_workerunregister  TRUE
	#define EXP_asm_workerunregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_workerunregister", (RTS_UINTPTR)asm_workerunregister, 1, RTSITF_GET_SIGNATURE(0, 0x4ECC5BAB), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManasm_workerunregister
	#define EXT_CmpCAAAsyncManasm_workerunregister
	#define GET_CmpCAAAsyncManasm_workerunregister  ERR_OK
	#define CAL_CmpCAAAsyncManasm_workerunregister  asm_workerunregister
	#define CHK_CmpCAAAsyncManasm_workerunregister  TRUE
	#define EXP_CmpCAAAsyncManasm_workerunregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_workerunregister", (RTS_UINTPTR)asm_workerunregister, 1, RTSITF_GET_SIGNATURE(0, 0x4ECC5BAB), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_asm_workerunregister
	#define EXT_asm_workerunregister
	#define GET_asm_workerunregister(fl)  CAL_CMGETAPI( "asm_workerunregister" ) 
	#define CAL_asm_workerunregister  asm_workerunregister
	#define CHK_asm_workerunregister  TRUE
	#define EXP_asm_workerunregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_workerunregister", (RTS_UINTPTR)asm_workerunregister, 1, RTSITF_GET_SIGNATURE(0, 0x4ECC5BAB), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_asm_workerunregister  PFASM_WORKERUNREGISTER_IEC pfasm_workerunregister;
	#define EXT_asm_workerunregister  extern PFASM_WORKERUNREGISTER_IEC pfasm_workerunregister;
	#define GET_asm_workerunregister(fl)  s_pfCMGetAPI2( "asm_workerunregister", (RTS_VOID_FCTPTR *)&pfasm_workerunregister, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x4ECC5BAB), 0x03050528)
	#define CAL_asm_workerunregister  pfasm_workerunregister
	#define CHK_asm_workerunregister  (pfasm_workerunregister != NULL)
	#define EXP_asm_workerunregister   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_workerunregister", (RTS_UINTPTR)asm_workerunregister, 1, RTSITF_GET_SIGNATURE(0, 0x4ECC5BAB), 0x03050528) 
#endif


/**
 * <description>asm_getsupplierversion</description>
 */
typedef struct tagasm_getsupplierversion_struct
{
	RTS_IEC_WORD ASM_GetSupplierVersion;	/* VAR_OUTPUT */	
} asm_getsupplierversion_struct;

void CDECL CDECL_EXT asm_getsupplierversion(asm_getsupplierversion_struct *p);
typedef void (CDECL CDECL_EXT* PFASM_GETSUPPLIERVERSION_IEC) (asm_getsupplierversion_struct *p);
#if defined(CMPCAAASYNCMAN_NOTIMPLEMENTED) || defined(ASM_GETSUPPLIERVERSION_NOTIMPLEMENTED)
	#define USE_asm_getsupplierversion
	#define EXT_asm_getsupplierversion
	#define GET_asm_getsupplierversion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_asm_getsupplierversion(p0) 
	#define CHK_asm_getsupplierversion  FALSE
	#define EXP_asm_getsupplierversion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_asm_getsupplierversion
	#define EXT_asm_getsupplierversion
	#define GET_asm_getsupplierversion(fl)  CAL_CMGETAPI( "asm_getsupplierversion" ) 
	#define CAL_asm_getsupplierversion  asm_getsupplierversion
	#define CHK_asm_getsupplierversion  TRUE
	#define EXP_asm_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_getsupplierversion", (RTS_UINTPTR)asm_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xAC164AE9), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAASYNCMAN_EXTERNAL)
	#define USE_asm_getsupplierversion
	#define EXT_asm_getsupplierversion
	#define GET_asm_getsupplierversion(fl)  CAL_CMGETAPI( "asm_getsupplierversion" ) 
	#define CAL_asm_getsupplierversion  asm_getsupplierversion
	#define CHK_asm_getsupplierversion  TRUE
	#define EXP_asm_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_getsupplierversion", (RTS_UINTPTR)asm_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xAC164AE9), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAAsyncManasm_getsupplierversion
	#define EXT_CmpCAAAsyncManasm_getsupplierversion
	#define GET_CmpCAAAsyncManasm_getsupplierversion  ERR_OK
	#define CAL_CmpCAAAsyncManasm_getsupplierversion  asm_getsupplierversion
	#define CHK_CmpCAAAsyncManasm_getsupplierversion  TRUE
	#define EXP_CmpCAAAsyncManasm_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_getsupplierversion", (RTS_UINTPTR)asm_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xAC164AE9), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_asm_getsupplierversion
	#define EXT_asm_getsupplierversion
	#define GET_asm_getsupplierversion(fl)  CAL_CMGETAPI( "asm_getsupplierversion" ) 
	#define CAL_asm_getsupplierversion  asm_getsupplierversion
	#define CHK_asm_getsupplierversion  TRUE
	#define EXP_asm_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_getsupplierversion", (RTS_UINTPTR)asm_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xAC164AE9), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_asm_getsupplierversion  PFASM_GETSUPPLIERVERSION_IEC pfasm_getsupplierversion;
	#define EXT_asm_getsupplierversion  extern PFASM_GETSUPPLIERVERSION_IEC pfasm_getsupplierversion;
	#define GET_asm_getsupplierversion(fl)  s_pfCMGetAPI2( "asm_getsupplierversion", (RTS_VOID_FCTPTR *)&pfasm_getsupplierversion, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xAC164AE9), 0x03050528)
	#define CAL_asm_getsupplierversion  pfasm_getsupplierversion
	#define CHK_asm_getsupplierversion  (pfasm_getsupplierversion != NULL)
	#define EXP_asm_getsupplierversion   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asm_getsupplierversion", (RTS_UINTPTR)asm_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xAC164AE9), 0x03050528) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/



typedef struct
{
	IBase_C *pBase;
	PFASM_JOBOPENEX IASM_JobOpenEx;
 	PFASM_JOBOPEN IASM_JobOpen;
 	PFASM_JOBCLOSE IASM_JobClose;
 	PFASM_JOBEXECUTE IASM_JobExecute;
 	PFASM_JOBRESET IASM_JobReset;
 	PFASM_JOBABORT IASM_JobAbort;
 	PFASM_JOBGETPARAMS IASM_JobGetParams;
 	PFASM_JOBGETSTATE IASM_JobGetState;
 	PFASM_JOBGETID IASM_JobGetId;
 	PFASM_WORKERREGISTER IASM_WorkerRegister;
 	PFASM_WORKERREGISTER2 IASM_WorkerRegister2;
 	PFASM_WORKERUNREGISTER IASM_WorkerUnregister;
 	PFASM_JOBSETSTATE IASM_JobSetState;
 	PFASM_GETSUPPLIERVERSION IASM_GetSupplierVersion;
 	PFASM_JOBEXECQUEUE IASM_JobExecQueue;
 } ICmpCAAAsyncMan_C;

#ifdef CPLUSPLUS
class ICmpCAAAsyncMan : public IBase
{
	public:
		virtual CAA_HANDLE CDECL IASM_JobOpenEx(CAA_UDINT udiId, CAA_PVOID pParams, CAA_ERROR* peError) =0;
		virtual CAA_HANDLE CDECL IASM_JobOpen(RTS_IEC_UDINT udiId, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL IASM_JobClose(CAA_HANDLE hJob) =0;
		virtual CAA_ERROR CDECL IASM_JobExecute(CAA_HANDLE hJob) =0;
		virtual CAA_ERROR CDECL IASM_JobReset(CAA_HANDLE hJob) =0;
		virtual CAA_ERROR CDECL IASM_JobAbort(CAA_HANDLE hJob) =0;
		virtual CAA_PVOID CDECL IASM_JobGetParams(CAA_HANDLE hJob, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL IASM_JobGetState(CAA_HANDLE hJob, ASM_STATE* pstateJob) =0;
		virtual RTS_IEC_UDINT CDECL IASM_JobGetId(CAA_HANDLE hJob, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL IASM_WorkerRegister(RTS_IEC_UDINT udiId, ASM_IWORKER* pwiItf) =0;
		virtual CAA_ERROR CDECL IASM_WorkerRegister2(RTS_IEC_UDINT udiId, ASM_IWORKER2* pwiItf2) =0;
		virtual CAA_ERROR CDECL IASM_WorkerUnregister(RTS_IEC_UDINT udiId) =0;
		virtual CAA_ERROR CDECL IASM_JobSetState(CAA_HANDLE hJob, ASM_STATE stateJob) =0;
		virtual unsigned short CDECL IASM_GetSupplierVersion(CAA_BOOL xDummy) =0;
		virtual CAA_ERROR CDECL IASM_JobExecQueue(void) =0;
};
	#ifndef ITF_CmpCAAAsyncMan
		#define ITF_CmpCAAAsyncMan static ICmpCAAAsyncMan *pICmpCAAAsyncMan = NULL;
	#endif
	#define EXTITF_CmpCAAAsyncMan
#else	/*CPLUSPLUS*/
	typedef ICmpCAAAsyncMan_C		ICmpCAAAsyncMan;
	#ifndef ITF_CmpCAAAsyncMan
		#define ITF_CmpCAAAsyncMan
	#endif
	#define EXTITF_CmpCAAAsyncMan
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCAAASYNCMANITF_H_*/
