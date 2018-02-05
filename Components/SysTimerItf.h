 /**
 * <interfacename>SysTimer</interfacename>
 * <description> 
 *	<p>The SysTimer interface is projected to access timer devices on target.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _SYSTIMERITF_H_
#define _SYSTIMERITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "SysTimeItf.h"

/**
 * <category>Timer error codes</category>
 * <description> Possible Error codes:
 * TIMER_NO_ERROR
 * TIMER_HANDLE_INVALID
 * TIMER_SYS_SPEC_ERROR
 * TIMER_MANUF_SPEC_ERROR
 * </description>
 */
#define		TIMER_NO_ERROR			0x0000
#define		TIMER_HANDLE_INVALID	0x0001
#define		TIMER_SYS_SPEC_ERROR	0x3FFF
#define		TIMER_MANUF_SPEC_ERROR	0x7FFF

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>
 *	Timer callback interface
 * </description>
 * <param name="hParam" type="IN" range="[RTS_INVALID_HANDLE,VALID_HPARAM]">Parameter handle</param>
 * <result></result>
 */
typedef void HUGEPTR(CDECL *PFTIMERCALLBACK)(RTS_HANDLE hParam);

typedef struct
{
	RTS_IEC_HANDLE hParam;
	RTS_IEC_RESULT SysTimerCallback;
} systimercallback_struct;


/**
 * <description>
 *	Timer exception callback interface
 * </description>
 * <param name="hTimerHandle" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERHANDLE]">Handle of the assigned timer</param>
 * <param name="ulException" type="IN" range="[RTS_RANGE_OF_ULONG]">Exception number</param>
 * <param name="Context" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_CONTEXT]">Register context of the exception</param>
 * <result></result>
 */
typedef RTS_RESULT (CDECL *PFTIMEREXCEPTIONHANDLER)(RTS_HANDLE hTimerHandle, RTS_UI32 ulException, RegContext Context);

/**
 * <category>Timer type</category>
 * <description>
 * Possible type of a Timer:
 * RTS_TIMER_NONE: Not Defined
 * RTS_TIMER_PERIODIC: Periodical timer
 * RTS_TIMER_ONESHOT: Oneshot timer
 * </description>
 */
#define RTS_TIMER_NONE			0
#define RTS_TIMER_PERIODIC		1
#define RTS_TIMER_ONESHOT		2

/*Info of SchedTimer. Only used for TimerScheduler*/
#define TI_STARTED			0x0001
#define TI_ACTIVE			0x0002
#define	TI_RESETFOLLOW		0x0004
#define TI_INITIALIZED		0x0008
#define TI_WATCHDOG			0x0020
#define TI_BREAKPOINT		0x0040

#define TimerIsWatchdog(pTimerInfo)			(((SYS_TIMER_INFO*)pTimerInfo)->iState & TI_WATCHDOG)
#define TimerSetWatchdog(pTimerInfo)		(((SYS_TIMER_INFO*)pTimerInfo)->iState |= TI_WATCHDOG)
#define TimerResetWatchdog(pTimerInfo)		(((SYS_TIMER_INFO*)pTimerInfo)->iState &= ~TI_WATCHDOG)

#define TimerResetFollow(pTimerInfo)		(((SYS_TIMER_INFO*)pTimerInfo)->iState & TI_RESETFOLLOW)
#define TimerSetResetFollow(pTimerInfo)		(((SYS_TIMER_INFO*)pTimerInfo)->iState |= TI_RESETFOLLOW)
#define TimerResetResetFollow(pTimerInfo)	(((SYS_TIMER_INFO*)pTimerInfo)->iState &= ~TI_RESETFOLLOW)

#define TimerIsActive(pTimerInfo)			(((SYS_TIMER_INFO*)pTimerInfo)->iState & TI_ACTIVE)
#define TimerSetActive(pTimerInfo)			(((SYS_TIMER_INFO*)pTimerInfo)->iState |= TI_ACTIVE)
#define TimerResetActive(pTimerInfo)		(((SYS_TIMER_INFO*)pTimerInfo)->iState &= ~TI_ACTIVE)

/* Deprecated macro, only for backward compatibility */
#define TimerSetStarted(pTimerInfo)			(((SYS_TIMER_INFO*)pTimerInfo)->iState |= TI_STARTED)
/* Deprecated macro, only for backward compatibility */
#define TimerResetStarted(pTimerInfo)		(((SYS_TIMER_INFO*)pTimerInfo)->iState &= ~TI_STARTED)

#define TimerIsStarted(pTimerInfo)			(((SYS_TIMER_INFO*)pTimerInfo)->iState & TI_STARTED)
#define TimerSetStart(pTimerInfo)			(((SYS_TIMER_INFO*)pTimerInfo)->iState |= TI_STARTED)
#define TimerIsStopped(pTimerInfo)			(~(((SYS_TIMER_INFO*)pTimerInfo)->iState & TI_STARTED))
#define TimerSetStop(pTimerInfo)			(((SYS_TIMER_INFO*)pTimerInfo)->iState &= ~TI_STARTED)

#define TimerOnBP(pTimerInfo)				(((SYS_TIMER_INFO*)pTimerInfo)->iState & TI_BREAKPOINT)
#define TimerSetOnBP(pTimerInfo)			(((SYS_TIMER_INFO*)pTimerInfo)->iState |= TI_BREAKPOINT)
#define TimerResetOnBP(pTimerInfo)			(((SYS_TIMER_INFO*)pTimerInfo)->iState &= ~TI_BREAKPOINT)

#define TimerIsInit(pTimerInfo)		(((SYS_TIMER_INFO*)pTimerInfo)->iState & TI_INITIALIZED)
#define TimerSetInit(pTimerInfo)			(((SYS_TIMER_INFO*)pTimerInfo)->iState |= TI_INITIALIZED)
#define TimerResetInit(pTimerInfo)			(((SYS_TIMER_INFO*)pTimerInfo)->iState &= ~TI_INITIALIZED)


/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 * Setting to get timer (schedule) tick:
 * Auxiliary: AuxiliaryClock is used
 * System: SystemClock is used
 * Task: A high priority task is used
 * </description>
 */
#define SYSTIMERKEY_STRING_VXWORKS_TIMERSOURCE                  "VxWorks.TimerSource"
#define SYSTIMERVALUE_STRING_VXWORKS_TIMERSOURCE_AUXILIARY      "Auxiliary"
#define SYSTIMERVALUE_STRING_VXWORKS_TIMERSOURCE_SYSTEM         "System"
#define SYSTIMERVALUE_STRING_VXWORKS_TIMERSOURCE_TASK           "Task"
#ifndef SYSTIMERVALUE_STRING_VXWORKS_TIMERSOURCE_DEFAULT
  #define SYSTIMERVALUE_STRING_VXWORKS_TIMERSOURCE_DEFAULT      SYSTIMERVALUE_STRING_VXWORKS_TIMERSOURCE_TASK
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 * Setting to set the timer mode:
 * Periodic: Use a periodic HW Timer, which is programmed once.
 * OneShot: Use a one shot timer, which is reprogrammed on every tick.
 * </description>
 */
#define SYSTIMERKEY_STRING_VXWORKS_TIMERMODE                   "VxWorks.TimerMode"
#define SYSTIMERVALUE_STRING_VXWORKS_TIMERMODE_PERIODIC        "Periodic"
#define SYSTIMERVALUE_STRING_VXWORKS_TIMERMODE_ONESHOT         "OneShot"
#ifndef SYSTIMERVALUE_STRING_VXWORKS_TIMERMODE_DEFAULT
  #define SYSTIMERVALUE_STRING_VXWORKS_TIMERMODE_DEFAULT       SYSTIMERVALUE_STRING_VXWORKS_TIMERMODE_PERIODIC
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 * Setting to get timer tick:
 * SysInt: Interrupt latency time measurement IRQ is used
 * IRQ: An interrupt is used
 * Multimedia: The multimedia timer is used
 * </description>
 */
#define SYSTIMERKEY_STRING_WINCE_TIMERSOURCE					"WinCE.TimerSource"
#define SYSTIMERVALUE_STRING_WINCE_TIMERSOURCE_SYSINT	        "SysInt"
#define SYSTIMERVALUE_STRING_WINCE_TIMERSOURCE_INTERRUPT        "IRQ"
#define SYSTIMERVALUE_STRING_WINCE_TIMERSOURCE_MULTIMEDIA       "Multimedia"
#define SYSTIMERVALUE_STRING_WINCE_TIMERSOURCE_THREADWAITTILLTICK "ThreadWaitTillTick"
#define SYSTIMERVALUE_STRING_WINCE_TIMERSOURCE_DEFAULT			SYSTIMERVALUE_STRING_WINCE_TIMERSOURCE_MULTIMEDIA

 
/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Setting to specify the timer. A timer with this priority should use the settings with the same index.</description>
 */
#define SYSTIMERKEY_INT_WINCE_TIMERPRIORITY							"WinCE.Priority"
#define SYSTIMERVALUE_INT_WINCE_TIMER_DEFAULT_PRIORITY				0

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Setting to ignore wrong return values of HalTimingEnable. Only for WinCE and in very exceptional cases.</description>
 */
#define SYSTIMERKEY_INT_WINCE_IGNORE_FAILURE_OFIOCTRL_HALTIMING_ENABLE	"WinCE.IgnoreFailureOfIoCtrlHalTimingEnable"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * Setting to get the interrupt number of the timer tick interrupt. Only used for WinCE.
 * </description>
 */
#define SYSTIMERKEY_INT_WINCE_TIMER_IRQNUMBER							"WinCE.IRQNumber"
#define SYSTIMERVALUE_INT_WINCE_TIMER_DEFAULT_IRQNUMBER	0

/**
 * <category>Static defines</category>
 * <description>Maximum number of timers</description>
 */
#ifndef SYSTIMER_NUM_OF_STATIC_TIMER
	#define SYSTIMER_NUM_OF_STATIC_TIMER	2
#endif

/**
 * <category>Static defines</category>
 * <description>Maximum number of timer priorities</description>
 */
#ifndef SYSTIMER_NUM_OF_TIMER_PRIOS
	#define SYSTIMER_NUM_OF_TIMER_PRIOS	256
#endif

typedef struct
{
	RTS_UINTPTR			ulReturnBP;
	RTS_UINTPTR			ulReturnPC;
} SYS_TIMER_CALL_CONTEXT;

typedef struct
{
	RTS_UINTPTR			ulOnBP;
	RTS_UINTPTR			ulSPOnBreakpoint;
	RTS_UINTPTR			ulBPOnBreakpoint;
	/*ToDo: Add Data/Address Registers*/
} SYS_TIMER_BP_CONTEXT;

/**
 * <category>Timer info structure</category>
 * <description>
 *	Timer information structure that contains all information for the SysTimerOS implementation to handle one sepcific timer object.
 * </description>
 * <element name="pfTimerCallback" type="IN">Function pointer to the timer callback, that must be executed in the timer event</element>
 * <element name="pfExceptionHandler" type="IN">Function pointer to an exception handler, that must be called, if an exception occurred in the corresponding timer callback function</element>
 * <element name="hParam" type="IN">Handle to a parameter, that must be transmitted as a parameter for the callback routine!</element>
 * <element name="hSysTimer" type="IN">Handle to the system timer object in the OS implementation</element>
 * <element name="hTimerToReset" type="IN">SysTimer handle to the next timer that mast be activated at the return code of the actual timer callback</element>
 * <element name="tIntervalNs" type="IN">Interval of the timer in nanoseconds</element>
 * <element name="tStartTime" type="IN">Start time of the timer event, when the callback is called</element>
 * <element name="tLastExecuteNs" type="IN">Last execution time of the timer</element>
 * <element name="ulType" type="IN">Timer type. See corresponding category.</element>
 * <element name="ulPriority" type="IN">Piority of the timer object. Typically between [0..SYSTIMER_NUM_OF_TIMER_PRIOS - 1]: 0=highest prio, 255=lowest prio</element>
 * <element name="tCallContext" type="IN">Actual register context of the calling callback. Can be used to make a context switch.</element>
 * <element name="tBPContext" type="IN">Actual register context of the actual breakpoint position</element>
 * <element name="bIECFunction" type="IN">Flag to mark, if callback function is an IEC function</element>
 * <element name="iState" type="IN">Actual state of the timer object</element>
 * <element name="hParam" type="IN">Optional event to wake up the callback routine (task). This event is delivered in SysTimerCreateEvent.</element>
 * <element name="ulIRQ" type="IN">Interrupt number of the corresponding timer object</element>
 * <element name="pSEHContextHead" type="IN">Points to the head of the registered exception frames</element>
 */
typedef struct
{
	PFTIMERCALLBACK				pTimerCallback;
	PFTIMEREXCEPTIONHANDLER		pExceptionHandler;
	RTS_HANDLE					hParam;
	RTS_HANDLE					hSysTimer;
	RTS_HANDLE					hTimerToReset;
	RTS_SYSTIME					tIntervalNs; 
	RTS_SYSTIME					tStartTime;
	RTS_SYSTIME					tLastExecuteNs;
	unsigned long				ulType;
	unsigned long				ulPriority;
	SYS_TIMER_CALL_CONTEXT		tCallContext;
	SYS_TIMER_BP_CONTEXT		tBPContext;
	int							bIECFunction;
	int							iState;
	RTS_HANDLE					hEvent;
	unsigned long				ulIRQ;
	SEHContext 				*pSEHContextHead;
#ifdef CPLUSPLUS
	void *pCppInstance;
#endif
} SYS_TIMER_INFO;

#ifdef __cplusplus
}
#endif


/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>This function creates a new timer and calls a callback function.</description>
 * <result><p>RESULT: Handle of the timer or RTS_INVALID_HANDLE if failed</p></result>
 */
typedef struct tagsystimercreatecallback_struct
{
	PFTIMERCALLBACK pfTimerCallback;	/* VAR_INPUT */	/* <param name="pfTimerCallback" type="IN">Pointer to a callback function</param> */
	RTS_IEC_HANDLE hParam;				/* VAR_INPUT */	/* <param name="hParam" type="IN">Parameter for callback routine</param> */
	RTS_IEC_ULINT tIntervalNs;			/* VAR_INPUT */	/* <param name="tIntervalNs" type="IN">Interval of the timer (timebase = 1 ns)</param> */
	RTS_IEC_UDINT ulPriority;			/* VAR_INPUT */	/* <param name="ulPriority" type="IN">Priority of the timer object</param> */
	PFTIMEREXCEPTIONHANDLER pfExceptionHandler;	/* VAR_INPUT */	/* <param name="pfExceptionHandler" type="IN">Pointer to an optional exception handler. Can be NULL.</param> */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library)</param> */
	RTS_IEC_HANDLE SysTimerCreateCallback;	/* VAR_OUTPUT */	
} systimercreatecallback_struct;

void CDECL CDECL_EXT systimercreatecallback(systimercreatecallback_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTIMERCREATECALLBACK_IEC) (systimercreatecallback_struct *p);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERCREATECALLBACK_NOTIMPLEMENTED)
	#define USE_systimercreatecallback
	#define EXT_systimercreatecallback
	#define GET_systimercreatecallback(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systimercreatecallback(p0) 
	#define CHK_systimercreatecallback  FALSE
	#define EXP_systimercreatecallback  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systimercreatecallback
	#define EXT_systimercreatecallback
	#define GET_systimercreatecallback(fl)  CAL_CMGETAPI( "systimercreatecallback" ) 
	#define CAL_systimercreatecallback  systimercreatecallback
	#define CHK_systimercreatecallback  TRUE
	#define EXP_systimercreatecallback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimercreatecallback", (RTS_UINTPTR)systimercreatecallback, 1, 0xE5D4A503, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_systimercreatecallback
	#define EXT_systimercreatecallback
	#define GET_systimercreatecallback(fl)  CAL_CMGETAPI( "systimercreatecallback" ) 
	#define CAL_systimercreatecallback  systimercreatecallback
	#define CHK_systimercreatecallback  TRUE
	#define EXP_systimercreatecallback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimercreatecallback", (RTS_UINTPTR)systimercreatecallback, 1, 0xE5D4A503, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimersystimercreatecallback
	#define EXT_SysTimersystimercreatecallback
	#define GET_SysTimersystimercreatecallback  ERR_OK
	#define CAL_SysTimersystimercreatecallback  systimercreatecallback
	#define CHK_SysTimersystimercreatecallback  TRUE
	#define EXP_SysTimersystimercreatecallback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimercreatecallback", (RTS_UINTPTR)systimercreatecallback, 1, 0xE5D4A503, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systimercreatecallback
	#define EXT_systimercreatecallback
	#define GET_systimercreatecallback(fl)  CAL_CMGETAPI( "systimercreatecallback" ) 
	#define CAL_systimercreatecallback  systimercreatecallback
	#define CHK_systimercreatecallback  TRUE
	#define EXP_systimercreatecallback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimercreatecallback", (RTS_UINTPTR)systimercreatecallback, 1, 0xE5D4A503, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systimercreatecallback  PFSYSTIMERCREATECALLBACK_IEC pfsystimercreatecallback;
	#define EXT_systimercreatecallback  extern PFSYSTIMERCREATECALLBACK_IEC pfsystimercreatecallback;
	#define GET_systimercreatecallback(fl)  s_pfCMGetAPI2( "systimercreatecallback", (RTS_VOID_FCTPTR *)&pfsystimercreatecallback, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xE5D4A503, 0x03050500)
	#define CAL_systimercreatecallback  pfsystimercreatecallback
	#define CHK_systimercreatecallback  (pfsystimercreatecallback != NULL)
	#define EXP_systimercreatecallback   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimercreatecallback", (RTS_UINTPTR)systimercreatecallback, 1, 0xE5D4A503, 0x03050500) 
#endif


/**
 * <description>This function creates a timer and calls a callback function.</description>
 * <result><p>RESULT: Handle of the timer or RTS_INVALID_HANDLE if failed</p></result>
 */
typedef struct tagsystimercreatecallback2_struct
{
	PFTIMERCALLBACK pfTimerCallback;	/* VAR_INPUT */	/* <param name="pfTimerCallback" type="IN">Pointer to a callback function</param> */
	RTS_IEC_HANDLE hParam;				/* VAR_INPUT */	/* <param name="hParam" type="IN">Parameter for callback routine</param> */
	RTS_IEC_ULINT tIntervalNs;			/* VAR_INPUT */	/* <param name="tIntervalNs" type="IN">Interval of the timer (timebase = 1 ns)</param> */
	RTS_IEC_UDINT ulPriority;			/* VAR_INPUT */	/* <param name="ulPriority" type="IN">Priority of the timer object</param> */
	RTS_IEC_UDINT ulType;				/* VAR_INPUT */	/* <param name="ulType" type="IN">Timer type. See corresponding category.</param> */
	PFTIMEREXCEPTIONHANDLER pfExceptionHandler;	/* VAR_INPUT */	/* <param name="pfExceptionHandler" type="IN">Pointer to an optional exception handler. Can be NULL.</param> */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library)</param> */
	RTS_IEC_HANDLE SysTimerCreateCallback2;	/* VAR_OUTPUT */	
} systimercreatecallback2_struct;

