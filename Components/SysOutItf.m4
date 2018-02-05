/**
 * <interfacename>SysOut</interfacename>
 * <description> 
 *	<p>The SysOut interface is projected to get access to the console output routines. This
 *	can be used for debugging or logging needs.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysOut')

#include "CmpStd.h"

#ifndef CDECL
	#define CDECL
#endif


#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysOutOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysOutOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>Function to print out a formatted string on the standard console output</description>
 * <param name="szFormat" type="IN">Format string with optional arguments</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysOutPrintf',`(char *szFormat, ...)')

/**
 * <description>Function to print out an argument list on the standard console output</description>
 * <param name="szFormat" type="IN">Format string</param>
 * <param name="pargList" type="IN">Pointer to argument list for the format string</param>
 * <result>error code</result>
 */
#define SysOutPrintfArg		SysOutVPrintf
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysOutVPrintf',`(char *szFormat, va_list *pargList)')

/**
 * <description>
 *	Debug output fo a formatted string on the standard console output.
 *	NOTE: Actual time should be added in front of each debug output string
 * </description>
 * <param name="szFormat" type="IN">Format string with optional arguments</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysOutDebug',`(char *szFormat, ...)')

/**
 * <description>
 *	Debug output of an argument list on the standard console output.
 *	NOTE: Actual time should be added in front of each debug output string
 * </description>
 * <param name="szFormat" type="IN">Format string</param>
 * <param name="pargList" type="IN">Pointer to argument list for the format string</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysOutDebugArg',`(char *szFormat, va_list *pargList)')

/**
 * <description>Checkpoints for debugging needs. Prints the actual file and line number</description>
 */
#ifndef CPT
	#define CPT				SysOutDebug("%s checkpoint at line %d\n", __FILE__, __LINE__);
#endif
#ifndef CPTPRINTF
	#define CPTPRINTF		("%s checkpoint at line %d\n", __FILE__, __LINE__);
#endif

#ifdef __cplusplus
}
#endif
