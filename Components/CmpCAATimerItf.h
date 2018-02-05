 /**
 * <interfacename>CmpCAATimer</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _CMPCAATIMERITF_H_
#define _CMPCAATIMERITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAATimer.h"

#ifdef __cplusplus
extern "C" {
#endif

CAA_HANDLE CDECL TMR_CreateH(CAA_BOOL xCyclic, CAA_COUNT ctInterval, RTS_IEC_XWORD dwParam, CAA_BOOL xHardware, CAA_ENUM eTimer, CAA_ERROR *peError);
typedef CAA_HANDLE (CDECL * PFTMR_CREATEH) (CAA_BOOL xCyclic, CAA_COUNT ctInterval, RTS_IEC_XWORD dwParam, CAA_BOOL xHardware, CAA_ENUM eTimer, CAA_ERROR *peError);
#if defined(CMPCAATIMER_NOTIMPLEMENTED) || defined(TMR_CREATEH_NOTIMPLEMENTED)
	#define USE_TMR_CreateH
	#define EXT_TMR_CreateH
	#define GET_TMR_CreateH(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TMR_CreateH(p0,p1,p2,p3,p4,p5)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_TMR_CreateH  FALSE
	#define EXP_TMR_CreateH  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TMR_CreateH
	#define EXT_TMR_CreateH
	#define GET_TMR_CreateH(fl)  CAL_CMGETAPI( "TMR_CreateH" ) 
	#define CAL_TMR_CreateH  TMR_CreateH
	#define CHK_TMR_CreateH  TRUE
	#define EXP_TMR_CreateH  CAL_CMEXPAPI( "TMR_CreateH" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAATIMER_EXTERNAL)
	#define USE_TMR_CreateH
	#define EXT_TMR_CreateH
	#define GET_TMR_CreateH(fl)  CAL_CMGETAPI( "TMR_CreateH" ) 
	#define CAL_TMR_CreateH  TMR_CreateH
	#define CHK_TMR_CreateH  TRUE
	#define EXP_TMR_CreateH  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TMR_CreateH", (RTS_UINTPTR)TMR_CreateH, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATimerTMR_CreateH
	#define EXT_CmpCAATimerTMR_CreateH
	#define GET_CmpCAATimerTMR_CreateH  ERR_OK
	#define CAL_CmpCAATimerTMR_CreateH pICmpCAATimer->ITMR_CreateH
	#define CHK_CmpCAATimerTMR_CreateH (pICmpCAATimer != NULL)
	#define EXP_CmpCAATimerTMR_CreateH  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TMR_CreateH
	#define EXT_TMR_CreateH
	#define GET_TMR_CreateH(fl)  CAL_CMGETAPI( "TMR_CreateH" ) 
	#define CAL_TMR_CreateH pICmpCAATimer->ITMR_CreateH
	#define CHK_TMR_CreateH (pICmpCAATimer != NULL)
	#define EXP_TMR_CreateH  CAL_CMEXPAPI( "TMR_CreateH" ) 
#else /* DYNAMIC_LINK */
	#define USE_TMR_CreateH  PFTMR_CREATEH pfTMR_CreateH;
	#define EXT_TMR_CreateH  extern PFTMR_CREATEH pfTMR_CreateH;
	#define GET_TMR_CreateH(fl)  s_pfCMGetAPI2( "TMR_CreateH", (RTS_VOID_FCTPTR *)&pfTMR_CreateH, (fl), 0, 0)
	#define CAL_TMR_CreateH  pfTMR_CreateH
	#define CHK_TMR_CreateH  (pfTMR_CreateH != NULL)
	#define EXP_TMR_CreateH  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TMR_CreateH", (RTS_UINTPTR)TMR_CreateH, 0, 0) 
#endif




CAA_HANDLE CDECL TMR_CreateP(CAA_BOOL xCyclic, CAA_COUNT ctInterval, RTS_IEC_XWORD dwParam, CAA_BOOL xHardware, CAA_ENUM eTimer, CAA_SIZE szMemSize, CAA_PVOID pMemory, CAA_ERROR *peError);
typedef CAA_HANDLE (CDECL * PFTMR_CREATEP) (CAA_BOOL xCyclic, CAA_COUNT ctInterval, RTS_IEC_XWORD dwParam, CAA_BOOL xHardware, CAA_ENUM eTimer, CAA_SIZE szMemSize, CAA_PVOID pMemory, CAA_ERROR *peError);
#if defined(CMPCAATIMER_NOTIMPLEMENTED) || defined(TMR_CREATEP_NOTIMPLEMENTED)
	#define USE_TMR_CreateP
	#define EXT_TMR_CreateP
	#define GET_TMR_CreateP(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TMR_CreateP(p0,p1,p2,p3,p4,p5,p6,p7)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_TMR_CreateP  FALSE
	#define EXP_TMR_CreateP  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TMR_CreateP
	#define EXT_TMR_CreateP
	#define GET_TMR_CreateP(fl)  CAL_CMGETAPI( "TMR_CreateP" ) 
	#define CAL_TMR_CreateP  TMR_CreateP
	#define CHK_TMR_CreateP  TRUE
	#define EXP_TMR_CreateP  CAL_CMEXPAPI( "TMR_CreateP" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAATIMER_EXTERNAL)
	#define USE_TMR_CreateP
	#define EXT_TMR_CreateP
	#define GET_TMR_CreateP(fl)  CAL_CMGETAPI( "TMR_CreateP" ) 
	#define CAL_TMR_CreateP  TMR_CreateP
	#define CHK_TMR_CreateP  TRUE
	#define EXP_TMR_CreateP  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TMR_CreateP", (RTS_UINTPTR)TMR_CreateP, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATimerTMR_CreateP
	#define EXT_CmpCAATimerTMR_CreateP
	#define GET_CmpCAATimerTMR_CreateP  ERR_OK
	#define CAL_CmpCAATimerTMR_CreateP pICmpCAATimer->ITMR_CreateP
	#define CHK_CmpCAATimerTMR_CreateP (pICmpCAATimer != NULL)
	#define EXP_CmpCAATimerTMR_CreateP  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TMR_CreateP
	#define EXT_TMR_CreateP
	#define GET_TMR_CreateP(fl)  CAL_CMGETAPI( "TMR_CreateP" ) 
	#define CAL_TMR_CreateP pICmpCAATimer->ITMR_CreateP
	#define CHK_TMR_CreateP (pICmpCAATimer != NULL)
	#define EXP_TMR_CreateP  CAL_CMEXPAPI( "TMR_CreateP" ) 
#else /* DYNAMIC_LINK */
	#define USE_TMR_CreateP  PFTMR_CREATEP pfTMR_CreateP;
	#define EXT_TMR_CreateP  extern PFTMR_CREATEP pfTMR_CreateP;
	#define GET_TMR_CreateP(fl)  s_pfCMGetAPI2( "TMR_CreateP", (RTS_VOID_FCTPTR *)&pfTMR_CreateP, (fl), 0, 0)
	#define CAL_TMR_CreateP  pfTMR_CreateP
	#define CHK_TMR_CreateP  (pfTMR_CreateP != NULL)
	#define EXP_TMR_CreateP  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TMR_CreateP", (RTS_UINTPTR)TMR_CreateP, 0, 0) 
#endif




