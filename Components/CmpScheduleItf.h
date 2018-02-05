 /**
 * <interfacename>CmpSchedule</interfacename>
 * <description> 
 *	Interface of the scheduler.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPSCHEDULEITF_H_
#define _CMPSCHEDULEITF_H_

#include "CmpStd.h"

 

 




#include "CmpIecTaskItf.h"
#include "SysCpuMultiCoreItf.h"

#define CMD_INIT				0
#define CMD_TICK				1
#define CMD_WAIT				2
#define CMD_DEBUG_LOOP			3
#define CMD_TIMESLICE_BEGIN		4
#define CMD_TIMESLICE_END		5

/**
 * <category>Stack size</category>
 * <description>Specifies the stack size of an IEC task of the timer scheduler. 0 is the default size of the operating system or environment.</description>
 */
#ifndef CMPSCHEDULE_IECTASK_STACK_SIZE
	#define CMPSCHEDULE_IECTASK_STACK_SIZE		0
#endif

/**
 * <category>Compiler switch</category>
 * <description>
 *	Compiler switches to enable/disable single features in the component.
 * </description>
 * <element name="CMPSCHEDULE_DISABLE_TASK_WAKEUP_ON_CYCLE_END">Switch to disable calling the scheduler at each IEC task cycle end once more to reduce processor load</element>
 */
   

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to set priority of the scheduler. INT type.
 * </description>
 */
#define SCHEDULEKEY_INT_SCHEDULER_PRIORITY				"SchedulerPriority"
#ifndef SCHEDULEKEY_INT_SCHEDULER_PRIORITY_DEFAULT
	#define SCHEDULEKEY_INT_SCHEDULER_PRIORITY_DEFAULT		0		
#endif

/**
 * <description>
 *	Set the interval in microseconds of the scheduler. INT type.
 * </description>
 */
#define SCHEDULEKEY_INT_SCHEDULER_INTERVAL_US			"SchedulerInterval"
#ifndef SCHEDULEKEY_INT_SCHEDULER_INTERVAL_DEFAULT
	#define SCHEDULEKEY_INT_SCHEDULER_INTERVAL_DEFAULT	INT32_C(1000)
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Enable the processor load measurement of all plc tasks. If the processor load should be limited, you can conifure this with the setting "ProcessorLoad.Maximum". 
 * </description>
 */
#define SCHEDULEKEY_INT_PROCESSOR_LOAD_ENABLE					"ProcessorLoad.Enable"
#ifndef SCHEDULEVALUE_INT_PROCESSOR_LOAD_ENABLE_DEFAULT
	#define SCHEDULEVALUE_INT_PROCESSOR_LOAD_ENABLE_DEFAULT		1
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Set maximum processor load of all plc tasks.
 *  If maximum is reached, either a watchdog exception is generated (default) or
 *  timelicing is started (see setting [Timelicing.StartOnProcessorLoad]).
 *  Value: 10..100% possible. 0: feature is diabled.
 *  Default: 0 (Disabled)
 * </description>
 */
#define SCHEDULEKEY_INT_PROCESSOR_LOAD_MAX						"ProcessorLoad.Maximum"
#ifndef SCHEDULEKEY_INT_PROCESSOR_LOAD_MAX_DEFAULT
	#define SCHEDULEKEY_INT_PROCESSOR_LOAD_MAX_DEFAULT			0
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Set the interval of the processor load measurement in milliseconds. During this interval, the processorload
 *	will be added up.
 * </description>
 */
#define SCHEDULEKEY_INT_PROCESSOR_LOAD_INTERVAL					"ProcessorLoad.Interval"
#ifndef SCHEDULEKEY_INT_PROCESSOR_LOAD_INTERVAL_DEFAULT
	#define SCHEDULEKEY_INT_PROCESSOR_LOAD_INTERVAL_DEFAULT		INT32_C(1000)
#endif


/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 *	Setting to set the timeslice mode of the scheduler
 *  Default: None
 * </description>
 */
#define SCHEDULEKEY_STRING_TIMESLICING_MODE				"Timeslicing.Mode"
#define SCHEDULEVALUE_STRING_TIMESLICING_MODE_NONE		"None"
#define SCHEDULEVALUE_STRING_TIMESLICING_MODE_INTERNAL	"Internal"
#define SCHEDULEVALUE_STRING_TIMESLICING_MODE_EXTERNAL	"External"
#define SCHEDULEVALUE_STRING_TIMESLICING_MODE_DEFAULT	SCHEDULEVALUE_STRING_TIMESLICING_MODE_NONE

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *  Setting to set a fix timeslice in % for all plc tasks
 *  Value: 10..90% possible. 0: feature is diabled.
 *  Default: 0 (disabled)
 * </description>
 */
#define SCHEDULEKEY_INT_TIMESLICING_PLCSLICE_PERCENT			"Timeslicing.PlcSlicePercent"
#define SCHEDULEKEY_INT_TIMESLICING_PLCSLICE_PERCENT_DEFAULT	0

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *  Setting to set a fix timeslice in microseconds for all plc tasks
 *  0: feature is diabled (default)
 * </description>
 */
#define SCHEDULEKEY_INT_TIMESLICING_PLCSLICE_US			"Timeslicing.PlcSliceUs"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *  Setting to set an option, if timeslicing should be started automatically,
 *  after the MaxProcessorLoad is reached (see setting [MaxProcessorLoad])
 *  0: Feature is diabled, 1: Feature is enabled
 *  Default: 0 (disabled)
 * </description>
 */
#define SCHEDULEKEY_INT_TIMESLICING_START_ON_PROCESSORLOAD		"Timeslicing.StartOnProcessorLoad"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * </description>
 */
#define SCHEDULETIMERKEY_USE_WATCHDOG_TIMER					"UseWatchdogTimer"
#ifndef SCHEDULETIMERVALUE_USE_WATCHDOG_TIMER_DEFAULT
	#define SCHEDULETIMERVALUE_USE_WATCHDOG_TIMER_DEFAULT	1
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to enable the logger for the scheduler
 * </description>
 */
#define SCHEDULEKEY_INT_ENABLE_LOGGER					"EnableLogger"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Sleep time of a freewheeling IEC task at the end of its cycle.
 *	By default (if this setting is -1), (100% - SCHEDULEKEY_INT_PROCESSOR_LOAD_MAX) of the real cycle time of a freewheeling task is assumed for sleep.
 *	Example:
 *	- This setting is -1
 *	- Execution time of the freewheeling task is 10ms
 *	-> 20% of 10ms is the sleep time => 2ms sleep at the end of its cycle
 *	NOTE:
 *	Can be configured to 0 only in combination with internal or external timeslicing! In this case, the task can be running forever, but is
 *	interrupted only by timeslicing. Be shure, that no other IEC task is running at a lower priority as this task!
 * </description>
 */
#define SCHEDULEKEY_INT_FREEWHEELING_CYCLETIME_US			"Task.Freewheeling.Cycletime"
#ifndef SCHEDULEKEY_INT_FREEWHEELING_CYCLETIME_DEFAULT
	#define SCHEDULEKEY_INT_FREEWHEELING_CYCLETIME_DEFAULT	INT32_C(-1)
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * OBSOLETE: USE THE FOLLOWING SETTING INSTEAD:	[Scheduling.Mode=Tick]
 * Setting for the multitasking scheduler, to ignore the microsecond time and always use the 
 * tick resolution for decision if cyclic IEC tasks must be activated
 *  0: Microsecond scheduling is used [Default]
 *  1: Tick based scheduling (no usage of microseconds).
 *		NOTE: In this case, the scheduler interval must be correctly specified in setting [SchedulerInterval]!
 * </description>
 */
#define SCHEDULEKEY_DONT_USE_MICROSECOND_TIMING					"DontUseMicrosecondTiming"
#ifndef SCHEDULEVALUE_DONT_USE_MICROSECOND_TIMING_DEFAULT
	#define SCHEDULEVALUE_DONT_USE_MICROSECOND_TIMING_DEFAULT	0
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 * Scheduling mode. Is used only for CmpSchedule (not supported in CmpScheduleEmbedded and CmpScheduleTimer)!
 * o MicroSecond: Microsecond scheduling is used [Default]
 * o Tick: Tick based scheduling (no usage of microseconds).
 *		NOTE: In this case, the scheduler interval must be correctly specified in setting [SchedulerInterval]!
 * o OSScheduler: The operating system scheduler can schedule the cyclic tasks in realtime. In this case the RTS-scheduler does nothing.
 *		The RTS-scheduler supervises only the iEC tasks for an endless loop by default (see setting Scheduling.TaskSupervisor=ScheduleTick).
 *		To disable the RTS-scheduler completely, use the corresponding setting Scheduling.TaskSupervisor=WatchdogTimer.
 * </description>
 */
#define SCHEDULEKEY_STRING_SCHEDULING_MODE							"Scheduling.Mode"
#define SCHEDULEVALUE_STRING_SCHEDULING_MODE_MICROSECOND			"MicroSecond"
#define SCHEDULEVALUE_STRING_SCHEDULING_MODE_TICK					"Tick"
#define SCHEDULEVALUE_STRING_SCHEDULING_MODE_OS_SCHEDULE			"OSScheduler"
#ifndef SCHEDULEVALUE_STRING_SCHEDULING_MODE_DEFAULT
	#define SCHEDULEVALUE_STRING_SCHEDULING_MODE_DEFAULT			SCHEDULEVALUE_STRING_SCHEDULING_MODE_MICROSECOND
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 * Scheduling task supervisor mode. Is used only for CmpSchedule (not supported in CmpScheduleEmbedded and CmpScheduleTimer)!
 * o ScheduleTick: The scheduler supervises all IEC tasks at every schedule tick for an expired watchdog [Default]. Scheduler runs in a timer.
 * o ScheduleTickTask: The scheduler supervises all IEC tasks at every schedule tick for an expired watchdog. Here the scheduler is running in a task.
 * o WatchdogTimer: All IEC tasks are supervised by a watchdog timer. So the RTS-schedule tick is disabled and does not consume any resources (tickless)
 * </description>
 */
#define SCHEDULEKEY_STRING_SCHEDULING_TASKSUPERVISOR					"Scheduling.TaskSupervisor"
#define SCHEDULEVALUE_STRING_SCHEDULING_SUPERVISOR_SCHEDULETICK			"ScheduleTick"
#define SCHEDULEVALUE_STRING_SCHEDULING_SUPERVISOR_WATCHDOGTIMER		"WatchdogTimer"
#define SCHEDULEVALUE_STRING_SCHEDULING_SUPERVISOR_SCHEDULETICK_TASK	"ScheduleTickTask"
#ifndef SCHEDULEVALUE_STRING_SCHEDULING_SUPERVISOR_DEFAULT
	/* Only for backward compatibility */
	#ifdef CMPSCHEDULE_DISABLE_SCHEDULE_TICK
		#define SCHEDULEVALUE_STRING_SCHEDULING_SUPERVISOR_DEFAULT		SCHEDULEVALUE_STRING_SCHEDULING_SUPERVISOR_WATCHDOGTIMER
	#else
		#define SCHEDULEVALUE_STRING_SCHEDULING_SUPERVISOR_DEFAULT		SCHEDULEVALUE_STRING_SCHEDULING_SUPERVISOR_SCHEDULETICK
	#endif
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * Setting to disable the new watchdog feature to detected omitted cycles of a task. THis can be activated for backward compatibility, if feature
 * makes a problem in existing systems.
 * NOTE:
 * Setting is ony available for CmpSchedule (not in CmpScheduleTimer and CmpScheduleEmbedded)!
 *  0: Omitted cycle watchdog is enabled [Default]
 *  1: Disable omitted cycle watchdog
 * </description>
 */
#define SCHEDULEKEY_DISABLE_OMITTED_CYCLE_WATCHDOG						"DisableOmittedCycleWatchdog"
#ifndef SCHEDULEKEY_DISABLE_OMITTED_CYCLE_WATCHDOG_DEFAULT
	#define SCHEDULEKEY_DISABLE_OMITTED_CYCLE_WATCHDOG_DEFAULT			0
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * Setting to specify the watchdog time in [us] that is added as a constant to the omitted cycle watchdog during OnlineChange.
 *
 * ATTENTION:
 *	This should only be used on systems to inhibit a watchdog exception for longer processing online change code!
 *	Setting must only be used for systems, that has sometimes a serious problem with watchdog exception during OnlineChange, but the specified jitter can be accepted!
 *
 * NOTES:
 * - Setting is ony available for CmpSchedule (not in CmpScheduleTimer and CmpScheduleEmbedded)!
 * - 0=Standard omitted cycle watchdog time is used
 * </description>
 */
#define SCHEDULEKEY_INT_OMITTED_CYCLE_WATCHDOG_OC						"OmittedCycleWatchdog.OnlineChangeUs"
#ifndef SCHEDULEVALUE_INT_OMITTED_CYCLE_WATCHDOG_OC_DEFAULT
	#define SCHEDULEVALUE_INT_OMITTED_CYCLE_WATCHDOG_OC_DEFAULT			0
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * Setting to specify the multiplier of the schedule interval for the timeout of the supervisor (e.g. the hardware watchdog).
 * Default: 2 (timeout after expiration of the double of the scheduler interval).
 * </description>
 */
#define SCHEDULEKEY_INT_SUPERVISOR_TIMEOUT_MULTIPLIER					"SupervisorTimeoutMultiplier"
#ifndef SCHEDULEVALUE_INT_SUPERVISOR_TIMEOUT_MULTIPLIER_DEFAULT
	#define SCHEDULEVALUE_INT_SUPERVISOR_TIMEOUT_MULTIPLIER_DEFAULT		INT32_C(2)
#endif

/**
 * <category>OperationID</category>
 * <description>Operation ID for the supervision of the scheduler tick</description>
 * <param name="OPID_SchedulerTick" type="IN"></param>
 * <param name="OPID_SchedulerTick_Description" type="IN"></param>
 */
#define RTS_OPID_SchedulerTick								1
#define RTS_OPID_SchedulerTick_Description					"Scheduler Tick"

/**
 * <category>OperationID</category>
 * <description>Operation ID for the supervision of the watchdog timer</description>
 * <param name="RTS_OPID_WatchdogTimer" type="IN"></param>
 * <param name="RTS_OPID_WatchdogTimer_Description" type="IN"></param>
 */
#define RTS_OPID_WatchdogTimer								2
#define RTS_OPID_WatchdogTimer_Description					"Watchdog Timer"

/**
 * <category>Static defines</category>
 * <description>Sleep time in breakpoint loop in milliseconds</description>
 */
#ifndef SCHED_DEBUG_LOOP_CYCLE_TIME
	#define SCHED_DEBUG_LOOP_CYCLE_TIME						100
#endif


#ifndef CMPSCHEDULETIMER_WATCHDOG_PRIORITY
	#define CMPSCHEDULETIMER_WATCHDOG_PRIORITY				0
#endif

#ifndef CMPSCHEDULETIMER_WATCHDOG_INTERVAL
	#define CMPSCHEDULETIMER_WATCHDOG_INTERVAL				1000000 /* 1 ms */
#endif

/**
 * <category>Static defines</category>
 * <description>There is a new feature to avoid possible deadlocks in external library calls if a watchdog exception occurred.
 *	This feature can be activated in the device description by the following setting:
 *		Targetsetting:  "codegenerator\\breakpoint-mark-after-external-call"
 *	If you activate this feature we do not suspend the IecTask directly in the exernal library call, but we set a breakpoint right after returning from this external library
 *	call to driver out of this code in a defined way.
 *  And this define is the number of code bytes after returning from the external library call to look maximum for the NOP code.
 * </description>
 */
#ifndef CMPSCHEDULE_SEARCH_NOP_AFTER_EXTERNAL_CALL
	#define CMPSCHEDULE_SEARCH_NOP_AFTER_EXTERNAL_CALL		21
#endif


/**
 * <category>Features</category>
 * <type>Int</type>
 * <description>
 *	Supported features of the scheduler
 * </description>
 */
#define SCHEDULE_FEATURE_RESET_ON_BREAKPOINT	0x00000001
#define SCHEDULE_FEATURE_INTERNAL_TIMESLICING	0x00000002
#define SCHEDULE_FEATURE_EXTERNAL_TIMESLICING	0x00000003
#define SCHEDULE_FEATURE_PROCESSOR_LOAD_CHECK	0x00000004


/**
 * <category>Event parameter</category>
 * <element name="pTaskDesc" type="IN">Pointer to the task description of the assigned IEC task</element>
 * <element name="hEvent" type="IN">Handle to the event, that can be used to trigger the task by SysEventSet(hEvent)</element>
 */
typedef struct
{
	Task_Desc* pTaskDesc;
	RTS_HANDLE hEvent;
} EVTPARAM_CmpSchedule;
#define EVTPARAMID_CmpSchedule		0x0001
#define EVTVERSION_CmpSchedule		0x0001

/**
 * <category>Events</category>
 * <description>Event is sent, after an IEC-task was created at application download</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpSchedule</param>
 */
#define EVT_TaskCreateDone									MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Events</category>
 * <description>Event is sent, before an IEC-task will be deleted at application download</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpSchedule</param>
 */
#define EVT_PrepareTaskDelete								MAKE_EVENTID(EVTCLASS_INFO, 2)

/**
 * <category>Events</category>
 * <description>Event is sent, after an IEC-task, that is external event triggered was created</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpSchedule</param>
 */
#define EVT_ExternalEventTaskCreateDone						MAKE_EVENTID(EVTCLASS_INFO, 3)

/**
 * <category>Events</category>
 * <description>Event is sent, before an IEC-task, that is external event triggered will be deleted</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpSchedule</param>
 */
#define EVT_PrepareExternalEventTaskDelete					MAKE_EVENTID(EVTCLASS_INFO, 4)


/**
 * <category>Event parameter</category>
 * <element name="pSchedTime" type="IN">Actual time value of the scheduler, that is used for activating the tasks</element>
 */
typedef struct
{
	RTS_SYSTIME *pSchedTime;
	int nScheduleIntervalUs;
} EVTPARAM_CmpScheduleTick;
#define EVTPARAMID_CmpScheduleTick	0x0002
#define EVTVERSION_CmpScheduleTick	0x0002

/**
 * <category>Events</category>
 * <description>Event is sent always in the schedule tick</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpScheduleTick</param>
 */
#define EVT_ScheduleTick									MAKE_EVENTID(EVTCLASS_INFO, 5)

/**
 * <category>Events</category>
 * <description>Event is sent always, if no IEC task is active (task gap)</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpScheduleTick</param>
 */
#define EVT_ScheduleTaskGap									MAKE_EVENTID(EVTCLASS_INFO, 6)


/**
* <category>Event parameter</category>
* <element name="pSchedTime" type="IN">Actual time value of the scheduler, that is used for activating the tasks</element>
* <element name="iScheduleIntervalUs" type="IN">Schedule interval in microseconds</element>
* <element name="pApp" type="IN">Pointer to the application for which the task gap has been detected</element>
*/
typedef struct
{
	RTS_SYSTIME *pSchedTime;
	RTS_I32 iScheduleIntervalUs;
	APPLICATION *pApp;
} EVTPARAM_CmpScheduleTaskGapApp;
#define EVTPARAMID_CmpScheduleTaskGapApp	0x0003
#define EVTVERSION_CmpScheduleTaskGapApp	0x0001

/**
 * <category>Events</category>
 * <description>
 * Event is sent always for each application, if no IEC task in that application is active (task gap).
 * The synchronization for the application has to be done in the callback of the event.
 * </description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpScheduleTaskGapApp</param>
 */
#define EVT_ScheduleTaskGapApp								MAKE_EVENTID(EVTCLASS_INFO, 7)

/**
 * <SIL2/>
 * <category>Typedef</category>
 * <description><p>SIL2 life counter for safe comm cycle hook</p>
 * </description>
 */
#ifdef RTS_SIL2
extern RTS_UI32 g_RTS_SIL2_Cycle_LifeCounter_CmpScheduleTimer;
#endif


/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  <description>Is called to get the schedule handle of the current running task</description>
 *  <param name="pResult" type="OUT">ERR_OK or Error code</param>
 *  <result>Handle to the current running task or RTS_INVALID_HANDLE if failed</result>
 */
typedef struct tagschedgetcurrenttask_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE SchedGetCurrentTask;	/* VAR_OUTPUT */	
} schedgetcurrenttask_struct;

void CDECL CDECL_EXT schedgetcurrenttask(schedgetcurrenttask_struct *p);
typedef void (CDECL CDECL_EXT* PFSCHEDGETCURRENTTASK_IEC) (schedgetcurrenttask_struct *p);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDGETCURRENTTASK_NOTIMPLEMENTED)
	#define USE_schedgetcurrenttask
	#define EXT_schedgetcurrenttask
	#define GET_schedgetcurrenttask(fl)  ERR_NOTIMPLEMENTED
	#define CAL_schedgetcurrenttask(p0) 
	#define CHK_schedgetcurrenttask  FALSE
	#define EXP_schedgetcurrenttask  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_schedgetcurrenttask
	#define EXT_schedgetcurrenttask
	#define GET_schedgetcurrenttask(fl)  CAL_CMGETAPI( "schedgetcurrenttask" ) 
	#define CAL_schedgetcurrenttask  schedgetcurrenttask
	#define CHK_schedgetcurrenttask  TRUE
	#define EXP_schedgetcurrenttask  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgetcurrenttask", (RTS_UINTPTR)schedgetcurrenttask, 1, 0x4896EDD1, 0x03050900) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_schedgetcurrenttask
	#define EXT_schedgetcurrenttask
	#define GET_schedgetcurrenttask(fl)  CAL_CMGETAPI( "schedgetcurrenttask" ) 
	#define CAL_schedgetcurrenttask  schedgetcurrenttask
	#define CHK_schedgetcurrenttask  TRUE
	#define EXP_schedgetcurrenttask  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgetcurrenttask", (RTS_UINTPTR)schedgetcurrenttask, 1, 0x4896EDD1, 0x03050900) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleschedgetcurrenttask
	#define EXT_CmpScheduleschedgetcurrenttask
	#define GET_CmpScheduleschedgetcurrenttask  ERR_OK
	#define CAL_CmpScheduleschedgetcurrenttask  schedgetcurrenttask
	#define CHK_CmpScheduleschedgetcurrenttask  TRUE
	#define EXP_CmpScheduleschedgetcurrenttask  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgetcurrenttask", (RTS_UINTPTR)schedgetcurrenttask, 1, 0x4896EDD1, 0x03050900) 
#elif defined(CPLUSPLUS)
	#define USE_schedgetcurrenttask
	#define EXT_schedgetcurrenttask
	#define GET_schedgetcurrenttask(fl)  CAL_CMGETAPI( "schedgetcurrenttask" ) 
	#define CAL_schedgetcurrenttask  schedgetcurrenttask
	#define CHK_schedgetcurrenttask  TRUE
	#define EXP_schedgetcurrenttask  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgetcurrenttask", (RTS_UINTPTR)schedgetcurrenttask, 1, 0x4896EDD1, 0x03050900) 
#else /* DYNAMIC_LINK */
	#define USE_schedgetcurrenttask  PFSCHEDGETCURRENTTASK_IEC pfschedgetcurrenttask;
	#define EXT_schedgetcurrenttask  extern PFSCHEDGETCURRENTTASK_IEC pfschedgetcurrenttask;
	#define GET_schedgetcurrenttask(fl)  s_pfCMGetAPI2( "schedgetcurrenttask", (RTS_VOID_FCTPTR *)&pfschedgetcurrenttask, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x4896EDD1, 0x03050900)
	#define CAL_schedgetcurrenttask  pfschedgetcurrenttask
	#define CHK_schedgetcurrenttask  (pfschedgetcurrenttask != NULL)
	#define EXP_schedgetcurrenttask   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgetcurrenttask", (RTS_UINTPTR)schedgetcurrenttask, 1, 0x4896EDD1, 0x03050900) 
#endif


/**
 *  <description>
 * 	Is called to get the number of all registerd IEC tasks in the scheduler.
 *  </description>	
 *  <param name="pApp" type="IN">If an application is specified, only the tasks of this application is returned.
 * 	If NULL, number of all tasks is returned.
 *  </param>
 *  <param name="pResult" type="OUT">ERR_OK or Error code</param>
 *  <result>Number of tasks</result>
 */
typedef struct tagschedgetnumoftasks_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_DINT SchedGetNumOfTasks;	/* VAR_OUTPUT */	
} schedgetnumoftasks_struct;

void CDECL CDECL_EXT schedgetnumoftasks(schedgetnumoftasks_struct *p);
typedef void (CDECL CDECL_EXT* PFSCHEDGETNUMOFTASKS_IEC) (schedgetnumoftasks_struct *p);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDGETNUMOFTASKS_NOTIMPLEMENTED)
	#define USE_schedgetnumoftasks
	#define EXT_schedgetnumoftasks
	#define GET_schedgetnumoftasks(fl)  ERR_NOTIMPLEMENTED
	#define CAL_schedgetnumoftasks(p0) 
	#define CHK_schedgetnumoftasks  FALSE
	#define EXP_schedgetnumoftasks  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_schedgetnumoftasks
	#define EXT_schedgetnumoftasks
	#define GET_schedgetnumoftasks(fl)  CAL_CMGETAPI( "schedgetnumoftasks" ) 
	#define CAL_schedgetnumoftasks  schedgetnumoftasks
	#define CHK_schedgetnumoftasks  TRUE
	#define EXP_schedgetnumoftasks  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgetnumoftasks", (RTS_UINTPTR)schedgetnumoftasks, 1, 0x8D47FCA0, 0x03050900) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_schedgetnumoftasks
	#define EXT_schedgetnumoftasks
	#define GET_schedgetnumoftasks(fl)  CAL_CMGETAPI( "schedgetnumoftasks" ) 
	#define CAL_schedgetnumoftasks  schedgetnumoftasks
	#define CHK_schedgetnumoftasks  TRUE
	#define EXP_schedgetnumoftasks  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgetnumoftasks", (RTS_UINTPTR)schedgetnumoftasks, 1, 0x8D47FCA0, 0x03050900) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleschedgetnumoftasks
	#define EXT_CmpScheduleschedgetnumoftasks
	#define GET_CmpScheduleschedgetnumoftasks  ERR_OK
	#define CAL_CmpScheduleschedgetnumoftasks  schedgetnumoftasks
	#define CHK_CmpScheduleschedgetnumoftasks  TRUE
	#define EXP_CmpScheduleschedgetnumoftasks  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgetnumoftasks", (RTS_UINTPTR)schedgetnumoftasks, 1, 0x8D47FCA0, 0x03050900) 
