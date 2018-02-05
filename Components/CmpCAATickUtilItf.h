 /**
 * <interfacename>CmpCAATickUtil</interfacename>
 * <description></description> 
 *
 * <copyright></copyright>
 */


	
	
#ifndef _CMPCAATICKUTILITF_H_
#define _CMPCAATICKUTILITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAATickUtil.h"

#ifdef __cplusplus
extern "C" {
#endif

CAA_TICK CDECL TICKU_ConvertNSecToTick(RTS_UI32 ulNSeconds);
typedef CAA_TICK (CDECL * PFTICKU_CONVERTNSECTOTICK) (RTS_UI32 ulNSeconds);
#if defined(CMPCAATICKUTIL_NOTIMPLEMENTED) || defined(TICKU_CONVERTNSECTOTICK_NOTIMPLEMENTED)
	#define USE_TICKU_ConvertNSecToTick
	#define EXT_TICKU_ConvertNSecToTick
	#define GET_TICKU_ConvertNSecToTick(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TICKU_ConvertNSecToTick(p0)  (CAA_TICK)ERR_NOTIMPLEMENTED
	#define CHK_TICKU_ConvertNSecToTick  FALSE
	#define EXP_TICKU_ConvertNSecToTick  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TICKU_ConvertNSecToTick
	#define EXT_TICKU_ConvertNSecToTick
	#define GET_TICKU_ConvertNSecToTick(fl)  CAL_CMGETAPI( "TICKU_ConvertNSecToTick" ) 
	#define CAL_TICKU_ConvertNSecToTick  TICKU_ConvertNSecToTick
	#define CHK_TICKU_ConvertNSecToTick  TRUE
	#define EXP_TICKU_ConvertNSecToTick  CAL_CMEXPAPI( "TICKU_ConvertNSecToTick" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAATICKUTIL_EXTERNAL)
	#define USE_TICKU_ConvertNSecToTick
	#define EXT_TICKU_ConvertNSecToTick
	#define GET_TICKU_ConvertNSecToTick(fl)  CAL_CMGETAPI( "TICKU_ConvertNSecToTick" ) 
	#define CAL_TICKU_ConvertNSecToTick  TICKU_ConvertNSecToTick
	#define CHK_TICKU_ConvertNSecToTick  TRUE
	#define EXP_TICKU_ConvertNSecToTick  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TICKU_ConvertNSecToTick", (RTS_UINTPTR)TICKU_ConvertNSecToTick, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATickUtilTICKU_ConvertNSecToTick
	#define EXT_CmpCAATickUtilTICKU_ConvertNSecToTick
	#define GET_CmpCAATickUtilTICKU_ConvertNSecToTick  ERR_OK
	#define CAL_CmpCAATickUtilTICKU_ConvertNSecToTick pICmpCAATickUtil->ITICKU_ConvertNSecToTick
	#define CHK_CmpCAATickUtilTICKU_ConvertNSecToTick (pICmpCAATickUtil != NULL)
	#define EXP_CmpCAATickUtilTICKU_ConvertNSecToTick  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TICKU_ConvertNSecToTick
	#define EXT_TICKU_ConvertNSecToTick
	#define GET_TICKU_ConvertNSecToTick(fl)  CAL_CMGETAPI( "TICKU_ConvertNSecToTick" ) 
	#define CAL_TICKU_ConvertNSecToTick pICmpCAATickUtil->ITICKU_ConvertNSecToTick
	#define CHK_TICKU_ConvertNSecToTick (pICmpCAATickUtil != NULL)
	#define EXP_TICKU_ConvertNSecToTick  CAL_CMEXPAPI( "TICKU_ConvertNSecToTick" ) 
#else /* DYNAMIC_LINK */
	#define USE_TICKU_ConvertNSecToTick  PFTICKU_CONVERTNSECTOTICK pfTICKU_ConvertNSecToTick;
	#define EXT_TICKU_ConvertNSecToTick  extern PFTICKU_CONVERTNSECTOTICK pfTICKU_ConvertNSecToTick;
	#define GET_TICKU_ConvertNSecToTick(fl)  s_pfCMGetAPI2( "TICKU_ConvertNSecToTick", (RTS_VOID_FCTPTR *)&pfTICKU_ConvertNSecToTick, (fl), 0, 0)
	#define CAL_TICKU_ConvertNSecToTick  pfTICKU_ConvertNSecToTick
	#define CHK_TICKU_ConvertNSecToTick  (pfTICKU_ConvertNSecToTick != NULL)
	#define EXP_TICKU_ConvertNSecToTick  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TICKU_ConvertNSecToTick", (RTS_UINTPTR)TICKU_ConvertNSecToTick, 0, 0) 
#endif



RTS_UI32 CDECL TICKU_ConvertTickToNSec(CAA_TICK tkTick);
typedef RTS_UI32 (CDECL * PFTICKU_CONVERTTICKTONSEC) (CAA_TICK tkTick);
#if defined(CMPCAATICKUTIL_NOTIMPLEMENTED) || defined(TICKU_CONVERTTICKTONSEC_NOTIMPLEMENTED)
	#define USE_TICKU_ConvertTickToNSec
	#define EXT_TICKU_ConvertTickToNSec
	#define GET_TICKU_ConvertTickToNSec(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TICKU_ConvertTickToNSec(p0)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_TICKU_ConvertTickToNSec  FALSE
	#define EXP_TICKU_ConvertTickToNSec  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TICKU_ConvertTickToNSec
	#define EXT_TICKU_ConvertTickToNSec
	#define GET_TICKU_ConvertTickToNSec(fl)  CAL_CMGETAPI( "TICKU_ConvertTickToNSec" ) 
	#define CAL_TICKU_ConvertTickToNSec  TICKU_ConvertTickToNSec
	#define CHK_TICKU_ConvertTickToNSec  TRUE
	#define EXP_TICKU_ConvertTickToNSec  CAL_CMEXPAPI( "TICKU_ConvertTickToNSec" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAATICKUTIL_EXTERNAL)
	#define USE_TICKU_ConvertTickToNSec
	#define EXT_TICKU_ConvertTickToNSec
	#define GET_TICKU_ConvertTickToNSec(fl)  CAL_CMGETAPI( "TICKU_ConvertTickToNSec" ) 
	#define CAL_TICKU_ConvertTickToNSec  TICKU_ConvertTickToNSec
	#define CHK_TICKU_ConvertTickToNSec  TRUE
	#define EXP_TICKU_ConvertTickToNSec  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TICKU_ConvertTickToNSec", (RTS_UINTPTR)TICKU_ConvertTickToNSec, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATickUtilTICKU_ConvertTickToNSec
	#define EXT_CmpCAATickUtilTICKU_ConvertTickToNSec
	#define GET_CmpCAATickUtilTICKU_ConvertTickToNSec  ERR_OK
	#define CAL_CmpCAATickUtilTICKU_ConvertTickToNSec pICmpCAATickUtil->ITICKU_ConvertTickToNSec
	#define CHK_CmpCAATickUtilTICKU_ConvertTickToNSec (pICmpCAATickUtil != NULL)
	#define EXP_CmpCAATickUtilTICKU_ConvertTickToNSec  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TICKU_ConvertTickToNSec
	#define EXT_TICKU_ConvertTickToNSec
	#define GET_TICKU_ConvertTickToNSec(fl)  CAL_CMGETAPI( "TICKU_ConvertTickToNSec" ) 
	#define CAL_TICKU_ConvertTickToNSec pICmpCAATickUtil->ITICKU_ConvertTickToNSec
	#define CHK_TICKU_ConvertTickToNSec (pICmpCAATickUtil != NULL)
	#define EXP_TICKU_ConvertTickToNSec  CAL_CMEXPAPI( "TICKU_ConvertTickToNSec" ) 
#else /* DYNAMIC_LINK */
	#define USE_TICKU_ConvertTickToNSec  PFTICKU_CONVERTTICKTONSEC pfTICKU_ConvertTickToNSec;
	#define EXT_TICKU_ConvertTickToNSec  extern PFTICKU_CONVERTTICKTONSEC pfTICKU_ConvertTickToNSec;
	#define GET_TICKU_ConvertTickToNSec(fl)  s_pfCMGetAPI2( "TICKU_ConvertTickToNSec", (RTS_VOID_FCTPTR *)&pfTICKU_ConvertTickToNSec, (fl), 0, 0)
	#define CAL_TICKU_ConvertTickToNSec  pfTICKU_ConvertTickToNSec
	#define CHK_TICKU_ConvertTickToNSec  (pfTICKU_ConvertTickToNSec != NULL)
	#define EXP_TICKU_ConvertTickToNSec  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TICKU_ConvertTickToNSec", (RTS_UINTPTR)TICKU_ConvertTickToNSec, 0, 0) 
#endif



RTS_UI32 CDECL TICKU_ConvertTickToUSec(CAA_TICK tkTick);
typedef RTS_UI32 (CDECL * PFTICKU_CONVERTTICKTOUSEC) (CAA_TICK tkTick);
#if defined(CMPCAATICKUTIL_NOTIMPLEMENTED) || defined(TICKU_CONVERTTICKTOUSEC_NOTIMPLEMENTED)
	#define USE_TICKU_ConvertTickToUSec
	#define EXT_TICKU_ConvertTickToUSec
	#define GET_TICKU_ConvertTickToUSec(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TICKU_ConvertTickToUSec(p0)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_TICKU_ConvertTickToUSec  FALSE
	#define EXP_TICKU_ConvertTickToUSec  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TICKU_ConvertTickToUSec
	#define EXT_TICKU_ConvertTickToUSec
	#define GET_TICKU_ConvertTickToUSec(fl)  CAL_CMGETAPI( "TICKU_ConvertTickToUSec" ) 
	#define CAL_TICKU_ConvertTickToUSec  TICKU_ConvertTickToUSec
	#define CHK_TICKU_ConvertTickToUSec  TRUE
	#define EXP_TICKU_ConvertTickToUSec  CAL_CMEXPAPI( "TICKU_ConvertTickToUSec" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAATICKUTIL_EXTERNAL)
	#define USE_TICKU_ConvertTickToUSec
	#define EXT_TICKU_ConvertTickToUSec
	#define GET_TICKU_ConvertTickToUSec(fl)  CAL_CMGETAPI( "TICKU_ConvertTickToUSec" ) 
	#define CAL_TICKU_ConvertTickToUSec  TICKU_ConvertTickToUSec
	#define CHK_TICKU_ConvertTickToUSec  TRUE
	#define EXP_TICKU_ConvertTickToUSec  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TICKU_ConvertTickToUSec", (RTS_UINTPTR)TICKU_ConvertTickToUSec, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATickUtilTICKU_ConvertTickToUSec
	#define EXT_CmpCAATickUtilTICKU_ConvertTickToUSec
	#define GET_CmpCAATickUtilTICKU_ConvertTickToUSec  ERR_OK
	#define CAL_CmpCAATickUtilTICKU_ConvertTickToUSec pICmpCAATickUtil->ITICKU_ConvertTickToUSec
	#define CHK_CmpCAATickUtilTICKU_ConvertTickToUSec (pICmpCAATickUtil != NULL)
	#define EXP_CmpCAATickUtilTICKU_ConvertTickToUSec  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TICKU_ConvertTickToUSec
	#define EXT_TICKU_ConvertTickToUSec
	#define GET_TICKU_ConvertTickToUSec(fl)  CAL_CMGETAPI( "TICKU_ConvertTickToUSec" ) 
	#define CAL_TICKU_ConvertTickToUSec pICmpCAATickUtil->ITICKU_ConvertTickToUSec
	#define CHK_TICKU_ConvertTickToUSec (pICmpCAATickUtil != NULL)
	#define EXP_TICKU_ConvertTickToUSec  CAL_CMEXPAPI( "TICKU_ConvertTickToUSec" ) 
#else /* DYNAMIC_LINK */
	#define USE_TICKU_ConvertTickToUSec  PFTICKU_CONVERTTICKTOUSEC pfTICKU_ConvertTickToUSec;
	#define EXT_TICKU_ConvertTickToUSec  extern PFTICKU_CONVERTTICKTOUSEC pfTICKU_ConvertTickToUSec;
	#define GET_TICKU_ConvertTickToUSec(fl)  s_pfCMGetAPI2( "TICKU_ConvertTickToUSec", (RTS_VOID_FCTPTR *)&pfTICKU_ConvertTickToUSec, (fl), 0, 0)
	#define CAL_TICKU_ConvertTickToUSec  pfTICKU_ConvertTickToUSec
	#define CHK_TICKU_ConvertTickToUSec  (pfTICKU_ConvertTickToUSec != NULL)
	#define EXP_TICKU_ConvertTickToUSec  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TICKU_ConvertTickToUSec", (RTS_UINTPTR)TICKU_ConvertTickToUSec, 0, 0) 
#endif



CAA_TICK CDECL TICKU_ConvertUSecToTick(RTS_UI32 ulUSeconds);
typedef CAA_TICK (CDECL * PFTICKU_CONVERTUSECTOTICK) (RTS_UI32 ulUSeconds);
#if defined(CMPCAATICKUTIL_NOTIMPLEMENTED) || defined(TICKU_CONVERTUSECTOTICK_NOTIMPLEMENTED)
	#define USE_TICKU_ConvertUSecToTick
	#define EXT_TICKU_ConvertUSecToTick
	#define GET_TICKU_ConvertUSecToTick(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TICKU_ConvertUSecToTick(p0)  (CAA_TICK)ERR_NOTIMPLEMENTED
	#define CHK_TICKU_ConvertUSecToTick  FALSE
	#define EXP_TICKU_ConvertUSecToTick  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TICKU_ConvertUSecToTick
	#define EXT_TICKU_ConvertUSecToTick
	#define GET_TICKU_ConvertUSecToTick(fl)  CAL_CMGETAPI( "TICKU_ConvertUSecToTick" ) 
	#define CAL_TICKU_ConvertUSecToTick  TICKU_ConvertUSecToTick
	#define CHK_TICKU_ConvertUSecToTick  TRUE
	#define EXP_TICKU_ConvertUSecToTick  CAL_CMEXPAPI( "TICKU_ConvertUSecToTick" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAATICKUTIL_EXTERNAL)
	#define USE_TICKU_ConvertUSecToTick
	#define EXT_TICKU_ConvertUSecToTick
	#define GET_TICKU_ConvertUSecToTick(fl)  CAL_CMGETAPI( "TICKU_ConvertUSecToTick" ) 
	#define CAL_TICKU_ConvertUSecToTick  TICKU_ConvertUSecToTick
	#define CHK_TICKU_ConvertUSecToTick  TRUE
	#define EXP_TICKU_ConvertUSecToTick  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TICKU_ConvertUSecToTick", (RTS_UINTPTR)TICKU_ConvertUSecToTick, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATickUtilTICKU_ConvertUSecToTick
	#define EXT_CmpCAATickUtilTICKU_ConvertUSecToTick
	#define GET_CmpCAATickUtilTICKU_ConvertUSecToTick  ERR_OK
	#define CAL_CmpCAATickUtilTICKU_ConvertUSecToTick pICmpCAATickUtil->ITICKU_ConvertUSecToTick
	#define CHK_CmpCAATickUtilTICKU_ConvertUSecToTick (pICmpCAATickUtil != NULL)
	#define EXP_CmpCAATickUtilTICKU_ConvertUSecToTick  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TICKU_ConvertUSecToTick
	#define EXT_TICKU_ConvertUSecToTick
	#define GET_TICKU_ConvertUSecToTick(fl)  CAL_CMGETAPI( "TICKU_ConvertUSecToTick" ) 
	#define CAL_TICKU_ConvertUSecToTick pICmpCAATickUtil->ITICKU_ConvertUSecToTick
	#define CHK_TICKU_ConvertUSecToTick (pICmpCAATickUtil != NULL)
	#define EXP_TICKU_ConvertUSecToTick  CAL_CMEXPAPI( "TICKU_ConvertUSecToTick" ) 
#else /* DYNAMIC_LINK */
	#define USE_TICKU_ConvertUSecToTick  PFTICKU_CONVERTUSECTOTICK pfTICKU_ConvertUSecToTick;
	#define EXT_TICKU_ConvertUSecToTick  extern PFTICKU_CONVERTUSECTOTICK pfTICKU_ConvertUSecToTick;
	#define GET_TICKU_ConvertUSecToTick(fl)  s_pfCMGetAPI2( "TICKU_ConvertUSecToTick", (RTS_VOID_FCTPTR *)&pfTICKU_ConvertUSecToTick, (fl), 0, 0)
	#define CAL_TICKU_ConvertUSecToTick  pfTICKU_ConvertUSecToTick
	#define CHK_TICKU_ConvertUSecToTick  (pfTICKU_ConvertUSecToTick != NULL)
	#define EXP_TICKU_ConvertUSecToTick  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TICKU_ConvertUSecToTick", (RTS_UINTPTR)TICKU_ConvertUSecToTick, 0, 0) 
#endif



RTS_UI32 CDECL TICKU_GetElapsedTimeInNSec(CAA_TICK tkStart);
typedef RTS_UI32 (CDECL * PFTICKU_GETELAPSEDTIMEINNSEC) (CAA_TICK tkStart);
#if defined(CMPCAATICKUTIL_NOTIMPLEMENTED) || defined(TICKU_GETELAPSEDTIMEINNSEC_NOTIMPLEMENTED)
	#define USE_TICKU_GetElapsedTimeInNSec
	#define EXT_TICKU_GetElapsedTimeInNSec
	#define GET_TICKU_GetElapsedTimeInNSec(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TICKU_GetElapsedTimeInNSec(p0)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_TICKU_GetElapsedTimeInNSec  FALSE
	#define EXP_TICKU_GetElapsedTimeInNSec  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TICKU_GetElapsedTimeInNSec
	#define EXT_TICKU_GetElapsedTimeInNSec
	#define GET_TICKU_GetElapsedTimeInNSec(fl)  CAL_CMGETAPI( "TICKU_GetElapsedTimeInNSec" ) 
	#define CAL_TICKU_GetElapsedTimeInNSec  TICKU_GetElapsedTimeInNSec
	#define CHK_TICKU_GetElapsedTimeInNSec  TRUE
	#define EXP_TICKU_GetElapsedTimeInNSec  CAL_CMEXPAPI( "TICKU_GetElapsedTimeInNSec" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAATICKUTIL_EXTERNAL)
	#define USE_TICKU_GetElapsedTimeInNSec
	#define EXT_TICKU_GetElapsedTimeInNSec
	#define GET_TICKU_GetElapsedTimeInNSec(fl)  CAL_CMGETAPI( "TICKU_GetElapsedTimeInNSec" ) 
	#define CAL_TICKU_GetElapsedTimeInNSec  TICKU_GetElapsedTimeInNSec
	#define CHK_TICKU_GetElapsedTimeInNSec  TRUE
	#define EXP_TICKU_GetElapsedTimeInNSec  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TICKU_GetElapsedTimeInNSec", (RTS_UINTPTR)TICKU_GetElapsedTimeInNSec, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATickUtilTICKU_GetElapsedTimeInNSec
	#define EXT_CmpCAATickUtilTICKU_GetElapsedTimeInNSec
	#define GET_CmpCAATickUtilTICKU_GetElapsedTimeInNSec  ERR_OK
	#define CAL_CmpCAATickUtilTICKU_GetElapsedTimeInNSec pICmpCAATickUtil->ITICKU_GetElapsedTimeInNSec
	#define CHK_CmpCAATickUtilTICKU_GetElapsedTimeInNSec (pICmpCAATickUtil != NULL)
	#define EXP_CmpCAATickUtilTICKU_GetElapsedTimeInNSec  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TICKU_GetElapsedTimeInNSec
	#define EXT_TICKU_GetElapsedTimeInNSec
	#define GET_TICKU_GetElapsedTimeInNSec(fl)  CAL_CMGETAPI( "TICKU_GetElapsedTimeInNSec" ) 
	#define CAL_TICKU_GetElapsedTimeInNSec pICmpCAATickUtil->ITICKU_GetElapsedTimeInNSec
	#define CHK_TICKU_GetElapsedTimeInNSec (pICmpCAATickUtil != NULL)
	#define EXP_TICKU_GetElapsedTimeInNSec  CAL_CMEXPAPI( "TICKU_GetElapsedTimeInNSec" ) 
#else /* DYNAMIC_LINK */
	#define USE_TICKU_GetElapsedTimeInNSec  PFTICKU_GETELAPSEDTIMEINNSEC pfTICKU_GetElapsedTimeInNSec;
	#define EXT_TICKU_GetElapsedTimeInNSec  extern PFTICKU_GETELAPSEDTIMEINNSEC pfTICKU_GetElapsedTimeInNSec;
	#define GET_TICKU_GetElapsedTimeInNSec(fl)  s_pfCMGetAPI2( "TICKU_GetElapsedTimeInNSec", (RTS_VOID_FCTPTR *)&pfTICKU_GetElapsedTimeInNSec, (fl), 0, 0)
	#define CAL_TICKU_GetElapsedTimeInNSec  pfTICKU_GetElapsedTimeInNSec
	#define CHK_TICKU_GetElapsedTimeInNSec  (pfTICKU_GetElapsedTimeInNSec != NULL)
	#define EXP_TICKU_GetElapsedTimeInNSec  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TICKU_GetElapsedTimeInNSec", (RTS_UINTPTR)TICKU_GetElapsedTimeInNSec, 0, 0) 
#endif



RTS_UI32 CDECL TICKU_GetElapsedTimeInUSec(CAA_TICK tkStart);
typedef RTS_UI32 (CDECL * PFTICKU_GETELAPSEDTIMEINUSEC) (CAA_TICK tkStart);
#if defined(CMPCAATICKUTIL_NOTIMPLEMENTED) || defined(TICKU_GETELAPSEDTIMEINUSEC_NOTIMPLEMENTED)
	#define USE_TICKU_GetElapsedTimeInUSec
	#define EXT_TICKU_GetElapsedTimeInUSec
	#define GET_TICKU_GetElapsedTimeInUSec(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TICKU_GetElapsedTimeInUSec(p0)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_TICKU_GetElapsedTimeInUSec  FALSE
	#define EXP_TICKU_GetElapsedTimeInUSec  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TICKU_GetElapsedTimeInUSec
	#define EXT_TICKU_GetElapsedTimeInUSec
	#define GET_TICKU_GetElapsedTimeInUSec(fl)  CAL_CMGETAPI( "TICKU_GetElapsedTimeInUSec" ) 
	#define CAL_TICKU_GetElapsedTimeInUSec  TICKU_GetElapsedTimeInUSec
	#define CHK_TICKU_GetElapsedTimeInUSec  TRUE
	#define EXP_TICKU_GetElapsedTimeInUSec  CAL_CMEXPAPI( "TICKU_GetElapsedTimeInUSec" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAATICKUTIL_EXTERNAL)
	#define USE_TICKU_GetElapsedTimeInUSec
	#define EXT_TICKU_GetElapsedTimeInUSec
	#define GET_TICKU_GetElapsedTimeInUSec(fl)  CAL_CMGETAPI( "TICKU_GetElapsedTimeInUSec" ) 
	#define CAL_TICKU_GetElapsedTimeInUSec  TICKU_GetElapsedTimeInUSec
	#define CHK_TICKU_GetElapsedTimeInUSec  TRUE
	#define EXP_TICKU_GetElapsedTimeInUSec  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TICKU_GetElapsedTimeInUSec", (RTS_UINTPTR)TICKU_GetElapsedTimeInUSec, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATickUtilTICKU_GetElapsedTimeInUSec
	#define EXT_CmpCAATickUtilTICKU_GetElapsedTimeInUSec
	#define GET_CmpCAATickUtilTICKU_GetElapsedTimeInUSec  ERR_OK
	#define CAL_CmpCAATickUtilTICKU_GetElapsedTimeInUSec pICmpCAATickUtil->ITICKU_GetElapsedTimeInUSec
	#define CHK_CmpCAATickUtilTICKU_GetElapsedTimeInUSec (pICmpCAATickUtil != NULL)
	#define EXP_CmpCAATickUtilTICKU_GetElapsedTimeInUSec  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TICKU_GetElapsedTimeInUSec
	#define EXT_TICKU_GetElapsedTimeInUSec
	#define GET_TICKU_GetElapsedTimeInUSec(fl)  CAL_CMGETAPI( "TICKU_GetElapsedTimeInUSec" ) 
	#define CAL_TICKU_GetElapsedTimeInUSec pICmpCAATickUtil->ITICKU_GetElapsedTimeInUSec
	#define CHK_TICKU_GetElapsedTimeInUSec (pICmpCAATickUtil != NULL)
	#define EXP_TICKU_GetElapsedTimeInUSec  CAL_CMEXPAPI( "TICKU_GetElapsedTimeInUSec" ) 
#else /* DYNAMIC_LINK */
	#define USE_TICKU_GetElapsedTimeInUSec  PFTICKU_GETELAPSEDTIMEINUSEC pfTICKU_GetElapsedTimeInUSec;
	#define EXT_TICKU_GetElapsedTimeInUSec  extern PFTICKU_GETELAPSEDTIMEINUSEC pfTICKU_GetElapsedTimeInUSec;
	#define GET_TICKU_GetElapsedTimeInUSec(fl)  s_pfCMGetAPI2( "TICKU_GetElapsedTimeInUSec", (RTS_VOID_FCTPTR *)&pfTICKU_GetElapsedTimeInUSec, (fl), 0, 0)
	#define CAL_TICKU_GetElapsedTimeInUSec  pfTICKU_GetElapsedTimeInUSec
	#define CHK_TICKU_GetElapsedTimeInUSec  (pfTICKU_GetElapsedTimeInUSec != NULL)
	#define EXP_TICKU_GetElapsedTimeInUSec  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TICKU_GetElapsedTimeInUSec", (RTS_UINTPTR)TICKU_GetElapsedTimeInUSec, 0, 0) 
#endif



unsigned short CDECL TICKU_GetSupplierVersion(CAA_BOOL xDummy);
typedef unsigned short (CDECL * PFTICKU_GETSUPPLIERVERSION) (CAA_BOOL xDummy);
#if defined(CMPCAATICKUTIL_NOTIMPLEMENTED) || defined(TICKU_GETSUPPLIERVERSION_NOTIMPLEMENTED)
	#define USE_TICKU_GetSupplierVersion
	#define EXT_TICKU_GetSupplierVersion
	#define GET_TICKU_GetSupplierVersion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TICKU_GetSupplierVersion(p0)  (unsigned short)ERR_NOTIMPLEMENTED
	#define CHK_TICKU_GetSupplierVersion  FALSE
	#define EXP_TICKU_GetSupplierVersion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TICKU_GetSupplierVersion
	#define EXT_TICKU_GetSupplierVersion
	#define GET_TICKU_GetSupplierVersion(fl)  CAL_CMGETAPI( "TICKU_GetSupplierVersion" ) 
	#define CAL_TICKU_GetSupplierVersion  TICKU_GetSupplierVersion
	#define CHK_TICKU_GetSupplierVersion  TRUE
	#define EXP_TICKU_GetSupplierVersion  CAL_CMEXPAPI( "TICKU_GetSupplierVersion" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAATICKUTIL_EXTERNAL)
	#define USE_TICKU_GetSupplierVersion
	#define EXT_TICKU_GetSupplierVersion
	#define GET_TICKU_GetSupplierVersion(fl)  CAL_CMGETAPI( "TICKU_GetSupplierVersion" ) 
	#define CAL_TICKU_GetSupplierVersion  TICKU_GetSupplierVersion
	#define CHK_TICKU_GetSupplierVersion  TRUE
	#define EXP_TICKU_GetSupplierVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TICKU_GetSupplierVersion", (RTS_UINTPTR)TICKU_GetSupplierVersion, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATickUtilTICKU_GetSupplierVersion
	#define EXT_CmpCAATickUtilTICKU_GetSupplierVersion
	#define GET_CmpCAATickUtilTICKU_GetSupplierVersion  ERR_OK
	#define CAL_CmpCAATickUtilTICKU_GetSupplierVersion pICmpCAATickUtil->ITICKU_GetSupplierVersion
	#define CHK_CmpCAATickUtilTICKU_GetSupplierVersion (pICmpCAATickUtil != NULL)
	#define EXP_CmpCAATickUtilTICKU_GetSupplierVersion  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TICKU_GetSupplierVersion
	#define EXT_TICKU_GetSupplierVersion
	#define GET_TICKU_GetSupplierVersion(fl)  CAL_CMGETAPI( "TICKU_GetSupplierVersion" ) 
	#define CAL_TICKU_GetSupplierVersion pICmpCAATickUtil->ITICKU_GetSupplierVersion
	#define CHK_TICKU_GetSupplierVersion (pICmpCAATickUtil != NULL)
	#define EXP_TICKU_GetSupplierVersion  CAL_CMEXPAPI( "TICKU_GetSupplierVersion" ) 
#else /* DYNAMIC_LINK */
	#define USE_TICKU_GetSupplierVersion  PFTICKU_GETSUPPLIERVERSION pfTICKU_GetSupplierVersion;
	#define EXT_TICKU_GetSupplierVersion  extern PFTICKU_GETSUPPLIERVERSION pfTICKU_GetSupplierVersion;
	#define GET_TICKU_GetSupplierVersion(fl)  s_pfCMGetAPI2( "TICKU_GetSupplierVersion", (RTS_VOID_FCTPTR *)&pfTICKU_GetSupplierVersion, (fl), 0, 0)
	#define CAL_TICKU_GetSupplierVersion  pfTICKU_GetSupplierVersion
	#define CHK_TICKU_GetSupplierVersion  (pfTICKU_GetSupplierVersion != NULL)
	#define EXP_TICKU_GetSupplierVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TICKU_GetSupplierVersion", (RTS_UINTPTR)TICKU_GetSupplierVersion, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif


/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>ticku_convertnsectotick</description>
 */
typedef struct tagticku_convertnsectotick_struct
{
	RTS_IEC_UDINT udiNSeconds;			/* VAR_INPUT */	
	CAA_TICK TICKU_ConvertNSecToTick;	/* VAR_OUTPUT */	
} ticku_convertnsectotick_struct;

void CDECL CDECL_EXT ticku_convertnsectotick(ticku_convertnsectotick_struct *p);
typedef void (CDECL CDECL_EXT* PFTICKU_CONVERTNSECTOTICK_IEC) (ticku_convertnsectotick_struct *p);
#if defined(CMPCAATICKUTIL_NOTIMPLEMENTED) || defined(TICKU_CONVERTNSECTOTICK_NOTIMPLEMENTED)
	#define USE_ticku_convertnsectotick
	#define EXT_ticku_convertnsectotick
	#define GET_ticku_convertnsectotick(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ticku_convertnsectotick(p0) 
	#define CHK_ticku_convertnsectotick  FALSE
	#define EXP_ticku_convertnsectotick  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ticku_convertnsectotick
	#define EXT_ticku_convertnsectotick
	#define GET_ticku_convertnsectotick(fl)  CAL_CMGETAPI( "ticku_convertnsectotick" ) 
	#define CAL_ticku_convertnsectotick  ticku_convertnsectotick
	#define CHK_ticku_convertnsectotick  TRUE
	#define EXP_ticku_convertnsectotick  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_convertnsectotick", (RTS_UINTPTR)ticku_convertnsectotick, 1, RTSITF_GET_SIGNATURE(0, 0xCE69B11B), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAATICKUTIL_EXTERNAL)
	#define USE_ticku_convertnsectotick
	#define EXT_ticku_convertnsectotick
	#define GET_ticku_convertnsectotick(fl)  CAL_CMGETAPI( "ticku_convertnsectotick" ) 
	#define CAL_ticku_convertnsectotick  ticku_convertnsectotick
	#define CHK_ticku_convertnsectotick  TRUE
	#define EXP_ticku_convertnsectotick  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_convertnsectotick", (RTS_UINTPTR)ticku_convertnsectotick, 1, RTSITF_GET_SIGNATURE(0, 0xCE69B11B), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATickUtilticku_convertnsectotick
	#define EXT_CmpCAATickUtilticku_convertnsectotick
	#define GET_CmpCAATickUtilticku_convertnsectotick  ERR_OK
	#define CAL_CmpCAATickUtilticku_convertnsectotick  ticku_convertnsectotick
	#define CHK_CmpCAATickUtilticku_convertnsectotick  TRUE
	#define EXP_CmpCAATickUtilticku_convertnsectotick  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_convertnsectotick", (RTS_UINTPTR)ticku_convertnsectotick, 1, RTSITF_GET_SIGNATURE(0, 0xCE69B11B), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_ticku_convertnsectotick
	#define EXT_ticku_convertnsectotick
	#define GET_ticku_convertnsectotick(fl)  CAL_CMGETAPI( "ticku_convertnsectotick" ) 
	#define CAL_ticku_convertnsectotick  ticku_convertnsectotick
	#define CHK_ticku_convertnsectotick  TRUE
	#define EXP_ticku_convertnsectotick  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_convertnsectotick", (RTS_UINTPTR)ticku_convertnsectotick, 1, RTSITF_GET_SIGNATURE(0, 0xCE69B11B), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_ticku_convertnsectotick  PFTICKU_CONVERTNSECTOTICK_IEC pfticku_convertnsectotick;
	#define EXT_ticku_convertnsectotick  extern PFTICKU_CONVERTNSECTOTICK_IEC pfticku_convertnsectotick;
	#define GET_ticku_convertnsectotick(fl)  s_pfCMGetAPI2( "ticku_convertnsectotick", (RTS_VOID_FCTPTR *)&pfticku_convertnsectotick, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xCE69B11B), 0x03050500)
	#define CAL_ticku_convertnsectotick  pfticku_convertnsectotick
	#define CHK_ticku_convertnsectotick  (pfticku_convertnsectotick != NULL)
	#define EXP_ticku_convertnsectotick   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_convertnsectotick", (RTS_UINTPTR)ticku_convertnsectotick, 1, RTSITF_GET_SIGNATURE(0, 0xCE69B11B), 0x03050500) 
#endif


/**
 * <description>ticku_convertticktonsec</description>
 */
typedef struct tagticku_convertticktonsec_struct
{
	CAA_TICK tkTick;					/* VAR_INPUT */	
	RTS_IEC_UDINT TICKU_ConvertTickToNSec;	/* VAR_OUTPUT */	
} ticku_convertticktonsec_struct;

void CDECL CDECL_EXT ticku_convertticktonsec(ticku_convertticktonsec_struct *p);
typedef void (CDECL CDECL_EXT* PFTICKU_CONVERTTICKTONSEC_IEC) (ticku_convertticktonsec_struct *p);
#if defined(CMPCAATICKUTIL_NOTIMPLEMENTED) || defined(TICKU_CONVERTTICKTONSEC_NOTIMPLEMENTED)
	#define USE_ticku_convertticktonsec
	#define EXT_ticku_convertticktonsec
	#define GET_ticku_convertticktonsec(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ticku_convertticktonsec(p0) 
	#define CHK_ticku_convertticktonsec  FALSE
	#define EXP_ticku_convertticktonsec  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ticku_convertticktonsec
	#define EXT_ticku_convertticktonsec
	#define GET_ticku_convertticktonsec(fl)  CAL_CMGETAPI( "ticku_convertticktonsec" ) 
	#define CAL_ticku_convertticktonsec  ticku_convertticktonsec
	#define CHK_ticku_convertticktonsec  TRUE
	#define EXP_ticku_convertticktonsec  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_convertticktonsec", (RTS_UINTPTR)ticku_convertticktonsec, 1, RTSITF_GET_SIGNATURE(0, 0x1163A81F), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAATICKUTIL_EXTERNAL)
	#define USE_ticku_convertticktonsec
	#define EXT_ticku_convertticktonsec
	#define GET_ticku_convertticktonsec(fl)  CAL_CMGETAPI( "ticku_convertticktonsec" ) 
	#define CAL_ticku_convertticktonsec  ticku_convertticktonsec
	#define CHK_ticku_convertticktonsec  TRUE
	#define EXP_ticku_convertticktonsec  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_convertticktonsec", (RTS_UINTPTR)ticku_convertticktonsec, 1, RTSITF_GET_SIGNATURE(0, 0x1163A81F), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATickUtilticku_convertticktonsec
	#define EXT_CmpCAATickUtilticku_convertticktonsec
	#define GET_CmpCAATickUtilticku_convertticktonsec  ERR_OK
	#define CAL_CmpCAATickUtilticku_convertticktonsec  ticku_convertticktonsec
	#define CHK_CmpCAATickUtilticku_convertticktonsec  TRUE
	#define EXP_CmpCAATickUtilticku_convertticktonsec  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_convertticktonsec", (RTS_UINTPTR)ticku_convertticktonsec, 1, RTSITF_GET_SIGNATURE(0, 0x1163A81F), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_ticku_convertticktonsec
	#define EXT_ticku_convertticktonsec
	#define GET_ticku_convertticktonsec(fl)  CAL_CMGETAPI( "ticku_convertticktonsec" ) 
	#define CAL_ticku_convertticktonsec  ticku_convertticktonsec
	#define CHK_ticku_convertticktonsec  TRUE
	#define EXP_ticku_convertticktonsec  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_convertticktonsec", (RTS_UINTPTR)ticku_convertticktonsec, 1, RTSITF_GET_SIGNATURE(0, 0x1163A81F), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_ticku_convertticktonsec  PFTICKU_CONVERTTICKTONSEC_IEC pfticku_convertticktonsec;
	#define EXT_ticku_convertticktonsec  extern PFTICKU_CONVERTTICKTONSEC_IEC pfticku_convertticktonsec;
	#define GET_ticku_convertticktonsec(fl)  s_pfCMGetAPI2( "ticku_convertticktonsec", (RTS_VOID_FCTPTR *)&pfticku_convertticktonsec, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x1163A81F), 0x03050500)
	#define CAL_ticku_convertticktonsec  pfticku_convertticktonsec
	#define CHK_ticku_convertticktonsec  (pfticku_convertticktonsec != NULL)
	#define EXP_ticku_convertticktonsec   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_convertticktonsec", (RTS_UINTPTR)ticku_convertticktonsec, 1, RTSITF_GET_SIGNATURE(0, 0x1163A81F), 0x03050500) 
#endif


/**
 * <description>ticku_convertticktousec</description>
 */
typedef struct tagticku_convertticktousec_struct
{
	CAA_TICK tkTick;					/* VAR_INPUT */	
	RTS_IEC_UDINT TICKU_ConvertTickToUSec;	/* VAR_OUTPUT */	
} ticku_convertticktousec_struct;

void CDECL CDECL_EXT ticku_convertticktousec(ticku_convertticktousec_struct *p);
typedef void (CDECL CDECL_EXT* PFTICKU_CONVERTTICKTOUSEC_IEC) (ticku_convertticktousec_struct *p);
#if defined(CMPCAATICKUTIL_NOTIMPLEMENTED) || defined(TICKU_CONVERTTICKTOUSEC_NOTIMPLEMENTED)
	#define USE_ticku_convertticktousec
	#define EXT_ticku_convertticktousec
	#define GET_ticku_convertticktousec(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ticku_convertticktousec(p0) 
	#define CHK_ticku_convertticktousec  FALSE
	#define EXP_ticku_convertticktousec  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ticku_convertticktousec
	#define EXT_ticku_convertticktousec
	#define GET_ticku_convertticktousec(fl)  CAL_CMGETAPI( "ticku_convertticktousec" ) 
	#define CAL_ticku_convertticktousec  ticku_convertticktousec
	#define CHK_ticku_convertticktousec  TRUE
	#define EXP_ticku_convertticktousec  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_convertticktousec", (RTS_UINTPTR)ticku_convertticktousec, 1, RTSITF_GET_SIGNATURE(0, 0x89370F4E), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAATICKUTIL_EXTERNAL)
	#define USE_ticku_convertticktousec
	#define EXT_ticku_convertticktousec
	#define GET_ticku_convertticktousec(fl)  CAL_CMGETAPI( "ticku_convertticktousec" ) 
	#define CAL_ticku_convertticktousec  ticku_convertticktousec
	#define CHK_ticku_convertticktousec  TRUE
	#define EXP_ticku_convertticktousec  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_convertticktousec", (RTS_UINTPTR)ticku_convertticktousec, 1, RTSITF_GET_SIGNATURE(0, 0x89370F4E), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATickUtilticku_convertticktousec
	#define EXT_CmpCAATickUtilticku_convertticktousec
	#define GET_CmpCAATickUtilticku_convertticktousec  ERR_OK
	#define CAL_CmpCAATickUtilticku_convertticktousec  ticku_convertticktousec
	#define CHK_CmpCAATickUtilticku_convertticktousec  TRUE
	#define EXP_CmpCAATickUtilticku_convertticktousec  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_convertticktousec", (RTS_UINTPTR)ticku_convertticktousec, 1, RTSITF_GET_SIGNATURE(0, 0x89370F4E), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_ticku_convertticktousec
	#define EXT_ticku_convertticktousec
	#define GET_ticku_convertticktousec(fl)  CAL_CMGETAPI( "ticku_convertticktousec" ) 
	#define CAL_ticku_convertticktousec  ticku_convertticktousec
	#define CHK_ticku_convertticktousec  TRUE
	#define EXP_ticku_convertticktousec  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_convertticktousec", (RTS_UINTPTR)ticku_convertticktousec, 1, RTSITF_GET_SIGNATURE(0, 0x89370F4E), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_ticku_convertticktousec  PFTICKU_CONVERTTICKTOUSEC_IEC pfticku_convertticktousec;
	#define EXT_ticku_convertticktousec  extern PFTICKU_CONVERTTICKTOUSEC_IEC pfticku_convertticktousec;
	#define GET_ticku_convertticktousec(fl)  s_pfCMGetAPI2( "ticku_convertticktousec", (RTS_VOID_FCTPTR *)&pfticku_convertticktousec, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x89370F4E), 0x03050500)
	#define CAL_ticku_convertticktousec  pfticku_convertticktousec
	#define CHK_ticku_convertticktousec  (pfticku_convertticktousec != NULL)
	#define EXP_ticku_convertticktousec   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_convertticktousec", (RTS_UINTPTR)ticku_convertticktousec, 1, RTSITF_GET_SIGNATURE(0, 0x89370F4E), 0x03050500) 
#endif


/**
 * <description>ticku_convertusectotick</description>
 */
typedef struct tagticku_convertusectotick_struct
{
	RTS_IEC_UDINT udiUSeconds;			/* VAR_INPUT */	
	CAA_TICK TICKU_ConvertUSecToTick;	/* VAR_OUTPUT */	
} ticku_convertusectotick_struct;

void CDECL CDECL_EXT ticku_convertusectotick(ticku_convertusectotick_struct *p);
typedef void (CDECL CDECL_EXT* PFTICKU_CONVERTUSECTOTICK_IEC) (ticku_convertusectotick_struct *p);
#if defined(CMPCAATICKUTIL_NOTIMPLEMENTED) || defined(TICKU_CONVERTUSECTOTICK_NOTIMPLEMENTED)
	#define USE_ticku_convertusectotick
	#define EXT_ticku_convertusectotick
	#define GET_ticku_convertusectotick(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ticku_convertusectotick(p0) 
	#define CHK_ticku_convertusectotick  FALSE
	#define EXP_ticku_convertusectotick  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ticku_convertusectotick
	#define EXT_ticku_convertusectotick
	#define GET_ticku_convertusectotick(fl)  CAL_CMGETAPI( "ticku_convertusectotick" ) 
	#define CAL_ticku_convertusectotick  ticku_convertusectotick
	#define CHK_ticku_convertusectotick  TRUE
	#define EXP_ticku_convertusectotick  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_convertusectotick", (RTS_UINTPTR)ticku_convertusectotick, 1, RTSITF_GET_SIGNATURE(0, 0xEF322DA4), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAATICKUTIL_EXTERNAL)
	#define USE_ticku_convertusectotick
	#define EXT_ticku_convertusectotick
	#define GET_ticku_convertusectotick(fl)  CAL_CMGETAPI( "ticku_convertusectotick" ) 
	#define CAL_ticku_convertusectotick  ticku_convertusectotick
	#define CHK_ticku_convertusectotick  TRUE
	#define EXP_ticku_convertusectotick  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_convertusectotick", (RTS_UINTPTR)ticku_convertusectotick, 1, RTSITF_GET_SIGNATURE(0, 0xEF322DA4), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATickUtilticku_convertusectotick
	#define EXT_CmpCAATickUtilticku_convertusectotick
	#define GET_CmpCAATickUtilticku_convertusectotick  ERR_OK
	#define CAL_CmpCAATickUtilticku_convertusectotick  ticku_convertusectotick
	#define CHK_CmpCAATickUtilticku_convertusectotick  TRUE
	#define EXP_CmpCAATickUtilticku_convertusectotick  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_convertusectotick", (RTS_UINTPTR)ticku_convertusectotick, 1, RTSITF_GET_SIGNATURE(0, 0xEF322DA4), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_ticku_convertusectotick
	#define EXT_ticku_convertusectotick
	#define GET_ticku_convertusectotick(fl)  CAL_CMGETAPI( "ticku_convertusectotick" ) 
	#define CAL_ticku_convertusectotick  ticku_convertusectotick
	#define CHK_ticku_convertusectotick  TRUE
	#define EXP_ticku_convertusectotick  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_convertusectotick", (RTS_UINTPTR)ticku_convertusectotick, 1, RTSITF_GET_SIGNATURE(0, 0xEF322DA4), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_ticku_convertusectotick  PFTICKU_CONVERTUSECTOTICK_IEC pfticku_convertusectotick;
	#define EXT_ticku_convertusectotick  extern PFTICKU_CONVERTUSECTOTICK_IEC pfticku_convertusectotick;
	#define GET_ticku_convertusectotick(fl)  s_pfCMGetAPI2( "ticku_convertusectotick", (RTS_VOID_FCTPTR *)&pfticku_convertusectotick, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xEF322DA4), 0x03050500)
	#define CAL_ticku_convertusectotick  pfticku_convertusectotick
	#define CHK_ticku_convertusectotick  (pfticku_convertusectotick != NULL)
	#define EXP_ticku_convertusectotick   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_convertusectotick", (RTS_UINTPTR)ticku_convertusectotick, 1, RTSITF_GET_SIGNATURE(0, 0xEF322DA4), 0x03050500) 
#endif


/**
 * <description>ticku_getelapsedtimeinnsec</description>
 */
typedef struct tagticku_getelapsedtimeinnsec_struct
{
	CAA_TICK tkStart;					/* VAR_INPUT */	
	RTS_IEC_UDINT TICKU_GetElapsedTimeInNSec;	/* VAR_OUTPUT */	
} ticku_getelapsedtimeinnsec_struct;

void CDECL CDECL_EXT ticku_getelapsedtimeinnsec(ticku_getelapsedtimeinnsec_struct *p);
typedef void (CDECL CDECL_EXT* PFTICKU_GETELAPSEDTIMEINNSEC_IEC) (ticku_getelapsedtimeinnsec_struct *p);
#if defined(CMPCAATICKUTIL_NOTIMPLEMENTED) || defined(TICKU_GETELAPSEDTIMEINNSEC_NOTIMPLEMENTED)
	#define USE_ticku_getelapsedtimeinnsec
	#define EXT_ticku_getelapsedtimeinnsec
	#define GET_ticku_getelapsedtimeinnsec(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ticku_getelapsedtimeinnsec(p0) 
	#define CHK_ticku_getelapsedtimeinnsec  FALSE
	#define EXP_ticku_getelapsedtimeinnsec  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ticku_getelapsedtimeinnsec
	#define EXT_ticku_getelapsedtimeinnsec
	#define GET_ticku_getelapsedtimeinnsec(fl)  CAL_CMGETAPI( "ticku_getelapsedtimeinnsec" ) 
	#define CAL_ticku_getelapsedtimeinnsec  ticku_getelapsedtimeinnsec
	#define CHK_ticku_getelapsedtimeinnsec  TRUE
	#define EXP_ticku_getelapsedtimeinnsec  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_getelapsedtimeinnsec", (RTS_UINTPTR)ticku_getelapsedtimeinnsec, 1, RTSITF_GET_SIGNATURE(0, 0xF18913FC), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAATICKUTIL_EXTERNAL)
	#define USE_ticku_getelapsedtimeinnsec
	#define EXT_ticku_getelapsedtimeinnsec
	#define GET_ticku_getelapsedtimeinnsec(fl)  CAL_CMGETAPI( "ticku_getelapsedtimeinnsec" ) 
	#define CAL_ticku_getelapsedtimeinnsec  ticku_getelapsedtimeinnsec
	#define CHK_ticku_getelapsedtimeinnsec  TRUE
	#define EXP_ticku_getelapsedtimeinnsec  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_getelapsedtimeinnsec", (RTS_UINTPTR)ticku_getelapsedtimeinnsec, 1, RTSITF_GET_SIGNATURE(0, 0xF18913FC), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATickUtilticku_getelapsedtimeinnsec
	#define EXT_CmpCAATickUtilticku_getelapsedtimeinnsec
	#define GET_CmpCAATickUtilticku_getelapsedtimeinnsec  ERR_OK
	#define CAL_CmpCAATickUtilticku_getelapsedtimeinnsec  ticku_getelapsedtimeinnsec
	#define CHK_CmpCAATickUtilticku_getelapsedtimeinnsec  TRUE
	#define EXP_CmpCAATickUtilticku_getelapsedtimeinnsec  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_getelapsedtimeinnsec", (RTS_UINTPTR)ticku_getelapsedtimeinnsec, 1, RTSITF_GET_SIGNATURE(0, 0xF18913FC), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_ticku_getelapsedtimeinnsec
	#define EXT_ticku_getelapsedtimeinnsec
	#define GET_ticku_getelapsedtimeinnsec(fl)  CAL_CMGETAPI( "ticku_getelapsedtimeinnsec" ) 
	#define CAL_ticku_getelapsedtimeinnsec  ticku_getelapsedtimeinnsec
	#define CHK_ticku_getelapsedtimeinnsec  TRUE
	#define EXP_ticku_getelapsedtimeinnsec  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_getelapsedtimeinnsec", (RTS_UINTPTR)ticku_getelapsedtimeinnsec, 1, RTSITF_GET_SIGNATURE(0, 0xF18913FC), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_ticku_getelapsedtimeinnsec  PFTICKU_GETELAPSEDTIMEINNSEC_IEC pfticku_getelapsedtimeinnsec;
	#define EXT_ticku_getelapsedtimeinnsec  extern PFTICKU_GETELAPSEDTIMEINNSEC_IEC pfticku_getelapsedtimeinnsec;
	#define GET_ticku_getelapsedtimeinnsec(fl)  s_pfCMGetAPI2( "ticku_getelapsedtimeinnsec", (RTS_VOID_FCTPTR *)&pfticku_getelapsedtimeinnsec, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xF18913FC), 0x03050500)
	#define CAL_ticku_getelapsedtimeinnsec  pfticku_getelapsedtimeinnsec
	#define CHK_ticku_getelapsedtimeinnsec  (pfticku_getelapsedtimeinnsec != NULL)
	#define EXP_ticku_getelapsedtimeinnsec   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_getelapsedtimeinnsec", (RTS_UINTPTR)ticku_getelapsedtimeinnsec, 1, RTSITF_GET_SIGNATURE(0, 0xF18913FC), 0x03050500) 
#endif


/**
 * <description>ticku_getelapsedtimeinusec</description>
 */
typedef struct tagticku_getelapsedtimeinusec_struct
{
	CAA_TICK tkStart;					/* VAR_INPUT */	
	RTS_IEC_UDINT TICKU_GetElapsedTimeInUSec;	/* VAR_OUTPUT */	
} ticku_getelapsedtimeinusec_struct;

void CDECL CDECL_EXT ticku_getelapsedtimeinusec(ticku_getelapsedtimeinusec_struct *p);
typedef void (CDECL CDECL_EXT* PFTICKU_GETELAPSEDTIMEINUSEC_IEC) (ticku_getelapsedtimeinusec_struct *p);
#if defined(CMPCAATICKUTIL_NOTIMPLEMENTED) || defined(TICKU_GETELAPSEDTIMEINUSEC_NOTIMPLEMENTED)
	#define USE_ticku_getelapsedtimeinusec
	#define EXT_ticku_getelapsedtimeinusec
	#define GET_ticku_getelapsedtimeinusec(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ticku_getelapsedtimeinusec(p0) 
	#define CHK_ticku_getelapsedtimeinusec  FALSE
	#define EXP_ticku_getelapsedtimeinusec  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ticku_getelapsedtimeinusec
	#define EXT_ticku_getelapsedtimeinusec
	#define GET_ticku_getelapsedtimeinusec(fl)  CAL_CMGETAPI( "ticku_getelapsedtimeinusec" ) 
	#define CAL_ticku_getelapsedtimeinusec  ticku_getelapsedtimeinusec
	#define CHK_ticku_getelapsedtimeinusec  TRUE
	#define EXP_ticku_getelapsedtimeinusec  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_getelapsedtimeinusec", (RTS_UINTPTR)ticku_getelapsedtimeinusec, 1, RTSITF_GET_SIGNATURE(0, 0xC903347A), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAATICKUTIL_EXTERNAL)
	#define USE_ticku_getelapsedtimeinusec
	#define EXT_ticku_getelapsedtimeinusec
	#define GET_ticku_getelapsedtimeinusec(fl)  CAL_CMGETAPI( "ticku_getelapsedtimeinusec" ) 
	#define CAL_ticku_getelapsedtimeinusec  ticku_getelapsedtimeinusec
	#define CHK_ticku_getelapsedtimeinusec  TRUE
	#define EXP_ticku_getelapsedtimeinusec  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_getelapsedtimeinusec", (RTS_UINTPTR)ticku_getelapsedtimeinusec, 1, RTSITF_GET_SIGNATURE(0, 0xC903347A), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATickUtilticku_getelapsedtimeinusec
	#define EXT_CmpCAATickUtilticku_getelapsedtimeinusec
	#define GET_CmpCAATickUtilticku_getelapsedtimeinusec  ERR_OK
	#define CAL_CmpCAATickUtilticku_getelapsedtimeinusec  ticku_getelapsedtimeinusec
	#define CHK_CmpCAATickUtilticku_getelapsedtimeinusec  TRUE
	#define EXP_CmpCAATickUtilticku_getelapsedtimeinusec  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_getelapsedtimeinusec", (RTS_UINTPTR)ticku_getelapsedtimeinusec, 1, RTSITF_GET_SIGNATURE(0, 0xC903347A), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_ticku_getelapsedtimeinusec
	#define EXT_ticku_getelapsedtimeinusec
	#define GET_ticku_getelapsedtimeinusec(fl)  CAL_CMGETAPI( "ticku_getelapsedtimeinusec" ) 
	#define CAL_ticku_getelapsedtimeinusec  ticku_getelapsedtimeinusec
	#define CHK_ticku_getelapsedtimeinusec  TRUE
	#define EXP_ticku_getelapsedtimeinusec  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_getelapsedtimeinusec", (RTS_UINTPTR)ticku_getelapsedtimeinusec, 1, RTSITF_GET_SIGNATURE(0, 0xC903347A), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_ticku_getelapsedtimeinusec  PFTICKU_GETELAPSEDTIMEINUSEC_IEC pfticku_getelapsedtimeinusec;
	#define EXT_ticku_getelapsedtimeinusec  extern PFTICKU_GETELAPSEDTIMEINUSEC_IEC pfticku_getelapsedtimeinusec;
	#define GET_ticku_getelapsedtimeinusec(fl)  s_pfCMGetAPI2( "ticku_getelapsedtimeinusec", (RTS_VOID_FCTPTR *)&pfticku_getelapsedtimeinusec, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xC903347A), 0x03050500)
	#define CAL_ticku_getelapsedtimeinusec  pfticku_getelapsedtimeinusec
	#define CHK_ticku_getelapsedtimeinusec  (pfticku_getelapsedtimeinusec != NULL)
	#define EXP_ticku_getelapsedtimeinusec   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_getelapsedtimeinusec", (RTS_UINTPTR)ticku_getelapsedtimeinusec, 1, RTSITF_GET_SIGNATURE(0, 0xC903347A), 0x03050500) 
#endif


/**
 * <description>ticku_getsupplierversion</description>
 */
typedef struct tagticku_getsupplierversion_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	RTS_IEC_WORD TICKU_GetSupplierVersion;	/* VAR_OUTPUT */	
} ticku_getsupplierversion_struct;

