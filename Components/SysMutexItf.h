 /**
 * <interfacename>SysMutex/interfacename>
 * <description> 
 *	<p>The SysMutex interface is projected to handle synchonization objects for tasks and threads.
 *	The synchronization objects are called mutexes to synchronize concurrent access to single
 *	data resources.</p>
 *	<p>For example:</p>
 *	<p>	Task1:
 *			...
 *			SysMutexEnter(hMutex);
 *			[Here you can accessed the protected data]
 *			SysMutexLeave(hMutex);
 *			[After SysSemLeave() you must not access the protected data]
 *			....
 *	</p>
 *	<p>
 *		IMPLEMENTATION NOTE:
 *		The mutexes must work recursive! That means, that a multiple call out of one task
 *		must not block the execution! For each SysMutexEnter() call, a corresponding SysMutexLeave()
 *		must be used!
 *	</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _SYSMUTEXITF_H_
#define _SYSMUTEXITF_H_

#include "CmpStd.h"

 

 




#include "CmpStd.h"


#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysMutexOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysMutexOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>
 *	Create a new mutex object.
 * </description>
 * <param name="pResult" type="OUT">Pointer to error code:
 * One of:
 * - ERR_OK: The mutex was created.
 * - ERR_NOMEMORY: The neede ressources couldn't be allocated.
 * </param>
 * <result>Handle to the mutex</result>
 */
RTS_HANDLE CDECL SysMutexCreate(RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSMUTEXCREATE) (RTS_RESULT *pResult);
#if defined(SYSMUTEX_NOTIMPLEMENTED) || defined(SYSMUTEXCREATE_NOTIMPLEMENTED)
	#define USE_SysMutexCreate
	#define EXT_SysMutexCreate
	#define GET_SysMutexCreate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMutexCreate(p0)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysMutexCreate  FALSE
	#define EXP_SysMutexCreate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMutexCreate
	#define EXT_SysMutexCreate
	#define GET_SysMutexCreate(fl)  CAL_CMGETAPI( "SysMutexCreate" ) 
	#define CAL_SysMutexCreate  SysMutexCreate
	#define CHK_SysMutexCreate  TRUE
	#define EXP_SysMutexCreate  CAL_CMEXPAPI( "SysMutexCreate" ) 
#elif defined(MIXED_LINK) && !defined(SYSMUTEX_EXTERNAL)
	#define USE_SysMutexCreate
	#define EXT_SysMutexCreate
	#define GET_SysMutexCreate(fl)  CAL_CMGETAPI( "SysMutexCreate" ) 
	#define CAL_SysMutexCreate  SysMutexCreate
	#define CHK_SysMutexCreate  TRUE
	#define EXP_SysMutexCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMutexCreate", (RTS_UINTPTR)SysMutexCreate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysMutexSysMutexCreate
	#define EXT_SysMutexSysMutexCreate
	#define GET_SysMutexSysMutexCreate  ERR_OK
	#define CAL_SysMutexSysMutexCreate  ((ISysMutex*)s_pfCMCreateInstance(CLASSID_CSysMutex, NULL))->ISysMutexCreate
	#define CHK_SysMutexSysMutexCreate	(s_pfCMCreateInstance != NULL && pISysMutex != NULL)
	#define EXP_SysMutexSysMutexCreate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMutexCreate
	#define EXT_SysMutexCreate
	#define GET_SysMutexCreate(fl)  CAL_CMGETAPI( "SysMutexCreate" ) 
	#define CAL_SysMutexCreate  ((ISysMutex*)s_pfCMCreateInstance(CLASSID_CSysMutex, NULL))->ISysMutexCreate
	#define CHK_SysMutexCreate	(s_pfCMCreateInstance != NULL && pISysMutex != NULL)
	#define EXP_SysMutexCreate  CAL_CMEXPAPI( "SysMutexCreate" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMutexCreate  PFSYSMUTEXCREATE pfSysMutexCreate;
	#define EXT_SysMutexCreate  extern PFSYSMUTEXCREATE pfSysMutexCreate;
	#define GET_SysMutexCreate(fl)  s_pfCMGetAPI2( "SysMutexCreate", (RTS_VOID_FCTPTR *)&pfSysMutexCreate, (fl), 0, 0)
	#define CAL_SysMutexCreate  pfSysMutexCreate
	#define CHK_SysMutexCreate  (pfSysMutexCreate != NULL)
	#define EXP_SysMutexCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMutexCreate", (RTS_UINTPTR)SysMutexCreate, 0, 0) 