#elif defined(CPLUSPLUS)
	#define USE_schedgetnumoftasks
	#define EXT_schedgetnumoftasks
	#define GET_schedgetnumoftasks(fl)  CAL_CMGETAPI( "schedgetnumoftasks" ) 
	#define CAL_schedgetnumoftasks  schedgetnumoftasks
	#define CHK_schedgetnumoftasks  TRUE
	#define EXP_schedgetnumoftasks  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgetnumoftasks", (RTS_UINTPTR)schedgetnumoftasks, 1, 0x8D47FCA0, 0x03050900) 
#else /* DYNAMIC_LINK */
	#define USE_schedgetnumoftasks  PFSCHEDGETNUMOFTASKS_IEC pfschedgetnumoftasks;
	#define EXT_schedgetnumoftasks  extern PFSCHEDGETNUMOFTASKS_IEC pfschedgetnumoftasks;
	#define GET_schedgetnumoftasks(fl)  s_pfCMGetAPI2( "schedgetnumoftasks", (RTS_VOID_FCTPTR *)&pfschedgetnumoftasks, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x8D47FCA0, 0x03050900)
	#define CAL_schedgetnumoftasks  pfschedgetnumoftasks
	#define CHK_schedgetnumoftasks  (pfschedgetnumoftasks != NULL)
	#define EXP_schedgetnumoftasks   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgetnumoftasks", (RTS_UINTPTR)schedgetnumoftasks, 1, 0x8D47FCA0, 0x03050900) 
#endif


/**
 *  <description>Returns the processor load of all IEC tasks</description>
 *  <param name="pResult" type="OUT">Pointer to error code</param>
 *  <result>Processor load in percent</result>
 */
typedef struct tagschedgetprocessorload_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_UDINT SchedGetProcessorLoad;	/* VAR_OUTPUT */	
} schedgetprocessorload_struct;

void CDECL CDECL_EXT schedgetprocessorload(schedgetprocessorload_struct *p);
typedef void (CDECL CDECL_EXT* PFSCHEDGETPROCESSORLOAD_IEC) (schedgetprocessorload_struct *p);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDGETPROCESSORLOAD_NOTIMPLEMENTED)
	#define USE_schedgetprocessorload
	#define EXT_schedgetprocessorload
	#define GET_schedgetprocessorload(fl)  ERR_NOTIMPLEMENTED
	#define CAL_schedgetprocessorload(p0) 
	#define CHK_schedgetprocessorload  FALSE
	#define EXP_schedgetprocessorload  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_schedgetprocessorload
	#define EXT_schedgetprocessorload
	#define GET_schedgetprocessorload(fl)  CAL_CMGETAPI( "schedgetprocessorload" ) 
	#define CAL_schedgetprocessorload  schedgetprocessorload
	#define CHK_schedgetprocessorload  TRUE
	#define EXP_schedgetprocessorload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgetprocessorload", (RTS_UINTPTR)schedgetprocessorload, 1, 0xD458FC16, 0x03050900) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_schedgetprocessorload
	#define EXT_schedgetprocessorload
	#define GET_schedgetprocessorload(fl)  CAL_CMGETAPI( "schedgetprocessorload" ) 
	#define CAL_schedgetprocessorload  schedgetprocessorload
	#define CHK_schedgetprocessorload  TRUE
	#define EXP_schedgetprocessorload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgetprocessorload", (RTS_UINTPTR)schedgetprocessorload, 1, 0xD458FC16, 0x03050900) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleschedgetprocessorload
	#define EXT_CmpScheduleschedgetprocessorload
	#define GET_CmpScheduleschedgetprocessorload  ERR_OK
	#define CAL_CmpScheduleschedgetprocessorload  schedgetprocessorload
	#define CHK_CmpScheduleschedgetprocessorload  TRUE
	#define EXP_CmpScheduleschedgetprocessorload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgetprocessorload", (RTS_UINTPTR)schedgetprocessorload, 1, 0xD458FC16, 0x03050900) 
#elif defined(CPLUSPLUS)
	#define USE_schedgetprocessorload
	#define EXT_schedgetprocessorload
	#define GET_schedgetprocessorload(fl)  CAL_CMGETAPI( "schedgetprocessorload" ) 
	#define CAL_schedgetprocessorload  schedgetprocessorload
	#define CHK_schedgetprocessorload  TRUE
	#define EXP_schedgetprocessorload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgetprocessorload", (RTS_UINTPTR)schedgetprocessorload, 1, 0xD458FC16, 0x03050900) 
#else /* DYNAMIC_LINK */
	#define USE_schedgetprocessorload  PFSCHEDGETPROCESSORLOAD_IEC pfschedgetprocessorload;
	#define EXT_schedgetprocessorload  extern PFSCHEDGETPROCESSORLOAD_IEC pfschedgetprocessorload;
	#define GET_schedgetprocessorload(fl)  s_pfCMGetAPI2( "schedgetprocessorload", (RTS_VOID_FCTPTR *)&pfschedgetprocessorload, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xD458FC16, 0x03050900)
	#define CAL_schedgetprocessorload  pfschedgetprocessorload
	#define CHK_schedgetprocessorload  (pfschedgetprocessorload != NULL)
	#define EXP_schedgetprocessorload   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgetprocessorload", (RTS_UINTPTR)schedgetprocessorload, 1, 0xD458FC16, 0x03050900) 
#endif


/**
 *  <description>
 * 	Function returns the handle to the task event. With this event a task can be activaed externally,
 * 	e.g. for external triggered event tasks. The event can be sent by SysEventSet(EventHandle);
 *  </description>	
 *  <param name="hSchedTask" type="IN">Scheduler task handle</param>
 *  <param name="pResult" type="OUT">ERR_OK or Error code</param>
 *  <result>Event handle. Can be used with SysEventSet(hEvent) of the SysEvent.library to wakeup the task</result>
 */
typedef struct tagschedgettaskeventbyhandle_struct
{
	RTS_IEC_HANDLE hSchedTask;			/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE SchedGetTaskEventByHandle;	/* VAR_OUTPUT */	
} schedgettaskeventbyhandle_struct;

void CDECL CDECL_EXT schedgettaskeventbyhandle(schedgettaskeventbyhandle_struct *p);
typedef void (CDECL CDECL_EXT* PFSCHEDGETTASKEVENTBYHANDLE_IEC) (schedgettaskeventbyhandle_struct *p);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDGETTASKEVENTBYHANDLE_NOTIMPLEMENTED)
	#define USE_schedgettaskeventbyhandle
	#define EXT_schedgettaskeventbyhandle
	#define GET_schedgettaskeventbyhandle(fl)  ERR_NOTIMPLEMENTED
	#define CAL_schedgettaskeventbyhandle(p0) 
	#define CHK_schedgettaskeventbyhandle  FALSE
	#define EXP_schedgettaskeventbyhandle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_schedgettaskeventbyhandle
	#define EXT_schedgettaskeventbyhandle
	#define GET_schedgettaskeventbyhandle(fl)  CAL_CMGETAPI( "schedgettaskeventbyhandle" ) 
	#define CAL_schedgettaskeventbyhandle  schedgettaskeventbyhandle
	#define CHK_schedgettaskeventbyhandle  TRUE
	#define EXP_schedgettaskeventbyhandle  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgettaskeventbyhandle", (RTS_UINTPTR)schedgettaskeventbyhandle, 1, 0xCF74EFE9, 0x03050900) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_schedgettaskeventbyhandle
	#define EXT_schedgettaskeventbyhandle
	#define GET_schedgettaskeventbyhandle(fl)  CAL_CMGETAPI( "schedgettaskeventbyhandle" ) 
	#define CAL_schedgettaskeventbyhandle  schedgettaskeventbyhandle
	#define CHK_schedgettaskeventbyhandle  TRUE
	#define EXP_schedgettaskeventbyhandle  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgettaskeventbyhandle", (RTS_UINTPTR)schedgettaskeventbyhandle, 1, 0xCF74EFE9, 0x03050900) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleschedgettaskeventbyhandle
	#define EXT_CmpScheduleschedgettaskeventbyhandle
	#define GET_CmpScheduleschedgettaskeventbyhandle  ERR_OK
	#define CAL_CmpScheduleschedgettaskeventbyhandle  schedgettaskeventbyhandle
	#define CHK_CmpScheduleschedgettaskeventbyhandle  TRUE
	#define EXP_CmpScheduleschedgettaskeventbyhandle  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgettaskeventbyhandle", (RTS_UINTPTR)schedgettaskeventbyhandle, 1, 0xCF74EFE9, 0x03050900) 
#elif defined(CPLUSPLUS)
	#define USE_schedgettaskeventbyhandle
	#define EXT_schedgettaskeventbyhandle
	#define GET_schedgettaskeventbyhandle(fl)  CAL_CMGETAPI( "schedgettaskeventbyhandle" ) 
	#define CAL_schedgettaskeventbyhandle  schedgettaskeventbyhandle
	#define CHK_schedgettaskeventbyhandle  TRUE
	#define EXP_schedgettaskeventbyhandle  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgettaskeventbyhandle", (RTS_UINTPTR)schedgettaskeventbyhandle, 1, 0xCF74EFE9, 0x03050900) 
#else /* DYNAMIC_LINK */
	#define USE_schedgettaskeventbyhandle  PFSCHEDGETTASKEVENTBYHANDLE_IEC pfschedgettaskeventbyhandle;
	#define EXT_schedgettaskeventbyhandle  extern PFSCHEDGETTASKEVENTBYHANDLE_IEC pfschedgettaskeventbyhandle;
	#define GET_schedgettaskeventbyhandle(fl)  s_pfCMGetAPI2( "schedgettaskeventbyhandle", (RTS_VOID_FCTPTR *)&pfschedgettaskeventbyhandle, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xCF74EFE9, 0x03050900)
	#define CAL_schedgettaskeventbyhandle  pfschedgettaskeventbyhandle
	#define CHK_schedgettaskeventbyhandle  (pfschedgettaskeventbyhandle != NULL)
	#define EXP_schedgettaskeventbyhandle   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgettaskeventbyhandle", (RTS_UINTPTR)schedgettaskeventbyhandle, 1, 0xCF74EFE9, 0x03050900) 
#endif


/**
 *  <description>
 * 	Function returns the task handle of a task specified by an index.
 *  </description>	
 *  <param name="pApp" type="IN">If an application is specified, only the task of this application is returned.
 * 	If NULL, the task with the index in all tasks i returned.
 *  </param>
 *  <param name="pResult" type="OUT">ERR_OK or Error code</param>
 *  <result>Handle to the task</result>
 */
typedef struct tagschedgettaskhandlebyindex_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_DINT nIndex;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE SchedGetTaskHandleByIndex;	/* VAR_OUTPUT */	
} schedgettaskhandlebyindex_struct;

void CDECL CDECL_EXT schedgettaskhandlebyindex(schedgettaskhandlebyindex_struct *p);
typedef void (CDECL CDECL_EXT* PFSCHEDGETTASKHANDLEBYINDEX_IEC) (schedgettaskhandlebyindex_struct *p);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDGETTASKHANDLEBYINDEX_NOTIMPLEMENTED)
	#define USE_schedgettaskhandlebyindex
	#define EXT_schedgettaskhandlebyindex
	#define GET_schedgettaskhandlebyindex(fl)  ERR_NOTIMPLEMENTED
	#define CAL_schedgettaskhandlebyindex(p0) 
	#define CHK_schedgettaskhandlebyindex  FALSE
	#define EXP_schedgettaskhandlebyindex  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_schedgettaskhandlebyindex
	#define EXT_schedgettaskhandlebyindex
	#define GET_schedgettaskhandlebyindex(fl)  CAL_CMGETAPI( "schedgettaskhandlebyindex" ) 
	#define CAL_schedgettaskhandlebyindex  schedgettaskhandlebyindex
	#define CHK_schedgettaskhandlebyindex  TRUE
	#define EXP_schedgettaskhandlebyindex  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgettaskhandlebyindex", (RTS_UINTPTR)schedgettaskhandlebyindex, 1, 0xA90D39FA, 0x03050900) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_schedgettaskhandlebyindex
	#define EXT_schedgettaskhandlebyindex
	#define GET_schedgettaskhandlebyindex(fl)  CAL_CMGETAPI( "schedgettaskhandlebyindex" ) 
	#define CAL_schedgettaskhandlebyindex  schedgettaskhandlebyindex
	#define CHK_schedgettaskhandlebyindex  TRUE
	#define EXP_schedgettaskhandlebyindex  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgettaskhandlebyindex", (RTS_UINTPTR)schedgettaskhandlebyindex, 1, 0xA90D39FA, 0x03050900) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleschedgettaskhandlebyindex
	#define EXT_CmpScheduleschedgettaskhandlebyindex
	#define GET_CmpScheduleschedgettaskhandlebyindex  ERR_OK
	#define CAL_CmpScheduleschedgettaskhandlebyindex  schedgettaskhandlebyindex
	#define CHK_CmpScheduleschedgettaskhandlebyindex  TRUE
	#define EXP_CmpScheduleschedgettaskhandlebyindex  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgettaskhandlebyindex", (RTS_UINTPTR)schedgettaskhandlebyindex, 1, 0xA90D39FA, 0x03050900) 
#elif defined(CPLUSPLUS)
	#define USE_schedgettaskhandlebyindex
	#define EXT_schedgettaskhandlebyindex
	#define GET_schedgettaskhandlebyindex(fl)  CAL_CMGETAPI( "schedgettaskhandlebyindex" ) 
	#define CAL_schedgettaskhandlebyindex  schedgettaskhandlebyindex
	#define CHK_schedgettaskhandlebyindex  TRUE
	#define EXP_schedgettaskhandlebyindex  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgettaskhandlebyindex", (RTS_UINTPTR)schedgettaskhandlebyindex, 1, 0xA90D39FA, 0x03050900) 
#else /* DYNAMIC_LINK */
	#define USE_schedgettaskhandlebyindex  PFSCHEDGETTASKHANDLEBYINDEX_IEC pfschedgettaskhandlebyindex;
	#define EXT_schedgettaskhandlebyindex  extern PFSCHEDGETTASKHANDLEBYINDEX_IEC pfschedgettaskhandlebyindex;
	#define GET_schedgettaskhandlebyindex(fl)  s_pfCMGetAPI2( "schedgettaskhandlebyindex", (RTS_VOID_FCTPTR *)&pfschedgettaskhandlebyindex, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xA90D39FA, 0x03050900)
	#define CAL_schedgettaskhandlebyindex  pfschedgettaskhandlebyindex
	#define CHK_schedgettaskhandlebyindex  (pfschedgettaskhandlebyindex != NULL)
	#define EXP_schedgettaskhandlebyindex   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgettaskhandlebyindex", (RTS_UINTPTR)schedgettaskhandlebyindex, 1, 0xA90D39FA, 0x03050900) 
#endif


/**
 *  <description>
 * 	Function returns the handle to the task specified by name.
 *  </description>	
 *  <param name="pszTaskName" type="IN">Task name</param>
 *  <param name="pResult" type="OUT">ERR_OK or Error code</param>
 *  <result>Scheduler task handle</result>
 */
typedef struct tagschedgettaskhandlebyname_struct
{
	RTS_IEC_STRING *pszTaskName;		/* VAR_IN_OUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE SchedGetTaskHandleByName;	/* VAR_OUTPUT */	
} schedgettaskhandlebyname_struct;

void CDECL CDECL_EXT schedgettaskhandlebyname(schedgettaskhandlebyname_struct *p);
typedef void (CDECL CDECL_EXT* PFSCHEDGETTASKHANDLEBYNAME_IEC) (schedgettaskhandlebyname_struct *p);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDGETTASKHANDLEBYNAME_NOTIMPLEMENTED)
	#define USE_schedgettaskhandlebyname
	#define EXT_schedgettaskhandlebyname
	#define GET_schedgettaskhandlebyname(fl)  ERR_NOTIMPLEMENTED
	#define CAL_schedgettaskhandlebyname(p0) 
	#define CHK_schedgettaskhandlebyname  FALSE
	#define EXP_schedgettaskhandlebyname  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_schedgettaskhandlebyname
	#define EXT_schedgettaskhandlebyname
	#define GET_schedgettaskhandlebyname(fl)  CAL_CMGETAPI( "schedgettaskhandlebyname" ) 
	#define CAL_schedgettaskhandlebyname  schedgettaskhandlebyname
	#define CHK_schedgettaskhandlebyname  TRUE
	#define EXP_schedgettaskhandlebyname  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgettaskhandlebyname", (RTS_UINTPTR)schedgettaskhandlebyname, 1, 0x0FBFD668, 0x03050900) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_schedgettaskhandlebyname
	#define EXT_schedgettaskhandlebyname
	#define GET_schedgettaskhandlebyname(fl)  CAL_CMGETAPI( "schedgettaskhandlebyname" ) 
	#define CAL_schedgettaskhandlebyname  schedgettaskhandlebyname
	#define CHK_schedgettaskhandlebyname  TRUE
	#define EXP_schedgettaskhandlebyname  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgettaskhandlebyname", (RTS_UINTPTR)schedgettaskhandlebyname, 1, 0x0FBFD668, 0x03050900) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleschedgettaskhandlebyname
	#define EXT_CmpScheduleschedgettaskhandlebyname
	#define GET_CmpScheduleschedgettaskhandlebyname  ERR_OK
	#define CAL_CmpScheduleschedgettaskhandlebyname  schedgettaskhandlebyname
	#define CHK_CmpScheduleschedgettaskhandlebyname  TRUE
	#define EXP_CmpScheduleschedgettaskhandlebyname  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgettaskhandlebyname", (RTS_UINTPTR)schedgettaskhandlebyname, 1, 0x0FBFD668, 0x03050900) 
#elif defined(CPLUSPLUS)
	#define USE_schedgettaskhandlebyname
	#define EXT_schedgettaskhandlebyname
	#define GET_schedgettaskhandlebyname(fl)  CAL_CMGETAPI( "schedgettaskhandlebyname" ) 
	#define CAL_schedgettaskhandlebyname  schedgettaskhandlebyname
	#define CHK_schedgettaskhandlebyname  TRUE
	#define EXP_schedgettaskhandlebyname  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgettaskhandlebyname", (RTS_UINTPTR)schedgettaskhandlebyname, 1, 0x0FBFD668, 0x03050900) 
#else /* DYNAMIC_LINK */
	#define USE_schedgettaskhandlebyname  PFSCHEDGETTASKHANDLEBYNAME_IEC pfschedgettaskhandlebyname;
	#define EXT_schedgettaskhandlebyname  extern PFSCHEDGETTASKHANDLEBYNAME_IEC pfschedgettaskhandlebyname;
	#define GET_schedgettaskhandlebyname(fl)  s_pfCMGetAPI2( "schedgettaskhandlebyname", (RTS_VOID_FCTPTR *)&pfschedgettaskhandlebyname, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0FBFD668, 0x03050900)
	#define CAL_schedgettaskhandlebyname  pfschedgettaskhandlebyname
	#define CHK_schedgettaskhandlebyname  (pfschedgettaskhandlebyname != NULL)
	#define EXP_schedgettaskhandlebyname   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgettaskhandlebyname", (RTS_UINTPTR)schedgettaskhandlebyname, 1, 0x0FBFD668, 0x03050900) 
#endif


/**
 *  <description>
 * 	Get the actual interval of a cyclic task. If the specified task is no cyclic task, the function return an error.
 *  </description>
 *  <param name="hSchedTask" type="IN">Handle to the task</param>
 *  <param name="ptInterval" type="OUT">Interval of the task in microseconds!</param>
 *  <result>error code</result>
 */
typedef struct tagschedgettaskinterval_struct
{
	RTS_IEC_HANDLE hSchedTask;			/* VAR_INPUT */	
	RTS_IEC_UDINT *pulInterval;			/* VAR_IN_OUT */	
	RTS_IEC_RESULT SchedGetTaskInterval;	/* VAR_OUTPUT */	
} schedgettaskinterval_struct;

void CDECL CDECL_EXT schedgettaskinterval(schedgettaskinterval_struct *p);
typedef void (CDECL CDECL_EXT* PFSCHEDGETTASKINTERVAL_IEC) (schedgettaskinterval_struct *p);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDGETTASKINTERVAL_NOTIMPLEMENTED)
	#define USE_schedgettaskinterval
	#define EXT_schedgettaskinterval
	#define GET_schedgettaskinterval(fl)  ERR_NOTIMPLEMENTED
	#define CAL_schedgettaskinterval(p0) 
	#define CHK_schedgettaskinterval  FALSE
	#define EXP_schedgettaskinterval  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_schedgettaskinterval
	#define EXT_schedgettaskinterval
	#define GET_schedgettaskinterval(fl)  CAL_CMGETAPI( "schedgettaskinterval" ) 
	#define CAL_schedgettaskinterval  schedgettaskinterval
	#define CHK_schedgettaskinterval  TRUE
	#define EXP_schedgettaskinterval  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgettaskinterval", (RTS_UINTPTR)schedgettaskinterval, 1, 0x247455BA, 0x03050900) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_schedgettaskinterval
	#define EXT_schedgettaskinterval
	#define GET_schedgettaskinterval(fl)  CAL_CMGETAPI( "schedgettaskinterval" ) 
	#define CAL_schedgettaskinterval  schedgettaskinterval
	#define CHK_schedgettaskinterval  TRUE
	#define EXP_schedgettaskinterval  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgettaskinterval", (RTS_UINTPTR)schedgettaskinterval, 1, 0x247455BA, 0x03050900) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleschedgettaskinterval
	#define EXT_CmpScheduleschedgettaskinterval
	#define GET_CmpScheduleschedgettaskinterval  ERR_OK
	#define CAL_CmpScheduleschedgettaskinterval  schedgettaskinterval
	#define CHK_CmpScheduleschedgettaskinterval  TRUE
	#define EXP_CmpScheduleschedgettaskinterval  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgettaskinterval", (RTS_UINTPTR)schedgettaskinterval, 1, 0x247455BA, 0x03050900) 
#elif defined(CPLUSPLUS)
	#define USE_schedgettaskinterval
	#define EXT_schedgettaskinterval
	#define GET_schedgettaskinterval(fl)  CAL_CMGETAPI( "schedgettaskinterval" ) 
	#define CAL_schedgettaskinterval  schedgettaskinterval
	#define CHK_schedgettaskinterval  TRUE
	#define EXP_schedgettaskinterval  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgettaskinterval", (RTS_UINTPTR)schedgettaskinterval, 1, 0x247455BA, 0x03050900) 
#else /* DYNAMIC_LINK */
	#define USE_schedgettaskinterval  PFSCHEDGETTASKINTERVAL_IEC pfschedgettaskinterval;
	#define EXT_schedgettaskinterval  extern PFSCHEDGETTASKINTERVAL_IEC pfschedgettaskinterval;
	#define GET_schedgettaskinterval(fl)  s_pfCMGetAPI2( "schedgettaskinterval", (RTS_VOID_FCTPTR *)&pfschedgettaskinterval, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x247455BA, 0x03050900)
	#define CAL_schedgettaskinterval  pfschedgettaskinterval
	#define CHK_schedgettaskinterval  (pfschedgettaskinterval != NULL)
	#define EXP_schedgettaskinterval   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedgettaskinterval", (RTS_UINTPTR)schedgettaskinterval, 1, 0x247455BA, 0x03050900) 
#endif


/**
 * <description>
 * <p>Execute all tasks, that are registered for the given
 * event. The execution context may vary depending on the
 * scheduler type. It might be executed synchronously in the
 * context of the caller, or a system task (e.g. ontop of an
 * OS) is just signaled to execute the task code.</p>
 * <p>Note, that the result ERR_NO_OBJECT might not be a
 * real error. Depending on the system it might be OK, that
 * no task was registered for this event.</p>
 * </description>
 * <param name="hExtEvent" type="IN">Handle to the external event, which tasks should be signaled</param>
 * <errorcode name="RTS_IEC_RESULT" type="ERR_OK">Event was signaled successfully</errorcode>
 * <errorcode name="RTS_IEC_RESULT" type="ERR_PARAMETER">The event handle was not found</errorcode>
 * <errorcode name="RTS_IEC_RESULT" type="ERR_NO_OBJECT">There was no task, registered on this event</errorcode>
 * <result>Error Code</result>
 */
typedef struct tagschedpostexternalevent_struct
{
	RTS_IEC_HANDLE hExtEvent;			/* VAR_INPUT */	
	RTS_IEC_RESULT SchedPostExternalEvent;	/* VAR_OUTPUT */	
} schedpostexternalevent_struct;

void CDECL CDECL_EXT schedpostexternalevent(schedpostexternalevent_struct *p);
typedef void (CDECL CDECL_EXT* PFSCHEDPOSTEXTERNALEVENT_IEC) (schedpostexternalevent_struct *p);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDPOSTEXTERNALEVENT_NOTIMPLEMENTED)
	#define USE_schedpostexternalevent
	#define EXT_schedpostexternalevent
	#define GET_schedpostexternalevent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_schedpostexternalevent(p0) 
	#define CHK_schedpostexternalevent  FALSE
	#define EXP_schedpostexternalevent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_schedpostexternalevent
	#define EXT_schedpostexternalevent
	#define GET_schedpostexternalevent(fl)  CAL_CMGETAPI( "schedpostexternalevent" ) 
	#define CAL_schedpostexternalevent  schedpostexternalevent
	#define CHK_schedpostexternalevent  TRUE
	#define EXP_schedpostexternalevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedpostexternalevent", (RTS_UINTPTR)schedpostexternalevent, 1, 0x8F2A57B0, 0x03050900) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_schedpostexternalevent
	#define EXT_schedpostexternalevent
	#define GET_schedpostexternalevent(fl)  CAL_CMGETAPI( "schedpostexternalevent" ) 
	#define CAL_schedpostexternalevent  schedpostexternalevent
	#define CHK_schedpostexternalevent  TRUE
	#define EXP_schedpostexternalevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedpostexternalevent", (RTS_UINTPTR)schedpostexternalevent, 1, 0x8F2A57B0, 0x03050900) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleschedpostexternalevent
	#define EXT_CmpScheduleschedpostexternalevent
	#define GET_CmpScheduleschedpostexternalevent  ERR_OK
	#define CAL_CmpScheduleschedpostexternalevent  schedpostexternalevent
	#define CHK_CmpScheduleschedpostexternalevent  TRUE
	#define EXP_CmpScheduleschedpostexternalevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedpostexternalevent", (RTS_UINTPTR)schedpostexternalevent, 1, 0x8F2A57B0, 0x03050900) 
#elif defined(CPLUSPLUS)
	#define USE_schedpostexternalevent
	#define EXT_schedpostexternalevent
	#define GET_schedpostexternalevent(fl)  CAL_CMGETAPI( "schedpostexternalevent" ) 
	#define CAL_schedpostexternalevent  schedpostexternalevent
	#define CHK_schedpostexternalevent  TRUE
	#define EXP_schedpostexternalevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedpostexternalevent", (RTS_UINTPTR)schedpostexternalevent, 1, 0x8F2A57B0, 0x03050900) 
