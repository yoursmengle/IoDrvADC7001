 /**
 * <interfacename>CmpCAATick</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _CMPCAATICKITF_H_
#define _CMPCAATICKITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAATick.h"

#ifdef __cplusplus
extern "C" {
#endif

CAA_TICK CDECL TICKS_GetTick(CAA_BOOL xDummy);
typedef CAA_TICK (CDECL * PFTICKS_GETTICK) (CAA_BOOL xDummy);
#if defined(CMPCAATICK_NOTIMPLEMENTED) || defined(TICKS_GETTICK_NOTIMPLEMENTED)
	#define USE_TICKS_GetTick
	#define EXT_TICKS_GetTick
	#define GET_TICKS_GetTick(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TICKS_GetTick(p0)  (CAA_TICK)ERR_NOTIMPLEMENTED
	#define CHK_TICKS_GetTick  FALSE
	#define EXP_TICKS_GetTick  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TICKS_GetTick
	#define EXT_TICKS_GetTick
	#define GET_TICKS_GetTick(fl)  CAL_CMGETAPI( "TICKS_GetTick" ) 
	#define CAL_TICKS_GetTick  TICKS_GetTick
	#define CHK_TICKS_GetTick  TRUE
	#define EXP_TICKS_GetTick  CAL_CMEXPAPI( "TICKS_GetTick" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAATICK_EXTERNAL)
	#define USE_TICKS_GetTick
	#define EXT_TICKS_GetTick
	#define GET_TICKS_GetTick(fl)  CAL_CMGETAPI( "TICKS_GetTick" ) 
	#define CAL_TICKS_GetTick  TICKS_GetTick
	#define CHK_TICKS_GetTick  TRUE
	#define EXP_TICKS_GetTick  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TICKS_GetTick", (RTS_UINTPTR)TICKS_GetTick, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATickTICKS_GetTick
	#define EXT_CmpCAATickTICKS_GetTick
	#define GET_CmpCAATickTICKS_GetTick  ERR_OK
	#define CAL_CmpCAATickTICKS_GetTick pICmpCAATick->ITICKS_GetTick
	#define CHK_CmpCAATickTICKS_GetTick (pICmpCAATick != NULL)
	#define EXP_CmpCAATickTICKS_GetTick  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TICKS_GetTick
	#define EXT_TICKS_GetTick
	#define GET_TICKS_GetTick(fl)  CAL_CMGETAPI( "TICKS_GetTick" ) 
	#define CAL_TICKS_GetTick pICmpCAATick->ITICKS_GetTick
	#define CHK_TICKS_GetTick (pICmpCAATick != NULL)
	#define EXP_TICKS_GetTick  CAL_CMEXPAPI( "TICKS_GetTick" ) 
#else /* DYNAMIC_LINK */
	#define USE_TICKS_GetTick  PFTICKS_GETTICK pfTICKS_GetTick;
	#define EXT_TICKS_GetTick  extern PFTICKS_GETTICK pfTICKS_GetTick;
	#define GET_TICKS_GetTick(fl)  s_pfCMGetAPI2( "TICKS_GetTick", (RTS_VOID_FCTPTR *)&pfTICKS_GetTick, (fl), 0, 0)
	#define CAL_TICKS_GetTick  pfTICKS_GetTick
	#define CHK_TICKS_GetTick  (pfTICKS_GetTick != NULL)
	#define EXP_TICKS_GetTick  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TICKS_GetTick", (RTS_UINTPTR)TICKS_GetTick, 0, 0) 
#endif