CAA_SIZE CDECL TMR_GetSize(CAA_BOOL xCyclic, CAA_COUNT ctInterval,	RTS_IEC_XWORD dwParam, CAA_BOOL xHardware);
typedef CAA_SIZE (CDECL * PFTMR_GETSIZE) (CAA_BOOL xCyclic, CAA_COUNT ctInterval,	RTS_IEC_XWORD dwParam, CAA_BOOL xHardware);
#if defined(CMPCAATIMER_NOTIMPLEMENTED) || defined(TMR_GETSIZE_NOTIMPLEMENTED)
	#define USE_TMR_GetSize
	#define EXT_TMR_GetSize
	#define GET_TMR_GetSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TMR_GetSize(p0,p1,p2,p3)  (CAA_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_TMR_GetSize  FALSE
	#define EXP_TMR_GetSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TMR_GetSize
	#define EXT_TMR_GetSize
	#define GET_TMR_GetSize(fl)  CAL_CMGETAPI( "TMR_GetSize" ) 
	#define CAL_TMR_GetSize  TMR_GetSize
	#define CHK_TMR_GetSize  TRUE
	#define EXP_TMR_GetSize  CAL_CMEXPAPI( "TMR_GetSize" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAATIMER_EXTERNAL)
	#define USE_TMR_GetSize
	#define EXT_TMR_GetSize
	#define GET_TMR_GetSize(fl)  CAL_CMGETAPI( "TMR_GetSize" ) 
	#define CAL_TMR_GetSize  TMR_GetSize
	#define CHK_TMR_GetSize  TRUE
	#define EXP_TMR_GetSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TMR_GetSize", (RTS_UINTPTR)TMR_GetSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATimerTMR_GetSize
	#define EXT_CmpCAATimerTMR_GetSize
	#define GET_CmpCAATimerTMR_GetSize  ERR_OK
	#define CAL_CmpCAATimerTMR_GetSize pICmpCAATimer->ITMR_GetSize
	#define CHK_CmpCAATimerTMR_GetSize (pICmpCAATimer != NULL)
	#define EXP_CmpCAATimerTMR_GetSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TMR_GetSize
	#define EXT_TMR_GetSize
	#define GET_TMR_GetSize(fl)  CAL_CMGETAPI( "TMR_GetSize" ) 
	#define CAL_TMR_GetSize pICmpCAATimer->ITMR_GetSize
	#define CHK_TMR_GetSize (pICmpCAATimer != NULL)
	#define EXP_TMR_GetSize  CAL_CMEXPAPI( "TMR_GetSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_TMR_GetSize  PFTMR_GETSIZE pfTMR_GetSize;
	#define EXT_TMR_GetSize  extern PFTMR_GETSIZE pfTMR_GetSize;
	#define GET_TMR_GetSize(fl)  s_pfCMGetAPI2( "TMR_GetSize", (RTS_VOID_FCTPTR *)&pfTMR_GetSize, (fl), 0, 0)
	#define CAL_TMR_GetSize  pfTMR_GetSize
	#define CHK_TMR_GetSize  (pfTMR_GetSize != NULL)
	#define EXP_TMR_GetSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TMR_GetSize", (RTS_UINTPTR)TMR_GetSize, 0, 0) 
#endif




CAA_ERROR CDECL TMR_Start(CAA_HANDLE hTimer);
typedef CAA_ERROR (CDECL * PFTMR_START) (CAA_HANDLE hTimer);
#if defined(CMPCAATIMER_NOTIMPLEMENTED) || defined(TMR_START_NOTIMPLEMENTED)
	#define USE_TMR_Start
	#define EXT_TMR_Start
	#define GET_TMR_Start(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TMR_Start(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_TMR_Start  FALSE
	#define EXP_TMR_Start  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TMR_Start
	#define EXT_TMR_Start
	#define GET_TMR_Start(fl)  CAL_CMGETAPI( "TMR_Start" ) 
	#define CAL_TMR_Start  TMR_Start
	#define CHK_TMR_Start  TRUE
	#define EXP_TMR_Start  CAL_CMEXPAPI( "TMR_Start" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAATIMER_EXTERNAL)
	#define USE_TMR_Start
	#define EXT_TMR_Start
	#define GET_TMR_Start(fl)  CAL_CMGETAPI( "TMR_Start" ) 
	#define CAL_TMR_Start  TMR_Start
	#define CHK_TMR_Start  TRUE
	#define EXP_TMR_Start  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TMR_Start", (RTS_UINTPTR)TMR_Start, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATimerTMR_Start
	#define EXT_CmpCAATimerTMR_Start
	#define GET_CmpCAATimerTMR_Start  ERR_OK
	#define CAL_CmpCAATimerTMR_Start pICmpCAATimer->ITMR_Start
	#define CHK_CmpCAATimerTMR_Start (pICmpCAATimer != NULL)
	#define EXP_CmpCAATimerTMR_Start  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TMR_Start
	#define EXT_TMR_Start
	#define GET_TMR_Start(fl)  CAL_CMGETAPI( "TMR_Start" ) 
	#define CAL_TMR_Start pICmpCAATimer->ITMR_Start
	#define CHK_TMR_Start (pICmpCAATimer != NULL)
	#define EXP_TMR_Start  CAL_CMEXPAPI( "TMR_Start" ) 
#else /* DYNAMIC_LINK */
	#define USE_TMR_Start  PFTMR_START pfTMR_Start;
	#define EXT_TMR_Start  extern PFTMR_START pfTMR_Start;
	#define GET_TMR_Start(fl)  s_pfCMGetAPI2( "TMR_Start", (RTS_VOID_FCTPTR *)&pfTMR_Start, (fl), 0, 0)
	#define CAL_TMR_Start  pfTMR_Start
	#define CHK_TMR_Start  (pfTMR_Start != NULL)
	#define EXP_TMR_Start  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TMR_Start", (RTS_UINTPTR)TMR_Start, 0, 0) 
#endif




CAA_ERROR CDECL TMR_Stop(CAA_HANDLE hTimer);
typedef CAA_ERROR (CDECL * PFTMR_STOP) (CAA_HANDLE hTimer);
#if defined(CMPCAATIMER_NOTIMPLEMENTED) || defined(TMR_STOP_NOTIMPLEMENTED)
	#define USE_TMR_Stop
	#define EXT_TMR_Stop
	#define GET_TMR_Stop(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TMR_Stop(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_TMR_Stop  FALSE
	#define EXP_TMR_Stop  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TMR_Stop
	#define EXT_TMR_Stop
	#define GET_TMR_Stop(fl)  CAL_CMGETAPI( "TMR_Stop" ) 
	#define CAL_TMR_Stop  TMR_Stop
	#define CHK_TMR_Stop  TRUE
	#define EXP_TMR_Stop  CAL_CMEXPAPI( "TMR_Stop" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAATIMER_EXTERNAL)
	#define USE_TMR_Stop
	#define EXT_TMR_Stop
	#define GET_TMR_Stop(fl)  CAL_CMGETAPI( "TMR_Stop" ) 
	#define CAL_TMR_Stop  TMR_Stop
	#define CHK_TMR_Stop  TRUE
	#define EXP_TMR_Stop  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TMR_Stop", (RTS_UINTPTR)TMR_Stop, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATimerTMR_Stop
	#define EXT_CmpCAATimerTMR_Stop
	#define GET_CmpCAATimerTMR_Stop  ERR_OK
	#define CAL_CmpCAATimerTMR_Stop pICmpCAATimer->ITMR_Stop
	#define CHK_CmpCAATimerTMR_Stop (pICmpCAATimer != NULL)
	#define EXP_CmpCAATimerTMR_Stop  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TMR_Stop
	#define EXT_TMR_Stop
	#define GET_TMR_Stop(fl)  CAL_CMGETAPI( "TMR_Stop" ) 
	#define CAL_TMR_Stop pICmpCAATimer->ITMR_Stop
	#define CHK_TMR_Stop (pICmpCAATimer != NULL)
	#define EXP_TMR_Stop  CAL_CMEXPAPI( "TMR_Stop" ) 
#else /* DYNAMIC_LINK */
	#define USE_TMR_Stop  PFTMR_STOP pfTMR_Stop;
	#define EXT_TMR_Stop  extern PFTMR_STOP pfTMR_Stop;
	#define GET_TMR_Stop(fl)  s_pfCMGetAPI2( "TMR_Stop", (RTS_VOID_FCTPTR *)&pfTMR_Stop, (fl), 0, 0)
	#define CAL_TMR_Stop  pfTMR_Stop
	#define CHK_TMR_Stop  (pfTMR_Stop != NULL)
	#define EXP_TMR_Stop  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TMR_Stop", (RTS_UINTPTR)TMR_Stop, 0, 0) 
#endif




