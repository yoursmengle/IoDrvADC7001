 /**
 * <interfacename>SysModRTMain</interfacename>
 * <description> 
 *
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */
 

	
	
#ifndef _SYSMODRTMAINITF_H_
#define _SYSMODRTMAINITF_H_

#include "CmpStd.h"

 

 




#include "SysFlashItf.h"
#include "SysTimeItf.h"
#include "SysModRTSubItf.h"

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



typedef struct
{
	IBase_C *pBase;
} ISysModRTMain_C;

#ifdef CPLUSPLUS
class ISysModRTMain : public IBase
{
	public:
};
	#ifndef ITF_SysModRTMain
		#define ITF_SysModRTMain static ISysModRTMain *pISysModRTMain = NULL;
	#endif
	#define EXTITF_SysModRTMain
#else	/*CPLUSPLUS*/
	typedef ISysModRTMain_C		ISysModRTMain;
	#ifndef ITF_SysModRTMain
		#define ITF_SysModRTMain
	#endif
	#define EXTITF_SysModRTMain
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSMODRTMAINITF_H_*/
