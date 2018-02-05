 /**
 * <interfacename>SysSemaphore</interfacename>
 * <description> 
 *	<p>The SysSemaphore interface is projected to handle synchonization objects for tasks and threads.
 *	The synchronization objects are called semaphores to synchronize concurrent access to single
 *	data resources.</p>
 *	<p>For example:</p>
 *	<p>	Task1:
 *			...
 *			SysSemaphoreEnter(hSem, timeval);
 *			[Here you can accessed the protected data]
 *			SysSemaphoreEnter(hSem);
 *			[After SysSemLeave() you must not access the protected data]
 *			....
 *	</p>
 *	<p>
 *		IMPLEMENTATION NOTE:
 *		The semaphores must work recursive! That means, that a multiple call out of one task
 *		must not block the execution! For each SysSemaphoreEnter() call, a corresponding SysSemphoreLeave()
 *		must be used!
 *	</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _SYSSEMCOUNTITF_H_
#define _SYSSEMCOUNTITF_H_

#include "CmpStd.h"

 

 




#include "CmpStd.h"


#define RTS_SEMAPHORE_NOWAIT		0x0			/* Unblocking behavior of the SysSemaphoreEnter function */
#define RTS_SEMAPHORE_WAIT_INFINIT	0xFFFFFFFF	/* Blocking behavior of the SysSemaphoreEnter function */

#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysSemCountOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysSemCountOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>
 *	Create a new counting semaphore object 
 * </description>
 * <param name="pResult" type="OUT">
 * One of:
 * ERR_OK: The semaphore was created.
 * ERR_PARAMETER: Error within the given parameters.
 * ERR_NOMEMORY: The needed ressources couldn't be allocated.
 * ERR_FAILED: An internal error occured.
 * </param>
 * <result>Handle to the semaphore. RTS_INVALIDHANDLE in case of an error.</result>
 */
RTS_HANDLE CDECL SysSemCountCreate(RTS_UI32 ui32InitialValue, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSSEMCOUNTCREATE) (RTS_UI32 ui32InitialValue, RTS_RESULT *pResult);
#if defined(SYSSEMCOUNT_NOTIMPLEMENTED) || defined(SYSSEMCOUNTCREATE_NOTIMPLEMENTED)
	#define USE_SysSemCountCreate
	#define EXT_SysSemCountCreate
	#define GET_SysSemCountCreate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysSemCountCreate(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysSemCountCreate  FALSE
	#define EXP_SysSemCountCreate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysSemCountCreate
	#define EXT_SysSemCountCreate
	#define GET_SysSemCountCreate(fl)  CAL_CMGETAPI( "SysSemCountCreate" ) 
	#define CAL_SysSemCountCreate  SysSemCountCreate
	#define CHK_SysSemCountCreate  TRUE
	#define EXP_SysSemCountCreate  CAL_CMEXPAPI( "SysSemCountCreate" ) 
#elif defined(MIXED_LINK) && !defined(SYSSEMCOUNT_EXTERNAL)
	#define USE_SysSemCountCreate
	#define EXT_SysSemCountCreate
	#define GET_SysSemCountCreate(fl)  CAL_CMGETAPI( "SysSemCountCreate" ) 
	#define CAL_SysSemCountCreate  SysSemCountCreate
	#define CHK_SysSemCountCreate  TRUE
	#define EXP_SysSemCountCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemCountCreate", (RTS_UINTPTR)SysSemCountCreate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysSemCountSysSemCountCreate
	#define EXT_SysSemCountSysSemCountCreate
	#define GET_SysSemCountSysSemCountCreate  ERR_OK
	#define CAL_SysSemCountSysSemCountCreate  ((ISysSemCount*)s_pfCMCreateInstance(CLASSID_CSysSemCount, NULL))->ISysSemCountCreate
	#define CHK_SysSemCountSysSemCountCreate	(s_pfCMCreateInstance != NULL && pISysSemCount != NULL)
	#define EXP_SysSemCountSysSemCountCreate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysSemCountCreate
	#define EXT_SysSemCountCreate
	#define GET_SysSemCountCreate(fl)  CAL_CMGETAPI( "SysSemCountCreate" ) 
	#define CAL_SysSemCountCreate  ((ISysSemCount*)s_pfCMCreateInstance(CLASSID_CSysSemCount, NULL))->ISysSemCountCreate
	#define CHK_SysSemCountCreate	(s_pfCMCreateInstance != NULL && pISysSemCount != NULL)
	#define EXP_SysSemCountCreate  CAL_CMEXPAPI( "SysSemCountCreate" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysSemCountCreate  PFSYSSEMCOUNTCREATE pfSysSemCountCreate;
	#define EXT_SysSemCountCreate  extern PFSYSSEMCOUNTCREATE pfSysSemCountCreate;
	#define GET_SysSemCountCreate(fl)  s_pfCMGetAPI2( "SysSemCountCreate", (RTS_VOID_FCTPTR *)&pfSysSemCountCreate, (fl), 0, 0)
	#define CAL_SysSemCountCreate  pfSysSemCountCreate
	#define CHK_SysSemCountCreate  (pfSysSemCountCreate != NULL)
	#define EXP_SysSemCountCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemCountCreate", (RTS_UINTPTR)SysSemCountCreate, 0, 0) 