CAA_ERROR CDECL TMR_Delete(CAA_HANDLE hTimer);
typedef CAA_ERROR (CDECL * PFTMR_DELETE) (CAA_HANDLE hTimer);
#if defined(CMPCAATIMER_NOTIMPLEMENTED) || defined(TMR_DELETE_NOTIMPLEMENTED)
	#define USE_TMR_Delete
	#define EXT_TMR_Delete
	#define GET_TMR_Delete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TMR_Delete(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_TMR_Delete  FALSE
	#define EXP_TMR_Delete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TMR_Delete
	#define EXT_TMR_Delete
	#define GET_TMR_Delete(fl)  CAL_CMGETAPI( "TMR_Delete" ) 
	#define CAL_TMR_Delete  TMR_Delete
	#define CHK_TMR_Delete  TRUE
	#define EXP_TMR_Delete  CAL_CMEXPAPI( "TMR_Delete" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAATIMER_EXTERNAL)
	#define USE_TMR_Delete
	#define EXT_TMR_Delete
	#define GET_TMR_Delete(fl)  CAL_CMGETAPI( "TMR_Delete" ) 
	#define CAL_TMR_Delete  TMR_Delete
	#define CHK_TMR_Delete  TRUE
	#define EXP_TMR_Delete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TMR_Delete", (RTS_UINTPTR)TMR_Delete, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATimerTMR_Delete
	#define EXT_CmpCAATimerTMR_Delete
	#define GET_CmpCAATimerTMR_Delete  ERR_OK
	#define CAL_CmpCAATimerTMR_Delete pICmpCAATimer->ITMR_Delete
	#define CHK_CmpCAATimerTMR_Delete (pICmpCAATimer != NULL)
	#define EXP_CmpCAATimerTMR_Delete  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TMR_Delete
	#define EXT_TMR_Delete
	#define GET_TMR_Delete(fl)  CAL_CMGETAPI( "TMR_Delete" ) 
	#define CAL_TMR_Delete pICmpCAATimer->ITMR_Delete
	#define CHK_TMR_Delete (pICmpCAATimer != NULL)
	#define EXP_TMR_Delete  CAL_CMEXPAPI( "TMR_Delete" ) 
#else /* DYNAMIC_LINK */
	#define USE_TMR_Delete  PFTMR_DELETE pfTMR_Delete;
	#define EXT_TMR_Delete  extern PFTMR_DELETE pfTMR_Delete;
	#define GET_TMR_Delete(fl)  s_pfCMGetAPI2( "TMR_Delete", (RTS_VOID_FCTPTR *)&pfTMR_Delete, (fl), 0, 0)
	#define CAL_TMR_Delete  pfTMR_Delete
	#define CHK_TMR_Delete  (pfTMR_Delete != NULL)
	#define EXP_TMR_Delete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TMR_Delete", (RTS_UINTPTR)TMR_Delete, 0, 0) 
#endif




CAA_ERROR CDECL TMR_GetQuality(CAA_HANDLE hTimer, TMR_QUALITY *pqTimer);
typedef CAA_ERROR (CDECL * PFTMR_GETQUALITY) (CAA_HANDLE hTimer, TMR_QUALITY *pqTimer);
#if defined(CMPCAATIMER_NOTIMPLEMENTED) || defined(TMR_GETQUALITY_NOTIMPLEMENTED)
	#define USE_TMR_GetQuality
	#define EXT_TMR_GetQuality
	#define GET_TMR_GetQuality(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TMR_GetQuality(p0,p1)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_TMR_GetQuality  FALSE
	#define EXP_TMR_GetQuality  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TMR_GetQuality
	#define EXT_TMR_GetQuality
	#define GET_TMR_GetQuality(fl)  CAL_CMGETAPI( "TMR_GetQuality" ) 
	#define CAL_TMR_GetQuality  TMR_GetQuality
	#define CHK_TMR_GetQuality  TRUE
	#define EXP_TMR_GetQuality  CAL_CMEXPAPI( "TMR_GetQuality" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAATIMER_EXTERNAL)
	#define USE_TMR_GetQuality
	#define EXT_TMR_GetQuality
	#define GET_TMR_GetQuality(fl)  CAL_CMGETAPI( "TMR_GetQuality" ) 
	#define CAL_TMR_GetQuality  TMR_GetQuality
	#define CHK_TMR_GetQuality  TRUE
	#define EXP_TMR_GetQuality  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TMR_GetQuality", (RTS_UINTPTR)TMR_GetQuality, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATimerTMR_GetQuality
	#define EXT_CmpCAATimerTMR_GetQuality
	#define GET_CmpCAATimerTMR_GetQuality  ERR_OK
	#define CAL_CmpCAATimerTMR_GetQuality pICmpCAATimer->ITMR_GetQuality
	#define CHK_CmpCAATimerTMR_GetQuality (pICmpCAATimer != NULL)
	#define EXP_CmpCAATimerTMR_GetQuality  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TMR_GetQuality
	#define EXT_TMR_GetQuality
	#define GET_TMR_GetQuality(fl)  CAL_CMGETAPI( "TMR_GetQuality" ) 
	#define CAL_TMR_GetQuality pICmpCAATimer->ITMR_GetQuality
	#define CHK_TMR_GetQuality (pICmpCAATimer != NULL)
	#define EXP_TMR_GetQuality  CAL_CMEXPAPI( "TMR_GetQuality" ) 
#else /* DYNAMIC_LINK */
	#define USE_TMR_GetQuality  PFTMR_GETQUALITY pfTMR_GetQuality;
	#define EXT_TMR_GetQuality  extern PFTMR_GETQUALITY pfTMR_GetQuality;
	#define GET_TMR_GetQuality(fl)  s_pfCMGetAPI2( "TMR_GetQuality", (RTS_VOID_FCTPTR *)&pfTMR_GetQuality, (fl), 0, 0)
	#define CAL_TMR_GetQuality  pfTMR_GetQuality
	#define CHK_TMR_GetQuality  (pfTMR_GetQuality != NULL)
	#define EXP_TMR_GetQuality  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TMR_GetQuality", (RTS_UINTPTR)TMR_GetQuality, 0, 0) 
#endif




RTS_IEC_XWORD CDECL TMR_GetProperty(CAA_WORD wProperty);
typedef RTS_IEC_XWORD (CDECL * PFTMR_GETPROPERTY) (CAA_WORD wProperty);
#if defined(CMPCAATIMER_NOTIMPLEMENTED) || defined(TMR_GETPROPERTY_NOTIMPLEMENTED)
	#define USE_TMR_GetProperty
	#define EXT_TMR_GetProperty
	#define GET_TMR_GetProperty(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TMR_GetProperty(p0)  (RTS_IEC_XWORD)ERR_NOTIMPLEMENTED
	#define CHK_TMR_GetProperty  FALSE
	#define EXP_TMR_GetProperty  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TMR_GetProperty
	#define EXT_TMR_GetProperty
	#define GET_TMR_GetProperty(fl)  CAL_CMGETAPI( "TMR_GetProperty" ) 
	#define CAL_TMR_GetProperty  TMR_GetProperty
	#define CHK_TMR_GetProperty  TRUE
	#define EXP_TMR_GetProperty  CAL_CMEXPAPI( "TMR_GetProperty" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAATIMER_EXTERNAL)
	#define USE_TMR_GetProperty
	#define EXT_TMR_GetProperty
	#define GET_TMR_GetProperty(fl)  CAL_CMGETAPI( "TMR_GetProperty" ) 
	#define CAL_TMR_GetProperty  TMR_GetProperty
	#define CHK_TMR_GetProperty  TRUE
	#define EXP_TMR_GetProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TMR_GetProperty", (RTS_UINTPTR)TMR_GetProperty, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATimerTMR_GetProperty
	#define EXT_CmpCAATimerTMR_GetProperty
	#define GET_CmpCAATimerTMR_GetProperty  ERR_OK
	#define CAL_CmpCAATimerTMR_GetProperty pICmpCAATimer->ITMR_GetProperty
	#define CHK_CmpCAATimerTMR_GetProperty (pICmpCAATimer != NULL)
	#define EXP_CmpCAATimerTMR_GetProperty  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TMR_GetProperty
	#define EXT_TMR_GetProperty
	#define GET_TMR_GetProperty(fl)  CAL_CMGETAPI( "TMR_GetProperty" ) 
	#define CAL_TMR_GetProperty pICmpCAATimer->ITMR_GetProperty
	#define CHK_TMR_GetProperty (pICmpCAATimer != NULL)
	#define EXP_TMR_GetProperty  CAL_CMEXPAPI( "TMR_GetProperty" ) 