RTS_IEC_XWORD CDECL TICKS_GetProperty(unsigned short usProperty);
typedef RTS_IEC_XWORD (CDECL * PFTICKS_GETPROPERTY) (unsigned short usProperty);
#if defined(CMPCAATICK_NOTIMPLEMENTED) || defined(TICKS_GETPROPERTY_NOTIMPLEMENTED)
	#define USE_TICKS_GetProperty
	#define EXT_TICKS_GetProperty
	#define GET_TICKS_GetProperty(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TICKS_GetProperty(p0)  (RTS_IEC_XWORD)ERR_NOTIMPLEMENTED
	#define CHK_TICKS_GetProperty  FALSE
	#define EXP_TICKS_GetProperty  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TICKS_GetProperty
	#define EXT_TICKS_GetProperty
	#define GET_TICKS_GetProperty(fl)  CAL_CMGETAPI( "TICKS_GetProperty" ) 
	#define CAL_TICKS_GetProperty  TICKS_GetProperty
	#define CHK_TICKS_GetProperty  TRUE
	#define EXP_TICKS_GetProperty  CAL_CMEXPAPI( "TICKS_GetProperty" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAATICK_EXTERNAL)
	#define USE_TICKS_GetProperty
	#define EXT_TICKS_GetProperty
	#define GET_TICKS_GetProperty(fl)  CAL_CMGETAPI( "TICKS_GetProperty" ) 
	#define CAL_TICKS_GetProperty  TICKS_GetProperty
	#define CHK_TICKS_GetProperty  TRUE
	#define EXP_TICKS_GetProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TICKS_GetProperty", (RTS_UINTPTR)TICKS_GetProperty, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATickTICKS_GetProperty
	#define EXT_CmpCAATickTICKS_GetProperty
	#define GET_CmpCAATickTICKS_GetProperty  ERR_OK
	#define CAL_CmpCAATickTICKS_GetProperty pICmpCAATick->ITICKS_GetProperty
	#define CHK_CmpCAATickTICKS_GetProperty (pICmpCAATick != NULL)
	#define EXP_CmpCAATickTICKS_GetProperty  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TICKS_GetProperty
	#define EXT_TICKS_GetProperty
	#define GET_TICKS_GetProperty(fl)  CAL_CMGETAPI( "TICKS_GetProperty" ) 
	#define CAL_TICKS_GetProperty pICmpCAATick->ITICKS_GetProperty
	#define CHK_TICKS_GetProperty (pICmpCAATick != NULL)
	#define EXP_TICKS_GetProperty  CAL_CMEXPAPI( "TICKS_GetProperty" ) 
#else /* DYNAMIC_LINK */
	#define USE_TICKS_GetProperty  PFTICKS_GETPROPERTY pfTICKS_GetProperty;
	#define EXT_TICKS_GetProperty  extern PFTICKS_GETPROPERTY pfTICKS_GetProperty;
	#define GET_TICKS_GetProperty(fl)  s_pfCMGetAPI2( "TICKS_GetProperty", (RTS_VOID_FCTPTR *)&pfTICKS_GetProperty, (fl), 0, 0)
	#define CAL_TICKS_GetProperty  pfTICKS_GetProperty
	#define CHK_TICKS_GetProperty  (pfTICKS_GetProperty != NULL)
	#define EXP_TICKS_GetProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TICKS_GetProperty", (RTS_UINTPTR)TICKS_GetProperty, 0, 0) 
#endif



unsigned short CDECL TICKS_GetSupplierVersion(CAA_BOOL xDummy);
typedef unsigned short (CDECL * PFTICKS_GETSUPPLIERVERSION) (CAA_BOOL xDummy);
#if defined(CMPCAATICK_NOTIMPLEMENTED) || defined(TICKS_GETSUPPLIERVERSION_NOTIMPLEMENTED)
	#define USE_TICKS_GetSupplierVersion
	#define EXT_TICKS_GetSupplierVersion
	#define GET_TICKS_GetSupplierVersion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TICKS_GetSupplierVersion(p0)  (unsigned short)ERR_NOTIMPLEMENTED
	#define CHK_TICKS_GetSupplierVersion  FALSE
	#define EXP_TICKS_GetSupplierVersion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TICKS_GetSupplierVersion
	#define EXT_TICKS_GetSupplierVersion
	#define GET_TICKS_GetSupplierVersion(fl)  CAL_CMGETAPI( "TICKS_GetSupplierVersion" ) 
	#define CAL_TICKS_GetSupplierVersion  TICKS_GetSupplierVersion
	#define CHK_TICKS_GetSupplierVersion  TRUE
	#define EXP_TICKS_GetSupplierVersion  CAL_CMEXPAPI( "TICKS_GetSupplierVersion" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAATICK_EXTERNAL)
	#define USE_TICKS_GetSupplierVersion
	#define EXT_TICKS_GetSupplierVersion
	#define GET_TICKS_GetSupplierVersion(fl)  CAL_CMGETAPI( "TICKS_GetSupplierVersion" ) 
	#define CAL_TICKS_GetSupplierVersion  TICKS_GetSupplierVersion
	#define CHK_TICKS_GetSupplierVersion  TRUE
	#define EXP_TICKS_GetSupplierVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TICKS_GetSupplierVersion", (RTS_UINTPTR)TICKS_GetSupplierVersion, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATickTICKS_GetSupplierVersion
	#define EXT_CmpCAATickTICKS_GetSupplierVersion
	#define GET_CmpCAATickTICKS_GetSupplierVersion  ERR_OK
	#define CAL_CmpCAATickTICKS_GetSupplierVersion pICmpCAATick->ITICKS_GetSupplierVersion
	#define CHK_CmpCAATickTICKS_GetSupplierVersion (pICmpCAATick != NULL)
	#define EXP_CmpCAATickTICKS_GetSupplierVersion  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TICKS_GetSupplierVersion
	#define EXT_TICKS_GetSupplierVersion
	#define GET_TICKS_GetSupplierVersion(fl)  CAL_CMGETAPI( "TICKS_GetSupplierVersion" ) 
	#define CAL_TICKS_GetSupplierVersion pICmpCAATick->ITICKS_GetSupplierVersion
	#define CHK_TICKS_GetSupplierVersion (pICmpCAATick != NULL)
	#define EXP_TICKS_GetSupplierVersion  CAL_CMEXPAPI( "TICKS_GetSupplierVersion" ) 
