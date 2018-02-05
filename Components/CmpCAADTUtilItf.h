 /**
 * <interfacename>CAA_DTUtil_Extern</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _CMPCAADTUTILITF_H_
#define _CMPCAADTUTILITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAABehaviourModel.h"
#include "CAADTUtil.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Interface functions of CAA DTUtil*/
CAA_ERROR CDECL DTU_WorkerInit(void);
typedef CAA_ERROR (CDECL * PFDTU_WORKERINIT) (void);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_WORKERINIT_NOTIMPLEMENTED)
	#define USE_DTU_WorkerInit
	#define EXT_DTU_WorkerInit
	#define GET_DTU_WorkerInit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_DTU_WorkerInit()  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_DTU_WorkerInit  FALSE
	#define EXP_DTU_WorkerInit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_DTU_WorkerInit
	#define EXT_DTU_WorkerInit
	#define GET_DTU_WorkerInit(fl)  CAL_CMGETAPI( "DTU_WorkerInit" ) 
	#define CAL_DTU_WorkerInit  DTU_WorkerInit
	#define CHK_DTU_WorkerInit  TRUE
	#define EXP_DTU_WorkerInit  CAL_CMEXPAPI( "DTU_WorkerInit" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_DTU_WorkerInit
	#define EXT_DTU_WorkerInit
	#define GET_DTU_WorkerInit(fl)  CAL_CMGETAPI( "DTU_WorkerInit" ) 
	#define CAL_DTU_WorkerInit  DTU_WorkerInit
	#define CHK_DTU_WorkerInit  TRUE
	#define EXP_DTU_WorkerInit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_WorkerInit", (RTS_UINTPTR)DTU_WorkerInit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtilDTU_WorkerInit
	#define EXT_CmpCAADTUtilDTU_WorkerInit
	#define GET_CmpCAADTUtilDTU_WorkerInit  ERR_OK
	#define CAL_CmpCAADTUtilDTU_WorkerInit pICmpCAADTUtil->IDTU_WorkerInit
	#define CHK_CmpCAADTUtilDTU_WorkerInit (pICmpCAADTUtil != NULL)
	#define EXP_CmpCAADTUtilDTU_WorkerInit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_DTU_WorkerInit
	#define EXT_DTU_WorkerInit
	#define GET_DTU_WorkerInit(fl)  CAL_CMGETAPI( "DTU_WorkerInit" ) 
	#define CAL_DTU_WorkerInit pICmpCAADTUtil->IDTU_WorkerInit
	#define CHK_DTU_WorkerInit (pICmpCAADTUtil != NULL)
	#define EXP_DTU_WorkerInit  CAL_CMEXPAPI( "DTU_WorkerInit" ) 
#else /* DYNAMIC_LINK */
	#define USE_DTU_WorkerInit  PFDTU_WORKERINIT pfDTU_WorkerInit;
	#define EXT_DTU_WorkerInit  extern PFDTU_WORKERINIT pfDTU_WorkerInit;
	#define GET_DTU_WorkerInit(fl)  s_pfCMGetAPI2( "DTU_WorkerInit", (RTS_VOID_FCTPTR *)&pfDTU_WorkerInit, (fl), 0, 0)
	#define CAL_DTU_WorkerInit  pfDTU_WorkerInit
	#define CHK_DTU_WorkerInit  (pfDTU_WorkerInit != NULL)
	#define EXP_DTU_WorkerInit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_WorkerInit", (RTS_UINTPTR)DTU_WorkerInit, 0, 0) 
#endif



CAA_ERROR CDECL DTU_WorkerExit(void);
typedef CAA_ERROR (CDECL * PFDTU_WORKEREXIT) (void);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_WORKEREXIT_NOTIMPLEMENTED)
	#define USE_DTU_WorkerExit
	#define EXT_DTU_WorkerExit
	#define GET_DTU_WorkerExit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_DTU_WorkerExit()  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_DTU_WorkerExit  FALSE
	#define EXP_DTU_WorkerExit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_DTU_WorkerExit
	#define EXT_DTU_WorkerExit
	#define GET_DTU_WorkerExit(fl)  CAL_CMGETAPI( "DTU_WorkerExit" ) 
	#define CAL_DTU_WorkerExit  DTU_WorkerExit
	#define CHK_DTU_WorkerExit  TRUE
	#define EXP_DTU_WorkerExit  CAL_CMEXPAPI( "DTU_WorkerExit" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_DTU_WorkerExit
	#define EXT_DTU_WorkerExit
	#define GET_DTU_WorkerExit(fl)  CAL_CMGETAPI( "DTU_WorkerExit" ) 
	#define CAL_DTU_WorkerExit  DTU_WorkerExit
	#define CHK_DTU_WorkerExit  TRUE
	#define EXP_DTU_WorkerExit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_WorkerExit", (RTS_UINTPTR)DTU_WorkerExit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtilDTU_WorkerExit
	#define EXT_CmpCAADTUtilDTU_WorkerExit
	#define GET_CmpCAADTUtilDTU_WorkerExit  ERR_OK
	#define CAL_CmpCAADTUtilDTU_WorkerExit pICmpCAADTUtil->IDTU_WorkerExit
	#define CHK_CmpCAADTUtilDTU_WorkerExit (pICmpCAADTUtil != NULL)
	#define EXP_CmpCAADTUtilDTU_WorkerExit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_DTU_WorkerExit
	#define EXT_DTU_WorkerExit
	#define GET_DTU_WorkerExit(fl)  CAL_CMGETAPI( "DTU_WorkerExit" ) 
	#define CAL_DTU_WorkerExit pICmpCAADTUtil->IDTU_WorkerExit
	#define CHK_DTU_WorkerExit (pICmpCAADTUtil != NULL)
	#define EXP_DTU_WorkerExit  CAL_CMEXPAPI( "DTU_WorkerExit" ) 
#else /* DYNAMIC_LINK */
	#define USE_DTU_WorkerExit  PFDTU_WORKEREXIT pfDTU_WorkerExit;
	#define EXT_DTU_WorkerExit  extern PFDTU_WORKEREXIT pfDTU_WorkerExit;
	#define GET_DTU_WorkerExit(fl)  s_pfCMGetAPI2( "DTU_WorkerExit", (RTS_VOID_FCTPTR *)&pfDTU_WorkerExit, (fl), 0, 0)
	#define CAL_DTU_WorkerExit  pfDTU_WorkerExit
	#define CHK_DTU_WorkerExit  (pfDTU_WorkerExit != NULL)
	#define EXP_DTU_WorkerExit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_WorkerExit", (RTS_UINTPTR)DTU_WorkerExit, 0, 0) 
#endif



void CDECL DTU_GetDateAndTime(dtu_getdateandtime_typ* inst);
typedef void (CDECL * PFDTU_GETDATEANDTIME) (dtu_getdateandtime_typ* inst);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_GETDATEANDTIME_NOTIMPLEMENTED)
	#define USE_DTU_GetDateAndTime
	#define EXT_DTU_GetDateAndTime
	#define GET_DTU_GetDateAndTime(fl)  ERR_NOTIMPLEMENTED
	#define CAL_DTU_GetDateAndTime(p0)  
	#define CHK_DTU_GetDateAndTime  FALSE
	#define EXP_DTU_GetDateAndTime  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_DTU_GetDateAndTime
	#define EXT_DTU_GetDateAndTime
	#define GET_DTU_GetDateAndTime(fl)  CAL_CMGETAPI( "DTU_GetDateAndTime" ) 
	#define CAL_DTU_GetDateAndTime  DTU_GetDateAndTime
	#define CHK_DTU_GetDateAndTime  TRUE
	#define EXP_DTU_GetDateAndTime  CAL_CMEXPAPI( "DTU_GetDateAndTime" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_DTU_GetDateAndTime
	#define EXT_DTU_GetDateAndTime
	#define GET_DTU_GetDateAndTime(fl)  CAL_CMGETAPI( "DTU_GetDateAndTime" ) 
	#define CAL_DTU_GetDateAndTime  DTU_GetDateAndTime
	#define CHK_DTU_GetDateAndTime  TRUE
	#define EXP_DTU_GetDateAndTime  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_GetDateAndTime", (RTS_UINTPTR)DTU_GetDateAndTime, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtilDTU_GetDateAndTime
	#define EXT_CmpCAADTUtilDTU_GetDateAndTime
	#define GET_CmpCAADTUtilDTU_GetDateAndTime  ERR_OK
	#define CAL_CmpCAADTUtilDTU_GetDateAndTime pICmpCAADTUtil->IDTU_GetDateAndTime
	#define CHK_CmpCAADTUtilDTU_GetDateAndTime (pICmpCAADTUtil != NULL)
	#define EXP_CmpCAADTUtilDTU_GetDateAndTime  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_DTU_GetDateAndTime
	#define EXT_DTU_GetDateAndTime
	#define GET_DTU_GetDateAndTime(fl)  CAL_CMGETAPI( "DTU_GetDateAndTime" ) 
	#define CAL_DTU_GetDateAndTime pICmpCAADTUtil->IDTU_GetDateAndTime
	#define CHK_DTU_GetDateAndTime (pICmpCAADTUtil != NULL)
	#define EXP_DTU_GetDateAndTime  CAL_CMEXPAPI( "DTU_GetDateAndTime" ) 
#else /* DYNAMIC_LINK */
	#define USE_DTU_GetDateAndTime  PFDTU_GETDATEANDTIME pfDTU_GetDateAndTime;
	#define EXT_DTU_GetDateAndTime  extern PFDTU_GETDATEANDTIME pfDTU_GetDateAndTime;
	#define GET_DTU_GetDateAndTime(fl)  s_pfCMGetAPI2( "DTU_GetDateAndTime", (RTS_VOID_FCTPTR *)&pfDTU_GetDateAndTime, (fl), 0, 0)
	#define CAL_DTU_GetDateAndTime  pfDTU_GetDateAndTime
	#define CHK_DTU_GetDateAndTime  (pfDTU_GetDateAndTime != NULL)
	#define EXP_DTU_GetDateAndTime  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_GetDateAndTime", (RTS_UINTPTR)DTU_GetDateAndTime, 0, 0) 
#endif



CAA_BOOL CDECL DTU_GetDateAndTime_FB_Init(CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, dtu_getdateandtime_typ* inst);
typedef CAA_BOOL (CDECL * PFDTU_GETDATEANDTIME_FB_INIT) (CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, dtu_getdateandtime_typ* inst);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_GETDATEANDTIME_FB_INIT_NOTIMPLEMENTED)
	#define USE_DTU_GetDateAndTime_FB_Init
	#define EXT_DTU_GetDateAndTime_FB_Init
	#define GET_DTU_GetDateAndTime_FB_Init(fl)  ERR_NOTIMPLEMENTED
	#define CAL_DTU_GetDateAndTime_FB_Init(p0,p1,p2)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_DTU_GetDateAndTime_FB_Init  FALSE
	#define EXP_DTU_GetDateAndTime_FB_Init  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_DTU_GetDateAndTime_FB_Init
	#define EXT_DTU_GetDateAndTime_FB_Init
	#define GET_DTU_GetDateAndTime_FB_Init(fl)  CAL_CMGETAPI( "DTU_GetDateAndTime_FB_Init" ) 
	#define CAL_DTU_GetDateAndTime_FB_Init  DTU_GetDateAndTime_FB_Init
	#define CHK_DTU_GetDateAndTime_FB_Init  TRUE
	#define EXP_DTU_GetDateAndTime_FB_Init  CAL_CMEXPAPI( "DTU_GetDateAndTime_FB_Init" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_DTU_GetDateAndTime_FB_Init
	#define EXT_DTU_GetDateAndTime_FB_Init
	#define GET_DTU_GetDateAndTime_FB_Init(fl)  CAL_CMGETAPI( "DTU_GetDateAndTime_FB_Init" ) 
	#define CAL_DTU_GetDateAndTime_FB_Init  DTU_GetDateAndTime_FB_Init
	#define CHK_DTU_GetDateAndTime_FB_Init  TRUE
	#define EXP_DTU_GetDateAndTime_FB_Init  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_GetDateAndTime_FB_Init", (RTS_UINTPTR)DTU_GetDateAndTime_FB_Init, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtilDTU_GetDateAndTime_FB_Init
	#define EXT_CmpCAADTUtilDTU_GetDateAndTime_FB_Init
	#define GET_CmpCAADTUtilDTU_GetDateAndTime_FB_Init  ERR_OK
	#define CAL_CmpCAADTUtilDTU_GetDateAndTime_FB_Init pICmpCAADTUtil->IDTU_GetDateAndTime_FB_Init
	#define CHK_CmpCAADTUtilDTU_GetDateAndTime_FB_Init (pICmpCAADTUtil != NULL)
	#define EXP_CmpCAADTUtilDTU_GetDateAndTime_FB_Init  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_DTU_GetDateAndTime_FB_Init
	#define EXT_DTU_GetDateAndTime_FB_Init
	#define GET_DTU_GetDateAndTime_FB_Init(fl)  CAL_CMGETAPI( "DTU_GetDateAndTime_FB_Init" ) 
	#define CAL_DTU_GetDateAndTime_FB_Init pICmpCAADTUtil->IDTU_GetDateAndTime_FB_Init
	#define CHK_DTU_GetDateAndTime_FB_Init (pICmpCAADTUtil != NULL)
	#define EXP_DTU_GetDateAndTime_FB_Init  CAL_CMEXPAPI( "DTU_GetDateAndTime_FB_Init" ) 
#else /* DYNAMIC_LINK */
	#define USE_DTU_GetDateAndTime_FB_Init  PFDTU_GETDATEANDTIME_FB_INIT pfDTU_GetDateAndTime_FB_Init;
	#define EXT_DTU_GetDateAndTime_FB_Init  extern PFDTU_GETDATEANDTIME_FB_INIT pfDTU_GetDateAndTime_FB_Init;
	#define GET_DTU_GetDateAndTime_FB_Init(fl)  s_pfCMGetAPI2( "DTU_GetDateAndTime_FB_Init", (RTS_VOID_FCTPTR *)&pfDTU_GetDateAndTime_FB_Init, (fl), 0, 0)
	#define CAL_DTU_GetDateAndTime_FB_Init  pfDTU_GetDateAndTime_FB_Init
	#define CHK_DTU_GetDateAndTime_FB_Init  (pfDTU_GetDateAndTime_FB_Init != NULL)
	#define EXP_DTU_GetDateAndTime_FB_Init  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_GetDateAndTime_FB_Init", (RTS_UINTPTR)DTU_GetDateAndTime_FB_Init, 0, 0) 
#endif



CAA_BOOL CDECL DTU_GetDateAndTime_FB_Exit(CAA_BOOL bInCopyCode, dtu_getdateandtime_typ* inst);
typedef CAA_BOOL (CDECL * PFDTU_GETDATEANDTIME_FB_EXIT) (CAA_BOOL bInCopyCode, dtu_getdateandtime_typ* inst);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_GETDATEANDTIME_FB_EXIT_NOTIMPLEMENTED)
	#define USE_DTU_GetDateAndTime_FB_Exit
	#define EXT_DTU_GetDateAndTime_FB_Exit
	#define GET_DTU_GetDateAndTime_FB_Exit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_DTU_GetDateAndTime_FB_Exit(p0,p1)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_DTU_GetDateAndTime_FB_Exit  FALSE
	#define EXP_DTU_GetDateAndTime_FB_Exit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_DTU_GetDateAndTime_FB_Exit
	#define EXT_DTU_GetDateAndTime_FB_Exit
	#define GET_DTU_GetDateAndTime_FB_Exit(fl)  CAL_CMGETAPI( "DTU_GetDateAndTime_FB_Exit" ) 
	#define CAL_DTU_GetDateAndTime_FB_Exit  DTU_GetDateAndTime_FB_Exit
	#define CHK_DTU_GetDateAndTime_FB_Exit  TRUE
	#define EXP_DTU_GetDateAndTime_FB_Exit  CAL_CMEXPAPI( "DTU_GetDateAndTime_FB_Exit" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_DTU_GetDateAndTime_FB_Exit
	#define EXT_DTU_GetDateAndTime_FB_Exit
	#define GET_DTU_GetDateAndTime_FB_Exit(fl)  CAL_CMGETAPI( "DTU_GetDateAndTime_FB_Exit" ) 
	#define CAL_DTU_GetDateAndTime_FB_Exit  DTU_GetDateAndTime_FB_Exit
	#define CHK_DTU_GetDateAndTime_FB_Exit  TRUE
	#define EXP_DTU_GetDateAndTime_FB_Exit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_GetDateAndTime_FB_Exit", (RTS_UINTPTR)DTU_GetDateAndTime_FB_Exit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtilDTU_GetDateAndTime_FB_Exit
	#define EXT_CmpCAADTUtilDTU_GetDateAndTime_FB_Exit
	#define GET_CmpCAADTUtilDTU_GetDateAndTime_FB_Exit  ERR_OK
	#define CAL_CmpCAADTUtilDTU_GetDateAndTime_FB_Exit pICmpCAADTUtil->IDTU_GetDateAndTime_FB_Exit
	#define CHK_CmpCAADTUtilDTU_GetDateAndTime_FB_Exit (pICmpCAADTUtil != NULL)
	#define EXP_CmpCAADTUtilDTU_GetDateAndTime_FB_Exit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_DTU_GetDateAndTime_FB_Exit
	#define EXT_DTU_GetDateAndTime_FB_Exit
	#define GET_DTU_GetDateAndTime_FB_Exit(fl)  CAL_CMGETAPI( "DTU_GetDateAndTime_FB_Exit" ) 
	#define CAL_DTU_GetDateAndTime_FB_Exit pICmpCAADTUtil->IDTU_GetDateAndTime_FB_Exit
	#define CHK_DTU_GetDateAndTime_FB_Exit (pICmpCAADTUtil != NULL)
	#define EXP_DTU_GetDateAndTime_FB_Exit  CAL_CMEXPAPI( "DTU_GetDateAndTime_FB_Exit" ) 
#else /* DYNAMIC_LINK */
	#define USE_DTU_GetDateAndTime_FB_Exit  PFDTU_GETDATEANDTIME_FB_EXIT pfDTU_GetDateAndTime_FB_Exit;
	#define EXT_DTU_GetDateAndTime_FB_Exit  extern PFDTU_GETDATEANDTIME_FB_EXIT pfDTU_GetDateAndTime_FB_Exit;
	#define GET_DTU_GetDateAndTime_FB_Exit(fl)  s_pfCMGetAPI2( "DTU_GetDateAndTime_FB_Exit", (RTS_VOID_FCTPTR *)&pfDTU_GetDateAndTime_FB_Exit, (fl), 0, 0)
	#define CAL_DTU_GetDateAndTime_FB_Exit  pfDTU_GetDateAndTime_FB_Exit
	#define CHK_DTU_GetDateAndTime_FB_Exit  (pfDTU_GetDateAndTime_FB_Exit != NULL)
	#define EXP_DTU_GetDateAndTime_FB_Exit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_GetDateAndTime_FB_Exit", (RTS_UINTPTR)DTU_GetDateAndTime_FB_Exit, 0, 0) 
#endif



void CDECL DTU_SetDateAndTime(dtu_setdateandtime_typ* inst);
typedef void (CDECL * PFDTU_SETDATEANDTIME) (dtu_setdateandtime_typ* inst);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_SETDATEANDTIME_NOTIMPLEMENTED)
	#define USE_DTU_SetDateAndTime
	#define EXT_DTU_SetDateAndTime
	#define GET_DTU_SetDateAndTime(fl)  ERR_NOTIMPLEMENTED
	#define CAL_DTU_SetDateAndTime(p0)  
	#define CHK_DTU_SetDateAndTime  FALSE
	#define EXP_DTU_SetDateAndTime  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_DTU_SetDateAndTime
	#define EXT_DTU_SetDateAndTime
	#define GET_DTU_SetDateAndTime(fl)  CAL_CMGETAPI( "DTU_SetDateAndTime" ) 
	#define CAL_DTU_SetDateAndTime  DTU_SetDateAndTime
	#define CHK_DTU_SetDateAndTime  TRUE
	#define EXP_DTU_SetDateAndTime  CAL_CMEXPAPI( "DTU_SetDateAndTime" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_DTU_SetDateAndTime
	#define EXT_DTU_SetDateAndTime
	#define GET_DTU_SetDateAndTime(fl)  CAL_CMGETAPI( "DTU_SetDateAndTime" ) 
	#define CAL_DTU_SetDateAndTime  DTU_SetDateAndTime
	#define CHK_DTU_SetDateAndTime  TRUE
	#define EXP_DTU_SetDateAndTime  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_SetDateAndTime", (RTS_UINTPTR)DTU_SetDateAndTime, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtilDTU_SetDateAndTime
	#define EXT_CmpCAADTUtilDTU_SetDateAndTime
	#define GET_CmpCAADTUtilDTU_SetDateAndTime  ERR_OK
	#define CAL_CmpCAADTUtilDTU_SetDateAndTime pICmpCAADTUtil->IDTU_SetDateAndTime
	#define CHK_CmpCAADTUtilDTU_SetDateAndTime (pICmpCAADTUtil != NULL)
	#define EXP_CmpCAADTUtilDTU_SetDateAndTime  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_DTU_SetDateAndTime
	#define EXT_DTU_SetDateAndTime
	#define GET_DTU_SetDateAndTime(fl)  CAL_CMGETAPI( "DTU_SetDateAndTime" ) 
	#define CAL_DTU_SetDateAndTime pICmpCAADTUtil->IDTU_SetDateAndTime
	#define CHK_DTU_SetDateAndTime (pICmpCAADTUtil != NULL)
	#define EXP_DTU_SetDateAndTime  CAL_CMEXPAPI( "DTU_SetDateAndTime" ) 
#else /* DYNAMIC_LINK */
	#define USE_DTU_SetDateAndTime  PFDTU_SETDATEANDTIME pfDTU_SetDateAndTime;
	#define EXT_DTU_SetDateAndTime  extern PFDTU_SETDATEANDTIME pfDTU_SetDateAndTime;
	#define GET_DTU_SetDateAndTime(fl)  s_pfCMGetAPI2( "DTU_SetDateAndTime", (RTS_VOID_FCTPTR *)&pfDTU_SetDateAndTime, (fl), 0, 0)
	#define CAL_DTU_SetDateAndTime  pfDTU_SetDateAndTime
	#define CHK_DTU_SetDateAndTime  (pfDTU_SetDateAndTime != NULL)
	#define EXP_DTU_SetDateAndTime  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_SetDateAndTime", (RTS_UINTPTR)DTU_SetDateAndTime, 0, 0) 
#endif