#else /* DYNAMIC_LINK */
	#define USE_TMR_GetProperty  PFTMR_GETPROPERTY pfTMR_GetProperty;
	#define EXT_TMR_GetProperty  extern PFTMR_GETPROPERTY pfTMR_GetProperty;
	#define GET_TMR_GetProperty(fl)  s_pfCMGetAPI2( "TMR_GetProperty", (RTS_VOID_FCTPTR *)&pfTMR_GetProperty, (fl), 0, 0)
	#define CAL_TMR_GetProperty  pfTMR_GetProperty
	#define CHK_TMR_GetProperty  (pfTMR_GetProperty != NULL)
	#define EXP_TMR_GetProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TMR_GetProperty", (RTS_UINTPTR)TMR_GetProperty, 0, 0) 
#endif




CAA_WORD CDECL TMR_GetSupplierVersion(CAA_BOOL xDummy);
typedef CAA_WORD (CDECL * PFTMR_GETSUPPLIERVERSION) (CAA_BOOL xDummy);
#if defined(CMPCAATIMER_NOTIMPLEMENTED) || defined(TMR_GETSUPPLIERVERSION_NOTIMPLEMENTED)
	#define USE_TMR_GetSupplierVersion
	#define EXT_TMR_GetSupplierVersion
	#define GET_TMR_GetSupplierVersion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TMR_GetSupplierVersion(p0)  (CAA_WORD)ERR_NOTIMPLEMENTED
	#define CHK_TMR_GetSupplierVersion  FALSE
	#define EXP_TMR_GetSupplierVersion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TMR_GetSupplierVersion
	#define EXT_TMR_GetSupplierVersion
	#define GET_TMR_GetSupplierVersion(fl)  CAL_CMGETAPI( "TMR_GetSupplierVersion" ) 
	#define CAL_TMR_GetSupplierVersion  TMR_GetSupplierVersion
	#define CHK_TMR_GetSupplierVersion  TRUE
	#define EXP_TMR_GetSupplierVersion  CAL_CMEXPAPI( "TMR_GetSupplierVersion" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAATIMER_EXTERNAL)
	#define USE_TMR_GetSupplierVersion
	#define EXT_TMR_GetSupplierVersion
	#define GET_TMR_GetSupplierVersion(fl)  CAL_CMGETAPI( "TMR_GetSupplierVersion" ) 
	#define CAL_TMR_GetSupplierVersion  TMR_GetSupplierVersion
	#define CHK_TMR_GetSupplierVersion  TRUE
	#define EXP_TMR_GetSupplierVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TMR_GetSupplierVersion", (RTS_UINTPTR)TMR_GetSupplierVersion, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATimerTMR_GetSupplierVersion
	#define EXT_CmpCAATimerTMR_GetSupplierVersion
	#define GET_CmpCAATimerTMR_GetSupplierVersion  ERR_OK
	#define CAL_CmpCAATimerTMR_GetSupplierVersion pICmpCAATimer->ITMR_GetSupplierVersion
	#define CHK_CmpCAATimerTMR_GetSupplierVersion (pICmpCAATimer != NULL)
	#define EXP_CmpCAATimerTMR_GetSupplierVersion  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TMR_GetSupplierVersion
	#define EXT_TMR_GetSupplierVersion
	#define GET_TMR_GetSupplierVersion(fl)  CAL_CMGETAPI( "TMR_GetSupplierVersion" ) 
	#define CAL_TMR_GetSupplierVersion pICmpCAATimer->ITMR_GetSupplierVersion
	#define CHK_TMR_GetSupplierVersion (pICmpCAATimer != NULL)
	#define EXP_TMR_GetSupplierVersion  CAL_CMEXPAPI( "TMR_GetSupplierVersion" ) 
#else /* DYNAMIC_LINK */
	#define USE_TMR_GetSupplierVersion  PFTMR_GETSUPPLIERVERSION pfTMR_GetSupplierVersion;
	#define EXT_TMR_GetSupplierVersion  extern PFTMR_GETSUPPLIERVERSION pfTMR_GetSupplierVersion;
	#define GET_TMR_GetSupplierVersion(fl)  s_pfCMGetAPI2( "TMR_GetSupplierVersion", (RTS_VOID_FCTPTR *)&pfTMR_GetSupplierVersion, (fl), 0, 0)
	#define CAL_TMR_GetSupplierVersion  pfTMR_GetSupplierVersion
	#define CHK_TMR_GetSupplierVersion  (pfTMR_GetSupplierVersion != NULL)
	#define EXP_TMR_GetSupplierVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TMR_GetSupplierVersion", (RTS_UINTPTR)TMR_GetSupplierVersion, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif


/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>tmr_createh</description>
 */
typedef struct tagtmr_createh_struct
{
	CAA_BOOL xCyclic;					/* VAR_INPUT */	/* FALSE: non cyclic send an event, TRUE: cyclic send an event */
	CAA_COUNT ctInterval;				/* VAR_INPUT */	/* timer interval in nanoseconds */
	RTS_IEC_XWORD dwParam;				/* VAR_INPUT */	/* parameter to transfer to callback function */
	CAA_BOOL xHardware;					/* VAR_INPUT */	/* TRUE: Hardwaretimer; FALSE: Softwaretimer */
	CAA_ENUM eTimer;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE TMR_CreateH;				/* VAR_OUTPUT */	/* hTimer */
} tmr_createh_struct;

void CDECL CDECL_EXT tmr_createh(tmr_createh_struct *p);
typedef void (CDECL CDECL_EXT* PFTMR_CREATEH_IEC) (tmr_createh_struct *p);
#if defined(CMPCAATIMER_NOTIMPLEMENTED) || defined(TMR_CREATEH_NOTIMPLEMENTED)
	#define USE_tmr_createh
	#define EXT_tmr_createh
	#define GET_tmr_createh(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tmr_createh(p0) 
	#define CHK_tmr_createh  FALSE
	#define EXP_tmr_createh  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tmr_createh
	#define EXT_tmr_createh
	#define GET_tmr_createh(fl)  CAL_CMGETAPI( "tmr_createh" ) 
	#define CAL_tmr_createh  tmr_createh
	#define CHK_tmr_createh  TRUE
	#define EXP_tmr_createh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_createh", (RTS_UINTPTR)tmr_createh, 1, RTSITF_GET_SIGNATURE(0, 0xCD6CF9CC), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAATIMER_EXTERNAL)
	#define USE_tmr_createh
	#define EXT_tmr_createh
	#define GET_tmr_createh(fl)  CAL_CMGETAPI( "tmr_createh" ) 
	#define CAL_tmr_createh  tmr_createh
	#define CHK_tmr_createh  TRUE
	#define EXP_tmr_createh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_createh", (RTS_UINTPTR)tmr_createh, 1, RTSITF_GET_SIGNATURE(0, 0xCD6CF9CC), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATimertmr_createh
	#define EXT_CmpCAATimertmr_createh
	#define GET_CmpCAATimertmr_createh  ERR_OK
	#define CAL_CmpCAATimertmr_createh  tmr_createh
	#define CHK_CmpCAATimertmr_createh  TRUE
	#define EXP_CmpCAATimertmr_createh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_createh", (RTS_UINTPTR)tmr_createh, 1, RTSITF_GET_SIGNATURE(0, 0xCD6CF9CC), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_tmr_createh
	#define EXT_tmr_createh
	#define GET_tmr_createh(fl)  CAL_CMGETAPI( "tmr_createh" ) 
	#define CAL_tmr_createh  tmr_createh
	#define CHK_tmr_createh  TRUE
	#define EXP_tmr_createh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_createh", (RTS_UINTPTR)tmr_createh, 1, RTSITF_GET_SIGNATURE(0, 0xCD6CF9CC), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_tmr_createh  PFTMR_CREATEH_IEC pftmr_createh;
	#define EXT_tmr_createh  extern PFTMR_CREATEH_IEC pftmr_createh;
	#define GET_tmr_createh(fl)  s_pfCMGetAPI2( "tmr_createh", (RTS_VOID_FCTPTR *)&pftmr_createh, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xCD6CF9CC), 0x03050500)
	#define CAL_tmr_createh  pftmr_createh
	#define CHK_tmr_createh  (pftmr_createh != NULL)
	#define EXP_tmr_createh   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_createh", (RTS_UINTPTR)tmr_createh, 1, RTSITF_GET_SIGNATURE(0, 0xCD6CF9CC), 0x03050500) 
