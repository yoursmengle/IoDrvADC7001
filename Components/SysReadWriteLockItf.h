 /**
 * <interfacename>SysReadWriteLock</interfacename>
 * <description>
 * <p>This interface provides a synchronization technique for multiple (shared) reading and single (exclusive) writing access control to a critical resource</p>
 * </description>
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _SYSREADWRITELOCKITF_H_
#define _SYSREADWRITELOCKITF_H_

#include "CmpStd.h"

 

 




/**
 * <category>Compiler switch</category>
 * <description>
 * Compiler switch to enable/disable generic implementation.
 * When SYSREADWRITELOCK_GENERIC is not defined, the implementation relies on the underlying operating system.
 * If the switch is defined, the generic implementation is activated, indepentend of the underlying operating system.
 * </description>
 * <element name="SYSREADWRITELOCK_GENERIC">This switch may be defined in sysdefines.h</element>
 */

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This function can be used to create a ReadWrite locking object (synchronization object)
 * RETURN: Handle to the semaphore or RTS_INVALID_HANDLE if failed
 */
typedef struct tagsysrwlcreate_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors.library) */
	RTS_IEC_HANDLE SysRWLCreate;		/* VAR_OUTPUT */	
} sysrwlcreate_struct;

void CDECL CDECL_EXT sysrwlcreate(sysrwlcreate_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSRWLCREATE_IEC) (sysrwlcreate_struct *p);
#if defined(SYSREADWRITELOCK_NOTIMPLEMENTED) || defined(SYSRWLCREATE_NOTIMPLEMENTED)
	#define USE_sysrwlcreate
	#define EXT_sysrwlcreate
	#define GET_sysrwlcreate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysrwlcreate(p0) 
	#define CHK_sysrwlcreate  FALSE
	#define EXP_sysrwlcreate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysrwlcreate
	#define EXT_sysrwlcreate
	#define GET_sysrwlcreate(fl)  CAL_CMGETAPI( "sysrwlcreate" ) 
	#define CAL_sysrwlcreate  sysrwlcreate
	#define CHK_sysrwlcreate  TRUE
	#define EXP_sysrwlcreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlcreate", (RTS_UINTPTR)sysrwlcreate, 1, 0xC47B7841, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(SYSREADWRITELOCK_EXTERNAL)
	#define USE_sysrwlcreate
	#define EXT_sysrwlcreate
	#define GET_sysrwlcreate(fl)  CAL_CMGETAPI( "sysrwlcreate" ) 
	#define CAL_sysrwlcreate  sysrwlcreate
	#define CHK_sysrwlcreate  TRUE
	#define EXP_sysrwlcreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlcreate", (RTS_UINTPTR)sysrwlcreate, 1, 0xC47B7841, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysReadWriteLocksysrwlcreate
	#define EXT_SysReadWriteLocksysrwlcreate
	#define GET_SysReadWriteLocksysrwlcreate  ERR_OK
	#define CAL_SysReadWriteLocksysrwlcreate  sysrwlcreate
	#define CHK_SysReadWriteLocksysrwlcreate  TRUE
	#define EXP_SysReadWriteLocksysrwlcreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlcreate", (RTS_UINTPTR)sysrwlcreate, 1, 0xC47B7841, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_sysrwlcreate
	#define EXT_sysrwlcreate
	#define GET_sysrwlcreate(fl)  CAL_CMGETAPI( "sysrwlcreate" ) 
	#define CAL_sysrwlcreate  sysrwlcreate
	#define CHK_sysrwlcreate  TRUE
	#define EXP_sysrwlcreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlcreate", (RTS_UINTPTR)sysrwlcreate, 1, 0xC47B7841, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_sysrwlcreate  PFSYSRWLCREATE_IEC pfsysrwlcreate;
	#define EXT_sysrwlcreate  extern PFSYSRWLCREATE_IEC pfsysrwlcreate;
	#define GET_sysrwlcreate(fl)  s_pfCMGetAPI2( "sysrwlcreate", (RTS_VOID_FCTPTR *)&pfsysrwlcreate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xC47B7841, 0x03050B00)
	#define CAL_sysrwlcreate  pfsysrwlcreate
	#define CHK_sysrwlcreate  (pfsysrwlcreate != NULL)
	#define EXP_sysrwlcreate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlcreate", (RTS_UINTPTR)sysrwlcreate, 1, 0xC47B7841, 0x03050B00) 
#endif


/**
 * This function can be used to delete a ReadWrite locking object (synchronization object)
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysrwldelete_struct
{
	RTS_IEC_HANDLE hRWLock;				/* VAR_INPUT */	/* Handle to the ReadWrite lock object created by SysRWLCreate */
	RTS_IEC_RESULT SysRWLDelete;		/* VAR_OUTPUT */	
} sysrwldelete_struct;

void CDECL CDECL_EXT sysrwldelete(sysrwldelete_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSRWLDELETE_IEC) (sysrwldelete_struct *p);
#if defined(SYSREADWRITELOCK_NOTIMPLEMENTED) || defined(SYSRWLDELETE_NOTIMPLEMENTED)
	#define USE_sysrwldelete
	#define EXT_sysrwldelete
	#define GET_sysrwldelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysrwldelete(p0) 
	#define CHK_sysrwldelete  FALSE
	#define EXP_sysrwldelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysrwldelete
	#define EXT_sysrwldelete
	#define GET_sysrwldelete(fl)  CAL_CMGETAPI( "sysrwldelete" ) 
	#define CAL_sysrwldelete  sysrwldelete
	#define CHK_sysrwldelete  TRUE
	#define EXP_sysrwldelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwldelete", (RTS_UINTPTR)sysrwldelete, 1, 0x27A4A555, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(SYSREADWRITELOCK_EXTERNAL)
	#define USE_sysrwldelete
	#define EXT_sysrwldelete
	#define GET_sysrwldelete(fl)  CAL_CMGETAPI( "sysrwldelete" ) 
	#define CAL_sysrwldelete  sysrwldelete
	#define CHK_sysrwldelete  TRUE
	#define EXP_sysrwldelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwldelete", (RTS_UINTPTR)sysrwldelete, 1, 0x27A4A555, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysReadWriteLocksysrwldelete
	#define EXT_SysReadWriteLocksysrwldelete
	#define GET_SysReadWriteLocksysrwldelete  ERR_OK
	#define CAL_SysReadWriteLocksysrwldelete  sysrwldelete
	#define CHK_SysReadWriteLocksysrwldelete  TRUE
	#define EXP_SysReadWriteLocksysrwldelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwldelete", (RTS_UINTPTR)sysrwldelete, 1, 0x27A4A555, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_sysrwldelete
	#define EXT_sysrwldelete
	#define GET_sysrwldelete(fl)  CAL_CMGETAPI( "sysrwldelete" ) 
	#define CAL_sysrwldelete  sysrwldelete
	#define CHK_sysrwldelete  TRUE
	#define EXP_sysrwldelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwldelete", (RTS_UINTPTR)sysrwldelete, 1, 0x27A4A555, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_sysrwldelete  PFSYSRWLDELETE_IEC pfsysrwldelete;
	#define EXT_sysrwldelete  extern PFSYSRWLDELETE_IEC pfsysrwldelete;
	#define GET_sysrwldelete(fl)  s_pfCMGetAPI2( "sysrwldelete", (RTS_VOID_FCTPTR *)&pfsysrwldelete, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x27A4A555, 0x03050B00)
	#define CAL_sysrwldelete  pfsysrwldelete
	#define CHK_sysrwldelete  (pfsysrwldelete != NULL)
	#define EXP_sysrwldelete   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwldelete", (RTS_UINTPTR)sysrwldelete, 1, 0x27A4A555, 0x03050B00) 
#endif


/**
 * This function to enter a read lock(synchronization object). NOTE: Several readers can enter the lock simultaneously! But they are synchronized against an entered write lock!
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysrwlreadlock_struct
{
	RTS_IEC_HANDLE hRWLock;				/* VAR_INPUT */	/* Handle to the ReadWrite lock object created by SysRWLCreate */
	RTS_IEC_RESULT SysRWLReadLock;		/* VAR_OUTPUT */	
} sysrwlreadlock_struct;

void CDECL CDECL_EXT sysrwlreadlock(sysrwlreadlock_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSRWLREADLOCK_IEC) (sysrwlreadlock_struct *p);
#if defined(SYSREADWRITELOCK_NOTIMPLEMENTED) || defined(SYSRWLREADLOCK_NOTIMPLEMENTED)
	#define USE_sysrwlreadlock
	#define EXT_sysrwlreadlock
	#define GET_sysrwlreadlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysrwlreadlock(p0) 
	#define CHK_sysrwlreadlock  FALSE
	#define EXP_sysrwlreadlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysrwlreadlock
	#define EXT_sysrwlreadlock
	#define GET_sysrwlreadlock(fl)  CAL_CMGETAPI( "sysrwlreadlock" ) 
	#define CAL_sysrwlreadlock  sysrwlreadlock
	#define CHK_sysrwlreadlock  TRUE
	#define EXP_sysrwlreadlock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlreadlock", (RTS_UINTPTR)sysrwlreadlock, 1, 0x9CD9B449, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(SYSREADWRITELOCK_EXTERNAL)
	#define USE_sysrwlreadlock
	#define EXT_sysrwlreadlock
	#define GET_sysrwlreadlock(fl)  CAL_CMGETAPI( "sysrwlreadlock" ) 
	#define CAL_sysrwlreadlock  sysrwlreadlock
	#define CHK_sysrwlreadlock  TRUE
	#define EXP_sysrwlreadlock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlreadlock", (RTS_UINTPTR)sysrwlreadlock, 1, 0x9CD9B449, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysReadWriteLocksysrwlreadlock
	#define EXT_SysReadWriteLocksysrwlreadlock
	#define GET_SysReadWriteLocksysrwlreadlock  ERR_OK
	#define CAL_SysReadWriteLocksysrwlreadlock  sysrwlreadlock
	#define CHK_SysReadWriteLocksysrwlreadlock  TRUE
	#define EXP_SysReadWriteLocksysrwlreadlock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlreadlock", (RTS_UINTPTR)sysrwlreadlock, 1, 0x9CD9B449, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_sysrwlreadlock
	#define EXT_sysrwlreadlock
	#define GET_sysrwlreadlock(fl)  CAL_CMGETAPI( "sysrwlreadlock" ) 
	#define CAL_sysrwlreadlock  sysrwlreadlock
	#define CHK_sysrwlreadlock  TRUE
	#define EXP_sysrwlreadlock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlreadlock", (RTS_UINTPTR)sysrwlreadlock, 1, 0x9CD9B449, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_sysrwlreadlock  PFSYSRWLREADLOCK_IEC pfsysrwlreadlock;
	#define EXT_sysrwlreadlock  extern PFSYSRWLREADLOCK_IEC pfsysrwlreadlock;
	#define GET_sysrwlreadlock(fl)  s_pfCMGetAPI2( "sysrwlreadlock", (RTS_VOID_FCTPTR *)&pfsysrwlreadlock, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x9CD9B449, 0x03050B00)
	#define CAL_sysrwlreadlock  pfsysrwlreadlock
	#define CHK_sysrwlreadlock  (pfsysrwlreadlock != NULL)
	#define EXP_sysrwlreadlock   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlreadlock", (RTS_UINTPTR)sysrwlreadlock, 1, 0x9CD9B449, 0x03050B00) 
#endif


/**
 * This function tries enter a read lock(synchronization object). If a write lock is still active, the functions returns an error. The function succeeded as well, if another read lock
 * is still active.
 * NOTE: Several readers can enter the lock simultaneously! But they are synchronized against an entered write lock!
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysrwlreadlocktry_struct
{
	RTS_IEC_HANDLE hRWLock;				/* VAR_INPUT */	/* Handle to the ReadWrite lock object created by SysRWLCreate */
	RTS_IEC_RESULT SysRWLReadLockTry;	/* VAR_OUTPUT */	
} sysrwlreadlocktry_struct;

void CDECL CDECL_EXT sysrwlreadlocktry(sysrwlreadlocktry_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSRWLREADLOCKTRY_IEC) (sysrwlreadlocktry_struct *p);
#if defined(SYSREADWRITELOCK_NOTIMPLEMENTED) || defined(SYSRWLREADLOCKTRY_NOTIMPLEMENTED)
	#define USE_sysrwlreadlocktry
	#define EXT_sysrwlreadlocktry
	#define GET_sysrwlreadlocktry(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysrwlreadlocktry(p0) 
	#define CHK_sysrwlreadlocktry  FALSE
	#define EXP_sysrwlreadlocktry  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysrwlreadlocktry
	#define EXT_sysrwlreadlocktry
	#define GET_sysrwlreadlocktry(fl)  CAL_CMGETAPI( "sysrwlreadlocktry" ) 
	#define CAL_sysrwlreadlocktry  sysrwlreadlocktry
	#define CHK_sysrwlreadlocktry  TRUE
	#define EXP_sysrwlreadlocktry  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlreadlocktry", (RTS_UINTPTR)sysrwlreadlocktry, 1, 0x80D90810, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(SYSREADWRITELOCK_EXTERNAL)
	#define USE_sysrwlreadlocktry
	#define EXT_sysrwlreadlocktry
	#define GET_sysrwlreadlocktry(fl)  CAL_CMGETAPI( "sysrwlreadlocktry" ) 
	#define CAL_sysrwlreadlocktry  sysrwlreadlocktry
	#define CHK_sysrwlreadlocktry  TRUE
	#define EXP_sysrwlreadlocktry  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlreadlocktry", (RTS_UINTPTR)sysrwlreadlocktry, 1, 0x80D90810, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysReadWriteLocksysrwlreadlocktry
	#define EXT_SysReadWriteLocksysrwlreadlocktry
	#define GET_SysReadWriteLocksysrwlreadlocktry  ERR_OK
	#define CAL_SysReadWriteLocksysrwlreadlocktry  sysrwlreadlocktry
	#define CHK_SysReadWriteLocksysrwlreadlocktry  TRUE
	#define EXP_SysReadWriteLocksysrwlreadlocktry  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlreadlocktry", (RTS_UINTPTR)sysrwlreadlocktry, 1, 0x80D90810, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_sysrwlreadlocktry
	#define EXT_sysrwlreadlocktry
	#define GET_sysrwlreadlocktry(fl)  CAL_CMGETAPI( "sysrwlreadlocktry" ) 
	#define CAL_sysrwlreadlocktry  sysrwlreadlocktry
	#define CHK_sysrwlreadlocktry  TRUE
	#define EXP_sysrwlreadlocktry  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlreadlocktry", (RTS_UINTPTR)sysrwlreadlocktry, 1, 0x80D90810, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_sysrwlreadlocktry  PFSYSRWLREADLOCKTRY_IEC pfsysrwlreadlocktry;
	#define EXT_sysrwlreadlocktry  extern PFSYSRWLREADLOCKTRY_IEC pfsysrwlreadlocktry;
	#define GET_sysrwlreadlocktry(fl)  s_pfCMGetAPI2( "sysrwlreadlocktry", (RTS_VOID_FCTPTR *)&pfsysrwlreadlocktry, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x80D90810, 0x03050B00)
	#define CAL_sysrwlreadlocktry  pfsysrwlreadlocktry
	#define CHK_sysrwlreadlocktry  (pfsysrwlreadlocktry != NULL)
	#define EXP_sysrwlreadlocktry   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlreadlocktry", (RTS_UINTPTR)sysrwlreadlocktry, 1, 0x80D90810, 0x03050B00) 
#endif


/**
 * This function leaves a read lock, entered by SysRWLReadLock (synchronization object).
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysrwlreadunlock_struct
{
	RTS_IEC_HANDLE hRWLock;				/* VAR_INPUT */	/* Handle to the ReadWrite lock object created by SysRWLCreate */
	RTS_IEC_RESULT SysRWLReadUnlock;	/* VAR_OUTPUT */	
} sysrwlreadunlock_struct;

