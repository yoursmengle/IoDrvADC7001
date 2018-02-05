/**
 * <interfacename>SysTask</interfacename>
 * <description> 
 *	<p>The SysTask interface is projected to handle all system dependant task operations.
 *	This interface can only be imoplemented typically on targets with an operating system.</p>
 *
 *	All tasks that uses this SysTask interface must have the same structure.
 *	Here are two examples for a cyclic task.
 *	
 *	1. Cyclic task that sets itself into sleep for cyclic execution:
 *
 *		int iTaskParameter = 123;
 *		RTS_RESULT Result;
 *		RTS_HANDLE hTask = CAL_SysTaskCreate("TestTask", TestTask, &iTaskParameter, TASKPRIO_HIGH_BASE, 0, 0, NULL, &Result);
 *		CAL_SysTaskResume(hTask);
 *
 *		void TestTask(SYS_TASK_PARAM *ptp)
 *		{
 *			RTS_HANDLE hTask = ptp->hTask;
 *			void *pParameter = (void *)ptp->pParam;
 *
 *			CAL_SysTaskEnter(hTask);
 *			while (!ptp->bExit)
 *			{
 *				// TODO: Task code
 *				CAL_SysTaskWaitSleep(hTask, 100);
 *			}
 *			CAL_SysTaskLeave(hTask);
 *			CAL_SysTaskEnd(hTask, 0);
 *		}
 *
 *	2. Cyclic task that uses the cyclic mechanism of the operating system
 *		for cyclic execution:
 *		
 *		int iTaskParameter = 123;
 *		RTS_RESULT Result;
 *		RTS_HANDLE hTask = CAL_SysTaskCreate("TestTask2", TestTask2, &iTaskParameter, TASKPRIO_HIGH_BASE, 1000, 0, NULL, &Result);
 *		CAL_SysTaskResume(hTask);
 *
 *		void TestTask2(SYS_TASK_PARAM *ptp)
 *		{
 *			RTS_HANDLE hTask = ptp->hTask;
 *			void *pParameter = (void *)ptp->pParam;
 *
 *			CAL_SysTaskEnter(hTask);
 *			while (!ptp->bExit)
 *			{
 *				// TODO: Task code
 *				CAL_SysTaskWaitInterval(hTask);
 *			}
 *			CAL_SysTaskLeave(hTask);
 *			CAL_SysTaskEnd(hTask, 0);
 *		}
 *
 * </description>
 *	
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysTask')

#ifndef CDECL
	#define CDECL
#endif

REF_ITF(`SysExceptItf.m4')
REF_ITF(`SysTimeItf.m4')

/**
 * <category>Static defines</category>
 * <description>Maximum length of a task name</description>
 */
#ifndef SYSTASK_MAX_NAME_LEN
	#define SYSTASK_MAX_NAME_LEN	20
#endif

/**
 * <category>Static defines</category>
 * <description>Number of static tasks</description>
 */
 #ifndef SYSTASK_NUM_OF_STATIC_TASKS
	#define SYSTASK_NUM_OF_STATIC_TASKS	20
#endif

/**
 * <category>Task status definitions</category>
 * <description>Actual status of a task</description>
 */
#define TS_NOT_CREATED		0x0000
#define TS_VALID			0x0001
#define TS_ACTIVE			0x0002
#define TS_SUSPENDED		0x0004
#define TS_DELETED			0x0008
#define TS_EXCEPTION		0x0010

/**
 * <category>Task status bits</category>
 * <description></description>
 */
#define TF_VALID			0
#define TF_ACTIVE			1
#define TF_SUSPENDED		2
#define TF_DELETED			3
#define TF_EXCEPTION		4


/**
 * <category>Task status macros</category>
 */
#define SysTaskIsValid(pTask)				(pTask->iState & TS_VALID)
#define SysTaskIsActive(pTask)				(pTask->iState & TS_ACTIVE)
#define SysTaskIsSuspended(pTask)			(pTask->iState & TS_SUSPENDED)
#define SysTaskIsDeleted(pTask)				(pTask->iState & TS_DELETED)
#define SysTaskIsException(pTask)			(pTask->iState & TS_EXCEPTION)

#if defined(SYSCPUHANDLING_NOTIMPLEMENTED) || defined(SYSCPUTESTANDSETBIT_NOTIMPLEMENTED) || !defined(SYSTASK_USE_ATOMIC_BITACCESS)
	#define SysTaskSetValid(pTask)			(pTask->iState |= TS_VALID)
	#define SysTaskSetInvalid(pTask)		(pTask->iState &= ~TS_VALID)

	#define SysTaskSetActive(pTask)			(pTask->iState |= TS_ACTIVE)
	#define SysTaskSetInactive(pTask)		(pTask->iState &= ~TS_ACTIVE)

	#define SysTaskSetSuspended(pTask)		(pTask->iState |= TS_SUSPENDED)
	#define SysTaskSetResumed(pTask)		(pTask->iState &= ~TS_SUSPENDED)

	#define SysTaskSetDeleted(pTask)		(pTask->iState |= TS_DELETED)

	#define SysTaskSetException(pTask)		(pTask->iState |= TS_EXCEPTION)
	#define SysTaskResetException(pTask)	(pTask->iState &= ~TS_EXCEPTION)
#else
	#define SysTaskSetValid(pTask)			{\
												if (CHK_SysCpuTestAndSetBit)\
													CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_VALID, 1);\
												else\
												pTask->iState |= TS_VALID;\
											}
	#define SysTaskSetInvalid(pTask)		{\
												if (CHK_SysCpuTestAndSetBit)\
													CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_VALID, 0);\
												else\
													pTask->iState &= ~TS_VALID;\
											}

	#define SysTaskSetActive(pTask)			{\
												if (CHK_SysCpuTestAndSetBit)\
													CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_ACTIVE, 1);\
												else\
													pTask->iState |= TS_ACTIVE;\
											}
	#define SysTaskSetInactive(pTask)		{\
												if (CHK_SysCpuTestAndSetBit)\
													CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_ACTIVE, 0);\
												else\
													pTask->iState &= ~TS_ACTIVE;\
											}

	#define SysTaskSetSuspended(pTask)		{\
												if (CHK_SysCpuTestAndSetBit)\
													CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_SUSPENDED, 1);\
												else\
													pTask->iState |= TS_SUSPENDED;\
											}
	#define SysTaskSetResumed(pTask)		{\
												if (CHK_SysCpuTestAndSetBit)\
													CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_SUSPENDED, 0);\
												else\
													pTask->iState &= ~TS_SUSPENDED;\
											}

	#define SysTaskSetDeleted(pTask)		{\
												if (CHK_SysCpuTestAndSetBit)\
													CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_DELETED, 1);\
												else\
													pTask->iState |= TS_DELETED;\
											}

	#define SysTaskSetException(pTask)		{\
												if (CHK_SysCpuTestAndSetBit)\
													CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_EXCEPTION, 1);\
												else\
													pTask->iState |= TS_EXCEPTION;\
											}
	#define SysTaskResetException(pTask)	{\
												if (CHK_SysCpuTestAndSetBit)\
													CAL_SysCpuTestAndSetBit(&pTask->iState, sizeof(pTask->iState), TF_EXCEPTION, 0);\
												else\
													pTask->iState &= ~TS_EXCEPTION;\
											}
