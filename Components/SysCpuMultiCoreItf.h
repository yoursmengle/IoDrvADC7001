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


	
	
#ifndef _SYSCPUMULTICOREITF_H_
#define _SYSCPUMULTICOREITF_H_

#include "CmpStd.h"

 

 




#include "CmpTraceMgrItf.h"


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
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

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

void CDECL CDECL_EXT sysmcbdalloc(sysmcbdalloc_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSMCBDALLOC_IEC) (sysmcbdalloc_struct *p);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBDALLOC_NOTIMPLEMENTED)
	#define USE_sysmcbdalloc
	#define EXT_sysmcbdalloc
	#define GET_sysmcbdalloc(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysmcbdalloc(p0) 
	#define CHK_sysmcbdalloc  FALSE
	#define EXP_sysmcbdalloc  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysmcbdalloc
	#define EXT_sysmcbdalloc
	#define GET_sysmcbdalloc(fl)  CAL_CMGETAPI( "sysmcbdalloc" ) 
	#define CAL_sysmcbdalloc  sysmcbdalloc
	#define CHK_sysmcbdalloc  TRUE
	#define EXP_sysmcbdalloc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdalloc", (RTS_UINTPTR)sysmcbdalloc, 1, RTSITF_GET_SIGNATURE(0xECD5C206, 0xC7AAC7EB), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_sysmcbdalloc
	#define EXT_sysmcbdalloc
	#define GET_sysmcbdalloc(fl)  CAL_CMGETAPI( "sysmcbdalloc" ) 
	#define CAL_sysmcbdalloc  sysmcbdalloc
	#define CHK_sysmcbdalloc  TRUE
	#define EXP_sysmcbdalloc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdalloc", (RTS_UINTPTR)sysmcbdalloc, 1, RTSITF_GET_SIGNATURE(0xECD5C206, 0xC7AAC7EB), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoresysmcbdalloc
	#define EXT_SysCpuMultiCoresysmcbdalloc
	#define GET_SysCpuMultiCoresysmcbdalloc  ERR_OK
	#define CAL_SysCpuMultiCoresysmcbdalloc  sysmcbdalloc
	#define CHK_SysCpuMultiCoresysmcbdalloc  TRUE
	#define EXP_SysCpuMultiCoresysmcbdalloc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdalloc", (RTS_UINTPTR)sysmcbdalloc, 1, RTSITF_GET_SIGNATURE(0xECD5C206, 0xC7AAC7EB), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_sysmcbdalloc
	#define EXT_sysmcbdalloc
	#define GET_sysmcbdalloc(fl)  CAL_CMGETAPI( "sysmcbdalloc" ) 
	#define CAL_sysmcbdalloc  sysmcbdalloc
	#define CHK_sysmcbdalloc  TRUE
	#define EXP_sysmcbdalloc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdalloc", (RTS_UINTPTR)sysmcbdalloc, 1, RTSITF_GET_SIGNATURE(0xECD5C206, 0xC7AAC7EB), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_sysmcbdalloc  PFSYSMCBDALLOC_IEC pfsysmcbdalloc;
	#define EXT_sysmcbdalloc  extern PFSYSMCBDALLOC_IEC pfsysmcbdalloc;
	#define GET_sysmcbdalloc(fl)  s_pfCMGetAPI2( "sysmcbdalloc", (RTS_VOID_FCTPTR *)&pfsysmcbdalloc, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0xECD5C206, 0xC7AAC7EB), 0x03050B00)
	#define CAL_sysmcbdalloc  pfsysmcbdalloc
	#define CHK_sysmcbdalloc  (pfsysmcbdalloc != NULL)
	#define EXP_sysmcbdalloc   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdalloc", (RTS_UINTPTR)sysmcbdalloc, 1, RTSITF_GET_SIGNATURE(0xECD5C206, 0xC7AAC7EB), 0x03050B00) 
#endif


/**
 * <description>sysmcbdcount</description>
 */
typedef struct tagsysmcbdcount_struct
{
	CpuCoreBindingDesc *pBindingDesc;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_UDINT SysMCBDCount;			/* VAR_OUTPUT */	
} sysmcbdcount_struct;

void CDECL CDECL_EXT sysmcbdcount(sysmcbdcount_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSMCBDCOUNT_IEC) (sysmcbdcount_struct *p);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBDCOUNT_NOTIMPLEMENTED)
	#define USE_sysmcbdcount
	#define EXT_sysmcbdcount
	#define GET_sysmcbdcount(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysmcbdcount(p0) 
	#define CHK_sysmcbdcount  FALSE
	#define EXP_sysmcbdcount  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysmcbdcount
	#define EXT_sysmcbdcount
	#define GET_sysmcbdcount(fl)  CAL_CMGETAPI( "sysmcbdcount" ) 
	#define CAL_sysmcbdcount  sysmcbdcount
	#define CHK_sysmcbdcount  TRUE
	#define EXP_sysmcbdcount  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdcount", (RTS_UINTPTR)sysmcbdcount, 1, RTSITF_GET_SIGNATURE(0xA5E90785, 0x52EBF69E), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_sysmcbdcount
	#define EXT_sysmcbdcount
	#define GET_sysmcbdcount(fl)  CAL_CMGETAPI( "sysmcbdcount" ) 
	#define CAL_sysmcbdcount  sysmcbdcount
	#define CHK_sysmcbdcount  TRUE
	#define EXP_sysmcbdcount  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdcount", (RTS_UINTPTR)sysmcbdcount, 1, RTSITF_GET_SIGNATURE(0xA5E90785, 0x52EBF69E), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoresysmcbdcount
	#define EXT_SysCpuMultiCoresysmcbdcount
	#define GET_SysCpuMultiCoresysmcbdcount  ERR_OK
	#define CAL_SysCpuMultiCoresysmcbdcount  sysmcbdcount
	#define CHK_SysCpuMultiCoresysmcbdcount  TRUE
	#define EXP_SysCpuMultiCoresysmcbdcount  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdcount", (RTS_UINTPTR)sysmcbdcount, 1, RTSITF_GET_SIGNATURE(0xA5E90785, 0x52EBF69E), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_sysmcbdcount
	#define EXT_sysmcbdcount
	#define GET_sysmcbdcount(fl)  CAL_CMGETAPI( "sysmcbdcount" ) 
	#define CAL_sysmcbdcount  sysmcbdcount
	#define CHK_sysmcbdcount  TRUE
	#define EXP_sysmcbdcount  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdcount", (RTS_UINTPTR)sysmcbdcount, 1, RTSITF_GET_SIGNATURE(0xA5E90785, 0x52EBF69E), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_sysmcbdcount  PFSYSMCBDCOUNT_IEC pfsysmcbdcount;
	#define EXT_sysmcbdcount  extern PFSYSMCBDCOUNT_IEC pfsysmcbdcount;
	#define GET_sysmcbdcount(fl)  s_pfCMGetAPI2( "sysmcbdcount", (RTS_VOID_FCTPTR *)&pfsysmcbdcount, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0xA5E90785, 0x52EBF69E), 0x03050B00)
	#define CAL_sysmcbdcount  pfsysmcbdcount
	#define CHK_sysmcbdcount  (pfsysmcbdcount != NULL)
	#define EXP_sysmcbdcount   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdcount", (RTS_UINTPTR)sysmcbdcount, 1, RTSITF_GET_SIGNATURE(0xA5E90785, 0x52EBF69E), 0x03050B00) 
#endif


/**
 * <description>sysmcbdfree</description>
 */
typedef struct tagsysmcbdfree_struct
{
	CpuCoreBindingDesc *pBindingDesc;	/* VAR_INPUT */	
	RTS_IEC_RESULT SysMCBDFree;			/* VAR_OUTPUT */	
} sysmcbdfree_struct;

void CDECL CDECL_EXT sysmcbdfree(sysmcbdfree_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSMCBDFREE_IEC) (sysmcbdfree_struct *p);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBDFREE_NOTIMPLEMENTED)
	#define USE_sysmcbdfree
	#define EXT_sysmcbdfree
	#define GET_sysmcbdfree(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysmcbdfree(p0) 
	#define CHK_sysmcbdfree  FALSE
	#define EXP_sysmcbdfree  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysmcbdfree
	#define EXT_sysmcbdfree
	#define GET_sysmcbdfree(fl)  CAL_CMGETAPI( "sysmcbdfree" ) 
	#define CAL_sysmcbdfree  sysmcbdfree
	#define CHK_sysmcbdfree  TRUE
	#define EXP_sysmcbdfree  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdfree", (RTS_UINTPTR)sysmcbdfree, 1, RTSITF_GET_SIGNATURE(0x2D152790, 0x4E99D982), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_sysmcbdfree
	#define EXT_sysmcbdfree
	#define GET_sysmcbdfree(fl)  CAL_CMGETAPI( "sysmcbdfree" ) 
	#define CAL_sysmcbdfree  sysmcbdfree
	#define CHK_sysmcbdfree  TRUE
	#define EXP_sysmcbdfree  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdfree", (RTS_UINTPTR)sysmcbdfree, 1, RTSITF_GET_SIGNATURE(0x2D152790, 0x4E99D982), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoresysmcbdfree
	#define EXT_SysCpuMultiCoresysmcbdfree
	#define GET_SysCpuMultiCoresysmcbdfree  ERR_OK
	#define CAL_SysCpuMultiCoresysmcbdfree  sysmcbdfree
	#define CHK_SysCpuMultiCoresysmcbdfree  TRUE
	#define EXP_SysCpuMultiCoresysmcbdfree  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdfree", (RTS_UINTPTR)sysmcbdfree, 1, RTSITF_GET_SIGNATURE(0x2D152790, 0x4E99D982), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_sysmcbdfree
	#define EXT_sysmcbdfree
	#define GET_sysmcbdfree(fl)  CAL_CMGETAPI( "sysmcbdfree" ) 
	#define CAL_sysmcbdfree  sysmcbdfree
	#define CHK_sysmcbdfree  TRUE
	#define EXP_sysmcbdfree  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdfree", (RTS_UINTPTR)sysmcbdfree, 1, RTSITF_GET_SIGNATURE(0x2D152790, 0x4E99D982), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_sysmcbdfree  PFSYSMCBDFREE_IEC pfsysmcbdfree;
	#define EXT_sysmcbdfree  extern PFSYSMCBDFREE_IEC pfsysmcbdfree;
	#define GET_sysmcbdfree(fl)  s_pfCMGetAPI2( "sysmcbdfree", (RTS_VOID_FCTPTR *)&pfsysmcbdfree, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0x2D152790, 0x4E99D982), 0x03050B00)
	#define CAL_sysmcbdfree  pfsysmcbdfree
	#define CHK_sysmcbdfree  (pfsysmcbdfree != NULL)
	#define EXP_sysmcbdfree   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdfree", (RTS_UINTPTR)sysmcbdfree, 1, RTSITF_GET_SIGNATURE(0x2D152790, 0x4E99D982), 0x03050B00) 
#endif


/**
 * <description>sysmcbdgetfirstid</description>
 */
typedef struct tagsysmcbdgetfirstid_struct
{
	CpuCoreBindingDesc *pBindingDesc;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_UDINT SysMCBDGetFirstID;	/* VAR_OUTPUT */	
} sysmcbdgetfirstid_struct;

void CDECL CDECL_EXT sysmcbdgetfirstid(sysmcbdgetfirstid_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSMCBDGETFIRSTID_IEC) (sysmcbdgetfirstid_struct *p);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBDGETFIRSTID_NOTIMPLEMENTED)
	#define USE_sysmcbdgetfirstid
	#define EXT_sysmcbdgetfirstid
	#define GET_sysmcbdgetfirstid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysmcbdgetfirstid(p0) 
	#define CHK_sysmcbdgetfirstid  FALSE
	#define EXP_sysmcbdgetfirstid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysmcbdgetfirstid
	#define EXT_sysmcbdgetfirstid
	#define GET_sysmcbdgetfirstid(fl)  CAL_CMGETAPI( "sysmcbdgetfirstid" ) 
	#define CAL_sysmcbdgetfirstid  sysmcbdgetfirstid
	#define CHK_sysmcbdgetfirstid  TRUE
	#define EXP_sysmcbdgetfirstid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdgetfirstid", (RTS_UINTPTR)sysmcbdgetfirstid, 1, RTSITF_GET_SIGNATURE(0x0413C991, 0xF3084CC6), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_sysmcbdgetfirstid
	#define EXT_sysmcbdgetfirstid
	#define GET_sysmcbdgetfirstid(fl)  CAL_CMGETAPI( "sysmcbdgetfirstid" ) 
	#define CAL_sysmcbdgetfirstid  sysmcbdgetfirstid
	#define CHK_sysmcbdgetfirstid  TRUE
	#define EXP_sysmcbdgetfirstid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdgetfirstid", (RTS_UINTPTR)sysmcbdgetfirstid, 1, RTSITF_GET_SIGNATURE(0x0413C991, 0xF3084CC6), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoresysmcbdgetfirstid
	#define EXT_SysCpuMultiCoresysmcbdgetfirstid
	#define GET_SysCpuMultiCoresysmcbdgetfirstid  ERR_OK
	#define CAL_SysCpuMultiCoresysmcbdgetfirstid  sysmcbdgetfirstid
	#define CHK_SysCpuMultiCoresysmcbdgetfirstid  TRUE
	#define EXP_SysCpuMultiCoresysmcbdgetfirstid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdgetfirstid", (RTS_UINTPTR)sysmcbdgetfirstid, 1, RTSITF_GET_SIGNATURE(0x0413C991, 0xF3084CC6), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_sysmcbdgetfirstid
	#define EXT_sysmcbdgetfirstid
	#define GET_sysmcbdgetfirstid(fl)  CAL_CMGETAPI( "sysmcbdgetfirstid" ) 
	#define CAL_sysmcbdgetfirstid  sysmcbdgetfirstid
	#define CHK_sysmcbdgetfirstid  TRUE
	#define EXP_sysmcbdgetfirstid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdgetfirstid", (RTS_UINTPTR)sysmcbdgetfirstid, 1, RTSITF_GET_SIGNATURE(0x0413C991, 0xF3084CC6), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_sysmcbdgetfirstid  PFSYSMCBDGETFIRSTID_IEC pfsysmcbdgetfirstid;
	#define EXT_sysmcbdgetfirstid  extern PFSYSMCBDGETFIRSTID_IEC pfsysmcbdgetfirstid;
	#define GET_sysmcbdgetfirstid(fl)  s_pfCMGetAPI2( "sysmcbdgetfirstid", (RTS_VOID_FCTPTR *)&pfsysmcbdgetfirstid, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0x0413C991, 0xF3084CC6), 0x03050B00)
	#define CAL_sysmcbdgetfirstid  pfsysmcbdgetfirstid
	#define CHK_sysmcbdgetfirstid  (pfsysmcbdgetfirstid != NULL)
	#define EXP_sysmcbdgetfirstid   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdgetfirstid", (RTS_UINTPTR)sysmcbdgetfirstid, 1, RTSITF_GET_SIGNATURE(0x0413C991, 0xF3084CC6), 0x03050B00) 
#endif


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

void CDECL CDECL_EXT sysmcbdgetnextid(sysmcbdgetnextid_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSMCBDGETNEXTID_IEC) (sysmcbdgetnextid_struct *p);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBDGETNEXTID_NOTIMPLEMENTED)
	#define USE_sysmcbdgetnextid
	#define EXT_sysmcbdgetnextid
	#define GET_sysmcbdgetnextid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysmcbdgetnextid(p0) 
	#define CHK_sysmcbdgetnextid  FALSE
	#define EXP_sysmcbdgetnextid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysmcbdgetnextid
	#define EXT_sysmcbdgetnextid
	#define GET_sysmcbdgetnextid(fl)  CAL_CMGETAPI( "sysmcbdgetnextid" ) 
	#define CAL_sysmcbdgetnextid  sysmcbdgetnextid
	#define CHK_sysmcbdgetnextid  TRUE
	#define EXP_sysmcbdgetnextid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdgetnextid", (RTS_UINTPTR)sysmcbdgetnextid, 1, RTSITF_GET_SIGNATURE(0xDC0570FA, 0xB42D3BDD), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_sysmcbdgetnextid
	#define EXT_sysmcbdgetnextid
	#define GET_sysmcbdgetnextid(fl)  CAL_CMGETAPI( "sysmcbdgetnextid" ) 
	#define CAL_sysmcbdgetnextid  sysmcbdgetnextid
	#define CHK_sysmcbdgetnextid  TRUE
	#define EXP_sysmcbdgetnextid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdgetnextid", (RTS_UINTPTR)sysmcbdgetnextid, 1, RTSITF_GET_SIGNATURE(0xDC0570FA, 0xB42D3BDD), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoresysmcbdgetnextid
	#define EXT_SysCpuMultiCoresysmcbdgetnextid
	#define GET_SysCpuMultiCoresysmcbdgetnextid  ERR_OK
	#define CAL_SysCpuMultiCoresysmcbdgetnextid  sysmcbdgetnextid
	#define CHK_SysCpuMultiCoresysmcbdgetnextid  TRUE
	#define EXP_SysCpuMultiCoresysmcbdgetnextid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdgetnextid", (RTS_UINTPTR)sysmcbdgetnextid, 1, RTSITF_GET_SIGNATURE(0xDC0570FA, 0xB42D3BDD), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_sysmcbdgetnextid
	#define EXT_sysmcbdgetnextid
	#define GET_sysmcbdgetnextid(fl)  CAL_CMGETAPI( "sysmcbdgetnextid" ) 
	#define CAL_sysmcbdgetnextid  sysmcbdgetnextid
	#define CHK_sysmcbdgetnextid  TRUE
	#define EXP_sysmcbdgetnextid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdgetnextid", (RTS_UINTPTR)sysmcbdgetnextid, 1, RTSITF_GET_SIGNATURE(0xDC0570FA, 0xB42D3BDD), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_sysmcbdgetnextid  PFSYSMCBDGETNEXTID_IEC pfsysmcbdgetnextid;
	#define EXT_sysmcbdgetnextid  extern PFSYSMCBDGETNEXTID_IEC pfsysmcbdgetnextid;
	#define GET_sysmcbdgetnextid(fl)  s_pfCMGetAPI2( "sysmcbdgetnextid", (RTS_VOID_FCTPTR *)&pfsysmcbdgetnextid, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0xDC0570FA, 0xB42D3BDD), 0x03050B00)
	#define CAL_sysmcbdgetnextid  pfsysmcbdgetnextid
	#define CHK_sysmcbdgetnextid  (pfsysmcbdgetnextid != NULL)
	#define EXP_sysmcbdgetnextid   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdgetnextid", (RTS_UINTPTR)sysmcbdgetnextid, 1, RTSITF_GET_SIGNATURE(0xDC0570FA, 0xB42D3BDD), 0x03050B00) 
#endif


/**
 * <description>sysmcbdisset</description>
 */
typedef struct tagsysmcbdisset_struct
{
	CpuCoreBindingDesc *pBindingDesc;	/* VAR_INPUT */	
	RTS_IEC_UDINT uCoreId;				/* VAR_INPUT */	
	RTS_IEC_RESULT SysMCBDIsSet;		/* VAR_OUTPUT */	
} sysmcbdisset_struct;

void CDECL CDECL_EXT sysmcbdisset(sysmcbdisset_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSMCBDISSET_IEC) (sysmcbdisset_struct *p);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBDISSET_NOTIMPLEMENTED)
	#define USE_sysmcbdisset
	#define EXT_sysmcbdisset
	#define GET_sysmcbdisset(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysmcbdisset(p0) 
	#define CHK_sysmcbdisset  FALSE
	#define EXP_sysmcbdisset  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysmcbdisset
	#define EXT_sysmcbdisset
	#define GET_sysmcbdisset(fl)  CAL_CMGETAPI( "sysmcbdisset" ) 
	#define CAL_sysmcbdisset  sysmcbdisset
	#define CHK_sysmcbdisset  TRUE
	#define EXP_sysmcbdisset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdisset", (RTS_UINTPTR)sysmcbdisset, 1, RTSITF_GET_SIGNATURE(0x54BC1578, 0xA3BEE463), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_sysmcbdisset
	#define EXT_sysmcbdisset
	#define GET_sysmcbdisset(fl)  CAL_CMGETAPI( "sysmcbdisset" ) 
	#define CAL_sysmcbdisset  sysmcbdisset
	#define CHK_sysmcbdisset  TRUE
	#define EXP_sysmcbdisset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdisset", (RTS_UINTPTR)sysmcbdisset, 1, RTSITF_GET_SIGNATURE(0x54BC1578, 0xA3BEE463), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoresysmcbdisset
	#define EXT_SysCpuMultiCoresysmcbdisset
	#define GET_SysCpuMultiCoresysmcbdisset  ERR_OK
	#define CAL_SysCpuMultiCoresysmcbdisset  sysmcbdisset
	#define CHK_SysCpuMultiCoresysmcbdisset  TRUE
	#define EXP_SysCpuMultiCoresysmcbdisset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdisset", (RTS_UINTPTR)sysmcbdisset, 1, RTSITF_GET_SIGNATURE(0x54BC1578, 0xA3BEE463), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_sysmcbdisset
	#define EXT_sysmcbdisset
	#define GET_sysmcbdisset(fl)  CAL_CMGETAPI( "sysmcbdisset" ) 
	#define CAL_sysmcbdisset  sysmcbdisset
	#define CHK_sysmcbdisset  TRUE
	#define EXP_sysmcbdisset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdisset", (RTS_UINTPTR)sysmcbdisset, 1, RTSITF_GET_SIGNATURE(0x54BC1578, 0xA3BEE463), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_sysmcbdisset  PFSYSMCBDISSET_IEC pfsysmcbdisset;
	#define EXT_sysmcbdisset  extern PFSYSMCBDISSET_IEC pfsysmcbdisset;
	#define GET_sysmcbdisset(fl)  s_pfCMGetAPI2( "sysmcbdisset", (RTS_VOID_FCTPTR *)&pfsysmcbdisset, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0x54BC1578, 0xA3BEE463), 0x03050B00)
	#define CAL_sysmcbdisset  pfsysmcbdisset
	#define CHK_sysmcbdisset  (pfsysmcbdisset != NULL)
	#define EXP_sysmcbdisset   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbdisset", (RTS_UINTPTR)sysmcbdisset, 1, RTSITF_GET_SIGNATURE(0x54BC1578, 0xA3BEE463), 0x03050B00) 
