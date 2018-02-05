 
	
	
#ifndef _CMPCAAREALTIMECLOCKITF_H_
#define _CMPCAAREALTIMECLOCKITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAARealTimeClock.h"
#include "CAABehaviourModel.h"
#include "CAAAsyncMan.h"
#include "CAAMemBlockMan.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Interface functions of CAA Real Time Clock*/
CAA_ERROR CDECL RTCLK_WorkerInit(void);
typedef CAA_ERROR (CDECL * PFRTCLK_WORKERINIT) (void);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_WORKERINIT_NOTIMPLEMENTED)
	#define USE_RTCLK_WorkerInit
	#define EXT_RTCLK_WorkerInit
	#define GET_RTCLK_WorkerInit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RTCLK_WorkerInit()  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_RTCLK_WorkerInit  FALSE
	#define EXP_RTCLK_WorkerInit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RTCLK_WorkerInit
	#define EXT_RTCLK_WorkerInit
	#define GET_RTCLK_WorkerInit(fl)  CAL_CMGETAPI( "RTCLK_WorkerInit" ) 
	#define CAL_RTCLK_WorkerInit  RTCLK_WorkerInit
	#define CHK_RTCLK_WorkerInit  TRUE
	#define EXP_RTCLK_WorkerInit  CAL_CMEXPAPI( "RTCLK_WorkerInit" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_RTCLK_WorkerInit
	#define EXT_RTCLK_WorkerInit
	#define GET_RTCLK_WorkerInit(fl)  CAL_CMGETAPI( "RTCLK_WorkerInit" ) 
	#define CAL_RTCLK_WorkerInit  RTCLK_WorkerInit
	#define CHK_RTCLK_WorkerInit  TRUE
	#define EXP_RTCLK_WorkerInit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_WorkerInit", (RTS_UINTPTR)RTCLK_WorkerInit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockRTCLK_WorkerInit
	#define EXT_CmpCAARealTimeClockRTCLK_WorkerInit
	#define GET_CmpCAARealTimeClockRTCLK_WorkerInit  ERR_OK
	#define CAL_CmpCAARealTimeClockRTCLK_WorkerInit pICmpCAARealTimeClock->IRTCLK_WorkerInit
	#define CHK_CmpCAARealTimeClockRTCLK_WorkerInit (pICmpCAARealTimeClock != NULL)
	#define EXP_CmpCAARealTimeClockRTCLK_WorkerInit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RTCLK_WorkerInit
	#define EXT_RTCLK_WorkerInit
	#define GET_RTCLK_WorkerInit(fl)  CAL_CMGETAPI( "RTCLK_WorkerInit" ) 
	#define CAL_RTCLK_WorkerInit pICmpCAARealTimeClock->IRTCLK_WorkerInit
	#define CHK_RTCLK_WorkerInit (pICmpCAARealTimeClock != NULL)
	#define EXP_RTCLK_WorkerInit  CAL_CMEXPAPI( "RTCLK_WorkerInit" ) 
#else /* DYNAMIC_LINK */
	#define USE_RTCLK_WorkerInit  PFRTCLK_WORKERINIT pfRTCLK_WorkerInit;
	#define EXT_RTCLK_WorkerInit  extern PFRTCLK_WORKERINIT pfRTCLK_WorkerInit;
	#define GET_RTCLK_WorkerInit(fl)  s_pfCMGetAPI2( "RTCLK_WorkerInit", (RTS_VOID_FCTPTR *)&pfRTCLK_WorkerInit, (fl), 0, 0)
	#define CAL_RTCLK_WorkerInit  pfRTCLK_WorkerInit
	#define CHK_RTCLK_WorkerInit  (pfRTCLK_WorkerInit != NULL)
	#define EXP_RTCLK_WorkerInit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_WorkerInit", (RTS_UINTPTR)RTCLK_WorkerInit, 0, 0) 
#endif



CAA_ERROR CDECL RTCLK_WorkerExit(void);
typedef CAA_ERROR (CDECL * PFRTCLK_WORKEREXIT) (void);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_WORKEREXIT_NOTIMPLEMENTED)
	#define USE_RTCLK_WorkerExit
	#define EXT_RTCLK_WorkerExit
	#define GET_RTCLK_WorkerExit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RTCLK_WorkerExit()  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_RTCLK_WorkerExit  FALSE
	#define EXP_RTCLK_WorkerExit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RTCLK_WorkerExit
	#define EXT_RTCLK_WorkerExit
	#define GET_RTCLK_WorkerExit(fl)  CAL_CMGETAPI( "RTCLK_WorkerExit" ) 
	#define CAL_RTCLK_WorkerExit  RTCLK_WorkerExit
	#define CHK_RTCLK_WorkerExit  TRUE
	#define EXP_RTCLK_WorkerExit  CAL_CMEXPAPI( "RTCLK_WorkerExit" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_RTCLK_WorkerExit
	#define EXT_RTCLK_WorkerExit
	#define GET_RTCLK_WorkerExit(fl)  CAL_CMGETAPI( "RTCLK_WorkerExit" ) 
	#define CAL_RTCLK_WorkerExit  RTCLK_WorkerExit
	#define CHK_RTCLK_WorkerExit  TRUE
	#define EXP_RTCLK_WorkerExit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_WorkerExit", (RTS_UINTPTR)RTCLK_WorkerExit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockRTCLK_WorkerExit
	#define EXT_CmpCAARealTimeClockRTCLK_WorkerExit
	#define GET_CmpCAARealTimeClockRTCLK_WorkerExit  ERR_OK
	#define CAL_CmpCAARealTimeClockRTCLK_WorkerExit pICmpCAARealTimeClock->IRTCLK_WorkerExit
	#define CHK_CmpCAARealTimeClockRTCLK_WorkerExit (pICmpCAARealTimeClock != NULL)
	#define EXP_CmpCAARealTimeClockRTCLK_WorkerExit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RTCLK_WorkerExit
	#define EXT_RTCLK_WorkerExit
	#define GET_RTCLK_WorkerExit(fl)  CAL_CMGETAPI( "RTCLK_WorkerExit" ) 
	#define CAL_RTCLK_WorkerExit pICmpCAARealTimeClock->IRTCLK_WorkerExit
	#define CHK_RTCLK_WorkerExit (pICmpCAARealTimeClock != NULL)
	#define EXP_RTCLK_WorkerExit  CAL_CMEXPAPI( "RTCLK_WorkerExit" ) 
#else /* DYNAMIC_LINK */
	#define USE_RTCLK_WorkerExit  PFRTCLK_WORKEREXIT pfRTCLK_WorkerExit;
	#define EXT_RTCLK_WorkerExit  extern PFRTCLK_WORKEREXIT pfRTCLK_WorkerExit;
	#define GET_RTCLK_WorkerExit(fl)  s_pfCMGetAPI2( "RTCLK_WorkerExit", (RTS_VOID_FCTPTR *)&pfRTCLK_WorkerExit, (fl), 0, 0)
	#define CAL_RTCLK_WorkerExit  pfRTCLK_WorkerExit
	#define CHK_RTCLK_WorkerExit  (pfRTCLK_WorkerExit != NULL)
	#define EXP_RTCLK_WorkerExit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_WorkerExit", (RTS_UINTPTR)RTCLK_WorkerExit, 0, 0) 
#endif



void CDECL RTCLK_GetDateAndTime(rtclk_getdateandtime_typ* inst);
typedef void (CDECL * PFRTCLK_GETDATEANDTIME) (rtclk_getdateandtime_typ* inst);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_GETDATEANDTIME_NOTIMPLEMENTED)
	#define USE_RTCLK_GetDateAndTime
	#define EXT_RTCLK_GetDateAndTime
	#define GET_RTCLK_GetDateAndTime(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RTCLK_GetDateAndTime(p0)  
	#define CHK_RTCLK_GetDateAndTime  FALSE
	#define EXP_RTCLK_GetDateAndTime  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RTCLK_GetDateAndTime
	#define EXT_RTCLK_GetDateAndTime
	#define GET_RTCLK_GetDateAndTime(fl)  CAL_CMGETAPI( "RTCLK_GetDateAndTime" ) 
	#define CAL_RTCLK_GetDateAndTime  RTCLK_GetDateAndTime
	#define CHK_RTCLK_GetDateAndTime  TRUE
	#define EXP_RTCLK_GetDateAndTime  CAL_CMEXPAPI( "RTCLK_GetDateAndTime" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_RTCLK_GetDateAndTime
	#define EXT_RTCLK_GetDateAndTime
	#define GET_RTCLK_GetDateAndTime(fl)  CAL_CMGETAPI( "RTCLK_GetDateAndTime" ) 
	#define CAL_RTCLK_GetDateAndTime  RTCLK_GetDateAndTime
	#define CHK_RTCLK_GetDateAndTime  TRUE
	#define EXP_RTCLK_GetDateAndTime  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_GetDateAndTime", (RTS_UINTPTR)RTCLK_GetDateAndTime, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockRTCLK_GetDateAndTime
	#define EXT_CmpCAARealTimeClockRTCLK_GetDateAndTime
	#define GET_CmpCAARealTimeClockRTCLK_GetDateAndTime  ERR_OK
	#define CAL_CmpCAARealTimeClockRTCLK_GetDateAndTime pICmpCAARealTimeClock->IRTCLK_GetDateAndTime
	#define CHK_CmpCAARealTimeClockRTCLK_GetDateAndTime (pICmpCAARealTimeClock != NULL)
	#define EXP_CmpCAARealTimeClockRTCLK_GetDateAndTime  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RTCLK_GetDateAndTime
	#define EXT_RTCLK_GetDateAndTime
	#define GET_RTCLK_GetDateAndTime(fl)  CAL_CMGETAPI( "RTCLK_GetDateAndTime" ) 
	#define CAL_RTCLK_GetDateAndTime pICmpCAARealTimeClock->IRTCLK_GetDateAndTime
	#define CHK_RTCLK_GetDateAndTime (pICmpCAARealTimeClock != NULL)
	#define EXP_RTCLK_GetDateAndTime  CAL_CMEXPAPI( "RTCLK_GetDateAndTime" ) 
#else /* DYNAMIC_LINK */
	#define USE_RTCLK_GetDateAndTime  PFRTCLK_GETDATEANDTIME pfRTCLK_GetDateAndTime;
	#define EXT_RTCLK_GetDateAndTime  extern PFRTCLK_GETDATEANDTIME pfRTCLK_GetDateAndTime;
	#define GET_RTCLK_GetDateAndTime(fl)  s_pfCMGetAPI2( "RTCLK_GetDateAndTime", (RTS_VOID_FCTPTR *)&pfRTCLK_GetDateAndTime, (fl), 0, 0)
	#define CAL_RTCLK_GetDateAndTime  pfRTCLK_GetDateAndTime
	#define CHK_RTCLK_GetDateAndTime  (pfRTCLK_GetDateAndTime != NULL)
	#define EXP_RTCLK_GetDateAndTime  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_GetDateAndTime", (RTS_UINTPTR)RTCLK_GetDateAndTime, 0, 0) 
#endif



CAA_BOOL CDECL RTCLK_GetDateAndTime_FB_Init(CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, rtclk_getdateandtime_typ* inst);
typedef CAA_BOOL (CDECL * PFRTCLK_GETDATEANDTIME_FB_INIT) (CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, rtclk_getdateandtime_typ* inst);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_GETDATEANDTIME_FB_INIT_NOTIMPLEMENTED)
	#define USE_RTCLK_GetDateAndTime_FB_Init
	#define EXT_RTCLK_GetDateAndTime_FB_Init
	#define GET_RTCLK_GetDateAndTime_FB_Init(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RTCLK_GetDateAndTime_FB_Init(p0,p1,p2)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_RTCLK_GetDateAndTime_FB_Init  FALSE
	#define EXP_RTCLK_GetDateAndTime_FB_Init  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RTCLK_GetDateAndTime_FB_Init
	#define EXT_RTCLK_GetDateAndTime_FB_Init
	#define GET_RTCLK_GetDateAndTime_FB_Init(fl)  CAL_CMGETAPI( "RTCLK_GetDateAndTime_FB_Init" ) 
	#define CAL_RTCLK_GetDateAndTime_FB_Init  RTCLK_GetDateAndTime_FB_Init
	#define CHK_RTCLK_GetDateAndTime_FB_Init  TRUE
	#define EXP_RTCLK_GetDateAndTime_FB_Init  CAL_CMEXPAPI( "RTCLK_GetDateAndTime_FB_Init" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_RTCLK_GetDateAndTime_FB_Init
	#define EXT_RTCLK_GetDateAndTime_FB_Init
	#define GET_RTCLK_GetDateAndTime_FB_Init(fl)  CAL_CMGETAPI( "RTCLK_GetDateAndTime_FB_Init" ) 
	#define CAL_RTCLK_GetDateAndTime_FB_Init  RTCLK_GetDateAndTime_FB_Init
	#define CHK_RTCLK_GetDateAndTime_FB_Init  TRUE
	#define EXP_RTCLK_GetDateAndTime_FB_Init  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_GetDateAndTime_FB_Init", (RTS_UINTPTR)RTCLK_GetDateAndTime_FB_Init, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockRTCLK_GetDateAndTime_FB_Init
	#define EXT_CmpCAARealTimeClockRTCLK_GetDateAndTime_FB_Init
	#define GET_CmpCAARealTimeClockRTCLK_GetDateAndTime_FB_Init  ERR_OK
	#define CAL_CmpCAARealTimeClockRTCLK_GetDateAndTime_FB_Init pICmpCAARealTimeClock->IRTCLK_GetDateAndTime_FB_Init
	#define CHK_CmpCAARealTimeClockRTCLK_GetDateAndTime_FB_Init (pICmpCAARealTimeClock != NULL)
	#define EXP_CmpCAARealTimeClockRTCLK_GetDateAndTime_FB_Init  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RTCLK_GetDateAndTime_FB_Init
	#define EXT_RTCLK_GetDateAndTime_FB_Init
	#define GET_RTCLK_GetDateAndTime_FB_Init(fl)  CAL_CMGETAPI( "RTCLK_GetDateAndTime_FB_Init" ) 
	#define CAL_RTCLK_GetDateAndTime_FB_Init pICmpCAARealTimeClock->IRTCLK_GetDateAndTime_FB_Init
	#define CHK_RTCLK_GetDateAndTime_FB_Init (pICmpCAARealTimeClock != NULL)
	#define EXP_RTCLK_GetDateAndTime_FB_Init  CAL_CMEXPAPI( "RTCLK_GetDateAndTime_FB_Init" ) 
#else /* DYNAMIC_LINK */
	#define USE_RTCLK_GetDateAndTime_FB_Init  PFRTCLK_GETDATEANDTIME_FB_INIT pfRTCLK_GetDateAndTime_FB_Init;
	#define EXT_RTCLK_GetDateAndTime_FB_Init  extern PFRTCLK_GETDATEANDTIME_FB_INIT pfRTCLK_GetDateAndTime_FB_Init;
	#define GET_RTCLK_GetDateAndTime_FB_Init(fl)  s_pfCMGetAPI2( "RTCLK_GetDateAndTime_FB_Init", (RTS_VOID_FCTPTR *)&pfRTCLK_GetDateAndTime_FB_Init, (fl), 0, 0)
	#define CAL_RTCLK_GetDateAndTime_FB_Init  pfRTCLK_GetDateAndTime_FB_Init
	#define CHK_RTCLK_GetDateAndTime_FB_Init  (pfRTCLK_GetDateAndTime_FB_Init != NULL)
	#define EXP_RTCLK_GetDateAndTime_FB_Init  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_GetDateAndTime_FB_Init", (RTS_UINTPTR)RTCLK_GetDateAndTime_FB_Init, 0, 0) 
#endif



CAA_BOOL CDECL RTCLK_GetDateAndTime_FB_Exit(CAA_BOOL bInCopyCode, rtclk_getdateandtime_typ* inst);
typedef CAA_BOOL (CDECL * PFRTCLK_GETDATEANDTIME_FB_EXIT) (CAA_BOOL bInCopyCode, rtclk_getdateandtime_typ* inst);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_GETDATEANDTIME_FB_EXIT_NOTIMPLEMENTED)
	#define USE_RTCLK_GetDateAndTime_FB_Exit
	#define EXT_RTCLK_GetDateAndTime_FB_Exit
	#define GET_RTCLK_GetDateAndTime_FB_Exit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RTCLK_GetDateAndTime_FB_Exit(p0,p1)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_RTCLK_GetDateAndTime_FB_Exit  FALSE
	#define EXP_RTCLK_GetDateAndTime_FB_Exit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RTCLK_GetDateAndTime_FB_Exit
	#define EXT_RTCLK_GetDateAndTime_FB_Exit
	#define GET_RTCLK_GetDateAndTime_FB_Exit(fl)  CAL_CMGETAPI( "RTCLK_GetDateAndTime_FB_Exit" ) 
	#define CAL_RTCLK_GetDateAndTime_FB_Exit  RTCLK_GetDateAndTime_FB_Exit
	#define CHK_RTCLK_GetDateAndTime_FB_Exit  TRUE
	#define EXP_RTCLK_GetDateAndTime_FB_Exit  CAL_CMEXPAPI( "RTCLK_GetDateAndTime_FB_Exit" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_RTCLK_GetDateAndTime_FB_Exit
	#define EXT_RTCLK_GetDateAndTime_FB_Exit
	#define GET_RTCLK_GetDateAndTime_FB_Exit(fl)  CAL_CMGETAPI( "RTCLK_GetDateAndTime_FB_Exit" ) 
	#define CAL_RTCLK_GetDateAndTime_FB_Exit  RTCLK_GetDateAndTime_FB_Exit
	#define CHK_RTCLK_GetDateAndTime_FB_Exit  TRUE
	#define EXP_RTCLK_GetDateAndTime_FB_Exit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_GetDateAndTime_FB_Exit", (RTS_UINTPTR)RTCLK_GetDateAndTime_FB_Exit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockRTCLK_GetDateAndTime_FB_Exit
	#define EXT_CmpCAARealTimeClockRTCLK_GetDateAndTime_FB_Exit
	#define GET_CmpCAARealTimeClockRTCLK_GetDateAndTime_FB_Exit  ERR_OK
	#define CAL_CmpCAARealTimeClockRTCLK_GetDateAndTime_FB_Exit pICmpCAARealTimeClock->IRTCLK_GetDateAndTime_FB_Exit
	#define CHK_CmpCAARealTimeClockRTCLK_GetDateAndTime_FB_Exit (pICmpCAARealTimeClock != NULL)
	#define EXP_CmpCAARealTimeClockRTCLK_GetDateAndTime_FB_Exit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RTCLK_GetDateAndTime_FB_Exit
	#define EXT_RTCLK_GetDateAndTime_FB_Exit
	#define GET_RTCLK_GetDateAndTime_FB_Exit(fl)  CAL_CMGETAPI( "RTCLK_GetDateAndTime_FB_Exit" ) 
	#define CAL_RTCLK_GetDateAndTime_FB_Exit pICmpCAARealTimeClock->IRTCLK_GetDateAndTime_FB_Exit
	#define CHK_RTCLK_GetDateAndTime_FB_Exit (pICmpCAARealTimeClock != NULL)
	#define EXP_RTCLK_GetDateAndTime_FB_Exit  CAL_CMEXPAPI( "RTCLK_GetDateAndTime_FB_Exit" ) 