#endif


/**
 * <category>Priority ranges</category>
 * <description>
 *	Task priorities can be set between 0..255.
 *	Each task priority is assigned to one of the following range:
 *	<ul>
 *		<li>TASKPRIO_SYSTEM: Runtime system management tasks, like scheduler</li>
 *		<li>TASKPRIO_REALTIME: Realtime tasks. Reserved for IEC-tasks</li>
 *		<li>TASKPRIO_HIGH: For tasks right below realtime tasks. Could be used e.g. for higher priority communication tasks</li>
 *		<li>TASKPRIO_ABOVENORMAL: For tasks below high tasks</li>
 *		<li>TASKPRIO_NORMAL: Normal tasks, like communication server tasks</li>
 *		<li>TASKPRIO_BELOWNORMAL: For tasks below normal tasks</li>
 *		<li>TASKPRIO_LOW: For tasks with low priority</li>
 *		<li>TASKPRIO_LOWEST: For tasks with lowest priority</li>
 *		<li>TASKPRIO_IDLE: For background or idle operations</li>
 *	</ul>
 * </description>
 */
#define TASKPRIO_RANGE				255
#define TASKPRIO_SEGMENT			32

#define TASKPRIO_MAX				0

/* Task segment 1 */
#define TASKPRIO_SYSTEM_BASE		0
#define TASKPRIO_SYSTEM_END			31

/* Task segment 2 */
#define TASKPRIO_REALTIME_BASE		32
#define TASKPRIO_REALTIME_END		63

/* Task segment 3 */
#define TASKPRIO_HIGH_BASE			64
#define TASKPRIO_HIGH_END			95

/* Task segment 4 */
#define TASKPRIO_ABOVENORMAL_BASE	96
#define TASKPRIO_ABOVENORMAL_END	127

/* Task segment 5 */
#define TASKPRIO_NORMAL_BASE		128
#define TASKPRIO_NORMAL_END			159

/* Task segment 6 */
#define TASKPRIO_BELOWNORMAL_BASE	160
#define TASKPRIO_BELOWNORMAL_END	191

/* Task segment 7 */
#define TASKPRIO_LOW_BASE			192
#define TASKPRIO_LOW_END			223

/* Task segment 8 */
#define TASKPRIO_LOWEST_BASE		224
#define TASKPRIO_LOWEST_END			255

#define TASKPRIO_IDLE				255
#define TASKPRIO_MIN				255


/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Mapping task priorities:
 *	Settings to shift task priority ranges to the appropriate area. This is done via calling the function SysTaskGetConfiguredPriority(). 
 *	The virtual priorities can be mapped to real operating system priorites with the following settings.
 *
 *	The mapping is done this way (pseudocode):
 *	if (taskPriority >= OSPriority.XXX.Base && TaskPriority <= OSPriority.XXX.Base)
 *		if (taskPriority > (OSPriority.XXX.End - OSPriority.XXX.Base))
 *				return OSPriority.XXX.End;
 *			return OSPriority.XXX.Base + taskPriority;
 *		return taskPriority;
 * </description>
 */
#define SYSTASKKEY_INT_PRIORITY_SYSTEM_BASE				"OSPriority.System.Base"
#define SYSTASKVALUE_INT_PRIORITY_SYSTEM_BASE_DEFAULT	TASKPRIO_SYSTEM_BASE
#define SYSTASKKEY_INT_PRIORITY_SYSTEM_END				"OSPriority.System.End"
#define SYSTASKVALUE_INT_PRIORITY_SYSTEM_END_DEFAULT	TASKPRIO_SYSTEM_END

#define SYSTASKKEY_INT_PRIORITY_REALTIME_BASE			"OSPriority.Realtime.Base"
#define SYSTASKVALUE_INT_PRIORITY_REALTIME_BASE_DEFAULT	TASKPRIO_REALTIME_BASE
#define SYSTASKKEY_INT_PRIORITY_REALTIME_END			"OSPriority.Realtime.End"
#define SYSTASKVALUE_INT_PRIORITY_REALTIME_END_DEFAULT	TASKPRIO_REALTIME_END

#define SYSTASKKEY_INT_PRIORITY_HIGH_BASE				"OSPriority.High.Base"
#define SYSTASKVALUE_INT_PRIORITY_HIGH_BASE_DEFAULT		TASKPRIO_HIGH_BASE
#define SYSTASKKEY_INT_PRIORITY_HIGH_END				"OSPriority.High.End"
#define SYSTASKVALUE_INT_PRIORITY_HIGH_END_DEFAULT		TASKPRIO_HIGH_END

#define SYSTASKKEY_INT_PRIORITY_ABOVENORMAL_BASE			"OSPriority.AboveNormal.Base"
#define SYSTASKVALUE_INT_PRIORITY_ABOVENORMAL_BASE_DEFAULT	TASKPRIO_ABOVENORMAL_BASE
#define SYSTASKKEY_INT_PRIORITY_ABOVENORMAL_END				"OSPriority.AboveNormal.End"
#define SYSTASKVALUE_INT_PRIORITY_ABOVENORMAL_END_DEFAULT	TASKPRIO_ABOVENORMAL_END

#define SYSTASKKEY_INT_PRIORITY_NORMAL_BASE				"OSPriority.Normal.Base"
#define SYSTASKVALUE_INT_PRIORITY_NORMAL_BASE_DEFAULT	TASKPRIO_NORMAL_BASE
#define SYSTASKKEY_INT_PRIORITY_NORMAL_END				"OSPriority.Normal.End"
#define SYSTASKVALUE_INT_PRIORITY_NORMAL_END_DEFAULT	TASKPRIO_NORMAL_END

#define SYSTASKKEY_INT_PRIORITY_BELOWNORMAL_BASE			"OSPriority.BelowNormal.Base"
#define SYSTASKVALUE_INT_PRIORITY_BELOWNORMAL_BASE_DEFAULT	TASKPRIO_BELOWNORMAL_BASE
#define SYSTASKKEY_INT_PRIORITY_BELOWNORMAL_END				"OSPriority.BelowNormal.End"
#define SYSTASKVALUE_INT_PRIORITY_BELOWNORMAL_END_DEFAULT	TASKPRIO_BELOWNORMAL_END

#define SYSTASKKEY_INT_PRIORITY_LOW_BASE				"OSPriority.Low.Base"
#define SYSTASKVALUE_INT_PRIORITY_LOW_BASE_DEFAULT		TASKPRIO_LOW_BASE
#define SYSTASKKEY_INT_PRIORITY_LOW_END					"OSPriority.Low.End"
#define SYSTASKVALUE_INT_PRIORITY_LOW_END_DEFAULT		TASKPRIO_LOW_END

#define SYSTASKKEY_INT_PRIORITY_LOWEST_BASE				"OSPriority.Lowest.Base"
#define SYSTASKVALUE_INT_PRIORITY_LOWEST_BASE_DEFAULT	TASKPRIO_LOWEST_BASE
#define SYSTASKKEY_INT_PRIORITY_LOWEST_END				"OSPriority.Lowest.End"
#define SYSTASKVALUE_INT_PRIORITY_LOWEST_END_DEFAULT	TASKPRIO_LOWEST_END