CAA_BOOL CDECL DTU_SetDateAndTime_FB_Init(CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, dtu_setdateandtime_typ* inst);
typedef CAA_BOOL (CDECL * PFDTU_SETDATEANDTIME_FB_INIT) (CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, dtu_setdateandtime_typ* inst);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_SETDATEANDTIME_FB_INIT_NOTIMPLEMENTED)
	#define USE_DTU_SetDateAndTime_FB_Init
	#define EXT_DTU_SetDateAndTime_FB_Init
	#define GET_DTU_SetDateAndTime_FB_Init(fl)  ERR_NOTIMPLEMENTED
	#define CAL_DTU_SetDateAndTime_FB_Init(p0,p1,p2)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_DTU_SetDateAndTime_FB_Init  FALSE
	#define EXP_DTU_SetDateAndTime_FB_Init  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_DTU_SetDateAndTime_FB_Init
	#define EXT_DTU_SetDateAndTime_FB_Init
	#define GET_DTU_SetDateAndTime_FB_Init(fl)  CAL_CMGETAPI( "DTU_SetDateAndTime_FB_Init" ) 
	#define CAL_DTU_SetDateAndTime_FB_Init  DTU_SetDateAndTime_FB_Init
	#define CHK_DTU_SetDateAndTime_FB_Init  TRUE
	#define EXP_DTU_SetDateAndTime_FB_Init  CAL_CMEXPAPI( "DTU_SetDateAndTime_FB_Init" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_DTU_SetDateAndTime_FB_Init
	#define EXT_DTU_SetDateAndTime_FB_Init
	#define GET_DTU_SetDateAndTime_FB_Init(fl)  CAL_CMGETAPI( "DTU_SetDateAndTime_FB_Init" ) 
	#define CAL_DTU_SetDateAndTime_FB_Init  DTU_SetDateAndTime_FB_Init
	#define CHK_DTU_SetDateAndTime_FB_Init  TRUE
	#define EXP_DTU_SetDateAndTime_FB_Init  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_SetDateAndTime_FB_Init", (RTS_UINTPTR)DTU_SetDateAndTime_FB_Init, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtilDTU_SetDateAndTime_FB_Init
	#define EXT_CmpCAADTUtilDTU_SetDateAndTime_FB_Init
	#define GET_CmpCAADTUtilDTU_SetDateAndTime_FB_Init  ERR_OK
	#define CAL_CmpCAADTUtilDTU_SetDateAndTime_FB_Init pICmpCAADTUtil->IDTU_SetDateAndTime_FB_Init
	#define CHK_CmpCAADTUtilDTU_SetDateAndTime_FB_Init (pICmpCAADTUtil != NULL)
	#define EXP_CmpCAADTUtilDTU_SetDateAndTime_FB_Init  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_DTU_SetDateAndTime_FB_Init
	#define EXT_DTU_SetDateAndTime_FB_Init
	#define GET_DTU_SetDateAndTime_FB_Init(fl)  CAL_CMGETAPI( "DTU_SetDateAndTime_FB_Init" ) 
	#define CAL_DTU_SetDateAndTime_FB_Init pICmpCAADTUtil->IDTU_SetDateAndTime_FB_Init
	#define CHK_DTU_SetDateAndTime_FB_Init (pICmpCAADTUtil != NULL)
	#define EXP_DTU_SetDateAndTime_FB_Init  CAL_CMEXPAPI( "DTU_SetDateAndTime_FB_Init" ) 
#else /* DYNAMIC_LINK */
	#define USE_DTU_SetDateAndTime_FB_Init  PFDTU_SETDATEANDTIME_FB_INIT pfDTU_SetDateAndTime_FB_Init;
	#define EXT_DTU_SetDateAndTime_FB_Init  extern PFDTU_SETDATEANDTIME_FB_INIT pfDTU_SetDateAndTime_FB_Init;
	#define GET_DTU_SetDateAndTime_FB_Init(fl)  s_pfCMGetAPI2( "DTU_SetDateAndTime_FB_Init", (RTS_VOID_FCTPTR *)&pfDTU_SetDateAndTime_FB_Init, (fl), 0, 0)
	#define CAL_DTU_SetDateAndTime_FB_Init  pfDTU_SetDateAndTime_FB_Init
	#define CHK_DTU_SetDateAndTime_FB_Init  (pfDTU_SetDateAndTime_FB_Init != NULL)
	#define EXP_DTU_SetDateAndTime_FB_Init  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_SetDateAndTime_FB_Init", (RTS_UINTPTR)DTU_SetDateAndTime_FB_Init, 0, 0) 
#endif



CAA_BOOL CDECL DTU_SetDateAndTime_FB_Exit(CAA_BOOL bInCopyCode, dtu_setdateandtime_typ* inst);
typedef CAA_BOOL (CDECL * PFDTU_SETDATEANDTIME_FB_EXIT) (CAA_BOOL bInCopyCode, dtu_setdateandtime_typ* inst);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_SETDATEANDTIME_FB_EXIT_NOTIMPLEMENTED)
	#define USE_DTU_SetDateAndTime_FB_Exit
	#define EXT_DTU_SetDateAndTime_FB_Exit
	#define GET_DTU_SetDateAndTime_FB_Exit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_DTU_SetDateAndTime_FB_Exit(p0,p1)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_DTU_SetDateAndTime_FB_Exit  FALSE
	#define EXP_DTU_SetDateAndTime_FB_Exit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_DTU_SetDateAndTime_FB_Exit
	#define EXT_DTU_SetDateAndTime_FB_Exit
	#define GET_DTU_SetDateAndTime_FB_Exit(fl)  CAL_CMGETAPI( "DTU_SetDateAndTime_FB_Exit" ) 
	#define CAL_DTU_SetDateAndTime_FB_Exit  DTU_SetDateAndTime_FB_Exit
	#define CHK_DTU_SetDateAndTime_FB_Exit  TRUE
	#define EXP_DTU_SetDateAndTime_FB_Exit  CAL_CMEXPAPI( "DTU_SetDateAndTime_FB_Exit" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_DTU_SetDateAndTime_FB_Exit
	#define EXT_DTU_SetDateAndTime_FB_Exit
	#define GET_DTU_SetDateAndTime_FB_Exit(fl)  CAL_CMGETAPI( "DTU_SetDateAndTime_FB_Exit" ) 
	#define CAL_DTU_SetDateAndTime_FB_Exit  DTU_SetDateAndTime_FB_Exit
	#define CHK_DTU_SetDateAndTime_FB_Exit  TRUE
	#define EXP_DTU_SetDateAndTime_FB_Exit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_SetDateAndTime_FB_Exit", (RTS_UINTPTR)DTU_SetDateAndTime_FB_Exit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtilDTU_SetDateAndTime_FB_Exit
	#define EXT_CmpCAADTUtilDTU_SetDateAndTime_FB_Exit
	#define GET_CmpCAADTUtilDTU_SetDateAndTime_FB_Exit  ERR_OK
	#define CAL_CmpCAADTUtilDTU_SetDateAndTime_FB_Exit pICmpCAADTUtil->IDTU_SetDateAndTime_FB_Exit
	#define CHK_CmpCAADTUtilDTU_SetDateAndTime_FB_Exit (pICmpCAADTUtil != NULL)
	#define EXP_CmpCAADTUtilDTU_SetDateAndTime_FB_Exit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_DTU_SetDateAndTime_FB_Exit
	#define EXT_DTU_SetDateAndTime_FB_Exit
	#define GET_DTU_SetDateAndTime_FB_Exit(fl)  CAL_CMGETAPI( "DTU_SetDateAndTime_FB_Exit" ) 
	#define CAL_DTU_SetDateAndTime_FB_Exit pICmpCAADTUtil->IDTU_SetDateAndTime_FB_Exit
	#define CHK_DTU_SetDateAndTime_FB_Exit (pICmpCAADTUtil != NULL)
	#define EXP_DTU_SetDateAndTime_FB_Exit  CAL_CMEXPAPI( "DTU_SetDateAndTime_FB_Exit" ) 
#else /* DYNAMIC_LINK */
	#define USE_DTU_SetDateAndTime_FB_Exit  PFDTU_SETDATEANDTIME_FB_EXIT pfDTU_SetDateAndTime_FB_Exit;
	#define EXT_DTU_SetDateAndTime_FB_Exit  extern PFDTU_SETDATEANDTIME_FB_EXIT pfDTU_SetDateAndTime_FB_Exit;
	#define GET_DTU_SetDateAndTime_FB_Exit(fl)  s_pfCMGetAPI2( "DTU_SetDateAndTime_FB_Exit", (RTS_VOID_FCTPTR *)&pfDTU_SetDateAndTime_FB_Exit, (fl), 0, 0)
	#define CAL_DTU_SetDateAndTime_FB_Exit  pfDTU_SetDateAndTime_FB_Exit
	#define CHK_DTU_SetDateAndTime_FB_Exit  (pfDTU_SetDateAndTime_FB_Exit != NULL)
	#define EXP_DTU_SetDateAndTime_FB_Exit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_SetDateAndTime_FB_Exit", (RTS_UINTPTR)DTU_SetDateAndTime_FB_Exit, 0, 0) 
#endif



void CDECL DTU_GetTimeZoneInformation(dtu_gettimezoneinformation_typ* inst);
typedef void (CDECL * PFDTU_GETTIMEZONEINFORMATION) (dtu_gettimezoneinformation_typ* inst);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_GETTIMEZONEINFORMATION_NOTIMPLEMENTED)
	#define USE_DTU_GetTimeZoneInformation
	#define EXT_DTU_GetTimeZoneInformation
	#define GET_DTU_GetTimeZoneInformation(fl)  ERR_NOTIMPLEMENTED
	#define CAL_DTU_GetTimeZoneInformation(p0)  
	#define CHK_DTU_GetTimeZoneInformation  FALSE
	#define EXP_DTU_GetTimeZoneInformation  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_DTU_GetTimeZoneInformation
	#define EXT_DTU_GetTimeZoneInformation
	#define GET_DTU_GetTimeZoneInformation(fl)  CAL_CMGETAPI( "DTU_GetTimeZoneInformation" ) 
	#define CAL_DTU_GetTimeZoneInformation  DTU_GetTimeZoneInformation
	#define CHK_DTU_GetTimeZoneInformation  TRUE
	#define EXP_DTU_GetTimeZoneInformation  CAL_CMEXPAPI( "DTU_GetTimeZoneInformation" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_DTU_GetTimeZoneInformation
	#define EXT_DTU_GetTimeZoneInformation
	#define GET_DTU_GetTimeZoneInformation(fl)  CAL_CMGETAPI( "DTU_GetTimeZoneInformation" ) 
	#define CAL_DTU_GetTimeZoneInformation  DTU_GetTimeZoneInformation
	#define CHK_DTU_GetTimeZoneInformation  TRUE
	#define EXP_DTU_GetTimeZoneInformation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_GetTimeZoneInformation", (RTS_UINTPTR)DTU_GetTimeZoneInformation, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtilDTU_GetTimeZoneInformation
	#define EXT_CmpCAADTUtilDTU_GetTimeZoneInformation
	#define GET_CmpCAADTUtilDTU_GetTimeZoneInformation  ERR_OK
	#define CAL_CmpCAADTUtilDTU_GetTimeZoneInformation pICmpCAADTUtil->IDTU_GetTimeZoneInformation
	#define CHK_CmpCAADTUtilDTU_GetTimeZoneInformation (pICmpCAADTUtil != NULL)
	#define EXP_CmpCAADTUtilDTU_GetTimeZoneInformation  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_DTU_GetTimeZoneInformation
	#define EXT_DTU_GetTimeZoneInformation
	#define GET_DTU_GetTimeZoneInformation(fl)  CAL_CMGETAPI( "DTU_GetTimeZoneInformation" ) 
	#define CAL_DTU_GetTimeZoneInformation pICmpCAADTUtil->IDTU_GetTimeZoneInformation
	#define CHK_DTU_GetTimeZoneInformation (pICmpCAADTUtil != NULL)
	#define EXP_DTU_GetTimeZoneInformation  CAL_CMEXPAPI( "DTU_GetTimeZoneInformation" ) 
#else /* DYNAMIC_LINK */
	#define USE_DTU_GetTimeZoneInformation  PFDTU_GETTIMEZONEINFORMATION pfDTU_GetTimeZoneInformation;
	#define EXT_DTU_GetTimeZoneInformation  extern PFDTU_GETTIMEZONEINFORMATION pfDTU_GetTimeZoneInformation;
	#define GET_DTU_GetTimeZoneInformation(fl)  s_pfCMGetAPI2( "DTU_GetTimeZoneInformation", (RTS_VOID_FCTPTR *)&pfDTU_GetTimeZoneInformation, (fl), 0, 0)
	#define CAL_DTU_GetTimeZoneInformation  pfDTU_GetTimeZoneInformation
	#define CHK_DTU_GetTimeZoneInformation  (pfDTU_GetTimeZoneInformation != NULL)
	#define EXP_DTU_GetTimeZoneInformation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_GetTimeZoneInformation", (RTS_UINTPTR)DTU_GetTimeZoneInformation, 0, 0) 
#endif



CAA_BOOL CDECL DTU_GetTimeZoneInformation_FB_Init(CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, dtu_gettimezoneinformation_typ* inst);
typedef CAA_BOOL (CDECL * PFDTU_GETTIMEZONEINFORMATION_FB_INIT) (CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, dtu_gettimezoneinformation_typ* inst);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_GETTIMEZONEINFORMATION_FB_INIT_NOTIMPLEMENTED)
	#define USE_DTU_GetTimeZoneInformation_FB_Init
	#define EXT_DTU_GetTimeZoneInformation_FB_Init
	#define GET_DTU_GetTimeZoneInformation_FB_Init(fl)  ERR_NOTIMPLEMENTED
	#define CAL_DTU_GetTimeZoneInformation_FB_Init(p0,p1,p2)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_DTU_GetTimeZoneInformation_FB_Init  FALSE
	#define EXP_DTU_GetTimeZoneInformation_FB_Init  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_DTU_GetTimeZoneInformation_FB_Init
	#define EXT_DTU_GetTimeZoneInformation_FB_Init
	#define GET_DTU_GetTimeZoneInformation_FB_Init(fl)  CAL_CMGETAPI( "DTU_GetTimeZoneInformation_FB_Init" ) 
	#define CAL_DTU_GetTimeZoneInformation_FB_Init  DTU_GetTimeZoneInformation_FB_Init
	#define CHK_DTU_GetTimeZoneInformation_FB_Init  TRUE
	#define EXP_DTU_GetTimeZoneInformation_FB_Init  CAL_CMEXPAPI( "DTU_GetTimeZoneInformation_FB_Init" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_DTU_GetTimeZoneInformation_FB_Init
	#define EXT_DTU_GetTimeZoneInformation_FB_Init
	#define GET_DTU_GetTimeZoneInformation_FB_Init(fl)  CAL_CMGETAPI( "DTU_GetTimeZoneInformation_FB_Init" ) 
	#define CAL_DTU_GetTimeZoneInformation_FB_Init  DTU_GetTimeZoneInformation_FB_Init
	#define CHK_DTU_GetTimeZoneInformation_FB_Init  TRUE
	#define EXP_DTU_GetTimeZoneInformation_FB_Init  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_GetTimeZoneInformation_FB_Init", (RTS_UINTPTR)DTU_GetTimeZoneInformation_FB_Init, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtilDTU_GetTimeZoneInformation_FB_Init
	#define EXT_CmpCAADTUtilDTU_GetTimeZoneInformation_FB_Init
	#define GET_CmpCAADTUtilDTU_GetTimeZoneInformation_FB_Init  ERR_OK
	#define CAL_CmpCAADTUtilDTU_GetTimeZoneInformation_FB_Init pICmpCAADTUtil->IDTU_GetTimeZoneInformation_FB_Init
	#define CHK_CmpCAADTUtilDTU_GetTimeZoneInformation_FB_Init (pICmpCAADTUtil != NULL)
	#define EXP_CmpCAADTUtilDTU_GetTimeZoneInformation_FB_Init  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_DTU_GetTimeZoneInformation_FB_Init
	#define EXT_DTU_GetTimeZoneInformation_FB_Init
	#define GET_DTU_GetTimeZoneInformation_FB_Init(fl)  CAL_CMGETAPI( "DTU_GetTimeZoneInformation_FB_Init" ) 
	#define CAL_DTU_GetTimeZoneInformation_FB_Init pICmpCAADTUtil->IDTU_GetTimeZoneInformation_FB_Init
	#define CHK_DTU_GetTimeZoneInformation_FB_Init (pICmpCAADTUtil != NULL)
	#define EXP_DTU_GetTimeZoneInformation_FB_Init  CAL_CMEXPAPI( "DTU_GetTimeZoneInformation_FB_Init" ) 
#else /* DYNAMIC_LINK */
	#define USE_DTU_GetTimeZoneInformation_FB_Init  PFDTU_GETTIMEZONEINFORMATION_FB_INIT pfDTU_GetTimeZoneInformation_FB_Init;
	#define EXT_DTU_GetTimeZoneInformation_FB_Init  extern PFDTU_GETTIMEZONEINFORMATION_FB_INIT pfDTU_GetTimeZoneInformation_FB_Init;
	#define GET_DTU_GetTimeZoneInformation_FB_Init(fl)  s_pfCMGetAPI2( "DTU_GetTimeZoneInformation_FB_Init", (RTS_VOID_FCTPTR *)&pfDTU_GetTimeZoneInformation_FB_Init, (fl), 0, 0)
	#define CAL_DTU_GetTimeZoneInformation_FB_Init  pfDTU_GetTimeZoneInformation_FB_Init
	#define CHK_DTU_GetTimeZoneInformation_FB_Init  (pfDTU_GetTimeZoneInformation_FB_Init != NULL)
	#define EXP_DTU_GetTimeZoneInformation_FB_Init  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_GetTimeZoneInformation_FB_Init", (RTS_UINTPTR)DTU_GetTimeZoneInformation_FB_Init, 0, 0) 
#endif



CAA_BOOL CDECL DTU_GetTimeZoneInformation_FB_Exit(CAA_BOOL bInCopyCode, dtu_gettimezoneinformation_typ* inst);
typedef CAA_BOOL (CDECL * PFDTU_GETTIMEZONEINFORMATION_FB_EXIT) (CAA_BOOL bInCopyCode, dtu_gettimezoneinformation_typ* inst);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_GETTIMEZONEINFORMATION_FB_EXIT_NOTIMPLEMENTED)
	#define USE_DTU_GetTimeZoneInformation_FB_Exit
	#define EXT_DTU_GetTimeZoneInformation_FB_Exit
	#define GET_DTU_GetTimeZoneInformation_FB_Exit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_DTU_GetTimeZoneInformation_FB_Exit(p0,p1)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_DTU_GetTimeZoneInformation_FB_Exit  FALSE
	#define EXP_DTU_GetTimeZoneInformation_FB_Exit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_DTU_GetTimeZoneInformation_FB_Exit
	#define EXT_DTU_GetTimeZoneInformation_FB_Exit
	#define GET_DTU_GetTimeZoneInformation_FB_Exit(fl)  CAL_CMGETAPI( "DTU_GetTimeZoneInformation_FB_Exit" ) 
	#define CAL_DTU_GetTimeZoneInformation_FB_Exit  DTU_GetTimeZoneInformation_FB_Exit
	#define CHK_DTU_GetTimeZoneInformation_FB_Exit  TRUE
	#define EXP_DTU_GetTimeZoneInformation_FB_Exit  CAL_CMEXPAPI( "DTU_GetTimeZoneInformation_FB_Exit" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_DTU_GetTimeZoneInformation_FB_Exit
	#define EXT_DTU_GetTimeZoneInformation_FB_Exit
	#define GET_DTU_GetTimeZoneInformation_FB_Exit(fl)  CAL_CMGETAPI( "DTU_GetTimeZoneInformation_FB_Exit" ) 
	#define CAL_DTU_GetTimeZoneInformation_FB_Exit  DTU_GetTimeZoneInformation_FB_Exit
	#define CHK_DTU_GetTimeZoneInformation_FB_Exit  TRUE
	#define EXP_DTU_GetTimeZoneInformation_FB_Exit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_GetTimeZoneInformation_FB_Exit", (RTS_UINTPTR)DTU_GetTimeZoneInformation_FB_Exit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtilDTU_GetTimeZoneInformation_FB_Exit
	#define EXT_CmpCAADTUtilDTU_GetTimeZoneInformation_FB_Exit
	#define GET_CmpCAADTUtilDTU_GetTimeZoneInformation_FB_Exit  ERR_OK
	#define CAL_CmpCAADTUtilDTU_GetTimeZoneInformation_FB_Exit pICmpCAADTUtil->IDTU_GetTimeZoneInformation_FB_Exit
	#define CHK_CmpCAADTUtilDTU_GetTimeZoneInformation_FB_Exit (pICmpCAADTUtil != NULL)
	#define EXP_CmpCAADTUtilDTU_GetTimeZoneInformation_FB_Exit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_DTU_GetTimeZoneInformation_FB_Exit
	#define EXT_DTU_GetTimeZoneInformation_FB_Exit
	#define GET_DTU_GetTimeZoneInformation_FB_Exit(fl)  CAL_CMGETAPI( "DTU_GetTimeZoneInformation_FB_Exit" ) 
	#define CAL_DTU_GetTimeZoneInformation_FB_Exit pICmpCAADTUtil->IDTU_GetTimeZoneInformation_FB_Exit
	#define CHK_DTU_GetTimeZoneInformation_FB_Exit (pICmpCAADTUtil != NULL)
	#define EXP_DTU_GetTimeZoneInformation_FB_Exit  CAL_CMEXPAPI( "DTU_GetTimeZoneInformation_FB_Exit" ) 
#else /* DYNAMIC_LINK */
	#define USE_DTU_GetTimeZoneInformation_FB_Exit  PFDTU_GETTIMEZONEINFORMATION_FB_EXIT pfDTU_GetTimeZoneInformation_FB_Exit;
	#define EXT_DTU_GetTimeZoneInformation_FB_Exit  extern PFDTU_GETTIMEZONEINFORMATION_FB_EXIT pfDTU_GetTimeZoneInformation_FB_Exit;
	#define GET_DTU_GetTimeZoneInformation_FB_Exit(fl)  s_pfCMGetAPI2( "DTU_GetTimeZoneInformation_FB_Exit", (RTS_VOID_FCTPTR *)&pfDTU_GetTimeZoneInformation_FB_Exit, (fl), 0, 0)
	#define CAL_DTU_GetTimeZoneInformation_FB_Exit  pfDTU_GetTimeZoneInformation_FB_Exit
	#define CHK_DTU_GetTimeZoneInformation_FB_Exit  (pfDTU_GetTimeZoneInformation_FB_Exit != NULL)
	#define EXP_DTU_GetTimeZoneInformation_FB_Exit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_GetTimeZoneInformation_FB_Exit", (RTS_UINTPTR)DTU_GetTimeZoneInformation_FB_Exit, 0, 0) 
#endif



