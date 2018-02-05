 /**
 * <interfacename>CmpIpc</interfacename>
 * <description> 
 *	Interface of the inter process communication component.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPIPCITF_H_
#define _CMPIPCITF_H_

#include "CmpStd.h"

 

 




/**
 * <description>Setting that decides about the size of the sharedmemory that is used for the inter
 *	process communication. This size limits the maximal size of data that can be transferred withing one call. 
 *	The size for the data that can be used is about one half of this size for parameters to the call 
 *	as well as return values. </description>
 *
 */
#define CMPIPC_KEY_SHAREDMEMSIZE				"SharedMemSize"
#define CMPIPC_KEY_SHAREDMEMSIZE_DEFAULT		INT32_C(5000)

/**
 * <description>Setting that decides about basename for the shared memory used for the communication of the channel. </description>
 *
 */
#define CMPIPC_KEY_SHAREDMEM_BASENAME				"SharedMemBaseName"
#define CMPIPC_KEY_SHAREDMEM_BASENAME_DEFAULT		"IPC_SHM_"

/**
 * <description>Setting that decides about the interval for the task polling for result or call on a channel. 
 *	This value is in microseconds.</description>
 *
 */
#define CMPIPC_KEY_IPCTASKINTERVAL				"IpcTaskInterval"
#define CMPIPC_KEY_IPCTASKINTERVAL_DEFAULT		INT32_C(20000)

/**
 * <description>Setting that decides about whether one task handles all connections. If this setting is active,
	then usage of event synchronization is not possible at the moment.</description>
 *
 */
#define CMPIPC_KEY_IPCTASKONEFORALL				"IpcOneTaskForAll"
#define CMPIPC_KEY_IPCTASKONEFORALL_DEFAULT		0

/**
 * <description>Setting that decides about the time the task that is polling for calls or returns will sleep after
 *	it has done its work. Increasing this time will reduce cpuload for ipchandling but will also increase
 *	the latency for a call or result to be detected. This value is in milliseconds. </description>
 *
 */	
#define CMPIPC_KEY_IPCPOLLINGWAITTIME				"IpcPollingWaittime"
#define CMPIPC_KEY_IPCPOLLINGWAITTIME_DEFAULT		20

/**
 * <description>Setting that decides about the maximal time a connected client will wait until the connection has been
 *	completely initialized by the creating communication partner. This value is in milliseconds.</description>
 *
 */
#define CMPIPC_KEY_IPCSTARTUPWAITTIME				"IpcStartupWaittime"
#define CMPIPC_KEY_IPCSTARTUPWAITTIME_DEFAULT		INT32_C(10000)

/**
 * <description>Setting that decides about whether this side of an IPC channel should try to use events for faster calls. In fact the usage of
 *	events is only possible if both channels support this.</description>
 *
 */
#define CMPIPC_KEY_EVENTSYNC						"EventSync"
#define CMPIPC_KEY_EVENTSYNC_DEFAULT				1

#define MAX_METHOD_NAME_LEN		40

#define ERR_CHANNELNAMETOOLONG		0x0500
#define ERR_METHODNAMETOOLONG		0x0501
#define ERR_INVALIDTYPEFORGETVALUE	0x0502