#define SYSTASKKEY_INT_VXWORKS_CPU					"VxWorks.CPU"
#define SYSTASKVALUE_INT_VXWORKS_CPU_DEFAULT		0

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * ATTENTION!!! Only intended for very special debug purposes!
 * Use this setting only, if this was requested by the 3S team!
 * Use this setting only in non-productive test environments!
 * When this is set, all task exceptions are unhandeled and the first exception will directly crash the runtime system!!!* 
 * </description>
 */
#define SYSTASKKEY_INT_WIN32_DEBUG_DISABLE_EXCEPTIONHANDLER				"Win32.DebuggingOnlyDisableExceptionHandler"
#ifndef SYSTASKKEY_INT_WIN32_DEBUG_DISABLE_EXCEPTIONHANDLER_DEFAULT
	#define SYSTASKKEY_INT_WIN32_DEBUG_DISABLE_EXCEPTIONHANDLER_DEFAULT		0
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to specify the OS specifiy task stacksize. For smaller embedded systems with tasks, this setting is necessary.
 *	NOTE:
 *	Actually this setting is only supported by Linux platforms!
 * </description>
 */
#define SYSTASKKEY_INT_TASK_STACKSIZE									"StackSize"
#ifndef SYSTASKVALUE_INT_TASK_STACKSIZE_DEFAULT
	#define SYSTASKVALUE_INT_TASK_STACKSIZE_DEFAULT						0
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	By default CODESYS doesn't change the clock period of the QNX system tick. To reduce the jitter of
 *	the tasks, or to support "distributed clocks", one might want to have a higher resolution of the
 *	timer. With this setting you can adjust the clock period at CODESYS startup.
 *	The period is defined in nanoseconds and is passed as is to the QNX neutrino function ClockPeriod().
 * </description>
 */
#define SYSTASKKEY_INT_QNX_CLOCKPERIOD							"QNX.ClockPeriod"
#ifndef SYSTASKVALUE_INT_QNX_CLOCKPERIOD_DEFAULT
#define SYSTASKVALUE_INT_QNX_CLOCKPERIOD_DEFAULT			0
#endif

RTS_RESULT CDECL TaskExceptionHandler(RTS_HANDLE hTask, RTS_UI32 ulException, RegContext Context);
typedef RTS_RESULT (CDECL *PFSYS_TASK_EXCEPTIONHANDLER)(RTS_HANDLE hTask, RTS_UI32 ulException, RegContext Context);
#define PFTASKEXCEPTIONHANDLER		PFSYS_TASK_EXCEPTIONHANDLER


/**
 * <category>Event parameter</category>
 * <element name="pSysTaskInfo" type="IN">Pointer to task info structure</element>
im */
typedef struct
{
	struct tagSYS_TASK_INFO *pSysTaskInfo;
} EVTPARAM_SysTask;
#define EVTPARAMID_SysTask					0x0001
#define EVTVERSION_SysTask					0x0001

/**
 * <category>Event parameter</category>
 * <element name="pSysTaskInfo" type="IN">Pointer to task info structure</element>
 * <element name="ui32PriorityOriginal" type="IN">Original task priority (virtual RTS task prio)</element>
 * <element name="ui32PriorityMapped" type="OUT">Mapped task priority (virtual RTS task prio)</element>
 * <element name="Result" type="OUT">Error code:
 *					 ERR_OK: Priority is mapped
 *					 Other:  Original mapping is used
 * </element>
 */
typedef struct
{
	struct tagSYS_TASK_INFO *pSysTaskInfo;
	RTS_UI32 ui32PriorityOriginal;
	RTS_UI32 ui32PriorityMapped;
	RTS_RESULT Result;
} EVTPARAM_SysTask_GetPriority;
#define EVTPARAMID_SysTask_GetPriority			0x0002
#define EVTVERSION_SysTask_GetPriority			0x0001

/**
 * <category>Events</category>
 * <description>Event is sent, if a new task was create</description>
 * <param name="pEventParam" type="IN">EVTPARAM_SysTask</param>
 */
#define EVT_TaskCreate					MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Events</category>
 * <description>Event is sent, before a task will be deleted</description>
 * <param name="pEventParam" type="IN">EVTPARAM_SysTask</param>
 */
#define EVT_TaskDelete					MAKE_EVENTID(EVTCLASS_INFO, 2)

/**
 * <category>Events</category>
 * <description>Event is sent, whenever the task intervall is set (used for ECAT DC)</description>
 * <param name="pEventParam" type="IN">EVTPARAM_SysTask</param>
 */
#define EVT_TaskSetInterval				MAKE_EVENTID(EVTCLASS_INFO, 3)
#define EVTPARAMID_SysTaskSetInterval		0x0002
#define EVTVERSION_SysTaskSetInterval		0x0001

/**
 * <category>Events</category>
 * <description>Event is sent for each task to map virtual RTS task priority</description>
 * <param name="pEventParam" type="IN">EVTPARAM_SysTask_GetPriority</param>
 */
#define EVT_TaskGetPriority				MAKE_EVENTID(EVTCLASS_INFO, 4)


/**
 * <category>Event parameter</category>
 * <element name="pSysTaskSetInterval" type="IN">Pointer to set task interval information</element>
 */
typedef struct
{
	struct tagsystasksetinterval_struct* pSysTaskSetInterval;
} EVTPARAM_SysTaskSetInterval;

/**
 * <category>Feature flags</category>
 * <element name="pSysTaskInfo" type="IN">Pointer to task info structure</element>
 */
#define SYSTASK_FF_NONE						0x00000000
#define SYSTASK_FF_AUTORELEASEONEXIT		0x00000001


struct tagSYS_TASK_PARAM;
typedef void CDECL SYS_TASK_FUNCTION(struct tagSYS_TASK_PARAM *);
typedef void (CDECL *PFSYS_TASK_FUNCTION)(struct tagSYS_TASK_PARAM *);

/**
 * <description>SYS_TASK_PARAM</description>
 */
typedef struct tagSYS_TASK_PARAM
{
	RTS_IEC_HANDLE hTask;		/* <element name="hTask" type="IN">SysTask handle of the task</element> */
	RTS_IEC_DINT bExit;		/* <element name="bExit" type="IN">bExit flag to exit the task loop</element> */
	RTS_IEC_UDINT ulInterval;		/* <element name="ulInterval" type="IN">Specified interval of the task</element> */
	void *pParam;		/* <element name="pParam" type="IN">User specific parameter for the task</element> */
} SYS_TASK_PARAM;

/**
 * <description>SYS_TASK_INFO</description>
 */
typedef struct tagSYS_TASK_INFO
{
	RTS_IEC_HANDLE uiOSHandle;		/* <element name="uiOSHandle" type="IN">Operating system handle of a task</element> */
	RTS_IEC_DINT iState;		/* <element name="iState" type="IN">Actual state of the task. See category "Task status definitions" for details.</element> */
	RTS_IEC_DINT iOldState;		/* <element name="iOldState" type="IN">Previous state of the task</element> */
	SYS_TASK_PARAM TP;		/* <element name="TP" type="IN">Task parameter, with which the task was created</element> */
	RTS_IEC_UDINT ulCycleTime;		/* <element name="ulCycleTime" type="IN">Last cycle time</element> */
	RTS_IEC_UDINT ulCycleStart;		/* <element name="ulCycleStart" type="IN">Start time of the cycle</element> */
	RTS_IEC_UDINT ulPriority;		/* <element name="ulPriority" type="IN">RTS priority of the task (not OS priority)</element> */
	RTS_IEC_UDINT ulOSPriority;		/* <element name="ulOSPriority" type="IN">Operating system priority of the task</element> */
	RTS_IEC_UDINT ulInterval;		/* <element name="ulInterval" type="IN">Specified interval for the task</element> */
	RTS_IEC_UDINT ulStackSize;		/* <element name="ulStackSize" type="IN">Specified stack size for the task</element> */
	PFSYS_TASK_FUNCTION pFunction;		/* <element name="pFunction" type="IN">Function pointer of the task frame</element> */
	RTS_IEC_STRING szName[SYSTASK_MAX_NAME_LEN];		/* <element name="szName" type="IN">Name of the task</element> */
	PFSYS_TASK_EXCEPTIONHANDLER pExceptionHandler;		/* <element name="pExceptionHandler" type="IN">Specified exception handler of the task</element> */
	RegContext Context;		/* <element name="Context" type="IN">Current context of the task, if the task is supended</element> */
	RTS_IEC_BYTE *pCppInstance;		/* <element name="pCppInstance" type="IN">Internal usage for C++</element> */
	RTS_IEC_BYTE *pOSSpecific;		/* <element name="pOSSpecific" type="IN">Optional pointer to operating system specific stuff</element> */
	RTS_IEC_DWORD ulFeature;		/* <element name="ulFeature" type="IN">Features flags of the task. See category "FeatureFlags" for details.</element> */
	SEHContext *pSEHContextHead;    /* <element name="pSEHContextHead" type="IN">Points to the head of the registered exception frames</element> */
	RTS_IEC_STRING *pszLongName;	/* <element name="pszLongName" type="IN">Long name of the task</element> */
	RTS_IEC_HANDLE hTaskGroup;		/* <element name="hTaskGroup" type="IN">Optional task group handle</element> */
} SYS_TASK_INFO;

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>The creator of a task can call this function to release the task object, if the task ends is execution. So the task is responsible itself to delete this object.
 *	NOTE: The task object must not be used from outside the task after calling this function!</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystaskautoreleaseonexit_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	/* <param name="hTask" type="IN">Handle to task</param> */
	RTS_IEC_RESULT SysTaskAutoReleaseOnExit;	/* VAR_OUTPUT */	
} systaskautoreleaseonexit_struct;

DEF_API(`void',`CDECL',`systaskautoreleaseonexit',`(systaskautoreleaseonexit_struct *p)',1,0x3A77FA5D,0x03050A00)

/**
 * <description>NOT IMPLEMENTED YET! Function to investigate the stack task. </description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystaskcheckstack_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	/* <param name="hTask" type="IN">Handle to task</param> */
	RTS_IEC_UDINT *pulMaxDepth;			/* VAR_INPUT */	/* <param name="pulMaxDepth" type="OUT">Maximum stack depth</param> */
	RTS_IEC_RESULT SysTaskCheckStack;	/* VAR_OUTPUT */	
} systaskcheckstack_struct;

DEF_API(`void',`CDECL',`systaskcheckstack',`(systaskcheckstack_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF64957C9),0x03050A00)

/**
 * <description>Is called to create a task in _run_ mode.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystaskcreate_struct
{
	RTS_IEC_STRING *pszTaskName;		/* VAR_INPUT */	/* <param name="pszTaskName" type="IN">The name of the task</param> */
	PFSYS_TASK_FUNCTION pFunction;		/* VAR_INPUT */	/* <param name="pFunction" type="IN">Function which implements the task: void func (SYS_TASK_PARAM/// pParam*)</param> */
	SYS_TASK_PARAM *pParam;				/* VAR_INPUT */	/* <param name="pParam" type="IN">Pointer to the argument which is passed on entry, see SYS_TASK_PARAM->pParam</param> */
	RTS_IEC_UDINT ulPriority;			/* VAR_INPUT */	/* <param name="ulPriority" type="IN">Priority of the task. Can be 0..255</param> */
	RTS_IEC_UDINT ulInterval;			/* VAR_INPUT */	/* <param name="ulInterval" type="IN">Interval in microseconds</param> */
	RTS_IEC_UDINT ulStackSize;			/* VAR_INPUT */	/* <param name="ulStackSize" type="IN">Stack size of task in bytes. 0=Default</param> */
	PFSYS_TASK_EXCEPTIONHANDLER pExceptionHandler;	/* VAR_INPUT */	/* <param name="pExceptionHandler" type="IN">Function pointer to exception handler that is called after an exception has occurred in the task</param> */
	RTS_IEC_HANDLE *phTaskHandle;		/* VAR_INPUT */	/* <param name="phTaskHandle" type="OUT">Handle to the created task</param> */
	RTS_IEC_RESULT SysTaskCreate;		/* VAR_OUTPUT */	
} systaskcreate_struct;

DEF_API(`void',`CDECL',`systaskcreate',`(systaskcreate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x6A30BC52),0x03050A00)

/**
 * <description>Is called to create a task in _suspended_ mode. SysTaskResume must be called afterwards!</description>
 * <result><p>RESULT: Handle to the created task</p></result>
 */
typedef struct tagsystaskcreate2_struct
{
	RTS_IEC_STRING *pszTaskName;		/* VAR_INPUT */	/* <param name="pszTaskName" type="IN">The name of the task</param> */
	PFSYS_TASK_FUNCTION pFunction;		/* VAR_INPUT */	/* <param name="pFunction" type="IN">Function which implements the task: void func (SYS_TASK_PARAM/// pParam*)</param> */
	SYS_TASK_PARAM *pParam;				/* VAR_INPUT */	/* <param name="pParam" type="IN">Pointer to the argument which is passed on entry, see SYS_TASK_PARAM->pParam</param> */
	RTS_IEC_UDINT ulPriority;			/* VAR_INPUT */	/* <param name="ulPriority" type="IN">Priority of the task. Can be 0..255</param> */
	RTS_IEC_UDINT ulInterval;			/* VAR_INPUT */	/* <param name="ulInterval" type="IN">Interval in microseconds</param> */
	RTS_IEC_UDINT ulStackSize;			/* VAR_INPUT */	/* <param name="ulStackSize" type="IN">Stack size of task in bytes. 0=Default</param> */
	PFSYS_TASK_EXCEPTIONHANDLER pExceptionHandler;	/* VAR_INPUT */	/* <param name="pExceptionHandler" type="IN">Function pointer to exception handler that is called after an exception has occurred in the task</param> */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library)</param> */
	RTS_IEC_HANDLE SysTaskCreate2;		/* VAR_OUTPUT */	
} systaskcreate2_struct;

DEF_API(`void',`CDECL',`systaskcreate2',`(systaskcreate2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x94FB2C1D),0x03050A00)

/**
 * <description>Is called to destroy the given task.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystaskdestroy_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	/* <param name="hTask" type="IN">Handle to task</param> */
	RTS_IEC_RESULT SysTaskDestroy;		/* VAR_OUTPUT */	
} systaskdestroy_struct;