#endif


/**
 * <description>sysmcgetload</description>
 */
typedef struct tagsysmcgetload_struct
{
	RTS_IEC_UDINT CoreID;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pPercent;				/* VAR_INPUT */	/* CPU-Core load in percent. */
	RTS_IEC_RESULT SysMCGetLoad;		/* VAR_OUTPUT */	
} sysmcgetload_struct;

void CDECL CDECL_EXT sysmcgetload(sysmcgetload_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSMCGETLOAD_IEC) (sysmcgetload_struct *p);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETLOAD_NOTIMPLEMENTED)
	#define USE_sysmcgetload
	#define EXT_sysmcgetload
	#define GET_sysmcgetload(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysmcgetload(p0) 
	#define CHK_sysmcgetload  FALSE
	#define EXP_sysmcgetload  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysmcgetload
	#define EXT_sysmcgetload
	#define GET_sysmcgetload(fl)  CAL_CMGETAPI( "sysmcgetload" ) 
	#define CAL_sysmcgetload  sysmcgetload
	#define CHK_sysmcgetload  TRUE
	#define EXP_sysmcgetload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetload", (RTS_UINTPTR)sysmcgetload, 1, 0xEF6D21E5, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_sysmcgetload
	#define EXT_sysmcgetload
	#define GET_sysmcgetload(fl)  CAL_CMGETAPI( "sysmcgetload" ) 
	#define CAL_sysmcgetload  sysmcgetload
	#define CHK_sysmcgetload  TRUE
	#define EXP_sysmcgetload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetload", (RTS_UINTPTR)sysmcgetload, 1, 0xEF6D21E5, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoresysmcgetload
	#define EXT_SysCpuMultiCoresysmcgetload
	#define GET_SysCpuMultiCoresysmcgetload  ERR_OK
	#define CAL_SysCpuMultiCoresysmcgetload  sysmcgetload
	#define CHK_SysCpuMultiCoresysmcgetload  TRUE
	#define EXP_SysCpuMultiCoresysmcgetload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetload", (RTS_UINTPTR)sysmcgetload, 1, 0xEF6D21E5, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_sysmcgetload
	#define EXT_sysmcgetload
	#define GET_sysmcgetload(fl)  CAL_CMGETAPI( "sysmcgetload" ) 
	#define CAL_sysmcgetload  sysmcgetload
	#define CHK_sysmcgetload  TRUE
	#define EXP_sysmcgetload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetload", (RTS_UINTPTR)sysmcgetload, 1, 0xEF6D21E5, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_sysmcgetload  PFSYSMCGETLOAD_IEC pfsysmcgetload;
	#define EXT_sysmcgetload  extern PFSYSMCGETLOAD_IEC pfsysmcgetload;
	#define GET_sysmcgetload(fl)  s_pfCMGetAPI2( "sysmcgetload", (RTS_VOID_FCTPTR *)&pfsysmcgetload, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xEF6D21E5, 0x03050B00)
	#define CAL_sysmcgetload  pfsysmcgetload
	#define CHK_sysmcgetload  (pfsysmcgetload != NULL)
	#define EXP_sysmcgetload   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetload", (RTS_UINTPTR)sysmcgetload, 1, 0xEF6D21E5, 0x03050B00) 
#endif


/**
 *Returns the number of available cores.
 *Available means: Available to be used by runtime system.
 */
typedef struct tagsysmcgetnumofcores_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to retrieve optional error code. */
	RTS_IEC_DWORD SysMCGetNumOfCores;	/* VAR_OUTPUT */	
} sysmcgetnumofcores_struct;

void CDECL CDECL_EXT sysmcgetnumofcores(sysmcgetnumofcores_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSMCGETNUMOFCORES_IEC) (sysmcgetnumofcores_struct *p);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETNUMOFCORES_NOTIMPLEMENTED)
	#define USE_sysmcgetnumofcores
	#define EXT_sysmcgetnumofcores
	#define GET_sysmcgetnumofcores(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysmcgetnumofcores(p0) 
	#define CHK_sysmcgetnumofcores  FALSE
	#define EXP_sysmcgetnumofcores  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysmcgetnumofcores
	#define EXT_sysmcgetnumofcores
	#define GET_sysmcgetnumofcores(fl)  CAL_CMGETAPI( "sysmcgetnumofcores" ) 
	#define CAL_sysmcgetnumofcores  sysmcgetnumofcores
	#define CHK_sysmcgetnumofcores  TRUE
	#define EXP_sysmcgetnumofcores  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetnumofcores", (RTS_UINTPTR)sysmcgetnumofcores, 1, 0x9360E181, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_sysmcgetnumofcores
	#define EXT_sysmcgetnumofcores
	#define GET_sysmcgetnumofcores(fl)  CAL_CMGETAPI( "sysmcgetnumofcores" ) 
	#define CAL_sysmcgetnumofcores  sysmcgetnumofcores
	#define CHK_sysmcgetnumofcores  TRUE
	#define EXP_sysmcgetnumofcores  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetnumofcores", (RTS_UINTPTR)sysmcgetnumofcores, 1, 0x9360E181, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoresysmcgetnumofcores
	#define EXT_SysCpuMultiCoresysmcgetnumofcores
	#define GET_SysCpuMultiCoresysmcgetnumofcores  ERR_OK
	#define CAL_SysCpuMultiCoresysmcgetnumofcores  sysmcgetnumofcores
	#define CHK_SysCpuMultiCoresysmcgetnumofcores  TRUE
	#define EXP_SysCpuMultiCoresysmcgetnumofcores  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetnumofcores", (RTS_UINTPTR)sysmcgetnumofcores, 1, 0x9360E181, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_sysmcgetnumofcores
	#define EXT_sysmcgetnumofcores
	#define GET_sysmcgetnumofcores(fl)  CAL_CMGETAPI( "sysmcgetnumofcores" ) 
	#define CAL_sysmcgetnumofcores  sysmcgetnumofcores
	#define CHK_sysmcgetnumofcores  TRUE
	#define EXP_sysmcgetnumofcores  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetnumofcores", (RTS_UINTPTR)sysmcgetnumofcores, 1, 0x9360E181, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_sysmcgetnumofcores  PFSYSMCGETNUMOFCORES_IEC pfsysmcgetnumofcores;
	#define EXT_sysmcgetnumofcores  extern PFSYSMCGETNUMOFCORES_IEC pfsysmcgetnumofcores;
	#define GET_sysmcgetnumofcores(fl)  s_pfCMGetAPI2( "sysmcgetnumofcores", (RTS_VOID_FCTPTR *)&pfsysmcgetnumofcores, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x9360E181, 0x03050B00)
	#define CAL_sysmcgetnumofcores  pfsysmcgetnumofcores
	#define CHK_sysmcgetnumofcores  (pfsysmcgetnumofcores != NULL)
	#define EXP_sysmcgetnumofcores   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetnumofcores", (RTS_UINTPTR)sysmcgetnumofcores, 1, 0x9360E181, 0x03050B00) 
#endif


/**
 *Read the binding description of a process.
 */
typedef struct tagsysmcgetprocessbinding_struct
{
	RTS_IEC_HANDLE hProcess;			/* VAR_INPUT */	
	CpuCoreBindingDesc *pBindingDesc;	/* VAR_INPUT */	
	RTS_IEC_RESULT SysMCGetProcessBinding;	/* VAR_OUTPUT */	
} sysmcgetprocessbinding_struct;

void CDECL CDECL_EXT sysmcgetprocessbinding(sysmcgetprocessbinding_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSMCGETPROCESSBINDING_IEC) (sysmcgetprocessbinding_struct *p);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETPROCESSBINDING_NOTIMPLEMENTED)
	#define USE_sysmcgetprocessbinding
	#define EXT_sysmcgetprocessbinding
	#define GET_sysmcgetprocessbinding(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysmcgetprocessbinding(p0) 
	#define CHK_sysmcgetprocessbinding  FALSE
	#define EXP_sysmcgetprocessbinding  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysmcgetprocessbinding
	#define EXT_sysmcgetprocessbinding
	#define GET_sysmcgetprocessbinding(fl)  CAL_CMGETAPI( "sysmcgetprocessbinding" ) 
	#define CAL_sysmcgetprocessbinding  sysmcgetprocessbinding
	#define CHK_sysmcgetprocessbinding  TRUE
	#define EXP_sysmcgetprocessbinding  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetprocessbinding", (RTS_UINTPTR)sysmcgetprocessbinding, 1, RTSITF_GET_SIGNATURE(0x630248E0, 0x2F2E120C), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_sysmcgetprocessbinding
	#define EXT_sysmcgetprocessbinding
	#define GET_sysmcgetprocessbinding(fl)  CAL_CMGETAPI( "sysmcgetprocessbinding" ) 
	#define CAL_sysmcgetprocessbinding  sysmcgetprocessbinding
	#define CHK_sysmcgetprocessbinding  TRUE
	#define EXP_sysmcgetprocessbinding  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetprocessbinding", (RTS_UINTPTR)sysmcgetprocessbinding, 1, RTSITF_GET_SIGNATURE(0x630248E0, 0x2F2E120C), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoresysmcgetprocessbinding
	#define EXT_SysCpuMultiCoresysmcgetprocessbinding
	#define GET_SysCpuMultiCoresysmcgetprocessbinding  ERR_OK
	#define CAL_SysCpuMultiCoresysmcgetprocessbinding  sysmcgetprocessbinding
	#define CHK_SysCpuMultiCoresysmcgetprocessbinding  TRUE
	#define EXP_SysCpuMultiCoresysmcgetprocessbinding  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetprocessbinding", (RTS_UINTPTR)sysmcgetprocessbinding, 1, RTSITF_GET_SIGNATURE(0x630248E0, 0x2F2E120C), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_sysmcgetprocessbinding
	#define EXT_sysmcgetprocessbinding
	#define GET_sysmcgetprocessbinding(fl)  CAL_CMGETAPI( "sysmcgetprocessbinding" ) 
	#define CAL_sysmcgetprocessbinding  sysmcgetprocessbinding
	#define CHK_sysmcgetprocessbinding  TRUE
	#define EXP_sysmcgetprocessbinding  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetprocessbinding", (RTS_UINTPTR)sysmcgetprocessbinding, 1, RTSITF_GET_SIGNATURE(0x630248E0, 0x2F2E120C), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_sysmcgetprocessbinding  PFSYSMCGETPROCESSBINDING_IEC pfsysmcgetprocessbinding;
	#define EXT_sysmcgetprocessbinding  extern PFSYSMCGETPROCESSBINDING_IEC pfsysmcgetprocessbinding;
	#define GET_sysmcgetprocessbinding(fl)  s_pfCMGetAPI2( "sysmcgetprocessbinding", (RTS_VOID_FCTPTR *)&pfsysmcgetprocessbinding, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0x630248E0, 0x2F2E120C), 0x03050B00)
	#define CAL_sysmcgetprocessbinding  pfsysmcgetprocessbinding
	#define CHK_sysmcgetprocessbinding  (pfsysmcgetprocessbinding != NULL)
	#define EXP_sysmcgetprocessbinding   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetprocessbinding", (RTS_UINTPTR)sysmcgetprocessbinding, 1, RTSITF_GET_SIGNATURE(0x630248E0, 0x2F2E120C), 0x03050B00) 
#endif


/**
 *Read the binding description of a task.
 */
typedef struct tagsysmcgettaskbinding_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	
	CpuCoreBindingDesc *pBindingDesc;	/* VAR_INPUT */	
	RTS_IEC_RESULT SysMCGetTaskBinding;	/* VAR_OUTPUT */	
} sysmcgettaskbinding_struct;

void CDECL CDECL_EXT sysmcgettaskbinding(sysmcgettaskbinding_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSMCGETTASKBINDING_IEC) (sysmcgettaskbinding_struct *p);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETTASKBINDING_NOTIMPLEMENTED)
	#define USE_sysmcgettaskbinding
	#define EXT_sysmcgettaskbinding
	#define GET_sysmcgettaskbinding(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysmcgettaskbinding(p0) 
	#define CHK_sysmcgettaskbinding  FALSE
	#define EXP_sysmcgettaskbinding  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysmcgettaskbinding
	#define EXT_sysmcgettaskbinding
	#define GET_sysmcgettaskbinding(fl)  CAL_CMGETAPI( "sysmcgettaskbinding" ) 
	#define CAL_sysmcgettaskbinding  sysmcgettaskbinding
	#define CHK_sysmcgettaskbinding  TRUE
	#define EXP_sysmcgettaskbinding  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgettaskbinding", (RTS_UINTPTR)sysmcgettaskbinding, 1, RTSITF_GET_SIGNATURE(0x4571B9EE, 0x2D12BDE0), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_sysmcgettaskbinding
	#define EXT_sysmcgettaskbinding
	#define GET_sysmcgettaskbinding(fl)  CAL_CMGETAPI( "sysmcgettaskbinding" ) 
	#define CAL_sysmcgettaskbinding  sysmcgettaskbinding
	#define CHK_sysmcgettaskbinding  TRUE
	#define EXP_sysmcgettaskbinding  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgettaskbinding", (RTS_UINTPTR)sysmcgettaskbinding, 1, RTSITF_GET_SIGNATURE(0x4571B9EE, 0x2D12BDE0), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoresysmcgettaskbinding
	#define EXT_SysCpuMultiCoresysmcgettaskbinding
	#define GET_SysCpuMultiCoresysmcgettaskbinding  ERR_OK
	#define CAL_SysCpuMultiCoresysmcgettaskbinding  sysmcgettaskbinding
	#define CHK_SysCpuMultiCoresysmcgettaskbinding  TRUE
	#define EXP_SysCpuMultiCoresysmcgettaskbinding  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgettaskbinding", (RTS_UINTPTR)sysmcgettaskbinding, 1, RTSITF_GET_SIGNATURE(0x4571B9EE, 0x2D12BDE0), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_sysmcgettaskbinding
	#define EXT_sysmcgettaskbinding
	#define GET_sysmcgettaskbinding(fl)  CAL_CMGETAPI( "sysmcgettaskbinding" ) 
	#define CAL_sysmcgettaskbinding  sysmcgettaskbinding
	#define CHK_sysmcgettaskbinding  TRUE
	#define EXP_sysmcgettaskbinding  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgettaskbinding", (RTS_UINTPTR)sysmcgettaskbinding, 1, RTSITF_GET_SIGNATURE(0x4571B9EE, 0x2D12BDE0), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_sysmcgettaskbinding  PFSYSMCGETTASKBINDING_IEC pfsysmcgettaskbinding;
	#define EXT_sysmcgettaskbinding  extern PFSYSMCGETTASKBINDING_IEC pfsysmcgettaskbinding;
	#define GET_sysmcgettaskbinding(fl)  s_pfCMGetAPI2( "sysmcgettaskbinding", (RTS_VOID_FCTPTR *)&pfsysmcgettaskbinding, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0x4571B9EE, 0x2D12BDE0), 0x03050B00)
	#define CAL_sysmcgettaskbinding  pfsysmcgettaskbinding
	#define CHK_sysmcgettaskbinding  (pfsysmcgettaskbinding != NULL)
	#define EXP_sysmcgettaskbinding   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgettaskbinding", (RTS_UINTPTR)sysmcgettaskbinding, 1, RTSITF_GET_SIGNATURE(0x4571B9EE, 0x2D12BDE0), 0x03050B00) 
#endif


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
RTS_HANDLE CDECL SysMCAddTaskGroup(char *pszTaskGroup, RTS_UI32 taskGroupOptions, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSMCADDTASKGROUP) (char *pszTaskGroup, RTS_UI32 taskGroupOptions, RTS_RESULT *pResult);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCADDTASKGROUP_NOTIMPLEMENTED)
	#define USE_SysMCAddTaskGroup
	#define EXT_SysMCAddTaskGroup
	#define GET_SysMCAddTaskGroup(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCAddTaskGroup(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysMCAddTaskGroup  FALSE
	#define EXP_SysMCAddTaskGroup  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCAddTaskGroup
	#define EXT_SysMCAddTaskGroup
	#define GET_SysMCAddTaskGroup(fl)  CAL_CMGETAPI( "SysMCAddTaskGroup" ) 
	#define CAL_SysMCAddTaskGroup  SysMCAddTaskGroup
	#define CHK_SysMCAddTaskGroup  TRUE
	#define EXP_SysMCAddTaskGroup  CAL_CMEXPAPI( "SysMCAddTaskGroup" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCAddTaskGroup
	#define EXT_SysMCAddTaskGroup
	#define GET_SysMCAddTaskGroup(fl)  CAL_CMGETAPI( "SysMCAddTaskGroup" ) 
	#define CAL_SysMCAddTaskGroup  SysMCAddTaskGroup
	#define CHK_SysMCAddTaskGroup  TRUE
	#define EXP_SysMCAddTaskGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCAddTaskGroup", (RTS_UINTPTR)SysMCAddTaskGroup, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCAddTaskGroup
	#define EXT_SysCpuMultiCoreSysMCAddTaskGroup
	#define GET_SysCpuMultiCoreSysMCAddTaskGroup  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCAddTaskGroup pISysCpuMultiCore->ISysMCAddTaskGroup
	#define CHK_SysCpuMultiCoreSysMCAddTaskGroup (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCAddTaskGroup  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCAddTaskGroup
	#define EXT_SysMCAddTaskGroup
	#define GET_SysMCAddTaskGroup(fl)  CAL_CMGETAPI( "SysMCAddTaskGroup" ) 
	#define CAL_SysMCAddTaskGroup pISysCpuMultiCore->ISysMCAddTaskGroup
	#define CHK_SysMCAddTaskGroup (pISysCpuMultiCore != NULL)
	#define EXP_SysMCAddTaskGroup  CAL_CMEXPAPI( "SysMCAddTaskGroup" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCAddTaskGroup  PFSYSMCADDTASKGROUP pfSysMCAddTaskGroup;
	#define EXT_SysMCAddTaskGroup  extern PFSYSMCADDTASKGROUP pfSysMCAddTaskGroup;
	#define GET_SysMCAddTaskGroup(fl)  s_pfCMGetAPI2( "SysMCAddTaskGroup", (RTS_VOID_FCTPTR *)&pfSysMCAddTaskGroup, (fl), 0, 0)
	#define CAL_SysMCAddTaskGroup  pfSysMCAddTaskGroup
	#define CHK_SysMCAddTaskGroup  (pfSysMCAddTaskGroup != NULL)
	#define EXP_SysMCAddTaskGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCAddTaskGroup", (RTS_UINTPTR)SysMCAddTaskGroup, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCRemoveTaskGroup(RTS_HANDLE hTaskGroup);
typedef RTS_RESULT (CDECL * PFSYSMCREMOVETASKGROUP) (RTS_HANDLE hTaskGroup);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCREMOVETASKGROUP_NOTIMPLEMENTED)
	#define USE_SysMCRemoveTaskGroup
	#define EXT_SysMCRemoveTaskGroup
	#define GET_SysMCRemoveTaskGroup(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCRemoveTaskGroup(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCRemoveTaskGroup  FALSE
	#define EXP_SysMCRemoveTaskGroup  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCRemoveTaskGroup
	#define EXT_SysMCRemoveTaskGroup
	#define GET_SysMCRemoveTaskGroup(fl)  CAL_CMGETAPI( "SysMCRemoveTaskGroup" ) 
	#define CAL_SysMCRemoveTaskGroup  SysMCRemoveTaskGroup
	#define CHK_SysMCRemoveTaskGroup  TRUE
	#define EXP_SysMCRemoveTaskGroup  CAL_CMEXPAPI( "SysMCRemoveTaskGroup" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCRemoveTaskGroup
	#define EXT_SysMCRemoveTaskGroup
	#define GET_SysMCRemoveTaskGroup(fl)  CAL_CMGETAPI( "SysMCRemoveTaskGroup" ) 
	#define CAL_SysMCRemoveTaskGroup  SysMCRemoveTaskGroup
	#define CHK_SysMCRemoveTaskGroup  TRUE
	#define EXP_SysMCRemoveTaskGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCRemoveTaskGroup", (RTS_UINTPTR)SysMCRemoveTaskGroup, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCRemoveTaskGroup
	#define EXT_SysCpuMultiCoreSysMCRemoveTaskGroup
	#define GET_SysCpuMultiCoreSysMCRemoveTaskGroup  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCRemoveTaskGroup pISysCpuMultiCore->ISysMCRemoveTaskGroup
	#define CHK_SysCpuMultiCoreSysMCRemoveTaskGroup (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCRemoveTaskGroup  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCRemoveTaskGroup
	#define EXT_SysMCRemoveTaskGroup
	#define GET_SysMCRemoveTaskGroup(fl)  CAL_CMGETAPI( "SysMCRemoveTaskGroup" ) 
	#define CAL_SysMCRemoveTaskGroup pISysCpuMultiCore->ISysMCRemoveTaskGroup
	#define CHK_SysMCRemoveTaskGroup (pISysCpuMultiCore != NULL)
	#define EXP_SysMCRemoveTaskGroup  CAL_CMEXPAPI( "SysMCRemoveTaskGroup" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCRemoveTaskGroup  PFSYSMCREMOVETASKGROUP pfSysMCRemoveTaskGroup;
	#define EXT_SysMCRemoveTaskGroup  extern PFSYSMCREMOVETASKGROUP pfSysMCRemoveTaskGroup;
	#define GET_SysMCRemoveTaskGroup(fl)  s_pfCMGetAPI2( "SysMCRemoveTaskGroup", (RTS_VOID_FCTPTR *)&pfSysMCRemoveTaskGroup, (fl), 0, 0)
	#define CAL_SysMCRemoveTaskGroup  pfSysMCRemoveTaskGroup
	#define CHK_SysMCRemoveTaskGroup  (pfSysMCRemoveTaskGroup != NULL)
	#define EXP_SysMCRemoveTaskGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCRemoveTaskGroup", (RTS_UINTPTR)SysMCRemoveTaskGroup, 0, 0) 