#else /* DYNAMIC_LINK */
	#define USE_RTCLK_GetDateAndTime_FB_Exit  PFRTCLK_GETDATEANDTIME_FB_EXIT pfRTCLK_GetDateAndTime_FB_Exit;
	#define EXT_RTCLK_GetDateAndTime_FB_Exit  extern PFRTCLK_GETDATEANDTIME_FB_EXIT pfRTCLK_GetDateAndTime_FB_Exit;
	#define GET_RTCLK_GetDateAndTime_FB_Exit(fl)  s_pfCMGetAPI2( "RTCLK_GetDateAndTime_FB_Exit", (RTS_VOID_FCTPTR *)&pfRTCLK_GetDateAndTime_FB_Exit, (fl), 0, 0)
	#define CAL_RTCLK_GetDateAndTime_FB_Exit  pfRTCLK_GetDateAndTime_FB_Exit
	#define CHK_RTCLK_GetDateAndTime_FB_Exit  (pfRTCLK_GetDateAndTime_FB_Exit != NULL)
	#define EXP_RTCLK_GetDateAndTime_FB_Exit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_GetDateAndTime_FB_Exit", (RTS_UINTPTR)RTCLK_GetDateAndTime_FB_Exit, 0, 0) 
#endif



void CDECL RTCLK_SetDateAndTime(rtclk_setdateandtime_typ* inst);
typedef void (CDECL * PFRTCLK_SETDATEANDTIME) (rtclk_setdateandtime_typ* inst);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_SETDATEANDTIME_NOTIMPLEMENTED)
	#define USE_RTCLK_SetDateAndTime
	#define EXT_RTCLK_SetDateAndTime
	#define GET_RTCLK_SetDateAndTime(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RTCLK_SetDateAndTime(p0)  
	#define CHK_RTCLK_SetDateAndTime  FALSE
	#define EXP_RTCLK_SetDateAndTime  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RTCLK_SetDateAndTime
	#define EXT_RTCLK_SetDateAndTime
	#define GET_RTCLK_SetDateAndTime(fl)  CAL_CMGETAPI( "RTCLK_SetDateAndTime" ) 
	#define CAL_RTCLK_SetDateAndTime  RTCLK_SetDateAndTime
	#define CHK_RTCLK_SetDateAndTime  TRUE
	#define EXP_RTCLK_SetDateAndTime  CAL_CMEXPAPI( "RTCLK_SetDateAndTime" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_RTCLK_SetDateAndTime
	#define EXT_RTCLK_SetDateAndTime
	#define GET_RTCLK_SetDateAndTime(fl)  CAL_CMGETAPI( "RTCLK_SetDateAndTime" ) 
	#define CAL_RTCLK_SetDateAndTime  RTCLK_SetDateAndTime
	#define CHK_RTCLK_SetDateAndTime  TRUE
	#define EXP_RTCLK_SetDateAndTime  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_SetDateAndTime", (RTS_UINTPTR)RTCLK_SetDateAndTime, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockRTCLK_SetDateAndTime
	#define EXT_CmpCAARealTimeClockRTCLK_SetDateAndTime
	#define GET_CmpCAARealTimeClockRTCLK_SetDateAndTime  ERR_OK
	#define CAL_CmpCAARealTimeClockRTCLK_SetDateAndTime pICmpCAARealTimeClock->IRTCLK_SetDateAndTime
	#define CHK_CmpCAARealTimeClockRTCLK_SetDateAndTime (pICmpCAARealTimeClock != NULL)
	#define EXP_CmpCAARealTimeClockRTCLK_SetDateAndTime  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RTCLK_SetDateAndTime
	#define EXT_RTCLK_SetDateAndTime
	#define GET_RTCLK_SetDateAndTime(fl)  CAL_CMGETAPI( "RTCLK_SetDateAndTime" ) 
	#define CAL_RTCLK_SetDateAndTime pICmpCAARealTimeClock->IRTCLK_SetDateAndTime
	#define CHK_RTCLK_SetDateAndTime (pICmpCAARealTimeClock != NULL)
	#define EXP_RTCLK_SetDateAndTime  CAL_CMEXPAPI( "RTCLK_SetDateAndTime" ) 
#else /* DYNAMIC_LINK */
	#define USE_RTCLK_SetDateAndTime  PFRTCLK_SETDATEANDTIME pfRTCLK_SetDateAndTime;
	#define EXT_RTCLK_SetDateAndTime  extern PFRTCLK_SETDATEANDTIME pfRTCLK_SetDateAndTime;
	#define GET_RTCLK_SetDateAndTime(fl)  s_pfCMGetAPI2( "RTCLK_SetDateAndTime", (RTS_VOID_FCTPTR *)&pfRTCLK_SetDateAndTime, (fl), 0, 0)
	#define CAL_RTCLK_SetDateAndTime  pfRTCLK_SetDateAndTime
	#define CHK_RTCLK_SetDateAndTime  (pfRTCLK_SetDateAndTime != NULL)
	#define EXP_RTCLK_SetDateAndTime  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_SetDateAndTime", (RTS_UINTPTR)RTCLK_SetDateAndTime, 0, 0) 
#endif



CAA_BOOL CDECL RTCLK_SetDateAndTime_FB_Init(CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, rtclk_setdateandtime_typ* inst);
typedef CAA_BOOL (CDECL * PFRTCLK_SETDATEANDTIME_FB_INIT) (CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, rtclk_setdateandtime_typ* inst);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_SETDATEANDTIME_FB_INIT_NOTIMPLEMENTED)
	#define USE_RTCLK_SetDateAndTime_FB_Init
	#define EXT_RTCLK_SetDateAndTime_FB_Init
	#define GET_RTCLK_SetDateAndTime_FB_Init(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RTCLK_SetDateAndTime_FB_Init(p0,p1,p2)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_RTCLK_SetDateAndTime_FB_Init  FALSE
	#define EXP_RTCLK_SetDateAndTime_FB_Init  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RTCLK_SetDateAndTime_FB_Init
	#define EXT_RTCLK_SetDateAndTime_FB_Init
	#define GET_RTCLK_SetDateAndTime_FB_Init(fl)  CAL_CMGETAPI( "RTCLK_SetDateAndTime_FB_Init" ) 
	#define CAL_RTCLK_SetDateAndTime_FB_Init  RTCLK_SetDateAndTime_FB_Init
	#define CHK_RTCLK_SetDateAndTime_FB_Init  TRUE
	#define EXP_RTCLK_SetDateAndTime_FB_Init  CAL_CMEXPAPI( "RTCLK_SetDateAndTime_FB_Init" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_RTCLK_SetDateAndTime_FB_Init
	#define EXT_RTCLK_SetDateAndTime_FB_Init
	#define GET_RTCLK_SetDateAndTime_FB_Init(fl)  CAL_CMGETAPI( "RTCLK_SetDateAndTime_FB_Init" ) 
	#define CAL_RTCLK_SetDateAndTime_FB_Init  RTCLK_SetDateAndTime_FB_Init
	#define CHK_RTCLK_SetDateAndTime_FB_Init  TRUE
	#define EXP_RTCLK_SetDateAndTime_FB_Init  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_SetDateAndTime_FB_Init", (RTS_UINTPTR)RTCLK_SetDateAndTime_FB_Init, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockRTCLK_SetDateAndTime_FB_Init
	#define EXT_CmpCAARealTimeClockRTCLK_SetDateAndTime_FB_Init
	#define GET_CmpCAARealTimeClockRTCLK_SetDateAndTime_FB_Init  ERR_OK
	#define CAL_CmpCAARealTimeClockRTCLK_SetDateAndTime_FB_Init pICmpCAARealTimeClock->IRTCLK_SetDateAndTime_FB_Init
	#define CHK_CmpCAARealTimeClockRTCLK_SetDateAndTime_FB_Init (pICmpCAARealTimeClock != NULL)
	#define EXP_CmpCAARealTimeClockRTCLK_SetDateAndTime_FB_Init  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RTCLK_SetDateAndTime_FB_Init
	#define EXT_RTCLK_SetDateAndTime_FB_Init
	#define GET_RTCLK_SetDateAndTime_FB_Init(fl)  CAL_CMGETAPI( "RTCLK_SetDateAndTime_FB_Init" ) 
	#define CAL_RTCLK_SetDateAndTime_FB_Init pICmpCAARealTimeClock->IRTCLK_SetDateAndTime_FB_Init
	#define CHK_RTCLK_SetDateAndTime_FB_Init (pICmpCAARealTimeClock != NULL)
	#define EXP_RTCLK_SetDateAndTime_FB_Init  CAL_CMEXPAPI( "RTCLK_SetDateAndTime_FB_Init" ) 
#else /* DYNAMIC_LINK */
	#define USE_RTCLK_SetDateAndTime_FB_Init  PFRTCLK_SETDATEANDTIME_FB_INIT pfRTCLK_SetDateAndTime_FB_Init;
	#define EXT_RTCLK_SetDateAndTime_FB_Init  extern PFRTCLK_SETDATEANDTIME_FB_INIT pfRTCLK_SetDateAndTime_FB_Init;
	#define GET_RTCLK_SetDateAndTime_FB_Init(fl)  s_pfCMGetAPI2( "RTCLK_SetDateAndTime_FB_Init", (RTS_VOID_FCTPTR *)&pfRTCLK_SetDateAndTime_FB_Init, (fl), 0, 0)
	#define CAL_RTCLK_SetDateAndTime_FB_Init  pfRTCLK_SetDateAndTime_FB_Init
	#define CHK_RTCLK_SetDateAndTime_FB_Init  (pfRTCLK_SetDateAndTime_FB_Init != NULL)
	#define EXP_RTCLK_SetDateAndTime_FB_Init  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_SetDateAndTime_FB_Init", (RTS_UINTPTR)RTCLK_SetDateAndTime_FB_Init, 0, 0) 
#endif



CAA_BOOL CDECL RTCLK_SetDateAndTime_FB_Exit(CAA_BOOL bInCopyCode, rtclk_setdateandtime_typ* inst);
typedef CAA_BOOL (CDECL * PFRTCLK_SETDATEANDTIME_FB_EXIT) (CAA_BOOL bInCopyCode, rtclk_setdateandtime_typ* inst);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_SETDATEANDTIME_FB_EXIT_NOTIMPLEMENTED)
	#define USE_RTCLK_SetDateAndTime_FB_Exit
	#define EXT_RTCLK_SetDateAndTime_FB_Exit
	#define GET_RTCLK_SetDateAndTime_FB_Exit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RTCLK_SetDateAndTime_FB_Exit(p0,p1)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_RTCLK_SetDateAndTime_FB_Exit  FALSE
	#define EXP_RTCLK_SetDateAndTime_FB_Exit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RTCLK_SetDateAndTime_FB_Exit
	#define EXT_RTCLK_SetDateAndTime_FB_Exit
	#define GET_RTCLK_SetDateAndTime_FB_Exit(fl)  CAL_CMGETAPI( "RTCLK_SetDateAndTime_FB_Exit" ) 
	#define CAL_RTCLK_SetDateAndTime_FB_Exit  RTCLK_SetDateAndTime_FB_Exit
	#define CHK_RTCLK_SetDateAndTime_FB_Exit  TRUE
	#define EXP_RTCLK_SetDateAndTime_FB_Exit  CAL_CMEXPAPI( "RTCLK_SetDateAndTime_FB_Exit" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_RTCLK_SetDateAndTime_FB_Exit
	#define EXT_RTCLK_SetDateAndTime_FB_Exit
	#define GET_RTCLK_SetDateAndTime_FB_Exit(fl)  CAL_CMGETAPI( "RTCLK_SetDateAndTime_FB_Exit" ) 
	#define CAL_RTCLK_SetDateAndTime_FB_Exit  RTCLK_SetDateAndTime_FB_Exit
	#define CHK_RTCLK_SetDateAndTime_FB_Exit  TRUE
	#define EXP_RTCLK_SetDateAndTime_FB_Exit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_SetDateAndTime_FB_Exit", (RTS_UINTPTR)RTCLK_SetDateAndTime_FB_Exit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockRTCLK_SetDateAndTime_FB_Exit
	#define EXT_CmpCAARealTimeClockRTCLK_SetDateAndTime_FB_Exit
	#define GET_CmpCAARealTimeClockRTCLK_SetDateAndTime_FB_Exit  ERR_OK
	#define CAL_CmpCAARealTimeClockRTCLK_SetDateAndTime_FB_Exit pICmpCAARealTimeClock->IRTCLK_SetDateAndTime_FB_Exit
	#define CHK_CmpCAARealTimeClockRTCLK_SetDateAndTime_FB_Exit (pICmpCAARealTimeClock != NULL)
	#define EXP_CmpCAARealTimeClockRTCLK_SetDateAndTime_FB_Exit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RTCLK_SetDateAndTime_FB_Exit
	#define EXT_RTCLK_SetDateAndTime_FB_Exit
	#define GET_RTCLK_SetDateAndTime_FB_Exit(fl)  CAL_CMGETAPI( "RTCLK_SetDateAndTime_FB_Exit" ) 
	#define CAL_RTCLK_SetDateAndTime_FB_Exit pICmpCAARealTimeClock->IRTCLK_SetDateAndTime_FB_Exit
	#define CHK_RTCLK_SetDateAndTime_FB_Exit (pICmpCAARealTimeClock != NULL)
	#define EXP_RTCLK_SetDateAndTime_FB_Exit  CAL_CMEXPAPI( "RTCLK_SetDateAndTime_FB_Exit" ) 
#else /* DYNAMIC_LINK */
	#define USE_RTCLK_SetDateAndTime_FB_Exit  PFRTCLK_SETDATEANDTIME_FB_EXIT pfRTCLK_SetDateAndTime_FB_Exit;
	#define EXT_RTCLK_SetDateAndTime_FB_Exit  extern PFRTCLK_SETDATEANDTIME_FB_EXIT pfRTCLK_SetDateAndTime_FB_Exit;
	#define GET_RTCLK_SetDateAndTime_FB_Exit(fl)  s_pfCMGetAPI2( "RTCLK_SetDateAndTime_FB_Exit", (RTS_VOID_FCTPTR *)&pfRTCLK_SetDateAndTime_FB_Exit, (fl), 0, 0)
	#define CAL_RTCLK_SetDateAndTime_FB_Exit  pfRTCLK_SetDateAndTime_FB_Exit
	#define CHK_RTCLK_SetDateAndTime_FB_Exit  (pfRTCLK_SetDateAndTime_FB_Exit != NULL)
	#define EXP_RTCLK_SetDateAndTime_FB_Exit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_SetDateAndTime_FB_Exit", (RTS_UINTPTR)RTCLK_SetDateAndTime_FB_Exit, 0, 0) 
#endif



void CDECL RTCLK_GetTimeZoneInformation(rtclk_gettimezoneinformation_typ* inst);
typedef void (CDECL * PFRTCLK_GETTIMEZONEINFORMATION) (rtclk_gettimezoneinformation_typ* inst);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_GETTIMEZONEINFORMATION_NOTIMPLEMENTED)
	#define USE_RTCLK_GetTimeZoneInformation
	#define EXT_RTCLK_GetTimeZoneInformation
	#define GET_RTCLK_GetTimeZoneInformation(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RTCLK_GetTimeZoneInformation(p0)  
	#define CHK_RTCLK_GetTimeZoneInformation  FALSE
	#define EXP_RTCLK_GetTimeZoneInformation  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RTCLK_GetTimeZoneInformation
	#define EXT_RTCLK_GetTimeZoneInformation
	#define GET_RTCLK_GetTimeZoneInformation(fl)  CAL_CMGETAPI( "RTCLK_GetTimeZoneInformation" ) 
	#define CAL_RTCLK_GetTimeZoneInformation  RTCLK_GetTimeZoneInformation
	#define CHK_RTCLK_GetTimeZoneInformation  TRUE
	#define EXP_RTCLK_GetTimeZoneInformation  CAL_CMEXPAPI( "RTCLK_GetTimeZoneInformation" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_RTCLK_GetTimeZoneInformation
	#define EXT_RTCLK_GetTimeZoneInformation
	#define GET_RTCLK_GetTimeZoneInformation(fl)  CAL_CMGETAPI( "RTCLK_GetTimeZoneInformation" ) 
	#define CAL_RTCLK_GetTimeZoneInformation  RTCLK_GetTimeZoneInformation
	#define CHK_RTCLK_GetTimeZoneInformation  TRUE
	#define EXP_RTCLK_GetTimeZoneInformation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_GetTimeZoneInformation", (RTS_UINTPTR)RTCLK_GetTimeZoneInformation, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockRTCLK_GetTimeZoneInformation
	#define EXT_CmpCAARealTimeClockRTCLK_GetTimeZoneInformation
	#define GET_CmpCAARealTimeClockRTCLK_GetTimeZoneInformation  ERR_OK
	#define CAL_CmpCAARealTimeClockRTCLK_GetTimeZoneInformation pICmpCAARealTimeClock->IRTCLK_GetTimeZoneInformation
	#define CHK_CmpCAARealTimeClockRTCLK_GetTimeZoneInformation (pICmpCAARealTimeClock != NULL)
	#define EXP_CmpCAARealTimeClockRTCLK_GetTimeZoneInformation  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RTCLK_GetTimeZoneInformation
	#define EXT_RTCLK_GetTimeZoneInformation
	#define GET_RTCLK_GetTimeZoneInformation(fl)  CAL_CMGETAPI( "RTCLK_GetTimeZoneInformation" ) 
	#define CAL_RTCLK_GetTimeZoneInformation pICmpCAARealTimeClock->IRTCLK_GetTimeZoneInformation
	#define CHK_RTCLK_GetTimeZoneInformation (pICmpCAARealTimeClock != NULL)
	#define EXP_RTCLK_GetTimeZoneInformation  CAL_CMEXPAPI( "RTCLK_GetTimeZoneInformation" ) 
#else /* DYNAMIC_LINK */
	#define USE_RTCLK_GetTimeZoneInformation  PFRTCLK_GETTIMEZONEINFORMATION pfRTCLK_GetTimeZoneInformation;
	#define EXT_RTCLK_GetTimeZoneInformation  extern PFRTCLK_GETTIMEZONEINFORMATION pfRTCLK_GetTimeZoneInformation;
	#define GET_RTCLK_GetTimeZoneInformation(fl)  s_pfCMGetAPI2( "RTCLK_GetTimeZoneInformation", (RTS_VOID_FCTPTR *)&pfRTCLK_GetTimeZoneInformation, (fl), 0, 0)
	#define CAL_RTCLK_GetTimeZoneInformation  pfRTCLK_GetTimeZoneInformation
	#define CHK_RTCLK_GetTimeZoneInformation  (pfRTCLK_GetTimeZoneInformation != NULL)
	#define EXP_RTCLK_GetTimeZoneInformation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_GetTimeZoneInformation", (RTS_UINTPTR)RTCLK_GetTimeZoneInformation, 0, 0) 
#endif



CAA_BOOL CDECL RTCLK_GetTimeZoneInformation_FB_Init(CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, rtclk_gettimezoneinformation_typ* inst);
typedef CAA_BOOL (CDECL * PFRTCLK_GETTIMEZONEINFORMATION_FB_INIT) (CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, rtclk_gettimezoneinformation_typ* inst);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_GETTIMEZONEINFORMATION_FB_INIT_NOTIMPLEMENTED)
	#define USE_RTCLK_GetTimeZoneInformation_FB_Init
	#define EXT_RTCLK_GetTimeZoneInformation_FB_Init
	#define GET_RTCLK_GetTimeZoneInformation_FB_Init(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RTCLK_GetTimeZoneInformation_FB_Init(p0,p1,p2)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_RTCLK_GetTimeZoneInformation_FB_Init  FALSE
	#define EXP_RTCLK_GetTimeZoneInformation_FB_Init  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RTCLK_GetTimeZoneInformation_FB_Init
	#define EXT_RTCLK_GetTimeZoneInformation_FB_Init
	#define GET_RTCLK_GetTimeZoneInformation_FB_Init(fl)  CAL_CMGETAPI( "RTCLK_GetTimeZoneInformation_FB_Init" ) 
	#define CAL_RTCLK_GetTimeZoneInformation_FB_Init  RTCLK_GetTimeZoneInformation_FB_Init
	#define CHK_RTCLK_GetTimeZoneInformation_FB_Init  TRUE
	#define EXP_RTCLK_GetTimeZoneInformation_FB_Init  CAL_CMEXPAPI( "RTCLK_GetTimeZoneInformation_FB_Init" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_RTCLK_GetTimeZoneInformation_FB_Init
	#define EXT_RTCLK_GetTimeZoneInformation_FB_Init
	#define GET_RTCLK_GetTimeZoneInformation_FB_Init(fl)  CAL_CMGETAPI( "RTCLK_GetTimeZoneInformation_FB_Init" ) 
	#define CAL_RTCLK_GetTimeZoneInformation_FB_Init  RTCLK_GetTimeZoneInformation_FB_Init
	#define CHK_RTCLK_GetTimeZoneInformation_FB_Init  TRUE
	#define EXP_RTCLK_GetTimeZoneInformation_FB_Init  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_GetTimeZoneInformation_FB_Init", (RTS_UINTPTR)RTCLK_GetTimeZoneInformation_FB_Init, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockRTCLK_GetTimeZoneInformation_FB_Init
	#define EXT_CmpCAARealTimeClockRTCLK_GetTimeZoneInformation_FB_Init
	#define GET_CmpCAARealTimeClockRTCLK_GetTimeZoneInformation_FB_Init  ERR_OK
	#define CAL_CmpCAARealTimeClockRTCLK_GetTimeZoneInformation_FB_Init pICmpCAARealTimeClock->IRTCLK_GetTimeZoneInformation_FB_Init
	#define CHK_CmpCAARealTimeClockRTCLK_GetTimeZoneInformation_FB_Init (pICmpCAARealTimeClock != NULL)
	#define EXP_CmpCAARealTimeClockRTCLK_GetTimeZoneInformation_FB_Init  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RTCLK_GetTimeZoneInformation_FB_Init
	#define EXT_RTCLK_GetTimeZoneInformation_FB_Init
	#define GET_RTCLK_GetTimeZoneInformation_FB_Init(fl)  CAL_CMGETAPI( "RTCLK_GetTimeZoneInformation_FB_Init" ) 
	#define CAL_RTCLK_GetTimeZoneInformation_FB_Init pICmpCAARealTimeClock->IRTCLK_GetTimeZoneInformation_FB_Init
	#define CHK_RTCLK_GetTimeZoneInformation_FB_Init (pICmpCAARealTimeClock != NULL)
	#define EXP_RTCLK_GetTimeZoneInformation_FB_Init  CAL_CMEXPAPI( "RTCLK_GetTimeZoneInformation_FB_Init" ) 
#else /* DYNAMIC_LINK */
	#define USE_RTCLK_GetTimeZoneInformation_FB_Init  PFRTCLK_GETTIMEZONEINFORMATION_FB_INIT pfRTCLK_GetTimeZoneInformation_FB_Init;
	#define EXT_RTCLK_GetTimeZoneInformation_FB_Init  extern PFRTCLK_GETTIMEZONEINFORMATION_FB_INIT pfRTCLK_GetTimeZoneInformation_FB_Init;
	#define GET_RTCLK_GetTimeZoneInformation_FB_Init(fl)  s_pfCMGetAPI2( "RTCLK_GetTimeZoneInformation_FB_Init", (RTS_VOID_FCTPTR *)&pfRTCLK_GetTimeZoneInformation_FB_Init, (fl), 0, 0)
	#define CAL_RTCLK_GetTimeZoneInformation_FB_Init  pfRTCLK_GetTimeZoneInformation_FB_Init
	#define CHK_RTCLK_GetTimeZoneInformation_FB_Init  (pfRTCLK_GetTimeZoneInformation_FB_Init != NULL)
	#define EXP_RTCLK_GetTimeZoneInformation_FB_Init  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_GetTimeZoneInformation_FB_Init", (RTS_UINTPTR)RTCLK_GetTimeZoneInformation_FB_Init, 0, 0) 
#endif



CAA_BOOL CDECL RTCLK_GetTimeZoneInformation_FB_Exit(CAA_BOOL bInCopyCode, rtclk_gettimezoneinformation_typ* inst);
typedef CAA_BOOL (CDECL * PFRTCLK_GETTIMEZONEINFORMATION_FB_EXIT) (CAA_BOOL bInCopyCode, rtclk_gettimezoneinformation_typ* inst);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_GETTIMEZONEINFORMATION_FB_EXIT_NOTIMPLEMENTED)
	#define USE_RTCLK_GetTimeZoneInformation_FB_Exit
	#define EXT_RTCLK_GetTimeZoneInformation_FB_Exit
	#define GET_RTCLK_GetTimeZoneInformation_FB_Exit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RTCLK_GetTimeZoneInformation_FB_Exit(p0,p1)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_RTCLK_GetTimeZoneInformation_FB_Exit  FALSE
	#define EXP_RTCLK_GetTimeZoneInformation_FB_Exit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RTCLK_GetTimeZoneInformation_FB_Exit
	#define EXT_RTCLK_GetTimeZoneInformation_FB_Exit
	#define GET_RTCLK_GetTimeZoneInformation_FB_Exit(fl)  CAL_CMGETAPI( "RTCLK_GetTimeZoneInformation_FB_Exit" ) 
	#define CAL_RTCLK_GetTimeZoneInformation_FB_Exit  RTCLK_GetTimeZoneInformation_FB_Exit
	#define CHK_RTCLK_GetTimeZoneInformation_FB_Exit  TRUE
	#define EXP_RTCLK_GetTimeZoneInformation_FB_Exit  CAL_CMEXPAPI( "RTCLK_GetTimeZoneInformation_FB_Exit" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_RTCLK_GetTimeZoneInformation_FB_Exit
	#define EXT_RTCLK_GetTimeZoneInformation_FB_Exit
	#define GET_RTCLK_GetTimeZoneInformation_FB_Exit(fl)  CAL_CMGETAPI( "RTCLK_GetTimeZoneInformation_FB_Exit" ) 
	#define CAL_RTCLK_GetTimeZoneInformation_FB_Exit  RTCLK_GetTimeZoneInformation_FB_Exit
	#define CHK_RTCLK_GetTimeZoneInformation_FB_Exit  TRUE
	#define EXP_RTCLK_GetTimeZoneInformation_FB_Exit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_GetTimeZoneInformation_FB_Exit", (RTS_UINTPTR)RTCLK_GetTimeZoneInformation_FB_Exit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockRTCLK_GetTimeZoneInformation_FB_Exit
	#define EXT_CmpCAARealTimeClockRTCLK_GetTimeZoneInformation_FB_Exit
	#define GET_CmpCAARealTimeClockRTCLK_GetTimeZoneInformation_FB_Exit  ERR_OK
	#define CAL_CmpCAARealTimeClockRTCLK_GetTimeZoneInformation_FB_Exit pICmpCAARealTimeClock->IRTCLK_GetTimeZoneInformation_FB_Exit
	#define CHK_CmpCAARealTimeClockRTCLK_GetTimeZoneInformation_FB_Exit (pICmpCAARealTimeClock != NULL)
	#define EXP_CmpCAARealTimeClockRTCLK_GetTimeZoneInformation_FB_Exit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RTCLK_GetTimeZoneInformation_FB_Exit
	#define EXT_RTCLK_GetTimeZoneInformation_FB_Exit
	#define GET_RTCLK_GetTimeZoneInformation_FB_Exit(fl)  CAL_CMGETAPI( "RTCLK_GetTimeZoneInformation_FB_Exit" ) 
	#define CAL_RTCLK_GetTimeZoneInformation_FB_Exit pICmpCAARealTimeClock->IRTCLK_GetTimeZoneInformation_FB_Exit
	#define CHK_RTCLK_GetTimeZoneInformation_FB_Exit (pICmpCAARealTimeClock != NULL)
	#define EXP_RTCLK_GetTimeZoneInformation_FB_Exit  CAL_CMEXPAPI( "RTCLK_GetTimeZoneInformation_FB_Exit" ) 
#else /* DYNAMIC_LINK */
	#define USE_RTCLK_GetTimeZoneInformation_FB_Exit  PFRTCLK_GETTIMEZONEINFORMATION_FB_EXIT pfRTCLK_GetTimeZoneInformation_FB_Exit;
	#define EXT_RTCLK_GetTimeZoneInformation_FB_Exit  extern PFRTCLK_GETTIMEZONEINFORMATION_FB_EXIT pfRTCLK_GetTimeZoneInformation_FB_Exit;
	#define GET_RTCLK_GetTimeZoneInformation_FB_Exit(fl)  s_pfCMGetAPI2( "RTCLK_GetTimeZoneInformation_FB_Exit", (RTS_VOID_FCTPTR *)&pfRTCLK_GetTimeZoneInformation_FB_Exit, (fl), 0, 0)
	#define CAL_RTCLK_GetTimeZoneInformation_FB_Exit  pfRTCLK_GetTimeZoneInformation_FB_Exit
	#define CHK_RTCLK_GetTimeZoneInformation_FB_Exit  (pfRTCLK_GetTimeZoneInformation_FB_Exit != NULL)
	#define EXP_RTCLK_GetTimeZoneInformation_FB_Exit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_GetTimeZoneInformation_FB_Exit", (RTS_UINTPTR)RTCLK_GetTimeZoneInformation_FB_Exit, 0, 0) 
#endif



void CDECL RTCLK_SetTimeZoneInformation(rtclk_settimezoneinformation_typ* inst);
typedef void (CDECL * PFRTCLK_SETTIMEZONEINFORMATION) (rtclk_settimezoneinformation_typ* inst);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_SETTIMEZONEINFORMATION_NOTIMPLEMENTED)
	#define USE_RTCLK_SetTimeZoneInformation
	#define EXT_RTCLK_SetTimeZoneInformation
	#define GET_RTCLK_SetTimeZoneInformation(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RTCLK_SetTimeZoneInformation(p0)  
	#define CHK_RTCLK_SetTimeZoneInformation  FALSE
	#define EXP_RTCLK_SetTimeZoneInformation  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RTCLK_SetTimeZoneInformation
	#define EXT_RTCLK_SetTimeZoneInformation
	#define GET_RTCLK_SetTimeZoneInformation(fl)  CAL_CMGETAPI( "RTCLK_SetTimeZoneInformation" ) 
	#define CAL_RTCLK_SetTimeZoneInformation  RTCLK_SetTimeZoneInformation
	#define CHK_RTCLK_SetTimeZoneInformation  TRUE
	#define EXP_RTCLK_SetTimeZoneInformation  CAL_CMEXPAPI( "RTCLK_SetTimeZoneInformation" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_RTCLK_SetTimeZoneInformation
	#define EXT_RTCLK_SetTimeZoneInformation
	#define GET_RTCLK_SetTimeZoneInformation(fl)  CAL_CMGETAPI( "RTCLK_SetTimeZoneInformation" ) 
	#define CAL_RTCLK_SetTimeZoneInformation  RTCLK_SetTimeZoneInformation
	#define CHK_RTCLK_SetTimeZoneInformation  TRUE
	#define EXP_RTCLK_SetTimeZoneInformation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_SetTimeZoneInformation", (RTS_UINTPTR)RTCLK_SetTimeZoneInformation, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockRTCLK_SetTimeZoneInformation
	#define EXT_CmpCAARealTimeClockRTCLK_SetTimeZoneInformation
	#define GET_CmpCAARealTimeClockRTCLK_SetTimeZoneInformation  ERR_OK
	#define CAL_CmpCAARealTimeClockRTCLK_SetTimeZoneInformation pICmpCAARealTimeClock->IRTCLK_SetTimeZoneInformation
	#define CHK_CmpCAARealTimeClockRTCLK_SetTimeZoneInformation (pICmpCAARealTimeClock != NULL)
	#define EXP_CmpCAARealTimeClockRTCLK_SetTimeZoneInformation  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RTCLK_SetTimeZoneInformation
	#define EXT_RTCLK_SetTimeZoneInformation
	#define GET_RTCLK_SetTimeZoneInformation(fl)  CAL_CMGETAPI( "RTCLK_SetTimeZoneInformation" ) 
	#define CAL_RTCLK_SetTimeZoneInformation pICmpCAARealTimeClock->IRTCLK_SetTimeZoneInformation
	#define CHK_RTCLK_SetTimeZoneInformation (pICmpCAARealTimeClock != NULL)
	#define EXP_RTCLK_SetTimeZoneInformation  CAL_CMEXPAPI( "RTCLK_SetTimeZoneInformation" ) 
#else /* DYNAMIC_LINK */
	#define USE_RTCLK_SetTimeZoneInformation  PFRTCLK_SETTIMEZONEINFORMATION pfRTCLK_SetTimeZoneInformation;
	#define EXT_RTCLK_SetTimeZoneInformation  extern PFRTCLK_SETTIMEZONEINFORMATION pfRTCLK_SetTimeZoneInformation;
	#define GET_RTCLK_SetTimeZoneInformation(fl)  s_pfCMGetAPI2( "RTCLK_SetTimeZoneInformation", (RTS_VOID_FCTPTR *)&pfRTCLK_SetTimeZoneInformation, (fl), 0, 0)
	#define CAL_RTCLK_SetTimeZoneInformation  pfRTCLK_SetTimeZoneInformation
	#define CHK_RTCLK_SetTimeZoneInformation  (pfRTCLK_SetTimeZoneInformation != NULL)
	#define EXP_RTCLK_SetTimeZoneInformation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_SetTimeZoneInformation", (RTS_UINTPTR)RTCLK_SetTimeZoneInformation, 0, 0) 
#endif