#endif




/**
 * <description>
 *	Delete a semaphore object 
 * </description>
 * <param name="hSemaphore" type="IN">Handle to the semaphore that is provided from SysSemaphoreCreate()</param>
 * <result>
 * One of:
 * ERR_OK: The semaphore was deleted successful.
 * ERR_INVALID_HANDLE: The given semaphore isn't a valid semaphore handle.
 * ERR_FAILED: An internal error occured.
 * </result>
 */
RTS_RESULT CDECL SysSemCountDelete(RTS_HANDLE hSemaphore);
typedef RTS_RESULT (CDECL * PFSYSSEMCOUNTDELETE) (RTS_HANDLE hSemaphore);
#if defined(SYSSEMCOUNT_NOTIMPLEMENTED) || defined(SYSSEMCOUNTDELETE_NOTIMPLEMENTED)
	#define USE_SysSemCountDelete
	#define EXT_SysSemCountDelete
	#define GET_SysSemCountDelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysSemCountDelete(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysSemCountDelete  FALSE
	#define EXP_SysSemCountDelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysSemCountDelete
	#define EXT_SysSemCountDelete
	#define GET_SysSemCountDelete(fl)  CAL_CMGETAPI( "SysSemCountDelete" ) 
	#define CAL_SysSemCountDelete  SysSemCountDelete
	#define CHK_SysSemCountDelete  TRUE
	#define EXP_SysSemCountDelete  CAL_CMEXPAPI( "SysSemCountDelete" ) 
#elif defined(MIXED_LINK) && !defined(SYSSEMCOUNT_EXTERNAL)
	#define USE_SysSemCountDelete
	#define EXT_SysSemCountDelete
	#define GET_SysSemCountDelete(fl)  CAL_CMGETAPI( "SysSemCountDelete" ) 
	#define CAL_SysSemCountDelete  SysSemCountDelete
	#define CHK_SysSemCountDelete  TRUE
	#define EXP_SysSemCountDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemCountDelete", (RTS_UINTPTR)SysSemCountDelete, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysSemCountSysSemCountDelete
	#define EXT_SysSemCountSysSemCountDelete
	#define GET_SysSemCountSysSemCountDelete  ERR_OK
	#define CAL_SysSemCountSysSemCountDelete(p0) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ISysSemCount*)p0)->ISysSemCountDelete())
	#define CHK_SysSemCountSysSemCountDelete  TRUE
	#define EXP_SysSemCountSysSemCountDelete  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysSemCountDelete
	#define EXT_SysSemCountDelete
	#define GET_SysSemCountDelete(fl)  CAL_CMGETAPI( "SysSemCountDelete" ) 
	#define CAL_SysSemCountDelete(p0) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ISysSemCount*)p0)->ISysSemCountDelete())
	#define CHK_SysSemCountDelete  TRUE
	#define EXP_SysSemCountDelete  CAL_CMEXPAPI( "SysSemCountDelete" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysSemCountDelete  PFSYSSEMCOUNTDELETE pfSysSemCountDelete;
	#define EXT_SysSemCountDelete  extern PFSYSSEMCOUNTDELETE pfSysSemCountDelete;
	#define GET_SysSemCountDelete(fl)  s_pfCMGetAPI2( "SysSemCountDelete", (RTS_VOID_FCTPTR *)&pfSysSemCountDelete, (fl), 0, 0)
	#define CAL_SysSemCountDelete  pfSysSemCountDelete
	#define CHK_SysSemCountDelete  (pfSysSemCountDelete != NULL)
	#define EXP_SysSemCountDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemCountDelete", (RTS_UINTPTR)SysSemCountDelete, 0, 0) 
#endif