void CDECL DTU_SetTimeZoneInformation(dtu_settimezoneinformation_typ* inst);
typedef void (CDECL * PFDTU_SETTIMEZONEINFORMATION) (dtu_settimezoneinformation_typ* inst);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_SETTIMEZONEINFORMATION_NOTIMPLEMENTED)
	#define USE_DTU_SetTimeZoneInformation
	#define EXT_DTU_SetTimeZoneInformation
	#define GET_DTU_SetTimeZoneInformation(fl)  ERR_NOTIMPLEMENTED
	#define CAL_DTU_SetTimeZoneInformation(p0)  
	#define CHK_DTU_SetTimeZoneInformation  FALSE
	#define EXP_DTU_SetTimeZoneInformation  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_DTU_SetTimeZoneInformation
	#define EXT_DTU_SetTimeZoneInformation
	#define GET_DTU_SetTimeZoneInformation(fl)  CAL_CMGETAPI( "DTU_SetTimeZoneInformation" ) 
	#define CAL_DTU_SetTimeZoneInformation  DTU_SetTimeZoneInformation
	#define CHK_DTU_SetTimeZoneInformation  TRUE
	#define EXP_DTU_SetTimeZoneInformation  CAL_CMEXPAPI( "DTU_SetTimeZoneInformation" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_DTU_SetTimeZoneInformation
	#define EXT_DTU_SetTimeZoneInformation
	#define GET_DTU_SetTimeZoneInformation(fl)  CAL_CMGETAPI( "DTU_SetTimeZoneInformation" ) 
	#define CAL_DTU_SetTimeZoneInformation  DTU_SetTimeZoneInformation
	#define CHK_DTU_SetTimeZoneInformation  TRUE
	#define EXP_DTU_SetTimeZoneInformation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_SetTimeZoneInformation", (RTS_UINTPTR)DTU_SetTimeZoneInformation, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtilDTU_SetTimeZoneInformation
	#define EXT_CmpCAADTUtilDTU_SetTimeZoneInformation
	#define GET_CmpCAADTUtilDTU_SetTimeZoneInformation  ERR_OK
	#define CAL_CmpCAADTUtilDTU_SetTimeZoneInformation pICmpCAADTUtil->IDTU_SetTimeZoneInformation
	#define CHK_CmpCAADTUtilDTU_SetTimeZoneInformation (pICmpCAADTUtil != NULL)
	#define EXP_CmpCAADTUtilDTU_SetTimeZoneInformation  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_DTU_SetTimeZoneInformation
	#define EXT_DTU_SetTimeZoneInformation
	#define GET_DTU_SetTimeZoneInformation(fl)  CAL_CMGETAPI( "DTU_SetTimeZoneInformation" ) 
	#define CAL_DTU_SetTimeZoneInformation pICmpCAADTUtil->IDTU_SetTimeZoneInformation
	#define CHK_DTU_SetTimeZoneInformation (pICmpCAADTUtil != NULL)
	#define EXP_DTU_SetTimeZoneInformation  CAL_CMEXPAPI( "DTU_SetTimeZoneInformation" ) 
#else /* DYNAMIC_LINK */
	#define USE_DTU_SetTimeZoneInformation  PFDTU_SETTIMEZONEINFORMATION pfDTU_SetTimeZoneInformation;
	#define EXT_DTU_SetTimeZoneInformation  extern PFDTU_SETTIMEZONEINFORMATION pfDTU_SetTimeZoneInformation;
	#define GET_DTU_SetTimeZoneInformation(fl)  s_pfCMGetAPI2( "DTU_SetTimeZoneInformation", (RTS_VOID_FCTPTR *)&pfDTU_SetTimeZoneInformation, (fl), 0, 0)
	#define CAL_DTU_SetTimeZoneInformation  pfDTU_SetTimeZoneInformation
	#define CHK_DTU_SetTimeZoneInformation  (pfDTU_SetTimeZoneInformation != NULL)
	#define EXP_DTU_SetTimeZoneInformation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_SetTimeZoneInformation", (RTS_UINTPTR)DTU_SetTimeZoneInformation, 0, 0) 
#endif



CAA_BOOL CDECL DTU_SetTimeZoneInformation_FB_Init(CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, dtu_settimezoneinformation_typ* inst);
typedef CAA_BOOL (CDECL * PFDTU_SETTIMEZONEINFORMATION_FB_INIT) (CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, dtu_settimezoneinformation_typ* inst);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_SETTIMEZONEINFORMATION_FB_INIT_NOTIMPLEMENTED)
	#define USE_DTU_SetTimeZoneInformation_FB_Init
	#define EXT_DTU_SetTimeZoneInformation_FB_Init
	#define GET_DTU_SetTimeZoneInformation_FB_Init(fl)  ERR_NOTIMPLEMENTED
	#define CAL_DTU_SetTimeZoneInformation_FB_Init(p0,p1,p2)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_DTU_SetTimeZoneInformation_FB_Init  FALSE
	#define EXP_DTU_SetTimeZoneInformation_FB_Init  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_DTU_SetTimeZoneInformation_FB_Init
	#define EXT_DTU_SetTimeZoneInformation_FB_Init
	#define GET_DTU_SetTimeZoneInformation_FB_Init(fl)  CAL_CMGETAPI( "DTU_SetTimeZoneInformation_FB_Init" ) 
	#define CAL_DTU_SetTimeZoneInformation_FB_Init  DTU_SetTimeZoneInformation_FB_Init
	#define CHK_DTU_SetTimeZoneInformation_FB_Init  TRUE
	#define EXP_DTU_SetTimeZoneInformation_FB_Init  CAL_CMEXPAPI( "DTU_SetTimeZoneInformation_FB_Init" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_DTU_SetTimeZoneInformation_FB_Init
	#define EXT_DTU_SetTimeZoneInformation_FB_Init
	#define GET_DTU_SetTimeZoneInformation_FB_Init(fl)  CAL_CMGETAPI( "DTU_SetTimeZoneInformation_FB_Init" ) 
	#define CAL_DTU_SetTimeZoneInformation_FB_Init  DTU_SetTimeZoneInformation_FB_Init
	#define CHK_DTU_SetTimeZoneInformation_FB_Init  TRUE
	#define EXP_DTU_SetTimeZoneInformation_FB_Init  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_SetTimeZoneInformation_FB_Init", (RTS_UINTPTR)DTU_SetTimeZoneInformation_FB_Init, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtilDTU_SetTimeZoneInformation_FB_Init
	#define EXT_CmpCAADTUtilDTU_SetTimeZoneInformation_FB_Init
	#define GET_CmpCAADTUtilDTU_SetTimeZoneInformation_FB_Init  ERR_OK
	#define CAL_CmpCAADTUtilDTU_SetTimeZoneInformation_FB_Init pICmpCAADTUtil->IDTU_SetTimeZoneInformation_FB_Init
	#define CHK_CmpCAADTUtilDTU_SetTimeZoneInformation_FB_Init (pICmpCAADTUtil != NULL)
	#define EXP_CmpCAADTUtilDTU_SetTimeZoneInformation_FB_Init  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_DTU_SetTimeZoneInformation_FB_Init
	#define EXT_DTU_SetTimeZoneInformation_FB_Init
	#define GET_DTU_SetTimeZoneInformation_FB_Init(fl)  CAL_CMGETAPI( "DTU_SetTimeZoneInformation_FB_Init" ) 
	#define CAL_DTU_SetTimeZoneInformation_FB_Init pICmpCAADTUtil->IDTU_SetTimeZoneInformation_FB_Init
	#define CHK_DTU_SetTimeZoneInformation_FB_Init (pICmpCAADTUtil != NULL)
	#define EXP_DTU_SetTimeZoneInformation_FB_Init  CAL_CMEXPAPI( "DTU_SetTimeZoneInformation_FB_Init" ) 
#else /* DYNAMIC_LINK */
	#define USE_DTU_SetTimeZoneInformation_FB_Init  PFDTU_SETTIMEZONEINFORMATION_FB_INIT pfDTU_SetTimeZoneInformation_FB_Init;
	#define EXT_DTU_SetTimeZoneInformation_FB_Init  extern PFDTU_SETTIMEZONEINFORMATION_FB_INIT pfDTU_SetTimeZoneInformation_FB_Init;
	#define GET_DTU_SetTimeZoneInformation_FB_Init(fl)  s_pfCMGetAPI2( "DTU_SetTimeZoneInformation_FB_Init", (RTS_VOID_FCTPTR *)&pfDTU_SetTimeZoneInformation_FB_Init, (fl), 0, 0)
	#define CAL_DTU_SetTimeZoneInformation_FB_Init  pfDTU_SetTimeZoneInformation_FB_Init
	#define CHK_DTU_SetTimeZoneInformation_FB_Init  (pfDTU_SetTimeZoneInformation_FB_Init != NULL)
	#define EXP_DTU_SetTimeZoneInformation_FB_Init  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_SetTimeZoneInformation_FB_Init", (RTS_UINTPTR)DTU_SetTimeZoneInformation_FB_Init, 0, 0) 
#endif



CAA_BOOL CDECL DTU_SetTimeZoneInformation_FB_Exit(CAA_BOOL bInCopyCode, dtu_settimezoneinformation_typ* inst);
typedef CAA_BOOL (CDECL * PFDTU_SETTIMEZONEINFORMATION_FB_EXIT) (CAA_BOOL bInCopyCode, dtu_settimezoneinformation_typ* inst);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_SETTIMEZONEINFORMATION_FB_EXIT_NOTIMPLEMENTED)
	#define USE_DTU_SetTimeZoneInformation_FB_Exit
	#define EXT_DTU_SetTimeZoneInformation_FB_Exit
	#define GET_DTU_SetTimeZoneInformation_FB_Exit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_DTU_SetTimeZoneInformation_FB_Exit(p0,p1)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_DTU_SetTimeZoneInformation_FB_Exit  FALSE
	#define EXP_DTU_SetTimeZoneInformation_FB_Exit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_DTU_SetTimeZoneInformation_FB_Exit
	#define EXT_DTU_SetTimeZoneInformation_FB_Exit
	#define GET_DTU_SetTimeZoneInformation_FB_Exit(fl)  CAL_CMGETAPI( "DTU_SetTimeZoneInformation_FB_Exit" ) 
	#define CAL_DTU_SetTimeZoneInformation_FB_Exit  DTU_SetTimeZoneInformation_FB_Exit
	#define CHK_DTU_SetTimeZoneInformation_FB_Exit  TRUE
	#define EXP_DTU_SetTimeZoneInformation_FB_Exit  CAL_CMEXPAPI( "DTU_SetTimeZoneInformation_FB_Exit" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_DTU_SetTimeZoneInformation_FB_Exit
	#define EXT_DTU_SetTimeZoneInformation_FB_Exit
	#define GET_DTU_SetTimeZoneInformation_FB_Exit(fl)  CAL_CMGETAPI( "DTU_SetTimeZoneInformation_FB_Exit" ) 
	#define CAL_DTU_SetTimeZoneInformation_FB_Exit  DTU_SetTimeZoneInformation_FB_Exit
	#define CHK_DTU_SetTimeZoneInformation_FB_Exit  TRUE
	#define EXP_DTU_SetTimeZoneInformation_FB_Exit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_SetTimeZoneInformation_FB_Exit", (RTS_UINTPTR)DTU_SetTimeZoneInformation_FB_Exit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtilDTU_SetTimeZoneInformation_FB_Exit
	#define EXT_CmpCAADTUtilDTU_SetTimeZoneInformation_FB_Exit
	#define GET_CmpCAADTUtilDTU_SetTimeZoneInformation_FB_Exit  ERR_OK
	#define CAL_CmpCAADTUtilDTU_SetTimeZoneInformation_FB_Exit pICmpCAADTUtil->IDTU_SetTimeZoneInformation_FB_Exit
	#define CHK_CmpCAADTUtilDTU_SetTimeZoneInformation_FB_Exit (pICmpCAADTUtil != NULL)
	#define EXP_CmpCAADTUtilDTU_SetTimeZoneInformation_FB_Exit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_DTU_SetTimeZoneInformation_FB_Exit
	#define EXT_DTU_SetTimeZoneInformation_FB_Exit
	#define GET_DTU_SetTimeZoneInformation_FB_Exit(fl)  CAL_CMGETAPI( "DTU_SetTimeZoneInformation_FB_Exit" ) 
	#define CAL_DTU_SetTimeZoneInformation_FB_Exit pICmpCAADTUtil->IDTU_SetTimeZoneInformation_FB_Exit
	#define CHK_DTU_SetTimeZoneInformation_FB_Exit (pICmpCAADTUtil != NULL)
	#define EXP_DTU_SetTimeZoneInformation_FB_Exit  CAL_CMEXPAPI( "DTU_SetTimeZoneInformation_FB_Exit" ) 
#else /* DYNAMIC_LINK */
	#define USE_DTU_SetTimeZoneInformation_FB_Exit  PFDTU_SETTIMEZONEINFORMATION_FB_EXIT pfDTU_SetTimeZoneInformation_FB_Exit;
	#define EXT_DTU_SetTimeZoneInformation_FB_Exit  extern PFDTU_SETTIMEZONEINFORMATION_FB_EXIT pfDTU_SetTimeZoneInformation_FB_Exit;
	#define GET_DTU_SetTimeZoneInformation_FB_Exit(fl)  s_pfCMGetAPI2( "DTU_SetTimeZoneInformation_FB_Exit", (RTS_VOID_FCTPTR *)&pfDTU_SetTimeZoneInformation_FB_Exit, (fl), 0, 0)
	#define CAL_DTU_SetTimeZoneInformation_FB_Exit  pfDTU_SetTimeZoneInformation_FB_Exit
	#define CHK_DTU_SetTimeZoneInformation_FB_Exit  (pfDTU_SetTimeZoneInformation_FB_Exit != NULL)
	#define EXP_DTU_SetTimeZoneInformation_FB_Exit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_SetTimeZoneInformation_FB_Exit", (RTS_UINTPTR)DTU_SetTimeZoneInformation_FB_Exit, 0, 0) 
#endif



unsigned long CDECL DTU_DateConcat(unsigned short usYear, unsigned short usMonth, unsigned short usDay, CAA_ERROR* peError);
typedef unsigned long (CDECL * PFDTU_DATECONCAT) (unsigned short usYear, unsigned short usMonth, unsigned short usDay, CAA_ERROR* peError);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_DATECONCAT_NOTIMPLEMENTED)
	#define USE_DTU_DateConcat
	#define EXT_DTU_DateConcat
	#define GET_DTU_DateConcat(fl)  ERR_NOTIMPLEMENTED
	#define CAL_DTU_DateConcat(p0,p1,p2,p3)  (unsigned long)ERR_NOTIMPLEMENTED
	#define CHK_DTU_DateConcat  FALSE
	#define EXP_DTU_DateConcat  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_DTU_DateConcat
	#define EXT_DTU_DateConcat
	#define GET_DTU_DateConcat(fl)  CAL_CMGETAPI( "DTU_DateConcat" ) 
	#define CAL_DTU_DateConcat  DTU_DateConcat
	#define CHK_DTU_DateConcat  TRUE
	#define EXP_DTU_DateConcat  CAL_CMEXPAPI( "DTU_DateConcat" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_DTU_DateConcat
	#define EXT_DTU_DateConcat
	#define GET_DTU_DateConcat(fl)  CAL_CMGETAPI( "DTU_DateConcat" ) 
	#define CAL_DTU_DateConcat  DTU_DateConcat
	#define CHK_DTU_DateConcat  TRUE
	#define EXP_DTU_DateConcat  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_DateConcat", (RTS_UINTPTR)DTU_DateConcat, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtilDTU_DateConcat
	#define EXT_CmpCAADTUtilDTU_DateConcat
	#define GET_CmpCAADTUtilDTU_DateConcat  ERR_OK
	#define CAL_CmpCAADTUtilDTU_DateConcat pICmpCAADTUtil->IDTU_DateConcat
	#define CHK_CmpCAADTUtilDTU_DateConcat (pICmpCAADTUtil != NULL)
	#define EXP_CmpCAADTUtilDTU_DateConcat  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_DTU_DateConcat
	#define EXT_DTU_DateConcat
	#define GET_DTU_DateConcat(fl)  CAL_CMGETAPI( "DTU_DateConcat" ) 
	#define CAL_DTU_DateConcat pICmpCAADTUtil->IDTU_DateConcat
	#define CHK_DTU_DateConcat (pICmpCAADTUtil != NULL)
	#define EXP_DTU_DateConcat  CAL_CMEXPAPI( "DTU_DateConcat" ) 
#else /* DYNAMIC_LINK */
	#define USE_DTU_DateConcat  PFDTU_DATECONCAT pfDTU_DateConcat;
	#define EXT_DTU_DateConcat  extern PFDTU_DATECONCAT pfDTU_DateConcat;
	#define GET_DTU_DateConcat(fl)  s_pfCMGetAPI2( "DTU_DateConcat", (RTS_VOID_FCTPTR *)&pfDTU_DateConcat, (fl), 0, 0)
	#define CAL_DTU_DateConcat  pfDTU_DateConcat
	#define CHK_DTU_DateConcat  (pfDTU_DateConcat != NULL)
	#define EXP_DTU_DateConcat  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_DateConcat", (RTS_UINTPTR)DTU_DateConcat, 0, 0) 
#endif



CAA_ERROR CDECL DTU_DateSplit(unsigned long ulDate, unsigned short* pusYear, unsigned short* pusMonth, unsigned short* pusDay);
typedef CAA_ERROR (CDECL * PFDTU_DATESPLIT) (unsigned long ulDate, unsigned short* pusYear, unsigned short* pusMonth, unsigned short* pusDay);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_DATESPLIT_NOTIMPLEMENTED)
	#define USE_DTU_DateSplit
	#define EXT_DTU_DateSplit
	#define GET_DTU_DateSplit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_DTU_DateSplit(p0,p1,p2,p3)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_DTU_DateSplit  FALSE
	#define EXP_DTU_DateSplit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_DTU_DateSplit
	#define EXT_DTU_DateSplit
	#define GET_DTU_DateSplit(fl)  CAL_CMGETAPI( "DTU_DateSplit" ) 
	#define CAL_DTU_DateSplit  DTU_DateSplit
	#define CHK_DTU_DateSplit  TRUE
	#define EXP_DTU_DateSplit  CAL_CMEXPAPI( "DTU_DateSplit" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_DTU_DateSplit
	#define EXT_DTU_DateSplit
	#define GET_DTU_DateSplit(fl)  CAL_CMGETAPI( "DTU_DateSplit" ) 
	#define CAL_DTU_DateSplit  DTU_DateSplit
	#define CHK_DTU_DateSplit  TRUE
	#define EXP_DTU_DateSplit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_DateSplit", (RTS_UINTPTR)DTU_DateSplit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtilDTU_DateSplit
	#define EXT_CmpCAADTUtilDTU_DateSplit
	#define GET_CmpCAADTUtilDTU_DateSplit  ERR_OK
	#define CAL_CmpCAADTUtilDTU_DateSplit pICmpCAADTUtil->IDTU_DateSplit
	#define CHK_CmpCAADTUtilDTU_DateSplit (pICmpCAADTUtil != NULL)
	#define EXP_CmpCAADTUtilDTU_DateSplit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_DTU_DateSplit
	#define EXT_DTU_DateSplit
	#define GET_DTU_DateSplit(fl)  CAL_CMGETAPI( "DTU_DateSplit" ) 
	#define CAL_DTU_DateSplit pICmpCAADTUtil->IDTU_DateSplit
	#define CHK_DTU_DateSplit (pICmpCAADTUtil != NULL)
	#define EXP_DTU_DateSplit  CAL_CMEXPAPI( "DTU_DateSplit" ) 
#else /* DYNAMIC_LINK */
	#define USE_DTU_DateSplit  PFDTU_DATESPLIT pfDTU_DateSplit;
	#define EXT_DTU_DateSplit  extern PFDTU_DATESPLIT pfDTU_DateSplit;
	#define GET_DTU_DateSplit(fl)  s_pfCMGetAPI2( "DTU_DateSplit", (RTS_VOID_FCTPTR *)&pfDTU_DateSplit, (fl), 0, 0)
	#define CAL_DTU_DateSplit  pfDTU_DateSplit
	#define CHK_DTU_DateSplit  (pfDTU_DateSplit != NULL)
	#define EXP_DTU_DateSplit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_DateSplit", (RTS_UINTPTR)DTU_DateSplit, 0, 0) 
#endif



unsigned long CDECL DTU_DTConcat(unsigned short usYear, unsigned short usMonth, unsigned short usDay, unsigned short usHour, unsigned short usMinute, unsigned short usSecond, CAA_ERROR* peError);
typedef unsigned long (CDECL * PFDTU_DTCONCAT) (unsigned short usYear, unsigned short usMonth, unsigned short usDay, unsigned short usHour, unsigned short usMinute, unsigned short usSecond, CAA_ERROR* peError);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_DTCONCAT_NOTIMPLEMENTED)
	#define USE_DTU_DTConcat
	#define EXT_DTU_DTConcat
	#define GET_DTU_DTConcat(fl)  ERR_NOTIMPLEMENTED
	#define CAL_DTU_DTConcat(p0,p1,p2,p3,p4,p5,p6)  (unsigned long)ERR_NOTIMPLEMENTED
	#define CHK_DTU_DTConcat  FALSE
	#define EXP_DTU_DTConcat  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_DTU_DTConcat
	#define EXT_DTU_DTConcat
	#define GET_DTU_DTConcat(fl)  CAL_CMGETAPI( "DTU_DTConcat" ) 
	#define CAL_DTU_DTConcat  DTU_DTConcat
	#define CHK_DTU_DTConcat  TRUE
	#define EXP_DTU_DTConcat  CAL_CMEXPAPI( "DTU_DTConcat" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_DTU_DTConcat
	#define EXT_DTU_DTConcat
	#define GET_DTU_DTConcat(fl)  CAL_CMGETAPI( "DTU_DTConcat" ) 
	#define CAL_DTU_DTConcat  DTU_DTConcat
	#define CHK_DTU_DTConcat  TRUE
	#define EXP_DTU_DTConcat  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_DTConcat", (RTS_UINTPTR)DTU_DTConcat, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtilDTU_DTConcat
	#define EXT_CmpCAADTUtilDTU_DTConcat
	#define GET_CmpCAADTUtilDTU_DTConcat  ERR_OK
	#define CAL_CmpCAADTUtilDTU_DTConcat pICmpCAADTUtil->IDTU_DTConcat
	#define CHK_CmpCAADTUtilDTU_DTConcat (pICmpCAADTUtil != NULL)
	#define EXP_CmpCAADTUtilDTU_DTConcat  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_DTU_DTConcat
	#define EXT_DTU_DTConcat
	#define GET_DTU_DTConcat(fl)  CAL_CMGETAPI( "DTU_DTConcat" ) 
	#define CAL_DTU_DTConcat pICmpCAADTUtil->IDTU_DTConcat
	#define CHK_DTU_DTConcat (pICmpCAADTUtil != NULL)
	#define EXP_DTU_DTConcat  CAL_CMEXPAPI( "DTU_DTConcat" ) 
#else /* DYNAMIC_LINK */
	#define USE_DTU_DTConcat  PFDTU_DTCONCAT pfDTU_DTConcat;
	#define EXT_DTU_DTConcat  extern PFDTU_DTCONCAT pfDTU_DTConcat;
	#define GET_DTU_DTConcat(fl)  s_pfCMGetAPI2( "DTU_DTConcat", (RTS_VOID_FCTPTR *)&pfDTU_DTConcat, (fl), 0, 0)
	#define CAL_DTU_DTConcat  pfDTU_DTConcat
	#define CHK_DTU_DTConcat  (pfDTU_DTConcat != NULL)
	#define EXP_DTU_DTConcat  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_DTConcat", (RTS_UINTPTR)DTU_DTConcat, 0, 0) 
#endif



