/**
 * <interfacename>CmpMgr</interfacename>
 * <description> 
 *	<p>Interface of the component manager</p>
 *	<p>The component manager component is the central component of the runtime system.
 *	The component manager is responsible for:</p>
 *	<ul>
 *		<li>startup and shutdown of the runtime system</li>
 *		<li>loading and unloading all components</li>
 *		<li>intializing all components</li>
 *		<li>linking all functions, including the external IEC library functions</li>
 *		<li>checking the consistency of calling a function (matching function prototypes)</li>
 *	</ul>
 *	<p>The list of components that should be loaded can be specified in different ways.</p>
 *	<p>If the components are linked static, there are two different ways to specify the component list:</p>
 *	<ul>
 *		<li>Static list: The list of static loaded components can be specified as a calling option for the CMInit()
 *		interface method. The name of the component on the entry funtion of each component must be specified.
 *		See the description of the CMInit() method for detailed information.</li>
 *		<li>Settings: The settings component has a settings interface, where the component list can be specified.
 *		Here only the component name must be specified. In this case, the function MainLoadComponent() must be
 *		impleemnted in the Main module and here all static linked components must be added to the list. The advantage
 *		of this method is that in the settings you can specify, which static component can be loaded or not. This
 *		is quite flexible.</li>
 *	</ul>
 *	<p>For dynamically linked components, the component list can only be specified in the settings component.</p>
 *	<p>External IEC library functions are managed by the component manager too. Each interface have to specify,
 *	if it could be used for IEC code or not in the m4 Interface definition.</p>
 *
 *	<p>An additional feature is the possibility to use all components with a C++ interface. Here you can implement
 *	your own component in C++ and can use all other runtime components object oriented with a C++ interface.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CM')

REF_ITF(`CmpMemPoolItf.m4')
REF_ITF(`CmpEventMgrItf.m4')
REF_ITF(`CMUtilsItf.m4')
REF_ITF(`SysSemItf.m4')
REF_ITF(`SysIntItf.m4')

/**
 * <category>Compiler switch</category>
 * <description>The way components are linked together can be specified by the following compiler switches.
 *	<p>If nothing is specified, DYNAMIC_LINK is used by default.</p>
 *	<p>Link examples:</p>
 *	<ul>
 *		<li>Static linked and closed runtime system (e.g. embedded):
 *			STATIC_LINK must be specified</li>
 *		<li>Static linked runtime system, that can be extended via separate, dynamically linkable components:
 *			MIXED_LINK must be specified for the runtime system.
 *			Nothing must be specified in the external component.</li>
 *		<li>Complete dynamically linked runtime system (each component is a separate loadable module):
 *			-- Nothing must be specified in each component.</li>
 *		<li>Static linked runtime system, that can be extended via separate, dynamically linkable components
 *			and all interface functions should be overloadable:
 *			DYNAMIC_LINK must be specified for the runtime system.
 *			-- Nothing must be specified in the external component.</li>
 *		<li>C++ runtime system: 
 *			CPLUSPLUS must be specified always in each component, that is used in a C++ runtime system.
 *			This is independant, if the kernel or a separate component is linked (static or dynamically linked!</li>
 *	</ul>
 * </description>
 * <element name="STATIC_LINK">All components are linked statically to the component manager during compile time.
 *			All components call each other via C-function calls.</element>
 * <element name="MIXED_LINK">All components are linked static, but can be extended by dynamically linked components.
 *			All static components call each other via C-function. All dynamically linked components are
 *			called and call the kernel components via function pointers.</element>
 * <element name="DYNAMIC_LINK">[Default] All components exists as separate compiled modules. So this modules can be loaded dynamically.
 *			All components call each other via function pointers.
 *			NOTE:
 *			If DYNAMIC_LINK is specified explicitly in a runtime system that is linked static,
 *			all component functions	(also the kernel components) are called via function pointers!</element>
 * <element name="CPLUSPLUS">All components are linked together via C++ classes.
 *			All components call each other via C++ method calls.
 *			Internally, the components calls itself	via C-function calls.</element>
 */


/**
 * <category>Compiler switch</category>
 * <description>
 *	Compiler switches to check if the alignment between the DeviceDescription setting "pack-mode" of the CODESYS compiler 
 *	and the C-compiler standard pack mode match together.
 * </description>
 * <element name="EXTERNAL_LIB_PACKMODE">Define the alignment of the CODESYS Compiler:
 *			2=2Byte alignment ("pack-mode"=2)
 *			4=4Byte alignment ("pack-mode"=4)
 *			8=8Byte alignment [default] ("pack-mode"=8)</element>
 */
#ifndef EXTERNAL_LIB_PACKMODE
	#define EXTERNAL_LIB_PACKMODE	8
#endif


/**
 * <category>Compiler switch</category>
 * <description>
 *	Compiler switches to enable/disable single features in the component.
 * </description>
 * <element name="CM_SYSTARGET_DISABLE_OVERLOADABLE_FUNCTIONS">Switch to disable the possibility to overload the SysTarget functions</element>
 * <element name="CM_DISABLE_API_SIGNATURE_CHECK">Switch to disable the signature check of all api functions</element>
 * <element name="CM_DISABLE_API_VERSION_CHECK">Switch to disable the version check of all api functions</element>
 * <element name="CM_NO_EXIT">Switch to disable definite exit or shutdown process of the runtime system</element>
 * <element name="CM_NO_DYNAMIC_COMPONENTS">Switch to disable dynamic loadable components</element>
 */
#if defined(RTS_COMPACT) || defined(RTS_SIL2)
	#define CM_NO_EXIT
	#define CM_NO_DYNAMIC_COMPONENTS
#endif



/**
 * <category>Static defines</category>
 * <description>Maximum length of component name</description>
 */
#define MAX_COMPONENT_NAME						32

/**
 * <category>Static defines</category>
 * <description>Maximum length of api function name</description>
 */
#define MAX_API_NAME							64


/**
 * <category>Static defines</category>
 * <description>Length of component list that is allocated static</description>
 */
#ifndef CM_NUM_OF_STATIC_COMPONENTS
	#if defined(CPLUSPLUS)
		#define CM_NUM_OF_STATIC_COMPONENTS		110
	#else
		#define CM_NUM_OF_STATIC_COMPONENTS		40
	#endif
#endif

/**
 * <category>Static defines</category>
 * <description>Length of class list that is allocated static</description>
 */
#ifndef CM_NUM_OF_STATIC_CLASSES
	#ifdef CPLUSPLUS
		#define CM_NUM_OF_STATIC_CLASSES		CM_NUM_OF_STATIC_COMPONENTS
	#else		
		#define CM_NUM_OF_STATIC_CLASSES		5
	#endif
#endif

/**
 * <category>Static defines</category>
 * <description>Length of instance list that is allocated static</description>
 */
#ifndef CM_NUM_OF_STATIC_INSTANCES
	#ifdef CPLUSPLUS
		#define CM_NUM_OF_STATIC_INSTANCES		CM_NUM_OF_STATIC_COMPONENTS
	#else		
		#define CM_NUM_OF_STATIC_INSTANCES		5
	#endif
#endif

/**
 * <category>Static defines</category>
 * <description>
 *	Significant mask to check different versions of an api function. If the significant
 *	parts of the version don't match, the api versions don't match!
 * </description>
 */
#ifndef CM_API_VERSION_CHECK_MASK
	#define CM_API_VERSION_CHECK_MASK				UINT32_C(0xFF000000)
#endif

/**
 * <category>Static defines</category>
 * <description>
 *	Specifies the minimum supported version of all api functions.
 * </description>
 */
#ifndef CM_API_VERSION_CHECK_MINIMUM
	#define CM_API_VERSION_CHECK_MINIMUM			UINT32_C(0x00000000)
#endif


/**
 * <category>Static defines</category>
 * <description>
 *	Significant mask to check different versions of an external library api function. If the significant
 *	parts of the version don't match, the api versions don't match!
 * </description>
 */
