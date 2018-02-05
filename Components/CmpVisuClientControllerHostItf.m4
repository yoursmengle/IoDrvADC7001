/**
 * <interfacename>CmpVisuClientControllerHost</interfacename>
 * <description> 
 *	Interface for the visu client controller host.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpVisuClientControllerHost')


/**
 * <category>Settings</category>
 * <description> The ipc base name of the visu client controller
 * IMPORTANT: The according visu client controller must have configured the same basename ! </description>
 */
#define CMPVISUCLIENTCONTROLLERSTUB_KEY_IPCBASENAME				"IpcBasename"
#define CMPVISUCLIENTCONTROLLERSTUB_KEY_IPCBASENAME_DEFAULT		"Ipc__VisuClientController__"

/**
 * <description> Function to register the visu client controller host. </description>
 * <param name="pszApplication" type="IN">The target visualization application</param>
 * <param name="pHandleRet" type="OUT">The created handle.</param>
 * <result>error code</result>
 */	
DEF_API(`RTS_RESULT', `CDECL', `VisuClientControllerHostCreateInstance', `(char* pszApplication, RTS_HANDLE* pHandleRet)')

/**
 * <description> Function to release a formerly registered visu client controller host. </description>
 * <param name="hInstance" type="IN">The instance that should be released.</param>
 * <result>error code</result>
 */	
DEF_API(`RTS_RESULT', `CDECL', `VisuClientControllerHostDestroyInstance', `(RTS_HANDLE hInstance)')