void CDECL CDECL_EXT sysrwlreadunlock(sysrwlreadunlock_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSRWLREADUNLOCK_IEC) (sysrwlreadunlock_struct *p);
#if defined(SYSREADWRITELOCK_NOTIMPLEMENTED) || defined(SYSRWLREADUNLOCK_NOTIMPLEMENTED)
	#define USE_sysrwlreadunlock
	#define EXT_sysrwlreadunlock
	#define GET_sysrwlreadunlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysrwlreadunlock(p0) 
	#define CHK_sysrwlreadunlock  FALSE
	#define EXP_sysrwlreadunlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysrwlreadunlock
	#define EXT_sysrwlreadunlock
	#define GET_sysrwlreadunlock(fl)  CAL_CMGETAPI( "sysrwlreadunlock" ) 
	#define CAL_sysrwlreadunlock  sysrwlreadunlock
	#define CHK_sysrwlreadunlock  TRUE
	#define EXP_sysrwlreadunlock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlreadunlock", (RTS_UINTPTR)sysrwlreadunlock, 1, 0x2F29EF04, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(SYSREADWRITELOCK_EXTERNAL)
	#define USE_sysrwlreadunlock
	#define EXT_sysrwlreadunlock
	#define GET_sysrwlreadunlock(fl)  CAL_CMGETAPI( "sysrwlreadunlock" ) 
	#define CAL_sysrwlreadunlock  sysrwlreadunlock
	#define CHK_sysrwlreadunlock  TRUE
	#define EXP_sysrwlreadunlock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlreadunlock", (RTS_UINTPTR)sysrwlreadunlock, 1, 0x2F29EF04, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysReadWriteLocksysrwlreadunlock
	#define EXT_SysReadWriteLocksysrwlreadunlock
	#define GET_SysReadWriteLocksysrwlreadunlock  ERR_OK
	#define CAL_SysReadWriteLocksysrwlreadunlock  sysrwlreadunlock
	#define CHK_SysReadWriteLocksysrwlreadunlock  TRUE
	#define EXP_SysReadWriteLocksysrwlreadunlock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlreadunlock", (RTS_UINTPTR)sysrwlreadunlock, 1, 0x2F29EF04, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_sysrwlreadunlock
	#define EXT_sysrwlreadunlock
	#define GET_sysrwlreadunlock(fl)  CAL_CMGETAPI( "sysrwlreadunlock" ) 
	#define CAL_sysrwlreadunlock  sysrwlreadunlock
	#define CHK_sysrwlreadunlock  TRUE
	#define EXP_sysrwlreadunlock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlreadunlock", (RTS_UINTPTR)sysrwlreadunlock, 1, 0x2F29EF04, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_sysrwlreadunlock  PFSYSRWLREADUNLOCK_IEC pfsysrwlreadunlock;
	#define EXT_sysrwlreadunlock  extern PFSYSRWLREADUNLOCK_IEC pfsysrwlreadunlock;
	#define GET_sysrwlreadunlock(fl)  s_pfCMGetAPI2( "sysrwlreadunlock", (RTS_VOID_FCTPTR *)&pfsysrwlreadunlock, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x2F29EF04, 0x03050B00)
	#define CAL_sysrwlreadunlock  pfsysrwlreadunlock
	#define CHK_sysrwlreadunlock  (pfsysrwlreadunlock != NULL)
	#define EXP_sysrwlreadunlock   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlreadunlock", (RTS_UINTPTR)sysrwlreadunlock, 1, 0x2F29EF04, 0x03050B00) 
#endif


/**
 * This function to enter a write lock(synchronization object). NOTE: Several readers can enter the lock simultaneously! But they are synchronized against an entered write lock!
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysrwlwritelock_struct
{
	RTS_IEC_HANDLE hRWLock;				/* VAR_INPUT */	/* Handle to the ReadWrite lock object created by SysRWLCreate */
	RTS_IEC_RESULT SysRWLWriteLock;		/* VAR_OUTPUT */	
} sysrwlwritelock_struct;

void CDECL CDECL_EXT sysrwlwritelock(sysrwlwritelock_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSRWLWRITELOCK_IEC) (sysrwlwritelock_struct *p);
#if defined(SYSREADWRITELOCK_NOTIMPLEMENTED) || defined(SYSRWLWRITELOCK_NOTIMPLEMENTED)
	#define USE_sysrwlwritelock
	#define EXT_sysrwlwritelock
	#define GET_sysrwlwritelock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysrwlwritelock(p0) 
	#define CHK_sysrwlwritelock  FALSE
	#define EXP_sysrwlwritelock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysrwlwritelock
	#define EXT_sysrwlwritelock
	#define GET_sysrwlwritelock(fl)  CAL_CMGETAPI( "sysrwlwritelock" ) 
	#define CAL_sysrwlwritelock  sysrwlwritelock
	#define CHK_sysrwlwritelock  TRUE
	#define EXP_sysrwlwritelock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlwritelock", (RTS_UINTPTR)sysrwlwritelock, 1, 0xCA2B1D08, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(SYSREADWRITELOCK_EXTERNAL)
	#define USE_sysrwlwritelock
	#define EXT_sysrwlwritelock
	#define GET_sysrwlwritelock(fl)  CAL_CMGETAPI( "sysrwlwritelock" ) 
	#define CAL_sysrwlwritelock  sysrwlwritelock
	#define CHK_sysrwlwritelock  TRUE
	#define EXP_sysrwlwritelock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlwritelock", (RTS_UINTPTR)sysrwlwritelock, 1, 0xCA2B1D08, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysReadWriteLocksysrwlwritelock
	#define EXT_SysReadWriteLocksysrwlwritelock
	#define GET_SysReadWriteLocksysrwlwritelock  ERR_OK
	#define CAL_SysReadWriteLocksysrwlwritelock  sysrwlwritelock
	#define CHK_SysReadWriteLocksysrwlwritelock  TRUE
	#define EXP_SysReadWriteLocksysrwlwritelock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlwritelock", (RTS_UINTPTR)sysrwlwritelock, 1, 0xCA2B1D08, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_sysrwlwritelock
	#define EXT_sysrwlwritelock
	#define GET_sysrwlwritelock(fl)  CAL_CMGETAPI( "sysrwlwritelock" ) 
	#define CAL_sysrwlwritelock  sysrwlwritelock
	#define CHK_sysrwlwritelock  TRUE
	#define EXP_sysrwlwritelock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlwritelock", (RTS_UINTPTR)sysrwlwritelock, 1, 0xCA2B1D08, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_sysrwlwritelock  PFSYSRWLWRITELOCK_IEC pfsysrwlwritelock;
	#define EXT_sysrwlwritelock  extern PFSYSRWLWRITELOCK_IEC pfsysrwlwritelock;
	#define GET_sysrwlwritelock(fl)  s_pfCMGetAPI2( "sysrwlwritelock", (RTS_VOID_FCTPTR *)&pfsysrwlwritelock, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xCA2B1D08, 0x03050B00)
	#define CAL_sysrwlwritelock  pfsysrwlwritelock
	#define CHK_sysrwlwritelock  (pfsysrwlwritelock != NULL)
	#define EXP_sysrwlwritelock   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlwritelock", (RTS_UINTPTR)sysrwlwritelock, 1, 0xCA2B1D08, 0x03050B00) 
#endif


/**
 * This function tries enter a write lock(synchronization object). If a write lock is still active, the functions returns an error.
 * NOTE: Several readers can enter the lock simultaneously! But they are synchronized against an entered write lock!
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysrwlwritelocktry_struct
{
	RTS_IEC_HANDLE hRWLock;				/* VAR_INPUT */	/* Handle to the ReadWrite lock object created by SysRWLCreate */
	RTS_IEC_RESULT SysRWLWriteLockTry;	/* VAR_OUTPUT */	
} sysrwlwritelocktry_struct;