#ifdef __cplusplus
extern "C" {
#endif

RTS_RESULT CDECL IpcOpen(char* pszName, RTS_HANDLE* phReturn);
typedef RTS_RESULT (CDECL * PFIPCOPEN) (char* pszName, RTS_HANDLE* phReturn);
#if defined(CMPIPC_NOTIMPLEMENTED) || defined(IPCOPEN_NOTIMPLEMENTED)
	#define USE_IpcOpen
	#define EXT_IpcOpen
	#define GET_IpcOpen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IpcOpen(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IpcOpen  FALSE
	#define EXP_IpcOpen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IpcOpen
	#define EXT_IpcOpen
	#define GET_IpcOpen(fl)  CAL_CMGETAPI( "IpcOpen" ) 
	#define CAL_IpcOpen  IpcOpen
	#define CHK_IpcOpen  TRUE
	#define EXP_IpcOpen  CAL_CMEXPAPI( "IpcOpen" ) 
#elif defined(MIXED_LINK) && !defined(CMPIPC_EXTERNAL)
	#define USE_IpcOpen
	#define EXT_IpcOpen
	#define GET_IpcOpen(fl)  CAL_CMGETAPI( "IpcOpen" ) 
	#define CAL_IpcOpen  IpcOpen
	#define CHK_IpcOpen  TRUE
	#define EXP_IpcOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcOpen", (RTS_UINTPTR)IpcOpen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIpcIpcOpen
	#define EXT_CmpIpcIpcOpen
	#define GET_CmpIpcIpcOpen  ERR_OK
	#define CAL_CmpIpcIpcOpen  IpcOpen
	#define CHK_CmpIpcIpcOpen  TRUE
	#define EXP_CmpIpcIpcOpen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IpcOpen
	#define EXT_IpcOpen
	#define GET_IpcOpen(fl)  CAL_CMGETAPI( "IpcOpen" ) 
	#define CAL_IpcOpen  IpcOpen
	#define CHK_IpcOpen  TRUE
	#define EXP_IpcOpen  CAL_CMEXPAPI( "IpcOpen" ) 
#else /* DYNAMIC_LINK */
	#define USE_IpcOpen  PFIPCOPEN pfIpcOpen;
	#define EXT_IpcOpen  extern PFIPCOPEN pfIpcOpen;
	#define GET_IpcOpen(fl)  s_pfCMGetAPI2( "IpcOpen", (RTS_VOID_FCTPTR *)&pfIpcOpen, (fl), 0, 0)
	#define CAL_IpcOpen  pfIpcOpen
	#define CHK_IpcOpen  (pfIpcOpen != NULL)
	#define EXP_IpcOpen   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcOpen", (RTS_UINTPTR)IpcOpen, 0, 0) 
#endif


RTS_RESULT CDECL IpcClose(RTS_HANDLE hIpc);
typedef RTS_RESULT (CDECL * PFIPCCLOSE) (RTS_HANDLE hIpc);
#if defined(CMPIPC_NOTIMPLEMENTED) || defined(IPCCLOSE_NOTIMPLEMENTED)
	#define USE_IpcClose
	#define EXT_IpcClose
	#define GET_IpcClose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IpcClose(p0) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IpcClose  FALSE
	#define EXP_IpcClose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IpcClose
	#define EXT_IpcClose
	#define GET_IpcClose(fl)  CAL_CMGETAPI( "IpcClose" ) 
	#define CAL_IpcClose  IpcClose
	#define CHK_IpcClose  TRUE
	#define EXP_IpcClose  CAL_CMEXPAPI( "IpcClose" ) 
#elif defined(MIXED_LINK) && !defined(CMPIPC_EXTERNAL)
	#define USE_IpcClose
	#define EXT_IpcClose
	#define GET_IpcClose(fl)  CAL_CMGETAPI( "IpcClose" ) 
	#define CAL_IpcClose  IpcClose
	#define CHK_IpcClose  TRUE
	#define EXP_IpcClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcClose", (RTS_UINTPTR)IpcClose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIpcIpcClose
	#define EXT_CmpIpcIpcClose
	#define GET_CmpIpcIpcClose  ERR_OK
	#define CAL_CmpIpcIpcClose  IpcClose
	#define CHK_CmpIpcIpcClose  TRUE
	#define EXP_CmpIpcIpcClose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IpcClose
	#define EXT_IpcClose
	#define GET_IpcClose(fl)  CAL_CMGETAPI( "IpcClose" ) 
	#define CAL_IpcClose  IpcClose
	#define CHK_IpcClose  TRUE
	#define EXP_IpcClose  CAL_CMEXPAPI( "IpcClose" ) 
#else /* DYNAMIC_LINK */
	#define USE_IpcClose  PFIPCCLOSE pfIpcClose;
	#define EXT_IpcClose  extern PFIPCCLOSE pfIpcClose;
	#define GET_IpcClose(fl)  s_pfCMGetAPI2( "IpcClose", (RTS_VOID_FCTPTR *)&pfIpcClose, (fl), 0, 0)
	#define CAL_IpcClose  pfIpcClose
	#define CHK_IpcClose  (pfIpcClose != NULL)
	#define EXP_IpcClose   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcClose", (RTS_UINTPTR)IpcClose, 0, 0) 
#endif


/**
 * <description> Function that must be called before unregistering callbacks on the server side of an ipc channel.</description>
 * <param name="hIpc" type="IN">Handle to the ipc communcation channel.</param>
 * <result>ERR_OK</result>
 */
RTS_RESULT CDECL IpcStop(RTS_HANDLE hIpc);
typedef RTS_RESULT (CDECL * PFIPCSTOP) (RTS_HANDLE hIpc);
#if defined(CMPIPC_NOTIMPLEMENTED) || defined(IPCSTOP_NOTIMPLEMENTED)
	#define USE_IpcStop
	#define EXT_IpcStop
	#define GET_IpcStop(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IpcStop(p0) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IpcStop  FALSE
	#define EXP_IpcStop  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IpcStop
	#define EXT_IpcStop
	#define GET_IpcStop(fl)  CAL_CMGETAPI( "IpcStop" ) 
	#define CAL_IpcStop  IpcStop
	#define CHK_IpcStop  TRUE
	#define EXP_IpcStop  CAL_CMEXPAPI( "IpcStop" ) 
#elif defined(MIXED_LINK) && !defined(CMPIPC_EXTERNAL)
	#define USE_IpcStop
	#define EXT_IpcStop
	#define GET_IpcStop(fl)  CAL_CMGETAPI( "IpcStop" ) 
	#define CAL_IpcStop  IpcStop
	#define CHK_IpcStop  TRUE
	#define EXP_IpcStop  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcStop", (RTS_UINTPTR)IpcStop, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIpcIpcStop
	#define EXT_CmpIpcIpcStop
	#define GET_CmpIpcIpcStop  ERR_OK
	#define CAL_CmpIpcIpcStop  IpcStop
	#define CHK_CmpIpcIpcStop  TRUE
	#define EXP_CmpIpcIpcStop  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IpcStop
	#define EXT_IpcStop
	#define GET_IpcStop(fl)  CAL_CMGETAPI( "IpcStop" ) 
	#define CAL_IpcStop  IpcStop
	#define CHK_IpcStop  TRUE
	#define EXP_IpcStop  CAL_CMEXPAPI( "IpcStop" ) 
#else /* DYNAMIC_LINK */
	#define USE_IpcStop  PFIPCSTOP pfIpcStop;
	#define EXT_IpcStop  extern PFIPCSTOP pfIpcStop;
	#define GET_IpcStop(fl)  s_pfCMGetAPI2( "IpcStop", (RTS_VOID_FCTPTR *)&pfIpcStop, (fl), 0, 0)
	#define CAL_IpcStop  pfIpcStop
	#define CHK_IpcStop  (pfIpcStop != NULL)
	#define EXP_IpcStop   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcStop", (RTS_UINTPTR)IpcStop, 0, 0) 
#endif


/**
 * <description> Callback function for the ipc-mechanism </description>
 * <param name="hParam" type="IN">Handle to the parameters to this call.</param>
 * <param name="phResultParam" type="OUT">The result of this call, if RTS_INVALID_HANDLE will be set to this parameter, 
 *	than a parameter of type IPC_TYPE_VOID will be returned to the caller. </param>
 * <param name="ulParam" type="IN">The parameter registered in IpcRegisterHandler</param>
 * <result>ERR_OK or ERR_PARAMETER</result>
 */
typedef RTS_RESULT (CDECL *PFIPCHANDLER)(RTS_HANDLE hParam, RTS_HANDLE* phResultParam, RTS_UINTPTR ulParam);

/**
 * <description> Register a handler for a method that should be called via the ipc-mechanism. </description>
 * <param name="hIpc" type="IN">Handle to the IPC-instance</param>
 * <param name="pszMethod" type="IN">Name of the registered method.</param>
 * <param name="pfHandler" type="IN">The callback method.</param>
 * <param name="ulParam" type="IN">A parameter that will be forwarded to each call to pfHandler</param>
 * <result>ERR_OK or ERR_PARAMETER</result>
 */
RTS_RESULT CDECL IpcRegisterHandler(RTS_HANDLE hIpc, char* pszMethod, PFIPCHANDLER pfHandler, RTS_UINTPTR ulParam);
typedef RTS_RESULT (CDECL * PFIPCREGISTERHANDLER) (RTS_HANDLE hIpc, char* pszMethod, PFIPCHANDLER pfHandler, RTS_UINTPTR ulParam);
#if defined(CMPIPC_NOTIMPLEMENTED) || defined(IPCREGISTERHANDLER_NOTIMPLEMENTED)
	#define USE_IpcRegisterHandler
	#define EXT_IpcRegisterHandler
	#define GET_IpcRegisterHandler(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IpcRegisterHandler(p0,p1,p2,p3) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IpcRegisterHandler  FALSE
	#define EXP_IpcRegisterHandler  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IpcRegisterHandler
	#define EXT_IpcRegisterHandler
	#define GET_IpcRegisterHandler(fl)  CAL_CMGETAPI( "IpcRegisterHandler" ) 
	#define CAL_IpcRegisterHandler  IpcRegisterHandler
	#define CHK_IpcRegisterHandler  TRUE
	#define EXP_IpcRegisterHandler  CAL_CMEXPAPI( "IpcRegisterHandler" ) 
#elif defined(MIXED_LINK) && !defined(CMPIPC_EXTERNAL)
	#define USE_IpcRegisterHandler
	#define EXT_IpcRegisterHandler
	#define GET_IpcRegisterHandler(fl)  CAL_CMGETAPI( "IpcRegisterHandler" ) 
	#define CAL_IpcRegisterHandler  IpcRegisterHandler
	#define CHK_IpcRegisterHandler  TRUE
	#define EXP_IpcRegisterHandler  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcRegisterHandler", (RTS_UINTPTR)IpcRegisterHandler, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIpcIpcRegisterHandler
	#define EXT_CmpIpcIpcRegisterHandler
	#define GET_CmpIpcIpcRegisterHandler  ERR_OK
	#define CAL_CmpIpcIpcRegisterHandler  IpcRegisterHandler
	#define CHK_CmpIpcIpcRegisterHandler  TRUE
	#define EXP_CmpIpcIpcRegisterHandler  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IpcRegisterHandler
	#define EXT_IpcRegisterHandler
	#define GET_IpcRegisterHandler(fl)  CAL_CMGETAPI( "IpcRegisterHandler" ) 
	#define CAL_IpcRegisterHandler  IpcRegisterHandler
	#define CHK_IpcRegisterHandler  TRUE
	#define EXP_IpcRegisterHandler  CAL_CMEXPAPI( "IpcRegisterHandler" ) 
#else /* DYNAMIC_LINK */
	#define USE_IpcRegisterHandler  PFIPCREGISTERHANDLER pfIpcRegisterHandler;
	#define EXT_IpcRegisterHandler  extern PFIPCREGISTERHANDLER pfIpcRegisterHandler;
	#define GET_IpcRegisterHandler(fl)  s_pfCMGetAPI2( "IpcRegisterHandler", (RTS_VOID_FCTPTR *)&pfIpcRegisterHandler, (fl), 0, 0)
	#define CAL_IpcRegisterHandler  pfIpcRegisterHandler
	#define CHK_IpcRegisterHandler  (pfIpcRegisterHandler != NULL)
	#define EXP_IpcRegisterHandler   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcRegisterHandler", (RTS_UINTPTR)IpcRegisterHandler, 0, 0) 
#endif


RTS_RESULT CDECL IpcUnregisterHandler(RTS_HANDLE hIpc, char* pszMethod);
typedef RTS_RESULT (CDECL * PFIPCUNREGISTERHANDLER) (RTS_HANDLE hIpc, char* pszMethod);
#if defined(CMPIPC_NOTIMPLEMENTED) || defined(IPCUNREGISTERHANDLER_NOTIMPLEMENTED)
	#define USE_IpcUnregisterHandler
	#define EXT_IpcUnregisterHandler
	#define GET_IpcUnregisterHandler(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IpcUnregisterHandler(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IpcUnregisterHandler  FALSE
	#define EXP_IpcUnregisterHandler  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IpcUnregisterHandler
	#define EXT_IpcUnregisterHandler
	#define GET_IpcUnregisterHandler(fl)  CAL_CMGETAPI( "IpcUnregisterHandler" ) 
	#define CAL_IpcUnregisterHandler  IpcUnregisterHandler
	#define CHK_IpcUnregisterHandler  TRUE
	#define EXP_IpcUnregisterHandler  CAL_CMEXPAPI( "IpcUnregisterHandler" ) 
#elif defined(MIXED_LINK) && !defined(CMPIPC_EXTERNAL)
	#define USE_IpcUnregisterHandler
	#define EXT_IpcUnregisterHandler
	#define GET_IpcUnregisterHandler(fl)  CAL_CMGETAPI( "IpcUnregisterHandler" ) 
	#define CAL_IpcUnregisterHandler  IpcUnregisterHandler
	#define CHK_IpcUnregisterHandler  TRUE
	#define EXP_IpcUnregisterHandler  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcUnregisterHandler", (RTS_UINTPTR)IpcUnregisterHandler, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIpcIpcUnregisterHandler
	#define EXT_CmpIpcIpcUnregisterHandler
	#define GET_CmpIpcIpcUnregisterHandler  ERR_OK
	#define CAL_CmpIpcIpcUnregisterHandler  IpcUnregisterHandler
	#define CHK_CmpIpcIpcUnregisterHandler  TRUE
	#define EXP_CmpIpcIpcUnregisterHandler  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IpcUnregisterHandler
	#define EXT_IpcUnregisterHandler
	#define GET_IpcUnregisterHandler(fl)  CAL_CMGETAPI( "IpcUnregisterHandler" ) 
	#define CAL_IpcUnregisterHandler  IpcUnregisterHandler
	#define CHK_IpcUnregisterHandler  TRUE
	#define EXP_IpcUnregisterHandler  CAL_CMEXPAPI( "IpcUnregisterHandler" ) 
#else /* DYNAMIC_LINK */
	#define USE_IpcUnregisterHandler  PFIPCUNREGISTERHANDLER pfIpcUnregisterHandler;
	#define EXT_IpcUnregisterHandler  extern PFIPCUNREGISTERHANDLER pfIpcUnregisterHandler;
	#define GET_IpcUnregisterHandler(fl)  s_pfCMGetAPI2( "IpcUnregisterHandler", (RTS_VOID_FCTPTR *)&pfIpcUnregisterHandler, (fl), 0, 0)
	#define CAL_IpcUnregisterHandler  pfIpcUnregisterHandler
	#define CHK_IpcUnregisterHandler  (pfIpcUnregisterHandler != NULL)
	#define EXP_IpcUnregisterHandler   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcUnregisterHandler", (RTS_UINTPTR)IpcUnregisterHandler, 0, 0) 
#endif


/**
 * <description> Call a method via the ipc-mechanism. </description>
 * <param name="hIpc" type="IN">Handle to the IPC-instance</param>
 * <param name="pszMethod" type="IN">Name of the method to call.</param>
 * <param name="hParams" type="IN">The parameter that will be used for the call. In case of RTS_INVALID_HANDLE a parameter of type 
 *	IPC_TYPE_VOID will be used for the call. The paramter given here must not be freed after a IpcCall! </param>
 * <param name="phResult" type="OUT">The pointer will recieve the result of the call. 
 *	The paramter returned here must be freed after a IpcCall! </param>
 * <param name="iTimeOutMs" type="IN">The maximal time that will be waited for the return of the call</param>
 * <result>ERR_OK if the call succeeded, ERR_PARAMETER in case of invalid parameters to this call, ERR_TIMOUT if the current call
 *	timed out or ERR_PENDING if the communication channel is still blocked due to a previously timed out call.</result>
 */
RTS_RESULT CDECL IpcCall(RTS_HANDLE hIpc, char* pszMethod, RTS_HANDLE hParams, RTS_HANDLE* phResult, RTS_UI32 iTimeOutMs);
typedef RTS_RESULT (CDECL * PFIPCCALL) (RTS_HANDLE hIpc, char* pszMethod, RTS_HANDLE hParams, RTS_HANDLE* phResult, RTS_UI32 iTimeOutMs);
#if defined(CMPIPC_NOTIMPLEMENTED) || defined(IPCCALL_NOTIMPLEMENTED)
	#define USE_IpcCall
	#define EXT_IpcCall
	#define GET_IpcCall(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IpcCall(p0,p1,p2,p3,p4) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IpcCall  FALSE
	#define EXP_IpcCall  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IpcCall
	#define EXT_IpcCall
	#define GET_IpcCall(fl)  CAL_CMGETAPI( "IpcCall" ) 
	#define CAL_IpcCall  IpcCall
	#define CHK_IpcCall  TRUE
	#define EXP_IpcCall  CAL_CMEXPAPI( "IpcCall" ) 
#elif defined(MIXED_LINK) && !defined(CMPIPC_EXTERNAL)
	#define USE_IpcCall
	#define EXT_IpcCall
	#define GET_IpcCall(fl)  CAL_CMGETAPI( "IpcCall" ) 
	#define CAL_IpcCall  IpcCall
	#define CHK_IpcCall  TRUE
	#define EXP_IpcCall  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcCall", (RTS_UINTPTR)IpcCall, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIpcIpcCall
	#define EXT_CmpIpcIpcCall
	#define GET_CmpIpcIpcCall  ERR_OK
	#define CAL_CmpIpcIpcCall  IpcCall
	#define CHK_CmpIpcIpcCall  TRUE
	#define EXP_CmpIpcIpcCall  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IpcCall
	#define EXT_IpcCall
	#define GET_IpcCall(fl)  CAL_CMGETAPI( "IpcCall" ) 
	#define CAL_IpcCall  IpcCall
	#define CHK_IpcCall  TRUE
	#define EXP_IpcCall  CAL_CMEXPAPI( "IpcCall" ) 
#else /* DYNAMIC_LINK */
	#define USE_IpcCall  PFIPCCALL pfIpcCall;
	#define EXT_IpcCall  extern PFIPCCALL pfIpcCall;
	#define GET_IpcCall(fl)  s_pfCMGetAPI2( "IpcCall", (RTS_VOID_FCTPTR *)&pfIpcCall, (fl), 0, 0)
	#define CAL_IpcCall  pfIpcCall
	#define CHK_IpcCall  (pfIpcCall != NULL)
	#define EXP_IpcCall   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcCall", (RTS_UINTPTR)IpcCall, 0, 0) 
#endif


/**
 * <description> This function creates a new parameter and returns a handle to it. </description>
 * <param name="pszName" type="IN">Optional name of the parameter, may be NULL if no name is needed. </param>
 * <param name="phResult" type="OUT">Pointer that will recieve the created parameter. </param>
 * <result>ERR_OK or ERR_PARAMETER</result>
 */
RTS_RESULT CDECL IpcCreateParam(char* pszName, RTS_HANDLE* phResult);
typedef RTS_RESULT (CDECL * PFIPCCREATEPARAM) (char* pszName, RTS_HANDLE* phResult);
#if defined(CMPIPC_NOTIMPLEMENTED) || defined(IPCCREATEPARAM_NOTIMPLEMENTED)
	#define USE_IpcCreateParam
	#define EXT_IpcCreateParam
	#define GET_IpcCreateParam(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IpcCreateParam(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IpcCreateParam  FALSE
	#define EXP_IpcCreateParam  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IpcCreateParam
	#define EXT_IpcCreateParam
	#define GET_IpcCreateParam(fl)  CAL_CMGETAPI( "IpcCreateParam" ) 
	#define CAL_IpcCreateParam  IpcCreateParam
	#define CHK_IpcCreateParam  TRUE
	#define EXP_IpcCreateParam  CAL_CMEXPAPI( "IpcCreateParam" ) 
#elif defined(MIXED_LINK) && !defined(CMPIPC_EXTERNAL)
	#define USE_IpcCreateParam
	#define EXT_IpcCreateParam
	#define GET_IpcCreateParam(fl)  CAL_CMGETAPI( "IpcCreateParam" ) 
	#define CAL_IpcCreateParam  IpcCreateParam
	#define CHK_IpcCreateParam  TRUE
	#define EXP_IpcCreateParam  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcCreateParam", (RTS_UINTPTR)IpcCreateParam, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIpcIpcCreateParam
	#define EXT_CmpIpcIpcCreateParam
	#define GET_CmpIpcIpcCreateParam  ERR_OK
	#define CAL_CmpIpcIpcCreateParam  IpcCreateParam
	#define CHK_CmpIpcIpcCreateParam  TRUE
	#define EXP_CmpIpcIpcCreateParam  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IpcCreateParam
	#define EXT_IpcCreateParam
	#define GET_IpcCreateParam(fl)  CAL_CMGETAPI( "IpcCreateParam" ) 
	#define CAL_IpcCreateParam  IpcCreateParam
	#define CHK_IpcCreateParam  TRUE
	#define EXP_IpcCreateParam  CAL_CMEXPAPI( "IpcCreateParam" ) 
#else /* DYNAMIC_LINK */
	#define USE_IpcCreateParam  PFIPCCREATEPARAM pfIpcCreateParam;
	#define EXT_IpcCreateParam  extern PFIPCCREATEPARAM pfIpcCreateParam;
	#define GET_IpcCreateParam(fl)  s_pfCMGetAPI2( "IpcCreateParam", (RTS_VOID_FCTPTR *)&pfIpcCreateParam, (fl), 0, 0)
	#define CAL_IpcCreateParam  pfIpcCreateParam
	#define CHK_IpcCreateParam  (pfIpcCreateParam != NULL)
	#define EXP_IpcCreateParam   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcCreateParam", (RTS_UINTPTR)IpcCreateParam, 0, 0) 
#endif


/**
 * <description> This function destroys a parameter. </description>
 * <param name="hParam" type="IN">Handle to the parameter.</param>
 * <result>ERR_OK or ERR_PARAMETER</result>
 */
RTS_RESULT CDECL IpcFreeParam(RTS_HANDLE hParam);
typedef RTS_RESULT (CDECL * PFIPCFREEPARAM) (RTS_HANDLE hParam);
#if defined(CMPIPC_NOTIMPLEMENTED) || defined(IPCFREEPARAM_NOTIMPLEMENTED)
	#define USE_IpcFreeParam
	#define EXT_IpcFreeParam
	#define GET_IpcFreeParam(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IpcFreeParam(p0) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IpcFreeParam  FALSE
	#define EXP_IpcFreeParam  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IpcFreeParam
	#define EXT_IpcFreeParam
	#define GET_IpcFreeParam(fl)  CAL_CMGETAPI( "IpcFreeParam" ) 
	#define CAL_IpcFreeParam  IpcFreeParam
	#define CHK_IpcFreeParam  TRUE
	#define EXP_IpcFreeParam  CAL_CMEXPAPI( "IpcFreeParam" ) 
#elif defined(MIXED_LINK) && !defined(CMPIPC_EXTERNAL)
	#define USE_IpcFreeParam
	#define EXT_IpcFreeParam
	#define GET_IpcFreeParam(fl)  CAL_CMGETAPI( "IpcFreeParam" ) 
	#define CAL_IpcFreeParam  IpcFreeParam
	#define CHK_IpcFreeParam  TRUE
	#define EXP_IpcFreeParam  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcFreeParam", (RTS_UINTPTR)IpcFreeParam, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIpcIpcFreeParam
	#define EXT_CmpIpcIpcFreeParam
	#define GET_CmpIpcIpcFreeParam  ERR_OK
	#define CAL_CmpIpcIpcFreeParam  IpcFreeParam
	#define CHK_CmpIpcIpcFreeParam  TRUE
	#define EXP_CmpIpcIpcFreeParam  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IpcFreeParam
	#define EXT_IpcFreeParam
	#define GET_IpcFreeParam(fl)  CAL_CMGETAPI( "IpcFreeParam" ) 
	#define CAL_IpcFreeParam  IpcFreeParam
	#define CHK_IpcFreeParam  TRUE
	#define EXP_IpcFreeParam  CAL_CMEXPAPI( "IpcFreeParam" ) 
#else /* DYNAMIC_LINK */
	#define USE_IpcFreeParam  PFIPCFREEPARAM pfIpcFreeParam;
	#define EXT_IpcFreeParam  extern PFIPCFREEPARAM pfIpcFreeParam;
	#define GET_IpcFreeParam(fl)  s_pfCMGetAPI2( "IpcFreeParam", (RTS_VOID_FCTPTR *)&pfIpcFreeParam, (fl), 0, 0)
	#define CAL_IpcFreeParam  pfIpcFreeParam
	#define CHK_IpcFreeParam  (pfIpcFreeParam != NULL)
	#define EXP_IpcFreeParam   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcFreeParam", (RTS_UINTPTR)IpcFreeParam, 0, 0) 
#endif


#define IPC_TYPE_VOID			0
#define IPC_TYPE_DWORD			1
#define IPC_TYPE_BOOLEAN		2
#define IPC_TYPE_STRING			3
#define IPC_TYPE_BINARY			4
#define IPC_TYPE_STRUCTURED		100

/**
 * <description> This function sets the value in a parameter. If you call this function on a structured parameter, then all members of 
 *	the structure will be freed, so they may not be access afterwards. </description>
 * <param name="iType" type="IN">The type of the given value, one of the IPC_TYPE_... constants without IPC_TYPE_STRUCTURED.</param>
 * <param name="iSize" type="IN">This parameter is only needed for types with an unknown size ie. strings or binary. </param>
 * <param name="pData" type="OUT">Pointer to the data of the value to set. This data will be copied, so it can be deleted after the call. </param>
 * <result>ERR_OK or ERR_PARAMETER</result>
 */
RTS_RESULT CDECL IpcParamSetValue(RTS_HANDLE hParam, RTS_I32 iType, RTS_SIZE iSize, void* pData);
typedef RTS_RESULT (CDECL * PFIPCPARAMSETVALUE) (RTS_HANDLE hParam, RTS_I32 iType, RTS_SIZE iSize, void* pData);
#if defined(CMPIPC_NOTIMPLEMENTED) || defined(IPCPARAMSETVALUE_NOTIMPLEMENTED)
	#define USE_IpcParamSetValue
	#define EXT_IpcParamSetValue
	#define GET_IpcParamSetValue(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IpcParamSetValue(p0,p1,p2,p3) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IpcParamSetValue  FALSE
	#define EXP_IpcParamSetValue  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IpcParamSetValue
	#define EXT_IpcParamSetValue
	#define GET_IpcParamSetValue(fl)  CAL_CMGETAPI( "IpcParamSetValue" ) 
	#define CAL_IpcParamSetValue  IpcParamSetValue
	#define CHK_IpcParamSetValue  TRUE
	#define EXP_IpcParamSetValue  CAL_CMEXPAPI( "IpcParamSetValue" ) 
#elif defined(MIXED_LINK) && !defined(CMPIPC_EXTERNAL)
	#define USE_IpcParamSetValue
	#define EXT_IpcParamSetValue
	#define GET_IpcParamSetValue(fl)  CAL_CMGETAPI( "IpcParamSetValue" ) 
	#define CAL_IpcParamSetValue  IpcParamSetValue
	#define CHK_IpcParamSetValue  TRUE
	#define EXP_IpcParamSetValue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcParamSetValue", (RTS_UINTPTR)IpcParamSetValue, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIpcIpcParamSetValue
	#define EXT_CmpIpcIpcParamSetValue
	#define GET_CmpIpcIpcParamSetValue  ERR_OK
	#define CAL_CmpIpcIpcParamSetValue  IpcParamSetValue
	#define CHK_CmpIpcIpcParamSetValue  TRUE
	#define EXP_CmpIpcIpcParamSetValue  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IpcParamSetValue
	#define EXT_IpcParamSetValue
	#define GET_IpcParamSetValue(fl)  CAL_CMGETAPI( "IpcParamSetValue" ) 
	#define CAL_IpcParamSetValue  IpcParamSetValue
	#define CHK_IpcParamSetValue  TRUE
	#define EXP_IpcParamSetValue  CAL_CMEXPAPI( "IpcParamSetValue" ) 
#else /* DYNAMIC_LINK */
	#define USE_IpcParamSetValue  PFIPCPARAMSETVALUE pfIpcParamSetValue;
	#define EXT_IpcParamSetValue  extern PFIPCPARAMSETVALUE pfIpcParamSetValue;
	#define GET_IpcParamSetValue(fl)  s_pfCMGetAPI2( "IpcParamSetValue", (RTS_VOID_FCTPTR *)&pfIpcParamSetValue, (fl), 0, 0)
	#define CAL_IpcParamSetValue  pfIpcParamSetValue
	#define CHK_IpcParamSetValue  (pfIpcParamSetValue != NULL)
	#define EXP_IpcParamSetValue   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcParamSetValue", (RTS_UINTPTR)IpcParamSetValue, 0, 0) 
#endif


/**
 * <description> This function returns the value of a parameter. The value will be copied to the buffer pointed
 *	to by pBuffer. </description>
 * <param name="hParam" type="IN">Handle to the parameter</param>
 * <param name="piSize" type="INOUT">Pointer to a int that contains the size of the buffer as an IN-param, 
 *	and after the call will contain the size of the used buffer as an OUT-param. For Types with fixed sizes
 *	like IPC_TYPE_BOOLEAN or IPC_TYPE_DWORD this parameter may be NULL. </param>
 * <param name="pBuffer" type="IN">Buffer where the data should be copied to. If NULL, only the size will be returned.  </param>
 * <result>ERR_OK or ERR_PARAMETER or ERR_NOBUFFER, if the given size of pBuffer is too small</result>
 */
RTS_RESULT CDECL IpcParamGetValue(RTS_HANDLE hParam, RTS_SIZE* piSize, void* pBuffer);
typedef RTS_RESULT (CDECL * PFIPCPARAMGETVALUE) (RTS_HANDLE hParam, RTS_SIZE* piSize, void* pBuffer);
#if defined(CMPIPC_NOTIMPLEMENTED) || defined(IPCPARAMGETVALUE_NOTIMPLEMENTED)
	#define USE_IpcParamGetValue
	#define EXT_IpcParamGetValue
	#define GET_IpcParamGetValue(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IpcParamGetValue(p0,p1,p2) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IpcParamGetValue  FALSE
	#define EXP_IpcParamGetValue  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IpcParamGetValue
	#define EXT_IpcParamGetValue
	#define GET_IpcParamGetValue(fl)  CAL_CMGETAPI( "IpcParamGetValue" ) 
	#define CAL_IpcParamGetValue  IpcParamGetValue
	#define CHK_IpcParamGetValue  TRUE
	#define EXP_IpcParamGetValue  CAL_CMEXPAPI( "IpcParamGetValue" ) 
#elif defined(MIXED_LINK) && !defined(CMPIPC_EXTERNAL)
	#define USE_IpcParamGetValue
	#define EXT_IpcParamGetValue
	#define GET_IpcParamGetValue(fl)  CAL_CMGETAPI( "IpcParamGetValue" ) 
	#define CAL_IpcParamGetValue  IpcParamGetValue
	#define CHK_IpcParamGetValue  TRUE
	#define EXP_IpcParamGetValue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcParamGetValue", (RTS_UINTPTR)IpcParamGetValue, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIpcIpcParamGetValue
	#define EXT_CmpIpcIpcParamGetValue
	#define GET_CmpIpcIpcParamGetValue  ERR_OK
	#define CAL_CmpIpcIpcParamGetValue  IpcParamGetValue
	#define CHK_CmpIpcIpcParamGetValue  TRUE
	#define EXP_CmpIpcIpcParamGetValue  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IpcParamGetValue
	#define EXT_IpcParamGetValue
	#define GET_IpcParamGetValue(fl)  CAL_CMGETAPI( "IpcParamGetValue" ) 
	#define CAL_IpcParamGetValue  IpcParamGetValue
	#define CHK_IpcParamGetValue  TRUE
	#define EXP_IpcParamGetValue  CAL_CMEXPAPI( "IpcParamGetValue" ) 
#else /* DYNAMIC_LINK */
	#define USE_IpcParamGetValue  PFIPCPARAMGETVALUE pfIpcParamGetValue;
	#define EXT_IpcParamGetValue  extern PFIPCPARAMGETVALUE pfIpcParamGetValue;
	#define GET_IpcParamGetValue(fl)  s_pfCMGetAPI2( "IpcParamGetValue", (RTS_VOID_FCTPTR *)&pfIpcParamGetValue, (fl), 0, 0)
	#define CAL_IpcParamGetValue  pfIpcParamGetValue
	#define CHK_IpcParamGetValue  (pfIpcParamGetValue != NULL)
	#define EXP_IpcParamGetValue   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcParamGetValue", (RTS_UINTPTR)IpcParamGetValue, 0, 0) 
#endif


/**
 * <description> This function retrieves the value of a parameter. </description>
 * <param name="hParam" type="IN">Handle to the parameter</param>
 * <param name="ppszName" type="OUT">Pointer to a c-string. This string will return the name. It will never be NULL! </param>
 * <result>ERR_OK or ERR_PARAMETER</result>
 */
RTS_RESULT CDECL IpcParamGetName(RTS_HANDLE hParam, char** ppszName);
typedef RTS_RESULT (CDECL * PFIPCPARAMGETNAME) (RTS_HANDLE hParam, char** ppszName);
#if defined(CMPIPC_NOTIMPLEMENTED) || defined(IPCPARAMGETNAME_NOTIMPLEMENTED)
	#define USE_IpcParamGetName
	#define EXT_IpcParamGetName
	#define GET_IpcParamGetName(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IpcParamGetName(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IpcParamGetName  FALSE
	#define EXP_IpcParamGetName  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IpcParamGetName
	#define EXT_IpcParamGetName
	#define GET_IpcParamGetName(fl)  CAL_CMGETAPI( "IpcParamGetName" ) 
	#define CAL_IpcParamGetName  IpcParamGetName
	#define CHK_IpcParamGetName  TRUE
	#define EXP_IpcParamGetName  CAL_CMEXPAPI( "IpcParamGetName" ) 
#elif defined(MIXED_LINK) && !defined(CMPIPC_EXTERNAL)
	#define USE_IpcParamGetName
	#define EXT_IpcParamGetName
	#define GET_IpcParamGetName(fl)  CAL_CMGETAPI( "IpcParamGetName" ) 
	#define CAL_IpcParamGetName  IpcParamGetName
	#define CHK_IpcParamGetName  TRUE
	#define EXP_IpcParamGetName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcParamGetName", (RTS_UINTPTR)IpcParamGetName, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIpcIpcParamGetName
	#define EXT_CmpIpcIpcParamGetName
	#define GET_CmpIpcIpcParamGetName  ERR_OK
	#define CAL_CmpIpcIpcParamGetName  IpcParamGetName
	#define CHK_CmpIpcIpcParamGetName  TRUE
	#define EXP_CmpIpcIpcParamGetName  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IpcParamGetName
	#define EXT_IpcParamGetName
	#define GET_IpcParamGetName(fl)  CAL_CMGETAPI( "IpcParamGetName" ) 
	#define CAL_IpcParamGetName  IpcParamGetName
	#define CHK_IpcParamGetName  TRUE
	#define EXP_IpcParamGetName  CAL_CMEXPAPI( "IpcParamGetName" ) 
#else /* DYNAMIC_LINK */
	#define USE_IpcParamGetName  PFIPCPARAMGETNAME pfIpcParamGetName;
	#define EXT_IpcParamGetName  extern PFIPCPARAMGETNAME pfIpcParamGetName;
	#define GET_IpcParamGetName(fl)  s_pfCMGetAPI2( "IpcParamGetName", (RTS_VOID_FCTPTR *)&pfIpcParamGetName, (fl), 0, 0)
	#define CAL_IpcParamGetName  pfIpcParamGetName
	#define CHK_IpcParamGetName  (pfIpcParamGetName != NULL)
	#define EXP_IpcParamGetName   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcParamGetName", (RTS_UINTPTR)IpcParamGetName, 0, 0) 
#endif


/**
 * <description> This function returns the type of a given parameter. </description>
 * <param name="hParam" type="IN">Handle to the parameter</param>
 * <param name="piType" type="OUT">Pointer that will recieve the type of this parameter as one of the IPC_TYPE_... values. </param>
 * <result>ERR_OK or ERR_PARAMETER</result>
 */
RTS_RESULT CDECL IpcParamGetType(RTS_HANDLE hParam, RTS_I32* piType);
typedef RTS_RESULT (CDECL * PFIPCPARAMGETTYPE) (RTS_HANDLE hParam, RTS_I32* piType);
#if defined(CMPIPC_NOTIMPLEMENTED) || defined(IPCPARAMGETTYPE_NOTIMPLEMENTED)
	#define USE_IpcParamGetType
	#define EXT_IpcParamGetType
	#define GET_IpcParamGetType(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IpcParamGetType(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IpcParamGetType  FALSE
	#define EXP_IpcParamGetType  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IpcParamGetType
	#define EXT_IpcParamGetType
	#define GET_IpcParamGetType(fl)  CAL_CMGETAPI( "IpcParamGetType" ) 
	#define CAL_IpcParamGetType  IpcParamGetType
	#define CHK_IpcParamGetType  TRUE
	#define EXP_IpcParamGetType  CAL_CMEXPAPI( "IpcParamGetType" ) 
#elif defined(MIXED_LINK) && !defined(CMPIPC_EXTERNAL)
	#define USE_IpcParamGetType
	#define EXT_IpcParamGetType
	#define GET_IpcParamGetType(fl)  CAL_CMGETAPI( "IpcParamGetType" ) 
	#define CAL_IpcParamGetType  IpcParamGetType
	#define CHK_IpcParamGetType  TRUE
	#define EXP_IpcParamGetType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcParamGetType", (RTS_UINTPTR)IpcParamGetType, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIpcIpcParamGetType
	#define EXT_CmpIpcIpcParamGetType
	#define GET_CmpIpcIpcParamGetType  ERR_OK
	#define CAL_CmpIpcIpcParamGetType  IpcParamGetType
	#define CHK_CmpIpcIpcParamGetType  TRUE
	#define EXP_CmpIpcIpcParamGetType  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IpcParamGetType
	#define EXT_IpcParamGetType
	#define GET_IpcParamGetType(fl)  CAL_CMGETAPI( "IpcParamGetType" ) 
	#define CAL_IpcParamGetType  IpcParamGetType
	#define CHK_IpcParamGetType  TRUE
	#define EXP_IpcParamGetType  CAL_CMEXPAPI( "IpcParamGetType" ) 
#else /* DYNAMIC_LINK */
	#define USE_IpcParamGetType  PFIPCPARAMGETTYPE pfIpcParamGetType;
	#define EXT_IpcParamGetType  extern PFIPCPARAMGETTYPE pfIpcParamGetType;
	#define GET_IpcParamGetType(fl)  s_pfCMGetAPI2( "IpcParamGetType", (RTS_VOID_FCTPTR *)&pfIpcParamGetType, (fl), 0, 0)
	#define CAL_IpcParamGetType  pfIpcParamGetType
	#define CHK_IpcParamGetType  (pfIpcParamGetType != NULL)
	#define EXP_IpcParamGetType   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcParamGetType", (RTS_UINTPTR)IpcParamGetType, 0, 0) 
#endif


RTS_RESULT CDECL IpcParamAddMember(RTS_HANDLE hParam, RTS_HANDLE hParamMember);
typedef RTS_RESULT (CDECL * PFIPCPARAMADDMEMBER) (RTS_HANDLE hParam, RTS_HANDLE hParamMember);
#if defined(CMPIPC_NOTIMPLEMENTED) || defined(IPCPARAMADDMEMBER_NOTIMPLEMENTED)
	#define USE_IpcParamAddMember
	#define EXT_IpcParamAddMember
	#define GET_IpcParamAddMember(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IpcParamAddMember(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IpcParamAddMember  FALSE
	#define EXP_IpcParamAddMember  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IpcParamAddMember
	#define EXT_IpcParamAddMember
	#define GET_IpcParamAddMember(fl)  CAL_CMGETAPI( "IpcParamAddMember" ) 
	#define CAL_IpcParamAddMember  IpcParamAddMember
	#define CHK_IpcParamAddMember  TRUE
	#define EXP_IpcParamAddMember  CAL_CMEXPAPI( "IpcParamAddMember" ) 
#elif defined(MIXED_LINK) && !defined(CMPIPC_EXTERNAL)
	#define USE_IpcParamAddMember
	#define EXT_IpcParamAddMember
	#define GET_IpcParamAddMember(fl)  CAL_CMGETAPI( "IpcParamAddMember" ) 
	#define CAL_IpcParamAddMember  IpcParamAddMember
	#define CHK_IpcParamAddMember  TRUE
	#define EXP_IpcParamAddMember  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcParamAddMember", (RTS_UINTPTR)IpcParamAddMember, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIpcIpcParamAddMember
	#define EXT_CmpIpcIpcParamAddMember
	#define GET_CmpIpcIpcParamAddMember  ERR_OK
	#define CAL_CmpIpcIpcParamAddMember  IpcParamAddMember
	#define CHK_CmpIpcIpcParamAddMember  TRUE
	#define EXP_CmpIpcIpcParamAddMember  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IpcParamAddMember
	#define EXT_IpcParamAddMember
	#define GET_IpcParamAddMember(fl)  CAL_CMGETAPI( "IpcParamAddMember" ) 
	#define CAL_IpcParamAddMember  IpcParamAddMember
	#define CHK_IpcParamAddMember  TRUE
	#define EXP_IpcParamAddMember  CAL_CMEXPAPI( "IpcParamAddMember" ) 
#else /* DYNAMIC_LINK */
	#define USE_IpcParamAddMember  PFIPCPARAMADDMEMBER pfIpcParamAddMember;
	#define EXT_IpcParamAddMember  extern PFIPCPARAMADDMEMBER pfIpcParamAddMember;
	#define GET_IpcParamAddMember(fl)  s_pfCMGetAPI2( "IpcParamAddMember", (RTS_VOID_FCTPTR *)&pfIpcParamAddMember, (fl), 0, 0)
	#define CAL_IpcParamAddMember  pfIpcParamAddMember
	#define CHK_IpcParamAddMember  (pfIpcParamAddMember != NULL)
	#define EXP_IpcParamAddMember   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcParamAddMember", (RTS_UINTPTR)IpcParamAddMember, 0, 0) 
#endif


RTS_RESULT CDECL IpcParamGetMemberCount(RTS_HANDLE hParam, RTS_I32* piCount);
typedef RTS_RESULT (CDECL * PFIPCPARAMGETMEMBERCOUNT) (RTS_HANDLE hParam, RTS_I32* piCount);
#if defined(CMPIPC_NOTIMPLEMENTED) || defined(IPCPARAMGETMEMBERCOUNT_NOTIMPLEMENTED)
	#define USE_IpcParamGetMemberCount
	#define EXT_IpcParamGetMemberCount
	#define GET_IpcParamGetMemberCount(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IpcParamGetMemberCount(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IpcParamGetMemberCount  FALSE
	#define EXP_IpcParamGetMemberCount  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IpcParamGetMemberCount
	#define EXT_IpcParamGetMemberCount
	#define GET_IpcParamGetMemberCount(fl)  CAL_CMGETAPI( "IpcParamGetMemberCount" ) 
	#define CAL_IpcParamGetMemberCount  IpcParamGetMemberCount
	#define CHK_IpcParamGetMemberCount  TRUE
	#define EXP_IpcParamGetMemberCount  CAL_CMEXPAPI( "IpcParamGetMemberCount" ) 
#elif defined(MIXED_LINK) && !defined(CMPIPC_EXTERNAL)
	#define USE_IpcParamGetMemberCount
	#define EXT_IpcParamGetMemberCount
	#define GET_IpcParamGetMemberCount(fl)  CAL_CMGETAPI( "IpcParamGetMemberCount" ) 
	#define CAL_IpcParamGetMemberCount  IpcParamGetMemberCount
	#define CHK_IpcParamGetMemberCount  TRUE
	#define EXP_IpcParamGetMemberCount  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcParamGetMemberCount", (RTS_UINTPTR)IpcParamGetMemberCount, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIpcIpcParamGetMemberCount
	#define EXT_CmpIpcIpcParamGetMemberCount
	#define GET_CmpIpcIpcParamGetMemberCount  ERR_OK
	#define CAL_CmpIpcIpcParamGetMemberCount  IpcParamGetMemberCount
	#define CHK_CmpIpcIpcParamGetMemberCount  TRUE
	#define EXP_CmpIpcIpcParamGetMemberCount  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IpcParamGetMemberCount
	#define EXT_IpcParamGetMemberCount
	#define GET_IpcParamGetMemberCount(fl)  CAL_CMGETAPI( "IpcParamGetMemberCount" ) 
	#define CAL_IpcParamGetMemberCount  IpcParamGetMemberCount
	#define CHK_IpcParamGetMemberCount  TRUE
	#define EXP_IpcParamGetMemberCount  CAL_CMEXPAPI( "IpcParamGetMemberCount" ) 
#else /* DYNAMIC_LINK */
	#define USE_IpcParamGetMemberCount  PFIPCPARAMGETMEMBERCOUNT pfIpcParamGetMemberCount;
	#define EXT_IpcParamGetMemberCount  extern PFIPCPARAMGETMEMBERCOUNT pfIpcParamGetMemberCount;
	#define GET_IpcParamGetMemberCount(fl)  s_pfCMGetAPI2( "IpcParamGetMemberCount", (RTS_VOID_FCTPTR *)&pfIpcParamGetMemberCount, (fl), 0, 0)
	#define CAL_IpcParamGetMemberCount  pfIpcParamGetMemberCount
	#define CHK_IpcParamGetMemberCount  (pfIpcParamGetMemberCount != NULL)
	#define EXP_IpcParamGetMemberCount   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcParamGetMemberCount", (RTS_UINTPTR)IpcParamGetMemberCount, 0, 0) 
#endif


RTS_RESULT CDECL IpcParamGetMember(RTS_HANDLE hParam, RTS_I32 iNumber, RTS_HANDLE* phParamMember);
typedef RTS_RESULT (CDECL * PFIPCPARAMGETMEMBER) (RTS_HANDLE hParam, RTS_I32 iNumber, RTS_HANDLE* phParamMember);
#if defined(CMPIPC_NOTIMPLEMENTED) || defined(IPCPARAMGETMEMBER_NOTIMPLEMENTED)
	#define USE_IpcParamGetMember
	#define EXT_IpcParamGetMember
	#define GET_IpcParamGetMember(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IpcParamGetMember(p0,p1,p2) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IpcParamGetMember  FALSE
	#define EXP_IpcParamGetMember  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IpcParamGetMember
	#define EXT_IpcParamGetMember
	#define GET_IpcParamGetMember(fl)  CAL_CMGETAPI( "IpcParamGetMember" ) 
	#define CAL_IpcParamGetMember  IpcParamGetMember
	#define CHK_IpcParamGetMember  TRUE
	#define EXP_IpcParamGetMember  CAL_CMEXPAPI( "IpcParamGetMember" ) 
#elif defined(MIXED_LINK) && !defined(CMPIPC_EXTERNAL)
	#define USE_IpcParamGetMember
	#define EXT_IpcParamGetMember
	#define GET_IpcParamGetMember(fl)  CAL_CMGETAPI( "IpcParamGetMember" ) 
	#define CAL_IpcParamGetMember  IpcParamGetMember
	#define CHK_IpcParamGetMember  TRUE
	#define EXP_IpcParamGetMember  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcParamGetMember", (RTS_UINTPTR)IpcParamGetMember, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIpcIpcParamGetMember
	#define EXT_CmpIpcIpcParamGetMember
	#define GET_CmpIpcIpcParamGetMember  ERR_OK
	#define CAL_CmpIpcIpcParamGetMember  IpcParamGetMember
	#define CHK_CmpIpcIpcParamGetMember  TRUE
	#define EXP_CmpIpcIpcParamGetMember  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IpcParamGetMember
	#define EXT_IpcParamGetMember
	#define GET_IpcParamGetMember(fl)  CAL_CMGETAPI( "IpcParamGetMember" ) 
	#define CAL_IpcParamGetMember  IpcParamGetMember
	#define CHK_IpcParamGetMember  TRUE
	#define EXP_IpcParamGetMember  CAL_CMEXPAPI( "IpcParamGetMember" ) 
#else /* DYNAMIC_LINK */
	#define USE_IpcParamGetMember  PFIPCPARAMGETMEMBER pfIpcParamGetMember;
	#define EXT_IpcParamGetMember  extern PFIPCPARAMGETMEMBER pfIpcParamGetMember;
	#define GET_IpcParamGetMember(fl)  s_pfCMGetAPI2( "IpcParamGetMember", (RTS_VOID_FCTPTR *)&pfIpcParamGetMember, (fl), 0, 0)
	#define CAL_IpcParamGetMember  pfIpcParamGetMember
	#define CHK_IpcParamGetMember  (pfIpcParamGetMember != NULL)
	#define EXP_IpcParamGetMember   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IpcParamGetMember", (RTS_UINTPTR)IpcParamGetMember, 0, 0) 
#endif


#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
} ICmpIpc_C;

#ifdef CPLUSPLUS
class ICmpIpc : public IBase
{
	public:
};
	#ifndef ITF_CmpIpc
		#define ITF_CmpIpc static ICmpIpc *pICmpIpc = NULL;
	#endif
	#define EXTITF_CmpIpc
#else	/*CPLUSPLUS*/
	typedef ICmpIpc_C		ICmpIpc;
	#ifndef ITF_CmpIpc
		#define ITF_CmpIpc
	#endif
	#define EXTITF_CmpIpc
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPIPCITF_H_*/
