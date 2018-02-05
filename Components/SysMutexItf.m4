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

SET_INTERFACE_NAME(`SysMutex')

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
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysMutexCreate',`(RTS_RESULT *pResult)')

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
DEF_DELETEITF_API(`RTS_RESULT',`CDECL',`SysMutexDelete',`(RTS_HANDLE hMutex)')

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
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysMutexTryEnter',`(RTS_HANDLE hMutex)')

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
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysMutexEnter',`(RTS_HANDLE hMutex)')

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
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysMutexLeave',`(RTS_HANDLE hMutex)')

#ifdef __cplusplus
}
#endif