#endif


/**
 * <description>tmr_createp</description>
 */
typedef struct tagtmr_createp_struct
{
	CAA_BOOL xCyclic;					/* VAR_INPUT */	/* FALSE: non cyclic send an event, TRUE: cyclic send an event */
	CAA_COUNT ctInterval;				/* VAR_INPUT */	/* timer interval in nanoseconds */
	RTS_IEC_XWORD dwParam;				/* VAR_INPUT */	/* parameter to transfer to callback function */
	CAA_BOOL xHardware;					/* VAR_INPUT */	/* TRUE: Hardwaretimer; FALSE: Softwaretimer */
	CAA_ENUM eTimer;					/* VAR_INPUT */	
	CAA_SIZE szMemSize;					/* VAR_INPUT */	
	CAA_PVOID pMemory;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE TMR_CreateP;				/* VAR_OUTPUT */	/* hTimer */
} tmr_createp_struct;

void CDECL CDECL_EXT tmr_createp(tmr_createp_struct *p);
typedef void (CDECL CDECL_EXT* PFTMR_CREATEP_IEC) (tmr_createp_struct *p);
#if defined(CMPCAATIMER_NOTIMPLEMENTED) || defined(TMR_CREATEP_NOTIMPLEMENTED)
	#define USE_tmr_createp
	#define EXT_tmr_createp
	#define GET_tmr_createp(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tmr_createp(p0) 
	#define CHK_tmr_createp  FALSE
	#define EXP_tmr_createp  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tmr_createp
	#define EXT_tmr_createp
	#define GET_tmr_createp(fl)  CAL_CMGETAPI( "tmr_createp" ) 
	#define CAL_tmr_createp  tmr_createp
	#define CHK_tmr_createp  TRUE
	#define EXP_tmr_createp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_createp", (RTS_UINTPTR)tmr_createp, 1, RTSITF_GET_SIGNATURE(0, 0x82CE337D), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAATIMER_EXTERNAL)
	#define USE_tmr_createp
	#define EXT_tmr_createp
	#define GET_tmr_createp(fl)  CAL_CMGETAPI( "tmr_createp" ) 
	#define CAL_tmr_createp  tmr_createp
	#define CHK_tmr_createp  TRUE
	#define EXP_tmr_createp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_createp", (RTS_UINTPTR)tmr_createp, 1, RTSITF_GET_SIGNATURE(0, 0x82CE337D), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATimertmr_createp
	#define EXT_CmpCAATimertmr_createp
	#define GET_CmpCAATimertmr_createp  ERR_OK
	#define CAL_CmpCAATimertmr_createp  tmr_createp
	#define CHK_CmpCAATimertmr_createp  TRUE
	#define EXP_CmpCAATimertmr_createp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_createp", (RTS_UINTPTR)tmr_createp, 1, RTSITF_GET_SIGNATURE(0, 0x82CE337D), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_tmr_createp
	#define EXT_tmr_createp
	#define GET_tmr_createp(fl)  CAL_CMGETAPI( "tmr_createp" ) 
	#define CAL_tmr_createp  tmr_createp
	#define CHK_tmr_createp  TRUE
	#define EXP_tmr_createp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_createp", (RTS_UINTPTR)tmr_createp, 1, RTSITF_GET_SIGNATURE(0, 0x82CE337D), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_tmr_createp  PFTMR_CREATEP_IEC pftmr_createp;
	#define EXT_tmr_createp  extern PFTMR_CREATEP_IEC pftmr_createp;
	#define GET_tmr_createp(fl)  s_pfCMGetAPI2( "tmr_createp", (RTS_VOID_FCTPTR *)&pftmr_createp, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x82CE337D), 0x03050500)
	#define CAL_tmr_createp  pftmr_createp
	#define CHK_tmr_createp  (pftmr_createp != NULL)
	#define EXP_tmr_createp   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_createp", (RTS_UINTPTR)tmr_createp, 1, RTSITF_GET_SIGNATURE(0, 0x82CE337D), 0x03050500) 
#endif


/**
 * <description>tmr_delete</description>
 */
typedef struct tagtmr_delete_struct
{
	CAA_HANDLE hTimer;					/* VAR_INPUT */	/* timer handle */
	CAA_ERROR TMR_Delete;				/* VAR_OUTPUT */	
} tmr_delete_struct;

void CDECL CDECL_EXT tmr_delete(tmr_delete_struct *p);
typedef void (CDECL CDECL_EXT* PFTMR_DELETE_IEC) (tmr_delete_struct *p);
#if defined(CMPCAATIMER_NOTIMPLEMENTED) || defined(TMR_DELETE_NOTIMPLEMENTED)
	#define USE_tmr_delete
	#define EXT_tmr_delete
	#define GET_tmr_delete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tmr_delete(p0) 
	#define CHK_tmr_delete  FALSE
	#define EXP_tmr_delete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tmr_delete
	#define EXT_tmr_delete
	#define GET_tmr_delete(fl)  CAL_CMGETAPI( "tmr_delete" ) 
	#define CAL_tmr_delete  tmr_delete
	#define CHK_tmr_delete  TRUE
	#define EXP_tmr_delete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_delete", (RTS_UINTPTR)tmr_delete, 1, RTSITF_GET_SIGNATURE(0, 0xE6D63FAA), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAATIMER_EXTERNAL)
	#define USE_tmr_delete
	#define EXT_tmr_delete
	#define GET_tmr_delete(fl)  CAL_CMGETAPI( "tmr_delete" ) 
	#define CAL_tmr_delete  tmr_delete
	#define CHK_tmr_delete  TRUE
	#define EXP_tmr_delete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_delete", (RTS_UINTPTR)tmr_delete, 1, RTSITF_GET_SIGNATURE(0, 0xE6D63FAA), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATimertmr_delete
	#define EXT_CmpCAATimertmr_delete
	#define GET_CmpCAATimertmr_delete  ERR_OK
	#define CAL_CmpCAATimertmr_delete  tmr_delete
	#define CHK_CmpCAATimertmr_delete  TRUE
	#define EXP_CmpCAATimertmr_delete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_delete", (RTS_UINTPTR)tmr_delete, 1, RTSITF_GET_SIGNATURE(0, 0xE6D63FAA), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_tmr_delete
	#define EXT_tmr_delete
	#define GET_tmr_delete(fl)  CAL_CMGETAPI( "tmr_delete" ) 
	#define CAL_tmr_delete  tmr_delete
	#define CHK_tmr_delete  TRUE
	#define EXP_tmr_delete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_delete", (RTS_UINTPTR)tmr_delete, 1, RTSITF_GET_SIGNATURE(0, 0xE6D63FAA), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_tmr_delete  PFTMR_DELETE_IEC pftmr_delete;
	#define EXT_tmr_delete  extern PFTMR_DELETE_IEC pftmr_delete;
	#define GET_tmr_delete(fl)  s_pfCMGetAPI2( "tmr_delete", (RTS_VOID_FCTPTR *)&pftmr_delete, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xE6D63FAA), 0x03050500)
	#define CAL_tmr_delete  pftmr_delete
	#define CHK_tmr_delete  (pftmr_delete != NULL)
	#define EXP_tmr_delete   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_delete", (RTS_UINTPTR)tmr_delete, 1, RTSITF_GET_SIGNATURE(0, 0xE6D63FAA), 0x03050500) 
#endif


