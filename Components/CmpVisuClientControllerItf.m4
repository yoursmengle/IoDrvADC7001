/**
 * <interfacename>CmpVisuClientController</interfacename>
 * <description> 
 *	Interface for the visu client controller.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpVisuClientController')

/**
 * <category>Settings</category>
 * <description>The basename for the ipcchannel.
 *	IMPORTANT: The according visuclientcontroller must have configured the same basename ! </description>
 */
#define CMPVISUCLIENTCONTROLLER_KEY_TARGETVISUPROCESS_IPCBASENAME				"IpcBasename"
#define CMPVISUCLIENTCONTROLLER_KEY_TARGETVISUPROCESS_IPCBASENAME_DEFAULT		"Ipc__VisuClientController__"

/**
 * <category>Settings</category>
 * <description>Setting that decides about the timeout that is used for single ipccalls </description>
 */
#define CMPVISUCLIENTCONTROLLER_KEY_IPCTIMEOUT				"IpcTimeoutMs"
#define CMPVISUCLIENTCONTROLLER_KEY_IPCTIMEOUT_DEFAULT		INT32_C(5000)

/**
 * <category>Settings</category>
 * <description>The basename of the sharedmemory. Will be followed by the externid of the specific client.
 * IMPORTANT: The according visualization must have configured the same basename ! </description>
 */
#define CMPVISUCLIENTCONTROLLER_KEY_TARGETVISUPROCESS_SHMBASENAME				"SharedMemoryBasename"
#define CMPVISUCLIENTCONTROLLER_KEY_TARGETVISUPROCESS_SHMBASENAME_DEFAULT		"SHM_EXTERN_VISUCLIENTCONTROLLER_"


/**
 * <description> Function to register the visu client controller host. </description>
 * <param name="pszAppName" type="IN">The target visualization application</param>
 * <param name="dwFlags" type="IN">The flags if the visu client should be created or destoyed.</param>
 * <result>error code</result>
 */	
DEF_API(`RTS_RESULT', `CDECL', `VisuClientControllerSendRequest', `(char* pszAppName, RTS_IEC_DWORD dwFlags)')

