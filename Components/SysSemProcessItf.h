 /**
 * <interfacename>SysSemProcess</interfacename>
 * <description> 
 *	<p>The SysSemProcess interface is projected to handle synchonization objects for processes.
 *	The synchronization objects are called semaphores to synchronize concurrent access to single
 *	system global resources.</p>
 *	<p>For example:</p>
 *	<p>	Process1:
 *			...
 *			SysSemProcessEnter(hSem);
 *			[Here you can accessed the protected global resource]
 *			SysSemProcessLeave(hSem);
 *			[After SysSemProcessLeave() you must not access the protected globale resource]
 *			....
 *	</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _SYSSEMPROCESSITF_H_
#define _SYSSEMPROCESSITF_H_

#include "CmpStd.h"

 

 




#include "CmpStd.h"

#ifndef CDECL
	#define CDECL
#endif


/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Create a new semaphore object to synchronize processes (global semaphores)</description>
 * <result><p>RESULT: Handle to the sempahore object</p></result>
 */
typedef struct tagsyssemprocesscreate_struct
{
	RTS_IEC_STRING *pszName;			/* VAR_INPUT */	/* <param name="pszName" type="IN">Name of the semaphore</param> */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library):
	<ul>
 	<li>ERR_OK</li>
 	<li>ERR_DUPLICATE: if semaphore already exists</li>
	<ul>
 </param> */
	RTS_IEC_HANDLE SysSemProcessCreate;	/* VAR_OUTPUT */	
} syssemprocesscreate_struct;

void CDECL CDECL_EXT syssemprocesscreate(syssemprocesscreate_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSSEMPROCESSCREATE_IEC) (syssemprocesscreate_struct *p);
#if defined(SYSSEMPROCESS_NOTIMPLEMENTED) || defined(SYSSEMPROCESSCREATE_NOTIMPLEMENTED)
	#define USE_syssemprocesscreate
	#define EXT_syssemprocesscreate
	#define GET_syssemprocesscreate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syssemprocesscreate(p0) 
	#define CHK_syssemprocesscreate  FALSE
	#define EXP_syssemprocesscreate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syssemprocesscreate
	#define EXT_syssemprocesscreate
	#define GET_syssemprocesscreate(fl)  CAL_CMGETAPI( "syssemprocesscreate" ) 
	#define CAL_syssemprocesscreate  syssemprocesscreate
	#define CHK_syssemprocesscreate  TRUE
	#define EXP_syssemprocesscreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemprocesscreate", (RTS_UINTPTR)syssemprocesscreate, 1, RTSITF_GET_SIGNATURE(0, 0x56515D0D), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSSEMPROCESS_EXTERNAL)
	#define USE_syssemprocesscreate
	#define EXT_syssemprocesscreate
	#define GET_syssemprocesscreate(fl)  CAL_CMGETAPI( "syssemprocesscreate" ) 
	#define CAL_syssemprocesscreate  syssemprocesscreate
	#define CHK_syssemprocesscreate  TRUE
	#define EXP_syssemprocesscreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemprocesscreate", (RTS_UINTPTR)syssemprocesscreate, 1, RTSITF_GET_SIGNATURE(0, 0x56515D0D), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysSemProcesssyssemprocesscreate
	#define EXT_SysSemProcesssyssemprocesscreate
	#define GET_SysSemProcesssyssemprocesscreate  ERR_OK
	#define CAL_SysSemProcesssyssemprocesscreate  syssemprocesscreate
	#define CHK_SysSemProcesssyssemprocesscreate  TRUE
	#define EXP_SysSemProcesssyssemprocesscreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemprocesscreate", (RTS_UINTPTR)syssemprocesscreate, 1, RTSITF_GET_SIGNATURE(0, 0x56515D0D), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_syssemprocesscreate
	#define EXT_syssemprocesscreate
	#define GET_syssemprocesscreate(fl)  CAL_CMGETAPI( "syssemprocesscreate" ) 
	#define CAL_syssemprocesscreate  syssemprocesscreate
	#define CHK_syssemprocesscreate  TRUE
	#define EXP_syssemprocesscreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemprocesscreate", (RTS_UINTPTR)syssemprocesscreate, 1, RTSITF_GET_SIGNATURE(0, 0x56515D0D), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_syssemprocesscreate  PFSYSSEMPROCESSCREATE_IEC pfsyssemprocesscreate;
	#define EXT_syssemprocesscreate  extern PFSYSSEMPROCESSCREATE_IEC pfsyssemprocesscreate;
	#define GET_syssemprocesscreate(fl)  s_pfCMGetAPI2( "syssemprocesscreate", (RTS_VOID_FCTPTR *)&pfsyssemprocesscreate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x56515D0D), 0x03050500)
	#define CAL_syssemprocesscreate  pfsyssemprocesscreate
	#define CHK_syssemprocesscreate  (pfsyssemprocesscreate != NULL)
	#define EXP_syssemprocesscreate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemprocesscreate", (RTS_UINTPTR)syssemprocesscreate, 1, RTSITF_GET_SIGNATURE(0, 0x56515D0D), 0x03050500) 
