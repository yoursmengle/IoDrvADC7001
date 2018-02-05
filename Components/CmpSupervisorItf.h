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


	
	
#ifndef _CMPSUPERVISORITF_H_
#define _CMPSUPERVISORITF_H_

#include "CmpStd.h"

 

 




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
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

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

void CDECL CDECL_EXT supervisoroperationalive(supervisoroperationalive_struct *p);
typedef void (CDECL CDECL_EXT* PFSUPERVISOROPERATIONALIVE_IEC) (supervisoroperationalive_struct *p);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONALIVE_NOTIMPLEMENTED)
	#define USE_supervisoroperationalive
	#define EXT_supervisoroperationalive
	#define GET_supervisoroperationalive(fl)  ERR_NOTIMPLEMENTED
	#define CAL_supervisoroperationalive(p0) 
	#define CHK_supervisoroperationalive  FALSE
	#define EXP_supervisoroperationalive  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_supervisoroperationalive
	#define EXT_supervisoroperationalive
	#define GET_supervisoroperationalive(fl)  CAL_CMGETAPI( "supervisoroperationalive" ) 
	#define CAL_supervisoroperationalive  supervisoroperationalive
	#define CHK_supervisoroperationalive  TRUE
	#define EXP_supervisoroperationalive  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationalive", (RTS_UINTPTR)supervisoroperationalive, 1, 0x33C47EE3, 0x03050C00) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_supervisoroperationalive
	#define EXT_supervisoroperationalive
	#define GET_supervisoroperationalive(fl)  CAL_CMGETAPI( "supervisoroperationalive" ) 
	#define CAL_supervisoroperationalive  supervisoroperationalive
	#define CHK_supervisoroperationalive  TRUE
	#define EXP_supervisoroperationalive  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationalive", (RTS_UINTPTR)supervisoroperationalive, 1, 0x33C47EE3, 0x03050C00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorsupervisoroperationalive
	#define EXT_CmpSupervisorsupervisoroperationalive
	#define GET_CmpSupervisorsupervisoroperationalive  ERR_OK
	#define CAL_CmpSupervisorsupervisoroperationalive  supervisoroperationalive
	#define CHK_CmpSupervisorsupervisoroperationalive  TRUE
	#define EXP_CmpSupervisorsupervisoroperationalive  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationalive", (RTS_UINTPTR)supervisoroperationalive, 1, 0x33C47EE3, 0x03050C00) 
#elif defined(CPLUSPLUS)
	#define USE_supervisoroperationalive
	#define EXT_supervisoroperationalive
	#define GET_supervisoroperationalive(fl)  CAL_CMGETAPI( "supervisoroperationalive" ) 
	#define CAL_supervisoroperationalive  supervisoroperationalive
	#define CHK_supervisoroperationalive  TRUE
	#define EXP_supervisoroperationalive  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationalive", (RTS_UINTPTR)supervisoroperationalive, 1, 0x33C47EE3, 0x03050C00) 
#else /* DYNAMIC_LINK */
	#define USE_supervisoroperationalive  PFSUPERVISOROPERATIONALIVE_IEC pfsupervisoroperationalive;
	#define EXT_supervisoroperationalive  extern PFSUPERVISOROPERATIONALIVE_IEC pfsupervisoroperationalive;
	#define GET_supervisoroperationalive(fl)  s_pfCMGetAPI2( "supervisoroperationalive", (RTS_VOID_FCTPTR *)&pfsupervisoroperationalive, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x33C47EE3, 0x03050C00)
	#define CAL_supervisoroperationalive  pfsupervisoroperationalive
	#define CHK_supervisoroperationalive  (pfsupervisoroperationalive != NULL)
	#define EXP_supervisoroperationalive   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationalive", (RTS_UINTPTR)supervisoroperationalive, 1, 0x33C47EE3, 0x03050C00) 
#endif


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

void CDECL CDECL_EXT supervisoroperationdead(supervisoroperationdead_struct *p);
typedef void (CDECL CDECL_EXT* PFSUPERVISOROPERATIONDEAD_IEC) (supervisoroperationdead_struct *p);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONDEAD_NOTIMPLEMENTED)
	#define USE_supervisoroperationdead
	#define EXT_supervisoroperationdead
	#define GET_supervisoroperationdead(fl)  ERR_NOTIMPLEMENTED
	#define CAL_supervisoroperationdead(p0) 
	#define CHK_supervisoroperationdead  FALSE
	#define EXP_supervisoroperationdead  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_supervisoroperationdead
	#define EXT_supervisoroperationdead
	#define GET_supervisoroperationdead(fl)  CAL_CMGETAPI( "supervisoroperationdead" ) 
	#define CAL_supervisoroperationdead  supervisoroperationdead
	#define CHK_supervisoroperationdead  TRUE
	#define EXP_supervisoroperationdead  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationdead", (RTS_UINTPTR)supervisoroperationdead, 1, 0x709DF6D1, 0x03050C00) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_supervisoroperationdead
	#define EXT_supervisoroperationdead
	#define GET_supervisoroperationdead(fl)  CAL_CMGETAPI( "supervisoroperationdead" ) 
	#define CAL_supervisoroperationdead  supervisoroperationdead
	#define CHK_supervisoroperationdead  TRUE
	#define EXP_supervisoroperationdead  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationdead", (RTS_UINTPTR)supervisoroperationdead, 1, 0x709DF6D1, 0x03050C00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorsupervisoroperationdead
	#define EXT_CmpSupervisorsupervisoroperationdead
	#define GET_CmpSupervisorsupervisoroperationdead  ERR_OK
	#define CAL_CmpSupervisorsupervisoroperationdead  supervisoroperationdead
	#define CHK_CmpSupervisorsupervisoroperationdead  TRUE
	#define EXP_CmpSupervisorsupervisoroperationdead  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationdead", (RTS_UINTPTR)supervisoroperationdead, 1, 0x709DF6D1, 0x03050C00) 
#elif defined(CPLUSPLUS)
	#define USE_supervisoroperationdead
	#define EXT_supervisoroperationdead
	#define GET_supervisoroperationdead(fl)  CAL_CMGETAPI( "supervisoroperationdead" ) 
	#define CAL_supervisoroperationdead  supervisoroperationdead
	#define CHK_supervisoroperationdead  TRUE
	#define EXP_supervisoroperationdead  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationdead", (RTS_UINTPTR)supervisoroperationdead, 1, 0x709DF6D1, 0x03050C00) 
#else /* DYNAMIC_LINK */
	#define USE_supervisoroperationdead  PFSUPERVISOROPERATIONDEAD_IEC pfsupervisoroperationdead;
	#define EXT_supervisoroperationdead  extern PFSUPERVISOROPERATIONDEAD_IEC pfsupervisoroperationdead;
	#define GET_supervisoroperationdead(fl)  s_pfCMGetAPI2( "supervisoroperationdead", (RTS_VOID_FCTPTR *)&pfsupervisoroperationdead, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x709DF6D1, 0x03050C00)
	#define CAL_supervisoroperationdead  pfsupervisoroperationdead
	#define CHK_supervisoroperationdead  (pfsupervisoroperationdead != NULL)
	#define EXP_supervisoroperationdead   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationdead", (RTS_UINTPTR)supervisoroperationdead, 1, 0x709DF6D1, 0x03050C00) 
#endif


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

void CDECL CDECL_EXT supervisoroperationdisable(supervisoroperationdisable_struct *p);
typedef void (CDECL CDECL_EXT* PFSUPERVISOROPERATIONDISABLE_IEC) (supervisoroperationdisable_struct *p);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONDISABLE_NOTIMPLEMENTED)
	#define USE_supervisoroperationdisable
	#define EXT_supervisoroperationdisable
	#define GET_supervisoroperationdisable(fl)  ERR_NOTIMPLEMENTED
	#define CAL_supervisoroperationdisable(p0) 
	#define CHK_supervisoroperationdisable  FALSE
	#define EXP_supervisoroperationdisable  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_supervisoroperationdisable
	#define EXT_supervisoroperationdisable
	#define GET_supervisoroperationdisable(fl)  CAL_CMGETAPI( "supervisoroperationdisable" ) 
	#define CAL_supervisoroperationdisable  supervisoroperationdisable
	#define CHK_supervisoroperationdisable  TRUE
	#define EXP_supervisoroperationdisable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationdisable", (RTS_UINTPTR)supervisoroperationdisable, 1, 0xD5C85590, 0x03050C00) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_supervisoroperationdisable
	#define EXT_supervisoroperationdisable
	#define GET_supervisoroperationdisable(fl)  CAL_CMGETAPI( "supervisoroperationdisable" ) 
	#define CAL_supervisoroperationdisable  supervisoroperationdisable
	#define CHK_supervisoroperationdisable  TRUE
	#define EXP_supervisoroperationdisable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationdisable", (RTS_UINTPTR)supervisoroperationdisable, 1, 0xD5C85590, 0x03050C00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorsupervisoroperationdisable
	#define EXT_CmpSupervisorsupervisoroperationdisable
	#define GET_CmpSupervisorsupervisoroperationdisable  ERR_OK
	#define CAL_CmpSupervisorsupervisoroperationdisable  supervisoroperationdisable
	#define CHK_CmpSupervisorsupervisoroperationdisable  TRUE
	#define EXP_CmpSupervisorsupervisoroperationdisable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationdisable", (RTS_UINTPTR)supervisoroperationdisable, 1, 0xD5C85590, 0x03050C00) 
#elif defined(CPLUSPLUS)
	#define USE_supervisoroperationdisable
	#define EXT_supervisoroperationdisable
	#define GET_supervisoroperationdisable(fl)  CAL_CMGETAPI( "supervisoroperationdisable" ) 
	#define CAL_supervisoroperationdisable  supervisoroperationdisable
	#define CHK_supervisoroperationdisable  TRUE
	#define EXP_supervisoroperationdisable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationdisable", (RTS_UINTPTR)supervisoroperationdisable, 1, 0xD5C85590, 0x03050C00) 
#else /* DYNAMIC_LINK */
	#define USE_supervisoroperationdisable  PFSUPERVISOROPERATIONDISABLE_IEC pfsupervisoroperationdisable;
	#define EXT_supervisoroperationdisable  extern PFSUPERVISOROPERATIONDISABLE_IEC pfsupervisoroperationdisable;
	#define GET_supervisoroperationdisable(fl)  s_pfCMGetAPI2( "supervisoroperationdisable", (RTS_VOID_FCTPTR *)&pfsupervisoroperationdisable, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xD5C85590, 0x03050C00)
	#define CAL_supervisoroperationdisable  pfsupervisoroperationdisable
	#define CHK_supervisoroperationdisable  (pfsupervisoroperationdisable != NULL)
	#define EXP_supervisoroperationdisable   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationdisable", (RTS_UINTPTR)supervisoroperationdisable, 1, 0xD5C85590, 0x03050C00) 
#endif


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