#endif




/**
 * <description>
 *	Delete a mutex object 
 * </description>
 * <param name="hMutex" type="IN">Handle to the mutex that is provided from SysMutexCreate()</param>
 * <result> 
 * One of:
 * ERR_OK: The mutex was deleted successful.
 * ERR_INVALID_HANDLE: The given mutex isn't a valid mutex handle.
 * ERR_FAILED: An internal error occured.</result>
 */
RTS_RESULT CDECL SysMutexDelete(RTS_HANDLE hMutex);
typedef RTS_RESULT (CDECL * PFSYSMUTEXDELETE) (RTS_HANDLE hMutex);
#if defined(SYSMUTEX_NOTIMPLEMENTED) || defined(SYSMUTEXDELETE_NOTIMPLEMENTED)
	#define USE_SysMutexDelete
	#define EXT_SysMutexDelete
	#define GET_SysMutexDelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMutexDelete(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMutexDelete  FALSE
	#define EXP_SysMutexDelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMutexDelete
	#define EXT_SysMutexDelete
	#define GET_SysMutexDelete(fl)  CAL_CMGETAPI( "SysMutexDelete" ) 
	#define CAL_SysMutexDelete  SysMutexDelete
	#define CHK_SysMutexDelete  TRUE
	#define EXP_SysMutexDelete  CAL_CMEXPAPI( "SysMutexDelete" ) 
#elif defined(MIXED_LINK) && !defined(SYSMUTEX_EXTERNAL)
	#define USE_SysMutexDelete
	#define EXT_SysMutexDelete
	#define GET_SysMutexDelete(fl)  CAL_CMGETAPI( "SysMutexDelete" ) 
	#define CAL_SysMutexDelete  SysMutexDelete
	#define CHK_SysMutexDelete  TRUE
	#define EXP_SysMutexDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMutexDelete", (RTS_UINTPTR)SysMutexDelete, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysMutexSysMutexDelete
	#define EXT_SysMutexSysMutexDelete
	#define GET_SysMutexSysMutexDelete  ERR_OK
	#define CAL_SysMutexSysMutexDelete(p0) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ISysMutex*)p0)->ISysMutexDelete())
	#define CHK_SysMutexSysMutexDelete  TRUE
	#define EXP_SysMutexSysMutexDelete  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMutexDelete
	#define EXT_SysMutexDelete
	#define GET_SysMutexDelete(fl)  CAL_CMGETAPI( "SysMutexDelete" ) 
	#define CAL_SysMutexDelete(p0) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ISysMutex*)p0)->ISysMutexDelete())
	#define CHK_SysMutexDelete  TRUE
	#define EXP_SysMutexDelete  CAL_CMEXPAPI( "SysMutexDelete" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMutexDelete  PFSYSMUTEXDELETE pfSysMutexDelete;
	#define EXT_SysMutexDelete  extern PFSYSMUTEXDELETE pfSysMutexDelete;
	#define GET_SysMutexDelete(fl)  s_pfCMGetAPI2( "SysMutexDelete", (RTS_VOID_FCTPTR *)&pfSysMutexDelete, (fl), 0, 0)
	#define CAL_SysMutexDelete  pfSysMutexDelete
	#define CHK_SysMutexDelete  (pfSysMutexDelete != NULL)
	#define EXP_SysMutexDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMutexDelete", (RTS_UINTPTR)SysMutexDelete, 0, 0) 
#endif




/**
 * <description>
 *  Try to enter the mutex. If mutex is available, the function 
 *	entered the mutex and returned ERR_OK. If mutex is not available, ERR_FAILED is returned. 
 * </description>
 * <param name="hMutex" type="IN">Handle to the mutex that is provided from SysMutexCreate()</param>
 * <result>
 * One of:
 * ERR_OK: The mutex was enterd.
 * ERR_INVALID_HANDLE: The given mutex isn't a valid mutex handle.
 * ERR_FAILED: An internal error occured. Mutex was no enterd.
 * </result>
 */
RTS_RESULT CDECL SysMutexTryEnter(RTS_HANDLE hMutex);
typedef RTS_RESULT (CDECL * PFSYSMUTEXTRYENTER) (RTS_HANDLE hMutex);
#if defined(SYSMUTEX_NOTIMPLEMENTED) || defined(SYSMUTEXTRYENTER_NOTIMPLEMENTED)
	#define USE_SysMutexTryEnter
	#define EXT_SysMutexTryEnter
	#define GET_SysMutexTryEnter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMutexTryEnter(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMutexTryEnter  FALSE
	#define EXP_SysMutexTryEnter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMutexTryEnter
	#define EXT_SysMutexTryEnter
	#define GET_SysMutexTryEnter(fl)  CAL_CMGETAPI( "SysMutexTryEnter" ) 
	#define CAL_SysMutexTryEnter  SysMutexTryEnter
	#define CHK_SysMutexTryEnter  TRUE
	#define EXP_SysMutexTryEnter  CAL_CMEXPAPI( "SysMutexTryEnter" ) 
#elif defined(MIXED_LINK) && !defined(SYSMUTEX_EXTERNAL)
	#define USE_SysMutexTryEnter
	#define EXT_SysMutexTryEnter
	#define GET_SysMutexTryEnter(fl)  CAL_CMGETAPI( "SysMutexTryEnter" ) 
	#define CAL_SysMutexTryEnter  SysMutexTryEnter
	#define CHK_SysMutexTryEnter  TRUE
	#define EXP_SysMutexTryEnter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMutexTryEnter", (RTS_UINTPTR)SysMutexTryEnter, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysMutexSysMutexTryEnter
	#define EXT_SysMutexSysMutexTryEnter
	#define GET_SysMutexSysMutexTryEnter  ERR_OK
	#define CAL_SysMutexSysMutexTryEnter(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysMutex->ISysMutexTryEnter() : ((ISysMutex*)p0)->ISysMutexTryEnter())
	#define CHK_SysMutexSysMutexTryEnter  (pISysMutex != NULL)
	#define EXP_SysMutexSysMutexTryEnter  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMutexTryEnter
	#define EXT_SysMutexTryEnter
	#define GET_SysMutexTryEnter(fl)  CAL_CMGETAPI( "SysMutexTryEnter" ) 
	#define CAL_SysMutexTryEnter(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysMutex->ISysMutexTryEnter() : ((ISysMutex*)p0)->ISysMutexTryEnter())
	#define CHK_SysMutexTryEnter  (pISysMutex != NULL)
	#define EXP_SysMutexTryEnter  CAL_CMEXPAPI( "SysMutexTryEnter" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMutexTryEnter  PFSYSMUTEXTRYENTER pfSysMutexTryEnter;
	#define EXT_SysMutexTryEnter  extern PFSYSMUTEXTRYENTER pfSysMutexTryEnter;
	#define GET_SysMutexTryEnter(fl)  s_pfCMGetAPI2( "SysMutexTryEnter", (RTS_VOID_FCTPTR *)&pfSysMutexTryEnter, (fl), 0, 0)
	#define CAL_SysMutexTryEnter  pfSysMutexTryEnter
	#define CHK_SysMutexTryEnter  (pfSysMutexTryEnter != NULL)
	#define EXP_SysMutexTryEnter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMutexTryEnter", (RTS_UINTPTR)SysMutexTryEnter, 0, 0) 
#endif




/**
 * <description>
 *  Enter the given mutex. If the mutex is still entered by another task1, the actual task2 will be blocked,
 *	until the task1 has called SysMutexLeave().
 *
 *	IMPLEMENTATION NOTE:
 *		The mutexes must work recursive! That means, that a multiple call out of one task
 *		must not block the execution! For each SysMutexEnter() call, a corresponding SysMutexLeave()
 *		must be used!
 * </description>
 * <param name="hSem" type="IN">Handle to the mutex that is provided from SysMutexCreate()</param>
 * <result>
 * One of:
 * - ERR_OK: The mutex was enterd successful.
 * - ERR_INVALID_HANDLE: The given mutex isn't a valid mutex handle.
 * - ERR_FAILED: An internal error occurred.
 * </result>
 */
