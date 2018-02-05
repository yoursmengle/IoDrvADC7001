/**
 * <interfacename>CmpSupervisor</interfacename>
 * <description> 
 * This interface provides a generic and easy to handle supervisor for all vital operations in the runtime system.
 * This interface can be used for example to retrigger a hardware watchdog to detect a failure in such a vital operation (in case of a software error).
 *
 * Interface can be used to: 
 * <ul>
 *		<li>Register/unregister a vital operation for supervision</li>
 *		<li>Retrigger a vital operation to be alive</li>
 *		<li>There is an explicit dead signal for desperate situations such as memory overwrite, etc. For these operations stTimeoutUs should be set to 0 to disable time check</li>
 *		<li>Interfaces to read the global state of all vital operations and to interate over all vital operations</li>
 * </ul>
 * <p>
 * Use case: Use supervisor to support a hardware watchdog:
 * A cyclic task checks SupervisorOperationGetState2() periodically and retriggers the hardware watchdog. In case the nNumOfFailedOperations is greater than 0 the cyclic task can
 * <ul>
 *		<li>just prevent the retriggering of the hardware watchdog so that it expires or</li>
 *		<li>check the causing operation and in the case it is not that important, give a second chance by reactivating its supervision.
 *			This is done by iterating through all operations by SupervisorOperationGetFirst(), SupervisorOperationGetNext(), and SupervisorOperationGetEntry() to find the causing operation
 *			and then by calling SupervisorOperationDisable() followed by SupervisorOperationEnable() to reactivate the supervision of the operation.</li>
 * </ul>
 * </p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpSupervisor')

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * Setting to specify the timeout of the supervision of the Comm Cycle in seconds (e.g. for the hardware watchdog).
 * Default: 60.
 * </description>
 */
#define SUPERVISORKEY_INT_COMM_CYCLE_TIMEOUT					"CommCycleTimeout"
#ifndef SUPERVISORKEY_INT_COMM_CYCLE_TIMEOUT_DEFAULT
	#define SUPERVISORKEY_INT_COMM_CYCLE_TIMEOUT_DEFAULT		INT32_C(60)
#endif

/**
 * <category>OperationID</category>
 * <description>Operation ID for the supervision of the Comm Cycle</description>
 * <param name="RTS_OPID_CommCycle" type="IN"></param>
 * <param name="RTS_OPID_CommCycle_Description" type="IN"></param>
 */
#define RTS_OPID_CommCycle					1
#define RTS_OPID_CommCycle_Description		"Comm Cycle"

/**
 * <category>Supervisor flags</category>
 * <element name="RTS_SUPERVISOR_FLAG_NONE" type="IN">No flag specified</element>
 * <element name="RTS_SUPERVISOR_FLAG_RESET_NECESSARY" type="IN">TODO</element>
 * <element name="RTS_SUPERVISOR_FLAG_WATCHDOG" type="IN">This is a watchdog (consumer), that uses the supervisor to protect the controller!
 *	NOTE:
 *	This consumer can be disabled via the standard function SupervisorOperationDisable() and so this watchdog will not expire, if any of the supervisor operations will fail!
 * </element>
 */
#define RTS_SUPERVISOR_FLAG_NONE				0
#define RTS_SUPERVISOR_FLAG_RESET_NECESSARY		0x00000001
#define RTS_SUPERVISOR_FLAG_WATCHDOG			0x00010000


/**
 * <category>Event parameter</category>
 * <element name="nNumOfOperations" type="IN">Number of operations that are registered and supervised</element>
 * <element name="nNumOfFailedOperations" type="IN">Number of failed operations. 0=All operations alive</element>
 * <element name="nNumOfRegisteredOperations" type="IN">Number of all registered operations</element>
 */
typedef struct
{
	RTS_UI32 nNumOfOperations;
	RTS_UI32 nNumOfFailedOperations;
	RTS_UI32 nNumOfRegisteredOperations;
} EVTPARAM_CmpSupervisor_StateChanged;
#define EVTPARAMID_CmpSupervisor_StateChanged	0x0001
#define EVTVERSION_CmpSupervisor_StateChanged	0x0001