void CDECL CDECL_EXT supervisoroperationenable(supervisoroperationenable_struct *p);
typedef void (CDECL CDECL_EXT* PFSUPERVISOROPERATIONENABLE_IEC) (supervisoroperationenable_struct *p);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONENABLE_NOTIMPLEMENTED)
	#define USE_supervisoroperationenable
	#define EXT_supervisoroperationenable
	#define GET_supervisoroperationenable(fl)  ERR_NOTIMPLEMENTED
	#define CAL_supervisoroperationenable(p0) 
	#define CHK_supervisoroperationenable  FALSE
	#define EXP_supervisoroperationenable  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_supervisoroperationenable
	#define EXT_supervisoroperationenable
	#define GET_supervisoroperationenable(fl)  CAL_CMGETAPI( "supervisoroperationenable" ) 
	#define CAL_supervisoroperationenable  supervisoroperationenable
	#define CHK_supervisoroperationenable  TRUE
	#define EXP_supervisoroperationenable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationenable", (RTS_UINTPTR)supervisoroperationenable, 1, 0x8FCDAEB8, 0x03050C00) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_supervisoroperationenable
	#define EXT_supervisoroperationenable
	#define GET_supervisoroperationenable(fl)  CAL_CMGETAPI( "supervisoroperationenable" ) 
	#define CAL_supervisoroperationenable  supervisoroperationenable
	#define CHK_supervisoroperationenable  TRUE
	#define EXP_supervisoroperationenable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationenable", (RTS_UINTPTR)supervisoroperationenable, 1, 0x8FCDAEB8, 0x03050C00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorsupervisoroperationenable
	#define EXT_CmpSupervisorsupervisoroperationenable
	#define GET_CmpSupervisorsupervisoroperationenable  ERR_OK
	#define CAL_CmpSupervisorsupervisoroperationenable  supervisoroperationenable
	#define CHK_CmpSupervisorsupervisoroperationenable  TRUE
	#define EXP_CmpSupervisorsupervisoroperationenable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationenable", (RTS_UINTPTR)supervisoroperationenable, 1, 0x8FCDAEB8, 0x03050C00) 
#elif defined(CPLUSPLUS)
	#define USE_supervisoroperationenable
	#define EXT_supervisoroperationenable
	#define GET_supervisoroperationenable(fl)  CAL_CMGETAPI( "supervisoroperationenable" ) 
	#define CAL_supervisoroperationenable  supervisoroperationenable
	#define CHK_supervisoroperationenable  TRUE
	#define EXP_supervisoroperationenable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationenable", (RTS_UINTPTR)supervisoroperationenable, 1, 0x8FCDAEB8, 0x03050C00) 
#else /* DYNAMIC_LINK */
	#define USE_supervisoroperationenable  PFSUPERVISOROPERATIONENABLE_IEC pfsupervisoroperationenable;
	#define EXT_supervisoroperationenable  extern PFSUPERVISOROPERATIONENABLE_IEC pfsupervisoroperationenable;
	#define GET_supervisoroperationenable(fl)  s_pfCMGetAPI2( "supervisoroperationenable", (RTS_VOID_FCTPTR *)&pfsupervisoroperationenable, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x8FCDAEB8, 0x03050C00)
	#define CAL_supervisoroperationenable  pfsupervisoroperationenable
	#define CHK_supervisoroperationenable  (pfsupervisoroperationenable != NULL)
	#define EXP_supervisoroperationenable   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationenable", (RTS_UINTPTR)supervisoroperationenable, 1, 0x8FCDAEB8, 0x03050C00) 
#endif


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

void CDECL CDECL_EXT supervisoroperationgetentry(supervisoroperationgetentry_struct *p);
typedef void (CDECL CDECL_EXT* PFSUPERVISOROPERATIONGETENTRY_IEC) (supervisoroperationgetentry_struct *p);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONGETENTRY_NOTIMPLEMENTED)
	#define USE_supervisoroperationgetentry
	#define EXT_supervisoroperationgetentry
	#define GET_supervisoroperationgetentry(fl)  ERR_NOTIMPLEMENTED
	#define CAL_supervisoroperationgetentry(p0) 
	#define CHK_supervisoroperationgetentry  FALSE
	#define EXP_supervisoroperationgetentry  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_supervisoroperationgetentry
	#define EXT_supervisoroperationgetentry
	#define GET_supervisoroperationgetentry(fl)  CAL_CMGETAPI( "supervisoroperationgetentry" ) 
	#define CAL_supervisoroperationgetentry  supervisoroperationgetentry
	#define CHK_supervisoroperationgetentry  TRUE
	#define EXP_supervisoroperationgetentry  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetentry", (RTS_UINTPTR)supervisoroperationgetentry, 1, 0, 0x03050C00) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_supervisoroperationgetentry
	#define EXT_supervisoroperationgetentry
	#define GET_supervisoroperationgetentry(fl)  CAL_CMGETAPI( "supervisoroperationgetentry" ) 
	#define CAL_supervisoroperationgetentry  supervisoroperationgetentry
	#define CHK_supervisoroperationgetentry  TRUE
	#define EXP_supervisoroperationgetentry  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetentry", (RTS_UINTPTR)supervisoroperationgetentry, 1, 0, 0x03050C00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorsupervisoroperationgetentry
	#define EXT_CmpSupervisorsupervisoroperationgetentry
	#define GET_CmpSupervisorsupervisoroperationgetentry  ERR_OK
	#define CAL_CmpSupervisorsupervisoroperationgetentry  supervisoroperationgetentry
	#define CHK_CmpSupervisorsupervisoroperationgetentry  TRUE
	#define EXP_CmpSupervisorsupervisoroperationgetentry  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetentry", (RTS_UINTPTR)supervisoroperationgetentry, 1, 0, 0x03050C00) 
#elif defined(CPLUSPLUS)
	#define USE_supervisoroperationgetentry
	#define EXT_supervisoroperationgetentry
	#define GET_supervisoroperationgetentry(fl)  CAL_CMGETAPI( "supervisoroperationgetentry" ) 
	#define CAL_supervisoroperationgetentry  supervisoroperationgetentry
	#define CHK_supervisoroperationgetentry  TRUE
	#define EXP_supervisoroperationgetentry  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetentry", (RTS_UINTPTR)supervisoroperationgetentry, 1, 0, 0x03050C00) 
#else /* DYNAMIC_LINK */
	#define USE_supervisoroperationgetentry  PFSUPERVISOROPERATIONGETENTRY_IEC pfsupervisoroperationgetentry;
	#define EXT_supervisoroperationgetentry  extern PFSUPERVISOROPERATIONGETENTRY_IEC pfsupervisoroperationgetentry;
	#define GET_supervisoroperationgetentry(fl)  s_pfCMGetAPI2( "supervisoroperationgetentry", (RTS_VOID_FCTPTR *)&pfsupervisoroperationgetentry, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0x03050C00)
	#define CAL_supervisoroperationgetentry  pfsupervisoroperationgetentry
	#define CHK_supervisoroperationgetentry  (pfsupervisoroperationgetentry != NULL)
	#define EXP_supervisoroperationgetentry   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetentry", (RTS_UINTPTR)supervisoroperationgetentry, 1, 0, 0x03050C00) 
#endif


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

void CDECL CDECL_EXT supervisoroperationgetfirst(supervisoroperationgetfirst_struct *p);
typedef void (CDECL CDECL_EXT* PFSUPERVISOROPERATIONGETFIRST_IEC) (supervisoroperationgetfirst_struct *p);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONGETFIRST_NOTIMPLEMENTED)
	#define USE_supervisoroperationgetfirst
	#define EXT_supervisoroperationgetfirst
	#define GET_supervisoroperationgetfirst(fl)  ERR_NOTIMPLEMENTED
	#define CAL_supervisoroperationgetfirst(p0) 
	#define CHK_supervisoroperationgetfirst  FALSE
	#define EXP_supervisoroperationgetfirst  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_supervisoroperationgetfirst
	#define EXT_supervisoroperationgetfirst
	#define GET_supervisoroperationgetfirst(fl)  CAL_CMGETAPI( "supervisoroperationgetfirst" ) 
	#define CAL_supervisoroperationgetfirst  supervisoroperationgetfirst
	#define CHK_supervisoroperationgetfirst  TRUE
	#define EXP_supervisoroperationgetfirst  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetfirst", (RTS_UINTPTR)supervisoroperationgetfirst, 1, 0x33144D0D, 0x03050C00) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_supervisoroperationgetfirst
	#define EXT_supervisoroperationgetfirst
	#define GET_supervisoroperationgetfirst(fl)  CAL_CMGETAPI( "supervisoroperationgetfirst" ) 
	#define CAL_supervisoroperationgetfirst  supervisoroperationgetfirst
	#define CHK_supervisoroperationgetfirst  TRUE
	#define EXP_supervisoroperationgetfirst  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetfirst", (RTS_UINTPTR)supervisoroperationgetfirst, 1, 0x33144D0D, 0x03050C00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorsupervisoroperationgetfirst
	#define EXT_CmpSupervisorsupervisoroperationgetfirst
	#define GET_CmpSupervisorsupervisoroperationgetfirst  ERR_OK
	#define CAL_CmpSupervisorsupervisoroperationgetfirst  supervisoroperationgetfirst
	#define CHK_CmpSupervisorsupervisoroperationgetfirst  TRUE
	#define EXP_CmpSupervisorsupervisoroperationgetfirst  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetfirst", (RTS_UINTPTR)supervisoroperationgetfirst, 1, 0x33144D0D, 0x03050C00) 
#elif defined(CPLUSPLUS)
	#define USE_supervisoroperationgetfirst
	#define EXT_supervisoroperationgetfirst
	#define GET_supervisoroperationgetfirst(fl)  CAL_CMGETAPI( "supervisoroperationgetfirst" ) 
	#define CAL_supervisoroperationgetfirst  supervisoroperationgetfirst
	#define CHK_supervisoroperationgetfirst  TRUE
	#define EXP_supervisoroperationgetfirst  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetfirst", (RTS_UINTPTR)supervisoroperationgetfirst, 1, 0x33144D0D, 0x03050C00) 
#else /* DYNAMIC_LINK */
	#define USE_supervisoroperationgetfirst  PFSUPERVISOROPERATIONGETFIRST_IEC pfsupervisoroperationgetfirst;
	#define EXT_supervisoroperationgetfirst  extern PFSUPERVISOROPERATIONGETFIRST_IEC pfsupervisoroperationgetfirst;
	#define GET_supervisoroperationgetfirst(fl)  s_pfCMGetAPI2( "supervisoroperationgetfirst", (RTS_VOID_FCTPTR *)&pfsupervisoroperationgetfirst, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x33144D0D, 0x03050C00)
	#define CAL_supervisoroperationgetfirst  pfsupervisoroperationgetfirst
	#define CHK_supervisoroperationgetfirst  (pfsupervisoroperationgetfirst != NULL)
	#define EXP_supervisoroperationgetfirst   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetfirst", (RTS_UINTPTR)supervisoroperationgetfirst, 1, 0x33144D0D, 0x03050C00) 
#endif


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

void CDECL CDECL_EXT supervisoroperationgetnext(supervisoroperationgetnext_struct *p);
typedef void (CDECL CDECL_EXT* PFSUPERVISOROPERATIONGETNEXT_IEC) (supervisoroperationgetnext_struct *p);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONGETNEXT_NOTIMPLEMENTED)
	#define USE_supervisoroperationgetnext
	#define EXT_supervisoroperationgetnext
	#define GET_supervisoroperationgetnext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_supervisoroperationgetnext(p0) 
	#define CHK_supervisoroperationgetnext  FALSE
	#define EXP_supervisoroperationgetnext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_supervisoroperationgetnext
	#define EXT_supervisoroperationgetnext
	#define GET_supervisoroperationgetnext(fl)  CAL_CMGETAPI( "supervisoroperationgetnext" ) 
	#define CAL_supervisoroperationgetnext  supervisoroperationgetnext
	#define CHK_supervisoroperationgetnext  TRUE
	#define EXP_supervisoroperationgetnext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetnext", (RTS_UINTPTR)supervisoroperationgetnext, 1, 0x45054F88, 0x03050C00) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_supervisoroperationgetnext
	#define EXT_supervisoroperationgetnext
	#define GET_supervisoroperationgetnext(fl)  CAL_CMGETAPI( "supervisoroperationgetnext" ) 
	#define CAL_supervisoroperationgetnext  supervisoroperationgetnext
	#define CHK_supervisoroperationgetnext  TRUE
	#define EXP_supervisoroperationgetnext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetnext", (RTS_UINTPTR)supervisoroperationgetnext, 1, 0x45054F88, 0x03050C00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorsupervisoroperationgetnext
	#define EXT_CmpSupervisorsupervisoroperationgetnext
	#define GET_CmpSupervisorsupervisoroperationgetnext  ERR_OK
	#define CAL_CmpSupervisorsupervisoroperationgetnext  supervisoroperationgetnext
	#define CHK_CmpSupervisorsupervisoroperationgetnext  TRUE
	#define EXP_CmpSupervisorsupervisoroperationgetnext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetnext", (RTS_UINTPTR)supervisoroperationgetnext, 1, 0x45054F88, 0x03050C00) 