#else /* DYNAMIC_LINK */
	#define USE_schedpostexternalevent  PFSCHEDPOSTEXTERNALEVENT_IEC pfschedpostexternalevent;
	#define EXT_schedpostexternalevent  extern PFSCHEDPOSTEXTERNALEVENT_IEC pfschedpostexternalevent;
	#define GET_schedpostexternalevent(fl)  s_pfCMGetAPI2( "schedpostexternalevent", (RTS_VOID_FCTPTR *)&pfschedpostexternalevent, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x8F2A57B0, 0x03050900)
	#define CAL_schedpostexternalevent  pfschedpostexternalevent
	#define CHK_schedpostexternalevent  (pfschedpostexternalevent != NULL)
	#define EXP_schedpostexternalevent   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedpostexternalevent", (RTS_UINTPTR)schedpostexternalevent, 1, 0x8F2A57B0, 0x03050900) 
#endif


/**
 * <description>
 * <p>Register an external event, which might be used later by
 * event tasks. You should register those events during the system
 * startup, so that the scheduler knows all events when the
 * application is loaded.</p>
 * <p>Valid Hook: CH_INIT2</p>
 * <p>Note: the parameter pszExtEventName needs to be constantly
 * allocated. It might either be a constant string, a global string
 * variable, or a dynamically allocated string. But the memory needs
 * to be valid during the life time of the event handle.</p>
 * </description>
 * <param name="pszExtEventName" type="IN">Name of the event, as it was specified in the device description. This parameter needs to be constantly allocated</param>
 * <param name="pResult" type="INOUT">Error Code</param>
 * <errorcode name="RTS_IEC_RESULT" type="ERR_OK">Event was registered successfully</errorcode>
 * <errorcode name="RTS_IEC_RESULT" type="ERR_NOMEMORY">There was not enough memory to register the new event handle</errorcode>
 * <result>handle to the event</result>
 */
typedef struct tagschedregisterexternalevent_struct
{
	RTS_IEC_STRING *pszExtEventName;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE SchedRegisterExternalEvent;	/* VAR_OUTPUT */	
} schedregisterexternalevent_struct;

void CDECL CDECL_EXT schedregisterexternalevent(schedregisterexternalevent_struct *p);
typedef void (CDECL CDECL_EXT* PFSCHEDREGISTEREXTERNALEVENT_IEC) (schedregisterexternalevent_struct *p);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDREGISTEREXTERNALEVENT_NOTIMPLEMENTED)
	#define USE_schedregisterexternalevent
	#define EXT_schedregisterexternalevent
	#define GET_schedregisterexternalevent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_schedregisterexternalevent(p0) 
	#define CHK_schedregisterexternalevent  FALSE
	#define EXP_schedregisterexternalevent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_schedregisterexternalevent
	#define EXT_schedregisterexternalevent
	#define GET_schedregisterexternalevent(fl)  CAL_CMGETAPI( "schedregisterexternalevent" ) 
	#define CAL_schedregisterexternalevent  schedregisterexternalevent
	#define CHK_schedregisterexternalevent  TRUE
	#define EXP_schedregisterexternalevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedregisterexternalevent", (RTS_UINTPTR)schedregisterexternalevent, 1, 0xF3A15AA7, 0x03050900) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_schedregisterexternalevent
	#define EXT_schedregisterexternalevent
	#define GET_schedregisterexternalevent(fl)  CAL_CMGETAPI( "schedregisterexternalevent" ) 
	#define CAL_schedregisterexternalevent  schedregisterexternalevent
	#define CHK_schedregisterexternalevent  TRUE
	#define EXP_schedregisterexternalevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedregisterexternalevent", (RTS_UINTPTR)schedregisterexternalevent, 1, 0xF3A15AA7, 0x03050900) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleschedregisterexternalevent
	#define EXT_CmpScheduleschedregisterexternalevent
	#define GET_CmpScheduleschedregisterexternalevent  ERR_OK
	#define CAL_CmpScheduleschedregisterexternalevent  schedregisterexternalevent
	#define CHK_CmpScheduleschedregisterexternalevent  TRUE
	#define EXP_CmpScheduleschedregisterexternalevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedregisterexternalevent", (RTS_UINTPTR)schedregisterexternalevent, 1, 0xF3A15AA7, 0x03050900) 
#elif defined(CPLUSPLUS)
	#define USE_schedregisterexternalevent
	#define EXT_schedregisterexternalevent
	#define GET_schedregisterexternalevent(fl)  CAL_CMGETAPI( "schedregisterexternalevent" ) 
	#define CAL_schedregisterexternalevent  schedregisterexternalevent
	#define CHK_schedregisterexternalevent  TRUE
	#define EXP_schedregisterexternalevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedregisterexternalevent", (RTS_UINTPTR)schedregisterexternalevent, 1, 0xF3A15AA7, 0x03050900) 
#else /* DYNAMIC_LINK */
	#define USE_schedregisterexternalevent  PFSCHEDREGISTEREXTERNALEVENT_IEC pfschedregisterexternalevent;
	#define EXT_schedregisterexternalevent  extern PFSCHEDREGISTEREXTERNALEVENT_IEC pfschedregisterexternalevent;
	#define GET_schedregisterexternalevent(fl)  s_pfCMGetAPI2( "schedregisterexternalevent", (RTS_VOID_FCTPTR *)&pfschedregisterexternalevent, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xF3A15AA7, 0x03050900)
	#define CAL_schedregisterexternalevent  pfschedregisterexternalevent
	#define CHK_schedregisterexternalevent  (pfschedregisterexternalevent != NULL)
	#define EXP_schedregisterexternalevent   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedregisterexternalevent", (RTS_UINTPTR)schedregisterexternalevent, 1, 0xF3A15AA7, 0x03050900) 
#endif


/**
 *  <description>
 * 	Set the actual interval of a cyclic task. If the specified task is no cyclic task, the function return an error.
 * 	This interface can be used to synchronize a task to another task or to events.
 *  </description>
 *  <param name="hSchedTask" type="IN">Handle to the task</param>
 *  <param name="tInterval" type="IN">New interval in microseconds!</param>
 *  <result>error code</result>
 */
typedef struct tagschedsettaskinterval_struct
{
	RTS_IEC_HANDLE hSchedTask;			/* VAR_INPUT */	
	RTS_IEC_UDINT ulInterval;			/* VAR_INPUT */	
	RTS_IEC_RESULT SchedSetTaskInterval;	/* VAR_OUTPUT */	
} schedsettaskinterval_struct;

void CDECL CDECL_EXT schedsettaskinterval(schedsettaskinterval_struct *p);
typedef void (CDECL CDECL_EXT* PFSCHEDSETTASKINTERVAL_IEC) (schedsettaskinterval_struct *p);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDSETTASKINTERVAL_NOTIMPLEMENTED)
	#define USE_schedsettaskinterval
	#define EXT_schedsettaskinterval
	#define GET_schedsettaskinterval(fl)  ERR_NOTIMPLEMENTED
	#define CAL_schedsettaskinterval(p0) 
	#define CHK_schedsettaskinterval  FALSE
	#define EXP_schedsettaskinterval  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_schedsettaskinterval
	#define EXT_schedsettaskinterval
	#define GET_schedsettaskinterval(fl)  CAL_CMGETAPI( "schedsettaskinterval" ) 
	#define CAL_schedsettaskinterval  schedsettaskinterval
	#define CHK_schedsettaskinterval  TRUE
	#define EXP_schedsettaskinterval  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedsettaskinterval", (RTS_UINTPTR)schedsettaskinterval, 1, 0x4DF2120E, 0x03050900) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_schedsettaskinterval
	#define EXT_schedsettaskinterval
	#define GET_schedsettaskinterval(fl)  CAL_CMGETAPI( "schedsettaskinterval" ) 
	#define CAL_schedsettaskinterval  schedsettaskinterval
	#define CHK_schedsettaskinterval  TRUE
	#define EXP_schedsettaskinterval  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedsettaskinterval", (RTS_UINTPTR)schedsettaskinterval, 1, 0x4DF2120E, 0x03050900) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleschedsettaskinterval
	#define EXT_CmpScheduleschedsettaskinterval
	#define GET_CmpScheduleschedsettaskinterval  ERR_OK
	#define CAL_CmpScheduleschedsettaskinterval  schedsettaskinterval
	#define CHK_CmpScheduleschedsettaskinterval  TRUE
	#define EXP_CmpScheduleschedsettaskinterval  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedsettaskinterval", (RTS_UINTPTR)schedsettaskinterval, 1, 0x4DF2120E, 0x03050900) 
#elif defined(CPLUSPLUS)
	#define USE_schedsettaskinterval
	#define EXT_schedsettaskinterval
	#define GET_schedsettaskinterval(fl)  CAL_CMGETAPI( "schedsettaskinterval" ) 
	#define CAL_schedsettaskinterval  schedsettaskinterval
	#define CHK_schedsettaskinterval  TRUE
	#define EXP_schedsettaskinterval  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedsettaskinterval", (RTS_UINTPTR)schedsettaskinterval, 1, 0x4DF2120E, 0x03050900) 
#else /* DYNAMIC_LINK */
	#define USE_schedsettaskinterval  PFSCHEDSETTASKINTERVAL_IEC pfschedsettaskinterval;
	#define EXT_schedsettaskinterval  extern PFSCHEDSETTASKINTERVAL_IEC pfschedsettaskinterval;
	#define GET_schedsettaskinterval(fl)  s_pfCMGetAPI2( "schedsettaskinterval", (RTS_VOID_FCTPTR *)&pfschedsettaskinterval, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x4DF2120E, 0x03050900)
	#define CAL_schedsettaskinterval  pfschedsettaskinterval
	#define CHK_schedsettaskinterval  (pfschedsettaskinterval != NULL)
	#define EXP_schedsettaskinterval   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedsettaskinterval", (RTS_UINTPTR)schedsettaskinterval, 1, 0x4DF2120E, 0x03050900) 
#endif


/**
 * <description>
 * <p>Unregister an external event, which was registered by
 * SchedRegisterExternalEvent() before.</p>
 * <p>This function should be called on system shutdown</p>
 * <p>Valid Hook: CH_EXIT2</p>
 * </description>
 * <param name="hExtEvent" type="IN">Handle to the external event, that should be unregistered.</param>
 * <errorcode name="RTS_IEC_RESULT" type="ERR_OK">Event was deregistered successfully</errorcode>
 * <errorcode name="RTS_IEC_RESULT" type="ERR_PARAMETER">The event handle was not registered before</errorcode>
 * <result>Error code</result>
 */
typedef struct tagschedunregisterexternalevent_struct
{
	RTS_IEC_HANDLE hExtEvent;			/* VAR_INPUT */	
	RTS_IEC_RESULT SchedUnregisterExternalEvent;	/* VAR_OUTPUT */	
} schedunregisterexternalevent_struct;

void CDECL CDECL_EXT schedunregisterexternalevent(schedunregisterexternalevent_struct *p);
typedef void (CDECL CDECL_EXT* PFSCHEDUNREGISTEREXTERNALEVENT_IEC) (schedunregisterexternalevent_struct *p);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDUNREGISTEREXTERNALEVENT_NOTIMPLEMENTED)
	#define USE_schedunregisterexternalevent
	#define EXT_schedunregisterexternalevent
	#define GET_schedunregisterexternalevent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_schedunregisterexternalevent(p0) 
	#define CHK_schedunregisterexternalevent  FALSE
	#define EXP_schedunregisterexternalevent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_schedunregisterexternalevent
	#define EXT_schedunregisterexternalevent
	#define GET_schedunregisterexternalevent(fl)  CAL_CMGETAPI( "schedunregisterexternalevent" ) 
	#define CAL_schedunregisterexternalevent  schedunregisterexternalevent
	#define CHK_schedunregisterexternalevent  TRUE
	#define EXP_schedunregisterexternalevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedunregisterexternalevent", (RTS_UINTPTR)schedunregisterexternalevent, 1, 0xF74A64AD, 0x03050900) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_schedunregisterexternalevent
	#define EXT_schedunregisterexternalevent
	#define GET_schedunregisterexternalevent(fl)  CAL_CMGETAPI( "schedunregisterexternalevent" ) 
	#define CAL_schedunregisterexternalevent  schedunregisterexternalevent
	#define CHK_schedunregisterexternalevent  TRUE
	#define EXP_schedunregisterexternalevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedunregisterexternalevent", (RTS_UINTPTR)schedunregisterexternalevent, 1, 0xF74A64AD, 0x03050900) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleschedunregisterexternalevent
	#define EXT_CmpScheduleschedunregisterexternalevent
	#define GET_CmpScheduleschedunregisterexternalevent  ERR_OK
	#define CAL_CmpScheduleschedunregisterexternalevent  schedunregisterexternalevent
	#define CHK_CmpScheduleschedunregisterexternalevent  TRUE
	#define EXP_CmpScheduleschedunregisterexternalevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedunregisterexternalevent", (RTS_UINTPTR)schedunregisterexternalevent, 1, 0xF74A64AD, 0x03050900) 
#elif defined(CPLUSPLUS)
	#define USE_schedunregisterexternalevent
	#define EXT_schedunregisterexternalevent
	#define GET_schedunregisterexternalevent(fl)  CAL_CMGETAPI( "schedunregisterexternalevent" ) 
	#define CAL_schedunregisterexternalevent  schedunregisterexternalevent
	#define CHK_schedunregisterexternalevent  TRUE
	#define EXP_schedunregisterexternalevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedunregisterexternalevent", (RTS_UINTPTR)schedunregisterexternalevent, 1, 0xF74A64AD, 0x03050900) 
#else /* DYNAMIC_LINK */
	#define USE_schedunregisterexternalevent  PFSCHEDUNREGISTEREXTERNALEVENT_IEC pfschedunregisterexternalevent;
	#define EXT_schedunregisterexternalevent  extern PFSCHEDUNREGISTEREXTERNALEVENT_IEC pfschedunregisterexternalevent;
	#define GET_schedunregisterexternalevent(fl)  s_pfCMGetAPI2( "schedunregisterexternalevent", (RTS_VOID_FCTPTR *)&pfschedunregisterexternalevent, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xF74A64AD, 0x03050900)
	#define CAL_schedunregisterexternalevent  pfschedunregisterexternalevent
	#define CHK_schedunregisterexternalevent  (pfschedunregisterexternalevent != NULL)
	#define EXP_schedunregisterexternalevent   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedunregisterexternalevent", (RTS_UINTPTR)schedunregisterexternalevent, 1, 0xF74A64AD, 0x03050900) 
#endif


/**
 *  <description>
 * 	Function to wait busy during a specified time interval. This consumes maximum of processor load!
 *  </description>
 *  <param name="ptSleepUs" type="IN">Time to sleep in microseconds</param>
 *  <result>error code</result>
 */
typedef struct tagschedwaitbusy_struct
{
	RTS_IEC_ULINT *ptSleepUs;			/* VAR_IN_OUT */	
	RTS_IEC_RESULT SchedWaitBusy;		/* VAR_OUTPUT */	
} schedwaitbusy_struct;

void CDECL CDECL_EXT schedwaitbusy(schedwaitbusy_struct *p);
typedef void (CDECL CDECL_EXT* PFSCHEDWAITBUSY_IEC) (schedwaitbusy_struct *p);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDWAITBUSY_NOTIMPLEMENTED)
	#define USE_schedwaitbusy
	#define EXT_schedwaitbusy
	#define GET_schedwaitbusy(fl)  ERR_NOTIMPLEMENTED
	#define CAL_schedwaitbusy(p0) 
	#define CHK_schedwaitbusy  FALSE
	#define EXP_schedwaitbusy  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_schedwaitbusy
	#define EXT_schedwaitbusy
	#define GET_schedwaitbusy(fl)  CAL_CMGETAPI( "schedwaitbusy" ) 
	#define CAL_schedwaitbusy  schedwaitbusy
	#define CHK_schedwaitbusy  TRUE
	#define EXP_schedwaitbusy  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedwaitbusy", (RTS_UINTPTR)schedwaitbusy, 1, RTSITF_GET_SIGNATURE(0, 0x34BA0AC2), 0x03050900) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_schedwaitbusy
	#define EXT_schedwaitbusy
	#define GET_schedwaitbusy(fl)  CAL_CMGETAPI( "schedwaitbusy" ) 
	#define CAL_schedwaitbusy  schedwaitbusy
	#define CHK_schedwaitbusy  TRUE
	#define EXP_schedwaitbusy  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedwaitbusy", (RTS_UINTPTR)schedwaitbusy, 1, RTSITF_GET_SIGNATURE(0, 0x34BA0AC2), 0x03050900) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleschedwaitbusy
	#define EXT_CmpScheduleschedwaitbusy
	#define GET_CmpScheduleschedwaitbusy  ERR_OK
	#define CAL_CmpScheduleschedwaitbusy  schedwaitbusy
	#define CHK_CmpScheduleschedwaitbusy  TRUE
	#define EXP_CmpScheduleschedwaitbusy  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedwaitbusy", (RTS_UINTPTR)schedwaitbusy, 1, RTSITF_GET_SIGNATURE(0, 0x34BA0AC2), 0x03050900) 
#elif defined(CPLUSPLUS)
	#define USE_schedwaitbusy
	#define EXT_schedwaitbusy
	#define GET_schedwaitbusy(fl)  CAL_CMGETAPI( "schedwaitbusy" ) 
	#define CAL_schedwaitbusy  schedwaitbusy
	#define CHK_schedwaitbusy  TRUE
	#define EXP_schedwaitbusy  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedwaitbusy", (RTS_UINTPTR)schedwaitbusy, 1, RTSITF_GET_SIGNATURE(0, 0x34BA0AC2), 0x03050900) 
#else /* DYNAMIC_LINK */
	#define USE_schedwaitbusy  PFSCHEDWAITBUSY_IEC pfschedwaitbusy;
	#define EXT_schedwaitbusy  extern PFSCHEDWAITBUSY_IEC pfschedwaitbusy;
	#define GET_schedwaitbusy(fl)  s_pfCMGetAPI2( "schedwaitbusy", (RTS_VOID_FCTPTR *)&pfschedwaitbusy, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x34BA0AC2), 0x03050900)
	#define CAL_schedwaitbusy  pfschedwaitbusy
	#define CHK_schedwaitbusy  (pfschedwaitbusy != NULL)
	#define EXP_schedwaitbusy   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedwaitbusy", (RTS_UINTPTR)schedwaitbusy, 1, RTSITF_GET_SIGNATURE(0, 0x34BA0AC2), 0x03050900) 
#endif


/**
 *  <description>
 * 	Function to sleep a specified time interval in microseconds _without_ consuming processor load!
 *  </description>
 *  <param name="ptSleepUs" type="IN">Time to sleep in microseconds</param>
 *  <result>error code</result>
 */
typedef struct tagschedwaitsleep_struct
{
	RTS_IEC_ULINT *ptSleepUs;			/* VAR_IN_OUT */	
	RTS_IEC_RESULT SchedWaitSleep;		/* VAR_OUTPUT */	
} schedwaitsleep_struct;

void CDECL CDECL_EXT schedwaitsleep(schedwaitsleep_struct *p);
typedef void (CDECL CDECL_EXT* PFSCHEDWAITSLEEP_IEC) (schedwaitsleep_struct *p);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDWAITSLEEP_NOTIMPLEMENTED)
	#define USE_schedwaitsleep
	#define EXT_schedwaitsleep
	#define GET_schedwaitsleep(fl)  ERR_NOTIMPLEMENTED
	#define CAL_schedwaitsleep(p0) 
	#define CHK_schedwaitsleep  FALSE
	#define EXP_schedwaitsleep  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_schedwaitsleep
	#define EXT_schedwaitsleep
	#define GET_schedwaitsleep(fl)  CAL_CMGETAPI( "schedwaitsleep" ) 
	#define CAL_schedwaitsleep  schedwaitsleep
	#define CHK_schedwaitsleep  TRUE
	#define EXP_schedwaitsleep  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedwaitsleep", (RTS_UINTPTR)schedwaitsleep, 1, RTSITF_GET_SIGNATURE(0, 0xAD6B19D4), 0x03050900) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_schedwaitsleep
	#define EXT_schedwaitsleep
	#define GET_schedwaitsleep(fl)  CAL_CMGETAPI( "schedwaitsleep" ) 
	#define CAL_schedwaitsleep  schedwaitsleep
	#define CHK_schedwaitsleep  TRUE
	#define EXP_schedwaitsleep  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedwaitsleep", (RTS_UINTPTR)schedwaitsleep, 1, RTSITF_GET_SIGNATURE(0, 0xAD6B19D4), 0x03050900) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleschedwaitsleep
	#define EXT_CmpScheduleschedwaitsleep
	#define GET_CmpScheduleschedwaitsleep  ERR_OK
	#define CAL_CmpScheduleschedwaitsleep  schedwaitsleep
	#define CHK_CmpScheduleschedwaitsleep  TRUE
	#define EXP_CmpScheduleschedwaitsleep  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedwaitsleep", (RTS_UINTPTR)schedwaitsleep, 1, RTSITF_GET_SIGNATURE(0, 0xAD6B19D4), 0x03050900) 
#elif defined(CPLUSPLUS)
	#define USE_schedwaitsleep
	#define EXT_schedwaitsleep
	#define GET_schedwaitsleep(fl)  CAL_CMGETAPI( "schedwaitsleep" ) 
	#define CAL_schedwaitsleep  schedwaitsleep
	#define CHK_schedwaitsleep  TRUE
	#define EXP_schedwaitsleep  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedwaitsleep", (RTS_UINTPTR)schedwaitsleep, 1, RTSITF_GET_SIGNATURE(0, 0xAD6B19D4), 0x03050900) 
#else /* DYNAMIC_LINK */
	#define USE_schedwaitsleep  PFSCHEDWAITSLEEP_IEC pfschedwaitsleep;
	#define EXT_schedwaitsleep  extern PFSCHEDWAITSLEEP_IEC pfschedwaitsleep;
	#define GET_schedwaitsleep(fl)  s_pfCMGetAPI2( "schedwaitsleep", (RTS_VOID_FCTPTR *)&pfschedwaitsleep, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xAD6B19D4), 0x03050900)
	#define CAL_schedwaitsleep  pfschedwaitsleep
	#define CHK_schedwaitsleep  (pfschedwaitsleep != NULL)
	#define EXP_schedwaitsleep   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"schedwaitsleep", (RTS_UINTPTR)schedwaitsleep, 1, RTSITF_GET_SIGNATURE(0, 0xAD6B19D4), 0x03050900) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>
 *	Routine to check, if a scheduler has the specified feature.
 * </description>
 * <param name="ulFeatures" type="IN">Feature flags, See corresponding category "Features".</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SchedHasFeature(unsigned long ulFeatures);
typedef RTS_RESULT (CDECL * PFSCHEDHASFEATURE) (unsigned long ulFeatures);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDHASFEATURE_NOTIMPLEMENTED)
	#define USE_SchedHasFeature
	#define EXT_SchedHasFeature
	#define GET_SchedHasFeature(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedHasFeature(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SchedHasFeature  FALSE
	#define EXP_SchedHasFeature  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedHasFeature
	#define EXT_SchedHasFeature
	#define GET_SchedHasFeature(fl)  CAL_CMGETAPI( "SchedHasFeature" ) 
	#define CAL_SchedHasFeature  SchedHasFeature
	#define CHK_SchedHasFeature  TRUE
	#define EXP_SchedHasFeature  CAL_CMEXPAPI( "SchedHasFeature" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedHasFeature
	#define EXT_SchedHasFeature
	#define GET_SchedHasFeature(fl)  CAL_CMGETAPI( "SchedHasFeature" ) 
	#define CAL_SchedHasFeature  SchedHasFeature
	#define CHK_SchedHasFeature  TRUE
	#define EXP_SchedHasFeature  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedHasFeature", (RTS_UINTPTR)SchedHasFeature, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedHasFeature
	#define EXT_CmpScheduleSchedHasFeature
	#define GET_CmpScheduleSchedHasFeature  ERR_OK
	#define CAL_CmpScheduleSchedHasFeature pICmpSchedule->ISchedHasFeature
	#define CHK_CmpScheduleSchedHasFeature (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedHasFeature  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedHasFeature
	#define EXT_SchedHasFeature
	#define GET_SchedHasFeature(fl)  CAL_CMGETAPI( "SchedHasFeature" ) 
	#define CAL_SchedHasFeature pICmpSchedule->ISchedHasFeature
	#define CHK_SchedHasFeature (pICmpSchedule != NULL)
	#define EXP_SchedHasFeature  CAL_CMEXPAPI( "SchedHasFeature" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedHasFeature  PFSCHEDHASFEATURE pfSchedHasFeature;
	#define EXT_SchedHasFeature  extern PFSCHEDHASFEATURE pfSchedHasFeature;
	#define GET_SchedHasFeature(fl)  s_pfCMGetAPI2( "SchedHasFeature", (RTS_VOID_FCTPTR *)&pfSchedHasFeature, (fl), 0, 0)
	#define CAL_SchedHasFeature  pfSchedHasFeature
	#define CHK_SchedHasFeature  (pfSchedHasFeature != NULL)
	#define EXP_SchedHasFeature  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedHasFeature", (RTS_UINTPTR)SchedHasFeature, 0, 0) 
#endif




/**
 * <description>
 * <p>Create a new IEC task, that is under control of the CoDeSys Control
 * Scheduler</p>
 * <p>Depending on the type of Scheduler which is used, the tasks may be
 * created in different ways. Here is a small list of the most common
 * Scheduling schemes:</p>
 * <ul>
 *   <li><b>CmpSchedule:</b>
 *   A full multitasking scheduler, where every task (independent of its
 *   type) has a corresponding OS task.</li>
 *   <li><b>CmpScheduleEmbedded:</b>
 *   A very simple scheduler, where every task runs in the context of a
 *   super loop in the background (the comm cycle). The tasks are scheduled
 *   in polling mode by the scheduler.</li>
 *   <li><b>CmpScheduleTimer:</b>
 *   Freewheeling and Event tasks are scheduled similar to CmpScheduleEmbedded,
 *   but cyclic tasks are placed on preemptive timers.</li>
 * </ul>
 * <p>The tasks are set up, but not started, yet. To start the tasks, one
 * should call SchedStart().</p>
 * </description>
 * <param name="pTask" type="IN" range="[NULL,VALID_TASKSDESC]">Task description</param>
 * <parampseudo name="TaskType" type="IN" range="[TaskFreewheeling,TaskEvent,TaskCyclic,TaskExternal]">Type of the IEC task</parampseudo>
 * <parampseudo name="iNumOfTasks" type="IN" range="[0..NUM_OF_STATIC_IEC_TASKS]">Number of Tasks that are created</parampseudo>
 * <parampseudo name="bException" type="OUT">Exception was thrown</parampseudo>
 * <param name="pResult" type="OUT">Result</param>
 * <result>Handle to task</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Task was created successfully</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">pTask was NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">Not enough memory to create the task.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Scheduler specific error. Most likely the scheduler was unable to create a required ressource.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOT_SUPPORTED">The configured task type is not supported by this scheduler</errorcode>
 */