#else /* DYNAMIC_LINK */
	#define USE_TICKS_GetSupplierVersion  PFTICKS_GETSUPPLIERVERSION pfTICKS_GetSupplierVersion;
	#define EXT_TICKS_GetSupplierVersion  extern PFTICKS_GETSUPPLIERVERSION pfTICKS_GetSupplierVersion;
	#define GET_TICKS_GetSupplierVersion(fl)  s_pfCMGetAPI2( "TICKS_GetSupplierVersion", (RTS_VOID_FCTPTR *)&pfTICKS_GetSupplierVersion, (fl), 0, 0)
	#define CAL_TICKS_GetSupplierVersion  pfTICKS_GetSupplierVersion
	#define CHK_TICKS_GetSupplierVersion  (pfTICKS_GetSupplierVersion != NULL)
	#define EXP_TICKS_GetSupplierVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TICKS_GetSupplierVersion", (RTS_UINTPTR)TICKS_GetSupplierVersion, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>ticks_getproperty</description>
 */
typedef struct tagticks_getproperty_struct
{
	RTS_IEC_WORD wProperty;				/* VAR_INPUT */	
	RTS_IEC_XWORD TICKS_GetProperty;	/* VAR_OUTPUT */	
} ticks_getproperty_struct;

void CDECL CDECL_EXT ticks_getproperty(ticks_getproperty_struct *p);
typedef void (CDECL CDECL_EXT* PFTICKS_GETPROPERTY_IEC) (ticks_getproperty_struct *p);
#if defined(CMPCAATICK_NOTIMPLEMENTED) || defined(TICKS_GETPROPERTY_NOTIMPLEMENTED)
	#define USE_ticks_getproperty
	#define EXT_ticks_getproperty
	#define GET_ticks_getproperty(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ticks_getproperty(p0) 
	#define CHK_ticks_getproperty  FALSE
	#define EXP_ticks_getproperty  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ticks_getproperty
	#define EXT_ticks_getproperty
	#define GET_ticks_getproperty(fl)  CAL_CMGETAPI( "ticks_getproperty" ) 
	#define CAL_ticks_getproperty  ticks_getproperty
	#define CHK_ticks_getproperty  TRUE
	#define EXP_ticks_getproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticks_getproperty", (RTS_UINTPTR)ticks_getproperty, 1, RTSITF_GET_SIGNATURE(0, 0x2BC58761), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAATICK_EXTERNAL)
	#define USE_ticks_getproperty
	#define EXT_ticks_getproperty
	#define GET_ticks_getproperty(fl)  CAL_CMGETAPI( "ticks_getproperty" ) 
	#define CAL_ticks_getproperty  ticks_getproperty
	#define CHK_ticks_getproperty  TRUE
	#define EXP_ticks_getproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticks_getproperty", (RTS_UINTPTR)ticks_getproperty, 1, RTSITF_GET_SIGNATURE(0, 0x2BC58761), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATickticks_getproperty
	#define EXT_CmpCAATickticks_getproperty
	#define GET_CmpCAATickticks_getproperty  ERR_OK
	#define CAL_CmpCAATickticks_getproperty  ticks_getproperty
	#define CHK_CmpCAATickticks_getproperty  TRUE
	#define EXP_CmpCAATickticks_getproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticks_getproperty", (RTS_UINTPTR)ticks_getproperty, 1, RTSITF_GET_SIGNATURE(0, 0x2BC58761), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_ticks_getproperty
	#define EXT_ticks_getproperty
	#define GET_ticks_getproperty(fl)  CAL_CMGETAPI( "ticks_getproperty" ) 
	#define CAL_ticks_getproperty  ticks_getproperty
	#define CHK_ticks_getproperty  TRUE
	#define EXP_ticks_getproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticks_getproperty", (RTS_UINTPTR)ticks_getproperty, 1, RTSITF_GET_SIGNATURE(0, 0x2BC58761), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_ticks_getproperty  PFTICKS_GETPROPERTY_IEC pfticks_getproperty;
	#define EXT_ticks_getproperty  extern PFTICKS_GETPROPERTY_IEC pfticks_getproperty;
	#define GET_ticks_getproperty(fl)  s_pfCMGetAPI2( "ticks_getproperty", (RTS_VOID_FCTPTR *)&pfticks_getproperty, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x2BC58761), 0x03050500)
	#define CAL_ticks_getproperty  pfticks_getproperty
	#define CHK_ticks_getproperty  (pfticks_getproperty != NULL)
	#define EXP_ticks_getproperty   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticks_getproperty", (RTS_UINTPTR)ticks_getproperty, 1, RTSITF_GET_SIGNATURE(0, 0x2BC58761), 0x03050500) 
