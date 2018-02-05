 
	
	
#ifndef _CMPCAATYPESITF_H_
#define _CMPCAATYPESITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns the actual release and implementation version of the library 
 */
typedef struct tagcaa_getsupplierversion_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	/* Backward compatibility */
	RTS_IEC_WORD CAA_GetSupplierVersion;	/* VAR_OUTPUT */	
} caa_getsupplierversion_struct;

void CDECL CDECL_EXT caa_getsupplierversion(caa_getsupplierversion_struct *p);
typedef void (CDECL CDECL_EXT* PFCAA_GETSUPPLIERVERSION_IEC) (caa_getsupplierversion_struct *p);
#if defined(CMPCAATYPES_NOTIMPLEMENTED) || defined(CAA_GETSUPPLIERVERSION_NOTIMPLEMENTED)
	#define USE_caa_getsupplierversion
	#define EXT_caa_getsupplierversion
	#define GET_caa_getsupplierversion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_caa_getsupplierversion(p0) 
	#define CHK_caa_getsupplierversion  FALSE
	#define EXP_caa_getsupplierversion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_caa_getsupplierversion
	#define EXT_caa_getsupplierversion
	#define GET_caa_getsupplierversion(fl)  CAL_CMGETAPI( "caa_getsupplierversion" ) 
	#define CAL_caa_getsupplierversion  caa_getsupplierversion
	#define CHK_caa_getsupplierversion  TRUE
	#define EXP_caa_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"caa_getsupplierversion", (RTS_UINTPTR)caa_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0x0CB79C27), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAATYPES_EXTERNAL)
	#define USE_caa_getsupplierversion
	#define EXT_caa_getsupplierversion
	#define GET_caa_getsupplierversion(fl)  CAL_CMGETAPI( "caa_getsupplierversion" ) 
	#define CAL_caa_getsupplierversion  caa_getsupplierversion
	#define CHK_caa_getsupplierversion  TRUE
	#define EXP_caa_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"caa_getsupplierversion", (RTS_UINTPTR)caa_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0x0CB79C27), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATypescaa_getsupplierversion
	#define EXT_CmpCAATypescaa_getsupplierversion
	#define GET_CmpCAATypescaa_getsupplierversion  ERR_OK
	#define CAL_CmpCAATypescaa_getsupplierversion  caa_getsupplierversion
	#define CHK_CmpCAATypescaa_getsupplierversion  TRUE
	#define EXP_CmpCAATypescaa_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"caa_getsupplierversion", (RTS_UINTPTR)caa_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0x0CB79C27), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_caa_getsupplierversion
	#define EXT_caa_getsupplierversion
	#define GET_caa_getsupplierversion(fl)  CAL_CMGETAPI( "caa_getsupplierversion" ) 
	#define CAL_caa_getsupplierversion  caa_getsupplierversion
	#define CHK_caa_getsupplierversion  TRUE
	#define EXP_caa_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"caa_getsupplierversion", (RTS_UINTPTR)caa_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0x0CB79C27), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_caa_getsupplierversion  PFCAA_GETSUPPLIERVERSION_IEC pfcaa_getsupplierversion;
	#define EXT_caa_getsupplierversion  extern PFCAA_GETSUPPLIERVERSION_IEC pfcaa_getsupplierversion;
	#define GET_caa_getsupplierversion(fl)  s_pfCMGetAPI2( "caa_getsupplierversion", (RTS_VOID_FCTPTR *)&pfcaa_getsupplierversion, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x0CB79C27), 0x03050500)
	#define CAL_caa_getsupplierversion  pfcaa_getsupplierversion
	#define CHK_caa_getsupplierversion  (pfcaa_getsupplierversion != NULL)
	#define EXP_caa_getsupplierversion   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"caa_getsupplierversion", (RTS_UINTPTR)caa_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0x0CB79C27), 0x03050500) 
#endif


/**
 * <description>caa_resmanincharge</description>
 */
typedef struct tagcaa_resmanincharge_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	CAA_BOOL CAA_ResManInCharge;		/* VAR_OUTPUT */	
} caa_resmanincharge_struct;