#elif defined(CPLUSPLUS)
	#define USE_supervisoroperationgetnext
	#define EXT_supervisoroperationgetnext
	#define GET_supervisoroperationgetnext(fl)  CAL_CMGETAPI( "supervisoroperationgetnext" ) 
	#define CAL_supervisoroperationgetnext  supervisoroperationgetnext
	#define CHK_supervisoroperationgetnext  TRUE
	#define EXP_supervisoroperationgetnext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetnext", (RTS_UINTPTR)supervisoroperationgetnext, 1, 0x45054F88, 0x03050C00) 
#else /* DYNAMIC_LINK */
	#define USE_supervisoroperationgetnext  PFSUPERVISOROPERATIONGETNEXT_IEC pfsupervisoroperationgetnext;
	#define EXT_supervisoroperationgetnext  extern PFSUPERVISOROPERATIONGETNEXT_IEC pfsupervisoroperationgetnext;
	#define GET_supervisoroperationgetnext(fl)  s_pfCMGetAPI2( "supervisoroperationgetnext", (RTS_VOID_FCTPTR *)&pfsupervisoroperationgetnext, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x45054F88, 0x03050C00)
	#define CAL_supervisoroperationgetnext  pfsupervisoroperationgetnext
	#define CHK_supervisoroperationgetnext  (pfsupervisoroperationgetnext != NULL)
	#define EXP_supervisoroperationgetnext   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetnext", (RTS_UINTPTR)supervisoroperationgetnext, 1, 0x45054F88, 0x03050C00) 
#endif


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

void CDECL CDECL_EXT supervisoroperationgetstate(supervisoroperationgetstate_struct *p);
typedef void (CDECL CDECL_EXT* PFSUPERVISOROPERATIONGETSTATE_IEC) (supervisoroperationgetstate_struct *p);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONGETSTATE_NOTIMPLEMENTED)
	#define USE_supervisoroperationgetstate
	#define EXT_supervisoroperationgetstate
	#define GET_supervisoroperationgetstate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_supervisoroperationgetstate(p0) 
	#define CHK_supervisoroperationgetstate  FALSE
	#define EXP_supervisoroperationgetstate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_supervisoroperationgetstate
	#define EXT_supervisoroperationgetstate
	#define GET_supervisoroperationgetstate(fl)  CAL_CMGETAPI( "supervisoroperationgetstate" ) 
	#define CAL_supervisoroperationgetstate  supervisoroperationgetstate
	#define CHK_supervisoroperationgetstate  TRUE
	#define EXP_supervisoroperationgetstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetstate", (RTS_UINTPTR)supervisoroperationgetstate, 1, 0, 0x03050C00) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_supervisoroperationgetstate
	#define EXT_supervisoroperationgetstate
	#define GET_supervisoroperationgetstate(fl)  CAL_CMGETAPI( "supervisoroperationgetstate" ) 
	#define CAL_supervisoroperationgetstate  supervisoroperationgetstate
	#define CHK_supervisoroperationgetstate  TRUE
	#define EXP_supervisoroperationgetstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetstate", (RTS_UINTPTR)supervisoroperationgetstate, 1, 0, 0x03050C00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorsupervisoroperationgetstate
	#define EXT_CmpSupervisorsupervisoroperationgetstate
	#define GET_CmpSupervisorsupervisoroperationgetstate  ERR_OK
	#define CAL_CmpSupervisorsupervisoroperationgetstate  supervisoroperationgetstate
	#define CHK_CmpSupervisorsupervisoroperationgetstate  TRUE
	#define EXP_CmpSupervisorsupervisoroperationgetstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetstate", (RTS_UINTPTR)supervisoroperationgetstate, 1, 0, 0x03050C00) 
#elif defined(CPLUSPLUS)
	#define USE_supervisoroperationgetstate
	#define EXT_supervisoroperationgetstate
	#define GET_supervisoroperationgetstate(fl)  CAL_CMGETAPI( "supervisoroperationgetstate" ) 
	#define CAL_supervisoroperationgetstate  supervisoroperationgetstate
	#define CHK_supervisoroperationgetstate  TRUE
	#define EXP_supervisoroperationgetstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetstate", (RTS_UINTPTR)supervisoroperationgetstate, 1, 0, 0x03050C00) 
#else /* DYNAMIC_LINK */
	#define USE_supervisoroperationgetstate  PFSUPERVISOROPERATIONGETSTATE_IEC pfsupervisoroperationgetstate;
	#define EXT_supervisoroperationgetstate  extern PFSUPERVISOROPERATIONGETSTATE_IEC pfsupervisoroperationgetstate;
	#define GET_supervisoroperationgetstate(fl)  s_pfCMGetAPI2( "supervisoroperationgetstate", (RTS_VOID_FCTPTR *)&pfsupervisoroperationgetstate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0x03050C00)
	#define CAL_supervisoroperationgetstate  pfsupervisoroperationgetstate
	#define CHK_supervisoroperationgetstate  (pfsupervisoroperationgetstate != NULL)
	#define EXP_supervisoroperationgetstate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetstate", (RTS_UINTPTR)supervisoroperationgetstate, 1, 0, 0x03050C00) 
#endif


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

void CDECL CDECL_EXT supervisoroperationgetstate2(supervisoroperationgetstate2_struct *p);
typedef void (CDECL CDECL_EXT* PFSUPERVISOROPERATIONGETSTATE2_IEC) (supervisoroperationgetstate2_struct *p);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONGETSTATE2_NOTIMPLEMENTED)
	#define USE_supervisoroperationgetstate2
	#define EXT_supervisoroperationgetstate2
	#define GET_supervisoroperationgetstate2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_supervisoroperationgetstate2(p0) 
	#define CHK_supervisoroperationgetstate2  FALSE
	#define EXP_supervisoroperationgetstate2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_supervisoroperationgetstate2
	#define EXT_supervisoroperationgetstate2
	#define GET_supervisoroperationgetstate2(fl)  CAL_CMGETAPI( "supervisoroperationgetstate2" ) 
	#define CAL_supervisoroperationgetstate2  supervisoroperationgetstate2
	#define CHK_supervisoroperationgetstate2  TRUE
	#define EXP_supervisoroperationgetstate2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetstate2", (RTS_UINTPTR)supervisoroperationgetstate2, 1, 0x284A6A2A, 0x03050C00) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_supervisoroperationgetstate2
	#define EXT_supervisoroperationgetstate2
	#define GET_supervisoroperationgetstate2(fl)  CAL_CMGETAPI( "supervisoroperationgetstate2" ) 
	#define CAL_supervisoroperationgetstate2  supervisoroperationgetstate2
	#define CHK_supervisoroperationgetstate2  TRUE
	#define EXP_supervisoroperationgetstate2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetstate2", (RTS_UINTPTR)supervisoroperationgetstate2, 1, 0x284A6A2A, 0x03050C00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorsupervisoroperationgetstate2
	#define EXT_CmpSupervisorsupervisoroperationgetstate2
	#define GET_CmpSupervisorsupervisoroperationgetstate2  ERR_OK
	#define CAL_CmpSupervisorsupervisoroperationgetstate2  supervisoroperationgetstate2
	#define CHK_CmpSupervisorsupervisoroperationgetstate2  TRUE
	#define EXP_CmpSupervisorsupervisoroperationgetstate2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetstate2", (RTS_UINTPTR)supervisoroperationgetstate2, 1, 0x284A6A2A, 0x03050C00) 
#elif defined(CPLUSPLUS)
	#define USE_supervisoroperationgetstate2
	#define EXT_supervisoroperationgetstate2
	#define GET_supervisoroperationgetstate2(fl)  CAL_CMGETAPI( "supervisoroperationgetstate2" ) 
	#define CAL_supervisoroperationgetstate2  supervisoroperationgetstate2
	#define CHK_supervisoroperationgetstate2  TRUE
	#define EXP_supervisoroperationgetstate2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetstate2", (RTS_UINTPTR)supervisoroperationgetstate2, 1, 0x284A6A2A, 0x03050C00) 
#else /* DYNAMIC_LINK */
	#define USE_supervisoroperationgetstate2  PFSUPERVISOROPERATIONGETSTATE2_IEC pfsupervisoroperationgetstate2;
	#define EXT_supervisoroperationgetstate2  extern PFSUPERVISOROPERATIONGETSTATE2_IEC pfsupervisoroperationgetstate2;
	#define GET_supervisoroperationgetstate2(fl)  s_pfCMGetAPI2( "supervisoroperationgetstate2", (RTS_VOID_FCTPTR *)&pfsupervisoroperationgetstate2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x284A6A2A, 0x03050C00)
	#define CAL_supervisoroperationgetstate2  pfsupervisoroperationgetstate2
	#define CHK_supervisoroperationgetstate2  (pfsupervisoroperationgetstate2 != NULL)
	#define EXP_supervisoroperationgetstate2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationgetstate2", (RTS_UINTPTR)supervisoroperationgetstate2, 1, 0x284A6A2A, 0x03050C00) 
#endif


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

void CDECL CDECL_EXT supervisoroperationregister(supervisoroperationregister_struct *p);
typedef void (CDECL CDECL_EXT* PFSUPERVISOROPERATIONREGISTER_IEC) (supervisoroperationregister_struct *p);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONREGISTER_NOTIMPLEMENTED)
	#define USE_supervisoroperationregister
	#define EXT_supervisoroperationregister
	#define GET_supervisoroperationregister(fl)  ERR_NOTIMPLEMENTED
	#define CAL_supervisoroperationregister(p0) 
	#define CHK_supervisoroperationregister  FALSE
	#define EXP_supervisoroperationregister  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_supervisoroperationregister
	#define EXT_supervisoroperationregister
	#define GET_supervisoroperationregister(fl)  CAL_CMGETAPI( "supervisoroperationregister" ) 
	#define CAL_supervisoroperationregister  supervisoroperationregister
	#define CHK_supervisoroperationregister  TRUE
	#define EXP_supervisoroperationregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationregister", (RTS_UINTPTR)supervisoroperationregister, 1, 0x6D8179C0, 0x03050C00) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_supervisoroperationregister
	#define EXT_supervisoroperationregister
	#define GET_supervisoroperationregister(fl)  CAL_CMGETAPI( "supervisoroperationregister" ) 
	#define CAL_supervisoroperationregister  supervisoroperationregister
	#define CHK_supervisoroperationregister  TRUE
	#define EXP_supervisoroperationregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationregister", (RTS_UINTPTR)supervisoroperationregister, 1, 0x6D8179C0, 0x03050C00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorsupervisoroperationregister
	#define EXT_CmpSupervisorsupervisoroperationregister
	#define GET_CmpSupervisorsupervisoroperationregister  ERR_OK
	#define CAL_CmpSupervisorsupervisoroperationregister  supervisoroperationregister
	#define CHK_CmpSupervisorsupervisoroperationregister  TRUE
	#define EXP_CmpSupervisorsupervisoroperationregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationregister", (RTS_UINTPTR)supervisoroperationregister, 1, 0x6D8179C0, 0x03050C00) 
