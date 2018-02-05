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

SET_INTERFACE_NAME(`SysSem')

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

DEF_API(`void',`CDECL',`syssemcreate',`(syssemcreate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x9344C747),0x03050500)

/**
 * This function deletes the semaphore which is identified by its handle
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsyssemdelete_struct
{
	RTS_IEC_HANDLE hSem;				/* VAR_INPUT */	/* Handle of the semaphore */
	RTS_IEC_RESULT SysSemDelete;		/* VAR_OUTPUT */	
} syssemdelete_struct;

DEF_API(`void',`CDECL',`syssemdelete',`(syssemdelete_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x88B7C7F6),0x03050500)

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

DEF_API(`void',`CDECL',`syssementer',`(syssementer_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x85E1C5F9),0x03050500)

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

DEF_API(`void',`CDECL',`syssemleave',`(syssemleave_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x2AA5DCFF),0x03050500)

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

DEF_API(`void',`CDECL',`syssemtry',`(syssemtry_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x14382CB4),0x03050500)

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
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysSemCreate',`(RTS_RESULT *pResult)')

/**
 * <description>
 *	Delete a semaphore object 
 * </description>
 * <param name="hSem" type="IN">Handle to the semaphore that is provided from SysSemCreate()</param>
 * <result>error code</result>
 */
DEF_DELETEITF_API(`RTS_RESULT',`CDECL',`SysSemDelete',`(RTS_HANDLE hSem)')

/**
 * <description>
 *  Try to enter the semaphore. If semaphore is available, the function 
 *	entered the semaphore and returned ERR_OK. If semaphore is not available, ERR_FAILED is returned. 
 * </description>
 * <param name="hSem" type="IN">Handle to the semaphore that is provided from SysSemCreate()</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysSemTry',`(RTS_HANDLE hSem)')

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
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysSemEnter',`(RTS_HANDLE hSem)')

/**
 * <description>
 *  Leave the given semaphore.
 * </description>
 * <param name="hSem" type="IN">Handle to the semaphore that is provided from SysSemCreate()</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysSemLeave',`(RTS_HANDLE hSem)')

#ifdef __cplusplus
}
#endif