CAA_BOOL CDECL RTCLK_SetTimeZoneInformation_FB_Init(CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, rtclk_settimezoneinformation_typ* inst);
typedef CAA_BOOL (CDECL * PFRTCLK_SETTIMEZONEINFORMATION_FB_INIT) (CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, rtclk_settimezoneinformation_typ* inst);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_SETTIMEZONEINFORMATION_FB_INIT_NOTIMPLEMENTED)
	#define USE_RTCLK_SetTimeZoneInformation_FB_Init
	#define EXT_RTCLK_SetTimeZoneInformation_FB_Init
	#define GET_RTCLK_SetTimeZoneInformation_FB_Init(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RTCLK_SetTimeZoneInformation_FB_Init(p0,p1,p2)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_RTCLK_SetTimeZoneInformation_FB_Init  FALSE
	#define EXP_RTCLK_SetTimeZoneInformation_FB_Init  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RTCLK_SetTimeZoneInformation_FB_Init
	#define EXT_RTCLK_SetTimeZoneInformation_FB_Init
	#define GET_RTCLK_SetTimeZoneInformation_FB_Init(fl)  CAL_CMGETAPI( "RTCLK_SetTimeZoneInformation_FB_Init" ) 
	#define CAL_RTCLK_SetTimeZoneInformation_FB_Init  RTCLK_SetTimeZoneInformation_FB_Init
	#define CHK_RTCLK_SetTimeZoneInformation_FB_Init  TRUE
	#define EXP_RTCLK_SetTimeZoneInformation_FB_Init  CAL_CMEXPAPI( "RTCLK_SetTimeZoneInformation_FB_Init" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_RTCLK_SetTimeZoneInformation_FB_Init
	#define EXT_RTCLK_SetTimeZoneInformation_FB_Init
	#define GET_RTCLK_SetTimeZoneInformation_FB_Init(fl)  CAL_CMGETAPI( "RTCLK_SetTimeZoneInformation_FB_Init" ) 
	#define CAL_RTCLK_SetTimeZoneInformation_FB_Init  RTCLK_SetTimeZoneInformation_FB_Init
	#define CHK_RTCLK_SetTimeZoneInformation_FB_Init  TRUE
	#define EXP_RTCLK_SetTimeZoneInformation_FB_Init  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_SetTimeZoneInformation_FB_Init", (RTS_UINTPTR)RTCLK_SetTimeZoneInformation_FB_Init, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockRTCLK_SetTimeZoneInformation_FB_Init
	#define EXT_CmpCAARealTimeClockRTCLK_SetTimeZoneInformation_FB_Init
	#define GET_CmpCAARealTimeClockRTCLK_SetTimeZoneInformation_FB_Init  ERR_OK
	#define CAL_CmpCAARealTimeClockRTCLK_SetTimeZoneInformation_FB_Init pICmpCAARealTimeClock->IRTCLK_SetTimeZoneInformation_FB_Init
	#define CHK_CmpCAARealTimeClockRTCLK_SetTimeZoneInformation_FB_Init (pICmpCAARealTimeClock != NULL)
	#define EXP_CmpCAARealTimeClockRTCLK_SetTimeZoneInformation_FB_Init  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RTCLK_SetTimeZoneInformation_FB_Init
	#define EXT_RTCLK_SetTimeZoneInformation_FB_Init
	#define GET_RTCLK_SetTimeZoneInformation_FB_Init(fl)  CAL_CMGETAPI( "RTCLK_SetTimeZoneInformation_FB_Init" ) 
	#define CAL_RTCLK_SetTimeZoneInformation_FB_Init pICmpCAARealTimeClock->IRTCLK_SetTimeZoneInformation_FB_Init
	#define CHK_RTCLK_SetTimeZoneInformation_FB_Init (pICmpCAARealTimeClock != NULL)
	#define EXP_RTCLK_SetTimeZoneInformation_FB_Init  CAL_CMEXPAPI( "RTCLK_SetTimeZoneInformation_FB_Init" ) 
#else /* DYNAMIC_LINK */
	#define USE_RTCLK_SetTimeZoneInformation_FB_Init  PFRTCLK_SETTIMEZONEINFORMATION_FB_INIT pfRTCLK_SetTimeZoneInformation_FB_Init;
	#define EXT_RTCLK_SetTimeZoneInformation_FB_Init  extern PFRTCLK_SETTIMEZONEINFORMATION_FB_INIT pfRTCLK_SetTimeZoneInformation_FB_Init;
	#define GET_RTCLK_SetTimeZoneInformation_FB_Init(fl)  s_pfCMGetAPI2( "RTCLK_SetTimeZoneInformation_FB_Init", (RTS_VOID_FCTPTR *)&pfRTCLK_SetTimeZoneInformation_FB_Init, (fl), 0, 0)
	#define CAL_RTCLK_SetTimeZoneInformation_FB_Init  pfRTCLK_SetTimeZoneInformation_FB_Init
	#define CHK_RTCLK_SetTimeZoneInformation_FB_Init  (pfRTCLK_SetTimeZoneInformation_FB_Init != NULL)
	#define EXP_RTCLK_SetTimeZoneInformation_FB_Init  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_SetTimeZoneInformation_FB_Init", (RTS_UINTPTR)RTCLK_SetTimeZoneInformation_FB_Init, 0, 0) 
#endif



CAA_BOOL CDECL RTCLK_SetTimeZoneInformation_FB_Exit(CAA_BOOL bInCopyCode, rtclk_settimezoneinformation_typ* inst);
typedef CAA_BOOL (CDECL * PFRTCLK_SETTIMEZONEINFORMATION_FB_EXIT) (CAA_BOOL bInCopyCode, rtclk_settimezoneinformation_typ* inst);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_SETTIMEZONEINFORMATION_FB_EXIT_NOTIMPLEMENTED)
	#define USE_RTCLK_SetTimeZoneInformation_FB_Exit
	#define EXT_RTCLK_SetTimeZoneInformation_FB_Exit
	#define GET_RTCLK_SetTimeZoneInformation_FB_Exit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RTCLK_SetTimeZoneInformation_FB_Exit(p0,p1)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_RTCLK_SetTimeZoneInformation_FB_Exit  FALSE
	#define EXP_RTCLK_SetTimeZoneInformation_FB_Exit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RTCLK_SetTimeZoneInformation_FB_Exit
	#define EXT_RTCLK_SetTimeZoneInformation_FB_Exit
	#define GET_RTCLK_SetTimeZoneInformation_FB_Exit(fl)  CAL_CMGETAPI( "RTCLK_SetTimeZoneInformation_FB_Exit" ) 
	#define CAL_RTCLK_SetTimeZoneInformation_FB_Exit  RTCLK_SetTimeZoneInformation_FB_Exit
	#define CHK_RTCLK_SetTimeZoneInformation_FB_Exit  TRUE
	#define EXP_RTCLK_SetTimeZoneInformation_FB_Exit  CAL_CMEXPAPI( "RTCLK_SetTimeZoneInformation_FB_Exit" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_RTCLK_SetTimeZoneInformation_FB_Exit
	#define EXT_RTCLK_SetTimeZoneInformation_FB_Exit
	#define GET_RTCLK_SetTimeZoneInformation_FB_Exit(fl)  CAL_CMGETAPI( "RTCLK_SetTimeZoneInformation_FB_Exit" ) 
	#define CAL_RTCLK_SetTimeZoneInformation_FB_Exit  RTCLK_SetTimeZoneInformation_FB_Exit
	#define CHK_RTCLK_SetTimeZoneInformation_FB_Exit  TRUE
	#define EXP_RTCLK_SetTimeZoneInformation_FB_Exit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_SetTimeZoneInformation_FB_Exit", (RTS_UINTPTR)RTCLK_SetTimeZoneInformation_FB_Exit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockRTCLK_SetTimeZoneInformation_FB_Exit
	#define EXT_CmpCAARealTimeClockRTCLK_SetTimeZoneInformation_FB_Exit
	#define GET_CmpCAARealTimeClockRTCLK_SetTimeZoneInformation_FB_Exit  ERR_OK
	#define CAL_CmpCAARealTimeClockRTCLK_SetTimeZoneInformation_FB_Exit pICmpCAARealTimeClock->IRTCLK_SetTimeZoneInformation_FB_Exit
	#define CHK_CmpCAARealTimeClockRTCLK_SetTimeZoneInformation_FB_Exit (pICmpCAARealTimeClock != NULL)
	#define EXP_CmpCAARealTimeClockRTCLK_SetTimeZoneInformation_FB_Exit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RTCLK_SetTimeZoneInformation_FB_Exit
	#define EXT_RTCLK_SetTimeZoneInformation_FB_Exit
	#define GET_RTCLK_SetTimeZoneInformation_FB_Exit(fl)  CAL_CMGETAPI( "RTCLK_SetTimeZoneInformation_FB_Exit" ) 
	#define CAL_RTCLK_SetTimeZoneInformation_FB_Exit pICmpCAARealTimeClock->IRTCLK_SetTimeZoneInformation_FB_Exit
	#define CHK_RTCLK_SetTimeZoneInformation_FB_Exit (pICmpCAARealTimeClock != NULL)
	#define EXP_RTCLK_SetTimeZoneInformation_FB_Exit  CAL_CMEXPAPI( "RTCLK_SetTimeZoneInformation_FB_Exit" ) 
#else /* DYNAMIC_LINK */
	#define USE_RTCLK_SetTimeZoneInformation_FB_Exit  PFRTCLK_SETTIMEZONEINFORMATION_FB_EXIT pfRTCLK_SetTimeZoneInformation_FB_Exit;
	#define EXT_RTCLK_SetTimeZoneInformation_FB_Exit  extern PFRTCLK_SETTIMEZONEINFORMATION_FB_EXIT pfRTCLK_SetTimeZoneInformation_FB_Exit;
	#define GET_RTCLK_SetTimeZoneInformation_FB_Exit(fl)  s_pfCMGetAPI2( "RTCLK_SetTimeZoneInformation_FB_Exit", (RTS_VOID_FCTPTR *)&pfRTCLK_SetTimeZoneInformation_FB_Exit, (fl), 0, 0)
	#define CAL_RTCLK_SetTimeZoneInformation_FB_Exit  pfRTCLK_SetTimeZoneInformation_FB_Exit
	#define CHK_RTCLK_SetTimeZoneInformation_FB_Exit  (pfRTCLK_SetTimeZoneInformation_FB_Exit != NULL)
	#define EXP_RTCLK_SetTimeZoneInformation_FB_Exit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_SetTimeZoneInformation_FB_Exit", (RTS_UINTPTR)RTCLK_SetTimeZoneInformation_FB_Exit, 0, 0) 
#endif



unsigned short CDECL RTCLK_GetSupplierVersion(CAA_BOOL xDummy);
typedef unsigned short (CDECL * PFRTCLK_GETSUPPLIERVERSION) (CAA_BOOL xDummy);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_GETSUPPLIERVERSION_NOTIMPLEMENTED)
	#define USE_RTCLK_GetSupplierVersion
	#define EXT_RTCLK_GetSupplierVersion
	#define GET_RTCLK_GetSupplierVersion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RTCLK_GetSupplierVersion(p0)  (unsigned short)ERR_NOTIMPLEMENTED
	#define CHK_RTCLK_GetSupplierVersion  FALSE
	#define EXP_RTCLK_GetSupplierVersion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RTCLK_GetSupplierVersion
	#define EXT_RTCLK_GetSupplierVersion
	#define GET_RTCLK_GetSupplierVersion(fl)  CAL_CMGETAPI( "RTCLK_GetSupplierVersion" ) 
	#define CAL_RTCLK_GetSupplierVersion  RTCLK_GetSupplierVersion
	#define CHK_RTCLK_GetSupplierVersion  TRUE
	#define EXP_RTCLK_GetSupplierVersion  CAL_CMEXPAPI( "RTCLK_GetSupplierVersion" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_RTCLK_GetSupplierVersion
	#define EXT_RTCLK_GetSupplierVersion
	#define GET_RTCLK_GetSupplierVersion(fl)  CAL_CMGETAPI( "RTCLK_GetSupplierVersion" ) 
	#define CAL_RTCLK_GetSupplierVersion  RTCLK_GetSupplierVersion
	#define CHK_RTCLK_GetSupplierVersion  TRUE
	#define EXP_RTCLK_GetSupplierVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_GetSupplierVersion", (RTS_UINTPTR)RTCLK_GetSupplierVersion, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockRTCLK_GetSupplierVersion
	#define EXT_CmpCAARealTimeClockRTCLK_GetSupplierVersion
	#define GET_CmpCAARealTimeClockRTCLK_GetSupplierVersion  ERR_OK
	#define CAL_CmpCAARealTimeClockRTCLK_GetSupplierVersion pICmpCAARealTimeClock->IRTCLK_GetSupplierVersion
	#define CHK_CmpCAARealTimeClockRTCLK_GetSupplierVersion (pICmpCAARealTimeClock != NULL)
	#define EXP_CmpCAARealTimeClockRTCLK_GetSupplierVersion  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RTCLK_GetSupplierVersion
	#define EXT_RTCLK_GetSupplierVersion
	#define GET_RTCLK_GetSupplierVersion(fl)  CAL_CMGETAPI( "RTCLK_GetSupplierVersion" ) 
	#define CAL_RTCLK_GetSupplierVersion pICmpCAARealTimeClock->IRTCLK_GetSupplierVersion
	#define CHK_RTCLK_GetSupplierVersion (pICmpCAARealTimeClock != NULL)
	#define EXP_RTCLK_GetSupplierVersion  CAL_CMEXPAPI( "RTCLK_GetSupplierVersion" ) 
#else /* DYNAMIC_LINK */
	#define USE_RTCLK_GetSupplierVersion  PFRTCLK_GETSUPPLIERVERSION pfRTCLK_GetSupplierVersion;
	#define EXT_RTCLK_GetSupplierVersion  extern PFRTCLK_GETSUPPLIERVERSION pfRTCLK_GetSupplierVersion;
	#define GET_RTCLK_GetSupplierVersion(fl)  s_pfCMGetAPI2( "RTCLK_GetSupplierVersion", (RTS_VOID_FCTPTR *)&pfRTCLK_GetSupplierVersion, (fl), 0, 0)
	#define CAL_RTCLK_GetSupplierVersion  pfRTCLK_GetSupplierVersion
	#define CHK_RTCLK_GetSupplierVersion  (pfRTCLK_GetSupplierVersion != NULL)
	#define EXP_RTCLK_GetSupplierVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_GetSupplierVersion", (RTS_UINTPTR)RTCLK_GetSupplierVersion, 0, 0) 
#endif



RTS_IEC_XWORD CDECL RTCLK_GetProperty(unsigned short usProperty);
typedef RTS_IEC_XWORD (CDECL * PFRTCLK_GETPROPERTY) (unsigned short usProperty);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_GETPROPERTY_NOTIMPLEMENTED)
	#define USE_RTCLK_GetProperty
	#define EXT_RTCLK_GetProperty
	#define GET_RTCLK_GetProperty(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RTCLK_GetProperty(p0)  (RTS_IEC_XWORD)ERR_NOTIMPLEMENTED
	#define CHK_RTCLK_GetProperty  FALSE
	#define EXP_RTCLK_GetProperty  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RTCLK_GetProperty
	#define EXT_RTCLK_GetProperty
	#define GET_RTCLK_GetProperty(fl)  CAL_CMGETAPI( "RTCLK_GetProperty" ) 
	#define CAL_RTCLK_GetProperty  RTCLK_GetProperty
	#define CHK_RTCLK_GetProperty  TRUE
	#define EXP_RTCLK_GetProperty  CAL_CMEXPAPI( "RTCLK_GetProperty" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_RTCLK_GetProperty
	#define EXT_RTCLK_GetProperty
	#define GET_RTCLK_GetProperty(fl)  CAL_CMGETAPI( "RTCLK_GetProperty" ) 
	#define CAL_RTCLK_GetProperty  RTCLK_GetProperty
	#define CHK_RTCLK_GetProperty  TRUE
	#define EXP_RTCLK_GetProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_GetProperty", (RTS_UINTPTR)RTCLK_GetProperty, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockRTCLK_GetProperty
	#define EXT_CmpCAARealTimeClockRTCLK_GetProperty
	#define GET_CmpCAARealTimeClockRTCLK_GetProperty  ERR_OK
	#define CAL_CmpCAARealTimeClockRTCLK_GetProperty pICmpCAARealTimeClock->IRTCLK_GetProperty
	#define CHK_CmpCAARealTimeClockRTCLK_GetProperty (pICmpCAARealTimeClock != NULL)
	#define EXP_CmpCAARealTimeClockRTCLK_GetProperty  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RTCLK_GetProperty
	#define EXT_RTCLK_GetProperty
	#define GET_RTCLK_GetProperty(fl)  CAL_CMGETAPI( "RTCLK_GetProperty" ) 
	#define CAL_RTCLK_GetProperty pICmpCAARealTimeClock->IRTCLK_GetProperty
	#define CHK_RTCLK_GetProperty (pICmpCAARealTimeClock != NULL)
	#define EXP_RTCLK_GetProperty  CAL_CMEXPAPI( "RTCLK_GetProperty" ) 
#else /* DYNAMIC_LINK */
	#define USE_RTCLK_GetProperty  PFRTCLK_GETPROPERTY pfRTCLK_GetProperty;
	#define EXT_RTCLK_GetProperty  extern PFRTCLK_GETPROPERTY pfRTCLK_GetProperty;
	#define GET_RTCLK_GetProperty(fl)  s_pfCMGetAPI2( "RTCLK_GetProperty", (RTS_VOID_FCTPTR *)&pfRTCLK_GetProperty, (fl), 0, 0)
	#define CAL_RTCLK_GetProperty  pfRTCLK_GetProperty
	#define CHK_RTCLK_GetProperty  (pfRTCLK_GetProperty != NULL)
	#define EXP_RTCLK_GetProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RTCLK_GetProperty", (RTS_UINTPTR)RTCLK_GetProperty, 0, 0) 
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
 * <description>RTCLK_GETTIMEZONEINFORMATION_PARAMS</description>
 */
typedef struct tagRTCLK_GETTIMEZONEINFORMATION_PARAMS
{
	RTCLK_TIME_ZONE_INFO tziTimezone;
} RTCLK_GETTIMEZONEINFORMATION_PARAMS;

/**
 * <description>RTCLK_SETTIMEZONEINFORMATION_PARAMS</description>
 */
typedef struct tagRTCLK_SETTIMEZONEINFORMATION_PARAMS
{
	RTCLK_TIME_ZONE_INFO tziTimezone;
} RTCLK_SETTIMEZONEINFORMATION_PARAMS;

/**
 * <description>RTCLK_SETDATEANDTIME_PARAMS</description>
 */
typedef struct tagRTCLK_SETDATEANDTIME_PARAMS
{
	RTS_IEC_DATE_AND_TIME dtDateAndTime;
} RTCLK_SETDATEANDTIME_PARAMS;

/**
 * <description>RTCLK_GETDATEANDTIME_PARAMS</description>
 */
typedef struct tagRTCLK_GETDATEANDTIME_PARAMS
{
	RTS_IEC_DATE_AND_TIME dtDateAndTime;
	CAA_ENUM eTimezone;
} RTCLK_GETDATEANDTIME_PARAMS;