#endif


/**
 * <description>Delete a semaphore object</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsyssemprocessdelete_struct
{
	RTS_IEC_HANDLE hSem;				/* VAR_INPUT */	/* <param name="hSem" type="IN">Handle to the semaphore</param> */
	RTS_IEC_RESULT SysSemProcessDelete;	/* VAR_OUTPUT */	
} syssemprocessdelete_struct;

void CDECL CDECL_EXT syssemprocessdelete(syssemprocessdelete_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSSEMPROCESSDELETE_IEC) (syssemprocessdelete_struct *p);
#if defined(SYSSEMPROCESS_NOTIMPLEMENTED) || defined(SYSSEMPROCESSDELETE_NOTIMPLEMENTED)
	#define USE_syssemprocessdelete
	#define EXT_syssemprocessdelete
	#define GET_syssemprocessdelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syssemprocessdelete(p0) 
	#define CHK_syssemprocessdelete  FALSE
	#define EXP_syssemprocessdelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syssemprocessdelete
	#define EXT_syssemprocessdelete
	#define GET_syssemprocessdelete(fl)  CAL_CMGETAPI( "syssemprocessdelete" ) 
	#define CAL_syssemprocessdelete  syssemprocessdelete
	#define CHK_syssemprocessdelete  TRUE
	#define EXP_syssemprocessdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemprocessdelete", (RTS_UINTPTR)syssemprocessdelete, 1, RTSITF_GET_SIGNATURE(0, 0xDBBE905D), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSSEMPROCESS_EXTERNAL)
	#define USE_syssemprocessdelete
	#define EXT_syssemprocessdelete
	#define GET_syssemprocessdelete(fl)  CAL_CMGETAPI( "syssemprocessdelete" ) 
	#define CAL_syssemprocessdelete  syssemprocessdelete
	#define CHK_syssemprocessdelete  TRUE
	#define EXP_syssemprocessdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemprocessdelete", (RTS_UINTPTR)syssemprocessdelete, 1, RTSITF_GET_SIGNATURE(0, 0xDBBE905D), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysSemProcesssyssemprocessdelete
	#define EXT_SysSemProcesssyssemprocessdelete
	#define GET_SysSemProcesssyssemprocessdelete  ERR_OK
	#define CAL_SysSemProcesssyssemprocessdelete  syssemprocessdelete
	#define CHK_SysSemProcesssyssemprocessdelete  TRUE
	#define EXP_SysSemProcesssyssemprocessdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemprocessdelete", (RTS_UINTPTR)syssemprocessdelete, 1, RTSITF_GET_SIGNATURE(0, 0xDBBE905D), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_syssemprocessdelete
	#define EXT_syssemprocessdelete
	#define GET_syssemprocessdelete(fl)  CAL_CMGETAPI( "syssemprocessdelete" ) 
	#define CAL_syssemprocessdelete  syssemprocessdelete
	#define CHK_syssemprocessdelete  TRUE
	#define EXP_syssemprocessdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemprocessdelete", (RTS_UINTPTR)syssemprocessdelete, 1, RTSITF_GET_SIGNATURE(0, 0xDBBE905D), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_syssemprocessdelete  PFSYSSEMPROCESSDELETE_IEC pfsyssemprocessdelete;
	#define EXT_syssemprocessdelete  extern PFSYSSEMPROCESSDELETE_IEC pfsyssemprocessdelete;
	#define GET_syssemprocessdelete(fl)  s_pfCMGetAPI2( "syssemprocessdelete", (RTS_VOID_FCTPTR *)&pfsyssemprocessdelete, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xDBBE905D), 0x03050500)
	#define CAL_syssemprocessdelete  pfsyssemprocessdelete
	#define CHK_syssemprocessdelete  (pfsyssemprocessdelete != NULL)
	#define EXP_syssemprocessdelete   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemprocessdelete", (RTS_UINTPTR)syssemprocessdelete, 1, RTSITF_GET_SIGNATURE(0, 0xDBBE905D), 0x03050500) 
