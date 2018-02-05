/**
 * <interfacename>SysEvent</interfacename>
 * <description> 
 *	<p>The SysEvent interface is projected to use an operating system event to activate a task. So this component
 *	can only be used on systems with tasks!</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysEvent')

#include "CmpStd.h"

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Create a new event object specified with name. Two components can open the same event, if they specify
 *	the same name.
 *	<p>IMPLEMENTATION NOTE:</p>
 *	<ul>
 *		<li>If a name is specified in szEvent, typically a system wide event is created.</li>
 *		<li>If an event still exists with this name, the routine returns the handle to the existing event</li>
 *		<li>szEvent can be NULL, so a new unique event with an empty name must be created</li>
 *		<li>If SysEventWait() is done after SysEventSet(), the event should signal the task!</li>
 *		<li>An event must not be used to signal several tasks!</li>
 *	</ul>
 *	<p>TARGET SPECIFIC IMPLEMENTATION:</p>
 *	<ul>
 *		<li>CoDeSys Control RTE:
 *			- If szEvent is specified, the event will work as a system wide Windows event. In this case, every call to SysEventSet/Wait will 
 *				call the corresponding Windows API-functions and this may last an unpredictable time!
 *			- In case SysEventCreate is called with a NULL-pointer in szEvent, the event can be used to synchronize RTE-tasks only. The calls
 *				to SysEventSet/Wait keep their real time capabilities.
 *		</li> 
 *  </ul>
 * </description>
 * <result><p>RESULT: Handle to the event or RTS_INVALID_HANDLE if failed.</p></result>
 */
typedef struct tagsyseventcreate_struct
{
	RTS_IEC_STRING *szEvent;			/* VAR_INPUT */	/* <param name="szEvent" type="IN">Name for the new event. Can be NULL!</param> */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library)</param> */
	RTS_IEC_HANDLE SysEventCreate;		/* VAR_OUTPUT */	
} syseventcreate_struct;

DEF_API(`void',`CDECL',`syseventcreate',`(syseventcreate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x67712592),0x03050500)

/**
 * <description>Delete an exisiting event object</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsyseventdelete_struct
{
	RTS_IEC_HANDLE hEvent;				/* VAR_INPUT */	/* <param name="hEvent" type="IN">Handle of the event</param> */
	RTS_IEC_RESULT SysEventDelete;		/* VAR_OUTPUT */	
} syseventdelete_struct;

DEF_API(`void',`CDECL',`syseventdelete',`(syseventdelete_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x97BA564C),0x03050500)

/**
 * <description>Set the given Event. With this operation, a task is activated if it waits for the
 *	event with SysEventWait.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsyseventset_struct
{
	RTS_IEC_HANDLE hEvent;				/* VAR_INPUT */	/* <param name="hEvent" type="IN">Handle of the event</param> */
	RTS_IEC_RESULT SysEventSet;			/* VAR_OUTPUT */	
} syseventset_struct;

DEF_API(`void',`CDECL',`syseventset',`(syseventset_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xBDDBC5FE),0x03050500)

/**
 * <description>Wait for the given Event</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library):
 *	<ul>
 *		<li>ERR_OK: if event was received</li>
 *		<li>ERR_TIMEOUT: for timeout</li>
 *	</ul>
 * </p></result>
 */
typedef struct tagsyseventwait_struct
{
	RTS_IEC_HANDLE hEvent;				/* VAR_INPUT */	/* <param name="hEvent" type="IN">Handle of the event</param> */
	RTS_IEC_UDINT ulTimeout;			/* VAR_INPUT */	/* <param name="lTimeout" type="IN">Timeout in ms to wait for the event:
	<ul>
		<li>ulTimeout = 16#FFFFFFFF: means infinite wait</li>
		<li>ulTimeout = 0: means no wait, only check the event!</li>
	</ul>
 </param> */
	RTS_IEC_RESULT SysEventWait;		/* VAR_OUTPUT */	
} syseventwait_struct;

DEF_API(`void',`CDECL',`syseventwait',`(syseventwait_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x34C44553),0x03050500)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#define SYSEVENT_WAIT_INFINITE	((long)-1)

#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysEventOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysEventOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>
 *	<p>Create a new event object specified with name. Two components can open the same event, if they sepecify
 *	the same name.</p>
 *	<p>IMPLEMENTATION NOTE:</p>
 *	<ul>
 *		<li>If a name is specified in pszName, typically a system wide event is created.</li>
 *		<li>If an event still exists with this name, the routine returns the handle to the existing event</li>
 *		<li>pszName can be NULL, so a new unique event with an empty name must be created</li>
 *		<li>If SysEventWait() is done after SysEventSet(), the event should signal the task!</li>
 *		<li>An event must not be used to signal several tasks!</li>
 *	</ul>
 *	<p>TARGET SPECIFIC IMPLEMENTATION:</p>
 *	<ul>
 *		<li>CoDeSys Control RTE:
 *			- If pszName is specified, the event will work as a system wide Windows event. In this case, every call to SysEventSet/Wait will 
 *				call the corresponding Windows API-functions and this may last an unpredictable time!
 *			- In case SysEventCreate is called with a NULL-pointer in pszName, the event can be used to synchronize RTE-tasks only. The calls
 *				to SysEventSet/Wait keep their real time capabilities.
 *		</li> 
 *  </ul>
 * </description>
 * <param name="pszName" type="IN">Name for the new event. Can be NULL!</param>
 * <param name="pResult" type="OUT">Pointer to error code </param>
 * <result>Handle to the event or RTS_INVALID_HANDLE if failed</result>
 */
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysEventCreate',`(char *pszName, RTS_RESULT *pResult)')

/**
 * <description>Delete an exisiting event object</description>
 * <param name="hEvent" type="IN">Handle to the event. If hEvent is RTS_INVALID_HANDLE, 
 *	function returned with an error</param>
 * <result>error code</result>
 */
DEF_DELETEITF_API(`RTS_RESULT',`CDECL',`SysEventDelete',`(RTS_HANDLE hEvent)')

/**
 * <description>Set the given Event. With this operation, a task is activated, if this task waits for the
 *	event (see SysEventWait).</description>
 * <param name="hEvent" type="IN">Handle to the event. If hEvent is RTS_INVALID_HANDLE, 
 *	function returned with an error</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysEventSet',`(RTS_HANDLE hEvent)')

/**
 * <description>Wait for the given Event</description>
 * <param name="hEvent" type="IN">Handle to the event. If hEvent is RTS_INVALID_HANDLE, 
 *	function returned with an error</param>
 * <param name="lTimeout" type="IN">Timeout in ms to wait for the event.
 *	<ul>
 *		<li>lTimeout = -1 (SYSEVENT_WAIT_INFINITE): means infinite wait</li>
 *		<li>lTimeout = 0: means no wait, only checks the event!</li>
 *	</ul>
 * </param>
 * <result>error code:
 * <ul>
 *		<li>ERR_OK: if event was received</li>
 *		<li>ERR_TIMEOUT: for timeout</li>
 * </ul>
 * </result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysEventWait',`(RTS_HANDLE hEvent, long lTimeout)')

#ifdef __cplusplus
}
#endif
