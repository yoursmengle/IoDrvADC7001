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


	
	
#ifndef _CMPIECTASKITF_H_
#define _CMPIECTASKITF_H_

#include "CmpStd.h"

 

 




#include "CmpAppItf.h"
#include "CmpMemPoolItf.h"
#include "SysTimeItf.h"


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

void CDECL CDECL_EXT iectaskgetconfig(iectaskgetconfig_struct *p);
typedef void (CDECL CDECL_EXT* PFIECTASKGETCONFIG_IEC) (iectaskgetconfig_struct *p);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKGETCONFIG_NOTIMPLEMENTED)
	#define USE_iectaskgetconfig
	#define EXT_iectaskgetconfig
	#define GET_iectaskgetconfig(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iectaskgetconfig(p0) 
	#define CHK_iectaskgetconfig  FALSE
	#define EXP_iectaskgetconfig  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iectaskgetconfig
	#define EXT_iectaskgetconfig
	#define GET_iectaskgetconfig(fl)  CAL_CMGETAPI( "iectaskgetconfig" ) 
	#define CAL_iectaskgetconfig  iectaskgetconfig
	#define CHK_iectaskgetconfig  TRUE
	#define EXP_iectaskgetconfig  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"iectaskgetconfig", (RTS_UINTPTR)iectaskgetconfig, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_iectaskgetconfig
	#define EXT_iectaskgetconfig
	#define GET_iectaskgetconfig(fl)  CAL_CMGETAPI( "iectaskgetconfig" ) 
	#define CAL_iectaskgetconfig  iectaskgetconfig
	#define CHK_iectaskgetconfig  TRUE
	#define EXP_iectaskgetconfig  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"iectaskgetconfig", (RTS_UINTPTR)iectaskgetconfig, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskiectaskgetconfig
	#define EXT_CmpIecTaskiectaskgetconfig
	#define GET_CmpIecTaskiectaskgetconfig  ERR_OK
	#define CAL_CmpIecTaskiectaskgetconfig  iectaskgetconfig
	#define CHK_CmpIecTaskiectaskgetconfig  TRUE
	#define EXP_CmpIecTaskiectaskgetconfig  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"iectaskgetconfig", (RTS_UINTPTR)iectaskgetconfig, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_iectaskgetconfig
	#define EXT_iectaskgetconfig
	#define GET_iectaskgetconfig(fl)  CAL_CMGETAPI( "iectaskgetconfig" ) 
	#define CAL_iectaskgetconfig  iectaskgetconfig
	#define CHK_iectaskgetconfig  TRUE
	#define EXP_iectaskgetconfig  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"iectaskgetconfig", (RTS_UINTPTR)iectaskgetconfig, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_iectaskgetconfig  PFIECTASKGETCONFIG_IEC pfiectaskgetconfig;
	#define EXT_iectaskgetconfig  extern PFIECTASKGETCONFIG_IEC pfiectaskgetconfig;
	#define GET_iectaskgetconfig(fl)  s_pfCMGetAPI2( "iectaskgetconfig", (RTS_VOID_FCTPTR *)&pfiectaskgetconfig, (fl), 0, 0)
	#define CAL_iectaskgetconfig  pfiectaskgetconfig
	#define CHK_iectaskgetconfig  (pfiectaskgetconfig != NULL)
	#define EXP_iectaskgetconfig   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"iectaskgetconfig", (RTS_UINTPTR)iectaskgetconfig, 1, 0) 
#endif


/**
 * <description>iectaskgetinfo</description>
 */
typedef struct tagiectaskgetinfo_struct
{
	RTS_IEC_STRING *stTaskName;			/* VAR_INPUT */
	SYSIECTASKINFO *pTaskInfo;			/* VAR_INPUT */
	RTS_IEC_UDINT IecTaskGetInfo;		/* VAR_OUTPUT */
} iectaskgetinfo_struct;

void CDECL CDECL_EXT iectaskgetinfo(iectaskgetinfo_struct *p);
typedef void (CDECL CDECL_EXT* PFIECTASKGETINFO_IEC) (iectaskgetinfo_struct *p);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKGETINFO_NOTIMPLEMENTED)
	#define USE_iectaskgetinfo
	#define EXT_iectaskgetinfo
	#define GET_iectaskgetinfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iectaskgetinfo(p0) 
	#define CHK_iectaskgetinfo  FALSE
	#define EXP_iectaskgetinfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iectaskgetinfo
	#define EXT_iectaskgetinfo
	#define GET_iectaskgetinfo(fl)  CAL_CMGETAPI( "iectaskgetinfo" ) 
	#define CAL_iectaskgetinfo  iectaskgetinfo
	#define CHK_iectaskgetinfo  TRUE
	#define EXP_iectaskgetinfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"iectaskgetinfo", (RTS_UINTPTR)iectaskgetinfo, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_iectaskgetinfo
	#define EXT_iectaskgetinfo
	#define GET_iectaskgetinfo(fl)  CAL_CMGETAPI( "iectaskgetinfo" ) 
	#define CAL_iectaskgetinfo  iectaskgetinfo
	#define CHK_iectaskgetinfo  TRUE
	#define EXP_iectaskgetinfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"iectaskgetinfo", (RTS_UINTPTR)iectaskgetinfo, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskiectaskgetinfo
	#define EXT_CmpIecTaskiectaskgetinfo
	#define GET_CmpIecTaskiectaskgetinfo  ERR_OK
	#define CAL_CmpIecTaskiectaskgetinfo  iectaskgetinfo
	#define CHK_CmpIecTaskiectaskgetinfo  TRUE
	#define EXP_CmpIecTaskiectaskgetinfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"iectaskgetinfo", (RTS_UINTPTR)iectaskgetinfo, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_iectaskgetinfo
	#define EXT_iectaskgetinfo
	#define GET_iectaskgetinfo(fl)  CAL_CMGETAPI( "iectaskgetinfo" ) 
	#define CAL_iectaskgetinfo  iectaskgetinfo
	#define CHK_iectaskgetinfo  TRUE
	#define EXP_iectaskgetinfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"iectaskgetinfo", (RTS_UINTPTR)iectaskgetinfo, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_iectaskgetinfo  PFIECTASKGETINFO_IEC pfiectaskgetinfo;
	#define EXT_iectaskgetinfo  extern PFIECTASKGETINFO_IEC pfiectaskgetinfo;
	#define GET_iectaskgetinfo(fl)  s_pfCMGetAPI2( "iectaskgetinfo", (RTS_VOID_FCTPTR *)&pfiectaskgetinfo, (fl), 0, 0)
	#define CAL_iectaskgetinfo  pfiectaskgetinfo
	#define CHK_iectaskgetinfo  (pfiectaskgetinfo != NULL)
	#define EXP_iectaskgetinfo   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"iectaskgetinfo", (RTS_UINTPTR)iectaskgetinfo, 1, 0) 
#endif


/*------<<< Functions only for backward compatibility  ----------*/


/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

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

void CDECL CDECL_EXT iectaskcreate(iectaskcreate_struct *p);
typedef void (CDECL CDECL_EXT* PFIECTASKCREATE_IEC) (iectaskcreate_struct *p);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKCREATE_NOTIMPLEMENTED)
	#define USE_iectaskcreate
	#define EXT_iectaskcreate
	#define GET_iectaskcreate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iectaskcreate(p0) 
	#define CHK_iectaskcreate  FALSE
	#define EXP_iectaskcreate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iectaskcreate
	#define EXT_iectaskcreate
	#define GET_iectaskcreate(fl)  CAL_CMGETAPI( "iectaskcreate" ) 
	#define CAL_iectaskcreate  iectaskcreate
	#define CHK_iectaskcreate  TRUE
	#define EXP_iectaskcreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskcreate", (RTS_UINTPTR)iectaskcreate, 1, 0xAF209471, 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_iectaskcreate
	#define EXT_iectaskcreate
	#define GET_iectaskcreate(fl)  CAL_CMGETAPI( "iectaskcreate" ) 
	#define CAL_iectaskcreate  iectaskcreate
	#define CHK_iectaskcreate  TRUE
	#define EXP_iectaskcreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskcreate", (RTS_UINTPTR)iectaskcreate, 1, 0xAF209471, 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskiectaskcreate
	#define EXT_CmpIecTaskiectaskcreate
	#define GET_CmpIecTaskiectaskcreate  ERR_OK
	#define CAL_CmpIecTaskiectaskcreate  iectaskcreate
	#define CHK_CmpIecTaskiectaskcreate  TRUE
	#define EXP_CmpIecTaskiectaskcreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskcreate", (RTS_UINTPTR)iectaskcreate, 1, 0xAF209471, 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iectaskcreate
	#define EXT_iectaskcreate
	#define GET_iectaskcreate(fl)  CAL_CMGETAPI( "iectaskcreate" ) 
	#define CAL_iectaskcreate  iectaskcreate
	#define CHK_iectaskcreate  TRUE
	#define EXP_iectaskcreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskcreate", (RTS_UINTPTR)iectaskcreate, 1, 0xAF209471, 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iectaskcreate  PFIECTASKCREATE_IEC pfiectaskcreate;
	#define EXT_iectaskcreate  extern PFIECTASKCREATE_IEC pfiectaskcreate;
	#define GET_iectaskcreate(fl)  s_pfCMGetAPI2( "iectaskcreate", (RTS_VOID_FCTPTR *)&pfiectaskcreate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xAF209471, 0x03050800)
	#define CAL_iectaskcreate  pfiectaskcreate
	#define CHK_iectaskcreate  (pfiectaskcreate != NULL)
	#define EXP_iectaskcreate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskcreate", (RTS_UINTPTR)iectaskcreate, 1, 0xAF209471, 0x03050800) 
#endif


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

void CDECL CDECL_EXT iectaskdelete2(iectaskdelete2_struct *p);
typedef void (CDECL CDECL_EXT* PFIECTASKDELETE2_IEC) (iectaskdelete2_struct *p);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKDELETE2_NOTIMPLEMENTED)
	#define USE_iectaskdelete2
	#define EXT_iectaskdelete2
	#define GET_iectaskdelete2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iectaskdelete2(p0) 
	#define CHK_iectaskdelete2  FALSE
	#define EXP_iectaskdelete2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iectaskdelete2
	#define EXT_iectaskdelete2
	#define GET_iectaskdelete2(fl)  CAL_CMGETAPI( "iectaskdelete2" ) 
	#define CAL_iectaskdelete2  iectaskdelete2
	#define CHK_iectaskdelete2  TRUE
	#define EXP_iectaskdelete2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskdelete2", (RTS_UINTPTR)iectaskdelete2, 1, 0x8269275F, 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_iectaskdelete2
	#define EXT_iectaskdelete2
	#define GET_iectaskdelete2(fl)  CAL_CMGETAPI( "iectaskdelete2" ) 
	#define CAL_iectaskdelete2  iectaskdelete2
	#define CHK_iectaskdelete2  TRUE
	#define EXP_iectaskdelete2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskdelete2", (RTS_UINTPTR)iectaskdelete2, 1, 0x8269275F, 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskiectaskdelete2
	#define EXT_CmpIecTaskiectaskdelete2
	#define GET_CmpIecTaskiectaskdelete2  ERR_OK
	#define CAL_CmpIecTaskiectaskdelete2  iectaskdelete2
	#define CHK_CmpIecTaskiectaskdelete2  TRUE
	#define EXP_CmpIecTaskiectaskdelete2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskdelete2", (RTS_UINTPTR)iectaskdelete2, 1, 0x8269275F, 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iectaskdelete2
	#define EXT_iectaskdelete2
	#define GET_iectaskdelete2(fl)  CAL_CMGETAPI( "iectaskdelete2" ) 
	#define CAL_iectaskdelete2  iectaskdelete2
	#define CHK_iectaskdelete2  TRUE
	#define EXP_iectaskdelete2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskdelete2", (RTS_UINTPTR)iectaskdelete2, 1, 0x8269275F, 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iectaskdelete2  PFIECTASKDELETE2_IEC pfiectaskdelete2;
	#define EXT_iectaskdelete2  extern PFIECTASKDELETE2_IEC pfiectaskdelete2;
	#define GET_iectaskdelete2(fl)  s_pfCMGetAPI2( "iectaskdelete2", (RTS_VOID_FCTPTR *)&pfiectaskdelete2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x8269275F, 0x03050800)
	#define CAL_iectaskdelete2  pfiectaskdelete2
	#define CHK_iectaskdelete2  (pfiectaskdelete2 != NULL)
	#define EXP_iectaskdelete2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskdelete2", (RTS_UINTPTR)iectaskdelete2, 1, 0x8269275F, 0x03050800) 
#endif


/**
 * Disable scheduling for the specified task
 * :return: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagiectaskdisablescheduling_struct
{
	RTS_IEC_HANDLE hIecTask;			/* VAR_INPUT */	/* Handle of the task */
	RTS_IEC_RESULT IecTaskDisableScheduling;	/* VAR_OUTPUT */	
} iectaskdisablescheduling_struct;

void CDECL CDECL_EXT iectaskdisablescheduling(iectaskdisablescheduling_struct *p);
typedef void (CDECL CDECL_EXT* PFIECTASKDISABLESCHEDULING_IEC) (iectaskdisablescheduling_struct *p);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKDISABLESCHEDULING_NOTIMPLEMENTED)
	#define USE_iectaskdisablescheduling
	#define EXT_iectaskdisablescheduling
	#define GET_iectaskdisablescheduling(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iectaskdisablescheduling(p0) 
	#define CHK_iectaskdisablescheduling  FALSE
	#define EXP_iectaskdisablescheduling  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iectaskdisablescheduling
	#define EXT_iectaskdisablescheduling
	#define GET_iectaskdisablescheduling(fl)  CAL_CMGETAPI( "iectaskdisablescheduling" ) 
	#define CAL_iectaskdisablescheduling  iectaskdisablescheduling
	#define CHK_iectaskdisablescheduling  TRUE
	#define EXP_iectaskdisablescheduling  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskdisablescheduling", (RTS_UINTPTR)iectaskdisablescheduling, 1, 0xC3E3F168, 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_iectaskdisablescheduling
	#define EXT_iectaskdisablescheduling
	#define GET_iectaskdisablescheduling(fl)  CAL_CMGETAPI( "iectaskdisablescheduling" ) 
	#define CAL_iectaskdisablescheduling  iectaskdisablescheduling
	#define CHK_iectaskdisablescheduling  TRUE
	#define EXP_iectaskdisablescheduling  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskdisablescheduling", (RTS_UINTPTR)iectaskdisablescheduling, 1, 0xC3E3F168, 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskiectaskdisablescheduling
	#define EXT_CmpIecTaskiectaskdisablescheduling
	#define GET_CmpIecTaskiectaskdisablescheduling  ERR_OK
	#define CAL_CmpIecTaskiectaskdisablescheduling  iectaskdisablescheduling
	#define CHK_CmpIecTaskiectaskdisablescheduling  TRUE
	#define EXP_CmpIecTaskiectaskdisablescheduling  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskdisablescheduling", (RTS_UINTPTR)iectaskdisablescheduling, 1, 0xC3E3F168, 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iectaskdisablescheduling
	#define EXT_iectaskdisablescheduling
	#define GET_iectaskdisablescheduling(fl)  CAL_CMGETAPI( "iectaskdisablescheduling" ) 
	#define CAL_iectaskdisablescheduling  iectaskdisablescheduling
	#define CHK_iectaskdisablescheduling  TRUE
	#define EXP_iectaskdisablescheduling  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskdisablescheduling", (RTS_UINTPTR)iectaskdisablescheduling, 1, 0xC3E3F168, 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iectaskdisablescheduling  PFIECTASKDISABLESCHEDULING_IEC pfiectaskdisablescheduling;
	#define EXT_iectaskdisablescheduling  extern PFIECTASKDISABLESCHEDULING_IEC pfiectaskdisablescheduling;
	#define GET_iectaskdisablescheduling(fl)  s_pfCMGetAPI2( "iectaskdisablescheduling", (RTS_VOID_FCTPTR *)&pfiectaskdisablescheduling, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xC3E3F168, 0x03050800)
	#define CAL_iectaskdisablescheduling  pfiectaskdisablescheduling
	#define CHK_iectaskdisablescheduling  (pfiectaskdisablescheduling != NULL)
	#define EXP_iectaskdisablescheduling   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskdisablescheduling", (RTS_UINTPTR)iectaskdisablescheduling, 1, 0xC3E3F168, 0x03050800) 
#endif


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

void CDECL CDECL_EXT iectaskdisablewatchdog(iectaskdisablewatchdog_struct *p);
typedef void (CDECL CDECL_EXT* PFIECTASKDISABLEWATCHDOG_IEC) (iectaskdisablewatchdog_struct *p);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKDISABLEWATCHDOG_NOTIMPLEMENTED)
	#define USE_iectaskdisablewatchdog
	#define EXT_iectaskdisablewatchdog
	#define GET_iectaskdisablewatchdog(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iectaskdisablewatchdog(p0) 
	#define CHK_iectaskdisablewatchdog  FALSE
	#define EXP_iectaskdisablewatchdog  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iectaskdisablewatchdog
	#define EXT_iectaskdisablewatchdog
	#define GET_iectaskdisablewatchdog(fl)  CAL_CMGETAPI( "iectaskdisablewatchdog" ) 
	#define CAL_iectaskdisablewatchdog  iectaskdisablewatchdog
	#define CHK_iectaskdisablewatchdog  TRUE
	#define EXP_iectaskdisablewatchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskdisablewatchdog", (RTS_UINTPTR)iectaskdisablewatchdog, 1, RTSITF_GET_SIGNATURE(0, 0x2FF63495), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_iectaskdisablewatchdog
	#define EXT_iectaskdisablewatchdog
	#define GET_iectaskdisablewatchdog(fl)  CAL_CMGETAPI( "iectaskdisablewatchdog" ) 
	#define CAL_iectaskdisablewatchdog  iectaskdisablewatchdog
	#define CHK_iectaskdisablewatchdog  TRUE
	#define EXP_iectaskdisablewatchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskdisablewatchdog", (RTS_UINTPTR)iectaskdisablewatchdog, 1, RTSITF_GET_SIGNATURE(0, 0x2FF63495), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskiectaskdisablewatchdog
	#define EXT_CmpIecTaskiectaskdisablewatchdog
	#define GET_CmpIecTaskiectaskdisablewatchdog  ERR_OK
	#define CAL_CmpIecTaskiectaskdisablewatchdog  iectaskdisablewatchdog
	#define CHK_CmpIecTaskiectaskdisablewatchdog  TRUE
	#define EXP_CmpIecTaskiectaskdisablewatchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskdisablewatchdog", (RTS_UINTPTR)iectaskdisablewatchdog, 1, RTSITF_GET_SIGNATURE(0, 0x2FF63495), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iectaskdisablewatchdog
	#define EXT_iectaskdisablewatchdog
	#define GET_iectaskdisablewatchdog(fl)  CAL_CMGETAPI( "iectaskdisablewatchdog" ) 
	#define CAL_iectaskdisablewatchdog  iectaskdisablewatchdog
	#define CHK_iectaskdisablewatchdog  TRUE
	#define EXP_iectaskdisablewatchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskdisablewatchdog", (RTS_UINTPTR)iectaskdisablewatchdog, 1, RTSITF_GET_SIGNATURE(0, 0x2FF63495), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iectaskdisablewatchdog  PFIECTASKDISABLEWATCHDOG_IEC pfiectaskdisablewatchdog;
	#define EXT_iectaskdisablewatchdog  extern PFIECTASKDISABLEWATCHDOG_IEC pfiectaskdisablewatchdog;
	#define GET_iectaskdisablewatchdog(fl)  s_pfCMGetAPI2( "iectaskdisablewatchdog", (RTS_VOID_FCTPTR *)&pfiectaskdisablewatchdog, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x2FF63495), 0x03050800)
	#define CAL_iectaskdisablewatchdog  pfiectaskdisablewatchdog
	#define CHK_iectaskdisablewatchdog  (pfiectaskdisablewatchdog != NULL)
	#define EXP_iectaskdisablewatchdog   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskdisablewatchdog", (RTS_UINTPTR)iectaskdisablewatchdog, 1, RTSITF_GET_SIGNATURE(0, 0x2FF63495), 0x03050800) 
#endif


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

void CDECL CDECL_EXT iectaskdisablewatchdog2(iectaskdisablewatchdog2_struct *p);
typedef void (CDECL CDECL_EXT* PFIECTASKDISABLEWATCHDOG2_IEC) (iectaskdisablewatchdog2_struct *p);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKDISABLEWATCHDOG2_NOTIMPLEMENTED)
	#define USE_iectaskdisablewatchdog2
	#define EXT_iectaskdisablewatchdog2
	#define GET_iectaskdisablewatchdog2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iectaskdisablewatchdog2(p0) 
	#define CHK_iectaskdisablewatchdog2  FALSE
	#define EXP_iectaskdisablewatchdog2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iectaskdisablewatchdog2
	#define EXT_iectaskdisablewatchdog2
	#define GET_iectaskdisablewatchdog2(fl)  CAL_CMGETAPI( "iectaskdisablewatchdog2" ) 
	#define CAL_iectaskdisablewatchdog2  iectaskdisablewatchdog2
	#define CHK_iectaskdisablewatchdog2  TRUE
	#define EXP_iectaskdisablewatchdog2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskdisablewatchdog2", (RTS_UINTPTR)iectaskdisablewatchdog2, 1, 0x277BF3FE, 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_iectaskdisablewatchdog2
	#define EXT_iectaskdisablewatchdog2
	#define GET_iectaskdisablewatchdog2(fl)  CAL_CMGETAPI( "iectaskdisablewatchdog2" ) 
	#define CAL_iectaskdisablewatchdog2  iectaskdisablewatchdog2
	#define CHK_iectaskdisablewatchdog2  TRUE
	#define EXP_iectaskdisablewatchdog2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskdisablewatchdog2", (RTS_UINTPTR)iectaskdisablewatchdog2, 1, 0x277BF3FE, 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskiectaskdisablewatchdog2
	#define EXT_CmpIecTaskiectaskdisablewatchdog2
	#define GET_CmpIecTaskiectaskdisablewatchdog2  ERR_OK
	#define CAL_CmpIecTaskiectaskdisablewatchdog2  iectaskdisablewatchdog2
	#define CHK_CmpIecTaskiectaskdisablewatchdog2  TRUE
	#define EXP_CmpIecTaskiectaskdisablewatchdog2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskdisablewatchdog2", (RTS_UINTPTR)iectaskdisablewatchdog2, 1, 0x277BF3FE, 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iectaskdisablewatchdog2
	#define EXT_iectaskdisablewatchdog2
	#define GET_iectaskdisablewatchdog2(fl)  CAL_CMGETAPI( "iectaskdisablewatchdog2" ) 
	#define CAL_iectaskdisablewatchdog2  iectaskdisablewatchdog2
	#define CHK_iectaskdisablewatchdog2  TRUE
	#define EXP_iectaskdisablewatchdog2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskdisablewatchdog2", (RTS_UINTPTR)iectaskdisablewatchdog2, 1, 0x277BF3FE, 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iectaskdisablewatchdog2  PFIECTASKDISABLEWATCHDOG2_IEC pfiectaskdisablewatchdog2;
	#define EXT_iectaskdisablewatchdog2  extern PFIECTASKDISABLEWATCHDOG2_IEC pfiectaskdisablewatchdog2;
	#define GET_iectaskdisablewatchdog2(fl)  s_pfCMGetAPI2( "iectaskdisablewatchdog2", (RTS_VOID_FCTPTR *)&pfiectaskdisablewatchdog2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x277BF3FE, 0x03050800)
	#define CAL_iectaskdisablewatchdog2  pfiectaskdisablewatchdog2
	#define CHK_iectaskdisablewatchdog2  (pfiectaskdisablewatchdog2 != NULL)
	#define EXP_iectaskdisablewatchdog2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskdisablewatchdog2", (RTS_UINTPTR)iectaskdisablewatchdog2, 1, 0x277BF3FE, 0x03050800) 
#endif


/**
 * Enable scheduling for one specified task
 * :return: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagiectaskenablescheduling_struct
{
	RTS_IEC_HANDLE hIecTask;			/* VAR_INPUT */	/* Handle of the task */
	RTS_IEC_RESULT IecTaskEnableScheduling;	/* VAR_OUTPUT */	
} iectaskenablescheduling_struct;

void CDECL CDECL_EXT iectaskenablescheduling(iectaskenablescheduling_struct *p);
typedef void (CDECL CDECL_EXT* PFIECTASKENABLESCHEDULING_IEC) (iectaskenablescheduling_struct *p);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKENABLESCHEDULING_NOTIMPLEMENTED)
	#define USE_iectaskenablescheduling
	#define EXT_iectaskenablescheduling
	#define GET_iectaskenablescheduling(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iectaskenablescheduling(p0) 
	#define CHK_iectaskenablescheduling  FALSE
	#define EXP_iectaskenablescheduling  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iectaskenablescheduling
	#define EXT_iectaskenablescheduling
	#define GET_iectaskenablescheduling(fl)  CAL_CMGETAPI( "iectaskenablescheduling" ) 
	#define CAL_iectaskenablescheduling  iectaskenablescheduling
	#define CHK_iectaskenablescheduling  TRUE
	#define EXP_iectaskenablescheduling  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskenablescheduling", (RTS_UINTPTR)iectaskenablescheduling, 1, 0x4A96918C, 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_iectaskenablescheduling
	#define EXT_iectaskenablescheduling
	#define GET_iectaskenablescheduling(fl)  CAL_CMGETAPI( "iectaskenablescheduling" ) 
	#define CAL_iectaskenablescheduling  iectaskenablescheduling
	#define CHK_iectaskenablescheduling  TRUE
	#define EXP_iectaskenablescheduling  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskenablescheduling", (RTS_UINTPTR)iectaskenablescheduling, 1, 0x4A96918C, 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskiectaskenablescheduling
	#define EXT_CmpIecTaskiectaskenablescheduling
	#define GET_CmpIecTaskiectaskenablescheduling  ERR_OK
	#define CAL_CmpIecTaskiectaskenablescheduling  iectaskenablescheduling
	#define CHK_CmpIecTaskiectaskenablescheduling  TRUE
	#define EXP_CmpIecTaskiectaskenablescheduling  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskenablescheduling", (RTS_UINTPTR)iectaskenablescheduling, 1, 0x4A96918C, 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iectaskenablescheduling
	#define EXT_iectaskenablescheduling
	#define GET_iectaskenablescheduling(fl)  CAL_CMGETAPI( "iectaskenablescheduling" ) 
	#define CAL_iectaskenablescheduling  iectaskenablescheduling
	#define CHK_iectaskenablescheduling  TRUE
	#define EXP_iectaskenablescheduling  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskenablescheduling", (RTS_UINTPTR)iectaskenablescheduling, 1, 0x4A96918C, 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iectaskenablescheduling  PFIECTASKENABLESCHEDULING_IEC pfiectaskenablescheduling;
	#define EXT_iectaskenablescheduling  extern PFIECTASKENABLESCHEDULING_IEC pfiectaskenablescheduling;
	#define GET_iectaskenablescheduling(fl)  s_pfCMGetAPI2( "iectaskenablescheduling", (RTS_VOID_FCTPTR *)&pfiectaskenablescheduling, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x4A96918C, 0x03050800)
	#define CAL_iectaskenablescheduling  pfiectaskenablescheduling
	#define CHK_iectaskenablescheduling  (pfiectaskenablescheduling != NULL)
	#define EXP_iectaskenablescheduling   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskenablescheduling", (RTS_UINTPTR)iectaskenablescheduling, 1, 0x4A96918C, 0x03050800) 
#endif


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

void CDECL CDECL_EXT iectaskenablewatchdog(iectaskenablewatchdog_struct *p);
typedef void (CDECL CDECL_EXT* PFIECTASKENABLEWATCHDOG_IEC) (iectaskenablewatchdog_struct *p);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKENABLEWATCHDOG_NOTIMPLEMENTED)
	#define USE_iectaskenablewatchdog
	#define EXT_iectaskenablewatchdog
	#define GET_iectaskenablewatchdog(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iectaskenablewatchdog(p0) 
	#define CHK_iectaskenablewatchdog  FALSE
	#define EXP_iectaskenablewatchdog  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iectaskenablewatchdog
	#define EXT_iectaskenablewatchdog
	#define GET_iectaskenablewatchdog(fl)  CAL_CMGETAPI( "iectaskenablewatchdog" ) 
	#define CAL_iectaskenablewatchdog  iectaskenablewatchdog
	#define CHK_iectaskenablewatchdog  TRUE
	#define EXP_iectaskenablewatchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskenablewatchdog", (RTS_UINTPTR)iectaskenablewatchdog, 1, RTSITF_GET_SIGNATURE(0, 0x1CDBB730), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_iectaskenablewatchdog
	#define EXT_iectaskenablewatchdog
	#define GET_iectaskenablewatchdog(fl)  CAL_CMGETAPI( "iectaskenablewatchdog" ) 
	#define CAL_iectaskenablewatchdog  iectaskenablewatchdog
	#define CHK_iectaskenablewatchdog  TRUE
	#define EXP_iectaskenablewatchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskenablewatchdog", (RTS_UINTPTR)iectaskenablewatchdog, 1, RTSITF_GET_SIGNATURE(0, 0x1CDBB730), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskiectaskenablewatchdog
	#define EXT_CmpIecTaskiectaskenablewatchdog
	#define GET_CmpIecTaskiectaskenablewatchdog  ERR_OK
	#define CAL_CmpIecTaskiectaskenablewatchdog  iectaskenablewatchdog
	#define CHK_CmpIecTaskiectaskenablewatchdog  TRUE
	#define EXP_CmpIecTaskiectaskenablewatchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskenablewatchdog", (RTS_UINTPTR)iectaskenablewatchdog, 1, RTSITF_GET_SIGNATURE(0, 0x1CDBB730), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iectaskenablewatchdog
	#define EXT_iectaskenablewatchdog
	#define GET_iectaskenablewatchdog(fl)  CAL_CMGETAPI( "iectaskenablewatchdog" ) 
	#define CAL_iectaskenablewatchdog  iectaskenablewatchdog
	#define CHK_iectaskenablewatchdog  TRUE
	#define EXP_iectaskenablewatchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskenablewatchdog", (RTS_UINTPTR)iectaskenablewatchdog, 1, RTSITF_GET_SIGNATURE(0, 0x1CDBB730), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iectaskenablewatchdog  PFIECTASKENABLEWATCHDOG_IEC pfiectaskenablewatchdog;
	#define EXT_iectaskenablewatchdog  extern PFIECTASKENABLEWATCHDOG_IEC pfiectaskenablewatchdog;
	#define GET_iectaskenablewatchdog(fl)  s_pfCMGetAPI2( "iectaskenablewatchdog", (RTS_VOID_FCTPTR *)&pfiectaskenablewatchdog, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x1CDBB730), 0x03050800)
	#define CAL_iectaskenablewatchdog  pfiectaskenablewatchdog
	#define CHK_iectaskenablewatchdog  (pfiectaskenablewatchdog != NULL)
	#define EXP_iectaskenablewatchdog   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskenablewatchdog", (RTS_UINTPTR)iectaskenablewatchdog, 1, RTSITF_GET_SIGNATURE(0, 0x1CDBB730), 0x03050800) 
#endif


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

void CDECL CDECL_EXT iectaskenablewatchdog2(iectaskenablewatchdog2_struct *p);
typedef void (CDECL CDECL_EXT* PFIECTASKENABLEWATCHDOG2_IEC) (iectaskenablewatchdog2_struct *p);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKENABLEWATCHDOG2_NOTIMPLEMENTED)
	#define USE_iectaskenablewatchdog2
	#define EXT_iectaskenablewatchdog2
	#define GET_iectaskenablewatchdog2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iectaskenablewatchdog2(p0) 
	#define CHK_iectaskenablewatchdog2  FALSE
	#define EXP_iectaskenablewatchdog2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iectaskenablewatchdog2
	#define EXT_iectaskenablewatchdog2
	#define GET_iectaskenablewatchdog2(fl)  CAL_CMGETAPI( "iectaskenablewatchdog2" ) 
	#define CAL_iectaskenablewatchdog2  iectaskenablewatchdog2
	#define CHK_iectaskenablewatchdog2  TRUE
	#define EXP_iectaskenablewatchdog2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskenablewatchdog2", (RTS_UINTPTR)iectaskenablewatchdog2, 1, 0xE71D232F, 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_iectaskenablewatchdog2
	#define EXT_iectaskenablewatchdog2
	#define GET_iectaskenablewatchdog2(fl)  CAL_CMGETAPI( "iectaskenablewatchdog2" ) 
	#define CAL_iectaskenablewatchdog2  iectaskenablewatchdog2
	#define CHK_iectaskenablewatchdog2  TRUE
	#define EXP_iectaskenablewatchdog2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskenablewatchdog2", (RTS_UINTPTR)iectaskenablewatchdog2, 1, 0xE71D232F, 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskiectaskenablewatchdog2
	#define EXT_CmpIecTaskiectaskenablewatchdog2
	#define GET_CmpIecTaskiectaskenablewatchdog2  ERR_OK
	#define CAL_CmpIecTaskiectaskenablewatchdog2  iectaskenablewatchdog2
	#define CHK_CmpIecTaskiectaskenablewatchdog2  TRUE
	#define EXP_CmpIecTaskiectaskenablewatchdog2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskenablewatchdog2", (RTS_UINTPTR)iectaskenablewatchdog2, 1, 0xE71D232F, 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iectaskenablewatchdog2
	#define EXT_iectaskenablewatchdog2
	#define GET_iectaskenablewatchdog2(fl)  CAL_CMGETAPI( "iectaskenablewatchdog2" ) 
	#define CAL_iectaskenablewatchdog2  iectaskenablewatchdog2
	#define CHK_iectaskenablewatchdog2  TRUE
	#define EXP_iectaskenablewatchdog2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskenablewatchdog2", (RTS_UINTPTR)iectaskenablewatchdog2, 1, 0xE71D232F, 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iectaskenablewatchdog2  PFIECTASKENABLEWATCHDOG2_IEC pfiectaskenablewatchdog2;
	#define EXT_iectaskenablewatchdog2  extern PFIECTASKENABLEWATCHDOG2_IEC pfiectaskenablewatchdog2;
	#define GET_iectaskenablewatchdog2(fl)  s_pfCMGetAPI2( "iectaskenablewatchdog2", (RTS_VOID_FCTPTR *)&pfiectaskenablewatchdog2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xE71D232F, 0x03050800)
	#define CAL_iectaskenablewatchdog2  pfiectaskenablewatchdog2
	#define CHK_iectaskenablewatchdog2  (pfiectaskenablewatchdog2 != NULL)
	#define EXP_iectaskenablewatchdog2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskenablewatchdog2", (RTS_UINTPTR)iectaskenablewatchdog2, 1, 0xE71D232F, 0x03050800) 
#endif


/**
 * Funktion to get own task handle
 * :return: Returns the current IEC task handle
 */