CAA_ERROR CDECL DTU_DTSplit(unsigned long ulDateAndTime, unsigned short* pusYear, unsigned short* pusMonth, unsigned short* pusDay, unsigned short* pusHour, unsigned short* pusMinute, unsigned short* pusSecond);
typedef CAA_ERROR (CDECL * PFDTU_DTSPLIT) (unsigned long ulDateAndTime, unsigned short* pusYear, unsigned short* pusMonth, unsigned short* pusDay, unsigned short* pusHour, unsigned short* pusMinute, unsigned short* pusSecond);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_DTSPLIT_NOTIMPLEMENTED)
	#define USE_DTU_DTSplit
	#define EXT_DTU_DTSplit
	#define GET_DTU_DTSplit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_DTU_DTSplit(p0,p1,p2,p3,p4,p5,p6)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_DTU_DTSplit  FALSE
	#define EXP_DTU_DTSplit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_DTU_DTSplit
	#define EXT_DTU_DTSplit
	#define GET_DTU_DTSplit(fl)  CAL_CMGETAPI( "DTU_DTSplit" ) 
	#define CAL_DTU_DTSplit  DTU_DTSplit
	#define CHK_DTU_DTSplit  TRUE
	#define EXP_DTU_DTSplit  CAL_CMEXPAPI( "DTU_DTSplit" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_DTU_DTSplit
	#define EXT_DTU_DTSplit
	#define GET_DTU_DTSplit(fl)  CAL_CMGETAPI( "DTU_DTSplit" ) 
	#define CAL_DTU_DTSplit  DTU_DTSplit
	#define CHK_DTU_DTSplit  TRUE
	#define EXP_DTU_DTSplit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_DTSplit", (RTS_UINTPTR)DTU_DTSplit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtilDTU_DTSplit
	#define EXT_CmpCAADTUtilDTU_DTSplit
	#define GET_CmpCAADTUtilDTU_DTSplit  ERR_OK
	#define CAL_CmpCAADTUtilDTU_DTSplit pICmpCAADTUtil->IDTU_DTSplit
	#define CHK_CmpCAADTUtilDTU_DTSplit (pICmpCAADTUtil != NULL)
	#define EXP_CmpCAADTUtilDTU_DTSplit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_DTU_DTSplit
	#define EXT_DTU_DTSplit
	#define GET_DTU_DTSplit(fl)  CAL_CMGETAPI( "DTU_DTSplit" ) 
	#define CAL_DTU_DTSplit pICmpCAADTUtil->IDTU_DTSplit
	#define CHK_DTU_DTSplit (pICmpCAADTUtil != NULL)
	#define EXP_DTU_DTSplit  CAL_CMEXPAPI( "DTU_DTSplit" ) 
#else /* DYNAMIC_LINK */
	#define USE_DTU_DTSplit  PFDTU_DTSPLIT pfDTU_DTSplit;
	#define EXT_DTU_DTSplit  extern PFDTU_DTSPLIT pfDTU_DTSplit;
	#define GET_DTU_DTSplit(fl)  s_pfCMGetAPI2( "DTU_DTSplit", (RTS_VOID_FCTPTR *)&pfDTU_DTSplit, (fl), 0, 0)
	#define CAL_DTU_DTSplit  pfDTU_DTSplit
	#define CHK_DTU_DTSplit  (pfDTU_DTSplit != NULL)
	#define EXP_DTU_DTSplit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_DTSplit", (RTS_UINTPTR)DTU_DTSplit, 0, 0) 
#endif



unsigned long CDECL DTU_TODConcat(unsigned short usHour, unsigned short usMinute, unsigned short usSecond, unsigned short usMillisecond, CAA_ERROR* peError);
typedef unsigned long (CDECL * PFDTU_TODCONCAT) (unsigned short usHour, unsigned short usMinute, unsigned short usSecond, unsigned short usMillisecond, CAA_ERROR* peError);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_TODCONCAT_NOTIMPLEMENTED)
	#define USE_DTU_TODConcat
	#define EXT_DTU_TODConcat
	#define GET_DTU_TODConcat(fl)  ERR_NOTIMPLEMENTED
	#define CAL_DTU_TODConcat(p0,p1,p2,p3,p4)  (unsigned long)ERR_NOTIMPLEMENTED
	#define CHK_DTU_TODConcat  FALSE
	#define EXP_DTU_TODConcat  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_DTU_TODConcat
	#define EXT_DTU_TODConcat
	#define GET_DTU_TODConcat(fl)  CAL_CMGETAPI( "DTU_TODConcat" ) 
	#define CAL_DTU_TODConcat  DTU_TODConcat
	#define CHK_DTU_TODConcat  TRUE
	#define EXP_DTU_TODConcat  CAL_CMEXPAPI( "DTU_TODConcat" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_DTU_TODConcat
	#define EXT_DTU_TODConcat
	#define GET_DTU_TODConcat(fl)  CAL_CMGETAPI( "DTU_TODConcat" ) 
	#define CAL_DTU_TODConcat  DTU_TODConcat
	#define CHK_DTU_TODConcat  TRUE
	#define EXP_DTU_TODConcat  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_TODConcat", (RTS_UINTPTR)DTU_TODConcat, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtilDTU_TODConcat
	#define EXT_CmpCAADTUtilDTU_TODConcat
	#define GET_CmpCAADTUtilDTU_TODConcat  ERR_OK
	#define CAL_CmpCAADTUtilDTU_TODConcat pICmpCAADTUtil->IDTU_TODConcat
	#define CHK_CmpCAADTUtilDTU_TODConcat (pICmpCAADTUtil != NULL)
	#define EXP_CmpCAADTUtilDTU_TODConcat  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_DTU_TODConcat
	#define EXT_DTU_TODConcat
	#define GET_DTU_TODConcat(fl)  CAL_CMGETAPI( "DTU_TODConcat" ) 
	#define CAL_DTU_TODConcat pICmpCAADTUtil->IDTU_TODConcat
	#define CHK_DTU_TODConcat (pICmpCAADTUtil != NULL)
	#define EXP_DTU_TODConcat  CAL_CMEXPAPI( "DTU_TODConcat" ) 
#else /* DYNAMIC_LINK */
	#define USE_DTU_TODConcat  PFDTU_TODCONCAT pfDTU_TODConcat;
	#define EXT_DTU_TODConcat  extern PFDTU_TODCONCAT pfDTU_TODConcat;
	#define GET_DTU_TODConcat(fl)  s_pfCMGetAPI2( "DTU_TODConcat", (RTS_VOID_FCTPTR *)&pfDTU_TODConcat, (fl), 0, 0)
	#define CAL_DTU_TODConcat  pfDTU_TODConcat
	#define CHK_DTU_TODConcat  (pfDTU_TODConcat != NULL)
	#define EXP_DTU_TODConcat  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_TODConcat", (RTS_UINTPTR)DTU_TODConcat, 0, 0) 
#endif



CAA_ERROR CDECL DTU_TODSplit(unsigned long ulTime, unsigned short* pusHour, unsigned short* pusMinute, unsigned short* pusSecond, unsigned short* pusMillisecond);
typedef CAA_ERROR (CDECL * PFDTU_TODSPLIT) (unsigned long ulTime, unsigned short* pusHour, unsigned short* pusMinute, unsigned short* pusSecond, unsigned short* pusMillisecond);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_TODSPLIT_NOTIMPLEMENTED)
	#define USE_DTU_TODSplit
	#define EXT_DTU_TODSplit
	#define GET_DTU_TODSplit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_DTU_TODSplit(p0,p1,p2,p3,p4)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_DTU_TODSplit  FALSE
	#define EXP_DTU_TODSplit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_DTU_TODSplit
	#define EXT_DTU_TODSplit
	#define GET_DTU_TODSplit(fl)  CAL_CMGETAPI( "DTU_TODSplit" ) 
	#define CAL_DTU_TODSplit  DTU_TODSplit
	#define CHK_DTU_TODSplit  TRUE
	#define EXP_DTU_TODSplit  CAL_CMEXPAPI( "DTU_TODSplit" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_DTU_TODSplit
	#define EXT_DTU_TODSplit
	#define GET_DTU_TODSplit(fl)  CAL_CMGETAPI( "DTU_TODSplit" ) 
	#define CAL_DTU_TODSplit  DTU_TODSplit
	#define CHK_DTU_TODSplit  TRUE
	#define EXP_DTU_TODSplit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_TODSplit", (RTS_UINTPTR)DTU_TODSplit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtilDTU_TODSplit
	#define EXT_CmpCAADTUtilDTU_TODSplit
	#define GET_CmpCAADTUtilDTU_TODSplit  ERR_OK
	#define CAL_CmpCAADTUtilDTU_TODSplit pICmpCAADTUtil->IDTU_TODSplit
	#define CHK_CmpCAADTUtilDTU_TODSplit (pICmpCAADTUtil != NULL)
	#define EXP_CmpCAADTUtilDTU_TODSplit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_DTU_TODSplit
	#define EXT_DTU_TODSplit
	#define GET_DTU_TODSplit(fl)  CAL_CMGETAPI( "DTU_TODSplit" ) 
	#define CAL_DTU_TODSplit pICmpCAADTUtil->IDTU_TODSplit
	#define CHK_DTU_TODSplit (pICmpCAADTUtil != NULL)
	#define EXP_DTU_TODSplit  CAL_CMEXPAPI( "DTU_TODSplit" ) 
#else /* DYNAMIC_LINK */
	#define USE_DTU_TODSplit  PFDTU_TODSPLIT pfDTU_TODSplit;
	#define EXT_DTU_TODSplit  extern PFDTU_TODSPLIT pfDTU_TODSplit;
	#define GET_DTU_TODSplit(fl)  s_pfCMGetAPI2( "DTU_TODSplit", (RTS_VOID_FCTPTR *)&pfDTU_TODSplit, (fl), 0, 0)
	#define CAL_DTU_TODSplit  pfDTU_TODSplit
	#define CHK_DTU_TODSplit  (pfDTU_TODSplit != NULL)
	#define EXP_DTU_TODSplit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_TODSplit", (RTS_UINTPTR)DTU_TODSplit, 0, 0) 
#endif



CAA_ENUM CDECL DTU_GetDayOfWeek(unsigned long ulDate, CAA_ERROR* peError);
typedef CAA_ENUM (CDECL * PFDTU_GETDAYOFWEEK) (unsigned long ulDate, CAA_ERROR* peError);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_GETDAYOFWEEK_NOTIMPLEMENTED)
	#define USE_DTU_GetDayOfWeek
	#define EXT_DTU_GetDayOfWeek
	#define GET_DTU_GetDayOfWeek(fl)  ERR_NOTIMPLEMENTED
	#define CAL_DTU_GetDayOfWeek(p0,p1)  (CAA_ENUM)ERR_NOTIMPLEMENTED
	#define CHK_DTU_GetDayOfWeek  FALSE
	#define EXP_DTU_GetDayOfWeek  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_DTU_GetDayOfWeek
	#define EXT_DTU_GetDayOfWeek
	#define GET_DTU_GetDayOfWeek(fl)  CAL_CMGETAPI( "DTU_GetDayOfWeek" ) 
	#define CAL_DTU_GetDayOfWeek  DTU_GetDayOfWeek
	#define CHK_DTU_GetDayOfWeek  TRUE
	#define EXP_DTU_GetDayOfWeek  CAL_CMEXPAPI( "DTU_GetDayOfWeek" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_DTU_GetDayOfWeek
	#define EXT_DTU_GetDayOfWeek
	#define GET_DTU_GetDayOfWeek(fl)  CAL_CMGETAPI( "DTU_GetDayOfWeek" ) 
	#define CAL_DTU_GetDayOfWeek  DTU_GetDayOfWeek
	#define CHK_DTU_GetDayOfWeek  TRUE
	#define EXP_DTU_GetDayOfWeek  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_GetDayOfWeek", (RTS_UINTPTR)DTU_GetDayOfWeek, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtilDTU_GetDayOfWeek
	#define EXT_CmpCAADTUtilDTU_GetDayOfWeek
	#define GET_CmpCAADTUtilDTU_GetDayOfWeek  ERR_OK
	#define CAL_CmpCAADTUtilDTU_GetDayOfWeek pICmpCAADTUtil->IDTU_GetDayOfWeek
	#define CHK_CmpCAADTUtilDTU_GetDayOfWeek (pICmpCAADTUtil != NULL)
	#define EXP_CmpCAADTUtilDTU_GetDayOfWeek  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_DTU_GetDayOfWeek
	#define EXT_DTU_GetDayOfWeek
	#define GET_DTU_GetDayOfWeek(fl)  CAL_CMGETAPI( "DTU_GetDayOfWeek" ) 
	#define CAL_DTU_GetDayOfWeek pICmpCAADTUtil->IDTU_GetDayOfWeek
	#define CHK_DTU_GetDayOfWeek (pICmpCAADTUtil != NULL)
	#define EXP_DTU_GetDayOfWeek  CAL_CMEXPAPI( "DTU_GetDayOfWeek" ) 
#else /* DYNAMIC_LINK */
	#define USE_DTU_GetDayOfWeek  PFDTU_GETDAYOFWEEK pfDTU_GetDayOfWeek;
	#define EXT_DTU_GetDayOfWeek  extern PFDTU_GETDAYOFWEEK pfDTU_GetDayOfWeek;
	#define GET_DTU_GetDayOfWeek(fl)  s_pfCMGetAPI2( "DTU_GetDayOfWeek", (RTS_VOID_FCTPTR *)&pfDTU_GetDayOfWeek, (fl), 0, 0)
	#define CAL_DTU_GetDayOfWeek  pfDTU_GetDayOfWeek
	#define CHK_DTU_GetDayOfWeek  (pfDTU_GetDayOfWeek != NULL)
	#define EXP_DTU_GetDayOfWeek  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_GetDayOfWeek", (RTS_UINTPTR)DTU_GetDayOfWeek, 0, 0) 
#endif



unsigned short CDECL DTU_GetSupplierVersion(CAA_BOOL xDummy);
typedef unsigned short (CDECL * PFDTU_GETSUPPLIERVERSION) (CAA_BOOL xDummy);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_GETSUPPLIERVERSION_NOTIMPLEMENTED)
	#define USE_DTU_GetSupplierVersion
	#define EXT_DTU_GetSupplierVersion
	#define GET_DTU_GetSupplierVersion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_DTU_GetSupplierVersion(p0)  (unsigned short)ERR_NOTIMPLEMENTED
	#define CHK_DTU_GetSupplierVersion  FALSE
	#define EXP_DTU_GetSupplierVersion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_DTU_GetSupplierVersion
	#define EXT_DTU_GetSupplierVersion
	#define GET_DTU_GetSupplierVersion(fl)  CAL_CMGETAPI( "DTU_GetSupplierVersion" ) 
	#define CAL_DTU_GetSupplierVersion  DTU_GetSupplierVersion
	#define CHK_DTU_GetSupplierVersion  TRUE
	#define EXP_DTU_GetSupplierVersion  CAL_CMEXPAPI( "DTU_GetSupplierVersion" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_DTU_GetSupplierVersion
	#define EXT_DTU_GetSupplierVersion
	#define GET_DTU_GetSupplierVersion(fl)  CAL_CMGETAPI( "DTU_GetSupplierVersion" ) 
	#define CAL_DTU_GetSupplierVersion  DTU_GetSupplierVersion
	#define CHK_DTU_GetSupplierVersion  TRUE
	#define EXP_DTU_GetSupplierVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_GetSupplierVersion", (RTS_UINTPTR)DTU_GetSupplierVersion, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtilDTU_GetSupplierVersion
	#define EXT_CmpCAADTUtilDTU_GetSupplierVersion
	#define GET_CmpCAADTUtilDTU_GetSupplierVersion  ERR_OK
	#define CAL_CmpCAADTUtilDTU_GetSupplierVersion pICmpCAADTUtil->IDTU_GetSupplierVersion
	#define CHK_CmpCAADTUtilDTU_GetSupplierVersion (pICmpCAADTUtil != NULL)
	#define EXP_CmpCAADTUtilDTU_GetSupplierVersion  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_DTU_GetSupplierVersion
	#define EXT_DTU_GetSupplierVersion
	#define GET_DTU_GetSupplierVersion(fl)  CAL_CMGETAPI( "DTU_GetSupplierVersion" ) 
	#define CAL_DTU_GetSupplierVersion pICmpCAADTUtil->IDTU_GetSupplierVersion
	#define CHK_DTU_GetSupplierVersion (pICmpCAADTUtil != NULL)
	#define EXP_DTU_GetSupplierVersion  CAL_CMEXPAPI( "DTU_GetSupplierVersion" ) 
#else /* DYNAMIC_LINK */
	#define USE_DTU_GetSupplierVersion  PFDTU_GETSUPPLIERVERSION pfDTU_GetSupplierVersion;
	#define EXT_DTU_GetSupplierVersion  extern PFDTU_GETSUPPLIERVERSION pfDTU_GetSupplierVersion;
	#define GET_DTU_GetSupplierVersion(fl)  s_pfCMGetAPI2( "DTU_GetSupplierVersion", (RTS_VOID_FCTPTR *)&pfDTU_GetSupplierVersion, (fl), 0, 0)
	#define CAL_DTU_GetSupplierVersion  pfDTU_GetSupplierVersion
	#define CHK_DTU_GetSupplierVersion  (pfDTU_GetSupplierVersion != NULL)
	#define EXP_DTU_GetSupplierVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"DTU_GetSupplierVersion", (RTS_UINTPTR)DTU_GetSupplierVersion, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>DTU_GETDATEANDTIME_PARAMS</description>
 */
typedef struct tagDTU_GETDATEANDTIME_PARAMS
{
	RTS_IEC_DATE_AND_TIME dtDateAndTime;
	CAA_ENUM eTimezone;
} DTU_GETDATEANDTIME_PARAMS;

/**
 * <description>DTU_SETDATEANDTIME_PARAMS</description>
 */
typedef struct tagDTU_SETDATEANDTIME_PARAMS
{
	RTS_IEC_DATE_AND_TIME dtDateAndTime;
} DTU_SETDATEANDTIME_PARAMS;

/**
 * <description>DTU_GETTIMEZONEINFORMATION_PARAMS</description>
 */
typedef struct tagDTU_GETTIMEZONEINFORMATION_PARAMS
{
	RTCLK_TIME_ZONE_INFO tziTimezone;
} DTU_GETTIMEZONEINFORMATION_PARAMS;

/**
 * <description>DTU_SETTIMEZONEINFORMATION_PARAMS</description>
 */
typedef struct tagDTU_SETTIMEZONEINFORMATION_PARAMS
{
	RTCLK_TIME_ZONE_INFO tziTimezone;
} DTU_SETTIMEZONEINFORMATION_PARAMS;

/**
 * <description>dtu_dateconcat</description>
 */
typedef struct tagdtu_dateconcat_struct
{
	RTS_IEC_UINT uiYear;				/* VAR_INPUT */	/* 1970 .. 2099 */
	RTS_IEC_UINT uiMonth;				/* VAR_INPUT */	/* 1 .. 12 */
	RTS_IEC_UINT uiDay;					/* VAR_INPUT */	/* 1 .. 31 */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	RTS_IEC_DATE DTU_DateConcat;		/* VAR_OUTPUT */	/* datDate */
} dtu_dateconcat_struct;

void CDECL CDECL_EXT dtu_dateconcat(dtu_dateconcat_struct *p);
typedef void (CDECL CDECL_EXT* PFDTU_DATECONCAT_IEC) (dtu_dateconcat_struct *p);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_DATECONCAT_NOTIMPLEMENTED)
	#define USE_dtu_dateconcat
	#define EXT_dtu_dateconcat
	#define GET_dtu_dateconcat(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dtu_dateconcat(p0) 
	#define CHK_dtu_dateconcat  FALSE
	#define EXP_dtu_dateconcat  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dtu_dateconcat
	#define EXT_dtu_dateconcat
	#define GET_dtu_dateconcat(fl)  CAL_CMGETAPI( "dtu_dateconcat" ) 
	#define CAL_dtu_dateconcat  dtu_dateconcat
	#define CHK_dtu_dateconcat  TRUE
	#define EXP_dtu_dateconcat  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_dateconcat", (RTS_UINTPTR)dtu_dateconcat, 1, RTSITF_GET_SIGNATURE(0, 0x85BEB2FF), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_dtu_dateconcat
	#define EXT_dtu_dateconcat
	#define GET_dtu_dateconcat(fl)  CAL_CMGETAPI( "dtu_dateconcat" ) 
	#define CAL_dtu_dateconcat  dtu_dateconcat
	#define CHK_dtu_dateconcat  TRUE
	#define EXP_dtu_dateconcat  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_dateconcat", (RTS_UINTPTR)dtu_dateconcat, 1, RTSITF_GET_SIGNATURE(0, 0x85BEB2FF), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtildtu_dateconcat
	#define EXT_CmpCAADTUtildtu_dateconcat
	#define GET_CmpCAADTUtildtu_dateconcat  ERR_OK
	#define CAL_CmpCAADTUtildtu_dateconcat  dtu_dateconcat
	#define CHK_CmpCAADTUtildtu_dateconcat  TRUE
	#define EXP_CmpCAADTUtildtu_dateconcat  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_dateconcat", (RTS_UINTPTR)dtu_dateconcat, 1, RTSITF_GET_SIGNATURE(0, 0x85BEB2FF), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_dtu_dateconcat
	#define EXT_dtu_dateconcat
	#define GET_dtu_dateconcat(fl)  CAL_CMGETAPI( "dtu_dateconcat" ) 
	#define CAL_dtu_dateconcat  dtu_dateconcat
	#define CHK_dtu_dateconcat  TRUE
	#define EXP_dtu_dateconcat  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_dateconcat", (RTS_UINTPTR)dtu_dateconcat, 1, RTSITF_GET_SIGNATURE(0, 0x85BEB2FF), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_dtu_dateconcat  PFDTU_DATECONCAT_IEC pfdtu_dateconcat;
	#define EXT_dtu_dateconcat  extern PFDTU_DATECONCAT_IEC pfdtu_dateconcat;
	#define GET_dtu_dateconcat(fl)  s_pfCMGetAPI2( "dtu_dateconcat", (RTS_VOID_FCTPTR *)&pfdtu_dateconcat, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x85BEB2FF), 0x03050500)
	#define CAL_dtu_dateconcat  pfdtu_dateconcat
	#define CHK_dtu_dateconcat  (pfdtu_dateconcat != NULL)
	#define EXP_dtu_dateconcat   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_dateconcat", (RTS_UINTPTR)dtu_dateconcat, 1, RTSITF_GET_SIGNATURE(0, 0x85BEB2FF), 0x03050500) 
#endif


/**
 * <description>dtu_datesplit</description>
 */
typedef struct tagdtu_datesplit_struct
{
	RTS_IEC_DATE datDate;				/* VAR_INPUT */	
	RTS_IEC_UINT *puiYear;				/* VAR_INPUT */	/* 1970 .. 2099 */
	RTS_IEC_UINT *puiMonth;				/* VAR_INPUT */	/* 1 .. 12 */
	RTS_IEC_UINT *puiDay;				/* VAR_INPUT */	/* 1 .. 31 */
	CAA_ERROR DTU_DateSplit;			/* VAR_OUTPUT */	
} dtu_datesplit_struct;

