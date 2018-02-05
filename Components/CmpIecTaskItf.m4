/**
 * <interfacename>CmpIecTask</interfacename>
 * <description> 
 * <p>The component CmpIecTask provides an interface to create an handle all
 * task of one or more IEC applications.</p>
 * <p>The following drawing describes the dependencies between the structures
 * of this and other components in this context:</p>
 * <pre>
 * +-----------+ 1   1 +-----------+ 1   n +---------+
 * | Task_Desc | ----- | Task_Info | ----- | SlotPOU |
 * +-----------+       +-----------+       +---------+
 *      | n   | 1
 *      |     '--------------.
 *      | 1                  | 1
 * +-------------+     +-----------+
 * | Application |     | SchedTask |
 * +-------------+     +-----------+
 * </pre>
 * <p>Depending on the Scheduler, the task might furthermore be mapped to
 * a hardware ressource or another operating system object.</p>
 * <p>CmpSchedule (Multitasking):</p>
 * <pre>
 * +-----------+ 1   1 +---------------+ 1   1 +----------------+
 * | SchedTask | ----- | SYS_TASK_INFO | ----- | OS Task Handle |
 * +-----------+       +---------------+       +----------------+
 * </pre>
 * <p>CmpScheduleTimer:</p>
 * <pre>
 * +-----------+ 1   1 +----------------+ 1   1 +-----------------+
 * | SchedTask | ----- | SYS_TIMER_INFO | ----- | HW Timer Handle |
 * +-----------+       +----------------+       +-----------------+
 * </pre>
 * <p>CmpScheduleEmbedded:</p>
 * <pre>
 * +-----------+
 * | SchedTask |
 * +-----------+
 * </pre>
 * <p>The Task_Info structure is created and allocated in the IEC data area of
 * the application, while everything else is allocated in the runtime.</p>
 * <p>Beside the handling of tasks, this component manages also the slots for
 * the tasks, that might be registered by C or IEC code. Those slots are stored
 * within a memory pool, from which they are called at some specific points
 * before and after the IEC task cycle code.</p>
 * <p>For SIL2 certified systems, those slots are denied, because they 
 * potentially cause a call to an unsafe context from the safe context of
 * the IEC task. So we allow those calls only in debug mode.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpIecTask')

REF_ITF(`CmpAppItf.m4')
REF_ITF(`CmpMemPoolItf.m4')
REF_ITF(`SysTimeItf.m4')


/**
 * <category>Compiler switch</category>
 * <description>
 *	Compiler switches to enable/disable single features in the component.
 * </description>
 * <element name="RTS_STRUCTURED_EXCEPTION_HANDLING" type="IN">To enable the structured exception handling</element>
 * <element name="RTS_IECTASK_STRUCTURED_EXCEPTION_HANDLING" type="IN">To enable structured exception handling for all IecTasks.
 *		If RTS_STRUCTURED_EXCEPTION_HANDLING is enable and RTS_IECTASK_STRUCTURED_EXCEPTION_HANDLING is disabled, the structured exception handling
 *		out of the IEC program can be used via the SysExcept.library (unusual used feature).
 * </element>
 * <element name="RTS_IECTASK_ENABLE_TASK_TRACE" type="IN">Enable IEC task trace feature. This feature creates a CODESYS system trace with all IEC-tasks to trace the timing.
 *	NOTES:
 *		1. To really activate the task trace, you have to set the setting "EnableTaskTrace=1" in the configuration!
 *		2. CmpSchedule must be built with the same compiler switch to activate additional tracing of the SchedulerTick and optional SchedulerTimeslicing!
 * </element>
 */

#if defined(CMPTRACEMGR_NOTIMPLEMENTED)
	#undef RTS_IECTASK_ENABLE_TASK_TRACE
#elif !defined(SYSCPUMULTICORE_NOTIMPLEMENTED) && !defined(RTS_IECTASK_ENABLE_TASK_TRACE)
	#define RTS_IECTASK_ENABLE_TASK_TRACE
#endif

#if !defined(SYSCPUMULTICORE_NOTIMPLEMENTED)
	#define IECTASK_USE_ATOMIC_BITACCESS
#endif


typedef struct
{
    RTS_IEC_DINT slotLower;
    RTS_IEC_DINT slotUpper;
    RTS_IEC_STRING szTaskName[50];
    RTS_IEC_STRING szApplicationName[50];
}sys_rts_cycle_struct;

struct tagTask_Desc;
struct tagTask_Info;

typedef struct
{
    RTS_IEC_DINT slotLower;
    RTS_IEC_DINT slotUpper;
    RTS_IEC_HANDLE hTask;
}sys_rts_cycle_2_struct;


#ifndef NUM_OF_STATIC_IEC_TASKS
	#define NUM_OF_STATIC_IEC_TASKS			5
#endif
#ifndef NUM_OF_STATIC_IEC_EVENTS
	#define NUM_OF_STATIC_IEC_EVENTS		1
#endif
#ifndef MAX_IEC_TASKS
	#define MAX_IEC_TASKS					(-1)
#endif

#ifndef NUM_OF_STATIC_IEC_SLOTS
	#define NUM_OF_STATIC_IEC_SLOTS			10
#endif
#ifndef MAX_IEC_SLOTS
	#define MAX_IEC_SLOTS					(-1)
#endif

#define IECTASK_TASK_INFO_VERSION			4
#define IECTASK_TASK_INFO_GROUPS_VERSION    4
#define IECTASK_TASK_MAX_PRIO				255


/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Default timeout to wait for a task until stop. If a task is not ending execution in this timeout, the
 *	task will be suspended and marked with exception.
 *	This timeout is the maximum reaction time on an application stop to set the machine in a safe state!
 *	The value is in milliseconds.
 * </description>
 */
#define IECTASKKEY_INT_WAIT_FOR_STOP_TIMEOUT				"WaitForStopTimeoutMs"
#ifndef IECTASKVALUE_INT_WAIT_FOR_STOP_TIMEOUT_DEFAULT
	#define IECTASKVALUE_INT_WAIT_FOR_STOP_TIMEOUT_DEFAULT	INT32_C(10000)
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Default timeout to wait for a task until stop, after the safe state is reached! If a task is not ending execution in this timeout, the
 *	task will be suspended and marked with exception.
  *	The value is in milliseconds.
 * </description>
 */
#define IECTASKKEY_INT_WAIT_FOR_STOP_TIMEOUT_2				"WaitForStop.TimeoutMs_2"
#ifndef IECTASKVALUE_INT_WAIT_FOR_STOP_TIMEOUT_2_DEFAULT
	#define IECTASKVALUE_INT_WAIT_FOR_STOP_TIMEOUT_2_DEFAULT	INT32_C(25000)
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * Setting to disable the following feature for the RUN/STOP transition of an application.
 *
 * This feature splits the RUN/STOP transition into 2 phases:
 *
 * - PHASE 1:
 *   This is the phase at the RUN/STOP transition until the safe state of the application/machine will be reached.
 *	 In this phase, we wait only for IEC tasks wich use mapped outputs!
 *	 
 * - PHASE 2:
 *   This is the phase at the RUN/STOP transition after the safe state of the application/machine has been reached.
 *	 In this phase, we wait only for IEC tasks, wich don't use mapped outputs!
 *	 For this phase, there is a new setting for the timeout:
 *	    [CmpIecTask]
 *	    WaitForStop.TimeoutMs_2=25000
 *  
 * Reason for this feature:
 * - This is because typically non IO tasks (AlarmTasks, TrendTasks, etc.) need a much longer cycle time at the RUN/STOP transition than the IO tasks.
 *   And so sometimes a watchdog error occurres at this non IO tasks during normal RUN/STOP transition.
 *  
 * NOTES:
 * - To disable this feature, you can use the following new setting in the cfg-file:
 *     [CmpIecTask]
 *     WaitForStop.SkipTasksWithoutOutputs=0
 * - If your plc does not use the standard CODESYS IO-configuration/IO-mapping, you have to switch off this feature!
 *
 * </description>
 */
#define IECTASKKEY_INT_WAIT_FOR_STOP_SKIPTASKSWITHOUTOUTPUTS		"WaitForStop.SkipTasksWithoutOutputs"
#ifndef IECTASKVALUE_INT_WAIT_FOR_STOP_SKIPTASKSWITHOUTOUTPUTS_DEFAULT
	#define IECTASKVALUE_INT_WAIT_FOR_STOP_SKIPTASKSWITHOUTOUTPUTS_DEFAULT	INT32_C(1)
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Flag for using simple cycle mode. To use this feature, the setting "simple_cycle" must be activated in the corresponding devdesc too!
 * </description>
 */
#define IECTASKKEY_INT_SIMPLE_CYCLE							"Simple_Cycle"
#ifndef IECTASKVALUE_INT_SIMPLE_CYCLE_DEFAULT
	#define IECTASKVALUE_INT_SIMPLE_CYCLE_DEFAULT			0
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to activate the task trace.
 * </description>
 */
#define IECTASKKEY_INT_ENABLE_TASK_TRACE					"EnableTaskTrace"
#ifndef IECTASKVALUE_INT_ENABLE_TASK_TRACE_DEFAULT
	#define IECTASKVALUE_INT_ENABLE_TASK_TRACE_DEFAULT		0
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 *	Name of the task, that controls the target visualization.
 *	NOTE:
 *	For this task, the standard exception handling is skipped, if RTS_STRUCTURED_EXCEPTION_HANDLING is defined additionally! So the application is not forced in stop.
 *	Only the visu task is set in exception state and is never scheduled! All other plc tasks are executed unchanged.
 * </description>
 */
#define IECTASKKEY_STRING_VISU_TASK							"VisuTask"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting enables the feature to fire a watchdog during an IO-update in an IEC task!
 *	Can be disabled if this causes problems in IEC applications and so the behaviour is similar to the runtime system before v3.5.12.0.
 * </description>
 */
#define IECTASKKEY_INT_ENABLE_WATCHDOG_DURING_IOUPDATE		"EnableWatchdogDuringIOUpdate"
#ifndef IECTASKVALUE_INT_ENABLE_WATCHDOG_DURING_IOUPDATE
	#define IECTASKVALUE_INT_ENABLE_WATCHDOG_DURING_IOUPDATE		1
#endif

/**
 * <category>Event parameter</category>
 * <element name="pTaskDesc" type="IN">Pointer to task description</element>
 */
typedef struct
{
	struct tagTask_Desc *pTaskDesc;
} EVTPARAM_CmpIecTask;
#define EVTPARAMID_CmpIecTask		0x0001
#define EVTVERSION_CmpIecTask		0x0001

/**
 * <category>Events</category>
 * <description>Event is sent after reading inputs</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpIecTask</param>
 */
#define EVT_AfterReadingInputs			MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Events</category>
 * <description>Event is sent before writing outputs</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpIecTask</param>
 */
#define EVT_BeforeWritingOutputs		MAKE_EVENTID(EVTCLASS_INFO, 2)

/**
 * <category>Events</category>
 * <description>Event is sent before reading inputs</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpIecTask</param>
 */
#define EVT_BeforeReadingInputs			MAKE_EVENTID(EVTCLASS_INFO, 3)

/**
 * <category>Events</category>
 * <description>Event is sent after writing outputs</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpIecTask</param>
 */