#elif defined(CPLUSPLUS)
	#define USE_supervisoroperationregister
	#define EXT_supervisoroperationregister
	#define GET_supervisoroperationregister(fl)  CAL_CMGETAPI( "supervisoroperationregister" ) 
	#define CAL_supervisoroperationregister  supervisoroperationregister
	#define CHK_supervisoroperationregister  TRUE
	#define EXP_supervisoroperationregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationregister", (RTS_UINTPTR)supervisoroperationregister, 1, 0x6D8179C0, 0x03050C00) 
#else /* DYNAMIC_LINK */
	#define USE_supervisoroperationregister  PFSUPERVISOROPERATIONREGISTER_IEC pfsupervisoroperationregister;
	#define EXT_supervisoroperationregister  extern PFSUPERVISOROPERATIONREGISTER_IEC pfsupervisoroperationregister;
	#define GET_supervisoroperationregister(fl)  s_pfCMGetAPI2( "supervisoroperationregister", (RTS_VOID_FCTPTR *)&pfsupervisoroperationregister, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x6D8179C0, 0x03050C00)
	#define CAL_supervisoroperationregister  pfsupervisoroperationregister
	#define CHK_supervisoroperationregister  (pfsupervisoroperationregister != NULL)
	#define EXP_supervisoroperationregister   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationregister", (RTS_UINTPTR)supervisoroperationregister, 1, 0x6D8179C0, 0x03050C00) 
#endif


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

void CDECL CDECL_EXT supervisoroperationsettimeout(supervisoroperationsettimeout_struct *p);
typedef void (CDECL CDECL_EXT* PFSUPERVISOROPERATIONSETTIMEOUT_IEC) (supervisoroperationsettimeout_struct *p);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONSETTIMEOUT_NOTIMPLEMENTED)
	#define USE_supervisoroperationsettimeout
	#define EXT_supervisoroperationsettimeout
	#define GET_supervisoroperationsettimeout(fl)  ERR_NOTIMPLEMENTED
	#define CAL_supervisoroperationsettimeout(p0) 
	#define CHK_supervisoroperationsettimeout  FALSE
	#define EXP_supervisoroperationsettimeout  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_supervisoroperationsettimeout
	#define EXT_supervisoroperationsettimeout
	#define GET_supervisoroperationsettimeout(fl)  CAL_CMGETAPI( "supervisoroperationsettimeout" ) 
	#define CAL_supervisoroperationsettimeout  supervisoroperationsettimeout
	#define CHK_supervisoroperationsettimeout  TRUE
	#define EXP_supervisoroperationsettimeout  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationsettimeout", (RTS_UINTPTR)supervisoroperationsettimeout, 1, 0xDB1591C0, 0x03050C00) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_supervisoroperationsettimeout
	#define EXT_supervisoroperationsettimeout
	#define GET_supervisoroperationsettimeout(fl)  CAL_CMGETAPI( "supervisoroperationsettimeout" ) 
	#define CAL_supervisoroperationsettimeout  supervisoroperationsettimeout
	#define CHK_supervisoroperationsettimeout  TRUE
	#define EXP_supervisoroperationsettimeout  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationsettimeout", (RTS_UINTPTR)supervisoroperationsettimeout, 1, 0xDB1591C0, 0x03050C00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorsupervisoroperationsettimeout
	#define EXT_CmpSupervisorsupervisoroperationsettimeout
	#define GET_CmpSupervisorsupervisoroperationsettimeout  ERR_OK
	#define CAL_CmpSupervisorsupervisoroperationsettimeout  supervisoroperationsettimeout
	#define CHK_CmpSupervisorsupervisoroperationsettimeout  TRUE
	#define EXP_CmpSupervisorsupervisoroperationsettimeout  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationsettimeout", (RTS_UINTPTR)supervisoroperationsettimeout, 1, 0xDB1591C0, 0x03050C00) 
#elif defined(CPLUSPLUS)
	#define USE_supervisoroperationsettimeout
	#define EXT_supervisoroperationsettimeout
	#define GET_supervisoroperationsettimeout(fl)  CAL_CMGETAPI( "supervisoroperationsettimeout" ) 
	#define CAL_supervisoroperationsettimeout  supervisoroperationsettimeout
	#define CHK_supervisoroperationsettimeout  TRUE
	#define EXP_supervisoroperationsettimeout  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationsettimeout", (RTS_UINTPTR)supervisoroperationsettimeout, 1, 0xDB1591C0, 0x03050C00) 
#else /* DYNAMIC_LINK */
	#define USE_supervisoroperationsettimeout  PFSUPERVISOROPERATIONSETTIMEOUT_IEC pfsupervisoroperationsettimeout;
	#define EXT_supervisoroperationsettimeout  extern PFSUPERVISOROPERATIONSETTIMEOUT_IEC pfsupervisoroperationsettimeout;
	#define GET_supervisoroperationsettimeout(fl)  s_pfCMGetAPI2( "supervisoroperationsettimeout", (RTS_VOID_FCTPTR *)&pfsupervisoroperationsettimeout, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xDB1591C0, 0x03050C00)
	#define CAL_supervisoroperationsettimeout  pfsupervisoroperationsettimeout
	#define CHK_supervisoroperationsettimeout  (pfsupervisoroperationsettimeout != NULL)
	#define EXP_supervisoroperationsettimeout   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationsettimeout", (RTS_UINTPTR)supervisoroperationsettimeout, 1, 0xDB1591C0, 0x03050C00) 
#endif


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

void CDECL CDECL_EXT supervisoroperationunregister(supervisoroperationunregister_struct *p);
typedef void (CDECL CDECL_EXT* PFSUPERVISOROPERATIONUNREGISTER_IEC) (supervisoroperationunregister_struct *p);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONUNREGISTER_NOTIMPLEMENTED)
	#define USE_supervisoroperationunregister
	#define EXT_supervisoroperationunregister
	#define GET_supervisoroperationunregister(fl)  ERR_NOTIMPLEMENTED
	#define CAL_supervisoroperationunregister(p0) 
	#define CHK_supervisoroperationunregister  FALSE
	#define EXP_supervisoroperationunregister  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_supervisoroperationunregister
	#define EXT_supervisoroperationunregister
	#define GET_supervisoroperationunregister(fl)  CAL_CMGETAPI( "supervisoroperationunregister" ) 
	#define CAL_supervisoroperationunregister  supervisoroperationunregister
	#define CHK_supervisoroperationunregister  TRUE
	#define EXP_supervisoroperationunregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationunregister", (RTS_UINTPTR)supervisoroperationunregister, 1, 0xF19896D6, 0x03050C00) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_supervisoroperationunregister
	#define EXT_supervisoroperationunregister
	#define GET_supervisoroperationunregister(fl)  CAL_CMGETAPI( "supervisoroperationunregister" ) 
	#define CAL_supervisoroperationunregister  supervisoroperationunregister
	#define CHK_supervisoroperationunregister  TRUE
	#define EXP_supervisoroperationunregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationunregister", (RTS_UINTPTR)supervisoroperationunregister, 1, 0xF19896D6, 0x03050C00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorsupervisoroperationunregister
	#define EXT_CmpSupervisorsupervisoroperationunregister
	#define GET_CmpSupervisorsupervisoroperationunregister  ERR_OK
	#define CAL_CmpSupervisorsupervisoroperationunregister  supervisoroperationunregister
	#define CHK_CmpSupervisorsupervisoroperationunregister  TRUE
	#define EXP_CmpSupervisorsupervisoroperationunregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationunregister", (RTS_UINTPTR)supervisoroperationunregister, 1, 0xF19896D6, 0x03050C00) 
#elif defined(CPLUSPLUS)
	#define USE_supervisoroperationunregister
	#define EXT_supervisoroperationunregister
	#define GET_supervisoroperationunregister(fl)  CAL_CMGETAPI( "supervisoroperationunregister" ) 
	#define CAL_supervisoroperationunregister  supervisoroperationunregister
	#define CHK_supervisoroperationunregister  TRUE
	#define EXP_supervisoroperationunregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationunregister", (RTS_UINTPTR)supervisoroperationunregister, 1, 0xF19896D6, 0x03050C00) 
#else /* DYNAMIC_LINK */
	#define USE_supervisoroperationunregister  PFSUPERVISOROPERATIONUNREGISTER_IEC pfsupervisoroperationunregister;
	#define EXT_supervisoroperationunregister  extern PFSUPERVISOROPERATIONUNREGISTER_IEC pfsupervisoroperationunregister;
	#define GET_supervisoroperationunregister(fl)  s_pfCMGetAPI2( "supervisoroperationunregister", (RTS_VOID_FCTPTR *)&pfsupervisoroperationunregister, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xF19896D6, 0x03050C00)
	#define CAL_supervisoroperationunregister  pfsupervisoroperationunregister
	#define CHK_supervisoroperationunregister  (pfsupervisoroperationunregister != NULL)
	#define EXP_supervisoroperationunregister   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"supervisoroperationunregister", (RTS_UINTPTR)supervisoroperationunregister, 1, 0xF19896D6, 0x03050C00) 
#endif


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
RTS_HANDLE CDECL SupervisorOperationRegister(RTS_UI32 ui32OperationID, CMPID cmpId, char *pszOperationDescription, RTS_SYSTIME stTimeoutUs, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSUPERVISOROPERATIONREGISTER) (RTS_UI32 ui32OperationID, CMPID cmpId, char *pszOperationDescription, RTS_SYSTIME stTimeoutUs, RTS_RESULT *pResult);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONREGISTER_NOTIMPLEMENTED)
	#define USE_SupervisorOperationRegister
	#define EXT_SupervisorOperationRegister
	#define GET_SupervisorOperationRegister(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SupervisorOperationRegister(p0,p1,p2,p3,p4)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SupervisorOperationRegister  FALSE
	#define EXP_SupervisorOperationRegister  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SupervisorOperationRegister
	#define EXT_SupervisorOperationRegister
	#define GET_SupervisorOperationRegister(fl)  CAL_CMGETAPI( "SupervisorOperationRegister" ) 
	#define CAL_SupervisorOperationRegister  SupervisorOperationRegister
	#define CHK_SupervisorOperationRegister  TRUE
	#define EXP_SupervisorOperationRegister  CAL_CMEXPAPI( "SupervisorOperationRegister" ) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_SupervisorOperationRegister
	#define EXT_SupervisorOperationRegister
	#define GET_SupervisorOperationRegister(fl)  CAL_CMGETAPI( "SupervisorOperationRegister" ) 
	#define CAL_SupervisorOperationRegister  SupervisorOperationRegister
	#define CHK_SupervisorOperationRegister  TRUE
	#define EXP_SupervisorOperationRegister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationRegister", (RTS_UINTPTR)SupervisorOperationRegister, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorSupervisorOperationRegister
	#define EXT_CmpSupervisorSupervisorOperationRegister
	#define GET_CmpSupervisorSupervisorOperationRegister  ERR_OK
	#define CAL_CmpSupervisorSupervisorOperationRegister pICmpSupervisor->ISupervisorOperationRegister
	#define CHK_CmpSupervisorSupervisorOperationRegister (pICmpSupervisor != NULL)
	#define EXP_CmpSupervisorSupervisorOperationRegister  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SupervisorOperationRegister
	#define EXT_SupervisorOperationRegister
	#define GET_SupervisorOperationRegister(fl)  CAL_CMGETAPI( "SupervisorOperationRegister" ) 
	#define CAL_SupervisorOperationRegister pICmpSupervisor->ISupervisorOperationRegister
	#define CHK_SupervisorOperationRegister (pICmpSupervisor != NULL)
	#define EXP_SupervisorOperationRegister  CAL_CMEXPAPI( "SupervisorOperationRegister" ) 