/**
 * <description>
 * Try to enter the semaphore. If semaphore is available, the function enteres the semaphore 
 * and returnes ERR_OK. If semaphore is not available, ERR_TIMEOUT is returned. The behavior of
 * the function  depends on the timeout value:
 * - RTS_TIMEOUT_NO_WAIT indicates that the function is nonblocking. If the semaphore is not available, the function will return immediatly
 * - RTS_TIMEOUT_INFINITE indicates that the function is blocking. The thread will be suspended until the semaphore is available.
 * - Any other value: The Function will block until the semaphore is available, but will return after the timeout if the 
 *   semaphore was not available. ERR_TIMEOUT will be returned in this case.
 * </description>
 * <param name="hSemaphore" type="IN">Handle to the semaphore that is provided from SysSemaphoreCreate()</param>
 * <param name="ui32TimeoutMs">Timeout for the enter operation in ms</param>
 * <result>e
 * One of:
 * - ERR_OK: The semaphore was enterd.
 * - ERR_FAILED: The semaphore couldn't be enterd.
 * - ERR_TIMEOUT: The given timeout expired.
 * - ERR_INVALID_HANDLE: The given semaphore isn't a valid semaphore handle.
 * - ERR_PARAMETER: Error within the given parameters.
 * </result>
 */
RTS_RESULT CDECL SysSemCountEnter(RTS_HANDLE hSemaphore, RTS_UI32 ui32TimeoutMs);
typedef RTS_RESULT (CDECL * PFSYSSEMCOUNTENTER) (RTS_HANDLE hSemaphore, RTS_UI32 ui32TimeoutMs);
#if defined(SYSSEMCOUNT_NOTIMPLEMENTED) || defined(SYSSEMCOUNTENTER_NOTIMPLEMENTED)
	#define USE_SysSemCountEnter
	#define EXT_SysSemCountEnter
	#define GET_SysSemCountEnter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysSemCountEnter(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysSemCountEnter  FALSE
	#define EXP_SysSemCountEnter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysSemCountEnter
	#define EXT_SysSemCountEnter
	#define GET_SysSemCountEnter(fl)  CAL_CMGETAPI( "SysSemCountEnter" ) 
	#define CAL_SysSemCountEnter  SysSemCountEnter
	#define CHK_SysSemCountEnter  TRUE
	#define EXP_SysSemCountEnter  CAL_CMEXPAPI( "SysSemCountEnter" ) 
#elif defined(MIXED_LINK) && !defined(SYSSEMCOUNT_EXTERNAL)
	#define USE_SysSemCountEnter
	#define EXT_SysSemCountEnter
	#define GET_SysSemCountEnter(fl)  CAL_CMGETAPI( "SysSemCountEnter" ) 
	#define CAL_SysSemCountEnter  SysSemCountEnter
	#define CHK_SysSemCountEnter  TRUE
	#define EXP_SysSemCountEnter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemCountEnter", (RTS_UINTPTR)SysSemCountEnter, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysSemCountSysSemCountEnter
	#define EXT_SysSemCountSysSemCountEnter
	#define GET_SysSemCountSysSemCountEnter  ERR_OK
	#define CAL_SysSemCountSysSemCountEnter(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysSemCount->ISysSemCountEnter(p1) : ((ISysSemCount*)p0)->ISysSemCountEnter(p1))
	#define CHK_SysSemCountSysSemCountEnter  (pISysSemCount != NULL)
	#define EXP_SysSemCountSysSemCountEnter  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysSemCountEnter
	#define EXT_SysSemCountEnter
	#define GET_SysSemCountEnter(fl)  CAL_CMGETAPI( "SysSemCountEnter" ) 
	#define CAL_SysSemCountEnter(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysSemCount->ISysSemCountEnter(p1) : ((ISysSemCount*)p0)->ISysSemCountEnter(p1))
	#define CHK_SysSemCountEnter  (pISysSemCount != NULL)
	#define EXP_SysSemCountEnter  CAL_CMEXPAPI( "SysSemCountEnter" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysSemCountEnter  PFSYSSEMCOUNTENTER pfSysSemCountEnter;
	#define EXT_SysSemCountEnter  extern PFSYSSEMCOUNTENTER pfSysSemCountEnter;
	#define GET_SysSemCountEnter(fl)  s_pfCMGetAPI2( "SysSemCountEnter", (RTS_VOID_FCTPTR *)&pfSysSemCountEnter, (fl), 0, 0)
	#define CAL_SysSemCountEnter  pfSysSemCountEnter
	#define CHK_SysSemCountEnter  (pfSysSemCountEnter != NULL)
	#define EXP_SysSemCountEnter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemCountEnter", (RTS_UINTPTR)SysSemCountEnter, 0, 0) 
#endif




/**
 * <description>
 *  Leave the given semaphore.
 * </description>
 * <param name="hSem" type="IN">Handle to the semaphore that is provided from SysSemaphoreCreate()</param>
 * <result>
 * One of:
 * - ERR_OK: The operation was successful
 * - ERR_INVALID_HANDLE: The given semaphore isn't a valid semaphore handle.
 * - ERR_FAILED: The operation failed. 
 * </result>
 */