typedef struct tagiectaskgetcurrent_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer that returns the runtime system error code (see CmpErrors.library) */
	RTS_IEC_HANDLE IecTaskGetCurrent;	/* VAR_OUTPUT */	
} iectaskgetcurrent_struct;

void CDECL CDECL_EXT iectaskgetcurrent(iectaskgetcurrent_struct *p);
typedef void (CDECL CDECL_EXT* PFIECTASKGETCURRENT_IEC) (iectaskgetcurrent_struct *p);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKGETCURRENT_NOTIMPLEMENTED)
	#define USE_iectaskgetcurrent
	#define EXT_iectaskgetcurrent
	#define GET_iectaskgetcurrent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iectaskgetcurrent(p0) 
	#define CHK_iectaskgetcurrent  FALSE
	#define EXP_iectaskgetcurrent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iectaskgetcurrent
	#define EXT_iectaskgetcurrent
	#define GET_iectaskgetcurrent(fl)  CAL_CMGETAPI( "iectaskgetcurrent" ) 
	#define CAL_iectaskgetcurrent  iectaskgetcurrent
	#define CHK_iectaskgetcurrent  TRUE
	#define EXP_iectaskgetcurrent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetcurrent", (RTS_UINTPTR)iectaskgetcurrent, 1, RTSITF_GET_SIGNATURE(0, 0xFD44B5CC), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_iectaskgetcurrent
	#define EXT_iectaskgetcurrent
	#define GET_iectaskgetcurrent(fl)  CAL_CMGETAPI( "iectaskgetcurrent" ) 
	#define CAL_iectaskgetcurrent  iectaskgetcurrent
	#define CHK_iectaskgetcurrent  TRUE
	#define EXP_iectaskgetcurrent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetcurrent", (RTS_UINTPTR)iectaskgetcurrent, 1, RTSITF_GET_SIGNATURE(0, 0xFD44B5CC), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskiectaskgetcurrent
	#define EXT_CmpIecTaskiectaskgetcurrent
	#define GET_CmpIecTaskiectaskgetcurrent  ERR_OK
	#define CAL_CmpIecTaskiectaskgetcurrent  iectaskgetcurrent
	#define CHK_CmpIecTaskiectaskgetcurrent  TRUE
	#define EXP_CmpIecTaskiectaskgetcurrent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetcurrent", (RTS_UINTPTR)iectaskgetcurrent, 1, RTSITF_GET_SIGNATURE(0, 0xFD44B5CC), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iectaskgetcurrent
	#define EXT_iectaskgetcurrent
	#define GET_iectaskgetcurrent(fl)  CAL_CMGETAPI( "iectaskgetcurrent" ) 
	#define CAL_iectaskgetcurrent  iectaskgetcurrent
	#define CHK_iectaskgetcurrent  TRUE
	#define EXP_iectaskgetcurrent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetcurrent", (RTS_UINTPTR)iectaskgetcurrent, 1, RTSITF_GET_SIGNATURE(0, 0xFD44B5CC), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iectaskgetcurrent  PFIECTASKGETCURRENT_IEC pfiectaskgetcurrent;
	#define EXT_iectaskgetcurrent  extern PFIECTASKGETCURRENT_IEC pfiectaskgetcurrent;
	#define GET_iectaskgetcurrent(fl)  s_pfCMGetAPI2( "iectaskgetcurrent", (RTS_VOID_FCTPTR *)&pfiectaskgetcurrent, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xFD44B5CC), 0x03050800)
	#define CAL_iectaskgetcurrent  pfiectaskgetcurrent
	#define CHK_iectaskgetcurrent  (pfiectaskgetcurrent != NULL)
	#define EXP_iectaskgetcurrent   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetcurrent", (RTS_UINTPTR)iectaskgetcurrent, 1, RTSITF_GET_SIGNATURE(0, 0xFD44B5CC), 0x03050800) 
#endif


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

void CDECL CDECL_EXT iectaskgetfirst(iectaskgetfirst_struct *p);
typedef void (CDECL CDECL_EXT* PFIECTASKGETFIRST_IEC) (iectaskgetfirst_struct *p);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKGETFIRST_NOTIMPLEMENTED)
	#define USE_iectaskgetfirst
	#define EXT_iectaskgetfirst
	#define GET_iectaskgetfirst(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iectaskgetfirst(p0) 
	#define CHK_iectaskgetfirst  FALSE
	#define EXP_iectaskgetfirst  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iectaskgetfirst
	#define EXT_iectaskgetfirst
	#define GET_iectaskgetfirst(fl)  CAL_CMGETAPI( "iectaskgetfirst" ) 
	#define CAL_iectaskgetfirst  iectaskgetfirst
	#define CHK_iectaskgetfirst  TRUE
	#define EXP_iectaskgetfirst  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetfirst", (RTS_UINTPTR)iectaskgetfirst, 1, RTSITF_GET_SIGNATURE(0, 0xD65D1BF9), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_iectaskgetfirst
	#define EXT_iectaskgetfirst
	#define GET_iectaskgetfirst(fl)  CAL_CMGETAPI( "iectaskgetfirst" ) 
	#define CAL_iectaskgetfirst  iectaskgetfirst
	#define CHK_iectaskgetfirst  TRUE
	#define EXP_iectaskgetfirst  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetfirst", (RTS_UINTPTR)iectaskgetfirst, 1, RTSITF_GET_SIGNATURE(0, 0xD65D1BF9), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskiectaskgetfirst
	#define EXT_CmpIecTaskiectaskgetfirst
	#define GET_CmpIecTaskiectaskgetfirst  ERR_OK
	#define CAL_CmpIecTaskiectaskgetfirst  iectaskgetfirst
	#define CHK_CmpIecTaskiectaskgetfirst  TRUE
	#define EXP_CmpIecTaskiectaskgetfirst  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetfirst", (RTS_UINTPTR)iectaskgetfirst, 1, RTSITF_GET_SIGNATURE(0, 0xD65D1BF9), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iectaskgetfirst
	#define EXT_iectaskgetfirst
	#define GET_iectaskgetfirst(fl)  CAL_CMGETAPI( "iectaskgetfirst" ) 
	#define CAL_iectaskgetfirst  iectaskgetfirst
	#define CHK_iectaskgetfirst  TRUE
	#define EXP_iectaskgetfirst  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetfirst", (RTS_UINTPTR)iectaskgetfirst, 1, RTSITF_GET_SIGNATURE(0, 0xD65D1BF9), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iectaskgetfirst  PFIECTASKGETFIRST_IEC pfiectaskgetfirst;
	#define EXT_iectaskgetfirst  extern PFIECTASKGETFIRST_IEC pfiectaskgetfirst;
	#define GET_iectaskgetfirst(fl)  s_pfCMGetAPI2( "iectaskgetfirst", (RTS_VOID_FCTPTR *)&pfiectaskgetfirst, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xD65D1BF9), 0x03050800)
	#define CAL_iectaskgetfirst  pfiectaskgetfirst
	#define CHK_iectaskgetfirst  (pfiectaskgetfirst != NULL)
	#define EXP_iectaskgetfirst   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetfirst", (RTS_UINTPTR)iectaskgetfirst, 1, RTSITF_GET_SIGNATURE(0, 0xD65D1BF9), 0x03050800) 
#endif


/**
 * OBSOLETE FUNCTION
 */
typedef struct tagiectaskgetinfo2_struct
{
	RTS_IEC_HANDLE hIecTask;			/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	Task_Info *IecTaskGetInfo2;			/* VAR_OUTPUT */	
} iectaskgetinfo2_struct;

void CDECL CDECL_EXT iectaskgetinfo2(iectaskgetinfo2_struct *p);
typedef void (CDECL CDECL_EXT* PFIECTASKGETINFO2_IEC) (iectaskgetinfo2_struct *p);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKGETINFO2_NOTIMPLEMENTED)
	#define USE_iectaskgetinfo2
	#define EXT_iectaskgetinfo2
	#define GET_iectaskgetinfo2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iectaskgetinfo2(p0) 
	#define CHK_iectaskgetinfo2  FALSE
	#define EXP_iectaskgetinfo2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iectaskgetinfo2
	#define EXT_iectaskgetinfo2
	#define GET_iectaskgetinfo2(fl)  CAL_CMGETAPI( "iectaskgetinfo2" ) 
	#define CAL_iectaskgetinfo2  iectaskgetinfo2
	#define CHK_iectaskgetinfo2  TRUE
	#define EXP_iectaskgetinfo2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetinfo2", (RTS_UINTPTR)iectaskgetinfo2, 1, RTSITF_GET_SIGNATURE(0, 0x2A6E9BE6), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_iectaskgetinfo2
	#define EXT_iectaskgetinfo2
	#define GET_iectaskgetinfo2(fl)  CAL_CMGETAPI( "iectaskgetinfo2" ) 
	#define CAL_iectaskgetinfo2  iectaskgetinfo2
	#define CHK_iectaskgetinfo2  TRUE
	#define EXP_iectaskgetinfo2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetinfo2", (RTS_UINTPTR)iectaskgetinfo2, 1, RTSITF_GET_SIGNATURE(0, 0x2A6E9BE6), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskiectaskgetinfo2
	#define EXT_CmpIecTaskiectaskgetinfo2
	#define GET_CmpIecTaskiectaskgetinfo2  ERR_OK
	#define CAL_CmpIecTaskiectaskgetinfo2  iectaskgetinfo2
	#define CHK_CmpIecTaskiectaskgetinfo2  TRUE
	#define EXP_CmpIecTaskiectaskgetinfo2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetinfo2", (RTS_UINTPTR)iectaskgetinfo2, 1, RTSITF_GET_SIGNATURE(0, 0x2A6E9BE6), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iectaskgetinfo2
	#define EXT_iectaskgetinfo2
	#define GET_iectaskgetinfo2(fl)  CAL_CMGETAPI( "iectaskgetinfo2" ) 
	#define CAL_iectaskgetinfo2  iectaskgetinfo2
	#define CHK_iectaskgetinfo2  TRUE
	#define EXP_iectaskgetinfo2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetinfo2", (RTS_UINTPTR)iectaskgetinfo2, 1, RTSITF_GET_SIGNATURE(0, 0x2A6E9BE6), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iectaskgetinfo2  PFIECTASKGETINFO2_IEC pfiectaskgetinfo2;
	#define EXT_iectaskgetinfo2  extern PFIECTASKGETINFO2_IEC pfiectaskgetinfo2;
	#define GET_iectaskgetinfo2(fl)  s_pfCMGetAPI2( "iectaskgetinfo2", (RTS_VOID_FCTPTR *)&pfiectaskgetinfo2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x2A6E9BE6), 0x03050800)
	#define CAL_iectaskgetinfo2  pfiectaskgetinfo2
	#define CHK_iectaskgetinfo2  (pfiectaskgetinfo2 != NULL)
	#define EXP_iectaskgetinfo2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetinfo2", (RTS_UINTPTR)iectaskgetinfo2, 1, RTSITF_GET_SIGNATURE(0, 0x2A6E9BE6), 0x03050800) 
#endif


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

void CDECL CDECL_EXT iectaskgetnext(iectaskgetnext_struct *p);
typedef void (CDECL CDECL_EXT* PFIECTASKGETNEXT_IEC) (iectaskgetnext_struct *p);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKGETNEXT_NOTIMPLEMENTED)
	#define USE_iectaskgetnext
	#define EXT_iectaskgetnext
	#define GET_iectaskgetnext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iectaskgetnext(p0) 
	#define CHK_iectaskgetnext  FALSE
	#define EXP_iectaskgetnext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iectaskgetnext
	#define EXT_iectaskgetnext
	#define GET_iectaskgetnext(fl)  CAL_CMGETAPI( "iectaskgetnext" ) 
	#define CAL_iectaskgetnext  iectaskgetnext
	#define CHK_iectaskgetnext  TRUE
	#define EXP_iectaskgetnext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetnext", (RTS_UINTPTR)iectaskgetnext, 1, RTSITF_GET_SIGNATURE(0, 0xC2306FF5), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_iectaskgetnext
	#define EXT_iectaskgetnext
	#define GET_iectaskgetnext(fl)  CAL_CMGETAPI( "iectaskgetnext" ) 
	#define CAL_iectaskgetnext  iectaskgetnext
	#define CHK_iectaskgetnext  TRUE
	#define EXP_iectaskgetnext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetnext", (RTS_UINTPTR)iectaskgetnext, 1, RTSITF_GET_SIGNATURE(0, 0xC2306FF5), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskiectaskgetnext
	#define EXT_CmpIecTaskiectaskgetnext
	#define GET_CmpIecTaskiectaskgetnext  ERR_OK
	#define CAL_CmpIecTaskiectaskgetnext  iectaskgetnext
	#define CHK_CmpIecTaskiectaskgetnext  TRUE
	#define EXP_CmpIecTaskiectaskgetnext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetnext", (RTS_UINTPTR)iectaskgetnext, 1, RTSITF_GET_SIGNATURE(0, 0xC2306FF5), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iectaskgetnext
	#define EXT_iectaskgetnext
	#define GET_iectaskgetnext(fl)  CAL_CMGETAPI( "iectaskgetnext" ) 
	#define CAL_iectaskgetnext  iectaskgetnext
	#define CHK_iectaskgetnext  TRUE
	#define EXP_iectaskgetnext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetnext", (RTS_UINTPTR)iectaskgetnext, 1, RTSITF_GET_SIGNATURE(0, 0xC2306FF5), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iectaskgetnext  PFIECTASKGETNEXT_IEC pfiectaskgetnext;
	#define EXT_iectaskgetnext  extern PFIECTASKGETNEXT_IEC pfiectaskgetnext;
	#define GET_iectaskgetnext(fl)  s_pfCMGetAPI2( "iectaskgetnext", (RTS_VOID_FCTPTR *)&pfiectaskgetnext, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xC2306FF5), 0x03050800)
	#define CAL_iectaskgetnext  pfiectaskgetnext
	#define CHK_iectaskgetnext  (pfiectaskgetnext != NULL)
	#define EXP_iectaskgetnext   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetnext", (RTS_UINTPTR)iectaskgetnext, 1, RTSITF_GET_SIGNATURE(0, 0xC2306FF5), 0x03050800) 
#endif


/**
 * <description>iectaskgetprofiling</description>
 */
typedef struct tagiectaskgetprofiling_struct
{
	RTS_IEC_BOOL IecTaskGetProfiling;	/* VAR_OUTPUT */	
} iectaskgetprofiling_struct;

void CDECL CDECL_EXT iectaskgetprofiling(iectaskgetprofiling_struct *p);
typedef void (CDECL CDECL_EXT* PFIECTASKGETPROFILING_IEC) (iectaskgetprofiling_struct *p);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKGETPROFILING_NOTIMPLEMENTED)
	#define USE_iectaskgetprofiling
	#define EXT_iectaskgetprofiling
	#define GET_iectaskgetprofiling(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iectaskgetprofiling(p0) 
	#define CHK_iectaskgetprofiling  FALSE
	#define EXP_iectaskgetprofiling  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iectaskgetprofiling
	#define EXT_iectaskgetprofiling
	#define GET_iectaskgetprofiling(fl)  CAL_CMGETAPI( "iectaskgetprofiling" ) 
	#define CAL_iectaskgetprofiling  iectaskgetprofiling
	#define CHK_iectaskgetprofiling  TRUE
	#define EXP_iectaskgetprofiling  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetprofiling", (RTS_UINTPTR)iectaskgetprofiling, 1, RTSITF_GET_SIGNATURE(0, 0x217F24B2), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_iectaskgetprofiling
	#define EXT_iectaskgetprofiling
	#define GET_iectaskgetprofiling(fl)  CAL_CMGETAPI( "iectaskgetprofiling" ) 
	#define CAL_iectaskgetprofiling  iectaskgetprofiling
	#define CHK_iectaskgetprofiling  TRUE
	#define EXP_iectaskgetprofiling  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetprofiling", (RTS_UINTPTR)iectaskgetprofiling, 1, RTSITF_GET_SIGNATURE(0, 0x217F24B2), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskiectaskgetprofiling
	#define EXT_CmpIecTaskiectaskgetprofiling
	#define GET_CmpIecTaskiectaskgetprofiling  ERR_OK
	#define CAL_CmpIecTaskiectaskgetprofiling  iectaskgetprofiling
	#define CHK_CmpIecTaskiectaskgetprofiling  TRUE
	#define EXP_CmpIecTaskiectaskgetprofiling  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetprofiling", (RTS_UINTPTR)iectaskgetprofiling, 1, RTSITF_GET_SIGNATURE(0, 0x217F24B2), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iectaskgetprofiling
	#define EXT_iectaskgetprofiling
	#define GET_iectaskgetprofiling(fl)  CAL_CMGETAPI( "iectaskgetprofiling" ) 
	#define CAL_iectaskgetprofiling  iectaskgetprofiling
	#define CHK_iectaskgetprofiling  TRUE
	#define EXP_iectaskgetprofiling  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetprofiling", (RTS_UINTPTR)iectaskgetprofiling, 1, RTSITF_GET_SIGNATURE(0, 0x217F24B2), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iectaskgetprofiling  PFIECTASKGETPROFILING_IEC pfiectaskgetprofiling;
	#define EXT_iectaskgetprofiling  extern PFIECTASKGETPROFILING_IEC pfiectaskgetprofiling;
	#define GET_iectaskgetprofiling(fl)  s_pfCMGetAPI2( "iectaskgetprofiling", (RTS_VOID_FCTPTR *)&pfiectaskgetprofiling, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x217F24B2), 0x03050800)
	#define CAL_iectaskgetprofiling  pfiectaskgetprofiling
	#define CHK_iectaskgetprofiling  (pfiectaskgetprofiling != NULL)
	#define EXP_iectaskgetprofiling   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskgetprofiling", (RTS_UINTPTR)iectaskgetprofiling, 1, RTSITF_GET_SIGNATURE(0, 0x217F24B2), 0x03050800) 
#endif


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

void CDECL CDECL_EXT iectaskreload(iectaskreload_struct *p);
typedef void (CDECL CDECL_EXT* PFIECTASKRELOAD_IEC) (iectaskreload_struct *p);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKRELOAD_NOTIMPLEMENTED)
	#define USE_iectaskreload
	#define EXT_iectaskreload
	#define GET_iectaskreload(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iectaskreload(p0) 
	#define CHK_iectaskreload  FALSE
	#define EXP_iectaskreload  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iectaskreload
	#define EXT_iectaskreload
	#define GET_iectaskreload(fl)  CAL_CMGETAPI( "iectaskreload" ) 
	#define CAL_iectaskreload  iectaskreload
	#define CHK_iectaskreload  TRUE
	#define EXP_iectaskreload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskreload", (RTS_UINTPTR)iectaskreload, 1, 0x796FC828, 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_iectaskreload
	#define EXT_iectaskreload
	#define GET_iectaskreload(fl)  CAL_CMGETAPI( "iectaskreload" ) 
	#define CAL_iectaskreload  iectaskreload
	#define CHK_iectaskreload  TRUE
	#define EXP_iectaskreload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskreload", (RTS_UINTPTR)iectaskreload, 1, 0x796FC828, 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskiectaskreload
	#define EXT_CmpIecTaskiectaskreload
	#define GET_CmpIecTaskiectaskreload  ERR_OK
	#define CAL_CmpIecTaskiectaskreload  iectaskreload
	#define CHK_CmpIecTaskiectaskreload  TRUE
	#define EXP_CmpIecTaskiectaskreload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskreload", (RTS_UINTPTR)iectaskreload, 1, 0x796FC828, 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iectaskreload
	#define EXT_iectaskreload
	#define GET_iectaskreload(fl)  CAL_CMGETAPI( "iectaskreload" ) 
	#define CAL_iectaskreload  iectaskreload
	#define CHK_iectaskreload  TRUE
	#define EXP_iectaskreload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskreload", (RTS_UINTPTR)iectaskreload, 1, 0x796FC828, 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iectaskreload  PFIECTASKRELOAD_IEC pfiectaskreload;
	#define EXT_iectaskreload  extern PFIECTASKRELOAD_IEC pfiectaskreload;
	#define GET_iectaskreload(fl)  s_pfCMGetAPI2( "iectaskreload", (RTS_VOID_FCTPTR *)&pfiectaskreload, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x796FC828, 0x03050800)
	#define CAL_iectaskreload  pfiectaskreload
	#define CHK_iectaskreload  (pfiectaskreload != NULL)
	#define EXP_iectaskreload   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskreload", (RTS_UINTPTR)iectaskreload, 1, 0x796FC828, 0x03050800) 
#endif


/**
 * Reset the task statistics of a task (see Task_Info member e.g. dwCycleTime, dwAverageCycleTime, etc.)
 * :return: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagiectaskresetstatistics_struct
{
	RTS_IEC_HANDLE hIecTask;			/* VAR_INPUT */	/* Handle of the task */
	RTS_IEC_RESULT IecTaskResetStatistics;	/* VAR_OUTPUT */	
} iectaskresetstatistics_struct;

void CDECL CDECL_EXT iectaskresetstatistics(iectaskresetstatistics_struct *p);
typedef void (CDECL CDECL_EXT* PFIECTASKRESETSTATISTICS_IEC) (iectaskresetstatistics_struct *p);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKRESETSTATISTICS_NOTIMPLEMENTED)
	#define USE_iectaskresetstatistics
	#define EXT_iectaskresetstatistics
	#define GET_iectaskresetstatistics(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iectaskresetstatistics(p0) 
	#define CHK_iectaskresetstatistics  FALSE
	#define EXP_iectaskresetstatistics  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iectaskresetstatistics
	#define EXT_iectaskresetstatistics
	#define GET_iectaskresetstatistics(fl)  CAL_CMGETAPI( "iectaskresetstatistics" ) 
	#define CAL_iectaskresetstatistics  iectaskresetstatistics
	#define CHK_iectaskresetstatistics  TRUE
	#define EXP_iectaskresetstatistics  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskresetstatistics", (RTS_UINTPTR)iectaskresetstatistics, 1, 0x6291DC5B, 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_iectaskresetstatistics
	#define EXT_iectaskresetstatistics
	#define GET_iectaskresetstatistics(fl)  CAL_CMGETAPI( "iectaskresetstatistics" ) 
	#define CAL_iectaskresetstatistics  iectaskresetstatistics
	#define CHK_iectaskresetstatistics  TRUE
	#define EXP_iectaskresetstatistics  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskresetstatistics", (RTS_UINTPTR)iectaskresetstatistics, 1, 0x6291DC5B, 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskiectaskresetstatistics
	#define EXT_CmpIecTaskiectaskresetstatistics
	#define GET_CmpIecTaskiectaskresetstatistics  ERR_OK
	#define CAL_CmpIecTaskiectaskresetstatistics  iectaskresetstatistics
	#define CHK_CmpIecTaskiectaskresetstatistics  TRUE
	#define EXP_CmpIecTaskiectaskresetstatistics  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskresetstatistics", (RTS_UINTPTR)iectaskresetstatistics, 1, 0x6291DC5B, 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iectaskresetstatistics
	#define EXT_iectaskresetstatistics
	#define GET_iectaskresetstatistics(fl)  CAL_CMGETAPI( "iectaskresetstatistics" ) 
	#define CAL_iectaskresetstatistics  iectaskresetstatistics
	#define CHK_iectaskresetstatistics  TRUE
	#define EXP_iectaskresetstatistics  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskresetstatistics", (RTS_UINTPTR)iectaskresetstatistics, 1, 0x6291DC5B, 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iectaskresetstatistics  PFIECTASKRESETSTATISTICS_IEC pfiectaskresetstatistics;
	#define EXT_iectaskresetstatistics  extern PFIECTASKRESETSTATISTICS_IEC pfiectaskresetstatistics;
	#define GET_iectaskresetstatistics(fl)  s_pfCMGetAPI2( "iectaskresetstatistics", (RTS_VOID_FCTPTR *)&pfiectaskresetstatistics, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x6291DC5B, 0x03050800)
	#define CAL_iectaskresetstatistics  pfiectaskresetstatistics
	#define CHK_iectaskresetstatistics  (pfiectaskresetstatistics != NULL)
	#define EXP_iectaskresetstatistics   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iectaskresetstatistics", (RTS_UINTPTR)iectaskresetstatistics, 1, 0x6291DC5B, 0x03050800) 
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
RTS_HANDLE CDECL IecTaskCreate(APPLICATION *pApp, Task_Info *pTaskInfo, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECTASKCREATE) (APPLICATION *pApp, Task_Info *pTaskInfo, RTS_RESULT *pResult);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKCREATE_NOTIMPLEMENTED)
	#define USE_IecTaskCreate
	#define EXT_IecTaskCreate
	#define GET_IecTaskCreate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskCreate(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecTaskCreate  FALSE
	#define EXP_IecTaskCreate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskCreate
	#define EXT_IecTaskCreate
	#define GET_IecTaskCreate(fl)  CAL_CMGETAPI( "IecTaskCreate" ) 
	#define CAL_IecTaskCreate  IecTaskCreate
	#define CHK_IecTaskCreate  TRUE
	#define EXP_IecTaskCreate  CAL_CMEXPAPI( "IecTaskCreate" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskCreate
	#define EXT_IecTaskCreate
	#define GET_IecTaskCreate(fl)  CAL_CMGETAPI( "IecTaskCreate" ) 
	#define CAL_IecTaskCreate  IecTaskCreate
	#define CHK_IecTaskCreate  TRUE
	#define EXP_IecTaskCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskCreate", (RTS_UINTPTR)IecTaskCreate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskCreate
	#define EXT_CmpIecTaskIecTaskCreate
	#define GET_CmpIecTaskIecTaskCreate  ERR_OK
	#define CAL_CmpIecTaskIecTaskCreate  ((ICmpIecTask*)s_pfCMCreateInstance(CLASSID_CCmpIecTask, NULL))->IIecTaskCreate
	#define CHK_CmpIecTaskIecTaskCreate	(s_pfCMCreateInstance != NULL && pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskCreate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskCreate
	#define EXT_IecTaskCreate
	#define GET_IecTaskCreate(fl)  CAL_CMGETAPI( "IecTaskCreate" ) 
	#define CAL_IecTaskCreate  ((ICmpIecTask*)s_pfCMCreateInstance(CLASSID_CCmpIecTask, NULL))->IIecTaskCreate
	#define CHK_IecTaskCreate	(s_pfCMCreateInstance != NULL && pICmpIecTask != NULL)
	#define EXP_IecTaskCreate  CAL_CMEXPAPI( "IecTaskCreate" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskCreate  PFIECTASKCREATE pfIecTaskCreate;
	#define EXT_IecTaskCreate  extern PFIECTASKCREATE pfIecTaskCreate;
	#define GET_IecTaskCreate(fl)  s_pfCMGetAPI2( "IecTaskCreate", (RTS_VOID_FCTPTR *)&pfIecTaskCreate, (fl), 0, 0)
	#define CAL_IecTaskCreate  pfIecTaskCreate
	#define CHK_IecTaskCreate  (pfIecTaskCreate != NULL)
	#define EXP_IecTaskCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskCreate", (RTS_UINTPTR)IecTaskCreate, 0, 0) 
#endif




/**
 * <description> Delete an IEC task </description>
 * <param name="hIecTask" type="IN">Handle to task</param>
 * <result>Error code</result>
 */
RTS_RESULT CDECL IecTaskDelete(RTS_HANDLE hIecTask);
typedef RTS_RESULT (CDECL * PFIECTASKDELETE) (RTS_HANDLE hIecTask);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKDELETE_NOTIMPLEMENTED)
	#define USE_IecTaskDelete
	#define EXT_IecTaskDelete
	#define GET_IecTaskDelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskDelete(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskDelete  FALSE
	#define EXP_IecTaskDelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskDelete
	#define EXT_IecTaskDelete
	#define GET_IecTaskDelete(fl)  CAL_CMGETAPI( "IecTaskDelete" ) 
	#define CAL_IecTaskDelete  IecTaskDelete
	#define CHK_IecTaskDelete  TRUE
	#define EXP_IecTaskDelete  CAL_CMEXPAPI( "IecTaskDelete" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskDelete
	#define EXT_IecTaskDelete
	#define GET_IecTaskDelete(fl)  CAL_CMGETAPI( "IecTaskDelete" ) 
	#define CAL_IecTaskDelete  IecTaskDelete
	#define CHK_IecTaskDelete  TRUE
	#define EXP_IecTaskDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskDelete", (RTS_UINTPTR)IecTaskDelete, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskDelete
	#define EXT_CmpIecTaskIecTaskDelete
	#define GET_CmpIecTaskIecTaskDelete  ERR_OK
	#define CAL_CmpIecTaskIecTaskDelete(p0) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ICmpIecTask*)p0)->IIecTaskDelete())
	#define CHK_CmpIecTaskIecTaskDelete  TRUE
	#define EXP_CmpIecTaskIecTaskDelete  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskDelete
	#define EXT_IecTaskDelete
	#define GET_IecTaskDelete(fl)  CAL_CMGETAPI( "IecTaskDelete" ) 
	#define CAL_IecTaskDelete(p0) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ICmpIecTask*)p0)->IIecTaskDelete())
	#define CHK_IecTaskDelete  TRUE
	#define EXP_IecTaskDelete  CAL_CMEXPAPI( "IecTaskDelete" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskDelete  PFIECTASKDELETE pfIecTaskDelete;
	#define EXT_IecTaskDelete  extern PFIECTASKDELETE pfIecTaskDelete;
	#define GET_IecTaskDelete(fl)  s_pfCMGetAPI2( "IecTaskDelete", (RTS_VOID_FCTPTR *)&pfIecTaskDelete, (fl), 0, 0)
	#define CAL_IecTaskDelete  pfIecTaskDelete
	#define CHK_IecTaskDelete  (pfIecTaskDelete != NULL)
	#define EXP_IecTaskDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskDelete", (RTS_UINTPTR)IecTaskDelete, 0, 0) 
#endif




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
RTS_RESULT CDECL IecTaskDelete2(RTS_HANDLE hIecTask, RTS_UI32 ulTimeoutMs);
typedef RTS_RESULT (CDECL * PFIECTASKDELETE2) (RTS_HANDLE hIecTask, RTS_UI32 ulTimeoutMs);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKDELETE2_NOTIMPLEMENTED)
	#define USE_IecTaskDelete2
	#define EXT_IecTaskDelete2
	#define GET_IecTaskDelete2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskDelete2(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskDelete2  FALSE
	#define EXP_IecTaskDelete2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskDelete2
	#define EXT_IecTaskDelete2
	#define GET_IecTaskDelete2(fl)  CAL_CMGETAPI( "IecTaskDelete2" ) 
	#define CAL_IecTaskDelete2  IecTaskDelete2
	#define CHK_IecTaskDelete2  TRUE
	#define EXP_IecTaskDelete2  CAL_CMEXPAPI( "IecTaskDelete2" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskDelete2
	#define EXT_IecTaskDelete2
	#define GET_IecTaskDelete2(fl)  CAL_CMGETAPI( "IecTaskDelete2" ) 
	#define CAL_IecTaskDelete2  IecTaskDelete2
	#define CHK_IecTaskDelete2  TRUE
	#define EXP_IecTaskDelete2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskDelete2", (RTS_UINTPTR)IecTaskDelete2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskDelete2
	#define EXT_CmpIecTaskIecTaskDelete2
	#define GET_CmpIecTaskIecTaskDelete2  ERR_OK
	#define CAL_CmpIecTaskIecTaskDelete2(p0,p1) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ICmpIecTask*)p0)->IIecTaskDelete2(p1))
	#define CHK_CmpIecTaskIecTaskDelete2  TRUE
	#define EXP_CmpIecTaskIecTaskDelete2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskDelete2
	#define EXT_IecTaskDelete2
	#define GET_IecTaskDelete2(fl)  CAL_CMGETAPI( "IecTaskDelete2" ) 
	#define CAL_IecTaskDelete2(p0,p1) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ICmpIecTask*)p0)->IIecTaskDelete2(p1))
	#define CHK_IecTaskDelete2  TRUE
	#define EXP_IecTaskDelete2  CAL_CMEXPAPI( "IecTaskDelete2" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskDelete2  PFIECTASKDELETE2 pfIecTaskDelete2;
	#define EXT_IecTaskDelete2  extern PFIECTASKDELETE2 pfIecTaskDelete2;
	#define GET_IecTaskDelete2(fl)  s_pfCMGetAPI2( "IecTaskDelete2", (RTS_VOID_FCTPTR *)&pfIecTaskDelete2, (fl), 0, 0)
	#define CAL_IecTaskDelete2  pfIecTaskDelete2
	#define CHK_IecTaskDelete2  (pfIecTaskDelete2 != NULL)
	#define EXP_IecTaskDelete2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskDelete2", (RTS_UINTPTR)IecTaskDelete2, 0, 0) 
#endif




/**
 * <description> Frees all IEC tasks </description>
 * <param name="pApp" type="IN">Pointer to specified application</param>
 * <result>Error code</result>
 */
RTS_RESULT CDECL IecFreeTasks(APPLICATION *pApp);
typedef RTS_RESULT (CDECL * PFIECFREETASKS) (APPLICATION *pApp);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECFREETASKS_NOTIMPLEMENTED)
	#define USE_IecFreeTasks
	#define EXT_IecFreeTasks
	#define GET_IecFreeTasks(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecFreeTasks(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecFreeTasks  FALSE
	#define EXP_IecFreeTasks  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecFreeTasks
	#define EXT_IecFreeTasks
	#define GET_IecFreeTasks(fl)  CAL_CMGETAPI( "IecFreeTasks" ) 
	#define CAL_IecFreeTasks  IecFreeTasks
	#define CHK_IecFreeTasks  TRUE
	#define EXP_IecFreeTasks  CAL_CMEXPAPI( "IecFreeTasks" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecFreeTasks
	#define EXT_IecFreeTasks
	#define GET_IecFreeTasks(fl)  CAL_CMGETAPI( "IecFreeTasks" ) 
	#define CAL_IecFreeTasks  IecFreeTasks
	#define CHK_IecFreeTasks  TRUE
	#define EXP_IecFreeTasks  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecFreeTasks", (RTS_UINTPTR)IecFreeTasks, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecFreeTasks
	#define EXT_CmpIecTaskIecFreeTasks
	#define GET_CmpIecTaskIecFreeTasks  ERR_OK
	#define CAL_CmpIecTaskIecFreeTasks pICmpIecTask->IIecFreeTasks
	#define CHK_CmpIecTaskIecFreeTasks (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecFreeTasks  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecFreeTasks
	#define EXT_IecFreeTasks
	#define GET_IecFreeTasks(fl)  CAL_CMGETAPI( "IecFreeTasks" ) 
	#define CAL_IecFreeTasks pICmpIecTask->IIecFreeTasks
	#define CHK_IecFreeTasks (pICmpIecTask != NULL)
	#define EXP_IecFreeTasks  CAL_CMEXPAPI( "IecFreeTasks" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecFreeTasks  PFIECFREETASKS pfIecFreeTasks;
	#define EXT_IecFreeTasks  extern PFIECFREETASKS pfIecFreeTasks;
	#define GET_IecFreeTasks(fl)  s_pfCMGetAPI2( "IecFreeTasks", (RTS_VOID_FCTPTR *)&pfIecFreeTasks, (fl), 0, 0)
	#define CAL_IecFreeTasks  pfIecFreeTasks
	#define CHK_IecFreeTasks  (pfIecFreeTasks != NULL)
	#define EXP_IecFreeTasks  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecFreeTasks", (RTS_UINTPTR)IecFreeTasks, 0, 0) 