void CDECL CDECL_EXT dtu_datesplit(dtu_datesplit_struct *p);
typedef void (CDECL CDECL_EXT* PFDTU_DATESPLIT_IEC) (dtu_datesplit_struct *p);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_DATESPLIT_NOTIMPLEMENTED)
	#define USE_dtu_datesplit
	#define EXT_dtu_datesplit
	#define GET_dtu_datesplit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dtu_datesplit(p0) 
	#define CHK_dtu_datesplit  FALSE
	#define EXP_dtu_datesplit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dtu_datesplit
	#define EXT_dtu_datesplit
	#define GET_dtu_datesplit(fl)  CAL_CMGETAPI( "dtu_datesplit" ) 
	#define CAL_dtu_datesplit  dtu_datesplit
	#define CHK_dtu_datesplit  TRUE
	#define EXP_dtu_datesplit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_datesplit", (RTS_UINTPTR)dtu_datesplit, 1, RTSITF_GET_SIGNATURE(0, 0x4977970B), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_dtu_datesplit
	#define EXT_dtu_datesplit
	#define GET_dtu_datesplit(fl)  CAL_CMGETAPI( "dtu_datesplit" ) 
	#define CAL_dtu_datesplit  dtu_datesplit
	#define CHK_dtu_datesplit  TRUE
	#define EXP_dtu_datesplit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_datesplit", (RTS_UINTPTR)dtu_datesplit, 1, RTSITF_GET_SIGNATURE(0, 0x4977970B), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtildtu_datesplit
	#define EXT_CmpCAADTUtildtu_datesplit
	#define GET_CmpCAADTUtildtu_datesplit  ERR_OK
	#define CAL_CmpCAADTUtildtu_datesplit  dtu_datesplit
	#define CHK_CmpCAADTUtildtu_datesplit  TRUE
	#define EXP_CmpCAADTUtildtu_datesplit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_datesplit", (RTS_UINTPTR)dtu_datesplit, 1, RTSITF_GET_SIGNATURE(0, 0x4977970B), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_dtu_datesplit
	#define EXT_dtu_datesplit
	#define GET_dtu_datesplit(fl)  CAL_CMGETAPI( "dtu_datesplit" ) 
	#define CAL_dtu_datesplit  dtu_datesplit
	#define CHK_dtu_datesplit  TRUE
	#define EXP_dtu_datesplit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_datesplit", (RTS_UINTPTR)dtu_datesplit, 1, RTSITF_GET_SIGNATURE(0, 0x4977970B), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_dtu_datesplit  PFDTU_DATESPLIT_IEC pfdtu_datesplit;
	#define EXT_dtu_datesplit  extern PFDTU_DATESPLIT_IEC pfdtu_datesplit;
	#define GET_dtu_datesplit(fl)  s_pfCMGetAPI2( "dtu_datesplit", (RTS_VOID_FCTPTR *)&pfdtu_datesplit, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x4977970B), 0x03050500)
	#define CAL_dtu_datesplit  pfdtu_datesplit
	#define CHK_dtu_datesplit  (pfdtu_datesplit != NULL)
	#define EXP_dtu_datesplit   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_datesplit", (RTS_UINTPTR)dtu_datesplit, 1, RTSITF_GET_SIGNATURE(0, 0x4977970B), 0x03050500) 
#endif


/**
 * <description>dtu_dtconcat</description>
 */
typedef struct tagdtu_dtconcat_struct
{
	RTS_IEC_UINT uiYear;				/* VAR_INPUT */	/* 1970 .. 2099 */
	RTS_IEC_UINT uiMonth;				/* VAR_INPUT */	/* 1 .. 12 */
	RTS_IEC_UINT uiDay;					/* VAR_INPUT */	/* 1 .. 31 */
	RTS_IEC_UINT uiHour;				/* VAR_INPUT */	/* 0 .. 23 */
	RTS_IEC_UINT uiMinute;				/* VAR_INPUT */	/* 0 .. 59 */
	RTS_IEC_UINT uiSecond;				/* VAR_INPUT */	/* 0 .. 59 */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	RTS_IEC_DATE_AND_TIME DTU_DTConcat;	/* VAR_OUTPUT */	
} dtu_dtconcat_struct;

void CDECL CDECL_EXT dtu_dtconcat(dtu_dtconcat_struct *p);
typedef void (CDECL CDECL_EXT* PFDTU_DTCONCAT_IEC) (dtu_dtconcat_struct *p);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_DTCONCAT_NOTIMPLEMENTED)
	#define USE_dtu_dtconcat
	#define EXT_dtu_dtconcat
	#define GET_dtu_dtconcat(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dtu_dtconcat(p0) 
	#define CHK_dtu_dtconcat  FALSE
	#define EXP_dtu_dtconcat  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dtu_dtconcat
	#define EXT_dtu_dtconcat
	#define GET_dtu_dtconcat(fl)  CAL_CMGETAPI( "dtu_dtconcat" ) 
	#define CAL_dtu_dtconcat  dtu_dtconcat
	#define CHK_dtu_dtconcat  TRUE
	#define EXP_dtu_dtconcat  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_dtconcat", (RTS_UINTPTR)dtu_dtconcat, 1, RTSITF_GET_SIGNATURE(0, 0xEB362791), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_dtu_dtconcat
	#define EXT_dtu_dtconcat
	#define GET_dtu_dtconcat(fl)  CAL_CMGETAPI( "dtu_dtconcat" ) 
	#define CAL_dtu_dtconcat  dtu_dtconcat
	#define CHK_dtu_dtconcat  TRUE
	#define EXP_dtu_dtconcat  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_dtconcat", (RTS_UINTPTR)dtu_dtconcat, 1, RTSITF_GET_SIGNATURE(0, 0xEB362791), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtildtu_dtconcat
	#define EXT_CmpCAADTUtildtu_dtconcat
	#define GET_CmpCAADTUtildtu_dtconcat  ERR_OK
	#define CAL_CmpCAADTUtildtu_dtconcat  dtu_dtconcat
	#define CHK_CmpCAADTUtildtu_dtconcat  TRUE
	#define EXP_CmpCAADTUtildtu_dtconcat  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_dtconcat", (RTS_UINTPTR)dtu_dtconcat, 1, RTSITF_GET_SIGNATURE(0, 0xEB362791), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_dtu_dtconcat
	#define EXT_dtu_dtconcat
	#define GET_dtu_dtconcat(fl)  CAL_CMGETAPI( "dtu_dtconcat" ) 
	#define CAL_dtu_dtconcat  dtu_dtconcat
	#define CHK_dtu_dtconcat  TRUE
	#define EXP_dtu_dtconcat  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_dtconcat", (RTS_UINTPTR)dtu_dtconcat, 1, RTSITF_GET_SIGNATURE(0, 0xEB362791), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_dtu_dtconcat  PFDTU_DTCONCAT_IEC pfdtu_dtconcat;
	#define EXT_dtu_dtconcat  extern PFDTU_DTCONCAT_IEC pfdtu_dtconcat;
	#define GET_dtu_dtconcat(fl)  s_pfCMGetAPI2( "dtu_dtconcat", (RTS_VOID_FCTPTR *)&pfdtu_dtconcat, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xEB362791), 0x03050500)
	#define CAL_dtu_dtconcat  pfdtu_dtconcat
	#define CHK_dtu_dtconcat  (pfdtu_dtconcat != NULL)
	#define EXP_dtu_dtconcat   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_dtconcat", (RTS_UINTPTR)dtu_dtconcat, 1, RTSITF_GET_SIGNATURE(0, 0xEB362791), 0x03050500) 
#endif


/**
 * <description>dtu_dtsplit</description>
 */
typedef struct tagdtu_dtsplit_struct
{
	RTS_IEC_DATE_AND_TIME dtDateAndTime;	/* VAR_INPUT */	
	RTS_IEC_UINT *puiYear;				/* VAR_INPUT */	/* 1970 .. 2099 */
	RTS_IEC_UINT *puiMonth;				/* VAR_INPUT */	/* 1 .. 12 */
	RTS_IEC_UINT *puiDay;				/* VAR_INPUT */	/* 1 .. 31 */
	RTS_IEC_UINT *puiHour;				/* VAR_INPUT */	/* 0 .. 23 */
	RTS_IEC_UINT *puiMinute;			/* VAR_INPUT */	/* 0 .. 59 */
	RTS_IEC_UINT *puiSecond;			/* VAR_INPUT */	/* 0 .. 59 */
	CAA_ERROR DTU_DTSplit;				/* VAR_OUTPUT */	
} dtu_dtsplit_struct;

void CDECL CDECL_EXT dtu_dtsplit(dtu_dtsplit_struct *p);
typedef void (CDECL CDECL_EXT* PFDTU_DTSPLIT_IEC) (dtu_dtsplit_struct *p);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_DTSPLIT_NOTIMPLEMENTED)
	#define USE_dtu_dtsplit
	#define EXT_dtu_dtsplit
	#define GET_dtu_dtsplit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dtu_dtsplit(p0) 
	#define CHK_dtu_dtsplit  FALSE
	#define EXP_dtu_dtsplit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dtu_dtsplit
	#define EXT_dtu_dtsplit
	#define GET_dtu_dtsplit(fl)  CAL_CMGETAPI( "dtu_dtsplit" ) 
	#define CAL_dtu_dtsplit  dtu_dtsplit
	#define CHK_dtu_dtsplit  TRUE
	#define EXP_dtu_dtsplit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_dtsplit", (RTS_UINTPTR)dtu_dtsplit, 1, RTSITF_GET_SIGNATURE(0, 0xEECCB7E8), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_dtu_dtsplit
	#define EXT_dtu_dtsplit
	#define GET_dtu_dtsplit(fl)  CAL_CMGETAPI( "dtu_dtsplit" ) 
	#define CAL_dtu_dtsplit  dtu_dtsplit
	#define CHK_dtu_dtsplit  TRUE
	#define EXP_dtu_dtsplit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_dtsplit", (RTS_UINTPTR)dtu_dtsplit, 1, RTSITF_GET_SIGNATURE(0, 0xEECCB7E8), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtildtu_dtsplit
	#define EXT_CmpCAADTUtildtu_dtsplit
	#define GET_CmpCAADTUtildtu_dtsplit  ERR_OK
	#define CAL_CmpCAADTUtildtu_dtsplit  dtu_dtsplit
	#define CHK_CmpCAADTUtildtu_dtsplit  TRUE
	#define EXP_CmpCAADTUtildtu_dtsplit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_dtsplit", (RTS_UINTPTR)dtu_dtsplit, 1, RTSITF_GET_SIGNATURE(0, 0xEECCB7E8), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_dtu_dtsplit
	#define EXT_dtu_dtsplit
	#define GET_dtu_dtsplit(fl)  CAL_CMGETAPI( "dtu_dtsplit" ) 
	#define CAL_dtu_dtsplit  dtu_dtsplit
	#define CHK_dtu_dtsplit  TRUE
	#define EXP_dtu_dtsplit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_dtsplit", (RTS_UINTPTR)dtu_dtsplit, 1, RTSITF_GET_SIGNATURE(0, 0xEECCB7E8), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_dtu_dtsplit  PFDTU_DTSPLIT_IEC pfdtu_dtsplit;
	#define EXT_dtu_dtsplit  extern PFDTU_DTSPLIT_IEC pfdtu_dtsplit;
	#define GET_dtu_dtsplit(fl)  s_pfCMGetAPI2( "dtu_dtsplit", (RTS_VOID_FCTPTR *)&pfdtu_dtsplit, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xEECCB7E8), 0x03050500)
	#define CAL_dtu_dtsplit  pfdtu_dtsplit
	#define CHK_dtu_dtsplit  (pfdtu_dtsplit != NULL)
	#define EXP_dtu_dtsplit   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_dtsplit", (RTS_UINTPTR)dtu_dtsplit, 1, RTSITF_GET_SIGNATURE(0, 0xEECCB7E8), 0x03050500) 
#endif


/**
 * <description>dtu_getdateandtime__main</description>
 */
typedef struct tagdtu_getdateandtime_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	CAA_BOOL xExecute;					/* VAR_INPUT */	/* Rising edge: Action start
							Falling edge: Resets outputs
							If a falling edge occurs before the function block has completed its action, the outputs operate
							in the usual manner and are only reset if either the action is completed or
							in the event of an error. In this case, the corresponding output values (xDone, xError, iError)
							are present at the outputs for exactly one cycle. */
	CAA_BOOL xDone;						/* VAR_OUTPUT */	/* Action successfully completed */
	CAA_BOOL xBusy;						/* VAR_OUTPUT */	/* Function block active */
	CAA_BOOL xError;					/* VAR_OUTPUT */	/* TRUE: error occurred, function block aborts action
							FALSE: no error */
	CAA_ERROR eError;					/* VAR_OUTPUT */	
	RTS_IEC_DATE_AND_TIME dtDateAndTime;	/* VAR_OUTPUT */	
	CAA_ENUM ePeriode;					/* VAR_OUTPUT */	
	CAA_BOOL xPreviousExecute;			/* Local variable */	/* value of xExecute in previous cycle */
	CAA_BOOL xPreviousAbortInProgress;	/* Local variable */	/* value of xAbortInPrograss in previous cycle */
	CAA_BOOL xAbortInProgress;			/* Local variable */	/* TRUE: abort is processed
											FALSE: abort is done */
	RTS_IEC_INT iError;					/* Local variable */	/* Local library error ID is transfered to eError by the concrete implementation */
	CAA_HANDLE hJob;					/* Local variable */	/* specific vars */
	DTU_GETDATEANDTIME_PARAMS *pGetDateAndTimeParams;	/* Local variable */	
	ASM_STATE StateJob;					/* Local variable */	
	RTS_IEC_XWORD dwEtrigClass;			/* Local variable */	
} dtu_getdateandtime_struct;

/**
 * <description>dtu_getdateandtime_fb_init</description>
 */
typedef struct tagdtu_getdateandtime_fb_init_struct
{
	dtu_getdateandtime_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInitRetains;				/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Init;					/* VAR_OUTPUT */	
} dtu_getdateandtime_fb_init_struct;

void CDECL CDECL_EXT dtu_getdateandtime__fb_init(dtu_getdateandtime_fb_init_struct *p);
typedef void (CDECL CDECL_EXT* PFDTU_GETDATEANDTIME__FB_INIT_IEC) (dtu_getdateandtime_fb_init_struct *p);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_GETDATEANDTIME__FB_INIT_NOTIMPLEMENTED)
	#define USE_dtu_getdateandtime__fb_init
	#define EXT_dtu_getdateandtime__fb_init
	#define GET_dtu_getdateandtime__fb_init(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dtu_getdateandtime__fb_init(p0) 
	#define CHK_dtu_getdateandtime__fb_init  FALSE
	#define EXP_dtu_getdateandtime__fb_init  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dtu_getdateandtime__fb_init
	#define EXT_dtu_getdateandtime__fb_init
	#define GET_dtu_getdateandtime__fb_init(fl)  CAL_CMGETAPI( "dtu_getdateandtime__fb_init" ) 
	#define CAL_dtu_getdateandtime__fb_init  dtu_getdateandtime__fb_init
	#define CHK_dtu_getdateandtime__fb_init  TRUE
	#define EXP_dtu_getdateandtime__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getdateandtime__fb_init", (RTS_UINTPTR)dtu_getdateandtime__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0x6854C6A4), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_dtu_getdateandtime__fb_init
	#define EXT_dtu_getdateandtime__fb_init
	#define GET_dtu_getdateandtime__fb_init(fl)  CAL_CMGETAPI( "dtu_getdateandtime__fb_init" ) 
	#define CAL_dtu_getdateandtime__fb_init  dtu_getdateandtime__fb_init
	#define CHK_dtu_getdateandtime__fb_init  TRUE
	#define EXP_dtu_getdateandtime__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getdateandtime__fb_init", (RTS_UINTPTR)dtu_getdateandtime__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0x6854C6A4), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtildtu_getdateandtime__fb_init
	#define EXT_CmpCAADTUtildtu_getdateandtime__fb_init
	#define GET_CmpCAADTUtildtu_getdateandtime__fb_init  ERR_OK
	#define CAL_CmpCAADTUtildtu_getdateandtime__fb_init  dtu_getdateandtime__fb_init
	#define CHK_CmpCAADTUtildtu_getdateandtime__fb_init  TRUE
	#define EXP_CmpCAADTUtildtu_getdateandtime__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getdateandtime__fb_init", (RTS_UINTPTR)dtu_getdateandtime__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0x6854C6A4), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_dtu_getdateandtime__fb_init
	#define EXT_dtu_getdateandtime__fb_init
	#define GET_dtu_getdateandtime__fb_init(fl)  CAL_CMGETAPI( "dtu_getdateandtime__fb_init" ) 
	#define CAL_dtu_getdateandtime__fb_init  dtu_getdateandtime__fb_init
	#define CHK_dtu_getdateandtime__fb_init  TRUE
	#define EXP_dtu_getdateandtime__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getdateandtime__fb_init", (RTS_UINTPTR)dtu_getdateandtime__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0x6854C6A4), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_dtu_getdateandtime__fb_init  PFDTU_GETDATEANDTIME__FB_INIT_IEC pfdtu_getdateandtime__fb_init;
	#define EXT_dtu_getdateandtime__fb_init  extern PFDTU_GETDATEANDTIME__FB_INIT_IEC pfdtu_getdateandtime__fb_init;
	#define GET_dtu_getdateandtime__fb_init(fl)  s_pfCMGetAPI2( "dtu_getdateandtime__fb_init", (RTS_VOID_FCTPTR *)&pfdtu_getdateandtime__fb_init, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x6854C6A4), 0x03050500)
	#define CAL_dtu_getdateandtime__fb_init  pfdtu_getdateandtime__fb_init
	#define CHK_dtu_getdateandtime__fb_init  (pfdtu_getdateandtime__fb_init != NULL)
	#define EXP_dtu_getdateandtime__fb_init   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getdateandtime__fb_init", (RTS_UINTPTR)dtu_getdateandtime__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0x6854C6A4), 0x03050500) 
#endif


/**
 * <description>dtu_getdateandtime_main</description>
 */
typedef struct tagdtu_getdateandtime_main_struct
{
	dtu_getdateandtime_struct *pInstance;	/* VAR_INPUT */	
} dtu_getdateandtime_main_struct;

void CDECL CDECL_EXT dtu_getdateandtime__main(dtu_getdateandtime_main_struct *p);
typedef void (CDECL CDECL_EXT* PFDTU_GETDATEANDTIME__MAIN_IEC) (dtu_getdateandtime_main_struct *p);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_GETDATEANDTIME__MAIN_NOTIMPLEMENTED)
	#define USE_dtu_getdateandtime__main
	#define EXT_dtu_getdateandtime__main
	#define GET_dtu_getdateandtime__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dtu_getdateandtime__main(p0) 
	#define CHK_dtu_getdateandtime__main  FALSE
	#define EXP_dtu_getdateandtime__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dtu_getdateandtime__main
	#define EXT_dtu_getdateandtime__main
	#define GET_dtu_getdateandtime__main(fl)  CAL_CMGETAPI( "dtu_getdateandtime__main" ) 
	#define CAL_dtu_getdateandtime__main  dtu_getdateandtime__main
	#define CHK_dtu_getdateandtime__main  TRUE
	#define EXP_dtu_getdateandtime__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getdateandtime__main", (RTS_UINTPTR)dtu_getdateandtime__main, 1, RTSITF_GET_SIGNATURE(0, 0x62F3BD7B), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_dtu_getdateandtime__main
	#define EXT_dtu_getdateandtime__main
	#define GET_dtu_getdateandtime__main(fl)  CAL_CMGETAPI( "dtu_getdateandtime__main" ) 
	#define CAL_dtu_getdateandtime__main  dtu_getdateandtime__main
	#define CHK_dtu_getdateandtime__main  TRUE
	#define EXP_dtu_getdateandtime__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getdateandtime__main", (RTS_UINTPTR)dtu_getdateandtime__main, 1, RTSITF_GET_SIGNATURE(0, 0x62F3BD7B), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtildtu_getdateandtime__main
	#define EXT_CmpCAADTUtildtu_getdateandtime__main
	#define GET_CmpCAADTUtildtu_getdateandtime__main  ERR_OK
	#define CAL_CmpCAADTUtildtu_getdateandtime__main  dtu_getdateandtime__main
	#define CHK_CmpCAADTUtildtu_getdateandtime__main  TRUE
	#define EXP_CmpCAADTUtildtu_getdateandtime__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getdateandtime__main", (RTS_UINTPTR)dtu_getdateandtime__main, 1, RTSITF_GET_SIGNATURE(0, 0x62F3BD7B), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_dtu_getdateandtime__main
	#define EXT_dtu_getdateandtime__main
	#define GET_dtu_getdateandtime__main(fl)  CAL_CMGETAPI( "dtu_getdateandtime__main" ) 
	#define CAL_dtu_getdateandtime__main  dtu_getdateandtime__main
	#define CHK_dtu_getdateandtime__main  TRUE
	#define EXP_dtu_getdateandtime__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getdateandtime__main", (RTS_UINTPTR)dtu_getdateandtime__main, 1, RTSITF_GET_SIGNATURE(0, 0x62F3BD7B), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_dtu_getdateandtime__main  PFDTU_GETDATEANDTIME__MAIN_IEC pfdtu_getdateandtime__main;
	#define EXT_dtu_getdateandtime__main  extern PFDTU_GETDATEANDTIME__MAIN_IEC pfdtu_getdateandtime__main;
	#define GET_dtu_getdateandtime__main(fl)  s_pfCMGetAPI2( "dtu_getdateandtime__main", (RTS_VOID_FCTPTR *)&pfdtu_getdateandtime__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x62F3BD7B), 0x03050500)
	#define CAL_dtu_getdateandtime__main  pfdtu_getdateandtime__main
	#define CHK_dtu_getdateandtime__main  (pfdtu_getdateandtime__main != NULL)
	#define EXP_dtu_getdateandtime__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getdateandtime__main", (RTS_UINTPTR)dtu_getdateandtime__main, 1, RTSITF_GET_SIGNATURE(0, 0x62F3BD7B), 0x03050500) 
#endif


/**
 * <description>dtu_getdateandtime_fb_exit</description>
 */
typedef struct tagdtu_getdateandtime_fb_exit_struct
{
	dtu_getdateandtime_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Exit;					/* VAR_OUTPUT */	
} dtu_getdateandtime_fb_exit_struct;

void CDECL CDECL_EXT dtu_getdateandtime__fb_exit(dtu_getdateandtime_fb_exit_struct *p);
typedef void (CDECL CDECL_EXT* PFDTU_GETDATEANDTIME__FB_EXIT_IEC) (dtu_getdateandtime_fb_exit_struct *p);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_GETDATEANDTIME__FB_EXIT_NOTIMPLEMENTED)
	#define USE_dtu_getdateandtime__fb_exit
	#define EXT_dtu_getdateandtime__fb_exit
	#define GET_dtu_getdateandtime__fb_exit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dtu_getdateandtime__fb_exit(p0) 
	#define CHK_dtu_getdateandtime__fb_exit  FALSE
	#define EXP_dtu_getdateandtime__fb_exit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dtu_getdateandtime__fb_exit
	#define EXT_dtu_getdateandtime__fb_exit
	#define GET_dtu_getdateandtime__fb_exit(fl)  CAL_CMGETAPI( "dtu_getdateandtime__fb_exit" ) 
	#define CAL_dtu_getdateandtime__fb_exit  dtu_getdateandtime__fb_exit
	#define CHK_dtu_getdateandtime__fb_exit  TRUE
	#define EXP_dtu_getdateandtime__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getdateandtime__fb_exit", (RTS_UINTPTR)dtu_getdateandtime__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xAD882E4A), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_dtu_getdateandtime__fb_exit
	#define EXT_dtu_getdateandtime__fb_exit
	#define GET_dtu_getdateandtime__fb_exit(fl)  CAL_CMGETAPI( "dtu_getdateandtime__fb_exit" ) 
	#define CAL_dtu_getdateandtime__fb_exit  dtu_getdateandtime__fb_exit
	#define CHK_dtu_getdateandtime__fb_exit  TRUE
	#define EXP_dtu_getdateandtime__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getdateandtime__fb_exit", (RTS_UINTPTR)dtu_getdateandtime__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xAD882E4A), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtildtu_getdateandtime__fb_exit
	#define EXT_CmpCAADTUtildtu_getdateandtime__fb_exit
	#define GET_CmpCAADTUtildtu_getdateandtime__fb_exit  ERR_OK
	#define CAL_CmpCAADTUtildtu_getdateandtime__fb_exit  dtu_getdateandtime__fb_exit
	#define CHK_CmpCAADTUtildtu_getdateandtime__fb_exit  TRUE
	#define EXP_CmpCAADTUtildtu_getdateandtime__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getdateandtime__fb_exit", (RTS_UINTPTR)dtu_getdateandtime__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xAD882E4A), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_dtu_getdateandtime__fb_exit
	#define EXT_dtu_getdateandtime__fb_exit
	#define GET_dtu_getdateandtime__fb_exit(fl)  CAL_CMGETAPI( "dtu_getdateandtime__fb_exit" ) 
	#define CAL_dtu_getdateandtime__fb_exit  dtu_getdateandtime__fb_exit
	#define CHK_dtu_getdateandtime__fb_exit  TRUE
	#define EXP_dtu_getdateandtime__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getdateandtime__fb_exit", (RTS_UINTPTR)dtu_getdateandtime__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xAD882E4A), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_dtu_getdateandtime__fb_exit  PFDTU_GETDATEANDTIME__FB_EXIT_IEC pfdtu_getdateandtime__fb_exit;
	#define EXT_dtu_getdateandtime__fb_exit  extern PFDTU_GETDATEANDTIME__FB_EXIT_IEC pfdtu_getdateandtime__fb_exit;
	#define GET_dtu_getdateandtime__fb_exit(fl)  s_pfCMGetAPI2( "dtu_getdateandtime__fb_exit", (RTS_VOID_FCTPTR *)&pfdtu_getdateandtime__fb_exit, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xAD882E4A), 0x03050500)
	#define CAL_dtu_getdateandtime__fb_exit  pfdtu_getdateandtime__fb_exit
	#define CHK_dtu_getdateandtime__fb_exit  (pfdtu_getdateandtime__fb_exit != NULL)
	#define EXP_dtu_getdateandtime__fb_exit   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getdateandtime__fb_exit", (RTS_UINTPTR)dtu_getdateandtime__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xAD882E4A), 0x03050500) 