#else /* DYNAMIC_LINK */
	#define USE_SupervisorOperationRegister  PFSUPERVISOROPERATIONREGISTER pfSupervisorOperationRegister;
	#define EXT_SupervisorOperationRegister  extern PFSUPERVISOROPERATIONREGISTER pfSupervisorOperationRegister;
	#define GET_SupervisorOperationRegister(fl)  s_pfCMGetAPI2( "SupervisorOperationRegister", (RTS_VOID_FCTPTR *)&pfSupervisorOperationRegister, (fl), 0, 0)
	#define CAL_SupervisorOperationRegister  pfSupervisorOperationRegister
	#define CHK_SupervisorOperationRegister  (pfSupervisorOperationRegister != NULL)
	#define EXP_SupervisorOperationRegister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationRegister", (RTS_UINTPTR)SupervisorOperationRegister, 0, 0) 
#endif




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
RTS_RESULT CDECL SupervisorOperationUnregister(RTS_HANDLE hOperation);
typedef RTS_RESULT (CDECL * PFSUPERVISOROPERATIONUNREGISTER) (RTS_HANDLE hOperation);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONUNREGISTER_NOTIMPLEMENTED)
	#define USE_SupervisorOperationUnregister
	#define EXT_SupervisorOperationUnregister
	#define GET_SupervisorOperationUnregister(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SupervisorOperationUnregister(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SupervisorOperationUnregister  FALSE
	#define EXP_SupervisorOperationUnregister  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SupervisorOperationUnregister
	#define EXT_SupervisorOperationUnregister
	#define GET_SupervisorOperationUnregister(fl)  CAL_CMGETAPI( "SupervisorOperationUnregister" ) 
	#define CAL_SupervisorOperationUnregister  SupervisorOperationUnregister
	#define CHK_SupervisorOperationUnregister  TRUE
	#define EXP_SupervisorOperationUnregister  CAL_CMEXPAPI( "SupervisorOperationUnregister" ) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_SupervisorOperationUnregister
	#define EXT_SupervisorOperationUnregister
	#define GET_SupervisorOperationUnregister(fl)  CAL_CMGETAPI( "SupervisorOperationUnregister" ) 
	#define CAL_SupervisorOperationUnregister  SupervisorOperationUnregister
	#define CHK_SupervisorOperationUnregister  TRUE
	#define EXP_SupervisorOperationUnregister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationUnregister", (RTS_UINTPTR)SupervisorOperationUnregister, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorSupervisorOperationUnregister
	#define EXT_CmpSupervisorSupervisorOperationUnregister
	#define GET_CmpSupervisorSupervisorOperationUnregister  ERR_OK
	#define CAL_CmpSupervisorSupervisorOperationUnregister pICmpSupervisor->ISupervisorOperationUnregister
	#define CHK_CmpSupervisorSupervisorOperationUnregister (pICmpSupervisor != NULL)
	#define EXP_CmpSupervisorSupervisorOperationUnregister  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SupervisorOperationUnregister
	#define EXT_SupervisorOperationUnregister
	#define GET_SupervisorOperationUnregister(fl)  CAL_CMGETAPI( "SupervisorOperationUnregister" ) 
	#define CAL_SupervisorOperationUnregister pICmpSupervisor->ISupervisorOperationUnregister
	#define CHK_SupervisorOperationUnregister (pICmpSupervisor != NULL)
	#define EXP_SupervisorOperationUnregister  CAL_CMEXPAPI( "SupervisorOperationUnregister" ) 
#else /* DYNAMIC_LINK */
	#define USE_SupervisorOperationUnregister  PFSUPERVISOROPERATIONUNREGISTER pfSupervisorOperationUnregister;
	#define EXT_SupervisorOperationUnregister  extern PFSUPERVISOROPERATIONUNREGISTER pfSupervisorOperationUnregister;
	#define GET_SupervisorOperationUnregister(fl)  s_pfCMGetAPI2( "SupervisorOperationUnregister", (RTS_VOID_FCTPTR *)&pfSupervisorOperationUnregister, (fl), 0, 0)
	#define CAL_SupervisorOperationUnregister  pfSupervisorOperationUnregister
	#define CHK_SupervisorOperationUnregister  (pfSupervisorOperationUnregister != NULL)
	#define EXP_SupervisorOperationUnregister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationUnregister", (RTS_UINTPTR)SupervisorOperationUnregister, 0, 0) 
#endif




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
SupervisorState* CDECL SupervisorOperationGetState(RTS_RESULT *pResult);
typedef SupervisorState* (CDECL * PFSUPERVISOROPERATIONGETSTATE) (RTS_RESULT *pResult);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONGETSTATE_NOTIMPLEMENTED)
	#define USE_SupervisorOperationGetState
	#define EXT_SupervisorOperationGetState
	#define GET_SupervisorOperationGetState(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SupervisorOperationGetState(p0)  (SupervisorState*)ERR_NOTIMPLEMENTED
	#define CHK_SupervisorOperationGetState  FALSE
	#define EXP_SupervisorOperationGetState  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SupervisorOperationGetState
	#define EXT_SupervisorOperationGetState
	#define GET_SupervisorOperationGetState(fl)  CAL_CMGETAPI( "SupervisorOperationGetState" ) 
	#define CAL_SupervisorOperationGetState  SupervisorOperationGetState
	#define CHK_SupervisorOperationGetState  TRUE
	#define EXP_SupervisorOperationGetState  CAL_CMEXPAPI( "SupervisorOperationGetState" ) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_SupervisorOperationGetState
	#define EXT_SupervisorOperationGetState
	#define GET_SupervisorOperationGetState(fl)  CAL_CMGETAPI( "SupervisorOperationGetState" ) 
	#define CAL_SupervisorOperationGetState  SupervisorOperationGetState
	#define CHK_SupervisorOperationGetState  TRUE
	#define EXP_SupervisorOperationGetState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationGetState", (RTS_UINTPTR)SupervisorOperationGetState, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorSupervisorOperationGetState
	#define EXT_CmpSupervisorSupervisorOperationGetState
	#define GET_CmpSupervisorSupervisorOperationGetState  ERR_OK
	#define CAL_CmpSupervisorSupervisorOperationGetState pICmpSupervisor->ISupervisorOperationGetState
	#define CHK_CmpSupervisorSupervisorOperationGetState (pICmpSupervisor != NULL)
	#define EXP_CmpSupervisorSupervisorOperationGetState  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SupervisorOperationGetState
	#define EXT_SupervisorOperationGetState
	#define GET_SupervisorOperationGetState(fl)  CAL_CMGETAPI( "SupervisorOperationGetState" ) 
	#define CAL_SupervisorOperationGetState pICmpSupervisor->ISupervisorOperationGetState
	#define CHK_SupervisorOperationGetState (pICmpSupervisor != NULL)
	#define EXP_SupervisorOperationGetState  CAL_CMEXPAPI( "SupervisorOperationGetState" ) 
#else /* DYNAMIC_LINK */
	#define USE_SupervisorOperationGetState  PFSUPERVISOROPERATIONGETSTATE pfSupervisorOperationGetState;
	#define EXT_SupervisorOperationGetState  extern PFSUPERVISOROPERATIONGETSTATE pfSupervisorOperationGetState;
	#define GET_SupervisorOperationGetState(fl)  s_pfCMGetAPI2( "SupervisorOperationGetState", (RTS_VOID_FCTPTR *)&pfSupervisorOperationGetState, (fl), 0, 0)
	#define CAL_SupervisorOperationGetState  pfSupervisorOperationGetState
	#define CHK_SupervisorOperationGetState  (pfSupervisorOperationGetState != NULL)
	#define EXP_SupervisorOperationGetState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationGetState", (RTS_UINTPTR)SupervisorOperationGetState, 0, 0) 
#endif




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
RTS_RESULT CDECL SupervisorOperationGetState2(SupervisorState *pSupervisorState);
typedef RTS_RESULT (CDECL * PFSUPERVISOROPERATIONGETSTATE2) (SupervisorState *pSupervisorState);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONGETSTATE2_NOTIMPLEMENTED)
	#define USE_SupervisorOperationGetState2
	#define EXT_SupervisorOperationGetState2
	#define GET_SupervisorOperationGetState2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SupervisorOperationGetState2(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SupervisorOperationGetState2  FALSE
	#define EXP_SupervisorOperationGetState2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SupervisorOperationGetState2
	#define EXT_SupervisorOperationGetState2
	#define GET_SupervisorOperationGetState2(fl)  CAL_CMGETAPI( "SupervisorOperationGetState2" ) 
	#define CAL_SupervisorOperationGetState2  SupervisorOperationGetState2
	#define CHK_SupervisorOperationGetState2  TRUE
	#define EXP_SupervisorOperationGetState2  CAL_CMEXPAPI( "SupervisorOperationGetState2" ) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_SupervisorOperationGetState2
	#define EXT_SupervisorOperationGetState2
	#define GET_SupervisorOperationGetState2(fl)  CAL_CMGETAPI( "SupervisorOperationGetState2" ) 
	#define CAL_SupervisorOperationGetState2  SupervisorOperationGetState2
	#define CHK_SupervisorOperationGetState2  TRUE
	#define EXP_SupervisorOperationGetState2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationGetState2", (RTS_UINTPTR)SupervisorOperationGetState2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorSupervisorOperationGetState2
	#define EXT_CmpSupervisorSupervisorOperationGetState2
	#define GET_CmpSupervisorSupervisorOperationGetState2  ERR_OK
	#define CAL_CmpSupervisorSupervisorOperationGetState2 pICmpSupervisor->ISupervisorOperationGetState2
	#define CHK_CmpSupervisorSupervisorOperationGetState2 (pICmpSupervisor != NULL)
	#define EXP_CmpSupervisorSupervisorOperationGetState2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SupervisorOperationGetState2
	#define EXT_SupervisorOperationGetState2
	#define GET_SupervisorOperationGetState2(fl)  CAL_CMGETAPI( "SupervisorOperationGetState2" ) 
	#define CAL_SupervisorOperationGetState2 pICmpSupervisor->ISupervisorOperationGetState2
	#define CHK_SupervisorOperationGetState2 (pICmpSupervisor != NULL)
	#define EXP_SupervisorOperationGetState2  CAL_CMEXPAPI( "SupervisorOperationGetState2" ) 
#else /* DYNAMIC_LINK */
	#define USE_SupervisorOperationGetState2  PFSUPERVISOROPERATIONGETSTATE2 pfSupervisorOperationGetState2;
	#define EXT_SupervisorOperationGetState2  extern PFSUPERVISOROPERATIONGETSTATE2 pfSupervisorOperationGetState2;
	#define GET_SupervisorOperationGetState2(fl)  s_pfCMGetAPI2( "SupervisorOperationGetState2", (RTS_VOID_FCTPTR *)&pfSupervisorOperationGetState2, (fl), 0, 0)
	#define CAL_SupervisorOperationGetState2  pfSupervisorOperationGetState2
	#define CHK_SupervisorOperationGetState2  (pfSupervisorOperationGetState2 != NULL)
	#define EXP_SupervisorOperationGetState2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationGetState2", (RTS_UINTPTR)SupervisorOperationGetState2, 0, 0) 
