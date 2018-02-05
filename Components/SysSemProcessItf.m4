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

SET_INTERFACE_NAME(`SysSemProcess')

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

DEF_API(`void',`CDECL',`syssemprocesscreate',`(syssemprocesscreate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x56515D0D),0x03050500)

/**
 * <description>Delete a semaphore object</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsyssemprocessdelete_struct
{
	RTS_IEC_HANDLE hSem;				/* VAR_INPUT */	/* <param name="hSem" type="IN">Handle to the semaphore</param> */
	RTS_IEC_RESULT SysSemProcessDelete;	/* VAR_OUTPUT */	
} syssemprocessdelete_struct;

DEF_API(`void',`CDECL',`syssemprocessdelete',`(syssemprocessdelete_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xDBBE905D),0x03050500)

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

DEF_API(`void',`CDECL',`syssemprocessenter',`(syssemprocessenter_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x8A9203CC),0x03050500)

/**
 * <description>Leave the given semaphore.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsyssemprocessleave_struct
{
	RTS_IEC_HANDLE hSem;				/* VAR_INPUT */	/* <param name="hSem" type="IN">Handle to the semaphore</param> */
	RTS_IEC_RESULT SysSemProcessLeave;	/* VAR_OUTPUT */	
} syssemprocessleave_struct;

DEF_API(`void',`CDECL',`syssemprocessleave',`(syssemprocessleave_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4816900D),0x03050500)

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
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysSemProcessCreate',`(char *pszName, RTS_RESULT *pResult)')

/**
 * <description>
 *	Delete a semaphore object 
 * </description>
 * <param name="hSem" type="IN">Handle to the semaphore</param>
 * <result>error code</result>
 */
DEF_DELETEITF_API(`RTS_RESULT',`CDECL',`SysSemProcessDelete',`(RTS_HANDLE hSem)')

/**
 * <description>
 *  Enter the given semaphore.
 * </description>
 * <param name="hSem" type="IN">Handle to the semaphore</param>
 * <param name="ulTimeoutMs" type="IN">Timeout in milliseconds to wait to enter the semaphore or
 *				SYSSEMPROCESS_WAIT_INFINITE for an infinite wait.</param>
 * <result>ERR_OK or ERR_TIMEOUT if timeout expires before enter the semaphore</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysSemProcessEnter',`(RTS_HANDLE hSem, unsigned long ulTimeoutMs)')

/**
 * <description>
 *  Leave the given semaphore.
 * </description>
 * <param name="hSem" type="IN">Handle to the semaphore</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysSemProcessLeave',`(RTS_HANDLE hSem)')

#ifdef __cplusplus
}
#endif