void CDECL CDECL_EXT systimercreatecallback2(systimercreatecallback2_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTIMERCREATECALLBACK2_IEC) (systimercreatecallback2_struct *p);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERCREATECALLBACK2_NOTIMPLEMENTED)
	#define USE_systimercreatecallback2
	#define EXT_systimercreatecallback2
	#define GET_systimercreatecallback2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systimercreatecallback2(p0) 
	#define CHK_systimercreatecallback2  FALSE
	#define EXP_systimercreatecallback2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systimercreatecallback2
	#define EXT_systimercreatecallback2
	#define GET_systimercreatecallback2(fl)  CAL_CMGETAPI( "systimercreatecallback2" ) 
	#define CAL_systimercreatecallback2  systimercreatecallback2
	#define CHK_systimercreatecallback2  TRUE
	#define EXP_systimercreatecallback2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimercreatecallback2", (RTS_UINTPTR)systimercreatecallback2, 1, 0x337F2137, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_systimercreatecallback2
	#define EXT_systimercreatecallback2
	#define GET_systimercreatecallback2(fl)  CAL_CMGETAPI( "systimercreatecallback2" ) 
	#define CAL_systimercreatecallback2  systimercreatecallback2
	#define CHK_systimercreatecallback2  TRUE
	#define EXP_systimercreatecallback2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimercreatecallback2", (RTS_UINTPTR)systimercreatecallback2, 1, 0x337F2137, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimersystimercreatecallback2
	#define EXT_SysTimersystimercreatecallback2
	#define GET_SysTimersystimercreatecallback2  ERR_OK
	#define CAL_SysTimersystimercreatecallback2  systimercreatecallback2
	#define CHK_SysTimersystimercreatecallback2  TRUE
	#define EXP_SysTimersystimercreatecallback2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimercreatecallback2", (RTS_UINTPTR)systimercreatecallback2, 1, 0x337F2137, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systimercreatecallback2
	#define EXT_systimercreatecallback2
	#define GET_systimercreatecallback2(fl)  CAL_CMGETAPI( "systimercreatecallback2" ) 
	#define CAL_systimercreatecallback2  systimercreatecallback2
	#define CHK_systimercreatecallback2  TRUE
	#define EXP_systimercreatecallback2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimercreatecallback2", (RTS_UINTPTR)systimercreatecallback2, 1, 0x337F2137, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systimercreatecallback2  PFSYSTIMERCREATECALLBACK2_IEC pfsystimercreatecallback2;
	#define EXT_systimercreatecallback2  extern PFSYSTIMERCREATECALLBACK2_IEC pfsystimercreatecallback2;
	#define GET_systimercreatecallback2(fl)  s_pfCMGetAPI2( "systimercreatecallback2", (RTS_VOID_FCTPTR *)&pfsystimercreatecallback2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x337F2137, 0x03050500)
	#define CAL_systimercreatecallback2  pfsystimercreatecallback2
	#define CHK_systimercreatecallback2  (pfsystimercreatecallback2 != NULL)
	#define EXP_systimercreatecallback2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimercreatecallback2", (RTS_UINTPTR)systimercreatecallback2, 1, 0x337F2137, 0x03050500) 
#endif


/**
 * <description>This function creates a new timer and sets an event at timer elapsed.</description>
 * <result>Handle of the timer or RTS_INVALID_HANDLE</result>
 */
typedef struct tagsystimercreateevent_struct
{
	RTS_IEC_HANDLE hEvent;				/* VAR_INPUT */	/* <param name="hEvent" type="IN">Handle to the event that is sent after the interval expires</param> */
	RTS_IEC_ULINT tIntervalNs;			/* VAR_INPUT */	/* <param name="tIntervalNs" type="IN">Period of the timer (timebase = 1 ns)</param> */
	RTS_IEC_UDINT ulPriority;			/* VAR_INPUT */	/* <param name="ulPriority" type="IN">Priority of the timer object</param> */
	PFTIMEREXCEPTIONHANDLER pfExceptionHandler;	/* VAR_INPUT */	/* <param name="pfExceptionHandler" type="IN">Pointer to an optional exception handler. Can be NULL.</param> */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library)</param> */
	RTS_IEC_HANDLE SysTimerCreateEvent;	/* VAR_OUTPUT */	
} systimercreateevent_struct;

void CDECL CDECL_EXT systimercreateevent(systimercreateevent_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTIMERCREATEEVENT_IEC) (systimercreateevent_struct *p);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERCREATEEVENT_NOTIMPLEMENTED)
	#define USE_systimercreateevent
	#define EXT_systimercreateevent
	#define GET_systimercreateevent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systimercreateevent(p0) 
	#define CHK_systimercreateevent  FALSE
	#define EXP_systimercreateevent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systimercreateevent
	#define EXT_systimercreateevent
	#define GET_systimercreateevent(fl)  CAL_CMGETAPI( "systimercreateevent" ) 
	#define CAL_systimercreateevent  systimercreateevent
	#define CHK_systimercreateevent  TRUE
	#define EXP_systimercreateevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimercreateevent", (RTS_UINTPTR)systimercreateevent, 1, 0xA540A9F1, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_systimercreateevent
	#define EXT_systimercreateevent
	#define GET_systimercreateevent(fl)  CAL_CMGETAPI( "systimercreateevent" ) 
	#define CAL_systimercreateevent  systimercreateevent
	#define CHK_systimercreateevent  TRUE
	#define EXP_systimercreateevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimercreateevent", (RTS_UINTPTR)systimercreateevent, 1, 0xA540A9F1, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimersystimercreateevent
	#define EXT_SysTimersystimercreateevent
	#define GET_SysTimersystimercreateevent  ERR_OK
	#define CAL_SysTimersystimercreateevent  systimercreateevent
	#define CHK_SysTimersystimercreateevent  TRUE
	#define EXP_SysTimersystimercreateevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimercreateevent", (RTS_UINTPTR)systimercreateevent, 1, 0xA540A9F1, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systimercreateevent
	#define EXT_systimercreateevent
	#define GET_systimercreateevent(fl)  CAL_CMGETAPI( "systimercreateevent" ) 
	#define CAL_systimercreateevent  systimercreateevent
	#define CHK_systimercreateevent  TRUE
	#define EXP_systimercreateevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimercreateevent", (RTS_UINTPTR)systimercreateevent, 1, 0xA540A9F1, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systimercreateevent  PFSYSTIMERCREATEEVENT_IEC pfsystimercreateevent;
	#define EXT_systimercreateevent  extern PFSYSTIMERCREATEEVENT_IEC pfsystimercreateevent;
	#define GET_systimercreateevent(fl)  s_pfCMGetAPI2( "systimercreateevent", (RTS_VOID_FCTPTR *)&pfsystimercreateevent, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xA540A9F1, 0x03050500)
	#define CAL_systimercreateevent  pfsystimercreateevent
	#define CHK_systimercreateevent  (pfsystimercreateevent != NULL)
	#define EXP_systimercreateevent   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimercreateevent", (RTS_UINTPTR)systimercreateevent, 1, 0xA540A9F1, 0x03050500) 
#endif


/**
 * <description>This function deletes a timer</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystimerdelete_struct
{
	RTS_IEC_HANDLE hTimer;				/* VAR_INPUT */	/* <param name="hTimer" type="IN">Handle of the timer</param> */
	RTS_IEC_RESULT SysTimerDelete;		/* VAR_OUTPUT */	
} systimerdelete_struct;

void CDECL CDECL_EXT systimerdelete(systimerdelete_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTIMERDELETE_IEC) (systimerdelete_struct *p);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERDELETE_NOTIMPLEMENTED)
	#define USE_systimerdelete
	#define EXT_systimerdelete
	#define GET_systimerdelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systimerdelete(p0) 
	#define CHK_systimerdelete  FALSE
	#define EXP_systimerdelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systimerdelete
	#define EXT_systimerdelete
	#define GET_systimerdelete(fl)  CAL_CMGETAPI( "systimerdelete" ) 
	#define CAL_systimerdelete  systimerdelete
	#define CHK_systimerdelete  TRUE
	#define EXP_systimerdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimerdelete", (RTS_UINTPTR)systimerdelete, 1, 0xE1762326, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_systimerdelete
	#define EXT_systimerdelete
	#define GET_systimerdelete(fl)  CAL_CMGETAPI( "systimerdelete" ) 
	#define CAL_systimerdelete  systimerdelete
	#define CHK_systimerdelete  TRUE
	#define EXP_systimerdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimerdelete", (RTS_UINTPTR)systimerdelete, 1, 0xE1762326, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimersystimerdelete
	#define EXT_SysTimersystimerdelete
	#define GET_SysTimersystimerdelete  ERR_OK
	#define CAL_SysTimersystimerdelete  systimerdelete
	#define CHK_SysTimersystimerdelete  TRUE
	#define EXP_SysTimersystimerdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimerdelete", (RTS_UINTPTR)systimerdelete, 1, 0xE1762326, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systimerdelete
	#define EXT_systimerdelete
	#define GET_systimerdelete(fl)  CAL_CMGETAPI( "systimerdelete" ) 
	#define CAL_systimerdelete  systimerdelete
	#define CHK_systimerdelete  TRUE
	#define EXP_systimerdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimerdelete", (RTS_UINTPTR)systimerdelete, 1, 0xE1762326, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systimerdelete  PFSYSTIMERDELETE_IEC pfsystimerdelete;
	#define EXT_systimerdelete  extern PFSYSTIMERDELETE_IEC pfsystimerdelete;
	#define GET_systimerdelete(fl)  s_pfCMGetAPI2( "systimerdelete", (RTS_VOID_FCTPTR *)&pfsystimerdelete, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xE1762326, 0x03050500)
	#define CAL_systimerdelete  pfsystimerdelete
	#define CHK_systimerdelete  (pfsystimerdelete != NULL)
	#define EXP_systimerdelete   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimerdelete", (RTS_UINTPTR)systimerdelete, 1, 0xE1762326, 0x03050500) 
#endif


/**
 * <description>Returns the interval of a timer</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystimergetinterval_struct
{
	RTS_IEC_HANDLE hTimer;				/* VAR_INPUT */	/* <param name="hTimer" type="IN">Handle of the timer</param> */
	RTS_IEC_ULINT *ptIntervalNs;		/* VAR_INPUT */	/* <param name="ptIntervalNs" type="OUT">Interval of the timer in nanoseconds</param> */
	RTS_IEC_RESULT SysTimerGetInterval;	/* VAR_OUTPUT */	
} systimergetinterval_struct;

void CDECL CDECL_EXT systimergetinterval(systimergetinterval_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTIMERGETINTERVAL_IEC) (systimergetinterval_struct *p);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERGETINTERVAL_NOTIMPLEMENTED)
	#define USE_systimergetinterval
	#define EXT_systimergetinterval
	#define GET_systimergetinterval(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systimergetinterval(p0) 
	#define CHK_systimergetinterval  FALSE
	#define EXP_systimergetinterval  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systimergetinterval
	#define EXT_systimergetinterval
	#define GET_systimergetinterval(fl)  CAL_CMGETAPI( "systimergetinterval" ) 
	#define CAL_systimergetinterval  systimergetinterval
	#define CHK_systimergetinterval  TRUE
	#define EXP_systimergetinterval  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimergetinterval", (RTS_UINTPTR)systimergetinterval, 1, 0x1B0A9C63, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_systimergetinterval
	#define EXT_systimergetinterval
	#define GET_systimergetinterval(fl)  CAL_CMGETAPI( "systimergetinterval" ) 
	#define CAL_systimergetinterval  systimergetinterval
	#define CHK_systimergetinterval  TRUE
	#define EXP_systimergetinterval  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimergetinterval", (RTS_UINTPTR)systimergetinterval, 1, 0x1B0A9C63, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimersystimergetinterval
	#define EXT_SysTimersystimergetinterval
	#define GET_SysTimersystimergetinterval  ERR_OK
	#define CAL_SysTimersystimergetinterval  systimergetinterval
	#define CHK_SysTimersystimergetinterval  TRUE
	#define EXP_SysTimersystimergetinterval  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimergetinterval", (RTS_UINTPTR)systimergetinterval, 1, 0x1B0A9C63, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systimergetinterval
	#define EXT_systimergetinterval
	#define GET_systimergetinterval(fl)  CAL_CMGETAPI( "systimergetinterval" ) 
	#define CAL_systimergetinterval  systimergetinterval
	#define CHK_systimergetinterval  TRUE
	#define EXP_systimergetinterval  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimergetinterval", (RTS_UINTPTR)systimergetinterval, 1, 0x1B0A9C63, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systimergetinterval  PFSYSTIMERGETINTERVAL_IEC pfsystimergetinterval;
	#define EXT_systimergetinterval  extern PFSYSTIMERGETINTERVAL_IEC pfsystimergetinterval;
	#define GET_systimergetinterval(fl)  s_pfCMGetAPI2( "systimergetinterval", (RTS_VOID_FCTPTR *)&pfsystimergetinterval, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x1B0A9C63, 0x03050500)
	#define CAL_systimergetinterval  pfsystimergetinterval
	#define CHK_systimergetinterval  (pfsystimergetinterval != NULL)
	#define EXP_systimergetinterval   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimergetinterval", (RTS_UINTPTR)systimergetinterval, 1, 0x1B0A9C63, 0x03050500) 
#endif


/**
 * <description>This function returns the timestamp in ticks since timer start</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystimergettimestamp_struct
{
	RTS_IEC_HANDLE hTimer;				/* VAR_INPUT */	/* <param name="hTimer" type="IN">Handle of the timer</param> */
	RTS_IEC_ULINT *ptTimestampNs;		/* VAR_INPUT */	/* <param name="ptTimestampNs" type="OUT">Timestamp in nanoseconds</param> */
	RTS_IEC_RESULT SysTimerGetTimeStamp;	/* VAR_OUTPUT */	
} systimergettimestamp_struct;

void CDECL CDECL_EXT systimergettimestamp(systimergettimestamp_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTIMERGETTIMESTAMP_IEC) (systimergettimestamp_struct *p);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERGETTIMESTAMP_NOTIMPLEMENTED)
	#define USE_systimergettimestamp
	#define EXT_systimergettimestamp
	#define GET_systimergettimestamp(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systimergettimestamp(p0) 
	#define CHK_systimergettimestamp  FALSE
	#define EXP_systimergettimestamp  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systimergettimestamp
	#define EXT_systimergettimestamp
	#define GET_systimergettimestamp(fl)  CAL_CMGETAPI( "systimergettimestamp" ) 
	#define CAL_systimergettimestamp  systimergettimestamp
	#define CHK_systimergettimestamp  TRUE
	#define EXP_systimergettimestamp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimergettimestamp", (RTS_UINTPTR)systimergettimestamp, 1, 0xFE525971, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_systimergettimestamp
	#define EXT_systimergettimestamp
	#define GET_systimergettimestamp(fl)  CAL_CMGETAPI( "systimergettimestamp" ) 
	#define CAL_systimergettimestamp  systimergettimestamp
	#define CHK_systimergettimestamp  TRUE
	#define EXP_systimergettimestamp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimergettimestamp", (RTS_UINTPTR)systimergettimestamp, 1, 0xFE525971, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimersystimergettimestamp
	#define EXT_SysTimersystimergettimestamp
	#define GET_SysTimersystimergettimestamp  ERR_OK
	#define CAL_SysTimersystimergettimestamp  systimergettimestamp
	#define CHK_SysTimersystimergettimestamp  TRUE
	#define EXP_SysTimersystimergettimestamp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimergettimestamp", (RTS_UINTPTR)systimergettimestamp, 1, 0xFE525971, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systimergettimestamp
	#define EXT_systimergettimestamp
	#define GET_systimergettimestamp(fl)  CAL_CMGETAPI( "systimergettimestamp" ) 
	#define CAL_systimergettimestamp  systimergettimestamp
	#define CHK_systimergettimestamp  TRUE
	#define EXP_systimergettimestamp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimergettimestamp", (RTS_UINTPTR)systimergettimestamp, 1, 0xFE525971, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systimergettimestamp  PFSYSTIMERGETTIMESTAMP_IEC pfsystimergettimestamp;
	#define EXT_systimergettimestamp  extern PFSYSTIMERGETTIMESTAMP_IEC pfsystimergettimestamp;
	#define GET_systimergettimestamp(fl)  s_pfCMGetAPI2( "systimergettimestamp", (RTS_VOID_FCTPTR *)&pfsystimergettimestamp, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xFE525971, 0x03050500)
	#define CAL_systimergettimestamp  pfsystimergettimestamp
	#define CHK_systimergettimestamp  (pfsystimergettimestamp != NULL)
	#define EXP_systimergettimestamp   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimergettimestamp", (RTS_UINTPTR)systimergettimestamp, 1, 0xFE525971, 0x03050500) 
#endif


/**
 * <description>This function returns the maximal number of timers</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystimermaxtimer_struct
{
	RTS_IEC_UDINT *pulMaxTimer;			/* VAR_INPUT */	/* <param name="pulMaxTimer" type="OUT">Number of Timers</param> */
	RTS_IEC_RESULT SysTimerMaxTimer;	/* VAR_OUTPUT */	
} systimermaxtimer_struct;