#endif




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
RTS_HANDLE CDECL SupervisorOperationGetFirst(RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSUPERVISOROPERATIONGETFIRST) (RTS_RESULT *pResult);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONGETFIRST_NOTIMPLEMENTED)
	#define USE_SupervisorOperationGetFirst
	#define EXT_SupervisorOperationGetFirst
	#define GET_SupervisorOperationGetFirst(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SupervisorOperationGetFirst(p0)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SupervisorOperationGetFirst  FALSE
	#define EXP_SupervisorOperationGetFirst  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SupervisorOperationGetFirst
	#define EXT_SupervisorOperationGetFirst
	#define GET_SupervisorOperationGetFirst(fl)  CAL_CMGETAPI( "SupervisorOperationGetFirst" ) 
	#define CAL_SupervisorOperationGetFirst  SupervisorOperationGetFirst
	#define CHK_SupervisorOperationGetFirst  TRUE
	#define EXP_SupervisorOperationGetFirst  CAL_CMEXPAPI( "SupervisorOperationGetFirst" ) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_SupervisorOperationGetFirst
	#define EXT_SupervisorOperationGetFirst
	#define GET_SupervisorOperationGetFirst(fl)  CAL_CMGETAPI( "SupervisorOperationGetFirst" ) 
	#define CAL_SupervisorOperationGetFirst  SupervisorOperationGetFirst
	#define CHK_SupervisorOperationGetFirst  TRUE
	#define EXP_SupervisorOperationGetFirst  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationGetFirst", (RTS_UINTPTR)SupervisorOperationGetFirst, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorSupervisorOperationGetFirst
	#define EXT_CmpSupervisorSupervisorOperationGetFirst
	#define GET_CmpSupervisorSupervisorOperationGetFirst  ERR_OK
	#define CAL_CmpSupervisorSupervisorOperationGetFirst pICmpSupervisor->ISupervisorOperationGetFirst
	#define CHK_CmpSupervisorSupervisorOperationGetFirst (pICmpSupervisor != NULL)
	#define EXP_CmpSupervisorSupervisorOperationGetFirst  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SupervisorOperationGetFirst
	#define EXT_SupervisorOperationGetFirst
	#define GET_SupervisorOperationGetFirst(fl)  CAL_CMGETAPI( "SupervisorOperationGetFirst" ) 
	#define CAL_SupervisorOperationGetFirst pICmpSupervisor->ISupervisorOperationGetFirst
	#define CHK_SupervisorOperationGetFirst (pICmpSupervisor != NULL)
	#define EXP_SupervisorOperationGetFirst  CAL_CMEXPAPI( "SupervisorOperationGetFirst" ) 
#else /* DYNAMIC_LINK */
	#define USE_SupervisorOperationGetFirst  PFSUPERVISOROPERATIONGETFIRST pfSupervisorOperationGetFirst;
	#define EXT_SupervisorOperationGetFirst  extern PFSUPERVISOROPERATIONGETFIRST pfSupervisorOperationGetFirst;
	#define GET_SupervisorOperationGetFirst(fl)  s_pfCMGetAPI2( "SupervisorOperationGetFirst", (RTS_VOID_FCTPTR *)&pfSupervisorOperationGetFirst, (fl), 0, 0)
	#define CAL_SupervisorOperationGetFirst  pfSupervisorOperationGetFirst
	#define CHK_SupervisorOperationGetFirst  (pfSupervisorOperationGetFirst != NULL)
	#define EXP_SupervisorOperationGetFirst  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationGetFirst", (RTS_UINTPTR)SupervisorOperationGetFirst, 0, 0) 
#endif




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
RTS_HANDLE CDECL SupervisorOperationGetNext(RTS_HANDLE hPrevOperation, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSUPERVISOROPERATIONGETNEXT) (RTS_HANDLE hPrevOperation, RTS_RESULT *pResult);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONGETNEXT_NOTIMPLEMENTED)
	#define USE_SupervisorOperationGetNext
	#define EXT_SupervisorOperationGetNext
	#define GET_SupervisorOperationGetNext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SupervisorOperationGetNext(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SupervisorOperationGetNext  FALSE
	#define EXP_SupervisorOperationGetNext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SupervisorOperationGetNext
	#define EXT_SupervisorOperationGetNext
	#define GET_SupervisorOperationGetNext(fl)  CAL_CMGETAPI( "SupervisorOperationGetNext" ) 
	#define CAL_SupervisorOperationGetNext  SupervisorOperationGetNext
	#define CHK_SupervisorOperationGetNext  TRUE
	#define EXP_SupervisorOperationGetNext  CAL_CMEXPAPI( "SupervisorOperationGetNext" ) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_SupervisorOperationGetNext
	#define EXT_SupervisorOperationGetNext
	#define GET_SupervisorOperationGetNext(fl)  CAL_CMGETAPI( "SupervisorOperationGetNext" ) 
	#define CAL_SupervisorOperationGetNext  SupervisorOperationGetNext
	#define CHK_SupervisorOperationGetNext  TRUE
	#define EXP_SupervisorOperationGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationGetNext", (RTS_UINTPTR)SupervisorOperationGetNext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorSupervisorOperationGetNext
	#define EXT_CmpSupervisorSupervisorOperationGetNext
	#define GET_CmpSupervisorSupervisorOperationGetNext  ERR_OK
	#define CAL_CmpSupervisorSupervisorOperationGetNext pICmpSupervisor->ISupervisorOperationGetNext
	#define CHK_CmpSupervisorSupervisorOperationGetNext (pICmpSupervisor != NULL)
	#define EXP_CmpSupervisorSupervisorOperationGetNext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SupervisorOperationGetNext
	#define EXT_SupervisorOperationGetNext
	#define GET_SupervisorOperationGetNext(fl)  CAL_CMGETAPI( "SupervisorOperationGetNext" ) 
	#define CAL_SupervisorOperationGetNext pICmpSupervisor->ISupervisorOperationGetNext
	#define CHK_SupervisorOperationGetNext (pICmpSupervisor != NULL)
	#define EXP_SupervisorOperationGetNext  CAL_CMEXPAPI( "SupervisorOperationGetNext" ) 
#else /* DYNAMIC_LINK */
	#define USE_SupervisorOperationGetNext  PFSUPERVISOROPERATIONGETNEXT pfSupervisorOperationGetNext;
	#define EXT_SupervisorOperationGetNext  extern PFSUPERVISOROPERATIONGETNEXT pfSupervisorOperationGetNext;
	#define GET_SupervisorOperationGetNext(fl)  s_pfCMGetAPI2( "SupervisorOperationGetNext", (RTS_VOID_FCTPTR *)&pfSupervisorOperationGetNext, (fl), 0, 0)
	#define CAL_SupervisorOperationGetNext  pfSupervisorOperationGetNext
	#define CHK_SupervisorOperationGetNext  (pfSupervisorOperationGetNext != NULL)
	#define EXP_SupervisorOperationGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationGetNext", (RTS_UINTPTR)SupervisorOperationGetNext, 0, 0) 
#endif




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
SupervisorEntry* CDECL SupervisorOperationGetEntry(RTS_HANDLE hOperation, RTS_RESULT *pResult);
typedef SupervisorEntry* (CDECL * PFSUPERVISOROPERATIONGETENTRY) (RTS_HANDLE hOperation, RTS_RESULT *pResult);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONGETENTRY_NOTIMPLEMENTED)
	#define USE_SupervisorOperationGetEntry
	#define EXT_SupervisorOperationGetEntry
	#define GET_SupervisorOperationGetEntry(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SupervisorOperationGetEntry(p0,p1)  (SupervisorEntry*)ERR_NOTIMPLEMENTED
	#define CHK_SupervisorOperationGetEntry  FALSE
	#define EXP_SupervisorOperationGetEntry  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SupervisorOperationGetEntry
	#define EXT_SupervisorOperationGetEntry
	#define GET_SupervisorOperationGetEntry(fl)  CAL_CMGETAPI( "SupervisorOperationGetEntry" ) 
	#define CAL_SupervisorOperationGetEntry  SupervisorOperationGetEntry
	#define CHK_SupervisorOperationGetEntry  TRUE
	#define EXP_SupervisorOperationGetEntry  CAL_CMEXPAPI( "SupervisorOperationGetEntry" ) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_SupervisorOperationGetEntry
	#define EXT_SupervisorOperationGetEntry
	#define GET_SupervisorOperationGetEntry(fl)  CAL_CMGETAPI( "SupervisorOperationGetEntry" ) 
	#define CAL_SupervisorOperationGetEntry  SupervisorOperationGetEntry
	#define CHK_SupervisorOperationGetEntry  TRUE
	#define EXP_SupervisorOperationGetEntry  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationGetEntry", (RTS_UINTPTR)SupervisorOperationGetEntry, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorSupervisorOperationGetEntry
	#define EXT_CmpSupervisorSupervisorOperationGetEntry
	#define GET_CmpSupervisorSupervisorOperationGetEntry  ERR_OK
	#define CAL_CmpSupervisorSupervisorOperationGetEntry pICmpSupervisor->ISupervisorOperationGetEntry
	#define CHK_CmpSupervisorSupervisorOperationGetEntry (pICmpSupervisor != NULL)
	#define EXP_CmpSupervisorSupervisorOperationGetEntry  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SupervisorOperationGetEntry
	#define EXT_SupervisorOperationGetEntry
	#define GET_SupervisorOperationGetEntry(fl)  CAL_CMGETAPI( "SupervisorOperationGetEntry" ) 
	#define CAL_SupervisorOperationGetEntry pICmpSupervisor->ISupervisorOperationGetEntry
	#define CHK_SupervisorOperationGetEntry (pICmpSupervisor != NULL)
	#define EXP_SupervisorOperationGetEntry  CAL_CMEXPAPI( "SupervisorOperationGetEntry" ) 
#else /* DYNAMIC_LINK */
	#define USE_SupervisorOperationGetEntry  PFSUPERVISOROPERATIONGETENTRY pfSupervisorOperationGetEntry;
	#define EXT_SupervisorOperationGetEntry  extern PFSUPERVISOROPERATIONGETENTRY pfSupervisorOperationGetEntry;
	#define GET_SupervisorOperationGetEntry(fl)  s_pfCMGetAPI2( "SupervisorOperationGetEntry", (RTS_VOID_FCTPTR *)&pfSupervisorOperationGetEntry, (fl), 0, 0)
	#define CAL_SupervisorOperationGetEntry  pfSupervisorOperationGetEntry
	#define CHK_SupervisorOperationGetEntry  (pfSupervisorOperationGetEntry != NULL)
	#define EXP_SupervisorOperationGetEntry  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationGetEntry", (RTS_UINTPTR)SupervisorOperationGetEntry, 0, 0) 