void CDECL CDECL_EXT caa_resmanincharge(caa_resmanincharge_struct *p);
typedef void (CDECL CDECL_EXT* PFCAA_RESMANINCHARGE_IEC) (caa_resmanincharge_struct *p);
#if defined(CMPCAATYPES_NOTIMPLEMENTED) || defined(CAA_RESMANINCHARGE_NOTIMPLEMENTED)
	#define USE_caa_resmanincharge
	#define EXT_caa_resmanincharge
	#define GET_caa_resmanincharge(fl)  ERR_NOTIMPLEMENTED
	#define CAL_caa_resmanincharge(p0) 
	#define CHK_caa_resmanincharge  FALSE
	#define EXP_caa_resmanincharge  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_caa_resmanincharge
	#define EXT_caa_resmanincharge
	#define GET_caa_resmanincharge(fl)  CAL_CMGETAPI( "caa_resmanincharge" ) 
	#define CAL_caa_resmanincharge  caa_resmanincharge
	#define CHK_caa_resmanincharge  TRUE
	#define EXP_caa_resmanincharge  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"caa_resmanincharge", (RTS_UINTPTR)caa_resmanincharge, 1, RTSITF_GET_SIGNATURE(0, 0x152491C7), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAATYPES_EXTERNAL)
	#define USE_caa_resmanincharge
	#define EXT_caa_resmanincharge
	#define GET_caa_resmanincharge(fl)  CAL_CMGETAPI( "caa_resmanincharge" ) 
	#define CAL_caa_resmanincharge  caa_resmanincharge
	#define CHK_caa_resmanincharge  TRUE
	#define EXP_caa_resmanincharge  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"caa_resmanincharge", (RTS_UINTPTR)caa_resmanincharge, 1, RTSITF_GET_SIGNATURE(0, 0x152491C7), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATypescaa_resmanincharge
	#define EXT_CmpCAATypescaa_resmanincharge
	#define GET_CmpCAATypescaa_resmanincharge  ERR_OK
	#define CAL_CmpCAATypescaa_resmanincharge  caa_resmanincharge
	#define CHK_CmpCAATypescaa_resmanincharge  TRUE
	#define EXP_CmpCAATypescaa_resmanincharge  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"caa_resmanincharge", (RTS_UINTPTR)caa_resmanincharge, 1, RTSITF_GET_SIGNATURE(0, 0x152491C7), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_caa_resmanincharge
	#define EXT_caa_resmanincharge
	#define GET_caa_resmanincharge(fl)  CAL_CMGETAPI( "caa_resmanincharge" ) 
	#define CAL_caa_resmanincharge  caa_resmanincharge
	#define CHK_caa_resmanincharge  TRUE
	#define EXP_caa_resmanincharge  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"caa_resmanincharge", (RTS_UINTPTR)caa_resmanincharge, 1, RTSITF_GET_SIGNATURE(0, 0x152491C7), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_caa_resmanincharge  PFCAA_RESMANINCHARGE_IEC pfcaa_resmanincharge;
	#define EXT_caa_resmanincharge  extern PFCAA_RESMANINCHARGE_IEC pfcaa_resmanincharge;
	#define GET_caa_resmanincharge(fl)  s_pfCMGetAPI2( "caa_resmanincharge", (RTS_VOID_FCTPTR *)&pfcaa_resmanincharge, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x152491C7), 0x03050500)
	#define CAL_caa_resmanincharge  pfcaa_resmanincharge
	#define CHK_caa_resmanincharge  (pfcaa_resmanincharge != NULL)
	#define EXP_caa_resmanincharge   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"caa_resmanincharge", (RTS_UINTPTR)caa_resmanincharge, 1, RTSITF_GET_SIGNATURE(0, 0x152491C7), 0x03050500) 
#endif


/**
 * <description>caa_tasklock</description>
 */
typedef struct tagcaa_tasklock_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	CAA_ERROR CAA_TaskLock;				/* VAR_OUTPUT */	
} caa_tasklock_struct;