/**
 * <category>Events</category>
 * <description>Event is sent if the state of the supervisor has changed:
 *	- if number of operations has changed
 *	- or if at least one failed vital operation is detected
 * </description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpSupervisor_StateChanged</param>
 */
#define EVT_Supervisor_StateChanged				MAKE_EVENTID(EVTCLASS_INFO, 1)


/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>SupervisorInstance</description>
 */
typedef struct tagSupervisorInstance
{
	RTS_IEC_HANDLE hInstance;		/* Handle to the instance */
	RTS_IEC_UDINT idInstance;		/* Id of the instance */
	RTS_IEC_BOOL xIsIECInstance;		/* TRUE=hInstance is an IEC instance, FALSE=hInstance is a runtime handle */
} SupervisorInstance;

/**
 * Single operation/function that is supervised.
 */
typedef struct tagSupervisorEntry
{
	RTS_IEC_DWORD cmpId;		/* ComponentID of the component which operation is supervised */
	RTS_IEC_DWORD ui32OperationID;		/* Unique operation ID */
	RTS_IEC_STRING *pszOperationDescription;		/* Description of the operation */
	RTS_IEC_ULINT stLastActiveUs;		/* Timestamp of last activity in [us] */
	RTS_IEC_ULINT stTimeoutUs;		/* Optional timeout limit in [us] */
	RTS_IEC_DWORD flags;		/* See SupervisorFlags for details. Don't modify the other bits!! */
	RTS_IEC_BOOL bEnable;		/* Is supervised, FALSE=Is not supervised */
	RTS_IEC_BOOL bAlive;		/* TRUE=Alive, FALSE=Dead */
	SupervisorInstance instance;		/* Instance identification */
	RTS_IEC_HANDLE hSync;		/* handle to synchronize 64Bit timestamp access */
} SupervisorEntry;

/**
 * <description>SupervisorState</description>
 */
typedef struct tagSupervisorState
{
	RTS_IEC_UDINT nNumOfOperations;		/* Number of registered operations that are supervised/enabled */
	RTS_IEC_UDINT nNumOfFailedOperations;		/* Number of failed operations. 0=All operations alive */
	RTS_IEC_UDINT nNumOfRegisteredOperations;		/* Number of all registered operations */
} SupervisorState;

/**
 * Reassures the alive state of the operation with the given timestamp in order to retrigger the hardware watchdog
 *
 * :return: Error code
 *
 * Error code:
 *     + ERR_OK: Alive state was successfully reassured
 *     + ERR_NOTINITIALIZED: The operation memory is not initialized
 *     + ERR_INVALID_HANDLE: The handle to the operation is invalid
 *     + ERR_PARAMETER: The handle to the operation is invalid
 *     + ERR_NO_CHANGE: Supervision is disabled for the operation
 *     + ERR_NOT_SUPPORTED">SysTimeGetUs is not supported
 */
typedef struct tagsupervisoroperationalive_struct
{
	RTS_IEC_HANDLE hOperation;			/* VAR_INPUT */	/* Handle to the operation */
	RTS_IEC_ULINT *pstTimestampUs;		/* VAR_INPUT */	/* Pointer to timestamp. May be NULL, if time check is enabled timestamp is set to current time. */
	RTS_IEC_RESULT SupervisorOperationAlive;	/* VAR_OUTPUT */	
} supervisoroperationalive_struct;