#endif




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
RTS_RESULT CDECL SupervisorOperationEnable(RTS_HANDLE hOperation);
typedef RTS_RESULT (CDECL * PFSUPERVISOROPERATIONENABLE) (RTS_HANDLE hOperation);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONENABLE_NOTIMPLEMENTED)
	#define USE_SupervisorOperationEnable
	#define EXT_SupervisorOperationEnable
	#define GET_SupervisorOperationEnable(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SupervisorOperationEnable(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SupervisorOperationEnable  FALSE
	#define EXP_SupervisorOperationEnable  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SupervisorOperationEnable
	#define EXT_SupervisorOperationEnable
	#define GET_SupervisorOperationEnable(fl)  CAL_CMGETAPI( "SupervisorOperationEnable" ) 
	#define CAL_SupervisorOperationEnable  SupervisorOperationEnable
	#define CHK_SupervisorOperationEnable  TRUE
	#define EXP_SupervisorOperationEnable  CAL_CMEXPAPI( "SupervisorOperationEnable" ) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_SupervisorOperationEnable
	#define EXT_SupervisorOperationEnable
	#define GET_SupervisorOperationEnable(fl)  CAL_CMGETAPI( "SupervisorOperationEnable" ) 
	#define CAL_SupervisorOperationEnable  SupervisorOperationEnable
	#define CHK_SupervisorOperationEnable  TRUE
	#define EXP_SupervisorOperationEnable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationEnable", (RTS_UINTPTR)SupervisorOperationEnable, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorSupervisorOperationEnable
	#define EXT_CmpSupervisorSupervisorOperationEnable
	#define GET_CmpSupervisorSupervisorOperationEnable  ERR_OK
	#define CAL_CmpSupervisorSupervisorOperationEnable pICmpSupervisor->ISupervisorOperationEnable
	#define CHK_CmpSupervisorSupervisorOperationEnable (pICmpSupervisor != NULL)
	#define EXP_CmpSupervisorSupervisorOperationEnable  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SupervisorOperationEnable
	#define EXT_SupervisorOperationEnable
	#define GET_SupervisorOperationEnable(fl)  CAL_CMGETAPI( "SupervisorOperationEnable" ) 
	#define CAL_SupervisorOperationEnable pICmpSupervisor->ISupervisorOperationEnable
	#define CHK_SupervisorOperationEnable (pICmpSupervisor != NULL)
	#define EXP_SupervisorOperationEnable  CAL_CMEXPAPI( "SupervisorOperationEnable" ) 
#else /* DYNAMIC_LINK */
	#define USE_SupervisorOperationEnable  PFSUPERVISOROPERATIONENABLE pfSupervisorOperationEnable;
	#define EXT_SupervisorOperationEnable  extern PFSUPERVISOROPERATIONENABLE pfSupervisorOperationEnable;
	#define GET_SupervisorOperationEnable(fl)  s_pfCMGetAPI2( "SupervisorOperationEnable", (RTS_VOID_FCTPTR *)&pfSupervisorOperationEnable, (fl), 0, 0)
	#define CAL_SupervisorOperationEnable  pfSupervisorOperationEnable
	#define CHK_SupervisorOperationEnable  (pfSupervisorOperationEnable != NULL)
	#define EXP_SupervisorOperationEnable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationEnable", (RTS_UINTPTR)SupervisorOperationEnable, 0, 0) 
#endif




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
RTS_RESULT CDECL SupervisorOperationDisable(RTS_HANDLE hOperation);
typedef RTS_RESULT (CDECL * PFSUPERVISOROPERATIONDISABLE) (RTS_HANDLE hOperation);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONDISABLE_NOTIMPLEMENTED)
	#define USE_SupervisorOperationDisable
	#define EXT_SupervisorOperationDisable
	#define GET_SupervisorOperationDisable(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SupervisorOperationDisable(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SupervisorOperationDisable  FALSE
	#define EXP_SupervisorOperationDisable  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SupervisorOperationDisable
	#define EXT_SupervisorOperationDisable
	#define GET_SupervisorOperationDisable(fl)  CAL_CMGETAPI( "SupervisorOperationDisable" ) 
	#define CAL_SupervisorOperationDisable  SupervisorOperationDisable
	#define CHK_SupervisorOperationDisable  TRUE
	#define EXP_SupervisorOperationDisable  CAL_CMEXPAPI( "SupervisorOperationDisable" ) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_SupervisorOperationDisable
	#define EXT_SupervisorOperationDisable
	#define GET_SupervisorOperationDisable(fl)  CAL_CMGETAPI( "SupervisorOperationDisable" ) 
	#define CAL_SupervisorOperationDisable  SupervisorOperationDisable
	#define CHK_SupervisorOperationDisable  TRUE
	#define EXP_SupervisorOperationDisable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationDisable", (RTS_UINTPTR)SupervisorOperationDisable, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorSupervisorOperationDisable
	#define EXT_CmpSupervisorSupervisorOperationDisable
	#define GET_CmpSupervisorSupervisorOperationDisable  ERR_OK
	#define CAL_CmpSupervisorSupervisorOperationDisable pICmpSupervisor->ISupervisorOperationDisable
	#define CHK_CmpSupervisorSupervisorOperationDisable (pICmpSupervisor != NULL)
	#define EXP_CmpSupervisorSupervisorOperationDisable  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SupervisorOperationDisable
	#define EXT_SupervisorOperationDisable
	#define GET_SupervisorOperationDisable(fl)  CAL_CMGETAPI( "SupervisorOperationDisable" ) 
	#define CAL_SupervisorOperationDisable pICmpSupervisor->ISupervisorOperationDisable
	#define CHK_SupervisorOperationDisable (pICmpSupervisor != NULL)
	#define EXP_SupervisorOperationDisable  CAL_CMEXPAPI( "SupervisorOperationDisable" ) 
#else /* DYNAMIC_LINK */
	#define USE_SupervisorOperationDisable  PFSUPERVISOROPERATIONDISABLE pfSupervisorOperationDisable;
	#define EXT_SupervisorOperationDisable  extern PFSUPERVISOROPERATIONDISABLE pfSupervisorOperationDisable;
	#define GET_SupervisorOperationDisable(fl)  s_pfCMGetAPI2( "SupervisorOperationDisable", (RTS_VOID_FCTPTR *)&pfSupervisorOperationDisable, (fl), 0, 0)
	#define CAL_SupervisorOperationDisable  pfSupervisorOperationDisable
	#define CHK_SupervisorOperationDisable  (pfSupervisorOperationDisable != NULL)
	#define EXP_SupervisorOperationDisable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationDisable", (RTS_UINTPTR)SupervisorOperationDisable, 0, 0) 
#endif




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
RTS_RESULT CDECL SupervisorOperationAlive(RTS_HANDLE hOperation, RTS_SYSTIME *pstTimestampUs);
typedef RTS_RESULT (CDECL * PFSUPERVISOROPERATIONALIVE) (RTS_HANDLE hOperation, RTS_SYSTIME *pstTimestampUs);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONALIVE_NOTIMPLEMENTED)
	#define USE_SupervisorOperationAlive
	#define EXT_SupervisorOperationAlive
	#define GET_SupervisorOperationAlive(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SupervisorOperationAlive(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SupervisorOperationAlive  FALSE
	#define EXP_SupervisorOperationAlive  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SupervisorOperationAlive
	#define EXT_SupervisorOperationAlive
	#define GET_SupervisorOperationAlive(fl)  CAL_CMGETAPI( "SupervisorOperationAlive" ) 
	#define CAL_SupervisorOperationAlive  SupervisorOperationAlive
	#define CHK_SupervisorOperationAlive  TRUE
	#define EXP_SupervisorOperationAlive  CAL_CMEXPAPI( "SupervisorOperationAlive" ) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_SupervisorOperationAlive
	#define EXT_SupervisorOperationAlive
	#define GET_SupervisorOperationAlive(fl)  CAL_CMGETAPI( "SupervisorOperationAlive" ) 
	#define CAL_SupervisorOperationAlive  SupervisorOperationAlive
	#define CHK_SupervisorOperationAlive  TRUE
	#define EXP_SupervisorOperationAlive  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationAlive", (RTS_UINTPTR)SupervisorOperationAlive, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorSupervisorOperationAlive
	#define EXT_CmpSupervisorSupervisorOperationAlive
	#define GET_CmpSupervisorSupervisorOperationAlive  ERR_OK
	#define CAL_CmpSupervisorSupervisorOperationAlive pICmpSupervisor->ISupervisorOperationAlive
	#define CHK_CmpSupervisorSupervisorOperationAlive (pICmpSupervisor != NULL)
	#define EXP_CmpSupervisorSupervisorOperationAlive  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SupervisorOperationAlive
	#define EXT_SupervisorOperationAlive
	#define GET_SupervisorOperationAlive(fl)  CAL_CMGETAPI( "SupervisorOperationAlive" ) 
	#define CAL_SupervisorOperationAlive pICmpSupervisor->ISupervisorOperationAlive
	#define CHK_SupervisorOperationAlive (pICmpSupervisor != NULL)
	#define EXP_SupervisorOperationAlive  CAL_CMEXPAPI( "SupervisorOperationAlive" ) 
#else /* DYNAMIC_LINK */
	#define USE_SupervisorOperationAlive  PFSUPERVISOROPERATIONALIVE pfSupervisorOperationAlive;
	#define EXT_SupervisorOperationAlive  extern PFSUPERVISOROPERATIONALIVE pfSupervisorOperationAlive;
	#define GET_SupervisorOperationAlive(fl)  s_pfCMGetAPI2( "SupervisorOperationAlive", (RTS_VOID_FCTPTR *)&pfSupervisorOperationAlive, (fl), 0, 0)
	#define CAL_SupervisorOperationAlive  pfSupervisorOperationAlive
	#define CHK_SupervisorOperationAlive  (pfSupervisorOperationAlive != NULL)
	#define EXP_SupervisorOperationAlive  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationAlive", (RTS_UINTPTR)SupervisorOperationAlive, 0, 0) 
#endif




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
RTS_RESULT CDECL SupervisorOperationDead(RTS_HANDLE hOperation);
typedef RTS_RESULT (CDECL * PFSUPERVISOROPERATIONDEAD) (RTS_HANDLE hOperation);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONDEAD_NOTIMPLEMENTED)
	#define USE_SupervisorOperationDead
	#define EXT_SupervisorOperationDead
	#define GET_SupervisorOperationDead(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SupervisorOperationDead(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SupervisorOperationDead  FALSE
	#define EXP_SupervisorOperationDead  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SupervisorOperationDead
	#define EXT_SupervisorOperationDead
	#define GET_SupervisorOperationDead(fl)  CAL_CMGETAPI( "SupervisorOperationDead" ) 
	#define CAL_SupervisorOperationDead  SupervisorOperationDead
	#define CHK_SupervisorOperationDead  TRUE
	#define EXP_SupervisorOperationDead  CAL_CMEXPAPI( "SupervisorOperationDead" ) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_SupervisorOperationDead
	#define EXT_SupervisorOperationDead
	#define GET_SupervisorOperationDead(fl)  CAL_CMGETAPI( "SupervisorOperationDead" ) 
	#define CAL_SupervisorOperationDead  SupervisorOperationDead
	#define CHK_SupervisorOperationDead  TRUE
	#define EXP_SupervisorOperationDead  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationDead", (RTS_UINTPTR)SupervisorOperationDead, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorSupervisorOperationDead
	#define EXT_CmpSupervisorSupervisorOperationDead
	#define GET_CmpSupervisorSupervisorOperationDead  ERR_OK
	#define CAL_CmpSupervisorSupervisorOperationDead pICmpSupervisor->ISupervisorOperationDead
	#define CHK_CmpSupervisorSupervisorOperationDead (pICmpSupervisor != NULL)
	#define EXP_CmpSupervisorSupervisorOperationDead  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SupervisorOperationDead
	#define EXT_SupervisorOperationDead
	#define GET_SupervisorOperationDead(fl)  CAL_CMGETAPI( "SupervisorOperationDead" ) 
	#define CAL_SupervisorOperationDead pICmpSupervisor->ISupervisorOperationDead
	#define CHK_SupervisorOperationDead (pICmpSupervisor != NULL)
	#define EXP_SupervisorOperationDead  CAL_CMEXPAPI( "SupervisorOperationDead" ) 