void CDECL CDECL_EXT caa_tasklock(caa_tasklock_struct *p);
typedef void (CDECL CDECL_EXT* PFCAA_TASKLOCK_IEC) (caa_tasklock_struct *p);
#if defined(CMPCAATYPES_NOTIMPLEMENTED) || defined(CAA_TASKLOCK_NOTIMPLEMENTED)
	#define USE_caa_tasklock
	#define EXT_caa_tasklock
	#define GET_caa_tasklock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_caa_tasklock(p0) 
	#define CHK_caa_tasklock  FALSE
	#define EXP_caa_tasklock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_caa_tasklock
	#define EXT_caa_tasklock
	#define GET_caa_tasklock(fl)  CAL_CMGETAPI( "caa_tasklock" ) 
	#define CAL_caa_tasklock  caa_tasklock
	#define CHK_caa_tasklock  TRUE
	#define EXP_caa_tasklock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"caa_tasklock", (RTS_UINTPTR)caa_tasklock, 1, RTSITF_GET_SIGNATURE(0, 0x7366A49D), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAATYPES_EXTERNAL)
	#define USE_caa_tasklock
	#define EXT_caa_tasklock
	#define GET_caa_tasklock(fl)  CAL_CMGETAPI( "caa_tasklock" ) 
	#define CAL_caa_tasklock  caa_tasklock
	#define CHK_caa_tasklock  TRUE
	#define EXP_caa_tasklock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"caa_tasklock", (RTS_UINTPTR)caa_tasklock, 1, RTSITF_GET_SIGNATURE(0, 0x7366A49D), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATypescaa_tasklock
	#define EXT_CmpCAATypescaa_tasklock
	#define GET_CmpCAATypescaa_tasklock  ERR_OK
	#define CAL_CmpCAATypescaa_tasklock  caa_tasklock
	#define CHK_CmpCAATypescaa_tasklock  TRUE
	#define EXP_CmpCAATypescaa_tasklock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"caa_tasklock", (RTS_UINTPTR)caa_tasklock, 1, RTSITF_GET_SIGNATURE(0, 0x7366A49D), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_caa_tasklock
	#define EXT_caa_tasklock
	#define GET_caa_tasklock(fl)  CAL_CMGETAPI( "caa_tasklock" ) 
	#define CAL_caa_tasklock  caa_tasklock
	#define CHK_caa_tasklock  TRUE
	#define EXP_caa_tasklock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"caa_tasklock", (RTS_UINTPTR)caa_tasklock, 1, RTSITF_GET_SIGNATURE(0, 0x7366A49D), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_caa_tasklock  PFCAA_TASKLOCK_IEC pfcaa_tasklock;
	#define EXT_caa_tasklock  extern PFCAA_TASKLOCK_IEC pfcaa_tasklock;
	#define GET_caa_tasklock(fl)  s_pfCMGetAPI2( "caa_tasklock", (RTS_VOID_FCTPTR *)&pfcaa_tasklock, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x7366A49D), 0x03050500)
	#define CAL_caa_tasklock  pfcaa_tasklock
	#define CHK_caa_tasklock  (pfcaa_tasklock != NULL)
	#define EXP_caa_tasklock   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"caa_tasklock", (RTS_UINTPTR)caa_tasklock, 1, RTSITF_GET_SIGNATURE(0, 0x7366A49D), 0x03050500) 
#endif


/**
 * <description>caa_taskunlock</description>
 */
typedef struct tagcaa_taskunlock_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	CAA_ERROR CAA_TaskUnlock;			/* VAR_OUTPUT */	
} caa_taskunlock_struct;