/**
 * <description>rtclk_getdateandtime__main</description>
 */
typedef struct tagrtclk_getdateandtime_struct
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
	CAA_ENUM eTimezone;					/* VAR_OUTPUT */	
	CAA_BOOL xPreviousExecute;			/* Local variable */	/* value of xExecute in previous cycle */
	CAA_BOOL xPreviousAbortInProgress;	/* Local variable */	/* value of xAbortInPrograss in previous cycle */
	CAA_BOOL xAbortInProgress;			/* Local variable */	/* TRUE: abort is processed
											FALSE: abort is done */
	RTS_IEC_INT iError;					/* Local variable */	/* Local library error ID is transfered to eError by the concrete implementation */
	CAA_HANDLE hJob;					/* Local variable */	/* specific vars */
	RTCLK_GETDATEANDTIME_PARAMS *pGetDateAndTimeParams;	/* Local variable */	
	ASM_STATE StateJob;					/* Local variable */	
	RTS_IEC_XWORD dwEtrigClass;			/* Local variable */	
} rtclk_getdateandtime_struct;

/**
 * <description>rtclk_getdateandtime_main</description>
 */
typedef struct tagrtclk_getdateandtime_main_struct
{
	rtclk_getdateandtime_struct *pInstance;	/* VAR_INPUT */	
} rtclk_getdateandtime_main_struct;

void CDECL CDECL_EXT rtclk_getdateandtime__main(rtclk_getdateandtime_main_struct *p);
typedef void (CDECL CDECL_EXT* PFRTCLK_GETDATEANDTIME__MAIN_IEC) (rtclk_getdateandtime_main_struct *p);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_GETDATEANDTIME__MAIN_NOTIMPLEMENTED)
	#define USE_rtclk_getdateandtime__main
	#define EXT_rtclk_getdateandtime__main
	#define GET_rtclk_getdateandtime__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_rtclk_getdateandtime__main(p0) 
	#define CHK_rtclk_getdateandtime__main  FALSE
	#define EXP_rtclk_getdateandtime__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_rtclk_getdateandtime__main
	#define EXT_rtclk_getdateandtime__main
	#define GET_rtclk_getdateandtime__main(fl)  CAL_CMGETAPI( "rtclk_getdateandtime__main" ) 
	#define CAL_rtclk_getdateandtime__main  rtclk_getdateandtime__main
	#define CHK_rtclk_getdateandtime__main  TRUE
	#define EXP_rtclk_getdateandtime__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getdateandtime__main", (RTS_UINTPTR)rtclk_getdateandtime__main, 1, RTSITF_GET_SIGNATURE(0, 0xA101FA6A), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_rtclk_getdateandtime__main
	#define EXT_rtclk_getdateandtime__main
	#define GET_rtclk_getdateandtime__main(fl)  CAL_CMGETAPI( "rtclk_getdateandtime__main" ) 
	#define CAL_rtclk_getdateandtime__main  rtclk_getdateandtime__main
	#define CHK_rtclk_getdateandtime__main  TRUE
	#define EXP_rtclk_getdateandtime__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getdateandtime__main", (RTS_UINTPTR)rtclk_getdateandtime__main, 1, RTSITF_GET_SIGNATURE(0, 0xA101FA6A), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockrtclk_getdateandtime__main
	#define EXT_CmpCAARealTimeClockrtclk_getdateandtime__main
	#define GET_CmpCAARealTimeClockrtclk_getdateandtime__main  ERR_OK
	#define CAL_CmpCAARealTimeClockrtclk_getdateandtime__main  rtclk_getdateandtime__main
	#define CHK_CmpCAARealTimeClockrtclk_getdateandtime__main  TRUE
	#define EXP_CmpCAARealTimeClockrtclk_getdateandtime__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getdateandtime__main", (RTS_UINTPTR)rtclk_getdateandtime__main, 1, RTSITF_GET_SIGNATURE(0, 0xA101FA6A), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_rtclk_getdateandtime__main
	#define EXT_rtclk_getdateandtime__main
	#define GET_rtclk_getdateandtime__main(fl)  CAL_CMGETAPI( "rtclk_getdateandtime__main" ) 
	#define CAL_rtclk_getdateandtime__main  rtclk_getdateandtime__main
	#define CHK_rtclk_getdateandtime__main  TRUE
	#define EXP_rtclk_getdateandtime__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getdateandtime__main", (RTS_UINTPTR)rtclk_getdateandtime__main, 1, RTSITF_GET_SIGNATURE(0, 0xA101FA6A), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_rtclk_getdateandtime__main  PFRTCLK_GETDATEANDTIME__MAIN_IEC pfrtclk_getdateandtime__main;
	#define EXT_rtclk_getdateandtime__main  extern PFRTCLK_GETDATEANDTIME__MAIN_IEC pfrtclk_getdateandtime__main;
	#define GET_rtclk_getdateandtime__main(fl)  s_pfCMGetAPI2( "rtclk_getdateandtime__main", (RTS_VOID_FCTPTR *)&pfrtclk_getdateandtime__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xA101FA6A), 0x03050528)
	#define CAL_rtclk_getdateandtime__main  pfrtclk_getdateandtime__main
	#define CHK_rtclk_getdateandtime__main  (pfrtclk_getdateandtime__main != NULL)
	#define EXP_rtclk_getdateandtime__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getdateandtime__main", (RTS_UINTPTR)rtclk_getdateandtime__main, 1, RTSITF_GET_SIGNATURE(0, 0xA101FA6A), 0x03050528) 
#endif


/**
 * <description>rtclk_getdateandtime_fb_init</description>
 */
typedef struct tagrtclk_getdateandtime_fb_init_struct
{
	rtclk_getdateandtime_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInitRetains;				/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Init;					/* VAR_OUTPUT */	
} rtclk_getdateandtime_fb_init_struct;

void CDECL CDECL_EXT rtclk_getdateandtime__fb_init(rtclk_getdateandtime_fb_init_struct *p);
typedef void (CDECL CDECL_EXT* PFRTCLK_GETDATEANDTIME__FB_INIT_IEC) (rtclk_getdateandtime_fb_init_struct *p);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_GETDATEANDTIME__FB_INIT_NOTIMPLEMENTED)
	#define USE_rtclk_getdateandtime__fb_init
	#define EXT_rtclk_getdateandtime__fb_init
	#define GET_rtclk_getdateandtime__fb_init(fl)  ERR_NOTIMPLEMENTED
	#define CAL_rtclk_getdateandtime__fb_init(p0) 
	#define CHK_rtclk_getdateandtime__fb_init  FALSE
	#define EXP_rtclk_getdateandtime__fb_init  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_rtclk_getdateandtime__fb_init
	#define EXT_rtclk_getdateandtime__fb_init
	#define GET_rtclk_getdateandtime__fb_init(fl)  CAL_CMGETAPI( "rtclk_getdateandtime__fb_init" ) 
	#define CAL_rtclk_getdateandtime__fb_init  rtclk_getdateandtime__fb_init
	#define CHK_rtclk_getdateandtime__fb_init  TRUE
	#define EXP_rtclk_getdateandtime__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getdateandtime__fb_init", (RTS_UINTPTR)rtclk_getdateandtime__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0xD64C25C7), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_rtclk_getdateandtime__fb_init
	#define EXT_rtclk_getdateandtime__fb_init
	#define GET_rtclk_getdateandtime__fb_init(fl)  CAL_CMGETAPI( "rtclk_getdateandtime__fb_init" ) 
	#define CAL_rtclk_getdateandtime__fb_init  rtclk_getdateandtime__fb_init
	#define CHK_rtclk_getdateandtime__fb_init  TRUE
	#define EXP_rtclk_getdateandtime__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getdateandtime__fb_init", (RTS_UINTPTR)rtclk_getdateandtime__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0xD64C25C7), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockrtclk_getdateandtime__fb_init
	#define EXT_CmpCAARealTimeClockrtclk_getdateandtime__fb_init
	#define GET_CmpCAARealTimeClockrtclk_getdateandtime__fb_init  ERR_OK
	#define CAL_CmpCAARealTimeClockrtclk_getdateandtime__fb_init  rtclk_getdateandtime__fb_init
	#define CHK_CmpCAARealTimeClockrtclk_getdateandtime__fb_init  TRUE
	#define EXP_CmpCAARealTimeClockrtclk_getdateandtime__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getdateandtime__fb_init", (RTS_UINTPTR)rtclk_getdateandtime__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0xD64C25C7), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_rtclk_getdateandtime__fb_init
	#define EXT_rtclk_getdateandtime__fb_init
	#define GET_rtclk_getdateandtime__fb_init(fl)  CAL_CMGETAPI( "rtclk_getdateandtime__fb_init" ) 
	#define CAL_rtclk_getdateandtime__fb_init  rtclk_getdateandtime__fb_init
	#define CHK_rtclk_getdateandtime__fb_init  TRUE
	#define EXP_rtclk_getdateandtime__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getdateandtime__fb_init", (RTS_UINTPTR)rtclk_getdateandtime__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0xD64C25C7), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_rtclk_getdateandtime__fb_init  PFRTCLK_GETDATEANDTIME__FB_INIT_IEC pfrtclk_getdateandtime__fb_init;
	#define EXT_rtclk_getdateandtime__fb_init  extern PFRTCLK_GETDATEANDTIME__FB_INIT_IEC pfrtclk_getdateandtime__fb_init;
	#define GET_rtclk_getdateandtime__fb_init(fl)  s_pfCMGetAPI2( "rtclk_getdateandtime__fb_init", (RTS_VOID_FCTPTR *)&pfrtclk_getdateandtime__fb_init, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xD64C25C7), 0x03050528)
	#define CAL_rtclk_getdateandtime__fb_init  pfrtclk_getdateandtime__fb_init
	#define CHK_rtclk_getdateandtime__fb_init  (pfrtclk_getdateandtime__fb_init != NULL)
	#define EXP_rtclk_getdateandtime__fb_init   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getdateandtime__fb_init", (RTS_UINTPTR)rtclk_getdateandtime__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0xD64C25C7), 0x03050528) 
#endif


/**
 * <description>rtclk_getdateandtime_fb_exit</description>
 */
typedef struct tagrtclk_getdateandtime_fb_exit_struct
{
	rtclk_getdateandtime_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Exit;					/* VAR_OUTPUT */	
} rtclk_getdateandtime_fb_exit_struct;

void CDECL CDECL_EXT rtclk_getdateandtime__fb_exit(rtclk_getdateandtime_fb_exit_struct *p);
typedef void (CDECL CDECL_EXT* PFRTCLK_GETDATEANDTIME__FB_EXIT_IEC) (rtclk_getdateandtime_fb_exit_struct *p);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_GETDATEANDTIME__FB_EXIT_NOTIMPLEMENTED)
	#define USE_rtclk_getdateandtime__fb_exit
	#define EXT_rtclk_getdateandtime__fb_exit
	#define GET_rtclk_getdateandtime__fb_exit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_rtclk_getdateandtime__fb_exit(p0) 
	#define CHK_rtclk_getdateandtime__fb_exit  FALSE
	#define EXP_rtclk_getdateandtime__fb_exit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_rtclk_getdateandtime__fb_exit
	#define EXT_rtclk_getdateandtime__fb_exit
	#define GET_rtclk_getdateandtime__fb_exit(fl)  CAL_CMGETAPI( "rtclk_getdateandtime__fb_exit" ) 
	#define CAL_rtclk_getdateandtime__fb_exit  rtclk_getdateandtime__fb_exit
	#define CHK_rtclk_getdateandtime__fb_exit  TRUE
	#define EXP_rtclk_getdateandtime__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getdateandtime__fb_exit", (RTS_UINTPTR)rtclk_getdateandtime__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xA9565B5F), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_rtclk_getdateandtime__fb_exit
	#define EXT_rtclk_getdateandtime__fb_exit
	#define GET_rtclk_getdateandtime__fb_exit(fl)  CAL_CMGETAPI( "rtclk_getdateandtime__fb_exit" ) 
	#define CAL_rtclk_getdateandtime__fb_exit  rtclk_getdateandtime__fb_exit
	#define CHK_rtclk_getdateandtime__fb_exit  TRUE
	#define EXP_rtclk_getdateandtime__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getdateandtime__fb_exit", (RTS_UINTPTR)rtclk_getdateandtime__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xA9565B5F), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockrtclk_getdateandtime__fb_exit
	#define EXT_CmpCAARealTimeClockrtclk_getdateandtime__fb_exit
	#define GET_CmpCAARealTimeClockrtclk_getdateandtime__fb_exit  ERR_OK
	#define CAL_CmpCAARealTimeClockrtclk_getdateandtime__fb_exit  rtclk_getdateandtime__fb_exit
	#define CHK_CmpCAARealTimeClockrtclk_getdateandtime__fb_exit  TRUE
	#define EXP_CmpCAARealTimeClockrtclk_getdateandtime__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getdateandtime__fb_exit", (RTS_UINTPTR)rtclk_getdateandtime__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xA9565B5F), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_rtclk_getdateandtime__fb_exit
	#define EXT_rtclk_getdateandtime__fb_exit
	#define GET_rtclk_getdateandtime__fb_exit(fl)  CAL_CMGETAPI( "rtclk_getdateandtime__fb_exit" ) 
	#define CAL_rtclk_getdateandtime__fb_exit  rtclk_getdateandtime__fb_exit
	#define CHK_rtclk_getdateandtime__fb_exit  TRUE
	#define EXP_rtclk_getdateandtime__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getdateandtime__fb_exit", (RTS_UINTPTR)rtclk_getdateandtime__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xA9565B5F), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_rtclk_getdateandtime__fb_exit  PFRTCLK_GETDATEANDTIME__FB_EXIT_IEC pfrtclk_getdateandtime__fb_exit;
	#define EXT_rtclk_getdateandtime__fb_exit  extern PFRTCLK_GETDATEANDTIME__FB_EXIT_IEC pfrtclk_getdateandtime__fb_exit;
	#define GET_rtclk_getdateandtime__fb_exit(fl)  s_pfCMGetAPI2( "rtclk_getdateandtime__fb_exit", (RTS_VOID_FCTPTR *)&pfrtclk_getdateandtime__fb_exit, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xA9565B5F), 0x03050528)
	#define CAL_rtclk_getdateandtime__fb_exit  pfrtclk_getdateandtime__fb_exit
	#define CHK_rtclk_getdateandtime__fb_exit  (pfrtclk_getdateandtime__fb_exit != NULL)
	#define EXP_rtclk_getdateandtime__fb_exit   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getdateandtime__fb_exit", (RTS_UINTPTR)rtclk_getdateandtime__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xA9565B5F), 0x03050528) 
#endif


/**
 * <description>rtclk_getproperty</description>
 */
typedef struct tagrtclk_getproperty_struct
{
	RTS_IEC_WORD wProperty;				/* VAR_INPUT */	/* property number */
	RTS_IEC_XWORD RTCLK_GetProperty;	/* VAR_OUTPUT */	
} rtclk_getproperty_struct;

void CDECL CDECL_EXT rtclk_getproperty(rtclk_getproperty_struct *p);
typedef void (CDECL CDECL_EXT* PFRTCLK_GETPROPERTY_IEC) (rtclk_getproperty_struct *p);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_GETPROPERTY_NOTIMPLEMENTED)
	#define USE_rtclk_getproperty
	#define EXT_rtclk_getproperty
	#define GET_rtclk_getproperty(fl)  ERR_NOTIMPLEMENTED
	#define CAL_rtclk_getproperty(p0) 
	#define CHK_rtclk_getproperty  FALSE
	#define EXP_rtclk_getproperty  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_rtclk_getproperty
	#define EXT_rtclk_getproperty
	#define GET_rtclk_getproperty(fl)  CAL_CMGETAPI( "rtclk_getproperty" ) 
	#define CAL_rtclk_getproperty  rtclk_getproperty
	#define CHK_rtclk_getproperty  TRUE
	#define EXP_rtclk_getproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getproperty", (RTS_UINTPTR)rtclk_getproperty, 1, RTSITF_GET_SIGNATURE(0, 0xCE228B87), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_rtclk_getproperty
	#define EXT_rtclk_getproperty
	#define GET_rtclk_getproperty(fl)  CAL_CMGETAPI( "rtclk_getproperty" ) 
	#define CAL_rtclk_getproperty  rtclk_getproperty
	#define CHK_rtclk_getproperty  TRUE
	#define EXP_rtclk_getproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getproperty", (RTS_UINTPTR)rtclk_getproperty, 1, RTSITF_GET_SIGNATURE(0, 0xCE228B87), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockrtclk_getproperty
	#define EXT_CmpCAARealTimeClockrtclk_getproperty
	#define GET_CmpCAARealTimeClockrtclk_getproperty  ERR_OK
	#define CAL_CmpCAARealTimeClockrtclk_getproperty  rtclk_getproperty
	#define CHK_CmpCAARealTimeClockrtclk_getproperty  TRUE
	#define EXP_CmpCAARealTimeClockrtclk_getproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getproperty", (RTS_UINTPTR)rtclk_getproperty, 1, RTSITF_GET_SIGNATURE(0, 0xCE228B87), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_rtclk_getproperty
	#define EXT_rtclk_getproperty
	#define GET_rtclk_getproperty(fl)  CAL_CMGETAPI( "rtclk_getproperty" ) 
	#define CAL_rtclk_getproperty  rtclk_getproperty
	#define CHK_rtclk_getproperty  TRUE
	#define EXP_rtclk_getproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getproperty", (RTS_UINTPTR)rtclk_getproperty, 1, RTSITF_GET_SIGNATURE(0, 0xCE228B87), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_rtclk_getproperty  PFRTCLK_GETPROPERTY_IEC pfrtclk_getproperty;
	#define EXT_rtclk_getproperty  extern PFRTCLK_GETPROPERTY_IEC pfrtclk_getproperty;
	#define GET_rtclk_getproperty(fl)  s_pfCMGetAPI2( "rtclk_getproperty", (RTS_VOID_FCTPTR *)&pfrtclk_getproperty, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xCE228B87), 0x03050528)
	#define CAL_rtclk_getproperty  pfrtclk_getproperty
	#define CHK_rtclk_getproperty  (pfrtclk_getproperty != NULL)
	#define EXP_rtclk_getproperty   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getproperty", (RTS_UINTPTR)rtclk_getproperty, 1, RTSITF_GET_SIGNATURE(0, 0xCE228B87), 0x03050528) 