/**
 * <description>tmr_getproperty</description>
 */
typedef struct tagtmr_getproperty_struct
{
	RTS_IEC_WORD wProperty;				/* VAR_INPUT */	/* property number */
	RTS_IEC_XWORD TMR_GetProperty;		/* VAR_OUTPUT */	
} tmr_getproperty_struct;

void CDECL CDECL_EXT tmr_getproperty(tmr_getproperty_struct *p);
typedef void (CDECL CDECL_EXT* PFTMR_GETPROPERTY_IEC) (tmr_getproperty_struct *p);
#if defined(CMPCAATIMER_NOTIMPLEMENTED) || defined(TMR_GETPROPERTY_NOTIMPLEMENTED)
	#define USE_tmr_getproperty
	#define EXT_tmr_getproperty
	#define GET_tmr_getproperty(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tmr_getproperty(p0) 
	#define CHK_tmr_getproperty  FALSE
	#define EXP_tmr_getproperty  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tmr_getproperty
	#define EXT_tmr_getproperty
	#define GET_tmr_getproperty(fl)  CAL_CMGETAPI( "tmr_getproperty" ) 
	#define CAL_tmr_getproperty  tmr_getproperty
	#define CHK_tmr_getproperty  TRUE
	#define EXP_tmr_getproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_getproperty", (RTS_UINTPTR)tmr_getproperty, 1, RTSITF_GET_SIGNATURE(0, 0x57855015), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAATIMER_EXTERNAL)
	#define USE_tmr_getproperty
	#define EXT_tmr_getproperty
	#define GET_tmr_getproperty(fl)  CAL_CMGETAPI( "tmr_getproperty" ) 
	#define CAL_tmr_getproperty  tmr_getproperty
	#define CHK_tmr_getproperty  TRUE
	#define EXP_tmr_getproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_getproperty", (RTS_UINTPTR)tmr_getproperty, 1, RTSITF_GET_SIGNATURE(0, 0x57855015), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATimertmr_getproperty
	#define EXT_CmpCAATimertmr_getproperty
	#define GET_CmpCAATimertmr_getproperty  ERR_OK
	#define CAL_CmpCAATimertmr_getproperty  tmr_getproperty
	#define CHK_CmpCAATimertmr_getproperty  TRUE
	#define EXP_CmpCAATimertmr_getproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_getproperty", (RTS_UINTPTR)tmr_getproperty, 1, RTSITF_GET_SIGNATURE(0, 0x57855015), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_tmr_getproperty
	#define EXT_tmr_getproperty
	#define GET_tmr_getproperty(fl)  CAL_CMGETAPI( "tmr_getproperty" ) 
	#define CAL_tmr_getproperty  tmr_getproperty
	#define CHK_tmr_getproperty  TRUE
	#define EXP_tmr_getproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_getproperty", (RTS_UINTPTR)tmr_getproperty, 1, RTSITF_GET_SIGNATURE(0, 0x57855015), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_tmr_getproperty  PFTMR_GETPROPERTY_IEC pftmr_getproperty;
	#define EXT_tmr_getproperty  extern PFTMR_GETPROPERTY_IEC pftmr_getproperty;
	#define GET_tmr_getproperty(fl)  s_pfCMGetAPI2( "tmr_getproperty", (RTS_VOID_FCTPTR *)&pftmr_getproperty, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x57855015), 0x03050500)
	#define CAL_tmr_getproperty  pftmr_getproperty
	#define CHK_tmr_getproperty  (pftmr_getproperty != NULL)
	#define EXP_tmr_getproperty   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_getproperty", (RTS_UINTPTR)tmr_getproperty, 1, RTSITF_GET_SIGNATURE(0, 0x57855015), 0x03050500) 
#endif


/**
 * <description>tmr_getquality</description>
 */
typedef struct tagtmr_getquality_struct
{
	CAA_HANDLE hTimer;					/* VAR_INPUT */	/* timer handle */
	TMR_QUALITY *pqTimer;				/* VAR_INPUT */	/* pointer to qualtiy structure, return the actual values in this structure */
	CAA_ERROR TMR_GetQuality;			/* VAR_OUTPUT */	
} tmr_getquality_struct;

void CDECL CDECL_EXT tmr_getquality(tmr_getquality_struct *p);
typedef void (CDECL CDECL_EXT* PFTMR_GETQUALITY_IEC) (tmr_getquality_struct *p);
#if defined(CMPCAATIMER_NOTIMPLEMENTED) || defined(TMR_GETQUALITY_NOTIMPLEMENTED)
	#define USE_tmr_getquality
	#define EXT_tmr_getquality
	#define GET_tmr_getquality(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tmr_getquality(p0) 
	#define CHK_tmr_getquality  FALSE
	#define EXP_tmr_getquality  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tmr_getquality
	#define EXT_tmr_getquality
	#define GET_tmr_getquality(fl)  CAL_CMGETAPI( "tmr_getquality" ) 
	#define CAL_tmr_getquality  tmr_getquality
	#define CHK_tmr_getquality  TRUE
	#define EXP_tmr_getquality  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_getquality", (RTS_UINTPTR)tmr_getquality, 1, RTSITF_GET_SIGNATURE(0, 0x5BB85F5E), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAATIMER_EXTERNAL)
	#define USE_tmr_getquality
	#define EXT_tmr_getquality
	#define GET_tmr_getquality(fl)  CAL_CMGETAPI( "tmr_getquality" ) 
	#define CAL_tmr_getquality  tmr_getquality
	#define CHK_tmr_getquality  TRUE
	#define EXP_tmr_getquality  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_getquality", (RTS_UINTPTR)tmr_getquality, 1, RTSITF_GET_SIGNATURE(0, 0x5BB85F5E), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATimertmr_getquality
	#define EXT_CmpCAATimertmr_getquality
	#define GET_CmpCAATimertmr_getquality  ERR_OK
	#define CAL_CmpCAATimertmr_getquality  tmr_getquality
	#define CHK_CmpCAATimertmr_getquality  TRUE
	#define EXP_CmpCAATimertmr_getquality  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_getquality", (RTS_UINTPTR)tmr_getquality, 1, RTSITF_GET_SIGNATURE(0, 0x5BB85F5E), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_tmr_getquality
	#define EXT_tmr_getquality
	#define GET_tmr_getquality(fl)  CAL_CMGETAPI( "tmr_getquality" ) 
	#define CAL_tmr_getquality  tmr_getquality
	#define CHK_tmr_getquality  TRUE
	#define EXP_tmr_getquality  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_getquality", (RTS_UINTPTR)tmr_getquality, 1, RTSITF_GET_SIGNATURE(0, 0x5BB85F5E), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_tmr_getquality  PFTMR_GETQUALITY_IEC pftmr_getquality;
	#define EXT_tmr_getquality  extern PFTMR_GETQUALITY_IEC pftmr_getquality;
	#define GET_tmr_getquality(fl)  s_pfCMGetAPI2( "tmr_getquality", (RTS_VOID_FCTPTR *)&pftmr_getquality, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x5BB85F5E), 0x03050500)
	#define CAL_tmr_getquality  pftmr_getquality
	#define CHK_tmr_getquality  (pftmr_getquality != NULL)
	#define EXP_tmr_getquality   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_getquality", (RTS_UINTPTR)tmr_getquality, 1, RTSITF_GET_SIGNATURE(0, 0x5BB85F5E), 0x03050500) 
#endif


/**
 * <description>tmr_getsize</description>
 */
typedef struct tagtmr_getsize_struct
{
	CAA_BOOL xCyclic;					/* VAR_INPUT */	/* FALSE: non cyclic send an event, TRUE: cyclic send an event */
	CAA_COUNT ctInterval;				/* VAR_INPUT */	/* timer interval in nanoseconds */
	RTS_IEC_XWORD dwParam;				/* VAR_INPUT */	/* parameter to transfer to callback function */
	CAA_BOOL xHardware;					/* VAR_INPUT */	/* TRUE: Hardwaretimer; FALSE: Softwaretimer */
	CAA_SIZE TMR_GetSize;				/* VAR_OUTPUT */	
} tmr_getsize_struct;

