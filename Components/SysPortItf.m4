/**
 * <interfacename>SysPort</interfacename>
 * <description> 
 *	<p>The SysPort interface is projected to get direct access to hardware devices by port access</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysPort')

#include "CmpItf.h"


/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>This function reads the current BYTE-value at the given port address.</description>
 * <result><p>RESULT: Input port value that was read.</p></result>
 */
typedef struct tagsysportin_struct
{
	RTS_IEC_UDINT ulAddress;			/* VAR_INPUT */	/* <param name="ulAddress" type="IN">Port address</param> */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library)</param> */
	RTS_IEC_BYTE SysPortIn;				/* VAR_OUTPUT */	
} sysportin_struct;

DEF_API(`void',`CDECL',`sysportin',`(sysportin_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD23F618E),0x03050500)

/**
 * <description>This function reads the current UDINT-value at the given port address.</description>
 * <result><p>RESULT: Input port value that was read.</p></result>
 */
typedef struct tagsysportind_struct
{
	RTS_IEC_UDINT ulAddress;			/* VAR_INPUT */	/* <param name="ulAddress" type="IN">Port address</param> */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library)</param> */
	RTS_IEC_UDINT SysPortInD;			/* VAR_OUTPUT */	
} sysportind_struct;

DEF_API(`void',`CDECL',`sysportind',`(sysportind_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x40C580DD),0x03050500)

/**
 * <description>This function reads the current WORD-value at the given port address.</description>
 * <result><p>RESULT: Input port value that was read.</p></result>
 */
typedef struct tagsysportinw_struct
{
	RTS_IEC_UDINT ulAddress;			/* VAR_INPUT */	/* <param name="ulAddress" type="IN">Port address</param> */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library)</param> */
	RTS_IEC_WORD SysPortInW;			/* VAR_OUTPUT */	
} sysportinw_struct;

DEF_API(`void',`CDECL',`sysportinw',`(sysportinw_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x8D4FCB60),0x03050500)

/**
 * <description>This function writes the specified BYTE-value on the certain port address.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysportout_struct
{
	RTS_IEC_UDINT ulAddress;			/* VAR_INPUT */	/* <param name="ulAddress" type="IN">Port address</param> */
	RTS_IEC_BYTE byVal;					/* VAR_INPUT */	/* <param name="byVal" type="IN">Value to be written to the port.</param> */
	RTS_IEC_RESULT SysPortOut;			/* VAR_OUTPUT */	
} sysportout_struct;

DEF_API(`void',`CDECL',`sysportout',`(sysportout_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x8A8205C9),0x03050500)

/**
 * <description>This function writes the specified UDINT-value on the certain port address.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysportoutd_struct
{
	RTS_IEC_UDINT ulAddress;			/* VAR_INPUT */	/* <param name="ulAddress" type="IN">Port address</param> */
	RTS_IEC_UDINT udVal;				/* VAR_INPUT */	/* <param name="udVal" type="IN">Value to be written to the port.</param> */
	RTS_IEC_RESULT SysPortOutD;			/* VAR_OUTPUT */	
} sysportoutd_struct;

DEF_API(`void',`CDECL',`sysportoutd',`(sysportoutd_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB129E67D),0x03050500)

/**
 * <description>This function writes the specified WORD-value on the certain port address.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysportoutw_struct
{
	RTS_IEC_UDINT ulAddress;			/* VAR_INPUT */	/* <param name="ulAddress" type="IN">Port address</param> */
	RTS_IEC_WORD usVal;					/* VAR_INPUT */	/* <param name="usVal" type="IN">Value to be written to the port.</param> */
	RTS_IEC_RESULT SysPortOutW;			/* VAR_OUTPUT */	
} sysportoutw_struct;

DEF_API(`void',`CDECL',`sysportoutw',`(sysportoutw_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x19126DF2),0x03050500)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysPortOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysPortOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description> Function to read in a device port </description>
 * <param name="ulAddress" type="IN">Port address</param>
 * <param name="pResult" type="OUT">Result</param>
 * <result>input port value</result>
 */
DEF_ITF_API(`RTS_UI8',`CDECL',`SysPortIn',`(RTS_UI32 ulAddress, RTS_RESULT *pResult)')

/**
 * <description> Function to read in a device port </description>
 * <param name="ulAddress" type="IN">Port address</param>
 * <param name="pResult" type="OUT">Result</param>
 * <result>input port value</result>
 */
DEF_ITF_API(`RTS_UI16',`CDECL',`SysPortInW',`(RTS_UI32 ulAddress, RTS_RESULT *pResult)')

/**
 * <description> Function to read in a device port </description>
 * <param name="ulAddress" type="IN">Port address</param>
 * <param name="pResult" type="OUT">Result</param>
 * <result>input port value</result>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`SysPortInD',`(RTS_UI32 ulAddress, RTS_RESULT *pResult)')

/**
 * <description> Function to write a value to a device port </description>
 * <param name="ulAddress" type="IN">Port address</param>
 * <param name="byValue" type="IN">Value</param>
 * <result>ERR_OK</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysPortOut',`(RTS_UI32 ulAddress, RTS_UI8 byValue)')

/**
 * <description> Function to write a value to a device port </description>
 * <param name="ulAddress" type="IN">Port address</param>
 * <param name="wValue" type="IN">Value</param>
 * <result>ERR_OK</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysPortOutW',`(RTS_UI32 ulAddress, RTS_UI16 usValue)')

/**
 * <description> Function to write a value to a device port </description>
 * <param name="ulAddress" type="IN">Port address</param>
 * <param name="dwValue" type="IN">Value</param>
 * <result>ERR_OK</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysPortOutD',`(RTS_UI32 ulAddress, RTS_UI32 ulValue)')

#ifdef __cplusplus
}
#endif