void CDECL CDECL_EXT ticku_getsupplierversion(ticku_getsupplierversion_struct *p);
typedef void (CDECL CDECL_EXT* PFTICKU_GETSUPPLIERVERSION_IEC) (ticku_getsupplierversion_struct *p);
#if defined(CMPCAATICKUTIL_NOTIMPLEMENTED) || defined(TICKU_GETSUPPLIERVERSION_NOTIMPLEMENTED)
	#define USE_ticku_getsupplierversion
	#define EXT_ticku_getsupplierversion
	#define GET_ticku_getsupplierversion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ticku_getsupplierversion(p0) 
	#define CHK_ticku_getsupplierversion  FALSE
	#define EXP_ticku_getsupplierversion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ticku_getsupplierversion
	#define EXT_ticku_getsupplierversion
	#define GET_ticku_getsupplierversion(fl)  CAL_CMGETAPI( "ticku_getsupplierversion" ) 
	#define CAL_ticku_getsupplierversion  ticku_getsupplierversion
	#define CHK_ticku_getsupplierversion  TRUE
	#define EXP_ticku_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_getsupplierversion", (RTS_UINTPTR)ticku_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xA4D2E65F), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAATICKUTIL_EXTERNAL)
	#define USE_ticku_getsupplierversion
	#define EXT_ticku_getsupplierversion
	#define GET_ticku_getsupplierversion(fl)  CAL_CMGETAPI( "ticku_getsupplierversion" ) 
	#define CAL_ticku_getsupplierversion  ticku_getsupplierversion
	#define CHK_ticku_getsupplierversion  TRUE
	#define EXP_ticku_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_getsupplierversion", (RTS_UINTPTR)ticku_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xA4D2E65F), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATickUtilticku_getsupplierversion
	#define EXT_CmpCAATickUtilticku_getsupplierversion
	#define GET_CmpCAATickUtilticku_getsupplierversion  ERR_OK
	#define CAL_CmpCAATickUtilticku_getsupplierversion  ticku_getsupplierversion
	#define CHK_CmpCAATickUtilticku_getsupplierversion  TRUE
	#define EXP_CmpCAATickUtilticku_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_getsupplierversion", (RTS_UINTPTR)ticku_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xA4D2E65F), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_ticku_getsupplierversion
	#define EXT_ticku_getsupplierversion
	#define GET_ticku_getsupplierversion(fl)  CAL_CMGETAPI( "ticku_getsupplierversion" ) 
	#define CAL_ticku_getsupplierversion  ticku_getsupplierversion
	#define CHK_ticku_getsupplierversion  TRUE
	#define EXP_ticku_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_getsupplierversion", (RTS_UINTPTR)ticku_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xA4D2E65F), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_ticku_getsupplierversion  PFTICKU_GETSUPPLIERVERSION_IEC pfticku_getsupplierversion;
	#define EXT_ticku_getsupplierversion  extern PFTICKU_GETSUPPLIERVERSION_IEC pfticku_getsupplierversion;
	#define GET_ticku_getsupplierversion(fl)  s_pfCMGetAPI2( "ticku_getsupplierversion", (RTS_VOID_FCTPTR *)&pfticku_getsupplierversion, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xA4D2E65F), 0x03050500)
	#define CAL_ticku_getsupplierversion  pfticku_getsupplierversion
	#define CHK_ticku_getsupplierversion  (pfticku_getsupplierversion != NULL)
	#define EXP_ticku_getsupplierversion   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticku_getsupplierversion", (RTS_UINTPTR)ticku_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xA4D2E65F), 0x03050500) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/