#endif


/**
 * <description>ticks_getsupplierversion</description>
 */
typedef struct tagticks_getsupplierversion_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	RTS_IEC_WORD TICKS_GetSupplierVersion;	/* VAR_OUTPUT */	
} ticks_getsupplierversion_struct;

void CDECL CDECL_EXT ticks_getsupplierversion(ticks_getsupplierversion_struct *p);
typedef void (CDECL CDECL_EXT* PFTICKS_GETSUPPLIERVERSION_IEC) (ticks_getsupplierversion_struct *p);
#if defined(CMPCAATICK_NOTIMPLEMENTED) || defined(TICKS_GETSUPPLIERVERSION_NOTIMPLEMENTED)
	#define USE_ticks_getsupplierversion
	#define EXT_ticks_getsupplierversion
	#define GET_ticks_getsupplierversion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ticks_getsupplierversion(p0) 
	#define CHK_ticks_getsupplierversion  FALSE
	#define EXP_ticks_getsupplierversion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ticks_getsupplierversion
	#define EXT_ticks_getsupplierversion
	#define GET_ticks_getsupplierversion(fl)  CAL_CMGETAPI( "ticks_getsupplierversion" ) 
	#define CAL_ticks_getsupplierversion  ticks_getsupplierversion
	#define CHK_ticks_getsupplierversion  TRUE
	#define EXP_ticks_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticks_getsupplierversion", (RTS_UINTPTR)ticks_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xF305F08E), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAATICK_EXTERNAL)
	#define USE_ticks_getsupplierversion
	#define EXT_ticks_getsupplierversion
	#define GET_ticks_getsupplierversion(fl)  CAL_CMGETAPI( "ticks_getsupplierversion" ) 
	#define CAL_ticks_getsupplierversion  ticks_getsupplierversion
	#define CHK_ticks_getsupplierversion  TRUE
	#define EXP_ticks_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticks_getsupplierversion", (RTS_UINTPTR)ticks_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xF305F08E), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATickticks_getsupplierversion
	#define EXT_CmpCAATickticks_getsupplierversion
	#define GET_CmpCAATickticks_getsupplierversion  ERR_OK
	#define CAL_CmpCAATickticks_getsupplierversion  ticks_getsupplierversion
	#define CHK_CmpCAATickticks_getsupplierversion  TRUE
	#define EXP_CmpCAATickticks_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticks_getsupplierversion", (RTS_UINTPTR)ticks_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xF305F08E), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_ticks_getsupplierversion
	#define EXT_ticks_getsupplierversion
	#define GET_ticks_getsupplierversion(fl)  CAL_CMGETAPI( "ticks_getsupplierversion" ) 
	#define CAL_ticks_getsupplierversion  ticks_getsupplierversion
	#define CHK_ticks_getsupplierversion  TRUE
	#define EXP_ticks_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticks_getsupplierversion", (RTS_UINTPTR)ticks_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xF305F08E), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_ticks_getsupplierversion  PFTICKS_GETSUPPLIERVERSION_IEC pfticks_getsupplierversion;
	#define EXT_ticks_getsupplierversion  extern PFTICKS_GETSUPPLIERVERSION_IEC pfticks_getsupplierversion;
	#define GET_ticks_getsupplierversion(fl)  s_pfCMGetAPI2( "ticks_getsupplierversion", (RTS_VOID_FCTPTR *)&pfticks_getsupplierversion, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xF305F08E), 0x03050500)
	#define CAL_ticks_getsupplierversion  pfticks_getsupplierversion
	#define CHK_ticks_getsupplierversion  (pfticks_getsupplierversion != NULL)
	#define EXP_ticks_getsupplierversion   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticks_getsupplierversion", (RTS_UINTPTR)ticks_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xF305F08E), 0x03050500) 
#endif


/**
 * <description>ticks_gettick</description>
 */