#endif




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
RTS_HANDLE CDECL SysMCFindTaskGroup(char *pszTaskGroup, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSMCFINDTASKGROUP) (char *pszTaskGroup, RTS_RESULT *pResult);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCFINDTASKGROUP_NOTIMPLEMENTED)
	#define USE_SysMCFindTaskGroup
	#define EXT_SysMCFindTaskGroup
	#define GET_SysMCFindTaskGroup(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCFindTaskGroup(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysMCFindTaskGroup  FALSE
	#define EXP_SysMCFindTaskGroup  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCFindTaskGroup
	#define EXT_SysMCFindTaskGroup
	#define GET_SysMCFindTaskGroup(fl)  CAL_CMGETAPI( "SysMCFindTaskGroup" ) 
	#define CAL_SysMCFindTaskGroup  SysMCFindTaskGroup
	#define CHK_SysMCFindTaskGroup  TRUE
	#define EXP_SysMCFindTaskGroup  CAL_CMEXPAPI( "SysMCFindTaskGroup" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCFindTaskGroup
	#define EXT_SysMCFindTaskGroup
	#define GET_SysMCFindTaskGroup(fl)  CAL_CMGETAPI( "SysMCFindTaskGroup" ) 
	#define CAL_SysMCFindTaskGroup  SysMCFindTaskGroup
	#define CHK_SysMCFindTaskGroup  TRUE
	#define EXP_SysMCFindTaskGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCFindTaskGroup", (RTS_UINTPTR)SysMCFindTaskGroup, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCFindTaskGroup
	#define EXT_SysCpuMultiCoreSysMCFindTaskGroup
	#define GET_SysCpuMultiCoreSysMCFindTaskGroup  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCFindTaskGroup pISysCpuMultiCore->ISysMCFindTaskGroup
	#define CHK_SysCpuMultiCoreSysMCFindTaskGroup (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCFindTaskGroup  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCFindTaskGroup
	#define EXT_SysMCFindTaskGroup
	#define GET_SysMCFindTaskGroup(fl)  CAL_CMGETAPI( "SysMCFindTaskGroup" ) 
	#define CAL_SysMCFindTaskGroup pISysCpuMultiCore->ISysMCFindTaskGroup
	#define CHK_SysMCFindTaskGroup (pISysCpuMultiCore != NULL)
	#define EXP_SysMCFindTaskGroup  CAL_CMEXPAPI( "SysMCFindTaskGroup" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCFindTaskGroup  PFSYSMCFINDTASKGROUP pfSysMCFindTaskGroup;
	#define EXT_SysMCFindTaskGroup  extern PFSYSMCFINDTASKGROUP pfSysMCFindTaskGroup;
	#define GET_SysMCFindTaskGroup(fl)  s_pfCMGetAPI2( "SysMCFindTaskGroup", (RTS_VOID_FCTPTR *)&pfSysMCFindTaskGroup, (fl), 0, 0)
	#define CAL_SysMCFindTaskGroup  pfSysMCFindTaskGroup
	#define CHK_SysMCFindTaskGroup  (pfSysMCFindTaskGroup != NULL)
	#define EXP_SysMCFindTaskGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCFindTaskGroup", (RTS_UINTPTR)SysMCFindTaskGroup, 0, 0) 
#endif




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
RTS_HANDLE CDECL SysMCGetFirstTaskGroup(RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSMCGETFIRSTTASKGROUP) (RTS_RESULT *pResult);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETFIRSTTASKGROUP_NOTIMPLEMENTED)
	#define USE_SysMCGetFirstTaskGroup
	#define EXT_SysMCGetFirstTaskGroup
	#define GET_SysMCGetFirstTaskGroup(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCGetFirstTaskGroup(p0)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysMCGetFirstTaskGroup  FALSE
	#define EXP_SysMCGetFirstTaskGroup  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCGetFirstTaskGroup
	#define EXT_SysMCGetFirstTaskGroup
	#define GET_SysMCGetFirstTaskGroup(fl)  CAL_CMGETAPI( "SysMCGetFirstTaskGroup" ) 
	#define CAL_SysMCGetFirstTaskGroup  SysMCGetFirstTaskGroup
	#define CHK_SysMCGetFirstTaskGroup  TRUE
	#define EXP_SysMCGetFirstTaskGroup  CAL_CMEXPAPI( "SysMCGetFirstTaskGroup" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCGetFirstTaskGroup
	#define EXT_SysMCGetFirstTaskGroup
	#define GET_SysMCGetFirstTaskGroup(fl)  CAL_CMGETAPI( "SysMCGetFirstTaskGroup" ) 
	#define CAL_SysMCGetFirstTaskGroup  SysMCGetFirstTaskGroup
	#define CHK_SysMCGetFirstTaskGroup  TRUE
	#define EXP_SysMCGetFirstTaskGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetFirstTaskGroup", (RTS_UINTPTR)SysMCGetFirstTaskGroup, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCGetFirstTaskGroup
	#define EXT_SysCpuMultiCoreSysMCGetFirstTaskGroup
	#define GET_SysCpuMultiCoreSysMCGetFirstTaskGroup  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCGetFirstTaskGroup pISysCpuMultiCore->ISysMCGetFirstTaskGroup
	#define CHK_SysCpuMultiCoreSysMCGetFirstTaskGroup (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCGetFirstTaskGroup  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCGetFirstTaskGroup
	#define EXT_SysMCGetFirstTaskGroup
	#define GET_SysMCGetFirstTaskGroup(fl)  CAL_CMGETAPI( "SysMCGetFirstTaskGroup" ) 
	#define CAL_SysMCGetFirstTaskGroup pISysCpuMultiCore->ISysMCGetFirstTaskGroup
	#define CHK_SysMCGetFirstTaskGroup (pISysCpuMultiCore != NULL)
	#define EXP_SysMCGetFirstTaskGroup  CAL_CMEXPAPI( "SysMCGetFirstTaskGroup" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCGetFirstTaskGroup  PFSYSMCGETFIRSTTASKGROUP pfSysMCGetFirstTaskGroup;
	#define EXT_SysMCGetFirstTaskGroup  extern PFSYSMCGETFIRSTTASKGROUP pfSysMCGetFirstTaskGroup;
	#define GET_SysMCGetFirstTaskGroup(fl)  s_pfCMGetAPI2( "SysMCGetFirstTaskGroup", (RTS_VOID_FCTPTR *)&pfSysMCGetFirstTaskGroup, (fl), 0, 0)
	#define CAL_SysMCGetFirstTaskGroup  pfSysMCGetFirstTaskGroup
	#define CHK_SysMCGetFirstTaskGroup  (pfSysMCGetFirstTaskGroup != NULL)
	#define EXP_SysMCGetFirstTaskGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetFirstTaskGroup", (RTS_UINTPTR)SysMCGetFirstTaskGroup, 0, 0) 
#endif




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
RTS_HANDLE CDECL SysMCGetNextTaskGroup(RTS_HANDLE hPrevTaskGroup, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSMCGETNEXTTASKGROUP) (RTS_HANDLE hPrevTaskGroup, RTS_RESULT *pResult);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETNEXTTASKGROUP_NOTIMPLEMENTED)
	#define USE_SysMCGetNextTaskGroup
	#define EXT_SysMCGetNextTaskGroup
	#define GET_SysMCGetNextTaskGroup(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCGetNextTaskGroup(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysMCGetNextTaskGroup  FALSE
	#define EXP_SysMCGetNextTaskGroup  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCGetNextTaskGroup
	#define EXT_SysMCGetNextTaskGroup
	#define GET_SysMCGetNextTaskGroup(fl)  CAL_CMGETAPI( "SysMCGetNextTaskGroup" ) 
	#define CAL_SysMCGetNextTaskGroup  SysMCGetNextTaskGroup
	#define CHK_SysMCGetNextTaskGroup  TRUE
	#define EXP_SysMCGetNextTaskGroup  CAL_CMEXPAPI( "SysMCGetNextTaskGroup" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCGetNextTaskGroup
	#define EXT_SysMCGetNextTaskGroup
	#define GET_SysMCGetNextTaskGroup(fl)  CAL_CMGETAPI( "SysMCGetNextTaskGroup" ) 
	#define CAL_SysMCGetNextTaskGroup  SysMCGetNextTaskGroup
	#define CHK_SysMCGetNextTaskGroup  TRUE
	#define EXP_SysMCGetNextTaskGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetNextTaskGroup", (RTS_UINTPTR)SysMCGetNextTaskGroup, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCGetNextTaskGroup
	#define EXT_SysCpuMultiCoreSysMCGetNextTaskGroup
	#define GET_SysCpuMultiCoreSysMCGetNextTaskGroup  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCGetNextTaskGroup pISysCpuMultiCore->ISysMCGetNextTaskGroup
	#define CHK_SysCpuMultiCoreSysMCGetNextTaskGroup (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCGetNextTaskGroup  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCGetNextTaskGroup
	#define EXT_SysMCGetNextTaskGroup
	#define GET_SysMCGetNextTaskGroup(fl)  CAL_CMGETAPI( "SysMCGetNextTaskGroup" ) 
	#define CAL_SysMCGetNextTaskGroup pISysCpuMultiCore->ISysMCGetNextTaskGroup
	#define CHK_SysMCGetNextTaskGroup (pISysCpuMultiCore != NULL)
	#define EXP_SysMCGetNextTaskGroup  CAL_CMEXPAPI( "SysMCGetNextTaskGroup" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCGetNextTaskGroup  PFSYSMCGETNEXTTASKGROUP pfSysMCGetNextTaskGroup;
	#define EXT_SysMCGetNextTaskGroup  extern PFSYSMCGETNEXTTASKGROUP pfSysMCGetNextTaskGroup;
	#define GET_SysMCGetNextTaskGroup(fl)  s_pfCMGetAPI2( "SysMCGetNextTaskGroup", (RTS_VOID_FCTPTR *)&pfSysMCGetNextTaskGroup, (fl), 0, 0)
	#define CAL_SysMCGetNextTaskGroup  pfSysMCGetNextTaskGroup
	#define CHK_SysMCGetNextTaskGroup  (pfSysMCGetNextTaskGroup != NULL)
	#define EXP_SysMCGetNextTaskGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetNextTaskGroup", (RTS_UINTPTR)SysMCGetNextTaskGroup, 0, 0) 
#endif




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
char* CDECL SysMCGetTaskGroupName(RTS_HANDLE hTaskGroup, RTS_RESULT *pResult);
typedef char* (CDECL * PFSYSMCGETTASKGROUPNAME) (RTS_HANDLE hTaskGroup, RTS_RESULT *pResult);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETTASKGROUPNAME_NOTIMPLEMENTED)
	#define USE_SysMCGetTaskGroupName
	#define EXT_SysMCGetTaskGroupName
	#define GET_SysMCGetTaskGroupName(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCGetTaskGroupName(p0,p1)  (char*)ERR_NOTIMPLEMENTED
	#define CHK_SysMCGetTaskGroupName  FALSE
	#define EXP_SysMCGetTaskGroupName  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCGetTaskGroupName
	#define EXT_SysMCGetTaskGroupName
	#define GET_SysMCGetTaskGroupName(fl)  CAL_CMGETAPI( "SysMCGetTaskGroupName" ) 
	#define CAL_SysMCGetTaskGroupName  SysMCGetTaskGroupName
	#define CHK_SysMCGetTaskGroupName  TRUE
	#define EXP_SysMCGetTaskGroupName  CAL_CMEXPAPI( "SysMCGetTaskGroupName" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCGetTaskGroupName
	#define EXT_SysMCGetTaskGroupName
	#define GET_SysMCGetTaskGroupName(fl)  CAL_CMGETAPI( "SysMCGetTaskGroupName" ) 
	#define CAL_SysMCGetTaskGroupName  SysMCGetTaskGroupName
	#define CHK_SysMCGetTaskGroupName  TRUE
	#define EXP_SysMCGetTaskGroupName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetTaskGroupName", (RTS_UINTPTR)SysMCGetTaskGroupName, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCGetTaskGroupName
	#define EXT_SysCpuMultiCoreSysMCGetTaskGroupName
	#define GET_SysCpuMultiCoreSysMCGetTaskGroupName  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCGetTaskGroupName pISysCpuMultiCore->ISysMCGetTaskGroupName
	#define CHK_SysCpuMultiCoreSysMCGetTaskGroupName (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCGetTaskGroupName  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCGetTaskGroupName
	#define EXT_SysMCGetTaskGroupName
	#define GET_SysMCGetTaskGroupName(fl)  CAL_CMGETAPI( "SysMCGetTaskGroupName" ) 
	#define CAL_SysMCGetTaskGroupName pISysCpuMultiCore->ISysMCGetTaskGroupName
	#define CHK_SysMCGetTaskGroupName (pISysCpuMultiCore != NULL)
	#define EXP_SysMCGetTaskGroupName  CAL_CMEXPAPI( "SysMCGetTaskGroupName" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCGetTaskGroupName  PFSYSMCGETTASKGROUPNAME pfSysMCGetTaskGroupName;
	#define EXT_SysMCGetTaskGroupName  extern PFSYSMCGETTASKGROUPNAME pfSysMCGetTaskGroupName;
	#define GET_SysMCGetTaskGroupName(fl)  s_pfCMGetAPI2( "SysMCGetTaskGroupName", (RTS_VOID_FCTPTR *)&pfSysMCGetTaskGroupName, (fl), 0, 0)
	#define CAL_SysMCGetTaskGroupName  pfSysMCGetTaskGroupName
	#define CHK_SysMCGetTaskGroupName  (pfSysMCGetTaskGroupName != NULL)
	#define EXP_SysMCGetTaskGroupName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetTaskGroupName", (RTS_UINTPTR)SysMCGetTaskGroupName, 0, 0) 
#endif




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
CpuCoreBindingDesc* CDECL SysMCGetTaskGroupBinding(RTS_HANDLE hTaskGroup, RTS_RESULT *pResult);
typedef CpuCoreBindingDesc* (CDECL * PFSYSMCGETTASKGROUPBINDING) (RTS_HANDLE hTaskGroup, RTS_RESULT *pResult);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETTASKGROUPBINDING_NOTIMPLEMENTED)
	#define USE_SysMCGetTaskGroupBinding
	#define EXT_SysMCGetTaskGroupBinding
	#define GET_SysMCGetTaskGroupBinding(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCGetTaskGroupBinding(p0,p1)  (CpuCoreBindingDesc*)ERR_NOTIMPLEMENTED
	#define CHK_SysMCGetTaskGroupBinding  FALSE
	#define EXP_SysMCGetTaskGroupBinding  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCGetTaskGroupBinding
	#define EXT_SysMCGetTaskGroupBinding
	#define GET_SysMCGetTaskGroupBinding(fl)  CAL_CMGETAPI( "SysMCGetTaskGroupBinding" ) 
	#define CAL_SysMCGetTaskGroupBinding  SysMCGetTaskGroupBinding
	#define CHK_SysMCGetTaskGroupBinding  TRUE
	#define EXP_SysMCGetTaskGroupBinding  CAL_CMEXPAPI( "SysMCGetTaskGroupBinding" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCGetTaskGroupBinding
	#define EXT_SysMCGetTaskGroupBinding
	#define GET_SysMCGetTaskGroupBinding(fl)  CAL_CMGETAPI( "SysMCGetTaskGroupBinding" ) 
	#define CAL_SysMCGetTaskGroupBinding  SysMCGetTaskGroupBinding
	#define CHK_SysMCGetTaskGroupBinding  TRUE
	#define EXP_SysMCGetTaskGroupBinding  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetTaskGroupBinding", (RTS_UINTPTR)SysMCGetTaskGroupBinding, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCGetTaskGroupBinding
	#define EXT_SysCpuMultiCoreSysMCGetTaskGroupBinding
	#define GET_SysCpuMultiCoreSysMCGetTaskGroupBinding  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCGetTaskGroupBinding pISysCpuMultiCore->ISysMCGetTaskGroupBinding
	#define CHK_SysCpuMultiCoreSysMCGetTaskGroupBinding (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCGetTaskGroupBinding  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCGetTaskGroupBinding
	#define EXT_SysMCGetTaskGroupBinding
	#define GET_SysMCGetTaskGroupBinding(fl)  CAL_CMGETAPI( "SysMCGetTaskGroupBinding" ) 
	#define CAL_SysMCGetTaskGroupBinding pISysCpuMultiCore->ISysMCGetTaskGroupBinding
	#define CHK_SysMCGetTaskGroupBinding (pISysCpuMultiCore != NULL)
	#define EXP_SysMCGetTaskGroupBinding  CAL_CMEXPAPI( "SysMCGetTaskGroupBinding" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCGetTaskGroupBinding  PFSYSMCGETTASKGROUPBINDING pfSysMCGetTaskGroupBinding;
	#define EXT_SysMCGetTaskGroupBinding  extern PFSYSMCGETTASKGROUPBINDING pfSysMCGetTaskGroupBinding;
	#define GET_SysMCGetTaskGroupBinding(fl)  s_pfCMGetAPI2( "SysMCGetTaskGroupBinding", (RTS_VOID_FCTPTR *)&pfSysMCGetTaskGroupBinding, (fl), 0, 0)
	#define CAL_SysMCGetTaskGroupBinding  pfSysMCGetTaskGroupBinding
	#define CHK_SysMCGetTaskGroupBinding  (pfSysMCGetTaskGroupBinding != NULL)
	#define EXP_SysMCGetTaskGroupBinding  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetTaskGroupBinding", (RTS_UINTPTR)SysMCGetTaskGroupBinding, 0, 0) 
#endif




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
RTS_UI32 CDECL SysMCGetTaskGroupOptions(RTS_HANDLE hTaskGroup, RTS_RESULT *pResult);
typedef RTS_UI32 (CDECL * PFSYSMCGETTASKGROUPOPTIONS) (RTS_HANDLE hTaskGroup, RTS_RESULT *pResult);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETTASKGROUPOPTIONS_NOTIMPLEMENTED)
	#define USE_SysMCGetTaskGroupOptions
	#define EXT_SysMCGetTaskGroupOptions
	#define GET_SysMCGetTaskGroupOptions(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCGetTaskGroupOptions(p0,p1)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_SysMCGetTaskGroupOptions  FALSE
	#define EXP_SysMCGetTaskGroupOptions  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCGetTaskGroupOptions
	#define EXT_SysMCGetTaskGroupOptions
	#define GET_SysMCGetTaskGroupOptions(fl)  CAL_CMGETAPI( "SysMCGetTaskGroupOptions" ) 
	#define CAL_SysMCGetTaskGroupOptions  SysMCGetTaskGroupOptions
	#define CHK_SysMCGetTaskGroupOptions  TRUE
	#define EXP_SysMCGetTaskGroupOptions  CAL_CMEXPAPI( "SysMCGetTaskGroupOptions" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCGetTaskGroupOptions
	#define EXT_SysMCGetTaskGroupOptions
	#define GET_SysMCGetTaskGroupOptions(fl)  CAL_CMGETAPI( "SysMCGetTaskGroupOptions" ) 
	#define CAL_SysMCGetTaskGroupOptions  SysMCGetTaskGroupOptions
	#define CHK_SysMCGetTaskGroupOptions  TRUE
	#define EXP_SysMCGetTaskGroupOptions  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetTaskGroupOptions", (RTS_UINTPTR)SysMCGetTaskGroupOptions, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCGetTaskGroupOptions
	#define EXT_SysCpuMultiCoreSysMCGetTaskGroupOptions
	#define GET_SysCpuMultiCoreSysMCGetTaskGroupOptions  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCGetTaskGroupOptions pISysCpuMultiCore->ISysMCGetTaskGroupOptions
	#define CHK_SysCpuMultiCoreSysMCGetTaskGroupOptions (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCGetTaskGroupOptions  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCGetTaskGroupOptions
	#define EXT_SysMCGetTaskGroupOptions
	#define GET_SysMCGetTaskGroupOptions(fl)  CAL_CMGETAPI( "SysMCGetTaskGroupOptions" ) 
	#define CAL_SysMCGetTaskGroupOptions pISysCpuMultiCore->ISysMCGetTaskGroupOptions
	#define CHK_SysMCGetTaskGroupOptions (pISysCpuMultiCore != NULL)
	#define EXP_SysMCGetTaskGroupOptions  CAL_CMEXPAPI( "SysMCGetTaskGroupOptions" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCGetTaskGroupOptions  PFSYSMCGETTASKGROUPOPTIONS pfSysMCGetTaskGroupOptions;
	#define EXT_SysMCGetTaskGroupOptions  extern PFSYSMCGETTASKGROUPOPTIONS pfSysMCGetTaskGroupOptions;
	#define GET_SysMCGetTaskGroupOptions(fl)  s_pfCMGetAPI2( "SysMCGetTaskGroupOptions", (RTS_VOID_FCTPTR *)&pfSysMCGetTaskGroupOptions, (fl), 0, 0)
	#define CAL_SysMCGetTaskGroupOptions  pfSysMCGetTaskGroupOptions
	#define CHK_SysMCGetTaskGroupOptions  (pfSysMCGetTaskGroupOptions != NULL)
	#define EXP_SysMCGetTaskGroupOptions  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetTaskGroupOptions", (RTS_UINTPTR)SysMCGetTaskGroupOptions, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCSetTaskGroupBinding(RTS_HANDLE hTaskGroup, CpuCoreBindingDesc *pBindingDesc);