#else /* DYNAMIC_LINK */
	#define USE_SupervisorOperationDead  PFSUPERVISOROPERATIONDEAD pfSupervisorOperationDead;
	#define EXT_SupervisorOperationDead  extern PFSUPERVISOROPERATIONDEAD pfSupervisorOperationDead;
	#define GET_SupervisorOperationDead(fl)  s_pfCMGetAPI2( "SupervisorOperationDead", (RTS_VOID_FCTPTR *)&pfSupervisorOperationDead, (fl), 0, 0)
	#define CAL_SupervisorOperationDead  pfSupervisorOperationDead
	#define CHK_SupervisorOperationDead  (pfSupervisorOperationDead != NULL)
	#define EXP_SupervisorOperationDead  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationDead", (RTS_UINTPTR)SupervisorOperationDead, 0, 0) 
#endif




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
RTS_RESULT CDECL SupervisorOperationSetTimeout(RTS_HANDLE hOperation, RTS_SYSTIME stTimeoutUs);
typedef RTS_RESULT (CDECL * PFSUPERVISOROPERATIONSETTIMEOUT) (RTS_HANDLE hOperation, RTS_SYSTIME stTimeoutUs);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONSETTIMEOUT_NOTIMPLEMENTED)
	#define USE_SupervisorOperationSetTimeout
	#define EXT_SupervisorOperationSetTimeout
	#define GET_SupervisorOperationSetTimeout(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SupervisorOperationSetTimeout(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SupervisorOperationSetTimeout  FALSE
	#define EXP_SupervisorOperationSetTimeout  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SupervisorOperationSetTimeout
	#define EXT_SupervisorOperationSetTimeout
	#define GET_SupervisorOperationSetTimeout(fl)  CAL_CMGETAPI( "SupervisorOperationSetTimeout" ) 
	#define CAL_SupervisorOperationSetTimeout  SupervisorOperationSetTimeout
	#define CHK_SupervisorOperationSetTimeout  TRUE
	#define EXP_SupervisorOperationSetTimeout  CAL_CMEXPAPI( "SupervisorOperationSetTimeout" ) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_SupervisorOperationSetTimeout
	#define EXT_SupervisorOperationSetTimeout
	#define GET_SupervisorOperationSetTimeout(fl)  CAL_CMGETAPI( "SupervisorOperationSetTimeout" ) 
	#define CAL_SupervisorOperationSetTimeout  SupervisorOperationSetTimeout
	#define CHK_SupervisorOperationSetTimeout  TRUE
	#define EXP_SupervisorOperationSetTimeout  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationSetTimeout", (RTS_UINTPTR)SupervisorOperationSetTimeout, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorSupervisorOperationSetTimeout
	#define EXT_CmpSupervisorSupervisorOperationSetTimeout
	#define GET_CmpSupervisorSupervisorOperationSetTimeout  ERR_OK
	#define CAL_CmpSupervisorSupervisorOperationSetTimeout pICmpSupervisor->ISupervisorOperationSetTimeout
	#define CHK_CmpSupervisorSupervisorOperationSetTimeout (pICmpSupervisor != NULL)
	#define EXP_CmpSupervisorSupervisorOperationSetTimeout  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SupervisorOperationSetTimeout
	#define EXT_SupervisorOperationSetTimeout
	#define GET_SupervisorOperationSetTimeout(fl)  CAL_CMGETAPI( "SupervisorOperationSetTimeout" ) 
	#define CAL_SupervisorOperationSetTimeout pICmpSupervisor->ISupervisorOperationSetTimeout
	#define CHK_SupervisorOperationSetTimeout (pICmpSupervisor != NULL)
	#define EXP_SupervisorOperationSetTimeout  CAL_CMEXPAPI( "SupervisorOperationSetTimeout" ) 
#else /* DYNAMIC_LINK */
	#define USE_SupervisorOperationSetTimeout  PFSUPERVISOROPERATIONSETTIMEOUT pfSupervisorOperationSetTimeout;
	#define EXT_SupervisorOperationSetTimeout  extern PFSUPERVISOROPERATIONSETTIMEOUT pfSupervisorOperationSetTimeout;
	#define GET_SupervisorOperationSetTimeout(fl)  s_pfCMGetAPI2( "SupervisorOperationSetTimeout", (RTS_VOID_FCTPTR *)&pfSupervisorOperationSetTimeout, (fl), 0, 0)
	#define CAL_SupervisorOperationSetTimeout  pfSupervisorOperationSetTimeout
	#define CHK_SupervisorOperationSetTimeout  (pfSupervisorOperationSetTimeout != NULL)
	#define EXP_SupervisorOperationSetTimeout  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationSetTimeout", (RTS_UINTPTR)SupervisorOperationSetTimeout, 0, 0) 
#endif




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
RTS_HANDLE CDECL SupervisorOperationGet(RTS_UI32 ui32OperationID, RTS_UI32 cmpId, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSUPERVISOROPERATIONGET) (RTS_UI32 ui32OperationID, RTS_UI32 cmpId, RTS_RESULT *pResult);
#if defined(CMPSUPERVISOR_NOTIMPLEMENTED) || defined(SUPERVISOROPERATIONGET_NOTIMPLEMENTED)
	#define USE_SupervisorOperationGet
	#define EXT_SupervisorOperationGet
	#define GET_SupervisorOperationGet(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SupervisorOperationGet(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SupervisorOperationGet  FALSE
	#define EXP_SupervisorOperationGet  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SupervisorOperationGet
	#define EXT_SupervisorOperationGet
	#define GET_SupervisorOperationGet(fl)  CAL_CMGETAPI( "SupervisorOperationGet" ) 
	#define CAL_SupervisorOperationGet  SupervisorOperationGet
	#define CHK_SupervisorOperationGet  TRUE
	#define EXP_SupervisorOperationGet  CAL_CMEXPAPI( "SupervisorOperationGet" ) 
#elif defined(MIXED_LINK) && !defined(CMPSUPERVISOR_EXTERNAL)
	#define USE_SupervisorOperationGet
	#define EXT_SupervisorOperationGet
	#define GET_SupervisorOperationGet(fl)  CAL_CMGETAPI( "SupervisorOperationGet" ) 
	#define CAL_SupervisorOperationGet  SupervisorOperationGet
	#define CHK_SupervisorOperationGet  TRUE
	#define EXP_SupervisorOperationGet  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationGet", (RTS_UINTPTR)SupervisorOperationGet, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSupervisorSupervisorOperationGet
	#define EXT_CmpSupervisorSupervisorOperationGet
	#define GET_CmpSupervisorSupervisorOperationGet  ERR_OK
	#define CAL_CmpSupervisorSupervisorOperationGet pICmpSupervisor->ISupervisorOperationGet
	#define CHK_CmpSupervisorSupervisorOperationGet (pICmpSupervisor != NULL)
	#define EXP_CmpSupervisorSupervisorOperationGet  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SupervisorOperationGet
	#define EXT_SupervisorOperationGet
	#define GET_SupervisorOperationGet(fl)  CAL_CMGETAPI( "SupervisorOperationGet" ) 
	#define CAL_SupervisorOperationGet pICmpSupervisor->ISupervisorOperationGet
	#define CHK_SupervisorOperationGet (pICmpSupervisor != NULL)
	#define EXP_SupervisorOperationGet  CAL_CMEXPAPI( "SupervisorOperationGet" ) 
#else /* DYNAMIC_LINK */
	#define USE_SupervisorOperationGet  PFSUPERVISOROPERATIONGET pfSupervisorOperationGet;
	#define EXT_SupervisorOperationGet  extern PFSUPERVISOROPERATIONGET pfSupervisorOperationGet;
	#define GET_SupervisorOperationGet(fl)  s_pfCMGetAPI2( "SupervisorOperationGet", (RTS_VOID_FCTPTR *)&pfSupervisorOperationGet, (fl), 0, 0)
	#define CAL_SupervisorOperationGet  pfSupervisorOperationGet
	#define CHK_SupervisorOperationGet  (pfSupervisorOperationGet != NULL)
	#define EXP_SupervisorOperationGet  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SupervisorOperationGet", (RTS_UINTPTR)SupervisorOperationGet, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSUPERVISOROPERATIONREGISTER ISupervisorOperationRegister;
 	PFSUPERVISOROPERATIONUNREGISTER ISupervisorOperationUnregister;
 	PFSUPERVISOROPERATIONGETSTATE ISupervisorOperationGetState;
 	PFSUPERVISOROPERATIONGETSTATE2 ISupervisorOperationGetState2;
 	PFSUPERVISOROPERATIONGETFIRST ISupervisorOperationGetFirst;
 	PFSUPERVISOROPERATIONGETNEXT ISupervisorOperationGetNext;
 	PFSUPERVISOROPERATIONGETENTRY ISupervisorOperationGetEntry;
 	PFSUPERVISOROPERATIONENABLE ISupervisorOperationEnable;
 	PFSUPERVISOROPERATIONDISABLE ISupervisorOperationDisable;
 	PFSUPERVISOROPERATIONALIVE ISupervisorOperationAlive;
 	PFSUPERVISOROPERATIONDEAD ISupervisorOperationDead;
 	PFSUPERVISOROPERATIONSETTIMEOUT ISupervisorOperationSetTimeout;
 	PFSUPERVISOROPERATIONGET ISupervisorOperationGet;
 } ICmpSupervisor_C;

#ifdef CPLUSPLUS
class ICmpSupervisor : public IBase
{
	public:
		virtual RTS_HANDLE CDECL ISupervisorOperationRegister(RTS_UI32 ui32OperationID, CMPID cmpId, char *pszOperationDescription, RTS_SYSTIME stTimeoutUs, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISupervisorOperationUnregister(RTS_HANDLE hOperation) =0;
		virtual SupervisorState* CDECL ISupervisorOperationGetState(RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISupervisorOperationGetState2(SupervisorState *pSupervisorState) =0;
		virtual RTS_HANDLE CDECL ISupervisorOperationGetFirst(RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL ISupervisorOperationGetNext(RTS_HANDLE hPrevOperation, RTS_RESULT *pResult) =0;
		virtual SupervisorEntry* CDECL ISupervisorOperationGetEntry(RTS_HANDLE hOperation, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISupervisorOperationEnable(RTS_HANDLE hOperation) =0;
		virtual RTS_RESULT CDECL ISupervisorOperationDisable(RTS_HANDLE hOperation) =0;
		virtual RTS_RESULT CDECL ISupervisorOperationAlive(RTS_HANDLE hOperation, RTS_SYSTIME *pstTimestampUs) =0;
		virtual RTS_RESULT CDECL ISupervisorOperationDead(RTS_HANDLE hOperation) =0;
		virtual RTS_RESULT CDECL ISupervisorOperationSetTimeout(RTS_HANDLE hOperation, RTS_SYSTIME stTimeoutUs) =0;
		virtual RTS_HANDLE CDECL ISupervisorOperationGet(RTS_UI32 ui32OperationID, RTS_UI32 cmpId, RTS_RESULT *pResult) =0;
};
	#ifndef ITF_CmpSupervisor
		#define ITF_CmpSupervisor static ICmpSupervisor *pICmpSupervisor = NULL;
	#endif
	#define EXTITF_CmpSupervisor
#else	/*CPLUSPLUS*/
	typedef ICmpSupervisor_C		ICmpSupervisor;
	#ifndef ITF_CmpSupervisor
		#define ITF_CmpSupervisor
	#endif
	#define EXTITF_CmpSupervisor
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPSUPERVISORITF_H_*/