#endif


/**
 * <description>dtu_getdayofweek</description>
 */
typedef struct tagdtu_getdayofweek_struct
{
	RTS_IEC_DATE dtDate;				/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_ENUM DTU_GetDayOfWeek;			/* VAR_OUTPUT */	/* eWeekday */
} dtu_getdayofweek_struct;

void CDECL CDECL_EXT dtu_getdayofweek(dtu_getdayofweek_struct *p);
typedef void (CDECL CDECL_EXT* PFDTU_GETDAYOFWEEK_IEC) (dtu_getdayofweek_struct *p);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_GETDAYOFWEEK_NOTIMPLEMENTED)
	#define USE_dtu_getdayofweek
	#define EXT_dtu_getdayofweek
	#define GET_dtu_getdayofweek(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dtu_getdayofweek(p0) 
	#define CHK_dtu_getdayofweek  FALSE
	#define EXP_dtu_getdayofweek  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dtu_getdayofweek
	#define EXT_dtu_getdayofweek
	#define GET_dtu_getdayofweek(fl)  CAL_CMGETAPI( "dtu_getdayofweek" ) 
	#define CAL_dtu_getdayofweek  dtu_getdayofweek
	#define CHK_dtu_getdayofweek  TRUE
	#define EXP_dtu_getdayofweek  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getdayofweek", (RTS_UINTPTR)dtu_getdayofweek, 1, RTSITF_GET_SIGNATURE(0, 0x5765448B), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_dtu_getdayofweek
	#define EXT_dtu_getdayofweek
	#define GET_dtu_getdayofweek(fl)  CAL_CMGETAPI( "dtu_getdayofweek" ) 
	#define CAL_dtu_getdayofweek  dtu_getdayofweek
	#define CHK_dtu_getdayofweek  TRUE
	#define EXP_dtu_getdayofweek  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getdayofweek", (RTS_UINTPTR)dtu_getdayofweek, 1, RTSITF_GET_SIGNATURE(0, 0x5765448B), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtildtu_getdayofweek
	#define EXT_CmpCAADTUtildtu_getdayofweek
	#define GET_CmpCAADTUtildtu_getdayofweek  ERR_OK
	#define CAL_CmpCAADTUtildtu_getdayofweek  dtu_getdayofweek
	#define CHK_CmpCAADTUtildtu_getdayofweek  TRUE
	#define EXP_CmpCAADTUtildtu_getdayofweek  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getdayofweek", (RTS_UINTPTR)dtu_getdayofweek, 1, RTSITF_GET_SIGNATURE(0, 0x5765448B), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_dtu_getdayofweek
	#define EXT_dtu_getdayofweek
	#define GET_dtu_getdayofweek(fl)  CAL_CMGETAPI( "dtu_getdayofweek" ) 
	#define CAL_dtu_getdayofweek  dtu_getdayofweek
	#define CHK_dtu_getdayofweek  TRUE
	#define EXP_dtu_getdayofweek  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getdayofweek", (RTS_UINTPTR)dtu_getdayofweek, 1, RTSITF_GET_SIGNATURE(0, 0x5765448B), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_dtu_getdayofweek  PFDTU_GETDAYOFWEEK_IEC pfdtu_getdayofweek;
	#define EXT_dtu_getdayofweek  extern PFDTU_GETDAYOFWEEK_IEC pfdtu_getdayofweek;
	#define GET_dtu_getdayofweek(fl)  s_pfCMGetAPI2( "dtu_getdayofweek", (RTS_VOID_FCTPTR *)&pfdtu_getdayofweek, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x5765448B), 0x03050500)
	#define CAL_dtu_getdayofweek  pfdtu_getdayofweek
	#define CHK_dtu_getdayofweek  (pfdtu_getdayofweek != NULL)
	#define EXP_dtu_getdayofweek   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getdayofweek", (RTS_UINTPTR)dtu_getdayofweek, 1, RTSITF_GET_SIGNATURE(0, 0x5765448B), 0x03050500) 
#endif


/**
 * <description>dtu_getsupplierversion</description>
 */
typedef struct tagdtu_getsupplierversion_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	RTS_IEC_WORD DTU_GetSupplierVersion;	/* VAR_OUTPUT */	
} dtu_getsupplierversion_struct;

void CDECL CDECL_EXT dtu_getsupplierversion(dtu_getsupplierversion_struct *p);
typedef void (CDECL CDECL_EXT* PFDTU_GETSUPPLIERVERSION_IEC) (dtu_getsupplierversion_struct *p);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_GETSUPPLIERVERSION_NOTIMPLEMENTED)
	#define USE_dtu_getsupplierversion
	#define EXT_dtu_getsupplierversion
	#define GET_dtu_getsupplierversion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dtu_getsupplierversion(p0) 
	#define CHK_dtu_getsupplierversion  FALSE
	#define EXP_dtu_getsupplierversion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dtu_getsupplierversion
	#define EXT_dtu_getsupplierversion
	#define GET_dtu_getsupplierversion(fl)  CAL_CMGETAPI( "dtu_getsupplierversion" ) 
	#define CAL_dtu_getsupplierversion  dtu_getsupplierversion
	#define CHK_dtu_getsupplierversion  TRUE
	#define EXP_dtu_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getsupplierversion", (RTS_UINTPTR)dtu_getsupplierversion, 1, 0xD6C53158, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_dtu_getsupplierversion
	#define EXT_dtu_getsupplierversion
	#define GET_dtu_getsupplierversion(fl)  CAL_CMGETAPI( "dtu_getsupplierversion" ) 
	#define CAL_dtu_getsupplierversion  dtu_getsupplierversion
	#define CHK_dtu_getsupplierversion  TRUE
	#define EXP_dtu_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getsupplierversion", (RTS_UINTPTR)dtu_getsupplierversion, 1, 0xD6C53158, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtildtu_getsupplierversion
	#define EXT_CmpCAADTUtildtu_getsupplierversion
	#define GET_CmpCAADTUtildtu_getsupplierversion  ERR_OK
	#define CAL_CmpCAADTUtildtu_getsupplierversion  dtu_getsupplierversion
	#define CHK_CmpCAADTUtildtu_getsupplierversion  TRUE
	#define EXP_CmpCAADTUtildtu_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getsupplierversion", (RTS_UINTPTR)dtu_getsupplierversion, 1, 0xD6C53158, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_dtu_getsupplierversion
	#define EXT_dtu_getsupplierversion
	#define GET_dtu_getsupplierversion(fl)  CAL_CMGETAPI( "dtu_getsupplierversion" ) 
	#define CAL_dtu_getsupplierversion  dtu_getsupplierversion
	#define CHK_dtu_getsupplierversion  TRUE
	#define EXP_dtu_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getsupplierversion", (RTS_UINTPTR)dtu_getsupplierversion, 1, 0xD6C53158, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_dtu_getsupplierversion  PFDTU_GETSUPPLIERVERSION_IEC pfdtu_getsupplierversion;
	#define EXT_dtu_getsupplierversion  extern PFDTU_GETSUPPLIERVERSION_IEC pfdtu_getsupplierversion;
	#define GET_dtu_getsupplierversion(fl)  s_pfCMGetAPI2( "dtu_getsupplierversion", (RTS_VOID_FCTPTR *)&pfdtu_getsupplierversion, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xD6C53158, 0x03050500)
	#define CAL_dtu_getsupplierversion  pfdtu_getsupplierversion
	#define CHK_dtu_getsupplierversion  (pfdtu_getsupplierversion != NULL)
	#define EXP_dtu_getsupplierversion   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_getsupplierversion", (RTS_UINTPTR)dtu_getsupplierversion, 1, 0xD6C53158, 0x03050500) 
#endif


/**
 * <description>dtu_gettimezoneinformation__main</description>
 */
typedef struct tagdtu_gettimezoneinformation_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	CAA_BOOL xExecute;					/* VAR_INPUT */	/* Rising edge: Action start
							Falling edge: Resets outputs
							If a falling edge occurs before the function block has completed its action, the outputs operate
							in the usual manner and are only reset if either the action is completed or
							in the event of an error. In this case, the corresponding output values (xDone, xError, iError)
							are present at the outputs for exactly one cycle. */
	CAA_BOOL xDone;						/* VAR_OUTPUT */	/* Action successfully completed */
	CAA_BOOL xBusy;						/* VAR_OUTPUT */	/* Function block active */
	CAA_BOOL xError;					/* VAR_OUTPUT */	/* TRUE: error occurred, function block aborts action
							FALSE: no error */
	CAA_ERROR eError;					/* VAR_OUTPUT */	
	RTCLK_TIME_ZONE_INFO tziInfo;		/* VAR_OUTPUT */	
	CAA_BOOL xPreviousExecute;			/* Local variable */	/* value of xExecute in previous cycle */
	CAA_BOOL xPreviousAbortInProgress;	/* Local variable */	/* value of xAbortInPrograss in previous cycle */
	CAA_BOOL xAbortInProgress;			/* Local variable */	/* TRUE: abort is processed
											FALSE: abort is done */
	RTS_IEC_INT iError;					/* Local variable */	/* Local library error ID is transfered to eError by the concrete implementation */
	CAA_HANDLE hJob;					/* Local variable */	/* specific vars */
	DTU_GETTIMEZONEINFORMATION_PARAMS *pGetTimeZoneInformationParams;	/* Local variable */	
	ASM_STATE StateJob;					/* Local variable */	
	RTS_IEC_XWORD dwEtrigClass;			/* Local variable */	
} dtu_gettimezoneinformation_struct;

/**
 * <description>dtu_gettimezoneinformation_fb_init</description>
 */
typedef struct tagdtu_gettimezoneinformation_fb_init_struct
{
	dtu_gettimezoneinformation_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInitRetains;				/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Init;					/* VAR_OUTPUT */	
} dtu_gettimezoneinformation_fb_init_struct;

void CDECL CDECL_EXT dtu_gettimezoneinformation__fb_init(dtu_gettimezoneinformation_fb_init_struct *p);
typedef void (CDECL CDECL_EXT* PFDTU_GETTIMEZONEINFORMATION__FB_INIT_IEC) (dtu_gettimezoneinformation_fb_init_struct *p);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_GETTIMEZONEINFORMATION__FB_INIT_NOTIMPLEMENTED)
	#define USE_dtu_gettimezoneinformation__fb_init
	#define EXT_dtu_gettimezoneinformation__fb_init
	#define GET_dtu_gettimezoneinformation__fb_init(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dtu_gettimezoneinformation__fb_init(p0) 
	#define CHK_dtu_gettimezoneinformation__fb_init  FALSE
	#define EXP_dtu_gettimezoneinformation__fb_init  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dtu_gettimezoneinformation__fb_init
	#define EXT_dtu_gettimezoneinformation__fb_init
	#define GET_dtu_gettimezoneinformation__fb_init(fl)  CAL_CMGETAPI( "dtu_gettimezoneinformation__fb_init" ) 
	#define CAL_dtu_gettimezoneinformation__fb_init  dtu_gettimezoneinformation__fb_init
	#define CHK_dtu_gettimezoneinformation__fb_init  TRUE
	#define EXP_dtu_gettimezoneinformation__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_gettimezoneinformation__fb_init", (RTS_UINTPTR)dtu_gettimezoneinformation__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0x38F23BEC), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_dtu_gettimezoneinformation__fb_init
	#define EXT_dtu_gettimezoneinformation__fb_init
	#define GET_dtu_gettimezoneinformation__fb_init(fl)  CAL_CMGETAPI( "dtu_gettimezoneinformation__fb_init" ) 
	#define CAL_dtu_gettimezoneinformation__fb_init  dtu_gettimezoneinformation__fb_init
	#define CHK_dtu_gettimezoneinformation__fb_init  TRUE
	#define EXP_dtu_gettimezoneinformation__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_gettimezoneinformation__fb_init", (RTS_UINTPTR)dtu_gettimezoneinformation__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0x38F23BEC), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtildtu_gettimezoneinformation__fb_init
	#define EXT_CmpCAADTUtildtu_gettimezoneinformation__fb_init
	#define GET_CmpCAADTUtildtu_gettimezoneinformation__fb_init  ERR_OK
	#define CAL_CmpCAADTUtildtu_gettimezoneinformation__fb_init  dtu_gettimezoneinformation__fb_init
	#define CHK_CmpCAADTUtildtu_gettimezoneinformation__fb_init  TRUE
	#define EXP_CmpCAADTUtildtu_gettimezoneinformation__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_gettimezoneinformation__fb_init", (RTS_UINTPTR)dtu_gettimezoneinformation__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0x38F23BEC), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_dtu_gettimezoneinformation__fb_init
	#define EXT_dtu_gettimezoneinformation__fb_init
	#define GET_dtu_gettimezoneinformation__fb_init(fl)  CAL_CMGETAPI( "dtu_gettimezoneinformation__fb_init" ) 
	#define CAL_dtu_gettimezoneinformation__fb_init  dtu_gettimezoneinformation__fb_init
	#define CHK_dtu_gettimezoneinformation__fb_init  TRUE
	#define EXP_dtu_gettimezoneinformation__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_gettimezoneinformation__fb_init", (RTS_UINTPTR)dtu_gettimezoneinformation__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0x38F23BEC), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_dtu_gettimezoneinformation__fb_init  PFDTU_GETTIMEZONEINFORMATION__FB_INIT_IEC pfdtu_gettimezoneinformation__fb_init;
	#define EXT_dtu_gettimezoneinformation__fb_init  extern PFDTU_GETTIMEZONEINFORMATION__FB_INIT_IEC pfdtu_gettimezoneinformation__fb_init;
	#define GET_dtu_gettimezoneinformation__fb_init(fl)  s_pfCMGetAPI2( "dtu_gettimezoneinformation__fb_init", (RTS_VOID_FCTPTR *)&pfdtu_gettimezoneinformation__fb_init, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x38F23BEC), 0x03050500)
	#define CAL_dtu_gettimezoneinformation__fb_init  pfdtu_gettimezoneinformation__fb_init
	#define CHK_dtu_gettimezoneinformation__fb_init  (pfdtu_gettimezoneinformation__fb_init != NULL)
	#define EXP_dtu_gettimezoneinformation__fb_init   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_gettimezoneinformation__fb_init", (RTS_UINTPTR)dtu_gettimezoneinformation__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0x38F23BEC), 0x03050500) 
#endif


/**
 * <description>dtu_gettimezoneinformation_main</description>
 */
typedef struct tagdtu_gettimezoneinformation_main_struct
{
	dtu_gettimezoneinformation_struct *pInstance;	/* VAR_INPUT */	
} dtu_gettimezoneinformation_main_struct;

void CDECL CDECL_EXT dtu_gettimezoneinformation__main(dtu_gettimezoneinformation_main_struct *p);
typedef void (CDECL CDECL_EXT* PFDTU_GETTIMEZONEINFORMATION__MAIN_IEC) (dtu_gettimezoneinformation_main_struct *p);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_GETTIMEZONEINFORMATION__MAIN_NOTIMPLEMENTED)
	#define USE_dtu_gettimezoneinformation__main
	#define EXT_dtu_gettimezoneinformation__main
	#define GET_dtu_gettimezoneinformation__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dtu_gettimezoneinformation__main(p0) 
	#define CHK_dtu_gettimezoneinformation__main  FALSE
	#define EXP_dtu_gettimezoneinformation__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dtu_gettimezoneinformation__main
	#define EXT_dtu_gettimezoneinformation__main
	#define GET_dtu_gettimezoneinformation__main(fl)  CAL_CMGETAPI( "dtu_gettimezoneinformation__main" ) 
	#define CAL_dtu_gettimezoneinformation__main  dtu_gettimezoneinformation__main
	#define CHK_dtu_gettimezoneinformation__main  TRUE
	#define EXP_dtu_gettimezoneinformation__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_gettimezoneinformation__main", (RTS_UINTPTR)dtu_gettimezoneinformation__main, 1, RTSITF_GET_SIGNATURE(0, 0xFE0E2F0A), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_dtu_gettimezoneinformation__main
	#define EXT_dtu_gettimezoneinformation__main
	#define GET_dtu_gettimezoneinformation__main(fl)  CAL_CMGETAPI( "dtu_gettimezoneinformation__main" ) 
	#define CAL_dtu_gettimezoneinformation__main  dtu_gettimezoneinformation__main
	#define CHK_dtu_gettimezoneinformation__main  TRUE
	#define EXP_dtu_gettimezoneinformation__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_gettimezoneinformation__main", (RTS_UINTPTR)dtu_gettimezoneinformation__main, 1, RTSITF_GET_SIGNATURE(0, 0xFE0E2F0A), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtildtu_gettimezoneinformation__main
	#define EXT_CmpCAADTUtildtu_gettimezoneinformation__main
	#define GET_CmpCAADTUtildtu_gettimezoneinformation__main  ERR_OK
	#define CAL_CmpCAADTUtildtu_gettimezoneinformation__main  dtu_gettimezoneinformation__main
	#define CHK_CmpCAADTUtildtu_gettimezoneinformation__main  TRUE
	#define EXP_CmpCAADTUtildtu_gettimezoneinformation__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_gettimezoneinformation__main", (RTS_UINTPTR)dtu_gettimezoneinformation__main, 1, RTSITF_GET_SIGNATURE(0, 0xFE0E2F0A), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_dtu_gettimezoneinformation__main
	#define EXT_dtu_gettimezoneinformation__main
	#define GET_dtu_gettimezoneinformation__main(fl)  CAL_CMGETAPI( "dtu_gettimezoneinformation__main" ) 
	#define CAL_dtu_gettimezoneinformation__main  dtu_gettimezoneinformation__main
	#define CHK_dtu_gettimezoneinformation__main  TRUE
	#define EXP_dtu_gettimezoneinformation__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_gettimezoneinformation__main", (RTS_UINTPTR)dtu_gettimezoneinformation__main, 1, RTSITF_GET_SIGNATURE(0, 0xFE0E2F0A), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_dtu_gettimezoneinformation__main  PFDTU_GETTIMEZONEINFORMATION__MAIN_IEC pfdtu_gettimezoneinformation__main;
	#define EXT_dtu_gettimezoneinformation__main  extern PFDTU_GETTIMEZONEINFORMATION__MAIN_IEC pfdtu_gettimezoneinformation__main;
	#define GET_dtu_gettimezoneinformation__main(fl)  s_pfCMGetAPI2( "dtu_gettimezoneinformation__main", (RTS_VOID_FCTPTR *)&pfdtu_gettimezoneinformation__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xFE0E2F0A), 0x03050500)
	#define CAL_dtu_gettimezoneinformation__main  pfdtu_gettimezoneinformation__main
	#define CHK_dtu_gettimezoneinformation__main  (pfdtu_gettimezoneinformation__main != NULL)
	#define EXP_dtu_gettimezoneinformation__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_gettimezoneinformation__main", (RTS_UINTPTR)dtu_gettimezoneinformation__main, 1, RTSITF_GET_SIGNATURE(0, 0xFE0E2F0A), 0x03050500) 
#endif


/**
 * <description>dtu_gettimezoneinformation_fb_exit</description>
 */
typedef struct tagdtu_gettimezoneinformation_fb_exit_struct
{
	dtu_gettimezoneinformation_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Exit;					/* VAR_OUTPUT */	
} dtu_gettimezoneinformation_fb_exit_struct;