#ifndef CM_EXTLIB_API_VERSION_CHECK_MASK
	#define CM_EXTLIB_API_VERSION_CHECK_MASK		UINT32_C(0xFF000000)
#endif

/**
 * <category>Static defines</category>
 * <description>
 *	Specifies the minimum supported version of all external library api functions.
 * </description>
 */
#ifndef CM_EXTLIB_API_VERSION_CHECK_MINIMUM
	#define CM_EXTLIB_API_VERSION_CHECK_MINIMUM		UINT32_C(0x00000000)
#endif



/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting to read in list of components.
 *	Component list must be indexed, started with 0 or 1, e.g.:
 *	Component.0=[Component Name]	or
 *	Component.1=[Component Name]
 * </description>
 */
#define CMPMGR_KEY_STRING_COMPONENT_NAME		"Component"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to enable/disable the possibility to overload single interface functions of a component.
 *	ATTENTION: The component, which interface function should be overloaded, must be loaded _before_ the component
 *			   that overloads the function!
 * </description>
 */
#define CMPMGR_KEY_INT_OVERLOADABLE_FUNCTIONS							"OverloadableFunctions"
#ifndef CMPMGR_VALUE_INT_OVERLOADABLE_FUNCTIONS_DEFAULT
	#define CMPMGR_VALUE_INT_OVERLOADABLE_FUNCTIONS_DEFAULT				0
#endif

/**
 * <category>Static defines</category>
 * <description>OBSOLETE: Only for backward compatibility</description>
 */
#ifdef CMPMGR_KEY_INT_OVERLOADABLE_FUNCTIONS_DEFAULT
	#undef CMPMGR_VALUE_INT_OVERLOADABLE_FUNCTIONS_DEFAULT
	#define CMPMGR_VALUE_INT_OVERLOADABLE_FUNCTIONS_DEFAULT				CMPMGR_KEY_INT_OVERLOADABLE_FUNCTIONS_DEFAULT
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to define the minimal interval (in ms) in which the function CMCallExtraCommCycleHook() calls on
 *  non-multitaskling systems the CommCycleHook additionally.
 * </description>
 */
#define CMPMGR_KEY_INT_MINIMAL_COMM_CYCLE_HOOK_INTERVAL					"MinimalCommCycleHookInterval"
#ifndef CMPMGR_VALUE_INT_MINIMAL_COMM_CYCLE_HOOK_INTERVAL_DEFAULT
	#define CMPMGR_VALUE_INT_MINIMAL_COMM_CYCLE_HOOK_INTERVAL_DEFAULT	250
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to define the sleep time (in ms) after each comm cycle on WinCE targets. 
 * </description>
 */
#define CMPMGR_KEY_INT_WINCE_COMM_CYCLE_INTERVAL						"WinCE.CommCycleInterval"
#ifndef CMPMGR_VALUE_INT_WINCE_COMM_CYCLE_INTERVAL_DEFAULT
	#define CMPMGR_VALUE_INT_WINCE_COMM_CYCLE_INTERVAL_DEFAULT			9
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to define Windows CE thread priority of the comm cycle thread on WinCE targets. 
 * Important for communication performance
 * </description>
 */
#define CMPMGR_KEY_INT_WINCE_COMM_CYCLE_THREAD_PRIORITY					"WinCE.CommCycleThreadPriority"
#ifndef CMPMGR_KEY_INT_WINCE_COMM_CYCLE_THREAD_PRIORITY_DEFAULT
	#define CMPMGR_KEY_INT_WINCE_COMM_CYCLE_THREAD_PRIORITY_DEFAULT		250
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to define if the PLC window is hided after startup.
 * </description>
 */
#define CMPMGR_KEY_INT_WINDOWHIDED					"WindowHided"
#ifndef CMPMGR_KEY_INT_WINDOWHIDED_DEFAULT
	#define CMPMGR_KEY_INT_WINDOWHIDED_DEFAULT		0
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to switch on/off the possibility to disable single operations by the corresponding event EVT_CmpMgr_DisableOperation.
 *	DisablingOperations=1: Operations can be disabled
 *	DisablingOperations=0: Operations cannot be disabled
 * </description>
 */
#define CMPMGR_KEY_INT_DISABLING_OPERATIONS								"DisablingOperations"
#ifndef CMPMGR_VALUE_INT_DISABLING_OPERATIONS_DEFAULT
	#define CMPMGR_VALUE_INT_DISABLING_OPERATIONS_DEFAULT				1
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to specify, for which component the profiler is active. See category "Profiler" for details.
 * </description>
 */
#define CMPMGR_KEY_INT_PROFILER_COMPONENTID								"Profiler.ComponentID"
#ifndef CMPMGR_VALUE_INT_PROFILER_COMPONENTID_DEFAULT					
	#define CMPMGR_VALUE_INT_PROFILER_COMPONENTID_DEFAULT				0
#endif


/**
 * <category>Event parameter</category>
 * <element name="pdummy" type="IN">dummy</element>
 */
typedef struct
{
	void* pdummy;
} EVTPARAM_CmpMgr_Shutdown;
#define EVTPARAMID_CmpMgr_Shutdown	0x0001
#define EVTVERSION_CmpMgr_Shutdown	0x0001

/**
 * <category>Event parameter</category>
 * <element name="cmpId" type="IN">ComponentID of the component, which operation should be disabled</element>
 * <element name="ulOperation" type="IN">Operation that can be disabled. See category "Operations" in Itf.h file of the corresponding component for details.</element>
 * <element name="cmpIdDisabled" type="IN">ComponentID of the source, which disabled the operation</element>
 * <element name="bDisable" type="IN">Must be set to 1 to disable the operation, else: do nothing and remain the value as it is!</element>
 */
typedef struct
{
	CMPID cmpId;
	RTS_UI32 ulOperation;
	CMPID cmpIdDisabled;
	RTS_I32 bDisable;
} EVTPARAM_CmpMgr_DisableOperation;
#define EVTPARAMID_CmpMgr_DisableOperation	0x0002
#define EVTVERSION_CmpMgr_DisableOperation	0x0001

/**
 * <category>Event parameter</category>
 * <element name="bLastCall" type="IN">This value will be != 0 for the last call of this event, otherwise 0.</element>
 * <element name="bFurtherCallNecessary" type="OUT">Callees of the event can set this value to <c>!= 0</c> if they expect a further call of
 *	the same event with inbetween comm cycle calls. It is not expected that a callee sets this value to <c>0</c>!</element>
 */
typedef struct
{
	RTS_I32 bLastCall;
	RTS_I32 bFurtherCallNecessary;
} EVTPARAM_CmpMgr_PrepareExitCommProcessing;
#define EVTPARAMID_CmpMgr_PrepareExitCommProcessing	0x0003
#define EVTVERSION_CmpMgr_PrepareExitCommProcessing	0x0001

/**
 * <category>Event parameter</category>
 * <element name="ulLicenseID" type="IN">License ID requested.</element>
 * <element name="ulLicenseValue" type="IN">Value of the license.</element>
 */
typedef struct
{
	RTS_IEC_UDINT ulLicenseID;
	RTS_IEC_UDINT ulLicenseValue;
} EVTPARAM_CmpMgr_LicenseRequest;
#define EVTPARAMID_CmpMgr_LicenseRequest			0x0004
#define EVTVERSION_CmpMgr_LicenseRequest					0x0001



/**
 * <category>Events</category>
 * <description>Event is sent before shutdown of the runtime system</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpMgr_Shutdown</param>
 */
#define EVT_CmpMgr_PrepareShutdown				MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Events</category>
 * <description>Event is sent before exit the communication servers during shutdown</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpMgr_Shutdown</param>
 */
#define EVT_CmpMgr_PrepareExitComm				MAKE_EVENTID(EVTCLASS_INFO, 2)

/**
 * <category>Events</category>
 * <description>Event is sent before exit all tasks during shutdown</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpMgr_Shutdown</param>
 */
#define EVT_CmpMgr_PrepareExitTasks				MAKE_EVENTID(EVTCLASS_INFO, 3)

/**
 * <category>Events</category>
 * <description>Event is sent before exit of the runtime system during shutdown</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpMgr_Shutdown</param>
 */
#define EVT_CmpMgr_Exit3						MAKE_EVENTID(EVTCLASS_INFO, 4)

/**
 * <category>Events</category>
 * <description>Event is sent before exit of the runtime system during shutdown</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpMgr_Shutdown</param>
 */
#define EVT_CmpMgr_PrepareExit					MAKE_EVENTID(EVTCLASS_INFO, 5)

/**
 * <category>Events</category>
 * <description>Event is sent before exit of the runtime system during shutdown</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpMgr_Shutdown</param>
 */
#define EVT_CmpMgr_Exit2						MAKE_EVENTID(EVTCLASS_INFO, 5)

/**
 * <category>Events</category>
 * <description>Event is sent to disable operations. Each operation is defined in the corresponding Itf.h file of the component, which is specified by its ComponentID</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpMgr_DisableOperation</param>
 */
#define EVT_CmpMgr_DisableOperation				MAKE_EVENTID(EVTCLASS_INFO, 6)

 /**
 * <category>Events</category>
 * <description>Event is sent after <see>EVT_CmpMgr_PrepareExitComm</see> and can be used if comm cycles are necessary to perform some kind
 *	of shutdown operation. The event may be called several times if one of the callees requests further calls. This can happen if the shutdown operation
 *	takes some time.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpMgr_Shutdown</param>
 */
#define EVT_CmpMgr_PrepareExitCommProcessing	MAKE_EVENTID(EVTCLASS_INFO, 7)

 /**
 * <category>Events</category>
 * <description>Event to get informed when a license was requrested. Only for informational use. 
 * No result of the event will be evaulated.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpMgr_LicenseRequest</param>
 */
#define EVT_CmpMgr_LicenseRequest				MAKE_EVENTID(EVTCLASS_INFO, 8)

/**
 * <category>CMInit options</category>
 * <element name="RTS_CMINIT_OPTION_SETTINGSFILEISOPTIONAL" type="IN">Specifies, if the Settingsfile is only used optional</element> 
 * <element name="RTS_CMINIT_OPTION_DONTCALLINITHOOKS" type="IN">If this option is set, the CMInit sequence is stopped right after CH_INIT hook.
 *	To finish the startup sequence, you have to call CMInitEnd() afterwards.
 *	This can be used, if you have to do things first before before all other components, but you need here the runtime system components.
 * </element> 
 */
#define RTS_CMINIT_OPTION_SETTINGSFILEISOPTIONAL			UINT32_C(0x00000001)
#define RTS_CMINIT_OPTION_DONTCALLINITHOOKS					UINT32_C(0x00000002)

/**
 * <category>ComponentType</category>
 * <description>
 *	A component can only be a member of type CMPTYPE_STANDARD or type CMPTYPE_SAFETY.
 *	To separate the components in detail, we use the types CMPTYPE_STATIC, CMPTYPE_DYNAMIC, CMPTYPE_SYSTEM or CMPTYPE_IEC.
 * </description>
 * <element name="CMPTYPE_STANDARD" type="IN">Standard component category</element> 
 * <element name="CMPTYPE_SAFETY" type="IN">Safety component category</element> 
 * <element name="CMPTYPE_ALL" type="IN">Can be used to select all components. Only a mask to select STANDARD and SAFETY.</element> 
 * <element name="CMPTYPE_STATIC" type="IN">Static linked component</element> 
 * <element name="CMPTYPE_DYNAMIC" type="IN">Dynamically linked component</element> 
 * <element name="CMPTYPE_SYSTEM" type="IN">System component</element> 
 * <element name="CMPTYPE_IEC" type="IN">IEC component (IEC code is registered as a component)</element> 
 * <element name="CMPTYPE_APP_CMODULE" type="IN">Application C-Module component</element> 
 */
#define CMPTYPE_STANDARD		UINT16_C(0x0100)
#define CMPTYPE_SAFETY			UINT16_C(0x0200)
#define CMPTYPE_ALL				(CMPTYPE_STANDARD | CMPTYPE_SAFETY)
#define CMPTYPE_STATIC			UINT16_C(0x0001)
#define CMPTYPE_DYNAMIC			UINT16_C(0x0002)
#define CMPTYPE_SYSTEM			UINT16_C(0x0004)
#define CMPTYPE_IEC				UINT16_C(0x0008)
#define CMPTYPE_APP_CMODULE		UINT16_C(0x0010)


/**
 * <category>ComponentState</category>
 * <element name="RTS_CS_UNKNOWN" type="IN">Unknown state</element> 
 * <element name="RTS_CS_NOT_FOUND" type="IN">Not found to load</element> 
 * <element name="RTS_CS_LOADED" type="IN">Component successfully loaded</element> 
 * <element name="RTS_CS_DISABLED" type="IN">Component disabled in the configuration</element> 
 * <element name="RTS_CS_INITIALIZED" type="IN">Component initialized</element> 
 * <element name="RTS_CS_READY" type="IN">Component loaded and initialized and is ready to use</element> 
 * <element name="RTS_CS_UNLOADED" type="IN">Component is unloaded</element> 
 */
#define RTS_CS_UNKNOWN			UINT16_C(0x0000)
#define RTS_CS_NOT_FOUND		UINT16_C(0x0001)
#define RTS_CS_LOADED			UINT16_C(0x0002)
#define RTS_CS_DISABLED			UINT16_C(0x0003)
#define RTS_CS_INITIALIZED		UINT16_C(0x0004)
#define RTS_CS_READY			UINT16_C(0x0005)
#define RTS_CS_UNLOADED			UINT16_C(0x0006)

/**
 * <category>COMM_CYCLE_HOOK types</category>
 * <description>
 *	<ul>
 *		<li>CM_HOOK_TYPE_NORMAL: Cyclic call of COMM_CYCLE_HOOK </li>
 *		<li>CM_HOOK_TYPE_FLASH_ACCESS: Additional call during flash accesses </li>
 *	</ul>
 * </description>
 */
#define CM_HOOK_TYPE_NORMAL			0
#define CM_HOOK_TYPE_FLASH_ACCESS	1


/**
 * <category>ComponentNameFlags</category>
 * <description>
 *	<ul>
 *		<li>CM_CNF_STATIC: Name is stored in a static buffer</li>
 *		<li>CM_CNF_DYNAMIC: Name is stored in a dynamic buffer</li>
 *	</ul>
 * </description>
 */
#define CM_CNF_STATIC		0
#define CM_CNF_DYNAMIC		1

/**
 * <category>ComponentName</category>
 * <description>
 *	Can be used to manage component names static or dynamic.
 * </description>
 */
typedef union ComponentNameString_
{
	char *psz;	
	char sz[MAX_COMPONENT_NAME];
} ComponentNameString;

typedef struct ComponentName_
{
	RTS_UI32 ulFlags;
	ComponentNameString string;
} ComponentName;


/* Component list */
typedef struct tagComponent_ENTRY
{
	CMPID Id;
	char *pszName;
#ifndef CM_NO_DYNAMIC_COMPONENTS	
	RTS_HANDLE hModule;
#endif
	RTS_UI32 ulVersion;
	PF_COMPONENT_ENTRY pfEntry;
	PF_EXPORT_FUNCTIONS pfExportFunctions;
	PF_IMPORT_FUNCTIONS pfImportFunctions;
	PF_GET_VERSION pfGetVersion;
	PF_HOOK_FUNCTION pfHookFunction;
	PF_CREATEINSTANCE pfCreateInstance;
	PF_DELETEINSTANCE pfDeleteInstance;
	RTS_UI16 iState;
	RTS_UI16 iType;
	RTS_UI8 bStaticName;
} COMPONENT_ENTRY;

typedef struct tagStaticComponent
{
	char *pszCmpName;
	PF_COMPONENT_ENTRY pfCmpEntry;
	int bSystem;
} StaticComponent;

typedef struct tagComponent_LIST
{
	COMPONENT_ENTRY *pComponent;
	int nCount;
} COMPONENT_LIST;

