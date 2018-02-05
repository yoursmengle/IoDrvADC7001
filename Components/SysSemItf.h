 /**
 * <interfacename>SysSem</interfacename>
 * <description> 
 *	<p>The SysSem interface is projected to handle synchonization objects for tasks and threads.
 *	The synchronization objects are called semaphores to synchronize concurrent access to single
 *	data resources.</p>
 *	<p>For example:</p>
 *	<p>	Task1:
 *			...
 *			SysSemEnter(hSem);
 *			[Here you can accessed the protected data]
 *			SysSemLeave(hSem);
 *			[After SysSemLeave() you must not access the protected data]
 *			....
 *	</p>
 *	<p>
 *		IMPLEMENTATION NOTE:
 *		The semaphores must work recursive! That means, that a multiple call out of one task
 *		must not block the execution! For each SysSemEnter() call, a corresponding SysSemLeave()
 *		must be used!
 *		For this feature, binary sempahores are typically used.
 *	</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _SYSSEMITF_H_
#define _SYSSEMITF_H_

#include "CmpStd.h"

 

 




#include "CmpStd.h"

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 *This function can be used to create a semaphore (synchronization object)
 * RETURN: Handle to the semaphore or RTS_INVALID_HANDLE if failed
 */
typedef struct tagsyssemcreate_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors.library) */
	RTS_IEC_HANDLE SysSemCreate;		/* VAR_OUTPUT */	
} syssemcreate_struct;

void CDECL CDECL_EXT syssemcreate(syssemcreate_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSSEMCREATE_IEC) (syssemcreate_struct *p);
#if defined(SYSSEM_NOTIMPLEMENTED) || defined(SYSSEMCREATE_NOTIMPLEMENTED)
	#define USE_syssemcreate
	#define EXT_syssemcreate
	#define GET_syssemcreate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syssemcreate(p0) 
	#define CHK_syssemcreate  FALSE
	#define EXP_syssemcreate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syssemcreate
	#define EXT_syssemcreate
	#define GET_syssemcreate(fl)  CAL_CMGETAPI( "syssemcreate" ) 
	#define CAL_syssemcreate  syssemcreate
	#define CHK_syssemcreate  TRUE
	#define EXP_syssemcreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemcreate", (RTS_UINTPTR)syssemcreate, 1, RTSITF_GET_SIGNATURE(0, 0x9344C747), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSSEM_EXTERNAL)
	#define USE_syssemcreate
	#define EXT_syssemcreate
	#define GET_syssemcreate(fl)  CAL_CMGETAPI( "syssemcreate" ) 
	#define CAL_syssemcreate  syssemcreate
	#define CHK_syssemcreate  TRUE
	#define EXP_syssemcreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemcreate", (RTS_UINTPTR)syssemcreate, 1, RTSITF_GET_SIGNATURE(0, 0x9344C747), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysSemsyssemcreate
	#define EXT_SysSemsyssemcreate
	#define GET_SysSemsyssemcreate  ERR_OK
	#define CAL_SysSemsyssemcreate  syssemcreate
	#define CHK_SysSemsyssemcreate  TRUE
	#define EXP_SysSemsyssemcreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemcreate", (RTS_UINTPTR)syssemcreate, 1, RTSITF_GET_SIGNATURE(0, 0x9344C747), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_syssemcreate
	#define EXT_syssemcreate
	#define GET_syssemcreate(fl)  CAL_CMGETAPI( "syssemcreate" ) 
	#define CAL_syssemcreate  syssemcreate
	#define CHK_syssemcreate  TRUE
	#define EXP_syssemcreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemcreate", (RTS_UINTPTR)syssemcreate, 1, RTSITF_GET_SIGNATURE(0, 0x9344C747), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_syssemcreate  PFSYSSEMCREATE_IEC pfsyssemcreate;
	#define EXT_syssemcreate  extern PFSYSSEMCREATE_IEC pfsyssemcreate;
	#define GET_syssemcreate(fl)  s_pfCMGetAPI2( "syssemcreate", (RTS_VOID_FCTPTR *)&pfsyssemcreate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x9344C747), 0x03050500)
	#define CAL_syssemcreate  pfsyssemcreate
	#define CHK_syssemcreate  (pfsyssemcreate != NULL)
	#define EXP_syssemcreate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemcreate", (RTS_UINTPTR)syssemcreate, 1, RTSITF_GET_SIGNATURE(0, 0x9344C747), 0x03050500) 