void CDECL CDECL_EXT sysrwlwritelocktry(sysrwlwritelocktry_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSRWLWRITELOCKTRY_IEC) (sysrwlwritelocktry_struct *p);
#if defined(SYSREADWRITELOCK_NOTIMPLEMENTED) || defined(SYSRWLWRITELOCKTRY_NOTIMPLEMENTED)
	#define USE_sysrwlwritelocktry
	#define EXT_sysrwlwritelocktry
	#define GET_sysrwlwritelocktry(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysrwlwritelocktry(p0) 
	#define CHK_sysrwlwritelocktry  FALSE
	#define EXP_sysrwlwritelocktry  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysrwlwritelocktry
	#define EXT_sysrwlwritelocktry
	#define GET_sysrwlwritelocktry(fl)  CAL_CMGETAPI( "sysrwlwritelocktry" ) 
	#define CAL_sysrwlwritelocktry  sysrwlwritelocktry
	#define CHK_sysrwlwritelocktry  TRUE
	#define EXP_sysrwlwritelocktry  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlwritelocktry", (RTS_UINTPTR)sysrwlwritelocktry, 1, 0x26069BED, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(SYSREADWRITELOCK_EXTERNAL)
	#define USE_sysrwlwritelocktry
	#define EXT_sysrwlwritelocktry
	#define GET_sysrwlwritelocktry(fl)  CAL_CMGETAPI( "sysrwlwritelocktry" ) 
	#define CAL_sysrwlwritelocktry  sysrwlwritelocktry
	#define CHK_sysrwlwritelocktry  TRUE
	#define EXP_sysrwlwritelocktry  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlwritelocktry", (RTS_UINTPTR)sysrwlwritelocktry, 1, 0x26069BED, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysReadWriteLocksysrwlwritelocktry
	#define EXT_SysReadWriteLocksysrwlwritelocktry
	#define GET_SysReadWriteLocksysrwlwritelocktry  ERR_OK
	#define CAL_SysReadWriteLocksysrwlwritelocktry  sysrwlwritelocktry
	#define CHK_SysReadWriteLocksysrwlwritelocktry  TRUE
	#define EXP_SysReadWriteLocksysrwlwritelocktry  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlwritelocktry", (RTS_UINTPTR)sysrwlwritelocktry, 1, 0x26069BED, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_sysrwlwritelocktry
	#define EXT_sysrwlwritelocktry
	#define GET_sysrwlwritelocktry(fl)  CAL_CMGETAPI( "sysrwlwritelocktry" ) 
	#define CAL_sysrwlwritelocktry  sysrwlwritelocktry
	#define CHK_sysrwlwritelocktry  TRUE
	#define EXP_sysrwlwritelocktry  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlwritelocktry", (RTS_UINTPTR)sysrwlwritelocktry, 1, 0x26069BED, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_sysrwlwritelocktry  PFSYSRWLWRITELOCKTRY_IEC pfsysrwlwritelocktry;
	#define EXT_sysrwlwritelocktry  extern PFSYSRWLWRITELOCKTRY_IEC pfsysrwlwritelocktry;
	#define GET_sysrwlwritelocktry(fl)  s_pfCMGetAPI2( "sysrwlwritelocktry", (RTS_VOID_FCTPTR *)&pfsysrwlwritelocktry, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x26069BED, 0x03050B00)
	#define CAL_sysrwlwritelocktry  pfsysrwlwritelocktry
	#define CHK_sysrwlwritelocktry  (pfsysrwlwritelocktry != NULL)
	#define EXP_sysrwlwritelocktry   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlwritelocktry", (RTS_UINTPTR)sysrwlwritelocktry, 1, 0x26069BED, 0x03050B00) 
#endif


/**
 * This function leaves a write lock, entered by SysRWLReadLock (synchronization object).
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysrwlwriteunlock_struct
{
	RTS_IEC_HANDLE hRWLock;				/* VAR_INPUT */	/* Handle to the ReadWrite lock object created by SysRWLCreate */
	RTS_IEC_RESULT SysRWLWriteUnlock;	/* VAR_OUTPUT */	
} sysrwlwriteunlock_struct;

void CDECL CDECL_EXT sysrwlwriteunlock(sysrwlwriteunlock_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSRWLWRITEUNLOCK_IEC) (sysrwlwriteunlock_struct *p);
#if defined(SYSREADWRITELOCK_NOTIMPLEMENTED) || defined(SYSRWLWRITEUNLOCK_NOTIMPLEMENTED)
	#define USE_sysrwlwriteunlock
	#define EXT_sysrwlwriteunlock
	#define GET_sysrwlwriteunlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysrwlwriteunlock(p0) 
	#define CHK_sysrwlwriteunlock  FALSE
	#define EXP_sysrwlwriteunlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysrwlwriteunlock
	#define EXT_sysrwlwriteunlock
	#define GET_sysrwlwriteunlock(fl)  CAL_CMGETAPI( "sysrwlwriteunlock" ) 
	#define CAL_sysrwlwriteunlock  sysrwlwriteunlock
	#define CHK_sysrwlwriteunlock  TRUE
	#define EXP_sysrwlwriteunlock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlwriteunlock", (RTS_UINTPTR)sysrwlwriteunlock, 1, 0xDF9F26CB, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(SYSREADWRITELOCK_EXTERNAL)
	#define USE_sysrwlwriteunlock
	#define EXT_sysrwlwriteunlock
	#define GET_sysrwlwriteunlock(fl)  CAL_CMGETAPI( "sysrwlwriteunlock" ) 
	#define CAL_sysrwlwriteunlock  sysrwlwriteunlock
	#define CHK_sysrwlwriteunlock  TRUE
	#define EXP_sysrwlwriteunlock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlwriteunlock", (RTS_UINTPTR)sysrwlwriteunlock, 1, 0xDF9F26CB, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysReadWriteLocksysrwlwriteunlock
	#define EXT_SysReadWriteLocksysrwlwriteunlock
	#define GET_SysReadWriteLocksysrwlwriteunlock  ERR_OK
	#define CAL_SysReadWriteLocksysrwlwriteunlock  sysrwlwriteunlock
	#define CHK_SysReadWriteLocksysrwlwriteunlock  TRUE
	#define EXP_SysReadWriteLocksysrwlwriteunlock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlwriteunlock", (RTS_UINTPTR)sysrwlwriteunlock, 1, 0xDF9F26CB, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_sysrwlwriteunlock
	#define EXT_sysrwlwriteunlock
	#define GET_sysrwlwriteunlock(fl)  CAL_CMGETAPI( "sysrwlwriteunlock" ) 
	#define CAL_sysrwlwriteunlock  sysrwlwriteunlock
	#define CHK_sysrwlwriteunlock  TRUE
	#define EXP_sysrwlwriteunlock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlwriteunlock", (RTS_UINTPTR)sysrwlwriteunlock, 1, 0xDF9F26CB, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_sysrwlwriteunlock  PFSYSRWLWRITEUNLOCK_IEC pfsysrwlwriteunlock;
	#define EXT_sysrwlwriteunlock  extern PFSYSRWLWRITEUNLOCK_IEC pfsysrwlwriteunlock;
	#define GET_sysrwlwriteunlock(fl)  s_pfCMGetAPI2( "sysrwlwriteunlock", (RTS_VOID_FCTPTR *)&pfsysrwlwriteunlock, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xDF9F26CB, 0x03050B00)
	#define CAL_sysrwlwriteunlock  pfsysrwlwriteunlock
	#define CHK_sysrwlwriteunlock  (pfsysrwlwriteunlock != NULL)
	#define EXP_sysrwlwriteunlock   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysrwlwriteunlock", (RTS_UINTPTR)sysrwlwriteunlock, 1, 0xDF9F26CB, 0x03050B00) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysReadWriteLockOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysReadWriteLockOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>
 * This function creates a ReadWrite locking synchronization object.
 * </description>
 * <param name="pResult" type="IN">Pointer to a variable to return an errorcode (optional).</param>
 * <result>Returns a handle to the synchronization object or RTS_INVALID_HANDLE in case of failure.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">A valid handle is returned.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">Not enough memory available.</errorcode>
 */