typedef RTS_RESULT (CDECL * PFSYSMCSETTASKGROUPBINDING) (RTS_HANDLE hTaskGroup, CpuCoreBindingDesc *pBindingDesc);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCSETTASKGROUPBINDING_NOTIMPLEMENTED)
	#define USE_SysMCSetTaskGroupBinding
	#define EXT_SysMCSetTaskGroupBinding
	#define GET_SysMCSetTaskGroupBinding(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCSetTaskGroupBinding(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCSetTaskGroupBinding  FALSE
	#define EXP_SysMCSetTaskGroupBinding  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCSetTaskGroupBinding
	#define EXT_SysMCSetTaskGroupBinding
	#define GET_SysMCSetTaskGroupBinding(fl)  CAL_CMGETAPI( "SysMCSetTaskGroupBinding" ) 
	#define CAL_SysMCSetTaskGroupBinding  SysMCSetTaskGroupBinding
	#define CHK_SysMCSetTaskGroupBinding  TRUE
	#define EXP_SysMCSetTaskGroupBinding  CAL_CMEXPAPI( "SysMCSetTaskGroupBinding" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCSetTaskGroupBinding
	#define EXT_SysMCSetTaskGroupBinding
	#define GET_SysMCSetTaskGroupBinding(fl)  CAL_CMGETAPI( "SysMCSetTaskGroupBinding" ) 
	#define CAL_SysMCSetTaskGroupBinding  SysMCSetTaskGroupBinding
	#define CHK_SysMCSetTaskGroupBinding  TRUE
	#define EXP_SysMCSetTaskGroupBinding  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCSetTaskGroupBinding", (RTS_UINTPTR)SysMCSetTaskGroupBinding, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCSetTaskGroupBinding
	#define EXT_SysCpuMultiCoreSysMCSetTaskGroupBinding
	#define GET_SysCpuMultiCoreSysMCSetTaskGroupBinding  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCSetTaskGroupBinding pISysCpuMultiCore->ISysMCSetTaskGroupBinding
	#define CHK_SysCpuMultiCoreSysMCSetTaskGroupBinding (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCSetTaskGroupBinding  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCSetTaskGroupBinding
	#define EXT_SysMCSetTaskGroupBinding
	#define GET_SysMCSetTaskGroupBinding(fl)  CAL_CMGETAPI( "SysMCSetTaskGroupBinding" ) 
	#define CAL_SysMCSetTaskGroupBinding pISysCpuMultiCore->ISysMCSetTaskGroupBinding
	#define CHK_SysMCSetTaskGroupBinding (pISysCpuMultiCore != NULL)
	#define EXP_SysMCSetTaskGroupBinding  CAL_CMEXPAPI( "SysMCSetTaskGroupBinding" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCSetTaskGroupBinding  PFSYSMCSETTASKGROUPBINDING pfSysMCSetTaskGroupBinding;
	#define EXT_SysMCSetTaskGroupBinding  extern PFSYSMCSETTASKGROUPBINDING pfSysMCSetTaskGroupBinding;
	#define GET_SysMCSetTaskGroupBinding(fl)  s_pfCMGetAPI2( "SysMCSetTaskGroupBinding", (RTS_VOID_FCTPTR *)&pfSysMCSetTaskGroupBinding, (fl), 0, 0)
	#define CAL_SysMCSetTaskGroupBinding  pfSysMCSetTaskGroupBinding
	#define CHK_SysMCSetTaskGroupBinding  (pfSysMCSetTaskGroupBinding != NULL)
	#define EXP_SysMCSetTaskGroupBinding  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCSetTaskGroupBinding", (RTS_UINTPTR)SysMCSetTaskGroupBinding, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCAddToTaskGroup(RTS_HANDLE hSysTask, RTS_HANDLE hTaskGroup);
typedef RTS_RESULT (CDECL * PFSYSMCADDTOTASKGROUP) (RTS_HANDLE hSysTask, RTS_HANDLE hTaskGroup);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCADDTOTASKGROUP_NOTIMPLEMENTED)
	#define USE_SysMCAddToTaskGroup
	#define EXT_SysMCAddToTaskGroup
	#define GET_SysMCAddToTaskGroup(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCAddToTaskGroup(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCAddToTaskGroup  FALSE
	#define EXP_SysMCAddToTaskGroup  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCAddToTaskGroup
	#define EXT_SysMCAddToTaskGroup
	#define GET_SysMCAddToTaskGroup(fl)  CAL_CMGETAPI( "SysMCAddToTaskGroup" ) 
	#define CAL_SysMCAddToTaskGroup  SysMCAddToTaskGroup
	#define CHK_SysMCAddToTaskGroup  TRUE
	#define EXP_SysMCAddToTaskGroup  CAL_CMEXPAPI( "SysMCAddToTaskGroup" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCAddToTaskGroup
	#define EXT_SysMCAddToTaskGroup
	#define GET_SysMCAddToTaskGroup(fl)  CAL_CMGETAPI( "SysMCAddToTaskGroup" ) 
	#define CAL_SysMCAddToTaskGroup  SysMCAddToTaskGroup
	#define CHK_SysMCAddToTaskGroup  TRUE
	#define EXP_SysMCAddToTaskGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCAddToTaskGroup", (RTS_UINTPTR)SysMCAddToTaskGroup, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCAddToTaskGroup
	#define EXT_SysCpuMultiCoreSysMCAddToTaskGroup
	#define GET_SysCpuMultiCoreSysMCAddToTaskGroup  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCAddToTaskGroup pISysCpuMultiCore->ISysMCAddToTaskGroup
	#define CHK_SysCpuMultiCoreSysMCAddToTaskGroup (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCAddToTaskGroup  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCAddToTaskGroup
	#define EXT_SysMCAddToTaskGroup
	#define GET_SysMCAddToTaskGroup(fl)  CAL_CMGETAPI( "SysMCAddToTaskGroup" ) 
	#define CAL_SysMCAddToTaskGroup pISysCpuMultiCore->ISysMCAddToTaskGroup
	#define CHK_SysMCAddToTaskGroup (pISysCpuMultiCore != NULL)
	#define EXP_SysMCAddToTaskGroup  CAL_CMEXPAPI( "SysMCAddToTaskGroup" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCAddToTaskGroup  PFSYSMCADDTOTASKGROUP pfSysMCAddToTaskGroup;
	#define EXT_SysMCAddToTaskGroup  extern PFSYSMCADDTOTASKGROUP pfSysMCAddToTaskGroup;
	#define GET_SysMCAddToTaskGroup(fl)  s_pfCMGetAPI2( "SysMCAddToTaskGroup", (RTS_VOID_FCTPTR *)&pfSysMCAddToTaskGroup, (fl), 0, 0)
	#define CAL_SysMCAddToTaskGroup  pfSysMCAddToTaskGroup
	#define CHK_SysMCAddToTaskGroup  (pfSysMCAddToTaskGroup != NULL)
	#define EXP_SysMCAddToTaskGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCAddToTaskGroup", (RTS_UINTPTR)SysMCAddToTaskGroup, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCRemoveFromTaskGroup(RTS_HANDLE hSysTask, RTS_HANDLE hTaskGroup);
typedef RTS_RESULT (CDECL * PFSYSMCREMOVEFROMTASKGROUP) (RTS_HANDLE hSysTask, RTS_HANDLE hTaskGroup);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCREMOVEFROMTASKGROUP_NOTIMPLEMENTED)
	#define USE_SysMCRemoveFromTaskGroup
	#define EXT_SysMCRemoveFromTaskGroup
	#define GET_SysMCRemoveFromTaskGroup(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCRemoveFromTaskGroup(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCRemoveFromTaskGroup  FALSE
	#define EXP_SysMCRemoveFromTaskGroup  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCRemoveFromTaskGroup
	#define EXT_SysMCRemoveFromTaskGroup
	#define GET_SysMCRemoveFromTaskGroup(fl)  CAL_CMGETAPI( "SysMCRemoveFromTaskGroup" ) 
	#define CAL_SysMCRemoveFromTaskGroup  SysMCRemoveFromTaskGroup
	#define CHK_SysMCRemoveFromTaskGroup  TRUE
	#define EXP_SysMCRemoveFromTaskGroup  CAL_CMEXPAPI( "SysMCRemoveFromTaskGroup" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCRemoveFromTaskGroup
	#define EXT_SysMCRemoveFromTaskGroup
	#define GET_SysMCRemoveFromTaskGroup(fl)  CAL_CMGETAPI( "SysMCRemoveFromTaskGroup" ) 
	#define CAL_SysMCRemoveFromTaskGroup  SysMCRemoveFromTaskGroup
	#define CHK_SysMCRemoveFromTaskGroup  TRUE
	#define EXP_SysMCRemoveFromTaskGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCRemoveFromTaskGroup", (RTS_UINTPTR)SysMCRemoveFromTaskGroup, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCRemoveFromTaskGroup
	#define EXT_SysCpuMultiCoreSysMCRemoveFromTaskGroup
	#define GET_SysCpuMultiCoreSysMCRemoveFromTaskGroup  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCRemoveFromTaskGroup pISysCpuMultiCore->ISysMCRemoveFromTaskGroup
	#define CHK_SysCpuMultiCoreSysMCRemoveFromTaskGroup (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCRemoveFromTaskGroup  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCRemoveFromTaskGroup
	#define EXT_SysMCRemoveFromTaskGroup
	#define GET_SysMCRemoveFromTaskGroup(fl)  CAL_CMGETAPI( "SysMCRemoveFromTaskGroup" ) 
	#define CAL_SysMCRemoveFromTaskGroup pISysCpuMultiCore->ISysMCRemoveFromTaskGroup
	#define CHK_SysMCRemoveFromTaskGroup (pISysCpuMultiCore != NULL)
	#define EXP_SysMCRemoveFromTaskGroup  CAL_CMEXPAPI( "SysMCRemoveFromTaskGroup" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCRemoveFromTaskGroup  PFSYSMCREMOVEFROMTASKGROUP pfSysMCRemoveFromTaskGroup;
	#define EXT_SysMCRemoveFromTaskGroup  extern PFSYSMCREMOVEFROMTASKGROUP pfSysMCRemoveFromTaskGroup;
	#define GET_SysMCRemoveFromTaskGroup(fl)  s_pfCMGetAPI2( "SysMCRemoveFromTaskGroup", (RTS_VOID_FCTPTR *)&pfSysMCRemoveFromTaskGroup, (fl), 0, 0)
	#define CAL_SysMCRemoveFromTaskGroup  pfSysMCRemoveFromTaskGroup
	#define CHK_SysMCRemoveFromTaskGroup  (pfSysMCRemoveFromTaskGroup != NULL)
	#define EXP_SysMCRemoveFromTaskGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCRemoveFromTaskGroup", (RTS_UINTPTR)SysMCRemoveFromTaskGroup, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCBeginTaskGroupConf(RTS_HANDLE hTaskGroup);
typedef RTS_RESULT (CDECL * PFSYSMCBEGINTASKGROUPCONF) (RTS_HANDLE hTaskGroup);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBEGINTASKGROUPCONF_NOTIMPLEMENTED)
	#define USE_SysMCBeginTaskGroupConf
	#define EXT_SysMCBeginTaskGroupConf
	#define GET_SysMCBeginTaskGroupConf(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCBeginTaskGroupConf(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCBeginTaskGroupConf  FALSE
	#define EXP_SysMCBeginTaskGroupConf  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCBeginTaskGroupConf
	#define EXT_SysMCBeginTaskGroupConf
	#define GET_SysMCBeginTaskGroupConf(fl)  CAL_CMGETAPI( "SysMCBeginTaskGroupConf" ) 
	#define CAL_SysMCBeginTaskGroupConf  SysMCBeginTaskGroupConf
	#define CHK_SysMCBeginTaskGroupConf  TRUE
	#define EXP_SysMCBeginTaskGroupConf  CAL_CMEXPAPI( "SysMCBeginTaskGroupConf" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCBeginTaskGroupConf
	#define EXT_SysMCBeginTaskGroupConf
	#define GET_SysMCBeginTaskGroupConf(fl)  CAL_CMGETAPI( "SysMCBeginTaskGroupConf" ) 
	#define CAL_SysMCBeginTaskGroupConf  SysMCBeginTaskGroupConf
	#define CHK_SysMCBeginTaskGroupConf  TRUE
	#define EXP_SysMCBeginTaskGroupConf  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBeginTaskGroupConf", (RTS_UINTPTR)SysMCBeginTaskGroupConf, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCBeginTaskGroupConf
	#define EXT_SysCpuMultiCoreSysMCBeginTaskGroupConf
	#define GET_SysCpuMultiCoreSysMCBeginTaskGroupConf  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCBeginTaskGroupConf pISysCpuMultiCore->ISysMCBeginTaskGroupConf
	#define CHK_SysCpuMultiCoreSysMCBeginTaskGroupConf (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCBeginTaskGroupConf  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCBeginTaskGroupConf
	#define EXT_SysMCBeginTaskGroupConf
	#define GET_SysMCBeginTaskGroupConf(fl)  CAL_CMGETAPI( "SysMCBeginTaskGroupConf" ) 
	#define CAL_SysMCBeginTaskGroupConf pISysCpuMultiCore->ISysMCBeginTaskGroupConf
	#define CHK_SysMCBeginTaskGroupConf (pISysCpuMultiCore != NULL)
	#define EXP_SysMCBeginTaskGroupConf  CAL_CMEXPAPI( "SysMCBeginTaskGroupConf" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCBeginTaskGroupConf  PFSYSMCBEGINTASKGROUPCONF pfSysMCBeginTaskGroupConf;
	#define EXT_SysMCBeginTaskGroupConf  extern PFSYSMCBEGINTASKGROUPCONF pfSysMCBeginTaskGroupConf;
	#define GET_SysMCBeginTaskGroupConf(fl)  s_pfCMGetAPI2( "SysMCBeginTaskGroupConf", (RTS_VOID_FCTPTR *)&pfSysMCBeginTaskGroupConf, (fl), 0, 0)
	#define CAL_SysMCBeginTaskGroupConf  pfSysMCBeginTaskGroupConf
	#define CHK_SysMCBeginTaskGroupConf  (pfSysMCBeginTaskGroupConf != NULL)
	#define EXP_SysMCBeginTaskGroupConf  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBeginTaskGroupConf", (RTS_UINTPTR)SysMCBeginTaskGroupConf, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCEndTaskGroupConf(RTS_HANDLE hTaskGroup);
typedef RTS_RESULT (CDECL * PFSYSMCENDTASKGROUPCONF) (RTS_HANDLE hTaskGroup);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCENDTASKGROUPCONF_NOTIMPLEMENTED)
	#define USE_SysMCEndTaskGroupConf
	#define EXT_SysMCEndTaskGroupConf
	#define GET_SysMCEndTaskGroupConf(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCEndTaskGroupConf(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCEndTaskGroupConf  FALSE
	#define EXP_SysMCEndTaskGroupConf  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCEndTaskGroupConf
	#define EXT_SysMCEndTaskGroupConf
	#define GET_SysMCEndTaskGroupConf(fl)  CAL_CMGETAPI( "SysMCEndTaskGroupConf" ) 
	#define CAL_SysMCEndTaskGroupConf  SysMCEndTaskGroupConf
	#define CHK_SysMCEndTaskGroupConf  TRUE
	#define EXP_SysMCEndTaskGroupConf  CAL_CMEXPAPI( "SysMCEndTaskGroupConf" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCEndTaskGroupConf
	#define EXT_SysMCEndTaskGroupConf
	#define GET_SysMCEndTaskGroupConf(fl)  CAL_CMGETAPI( "SysMCEndTaskGroupConf" ) 
	#define CAL_SysMCEndTaskGroupConf  SysMCEndTaskGroupConf
	#define CHK_SysMCEndTaskGroupConf  TRUE
	#define EXP_SysMCEndTaskGroupConf  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCEndTaskGroupConf", (RTS_UINTPTR)SysMCEndTaskGroupConf, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCEndTaskGroupConf
	#define EXT_SysCpuMultiCoreSysMCEndTaskGroupConf
	#define GET_SysCpuMultiCoreSysMCEndTaskGroupConf  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCEndTaskGroupConf pISysCpuMultiCore->ISysMCEndTaskGroupConf
	#define CHK_SysCpuMultiCoreSysMCEndTaskGroupConf (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCEndTaskGroupConf  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCEndTaskGroupConf
	#define EXT_SysMCEndTaskGroupConf
	#define GET_SysMCEndTaskGroupConf(fl)  CAL_CMGETAPI( "SysMCEndTaskGroupConf" ) 
	#define CAL_SysMCEndTaskGroupConf pISysCpuMultiCore->ISysMCEndTaskGroupConf
	#define CHK_SysMCEndTaskGroupConf (pISysCpuMultiCore != NULL)
	#define EXP_SysMCEndTaskGroupConf  CAL_CMEXPAPI( "SysMCEndTaskGroupConf" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCEndTaskGroupConf  PFSYSMCENDTASKGROUPCONF pfSysMCEndTaskGroupConf;
	#define EXT_SysMCEndTaskGroupConf  extern PFSYSMCENDTASKGROUPCONF pfSysMCEndTaskGroupConf;
	#define GET_SysMCEndTaskGroupConf(fl)  s_pfCMGetAPI2( "SysMCEndTaskGroupConf", (RTS_VOID_FCTPTR *)&pfSysMCEndTaskGroupConf, (fl), 0, 0)
	#define CAL_SysMCEndTaskGroupConf  pfSysMCEndTaskGroupConf
	#define CHK_SysMCEndTaskGroupConf  (pfSysMCEndTaskGroupConf != NULL)
	#define EXP_SysMCEndTaskGroupConf  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCEndTaskGroupConf", (RTS_UINTPTR)SysMCEndTaskGroupConf, 0, 0) 
#endif




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
CpuCoreBindingDesc * CDECL SysMCBDAlloc(RTS_RESULT* pResult);
typedef CpuCoreBindingDesc * (CDECL * PFSYSMCBDALLOC) (RTS_RESULT* pResult);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBDALLOC_NOTIMPLEMENTED)
	#define USE_SysMCBDAlloc
	#define EXT_SysMCBDAlloc
	#define GET_SysMCBDAlloc(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCBDAlloc(p0)  (CpuCoreBindingDesc *)ERR_NOTIMPLEMENTED
	#define CHK_SysMCBDAlloc  FALSE
	#define EXP_SysMCBDAlloc  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCBDAlloc
	#define EXT_SysMCBDAlloc
	#define GET_SysMCBDAlloc(fl)  CAL_CMGETAPI( "SysMCBDAlloc" ) 
	#define CAL_SysMCBDAlloc  SysMCBDAlloc
	#define CHK_SysMCBDAlloc  TRUE
	#define EXP_SysMCBDAlloc  CAL_CMEXPAPI( "SysMCBDAlloc" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCBDAlloc
	#define EXT_SysMCBDAlloc
	#define GET_SysMCBDAlloc(fl)  CAL_CMGETAPI( "SysMCBDAlloc" ) 
	#define CAL_SysMCBDAlloc  SysMCBDAlloc
	#define CHK_SysMCBDAlloc  TRUE
	#define EXP_SysMCBDAlloc  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBDAlloc", (RTS_UINTPTR)SysMCBDAlloc, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCBDAlloc
	#define EXT_SysCpuMultiCoreSysMCBDAlloc
	#define GET_SysCpuMultiCoreSysMCBDAlloc  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCBDAlloc pISysCpuMultiCore->ISysMCBDAlloc
	#define CHK_SysCpuMultiCoreSysMCBDAlloc (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCBDAlloc  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCBDAlloc
	#define EXT_SysMCBDAlloc
	#define GET_SysMCBDAlloc(fl)  CAL_CMGETAPI( "SysMCBDAlloc" ) 
	#define CAL_SysMCBDAlloc pISysCpuMultiCore->ISysMCBDAlloc
	#define CHK_SysMCBDAlloc (pISysCpuMultiCore != NULL)
	#define EXP_SysMCBDAlloc  CAL_CMEXPAPI( "SysMCBDAlloc" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCBDAlloc  PFSYSMCBDALLOC pfSysMCBDAlloc;
	#define EXT_SysMCBDAlloc  extern PFSYSMCBDALLOC pfSysMCBDAlloc;
	#define GET_SysMCBDAlloc(fl)  s_pfCMGetAPI2( "SysMCBDAlloc", (RTS_VOID_FCTPTR *)&pfSysMCBDAlloc, (fl), 0, 0)
	#define CAL_SysMCBDAlloc  pfSysMCBDAlloc
	#define CHK_SysMCBDAlloc  (pfSysMCBDAlloc != NULL)
	#define EXP_SysMCBDAlloc  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBDAlloc", (RTS_UINTPTR)SysMCBDAlloc, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCBDFree(CpuCoreBindingDesc *pBindingDesc);
typedef RTS_RESULT (CDECL * PFSYSMCBDFREE) (CpuCoreBindingDesc *pBindingDesc);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBDFREE_NOTIMPLEMENTED)
	#define USE_SysMCBDFree
	#define EXT_SysMCBDFree
	#define GET_SysMCBDFree(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCBDFree(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCBDFree  FALSE
	#define EXP_SysMCBDFree  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCBDFree
	#define EXT_SysMCBDFree
	#define GET_SysMCBDFree(fl)  CAL_CMGETAPI( "SysMCBDFree" ) 
	#define CAL_SysMCBDFree  SysMCBDFree
	#define CHK_SysMCBDFree  TRUE
	#define EXP_SysMCBDFree  CAL_CMEXPAPI( "SysMCBDFree" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCBDFree
	#define EXT_SysMCBDFree
	#define GET_SysMCBDFree(fl)  CAL_CMGETAPI( "SysMCBDFree" ) 
	#define CAL_SysMCBDFree  SysMCBDFree
	#define CHK_SysMCBDFree  TRUE
	#define EXP_SysMCBDFree  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBDFree", (RTS_UINTPTR)SysMCBDFree, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCBDFree
	#define EXT_SysCpuMultiCoreSysMCBDFree
	#define GET_SysCpuMultiCoreSysMCBDFree  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCBDFree pISysCpuMultiCore->ISysMCBDFree
	#define CHK_SysCpuMultiCoreSysMCBDFree (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCBDFree  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCBDFree
	#define EXT_SysMCBDFree
	#define GET_SysMCBDFree(fl)  CAL_CMGETAPI( "SysMCBDFree" ) 
	#define CAL_SysMCBDFree pISysCpuMultiCore->ISysMCBDFree
	#define CHK_SysMCBDFree (pISysCpuMultiCore != NULL)
	#define EXP_SysMCBDFree  CAL_CMEXPAPI( "SysMCBDFree" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCBDFree  PFSYSMCBDFREE pfSysMCBDFree;
	#define EXT_SysMCBDFree  extern PFSYSMCBDFREE pfSysMCBDFree;
	#define GET_SysMCBDFree(fl)  s_pfCMGetAPI2( "SysMCBDFree", (RTS_VOID_FCTPTR *)&pfSysMCBDFree, (fl), 0, 0)
	#define CAL_SysMCBDFree  pfSysMCBDFree
	#define CHK_SysMCBDFree  (pfSysMCBDFree != NULL)
	#define EXP_SysMCBDFree  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBDFree", (RTS_UINTPTR)SysMCBDFree, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCBDZero(CpuCoreBindingDesc *pBindingDesc);