RTS_RESULT CDECL SysMutexEnter(RTS_HANDLE hMutex);
typedef RTS_RESULT (CDECL * PFSYSMUTEXENTER) (RTS_HANDLE hMutex);
#if defined(SYSMUTEX_NOTIMPLEMENTED) || defined(SYSMUTEXENTER_NOTIMPLEMENTED)
	#define USE_SysMutexEnter
	#define EXT_SysMutexEnter
	#define GET_SysMutexEnter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMutexEnter(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMutexEnter  FALSE
	#define EXP_SysMutexEnter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMutexEnter
	#define EXT_SysMutexEnter
	#define GET_SysMutexEnter(fl)  CAL_CMGETAPI( "SysMutexEnter" ) 
	#define CAL_SysMutexEnter  SysMutexEnter
	#define CHK_SysMutexEnter  TRUE
	#define EXP_SysMutexEnter  CAL_CMEXPAPI( "SysMutexEnter" ) 
#elif defined(MIXED_LINK) && !defined(SYSMUTEX_EXTERNAL)
	#define USE_SysMutexEnter
	#define EXT_SysMutexEnter
	#define GET_SysMutexEnter(fl)  CAL_CMGETAPI( "SysMutexEnter" ) 
	#define CAL_SysMutexEnter  SysMutexEnter
	#define CHK_SysMutexEnter  TRUE
	#define EXP_SysMutexEnter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMutexEnter", (RTS_UINTPTR)SysMutexEnter, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysMutexSysMutexEnter
	#define EXT_SysMutexSysMutexEnter
	#define GET_SysMutexSysMutexEnter  ERR_OK
	#define CAL_SysMutexSysMutexEnter(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysMutex->ISysMutexEnter() : ((ISysMutex*)p0)->ISysMutexEnter())
	#define CHK_SysMutexSysMutexEnter  (pISysMutex != NULL)
	#define EXP_SysMutexSysMutexEnter  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMutexEnter
	#define EXT_SysMutexEnter
	#define GET_SysMutexEnter(fl)  CAL_CMGETAPI( "SysMutexEnter" ) 
	#define CAL_SysMutexEnter(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysMutex->ISysMutexEnter() : ((ISysMutex*)p0)->ISysMutexEnter())
	#define CHK_SysMutexEnter  (pISysMutex != NULL)
	#define EXP_SysMutexEnter  CAL_CMEXPAPI( "SysMutexEnter" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMutexEnter  PFSYSMUTEXENTER pfSysMutexEnter;
	#define EXT_SysMutexEnter  extern PFSYSMUTEXENTER pfSysMutexEnter;
	#define GET_SysMutexEnter(fl)  s_pfCMGetAPI2( "SysMutexEnter", (RTS_VOID_FCTPTR *)&pfSysMutexEnter, (fl), 0, 0)
	#define CAL_SysMutexEnter  pfSysMutexEnter
	#define CHK_SysMutexEnter  (pfSysMutexEnter != NULL)
	#define EXP_SysMutexEnter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMutexEnter", (RTS_UINTPTR)SysMutexEnter, 0, 0) 
#endif




/**
 * <description>
 *  Leave the given mutex.
 * </description>
 * <param name="hMutex" type="IN">Handle to the mutex that is provided from SysMutexCreate()</param>
 * <result>
 * One of:
 * - ERR_OK: The mutex was leafed successful.
 * - ERR_INVALID_HANDLE: The given mutex isn't a valid mutex handle.
 * - ERR_FAILED: An internal error occured.
 * </result>
 */