void CDECL CDECL_EXT systimermaxtimer(systimermaxtimer_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTIMERMAXTIMER_IEC) (systimermaxtimer_struct *p);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERMAXTIMER_NOTIMPLEMENTED)
	#define USE_systimermaxtimer
	#define EXT_systimermaxtimer
	#define GET_systimermaxtimer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systimermaxtimer(p0) 
	#define CHK_systimermaxtimer  FALSE
	#define EXP_systimermaxtimer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systimermaxtimer
	#define EXT_systimermaxtimer
	#define GET_systimermaxtimer(fl)  CAL_CMGETAPI( "systimermaxtimer" ) 
	#define CAL_systimermaxtimer  systimermaxtimer
	#define CHK_systimermaxtimer  TRUE
	#define EXP_systimermaxtimer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimermaxtimer", (RTS_UINTPTR)systimermaxtimer, 1, 0xFF05757E, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_systimermaxtimer
	#define EXT_systimermaxtimer
	#define GET_systimermaxtimer(fl)  CAL_CMGETAPI( "systimermaxtimer" ) 
	#define CAL_systimermaxtimer  systimermaxtimer
	#define CHK_systimermaxtimer  TRUE
	#define EXP_systimermaxtimer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimermaxtimer", (RTS_UINTPTR)systimermaxtimer, 1, 0xFF05757E, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimersystimermaxtimer
	#define EXT_SysTimersystimermaxtimer
	#define GET_SysTimersystimermaxtimer  ERR_OK
	#define CAL_SysTimersystimermaxtimer  systimermaxtimer
	#define CHK_SysTimersystimermaxtimer  TRUE
	#define EXP_SysTimersystimermaxtimer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimermaxtimer", (RTS_UINTPTR)systimermaxtimer, 1, 0xFF05757E, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systimermaxtimer
	#define EXT_systimermaxtimer
	#define GET_systimermaxtimer(fl)  CAL_CMGETAPI( "systimermaxtimer" ) 
	#define CAL_systimermaxtimer  systimermaxtimer
	#define CHK_systimermaxtimer  TRUE
	#define EXP_systimermaxtimer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimermaxtimer", (RTS_UINTPTR)systimermaxtimer, 1, 0xFF05757E, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systimermaxtimer  PFSYSTIMERMAXTIMER_IEC pfsystimermaxtimer;
	#define EXT_systimermaxtimer  extern PFSYSTIMERMAXTIMER_IEC pfsystimermaxtimer;
	#define GET_systimermaxtimer(fl)  s_pfCMGetAPI2( "systimermaxtimer", (RTS_VOID_FCTPTR *)&pfsystimermaxtimer, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xFF05757E, 0x03050500)
	#define CAL_systimermaxtimer  pfsystimermaxtimer
	#define CHK_systimermaxtimer  (pfsystimermaxtimer != NULL)
	#define EXP_systimermaxtimer   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimermaxtimer", (RTS_UINTPTR)systimermaxtimer, 1, 0xFF05757E, 0x03050500) 
#endif


/**
 * <description>This function returns the interval of a timer</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystimersetinterval_struct
{
	RTS_IEC_HANDLE hTimer;				/* VAR_INPUT */	/* <param name="hTimer" type="IN">Handle of the timer</param> */
	RTS_IEC_ULINT tIntervalNs;			/* VAR_INPUT */	/* <param name="tIntervalNs" type="IN">Interval of the timer in nanoseconds</param> */
	RTS_IEC_RESULT SysTimerSetInterval;	/* VAR_OUTPUT */	
} systimersetinterval_struct;

void CDECL CDECL_EXT systimersetinterval(systimersetinterval_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTIMERSETINTERVAL_IEC) (systimersetinterval_struct *p);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERSETINTERVAL_NOTIMPLEMENTED)
	#define USE_systimersetinterval
	#define EXT_systimersetinterval
	#define GET_systimersetinterval(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systimersetinterval(p0) 
	#define CHK_systimersetinterval  FALSE
	#define EXP_systimersetinterval  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systimersetinterval
	#define EXT_systimersetinterval
	#define GET_systimersetinterval(fl)  CAL_CMGETAPI( "systimersetinterval" ) 
	#define CAL_systimersetinterval  systimersetinterval
	#define CHK_systimersetinterval  TRUE
	#define EXP_systimersetinterval  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimersetinterval", (RTS_UINTPTR)systimersetinterval, 1, 0x2AF11037, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_systimersetinterval
	#define EXT_systimersetinterval
	#define GET_systimersetinterval(fl)  CAL_CMGETAPI( "systimersetinterval" ) 
	#define CAL_systimersetinterval  systimersetinterval
	#define CHK_systimersetinterval  TRUE
	#define EXP_systimersetinterval  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimersetinterval", (RTS_UINTPTR)systimersetinterval, 1, 0x2AF11037, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimersystimersetinterval
	#define EXT_SysTimersystimersetinterval
	#define GET_SysTimersystimersetinterval  ERR_OK
	#define CAL_SysTimersystimersetinterval  systimersetinterval
	#define CHK_SysTimersystimersetinterval  TRUE
	#define EXP_SysTimersystimersetinterval  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimersetinterval", (RTS_UINTPTR)systimersetinterval, 1, 0x2AF11037, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systimersetinterval
	#define EXT_systimersetinterval
	#define GET_systimersetinterval(fl)  CAL_CMGETAPI( "systimersetinterval" ) 
	#define CAL_systimersetinterval  systimersetinterval
	#define CHK_systimersetinterval  TRUE
	#define EXP_systimersetinterval  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimersetinterval", (RTS_UINTPTR)systimersetinterval, 1, 0x2AF11037, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systimersetinterval  PFSYSTIMERSETINTERVAL_IEC pfsystimersetinterval;
	#define EXT_systimersetinterval  extern PFSYSTIMERSETINTERVAL_IEC pfsystimersetinterval;
	#define GET_systimersetinterval(fl)  s_pfCMGetAPI2( "systimersetinterval", (RTS_VOID_FCTPTR *)&pfsystimersetinterval, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x2AF11037, 0x03050500)
	#define CAL_systimersetinterval  pfsystimersetinterval
	#define CHK_systimersetinterval  (pfsystimersetinterval != NULL)
	#define EXP_systimersetinterval   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimersetinterval", (RTS_UINTPTR)systimersetinterval, 1, 0x2AF11037, 0x03050500) 
#endif


/**
 * <description>This function starts a timer</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystimerstart_struct
{
	RTS_IEC_HANDLE hTimer;				/* VAR_INPUT */	/* <param name="hTimer" type="IN">Handle of the timer</param> */
	RTS_IEC_UDINT ulType;				/* VAR_INPUT */	/* <param name="ulType" type="IN">Type of timer</param> */
	RTS_IEC_RESULT SysTimerStart;		/* VAR_OUTPUT */	
} systimerstart_struct;

void CDECL CDECL_EXT systimerstart(systimerstart_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTIMERSTART_IEC) (systimerstart_struct *p);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERSTART_NOTIMPLEMENTED)
	#define USE_systimerstart
	#define EXT_systimerstart
	#define GET_systimerstart(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systimerstart(p0) 
	#define CHK_systimerstart  FALSE
	#define EXP_systimerstart  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systimerstart
	#define EXT_systimerstart
	#define GET_systimerstart(fl)  CAL_CMGETAPI( "systimerstart" ) 
	#define CAL_systimerstart  systimerstart
	#define CHK_systimerstart  TRUE
	#define EXP_systimerstart  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimerstart", (RTS_UINTPTR)systimerstart, 1, 0xE6A9B3FA, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_systimerstart
	#define EXT_systimerstart
	#define GET_systimerstart(fl)  CAL_CMGETAPI( "systimerstart" ) 
	#define CAL_systimerstart  systimerstart
	#define CHK_systimerstart  TRUE
	#define EXP_systimerstart  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimerstart", (RTS_UINTPTR)systimerstart, 1, 0xE6A9B3FA, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimersystimerstart
	#define EXT_SysTimersystimerstart
	#define GET_SysTimersystimerstart  ERR_OK
	#define CAL_SysTimersystimerstart  systimerstart
	#define CHK_SysTimersystimerstart  TRUE
	#define EXP_SysTimersystimerstart  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimerstart", (RTS_UINTPTR)systimerstart, 1, 0xE6A9B3FA, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systimerstart
	#define EXT_systimerstart
	#define GET_systimerstart(fl)  CAL_CMGETAPI( "systimerstart" ) 
	#define CAL_systimerstart  systimerstart
	#define CHK_systimerstart  TRUE
	#define EXP_systimerstart  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimerstart", (RTS_UINTPTR)systimerstart, 1, 0xE6A9B3FA, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systimerstart  PFSYSTIMERSTART_IEC pfsystimerstart;
	#define EXT_systimerstart  extern PFSYSTIMERSTART_IEC pfsystimerstart;
	#define GET_systimerstart(fl)  s_pfCMGetAPI2( "systimerstart", (RTS_VOID_FCTPTR *)&pfsystimerstart, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xE6A9B3FA, 0x03050500)
	#define CAL_systimerstart  pfsystimerstart
	#define CHK_systimerstart  (pfsystimerstart != NULL)
	#define EXP_systimerstart   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimerstart", (RTS_UINTPTR)systimerstart, 1, 0xE6A9B3FA, 0x03050500) 
#endif


/**
 * <description>This function stops a timer</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystimerstop_struct
{
	RTS_IEC_HANDLE hTimer;				/* VAR_INPUT */	/* <param name="hTimer" type="IN">Handle of the timer</param> */
	RTS_IEC_RESULT SysTimerStop;		/* VAR_OUTPUT */	
} systimerstop_struct;

void CDECL CDECL_EXT systimerstop(systimerstop_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTIMERSTOP_IEC) (systimerstop_struct *p);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERSTOP_NOTIMPLEMENTED)
	#define USE_systimerstop
	#define EXT_systimerstop
	#define GET_systimerstop(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systimerstop(p0) 
	#define CHK_systimerstop  FALSE
	#define EXP_systimerstop  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systimerstop
	#define EXT_systimerstop
	#define GET_systimerstop(fl)  CAL_CMGETAPI( "systimerstop" ) 
	#define CAL_systimerstop  systimerstop
	#define CHK_systimerstop  TRUE
	#define EXP_systimerstop  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimerstop", (RTS_UINTPTR)systimerstop, 1, 0x6374B953, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_systimerstop
	#define EXT_systimerstop
	#define GET_systimerstop(fl)  CAL_CMGETAPI( "systimerstop" ) 
	#define CAL_systimerstop  systimerstop
	#define CHK_systimerstop  TRUE
	#define EXP_systimerstop  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimerstop", (RTS_UINTPTR)systimerstop, 1, 0x6374B953, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimersystimerstop
	#define EXT_SysTimersystimerstop
	#define GET_SysTimersystimerstop  ERR_OK
	#define CAL_SysTimersystimerstop  systimerstop
	#define CHK_SysTimersystimerstop  TRUE
	#define EXP_SysTimersystimerstop  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimerstop", (RTS_UINTPTR)systimerstop, 1, 0x6374B953, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systimerstop
	#define EXT_systimerstop
	#define GET_systimerstop(fl)  CAL_CMGETAPI( "systimerstop" ) 
	#define CAL_systimerstop  systimerstop
	#define CHK_systimerstop  TRUE
	#define EXP_systimerstop  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimerstop", (RTS_UINTPTR)systimerstop, 1, 0x6374B953, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systimerstop  PFSYSTIMERSTOP_IEC pfsystimerstop;
	#define EXT_systimerstop  extern PFSYSTIMERSTOP_IEC pfsystimerstop;
	#define GET_systimerstop(fl)  s_pfCMGetAPI2( "systimerstop", (RTS_VOID_FCTPTR *)&pfsystimerstop, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x6374B953, 0x03050500)
	#define CAL_systimerstop  pfsystimerstop
	#define CHK_systimerstop  (pfsystimerstop != NULL)
	#define EXP_systimerstop   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimerstop", (RTS_UINTPTR)systimerstop, 1, 0x6374B953, 0x03050500) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif


/* Init routines for OS specific modules */
RTS_RESULT CDECL SysTimerOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysTimerOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description> This function creates a timer and sets an event </description>
 * <param name="hEvent" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_EVENTHANDLE]">Handle to the event that is sent after the interval expires</param>
 * <param name="tIntervalNs" type="IN" range="[0,MIN_INTERVAL,MAX_INTERVAL,1000000]">Period of the timer (timebase = 1 ns)</param>
 * <param name="ulPriority" type="IN" range="[0..(SYSTIMER_NUM_OF_TIMER_PRIOS - 1),SYSTIMER_NUM_OF_TIMER_PRIOS]">Priority of the timer object</param>
 * <param name="pfExceptionHandler" type="IN" range="[NULL,VALID_PFEXCEPTIONHANDLER]">Pointer to an optional exception handler. Can be NULL.</param>
 * <param name="pResult" type="OUT">Result pointer containing the error code. Might be NULL. </param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOTIMPLEMENTED">Functionality not implemented, RTS_INVALID_HANDLE is returned</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Event was created, a valid Handle is returned</errorcode>
 * <result>Handle of the timer or RTS_INVALID_HANDLE</result>
 */
RTS_HANDLE CDECL SysTimerCreateEvent(RTS_HANDLE hEvent, RTS_SYSTIME tIntervalNs, unsigned long ulPriority, PFTIMEREXCEPTIONHANDLER pfExceptionHandler, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSTIMERCREATEEVENT) (RTS_HANDLE hEvent, RTS_SYSTIME tIntervalNs, unsigned long ulPriority, PFTIMEREXCEPTIONHANDLER pfExceptionHandler, RTS_RESULT *pResult);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERCREATEEVENT_NOTIMPLEMENTED)
	#define USE_SysTimerCreateEvent
	#define EXT_SysTimerCreateEvent
	#define GET_SysTimerCreateEvent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerCreateEvent(p0,p1,p2,p3,p4)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysTimerCreateEvent  FALSE
	#define EXP_SysTimerCreateEvent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerCreateEvent
	#define EXT_SysTimerCreateEvent
	#define GET_SysTimerCreateEvent(fl)  CAL_CMGETAPI( "SysTimerCreateEvent" ) 
	#define CAL_SysTimerCreateEvent  SysTimerCreateEvent
	#define CHK_SysTimerCreateEvent  TRUE
	#define EXP_SysTimerCreateEvent  CAL_CMEXPAPI( "SysTimerCreateEvent" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerCreateEvent
	#define EXT_SysTimerCreateEvent
	#define GET_SysTimerCreateEvent(fl)  CAL_CMGETAPI( "SysTimerCreateEvent" ) 
	#define CAL_SysTimerCreateEvent  SysTimerCreateEvent
	#define CHK_SysTimerCreateEvent  TRUE
	#define EXP_SysTimerCreateEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerCreateEvent", (RTS_UINTPTR)SysTimerCreateEvent, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerCreateEvent
	#define EXT_SysTimerSysTimerCreateEvent
	#define GET_SysTimerSysTimerCreateEvent  ERR_OK
	#define CAL_SysTimerSysTimerCreateEvent  ((ISysTimer*)s_pfCMCreateInstance(CLASSID_CSysTimer, NULL))->ISysTimerCreateEvent
	#define CHK_SysTimerSysTimerCreateEvent	(s_pfCMCreateInstance != NULL && pISysTimer != NULL)
	#define EXP_SysTimerSysTimerCreateEvent  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerCreateEvent
	#define EXT_SysTimerCreateEvent
	#define GET_SysTimerCreateEvent(fl)  CAL_CMGETAPI( "SysTimerCreateEvent" ) 
	#define CAL_SysTimerCreateEvent  ((ISysTimer*)s_pfCMCreateInstance(CLASSID_CSysTimer, NULL))->ISysTimerCreateEvent
	#define CHK_SysTimerCreateEvent	(s_pfCMCreateInstance != NULL && pISysTimer != NULL)
	#define EXP_SysTimerCreateEvent  CAL_CMEXPAPI( "SysTimerCreateEvent" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerCreateEvent  PFSYSTIMERCREATEEVENT pfSysTimerCreateEvent;
	#define EXT_SysTimerCreateEvent  extern PFSYSTIMERCREATEEVENT pfSysTimerCreateEvent;
	#define GET_SysTimerCreateEvent(fl)  s_pfCMGetAPI2( "SysTimerCreateEvent", (RTS_VOID_FCTPTR *)&pfSysTimerCreateEvent, (fl), 0, 0)
	#define CAL_SysTimerCreateEvent  pfSysTimerCreateEvent
	#define CHK_SysTimerCreateEvent  (pfSysTimerCreateEvent != NULL)
	#define EXP_SysTimerCreateEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerCreateEvent", (RTS_UINTPTR)SysTimerCreateEvent, 0, 0) 
#endif




/**
 * <description>
 * <p>This function creates a system timer, which cyclically calls the callback
 * function that is passed with the parameter pfTimerCallback.</p>
 * <p>This callback has to be of type PFTIMERCALLBACK and gets a the handle 
 * which is specified by hParam passed on every call.</p>
 * <p>The supported timer intervals may be limited by the hardware and/or
 * underlying operating systems.</p>
 * </description>
 *
 * <param name="pfTimerCallback" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_PFTIMERCALLBACK]">Pointer to a callback function</param>
 * <param name="hParam" type="IN" range="[RTS_INVALID_HANDLE,VALID_HPARAM]">Parameter for callback routine</param>
 * <param name="bIECFunction" type="IN" range="[0,1]">Is IEC function</param>
 * <param name="tIntervalNs" type="IN" range="[0,MIN_INTERVAL,MAX_INTERVAL,1000000]">Interval of the timer (timebase = 1 ns)</param>
 * <param name="ulPriority" type="IN" range="[0..(SYSTIMER_NUM_OF_TIMER_PRIOS - 1),SYSTIMER_NUM_OF_TIMER_PRIOS]">Priority of the timer object</param>
 * <param name="pfExceptionHandler" type="IN" range="[NULL,VALID_PFEXCEPTIONHANDLER]">Pointer to an optional exception handler. Can be NULL.</param>
 * <param name="pResult" type="OUT">Result pointer containing the error code. Might be NULL. </param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Callback was created successfully</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_FAILED">Timer could not be opened, SysTimerOpen returned not ERR_OK, RTS_INVALID_HANDLE is returned</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">pfTimerCallback was invalid, RTS_INVALID_HANDLE is returned</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OUT_OF_LIMITS">Number of static timers exceeds Limit: SYSTIMER_NUM_OF_STATIC_TIMER, RTS_INVALID_HANDLE is returned</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NO_MEMORY">Could not get Timerinfo from MemPool, RTS_INVALID_HANDLE is returned</errorcode>
 * <result>Handle of the timer or RTS_INVALID_HANDLE</result>
 */
RTS_HANDLE CDECL SysTimerCreateCallback(PFTIMERCALLBACK pfTimerCallback, RTS_HANDLE hParam, int bIECFunction, RTS_SYSTIME tIntervalNs, unsigned long ulPriority, PFTIMEREXCEPTIONHANDLER pfExceptionHandler, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSTIMERCREATECALLBACK) (PFTIMERCALLBACK pfTimerCallback, RTS_HANDLE hParam, int bIECFunction, RTS_SYSTIME tIntervalNs, unsigned long ulPriority, PFTIMEREXCEPTIONHANDLER pfExceptionHandler, RTS_RESULT *pResult);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERCREATECALLBACK_NOTIMPLEMENTED)
	#define USE_SysTimerCreateCallback
	#define EXT_SysTimerCreateCallback
	#define GET_SysTimerCreateCallback(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerCreateCallback(p0,p1,p2,p3,p4,p5,p6)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysTimerCreateCallback  FALSE
	#define EXP_SysTimerCreateCallback  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerCreateCallback
	#define EXT_SysTimerCreateCallback
	#define GET_SysTimerCreateCallback(fl)  CAL_CMGETAPI( "SysTimerCreateCallback" ) 
	#define CAL_SysTimerCreateCallback  SysTimerCreateCallback
	#define CHK_SysTimerCreateCallback  TRUE
	#define EXP_SysTimerCreateCallback  CAL_CMEXPAPI( "SysTimerCreateCallback" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerCreateCallback
	#define EXT_SysTimerCreateCallback
	#define GET_SysTimerCreateCallback(fl)  CAL_CMGETAPI( "SysTimerCreateCallback" ) 
	#define CAL_SysTimerCreateCallback  SysTimerCreateCallback
	#define CHK_SysTimerCreateCallback  TRUE
	#define EXP_SysTimerCreateCallback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerCreateCallback", (RTS_UINTPTR)SysTimerCreateCallback, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerCreateCallback
	#define EXT_SysTimerSysTimerCreateCallback
	#define GET_SysTimerSysTimerCreateCallback  ERR_OK
	#define CAL_SysTimerSysTimerCreateCallback  ((ISysTimer*)s_pfCMCreateInstance(CLASSID_CSysTimer, NULL))->ISysTimerCreateCallback
	#define CHK_SysTimerSysTimerCreateCallback	(s_pfCMCreateInstance != NULL && pISysTimer != NULL)
	#define EXP_SysTimerSysTimerCreateCallback  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerCreateCallback
	#define EXT_SysTimerCreateCallback
	#define GET_SysTimerCreateCallback(fl)  CAL_CMGETAPI( "SysTimerCreateCallback" ) 
	#define CAL_SysTimerCreateCallback  ((ISysTimer*)s_pfCMCreateInstance(CLASSID_CSysTimer, NULL))->ISysTimerCreateCallback
	#define CHK_SysTimerCreateCallback	(s_pfCMCreateInstance != NULL && pISysTimer != NULL)
	#define EXP_SysTimerCreateCallback  CAL_CMEXPAPI( "SysTimerCreateCallback" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerCreateCallback  PFSYSTIMERCREATECALLBACK pfSysTimerCreateCallback;
	#define EXT_SysTimerCreateCallback  extern PFSYSTIMERCREATECALLBACK pfSysTimerCreateCallback;
	#define GET_SysTimerCreateCallback(fl)  s_pfCMGetAPI2( "SysTimerCreateCallback", (RTS_VOID_FCTPTR *)&pfSysTimerCreateCallback, (fl), 0, 0)
	#define CAL_SysTimerCreateCallback  pfSysTimerCreateCallback
	#define CHK_SysTimerCreateCallback  (pfSysTimerCreateCallback != NULL)
	#define EXP_SysTimerCreateCallback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerCreateCallback", (RTS_UINTPTR)SysTimerCreateCallback, 0, 0) 
#endif




/**
 * <SIL2>Certified Function</SIL2>
 * <description>
 * <p>This function creates a system timer, which calls the callback
 * function that is passed with the parameter pfTimerCallback.</p>
 * <p>This callback has to be of type PFTIMERCALLBACK and gets a the handle 
 * which is specified by hParam passed on every call.</p>
 * <p>Supported are timers with a different behavior (e.g. cyclic timers and
 * one-shot timers). They are specified in the categorie "Timer type"</p>
 * <p>The supported timer intervals may be limited by the hardware and/or
 * underlying operating systems. For one-shot timers, the interval just
 * specifies the time for the next shot.</p>
 * <p>For the case, that the underlying operating system supports only exception
 * handling based on tasks, you can pass a task as an exception handler with
 * the parameter pfExceptionHandler.</p>
 * <p>Timers are priorized like IEC Tasks. There may be 256 Priorities, but
 * this number is in fact limited by the system adaptation.</p>
 * </description>
 *
 * <param name="pfTimerCallback" type="IN" range="[NULL,VALID_PFTIMERCALLBACK]">
 *   Pointer for the Timer callback. This callback is called when ever the timer
 *   event occured.
 * </param>
 * <param name="hParam" type="IN" range="[NULL,VALID_HPARAM]">
 *   Parameter that is passed to the timer callback.
 * </param>
 * <param name="bIECFunction" type="IN" range="[0,1]">
 *   Specify if the Callback is an IEC Function or a C Function. This parameter
 *   is only used internally and may be 0 in most cases.
 * </param>
 * <param name="tIntervalNs" type="IN" range="[0,MIN_INTERVAL,MAX_INTERVAL,1000000]">
 *   Interval of the timer (timebase = 1 ns). The resolution may vary because
 *   of limitations from the hardware or underlying operating system.
 * </param>
 * <param name="ulPriority" type="IN" range="[0..(SYSTIMER_NUM_OF_TIMER_PRIOS - 1),SYSTIMER_NUM_OF_TIMER_PRIOS]">Priority of the timer object</param>
 * <param name="ulType" type="IN" range="[RTS_TIMER_NONE,RTS_TIMER_PERIODIC]">
 *   Not all timers from the category "Timer type" might be supported by the 
 *   system. The only relyable timer is the periodic timer.
 * </param>
 * <param name="pfExceptionHandler" type="IN" range="[NULL,VALID_PFEXCEPTIONHANDLER]">
 *   Pointer to an optional exception handler. Can be NULL.
 * </param>
 * <param name="pResult" type="OUT">Result pointer containing the error code. Might be NULL. </param>
 * <parampseudo name="bFullMemPool" type="IN" range="[TRUE,FALSE]">Indicates whether the internal used MemPool is full.</parampseudo>
 * <parampseudo name="_bIECFunction" type="OUT">if bIECFunction Input is set, IEC Func is called with SysCpuCallIECFuncWithParams, else directly</parampseudo>
 * <parampseudo name="_hParam" type="OUT">hParam from pfTimerCallback must be same value as INPUT hParam</parampseudo>
 * <parampseudo name="_tIntervalNs" type="OUT">Interval in which pfTimerCallback is called must be equal to INPUT tIntervalNs</parampseudo>
 * <parampseudo name="bFullTimer" type="IN" range="[TRUE,FALSE]">Indicates whether all timer used.</parampseudo>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Callback was created successfully</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_FAILED">Timer could not be opened, SysTimerOpen returned not ERR_OK, RTS_INVALID_HANDLE is returned</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">pfTimerCallback was invalid, RTS_INVALID_HANDLE is returned</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OUT_OF_LIMITS">Number of static timers exceeds Limit: SYSTIMER_NUM_OF_STATIC_TIMER, RTS_INVALID_HANDLE is returned</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NO_MEMORY">Could not get Timerinfo from MemPool, RTS_INVALID_HANDLE is returned</errorcode>
 * <result>
 *   Handle of the timer or RTS_INVALID_HANDLE if there was an error.
 * </result> 
 */
RTS_HANDLE CDECL SysTimerCreateCallback2(PFTIMERCALLBACK pfTimerCallback, RTS_HANDLE hParam, int bIECFunction, RTS_SYSTIME tIntervalNs, unsigned long ulPriority, unsigned long ulType, PFTIMEREXCEPTIONHANDLER pfExceptionHandler, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSTIMERCREATECALLBACK2) (PFTIMERCALLBACK pfTimerCallback, RTS_HANDLE hParam, int bIECFunction, RTS_SYSTIME tIntervalNs, unsigned long ulPriority, unsigned long ulType, PFTIMEREXCEPTIONHANDLER pfExceptionHandler, RTS_RESULT *pResult);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERCREATECALLBACK2_NOTIMPLEMENTED)
	#define USE_SysTimerCreateCallback2
	#define EXT_SysTimerCreateCallback2
	#define GET_SysTimerCreateCallback2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerCreateCallback2(p0,p1,p2,p3,p4,p5,p6,p7)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysTimerCreateCallback2  FALSE
	#define EXP_SysTimerCreateCallback2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerCreateCallback2
	#define EXT_SysTimerCreateCallback2
	#define GET_SysTimerCreateCallback2(fl)  CAL_CMGETAPI( "SysTimerCreateCallback2" ) 
	#define CAL_SysTimerCreateCallback2  SysTimerCreateCallback2
	#define CHK_SysTimerCreateCallback2  TRUE
	#define EXP_SysTimerCreateCallback2  CAL_CMEXPAPI( "SysTimerCreateCallback2" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerCreateCallback2
	#define EXT_SysTimerCreateCallback2
	#define GET_SysTimerCreateCallback2(fl)  CAL_CMGETAPI( "SysTimerCreateCallback2" ) 
	#define CAL_SysTimerCreateCallback2  SysTimerCreateCallback2
	#define CHK_SysTimerCreateCallback2  TRUE
	#define EXP_SysTimerCreateCallback2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerCreateCallback2", (RTS_UINTPTR)SysTimerCreateCallback2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerCreateCallback2
	#define EXT_SysTimerSysTimerCreateCallback2
	#define GET_SysTimerSysTimerCreateCallback2  ERR_OK
	#define CAL_SysTimerSysTimerCreateCallback2  ((ISysTimer*)s_pfCMCreateInstance(CLASSID_CSysTimer, NULL))->ISysTimerCreateCallback2
	#define CHK_SysTimerSysTimerCreateCallback2	(s_pfCMCreateInstance != NULL && pISysTimer != NULL)
	#define EXP_SysTimerSysTimerCreateCallback2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerCreateCallback2
	#define EXT_SysTimerCreateCallback2
	#define GET_SysTimerCreateCallback2(fl)  CAL_CMGETAPI( "SysTimerCreateCallback2" ) 
	#define CAL_SysTimerCreateCallback2  ((ISysTimer*)s_pfCMCreateInstance(CLASSID_CSysTimer, NULL))->ISysTimerCreateCallback2
	#define CHK_SysTimerCreateCallback2	(s_pfCMCreateInstance != NULL && pISysTimer != NULL)
	#define EXP_SysTimerCreateCallback2  CAL_CMEXPAPI( "SysTimerCreateCallback2" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerCreateCallback2  PFSYSTIMERCREATECALLBACK2 pfSysTimerCreateCallback2;
	#define EXT_SysTimerCreateCallback2  extern PFSYSTIMERCREATECALLBACK2 pfSysTimerCreateCallback2;
	#define GET_SysTimerCreateCallback2(fl)  s_pfCMGetAPI2( "SysTimerCreateCallback2", (RTS_VOID_FCTPTR *)&pfSysTimerCreateCallback2, (fl), 0, 0)
	#define CAL_SysTimerCreateCallback2  pfSysTimerCreateCallback2
	#define CHK_SysTimerCreateCallback2  (pfSysTimerCreateCallback2 != NULL)
	#define EXP_SysTimerCreateCallback2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerCreateCallback2", (RTS_UINTPTR)SysTimerCreateCallback2, 0, 0) 
#endif




/**
 * <description>This function deletes a timer</description>
 * <param name="hTimer" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERHANDLE]">Handle of the timer</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">hTimer is invalid</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">hTimer could be deleted</errorcode>
 * <result>Error code</result>
 */
RTS_RESULT CDECL SysTimerDelete(RTS_HANDLE hTimer);
typedef RTS_RESULT (CDECL * PFSYSTIMERDELETE) (RTS_HANDLE hTimer);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERDELETE_NOTIMPLEMENTED)
	#define USE_SysTimerDelete
	#define EXT_SysTimerDelete
	#define GET_SysTimerDelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerDelete(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTimerDelete  FALSE
	#define EXP_SysTimerDelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerDelete
	#define EXT_SysTimerDelete
	#define GET_SysTimerDelete(fl)  CAL_CMGETAPI( "SysTimerDelete" ) 
	#define CAL_SysTimerDelete  SysTimerDelete
	#define CHK_SysTimerDelete  TRUE
	#define EXP_SysTimerDelete  CAL_CMEXPAPI( "SysTimerDelete" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerDelete
	#define EXT_SysTimerDelete
	#define GET_SysTimerDelete(fl)  CAL_CMGETAPI( "SysTimerDelete" ) 
	#define CAL_SysTimerDelete  SysTimerDelete
	#define CHK_SysTimerDelete  TRUE
	#define EXP_SysTimerDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerDelete", (RTS_UINTPTR)SysTimerDelete, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerDelete
	#define EXT_SysTimerSysTimerDelete
	#define GET_SysTimerSysTimerDelete  ERR_OK
	#define CAL_SysTimerSysTimerDelete(p0) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ISysTimer*)p0)->ISysTimerDelete())
	#define CHK_SysTimerSysTimerDelete  TRUE
	#define EXP_SysTimerSysTimerDelete  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerDelete
	#define EXT_SysTimerDelete
	#define GET_SysTimerDelete(fl)  CAL_CMGETAPI( "SysTimerDelete" ) 
	#define CAL_SysTimerDelete(p0) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ISysTimer*)p0)->ISysTimerDelete())
	#define CHK_SysTimerDelete  TRUE
	#define EXP_SysTimerDelete  CAL_CMEXPAPI( "SysTimerDelete" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerDelete  PFSYSTIMERDELETE pfSysTimerDelete;
	#define EXT_SysTimerDelete  extern PFSYSTIMERDELETE pfSysTimerDelete;
	#define GET_SysTimerDelete(fl)  s_pfCMGetAPI2( "SysTimerDelete", (RTS_VOID_FCTPTR *)&pfSysTimerDelete, (fl), 0, 0)
	#define CAL_SysTimerDelete  pfSysTimerDelete
	#define CHK_SysTimerDelete  (pfSysTimerDelete != NULL)
	#define EXP_SysTimerDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerDelete", (RTS_UINTPTR)SysTimerDelete, 0, 0) 
#endif




/**
 * <description> This function creates a system specific timer.
 *	IMPLEMENTATION NOTE: The timer must be disabled (in stop state) after returning this routine! The timer must be 
 *	started explicitly with SysTimerStart.</description>
 * <param name="pTimerInfo" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERINFOHANDLE]">Parameter for timer</param>
 * <param name="pResult" type="OUT">Result pointer containing the error code. Might be NULL. </param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">pTimerInfo is invalid</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Timer was opened</errorcode>
 * <result>Handle of the timerinfo or RTS_INVALID_HANDLE</result>
 */
RTS_HANDLE CDECL SysTimerOpen(SYS_TIMER_INFO *pTimerInfo, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSTIMEROPEN) (SYS_TIMER_INFO *pTimerInfo, RTS_RESULT *pResult);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMEROPEN_NOTIMPLEMENTED)
	#define USE_SysTimerOpen
	#define EXT_SysTimerOpen
	#define GET_SysTimerOpen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerOpen(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysTimerOpen  FALSE
	#define EXP_SysTimerOpen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerOpen
	#define EXT_SysTimerOpen
	#define GET_SysTimerOpen(fl)  CAL_CMGETAPI( "SysTimerOpen" ) 
	#define CAL_SysTimerOpen  SysTimerOpen
	#define CHK_SysTimerOpen  TRUE
	#define EXP_SysTimerOpen  CAL_CMEXPAPI( "SysTimerOpen" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerOpen
	#define EXT_SysTimerOpen
	#define GET_SysTimerOpen(fl)  CAL_CMGETAPI( "SysTimerOpen" ) 
	#define CAL_SysTimerOpen  SysTimerOpen
	#define CHK_SysTimerOpen  TRUE
	#define EXP_SysTimerOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerOpen", (RTS_UINTPTR)SysTimerOpen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerOpen
	#define EXT_SysTimerSysTimerOpen
	#define GET_SysTimerSysTimerOpen  ERR_OK
	#define CAL_SysTimerSysTimerOpen  ((ISysTimer*)s_pfCMCreateInstance(CLASSID_CSysTimer, NULL))->ISysTimerOpen
	#define CHK_SysTimerSysTimerOpen	(s_pfCMCreateInstance != NULL && pISysTimer != NULL)
	#define EXP_SysTimerSysTimerOpen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerOpen
	#define EXT_SysTimerOpen
	#define GET_SysTimerOpen(fl)  CAL_CMGETAPI( "SysTimerOpen" ) 
	#define CAL_SysTimerOpen  ((ISysTimer*)s_pfCMCreateInstance(CLASSID_CSysTimer, NULL))->ISysTimerOpen
	#define CHK_SysTimerOpen	(s_pfCMCreateInstance != NULL && pISysTimer != NULL)
	#define EXP_SysTimerOpen  CAL_CMEXPAPI( "SysTimerOpen" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerOpen  PFSYSTIMEROPEN pfSysTimerOpen;
	#define EXT_SysTimerOpen  extern PFSYSTIMEROPEN pfSysTimerOpen;
	#define GET_SysTimerOpen(fl)  s_pfCMGetAPI2( "SysTimerOpen", (RTS_VOID_FCTPTR *)&pfSysTimerOpen, (fl), 0, 0)
	#define CAL_SysTimerOpen  pfSysTimerOpen
	#define CHK_SysTimerOpen  (pfSysTimerOpen != NULL)
	#define EXP_SysTimerOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerOpen", (RTS_UINTPTR)SysTimerOpen, 0, 0) 
#endif




/**
 * <description> This function closes a timer </description>
 * <param name="hTimer" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERHANDLE]">Handle of the timer</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">hTimer is invalid</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Timer was closed</errorcode>
 * <result>Error code</result>
 */
RTS_RESULT CDECL SysTimerClose(RTS_HANDLE hTimer);
typedef RTS_RESULT (CDECL * PFSYSTIMERCLOSE) (RTS_HANDLE hTimer);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERCLOSE_NOTIMPLEMENTED)
	#define USE_SysTimerClose
	#define EXT_SysTimerClose
	#define GET_SysTimerClose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerClose(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTimerClose  FALSE
	#define EXP_SysTimerClose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerClose
	#define EXT_SysTimerClose
	#define GET_SysTimerClose(fl)  CAL_CMGETAPI( "SysTimerClose" ) 
	#define CAL_SysTimerClose  SysTimerClose
	#define CHK_SysTimerClose  TRUE
	#define EXP_SysTimerClose  CAL_CMEXPAPI( "SysTimerClose" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerClose
	#define EXT_SysTimerClose
	#define GET_SysTimerClose(fl)  CAL_CMGETAPI( "SysTimerClose" ) 
	#define CAL_SysTimerClose  SysTimerClose
	#define CHK_SysTimerClose  TRUE
	#define EXP_SysTimerClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerClose", (RTS_UINTPTR)SysTimerClose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerClose
	#define EXT_SysTimerSysTimerClose
	#define GET_SysTimerSysTimerClose  ERR_OK
	#define CAL_SysTimerSysTimerClose(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysTimer->ISysTimerClose() : ((ISysTimer*)p0)->ISysTimerClose())
	#define CHK_SysTimerSysTimerClose  (pISysTimer != NULL)
	#define EXP_SysTimerSysTimerClose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerClose
	#define EXT_SysTimerClose
	#define GET_SysTimerClose(fl)  CAL_CMGETAPI( "SysTimerClose" ) 
	#define CAL_SysTimerClose(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysTimer->ISysTimerClose() : ((ISysTimer*)p0)->ISysTimerClose())
	#define CHK_SysTimerClose  (pISysTimer != NULL)
	#define EXP_SysTimerClose  CAL_CMEXPAPI( "SysTimerClose" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerClose  PFSYSTIMERCLOSE pfSysTimerClose;
	#define EXT_SysTimerClose  extern PFSYSTIMERCLOSE pfSysTimerClose;
	#define GET_SysTimerClose(fl)  s_pfCMGetAPI2( "SysTimerClose", (RTS_VOID_FCTPTR *)&pfSysTimerClose, (fl), 0, 0)
	#define CAL_SysTimerClose  pfSysTimerClose
	#define CHK_SysTimerClose  (pfSysTimerClose != NULL)
	#define EXP_SysTimerClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerClose", (RTS_UINTPTR)SysTimerClose, 0, 0) 