typedef struct
{
	COMPONENT_ENTRY *pCmp;
	CLASSID ClassId;
	CMPID CmpId;
} ClassEntry;

typedef struct
{
	ClassEntry *pClass;
	OBJID ObjId;
	IBase *pIBase;
} InstanceEntry;

/* Api list */
typedef struct tagApi_ENTRY
{
	char szAPIName[MAX_API_NAME];
	RTS_VOID_FCTPTR pfAPIFunction;
	int nRefCount;
	int bExternalLibrary;
	RTS_UI32 ulSignatureID;
	RTS_UI32 ulVersion;
} API_ENTRY;

typedef struct tagApi_LIST
{
	API_ENTRY *pApiList;
	int nCount;
	int nAlloc;
} API_LIST;

/**
 * <category>ApiResolveInfo</category>
 * <description>
 *	API info of the current API function to resolve. See CMGetAPIToResolve.
 * </description>
 */
typedef struct tagAPI_RESOLVE_INFO
{
    char *pszName;
    int importOptions;
    RTS_UI32 ulSignatureID;
    RTS_UI32 ulVersion;
} API_RESOLVE_INFO;


/**
 * <category>Profiler</category>
 * <description>
 *	- To use profiling, RTS_ENABLE_PROFILING must be set during compile. If it is not set, the code for profiling is empty.
 *  - To enable profile of single component hooks set RTS_ENABLE_PROFILING_COMPONENTS during compile time.
 *  - To use the profiler the SysTime component has to be linked statically to the runtime core.
 *	- All profiling information is stored in a separate logger with name "Profiler"
 *	- Profiling component can be specified in setting "Profiler.ComponentID" or during compile in CMPMGR_VALUE_INT_PROFILER_COMPONENTID_DEFAULT.
 *	- RTS_USE_PROFILING must be specified in the beginning of the file, in which profiling is used. Typically this can be specified right after USE_STMT.
 *	- RTS_PROFILING("") can be used to specify a profiling point. In the logger the absolute time and the time difference between two entries is stored.
 *	- With RTS_PROFILING_BEGIN(), RTS_PROFILING2() and RTS_PROFILING_END() a special sequence can be profiled that is marked with a unique ID. All time
 *		differences	between two profiling points with the same ID are store in the profiler.
 * </description>
 */
#if defined(RTS_ENABLE_PROFILING)
#if defined(STATIC_LINK) || defined(MIXED_LINK)	|| defined(CPLUSPLUS)
    #define RTS_USE_PROFILING		ITF_CM
#else
    #define RTS_USE_PROFILING		static PFCMPROFILING pfCMProfiling = NULL;
#endif

#define RTS_PROFILING(s)			{\
                                        IMPORT_SINGLE_ITF(CM);\
                                        if (!CHK_CMProfiling)\
                                            GET_CMProfiling(0);\
                                        if (CHK_CMProfiling)\
                                            CAL_CMProfiling(s,COMPONENT_ID,COMPONENT_NAME,__FILE__,__LINE__,-1);\
                                    }		

#ifdef RTS_ENABLE_PROFILING_COMPONENTS
#define RTS_PROFILING_COMPONENTS(s,cmp)	{\
											IMPORT_SINGLE_ITF(CM);\
											if (!CHK_CMProfiling)\
												GET_CMProfiling(0);\
											if (CHK_CMProfiling)\
											{\
												char tmp[128]; \
												CAL_CMUtlsnprintf(tmp, sizeof(tmp), s, cmp); \
												CAL_CMProfiling(tmp,COMPONENT_ID,COMPONENT_NAME,__FILE__,__LINE__,-1);\
											}\
										}
#else
#define RTS_PROFILING_COMPONENTS(s,cmp)
#endif

	#define RTS_PROFILING_BEGIN(s,id)	{\
											IMPORT_SINGLE_ITF(CM);\
											if (!CHK_CMProfiling)\
												GET_CMProfiling(0);\
											if (CHK_CMProfiling)\
												CAL_CMProfiling(s,COMPONENT_ID,COMPONENT_NAME,__FILE__,__LINE__,CM_PROFILING_ID_ADD_BEGIN(id));\
										}		

	#define RTS_PROFILING2(s,id)		{\
											IMPORT_SINGLE_ITF(CM);\
											if (!CHK_CMProfiling)\
												GET_CMProfiling(0);\
											if (CHK_CMProfiling)\
												CAL_CMProfiling(s,COMPONENT_ID,COMPONENT_NAME,__FILE__,__LINE__,id);\
										}		

	#define RTS_PROFILING_END(s,id)		{\
											IMPORT_SINGLE_ITF(CM);\
											if (!CHK_CMProfiling)\
												GET_CMProfiling(0);\
											if (CHK_CMProfiling)\
												CAL_CMProfiling(s,COMPONENT_ID,COMPONENT_NAME,__FILE__,__LINE__,CM_PROFILING_ID_ADD_END(id));\
										}		
#else
	#define RTS_USE_PROFILING
	#define RTS_PROFILING(s)
	#define RTS_PROFILING_COMPONENTS(s,cmp)
	#define RTS_PROFILING_BEGIN(s,id)
	#define RTS_PROFILING2(s,id)
	#define RTS_PROFILING_END(s,id)
#endif


/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>LicenseFunctions</description>
 */
typedef struct tagLicenseFunctions
{
	RTS_IEC_DWORD dwStructSize;		
	RTS_IEC_BYTE *pfGetUserLicenseValue;		
	RTS_IEC_BYTE *pfConfDynLicChallenge;		
	RTS_IEC_BYTE *pfReqDynLicChallenge;		
	RTS_IEC_DWORD dwVersion;		
} LicenseFunctions;

/**
 * <description>cmaddcomponent</description>
 */
typedef struct tagcmaddcomponent_struct
{
	RTS_IEC_STRING *pszComponent;		/* VAR_INPUT */	
	RTS_IEC_UDINT udiCmpId;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiVersion;			/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE CMAddComponent;		/* VAR_OUTPUT */	
} cmaddcomponent_struct;

DEF_API(`void',`CDECL',`cmaddcomponent',`(cmaddcomponent_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x3FB931A6),0x03050C00)

/**
 * <description>cmexitcomponent</description>
 */
typedef struct tagcmexitcomponent_struct
{
	RTS_IEC_HANDLE hComponent;			/* VAR_INPUT */	
	RTS_IEC_RESULT CMExitComponent;		/* VAR_OUTPUT */	
} cmexitcomponent_struct;

DEF_API(`void',`CDECL',`cmexitcomponent',`(cmexitcomponent_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0DDC8E7F),0x03050C00)

/**
 * <description>cmgetcomponentbyname</description>
 */
typedef struct tagcmgetcomponentbyname_struct
{
	RTS_IEC_STRING *pszComponent;		/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE CMGetComponentByName;	/* VAR_OUTPUT */	
} cmgetcomponentbyname_struct;

DEF_API(`void',`CDECL',`cmgetcomponentbyname',`(cmgetcomponentbyname_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x1C90B550),0x03050C00)

/**
 * <description>cminitcomponent</description>
 */
typedef struct tagcminitcomponent_struct
{
	RTS_IEC_HANDLE hComponent;			/* VAR_INPUT */	
	RTS_IEC_RESULT CMInitComponent;		/* VAR_OUTPUT */	
} cminitcomponent_struct;

DEF_API(`void',`CDECL',`cminitcomponent',`(cminitcomponent_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xAD863340),0x03050C00)

/**
 * OBSOLETE FUNCTION: Use CMRegisterLicenseFunctions instead
 */
typedef struct tagcmregistergetuserlicensevalue_struct
{
	RTS_IEC_BYTE *pfGetUserLicenseValue;	/* VAR_INPUT */	
	RTS_IEC_RESULT CMRegisterGetUserLicenseValue;	/* VAR_OUTPUT */	
} cmregistergetuserlicensevalue_struct;