RTS_HANDLE CDECL SchedAddTask(Task_Desc *pTask, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSCHEDADDTASK) (Task_Desc *pTask, RTS_RESULT *pResult);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDADDTASK_NOTIMPLEMENTED)
	#define USE_SchedAddTask
	#define EXT_SchedAddTask
	#define GET_SchedAddTask(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedAddTask(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SchedAddTask  FALSE
	#define EXP_SchedAddTask  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedAddTask
	#define EXT_SchedAddTask
	#define GET_SchedAddTask(fl)  CAL_CMGETAPI( "SchedAddTask" ) 
	#define CAL_SchedAddTask  SchedAddTask
	#define CHK_SchedAddTask  TRUE
	#define EXP_SchedAddTask  CAL_CMEXPAPI( "SchedAddTask" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedAddTask
	#define EXT_SchedAddTask
	#define GET_SchedAddTask(fl)  CAL_CMGETAPI( "SchedAddTask" ) 
	#define CAL_SchedAddTask  SchedAddTask
	#define CHK_SchedAddTask  TRUE
	#define EXP_SchedAddTask  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedAddTask", (RTS_UINTPTR)SchedAddTask, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedAddTask
	#define EXT_CmpScheduleSchedAddTask
	#define GET_CmpScheduleSchedAddTask  ERR_OK
	#define CAL_CmpScheduleSchedAddTask pICmpSchedule->ISchedAddTask
	#define CHK_CmpScheduleSchedAddTask (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedAddTask  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedAddTask
	#define EXT_SchedAddTask
	#define GET_SchedAddTask(fl)  CAL_CMGETAPI( "SchedAddTask" ) 
	#define CAL_SchedAddTask pICmpSchedule->ISchedAddTask
	#define CHK_SchedAddTask (pICmpSchedule != NULL)
	#define EXP_SchedAddTask  CAL_CMEXPAPI( "SchedAddTask" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedAddTask  PFSCHEDADDTASK pfSchedAddTask;
	#define EXT_SchedAddTask  extern PFSCHEDADDTASK pfSchedAddTask;
	#define GET_SchedAddTask(fl)  s_pfCMGetAPI2( "SchedAddTask", (RTS_VOID_FCTPTR *)&pfSchedAddTask, (fl), 0, 0)
	#define CAL_SchedAddTask  pfSchedAddTask
	#define CHK_SchedAddTask  (pfSchedAddTask != NULL)
	#define EXP_SchedAddTask  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedAddTask", (RTS_UINTPTR)SchedAddTask, 0, 0) 
#endif




/**
 * <description> Removes a task from scheduler </description>
 * <param name="hSchedTask" type="IN">Handle to task</param>
 * <result>ERR_OK</result>
 */
RTS_RESULT CDECL SchedRemoveTask(RTS_HANDLE hSchedTask);
typedef RTS_RESULT (CDECL * PFSCHEDREMOVETASK) (RTS_HANDLE hSchedTask);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDREMOVETASK_NOTIMPLEMENTED)
	#define USE_SchedRemoveTask
	#define EXT_SchedRemoveTask
	#define GET_SchedRemoveTask(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedRemoveTask(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SchedRemoveTask  FALSE
	#define EXP_SchedRemoveTask  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedRemoveTask
	#define EXT_SchedRemoveTask
	#define GET_SchedRemoveTask(fl)  CAL_CMGETAPI( "SchedRemoveTask" ) 
	#define CAL_SchedRemoveTask  SchedRemoveTask
	#define CHK_SchedRemoveTask  TRUE
	#define EXP_SchedRemoveTask  CAL_CMEXPAPI( "SchedRemoveTask" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedRemoveTask
	#define EXT_SchedRemoveTask
	#define GET_SchedRemoveTask(fl)  CAL_CMGETAPI( "SchedRemoveTask" ) 
	#define CAL_SchedRemoveTask  SchedRemoveTask
	#define CHK_SchedRemoveTask  TRUE
	#define EXP_SchedRemoveTask  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedRemoveTask", (RTS_UINTPTR)SchedRemoveTask, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedRemoveTask
	#define EXT_CmpScheduleSchedRemoveTask
	#define GET_CmpScheduleSchedRemoveTask  ERR_OK
	#define CAL_CmpScheduleSchedRemoveTask pICmpSchedule->ISchedRemoveTask
	#define CHK_CmpScheduleSchedRemoveTask (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedRemoveTask  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedRemoveTask
	#define EXT_SchedRemoveTask
	#define GET_SchedRemoveTask(fl)  CAL_CMGETAPI( "SchedRemoveTask" ) 
	#define CAL_SchedRemoveTask pICmpSchedule->ISchedRemoveTask
	#define CHK_SchedRemoveTask (pICmpSchedule != NULL)
	#define EXP_SchedRemoveTask  CAL_CMEXPAPI( "SchedRemoveTask" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedRemoveTask  PFSCHEDREMOVETASK pfSchedRemoveTask;
	#define EXT_SchedRemoveTask  extern PFSCHEDREMOVETASK pfSchedRemoveTask;
	#define GET_SchedRemoveTask(fl)  s_pfCMGetAPI2( "SchedRemoveTask", (RTS_VOID_FCTPTR *)&pfSchedRemoveTask, (fl), 0, 0)
	#define CAL_SchedRemoveTask  pfSchedRemoveTask
	#define CHK_SchedRemoveTask  (pfSchedRemoveTask != NULL)
	#define EXP_SchedRemoveTask  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedRemoveTask", (RTS_UINTPTR)SchedRemoveTask, 0, 0) 
#endif




/**
 * <description> Removes a task from scheduler with timeout </description>
 * <param name="hSchedTask" type="IN">Handle to task</param>
 * <param name="ulTimeoutMs" type="IN">Timeout in milliseconds to wait for removing the task
 *	Some timeouts are predefined (see CmpStd.h):
 *	<ul>
 *		<li>RTS_TIMEOUT_DEFAULT: Use default wait time</li>
 *		<li>RTS_TIMEOUT_NO_WAIT: No wait</li>
 *	</ul>
 * </param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SchedRemoveTask2(RTS_HANDLE hSchedTask, RTS_UI32 ulTimeoutMs);
typedef RTS_RESULT (CDECL * PFSCHEDREMOVETASK2) (RTS_HANDLE hSchedTask, RTS_UI32 ulTimeoutMs);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDREMOVETASK2_NOTIMPLEMENTED)
	#define USE_SchedRemoveTask2
	#define EXT_SchedRemoveTask2
	#define GET_SchedRemoveTask2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedRemoveTask2(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SchedRemoveTask2  FALSE
	#define EXP_SchedRemoveTask2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedRemoveTask2
	#define EXT_SchedRemoveTask2
	#define GET_SchedRemoveTask2(fl)  CAL_CMGETAPI( "SchedRemoveTask2" ) 
	#define CAL_SchedRemoveTask2  SchedRemoveTask2
	#define CHK_SchedRemoveTask2  TRUE
	#define EXP_SchedRemoveTask2  CAL_CMEXPAPI( "SchedRemoveTask2" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedRemoveTask2
	#define EXT_SchedRemoveTask2
	#define GET_SchedRemoveTask2(fl)  CAL_CMGETAPI( "SchedRemoveTask2" ) 
	#define CAL_SchedRemoveTask2  SchedRemoveTask2
	#define CHK_SchedRemoveTask2  TRUE
	#define EXP_SchedRemoveTask2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedRemoveTask2", (RTS_UINTPTR)SchedRemoveTask2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedRemoveTask2
	#define EXT_CmpScheduleSchedRemoveTask2
	#define GET_CmpScheduleSchedRemoveTask2  ERR_OK
	#define CAL_CmpScheduleSchedRemoveTask2 pICmpSchedule->ISchedRemoveTask2
	#define CHK_CmpScheduleSchedRemoveTask2 (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedRemoveTask2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedRemoveTask2
	#define EXT_SchedRemoveTask2
	#define GET_SchedRemoveTask2(fl)  CAL_CMGETAPI( "SchedRemoveTask2" ) 
	#define CAL_SchedRemoveTask2 pICmpSchedule->ISchedRemoveTask2
	#define CHK_SchedRemoveTask2 (pICmpSchedule != NULL)
	#define EXP_SchedRemoveTask2  CAL_CMEXPAPI( "SchedRemoveTask2" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedRemoveTask2  PFSCHEDREMOVETASK2 pfSchedRemoveTask2;
	#define EXT_SchedRemoveTask2  extern PFSCHEDREMOVETASK2 pfSchedRemoveTask2;
	#define GET_SchedRemoveTask2(fl)  s_pfCMGetAPI2( "SchedRemoveTask2", (RTS_VOID_FCTPTR *)&pfSchedRemoveTask2, (fl), 0, 0)
	#define CAL_SchedRemoveTask2  pfSchedRemoveTask2
	#define CHK_SchedRemoveTask2  (pfSchedRemoveTask2 != NULL)
	#define EXP_SchedRemoveTask2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedRemoveTask2", (RTS_UINTPTR)SchedRemoveTask2, 0, 0) 
#endif




/**
 * <description>
 * <p>Execute a scheduler command.</p>
 * <p>Depending on the kind of scheduler, it may support different scheduler
 * specific commands. Those commands may be described in the documentation
 * of the scheduler component itself.</p>
 * <p>The following are generic commands which every scheduler should support:</p>
 * <ul>
 *   <li>CMD_TICK:
 *   This command can be used by the scheduler to schedule it's cyclic- or
 *   event tasks. But most essentially this tick has to check the tasks
 *   watchdogs.</li>
 *   <li>CMD_DEBUG_LOOP:
 *   This command is used by the IEC tasks to halt on a breakpoint. It should
 *   only be called by an IEC task, which ran on a breakpoint. The implementation
 *   is very dependent on the kind of scheduler, but it will halt the execution
 *   of the IEC task until the breakpoint is left.</li>
 * </ul>
 * </description>
 * <param name="hSchedTask" type="IN" range="[RTS_INVALID_HANDLE,VALID_TASKHANDLE]">Handle to task</param>
 * <param name="iCmd" type="IN" range="[CMD_TICK,CMD_DEBUG_LOOP,INVALID_CMD]">Type of schedule command</param>
 * <parampseudo name="bSIL2SafetyMode" type="IN" range="[0,1]">Type of schedule command</parampseudo>
 * <parampseudo name="bWatchdogSleep" type="IN" range="[0,1]">Watchdog sleep to check if Exception occurs</parampseudo>
 * <parampseudo name="bException" type="OUT">Is only allowed in SIL2 Runtime in Debugmode</parampseudo>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Command executed successfully</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOT_SUPPORTED">Command is not supported</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Command is not supported</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Command is not supported</errorcode>
 */
RTS_RESULT CDECL Schedule(RTS_HANDLE hSchedTask, int iCmd);
typedef RTS_RESULT (CDECL * PFSCHEDULE) (RTS_HANDLE hSchedTask, int iCmd);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDULE_NOTIMPLEMENTED)
	#define USE_Schedule
	#define EXT_Schedule
	#define GET_Schedule(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Schedule(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Schedule  FALSE
	#define EXP_Schedule  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Schedule
	#define EXT_Schedule
	#define GET_Schedule(fl)  CAL_CMGETAPI( "Schedule" ) 
	#define CAL_Schedule  Schedule
	#define CHK_Schedule  TRUE
	#define EXP_Schedule  CAL_CMEXPAPI( "Schedule" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_Schedule
	#define EXT_Schedule
	#define GET_Schedule(fl)  CAL_CMGETAPI( "Schedule" ) 
	#define CAL_Schedule  Schedule
	#define CHK_Schedule  TRUE
	#define EXP_Schedule  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Schedule", (RTS_UINTPTR)Schedule, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedule
	#define EXT_CmpScheduleSchedule
	#define GET_CmpScheduleSchedule  ERR_OK
	#define CAL_CmpScheduleSchedule pICmpSchedule->ISchedule
	#define CHK_CmpScheduleSchedule (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedule  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Schedule
	#define EXT_Schedule
	#define GET_Schedule(fl)  CAL_CMGETAPI( "Schedule" ) 
	#define CAL_Schedule pICmpSchedule->ISchedule
	#define CHK_Schedule (pICmpSchedule != NULL)
	#define EXP_Schedule  CAL_CMEXPAPI( "Schedule" ) 
#else /* DYNAMIC_LINK */
	#define USE_Schedule  PFSCHEDULE pfSchedule;
	#define EXT_Schedule  extern PFSCHEDULE pfSchedule;
	#define GET_Schedule(fl)  s_pfCMGetAPI2( "Schedule", (RTS_VOID_FCTPTR *)&pfSchedule, (fl), 0, 0)
	#define CAL_Schedule  pfSchedule
	#define CHK_Schedule  (pfSchedule != NULL)
	#define EXP_Schedule  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Schedule", (RTS_UINTPTR)Schedule, 0, 0) 
#endif




/**
 * <description> Enter task for debugging </description>
 * <param name="hSchedTask" type="IN">Handle to task</param>
 * <result>ERR_OK</result>
 */
RTS_RESULT CDECL SchedDebugEnter(RTS_HANDLE hSchedTask);
typedef RTS_RESULT (CDECL * PFSCHEDDEBUGENTER) (RTS_HANDLE hSchedTask);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDDEBUGENTER_NOTIMPLEMENTED)
	#define USE_SchedDebugEnter
	#define EXT_SchedDebugEnter
	#define GET_SchedDebugEnter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedDebugEnter(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SchedDebugEnter  FALSE
	#define EXP_SchedDebugEnter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedDebugEnter
	#define EXT_SchedDebugEnter
	#define GET_SchedDebugEnter(fl)  CAL_CMGETAPI( "SchedDebugEnter" ) 
	#define CAL_SchedDebugEnter  SchedDebugEnter
	#define CHK_SchedDebugEnter  TRUE
	#define EXP_SchedDebugEnter  CAL_CMEXPAPI( "SchedDebugEnter" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedDebugEnter
	#define EXT_SchedDebugEnter
	#define GET_SchedDebugEnter(fl)  CAL_CMGETAPI( "SchedDebugEnter" ) 
	#define CAL_SchedDebugEnter  SchedDebugEnter
	#define CHK_SchedDebugEnter  TRUE
	#define EXP_SchedDebugEnter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedDebugEnter", (RTS_UINTPTR)SchedDebugEnter, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedDebugEnter
	#define EXT_CmpScheduleSchedDebugEnter
	#define GET_CmpScheduleSchedDebugEnter  ERR_OK
	#define CAL_CmpScheduleSchedDebugEnter pICmpSchedule->ISchedDebugEnter
	#define CHK_CmpScheduleSchedDebugEnter (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedDebugEnter  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedDebugEnter
	#define EXT_SchedDebugEnter
	#define GET_SchedDebugEnter(fl)  CAL_CMGETAPI( "SchedDebugEnter" ) 
	#define CAL_SchedDebugEnter pICmpSchedule->ISchedDebugEnter
	#define CHK_SchedDebugEnter (pICmpSchedule != NULL)
	#define EXP_SchedDebugEnter  CAL_CMEXPAPI( "SchedDebugEnter" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedDebugEnter  PFSCHEDDEBUGENTER pfSchedDebugEnter;
	#define EXT_SchedDebugEnter  extern PFSCHEDDEBUGENTER pfSchedDebugEnter;
	#define GET_SchedDebugEnter(fl)  s_pfCMGetAPI2( "SchedDebugEnter", (RTS_VOID_FCTPTR *)&pfSchedDebugEnter, (fl), 0, 0)
	#define CAL_SchedDebugEnter  pfSchedDebugEnter
	#define CHK_SchedDebugEnter  (pfSchedDebugEnter != NULL)
	#define EXP_SchedDebugEnter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedDebugEnter", (RTS_UINTPTR)SchedDebugEnter, 0, 0) 
#endif




/**
 * <description> Leave from debugging </description>
 * <param name="hSchedTask" type="IN">Handle to task</param>
 * <result>ERR_OK</result>
 */
RTS_RESULT CDECL SchedDebugLeave(RTS_HANDLE hSchedTask);
typedef RTS_RESULT (CDECL * PFSCHEDDEBUGLEAVE) (RTS_HANDLE hSchedTask);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDDEBUGLEAVE_NOTIMPLEMENTED)
	#define USE_SchedDebugLeave
	#define EXT_SchedDebugLeave
	#define GET_SchedDebugLeave(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedDebugLeave(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SchedDebugLeave  FALSE
	#define EXP_SchedDebugLeave  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedDebugLeave
	#define EXT_SchedDebugLeave
	#define GET_SchedDebugLeave(fl)  CAL_CMGETAPI( "SchedDebugLeave" ) 
	#define CAL_SchedDebugLeave  SchedDebugLeave
	#define CHK_SchedDebugLeave  TRUE
	#define EXP_SchedDebugLeave  CAL_CMEXPAPI( "SchedDebugLeave" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedDebugLeave
	#define EXT_SchedDebugLeave
	#define GET_SchedDebugLeave(fl)  CAL_CMGETAPI( "SchedDebugLeave" ) 
	#define CAL_SchedDebugLeave  SchedDebugLeave
	#define CHK_SchedDebugLeave  TRUE
	#define EXP_SchedDebugLeave  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedDebugLeave", (RTS_UINTPTR)SchedDebugLeave, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedDebugLeave
	#define EXT_CmpScheduleSchedDebugLeave
	#define GET_CmpScheduleSchedDebugLeave  ERR_OK
	#define CAL_CmpScheduleSchedDebugLeave pICmpSchedule->ISchedDebugLeave
	#define CHK_CmpScheduleSchedDebugLeave (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedDebugLeave  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedDebugLeave
	#define EXT_SchedDebugLeave
	#define GET_SchedDebugLeave(fl)  CAL_CMGETAPI( "SchedDebugLeave" ) 
	#define CAL_SchedDebugLeave pICmpSchedule->ISchedDebugLeave
	#define CHK_SchedDebugLeave (pICmpSchedule != NULL)
	#define EXP_SchedDebugLeave  CAL_CMEXPAPI( "SchedDebugLeave" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedDebugLeave  PFSCHEDDEBUGLEAVE pfSchedDebugLeave;
	#define EXT_SchedDebugLeave  extern PFSCHEDDEBUGLEAVE pfSchedDebugLeave;
	#define GET_SchedDebugLeave(fl)  s_pfCMGetAPI2( "SchedDebugLeave", (RTS_VOID_FCTPTR *)&pfSchedDebugLeave, (fl), 0, 0)
	#define CAL_SchedDebugLeave  pfSchedDebugLeave
	#define CHK_SchedDebugLeave  (pfSchedDebugLeave != NULL)
	#define EXP_SchedDebugLeave  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedDebugLeave", (RTS_UINTPTR)SchedDebugLeave, 0, 0) 
#endif




/**
 * <description> Prepare reset, delete all IEC tasks in error state</description>
 * <result>ERR_OK</result>
 */
RTS_RESULT CDECL SchedPrepareReset(APPLICATION *pApp, int bResetOrigin);
typedef RTS_RESULT (CDECL * PFSCHEDPREPARERESET) (APPLICATION *pApp, int bResetOrigin);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDPREPARERESET_NOTIMPLEMENTED)
	#define USE_SchedPrepareReset
	#define EXT_SchedPrepareReset
	#define GET_SchedPrepareReset(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedPrepareReset(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SchedPrepareReset  FALSE
	#define EXP_SchedPrepareReset  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedPrepareReset
	#define EXT_SchedPrepareReset
	#define GET_SchedPrepareReset(fl)  CAL_CMGETAPI( "SchedPrepareReset" ) 
	#define CAL_SchedPrepareReset  SchedPrepareReset
	#define CHK_SchedPrepareReset  TRUE
	#define EXP_SchedPrepareReset  CAL_CMEXPAPI( "SchedPrepareReset" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedPrepareReset
	#define EXT_SchedPrepareReset
	#define GET_SchedPrepareReset(fl)  CAL_CMGETAPI( "SchedPrepareReset" ) 
	#define CAL_SchedPrepareReset  SchedPrepareReset
	#define CHK_SchedPrepareReset  TRUE
	#define EXP_SchedPrepareReset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedPrepareReset", (RTS_UINTPTR)SchedPrepareReset, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedPrepareReset
	#define EXT_CmpScheduleSchedPrepareReset
	#define GET_CmpScheduleSchedPrepareReset  ERR_OK
	#define CAL_CmpScheduleSchedPrepareReset pICmpSchedule->ISchedPrepareReset
	#define CHK_CmpScheduleSchedPrepareReset (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedPrepareReset  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedPrepareReset
	#define EXT_SchedPrepareReset
	#define GET_SchedPrepareReset(fl)  CAL_CMGETAPI( "SchedPrepareReset" ) 
	#define CAL_SchedPrepareReset pICmpSchedule->ISchedPrepareReset
	#define CHK_SchedPrepareReset (pICmpSchedule != NULL)
	#define EXP_SchedPrepareReset  CAL_CMEXPAPI( "SchedPrepareReset" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedPrepareReset  PFSCHEDPREPARERESET pfSchedPrepareReset;
	#define EXT_SchedPrepareReset  extern PFSCHEDPREPARERESET pfSchedPrepareReset;
	#define GET_SchedPrepareReset(fl)  s_pfCMGetAPI2( "SchedPrepareReset", (RTS_VOID_FCTPTR *)&pfSchedPrepareReset, (fl), 0, 0)
	#define CAL_SchedPrepareReset  pfSchedPrepareReset
	#define CHK_SchedPrepareReset  (pfSchedPrepareReset != NULL)
	#define EXP_SchedPrepareReset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedPrepareReset", (RTS_UINTPTR)SchedPrepareReset, 0, 0) 
#endif




/**
 * <description> Restart all IEC tasks in error state</description>
 * <result>ERR_OK</result>
 */
RTS_RESULT CDECL SchedResetDone(APPLICATION *pApp, int bResetOrigin);
typedef RTS_RESULT (CDECL * PFSCHEDRESETDONE) (APPLICATION *pApp, int bResetOrigin);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDRESETDONE_NOTIMPLEMENTED)
	#define USE_SchedResetDone
	#define EXT_SchedResetDone
	#define GET_SchedResetDone(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedResetDone(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SchedResetDone  FALSE
	#define EXP_SchedResetDone  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedResetDone
	#define EXT_SchedResetDone
	#define GET_SchedResetDone(fl)  CAL_CMGETAPI( "SchedResetDone" ) 
	#define CAL_SchedResetDone  SchedResetDone
	#define CHK_SchedResetDone  TRUE
	#define EXP_SchedResetDone  CAL_CMEXPAPI( "SchedResetDone" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedResetDone
	#define EXT_SchedResetDone
	#define GET_SchedResetDone(fl)  CAL_CMGETAPI( "SchedResetDone" ) 
	#define CAL_SchedResetDone  SchedResetDone
	#define CHK_SchedResetDone  TRUE
	#define EXP_SchedResetDone  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedResetDone", (RTS_UINTPTR)SchedResetDone, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedResetDone
	#define EXT_CmpScheduleSchedResetDone
	#define GET_CmpScheduleSchedResetDone  ERR_OK
	#define CAL_CmpScheduleSchedResetDone pICmpSchedule->ISchedResetDone
	#define CHK_CmpScheduleSchedResetDone (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedResetDone  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedResetDone
	#define EXT_SchedResetDone
	#define GET_SchedResetDone(fl)  CAL_CMGETAPI( "SchedResetDone" ) 
	#define CAL_SchedResetDone pICmpSchedule->ISchedResetDone
	#define CHK_SchedResetDone (pICmpSchedule != NULL)
	#define EXP_SchedResetDone  CAL_CMEXPAPI( "SchedResetDone" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedResetDone  PFSCHEDRESETDONE pfSchedResetDone;
	#define EXT_SchedResetDone  extern PFSCHEDRESETDONE pfSchedResetDone;
	#define GET_SchedResetDone(fl)  s_pfCMGetAPI2( "SchedResetDone", (RTS_VOID_FCTPTR *)&pfSchedResetDone, (fl), 0, 0)
	#define CAL_SchedResetDone  pfSchedResetDone
	#define CHK_SchedResetDone  (pfSchedResetDone != NULL)
	#define EXP_SchedResetDone  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedResetDone", (RTS_UINTPTR)SchedResetDone, 0, 0) 
#endif




/**
 * <description>
 * <p>Start scheduling of all tasks of an application</p>
 * </description>
 * <param name="pApp" type="IN" range="[NULL,VALID_APPLICATION]">APPLICATION object</param>
 * <parampseudo name="bTaskIsValid" type="IN" range="[0,1]">Task is valid</parampseudo>
 * <parampseudo name="bTimerIsStarted" type="IN" range="[0,1]">Timer was started</parampseudo>
 * <parampseudo name="_pApp" type="IN" range="[NULL,VALID_APPLICATION]">Application registered for this Task</parampseudo>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">All tasks started successfully</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Internal Error of the scheduler</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No task found in application</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">pApp was NULL</errorcode>
 */
RTS_RESULT CDECL SchedStart(APPLICATION *pApp);
typedef RTS_RESULT (CDECL * PFSCHEDSTART) (APPLICATION *pApp);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDSTART_NOTIMPLEMENTED)
	#define USE_SchedStart
	#define EXT_SchedStart
	#define GET_SchedStart(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedStart(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SchedStart  FALSE
	#define EXP_SchedStart  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedStart
	#define EXT_SchedStart
	#define GET_SchedStart(fl)  CAL_CMGETAPI( "SchedStart" ) 
	#define CAL_SchedStart  SchedStart
	#define CHK_SchedStart  TRUE
	#define EXP_SchedStart  CAL_CMEXPAPI( "SchedStart" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedStart
	#define EXT_SchedStart
	#define GET_SchedStart(fl)  CAL_CMGETAPI( "SchedStart" ) 
	#define CAL_SchedStart  SchedStart
	#define CHK_SchedStart  TRUE
	#define EXP_SchedStart  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedStart", (RTS_UINTPTR)SchedStart, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedStart
	#define EXT_CmpScheduleSchedStart
	#define GET_CmpScheduleSchedStart  ERR_OK
	#define CAL_CmpScheduleSchedStart pICmpSchedule->ISchedStart
	#define CHK_CmpScheduleSchedStart (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedStart  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedStart
	#define EXT_SchedStart
	#define GET_SchedStart(fl)  CAL_CMGETAPI( "SchedStart" ) 
	#define CAL_SchedStart pICmpSchedule->ISchedStart
	#define CHK_SchedStart (pICmpSchedule != NULL)
	#define EXP_SchedStart  CAL_CMEXPAPI( "SchedStart" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedStart  PFSCHEDSTART pfSchedStart;
	#define EXT_SchedStart  extern PFSCHEDSTART pfSchedStart;
	#define GET_SchedStart(fl)  s_pfCMGetAPI2( "SchedStart", (RTS_VOID_FCTPTR *)&pfSchedStart, (fl), 0, 0)
	#define CAL_SchedStart  pfSchedStart
	#define CHK_SchedStart  (pfSchedStart != NULL)
	#define EXP_SchedStart  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedStart", (RTS_UINTPTR)SchedStart, 0, 0) 
#endif




/**
 * <description> Stop scheduling all tasks specified by application </description>
 * <param name="pApp" type="IN">APPLICATION object</param>
 * <param name="hTaskToExclude" type="IN">Handle of task to exclude from scheduling.
 *	hTask=RTS_INVALID_HANDLE, all tasks are disabled</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SchedStop(APPLICATION *pApp, RTS_HANDLE hTaskToExclude);
typedef RTS_RESULT (CDECL * PFSCHEDSTOP) (APPLICATION *pApp, RTS_HANDLE hTaskToExclude);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDSTOP_NOTIMPLEMENTED)
	#define USE_SchedStop
	#define EXT_SchedStop
	#define GET_SchedStop(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedStop(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SchedStop  FALSE
	#define EXP_SchedStop  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedStop
	#define EXT_SchedStop
	#define GET_SchedStop(fl)  CAL_CMGETAPI( "SchedStop" ) 
	#define CAL_SchedStop  SchedStop
	#define CHK_SchedStop  TRUE
	#define EXP_SchedStop  CAL_CMEXPAPI( "SchedStop" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedStop
	#define EXT_SchedStop
	#define GET_SchedStop(fl)  CAL_CMGETAPI( "SchedStop" ) 
	#define CAL_SchedStop  SchedStop
	#define CHK_SchedStop  TRUE
	#define EXP_SchedStop  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedStop", (RTS_UINTPTR)SchedStop, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedStop
	#define EXT_CmpScheduleSchedStop
	#define GET_CmpScheduleSchedStop  ERR_OK
	#define CAL_CmpScheduleSchedStop pICmpSchedule->ISchedStop
	#define CHK_CmpScheduleSchedStop (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedStop  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedStop
	#define EXT_SchedStop
	#define GET_SchedStop(fl)  CAL_CMGETAPI( "SchedStop" ) 
	#define CAL_SchedStop pICmpSchedule->ISchedStop
	#define CHK_SchedStop (pICmpSchedule != NULL)
	#define EXP_SchedStop  CAL_CMEXPAPI( "SchedStop" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedStop  PFSCHEDSTOP pfSchedStop;
	#define EXT_SchedStop  extern PFSCHEDSTOP pfSchedStop;
	#define GET_SchedStop(fl)  s_pfCMGetAPI2( "SchedStop", (RTS_VOID_FCTPTR *)&pfSchedStop, (fl), 0, 0)
	#define CAL_SchedStop  pfSchedStop
	#define CHK_SchedStop  (pfSchedStop != NULL)
	#define EXP_SchedStop  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedStop", (RTS_UINTPTR)SchedStop, 0, 0) 
#endif




/**
 * <description>Is called to get the schedule handle of the current running task</description>
 * <param name="ppTask" type="OUT">Task description for the IecTask component. Can be NULL.</param>
 * <param name="pResult" type="OUT">ERR_OK or Error code</param>
 * <result>Handle to the current running task or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL SchedGetCurrentTask(Task_Desc **ppTask, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSCHEDGETCURRENTTASK) (Task_Desc **ppTask, RTS_RESULT *pResult);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDGETCURRENTTASK_NOTIMPLEMENTED)
	#define USE_SchedGetCurrentTask
	#define EXT_SchedGetCurrentTask
	#define GET_SchedGetCurrentTask(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedGetCurrentTask(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SchedGetCurrentTask  FALSE
	#define EXP_SchedGetCurrentTask  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedGetCurrentTask
	#define EXT_SchedGetCurrentTask
	#define GET_SchedGetCurrentTask(fl)  CAL_CMGETAPI( "SchedGetCurrentTask" ) 
	#define CAL_SchedGetCurrentTask  SchedGetCurrentTask
	#define CHK_SchedGetCurrentTask  TRUE
	#define EXP_SchedGetCurrentTask  CAL_CMEXPAPI( "SchedGetCurrentTask" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedGetCurrentTask
	#define EXT_SchedGetCurrentTask
	#define GET_SchedGetCurrentTask(fl)  CAL_CMGETAPI( "SchedGetCurrentTask" ) 
	#define CAL_SchedGetCurrentTask  SchedGetCurrentTask
	#define CHK_SchedGetCurrentTask  TRUE
	#define EXP_SchedGetCurrentTask  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetCurrentTask", (RTS_UINTPTR)SchedGetCurrentTask, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedGetCurrentTask
	#define EXT_CmpScheduleSchedGetCurrentTask
	#define GET_CmpScheduleSchedGetCurrentTask  ERR_OK
	#define CAL_CmpScheduleSchedGetCurrentTask pICmpSchedule->ISchedGetCurrentTask
	#define CHK_CmpScheduleSchedGetCurrentTask (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedGetCurrentTask  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedGetCurrentTask
	#define EXT_SchedGetCurrentTask
	#define GET_SchedGetCurrentTask(fl)  CAL_CMGETAPI( "SchedGetCurrentTask" ) 
	#define CAL_SchedGetCurrentTask pICmpSchedule->ISchedGetCurrentTask
	#define CHK_SchedGetCurrentTask (pICmpSchedule != NULL)
	#define EXP_SchedGetCurrentTask  CAL_CMEXPAPI( "SchedGetCurrentTask" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedGetCurrentTask  PFSCHEDGETCURRENTTASK pfSchedGetCurrentTask;
	#define EXT_SchedGetCurrentTask  extern PFSCHEDGETCURRENTTASK pfSchedGetCurrentTask;
	#define GET_SchedGetCurrentTask(fl)  s_pfCMGetAPI2( "SchedGetCurrentTask", (RTS_VOID_FCTPTR *)&pfSchedGetCurrentTask, (fl), 0, 0)
	#define CAL_SchedGetCurrentTask  pfSchedGetCurrentTask
	#define CHK_SchedGetCurrentTask  (pfSchedGetCurrentTask != NULL)
	#define EXP_SchedGetCurrentTask  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetCurrentTask", (RTS_UINTPTR)SchedGetCurrentTask, 0, 0) 
#endif




/**
 * <description>Get context of the specified task</description>
 * <param name="hSchedTask" type="IN">Scheduler task handle</param>
 * <param name="pContext" type="IN">Pointer to register context</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SchedGetContext(RTS_HANDLE hSchedTask, RegContext *pContext);
typedef RTS_RESULT (CDECL * PFSCHEDGETCONTEXT) (RTS_HANDLE hSchedTask, RegContext *pContext);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDGETCONTEXT_NOTIMPLEMENTED)
	#define USE_SchedGetContext
	#define EXT_SchedGetContext
	#define GET_SchedGetContext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedGetContext(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SchedGetContext  FALSE
	#define EXP_SchedGetContext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedGetContext
	#define EXT_SchedGetContext
	#define GET_SchedGetContext(fl)  CAL_CMGETAPI( "SchedGetContext" ) 
	#define CAL_SchedGetContext  SchedGetContext
	#define CHK_SchedGetContext  TRUE
	#define EXP_SchedGetContext  CAL_CMEXPAPI( "SchedGetContext" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedGetContext
	#define EXT_SchedGetContext
	#define GET_SchedGetContext(fl)  CAL_CMGETAPI( "SchedGetContext" ) 
	#define CAL_SchedGetContext  SchedGetContext
	#define CHK_SchedGetContext  TRUE
	#define EXP_SchedGetContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetContext", (RTS_UINTPTR)SchedGetContext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedGetContext
	#define EXT_CmpScheduleSchedGetContext
	#define GET_CmpScheduleSchedGetContext  ERR_OK
	#define CAL_CmpScheduleSchedGetContext pICmpSchedule->ISchedGetContext
	#define CHK_CmpScheduleSchedGetContext (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedGetContext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedGetContext
	#define EXT_SchedGetContext
	#define GET_SchedGetContext(fl)  CAL_CMGETAPI( "SchedGetContext" ) 
	#define CAL_SchedGetContext pICmpSchedule->ISchedGetContext
	#define CHK_SchedGetContext (pICmpSchedule != NULL)
	#define EXP_SchedGetContext  CAL_CMEXPAPI( "SchedGetContext" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedGetContext  PFSCHEDGETCONTEXT pfSchedGetContext;
	#define EXT_SchedGetContext  extern PFSCHEDGETCONTEXT pfSchedGetContext;
	#define GET_SchedGetContext(fl)  s_pfCMGetAPI2( "SchedGetContext", (RTS_VOID_FCTPTR *)&pfSchedGetContext, (fl), 0, 0)
	#define CAL_SchedGetContext  pfSchedGetContext
	#define CHK_SchedGetContext  (pfSchedGetContext != NULL)
	#define EXP_SchedGetContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetContext", (RTS_UINTPTR)SchedGetContext, 0, 0) 
#endif




/**
 * <description>
 *	Is called to get the number of all registerd IEC tasks in the scheduler.
 * </description>
 * <param name="pApp" type="IN">If an application is specified, only the tasks of this application is returned.
 *	If NULL, number of all tasks is returned.
 * </param>
 * <param name="pResult" type="OUT">ERR_OK or Error code</param>
 * <result>Number of tasks</result>
 */
int CDECL SchedGetNumOfTasks(APPLICATION *pApp, RTS_RESULT *pResult);
typedef int (CDECL * PFSCHEDGETNUMOFTASKS) (APPLICATION *pApp, RTS_RESULT *pResult);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDGETNUMOFTASKS_NOTIMPLEMENTED)
	#define USE_SchedGetNumOfTasks
	#define EXT_SchedGetNumOfTasks
	#define GET_SchedGetNumOfTasks(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedGetNumOfTasks(p0,p1)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SchedGetNumOfTasks  FALSE
	#define EXP_SchedGetNumOfTasks  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedGetNumOfTasks
	#define EXT_SchedGetNumOfTasks
	#define GET_SchedGetNumOfTasks(fl)  CAL_CMGETAPI( "SchedGetNumOfTasks" ) 
	#define CAL_SchedGetNumOfTasks  SchedGetNumOfTasks
	#define CHK_SchedGetNumOfTasks  TRUE
	#define EXP_SchedGetNumOfTasks  CAL_CMEXPAPI( "SchedGetNumOfTasks" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedGetNumOfTasks
	#define EXT_SchedGetNumOfTasks
	#define GET_SchedGetNumOfTasks(fl)  CAL_CMGETAPI( "SchedGetNumOfTasks" ) 
	#define CAL_SchedGetNumOfTasks  SchedGetNumOfTasks
	#define CHK_SchedGetNumOfTasks  TRUE
	#define EXP_SchedGetNumOfTasks  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetNumOfTasks", (RTS_UINTPTR)SchedGetNumOfTasks, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedGetNumOfTasks
	#define EXT_CmpScheduleSchedGetNumOfTasks
	#define GET_CmpScheduleSchedGetNumOfTasks  ERR_OK
	#define CAL_CmpScheduleSchedGetNumOfTasks pICmpSchedule->ISchedGetNumOfTasks
	#define CHK_CmpScheduleSchedGetNumOfTasks (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedGetNumOfTasks  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedGetNumOfTasks
	#define EXT_SchedGetNumOfTasks
	#define GET_SchedGetNumOfTasks(fl)  CAL_CMGETAPI( "SchedGetNumOfTasks" ) 
	#define CAL_SchedGetNumOfTasks pICmpSchedule->ISchedGetNumOfTasks
	#define CHK_SchedGetNumOfTasks (pICmpSchedule != NULL)
	#define EXP_SchedGetNumOfTasks  CAL_CMEXPAPI( "SchedGetNumOfTasks" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedGetNumOfTasks  PFSCHEDGETNUMOFTASKS pfSchedGetNumOfTasks;
	#define EXT_SchedGetNumOfTasks  extern PFSCHEDGETNUMOFTASKS pfSchedGetNumOfTasks;
	#define GET_SchedGetNumOfTasks(fl)  s_pfCMGetAPI2( "SchedGetNumOfTasks", (RTS_VOID_FCTPTR *)&pfSchedGetNumOfTasks, (fl), 0, 0)
	#define CAL_SchedGetNumOfTasks  pfSchedGetNumOfTasks
	#define CHK_SchedGetNumOfTasks  (pfSchedGetNumOfTasks != NULL)
	#define EXP_SchedGetNumOfTasks  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetNumOfTasks", (RTS_UINTPTR)SchedGetNumOfTasks, 0, 0) 
#endif




/**
 * <description>
 *	Function returns the task description of a task specified by an index.
 * </description>
 * <param name="pApp" type="IN">If an application is specified, only the task of this application is returned.
 *	If NULL, the task with the index in all tasks i returned.
 * </param>
 * <param name="pResult" type="OUT">ERR_OK or Error code</param>
 * <result>Task description</result>
 */
Task_Desc * CDECL SchedGetTaskDescByIndex(APPLICATION *pApp, int iIndex, RTS_RESULT *pResult);
typedef Task_Desc * (CDECL * PFSCHEDGETTASKDESCBYINDEX) (APPLICATION *pApp, int iIndex, RTS_RESULT *pResult);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDGETTASKDESCBYINDEX_NOTIMPLEMENTED)
	#define USE_SchedGetTaskDescByIndex
	#define EXT_SchedGetTaskDescByIndex
	#define GET_SchedGetTaskDescByIndex(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedGetTaskDescByIndex(p0,p1,p2)  (Task_Desc *)ERR_NOTIMPLEMENTED
	#define CHK_SchedGetTaskDescByIndex  FALSE
	#define EXP_SchedGetTaskDescByIndex  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedGetTaskDescByIndex
	#define EXT_SchedGetTaskDescByIndex
	#define GET_SchedGetTaskDescByIndex(fl)  CAL_CMGETAPI( "SchedGetTaskDescByIndex" ) 
	#define CAL_SchedGetTaskDescByIndex  SchedGetTaskDescByIndex
	#define CHK_SchedGetTaskDescByIndex  TRUE
	#define EXP_SchedGetTaskDescByIndex  CAL_CMEXPAPI( "SchedGetTaskDescByIndex" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedGetTaskDescByIndex
	#define EXT_SchedGetTaskDescByIndex
	#define GET_SchedGetTaskDescByIndex(fl)  CAL_CMGETAPI( "SchedGetTaskDescByIndex" ) 
	#define CAL_SchedGetTaskDescByIndex  SchedGetTaskDescByIndex
	#define CHK_SchedGetTaskDescByIndex  TRUE
	#define EXP_SchedGetTaskDescByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetTaskDescByIndex", (RTS_UINTPTR)SchedGetTaskDescByIndex, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedGetTaskDescByIndex
	#define EXT_CmpScheduleSchedGetTaskDescByIndex
	#define GET_CmpScheduleSchedGetTaskDescByIndex  ERR_OK
	#define CAL_CmpScheduleSchedGetTaskDescByIndex pICmpSchedule->ISchedGetTaskDescByIndex
	#define CHK_CmpScheduleSchedGetTaskDescByIndex (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedGetTaskDescByIndex  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedGetTaskDescByIndex
	#define EXT_SchedGetTaskDescByIndex
	#define GET_SchedGetTaskDescByIndex(fl)  CAL_CMGETAPI( "SchedGetTaskDescByIndex" ) 
	#define CAL_SchedGetTaskDescByIndex pICmpSchedule->ISchedGetTaskDescByIndex
	#define CHK_SchedGetTaskDescByIndex (pICmpSchedule != NULL)
	#define EXP_SchedGetTaskDescByIndex  CAL_CMEXPAPI( "SchedGetTaskDescByIndex" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedGetTaskDescByIndex  PFSCHEDGETTASKDESCBYINDEX pfSchedGetTaskDescByIndex;
	#define EXT_SchedGetTaskDescByIndex  extern PFSCHEDGETTASKDESCBYINDEX pfSchedGetTaskDescByIndex;
	#define GET_SchedGetTaskDescByIndex(fl)  s_pfCMGetAPI2( "SchedGetTaskDescByIndex", (RTS_VOID_FCTPTR *)&pfSchedGetTaskDescByIndex, (fl), 0, 0)
	#define CAL_SchedGetTaskDescByIndex  pfSchedGetTaskDescByIndex
	#define CHK_SchedGetTaskDescByIndex  (pfSchedGetTaskDescByIndex != NULL)
	#define EXP_SchedGetTaskDescByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetTaskDescByIndex", (RTS_UINTPTR)SchedGetTaskDescByIndex, 0, 0) 
#endif




/**
 * <description>
 *	Function returns the task description of a task specified by handle.
 * </description>
 * <param name="hSchedTask" type="IN">Handle of the task</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Task description</result>
 */
Task_Desc * CDECL SchedGetTaskDescByHandle(RTS_HANDLE hSchedTask, RTS_RESULT *pResult);
typedef Task_Desc * (CDECL * PFSCHEDGETTASKDESCBYHANDLE) (RTS_HANDLE hSchedTask, RTS_RESULT *pResult);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDGETTASKDESCBYHANDLE_NOTIMPLEMENTED)
	#define USE_SchedGetTaskDescByHandle
	#define EXT_SchedGetTaskDescByHandle
	#define GET_SchedGetTaskDescByHandle(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedGetTaskDescByHandle(p0,p1)  (Task_Desc *)ERR_NOTIMPLEMENTED
	#define CHK_SchedGetTaskDescByHandle  FALSE
	#define EXP_SchedGetTaskDescByHandle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedGetTaskDescByHandle
	#define EXT_SchedGetTaskDescByHandle
	#define GET_SchedGetTaskDescByHandle(fl)  CAL_CMGETAPI( "SchedGetTaskDescByHandle" ) 
	#define CAL_SchedGetTaskDescByHandle  SchedGetTaskDescByHandle
	#define CHK_SchedGetTaskDescByHandle  TRUE
	#define EXP_SchedGetTaskDescByHandle  CAL_CMEXPAPI( "SchedGetTaskDescByHandle" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedGetTaskDescByHandle
	#define EXT_SchedGetTaskDescByHandle
	#define GET_SchedGetTaskDescByHandle(fl)  CAL_CMGETAPI( "SchedGetTaskDescByHandle" ) 
	#define CAL_SchedGetTaskDescByHandle  SchedGetTaskDescByHandle
	#define CHK_SchedGetTaskDescByHandle  TRUE
	#define EXP_SchedGetTaskDescByHandle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetTaskDescByHandle", (RTS_UINTPTR)SchedGetTaskDescByHandle, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedGetTaskDescByHandle
	#define EXT_CmpScheduleSchedGetTaskDescByHandle
	#define GET_CmpScheduleSchedGetTaskDescByHandle  ERR_OK
	#define CAL_CmpScheduleSchedGetTaskDescByHandle pICmpSchedule->ISchedGetTaskDescByHandle
	#define CHK_CmpScheduleSchedGetTaskDescByHandle (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedGetTaskDescByHandle  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedGetTaskDescByHandle
	#define EXT_SchedGetTaskDescByHandle
	#define GET_SchedGetTaskDescByHandle(fl)  CAL_CMGETAPI( "SchedGetTaskDescByHandle" ) 
	#define CAL_SchedGetTaskDescByHandle pICmpSchedule->ISchedGetTaskDescByHandle
	#define CHK_SchedGetTaskDescByHandle (pICmpSchedule != NULL)
	#define EXP_SchedGetTaskDescByHandle  CAL_CMEXPAPI( "SchedGetTaskDescByHandle" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedGetTaskDescByHandle  PFSCHEDGETTASKDESCBYHANDLE pfSchedGetTaskDescByHandle;
	#define EXT_SchedGetTaskDescByHandle  extern PFSCHEDGETTASKDESCBYHANDLE pfSchedGetTaskDescByHandle;
	#define GET_SchedGetTaskDescByHandle(fl)  s_pfCMGetAPI2( "SchedGetTaskDescByHandle", (RTS_VOID_FCTPTR *)&pfSchedGetTaskDescByHandle, (fl), 0, 0)
	#define CAL_SchedGetTaskDescByHandle  pfSchedGetTaskDescByHandle
	#define CHK_SchedGetTaskDescByHandle  (pfSchedGetTaskDescByHandle != NULL)
	#define EXP_SchedGetTaskDescByHandle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetTaskDescByHandle", (RTS_UINTPTR)SchedGetTaskDescByHandle, 0, 0) 
#endif




/**
 * <description>
 *	Function returns the task handle of a task specified by an index.
 * </description>
 * <param name="pApp" type="IN">If an application is specified, only the task of this application is returned.
 *	If NULL, the task with the index in all tasks i returned.
 * </param>
 * <param name="pResult" type="OUT">ERR_OK or Error code</param>
 * <result>Handle to the task</result>
 */
RTS_HANDLE CDECL SchedGetTaskHandleByIndex(APPLICATION *pApp, int iIndex, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSCHEDGETTASKHANDLEBYINDEX) (APPLICATION *pApp, int iIndex, RTS_RESULT *pResult);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDGETTASKHANDLEBYINDEX_NOTIMPLEMENTED)
	#define USE_SchedGetTaskHandleByIndex
	#define EXT_SchedGetTaskHandleByIndex
	#define GET_SchedGetTaskHandleByIndex(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedGetTaskHandleByIndex(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SchedGetTaskHandleByIndex  FALSE
	#define EXP_SchedGetTaskHandleByIndex  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedGetTaskHandleByIndex
	#define EXT_SchedGetTaskHandleByIndex
	#define GET_SchedGetTaskHandleByIndex(fl)  CAL_CMGETAPI( "SchedGetTaskHandleByIndex" ) 
	#define CAL_SchedGetTaskHandleByIndex  SchedGetTaskHandleByIndex
	#define CHK_SchedGetTaskHandleByIndex  TRUE
	#define EXP_SchedGetTaskHandleByIndex  CAL_CMEXPAPI( "SchedGetTaskHandleByIndex" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedGetTaskHandleByIndex
	#define EXT_SchedGetTaskHandleByIndex
	#define GET_SchedGetTaskHandleByIndex(fl)  CAL_CMGETAPI( "SchedGetTaskHandleByIndex" ) 
	#define CAL_SchedGetTaskHandleByIndex  SchedGetTaskHandleByIndex
	#define CHK_SchedGetTaskHandleByIndex  TRUE
	#define EXP_SchedGetTaskHandleByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetTaskHandleByIndex", (RTS_UINTPTR)SchedGetTaskHandleByIndex, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedGetTaskHandleByIndex
	#define EXT_CmpScheduleSchedGetTaskHandleByIndex
	#define GET_CmpScheduleSchedGetTaskHandleByIndex  ERR_OK
	#define CAL_CmpScheduleSchedGetTaskHandleByIndex pICmpSchedule->ISchedGetTaskHandleByIndex
	#define CHK_CmpScheduleSchedGetTaskHandleByIndex (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedGetTaskHandleByIndex  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedGetTaskHandleByIndex
	#define EXT_SchedGetTaskHandleByIndex
	#define GET_SchedGetTaskHandleByIndex(fl)  CAL_CMGETAPI( "SchedGetTaskHandleByIndex" ) 
	#define CAL_SchedGetTaskHandleByIndex pICmpSchedule->ISchedGetTaskHandleByIndex
	#define CHK_SchedGetTaskHandleByIndex (pICmpSchedule != NULL)
	#define EXP_SchedGetTaskHandleByIndex  CAL_CMEXPAPI( "SchedGetTaskHandleByIndex" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedGetTaskHandleByIndex  PFSCHEDGETTASKHANDLEBYINDEX pfSchedGetTaskHandleByIndex;
	#define EXT_SchedGetTaskHandleByIndex  extern PFSCHEDGETTASKHANDLEBYINDEX pfSchedGetTaskHandleByIndex;
	#define GET_SchedGetTaskHandleByIndex(fl)  s_pfCMGetAPI2( "SchedGetTaskHandleByIndex", (RTS_VOID_FCTPTR *)&pfSchedGetTaskHandleByIndex, (fl), 0, 0)
	#define CAL_SchedGetTaskHandleByIndex  pfSchedGetTaskHandleByIndex
	#define CHK_SchedGetTaskHandleByIndex  (pfSchedGetTaskHandleByIndex != NULL)
	#define EXP_SchedGetTaskHandleByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetTaskHandleByIndex", (RTS_UINTPTR)SchedGetTaskHandleByIndex, 0, 0) 
#endif




/**
 * <description>
 *	Function returns the handle to the task specified by name.
 * </description>
 * <param name="pszTaskName" type="IN">Task name</param>
 * <param name="pResult" type="OUT">ERR_OK or Error code</param>
 * <result>Scheduler task handle</result>
 */