void CDECL CDECL_EXT caa_taskunlock(caa_taskunlock_struct *p);
typedef void (CDECL CDECL_EXT* PFCAA_TASKUNLOCK_IEC) (caa_taskunlock_struct *p);
#if defined(CMPCAATYPES_NOTIMPLEMENTED) || defined(CAA_TASKUNLOCK_NOTIMPLEMENTED)
	#define USE_caa_taskunlock
	#define EXT_caa_taskunlock
	#define GET_caa_taskunlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_caa_taskunlock(p0) 
	#define CHK_caa_taskunlock  FALSE
	#define EXP_caa_taskunlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_caa_taskunlock
	#define EXT_caa_taskunlock
	#define GET_caa_taskunlock(fl)  CAL_CMGETAPI( "caa_taskunlock" ) 
	#define CAL_caa_taskunlock  caa_taskunlock
	#define CHK_caa_taskunlock  TRUE
	#define EXP_caa_taskunlock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"caa_taskunlock", (RTS_UINTPTR)caa_taskunlock, 1, RTSITF_GET_SIGNATURE(0, 0x8ABBECC7), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAATYPES_EXTERNAL)
	#define USE_caa_taskunlock
	#define EXT_caa_taskunlock
	#define GET_caa_taskunlock(fl)  CAL_CMGETAPI( "caa_taskunlock" ) 
	#define CAL_caa_taskunlock  caa_taskunlock
	#define CHK_caa_taskunlock  TRUE
	#define EXP_caa_taskunlock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"caa_taskunlock", (RTS_UINTPTR)caa_taskunlock, 1, RTSITF_GET_SIGNATURE(0, 0x8ABBECC7), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATypescaa_taskunlock
	#define EXT_CmpCAATypescaa_taskunlock
	#define GET_CmpCAATypescaa_taskunlock  ERR_OK
	#define CAL_CmpCAATypescaa_taskunlock  caa_taskunlock
	#define CHK_CmpCAATypescaa_taskunlock  TRUE
	#define EXP_CmpCAATypescaa_taskunlock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"caa_taskunlock", (RTS_UINTPTR)caa_taskunlock, 1, RTSITF_GET_SIGNATURE(0, 0x8ABBECC7), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_caa_taskunlock
	#define EXT_caa_taskunlock
	#define GET_caa_taskunlock(fl)  CAL_CMGETAPI( "caa_taskunlock" ) 
	#define CAL_caa_taskunlock  caa_taskunlock
	#define CHK_caa_taskunlock  TRUE
	#define EXP_caa_taskunlock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"caa_taskunlock", (RTS_UINTPTR)caa_taskunlock, 1, RTSITF_GET_SIGNATURE(0, 0x8ABBECC7), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_caa_taskunlock  PFCAA_TASKUNLOCK_IEC pfcaa_taskunlock;
	#define EXT_caa_taskunlock  extern PFCAA_TASKUNLOCK_IEC pfcaa_taskunlock;
	#define GET_caa_taskunlock(fl)  s_pfCMGetAPI2( "caa_taskunlock", (RTS_VOID_FCTPTR *)&pfcaa_taskunlock, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x8ABBECC7), 0x03050500)
	#define CAL_caa_taskunlock  pfcaa_taskunlock
	#define CHK_caa_taskunlock  (pfcaa_taskunlock != NULL)
	#define EXP_caa_taskunlock   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"caa_taskunlock", (RTS_UINTPTR)caa_taskunlock, 1, RTSITF_GET_SIGNATURE(0, 0x8ABBECC7), 0x03050500) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

unsigned short CDECL CAA_GetSupplierVersion(char xDummy);
typedef unsigned short (CDECL * PFCAA_GETSUPPLIERVERSION) (char xDummy);
#if defined(CMPCAATYPES_NOTIMPLEMENTED) || defined(CAA_GETSUPPLIERVERSION_NOTIMPLEMENTED)
	#define USE_CAA_GetSupplierVersion
	#define EXT_CAA_GetSupplierVersion
	#define GET_CAA_GetSupplierVersion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CAA_GetSupplierVersion(p0)  (unsigned short)ERR_NOTIMPLEMENTED
	#define CHK_CAA_GetSupplierVersion  FALSE
	#define EXP_CAA_GetSupplierVersion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CAA_GetSupplierVersion
	#define EXT_CAA_GetSupplierVersion
	#define GET_CAA_GetSupplierVersion(fl)  CAL_CMGETAPI( "CAA_GetSupplierVersion" ) 
	#define CAL_CAA_GetSupplierVersion  CAA_GetSupplierVersion
	#define CHK_CAA_GetSupplierVersion  TRUE
	#define EXP_CAA_GetSupplierVersion  CAL_CMEXPAPI( "CAA_GetSupplierVersion" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAATYPES_EXTERNAL)
	#define USE_CAA_GetSupplierVersion
	#define EXT_CAA_GetSupplierVersion
	#define GET_CAA_GetSupplierVersion(fl)  CAL_CMGETAPI( "CAA_GetSupplierVersion" ) 
	#define CAL_CAA_GetSupplierVersion  CAA_GetSupplierVersion
	#define CHK_CAA_GetSupplierVersion  TRUE
	#define EXP_CAA_GetSupplierVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CAA_GetSupplierVersion", (RTS_UINTPTR)CAA_GetSupplierVersion, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATypesCAA_GetSupplierVersion
	#define EXT_CmpCAATypesCAA_GetSupplierVersion
	#define GET_CmpCAATypesCAA_GetSupplierVersion  ERR_OK
	#define CAL_CmpCAATypesCAA_GetSupplierVersion pICmpCAATypes->ICAA_GetSupplierVersion
	#define CHK_CmpCAATypesCAA_GetSupplierVersion (pICmpCAATypes != NULL)
	#define EXP_CmpCAATypesCAA_GetSupplierVersion  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CAA_GetSupplierVersion
	#define EXT_CAA_GetSupplierVersion
	#define GET_CAA_GetSupplierVersion(fl)  CAL_CMGETAPI( "CAA_GetSupplierVersion" ) 
	#define CAL_CAA_GetSupplierVersion pICmpCAATypes->ICAA_GetSupplierVersion
	#define CHK_CAA_GetSupplierVersion (pICmpCAATypes != NULL)
	#define EXP_CAA_GetSupplierVersion  CAL_CMEXPAPI( "CAA_GetSupplierVersion" ) 
