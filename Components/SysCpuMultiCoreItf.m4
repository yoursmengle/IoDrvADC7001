/**
 * <interfacename>SysCpuMultiCore</interfacename>
 * <description>
 * <p>This interface provides functions to manage multi core cpu system.</p>
 * <p>Naming convention: In this interface a core describes a logical processor, a logical CPU, independent of the physical hardware. 
 * A CoreId is a zero based number of a core, corresponding to the position of a bit in the CoreBits bitfield. E.g., a dual core processor 
 * with hyperthreading supplies four logical processors, SysMCGetNumOfCores returns 4 cores and they are numbered from 0 to 3.</p>
 * <p>The bitfield is placed in a processor word (XWORD ulCoreBits) inside the CpuCoreBits union in case the number of cores fits there in,
 * i.e. up to 32 cores on a 32 bit system, up to 64 cores on a 64 bit system. In case the number of cores exceed these values 
 * (i.e. nNumOfCores > SYSMCBITSPERXWORD), an allocated array of XWORDs is used (pulCoreBits) and this is where the functions SysMCBDAlloc 
 * and SysMCBDFree come in handy.</p>
 *
 * <p>NOTE:
 * SysMCBDAlloc also initializes the member nNumOfCores of the CpuCoreBindingDesc structure. In case a local declared variable of CpuCoreBindingDesc
 * is used, this member nNumOfCores should be initialized manually.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysCpuMultiCore')

REF_ITF(`CmpTraceMgrItf.m4')


struct tagCpuCoreBindingDesc;
/**
 * <category>Event parameter</category>
 * <element name="hTaskGroup" type="IN">Handle to task group where the binding is set.</element>
 * <element name="pCoreBinding" type="IN">Configuration which cores the group should use. Can be set by this event.</element>
 */
typedef struct
{
	RTS_HANDLE hTaskGroup;
    struct tagCpuCoreBindingDesc* pCoreBinding;
} EVTPARAM_SysCpuMC_GroupBinding;
#define EVTPARAMID_SysCpuMC_GroupBinding						0x0001
#define EVTVERSION_SysCpuMC_GroupBinding						0x0001

/**
 * <category>Events</category>
 * <description>Event is sent before start of the specified application</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpApp</param>
 */
#define EVT_GroupBinding					                    MAKE_EVENTID(EVTCLASS_INFO, 1)



/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Setting to bind the runtime process to the specified core (0 is the first core). If the value is -1, the process is unbound!</description>
 */
#define SYSMCKEY_INT_BINDPROCESS					"BindProcess.CoreID"
#ifndef SYSMCVALUE_INT_BINDPROCESS
	#define SYSMCVALUE_INT_BINDPROCESS				0
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Setting to enable/disable the CPU load system trace feature. With this feature you can upload the system trace "CpuCoreLoad" in CODESYS and you can see the CPU load
 *	in a trace window!
 * </description>
 */
#define SYSMCKEY_INT_CPULOADTRACE					"CpuLoadTrace.Enable"
#ifndef SYSMCVALUE_INT_CPULOADTRACE
	#define SYSMCVALUE_INT_CPULOADTRACE				1
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Setting to enable/disable the PLC load system trace feature. With this feature you can upload the system trace "PlcLoad" in CODESYS and you can see the CPU load
 *	in a trace window!
 * </description>
 */
#define SYSMCKEY_INT_PLCLOADTRACE					"PlcLoadTrace.Enable"
#ifndef SYSMCVALUE_INT_PLCLOADTRACE
	#define SYSMCVALUE_INT_PLCLOADTRACE				1
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting to configure which cores should be used by the IEC code. For notation see: SYSMCSUBKEY_TASKGROUP_CORESET. 
 * If not configured the default depends on the available license:
 * 1. No license available: This results in a single core license. Core 0 will be used by default.
 * 2. License available: This will result in a {0..Licensevalue-1} core set.
 * The core set can be overwritten using this setting. Pay attention to configure only the licensed number of cores.
 * </description>
 */
#define SYSMCKEY_STRING_IECCORESET					"IecCoreSet"
#ifndef SYSMCVALUE_STRING_IECCORESET
	#define SYSMCVALUE_STRING_IECCORESET			"{0..MAXCOREID}"
#endif