#endif




/**
 * <description> Frees all IEC tasks </description>
 * <param name="pApp" type="IN">Pointer to specified application</param>
 * <param name="ulTimeoutMs" type="IN">Timeout in milliseconds to release the tasks. RTS_TIMEOUT_DEFAULT can be used as the default value</param>
 * <result>Error code</result>
 */
RTS_RESULT CDECL IecFreeTasks2(APPLICATION *pApp, RTS_UI32 ulTimeoutMs);
typedef RTS_RESULT (CDECL * PFIECFREETASKS2) (APPLICATION *pApp, RTS_UI32 ulTimeoutMs);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECFREETASKS2_NOTIMPLEMENTED)
	#define USE_IecFreeTasks2
	#define EXT_IecFreeTasks2
	#define GET_IecFreeTasks2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecFreeTasks2(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecFreeTasks2  FALSE
	#define EXP_IecFreeTasks2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecFreeTasks2
	#define EXT_IecFreeTasks2
	#define GET_IecFreeTasks2(fl)  CAL_CMGETAPI( "IecFreeTasks2" ) 
	#define CAL_IecFreeTasks2  IecFreeTasks2
	#define CHK_IecFreeTasks2  TRUE
	#define EXP_IecFreeTasks2  CAL_CMEXPAPI( "IecFreeTasks2" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecFreeTasks2
	#define EXT_IecFreeTasks2
	#define GET_IecFreeTasks2(fl)  CAL_CMGETAPI( "IecFreeTasks2" ) 
	#define CAL_IecFreeTasks2  IecFreeTasks2
	#define CHK_IecFreeTasks2  TRUE
	#define EXP_IecFreeTasks2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecFreeTasks2", (RTS_UINTPTR)IecFreeTasks2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecFreeTasks2
	#define EXT_CmpIecTaskIecFreeTasks2
	#define GET_CmpIecTaskIecFreeTasks2  ERR_OK
	#define CAL_CmpIecTaskIecFreeTasks2 pICmpIecTask->IIecFreeTasks2
	#define CHK_CmpIecTaskIecFreeTasks2 (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecFreeTasks2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecFreeTasks2
	#define EXT_IecFreeTasks2
	#define GET_IecFreeTasks2(fl)  CAL_CMGETAPI( "IecFreeTasks2" ) 
	#define CAL_IecFreeTasks2 pICmpIecTask->IIecFreeTasks2
	#define CHK_IecFreeTasks2 (pICmpIecTask != NULL)
	#define EXP_IecFreeTasks2  CAL_CMEXPAPI( "IecFreeTasks2" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecFreeTasks2  PFIECFREETASKS2 pfIecFreeTasks2;
	#define EXT_IecFreeTasks2  extern PFIECFREETASKS2 pfIecFreeTasks2;
	#define GET_IecFreeTasks2(fl)  s_pfCMGetAPI2( "IecFreeTasks2", (RTS_VOID_FCTPTR *)&pfIecFreeTasks2, (fl), 0, 0)
	#define CAL_IecFreeTasks2  pfIecFreeTasks2
	#define CHK_IecFreeTasks2  (pfIecFreeTasks2 != NULL)
	#define EXP_IecFreeTasks2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecFreeTasks2", (RTS_UINTPTR)IecFreeTasks2, 0, 0) 
#endif




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
RTS_RESULT CDECL IecTaskCycle(Task_Desc* pTask);
typedef RTS_RESULT (CDECL * PFIECTASKCYCLE) (Task_Desc* pTask);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKCYCLE_NOTIMPLEMENTED)
	#define USE_IecTaskCycle
	#define EXT_IecTaskCycle
	#define GET_IecTaskCycle(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskCycle(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskCycle  FALSE
	#define EXP_IecTaskCycle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskCycle
	#define EXT_IecTaskCycle
	#define GET_IecTaskCycle(fl)  CAL_CMGETAPI( "IecTaskCycle" ) 
	#define CAL_IecTaskCycle  IecTaskCycle
	#define CHK_IecTaskCycle  TRUE
	#define EXP_IecTaskCycle  CAL_CMEXPAPI( "IecTaskCycle" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskCycle
	#define EXT_IecTaskCycle
	#define GET_IecTaskCycle(fl)  CAL_CMGETAPI( "IecTaskCycle" ) 
	#define CAL_IecTaskCycle  IecTaskCycle
	#define CHK_IecTaskCycle  TRUE
	#define EXP_IecTaskCycle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskCycle", (RTS_UINTPTR)IecTaskCycle, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskCycle
	#define EXT_CmpIecTaskIecTaskCycle
	#define GET_CmpIecTaskIecTaskCycle  ERR_OK
	#define CAL_CmpIecTaskIecTaskCycle pICmpIecTask->IIecTaskCycle
	#define CHK_CmpIecTaskIecTaskCycle (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskCycle  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskCycle
	#define EXT_IecTaskCycle
	#define GET_IecTaskCycle(fl)  CAL_CMGETAPI( "IecTaskCycle" ) 
	#define CAL_IecTaskCycle pICmpIecTask->IIecTaskCycle
	#define CHK_IecTaskCycle (pICmpIecTask != NULL)
	#define EXP_IecTaskCycle  CAL_CMEXPAPI( "IecTaskCycle" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskCycle  PFIECTASKCYCLE pfIecTaskCycle;
	#define EXT_IecTaskCycle  extern PFIECTASKCYCLE pfIecTaskCycle;
	#define GET_IecTaskCycle(fl)  s_pfCMGetAPI2( "IecTaskCycle", (RTS_VOID_FCTPTR *)&pfIecTaskCycle, (fl), 0, 0)
	#define CAL_IecTaskCycle  pfIecTaskCycle
	#define CHK_IecTaskCycle  (pfIecTaskCycle != NULL)
	#define EXP_IecTaskCycle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskCycle", (RTS_UINTPTR)IecTaskCycle, 0, 0) 
#endif




/**
 * <description> Calculate jitter time of task </description>
 * <param name="pTask" type="IN">Pointer to task description</param>
 * <param name="ptNow" type="IN">Pointer to actual microsecond time tick</param>
 * <result>Error code</result>
 */
RTS_RESULT CDECL IecTaskUpdateJitterTime(Task_Desc* pTask, RTS_SYSTIME *ptNow);
typedef RTS_RESULT (CDECL * PFIECTASKUPDATEJITTERTIME) (Task_Desc* pTask, RTS_SYSTIME *ptNow);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKUPDATEJITTERTIME_NOTIMPLEMENTED)
	#define USE_IecTaskUpdateJitterTime
	#define EXT_IecTaskUpdateJitterTime
	#define GET_IecTaskUpdateJitterTime(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskUpdateJitterTime(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskUpdateJitterTime  FALSE
	#define EXP_IecTaskUpdateJitterTime  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskUpdateJitterTime
	#define EXT_IecTaskUpdateJitterTime
	#define GET_IecTaskUpdateJitterTime(fl)  CAL_CMGETAPI( "IecTaskUpdateJitterTime" ) 
	#define CAL_IecTaskUpdateJitterTime  IecTaskUpdateJitterTime
	#define CHK_IecTaskUpdateJitterTime  TRUE
	#define EXP_IecTaskUpdateJitterTime  CAL_CMEXPAPI( "IecTaskUpdateJitterTime" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskUpdateJitterTime
	#define EXT_IecTaskUpdateJitterTime
	#define GET_IecTaskUpdateJitterTime(fl)  CAL_CMGETAPI( "IecTaskUpdateJitterTime" ) 
	#define CAL_IecTaskUpdateJitterTime  IecTaskUpdateJitterTime
	#define CHK_IecTaskUpdateJitterTime  TRUE
	#define EXP_IecTaskUpdateJitterTime  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskUpdateJitterTime", (RTS_UINTPTR)IecTaskUpdateJitterTime, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskUpdateJitterTime
	#define EXT_CmpIecTaskIecTaskUpdateJitterTime
	#define GET_CmpIecTaskIecTaskUpdateJitterTime  ERR_OK
	#define CAL_CmpIecTaskIecTaskUpdateJitterTime pICmpIecTask->IIecTaskUpdateJitterTime
	#define CHK_CmpIecTaskIecTaskUpdateJitterTime (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskUpdateJitterTime  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskUpdateJitterTime
	#define EXT_IecTaskUpdateJitterTime
	#define GET_IecTaskUpdateJitterTime(fl)  CAL_CMGETAPI( "IecTaskUpdateJitterTime" ) 
	#define CAL_IecTaskUpdateJitterTime pICmpIecTask->IIecTaskUpdateJitterTime
	#define CHK_IecTaskUpdateJitterTime (pICmpIecTask != NULL)
	#define EXP_IecTaskUpdateJitterTime  CAL_CMEXPAPI( "IecTaskUpdateJitterTime" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskUpdateJitterTime  PFIECTASKUPDATEJITTERTIME pfIecTaskUpdateJitterTime;
	#define EXT_IecTaskUpdateJitterTime  extern PFIECTASKUPDATEJITTERTIME pfIecTaskUpdateJitterTime;
	#define GET_IecTaskUpdateJitterTime(fl)  s_pfCMGetAPI2( "IecTaskUpdateJitterTime", (RTS_VOID_FCTPTR *)&pfIecTaskUpdateJitterTime, (fl), 0, 0)
	#define CAL_IecTaskUpdateJitterTime  pfIecTaskUpdateJitterTime
	#define CHK_IecTaskUpdateJitterTime  (pfIecTaskUpdateJitterTime != NULL)
	#define EXP_IecTaskUpdateJitterTime  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskUpdateJitterTime", (RTS_UINTPTR)IecTaskUpdateJitterTime, 0, 0) 
#endif




/**
 * <description>Calculate cycle time of task.</description>
 * <param name="pTask" type="IN" range="[NULL,VALID_TASK]">Pointer to task description</param> 
 * <param name="ptActUs" type="IN" range="[ACT_TIME]">Pointer to actual time tick in microseconds</param>
 * <parampseudo name="bIgnoreWatchdogInCycle" type="IN" range="[TRUE,FALSE]">Ignore watchdog in cycle</parampseudo>
 * <result>Error code</result>
 */
RTS_RESULT CDECL IecTaskUpdateCycleTime(Task_Desc* pTask, RTS_SYSTIME *ptActUs);
typedef RTS_RESULT (CDECL * PFIECTASKUPDATECYCLETIME) (Task_Desc* pTask, RTS_SYSTIME *ptActUs);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKUPDATECYCLETIME_NOTIMPLEMENTED)
	#define USE_IecTaskUpdateCycleTime
	#define EXT_IecTaskUpdateCycleTime
	#define GET_IecTaskUpdateCycleTime(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskUpdateCycleTime(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskUpdateCycleTime  FALSE
	#define EXP_IecTaskUpdateCycleTime  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskUpdateCycleTime
	#define EXT_IecTaskUpdateCycleTime
	#define GET_IecTaskUpdateCycleTime(fl)  CAL_CMGETAPI( "IecTaskUpdateCycleTime" ) 
	#define CAL_IecTaskUpdateCycleTime  IecTaskUpdateCycleTime
	#define CHK_IecTaskUpdateCycleTime  TRUE
	#define EXP_IecTaskUpdateCycleTime  CAL_CMEXPAPI( "IecTaskUpdateCycleTime" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskUpdateCycleTime
	#define EXT_IecTaskUpdateCycleTime
	#define GET_IecTaskUpdateCycleTime(fl)  CAL_CMGETAPI( "IecTaskUpdateCycleTime" ) 
	#define CAL_IecTaskUpdateCycleTime  IecTaskUpdateCycleTime
	#define CHK_IecTaskUpdateCycleTime  TRUE
	#define EXP_IecTaskUpdateCycleTime  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskUpdateCycleTime", (RTS_UINTPTR)IecTaskUpdateCycleTime, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskUpdateCycleTime
	#define EXT_CmpIecTaskIecTaskUpdateCycleTime
	#define GET_CmpIecTaskIecTaskUpdateCycleTime  ERR_OK
	#define CAL_CmpIecTaskIecTaskUpdateCycleTime pICmpIecTask->IIecTaskUpdateCycleTime
	#define CHK_CmpIecTaskIecTaskUpdateCycleTime (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskUpdateCycleTime  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskUpdateCycleTime
	#define EXT_IecTaskUpdateCycleTime
	#define GET_IecTaskUpdateCycleTime(fl)  CAL_CMGETAPI( "IecTaskUpdateCycleTime" ) 
	#define CAL_IecTaskUpdateCycleTime pICmpIecTask->IIecTaskUpdateCycleTime
	#define CHK_IecTaskUpdateCycleTime (pICmpIecTask != NULL)
	#define EXP_IecTaskUpdateCycleTime  CAL_CMEXPAPI( "IecTaskUpdateCycleTime" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskUpdateCycleTime  PFIECTASKUPDATECYCLETIME pfIecTaskUpdateCycleTime;
	#define EXT_IecTaskUpdateCycleTime  extern PFIECTASKUPDATECYCLETIME pfIecTaskUpdateCycleTime;
	#define GET_IecTaskUpdateCycleTime(fl)  s_pfCMGetAPI2( "IecTaskUpdateCycleTime", (RTS_VOID_FCTPTR *)&pfIecTaskUpdateCycleTime, (fl), 0, 0)
	#define CAL_IecTaskUpdateCycleTime  pfIecTaskUpdateCycleTime
	#define CHK_IecTaskUpdateCycleTime  (pfIecTaskUpdateCycleTime != NULL)
	#define EXP_IecTaskUpdateCycleTime  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskUpdateCycleTime", (RTS_UINTPTR)IecTaskUpdateCycleTime, 0, 0) 
#endif




/**
 * <description> FUnction to check, if reset is allowed in the actual state on this application </description>
 * <param name="pApp" type="IN">Pointer to specified application</param>
 * <result>ERR_OK: Reset allowed, ERR_NOT_SUPPORTED: Not allowed (e.g. if one task is halted on a breakpoint)</result>
 */
RTS_RESULT CDECL IecTasksResetAllowed(APPLICATION *pApp);
typedef RTS_RESULT (CDECL * PFIECTASKSRESETALLOWED) (APPLICATION *pApp);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKSRESETALLOWED_NOTIMPLEMENTED)
	#define USE_IecTasksResetAllowed
	#define EXT_IecTasksResetAllowed
	#define GET_IecTasksResetAllowed(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTasksResetAllowed(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTasksResetAllowed  FALSE
	#define EXP_IecTasksResetAllowed  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTasksResetAllowed
	#define EXT_IecTasksResetAllowed
	#define GET_IecTasksResetAllowed(fl)  CAL_CMGETAPI( "IecTasksResetAllowed" ) 
	#define CAL_IecTasksResetAllowed  IecTasksResetAllowed
	#define CHK_IecTasksResetAllowed  TRUE
	#define EXP_IecTasksResetAllowed  CAL_CMEXPAPI( "IecTasksResetAllowed" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTasksResetAllowed
	#define EXT_IecTasksResetAllowed
	#define GET_IecTasksResetAllowed(fl)  CAL_CMGETAPI( "IecTasksResetAllowed" ) 
	#define CAL_IecTasksResetAllowed  IecTasksResetAllowed
	#define CHK_IecTasksResetAllowed  TRUE
	#define EXP_IecTasksResetAllowed  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTasksResetAllowed", (RTS_UINTPTR)IecTasksResetAllowed, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTasksResetAllowed
	#define EXT_CmpIecTaskIecTasksResetAllowed
	#define GET_CmpIecTaskIecTasksResetAllowed  ERR_OK
	#define CAL_CmpIecTaskIecTasksResetAllowed pICmpIecTask->IIecTasksResetAllowed
	#define CHK_CmpIecTaskIecTasksResetAllowed (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTasksResetAllowed  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTasksResetAllowed
	#define EXT_IecTasksResetAllowed
	#define GET_IecTasksResetAllowed(fl)  CAL_CMGETAPI( "IecTasksResetAllowed" ) 
	#define CAL_IecTasksResetAllowed pICmpIecTask->IIecTasksResetAllowed
	#define CHK_IecTasksResetAllowed (pICmpIecTask != NULL)
	#define EXP_IecTasksResetAllowed  CAL_CMEXPAPI( "IecTasksResetAllowed" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTasksResetAllowed  PFIECTASKSRESETALLOWED pfIecTasksResetAllowed;
	#define EXT_IecTasksResetAllowed  extern PFIECTASKSRESETALLOWED pfIecTasksResetAllowed;
	#define GET_IecTasksResetAllowed(fl)  s_pfCMGetAPI2( "IecTasksResetAllowed", (RTS_VOID_FCTPTR *)&pfIecTasksResetAllowed, (fl), 0, 0)
	#define CAL_IecTasksResetAllowed  pfIecTasksResetAllowed
	#define CHK_IecTasksResetAllowed  (pfIecTasksResetAllowed != NULL)
	#define EXP_IecTasksResetAllowed  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTasksResetAllowed", (RTS_UINTPTR)IecTasksResetAllowed, 0, 0) 
#endif




/**
 * <description> Prepare reset for all IEC tasks specified by application </description>
 * <param name="pApp" type="IN">Pointer to specified application</param>
 * <result>Error code</result>
 */
RTS_RESULT CDECL IecTasksPrepareReset(APPLICATION *pApp, int bResetOrigin);
typedef RTS_RESULT (CDECL * PFIECTASKSPREPARERESET) (APPLICATION *pApp, int bResetOrigin);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKSPREPARERESET_NOTIMPLEMENTED)
	#define USE_IecTasksPrepareReset
	#define EXT_IecTasksPrepareReset
	#define GET_IecTasksPrepareReset(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTasksPrepareReset(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTasksPrepareReset  FALSE
	#define EXP_IecTasksPrepareReset  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTasksPrepareReset
	#define EXT_IecTasksPrepareReset
	#define GET_IecTasksPrepareReset(fl)  CAL_CMGETAPI( "IecTasksPrepareReset" ) 
	#define CAL_IecTasksPrepareReset  IecTasksPrepareReset
	#define CHK_IecTasksPrepareReset  TRUE
	#define EXP_IecTasksPrepareReset  CAL_CMEXPAPI( "IecTasksPrepareReset" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTasksPrepareReset
	#define EXT_IecTasksPrepareReset
	#define GET_IecTasksPrepareReset(fl)  CAL_CMGETAPI( "IecTasksPrepareReset" ) 
	#define CAL_IecTasksPrepareReset  IecTasksPrepareReset
	#define CHK_IecTasksPrepareReset  TRUE
	#define EXP_IecTasksPrepareReset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTasksPrepareReset", (RTS_UINTPTR)IecTasksPrepareReset, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTasksPrepareReset
	#define EXT_CmpIecTaskIecTasksPrepareReset
	#define GET_CmpIecTaskIecTasksPrepareReset  ERR_OK
	#define CAL_CmpIecTaskIecTasksPrepareReset pICmpIecTask->IIecTasksPrepareReset
	#define CHK_CmpIecTaskIecTasksPrepareReset (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTasksPrepareReset  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTasksPrepareReset
	#define EXT_IecTasksPrepareReset
	#define GET_IecTasksPrepareReset(fl)  CAL_CMGETAPI( "IecTasksPrepareReset" ) 
	#define CAL_IecTasksPrepareReset pICmpIecTask->IIecTasksPrepareReset
	#define CHK_IecTasksPrepareReset (pICmpIecTask != NULL)
	#define EXP_IecTasksPrepareReset  CAL_CMEXPAPI( "IecTasksPrepareReset" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTasksPrepareReset  PFIECTASKSPREPARERESET pfIecTasksPrepareReset;
	#define EXT_IecTasksPrepareReset  extern PFIECTASKSPREPARERESET pfIecTasksPrepareReset;
	#define GET_IecTasksPrepareReset(fl)  s_pfCMGetAPI2( "IecTasksPrepareReset", (RTS_VOID_FCTPTR *)&pfIecTasksPrepareReset, (fl), 0, 0)
	#define CAL_IecTasksPrepareReset  pfIecTasksPrepareReset
	#define CHK_IecTasksPrepareReset  (pfIecTasksPrepareReset != NULL)
	#define EXP_IecTasksPrepareReset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTasksPrepareReset", (RTS_UINTPTR)IecTasksPrepareReset, 0, 0) 
#endif




/**
 * <description> Initialize all IEC tasks after reset specified by application </description>
 * <param name="pApp" type="IN">Pointer to specified application</param>
 * <result>Error code</result>
 */
RTS_RESULT CDECL IecTasksResetDone(APPLICATION *pApp, int bResetOrigin);
typedef RTS_RESULT (CDECL * PFIECTASKSRESETDONE) (APPLICATION *pApp, int bResetOrigin);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKSRESETDONE_NOTIMPLEMENTED)
	#define USE_IecTasksResetDone
	#define EXT_IecTasksResetDone
	#define GET_IecTasksResetDone(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTasksResetDone(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTasksResetDone  FALSE
	#define EXP_IecTasksResetDone  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTasksResetDone
	#define EXT_IecTasksResetDone
	#define GET_IecTasksResetDone(fl)  CAL_CMGETAPI( "IecTasksResetDone" ) 
	#define CAL_IecTasksResetDone  IecTasksResetDone
	#define CHK_IecTasksResetDone  TRUE
	#define EXP_IecTasksResetDone  CAL_CMEXPAPI( "IecTasksResetDone" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTasksResetDone
	#define EXT_IecTasksResetDone
	#define GET_IecTasksResetDone(fl)  CAL_CMGETAPI( "IecTasksResetDone" ) 
	#define CAL_IecTasksResetDone  IecTasksResetDone
	#define CHK_IecTasksResetDone  TRUE
	#define EXP_IecTasksResetDone  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTasksResetDone", (RTS_UINTPTR)IecTasksResetDone, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTasksResetDone
	#define EXT_CmpIecTaskIecTasksResetDone
	#define GET_CmpIecTaskIecTasksResetDone  ERR_OK
	#define CAL_CmpIecTaskIecTasksResetDone pICmpIecTask->IIecTasksResetDone
	#define CHK_CmpIecTaskIecTasksResetDone (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTasksResetDone  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTasksResetDone
	#define EXT_IecTasksResetDone
	#define GET_IecTasksResetDone(fl)  CAL_CMGETAPI( "IecTasksResetDone" ) 
	#define CAL_IecTasksResetDone pICmpIecTask->IIecTasksResetDone
	#define CHK_IecTasksResetDone (pICmpIecTask != NULL)
	#define EXP_IecTasksResetDone  CAL_CMEXPAPI( "IecTasksResetDone" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTasksResetDone  PFIECTASKSRESETDONE pfIecTasksResetDone;
	#define EXT_IecTasksResetDone  extern PFIECTASKSRESETDONE pfIecTasksResetDone;
	#define GET_IecTasksResetDone(fl)  s_pfCMGetAPI2( "IecTasksResetDone", (RTS_VOID_FCTPTR *)&pfIecTasksResetDone, (fl), 0, 0)
	#define CAL_IecTasksResetDone  pfIecTasksResetDone
	#define CHK_IecTasksResetDone  (pfIecTasksResetDone != NULL)
	#define EXP_IecTasksResetDone  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTasksResetDone", (RTS_UINTPTR)IecTasksResetDone, 0, 0) 
#endif




/**
 * <description>Get the calculated timeout to wait for stop for specified application</description>
 * <param name="pApp" type="IN">Pointer to specified application</param>
 * <param name="pResult" type="OUT">Result of operation</param>
 * <errorcode name="pResult" type="ERR_OK">Timeout has been calculated successfully</errorcode>
 * <errorcode name="pResult" type="ERR_PARAMETER">Application is not valid</errorcode>
 * <result>calculated timeout</result>
 */
RTS_UI32 CDECL IecTaskGetWaitForStopTimeout(APPLICATION *pApp, RTS_RESULT *pResult);
typedef RTS_UI32 (CDECL * PFIECTASKGETWAITFORSTOPTIMEOUT) (APPLICATION *pApp, RTS_RESULT *pResult);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKGETWAITFORSTOPTIMEOUT_NOTIMPLEMENTED)
	#define USE_IecTaskGetWaitForStopTimeout
	#define EXT_IecTaskGetWaitForStopTimeout
	#define GET_IecTaskGetWaitForStopTimeout(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskGetWaitForStopTimeout(p0,p1)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskGetWaitForStopTimeout  FALSE
	#define EXP_IecTaskGetWaitForStopTimeout  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskGetWaitForStopTimeout
	#define EXT_IecTaskGetWaitForStopTimeout
	#define GET_IecTaskGetWaitForStopTimeout(fl)  CAL_CMGETAPI( "IecTaskGetWaitForStopTimeout" ) 
	#define CAL_IecTaskGetWaitForStopTimeout  IecTaskGetWaitForStopTimeout
	#define CHK_IecTaskGetWaitForStopTimeout  TRUE
	#define EXP_IecTaskGetWaitForStopTimeout  CAL_CMEXPAPI( "IecTaskGetWaitForStopTimeout" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskGetWaitForStopTimeout
	#define EXT_IecTaskGetWaitForStopTimeout
	#define GET_IecTaskGetWaitForStopTimeout(fl)  CAL_CMGETAPI( "IecTaskGetWaitForStopTimeout" ) 
	#define CAL_IecTaskGetWaitForStopTimeout  IecTaskGetWaitForStopTimeout
	#define CHK_IecTaskGetWaitForStopTimeout  TRUE
	#define EXP_IecTaskGetWaitForStopTimeout  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetWaitForStopTimeout", (RTS_UINTPTR)IecTaskGetWaitForStopTimeout, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskGetWaitForStopTimeout
	#define EXT_CmpIecTaskIecTaskGetWaitForStopTimeout
	#define GET_CmpIecTaskIecTaskGetWaitForStopTimeout  ERR_OK
	#define CAL_CmpIecTaskIecTaskGetWaitForStopTimeout pICmpIecTask->IIecTaskGetWaitForStopTimeout
	#define CHK_CmpIecTaskIecTaskGetWaitForStopTimeout (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskGetWaitForStopTimeout  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskGetWaitForStopTimeout
	#define EXT_IecTaskGetWaitForStopTimeout
	#define GET_IecTaskGetWaitForStopTimeout(fl)  CAL_CMGETAPI( "IecTaskGetWaitForStopTimeout" ) 
	#define CAL_IecTaskGetWaitForStopTimeout pICmpIecTask->IIecTaskGetWaitForStopTimeout
	#define CHK_IecTaskGetWaitForStopTimeout (pICmpIecTask != NULL)
	#define EXP_IecTaskGetWaitForStopTimeout  CAL_CMEXPAPI( "IecTaskGetWaitForStopTimeout" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskGetWaitForStopTimeout  PFIECTASKGETWAITFORSTOPTIMEOUT pfIecTaskGetWaitForStopTimeout;
	#define EXT_IecTaskGetWaitForStopTimeout  extern PFIECTASKGETWAITFORSTOPTIMEOUT pfIecTaskGetWaitForStopTimeout;
	#define GET_IecTaskGetWaitForStopTimeout(fl)  s_pfCMGetAPI2( "IecTaskGetWaitForStopTimeout", (RTS_VOID_FCTPTR *)&pfIecTaskGetWaitForStopTimeout, (fl), 0, 0)
	#define CAL_IecTaskGetWaitForStopTimeout  pfIecTaskGetWaitForStopTimeout
	#define CHK_IecTaskGetWaitForStopTimeout  (pfIecTaskGetWaitForStopTimeout != NULL)
	#define EXP_IecTaskGetWaitForStopTimeout  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetWaitForStopTimeout", (RTS_UINTPTR)IecTaskGetWaitForStopTimeout, 0, 0) 
#endif




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
RTS_RESULT CDECL IecTasksWaitForStop(APPLICATION *pApp, RTS_UI32 ulTimeoutMs, unsigned long ulStopReason);
typedef RTS_RESULT (CDECL * PFIECTASKSWAITFORSTOP) (APPLICATION *pApp, RTS_UI32 ulTimeoutMs, unsigned long ulStopReason);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKSWAITFORSTOP_NOTIMPLEMENTED)
	#define USE_IecTasksWaitForStop
	#define EXT_IecTasksWaitForStop
	#define GET_IecTasksWaitForStop(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTasksWaitForStop(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTasksWaitForStop  FALSE
	#define EXP_IecTasksWaitForStop  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTasksWaitForStop
	#define EXT_IecTasksWaitForStop
	#define GET_IecTasksWaitForStop(fl)  CAL_CMGETAPI( "IecTasksWaitForStop" ) 
	#define CAL_IecTasksWaitForStop  IecTasksWaitForStop
	#define CHK_IecTasksWaitForStop  TRUE
	#define EXP_IecTasksWaitForStop  CAL_CMEXPAPI( "IecTasksWaitForStop" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTasksWaitForStop
	#define EXT_IecTasksWaitForStop
	#define GET_IecTasksWaitForStop(fl)  CAL_CMGETAPI( "IecTasksWaitForStop" ) 
	#define CAL_IecTasksWaitForStop  IecTasksWaitForStop
	#define CHK_IecTasksWaitForStop  TRUE
	#define EXP_IecTasksWaitForStop  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTasksWaitForStop", (RTS_UINTPTR)IecTasksWaitForStop, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTasksWaitForStop
	#define EXT_CmpIecTaskIecTasksWaitForStop
	#define GET_CmpIecTaskIecTasksWaitForStop  ERR_OK
	#define CAL_CmpIecTaskIecTasksWaitForStop pICmpIecTask->IIecTasksWaitForStop
	#define CHK_CmpIecTaskIecTasksWaitForStop (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTasksWaitForStop  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTasksWaitForStop
	#define EXT_IecTasksWaitForStop
	#define GET_IecTasksWaitForStop(fl)  CAL_CMGETAPI( "IecTasksWaitForStop" ) 
	#define CAL_IecTasksWaitForStop pICmpIecTask->IIecTasksWaitForStop
	#define CHK_IecTasksWaitForStop (pICmpIecTask != NULL)
	#define EXP_IecTasksWaitForStop  CAL_CMEXPAPI( "IecTasksWaitForStop" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTasksWaitForStop  PFIECTASKSWAITFORSTOP pfIecTasksWaitForStop;
	#define EXT_IecTasksWaitForStop  extern PFIECTASKSWAITFORSTOP pfIecTasksWaitForStop;
	#define GET_IecTasksWaitForStop(fl)  s_pfCMGetAPI2( "IecTasksWaitForStop", (RTS_VOID_FCTPTR *)&pfIecTasksWaitForStop, (fl), 0, 0)
	#define CAL_IecTasksWaitForStop  pfIecTasksWaitForStop
	#define CHK_IecTasksWaitForStop  (pfIecTasksWaitForStop != NULL)
	#define EXP_IecTasksWaitForStop  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTasksWaitForStop", (RTS_UINTPTR)IecTasksWaitForStop, 0, 0) 
#endif




/**
 * <description>Init all outputs and write to the periphery.
 *	NOTE: Application must be in stop before calling this function!</description>
 * <param name="pApp" type="IN">Pointer to specified application</param>
 * <result>Error code</result>
 */
RTS_RESULT CDECL IecTaskInitOutputs(APPLICATION *pApp);
typedef RTS_RESULT (CDECL * PFIECTASKINITOUTPUTS) (APPLICATION *pApp);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKINITOUTPUTS_NOTIMPLEMENTED)
	#define USE_IecTaskInitOutputs
	#define EXT_IecTaskInitOutputs
	#define GET_IecTaskInitOutputs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskInitOutputs(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskInitOutputs  FALSE
	#define EXP_IecTaskInitOutputs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskInitOutputs
	#define EXT_IecTaskInitOutputs
	#define GET_IecTaskInitOutputs(fl)  CAL_CMGETAPI( "IecTaskInitOutputs" ) 
	#define CAL_IecTaskInitOutputs  IecTaskInitOutputs
	#define CHK_IecTaskInitOutputs  TRUE
	#define EXP_IecTaskInitOutputs  CAL_CMEXPAPI( "IecTaskInitOutputs" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskInitOutputs
	#define EXT_IecTaskInitOutputs
	#define GET_IecTaskInitOutputs(fl)  CAL_CMGETAPI( "IecTaskInitOutputs" ) 
	#define CAL_IecTaskInitOutputs  IecTaskInitOutputs
	#define CHK_IecTaskInitOutputs  TRUE
	#define EXP_IecTaskInitOutputs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskInitOutputs", (RTS_UINTPTR)IecTaskInitOutputs, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskInitOutputs
	#define EXT_CmpIecTaskIecTaskInitOutputs
	#define GET_CmpIecTaskIecTaskInitOutputs  ERR_OK
	#define CAL_CmpIecTaskIecTaskInitOutputs pICmpIecTask->IIecTaskInitOutputs
	#define CHK_CmpIecTaskIecTaskInitOutputs (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskInitOutputs  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskInitOutputs
	#define EXT_IecTaskInitOutputs
	#define GET_IecTaskInitOutputs(fl)  CAL_CMGETAPI( "IecTaskInitOutputs" ) 
	#define CAL_IecTaskInitOutputs pICmpIecTask->IIecTaskInitOutputs
	#define CHK_IecTaskInitOutputs (pICmpIecTask != NULL)
	#define EXP_IecTaskInitOutputs  CAL_CMEXPAPI( "IecTaskInitOutputs" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskInitOutputs  PFIECTASKINITOUTPUTS pfIecTaskInitOutputs;
	#define EXT_IecTaskInitOutputs  extern PFIECTASKINITOUTPUTS pfIecTaskInitOutputs;
	#define GET_IecTaskInitOutputs(fl)  s_pfCMGetAPI2( "IecTaskInitOutputs", (RTS_VOID_FCTPTR *)&pfIecTaskInitOutputs, (fl), 0, 0)
	#define CAL_IecTaskInitOutputs  pfIecTaskInitOutputs
	#define CHK_IecTaskInitOutputs  (pfIecTaskInitOutputs != NULL)
	#define EXP_IecTaskInitOutputs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskInitOutputs", (RTS_UINTPTR)IecTaskInitOutputs, 0, 0) 
#endif




/**
 * <description>After this call no IEC task will be rescheduled, that is 
 * if it is not already running. May be used for executing onlinechange code.
 * Each call must be matched with a call to TaskLeaveExclusiveSection.
 * </description>
 * <result>Error code</result>
 */