#endif


/**
 * <description>rtclk_getsupplierversion</description>
 */
typedef struct tagrtclk_getsupplierversion_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	RTS_IEC_WORD RTCLK_GetSupplierVersion;	/* VAR_OUTPUT */	
} rtclk_getsupplierversion_struct;

void CDECL CDECL_EXT rtclk_getsupplierversion(rtclk_getsupplierversion_struct *p);
typedef void (CDECL CDECL_EXT* PFRTCLK_GETSUPPLIERVERSION_IEC) (rtclk_getsupplierversion_struct *p);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_GETSUPPLIERVERSION_NOTIMPLEMENTED)
	#define USE_rtclk_getsupplierversion
	#define EXT_rtclk_getsupplierversion
	#define GET_rtclk_getsupplierversion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_rtclk_getsupplierversion(p0) 
	#define CHK_rtclk_getsupplierversion  FALSE
	#define EXP_rtclk_getsupplierversion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_rtclk_getsupplierversion
	#define EXT_rtclk_getsupplierversion
	#define GET_rtclk_getsupplierversion(fl)  CAL_CMGETAPI( "rtclk_getsupplierversion" ) 
	#define CAL_rtclk_getsupplierversion  rtclk_getsupplierversion
	#define CHK_rtclk_getsupplierversion  TRUE
	#define EXP_rtclk_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getsupplierversion", (RTS_UINTPTR)rtclk_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0x25593C3C), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_rtclk_getsupplierversion
	#define EXT_rtclk_getsupplierversion
	#define GET_rtclk_getsupplierversion(fl)  CAL_CMGETAPI( "rtclk_getsupplierversion" ) 
	#define CAL_rtclk_getsupplierversion  rtclk_getsupplierversion
	#define CHK_rtclk_getsupplierversion  TRUE
	#define EXP_rtclk_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getsupplierversion", (RTS_UINTPTR)rtclk_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0x25593C3C), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockrtclk_getsupplierversion
	#define EXT_CmpCAARealTimeClockrtclk_getsupplierversion
	#define GET_CmpCAARealTimeClockrtclk_getsupplierversion  ERR_OK
	#define CAL_CmpCAARealTimeClockrtclk_getsupplierversion  rtclk_getsupplierversion
	#define CHK_CmpCAARealTimeClockrtclk_getsupplierversion  TRUE
	#define EXP_CmpCAARealTimeClockrtclk_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getsupplierversion", (RTS_UINTPTR)rtclk_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0x25593C3C), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_rtclk_getsupplierversion
	#define EXT_rtclk_getsupplierversion
	#define GET_rtclk_getsupplierversion(fl)  CAL_CMGETAPI( "rtclk_getsupplierversion" ) 
	#define CAL_rtclk_getsupplierversion  rtclk_getsupplierversion
	#define CHK_rtclk_getsupplierversion  TRUE
	#define EXP_rtclk_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getsupplierversion", (RTS_UINTPTR)rtclk_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0x25593C3C), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_rtclk_getsupplierversion  PFRTCLK_GETSUPPLIERVERSION_IEC pfrtclk_getsupplierversion;
	#define EXT_rtclk_getsupplierversion  extern PFRTCLK_GETSUPPLIERVERSION_IEC pfrtclk_getsupplierversion;
	#define GET_rtclk_getsupplierversion(fl)  s_pfCMGetAPI2( "rtclk_getsupplierversion", (RTS_VOID_FCTPTR *)&pfrtclk_getsupplierversion, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x25593C3C), 0x03050528)
	#define CAL_rtclk_getsupplierversion  pfrtclk_getsupplierversion
	#define CHK_rtclk_getsupplierversion  (pfrtclk_getsupplierversion != NULL)
	#define EXP_rtclk_getsupplierversion   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_getsupplierversion", (RTS_UINTPTR)rtclk_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0x25593C3C), 0x03050528) 
#endif


/**
 * <description>rtclk_gettimezoneinformation__main</description>
 */
typedef struct tagrtclk_gettimezoneinformation_struct
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
	RTCLK_GETTIMEZONEINFORMATION_PARAMS *pGetTimeZoneInformationParams;	/* Local variable */	
	ASM_STATE StateJob;					/* Local variable */	
	RTS_IEC_XWORD dwEtrigClass;			/* Local variable */	
} rtclk_gettimezoneinformation_struct;

/**
 * <description>rtclk_gettimezoneinformation_main</description>
 */
typedef struct tagrtclk_gettimezoneinformation_main_struct
{
	rtclk_gettimezoneinformation_struct *pInstance;	/* VAR_INPUT */	
} rtclk_gettimezoneinformation_main_struct;

void CDECL CDECL_EXT rtclk_gettimezoneinformation__main(rtclk_gettimezoneinformation_main_struct *p);
typedef void (CDECL CDECL_EXT* PFRTCLK_GETTIMEZONEINFORMATION__MAIN_IEC) (rtclk_gettimezoneinformation_main_struct *p);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_GETTIMEZONEINFORMATION__MAIN_NOTIMPLEMENTED)
	#define USE_rtclk_gettimezoneinformation__main
	#define EXT_rtclk_gettimezoneinformation__main
	#define GET_rtclk_gettimezoneinformation__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_rtclk_gettimezoneinformation__main(p0) 
	#define CHK_rtclk_gettimezoneinformation__main  FALSE
	#define EXP_rtclk_gettimezoneinformation__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_rtclk_gettimezoneinformation__main
	#define EXT_rtclk_gettimezoneinformation__main
	#define GET_rtclk_gettimezoneinformation__main(fl)  CAL_CMGETAPI( "rtclk_gettimezoneinformation__main" ) 
	#define CAL_rtclk_gettimezoneinformation__main  rtclk_gettimezoneinformation__main
	#define CHK_rtclk_gettimezoneinformation__main  TRUE
	#define EXP_rtclk_gettimezoneinformation__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_gettimezoneinformation__main", (RTS_UINTPTR)rtclk_gettimezoneinformation__main, 1, RTSITF_GET_SIGNATURE(0, 0x9FDA8153), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_rtclk_gettimezoneinformation__main
	#define EXT_rtclk_gettimezoneinformation__main
	#define GET_rtclk_gettimezoneinformation__main(fl)  CAL_CMGETAPI( "rtclk_gettimezoneinformation__main" ) 
	#define CAL_rtclk_gettimezoneinformation__main  rtclk_gettimezoneinformation__main
	#define CHK_rtclk_gettimezoneinformation__main  TRUE
	#define EXP_rtclk_gettimezoneinformation__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_gettimezoneinformation__main", (RTS_UINTPTR)rtclk_gettimezoneinformation__main, 1, RTSITF_GET_SIGNATURE(0, 0x9FDA8153), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockrtclk_gettimezoneinformation__main
	#define EXT_CmpCAARealTimeClockrtclk_gettimezoneinformation__main
	#define GET_CmpCAARealTimeClockrtclk_gettimezoneinformation__main  ERR_OK
	#define CAL_CmpCAARealTimeClockrtclk_gettimezoneinformation__main  rtclk_gettimezoneinformation__main
	#define CHK_CmpCAARealTimeClockrtclk_gettimezoneinformation__main  TRUE
	#define EXP_CmpCAARealTimeClockrtclk_gettimezoneinformation__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_gettimezoneinformation__main", (RTS_UINTPTR)rtclk_gettimezoneinformation__main, 1, RTSITF_GET_SIGNATURE(0, 0x9FDA8153), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_rtclk_gettimezoneinformation__main
	#define EXT_rtclk_gettimezoneinformation__main
	#define GET_rtclk_gettimezoneinformation__main(fl)  CAL_CMGETAPI( "rtclk_gettimezoneinformation__main" ) 
	#define CAL_rtclk_gettimezoneinformation__main  rtclk_gettimezoneinformation__main
	#define CHK_rtclk_gettimezoneinformation__main  TRUE
	#define EXP_rtclk_gettimezoneinformation__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_gettimezoneinformation__main", (RTS_UINTPTR)rtclk_gettimezoneinformation__main, 1, RTSITF_GET_SIGNATURE(0, 0x9FDA8153), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_rtclk_gettimezoneinformation__main  PFRTCLK_GETTIMEZONEINFORMATION__MAIN_IEC pfrtclk_gettimezoneinformation__main;
	#define EXT_rtclk_gettimezoneinformation__main  extern PFRTCLK_GETTIMEZONEINFORMATION__MAIN_IEC pfrtclk_gettimezoneinformation__main;
	#define GET_rtclk_gettimezoneinformation__main(fl)  s_pfCMGetAPI2( "rtclk_gettimezoneinformation__main", (RTS_VOID_FCTPTR *)&pfrtclk_gettimezoneinformation__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x9FDA8153), 0x03050528)
	#define CAL_rtclk_gettimezoneinformation__main  pfrtclk_gettimezoneinformation__main
	#define CHK_rtclk_gettimezoneinformation__main  (pfrtclk_gettimezoneinformation__main != NULL)
	#define EXP_rtclk_gettimezoneinformation__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_gettimezoneinformation__main", (RTS_UINTPTR)rtclk_gettimezoneinformation__main, 1, RTSITF_GET_SIGNATURE(0, 0x9FDA8153), 0x03050528) 
#endif


/**
 * <description>rtclk_gettimezoneinformation_fb_init</description>
 */
typedef struct tagrtclk_gettimezoneinformation_fb_init_struct
{
	rtclk_gettimezoneinformation_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInitRetains;				/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Init;					/* VAR_OUTPUT */	
} rtclk_gettimezoneinformation_fb_init_struct;

void CDECL CDECL_EXT rtclk_gettimezoneinformation__fb_init(rtclk_gettimezoneinformation_fb_init_struct *p);
typedef void (CDECL CDECL_EXT* PFRTCLK_GETTIMEZONEINFORMATION__FB_INIT_IEC) (rtclk_gettimezoneinformation_fb_init_struct *p);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_GETTIMEZONEINFORMATION__FB_INIT_NOTIMPLEMENTED)
	#define USE_rtclk_gettimezoneinformation__fb_init
	#define EXT_rtclk_gettimezoneinformation__fb_init
	#define GET_rtclk_gettimezoneinformation__fb_init(fl)  ERR_NOTIMPLEMENTED
	#define CAL_rtclk_gettimezoneinformation__fb_init(p0) 
	#define CHK_rtclk_gettimezoneinformation__fb_init  FALSE
	#define EXP_rtclk_gettimezoneinformation__fb_init  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_rtclk_gettimezoneinformation__fb_init
	#define EXT_rtclk_gettimezoneinformation__fb_init
	#define GET_rtclk_gettimezoneinformation__fb_init(fl)  CAL_CMGETAPI( "rtclk_gettimezoneinformation__fb_init" ) 
	#define CAL_rtclk_gettimezoneinformation__fb_init  rtclk_gettimezoneinformation__fb_init
	#define CHK_rtclk_gettimezoneinformation__fb_init  TRUE
	#define EXP_rtclk_gettimezoneinformation__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_gettimezoneinformation__fb_init", (RTS_UINTPTR)rtclk_gettimezoneinformation__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0xC7722D11), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_rtclk_gettimezoneinformation__fb_init
	#define EXT_rtclk_gettimezoneinformation__fb_init
	#define GET_rtclk_gettimezoneinformation__fb_init(fl)  CAL_CMGETAPI( "rtclk_gettimezoneinformation__fb_init" ) 
	#define CAL_rtclk_gettimezoneinformation__fb_init  rtclk_gettimezoneinformation__fb_init
	#define CHK_rtclk_gettimezoneinformation__fb_init  TRUE
	#define EXP_rtclk_gettimezoneinformation__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_gettimezoneinformation__fb_init", (RTS_UINTPTR)rtclk_gettimezoneinformation__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0xC7722D11), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockrtclk_gettimezoneinformation__fb_init
	#define EXT_CmpCAARealTimeClockrtclk_gettimezoneinformation__fb_init
	#define GET_CmpCAARealTimeClockrtclk_gettimezoneinformation__fb_init  ERR_OK
	#define CAL_CmpCAARealTimeClockrtclk_gettimezoneinformation__fb_init  rtclk_gettimezoneinformation__fb_init
	#define CHK_CmpCAARealTimeClockrtclk_gettimezoneinformation__fb_init  TRUE
	#define EXP_CmpCAARealTimeClockrtclk_gettimezoneinformation__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_gettimezoneinformation__fb_init", (RTS_UINTPTR)rtclk_gettimezoneinformation__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0xC7722D11), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_rtclk_gettimezoneinformation__fb_init
	#define EXT_rtclk_gettimezoneinformation__fb_init
	#define GET_rtclk_gettimezoneinformation__fb_init(fl)  CAL_CMGETAPI( "rtclk_gettimezoneinformation__fb_init" ) 
	#define CAL_rtclk_gettimezoneinformation__fb_init  rtclk_gettimezoneinformation__fb_init
	#define CHK_rtclk_gettimezoneinformation__fb_init  TRUE
	#define EXP_rtclk_gettimezoneinformation__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_gettimezoneinformation__fb_init", (RTS_UINTPTR)rtclk_gettimezoneinformation__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0xC7722D11), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_rtclk_gettimezoneinformation__fb_init  PFRTCLK_GETTIMEZONEINFORMATION__FB_INIT_IEC pfrtclk_gettimezoneinformation__fb_init;
	#define EXT_rtclk_gettimezoneinformation__fb_init  extern PFRTCLK_GETTIMEZONEINFORMATION__FB_INIT_IEC pfrtclk_gettimezoneinformation__fb_init;
	#define GET_rtclk_gettimezoneinformation__fb_init(fl)  s_pfCMGetAPI2( "rtclk_gettimezoneinformation__fb_init", (RTS_VOID_FCTPTR *)&pfrtclk_gettimezoneinformation__fb_init, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xC7722D11), 0x03050528)
	#define CAL_rtclk_gettimezoneinformation__fb_init  pfrtclk_gettimezoneinformation__fb_init
	#define CHK_rtclk_gettimezoneinformation__fb_init  (pfrtclk_gettimezoneinformation__fb_init != NULL)
	#define EXP_rtclk_gettimezoneinformation__fb_init   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_gettimezoneinformation__fb_init", (RTS_UINTPTR)rtclk_gettimezoneinformation__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0xC7722D11), 0x03050528) 
#endif


/**
 * <description>rtclk_gettimezoneinformation_fb_exit</description>
 */
typedef struct tagrtclk_gettimezoneinformation_fb_exit_struct
{
	rtclk_gettimezoneinformation_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Exit;					/* VAR_OUTPUT */	
} rtclk_gettimezoneinformation_fb_exit_struct;

void CDECL CDECL_EXT rtclk_gettimezoneinformation__fb_exit(rtclk_gettimezoneinformation_fb_exit_struct *p);
typedef void (CDECL CDECL_EXT* PFRTCLK_GETTIMEZONEINFORMATION__FB_EXIT_IEC) (rtclk_gettimezoneinformation_fb_exit_struct *p);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_GETTIMEZONEINFORMATION__FB_EXIT_NOTIMPLEMENTED)
	#define USE_rtclk_gettimezoneinformation__fb_exit
	#define EXT_rtclk_gettimezoneinformation__fb_exit
	#define GET_rtclk_gettimezoneinformation__fb_exit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_rtclk_gettimezoneinformation__fb_exit(p0) 
	#define CHK_rtclk_gettimezoneinformation__fb_exit  FALSE
	#define EXP_rtclk_gettimezoneinformation__fb_exit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_rtclk_gettimezoneinformation__fb_exit
	#define EXT_rtclk_gettimezoneinformation__fb_exit
	#define GET_rtclk_gettimezoneinformation__fb_exit(fl)  CAL_CMGETAPI( "rtclk_gettimezoneinformation__fb_exit" ) 
	#define CAL_rtclk_gettimezoneinformation__fb_exit  rtclk_gettimezoneinformation__fb_exit
	#define CHK_rtclk_gettimezoneinformation__fb_exit  TRUE
	#define EXP_rtclk_gettimezoneinformation__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_gettimezoneinformation__fb_exit", (RTS_UINTPTR)rtclk_gettimezoneinformation__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0x578320C7), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_rtclk_gettimezoneinformation__fb_exit
	#define EXT_rtclk_gettimezoneinformation__fb_exit
	#define GET_rtclk_gettimezoneinformation__fb_exit(fl)  CAL_CMGETAPI( "rtclk_gettimezoneinformation__fb_exit" ) 
	#define CAL_rtclk_gettimezoneinformation__fb_exit  rtclk_gettimezoneinformation__fb_exit
	#define CHK_rtclk_gettimezoneinformation__fb_exit  TRUE
	#define EXP_rtclk_gettimezoneinformation__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_gettimezoneinformation__fb_exit", (RTS_UINTPTR)rtclk_gettimezoneinformation__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0x578320C7), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockrtclk_gettimezoneinformation__fb_exit
	#define EXT_CmpCAARealTimeClockrtclk_gettimezoneinformation__fb_exit
	#define GET_CmpCAARealTimeClockrtclk_gettimezoneinformation__fb_exit  ERR_OK
	#define CAL_CmpCAARealTimeClockrtclk_gettimezoneinformation__fb_exit  rtclk_gettimezoneinformation__fb_exit
	#define CHK_CmpCAARealTimeClockrtclk_gettimezoneinformation__fb_exit  TRUE
	#define EXP_CmpCAARealTimeClockrtclk_gettimezoneinformation__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_gettimezoneinformation__fb_exit", (RTS_UINTPTR)rtclk_gettimezoneinformation__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0x578320C7), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_rtclk_gettimezoneinformation__fb_exit
	#define EXT_rtclk_gettimezoneinformation__fb_exit
	#define GET_rtclk_gettimezoneinformation__fb_exit(fl)  CAL_CMGETAPI( "rtclk_gettimezoneinformation__fb_exit" ) 
	#define CAL_rtclk_gettimezoneinformation__fb_exit  rtclk_gettimezoneinformation__fb_exit
	#define CHK_rtclk_gettimezoneinformation__fb_exit  TRUE
	#define EXP_rtclk_gettimezoneinformation__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_gettimezoneinformation__fb_exit", (RTS_UINTPTR)rtclk_gettimezoneinformation__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0x578320C7), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_rtclk_gettimezoneinformation__fb_exit  PFRTCLK_GETTIMEZONEINFORMATION__FB_EXIT_IEC pfrtclk_gettimezoneinformation__fb_exit;
	#define EXT_rtclk_gettimezoneinformation__fb_exit  extern PFRTCLK_GETTIMEZONEINFORMATION__FB_EXIT_IEC pfrtclk_gettimezoneinformation__fb_exit;
	#define GET_rtclk_gettimezoneinformation__fb_exit(fl)  s_pfCMGetAPI2( "rtclk_gettimezoneinformation__fb_exit", (RTS_VOID_FCTPTR *)&pfrtclk_gettimezoneinformation__fb_exit, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x578320C7), 0x03050528)
	#define CAL_rtclk_gettimezoneinformation__fb_exit  pfrtclk_gettimezoneinformation__fb_exit
	#define CHK_rtclk_gettimezoneinformation__fb_exit  (pfrtclk_gettimezoneinformation__fb_exit != NULL)
	#define EXP_rtclk_gettimezoneinformation__fb_exit   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_gettimezoneinformation__fb_exit", (RTS_UINTPTR)rtclk_gettimezoneinformation__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0x578320C7), 0x03050528) 