/**
 * <category>Static defines</category>
 * <description>Task group options
 * </description>
 * <element name="SYSMC_TASKGROUPMASK_STRATEGY">Mask to select the strategy bits of the task group (low byte). The strategy defines how the tasks of this group are bound to cores.</element>
 * <element name="SYSMC_TASKGROUPOPTION_MULTICORE_FREEFLOATING" type="IN">
 *  Default: Tasks will be freely moved around the cores by the operating system. 
 *  Depending of the binding set by SysMCSetTaskGroupBinding the task will behave differently:
 *      1. No bits set in the CpuCoreBindingDesc: All Cores will be used by the tasks. Tasks can be freely moved by the operating system.
 *      2. Bits set in the CpuCoreBindingDesc: The taks will be freely moved by the operating system within the specified cores. Note: This is not supported by all operating systems.
 * </element>
 * <element name="SYSMC_TASKGROUPOPTION_MULTICORE_SEQUENCIAL_PINNED" type="IN">The tasks of this group will be sequentially pinned.
 * The pinning is done by pinning each task one by one to the next configured core and then start over again. The task with the highest priority is pinned first.
 * The core used by the system group is stepped over in the first pinnig cycle.</element>
 * <element name="SYSMC_TASKGROUPOPTION_SINGLECORE" type="IN">The tasks of this group will be pinned to the same core.
 *  Depending of the binding set by SysMCSetTaskGroupBinding the task will behave differently
 *      1. No bits set in the CpuCoreBindingDesc: A core is selected by the runtime system.</element>
 *      2. One bit is set in the CpuCoreBindingDesc: This core will be used.</element>
 *      3. More bits set: Configuration error. Will not be accepted.
 * <element name="SYSMC_TASKGROUPMASK_OPTIONS" type="IN">Mask to select the options part of the flag field.</element>
 * <element name="SYSMC_TASKGROUPOPTION_GROUP_CONF" type="IN">Flag that indicates this group is in configuration mode.</element>
 * <element name="SYSMC_TASKGROUPOPTION_IEC_TASKS" type="IN">Flag that this task group contains contain IEC Tasks.</element>
 * <element name="SYSMC_TASKGROUPOPTION_AUTODELETE" type="IN">Flag to indicate that this group shold be deleted automatically if the last task was removed from this group.</element>
 */
#define SYSMC_TASKGROUPMASK_STRATEGY                        0x000000FF
#define SYSMC_TASKGROUPOPTION_MULTICORE_FREEFLOATING		0x00000000
#define SYSMC_TASKGROUPOPTION_MULTICORE_SEQUENCIAL_PINNED	0x00000001
#define SYSMC_TASKGROUPOPTION_SINGLECORE					0x00000002

#define SYSMC_TASKGROUPMASK_OPTIONS                         0x0000FF00
#define SYSMC_TASKGROUPOPTION_GROUP_CONF                    0x00000100
#define SYSMC_TASKGROUPOPTION_IEC_TASKS                     0x00000200
#define SYSMC_TASKGROUPOPTION_AUTODELETE                    0x00000400


/**
 * <category>Static defines</category>
 * <description>Task group names
 * </description>
 */
#ifndef SYSMC_TASKGROUPNAME_SYS
	#define SYSMC_TASKGROUPNAME_SYS "System"
#endif
#ifndef SYSMC_TASKGROUPNAME_IEC
	#define SYSMC_TASKGROUPNAME_IEC "IEC-Tasks"
#endif
#ifndef SYSMC_TASKGROUPNAME_COM
	#define SYSMC_TASKGROUPNAME_COM "Communication"
#endif
#ifndef SYSMC_TASKGROUPNAME_VIS
	#define SYSMC_TASKGROUPNAME_VIS "Visualization"
#endif

/**
 * <category>Settings</category>
 * <description>A base setting to configure task groups. The followind subsettings are available: Name, Optiion and CoreSet. The numbering starts with 1.
 * Example to bind all system tasks to core 0:
 * TaskGroup.1.Name=System
 * TaskGroup.1.Option=1
 * TaskGroup.1.CoreSet={0}
 * </description>
 */
#define SYSMCBASEKEY_TASKGROUP						"TaskGroup"

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting to name a task group. For predefined task group names see 'Task group names'.
 * Example:
 * TaskGroup.2.Name=IecTask
 * </description>
 */
#define SYSMCSUBKEY_TASKGROUP_NAME					"Name"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Setting to configure the options of a task group. See 'Task group options'.
 * Example:
 * TaskGroup.2.Option=2
 * </description>
 */
#define SYSMCSUBKEY_TASKGROUP_OPTION				"Option"
#ifndef SYSMCVALUE_INT_TASKGROUP_OPTION_DEFAULT
	#define SYSMCVALUE_INT_TASKGROUP_OPTION_DEFAULT	SYSMC_TASKGROUPOPTION_MULTICORE_FREEFLOATING
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting to configure a set of cores for a task group.
 * There is a placeholder for the highest core id named MAXCOREID to configure independently of the current num of cores.
 * To build more comlex expressions a range and a subtraction operator are provided.
 * Example:
 * TaskGroup.2.CoreSet={0..MAXCOREID-1}
 * TaskGroup.3.CoreSet={0,1,2}
 * </description>
 */
#define SYSMCSUBKEY_TASKGROUP_CORESET				"CoreSet"