RTS_RESULT CDECL SysSemCountLeave(RTS_HANDLE hSemaphore);
typedef RTS_RESULT (CDECL * PFSYSSEMCOUNTLEAVE) (RTS_HANDLE hSemaphore);
#if defined(SYSSEMCOUNT_NOTIMPLEMENTED) || defined(SYSSEMCOUNTLEAVE_NOTIMPLEMENTED)
	#define USE_SysSemCountLeave
	#define EXT_SysSemCountLeave
	#define GET_SysSemCountLeave(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysSemCountLeave(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysSemCountLeave  FALSE
	#define EXP_SysSemCountLeave  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysSemCountLeave
	#define EXT_SysSemCountLeave
	#define GET_SysSemCountLeave(fl)  CAL_CMGETAPI( "SysSemCountLeave" ) 
	#define CAL_SysSemCountLeave  SysSemCountLeave
	#define CHK_SysSemCountLeave  TRUE
	#define EXP_SysSemCountLeave  CAL_CMEXPAPI( "SysSemCountLeave" ) 
#elif defined(MIXED_LINK) && !defined(SYSSEMCOUNT_EXTERNAL)
	#define USE_SysSemCountLeave
	#define EXT_SysSemCountLeave
	#define GET_SysSemCountLeave(fl)  CAL_CMGETAPI( "SysSemCountLeave" ) 
	#define CAL_SysSemCountLeave  SysSemCountLeave
	#define CHK_SysSemCountLeave  TRUE
	#define EXP_SysSemCountLeave  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemCountLeave", (RTS_UINTPTR)SysSemCountLeave, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysSemCountSysSemCountLeave
	#define EXT_SysSemCountSysSemCountLeave
	#define GET_SysSemCountSysSemCountLeave  ERR_OK
	#define CAL_SysSemCountSysSemCountLeave(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysSemCount->ISysSemCountLeave() : ((ISysSemCount*)p0)->ISysSemCountLeave())
	#define CHK_SysSemCountSysSemCountLeave  (pISysSemCount != NULL)
	#define EXP_SysSemCountSysSemCountLeave  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysSemCountLeave
	#define EXT_SysSemCountLeave
	#define GET_SysSemCountLeave(fl)  CAL_CMGETAPI( "SysSemCountLeave" ) 
	#define CAL_SysSemCountLeave(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysSemCount->ISysSemCountLeave() : ((ISysSemCount*)p0)->ISysSemCountLeave())
	#define CHK_SysSemCountLeave  (pISysSemCount != NULL)
	#define EXP_SysSemCountLeave  CAL_CMEXPAPI( "SysSemCountLeave" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysSemCountLeave  PFSYSSEMCOUNTLEAVE pfSysSemCountLeave;
	#define EXT_SysSemCountLeave  extern PFSYSSEMCOUNTLEAVE pfSysSemCountLeave;
	#define GET_SysSemCountLeave(fl)  s_pfCMGetAPI2( "SysSemCountLeave", (RTS_VOID_FCTPTR *)&pfSysSemCountLeave, (fl), 0, 0)
	#define CAL_SysSemCountLeave  pfSysSemCountLeave
	#define CHK_SysSemCountLeave  (pfSysSemCountLeave != NULL)
	#define EXP_SysSemCountLeave  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSemCountLeave", (RTS_UINTPTR)SysSemCountLeave, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSYSSEMCOUNTCREATE ISysSemCountCreate;
 	PFSYSSEMCOUNTDELETE ISysSemCountDelete;
 	PFSYSSEMCOUNTENTER ISysSemCountEnter;
 	PFSYSSEMCOUNTLEAVE ISysSemCountLeave;
 } ISysSemCount_C;

#ifdef CPLUSPLUS
class ISysSemCount : public IBase
{
	public:
		virtual RTS_HANDLE CDECL ISysSemCountCreate(RTS_UI32 ui32InitialValue, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISysSemCountDelete(void) =0;
		virtual RTS_RESULT CDECL ISysSemCountEnter(RTS_UI32 ui32TimeoutMs) =0;
		virtual RTS_RESULT CDECL ISysSemCountLeave(void) =0;
};
	#ifndef ITF_SysSemCount
		#define ITF_SysSemCount static ISysSemCount *pISysSemCount = NULL;
	#endif
	#define EXTITF_SysSemCount
#else	/*CPLUSPLUS*/
	typedef ISysSemCount_C		ISysSemCount;
	#ifndef ITF_SysSemCount
		#define ITF_SysSemCount
	#endif
	#define EXTITF_SysSemCount
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSSEMCOUNTITF_H_*/