RTS_HANDLE CDECL SchedGetTaskHandleByName(char *pszTaskName, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSCHEDGETTASKHANDLEBYNAME) (char *pszTaskName, RTS_RESULT *pResult);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDGETTASKHANDLEBYNAME_NOTIMPLEMENTED)
	#define USE_SchedGetTaskHandleByName
	#define EXT_SchedGetTaskHandleByName
	#define GET_SchedGetTaskHandleByName(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedGetTaskHandleByName(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SchedGetTaskHandleByName  FALSE
	#define EXP_SchedGetTaskHandleByName  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedGetTaskHandleByName
	#define EXT_SchedGetTaskHandleByName
	#define GET_SchedGetTaskHandleByName(fl)  CAL_CMGETAPI( "SchedGetTaskHandleByName" ) 
	#define CAL_SchedGetTaskHandleByName  SchedGetTaskHandleByName
	#define CHK_SchedGetTaskHandleByName  TRUE
	#define EXP_SchedGetTaskHandleByName  CAL_CMEXPAPI( "SchedGetTaskHandleByName" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedGetTaskHandleByName
	#define EXT_SchedGetTaskHandleByName
	#define GET_SchedGetTaskHandleByName(fl)  CAL_CMGETAPI( "SchedGetTaskHandleByName" ) 
	#define CAL_SchedGetTaskHandleByName  SchedGetTaskHandleByName
	#define CHK_SchedGetTaskHandleByName  TRUE
	#define EXP_SchedGetTaskHandleByName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetTaskHandleByName", (RTS_UINTPTR)SchedGetTaskHandleByName, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedGetTaskHandleByName
	#define EXT_CmpScheduleSchedGetTaskHandleByName
	#define GET_CmpScheduleSchedGetTaskHandleByName  ERR_OK
	#define CAL_CmpScheduleSchedGetTaskHandleByName pICmpSchedule->ISchedGetTaskHandleByName
	#define CHK_CmpScheduleSchedGetTaskHandleByName (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedGetTaskHandleByName  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedGetTaskHandleByName
	#define EXT_SchedGetTaskHandleByName
	#define GET_SchedGetTaskHandleByName(fl)  CAL_CMGETAPI( "SchedGetTaskHandleByName" ) 
	#define CAL_SchedGetTaskHandleByName pICmpSchedule->ISchedGetTaskHandleByName
	#define CHK_SchedGetTaskHandleByName (pICmpSchedule != NULL)
	#define EXP_SchedGetTaskHandleByName  CAL_CMEXPAPI( "SchedGetTaskHandleByName" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedGetTaskHandleByName  PFSCHEDGETTASKHANDLEBYNAME pfSchedGetTaskHandleByName;
	#define EXT_SchedGetTaskHandleByName  extern PFSCHEDGETTASKHANDLEBYNAME pfSchedGetTaskHandleByName;
	#define GET_SchedGetTaskHandleByName(fl)  s_pfCMGetAPI2( "SchedGetTaskHandleByName", (RTS_VOID_FCTPTR *)&pfSchedGetTaskHandleByName, (fl), 0, 0)
	#define CAL_SchedGetTaskHandleByName  pfSchedGetTaskHandleByName
	#define CHK_SchedGetTaskHandleByName  (pfSchedGetTaskHandleByName != NULL)
	#define EXP_SchedGetTaskHandleByName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetTaskHandleByName", (RTS_UINTPTR)SchedGetTaskHandleByName, 0, 0) 
#endif




/**
 * <description>
 *	Function returns the handle to the task event. With this event a task can be activaed externally,
 *	e.g. for external triggered event tasks. The event can be sent by SysEventSet(EventHandle);
 * </description>
 * <param name="hSchedTask" type="IN">Scheduler task handle</param>
 * <param name="pResult" type="OUT">ERR_OK or Error code</param>
 * <result>Event handle</result>
 */
RTS_HANDLE CDECL SchedGetTaskEventByHandle(RTS_HANDLE hSchedTask, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSCHEDGETTASKEVENTBYHANDLE) (RTS_HANDLE hSchedTask, RTS_RESULT *pResult);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDGETTASKEVENTBYHANDLE_NOTIMPLEMENTED)
	#define USE_SchedGetTaskEventByHandle
	#define EXT_SchedGetTaskEventByHandle
	#define GET_SchedGetTaskEventByHandle(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedGetTaskEventByHandle(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SchedGetTaskEventByHandle  FALSE
	#define EXP_SchedGetTaskEventByHandle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedGetTaskEventByHandle
	#define EXT_SchedGetTaskEventByHandle
	#define GET_SchedGetTaskEventByHandle(fl)  CAL_CMGETAPI( "SchedGetTaskEventByHandle" ) 
	#define CAL_SchedGetTaskEventByHandle  SchedGetTaskEventByHandle
	#define CHK_SchedGetTaskEventByHandle  TRUE
	#define EXP_SchedGetTaskEventByHandle  CAL_CMEXPAPI( "SchedGetTaskEventByHandle" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedGetTaskEventByHandle
	#define EXT_SchedGetTaskEventByHandle
	#define GET_SchedGetTaskEventByHandle(fl)  CAL_CMGETAPI( "SchedGetTaskEventByHandle" ) 
	#define CAL_SchedGetTaskEventByHandle  SchedGetTaskEventByHandle
	#define CHK_SchedGetTaskEventByHandle  TRUE
	#define EXP_SchedGetTaskEventByHandle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetTaskEventByHandle", (RTS_UINTPTR)SchedGetTaskEventByHandle, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedGetTaskEventByHandle
	#define EXT_CmpScheduleSchedGetTaskEventByHandle
	#define GET_CmpScheduleSchedGetTaskEventByHandle  ERR_OK
	#define CAL_CmpScheduleSchedGetTaskEventByHandle pICmpSchedule->ISchedGetTaskEventByHandle
	#define CHK_CmpScheduleSchedGetTaskEventByHandle (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedGetTaskEventByHandle  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedGetTaskEventByHandle
	#define EXT_SchedGetTaskEventByHandle
	#define GET_SchedGetTaskEventByHandle(fl)  CAL_CMGETAPI( "SchedGetTaskEventByHandle" ) 
	#define CAL_SchedGetTaskEventByHandle pICmpSchedule->ISchedGetTaskEventByHandle
	#define CHK_SchedGetTaskEventByHandle (pICmpSchedule != NULL)
	#define EXP_SchedGetTaskEventByHandle  CAL_CMEXPAPI( "SchedGetTaskEventByHandle" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedGetTaskEventByHandle  PFSCHEDGETTASKEVENTBYHANDLE pfSchedGetTaskEventByHandle;
	#define EXT_SchedGetTaskEventByHandle  extern PFSCHEDGETTASKEVENTBYHANDLE pfSchedGetTaskEventByHandle;
	#define GET_SchedGetTaskEventByHandle(fl)  s_pfCMGetAPI2( "SchedGetTaskEventByHandle", (RTS_VOID_FCTPTR *)&pfSchedGetTaskEventByHandle, (fl), 0, 0)
	#define CAL_SchedGetTaskEventByHandle  pfSchedGetTaskEventByHandle
	#define CHK_SchedGetTaskEventByHandle  (pfSchedGetTaskEventByHandle != NULL)
	#define EXP_SchedGetTaskEventByHandle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetTaskEventByHandle", (RTS_UINTPTR)SchedGetTaskEventByHandle, 0, 0) 
#endif




/**
 * <description>Begin of the plc timeslice. Can be called by an external component, if external timselicing
 *	is enabled.
 * </description>
 * <result>error code</result>
 */
RTS_RESULT CDECL SchedTimeslicePlcBegin(void);
typedef RTS_RESULT (CDECL * PFSCHEDTIMESLICEPLCBEGIN) (void);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDTIMESLICEPLCBEGIN_NOTIMPLEMENTED)
	#define USE_SchedTimeslicePlcBegin
	#define EXT_SchedTimeslicePlcBegin
	#define GET_SchedTimeslicePlcBegin(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedTimeslicePlcBegin()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SchedTimeslicePlcBegin  FALSE
	#define EXP_SchedTimeslicePlcBegin  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedTimeslicePlcBegin
	#define EXT_SchedTimeslicePlcBegin
	#define GET_SchedTimeslicePlcBegin(fl)  CAL_CMGETAPI( "SchedTimeslicePlcBegin" ) 
	#define CAL_SchedTimeslicePlcBegin  SchedTimeslicePlcBegin
	#define CHK_SchedTimeslicePlcBegin  TRUE
	#define EXP_SchedTimeslicePlcBegin  CAL_CMEXPAPI( "SchedTimeslicePlcBegin" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedTimeslicePlcBegin
	#define EXT_SchedTimeslicePlcBegin
	#define GET_SchedTimeslicePlcBegin(fl)  CAL_CMGETAPI( "SchedTimeslicePlcBegin" ) 
	#define CAL_SchedTimeslicePlcBegin  SchedTimeslicePlcBegin
	#define CHK_SchedTimeslicePlcBegin  TRUE
	#define EXP_SchedTimeslicePlcBegin  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedTimeslicePlcBegin", (RTS_UINTPTR)SchedTimeslicePlcBegin, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedTimeslicePlcBegin
	#define EXT_CmpScheduleSchedTimeslicePlcBegin
	#define GET_CmpScheduleSchedTimeslicePlcBegin  ERR_OK
	#define CAL_CmpScheduleSchedTimeslicePlcBegin pICmpSchedule->ISchedTimeslicePlcBegin
	#define CHK_CmpScheduleSchedTimeslicePlcBegin (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedTimeslicePlcBegin  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedTimeslicePlcBegin
	#define EXT_SchedTimeslicePlcBegin
	#define GET_SchedTimeslicePlcBegin(fl)  CAL_CMGETAPI( "SchedTimeslicePlcBegin" ) 
	#define CAL_SchedTimeslicePlcBegin pICmpSchedule->ISchedTimeslicePlcBegin
	#define CHK_SchedTimeslicePlcBegin (pICmpSchedule != NULL)
	#define EXP_SchedTimeslicePlcBegin  CAL_CMEXPAPI( "SchedTimeslicePlcBegin" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedTimeslicePlcBegin  PFSCHEDTIMESLICEPLCBEGIN pfSchedTimeslicePlcBegin;
	#define EXT_SchedTimeslicePlcBegin  extern PFSCHEDTIMESLICEPLCBEGIN pfSchedTimeslicePlcBegin;
	#define GET_SchedTimeslicePlcBegin(fl)  s_pfCMGetAPI2( "SchedTimeslicePlcBegin", (RTS_VOID_FCTPTR *)&pfSchedTimeslicePlcBegin, (fl), 0, 0)
	#define CAL_SchedTimeslicePlcBegin  pfSchedTimeslicePlcBegin
	#define CHK_SchedTimeslicePlcBegin  (pfSchedTimeslicePlcBegin != NULL)
	#define EXP_SchedTimeslicePlcBegin  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedTimeslicePlcBegin", (RTS_UINTPTR)SchedTimeslicePlcBegin, 0, 0) 
#endif




/**
 * <description>End of the plc timeslice. Can be called by an external component, if external timselicing
 *	is enabled.
 * </description>
 * <result>error code</result>
 */
RTS_RESULT CDECL SchedTimeslicePlcEnd(void);
typedef RTS_RESULT (CDECL * PFSCHEDTIMESLICEPLCEND) (void);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDTIMESLICEPLCEND_NOTIMPLEMENTED)
	#define USE_SchedTimeslicePlcEnd
	#define EXT_SchedTimeslicePlcEnd
	#define GET_SchedTimeslicePlcEnd(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedTimeslicePlcEnd()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SchedTimeslicePlcEnd  FALSE
	#define EXP_SchedTimeslicePlcEnd  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedTimeslicePlcEnd
	#define EXT_SchedTimeslicePlcEnd
	#define GET_SchedTimeslicePlcEnd(fl)  CAL_CMGETAPI( "SchedTimeslicePlcEnd" ) 
	#define CAL_SchedTimeslicePlcEnd  SchedTimeslicePlcEnd
	#define CHK_SchedTimeslicePlcEnd  TRUE
	#define EXP_SchedTimeslicePlcEnd  CAL_CMEXPAPI( "SchedTimeslicePlcEnd" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedTimeslicePlcEnd
	#define EXT_SchedTimeslicePlcEnd
	#define GET_SchedTimeslicePlcEnd(fl)  CAL_CMGETAPI( "SchedTimeslicePlcEnd" ) 
	#define CAL_SchedTimeslicePlcEnd  SchedTimeslicePlcEnd
	#define CHK_SchedTimeslicePlcEnd  TRUE
	#define EXP_SchedTimeslicePlcEnd  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedTimeslicePlcEnd", (RTS_UINTPTR)SchedTimeslicePlcEnd, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedTimeslicePlcEnd
	#define EXT_CmpScheduleSchedTimeslicePlcEnd
	#define GET_CmpScheduleSchedTimeslicePlcEnd  ERR_OK
	#define CAL_CmpScheduleSchedTimeslicePlcEnd pICmpSchedule->ISchedTimeslicePlcEnd
	#define CHK_CmpScheduleSchedTimeslicePlcEnd (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedTimeslicePlcEnd  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedTimeslicePlcEnd
	#define EXT_SchedTimeslicePlcEnd
	#define GET_SchedTimeslicePlcEnd(fl)  CAL_CMGETAPI( "SchedTimeslicePlcEnd" ) 
	#define CAL_SchedTimeslicePlcEnd pICmpSchedule->ISchedTimeslicePlcEnd
	#define CHK_SchedTimeslicePlcEnd (pICmpSchedule != NULL)
	#define EXP_SchedTimeslicePlcEnd  CAL_CMEXPAPI( "SchedTimeslicePlcEnd" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedTimeslicePlcEnd  PFSCHEDTIMESLICEPLCEND pfSchedTimeslicePlcEnd;
	#define EXT_SchedTimeslicePlcEnd  extern PFSCHEDTIMESLICEPLCEND pfSchedTimeslicePlcEnd;
	#define GET_SchedTimeslicePlcEnd(fl)  s_pfCMGetAPI2( "SchedTimeslicePlcEnd", (RTS_VOID_FCTPTR *)&pfSchedTimeslicePlcEnd, (fl), 0, 0)
	#define CAL_SchedTimeslicePlcEnd  pfSchedTimeslicePlcEnd
	#define CHK_SchedTimeslicePlcEnd  (pfSchedTimeslicePlcEnd != NULL)
	#define EXP_SchedTimeslicePlcEnd  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedTimeslicePlcEnd", (RTS_UINTPTR)SchedTimeslicePlcEnd, 0, 0) 
#endif




/**
 * <description>Returns the processor load, that is consumed by all IEC tasks in %. Can be in the range of 0..100 [%].
 *	This feature must be enabled with the setting "ProcessorLoad.Maximum" > 0.
 *	On multicore systems, the function returned the average load over all cores!
 * </description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Processor load in percent</result>
 */
unsigned long CDECL SchedGetProcessorLoad(RTS_RESULT *pResult);
typedef unsigned long (CDECL * PFSCHEDGETPROCESSORLOAD) (RTS_RESULT *pResult);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDGETPROCESSORLOAD_NOTIMPLEMENTED)
	#define USE_SchedGetProcessorLoad
	#define EXT_SchedGetProcessorLoad
	#define GET_SchedGetProcessorLoad(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedGetProcessorLoad(p0)  (unsigned long)ERR_NOTIMPLEMENTED
	#define CHK_SchedGetProcessorLoad  FALSE
	#define EXP_SchedGetProcessorLoad  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedGetProcessorLoad
	#define EXT_SchedGetProcessorLoad
	#define GET_SchedGetProcessorLoad(fl)  CAL_CMGETAPI( "SchedGetProcessorLoad" ) 
	#define CAL_SchedGetProcessorLoad  SchedGetProcessorLoad
	#define CHK_SchedGetProcessorLoad  TRUE
	#define EXP_SchedGetProcessorLoad  CAL_CMEXPAPI( "SchedGetProcessorLoad" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedGetProcessorLoad
	#define EXT_SchedGetProcessorLoad
	#define GET_SchedGetProcessorLoad(fl)  CAL_CMGETAPI( "SchedGetProcessorLoad" ) 
	#define CAL_SchedGetProcessorLoad  SchedGetProcessorLoad
	#define CHK_SchedGetProcessorLoad  TRUE
	#define EXP_SchedGetProcessorLoad  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetProcessorLoad", (RTS_UINTPTR)SchedGetProcessorLoad, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedGetProcessorLoad
	#define EXT_CmpScheduleSchedGetProcessorLoad
	#define GET_CmpScheduleSchedGetProcessorLoad  ERR_OK
	#define CAL_CmpScheduleSchedGetProcessorLoad pICmpSchedule->ISchedGetProcessorLoad
	#define CHK_CmpScheduleSchedGetProcessorLoad (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedGetProcessorLoad  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedGetProcessorLoad
	#define EXT_SchedGetProcessorLoad
	#define GET_SchedGetProcessorLoad(fl)  CAL_CMGETAPI( "SchedGetProcessorLoad" ) 
	#define CAL_SchedGetProcessorLoad pICmpSchedule->ISchedGetProcessorLoad
	#define CHK_SchedGetProcessorLoad (pICmpSchedule != NULL)
	#define EXP_SchedGetProcessorLoad  CAL_CMEXPAPI( "SchedGetProcessorLoad" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedGetProcessorLoad  PFSCHEDGETPROCESSORLOAD pfSchedGetProcessorLoad;
	#define EXT_SchedGetProcessorLoad  extern PFSCHEDGETPROCESSORLOAD pfSchedGetProcessorLoad;
	#define GET_SchedGetProcessorLoad(fl)  s_pfCMGetAPI2( "SchedGetProcessorLoad", (RTS_VOID_FCTPTR *)&pfSchedGetProcessorLoad, (fl), 0, 0)
	#define CAL_SchedGetProcessorLoad  pfSchedGetProcessorLoad
	#define CHK_SchedGetProcessorLoad  (pfSchedGetProcessorLoad != NULL)
	#define EXP_SchedGetProcessorLoad  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetProcessorLoad", (RTS_UINTPTR)SchedGetProcessorLoad, 0, 0) 
#endif




/**
 * <description>Returns the processor load, that is consumed by all IEC tasks in %. Can be in the range of 0..100 [%].
 *	This feature must be enabled with the setting "ProcessorLoad.Maximum" > 0.</description>
 * <param name="uCoreID" type="IN">Identifies a single core. Starting with 0=first core, ...
 *	NOTE:
 *	If uCoreID=RTS_UI32_MAX, average plc load over all cores in percent is returned (see SchedGetProcessorLoad())!
 * </param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Processor load in percent</result>
 */
RTS_UI32 CDECL SchedGetProcessorLoadOnCore(RTS_UI32 uCoreID, RTS_RESULT *pResult);
typedef RTS_UI32 (CDECL * PFSCHEDGETPROCESSORLOADONCORE) (RTS_UI32 uCoreID, RTS_RESULT *pResult);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDGETPROCESSORLOADONCORE_NOTIMPLEMENTED)
	#define USE_SchedGetProcessorLoadOnCore
	#define EXT_SchedGetProcessorLoadOnCore
	#define GET_SchedGetProcessorLoadOnCore(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedGetProcessorLoadOnCore(p0,p1)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_SchedGetProcessorLoadOnCore  FALSE
	#define EXP_SchedGetProcessorLoadOnCore  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedGetProcessorLoadOnCore
	#define EXT_SchedGetProcessorLoadOnCore
	#define GET_SchedGetProcessorLoadOnCore(fl)  CAL_CMGETAPI( "SchedGetProcessorLoadOnCore" ) 
	#define CAL_SchedGetProcessorLoadOnCore  SchedGetProcessorLoadOnCore
	#define CHK_SchedGetProcessorLoadOnCore  TRUE
	#define EXP_SchedGetProcessorLoadOnCore  CAL_CMEXPAPI( "SchedGetProcessorLoadOnCore" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedGetProcessorLoadOnCore
	#define EXT_SchedGetProcessorLoadOnCore
	#define GET_SchedGetProcessorLoadOnCore(fl)  CAL_CMGETAPI( "SchedGetProcessorLoadOnCore" ) 
	#define CAL_SchedGetProcessorLoadOnCore  SchedGetProcessorLoadOnCore
	#define CHK_SchedGetProcessorLoadOnCore  TRUE
	#define EXP_SchedGetProcessorLoadOnCore  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetProcessorLoadOnCore", (RTS_UINTPTR)SchedGetProcessorLoadOnCore, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedGetProcessorLoadOnCore
	#define EXT_CmpScheduleSchedGetProcessorLoadOnCore
	#define GET_CmpScheduleSchedGetProcessorLoadOnCore  ERR_OK
	#define CAL_CmpScheduleSchedGetProcessorLoadOnCore pICmpSchedule->ISchedGetProcessorLoadOnCore
	#define CHK_CmpScheduleSchedGetProcessorLoadOnCore (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedGetProcessorLoadOnCore  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedGetProcessorLoadOnCore
	#define EXT_SchedGetProcessorLoadOnCore
	#define GET_SchedGetProcessorLoadOnCore(fl)  CAL_CMGETAPI( "SchedGetProcessorLoadOnCore" ) 
	#define CAL_SchedGetProcessorLoadOnCore pICmpSchedule->ISchedGetProcessorLoadOnCore
	#define CHK_SchedGetProcessorLoadOnCore (pICmpSchedule != NULL)
	#define EXP_SchedGetProcessorLoadOnCore  CAL_CMEXPAPI( "SchedGetProcessorLoadOnCore" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedGetProcessorLoadOnCore  PFSCHEDGETPROCESSORLOADONCORE pfSchedGetProcessorLoadOnCore;
	#define EXT_SchedGetProcessorLoadOnCore  extern PFSCHEDGETPROCESSORLOADONCORE pfSchedGetProcessorLoadOnCore;
	#define GET_SchedGetProcessorLoadOnCore(fl)  s_pfCMGetAPI2( "SchedGetProcessorLoadOnCore", (RTS_VOID_FCTPTR *)&pfSchedGetProcessorLoadOnCore, (fl), 0, 0)
	#define CAL_SchedGetProcessorLoadOnCore  pfSchedGetProcessorLoadOnCore
	#define CHK_SchedGetProcessorLoadOnCore  (pfSchedGetProcessorLoadOnCore != NULL)
	#define EXP_SchedGetProcessorLoadOnCore  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetProcessorLoadOnCore", (RTS_UINTPTR)SchedGetProcessorLoadOnCore, 0, 0) 
#endif




