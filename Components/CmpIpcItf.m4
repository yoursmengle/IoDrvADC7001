/**
 * <interfacename>CmpIpc</interfacename>
 * <description> 
 *	Interface of the inter process communication component.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpIpc')

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

DEF_API(`RTS_RESULT',`CDECL',`IpcOpen',`(char* pszName, RTS_HANDLE* phReturn)')

DEF_API(`RTS_RESULT',`CDECL',`IpcClose',`(RTS_HANDLE hIpc)')

/**
 * <description> Function that must be called before unregistering callbacks on the server side of an ipc channel.</description>
 * <param name="hIpc" type="IN">Handle to the ipc communcation channel.</param>
 * <result>ERR_OK</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`IpcStop',`(RTS_HANDLE hIpc)')

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
DEF_API(`RTS_RESULT',`CDECL',`IpcRegisterHandler',`(RTS_HANDLE hIpc, char* pszMethod, PFIPCHANDLER pfHandler, RTS_UINTPTR ulParam)')

DEF_API(`RTS_RESULT',`CDECL',`IpcUnregisterHandler',`(RTS_HANDLE hIpc, char* pszMethod)')

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
DEF_API(`RTS_RESULT',`CDECL',`IpcCall',`(RTS_HANDLE hIpc, char* pszMethod, RTS_HANDLE hParams, RTS_HANDLE* phResult, RTS_UI32 iTimeOutMs)')

/**
 * <description> This function creates a new parameter and returns a handle to it. </description>
 * <param name="pszName" type="IN">Optional name of the parameter, may be NULL if no name is needed. </param>
 * <param name="phResult" type="OUT">Pointer that will recieve the created parameter. </param>
 * <result>ERR_OK or ERR_PARAMETER</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`IpcCreateParam',`(char* pszName, RTS_HANDLE* phResult)')

/**
 * <description> This function destroys a parameter. </description>
 * <param name="hParam" type="IN">Handle to the parameter.</param>
 * <result>ERR_OK or ERR_PARAMETER</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`IpcFreeParam',`(RTS_HANDLE hParam)')

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
DEF_API(`RTS_RESULT',`CDECL',`IpcParamSetValue',`(RTS_HANDLE hParam, RTS_I32 iType, RTS_SIZE iSize, void* pData)')

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
DEF_API(`RTS_RESULT',`CDECL',`IpcParamGetValue',`(RTS_HANDLE hParam, RTS_SIZE* piSize, void* pBuffer)')

/**
 * <description> This function retrieves the value of a parameter. </description>
 * <param name="hParam" type="IN">Handle to the parameter</param>
 * <param name="ppszName" type="OUT">Pointer to a c-string. This string will return the name. It will never be NULL! </param>
 * <result>ERR_OK or ERR_PARAMETER</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`IpcParamGetName',`(RTS_HANDLE hParam, char** ppszName)')

/**
 * <description> This function returns the type of a given parameter. </description>
 * <param name="hParam" type="IN">Handle to the parameter</param>
 * <param name="piType" type="OUT">Pointer that will recieve the type of this parameter as one of the IPC_TYPE_... values. </param>
 * <result>ERR_OK or ERR_PARAMETER</result>
 */
DEF_API(`RTS_RESULT',`CDECL',`IpcParamGetType',`(RTS_HANDLE hParam, RTS_I32* piType)')

DEF_API(`RTS_RESULT',`CDECL',`IpcParamAddMember',`(RTS_HANDLE hParam, RTS_HANDLE hParamMember)')

DEF_API(`RTS_RESULT',`CDECL',`IpcParamGetMemberCount',`(RTS_HANDLE hParam, RTS_I32* piCount)')

DEF_API(`RTS_RESULT',`CDECL',`IpcParamGetMember',`(RTS_HANDLE hParam, RTS_I32 iNumber, RTS_HANDLE* phParamMember)')

#ifdef __cplusplus
}
#endif