#endif


/**
 * This function deletes the semaphore which is identified by its handle
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsyssemdelete_struct
{
	RTS_IEC_HANDLE hSem;				/* VAR_INPUT */	/* Handle of the semaphore */
	RTS_IEC_RESULT SysSemDelete;		/* VAR_OUTPUT */	
} syssemdelete_struct;

void CDECL CDECL_EXT syssemdelete(syssemdelete_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSSEMDELETE_IEC) (syssemdelete_struct *p);
#if defined(SYSSEM_NOTIMPLEMENTED) || defined(SYSSEMDELETE_NOTIMPLEMENTED)
	#define USE_syssemdelete
	#define EXT_syssemdelete
	#define GET_syssemdelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syssemdelete(p0) 
	#define CHK_syssemdelete  FALSE
	#define EXP_syssemdelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syssemdelete
	#define EXT_syssemdelete
	#define GET_syssemdelete(fl)  CAL_CMGETAPI( "syssemdelete" ) 
	#define CAL_syssemdelete  syssemdelete
	#define CHK_syssemdelete  TRUE
	#define EXP_syssemdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemdelete", (RTS_UINTPTR)syssemdelete, 1, RTSITF_GET_SIGNATURE(0, 0x88B7C7F6), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSSEM_EXTERNAL)
	#define USE_syssemdelete
	#define EXT_syssemdelete
	#define GET_syssemdelete(fl)  CAL_CMGETAPI( "syssemdelete" ) 
	#define CAL_syssemdelete  syssemdelete
	#define CHK_syssemdelete  TRUE
	#define EXP_syssemdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemdelete", (RTS_UINTPTR)syssemdelete, 1, RTSITF_GET_SIGNATURE(0, 0x88B7C7F6), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysSemsyssemdelete
	#define EXT_SysSemsyssemdelete
	#define GET_SysSemsyssemdelete  ERR_OK
	#define CAL_SysSemsyssemdelete  syssemdelete
	#define CHK_SysSemsyssemdelete  TRUE
	#define EXP_SysSemsyssemdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemdelete", (RTS_UINTPTR)syssemdelete, 1, RTSITF_GET_SIGNATURE(0, 0x88B7C7F6), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_syssemdelete
	#define EXT_syssemdelete
	#define GET_syssemdelete(fl)  CAL_CMGETAPI( "syssemdelete" ) 
	#define CAL_syssemdelete  syssemdelete
	#define CHK_syssemdelete  TRUE
	#define EXP_syssemdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemdelete", (RTS_UINTPTR)syssemdelete, 1, RTSITF_GET_SIGNATURE(0, 0x88B7C7F6), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_syssemdelete  PFSYSSEMDELETE_IEC pfsyssemdelete;
	#define EXT_syssemdelete  extern PFSYSSEMDELETE_IEC pfsyssemdelete;
	#define GET_syssemdelete(fl)  s_pfCMGetAPI2( "syssemdelete", (RTS_VOID_FCTPTR *)&pfsyssemdelete, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x88B7C7F6), 0x03050500)
	#define CAL_syssemdelete  pfsyssemdelete
	#define CHK_syssemdelete  (pfsyssemdelete != NULL)
	#define EXP_syssemdelete   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemdelete", (RTS_UINTPTR)syssemdelete, 1, RTSITF_GET_SIGNATURE(0, 0x88B7C7F6), 0x03050500) 
#endif


/**
 * This function must be called before a task accesses data which also are used by other tasks.
 * Thus the data will be bocked for other tasks, which also use SysSemEnter until by function SysSemLeave the semaphore
 * will be set free again. The semaphore is identified by its handle.</description>
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsyssementer_struct
{
	RTS_IEC_HANDLE hSem;				/* VAR_INPUT */	/* Handle of the semaphore */
	RTS_IEC_RESULT SysSemEnter;			/* VAR_OUTPUT */	
} syssementer_struct;

void CDECL CDECL_EXT syssementer(syssementer_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSSEMENTER_IEC) (syssementer_struct *p);
#if defined(SYSSEM_NOTIMPLEMENTED) || defined(SYSSEMENTER_NOTIMPLEMENTED)
	#define USE_syssementer
	#define EXT_syssementer
	#define GET_syssementer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syssementer(p0) 
	#define CHK_syssementer  FALSE
	#define EXP_syssementer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syssementer
	#define EXT_syssementer
	#define GET_syssementer(fl)  CAL_CMGETAPI( "syssementer" ) 
	#define CAL_syssementer  syssementer
	#define CHK_syssementer  TRUE
	#define EXP_syssementer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssementer", (RTS_UINTPTR)syssementer, 1, RTSITF_GET_SIGNATURE(0, 0x85E1C5F9), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSSEM_EXTERNAL)
	#define USE_syssementer
	#define EXT_syssementer
	#define GET_syssementer(fl)  CAL_CMGETAPI( "syssementer" ) 
	#define CAL_syssementer  syssementer
	#define CHK_syssementer  TRUE
	#define EXP_syssementer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssementer", (RTS_UINTPTR)syssementer, 1, RTSITF_GET_SIGNATURE(0, 0x85E1C5F9), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysSemsyssementer
	#define EXT_SysSemsyssementer
	#define GET_SysSemsyssementer  ERR_OK
	#define CAL_SysSemsyssementer  syssementer
	#define CHK_SysSemsyssementer  TRUE
	#define EXP_SysSemsyssementer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssementer", (RTS_UINTPTR)syssementer, 1, RTSITF_GET_SIGNATURE(0, 0x85E1C5F9), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_syssementer
	#define EXT_syssementer
	#define GET_syssementer(fl)  CAL_CMGETAPI( "syssementer" ) 
	#define CAL_syssementer  syssementer
	#define CHK_syssementer  TRUE
	#define EXP_syssementer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssementer", (RTS_UINTPTR)syssementer, 1, RTSITF_GET_SIGNATURE(0, 0x85E1C5F9), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_syssementer  PFSYSSEMENTER_IEC pfsyssementer;
	#define EXT_syssementer  extern PFSYSSEMENTER_IEC pfsyssementer;
	#define GET_syssementer(fl)  s_pfCMGetAPI2( "syssementer", (RTS_VOID_FCTPTR *)&pfsyssementer, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x85E1C5F9), 0x03050500)
	#define CAL_syssementer  pfsyssementer
	#define CHK_syssementer  (pfsyssementer != NULL)
	#define EXP_syssementer   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssementer", (RTS_UINTPTR)syssementer, 1, RTSITF_GET_SIGNATURE(0, 0x85E1C5F9), 0x03050500) 
#endif


/**
 * This function must be called after an access on data which are also used by other tasks.
 * This is necessary to release the semaphore, which has been blocked before the access by function SysSemEnter.
 * The semaphore is identified by its handle.</description>
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsyssemleave_struct
{
	RTS_IEC_HANDLE hSem;				/* VAR_INPUT */	/* Handle of the semaphore */
	RTS_IEC_RESULT SysSemLeave;			/* VAR_OUTPUT */	
} syssemleave_struct;