typedef RTS_RESULT (CDECL * PFSYSMCBDZERO) (CpuCoreBindingDesc *pBindingDesc);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBDZERO_NOTIMPLEMENTED)
	#define USE_SysMCBDZero
	#define EXT_SysMCBDZero
	#define GET_SysMCBDZero(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCBDZero(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCBDZero  FALSE
	#define EXP_SysMCBDZero  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCBDZero
	#define EXT_SysMCBDZero
	#define GET_SysMCBDZero(fl)  CAL_CMGETAPI( "SysMCBDZero" ) 
	#define CAL_SysMCBDZero  SysMCBDZero
	#define CHK_SysMCBDZero  TRUE
	#define EXP_SysMCBDZero  CAL_CMEXPAPI( "SysMCBDZero" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCBDZero
	#define EXT_SysMCBDZero
	#define GET_SysMCBDZero(fl)  CAL_CMGETAPI( "SysMCBDZero" ) 
	#define CAL_SysMCBDZero  SysMCBDZero
	#define CHK_SysMCBDZero  TRUE
	#define EXP_SysMCBDZero  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBDZero", (RTS_UINTPTR)SysMCBDZero, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCBDZero
	#define EXT_SysCpuMultiCoreSysMCBDZero
	#define GET_SysCpuMultiCoreSysMCBDZero  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCBDZero pISysCpuMultiCore->ISysMCBDZero
	#define CHK_SysCpuMultiCoreSysMCBDZero (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCBDZero  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCBDZero
	#define EXT_SysMCBDZero
	#define GET_SysMCBDZero(fl)  CAL_CMGETAPI( "SysMCBDZero" ) 
	#define CAL_SysMCBDZero pISysCpuMultiCore->ISysMCBDZero
	#define CHK_SysMCBDZero (pISysCpuMultiCore != NULL)
	#define EXP_SysMCBDZero  CAL_CMEXPAPI( "SysMCBDZero" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCBDZero  PFSYSMCBDZERO pfSysMCBDZero;
	#define EXT_SysMCBDZero  extern PFSYSMCBDZERO pfSysMCBDZero;
	#define GET_SysMCBDZero(fl)  s_pfCMGetAPI2( "SysMCBDZero", (RTS_VOID_FCTPTR *)&pfSysMCBDZero, (fl), 0, 0)
	#define CAL_SysMCBDZero  pfSysMCBDZero
	#define CHK_SysMCBDZero  (pfSysMCBDZero != NULL)
	#define EXP_SysMCBDZero  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBDZero", (RTS_UINTPTR)SysMCBDZero, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCBDSet(CpuCoreBindingDesc *pBindingDesc, RTS_UI32 uCoreId);
typedef RTS_RESULT (CDECL * PFSYSMCBDSET) (CpuCoreBindingDesc *pBindingDesc, RTS_UI32 uCoreId);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBDSET_NOTIMPLEMENTED)
	#define USE_SysMCBDSet
	#define EXT_SysMCBDSet
	#define GET_SysMCBDSet(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCBDSet(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCBDSet  FALSE
	#define EXP_SysMCBDSet  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCBDSet
	#define EXT_SysMCBDSet
	#define GET_SysMCBDSet(fl)  CAL_CMGETAPI( "SysMCBDSet" ) 
	#define CAL_SysMCBDSet  SysMCBDSet
	#define CHK_SysMCBDSet  TRUE
	#define EXP_SysMCBDSet  CAL_CMEXPAPI( "SysMCBDSet" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCBDSet
	#define EXT_SysMCBDSet
	#define GET_SysMCBDSet(fl)  CAL_CMGETAPI( "SysMCBDSet" ) 
	#define CAL_SysMCBDSet  SysMCBDSet
	#define CHK_SysMCBDSet  TRUE
	#define EXP_SysMCBDSet  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBDSet", (RTS_UINTPTR)SysMCBDSet, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCBDSet
	#define EXT_SysCpuMultiCoreSysMCBDSet
	#define GET_SysCpuMultiCoreSysMCBDSet  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCBDSet pISysCpuMultiCore->ISysMCBDSet
	#define CHK_SysCpuMultiCoreSysMCBDSet (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCBDSet  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCBDSet
	#define EXT_SysMCBDSet
	#define GET_SysMCBDSet(fl)  CAL_CMGETAPI( "SysMCBDSet" ) 
	#define CAL_SysMCBDSet pISysCpuMultiCore->ISysMCBDSet
	#define CHK_SysMCBDSet (pISysCpuMultiCore != NULL)
	#define EXP_SysMCBDSet  CAL_CMEXPAPI( "SysMCBDSet" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCBDSet  PFSYSMCBDSET pfSysMCBDSet;
	#define EXT_SysMCBDSet  extern PFSYSMCBDSET pfSysMCBDSet;
	#define GET_SysMCBDSet(fl)  s_pfCMGetAPI2( "SysMCBDSet", (RTS_VOID_FCTPTR *)&pfSysMCBDSet, (fl), 0, 0)
	#define CAL_SysMCBDSet  pfSysMCBDSet
	#define CHK_SysMCBDSet  (pfSysMCBDSet != NULL)
	#define EXP_SysMCBDSet  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBDSet", (RTS_UINTPTR)SysMCBDSet, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCBDReset(CpuCoreBindingDesc *pBindingDesc, RTS_UI32 uCoreId);
typedef RTS_RESULT (CDECL * PFSYSMCBDRESET) (CpuCoreBindingDesc *pBindingDesc, RTS_UI32 uCoreId);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBDRESET_NOTIMPLEMENTED)
	#define USE_SysMCBDReset
	#define EXT_SysMCBDReset
	#define GET_SysMCBDReset(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCBDReset(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCBDReset  FALSE
	#define EXP_SysMCBDReset  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCBDReset
	#define EXT_SysMCBDReset
	#define GET_SysMCBDReset(fl)  CAL_CMGETAPI( "SysMCBDReset" ) 
	#define CAL_SysMCBDReset  SysMCBDReset
	#define CHK_SysMCBDReset  TRUE
	#define EXP_SysMCBDReset  CAL_CMEXPAPI( "SysMCBDReset" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCBDReset
	#define EXT_SysMCBDReset
	#define GET_SysMCBDReset(fl)  CAL_CMGETAPI( "SysMCBDReset" ) 
	#define CAL_SysMCBDReset  SysMCBDReset
	#define CHK_SysMCBDReset  TRUE
	#define EXP_SysMCBDReset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBDReset", (RTS_UINTPTR)SysMCBDReset, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCBDReset
	#define EXT_SysCpuMultiCoreSysMCBDReset
	#define GET_SysCpuMultiCoreSysMCBDReset  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCBDReset pISysCpuMultiCore->ISysMCBDReset
	#define CHK_SysCpuMultiCoreSysMCBDReset (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCBDReset  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCBDReset
	#define EXT_SysMCBDReset
	#define GET_SysMCBDReset(fl)  CAL_CMGETAPI( "SysMCBDReset" ) 
	#define CAL_SysMCBDReset pISysCpuMultiCore->ISysMCBDReset
	#define CHK_SysMCBDReset (pISysCpuMultiCore != NULL)
	#define EXP_SysMCBDReset  CAL_CMEXPAPI( "SysMCBDReset" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCBDReset  PFSYSMCBDRESET pfSysMCBDReset;
	#define EXT_SysMCBDReset  extern PFSYSMCBDRESET pfSysMCBDReset;
	#define GET_SysMCBDReset(fl)  s_pfCMGetAPI2( "SysMCBDReset", (RTS_VOID_FCTPTR *)&pfSysMCBDReset, (fl), 0, 0)
	#define CAL_SysMCBDReset  pfSysMCBDReset
	#define CHK_SysMCBDReset  (pfSysMCBDReset != NULL)
	#define EXP_SysMCBDReset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBDReset", (RTS_UINTPTR)SysMCBDReset, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCBDIsSet(CpuCoreBindingDesc *pBindingDesc, RTS_UI32 uCoreId);
typedef RTS_RESULT (CDECL * PFSYSMCBDISSET) (CpuCoreBindingDesc *pBindingDesc, RTS_UI32 uCoreId);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBDISSET_NOTIMPLEMENTED)
	#define USE_SysMCBDIsSet
	#define EXT_SysMCBDIsSet
	#define GET_SysMCBDIsSet(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCBDIsSet(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCBDIsSet  FALSE
	#define EXP_SysMCBDIsSet  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCBDIsSet
	#define EXT_SysMCBDIsSet
	#define GET_SysMCBDIsSet(fl)  CAL_CMGETAPI( "SysMCBDIsSet" ) 
	#define CAL_SysMCBDIsSet  SysMCBDIsSet
	#define CHK_SysMCBDIsSet  TRUE
	#define EXP_SysMCBDIsSet  CAL_CMEXPAPI( "SysMCBDIsSet" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCBDIsSet
	#define EXT_SysMCBDIsSet
	#define GET_SysMCBDIsSet(fl)  CAL_CMGETAPI( "SysMCBDIsSet" ) 
	#define CAL_SysMCBDIsSet  SysMCBDIsSet
	#define CHK_SysMCBDIsSet  TRUE
	#define EXP_SysMCBDIsSet  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBDIsSet", (RTS_UINTPTR)SysMCBDIsSet, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCBDIsSet
	#define EXT_SysCpuMultiCoreSysMCBDIsSet
	#define GET_SysCpuMultiCoreSysMCBDIsSet  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCBDIsSet pISysCpuMultiCore->ISysMCBDIsSet
	#define CHK_SysCpuMultiCoreSysMCBDIsSet (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCBDIsSet  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCBDIsSet
	#define EXT_SysMCBDIsSet
	#define GET_SysMCBDIsSet(fl)  CAL_CMGETAPI( "SysMCBDIsSet" ) 
	#define CAL_SysMCBDIsSet pISysCpuMultiCore->ISysMCBDIsSet
	#define CHK_SysMCBDIsSet (pISysCpuMultiCore != NULL)
	#define EXP_SysMCBDIsSet  CAL_CMEXPAPI( "SysMCBDIsSet" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCBDIsSet  PFSYSMCBDISSET pfSysMCBDIsSet;
	#define EXT_SysMCBDIsSet  extern PFSYSMCBDISSET pfSysMCBDIsSet;
	#define GET_SysMCBDIsSet(fl)  s_pfCMGetAPI2( "SysMCBDIsSet", (RTS_VOID_FCTPTR *)&pfSysMCBDIsSet, (fl), 0, 0)
	#define CAL_SysMCBDIsSet  pfSysMCBDIsSet
	#define CHK_SysMCBDIsSet  (pfSysMCBDIsSet != NULL)
	#define EXP_SysMCBDIsSet  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBDIsSet", (RTS_UINTPTR)SysMCBDIsSet, 0, 0) 
#endif




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
RTS_UI32 CDECL SysMCBDCount(CpuCoreBindingDesc *pBindingDesc, RTS_RESULT* pResult);
typedef RTS_UI32 (CDECL * PFSYSMCBDCOUNT) (CpuCoreBindingDesc *pBindingDesc, RTS_RESULT* pResult);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBDCOUNT_NOTIMPLEMENTED)
	#define USE_SysMCBDCount
	#define EXT_SysMCBDCount
	#define GET_SysMCBDCount(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCBDCount(p0,p1)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_SysMCBDCount  FALSE
	#define EXP_SysMCBDCount  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCBDCount
	#define EXT_SysMCBDCount
	#define GET_SysMCBDCount(fl)  CAL_CMGETAPI( "SysMCBDCount" ) 
	#define CAL_SysMCBDCount  SysMCBDCount
	#define CHK_SysMCBDCount  TRUE
	#define EXP_SysMCBDCount  CAL_CMEXPAPI( "SysMCBDCount" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCBDCount
	#define EXT_SysMCBDCount
	#define GET_SysMCBDCount(fl)  CAL_CMGETAPI( "SysMCBDCount" ) 
	#define CAL_SysMCBDCount  SysMCBDCount
	#define CHK_SysMCBDCount  TRUE
	#define EXP_SysMCBDCount  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBDCount", (RTS_UINTPTR)SysMCBDCount, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCBDCount
	#define EXT_SysCpuMultiCoreSysMCBDCount
	#define GET_SysCpuMultiCoreSysMCBDCount  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCBDCount pISysCpuMultiCore->ISysMCBDCount
	#define CHK_SysCpuMultiCoreSysMCBDCount (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCBDCount  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCBDCount
	#define EXT_SysMCBDCount
	#define GET_SysMCBDCount(fl)  CAL_CMGETAPI( "SysMCBDCount" ) 
	#define CAL_SysMCBDCount pISysCpuMultiCore->ISysMCBDCount
	#define CHK_SysMCBDCount (pISysCpuMultiCore != NULL)
	#define EXP_SysMCBDCount  CAL_CMEXPAPI( "SysMCBDCount" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCBDCount  PFSYSMCBDCOUNT pfSysMCBDCount;
	#define EXT_SysMCBDCount  extern PFSYSMCBDCOUNT pfSysMCBDCount;
	#define GET_SysMCBDCount(fl)  s_pfCMGetAPI2( "SysMCBDCount", (RTS_VOID_FCTPTR *)&pfSysMCBDCount, (fl), 0, 0)
	#define CAL_SysMCBDCount  pfSysMCBDCount
	#define CHK_SysMCBDCount  (pfSysMCBDCount != NULL)
	#define EXP_SysMCBDCount  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBDCount", (RTS_UINTPTR)SysMCBDCount, 0, 0) 
#endif




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
RTS_UI32 CDECL SysMCBDGetFirstID(CpuCoreBindingDesc *pBindingDesc, RTS_RESULT* pResult);
typedef RTS_UI32 (CDECL * PFSYSMCBDGETFIRSTID) (CpuCoreBindingDesc *pBindingDesc, RTS_RESULT* pResult);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBDGETFIRSTID_NOTIMPLEMENTED)
	#define USE_SysMCBDGetFirstID
	#define EXT_SysMCBDGetFirstID
	#define GET_SysMCBDGetFirstID(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCBDGetFirstID(p0,p1)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_SysMCBDGetFirstID  FALSE
	#define EXP_SysMCBDGetFirstID  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCBDGetFirstID
	#define EXT_SysMCBDGetFirstID
	#define GET_SysMCBDGetFirstID(fl)  CAL_CMGETAPI( "SysMCBDGetFirstID" ) 
	#define CAL_SysMCBDGetFirstID  SysMCBDGetFirstID
	#define CHK_SysMCBDGetFirstID  TRUE
	#define EXP_SysMCBDGetFirstID  CAL_CMEXPAPI( "SysMCBDGetFirstID" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCBDGetFirstID
	#define EXT_SysMCBDGetFirstID
	#define GET_SysMCBDGetFirstID(fl)  CAL_CMGETAPI( "SysMCBDGetFirstID" ) 
	#define CAL_SysMCBDGetFirstID  SysMCBDGetFirstID
	#define CHK_SysMCBDGetFirstID  TRUE
	#define EXP_SysMCBDGetFirstID  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBDGetFirstID", (RTS_UINTPTR)SysMCBDGetFirstID, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCBDGetFirstID
	#define EXT_SysCpuMultiCoreSysMCBDGetFirstID
	#define GET_SysCpuMultiCoreSysMCBDGetFirstID  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCBDGetFirstID pISysCpuMultiCore->ISysMCBDGetFirstID
	#define CHK_SysCpuMultiCoreSysMCBDGetFirstID (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCBDGetFirstID  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCBDGetFirstID
	#define EXT_SysMCBDGetFirstID
	#define GET_SysMCBDGetFirstID(fl)  CAL_CMGETAPI( "SysMCBDGetFirstID" ) 
	#define CAL_SysMCBDGetFirstID pISysCpuMultiCore->ISysMCBDGetFirstID
	#define CHK_SysMCBDGetFirstID (pISysCpuMultiCore != NULL)
	#define EXP_SysMCBDGetFirstID  CAL_CMEXPAPI( "SysMCBDGetFirstID" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCBDGetFirstID  PFSYSMCBDGETFIRSTID pfSysMCBDGetFirstID;
	#define EXT_SysMCBDGetFirstID  extern PFSYSMCBDGETFIRSTID pfSysMCBDGetFirstID;
	#define GET_SysMCBDGetFirstID(fl)  s_pfCMGetAPI2( "SysMCBDGetFirstID", (RTS_VOID_FCTPTR *)&pfSysMCBDGetFirstID, (fl), 0, 0)
	#define CAL_SysMCBDGetFirstID  pfSysMCBDGetFirstID
	#define CHK_SysMCBDGetFirstID  (pfSysMCBDGetFirstID != NULL)
	#define EXP_SysMCBDGetFirstID  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBDGetFirstID", (RTS_UINTPTR)SysMCBDGetFirstID, 0, 0) 
#endif




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
RTS_UI32 CDECL SysMCBDGetNextID(CpuCoreBindingDesc *pBindingDesc, RTS_UI32 uPrevCoreID, RTS_RESULT* pResult);
typedef RTS_UI32 (CDECL * PFSYSMCBDGETNEXTID) (CpuCoreBindingDesc *pBindingDesc, RTS_UI32 uPrevCoreID, RTS_RESULT* pResult);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBDGETNEXTID_NOTIMPLEMENTED)
	#define USE_SysMCBDGetNextID
	#define EXT_SysMCBDGetNextID
	#define GET_SysMCBDGetNextID(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCBDGetNextID(p0,p1,p2)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_SysMCBDGetNextID  FALSE
	#define EXP_SysMCBDGetNextID  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCBDGetNextID
	#define EXT_SysMCBDGetNextID
	#define GET_SysMCBDGetNextID(fl)  CAL_CMGETAPI( "SysMCBDGetNextID" ) 
	#define CAL_SysMCBDGetNextID  SysMCBDGetNextID
	#define CHK_SysMCBDGetNextID  TRUE
	#define EXP_SysMCBDGetNextID  CAL_CMEXPAPI( "SysMCBDGetNextID" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCBDGetNextID
	#define EXT_SysMCBDGetNextID
	#define GET_SysMCBDGetNextID(fl)  CAL_CMGETAPI( "SysMCBDGetNextID" ) 
	#define CAL_SysMCBDGetNextID  SysMCBDGetNextID
	#define CHK_SysMCBDGetNextID  TRUE
	#define EXP_SysMCBDGetNextID  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBDGetNextID", (RTS_UINTPTR)SysMCBDGetNextID, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCBDGetNextID
	#define EXT_SysCpuMultiCoreSysMCBDGetNextID
	#define GET_SysCpuMultiCoreSysMCBDGetNextID  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCBDGetNextID pISysCpuMultiCore->ISysMCBDGetNextID
	#define CHK_SysCpuMultiCoreSysMCBDGetNextID (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCBDGetNextID  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCBDGetNextID
	#define EXT_SysMCBDGetNextID
	#define GET_SysMCBDGetNextID(fl)  CAL_CMGETAPI( "SysMCBDGetNextID" ) 
	#define CAL_SysMCBDGetNextID pISysCpuMultiCore->ISysMCBDGetNextID
	#define CHK_SysMCBDGetNextID (pISysCpuMultiCore != NULL)
	#define EXP_SysMCBDGetNextID  CAL_CMEXPAPI( "SysMCBDGetNextID" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCBDGetNextID  PFSYSMCBDGETNEXTID pfSysMCBDGetNextID;
	#define EXT_SysMCBDGetNextID  extern PFSYSMCBDGETNEXTID pfSysMCBDGetNextID;
	#define GET_SysMCBDGetNextID(fl)  s_pfCMGetAPI2( "SysMCBDGetNextID", (RTS_VOID_FCTPTR *)&pfSysMCBDGetNextID, (fl), 0, 0)
	#define CAL_SysMCBDGetNextID  pfSysMCBDGetNextID
	#define CHK_SysMCBDGetNextID  (pfSysMCBDGetNextID != NULL)
	#define EXP_SysMCBDGetNextID  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBDGetNextID", (RTS_UINTPTR)SysMCBDGetNextID, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCBindProcess(CpuCoreBindingDesc *pBindingDesc, RTS_IEC_HANDLE hProcess);
typedef RTS_RESULT (CDECL * PFSYSMCBINDPROCESS) (CpuCoreBindingDesc *pBindingDesc, RTS_IEC_HANDLE hProcess);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBINDPROCESS_NOTIMPLEMENTED)
	#define USE_SysMCBindProcess
	#define EXT_SysMCBindProcess
	#define GET_SysMCBindProcess(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCBindProcess(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCBindProcess  FALSE
	#define EXP_SysMCBindProcess  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCBindProcess
	#define EXT_SysMCBindProcess
	#define GET_SysMCBindProcess(fl)  CAL_CMGETAPI( "SysMCBindProcess" ) 
	#define CAL_SysMCBindProcess  SysMCBindProcess
	#define CHK_SysMCBindProcess  TRUE
	#define EXP_SysMCBindProcess  CAL_CMEXPAPI( "SysMCBindProcess" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCBindProcess
	#define EXT_SysMCBindProcess
	#define GET_SysMCBindProcess(fl)  CAL_CMGETAPI( "SysMCBindProcess" ) 
	#define CAL_SysMCBindProcess  SysMCBindProcess
	#define CHK_SysMCBindProcess  TRUE
	#define EXP_SysMCBindProcess  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBindProcess", (RTS_UINTPTR)SysMCBindProcess, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCBindProcess
	#define EXT_SysCpuMultiCoreSysMCBindProcess
	#define GET_SysCpuMultiCoreSysMCBindProcess  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCBindProcess pISysCpuMultiCore->ISysMCBindProcess
	#define CHK_SysCpuMultiCoreSysMCBindProcess (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCBindProcess  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCBindProcess
	#define EXT_SysMCBindProcess
	#define GET_SysMCBindProcess(fl)  CAL_CMGETAPI( "SysMCBindProcess" ) 
	#define CAL_SysMCBindProcess pISysCpuMultiCore->ISysMCBindProcess
	#define CHK_SysMCBindProcess (pISysCpuMultiCore != NULL)
	#define EXP_SysMCBindProcess  CAL_CMEXPAPI( "SysMCBindProcess" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCBindProcess  PFSYSMCBINDPROCESS pfSysMCBindProcess;
	#define EXT_SysMCBindProcess  extern PFSYSMCBINDPROCESS pfSysMCBindProcess;
	#define GET_SysMCBindProcess(fl)  s_pfCMGetAPI2( "SysMCBindProcess", (RTS_VOID_FCTPTR *)&pfSysMCBindProcess, (fl), 0, 0)
	#define CAL_SysMCBindProcess  pfSysMCBindProcess
	#define CHK_SysMCBindProcess  (pfSysMCBindProcess != NULL)
	#define EXP_SysMCBindProcess  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBindProcess", (RTS_UINTPTR)SysMCBindProcess, 0, 0) 
#endif




/**
 * <description>
 * The OS implementation of SysMCBindProcess
 * </description>
 */
RTS_RESULT CDECL SysMCBindProcess_(CpuCoreBindingDesc *pBindingDesc, RTS_IEC_HANDLE hProcess);
typedef RTS_RESULT (CDECL * PFSYSMCBINDPROCESS_) (CpuCoreBindingDesc *pBindingDesc, RTS_IEC_HANDLE hProcess);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBINDPROCESS__NOTIMPLEMENTED)
	#define USE_SysMCBindProcess_
	#define EXT_SysMCBindProcess_
	#define GET_SysMCBindProcess_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCBindProcess_(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCBindProcess_  FALSE
	#define EXP_SysMCBindProcess_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCBindProcess_
	#define EXT_SysMCBindProcess_
	#define GET_SysMCBindProcess_(fl)  CAL_CMGETAPI( "SysMCBindProcess_" ) 
	#define CAL_SysMCBindProcess_  SysMCBindProcess_
	#define CHK_SysMCBindProcess_  TRUE
	#define EXP_SysMCBindProcess_  CAL_CMEXPAPI( "SysMCBindProcess_" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCBindProcess_
	#define EXT_SysMCBindProcess_
	#define GET_SysMCBindProcess_(fl)  CAL_CMGETAPI( "SysMCBindProcess_" ) 
	#define CAL_SysMCBindProcess_  SysMCBindProcess_
	#define CHK_SysMCBindProcess_  TRUE
	#define EXP_SysMCBindProcess_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBindProcess_", (RTS_UINTPTR)SysMCBindProcess_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCBindProcess_
	#define EXT_SysCpuMultiCoreSysMCBindProcess_
	#define GET_SysCpuMultiCoreSysMCBindProcess_  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCBindProcess_ pISysCpuMultiCore->ISysMCBindProcess_
	#define CHK_SysCpuMultiCoreSysMCBindProcess_ (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCBindProcess_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCBindProcess_
	#define EXT_SysMCBindProcess_
	#define GET_SysMCBindProcess_(fl)  CAL_CMGETAPI( "SysMCBindProcess_" ) 
	#define CAL_SysMCBindProcess_ pISysCpuMultiCore->ISysMCBindProcess_
	#define CHK_SysMCBindProcess_ (pISysCpuMultiCore != NULL)
	#define EXP_SysMCBindProcess_  CAL_CMEXPAPI( "SysMCBindProcess_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCBindProcess_  PFSYSMCBINDPROCESS_ pfSysMCBindProcess_;
	#define EXT_SysMCBindProcess_  extern PFSYSMCBINDPROCESS_ pfSysMCBindProcess_;
	#define GET_SysMCBindProcess_(fl)  s_pfCMGetAPI2( "SysMCBindProcess_", (RTS_VOID_FCTPTR *)&pfSysMCBindProcess_, (fl), 0, 0)
	#define CAL_SysMCBindProcess_  pfSysMCBindProcess_
	#define CHK_SysMCBindProcess_  (pfSysMCBindProcess_ != NULL)
	#define EXP_SysMCBindProcess_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBindProcess_", (RTS_UINTPTR)SysMCBindProcess_, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCBindTask(CpuCoreBindingDesc *pBindingDesc, RTS_IEC_HANDLE hTask);
typedef RTS_RESULT (CDECL * PFSYSMCBINDTASK) (CpuCoreBindingDesc *pBindingDesc, RTS_IEC_HANDLE hTask);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBINDTASK_NOTIMPLEMENTED)
	#define USE_SysMCBindTask
	#define EXT_SysMCBindTask
	#define GET_SysMCBindTask(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCBindTask(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCBindTask  FALSE
	#define EXP_SysMCBindTask  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCBindTask
	#define EXT_SysMCBindTask
	#define GET_SysMCBindTask(fl)  CAL_CMGETAPI( "SysMCBindTask" ) 
	#define CAL_SysMCBindTask  SysMCBindTask
	#define CHK_SysMCBindTask  TRUE
	#define EXP_SysMCBindTask  CAL_CMEXPAPI( "SysMCBindTask" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCBindTask
	#define EXT_SysMCBindTask
	#define GET_SysMCBindTask(fl)  CAL_CMGETAPI( "SysMCBindTask" ) 
	#define CAL_SysMCBindTask  SysMCBindTask
	#define CHK_SysMCBindTask  TRUE
	#define EXP_SysMCBindTask  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBindTask", (RTS_UINTPTR)SysMCBindTask, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCBindTask
	#define EXT_SysCpuMultiCoreSysMCBindTask
	#define GET_SysCpuMultiCoreSysMCBindTask  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCBindTask pISysCpuMultiCore->ISysMCBindTask
	#define CHK_SysCpuMultiCoreSysMCBindTask (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCBindTask  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCBindTask
	#define EXT_SysMCBindTask
	#define GET_SysMCBindTask(fl)  CAL_CMGETAPI( "SysMCBindTask" ) 
	#define CAL_SysMCBindTask pISysCpuMultiCore->ISysMCBindTask
	#define CHK_SysMCBindTask (pISysCpuMultiCore != NULL)
	#define EXP_SysMCBindTask  CAL_CMEXPAPI( "SysMCBindTask" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCBindTask  PFSYSMCBINDTASK pfSysMCBindTask;
	#define EXT_SysMCBindTask  extern PFSYSMCBINDTASK pfSysMCBindTask;
	#define GET_SysMCBindTask(fl)  s_pfCMGetAPI2( "SysMCBindTask", (RTS_VOID_FCTPTR *)&pfSysMCBindTask, (fl), 0, 0)
	#define CAL_SysMCBindTask  pfSysMCBindTask
	#define CHK_SysMCBindTask  (pfSysMCBindTask != NULL)
	#define EXP_SysMCBindTask  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBindTask", (RTS_UINTPTR)SysMCBindTask, 0, 0) 
#endif




/**
 * <description>
 * The OS implementation of SysMCBindTask
 * </description>
 */
RTS_RESULT CDECL SysMCBindTask_(CpuCoreBindingDesc *pBindingDesc, RTS_IEC_HANDLE hTask);
typedef RTS_RESULT (CDECL * PFSYSMCBINDTASK_) (CpuCoreBindingDesc *pBindingDesc, RTS_IEC_HANDLE hTask);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBINDTASK__NOTIMPLEMENTED)
	#define USE_SysMCBindTask_
	#define EXT_SysMCBindTask_
	#define GET_SysMCBindTask_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCBindTask_(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCBindTask_  FALSE
	#define EXP_SysMCBindTask_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCBindTask_
	#define EXT_SysMCBindTask_
	#define GET_SysMCBindTask_(fl)  CAL_CMGETAPI( "SysMCBindTask_" ) 
	#define CAL_SysMCBindTask_  SysMCBindTask_
	#define CHK_SysMCBindTask_  TRUE
	#define EXP_SysMCBindTask_  CAL_CMEXPAPI( "SysMCBindTask_" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCBindTask_
	#define EXT_SysMCBindTask_
	#define GET_SysMCBindTask_(fl)  CAL_CMGETAPI( "SysMCBindTask_" ) 
	#define CAL_SysMCBindTask_  SysMCBindTask_
	#define CHK_SysMCBindTask_  TRUE
	#define EXP_SysMCBindTask_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBindTask_", (RTS_UINTPTR)SysMCBindTask_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCBindTask_
	#define EXT_SysCpuMultiCoreSysMCBindTask_
	#define GET_SysCpuMultiCoreSysMCBindTask_  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCBindTask_ pISysCpuMultiCore->ISysMCBindTask_
	#define CHK_SysCpuMultiCoreSysMCBindTask_ (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCBindTask_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCBindTask_
	#define EXT_SysMCBindTask_
	#define GET_SysMCBindTask_(fl)  CAL_CMGETAPI( "SysMCBindTask_" ) 
	#define CAL_SysMCBindTask_ pISysCpuMultiCore->ISysMCBindTask_
	#define CHK_SysMCBindTask_ (pISysCpuMultiCore != NULL)
	#define EXP_SysMCBindTask_  CAL_CMEXPAPI( "SysMCBindTask_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCBindTask_  PFSYSMCBINDTASK_ pfSysMCBindTask_;
	#define EXT_SysMCBindTask_  extern PFSYSMCBINDTASK_ pfSysMCBindTask_;
	#define GET_SysMCBindTask_(fl)  s_pfCMGetAPI2( "SysMCBindTask_", (RTS_VOID_FCTPTR *)&pfSysMCBindTask_, (fl), 0, 0)
	#define CAL_SysMCBindTask_  pfSysMCBindTask_
	#define CHK_SysMCBindTask_  (pfSysMCBindTask_ != NULL)
	#define EXP_SysMCBindTask_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBindTask_", (RTS_UINTPTR)SysMCBindTask_, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCUnbindProcess(RTS_IEC_HANDLE hProcess);
typedef RTS_RESULT (CDECL * PFSYSMCUNBINDPROCESS) (RTS_IEC_HANDLE hProcess);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCUNBINDPROCESS_NOTIMPLEMENTED)
	#define USE_SysMCUnbindProcess
	#define EXT_SysMCUnbindProcess
	#define GET_SysMCUnbindProcess(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCUnbindProcess(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCUnbindProcess  FALSE
	#define EXP_SysMCUnbindProcess  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCUnbindProcess
	#define EXT_SysMCUnbindProcess
	#define GET_SysMCUnbindProcess(fl)  CAL_CMGETAPI( "SysMCUnbindProcess" ) 
	#define CAL_SysMCUnbindProcess  SysMCUnbindProcess
	#define CHK_SysMCUnbindProcess  TRUE
	#define EXP_SysMCUnbindProcess  CAL_CMEXPAPI( "SysMCUnbindProcess" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCUnbindProcess
	#define EXT_SysMCUnbindProcess
	#define GET_SysMCUnbindProcess(fl)  CAL_CMGETAPI( "SysMCUnbindProcess" ) 
	#define CAL_SysMCUnbindProcess  SysMCUnbindProcess
	#define CHK_SysMCUnbindProcess  TRUE
	#define EXP_SysMCUnbindProcess  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCUnbindProcess", (RTS_UINTPTR)SysMCUnbindProcess, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCUnbindProcess
	#define EXT_SysCpuMultiCoreSysMCUnbindProcess
	#define GET_SysCpuMultiCoreSysMCUnbindProcess  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCUnbindProcess pISysCpuMultiCore->ISysMCUnbindProcess
	#define CHK_SysCpuMultiCoreSysMCUnbindProcess (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCUnbindProcess  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCUnbindProcess
	#define EXT_SysMCUnbindProcess
	#define GET_SysMCUnbindProcess(fl)  CAL_CMGETAPI( "SysMCUnbindProcess" ) 
	#define CAL_SysMCUnbindProcess pISysCpuMultiCore->ISysMCUnbindProcess
	#define CHK_SysMCUnbindProcess (pISysCpuMultiCore != NULL)
	#define EXP_SysMCUnbindProcess  CAL_CMEXPAPI( "SysMCUnbindProcess" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCUnbindProcess  PFSYSMCUNBINDPROCESS pfSysMCUnbindProcess;
	#define EXT_SysMCUnbindProcess  extern PFSYSMCUNBINDPROCESS pfSysMCUnbindProcess;
	#define GET_SysMCUnbindProcess(fl)  s_pfCMGetAPI2( "SysMCUnbindProcess", (RTS_VOID_FCTPTR *)&pfSysMCUnbindProcess, (fl), 0, 0)
	#define CAL_SysMCUnbindProcess  pfSysMCUnbindProcess
	#define CHK_SysMCUnbindProcess  (pfSysMCUnbindProcess != NULL)
	#define EXP_SysMCUnbindProcess  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCUnbindProcess", (RTS_UINTPTR)SysMCUnbindProcess, 0, 0) 
#endif




/**
 * <description>
 * The OS implementation of SysMCUnbindProcess
 * </description>
 */
RTS_RESULT CDECL SysMCUnbindProcess_(RTS_IEC_HANDLE hProcess);
typedef RTS_RESULT (CDECL * PFSYSMCUNBINDPROCESS_) (RTS_IEC_HANDLE hProcess);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCUNBINDPROCESS__NOTIMPLEMENTED)
	#define USE_SysMCUnbindProcess_
	#define EXT_SysMCUnbindProcess_
	#define GET_SysMCUnbindProcess_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCUnbindProcess_(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCUnbindProcess_  FALSE
	#define EXP_SysMCUnbindProcess_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCUnbindProcess_
	#define EXT_SysMCUnbindProcess_
	#define GET_SysMCUnbindProcess_(fl)  CAL_CMGETAPI( "SysMCUnbindProcess_" ) 
	#define CAL_SysMCUnbindProcess_  SysMCUnbindProcess_
	#define CHK_SysMCUnbindProcess_  TRUE
	#define EXP_SysMCUnbindProcess_  CAL_CMEXPAPI( "SysMCUnbindProcess_" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCUnbindProcess_
	#define EXT_SysMCUnbindProcess_
	#define GET_SysMCUnbindProcess_(fl)  CAL_CMGETAPI( "SysMCUnbindProcess_" ) 
	#define CAL_SysMCUnbindProcess_  SysMCUnbindProcess_
	#define CHK_SysMCUnbindProcess_  TRUE
	#define EXP_SysMCUnbindProcess_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCUnbindProcess_", (RTS_UINTPTR)SysMCUnbindProcess_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCUnbindProcess_
	#define EXT_SysCpuMultiCoreSysMCUnbindProcess_
	#define GET_SysCpuMultiCoreSysMCUnbindProcess_  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCUnbindProcess_ pISysCpuMultiCore->ISysMCUnbindProcess_
	#define CHK_SysCpuMultiCoreSysMCUnbindProcess_ (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCUnbindProcess_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCUnbindProcess_
	#define EXT_SysMCUnbindProcess_
	#define GET_SysMCUnbindProcess_(fl)  CAL_CMGETAPI( "SysMCUnbindProcess_" ) 
	#define CAL_SysMCUnbindProcess_ pISysCpuMultiCore->ISysMCUnbindProcess_
	#define CHK_SysMCUnbindProcess_ (pISysCpuMultiCore != NULL)
	#define EXP_SysMCUnbindProcess_  CAL_CMEXPAPI( "SysMCUnbindProcess_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCUnbindProcess_  PFSYSMCUNBINDPROCESS_ pfSysMCUnbindProcess_;
	#define EXT_SysMCUnbindProcess_  extern PFSYSMCUNBINDPROCESS_ pfSysMCUnbindProcess_;
	#define GET_SysMCUnbindProcess_(fl)  s_pfCMGetAPI2( "SysMCUnbindProcess_", (RTS_VOID_FCTPTR *)&pfSysMCUnbindProcess_, (fl), 0, 0)
	#define CAL_SysMCUnbindProcess_  pfSysMCUnbindProcess_
	#define CHK_SysMCUnbindProcess_  (pfSysMCUnbindProcess_ != NULL)
	#define EXP_SysMCUnbindProcess_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCUnbindProcess_", (RTS_UINTPTR)SysMCUnbindProcess_, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCUnbindTask(RTS_IEC_HANDLE hTask);
typedef RTS_RESULT (CDECL * PFSYSMCUNBINDTASK) (RTS_IEC_HANDLE hTask);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCUNBINDTASK_NOTIMPLEMENTED)
	#define USE_SysMCUnbindTask
	#define EXT_SysMCUnbindTask
	#define GET_SysMCUnbindTask(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCUnbindTask(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCUnbindTask  FALSE
	#define EXP_SysMCUnbindTask  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCUnbindTask
	#define EXT_SysMCUnbindTask
	#define GET_SysMCUnbindTask(fl)  CAL_CMGETAPI( "SysMCUnbindTask" ) 
	#define CAL_SysMCUnbindTask  SysMCUnbindTask
	#define CHK_SysMCUnbindTask  TRUE
	#define EXP_SysMCUnbindTask  CAL_CMEXPAPI( "SysMCUnbindTask" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCUnbindTask
	#define EXT_SysMCUnbindTask
	#define GET_SysMCUnbindTask(fl)  CAL_CMGETAPI( "SysMCUnbindTask" ) 
	#define CAL_SysMCUnbindTask  SysMCUnbindTask
	#define CHK_SysMCUnbindTask  TRUE
	#define EXP_SysMCUnbindTask  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCUnbindTask", (RTS_UINTPTR)SysMCUnbindTask, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCUnbindTask
	#define EXT_SysCpuMultiCoreSysMCUnbindTask
	#define GET_SysCpuMultiCoreSysMCUnbindTask  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCUnbindTask pISysCpuMultiCore->ISysMCUnbindTask
	#define CHK_SysCpuMultiCoreSysMCUnbindTask (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCUnbindTask  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCUnbindTask
	#define EXT_SysMCUnbindTask
	#define GET_SysMCUnbindTask(fl)  CAL_CMGETAPI( "SysMCUnbindTask" ) 
	#define CAL_SysMCUnbindTask pISysCpuMultiCore->ISysMCUnbindTask
	#define CHK_SysMCUnbindTask (pISysCpuMultiCore != NULL)
	#define EXP_SysMCUnbindTask  CAL_CMEXPAPI( "SysMCUnbindTask" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCUnbindTask  PFSYSMCUNBINDTASK pfSysMCUnbindTask;
	#define EXT_SysMCUnbindTask  extern PFSYSMCUNBINDTASK pfSysMCUnbindTask;
	#define GET_SysMCUnbindTask(fl)  s_pfCMGetAPI2( "SysMCUnbindTask", (RTS_VOID_FCTPTR *)&pfSysMCUnbindTask, (fl), 0, 0)
	#define CAL_SysMCUnbindTask  pfSysMCUnbindTask
	#define CHK_SysMCUnbindTask  (pfSysMCUnbindTask != NULL)
	#define EXP_SysMCUnbindTask  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCUnbindTask", (RTS_UINTPTR)SysMCUnbindTask, 0, 0) 
#endif




/**
 * <description>
 * The OS implementation of SysMCUnbindTask
 * </description>
 */
RTS_RESULT CDECL SysMCUnbindTask_(RTS_IEC_HANDLE hTask);
typedef RTS_RESULT (CDECL * PFSYSMCUNBINDTASK_) (RTS_IEC_HANDLE hTask);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCUNBINDTASK__NOTIMPLEMENTED)
	#define USE_SysMCUnbindTask_
	#define EXT_SysMCUnbindTask_
	#define GET_SysMCUnbindTask_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCUnbindTask_(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCUnbindTask_  FALSE
	#define EXP_SysMCUnbindTask_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCUnbindTask_
	#define EXT_SysMCUnbindTask_
	#define GET_SysMCUnbindTask_(fl)  CAL_CMGETAPI( "SysMCUnbindTask_" ) 
	#define CAL_SysMCUnbindTask_  SysMCUnbindTask_
	#define CHK_SysMCUnbindTask_  TRUE
	#define EXP_SysMCUnbindTask_  CAL_CMEXPAPI( "SysMCUnbindTask_" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCUnbindTask_
	#define EXT_SysMCUnbindTask_
	#define GET_SysMCUnbindTask_(fl)  CAL_CMGETAPI( "SysMCUnbindTask_" ) 
	#define CAL_SysMCUnbindTask_  SysMCUnbindTask_
	#define CHK_SysMCUnbindTask_  TRUE
	#define EXP_SysMCUnbindTask_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCUnbindTask_", (RTS_UINTPTR)SysMCUnbindTask_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCUnbindTask_
	#define EXT_SysCpuMultiCoreSysMCUnbindTask_
	#define GET_SysCpuMultiCoreSysMCUnbindTask_  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCUnbindTask_ pISysCpuMultiCore->ISysMCUnbindTask_
	#define CHK_SysCpuMultiCoreSysMCUnbindTask_ (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCUnbindTask_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCUnbindTask_
	#define EXT_SysMCUnbindTask_
	#define GET_SysMCUnbindTask_(fl)  CAL_CMGETAPI( "SysMCUnbindTask_" ) 
	#define CAL_SysMCUnbindTask_ pISysCpuMultiCore->ISysMCUnbindTask_
	#define CHK_SysMCUnbindTask_ (pISysCpuMultiCore != NULL)
	#define EXP_SysMCUnbindTask_  CAL_CMEXPAPI( "SysMCUnbindTask_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCUnbindTask_  PFSYSMCUNBINDTASK_ pfSysMCUnbindTask_;
	#define EXT_SysMCUnbindTask_  extern PFSYSMCUNBINDTASK_ pfSysMCUnbindTask_;
	#define GET_SysMCUnbindTask_(fl)  s_pfCMGetAPI2( "SysMCUnbindTask_", (RTS_VOID_FCTPTR *)&pfSysMCUnbindTask_, (fl), 0, 0)
	#define CAL_SysMCUnbindTask_  pfSysMCUnbindTask_
	#define CHK_SysMCUnbindTask_  (pfSysMCUnbindTask_ != NULL)
	#define EXP_SysMCUnbindTask_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCUnbindTask_", (RTS_UINTPTR)SysMCUnbindTask_, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCGetLoad(RTS_UI32 uCoreID, RTS_UI8 *pPercent);