RTS_RESULT CDECL IecTaskEnterExclusiveSection(void);
typedef RTS_RESULT (CDECL * PFIECTASKENTEREXCLUSIVESECTION) (void);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKENTEREXCLUSIVESECTION_NOTIMPLEMENTED)
	#define USE_IecTaskEnterExclusiveSection
	#define EXT_IecTaskEnterExclusiveSection
	#define GET_IecTaskEnterExclusiveSection(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskEnterExclusiveSection()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskEnterExclusiveSection  FALSE
	#define EXP_IecTaskEnterExclusiveSection  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskEnterExclusiveSection
	#define EXT_IecTaskEnterExclusiveSection
	#define GET_IecTaskEnterExclusiveSection(fl)  CAL_CMGETAPI( "IecTaskEnterExclusiveSection" ) 
	#define CAL_IecTaskEnterExclusiveSection  IecTaskEnterExclusiveSection
	#define CHK_IecTaskEnterExclusiveSection  TRUE
	#define EXP_IecTaskEnterExclusiveSection  CAL_CMEXPAPI( "IecTaskEnterExclusiveSection" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskEnterExclusiveSection
	#define EXT_IecTaskEnterExclusiveSection
	#define GET_IecTaskEnterExclusiveSection(fl)  CAL_CMGETAPI( "IecTaskEnterExclusiveSection" ) 
	#define CAL_IecTaskEnterExclusiveSection  IecTaskEnterExclusiveSection
	#define CHK_IecTaskEnterExclusiveSection  TRUE
	#define EXP_IecTaskEnterExclusiveSection  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskEnterExclusiveSection", (RTS_UINTPTR)IecTaskEnterExclusiveSection, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskEnterExclusiveSection
	#define EXT_CmpIecTaskIecTaskEnterExclusiveSection
	#define GET_CmpIecTaskIecTaskEnterExclusiveSection  ERR_OK
	#define CAL_CmpIecTaskIecTaskEnterExclusiveSection pICmpIecTask->IIecTaskEnterExclusiveSection
	#define CHK_CmpIecTaskIecTaskEnterExclusiveSection (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskEnterExclusiveSection  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskEnterExclusiveSection
	#define EXT_IecTaskEnterExclusiveSection
	#define GET_IecTaskEnterExclusiveSection(fl)  CAL_CMGETAPI( "IecTaskEnterExclusiveSection" ) 
	#define CAL_IecTaskEnterExclusiveSection pICmpIecTask->IIecTaskEnterExclusiveSection
	#define CHK_IecTaskEnterExclusiveSection (pICmpIecTask != NULL)
	#define EXP_IecTaskEnterExclusiveSection  CAL_CMEXPAPI( "IecTaskEnterExclusiveSection" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskEnterExclusiveSection  PFIECTASKENTEREXCLUSIVESECTION pfIecTaskEnterExclusiveSection;
	#define EXT_IecTaskEnterExclusiveSection  extern PFIECTASKENTEREXCLUSIVESECTION pfIecTaskEnterExclusiveSection;
	#define GET_IecTaskEnterExclusiveSection(fl)  s_pfCMGetAPI2( "IecTaskEnterExclusiveSection", (RTS_VOID_FCTPTR *)&pfIecTaskEnterExclusiveSection, (fl), 0, 0)
	#define CAL_IecTaskEnterExclusiveSection  pfIecTaskEnterExclusiveSection
	#define CHK_IecTaskEnterExclusiveSection  (pfIecTaskEnterExclusiveSection != NULL)
	#define EXP_IecTaskEnterExclusiveSection  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskEnterExclusiveSection", (RTS_UINTPTR)IecTaskEnterExclusiveSection, 0, 0) 
#endif




/**
 * <description>Leave an exclusiv section, that has been started by TaskEnterExclusiveSection</description>
 * <result>Error code</result>
 */
RTS_RESULT CDECL IecTaskLeaveExclusiveSection(void);
typedef RTS_RESULT (CDECL * PFIECTASKLEAVEEXCLUSIVESECTION) (void);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKLEAVEEXCLUSIVESECTION_NOTIMPLEMENTED)
	#define USE_IecTaskLeaveExclusiveSection
	#define EXT_IecTaskLeaveExclusiveSection
	#define GET_IecTaskLeaveExclusiveSection(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskLeaveExclusiveSection()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskLeaveExclusiveSection  FALSE
	#define EXP_IecTaskLeaveExclusiveSection  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskLeaveExclusiveSection
	#define EXT_IecTaskLeaveExclusiveSection
	#define GET_IecTaskLeaveExclusiveSection(fl)  CAL_CMGETAPI( "IecTaskLeaveExclusiveSection" ) 
	#define CAL_IecTaskLeaveExclusiveSection  IecTaskLeaveExclusiveSection
	#define CHK_IecTaskLeaveExclusiveSection  TRUE
	#define EXP_IecTaskLeaveExclusiveSection  CAL_CMEXPAPI( "IecTaskLeaveExclusiveSection" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskLeaveExclusiveSection
	#define EXT_IecTaskLeaveExclusiveSection
	#define GET_IecTaskLeaveExclusiveSection(fl)  CAL_CMGETAPI( "IecTaskLeaveExclusiveSection" ) 
	#define CAL_IecTaskLeaveExclusiveSection  IecTaskLeaveExclusiveSection
	#define CHK_IecTaskLeaveExclusiveSection  TRUE
	#define EXP_IecTaskLeaveExclusiveSection  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskLeaveExclusiveSection", (RTS_UINTPTR)IecTaskLeaveExclusiveSection, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskLeaveExclusiveSection
	#define EXT_CmpIecTaskIecTaskLeaveExclusiveSection
	#define GET_CmpIecTaskIecTaskLeaveExclusiveSection  ERR_OK
	#define CAL_CmpIecTaskIecTaskLeaveExclusiveSection pICmpIecTask->IIecTaskLeaveExclusiveSection
	#define CHK_CmpIecTaskIecTaskLeaveExclusiveSection (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskLeaveExclusiveSection  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskLeaveExclusiveSection
	#define EXT_IecTaskLeaveExclusiveSection
	#define GET_IecTaskLeaveExclusiveSection(fl)  CAL_CMGETAPI( "IecTaskLeaveExclusiveSection" ) 
	#define CAL_IecTaskLeaveExclusiveSection pICmpIecTask->IIecTaskLeaveExclusiveSection
	#define CHK_IecTaskLeaveExclusiveSection (pICmpIecTask != NULL)
	#define EXP_IecTaskLeaveExclusiveSection  CAL_CMEXPAPI( "IecTaskLeaveExclusiveSection" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskLeaveExclusiveSection  PFIECTASKLEAVEEXCLUSIVESECTION pfIecTaskLeaveExclusiveSection;
	#define EXT_IecTaskLeaveExclusiveSection  extern PFIECTASKLEAVEEXCLUSIVESECTION pfIecTaskLeaveExclusiveSection;
	#define GET_IecTaskLeaveExclusiveSection(fl)  s_pfCMGetAPI2( "IecTaskLeaveExclusiveSection", (RTS_VOID_FCTPTR *)&pfIecTaskLeaveExclusiveSection, (fl), 0, 0)
	#define CAL_IecTaskLeaveExclusiveSection  pfIecTaskLeaveExclusiveSection
	#define CHK_IecTaskLeaveExclusiveSection  (pfIecTaskLeaveExclusiveSection != NULL)
	#define EXP_IecTaskLeaveExclusiveSection  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskLeaveExclusiveSection", (RTS_UINTPTR)IecTaskLeaveExclusiveSection, 0, 0) 
#endif




/**
 * <description>Enter an exclusive section.
 *	After this call, no IEC task will be rescheduled of the specified application, if it is not already running.
 *	Each call must be matched with a call to TaskLeaveExclusiveSection.
 * </description>
 * <result>Error code</result>
 */
RTS_RESULT CDECL IecTaskEnterExclusiveSection2(APPLICATION *pApp);
typedef RTS_RESULT (CDECL * PFIECTASKENTEREXCLUSIVESECTION2) (APPLICATION *pApp);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKENTEREXCLUSIVESECTION2_NOTIMPLEMENTED)
	#define USE_IecTaskEnterExclusiveSection2
	#define EXT_IecTaskEnterExclusiveSection2
	#define GET_IecTaskEnterExclusiveSection2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskEnterExclusiveSection2(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskEnterExclusiveSection2  FALSE
	#define EXP_IecTaskEnterExclusiveSection2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskEnterExclusiveSection2
	#define EXT_IecTaskEnterExclusiveSection2
	#define GET_IecTaskEnterExclusiveSection2(fl)  CAL_CMGETAPI( "IecTaskEnterExclusiveSection2" ) 
	#define CAL_IecTaskEnterExclusiveSection2  IecTaskEnterExclusiveSection2
	#define CHK_IecTaskEnterExclusiveSection2  TRUE
	#define EXP_IecTaskEnterExclusiveSection2  CAL_CMEXPAPI( "IecTaskEnterExclusiveSection2" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskEnterExclusiveSection2
	#define EXT_IecTaskEnterExclusiveSection2
	#define GET_IecTaskEnterExclusiveSection2(fl)  CAL_CMGETAPI( "IecTaskEnterExclusiveSection2" ) 
	#define CAL_IecTaskEnterExclusiveSection2  IecTaskEnterExclusiveSection2
	#define CHK_IecTaskEnterExclusiveSection2  TRUE
	#define EXP_IecTaskEnterExclusiveSection2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskEnterExclusiveSection2", (RTS_UINTPTR)IecTaskEnterExclusiveSection2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskEnterExclusiveSection2
	#define EXT_CmpIecTaskIecTaskEnterExclusiveSection2
	#define GET_CmpIecTaskIecTaskEnterExclusiveSection2  ERR_OK
	#define CAL_CmpIecTaskIecTaskEnterExclusiveSection2 pICmpIecTask->IIecTaskEnterExclusiveSection2
	#define CHK_CmpIecTaskIecTaskEnterExclusiveSection2 (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskEnterExclusiveSection2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskEnterExclusiveSection2
	#define EXT_IecTaskEnterExclusiveSection2
	#define GET_IecTaskEnterExclusiveSection2(fl)  CAL_CMGETAPI( "IecTaskEnterExclusiveSection2" ) 
	#define CAL_IecTaskEnterExclusiveSection2 pICmpIecTask->IIecTaskEnterExclusiveSection2
	#define CHK_IecTaskEnterExclusiveSection2 (pICmpIecTask != NULL)
	#define EXP_IecTaskEnterExclusiveSection2  CAL_CMEXPAPI( "IecTaskEnterExclusiveSection2" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskEnterExclusiveSection2  PFIECTASKENTEREXCLUSIVESECTION2 pfIecTaskEnterExclusiveSection2;
	#define EXT_IecTaskEnterExclusiveSection2  extern PFIECTASKENTEREXCLUSIVESECTION2 pfIecTaskEnterExclusiveSection2;
	#define GET_IecTaskEnterExclusiveSection2(fl)  s_pfCMGetAPI2( "IecTaskEnterExclusiveSection2", (RTS_VOID_FCTPTR *)&pfIecTaskEnterExclusiveSection2, (fl), 0, 0)
	#define CAL_IecTaskEnterExclusiveSection2  pfIecTaskEnterExclusiveSection2
	#define CHK_IecTaskEnterExclusiveSection2  (pfIecTaskEnterExclusiveSection2 != NULL)
	#define EXP_IecTaskEnterExclusiveSection2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskEnterExclusiveSection2", (RTS_UINTPTR)IecTaskEnterExclusiveSection2, 0, 0) 
#endif




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
RTS_RESULT CDECL IecTaskTryEnterExclusiveSection2(APPLICATION *pApp, RTS_UI32 timeoutMs, RTS_BOOL bForceEnter);
typedef RTS_RESULT (CDECL * PFIECTASKTRYENTEREXCLUSIVESECTION2) (APPLICATION *pApp, RTS_UI32 timeoutMs, RTS_BOOL bForceEnter);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKTRYENTEREXCLUSIVESECTION2_NOTIMPLEMENTED)
	#define USE_IecTaskTryEnterExclusiveSection2
	#define EXT_IecTaskTryEnterExclusiveSection2
	#define GET_IecTaskTryEnterExclusiveSection2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskTryEnterExclusiveSection2(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskTryEnterExclusiveSection2  FALSE
	#define EXP_IecTaskTryEnterExclusiveSection2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskTryEnterExclusiveSection2
	#define EXT_IecTaskTryEnterExclusiveSection2
	#define GET_IecTaskTryEnterExclusiveSection2(fl)  CAL_CMGETAPI( "IecTaskTryEnterExclusiveSection2" ) 
	#define CAL_IecTaskTryEnterExclusiveSection2  IecTaskTryEnterExclusiveSection2
	#define CHK_IecTaskTryEnterExclusiveSection2  TRUE
	#define EXP_IecTaskTryEnterExclusiveSection2  CAL_CMEXPAPI( "IecTaskTryEnterExclusiveSection2" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskTryEnterExclusiveSection2
	#define EXT_IecTaskTryEnterExclusiveSection2
	#define GET_IecTaskTryEnterExclusiveSection2(fl)  CAL_CMGETAPI( "IecTaskTryEnterExclusiveSection2" ) 
	#define CAL_IecTaskTryEnterExclusiveSection2  IecTaskTryEnterExclusiveSection2
	#define CHK_IecTaskTryEnterExclusiveSection2  TRUE
	#define EXP_IecTaskTryEnterExclusiveSection2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskTryEnterExclusiveSection2", (RTS_UINTPTR)IecTaskTryEnterExclusiveSection2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskTryEnterExclusiveSection2
	#define EXT_CmpIecTaskIecTaskTryEnterExclusiveSection2
	#define GET_CmpIecTaskIecTaskTryEnterExclusiveSection2  ERR_OK
	#define CAL_CmpIecTaskIecTaskTryEnterExclusiveSection2 pICmpIecTask->IIecTaskTryEnterExclusiveSection2
	#define CHK_CmpIecTaskIecTaskTryEnterExclusiveSection2 (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskTryEnterExclusiveSection2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskTryEnterExclusiveSection2
	#define EXT_IecTaskTryEnterExclusiveSection2
	#define GET_IecTaskTryEnterExclusiveSection2(fl)  CAL_CMGETAPI( "IecTaskTryEnterExclusiveSection2" ) 
	#define CAL_IecTaskTryEnterExclusiveSection2 pICmpIecTask->IIecTaskTryEnterExclusiveSection2
	#define CHK_IecTaskTryEnterExclusiveSection2 (pICmpIecTask != NULL)
	#define EXP_IecTaskTryEnterExclusiveSection2  CAL_CMEXPAPI( "IecTaskTryEnterExclusiveSection2" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskTryEnterExclusiveSection2  PFIECTASKTRYENTEREXCLUSIVESECTION2 pfIecTaskTryEnterExclusiveSection2;
	#define EXT_IecTaskTryEnterExclusiveSection2  extern PFIECTASKTRYENTEREXCLUSIVESECTION2 pfIecTaskTryEnterExclusiveSection2;
	#define GET_IecTaskTryEnterExclusiveSection2(fl)  s_pfCMGetAPI2( "IecTaskTryEnterExclusiveSection2", (RTS_VOID_FCTPTR *)&pfIecTaskTryEnterExclusiveSection2, (fl), 0, 0)
	#define CAL_IecTaskTryEnterExclusiveSection2  pfIecTaskTryEnterExclusiveSection2
	#define CHK_IecTaskTryEnterExclusiveSection2  (pfIecTaskTryEnterExclusiveSection2 != NULL)
	#define EXP_IecTaskTryEnterExclusiveSection2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskTryEnterExclusiveSection2", (RTS_UINTPTR)IecTaskTryEnterExclusiveSection2, 0, 0) 
#endif




/**
 * <description>Leave an exclusive section of the specified application, that has been entered by TaskEnterExclusiveSection or IecTaskTryEnterExclusiveSection2</description>
 * <result>Error code</result>
 */
RTS_RESULT CDECL IecTaskLeaveExclusiveSection2(APPLICATION *pApp);
typedef RTS_RESULT (CDECL * PFIECTASKLEAVEEXCLUSIVESECTION2) (APPLICATION *pApp);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKLEAVEEXCLUSIVESECTION2_NOTIMPLEMENTED)
	#define USE_IecTaskLeaveExclusiveSection2
	#define EXT_IecTaskLeaveExclusiveSection2
	#define GET_IecTaskLeaveExclusiveSection2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskLeaveExclusiveSection2(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskLeaveExclusiveSection2  FALSE
	#define EXP_IecTaskLeaveExclusiveSection2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskLeaveExclusiveSection2
	#define EXT_IecTaskLeaveExclusiveSection2
	#define GET_IecTaskLeaveExclusiveSection2(fl)  CAL_CMGETAPI( "IecTaskLeaveExclusiveSection2" ) 
	#define CAL_IecTaskLeaveExclusiveSection2  IecTaskLeaveExclusiveSection2
	#define CHK_IecTaskLeaveExclusiveSection2  TRUE
	#define EXP_IecTaskLeaveExclusiveSection2  CAL_CMEXPAPI( "IecTaskLeaveExclusiveSection2" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskLeaveExclusiveSection2
	#define EXT_IecTaskLeaveExclusiveSection2
	#define GET_IecTaskLeaveExclusiveSection2(fl)  CAL_CMGETAPI( "IecTaskLeaveExclusiveSection2" ) 
	#define CAL_IecTaskLeaveExclusiveSection2  IecTaskLeaveExclusiveSection2
	#define CHK_IecTaskLeaveExclusiveSection2  TRUE
	#define EXP_IecTaskLeaveExclusiveSection2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskLeaveExclusiveSection2", (RTS_UINTPTR)IecTaskLeaveExclusiveSection2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskLeaveExclusiveSection2
	#define EXT_CmpIecTaskIecTaskLeaveExclusiveSection2
	#define GET_CmpIecTaskIecTaskLeaveExclusiveSection2  ERR_OK
	#define CAL_CmpIecTaskIecTaskLeaveExclusiveSection2 pICmpIecTask->IIecTaskLeaveExclusiveSection2
	#define CHK_CmpIecTaskIecTaskLeaveExclusiveSection2 (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskLeaveExclusiveSection2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskLeaveExclusiveSection2
	#define EXT_IecTaskLeaveExclusiveSection2
	#define GET_IecTaskLeaveExclusiveSection2(fl)  CAL_CMGETAPI( "IecTaskLeaveExclusiveSection2" ) 
	#define CAL_IecTaskLeaveExclusiveSection2 pICmpIecTask->IIecTaskLeaveExclusiveSection2
	#define CHK_IecTaskLeaveExclusiveSection2 (pICmpIecTask != NULL)
	#define EXP_IecTaskLeaveExclusiveSection2  CAL_CMEXPAPI( "IecTaskLeaveExclusiveSection2" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskLeaveExclusiveSection2  PFIECTASKLEAVEEXCLUSIVESECTION2 pfIecTaskLeaveExclusiveSection2;
	#define EXT_IecTaskLeaveExclusiveSection2  extern PFIECTASKLEAVEEXCLUSIVESECTION2 pfIecTaskLeaveExclusiveSection2;
	#define GET_IecTaskLeaveExclusiveSection2(fl)  s_pfCMGetAPI2( "IecTaskLeaveExclusiveSection2", (RTS_VOID_FCTPTR *)&pfIecTaskLeaveExclusiveSection2, (fl), 0, 0)
	#define CAL_IecTaskLeaveExclusiveSection2  pfIecTaskLeaveExclusiveSection2
	#define CHK_IecTaskLeaveExclusiveSection2  (pfIecTaskLeaveExclusiveSection2 != NULL)
	#define EXP_IecTaskLeaveExclusiveSection2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskLeaveExclusiveSection2", (RTS_UINTPTR)IecTaskLeaveExclusiveSection2, 0, 0) 
#endif




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
void CDECL CDECL_EXT __sys__setup__tasks(sys_setup_tasks_struct* p);
typedef void (CDECL * PF__SYS__SETUP__TASKS) (sys_setup_tasks_struct* p);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(__SYS__SETUP__TASKS_NOTIMPLEMENTED)
	#define USE___sys__setup__tasks
	#define EXT___sys__setup__tasks
	#define GET___sys__setup__tasks(fl)  ERR_NOTIMPLEMENTED
	#define CAL___sys__setup__tasks(p0) 
	#define CHK___sys__setup__tasks  FALSE
	#define EXP___sys__setup__tasks  ERR_OK
#elif defined(STATIC_LINK)
	#define USE___sys__setup__tasks
	#define EXT___sys__setup__tasks
	#define GET___sys__setup__tasks(fl)  CAL_CMGETAPI( "__sys__setup__tasks" ) 
	#define CAL___sys__setup__tasks  __sys__setup__tasks
	#define CHK___sys__setup__tasks  TRUE
	#define EXP___sys__setup__tasks  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__setup__tasks", (RTS_UINTPTR)__sys__setup__tasks, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE___sys__setup__tasks
	#define EXT___sys__setup__tasks
	#define GET___sys__setup__tasks(fl)  CAL_CMGETAPI( "__sys__setup__tasks" ) 
	#define CAL___sys__setup__tasks  __sys__setup__tasks
	#define CHK___sys__setup__tasks  TRUE
	#define EXP___sys__setup__tasks  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__setup__tasks", (RTS_UINTPTR)__sys__setup__tasks, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTask__sys__setup__tasks
	#define EXT_CmpIecTask__sys__setup__tasks
	#define GET_CmpIecTask__sys__setup__tasks  ERR_OK
	#define CAL_CmpIecTask__sys__setup__tasks  __sys__setup__tasks
	#define CHK_CmpIecTask__sys__setup__tasks  TRUE
	#define EXP_CmpIecTask__sys__setup__tasks  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__setup__tasks", (RTS_UINTPTR)__sys__setup__tasks, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE___sys__setup__tasks
	#define EXT___sys__setup__tasks
	#define GET___sys__setup__tasks(fl)  CAL_CMGETAPI( "__sys__setup__tasks" ) 
	#define CAL___sys__setup__tasks  __sys__setup__tasks
	#define CHK___sys__setup__tasks  TRUE
	#define EXP___sys__setup__tasks  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__setup__tasks", (RTS_UINTPTR)__sys__setup__tasks, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE___sys__setup__tasks  PF__SYS__SETUP__TASKS pf__sys__setup__tasks;
	#define EXT___sys__setup__tasks  extern PF__SYS__SETUP__TASKS pf__sys__setup__tasks;
	#define GET___sys__setup__tasks(fl)  s_pfCMGetAPI2( "__sys__setup__tasks", (RTS_VOID_FCTPTR *)&pf__sys__setup__tasks, (fl), 0, 0)
	#define CAL___sys__setup__tasks  pf__sys__setup__tasks
	#define CHK___sys__setup__tasks  (pf__sys__setup__tasks != NULL)
	#define EXP___sys__setup__tasks   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__setup__tasks", (RTS_UINTPTR)__sys__setup__tasks, 1, 0) 
#endif


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
void CDECL CDECL_EXT __sys__register__slot__pou(sys_register_slot_pou_struct* p);
typedef void (CDECL * PF__SYS__REGISTER__SLOT__POU) (sys_register_slot_pou_struct* p);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(__SYS__REGISTER__SLOT__POU_NOTIMPLEMENTED)
	#define USE___sys__register__slot__pou
	#define EXT___sys__register__slot__pou
	#define GET___sys__register__slot__pou(fl)  ERR_NOTIMPLEMENTED
	#define CAL___sys__register__slot__pou(p0) 
	#define CHK___sys__register__slot__pou  FALSE
	#define EXP___sys__register__slot__pou  ERR_OK
#elif defined(STATIC_LINK)
	#define USE___sys__register__slot__pou
	#define EXT___sys__register__slot__pou
	#define GET___sys__register__slot__pou(fl)  CAL_CMGETAPI( "__sys__register__slot__pou" ) 
	#define CAL___sys__register__slot__pou  __sys__register__slot__pou
	#define CHK___sys__register__slot__pou  TRUE
	#define EXP___sys__register__slot__pou  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__register__slot__pou", (RTS_UINTPTR)__sys__register__slot__pou, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE___sys__register__slot__pou
	#define EXT___sys__register__slot__pou
	#define GET___sys__register__slot__pou(fl)  CAL_CMGETAPI( "__sys__register__slot__pou" ) 
	#define CAL___sys__register__slot__pou  __sys__register__slot__pou
	#define CHK___sys__register__slot__pou  TRUE
	#define EXP___sys__register__slot__pou  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__register__slot__pou", (RTS_UINTPTR)__sys__register__slot__pou, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTask__sys__register__slot__pou
	#define EXT_CmpIecTask__sys__register__slot__pou
	#define GET_CmpIecTask__sys__register__slot__pou  ERR_OK
	#define CAL_CmpIecTask__sys__register__slot__pou  __sys__register__slot__pou
	#define CHK_CmpIecTask__sys__register__slot__pou  TRUE
	#define EXP_CmpIecTask__sys__register__slot__pou  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__register__slot__pou", (RTS_UINTPTR)__sys__register__slot__pou, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE___sys__register__slot__pou
	#define EXT___sys__register__slot__pou
	#define GET___sys__register__slot__pou(fl)  CAL_CMGETAPI( "__sys__register__slot__pou" ) 
	#define CAL___sys__register__slot__pou  __sys__register__slot__pou
	#define CHK___sys__register__slot__pou  TRUE
	#define EXP___sys__register__slot__pou  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__register__slot__pou", (RTS_UINTPTR)__sys__register__slot__pou, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE___sys__register__slot__pou  PF__SYS__REGISTER__SLOT__POU pf__sys__register__slot__pou;
	#define EXT___sys__register__slot__pou  extern PF__SYS__REGISTER__SLOT__POU pf__sys__register__slot__pou;
	#define GET___sys__register__slot__pou(fl)  s_pfCMGetAPI2( "__sys__register__slot__pou", (RTS_VOID_FCTPTR *)&pf__sys__register__slot__pou, (fl), 0, 0)
	#define CAL___sys__register__slot__pou  pf__sys__register__slot__pou
	#define CHK___sys__register__slot__pou  (pf__sys__register__slot__pou != NULL)
	#define EXP___sys__register__slot__pou   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__register__slot__pou", (RTS_UINTPTR)__sys__register__slot__pou, 1, 0) 
#endif


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
void CDECL CDECL_EXT __sys__unregister__slot__pou(sys_register_slot_pou_struct* p);
typedef void (CDECL * PF__SYS__UNREGISTER__SLOT__POU) (sys_register_slot_pou_struct* p);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(__SYS__UNREGISTER__SLOT__POU_NOTIMPLEMENTED)
	#define USE___sys__unregister__slot__pou
	#define EXT___sys__unregister__slot__pou
	#define GET___sys__unregister__slot__pou(fl)  ERR_NOTIMPLEMENTED
	#define CAL___sys__unregister__slot__pou(p0) 
	#define CHK___sys__unregister__slot__pou  FALSE
	#define EXP___sys__unregister__slot__pou  ERR_OK
#elif defined(STATIC_LINK)
	#define USE___sys__unregister__slot__pou
	#define EXT___sys__unregister__slot__pou
	#define GET___sys__unregister__slot__pou(fl)  CAL_CMGETAPI( "__sys__unregister__slot__pou" ) 
	#define CAL___sys__unregister__slot__pou  __sys__unregister__slot__pou
	#define CHK___sys__unregister__slot__pou  TRUE
	#define EXP___sys__unregister__slot__pou  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__unregister__slot__pou", (RTS_UINTPTR)__sys__unregister__slot__pou, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE___sys__unregister__slot__pou
	#define EXT___sys__unregister__slot__pou
	#define GET___sys__unregister__slot__pou(fl)  CAL_CMGETAPI( "__sys__unregister__slot__pou" ) 
	#define CAL___sys__unregister__slot__pou  __sys__unregister__slot__pou
	#define CHK___sys__unregister__slot__pou  TRUE
	#define EXP___sys__unregister__slot__pou  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__unregister__slot__pou", (RTS_UINTPTR)__sys__unregister__slot__pou, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTask__sys__unregister__slot__pou
	#define EXT_CmpIecTask__sys__unregister__slot__pou
	#define GET_CmpIecTask__sys__unregister__slot__pou  ERR_OK
	#define CAL_CmpIecTask__sys__unregister__slot__pou  __sys__unregister__slot__pou
	#define CHK_CmpIecTask__sys__unregister__slot__pou  TRUE
	#define EXP_CmpIecTask__sys__unregister__slot__pou  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__unregister__slot__pou", (RTS_UINTPTR)__sys__unregister__slot__pou, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE___sys__unregister__slot__pou
	#define EXT___sys__unregister__slot__pou
	#define GET___sys__unregister__slot__pou(fl)  CAL_CMGETAPI( "__sys__unregister__slot__pou" ) 
	#define CAL___sys__unregister__slot__pou  __sys__unregister__slot__pou
	#define CHK___sys__unregister__slot__pou  TRUE
	#define EXP___sys__unregister__slot__pou  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__unregister__slot__pou", (RTS_UINTPTR)__sys__unregister__slot__pou, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE___sys__unregister__slot__pou  PF__SYS__UNREGISTER__SLOT__POU pf__sys__unregister__slot__pou;
	#define EXT___sys__unregister__slot__pou  extern PF__SYS__UNREGISTER__SLOT__POU pf__sys__unregister__slot__pou;
	#define GET___sys__unregister__slot__pou(fl)  s_pfCMGetAPI2( "__sys__unregister__slot__pou", (RTS_VOID_FCTPTR *)&pf__sys__unregister__slot__pou, (fl), 0, 0)
	#define CAL___sys__unregister__slot__pou  pf__sys__unregister__slot__pou
	#define CHK___sys__unregister__slot__pou  (pf__sys__unregister__slot__pou != NULL)
	#define EXP___sys__unregister__slot__pou   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__unregister__slot__pou", (RTS_UINTPTR)__sys__unregister__slot__pou, 1, 0) 
#endif


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
RTS_RESULT CDECL IecTaskRegisterSlotCallbacks(APPLICATION *pApp, RTS_I32 nSlotNr, PF_SLOT_CALLBACK pfSlotCallback, int bIecCallback);
typedef RTS_RESULT (CDECL * PFIECTASKREGISTERSLOTCALLBACKS) (APPLICATION *pApp, RTS_I32 nSlotNr, PF_SLOT_CALLBACK pfSlotCallback, int bIecCallback);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKREGISTERSLOTCALLBACKS_NOTIMPLEMENTED)
	#define USE_IecTaskRegisterSlotCallbacks
	#define EXT_IecTaskRegisterSlotCallbacks
	#define GET_IecTaskRegisterSlotCallbacks(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskRegisterSlotCallbacks(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskRegisterSlotCallbacks  FALSE
	#define EXP_IecTaskRegisterSlotCallbacks  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskRegisterSlotCallbacks
	#define EXT_IecTaskRegisterSlotCallbacks
	#define GET_IecTaskRegisterSlotCallbacks(fl)  CAL_CMGETAPI( "IecTaskRegisterSlotCallbacks" ) 
	#define CAL_IecTaskRegisterSlotCallbacks  IecTaskRegisterSlotCallbacks
	#define CHK_IecTaskRegisterSlotCallbacks  TRUE
	#define EXP_IecTaskRegisterSlotCallbacks  CAL_CMEXPAPI( "IecTaskRegisterSlotCallbacks" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskRegisterSlotCallbacks
	#define EXT_IecTaskRegisterSlotCallbacks
	#define GET_IecTaskRegisterSlotCallbacks(fl)  CAL_CMGETAPI( "IecTaskRegisterSlotCallbacks" ) 
	#define CAL_IecTaskRegisterSlotCallbacks  IecTaskRegisterSlotCallbacks
	#define CHK_IecTaskRegisterSlotCallbacks  TRUE
	#define EXP_IecTaskRegisterSlotCallbacks  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskRegisterSlotCallbacks", (RTS_UINTPTR)IecTaskRegisterSlotCallbacks, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskRegisterSlotCallbacks
	#define EXT_CmpIecTaskIecTaskRegisterSlotCallbacks
	#define GET_CmpIecTaskIecTaskRegisterSlotCallbacks  ERR_OK
	#define CAL_CmpIecTaskIecTaskRegisterSlotCallbacks pICmpIecTask->IIecTaskRegisterSlotCallbacks
	#define CHK_CmpIecTaskIecTaskRegisterSlotCallbacks (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskRegisterSlotCallbacks  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskRegisterSlotCallbacks
	#define EXT_IecTaskRegisterSlotCallbacks
	#define GET_IecTaskRegisterSlotCallbacks(fl)  CAL_CMGETAPI( "IecTaskRegisterSlotCallbacks" ) 
	#define CAL_IecTaskRegisterSlotCallbacks pICmpIecTask->IIecTaskRegisterSlotCallbacks
	#define CHK_IecTaskRegisterSlotCallbacks (pICmpIecTask != NULL)
	#define EXP_IecTaskRegisterSlotCallbacks  CAL_CMEXPAPI( "IecTaskRegisterSlotCallbacks" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskRegisterSlotCallbacks  PFIECTASKREGISTERSLOTCALLBACKS pfIecTaskRegisterSlotCallbacks;
	#define EXT_IecTaskRegisterSlotCallbacks  extern PFIECTASKREGISTERSLOTCALLBACKS pfIecTaskRegisterSlotCallbacks;
	#define GET_IecTaskRegisterSlotCallbacks(fl)  s_pfCMGetAPI2( "IecTaskRegisterSlotCallbacks", (RTS_VOID_FCTPTR *)&pfIecTaskRegisterSlotCallbacks, (fl), 0, 0)
	#define CAL_IecTaskRegisterSlotCallbacks  pfIecTaskRegisterSlotCallbacks
	#define CHK_IecTaskRegisterSlotCallbacks  (pfIecTaskRegisterSlotCallbacks != NULL)
	#define EXP_IecTaskRegisterSlotCallbacks  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskRegisterSlotCallbacks", (RTS_UINTPTR)IecTaskRegisterSlotCallbacks, 0, 0) 
#endif




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
RTS_RESULT CDECL IecTaskUnregisterSlotCallbacks(APPLICATION *pApp, RTS_I32 nSlotNr, PF_SLOT_CALLBACK pfSlotCallback, int bIecCallback);
typedef RTS_RESULT (CDECL * PFIECTASKUNREGISTERSLOTCALLBACKS) (APPLICATION *pApp, RTS_I32 nSlotNr, PF_SLOT_CALLBACK pfSlotCallback, int bIecCallback);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKUNREGISTERSLOTCALLBACKS_NOTIMPLEMENTED)
	#define USE_IecTaskUnregisterSlotCallbacks
	#define EXT_IecTaskUnregisterSlotCallbacks
	#define GET_IecTaskUnregisterSlotCallbacks(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskUnregisterSlotCallbacks(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskUnregisterSlotCallbacks  FALSE
	#define EXP_IecTaskUnregisterSlotCallbacks  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskUnregisterSlotCallbacks
	#define EXT_IecTaskUnregisterSlotCallbacks
	#define GET_IecTaskUnregisterSlotCallbacks(fl)  CAL_CMGETAPI( "IecTaskUnregisterSlotCallbacks" ) 
	#define CAL_IecTaskUnregisterSlotCallbacks  IecTaskUnregisterSlotCallbacks
	#define CHK_IecTaskUnregisterSlotCallbacks  TRUE
	#define EXP_IecTaskUnregisterSlotCallbacks  CAL_CMEXPAPI( "IecTaskUnregisterSlotCallbacks" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskUnregisterSlotCallbacks
	#define EXT_IecTaskUnregisterSlotCallbacks
	#define GET_IecTaskUnregisterSlotCallbacks(fl)  CAL_CMGETAPI( "IecTaskUnregisterSlotCallbacks" ) 
	#define CAL_IecTaskUnregisterSlotCallbacks  IecTaskUnregisterSlotCallbacks
	#define CHK_IecTaskUnregisterSlotCallbacks  TRUE
	#define EXP_IecTaskUnregisterSlotCallbacks  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskUnregisterSlotCallbacks", (RTS_UINTPTR)IecTaskUnregisterSlotCallbacks, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskUnregisterSlotCallbacks
	#define EXT_CmpIecTaskIecTaskUnregisterSlotCallbacks
	#define GET_CmpIecTaskIecTaskUnregisterSlotCallbacks  ERR_OK
	#define CAL_CmpIecTaskIecTaskUnregisterSlotCallbacks pICmpIecTask->IIecTaskUnregisterSlotCallbacks
	#define CHK_CmpIecTaskIecTaskUnregisterSlotCallbacks (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskUnregisterSlotCallbacks  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskUnregisterSlotCallbacks
	#define EXT_IecTaskUnregisterSlotCallbacks
	#define GET_IecTaskUnregisterSlotCallbacks(fl)  CAL_CMGETAPI( "IecTaskUnregisterSlotCallbacks" ) 
	#define CAL_IecTaskUnregisterSlotCallbacks pICmpIecTask->IIecTaskUnregisterSlotCallbacks
	#define CHK_IecTaskUnregisterSlotCallbacks (pICmpIecTask != NULL)
	#define EXP_IecTaskUnregisterSlotCallbacks  CAL_CMEXPAPI( "IecTaskUnregisterSlotCallbacks" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskUnregisterSlotCallbacks  PFIECTASKUNREGISTERSLOTCALLBACKS pfIecTaskUnregisterSlotCallbacks;
	#define EXT_IecTaskUnregisterSlotCallbacks  extern PFIECTASKUNREGISTERSLOTCALLBACKS pfIecTaskUnregisterSlotCallbacks;
	#define GET_IecTaskUnregisterSlotCallbacks(fl)  s_pfCMGetAPI2( "IecTaskUnregisterSlotCallbacks", (RTS_VOID_FCTPTR *)&pfIecTaskUnregisterSlotCallbacks, (fl), 0, 0)
	#define CAL_IecTaskUnregisterSlotCallbacks  pfIecTaskUnregisterSlotCallbacks
	#define CHK_IecTaskUnregisterSlotCallbacks  (pfIecTaskUnregisterSlotCallbacks != NULL)
	#define EXP_IecTaskUnregisterSlotCallbacks  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskUnregisterSlotCallbacks", (RTS_UINTPTR)IecTaskUnregisterSlotCallbacks, 0, 0) 
#endif




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
RTS_RESULT CDECL IecTaskRegisterSlotCallback(Task_Desc *pTask, RTS_I32 nSlotNr, PF_SLOT_CALLBACK pfSlotCallback, int bIecCallback);
typedef RTS_RESULT (CDECL * PFIECTASKREGISTERSLOTCALLBACK) (Task_Desc *pTask, RTS_I32 nSlotNr, PF_SLOT_CALLBACK pfSlotCallback, int bIecCallback);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKREGISTERSLOTCALLBACK_NOTIMPLEMENTED)
	#define USE_IecTaskRegisterSlotCallback
	#define EXT_IecTaskRegisterSlotCallback
	#define GET_IecTaskRegisterSlotCallback(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskRegisterSlotCallback(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskRegisterSlotCallback  FALSE
	#define EXP_IecTaskRegisterSlotCallback  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskRegisterSlotCallback
	#define EXT_IecTaskRegisterSlotCallback
	#define GET_IecTaskRegisterSlotCallback(fl)  CAL_CMGETAPI( "IecTaskRegisterSlotCallback" ) 
	#define CAL_IecTaskRegisterSlotCallback  IecTaskRegisterSlotCallback
	#define CHK_IecTaskRegisterSlotCallback  TRUE
	#define EXP_IecTaskRegisterSlotCallback  CAL_CMEXPAPI( "IecTaskRegisterSlotCallback" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskRegisterSlotCallback
	#define EXT_IecTaskRegisterSlotCallback
	#define GET_IecTaskRegisterSlotCallback(fl)  CAL_CMGETAPI( "IecTaskRegisterSlotCallback" ) 
	#define CAL_IecTaskRegisterSlotCallback  IecTaskRegisterSlotCallback
	#define CHK_IecTaskRegisterSlotCallback  TRUE
	#define EXP_IecTaskRegisterSlotCallback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskRegisterSlotCallback", (RTS_UINTPTR)IecTaskRegisterSlotCallback, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskRegisterSlotCallback
	#define EXT_CmpIecTaskIecTaskRegisterSlotCallback
	#define GET_CmpIecTaskIecTaskRegisterSlotCallback  ERR_OK
	#define CAL_CmpIecTaskIecTaskRegisterSlotCallback pICmpIecTask->IIecTaskRegisterSlotCallback
	#define CHK_CmpIecTaskIecTaskRegisterSlotCallback (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskRegisterSlotCallback  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskRegisterSlotCallback
	#define EXT_IecTaskRegisterSlotCallback
	#define GET_IecTaskRegisterSlotCallback(fl)  CAL_CMGETAPI( "IecTaskRegisterSlotCallback" ) 
	#define CAL_IecTaskRegisterSlotCallback pICmpIecTask->IIecTaskRegisterSlotCallback
	#define CHK_IecTaskRegisterSlotCallback (pICmpIecTask != NULL)
	#define EXP_IecTaskRegisterSlotCallback  CAL_CMEXPAPI( "IecTaskRegisterSlotCallback" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskRegisterSlotCallback  PFIECTASKREGISTERSLOTCALLBACK pfIecTaskRegisterSlotCallback;
	#define EXT_IecTaskRegisterSlotCallback  extern PFIECTASKREGISTERSLOTCALLBACK pfIecTaskRegisterSlotCallback;
	#define GET_IecTaskRegisterSlotCallback(fl)  s_pfCMGetAPI2( "IecTaskRegisterSlotCallback", (RTS_VOID_FCTPTR *)&pfIecTaskRegisterSlotCallback, (fl), 0, 0)
	#define CAL_IecTaskRegisterSlotCallback  pfIecTaskRegisterSlotCallback
	#define CHK_IecTaskRegisterSlotCallback  (pfIecTaskRegisterSlotCallback != NULL)
	#define EXP_IecTaskRegisterSlotCallback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskRegisterSlotCallback", (RTS_UINTPTR)IecTaskRegisterSlotCallback, 0, 0) 
#endif




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
RTS_RESULT CDECL IecTaskUnregisterSlotCallback(Task_Desc *pTask, RTS_I32 nSlotNr, PF_SLOT_CALLBACK pfSlotCallback, int bIecCallback);
typedef RTS_RESULT (CDECL * PFIECTASKUNREGISTERSLOTCALLBACK) (Task_Desc *pTask, RTS_I32 nSlotNr, PF_SLOT_CALLBACK pfSlotCallback, int bIecCallback);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKUNREGISTERSLOTCALLBACK_NOTIMPLEMENTED)
	#define USE_IecTaskUnregisterSlotCallback
	#define EXT_IecTaskUnregisterSlotCallback
	#define GET_IecTaskUnregisterSlotCallback(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskUnregisterSlotCallback(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskUnregisterSlotCallback  FALSE
	#define EXP_IecTaskUnregisterSlotCallback  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskUnregisterSlotCallback
	#define EXT_IecTaskUnregisterSlotCallback
	#define GET_IecTaskUnregisterSlotCallback(fl)  CAL_CMGETAPI( "IecTaskUnregisterSlotCallback" ) 
	#define CAL_IecTaskUnregisterSlotCallback  IecTaskUnregisterSlotCallback
	#define CHK_IecTaskUnregisterSlotCallback  TRUE
	#define EXP_IecTaskUnregisterSlotCallback  CAL_CMEXPAPI( "IecTaskUnregisterSlotCallback" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskUnregisterSlotCallback
	#define EXT_IecTaskUnregisterSlotCallback
	#define GET_IecTaskUnregisterSlotCallback(fl)  CAL_CMGETAPI( "IecTaskUnregisterSlotCallback" ) 
	#define CAL_IecTaskUnregisterSlotCallback  IecTaskUnregisterSlotCallback
	#define CHK_IecTaskUnregisterSlotCallback  TRUE
	#define EXP_IecTaskUnregisterSlotCallback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskUnregisterSlotCallback", (RTS_UINTPTR)IecTaskUnregisterSlotCallback, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskUnregisterSlotCallback
	#define EXT_CmpIecTaskIecTaskUnregisterSlotCallback
	#define GET_CmpIecTaskIecTaskUnregisterSlotCallback  ERR_OK
	#define CAL_CmpIecTaskIecTaskUnregisterSlotCallback pICmpIecTask->IIecTaskUnregisterSlotCallback
	#define CHK_CmpIecTaskIecTaskUnregisterSlotCallback (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskUnregisterSlotCallback  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskUnregisterSlotCallback
	#define EXT_IecTaskUnregisterSlotCallback
	#define GET_IecTaskUnregisterSlotCallback(fl)  CAL_CMGETAPI( "IecTaskUnregisterSlotCallback" ) 
	#define CAL_IecTaskUnregisterSlotCallback pICmpIecTask->IIecTaskUnregisterSlotCallback
	#define CHK_IecTaskUnregisterSlotCallback (pICmpIecTask != NULL)
	#define EXP_IecTaskUnregisterSlotCallback  CAL_CMEXPAPI( "IecTaskUnregisterSlotCallback" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskUnregisterSlotCallback  PFIECTASKUNREGISTERSLOTCALLBACK pfIecTaskUnregisterSlotCallback;
	#define EXT_IecTaskUnregisterSlotCallback  extern PFIECTASKUNREGISTERSLOTCALLBACK pfIecTaskUnregisterSlotCallback;
	#define GET_IecTaskUnregisterSlotCallback(fl)  s_pfCMGetAPI2( "IecTaskUnregisterSlotCallback", (RTS_VOID_FCTPTR *)&pfIecTaskUnregisterSlotCallback, (fl), 0, 0)
	#define CAL_IecTaskUnregisterSlotCallback  pfIecTaskUnregisterSlotCallback
	#define CHK_IecTaskUnregisterSlotCallback  (pfIecTaskUnregisterSlotCallback != NULL)
	#define EXP_IecTaskUnregisterSlotCallback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskUnregisterSlotCallback", (RTS_UINTPTR)IecTaskUnregisterSlotCallback, 0, 0) 
#endif




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
void CDECL CDECL_EXT __sys__rts__cycle(sys_rts_cycle_struct* p);
typedef void (CDECL * PF__SYS__RTS__CYCLE) (sys_rts_cycle_struct* p);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(__SYS__RTS__CYCLE_NOTIMPLEMENTED)
	#define USE___sys__rts__cycle
	#define EXT___sys__rts__cycle
	#define GET___sys__rts__cycle(fl)  ERR_NOTIMPLEMENTED
	#define CAL___sys__rts__cycle(p0) 
	#define CHK___sys__rts__cycle  FALSE
	#define EXP___sys__rts__cycle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE___sys__rts__cycle
	#define EXT___sys__rts__cycle
	#define GET___sys__rts__cycle(fl)  CAL_CMGETAPI( "__sys__rts__cycle" ) 
	#define CAL___sys__rts__cycle  __sys__rts__cycle
	#define CHK___sys__rts__cycle  TRUE
	#define EXP___sys__rts__cycle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__rts__cycle", (RTS_UINTPTR)__sys__rts__cycle, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE___sys__rts__cycle
	#define EXT___sys__rts__cycle
	#define GET___sys__rts__cycle(fl)  CAL_CMGETAPI( "__sys__rts__cycle" ) 
	#define CAL___sys__rts__cycle  __sys__rts__cycle
	#define CHK___sys__rts__cycle  TRUE
	#define EXP___sys__rts__cycle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__rts__cycle", (RTS_UINTPTR)__sys__rts__cycle, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTask__sys__rts__cycle
	#define EXT_CmpIecTask__sys__rts__cycle
	#define GET_CmpIecTask__sys__rts__cycle  ERR_OK
	#define CAL_CmpIecTask__sys__rts__cycle  __sys__rts__cycle
	#define CHK_CmpIecTask__sys__rts__cycle  TRUE
	#define EXP_CmpIecTask__sys__rts__cycle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__rts__cycle", (RTS_UINTPTR)__sys__rts__cycle, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE___sys__rts__cycle
	#define EXT___sys__rts__cycle
	#define GET___sys__rts__cycle(fl)  CAL_CMGETAPI( "__sys__rts__cycle" ) 
	#define CAL___sys__rts__cycle  __sys__rts__cycle
	#define CHK___sys__rts__cycle  TRUE
	#define EXP___sys__rts__cycle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__rts__cycle", (RTS_UINTPTR)__sys__rts__cycle, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE___sys__rts__cycle  PF__SYS__RTS__CYCLE pf__sys__rts__cycle;
	#define EXT___sys__rts__cycle  extern PF__SYS__RTS__CYCLE pf__sys__rts__cycle;
	#define GET___sys__rts__cycle(fl)  s_pfCMGetAPI2( "__sys__rts__cycle", (RTS_VOID_FCTPTR *)&pf__sys__rts__cycle, (fl), 0, 0)
	#define CAL___sys__rts__cycle  pf__sys__rts__cycle
	#define CHK___sys__rts__cycle  (pf__sys__rts__cycle != NULL)
	#define EXP___sys__rts__cycle   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__rts__cycle", (RTS_UINTPTR)__sys__rts__cycle, 1, 0) 
#endif


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
void CDECL CDECL_EXT __sys__rts__cycle__2(sys_rts_cycle_2_struct* p);
typedef void (CDECL * PF__SYS__RTS__CYCLE__2) (sys_rts_cycle_2_struct* p);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(__SYS__RTS__CYCLE__2_NOTIMPLEMENTED)
	#define USE___sys__rts__cycle__2
	#define EXT___sys__rts__cycle__2
	#define GET___sys__rts__cycle__2(fl)  ERR_NOTIMPLEMENTED
	#define CAL___sys__rts__cycle__2(p0) 
	#define CHK___sys__rts__cycle__2  FALSE
	#define EXP___sys__rts__cycle__2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE___sys__rts__cycle__2
	#define EXT___sys__rts__cycle__2
	#define GET___sys__rts__cycle__2(fl)  CAL_CMGETAPI( "__sys__rts__cycle__2" ) 
	#define CAL___sys__rts__cycle__2  __sys__rts__cycle__2
	#define CHK___sys__rts__cycle__2  TRUE
	#define EXP___sys__rts__cycle__2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__rts__cycle__2", (RTS_UINTPTR)__sys__rts__cycle__2, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE___sys__rts__cycle__2
	#define EXT___sys__rts__cycle__2
	#define GET___sys__rts__cycle__2(fl)  CAL_CMGETAPI( "__sys__rts__cycle__2" ) 
	#define CAL___sys__rts__cycle__2  __sys__rts__cycle__2
	#define CHK___sys__rts__cycle__2  TRUE
	#define EXP___sys__rts__cycle__2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__rts__cycle__2", (RTS_UINTPTR)__sys__rts__cycle__2, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTask__sys__rts__cycle__2
	#define EXT_CmpIecTask__sys__rts__cycle__2
	#define GET_CmpIecTask__sys__rts__cycle__2  ERR_OK
	#define CAL_CmpIecTask__sys__rts__cycle__2  __sys__rts__cycle__2
	#define CHK_CmpIecTask__sys__rts__cycle__2  TRUE
	#define EXP_CmpIecTask__sys__rts__cycle__2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__rts__cycle__2", (RTS_UINTPTR)__sys__rts__cycle__2, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE___sys__rts__cycle__2
	#define EXT___sys__rts__cycle__2
	#define GET___sys__rts__cycle__2(fl)  CAL_CMGETAPI( "__sys__rts__cycle__2" ) 
	#define CAL___sys__rts__cycle__2  __sys__rts__cycle__2
	#define CHK___sys__rts__cycle__2  TRUE
	#define EXP___sys__rts__cycle__2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__rts__cycle__2", (RTS_UINTPTR)__sys__rts__cycle__2, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE___sys__rts__cycle__2  PF__SYS__RTS__CYCLE__2 pf__sys__rts__cycle__2;
	#define EXT___sys__rts__cycle__2  extern PF__SYS__RTS__CYCLE__2 pf__sys__rts__cycle__2;
	#define GET___sys__rts__cycle__2(fl)  s_pfCMGetAPI2( "__sys__rts__cycle__2", (RTS_VOID_FCTPTR *)&pf__sys__rts__cycle__2, (fl), 0, 0)
	#define CAL___sys__rts__cycle__2  pf__sys__rts__cycle__2
	#define CHK___sys__rts__cycle__2  (pf__sys__rts__cycle__2 != NULL)
	#define EXP___sys__rts__cycle__2   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__sys__rts__cycle__2", (RTS_UINTPTR)__sys__rts__cycle__2, 1, 0) 
#endif


/**
 * <description>
 * <p>Return task description for a task, specified by it's task handle.
 * </p>
 * </description>
 * <param name="hIecTask" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TASKHANDLE]">Handle to task</param>
 * <result>Task Description or NULL if task handle was NULL or invalid</result>
 */
Task_Desc * CDECL IecTaskGetDesc(RTS_HANDLE hIecTask);
typedef Task_Desc * (CDECL * PFIECTASKGETDESC) (RTS_HANDLE hIecTask);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKGETDESC_NOTIMPLEMENTED)
	#define USE_IecTaskGetDesc
	#define EXT_IecTaskGetDesc
	#define GET_IecTaskGetDesc(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskGetDesc(p0)  (Task_Desc *)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskGetDesc  FALSE
	#define EXP_IecTaskGetDesc  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskGetDesc
	#define EXT_IecTaskGetDesc
	#define GET_IecTaskGetDesc(fl)  CAL_CMGETAPI( "IecTaskGetDesc" ) 
	#define CAL_IecTaskGetDesc  IecTaskGetDesc
	#define CHK_IecTaskGetDesc  TRUE
	#define EXP_IecTaskGetDesc  CAL_CMEXPAPI( "IecTaskGetDesc" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskGetDesc
	#define EXT_IecTaskGetDesc
	#define GET_IecTaskGetDesc(fl)  CAL_CMGETAPI( "IecTaskGetDesc" ) 
	#define CAL_IecTaskGetDesc  IecTaskGetDesc
	#define CHK_IecTaskGetDesc  TRUE
	#define EXP_IecTaskGetDesc  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetDesc", (RTS_UINTPTR)IecTaskGetDesc, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskGetDesc
	#define EXT_CmpIecTaskIecTaskGetDesc
	#define GET_CmpIecTaskIecTaskGetDesc  ERR_OK
	#define CAL_CmpIecTaskIecTaskGetDesc(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskGetDesc() : ((ICmpIecTask*)p0)->IIecTaskGetDesc())
	#define CHK_CmpIecTaskIecTaskGetDesc  (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskGetDesc  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskGetDesc
	#define EXT_IecTaskGetDesc
	#define GET_IecTaskGetDesc(fl)  CAL_CMGETAPI( "IecTaskGetDesc" ) 
	#define CAL_IecTaskGetDesc(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskGetDesc() : ((ICmpIecTask*)p0)->IIecTaskGetDesc())
	#define CHK_IecTaskGetDesc  (pICmpIecTask != NULL)
	#define EXP_IecTaskGetDesc  CAL_CMEXPAPI( "IecTaskGetDesc" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskGetDesc  PFIECTASKGETDESC pfIecTaskGetDesc;
	#define EXT_IecTaskGetDesc  extern PFIECTASKGETDESC pfIecTaskGetDesc;
	#define GET_IecTaskGetDesc(fl)  s_pfCMGetAPI2( "IecTaskGetDesc", (RTS_VOID_FCTPTR *)&pfIecTaskGetDesc, (fl), 0, 0)
	#define CAL_IecTaskGetDesc  pfIecTaskGetDesc
	#define CHK_IecTaskGetDesc  (pfIecTaskGetDesc != NULL)
	#define EXP_IecTaskGetDesc  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetDesc", (RTS_UINTPTR)IecTaskGetDesc, 0, 0) 
#endif




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
RTS_HANDLE CDECL IecTaskGetHandle(char *pszAppName, char *pszTaskName, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECTASKGETHANDLE) (char *pszAppName, char *pszTaskName, RTS_RESULT *pResult);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKGETHANDLE_NOTIMPLEMENTED)
	#define USE_IecTaskGetHandle
	#define EXT_IecTaskGetHandle
	#define GET_IecTaskGetHandle(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskGetHandle(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecTaskGetHandle  FALSE
	#define EXP_IecTaskGetHandle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskGetHandle
	#define EXT_IecTaskGetHandle
	#define GET_IecTaskGetHandle(fl)  CAL_CMGETAPI( "IecTaskGetHandle" ) 
	#define CAL_IecTaskGetHandle  IecTaskGetHandle
	#define CHK_IecTaskGetHandle  TRUE
	#define EXP_IecTaskGetHandle  CAL_CMEXPAPI( "IecTaskGetHandle" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskGetHandle
	#define EXT_IecTaskGetHandle
	#define GET_IecTaskGetHandle(fl)  CAL_CMGETAPI( "IecTaskGetHandle" ) 
	#define CAL_IecTaskGetHandle  IecTaskGetHandle
	#define CHK_IecTaskGetHandle  TRUE
	#define EXP_IecTaskGetHandle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetHandle", (RTS_UINTPTR)IecTaskGetHandle, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskGetHandle
	#define EXT_CmpIecTaskIecTaskGetHandle
	#define GET_CmpIecTaskIecTaskGetHandle  ERR_OK
	#define CAL_CmpIecTaskIecTaskGetHandle pICmpIecTask->IIecTaskGetHandle
	#define CHK_CmpIecTaskIecTaskGetHandle (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskGetHandle  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskGetHandle
	#define EXT_IecTaskGetHandle
	#define GET_IecTaskGetHandle(fl)  CAL_CMGETAPI( "IecTaskGetHandle" ) 
	#define CAL_IecTaskGetHandle pICmpIecTask->IIecTaskGetHandle
	#define CHK_IecTaskGetHandle (pICmpIecTask != NULL)
	#define EXP_IecTaskGetHandle  CAL_CMEXPAPI( "IecTaskGetHandle" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskGetHandle  PFIECTASKGETHANDLE pfIecTaskGetHandle;
	#define EXT_IecTaskGetHandle  extern PFIECTASKGETHANDLE pfIecTaskGetHandle;
	#define GET_IecTaskGetHandle(fl)  s_pfCMGetAPI2( "IecTaskGetHandle", (RTS_VOID_FCTPTR *)&pfIecTaskGetHandle, (fl), 0, 0)
	#define CAL_IecTaskGetHandle  pfIecTaskGetHandle
	#define CHK_IecTaskGetHandle  (pfIecTaskGetHandle != NULL)
	#define EXP_IecTaskGetHandle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetHandle", (RTS_UINTPTR)IecTaskGetHandle, 0, 0) 
#endif




/**
 * <description>Is called to get the task description of the current running task</description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Task handle</result>
 */
RTS_HANDLE CDECL IecTaskGetCurrent(RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECTASKGETCURRENT) (RTS_RESULT *pResult);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKGETCURRENT_NOTIMPLEMENTED)
	#define USE_IecTaskGetCurrent
	#define EXT_IecTaskGetCurrent
	#define GET_IecTaskGetCurrent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskGetCurrent(p0)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecTaskGetCurrent  FALSE
	#define EXP_IecTaskGetCurrent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskGetCurrent
	#define EXT_IecTaskGetCurrent
	#define GET_IecTaskGetCurrent(fl)  CAL_CMGETAPI( "IecTaskGetCurrent" ) 
	#define CAL_IecTaskGetCurrent  IecTaskGetCurrent
	#define CHK_IecTaskGetCurrent  TRUE
	#define EXP_IecTaskGetCurrent  CAL_CMEXPAPI( "IecTaskGetCurrent" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskGetCurrent
	#define EXT_IecTaskGetCurrent
	#define GET_IecTaskGetCurrent(fl)  CAL_CMGETAPI( "IecTaskGetCurrent" ) 
	#define CAL_IecTaskGetCurrent  IecTaskGetCurrent
	#define CHK_IecTaskGetCurrent  TRUE
	#define EXP_IecTaskGetCurrent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetCurrent", (RTS_UINTPTR)IecTaskGetCurrent, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskGetCurrent
	#define EXT_CmpIecTaskIecTaskGetCurrent
	#define GET_CmpIecTaskIecTaskGetCurrent  ERR_OK
	#define CAL_CmpIecTaskIecTaskGetCurrent pICmpIecTask->IIecTaskGetCurrent
	#define CHK_CmpIecTaskIecTaskGetCurrent (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskGetCurrent  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskGetCurrent
	#define EXT_IecTaskGetCurrent
	#define GET_IecTaskGetCurrent(fl)  CAL_CMGETAPI( "IecTaskGetCurrent" ) 
	#define CAL_IecTaskGetCurrent pICmpIecTask->IIecTaskGetCurrent
	#define CHK_IecTaskGetCurrent (pICmpIecTask != NULL)
	#define EXP_IecTaskGetCurrent  CAL_CMEXPAPI( "IecTaskGetCurrent" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskGetCurrent  PFIECTASKGETCURRENT pfIecTaskGetCurrent;
	#define EXT_IecTaskGetCurrent  extern PFIECTASKGETCURRENT pfIecTaskGetCurrent;
	#define GET_IecTaskGetCurrent(fl)  s_pfCMGetAPI2( "IecTaskGetCurrent", (RTS_VOID_FCTPTR *)&pfIecTaskGetCurrent, (fl), 0, 0)
	#define CAL_IecTaskGetCurrent  pfIecTaskGetCurrent
	#define CHK_IecTaskGetCurrent  (pfIecTaskGetCurrent != NULL)
	#define EXP_IecTaskGetCurrent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetCurrent", (RTS_UINTPTR)IecTaskGetCurrent, 0, 0) 
#endif




/**
 * <description>Is called in debug loop, when IEC task is halted on breakpoint</description>
 * <param name="hIecTask" type="IN">Handle to IEC task</param>
 * <result>ERR_OK</result>
 */
RTS_RESULT CDECL IecTaskDebugLoop(RTS_HANDLE hIecTask);
typedef RTS_RESULT (CDECL * PFIECTASKDEBUGLOOP) (RTS_HANDLE hIecTask);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKDEBUGLOOP_NOTIMPLEMENTED)
	#define USE_IecTaskDebugLoop
	#define EXT_IecTaskDebugLoop
	#define GET_IecTaskDebugLoop(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskDebugLoop(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskDebugLoop  FALSE
	#define EXP_IecTaskDebugLoop  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskDebugLoop
	#define EXT_IecTaskDebugLoop
	#define GET_IecTaskDebugLoop(fl)  CAL_CMGETAPI( "IecTaskDebugLoop" ) 
	#define CAL_IecTaskDebugLoop  IecTaskDebugLoop
	#define CHK_IecTaskDebugLoop  TRUE
	#define EXP_IecTaskDebugLoop  CAL_CMEXPAPI( "IecTaskDebugLoop" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskDebugLoop
	#define EXT_IecTaskDebugLoop
	#define GET_IecTaskDebugLoop(fl)  CAL_CMGETAPI( "IecTaskDebugLoop" ) 
	#define CAL_IecTaskDebugLoop  IecTaskDebugLoop
	#define CHK_IecTaskDebugLoop  TRUE
	#define EXP_IecTaskDebugLoop  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskDebugLoop", (RTS_UINTPTR)IecTaskDebugLoop, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskDebugLoop
	#define EXT_CmpIecTaskIecTaskDebugLoop
	#define GET_CmpIecTaskIecTaskDebugLoop  ERR_OK
	#define CAL_CmpIecTaskIecTaskDebugLoop(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskDebugLoop() : ((ICmpIecTask*)p0)->IIecTaskDebugLoop())
	#define CHK_CmpIecTaskIecTaskDebugLoop  (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskDebugLoop  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskDebugLoop
	#define EXT_IecTaskDebugLoop
	#define GET_IecTaskDebugLoop(fl)  CAL_CMGETAPI( "IecTaskDebugLoop" ) 
	#define CAL_IecTaskDebugLoop(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskDebugLoop() : ((ICmpIecTask*)p0)->IIecTaskDebugLoop())
	#define CHK_IecTaskDebugLoop  (pICmpIecTask != NULL)
	#define EXP_IecTaskDebugLoop  CAL_CMEXPAPI( "IecTaskDebugLoop" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskDebugLoop  PFIECTASKDEBUGLOOP pfIecTaskDebugLoop;
	#define EXT_IecTaskDebugLoop  extern PFIECTASKDEBUGLOOP pfIecTaskDebugLoop;
	#define GET_IecTaskDebugLoop(fl)  s_pfCMGetAPI2( "IecTaskDebugLoop", (RTS_VOID_FCTPTR *)&pfIecTaskDebugLoop, (fl), 0, 0)
	#define CAL_IecTaskDebugLoop  pfIecTaskDebugLoop
	#define CHK_IecTaskDebugLoop  (pfIecTaskDebugLoop != NULL)
	#define EXP_IecTaskDebugLoop  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskDebugLoop", (RTS_UINTPTR)IecTaskDebugLoop, 0, 0) 
#endif




/**
 * <description>Is called before entering debug loop, when IEC task is halted on breakpoint</description>
 * <param name="hIecTask" type="IN">Handle to IEC task</param>
 * <result>ERR_OK</result>
 */
RTS_RESULT CDECL IecTaskDebugEnter(RTS_HANDLE hIecTask);
typedef RTS_RESULT (CDECL * PFIECTASKDEBUGENTER) (RTS_HANDLE hIecTask);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKDEBUGENTER_NOTIMPLEMENTED)
	#define USE_IecTaskDebugEnter
	#define EXT_IecTaskDebugEnter
	#define GET_IecTaskDebugEnter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskDebugEnter(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskDebugEnter  FALSE
	#define EXP_IecTaskDebugEnter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskDebugEnter
	#define EXT_IecTaskDebugEnter
	#define GET_IecTaskDebugEnter(fl)  CAL_CMGETAPI( "IecTaskDebugEnter" ) 
	#define CAL_IecTaskDebugEnter  IecTaskDebugEnter
	#define CHK_IecTaskDebugEnter  TRUE
	#define EXP_IecTaskDebugEnter  CAL_CMEXPAPI( "IecTaskDebugEnter" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskDebugEnter
	#define EXT_IecTaskDebugEnter
	#define GET_IecTaskDebugEnter(fl)  CAL_CMGETAPI( "IecTaskDebugEnter" ) 
	#define CAL_IecTaskDebugEnter  IecTaskDebugEnter
	#define CHK_IecTaskDebugEnter  TRUE
	#define EXP_IecTaskDebugEnter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskDebugEnter", (RTS_UINTPTR)IecTaskDebugEnter, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskDebugEnter
	#define EXT_CmpIecTaskIecTaskDebugEnter
	#define GET_CmpIecTaskIecTaskDebugEnter  ERR_OK
	#define CAL_CmpIecTaskIecTaskDebugEnter(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskDebugEnter() : ((ICmpIecTask*)p0)->IIecTaskDebugEnter())
	#define CHK_CmpIecTaskIecTaskDebugEnter  (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskDebugEnter  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskDebugEnter
	#define EXT_IecTaskDebugEnter
	#define GET_IecTaskDebugEnter(fl)  CAL_CMGETAPI( "IecTaskDebugEnter" ) 
	#define CAL_IecTaskDebugEnter(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskDebugEnter() : ((ICmpIecTask*)p0)->IIecTaskDebugEnter())
	#define CHK_IecTaskDebugEnter  (pICmpIecTask != NULL)
	#define EXP_IecTaskDebugEnter  CAL_CMEXPAPI( "IecTaskDebugEnter" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskDebugEnter  PFIECTASKDEBUGENTER pfIecTaskDebugEnter;
	#define EXT_IecTaskDebugEnter  extern PFIECTASKDEBUGENTER pfIecTaskDebugEnter;
	#define GET_IecTaskDebugEnter(fl)  s_pfCMGetAPI2( "IecTaskDebugEnter", (RTS_VOID_FCTPTR *)&pfIecTaskDebugEnter, (fl), 0, 0)
	#define CAL_IecTaskDebugEnter  pfIecTaskDebugEnter
	#define CHK_IecTaskDebugEnter  (pfIecTaskDebugEnter != NULL)
	#define EXP_IecTaskDebugEnter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskDebugEnter", (RTS_UINTPTR)IecTaskDebugEnter, 0, 0) 
#endif




/**
 * <description>Is called after leaving debug loop, when IEC task was halted on breakpoint</description>
 * <param name="hIecTask" type="IN">Handle to IEC task</param>
 * <result>ERR_OK</result>
 */
RTS_RESULT CDECL IecTaskDebugLeave(RTS_HANDLE hIecTask);
typedef RTS_RESULT (CDECL * PFIECTASKDEBUGLEAVE) (RTS_HANDLE hIecTask);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKDEBUGLEAVE_NOTIMPLEMENTED)
	#define USE_IecTaskDebugLeave
	#define EXT_IecTaskDebugLeave
	#define GET_IecTaskDebugLeave(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskDebugLeave(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskDebugLeave  FALSE
	#define EXP_IecTaskDebugLeave  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskDebugLeave
	#define EXT_IecTaskDebugLeave
	#define GET_IecTaskDebugLeave(fl)  CAL_CMGETAPI( "IecTaskDebugLeave" ) 
	#define CAL_IecTaskDebugLeave  IecTaskDebugLeave
	#define CHK_IecTaskDebugLeave  TRUE
	#define EXP_IecTaskDebugLeave  CAL_CMEXPAPI( "IecTaskDebugLeave" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskDebugLeave
	#define EXT_IecTaskDebugLeave
	#define GET_IecTaskDebugLeave(fl)  CAL_CMGETAPI( "IecTaskDebugLeave" ) 
	#define CAL_IecTaskDebugLeave  IecTaskDebugLeave
	#define CHK_IecTaskDebugLeave  TRUE
	#define EXP_IecTaskDebugLeave  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskDebugLeave", (RTS_UINTPTR)IecTaskDebugLeave, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskDebugLeave
	#define EXT_CmpIecTaskIecTaskDebugLeave
	#define GET_CmpIecTaskIecTaskDebugLeave  ERR_OK
	#define CAL_CmpIecTaskIecTaskDebugLeave(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskDebugLeave() : ((ICmpIecTask*)p0)->IIecTaskDebugLeave())
	#define CHK_CmpIecTaskIecTaskDebugLeave  (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskDebugLeave  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskDebugLeave
	#define EXT_IecTaskDebugLeave
	#define GET_IecTaskDebugLeave(fl)  CAL_CMGETAPI( "IecTaskDebugLeave" ) 
	#define CAL_IecTaskDebugLeave(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskDebugLeave() : ((ICmpIecTask*)p0)->IIecTaskDebugLeave())
	#define CHK_IecTaskDebugLeave  (pICmpIecTask != NULL)
	#define EXP_IecTaskDebugLeave  CAL_CMEXPAPI( "IecTaskDebugLeave" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskDebugLeave  PFIECTASKDEBUGLEAVE pfIecTaskDebugLeave;
	#define EXT_IecTaskDebugLeave  extern PFIECTASKDEBUGLEAVE pfIecTaskDebugLeave;
	#define GET_IecTaskDebugLeave(fl)  s_pfCMGetAPI2( "IecTaskDebugLeave", (RTS_VOID_FCTPTR *)&pfIecTaskDebugLeave, (fl), 0, 0)
	#define CAL_IecTaskDebugLeave  pfIecTaskDebugLeave
	#define CHK_IecTaskDebugLeave  (pfIecTaskDebugLeave != NULL)
	#define EXP_IecTaskDebugLeave  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskDebugLeave", (RTS_UINTPTR)IecTaskDebugLeave, 0, 0) 