#define EVT_AfterWritingOutputs			MAKE_EVENTID(EVTCLASS_INFO, 4)

/**
 * <category>Events</category>
 * <description>Event is sent at reload of an IOEC task right after the task is deleted</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpIecTask</param>
 */
#define EVT_IecTask_ReloadInit			MAKE_EVENTID(EVTCLASS_INFO, 5)

/**
 * <category>Events</category>
 * <description>Event is sent, after an IEC-task was created at application download</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpIecTask</param>
 */
#define EVT_IecTaskCreateDone			MAKE_EVENTID(EVTCLASS_INFO, 6)

/**
 * <category>Events</category>
 * <description>Event is sent, before an IEC-task will be deleted (e.g. delete of the application)</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpIecTask</param>
 */
#define EVT_IecTaskPrepareDelete		MAKE_EVENTID(EVTCLASS_INFO, 7)

/**
 * <category>Events</category>
 * <description>Event is sent cyclically in the debug loop, if the IEC task is halted on a breakpoint</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpIecTask</param>
 */
#define EVT_IecTaskDebugLoop			MAKE_EVENTID(EVTCLASS_INFO, 8)


/**
 * <category>OperationID</category>
 * <description>Operation ID for the supervision of the RUN-STOP transition of an application</description>
 * <param name="RTS_OPID_Application_RunStop" type="IN">The OperationID is the ID of the application (see APPLICATION.iId for details)</param>
 * <param name="RTS_OPID_Application_RunStop_Description" type="IN"></param>
 */
#define RTS_OPID_IecTask_WatchdogInIO				1
#define RTS_OPID_IecTask_WatchdogInIO_Description	"Supervision of a watchdog error during IO-update (IEC task must leave IO update)"


/**
 * <category>Stop reason option</category>
 * <description>Option that can be specified for IecTasksWaitForStop() in stop reason</description>
 * <element name="IEC_TASK_STOPREASON_OPTION_PREPARE_SAFE_STATE" type="IN">Stop all IEC tasks _before_ setting the outputs to a safe state</element>
 * <element name="IEC_TASK_STOPREASON_OPTION_DONE_SAFE_STATE" type="IN">Stop all IEC tasks _after_ setting the outputs to a safe state. Here we can wait a longer period!</element>
 */
#define IEC_TASK_STOPREASON_OPTION_PREPARE_SAFE_STATE 			0x00000000
#define IEC_TASK_STOPREASON_OPTION_DONE_SAFE_STATE	 			0x00010000


/**
 * <category>IEC task types</category>
 * <description></description>
 */
#define TaskCyclic			0x0000
#define TaskEvent			0x0001
#define TaskExternal		0x0002
#define TaskFreewheeling	0x0003
#define TaskLastIndex		0x0004


/**
 * <category>Task status definitions</category>
 * <description></description>
 */
#define TS_WATCHDOG_ENABLE		0x0040
#define TS_DISABLE_TASK_TIME	0x0080
#define TS_ACTIVATED			0x0100
#define TS_TOACTIVATE			0x0200
#define TS_STOP					0x0400
#define TS_HALT_ON_BP			0x0800
#define TS_SINGLE_CYCLE			0x1000
#define TS_WATCHDOG_ENABLE2		0x2000

/**
 * <category>Task status bits</category>
 * <description></description>
 */
#define TF_WATCHDOG_ENABLE		6
#define TF_DISABLE_TASK_TIME	7
#define TF_ACTIVATED			8
#define TF_TOACTIVATE			9
#define TF_STOP					10
#define TF_HALT_ON_BP			11
#define TF_SINGLE_CYCLE			12
#define TF_WATCHDOG_ENABLE2		13


#define IsWatchdogEnabled(pTask)			((pTask->iState & TS_WATCHDOG_ENABLE) && (pTask->iState & TS_WATCHDOG_ENABLE2))
#define IsTaskTimeEnabled(pTask)			((pTask->iState & TS_DISABLE_TASK_TIME) == 0)
#define IsActivated(pTask)					(pTask->iState & TS_ACTIVATED)
#define ToActivate(pTask)					(pTask->iState & TS_TOACTIVATE)
#define IsStopped(pTask)					(pTask->iState & TS_STOP)
#define IsHaltOnBreakpoint(pTask)			(pTask->iState & TS_HALT_ON_BP)
#define IsSingleCycle(pTask)				(pTask->iState & TS_SINGLE_CYCLE)

#if defined(SYSCPUHANDLING_NOTIMPLEMENTED) || defined(SYSCPUTESTANDSETBIT_NOTIMPLEMENTED) || !defined(IECTASK_USE_ATOMIC_BITACCESS)
	#define SetWatchdogEnabled(pTask)		(pTask->iState |= TS_WATCHDOG_ENABLE)
	#define SetWatchdogDisabled(pTask)		(pTask->iState &= ~TS_WATCHDOG_ENABLE)
	#define SetWatchdogEnabled2(pTask)		(pTask->iState |= TS_WATCHDOG_ENABLE2)
	#define SetWatchdogDisabled2(pTask)		(pTask->iState &= ~TS_WATCHDOG_ENABLE2)

	#define SetTaskTimeDisabled(pTask)		(pTask->iState |= TS_DISABLE_TASK_TIME)
	#define SetTaskTimeEnabled(pTask)		(pTask->iState &= ~TS_DISABLE_TASK_TIME)

	#define SetActivated(pTask)				(pTask->iState |= TS_ACTIVATED)
	#define ResetActivated(pTask)			(pTask->iState &= ~TS_ACTIVATED)

	#define SetToActivate(pTask)			(pTask->iState |= TS_TOACTIVATE)
	#define ResetToActivate(pTask)			(pTask->iState &= ~TS_TOACTIVATE)

	#define SetStopped(pTask)				(pTask->iState |= TS_STOP)
	#define SetRunning(pTask)				(pTask->iState &= ~TS_STOP)

	#define SetHaltOnBreakpoint(pTask)		(pTask->iState |= TS_HALT_ON_BP)
	#define ResetHaltOnBreakpoint(pTask)	(pTask->iState &= ~TS_HALT_ON_BP)

	#define SetSingleCycle(pTask)			(pTask->iState |= TS_SINGLE_CYCLE)
	#define ResetSingleCycle(pTask)			(pTask->iState &= ~TS_SINGLE_CYCLE)
#else
	#define SetWatchdogEnabled(pTask)		CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_WATCHDOG_ENABLE, 1)
	#define SetWatchdogDisabled(pTask)		CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_WATCHDOG_ENABLE, 0)
	#define SetWatchdogEnabled2(pTask)		CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_WATCHDOG_ENABLE2, 1)
	#define SetWatchdogDisabled2(pTask)		CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_WATCHDOG_ENABLE2, 0)

	#define SetTaskTimeDisabled(pTask)		CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_DISABLE_TASK_TIME, 1)
	#define SetTaskTimeEnabled(pTask)		CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_DISABLE_TASK_TIME, 0)

	#define SetActivated(pTask)				CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_ACTIVATED, 1)
	#define ResetActivated(pTask)			CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_ACTIVATED, 0)

	#define SetToActivate(pTask)			CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_TOACTIVATE, 1)
	#define ResetToActivate(pTask)			CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_TOACTIVATE, 0)

	#define SetStopped(pTask)				CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_STOP, 1)
	#define SetRunning(pTask)				CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_STOP, 0)

	#define SetHaltOnBreakpoint(pTask)		CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_HALT_ON_BP, 1)
	#define ResetHaltOnBreakpoint(pTask)	CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_HALT_ON_BP, 0)

	#define SetSingleCycle(pTask)			CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_SINGLE_CYCLE, 1)
	#define ResetSingleCycle(pTask)			CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_SINGLE_CYCLE, 0)
#endif


typedef void HUGEPTR (CDECL **PF_SLOT_IEC_CALLBACK)(void);
typedef void HUGEPTR (CDECL *PF_SLOT_CALLBACK)(struct tagTask_Desc *pTask);

#define SLOT_BEFORE_READ_INPUTS		50
#define SLOT_READ_INPUTS			100
#define SLOT_AFTER_READ_INPUTS		15000
#define SLOT_IEC_CODE				30000
#define SLOT_BEFORE_WRITE_OUTPUTS	45000
#define SLOT_WRITE_OUTPUTS			60000
#define SLOT_AFTER_WRITE_OUTPUTS	75000

/* <SIL2/> */
typedef struct
{
	union
	{
		PF_SLOT_CALLBACK pfFunctionPointer;
		PF_SLOT_IEC_CALLBACK ppfFunctionPointer;
	} Fct;
	RTS_I32 nSlotNr;
	int bValid;
	int bIec;
} SlotPOU;

/**
 * <category>Iec Task Flags</category>
 * <element name="ITF_VISU_TASK" type="IN">This task is a visu task</element>
 */
#define ITF_VISU_TASK				0x00000001
#define ITF_DONT_SCHEDULE			0x00000002
#define ITF_ACTIVATE_TIMESLICING	0x00000004
#define ITF_DISABLE_TIMESLICING		0x00000008
#define ITF_EXCEPTION				0x00000010
#define ITF_SUSPENDED				0x00000020
#define ITF_ACTIVE					0x00000040
#define ITF_SUSPEND_AT_NEXT_CHANCE	0x00000080
#define ITF_IN_IO_UPDATE			0x00000100
#define ITF_INIT_OUTPUTS			0x00000200
#define ITF_ENTER_LOCK				0x00000400
#define ITF_LEAVE_READER_LOCK		0x00000800
#define ITF_SUSPENDED_BY_DEBUG_TASK	0x00001000
#define ITF_IN_DEBUG_CONTEXT		0x00002000

/**
 * <category>Iec Task Bits</category>
 * <element name="ITF_VISU_TASK" type="IN">This task is a visu task</element>
 */
#define ITF_BIT_VISU_TASK				0
#define ITF_BIT_DONT_SCHEDULE			1
#define ITF_BIT_ACTIVATE_TIMESLICING	2
#define ITF_BIT_DISABLE_TIMESLICING		3
#define ITF_BIT_EXCEPTION				4
#define ITF_BIT_SUSPENDED				5
#define ITF_BIT_ACTIVE					6
#define ITF_BIT_SUSPEND_AT_NEXT_CHANCE	7
#define ITF_BIT_IN_IO_UPDATE			8
#define ITF_BIT_INIT_OUTPUTS			9
#define ITF_BIT_ENTER_LOCK				10
#define ITF_BIT_LEAVE_READER_LOCK		11
#define ITF_BIT_SUSPENDED_BY_DEBUG_TASK	12
#define ITF_BIT_IN_DEBUG_CONTEXT		13


#define IsVisuTask(pTask)				(pTask->ulFlags & ITF_VISU_TASK)
#define DontSchedule(pTask)				(pTask->ulFlags & ITF_DONT_SCHEDULE)
#define IsTimeslicing(pTask)			(pTask->ulFlags & ITF_ACTIVATE_TIMESLICING)
#define IsTimeslicingDisabled(pTask)	(pTask->ulFlags & ITF_DISABLE_TIMESLICING)
#define IsSuspended(pTask)				(pTask->ulFlags & ITF_SUSPENDED)
#define IsException(pTask)				(pTask->ulFlags & ITF_EXCEPTION)
#define IsActive(pTask)					(pTask->ulFlags & ITF_ACTIVE)
#define IsSuspendAtNextChance(pTask)	(pTask->ulFlags & ITF_SUSPEND_AT_NEXT_CHANCE)
#define IsInIoUpdate(pTask)				(pTask->ulFlags & ITF_IN_IO_UPDATE)
#define DoInitOutputs(pTask)			(pTask->ulFlags & ITF_INIT_OUTPUTS)
#define IsEnterLockDisabled(pTask)		(pTask->ulFlags & ITF_ENTER_LOCK)
#define IsLeaveReaderLock(pTask)		(pTask->ulFlags & ITF_LEAVE_READER_LOCK)
#define IsSuspendedByDebugTask(pTask)	(pTask->ulFlags & ITF_SUSPENDED_BY_DEBUG_TASK)
#define IsInDebugContext(pTask)			(pTask->ulFlags & ITF_IN_DEBUG_CONTEXT)


#ifdef IECTASK_USE_NO_ATOMIC_BITACCESS
	#define SetVisuTask(pTask)			(pTask->ulFlags |= ITF_VISU_TASK)

	#define SetDontSchedule(pTask)		(pTask->ulFlags |= ITF_DONT_SCHEDULE)
	#define ResetDontSchedule(pTask)	(pTask->ulFlags &= ~ITF_DONT_SCHEDULE)

	#define SetTimeslicing(pTask)		(pTask->ulFlags |= ITF_ACTIVATE_TIMESLICING)
	#define ResetTimeslicing(pTask)		(pTask->ulFlags &= ~ITF_ACTIVATE_TIMESLICING)

	#define DisableTimeslicing(pTask)	(pTask->ulFlags |= ITF_DISABLE_TIMESLICING)
	#define EnableTimeslicing(pTask)	(pTask->ulFlags &= ~ITF_DISABLE_TIMESLICING)

	#define SetSuspended(pTask)			(pTask->ulFlags |= ITF_SUSPENDED)
	#define SetResumed(pTask)			(pTask->ulFlags &= ~ITF_SUSPENDED)

	#define SetException(pTask)			(pTask->ulFlags |= ITF_EXCEPTION)
	#define ResetException(pTask)		(pTask->ulFlags &= ~ITF_EXCEPTION)

	#define SetActive(pTask)			(pTask->ulFlags |= ITF_ACTIVE)
	#define SetInactive(pTask)			(pTask->ulFlags &= ~ITF_ACTIVE)

	#define SetSuspendAtNextChance(pTask)	(pTask->ulFlags |= ITF_SUSPEND_AT_NEXT_CHANCE)
	#define ResetSuspendAtNextChance(pTask)	(pTask->ulFlags &= ~ITF_SUSPEND_AT_NEXT_CHANCE)

	#define SetInIoUpdate(pTask)		(pTask->ulFlags |= ITF_IN_IO_UPDATE)
	#define ResetInIoUpdate(pTask)		(pTask->ulFlags &= ~ITF_IN_IO_UPDATE)

	#define SetInitOutputs(pTask)		(pTask->ulFlags |= ITF_INIT_OUTPUTS)
	#define ResetInitOutputs(pTask)		(pTask->ulFlags &= ~ITF_INIT_OUTPUTS)

	#define DisableEnterLock(pTask)		(pTask->ulFlags |= ITF_ENTER_LOCK)
	#define EnableEnterLock(pTask)		(pTask->ulFlags &= ~ITF_ENTER_LOCK)

	#define SetLeaveReaderLock(pTask)	(pTask->ulFlags |= ITF_LEAVE_READER_LOCK)
	#define ResetLeaveReaderLock(pTask)	(pTask->ulFlags &= ~ITF_LEAVE_READER_LOCK)
	
	#define SetSuspendedByDebugTask(pTask)		(pTask->ulFlags |= ITF_SUSPENDED_BY_DEBUG_TASK)
	#define ResetSuspendedByDebugTask(pTask)	(pTask->ulFlags &= ~ITF_SUSPENDED_BY_DEBUG_TASK)

	#define SetInDebugContext(pTask)	(pTask->ulFlags |= ITF_IN_DEBUG_CONTEXT)
	#define ResetInDebugContext(pTask)	(pTask->ulFlags &= ~ITF_IN_DEBUG_CONTEXT)
#else
	#define SetVisuTask(pTask)			CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_VISU_TASK, 1)

	#define SetDontSchedule(pTask)		CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_DONT_SCHEDULE, 1)
	#define ResetDontSchedule(pTask)	CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_DONT_SCHEDULE, 0)

	#define SetTimeslicing(pTask)		CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_ACTIVATE_TIMESLICING, 1)
	#define ResetTimeslicing(pTask)		CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_ACTIVATE_TIMESLICING, 0)

	#define DisableTimeslicing(pTask)	CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_DISABLE_TIMESLICING, 1)
	#define EnableTimeslicing(pTask)	CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_DISABLE_TIMESLICING, 0)

	#define SetSuspended(pTask)			CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_SUSPENDED, 1)
	#define SetResumed(pTask)			CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_SUSPENDED, 0)

	#define SetException(pTask)			CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_EXCEPTION, 1)
	#define ResetException(pTask)		CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_EXCEPTION, 0)

	#define SetActive(pTask)			CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_ACTIVE, 1)
	#define SetInactive(pTask)			CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_ACTIVE, 0)

	#define SetSuspendAtNextChance(pTask)	CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_SUSPEND_AT_NEXT_CHANCE, 1)
	#define ResetSuspendAtNextChance(pTask)	CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_SUSPEND_AT_NEXT_CHANCE, 0)

	#define SetInIoUpdate(pTask)		CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_IN_IO_UPDATE, 1)
	#define ResetInIoUpdate(pTask)		CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_IN_IO_UPDATE, 0)

	#define SetInitOutputs(pTask)		CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_INIT_OUTPUTS, 1)
	#define ResetInitOutputs(pTask)		CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_INIT_OUTPUTS, 0)

	#define DisableEnterLock(pTask)		CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_ENTER_LOCK, 1)
	#define EnableEnterLock(pTask)		CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_ENTER_LOCK, 0)

	#define SetLeaveReaderLock(pTask)	CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_LEAVE_READER_LOCK, 1)
	#define ResetLeaveReaderLock(pTask)	CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_LEAVE_READER_LOCK, 0)
	
	#define SetSuspendedByDebugTask(pTask)		CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_SUSPENDED_BY_DEBUG_TASK, 1)
	#define ResetSuspendedByDebugTask(pTask)	CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_SUSPENDED_BY_DEBUG_TASK, 0)

	#define SetInDebugContext(pTask)	CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_IN_DEBUG_CONTEXT, 1)
	#define ResetInDebugContext(pTask)	CAL_SysCpuTestAndSetBit(&pTask->ulFlags, sizeof(pTask->ulFlags), ITF_BIT_IN_DEBUG_CONTEXT, 0)
#endif

/**
 * <description>Local Task Description</description>
 * <SIL2/>
 */
typedef struct tagTask_Desc
{
	int iId;
	int bIgnoreWatchdogInCycle;
	RTS_HANDLE hSlotPOUPool;
	RTS_HANDLE hIecTask;
	RTS_HANDLE hSched;
	APPLICATION* pAppl;
	struct tagTask_Info *pInfo;
	RegContext Context;
	RTS_SYSTIME tCycleStart;
	RTS_SYSTIME tAccumulatedCycleTime;
	RTS_UI32 ulStackSize;
	unsigned char StaticSlotPool[MEM_GET_STATIC_LEN(NUM_OF_STATIC_IEC_SLOTS, SlotPOU)];
	void *pCppInstance;
	RTS_UI32 ulWatchdogCycleCount;
	RTS_UI32 ulFlags;
	int iWatchdogHitCount;
	RTS_I32 iWatchdogDisable2Ref;
#ifdef RTS_IECTASK_ENABLE_TASK_TRACE
	RTS_HANDLE hTracePacket;
	RTS_HANDLE hTraceRecord;
#endif
	SEHContext *pSEHContextHead;
	RTS_I32 nEnterWriteLock;
	RTS_HANDLE hRWLSync;
} Task_Desc;

typedef struct tagTASK_LIST
{
	int iTasks;
	int iMaxTasks;
	int bAllocated;
	Task_Desc **ppTasks;
} Task_List;

typedef struct
{
	RTS_IEC_WORD wVersion;
	RTS_IEC_INT nNumOfTasks;
	RTS_IEC_STRING *pszApplicationName;
	struct tagTask_Info **pptaskinfo;
} sys_setup_tasks_struct;

typedef struct
{
	RTS_IEC_STRING szTaskName[50];
	RTS_IEC_STRING szApplicationName[50];
	RTS_IEC_DWORD nSlotNr;
	RTS_IEC_VOID_FCTPTR dwFunctionPointer;
	RTS_IEC_DINT nReturnValue;
} sys_register_slot_pou_struct;

typedef struct
{
    RTS_IEC_DWORD dwVersion;
    RTS_IEC_STRING* pszGroupName;
    RTS_IEC_DWORD dwTaskGroupOptions;
    RTS_IEC_DINT diMaxCores;    /* maximum number of cores available in pdwCoreBits */
    RTS_IEC_DWORD* pdwCoreBits; /* Pointer to an array of DWORDS containing the core bits */
} TaskGroup_Info;

/*------>>> Functions only for backward compatibility ----------*/
/**
 * <description>LDATAREF_TYPE</description>
 */
typedef struct tagLDATAREF_TYPE
{
	RTS_IEC_UINT POURef;
	RTS_IEC_UDINT Offset;
	RTS_IEC_UDINT Size;
} LDATAREF_TYPE;

/**
 * <description>SYSIECTASKCONFENTRY</description>
 */
typedef struct tagSYSIECTASKCONFENTRY
{
	RTS_IEC_USINT byTaskNr;
	RTS_IEC_USINT byPriority;
	RTS_IEC_DINT lInterval;
	LDATAREF_TYPE ldrEvent;
	RTS_IEC_UINT wIndex;
	RTS_IEC_UDINT ulNameLen;
	RTS_IEC_STRING szName[81];
} SYSIECTASKCONFENTRY;

/**
 * <description>SYSIECTASKINFO</description>
 */
typedef struct tagSYSIECTASKINFO
{
	RTS_IEC_DWORD dwCount;
	RTS_IEC_DWORD dwCycleTime;
	RTS_IEC_DWORD dwCycleTimeMin;
	RTS_IEC_DWORD dwCycleTimeMax;
	RTS_IEC_DWORD dwCycleTimeAvg;
	RTS_IEC_WORD wStatus;
	RTS_IEC_WORD wMode;
} SYSIECTASKINFO;

/**
 * <description>This function return the iec task configuration </description>
 */
typedef struct tagiectaskgetconfig_struct
{
	RTS_IEC_UDINT udiTaskId;			/* VAR_INPUT */
	SYSIECTASKCONFENTRY *pTaskConfig;	/* VAR_INPUT */
	RTS_IEC_UDINT IecTaskGetConfig;		/* VAR_OUTPUT */
} iectaskgetconfig_struct;