DEF_API(`void',`CDECL',`systaskdestroy',`(systaskdestroy_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x23988B85),0x03050A00)

/**
 * <description>Is called from the task itself, that ends its execution.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystaskend_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	/* <param name="hTask" type="IN">Handle to task</param> */
	RTS_IEC_UDINT ulExitCode;			/* VAR_INPUT */	/* <param name="ulExitCode" type="IN">Exit code of the task</param> */
	RTS_IEC_RESULT SysTaskEnd;			/* VAR_OUTPUT */	
} systaskend_struct;

DEF_API(`void',`CDECL',`systaskend',`(systaskend_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xE402950D),0x03050A00)

/**
 * <description>This function is called to mark entering the while loop.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystaskenter_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	/* <param name="hTask" type="IN">Handle to task</param> */
	RTS_IEC_RESULT SysTaskEnter;		/* VAR_OUTPUT */	
} systaskenter_struct;

DEF_API(`void',`CDECL',`systaskenter',`(systaskenter_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x91B321BC),0x03050A00)

/**
 * <description>Tries to exit the given task gracefully. If the task doesn't answer in the specified timeout, then the task will be deleted hard!</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystaskexit_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	/* <param name="hTask" type="IN">Handle to task</param> */
	RTS_IEC_UDINT ulTimeoutMs;			/* VAR_INPUT */	/* <param name="ulTimeoutMs" type="IN">Timeout in milliseconds</param> */
	RTS_IEC_RESULT SysTaskExit;			/* VAR_OUTPUT */	
} systaskexit_struct;

DEF_API(`void',`CDECL',`systaskexit',`(systaskexit_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x643B6FFF),0x03050A00)

/**
 * <description>Call the corresponding exception handler of the task.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystaskgenerateexception_struct
{
	RTS_IEC_HANDLE ulTaskOSHandle;		/* VAR_INPUT */	/* <param name="ulTaskOSHandle" type="IN">Operating system handle of the task</param> */
	RTS_IEC_UDINT ulException;			/* VAR_INPUT */	/* <param name="ulException" type="IN">Rts standard exception</param> */
	RegContext Context;					/* VAR_INPUT */	/* <param name="Context" type="IN">Context to detect the code location where the exception occurred</param> */
	RTS_IEC_RESULT SysTaskGenerateException;	/* VAR_OUTPUT */	
} systaskgenerateexception_struct;

DEF_API(`void',`CDECL',`systaskgenerateexception',`(systaskgenerateexception_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x38E403E6),0x03050A00)

/**
 * <description>Get the current register context of the task. Task must be in suspended mode!</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystaskgetcontext_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	/* <param name="hTask" type="IN">Handle to task</param> */
	RegContext *pContext;				/* VAR_INPUT */	/* <param name="pContext" type="OUT">Pointer to context</param> */
	RTS_IEC_RESULT SysTaskGetContext;	/* VAR_OUTPUT */	
} systaskgetcontext_struct;

DEF_API(`void',`CDECL',`systaskgetcontext',`(systaskgetcontext_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x57FAA367),0x03050A00)

/**
 * <description>Returns the handle of the current running task.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystaskgetcurrent_struct
{
	RTS_IEC_HANDLE *phTask;				/* VAR_INPUT */	/* <param name="phTask" type="OUT">Pointer to task handle</param> */
	RTS_IEC_RESULT SysTaskGetCurrent;	/* VAR_OUTPUT */	
} systaskgetcurrent_struct;

DEF_API(`void',`CDECL',`systaskgetcurrent',`(systaskgetcurrent_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x79AE7BFF),0x03050A00)

/**
 * <description>Returns the operating system handle of the current running task.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystaskgetcurrentoshandle_struct
{
	RTS_IEC_HANDLE *puiTaskOSHandle;	/* VAR_INPUT */	/* <param name="puiTaskOSHandle" type="OUT">Pointer to operating system task handle</param> */
	RTS_IEC_RESULT SysTaskGetCurrentOSHandle;	/* VAR_OUTPUT */	
} systaskgetcurrentoshandle_struct;

DEF_API(`void',`CDECL',`systaskgetcurrentoshandle',`(systaskgetcurrentoshandle_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x9A7C0E47),0x03050A00)

/**
 * <description>Returns the task info of the specified task.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystaskgetinfo_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	/* <param name="hTask" type="IN">Handle to task</param> */
	SYS_TASK_INFO **ppInfo;				/* VAR_INPUT */	/* <param name="ppInfo" type="OUT">Pointer pointer to get task info structure</param> */
	RTS_IEC_RESULT SysTaskGetInfo;		/* VAR_OUTPUT */	
} systaskgetinfo_struct;

DEF_API(`void',`CDECL',`systaskgetinfo',`(systaskgetinfo_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB44E2B3F),0x03050A00)

/**
 * <description>Get the actual interval of a cyclic task. If the specified task is no cyclic task, the function return an error.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystaskgetinterval_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	/* <param name="hTask" type="IN">Handle to the task</param> */
	RTS_IEC_UDINT *pulInterval;			/* VAR_IN_OUT */	/* <param name="pulInterval" type="OUT">Interval of the task in microseconds!</param> */
	RTS_IEC_RESULT SysTaskGetInterval;	/* VAR_OUTPUT */	
} systaskgetinterval_struct;

DEF_API(`void',`CDECL',`systaskgetinterval',`(systaskgetinterval_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4CCFF91B),0x03050A00)

/**
 * <description>Returns the task name of the specified task.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystaskgetname_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	/* <param name="hTask" type="IN">Handle to task</param> */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library)</param> */
	RTS_IEC_STRING *SysTaskGetName;		/* VAR_OUTPUT */	
} systaskgetname_struct;

DEF_API(`void',`CDECL',`systaskgetname',`(systaskgetname_struct *p)',1,0xC7690C59,0x03050A00)

/**
 * <description>Function to get the operating system specific handle.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystaskgetoshandle_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	/* <param name="hTask" type="IN">Handle to task</param> */
	RTS_IEC_HANDLE SysTaskGetOSHandle;	/* VAR_OUTPUT */	
} systaskgetoshandle_struct;

DEF_API(`void',`CDECL',`systaskgetoshandle',`(systaskgetoshandle_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD55E19B5),0x03050A00)

/**
 * <description>Returns the operating system priority of the given task.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystaskgetospriority_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	/* <param name="hTask" type="IN">Handle to task</param> */
	RTS_IEC_UDINT *pulOSPriority;		/* VAR_INPUT */	/* <param name="pulOSPriority" type="OUT">Pointer to get operating system priority</param> */
	RTS_IEC_RESULT SysTaskGetOSPriority;	/* VAR_OUTPUT */	
} systaskgetospriority_struct;

DEF_API(`void',`CDECL',`systaskgetospriority',`(systaskgetospriority_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x21E9C566),0x03050A00)

/**
 * <description>Get the runtime system priority of the given task.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystaskgetpriority_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	/* <param name="hTask" TYPE="IN">Handle to the task</param> */
	RTS_IEC_UDINT *pulPriority;			/* VAR_INPUT */	/* <param name="pulPriority" type="OUT">Pointer to get priority</param> */
	RTS_IEC_RESULT SysTaskGetPriority;	/* VAR_OUTPUT */	
} systaskgetpriority_struct;

DEF_API(`void',`CDECL',`systaskgetpriority',`(systaskgetpriority_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB576F235),0x03050A00)

/**
 * <description>Is used to wait for exit of the specified join task.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystaskjoin_struct
{
	RTS_IEC_HANDLE hTaskToJoin;			/* VAR_INPUT */	/* <param name="hTaskToJoin" type="IN">Task to join</param> */
	RTS_IEC_UDINT ulTimeoutMs;			/* VAR_INPUT */	/* <param name="ulTimeoutMs" type="IN">Timeout in milliseconds to wait for join task</param> */
	RTS_IEC_RESULT SysTaskJoin;			/* VAR_OUTPUT */	
} systaskjoin_struct;

DEF_API(`void',`CDECL',`systaskjoin',`(systaskjoin_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x379A5B0D),0x03050A00)

/**
 * <description>This function is called to mark leaving the while loop.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystaskleave_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	/* <param name="hTask" type="IN">Handle to task</param> */
	RTS_IEC_RESULT SysTaskLeave;		/* VAR_OUTPUT */	
} systaskleave_struct;

DEF_API(`void',`CDECL',`systaskleave',`(systaskleave_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xE095052C),0x03050A00)

/**
 * <description>Is called to resume the given task, if the task was suspended.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystaskresume_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	/* <param name="hTask" type="IN">Handle to task</param> */
	RTS_IEC_RESULT SysTaskResume;		/* VAR_OUTPUT */	
} systaskresume_struct;

DEF_API(`void',`CDECL',`systaskresume',`(systaskresume_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x3C4C4CF9),0x03050A00)

/**
 * <description>Set the exit flag of the specified task. On the next cycle, the task will exit.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystasksetexit_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	/* <param name="hTask" type="IN">Handle to task</param> */
	RTS_IEC_RESULT SysTaskSetExit;		/* VAR_OUTPUT */	
} systasksetexit_struct;

DEF_API(`void',`CDECL',`systasksetexit',`(systasksetexit_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x137693C1),0x03050A00)

/**
 * <description>
 *	Set the actual interval of a cyclic task. If the specified task is no cyclic task, the function return an error.
 *	This interface can be used to synchronize a task to another task or to events.
 * </description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystasksetinterval_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	/* <param name="hTask" type="IN">Handle to the task</param> */
	RTS_IEC_UDINT ulInterval;			/* VAR_INPUT */	/* <param name="ulInterval" type="IN">New interval of the task in microseconds!</param> */
	RTS_IEC_RESULT SysTaskSetInterval;	/* VAR_OUTPUT */	
} systasksetinterval_struct;

DEF_API(`void',`CDECL',`systasksetinterval',`(systasksetinterval_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB855D3DE),0x03050A00)

/**
 * <description>
 *  Set the priority of the given task. 
 * </description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystasksetpriority_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	/* <param name="hTask" type="IN">Handle to task</param> */
	RTS_IEC_UDINT ulPriority;			/* VAR_INPUT */	/* <param name="ulPriority" type="IN">Task priority to set. Is the virtual priority between 0(highest)..255(lowest) and will be mapped to OS priority</param> */
	RTS_IEC_RESULT SysTaskSetPriority;	/* VAR_OUTPUT */	
} systasksetpriority_struct;

DEF_API(`void',`CDECL',`systasksetpriority',`(systasksetpriority_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x421AD898),0x03050A00)

/**
 * <description>
 *  Is called to suspend the given task. 
 * </description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystasksuspend_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	/* <param name="hTask" type="IN">Handle to task</param> */
	RTS_IEC_RESULT SysTaskSuspend;		/* VAR_OUTPUT */	
} systasksuspend_struct;

DEF_API(`void',`CDECL',`systasksuspend',`(systasksuspend_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x44E9CD9B),0x03050A00)

/**
 * <description>
 *  Wait to the next interval to be activated, if OS supports cyclic task.
 * </description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystaskwaitinterval_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	/* <param name="hTask" type="IN">Handle to task</param> */
	RTS_IEC_RESULT SysTaskWaitInterval;	/* VAR_OUTPUT */	
} systaskwaitinterval_struct;

DEF_API(`void',`CDECL',`systaskwaitinterval',`(systaskwaitinterval_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4FA22EBF),0x03050A00)

/**
 * <description>S
 * This function serves to pause the processing of a running task for a time interval specified in milliseconds.
 * Processing will be continued after the time interval elapsed. 
 * </description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystaskwaitsleep_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	/* <param name="hTask" type="IN">Handle to task</param> */
	RTS_IEC_UDINT ulMilliSeconds;		/* VAR_INPUT */	/* <param name="ulMilliSeconds" type="IN">Time in milliseconds to sleep</param> */
	RTS_IEC_RESULT SysTaskWaitSleep;	/* VAR_OUTPUT */	
} systaskwaitsleep_struct;

DEF_API(`void',`CDECL',`systaskwaitsleep',`(systaskwaitsleep_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x1A10CA63),0x03050A00)

/**
 * <description>
 * This function serves to pause the processing of a running task for a time interval specified in microseconds.
 * The function is not implemented on every platform. 
 * </description>
 * <result>error code</result>
 */
typedef struct tagsystaskwaitsleepus_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	/* <param name="hTask" type="IN">Handle to task</param> */
	RTS_IEC_ULINT *ptSleepUs;			/* VAR_IN_OUT */	/* <param name="ptSleepUs" type="IN">Time in microseconds to sleep</param> */
	RTS_IEC_RESULT SysTaskWaitSleepUs;	/* VAR_OUTPUT */	
} systaskwaitsleepus_struct;

DEF_API(`void',`CDECL',`systaskwaitsleepus',`(systaskwaitsleepus_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x3D82CA22),0x03050A00)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysTaskOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysTaskOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/* Functions to be optionally implemented and registered by the OS specific implementation of SysTask. */
/* Get the OS task handle from pTask->uiOSHandle. Only needed, if pTask->uiOSHandle is not the OS task handle itself. */
RTS_HANDLE CDECL SysTaskOSGetOSHandleFromTaskInfo(SYS_TASK_INFO *pTask);
typedef RTS_HANDLE (CDECL *PFSYSTASKOSGETOSHANDLEFROMTASKINFO)(SYS_TASK_INFO *pTask);

/* Helper functions to register optional OS specific functions of SysTask. */
/* Register SysTaskOSGetOSHandleFromTaskInfo */ 
RTS_RESULT CDECL SysTaskRegisterGetOSHandleFromTaskInfo(PFSYSTASKOSGETOSHANDLEFROMTASKINFO pfSysTaskOSGetOSHandleFromTaskInfo);


/**
 * <description>Get the first task</description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="pResult" type="ERR_OK">Task found</errorcode>
 * <errorcode name="pResult" type="ERR_NO_OBJECT">No more task available</errorcode>
 * <errorcode name="pResult" type="ERR_PARAMETER">Invalid parameters</errorcode>
 * <errorcode name="pResult" type="ERR_NOTINITIALIZED">The task list is not initialized</errorcode>
 * <result>Handle to the task or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API2(`RTS_HANDLE',`CDECL',`SysTaskGetFirst',`(RTS_RESULT *pResult)')

/**
 * <description>Get the next task</description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="pResult" type="ERR_OK">Task found</errorcode>
 * <errorcode name="pResult" type="ERR_NO_OBJECT">No more task available</errorcode>
 * <errorcode name="pResult" type="ERR_PARAMETER">Invalid parameters</errorcode>
 * <errorcode name="pResult" type="ERR_NOTINITIALIZED">The task list is not initialized</errorcode>
 * <result>Handle to the task or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API2(`RTS_HANDLE',`CDECL',`SysTaskGetNext',`(RTS_HANDLE hPrevTask, RTS_RESULT *pResult)')

/**
 * <description>
 *  Is called to create a task in suspended mode.
 *	IMPLEMENTATION NOTE:
 *	The task must be created _suspended_! After creating a task, the task must be resumed manually to run the task.
 *	If the operating system does not support creating tasks in suspended mode, a task frame must be setup
 *	in the SysTaskOS implementation, where the first call does a SysTaskSuspend() on itself.
 * </description>
 * <param name="pszTaskName" type="IN">The name of the task</param>
 * <param name="pFunction" type="IN">Function which implements the task</param>
 * <param name="pParam" type="IN">Pointer to the argument which is passed on entry</param>
 * <param name="ulPriority" type="IN">Priority of the task</param>
 * <param name="ulInterval" type="IN">Interval in microseconds</param>
 * <param name="ulStackSize" type="IN">Stack size of task in bytes. 0=Default</param>
 * <param name="pExceptionHandler" type="IN">Function pointer to exception handler that is called after an exception has occurred in the task</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the created task</result>
 */
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysTaskCreate',`(char* pszTaskName, PFSYS_TASK_FUNCTION pFunction, void *pParam, RTS_UI32 ulPriority, RTS_UI32 ulInterval, RTS_UI32 ulStackSize, PFTASKEXCEPTIONHANDLER pExceptionHandler, RTS_RESULT *pResult)')

/**
 * <description>
 *  This call extends SysTaskCreate (s.a.) with the name of the task group in order to add this task to the group.
 * </description>
 * <param name="pszTaskGroup" type="IN">Name of the task group</param>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`SysTaskCreate2',`(char* pszTaskName, char *pszTaskGroup, PFSYS_TASK_FUNCTION pFunction, void *pParam, RTS_UI32 ulPriority, RTS_UI32 ulInterval, RTS_UI32 ulStackSize, PFTASKEXCEPTIONHANDLER pExceptionHandler, RTS_RESULT *pResult)')

/**
 * <description>
 *  Tries exit the specified task gracefully. If the task doesn't come to its end within the timeout, then the task will be killed hard!
 * IMPLEMENTATION NOTE:
 * Use TaskTryExit(RTS_HANDLE hTask, RTS_UI32 ulTimeoutMs) first to handle the standard way to release a task gracefully.
 * If this function returned ERR_FAILED, the task doesn't comes to its end within the timeout. In this case, the task must be killed hard!
 * </description>
 * <param name="hTask" type="IN">Handle to task</param>
 * <param name="ulTimeoutMs" type="IN">Timeout in milliseconds. Defined values RTS_TIMEOUT_INFINITE, RTS_TIMEOUT_DEFAULT and RTS_TIMEOUT_NO_WAIT can be used here.</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Task exit gracefully</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Handle to task is invalid</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Task does not exit and could not be deleted hard! After this, only a reboot of
 *												 the controller can heal this situation!</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_TIMEOUT">Task does not exit within the timeout, but could be deleted hard. This is only a hint for the caller, but no serious error.</errorcode>
 */