DEF_API(`void',`CDECL',`cmregistergetuserlicensevalue',`(cmregistergetuserlicensevalue_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x84364FC6),0x03050C00)

/**
 * <description>cmregisterlicensefunctions</description>
 */
typedef struct tagcmregisterlicensefunctions_struct
{
	LicenseFunctions licenseFunctions;	/* VAR_INPUT */	
	RTS_IEC_RESULT CMRegisterLicenseFunctions;	/* VAR_OUTPUT */	
} cmregisterlicensefunctions_struct;

DEF_API(`void',`CDECL',`cmregisterlicensefunctions',`(cmregisterlicensefunctions_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC18CCC88),0x03050C00)

/**
 * <description>cmremovecomponent</description>
 */
typedef struct tagcmremovecomponent_struct
{
	RTS_IEC_HANDLE hComponent;			/* VAR_INPUT */	
	RTS_IEC_RESULT CMRemoveComponent;	/* VAR_OUTPUT */	
} cmremovecomponent_struct;

DEF_API(`void',`CDECL',`cmremovecomponent',`(cmremovecomponent_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB53B03F4),0x03050C00)

/**
 * <description>cmshutdown</description>
 */
typedef struct tagcmshutdown_struct
{
	RTS_IEC_UDINT dwReason;				/* VAR_INPUT */	
	RTS_IEC_RESULT CMShutDown;			/* VAR_OUTPUT */	
} cmshutdown_struct;

DEF_API(`void',`CDECL',`cmshutdown',`(cmshutdown_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x28C83A52),0x03050C00)

/**
 * OBSOLETE FUNCTION: Use CMUnregisterLicenseFunctions instead
 */
typedef struct tagcmunregistergetuserlicensevalue_struct
{
	RTS_IEC_BYTE *pfGetUserLicenseValue;	/* VAR_INPUT */	
	RTS_IEC_RESULT CMUnregisterGetUserLicenseValue;	/* VAR_OUTPUT */	
} cmunregistergetuserlicensevalue_struct;

DEF_API(`void',`CDECL',`cmunregistergetuserlicensevalue',`(cmunregistergetuserlicensevalue_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xE400F55F),0x03050C00)

/**
 * <description>cmunregisterlicensefunctions</description>
 */
typedef struct tagcmunregisterlicensefunctions_struct
{
	LicenseFunctions licenseFunctions;	/* VAR_INPUT */	
	RTS_IEC_RESULT CMUnregisterLicenseFunctions;	/* VAR_OUTPUT */	
} cmunregisterlicensefunctions_struct;

DEF_API(`void',`CDECL',`cmunregisterlicensefunctions',`(cmunregisterlicensefunctions_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x7144A275),0x03050C00)

/**
 * <description>cmutlcwstrcpy</description>
 */
typedef struct tagcmutlcwstrcpy_struct
{
	RTS_IEC_CWCHAR *pcwszDest;			/* VAR_INPUT */	
	RTS_IEC_XINT nDestSize;				/* VAR_INPUT */	
	RTS_IEC_CWCHAR *pcwszSrc;			/* VAR_INPUT */	
	RTS_IEC_RESULT CMUtlcwstrcpy;		/* VAR_OUTPUT */	
} cmutlcwstrcpy_struct;

DEF_API(`void',`CDECL',`cmutlcwstrcpy',`(cmutlcwstrcpy_struct *p)',1,RTSITF_GET_SIGNATURE(0x09DB4923, 0xCCB6DDB5),0x03050C00)

/**
 * <description>cmutlsafestrcpy</description>
 */
typedef struct tagcmutlsafestrcpy_struct
{
	RTS_IEC_STRING *pszDest;			/* VAR_INPUT */	
	RTS_IEC_XINT nDestSize;				/* VAR_INPUT */	
	RTS_IEC_STRING *pszSrc;				/* VAR_INPUT */	
	RTS_IEC_RESULT CMUtlSafeStrCpy;		/* VAR_OUTPUT */	
} cmutlsafestrcpy_struct;

DEF_API(`void',`CDECL',`cmutlsafestrcpy',`(cmutlsafestrcpy_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x794C4461),0x03050C00)

/**
 * <description>cmutlstricmp</description>
 */
typedef struct tagcmutlstricmp_struct
{
	RTS_IEC_STRING *pszString1;			/* VAR_INPUT */	
	RTS_IEC_STRING *pszString2;			/* VAR_INPUT */	
	RTS_IEC_DINT CMUtlStrICmp;			/* VAR_OUTPUT */	
} cmutlstricmp_struct;