DEF_API(`void',`CDECL',`supervisoroperationalive',`(supervisoroperationalive_struct *p)',1,0x33C47EE3,0x03050C00)

/**
 * Signals a desperate situation of an operation in order to prevent the retriggering of the hardware watchdog. After this call, the operation is marked immediate as failed!
 *
 * :return: Error code
 *
 * Error code:
 *     + ERR_OK: Dead state was successfully signalled
 *     + ERR_NOTINITIALIZED: The operation memory is not initialized
 *     + ERR_INVALID_HANDLE: The handle to the operation is invalid
 *     + ERR_PARAMETER: The handle to the operation is invalid
 *     + ERR_NO_CHANGE: Supervision is disabled for the operation
 */
typedef struct tagsupervisoroperationdead_struct
{
	RTS_IEC_HANDLE hOperation;			/* VAR_INPUT */	/* Handle to the operation */
	RTS_IEC_RESULT SupervisorOperationDead;	/* VAR_OUTPUT */	
} supervisoroperationdead_struct;

DEF_API(`void',`CDECL',`supervisoroperationdead',`(supervisoroperationdead_struct *p)',1,0x709DF6D1,0x03050C00)

/**
 * Disables supervision for this operation. This operation will never be supervised, until the next SupervisorOperationEnable() call!
 *
 * :return: Error code
 *
 * Error code:
 *     + ERR_OK: Supervision was successfully disabled
 *     + ERR_NOTINITIALIZED: The operation memory is not initialized
 *     + ERR_INVALID_HANDLE: The handle to the operation is invalid
 *     + ERR_PARAMETER: The handle to the operation is invalid
 *     + ERR_NO_CHANGE: The operation is already disabled
 */
typedef struct tagsupervisoroperationdisable_struct
{
	RTS_IEC_HANDLE hOperation;			/* VAR_INPUT */	/* Handle to the operation */
	RTS_IEC_RESULT SupervisorOperationDisable;	/* VAR_OUTPUT */	
} supervisoroperationdisable_struct;

DEF_API(`void',`CDECL',`supervisoroperationdisable',`(supervisoroperationdisable_struct *p)',1,0xD5C85590,0x03050C00)

/**
 * Enables supervision for this operation: Sets timestamp to current time and alive flag
 *
 * :return: Error code
 *
 * Error code:
 *     + ERR_OK: Supervision was successfully enabled
 *     + ERR_NOTINITIALIZED: The operation memory is not initialized
 *     + ERR_INVALID_HANDLE: The handle to the operation is invalid
 *     + ERR_PARAMETER: The handle to the operation is invalid
 *     + ERR_NO_CHANGE: The operation is already supervised
 *     + ERR_NOT_SUPPORTED">SysTimeGetUs is not supported
 */
typedef struct tagsupervisoroperationenable_struct
{
	RTS_IEC_HANDLE hOperation;			/* VAR_INPUT */	/* Handle to the operation */
	RTS_IEC_RESULT SupervisorOperationEnable;	/* VAR_OUTPUT */	
} supervisoroperationenable_struct;

DEF_API(`void',`CDECL',`supervisoroperationenable',`(supervisoroperationenable_struct *p)',1,0x8FCDAEB8,0x03050C00)

/**
 * Returns the SupervisorEntry of a given operation handle
 *
 * Error code:
 *     + ERR_OK: The SupervisorEntry was successfully retrieved
 *     + ERR_INVALID_HANDLE: The handle to the operation is invalid
 *     + ERR_PARAMETER: The handle to the operation is invalid
 *
 * :return: Pointer to SupervisorEntry of the given operation handle or NULL in case of an error
 * 
 */
typedef struct tagsupervisoroperationgetentry_struct
{
	RTS_IEC_HANDLE hOperation;			/* VAR_INPUT */	/* Handle to the operation */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to error code */
	SupervisorEntry *SupervisorOperationGetEntry;	/* VAR_OUTPUT */	
} supervisoroperationgetentry_struct;

DEF_API(`void',`CDECL',`supervisoroperationgetentry',`(supervisoroperationgetentry_struct *p)',1,0,0x03050C00)

/**
 * Iteration interface to get the first registered operation
 *
 * Error code:
 *     + ERR_OK: The first operation was successfully retrieved
 *     + ERR_NOTINITIALIZED: The operation memory is not initialized
 *     + ERR_NO_OBJECT: There are no registered operations 
 *
 * :return: Handle to the first operation or RTS_INVALID_HANDLE in case of an error
 * 
 */
typedef struct tagsupervisoroperationgetfirst_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to error code */
	RTS_IEC_HANDLE SupervisorOperationGetFirst;	/* VAR_OUTPUT */	
} supervisoroperationgetfirst_struct;

DEF_API(`void',`CDECL',`supervisoroperationgetfirst',`(supervisoroperationgetfirst_struct *p)',1,0x33144D0D,0x03050C00)

/**
 * Iteration interface to get the next registered operation. Must be started with SupervisorOperationGetFirst()
 *
 * Error code:
 *     + ERR_OK: The next operation was successfully retrieved
 *     + ERR_NOTINITIALIZED: The operation memory is not initialized
 *     + ERR_END_OF_OBJECT: There are no registered operations left 
 *
 * :return: Handle to the first operation or RTS_INVALID_HANDLE in case of an error
 * 
 */
typedef struct tagsupervisoroperationgetnext_struct
{
	RTS_IEC_HANDLE hPrevOperation;		/* VAR_INPUT */	/* Handle to the previous operation retrieved via SupervisorOperationGetFirst() or subsequent calls of SupervisorOperationGetNext() */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to error code */
	RTS_IEC_HANDLE SupervisorOperationGetNext;	/* VAR_OUTPUT */	
} supervisoroperationgetnext_struct;

DEF_API(`void',`CDECL',`supervisoroperationgetnext',`(supervisoroperationgetnext_struct *p)',1,0x45054F88,0x03050C00)

/**
 *  Deprecated, use SupervisorOperationGetState2 instead.
 *
 *  Returns the global supervisor state for all supervised operations! Here you can check with one call how many operations failed.
 *
 * Error code:
 *     + ERR_OK: The SupervisorState was successfully retrieved
 *     + ERR_NOTINITIALIZED: The operation memory is not initialized
 *     + ERR_NOT_SUPPORTED">SysTimeGetUs is not supported
 *
 * :return: A pointer to the SupervisorState or NULL in case of an error
 */
typedef struct tagsupervisoroperationgetstate_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to error code */
	SupervisorState *SupervisorOperationGetState;	/* VAR_OUTPUT */	
} supervisoroperationgetstate_struct;

DEF_API(`void',`CDECL',`supervisoroperationgetstate',`(supervisoroperationgetstate_struct *p)',1,0,0x03050C00)

/**
 *  Retrieves the supervisor state for all supervised operations! Here you can check with one call how many operations failed.
 *
 * :return: Error code
 *
 * Error code:
 *     + ERR_OK: The SupervisorState was successfully retrieved
 *     + ERR_NOTINITIALIZED: The operation memory is not initialized
 *     + ERR_PARAMETER: The pointer to the SupervisorState is invalid
 *     + ERR_NOT_SUPPORTED">SysTimeGetUs is not supported
 *
 */
typedef struct tagsupervisoroperationgetstate2_struct
{
	SupervisorState *pSupervisorState;	/* VAR_INPUT */	/* Pointer to the SupervisorState, will be filled with the corresponding information. The caller has to hold the buffer. */
	RTS_IEC_RESULT SupervisorOperationGetState2;	/* VAR_OUTPUT */	
} supervisoroperationgetstate2_struct;

DEF_API(`void',`CDECL',`supervisoroperationgetstate2',`(supervisoroperationgetstate2_struct *p)',1,0x284A6A2A,0x03050C00)

/**
 * Register an operation for supervision.
 * The operation will be regtistered disabled! To activate the supervision you have to call a subsequent SupervisorOperationEnable()!
 *
 * Error code:
 *     + ERR_OK: Operation was successfully registered
 *     + ERR_FAILED:  Register operation failed
 *     + ERR_NOTINITIALIZED: The operation memory is not initialized
 *     + ERR_DUPLICATE: The combination of ui32OperationID and cmpId is already registered 
 *     + ERR_NOMEMORY: There is no more memory left to register the operation
 *
 * :return: Handle to operation for all other management functions or RTS_INVALID_HANDLE in case of an error
 */
typedef struct tagsupervisoroperationregister_struct
{
	RTS_IEC_DWORD ui32OperationID;		/* VAR_INPUT */	/* Unique operation ID */
	RTS_IEC_DWORD cmpId;				/* VAR_INPUT */	/* ComponentID of the component which operation is supervised */
	RTS_IEC_STRING *pszOperationDescription;	/* VAR_INPUT */	/* Description of the operation, may be empty; the string must be a constant, it is not copied, just the reference is stored */
	RTS_IEC_ULINT stTimeoutUs;			/* VAR_INPUT */	/* Timeout limit in [us] (enables time check, 0 means no timeout check) */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to error code */
	RTS_IEC_HANDLE SupervisorOperationRegister;	/* VAR_OUTPUT */	
} supervisoroperationregister_struct;

DEF_API(`void',`CDECL',`supervisoroperationregister',`(supervisoroperationregister_struct *p)',1,0x6D8179C0,0x03050C00)

/**
 * Sets a (new) timeout for the given operation
 * Supervision must be disabled to modify the timeout and should be enabled afterwards. 
 *
 * :return: Error code
 *
 * Error code:
 *     + ERR_OK: The timeout was successfully set
 *     + ERR_NOTINITIALIZED: The operation memory is not initialized
 *     + ERR_INVALID_HANDLE: The handle to the operation is invalid
 *     + ERR_PARAMETER: The handle to the operation is invalid
 *     + ERR_NO_CHANGE: The timeout was not modified because supervision is enabled!
 */
typedef struct tagsupervisoroperationsettimeout_struct
{
	RTS_IEC_HANDLE hOperation;			/* VAR_INPUT */	/* Handle to the operation */
	RTS_IEC_ULINT stTimeoutUs;			/* VAR_INPUT */	/* Timeout limit in [us] */
	RTS_IEC_RESULT SupervisorOperationSetTimeout;	/* VAR_OUTPUT */	
} supervisoroperationsettimeout_struct;

DEF_API(`void',`CDECL',`supervisoroperationsettimeout',`(supervisoroperationsettimeout_struct *p)',1,0xDB1591C0,0x03050C00)

/**
 * Unregister a previously registered operation from supervision
 *
 * :return: Error code
 *
 * Error code:
 *     + ERR_OK: Operation was successfully unregistered
 *     + ERR_NOTINITIALIZED: The operation memory is not initialized
 *     + ERR_INVALID_HANDLE: The handle to the operation is invalid
 *     + ERR_PARAMETER: The handle to the operation is invalid
 */
typedef struct tagsupervisoroperationunregister_struct
{
	RTS_IEC_HANDLE hOperation;			/* VAR_INPUT */	/* Handle to the operation */
	RTS_IEC_RESULT SupervisorOperationUnregister;	/* VAR_OUTPUT */	
} supervisoroperationunregister_struct;

DEF_API(`void',`CDECL',`supervisoroperationunregister',`(supervisoroperationunregister_struct *p)',1,0xF19896D6,0x03050C00)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>
 * Register an operation for supervision.
 * The operation will be regtistered disabled! To activate the supervision you have to call a subsequent SupervisorOperationEnable()!
 *
 * NOTES:
 * - Any consumer/hardware watchdog, which controls all vital operations can be registered as a normal operation, but have to set the RTS_SUPERVISOR_FLAG_WATCHDOG flag in its SupervisorEntry!
 * - Additionally the consumer have to check its bEnable flag additionally to the state of the supervisor, if a vital operation will fail! If the bEnable flag is FALSE, you have to continue
 *   retriggering the watchdog, because your watchdog expiration is selectively be disabled!
 * </description>
 * <param name="ui32OperationID" type="IN">Unique operation ID</element>
 * <param name="cmpId" type="IN">ComponentID of the component which operation is supervised</element>
 * <param name="pszOperationDescription" type="IN">Description of the operation, may be NULL; the string must be a constant, it is not copied, just the reference is stored</element>
 * <param name="stTimeoutUs" type="IN">Timeout limit in [us] (enables time check, 0 means no timeout check)</element>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Operation was successfully registered</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_FAILED">Register operation failed</errorcode> 
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOTINITIALIZED">The operation memory is not initialized</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_DUPLICATE">The combination of ui32OperationID and cmpId is already registered</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOMEMORY">There is no more memory left to register the operation</errorcode>
 * <result>Handle to operation for all other management functions or RTS_INVALID_HANDLE in case of an error</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `SupervisorOperationRegister', `(RTS_UI32 ui32OperationID, CMPID cmpId, char *pszOperationDescription, RTS_SYSTIME stTimeoutUs, RTS_RESULT *pResult)')

/**
 * <description>
 * Unregister a previously registered operation from supervision
 * </description>
 * <param name="hOperation" type="IN">Handle to the operation</element>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Operation was successfully unregistered</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOTINITIALIZED">The operation memory is not initialized</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_INVALID_HANDLE">The handle to the operation is invalid</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">The handle to the operation is invalid</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SupervisorOperationUnregister', `(RTS_HANDLE hOperation)')

/**
 * <description>
 * Deprecated, use SupervisorOperationGetState2 instead.
 * Returns the global supervisor state for all supervised operations! Here you can check with one call how many operations failed.
 * </description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">The SupervisorState was successfully retrieved</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOTINITIALIZED">The operation memory is not initialized</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOT_SUPPORTED">SysTimeGetUs is not supported</errorcode>
 * <result>A pointer to the SupervisorState or NULL in case of an error</result>
 */
DEF_ITF_API(`SupervisorState*', `CDECL', `SupervisorOperationGetState', `(RTS_RESULT *pResult)')

/**
 * <description>
 * Returns the global supervisor state for all supervised operations! Here you can check with one call how many operations failed.
 * </description>
 * <param name="pSupervisorState" type="OUT">Pointer to the SupervisorState, will be filled with the corresponding information. The caller has to hold the buffer.</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">The SupervisorState was successfully retrieved</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOTINITIALIZED">The operation memory is not initialized</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">The pointer to the SupervisorState is invalid</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOT_SUPPORTED">SysTimeGetUs is not supported</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SupervisorOperationGetState2', `(SupervisorState *pSupervisorState)')

/**
 * <description>
 * Iteration interface to get the first registered operation
 * </description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">The first operation was successfully retrieved</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOTINITIALIZED">The operation memory is not initialized</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NO_OBJECT">There are no registered operations</errorcode>
 * <result>Handle to the first operation or RTS_INVALID_HANDLE in case of an error</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `SupervisorOperationGetFirst', `(RTS_RESULT *pResult)')

/**
 * <description>
 * Iteration interface to get the next registered operation. Must be started with SupervisorOperationGetFirst()
 * </description>
 * <param name="hPrevOperation" type="IN">Handle to the previous operation retrieved via SupervisorOperationGetFirst() or subsequent calls of SupervisorOperationGetNext()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">The next operation was successfully retrieved</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOTINITIALIZED">The operation memory is not initialized</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_INVALID_HANDLE">The handle to the previous operation is invalid</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">The handle to the previous operation is invalid</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_END_OF_OBJECT">There are no registered operations left</errorcode>
 * <result>Handle to the next operation or RTS_INVALID_HANDLE in case of an error</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `SupervisorOperationGetNext', `(RTS_HANDLE hPrevOperation, RTS_RESULT *pResult)')

/**
 * <description>
 * Returns the SupervisorEntry of a given operation handle
 * </description>
 * <param name="hOperation" type="IN">Handle to the operation</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">The SupervisorEntry was successfully retrieved</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_INVALID_HANDLE">The handle to the operation is invalid</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">The handle to the operation is invalid</errorcode>
 * <result>Pointer to SupervisorEntry of the given operation handle or NULL in case of an error</result>
 */
DEF_ITF_API(`SupervisorEntry*', `CDECL', `SupervisorOperationGetEntry', `(RTS_HANDLE hOperation, RTS_RESULT *pResult)')

/**
 * <description>
 * Enables supervision for this operation: Sets timestamp to current time and alive flag
 * </description>
 * <param name="hOperation" type="IN">Handle to the operation</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Supervision was successfully enabled</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOTINITIALIZED">The operation memory is not initialized</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_INVALID_HANDLE">The handle to the operation is invalid</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">The handle to the operation is invalid</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NO_CHANGE">The operation is already supervised</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOT_SUPPORTED">SysTimeGetUs is not supported</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SupervisorOperationEnable', `(RTS_HANDLE hOperation)')

/**
 * <description>
 * Disables supervision for this operation. This operation will never be supervised, until the next SupervisorOperationEnable() call!
 * </description>
 * <param name="hOperation" type="IN">Handle to the operation</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Supervision was successfully disabled</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOTINITIALIZED">The operation memory is not initialized</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_INVALID_HANDLE">The handle to the operation is invalid</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">The handle to the operation is invalid</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NO_CHANGE">The operation is already disabled</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SupervisorOperationDisable', `(RTS_HANDLE hOperation)')

/**
 * <description>
 * Reassures the alive state of the operation with the given timestamp in order to retrigger the hardware watchdog
 * </description>
 * <param name="hOperation" type="IN">Handle to the operation</param>
 * <param name="pstTimestampUs" type="IN">Pointer to timestamp. May be NULL, if time check is enabled timestamp is set to current time.</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Alive state was successfully reassured</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOTINITIALIZED">The operation memory is not initialized</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_INVALID_HANDLE">The handle to the operation is invalid</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">The handle to the operation is invalid</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NO_CHANGE">Supervision is disabled for the operation</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOT_SUPPORTED">SysTimeGetUs is not supported</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SupervisorOperationAlive', `(RTS_HANDLE hOperation, RTS_SYSTIME *pstTimestampUs)')

/**
 * <description>
 * Signals a desperate situation of an operation in order to prevent the retriggering of the hardware watchdog. After this call, the operation is marked immediate as failed!
 * </description>
 * <param name="hOperation" type="IN">Handle to the operation</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Dead state was successfully signalled</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOTINITIALIZED">The operation memory is not initialized</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_INVALID_HANDLE">The handle to the operation is invalid</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">The handle to the operation is invalid</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NO_CHANGE">Supervision is disabled for the operation</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SupervisorOperationDead', `(RTS_HANDLE hOperation)')

/**
 * <description>
 * Sets a (new) timeout for the given operation
 * Supervision must be disabled to modify the timeout and should be enabled afterwards.
 * </description>
 * <param name="hOperation" type="IN">Handle to the operation</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">The timeout was successfully set</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOTINITIALIZED">The operation memory is not initialized</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_INVALID_HANDLE">The handle to the operation is invalid</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">The handle to the operation is invalid</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NO_CHANGE">The timeout was not modified because supervision is enabled!</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SupervisorOperationSetTimeout', `(RTS_HANDLE hOperation, RTS_SYSTIME stTimeoutUs)')

/**
 * <description>
 * Get operation specified by operationid and componentid.
 * </description>
 * <param name="ui32OperationID" type="IN">Unique operation ID</element>
 * <param name="cmpId" type="IN">ComponentID of the component which operation is supervised</element>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Operation was found</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NO_OBJECT">No operation found</errorcode> 
 * <result>Handle to operation for all other management functions or RTS_INVALID_HANDLE in case of an error</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `SupervisorOperationGet', `(RTS_UI32 ui32OperationID, RTS_UI32 cmpId, RTS_RESULT *pResult)')

#ifdef __cplusplus
}
#endif