DEF_API(`void',`CDECL',`iectaskgetconfig',`(iectaskgetconfig_struct *p)',1,0)

/**
 * <description>iectaskgetinfo</description>
 */
typedef struct tagiectaskgetinfo_struct
{
	RTS_IEC_STRING *stTaskName;			/* VAR_INPUT */
	SYSIECTASKINFO *pTaskInfo;			/* VAR_INPUT */
	RTS_IEC_UDINT IecTaskGetInfo;		/* VAR_OUTPUT */
} iectaskgetinfo_struct;

DEF_API(`void',`CDECL',`iectaskgetinfo',`(iectaskgetinfo_struct *p)',1,0)

/*------<<< Functions only for backward compatibility  ----------*/


/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Jitter distribution
 */
typedef struct tagJitter_Distribution
{
	RTS_IEC_WORD wRangeMax;		/* Maximal range */
	RTS_IEC_WORD wCountJitterNeg;		/* Jitters events negative */
	RTS_IEC_WORD wCountJitterPos;		/* Jitter event positive */
} Jitter_Distribution;

/**
 * Task info
 * Task information out of the task configuration
 * Note for SIL2: This information is already inside of the data area, so we don't need to tag it as safe anywhere.
 */
typedef struct tagTask_Info
{
	RTS_IEC_DWORD dwVersion;		/* Version of the structure */
	RTS_IEC_STRING *pszName;		/* Name of the task */
	RTS_IEC_INT nPriority;		/* IEC priority of the task (0..31) */
	RTS_IEC_INT KindOfTask;		/* Kind of task. See corresponding category TaskType. */
	RTS_IEC_BOOL bWatchdog;		/* Is TRUE, if watchdog is enabled */
	RTS_IEC_BOOL bProfiling;		/* Is TRUE, if profiling is enabled */
	RTS_IEC_BYTE *dwEventFunctionPointer;		/* Function pointer to the event check routine */
	RTS_IEC_STRING *pszExternalEvent;		/* Name of the event, if it is an external event task */
	RTS_IEC_BYTE *dwTaskEntryFunctionPointer;		/* Function pointer to the task code */
	RTS_IEC_DWORD dwWatchdogSensitivity;		/* Watchdog sensitivity */
	RTS_IEC_DWORD dwInterval;		/* Interval in microseconds */
	RTS_IEC_DWORD dwWatchdogTime;		/* Watchdog time in microseconds */
	RTS_IEC_DWORD dwCycleTime;		/* Cycle time in microseconds (last execution time) */
	RTS_IEC_DWORD dwAverageCycleTime;		/* Average cycle time in microseconds */
	RTS_IEC_DWORD dwMaxCycleTime;		/* Maximum cycle time in microseconds */
	RTS_IEC_DWORD dwMinCycleTime;		/* Minumum cycle time in microseconds */
	RTS_IEC_DINT iJitter;		/* Jitter in microseconds */
	RTS_IEC_DINT iJitterMin;		/* Minimal jitter */
	RTS_IEC_DINT iJitterMax;		/* Maximal jitter */
	RTS_IEC_DWORD dwCycleCount;		/* Cycle counter */
	RTS_IEC_WORD iState;		/* Task state. See category TaskState. */
	RTS_IEC_WORD wNumOfJitterDistributions;		/* Number jitter statistical distribution entries */
	Jitter_Distribution *pJitterDistribution;		/* Statistical jitter distribution entries */
	RTS_IEC_BOOL bTimeSlicing;		/* Timeslicing enabled */
#ifndef RTS_SIXTEENBITBYTES			/* only the byteaware structure needs a dummy byte here */ 
	RTS_IEC_BYTE byDummy;		
#endif	
	RTS_IEC_BOOL bShouldBlock;		/* Declared in IEC and evaluated there starting with compiler 3.5.6; If TRUE, the task will not call it's POUs */
	RTS_IEC_BOOL bActive;			/* Declared in IEC and evaluated there starting with compiler 3.5.6; Will be FALSE when the task is not active */
	RTS_IEC_DWORD dwIECCycleCount;		/* Cycle counter for execution of user code */
	RTS_IEC_INT nCoreConfigured;	/* Needed for backward compatability for V3.5.11.0 */
	RTS_IEC_INT nCoreCurrent;		/* Needed for backward compatability for V3.5.11.0 */
	TaskGroup_Info *pTaskGroup;		/* Pointer to task group description since V3.5.12.0 */
    
} Task_Info;

/**
 * Create a new IEC Task
 *
 * IEC Tasks itself are used by the scheduler of the runtime. They don't 
 *   essentially need a corresponding OS task or timer. They might be handled
 *   by the scheduler in a completely different way.
 *
 * Error code:
 *    + ERR_OK: The new task was successfully created.
 *    + ERR_FAILED: There was an error in a subsystem (e.g. the scheduler could not allocate his task handle).
 *    + ERR_PARAMETER: Invalid application- or task info pointer
 *    + ERR_OUT_OF_LIMITS: Maximum number of Tasks reached (target specific)
 *    + ERR_NOMEMORY: Unable to allocate the memory, that is necessary for the task description    
 *
 * :return: Handle to newly created task
 */
typedef struct tagiectaskcreate_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	/* Pointer to application that contains the task */
	Task_Info *pTaskInfo;				/* VAR_INPUT */	/* Pointer to task information */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to error code */
	RTS_IEC_HANDLE IecTaskCreate;		/* VAR_OUTPUT */	
} iectaskcreate_struct;

DEF_API(`void',`CDECL',`iectaskcreate',`(iectaskcreate_struct *p)',1,0xAF209471,0x03050800)

/**
 * Delete an IEC task with timeout
 * :return: Error code 
 */
typedef struct tagiectaskdelete2_struct
{
	RTS_IEC_HANDLE hIecTask;			/* VAR_INPUT */	/* Handle to task */
	RTS_IEC_UDINT ulTimeoutMs;			/* VAR_INPUT */	/* Timeout in milliseconds to wait for deleting the task. Some timeouts are predefined:
     + RTS_TIMEOUT_DEFAULT: Use default wait time
     + RTS_TIMEOUT_NO_WAIT: No wait */
	RTS_IEC_RESULT IecTaskDelete2;		/* VAR_OUTPUT */	
} iectaskdelete2_struct;

DEF_API(`void',`CDECL',`iectaskdelete2',`(iectaskdelete2_struct *p)',1,0x8269275F,0x03050800)

/**
 * Disable scheduling for the specified task
 * :return: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagiectaskdisablescheduling_struct
{
	RTS_IEC_HANDLE hIecTask;			/* VAR_INPUT */	/* Handle of the task */
	RTS_IEC_RESULT IecTaskDisableScheduling;	/* VAR_OUTPUT */	
} iectaskdisablescheduling_struct;

DEF_API(`void',`CDECL',`iectaskdisablescheduling',`(iectaskdisablescheduling_struct *p)',1,0xC3E3F168,0x03050800)

/**
 * Disable watchdog for the specified task
 *
 * .. note::
 *     - You have to enable the watchdog of the task with |IecTaskEnableWatchdog| and _not_ with |IecTaskEnableWatchdog2|, because they act on different task flags!
 * - The watchdog is disabled only for the current cycle! At the next cycle, the watchod is automatically enabled!
 * :return: Returns the runtime system error code (see CmpErrors.library)
 *	+ ERR_OK: The watchdog for the task was disabled
 *	+ ERR_PARAMETER: The task handle was invalid
 */
typedef struct tagiectaskdisablewatchdog_struct
{
	RTS_IEC_HANDLE hIecTask;			/* VAR_INPUT */	/* Handle of the task */
	RTS_IEC_RESULT IecTaskDisableWatchdog;	/* VAR_OUTPUT */	
} iectaskdisablewatchdog_struct;

DEF_API(`void',`CDECL',`iectaskdisablewatchdog',`(iectaskdisablewatchdog_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x2FF63495),0x03050800)

/**
 * Disable watchdog for the specified task
 *
 * .. note::
 *     - You have to enable the watchdog of the task with |IecTaskEnableWatchdog2| and _not_ with |IecTaskEnableWatchdog|, because they act on different task flags!
 *     - The watchdog is disabled until |IecTaskEnableWatchdog2| is called!!! So this is a security issue, if you never enable the watchdog!
 *     - As a consequence, you always have to call |IecTaskDisableWatchdog2| and |IecTaskEnableWatchdog2| symmetrical
 * - Can be called nested. First call disables the watchdog.
 * :return: Returns the runtime system error code (see CmpErrors.library)
 *	+ ERR_OK: The watchdog for the task was disabled
 *	+ ERR_PARAMETER: The task handle was invalid
 */
typedef struct tagiectaskdisablewatchdog2_struct
{
	RTS_IEC_HANDLE hIecTask;			/* VAR_INPUT */	/* Handle of the task */
	RTS_IEC_RESULT IecTaskDisableWatchdog2;	/* VAR_OUTPUT */	
} iectaskdisablewatchdog2_struct;

