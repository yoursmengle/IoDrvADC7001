/**
 * <interfacename>CmpSchedule</interfacename>
 * <description> 
 *	Interface of the scheduler.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpSchedule')

REF_ITF(`CmpIecTaskItf.m4')
REF_ITF(`SysCpuMultiCoreItf.m4')

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

DEF_API(`void',`CDECL',`schedgetcurrenttask',`(schedgetcurrenttask_struct *p)',1,0x4896EDD1,0x03050900)

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

DEF_API(`void',`CDECL',`schedgetnumoftasks',`(schedgetnumoftasks_struct *p)',1,0x8D47FCA0,0x03050900)

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

DEF_API(`void',`CDECL',`schedgetprocessorload',`(schedgetprocessorload_struct *p)',1,0xD458FC16,0x03050900)

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

DEF_API(`void',`CDECL',`schedgettaskeventbyhandle',`(schedgettaskeventbyhandle_struct *p)',1,0xCF74EFE9,0x03050900)

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

DEF_API(`void',`CDECL',`schedgettaskhandlebyindex',`(schedgettaskhandlebyindex_struct *p)',1,0xA90D39FA,0x03050900)

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

DEF_API(`void',`CDECL',`schedgettaskhandlebyname',`(schedgettaskhandlebyname_struct *p)',1,0x0FBFD668,0x03050900)

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

DEF_API(`void',`CDECL',`schedgettaskinterval',`(schedgettaskinterval_struct *p)',1,0x247455BA,0x03050900)

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

DEF_API(`void',`CDECL',`schedpostexternalevent',`(schedpostexternalevent_struct *p)',1,0x8F2A57B0,0x03050900)

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

DEF_API(`void',`CDECL',`schedregisterexternalevent',`(schedregisterexternalevent_struct *p)',1,0xF3A15AA7,0x03050900)

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

DEF_API(`void',`CDECL',`schedsettaskinterval',`(schedsettaskinterval_struct *p)',1,0x4DF2120E,0x03050900)

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

DEF_API(`void',`CDECL',`schedunregisterexternalevent',`(schedunregisterexternalevent_struct *p)',1,0xF74A64AD,0x03050900)

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

DEF_API(`void',`CDECL',`schedwaitbusy',`(schedwaitbusy_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x34BA0AC2),0x03050900)

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

DEF_API(`void',`CDECL',`schedwaitsleep',`(schedwaitsleep_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xAD6B19D4),0x03050900)

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`SchedHasFeature',`(unsigned long ulFeatures)')

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
DEF_ITF_API(`RTS_HANDLE', `CDECL', `SchedAddTask', `(Task_Desc *pTask, RTS_RESULT *pResult)')

/**
 * <description> Removes a task from scheduler </description>
 * <param name="hSchedTask" type="IN">Handle to task</param>
 * <result>ERR_OK</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SchedRemoveTask', `(RTS_HANDLE hSchedTask)')

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `SchedRemoveTask2', `(RTS_HANDLE hSchedTask, RTS_UI32 ulTimeoutMs)')

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `Schedule', `(RTS_HANDLE hSchedTask, int iCmd)')

/**
 * <description> Enter task for debugging </description>
 * <param name="hSchedTask" type="IN">Handle to task</param>
 * <result>ERR_OK</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SchedDebugEnter', `(RTS_HANDLE hSchedTask)')

/**
 * <description> Leave from debugging </description>
 * <param name="hSchedTask" type="IN">Handle to task</param>
 * <result>ERR_OK</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SchedDebugLeave', `(RTS_HANDLE hSchedTask)')

/**
 * <description> Prepare reset, delete all IEC tasks in error state</description>
 * <result>ERR_OK</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SchedPrepareReset', `(APPLICATION *pApp, int bResetOrigin)')

/**
 * <description> Restart all IEC tasks in error state</description>
 * <result>ERR_OK</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SchedResetDone', `(APPLICATION *pApp, int bResetOrigin)')

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `SchedStart', `(APPLICATION *pApp)')

/**
 * <description> Stop scheduling all tasks specified by application </description>
 * <param name="pApp" type="IN">APPLICATION object</param>
 * <param name="hTaskToExclude" type="IN">Handle of task to exclude from scheduling.
 *	hTask=RTS_INVALID_HANDLE, all tasks are disabled</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SchedStop', `(APPLICATION *pApp, RTS_HANDLE hTaskToExclude)')

/**
 * <description>Is called to get the schedule handle of the current running task</description>
 * <param name="ppTask" type="OUT">Task description for the IecTask component. Can be NULL.</param>
 * <param name="pResult" type="OUT">ERR_OK or Error code</param>
 * <result>Handle to the current running task or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`SchedGetCurrentTask',`(Task_Desc **ppTask, RTS_RESULT *pResult)')

/**
 * <description>Get context of the specified task</description>
 * <param name="hSchedTask" type="IN">Scheduler task handle</param>
 * <param name="pContext" type="IN">Pointer to register context</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SchedGetContext',`(RTS_HANDLE hSchedTask, RegContext *pContext)')

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
DEF_ITF_API(`int',`CDECL',`SchedGetNumOfTasks',`(APPLICATION *pApp, RTS_RESULT *pResult)')

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
DEF_ITF_API(`Task_Desc *',`CDECL',`SchedGetTaskDescByIndex',`(APPLICATION *pApp, int iIndex, RTS_RESULT *pResult)')

/**
 * <description>
 *	Function returns the task description of a task specified by handle.
 * </description>
 * <param name="hSchedTask" type="IN">Handle of the task</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Task description</result>
 */
