/**
 * <interfacename>SysModule</interfacename>
 * <description> 
 *	<p>The SysModule interface is projected to handle component modules. This interface is only
 *	available on systems, that supports dynamically loading and unloading modules.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysModule')

#include "CmpStd.h"

#ifndef CDECL
	#define CDECL
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysModuleOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysModuleOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>
 *	Load a specified module
 * </description>
 * <param name="pszModuleName" type="IN">Pointer to the module name.
 *	NOTE: Module names MUST NOT include	operating system specific endings (e.g. .dll, .o, etc.)</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the loaded module or RTS_INVALID_HANDLE if failed.</result>
 */
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysModuleLoad',`(char *pszModuleName, RTS_RESULT *pResult)')

/**
 * <description>
 * Load a specified module
 * </description>
 * <param name="pszModuleName" type="IN">Pointer to the module name.
 * NOTE:
 * Module names must _NOT_ include operating system specific endings (e.g. .dll, .o, etc.)</param>
 * <param name="pszModuleFileName" type="IN">Pointer to the module file name.
 * NOTE:
 * Module names _must_ include operating system specific endings (e.g. .dll, .o, etc.) and optional the path of the file!</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Module could be loaded</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Failed to load module</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter (pszModuleName = NULL/empty or pszModuleFileName = NULL/empty)</errorcode>
 * <result>Handle to the loaded module or RTS_INVALID_HANDLE if failed</result>
 */
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysModuleLoad2',`(char *pszModuleName, char *pszModuleFileName, RTS_RESULT *pResult)') 

/**
 * <description>
 *	Unload a module
 * </description>
 * <param name="hModule" type="IN">Handle to the module</param>
 * <result>error code</result>
 */
DEF_DELETEITF_API(`RTS_RESULT',`CDECL',`SysModuleUnload',`(RTS_HANDLE hModule)')

/**
 * <description>
 *	Returns a function pointer of the routine in the module specified by name. 
 * </description>
 * <param name="hModule" type="IN">Handle to the module</param>
 * <param name="pszFctName" type="IN">Pointer to the function name</param>
 * <param name="ppFunction" type="OUT">Pointer to function pointer or NULL, if function is not available in the 
 *	specified module</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysModuleGetFunctionPointer',`(RTS_HANDLE hModule, char *pszFctName, void **ppFunction)')

#ifdef __cplusplus
}
#endif