/**
 * <description>
 *	Get the actual interval of a cyclic task. If the specified task is no cyclic task, the function return an error.
 * </description>
 * <param name="hSchedTask" type="IN">Handle to the task</param>
 * <param name="ptInterval" type="OUT">Pointer to the interval</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SchedGetTaskInterval(RTS_HANDLE hSchedTask, RTS_UI32 *pulInterval);
typedef RTS_RESULT (CDECL * PFSCHEDGETTASKINTERVAL) (RTS_HANDLE hSchedTask, RTS_UI32 *pulInterval);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDGETTASKINTERVAL_NOTIMPLEMENTED)
	#define USE_SchedGetTaskInterval
	#define EXT_SchedGetTaskInterval
	#define GET_SchedGetTaskInterval(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedGetTaskInterval(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SchedGetTaskInterval  FALSE
	#define EXP_SchedGetTaskInterval  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedGetTaskInterval
	#define EXT_SchedGetTaskInterval
	#define GET_SchedGetTaskInterval(fl)  CAL_CMGETAPI( "SchedGetTaskInterval" ) 
	#define CAL_SchedGetTaskInterval  SchedGetTaskInterval
	#define CHK_SchedGetTaskInterval  TRUE
	#define EXP_SchedGetTaskInterval  CAL_CMEXPAPI( "SchedGetTaskInterval" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedGetTaskInterval
	#define EXT_SchedGetTaskInterval
	#define GET_SchedGetTaskInterval(fl)  CAL_CMGETAPI( "SchedGetTaskInterval" ) 
	#define CAL_SchedGetTaskInterval  SchedGetTaskInterval
	#define CHK_SchedGetTaskInterval  TRUE
	#define EXP_SchedGetTaskInterval  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetTaskInterval", (RTS_UINTPTR)SchedGetTaskInterval, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedGetTaskInterval
	#define EXT_CmpScheduleSchedGetTaskInterval
	#define GET_CmpScheduleSchedGetTaskInterval  ERR_OK
	#define CAL_CmpScheduleSchedGetTaskInterval pICmpSchedule->ISchedGetTaskInterval
	#define CHK_CmpScheduleSchedGetTaskInterval (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedGetTaskInterval  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedGetTaskInterval
	#define EXT_SchedGetTaskInterval
	#define GET_SchedGetTaskInterval(fl)  CAL_CMGETAPI( "SchedGetTaskInterval" ) 
	#define CAL_SchedGetTaskInterval pICmpSchedule->ISchedGetTaskInterval
	#define CHK_SchedGetTaskInterval (pICmpSchedule != NULL)
	#define EXP_SchedGetTaskInterval  CAL_CMEXPAPI( "SchedGetTaskInterval" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedGetTaskInterval  PFSCHEDGETTASKINTERVAL pfSchedGetTaskInterval;
	#define EXT_SchedGetTaskInterval  extern PFSCHEDGETTASKINTERVAL pfSchedGetTaskInterval;
	#define GET_SchedGetTaskInterval(fl)  s_pfCMGetAPI2( "SchedGetTaskInterval", (RTS_VOID_FCTPTR *)&pfSchedGetTaskInterval, (fl), 0, 0)
	#define CAL_SchedGetTaskInterval  pfSchedGetTaskInterval
	#define CHK_SchedGetTaskInterval  (pfSchedGetTaskInterval != NULL)
	#define EXP_SchedGetTaskInterval  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetTaskInterval", (RTS_UINTPTR)SchedGetTaskInterval, 0, 0) 
#endif




/**
 * <description>
 *	Set the actual interval of a cyclic task. If the specified task is no cyclic task, the function return an error.
 *	This interface can be used to synchronize a task to another task or to events.
 * </description>
 * <param name="hSchedTask" type="IN">Handle to the task</param>
 * <param name="tInterval" type="IN">New interval</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SchedSetTaskInterval(RTS_HANDLE hSchedTask, RTS_UI32 ulInterval);
typedef RTS_RESULT (CDECL * PFSCHEDSETTASKINTERVAL) (RTS_HANDLE hSchedTask, RTS_UI32 ulInterval);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDSETTASKINTERVAL_NOTIMPLEMENTED)
	#define USE_SchedSetTaskInterval
	#define EXT_SchedSetTaskInterval
	#define GET_SchedSetTaskInterval(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedSetTaskInterval(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SchedSetTaskInterval  FALSE
	#define EXP_SchedSetTaskInterval  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedSetTaskInterval
	#define EXT_SchedSetTaskInterval
	#define GET_SchedSetTaskInterval(fl)  CAL_CMGETAPI( "SchedSetTaskInterval" ) 
	#define CAL_SchedSetTaskInterval  SchedSetTaskInterval
	#define CHK_SchedSetTaskInterval  TRUE
	#define EXP_SchedSetTaskInterval  CAL_CMEXPAPI( "SchedSetTaskInterval" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedSetTaskInterval
	#define EXT_SchedSetTaskInterval
	#define GET_SchedSetTaskInterval(fl)  CAL_CMGETAPI( "SchedSetTaskInterval" ) 
	#define CAL_SchedSetTaskInterval  SchedSetTaskInterval
	#define CHK_SchedSetTaskInterval  TRUE
	#define EXP_SchedSetTaskInterval  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedSetTaskInterval", (RTS_UINTPTR)SchedSetTaskInterval, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedSetTaskInterval
	#define EXT_CmpScheduleSchedSetTaskInterval
	#define GET_CmpScheduleSchedSetTaskInterval  ERR_OK
	#define CAL_CmpScheduleSchedSetTaskInterval pICmpSchedule->ISchedSetTaskInterval
	#define CHK_CmpScheduleSchedSetTaskInterval (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedSetTaskInterval  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedSetTaskInterval
	#define EXT_SchedSetTaskInterval
	#define GET_SchedSetTaskInterval(fl)  CAL_CMGETAPI( "SchedSetTaskInterval" ) 
	#define CAL_SchedSetTaskInterval pICmpSchedule->ISchedSetTaskInterval
	#define CHK_SchedSetTaskInterval (pICmpSchedule != NULL)
	#define EXP_SchedSetTaskInterval  CAL_CMEXPAPI( "SchedSetTaskInterval" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedSetTaskInterval  PFSCHEDSETTASKINTERVAL pfSchedSetTaskInterval;
	#define EXT_SchedSetTaskInterval  extern PFSCHEDSETTASKINTERVAL pfSchedSetTaskInterval;
	#define GET_SchedSetTaskInterval(fl)  s_pfCMGetAPI2( "SchedSetTaskInterval", (RTS_VOID_FCTPTR *)&pfSchedSetTaskInterval, (fl), 0, 0)
	#define CAL_SchedSetTaskInterval  pfSchedSetTaskInterval
	#define CHK_SchedSetTaskInterval  (pfSchedSetTaskInterval != NULL)
	#define EXP_SchedSetTaskInterval  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedSetTaskInterval", (RTS_UINTPTR)SchedSetTaskInterval, 0, 0) 
#endif




/**
 * <description>
 *	Function to sleep a specified time interval in microseconds _without_ consuming processor load!
 * </description>
 * <param name="ptSleepUs" type="IN">Time to sleep in microseconds</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SchedWaitSleep(RTS_SYSTIME *ptSleepUs);
typedef RTS_RESULT (CDECL * PFSCHEDWAITSLEEP) (RTS_SYSTIME *ptSleepUs);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDWAITSLEEP_NOTIMPLEMENTED)
	#define USE_SchedWaitSleep
	#define EXT_SchedWaitSleep
	#define GET_SchedWaitSleep(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedWaitSleep(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SchedWaitSleep  FALSE
	#define EXP_SchedWaitSleep  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedWaitSleep
	#define EXT_SchedWaitSleep
	#define GET_SchedWaitSleep(fl)  CAL_CMGETAPI( "SchedWaitSleep" ) 
	#define CAL_SchedWaitSleep  SchedWaitSleep
	#define CHK_SchedWaitSleep  TRUE
	#define EXP_SchedWaitSleep  CAL_CMEXPAPI( "SchedWaitSleep" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedWaitSleep
	#define EXT_SchedWaitSleep
	#define GET_SchedWaitSleep(fl)  CAL_CMGETAPI( "SchedWaitSleep" ) 
	#define CAL_SchedWaitSleep  SchedWaitSleep
	#define CHK_SchedWaitSleep  TRUE
	#define EXP_SchedWaitSleep  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedWaitSleep", (RTS_UINTPTR)SchedWaitSleep, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedWaitSleep
	#define EXT_CmpScheduleSchedWaitSleep
	#define GET_CmpScheduleSchedWaitSleep  ERR_OK
	#define CAL_CmpScheduleSchedWaitSleep pICmpSchedule->ISchedWaitSleep
	#define CHK_CmpScheduleSchedWaitSleep (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedWaitSleep  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedWaitSleep
	#define EXT_SchedWaitSleep
	#define GET_SchedWaitSleep(fl)  CAL_CMGETAPI( "SchedWaitSleep" ) 
	#define CAL_SchedWaitSleep pICmpSchedule->ISchedWaitSleep
	#define CHK_SchedWaitSleep (pICmpSchedule != NULL)
	#define EXP_SchedWaitSleep  CAL_CMEXPAPI( "SchedWaitSleep" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedWaitSleep  PFSCHEDWAITSLEEP pfSchedWaitSleep;
	#define EXT_SchedWaitSleep  extern PFSCHEDWAITSLEEP pfSchedWaitSleep;
	#define GET_SchedWaitSleep(fl)  s_pfCMGetAPI2( "SchedWaitSleep", (RTS_VOID_FCTPTR *)&pfSchedWaitSleep, (fl), 0, 0)
	#define CAL_SchedWaitSleep  pfSchedWaitSleep
	#define CHK_SchedWaitSleep  (pfSchedWaitSleep != NULL)
	#define EXP_SchedWaitSleep  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedWaitSleep", (RTS_UINTPTR)SchedWaitSleep, 0, 0) 
#endif




/**
 * <description>
 *	Function to wait busy during a specified time interval. This consumes maximum of processor load!
 * </description>
 * <param name="ptSleepUs" type="IN">Time to sleep in microseconds</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SchedWaitBusy(RTS_SYSTIME *ptSleepUs);
typedef RTS_RESULT (CDECL * PFSCHEDWAITBUSY) (RTS_SYSTIME *ptSleepUs);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDWAITBUSY_NOTIMPLEMENTED)
	#define USE_SchedWaitBusy
	#define EXT_SchedWaitBusy
	#define GET_SchedWaitBusy(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedWaitBusy(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SchedWaitBusy  FALSE
	#define EXP_SchedWaitBusy  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedWaitBusy
	#define EXT_SchedWaitBusy
	#define GET_SchedWaitBusy(fl)  CAL_CMGETAPI( "SchedWaitBusy" ) 
	#define CAL_SchedWaitBusy  SchedWaitBusy
	#define CHK_SchedWaitBusy  TRUE
	#define EXP_SchedWaitBusy  CAL_CMEXPAPI( "SchedWaitBusy" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedWaitBusy
	#define EXT_SchedWaitBusy
	#define GET_SchedWaitBusy(fl)  CAL_CMGETAPI( "SchedWaitBusy" ) 
	#define CAL_SchedWaitBusy  SchedWaitBusy
	#define CHK_SchedWaitBusy  TRUE
	#define EXP_SchedWaitBusy  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedWaitBusy", (RTS_UINTPTR)SchedWaitBusy, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedWaitBusy
	#define EXT_CmpScheduleSchedWaitBusy
	#define GET_CmpScheduleSchedWaitBusy  ERR_OK
	#define CAL_CmpScheduleSchedWaitBusy pICmpSchedule->ISchedWaitBusy
	#define CHK_CmpScheduleSchedWaitBusy (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedWaitBusy  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedWaitBusy
	#define EXT_SchedWaitBusy
	#define GET_SchedWaitBusy(fl)  CAL_CMGETAPI( "SchedWaitBusy" ) 
	#define CAL_SchedWaitBusy pICmpSchedule->ISchedWaitBusy
	#define CHK_SchedWaitBusy (pICmpSchedule != NULL)
	#define EXP_SchedWaitBusy  CAL_CMEXPAPI( "SchedWaitBusy" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedWaitBusy  PFSCHEDWAITBUSY pfSchedWaitBusy;
	#define EXT_SchedWaitBusy  extern PFSCHEDWAITBUSY pfSchedWaitBusy;
	#define GET_SchedWaitBusy(fl)  s_pfCMGetAPI2( "SchedWaitBusy", (RTS_VOID_FCTPTR *)&pfSchedWaitBusy, (fl), 0, 0)
	#define CAL_SchedWaitBusy  pfSchedWaitBusy
	#define CHK_SchedWaitBusy  (pfSchedWaitBusy != NULL)
	#define EXP_SchedWaitBusy  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedWaitBusy", (RTS_UINTPTR)SchedWaitBusy, 0, 0) 
#endif




/**
 * <description>
 *	Handler is called, if a watchdog exception occurred.
 * </description>
 * <param name="hSchedTask" type="IN">Handle to the task</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SchedWatchdogExceptionHandler(RTS_HANDLE hSchedTask);
typedef RTS_RESULT (CDECL * PFSCHEDWATCHDOGEXCEPTIONHANDLER) (RTS_HANDLE hSchedTask);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDWATCHDOGEXCEPTIONHANDLER_NOTIMPLEMENTED)
	#define USE_SchedWatchdogExceptionHandler
	#define EXT_SchedWatchdogExceptionHandler
	#define GET_SchedWatchdogExceptionHandler(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedWatchdogExceptionHandler(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SchedWatchdogExceptionHandler  FALSE
	#define EXP_SchedWatchdogExceptionHandler  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedWatchdogExceptionHandler
	#define EXT_SchedWatchdogExceptionHandler
	#define GET_SchedWatchdogExceptionHandler(fl)  CAL_CMGETAPI( "SchedWatchdogExceptionHandler" ) 
	#define CAL_SchedWatchdogExceptionHandler  SchedWatchdogExceptionHandler
	#define CHK_SchedWatchdogExceptionHandler  TRUE
	#define EXP_SchedWatchdogExceptionHandler  CAL_CMEXPAPI( "SchedWatchdogExceptionHandler" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedWatchdogExceptionHandler
	#define EXT_SchedWatchdogExceptionHandler
	#define GET_SchedWatchdogExceptionHandler(fl)  CAL_CMGETAPI( "SchedWatchdogExceptionHandler" ) 
	#define CAL_SchedWatchdogExceptionHandler  SchedWatchdogExceptionHandler
	#define CHK_SchedWatchdogExceptionHandler  TRUE
	#define EXP_SchedWatchdogExceptionHandler  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedWatchdogExceptionHandler", (RTS_UINTPTR)SchedWatchdogExceptionHandler, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedWatchdogExceptionHandler
	#define EXT_CmpScheduleSchedWatchdogExceptionHandler
	#define GET_CmpScheduleSchedWatchdogExceptionHandler  ERR_OK
	#define CAL_CmpScheduleSchedWatchdogExceptionHandler pICmpSchedule->ISchedWatchdogExceptionHandler
	#define CHK_CmpScheduleSchedWatchdogExceptionHandler (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedWatchdogExceptionHandler  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedWatchdogExceptionHandler
	#define EXT_SchedWatchdogExceptionHandler
	#define GET_SchedWatchdogExceptionHandler(fl)  CAL_CMGETAPI( "SchedWatchdogExceptionHandler" ) 
	#define CAL_SchedWatchdogExceptionHandler pICmpSchedule->ISchedWatchdogExceptionHandler
	#define CHK_SchedWatchdogExceptionHandler (pICmpSchedule != NULL)
	#define EXP_SchedWatchdogExceptionHandler  CAL_CMEXPAPI( "SchedWatchdogExceptionHandler" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedWatchdogExceptionHandler  PFSCHEDWATCHDOGEXCEPTIONHANDLER pfSchedWatchdogExceptionHandler;
	#define EXT_SchedWatchdogExceptionHandler  extern PFSCHEDWATCHDOGEXCEPTIONHANDLER pfSchedWatchdogExceptionHandler;
	#define GET_SchedWatchdogExceptionHandler(fl)  s_pfCMGetAPI2( "SchedWatchdogExceptionHandler", (RTS_VOID_FCTPTR *)&pfSchedWatchdogExceptionHandler, (fl), 0, 0)
	#define CAL_SchedWatchdogExceptionHandler  pfSchedWatchdogExceptionHandler
	#define CHK_SchedWatchdogExceptionHandler  (pfSchedWatchdogExceptionHandler != NULL)
	#define EXP_SchedWatchdogExceptionHandler  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedWatchdogExceptionHandler", (RTS_UINTPTR)SchedWatchdogExceptionHandler, 0, 0) 
#endif




/**
 * <description>
 *	Get the actual schedule interval in microseconds.
 * </description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Schedule interval in microseconds</result>
 */
int CDECL SchedGetScheduleIntervalUs(RTS_RESULT *pResult);
typedef int (CDECL * PFSCHEDGETSCHEDULEINTERVALUS) (RTS_RESULT *pResult);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDGETSCHEDULEINTERVALUS_NOTIMPLEMENTED)
	#define USE_SchedGetScheduleIntervalUs
	#define EXT_SchedGetScheduleIntervalUs
	#define GET_SchedGetScheduleIntervalUs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedGetScheduleIntervalUs(p0)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SchedGetScheduleIntervalUs  FALSE
	#define EXP_SchedGetScheduleIntervalUs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedGetScheduleIntervalUs
	#define EXT_SchedGetScheduleIntervalUs
	#define GET_SchedGetScheduleIntervalUs(fl)  CAL_CMGETAPI( "SchedGetScheduleIntervalUs" ) 
	#define CAL_SchedGetScheduleIntervalUs  SchedGetScheduleIntervalUs
	#define CHK_SchedGetScheduleIntervalUs  TRUE
	#define EXP_SchedGetScheduleIntervalUs  CAL_CMEXPAPI( "SchedGetScheduleIntervalUs" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedGetScheduleIntervalUs
	#define EXT_SchedGetScheduleIntervalUs
	#define GET_SchedGetScheduleIntervalUs(fl)  CAL_CMGETAPI( "SchedGetScheduleIntervalUs" ) 
	#define CAL_SchedGetScheduleIntervalUs  SchedGetScheduleIntervalUs
	#define CHK_SchedGetScheduleIntervalUs  TRUE
	#define EXP_SchedGetScheduleIntervalUs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetScheduleIntervalUs", (RTS_UINTPTR)SchedGetScheduleIntervalUs, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedGetScheduleIntervalUs
	#define EXT_CmpScheduleSchedGetScheduleIntervalUs
	#define GET_CmpScheduleSchedGetScheduleIntervalUs  ERR_OK
	#define CAL_CmpScheduleSchedGetScheduleIntervalUs pICmpSchedule->ISchedGetScheduleIntervalUs
	#define CHK_CmpScheduleSchedGetScheduleIntervalUs (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedGetScheduleIntervalUs  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedGetScheduleIntervalUs
	#define EXT_SchedGetScheduleIntervalUs
	#define GET_SchedGetScheduleIntervalUs(fl)  CAL_CMGETAPI( "SchedGetScheduleIntervalUs" ) 
	#define CAL_SchedGetScheduleIntervalUs pICmpSchedule->ISchedGetScheduleIntervalUs
	#define CHK_SchedGetScheduleIntervalUs (pICmpSchedule != NULL)
	#define EXP_SchedGetScheduleIntervalUs  CAL_CMEXPAPI( "SchedGetScheduleIntervalUs" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedGetScheduleIntervalUs  PFSCHEDGETSCHEDULEINTERVALUS pfSchedGetScheduleIntervalUs;
	#define EXT_SchedGetScheduleIntervalUs  extern PFSCHEDGETSCHEDULEINTERVALUS pfSchedGetScheduleIntervalUs;
	#define GET_SchedGetScheduleIntervalUs(fl)  s_pfCMGetAPI2( "SchedGetScheduleIntervalUs", (RTS_VOID_FCTPTR *)&pfSchedGetScheduleIntervalUs, (fl), 0, 0)
	#define CAL_SchedGetScheduleIntervalUs  pfSchedGetScheduleIntervalUs
	#define CHK_SchedGetScheduleIntervalUs  (pfSchedGetScheduleIntervalUs != NULL)
	#define EXP_SchedGetScheduleIntervalUs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetScheduleIntervalUs", (RTS_UINTPTR)SchedGetScheduleIntervalUs, 0, 0) 
#endif




/**
 * <description>
 *	Set the actual schedule interval in microseconds.
 *  The actual schedule interval (system base tick) has to be adapted accordingly.
 * </description>
 * <param name="iScheduleIntervalUsNew" type="IN">Schedule interval in microseconds to set</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SchedSetScheduleIntervalUs(int iScheduleIntervalUsNew);
typedef RTS_RESULT (CDECL * PFSCHEDSETSCHEDULEINTERVALUS) (int iScheduleIntervalUsNew);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDSETSCHEDULEINTERVALUS_NOTIMPLEMENTED)
	#define USE_SchedSetScheduleIntervalUs
	#define EXT_SchedSetScheduleIntervalUs
	#define GET_SchedSetScheduleIntervalUs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedSetScheduleIntervalUs(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SchedSetScheduleIntervalUs  FALSE
	#define EXP_SchedSetScheduleIntervalUs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedSetScheduleIntervalUs
	#define EXT_SchedSetScheduleIntervalUs
	#define GET_SchedSetScheduleIntervalUs(fl)  CAL_CMGETAPI( "SchedSetScheduleIntervalUs" ) 
	#define CAL_SchedSetScheduleIntervalUs  SchedSetScheduleIntervalUs
	#define CHK_SchedSetScheduleIntervalUs  TRUE
	#define EXP_SchedSetScheduleIntervalUs  CAL_CMEXPAPI( "SchedSetScheduleIntervalUs" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedSetScheduleIntervalUs
	#define EXT_SchedSetScheduleIntervalUs
	#define GET_SchedSetScheduleIntervalUs(fl)  CAL_CMGETAPI( "SchedSetScheduleIntervalUs" ) 
	#define CAL_SchedSetScheduleIntervalUs  SchedSetScheduleIntervalUs
	#define CHK_SchedSetScheduleIntervalUs  TRUE
	#define EXP_SchedSetScheduleIntervalUs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedSetScheduleIntervalUs", (RTS_UINTPTR)SchedSetScheduleIntervalUs, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedSetScheduleIntervalUs
	#define EXT_CmpScheduleSchedSetScheduleIntervalUs
	#define GET_CmpScheduleSchedSetScheduleIntervalUs  ERR_OK
	#define CAL_CmpScheduleSchedSetScheduleIntervalUs pICmpSchedule->ISchedSetScheduleIntervalUs
	#define CHK_CmpScheduleSchedSetScheduleIntervalUs (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedSetScheduleIntervalUs  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedSetScheduleIntervalUs
	#define EXT_SchedSetScheduleIntervalUs
	#define GET_SchedSetScheduleIntervalUs(fl)  CAL_CMGETAPI( "SchedSetScheduleIntervalUs" ) 
	#define CAL_SchedSetScheduleIntervalUs pICmpSchedule->ISchedSetScheduleIntervalUs
	#define CHK_SchedSetScheduleIntervalUs (pICmpSchedule != NULL)
	#define EXP_SchedSetScheduleIntervalUs  CAL_CMEXPAPI( "SchedSetScheduleIntervalUs" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedSetScheduleIntervalUs  PFSCHEDSETSCHEDULEINTERVALUS pfSchedSetScheduleIntervalUs;
	#define EXT_SchedSetScheduleIntervalUs  extern PFSCHEDSETSCHEDULEINTERVALUS pfSchedSetScheduleIntervalUs;
	#define GET_SchedSetScheduleIntervalUs(fl)  s_pfCMGetAPI2( "SchedSetScheduleIntervalUs", (RTS_VOID_FCTPTR *)&pfSchedSetScheduleIntervalUs, (fl), 0, 0)
	#define CAL_SchedSetScheduleIntervalUs  pfSchedSetScheduleIntervalUs
	#define CHK_SchedSetScheduleIntervalUs  (pfSchedSetScheduleIntervalUs != NULL)
	#define EXP_SchedSetScheduleIntervalUs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedSetScheduleIntervalUs", (RTS_UINTPTR)SchedSetScheduleIntervalUs, 0, 0) 
#endif




/**
 * <description>
 *	Set the actual interval of a cyclic task. If the specified task is no cyclic task, the function returns an error.
 *	This interface can be used to synchronize a task to another task or to events.
 *	NOTE:
 *	The provided handle is a SysTask handle, no schedule handle!
 * </description>
 * <param name="hSysTask" type="IN">Handle to the task provided by SysTask component</param>
 * <param name="ulInterval" type="IN">New interval</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SchedSetTaskIntervalByTaskHandle(RTS_HANDLE hSysTask, RTS_UI32 ulInterval);
typedef RTS_RESULT (CDECL * PFSCHEDSETTASKINTERVALBYTASKHANDLE) (RTS_HANDLE hSysTask, RTS_UI32 ulInterval);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDSETTASKINTERVALBYTASKHANDLE_NOTIMPLEMENTED)
	#define USE_SchedSetTaskIntervalByTaskHandle
	#define EXT_SchedSetTaskIntervalByTaskHandle
	#define GET_SchedSetTaskIntervalByTaskHandle(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedSetTaskIntervalByTaskHandle(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SchedSetTaskIntervalByTaskHandle  FALSE
	#define EXP_SchedSetTaskIntervalByTaskHandle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedSetTaskIntervalByTaskHandle
	#define EXT_SchedSetTaskIntervalByTaskHandle
	#define GET_SchedSetTaskIntervalByTaskHandle(fl)  CAL_CMGETAPI( "SchedSetTaskIntervalByTaskHandle" ) 
	#define CAL_SchedSetTaskIntervalByTaskHandle  SchedSetTaskIntervalByTaskHandle
	#define CHK_SchedSetTaskIntervalByTaskHandle  TRUE
	#define EXP_SchedSetTaskIntervalByTaskHandle  CAL_CMEXPAPI( "SchedSetTaskIntervalByTaskHandle" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedSetTaskIntervalByTaskHandle
	#define EXT_SchedSetTaskIntervalByTaskHandle
	#define GET_SchedSetTaskIntervalByTaskHandle(fl)  CAL_CMGETAPI( "SchedSetTaskIntervalByTaskHandle" ) 
	#define CAL_SchedSetTaskIntervalByTaskHandle  SchedSetTaskIntervalByTaskHandle
	#define CHK_SchedSetTaskIntervalByTaskHandle  TRUE
	#define EXP_SchedSetTaskIntervalByTaskHandle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedSetTaskIntervalByTaskHandle", (RTS_UINTPTR)SchedSetTaskIntervalByTaskHandle, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedSetTaskIntervalByTaskHandle
	#define EXT_CmpScheduleSchedSetTaskIntervalByTaskHandle
	#define GET_CmpScheduleSchedSetTaskIntervalByTaskHandle  ERR_OK
	#define CAL_CmpScheduleSchedSetTaskIntervalByTaskHandle pICmpSchedule->ISchedSetTaskIntervalByTaskHandle
	#define CHK_CmpScheduleSchedSetTaskIntervalByTaskHandle (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedSetTaskIntervalByTaskHandle  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedSetTaskIntervalByTaskHandle
	#define EXT_SchedSetTaskIntervalByTaskHandle
	#define GET_SchedSetTaskIntervalByTaskHandle(fl)  CAL_CMGETAPI( "SchedSetTaskIntervalByTaskHandle" ) 
	#define CAL_SchedSetTaskIntervalByTaskHandle pICmpSchedule->ISchedSetTaskIntervalByTaskHandle
	#define CHK_SchedSetTaskIntervalByTaskHandle (pICmpSchedule != NULL)
	#define EXP_SchedSetTaskIntervalByTaskHandle  CAL_CMEXPAPI( "SchedSetTaskIntervalByTaskHandle" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedSetTaskIntervalByTaskHandle  PFSCHEDSETTASKINTERVALBYTASKHANDLE pfSchedSetTaskIntervalByTaskHandle;
	#define EXT_SchedSetTaskIntervalByTaskHandle  extern PFSCHEDSETTASKINTERVALBYTASKHANDLE pfSchedSetTaskIntervalByTaskHandle;
	#define GET_SchedSetTaskIntervalByTaskHandle(fl)  s_pfCMGetAPI2( "SchedSetTaskIntervalByTaskHandle", (RTS_VOID_FCTPTR *)&pfSchedSetTaskIntervalByTaskHandle, (fl), 0, 0)
	#define CAL_SchedSetTaskIntervalByTaskHandle  pfSchedSetTaskIntervalByTaskHandle
	#define CHK_SchedSetTaskIntervalByTaskHandle  (pfSchedSetTaskIntervalByTaskHandle != NULL)
	#define EXP_SchedSetTaskIntervalByTaskHandle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedSetTaskIntervalByTaskHandle", (RTS_UINTPTR)SchedSetTaskIntervalByTaskHandle, 0, 0) 
#endif




/**
 * <description>
 * <p>Register an external event, which might be used later by
 * event tasks. You should register those events during the system
 * startup, so that the scheduler knows all events when the
 * application is loaded.</p>
 * <p>Valid Hook: CH_INIT2</p>
 * <p>Note: the parameter pszExtEventName needs to be constantly
 * allocated. It might either be a constant string, a global string
 * variable, or a dynamically allocated string. But the memory needs
 * to be valid during the life time of the event handle.</p>
 * </description>
 * <param name="pszExtEventName" type="IN">Name of the event, as it was specified in the device description. This parameter needs to be constantly allocated</param>
 * <param name="pResult" type="INOUT">Error Code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Event was registered successfully</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">There was not enough memory to register the new event handle</errorcode>
 * <result>handle to the event</result>
 */
RTS_HANDLE CDECL SchedRegisterExternalEvent(const char *pszExtEventName, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSCHEDREGISTEREXTERNALEVENT) (const char *pszExtEventName, RTS_RESULT *pResult);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDREGISTEREXTERNALEVENT_NOTIMPLEMENTED)
	#define USE_SchedRegisterExternalEvent
	#define EXT_SchedRegisterExternalEvent
	#define GET_SchedRegisterExternalEvent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedRegisterExternalEvent(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SchedRegisterExternalEvent  FALSE
	#define EXP_SchedRegisterExternalEvent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedRegisterExternalEvent
	#define EXT_SchedRegisterExternalEvent
	#define GET_SchedRegisterExternalEvent(fl)  CAL_CMGETAPI( "SchedRegisterExternalEvent" ) 
	#define CAL_SchedRegisterExternalEvent  SchedRegisterExternalEvent
	#define CHK_SchedRegisterExternalEvent  TRUE
	#define EXP_SchedRegisterExternalEvent  CAL_CMEXPAPI( "SchedRegisterExternalEvent" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedRegisterExternalEvent
	#define EXT_SchedRegisterExternalEvent
	#define GET_SchedRegisterExternalEvent(fl)  CAL_CMGETAPI( "SchedRegisterExternalEvent" ) 
	#define CAL_SchedRegisterExternalEvent  SchedRegisterExternalEvent
	#define CHK_SchedRegisterExternalEvent  TRUE
	#define EXP_SchedRegisterExternalEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedRegisterExternalEvent", (RTS_UINTPTR)SchedRegisterExternalEvent, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedRegisterExternalEvent
	#define EXT_CmpScheduleSchedRegisterExternalEvent
	#define GET_CmpScheduleSchedRegisterExternalEvent  ERR_OK
	#define CAL_CmpScheduleSchedRegisterExternalEvent pICmpSchedule->ISchedRegisterExternalEvent
	#define CHK_CmpScheduleSchedRegisterExternalEvent (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedRegisterExternalEvent  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedRegisterExternalEvent
	#define EXT_SchedRegisterExternalEvent
	#define GET_SchedRegisterExternalEvent(fl)  CAL_CMGETAPI( "SchedRegisterExternalEvent" ) 
	#define CAL_SchedRegisterExternalEvent pICmpSchedule->ISchedRegisterExternalEvent
	#define CHK_SchedRegisterExternalEvent (pICmpSchedule != NULL)
	#define EXP_SchedRegisterExternalEvent  CAL_CMEXPAPI( "SchedRegisterExternalEvent" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedRegisterExternalEvent  PFSCHEDREGISTEREXTERNALEVENT pfSchedRegisterExternalEvent;
	#define EXT_SchedRegisterExternalEvent  extern PFSCHEDREGISTEREXTERNALEVENT pfSchedRegisterExternalEvent;
	#define GET_SchedRegisterExternalEvent(fl)  s_pfCMGetAPI2( "SchedRegisterExternalEvent", (RTS_VOID_FCTPTR *)&pfSchedRegisterExternalEvent, (fl), 0, 0)
	#define CAL_SchedRegisterExternalEvent  pfSchedRegisterExternalEvent
	#define CHK_SchedRegisterExternalEvent  (pfSchedRegisterExternalEvent != NULL)
	#define EXP_SchedRegisterExternalEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedRegisterExternalEvent", (RTS_UINTPTR)SchedRegisterExternalEvent, 0, 0) 