#endif


/**
 * <description>Enter the given semaphore.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library):
 *	<ul>
 * 	<li>ERR_OK</li>
 * 	<li>ERR_TIMEOUT: if timeout expires before enter the semaphore</li>
 *	<ul>
 * </p></result>
 */
typedef struct tagsyssemprocessenter_struct
{
	RTS_IEC_HANDLE hSem;				/* VAR_INPUT */	/* <param name="hSem" type="IN">Handle to the semaphore</param> */
	RTS_IEC_UDINT ulTimeout;			/* VAR_INPUT */	/* <param name="ulTimeoutMs" type="IN">Timeout in milliseconds to wait to enter the semaphore or 16#FFFFFFFF for an infinite wait.</param> */
	RTS_IEC_RESULT SysSemProcessEnter;	/* VAR_OUTPUT */	
} syssemprocessenter_struct;

void CDECL CDECL_EXT syssemprocessenter(syssemprocessenter_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSSEMPROCESSENTER_IEC) (syssemprocessenter_struct *p);
#if defined(SYSSEMPROCESS_NOTIMPLEMENTED) || defined(SYSSEMPROCESSENTER_NOTIMPLEMENTED)
	#define USE_syssemprocessenter
	#define EXT_syssemprocessenter
	#define GET_syssemprocessenter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syssemprocessenter(p0) 
	#define CHK_syssemprocessenter  FALSE
	#define EXP_syssemprocessenter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syssemprocessenter
	#define EXT_syssemprocessenter
	#define GET_syssemprocessenter(fl)  CAL_CMGETAPI( "syssemprocessenter" ) 
	#define CAL_syssemprocessenter  syssemprocessenter
	#define CHK_syssemprocessenter  TRUE
	#define EXP_syssemprocessenter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemprocessenter", (RTS_UINTPTR)syssemprocessenter, 1, RTSITF_GET_SIGNATURE(0, 0x8A9203CC), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSSEMPROCESS_EXTERNAL)
	#define USE_syssemprocessenter
	#define EXT_syssemprocessenter
	#define GET_syssemprocessenter(fl)  CAL_CMGETAPI( "syssemprocessenter" ) 
	#define CAL_syssemprocessenter  syssemprocessenter
	#define CHK_syssemprocessenter  TRUE
	#define EXP_syssemprocessenter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemprocessenter", (RTS_UINTPTR)syssemprocessenter, 1, RTSITF_GET_SIGNATURE(0, 0x8A9203CC), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysSemProcesssyssemprocessenter
	#define EXT_SysSemProcesssyssemprocessenter
	#define GET_SysSemProcesssyssemprocessenter  ERR_OK
	#define CAL_SysSemProcesssyssemprocessenter  syssemprocessenter
	#define CHK_SysSemProcesssyssemprocessenter  TRUE
	#define EXP_SysSemProcesssyssemprocessenter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemprocessenter", (RTS_UINTPTR)syssemprocessenter, 1, RTSITF_GET_SIGNATURE(0, 0x8A9203CC), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_syssemprocessenter
	#define EXT_syssemprocessenter
	#define GET_syssemprocessenter(fl)  CAL_CMGETAPI( "syssemprocessenter" ) 
	#define CAL_syssemprocessenter  syssemprocessenter
	#define CHK_syssemprocessenter  TRUE
	#define EXP_syssemprocessenter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemprocessenter", (RTS_UINTPTR)syssemprocessenter, 1, RTSITF_GET_SIGNATURE(0, 0x8A9203CC), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_syssemprocessenter  PFSYSSEMPROCESSENTER_IEC pfsyssemprocessenter;
	#define EXT_syssemprocessenter  extern PFSYSSEMPROCESSENTER_IEC pfsyssemprocessenter;
	#define GET_syssemprocessenter(fl)  s_pfCMGetAPI2( "syssemprocessenter", (RTS_VOID_FCTPTR *)&pfsyssemprocessenter, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x8A9203CC), 0x03050500)
	#define CAL_syssemprocessenter  pfsyssemprocessenter
	#define CHK_syssemprocessenter  (pfsyssemprocessenter != NULL)
	#define EXP_syssemprocessenter   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemprocessenter", (RTS_UINTPTR)syssemprocessenter, 1, RTSITF_GET_SIGNATURE(0, 0x8A9203CC), 0x03050500) 