#endif




/**
 * <description> This function starts a timer </description>
 * <param name="hTimer" type="IN" range="[RTS_INVALID_HANDLE,VALID_TIMERHANDLE]">Handle of the timer</param>
 * <param name="ulType" type="IN" range="[RTS_TIMER_NONE,RTS_TIMER_PERIODIC]">Timer type. See corresponding category.</param>
 * <parampseudo name="bRunning" type="OUT">Timer is running successfully</parampseudo>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">hTimer is invalid or Type is not supported</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Timer was started</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Timer could not be started</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">Feature is not implemented</errorcode>
 * <result>Error Code</result>
 */
RTS_RESULT CDECL SysTimerStart(RTS_HANDLE hTimer, unsigned long ulType);
typedef RTS_RESULT (CDECL * PFSYSTIMERSTART) (RTS_HANDLE hTimer, unsigned long ulType);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERSTART_NOTIMPLEMENTED)
	#define USE_SysTimerStart
	#define EXT_SysTimerStart
	#define GET_SysTimerStart(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerStart(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTimerStart  FALSE
	#define EXP_SysTimerStart  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerStart
	#define EXT_SysTimerStart
	#define GET_SysTimerStart(fl)  CAL_CMGETAPI( "SysTimerStart" ) 
	#define CAL_SysTimerStart  SysTimerStart
	#define CHK_SysTimerStart  TRUE
	#define EXP_SysTimerStart  CAL_CMEXPAPI( "SysTimerStart" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerStart
	#define EXT_SysTimerStart
	#define GET_SysTimerStart(fl)  CAL_CMGETAPI( "SysTimerStart" ) 
	#define CAL_SysTimerStart  SysTimerStart
	#define CHK_SysTimerStart  TRUE
	#define EXP_SysTimerStart  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerStart", (RTS_UINTPTR)SysTimerStart, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerStart
	#define EXT_SysTimerSysTimerStart
	#define GET_SysTimerSysTimerStart  ERR_OK
	#define CAL_SysTimerSysTimerStart(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysTimer->ISysTimerStart(p1) : ((ISysTimer*)p0)->ISysTimerStart(p1))
	#define CHK_SysTimerSysTimerStart  (pISysTimer != NULL)
	#define EXP_SysTimerSysTimerStart  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerStart
	#define EXT_SysTimerStart
	#define GET_SysTimerStart(fl)  CAL_CMGETAPI( "SysTimerStart" ) 
	#define CAL_SysTimerStart(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysTimer->ISysTimerStart(p1) : ((ISysTimer*)p0)->ISysTimerStart(p1))
	#define CHK_SysTimerStart  (pISysTimer != NULL)
	#define EXP_SysTimerStart  CAL_CMEXPAPI( "SysTimerStart" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerStart  PFSYSTIMERSTART pfSysTimerStart;
	#define EXT_SysTimerStart  extern PFSYSTIMERSTART pfSysTimerStart;
	#define GET_SysTimerStart(fl)  s_pfCMGetAPI2( "SysTimerStart", (RTS_VOID_FCTPTR *)&pfSysTimerStart, (fl), 0, 0)
	#define CAL_SysTimerStart  pfSysTimerStart
	#define CHK_SysTimerStart  (pfSysTimerStart != NULL)
	#define EXP_SysTimerStart  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerStart", (RTS_UINTPTR)SysTimerStart, 0, 0) 
#endif




/**
 * <description> This function stops a timer </description>
 * <param name="hTimer" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERHANDLE]">Handle of the timer</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">hTimer is invalid</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Timer was stopped</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Timer could not be stopped</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">Feature is not implemented</errorcode>
 * <result>Error Code</result>
 */
RTS_RESULT CDECL SysTimerStop(RTS_HANDLE hTimer);
typedef RTS_RESULT (CDECL * PFSYSTIMERSTOP) (RTS_HANDLE hTimer);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERSTOP_NOTIMPLEMENTED)
	#define USE_SysTimerStop
	#define EXT_SysTimerStop
	#define GET_SysTimerStop(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerStop(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTimerStop  FALSE
	#define EXP_SysTimerStop  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerStop
	#define EXT_SysTimerStop
	#define GET_SysTimerStop(fl)  CAL_CMGETAPI( "SysTimerStop" ) 
	#define CAL_SysTimerStop  SysTimerStop
	#define CHK_SysTimerStop  TRUE
	#define EXP_SysTimerStop  CAL_CMEXPAPI( "SysTimerStop" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerStop
	#define EXT_SysTimerStop
	#define GET_SysTimerStop(fl)  CAL_CMGETAPI( "SysTimerStop" ) 
	#define CAL_SysTimerStop  SysTimerStop
	#define CHK_SysTimerStop  TRUE
	#define EXP_SysTimerStop  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerStop", (RTS_UINTPTR)SysTimerStop, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerStop
	#define EXT_SysTimerSysTimerStop
	#define GET_SysTimerSysTimerStop  ERR_OK
	#define CAL_SysTimerSysTimerStop(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysTimer->ISysTimerStop() : ((ISysTimer*)p0)->ISysTimerStop())
	#define CHK_SysTimerSysTimerStop  (pISysTimer != NULL)
	#define EXP_SysTimerSysTimerStop  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerStop
	#define EXT_SysTimerStop
	#define GET_SysTimerStop(fl)  CAL_CMGETAPI( "SysTimerStop" ) 
	#define CAL_SysTimerStop(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysTimer->ISysTimerStop() : ((ISysTimer*)p0)->ISysTimerStop())
	#define CHK_SysTimerStop  (pISysTimer != NULL)
	#define EXP_SysTimerStop  CAL_CMEXPAPI( "SysTimerStop" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerStop  PFSYSTIMERSTOP pfSysTimerStop;
	#define EXT_SysTimerStop  extern PFSYSTIMERSTOP pfSysTimerStop;
	#define GET_SysTimerStop(fl)  s_pfCMGetAPI2( "SysTimerStop", (RTS_VOID_FCTPTR *)&pfSysTimerStop, (fl), 0, 0)
	#define CAL_SysTimerStop  pfSysTimerStop
	#define CHK_SysTimerStop  (pfSysTimerStop != NULL)
	#define EXP_SysTimerStop  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerStop", (RTS_UINTPTR)SysTimerStop, 0, 0) 
#endif




/**
 * <description>Returns the interval of a timer</description>
 * <param name="hTimer" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERHANDLE]">Handle of the timer</param>
 * <param name="ptIntervalNs" type="OUT">Pointer to Interval of the timer in nanoseconds</param>
 * <parampseudo name="*ptIntervalNs" type="OUT">Interval of the timer in nanoseconds</parampseudo>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">hTimer is invalid or ptIntervalNs is invalid</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Interval could be read successfully</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Interval could not be read</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">Feature is not implemented</errorcode>
 * <result>Error code</result>
 */
RTS_RESULT CDECL SysTimerGetInterval(RTS_HANDLE hTimer, RTS_SYSTIME *ptIntervalNs);
typedef RTS_RESULT (CDECL * PFSYSTIMERGETINTERVAL) (RTS_HANDLE hTimer, RTS_SYSTIME *ptIntervalNs);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERGETINTERVAL_NOTIMPLEMENTED)
	#define USE_SysTimerGetInterval
	#define EXT_SysTimerGetInterval
	#define GET_SysTimerGetInterval(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerGetInterval(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTimerGetInterval  FALSE
	#define EXP_SysTimerGetInterval  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerGetInterval
	#define EXT_SysTimerGetInterval
	#define GET_SysTimerGetInterval(fl)  CAL_CMGETAPI( "SysTimerGetInterval" ) 
	#define CAL_SysTimerGetInterval  SysTimerGetInterval
	#define CHK_SysTimerGetInterval  TRUE
	#define EXP_SysTimerGetInterval  CAL_CMEXPAPI( "SysTimerGetInterval" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerGetInterval
	#define EXT_SysTimerGetInterval
	#define GET_SysTimerGetInterval(fl)  CAL_CMGETAPI( "SysTimerGetInterval" ) 
	#define CAL_SysTimerGetInterval  SysTimerGetInterval
	#define CHK_SysTimerGetInterval  TRUE
	#define EXP_SysTimerGetInterval  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerGetInterval", (RTS_UINTPTR)SysTimerGetInterval, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerGetInterval
	#define EXT_SysTimerSysTimerGetInterval
	#define GET_SysTimerSysTimerGetInterval  ERR_OK
	#define CAL_SysTimerSysTimerGetInterval(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysTimer->ISysTimerGetInterval(p1) : ((ISysTimer*)p0)->ISysTimerGetInterval(p1))
	#define CHK_SysTimerSysTimerGetInterval  (pISysTimer != NULL)
	#define EXP_SysTimerSysTimerGetInterval  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerGetInterval
	#define EXT_SysTimerGetInterval
	#define GET_SysTimerGetInterval(fl)  CAL_CMGETAPI( "SysTimerGetInterval" ) 
	#define CAL_SysTimerGetInterval(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysTimer->ISysTimerGetInterval(p1) : ((ISysTimer*)p0)->ISysTimerGetInterval(p1))
	#define CHK_SysTimerGetInterval  (pISysTimer != NULL)
	#define EXP_SysTimerGetInterval  CAL_CMEXPAPI( "SysTimerGetInterval" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerGetInterval  PFSYSTIMERGETINTERVAL pfSysTimerGetInterval;
	#define EXT_SysTimerGetInterval  extern PFSYSTIMERGETINTERVAL pfSysTimerGetInterval;
	#define GET_SysTimerGetInterval(fl)  s_pfCMGetAPI2( "SysTimerGetInterval", (RTS_VOID_FCTPTR *)&pfSysTimerGetInterval, (fl), 0, 0)
	#define CAL_SysTimerGetInterval  pfSysTimerGetInterval
	#define CHK_SysTimerGetInterval  (pfSysTimerGetInterval != NULL)
	#define EXP_SysTimerGetInterval  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerGetInterval", (RTS_UINTPTR)SysTimerGetInterval, 0, 0) 
#endif




/**
 * <description> This function set the interval of a timer </description>
 * <param name="hTimer" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERHANDLE]">Handle of the timer</param>
 * <param name="tIntervalNs" type="IN" range="[0,MIN_INTERVAL,MAX_INTERVAL,1000000]">Interval of the timer in nanoseconds to set</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">hTimer is invalid</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Interval was set successfully</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Interval was not set successfully</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">Feature is not implemented</errorcode>
 * <result>Error code</result>
 */
RTS_RESULT CDECL SysTimerSetInterval(RTS_HANDLE hTimer, RTS_SYSTIME tIntervalNs);
typedef RTS_RESULT (CDECL * PFSYSTIMERSETINTERVAL) (RTS_HANDLE hTimer, RTS_SYSTIME tIntervalNs);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERSETINTERVAL_NOTIMPLEMENTED)
	#define USE_SysTimerSetInterval
	#define EXT_SysTimerSetInterval
	#define GET_SysTimerSetInterval(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerSetInterval(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTimerSetInterval  FALSE
	#define EXP_SysTimerSetInterval  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerSetInterval
	#define EXT_SysTimerSetInterval
	#define GET_SysTimerSetInterval(fl)  CAL_CMGETAPI( "SysTimerSetInterval" ) 
	#define CAL_SysTimerSetInterval  SysTimerSetInterval
	#define CHK_SysTimerSetInterval  TRUE
	#define EXP_SysTimerSetInterval  CAL_CMEXPAPI( "SysTimerSetInterval" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerSetInterval
	#define EXT_SysTimerSetInterval
	#define GET_SysTimerSetInterval(fl)  CAL_CMGETAPI( "SysTimerSetInterval" ) 
	#define CAL_SysTimerSetInterval  SysTimerSetInterval
	#define CHK_SysTimerSetInterval  TRUE
	#define EXP_SysTimerSetInterval  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerSetInterval", (RTS_UINTPTR)SysTimerSetInterval, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerSetInterval
	#define EXT_SysTimerSysTimerSetInterval
	#define GET_SysTimerSysTimerSetInterval  ERR_OK
	#define CAL_SysTimerSysTimerSetInterval(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysTimer->ISysTimerSetInterval(p1) : ((ISysTimer*)p0)->ISysTimerSetInterval(p1))
	#define CHK_SysTimerSysTimerSetInterval  (pISysTimer != NULL)
	#define EXP_SysTimerSysTimerSetInterval  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerSetInterval
	#define EXT_SysTimerSetInterval
	#define GET_SysTimerSetInterval(fl)  CAL_CMGETAPI( "SysTimerSetInterval" ) 
	#define CAL_SysTimerSetInterval(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysTimer->ISysTimerSetInterval(p1) : ((ISysTimer*)p0)->ISysTimerSetInterval(p1))
	#define CHK_SysTimerSetInterval  (pISysTimer != NULL)
	#define EXP_SysTimerSetInterval  CAL_CMEXPAPI( "SysTimerSetInterval" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerSetInterval  PFSYSTIMERSETINTERVAL pfSysTimerSetInterval;
	#define EXT_SysTimerSetInterval  extern PFSYSTIMERSETINTERVAL pfSysTimerSetInterval;
	#define GET_SysTimerSetInterval(fl)  s_pfCMGetAPI2( "SysTimerSetInterval", (RTS_VOID_FCTPTR *)&pfSysTimerSetInterval, (fl), 0, 0)
	#define CAL_SysTimerSetInterval  pfSysTimerSetInterval
	#define CHK_SysTimerSetInterval  (pfSysTimerSetInterval != NULL)
	#define EXP_SysTimerSetInterval  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerSetInterval", (RTS_UINTPTR)SysTimerSetInterval, 0, 0) 
#endif




/**
 * <description> This function returns the timestamp in ticks since timer start </description>
 * <param name="hTimer" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERHANDLE]">Handle of the timer</param>
 * <param name="ptTimestampNs" type="OUT">Timestamp in nanoseconds</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">hTimer or ptTimestampNs is invalid</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Timestap returned successfully</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Timestamp could not be returned</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_OVERFLOW">Overflow detected since Timerstart</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">Feature is not implemented</errorcode>
 * <result>Error code</result>
 */
RTS_RESULT CDECL SysTimerGetTimeStamp(RTS_HANDLE hTimer, RTS_SYSTIME *ptTimestampNs);
typedef RTS_RESULT (CDECL * PFSYSTIMERGETTIMESTAMP) (RTS_HANDLE hTimer, RTS_SYSTIME *ptTimestampNs);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERGETTIMESTAMP_NOTIMPLEMENTED)
	#define USE_SysTimerGetTimeStamp
	#define EXT_SysTimerGetTimeStamp
	#define GET_SysTimerGetTimeStamp(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerGetTimeStamp(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTimerGetTimeStamp  FALSE
	#define EXP_SysTimerGetTimeStamp  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerGetTimeStamp
	#define EXT_SysTimerGetTimeStamp
	#define GET_SysTimerGetTimeStamp(fl)  CAL_CMGETAPI( "SysTimerGetTimeStamp" ) 
	#define CAL_SysTimerGetTimeStamp  SysTimerGetTimeStamp
	#define CHK_SysTimerGetTimeStamp  TRUE
	#define EXP_SysTimerGetTimeStamp  CAL_CMEXPAPI( "SysTimerGetTimeStamp" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerGetTimeStamp
	#define EXT_SysTimerGetTimeStamp
	#define GET_SysTimerGetTimeStamp(fl)  CAL_CMGETAPI( "SysTimerGetTimeStamp" ) 
	#define CAL_SysTimerGetTimeStamp  SysTimerGetTimeStamp
	#define CHK_SysTimerGetTimeStamp  TRUE
	#define EXP_SysTimerGetTimeStamp  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerGetTimeStamp", (RTS_UINTPTR)SysTimerGetTimeStamp, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerGetTimeStamp
	#define EXT_SysTimerSysTimerGetTimeStamp
	#define GET_SysTimerSysTimerGetTimeStamp  ERR_OK
	#define CAL_SysTimerSysTimerGetTimeStamp(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysTimer->ISysTimerGetTimeStamp(p1) : ((ISysTimer*)p0)->ISysTimerGetTimeStamp(p1))
	#define CHK_SysTimerSysTimerGetTimeStamp  (pISysTimer != NULL)
	#define EXP_SysTimerSysTimerGetTimeStamp  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerGetTimeStamp
	#define EXT_SysTimerGetTimeStamp
	#define GET_SysTimerGetTimeStamp(fl)  CAL_CMGETAPI( "SysTimerGetTimeStamp" ) 
	#define CAL_SysTimerGetTimeStamp(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysTimer->ISysTimerGetTimeStamp(p1) : ((ISysTimer*)p0)->ISysTimerGetTimeStamp(p1))
	#define CHK_SysTimerGetTimeStamp  (pISysTimer != NULL)
	#define EXP_SysTimerGetTimeStamp  CAL_CMEXPAPI( "SysTimerGetTimeStamp" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerGetTimeStamp  PFSYSTIMERGETTIMESTAMP pfSysTimerGetTimeStamp;
	#define EXT_SysTimerGetTimeStamp  extern PFSYSTIMERGETTIMESTAMP pfSysTimerGetTimeStamp;
	#define GET_SysTimerGetTimeStamp(fl)  s_pfCMGetAPI2( "SysTimerGetTimeStamp", (RTS_VOID_FCTPTR *)&pfSysTimerGetTimeStamp, (fl), 0, 0)
	#define CAL_SysTimerGetTimeStamp  pfSysTimerGetTimeStamp
	#define CHK_SysTimerGetTimeStamp  (pfSysTimerGetTimeStamp != NULL)
	#define EXP_SysTimerGetTimeStamp  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerGetTimeStamp", (RTS_UINTPTR)SysTimerGetTimeStamp, 0, 0) 
#endif




/**
 * <description> This function returns the maximal number of timers </description>
 * <param name="pulMaxTimer" type="OUT">Number of Timers</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">pulMaxTimer is invalid</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">pulMaxTimer returned successfully</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">pulMaxTimer could not be returned</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">Feature is not implemented</errorcode>
 * <result>Error code</result>
 */
RTS_RESULT CDECL SysTimerMaxTimer(RTS_UI32 *pulMaxTimers);
typedef RTS_RESULT (CDECL * PFSYSTIMERMAXTIMER) (RTS_UI32 *pulMaxTimers);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERMAXTIMER_NOTIMPLEMENTED)
	#define USE_SysTimerMaxTimer
	#define EXT_SysTimerMaxTimer
	#define GET_SysTimerMaxTimer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerMaxTimer(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTimerMaxTimer  FALSE
	#define EXP_SysTimerMaxTimer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerMaxTimer
	#define EXT_SysTimerMaxTimer
	#define GET_SysTimerMaxTimer(fl)  CAL_CMGETAPI( "SysTimerMaxTimer" ) 
	#define CAL_SysTimerMaxTimer  SysTimerMaxTimer
	#define CHK_SysTimerMaxTimer  TRUE
	#define EXP_SysTimerMaxTimer  CAL_CMEXPAPI( "SysTimerMaxTimer" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerMaxTimer
	#define EXT_SysTimerMaxTimer
	#define GET_SysTimerMaxTimer(fl)  CAL_CMGETAPI( "SysTimerMaxTimer" ) 
	#define CAL_SysTimerMaxTimer  SysTimerMaxTimer
	#define CHK_SysTimerMaxTimer  TRUE
	#define EXP_SysTimerMaxTimer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerMaxTimer", (RTS_UINTPTR)SysTimerMaxTimer, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerMaxTimer
	#define EXT_SysTimerSysTimerMaxTimer
	#define GET_SysTimerSysTimerMaxTimer  ERR_OK
	#define CAL_SysTimerSysTimerMaxTimer pISysTimer->ISysTimerMaxTimer
	#define CHK_SysTimerSysTimerMaxTimer (pISysTimer != NULL)
	#define EXP_SysTimerSysTimerMaxTimer  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerMaxTimer
	#define EXT_SysTimerMaxTimer
	#define GET_SysTimerMaxTimer(fl)  CAL_CMGETAPI( "SysTimerMaxTimer" ) 
	#define CAL_SysTimerMaxTimer pISysTimer->ISysTimerMaxTimer
	#define CHK_SysTimerMaxTimer (pISysTimer != NULL)
	#define EXP_SysTimerMaxTimer  CAL_CMEXPAPI( "SysTimerMaxTimer" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerMaxTimer  PFSYSTIMERMAXTIMER pfSysTimerMaxTimer;
	#define EXT_SysTimerMaxTimer  extern PFSYSTIMERMAXTIMER pfSysTimerMaxTimer;
	#define GET_SysTimerMaxTimer(fl)  s_pfCMGetAPI2( "SysTimerMaxTimer", (RTS_VOID_FCTPTR *)&pfSysTimerMaxTimer, (fl), 0, 0)
	#define CAL_SysTimerMaxTimer  pfSysTimerMaxTimer
	#define CHK_SysTimerMaxTimer  (pfSysTimerMaxTimer != NULL)
	#define EXP_SysTimerMaxTimer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerMaxTimer", (RTS_UINTPTR)SysTimerMaxTimer, 0, 0) 
#endif




/**
 * <description> This function looks for timers with the given properties </description>
 * <param name="ulPriority" type="IN" range="[0..(SYSTIMER_NUM_OF_TIMER_PRIOS - 1),SYSTIMER_NUM_OF_TIMER_PRIOS]">Priority of the timer</param>
 * <param name="tInterval" type="IN" range="[RTS_RANGE_OF_UINT64]">Interval of the timer</param>
 * <param name="pResult" type="OUT">Result pointer containing the error code. Might be NULL. </param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Found existing Timer</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NO_OBJECT">Found no Timer</errorcode>
 * <result>Handle to the searched timer or RTS_INVALID_HANDLE</result>
 */
RTS_HANDLE CDECL SysTimerExistsTimer(unsigned long ulPriority, RTS_SYSTIME tInterval, RTS_RESULT* pResult);
typedef RTS_HANDLE (CDECL * PFSYSTIMEREXISTSTIMER) (unsigned long ulPriority, RTS_SYSTIME tInterval, RTS_RESULT* pResult);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMEREXISTSTIMER_NOTIMPLEMENTED)
	#define USE_SysTimerExistsTimer
	#define EXT_SysTimerExistsTimer
	#define GET_SysTimerExistsTimer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerExistsTimer(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysTimerExistsTimer  FALSE
	#define EXP_SysTimerExistsTimer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerExistsTimer
	#define EXT_SysTimerExistsTimer
	#define GET_SysTimerExistsTimer(fl)  CAL_CMGETAPI( "SysTimerExistsTimer" ) 
	#define CAL_SysTimerExistsTimer  SysTimerExistsTimer
	#define CHK_SysTimerExistsTimer  TRUE
	#define EXP_SysTimerExistsTimer  CAL_CMEXPAPI( "SysTimerExistsTimer" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerExistsTimer
	#define EXT_SysTimerExistsTimer
	#define GET_SysTimerExistsTimer(fl)  CAL_CMGETAPI( "SysTimerExistsTimer" ) 
	#define CAL_SysTimerExistsTimer  SysTimerExistsTimer
	#define CHK_SysTimerExistsTimer  TRUE
	#define EXP_SysTimerExistsTimer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerExistsTimer", (RTS_UINTPTR)SysTimerExistsTimer, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerExistsTimer
	#define EXT_SysTimerSysTimerExistsTimer
	#define GET_SysTimerSysTimerExistsTimer  ERR_OK
	#define CAL_SysTimerSysTimerExistsTimer CSysTimer::ISysTimerExistsTimer
	#define CHK_SysTimerSysTimerExistsTimer  TRUE
	#define EXP_SysTimerSysTimerExistsTimer  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerExistsTimer
	#define EXT_SysTimerExistsTimer
	#define GET_SysTimerExistsTimer(fl)  CAL_CMGETAPI( "SysTimerExistsTimer" ) 
	#define CAL_SysTimerExistsTimer CSysTimer::ISysTimerExistsTimer
	#define CHK_SysTimerExistsTimer  TRUE
	#define EXP_SysTimerExistsTimer  CAL_CMEXPAPI( "SysTimerExistsTimer" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerExistsTimer  PFSYSTIMEREXISTSTIMER pfSysTimerExistsTimer;
	#define EXT_SysTimerExistsTimer  extern PFSYSTIMEREXISTSTIMER pfSysTimerExistsTimer;
	#define GET_SysTimerExistsTimer(fl)  s_pfCMGetAPI2( "SysTimerExistsTimer", (RTS_VOID_FCTPTR *)&pfSysTimerExistsTimer, (fl), 0, 0)
	#define CAL_SysTimerExistsTimer  pfSysTimerExistsTimer
	#define CHK_SysTimerExistsTimer  (pfSysTimerExistsTimer != NULL)
	#define EXP_SysTimerExistsTimer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerExistsTimer", (RTS_UINTPTR)SysTimerExistsTimer, 0, 0) 
#endif




/**
 * <description> This function checks a given timer  </description>
 * <param name="hTimer" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERHANDLE]">Timer to check</param>
 * <param name="ulPriority" type="IN" range="[0..(SYSTIMER_NUM_OF_TIMER_PRIOS - 1),SYSTIMER_NUM_OF_TIMER_PRIOS]">Priority to check</param>
 * <param name="tInterval" type="IN" range="[RTS_RANGE_OF_UINT64]">Interval to check</param>
 * <param name="pResult" type="OUT">Result pointer containing the error code. Might be NULL. </param>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">hTimer is invalid</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Found fit Timer</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NO_OBJECT">Found no Timer</errorcode>
 * <result>Returns if Timer fits</result>
 */
unsigned int CDECL SysTimerFitTimer(RTS_HANDLE hTimer, unsigned long ulPriority, RTS_SYSTIME tInterval, RTS_RESULT *pResult);
typedef unsigned int (CDECL * PFSYSTIMERFITTIMER) (RTS_HANDLE hTimer, unsigned long ulPriority, RTS_SYSTIME tInterval, RTS_RESULT *pResult);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERFITTIMER_NOTIMPLEMENTED)
	#define USE_SysTimerFitTimer
	#define EXT_SysTimerFitTimer
	#define GET_SysTimerFitTimer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerFitTimer(p0,p1,p2,p3)  (unsigned int)ERR_NOTIMPLEMENTED
	#define CHK_SysTimerFitTimer  FALSE
	#define EXP_SysTimerFitTimer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerFitTimer
	#define EXT_SysTimerFitTimer
	#define GET_SysTimerFitTimer(fl)  CAL_CMGETAPI( "SysTimerFitTimer" ) 
	#define CAL_SysTimerFitTimer  SysTimerFitTimer
	#define CHK_SysTimerFitTimer  TRUE
	#define EXP_SysTimerFitTimer  CAL_CMEXPAPI( "SysTimerFitTimer" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerFitTimer
	#define EXT_SysTimerFitTimer
	#define GET_SysTimerFitTimer(fl)  CAL_CMGETAPI( "SysTimerFitTimer" ) 
	#define CAL_SysTimerFitTimer  SysTimerFitTimer
	#define CHK_SysTimerFitTimer  TRUE
	#define EXP_SysTimerFitTimer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerFitTimer", (RTS_UINTPTR)SysTimerFitTimer, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerFitTimer
	#define EXT_SysTimerSysTimerFitTimer
	#define GET_SysTimerSysTimerFitTimer  ERR_OK
	#define CAL_SysTimerSysTimerFitTimer(p0,p1,p2,p3)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysTimer->ISysTimerFitTimer(p1,p2,p3) : ((ISysTimer*)p0)->ISysTimerFitTimer(p1,p2,p3))
	#define CHK_SysTimerSysTimerFitTimer  (pISysTimer != NULL)
	#define EXP_SysTimerSysTimerFitTimer  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerFitTimer
	#define EXT_SysTimerFitTimer
	#define GET_SysTimerFitTimer(fl)  CAL_CMGETAPI( "SysTimerFitTimer" ) 
	#define CAL_SysTimerFitTimer(p0,p1,p2,p3)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysTimer->ISysTimerFitTimer(p1,p2,p3) : ((ISysTimer*)p0)->ISysTimerFitTimer(p1,p2,p3))
	#define CHK_SysTimerFitTimer  (pISysTimer != NULL)
	#define EXP_SysTimerFitTimer  CAL_CMEXPAPI( "SysTimerFitTimer" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerFitTimer  PFSYSTIMERFITTIMER pfSysTimerFitTimer;
	#define EXT_SysTimerFitTimer  extern PFSYSTIMERFITTIMER pfSysTimerFitTimer;
	#define GET_SysTimerFitTimer(fl)  s_pfCMGetAPI2( "SysTimerFitTimer", (RTS_VOID_FCTPTR *)&pfSysTimerFitTimer, (fl), 0, 0)
	#define CAL_SysTimerFitTimer  pfSysTimerFitTimer
	#define CHK_SysTimerFitTimer  (pfSysTimerFitTimer != NULL)
	#define EXP_SysTimerFitTimer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerFitTimer", (RTS_UINTPTR)SysTimerFitTimer, 0, 0) 
#endif




/**
 * <description> Get the minimum resolution of the timer </description>
 * <param name="hTimer" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERHANDLE]">Handle of the timer</param>
 * <param name="ptMinResolutionNs" type="OUT">Minimum timer resolution in nanoseconds</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">hTimer or ptMinResolutionNs is invalid</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Could get min resolution</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Could not get min resolution</errorcode>
 * <result>Error code</result>
 */
RTS_RESULT CDECL SysTimerGetMinResolution(RTS_HANDLE hTimer, RTS_SYSTIME *ptMinResolutionNs);
typedef RTS_RESULT (CDECL * PFSYSTIMERGETMINRESOLUTION) (RTS_HANDLE hTimer, RTS_SYSTIME *ptMinResolutionNs);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERGETMINRESOLUTION_NOTIMPLEMENTED)
	#define USE_SysTimerGetMinResolution
	#define EXT_SysTimerGetMinResolution
	#define GET_SysTimerGetMinResolution(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerGetMinResolution(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTimerGetMinResolution  FALSE
	#define EXP_SysTimerGetMinResolution  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerGetMinResolution
	#define EXT_SysTimerGetMinResolution
	#define GET_SysTimerGetMinResolution(fl)  CAL_CMGETAPI( "SysTimerGetMinResolution" ) 
	#define CAL_SysTimerGetMinResolution  SysTimerGetMinResolution
	#define CHK_SysTimerGetMinResolution  TRUE
	#define EXP_SysTimerGetMinResolution  CAL_CMEXPAPI( "SysTimerGetMinResolution" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerGetMinResolution
	#define EXT_SysTimerGetMinResolution
	#define GET_SysTimerGetMinResolution(fl)  CAL_CMGETAPI( "SysTimerGetMinResolution" ) 
	#define CAL_SysTimerGetMinResolution  SysTimerGetMinResolution
	#define CHK_SysTimerGetMinResolution  TRUE
	#define EXP_SysTimerGetMinResolution  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerGetMinResolution", (RTS_UINTPTR)SysTimerGetMinResolution, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerGetMinResolution
	#define EXT_SysTimerSysTimerGetMinResolution
	#define GET_SysTimerSysTimerGetMinResolution  ERR_OK
	#define CAL_SysTimerSysTimerGetMinResolution(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysTimer->ISysTimerGetMinResolution(p1) : ((ISysTimer*)p0)->ISysTimerGetMinResolution(p1))
	#define CHK_SysTimerSysTimerGetMinResolution  (pISysTimer != NULL)
	#define EXP_SysTimerSysTimerGetMinResolution  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerGetMinResolution
	#define EXT_SysTimerGetMinResolution
	#define GET_SysTimerGetMinResolution(fl)  CAL_CMGETAPI( "SysTimerGetMinResolution" ) 
	#define CAL_SysTimerGetMinResolution(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysTimer->ISysTimerGetMinResolution(p1) : ((ISysTimer*)p0)->ISysTimerGetMinResolution(p1))
	#define CHK_SysTimerGetMinResolution  (pISysTimer != NULL)
	#define EXP_SysTimerGetMinResolution  CAL_CMEXPAPI( "SysTimerGetMinResolution" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerGetMinResolution  PFSYSTIMERGETMINRESOLUTION pfSysTimerGetMinResolution;
	#define EXT_SysTimerGetMinResolution  extern PFSYSTIMERGETMINRESOLUTION pfSysTimerGetMinResolution;
	#define GET_SysTimerGetMinResolution(fl)  s_pfCMGetAPI2( "SysTimerGetMinResolution", (RTS_VOID_FCTPTR *)&pfSysTimerGetMinResolution, (fl), 0, 0)
	#define CAL_SysTimerGetMinResolution  pfSysTimerGetMinResolution
	#define CHK_SysTimerGetMinResolution  (pfSysTimerGetMinResolution != NULL)
	#define EXP_SysTimerGetMinResolution  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerGetMinResolution", (RTS_UINTPTR)SysTimerGetMinResolution, 0, 0) 
#endif




/*-----------------------------------------------------------------------------------------------*/
/*						Interface for Timer Scheduler											 */
/*-----------------------------------------------------------------------------------------------*/
/**
 * <description> This function returns the context of the current timer handling </description>
 * <param name="hTimer" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERHANDLE]">Handle of the Timer</param>
 * <param name="pContext" type="OUT">Pointer to Timer Context</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">hTimer or pContext is invalid</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">GetContext was successful</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Could not get Context</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">Feature is not implemented</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysTimerGetContext(RTS_HANDLE hTimer, RegContext *pContext);
typedef RTS_RESULT (CDECL * PFSYSTIMERGETCONTEXT) (RTS_HANDLE hTimer, RegContext *pContext);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERGETCONTEXT_NOTIMPLEMENTED)
	#define USE_SysTimerGetContext
	#define EXT_SysTimerGetContext
	#define GET_SysTimerGetContext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerGetContext(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTimerGetContext  FALSE
	#define EXP_SysTimerGetContext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerGetContext
	#define EXT_SysTimerGetContext
	#define GET_SysTimerGetContext(fl)  CAL_CMGETAPI( "SysTimerGetContext" ) 
	#define CAL_SysTimerGetContext  SysTimerGetContext
	#define CHK_SysTimerGetContext  TRUE
	#define EXP_SysTimerGetContext  CAL_CMEXPAPI( "SysTimerGetContext" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerGetContext
	#define EXT_SysTimerGetContext
	#define GET_SysTimerGetContext(fl)  CAL_CMGETAPI( "SysTimerGetContext" ) 
	#define CAL_SysTimerGetContext  SysTimerGetContext
	#define CHK_SysTimerGetContext  TRUE
	#define EXP_SysTimerGetContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerGetContext", (RTS_UINTPTR)SysTimerGetContext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerGetContext
	#define EXT_SysTimerSysTimerGetContext
	#define GET_SysTimerSysTimerGetContext  ERR_OK
	#define CAL_SysTimerSysTimerGetContext(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysTimer->ISysTimerGetContext(p1) : ((ISysTimer*)p0)->ISysTimerGetContext(p1))
	#define CHK_SysTimerSysTimerGetContext  (pISysTimer != NULL)
	#define EXP_SysTimerSysTimerGetContext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerGetContext
	#define EXT_SysTimerGetContext
	#define GET_SysTimerGetContext(fl)  CAL_CMGETAPI( "SysTimerGetContext" ) 
	#define CAL_SysTimerGetContext(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysTimer->ISysTimerGetContext(p1) : ((ISysTimer*)p0)->ISysTimerGetContext(p1))
	#define CHK_SysTimerGetContext  (pISysTimer != NULL)
	#define EXP_SysTimerGetContext  CAL_CMEXPAPI( "SysTimerGetContext" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerGetContext  PFSYSTIMERGETCONTEXT pfSysTimerGetContext;
	#define EXT_SysTimerGetContext  extern PFSYSTIMERGETCONTEXT pfSysTimerGetContext;
	#define GET_SysTimerGetContext(fl)  s_pfCMGetAPI2( "SysTimerGetContext", (RTS_VOID_FCTPTR *)&pfSysTimerGetContext, (fl), 0, 0)
	#define CAL_SysTimerGetContext  pfSysTimerGetContext
	#define CHK_SysTimerGetContext  (pfSysTimerGetContext != NULL)
	#define EXP_SysTimerGetContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerGetContext", (RTS_UINTPTR)SysTimerGetContext, 0, 0) 
#endif




/**
 * <description> Calls the corresponding exception handler of the timer.</description>
 * <param name="hTimerHandle" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERHANDLE]">Handle to timer</param>
 * <param name="ulException" type="IN" range="[RTS_RANGE_OF_ULONG]">Rts standard exception</param>
 * <param name="Context" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_CONTEXT]">Context to detect the code location where the exception occurred</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Exception was successfully handled</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">No Timer found or Exception Handler returned ERR_FAILED</errorcode>
 * <result>ERR_OK</result>
 */
RTS_RESULT CDECL SysTimerGenerateException(RTS_HANDLE hTimerHandle, RTS_UI32 ulException, RegContext Context);
typedef RTS_RESULT (CDECL * PFSYSTIMERGENERATEEXCEPTION) (RTS_HANDLE hTimerHandle, RTS_UI32 ulException, RegContext Context);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERGENERATEEXCEPTION_NOTIMPLEMENTED)
	#define USE_SysTimerGenerateException
	#define EXT_SysTimerGenerateException
	#define GET_SysTimerGenerateException(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerGenerateException(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTimerGenerateException  FALSE
	#define EXP_SysTimerGenerateException  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerGenerateException
	#define EXT_SysTimerGenerateException
	#define GET_SysTimerGenerateException(fl)  CAL_CMGETAPI( "SysTimerGenerateException" ) 
	#define CAL_SysTimerGenerateException  SysTimerGenerateException
	#define CHK_SysTimerGenerateException  TRUE
	#define EXP_SysTimerGenerateException  CAL_CMEXPAPI( "SysTimerGenerateException" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerGenerateException
	#define EXT_SysTimerGenerateException
	#define GET_SysTimerGenerateException(fl)  CAL_CMGETAPI( "SysTimerGenerateException" ) 
	#define CAL_SysTimerGenerateException  SysTimerGenerateException
	#define CHK_SysTimerGenerateException  TRUE
	#define EXP_SysTimerGenerateException  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerGenerateException", (RTS_UINTPTR)SysTimerGenerateException, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerGenerateException
	#define EXT_SysTimerSysTimerGenerateException
	#define GET_SysTimerSysTimerGenerateException  ERR_OK
	#define CAL_SysTimerSysTimerGenerateException CSysTimer::ISysTimerGenerateException
	#define CHK_SysTimerSysTimerGenerateException  TRUE
	#define EXP_SysTimerSysTimerGenerateException  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerGenerateException
	#define EXT_SysTimerGenerateException
	#define GET_SysTimerGenerateException(fl)  CAL_CMGETAPI( "SysTimerGenerateException" ) 
	#define CAL_SysTimerGenerateException CSysTimer::ISysTimerGenerateException
	#define CHK_SysTimerGenerateException  TRUE
	#define EXP_SysTimerGenerateException  CAL_CMEXPAPI( "SysTimerGenerateException" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerGenerateException  PFSYSTIMERGENERATEEXCEPTION pfSysTimerGenerateException;
	#define EXT_SysTimerGenerateException  extern PFSYSTIMERGENERATEEXCEPTION pfSysTimerGenerateException;
	#define GET_SysTimerGenerateException(fl)  s_pfCMGetAPI2( "SysTimerGenerateException", (RTS_VOID_FCTPTR *)&pfSysTimerGenerateException, (fl), 0, 0)
	#define CAL_SysTimerGenerateException  pfSysTimerGenerateException
	#define CHK_SysTimerGenerateException  (pfSysTimerGenerateException != NULL)
	#define EXP_SysTimerGenerateException  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerGenerateException", (RTS_UINTPTR)SysTimerGenerateException, 0, 0) 
#endif




/**
 * <description> Sets the Callback Parameter </description>
 * <param name="hTimer" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERHANDLE]">Handle of the timer</param>
 * <param name="hParam" type="IN" range="[RTS_INVALID_HANDLE,VALID_HPARAM]">Parameter for callback routine</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Callback Parameter was successfully handled</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">hTimer invalid</errorcode>
 * <result>Error code</result>
 */
RTS_RESULT CDECL SysTimerSetCallbackParameter(RTS_HANDLE hTimer, RTS_HANDLE hParam);
typedef RTS_RESULT (CDECL * PFSYSTIMERSETCALLBACKPARAMETER) (RTS_HANDLE hTimer, RTS_HANDLE hParam);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERSETCALLBACKPARAMETER_NOTIMPLEMENTED)
	#define USE_SysTimerSetCallbackParameter
	#define EXT_SysTimerSetCallbackParameter
	#define GET_SysTimerSetCallbackParameter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerSetCallbackParameter(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTimerSetCallbackParameter  FALSE
	#define EXP_SysTimerSetCallbackParameter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerSetCallbackParameter
	#define EXT_SysTimerSetCallbackParameter
	#define GET_SysTimerSetCallbackParameter(fl)  CAL_CMGETAPI( "SysTimerSetCallbackParameter" ) 
	#define CAL_SysTimerSetCallbackParameter  SysTimerSetCallbackParameter
	#define CHK_SysTimerSetCallbackParameter  TRUE
	#define EXP_SysTimerSetCallbackParameter  CAL_CMEXPAPI( "SysTimerSetCallbackParameter" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerSetCallbackParameter
	#define EXT_SysTimerSetCallbackParameter
	#define GET_SysTimerSetCallbackParameter(fl)  CAL_CMGETAPI( "SysTimerSetCallbackParameter" ) 
	#define CAL_SysTimerSetCallbackParameter  SysTimerSetCallbackParameter
	#define CHK_SysTimerSetCallbackParameter  TRUE
	#define EXP_SysTimerSetCallbackParameter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerSetCallbackParameter", (RTS_UINTPTR)SysTimerSetCallbackParameter, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerSetCallbackParameter
	#define EXT_SysTimerSysTimerSetCallbackParameter
	#define GET_SysTimerSysTimerSetCallbackParameter  ERR_OK
	#define CAL_SysTimerSysTimerSetCallbackParameter(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysTimer->ISysTimerSetCallbackParameter(p1) : ((ISysTimer*)p0)->ISysTimerSetCallbackParameter(p1))
	#define CHK_SysTimerSysTimerSetCallbackParameter  (pISysTimer != NULL)
	#define EXP_SysTimerSysTimerSetCallbackParameter  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerSetCallbackParameter
	#define EXT_SysTimerSetCallbackParameter
	#define GET_SysTimerSetCallbackParameter(fl)  CAL_CMGETAPI( "SysTimerSetCallbackParameter" ) 
	#define CAL_SysTimerSetCallbackParameter(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysTimer->ISysTimerSetCallbackParameter(p1) : ((ISysTimer*)p0)->ISysTimerSetCallbackParameter(p1))
	#define CHK_SysTimerSetCallbackParameter  (pISysTimer != NULL)
	#define EXP_SysTimerSetCallbackParameter  CAL_CMEXPAPI( "SysTimerSetCallbackParameter" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerSetCallbackParameter  PFSYSTIMERSETCALLBACKPARAMETER pfSysTimerSetCallbackParameter;
	#define EXT_SysTimerSetCallbackParameter  extern PFSYSTIMERSETCALLBACKPARAMETER pfSysTimerSetCallbackParameter;
	#define GET_SysTimerSetCallbackParameter(fl)  s_pfCMGetAPI2( "SysTimerSetCallbackParameter", (RTS_VOID_FCTPTR *)&pfSysTimerSetCallbackParameter, (fl), 0, 0)
	#define CAL_SysTimerSetCallbackParameter  pfSysTimerSetCallbackParameter
	#define CHK_SysTimerSetCallbackParameter  (pfSysTimerSetCallbackParameter != NULL)
	#define EXP_SysTimerSetCallbackParameter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerSetCallbackParameter", (RTS_UINTPTR)SysTimerSetCallbackParameter, 0, 0) 
#endif




/**
 * <description> With this function the specified function is reseted (Needed for CmpScheduleTimer) </description>
 * <param name="hTimer" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERHANDLE]">Handle of the timer to reset</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">No error occured</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Setting Priority failed</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">hTimer invalid</errorcode>
 * <result>Error code</result>
 */
RTS_RESULT CDECL SysTimerSetResetFollowing(RTS_HANDLE hTimer);
typedef RTS_RESULT (CDECL * PFSYSTIMERSETRESETFOLLOWING) (RTS_HANDLE hTimer);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERSETRESETFOLLOWING_NOTIMPLEMENTED)
	#define USE_SysTimerSetResetFollowing
	#define EXT_SysTimerSetResetFollowing
	#define GET_SysTimerSetResetFollowing(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerSetResetFollowing(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTimerSetResetFollowing  FALSE
	#define EXP_SysTimerSetResetFollowing  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerSetResetFollowing
	#define EXT_SysTimerSetResetFollowing
	#define GET_SysTimerSetResetFollowing(fl)  CAL_CMGETAPI( "SysTimerSetResetFollowing" ) 
	#define CAL_SysTimerSetResetFollowing  SysTimerSetResetFollowing
	#define CHK_SysTimerSetResetFollowing  TRUE
	#define EXP_SysTimerSetResetFollowing  CAL_CMEXPAPI( "SysTimerSetResetFollowing" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerSetResetFollowing
	#define EXT_SysTimerSetResetFollowing
	#define GET_SysTimerSetResetFollowing(fl)  CAL_CMGETAPI( "SysTimerSetResetFollowing" ) 
	#define CAL_SysTimerSetResetFollowing  SysTimerSetResetFollowing
	#define CHK_SysTimerSetResetFollowing  TRUE
	#define EXP_SysTimerSetResetFollowing  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerSetResetFollowing", (RTS_UINTPTR)SysTimerSetResetFollowing, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerSetResetFollowing
	#define EXT_SysTimerSysTimerSetResetFollowing
	#define GET_SysTimerSysTimerSetResetFollowing  ERR_OK
	#define CAL_SysTimerSysTimerSetResetFollowing(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysTimer->ISysTimerSetResetFollowing() : ((ISysTimer*)p0)->ISysTimerSetResetFollowing())
	#define CHK_SysTimerSysTimerSetResetFollowing  (pISysTimer != NULL)
	#define EXP_SysTimerSysTimerSetResetFollowing  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerSetResetFollowing
	#define EXT_SysTimerSetResetFollowing
	#define GET_SysTimerSetResetFollowing(fl)  CAL_CMGETAPI( "SysTimerSetResetFollowing" ) 
	#define CAL_SysTimerSetResetFollowing(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysTimer->ISysTimerSetResetFollowing() : ((ISysTimer*)p0)->ISysTimerSetResetFollowing())
	#define CHK_SysTimerSetResetFollowing  (pISysTimer != NULL)
	#define EXP_SysTimerSetResetFollowing  CAL_CMEXPAPI( "SysTimerSetResetFollowing" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerSetResetFollowing  PFSYSTIMERSETRESETFOLLOWING pfSysTimerSetResetFollowing;
	#define EXT_SysTimerSetResetFollowing  extern PFSYSTIMERSETRESETFOLLOWING pfSysTimerSetResetFollowing;
	#define GET_SysTimerSetResetFollowing(fl)  s_pfCMGetAPI2( "SysTimerSetResetFollowing", (RTS_VOID_FCTPTR *)&pfSysTimerSetResetFollowing, (fl), 0, 0)
	#define CAL_SysTimerSetResetFollowing  pfSysTimerSetResetFollowing
	#define CHK_SysTimerSetResetFollowing  (pfSysTimerSetResetFollowing != NULL)
	#define EXP_SysTimerSetResetFollowing  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerSetResetFollowing", (RTS_UINTPTR)SysTimerSetResetFollowing, 0, 0) 
#endif




/**
 * <description> Register the base pointer of the main routine.</description>
 * <param name="pulBP" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_BASEPOINTER]">base pointer of main</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">pulBP is invalid</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">pulBP was successful registered</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">pulBP could not be registered</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">Feature is not implemented</errorcode>
 * <result>ERR_OK</result>
 */
RTS_RESULT CDECL SysTimerRegisterBasePointer(RTS_UINTPTR ulBP);
typedef RTS_RESULT (CDECL * PFSYSTIMERREGISTERBASEPOINTER) (RTS_UINTPTR ulBP);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERREGISTERBASEPOINTER_NOTIMPLEMENTED)
	#define USE_SysTimerRegisterBasePointer
	#define EXT_SysTimerRegisterBasePointer
	#define GET_SysTimerRegisterBasePointer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerRegisterBasePointer(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTimerRegisterBasePointer  FALSE
	#define EXP_SysTimerRegisterBasePointer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerRegisterBasePointer
	#define EXT_SysTimerRegisterBasePointer
	#define GET_SysTimerRegisterBasePointer(fl)  CAL_CMGETAPI( "SysTimerRegisterBasePointer" ) 
	#define CAL_SysTimerRegisterBasePointer  SysTimerRegisterBasePointer
	#define CHK_SysTimerRegisterBasePointer  TRUE
	#define EXP_SysTimerRegisterBasePointer  CAL_CMEXPAPI( "SysTimerRegisterBasePointer" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerRegisterBasePointer
	#define EXT_SysTimerRegisterBasePointer
	#define GET_SysTimerRegisterBasePointer(fl)  CAL_CMGETAPI( "SysTimerRegisterBasePointer" ) 
	#define CAL_SysTimerRegisterBasePointer  SysTimerRegisterBasePointer
	#define CHK_SysTimerRegisterBasePointer  TRUE
	#define EXP_SysTimerRegisterBasePointer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerRegisterBasePointer", (RTS_UINTPTR)SysTimerRegisterBasePointer, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerRegisterBasePointer
	#define EXT_SysTimerSysTimerRegisterBasePointer
	#define GET_SysTimerSysTimerRegisterBasePointer  ERR_OK
	#define CAL_SysTimerSysTimerRegisterBasePointer pISysTimer->ISysTimerRegisterBasePointer
	#define CHK_SysTimerSysTimerRegisterBasePointer (pISysTimer != NULL)
	#define EXP_SysTimerSysTimerRegisterBasePointer  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerRegisterBasePointer
	#define EXT_SysTimerRegisterBasePointer
	#define GET_SysTimerRegisterBasePointer(fl)  CAL_CMGETAPI( "SysTimerRegisterBasePointer" ) 
	#define CAL_SysTimerRegisterBasePointer pISysTimer->ISysTimerRegisterBasePointer
	#define CHK_SysTimerRegisterBasePointer (pISysTimer != NULL)
	#define EXP_SysTimerRegisterBasePointer  CAL_CMEXPAPI( "SysTimerRegisterBasePointer" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerRegisterBasePointer  PFSYSTIMERREGISTERBASEPOINTER pfSysTimerRegisterBasePointer;
	#define EXT_SysTimerRegisterBasePointer  extern PFSYSTIMERREGISTERBASEPOINTER pfSysTimerRegisterBasePointer;
	#define GET_SysTimerRegisterBasePointer(fl)  s_pfCMGetAPI2( "SysTimerRegisterBasePointer", (RTS_VOID_FCTPTR *)&pfSysTimerRegisterBasePointer, (fl), 0, 0)
	#define CAL_SysTimerRegisterBasePointer  pfSysTimerRegisterBasePointer
	#define CHK_SysTimerRegisterBasePointer  (pfSysTimerRegisterBasePointer != NULL)
	#define EXP_SysTimerRegisterBasePointer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerRegisterBasePointer", (RTS_UINTPTR)SysTimerRegisterBasePointer, 0, 0) 
#endif




/**
 * <description>Get first registered timer object</description>
 * <param name="pResult" type="OUT">Result pointer containing the error code. Might be NULL. </param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Successfully found first Timer</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NO_OBJECT">No Timer found</errorcode>
 * <result>Handle to first timer object</result>
 */
RTS_HANDLE CDECL SysTimerGetFirst(RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSTIMERGETFIRST) (RTS_RESULT *pResult);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERGETFIRST_NOTIMPLEMENTED)
	#define USE_SysTimerGetFirst
	#define EXT_SysTimerGetFirst
	#define GET_SysTimerGetFirst(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerGetFirst(p0)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysTimerGetFirst  FALSE
	#define EXP_SysTimerGetFirst  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerGetFirst
	#define EXT_SysTimerGetFirst
	#define GET_SysTimerGetFirst(fl)  CAL_CMGETAPI( "SysTimerGetFirst" ) 
	#define CAL_SysTimerGetFirst  SysTimerGetFirst
	#define CHK_SysTimerGetFirst  TRUE
	#define EXP_SysTimerGetFirst  CAL_CMEXPAPI( "SysTimerGetFirst" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerGetFirst
	#define EXT_SysTimerGetFirst
	#define GET_SysTimerGetFirst(fl)  CAL_CMGETAPI( "SysTimerGetFirst" ) 
	#define CAL_SysTimerGetFirst  SysTimerGetFirst
	#define CHK_SysTimerGetFirst  TRUE
	#define EXP_SysTimerGetFirst  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerGetFirst", (RTS_UINTPTR)SysTimerGetFirst, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerGetFirst
	#define EXT_SysTimerSysTimerGetFirst
	#define GET_SysTimerSysTimerGetFirst  ERR_OK
	#define CAL_SysTimerSysTimerGetFirst pISysTimer->ISysTimerGetFirst
	#define CHK_SysTimerSysTimerGetFirst (pISysTimer != NULL)
	#define EXP_SysTimerSysTimerGetFirst  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerGetFirst
	#define EXT_SysTimerGetFirst
	#define GET_SysTimerGetFirst(fl)  CAL_CMGETAPI( "SysTimerGetFirst" ) 
	#define CAL_SysTimerGetFirst pISysTimer->ISysTimerGetFirst
	#define CHK_SysTimerGetFirst (pISysTimer != NULL)
	#define EXP_SysTimerGetFirst  CAL_CMEXPAPI( "SysTimerGetFirst" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerGetFirst  PFSYSTIMERGETFIRST pfSysTimerGetFirst;
	#define EXT_SysTimerGetFirst  extern PFSYSTIMERGETFIRST pfSysTimerGetFirst;
	#define GET_SysTimerGetFirst(fl)  s_pfCMGetAPI2( "SysTimerGetFirst", (RTS_VOID_FCTPTR *)&pfSysTimerGetFirst, (fl), 0, 0)
	#define CAL_SysTimerGetFirst  pfSysTimerGetFirst
	#define CHK_SysTimerGetFirst  (pfSysTimerGetFirst != NULL)
	#define EXP_SysTimerGetFirst  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerGetFirst", (RTS_UINTPTR)SysTimerGetFirst, 0, 0) 
#endif




/**
 * <description>Get next registered timer object</description>
 * <param name="hTimerPrev" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERINFOHANDLE]">Handle to previous timer object</param>
 * <param name="pResult" type="OUT">Result pointer containing the error code. Might be NULL. </param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Successfully found next Timer</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NO_OBJECT">No Timer found</errorcode>
 * <result>Handle to next timer object</result>
 */
RTS_HANDLE CDECL SysTimerGetNext(RTS_HANDLE hTimerPrev, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSTIMERGETNEXT) (RTS_HANDLE hTimerPrev, RTS_RESULT *pResult);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERGETNEXT_NOTIMPLEMENTED)
	#define USE_SysTimerGetNext
	#define EXT_SysTimerGetNext
	#define GET_SysTimerGetNext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerGetNext(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysTimerGetNext  FALSE
	#define EXP_SysTimerGetNext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerGetNext
	#define EXT_SysTimerGetNext
	#define GET_SysTimerGetNext(fl)  CAL_CMGETAPI( "SysTimerGetNext" ) 
	#define CAL_SysTimerGetNext  SysTimerGetNext
	#define CHK_SysTimerGetNext  TRUE
	#define EXP_SysTimerGetNext  CAL_CMEXPAPI( "SysTimerGetNext" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerGetNext
	#define EXT_SysTimerGetNext
	#define GET_SysTimerGetNext(fl)  CAL_CMGETAPI( "SysTimerGetNext" ) 
	#define CAL_SysTimerGetNext  SysTimerGetNext
	#define CHK_SysTimerGetNext  TRUE
	#define EXP_SysTimerGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerGetNext", (RTS_UINTPTR)SysTimerGetNext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerGetNext
	#define EXT_SysTimerSysTimerGetNext
	#define GET_SysTimerSysTimerGetNext  ERR_OK
	#define CAL_SysTimerSysTimerGetNext pISysTimer->ISysTimerGetNext
	#define CHK_SysTimerSysTimerGetNext (pISysTimer != NULL)
	#define EXP_SysTimerSysTimerGetNext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerGetNext
	#define EXT_SysTimerGetNext
	#define GET_SysTimerGetNext(fl)  CAL_CMGETAPI( "SysTimerGetNext" ) 
	#define CAL_SysTimerGetNext pISysTimer->ISysTimerGetNext
	#define CHK_SysTimerGetNext (pISysTimer != NULL)
	#define EXP_SysTimerGetNext  CAL_CMEXPAPI( "SysTimerGetNext" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerGetNext  PFSYSTIMERGETNEXT pfSysTimerGetNext;
	#define EXT_SysTimerGetNext  extern PFSYSTIMERGETNEXT pfSysTimerGetNext;
	#define GET_SysTimerGetNext(fl)  s_pfCMGetAPI2( "SysTimerGetNext", (RTS_VOID_FCTPTR *)&pfSysTimerGetNext, (fl), 0, 0)
	#define CAL_SysTimerGetNext  pfSysTimerGetNext
	#define CHK_SysTimerGetNext  (pfSysTimerGetNext != NULL)
	#define EXP_SysTimerGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerGetNext", (RTS_UINTPTR)SysTimerGetNext, 0, 0) 
#endif




/**
 * <description>Call the registered callback handler with the corresponding hParam. IEC- and C-handlers are supported.</description>
 * <param name="hTimer" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERHANDLE]">Secified timer object</param>
 * <parampseudo name="pTimer->bIECFunction" type="IN" range="[RTS_RANGE_OF_INT]">Secified timer object</parampseudo>
 * <parampseudo name="bFuncCalled" type="OUT">Function call expected</parampseudo>
 * <result></result>
 */
void CDECL SysTimerCallCallback(SYS_TIMER_INFO *pTimer);
typedef void (CDECL * PFSYSTIMERCALLCALLBACK) (SYS_TIMER_INFO *pTimer);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERCALLCALLBACK_NOTIMPLEMENTED)
	#define USE_SysTimerCallCallback
	#define EXT_SysTimerCallCallback
	#define GET_SysTimerCallCallback(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerCallCallback(p0)  
	#define CHK_SysTimerCallCallback  FALSE
	#define EXP_SysTimerCallCallback  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerCallCallback
	#define EXT_SysTimerCallCallback
	#define GET_SysTimerCallCallback(fl)  CAL_CMGETAPI( "SysTimerCallCallback" ) 
	#define CAL_SysTimerCallCallback  SysTimerCallCallback
	#define CHK_SysTimerCallCallback  TRUE
	#define EXP_SysTimerCallCallback  CAL_CMEXPAPI( "SysTimerCallCallback" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerCallCallback
	#define EXT_SysTimerCallCallback
	#define GET_SysTimerCallCallback(fl)  CAL_CMGETAPI( "SysTimerCallCallback" ) 
	#define CAL_SysTimerCallCallback  SysTimerCallCallback
	#define CHK_SysTimerCallCallback  TRUE
	#define EXP_SysTimerCallCallback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerCallCallback", (RTS_UINTPTR)SysTimerCallCallback, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerCallCallback
	#define EXT_SysTimerSysTimerCallCallback
	#define GET_SysTimerSysTimerCallCallback  ERR_OK
	#define CAL_SysTimerSysTimerCallCallback pISysTimer->ISysTimerCallCallback
	#define CHK_SysTimerSysTimerCallCallback (pISysTimer != NULL)
	#define EXP_SysTimerSysTimerCallCallback  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerCallCallback
	#define EXT_SysTimerCallCallback
	#define GET_SysTimerCallCallback(fl)  CAL_CMGETAPI( "SysTimerCallCallback" ) 
	#define CAL_SysTimerCallCallback pISysTimer->ISysTimerCallCallback
	#define CHK_SysTimerCallCallback (pISysTimer != NULL)
	#define EXP_SysTimerCallCallback  CAL_CMEXPAPI( "SysTimerCallCallback" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerCallCallback  PFSYSTIMERCALLCALLBACK pfSysTimerCallCallback;
	#define EXT_SysTimerCallCallback  extern PFSYSTIMERCALLCALLBACK pfSysTimerCallCallback;
	#define GET_SysTimerCallCallback(fl)  s_pfCMGetAPI2( "SysTimerCallCallback", (RTS_VOID_FCTPTR *)&pfSysTimerCallCallback, (fl), 0, 0)
	#define CAL_SysTimerCallCallback  pfSysTimerCallCallback
	#define CHK_SysTimerCallCallback  (pfSysTimerCallCallback != NULL)
	#define EXP_SysTimerCallCallback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerCallCallback", (RTS_UINTPTR)SysTimerCallCallback, 0, 0) 
#endif




/**
 * <description>
 * <p>Returns the handle of the currently active timer, or RTS_INVALID_HANDLE if
 * we are outside of a timer context.</p>
 * <p>For SIL2 systems, this function is not implemented and returns always RTS_INVALID_HANDLE.</p>
 * </description> 
 * <param name="pResult" type="OUT">Result pointer containing the error code. Might be NULL. </param> 
 * <parampseudo name="bSIL2Runtime" type="IN" range="[1]">Result pointer containing the error code. Might be NULL. </parampseudo> 
 * <result>Handle of the currently active timer or RTS_INVALID_HANDLE</result>
 * 
 */
RTS_HANDLE CDECL SysTimerGetCurrent(RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSTIMERGETCURRENT) (RTS_RESULT *pResult);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERGETCURRENT_NOTIMPLEMENTED)
	#define USE_SysTimerGetCurrent
	#define EXT_SysTimerGetCurrent
	#define GET_SysTimerGetCurrent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerGetCurrent(p0)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysTimerGetCurrent  FALSE
	#define EXP_SysTimerGetCurrent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerGetCurrent
	#define EXT_SysTimerGetCurrent
	#define GET_SysTimerGetCurrent(fl)  CAL_CMGETAPI( "SysTimerGetCurrent" ) 
	#define CAL_SysTimerGetCurrent  SysTimerGetCurrent
	#define CHK_SysTimerGetCurrent  TRUE
	#define EXP_SysTimerGetCurrent  CAL_CMEXPAPI( "SysTimerGetCurrent" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerGetCurrent
	#define EXT_SysTimerGetCurrent
	#define GET_SysTimerGetCurrent(fl)  CAL_CMGETAPI( "SysTimerGetCurrent" ) 
	#define CAL_SysTimerGetCurrent  SysTimerGetCurrent
	#define CHK_SysTimerGetCurrent  TRUE
	#define EXP_SysTimerGetCurrent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerGetCurrent", (RTS_UINTPTR)SysTimerGetCurrent, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerGetCurrent
	#define EXT_SysTimerSysTimerGetCurrent
	#define GET_SysTimerSysTimerGetCurrent  ERR_OK
	#define CAL_SysTimerSysTimerGetCurrent pISysTimer->ISysTimerGetCurrent
	#define CHK_SysTimerSysTimerGetCurrent (pISysTimer != NULL)
	#define EXP_SysTimerSysTimerGetCurrent  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerGetCurrent
	#define EXT_SysTimerGetCurrent
	#define GET_SysTimerGetCurrent(fl)  CAL_CMGETAPI( "SysTimerGetCurrent" ) 
	#define CAL_SysTimerGetCurrent pISysTimer->ISysTimerGetCurrent
	#define CHK_SysTimerGetCurrent (pISysTimer != NULL)
	#define EXP_SysTimerGetCurrent  CAL_CMEXPAPI( "SysTimerGetCurrent" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerGetCurrent  PFSYSTIMERGETCURRENT pfSysTimerGetCurrent;
	#define EXT_SysTimerGetCurrent  extern PFSYSTIMERGETCURRENT pfSysTimerGetCurrent;
	#define GET_SysTimerGetCurrent(fl)  s_pfCMGetAPI2( "SysTimerGetCurrent", (RTS_VOID_FCTPTR *)&pfSysTimerGetCurrent, (fl), 0, 0)
	#define CAL_SysTimerGetCurrent  pfSysTimerGetCurrent
	#define CHK_SysTimerGetCurrent  (pfSysTimerGetCurrent != NULL)
	#define EXP_SysTimerGetCurrent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerGetCurrent", (RTS_UINTPTR)SysTimerGetCurrent, 0, 0) 
#endif




/**
 * <description>
 * <p>Returns the timer info of the specified timer</p>
 * </description> 
 * <param name="hTimer" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERHANDLE]">Secified timer object</param>
 * <param name="pResult" type="OUT">Result pointer containing the error code. Might be NULL. </param> 
 * <result>Pointer to the SYS_TIMER_INFO structure or NULL if failed</result>
 * 
 */
SYS_TIMER_INFO * CDECL SysTimerGetInfo(RTS_HANDLE hTimer, RTS_RESULT *pResult);
typedef SYS_TIMER_INFO * (CDECL * PFSYSTIMERGETINFO) (RTS_HANDLE hTimer, RTS_RESULT *pResult);
#if defined(SYSTIMER_NOTIMPLEMENTED) || defined(SYSTIMERGETINFO_NOTIMPLEMENTED)
	#define USE_SysTimerGetInfo
	#define EXT_SysTimerGetInfo
	#define GET_SysTimerGetInfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimerGetInfo(p0,p1)  (SYS_TIMER_INFO *)ERR_NOTIMPLEMENTED
	#define CHK_SysTimerGetInfo  FALSE
	#define EXP_SysTimerGetInfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimerGetInfo
	#define EXT_SysTimerGetInfo
	#define GET_SysTimerGetInfo(fl)  CAL_CMGETAPI( "SysTimerGetInfo" ) 
	#define CAL_SysTimerGetInfo  SysTimerGetInfo
	#define CHK_SysTimerGetInfo  TRUE
	#define EXP_SysTimerGetInfo  CAL_CMEXPAPI( "SysTimerGetInfo" ) 
#elif defined(MIXED_LINK) && !defined(SYSTIMER_EXTERNAL)
	#define USE_SysTimerGetInfo
	#define EXT_SysTimerGetInfo
	#define GET_SysTimerGetInfo(fl)  CAL_CMGETAPI( "SysTimerGetInfo" ) 
	#define CAL_SysTimerGetInfo  SysTimerGetInfo
	#define CHK_SysTimerGetInfo  TRUE
	#define EXP_SysTimerGetInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerGetInfo", (RTS_UINTPTR)SysTimerGetInfo, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTimerSysTimerGetInfo
	#define EXT_SysTimerSysTimerGetInfo
	#define GET_SysTimerSysTimerGetInfo  ERR_OK
	#define CAL_SysTimerSysTimerGetInfo pISysTimer->ISysTimerGetInfo
	#define CHK_SysTimerSysTimerGetInfo (pISysTimer != NULL)
	#define EXP_SysTimerSysTimerGetInfo  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimerGetInfo
	#define EXT_SysTimerGetInfo
	#define GET_SysTimerGetInfo(fl)  CAL_CMGETAPI( "SysTimerGetInfo" ) 
	#define CAL_SysTimerGetInfo pISysTimer->ISysTimerGetInfo
	#define CHK_SysTimerGetInfo (pISysTimer != NULL)
	#define EXP_SysTimerGetInfo  CAL_CMEXPAPI( "SysTimerGetInfo" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimerGetInfo  PFSYSTIMERGETINFO pfSysTimerGetInfo;
	#define EXT_SysTimerGetInfo  extern PFSYSTIMERGETINFO pfSysTimerGetInfo;
	#define GET_SysTimerGetInfo(fl)  s_pfCMGetAPI2( "SysTimerGetInfo", (RTS_VOID_FCTPTR *)&pfSysTimerGetInfo, (fl), 0, 0)
	#define CAL_SysTimerGetInfo  pfSysTimerGetInfo
	#define CHK_SysTimerGetInfo  (pfSysTimerGetInfo != NULL)
	#define EXP_SysTimerGetInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimerGetInfo", (RTS_UINTPTR)SysTimerGetInfo, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSYSTIMERCREATEEVENT ISysTimerCreateEvent;
 	PFSYSTIMERCREATECALLBACK ISysTimerCreateCallback;
 	PFSYSTIMERCREATECALLBACK2 ISysTimerCreateCallback2;
 	PFSYSTIMERDELETE ISysTimerDelete;
 	PFSYSTIMEROPEN ISysTimerOpen;
 	PFSYSTIMERCLOSE ISysTimerClose;
 	PFSYSTIMERSTART ISysTimerStart;
 	PFSYSTIMERSTOP ISysTimerStop;
 	PFSYSTIMERGETINTERVAL ISysTimerGetInterval;
 	PFSYSTIMERSETINTERVAL ISysTimerSetInterval;
 	PFSYSTIMERGETTIMESTAMP ISysTimerGetTimeStamp;
 	PFSYSTIMERMAXTIMER ISysTimerMaxTimer;
 	PFSYSTIMEREXISTSTIMER ISysTimerExistsTimer;
 	PFSYSTIMERFITTIMER ISysTimerFitTimer;
 	PFSYSTIMERGETMINRESOLUTION ISysTimerGetMinResolution;
 	PFSYSTIMERGETCONTEXT ISysTimerGetContext;
 	PFSYSTIMERGENERATEEXCEPTION ISysTimerGenerateException;
 	PFSYSTIMERSETCALLBACKPARAMETER ISysTimerSetCallbackParameter;
 	PFSYSTIMERSETRESETFOLLOWING ISysTimerSetResetFollowing;
 	PFSYSTIMERREGISTERBASEPOINTER ISysTimerRegisterBasePointer;
 	PFSYSTIMERGETFIRST ISysTimerGetFirst;
 	PFSYSTIMERGETNEXT ISysTimerGetNext;
 	PFSYSTIMERCALLCALLBACK ISysTimerCallCallback;
 	PFSYSTIMERGETCURRENT ISysTimerGetCurrent;
 	PFSYSTIMERGETINFO ISysTimerGetInfo;
 } ISysTimer_C;

#ifdef CPLUSPLUS
class ISysTimer : public IBase
{
	public:
		virtual RTS_HANDLE CDECL ISysTimerCreateEvent(RTS_HANDLE hEvent, RTS_SYSTIME tIntervalNs, unsigned long ulPriority, PFTIMEREXCEPTIONHANDLER pfExceptionHandler, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL ISysTimerCreateCallback(PFTIMERCALLBACK pfTimerCallback, RTS_HANDLE hParam, int bIECFunction, RTS_SYSTIME tIntervalNs, unsigned long ulPriority, PFTIMEREXCEPTIONHANDLER pfExceptionHandler, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL ISysTimerCreateCallback2(PFTIMERCALLBACK pfTimerCallback, RTS_HANDLE hParam, int bIECFunction, RTS_SYSTIME tIntervalNs, unsigned long ulPriority, unsigned long ulType, PFTIMEREXCEPTIONHANDLER pfExceptionHandler, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISysTimerDelete(void) =0;
		virtual RTS_HANDLE CDECL ISysTimerOpen(SYS_TIMER_INFO *pTimerInfo, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISysTimerClose(void) =0;
		virtual RTS_RESULT CDECL ISysTimerStart(unsigned long ulType) =0;
		virtual RTS_RESULT CDECL ISysTimerStop(void) =0;
		virtual RTS_RESULT CDECL ISysTimerGetInterval(RTS_SYSTIME *ptIntervalNs) =0;
		virtual RTS_RESULT CDECL ISysTimerSetInterval(RTS_SYSTIME tIntervalNs) =0;
		virtual RTS_RESULT CDECL ISysTimerGetTimeStamp(RTS_SYSTIME *ptTimestampNs) =0;
		virtual RTS_RESULT CDECL ISysTimerMaxTimer(RTS_UI32 *pulMaxTimers) =0;
		static RTS_HANDLE CDECL ISysTimerExistsTimer(unsigned long ulPriority, RTS_SYSTIME tInterval, RTS_RESULT* pResult);
		virtual unsigned int CDECL ISysTimerFitTimer(unsigned long ulPriority, RTS_SYSTIME tInterval, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISysTimerGetMinResolution(RTS_SYSTIME *ptMinResolutionNs) =0;
		virtual RTS_RESULT CDECL ISysTimerGetContext(RegContext *pContext) =0;
		static RTS_RESULT CDECL ISysTimerGenerateException(RTS_HANDLE hTimerHandle, RTS_UI32 ulException, RegContext Context);
		virtual RTS_RESULT CDECL ISysTimerSetCallbackParameter(RTS_HANDLE hParam) =0;
		virtual RTS_RESULT CDECL ISysTimerSetResetFollowing(void) =0;
		virtual RTS_RESULT CDECL ISysTimerRegisterBasePointer(RTS_UINTPTR ulBP) =0;
		virtual RTS_HANDLE CDECL ISysTimerGetFirst(RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL ISysTimerGetNext(RTS_HANDLE hTimerPrev, RTS_RESULT *pResult) =0;
		virtual void CDECL ISysTimerCallCallback(SYS_TIMER_INFO *pTimer) =0;
		virtual RTS_HANDLE CDECL ISysTimerGetCurrent(RTS_RESULT *pResult) =0;
		virtual SYS_TIMER_INFO * CDECL ISysTimerGetInfo(RTS_HANDLE hTimer, RTS_RESULT *pResult) =0;
};
	#ifndef ITF_SysTimer
		#define ITF_SysTimer static ISysTimer *pISysTimer = NULL;
	#endif
	#define EXTITF_SysTimer
#else	/*CPLUSPLUS*/
	typedef ISysTimer_C		ISysTimer;
	#ifndef ITF_SysTimer
		#define ITF_SysTimer
	#endif
	#define EXTITF_SysTimer
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSTIMERITF_H_*/