RTS_HANDLE CDECL SysRWLCreate(RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSRWLCREATE) (RTS_RESULT *pResult);
#if defined(SYSREADWRITELOCK_NOTIMPLEMENTED) || defined(SYSRWLCREATE_NOTIMPLEMENTED)
	#define USE_SysRWLCreate
	#define EXT_SysRWLCreate
	#define GET_SysRWLCreate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysRWLCreate(p0)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysRWLCreate  FALSE
	#define EXP_SysRWLCreate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysRWLCreate
	#define EXT_SysRWLCreate
	#define GET_SysRWLCreate(fl)  CAL_CMGETAPI( "SysRWLCreate" ) 
	#define CAL_SysRWLCreate  SysRWLCreate
	#define CHK_SysRWLCreate  TRUE
	#define EXP_SysRWLCreate  CAL_CMEXPAPI( "SysRWLCreate" ) 
#elif defined(MIXED_LINK) && !defined(SYSREADWRITELOCK_EXTERNAL)
	#define USE_SysRWLCreate
	#define EXT_SysRWLCreate
	#define GET_SysRWLCreate(fl)  CAL_CMGETAPI( "SysRWLCreate" ) 
	#define CAL_SysRWLCreate  SysRWLCreate
	#define CHK_SysRWLCreate  TRUE
	#define EXP_SysRWLCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysRWLCreate", (RTS_UINTPTR)SysRWLCreate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysReadWriteLockSysRWLCreate
	#define EXT_SysReadWriteLockSysRWLCreate
	#define GET_SysReadWriteLockSysRWLCreate  ERR_OK
	#define CAL_SysReadWriteLockSysRWLCreate pISysReadWriteLock->ISysRWLCreate
	#define CHK_SysReadWriteLockSysRWLCreate (pISysReadWriteLock != NULL)
	#define EXP_SysReadWriteLockSysRWLCreate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysRWLCreate
	#define EXT_SysRWLCreate
	#define GET_SysRWLCreate(fl)  CAL_CMGETAPI( "SysRWLCreate" ) 
	#define CAL_SysRWLCreate pISysReadWriteLock->ISysRWLCreate
	#define CHK_SysRWLCreate (pISysReadWriteLock != NULL)
	#define EXP_SysRWLCreate  CAL_CMEXPAPI( "SysRWLCreate" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysRWLCreate  PFSYSRWLCREATE pfSysRWLCreate;
	#define EXT_SysRWLCreate  extern PFSYSRWLCREATE pfSysRWLCreate;
	#define GET_SysRWLCreate(fl)  s_pfCMGetAPI2( "SysRWLCreate", (RTS_VOID_FCTPTR *)&pfSysRWLCreate, (fl), 0, 0)
	#define CAL_SysRWLCreate  pfSysRWLCreate
	#define CHK_SysRWLCreate  (pfSysRWLCreate != NULL)
	#define EXP_SysRWLCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysRWLCreate", (RTS_UINTPTR)SysRWLCreate, 0, 0) 
#endif




/**
 * <description>
 * This function deletes a prior created ReadWrite locking synchronization object.
 * </description>
 * <param name="hRWLock" type="IN">Handle to the synchronization object</param>
 * <result>Returns the runtime system error code.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Success</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">The given handle is invalid</errorcode>
 */
RTS_RESULT CDECL SysRWLDelete(RTS_HANDLE hRWLock);
typedef RTS_RESULT (CDECL * PFSYSRWLDELETE) (RTS_HANDLE hRWLock);
#if defined(SYSREADWRITELOCK_NOTIMPLEMENTED) || defined(SYSRWLDELETE_NOTIMPLEMENTED)
	#define USE_SysRWLDelete
	#define EXT_SysRWLDelete
	#define GET_SysRWLDelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysRWLDelete(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysRWLDelete  FALSE
	#define EXP_SysRWLDelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysRWLDelete
	#define EXT_SysRWLDelete
	#define GET_SysRWLDelete(fl)  CAL_CMGETAPI( "SysRWLDelete" ) 
	#define CAL_SysRWLDelete  SysRWLDelete
	#define CHK_SysRWLDelete  TRUE
	#define EXP_SysRWLDelete  CAL_CMEXPAPI( "SysRWLDelete" ) 
#elif defined(MIXED_LINK) && !defined(SYSREADWRITELOCK_EXTERNAL)
	#define USE_SysRWLDelete
	#define EXT_SysRWLDelete
	#define GET_SysRWLDelete(fl)  CAL_CMGETAPI( "SysRWLDelete" ) 
	#define CAL_SysRWLDelete  SysRWLDelete
	#define CHK_SysRWLDelete  TRUE
	#define EXP_SysRWLDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysRWLDelete", (RTS_UINTPTR)SysRWLDelete, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysReadWriteLockSysRWLDelete
	#define EXT_SysReadWriteLockSysRWLDelete
	#define GET_SysReadWriteLockSysRWLDelete  ERR_OK
	#define CAL_SysReadWriteLockSysRWLDelete pISysReadWriteLock->ISysRWLDelete
	#define CHK_SysReadWriteLockSysRWLDelete (pISysReadWriteLock != NULL)
	#define EXP_SysReadWriteLockSysRWLDelete  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysRWLDelete
	#define EXT_SysRWLDelete
	#define GET_SysRWLDelete(fl)  CAL_CMGETAPI( "SysRWLDelete" ) 
	#define CAL_SysRWLDelete pISysReadWriteLock->ISysRWLDelete
	#define CHK_SysRWLDelete (pISysReadWriteLock != NULL)
	#define EXP_SysRWLDelete  CAL_CMEXPAPI( "SysRWLDelete" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysRWLDelete  PFSYSRWLDELETE pfSysRWLDelete;
	#define EXT_SysRWLDelete  extern PFSYSRWLDELETE pfSysRWLDelete;
	#define GET_SysRWLDelete(fl)  s_pfCMGetAPI2( "SysRWLDelete", (RTS_VOID_FCTPTR *)&pfSysRWLDelete, (fl), 0, 0)
	#define CAL_SysRWLDelete  pfSysRWLDelete
	#define CHK_SysRWLDelete  (pfSysRWLDelete != NULL)
	#define EXP_SysRWLDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysRWLDelete", (RTS_UINTPTR)SysRWLDelete, 0, 0) 
#endif




/**
 * <description>
 * <p>This function enters a read lock (synchronization object).</p>
 * NOTE: Several readers can enter the lock simultaneously! But they are synchronized against an entered write lock!
 * </description>
 * <param name="hRWLock" type="IN">Handle to the synchronization object</param>
 * <result>Returns the runtime system error code.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Success</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">The given handle is invalid</errorcode>
 */
RTS_RESULT CDECL SysRWLReadLock(RTS_HANDLE hRWLock);
typedef RTS_RESULT (CDECL * PFSYSRWLREADLOCK) (RTS_HANDLE hRWLock);
#if defined(SYSREADWRITELOCK_NOTIMPLEMENTED) || defined(SYSRWLREADLOCK_NOTIMPLEMENTED)
	#define USE_SysRWLReadLock
	#define EXT_SysRWLReadLock
	#define GET_SysRWLReadLock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysRWLReadLock(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysRWLReadLock  FALSE
	#define EXP_SysRWLReadLock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysRWLReadLock
	#define EXT_SysRWLReadLock
	#define GET_SysRWLReadLock(fl)  CAL_CMGETAPI( "SysRWLReadLock" ) 
	#define CAL_SysRWLReadLock  SysRWLReadLock
	#define CHK_SysRWLReadLock  TRUE
	#define EXP_SysRWLReadLock  CAL_CMEXPAPI( "SysRWLReadLock" ) 
#elif defined(MIXED_LINK) && !defined(SYSREADWRITELOCK_EXTERNAL)
	#define USE_SysRWLReadLock
	#define EXT_SysRWLReadLock
	#define GET_SysRWLReadLock(fl)  CAL_CMGETAPI( "SysRWLReadLock" ) 
	#define CAL_SysRWLReadLock  SysRWLReadLock
	#define CHK_SysRWLReadLock  TRUE
	#define EXP_SysRWLReadLock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysRWLReadLock", (RTS_UINTPTR)SysRWLReadLock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysReadWriteLockSysRWLReadLock
	#define EXT_SysReadWriteLockSysRWLReadLock
	#define GET_SysReadWriteLockSysRWLReadLock  ERR_OK
	#define CAL_SysReadWriteLockSysRWLReadLock pISysReadWriteLock->ISysRWLReadLock
	#define CHK_SysReadWriteLockSysRWLReadLock (pISysReadWriteLock != NULL)
	#define EXP_SysReadWriteLockSysRWLReadLock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysRWLReadLock
	#define EXT_SysRWLReadLock
	#define GET_SysRWLReadLock(fl)  CAL_CMGETAPI( "SysRWLReadLock" ) 
	#define CAL_SysRWLReadLock pISysReadWriteLock->ISysRWLReadLock
	#define CHK_SysRWLReadLock (pISysReadWriteLock != NULL)
	#define EXP_SysRWLReadLock  CAL_CMEXPAPI( "SysRWLReadLock" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysRWLReadLock  PFSYSRWLREADLOCK pfSysRWLReadLock;
	#define EXT_SysRWLReadLock  extern PFSYSRWLREADLOCK pfSysRWLReadLock;
	#define GET_SysRWLReadLock(fl)  s_pfCMGetAPI2( "SysRWLReadLock", (RTS_VOID_FCTPTR *)&pfSysRWLReadLock, (fl), 0, 0)
	#define CAL_SysRWLReadLock  pfSysRWLReadLock
	#define CHK_SysRWLReadLock  (pfSysRWLReadLock != NULL)
	#define EXP_SysRWLReadLock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysRWLReadLock", (RTS_UINTPTR)SysRWLReadLock, 0, 0) 
#endif




/**
 * <description>
 * <p>This function enters a write lock (synchronization object).</p>
 * NOTE: Several readers can enter the lock simultaneously! But they are synchronized against an entered write lock!
 * </description>
 * <param name="hRWLock" type="IN">Handle to the synchronization object</param>
 * <result>Returns the runtime system error code.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Success</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">The given handle is invalid</errorcode>
 */
RTS_RESULT CDECL SysRWLWriteLock(RTS_HANDLE hRWLock);
typedef RTS_RESULT (CDECL * PFSYSRWLWRITELOCK) (RTS_HANDLE hRWLock);
#if defined(SYSREADWRITELOCK_NOTIMPLEMENTED) || defined(SYSRWLWRITELOCK_NOTIMPLEMENTED)
	#define USE_SysRWLWriteLock
	#define EXT_SysRWLWriteLock
	#define GET_SysRWLWriteLock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysRWLWriteLock(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysRWLWriteLock  FALSE
	#define EXP_SysRWLWriteLock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysRWLWriteLock
	#define EXT_SysRWLWriteLock
	#define GET_SysRWLWriteLock(fl)  CAL_CMGETAPI( "SysRWLWriteLock" ) 
	#define CAL_SysRWLWriteLock  SysRWLWriteLock
	#define CHK_SysRWLWriteLock  TRUE
	#define EXP_SysRWLWriteLock  CAL_CMEXPAPI( "SysRWLWriteLock" ) 
#elif defined(MIXED_LINK) && !defined(SYSREADWRITELOCK_EXTERNAL)
	#define USE_SysRWLWriteLock
	#define EXT_SysRWLWriteLock
	#define GET_SysRWLWriteLock(fl)  CAL_CMGETAPI( "SysRWLWriteLock" ) 
	#define CAL_SysRWLWriteLock  SysRWLWriteLock
	#define CHK_SysRWLWriteLock  TRUE
	#define EXP_SysRWLWriteLock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysRWLWriteLock", (RTS_UINTPTR)SysRWLWriteLock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysReadWriteLockSysRWLWriteLock
	#define EXT_SysReadWriteLockSysRWLWriteLock
	#define GET_SysReadWriteLockSysRWLWriteLock  ERR_OK
	#define CAL_SysReadWriteLockSysRWLWriteLock pISysReadWriteLock->ISysRWLWriteLock
	#define CHK_SysReadWriteLockSysRWLWriteLock (pISysReadWriteLock != NULL)
	#define EXP_SysReadWriteLockSysRWLWriteLock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysRWLWriteLock
	#define EXT_SysRWLWriteLock
	#define GET_SysRWLWriteLock(fl)  CAL_CMGETAPI( "SysRWLWriteLock" ) 
	#define CAL_SysRWLWriteLock pISysReadWriteLock->ISysRWLWriteLock
	#define CHK_SysRWLWriteLock (pISysReadWriteLock != NULL)
	#define EXP_SysRWLWriteLock  CAL_CMEXPAPI( "SysRWLWriteLock" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysRWLWriteLock  PFSYSRWLWRITELOCK pfSysRWLWriteLock;
	#define EXT_SysRWLWriteLock  extern PFSYSRWLWRITELOCK pfSysRWLWriteLock;
	#define GET_SysRWLWriteLock(fl)  s_pfCMGetAPI2( "SysRWLWriteLock", (RTS_VOID_FCTPTR *)&pfSysRWLWriteLock, (fl), 0, 0)
	#define CAL_SysRWLWriteLock  pfSysRWLWriteLock
	#define CHK_SysRWLWriteLock  (pfSysRWLWriteLock != NULL)
	#define EXP_SysRWLWriteLock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysRWLWriteLock", (RTS_UINTPTR)SysRWLWriteLock, 0, 0) 
#endif




/**
 * <description>
 * <p>This function tries to enter a read lock (synchronization object).</p>
 * If a write lock is still active, the functions returns ERR_FAILED. On the other hand the function succeeds, even though another read lock is still active.
 * NOTE: Several readers can enter the lock simultaneously! But they are synchronized against an entered write lock!
 * </description>
 * <param name="hRWLock" type="IN">Handle to the synchronization object</param>
 * <result>Returns the runtime system error code.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Success</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">The lock can't be entered.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">The given handle is invalid</errorcode>
 */
RTS_RESULT CDECL SysRWLReadLockTry(RTS_HANDLE hRWLock);
typedef RTS_RESULT (CDECL * PFSYSRWLREADLOCKTRY) (RTS_HANDLE hRWLock);
#if defined(SYSREADWRITELOCK_NOTIMPLEMENTED) || defined(SYSRWLREADLOCKTRY_NOTIMPLEMENTED)
	#define USE_SysRWLReadLockTry
	#define EXT_SysRWLReadLockTry
	#define GET_SysRWLReadLockTry(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysRWLReadLockTry(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysRWLReadLockTry  FALSE
	#define EXP_SysRWLReadLockTry  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysRWLReadLockTry
	#define EXT_SysRWLReadLockTry
	#define GET_SysRWLReadLockTry(fl)  CAL_CMGETAPI( "SysRWLReadLockTry" ) 
	#define CAL_SysRWLReadLockTry  SysRWLReadLockTry
	#define CHK_SysRWLReadLockTry  TRUE
	#define EXP_SysRWLReadLockTry  CAL_CMEXPAPI( "SysRWLReadLockTry" ) 
#elif defined(MIXED_LINK) && !defined(SYSREADWRITELOCK_EXTERNAL)
	#define USE_SysRWLReadLockTry
	#define EXT_SysRWLReadLockTry
	#define GET_SysRWLReadLockTry(fl)  CAL_CMGETAPI( "SysRWLReadLockTry" ) 
	#define CAL_SysRWLReadLockTry  SysRWLReadLockTry
	#define CHK_SysRWLReadLockTry  TRUE
	#define EXP_SysRWLReadLockTry  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysRWLReadLockTry", (RTS_UINTPTR)SysRWLReadLockTry, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysReadWriteLockSysRWLReadLockTry
	#define EXT_SysReadWriteLockSysRWLReadLockTry
	#define GET_SysReadWriteLockSysRWLReadLockTry  ERR_OK
	#define CAL_SysReadWriteLockSysRWLReadLockTry pISysReadWriteLock->ISysRWLReadLockTry
	#define CHK_SysReadWriteLockSysRWLReadLockTry (pISysReadWriteLock != NULL)
	#define EXP_SysReadWriteLockSysRWLReadLockTry  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysRWLReadLockTry
	#define EXT_SysRWLReadLockTry
	#define GET_SysRWLReadLockTry(fl)  CAL_CMGETAPI( "SysRWLReadLockTry" ) 
	#define CAL_SysRWLReadLockTry pISysReadWriteLock->ISysRWLReadLockTry
	#define CHK_SysRWLReadLockTry (pISysReadWriteLock != NULL)
	#define EXP_SysRWLReadLockTry  CAL_CMEXPAPI( "SysRWLReadLockTry" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysRWLReadLockTry  PFSYSRWLREADLOCKTRY pfSysRWLReadLockTry;
	#define EXT_SysRWLReadLockTry  extern PFSYSRWLREADLOCKTRY pfSysRWLReadLockTry;
	#define GET_SysRWLReadLockTry(fl)  s_pfCMGetAPI2( "SysRWLReadLockTry", (RTS_VOID_FCTPTR *)&pfSysRWLReadLockTry, (fl), 0, 0)
	#define CAL_SysRWLReadLockTry  pfSysRWLReadLockTry
	#define CHK_SysRWLReadLockTry  (pfSysRWLReadLockTry != NULL)
	#define EXP_SysRWLReadLockTry  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysRWLReadLockTry", (RTS_UINTPTR)SysRWLReadLockTry, 0, 0) 
#endif




/**
 * <description>
 * <p> This function tries to enter a write lock (synchronization object).</p>
 * If a write lock is still active, the functions returns ERR_FAILED.
 * NOTE: Several readers can enter the lock simultaneously! But they are synchronized against an entered write lock!
 * </description>
 * <param name="hRWLock" type="IN">Handle to the synchronization object</param>
 * <result>Returns the runtime system error code.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Success</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">The lock can't be entered.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">The given handle is invalid</errorcode>
 */
RTS_RESULT CDECL SysRWLWriteLockTry(RTS_HANDLE hRWLock);
typedef RTS_RESULT (CDECL * PFSYSRWLWRITELOCKTRY) (RTS_HANDLE hRWLock);
#if defined(SYSREADWRITELOCK_NOTIMPLEMENTED) || defined(SYSRWLWRITELOCKTRY_NOTIMPLEMENTED)
	#define USE_SysRWLWriteLockTry
	#define EXT_SysRWLWriteLockTry
	#define GET_SysRWLWriteLockTry(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysRWLWriteLockTry(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysRWLWriteLockTry  FALSE
	#define EXP_SysRWLWriteLockTry  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysRWLWriteLockTry
	#define EXT_SysRWLWriteLockTry
	#define GET_SysRWLWriteLockTry(fl)  CAL_CMGETAPI( "SysRWLWriteLockTry" ) 
	#define CAL_SysRWLWriteLockTry  SysRWLWriteLockTry
	#define CHK_SysRWLWriteLockTry  TRUE
	#define EXP_SysRWLWriteLockTry  CAL_CMEXPAPI( "SysRWLWriteLockTry" ) 
#elif defined(MIXED_LINK) && !defined(SYSREADWRITELOCK_EXTERNAL)
	#define USE_SysRWLWriteLockTry
	#define EXT_SysRWLWriteLockTry
	#define GET_SysRWLWriteLockTry(fl)  CAL_CMGETAPI( "SysRWLWriteLockTry" ) 
	#define CAL_SysRWLWriteLockTry  SysRWLWriteLockTry
	#define CHK_SysRWLWriteLockTry  TRUE
	#define EXP_SysRWLWriteLockTry  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysRWLWriteLockTry", (RTS_UINTPTR)SysRWLWriteLockTry, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysReadWriteLockSysRWLWriteLockTry
	#define EXT_SysReadWriteLockSysRWLWriteLockTry
	#define GET_SysReadWriteLockSysRWLWriteLockTry  ERR_OK
	#define CAL_SysReadWriteLockSysRWLWriteLockTry pISysReadWriteLock->ISysRWLWriteLockTry
	#define CHK_SysReadWriteLockSysRWLWriteLockTry (pISysReadWriteLock != NULL)
	#define EXP_SysReadWriteLockSysRWLWriteLockTry  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysRWLWriteLockTry
	#define EXT_SysRWLWriteLockTry
	#define GET_SysRWLWriteLockTry(fl)  CAL_CMGETAPI( "SysRWLWriteLockTry" ) 
	#define CAL_SysRWLWriteLockTry pISysReadWriteLock->ISysRWLWriteLockTry
	#define CHK_SysRWLWriteLockTry (pISysReadWriteLock != NULL)
	#define EXP_SysRWLWriteLockTry  CAL_CMEXPAPI( "SysRWLWriteLockTry" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysRWLWriteLockTry  PFSYSRWLWRITELOCKTRY pfSysRWLWriteLockTry;
	#define EXT_SysRWLWriteLockTry  extern PFSYSRWLWRITELOCKTRY pfSysRWLWriteLockTry;
	#define GET_SysRWLWriteLockTry(fl)  s_pfCMGetAPI2( "SysRWLWriteLockTry", (RTS_VOID_FCTPTR *)&pfSysRWLWriteLockTry, (fl), 0, 0)
	#define CAL_SysRWLWriteLockTry  pfSysRWLWriteLockTry
	#define CHK_SysRWLWriteLockTry  (pfSysRWLWriteLockTry != NULL)
	#define EXP_SysRWLWriteLockTry  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysRWLWriteLockTry", (RTS_UINTPTR)SysRWLWriteLockTry, 0, 0) 
#endif




/**
 * <description>
 * This function leaves a read lock, entered by SysRWLReadLock (synchronization object).
 * </description>
 * <param name="hRWLock" type="IN">Handle to the synchronization object</param>
 * <result>Returns the runtime system error code.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Success</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">The given handle is invalid</errorcode>
 */
RTS_RESULT CDECL SysRWLReadUnlock(RTS_HANDLE hRWLock);
typedef RTS_RESULT (CDECL * PFSYSRWLREADUNLOCK) (RTS_HANDLE hRWLock);
#if defined(SYSREADWRITELOCK_NOTIMPLEMENTED) || defined(SYSRWLREADUNLOCK_NOTIMPLEMENTED)
	#define USE_SysRWLReadUnlock
	#define EXT_SysRWLReadUnlock
	#define GET_SysRWLReadUnlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysRWLReadUnlock(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysRWLReadUnlock  FALSE
	#define EXP_SysRWLReadUnlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysRWLReadUnlock
	#define EXT_SysRWLReadUnlock
	#define GET_SysRWLReadUnlock(fl)  CAL_CMGETAPI( "SysRWLReadUnlock" ) 
	#define CAL_SysRWLReadUnlock  SysRWLReadUnlock
	#define CHK_SysRWLReadUnlock  TRUE
	#define EXP_SysRWLReadUnlock  CAL_CMEXPAPI( "SysRWLReadUnlock" ) 
#elif defined(MIXED_LINK) && !defined(SYSREADWRITELOCK_EXTERNAL)
	#define USE_SysRWLReadUnlock
	#define EXT_SysRWLReadUnlock
	#define GET_SysRWLReadUnlock(fl)  CAL_CMGETAPI( "SysRWLReadUnlock" ) 
	#define CAL_SysRWLReadUnlock  SysRWLReadUnlock
	#define CHK_SysRWLReadUnlock  TRUE
	#define EXP_SysRWLReadUnlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysRWLReadUnlock", (RTS_UINTPTR)SysRWLReadUnlock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysReadWriteLockSysRWLReadUnlock
	#define EXT_SysReadWriteLockSysRWLReadUnlock
	#define GET_SysReadWriteLockSysRWLReadUnlock  ERR_OK
	#define CAL_SysReadWriteLockSysRWLReadUnlock pISysReadWriteLock->ISysRWLReadUnlock
	#define CHK_SysReadWriteLockSysRWLReadUnlock (pISysReadWriteLock != NULL)
	#define EXP_SysReadWriteLockSysRWLReadUnlock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysRWLReadUnlock
	#define EXT_SysRWLReadUnlock
	#define GET_SysRWLReadUnlock(fl)  CAL_CMGETAPI( "SysRWLReadUnlock" ) 
	#define CAL_SysRWLReadUnlock pISysReadWriteLock->ISysRWLReadUnlock
	#define CHK_SysRWLReadUnlock (pISysReadWriteLock != NULL)
	#define EXP_SysRWLReadUnlock  CAL_CMEXPAPI( "SysRWLReadUnlock" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysRWLReadUnlock  PFSYSRWLREADUNLOCK pfSysRWLReadUnlock;
	#define EXT_SysRWLReadUnlock  extern PFSYSRWLREADUNLOCK pfSysRWLReadUnlock;
	#define GET_SysRWLReadUnlock(fl)  s_pfCMGetAPI2( "SysRWLReadUnlock", (RTS_VOID_FCTPTR *)&pfSysRWLReadUnlock, (fl), 0, 0)
	#define CAL_SysRWLReadUnlock  pfSysRWLReadUnlock
	#define CHK_SysRWLReadUnlock  (pfSysRWLReadUnlock != NULL)
	#define EXP_SysRWLReadUnlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysRWLReadUnlock", (RTS_UINTPTR)SysRWLReadUnlock, 0, 0) 
#endif




/**
 * <description>
 * This function leaves a write lock, entered by SysRWLWriteLock (synchronization object).
 * </description>
 * <param name="hRWLock" type="IN">Handle to the synchronization object</param>
 * <result>Returns the runtime system error code.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Success</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">The given handle is invalid</errorcode>
 */
RTS_RESULT CDECL SysRWLWriteUnlock(RTS_HANDLE hRWLock);
typedef RTS_RESULT (CDECL * PFSYSRWLWRITEUNLOCK) (RTS_HANDLE hRWLock);
#if defined(SYSREADWRITELOCK_NOTIMPLEMENTED) || defined(SYSRWLWRITEUNLOCK_NOTIMPLEMENTED)
	#define USE_SysRWLWriteUnlock
	#define EXT_SysRWLWriteUnlock
	#define GET_SysRWLWriteUnlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysRWLWriteUnlock(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysRWLWriteUnlock  FALSE
	#define EXP_SysRWLWriteUnlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysRWLWriteUnlock
	#define EXT_SysRWLWriteUnlock
	#define GET_SysRWLWriteUnlock(fl)  CAL_CMGETAPI( "SysRWLWriteUnlock" ) 
	#define CAL_SysRWLWriteUnlock  SysRWLWriteUnlock
	#define CHK_SysRWLWriteUnlock  TRUE
	#define EXP_SysRWLWriteUnlock  CAL_CMEXPAPI( "SysRWLWriteUnlock" ) 
#elif defined(MIXED_LINK) && !defined(SYSREADWRITELOCK_EXTERNAL)
	#define USE_SysRWLWriteUnlock
	#define EXT_SysRWLWriteUnlock
	#define GET_SysRWLWriteUnlock(fl)  CAL_CMGETAPI( "SysRWLWriteUnlock" ) 
	#define CAL_SysRWLWriteUnlock  SysRWLWriteUnlock
	#define CHK_SysRWLWriteUnlock  TRUE
	#define EXP_SysRWLWriteUnlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysRWLWriteUnlock", (RTS_UINTPTR)SysRWLWriteUnlock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysReadWriteLockSysRWLWriteUnlock
	#define EXT_SysReadWriteLockSysRWLWriteUnlock
	#define GET_SysReadWriteLockSysRWLWriteUnlock  ERR_OK
	#define CAL_SysReadWriteLockSysRWLWriteUnlock pISysReadWriteLock->ISysRWLWriteUnlock
	#define CHK_SysReadWriteLockSysRWLWriteUnlock (pISysReadWriteLock != NULL)
	#define EXP_SysReadWriteLockSysRWLWriteUnlock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysRWLWriteUnlock
	#define EXT_SysRWLWriteUnlock
	#define GET_SysRWLWriteUnlock(fl)  CAL_CMGETAPI( "SysRWLWriteUnlock" ) 
	#define CAL_SysRWLWriteUnlock pISysReadWriteLock->ISysRWLWriteUnlock
	#define CHK_SysRWLWriteUnlock (pISysReadWriteLock != NULL)
	#define EXP_SysRWLWriteUnlock  CAL_CMEXPAPI( "SysRWLWriteUnlock" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysRWLWriteUnlock  PFSYSRWLWRITEUNLOCK pfSysRWLWriteUnlock;
	#define EXT_SysRWLWriteUnlock  extern PFSYSRWLWRITEUNLOCK pfSysRWLWriteUnlock;
	#define GET_SysRWLWriteUnlock(fl)  s_pfCMGetAPI2( "SysRWLWriteUnlock", (RTS_VOID_FCTPTR *)&pfSysRWLWriteUnlock, (fl), 0, 0)
	#define CAL_SysRWLWriteUnlock  pfSysRWLWriteUnlock
	#define CHK_SysRWLWriteUnlock  (pfSysRWLWriteUnlock != NULL)
	#define EXP_SysRWLWriteUnlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysRWLWriteUnlock", (RTS_UINTPTR)SysRWLWriteUnlock, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSYSRWLCREATE ISysRWLCreate;
 	PFSYSRWLDELETE ISysRWLDelete;
 	PFSYSRWLREADLOCK ISysRWLReadLock;
 	PFSYSRWLWRITELOCK ISysRWLWriteLock;
 	PFSYSRWLREADLOCKTRY ISysRWLReadLockTry;
 	PFSYSRWLWRITELOCKTRY ISysRWLWriteLockTry;
 	PFSYSRWLREADUNLOCK ISysRWLReadUnlock;
 	PFSYSRWLWRITEUNLOCK ISysRWLWriteUnlock;
 } ISysReadWriteLock_C;

#ifdef CPLUSPLUS
class ISysReadWriteLock : public IBase
{
	public:
		virtual RTS_HANDLE CDECL ISysRWLCreate(RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISysRWLDelete(RTS_HANDLE hRWLock) =0;
		virtual RTS_RESULT CDECL ISysRWLReadLock(RTS_HANDLE hRWLock) =0;
		virtual RTS_RESULT CDECL ISysRWLWriteLock(RTS_HANDLE hRWLock) =0;
		virtual RTS_RESULT CDECL ISysRWLReadLockTry(RTS_HANDLE hRWLock) =0;
		virtual RTS_RESULT CDECL ISysRWLWriteLockTry(RTS_HANDLE hRWLock) =0;
		virtual RTS_RESULT CDECL ISysRWLReadUnlock(RTS_HANDLE hRWLock) =0;
		virtual RTS_RESULT CDECL ISysRWLWriteUnlock(RTS_HANDLE hRWLock) =0;
};
	#ifndef ITF_SysReadWriteLock
		#define ITF_SysReadWriteLock static ISysReadWriteLock *pISysReadWriteLock = NULL;
	#endif
	#define EXTITF_SysReadWriteLock
#else	/*CPLUSPLUS*/
	typedef ISysReadWriteLock_C		ISysReadWriteLock;
	#ifndef ITF_SysReadWriteLock
		#define ITF_SysReadWriteLock
	#endif
	#define EXTITF_SysReadWriteLock
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSREADWRITELOCKITF_H_*/