RTS_RESULT CDECL SysMutexLeave(RTS_HANDLE hMutex);
typedef RTS_RESULT (CDECL * PFSYSMUTEXLEAVE) (RTS_HANDLE hMutex);
#if defined(SYSMUTEX_NOTIMPLEMENTED) || defined(SYSMUTEXLEAVE_NOTIMPLEMENTED)
	#define USE_SysMutexLeave
	#define EXT_SysMutexLeave
	#define GET_SysMutexLeave(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMutexLeave(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMutexLeave  FALSE
	#define EXP_SysMutexLeave  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMutexLeave
	#define EXT_SysMutexLeave
	#define GET_SysMutexLeave(fl)  CAL_CMGETAPI( "SysMutexLeave" ) 
	#define CAL_SysMutexLeave  SysMutexLeave
	#define CHK_SysMutexLeave  TRUE
	#define EXP_SysMutexLeave  CAL_CMEXPAPI( "SysMutexLeave" ) 
#elif defined(MIXED_LINK) && !defined(SYSMUTEX_EXTERNAL)
	#define USE_SysMutexLeave
	#define EXT_SysMutexLeave
	#define GET_SysMutexLeave(fl)  CAL_CMGETAPI( "SysMutexLeave" ) 
	#define CAL_SysMutexLeave  SysMutexLeave
	#define CHK_SysMutexLeave  TRUE
	#define EXP_SysMutexLeave  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMutexLeave", (RTS_UINTPTR)SysMutexLeave, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysMutexSysMutexLeave
	#define EXT_SysMutexSysMutexLeave
	#define GET_SysMutexSysMutexLeave  ERR_OK
	#define CAL_SysMutexSysMutexLeave(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysMutex->ISysMutexLeave() : ((ISysMutex*)p0)->ISysMutexLeave())
	#define CHK_SysMutexSysMutexLeave  (pISysMutex != NULL)
	#define EXP_SysMutexSysMutexLeave  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMutexLeave
	#define EXT_SysMutexLeave
	#define GET_SysMutexLeave(fl)  CAL_CMGETAPI( "SysMutexLeave" ) 
	#define CAL_SysMutexLeave(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysMutex->ISysMutexLeave() : ((ISysMutex*)p0)->ISysMutexLeave())
	#define CHK_SysMutexLeave  (pISysMutex != NULL)
	#define EXP_SysMutexLeave  CAL_CMEXPAPI( "SysMutexLeave" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMutexLeave  PFSYSMUTEXLEAVE pfSysMutexLeave;
	#define EXT_SysMutexLeave  extern PFSYSMUTEXLEAVE pfSysMutexLeave;
	#define GET_SysMutexLeave(fl)  s_pfCMGetAPI2( "SysMutexLeave", (RTS_VOID_FCTPTR *)&pfSysMutexLeave, (fl), 0, 0)
	#define CAL_SysMutexLeave  pfSysMutexLeave
	#define CHK_SysMutexLeave  (pfSysMutexLeave != NULL)
	#define EXP_SysMutexLeave  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMutexLeave", (RTS_UINTPTR)SysMutexLeave, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSYSMUTEXCREATE ISysMutexCreate;
 	PFSYSMUTEXDELETE ISysMutexDelete;
 	PFSYSMUTEXTRYENTER ISysMutexTryEnter;
 	PFSYSMUTEXENTER ISysMutexEnter;
 	PFSYSMUTEXLEAVE ISysMutexLeave;
 } ISysMutex_C;

#ifdef CPLUSPLUS
class ISysMutex : public IBase
{
	public:
		virtual RTS_HANDLE CDECL ISysMutexCreate(RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISysMutexDelete(void) =0;
		virtual RTS_RESULT CDECL ISysMutexTryEnter(void) =0;
		virtual RTS_RESULT CDECL ISysMutexEnter(void) =0;
		virtual RTS_RESULT CDECL ISysMutexLeave(void) =0;
};
	#ifndef ITF_SysMutex
		#define ITF_SysMutex static ISysMutex *pISysMutex = NULL;
	#endif
	#define EXTITF_SysMutex
#else	/*CPLUSPLUS*/
	typedef ISysMutex_C		ISysMutex;
	#ifndef ITF_SysMutex
		#define ITF_SysMutex
	#endif
	#define EXTITF_SysMutex
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSMUTEXITF_H_*/