void CDECL CDECL_EXT tmr_getsize(tmr_getsize_struct *p);
typedef void (CDECL CDECL_EXT* PFTMR_GETSIZE_IEC) (tmr_getsize_struct *p);
#if defined(CMPCAATIMER_NOTIMPLEMENTED) || defined(TMR_GETSIZE_NOTIMPLEMENTED)
	#define USE_tmr_getsize
	#define EXT_tmr_getsize
	#define GET_tmr_getsize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tmr_getsize(p0) 
	#define CHK_tmr_getsize  FALSE
	#define EXP_tmr_getsize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tmr_getsize
	#define EXT_tmr_getsize
	#define GET_tmr_getsize(fl)  CAL_CMGETAPI( "tmr_getsize" ) 
	#define CAL_tmr_getsize  tmr_getsize
	#define CHK_tmr_getsize  TRUE
	#define EXP_tmr_getsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_getsize", (RTS_UINTPTR)tmr_getsize, 1, RTSITF_GET_SIGNATURE(0, 0x4819FDFC), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAATIMER_EXTERNAL)
	#define USE_tmr_getsize
	#define EXT_tmr_getsize
	#define GET_tmr_getsize(fl)  CAL_CMGETAPI( "tmr_getsize" ) 
	#define CAL_tmr_getsize  tmr_getsize
	#define CHK_tmr_getsize  TRUE
	#define EXP_tmr_getsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_getsize", (RTS_UINTPTR)tmr_getsize, 1, RTSITF_GET_SIGNATURE(0, 0x4819FDFC), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATimertmr_getsize
	#define EXT_CmpCAATimertmr_getsize
	#define GET_CmpCAATimertmr_getsize  ERR_OK
	#define CAL_CmpCAATimertmr_getsize  tmr_getsize
	#define CHK_CmpCAATimertmr_getsize  TRUE
	#define EXP_CmpCAATimertmr_getsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_getsize", (RTS_UINTPTR)tmr_getsize, 1, RTSITF_GET_SIGNATURE(0, 0x4819FDFC), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_tmr_getsize
	#define EXT_tmr_getsize
	#define GET_tmr_getsize(fl)  CAL_CMGETAPI( "tmr_getsize" ) 
	#define CAL_tmr_getsize  tmr_getsize
	#define CHK_tmr_getsize  TRUE
	#define EXP_tmr_getsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_getsize", (RTS_UINTPTR)tmr_getsize, 1, RTSITF_GET_SIGNATURE(0, 0x4819FDFC), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_tmr_getsize  PFTMR_GETSIZE_IEC pftmr_getsize;
	#define EXT_tmr_getsize  extern PFTMR_GETSIZE_IEC pftmr_getsize;
	#define GET_tmr_getsize(fl)  s_pfCMGetAPI2( "tmr_getsize", (RTS_VOID_FCTPTR *)&pftmr_getsize, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x4819FDFC), 0x03050500)
	#define CAL_tmr_getsize  pftmr_getsize
	#define CHK_tmr_getsize  (pftmr_getsize != NULL)
	#define EXP_tmr_getsize   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_getsize", (RTS_UINTPTR)tmr_getsize, 1, RTSITF_GET_SIGNATURE(0, 0x4819FDFC), 0x03050500) 
#endif


/**
 * <description>tmr_getsupplierversion</description>
 */
typedef struct tagtmr_getsupplierversion_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	RTS_IEC_WORD TMR_GetSupplierVersion;	/* VAR_OUTPUT */	
} tmr_getsupplierversion_struct;

void CDECL CDECL_EXT tmr_getsupplierversion(tmr_getsupplierversion_struct *p);
typedef void (CDECL CDECL_EXT* PFTMR_GETSUPPLIERVERSION_IEC) (tmr_getsupplierversion_struct *p);
#if defined(CMPCAATIMER_NOTIMPLEMENTED) || defined(TMR_GETSUPPLIERVERSION_NOTIMPLEMENTED)
	#define USE_tmr_getsupplierversion
	#define EXT_tmr_getsupplierversion
	#define GET_tmr_getsupplierversion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tmr_getsupplierversion(p0) 
	#define CHK_tmr_getsupplierversion  FALSE
	#define EXP_tmr_getsupplierversion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tmr_getsupplierversion
	#define EXT_tmr_getsupplierversion
	#define GET_tmr_getsupplierversion(fl)  CAL_CMGETAPI( "tmr_getsupplierversion" ) 
	#define CAL_tmr_getsupplierversion  tmr_getsupplierversion
	#define CHK_tmr_getsupplierversion  TRUE
	#define EXP_tmr_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_getsupplierversion", (RTS_UINTPTR)tmr_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0x353E7392), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAATIMER_EXTERNAL)
	#define USE_tmr_getsupplierversion
	#define EXT_tmr_getsupplierversion
	#define GET_tmr_getsupplierversion(fl)  CAL_CMGETAPI( "tmr_getsupplierversion" ) 
	#define CAL_tmr_getsupplierversion  tmr_getsupplierversion
	#define CHK_tmr_getsupplierversion  TRUE
	#define EXP_tmr_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_getsupplierversion", (RTS_UINTPTR)tmr_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0x353E7392), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATimertmr_getsupplierversion
	#define EXT_CmpCAATimertmr_getsupplierversion
	#define GET_CmpCAATimertmr_getsupplierversion  ERR_OK
	#define CAL_CmpCAATimertmr_getsupplierversion  tmr_getsupplierversion
	#define CHK_CmpCAATimertmr_getsupplierversion  TRUE
	#define EXP_CmpCAATimertmr_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_getsupplierversion", (RTS_UINTPTR)tmr_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0x353E7392), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_tmr_getsupplierversion
	#define EXT_tmr_getsupplierversion
	#define GET_tmr_getsupplierversion(fl)  CAL_CMGETAPI( "tmr_getsupplierversion" ) 
	#define CAL_tmr_getsupplierversion  tmr_getsupplierversion
	#define CHK_tmr_getsupplierversion  TRUE
	#define EXP_tmr_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_getsupplierversion", (RTS_UINTPTR)tmr_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0x353E7392), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_tmr_getsupplierversion  PFTMR_GETSUPPLIERVERSION_IEC pftmr_getsupplierversion;
	#define EXT_tmr_getsupplierversion  extern PFTMR_GETSUPPLIERVERSION_IEC pftmr_getsupplierversion;
	#define GET_tmr_getsupplierversion(fl)  s_pfCMGetAPI2( "tmr_getsupplierversion", (RTS_VOID_FCTPTR *)&pftmr_getsupplierversion, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x353E7392), 0x03050500)
	#define CAL_tmr_getsupplierversion  pftmr_getsupplierversion
	#define CHK_tmr_getsupplierversion  (pftmr_getsupplierversion != NULL)
	#define EXP_tmr_getsupplierversion   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_getsupplierversion", (RTS_UINTPTR)tmr_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0x353E7392), 0x03050500) 
#endif


/**
 * <description>tmr_start</description>
 */
typedef struct tagtmr_start_struct
{
	CAA_HANDLE hTimer;					/* VAR_INPUT */	/* timer handle */
	CAA_ERROR TMR_Start;				/* VAR_OUTPUT */	
} tmr_start_struct;