#endif




/**
 * <description>
 * <p>Unregister an external event, which was registered by
 * SchedRegisterExternalEvent() before.</p>
 * <p>This function should be called on system shutdown</p>
 * <p>Valid Hook: CH_EXIT2</p>
 * </description>
 * <param name="hExtEvent" type="IN">Handle to the external event, that should be unregistered.</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Event was deregistered successfully</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">The event handle was not registered before</errorcode>
 * <result>Error code</result>
 */
RTS_RESULT CDECL SchedUnregisterExternalEvent(RTS_HANDLE hExtEvent);
typedef RTS_RESULT (CDECL * PFSCHEDUNREGISTEREXTERNALEVENT) (RTS_HANDLE hExtEvent);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDUNREGISTEREXTERNALEVENT_NOTIMPLEMENTED)
	#define USE_SchedUnregisterExternalEvent
	#define EXT_SchedUnregisterExternalEvent
	#define GET_SchedUnregisterExternalEvent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedUnregisterExternalEvent(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SchedUnregisterExternalEvent  FALSE
	#define EXP_SchedUnregisterExternalEvent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedUnregisterExternalEvent
	#define EXT_SchedUnregisterExternalEvent
	#define GET_SchedUnregisterExternalEvent(fl)  CAL_CMGETAPI( "SchedUnregisterExternalEvent" ) 
	#define CAL_SchedUnregisterExternalEvent  SchedUnregisterExternalEvent
	#define CHK_SchedUnregisterExternalEvent  TRUE
	#define EXP_SchedUnregisterExternalEvent  CAL_CMEXPAPI( "SchedUnregisterExternalEvent" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedUnregisterExternalEvent
	#define EXT_SchedUnregisterExternalEvent
	#define GET_SchedUnregisterExternalEvent(fl)  CAL_CMGETAPI( "SchedUnregisterExternalEvent" ) 
	#define CAL_SchedUnregisterExternalEvent  SchedUnregisterExternalEvent
	#define CHK_SchedUnregisterExternalEvent  TRUE
	#define EXP_SchedUnregisterExternalEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedUnregisterExternalEvent", (RTS_UINTPTR)SchedUnregisterExternalEvent, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedUnregisterExternalEvent
	#define EXT_CmpScheduleSchedUnregisterExternalEvent
	#define GET_CmpScheduleSchedUnregisterExternalEvent  ERR_OK
	#define CAL_CmpScheduleSchedUnregisterExternalEvent pICmpSchedule->ISchedUnregisterExternalEvent
	#define CHK_CmpScheduleSchedUnregisterExternalEvent (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedUnregisterExternalEvent  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedUnregisterExternalEvent
	#define EXT_SchedUnregisterExternalEvent
	#define GET_SchedUnregisterExternalEvent(fl)  CAL_CMGETAPI( "SchedUnregisterExternalEvent" ) 
	#define CAL_SchedUnregisterExternalEvent pICmpSchedule->ISchedUnregisterExternalEvent
	#define CHK_SchedUnregisterExternalEvent (pICmpSchedule != NULL)
	#define EXP_SchedUnregisterExternalEvent  CAL_CMEXPAPI( "SchedUnregisterExternalEvent" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedUnregisterExternalEvent  PFSCHEDUNREGISTEREXTERNALEVENT pfSchedUnregisterExternalEvent;
	#define EXT_SchedUnregisterExternalEvent  extern PFSCHEDUNREGISTEREXTERNALEVENT pfSchedUnregisterExternalEvent;
	#define GET_SchedUnregisterExternalEvent(fl)  s_pfCMGetAPI2( "SchedUnregisterExternalEvent", (RTS_VOID_FCTPTR *)&pfSchedUnregisterExternalEvent, (fl), 0, 0)
	#define CAL_SchedUnregisterExternalEvent  pfSchedUnregisterExternalEvent
	#define CHK_SchedUnregisterExternalEvent  (pfSchedUnregisterExternalEvent != NULL)
	#define EXP_SchedUnregisterExternalEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedUnregisterExternalEvent", (RTS_UINTPTR)SchedUnregisterExternalEvent, 0, 0) 
#endif




/**
 * <description>
 * <p>Execute all tasks, that are registered for the given
 * event. The execution context may vary depending on the
 * scheduler type. It might be executed synchronously in the
 * context of the caller, or a system task (e.g. ontop of an
 * OS) is just signaled to execute the task code.</p>
 * <p>Note, that the result ERR_NO_OBJECT might not be a
 * real error. Depending on the system it might be OK, that
 * no task was registered for this event.</p>
 * </description>
 * <param name="hExtEvent" type="IN">Handle to the external event, which tasks should be signaled</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Event was signaled successfully</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">The event handle was not found</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">There was no task, registered on this event</errorcode>
 * <result>Error Code</result>
 */
RTS_RESULT CDECL SchedPostExternalEvent(RTS_HANDLE hExtEvent);
typedef RTS_RESULT (CDECL * PFSCHEDPOSTEXTERNALEVENT) (RTS_HANDLE hExtEvent);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDPOSTEXTERNALEVENT_NOTIMPLEMENTED)
	#define USE_SchedPostExternalEvent
	#define EXT_SchedPostExternalEvent
	#define GET_SchedPostExternalEvent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedPostExternalEvent(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SchedPostExternalEvent  FALSE
	#define EXP_SchedPostExternalEvent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedPostExternalEvent
	#define EXT_SchedPostExternalEvent
	#define GET_SchedPostExternalEvent(fl)  CAL_CMGETAPI( "SchedPostExternalEvent" ) 
	#define CAL_SchedPostExternalEvent  SchedPostExternalEvent
	#define CHK_SchedPostExternalEvent  TRUE
	#define EXP_SchedPostExternalEvent  CAL_CMEXPAPI( "SchedPostExternalEvent" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedPostExternalEvent
	#define EXT_SchedPostExternalEvent
	#define GET_SchedPostExternalEvent(fl)  CAL_CMGETAPI( "SchedPostExternalEvent" ) 
	#define CAL_SchedPostExternalEvent  SchedPostExternalEvent
	#define CHK_SchedPostExternalEvent  TRUE
	#define EXP_SchedPostExternalEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedPostExternalEvent", (RTS_UINTPTR)SchedPostExternalEvent, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedPostExternalEvent
	#define EXT_CmpScheduleSchedPostExternalEvent
	#define GET_CmpScheduleSchedPostExternalEvent  ERR_OK
	#define CAL_CmpScheduleSchedPostExternalEvent pICmpSchedule->ISchedPostExternalEvent
	#define CHK_CmpScheduleSchedPostExternalEvent (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedPostExternalEvent  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedPostExternalEvent
	#define EXT_SchedPostExternalEvent
	#define GET_SchedPostExternalEvent(fl)  CAL_CMGETAPI( "SchedPostExternalEvent" ) 
	#define CAL_SchedPostExternalEvent pICmpSchedule->ISchedPostExternalEvent
	#define CHK_SchedPostExternalEvent (pICmpSchedule != NULL)
	#define EXP_SchedPostExternalEvent  CAL_CMEXPAPI( "SchedPostExternalEvent" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedPostExternalEvent  PFSCHEDPOSTEXTERNALEVENT pfSchedPostExternalEvent;
	#define EXT_SchedPostExternalEvent  extern PFSCHEDPOSTEXTERNALEVENT pfSchedPostExternalEvent;
	#define GET_SchedPostExternalEvent(fl)  s_pfCMGetAPI2( "SchedPostExternalEvent", (RTS_VOID_FCTPTR *)&pfSchedPostExternalEvent, (fl), 0, 0)
	#define CAL_SchedPostExternalEvent  pfSchedPostExternalEvent
	#define CHK_SchedPostExternalEvent  (pfSchedPostExternalEvent != NULL)
	#define EXP_SchedPostExternalEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedPostExternalEvent", (RTS_UINTPTR)SchedPostExternalEvent, 0, 0) 
#endif




/**
 * <description>
 * Get the task handle of the backend interface
 * </description>
 * <param name="hSchedTask" type="IN">Scheduler task handle</param>
 * <param name="pCmpIdBackend" type="IN">Pointer to the resulting backend componentID</param>
 * <param name="pResult" type="IN">Pointer to the resulting error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Backend task handle was successfully retrieved</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid handle hSchedTask</errorcode>
 * <result>Task handle</result>
 */
RTS_HANDLE CDECL SchedGetTaskHandleBackend(RTS_HANDLE hSchedTask, CMPID *pCmpIdBackend, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSCHEDGETTASKHANDLEBACKEND) (RTS_HANDLE hSchedTask, CMPID *pCmpIdBackend, RTS_RESULT *pResult);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDGETTASKHANDLEBACKEND_NOTIMPLEMENTED)
	#define USE_SchedGetTaskHandleBackend
	#define EXT_SchedGetTaskHandleBackend
	#define GET_SchedGetTaskHandleBackend(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedGetTaskHandleBackend(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SchedGetTaskHandleBackend  FALSE
	#define EXP_SchedGetTaskHandleBackend  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedGetTaskHandleBackend
	#define EXT_SchedGetTaskHandleBackend
	#define GET_SchedGetTaskHandleBackend(fl)  CAL_CMGETAPI( "SchedGetTaskHandleBackend" ) 
	#define CAL_SchedGetTaskHandleBackend  SchedGetTaskHandleBackend
	#define CHK_SchedGetTaskHandleBackend  TRUE
	#define EXP_SchedGetTaskHandleBackend  CAL_CMEXPAPI( "SchedGetTaskHandleBackend" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedGetTaskHandleBackend
	#define EXT_SchedGetTaskHandleBackend
	#define GET_SchedGetTaskHandleBackend(fl)  CAL_CMGETAPI( "SchedGetTaskHandleBackend" ) 
	#define CAL_SchedGetTaskHandleBackend  SchedGetTaskHandleBackend
	#define CHK_SchedGetTaskHandleBackend  TRUE
	#define EXP_SchedGetTaskHandleBackend  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetTaskHandleBackend", (RTS_UINTPTR)SchedGetTaskHandleBackend, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedGetTaskHandleBackend
	#define EXT_CmpScheduleSchedGetTaskHandleBackend
	#define GET_CmpScheduleSchedGetTaskHandleBackend  ERR_OK
	#define CAL_CmpScheduleSchedGetTaskHandleBackend pICmpSchedule->ISchedGetTaskHandleBackend
	#define CHK_CmpScheduleSchedGetTaskHandleBackend (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedGetTaskHandleBackend  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedGetTaskHandleBackend
	#define EXT_SchedGetTaskHandleBackend
	#define GET_SchedGetTaskHandleBackend(fl)  CAL_CMGETAPI( "SchedGetTaskHandleBackend" ) 
	#define CAL_SchedGetTaskHandleBackend pICmpSchedule->ISchedGetTaskHandleBackend
	#define CHK_SchedGetTaskHandleBackend (pICmpSchedule != NULL)
	#define EXP_SchedGetTaskHandleBackend  CAL_CMEXPAPI( "SchedGetTaskHandleBackend" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedGetTaskHandleBackend  PFSCHEDGETTASKHANDLEBACKEND pfSchedGetTaskHandleBackend;
	#define EXT_SchedGetTaskHandleBackend  extern PFSCHEDGETTASKHANDLEBACKEND pfSchedGetTaskHandleBackend;
	#define GET_SchedGetTaskHandleBackend(fl)  s_pfCMGetAPI2( "SchedGetTaskHandleBackend", (RTS_VOID_FCTPTR *)&pfSchedGetTaskHandleBackend, (fl), 0, 0)
	#define CAL_SchedGetTaskHandleBackend  pfSchedGetTaskHandleBackend
	#define CHK_SchedGetTaskHandleBackend  (pfSchedGetTaskHandleBackend != NULL)
	#define EXP_SchedGetTaskHandleBackend  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedGetTaskHandleBackend", (RTS_UINTPTR)SchedGetTaskHandleBackend, 0, 0) 
#endif




/**
 * <description>
 * Suspend the specified task.
 * </description>
 * <param name="hSchedTask" type="IN">Scheduler task handle</param>
 * <result>Error code</result>
 */
RTS_RESULT CDECL SchedTaskSuspend(RTS_HANDLE hSchedTask);
typedef RTS_RESULT (CDECL * PFSCHEDTASKSUSPEND) (RTS_HANDLE hSchedTask);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDTASKSUSPEND_NOTIMPLEMENTED)
	#define USE_SchedTaskSuspend
	#define EXT_SchedTaskSuspend
	#define GET_SchedTaskSuspend(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedTaskSuspend(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SchedTaskSuspend  FALSE
	#define EXP_SchedTaskSuspend  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedTaskSuspend
	#define EXT_SchedTaskSuspend
	#define GET_SchedTaskSuspend(fl)  CAL_CMGETAPI( "SchedTaskSuspend" ) 
	#define CAL_SchedTaskSuspend  SchedTaskSuspend
	#define CHK_SchedTaskSuspend  TRUE
	#define EXP_SchedTaskSuspend  CAL_CMEXPAPI( "SchedTaskSuspend" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedTaskSuspend
	#define EXT_SchedTaskSuspend
	#define GET_SchedTaskSuspend(fl)  CAL_CMGETAPI( "SchedTaskSuspend" ) 
	#define CAL_SchedTaskSuspend  SchedTaskSuspend
	#define CHK_SchedTaskSuspend  TRUE
	#define EXP_SchedTaskSuspend  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedTaskSuspend", (RTS_UINTPTR)SchedTaskSuspend, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedTaskSuspend
	#define EXT_CmpScheduleSchedTaskSuspend
	#define GET_CmpScheduleSchedTaskSuspend  ERR_OK
	#define CAL_CmpScheduleSchedTaskSuspend pICmpSchedule->ISchedTaskSuspend
	#define CHK_CmpScheduleSchedTaskSuspend (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedTaskSuspend  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedTaskSuspend
	#define EXT_SchedTaskSuspend
	#define GET_SchedTaskSuspend(fl)  CAL_CMGETAPI( "SchedTaskSuspend" ) 
	#define CAL_SchedTaskSuspend pICmpSchedule->ISchedTaskSuspend
	#define CHK_SchedTaskSuspend (pICmpSchedule != NULL)
	#define EXP_SchedTaskSuspend  CAL_CMEXPAPI( "SchedTaskSuspend" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedTaskSuspend  PFSCHEDTASKSUSPEND pfSchedTaskSuspend;
	#define EXT_SchedTaskSuspend  extern PFSCHEDTASKSUSPEND pfSchedTaskSuspend;
	#define GET_SchedTaskSuspend(fl)  s_pfCMGetAPI2( "SchedTaskSuspend", (RTS_VOID_FCTPTR *)&pfSchedTaskSuspend, (fl), 0, 0)
	#define CAL_SchedTaskSuspend  pfSchedTaskSuspend
	#define CHK_SchedTaskSuspend  (pfSchedTaskSuspend != NULL)
	#define EXP_SchedTaskSuspend  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedTaskSuspend", (RTS_UINTPTR)SchedTaskSuspend, 0, 0) 
#endif




/**
 * <description>
 * Resume the specified task.
 * </description>
 * <param name="hSchedTask" type="IN">Scheduler task handle</param>
 * <result>Error code</result>
 */
RTS_RESULT CDECL SchedTaskResume(RTS_HANDLE hSchedTask);
typedef RTS_RESULT (CDECL * PFSCHEDTASKRESUME) (RTS_HANDLE hSchedTask);
#if defined(CMPSCHEDULE_NOTIMPLEMENTED) || defined(SCHEDTASKRESUME_NOTIMPLEMENTED)
	#define USE_SchedTaskResume
	#define EXT_SchedTaskResume
	#define GET_SchedTaskResume(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SchedTaskResume(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SchedTaskResume  FALSE
	#define EXP_SchedTaskResume  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SchedTaskResume
	#define EXT_SchedTaskResume
	#define GET_SchedTaskResume(fl)  CAL_CMGETAPI( "SchedTaskResume" ) 
	#define CAL_SchedTaskResume  SchedTaskResume
	#define CHK_SchedTaskResume  TRUE
	#define EXP_SchedTaskResume  CAL_CMEXPAPI( "SchedTaskResume" ) 
#elif defined(MIXED_LINK) && !defined(CMPSCHEDULE_EXTERNAL)
	#define USE_SchedTaskResume
	#define EXT_SchedTaskResume
	#define GET_SchedTaskResume(fl)  CAL_CMGETAPI( "SchedTaskResume" ) 
	#define CAL_SchedTaskResume  SchedTaskResume
	#define CHK_SchedTaskResume  TRUE
	#define EXP_SchedTaskResume  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedTaskResume", (RTS_UINTPTR)SchedTaskResume, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpScheduleSchedTaskResume
	#define EXT_CmpScheduleSchedTaskResume
	#define GET_CmpScheduleSchedTaskResume  ERR_OK
	#define CAL_CmpScheduleSchedTaskResume pICmpSchedule->ISchedTaskResume
	#define CHK_CmpScheduleSchedTaskResume (pICmpSchedule != NULL)
	#define EXP_CmpScheduleSchedTaskResume  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SchedTaskResume
	#define EXT_SchedTaskResume
	#define GET_SchedTaskResume(fl)  CAL_CMGETAPI( "SchedTaskResume" ) 
	#define CAL_SchedTaskResume pICmpSchedule->ISchedTaskResume
	#define CHK_SchedTaskResume (pICmpSchedule != NULL)
	#define EXP_SchedTaskResume  CAL_CMEXPAPI( "SchedTaskResume" ) 
#else /* DYNAMIC_LINK */
	#define USE_SchedTaskResume  PFSCHEDTASKRESUME pfSchedTaskResume;
	#define EXT_SchedTaskResume  extern PFSCHEDTASKRESUME pfSchedTaskResume;
	#define GET_SchedTaskResume(fl)  s_pfCMGetAPI2( "SchedTaskResume", (RTS_VOID_FCTPTR *)&pfSchedTaskResume, (fl), 0, 0)
	#define CAL_SchedTaskResume  pfSchedTaskResume
	#define CHK_SchedTaskResume  (pfSchedTaskResume != NULL)
	#define EXP_SchedTaskResume  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SchedTaskResume", (RTS_UINTPTR)SchedTaskResume, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSCHEDHASFEATURE ISchedHasFeature;
 	PFSCHEDADDTASK ISchedAddTask;
 	PFSCHEDREMOVETASK ISchedRemoveTask;
 	PFSCHEDREMOVETASK2 ISchedRemoveTask2;
 	PFSCHEDULE ISchedule;
 	PFSCHEDDEBUGENTER ISchedDebugEnter;
 	PFSCHEDDEBUGLEAVE ISchedDebugLeave;
 	PFSCHEDPREPARERESET ISchedPrepareReset;
 	PFSCHEDRESETDONE ISchedResetDone;
 	PFSCHEDSTART ISchedStart;
 	PFSCHEDSTOP ISchedStop;
 	PFSCHEDGETCURRENTTASK ISchedGetCurrentTask;
 	PFSCHEDGETCONTEXT ISchedGetContext;
 	PFSCHEDGETNUMOFTASKS ISchedGetNumOfTasks;
 	PFSCHEDGETTASKDESCBYINDEX ISchedGetTaskDescByIndex;
 	PFSCHEDGETTASKDESCBYHANDLE ISchedGetTaskDescByHandle;
 	PFSCHEDGETTASKHANDLEBYINDEX ISchedGetTaskHandleByIndex;
 	PFSCHEDGETTASKHANDLEBYNAME ISchedGetTaskHandleByName;
 	PFSCHEDGETTASKEVENTBYHANDLE ISchedGetTaskEventByHandle;
 	PFSCHEDTIMESLICEPLCBEGIN ISchedTimeslicePlcBegin;
 	PFSCHEDTIMESLICEPLCEND ISchedTimeslicePlcEnd;
 	PFSCHEDGETPROCESSORLOAD ISchedGetProcessorLoad;
 	PFSCHEDGETPROCESSORLOADONCORE ISchedGetProcessorLoadOnCore;
 	PFSCHEDGETTASKINTERVAL ISchedGetTaskInterval;
 	PFSCHEDSETTASKINTERVAL ISchedSetTaskInterval;
 	PFSCHEDWAITSLEEP ISchedWaitSleep;
 	PFSCHEDWAITBUSY ISchedWaitBusy;
 	PFSCHEDWATCHDOGEXCEPTIONHANDLER ISchedWatchdogExceptionHandler;
 	PFSCHEDGETSCHEDULEINTERVALUS ISchedGetScheduleIntervalUs;
 	PFSCHEDSETSCHEDULEINTERVALUS ISchedSetScheduleIntervalUs;
 	PFSCHEDSETTASKINTERVALBYTASKHANDLE ISchedSetTaskIntervalByTaskHandle;
 	PFSCHEDREGISTEREXTERNALEVENT ISchedRegisterExternalEvent;
 	PFSCHEDUNREGISTEREXTERNALEVENT ISchedUnregisterExternalEvent;
 	PFSCHEDPOSTEXTERNALEVENT ISchedPostExternalEvent;
 	PFSCHEDGETTASKHANDLEBACKEND ISchedGetTaskHandleBackend;
 	PFSCHEDTASKSUSPEND ISchedTaskSuspend;
 	PFSCHEDTASKRESUME ISchedTaskResume;
 } ICmpSchedule_C;

#ifdef CPLUSPLUS
class ICmpSchedule : public IBase
{
	public:
		virtual RTS_RESULT CDECL ISchedHasFeature(unsigned long ulFeatures) =0;
		virtual RTS_HANDLE CDECL ISchedAddTask(Task_Desc *pTask, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISchedRemoveTask(RTS_HANDLE hSchedTask) =0;
		virtual RTS_RESULT CDECL ISchedRemoveTask2(RTS_HANDLE hSchedTask, RTS_UI32 ulTimeoutMs) =0;
		virtual RTS_RESULT CDECL ISchedule(RTS_HANDLE hSchedTask, int iCmd) =0;
		virtual RTS_RESULT CDECL ISchedDebugEnter(RTS_HANDLE hSchedTask) =0;
		virtual RTS_RESULT CDECL ISchedDebugLeave(RTS_HANDLE hSchedTask) =0;
		virtual RTS_RESULT CDECL ISchedPrepareReset(APPLICATION *pApp, int bResetOrigin) =0;
		virtual RTS_RESULT CDECL ISchedResetDone(APPLICATION *pApp, int bResetOrigin) =0;
		virtual RTS_RESULT CDECL ISchedStart(APPLICATION *pApp) =0;
		virtual RTS_RESULT CDECL ISchedStop(APPLICATION *pApp, RTS_HANDLE hTaskToExclude) =0;
		virtual RTS_HANDLE CDECL ISchedGetCurrentTask(Task_Desc **ppTask, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISchedGetContext(RTS_HANDLE hSchedTask, RegContext *pContext) =0;
		virtual int CDECL ISchedGetNumOfTasks(APPLICATION *pApp, RTS_RESULT *pResult) =0;
		virtual Task_Desc * CDECL ISchedGetTaskDescByIndex(APPLICATION *pApp, int iIndex, RTS_RESULT *pResult) =0;
		virtual Task_Desc * CDECL ISchedGetTaskDescByHandle(RTS_HANDLE hSchedTask, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL ISchedGetTaskHandleByIndex(APPLICATION *pApp, int iIndex, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL ISchedGetTaskHandleByName(char *pszTaskName, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL ISchedGetTaskEventByHandle(RTS_HANDLE hSchedTask, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISchedTimeslicePlcBegin(void) =0;
		virtual RTS_RESULT CDECL ISchedTimeslicePlcEnd(void) =0;
		virtual unsigned long CDECL ISchedGetProcessorLoad(RTS_RESULT *pResult) =0;
		virtual RTS_UI32 CDECL ISchedGetProcessorLoadOnCore(RTS_UI32 uCoreID, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISchedGetTaskInterval(RTS_HANDLE hSchedTask, RTS_UI32 *pulInterval) =0;
		virtual RTS_RESULT CDECL ISchedSetTaskInterval(RTS_HANDLE hSchedTask, RTS_UI32 ulInterval) =0;
		virtual RTS_RESULT CDECL ISchedWaitSleep(RTS_SYSTIME *ptSleepUs) =0;
		virtual RTS_RESULT CDECL ISchedWaitBusy(RTS_SYSTIME *ptSleepUs) =0;
		virtual RTS_RESULT CDECL ISchedWatchdogExceptionHandler(RTS_HANDLE hSchedTask) =0;
		virtual int CDECL ISchedGetScheduleIntervalUs(RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISchedSetScheduleIntervalUs(int iScheduleIntervalUsNew) =0;
		virtual RTS_RESULT CDECL ISchedSetTaskIntervalByTaskHandle(RTS_HANDLE hSysTask, RTS_UI32 ulInterval) =0;
		virtual RTS_HANDLE CDECL ISchedRegisterExternalEvent(const char *pszExtEventName, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISchedUnregisterExternalEvent(RTS_HANDLE hExtEvent) =0;
		virtual RTS_RESULT CDECL ISchedPostExternalEvent(RTS_HANDLE hExtEvent) =0;
		virtual RTS_HANDLE CDECL ISchedGetTaskHandleBackend(RTS_HANDLE hSchedTask, CMPID *pCmpIdBackend, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISchedTaskSuspend(RTS_HANDLE hSchedTask) =0;
		virtual RTS_RESULT CDECL ISchedTaskResume(RTS_HANDLE hSchedTask) =0;
};
	#ifndef ITF_CmpSchedule
		#define ITF_CmpSchedule static ICmpSchedule *pICmpSchedule = NULL;
	#endif
	#define EXTITF_CmpSchedule
#else	/*CPLUSPLUS*/
	typedef ICmpSchedule_C		ICmpSchedule;
	#ifndef ITF_CmpSchedule
		#define ITF_CmpSchedule
	#endif
	#define EXTITF_CmpSchedule
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPSCHEDULEITF_H_*/