#else /* DYNAMIC_LINK */
	#define USE_CAA_GetSupplierVersion  PFCAA_GETSUPPLIERVERSION pfCAA_GetSupplierVersion;
	#define EXT_CAA_GetSupplierVersion  extern PFCAA_GETSUPPLIERVERSION pfCAA_GetSupplierVersion;
	#define GET_CAA_GetSupplierVersion(fl)  s_pfCMGetAPI2( "CAA_GetSupplierVersion", (RTS_VOID_FCTPTR *)&pfCAA_GetSupplierVersion, (fl), 0, 0)
	#define CAL_CAA_GetSupplierVersion  pfCAA_GetSupplierVersion
	#define CHK_CAA_GetSupplierVersion  (pfCAA_GetSupplierVersion != NULL)
	#define EXP_CAA_GetSupplierVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CAA_GetSupplierVersion", (RTS_UINTPTR)CAA_GetSupplierVersion, 0, 0) 
#endif



CAA_HANDLE CDECL CAA_Dummy(CAA_HANDLE hHandle, CAA_ERROR* pError);
typedef CAA_HANDLE (CDECL * PFCAA_DUMMY) (CAA_HANDLE hHandle, CAA_ERROR* pError);
#if defined(CMPCAATYPES_NOTIMPLEMENTED) || defined(CAA_DUMMY_NOTIMPLEMENTED)
	#define USE_CAA_Dummy
	#define EXT_CAA_Dummy
	#define GET_CAA_Dummy(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CAA_Dummy(p0,p1)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_CAA_Dummy  FALSE
	#define EXP_CAA_Dummy  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CAA_Dummy
	#define EXT_CAA_Dummy
	#define GET_CAA_Dummy(fl)  CAL_CMGETAPI( "CAA_Dummy" ) 
	#define CAL_CAA_Dummy  CAA_Dummy
	#define CHK_CAA_Dummy  TRUE
	#define EXP_CAA_Dummy  CAL_CMEXPAPI( "CAA_Dummy" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAATYPES_EXTERNAL)
	#define USE_CAA_Dummy
	#define EXT_CAA_Dummy
	#define GET_CAA_Dummy(fl)  CAL_CMGETAPI( "CAA_Dummy" ) 
	#define CAL_CAA_Dummy  CAA_Dummy
	#define CHK_CAA_Dummy  TRUE
	#define EXP_CAA_Dummy  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CAA_Dummy", (RTS_UINTPTR)CAA_Dummy, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATypesCAA_Dummy
	#define EXT_CmpCAATypesCAA_Dummy
	#define GET_CmpCAATypesCAA_Dummy  ERR_OK
	#define CAL_CmpCAATypesCAA_Dummy pICmpCAATypes->ICAA_Dummy
	#define CHK_CmpCAATypesCAA_Dummy (pICmpCAATypes != NULL)
	#define EXP_CmpCAATypesCAA_Dummy  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CAA_Dummy
	#define EXT_CAA_Dummy
	#define GET_CAA_Dummy(fl)  CAL_CMGETAPI( "CAA_Dummy" ) 
	#define CAL_CAA_Dummy pICmpCAATypes->ICAA_Dummy
	#define CHK_CAA_Dummy (pICmpCAATypes != NULL)
	#define EXP_CAA_Dummy  CAL_CMEXPAPI( "CAA_Dummy" ) 
#else /* DYNAMIC_LINK */
	#define USE_CAA_Dummy  PFCAA_DUMMY pfCAA_Dummy;
	#define EXT_CAA_Dummy  extern PFCAA_DUMMY pfCAA_Dummy;
	#define GET_CAA_Dummy(fl)  s_pfCMGetAPI2( "CAA_Dummy", (RTS_VOID_FCTPTR *)&pfCAA_Dummy, (fl), 0, 0)
	#define CAL_CAA_Dummy  pfCAA_Dummy
	#define CHK_CAA_Dummy  (pfCAA_Dummy != NULL)
	#define EXP_CAA_Dummy  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CAA_Dummy", (RTS_UINTPTR)CAA_Dummy, 0, 0) 
#endif



CAA_ERROR CDECL CAA_Dummy2(void);
typedef CAA_ERROR (CDECL * PFCAA_DUMMY2) (void);
#if defined(CMPCAATYPES_NOTIMPLEMENTED) || defined(CAA_DUMMY2_NOTIMPLEMENTED)
	#define USE_CAA_Dummy2
	#define EXT_CAA_Dummy2
	#define GET_CAA_Dummy2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CAA_Dummy2()  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CAA_Dummy2  FALSE
	#define EXP_CAA_Dummy2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CAA_Dummy2
	#define EXT_CAA_Dummy2
	#define GET_CAA_Dummy2(fl)  CAL_CMGETAPI( "CAA_Dummy2" ) 
	#define CAL_CAA_Dummy2  CAA_Dummy2
	#define CHK_CAA_Dummy2  TRUE
	#define EXP_CAA_Dummy2  CAL_CMEXPAPI( "CAA_Dummy2" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAATYPES_EXTERNAL)
	#define USE_CAA_Dummy2
	#define EXT_CAA_Dummy2
	#define GET_CAA_Dummy2(fl)  CAL_CMGETAPI( "CAA_Dummy2" ) 
	#define CAL_CAA_Dummy2  CAA_Dummy2
	#define CHK_CAA_Dummy2  TRUE
	#define EXP_CAA_Dummy2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CAA_Dummy2", (RTS_UINTPTR)CAA_Dummy2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAATypesCAA_Dummy2
	#define EXT_CmpCAATypesCAA_Dummy2
	#define GET_CmpCAATypesCAA_Dummy2  ERR_OK
	#define CAL_CmpCAATypesCAA_Dummy2 pICmpCAATypes->ICAA_Dummy2
	#define CHK_CmpCAATypesCAA_Dummy2 (pICmpCAATypes != NULL)
	#define EXP_CmpCAATypesCAA_Dummy2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CAA_Dummy2
	#define EXT_CAA_Dummy2
	#define GET_CAA_Dummy2(fl)  CAL_CMGETAPI( "CAA_Dummy2" ) 
	#define CAL_CAA_Dummy2 pICmpCAATypes->ICAA_Dummy2
	#define CHK_CAA_Dummy2 (pICmpCAATypes != NULL)
	#define EXP_CAA_Dummy2  CAL_CMEXPAPI( "CAA_Dummy2" ) 
#else /* DYNAMIC_LINK */
	#define USE_CAA_Dummy2  PFCAA_DUMMY2 pfCAA_Dummy2;
	#define EXT_CAA_Dummy2  extern PFCAA_DUMMY2 pfCAA_Dummy2;
	#define GET_CAA_Dummy2(fl)  s_pfCMGetAPI2( "CAA_Dummy2", (RTS_VOID_FCTPTR *)&pfCAA_Dummy2, (fl), 0, 0)
	#define CAL_CAA_Dummy2  pfCAA_Dummy2
	#define CHK_CAA_Dummy2  (pfCAA_Dummy2 != NULL)
	#define EXP_CAA_Dummy2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CAA_Dummy2", (RTS_UINTPTR)CAA_Dummy2, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFCAA_GETSUPPLIERVERSION ICAA_GetSupplierVersion;
 	PFCAA_DUMMY ICAA_Dummy;
 	PFCAA_DUMMY2 ICAA_Dummy2;
 } ICmpCAATypes_C;

#ifdef CPLUSPLUS
class ICmpCAATypes : public IBase
{
	public:
		virtual unsigned short CDECL ICAA_GetSupplierVersion(char xDummy) =0;
		virtual CAA_HANDLE CDECL ICAA_Dummy(CAA_HANDLE hHandle, CAA_ERROR* pError) =0;
		virtual CAA_ERROR CDECL ICAA_Dummy2(void) =0;
};
	#ifndef ITF_CmpCAATypes
		#define ITF_CmpCAATypes static ICmpCAATypes *pICmpCAATypes = NULL;
	#endif
	#define EXTITF_CmpCAATypes
#else	/*CPLUSPLUS*/
	typedef ICmpCAATypes_C		ICmpCAATypes;
	#ifndef ITF_CmpCAATypes
		#define ITF_CmpCAATypes
	#endif
	#define EXTITF_CmpCAATypes
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCAATYPESITF_H_*/