void CDECL CDECL_EXT syssemleave(syssemleave_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSSEMLEAVE_IEC) (syssemleave_struct *p);
#if defined(SYSSEM_NOTIMPLEMENTED) || defined(SYSSEMLEAVE_NOTIMPLEMENTED)
	#define USE_syssemleave
	#define EXT_syssemleave
	#define GET_syssemleave(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syssemleave(p0) 
	#define CHK_syssemleave  FALSE
	#define EXP_syssemleave  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syssemleave
	#define EXT_syssemleave
	#define GET_syssemleave(fl)  CAL_CMGETAPI( "syssemleave" ) 
	#define CAL_syssemleave  syssemleave
	#define CHK_syssemleave  TRUE
	#define EXP_syssemleave  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemleave", (RTS_UINTPTR)syssemleave, 1, RTSITF_GET_SIGNATURE(0, 0x2AA5DCFF), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSSEM_EXTERNAL)
	#define USE_syssemleave
	#define EXT_syssemleave
	#define GET_syssemleave(fl)  CAL_CMGETAPI( "syssemleave" ) 
	#define CAL_syssemleave  syssemleave
	#define CHK_syssemleave  TRUE
	#define EXP_syssemleave  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemleave", (RTS_UINTPTR)syssemleave, 1, RTSITF_GET_SIGNATURE(0, 0x2AA5DCFF), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysSemsyssemleave
	#define EXT_SysSemsyssemleave
	#define GET_SysSemsyssemleave  ERR_OK
	#define CAL_SysSemsyssemleave  syssemleave
	#define CHK_SysSemsyssemleave  TRUE
	#define EXP_SysSemsyssemleave  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemleave", (RTS_UINTPTR)syssemleave, 1, RTSITF_GET_SIGNATURE(0, 0x2AA5DCFF), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_syssemleave
	#define EXT_syssemleave
	#define GET_syssemleave(fl)  CAL_CMGETAPI( "syssemleave" ) 
	#define CAL_syssemleave  syssemleave
	#define CHK_syssemleave  TRUE
	#define EXP_syssemleave  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemleave", (RTS_UINTPTR)syssemleave, 1, RTSITF_GET_SIGNATURE(0, 0x2AA5DCFF), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_syssemleave  PFSYSSEMLEAVE_IEC pfsyssemleave;
	#define EXT_syssemleave  extern PFSYSSEMLEAVE_IEC pfsyssemleave;
	#define GET_syssemleave(fl)  s_pfCMGetAPI2( "syssemleave", (RTS_VOID_FCTPTR *)&pfsyssemleave, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x2AA5DCFF), 0x03050500)
	#define CAL_syssemleave  pfsyssemleave
	#define CHK_syssemleave  (pfsyssemleave != NULL)
	#define EXP_syssemleave   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemleave", (RTS_UINTPTR)syssemleave, 1, RTSITF_GET_SIGNATURE(0, 0x2AA5DCFF), 0x03050500) 
#endif


/**
 * This function can be used to check whether a semaphore currently is occupied by another task (via SysSemEnter).
 * The semaphore is identified by its handle.</description>
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsyssemtry_struct
{
	RTS_IEC_HANDLE hSem;				/* VAR_INPUT */	/* Handle of the semaphore */
	RTS_IEC_RESULT SysSemTry;			/* VAR_OUTPUT */	
} syssemtry_struct;

void CDECL CDECL_EXT syssemtry(syssemtry_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSSEMTRY_IEC) (syssemtry_struct *p);
#if defined(SYSSEM_NOTIMPLEMENTED) || defined(SYSSEMTRY_NOTIMPLEMENTED)
	#define USE_syssemtry
	#define EXT_syssemtry
	#define GET_syssemtry(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syssemtry(p0) 
	#define CHK_syssemtry  FALSE
	#define EXP_syssemtry  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syssemtry
	#define EXT_syssemtry
	#define GET_syssemtry(fl)  CAL_CMGETAPI( "syssemtry" ) 
	#define CAL_syssemtry  syssemtry
	#define CHK_syssemtry  TRUE
	#define EXP_syssemtry  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemtry", (RTS_UINTPTR)syssemtry, 1, RTSITF_GET_SIGNATURE(0, 0x14382CB4), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSSEM_EXTERNAL)
	#define USE_syssemtry
	#define EXT_syssemtry
	#define GET_syssemtry(fl)  CAL_CMGETAPI( "syssemtry" ) 
	#define CAL_syssemtry  syssemtry
	#define CHK_syssemtry  TRUE
	#define EXP_syssemtry  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemtry", (RTS_UINTPTR)syssemtry, 1, RTSITF_GET_SIGNATURE(0, 0x14382CB4), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysSemsyssemtry
	#define EXT_SysSemsyssemtry
	#define GET_SysSemsyssemtry  ERR_OK
	#define CAL_SysSemsyssemtry  syssemtry
	#define CHK_SysSemsyssemtry  TRUE
	#define EXP_SysSemsyssemtry  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemtry", (RTS_UINTPTR)syssemtry, 1, RTSITF_GET_SIGNATURE(0, 0x14382CB4), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_syssemtry
	#define EXT_syssemtry
	#define GET_syssemtry(fl)  CAL_CMGETAPI( "syssemtry" ) 
	#define CAL_syssemtry  syssemtry
	#define CHK_syssemtry  TRUE
	#define EXP_syssemtry  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemtry", (RTS_UINTPTR)syssemtry, 1, RTSITF_GET_SIGNATURE(0, 0x14382CB4), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_syssemtry  PFSYSSEMTRY_IEC pfsyssemtry;
	#define EXT_syssemtry  extern PFSYSSEMTRY_IEC pfsyssemtry;
	#define GET_syssemtry(fl)  s_pfCMGetAPI2( "syssemtry", (RTS_VOID_FCTPTR *)&pfsyssemtry, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x14382CB4), 0x03050500)
	#define CAL_syssemtry  pfsyssemtry
	#define CHK_syssemtry  (pfsyssemtry != NULL)
	#define EXP_syssemtry   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemtry", (RTS_UINTPTR)syssemtry, 1, RTSITF_GET_SIGNATURE(0, 0x14382CB4), 0x03050500) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysSemOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysSemOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>
 *	Create a new semaphore object 
 * </description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the semaphore</result>
 */