DEF_API(`void',`CDECL',`iectaskdisablewatchdog2',`(iectaskdisablewatchdog2_struct *p)',1,0x277BF3FE,0x03050800)

/**
 * Enable scheduling for one specified task
 * :return: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagiectaskenablescheduling_struct
{
	RTS_IEC_HANDLE hIecTask;			/* VAR_INPUT */	/* Handle of the task */
	RTS_IEC_RESULT IecTaskEnableScheduling;	/* VAR_OUTPUT */	
} iectaskenablescheduling_struct;

DEF_API(`void',`CDECL',`iectaskenablescheduling',`(iectaskenablescheduling_struct *p)',1,0x4A96918C,0x03050800)

/**
 * Enable watchdog for the specified task
 *
 * .. note::
 *     - You have to disable the watchdog of the task before with |IecTaskDisableWatchdog| and _not_ with |IecTaskDisableWatchdog2|, because they act on different task flags!
 * - The watchdog is enabled only at the next IEC cycle and _not_ immediately after calling this function!
 *     - If you disable with |IecTaskDisableWatchdog| and forgot to enable it, at least at the next cycle, the watchdog is automatically enabled!
 * :return: Returns the runtime system error code (see CmpErrors.library)
 *	+ ERR_OK: The watchdog for the task was enabled
 *	+ ERR_PARAMETER: The task handle was invalid
 */
typedef struct tagiectaskenablewatchdog_struct
{
	RTS_IEC_HANDLE hIecTask;			/* VAR_INPUT */	/* Handle of the task */
	RTS_IEC_RESULT IecTaskEnableWatchdog;	/* VAR_OUTPUT */	
} iectaskenablewatchdog_struct;

DEF_API(`void',`CDECL',`iectaskenablewatchdog',`(iectaskenablewatchdog_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x1CDBB730),0x03050800)

/**
 * Enable watchdog for the specified task
 *
 * .. note::
 *     - You have to disable the watchdog of the task before with |IecTaskDisableWatchdog2| and _not_ with |IecTaskDisableWatchdog|, because they act on different task flags!
 * - The watchdog is enabled only at the next IEC cycle and _not_ immediately after calling this function!
 *       But if you never enable the watchdog after calling |IecTaskDisableWatchdog2|, the watchdog is disabled forever!
 *     - As a consequence, you always have to call |IecTaskDisableWatchdog2| and |IecTaskEnableWatchdog2| symmetrical
 * - Can be called nested. Last call enables the watchdog.
 * :return: Returns the runtime system error code (see CmpErrors.library)
 *	+ ERR_OK: The watchdog for the task was enabled
 *	+ ERR_PARAMETER: The task handle was invalid
 */
typedef struct tagiectaskenablewatchdog2_struct
{
	RTS_IEC_HANDLE hIecTask;			/* VAR_INPUT */	/* Handle of the task */
	RTS_IEC_RESULT IecTaskEnableWatchdog2;	/* VAR_OUTPUT */	
} iectaskenablewatchdog2_struct;

DEF_API(`void',`CDECL',`iectaskenablewatchdog2',`(iectaskenablewatchdog2_struct *p)',1,0xE71D232F,0x03050800)

/**
 * Funktion to get own task handle
 * :return: Returns the current IEC task handle
 */
typedef struct tagiectaskgetcurrent_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer that returns the runtime system error code (see CmpErrors.library) */
	RTS_IEC_HANDLE IecTaskGetCurrent;	/* VAR_OUTPUT */	
} iectaskgetcurrent_struct;

DEF_API(`void',`CDECL',`iectaskgetcurrent',`(iectaskgetcurrent_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xFD44B5CC),0x03050800)

/**
 * Get the first IEC task in the specified application
 * :return: Returns the handle to the first IEC task
 */
typedef struct tagiectaskgetfirst_struct
{
	RTS_IEC_STRING *pszAppName;			/* VAR_INPUT */	/* Application name */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer that returns the runtime system error code (see CmpErrors.library) */
	RTS_IEC_HANDLE IecTaskGetFirst;		/* VAR_OUTPUT */	
} iectaskgetfirst_struct;

DEF_API(`void',`CDECL',`iectaskgetfirst',`(iectaskgetfirst_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD65D1BF9),0x03050800)

/**
 * OBSOLETE FUNCTION
 */
typedef struct tagiectaskgetinfo2_struct
{
	RTS_IEC_HANDLE hIecTask;			/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	Task_Info *IecTaskGetInfo2;			/* VAR_OUTPUT */	
} iectaskgetinfo2_struct;

DEF_API(`void',`CDECL',`iectaskgetinfo2',`(iectaskgetinfo2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x2A6E9BE6),0x03050800)

/**
 * Get the first IEC task in the specified application
 * :return: Returns the andle to the first IEC task 
 */
typedef struct tagiectaskgetnext_struct
{
	RTS_IEC_STRING *pszAppName;			/* VAR_INPUT */	/* Application name */
	RTS_IEC_HANDLE hPrevIecTask;		/* VAR_INPUT */	/* Handle to the previous task */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer that returns the runtime system error code (see CmpErrors.library) */
	RTS_IEC_HANDLE IecTaskGetNext;		/* VAR_OUTPUT */	
} iectaskgetnext_struct;

DEF_API(`void',`CDECL',`iectaskgetnext',`(iectaskgetnext_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC2306FF5),0x03050800)

/**
 * <description>iectaskgetprofiling</description>
 */
typedef struct tagiectaskgetprofiling_struct
{
	RTS_IEC_BOOL IecTaskGetProfiling;	/* VAR_OUTPUT */	
} iectaskgetprofiling_struct;

DEF_API(`void',`CDECL',`iectaskgetprofiling',`(iectaskgetprofiling_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x217F24B2),0x03050800)

/**
 * Reload a specified IEC task. Reload means here: Delete the task at the actual position and create it newly.
 * :return: Handle to the new created task
 */
typedef struct tagiectaskreload_struct
{
	RTS_IEC_HANDLE hIecTask;			/* VAR_INPUT */	/* Handle to the task to reload */
	RTS_IEC_UDINT udiTimeoutMs;			/* VAR_INPUT */	/* Timeout in milliseconds to wait, until the task deleted itself. Timeout can be one of the following predefined values:
     + RTS_TIMEOUT_DEFAULT: Default timeout to delete the task
     + RTS_TIMEOUT_NO_WAIT: Immediate deletion of the task
     See Timeouts details. */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to error code */
	RTS_IEC_HANDLE IecTaskReload;		/* VAR_OUTPUT */	
} iectaskreload_struct;

DEF_API(`void',`CDECL',`iectaskreload',`(iectaskreload_struct *p)',1,0x796FC828,0x03050800)

/**
 * Reset the task statistics of a task (see Task_Info member e.g. dwCycleTime, dwAverageCycleTime, etc.)
 * :return: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagiectaskresetstatistics_struct
{
	RTS_IEC_HANDLE hIecTask;			/* VAR_INPUT */	/* Handle of the task */
	RTS_IEC_RESULT IecTaskResetStatistics;	/* VAR_OUTPUT */	
} iectaskresetstatistics_struct;

DEF_API(`void',`CDECL',`iectaskresetstatistics',`(iectaskresetstatistics_struct *p)',1,0x6291DC5B,0x03050800)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/
							  

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>
 * <p>Create a new IEC Task</p>
 * <p>IEC Tasks itself are used by the scheduler of the runtime. They don't
 * essentially need a corresponding OS task or timer. They might be handled
 * by the scheduler in a completely different way.</p>
 * <p>For example: The embedded scheduler calls the task code directly in
 * the comm-cycle.</p>
 * <p>The Task registers itself at the scheduler, by calling the function
 * SchedAddTask().</p>
 * <p>When the define RTS_COMPACT is set, no semaphores are used.</p>
 * <p>When the define RTS_SIL2 is set, no dynamic memory allocation is used.</p>
 * </description>
 * <param name="pApp" type="IN" range="[NULL,VALID_APPLICATION]">Pointer to application that contains the task</param>
 * <parampseudo name="pApp.iId" type="IN" range="[0..APPL_NUM_OF_STATIC_APPLS-1,APPL_NUM_OF_STATIC_APPLS..INT_MAX]">Application ID</parampseudo>
 * <parampseudo name="s_hIecTaskPool" type="IN" range="[0,NUM_OF_STATIC_IEC_TASKS]">Number of already allocated tasks</parampseudo>
 * <param name="pTaskInfo" type="IN" range="[NULL,INVALID_TASKINFO,VALID_TASKINFO]">Pointer to task information</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to newly created task</result>
 * <errorcode name="pResult" type="ERR_OK">The new task was successfully created.</errorcode>
 * <errorcode name="pResult" type="ERR_FAILED">There was an error in a subsystem (e.g. the scheduler could not allocate his task handle).</errorcode>
 * <errorcode name="pResult" type="ERR_PARAMETER">Invalid application- or task info pointer</errorcode>
 * <errorcode name="pResult" type="ERR_OUT_OF_LIMITS">Maximum number of Tasks reached (target specific)</errorcode>
 * <errorcode name="pResult" type="ERR_NOMEMORY">Unable to allocate the memory, that is necessary for the task description</errorcode>
 */
DEF_CREATEITF_API(`RTS_HANDLE', `CDECL', `IecTaskCreate', `(APPLICATION *pApp, Task_Info *pTaskInfo, RTS_RESULT *pResult)')

/**
 * <description> Delete an IEC task </description>
 * <param name="hIecTask" type="IN">Handle to task</param>
 * <result>Error code</result>
 */
DEF_DELETEITF_API(`RTS_RESULT', `CDECL', `IecTaskDelete', `(RTS_HANDLE hIecTask)')

/**
 * <description> Delete an IEC task with timeout </description>
 * <param name="ulTimeoutMs" type="IN">Timeout in milliseconds to wait for deleting the task
 *	Some timeouts are predefined (see CmpStd.h):
 *	<ul>
 *		<li>RTS_TIMEOUT_DEFAULT: Use default wait time</li>
 *		<li>RTS_TIMEOUT_NO_WAIT: No wait</li>
 *	</ul>
 * </param>
 * <result>Error code</result>
 */
DEF_DELETEITF_API(`RTS_RESULT', `CDECL', `IecTaskDelete2', `(RTS_HANDLE hIecTask, RTS_UI32 ulTimeoutMs)')

/**
 * <description> Frees all IEC tasks </description>
 * <param name="pApp" type="IN">Pointer to specified application</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IecFreeTasks', `(APPLICATION *pApp)')

/**
 * <description> Frees all IEC tasks </description>
 * <param name="pApp" type="IN">Pointer to specified application</param>
 * <param name="ulTimeoutMs" type="IN">Timeout in milliseconds to release the tasks. RTS_TIMEOUT_DEFAULT can be used as the default value</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IecFreeTasks2', `(APPLICATION *pApp, RTS_UI32 ulTimeoutMs)')

/**
 * <description>
 * <p>Main cycle of an Iec task</p>
 * <p>Adopts the "running state" of the task, based on the current state of
 * it's application and starts the IEC task cycle:</p>
 * <ul>
 *     <li>ITF_DONT_SCHEDULE: Return ERR_PENDING</li>
 *     <li>OS_PROGRAM_LOADED: If not set, ERR_FAILED is returned</li>
 *     <li>AS_SINGLE_CYCLE: if task has TS_SINGLE_CYCLE flag set, set also TS_STOP</li>
 *     <li>AS_RUN: reset TS_STOP</li>
 *     <li>Application status != AS_RUN, AS_SINGLE_CYCLE: set TS_STOP</li>
 * </ul>
 * <p>Additionally this functions measures the time around the IEC task
 * cycle and calls IecTaskCheckWatchdog() to create a watchdog exception
 * if the time exceeded.</p>
 * <p>Note: This function may throw an exception, when program for the task was not, yet, loaded,
 * or when the task configuration contains no pointer for the cycle code.</p>
 * </description>
 * <param name="pTask" type="IN" range="[NULL,INVALID_TASK,VALID_TASK,VALID_TASK_NO_ENTRY]">Pointer to task description</param>
 * <parampseudo name="AppState" type="IN" range="[AS_NONE,AS_RUN,AS_STOP,AS_SINGLE_CYCLE]">The state of the task depends on the state of the corresponding application.</parampseudo>
 * <parampseudo name="AppOpState" type="IN" range="[OS_NONE,OS_PROGRAM_LOADED]">The state of the task depends on the state of the corresponding application.</parampseudo>
 * <parampseudo name="TaskFlags" type="IN" range="[0,ITF_DONT_SCHEDULE]">Defines the task flags before the call.</parampseudo>
 * <parampseudo name="TaskStatus" type="INOUT" range="[0,TS_SINGLE_CYCLE,TS_STOP,TS_SINGLE_CYCLE|TS_STOP]">Defines the task flags before the call.</parampseudo>
 * <parampseudo name="bException" type="OUT">Indicates if the function call generated an exception</parampseudo>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Task was called</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PENDING">Task was not called, but intentionally.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Task pointer was NULL or task was not valid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Program didn't finish load, or task-entry function pointer is not correctly relocated.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IecTaskCycle', `(Task_Desc* pTask)')

/**
 * <description> Calculate jitter time of task </description>
 * <param name="pTask" type="IN">Pointer to task description</param>
 * <param name="ptNow" type="IN">Pointer to actual microsecond time tick</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IecTaskUpdateJitterTime', `(Task_Desc* pTask, RTS_SYSTIME *ptNow)')

/**
 * <description>Calculate cycle time of task.</description>
 * <param name="pTask" type="IN" range="[NULL,VALID_TASK]">Pointer to task description</param> 
 * <param name="ptActUs" type="IN" range="[ACT_TIME]">Pointer to actual time tick in microseconds</param>
 * <parampseudo name="bIgnoreWatchdogInCycle" type="IN" range="[TRUE,FALSE]">Ignore watchdog in cycle</parampseudo>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IecTaskUpdateCycleTime', `(Task_Desc* pTask, RTS_SYSTIME *ptActUs)')

/**
 * <description> FUnction to check, if reset is allowed in the actual state on this application </description>
 * <param name="pApp" type="IN">Pointer to specified application</param>
 * <result>ERR_OK: Reset allowed, ERR_NOT_SUPPORTED: Not allowed (e.g. if one task is halted on a breakpoint)</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IecTasksResetAllowed', `(APPLICATION *pApp)')

/**
 * <description> Prepare reset for all IEC tasks specified by application </description>
 * <param name="pApp" type="IN">Pointer to specified application</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IecTasksPrepareReset', `(APPLICATION *pApp, int bResetOrigin)')

/**
 * <description> Initialize all IEC tasks after reset specified by application </description>
 * <param name="pApp" type="IN">Pointer to specified application</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IecTasksResetDone', `(APPLICATION *pApp, int bResetOrigin)')

/**
 * <description>Get the calculated timeout to wait for stop for specified application</description>
 * <param name="pApp" type="IN">Pointer to specified application</param>
 * <param name="pResult" type="OUT">Result of operation</param>
 * <errorcode name="pResult" type="ERR_OK">Timeout has been calculated successfully</errorcode>
 * <errorcode name="pResult" type="ERR_PARAMETER">Application is not valid</errorcode>
 * <result>calculated timeout</result>
 */
DEF_ITF_API(`RTS_UI32', `CDECL', `IecTaskGetWaitForStopTimeout', `(APPLICATION *pApp, RTS_RESULT *pResult)')

/**
 * <description>Wait, if all Iec-Tasks has recognized the stop status of the application</description>
 * <param name="pApp" type="IN">Pointer to specified application</param>
 * <param name="ulTimeoutMs" type="IN">Timeout in milliseconds to wait for stop.
 *	Some timeouts are predefined (see CmpStd.h):
 *	<ul>
 *		<li>RTS_TIMEOUT_INFINITE: Endless wait</li>
 *		<li>RTS_TIMEOUT_DEFAULT: Use default wait time</li>
 *		<li>RTS_TIMEOUT_NO_WAIT: No wait</li>
 *	</ul>
 * </param>
 * <param name="ulStopReason" type="IN">See corresponding category "Stop reason" in CmpAppItf.h and additionally "Stop reason option" in this file.</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IecTasksWaitForStop', `(APPLICATION *pApp, RTS_UI32 ulTimeoutMs, unsigned long ulStopReason)')

/**
 * <description>Init all outputs and write to the periphery.
 *	NOTE: Application must be in stop before calling this function!</description>
 * <param name="pApp" type="IN">Pointer to specified application</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IecTaskInitOutputs', `(APPLICATION *pApp)')

/**
 * <description>After this call no IEC task will be rescheduled, that is 
 * if it is not already running. May be used for executing onlinechange code.
 * Each call must be matched with a call to TaskLeaveExclusiveSection.
 * </description>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IecTaskEnterExclusiveSection',`(void)')

/**
 * <description>Leave an exclusiv section, that has been started by TaskEnterExclusiveSection</description>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IecTaskLeaveExclusiveSection',`(void)')

/**
 * <description>Enter an exclusive section.
 *	After this call, no IEC task will be rescheduled of the specified application, if it is not already running.
 *	Each call must be matched with a call to TaskLeaveExclusiveSection.
 * </description>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IecTaskEnterExclusiveSection2',`(APPLICATION *pApp)')

/**
 * <description>Try to enter an exclusive section.
 *	If the exclusive section can not be entered within the specified timeout, it depends on the bForceEnter flag what happens:
 *	- FALSE: ERR_FAILED is returned.
 *	- TRUE: Other tasks belonging to that application are successively suspended and their lock is released, while the try to enter the exclusive section is repeated.
 *	Each call must be matched with a call to TaskLeaveExclusiveSection.
 * </description>
 * <errorcode name="RTS_RESULT" type="ERR_OK">The exclusive section could be entered successfully</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">The exclusive section could not be entered.</errorcode>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IecTaskTryEnterExclusiveSection2',`(APPLICATION *pApp, RTS_UI32 timeoutMs, RTS_BOOL bForceEnter)')

/**
 * <description>Leave an exclusive section of the specified application, that has been entered by TaskEnterExclusiveSection or IecTaskTryEnterExclusiveSection2</description>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IecTaskLeaveExclusiveSection2',`(APPLICATION *pApp)')

/**
 * <description>
 * <p>External function is called by internal plc code to setup a plc task.
 * If a task can not be created, an exception is thrown.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_SETUP_TASKS_PARAM]">Pointer to task configuration entry. Is an implicit generated plc data structure.</param>
 * <parampseudo name="p.pszApplicationName" type="IN" range="[NULL,VALID_APPNAME]">Application name</parampseudo>
 * <parampseudo name="p.wNumOfTasks" type="IN" range="[0..NUM_OF_STATIC_IEC_TASKS-1,NUM_OF_STATIC_IEC_TASKS..INT_MAX]">Nmber of configured tasks</parampseudo>
 * <parampseudo name="p.pptaskinfo" type="IN" range="[VALID_TASKINFO_LIST]">Only valid info structures are allowed.</parampseudo>
 * <parampseudo name="OperationMode" type="IN" range="[RTS_SIL2_OPMODE_SAFE,RTS_SIL2_OPMODE_DEBUG]">Operation mode</parampseudo>
 * <parampseudo name="bException" type="OUT">Indicates if the function call generated an exception</parampseudo>
 * <parampseudo name="bTaskCreated" type="OUT">Indicates if the task could be created</parampseudo>
 * <result>no result</result>
 */
DEF_API(`void',`CDECL',`__sys__setup__tasks',`(sys_setup_tasks_struct* p)',1)

/**
 * <description>
 * <p>Register an IEC function function to a specific slot.</p>
 * <p>Slots are called in numbered order at specific positions in the task cycle</p>
 * <p>On SIL2 Runtimes, this call is only allowed in safety mode.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_REGISTER_SLOT_POU_PARAM]">IEC function call parameters.</param>
 * <parampseudo name="p.szApplicationName" type="IN" range="[NULL,VALID_APPNAME]">Application name</parampseudo>
 * <parampseudo name="p.szTaskName" type="IN" range="[NULL,VALID_TASKNAME]">Task name</parampseudo>
 * <parampseudo name="p.pFunctionPointer" type="IN" range="[NULL,VALID_SLOTFUNCTION]">Pointer to slot function</parampseudo>
 * <parampseudo name="p.nSlotNr" type="IN" range="[RTS_RANGE_OF_INT]">Slot number</parampseudo>
 * <parampseudo name="p.nReturnValue" type="OUT">Error Code</parampseudo>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Registration was successfull</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Call was not allowed in this context or registration failed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Application- or function pointer was NULL</errorcode>
 */
DEF_API(`void', `CDECL', `__sys__register__slot__pou', `(sys_register_slot_pou_struct* p)',1)

/**
 * <description>
 * <p>Unregister an IEC function function from a specific slot.</p>
 * <p>On SIL2 Runtimes, this call is only allowed in safety mode.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_UNREGISTER_SLOT_POU_PARAM]">IEC function call parameters.</param>
 * <parampseudo name="p.szApplicationName" type="IN" range="[NULL,VALID_APPNAME]">Application name</parampseudo>
 * <parampseudo name="p.szTaskName" type="IN" range="[NULL,VALID_TASKNAME]">Task name</parampseudo>
 * <parampseudo name="p.pFunctionPointer" type="IN" range="[NULL,VALID_SLOTFUNCTION]">Pointer to slot function</parampseudo>
 * <parampseudo name="p.nSlotNr" type="IN" range="[RTS_RANGE_OF_INT]">Slot number</parampseudo>
 * <parampseudo name="p.nReturnValue" type="OUT">Error Code</parampseudo>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Deregistration was successfull</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Call was not allowed in this context or deregistration failed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Application- or function pointer was NULL</errorcode>
 */
DEF_API(`void', `CDECL', `__sys__unregister__slot__pou', `(sys_register_slot_pou_struct* p)',1)

/**
 * <description>
 * <p>Register the given callback to all existing tasks of the application</p>
 * <p>On SIL2 Runtimes, this call is ignored in safety mode.</p>
 * </description>
 * <param name="pApp" type="IN" range="[NULL,VALID_APPLICATION]">Pointer to an application</param>
 * <param name="nSlotNr" type="IN" range="[RTS_RANGE_OF_INT]">Slotnumber</param>
 * <param name="pfSlotCallback" type="IN" range="[NULL,VALID_SLOTFUNCTION]">Pointer to Slot Callback</param>
 * <param name="bIecCallback" type="IN" range="[0,1]">Defines if the function pointer is an IEC or a C function</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Registration was successfull</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Call was not allowed in this context or registration failed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Application- or function pointer was NULL</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IecTaskRegisterSlotCallbacks', `(APPLICATION *pApp, RTS_I32 nSlotNr, PF_SLOT_CALLBACK pfSlotCallback, int bIecCallback)')

/**
 * <description>
 * <p>Unregister the given callback from all existing tasks of the application</p>
 * <p>On SIL2 Runtimes, this call is ignored in safety mode.</p>
 * </description>
 * <param name="pApp" type="IN" range="[NULL,VALID_APPLICATION]">Pointer to an application</param>
 * <param name="nSlotNr" type="IN" range="[RTS_RANGE_OF_INT]">Slotnumber</param>
 * <param name="pfSlotCallback" type="IN" range="[NULL,VALID_SLOTFUNCTION]">Pointer to Slot Callback</param>
 * <param name="bIecCallback" type="IN" range="[0,1]">Defines if the function pointer is an IEC or a C function</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Deregistration was successfull</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Call was not allowed in this context or deregistration failed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Application- or function pointer was NULL</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IecTaskUnregisterSlotCallbacks', `(APPLICATION *pApp, RTS_I32 nSlotNr, PF_SLOT_CALLBACK pfSlotCallback, int bIecCallback)')

/**
 * <description>
 * <p>Register the given callback to one specific IEC task.</p>
 * <p>On SIL2 Runtimes, this call throws an exception in safety mode.</p>
 * </description>
 * <parampseudo name="OperationMode" type="IN" range="[RTS_SIL2_OPMODE_SAFE,RTS_SIL2_OPMODE_DEBUG]">Operation mode</parampseudo>
 * <param name="pTask" type="IN" range="[NULL,VALID_TASK]">Handle IEC Task</param>
 * <param name="nSlotNr" type="IN" range="[RTS_RANGE_OF_INT]">Slotnumber</param>
 * <param name="pfSlotCallback" type="IN" range="[NULL,VALID_SLOTFUNCTION]">Pointer to Slot Callback</param>
 * <param name="bIecCallback" type="IN" range="[0,1]">Defines if the function pointer is an IEC or a C function</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Registration was successfull</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Call was not allowed in this context or registration failed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Application- or function pointer was NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">New slot could not be registered</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IecTaskRegisterSlotCallback', `(Task_Desc *pTask, RTS_I32 nSlotNr, PF_SLOT_CALLBACK pfSlotCallback, int bIecCallback)')

/**
 * <description>
 * <p>Unregister the given callback from the specific IEC task.</p>
 * <p>On SIL2 Runtimes, this call allows only IEC tasks in safety mode.</p>
 * </description>
 * <parampseudo name="OperationMode" type="IN" range="[RTS_SIL2_OPMODE_SAFE,RTS_SIL2_OPMODE_DEBUG]">Operation mode</parampseudo>
 * <param name="pTask" type="IN" range="[NULL,VALID_TASK]">Handle IEC Task</param>
 * <param name="nSlotNr" type="IN" range="[RTS_RANGE_OF_INT]">Slotnumber</param>
 * <param name="pfSlotCallback" type="IN" range="[NULL,VALID_SLOTFUNCTION]">Pointer to Slot Callback</param>
 * <param name="bIecCallback" type="IN" range="[0,1]">Defines if the function pointer is an IEC or a C function</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Registration was successfull</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Call was not allowed in this context or deregistration failed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Application- or function pointer was NULL</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IecTaskUnregisterSlotCallback', `(Task_Desc *pTask, RTS_I32 nSlotNr, PF_SLOT_CALLBACK pfSlotCallback, int bIecCallback)')

/**
 * <description>
 * <p>This function is obsolete and may not be used in SIL2 Runtime! (SIL2 Note: An Exception is generated if function is called in SIL2 Runtime!) </p>
 * <p>If supported for backward compatibility, it executes the
 * callbacks from a specific slot.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_RTS_CYCLE_PARAM]">IEC function call parameters.</param>
 * <parampseudo name="bException" type="OUT">Indicates if the function call generated an exception</parampseudo>
 * <result>Error code</result>
 */
DEF_API(`void',`CDECL',`__sys__rts__cycle',`(sys_rts_cycle_struct* p)',1)

/**
 * <description>
 * <p>This function executes a specific range of registered slots.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_RTS_CYCLE_2_PARAM]">IEC function call parameters.</param>
 * <parampseudo name="p.hTask" type="IN" range="[NULL,RTS_INVALID_HANDLE,VALID_TASKHANDLE]">Task Handle</parampseudo>
 * <parampseudo name="p.slotLower" type="IN" range="[RTS_RANGE_OF_INT]">Lower slot limit</parampseudo>
 * <parampseudo name="p.slotUpper" type="IN" range="[RTS_RANGE_OF_INT]">Upper slot limit</parampseudo>
 * <parampseudo name="bException" type="OUT">Indicates if the function call generated an exception</parampseudo>
 * <result>nothing</result>
 */
DEF_API(`void',`CDECL',`__sys__rts__cycle__2',`(sys_rts_cycle_2_struct* p)',1)

/**
 * <description>
 * <p>Return task description for a task, specified by it's task handle.
 * </p>
 * </description>
 * <param name="hIecTask" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TASKHANDLE]">Handle to task</param>
 * <result>Task Description or NULL if task handle was NULL or invalid</result>
 */
DEF_HANDLEITF_API(`Task_Desc *',`CDECL',`IecTaskGetDesc',`(RTS_HANDLE hIecTask)')

/**
 * <description>
 * <p>Get task, based on the application- and the task name.</p>
 * </description>
 * <param name="pszAppName" type="IN" range="[NULL,VALID_APPNAME,INVALID_APPNAME]">Pointer to application name</param>
 * <param name="pszTaskName" type="IN" range="[NULL,VALID_TASKNAME,INVALID_TASKNAME]">Pointer to task name</param>
 * <param name="pResult" type="OUT">Result of operation</param>
 * <errorcode name="pResult" type="ERR_OK">Task was found</errorcode>
 * <errorcode name="pResult" type="ERR_PARAMETER">Application- or task name where not valid</errorcode>
 * <errorcode name="pResult" type="ERR_FAILED">Application or task was not found</errorcode>
 * <result>Task handle</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecTaskGetHandle',`(char *pszAppName, char *pszTaskName, RTS_RESULT *pResult)')

/**
 * <description>Is called to get the task description of the current running task</description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Task handle</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecTaskGetCurrent',`(RTS_RESULT *pResult)')

/**
 * <description>Is called in debug loop, when IEC task is halted on breakpoint</description>
 * <param name="hIecTask" type="IN">Handle to IEC task</param>
 * <result>ERR_OK</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`IecTaskDebugLoop',`(RTS_HANDLE hIecTask)')

/**
 * <description>Is called before entering debug loop, when IEC task is halted on breakpoint</description>
 * <param name="hIecTask" type="IN">Handle to IEC task</param>
 * <result>ERR_OK</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`IecTaskDebugEnter',`(RTS_HANDLE hIecTask)')

/**
 * <description>Is called after leaving debug loop, when IEC task was halted on breakpoint</description>
 * <param name="hIecTask" type="IN">Handle to IEC task</param>
 * <result>ERR_OK</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`IecTaskDebugLeave',`(RTS_HANDLE hIecTask)')

/**
 * <description>Set context of the actual task</description>
 * <param name="hIecTask" type="IN">Handle to IEC task</param>
 * <param name="pContext" type="IN">Pointer to register context</param>
 * <result>ERR_OK</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`IecTaskSetContext',`(RTS_HANDLE hIecTask, RegContext *pContext)')

/**
 * <description>Get context of the actual task</description>
 * <param name="hIecTask" type="IN">Handle to IEC task</param>
 * <param name="pContext" type="IN">Pointer to register context</param>
 * <result>ERR_OK</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`IecTaskGetContext',`(RTS_HANDLE hIecTask, RegContext *pContext)')

/**
 * <description>Exception handler for the specified Iec task</description>
 * <param name="hIecTask" type="IN">Handle to IEC task</param>
 * <param name="ulException" type="IN">Exception</param>
 * <param name="pContext" type="IN">Pointer to register context</param>
 * <result>ERR_OK</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`IecTaskExceptionHandler',`(RTS_HANDLE hIecTask, RTS_UI32 ulException, RegContext Context)')

/**
 * <description>
 * <p>Get Task Description of a task by it's application ID
 * and it's task index.</p>
 * <p>Searches in the pool of all created tasks for the task,
 * with the given index in the specified application.</p>
 * </description>
 * <param name="pApp" type="IN" range="[NULL,VALID_APPLICATION]">Application object</param>
 * <parampseudo name="bTaskExists" type="IN" range="[FALSE,TRUE]">Defines whether the task exists or not</parampseudo> 
 * <param name="iIndex" type="IN" range="[VALID_INDEX,INVALID_INDEX]">Index of task within the application</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to task description, NULL if failed</result>
 * <errorcode name="pResult" type="ERR_OK">Task was found and description returned</errorcode>
 * <errorcode name="pResult" type="ERR_NO_MEMORY">No task pool was found</errorcode>
 * <errorcode name="pResult" type="ERR_PARAMETER">Application pointer was NULL</errorcode>
 */
DEF_ITF_API(`Task_Desc *',`CDECL',`IecTaskGetByIndex',`(APPLICATION* pApp, int iIndex, RTS_RESULT *pResult)')

/**
 * <description>Returns task handle of the task specified by index in an application</description>
 * <param name="pApp" type="IN">APPLICATION object</param>
 * <param name="iIndex" type="IN">Index of task in the task list of the application</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the task or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API_OWNCPP(`RTS_HANDLE',`CDECL',`IecTaskGetHandleByIndex',`(APPLICATION* pApp, int iIndex, RTS_RESULT *pResult)')

/**
 * <description>Returns task handle of the task specified by its unique Id</description>
 * <param name="pApp" type="IN">APPLICATION object</param>
 * <param name="iId" type="IN">Unique Id of the task</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the task or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`Task_Desc*',`CDECL',`IecTaskGetById',`(APPLICATION* pappl, int iId, RTS_RESULT *pResult)')

/**
 * <description>Returns the number of tasks of the specified applciation</description>
 * <param name="pAppl" type="IN">APPLICATION object</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`int',`CDECL',`IecTaskGetNumOfTasks',`(APPLICATION* pAppl, RTS_RESULT *pResult)')

/**
 * <description>
 * <p>Enable scheduling for all tasks of the specified application</p>
 * </description>
 * <param name="pApp" type="IN" range="[NULL,VALID_APPLICATION]">APPLICATION object</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">All tasks where enabled</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">The scheduler returned an error when trying to start the application</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecTaskEnableSchedulingAll',`(APPLICATION *pApp)')

/**
 * <description>
 * <p>Disable scheduling for all tasks of the specified application except the specified task.
 * Typically this interface is used to disable all tasks except the debug task.
 * </p>
 * </description>
 * <param name="pApp" type="IN">APPLICATION object</param>
 * <param name="hIecTaskToExclude" type="IN" range="[RTS_INVALID_HANDLE,VALID_TASKHANDLE]">Handle of task to exclude from scheduling.
 *	RTS_INVALID_HANDLE means, that all tasks are disabled</param>
 * <parampseudo name="s_hIecTaskPool" type="IN" range="[0,NUM_OF_STATIC_IEC_TASKS]">Number of already allocated tasks</parampseudo>
 * <parampseudo name="DisabledTasks" type="OUT" range="[WHICH_TAKS_ALL,WHICH_TASKS_ONE,WHICH_TASKS_NONE]">Defines, which tasks are disabled after this call</parampseudo>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecTaskDisableSchedulingAll',`(APPLICATION *pApp, RTS_HANDLE hIecTaskToExclude)')

/**
 * <description>
 * <p>Enable scheduling for one specified task.</p>
 * </description>
 * <param name="hIecTask" type="IN" range="[RTS_INVALID_HANDLE,VALID_TASKHANDLE]">Handle of task to enable scheduling</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">The task was enabled</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">The task handle was invalid</errorcode>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`IecTaskEnableScheduling',`(RTS_HANDLE hIecTask)')

/**
 * <description>Disable scheduling for the specified task</description>
 * <param name="hIecTask" type="IN">Handle of task to disable scheduling</param>
 * <result>Error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`IecTaskDisableScheduling',`(RTS_HANDLE hIecTask)')

/**
 * <description>
 * <p>Enable watchdog for the specified task</p>
 *	NOTES:
 *	- You have to disable the watchdog of the task before with IecTaskDisableWatchdog() and _not_ with IecTaskDisableWatchdog2(), because they act on different task flags!
 *	- The watchdog is enabled immediately after calling this function!
 *	- If you disable with IecTaskDisableWatchdog() and forgot to enable it, at least at the next cycle, the watchdog is automatically enabled!
 * </description>
 * <param name="hIecTask" type="IN" range="[RTS_INVALID_HANDLE,VALID_TASKHANDLE]">Handle of the task</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">The watchdog for the task was enabled</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">The task handle was invalid</errorcode>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`IecTaskEnableWatchdog',`(RTS_HANDLE hIecTask)')

/**
 * <description>
 * <p>Disable watchdog for the specified task</p>
 *	NOTE:
 *	- You have to enable the watchdog of the task with IecTaskEnableWatchdog() and _not_ with IecTaskEnableWatchdog2(), because they act on different task flags!
 *	- The watchdog is disabled only for the current cycle! At the next cycle, the watchod is automatically enabled!
 * </description>
 * <param name="hIecTask" type="IN" range="[RTS_INVALID_HANDLE,VALID_TASKHANDLE]">Handle of the task</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">The watchdog for the task was disabled</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">The task handle was invalid</errorcode>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`IecTaskDisableWatchdog',`(RTS_HANDLE hIecTask)')

/**
 * <description>
 * <p>Enable watchdog for the specified task</p>
 *	NOTES:
 *	- You have to disable the watchdog of the task before with IecTaskDisableWatchdog2() and _not_ with IecTaskDisableWatchdog(), because they act on different task flags!
 *	- The watchdog is enabled only at the next IEC cycle and _not_ immediately after calling this function!
 *	  But if you never enable the watchdog after calling IecTaskDisableWatchdog2(), the watchdog is disabled forever!
 *	- As a consequence, you always have to call IecTaskDisableWatchdog2 and IecTaskEnableWatchdog2 symmetrical
 *  - Can be called nested. Last call enables the watchdog.
 * </description>
 * <param name="hIecTask" type="IN" range="[RTS_INVALID_HANDLE,VALID_TASKHANDLE]">Handle of the task</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">The watchdog for the task was enabled</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">The task handle was invalid</errorcode>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`IecTaskEnableWatchdog2',`(RTS_HANDLE hIecTask)')

/**
 * <description>
 * <p>Disable watchdog for the specified task. Can be used to disable the watchdog over several cycles (instead of IecTaskDisableWatchdog)</p>
 *	NOTES:
 *	- You have to enable the watchdog of the task with IecTaskEnableWatchdog2() and _not_ with IecTaskEnableWatchdog(), because they act on different task flags!
 *	- The watchdog is disabled until IecTaskEnableWatchdog2() is called!!! So this is a security issue, if you never enable the watchdog!
 *	- As a consequence, you always have to call IecTaskDisableWatchdog2 and IecTaskEnableWatchdog2 symmetrical
 *  - Can be called nested. First call disables the watchdog.
 * </description>
 * <param name="hIecTask" type="IN" range="[RTS_INVALID_HANDLE,VALID_TASKHANDLE]">Handle of the task</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">The watchdog for the task was disabled</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">The task handle was invalid</errorcode>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`IecTaskDisableWatchdog2',`(RTS_HANDLE hIecTask)')

/**
 * <description>
 * <p>Check if the watchdog of a task expired.</p>
 * <p>This function is called by the scheduler, as well as from the 
 * task context.</p>
 * <p>If the watchdog expired, an exception is generated and (depending
 * on the scheduler) the function will return ERR_FAILED. Note, that
 * this function does not essentially return, because some schedulers
 * are not able to recover from this error in a way that the function
 * can return.</p>
 * <p>Handling of the Sensitivity:
 * <ul>
 *   <li>0,1,2: Exception in first cycle if it exceeds WD time * sensitivity</li>
 *   <li>3-MAX_INT: Exception in (sensitivity-1)'th cycle if time exceeded, or in first if time exceeded by WD time * sensitivity</li>
 * </ul>
 * </p>
 * </description>
 * <param name="hIecTask" type="IN" range="[RTS_INVALID_HANDLE,VALID_TASKHANDLE]">Handle of the task</param>
 * <param name="ptActUs" type="IN" range="[0,PT1,PT2,PT3,PT4]">Optional pointer to actual time tick in microseconds. Can be NULL.</param>
 * <parampseudo name="hIecTask.watchdogtime" type="IN" range="[0..400000000,400000001..INT_MAX]">Configured WD time</parampseudo>
 * <parampseudo name="hIecTask.sensitivity" type="IN" range="[0,1,2,3..10,11..INT_MAX]">Configured WD sensitivity</parampseudo>
 * <parampseudo name="hIecTask.iWatchdogHitCount" type="IN" range="[0,1,2,3]">Specifies how often the watchdog exceeded already</parampseudo>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">The watchdog did not expire or it is currently disabled for this task</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">The watchdog expired and the scheduler returned from the exception</errorcode>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`IecTaskCheckWatchdog',`(RTS_HANDLE hIecTask, RTS_SYSTIME *ptActUs)')

/**
 * <description>Get the first IEC task in the specified application</description>
 * <param name="pszAppName" type="IN">Application name, to which the task is bound</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="pResult" type="ERR_OK">Task found</errorcode>
 * <errorcode name="pResult" type="ERR_NO_OBJECT">No task found</errorcode>
 * <errorcode name="pResult" type="ERR_PARAMETER">Application name was NULL</errorcode>
 * <result>Handle to the task or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecTaskGetFirst',`(char *pszAppName, RTS_RESULT *pResult)')

/**
 * <description>
 * <p>Get the successor of an IEC task.</p>
 * <p>Return the successor of an IEC task, based on an
 * application and a predecessor.</p>
 * </description>
 * <param name="pszAppName" type="IN" range="[VALID_APPNAME,INVALID_APPNAME]">Application name, to which the task is bound</param>
 * <param name="hPrevIecTask" type="IN" range="[RTS_INVALID_HANDLE,VALID_TASKHANDLE]">Handle to previous task provided by IecTaskGetFirst()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="pResult" type="ERR_OK">Task found</errorcode>
 * <errorcode name="pResult" type="ERR_NO_OBJECT">No task found</errorcode>
 * <errorcode name="pResult" type="ERR_PARAMETER">Application name was NULL, or handle to prev task was invalid</errorcode>
 * <errorcode name="pResult" type="ERR_NOTINITIALIZED">The component was not correctly initialized</errorcode>
 * <result>Handle to the task or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecTaskGetNext',`(char *pszAppName, RTS_HANDLE hPrevIecTask, RTS_RESULT *pResult)')

/**
 * <description>
 * <p>Get the first IEC task of the specified application</p>
 * </description>
 * <param name="pApp" type="IN" range="[NULL,VALID_APPLICATION]">Handle of the application that contains the task</param>
 * <parampseudo name="bTaskExists" type="IN" range="[FALSE,TRUE]">Defines whether the task exists or not</parampseudo>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="pResult" type="ERR_OK">Task found</errorcode>
 * <errorcode name="pResult" type="ERR_NO_OBJECT">No task found</errorcode>
 * <errorcode name="pResult" type="ERR_PARAMETER">Application pointer was NULL</errorcode>
 * <errorcode name="pResult" type="ERR_NOTINITIALIZED">Component was not initialized</errorcode>
 * <result>Handle to the task or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API_OWNCPP(`RTS_HANDLE',`CDECL',`IecTaskGetFirst2',`(APPLICATION *pApp, RTS_RESULT *pResult)')

/**
 * <description>
 * <p>Get the successor of an IEC task.</p>
 * <p>Return the successor of an IEC task, based on an
 * application and a predecessor.</p>
 * </description>
 * <param name="pApp" type="IN" range="[NULL,VALID_APPLICATION]">Handle of the application that contains the task</param>
 * <param name="hPrevIecTask" type="IN" range="[RTS_INVALID_HANDLE,VALID_TASKHANDLE]">Handle to previous task provided by IecTaskGetFirst2()</param>
 * <parampseudo name="bSuccessorExists" type="IN" range="[FALSE,TRUE]">Defines if a successor to hPrevIecTask exists or not.</parampseudo>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="pResult" type="ERR_OK">Task found</errorcode>
 * <errorcode name="pResult" type="ERR_NO_OBJECT">No task found</errorcode>
 * <errorcode name="pResult" type="ERR_PARAMETER">Application name was NULL, or handle to prev task was invalid</errorcode>
 * <errorcode name="pResult" type="ERR_NOTINITIALIZED">The component was not correctly initialized</errorcode>
 * <result>Handle to the task or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API_OWNCPP(`RTS_HANDLE',`CDECL',`IecTaskGetNext2',`(APPLICATION *pApp, RTS_HANDLE hPrevIecTask, RTS_RESULT *pResult)')

/**
 * <description>Reload a specified IEC task. Reload means here: Delete the task at the actual position and create it newly.</description>
 * <param name="hIecTask" type="IN">Handle to the task to reload</param>
 * <param name="ulTimeoutMs" type="IN">Timeout in milliseconds to wait, until the task deleted itself. Timeout can be one of the following predefined values:
 *		RTS_TIMEOUT_DEFAULT: Default timeout to delete the task
 *		RTS_TIMEOUT_NO_WAIT: Immediate deletion of the task</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the new created task </result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `IecTaskReload', `(RTS_HANDLE hIecTask, RTS_UI32 ulTimeoutMs, RTS_RESULT *pResult)')

/**
 * <description>
 * <p>Calculate a task ID based on an application index and a task index.</p>
 * <p>This ID corresponds directly to the IDs that are used in the CoDeSys
 * programming system to identify a task.</p>
 * <p>The valid range of iIndex depends on the cpu. The limit is always
 * the square route of UINT_MAX, because the upper half of the datatype
 * is used for the application ID, and the lower half for the task index.</p>
 * </description>
 * <param name="pApp" type="IN" range="[NULL,VALID_APPLICATION]">Pointer to the application of the task.</param>
 * <parampseudo name="pApp.iId" type="IN" range="[-1,0..MAX_APPINDEX,MAX_APPINDEX+1..INT_MAX]">Application ID.</parampseudo>
 * <param name="iIndex" type="IN" range="[-1,0..MAX_TASKINDEX,MAX_TASKINDEX+1..INT_MAX]">Index of the task within it's application</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Unique Id of the task</result>
 * <errorcode name="pResult" type="ERR_OK">The ID was successfully calculated</errorcode>
 * <errorcode name="pResult" type="ERR_PARAMETER">Application pointer was null or IDs where out of range</errorcode>
 */
DEF_ITF_API(`int',`CDECL',`IecTaskCalculateId',`(APPLICATION *pApp, int iIndex, RTS_RESULT *pResult)')

/**
 * <description>Function to make a busy wait, while at least one task of the specified application is active</description>
 * <param name="pApp" type="IN">Handle of the application that contains the tasks to check. If pApp == NULL, all IEC tasks are checked.</param>
 * <param name="ulTimeoutMs" type="IN">Timeout in milliseconds to wait for deleting the task</param>
 * <result>Error code:</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">No task is active</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">At least one task is active after timeout</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Application name was NULL</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecTaskWaitTasksActive',`(APPLICATION *pApp, RTS_UI32 ulTimeoutMs)')

/**
 * <description>Activates a single cycle on every cyclic and freewheeling task of the specified application</description>
 * <param name="pApp" type="IN">Handle of the application to do a single cycle</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">No task is active</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Application name was NULL</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecTaskSingleCycle',`(APPLICATION *pApp)')

/**
 * <description>Reset the task statistics of a task (see Task_Info member e.g. dwCycleTime, dwAverageCycleTime, etc.)</description>
 * <param name="hIecTask" type="IN">Handle to the task</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">No task is active</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Application name was NULL</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IecTaskResetStatistics', `(RTS_HANDLE hIecTask)')

/**
 * <description>Is called entering the debug handler, if an IEC task is halted on a breakpoint</description>
 * <param name="hIecTask" type="IN">Handle to the task, which enters the debug handler</param>
 * <result>Error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`IecTaskDebugHandlerEnter',`(RTS_HANDLE hIecTask)')

/**
 * <description>Is called leaving the debug handler, if an IEC task is leaving a breakpoint</description>
 * <param name="hIecTask" type="IN">Handle to the task, which leaves the debug handler</param>
 * <result>Error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`IecTaskDebugHandlerLeave',`(RTS_HANDLE hIecTask)')

#ifdef __cplusplus
}
#endif