#endif


/**
 * <description>Leave the given semaphore.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsyssemprocessleave_struct
{
	RTS_IEC_HANDLE hSem;				/* VAR_INPUT */	/* <param name="hSem" type="IN">Handle to the semaphore</param> */
	RTS_IEC_RESULT SysSemProcessLeave;	/* VAR_OUTPUT */	
} syssemprocessleave_struct;

void CDECL CDECL_EXT syssemprocessleave(syssemprocessleave_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSSEMPROCESSLEAVE_IEC) (syssemprocessleave_struct *p);
#if defined(SYSSEMPROCESS_NOTIMPLEMENTED) || defined(SYSSEMPROCESSLEAVE_NOTIMPLEMENTED)
	#define USE_syssemprocessleave
	#define EXT_syssemprocessleave
	#define GET_syssemprocessleave(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syssemprocessleave(p0) 
	#define CHK_syssemprocessleave  FALSE
	#define EXP_syssemprocessleave  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syssemprocessleave
	#define EXT_syssemprocessleave
	#define GET_syssemprocessleave(fl)  CAL_CMGETAPI( "syssemprocessleave" ) 
	#define CAL_syssemprocessleave  syssemprocessleave
	#define CHK_syssemprocessleave  TRUE
	#define EXP_syssemprocessleave  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemprocessleave", (RTS_UINTPTR)syssemprocessleave, 1, RTSITF_GET_SIGNATURE(0, 0x4816900D), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSSEMPROCESS_EXTERNAL)
	#define USE_syssemprocessleave
	#define EXT_syssemprocessleave
	#define GET_syssemprocessleave(fl)  CAL_CMGETAPI( "syssemprocessleave" ) 
	#define CAL_syssemprocessleave  syssemprocessleave
	#define CHK_syssemprocessleave  TRUE
	#define EXP_syssemprocessleave  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemprocessleave", (RTS_UINTPTR)syssemprocessleave, 1, RTSITF_GET_SIGNATURE(0, 0x4816900D), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysSemProcesssyssemprocessleave
	#define EXT_SysSemProcesssyssemprocessleave
	#define GET_SysSemProcesssyssemprocessleave  ERR_OK
	#define CAL_SysSemProcesssyssemprocessleave  syssemprocessleave
	#define CHK_SysSemProcesssyssemprocessleave  TRUE
	#define EXP_SysSemProcesssyssemprocessleave  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemprocessleave", (RTS_UINTPTR)syssemprocessleave, 1, RTSITF_GET_SIGNATURE(0, 0x4816900D), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_syssemprocessleave
	#define EXT_syssemprocessleave
	#define GET_syssemprocessleave(fl)  CAL_CMGETAPI( "syssemprocessleave" ) 
	#define CAL_syssemprocessleave  syssemprocessleave
	#define CHK_syssemprocessleave  TRUE
	#define EXP_syssemprocessleave  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemprocessleave", (RTS_UINTPTR)syssemprocessleave, 1, RTSITF_GET_SIGNATURE(0, 0x4816900D), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_syssemprocessleave  PFSYSSEMPROCESSLEAVE_IEC pfsyssemprocessleave;
	#define EXT_syssemprocessleave  extern PFSYSSEMPROCESSLEAVE_IEC pfsyssemprocessleave;
	#define GET_syssemprocessleave(fl)  s_pfCMGetAPI2( "syssemprocessleave", (RTS_VOID_FCTPTR *)&pfsyssemprocessleave, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x4816900D), 0x03050500)
	#define CAL_syssemprocessleave  pfsyssemprocessleave
	#define CHK_syssemprocessleave  (pfsyssemprocessleave != NULL)
	#define EXP_syssemprocessleave   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssemprocessleave", (RTS_UINTPTR)syssemprocessleave, 1, RTSITF_GET_SIGNATURE(0, 0x4816900D), 0x03050500) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#define SYSSEMPROCESS_WAIT_INFINITE		((unsigned long)-1)

#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysSemProcessOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysSemProcessOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>
 *	Create a new semaphore object to synchronize processes (global semaphores)
 * </description>
 * <param name="pszName" type="IN">Name of the semaphore</param>
 * <param name="pResult" type="OUT">ERR_OK or ERR_DUPLICATE if semaphore already exists</param>
 * <result>Handle to the sempahore object</result>
 */
RTS_HANDLE CDECL SysSemProcessCreate(char *pszName, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSSEMPROCESSCREATE) (char *pszName, RTS_RESULT *pResult);
#if defined(SYSSEMPROCESS_NOTIMPLEMENTED) || defined(SYSSEMPROCESSCREATE_NOTIMPLEMENTED)
	#define USE_SysSemProcessCreate
	#define EXT_SysSemProcessCreate
	#define GET_SysSemProcessCreate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysSemProcessCreate(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysSemProcessCreate  FALSE
	#define EXP_SysSemProcessCreate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysSemProcessCreate
	#define EXT_SysSemProcessCreate
	#define GET_SysSemProcessCreate(fl)  CAL_CMGETAPI( "SysSemProcessCreate" ) 
	#define CAL_SysSemProcessCreate  SysSemProcessCreate
	#define CHK_SysSemProcessCreate  TRUE
	#define EXP_SysSemProcessCreate  CAL_CMEXPAPI( "SysSemProcessCreate" ) 
#elif defined(MIXED_LINK) && !defined(SYSSEMPROCESS_EXTERNAL)
	#define USE_SysSemProcessCreate
	#define EXT_SysSemProcessCreate
	#define GET_SysSemProcessCreate(fl)  CAL_CMGETAPI( "SysSemProcessCreate" ) 
	#define CAL_SysSemProcessCreate  SysSemProcessCreate
	#define CHK_SysSemProcessCreate  TRUE
	#define EXP_SysSemProcessCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemProcessCreate", (RTS_UINTPTR)SysSemProcessCreate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysSemProcessSysSemProcessCreate
	#define EXT_SysSemProcessSysSemProcessCreate
	#define GET_SysSemProcessSysSemProcessCreate  ERR_OK
	#define CAL_SysSemProcessSysSemProcessCreate  ((ISysSemProcess*)s_pfCMCreateInstance(CLASSID_CSysSemProcess, NULL))->ISysSemProcessCreate
	#define CHK_SysSemProcessSysSemProcessCreate	(s_pfCMCreateInstance != NULL && pISysSemProcess != NULL)
	#define EXP_SysSemProcessSysSemProcessCreate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysSemProcessCreate
	#define EXT_SysSemProcessCreate
	#define GET_SysSemProcessCreate(fl)  CAL_CMGETAPI( "SysSemProcessCreate" ) 
	#define CAL_SysSemProcessCreate  ((ISysSemProcess*)s_pfCMCreateInstance(CLASSID_CSysSemProcess, NULL))->ISysSemProcessCreate
	#define CHK_SysSemProcessCreate	(s_pfCMCreateInstance != NULL && pISysSemProcess != NULL)
	#define EXP_SysSemProcessCreate  CAL_CMEXPAPI( "SysSemProcessCreate" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysSemProcessCreate  PFSYSSEMPROCESSCREATE pfSysSemProcessCreate;
	#define EXT_SysSemProcessCreate  extern PFSYSSEMPROCESSCREATE pfSysSemProcessCreate;
	#define GET_SysSemProcessCreate(fl)  s_pfCMGetAPI2( "SysSemProcessCreate", (RTS_VOID_FCTPTR *)&pfSysSemProcessCreate, (fl), 0, 0)
	#define CAL_SysSemProcessCreate  pfSysSemProcessCreate
	#define CHK_SysSemProcessCreate  (pfSysSemProcessCreate != NULL)
	#define EXP_SysSemProcessCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemProcessCreate", (RTS_UINTPTR)SysSemProcessCreate, 0, 0) 
#endif




/**
 * <description>
 *	Delete a semaphore object 
 * </description>
 * <param name="hSem" type="IN">Handle to the semaphore</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysSemProcessDelete(RTS_HANDLE hSem);
typedef RTS_RESULT (CDECL * PFSYSSEMPROCESSDELETE) (RTS_HANDLE hSem);
#if defined(SYSSEMPROCESS_NOTIMPLEMENTED) || defined(SYSSEMPROCESSDELETE_NOTIMPLEMENTED)
	#define USE_SysSemProcessDelete
	#define EXT_SysSemProcessDelete
	#define GET_SysSemProcessDelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysSemProcessDelete(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysSemProcessDelete  FALSE
	#define EXP_SysSemProcessDelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysSemProcessDelete
	#define EXT_SysSemProcessDelete
	#define GET_SysSemProcessDelete(fl)  CAL_CMGETAPI( "SysSemProcessDelete" ) 
	#define CAL_SysSemProcessDelete  SysSemProcessDelete
	#define CHK_SysSemProcessDelete  TRUE
	#define EXP_SysSemProcessDelete  CAL_CMEXPAPI( "SysSemProcessDelete" ) 
#elif defined(MIXED_LINK) && !defined(SYSSEMPROCESS_EXTERNAL)
	#define USE_SysSemProcessDelete
	#define EXT_SysSemProcessDelete
	#define GET_SysSemProcessDelete(fl)  CAL_CMGETAPI( "SysSemProcessDelete" ) 
	#define CAL_SysSemProcessDelete  SysSemProcessDelete
	#define CHK_SysSemProcessDelete  TRUE
	#define EXP_SysSemProcessDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemProcessDelete", (RTS_UINTPTR)SysSemProcessDelete, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysSemProcessSysSemProcessDelete
	#define EXT_SysSemProcessSysSemProcessDelete
	#define GET_SysSemProcessSysSemProcessDelete  ERR_OK
	#define CAL_SysSemProcessSysSemProcessDelete(p0) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ISysSemProcess*)p0)->ISysSemProcessDelete())
	#define CHK_SysSemProcessSysSemProcessDelete  TRUE
	#define EXP_SysSemProcessSysSemProcessDelete  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysSemProcessDelete
	#define EXT_SysSemProcessDelete
	#define GET_SysSemProcessDelete(fl)  CAL_CMGETAPI( "SysSemProcessDelete" ) 
	#define CAL_SysSemProcessDelete(p0) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ISysSemProcess*)p0)->ISysSemProcessDelete())
	#define CHK_SysSemProcessDelete  TRUE
	#define EXP_SysSemProcessDelete  CAL_CMEXPAPI( "SysSemProcessDelete" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysSemProcessDelete  PFSYSSEMPROCESSDELETE pfSysSemProcessDelete;
	#define EXT_SysSemProcessDelete  extern PFSYSSEMPROCESSDELETE pfSysSemProcessDelete;
	#define GET_SysSemProcessDelete(fl)  s_pfCMGetAPI2( "SysSemProcessDelete", (RTS_VOID_FCTPTR *)&pfSysSemProcessDelete, (fl), 0, 0)
	#define CAL_SysSemProcessDelete  pfSysSemProcessDelete
	#define CHK_SysSemProcessDelete  (pfSysSemProcessDelete != NULL)
	#define EXP_SysSemProcessDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemProcessDelete", (RTS_UINTPTR)SysSemProcessDelete, 0, 0) 
#endif




/**
 * <description>
 *  Enter the given semaphore.
 * </description>
 * <param name="hSem" type="IN">Handle to the semaphore</param>
 * <param name="ulTimeoutMs" type="IN">Timeout in milliseconds to wait to enter the semaphore or
 *				SYSSEMPROCESS_WAIT_INFINITE for an infinite wait.</param>
 * <result>ERR_OK or ERR_TIMEOUT if timeout expires before enter the semaphore</result>
 */
RTS_RESULT CDECL SysSemProcessEnter(RTS_HANDLE hSem, unsigned long ulTimeoutMs);
typedef RTS_RESULT (CDECL * PFSYSSEMPROCESSENTER) (RTS_HANDLE hSem, unsigned long ulTimeoutMs);
#if defined(SYSSEMPROCESS_NOTIMPLEMENTED) || defined(SYSSEMPROCESSENTER_NOTIMPLEMENTED)
	#define USE_SysSemProcessEnter
	#define EXT_SysSemProcessEnter
	#define GET_SysSemProcessEnter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysSemProcessEnter(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysSemProcessEnter  FALSE
	#define EXP_SysSemProcessEnter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysSemProcessEnter
	#define EXT_SysSemProcessEnter
	#define GET_SysSemProcessEnter(fl)  CAL_CMGETAPI( "SysSemProcessEnter" ) 
	#define CAL_SysSemProcessEnter  SysSemProcessEnter
	#define CHK_SysSemProcessEnter  TRUE
	#define EXP_SysSemProcessEnter  CAL_CMEXPAPI( "SysSemProcessEnter" ) 
#elif defined(MIXED_LINK) && !defined(SYSSEMPROCESS_EXTERNAL)
	#define USE_SysSemProcessEnter
	#define EXT_SysSemProcessEnter
	#define GET_SysSemProcessEnter(fl)  CAL_CMGETAPI( "SysSemProcessEnter" ) 
	#define CAL_SysSemProcessEnter  SysSemProcessEnter
	#define CHK_SysSemProcessEnter  TRUE
	#define EXP_SysSemProcessEnter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemProcessEnter", (RTS_UINTPTR)SysSemProcessEnter, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysSemProcessSysSemProcessEnter
	#define EXT_SysSemProcessSysSemProcessEnter
	#define GET_SysSemProcessSysSemProcessEnter  ERR_OK
	#define CAL_SysSemProcessSysSemProcessEnter(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysSemProcess->ISysSemProcessEnter(p1) : ((ISysSemProcess*)p0)->ISysSemProcessEnter(p1))
	#define CHK_SysSemProcessSysSemProcessEnter  (pISysSemProcess != NULL)
	#define EXP_SysSemProcessSysSemProcessEnter  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysSemProcessEnter
	#define EXT_SysSemProcessEnter
	#define GET_SysSemProcessEnter(fl)  CAL_CMGETAPI( "SysSemProcessEnter" ) 
	#define CAL_SysSemProcessEnter(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysSemProcess->ISysSemProcessEnter(p1) : ((ISysSemProcess*)p0)->ISysSemProcessEnter(p1))
	#define CHK_SysSemProcessEnter  (pISysSemProcess != NULL)
	#define EXP_SysSemProcessEnter  CAL_CMEXPAPI( "SysSemProcessEnter" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysSemProcessEnter  PFSYSSEMPROCESSENTER pfSysSemProcessEnter;
	#define EXT_SysSemProcessEnter  extern PFSYSSEMPROCESSENTER pfSysSemProcessEnter;
	#define GET_SysSemProcessEnter(fl)  s_pfCMGetAPI2( "SysSemProcessEnter", (RTS_VOID_FCTPTR *)&pfSysSemProcessEnter, (fl), 0, 0)
	#define CAL_SysSemProcessEnter  pfSysSemProcessEnter
	#define CHK_SysSemProcessEnter  (pfSysSemProcessEnter != NULL)
	#define EXP_SysSemProcessEnter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemProcessEnter", (RTS_UINTPTR)SysSemProcessEnter, 0, 0) 
#endif




/**
 * <description>
 *  Leave the given semaphore.
 * </description>
 * <param name="hSem" type="IN">Handle to the semaphore</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysSemProcessLeave(RTS_HANDLE hSem);
typedef RTS_RESULT (CDECL * PFSYSSEMPROCESSLEAVE) (RTS_HANDLE hSem);
#if defined(SYSSEMPROCESS_NOTIMPLEMENTED) || defined(SYSSEMPROCESSLEAVE_NOTIMPLEMENTED)
	#define USE_SysSemProcessLeave
	#define EXT_SysSemProcessLeave
	#define GET_SysSemProcessLeave(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysSemProcessLeave(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysSemProcessLeave  FALSE
	#define EXP_SysSemProcessLeave  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysSemProcessLeave
	#define EXT_SysSemProcessLeave
	#define GET_SysSemProcessLeave(fl)  CAL_CMGETAPI( "SysSemProcessLeave" ) 
	#define CAL_SysSemProcessLeave  SysSemProcessLeave
	#define CHK_SysSemProcessLeave  TRUE
	#define EXP_SysSemProcessLeave  CAL_CMEXPAPI( "SysSemProcessLeave" ) 
#elif defined(MIXED_LINK) && !defined(SYSSEMPROCESS_EXTERNAL)
	#define USE_SysSemProcessLeave
	#define EXT_SysSemProcessLeave
	#define GET_SysSemProcessLeave(fl)  CAL_CMGETAPI( "SysSemProcessLeave" ) 
	#define CAL_SysSemProcessLeave  SysSemProcessLeave
	#define CHK_SysSemProcessLeave  TRUE
	#define EXP_SysSemProcessLeave  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemProcessLeave", (RTS_UINTPTR)SysSemProcessLeave, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysSemProcessSysSemProcessLeave
	#define EXT_SysSemProcessSysSemProcessLeave
	#define GET_SysSemProcessSysSemProcessLeave  ERR_OK
	#define CAL_SysSemProcessSysSemProcessLeave(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysSemProcess->ISysSemProcessLeave() : ((ISysSemProcess*)p0)->ISysSemProcessLeave())
	#define CHK_SysSemProcessSysSemProcessLeave  (pISysSemProcess != NULL)
	#define EXP_SysSemProcessSysSemProcessLeave  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysSemProcessLeave
	#define EXT_SysSemProcessLeave
	#define GET_SysSemProcessLeave(fl)  CAL_CMGETAPI( "SysSemProcessLeave" ) 
	#define CAL_SysSemProcessLeave(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysSemProcess->ISysSemProcessLeave() : ((ISysSemProcess*)p0)->ISysSemProcessLeave())
	#define CHK_SysSemProcessLeave  (pISysSemProcess != NULL)
	#define EXP_SysSemProcessLeave  CAL_CMEXPAPI( "SysSemProcessLeave" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysSemProcessLeave  PFSYSSEMPROCESSLEAVE pfSysSemProcessLeave;
	#define EXT_SysSemProcessLeave  extern PFSYSSEMPROCESSLEAVE pfSysSemProcessLeave;
	#define GET_SysSemProcessLeave(fl)  s_pfCMGetAPI2( "SysSemProcessLeave", (RTS_VOID_FCTPTR *)&pfSysSemProcessLeave, (fl), 0, 0)
	#define CAL_SysSemProcessLeave  pfSysSemProcessLeave
	#define CHK_SysSemProcessLeave  (pfSysSemProcessLeave != NULL)
	#define EXP_SysSemProcessLeave  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemProcessLeave", (RTS_UINTPTR)SysSemProcessLeave, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSYSSEMPROCESSCREATE ISysSemProcessCreate;
 	PFSYSSEMPROCESSDELETE ISysSemProcessDelete;
 	PFSYSSEMPROCESSENTER ISysSemProcessEnter;
 	PFSYSSEMPROCESSLEAVE ISysSemProcessLeave;
 } ISysSemProcess_C;

#ifdef CPLUSPLUS
class ISysSemProcess : public IBase
{
	public:
		virtual RTS_HANDLE CDECL ISysSemProcessCreate(char *pszName, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISysSemProcessDelete(void) =0;
		virtual RTS_RESULT CDECL ISysSemProcessEnter(unsigned long ulTimeoutMs) =0;
		virtual RTS_RESULT CDECL ISysSemProcessLeave(void) =0;
};
	#ifndef ITF_SysSemProcess
		#define ITF_SysSemProcess static ISysSemProcess *pISysSemProcess = NULL;
	#endif
	#define EXTITF_SysSemProcess
#else	/*CPLUSPLUS*/
	typedef ISysSemProcess_C		ISysSemProcess;
	#ifndef ITF_SysSemProcess
		#define ITF_SysSemProcess
	#endif
	#define EXTITF_SysSemProcess
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSSEMPROCESSITF_H_*/
