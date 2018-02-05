/**
 * <interfacename>SysTime</interfacename>
 * <description>
 * <p>The SysTime interface is projected to get access to time tick values with 
 * different resolutions (millisecond, microsecond, nanosecond).</p>
 * <p>All different ticks are wrapping around their natural data type limits
 * (RTS_UI32 or RTS_SYSTIME). Therefore, they can be used to measure
 * difference timings. They can't either be used to measure absolute timings
 * nor can they be calculated from one to each other.</p>
 * <p>Implementation Notes:</p>
 * <ul>
 *   <li>All three different timers need their own handling of wrap arounds,
 *   because they have a wrap around at different points in time at different
 *   boundaries. In practice, this implies the need for an own, static offset
 *   counter for every timer.</li>
 *   <li>If the timer is based on a periodic interrupt (e.g. millisecond tick),
 *   it works only as long as no interrupt lock is held. This might be the
 *   case in some flash drivers for example.</li>
 *   <li>Some timers are called very regularly. So if the wrap around of the
 *   timer source itself is very late (low frequency + large timer register),
 *   it might be enough for the system to detect timer overruns only at every
 *   call.</li>
 * </ul>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysTime')

#include "CmpStd.h"

#ifndef CDECL
	#define CDECL
#endif

#if !defined(_RTS_SYSTIME)
	#define _RTS_SYSTIME
	typedef RTS_UI64			RTS_SYSTIME;
	#define RTS_SYSTIME_MAX		(~((RTS_SYSTIME)0))
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Setting to specify a threshold for the jump distance from one call to GetPerformanceCounterValue to the next.</description>
 */
#define SYSTIMEKEY_INT_WINCE_TIME_PERFORMANCE_COUNTER_THRESHOLD			"WinCE.MaxDistancePC"
#define SYSTIMEVALUE_INT_TIME_PERFORMANCE_COUNTER_THRESHOLD				0

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Setting to specify whether SysTimeGetMs under Windows CE should take the time from the scheduler ticks.</description>
 */
#define SYSTIMEKEY_INT_WINCE_TIME_MS_FROM_SCHEDULER						"WinCE.GetMsTimeFromSchedulerTicks"
#define SYSTIMEVALUE_INT_WINCE_TIME_MS_FROM_SCHEDULER					0

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting to specify a customerspecific function for SysTimeGetUs (VxWorks only).</description>
 */
#define SYSTIMEKEY_INT_VXWORKS_CUSTOMSYSTIMEGETUS				"VxWorks.CustomSysTimeGetUs"
#define SYSTIMEVALUE_INT_VXWORKS_CUSTOMSYSTIMEGETUS				""

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting to specify a customerspecific function for SysTimeGetNs (VxWorks only).</description>
 */
#define SYSTIMEKEY_INT_VXWORKS_CUSTOMSYSTIMEGETNS				"VxWorks.CustomSysTimeGetNs"
#define SYSTIMEVALUE_INT_VXWORKS_CUSTOMSYSTIMEGETNS				""


/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <SIL2/>
 * Returns a monotonic rising millisecond tick. This tick can be used for timeout and
 * relative time measurements.
 * NOTE: The realtime clock is not influencing this tick!
 * RETURN: Returns the millisecond tick
 */
typedef struct tagsystimegetms_struct
{
	RTS_IEC_UDINT SysTimeGetMs;			/* VAR_OUTPUT */	
} systimegetms_struct;

DEF_API(`void',`CDECL',`systimegetms',`(systimegetms_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x9306CA2B),0x03050500)

/**
 * <SIL2/>
 * Returns a monotonic rising nanosecond tick. This tick can be used for very high
 * resolution time measurements
 * NOTE: The realtime clock does not influences this tick!
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsystimegetns_struct
{
	RTS_IEC_ULINT *pUsTime;				/* VAR_IN_OUT */	/* Time tick result in nanoseconds */
	RTS_IEC_RESULT SysTimeGetNs;		/* VAR_OUTPUT */	
} systimegetns_struct;

DEF_API(`void',`CDECL',`systimegetns',`(systimegetns_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x7EED4E09),0x03050500)

/**
 * <SIL2/>
 * Returns a monotonic rising microsecond tick. This tick can be used for timeout and
 * high resolution time measurements.
 * NOTE: The realtime clock does not influences this tick!
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsystimegetus_struct
{
	RTS_IEC_ULINT *pUsTime;				/* VAR_IN_OUT */	/* Time tick result in microseconds */
	RTS_IEC_RESULT SysTimeGetUs;		/* VAR_OUTPUT */	
} systimegetus_struct;

DEF_API(`void',`CDECL',`systimegetus',`(systimegetus_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x6C6308BF),0x03050500)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysTimeOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysTimeOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>
 * <p>Return a monotonic, rising millisecond tick.</p>
 * </description> 
 * <result>Returns the millisecond tick</result>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`SysTimeGetMs',`(void)')

/**
 * <description>
 * <p>Return a monotonic, rising microsecond tick.</p>
 * </description>
 * <param name="pTime" type="INOUT" range="[NULL,VALID_PTIME]">Pointer to the time tick result</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Time was returned successfully</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">pTime was NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Internal Error</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysTimeGetUs',`(RTS_SYSTIME* pTime)')

/**
 * <description>
 * <p>Return a monotonic, rising nanosecond tick.</p>
 * </description>
 * <param name="pTime" type="INOUT" range="[NULL,VALID_PTIME]">Pointer to the time tick result</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Time was returned successfully</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">pTime was NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Internal Error</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysTimeGetNs',`(RTS_SYSTIME* pTime)')

#ifdef __cplusplus
}
#endif