void CDECL CDECL_EXT dtu_gettimezoneinformation__fb_exit(dtu_gettimezoneinformation_fb_exit_struct *p);
typedef void (CDECL CDECL_EXT* PFDTU_GETTIMEZONEINFORMATION__FB_EXIT_IEC) (dtu_gettimezoneinformation_fb_exit_struct *p);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_GETTIMEZONEINFORMATION__FB_EXIT_NOTIMPLEMENTED)
	#define USE_dtu_gettimezoneinformation__fb_exit
	#define EXT_dtu_gettimezoneinformation__fb_exit
	#define GET_dtu_gettimezoneinformation__fb_exit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dtu_gettimezoneinformation__fb_exit(p0) 
	#define CHK_dtu_gettimezoneinformation__fb_exit  FALSE
	#define EXP_dtu_gettimezoneinformation__fb_exit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dtu_gettimezoneinformation__fb_exit
	#define EXT_dtu_gettimezoneinformation__fb_exit
	#define GET_dtu_gettimezoneinformation__fb_exit(fl)  CAL_CMGETAPI( "dtu_gettimezoneinformation__fb_exit" ) 
	#define CAL_dtu_gettimezoneinformation__fb_exit  dtu_gettimezoneinformation__fb_exit
	#define CHK_dtu_gettimezoneinformation__fb_exit  TRUE
	#define EXP_dtu_gettimezoneinformation__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_gettimezoneinformation__fb_exit", (RTS_UINTPTR)dtu_gettimezoneinformation__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0x5FBCC9DE), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_dtu_gettimezoneinformation__fb_exit
	#define EXT_dtu_gettimezoneinformation__fb_exit
	#define GET_dtu_gettimezoneinformation__fb_exit(fl)  CAL_CMGETAPI( "dtu_gettimezoneinformation__fb_exit" ) 
	#define CAL_dtu_gettimezoneinformation__fb_exit  dtu_gettimezoneinformation__fb_exit
	#define CHK_dtu_gettimezoneinformation__fb_exit  TRUE
	#define EXP_dtu_gettimezoneinformation__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_gettimezoneinformation__fb_exit", (RTS_UINTPTR)dtu_gettimezoneinformation__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0x5FBCC9DE), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtildtu_gettimezoneinformation__fb_exit
	#define EXT_CmpCAADTUtildtu_gettimezoneinformation__fb_exit
	#define GET_CmpCAADTUtildtu_gettimezoneinformation__fb_exit  ERR_OK
	#define CAL_CmpCAADTUtildtu_gettimezoneinformation__fb_exit  dtu_gettimezoneinformation__fb_exit
	#define CHK_CmpCAADTUtildtu_gettimezoneinformation__fb_exit  TRUE
	#define EXP_CmpCAADTUtildtu_gettimezoneinformation__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_gettimezoneinformation__fb_exit", (RTS_UINTPTR)dtu_gettimezoneinformation__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0x5FBCC9DE), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_dtu_gettimezoneinformation__fb_exit
	#define EXT_dtu_gettimezoneinformation__fb_exit
	#define GET_dtu_gettimezoneinformation__fb_exit(fl)  CAL_CMGETAPI( "dtu_gettimezoneinformation__fb_exit" ) 
	#define CAL_dtu_gettimezoneinformation__fb_exit  dtu_gettimezoneinformation__fb_exit
	#define CHK_dtu_gettimezoneinformation__fb_exit  TRUE
	#define EXP_dtu_gettimezoneinformation__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_gettimezoneinformation__fb_exit", (RTS_UINTPTR)dtu_gettimezoneinformation__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0x5FBCC9DE), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_dtu_gettimezoneinformation__fb_exit  PFDTU_GETTIMEZONEINFORMATION__FB_EXIT_IEC pfdtu_gettimezoneinformation__fb_exit;
	#define EXT_dtu_gettimezoneinformation__fb_exit  extern PFDTU_GETTIMEZONEINFORMATION__FB_EXIT_IEC pfdtu_gettimezoneinformation__fb_exit;
	#define GET_dtu_gettimezoneinformation__fb_exit(fl)  s_pfCMGetAPI2( "dtu_gettimezoneinformation__fb_exit", (RTS_VOID_FCTPTR *)&pfdtu_gettimezoneinformation__fb_exit, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x5FBCC9DE), 0x03050500)
	#define CAL_dtu_gettimezoneinformation__fb_exit  pfdtu_gettimezoneinformation__fb_exit
	#define CHK_dtu_gettimezoneinformation__fb_exit  (pfdtu_gettimezoneinformation__fb_exit != NULL)
	#define EXP_dtu_gettimezoneinformation__fb_exit   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_gettimezoneinformation__fb_exit", (RTS_UINTPTR)dtu_gettimezoneinformation__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0x5FBCC9DE), 0x03050500) 
#endif


/**
 * <description>dtu_setdateandtime__main</description>
 */
typedef struct tagdtu_setdateandtime_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	CAA_BOOL xExecute;					/* VAR_INPUT */	/* Rising edge: Action start
							Falling edge: Resets outputs
							If a falling edge occurs before the function block has completed its action, the outputs operate
							in the usual manner and are only reset if either the action is completed or
							in the event of an error. In this case, the corresponding output values (xDone, xError, iError)
							are present at the outputs for exactly one cycle. */
	RTS_IEC_DATE_AND_TIME dtDateAndTime;	/* VAR_INPUT */	
	CAA_BOOL xDone;						/* VAR_OUTPUT */	/* Action successfully completed */
	CAA_BOOL xBusy;						/* VAR_OUTPUT */	/* Function block active */
	CAA_BOOL xError;					/* VAR_OUTPUT */	/* TRUE: error occurred, function block aborts action
							FALSE: no error */
	CAA_ERROR eError;					/* VAR_OUTPUT */	
	CAA_BOOL xPreviousExecute;			/* Local variable */	/* value of xExecute in previous cycle */
	CAA_BOOL xPreviousAbortInProgress;	/* Local variable */	/* value of xAbortInPrograss in previous cycle */
	CAA_BOOL xAbortInProgress;			/* Local variable */	/* TRUE: abort is processed
											FALSE: abort is done */
	RTS_IEC_INT iError;					/* Local variable */	/* Local library error ID is transfered to eError by the concrete implementation */
	CAA_HANDLE hJob;					/* Local variable */	/* specific vars */
	DTU_SETDATEANDTIME_PARAMS *pSetDateAndTimeParams;	/* Local variable */	
	ASM_STATE StateJob;					/* Local variable */	
	RTS_IEC_XWORD dwEtrigClass;			/* Local variable */	
} dtu_setdateandtime_struct;

/**
 * <description>dtu_setdateandtime_fb_init</description>
 */
typedef struct tagdtu_setdateandtime_fb_init_struct
{
	dtu_setdateandtime_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInitRetains;				/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Init;					/* VAR_OUTPUT */	
} dtu_setdateandtime_fb_init_struct;

void CDECL CDECL_EXT dtu_setdateandtime__fb_init(dtu_setdateandtime_fb_init_struct *p);
typedef void (CDECL CDECL_EXT* PFDTU_SETDATEANDTIME__FB_INIT_IEC) (dtu_setdateandtime_fb_init_struct *p);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_SETDATEANDTIME__FB_INIT_NOTIMPLEMENTED)
	#define USE_dtu_setdateandtime__fb_init
	#define EXT_dtu_setdateandtime__fb_init
	#define GET_dtu_setdateandtime__fb_init(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dtu_setdateandtime__fb_init(p0) 
	#define CHK_dtu_setdateandtime__fb_init  FALSE
	#define EXP_dtu_setdateandtime__fb_init  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dtu_setdateandtime__fb_init
	#define EXT_dtu_setdateandtime__fb_init
	#define GET_dtu_setdateandtime__fb_init(fl)  CAL_CMGETAPI( "dtu_setdateandtime__fb_init" ) 
	#define CAL_dtu_setdateandtime__fb_init  dtu_setdateandtime__fb_init
	#define CHK_dtu_setdateandtime__fb_init  TRUE
	#define EXP_dtu_setdateandtime__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_setdateandtime__fb_init", (RTS_UINTPTR)dtu_setdateandtime__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0x0751D30F), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_dtu_setdateandtime__fb_init
	#define EXT_dtu_setdateandtime__fb_init
	#define GET_dtu_setdateandtime__fb_init(fl)  CAL_CMGETAPI( "dtu_setdateandtime__fb_init" ) 
	#define CAL_dtu_setdateandtime__fb_init  dtu_setdateandtime__fb_init
	#define CHK_dtu_setdateandtime__fb_init  TRUE
	#define EXP_dtu_setdateandtime__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_setdateandtime__fb_init", (RTS_UINTPTR)dtu_setdateandtime__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0x0751D30F), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtildtu_setdateandtime__fb_init
	#define EXT_CmpCAADTUtildtu_setdateandtime__fb_init
	#define GET_CmpCAADTUtildtu_setdateandtime__fb_init  ERR_OK
	#define CAL_CmpCAADTUtildtu_setdateandtime__fb_init  dtu_setdateandtime__fb_init
	#define CHK_CmpCAADTUtildtu_setdateandtime__fb_init  TRUE
	#define EXP_CmpCAADTUtildtu_setdateandtime__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_setdateandtime__fb_init", (RTS_UINTPTR)dtu_setdateandtime__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0x0751D30F), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_dtu_setdateandtime__fb_init
	#define EXT_dtu_setdateandtime__fb_init
	#define GET_dtu_setdateandtime__fb_init(fl)  CAL_CMGETAPI( "dtu_setdateandtime__fb_init" ) 
	#define CAL_dtu_setdateandtime__fb_init  dtu_setdateandtime__fb_init
	#define CHK_dtu_setdateandtime__fb_init  TRUE
	#define EXP_dtu_setdateandtime__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_setdateandtime__fb_init", (RTS_UINTPTR)dtu_setdateandtime__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0x0751D30F), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_dtu_setdateandtime__fb_init  PFDTU_SETDATEANDTIME__FB_INIT_IEC pfdtu_setdateandtime__fb_init;
	#define EXT_dtu_setdateandtime__fb_init  extern PFDTU_SETDATEANDTIME__FB_INIT_IEC pfdtu_setdateandtime__fb_init;
	#define GET_dtu_setdateandtime__fb_init(fl)  s_pfCMGetAPI2( "dtu_setdateandtime__fb_init", (RTS_VOID_FCTPTR *)&pfdtu_setdateandtime__fb_init, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x0751D30F), 0x03050500)
	#define CAL_dtu_setdateandtime__fb_init  pfdtu_setdateandtime__fb_init
	#define CHK_dtu_setdateandtime__fb_init  (pfdtu_setdateandtime__fb_init != NULL)
	#define EXP_dtu_setdateandtime__fb_init   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_setdateandtime__fb_init", (RTS_UINTPTR)dtu_setdateandtime__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0x0751D30F), 0x03050500) 
#endif


/**
 * <description>dtu_setdateandtime_main</description>
 */
typedef struct tagdtu_setdateandtime_main_struct
{
	dtu_setdateandtime_struct *pInstance;	/* VAR_INPUT */	
} dtu_setdateandtime_main_struct;

void CDECL CDECL_EXT dtu_setdateandtime__main(dtu_setdateandtime_main_struct *p);
typedef void (CDECL CDECL_EXT* PFDTU_SETDATEANDTIME__MAIN_IEC) (dtu_setdateandtime_main_struct *p);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_SETDATEANDTIME__MAIN_NOTIMPLEMENTED)
	#define USE_dtu_setdateandtime__main
	#define EXT_dtu_setdateandtime__main
	#define GET_dtu_setdateandtime__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dtu_setdateandtime__main(p0) 
	#define CHK_dtu_setdateandtime__main  FALSE
	#define EXP_dtu_setdateandtime__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dtu_setdateandtime__main
	#define EXT_dtu_setdateandtime__main
	#define GET_dtu_setdateandtime__main(fl)  CAL_CMGETAPI( "dtu_setdateandtime__main" ) 
	#define CAL_dtu_setdateandtime__main  dtu_setdateandtime__main
	#define CHK_dtu_setdateandtime__main  TRUE
	#define EXP_dtu_setdateandtime__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_setdateandtime__main", (RTS_UINTPTR)dtu_setdateandtime__main, 1, RTSITF_GET_SIGNATURE(0, 0xE8AC014D), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_dtu_setdateandtime__main
	#define EXT_dtu_setdateandtime__main
	#define GET_dtu_setdateandtime__main(fl)  CAL_CMGETAPI( "dtu_setdateandtime__main" ) 
	#define CAL_dtu_setdateandtime__main  dtu_setdateandtime__main
	#define CHK_dtu_setdateandtime__main  TRUE
	#define EXP_dtu_setdateandtime__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_setdateandtime__main", (RTS_UINTPTR)dtu_setdateandtime__main, 1, RTSITF_GET_SIGNATURE(0, 0xE8AC014D), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtildtu_setdateandtime__main
	#define EXT_CmpCAADTUtildtu_setdateandtime__main
	#define GET_CmpCAADTUtildtu_setdateandtime__main  ERR_OK
	#define CAL_CmpCAADTUtildtu_setdateandtime__main  dtu_setdateandtime__main
	#define CHK_CmpCAADTUtildtu_setdateandtime__main  TRUE
	#define EXP_CmpCAADTUtildtu_setdateandtime__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_setdateandtime__main", (RTS_UINTPTR)dtu_setdateandtime__main, 1, RTSITF_GET_SIGNATURE(0, 0xE8AC014D), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_dtu_setdateandtime__main
	#define EXT_dtu_setdateandtime__main
	#define GET_dtu_setdateandtime__main(fl)  CAL_CMGETAPI( "dtu_setdateandtime__main" ) 
	#define CAL_dtu_setdateandtime__main  dtu_setdateandtime__main
	#define CHK_dtu_setdateandtime__main  TRUE
	#define EXP_dtu_setdateandtime__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_setdateandtime__main", (RTS_UINTPTR)dtu_setdateandtime__main, 1, RTSITF_GET_SIGNATURE(0, 0xE8AC014D), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_dtu_setdateandtime__main  PFDTU_SETDATEANDTIME__MAIN_IEC pfdtu_setdateandtime__main;
	#define EXT_dtu_setdateandtime__main  extern PFDTU_SETDATEANDTIME__MAIN_IEC pfdtu_setdateandtime__main;
	#define GET_dtu_setdateandtime__main(fl)  s_pfCMGetAPI2( "dtu_setdateandtime__main", (RTS_VOID_FCTPTR *)&pfdtu_setdateandtime__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xE8AC014D), 0x03050500)
	#define CAL_dtu_setdateandtime__main  pfdtu_setdateandtime__main
	#define CHK_dtu_setdateandtime__main  (pfdtu_setdateandtime__main != NULL)
	#define EXP_dtu_setdateandtime__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_setdateandtime__main", (RTS_UINTPTR)dtu_setdateandtime__main, 1, RTSITF_GET_SIGNATURE(0, 0xE8AC014D), 0x03050500) 
#endif


/**
 * <description>dtu_setdateandtime_fb_exit</description>
 */
typedef struct tagdtu_setdateandtime_fb_exit_struct
{
	dtu_setdateandtime_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Exit;					/* VAR_OUTPUT */	
} dtu_setdateandtime_fb_exit_struct;

void CDECL CDECL_EXT dtu_setdateandtime__fb_exit(dtu_setdateandtime_fb_exit_struct *p);
typedef void (CDECL CDECL_EXT* PFDTU_SETDATEANDTIME__FB_EXIT_IEC) (dtu_setdateandtime_fb_exit_struct *p);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_SETDATEANDTIME__FB_EXIT_NOTIMPLEMENTED)
	#define USE_dtu_setdateandtime__fb_exit
	#define EXT_dtu_setdateandtime__fb_exit
	#define GET_dtu_setdateandtime__fb_exit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dtu_setdateandtime__fb_exit(p0) 
	#define CHK_dtu_setdateandtime__fb_exit  FALSE
	#define EXP_dtu_setdateandtime__fb_exit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dtu_setdateandtime__fb_exit
	#define EXT_dtu_setdateandtime__fb_exit
	#define GET_dtu_setdateandtime__fb_exit(fl)  CAL_CMGETAPI( "dtu_setdateandtime__fb_exit" ) 
	#define CAL_dtu_setdateandtime__fb_exit  dtu_setdateandtime__fb_exit
	#define CHK_dtu_setdateandtime__fb_exit  TRUE
	#define EXP_dtu_setdateandtime__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_setdateandtime__fb_exit", (RTS_UINTPTR)dtu_setdateandtime__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xF99DA59E), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_dtu_setdateandtime__fb_exit
	#define EXT_dtu_setdateandtime__fb_exit
	#define GET_dtu_setdateandtime__fb_exit(fl)  CAL_CMGETAPI( "dtu_setdateandtime__fb_exit" ) 
	#define CAL_dtu_setdateandtime__fb_exit  dtu_setdateandtime__fb_exit
	#define CHK_dtu_setdateandtime__fb_exit  TRUE
	#define EXP_dtu_setdateandtime__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_setdateandtime__fb_exit", (RTS_UINTPTR)dtu_setdateandtime__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xF99DA59E), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtildtu_setdateandtime__fb_exit
	#define EXT_CmpCAADTUtildtu_setdateandtime__fb_exit
	#define GET_CmpCAADTUtildtu_setdateandtime__fb_exit  ERR_OK
	#define CAL_CmpCAADTUtildtu_setdateandtime__fb_exit  dtu_setdateandtime__fb_exit
	#define CHK_CmpCAADTUtildtu_setdateandtime__fb_exit  TRUE
	#define EXP_CmpCAADTUtildtu_setdateandtime__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_setdateandtime__fb_exit", (RTS_UINTPTR)dtu_setdateandtime__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xF99DA59E), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_dtu_setdateandtime__fb_exit
	#define EXT_dtu_setdateandtime__fb_exit
	#define GET_dtu_setdateandtime__fb_exit(fl)  CAL_CMGETAPI( "dtu_setdateandtime__fb_exit" ) 
	#define CAL_dtu_setdateandtime__fb_exit  dtu_setdateandtime__fb_exit
	#define CHK_dtu_setdateandtime__fb_exit  TRUE
	#define EXP_dtu_setdateandtime__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_setdateandtime__fb_exit", (RTS_UINTPTR)dtu_setdateandtime__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xF99DA59E), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_dtu_setdateandtime__fb_exit  PFDTU_SETDATEANDTIME__FB_EXIT_IEC pfdtu_setdateandtime__fb_exit;
	#define EXT_dtu_setdateandtime__fb_exit  extern PFDTU_SETDATEANDTIME__FB_EXIT_IEC pfdtu_setdateandtime__fb_exit;
	#define GET_dtu_setdateandtime__fb_exit(fl)  s_pfCMGetAPI2( "dtu_setdateandtime__fb_exit", (RTS_VOID_FCTPTR *)&pfdtu_setdateandtime__fb_exit, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xF99DA59E), 0x03050500)
	#define CAL_dtu_setdateandtime__fb_exit  pfdtu_setdateandtime__fb_exit
	#define CHK_dtu_setdateandtime__fb_exit  (pfdtu_setdateandtime__fb_exit != NULL)
	#define EXP_dtu_setdateandtime__fb_exit   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_setdateandtime__fb_exit", (RTS_UINTPTR)dtu_setdateandtime__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xF99DA59E), 0x03050500) 
#endif


/**
 * <description>dtu_settimezoneinformation__main</description>
 */
typedef struct tagdtu_settimezoneinformation_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	CAA_BOOL xExecute;					/* VAR_INPUT */	/* Rising edge: Action start
							Falling edge: Resets outputs
							If a falling edge occurs before the function block has completed its action, the outputs operate
							in the usual manner and are only reset if either the action is completed or
							in the event of an error. In this case, the corresponding output values (xDone, xError, iError)
							are present at the outputs for exactly one cycle. */
	RTCLK_TIME_ZONE_INFO tziInfo;		/* VAR_INPUT */	
	CAA_BOOL xDone;						/* VAR_OUTPUT */	/* Action successfully completed */
	CAA_BOOL xBusy;						/* VAR_OUTPUT */	/* Function block active */
	CAA_BOOL xError;					/* VAR_OUTPUT */	/* TRUE: error occurred, function block aborts action
							FALSE: no error */
	CAA_ERROR eError;					/* VAR_OUTPUT */	
	CAA_BOOL xPreviousExecute;			/* Local variable */	/* value of xExecute in previous cycle */
	CAA_BOOL xPreviousAbortInProgress;	/* Local variable */	/* value of xAbortInPrograss in previous cycle */
	CAA_BOOL xAbortInProgress;			/* Local variable */	/* TRUE: abort is processed
											FALSE: abort is done */
	RTS_IEC_INT iError;					/* Local variable */	/* Local library error ID is transfered to eError by the concrete implementation */
	CAA_HANDLE hJob;					/* Local variable */	/* specific vars */
	DTU_SETTIMEZONEINFORMATION_PARAMS *pSetTimeZoneInformationParams;	/* Local variable */	
	ASM_STATE StateJob;					/* Local variable */	
	RTS_IEC_XWORD dwEtrigClass;			/* Local variable */	
} dtu_settimezoneinformation_struct;

/**
 * <description>dtu_settimezoneinformation_fb_init</description>
 */
typedef struct tagdtu_settimezoneinformation_fb_init_struct
{
	dtu_settimezoneinformation_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInitRetains;				/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Init;					/* VAR_OUTPUT */	
} dtu_settimezoneinformation_fb_init_struct;

void CDECL CDECL_EXT dtu_settimezoneinformation__fb_init(dtu_settimezoneinformation_fb_init_struct *p);
typedef void (CDECL CDECL_EXT* PFDTU_SETTIMEZONEINFORMATION__FB_INIT_IEC) (dtu_settimezoneinformation_fb_init_struct *p);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_SETTIMEZONEINFORMATION__FB_INIT_NOTIMPLEMENTED)
	#define USE_dtu_settimezoneinformation__fb_init
	#define EXT_dtu_settimezoneinformation__fb_init
	#define GET_dtu_settimezoneinformation__fb_init(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dtu_settimezoneinformation__fb_init(p0) 
	#define CHK_dtu_settimezoneinformation__fb_init  FALSE
	#define EXP_dtu_settimezoneinformation__fb_init  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dtu_settimezoneinformation__fb_init
	#define EXT_dtu_settimezoneinformation__fb_init
	#define GET_dtu_settimezoneinformation__fb_init(fl)  CAL_CMGETAPI( "dtu_settimezoneinformation__fb_init" ) 
	#define CAL_dtu_settimezoneinformation__fb_init  dtu_settimezoneinformation__fb_init
	#define CHK_dtu_settimezoneinformation__fb_init  TRUE
	#define EXP_dtu_settimezoneinformation__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_settimezoneinformation__fb_init", (RTS_UINTPTR)dtu_settimezoneinformation__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0x4088D487), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_dtu_settimezoneinformation__fb_init
	#define EXT_dtu_settimezoneinformation__fb_init
	#define GET_dtu_settimezoneinformation__fb_init(fl)  CAL_CMGETAPI( "dtu_settimezoneinformation__fb_init" ) 
	#define CAL_dtu_settimezoneinformation__fb_init  dtu_settimezoneinformation__fb_init
	#define CHK_dtu_settimezoneinformation__fb_init  TRUE
	#define EXP_dtu_settimezoneinformation__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_settimezoneinformation__fb_init", (RTS_UINTPTR)dtu_settimezoneinformation__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0x4088D487), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtildtu_settimezoneinformation__fb_init
	#define EXT_CmpCAADTUtildtu_settimezoneinformation__fb_init
	#define GET_CmpCAADTUtildtu_settimezoneinformation__fb_init  ERR_OK
	#define CAL_CmpCAADTUtildtu_settimezoneinformation__fb_init  dtu_settimezoneinformation__fb_init
	#define CHK_CmpCAADTUtildtu_settimezoneinformation__fb_init  TRUE
	#define EXP_CmpCAADTUtildtu_settimezoneinformation__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_settimezoneinformation__fb_init", (RTS_UINTPTR)dtu_settimezoneinformation__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0x4088D487), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_dtu_settimezoneinformation__fb_init
	#define EXT_dtu_settimezoneinformation__fb_init
	#define GET_dtu_settimezoneinformation__fb_init(fl)  CAL_CMGETAPI( "dtu_settimezoneinformation__fb_init" ) 
	#define CAL_dtu_settimezoneinformation__fb_init  dtu_settimezoneinformation__fb_init
	#define CHK_dtu_settimezoneinformation__fb_init  TRUE
	#define EXP_dtu_settimezoneinformation__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_settimezoneinformation__fb_init", (RTS_UINTPTR)dtu_settimezoneinformation__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0x4088D487), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_dtu_settimezoneinformation__fb_init  PFDTU_SETTIMEZONEINFORMATION__FB_INIT_IEC pfdtu_settimezoneinformation__fb_init;
	#define EXT_dtu_settimezoneinformation__fb_init  extern PFDTU_SETTIMEZONEINFORMATION__FB_INIT_IEC pfdtu_settimezoneinformation__fb_init;
	#define GET_dtu_settimezoneinformation__fb_init(fl)  s_pfCMGetAPI2( "dtu_settimezoneinformation__fb_init", (RTS_VOID_FCTPTR *)&pfdtu_settimezoneinformation__fb_init, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x4088D487), 0x03050500)
	#define CAL_dtu_settimezoneinformation__fb_init  pfdtu_settimezoneinformation__fb_init
	#define CHK_dtu_settimezoneinformation__fb_init  (pfdtu_settimezoneinformation__fb_init != NULL)
	#define EXP_dtu_settimezoneinformation__fb_init   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_settimezoneinformation__fb_init", (RTS_UINTPTR)dtu_settimezoneinformation__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0x4088D487), 0x03050500) 
#endif


/**
 * <description>dtu_settimezoneinformation_main</description>
 */
typedef struct tagdtu_settimezoneinformation_main_struct
{
	dtu_settimezoneinformation_struct *pInstance;	/* VAR_INPUT */	
} dtu_settimezoneinformation_main_struct;

void CDECL CDECL_EXT dtu_settimezoneinformation__main(dtu_settimezoneinformation_main_struct *p);
typedef void (CDECL CDECL_EXT* PFDTU_SETTIMEZONEINFORMATION__MAIN_IEC) (dtu_settimezoneinformation_main_struct *p);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_SETTIMEZONEINFORMATION__MAIN_NOTIMPLEMENTED)
	#define USE_dtu_settimezoneinformation__main
	#define EXT_dtu_settimezoneinformation__main
	#define GET_dtu_settimezoneinformation__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dtu_settimezoneinformation__main(p0) 
	#define CHK_dtu_settimezoneinformation__main  FALSE
	#define EXP_dtu_settimezoneinformation__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dtu_settimezoneinformation__main
	#define EXT_dtu_settimezoneinformation__main
	#define GET_dtu_settimezoneinformation__main(fl)  CAL_CMGETAPI( "dtu_settimezoneinformation__main" ) 
	#define CAL_dtu_settimezoneinformation__main  dtu_settimezoneinformation__main
	#define CHK_dtu_settimezoneinformation__main  TRUE
	#define EXP_dtu_settimezoneinformation__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_settimezoneinformation__main", (RTS_UINTPTR)dtu_settimezoneinformation__main, 1, RTSITF_GET_SIGNATURE(0, 0xCDAC022F), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_dtu_settimezoneinformation__main
	#define EXT_dtu_settimezoneinformation__main
	#define GET_dtu_settimezoneinformation__main(fl)  CAL_CMGETAPI( "dtu_settimezoneinformation__main" ) 
	#define CAL_dtu_settimezoneinformation__main  dtu_settimezoneinformation__main
	#define CHK_dtu_settimezoneinformation__main  TRUE
	#define EXP_dtu_settimezoneinformation__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_settimezoneinformation__main", (RTS_UINTPTR)dtu_settimezoneinformation__main, 1, RTSITF_GET_SIGNATURE(0, 0xCDAC022F), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtildtu_settimezoneinformation__main
	#define EXT_CmpCAADTUtildtu_settimezoneinformation__main
	#define GET_CmpCAADTUtildtu_settimezoneinformation__main  ERR_OK
	#define CAL_CmpCAADTUtildtu_settimezoneinformation__main  dtu_settimezoneinformation__main
	#define CHK_CmpCAADTUtildtu_settimezoneinformation__main  TRUE
	#define EXP_CmpCAADTUtildtu_settimezoneinformation__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_settimezoneinformation__main", (RTS_UINTPTR)dtu_settimezoneinformation__main, 1, RTSITF_GET_SIGNATURE(0, 0xCDAC022F), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_dtu_settimezoneinformation__main
	#define EXT_dtu_settimezoneinformation__main
	#define GET_dtu_settimezoneinformation__main(fl)  CAL_CMGETAPI( "dtu_settimezoneinformation__main" ) 
	#define CAL_dtu_settimezoneinformation__main  dtu_settimezoneinformation__main
	#define CHK_dtu_settimezoneinformation__main  TRUE
	#define EXP_dtu_settimezoneinformation__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_settimezoneinformation__main", (RTS_UINTPTR)dtu_settimezoneinformation__main, 1, RTSITF_GET_SIGNATURE(0, 0xCDAC022F), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_dtu_settimezoneinformation__main  PFDTU_SETTIMEZONEINFORMATION__MAIN_IEC pfdtu_settimezoneinformation__main;
	#define EXT_dtu_settimezoneinformation__main  extern PFDTU_SETTIMEZONEINFORMATION__MAIN_IEC pfdtu_settimezoneinformation__main;
	#define GET_dtu_settimezoneinformation__main(fl)  s_pfCMGetAPI2( "dtu_settimezoneinformation__main", (RTS_VOID_FCTPTR *)&pfdtu_settimezoneinformation__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xCDAC022F), 0x03050500)
	#define CAL_dtu_settimezoneinformation__main  pfdtu_settimezoneinformation__main
	#define CHK_dtu_settimezoneinformation__main  (pfdtu_settimezoneinformation__main != NULL)
	#define EXP_dtu_settimezoneinformation__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_settimezoneinformation__main", (RTS_UINTPTR)dtu_settimezoneinformation__main, 1, RTSITF_GET_SIGNATURE(0, 0xCDAC022F), 0x03050500) 
#endif


/**
 * <description>dtu_settimezoneinformation_fb_exit</description>
 */
typedef struct tagdtu_settimezoneinformation_fb_exit_struct
{
	dtu_settimezoneinformation_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Exit;					/* VAR_OUTPUT */	
} dtu_settimezoneinformation_fb_exit_struct;

void CDECL CDECL_EXT dtu_settimezoneinformation__fb_exit(dtu_settimezoneinformation_fb_exit_struct *p);
typedef void (CDECL CDECL_EXT* PFDTU_SETTIMEZONEINFORMATION__FB_EXIT_IEC) (dtu_settimezoneinformation_fb_exit_struct *p);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_SETTIMEZONEINFORMATION__FB_EXIT_NOTIMPLEMENTED)
	#define USE_dtu_settimezoneinformation__fb_exit
	#define EXT_dtu_settimezoneinformation__fb_exit
	#define GET_dtu_settimezoneinformation__fb_exit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dtu_settimezoneinformation__fb_exit(p0) 
	#define CHK_dtu_settimezoneinformation__fb_exit  FALSE
	#define EXP_dtu_settimezoneinformation__fb_exit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dtu_settimezoneinformation__fb_exit
	#define EXT_dtu_settimezoneinformation__fb_exit
	#define GET_dtu_settimezoneinformation__fb_exit(fl)  CAL_CMGETAPI( "dtu_settimezoneinformation__fb_exit" ) 
	#define CAL_dtu_settimezoneinformation__fb_exit  dtu_settimezoneinformation__fb_exit
	#define CHK_dtu_settimezoneinformation__fb_exit  TRUE
	#define EXP_dtu_settimezoneinformation__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_settimezoneinformation__fb_exit", (RTS_UINTPTR)dtu_settimezoneinformation__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xCAE0874A), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_dtu_settimezoneinformation__fb_exit
	#define EXT_dtu_settimezoneinformation__fb_exit
	#define GET_dtu_settimezoneinformation__fb_exit(fl)  CAL_CMGETAPI( "dtu_settimezoneinformation__fb_exit" ) 
	#define CAL_dtu_settimezoneinformation__fb_exit  dtu_settimezoneinformation__fb_exit
	#define CHK_dtu_settimezoneinformation__fb_exit  TRUE
	#define EXP_dtu_settimezoneinformation__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_settimezoneinformation__fb_exit", (RTS_UINTPTR)dtu_settimezoneinformation__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xCAE0874A), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtildtu_settimezoneinformation__fb_exit
	#define EXT_CmpCAADTUtildtu_settimezoneinformation__fb_exit
	#define GET_CmpCAADTUtildtu_settimezoneinformation__fb_exit  ERR_OK
	#define CAL_CmpCAADTUtildtu_settimezoneinformation__fb_exit  dtu_settimezoneinformation__fb_exit
	#define CHK_CmpCAADTUtildtu_settimezoneinformation__fb_exit  TRUE
	#define EXP_CmpCAADTUtildtu_settimezoneinformation__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_settimezoneinformation__fb_exit", (RTS_UINTPTR)dtu_settimezoneinformation__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xCAE0874A), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_dtu_settimezoneinformation__fb_exit
	#define EXT_dtu_settimezoneinformation__fb_exit
	#define GET_dtu_settimezoneinformation__fb_exit(fl)  CAL_CMGETAPI( "dtu_settimezoneinformation__fb_exit" ) 
	#define CAL_dtu_settimezoneinformation__fb_exit  dtu_settimezoneinformation__fb_exit
	#define CHK_dtu_settimezoneinformation__fb_exit  TRUE
	#define EXP_dtu_settimezoneinformation__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_settimezoneinformation__fb_exit", (RTS_UINTPTR)dtu_settimezoneinformation__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xCAE0874A), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_dtu_settimezoneinformation__fb_exit  PFDTU_SETTIMEZONEINFORMATION__FB_EXIT_IEC pfdtu_settimezoneinformation__fb_exit;
	#define EXT_dtu_settimezoneinformation__fb_exit  extern PFDTU_SETTIMEZONEINFORMATION__FB_EXIT_IEC pfdtu_settimezoneinformation__fb_exit;
	#define GET_dtu_settimezoneinformation__fb_exit(fl)  s_pfCMGetAPI2( "dtu_settimezoneinformation__fb_exit", (RTS_VOID_FCTPTR *)&pfdtu_settimezoneinformation__fb_exit, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xCAE0874A), 0x03050500)
	#define CAL_dtu_settimezoneinformation__fb_exit  pfdtu_settimezoneinformation__fb_exit
	#define CHK_dtu_settimezoneinformation__fb_exit  (pfdtu_settimezoneinformation__fb_exit != NULL)
	#define EXP_dtu_settimezoneinformation__fb_exit   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_settimezoneinformation__fb_exit", (RTS_UINTPTR)dtu_settimezoneinformation__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xCAE0874A), 0x03050500) 
#endif


/**
 * <description>dtu_todconcat</description>
 */
typedef struct tagdtu_todconcat_struct
{
	RTS_IEC_UINT uiHour;				/* VAR_INPUT */	/* 0..23 */
	RTS_IEC_UINT uiMinute;				/* VAR_INPUT */	/* 0..59 */
	RTS_IEC_UINT uiSecond;				/* VAR_INPUT */	/* 0..59 */
	RTS_IEC_UINT uiMillisecond;			/* VAR_INPUT */	/* 0..999 */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	RTS_IEC_TIME_OF_DAY DTU_TODConcat;	/* VAR_OUTPUT */	/* todTime */
} dtu_todconcat_struct;

void CDECL CDECL_EXT dtu_todconcat(dtu_todconcat_struct *p);
typedef void (CDECL CDECL_EXT* PFDTU_TODCONCAT_IEC) (dtu_todconcat_struct *p);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_TODCONCAT_NOTIMPLEMENTED)
	#define USE_dtu_todconcat
	#define EXT_dtu_todconcat
	#define GET_dtu_todconcat(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dtu_todconcat(p0) 
	#define CHK_dtu_todconcat  FALSE
	#define EXP_dtu_todconcat  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dtu_todconcat
	#define EXT_dtu_todconcat
	#define GET_dtu_todconcat(fl)  CAL_CMGETAPI( "dtu_todconcat" ) 
	#define CAL_dtu_todconcat  dtu_todconcat
	#define CHK_dtu_todconcat  TRUE
	#define EXP_dtu_todconcat  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_todconcat", (RTS_UINTPTR)dtu_todconcat, 1, RTSITF_GET_SIGNATURE(0, 0xB369CA69), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_dtu_todconcat
	#define EXT_dtu_todconcat
	#define GET_dtu_todconcat(fl)  CAL_CMGETAPI( "dtu_todconcat" ) 
	#define CAL_dtu_todconcat  dtu_todconcat
	#define CHK_dtu_todconcat  TRUE
	#define EXP_dtu_todconcat  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_todconcat", (RTS_UINTPTR)dtu_todconcat, 1, RTSITF_GET_SIGNATURE(0, 0xB369CA69), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtildtu_todconcat
	#define EXT_CmpCAADTUtildtu_todconcat
	#define GET_CmpCAADTUtildtu_todconcat  ERR_OK
	#define CAL_CmpCAADTUtildtu_todconcat  dtu_todconcat
	#define CHK_CmpCAADTUtildtu_todconcat  TRUE
	#define EXP_CmpCAADTUtildtu_todconcat  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_todconcat", (RTS_UINTPTR)dtu_todconcat, 1, RTSITF_GET_SIGNATURE(0, 0xB369CA69), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_dtu_todconcat
	#define EXT_dtu_todconcat
	#define GET_dtu_todconcat(fl)  CAL_CMGETAPI( "dtu_todconcat" ) 
	#define CAL_dtu_todconcat  dtu_todconcat
	#define CHK_dtu_todconcat  TRUE
	#define EXP_dtu_todconcat  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_todconcat", (RTS_UINTPTR)dtu_todconcat, 1, RTSITF_GET_SIGNATURE(0, 0xB369CA69), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_dtu_todconcat  PFDTU_TODCONCAT_IEC pfdtu_todconcat;
	#define EXT_dtu_todconcat  extern PFDTU_TODCONCAT_IEC pfdtu_todconcat;
	#define GET_dtu_todconcat(fl)  s_pfCMGetAPI2( "dtu_todconcat", (RTS_VOID_FCTPTR *)&pfdtu_todconcat, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xB369CA69), 0x03050500)
	#define CAL_dtu_todconcat  pfdtu_todconcat
	#define CHK_dtu_todconcat  (pfdtu_todconcat != NULL)
	#define EXP_dtu_todconcat   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_todconcat", (RTS_UINTPTR)dtu_todconcat, 1, RTSITF_GET_SIGNATURE(0, 0xB369CA69), 0x03050500) 
#endif


/**
 * <description>dtu_todsplit</description>
 */
typedef struct tagdtu_todsplit_struct
{
	RTS_IEC_TIME_OF_DAY todTime;		/* VAR_INPUT */	
	RTS_IEC_UINT *puiHour;				/* VAR_INPUT */	/* 0..23 */
	RTS_IEC_UINT *puiMinute;			/* VAR_INPUT */	/* 0..59 */
	RTS_IEC_UINT *puiSecond;			/* VAR_INPUT */	/* 0..59 */
	RTS_IEC_UINT *puiMillisecond;		/* VAR_INPUT */	/* 0..999 */
	CAA_ERROR DTU_TODSplit;				/* VAR_OUTPUT */	
} dtu_todsplit_struct;

void CDECL CDECL_EXT dtu_todsplit(dtu_todsplit_struct *p);
typedef void (CDECL CDECL_EXT* PFDTU_TODSPLIT_IEC) (dtu_todsplit_struct *p);
#if defined(CMPCAADTUTIL_NOTIMPLEMENTED) || defined(DTU_TODSPLIT_NOTIMPLEMENTED)
	#define USE_dtu_todsplit
	#define EXT_dtu_todsplit
	#define GET_dtu_todsplit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_dtu_todsplit(p0) 
	#define CHK_dtu_todsplit  FALSE
	#define EXP_dtu_todsplit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_dtu_todsplit
	#define EXT_dtu_todsplit
	#define GET_dtu_todsplit(fl)  CAL_CMGETAPI( "dtu_todsplit" ) 
	#define CAL_dtu_todsplit  dtu_todsplit
	#define CHK_dtu_todsplit  TRUE
	#define EXP_dtu_todsplit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_todsplit", (RTS_UINTPTR)dtu_todsplit, 1, RTSITF_GET_SIGNATURE(0, 0x96C543F6), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAADTUTIL_EXTERNAL)
	#define USE_dtu_todsplit
	#define EXT_dtu_todsplit
	#define GET_dtu_todsplit(fl)  CAL_CMGETAPI( "dtu_todsplit" ) 
	#define CAL_dtu_todsplit  dtu_todsplit
	#define CHK_dtu_todsplit  TRUE
	#define EXP_dtu_todsplit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_todsplit", (RTS_UINTPTR)dtu_todsplit, 1, RTSITF_GET_SIGNATURE(0, 0x96C543F6), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAADTUtildtu_todsplit
	#define EXT_CmpCAADTUtildtu_todsplit
	#define GET_CmpCAADTUtildtu_todsplit  ERR_OK
	#define CAL_CmpCAADTUtildtu_todsplit  dtu_todsplit
	#define CHK_CmpCAADTUtildtu_todsplit  TRUE
	#define EXP_CmpCAADTUtildtu_todsplit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_todsplit", (RTS_UINTPTR)dtu_todsplit, 1, RTSITF_GET_SIGNATURE(0, 0x96C543F6), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_dtu_todsplit
	#define EXT_dtu_todsplit
	#define GET_dtu_todsplit(fl)  CAL_CMGETAPI( "dtu_todsplit" ) 
	#define CAL_dtu_todsplit  dtu_todsplit
	#define CHK_dtu_todsplit  TRUE
	#define EXP_dtu_todsplit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_todsplit", (RTS_UINTPTR)dtu_todsplit, 1, RTSITF_GET_SIGNATURE(0, 0x96C543F6), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_dtu_todsplit  PFDTU_TODSPLIT_IEC pfdtu_todsplit;
	#define EXT_dtu_todsplit  extern PFDTU_TODSPLIT_IEC pfdtu_todsplit;
	#define GET_dtu_todsplit(fl)  s_pfCMGetAPI2( "dtu_todsplit", (RTS_VOID_FCTPTR *)&pfdtu_todsplit, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x96C543F6), 0x03050500)
	#define CAL_dtu_todsplit  pfdtu_todsplit
	#define CHK_dtu_todsplit  (pfdtu_todsplit != NULL)
	#define EXP_dtu_todsplit   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"dtu_todsplit", (RTS_UINTPTR)dtu_todsplit, 1, RTSITF_GET_SIGNATURE(0, 0x96C543F6), 0x03050500) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/



typedef struct
{
	IBase_C *pBase;
	PFDTU_WORKERINIT IDTU_WorkerInit;
 	PFDTU_WORKEREXIT IDTU_WorkerExit;
 	PFDTU_GETDATEANDTIME IDTU_GetDateAndTime;
 	PFDTU_GETDATEANDTIME_FB_INIT IDTU_GetDateAndTime_FB_Init;
 	PFDTU_GETDATEANDTIME_FB_EXIT IDTU_GetDateAndTime_FB_Exit;
 	PFDTU_SETDATEANDTIME IDTU_SetDateAndTime;
 	PFDTU_SETDATEANDTIME_FB_INIT IDTU_SetDateAndTime_FB_Init;
 	PFDTU_SETDATEANDTIME_FB_EXIT IDTU_SetDateAndTime_FB_Exit;
 	PFDTU_GETTIMEZONEINFORMATION IDTU_GetTimeZoneInformation;
 	PFDTU_GETTIMEZONEINFORMATION_FB_INIT IDTU_GetTimeZoneInformation_FB_Init;
 	PFDTU_GETTIMEZONEINFORMATION_FB_EXIT IDTU_GetTimeZoneInformation_FB_Exit;
 	PFDTU_SETTIMEZONEINFORMATION IDTU_SetTimeZoneInformation;
 	PFDTU_SETTIMEZONEINFORMATION_FB_INIT IDTU_SetTimeZoneInformation_FB_Init;
 	PFDTU_SETTIMEZONEINFORMATION_FB_EXIT IDTU_SetTimeZoneInformation_FB_Exit;
 	PFDTU_DATECONCAT IDTU_DateConcat;
 	PFDTU_DATESPLIT IDTU_DateSplit;
 	PFDTU_DTCONCAT IDTU_DTConcat;
 	PFDTU_DTSPLIT IDTU_DTSplit;
 	PFDTU_TODCONCAT IDTU_TODConcat;
 	PFDTU_TODSPLIT IDTU_TODSplit;
 	PFDTU_GETDAYOFWEEK IDTU_GetDayOfWeek;
 	PFDTU_GETSUPPLIERVERSION IDTU_GetSupplierVersion;
 } ICmpCAADTUtil_C;

#ifdef CPLUSPLUS
class ICmpCAADTUtil : public IBase
{
	public:
		virtual CAA_ERROR CDECL IDTU_WorkerInit(void) =0;
		virtual CAA_ERROR CDECL IDTU_WorkerExit(void) =0;
		virtual void CDECL IDTU_GetDateAndTime(dtu_getdateandtime_typ* inst) =0;
		virtual CAA_BOOL CDECL IDTU_GetDateAndTime_FB_Init(CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, dtu_getdateandtime_typ* inst) =0;
		virtual CAA_BOOL CDECL IDTU_GetDateAndTime_FB_Exit(CAA_BOOL bInCopyCode, dtu_getdateandtime_typ* inst) =0;
		virtual void CDECL IDTU_SetDateAndTime(dtu_setdateandtime_typ* inst) =0;
		virtual CAA_BOOL CDECL IDTU_SetDateAndTime_FB_Init(CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, dtu_setdateandtime_typ* inst) =0;
		virtual CAA_BOOL CDECL IDTU_SetDateAndTime_FB_Exit(CAA_BOOL bInCopyCode, dtu_setdateandtime_typ* inst) =0;
		virtual void CDECL IDTU_GetTimeZoneInformation(dtu_gettimezoneinformation_typ* inst) =0;
		virtual CAA_BOOL CDECL IDTU_GetTimeZoneInformation_FB_Init(CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, dtu_gettimezoneinformation_typ* inst) =0;
		virtual CAA_BOOL CDECL IDTU_GetTimeZoneInformation_FB_Exit(CAA_BOOL bInCopyCode, dtu_gettimezoneinformation_typ* inst) =0;
		virtual void CDECL IDTU_SetTimeZoneInformation(dtu_settimezoneinformation_typ* inst) =0;
		virtual CAA_BOOL CDECL IDTU_SetTimeZoneInformation_FB_Init(CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, dtu_settimezoneinformation_typ* inst) =0;
		virtual CAA_BOOL CDECL IDTU_SetTimeZoneInformation_FB_Exit(CAA_BOOL bInCopyCode, dtu_settimezoneinformation_typ* inst) =0;
		virtual unsigned long CDECL IDTU_DateConcat(unsigned short usYear, unsigned short usMonth, unsigned short usDay, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL IDTU_DateSplit(unsigned long ulDate, unsigned short* pusYear, unsigned short* pusMonth, unsigned short* pusDay) =0;
		virtual unsigned long CDECL IDTU_DTConcat(unsigned short usYear, unsigned short usMonth, unsigned short usDay, unsigned short usHour, unsigned short usMinute, unsigned short usSecond, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL IDTU_DTSplit(unsigned long ulDateAndTime, unsigned short* pusYear, unsigned short* pusMonth, unsigned short* pusDay, unsigned short* pusHour, unsigned short* pusMinute, unsigned short* pusSecond) =0;
		virtual unsigned long CDECL IDTU_TODConcat(unsigned short usHour, unsigned short usMinute, unsigned short usSecond, unsigned short usMillisecond, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL IDTU_TODSplit(unsigned long ulTime, unsigned short* pusHour, unsigned short* pusMinute, unsigned short* pusSecond, unsigned short* pusMillisecond) =0;
		virtual CAA_ENUM CDECL IDTU_GetDayOfWeek(unsigned long ulDate, CAA_ERROR* peError) =0;
		virtual unsigned short CDECL IDTU_GetSupplierVersion(CAA_BOOL xDummy) =0;
};
	#ifndef ITF_CmpCAADTUtil
		#define ITF_CmpCAADTUtil static ICmpCAADTUtil *pICmpCAADTUtil = NULL;
	#endif
	#define EXTITF_CmpCAADTUtil
#else	/*CPLUSPLUS*/
	typedef ICmpCAADTUtil_C		ICmpCAADTUtil;
	#ifndef ITF_CmpCAADTUtil
		#define ITF_CmpCAADTUtil
	#endif
	#define EXTITF_CmpCAADTUtil
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCAADTUTILITF_H_*/