#endif




/**
 * <description>Set context of the actual task</description>
 * <param name="hIecTask" type="IN">Handle to IEC task</param>
 * <param name="pContext" type="IN">Pointer to register context</param>
 * <result>ERR_OK</result>
 */
RTS_RESULT CDECL IecTaskSetContext(RTS_HANDLE hIecTask, RegContext *pContext);
typedef RTS_RESULT (CDECL * PFIECTASKSETCONTEXT) (RTS_HANDLE hIecTask, RegContext *pContext);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKSETCONTEXT_NOTIMPLEMENTED)
	#define USE_IecTaskSetContext
	#define EXT_IecTaskSetContext
	#define GET_IecTaskSetContext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskSetContext(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskSetContext  FALSE
	#define EXP_IecTaskSetContext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskSetContext
	#define EXT_IecTaskSetContext
	#define GET_IecTaskSetContext(fl)  CAL_CMGETAPI( "IecTaskSetContext" ) 
	#define CAL_IecTaskSetContext  IecTaskSetContext
	#define CHK_IecTaskSetContext  TRUE
	#define EXP_IecTaskSetContext  CAL_CMEXPAPI( "IecTaskSetContext" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskSetContext
	#define EXT_IecTaskSetContext
	#define GET_IecTaskSetContext(fl)  CAL_CMGETAPI( "IecTaskSetContext" ) 
	#define CAL_IecTaskSetContext  IecTaskSetContext
	#define CHK_IecTaskSetContext  TRUE
	#define EXP_IecTaskSetContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskSetContext", (RTS_UINTPTR)IecTaskSetContext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskSetContext
	#define EXT_CmpIecTaskIecTaskSetContext
	#define GET_CmpIecTaskIecTaskSetContext  ERR_OK
	#define CAL_CmpIecTaskIecTaskSetContext(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskSetContext(p1) : ((ICmpIecTask*)p0)->IIecTaskSetContext(p1))
	#define CHK_CmpIecTaskIecTaskSetContext  (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskSetContext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskSetContext
	#define EXT_IecTaskSetContext
	#define GET_IecTaskSetContext(fl)  CAL_CMGETAPI( "IecTaskSetContext" ) 
	#define CAL_IecTaskSetContext(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskSetContext(p1) : ((ICmpIecTask*)p0)->IIecTaskSetContext(p1))
	#define CHK_IecTaskSetContext  (pICmpIecTask != NULL)
	#define EXP_IecTaskSetContext  CAL_CMEXPAPI( "IecTaskSetContext" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskSetContext  PFIECTASKSETCONTEXT pfIecTaskSetContext;
	#define EXT_IecTaskSetContext  extern PFIECTASKSETCONTEXT pfIecTaskSetContext;
	#define GET_IecTaskSetContext(fl)  s_pfCMGetAPI2( "IecTaskSetContext", (RTS_VOID_FCTPTR *)&pfIecTaskSetContext, (fl), 0, 0)
	#define CAL_IecTaskSetContext  pfIecTaskSetContext
	#define CHK_IecTaskSetContext  (pfIecTaskSetContext != NULL)
	#define EXP_IecTaskSetContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskSetContext", (RTS_UINTPTR)IecTaskSetContext, 0, 0) 
#endif




/**
 * <description>Get context of the actual task</description>
 * <param name="hIecTask" type="IN">Handle to IEC task</param>
 * <param name="pContext" type="IN">Pointer to register context</param>
 * <result>ERR_OK</result>
 */
RTS_RESULT CDECL IecTaskGetContext(RTS_HANDLE hIecTask, RegContext *pContext);
typedef RTS_RESULT (CDECL * PFIECTASKGETCONTEXT) (RTS_HANDLE hIecTask, RegContext *pContext);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKGETCONTEXT_NOTIMPLEMENTED)
	#define USE_IecTaskGetContext
	#define EXT_IecTaskGetContext
	#define GET_IecTaskGetContext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskGetContext(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskGetContext  FALSE
	#define EXP_IecTaskGetContext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskGetContext
	#define EXT_IecTaskGetContext
	#define GET_IecTaskGetContext(fl)  CAL_CMGETAPI( "IecTaskGetContext" ) 
	#define CAL_IecTaskGetContext  IecTaskGetContext
	#define CHK_IecTaskGetContext  TRUE
	#define EXP_IecTaskGetContext  CAL_CMEXPAPI( "IecTaskGetContext" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskGetContext
	#define EXT_IecTaskGetContext
	#define GET_IecTaskGetContext(fl)  CAL_CMGETAPI( "IecTaskGetContext" ) 
	#define CAL_IecTaskGetContext  IecTaskGetContext
	#define CHK_IecTaskGetContext  TRUE
	#define EXP_IecTaskGetContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetContext", (RTS_UINTPTR)IecTaskGetContext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskGetContext
	#define EXT_CmpIecTaskIecTaskGetContext
	#define GET_CmpIecTaskIecTaskGetContext  ERR_OK
	#define CAL_CmpIecTaskIecTaskGetContext(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskGetContext(p1) : ((ICmpIecTask*)p0)->IIecTaskGetContext(p1))
	#define CHK_CmpIecTaskIecTaskGetContext  (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskGetContext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskGetContext
	#define EXT_IecTaskGetContext
	#define GET_IecTaskGetContext(fl)  CAL_CMGETAPI( "IecTaskGetContext" ) 
	#define CAL_IecTaskGetContext(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskGetContext(p1) : ((ICmpIecTask*)p0)->IIecTaskGetContext(p1))
	#define CHK_IecTaskGetContext  (pICmpIecTask != NULL)
	#define EXP_IecTaskGetContext  CAL_CMEXPAPI( "IecTaskGetContext" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskGetContext  PFIECTASKGETCONTEXT pfIecTaskGetContext;
	#define EXT_IecTaskGetContext  extern PFIECTASKGETCONTEXT pfIecTaskGetContext;
	#define GET_IecTaskGetContext(fl)  s_pfCMGetAPI2( "IecTaskGetContext", (RTS_VOID_FCTPTR *)&pfIecTaskGetContext, (fl), 0, 0)
	#define CAL_IecTaskGetContext  pfIecTaskGetContext
	#define CHK_IecTaskGetContext  (pfIecTaskGetContext != NULL)
	#define EXP_IecTaskGetContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetContext", (RTS_UINTPTR)IecTaskGetContext, 0, 0) 
#endif




/**
 * <description>Exception handler for the specified Iec task</description>
 * <param name="hIecTask" type="IN">Handle to IEC task</param>
 * <param name="ulException" type="IN">Exception</param>
 * <param name="pContext" type="IN">Pointer to register context</param>
 * <result>ERR_OK</result>
 */
RTS_RESULT CDECL IecTaskExceptionHandler(RTS_HANDLE hIecTask, RTS_UI32 ulException, RegContext Context);
typedef RTS_RESULT (CDECL * PFIECTASKEXCEPTIONHANDLER) (RTS_HANDLE hIecTask, RTS_UI32 ulException, RegContext Context);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKEXCEPTIONHANDLER_NOTIMPLEMENTED)
	#define USE_IecTaskExceptionHandler
	#define EXT_IecTaskExceptionHandler
	#define GET_IecTaskExceptionHandler(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskExceptionHandler(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskExceptionHandler  FALSE
	#define EXP_IecTaskExceptionHandler  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskExceptionHandler
	#define EXT_IecTaskExceptionHandler
	#define GET_IecTaskExceptionHandler(fl)  CAL_CMGETAPI( "IecTaskExceptionHandler" ) 
	#define CAL_IecTaskExceptionHandler  IecTaskExceptionHandler
	#define CHK_IecTaskExceptionHandler  TRUE
	#define EXP_IecTaskExceptionHandler  CAL_CMEXPAPI( "IecTaskExceptionHandler" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskExceptionHandler
	#define EXT_IecTaskExceptionHandler
	#define GET_IecTaskExceptionHandler(fl)  CAL_CMGETAPI( "IecTaskExceptionHandler" ) 
	#define CAL_IecTaskExceptionHandler  IecTaskExceptionHandler
	#define CHK_IecTaskExceptionHandler  TRUE
	#define EXP_IecTaskExceptionHandler  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskExceptionHandler", (RTS_UINTPTR)IecTaskExceptionHandler, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskExceptionHandler
	#define EXT_CmpIecTaskIecTaskExceptionHandler
	#define GET_CmpIecTaskIecTaskExceptionHandler  ERR_OK
	#define CAL_CmpIecTaskIecTaskExceptionHandler(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskExceptionHandler(p1,p2) : ((ICmpIecTask*)p0)->IIecTaskExceptionHandler(p1,p2))
	#define CHK_CmpIecTaskIecTaskExceptionHandler  (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskExceptionHandler  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskExceptionHandler
	#define EXT_IecTaskExceptionHandler
	#define GET_IecTaskExceptionHandler(fl)  CAL_CMGETAPI( "IecTaskExceptionHandler" ) 
	#define CAL_IecTaskExceptionHandler(p0,p1,p2)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskExceptionHandler(p1,p2) : ((ICmpIecTask*)p0)->IIecTaskExceptionHandler(p1,p2))
	#define CHK_IecTaskExceptionHandler  (pICmpIecTask != NULL)
	#define EXP_IecTaskExceptionHandler  CAL_CMEXPAPI( "IecTaskExceptionHandler" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskExceptionHandler  PFIECTASKEXCEPTIONHANDLER pfIecTaskExceptionHandler;
	#define EXT_IecTaskExceptionHandler  extern PFIECTASKEXCEPTIONHANDLER pfIecTaskExceptionHandler;
	#define GET_IecTaskExceptionHandler(fl)  s_pfCMGetAPI2( "IecTaskExceptionHandler", (RTS_VOID_FCTPTR *)&pfIecTaskExceptionHandler, (fl), 0, 0)
	#define CAL_IecTaskExceptionHandler  pfIecTaskExceptionHandler
	#define CHK_IecTaskExceptionHandler  (pfIecTaskExceptionHandler != NULL)
	#define EXP_IecTaskExceptionHandler  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskExceptionHandler", (RTS_UINTPTR)IecTaskExceptionHandler, 0, 0) 
#endif




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
Task_Desc * CDECL IecTaskGetByIndex(APPLICATION* pApp, int iIndex, RTS_RESULT *pResult);
typedef Task_Desc * (CDECL * PFIECTASKGETBYINDEX) (APPLICATION* pApp, int iIndex, RTS_RESULT *pResult);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKGETBYINDEX_NOTIMPLEMENTED)
	#define USE_IecTaskGetByIndex
	#define EXT_IecTaskGetByIndex
	#define GET_IecTaskGetByIndex(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskGetByIndex(p0,p1,p2)  (Task_Desc *)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskGetByIndex  FALSE
	#define EXP_IecTaskGetByIndex  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskGetByIndex
	#define EXT_IecTaskGetByIndex
	#define GET_IecTaskGetByIndex(fl)  CAL_CMGETAPI( "IecTaskGetByIndex" ) 
	#define CAL_IecTaskGetByIndex  IecTaskGetByIndex
	#define CHK_IecTaskGetByIndex  TRUE
	#define EXP_IecTaskGetByIndex  CAL_CMEXPAPI( "IecTaskGetByIndex" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskGetByIndex
	#define EXT_IecTaskGetByIndex
	#define GET_IecTaskGetByIndex(fl)  CAL_CMGETAPI( "IecTaskGetByIndex" ) 
	#define CAL_IecTaskGetByIndex  IecTaskGetByIndex
	#define CHK_IecTaskGetByIndex  TRUE
	#define EXP_IecTaskGetByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetByIndex", (RTS_UINTPTR)IecTaskGetByIndex, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskGetByIndex
	#define EXT_CmpIecTaskIecTaskGetByIndex
	#define GET_CmpIecTaskIecTaskGetByIndex  ERR_OK
	#define CAL_CmpIecTaskIecTaskGetByIndex pICmpIecTask->IIecTaskGetByIndex
	#define CHK_CmpIecTaskIecTaskGetByIndex (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskGetByIndex  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskGetByIndex
	#define EXT_IecTaskGetByIndex
	#define GET_IecTaskGetByIndex(fl)  CAL_CMGETAPI( "IecTaskGetByIndex" ) 
	#define CAL_IecTaskGetByIndex pICmpIecTask->IIecTaskGetByIndex
	#define CHK_IecTaskGetByIndex (pICmpIecTask != NULL)
	#define EXP_IecTaskGetByIndex  CAL_CMEXPAPI( "IecTaskGetByIndex" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskGetByIndex  PFIECTASKGETBYINDEX pfIecTaskGetByIndex;
	#define EXT_IecTaskGetByIndex  extern PFIECTASKGETBYINDEX pfIecTaskGetByIndex;
	#define GET_IecTaskGetByIndex(fl)  s_pfCMGetAPI2( "IecTaskGetByIndex", (RTS_VOID_FCTPTR *)&pfIecTaskGetByIndex, (fl), 0, 0)
	#define CAL_IecTaskGetByIndex  pfIecTaskGetByIndex
	#define CHK_IecTaskGetByIndex  (pfIecTaskGetByIndex != NULL)
	#define EXP_IecTaskGetByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetByIndex", (RTS_UINTPTR)IecTaskGetByIndex, 0, 0) 
#endif




/**
 * <description>Returns task handle of the task specified by index in an application</description>
 * <param name="pApp" type="IN">APPLICATION object</param>
 * <param name="iIndex" type="IN">Index of task in the task list of the application</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the task or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL IecTaskGetHandleByIndex(APPLICATION* pApp, int iIndex, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECTASKGETHANDLEBYINDEX) (APPLICATION* pApp, int iIndex, RTS_RESULT *pResult);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKGETHANDLEBYINDEX_NOTIMPLEMENTED)
	#define USE_IecTaskGetHandleByIndex
	#define EXT_IecTaskGetHandleByIndex
	#define GET_IecTaskGetHandleByIndex(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskGetHandleByIndex(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecTaskGetHandleByIndex  FALSE
	#define EXP_IecTaskGetHandleByIndex  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskGetHandleByIndex
	#define EXT_IecTaskGetHandleByIndex
	#define GET_IecTaskGetHandleByIndex(fl)  CAL_CMGETAPI( "IecTaskGetHandleByIndex" ) 
	#define CAL_IecTaskGetHandleByIndex  IecTaskGetHandleByIndex
	#define CHK_IecTaskGetHandleByIndex  TRUE
	#define EXP_IecTaskGetHandleByIndex  CAL_CMEXPAPI( "IecTaskGetHandleByIndex" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskGetHandleByIndex
	#define EXT_IecTaskGetHandleByIndex
	#define GET_IecTaskGetHandleByIndex(fl)  CAL_CMGETAPI( "IecTaskGetHandleByIndex" ) 
	#define CAL_IecTaskGetHandleByIndex  IecTaskGetHandleByIndex
	#define CHK_IecTaskGetHandleByIndex  TRUE
	#define EXP_IecTaskGetHandleByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetHandleByIndex", (RTS_UINTPTR)IecTaskGetHandleByIndex, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskGetHandleByIndex
	#define EXT_CmpIecTaskIecTaskGetHandleByIndex
	#define GET_CmpIecTaskIecTaskGetHandleByIndex  ERR_OK
	#define CAL_CmpIecTaskIecTaskGetHandleByIndex pICmpIecTask->IIecTaskGetHandleByIndex
	#define CHK_CmpIecTaskIecTaskGetHandleByIndex (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskGetHandleByIndex  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskGetHandleByIndex
	#define EXT_IecTaskGetHandleByIndex
	#define GET_IecTaskGetHandleByIndex(fl)  CAL_CMGETAPI( "IecTaskGetHandleByIndex" ) 
	#define CAL_IecTaskGetHandleByIndex pICmpIecTask->IIecTaskGetHandleByIndex
	#define CHK_IecTaskGetHandleByIndex (pICmpIecTask != NULL)
	#define EXP_IecTaskGetHandleByIndex  CAL_CMEXPAPI( "IecTaskGetHandleByIndex" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskGetHandleByIndex  PFIECTASKGETHANDLEBYINDEX pfIecTaskGetHandleByIndex;
	#define EXT_IecTaskGetHandleByIndex  extern PFIECTASKGETHANDLEBYINDEX pfIecTaskGetHandleByIndex;
	#define GET_IecTaskGetHandleByIndex(fl)  s_pfCMGetAPI2( "IecTaskGetHandleByIndex", (RTS_VOID_FCTPTR *)&pfIecTaskGetHandleByIndex, (fl), 0, 0)
	#define CAL_IecTaskGetHandleByIndex  pfIecTaskGetHandleByIndex
	#define CHK_IecTaskGetHandleByIndex  (pfIecTaskGetHandleByIndex != NULL)
	#define EXP_IecTaskGetHandleByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetHandleByIndex", (RTS_UINTPTR)IecTaskGetHandleByIndex, 0, 0) 
#endif




/**
 * <description>Returns task handle of the task specified by its unique Id</description>
 * <param name="pApp" type="IN">APPLICATION object</param>
 * <param name="iId" type="IN">Unique Id of the task</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the task or RTS_INVALID_HANDLE if failed</result>
 */
Task_Desc* CDECL IecTaskGetById(APPLICATION* pappl, int iId, RTS_RESULT *pResult);
typedef Task_Desc* (CDECL * PFIECTASKGETBYID) (APPLICATION* pappl, int iId, RTS_RESULT *pResult);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKGETBYID_NOTIMPLEMENTED)
	#define USE_IecTaskGetById
	#define EXT_IecTaskGetById
	#define GET_IecTaskGetById(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskGetById(p0,p1,p2)  (Task_Desc*)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskGetById  FALSE
	#define EXP_IecTaskGetById  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskGetById
	#define EXT_IecTaskGetById
	#define GET_IecTaskGetById(fl)  CAL_CMGETAPI( "IecTaskGetById" ) 
	#define CAL_IecTaskGetById  IecTaskGetById
	#define CHK_IecTaskGetById  TRUE
	#define EXP_IecTaskGetById  CAL_CMEXPAPI( "IecTaskGetById" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskGetById
	#define EXT_IecTaskGetById
	#define GET_IecTaskGetById(fl)  CAL_CMGETAPI( "IecTaskGetById" ) 
	#define CAL_IecTaskGetById  IecTaskGetById
	#define CHK_IecTaskGetById  TRUE
	#define EXP_IecTaskGetById  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetById", (RTS_UINTPTR)IecTaskGetById, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskGetById
	#define EXT_CmpIecTaskIecTaskGetById
	#define GET_CmpIecTaskIecTaskGetById  ERR_OK
	#define CAL_CmpIecTaskIecTaskGetById pICmpIecTask->IIecTaskGetById
	#define CHK_CmpIecTaskIecTaskGetById (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskGetById  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskGetById
	#define EXT_IecTaskGetById
	#define GET_IecTaskGetById(fl)  CAL_CMGETAPI( "IecTaskGetById" ) 
	#define CAL_IecTaskGetById pICmpIecTask->IIecTaskGetById
	#define CHK_IecTaskGetById (pICmpIecTask != NULL)
	#define EXP_IecTaskGetById  CAL_CMEXPAPI( "IecTaskGetById" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskGetById  PFIECTASKGETBYID pfIecTaskGetById;
	#define EXT_IecTaskGetById  extern PFIECTASKGETBYID pfIecTaskGetById;
	#define GET_IecTaskGetById(fl)  s_pfCMGetAPI2( "IecTaskGetById", (RTS_VOID_FCTPTR *)&pfIecTaskGetById, (fl), 0, 0)
	#define CAL_IecTaskGetById  pfIecTaskGetById
	#define CHK_IecTaskGetById  (pfIecTaskGetById != NULL)
	#define EXP_IecTaskGetById  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetById", (RTS_UINTPTR)IecTaskGetById, 0, 0) 
#endif




/**
 * <description>Returns the number of tasks of the specified applciation</description>
 * <param name="pAppl" type="IN">APPLICATION object</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Error code</result>
 */
int CDECL IecTaskGetNumOfTasks(APPLICATION* pAppl, RTS_RESULT *pResult);
typedef int (CDECL * PFIECTASKGETNUMOFTASKS) (APPLICATION* pAppl, RTS_RESULT *pResult);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKGETNUMOFTASKS_NOTIMPLEMENTED)
	#define USE_IecTaskGetNumOfTasks
	#define EXT_IecTaskGetNumOfTasks
	#define GET_IecTaskGetNumOfTasks(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskGetNumOfTasks(p0,p1)  (int)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskGetNumOfTasks  FALSE
	#define EXP_IecTaskGetNumOfTasks  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskGetNumOfTasks
	#define EXT_IecTaskGetNumOfTasks
	#define GET_IecTaskGetNumOfTasks(fl)  CAL_CMGETAPI( "IecTaskGetNumOfTasks" ) 
	#define CAL_IecTaskGetNumOfTasks  IecTaskGetNumOfTasks
	#define CHK_IecTaskGetNumOfTasks  TRUE
	#define EXP_IecTaskGetNumOfTasks  CAL_CMEXPAPI( "IecTaskGetNumOfTasks" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskGetNumOfTasks
	#define EXT_IecTaskGetNumOfTasks
	#define GET_IecTaskGetNumOfTasks(fl)  CAL_CMGETAPI( "IecTaskGetNumOfTasks" ) 
	#define CAL_IecTaskGetNumOfTasks  IecTaskGetNumOfTasks
	#define CHK_IecTaskGetNumOfTasks  TRUE
	#define EXP_IecTaskGetNumOfTasks  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetNumOfTasks", (RTS_UINTPTR)IecTaskGetNumOfTasks, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskGetNumOfTasks
	#define EXT_CmpIecTaskIecTaskGetNumOfTasks
	#define GET_CmpIecTaskIecTaskGetNumOfTasks  ERR_OK
	#define CAL_CmpIecTaskIecTaskGetNumOfTasks pICmpIecTask->IIecTaskGetNumOfTasks
	#define CHK_CmpIecTaskIecTaskGetNumOfTasks (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskGetNumOfTasks  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskGetNumOfTasks
	#define EXT_IecTaskGetNumOfTasks
	#define GET_IecTaskGetNumOfTasks(fl)  CAL_CMGETAPI( "IecTaskGetNumOfTasks" ) 
	#define CAL_IecTaskGetNumOfTasks pICmpIecTask->IIecTaskGetNumOfTasks
	#define CHK_IecTaskGetNumOfTasks (pICmpIecTask != NULL)
	#define EXP_IecTaskGetNumOfTasks  CAL_CMEXPAPI( "IecTaskGetNumOfTasks" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskGetNumOfTasks  PFIECTASKGETNUMOFTASKS pfIecTaskGetNumOfTasks;
	#define EXT_IecTaskGetNumOfTasks  extern PFIECTASKGETNUMOFTASKS pfIecTaskGetNumOfTasks;
	#define GET_IecTaskGetNumOfTasks(fl)  s_pfCMGetAPI2( "IecTaskGetNumOfTasks", (RTS_VOID_FCTPTR *)&pfIecTaskGetNumOfTasks, (fl), 0, 0)
	#define CAL_IecTaskGetNumOfTasks  pfIecTaskGetNumOfTasks
	#define CHK_IecTaskGetNumOfTasks  (pfIecTaskGetNumOfTasks != NULL)
	#define EXP_IecTaskGetNumOfTasks  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetNumOfTasks", (RTS_UINTPTR)IecTaskGetNumOfTasks, 0, 0) 
#endif




/**
 * <description>
 * <p>Enable scheduling for all tasks of the specified application</p>
 * </description>
 * <param name="pApp" type="IN" range="[NULL,VALID_APPLICATION]">APPLICATION object</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">All tasks where enabled</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">The scheduler returned an error when trying to start the application</errorcode>
 */
RTS_RESULT CDECL IecTaskEnableSchedulingAll(APPLICATION *pApp);
typedef RTS_RESULT (CDECL * PFIECTASKENABLESCHEDULINGALL) (APPLICATION *pApp);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKENABLESCHEDULINGALL_NOTIMPLEMENTED)
	#define USE_IecTaskEnableSchedulingAll
	#define EXT_IecTaskEnableSchedulingAll
	#define GET_IecTaskEnableSchedulingAll(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskEnableSchedulingAll(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskEnableSchedulingAll  FALSE
	#define EXP_IecTaskEnableSchedulingAll  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskEnableSchedulingAll
	#define EXT_IecTaskEnableSchedulingAll
	#define GET_IecTaskEnableSchedulingAll(fl)  CAL_CMGETAPI( "IecTaskEnableSchedulingAll" ) 
	#define CAL_IecTaskEnableSchedulingAll  IecTaskEnableSchedulingAll
	#define CHK_IecTaskEnableSchedulingAll  TRUE
	#define EXP_IecTaskEnableSchedulingAll  CAL_CMEXPAPI( "IecTaskEnableSchedulingAll" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskEnableSchedulingAll
	#define EXT_IecTaskEnableSchedulingAll
	#define GET_IecTaskEnableSchedulingAll(fl)  CAL_CMGETAPI( "IecTaskEnableSchedulingAll" ) 
	#define CAL_IecTaskEnableSchedulingAll  IecTaskEnableSchedulingAll
	#define CHK_IecTaskEnableSchedulingAll  TRUE
	#define EXP_IecTaskEnableSchedulingAll  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskEnableSchedulingAll", (RTS_UINTPTR)IecTaskEnableSchedulingAll, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskEnableSchedulingAll
	#define EXT_CmpIecTaskIecTaskEnableSchedulingAll
	#define GET_CmpIecTaskIecTaskEnableSchedulingAll  ERR_OK
	#define CAL_CmpIecTaskIecTaskEnableSchedulingAll pICmpIecTask->IIecTaskEnableSchedulingAll
	#define CHK_CmpIecTaskIecTaskEnableSchedulingAll (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskEnableSchedulingAll  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskEnableSchedulingAll
	#define EXT_IecTaskEnableSchedulingAll
	#define GET_IecTaskEnableSchedulingAll(fl)  CAL_CMGETAPI( "IecTaskEnableSchedulingAll" ) 
	#define CAL_IecTaskEnableSchedulingAll pICmpIecTask->IIecTaskEnableSchedulingAll
	#define CHK_IecTaskEnableSchedulingAll (pICmpIecTask != NULL)
	#define EXP_IecTaskEnableSchedulingAll  CAL_CMEXPAPI( "IecTaskEnableSchedulingAll" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskEnableSchedulingAll  PFIECTASKENABLESCHEDULINGALL pfIecTaskEnableSchedulingAll;
	#define EXT_IecTaskEnableSchedulingAll  extern PFIECTASKENABLESCHEDULINGALL pfIecTaskEnableSchedulingAll;
	#define GET_IecTaskEnableSchedulingAll(fl)  s_pfCMGetAPI2( "IecTaskEnableSchedulingAll", (RTS_VOID_FCTPTR *)&pfIecTaskEnableSchedulingAll, (fl), 0, 0)
	#define CAL_IecTaskEnableSchedulingAll  pfIecTaskEnableSchedulingAll
	#define CHK_IecTaskEnableSchedulingAll  (pfIecTaskEnableSchedulingAll != NULL)
	#define EXP_IecTaskEnableSchedulingAll  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskEnableSchedulingAll", (RTS_UINTPTR)IecTaskEnableSchedulingAll, 0, 0) 
#endif




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
RTS_RESULT CDECL IecTaskDisableSchedulingAll(APPLICATION *pApp, RTS_HANDLE hIecTaskToExclude);
typedef RTS_RESULT (CDECL * PFIECTASKDISABLESCHEDULINGALL) (APPLICATION *pApp, RTS_HANDLE hIecTaskToExclude);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKDISABLESCHEDULINGALL_NOTIMPLEMENTED)
	#define USE_IecTaskDisableSchedulingAll
	#define EXT_IecTaskDisableSchedulingAll
	#define GET_IecTaskDisableSchedulingAll(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskDisableSchedulingAll(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskDisableSchedulingAll  FALSE
	#define EXP_IecTaskDisableSchedulingAll  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskDisableSchedulingAll
	#define EXT_IecTaskDisableSchedulingAll
	#define GET_IecTaskDisableSchedulingAll(fl)  CAL_CMGETAPI( "IecTaskDisableSchedulingAll" ) 
	#define CAL_IecTaskDisableSchedulingAll  IecTaskDisableSchedulingAll
	#define CHK_IecTaskDisableSchedulingAll  TRUE
	#define EXP_IecTaskDisableSchedulingAll  CAL_CMEXPAPI( "IecTaskDisableSchedulingAll" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskDisableSchedulingAll
	#define EXT_IecTaskDisableSchedulingAll
	#define GET_IecTaskDisableSchedulingAll(fl)  CAL_CMGETAPI( "IecTaskDisableSchedulingAll" ) 
	#define CAL_IecTaskDisableSchedulingAll  IecTaskDisableSchedulingAll
	#define CHK_IecTaskDisableSchedulingAll  TRUE
	#define EXP_IecTaskDisableSchedulingAll  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskDisableSchedulingAll", (RTS_UINTPTR)IecTaskDisableSchedulingAll, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskDisableSchedulingAll
	#define EXT_CmpIecTaskIecTaskDisableSchedulingAll
	#define GET_CmpIecTaskIecTaskDisableSchedulingAll  ERR_OK
	#define CAL_CmpIecTaskIecTaskDisableSchedulingAll pICmpIecTask->IIecTaskDisableSchedulingAll
	#define CHK_CmpIecTaskIecTaskDisableSchedulingAll (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskDisableSchedulingAll  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskDisableSchedulingAll
	#define EXT_IecTaskDisableSchedulingAll
	#define GET_IecTaskDisableSchedulingAll(fl)  CAL_CMGETAPI( "IecTaskDisableSchedulingAll" ) 
	#define CAL_IecTaskDisableSchedulingAll pICmpIecTask->IIecTaskDisableSchedulingAll
	#define CHK_IecTaskDisableSchedulingAll (pICmpIecTask != NULL)
	#define EXP_IecTaskDisableSchedulingAll  CAL_CMEXPAPI( "IecTaskDisableSchedulingAll" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskDisableSchedulingAll  PFIECTASKDISABLESCHEDULINGALL pfIecTaskDisableSchedulingAll;
	#define EXT_IecTaskDisableSchedulingAll  extern PFIECTASKDISABLESCHEDULINGALL pfIecTaskDisableSchedulingAll;
	#define GET_IecTaskDisableSchedulingAll(fl)  s_pfCMGetAPI2( "IecTaskDisableSchedulingAll", (RTS_VOID_FCTPTR *)&pfIecTaskDisableSchedulingAll, (fl), 0, 0)
	#define CAL_IecTaskDisableSchedulingAll  pfIecTaskDisableSchedulingAll
	#define CHK_IecTaskDisableSchedulingAll  (pfIecTaskDisableSchedulingAll != NULL)
	#define EXP_IecTaskDisableSchedulingAll  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskDisableSchedulingAll", (RTS_UINTPTR)IecTaskDisableSchedulingAll, 0, 0) 
#endif




/**
 * <description>
 * <p>Enable scheduling for one specified task.</p>
 * </description>
 * <param name="hIecTask" type="IN" range="[RTS_INVALID_HANDLE,VALID_TASKHANDLE]">Handle of task to enable scheduling</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">The task was enabled</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">The task handle was invalid</errorcode>
 */
RTS_RESULT CDECL IecTaskEnableScheduling(RTS_HANDLE hIecTask);
typedef RTS_RESULT (CDECL * PFIECTASKENABLESCHEDULING) (RTS_HANDLE hIecTask);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKENABLESCHEDULING_NOTIMPLEMENTED)
	#define USE_IecTaskEnableScheduling
	#define EXT_IecTaskEnableScheduling
	#define GET_IecTaskEnableScheduling(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskEnableScheduling(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskEnableScheduling  FALSE
	#define EXP_IecTaskEnableScheduling  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskEnableScheduling
	#define EXT_IecTaskEnableScheduling
	#define GET_IecTaskEnableScheduling(fl)  CAL_CMGETAPI( "IecTaskEnableScheduling" ) 
	#define CAL_IecTaskEnableScheduling  IecTaskEnableScheduling
	#define CHK_IecTaskEnableScheduling  TRUE
	#define EXP_IecTaskEnableScheduling  CAL_CMEXPAPI( "IecTaskEnableScheduling" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskEnableScheduling
	#define EXT_IecTaskEnableScheduling
	#define GET_IecTaskEnableScheduling(fl)  CAL_CMGETAPI( "IecTaskEnableScheduling" ) 
	#define CAL_IecTaskEnableScheduling  IecTaskEnableScheduling
	#define CHK_IecTaskEnableScheduling  TRUE
	#define EXP_IecTaskEnableScheduling  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskEnableScheduling", (RTS_UINTPTR)IecTaskEnableScheduling, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskEnableScheduling
	#define EXT_CmpIecTaskIecTaskEnableScheduling
	#define GET_CmpIecTaskIecTaskEnableScheduling  ERR_OK
	#define CAL_CmpIecTaskIecTaskEnableScheduling(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskEnableScheduling() : ((ICmpIecTask*)p0)->IIecTaskEnableScheduling())
	#define CHK_CmpIecTaskIecTaskEnableScheduling  (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskEnableScheduling  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskEnableScheduling
	#define EXT_IecTaskEnableScheduling
	#define GET_IecTaskEnableScheduling(fl)  CAL_CMGETAPI( "IecTaskEnableScheduling" ) 
	#define CAL_IecTaskEnableScheduling(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskEnableScheduling() : ((ICmpIecTask*)p0)->IIecTaskEnableScheduling())
	#define CHK_IecTaskEnableScheduling  (pICmpIecTask != NULL)
	#define EXP_IecTaskEnableScheduling  CAL_CMEXPAPI( "IecTaskEnableScheduling" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskEnableScheduling  PFIECTASKENABLESCHEDULING pfIecTaskEnableScheduling;
	#define EXT_IecTaskEnableScheduling  extern PFIECTASKENABLESCHEDULING pfIecTaskEnableScheduling;
	#define GET_IecTaskEnableScheduling(fl)  s_pfCMGetAPI2( "IecTaskEnableScheduling", (RTS_VOID_FCTPTR *)&pfIecTaskEnableScheduling, (fl), 0, 0)
	#define CAL_IecTaskEnableScheduling  pfIecTaskEnableScheduling
	#define CHK_IecTaskEnableScheduling  (pfIecTaskEnableScheduling != NULL)
	#define EXP_IecTaskEnableScheduling  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskEnableScheduling", (RTS_UINTPTR)IecTaskEnableScheduling, 0, 0) 