typedef struct tagticks_gettick_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	CAA_TICK TICKS_GetTick;				/* VAR_OUTPUT */	
} ticks_gettick_struct;

void CDECL CDECL_EXT ticks_gettick(ticks_gettick_struct *p);
typedef void (CDECL CDECL_EXT* PFTICKS_GETTICK_IEC) (ticks_gettick_struct *p);
#if defined(CMPCAATICK_NOTIMPLEMENTED) || defined(TICKS_GETTICK_NOTIMPLEMENTED)
	#define USE_ticks_gettick
	#define EXT_ticks_gettick
	#define GET_ticks_gettick(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ticks_gettick(p0) 
	#define CHK_ticks_gettick  FALSE
	#define EXP_ticks_gettick  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ticks_gettick
	#define EXT_ticks_gettick
	#define GET_ticks_gettick(fl)  CAL_CMGETAPI( "ticks_gettick" ) 
	#define CAL_ticks_gettick  ticks_gettick
	#define CHK_ticks_gettick  TRUE
	#define EXP_ticks_gettick  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticks_gettick", (RTS_UINTPTR)ticks_gettick, 1, RTSITF_GET_SIGNATURE(0, 0xE34E0CC2), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAATICK_EXTERNAL)
	#define USE_ticks_gettick
	#define EXT_ticks_gettick
	#define GET_ticks_gettick(fl)  CAL_CMGETAPI( "ticks_gettick" ) 
	#define CAL_ticks_gettick  ticks_gettick
	#define CHK_ticks_gettick  TRUE
	#define EXP_ticks_gettick  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticks_gettick", (RTS_UINTPTR)ticks_gettick, 1, RTSITF_GET_SIGNATURE(0, 0xE34E0CC2), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATickticks_gettick
	#define EXT_CmpCAATickticks_gettick
	#define GET_CmpCAATickticks_gettick  ERR_OK
	#define CAL_CmpCAATickticks_gettick  ticks_gettick
	#define CHK_CmpCAATickticks_gettick  TRUE
	#define EXP_CmpCAATickticks_gettick  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticks_gettick", (RTS_UINTPTR)ticks_gettick, 1, RTSITF_GET_SIGNATURE(0, 0xE34E0CC2), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_ticks_gettick
	#define EXT_ticks_gettick
	#define GET_ticks_gettick(fl)  CAL_CMGETAPI( "ticks_gettick" ) 
	#define CAL_ticks_gettick  ticks_gettick
	#define CHK_ticks_gettick  TRUE
	#define EXP_ticks_gettick  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticks_gettick", (RTS_UINTPTR)ticks_gettick, 1, RTSITF_GET_SIGNATURE(0, 0xE34E0CC2), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_ticks_gettick  PFTICKS_GETTICK_IEC pfticks_gettick;
	#define EXT_ticks_gettick  extern PFTICKS_GETTICK_IEC pfticks_gettick;
	#define GET_ticks_gettick(fl)  s_pfCMGetAPI2( "ticks_gettick", (RTS_VOID_FCTPTR *)&pfticks_gettick, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xE34E0CC2), 0x03050500)
	#define CAL_ticks_gettick  pfticks_gettick
	#define CHK_ticks_gettick  (pfticks_gettick != NULL)
	#define EXP_ticks_gettick   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ticks_gettick", (RTS_UINTPTR)ticks_gettick, 1, RTSITF_GET_SIGNATURE(0, 0xE34E0CC2), 0x03050500) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/



typedef struct
{
	IBase_C *pBase;
	PFTICKS_GETTICK ITICKS_GetTick;
 	PFTICKS_GETPROPERTY ITICKS_GetProperty;
 	PFTICKS_GETSUPPLIERVERSION ITICKS_GetSupplierVersion;
 } ICmpCAATick_C;

#ifdef CPLUSPLUS
class ICmpCAATick : public IBase
{
	public:
		virtual CAA_TICK CDECL ITICKS_GetTick(CAA_BOOL xDummy) =0;
		virtual RTS_IEC_XWORD CDECL ITICKS_GetProperty(unsigned short usProperty) =0;
		virtual unsigned short CDECL ITICKS_GetSupplierVersion(CAA_BOOL xDummy) =0;
};
	#ifndef ITF_CmpCAATick
		#define ITF_CmpCAATick static ICmpCAATick *pICmpCAATick = NULL;
	#endif
	#define EXTITF_CmpCAATick
#else	/*CPLUSPLUS*/
	typedef ICmpCAATick_C		ICmpCAATick;
	#ifndef ITF_CmpCAATick
		#define ITF_CmpCAATick
	#endif
	#define EXTITF_CmpCAATick
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCAATICKITF_H_*/