#endif


/**
 * <description>rtclk_setdateandtime__main</description>
 */
typedef struct tagrtclk_setdateandtime_struct
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
	RTCLK_SETDATEANDTIME_PARAMS *pSetDateAndTimeParams;	/* Local variable */	
	ASM_STATE StateJob;					/* Local variable */	
	RTS_IEC_XWORD dwEtrigClass;			/* Local variable */	
} rtclk_setdateandtime_struct;

/**
 * <description>rtclk_setdateandtime_main</description>
 */
typedef struct tagrtclk_setdateandtime_main_struct
{
	rtclk_setdateandtime_struct *pInstance;	/* VAR_INPUT */	
} rtclk_setdateandtime_main_struct;

void CDECL CDECL_EXT rtclk_setdateandtime__main(rtclk_setdateandtime_main_struct *p);
typedef void (CDECL CDECL_EXT* PFRTCLK_SETDATEANDTIME__MAIN_IEC) (rtclk_setdateandtime_main_struct *p);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_SETDATEANDTIME__MAIN_NOTIMPLEMENTED)
	#define USE_rtclk_setdateandtime__main
	#define EXT_rtclk_setdateandtime__main
	#define GET_rtclk_setdateandtime__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_rtclk_setdateandtime__main(p0) 
	#define CHK_rtclk_setdateandtime__main  FALSE
	#define EXP_rtclk_setdateandtime__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_rtclk_setdateandtime__main
	#define EXT_rtclk_setdateandtime__main
	#define GET_rtclk_setdateandtime__main(fl)  CAL_CMGETAPI( "rtclk_setdateandtime__main" ) 
	#define CAL_rtclk_setdateandtime__main  rtclk_setdateandtime__main
	#define CHK_rtclk_setdateandtime__main  TRUE
	#define EXP_rtclk_setdateandtime__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_setdateandtime__main", (RTS_UINTPTR)rtclk_setdateandtime__main, 1, RTSITF_GET_SIGNATURE(0, 0x11AD8AA3), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_rtclk_setdateandtime__main
	#define EXT_rtclk_setdateandtime__main
	#define GET_rtclk_setdateandtime__main(fl)  CAL_CMGETAPI( "rtclk_setdateandtime__main" ) 
	#define CAL_rtclk_setdateandtime__main  rtclk_setdateandtime__main
	#define CHK_rtclk_setdateandtime__main  TRUE
	#define EXP_rtclk_setdateandtime__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_setdateandtime__main", (RTS_UINTPTR)rtclk_setdateandtime__main, 1, RTSITF_GET_SIGNATURE(0, 0x11AD8AA3), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockrtclk_setdateandtime__main
	#define EXT_CmpCAARealTimeClockrtclk_setdateandtime__main
	#define GET_CmpCAARealTimeClockrtclk_setdateandtime__main  ERR_OK
	#define CAL_CmpCAARealTimeClockrtclk_setdateandtime__main  rtclk_setdateandtime__main
	#define CHK_CmpCAARealTimeClockrtclk_setdateandtime__main  TRUE
	#define EXP_CmpCAARealTimeClockrtclk_setdateandtime__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_setdateandtime__main", (RTS_UINTPTR)rtclk_setdateandtime__main, 1, RTSITF_GET_SIGNATURE(0, 0x11AD8AA3), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_rtclk_setdateandtime__main
	#define EXT_rtclk_setdateandtime__main
	#define GET_rtclk_setdateandtime__main(fl)  CAL_CMGETAPI( "rtclk_setdateandtime__main" ) 
	#define CAL_rtclk_setdateandtime__main  rtclk_setdateandtime__main
	#define CHK_rtclk_setdateandtime__main  TRUE
	#define EXP_rtclk_setdateandtime__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_setdateandtime__main", (RTS_UINTPTR)rtclk_setdateandtime__main, 1, RTSITF_GET_SIGNATURE(0, 0x11AD8AA3), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_rtclk_setdateandtime__main  PFRTCLK_SETDATEANDTIME__MAIN_IEC pfrtclk_setdateandtime__main;
	#define EXT_rtclk_setdateandtime__main  extern PFRTCLK_SETDATEANDTIME__MAIN_IEC pfrtclk_setdateandtime__main;
	#define GET_rtclk_setdateandtime__main(fl)  s_pfCMGetAPI2( "rtclk_setdateandtime__main", (RTS_VOID_FCTPTR *)&pfrtclk_setdateandtime__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x11AD8AA3), 0x03050528)
	#define CAL_rtclk_setdateandtime__main  pfrtclk_setdateandtime__main
	#define CHK_rtclk_setdateandtime__main  (pfrtclk_setdateandtime__main != NULL)
	#define EXP_rtclk_setdateandtime__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_setdateandtime__main", (RTS_UINTPTR)rtclk_setdateandtime__main, 1, RTSITF_GET_SIGNATURE(0, 0x11AD8AA3), 0x03050528) 
#endif


/**
 * <description>rtclk_setdateandtime_fb_init</description>
 */
typedef struct tagrtclk_setdateandtime_fb_init_struct
{
	rtclk_setdateandtime_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInitRetains;				/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Init;					/* VAR_OUTPUT */	
} rtclk_setdateandtime_fb_init_struct;

void CDECL CDECL_EXT rtclk_setdateandtime__fb_init(rtclk_setdateandtime_fb_init_struct *p);
typedef void (CDECL CDECL_EXT* PFRTCLK_SETDATEANDTIME__FB_INIT_IEC) (rtclk_setdateandtime_fb_init_struct *p);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_SETDATEANDTIME__FB_INIT_NOTIMPLEMENTED)
	#define USE_rtclk_setdateandtime__fb_init
	#define EXT_rtclk_setdateandtime__fb_init
	#define GET_rtclk_setdateandtime__fb_init(fl)  ERR_NOTIMPLEMENTED
	#define CAL_rtclk_setdateandtime__fb_init(p0) 
	#define CHK_rtclk_setdateandtime__fb_init  FALSE
	#define EXP_rtclk_setdateandtime__fb_init  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_rtclk_setdateandtime__fb_init
	#define EXT_rtclk_setdateandtime__fb_init
	#define GET_rtclk_setdateandtime__fb_init(fl)  CAL_CMGETAPI( "rtclk_setdateandtime__fb_init" ) 
	#define CAL_rtclk_setdateandtime__fb_init  rtclk_setdateandtime__fb_init
	#define CHK_rtclk_setdateandtime__fb_init  TRUE
	#define EXP_rtclk_setdateandtime__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_setdateandtime__fb_init", (RTS_UINTPTR)rtclk_setdateandtime__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0xA2DDB783), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_rtclk_setdateandtime__fb_init
	#define EXT_rtclk_setdateandtime__fb_init
	#define GET_rtclk_setdateandtime__fb_init(fl)  CAL_CMGETAPI( "rtclk_setdateandtime__fb_init" ) 
	#define CAL_rtclk_setdateandtime__fb_init  rtclk_setdateandtime__fb_init
	#define CHK_rtclk_setdateandtime__fb_init  TRUE
	#define EXP_rtclk_setdateandtime__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_setdateandtime__fb_init", (RTS_UINTPTR)rtclk_setdateandtime__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0xA2DDB783), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockrtclk_setdateandtime__fb_init
	#define EXT_CmpCAARealTimeClockrtclk_setdateandtime__fb_init
	#define GET_CmpCAARealTimeClockrtclk_setdateandtime__fb_init  ERR_OK
	#define CAL_CmpCAARealTimeClockrtclk_setdateandtime__fb_init  rtclk_setdateandtime__fb_init
	#define CHK_CmpCAARealTimeClockrtclk_setdateandtime__fb_init  TRUE
	#define EXP_CmpCAARealTimeClockrtclk_setdateandtime__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_setdateandtime__fb_init", (RTS_UINTPTR)rtclk_setdateandtime__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0xA2DDB783), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_rtclk_setdateandtime__fb_init
	#define EXT_rtclk_setdateandtime__fb_init
	#define GET_rtclk_setdateandtime__fb_init(fl)  CAL_CMGETAPI( "rtclk_setdateandtime__fb_init" ) 
	#define CAL_rtclk_setdateandtime__fb_init  rtclk_setdateandtime__fb_init
	#define CHK_rtclk_setdateandtime__fb_init  TRUE
	#define EXP_rtclk_setdateandtime__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_setdateandtime__fb_init", (RTS_UINTPTR)rtclk_setdateandtime__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0xA2DDB783), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_rtclk_setdateandtime__fb_init  PFRTCLK_SETDATEANDTIME__FB_INIT_IEC pfrtclk_setdateandtime__fb_init;
	#define EXT_rtclk_setdateandtime__fb_init  extern PFRTCLK_SETDATEANDTIME__FB_INIT_IEC pfrtclk_setdateandtime__fb_init;
	#define GET_rtclk_setdateandtime__fb_init(fl)  s_pfCMGetAPI2( "rtclk_setdateandtime__fb_init", (RTS_VOID_FCTPTR *)&pfrtclk_setdateandtime__fb_init, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xA2DDB783), 0x03050528)
	#define CAL_rtclk_setdateandtime__fb_init  pfrtclk_setdateandtime__fb_init
	#define CHK_rtclk_setdateandtime__fb_init  (pfrtclk_setdateandtime__fb_init != NULL)
	#define EXP_rtclk_setdateandtime__fb_init   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_setdateandtime__fb_init", (RTS_UINTPTR)rtclk_setdateandtime__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0xA2DDB783), 0x03050528) 
#endif


/**
 * <description>rtclk_setdateandtime_fb_exit</description>
 */
typedef struct tagrtclk_setdateandtime_fb_exit_struct
{
	rtclk_setdateandtime_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Exit;					/* VAR_OUTPUT */	
} rtclk_setdateandtime_fb_exit_struct;

void CDECL CDECL_EXT rtclk_setdateandtime__fb_exit(rtclk_setdateandtime_fb_exit_struct *p);
typedef void (CDECL CDECL_EXT* PFRTCLK_SETDATEANDTIME__FB_EXIT_IEC) (rtclk_setdateandtime_fb_exit_struct *p);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_SETDATEANDTIME__FB_EXIT_NOTIMPLEMENTED)
	#define USE_rtclk_setdateandtime__fb_exit
	#define EXT_rtclk_setdateandtime__fb_exit
	#define GET_rtclk_setdateandtime__fb_exit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_rtclk_setdateandtime__fb_exit(p0) 
	#define CHK_rtclk_setdateandtime__fb_exit  FALSE
	#define EXP_rtclk_setdateandtime__fb_exit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_rtclk_setdateandtime__fb_exit
	#define EXT_rtclk_setdateandtime__fb_exit
	#define GET_rtclk_setdateandtime__fb_exit(fl)  CAL_CMGETAPI( "rtclk_setdateandtime__fb_exit" ) 
	#define CAL_rtclk_setdateandtime__fb_exit  rtclk_setdateandtime__fb_exit
	#define CHK_rtclk_setdateandtime__fb_exit  TRUE
	#define EXP_rtclk_setdateandtime__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_setdateandtime__fb_exit", (RTS_UINTPTR)rtclk_setdateandtime__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xFABF672F), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_rtclk_setdateandtime__fb_exit
	#define EXT_rtclk_setdateandtime__fb_exit
	#define GET_rtclk_setdateandtime__fb_exit(fl)  CAL_CMGETAPI( "rtclk_setdateandtime__fb_exit" ) 
	#define CAL_rtclk_setdateandtime__fb_exit  rtclk_setdateandtime__fb_exit
	#define CHK_rtclk_setdateandtime__fb_exit  TRUE
	#define EXP_rtclk_setdateandtime__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_setdateandtime__fb_exit", (RTS_UINTPTR)rtclk_setdateandtime__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xFABF672F), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockrtclk_setdateandtime__fb_exit
	#define EXT_CmpCAARealTimeClockrtclk_setdateandtime__fb_exit
	#define GET_CmpCAARealTimeClockrtclk_setdateandtime__fb_exit  ERR_OK
	#define CAL_CmpCAARealTimeClockrtclk_setdateandtime__fb_exit  rtclk_setdateandtime__fb_exit
	#define CHK_CmpCAARealTimeClockrtclk_setdateandtime__fb_exit  TRUE
	#define EXP_CmpCAARealTimeClockrtclk_setdateandtime__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_setdateandtime__fb_exit", (RTS_UINTPTR)rtclk_setdateandtime__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xFABF672F), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_rtclk_setdateandtime__fb_exit
	#define EXT_rtclk_setdateandtime__fb_exit
	#define GET_rtclk_setdateandtime__fb_exit(fl)  CAL_CMGETAPI( "rtclk_setdateandtime__fb_exit" ) 
	#define CAL_rtclk_setdateandtime__fb_exit  rtclk_setdateandtime__fb_exit
	#define CHK_rtclk_setdateandtime__fb_exit  TRUE
	#define EXP_rtclk_setdateandtime__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_setdateandtime__fb_exit", (RTS_UINTPTR)rtclk_setdateandtime__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xFABF672F), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_rtclk_setdateandtime__fb_exit  PFRTCLK_SETDATEANDTIME__FB_EXIT_IEC pfrtclk_setdateandtime__fb_exit;
	#define EXT_rtclk_setdateandtime__fb_exit  extern PFRTCLK_SETDATEANDTIME__FB_EXIT_IEC pfrtclk_setdateandtime__fb_exit;
	#define GET_rtclk_setdateandtime__fb_exit(fl)  s_pfCMGetAPI2( "rtclk_setdateandtime__fb_exit", (RTS_VOID_FCTPTR *)&pfrtclk_setdateandtime__fb_exit, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xFABF672F), 0x03050528)
	#define CAL_rtclk_setdateandtime__fb_exit  pfrtclk_setdateandtime__fb_exit
	#define CHK_rtclk_setdateandtime__fb_exit  (pfrtclk_setdateandtime__fb_exit != NULL)
	#define EXP_rtclk_setdateandtime__fb_exit   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_setdateandtime__fb_exit", (RTS_UINTPTR)rtclk_setdateandtime__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0xFABF672F), 0x03050528) 
#endif


/**
 * <description>rtclk_settimezoneinformation__main</description>
 */
typedef struct tagrtclk_settimezoneinformation_struct
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
	RTCLK_SETTIMEZONEINFORMATION_PARAMS *pSetTimeZoneInformationParams;	/* Local variable */	
	ASM_STATE StateJob;					/* Local variable */	
	RTS_IEC_XWORD dwEtrigClass;			/* Local variable */	
} rtclk_settimezoneinformation_struct;

/**
 * <description>rtclk_settimezoneinformation_main</description>
 */
typedef struct tagrtclk_settimezoneinformation_main_struct
{
	rtclk_settimezoneinformation_struct *pInstance;	/* VAR_INPUT */	
} rtclk_settimezoneinformation_main_struct;