#endif




/**
 * <description>Disable scheduling for the specified task</description>
 * <param name="hIecTask" type="IN">Handle of task to disable scheduling</param>
 * <result>Error code</result>
 */
RTS_RESULT CDECL IecTaskDisableScheduling(RTS_HANDLE hIecTask);
typedef RTS_RESULT (CDECL * PFIECTASKDISABLESCHEDULING) (RTS_HANDLE hIecTask);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKDISABLESCHEDULING_NOTIMPLEMENTED)
	#define USE_IecTaskDisableScheduling
	#define EXT_IecTaskDisableScheduling
	#define GET_IecTaskDisableScheduling(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskDisableScheduling(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskDisableScheduling  FALSE
	#define EXP_IecTaskDisableScheduling  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskDisableScheduling
	#define EXT_IecTaskDisableScheduling
	#define GET_IecTaskDisableScheduling(fl)  CAL_CMGETAPI( "IecTaskDisableScheduling" ) 
	#define CAL_IecTaskDisableScheduling  IecTaskDisableScheduling
	#define CHK_IecTaskDisableScheduling  TRUE
	#define EXP_IecTaskDisableScheduling  CAL_CMEXPAPI( "IecTaskDisableScheduling" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskDisableScheduling
	#define EXT_IecTaskDisableScheduling
	#define GET_IecTaskDisableScheduling(fl)  CAL_CMGETAPI( "IecTaskDisableScheduling" ) 
	#define CAL_IecTaskDisableScheduling  IecTaskDisableScheduling
	#define CHK_IecTaskDisableScheduling  TRUE
	#define EXP_IecTaskDisableScheduling  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskDisableScheduling", (RTS_UINTPTR)IecTaskDisableScheduling, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskDisableScheduling
	#define EXT_CmpIecTaskIecTaskDisableScheduling
	#define GET_CmpIecTaskIecTaskDisableScheduling  ERR_OK
	#define CAL_CmpIecTaskIecTaskDisableScheduling(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskDisableScheduling() : ((ICmpIecTask*)p0)->IIecTaskDisableScheduling())
	#define CHK_CmpIecTaskIecTaskDisableScheduling  (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskDisableScheduling  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskDisableScheduling
	#define EXT_IecTaskDisableScheduling
	#define GET_IecTaskDisableScheduling(fl)  CAL_CMGETAPI( "IecTaskDisableScheduling" ) 
	#define CAL_IecTaskDisableScheduling(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskDisableScheduling() : ((ICmpIecTask*)p0)->IIecTaskDisableScheduling())
	#define CHK_IecTaskDisableScheduling  (pICmpIecTask != NULL)
	#define EXP_IecTaskDisableScheduling  CAL_CMEXPAPI( "IecTaskDisableScheduling" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskDisableScheduling  PFIECTASKDISABLESCHEDULING pfIecTaskDisableScheduling;
	#define EXT_IecTaskDisableScheduling  extern PFIECTASKDISABLESCHEDULING pfIecTaskDisableScheduling;
	#define GET_IecTaskDisableScheduling(fl)  s_pfCMGetAPI2( "IecTaskDisableScheduling", (RTS_VOID_FCTPTR *)&pfIecTaskDisableScheduling, (fl), 0, 0)
	#define CAL_IecTaskDisableScheduling  pfIecTaskDisableScheduling
	#define CHK_IecTaskDisableScheduling  (pfIecTaskDisableScheduling != NULL)
	#define EXP_IecTaskDisableScheduling  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskDisableScheduling", (RTS_UINTPTR)IecTaskDisableScheduling, 0, 0) 
#endif




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
RTS_RESULT CDECL IecTaskEnableWatchdog(RTS_HANDLE hIecTask);
typedef RTS_RESULT (CDECL * PFIECTASKENABLEWATCHDOG) (RTS_HANDLE hIecTask);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKENABLEWATCHDOG_NOTIMPLEMENTED)
	#define USE_IecTaskEnableWatchdog
	#define EXT_IecTaskEnableWatchdog
	#define GET_IecTaskEnableWatchdog(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskEnableWatchdog(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskEnableWatchdog  FALSE
	#define EXP_IecTaskEnableWatchdog  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskEnableWatchdog
	#define EXT_IecTaskEnableWatchdog
	#define GET_IecTaskEnableWatchdog(fl)  CAL_CMGETAPI( "IecTaskEnableWatchdog" ) 
	#define CAL_IecTaskEnableWatchdog  IecTaskEnableWatchdog
	#define CHK_IecTaskEnableWatchdog  TRUE
	#define EXP_IecTaskEnableWatchdog  CAL_CMEXPAPI( "IecTaskEnableWatchdog" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskEnableWatchdog
	#define EXT_IecTaskEnableWatchdog
	#define GET_IecTaskEnableWatchdog(fl)  CAL_CMGETAPI( "IecTaskEnableWatchdog" ) 
	#define CAL_IecTaskEnableWatchdog  IecTaskEnableWatchdog
	#define CHK_IecTaskEnableWatchdog  TRUE
	#define EXP_IecTaskEnableWatchdog  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskEnableWatchdog", (RTS_UINTPTR)IecTaskEnableWatchdog, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskEnableWatchdog
	#define EXT_CmpIecTaskIecTaskEnableWatchdog
	#define GET_CmpIecTaskIecTaskEnableWatchdog  ERR_OK
	#define CAL_CmpIecTaskIecTaskEnableWatchdog(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskEnableWatchdog() : ((ICmpIecTask*)p0)->IIecTaskEnableWatchdog())
	#define CHK_CmpIecTaskIecTaskEnableWatchdog  (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskEnableWatchdog  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskEnableWatchdog
	#define EXT_IecTaskEnableWatchdog
	#define GET_IecTaskEnableWatchdog(fl)  CAL_CMGETAPI( "IecTaskEnableWatchdog" ) 
	#define CAL_IecTaskEnableWatchdog(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskEnableWatchdog() : ((ICmpIecTask*)p0)->IIecTaskEnableWatchdog())
	#define CHK_IecTaskEnableWatchdog  (pICmpIecTask != NULL)
	#define EXP_IecTaskEnableWatchdog  CAL_CMEXPAPI( "IecTaskEnableWatchdog" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskEnableWatchdog  PFIECTASKENABLEWATCHDOG pfIecTaskEnableWatchdog;
	#define EXT_IecTaskEnableWatchdog  extern PFIECTASKENABLEWATCHDOG pfIecTaskEnableWatchdog;
	#define GET_IecTaskEnableWatchdog(fl)  s_pfCMGetAPI2( "IecTaskEnableWatchdog", (RTS_VOID_FCTPTR *)&pfIecTaskEnableWatchdog, (fl), 0, 0)
	#define CAL_IecTaskEnableWatchdog  pfIecTaskEnableWatchdog
	#define CHK_IecTaskEnableWatchdog  (pfIecTaskEnableWatchdog != NULL)
	#define EXP_IecTaskEnableWatchdog  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskEnableWatchdog", (RTS_UINTPTR)IecTaskEnableWatchdog, 0, 0) 
#endif




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
RTS_RESULT CDECL IecTaskDisableWatchdog(RTS_HANDLE hIecTask);
typedef RTS_RESULT (CDECL * PFIECTASKDISABLEWATCHDOG) (RTS_HANDLE hIecTask);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKDISABLEWATCHDOG_NOTIMPLEMENTED)
	#define USE_IecTaskDisableWatchdog
	#define EXT_IecTaskDisableWatchdog
	#define GET_IecTaskDisableWatchdog(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskDisableWatchdog(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskDisableWatchdog  FALSE
	#define EXP_IecTaskDisableWatchdog  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskDisableWatchdog
	#define EXT_IecTaskDisableWatchdog
	#define GET_IecTaskDisableWatchdog(fl)  CAL_CMGETAPI( "IecTaskDisableWatchdog" ) 
	#define CAL_IecTaskDisableWatchdog  IecTaskDisableWatchdog
	#define CHK_IecTaskDisableWatchdog  TRUE
	#define EXP_IecTaskDisableWatchdog  CAL_CMEXPAPI( "IecTaskDisableWatchdog" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskDisableWatchdog
	#define EXT_IecTaskDisableWatchdog
	#define GET_IecTaskDisableWatchdog(fl)  CAL_CMGETAPI( "IecTaskDisableWatchdog" ) 
	#define CAL_IecTaskDisableWatchdog  IecTaskDisableWatchdog
	#define CHK_IecTaskDisableWatchdog  TRUE
	#define EXP_IecTaskDisableWatchdog  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskDisableWatchdog", (RTS_UINTPTR)IecTaskDisableWatchdog, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskDisableWatchdog
	#define EXT_CmpIecTaskIecTaskDisableWatchdog
	#define GET_CmpIecTaskIecTaskDisableWatchdog  ERR_OK
	#define CAL_CmpIecTaskIecTaskDisableWatchdog(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskDisableWatchdog() : ((ICmpIecTask*)p0)->IIecTaskDisableWatchdog())
	#define CHK_CmpIecTaskIecTaskDisableWatchdog  (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskDisableWatchdog  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskDisableWatchdog
	#define EXT_IecTaskDisableWatchdog
	#define GET_IecTaskDisableWatchdog(fl)  CAL_CMGETAPI( "IecTaskDisableWatchdog" ) 
	#define CAL_IecTaskDisableWatchdog(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskDisableWatchdog() : ((ICmpIecTask*)p0)->IIecTaskDisableWatchdog())
	#define CHK_IecTaskDisableWatchdog  (pICmpIecTask != NULL)
	#define EXP_IecTaskDisableWatchdog  CAL_CMEXPAPI( "IecTaskDisableWatchdog" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskDisableWatchdog  PFIECTASKDISABLEWATCHDOG pfIecTaskDisableWatchdog;
	#define EXT_IecTaskDisableWatchdog  extern PFIECTASKDISABLEWATCHDOG pfIecTaskDisableWatchdog;
	#define GET_IecTaskDisableWatchdog(fl)  s_pfCMGetAPI2( "IecTaskDisableWatchdog", (RTS_VOID_FCTPTR *)&pfIecTaskDisableWatchdog, (fl), 0, 0)
	#define CAL_IecTaskDisableWatchdog  pfIecTaskDisableWatchdog
	#define CHK_IecTaskDisableWatchdog  (pfIecTaskDisableWatchdog != NULL)
	#define EXP_IecTaskDisableWatchdog  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskDisableWatchdog", (RTS_UINTPTR)IecTaskDisableWatchdog, 0, 0) 
#endif




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
RTS_RESULT CDECL IecTaskEnableWatchdog2(RTS_HANDLE hIecTask);
typedef RTS_RESULT (CDECL * PFIECTASKENABLEWATCHDOG2) (RTS_HANDLE hIecTask);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKENABLEWATCHDOG2_NOTIMPLEMENTED)
	#define USE_IecTaskEnableWatchdog2
	#define EXT_IecTaskEnableWatchdog2
	#define GET_IecTaskEnableWatchdog2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskEnableWatchdog2(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskEnableWatchdog2  FALSE
	#define EXP_IecTaskEnableWatchdog2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskEnableWatchdog2
	#define EXT_IecTaskEnableWatchdog2
	#define GET_IecTaskEnableWatchdog2(fl)  CAL_CMGETAPI( "IecTaskEnableWatchdog2" ) 
	#define CAL_IecTaskEnableWatchdog2  IecTaskEnableWatchdog2
	#define CHK_IecTaskEnableWatchdog2  TRUE
	#define EXP_IecTaskEnableWatchdog2  CAL_CMEXPAPI( "IecTaskEnableWatchdog2" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskEnableWatchdog2
	#define EXT_IecTaskEnableWatchdog2
	#define GET_IecTaskEnableWatchdog2(fl)  CAL_CMGETAPI( "IecTaskEnableWatchdog2" ) 
	#define CAL_IecTaskEnableWatchdog2  IecTaskEnableWatchdog2
	#define CHK_IecTaskEnableWatchdog2  TRUE
	#define EXP_IecTaskEnableWatchdog2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskEnableWatchdog2", (RTS_UINTPTR)IecTaskEnableWatchdog2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskEnableWatchdog2
	#define EXT_CmpIecTaskIecTaskEnableWatchdog2
	#define GET_CmpIecTaskIecTaskEnableWatchdog2  ERR_OK
	#define CAL_CmpIecTaskIecTaskEnableWatchdog2(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskEnableWatchdog2() : ((ICmpIecTask*)p0)->IIecTaskEnableWatchdog2())
	#define CHK_CmpIecTaskIecTaskEnableWatchdog2  (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskEnableWatchdog2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskEnableWatchdog2
	#define EXT_IecTaskEnableWatchdog2
	#define GET_IecTaskEnableWatchdog2(fl)  CAL_CMGETAPI( "IecTaskEnableWatchdog2" ) 
	#define CAL_IecTaskEnableWatchdog2(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskEnableWatchdog2() : ((ICmpIecTask*)p0)->IIecTaskEnableWatchdog2())
	#define CHK_IecTaskEnableWatchdog2  (pICmpIecTask != NULL)
	#define EXP_IecTaskEnableWatchdog2  CAL_CMEXPAPI( "IecTaskEnableWatchdog2" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskEnableWatchdog2  PFIECTASKENABLEWATCHDOG2 pfIecTaskEnableWatchdog2;
	#define EXT_IecTaskEnableWatchdog2  extern PFIECTASKENABLEWATCHDOG2 pfIecTaskEnableWatchdog2;
	#define GET_IecTaskEnableWatchdog2(fl)  s_pfCMGetAPI2( "IecTaskEnableWatchdog2", (RTS_VOID_FCTPTR *)&pfIecTaskEnableWatchdog2, (fl), 0, 0)
	#define CAL_IecTaskEnableWatchdog2  pfIecTaskEnableWatchdog2
	#define CHK_IecTaskEnableWatchdog2  (pfIecTaskEnableWatchdog2 != NULL)
	#define EXP_IecTaskEnableWatchdog2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskEnableWatchdog2", (RTS_UINTPTR)IecTaskEnableWatchdog2, 0, 0) 
#endif




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
RTS_RESULT CDECL IecTaskDisableWatchdog2(RTS_HANDLE hIecTask);
typedef RTS_RESULT (CDECL * PFIECTASKDISABLEWATCHDOG2) (RTS_HANDLE hIecTask);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKDISABLEWATCHDOG2_NOTIMPLEMENTED)
	#define USE_IecTaskDisableWatchdog2
	#define EXT_IecTaskDisableWatchdog2
	#define GET_IecTaskDisableWatchdog2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskDisableWatchdog2(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskDisableWatchdog2  FALSE
	#define EXP_IecTaskDisableWatchdog2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskDisableWatchdog2
	#define EXT_IecTaskDisableWatchdog2
	#define GET_IecTaskDisableWatchdog2(fl)  CAL_CMGETAPI( "IecTaskDisableWatchdog2" ) 
	#define CAL_IecTaskDisableWatchdog2  IecTaskDisableWatchdog2
	#define CHK_IecTaskDisableWatchdog2  TRUE
	#define EXP_IecTaskDisableWatchdog2  CAL_CMEXPAPI( "IecTaskDisableWatchdog2" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskDisableWatchdog2
	#define EXT_IecTaskDisableWatchdog2
	#define GET_IecTaskDisableWatchdog2(fl)  CAL_CMGETAPI( "IecTaskDisableWatchdog2" ) 
	#define CAL_IecTaskDisableWatchdog2  IecTaskDisableWatchdog2
	#define CHK_IecTaskDisableWatchdog2  TRUE
	#define EXP_IecTaskDisableWatchdog2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskDisableWatchdog2", (RTS_UINTPTR)IecTaskDisableWatchdog2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskDisableWatchdog2
	#define EXT_CmpIecTaskIecTaskDisableWatchdog2
	#define GET_CmpIecTaskIecTaskDisableWatchdog2  ERR_OK
	#define CAL_CmpIecTaskIecTaskDisableWatchdog2(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskDisableWatchdog2() : ((ICmpIecTask*)p0)->IIecTaskDisableWatchdog2())
	#define CHK_CmpIecTaskIecTaskDisableWatchdog2  (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskDisableWatchdog2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskDisableWatchdog2
	#define EXT_IecTaskDisableWatchdog2
	#define GET_IecTaskDisableWatchdog2(fl)  CAL_CMGETAPI( "IecTaskDisableWatchdog2" ) 
	#define CAL_IecTaskDisableWatchdog2(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskDisableWatchdog2() : ((ICmpIecTask*)p0)->IIecTaskDisableWatchdog2())
	#define CHK_IecTaskDisableWatchdog2  (pICmpIecTask != NULL)
	#define EXP_IecTaskDisableWatchdog2  CAL_CMEXPAPI( "IecTaskDisableWatchdog2" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskDisableWatchdog2  PFIECTASKDISABLEWATCHDOG2 pfIecTaskDisableWatchdog2;
	#define EXT_IecTaskDisableWatchdog2  extern PFIECTASKDISABLEWATCHDOG2 pfIecTaskDisableWatchdog2;
	#define GET_IecTaskDisableWatchdog2(fl)  s_pfCMGetAPI2( "IecTaskDisableWatchdog2", (RTS_VOID_FCTPTR *)&pfIecTaskDisableWatchdog2, (fl), 0, 0)
	#define CAL_IecTaskDisableWatchdog2  pfIecTaskDisableWatchdog2
	#define CHK_IecTaskDisableWatchdog2  (pfIecTaskDisableWatchdog2 != NULL)
	#define EXP_IecTaskDisableWatchdog2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskDisableWatchdog2", (RTS_UINTPTR)IecTaskDisableWatchdog2, 0, 0) 
#endif




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
RTS_RESULT CDECL IecTaskCheckWatchdog(RTS_HANDLE hIecTask, RTS_SYSTIME *ptActUs);
typedef RTS_RESULT (CDECL * PFIECTASKCHECKWATCHDOG) (RTS_HANDLE hIecTask, RTS_SYSTIME *ptActUs);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKCHECKWATCHDOG_NOTIMPLEMENTED)
	#define USE_IecTaskCheckWatchdog
	#define EXT_IecTaskCheckWatchdog
	#define GET_IecTaskCheckWatchdog(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskCheckWatchdog(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskCheckWatchdog  FALSE
	#define EXP_IecTaskCheckWatchdog  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskCheckWatchdog
	#define EXT_IecTaskCheckWatchdog
	#define GET_IecTaskCheckWatchdog(fl)  CAL_CMGETAPI( "IecTaskCheckWatchdog" ) 
	#define CAL_IecTaskCheckWatchdog  IecTaskCheckWatchdog
	#define CHK_IecTaskCheckWatchdog  TRUE
	#define EXP_IecTaskCheckWatchdog  CAL_CMEXPAPI( "IecTaskCheckWatchdog" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskCheckWatchdog
	#define EXT_IecTaskCheckWatchdog
	#define GET_IecTaskCheckWatchdog(fl)  CAL_CMGETAPI( "IecTaskCheckWatchdog" ) 
	#define CAL_IecTaskCheckWatchdog  IecTaskCheckWatchdog
	#define CHK_IecTaskCheckWatchdog  TRUE
	#define EXP_IecTaskCheckWatchdog  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskCheckWatchdog", (RTS_UINTPTR)IecTaskCheckWatchdog, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskCheckWatchdog
	#define EXT_CmpIecTaskIecTaskCheckWatchdog
	#define GET_CmpIecTaskIecTaskCheckWatchdog  ERR_OK
	#define CAL_CmpIecTaskIecTaskCheckWatchdog(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskCheckWatchdog(p1) : ((ICmpIecTask*)p0)->IIecTaskCheckWatchdog(p1))
	#define CHK_CmpIecTaskIecTaskCheckWatchdog  (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskCheckWatchdog  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskCheckWatchdog
	#define EXT_IecTaskCheckWatchdog
	#define GET_IecTaskCheckWatchdog(fl)  CAL_CMGETAPI( "IecTaskCheckWatchdog" ) 
	#define CAL_IecTaskCheckWatchdog(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskCheckWatchdog(p1) : ((ICmpIecTask*)p0)->IIecTaskCheckWatchdog(p1))
	#define CHK_IecTaskCheckWatchdog  (pICmpIecTask != NULL)
	#define EXP_IecTaskCheckWatchdog  CAL_CMEXPAPI( "IecTaskCheckWatchdog" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskCheckWatchdog  PFIECTASKCHECKWATCHDOG pfIecTaskCheckWatchdog;
	#define EXT_IecTaskCheckWatchdog  extern PFIECTASKCHECKWATCHDOG pfIecTaskCheckWatchdog;
	#define GET_IecTaskCheckWatchdog(fl)  s_pfCMGetAPI2( "IecTaskCheckWatchdog", (RTS_VOID_FCTPTR *)&pfIecTaskCheckWatchdog, (fl), 0, 0)
	#define CAL_IecTaskCheckWatchdog  pfIecTaskCheckWatchdog
	#define CHK_IecTaskCheckWatchdog  (pfIecTaskCheckWatchdog != NULL)
	#define EXP_IecTaskCheckWatchdog  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskCheckWatchdog", (RTS_UINTPTR)IecTaskCheckWatchdog, 0, 0) 
#endif




/**
 * <description>Get the first IEC task in the specified application</description>
 * <param name="pszAppName" type="IN">Application name, to which the task is bound</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="pResult" type="ERR_OK">Task found</errorcode>
 * <errorcode name="pResult" type="ERR_NO_OBJECT">No task found</errorcode>
 * <errorcode name="pResult" type="ERR_PARAMETER">Application name was NULL</errorcode>
 * <result>Handle to the task or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL IecTaskGetFirst(char *pszAppName, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECTASKGETFIRST) (char *pszAppName, RTS_RESULT *pResult);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKGETFIRST_NOTIMPLEMENTED)
	#define USE_IecTaskGetFirst
	#define EXT_IecTaskGetFirst
	#define GET_IecTaskGetFirst(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskGetFirst(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecTaskGetFirst  FALSE
	#define EXP_IecTaskGetFirst  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskGetFirst
	#define EXT_IecTaskGetFirst
	#define GET_IecTaskGetFirst(fl)  CAL_CMGETAPI( "IecTaskGetFirst" ) 
	#define CAL_IecTaskGetFirst  IecTaskGetFirst
	#define CHK_IecTaskGetFirst  TRUE
	#define EXP_IecTaskGetFirst  CAL_CMEXPAPI( "IecTaskGetFirst" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskGetFirst
	#define EXT_IecTaskGetFirst
	#define GET_IecTaskGetFirst(fl)  CAL_CMGETAPI( "IecTaskGetFirst" ) 
	#define CAL_IecTaskGetFirst  IecTaskGetFirst
	#define CHK_IecTaskGetFirst  TRUE
	#define EXP_IecTaskGetFirst  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetFirst", (RTS_UINTPTR)IecTaskGetFirst, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskGetFirst
	#define EXT_CmpIecTaskIecTaskGetFirst
	#define GET_CmpIecTaskIecTaskGetFirst  ERR_OK
	#define CAL_CmpIecTaskIecTaskGetFirst pICmpIecTask->IIecTaskGetFirst
	#define CHK_CmpIecTaskIecTaskGetFirst (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskGetFirst  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskGetFirst
	#define EXT_IecTaskGetFirst
	#define GET_IecTaskGetFirst(fl)  CAL_CMGETAPI( "IecTaskGetFirst" ) 
	#define CAL_IecTaskGetFirst pICmpIecTask->IIecTaskGetFirst
	#define CHK_IecTaskGetFirst (pICmpIecTask != NULL)
	#define EXP_IecTaskGetFirst  CAL_CMEXPAPI( "IecTaskGetFirst" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskGetFirst  PFIECTASKGETFIRST pfIecTaskGetFirst;
	#define EXT_IecTaskGetFirst  extern PFIECTASKGETFIRST pfIecTaskGetFirst;
	#define GET_IecTaskGetFirst(fl)  s_pfCMGetAPI2( "IecTaskGetFirst", (RTS_VOID_FCTPTR *)&pfIecTaskGetFirst, (fl), 0, 0)
	#define CAL_IecTaskGetFirst  pfIecTaskGetFirst
	#define CHK_IecTaskGetFirst  (pfIecTaskGetFirst != NULL)
	#define EXP_IecTaskGetFirst  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetFirst", (RTS_UINTPTR)IecTaskGetFirst, 0, 0) 
#endif




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
RTS_HANDLE CDECL IecTaskGetNext(char *pszAppName, RTS_HANDLE hPrevIecTask, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECTASKGETNEXT) (char *pszAppName, RTS_HANDLE hPrevIecTask, RTS_RESULT *pResult);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKGETNEXT_NOTIMPLEMENTED)
	#define USE_IecTaskGetNext
	#define EXT_IecTaskGetNext
	#define GET_IecTaskGetNext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskGetNext(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecTaskGetNext  FALSE
	#define EXP_IecTaskGetNext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskGetNext
	#define EXT_IecTaskGetNext
	#define GET_IecTaskGetNext(fl)  CAL_CMGETAPI( "IecTaskGetNext" ) 
	#define CAL_IecTaskGetNext  IecTaskGetNext
	#define CHK_IecTaskGetNext  TRUE
	#define EXP_IecTaskGetNext  CAL_CMEXPAPI( "IecTaskGetNext" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskGetNext
	#define EXT_IecTaskGetNext
	#define GET_IecTaskGetNext(fl)  CAL_CMGETAPI( "IecTaskGetNext" ) 
	#define CAL_IecTaskGetNext  IecTaskGetNext
	#define CHK_IecTaskGetNext  TRUE
	#define EXP_IecTaskGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetNext", (RTS_UINTPTR)IecTaskGetNext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskGetNext
	#define EXT_CmpIecTaskIecTaskGetNext
	#define GET_CmpIecTaskIecTaskGetNext  ERR_OK
	#define CAL_CmpIecTaskIecTaskGetNext pICmpIecTask->IIecTaskGetNext
	#define CHK_CmpIecTaskIecTaskGetNext (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskGetNext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskGetNext
	#define EXT_IecTaskGetNext
	#define GET_IecTaskGetNext(fl)  CAL_CMGETAPI( "IecTaskGetNext" ) 
	#define CAL_IecTaskGetNext pICmpIecTask->IIecTaskGetNext
	#define CHK_IecTaskGetNext (pICmpIecTask != NULL)
	#define EXP_IecTaskGetNext  CAL_CMEXPAPI( "IecTaskGetNext" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskGetNext  PFIECTASKGETNEXT pfIecTaskGetNext;
	#define EXT_IecTaskGetNext  extern PFIECTASKGETNEXT pfIecTaskGetNext;
	#define GET_IecTaskGetNext(fl)  s_pfCMGetAPI2( "IecTaskGetNext", (RTS_VOID_FCTPTR *)&pfIecTaskGetNext, (fl), 0, 0)
	#define CAL_IecTaskGetNext  pfIecTaskGetNext
	#define CHK_IecTaskGetNext  (pfIecTaskGetNext != NULL)
	#define EXP_IecTaskGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetNext", (RTS_UINTPTR)IecTaskGetNext, 0, 0) 
#endif




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
RTS_HANDLE CDECL IecTaskGetFirst2(APPLICATION *pApp, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECTASKGETFIRST2) (APPLICATION *pApp, RTS_RESULT *pResult);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKGETFIRST2_NOTIMPLEMENTED)
	#define USE_IecTaskGetFirst2
	#define EXT_IecTaskGetFirst2
	#define GET_IecTaskGetFirst2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskGetFirst2(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecTaskGetFirst2  FALSE
	#define EXP_IecTaskGetFirst2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskGetFirst2
	#define EXT_IecTaskGetFirst2
	#define GET_IecTaskGetFirst2(fl)  CAL_CMGETAPI( "IecTaskGetFirst2" ) 
	#define CAL_IecTaskGetFirst2  IecTaskGetFirst2
	#define CHK_IecTaskGetFirst2  TRUE
	#define EXP_IecTaskGetFirst2  CAL_CMEXPAPI( "IecTaskGetFirst2" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskGetFirst2
	#define EXT_IecTaskGetFirst2
	#define GET_IecTaskGetFirst2(fl)  CAL_CMGETAPI( "IecTaskGetFirst2" ) 
	#define CAL_IecTaskGetFirst2  IecTaskGetFirst2
	#define CHK_IecTaskGetFirst2  TRUE
	#define EXP_IecTaskGetFirst2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetFirst2", (RTS_UINTPTR)IecTaskGetFirst2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskGetFirst2
	#define EXT_CmpIecTaskIecTaskGetFirst2
	#define GET_CmpIecTaskIecTaskGetFirst2  ERR_OK
	#define CAL_CmpIecTaskIecTaskGetFirst2 pICmpIecTask->IIecTaskGetFirst2
	#define CHK_CmpIecTaskIecTaskGetFirst2 (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskGetFirst2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskGetFirst2
	#define EXT_IecTaskGetFirst2
	#define GET_IecTaskGetFirst2(fl)  CAL_CMGETAPI( "IecTaskGetFirst2" ) 
	#define CAL_IecTaskGetFirst2 pICmpIecTask->IIecTaskGetFirst2
	#define CHK_IecTaskGetFirst2 (pICmpIecTask != NULL)
	#define EXP_IecTaskGetFirst2  CAL_CMEXPAPI( "IecTaskGetFirst2" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskGetFirst2  PFIECTASKGETFIRST2 pfIecTaskGetFirst2;
	#define EXT_IecTaskGetFirst2  extern PFIECTASKGETFIRST2 pfIecTaskGetFirst2;
	#define GET_IecTaskGetFirst2(fl)  s_pfCMGetAPI2( "IecTaskGetFirst2", (RTS_VOID_FCTPTR *)&pfIecTaskGetFirst2, (fl), 0, 0)
	#define CAL_IecTaskGetFirst2  pfIecTaskGetFirst2
	#define CHK_IecTaskGetFirst2  (pfIecTaskGetFirst2 != NULL)
	#define EXP_IecTaskGetFirst2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetFirst2", (RTS_UINTPTR)IecTaskGetFirst2, 0, 0) 
#endif




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
RTS_HANDLE CDECL IecTaskGetNext2(APPLICATION *pApp, RTS_HANDLE hPrevIecTask, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECTASKGETNEXT2) (APPLICATION *pApp, RTS_HANDLE hPrevIecTask, RTS_RESULT *pResult);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKGETNEXT2_NOTIMPLEMENTED)
	#define USE_IecTaskGetNext2
	#define EXT_IecTaskGetNext2
	#define GET_IecTaskGetNext2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskGetNext2(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecTaskGetNext2  FALSE
	#define EXP_IecTaskGetNext2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskGetNext2
	#define EXT_IecTaskGetNext2
	#define GET_IecTaskGetNext2(fl)  CAL_CMGETAPI( "IecTaskGetNext2" ) 
	#define CAL_IecTaskGetNext2  IecTaskGetNext2
	#define CHK_IecTaskGetNext2  TRUE
	#define EXP_IecTaskGetNext2  CAL_CMEXPAPI( "IecTaskGetNext2" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskGetNext2
	#define EXT_IecTaskGetNext2
	#define GET_IecTaskGetNext2(fl)  CAL_CMGETAPI( "IecTaskGetNext2" ) 
	#define CAL_IecTaskGetNext2  IecTaskGetNext2
	#define CHK_IecTaskGetNext2  TRUE
	#define EXP_IecTaskGetNext2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetNext2", (RTS_UINTPTR)IecTaskGetNext2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskGetNext2
	#define EXT_CmpIecTaskIecTaskGetNext2
	#define GET_CmpIecTaskIecTaskGetNext2  ERR_OK
	#define CAL_CmpIecTaskIecTaskGetNext2 pICmpIecTask->IIecTaskGetNext2
	#define CHK_CmpIecTaskIecTaskGetNext2 (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskGetNext2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskGetNext2
	#define EXT_IecTaskGetNext2
	#define GET_IecTaskGetNext2(fl)  CAL_CMGETAPI( "IecTaskGetNext2" ) 
	#define CAL_IecTaskGetNext2 pICmpIecTask->IIecTaskGetNext2
	#define CHK_IecTaskGetNext2 (pICmpIecTask != NULL)
	#define EXP_IecTaskGetNext2  CAL_CMEXPAPI( "IecTaskGetNext2" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskGetNext2  PFIECTASKGETNEXT2 pfIecTaskGetNext2;
	#define EXT_IecTaskGetNext2  extern PFIECTASKGETNEXT2 pfIecTaskGetNext2;
	#define GET_IecTaskGetNext2(fl)  s_pfCMGetAPI2( "IecTaskGetNext2", (RTS_VOID_FCTPTR *)&pfIecTaskGetNext2, (fl), 0, 0)
	#define CAL_IecTaskGetNext2  pfIecTaskGetNext2
	#define CHK_IecTaskGetNext2  (pfIecTaskGetNext2 != NULL)
	#define EXP_IecTaskGetNext2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskGetNext2", (RTS_UINTPTR)IecTaskGetNext2, 0, 0) 
#endif




/**
 * <description>Reload a specified IEC task. Reload means here: Delete the task at the actual position and create it newly.</description>
 * <param name="hIecTask" type="IN">Handle to the task to reload</param>
 * <param name="ulTimeoutMs" type="IN">Timeout in milliseconds to wait, until the task deleted itself. Timeout can be one of the following predefined values:
 *		RTS_TIMEOUT_DEFAULT: Default timeout to delete the task
 *		RTS_TIMEOUT_NO_WAIT: Immediate deletion of the task</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the new created task </result>
 */