typedef struct
{
	IBase_C *pBase;
	PFTICKU_CONVERTNSECTOTICK ITICKU_ConvertNSecToTick;
 	PFTICKU_CONVERTTICKTONSEC ITICKU_ConvertTickToNSec;
 	PFTICKU_CONVERTTICKTOUSEC ITICKU_ConvertTickToUSec;
 	PFTICKU_CONVERTUSECTOTICK ITICKU_ConvertUSecToTick;
 	PFTICKU_GETELAPSEDTIMEINNSEC ITICKU_GetElapsedTimeInNSec;
 	PFTICKU_GETELAPSEDTIMEINUSEC ITICKU_GetElapsedTimeInUSec;
 	PFTICKU_GETSUPPLIERVERSION ITICKU_GetSupplierVersion;
 } ICmpCAATickUtil_C;

#ifdef CPLUSPLUS
class ICmpCAATickUtil : public IBase
{
	public:
		virtual CAA_TICK CDECL ITICKU_ConvertNSecToTick(RTS_UI32 ulNSeconds) =0;
		virtual RTS_UI32 CDECL ITICKU_ConvertTickToNSec(CAA_TICK tkTick) =0;
		virtual RTS_UI32 CDECL ITICKU_ConvertTickToUSec(CAA_TICK tkTick) =0;
		virtual CAA_TICK CDECL ITICKU_ConvertUSecToTick(RTS_UI32 ulUSeconds) =0;
		virtual RTS_UI32 CDECL ITICKU_GetElapsedTimeInNSec(CAA_TICK tkStart) =0;
		virtual RTS_UI32 CDECL ITICKU_GetElapsedTimeInUSec(CAA_TICK tkStart) =0;
		virtual unsigned short CDECL ITICKU_GetSupplierVersion(CAA_BOOL xDummy) =0;
};
	#ifndef ITF_CmpCAATickUtil
		#define ITF_CmpCAATickUtil static ICmpCAATickUtil *pICmpCAATickUtil = NULL;
	#endif
	#define EXTITF_CmpCAATickUtil
#else	/*CPLUSPLUS*/
	typedef ICmpCAATickUtil_C		ICmpCAATickUtil;
	#ifndef ITF_CmpCAATickUtil
		#define ITF_CmpCAATickUtil
	#endif
	#define EXTITF_CmpCAATickUtil
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCAATICKUTILITF_H_*/