void CDECL CDECL_EXT rtclk_settimezoneinformation__main(rtclk_settimezoneinformation_main_struct *p);
typedef void (CDECL CDECL_EXT* PFRTCLK_SETTIMEZONEINFORMATION__MAIN_IEC) (rtclk_settimezoneinformation_main_struct *p);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_SETTIMEZONEINFORMATION__MAIN_NOTIMPLEMENTED)
	#define USE_rtclk_settimezoneinformation__main
	#define EXT_rtclk_settimezoneinformation__main
	#define GET_rtclk_settimezoneinformation__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_rtclk_settimezoneinformation__main(p0) 
	#define CHK_rtclk_settimezoneinformation__main  FALSE
	#define EXP_rtclk_settimezoneinformation__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_rtclk_settimezoneinformation__main
	#define EXT_rtclk_settimezoneinformation__main
	#define GET_rtclk_settimezoneinformation__main(fl)  CAL_CMGETAPI( "rtclk_settimezoneinformation__main" ) 
	#define CAL_rtclk_settimezoneinformation__main  rtclk_settimezoneinformation__main
	#define CHK_rtclk_settimezoneinformation__main  TRUE
	#define EXP_rtclk_settimezoneinformation__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_settimezoneinformation__main", (RTS_UINTPTR)rtclk_settimezoneinformation__main, 1, RTSITF_GET_SIGNATURE(0, 0xE87F7BC1), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_rtclk_settimezoneinformation__main
	#define EXT_rtclk_settimezoneinformation__main
	#define GET_rtclk_settimezoneinformation__main(fl)  CAL_CMGETAPI( "rtclk_settimezoneinformation__main" ) 
	#define CAL_rtclk_settimezoneinformation__main  rtclk_settimezoneinformation__main
	#define CHK_rtclk_settimezoneinformation__main  TRUE
	#define EXP_rtclk_settimezoneinformation__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_settimezoneinformation__main", (RTS_UINTPTR)rtclk_settimezoneinformation__main, 1, RTSITF_GET_SIGNATURE(0, 0xE87F7BC1), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockrtclk_settimezoneinformation__main
	#define EXT_CmpCAARealTimeClockrtclk_settimezoneinformation__main
	#define GET_CmpCAARealTimeClockrtclk_settimezoneinformation__main  ERR_OK
	#define CAL_CmpCAARealTimeClockrtclk_settimezoneinformation__main  rtclk_settimezoneinformation__main
	#define CHK_CmpCAARealTimeClockrtclk_settimezoneinformation__main  TRUE
	#define EXP_CmpCAARealTimeClockrtclk_settimezoneinformation__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_settimezoneinformation__main", (RTS_UINTPTR)rtclk_settimezoneinformation__main, 1, RTSITF_GET_SIGNATURE(0, 0xE87F7BC1), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_rtclk_settimezoneinformation__main
	#define EXT_rtclk_settimezoneinformation__main
	#define GET_rtclk_settimezoneinformation__main(fl)  CAL_CMGETAPI( "rtclk_settimezoneinformation__main" ) 
	#define CAL_rtclk_settimezoneinformation__main  rtclk_settimezoneinformation__main
	#define CHK_rtclk_settimezoneinformation__main  TRUE
	#define EXP_rtclk_settimezoneinformation__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_settimezoneinformation__main", (RTS_UINTPTR)rtclk_settimezoneinformation__main, 1, RTSITF_GET_SIGNATURE(0, 0xE87F7BC1), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_rtclk_settimezoneinformation__main  PFRTCLK_SETTIMEZONEINFORMATION__MAIN_IEC pfrtclk_settimezoneinformation__main;
	#define EXT_rtclk_settimezoneinformation__main  extern PFRTCLK_SETTIMEZONEINFORMATION__MAIN_IEC pfrtclk_settimezoneinformation__main;
	#define GET_rtclk_settimezoneinformation__main(fl)  s_pfCMGetAPI2( "rtclk_settimezoneinformation__main", (RTS_VOID_FCTPTR *)&pfrtclk_settimezoneinformation__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xE87F7BC1), 0x03050528)
	#define CAL_rtclk_settimezoneinformation__main  pfrtclk_settimezoneinformation__main
	#define CHK_rtclk_settimezoneinformation__main  (pfrtclk_settimezoneinformation__main != NULL)
	#define EXP_rtclk_settimezoneinformation__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_settimezoneinformation__main", (RTS_UINTPTR)rtclk_settimezoneinformation__main, 1, RTSITF_GET_SIGNATURE(0, 0xE87F7BC1), 0x03050528) 
#endif


/**
 * <description>rtclk_settimezoneinformation_fb_init</description>
 */
typedef struct tagrtclk_settimezoneinformation_fb_init_struct
{
	rtclk_settimezoneinformation_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInitRetains;				/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Init;					/* VAR_OUTPUT */	
} rtclk_settimezoneinformation_fb_init_struct;

void CDECL CDECL_EXT rtclk_settimezoneinformation__fb_init(rtclk_settimezoneinformation_fb_init_struct *p);
typedef void (CDECL CDECL_EXT* PFRTCLK_SETTIMEZONEINFORMATION__FB_INIT_IEC) (rtclk_settimezoneinformation_fb_init_struct *p);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_SETTIMEZONEINFORMATION__FB_INIT_NOTIMPLEMENTED)
	#define USE_rtclk_settimezoneinformation__fb_init
	#define EXT_rtclk_settimezoneinformation__fb_init
	#define GET_rtclk_settimezoneinformation__fb_init(fl)  ERR_NOTIMPLEMENTED
	#define CAL_rtclk_settimezoneinformation__fb_init(p0) 
	#define CHK_rtclk_settimezoneinformation__fb_init  FALSE
	#define EXP_rtclk_settimezoneinformation__fb_init  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_rtclk_settimezoneinformation__fb_init
	#define EXT_rtclk_settimezoneinformation__fb_init
	#define GET_rtclk_settimezoneinformation__fb_init(fl)  CAL_CMGETAPI( "rtclk_settimezoneinformation__fb_init" ) 
	#define CAL_rtclk_settimezoneinformation__fb_init  rtclk_settimezoneinformation__fb_init
	#define CHK_rtclk_settimezoneinformation__fb_init  TRUE
	#define EXP_rtclk_settimezoneinformation__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_settimezoneinformation__fb_init", (RTS_UINTPTR)rtclk_settimezoneinformation__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0xDDDC4554), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_rtclk_settimezoneinformation__fb_init
	#define EXT_rtclk_settimezoneinformation__fb_init
	#define GET_rtclk_settimezoneinformation__fb_init(fl)  CAL_CMGETAPI( "rtclk_settimezoneinformation__fb_init" ) 
	#define CAL_rtclk_settimezoneinformation__fb_init  rtclk_settimezoneinformation__fb_init
	#define CHK_rtclk_settimezoneinformation__fb_init  TRUE
	#define EXP_rtclk_settimezoneinformation__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_settimezoneinformation__fb_init", (RTS_UINTPTR)rtclk_settimezoneinformation__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0xDDDC4554), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockrtclk_settimezoneinformation__fb_init
	#define EXT_CmpCAARealTimeClockrtclk_settimezoneinformation__fb_init
	#define GET_CmpCAARealTimeClockrtclk_settimezoneinformation__fb_init  ERR_OK
	#define CAL_CmpCAARealTimeClockrtclk_settimezoneinformation__fb_init  rtclk_settimezoneinformation__fb_init
	#define CHK_CmpCAARealTimeClockrtclk_settimezoneinformation__fb_init  TRUE
	#define EXP_CmpCAARealTimeClockrtclk_settimezoneinformation__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_settimezoneinformation__fb_init", (RTS_UINTPTR)rtclk_settimezoneinformation__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0xDDDC4554), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_rtclk_settimezoneinformation__fb_init
	#define EXT_rtclk_settimezoneinformation__fb_init
	#define GET_rtclk_settimezoneinformation__fb_init(fl)  CAL_CMGETAPI( "rtclk_settimezoneinformation__fb_init" ) 
	#define CAL_rtclk_settimezoneinformation__fb_init  rtclk_settimezoneinformation__fb_init
	#define CHK_rtclk_settimezoneinformation__fb_init  TRUE
	#define EXP_rtclk_settimezoneinformation__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_settimezoneinformation__fb_init", (RTS_UINTPTR)rtclk_settimezoneinformation__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0xDDDC4554), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_rtclk_settimezoneinformation__fb_init  PFRTCLK_SETTIMEZONEINFORMATION__FB_INIT_IEC pfrtclk_settimezoneinformation__fb_init;
	#define EXT_rtclk_settimezoneinformation__fb_init  extern PFRTCLK_SETTIMEZONEINFORMATION__FB_INIT_IEC pfrtclk_settimezoneinformation__fb_init;
	#define GET_rtclk_settimezoneinformation__fb_init(fl)  s_pfCMGetAPI2( "rtclk_settimezoneinformation__fb_init", (RTS_VOID_FCTPTR *)&pfrtclk_settimezoneinformation__fb_init, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xDDDC4554), 0x03050528)
	#define CAL_rtclk_settimezoneinformation__fb_init  pfrtclk_settimezoneinformation__fb_init
	#define CHK_rtclk_settimezoneinformation__fb_init  (pfrtclk_settimezoneinformation__fb_init != NULL)
	#define EXP_rtclk_settimezoneinformation__fb_init   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_settimezoneinformation__fb_init", (RTS_UINTPTR)rtclk_settimezoneinformation__fb_init, 1, RTSITF_GET_SIGNATURE(0, 0xDDDC4554), 0x03050528) 
#endif


/**
 * <description>rtclk_settimezoneinformation_fb_exit</description>
 */
typedef struct tagrtclk_settimezoneinformation_fb_exit_struct
{
	rtclk_settimezoneinformation_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Exit;					/* VAR_OUTPUT */	
} rtclk_settimezoneinformation_fb_exit_struct;

void CDECL CDECL_EXT rtclk_settimezoneinformation__fb_exit(rtclk_settimezoneinformation_fb_exit_struct *p);
typedef void (CDECL CDECL_EXT* PFRTCLK_SETTIMEZONEINFORMATION__FB_EXIT_IEC) (rtclk_settimezoneinformation_fb_exit_struct *p);
#if defined(CMPCAAREALTIMECLOCK_NOTIMPLEMENTED) || defined(RTCLK_SETTIMEZONEINFORMATION__FB_EXIT_NOTIMPLEMENTED)
	#define USE_rtclk_settimezoneinformation__fb_exit
	#define EXT_rtclk_settimezoneinformation__fb_exit
	#define GET_rtclk_settimezoneinformation__fb_exit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_rtclk_settimezoneinformation__fb_exit(p0) 
	#define CHK_rtclk_settimezoneinformation__fb_exit  FALSE
	#define EXP_rtclk_settimezoneinformation__fb_exit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_rtclk_settimezoneinformation__fb_exit
	#define EXT_rtclk_settimezoneinformation__fb_exit
	#define GET_rtclk_settimezoneinformation__fb_exit(fl)  CAL_CMGETAPI( "rtclk_settimezoneinformation__fb_exit" ) 
	#define CAL_rtclk_settimezoneinformation__fb_exit  rtclk_settimezoneinformation__fb_exit
	#define CHK_rtclk_settimezoneinformation__fb_exit  TRUE
	#define EXP_rtclk_settimezoneinformation__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_settimezoneinformation__fb_exit", (RTS_UINTPTR)rtclk_settimezoneinformation__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0x2B8D8BD0), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAAREALTIMECLOCK_EXTERNAL)
	#define USE_rtclk_settimezoneinformation__fb_exit
	#define EXT_rtclk_settimezoneinformation__fb_exit
	#define GET_rtclk_settimezoneinformation__fb_exit(fl)  CAL_CMGETAPI( "rtclk_settimezoneinformation__fb_exit" ) 
	#define CAL_rtclk_settimezoneinformation__fb_exit  rtclk_settimezoneinformation__fb_exit
	#define CHK_rtclk_settimezoneinformation__fb_exit  TRUE
	#define EXP_rtclk_settimezoneinformation__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_settimezoneinformation__fb_exit", (RTS_UINTPTR)rtclk_settimezoneinformation__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0x2B8D8BD0), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAARealTimeClockrtclk_settimezoneinformation__fb_exit
	#define EXT_CmpCAARealTimeClockrtclk_settimezoneinformation__fb_exit
	#define GET_CmpCAARealTimeClockrtclk_settimezoneinformation__fb_exit  ERR_OK
	#define CAL_CmpCAARealTimeClockrtclk_settimezoneinformation__fb_exit  rtclk_settimezoneinformation__fb_exit
	#define CHK_CmpCAARealTimeClockrtclk_settimezoneinformation__fb_exit  TRUE
	#define EXP_CmpCAARealTimeClockrtclk_settimezoneinformation__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_settimezoneinformation__fb_exit", (RTS_UINTPTR)rtclk_settimezoneinformation__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0x2B8D8BD0), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_rtclk_settimezoneinformation__fb_exit
	#define EXT_rtclk_settimezoneinformation__fb_exit
	#define GET_rtclk_settimezoneinformation__fb_exit(fl)  CAL_CMGETAPI( "rtclk_settimezoneinformation__fb_exit" ) 
	#define CAL_rtclk_settimezoneinformation__fb_exit  rtclk_settimezoneinformation__fb_exit
	#define CHK_rtclk_settimezoneinformation__fb_exit  TRUE
	#define EXP_rtclk_settimezoneinformation__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_settimezoneinformation__fb_exit", (RTS_UINTPTR)rtclk_settimezoneinformation__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0x2B8D8BD0), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_rtclk_settimezoneinformation__fb_exit  PFRTCLK_SETTIMEZONEINFORMATION__FB_EXIT_IEC pfrtclk_settimezoneinformation__fb_exit;
	#define EXT_rtclk_settimezoneinformation__fb_exit  extern PFRTCLK_SETTIMEZONEINFORMATION__FB_EXIT_IEC pfrtclk_settimezoneinformation__fb_exit;
	#define GET_rtclk_settimezoneinformation__fb_exit(fl)  s_pfCMGetAPI2( "rtclk_settimezoneinformation__fb_exit", (RTS_VOID_FCTPTR *)&pfrtclk_settimezoneinformation__fb_exit, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x2B8D8BD0), 0x03050528)
	#define CAL_rtclk_settimezoneinformation__fb_exit  pfrtclk_settimezoneinformation__fb_exit
	#define CHK_rtclk_settimezoneinformation__fb_exit  (pfrtclk_settimezoneinformation__fb_exit != NULL)
	#define EXP_rtclk_settimezoneinformation__fb_exit   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"rtclk_settimezoneinformation__fb_exit", (RTS_UINTPTR)rtclk_settimezoneinformation__fb_exit, 1, RTSITF_GET_SIGNATURE(0, 0x2B8D8BD0), 0x03050528) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
	PFRTCLK_WORKERINIT IRTCLK_WorkerInit;
 	PFRTCLK_WORKEREXIT IRTCLK_WorkerExit;
 	PFRTCLK_GETDATEANDTIME IRTCLK_GetDateAndTime;
 	PFRTCLK_GETDATEANDTIME_FB_INIT IRTCLK_GetDateAndTime_FB_Init;
 	PFRTCLK_GETDATEANDTIME_FB_EXIT IRTCLK_GetDateAndTime_FB_Exit;
 	PFRTCLK_SETDATEANDTIME IRTCLK_SetDateAndTime;
 	PFRTCLK_SETDATEANDTIME_FB_INIT IRTCLK_SetDateAndTime_FB_Init;
 	PFRTCLK_SETDATEANDTIME_FB_EXIT IRTCLK_SetDateAndTime_FB_Exit;
 	PFRTCLK_GETTIMEZONEINFORMATION IRTCLK_GetTimeZoneInformation;
 	PFRTCLK_GETTIMEZONEINFORMATION_FB_INIT IRTCLK_GetTimeZoneInformation_FB_Init;
 	PFRTCLK_GETTIMEZONEINFORMATION_FB_EXIT IRTCLK_GetTimeZoneInformation_FB_Exit;
 	PFRTCLK_SETTIMEZONEINFORMATION IRTCLK_SetTimeZoneInformation;
 	PFRTCLK_SETTIMEZONEINFORMATION_FB_INIT IRTCLK_SetTimeZoneInformation_FB_Init;
 	PFRTCLK_SETTIMEZONEINFORMATION_FB_EXIT IRTCLK_SetTimeZoneInformation_FB_Exit;
 	PFRTCLK_GETSUPPLIERVERSION IRTCLK_GetSupplierVersion;
 	PFRTCLK_GETPROPERTY IRTCLK_GetProperty;
 } ICmpCAARealTimeClock_C;

#ifdef CPLUSPLUS
class ICmpCAARealTimeClock : public IBase
{
	public:
		virtual CAA_ERROR CDECL IRTCLK_WorkerInit(void) =0;
		virtual CAA_ERROR CDECL IRTCLK_WorkerExit(void) =0;
		virtual void CDECL IRTCLK_GetDateAndTime(rtclk_getdateandtime_typ* inst) =0;
		virtual CAA_BOOL CDECL IRTCLK_GetDateAndTime_FB_Init(CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, rtclk_getdateandtime_typ* inst) =0;
		virtual CAA_BOOL CDECL IRTCLK_GetDateAndTime_FB_Exit(CAA_BOOL bInCopyCode, rtclk_getdateandtime_typ* inst) =0;
		virtual void CDECL IRTCLK_SetDateAndTime(rtclk_setdateandtime_typ* inst) =0;
		virtual CAA_BOOL CDECL IRTCLK_SetDateAndTime_FB_Init(CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, rtclk_setdateandtime_typ* inst) =0;
		virtual CAA_BOOL CDECL IRTCLK_SetDateAndTime_FB_Exit(CAA_BOOL bInCopyCode, rtclk_setdateandtime_typ* inst) =0;
		virtual void CDECL IRTCLK_GetTimeZoneInformation(rtclk_gettimezoneinformation_typ* inst) =0;
		virtual CAA_BOOL CDECL IRTCLK_GetTimeZoneInformation_FB_Init(CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, rtclk_gettimezoneinformation_typ* inst) =0;
		virtual CAA_BOOL CDECL IRTCLK_GetTimeZoneInformation_FB_Exit(CAA_BOOL bInCopyCode, rtclk_gettimezoneinformation_typ* inst) =0;
		virtual void CDECL IRTCLK_SetTimeZoneInformation(rtclk_settimezoneinformation_typ* inst) =0;
		virtual CAA_BOOL CDECL IRTCLK_SetTimeZoneInformation_FB_Init(CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, rtclk_settimezoneinformation_typ* inst) =0;
		virtual CAA_BOOL CDECL IRTCLK_SetTimeZoneInformation_FB_Exit(CAA_BOOL bInCopyCode, rtclk_settimezoneinformation_typ* inst) =0;
		virtual unsigned short CDECL IRTCLK_GetSupplierVersion(CAA_BOOL xDummy) =0;
		virtual RTS_IEC_XWORD CDECL IRTCLK_GetProperty(unsigned short usProperty) =0;
};
	#ifndef ITF_CmpCAARealTimeClock
		#define ITF_CmpCAARealTimeClock static ICmpCAARealTimeClock *pICmpCAARealTimeClock = NULL;
	#endif
	#define EXTITF_CmpCAARealTimeClock
#else	/*CPLUSPLUS*/
	typedef ICmpCAARealTimeClock_C		ICmpCAARealTimeClock;
	#ifndef ITF_CmpCAARealTimeClock
		#define ITF_CmpCAARealTimeClock
	#endif
	#define EXTITF_CmpCAARealTimeClock
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCAAREALTIMECLOCKITF_H_*/
