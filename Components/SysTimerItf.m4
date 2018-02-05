/**
 * <interfacename>SysTimer</interfacename>
 * <description> 
 *	<p>The SysTimer interface is projected to access timer devices on target.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysTimer')

#include "CmpItf.h"
REF_ITF(`SysTimeItf.m4')

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

DEF_API(`void',`CDECL',`systimercreatecallback',`(systimercreatecallback_struct *p)',1,0xE5D4A503,0x03050500)

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

DEF_API(`void',`CDECL',`systimercreatecallback2',`(systimercreatecallback2_struct *p)',1,0x337F2137,0x03050500)

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

DEF_API(`void',`CDECL',`systimercreateevent',`(systimercreateevent_struct *p)',1,0xA540A9F1,0x03050500)

/**
 * <description>This function deletes a timer</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystimerdelete_struct
{
	RTS_IEC_HANDLE hTimer;				/* VAR_INPUT */	/* <param name="hTimer" type="IN">Handle of the timer</param> */
	RTS_IEC_RESULT SysTimerDelete;		/* VAR_OUTPUT */	
} systimerdelete_struct;

DEF_API(`void',`CDECL',`systimerdelete',`(systimerdelete_struct *p)',1,0xE1762326,0x03050500)

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

DEF_API(`void',`CDECL',`systimergetinterval',`(systimergetinterval_struct *p)',1,0x1B0A9C63,0x03050500)

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

DEF_API(`void',`CDECL',`systimergettimestamp',`(systimergettimestamp_struct *p)',1,0xFE525971,0x03050500)

/**
 * <description>This function returns the maximal number of timers</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystimermaxtimer_struct
{
	RTS_IEC_UDINT *pulMaxTimer;			/* VAR_INPUT */	/* <param name="pulMaxTimer" type="OUT">Number of Timers</param> */
	RTS_IEC_RESULT SysTimerMaxTimer;	/* VAR_OUTPUT */	
} systimermaxtimer_struct;

DEF_API(`void',`CDECL',`systimermaxtimer',`(systimermaxtimer_struct *p)',1,0xFF05757E,0x03050500)

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

DEF_API(`void',`CDECL',`systimersetinterval',`(systimersetinterval_struct *p)',1,0x2AF11037,0x03050500)

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

DEF_API(`void',`CDECL',`systimerstart',`(systimerstart_struct *p)',1,0xE6A9B3FA,0x03050500)

/**
 * <description>This function stops a timer</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystimerstop_struct
{
	RTS_IEC_HANDLE hTimer;				/* VAR_INPUT */	/* <param name="hTimer" type="IN">Handle of the timer</param> */
	RTS_IEC_RESULT SysTimerStop;		/* VAR_OUTPUT */	
} systimerstop_struct;

DEF_API(`void',`CDECL',`systimerstop',`(systimerstop_struct *p)',1,0x6374B953,0x03050500)

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
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysTimerCreateEvent',`(RTS_HANDLE hEvent, RTS_SYSTIME tIntervalNs, unsigned long ulPriority, PFTIMEREXCEPTIONHANDLER pfExceptionHandler, RTS_RESULT *pResult)')

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
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysTimerCreateCallback',`(PFTIMERCALLBACK pfTimerCallback, RTS_HANDLE hParam, int bIECFunction, RTS_SYSTIME tIntervalNs, unsigned long ulPriority, PFTIMEREXCEPTIONHANDLER pfExceptionHandler, RTS_RESULT *pResult)')

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
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysTimerCreateCallback2',`(PFTIMERCALLBACK pfTimerCallback, RTS_HANDLE hParam, int bIECFunction, RTS_SYSTIME tIntervalNs, unsigned long ulPriority, unsigned long ulType, PFTIMEREXCEPTIONHANDLER pfExceptionHandler, RTS_RESULT *pResult)')

/**
 * <description>This function deletes a timer</description>
 * <param name="hTimer" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERHANDLE]">Handle of the timer</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">hTimer is invalid</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">hTimer could be deleted</errorcode>
 * <result>Error code</result>
 */
DEF_DELETEITF_API(`RTS_RESULT',`CDECL',`SysTimerDelete',`(RTS_HANDLE hTimer)')

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
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysTimerOpen',`(SYS_TIMER_INFO *pTimerInfo, RTS_RESULT *pResult)')

/**
 * <description> This function closes a timer </description>
 * <param name="hTimer" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERHANDLE]">Handle of the timer</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">hTimer is invalid</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Timer was closed</errorcode>
 * <result>Error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTimerClose',`(RTS_HANDLE hTimer)')

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
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTimerStart',`(RTS_HANDLE hTimer, unsigned long ulType)')

/**
 * <description> This function stops a timer </description>
 * <param name="hTimer" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERHANDLE]">Handle of the timer</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">hTimer is invalid</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Timer was stopped</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Timer could not be stopped</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">Feature is not implemented</errorcode>
 * <result>Error Code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTimerStop',`(RTS_HANDLE hTimer)')

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
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTimerGetInterval',`(RTS_HANDLE hTimer, RTS_SYSTIME *ptIntervalNs)')

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
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTimerSetInterval',`(RTS_HANDLE hTimer, RTS_SYSTIME tIntervalNs)')

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
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTimerGetTimeStamp',`(RTS_HANDLE hTimer, RTS_SYSTIME *ptTimestampNs)')

/**
 * <description> This function returns the maximal number of timers </description>
 * <param name="pulMaxTimer" type="OUT">Number of Timers</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">pulMaxTimer is invalid</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">pulMaxTimer returned successfully</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">pulMaxTimer could not be returned</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">Feature is not implemented</errorcode>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysTimerMaxTimer',`(RTS_UI32 *pulMaxTimers)')

/**
 * <description> This function looks for timers with the given properties </description>
 * <param name="ulPriority" type="IN" range="[0..(SYSTIMER_NUM_OF_TIMER_PRIOS - 1),SYSTIMER_NUM_OF_TIMER_PRIOS]">Priority of the timer</param>
 * <param name="tInterval" type="IN" range="[RTS_RANGE_OF_UINT64]">Interval of the timer</param>
 * <param name="pResult" type="OUT">Result pointer containing the error code. Might be NULL. </param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Found existing Timer</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NO_OBJECT">Found no Timer</errorcode>
 * <result>Handle to the searched timer or RTS_INVALID_HANDLE</result>
 */
DEF_STATICITF_API(`RTS_HANDLE',`CDECL',`SysTimerExistsTimer',`(unsigned long ulPriority, RTS_SYSTIME tInterval, RTS_RESULT* pResult)')

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
DEF_HANDLEITF_API(`unsigned int',`CDECL',`SysTimerFitTimer',`(RTS_HANDLE hTimer, unsigned long ulPriority, RTS_SYSTIME tInterval, RTS_RESULT *pResult)')

/**
 * <description> Get the minimum resolution of the timer </description>
 * <param name="hTimer" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERHANDLE]">Handle of the timer</param>
 * <param name="ptMinResolutionNs" type="OUT">Minimum timer resolution in nanoseconds</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">hTimer or ptMinResolutionNs is invalid</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Could get min resolution</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Could not get min resolution</errorcode>
 * <result>Error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTimerGetMinResolution',`(RTS_HANDLE hTimer, RTS_SYSTIME *ptMinResolutionNs)')

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
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTimerGetContext',`(RTS_HANDLE hTimer, RegContext *pContext)')

/**
 * <description> Calls the corresponding exception handler of the timer.</description>
 * <param name="hTimerHandle" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERHANDLE]">Handle to timer</param>
 * <param name="ulException" type="IN" range="[RTS_RANGE_OF_ULONG]">Rts standard exception</param>
 * <param name="Context" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_CONTEXT]">Context to detect the code location where the exception occurred</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Exception was successfully handled</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">No Timer found or Exception Handler returned ERR_FAILED</errorcode>
 * <result>ERR_OK</result>
 */
DEF_STATICITF_API(`RTS_RESULT',`CDECL',`SysTimerGenerateException',`(RTS_HANDLE hTimerHandle, RTS_UI32 ulException, RegContext Context)')

/**
 * <description> Sets the Callback Parameter </description>
 * <param name="hTimer" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERHANDLE]">Handle of the timer</param>
 * <param name="hParam" type="IN" range="[RTS_INVALID_HANDLE,VALID_HPARAM]">Parameter for callback routine</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Callback Parameter was successfully handled</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">hTimer invalid</errorcode>
 * <result>Error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTimerSetCallbackParameter',`(RTS_HANDLE hTimer, RTS_HANDLE hParam)')

/**
 * <description> With this function the specified function is reseted (Needed for CmpScheduleTimer) </description>
 * <param name="hTimer" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERHANDLE]">Handle of the timer to reset</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">No error occured</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Setting Priority failed</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">hTimer invalid</errorcode>
 * <result>Error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTimerSetResetFollowing',`(RTS_HANDLE hTimer)')

/**
 * <description> Register the base pointer of the main routine.</description>
 * <param name="pulBP" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_BASEPOINTER]">base pointer of main</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">pulBP is invalid</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">pulBP was successful registered</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">pulBP could not be registered</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">Feature is not implemented</errorcode>
 * <result>ERR_OK</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysTimerRegisterBasePointer',`(RTS_UINTPTR ulBP)')

/**
 * <description>Get first registered timer object</description>
 * <param name="pResult" type="OUT">Result pointer containing the error code. Might be NULL. </param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Successfully found first Timer</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NO_OBJECT">No Timer found</errorcode>
 * <result>Handle to first timer object</result>
 */
DEF_ITF_API2(`RTS_HANDLE',`CDECL',`SysTimerGetFirst',`(RTS_RESULT *pResult)')

/**
 * <description>Get next registered timer object</description>
 * <param name="hTimerPrev" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERINFOHANDLE]">Handle to previous timer object</param>
 * <param name="pResult" type="OUT">Result pointer containing the error code. Might be NULL. </param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Successfully found next Timer</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NO_OBJECT">No Timer found</errorcode>
 * <result>Handle to next timer object</result>
 */
DEF_ITF_API2(`RTS_HANDLE',`CDECL',`SysTimerGetNext',`(RTS_HANDLE hTimerPrev, RTS_RESULT *pResult)')

/**
 * <description>Call the registered callback handler with the corresponding hParam. IEC- and C-handlers are supported.</description>
 * <param name="hTimer" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERHANDLE]">Secified timer object</param>
 * <parampseudo name="pTimer->bIECFunction" type="IN" range="[RTS_RANGE_OF_INT]">Secified timer object</parampseudo>
 * <parampseudo name="bFuncCalled" type="OUT">Function call expected</parampseudo>
 * <result></result>
 */
DEF_ITF_API(`void',`CDECL',`SysTimerCallCallback',`(SYS_TIMER_INFO *pTimer)')

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
DEF_ITF_API(`RTS_HANDLE',`CDECL',`SysTimerGetCurrent',`(RTS_RESULT *pResult)')

/**
 * <description>
 * <p>Returns the timer info of the specified timer</p>
 * </description> 
 * <param name="hTimer" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TIMERHANDLE]">Secified timer object</param>
 * <param name="pResult" type="OUT">Result pointer containing the error code. Might be NULL. </param> 
 * <result>Pointer to the SYS_TIMER_INFO structure or NULL if failed</result>
 * 
 */
DEF_ITF_API(`SYS_TIMER_INFO *',`CDECL',`SysTimerGetInfo',`(RTS_HANDLE hTimer, RTS_RESULT *pResult)')

#ifdef __cplusplus
}
#endif