RTS_HANDLE CDECL IecTaskReload(RTS_HANDLE hIecTask, RTS_UI32 ulTimeoutMs, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECTASKRELOAD) (RTS_HANDLE hIecTask, RTS_UI32 ulTimeoutMs, RTS_RESULT *pResult);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKRELOAD_NOTIMPLEMENTED)
	#define USE_IecTaskReload
	#define EXT_IecTaskReload
	#define GET_IecTaskReload(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskReload(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecTaskReload  FALSE
	#define EXP_IecTaskReload  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskReload
	#define EXT_IecTaskReload
	#define GET_IecTaskReload(fl)  CAL_CMGETAPI( "IecTaskReload" ) 
	#define CAL_IecTaskReload  IecTaskReload
	#define CHK_IecTaskReload  TRUE
	#define EXP_IecTaskReload  CAL_CMEXPAPI( "IecTaskReload" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskReload
	#define EXT_IecTaskReload
	#define GET_IecTaskReload(fl)  CAL_CMGETAPI( "IecTaskReload" ) 
	#define CAL_IecTaskReload  IecTaskReload
	#define CHK_IecTaskReload  TRUE
	#define EXP_IecTaskReload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskReload", (RTS_UINTPTR)IecTaskReload, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskReload
	#define EXT_CmpIecTaskIecTaskReload
	#define GET_CmpIecTaskIecTaskReload  ERR_OK
	#define CAL_CmpIecTaskIecTaskReload pICmpIecTask->IIecTaskReload
	#define CHK_CmpIecTaskIecTaskReload (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskReload  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskReload
	#define EXT_IecTaskReload
	#define GET_IecTaskReload(fl)  CAL_CMGETAPI( "IecTaskReload" ) 
	#define CAL_IecTaskReload pICmpIecTask->IIecTaskReload
	#define CHK_IecTaskReload (pICmpIecTask != NULL)
	#define EXP_IecTaskReload  CAL_CMEXPAPI( "IecTaskReload" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskReload  PFIECTASKRELOAD pfIecTaskReload;
	#define EXT_IecTaskReload  extern PFIECTASKRELOAD pfIecTaskReload;
	#define GET_IecTaskReload(fl)  s_pfCMGetAPI2( "IecTaskReload", (RTS_VOID_FCTPTR *)&pfIecTaskReload, (fl), 0, 0)
	#define CAL_IecTaskReload  pfIecTaskReload
	#define CHK_IecTaskReload  (pfIecTaskReload != NULL)
	#define EXP_IecTaskReload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskReload", (RTS_UINTPTR)IecTaskReload, 0, 0) 
#endif




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
int CDECL IecTaskCalculateId(APPLICATION *pApp, int iIndex, RTS_RESULT *pResult);
typedef int (CDECL * PFIECTASKCALCULATEID) (APPLICATION *pApp, int iIndex, RTS_RESULT *pResult);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKCALCULATEID_NOTIMPLEMENTED)
	#define USE_IecTaskCalculateId
	#define EXT_IecTaskCalculateId
	#define GET_IecTaskCalculateId(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskCalculateId(p0,p1,p2)  (int)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskCalculateId  FALSE
	#define EXP_IecTaskCalculateId  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskCalculateId
	#define EXT_IecTaskCalculateId
	#define GET_IecTaskCalculateId(fl)  CAL_CMGETAPI( "IecTaskCalculateId" ) 
	#define CAL_IecTaskCalculateId  IecTaskCalculateId
	#define CHK_IecTaskCalculateId  TRUE
	#define EXP_IecTaskCalculateId  CAL_CMEXPAPI( "IecTaskCalculateId" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskCalculateId
	#define EXT_IecTaskCalculateId
	#define GET_IecTaskCalculateId(fl)  CAL_CMGETAPI( "IecTaskCalculateId" ) 
	#define CAL_IecTaskCalculateId  IecTaskCalculateId
	#define CHK_IecTaskCalculateId  TRUE
	#define EXP_IecTaskCalculateId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskCalculateId", (RTS_UINTPTR)IecTaskCalculateId, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskCalculateId
	#define EXT_CmpIecTaskIecTaskCalculateId
	#define GET_CmpIecTaskIecTaskCalculateId  ERR_OK
	#define CAL_CmpIecTaskIecTaskCalculateId pICmpIecTask->IIecTaskCalculateId
	#define CHK_CmpIecTaskIecTaskCalculateId (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskCalculateId  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskCalculateId
	#define EXT_IecTaskCalculateId
	#define GET_IecTaskCalculateId(fl)  CAL_CMGETAPI( "IecTaskCalculateId" ) 
	#define CAL_IecTaskCalculateId pICmpIecTask->IIecTaskCalculateId
	#define CHK_IecTaskCalculateId (pICmpIecTask != NULL)
	#define EXP_IecTaskCalculateId  CAL_CMEXPAPI( "IecTaskCalculateId" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskCalculateId  PFIECTASKCALCULATEID pfIecTaskCalculateId;
	#define EXT_IecTaskCalculateId  extern PFIECTASKCALCULATEID pfIecTaskCalculateId;
	#define GET_IecTaskCalculateId(fl)  s_pfCMGetAPI2( "IecTaskCalculateId", (RTS_VOID_FCTPTR *)&pfIecTaskCalculateId, (fl), 0, 0)
	#define CAL_IecTaskCalculateId  pfIecTaskCalculateId
	#define CHK_IecTaskCalculateId  (pfIecTaskCalculateId != NULL)
	#define EXP_IecTaskCalculateId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskCalculateId", (RTS_UINTPTR)IecTaskCalculateId, 0, 0) 
#endif




/**
 * <description>Function to make a busy wait, while at least one task of the specified application is active</description>
 * <param name="pApp" type="IN">Handle of the application that contains the tasks to check. If pApp == NULL, all IEC tasks are checked.</param>
 * <param name="ulTimeoutMs" type="IN">Timeout in milliseconds to wait for deleting the task</param>
 * <result>Error code:</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">No task is active</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">At least one task is active after timeout</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Application name was NULL</errorcode>
 */
RTS_RESULT CDECL IecTaskWaitTasksActive(APPLICATION *pApp, RTS_UI32 ulTimeoutMs);
typedef RTS_RESULT (CDECL * PFIECTASKWAITTASKSACTIVE) (APPLICATION *pApp, RTS_UI32 ulTimeoutMs);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKWAITTASKSACTIVE_NOTIMPLEMENTED)
	#define USE_IecTaskWaitTasksActive
	#define EXT_IecTaskWaitTasksActive
	#define GET_IecTaskWaitTasksActive(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskWaitTasksActive(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskWaitTasksActive  FALSE
	#define EXP_IecTaskWaitTasksActive  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskWaitTasksActive
	#define EXT_IecTaskWaitTasksActive
	#define GET_IecTaskWaitTasksActive(fl)  CAL_CMGETAPI( "IecTaskWaitTasksActive" ) 
	#define CAL_IecTaskWaitTasksActive  IecTaskWaitTasksActive
	#define CHK_IecTaskWaitTasksActive  TRUE
	#define EXP_IecTaskWaitTasksActive  CAL_CMEXPAPI( "IecTaskWaitTasksActive" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskWaitTasksActive
	#define EXT_IecTaskWaitTasksActive
	#define GET_IecTaskWaitTasksActive(fl)  CAL_CMGETAPI( "IecTaskWaitTasksActive" ) 
	#define CAL_IecTaskWaitTasksActive  IecTaskWaitTasksActive
	#define CHK_IecTaskWaitTasksActive  TRUE
	#define EXP_IecTaskWaitTasksActive  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskWaitTasksActive", (RTS_UINTPTR)IecTaskWaitTasksActive, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskWaitTasksActive
	#define EXT_CmpIecTaskIecTaskWaitTasksActive
	#define GET_CmpIecTaskIecTaskWaitTasksActive  ERR_OK
	#define CAL_CmpIecTaskIecTaskWaitTasksActive pICmpIecTask->IIecTaskWaitTasksActive
	#define CHK_CmpIecTaskIecTaskWaitTasksActive (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskWaitTasksActive  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskWaitTasksActive
	#define EXT_IecTaskWaitTasksActive
	#define GET_IecTaskWaitTasksActive(fl)  CAL_CMGETAPI( "IecTaskWaitTasksActive" ) 
	#define CAL_IecTaskWaitTasksActive pICmpIecTask->IIecTaskWaitTasksActive
	#define CHK_IecTaskWaitTasksActive (pICmpIecTask != NULL)
	#define EXP_IecTaskWaitTasksActive  CAL_CMEXPAPI( "IecTaskWaitTasksActive" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskWaitTasksActive  PFIECTASKWAITTASKSACTIVE pfIecTaskWaitTasksActive;
	#define EXT_IecTaskWaitTasksActive  extern PFIECTASKWAITTASKSACTIVE pfIecTaskWaitTasksActive;
	#define GET_IecTaskWaitTasksActive(fl)  s_pfCMGetAPI2( "IecTaskWaitTasksActive", (RTS_VOID_FCTPTR *)&pfIecTaskWaitTasksActive, (fl), 0, 0)
	#define CAL_IecTaskWaitTasksActive  pfIecTaskWaitTasksActive
	#define CHK_IecTaskWaitTasksActive  (pfIecTaskWaitTasksActive != NULL)
	#define EXP_IecTaskWaitTasksActive  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskWaitTasksActive", (RTS_UINTPTR)IecTaskWaitTasksActive, 0, 0) 
#endif




/**
 * <description>Activates a single cycle on every cyclic and freewheeling task of the specified application</description>
 * <param name="pApp" type="IN">Handle of the application to do a single cycle</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">No task is active</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Application name was NULL</errorcode>
 */
RTS_RESULT CDECL IecTaskSingleCycle(APPLICATION *pApp);
typedef RTS_RESULT (CDECL * PFIECTASKSINGLECYCLE) (APPLICATION *pApp);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKSINGLECYCLE_NOTIMPLEMENTED)
	#define USE_IecTaskSingleCycle
	#define EXT_IecTaskSingleCycle
	#define GET_IecTaskSingleCycle(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskSingleCycle(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskSingleCycle  FALSE
	#define EXP_IecTaskSingleCycle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskSingleCycle
	#define EXT_IecTaskSingleCycle
	#define GET_IecTaskSingleCycle(fl)  CAL_CMGETAPI( "IecTaskSingleCycle" ) 
	#define CAL_IecTaskSingleCycle  IecTaskSingleCycle
	#define CHK_IecTaskSingleCycle  TRUE
	#define EXP_IecTaskSingleCycle  CAL_CMEXPAPI( "IecTaskSingleCycle" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskSingleCycle
	#define EXT_IecTaskSingleCycle
	#define GET_IecTaskSingleCycle(fl)  CAL_CMGETAPI( "IecTaskSingleCycle" ) 
	#define CAL_IecTaskSingleCycle  IecTaskSingleCycle
	#define CHK_IecTaskSingleCycle  TRUE
	#define EXP_IecTaskSingleCycle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskSingleCycle", (RTS_UINTPTR)IecTaskSingleCycle, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskSingleCycle
	#define EXT_CmpIecTaskIecTaskSingleCycle
	#define GET_CmpIecTaskIecTaskSingleCycle  ERR_OK
	#define CAL_CmpIecTaskIecTaskSingleCycle pICmpIecTask->IIecTaskSingleCycle
	#define CHK_CmpIecTaskIecTaskSingleCycle (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskSingleCycle  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskSingleCycle
	#define EXT_IecTaskSingleCycle
	#define GET_IecTaskSingleCycle(fl)  CAL_CMGETAPI( "IecTaskSingleCycle" ) 
	#define CAL_IecTaskSingleCycle pICmpIecTask->IIecTaskSingleCycle
	#define CHK_IecTaskSingleCycle (pICmpIecTask != NULL)
	#define EXP_IecTaskSingleCycle  CAL_CMEXPAPI( "IecTaskSingleCycle" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskSingleCycle  PFIECTASKSINGLECYCLE pfIecTaskSingleCycle;
	#define EXT_IecTaskSingleCycle  extern PFIECTASKSINGLECYCLE pfIecTaskSingleCycle;
	#define GET_IecTaskSingleCycle(fl)  s_pfCMGetAPI2( "IecTaskSingleCycle", (RTS_VOID_FCTPTR *)&pfIecTaskSingleCycle, (fl), 0, 0)
	#define CAL_IecTaskSingleCycle  pfIecTaskSingleCycle
	#define CHK_IecTaskSingleCycle  (pfIecTaskSingleCycle != NULL)
	#define EXP_IecTaskSingleCycle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskSingleCycle", (RTS_UINTPTR)IecTaskSingleCycle, 0, 0) 
#endif




/**
 * <description>Reset the task statistics of a task (see Task_Info member e.g. dwCycleTime, dwAverageCycleTime, etc.)</description>
 * <param name="hIecTask" type="IN">Handle to the task</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">No task is active</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Application name was NULL</errorcode>
 */
RTS_RESULT CDECL IecTaskResetStatistics(RTS_HANDLE hIecTask);
typedef RTS_RESULT (CDECL * PFIECTASKRESETSTATISTICS) (RTS_HANDLE hIecTask);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKRESETSTATISTICS_NOTIMPLEMENTED)
	#define USE_IecTaskResetStatistics
	#define EXT_IecTaskResetStatistics
	#define GET_IecTaskResetStatistics(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskResetStatistics(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskResetStatistics  FALSE
	#define EXP_IecTaskResetStatistics  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskResetStatistics
	#define EXT_IecTaskResetStatistics
	#define GET_IecTaskResetStatistics(fl)  CAL_CMGETAPI( "IecTaskResetStatistics" ) 
	#define CAL_IecTaskResetStatistics  IecTaskResetStatistics
	#define CHK_IecTaskResetStatistics  TRUE
	#define EXP_IecTaskResetStatistics  CAL_CMEXPAPI( "IecTaskResetStatistics" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskResetStatistics
	#define EXT_IecTaskResetStatistics
	#define GET_IecTaskResetStatistics(fl)  CAL_CMGETAPI( "IecTaskResetStatistics" ) 
	#define CAL_IecTaskResetStatistics  IecTaskResetStatistics
	#define CHK_IecTaskResetStatistics  TRUE
	#define EXP_IecTaskResetStatistics  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskResetStatistics", (RTS_UINTPTR)IecTaskResetStatistics, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskResetStatistics
	#define EXT_CmpIecTaskIecTaskResetStatistics
	#define GET_CmpIecTaskIecTaskResetStatistics  ERR_OK
	#define CAL_CmpIecTaskIecTaskResetStatistics pICmpIecTask->IIecTaskResetStatistics
	#define CHK_CmpIecTaskIecTaskResetStatistics (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskResetStatistics  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskResetStatistics
	#define EXT_IecTaskResetStatistics
	#define GET_IecTaskResetStatistics(fl)  CAL_CMGETAPI( "IecTaskResetStatistics" ) 
	#define CAL_IecTaskResetStatistics pICmpIecTask->IIecTaskResetStatistics
	#define CHK_IecTaskResetStatistics (pICmpIecTask != NULL)
	#define EXP_IecTaskResetStatistics  CAL_CMEXPAPI( "IecTaskResetStatistics" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskResetStatistics  PFIECTASKRESETSTATISTICS pfIecTaskResetStatistics;
	#define EXT_IecTaskResetStatistics  extern PFIECTASKRESETSTATISTICS pfIecTaskResetStatistics;
	#define GET_IecTaskResetStatistics(fl)  s_pfCMGetAPI2( "IecTaskResetStatistics", (RTS_VOID_FCTPTR *)&pfIecTaskResetStatistics, (fl), 0, 0)
	#define CAL_IecTaskResetStatistics  pfIecTaskResetStatistics
	#define CHK_IecTaskResetStatistics  (pfIecTaskResetStatistics != NULL)
	#define EXP_IecTaskResetStatistics  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskResetStatistics", (RTS_UINTPTR)IecTaskResetStatistics, 0, 0) 
#endif




/**
 * <description>Is called entering the debug handler, if an IEC task is halted on a breakpoint</description>
 * <param name="hIecTask" type="IN">Handle to the task, which enters the debug handler</param>
 * <result>Error code</result>
 */
RTS_RESULT CDECL IecTaskDebugHandlerEnter(RTS_HANDLE hIecTask);
typedef RTS_RESULT (CDECL * PFIECTASKDEBUGHANDLERENTER) (RTS_HANDLE hIecTask);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKDEBUGHANDLERENTER_NOTIMPLEMENTED)
	#define USE_IecTaskDebugHandlerEnter
	#define EXT_IecTaskDebugHandlerEnter
	#define GET_IecTaskDebugHandlerEnter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskDebugHandlerEnter(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskDebugHandlerEnter  FALSE
	#define EXP_IecTaskDebugHandlerEnter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskDebugHandlerEnter
	#define EXT_IecTaskDebugHandlerEnter
	#define GET_IecTaskDebugHandlerEnter(fl)  CAL_CMGETAPI( "IecTaskDebugHandlerEnter" ) 
	#define CAL_IecTaskDebugHandlerEnter  IecTaskDebugHandlerEnter
	#define CHK_IecTaskDebugHandlerEnter  TRUE
	#define EXP_IecTaskDebugHandlerEnter  CAL_CMEXPAPI( "IecTaskDebugHandlerEnter" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskDebugHandlerEnter
	#define EXT_IecTaskDebugHandlerEnter
	#define GET_IecTaskDebugHandlerEnter(fl)  CAL_CMGETAPI( "IecTaskDebugHandlerEnter" ) 
	#define CAL_IecTaskDebugHandlerEnter  IecTaskDebugHandlerEnter
	#define CHK_IecTaskDebugHandlerEnter  TRUE
	#define EXP_IecTaskDebugHandlerEnter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskDebugHandlerEnter", (RTS_UINTPTR)IecTaskDebugHandlerEnter, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskDebugHandlerEnter
	#define EXT_CmpIecTaskIecTaskDebugHandlerEnter
	#define GET_CmpIecTaskIecTaskDebugHandlerEnter  ERR_OK
	#define CAL_CmpIecTaskIecTaskDebugHandlerEnter(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskDebugHandlerEnter() : ((ICmpIecTask*)p0)->IIecTaskDebugHandlerEnter())
	#define CHK_CmpIecTaskIecTaskDebugHandlerEnter  (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskDebugHandlerEnter  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskDebugHandlerEnter
	#define EXT_IecTaskDebugHandlerEnter
	#define GET_IecTaskDebugHandlerEnter(fl)  CAL_CMGETAPI( "IecTaskDebugHandlerEnter" ) 
	#define CAL_IecTaskDebugHandlerEnter(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskDebugHandlerEnter() : ((ICmpIecTask*)p0)->IIecTaskDebugHandlerEnter())
	#define CHK_IecTaskDebugHandlerEnter  (pICmpIecTask != NULL)
	#define EXP_IecTaskDebugHandlerEnter  CAL_CMEXPAPI( "IecTaskDebugHandlerEnter" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskDebugHandlerEnter  PFIECTASKDEBUGHANDLERENTER pfIecTaskDebugHandlerEnter;
	#define EXT_IecTaskDebugHandlerEnter  extern PFIECTASKDEBUGHANDLERENTER pfIecTaskDebugHandlerEnter;
	#define GET_IecTaskDebugHandlerEnter(fl)  s_pfCMGetAPI2( "IecTaskDebugHandlerEnter", (RTS_VOID_FCTPTR *)&pfIecTaskDebugHandlerEnter, (fl), 0, 0)
	#define CAL_IecTaskDebugHandlerEnter  pfIecTaskDebugHandlerEnter
	#define CHK_IecTaskDebugHandlerEnter  (pfIecTaskDebugHandlerEnter != NULL)
	#define EXP_IecTaskDebugHandlerEnter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskDebugHandlerEnter", (RTS_UINTPTR)IecTaskDebugHandlerEnter, 0, 0) 
#endif




/**
 * <description>Is called leaving the debug handler, if an IEC task is leaving a breakpoint</description>
 * <param name="hIecTask" type="IN">Handle to the task, which leaves the debug handler</param>
 * <result>Error code</result>
 */
RTS_RESULT CDECL IecTaskDebugHandlerLeave(RTS_HANDLE hIecTask);
typedef RTS_RESULT (CDECL * PFIECTASKDEBUGHANDLERLEAVE) (RTS_HANDLE hIecTask);
#if defined(CMPIECTASK_NOTIMPLEMENTED) || defined(IECTASKDEBUGHANDLERLEAVE_NOTIMPLEMENTED)
	#define USE_IecTaskDebugHandlerLeave
	#define EXT_IecTaskDebugHandlerLeave
	#define GET_IecTaskDebugHandlerLeave(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecTaskDebugHandlerLeave(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecTaskDebugHandlerLeave  FALSE
	#define EXP_IecTaskDebugHandlerLeave  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecTaskDebugHandlerLeave
	#define EXT_IecTaskDebugHandlerLeave
	#define GET_IecTaskDebugHandlerLeave(fl)  CAL_CMGETAPI( "IecTaskDebugHandlerLeave" ) 
	#define CAL_IecTaskDebugHandlerLeave  IecTaskDebugHandlerLeave
	#define CHK_IecTaskDebugHandlerLeave  TRUE
	#define EXP_IecTaskDebugHandlerLeave  CAL_CMEXPAPI( "IecTaskDebugHandlerLeave" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECTASK_EXTERNAL)
	#define USE_IecTaskDebugHandlerLeave
	#define EXT_IecTaskDebugHandlerLeave
	#define GET_IecTaskDebugHandlerLeave(fl)  CAL_CMGETAPI( "IecTaskDebugHandlerLeave" ) 
	#define CAL_IecTaskDebugHandlerLeave  IecTaskDebugHandlerLeave
	#define CHK_IecTaskDebugHandlerLeave  TRUE
	#define EXP_IecTaskDebugHandlerLeave  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskDebugHandlerLeave", (RTS_UINTPTR)IecTaskDebugHandlerLeave, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecTaskIecTaskDebugHandlerLeave
	#define EXT_CmpIecTaskIecTaskDebugHandlerLeave
	#define GET_CmpIecTaskIecTaskDebugHandlerLeave  ERR_OK
	#define CAL_CmpIecTaskIecTaskDebugHandlerLeave(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskDebugHandlerLeave() : ((ICmpIecTask*)p0)->IIecTaskDebugHandlerLeave())
	#define CHK_CmpIecTaskIecTaskDebugHandlerLeave  (pICmpIecTask != NULL)
	#define EXP_CmpIecTaskIecTaskDebugHandlerLeave  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecTaskDebugHandlerLeave
	#define EXT_IecTaskDebugHandlerLeave
	#define GET_IecTaskDebugHandlerLeave(fl)  CAL_CMGETAPI( "IecTaskDebugHandlerLeave" ) 
	#define CAL_IecTaskDebugHandlerLeave(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpIecTask->IIecTaskDebugHandlerLeave() : ((ICmpIecTask*)p0)->IIecTaskDebugHandlerLeave())
	#define CHK_IecTaskDebugHandlerLeave  (pICmpIecTask != NULL)
	#define EXP_IecTaskDebugHandlerLeave  CAL_CMEXPAPI( "IecTaskDebugHandlerLeave" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecTaskDebugHandlerLeave  PFIECTASKDEBUGHANDLERLEAVE pfIecTaskDebugHandlerLeave;
	#define EXT_IecTaskDebugHandlerLeave  extern PFIECTASKDEBUGHANDLERLEAVE pfIecTaskDebugHandlerLeave;
	#define GET_IecTaskDebugHandlerLeave(fl)  s_pfCMGetAPI2( "IecTaskDebugHandlerLeave", (RTS_VOID_FCTPTR *)&pfIecTaskDebugHandlerLeave, (fl), 0, 0)
	#define CAL_IecTaskDebugHandlerLeave  pfIecTaskDebugHandlerLeave
	#define CHK_IecTaskDebugHandlerLeave  (pfIecTaskDebugHandlerLeave != NULL)
	#define EXP_IecTaskDebugHandlerLeave  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecTaskDebugHandlerLeave", (RTS_UINTPTR)IecTaskDebugHandlerLeave, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFIECTASKCREATE IIecTaskCreate;
 	PFIECTASKDELETE IIecTaskDelete;
 	PFIECTASKDELETE2 IIecTaskDelete2;
 	PFIECFREETASKS IIecFreeTasks;
 	PFIECFREETASKS2 IIecFreeTasks2;
 	PFIECTASKCYCLE IIecTaskCycle;
 	PFIECTASKUPDATEJITTERTIME IIecTaskUpdateJitterTime;
 	PFIECTASKUPDATECYCLETIME IIecTaskUpdateCycleTime;
 	PFIECTASKSRESETALLOWED IIecTasksResetAllowed;
 	PFIECTASKSPREPARERESET IIecTasksPrepareReset;
 	PFIECTASKSRESETDONE IIecTasksResetDone;
 	PFIECTASKGETWAITFORSTOPTIMEOUT IIecTaskGetWaitForStopTimeout;
 	PFIECTASKSWAITFORSTOP IIecTasksWaitForStop;
 	PFIECTASKINITOUTPUTS IIecTaskInitOutputs;
 	PFIECTASKENTEREXCLUSIVESECTION IIecTaskEnterExclusiveSection;
 	PFIECTASKLEAVEEXCLUSIVESECTION IIecTaskLeaveExclusiveSection;
 	PFIECTASKENTEREXCLUSIVESECTION2 IIecTaskEnterExclusiveSection2;
 	PFIECTASKTRYENTEREXCLUSIVESECTION2 IIecTaskTryEnterExclusiveSection2;
 	PFIECTASKLEAVEEXCLUSIVESECTION2 IIecTaskLeaveExclusiveSection2;
 	PFIECTASKREGISTERSLOTCALLBACKS IIecTaskRegisterSlotCallbacks;
 	PFIECTASKUNREGISTERSLOTCALLBACKS IIecTaskUnregisterSlotCallbacks;
 	PFIECTASKREGISTERSLOTCALLBACK IIecTaskRegisterSlotCallback;
 	PFIECTASKUNREGISTERSLOTCALLBACK IIecTaskUnregisterSlotCallback;
 	PFIECTASKGETDESC IIecTaskGetDesc;
 	PFIECTASKGETHANDLE IIecTaskGetHandle;
 	PFIECTASKGETCURRENT IIecTaskGetCurrent;
 	PFIECTASKDEBUGLOOP IIecTaskDebugLoop;
 	PFIECTASKDEBUGENTER IIecTaskDebugEnter;
 	PFIECTASKDEBUGLEAVE IIecTaskDebugLeave;
 	PFIECTASKSETCONTEXT IIecTaskSetContext;
 	PFIECTASKGETCONTEXT IIecTaskGetContext;
 	PFIECTASKEXCEPTIONHANDLER IIecTaskExceptionHandler;
 	PFIECTASKGETBYINDEX IIecTaskGetByIndex;
 	PFIECTASKGETHANDLEBYINDEX IIecTaskGetHandleByIndex;
 	PFIECTASKGETBYID IIecTaskGetById;
 	PFIECTASKGETNUMOFTASKS IIecTaskGetNumOfTasks;
 	PFIECTASKENABLESCHEDULINGALL IIecTaskEnableSchedulingAll;
 	PFIECTASKDISABLESCHEDULINGALL IIecTaskDisableSchedulingAll;
 	PFIECTASKENABLESCHEDULING IIecTaskEnableScheduling;
 	PFIECTASKDISABLESCHEDULING IIecTaskDisableScheduling;
 	PFIECTASKENABLEWATCHDOG IIecTaskEnableWatchdog;
 	PFIECTASKDISABLEWATCHDOG IIecTaskDisableWatchdog;
 	PFIECTASKENABLEWATCHDOG2 IIecTaskEnableWatchdog2;
 	PFIECTASKDISABLEWATCHDOG2 IIecTaskDisableWatchdog2;
 	PFIECTASKCHECKWATCHDOG IIecTaskCheckWatchdog;
 	PFIECTASKGETFIRST IIecTaskGetFirst;
 	PFIECTASKGETNEXT IIecTaskGetNext;
 	PFIECTASKGETFIRST2 IIecTaskGetFirst2;
 	PFIECTASKGETNEXT2 IIecTaskGetNext2;
 	PFIECTASKRELOAD IIecTaskReload;
 	PFIECTASKCALCULATEID IIecTaskCalculateId;
 	PFIECTASKWAITTASKSACTIVE IIecTaskWaitTasksActive;
 	PFIECTASKSINGLECYCLE IIecTaskSingleCycle;
 	PFIECTASKRESETSTATISTICS IIecTaskResetStatistics;
 	PFIECTASKDEBUGHANDLERENTER IIecTaskDebugHandlerEnter;
 	PFIECTASKDEBUGHANDLERLEAVE IIecTaskDebugHandlerLeave;
 } ICmpIecTask_C;

#ifdef CPLUSPLUS
class ICmpIecTask : public IBase
{
	public:
		virtual RTS_HANDLE CDECL IIecTaskCreate(APPLICATION *pApp, Task_Info *pTaskInfo, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IIecTaskDelete(void) =0;
		virtual RTS_RESULT CDECL IIecTaskDelete2(RTS_UI32 ulTimeoutMs) =0;
		virtual RTS_RESULT CDECL IIecFreeTasks(APPLICATION *pApp) =0;
		virtual RTS_RESULT CDECL IIecFreeTasks2(APPLICATION *pApp, RTS_UI32 ulTimeoutMs) =0;
		virtual RTS_RESULT CDECL IIecTaskCycle(Task_Desc* pTask) =0;
		virtual RTS_RESULT CDECL IIecTaskUpdateJitterTime(Task_Desc* pTask, RTS_SYSTIME *ptNow) =0;
		virtual RTS_RESULT CDECL IIecTaskUpdateCycleTime(Task_Desc* pTask, RTS_SYSTIME *ptActUs) =0;
		virtual RTS_RESULT CDECL IIecTasksResetAllowed(APPLICATION *pApp) =0;
		virtual RTS_RESULT CDECL IIecTasksPrepareReset(APPLICATION *pApp, int bResetOrigin) =0;
		virtual RTS_RESULT CDECL IIecTasksResetDone(APPLICATION *pApp, int bResetOrigin) =0;
		virtual RTS_UI32 CDECL IIecTaskGetWaitForStopTimeout(APPLICATION *pApp, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IIecTasksWaitForStop(APPLICATION *pApp, RTS_UI32 ulTimeoutMs, unsigned long ulStopReason) =0;
		virtual RTS_RESULT CDECL IIecTaskInitOutputs(APPLICATION *pApp) =0;
		virtual RTS_RESULT CDECL IIecTaskEnterExclusiveSection(void) =0;
		virtual RTS_RESULT CDECL IIecTaskLeaveExclusiveSection(void) =0;
		virtual RTS_RESULT CDECL IIecTaskEnterExclusiveSection2(APPLICATION *pApp) =0;
		virtual RTS_RESULT CDECL IIecTaskTryEnterExclusiveSection2(APPLICATION *pApp, RTS_UI32 timeoutMs, RTS_BOOL bForceEnter) =0;
		virtual RTS_RESULT CDECL IIecTaskLeaveExclusiveSection2(APPLICATION *pApp) =0;
		virtual RTS_RESULT CDECL IIecTaskRegisterSlotCallbacks(APPLICATION *pApp, RTS_I32 nSlotNr, PF_SLOT_CALLBACK pfSlotCallback, int bIecCallback) =0;
		virtual RTS_RESULT CDECL IIecTaskUnregisterSlotCallbacks(APPLICATION *pApp, RTS_I32 nSlotNr, PF_SLOT_CALLBACK pfSlotCallback, int bIecCallback) =0;
		virtual RTS_RESULT CDECL IIecTaskRegisterSlotCallback(Task_Desc *pTask, RTS_I32 nSlotNr, PF_SLOT_CALLBACK pfSlotCallback, int bIecCallback) =0;
		virtual RTS_RESULT CDECL IIecTaskUnregisterSlotCallback(Task_Desc *pTask, RTS_I32 nSlotNr, PF_SLOT_CALLBACK pfSlotCallback, int bIecCallback) =0;
		virtual Task_Desc * CDECL IIecTaskGetDesc(void) =0;
		virtual RTS_HANDLE CDECL IIecTaskGetHandle(char *pszAppName, char *pszTaskName, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IIecTaskGetCurrent(RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IIecTaskDebugLoop(void) =0;
		virtual RTS_RESULT CDECL IIecTaskDebugEnter(void) =0;
		virtual RTS_RESULT CDECL IIecTaskDebugLeave(void) =0;
		virtual RTS_RESULT CDECL IIecTaskSetContext(RegContext *pContext) =0;
		virtual RTS_RESULT CDECL IIecTaskGetContext(RegContext *pContext) =0;
		virtual RTS_RESULT CDECL IIecTaskExceptionHandler(RTS_UI32 ulException, RegContext Context) =0;
		virtual Task_Desc * CDECL IIecTaskGetByIndex(APPLICATION* pApp, int iIndex, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IIecTaskGetHandleByIndex(APPLICATION* pApp, int iIndex, RTS_RESULT *pResult) =0;
		virtual Task_Desc* CDECL IIecTaskGetById(APPLICATION* pappl, int iId, RTS_RESULT *pResult) =0;
		virtual int CDECL IIecTaskGetNumOfTasks(APPLICATION* pAppl, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IIecTaskEnableSchedulingAll(APPLICATION *pApp) =0;
		virtual RTS_RESULT CDECL IIecTaskDisableSchedulingAll(APPLICATION *pApp, RTS_HANDLE hIecTaskToExclude) =0;
		virtual RTS_RESULT CDECL IIecTaskEnableScheduling(void) =0;
		virtual RTS_RESULT CDECL IIecTaskDisableScheduling(void) =0;
		virtual RTS_RESULT CDECL IIecTaskEnableWatchdog(void) =0;
		virtual RTS_RESULT CDECL IIecTaskDisableWatchdog(void) =0;
		virtual RTS_RESULT CDECL IIecTaskEnableWatchdog2(void) =0;
		virtual RTS_RESULT CDECL IIecTaskDisableWatchdog2(void) =0;
		virtual RTS_RESULT CDECL IIecTaskCheckWatchdog(RTS_SYSTIME *ptActUs) =0;
		virtual RTS_HANDLE CDECL IIecTaskGetFirst(char *pszAppName, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IIecTaskGetNext(char *pszAppName, RTS_HANDLE hPrevIecTask, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IIecTaskGetFirst2(APPLICATION *pApp, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IIecTaskGetNext2(APPLICATION *pApp, RTS_HANDLE hPrevIecTask, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IIecTaskReload(RTS_HANDLE hIecTask, RTS_UI32 ulTimeoutMs, RTS_RESULT *pResult) =0;
		virtual int CDECL IIecTaskCalculateId(APPLICATION *pApp, int iIndex, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IIecTaskWaitTasksActive(APPLICATION *pApp, RTS_UI32 ulTimeoutMs) =0;
		virtual RTS_RESULT CDECL IIecTaskSingleCycle(APPLICATION *pApp) =0;
		virtual RTS_RESULT CDECL IIecTaskResetStatistics(RTS_HANDLE hIecTask) =0;
		virtual RTS_RESULT CDECL IIecTaskDebugHandlerEnter(void) =0;
		virtual RTS_RESULT CDECL IIecTaskDebugHandlerLeave(void) =0;
};
	#ifndef ITF_CmpIecTask
		#define ITF_CmpIecTask static ICmpIecTask *pICmpIecTask = NULL;
	#endif
	#define EXTITF_CmpIecTask
#else	/*CPLUSPLUS*/
	typedef ICmpIecTask_C		ICmpIecTask;
	#ifndef ITF_CmpIecTask
		#define ITF_CmpIecTask
	#endif
	#define EXTITF_CmpIecTask
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPIECTASKITF_H_*/
