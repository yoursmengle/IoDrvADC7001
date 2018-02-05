/**
 * <interfacename>SysModRTMain</interfacename>
 * <description> 
 *
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */
 
SET_INTERFACE_NAME(`SysModRTMain')

REF_ITF(`SysFlashItf.m4')
REF_ITF(`SysTimeItf.m4')
REF_ITF(`SysModRTSubItf.m4')

#include "CmpItf.h"

/**
 * <category>Static defines</category>
 * <description>Memory address of SysModRTMainFunctionTable</description>
 */
#ifndef MODRTMAIN_FUNCTION_TABLE_ADDRESS
	#error MODRTMAIN_FUNCTION_TABLE_ADDRESS not defined!!
#endif


/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	PFSYSFLASHERASE pfSysFlashErase;
	PFSYSFLASHWRITE pfSysFlashWrite;
	PFSYSFLASHFLUSH pfSysFlashFlush;
	PFSYSTIMEGETMS pfSysTimeGetMs;
	PFSYSTIMEGETUS pfSysTimeGetUs;
	PFSYSTIMEGETNS pfSysTimeGetNs;
} SysModRTMainFunctionTable;

/* no functions to export */


/** EXTERN LIB SECTION END **/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif
