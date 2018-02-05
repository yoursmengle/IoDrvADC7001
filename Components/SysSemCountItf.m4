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

SET_INTERFACE_NAME(`SysSemCount')

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
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysSemCountCreate',`(RTS_UI32 ui32InitialValue, RTS_RESULT *pResult)')

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
DEF_DELETEITF_API(`RTS_RESULT',`CDECL',`SysSemCountDelete',`(RTS_HANDLE hSemaphore)')

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
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysSemCountEnter',`(RTS_HANDLE hSemaphore, RTS_UI32 ui32TimeoutMs)')

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
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysSemCountLeave',`(RTS_HANDLE hSemaphore)')

#ifdef __cplusplus
}
#endif