RTS_HANDLE CDECL SysSemCreate(RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSSEMCREATE) (RTS_RESULT *pResult);
#if defined(SYSSEM_NOTIMPLEMENTED) || defined(SYSSEMCREATE_NOTIMPLEMENTED)
	#define USE_SysSemCreate
	#define EXT_SysSemCreate
	#define GET_SysSemCreate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysSemCreate(p0)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysSemCreate  FALSE
	#define EXP_SysSemCreate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysSemCreate
	#define EXT_SysSemCreate
	#define GET_SysSemCreate(fl)  CAL_CMGETAPI( "SysSemCreate" ) 
	#define CAL_SysSemCreate  SysSemCreate
	#define CHK_SysSemCreate  TRUE
	#define EXP_SysSemCreate  CAL_CMEXPAPI( "SysSemCreate" ) 
#elif defined(MIXED_LINK) && !defined(SYSSEM_EXTERNAL)
	#define USE_SysSemCreate
	#define EXT_SysSemCreate
	#define GET_SysSemCreate(fl)  CAL_CMGETAPI( "SysSemCreate" ) 
	#define CAL_SysSemCreate  SysSemCreate
	#define CHK_SysSemCreate  TRUE
	#define EXP_SysSemCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemCreate", (RTS_UINTPTR)SysSemCreate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysSemSysSemCreate
	#define EXT_SysSemSysSemCreate
	#define GET_SysSemSysSemCreate  ERR_OK
	#define CAL_SysSemSysSemCreate  ((ISysSem*)s_pfCMCreateInstance(CLASSID_CSysSem, NULL))->ISysSemCreate
	#define CHK_SysSemSysSemCreate	(s_pfCMCreateInstance != NULL && pISysSem != NULL)
	#define EXP_SysSemSysSemCreate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysSemCreate
	#define EXT_SysSemCreate
	#define GET_SysSemCreate(fl)  CAL_CMGETAPI( "SysSemCreate" ) 
	#define CAL_SysSemCreate  ((ISysSem*)s_pfCMCreateInstance(CLASSID_CSysSem, NULL))->ISysSemCreate
	#define CHK_SysSemCreate	(s_pfCMCreateInstance != NULL && pISysSem != NULL)
	#define EXP_SysSemCreate  CAL_CMEXPAPI( "SysSemCreate" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysSemCreate  PFSYSSEMCREATE pfSysSemCreate;
	#define EXT_SysSemCreate  extern PFSYSSEMCREATE pfSysSemCreate;
	#define GET_SysSemCreate(fl)  s_pfCMGetAPI2( "SysSemCreate", (RTS_VOID_FCTPTR *)&pfSysSemCreate, (fl), 0, 0)
	#define CAL_SysSemCreate  pfSysSemCreate
	#define CHK_SysSemCreate  (pfSysSemCreate != NULL)
	#define EXP_SysSemCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemCreate", (RTS_UINTPTR)SysSemCreate, 0, 0) 
#endif