DEF_DELETEITF_API(`RTS_RESULT',`CDECL',`SysTaskExit',`(RTS_HANDLE hTask, RTS_UI32 ulTimeoutMs)')

/**
 * <description>
 *  Set the exit flag of the specified task. On the next cycle, the task will exit.
 * </description>
 * <param name="hTask" type="IN">Handle to task</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTaskSetExit',`(RTS_HANDLE hTask)')

/**
 * <description>
 *  The creator of a task can call this function to release the task object, if the task ends is execution. So the task is responsible itself to delete this object.
 *	NOTE: The task object must not be used from outside the task after calling this function!
 * </description>
 * <param name="hTask" type="IN">Handle to task</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTaskAutoReleaseOnExit',`(RTS_HANDLE hTask)')

/**
 * <description>
 *  Is called to destroy the given task. 
 * </description>
 * <param name="hTask" type="IN">Handle to task</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTaskDestroy',`(RTS_HANDLE hTask)')

/**
 * <description>
 *  Is called to suspend the given task. 
 * </description>
 * <param name="hTask" type="IN">Handle to task</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTaskSuspend',`(RTS_HANDLE hTask)')

/**
 * <description>
 *  Is called to resume the given task. 
 * </description>
 * <param name="hTask" type="IN">Handle to task</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTaskResume',`(RTS_HANDLE hTask)')

/**
 * <description>
 *  Is called from the task, that end its execution. 
 * </description>
 * <param name="hTask" type="IN">Handle to task</param>
 * <param name="ulExitCode" type="IN">Exit code</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTaskEnd',`(RTS_HANDLE hTask, RTS_UINTPTR ulExitCode)')

/**
 * <description>
 *  Prevents excecution of the current task and addresses the OS scheduler to resume
 *  excecution after the given time (ms). 
 *	IMPLEMENTATION NOTE:
 *	- Don't use hTask in the implementation! If you must have the task handle, get it with SysTaskGetCurrent!
 * </description>
 * <param name="hTask" type="IN">Obsolete: Should be removed in future versions! Handle to task. Can be RTS_INVALID_HANDLE.</param>
 * <param name="ulMilliSeconds" type="IN">Time in milliseconds to sleep</param>
 * <result>error code</result>
 */
DEF_STATIC_API(`RTS_RESULT',`CDECL',`SysTaskWaitSleep',`(RTS_HANDLE hTask, RTS_UI32 ulMilliSeconds)')

/**
 * <description>
 *  Prevents excecution of the current task and addresses the OS scheduler to resume
 *  excecution after the given time (us). 
 *	IMPLEMENTATION NOTE:
 *	- Don't use hTask in the implementation! If you must have the task handle, get it with SysTaskGetCurrent!
 * </description>
 * <param name="hTask" type="IN">Obsolete: Should be removed in future versions! Handle to task. Can be RTS_INVALID_HANDLE.</param>
 * <param name="ptSleepUs" type="IN">Time in microseconds to sleep</param>
 * <result>error code</result>
 */
DEF_STATIC_API(`RTS_RESULT',`CDECL',`SysTaskWaitSleepUs',`(RTS_HANDLE hTask, RTS_SYSTIME *ptSleepUs)')

/**
 * <description>
 *  Wait to the next interval to be activated, if OS supports cyclic task.
 * </description>
 * <param name="hTask" type="IN">Handle to task</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTaskWaitInterval',`(RTS_HANDLE hTask)')

/**
 * <description>
 *  Is used to wait for exit of the specified join task. 
 * </description>
 * <param name="hTaskToJoin" type="IN">Task to join</param>
 * <param name="ulTimeoutMs" type="IN">Timeout in milliseconds to wait for join task</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysTaskJoin',`(RTS_HANDLE hTaskToJoin, RTS_UI32 ulTimeoutMs)')

/**
 * <description>
 *  Returns the task handle of the current running task. 
 * </description>
 * <param name="phTask" type="OUT">Pointer to task handle</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysTaskGetCurrent',`(RTS_HANDLE *phTask)')

/**
 * <description>
 *  Returns the operating system handle of the current running task. 
 * </description>
 * <param name="puiTaskOSHandle" type="OUT">Pointer to operating system task handle</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysTaskGetCurrentOSHandle',`(RTS_HANDLE *puiTaskOSHandle)')

/**
 * <description>
 *  Set the priority of the given task. 
 * </description>
 * <param name="hTask" type="IN">Handle to task</param>
 * <param name="ulPriority" type="IN">Task priority to set. Is the virtual priority between 0..255 and will be mapped to OS priority</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTaskSetPriority',`(RTS_HANDLE hTask, RTS_UI32 ulPriority)')

/**
 * <description>
 *	Get the runtime system priority of the given task. 
 * </description>
 * <param name="hTask" type="IN">Handle to task</param>
 * <param name="pulPriority" type="OUT">Pointer to get priority</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTaskGetPriority',`(RTS_HANDLE hTask, RTS_UI32 *pulPriority)')

/**
 * <description>
 *	Returns the operating system priority of the given task.
 * </description>
 * <param name="hTask" type="IN">Handle to task</param>
 * <param name="pulOSPriority" type="OUT">Pointer to get operating system priority</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTaskGetOSPriority',`(RTS_HANDLE hTask, RTS_UI32 *pulOSPriority)')

/**
 * <description>
 *	Returns the task info of the specified task.
 * </description>
 * <param name="hTask" type="IN">Handle to task</param>
 * <param name="ppInfo" type="OUT">Pointer pointer to get task info structure</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTaskGetInfo',`(RTS_HANDLE hTask, SYS_TASK_INFO **ppInfo)')

/**
 * <description>
 *	Returns the task name of the specified task.
 * </description>
 * <param name="hTask" type="IN">Handle to task</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="pResult" type="ERR_OK">Task name found</errorcode>
 * <errorcode name="pResult" type="ERR_PARAMETER">Invalid parameters</errorcode>
 * <errorcode name="pResult" type="ERR_FAILED">Task name not found</errorcode>
 * <result>pointer to task name</result>
 */
DEF_HANDLEITF_API(`char*',`CDECL',`SysTaskGetName',`(RTS_HANDLE hTask, RTS_RESULT *pResult)')

/**
 * <description>
 *  This function is called to mark entering the while loop.
 * </description>
 * <param name="hTask" type="IN">Handle to task</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTaskEnter',`(RTS_HANDLE hTask)')

/**
 * <description>
 *  This function is called to mark leaving the while loop. 
 * </description>
 * <param name="hTask" type="IN">Handle to task</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTaskLeave',`(RTS_HANDLE hTask)')

/**
 * <description>
 *  Get the current register context of the task. Task must be in suspended mode! 
 * </description>
 * <param name="hTask" type="IN">Handle to task</param>
 * <param name="pContext" type="OUT">Pointer to context</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTaskGetContext',`(RTS_HANDLE hTask, RegContext *pContext)')

/**
 * <description>
 *  Call the corresponding exception handler of the task. 
 * </description>
 * <param name="hTask" type="IN">Handle to task</param>
 * <param name="ulException" type="IN">Rts standard exception</param>
 * <param name="Context" type="IN">Context to detect the code location where the exception occurred</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysTaskGenerateException',`(RTS_HANDLE uiTaskOSHandle, RTS_UI32 ulException, RegContext Context)')

/**
 * <description>
 *  Function to investigate the stack task.
 * </description>
 * <param name="hTask" type="IN">Handle to task</param>
 * <param name="pulMaxDepth" type="OUT">Maximum stack depth</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysTaskCheckStack',`(RTS_HANDLE hTask, RTS_UI32 *pulMaxDepth)')

/**
 * <description>
 *  Function to get the operating system specific handle.
 * </description>
 * <param name="hTask" type="IN">Handle to task</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_HANDLE',`CDECL',`SysTaskGetOSHandle',`(RTS_HANDLE hTask)')

/**
 * <description>
 * OBSOLETE FUNCTION: Use SysTaskGetHandleByOSHandle() and SysTaskGetInfo() instead!
 *  Function to get the task handle specified by the operating system task handle.
 * </description>
 * <param name="uiTaskOSHandle" type="IN">Opertating system task handleHandle to task</param>
 * <result>Pointer to SYS_TASK_INFO</result>
 */
DEF_ITF_API(`SYS_TASK_INFO *',`CDECL',`SysTaskGetByOSHandle',`(RTS_HANDLE uiTaskOSHandle)')

/**
 * <description>
 *  Function to get the task handle specified by the operating system task handle.
 * </description>
 * <param name="uiTaskOSHandle" type="IN">Opertating system task handleHandle to task</param>
 * <param name="pResult" type="OUT">Pointer to error code.
 *		ERR_OK: Ok
 *		ERR_FAILED: Task not found
 * <result>Handle to the specified task</result>
 */
DEF_ITF_API2(`RTS_HANDLE',`CDECL',`SysTaskGetHandleByOSHandle',`(RTS_HANDLE uiTaskOSHandle, RTS_RESULT *pResult)')

/**
 * <description>
 *  Function to get the configured priority out of the settings. See category "Settings" | "Mapping task priorities" for details.
 * </description>
 * <param name="ulPriority" type="IN">Task priority</param>
 * <param name="pResult" type="OUT">Pointer to error code.
 *		ERR_OK: Priority is mapped
 *		ERR_FAILED: Original priority is returned, because no mapping is configured
 * </param>
 * <result>Configured priority</result>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`SysTaskGetConfiguredPriority',`(RTS_UI32 ulPriority, RTS_RESULT *pResult)')

/**
 * <description>
 *  Function to get the configured priority of a specified task out of the settings. See category "Settings" | "Mapping task priorities" for details.
 * </description>
 * <param name="hTask" type="IN">Handle to the task</param>
 * <param name="ulPriority" type="IN">Task priority</param>
 * <param name="pResult" type="OUT">Pointer to error code.
 *		ERR_OK: Priority is mapped
 *		ERR_FAILED: Original priority is returned, because no mapping is configured
 * </param>
 * <result>Configured priority</result>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`SysTaskGetConfiguredPriority2',`(RTS_HANDLE hTask, RTS_UI32 ulPriority, RTS_RESULT *pResult)')

/**
 * <description>
 *	Get the actual interval of a cyclic task. If the specified task is no cyclic task, the function return an error.
 * </description>
 * <param name="hTask" type="IN">Handle to the task</param>
 * <param name="pulInterval" type="OUT">Pointer to the interval in microseconds!</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysTaskGetInterval',`(RTS_HANDLE hTask, RTS_UI32 *pulInterval)')

/**
 * <description>
 *	Set the actual interval of a cyclic task. If the specified task is no cyclic task, the function return an error.
 *	This interface can be used to synchronize a task to another task or to events.
 * </description>
 * <param name="hTask" type="IN">Handle to the task</param>
 * <param name="ulInterval" type="IN">New interval in microseconds!</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysTaskSetInterval',`(RTS_HANDLE hTask, RTS_UI32 ulInterval)')


/* Obsolete function. Can be removed in the future */
typedef struct
{
	RTS_HANDLE hTask;
	RTS_HANDLE out;
}systaskgettaskhandle_struct ;
DEF_API(`void',`CDECL',`systaskgettaskhandle',`(systaskgettaskhandle_struct *p)',1,0)


#ifdef __cplusplus
}
#endif