/**
 * <category>Static defines</category>
 * <description>Number of bits in a processor word (XWORD)</description>
 */
#define SYSMCBITSPERXWORD (sizeof(RTS_IEC_XWORD) * 8)

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>CpuCoreBits</description>
 */
typedef union
{
	RTS_IEC_XWORD ulCoreBits;		
	RTS_IEC_XWORD *pulCoreBits;		
} CpuCoreBits;

/**
 * <description>CpuCoreBindingDesc</description>
 */
typedef struct tagCpuCoreBindingDesc
{
	RTS_IEC_UDINT nNumOfCores;		
	CpuCoreBits cores;		
} CpuCoreBindingDesc;

/**
 * <description>sysmcbdalloc</description>
 */
typedef struct tagsysmcbdalloc_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	CpuCoreBindingDesc *SysMCBDAlloc;	/* VAR_OUTPUT */	
} sysmcbdalloc_struct;

DEF_API(`void',`CDECL',`sysmcbdalloc',`(sysmcbdalloc_struct *p)',1,RTSITF_GET_SIGNATURE(0xECD5C206, 0xC7AAC7EB),0x03050B00)

/**
 * <description>sysmcbdcount</description>
 */
typedef struct tagsysmcbdcount_struct
{
	CpuCoreBindingDesc *pBindingDesc;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_UDINT SysMCBDCount;			/* VAR_OUTPUT */	
} sysmcbdcount_struct;

DEF_API(`void',`CDECL',`sysmcbdcount',`(sysmcbdcount_struct *p)',1,RTSITF_GET_SIGNATURE(0xA5E90785, 0x52EBF69E),0x03050B00)

/**
 * <description>sysmcbdfree</description>
 */
typedef struct tagsysmcbdfree_struct
{
	CpuCoreBindingDesc *pBindingDesc;	/* VAR_INPUT */	
	RTS_IEC_RESULT SysMCBDFree;			/* VAR_OUTPUT */	
} sysmcbdfree_struct;

DEF_API(`void',`CDECL',`sysmcbdfree',`(sysmcbdfree_struct *p)',1,RTSITF_GET_SIGNATURE(0x2D152790, 0x4E99D982),0x03050B00)

/**
 * <description>sysmcbdgetfirstid</description>
 */
typedef struct tagsysmcbdgetfirstid_struct
{
	CpuCoreBindingDesc *pBindingDesc;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_UDINT SysMCBDGetFirstID;	/* VAR_OUTPUT */	
} sysmcbdgetfirstid_struct;

DEF_API(`void',`CDECL',`sysmcbdgetfirstid',`(sysmcbdgetfirstid_struct *p)',1,RTSITF_GET_SIGNATURE(0x0413C991, 0xF3084CC6),0x03050B00)

/**
 * <description>sysmcbdgetnextid</description>
 */
typedef struct tagsysmcbdgetnextid_struct
{
	CpuCoreBindingDesc *pBindingDesc;	/* VAR_INPUT */	
	RTS_IEC_UDINT uPrevCoreID;			/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_UDINT SysMCBDGetNextID;		/* VAR_OUTPUT */	
} sysmcbdgetnextid_struct;

DEF_API(`void',`CDECL',`sysmcbdgetnextid',`(sysmcbdgetnextid_struct *p)',1,RTSITF_GET_SIGNATURE(0xDC0570FA, 0xB42D3BDD),0x03050B00)

/**
 * <description>sysmcbdisset</description>
 */
typedef struct tagsysmcbdisset_struct
{
	CpuCoreBindingDesc *pBindingDesc;	/* VAR_INPUT */	
	RTS_IEC_UDINT uCoreId;				/* VAR_INPUT */	
	RTS_IEC_RESULT SysMCBDIsSet;		/* VAR_OUTPUT */	
} sysmcbdisset_struct;

DEF_API(`void',`CDECL',`sysmcbdisset',`(sysmcbdisset_struct *p)',1,RTSITF_GET_SIGNATURE(0x54BC1578, 0xA3BEE463),0x03050B00)

/**
 * <description>sysmcgetload</description>
 */
typedef struct tagsysmcgetload_struct
{
	RTS_IEC_UDINT CoreID;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pPercent;				/* VAR_INPUT */	/* CPU-Core load in percent. */
	RTS_IEC_RESULT SysMCGetLoad;		/* VAR_OUTPUT */	
} sysmcgetload_struct;

DEF_API(`void',`CDECL',`sysmcgetload',`(sysmcgetload_struct *p)',1,0xEF6D21E5,0x03050B00)

/**
 *Returns the number of available cores.
 *Available means: Available to be used by runtime system.
 */
typedef struct tagsysmcgetnumofcores_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to retrieve optional error code. */
	RTS_IEC_DWORD SysMCGetNumOfCores;	/* VAR_OUTPUT */	
} sysmcgetnumofcores_struct;

DEF_API(`void',`CDECL',`sysmcgetnumofcores',`(sysmcgetnumofcores_struct *p)',1,0x9360E181,0x03050B00)

/**
 *Read the binding description of a process.
 */
typedef struct tagsysmcgetprocessbinding_struct
{
	RTS_IEC_HANDLE hProcess;			/* VAR_INPUT */	
	CpuCoreBindingDesc *pBindingDesc;	/* VAR_INPUT */	
	RTS_IEC_RESULT SysMCGetProcessBinding;	/* VAR_OUTPUT */	
} sysmcgetprocessbinding_struct;

DEF_API(`void',`CDECL',`sysmcgetprocessbinding',`(sysmcgetprocessbinding_struct *p)',1,RTSITF_GET_SIGNATURE(0x630248E0, 0x2F2E120C),0x03050B00)

/**
 *Read the binding description of a task.
 */
typedef struct tagsysmcgettaskbinding_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	
	CpuCoreBindingDesc *pBindingDesc;	/* VAR_INPUT */	
	RTS_IEC_RESULT SysMCGetTaskBinding;	/* VAR_OUTPUT */	
} sysmcgettaskbinding_struct;

DEF_API(`void',`CDECL',`sysmcgettaskbinding',`(sysmcgettaskbinding_struct *p)',1,RTSITF_GET_SIGNATURE(0x4571B9EE, 0x2D12BDE0),0x03050B00)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysCpuMultiCoreOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysCpuMultiCoreOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>
 * <p>Task group maintenance</p>
 * This function adds a task group. In case the task group is already present, the handle is returned anyway but an internal reference counter is incremented.
 * </description>
 * <param name="pszTaskGroup" type="IN">The name of the task group to add</param>
 * <param name="taskGroupOptions" type="IN">See task group options</param>
 * <param name="pResult" type="IN">Pointer to a variable to return an errorcode (optional)</param>
 * <result>Returns the handle to the newly added task group or RTS_INVALID_HANDLE.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The required memory pool was not initialized.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">Not enough memory to allocate.</errorcode>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`SysMCAddTaskGroup',`(char *pszTaskGroup, RTS_UI32 taskGroupOptions, RTS_RESULT *pResult)')

/**
 * <description>
 * <p>Task group maintenance</p>
 * This function removes a task group. The group is not deleted until the internal reference counter reaches zero. 
 * </description>
 * <param name="hTaskGroup" type="IN">The handle to a previous added task group</param>
 * <result>Returns an errorcode.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">The given handle is invalid.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCRemoveTaskGroup',`(RTS_HANDLE hTaskGroup)')

/**
 * <description>
 * <p>Task group maintenance</p>
 * This function searches for a task group and returns its handle on success.
 * </description>
 * <param name="pszTaskGroup" type="IN">The name of the task group to search for</param>
 * <param name="pResult" type="IN">Pointer to a variable to return an errorcode (optional)</param>
 * <result>Returns the handle to the searched task group or RTS_INVALID_HANDLE.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The required memory pool was not initialized.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">The task group was not found.</errorcode>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`SysMCFindTaskGroup',`(char *pszTaskGroup, RTS_RESULT *pResult)')

/**
 * <description>
 * <p>Task group maintenance</p>
 * This function returns the first found task group. The returned handle may be used for SysMCGetNextTaskGroup.
 * </description>
 * <param name="pResult" type="IN">Pointer to a variable to return an errorcode</param>
 * <result>Returns the handle to the searched task group or RTS_INVALID_HANDLE.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The required memory pool was not initialized.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">The task group was not found.</errorcode>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`SysMCGetFirstTaskGroup',`(RTS_RESULT *pResult)')

/**
 * <description>
 * <p>Task group maintenance</p>
 * This function returns the next found task group and is used to iterate through all task groups until the result is ERR_END_OF_OBJECT.
 * </description>
 * <param name="hPrevTaskGroup" type="IN">The handle to a previous found task group</param>
 * <param name="pResult" type="IN">Pointer to a variable to return an errorcode</param>
 * <result>Returns the handle to the searched task group or RTS_INVALID_HANDLE.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The required memory pool was not initialized.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">The given handle is invalid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_END_OF_OBJECT">There are no more task groups to find.</errorcode>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`SysMCGetNextTaskGroup',`(RTS_HANDLE hPrevTaskGroup, RTS_RESULT *pResult)')

/**
 * <description>
 * <p>Task group maintenance</p>
 * This function returns the name of a task group with the given handle.
 * </description>
 * <param name="hTaskGroup" type="IN">The handle to a task group</param>
 * <param name="pResult" type="IN">Pointer to a variable to return an errorcode</param>
 * <result>Returns a pointer to the name of the task group or NULL.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The required memory pool was not initialized.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">The given handle is invalid.</errorcode>
 */
DEF_ITF_API(`char*',`CDECL',`SysMCGetTaskGroupName',`(RTS_HANDLE hTaskGroup, RTS_RESULT *pResult)')

/**
 * <description>
 * <p>Task group maintenance</p>
 * This function returns the binding description of a task group with the given handle.
 * </description>
 * <param name="hTaskGroup" type="IN">The handle to a task group</param>
 * <param name="pResult" type="IN">Pointer to a variable to return an errorcode</param>
 * <result>Returns a pointer to binding description of the task group or NULL.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The required memory pool was not initialized.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">The given handle is invalid.</errorcode>
 */
DEF_ITF_API(`CpuCoreBindingDesc*',`CDECL',`SysMCGetTaskGroupBinding',`(RTS_HANDLE hTaskGroup, RTS_RESULT *pResult)')

/**
 * <description>
 * <p>Task group maintenance</p>
 * This function returns the options of a task group with the given handle.
 * </description>
 * <param name="hTaskGroup" type="IN">The handle to a task group</param>
 * <param name="pResult" type="IN">Pointer to a variable to return an errorcode</param>
 * <result>Returns the options of the task group (see task group options).</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The required memory pool was not initialized.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">The given handle is invalid.</errorcode>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`SysMCGetTaskGroupOptions',`(RTS_HANDLE hTaskGroup, RTS_RESULT *pResult)')

/**
 * <description>
 * <p>Task group maintenance</p>
 * This function sets the binding description of a task group with the given handle. No further action is taken.
 * </description>
 * <param name="hTaskGroup" type="IN">The handle to a task group</param>
 * <param name="pBindingDesc" type="IN">Pointer to the description of the core binding.</param>
 * <result>Returns an errorcode.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The required memory pool was not initialized.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">The given handle is invalid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">The given binding description is invalid.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCSetTaskGroupBinding',`(RTS_HANDLE hTaskGroup, CpuCoreBindingDesc *pBindingDesc)')

/**
 * <description>
 * <p>Task group maintenance</p>
 * This function adds a task to a task group.
 * After that it binds the tasks of the group if not in configuration mode (see SysMCBeginTaskGroupConf/SysMCEndTaskGroupConf).
 * NOTE: In case the process is bound to one core, no task binding is possible at all, but the function returns ERR_OK anyway.
 * </description>
 * <param name="hSysTask" type="IN">The handle to a SysTask</param>
 * <param name="hTaskGroup" type="IN">The handle to a task group</param>
 * <result>Returns an errorcode.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The required memory pool was not initialized.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">The given handle is invalid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">The given SysTask handle is invalid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_DUPLICATE">The given SysTask handle is already added.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">Not enough memory to allocate.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">The binding configuration is invalid.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCAddToTaskGroup',`(RTS_HANDLE hSysTask, RTS_HANDLE hTaskGroup)')

/**
 * <description>
 * <p>Task group maintenance</p>
 * This function removes a task from a task group.
 * </description>
 * <param name="hSysTask" type="IN">The handle to a SysTask</param>
 * <param name="hTaskGroup" type="IN">The handle to a task group</param>
 * <result>Returns an errorcode.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The required memory pool was not initialized.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">The given handle is invalid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">The given SysTask handle is invalid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">The given SysTask handle was not found.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCRemoveFromTaskGroup',`(RTS_HANDLE hSysTask, RTS_HANDLE hTaskGroup)')

/**
 * <description>
 * <p>Task group maintenance</p>
 * This function starts the configuration mode of task groups.
 * </description>
 * <param name="hTaskGroup" type="IN">The handle to a task group</param>
 * <result>Returns an errorcode.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">The given handle is invalid.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCBeginTaskGroupConf',`(RTS_HANDLE hTaskGroup)')

/**
 * <description>
 * <p>Task group maintenance</p>
 * This function ends the configuration mode of task groups and than binds the tasks of all groups as configured.
 * NOTE: In case the process is bound to one core, no task binding is possible at all, but the function returns ERR_OK anyway.
 * </description>
 * <param name="hTaskGroup" type="IN">The handle to a task group</param>
 * <result>Returns an errorcode.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">The given handle is invalid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">The binding configuration is invalid.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCEndTaskGroupConf',`(RTS_HANDLE hTaskGroup)')

/**
 * <description>
 * <p>CpuCoreBindingDesc helper function</p>
 * SysMCBDAlloc allocates a CpuCoreBindingDesc which should be freed with SysMCBDFree after usage. Initializes the nNumOfCores member. In case nNumOfCores > SYSMCBITSPERXWORD an array of appropriate XWORDs is allocated to pulCoreBits.
 * </description>
 * <param name="pResult" type="IN">Pointer to a variable to return an errorcode (optional)</param>
 * <result>Returns a pointer to CpuCoreBindingDesc or NULL if no memory is available.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">A valid pointer is returned.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">Not enough memory is available.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">Component is not yet initialized.</errorcode>
 */
DEF_ITF_API(`CpuCoreBindingDesc *',`CDECL',`SysMCBDAlloc',`(RTS_RESULT* pResult)')

/**
 * <description>
 * <p>CpuCoreBindingDesc helper function</p>
 * SysMCBDFree frees an CpuCoreBindingDesc which should be allocated with SysMCBDAlloc before usage.
 * </description>
 * <param name="pBindingDesc" type="IN">Pointer to the description of the core binding.</param>
 * <result>Returns an errorcode.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Memory is sucessfully freed.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">No appropriate memory block was found.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">CpuCoreBindingDesc is invalid pointer.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCBDFree',`(CpuCoreBindingDesc *pBindingDesc)')

/**
 * <description>
 * <p>CpuCoreBindingDesc helper function</p>
 * SysMCBDZero clears all the CpuCoreBits of the given CpuCoreBindingDesc. SysMCBDZero should be called prior to any call of SysMCBDSet.
 * </description>
 * <param name="pBindingDesc" type="IN">Pointer to the description of the core binding.</param>
 * <result>Returns an errorcode.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Operation sucessfully finished.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">CpuCoreBindingDesc is invalid pointer.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCBDZero',`(CpuCoreBindingDesc *pBindingDesc)')

/**
 * <description>
 * <p>CpuCoreBindingDesc helper function</p>
 * Set the appropriate bit for uCoreId in the CpuCoreBindingDesc.CpuCoreBits. SysMCBDZero should be called prior to any call of SysMCBDSet.
 * </description>
 * <param name="pBindingDesc" type="IN">Pointer to the description of the core binding.</param>
 * <param name="uCoreId" type="IN">Identifies the core ID. Starting with 0=first core, ...</param>
 * <result>Returns an errorcode.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Operation sucessfully finished.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">CpuCoreBindingDesc is invalid pointer or uCoreId is invalid.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCBDSet',`(CpuCoreBindingDesc *pBindingDesc, RTS_UI32 uCoreId)')

/**
 * <description>
 * <p>CpuCoreBindingDesc helper function</p>
 * SysMCBDReset resets the appropriate bit for uCoreId in the CpuCoreBindingDesc.CpuCoreBits, i.e. clears it.
 * </description>
 * <result>Returns an errorcode.</result>
 * <param name="pBindingDesc" type="IN">Pointer to the description of the core binding.</param>
 * <param name="uCoreId" type="IN">Identifies the core ID. Starting with 0=first core, ...</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Operation sucessfully finished.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">CpuCoreBindingDesc is invalid pointer or uCoreId is invalid.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCBDReset',`(CpuCoreBindingDesc *pBindingDesc, RTS_UI32 uCoreId)')

/**
 * <description>
 * <p>CpuCoreBindingDesc helper function</p>
 * SysMCBDIsSet tests the appropriate bit for uCoreId in CpuCoreBindingDesc.CpuCoreBits: see errorcode
 * </description>
 * <result>Returns an errorcode.</result>
 * <param name="pBindingDesc" type="IN">Pointer to the description of the core binding.</param>
 * <param name="uCoreId" type="IN">Identifies the core ID. Starting with 0=first core, ...</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Bit is set.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Bit is not set.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">CpuCoreBindingDesc is invalid pointer or uCoreId is invalid.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCBDIsSet',`(CpuCoreBindingDesc *pBindingDesc, RTS_UI32 uCoreId)')

/**
 * <description>
 * <p>CpuCoreBindingDesc helper function</p>
 * SysMCBDCount counts the set bits in CpuCoreBindingDesc.CpuCoreBits.
 * </description>
 * <result>Returns the number of the bits set.</result>
 * <param name="pBindingDesc" type="IN">Pointer to the description of the core binding.</param>
 * <param name="pResult" type="IN">Pointer to a variable to return an errorcode (optional)</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Operation sucessfully finished.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">CpuCoreBindingDesc is invalid pointer.</errorcode>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`SysMCBDCount',`(CpuCoreBindingDesc *pBindingDesc, RTS_RESULT* pResult)')

/**
 * <description>
 * <p>CpuCoreBindingDesc helper function</p>
 * SysMCBDGetFirstID returns the CoreId (i.e. the position) of the first set bit in CpuCoreBindingDesc.CpuCoreBits.
 * </description>
 * <param name="pBindingDesc" type="IN">Pointer to the description of the core binding.</param>
 * <param name="pResult" type="IN">Pointer to a variable to return an errorcode.</param>
 * <result>Returns a valid CoreId if ERR_OK, otherwise the result is undefined.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">First found CoreId is returned.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">CpuCoreBindingDesc is invalid pointer.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_END_OF_OBJECT">No core was set.</errorcode>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`SysMCBDGetFirstID',`(CpuCoreBindingDesc *pBindingDesc, RTS_RESULT* pResult)')

/**
 * <description>
 * <p>CpuCoreBindingDesc helper function</p>
 * SysMCBDGetNextID returns the CoreId (i.e. the position) of the next set bit in CpuCoreBindingDesc.CpuCoreBits.
 * </description>
 * <param name="pBindingDesc" type="IN">Pointer to the description of the core binding.</param>
 * <param name="uPrevCoreID" type="IN">CoreId found by SysMCBDGetFirstID or a previous call of SysMCBDGetNextID.</param>
 * <param name="pResult" type="IN">Pointer to a variable to return an errorcode.</param>
 * <result>Returns a valid CoreId if ERR_OK, otherwise the result is undefined.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Next found CoreId is returned.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">CpuCoreBindingDesc is invalid pointer.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_END_OF_OBJECT">No more cores were set.</errorcode>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`SysMCBDGetNextID',`(CpuCoreBindingDesc *pBindingDesc, RTS_UI32 uPrevCoreID, RTS_RESULT* pResult)')

/**
 * <description>
 * <p>Function to bind a process to a core or a set of cores.</p>
 * <p>
 * To set the corresponding bit(s) in CpuCoreBindingDesc.CpuCoreBits use SysMCBDSet.
 * </p>
 * </description>
 * <param name="pBindingDesc" type="IN">Pointer to the binding description for the new core binding.</param>
 * <param name="hProcess" type="IN">Handle of the process to bind.</param>
 * <result>Returns the result.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Parameter is invalid, e.g. core does not exist.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_OPERATION_DENIED">Operation is denied on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">Handle is invalid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Function failed for any reason on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Function is not implemented.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOT_SUPPORTED">Function is not supported.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCBindProcess',`(CpuCoreBindingDesc *pBindingDesc, RTS_IEC_HANDLE hProcess)')

/**
 * <description>
 * The OS implementation of SysMCBindProcess
 * </description>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCBindProcess_',`(CpuCoreBindingDesc *pBindingDesc, RTS_IEC_HANDLE hProcess)')

/**
 * <description>
 * <p>Function to bind a task to a core or a set of cores.</p>
 * <p>
 * To set the corresponding bit(s) in CpuCoreBindingDesc.CpuCoreBits use SysMCBDSet.
 * </p>
 * </description>
 * <param name="pBindingDesc" type="IN">Pointer to the binding description for the new core binding.</param>
 * <param name="hTask" type="IN">Handle of the task to bind.</param>
 * <result>Returns the result.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Parameter is invalid, e.g. core does not exist.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_OPERATION_DENIED">Operation is denied on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">Handle is invalid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Function failed for any reason on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Function is not implemented.</errorcode> 
 * <errorcode name="RTS_RESULT" type="ERR_NOT_SUPPORTED">Function is not supported.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCBindTask',`(CpuCoreBindingDesc *pBindingDesc, RTS_IEC_HANDLE hTask)')

/**
 * <description>
 * The OS implementation of SysMCBindTask
 * </description>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCBindTask_',`(CpuCoreBindingDesc *pBindingDesc, RTS_IEC_HANDLE hTask)')

/**
 * <description>
 * <p>Function to remove the binding to a core or a set of cores of a process.</p>
 * <p>
 * This means the OS is again responsible on which core(s) the process is allowed to run on.
 * </p>
 * </description>
 * <param name="hProcess" type="IN">Handle of the process to unbind.</param>
 * <result>Returns the result.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Parameter is invalid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_OPERATION_DENIED">Operation is denied on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">Handle is invalid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Function failed for any reason on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Function is not implemented.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCUnbindProcess',`(RTS_IEC_HANDLE hProcess)')

/**
 * <description>
 * The OS implementation of SysMCUnbindProcess
 * </description>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCUnbindProcess_',`(RTS_IEC_HANDLE hProcess)')

/**
 * <description>
 * <p>Function to remove the binding to a core or a group of cores of a task.</p>
 * <p>
 * This means the OS is again responsible on which core(s) the task is allowed to run on.
 * </p>
 * </description>
 * <param name="hTask" type="IN">Handle of the task to unbind.</param>
 * <result>Returns the result.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Parameter is invalid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_OPERATION_DENIED">Operation is denied on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">Handle is invalid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Function failed for any reason on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Function is not implemented.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCUnbindTask',`(RTS_IEC_HANDLE hTask)')

/**
 * <description>
 * The OS implementation of SysMCUnbindTask
 * </description>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCUnbindTask_',`(RTS_IEC_HANDLE hTask)')

/**
 * <description>
 * OPTIONAL FUNCTION:
 * <p>Function to get the current average workload of a dedicated core, identified by the input parameter.
 *  NOTE:
 *  This function may not be supported by every operating system!</p>
 * </description>
 * <param name="uCoreID" type="IN">Identifies the core whose load has to be returned. Starting with 0=first core, ...
 *	NOTE:
 *	If uCoreID=RTS_UI32_MAX, average CPU load over all cores in percent is returned!
 * </param>
 * <param name="pPercent" type="OUT">CPU-Core load in percent.</param>
 * <result>Returns the result.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Parameter is invalid, e.g. core does not exist.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">Function is not initialized.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOBUFFER">Not enough memory for the performance counters</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Function failed for any reason on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Function is not implemented.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCGetLoad',`(RTS_UI32 uCoreID, RTS_UI8 *pPercent)')

/**
 * <description>
 * The OS implementation of SysMCGetLoad
 * </description>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCGetLoad_',`(RTS_UI32 uCoreID, RTS_UI8 *pPercent)')

/**
 * <description>
 * <p>Function to get the number of cores available for use by the runtime system.</p>
 * </description>
 * <param name="pResult" type="IN">Pointer to a variable to return an errorcode (optional)</param>
 * <result>Returns the number of cores.</result>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_FAILED">Function failed for any reason on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Function is not implemented.</errorcode> 
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`SysMCGetNumOfCores',`(RTS_RESULT* pResult)')

/**
 * <description>
 * The OS implementation of SysMCGetNumOfCores
 * </description>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`SysMCGetNumOfCores_',`(RTS_RESULT* pResult)')

/**
 * <description>
 * <p>Function to read the binding of a process to core(s).</p>
 *  NOTE:
 *  To obtain the binding of the current process hProcess may be RTS_INVALID_HANDLE.
 *  NOTE:
 *  To obtain the CoreIds set in CpuCoreBindingDesc use SysMCBDGetFirstID and SysMCBDGetNextID.
 * </description>
 * <param name="hProcess" type="IN">Handle of the process or RTS_INVALID_HANDLE for current process.</param>
 * <param name="pBindingDesc" type="OUT">Pointer to the binding description for the core binding.</param>
 * <result>Returns the result.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Parameter is invalid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Function failed for any reason on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Function is not implemented.</errorcode> 
 * <errorcode name="RTS_RESULT" type="ERR_NOT_SUPPORTED">Function is not supported.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCGetProcessBinding',`(RTS_IEC_HANDLE hProcess, CpuCoreBindingDesc *pBindingDesc)')

/**
 * <description>
 * The OS implementation of SysMCGetProcessBinding
 * </description>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCGetProcessBinding_',`(RTS_IEC_HANDLE hProcess, CpuCoreBindingDesc *pBindingDesc)')

/**
 * <description>
 * <p>Function to read the binding of a task to core(s).</p>
 *  NOTE:
 *  To obtain the binding of the current task hTask may be RTS_INVALID_HANDLE.
 *  NOTE:
 *  Operating system dependent this function may support only the current task.
 *  NOTE:
 *  To obtain the CoreIds set in CpuCoreBindingDesc use SysMCBDGetFirstID and SysMCBDGetNextID.
 * </description>
 * <param name="hTask" type="IN">Handle of the task or RTS_INVALID_HANDLE for current task.</param>
 * <param name="pBindingDesc" type="OUT">Pointer to the binding description for the core binding.</param>
 * <result>Returns the result.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Parameter is invalid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Function failed for any reason on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Function is not implemented.</errorcode> 
 * <errorcode name="RTS_RESULT" type="ERR_NOT_SUPPORTED">Function is not supported.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCGetTaskBinding',`(RTS_IEC_HANDLE hTask, CpuCoreBindingDesc *pBindingDesc)')

/**
 * <description>
 * The OS implementation of SysMCGetTaskBinding
 * </description>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCGetTaskBinding_',`(RTS_IEC_HANDLE hTask, CpuCoreBindingDesc *pBindingDesc)')

/**
 * <description>
 * <p>Function to read current CoreId the calling process or task is running on.</p>
 * </description>
 * <param name="pResult" type="IN">Pointer to a variable to return an errorcode (optional)</param>
 * <result>Returns the current CoreId.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Function failed for any reason on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Function is not implemented.</errorcode> 
 * <errorcode name="RTS_RESULT" type="ERR_NOT_SUPPORTED">Function is not supported.</errorcode>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`SysMCGetCurrentCoreID',`(RTS_RESULT* pResult)')

/**
 * <description>
 * The OS implementation of SysMCGetCurrentCoreID
 * </description>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`SysMCGetCurrentCoreID_',`(RTS_RESULT* pResult)')

#ifdef __cplusplus
}
#endif