/**
 * <description>
 *	Delete a semaphore object 
 * </description>
 * <param name="hSem" type="IN">Handle to the semaphore that is provided from SysSemCreate()</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysSemDelete(RTS_HANDLE hSem);
typedef RTS_RESULT (CDECL * PFSYSSEMDELETE) (RTS_HANDLE hSem);
#if defined(SYSSEM_NOTIMPLEMENTED) || defined(SYSSEMDELETE_NOTIMPLEMENTED)
	#define USE_SysSemDelete
	#define EXT_SysSemDelete
	#define GET_SysSemDelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysSemDelete(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysSemDelete  FALSE
	#define EXP_SysSemDelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysSemDelete
	#define EXT_SysSemDelete
	#define GET_SysSemDelete(fl)  CAL_CMGETAPI( "SysSemDelete" ) 
	#define CAL_SysSemDelete  SysSemDelete
	#define CHK_SysSemDelete  TRUE
	#define EXP_SysSemDelete  CAL_CMEXPAPI( "SysSemDelete" ) 
#elif defined(MIXED_LINK) && !defined(SYSSEM_EXTERNAL)
	#define USE_SysSemDelete
	#define EXT_SysSemDelete
	#define GET_SysSemDelete(fl)  CAL_CMGETAPI( "SysSemDelete" ) 
	#define CAL_SysSemDelete  SysSemDelete
	#define CHK_SysSemDelete  TRUE
	#define EXP_SysSemDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemDelete", (RTS_UINTPTR)SysSemDelete, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysSemSysSemDelete
	#define EXT_SysSemSysSemDelete
	#define GET_SysSemSysSemDelete  ERR_OK
	#define CAL_SysSemSysSemDelete(p0) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ISysSem*)p0)->ISysSemDelete())
	#define CHK_SysSemSysSemDelete  TRUE
	#define EXP_SysSemSysSemDelete  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysSemDelete
	#define EXT_SysSemDelete
	#define GET_SysSemDelete(fl)  CAL_CMGETAPI( "SysSemDelete" ) 
	#define CAL_SysSemDelete(p0) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ISysSem*)p0)->ISysSemDelete())
	#define CHK_SysSemDelete  TRUE
	#define EXP_SysSemDelete  CAL_CMEXPAPI( "SysSemDelete" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysSemDelete  PFSYSSEMDELETE pfSysSemDelete;
	#define EXT_SysSemDelete  extern PFSYSSEMDELETE pfSysSemDelete;
	#define GET_SysSemDelete(fl)  s_pfCMGetAPI2( "SysSemDelete", (RTS_VOID_FCTPTR *)&pfSysSemDelete, (fl), 0, 0)
	#define CAL_SysSemDelete  pfSysSemDelete
	#define CHK_SysSemDelete  (pfSysSemDelete != NULL)
	#define EXP_SysSemDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemDelete", (RTS_UINTPTR)SysSemDelete, 0, 0) 
#endif




/**
 * <description>
 *  Try to enter the semaphore. If semaphore is available, the function 
 *	entered the semaphore and returned ERR_OK. If semaphore is not available, ERR_FAILED is returned. 
 * </description>
 * <param name="hSem" type="IN">Handle to the semaphore that is provided from SysSemCreate()</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysSemTry(RTS_HANDLE hSem);
typedef RTS_RESULT (CDECL * PFSYSSEMTRY) (RTS_HANDLE hSem);
#if defined(SYSSEM_NOTIMPLEMENTED) || defined(SYSSEMTRY_NOTIMPLEMENTED)
	#define USE_SysSemTry
	#define EXT_SysSemTry
	#define GET_SysSemTry(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysSemTry(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysSemTry  FALSE
	#define EXP_SysSemTry  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysSemTry
	#define EXT_SysSemTry
	#define GET_SysSemTry(fl)  CAL_CMGETAPI( "SysSemTry" ) 
	#define CAL_SysSemTry  SysSemTry
	#define CHK_SysSemTry  TRUE
	#define EXP_SysSemTry  CAL_CMEXPAPI( "SysSemTry" ) 
#elif defined(MIXED_LINK) && !defined(SYSSEM_EXTERNAL)
	#define USE_SysSemTry
	#define EXT_SysSemTry
	#define GET_SysSemTry(fl)  CAL_CMGETAPI( "SysSemTry" ) 
	#define CAL_SysSemTry  SysSemTry
	#define CHK_SysSemTry  TRUE
	#define EXP_SysSemTry  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemTry", (RTS_UINTPTR)SysSemTry, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysSemSysSemTry
	#define EXT_SysSemSysSemTry
	#define GET_SysSemSysSemTry  ERR_OK
	#define CAL_SysSemSysSemTry(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysSem->ISysSemTry() : ((ISysSem*)p0)->ISysSemTry())
	#define CHK_SysSemSysSemTry  (pISysSem != NULL)
	#define EXP_SysSemSysSemTry  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysSemTry
	#define EXT_SysSemTry
	#define GET_SysSemTry(fl)  CAL_CMGETAPI( "SysSemTry" ) 
	#define CAL_SysSemTry(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysSem->ISysSemTry() : ((ISysSem*)p0)->ISysSemTry())
	#define CHK_SysSemTry  (pISysSem != NULL)
	#define EXP_SysSemTry  CAL_CMEXPAPI( "SysSemTry" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysSemTry  PFSYSSEMTRY pfSysSemTry;
	#define EXT_SysSemTry  extern PFSYSSEMTRY pfSysSemTry;
	#define GET_SysSemTry(fl)  s_pfCMGetAPI2( "SysSemTry", (RTS_VOID_FCTPTR *)&pfSysSemTry, (fl), 0, 0)
	#define CAL_SysSemTry  pfSysSemTry
	#define CHK_SysSemTry  (pfSysSemTry != NULL)
	#define EXP_SysSemTry  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemTry", (RTS_UINTPTR)SysSemTry, 0, 0) 
#endif




/**
 * <description>
 *  Enter the given semaphore. If the semahore is still entered by another task1, the actual task2 will be blocked,
 *	until the task1 has called SysSemLeave().
 *
 *	IMPLEMENTATION NOTE:
 *		The semaphores must work recursive! That means, that a multiple call out of one task
 *		must not block the execution! For each SysSemEnter() call, a corresponding SysSemLeave()
 *		must be used!
 * </description>
 * <param name="hSem" type="IN">Handle to the semaphore that is provided from SysSemCreate()</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysSemEnter(RTS_HANDLE hSem);
typedef RTS_RESULT (CDECL * PFSYSSEMENTER) (RTS_HANDLE hSem);
#if defined(SYSSEM_NOTIMPLEMENTED) || defined(SYSSEMENTER_NOTIMPLEMENTED)
	#define USE_SysSemEnter
	#define EXT_SysSemEnter
	#define GET_SysSemEnter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysSemEnter(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysSemEnter  FALSE
	#define EXP_SysSemEnter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysSemEnter
	#define EXT_SysSemEnter
	#define GET_SysSemEnter(fl)  CAL_CMGETAPI( "SysSemEnter" ) 
	#define CAL_SysSemEnter  SysSemEnter
	#define CHK_SysSemEnter  TRUE
	#define EXP_SysSemEnter  CAL_CMEXPAPI( "SysSemEnter" ) 
#elif defined(MIXED_LINK) && !defined(SYSSEM_EXTERNAL)
	#define USE_SysSemEnter
	#define EXT_SysSemEnter
	#define GET_SysSemEnter(fl)  CAL_CMGETAPI( "SysSemEnter" ) 
	#define CAL_SysSemEnter  SysSemEnter
	#define CHK_SysSemEnter  TRUE
	#define EXP_SysSemEnter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemEnter", (RTS_UINTPTR)SysSemEnter, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysSemSysSemEnter
	#define EXT_SysSemSysSemEnter
	#define GET_SysSemSysSemEnter  ERR_OK
	#define CAL_SysSemSysSemEnter(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysSem->ISysSemEnter() : ((ISysSem*)p0)->ISysSemEnter())
	#define CHK_SysSemSysSemEnter  (pISysSem != NULL)
	#define EXP_SysSemSysSemEnter  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysSemEnter
	#define EXT_SysSemEnter
	#define GET_SysSemEnter(fl)  CAL_CMGETAPI( "SysSemEnter" ) 
	#define CAL_SysSemEnter(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysSem->ISysSemEnter() : ((ISysSem*)p0)->ISysSemEnter())
	#define CHK_SysSemEnter  (pISysSem != NULL)
	#define EXP_SysSemEnter  CAL_CMEXPAPI( "SysSemEnter" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysSemEnter  PFSYSSEMENTER pfSysSemEnter;
	#define EXT_SysSemEnter  extern PFSYSSEMENTER pfSysSemEnter;
	#define GET_SysSemEnter(fl)  s_pfCMGetAPI2( "SysSemEnter", (RTS_VOID_FCTPTR *)&pfSysSemEnter, (fl), 0, 0)
	#define CAL_SysSemEnter  pfSysSemEnter
	#define CHK_SysSemEnter  (pfSysSemEnter != NULL)
	#define EXP_SysSemEnter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemEnter", (RTS_UINTPTR)SysSemEnter, 0, 0) 
#endif




/**
 * <description>
 *  Leave the given semaphore.
 * </description>
 * <param name="hSem" type="IN">Handle to the semaphore that is provided from SysSemCreate()</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysSemLeave(RTS_HANDLE hSem);
typedef RTS_RESULT (CDECL * PFSYSSEMLEAVE) (RTS_HANDLE hSem);
#if defined(SYSSEM_NOTIMPLEMENTED) || defined(SYSSEMLEAVE_NOTIMPLEMENTED)
	#define USE_SysSemLeave
	#define EXT_SysSemLeave
	#define GET_SysSemLeave(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysSemLeave(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysSemLeave  FALSE
	#define EXP_SysSemLeave  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysSemLeave
	#define EXT_SysSemLeave
	#define GET_SysSemLeave(fl)  CAL_CMGETAPI( "SysSemLeave" ) 
	#define CAL_SysSemLeave  SysSemLeave
	#define CHK_SysSemLeave  TRUE
	#define EXP_SysSemLeave  CAL_CMEXPAPI( "SysSemLeave" ) 
#elif defined(MIXED_LINK) && !defined(SYSSEM_EXTERNAL)
	#define USE_SysSemLeave
	#define EXT_SysSemLeave
	#define GET_SysSemLeave(fl)  CAL_CMGETAPI( "SysSemLeave" ) 
	#define CAL_SysSemLeave  SysSemLeave
	#define CHK_SysSemLeave  TRUE
	#define EXP_SysSemLeave  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemLeave", (RTS_UINTPTR)SysSemLeave, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysSemSysSemLeave
	#define EXT_SysSemSysSemLeave
	#define GET_SysSemSysSemLeave  ERR_OK
	#define CAL_SysSemSysSemLeave(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysSem->ISysSemLeave() : ((ISysSem*)p0)->ISysSemLeave())
	#define CHK_SysSemSysSemLeave  (pISysSem != NULL)
	#define EXP_SysSemSysSemLeave  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysSemLeave
	#define EXT_SysSemLeave
	#define GET_SysSemLeave(fl)  CAL_CMGETAPI( "SysSemLeave" ) 
	#define CAL_SysSemLeave(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysSem->ISysSemLeave() : ((ISysSem*)p0)->ISysSemLeave())
	#define CHK_SysSemLeave  (pISysSem != NULL)
	#define EXP_SysSemLeave  CAL_CMEXPAPI( "SysSemLeave" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysSemLeave  PFSYSSEMLEAVE pfSysSemLeave;
	#define EXT_SysSemLeave  extern PFSYSSEMLEAVE pfSysSemLeave;
	#define GET_SysSemLeave(fl)  s_pfCMGetAPI2( "SysSemLeave", (RTS_VOID_FCTPTR *)&pfSysSemLeave, (fl), 0, 0)
	#define CAL_SysSemLeave  pfSysSemLeave
	#define CHK_SysSemLeave  (pfSysSemLeave != NULL)
	#define EXP_SysSemLeave  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemLeave", (RTS_UINTPTR)SysSemLeave, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSYSSEMCREATE ISysSemCreate;
 	PFSYSSEMDELETE ISysSemDelete;
 	PFSYSSEMTRY ISysSemTry;
 	PFSYSSEMENTER ISysSemEnter;
 	PFSYSSEMLEAVE ISysSemLeave;
 } ISysSem_C;

#ifdef CPLUSPLUS
class ISysSem : public IBase
{
	public:
		virtual RTS_HANDLE CDECL ISysSemCreate(RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISysSemDelete(void) =0;
		virtual RTS_RESULT CDECL ISysSemTry(void) =0;
		virtual RTS_RESULT CDECL ISysSemEnter(void) =0;
		virtual RTS_RESULT CDECL ISysSemLeave(void) =0;
};
	#ifndef ITF_SysSem
		#define ITF_SysSem static ISysSem *pISysSem = NULL;
	#endif
	#define EXTITF_SysSem
#else	/*CPLUSPLUS*/
	typedef ISysSem_C		ISysSem;
	#ifndef ITF_SysSem
		#define ITF_SysSem
	#endif
	#define EXTITF_SysSem
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSSEMITF_H_*/