void CDECL CDECL_EXT tmr_start(tmr_start_struct *p);
typedef void (CDECL CDECL_EXT* PFTMR_START_IEC) (tmr_start_struct *p);
#if defined(CMPCAATIMER_NOTIMPLEMENTED) || defined(TMR_START_NOTIMPLEMENTED)
	#define USE_tmr_start
	#define EXT_tmr_start
	#define GET_tmr_start(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tmr_start(p0) 
	#define CHK_tmr_start  FALSE
	#define EXP_tmr_start  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tmr_start
	#define EXT_tmr_start
	#define GET_tmr_start(fl)  CAL_CMGETAPI( "tmr_start" ) 
	#define CAL_tmr_start  tmr_start
	#define CHK_tmr_start  TRUE
	#define EXP_tmr_start  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_start", (RTS_UINTPTR)tmr_start, 1, RTSITF_GET_SIGNATURE(0, 0x31717A79), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAATIMER_EXTERNAL)
	#define USE_tmr_start
	#define EXT_tmr_start
	#define GET_tmr_start(fl)  CAL_CMGETAPI( "tmr_start" ) 
	#define CAL_tmr_start  tmr_start
	#define CHK_tmr_start  TRUE
	#define EXP_tmr_start  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_start", (RTS_UINTPTR)tmr_start, 1, RTSITF_GET_SIGNATURE(0, 0x31717A79), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATimertmr_start
	#define EXT_CmpCAATimertmr_start
	#define GET_CmpCAATimertmr_start  ERR_OK
	#define CAL_CmpCAATimertmr_start  tmr_start
	#define CHK_CmpCAATimertmr_start  TRUE
	#define EXP_CmpCAATimertmr_start  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_start", (RTS_UINTPTR)tmr_start, 1, RTSITF_GET_SIGNATURE(0, 0x31717A79), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_tmr_start
	#define EXT_tmr_start
	#define GET_tmr_start(fl)  CAL_CMGETAPI( "tmr_start" ) 
	#define CAL_tmr_start  tmr_start
	#define CHK_tmr_start  TRUE
	#define EXP_tmr_start  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_start", (RTS_UINTPTR)tmr_start, 1, RTSITF_GET_SIGNATURE(0, 0x31717A79), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_tmr_start  PFTMR_START_IEC pftmr_start;
	#define EXT_tmr_start  extern PFTMR_START_IEC pftmr_start;
	#define GET_tmr_start(fl)  s_pfCMGetAPI2( "tmr_start", (RTS_VOID_FCTPTR *)&pftmr_start, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x31717A79), 0x03050500)
	#define CAL_tmr_start  pftmr_start
	#define CHK_tmr_start  (pftmr_start != NULL)
	#define EXP_tmr_start   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_start", (RTS_UINTPTR)tmr_start, 1, RTSITF_GET_SIGNATURE(0, 0x31717A79), 0x03050500) 
#endif


/**
 * <description>tmr_stop</description>
 */
typedef struct tagtmr_stop_struct
{
	CAA_HANDLE hTimer;					/* VAR_INPUT */	/* timer handle */
	CAA_ERROR TMR_Stop;					/* VAR_OUTPUT */	
} tmr_stop_struct;

void CDECL CDECL_EXT tmr_stop(tmr_stop_struct *p);
typedef void (CDECL CDECL_EXT* PFTMR_STOP_IEC) (tmr_stop_struct *p);
#if defined(CMPCAATIMER_NOTIMPLEMENTED) || defined(TMR_STOP_NOTIMPLEMENTED)
	#define USE_tmr_stop
	#define EXT_tmr_stop
	#define GET_tmr_stop(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tmr_stop(p0) 
	#define CHK_tmr_stop  FALSE
	#define EXP_tmr_stop  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tmr_stop
	#define EXT_tmr_stop
	#define GET_tmr_stop(fl)  CAL_CMGETAPI( "tmr_stop" ) 
	#define CAL_tmr_stop  tmr_stop
	#define CHK_tmr_stop  TRUE
	#define EXP_tmr_stop  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_stop", (RTS_UINTPTR)tmr_stop, 1, RTSITF_GET_SIGNATURE(0, 0x816F6062), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAATIMER_EXTERNAL)
	#define USE_tmr_stop
	#define EXT_tmr_stop
	#define GET_tmr_stop(fl)  CAL_CMGETAPI( "tmr_stop" ) 
	#define CAL_tmr_stop  tmr_stop
	#define CHK_tmr_stop  TRUE
	#define EXP_tmr_stop  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_stop", (RTS_UINTPTR)tmr_stop, 1, RTSITF_GET_SIGNATURE(0, 0x816F6062), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATimertmr_stop
	#define EXT_CmpCAATimertmr_stop
	#define GET_CmpCAATimertmr_stop  ERR_OK
	#define CAL_CmpCAATimertmr_stop  tmr_stop
	#define CHK_CmpCAATimertmr_stop  TRUE
	#define EXP_CmpCAATimertmr_stop  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_stop", (RTS_UINTPTR)tmr_stop, 1, RTSITF_GET_SIGNATURE(0, 0x816F6062), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_tmr_stop
	#define EXT_tmr_stop
	#define GET_tmr_stop(fl)  CAL_CMGETAPI( "tmr_stop" ) 
	#define CAL_tmr_stop  tmr_stop
	#define CHK_tmr_stop  TRUE
	#define EXP_tmr_stop  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_stop", (RTS_UINTPTR)tmr_stop, 1, RTSITF_GET_SIGNATURE(0, 0x816F6062), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_tmr_stop  PFTMR_STOP_IEC pftmr_stop;
	#define EXT_tmr_stop  extern PFTMR_STOP_IEC pftmr_stop;
	#define GET_tmr_stop(fl)  s_pfCMGetAPI2( "tmr_stop", (RTS_VOID_FCTPTR *)&pftmr_stop, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x816F6062), 0x03050500)
	#define CAL_tmr_stop  pftmr_stop
	#define CHK_tmr_stop  (pftmr_stop != NULL)
	#define EXP_tmr_stop   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tmr_stop", (RTS_UINTPTR)tmr_stop, 1, RTSITF_GET_SIGNATURE(0, 0x816F6062), 0x03050500) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
	PFTMR_CREATEH ITMR_CreateH;
 	PFTMR_CREATEP ITMR_CreateP;
 	PFTMR_GETSIZE ITMR_GetSize;
 	PFTMR_START ITMR_Start;
 	PFTMR_STOP ITMR_Stop;
 	PFTMR_DELETE ITMR_Delete;
 	PFTMR_GETQUALITY ITMR_GetQuality;
 	PFTMR_GETPROPERTY ITMR_GetProperty;
 	PFTMR_GETSUPPLIERVERSION ITMR_GetSupplierVersion;
 } ICmpCAATimer_C;

#ifdef CPLUSPLUS
class ICmpCAATimer : public IBase
{
	public:
		virtual CAA_HANDLE CDECL ITMR_CreateH(CAA_BOOL xCyclic, CAA_COUNT ctInterval, RTS_IEC_XWORD dwParam, CAA_BOOL xHardware, CAA_ENUM eTimer, CAA_ERROR *peError) =0;
		virtual CAA_HANDLE CDECL ITMR_CreateP(CAA_BOOL xCyclic, CAA_COUNT ctInterval, RTS_IEC_XWORD dwParam, CAA_BOOL xHardware, CAA_ENUM eTimer, CAA_SIZE szMemSize, CAA_PVOID pMemory, CAA_ERROR *peError) =0;
		virtual CAA_SIZE CDECL ITMR_GetSize(CAA_BOOL xCyclic, CAA_COUNT ctInterval, RTS_IEC_XWORD dwParam, CAA_BOOL xHardware) =0;
		virtual CAA_ERROR CDECL ITMR_Start(CAA_HANDLE hTimer) =0;
		virtual CAA_ERROR CDECL ITMR_Stop(CAA_HANDLE hTimer) =0;
		virtual CAA_ERROR CDECL ITMR_Delete(CAA_HANDLE hTimer) =0;
		virtual CAA_ERROR CDECL ITMR_GetQuality(CAA_HANDLE hTimer, TMR_QUALITY *pqTimer) =0;
		virtual RTS_IEC_XWORD CDECL ITMR_GetProperty(CAA_WORD wProperty) =0;
		virtual CAA_WORD CDECL ITMR_GetSupplierVersion(CAA_BOOL xDummy) =0;
};
	#ifndef ITF_CmpCAATimer
		#define ITF_CmpCAATimer static ICmpCAATimer *pICmpCAATimer = NULL;
	#endif
	#define EXTITF_CmpCAATimer
#else	/*CPLUSPLUS*/
	typedef ICmpCAATimer_C		ICmpCAATimer;
	#ifndef ITF_CmpCAATimer
		#define ITF_CmpCAATimer
	#endif
	#define EXTITF_CmpCAATimer
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCAATIMERITF_H_*/