DEF_ITF_API(`Task_Desc *',`CDECL',`SchedGetTaskDescByHandle',`(RTS_HANDLE hSchedTask, RTS_RESULT *pResult)')

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
DEF_ITF_API(`RTS_HANDLE',`CDECL',`SchedGetTaskHandleByIndex',`(APPLICATION *pApp, int iIndex, RTS_RESULT *pResult)')

/**
 * <description>
 *	Function returns the handle to the task specified by name.
 * </description>
 * <param name="pszTaskName" type="IN">Task name</param>
 * <param name="pResult" type="OUT">ERR_OK or Error code</param>
 * <result>Scheduler task handle</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`SchedGetTaskHandleByName',`(char *pszTaskName, RTS_RESULT *pResult)')

/**
 * <description>
 *	Function returns the handle to the task event. With this event a task can be activaed externally,
 *	e.g. for external triggered event tasks. The event can be sent by SysEventSet(EventHandle);
 * </description>
 * <param name="hSchedTask" type="IN">Scheduler task handle</param>
 * <param name="pResult" type="OUT">ERR_OK or Error code</param>
 * <result>Event handle</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`SchedGetTaskEventByHandle',`(RTS_HANDLE hSchedTask, RTS_RESULT *pResult)')

/**
 * <description>Begin of the plc timeslice. Can be called by an external component, if external timselicing
 *	is enabled.
 * </description>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SchedTimeslicePlcBegin',`(void)')

/**
 * <description>End of the plc timeslice. Can be called by an external component, if external timselicing
 *	is enabled.
 * </description>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SchedTimeslicePlcEnd',`(void)')

/**
 * <description>Returns the processor load, that is consumed by all IEC tasks in %. Can be in the range of 0..100 [%].
 *	This feature must be enabled with the setting "ProcessorLoad.Maximum" > 0.
 *	On multicore systems, the function returned the average load over all cores!
 * </description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Processor load in percent</result>
 */
DEF_ITF_API(`unsigned long',`CDECL',`SchedGetProcessorLoad',`(RTS_RESULT *pResult)')

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
DEF_ITF_API(`RTS_UI32',`CDECL',`SchedGetProcessorLoadOnCore',`(RTS_UI32 uCoreID, RTS_RESULT *pResult)')

/**
 * <description>
 *	Get the actual interval of a cyclic task. If the specified task is no cyclic task, the function return an error.
 * </description>
 * <param name="hSchedTask" type="IN">Handle to the task</param>
 * <param name="ptInterval" type="OUT">Pointer to the interval</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SchedGetTaskInterval',`(RTS_HANDLE hSchedTask, RTS_UI32 *pulInterval)')

/**
 * <description>
 *	Set the actual interval of a cyclic task. If the specified task is no cyclic task, the function return an error.
 *	This interface can be used to synchronize a task to another task or to events.
 * </description>
 * <param name="hSchedTask" type="IN">Handle to the task</param>
 * <param name="tInterval" type="IN">New interval</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SchedSetTaskInterval',`(RTS_HANDLE hSchedTask, RTS_UI32 ulInterval)')

/**
 * <description>
 *	Function to sleep a specified time interval in microseconds _without_ consuming processor load!
 * </description>
 * <param name="ptSleepUs" type="IN">Time to sleep in microseconds</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SchedWaitSleep',`(RTS_SYSTIME *ptSleepUs)')

/**
 * <description>
 *	Function to wait busy during a specified time interval. This consumes maximum of processor load!
 * </description>
 * <param name="ptSleepUs" type="IN">Time to sleep in microseconds</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SchedWaitBusy',`(RTS_SYSTIME *ptSleepUs)')

/**
 * <description>
 *	Handler is called, if a watchdog exception occurred.
 * </description>
 * <param name="hSchedTask" type="IN">Handle to the task</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SchedWatchdogExceptionHandler',`(RTS_HANDLE hSchedTask)')

/**
 * <description>
 *	Get the actual schedule interval in microseconds.
 * </description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Schedule interval in microseconds</result>
 */
DEF_ITF_API(`int',`CDECL',`SchedGetScheduleIntervalUs',`(RTS_RESULT *pResult)')

/**
 * <description>
 *	Set the actual schedule interval in microseconds.
 *  The actual schedule interval (system base tick) has to be adapted accordingly.
 * </description>
 * <param name="iScheduleIntervalUsNew" type="IN">Schedule interval in microseconds to set</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SchedSetScheduleIntervalUs',`(int iScheduleIntervalUsNew)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`SchedSetTaskIntervalByTaskHandle',`(RTS_HANDLE hSysTask, RTS_UI32 ulInterval)')

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
DEF_ITF_API(`RTS_HANDLE',`CDECL',`SchedRegisterExternalEvent',`(const char *pszExtEventName, RTS_RESULT *pResult)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`SchedUnregisterExternalEvent',`(RTS_HANDLE hExtEvent)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`SchedPostExternalEvent',`(RTS_HANDLE hExtEvent)')

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
DEF_ITF_API(`RTS_HANDLE',`CDECL',`SchedGetTaskHandleBackend',`(RTS_HANDLE hSchedTask, CMPID *pCmpIdBackend, RTS_RESULT *pResult)')

/**
 * <description>
 * Suspend the specified task.
 * </description>
 * <param name="hSchedTask" type="IN">Scheduler task handle</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SchedTaskSuspend', `(RTS_HANDLE hSchedTask)')

/**
 * <description>
 * Resume the specified task.
 * </description>
 * <param name="hSchedTask" type="IN">Scheduler task handle</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SchedTaskResume', `(RTS_HANDLE hSchedTask)')

#ifdef __cplusplus
}
#endif