DEF_API(`void',`CDECL',`cmutlstricmp',`(cmutlstricmp_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF3161529),0x03050C00)

/**
 * <description>cmutlutf8tow</description>
 */
typedef struct tagcmutlutf8tow_struct
{
	RTS_IEC_BYTE *pUtf8Str;				/* VAR_INPUT */	
	RTS_IEC_UXINT utf8BufferSize;		/* VAR_INPUT */	
	RTS_IEC_WSTRING *pwsz;				/* VAR_INPUT */	
	RTS_IEC_UXINT wstrLen;				/* VAR_INPUT */	
	RTS_IEC_RESULT CMUtlUtf8ToW;		/* VAR_OUTPUT */	
} cmutlutf8tow_struct;

DEF_API(`void',`CDECL',`cmutlutf8tow',`(cmutlutf8tow_struct *p)',1,RTSITF_GET_SIGNATURE(0xB78A45E0, 0x76EB6470),0x03050C00)

/**
 * <description>cmutlwstrcpy</description>
 */
typedef struct tagcmutlwstrcpy_struct
{
	RTS_IEC_WSTRING *pwszDest;			/* VAR_INPUT */	
	RTS_IEC_XINT nDestSize;				/* VAR_INPUT */	
	RTS_IEC_WSTRING *pwszSrc;			/* VAR_INPUT */	
	RTS_IEC_RESULT CMUtlwstrcpy;		/* VAR_OUTPUT */	
} cmutlwstrcpy_struct;

DEF_API(`void',`CDECL',`cmutlwstrcpy',`(cmutlwstrcpy_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x92BF32B1),0x03050C00)

/**
 * <description>cmutlwtoutf8</description>
 */
typedef struct tagcmutlwtoutf8_struct
{
	RTS_IEC_WSTRING *pwsz;				/* VAR_INPUT */	
	RTS_IEC_UXINT wstrLen;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pUtf8Str;				/* VAR_INPUT */	
	RTS_IEC_UXINT utf8BufferSize;		/* VAR_INPUT */	
	RTS_IEC_RESULT CMUtlWToUtf8;		/* VAR_OUTPUT */	
} cmutlwtoutf8_struct;

DEF_API(`void',`CDECL',`cmutlwtoutf8',`(cmutlwtoutf8_struct *p)',1,RTSITF_GET_SIGNATURE(0xAE6E95C8, 0x61F1F05D),0x03050C00)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


typedef struct
{
	RTS_IEC_STRING *pszComponent;
	RTS_IEC_RESULT *pResult;
	RTS_IEC_HANDLE hComponent;
} cmloadcomponent_struct;

typedef struct
{
	RTS_IEC_HANDLE hComponent;
	RTS_IEC_RESULT Result;
} cmunloadcomponent_struct;

typedef struct
{
	RTS_IEC_UDINT udiLicenseID;
	RTS_IEC_RESULT *pResult;
	RTS_IEC_RESULT GetUserLicenseValue;
} getuserlicensevalue_struct;

typedef struct
{
	RTS_IEC_UDINT udiLicenseID;
	RTS_IEC_UDINT udiNewLicenseValue;
	RTS_IEC_RESULT *pResult;
	RTS_IEC_UDINT ReqDynLicChallenge;
} reqdynlicchallenge_struct;

typedef struct
{
	RTS_IEC_UDINT udiLicenseID;
	RTS_IEC_UDINT udiNewLicenseValue;
	RTS_IEC_UDINT udiChallenge;
	RTS_IEC_RESULT *pResult;
	RTS_IEC_BOOL ConfDynLicChallenge;
} confdynlicchallenge_struct;

typedef void (CDECL *PFGETUSERLICENSEVALUE)(getuserlicensevalue_struct);
typedef void (CDECL *PFREQDYNLICCHALLENGE)(reqdynlicchallenge_struct);
typedef void (CDECL *PFCONFDYNLICCHALLENGE)(confdynlicchallenge_struct);


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description> 
 *   Called to initialize the component manager
 * </description>
 * <param name="pszSettingsFile" type="IN">Pointer to name of the configuration file</param>
 * <param name="pStaticComponents" type="IN">Pointer to list of components with name and entry routine to initialize without configuration</param>
 * <result>Error code:
 * <ul>
 *		<li>ERR_OK</li>
 *		<li>ERR_FAILED: One or more components failed to load</li>
 *		<li>ERR_ID_MISMATCH: Signature mismatch of the SysTargetIDs</li>
 * </ul>
 * </result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMInit', `(char *pszSettingsFile, StaticComponent *pStaticComponents)')

/**
 * <description> 
 *   Called to initialize the component manager
 * </description>
 * <param name="pszSettingsFile" type="IN">Pointer to name of the configuration file</param>
 * <param name="pStaticComponents" type="IN">Pointer to list of components with name and entry routine to initialize without configuration</param>
 * <param name="bSettingsFileIsOptional" type="IN">Specifies, if the Settingsfile is only used optionally</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMInit2', `(char *pszSettingsFile, StaticComponent *pStaticComponents, int bSettingsFileIsOptional)')

/**
 * <description> 
 *   Called to initialize the component manager
 * </description>
 * <param name="pszSettingsFile" type="IN">Pointer to name of the configuration file</param>
 * <param name="pStaticComponents" type="IN">Pointer to list of components with name and entry routine to initialize without configuration</param>
 * <param name="options" type="IN">Options for the init sequence of the component manager. See category "CMInit options" for details.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMInit3', `(char *pszSettingsFile, StaticComponent *pStaticComponents, RTS_UI32 options)')

/**
 * <description> 
 *   Called to deinitialize the component manager
 * </description>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMExit', `(void)')

/**
 * <description>Set a flag for main loop to exit</description>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMSetExit', `(void)')

/**
 * <description>Get a flag to exit main loop</description>
 * <result>ERR_OK, if exit flag is set
 * ERR_FAILED else</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMGetExit', `(void)')

#ifdef RTS_DEBUG
	/* Macro can be used to check, if a single code line is reached. Result is printed in the console. */
	#define RTS_CHECKPOINT		if (CHK_CMDebugOut)CAL_CMDebugOut("===> %s checkpoint at line %d\n", __FILE__, __LINE__)
#else
	#define RTS_CHECKPOINT
#endif

/**
 * <description>Can be used for debug outputs on a console.</description>
 * <result>ERR_OK or ERR_NOT_SUPPORTED, if SysOut component is not available</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMDebugOut', `(const char *szFormat, ...)')

/**
 * <description>Can be used for debug outputs on a console.</description>
 * <result>ERR_OK or ERR_NOT_SUPPORTED, if SysOut component is not available</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMDebugOutArg', `(const char *szFormat, va_list *pargList)')

/**
 * <description> 
 *   Called to register a list of component API functions at the component manager
 * </description>
 * <param name="pExpTable" type="IN">Table of functions to be registered</param>
 * <param name="CmpId" type="IN">Component identifier</param>
 * <param name="bExternalLibrary" type="IN">Can be used as external library in the plc program</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMRegisterAPI', `(const CMP_EXT_FUNCTION_REF *pExpTable, RTS_UINTPTR dummy, int bExternalLibrary, RTS_UI32 cmpId)')

/**
 * <description> 
 *   Called to register a component API function at the component manager
 * </description>
 * <param name="pszAPIName" type="IN">Name of the API routine</param>
 * <param name="pfAPIFunction" type="IN">Function pointer of the API routine</param>
 * <param name="bExternalLibrary" type="IN">Can be used as external library in the plc program</param>
 * <param name="ulSignatureID" type="IN">SignatureID of the function prototype</param>
 * <param name="ulVersion" type="IN">Actual supported implementation version</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMRegisterAPI2', `(const char *pszAPIName, RTS_VOID_FCTPTR pfAPIFunction, int bExternalLibrary, RTS_UI32 ulSignatureID, RTS_UI32 ulVersion)')

/**
 * <description> 
 *   Called to get an API function of another component
 * </description>
 * <param name="pszAPIName" type="IN">Name of the API routine</param>
 * <param name="ppfAPIFunction" type="OUT">Returned the function pointer of the API routine</param>
 * <param name="ulSignatureID" type="IN">SignatureID of the function prototype we expected</param>
 * <result>error code</result>
 */
DEF_ITF_GLOBAL_API(`RTS_RESULT', `CDECL', `CMGetAPI', `(char *pszAPIName, RTS_VOID_FCTPTR *ppfAPIFunction, RTS_UI32 ulSignatureID)')

/**
 * <description> 
 *   Called to get an API function of another component
 * </description>
 * <param name="pszAPIName" type="IN">Name of the API routine</param>
 * <param name="ppfAPIFunction" type="OUT">Returned the function pointer of the API routine</param>
 * <param name="ulSignatureID" type="IN">SignatureID of the function prototype we expected</param>
 * <param name="ulVersion" type="IN">Actual implementation version requested</param>
 * <param name="importOptions" type="IN">Import options. See CM_IMPORT_xx defines in CmpStd.h for details</param>
 * <result>error code</result>
 */
DEF_ITF_GLOBAL_API(`RTS_RESULT', `CDECL', `CMGetAPI2', `(char *pszAPIName, RTS_VOID_FCTPTR *ppfAPIFunction, int importOptions, RTS_UI32 ulSignatureID, RTS_UI32 ulVersion)')

/**
 * <description> 
 *   Called to get an API function of another component
 * </description>
 * <param name="pszAPIName" type="IN">Name of the API routine</param>
 * <param name="ppfAPIFunction" type="OUT">Returned the function pointer of the API routine</param>
 * <param name="pulSignatureID" type="INOUT">SignatureID of the function prototype requested and returns the actual signature implemented</param>
 * <param name="pulVersion" type="INOUT">Implementation version requested and returns the actual version implemented</param>
 * <param name="importOptions" type="IN">Import options. See CM_IMPORT_xx defines in CmpStd.h for details</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMGetAPI3', `(char *pszAPIName, RTS_VOID_FCTPTR *ppfAPIFunction, int importOptions, RTS_UI32 *pulSignatureID, RTS_UI32 *pulVersion)')

/**
 * <description> 
 *   Returns the info of the current API function to resolve. Only valid during the run of CMGetAPIx. Otherwise the function returns ERR_NOT_INITIALIZED.
 * </description>
 * <param name="pApiResolveInfo" type="OUT">API function info to be filled. See ApiResolveInfo.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMGetAPIToResolve', `(API_RESOLVE_INFO *pApiResolveInfo)')

/**
 * <description> 
 *   Called to release an API function of another component
 * </description>
 * <param name="pfAPIFunction" type="IN"></param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMReleaseAPI', `(RTS_VOID_FCTPTR pfAPIFunction)')

/**
 * <description> 
 *   Called to load a component. Can also be called during runtime.
 *	 ATTENTION: If component has references to other components, referenced components must be loaded first!
 * </description>
 * <param name="pszComponent" type="IN">Name of the component</param>
 * <param name="pResult" type="INOUT">Pointer to error code</param>
 * <result>Component handle or RTS_INVALID_HANDLE, if an error is occured</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `CMLoadComponent', `(char *pszComponent, RTS_RESULT *pResult)')
DEF_API(`void',`CDECL',`cmloadcomponent',`(cmloadcomponent_struct *p)',1,0)

/**
 * <description> 
 *   Called to load a component. Can also be called during runtime.
 *	 ATTENTION: If component has references to other components, referenced components must be loaded first!
 * </description>
 * <param name="pszComponent" type="IN">Name of the component</param>
 * <param name="iType" type="IN">Type of the component. See category "ComponentType" for details.</param>
 * <param name="pResult" type="INOUT">Pointer to error code</param>
 * <result>Component handle or RTS_INVALID_HANDLE, if an error is occured</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `CMLoadComponent2', `(char *pszComponent, RTS_UI16 iType, RTS_RESULT *pResult)')

/**
 * <description> 
 *   Called to load a component. Can also be called during runtime.
 *	 ATTENTION: If component has references to other components, referenced components must be loaded first!
 * </description>
 * <param name="pszComponent" type="IN">Name of the component</param>
 * <param name="pszFilePath" type="IN">Complete file path of the component</param>
 * <param name="iType" type="IN">Type of the component. See category "ComponentType" for details.</param>
 * <param name="pResult" type="INOUT">Pointer to error code</param>
 * <result>Component handle or RTS_INVALID_HANDLE, if an error is occured</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `CMLoadComponent3', `(char *pszComponent, char *pszFilePath, RTS_UI16 iType, RTS_RESULT *pResult)')

/**
 * <description> 
 *   Called to initialize a component after it was loaded during runtime.
 * </description>
 * <param name="hComponent" type="IN">Handle of the component</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMInitComponent', `(RTS_HANDLE hComponent)')

/**
 * <description> 
 *   Called to update the function pointers of the previous loaded components to let them point to the new added functions.  
 * </description>
 *  <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMImportFunctions', `(void)')

/**
 * <description> 
 *   Called to exit a component after it was loaded during runtime. After this it can be unloaded,
 *   if no other components references this component
 * </description>
 * <param name="hComponent" type="IN">Handle of the component</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMExitComponent', `(RTS_HANDLE hComponent)')

/**
 * <description> 
 *   Called to unload a component. Can also be called during runtime.
 *	 ATTENTION: CMExitComponent must be called before unloading the component!
 * </description>
 * <param name="hComponent" type="IN">Handle of the component</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUnloadComponent', `(RTS_HANDLE hComponent)')
DEF_API(`void',`CDECL',`cmunloadcomponent',`(cmunloadcomponent_struct *p)',1,0)

/**
 * <description> 
 *   Add a component to the list
 * </description>
 * <param name="pComponent" type="IN">Pointer to component description</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>returns a handle to the component</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `CMAddComponent', `(COMPONENT_ENTRY *pComponent, RTS_RESULT *pResult)')

/**
 * <description> 
 *   Remove a component from the list
 * </description>
 * <param name="hComponent" type="IN">Handle to the component</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMRemoveComponent', `(RTS_HANDLE hComponent)')

/**
 * <description> 
 *	Get the component handle of a component specified by name.
 * </description>
 * <param name="pszCmpName" type="IN">Name of the component</param>
 * <param name="pResult" type="INOUT">Pointer to error code</param>
 * <result>Component handle or RTS_INVALID_HANDLE, if an error is occured</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`CMGetComponentByName',`(char *pszCmpName, RTS_RESULT *pResult)')

/**
 * <description> 
 *	Get the component id of a component specified by name.
 *	A component id always consists of the unique vendor id as high word and the specific component id
 *	as low word. So each component can be assigned to the specific vendor.
 * </description>
 * <param name="pszCmpName" type="IN">Name of the component</param>
 * <param name="pCmpId" type="OUT">Component id</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`CMGetCmpId',`(char *pszCmpName, CMPID *pCmpId)')

/**
 * <description> 
 *	Get the component name of a component specified by the component id.
 * </description>
 * <param name="pCmpId" type="IN">Component id</param>
 * <param name="pszCmpName" type="OUT">Name of the component</param>
 * <param name="iMaxCmpName" type="IN">Max length of the component name buffer</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`CMGetCmpName',`(CMPID CmpId, char *pszCmpName, int iMaxCmpName)')

/**
 * <description> 
 *	Get the component description of a component specified by the component id.
 * </description>
 * <param name="pCmpId" type="IN">Component id</param>
 * <result>Pointer to COMPONENT_ENTRY</result>
 */
DEF_ITF_API(`COMPONENT_ENTRY*',`CDECL',`CMGetComponent',`(CMPID CmpId)')

/**
 * <description>
 *	Returns the number of registered components
 * </description>
 * <result>Number of components</result>
 */
DEF_ITF_API(`int',`CDECL',`CMGetNumOfComponents',`(void)')

/**
 * <description>
 *	Returns the registered component specified by index
 * </description>
 * <param name="iIndex" type="IN">Index of the component in the list</param>
 * <result>Pointer to component or NULL if index ist out of range</result>
 */
DEF_ITF_API(`COMPONENT_ENTRY*',`CDECL',`CMGetComponentByIndex',`(int iIndex)')

/**
 * <description>
 *	Returns the first component entry
 * </description>
 * <param name="pResult" type="INOUT">Pointer to error code</param>
 * <result>Pointer to component or NULL if no component available</result>
 */
DEF_ITF_API(`COMPONENT_ENTRY*',`CDECL',`CMGetFirstComponent',`(RTS_RESULT *pResult)')

/**
 * <description>
 *	Returns the registered component specified by index
 * </description>
 * <param name="pCmp" type="IN">Pointer to the previous component</param>
 * <param name="pResult" type="INOUT">Pointer to error code</param>
 * <result>Pointer to component or NULL if end of list is reached</result>
 */
DEF_ITF_API(`COMPONENT_ENTRY*',`CDECL',`CMGetNextComponent',`(COMPONENT_ENTRY *pCmp, RTS_RESULT *pResult)')

/**
 * <description>
 *	Create an instance of a specified class.
 * </description>
 * <param name="ClassId" type="IN">ClassId of the class to create an object</param>
 * <param name="pResult" type="OUT">Pointer to error code for result</param>
 * <result>Pointer to IBase interface of the object</result>
 */
DEF_ITF_API(`IBase*', `CDECL', `CMCreateInstance', `(CLASSID ClassId, RTS_RESULT *pResult)')

/**
 * <description>
 *	Delete an instance.
 * </description>
 * <param name="pIBase" type="IN">Pointer to IBase interface</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMDeleteInstance', `(IBase *pIBase)')

/**
 * <description>
 *	Delete an instance.
 * </description>
 * <param name="ClassId" type="IN">ClassId of the instance</param>
 * <param name="pIBase" type="IN">Pointer to IBase interface</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMDeleteInstance2', `(CLASSID ClassId, IBase *pIBase)')

/**
 * <description>
 *	Get instance of a class.
 * </description>
 * <param name="ClassId" type="IN">ClassId of the class to create an object</param>
 * <param name="ObjId" type="IN">Index number of the instance</param>
 * <param name="pResult" type="OUT">Pointer to error code for result</param>
 * <result>Pointer to IBase interface of the object</result>
 */
DEF_ITF_API(`IBase*', `CDECL', `CMGetInstance', `(CLASSID ClassId, OBJID ObjId, RTS_RESULT *pResult)')

/**
 * <description>
 *	Register an exisiting instance to the component manager. 
 * </description>
 * <param name="ClassId" type="IN">ClassId of the class to create an object</param>
 * <param name="ObjId" type="IN">Index number of the instance</param>
 * <param name="pResult" type="OUT">Pointer to error code for result</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMRegisterInstance', `(CLASSID ClassId, OBJID ObjId, IBase *pIBase)')

/**
 * <description>
 *	Unregister an existing instance from component manager.
 * </description>
 * <param name="pIBase" type="IN">Pointer to IBase interface</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUnregisterInstance', `(IBase *pIBase)')

/**
 * <description>
 *	Get a list of instances, that implements the specified interface.
 * </description>
 * <param name="ItfId" type="IN">Id of the interface</param>
 * <param name="hIBasePool" type="INOUT">Must be a MemPool handle. All instances that implements the interface are
 * stored in this pool as result.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMGetInstanceList', `(ITFID ItfId, RTS_HANDLE hIBasePool)')

/**
 * <description> 
 *   Called to call all components with the specified hook
 * </description>
 * <param name="ulHook" type="IN">Hook (for definition, look into CmpItf.h)</param>
 * <param name="ulParam1" type="IN">First parameter. Hook dependant</param>
 * <param name="ulParam2" type="IN">Second parameter. Hook dependant</param>
 * <param name="bReverse" type="IN">Called the components in the opposite order as they were loaded</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMCallHook', `(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2, int bReverse)')

/**
 * <description> 
 *   Called to call all components with the specified type provided with the specified hook
 * </description>
 * <param name="usComponentTypeMask" type="IN" range="[CMPTYPE_ALL,CMPTYPE_SAFETY,CMPTYPE_STANDARD]">ComponentType mask. See corresponding category</param>
 * <param name="ulHook" type="IN" range="[CH_COMM_CYCLE,CMCALLHOOK_PSEUDOHOOK,RTS_UI32_MAX]">Hook (for definition, look into CmpItf.h)</param>
 * <param name="ulParam1" type="IN" range="[0,CMCALLHOOK_TEST1]">First parameter. Hook dependant</param>
 * <param name="ulParam2" type="IN" range="[0,CMCALLHOOK_TEST2]">Second parameter. Hook dependant</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Hookfunction successfully called</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_FAILED">Component Pool not initialized or any Component responded with some error</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PENDING">Any Component responded with ERR_PENDING</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMCallHook2', `(RTS_UI16 usComponentTypeMask, RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)')

/**
 * <description>Routine to check, if runtime runs in demo mode</description>
 * <result>1=Demo mode, 0=No demo</result>
 */
DEF_ITF_API(`int', `CDECL', `CMIsDemo', `(void)')

/**
 * <description>Routine to complete the component manager initialization.
 *	Contains calling the hooks from CH_INIT2 to CH_INIT_COMM.</description>
 * <result>
 *  <ul>
 *   <li>ERR_OK</li>
 *   <li>ERR_DUPLICATE: If init end is still done, this error message will be returned</li>
 *  </ul>
 * </result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMInitEnd', `(void)')

/**
 * <description>
 *	Functtion checks, if the SysTarget component is originally signed and was not modified.
 * </description>
 * <result>error code: ERR_OK: SysTarget is signed, ERR_FAILED: SysTarget was modified or is unsigned</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMCheckSysTargetSignature', `(void)')

/**
 * <description>Register the IEC function pointers from the license manager lib</description>
 * <param name="pLicenseFunctions" type="IN">Pointer to all IEC function pointers of the license manager lib</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMRegisterLicenseFunctions', `(LicenseFunctions *pLicenseFunctions)')

/**
 * <description>Unregister the IEC function pointers from the license manager lib</description>
 * <param name="pLicenseFunctions" type="IN">Pointer to all IEC function pointers of the license manager lib</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUnregisterLicenseFunctions', `(LicenseFunctions *pLicenseFunctions)')

#define LICENSE_NOT_AVAILABLE	UINT32_C(0xffffffff)
#define LICENSE_INVALID			UINT32_C(0x00000000)

/**
 * <description>Function to check the license of a feature</description>
 * <param name="ulLicenseID" type="IN">HIGHWORD: VendorID, LOWWORD: FeatureID</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>LICENSE_INVALID, LICENSE_NOT_AVAILABLE (Demo mode) or specific license code</result>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Specific license code or LICENSE_NOT_AVAILABLE (Demo mode)</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_FAILED">Not licensed</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOT_SUPPORTED">License library is not registered</errorcode>
 */
DEF_ITF_API(`RTS_UI32', `CDECL', `CMGetUserLicenseValue', `(RTS_UI32 ulLicenseID, RTS_RESULT *pResult)')

/**
 * <description></description>
 * <param name="ulLicenseID" type="IN">HIGHWORD: VendorID, LOWWORD: FeatureID</param>
 * <param name="ulNewLicenseValue" type="IN"></param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result></result>
 */
DEF_ITF_API(`RTS_UI32', `CDECL', `CMReqDynLicChallenge', `(RTS_UI32 ulLicenseID, RTS_UI32 ulNewLicenseValue, RTS_RESULT *pResult)')

/**
 * <description></description>
 * <param name="ulLicenseID" type="IN">HIGHWORD: VendorID, LOWWORD: FeatureID</param>
 * <param name="ulNewLicenseValue" type="IN"></param>
 * <param name="ulChallenge" type="IN"></param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result></result>
 */
DEF_ITF_API(`int', `CDECL', `CMConfDynLicChallenge', `(RTS_UI32 ulLicenseID, RTS_UI32 ulNewLicenseValue, RTS_UI32 ulChallenge, RTS_RESULT *pResult)')

/**
 * <description> 
 *   Function to call the CommCycleHook of all components from outside the CM, if neccessary. This function is 
 *   intended to be called on singletasking systems (with CmpScheduleTimer or CmpScheduleEmbedded) during long
 *   lasting operations. For example SysFlash calls this function to keep the communication alive during writing
 *   long memory areas. 
 *   Before calling the CommCycleHook, the function internally checks the following conditions:
 *   - Is SysTask implemented?
 *   - Is the less then the configured time since the last call of the CommCycleHook elapsed?
 *   If one of this conditions is true, the hook is not called. This allows to use this function without doing
 *   these checks locally in the caller. 
 *   On multitasking systems this function has no effect. Use AsyncServices instead.  
 * </description>
 * <param name="ulParam1" type="IN">Type of the COMM_CYCLE_HOOK. See CM_HOOK_TYPE... types.</param>
 * <param name="ulParam2" type="IN">Second parameter. Hook dependant, typically 0</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMCallExtraCommCycleHook', `(RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)')

/**
 * <description> 
 *   Function returns the current hook function, that is called by the component manager
 * </description>
 * <result>Current hook</result>
 */
DEF_ITF_API(`RTS_UI32', `CDECL', `CMGetCurrentHook', `(void)')

/**
 * <description> 
 *  Function can be called from each component to disable single operations. If this function is called, the event EVT_CmpMgr_DisableOperation is
 *	sent to disable this operation from any component or IEC program.
 * </description>
 * <element name="cmpId" type="IN">ComponentID</element>
 * <element name="ulOperation" type="IN">Operation that can be disabled. See category "Operations" in Itf.h file of the corresponding component for details.</element>
 * <element name="pCmpIdDisabled" type="OUT">Pointer to ComponentID to get the component which disabled the operation. Can be NULL.</element>
 * <result>
 *	<ul>
 *		<li>ERR_OK: Operation is disabled</li>
 *		<li>ERR_FAILED: Operation is enabled [default]</li>
 *		<li>ERR_NOT_SUPPORTED: Cannot be retrieved, because the event is not available</li>
 *	</ul>
 * </result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMIsOperationDisabled', `(CMPID cmpId, RTS_UI32 ulOperation, CMPID *pCmpIdDisabled)')

#define CM_PROFILING_ID_ADD_BEGIN(ID)		(ID | UINT32_C(0x40000000))
#define CM_PROFILING_ID_ADD_END(ID)			(ID | UINT32_C(0x80000000))
#define CM_PROFILING_ID_ISBEGIN(ID)			((ID & UINT32_C(0x40000000)) != 0)
#define CM_PROFILING_ID_ISEND(ID)			((ID & UINT32_C(0x80000000)) != 0)
#define CM_PROFILING_ID_GET(ID)				(ID & UINT32_C(0x3FFFFFFF))

/**
 * <description> 
 *  Central function for profiling
 * </description>
 * <element name="pszInfo" type="IN">Optional info string. Can be NULL.</element>
 * <element name="cmpId" type="IN">Component ID</element>
 * <element name="pszComponentName" type="IN">Component name</element>
 * <element name="pszModuleName" type="IN">Module name</element>
 * <element name="nLine" type="IN">Line number in the module</element>
 * <element name="iID" type="IN">Optional ID to calculate the time difference between two entries with the same ID.
 *	iID = -1: No difference time
 *	iID = 0: No difference time 
 * </element>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMProfiling', `(char *pszInfo, CMPID cmpId, char *pszComponentName, char *pszModuleName, RTS_I32 nLine, RTS_I32 iID)')

#ifdef __cplusplus
}
#endif