typedef RTS_RESULT (CDECL * PFSYSMCGETLOAD) (RTS_UI32 uCoreID, RTS_UI8 *pPercent);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETLOAD_NOTIMPLEMENTED)
	#define USE_SysMCGetLoad
	#define EXT_SysMCGetLoad
	#define GET_SysMCGetLoad(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCGetLoad(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCGetLoad  FALSE
	#define EXP_SysMCGetLoad  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCGetLoad
	#define EXT_SysMCGetLoad
	#define GET_SysMCGetLoad(fl)  CAL_CMGETAPI( "SysMCGetLoad" ) 
	#define CAL_SysMCGetLoad  SysMCGetLoad
	#define CHK_SysMCGetLoad  TRUE
	#define EXP_SysMCGetLoad  CAL_CMEXPAPI( "SysMCGetLoad" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCGetLoad
	#define EXT_SysMCGetLoad
	#define GET_SysMCGetLoad(fl)  CAL_CMGETAPI( "SysMCGetLoad" ) 
	#define CAL_SysMCGetLoad  SysMCGetLoad
	#define CHK_SysMCGetLoad  TRUE
	#define EXP_SysMCGetLoad  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetLoad", (RTS_UINTPTR)SysMCGetLoad, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCGetLoad
	#define EXT_SysCpuMultiCoreSysMCGetLoad
	#define GET_SysCpuMultiCoreSysMCGetLoad  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCGetLoad pISysCpuMultiCore->ISysMCGetLoad
	#define CHK_SysCpuMultiCoreSysMCGetLoad (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCGetLoad  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCGetLoad
	#define EXT_SysMCGetLoad
	#define GET_SysMCGetLoad(fl)  CAL_CMGETAPI( "SysMCGetLoad" ) 
	#define CAL_SysMCGetLoad pISysCpuMultiCore->ISysMCGetLoad
	#define CHK_SysMCGetLoad (pISysCpuMultiCore != NULL)
	#define EXP_SysMCGetLoad  CAL_CMEXPAPI( "SysMCGetLoad" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCGetLoad  PFSYSMCGETLOAD pfSysMCGetLoad;
	#define EXT_SysMCGetLoad  extern PFSYSMCGETLOAD pfSysMCGetLoad;
	#define GET_SysMCGetLoad(fl)  s_pfCMGetAPI2( "SysMCGetLoad", (RTS_VOID_FCTPTR *)&pfSysMCGetLoad, (fl), 0, 0)
	#define CAL_SysMCGetLoad  pfSysMCGetLoad
	#define CHK_SysMCGetLoad  (pfSysMCGetLoad != NULL)
	#define EXP_SysMCGetLoad  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetLoad", (RTS_UINTPTR)SysMCGetLoad, 0, 0) 
#endif




/**
 * <description>
 * The OS implementation of SysMCGetLoad
 * </description>
 */
RTS_RESULT CDECL SysMCGetLoad_(RTS_UI32 uCoreID, RTS_UI8 *pPercent);
typedef RTS_RESULT (CDECL * PFSYSMCGETLOAD_) (RTS_UI32 uCoreID, RTS_UI8 *pPercent);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETLOAD__NOTIMPLEMENTED)
	#define USE_SysMCGetLoad_
	#define EXT_SysMCGetLoad_
	#define GET_SysMCGetLoad_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCGetLoad_(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCGetLoad_  FALSE
	#define EXP_SysMCGetLoad_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCGetLoad_
	#define EXT_SysMCGetLoad_
	#define GET_SysMCGetLoad_(fl)  CAL_CMGETAPI( "SysMCGetLoad_" ) 
	#define CAL_SysMCGetLoad_  SysMCGetLoad_
	#define CHK_SysMCGetLoad_  TRUE
	#define EXP_SysMCGetLoad_  CAL_CMEXPAPI( "SysMCGetLoad_" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCGetLoad_
	#define EXT_SysMCGetLoad_
	#define GET_SysMCGetLoad_(fl)  CAL_CMGETAPI( "SysMCGetLoad_" ) 
	#define CAL_SysMCGetLoad_  SysMCGetLoad_
	#define CHK_SysMCGetLoad_  TRUE
	#define EXP_SysMCGetLoad_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetLoad_", (RTS_UINTPTR)SysMCGetLoad_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCGetLoad_
	#define EXT_SysCpuMultiCoreSysMCGetLoad_
	#define GET_SysCpuMultiCoreSysMCGetLoad_  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCGetLoad_ pISysCpuMultiCore->ISysMCGetLoad_
	#define CHK_SysCpuMultiCoreSysMCGetLoad_ (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCGetLoad_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCGetLoad_
	#define EXT_SysMCGetLoad_
	#define GET_SysMCGetLoad_(fl)  CAL_CMGETAPI( "SysMCGetLoad_" ) 
	#define CAL_SysMCGetLoad_ pISysCpuMultiCore->ISysMCGetLoad_
	#define CHK_SysMCGetLoad_ (pISysCpuMultiCore != NULL)
	#define EXP_SysMCGetLoad_  CAL_CMEXPAPI( "SysMCGetLoad_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCGetLoad_  PFSYSMCGETLOAD_ pfSysMCGetLoad_;
	#define EXT_SysMCGetLoad_  extern PFSYSMCGETLOAD_ pfSysMCGetLoad_;
	#define GET_SysMCGetLoad_(fl)  s_pfCMGetAPI2( "SysMCGetLoad_", (RTS_VOID_FCTPTR *)&pfSysMCGetLoad_, (fl), 0, 0)
	#define CAL_SysMCGetLoad_  pfSysMCGetLoad_
	#define CHK_SysMCGetLoad_  (pfSysMCGetLoad_ != NULL)
	#define EXP_SysMCGetLoad_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetLoad_", (RTS_UINTPTR)SysMCGetLoad_, 0, 0) 
#endif




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
RTS_UI32 CDECL SysMCGetNumOfCores(RTS_RESULT* pResult);
typedef RTS_UI32 (CDECL * PFSYSMCGETNUMOFCORES) (RTS_RESULT* pResult);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETNUMOFCORES_NOTIMPLEMENTED)
	#define USE_SysMCGetNumOfCores
	#define EXT_SysMCGetNumOfCores
	#define GET_SysMCGetNumOfCores(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCGetNumOfCores(p0)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_SysMCGetNumOfCores  FALSE
	#define EXP_SysMCGetNumOfCores  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCGetNumOfCores
	#define EXT_SysMCGetNumOfCores
	#define GET_SysMCGetNumOfCores(fl)  CAL_CMGETAPI( "SysMCGetNumOfCores" ) 
	#define CAL_SysMCGetNumOfCores  SysMCGetNumOfCores
	#define CHK_SysMCGetNumOfCores  TRUE
	#define EXP_SysMCGetNumOfCores  CAL_CMEXPAPI( "SysMCGetNumOfCores" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCGetNumOfCores
	#define EXT_SysMCGetNumOfCores
	#define GET_SysMCGetNumOfCores(fl)  CAL_CMGETAPI( "SysMCGetNumOfCores" ) 
	#define CAL_SysMCGetNumOfCores  SysMCGetNumOfCores
	#define CHK_SysMCGetNumOfCores  TRUE
	#define EXP_SysMCGetNumOfCores  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetNumOfCores", (RTS_UINTPTR)SysMCGetNumOfCores, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCGetNumOfCores
	#define EXT_SysCpuMultiCoreSysMCGetNumOfCores
	#define GET_SysCpuMultiCoreSysMCGetNumOfCores  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCGetNumOfCores pISysCpuMultiCore->ISysMCGetNumOfCores
	#define CHK_SysCpuMultiCoreSysMCGetNumOfCores (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCGetNumOfCores  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCGetNumOfCores
	#define EXT_SysMCGetNumOfCores
	#define GET_SysMCGetNumOfCores(fl)  CAL_CMGETAPI( "SysMCGetNumOfCores" ) 
	#define CAL_SysMCGetNumOfCores pISysCpuMultiCore->ISysMCGetNumOfCores
	#define CHK_SysMCGetNumOfCores (pISysCpuMultiCore != NULL)
	#define EXP_SysMCGetNumOfCores  CAL_CMEXPAPI( "SysMCGetNumOfCores" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCGetNumOfCores  PFSYSMCGETNUMOFCORES pfSysMCGetNumOfCores;
	#define EXT_SysMCGetNumOfCores  extern PFSYSMCGETNUMOFCORES pfSysMCGetNumOfCores;
	#define GET_SysMCGetNumOfCores(fl)  s_pfCMGetAPI2( "SysMCGetNumOfCores", (RTS_VOID_FCTPTR *)&pfSysMCGetNumOfCores, (fl), 0, 0)
	#define CAL_SysMCGetNumOfCores  pfSysMCGetNumOfCores
	#define CHK_SysMCGetNumOfCores  (pfSysMCGetNumOfCores != NULL)
	#define EXP_SysMCGetNumOfCores  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetNumOfCores", (RTS_UINTPTR)SysMCGetNumOfCores, 0, 0) 
#endif




/**
 * <description>
 * The OS implementation of SysMCGetNumOfCores
 * </description>
 */
RTS_UI32 CDECL SysMCGetNumOfCores_(RTS_RESULT* pResult);
typedef RTS_UI32 (CDECL * PFSYSMCGETNUMOFCORES_) (RTS_RESULT* pResult);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETNUMOFCORES__NOTIMPLEMENTED)
	#define USE_SysMCGetNumOfCores_
	#define EXT_SysMCGetNumOfCores_
	#define GET_SysMCGetNumOfCores_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCGetNumOfCores_(p0)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_SysMCGetNumOfCores_  FALSE
	#define EXP_SysMCGetNumOfCores_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCGetNumOfCores_
	#define EXT_SysMCGetNumOfCores_
	#define GET_SysMCGetNumOfCores_(fl)  CAL_CMGETAPI( "SysMCGetNumOfCores_" ) 
	#define CAL_SysMCGetNumOfCores_  SysMCGetNumOfCores_
	#define CHK_SysMCGetNumOfCores_  TRUE
	#define EXP_SysMCGetNumOfCores_  CAL_CMEXPAPI( "SysMCGetNumOfCores_" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCGetNumOfCores_
	#define EXT_SysMCGetNumOfCores_
	#define GET_SysMCGetNumOfCores_(fl)  CAL_CMGETAPI( "SysMCGetNumOfCores_" ) 
	#define CAL_SysMCGetNumOfCores_  SysMCGetNumOfCores_
	#define CHK_SysMCGetNumOfCores_  TRUE
	#define EXP_SysMCGetNumOfCores_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetNumOfCores_", (RTS_UINTPTR)SysMCGetNumOfCores_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCGetNumOfCores_
	#define EXT_SysCpuMultiCoreSysMCGetNumOfCores_
	#define GET_SysCpuMultiCoreSysMCGetNumOfCores_  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCGetNumOfCores_ pISysCpuMultiCore->ISysMCGetNumOfCores_
	#define CHK_SysCpuMultiCoreSysMCGetNumOfCores_ (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCGetNumOfCores_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCGetNumOfCores_
	#define EXT_SysMCGetNumOfCores_
	#define GET_SysMCGetNumOfCores_(fl)  CAL_CMGETAPI( "SysMCGetNumOfCores_" ) 
	#define CAL_SysMCGetNumOfCores_ pISysCpuMultiCore->ISysMCGetNumOfCores_
	#define CHK_SysMCGetNumOfCores_ (pISysCpuMultiCore != NULL)
	#define EXP_SysMCGetNumOfCores_  CAL_CMEXPAPI( "SysMCGetNumOfCores_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCGetNumOfCores_  PFSYSMCGETNUMOFCORES_ pfSysMCGetNumOfCores_;
	#define EXT_SysMCGetNumOfCores_  extern PFSYSMCGETNUMOFCORES_ pfSysMCGetNumOfCores_;
	#define GET_SysMCGetNumOfCores_(fl)  s_pfCMGetAPI2( "SysMCGetNumOfCores_", (RTS_VOID_FCTPTR *)&pfSysMCGetNumOfCores_, (fl), 0, 0)
	#define CAL_SysMCGetNumOfCores_  pfSysMCGetNumOfCores_
	#define CHK_SysMCGetNumOfCores_  (pfSysMCGetNumOfCores_ != NULL)
	#define EXP_SysMCGetNumOfCores_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetNumOfCores_", (RTS_UINTPTR)SysMCGetNumOfCores_, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCGetProcessBinding(RTS_IEC_HANDLE hProcess, CpuCoreBindingDesc *pBindingDesc);
typedef RTS_RESULT (CDECL * PFSYSMCGETPROCESSBINDING) (RTS_IEC_HANDLE hProcess, CpuCoreBindingDesc *pBindingDesc);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETPROCESSBINDING_NOTIMPLEMENTED)
	#define USE_SysMCGetProcessBinding
	#define EXT_SysMCGetProcessBinding
	#define GET_SysMCGetProcessBinding(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCGetProcessBinding(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCGetProcessBinding  FALSE
	#define EXP_SysMCGetProcessBinding  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCGetProcessBinding
	#define EXT_SysMCGetProcessBinding
	#define GET_SysMCGetProcessBinding(fl)  CAL_CMGETAPI( "SysMCGetProcessBinding" ) 
	#define CAL_SysMCGetProcessBinding  SysMCGetProcessBinding
	#define CHK_SysMCGetProcessBinding  TRUE
	#define EXP_SysMCGetProcessBinding  CAL_CMEXPAPI( "SysMCGetProcessBinding" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCGetProcessBinding
	#define EXT_SysMCGetProcessBinding
	#define GET_SysMCGetProcessBinding(fl)  CAL_CMGETAPI( "SysMCGetProcessBinding" ) 
	#define CAL_SysMCGetProcessBinding  SysMCGetProcessBinding
	#define CHK_SysMCGetProcessBinding  TRUE
	#define EXP_SysMCGetProcessBinding  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetProcessBinding", (RTS_UINTPTR)SysMCGetProcessBinding, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCGetProcessBinding
	#define EXT_SysCpuMultiCoreSysMCGetProcessBinding
	#define GET_SysCpuMultiCoreSysMCGetProcessBinding  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCGetProcessBinding pISysCpuMultiCore->ISysMCGetProcessBinding
	#define CHK_SysCpuMultiCoreSysMCGetProcessBinding (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCGetProcessBinding  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCGetProcessBinding
	#define EXT_SysMCGetProcessBinding
	#define GET_SysMCGetProcessBinding(fl)  CAL_CMGETAPI( "SysMCGetProcessBinding" ) 
	#define CAL_SysMCGetProcessBinding pISysCpuMultiCore->ISysMCGetProcessBinding
	#define CHK_SysMCGetProcessBinding (pISysCpuMultiCore != NULL)
	#define EXP_SysMCGetProcessBinding  CAL_CMEXPAPI( "SysMCGetProcessBinding" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCGetProcessBinding  PFSYSMCGETPROCESSBINDING pfSysMCGetProcessBinding;
	#define EXT_SysMCGetProcessBinding  extern PFSYSMCGETPROCESSBINDING pfSysMCGetProcessBinding;
	#define GET_SysMCGetProcessBinding(fl)  s_pfCMGetAPI2( "SysMCGetProcessBinding", (RTS_VOID_FCTPTR *)&pfSysMCGetProcessBinding, (fl), 0, 0)
	#define CAL_SysMCGetProcessBinding  pfSysMCGetProcessBinding
	#define CHK_SysMCGetProcessBinding  (pfSysMCGetProcessBinding != NULL)
	#define EXP_SysMCGetProcessBinding  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetProcessBinding", (RTS_UINTPTR)SysMCGetProcessBinding, 0, 0) 
#endif




/**
 * <description>
 * The OS implementation of SysMCGetProcessBinding
 * </description>
 */
RTS_RESULT CDECL SysMCGetProcessBinding_(RTS_IEC_HANDLE hProcess, CpuCoreBindingDesc *pBindingDesc);
typedef RTS_RESULT (CDECL * PFSYSMCGETPROCESSBINDING_) (RTS_IEC_HANDLE hProcess, CpuCoreBindingDesc *pBindingDesc);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETPROCESSBINDING__NOTIMPLEMENTED)
	#define USE_SysMCGetProcessBinding_
	#define EXT_SysMCGetProcessBinding_
	#define GET_SysMCGetProcessBinding_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCGetProcessBinding_(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCGetProcessBinding_  FALSE
	#define EXP_SysMCGetProcessBinding_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCGetProcessBinding_
	#define EXT_SysMCGetProcessBinding_
	#define GET_SysMCGetProcessBinding_(fl)  CAL_CMGETAPI( "SysMCGetProcessBinding_" ) 
	#define CAL_SysMCGetProcessBinding_  SysMCGetProcessBinding_
	#define CHK_SysMCGetProcessBinding_  TRUE
	#define EXP_SysMCGetProcessBinding_  CAL_CMEXPAPI( "SysMCGetProcessBinding_" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCGetProcessBinding_
	#define EXT_SysMCGetProcessBinding_
	#define GET_SysMCGetProcessBinding_(fl)  CAL_CMGETAPI( "SysMCGetProcessBinding_" ) 
	#define CAL_SysMCGetProcessBinding_  SysMCGetProcessBinding_
	#define CHK_SysMCGetProcessBinding_  TRUE
	#define EXP_SysMCGetProcessBinding_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetProcessBinding_", (RTS_UINTPTR)SysMCGetProcessBinding_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCGetProcessBinding_
	#define EXT_SysCpuMultiCoreSysMCGetProcessBinding_
	#define GET_SysCpuMultiCoreSysMCGetProcessBinding_  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCGetProcessBinding_ pISysCpuMultiCore->ISysMCGetProcessBinding_
	#define CHK_SysCpuMultiCoreSysMCGetProcessBinding_ (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCGetProcessBinding_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCGetProcessBinding_
	#define EXT_SysMCGetProcessBinding_
	#define GET_SysMCGetProcessBinding_(fl)  CAL_CMGETAPI( "SysMCGetProcessBinding_" ) 
	#define CAL_SysMCGetProcessBinding_ pISysCpuMultiCore->ISysMCGetProcessBinding_
	#define CHK_SysMCGetProcessBinding_ (pISysCpuMultiCore != NULL)
	#define EXP_SysMCGetProcessBinding_  CAL_CMEXPAPI( "SysMCGetProcessBinding_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCGetProcessBinding_  PFSYSMCGETPROCESSBINDING_ pfSysMCGetProcessBinding_;
	#define EXT_SysMCGetProcessBinding_  extern PFSYSMCGETPROCESSBINDING_ pfSysMCGetProcessBinding_;
	#define GET_SysMCGetProcessBinding_(fl)  s_pfCMGetAPI2( "SysMCGetProcessBinding_", (RTS_VOID_FCTPTR *)&pfSysMCGetProcessBinding_, (fl), 0, 0)
	#define CAL_SysMCGetProcessBinding_  pfSysMCGetProcessBinding_
	#define CHK_SysMCGetProcessBinding_  (pfSysMCGetProcessBinding_ != NULL)
	#define EXP_SysMCGetProcessBinding_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetProcessBinding_", (RTS_UINTPTR)SysMCGetProcessBinding_, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCGetTaskBinding(RTS_IEC_HANDLE hTask, CpuCoreBindingDesc *pBindingDesc);
typedef RTS_RESULT (CDECL * PFSYSMCGETTASKBINDING) (RTS_IEC_HANDLE hTask, CpuCoreBindingDesc *pBindingDesc);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETTASKBINDING_NOTIMPLEMENTED)
	#define USE_SysMCGetTaskBinding
	#define EXT_SysMCGetTaskBinding
	#define GET_SysMCGetTaskBinding(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCGetTaskBinding(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCGetTaskBinding  FALSE
	#define EXP_SysMCGetTaskBinding  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCGetTaskBinding
	#define EXT_SysMCGetTaskBinding
	#define GET_SysMCGetTaskBinding(fl)  CAL_CMGETAPI( "SysMCGetTaskBinding" ) 
	#define CAL_SysMCGetTaskBinding  SysMCGetTaskBinding
	#define CHK_SysMCGetTaskBinding  TRUE
	#define EXP_SysMCGetTaskBinding  CAL_CMEXPAPI( "SysMCGetTaskBinding" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCGetTaskBinding
	#define EXT_SysMCGetTaskBinding
	#define GET_SysMCGetTaskBinding(fl)  CAL_CMGETAPI( "SysMCGetTaskBinding" ) 
	#define CAL_SysMCGetTaskBinding  SysMCGetTaskBinding
	#define CHK_SysMCGetTaskBinding  TRUE
	#define EXP_SysMCGetTaskBinding  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetTaskBinding", (RTS_UINTPTR)SysMCGetTaskBinding, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCGetTaskBinding
	#define EXT_SysCpuMultiCoreSysMCGetTaskBinding
	#define GET_SysCpuMultiCoreSysMCGetTaskBinding  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCGetTaskBinding pISysCpuMultiCore->ISysMCGetTaskBinding
	#define CHK_SysCpuMultiCoreSysMCGetTaskBinding (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCGetTaskBinding  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCGetTaskBinding
	#define EXT_SysMCGetTaskBinding
	#define GET_SysMCGetTaskBinding(fl)  CAL_CMGETAPI( "SysMCGetTaskBinding" ) 
	#define CAL_SysMCGetTaskBinding pISysCpuMultiCore->ISysMCGetTaskBinding
	#define CHK_SysMCGetTaskBinding (pISysCpuMultiCore != NULL)
	#define EXP_SysMCGetTaskBinding  CAL_CMEXPAPI( "SysMCGetTaskBinding" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCGetTaskBinding  PFSYSMCGETTASKBINDING pfSysMCGetTaskBinding;
	#define EXT_SysMCGetTaskBinding  extern PFSYSMCGETTASKBINDING pfSysMCGetTaskBinding;
	#define GET_SysMCGetTaskBinding(fl)  s_pfCMGetAPI2( "SysMCGetTaskBinding", (RTS_VOID_FCTPTR *)&pfSysMCGetTaskBinding, (fl), 0, 0)
	#define CAL_SysMCGetTaskBinding  pfSysMCGetTaskBinding
	#define CHK_SysMCGetTaskBinding  (pfSysMCGetTaskBinding != NULL)
	#define EXP_SysMCGetTaskBinding  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetTaskBinding", (RTS_UINTPTR)SysMCGetTaskBinding, 0, 0) 
#endif




/**
 * <description>
 * The OS implementation of SysMCGetTaskBinding
 * </description>
 */
RTS_RESULT CDECL SysMCGetTaskBinding_(RTS_IEC_HANDLE hTask, CpuCoreBindingDesc *pBindingDesc);
typedef RTS_RESULT (CDECL * PFSYSMCGETTASKBINDING_) (RTS_IEC_HANDLE hTask, CpuCoreBindingDesc *pBindingDesc);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETTASKBINDING__NOTIMPLEMENTED)
	#define USE_SysMCGetTaskBinding_
	#define EXT_SysMCGetTaskBinding_
	#define GET_SysMCGetTaskBinding_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCGetTaskBinding_(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCGetTaskBinding_  FALSE
	#define EXP_SysMCGetTaskBinding_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCGetTaskBinding_
	#define EXT_SysMCGetTaskBinding_
	#define GET_SysMCGetTaskBinding_(fl)  CAL_CMGETAPI( "SysMCGetTaskBinding_" ) 
	#define CAL_SysMCGetTaskBinding_  SysMCGetTaskBinding_
	#define CHK_SysMCGetTaskBinding_  TRUE
	#define EXP_SysMCGetTaskBinding_  CAL_CMEXPAPI( "SysMCGetTaskBinding_" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCGetTaskBinding_
	#define EXT_SysMCGetTaskBinding_
	#define GET_SysMCGetTaskBinding_(fl)  CAL_CMGETAPI( "SysMCGetTaskBinding_" ) 
	#define CAL_SysMCGetTaskBinding_  SysMCGetTaskBinding_
	#define CHK_SysMCGetTaskBinding_  TRUE
	#define EXP_SysMCGetTaskBinding_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetTaskBinding_", (RTS_UINTPTR)SysMCGetTaskBinding_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCGetTaskBinding_
	#define EXT_SysCpuMultiCoreSysMCGetTaskBinding_
	#define GET_SysCpuMultiCoreSysMCGetTaskBinding_  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCGetTaskBinding_ pISysCpuMultiCore->ISysMCGetTaskBinding_
	#define CHK_SysCpuMultiCoreSysMCGetTaskBinding_ (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCGetTaskBinding_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCGetTaskBinding_
	#define EXT_SysMCGetTaskBinding_
	#define GET_SysMCGetTaskBinding_(fl)  CAL_CMGETAPI( "SysMCGetTaskBinding_" ) 
	#define CAL_SysMCGetTaskBinding_ pISysCpuMultiCore->ISysMCGetTaskBinding_
	#define CHK_SysMCGetTaskBinding_ (pISysCpuMultiCore != NULL)
	#define EXP_SysMCGetTaskBinding_  CAL_CMEXPAPI( "SysMCGetTaskBinding_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCGetTaskBinding_  PFSYSMCGETTASKBINDING_ pfSysMCGetTaskBinding_;
	#define EXT_SysMCGetTaskBinding_  extern PFSYSMCGETTASKBINDING_ pfSysMCGetTaskBinding_;
	#define GET_SysMCGetTaskBinding_(fl)  s_pfCMGetAPI2( "SysMCGetTaskBinding_", (RTS_VOID_FCTPTR *)&pfSysMCGetTaskBinding_, (fl), 0, 0)
	#define CAL_SysMCGetTaskBinding_  pfSysMCGetTaskBinding_
	#define CHK_SysMCGetTaskBinding_  (pfSysMCGetTaskBinding_ != NULL)
	#define EXP_SysMCGetTaskBinding_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetTaskBinding_", (RTS_UINTPTR)SysMCGetTaskBinding_, 0, 0) 
#endif




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
RTS_UI32 CDECL SysMCGetCurrentCoreID(RTS_RESULT* pResult);
typedef RTS_UI32 (CDECL * PFSYSMCGETCURRENTCOREID) (RTS_RESULT* pResult);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETCURRENTCOREID_NOTIMPLEMENTED)
	#define USE_SysMCGetCurrentCoreID
	#define EXT_SysMCGetCurrentCoreID
	#define GET_SysMCGetCurrentCoreID(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCGetCurrentCoreID(p0)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_SysMCGetCurrentCoreID  FALSE
	#define EXP_SysMCGetCurrentCoreID  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCGetCurrentCoreID
	#define EXT_SysMCGetCurrentCoreID
	#define GET_SysMCGetCurrentCoreID(fl)  CAL_CMGETAPI( "SysMCGetCurrentCoreID" ) 
	#define CAL_SysMCGetCurrentCoreID  SysMCGetCurrentCoreID
	#define CHK_SysMCGetCurrentCoreID  TRUE
	#define EXP_SysMCGetCurrentCoreID  CAL_CMEXPAPI( "SysMCGetCurrentCoreID" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCGetCurrentCoreID
	#define EXT_SysMCGetCurrentCoreID
	#define GET_SysMCGetCurrentCoreID(fl)  CAL_CMGETAPI( "SysMCGetCurrentCoreID" ) 
	#define CAL_SysMCGetCurrentCoreID  SysMCGetCurrentCoreID
	#define CHK_SysMCGetCurrentCoreID  TRUE
	#define EXP_SysMCGetCurrentCoreID  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetCurrentCoreID", (RTS_UINTPTR)SysMCGetCurrentCoreID, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCGetCurrentCoreID
	#define EXT_SysCpuMultiCoreSysMCGetCurrentCoreID
	#define GET_SysCpuMultiCoreSysMCGetCurrentCoreID  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCGetCurrentCoreID pISysCpuMultiCore->ISysMCGetCurrentCoreID
	#define CHK_SysCpuMultiCoreSysMCGetCurrentCoreID (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCGetCurrentCoreID  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCGetCurrentCoreID
	#define EXT_SysMCGetCurrentCoreID
	#define GET_SysMCGetCurrentCoreID(fl)  CAL_CMGETAPI( "SysMCGetCurrentCoreID" ) 
	#define CAL_SysMCGetCurrentCoreID pISysCpuMultiCore->ISysMCGetCurrentCoreID
	#define CHK_SysMCGetCurrentCoreID (pISysCpuMultiCore != NULL)
	#define EXP_SysMCGetCurrentCoreID  CAL_CMEXPAPI( "SysMCGetCurrentCoreID" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCGetCurrentCoreID  PFSYSMCGETCURRENTCOREID pfSysMCGetCurrentCoreID;
	#define EXT_SysMCGetCurrentCoreID  extern PFSYSMCGETCURRENTCOREID pfSysMCGetCurrentCoreID;
	#define GET_SysMCGetCurrentCoreID(fl)  s_pfCMGetAPI2( "SysMCGetCurrentCoreID", (RTS_VOID_FCTPTR *)&pfSysMCGetCurrentCoreID, (fl), 0, 0)
	#define CAL_SysMCGetCurrentCoreID  pfSysMCGetCurrentCoreID
	#define CHK_SysMCGetCurrentCoreID  (pfSysMCGetCurrentCoreID != NULL)
	#define EXP_SysMCGetCurrentCoreID  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetCurrentCoreID", (RTS_UINTPTR)SysMCGetCurrentCoreID, 0, 0) 
#endif




/**
 * <description>
 * The OS implementation of SysMCGetCurrentCoreID
 * </description>
 */
RTS_UI32 CDECL SysMCGetCurrentCoreID_(RTS_RESULT* pResult);
typedef RTS_UI32 (CDECL * PFSYSMCGETCURRENTCOREID_) (RTS_RESULT* pResult);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETCURRENTCOREID__NOTIMPLEMENTED)
	#define USE_SysMCGetCurrentCoreID_
	#define EXT_SysMCGetCurrentCoreID_
	#define GET_SysMCGetCurrentCoreID_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCGetCurrentCoreID_(p0)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_SysMCGetCurrentCoreID_  FALSE
	#define EXP_SysMCGetCurrentCoreID_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCGetCurrentCoreID_
	#define EXT_SysMCGetCurrentCoreID_
	#define GET_SysMCGetCurrentCoreID_(fl)  CAL_CMGETAPI( "SysMCGetCurrentCoreID_" ) 
	#define CAL_SysMCGetCurrentCoreID_  SysMCGetCurrentCoreID_
	#define CHK_SysMCGetCurrentCoreID_  TRUE
	#define EXP_SysMCGetCurrentCoreID_  CAL_CMEXPAPI( "SysMCGetCurrentCoreID_" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCGetCurrentCoreID_
	#define EXT_SysMCGetCurrentCoreID_
	#define GET_SysMCGetCurrentCoreID_(fl)  CAL_CMGETAPI( "SysMCGetCurrentCoreID_" ) 
	#define CAL_SysMCGetCurrentCoreID_  SysMCGetCurrentCoreID_
	#define CHK_SysMCGetCurrentCoreID_  TRUE
	#define EXP_SysMCGetCurrentCoreID_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetCurrentCoreID_", (RTS_UINTPTR)SysMCGetCurrentCoreID_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCGetCurrentCoreID_
	#define EXT_SysCpuMultiCoreSysMCGetCurrentCoreID_
	#define GET_SysCpuMultiCoreSysMCGetCurrentCoreID_  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCGetCurrentCoreID_ pISysCpuMultiCore->ISysMCGetCurrentCoreID_
	#define CHK_SysCpuMultiCoreSysMCGetCurrentCoreID_ (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCGetCurrentCoreID_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCGetCurrentCoreID_
	#define EXT_SysMCGetCurrentCoreID_
	#define GET_SysMCGetCurrentCoreID_(fl)  CAL_CMGETAPI( "SysMCGetCurrentCoreID_" ) 
	#define CAL_SysMCGetCurrentCoreID_ pISysCpuMultiCore->ISysMCGetCurrentCoreID_
	#define CHK_SysMCGetCurrentCoreID_ (pISysCpuMultiCore != NULL)
	#define EXP_SysMCGetCurrentCoreID_  CAL_CMEXPAPI( "SysMCGetCurrentCoreID_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCGetCurrentCoreID_  PFSYSMCGETCURRENTCOREID_ pfSysMCGetCurrentCoreID_;
	#define EXT_SysMCGetCurrentCoreID_  extern PFSYSMCGETCURRENTCOREID_ pfSysMCGetCurrentCoreID_;
	#define GET_SysMCGetCurrentCoreID_(fl)  s_pfCMGetAPI2( "SysMCGetCurrentCoreID_", (RTS_VOID_FCTPTR *)&pfSysMCGetCurrentCoreID_, (fl), 0, 0)
	#define CAL_SysMCGetCurrentCoreID_  pfSysMCGetCurrentCoreID_
	#define CHK_SysMCGetCurrentCoreID_  (pfSysMCGetCurrentCoreID_ != NULL)
	#define EXP_SysMCGetCurrentCoreID_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetCurrentCoreID_", (RTS_UINTPTR)SysMCGetCurrentCoreID_, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSYSMCADDTASKGROUP ISysMCAddTaskGroup;
 	PFSYSMCREMOVETASKGROUP ISysMCRemoveTaskGroup;
 	PFSYSMCFINDTASKGROUP ISysMCFindTaskGroup;
 	PFSYSMCGETFIRSTTASKGROUP ISysMCGetFirstTaskGroup;
 	PFSYSMCGETNEXTTASKGROUP ISysMCGetNextTaskGroup;
 	PFSYSMCGETTASKGROUPNAME ISysMCGetTaskGroupName;
 	PFSYSMCGETTASKGROUPBINDING ISysMCGetTaskGroupBinding;
 	PFSYSMCGETTASKGROUPOPTIONS ISysMCGetTaskGroupOptions;
 	PFSYSMCSETTASKGROUPBINDING ISysMCSetTaskGroupBinding;
 	PFSYSMCADDTOTASKGROUP ISysMCAddToTaskGroup;
 	PFSYSMCREMOVEFROMTASKGROUP ISysMCRemoveFromTaskGroup;
 	PFSYSMCBEGINTASKGROUPCONF ISysMCBeginTaskGroupConf;
 	PFSYSMCENDTASKGROUPCONF ISysMCEndTaskGroupConf;
 	PFSYSMCBDALLOC ISysMCBDAlloc;
 	PFSYSMCBDFREE ISysMCBDFree;
 	PFSYSMCBDZERO ISysMCBDZero;
 	PFSYSMCBDSET ISysMCBDSet;
 	PFSYSMCBDRESET ISysMCBDReset;
 	PFSYSMCBDISSET ISysMCBDIsSet;
 	PFSYSMCBDCOUNT ISysMCBDCount;
 	PFSYSMCBDGETFIRSTID ISysMCBDGetFirstID;
 	PFSYSMCBDGETNEXTID ISysMCBDGetNextID;
 	PFSYSMCBINDPROCESS ISysMCBindProcess;
 	PFSYSMCBINDPROCESS_ ISysMCBindProcess_;
 	PFSYSMCBINDTASK ISysMCBindTask;
 	PFSYSMCBINDTASK_ ISysMCBindTask_;
 	PFSYSMCUNBINDPROCESS ISysMCUnbindProcess;
 	PFSYSMCUNBINDPROCESS_ ISysMCUnbindProcess_;
 	PFSYSMCUNBINDTASK ISysMCUnbindTask;
 	PFSYSMCUNBINDTASK_ ISysMCUnbindTask_;
 	PFSYSMCGETLOAD ISysMCGetLoad;
 	PFSYSMCGETLOAD_ ISysMCGetLoad_;
 	PFSYSMCGETNUMOFCORES ISysMCGetNumOfCores;
 	PFSYSMCGETNUMOFCORES_ ISysMCGetNumOfCores_;
 	PFSYSMCGETPROCESSBINDING ISysMCGetProcessBinding;
 	PFSYSMCGETPROCESSBINDING_ ISysMCGetProcessBinding_;
 	PFSYSMCGETTASKBINDING ISysMCGetTaskBinding;
 	PFSYSMCGETTASKBINDING_ ISysMCGetTaskBinding_;
 	PFSYSMCGETCURRENTCOREID ISysMCGetCurrentCoreID;
 	PFSYSMCGETCURRENTCOREID_ ISysMCGetCurrentCoreID_;
 } ISysCpuMultiCore_C;

#ifdef CPLUSPLUS
class ISysCpuMultiCore : public IBase
{
	public:
		virtual RTS_HANDLE CDECL ISysMCAddTaskGroup(char *pszTaskGroup, RTS_UI32 taskGroupOptions, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISysMCRemoveTaskGroup(RTS_HANDLE hTaskGroup) =0;
		virtual RTS_HANDLE CDECL ISysMCFindTaskGroup(char *pszTaskGroup, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL ISysMCGetFirstTaskGroup(RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL ISysMCGetNextTaskGroup(RTS_HANDLE hPrevTaskGroup, RTS_RESULT *pResult) =0;
		virtual char* CDECL ISysMCGetTaskGroupName(RTS_HANDLE hTaskGroup, RTS_RESULT *pResult) =0;
		virtual CpuCoreBindingDesc* CDECL ISysMCGetTaskGroupBinding(RTS_HANDLE hTaskGroup, RTS_RESULT *pResult) =0;
		virtual RTS_UI32 CDECL ISysMCGetTaskGroupOptions(RTS_HANDLE hTaskGroup, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISysMCSetTaskGroupBinding(RTS_HANDLE hTaskGroup, CpuCoreBindingDesc *pBindingDesc) =0;
		virtual RTS_RESULT CDECL ISysMCAddToTaskGroup(RTS_HANDLE hSysTask, RTS_HANDLE hTaskGroup) =0;
		virtual RTS_RESULT CDECL ISysMCRemoveFromTaskGroup(RTS_HANDLE hSysTask, RTS_HANDLE hTaskGroup) =0;
		virtual RTS_RESULT CDECL ISysMCBeginTaskGroupConf(RTS_HANDLE hTaskGroup) =0;
		virtual RTS_RESULT CDECL ISysMCEndTaskGroupConf(RTS_HANDLE hTaskGroup) =0;
		virtual CpuCoreBindingDesc * CDECL ISysMCBDAlloc(RTS_RESULT* pResult) =0;
		virtual RTS_RESULT CDECL ISysMCBDFree(CpuCoreBindingDesc *pBindingDesc) =0;
		virtual RTS_RESULT CDECL ISysMCBDZero(CpuCoreBindingDesc *pBindingDesc) =0;
		virtual RTS_RESULT CDECL ISysMCBDSet(CpuCoreBindingDesc *pBindingDesc, RTS_UI32 uCoreId) =0;
		virtual RTS_RESULT CDECL ISysMCBDReset(CpuCoreBindingDesc *pBindingDesc, RTS_UI32 uCoreId) =0;
		virtual RTS_RESULT CDECL ISysMCBDIsSet(CpuCoreBindingDesc *pBindingDesc, RTS_UI32 uCoreId) =0;
		virtual RTS_UI32 CDECL ISysMCBDCount(CpuCoreBindingDesc *pBindingDesc, RTS_RESULT* pResult) =0;
		virtual RTS_UI32 CDECL ISysMCBDGetFirstID(CpuCoreBindingDesc *pBindingDesc, RTS_RESULT* pResult) =0;
		virtual RTS_UI32 CDECL ISysMCBDGetNextID(CpuCoreBindingDesc *pBindingDesc, RTS_UI32 uPrevCoreID, RTS_RESULT* pResult) =0;
		virtual RTS_RESULT CDECL ISysMCBindProcess(CpuCoreBindingDesc *pBindingDesc, RTS_IEC_HANDLE hProcess) =0;
		virtual RTS_RESULT CDECL ISysMCBindProcess_(CpuCoreBindingDesc *pBindingDesc, RTS_IEC_HANDLE hProcess) =0;
		virtual RTS_RESULT CDECL ISysMCBindTask(CpuCoreBindingDesc *pBindingDesc, RTS_IEC_HANDLE hTask) =0;
		virtual RTS_RESULT CDECL ISysMCBindTask_(CpuCoreBindingDesc *pBindingDesc, RTS_IEC_HANDLE hTask) =0;
		virtual RTS_RESULT CDECL ISysMCUnbindProcess(RTS_IEC_HANDLE hProcess) =0;
		virtual RTS_RESULT CDECL ISysMCUnbindProcess_(RTS_IEC_HANDLE hProcess) =0;
		virtual RTS_RESULT CDECL ISysMCUnbindTask(RTS_IEC_HANDLE hTask) =0;
		virtual RTS_RESULT CDECL ISysMCUnbindTask_(RTS_IEC_HANDLE hTask) =0;
		virtual RTS_RESULT CDECL ISysMCGetLoad(RTS_UI32 uCoreID, RTS_UI8 *pPercent) =0;
		virtual RTS_RESULT CDECL ISysMCGetLoad_(RTS_UI32 uCoreID, RTS_UI8 *pPercent) =0;
		virtual RTS_UI32 CDECL ISysMCGetNumOfCores(RTS_RESULT* pResult) =0;
		virtual RTS_UI32 CDECL ISysMCGetNumOfCores_(RTS_RESULT* pResult) =0;
		virtual RTS_RESULT CDECL ISysMCGetProcessBinding(RTS_IEC_HANDLE hProcess, CpuCoreBindingDesc *pBindingDesc) =0;
		virtual RTS_RESULT CDECL ISysMCGetProcessBinding_(RTS_IEC_HANDLE hProcess, CpuCoreBindingDesc *pBindingDesc) =0;
		virtual RTS_RESULT CDECL ISysMCGetTaskBinding(RTS_IEC_HANDLE hTask, CpuCoreBindingDesc *pBindingDesc) =0;
		virtual RTS_RESULT CDECL ISysMCGetTaskBinding_(RTS_IEC_HANDLE hTask, CpuCoreBindingDesc *pBindingDesc) =0;
		virtual RTS_UI32 CDECL ISysMCGetCurrentCoreID(RTS_RESULT* pResult) =0;
		virtual RTS_UI32 CDECL ISysMCGetCurrentCoreID_(RTS_RESULT* pResult) =0;
};
	#ifndef ITF_SysCpuMultiCore
		#define ITF_SysCpuMultiCore static ISysCpuMultiCore *pISysCpuMultiCore = NULL;
	#endif
	#define EXTITF_SysCpuMultiCore
#else	/*CPLUSPLUS*/
	typedef ISysCpuMultiCore_C		ISysCpuMultiCore;
	#ifndef ITF_SysCpuMultiCore
		#define ITF_SysCpuMultiCore
	#endif
	#define EXTITF_SysCpuMultiCore
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSCPUMULTICOREITF_H_*/
