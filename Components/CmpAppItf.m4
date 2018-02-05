/**
 * <interfacename>CmpApp</interfacename>
 * <description> 
 *	<p>This is the interface of the IEC application manager. The manager is responsible for:
 *	<ul>
 *		<li>Handles and collects all IEC applications</li>
 *		<li>Application specific online communication to CoDeSys (debugging, forcing, etc.)</li>
 *		<li>Code and data handling (areas)</li>
 *		<li>Handling of non volatile data (retain handling)</li>
 *	</ul>
 *	</p>
 *	<p>An IEC application is a set of objects which are needed for running a particular instance of the
 *	PLC program. Each application is specified by its unique name.</p>
 *	<p>Applications can have relationships among each other. If one application e.g. A2 depends from another
 *	application A1, A1 is the parent and A2 the child. So A2 is derived from A1.</p>
 *	<p>Each application has two different kinde of states:
 *	<ul>
 *		<li>Application state: run, stop, exception, etc.</li>
 *		<li>Operating state: storing bootproject, do online-change, etc.</li>
 *	</ul>
 *	The application state is used to specify, if the application is opertaing normal or not.
 *	The operating state is used to specify, which job is executed in the moment on the application.</p>
 *	<p>An IEC application consists of one or more tasks. The IEC tasks are not handled directly by the
 *	application manager. This is provided by the the IEC task manager. See CmpIecTask for detailed information.</p>
 *	<p>An application can have code and data. So the application manager needs for each application one or
 *	more memory areas in which the code and data will be administrated.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpApp')

REF_ITF(`SysTaskItf.m4')
REF_ITF(`SysMemItf.m4')
REF_ITF(`SysFileItf.m4')
REF_ITF(`SysCpuHandlingItf.m4')
REF_ITF(`CmpMemPoolItf.m4')
REF_ITF(`CmpEventMgrItf.m4')
REF_ITF(`CmpCommunicationLibItf.m4')
REF_ITF(`CmpRetainItf.m4')
REF_ITF(`CmpSrvItf.m4')

/**
 * <category>Compiler switch</category>
 * <description>
 *	Compiler switches to enable/disable single features in the component.
 * </description>
 * <element name="APP_POU_TABLES_ENABLED">Management of information for each POU can be enabled with this switch. This can be used in CoDeSys to check during login,
 *				which POUs are changed in the project. So at every download, a list of POUs with its size and offset in the area is transmitted to the runtime system.
 *
 *				For this feature you need in CoDeSys:
 *				1. Compiler version >= 3.5.0.0
 *				2. Runtime identification version must be set in the device description >= 3.5.0.0: 
 * 					<ts:section name="runtime_identification">
 *						<ts:setting name="version" type="string" access="visible">
 *							<!-- This is the official 3S runtime version. Can be used by CoDeSys PlugIns to check available functionality of the runtime system!
 *								So this version must be adapted always, if a new firmware version is integrated on the target! -->
 *							<ts:value>3.5.0.0</ts:value>
 *						</ts:setting>
 *					</ts:section>
 * </element>
 */


/**
 * <category>Static defines</category>
 * <description>Maximum length fo application name</description>
 */
#define MAX_LEN_APPLNAME					60

/**
 * <category>Static defines</category>
 * <description>Length of application list that is allocated static</description>
 */
#ifndef APPL_NUM_OF_STATIC_APPLS
	#define APPL_NUM_OF_STATIC_APPLS		8
#endif

/**
 * <category>Static defines</category>
 * <description>Length of session id list that is allocated static</description>
 */
#ifndef APPL_NUM_OF_STATIC_SESSIONIDS
	#define APPL_NUM_OF_STATIC_SESSIONIDS	5
#endif

/**
 * <category>Static defines</category>
 * <description>Length of area pointer list that is allocated static in the application object</description>
 */
#ifndef APPL_NUM_OF_STATIC_AREAS
	#define APPL_NUM_OF_STATIC_AREAS		10
#endif

/**
 * <category>Static defines</category>
 * <description>Number of possible static async services. Can be increased dynamically.</description>
 */
#ifndef APP_NUM_OF_STATIC_ASYNC_SERVICES
	#define APP_NUM_OF_STATIC_ASYNC_SERVICES		8
#endif

/**
 * <category>Static defines</category>
 * <description>The default compiler version. Programming systems < 3.5.12.0 do not provide the compiler version on download. 
 * In this case the earliest version to expect is 3.0.0.0.
 * </description>
 */
#define APP_UDINT_COMPILERVERSION_DEFAULT 0x03000000

/**
 * <category>File name definitions</category>
 * <description>Name of the project archive with all applications in the project</description>
 */
#define PROJECT_ARCHIVE								"Archive.prj"

/**
 * <category>File name definitions</category>
 * <description>Name of the project archive info file, which contains all informations about the archive content</description>
 */
#define PROJECT_ARCHIVE_INFO						"Archive.inf"

/**
 * <category>Static defines</category>
 * <description>Bootproject file extension</description>
 */
#ifndef APP_BOOTPROJECT_FILE_EXTENSION
	#define APP_BOOTPROJECT_FILE_EXTENSION			".app"
#endif

/**
 * <category>Static defines</category>
 * <description>Bootproject file extension to invalidate during download</description>
 */
#ifndef APP_BOOTPROJECT_FILE_EXTENSION_INVALID
	#define APP_BOOTPROJECT_FILE_EXTENSION_INVALID	".ap_"
#endif

/**
 * <category>Static defines</category>
 * <description>Bootproject file extension if file has an error</description>
 */
#ifndef APP_BOOTPROJECT_FILE_EXTENSION_ERROR
	#define APP_BOOTPROJECT_FILE_EXTENSION_ERROR	".err"
#endif

/**
 * <category>Static defines</category>
 * <description>File extension for bootproject crc checksum file</description>
 */
#ifndef APP_BOOTPROJECT_FILE_EXTENSION_CRC
	#define APP_BOOTPROJECT_FILE_EXTENSION_CRC		".crc"
#endif

/**
 * <category>Static defines</category>
 * <description>File extension for symbol file matching to application</description>
 */
#ifndef APP_FILE_EXTENSION_SYMBOLS
	#define APP_FILE_EXTENSION_SYMBOLS	".xml"
#endif

/**
 * <category>Static defines</category>
 * <description>File extension for symbol file matching to bootproject</description>
 */
#ifndef APP_BOOTPROJECT_FILE_EXTENSION_SYMBOLS
	#define APP_BOOTPROJECT_FILE_EXTENSION_SYMBOLS	".boot.xml"
#endif


/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to enable/disable creating bootproject implicit on download:
 *	1: Create bootproject implicit
 *	0: Don't create bootproject implicit
 * </description>
 */
#define APPKEY_INT_CREATE_BOOTPROJECT_ON_DOWNLOAD					"Bootproject.CreateOnDownload"
#ifndef APPVALUE_INT_CREATE_BOOTPROJECT_ON_DOWNLOAD_DEFAULT
	#define APPVALUE_INT_CREATE_BOOTPROJECT_ON_DOWNLOAD_DEFAULT		1
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to enable/diable only storing bootproject implicit on download without storing in RAM:
 *	1: Store bootproject only on download
 *	0: Don't store bootproject only on download
 * </description>
 */
#define APPKEY_INT_STORE_BOOTPROJECT_ONLY_ON_DOWNLOAD				"Bootproject.StoreOnlyOnDownload"
#define APPVALUE_INT_STORE_BOOTPROJECT_ONLY_ON_DOWNLOAD_DEFAULT		0

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Setting to invalidate bootpoject by rename. If not, the key APPKEY_INT_LOAD_BOOTPROJECT
 *	can be used to invalidate the bootproject.</description>
 */
#define APPKEY_INT_BOOTPROJECT_INVALIDATE_BY_RENAME					"Bootproject.InvalidateByRename"
#ifndef APPKEY_INT_BOOTPROJECT_INVALIDATE_BY_RENAME_DEFAULT
	#define APPKEY_INT_BOOTPROJECT_INVALIDATE_BY_RENAME_DEFAULT		0
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Setting to invalidate bootpoject by setting (key APPKEY_INT_LOAD_BOOTPROJECT)</description>
 */
#define APPKEY_INT_BOOTPROJECT_INVALIDATE_BY_SETTING				"Bootproject.InvalidateBySetting"
#ifndef APPKEY_INT_BOOTPROJECT_INVALIDATE_BY_SETTING_DEFAULT
	#define APPKEY_INT_BOOTPROJECT_INVALIDATE_BY_SETTING_DEFAULT	0
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Setting to disable invalidating bootpoject (1=disables both APPKEY_INT_BOOTPROJECT_INVALIDATE_BY_RENAME and APPKEY_INT_BOOTPROJECT_INVALIDATE_BY_SETTING)</description>
 */
#define APPKEY_INT_BOOTPROJECT_INVALIDATE_NEVER						"Bootproject.InvalidateNever"
#ifndef APPKEY_INT_BOOTPROJECT_INVALIDATE_NEVER_DEFAULT
	#define APPKEY_INT_BOOTPROJECT_INVALIDATE_NEVER_DEFAULT			1
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Setting to invalidate bootpoject by rename. If not, the next key (APPKEY_INT_LOAD_BOOTPROJECT)
 *	can be used to invalidate the bootproject.</description>
 */
#define APPKEY_INT_BOOTPROJECT_RUN_IN_FLASH							"Bootproject.RunInFlash"
#ifndef APPKEY_INT_BOOTPROJECT_RUN_IN_FLASH_DEFAULT
	#define APPKEY_INT_BOOTPROJECT_RUN_IN_FLASH_DEFAULT				0
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Setting to disable the bootproject. The application name must be used as prefix for this key!</description>
 */
#define APPKEY_INT_LOAD_BOOTPROJECT									".Load"
#define APPKEY_INT_LOAD_BOOTPROJECT_DEFAULT							1

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Setting to specify wether the the bootproject should start on startup or not. The application name must be used as prefix for this key:
 *	 e.g. Application.Start=0
 * </description>
 */
#define APPKEY_INT_START_BOOTPROJECT								".Start"
#ifndef APPKEY_INT_START_BOOTPROJECT_DEFAULT
	#define APPKEY_INT_START_BOOTPROJECT_DEFAULT						1
#endif
	
/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Setting to initialize the retains during the first load of an offline bootproject. This key is automatically removed after the first load. The application name must be used as prefix for this key!</description>
 */
#define APPKEY_INT_FIRST_LOAD_INIT_RETAINS							".FirstLoadInitRetains"
#define APPKEY_INT_FIRST_LOAD_INIT_RETAINS_DEFAULT					0

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting to set the bootproject of an application. The application name must be used as prefix for this key:
 *	e.g. Application.Bootproject=App1
 * </description>
 */
#define APPKEY_STRING_BOOTPROJECT_NAME								".Bootproject"

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Settings to set the retain management</description>
 */
#define APPKEY_STRING_RETAIN_TYPE_APPLICATIONS		"RetainType.Applications"
#define APPVALUE_STRING_RETAIN_TYPE_ONPOWERFAIL		"OnPowerfail"
#define APPVALUE_STRING_RETAIN_TYPE_INSRAM			"InSRAM"
#define APPVALUE_STRING_RETAIN_TYPE_NONE			"None"
#define APPVALUE_STRING_RETAIN_TYPE_DEFAULT			APPVALUE_STRING_RETAIN_TYPE_ONPOWERFAIL	

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	OBSOLETE SETTING:
 *	"Bootproject.RetainMismatch.Init" should be used instead. Only for backward compatibility.
 * </description>
 */
#define APPKEY_INT_LOAD_WITH_RETAIN_MISMATCH					"Bootproject.LoadWithRetainMismatch"
#define APPVALUE_INT_LOAD_WITH_RETAIN_MISMATCH_DEFAULT			0

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to define the behaviour on loading boot project, if retains do not match.
 *	In this case, all retains are initialized and the bootproject will be started!
 *	Both keys are equivalent!
 * </description>
 */
#define APPKEY_INT_BOOTPROJECT_RETAIN_MISMATCH_INIT				"Bootproject.RetainMismatch.Init"
#define APPVALUE_INT_BOOTPROJECT_RETAIN_MISMATCH_INIT_DEFAULT	0

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to define the behaviour on loading boot project, if retains do not match.
 *	In this case, the bootproject will remain in stop and in exception state! Only a manual reset can heal this state!
 * </description>
 */
#define APPKEY_INT_BOOTPROJECT_RETAIN_MISMATCH_EXCEPTION			"Bootproject.RetainMismatch.Exception"
#define APPVALUE_INT_BOOTPROJECT_RETAIN_MISMATCH_EXCEPTION_DEFAULT	0

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Handle all application online services asynchronously.
 * </description>
 */
#define APPKEY_INT_ASYNC_SERVICES					"AsyncServices"
#ifndef APPVALUE_INT_ASYNC_SERVICES_DEFAULT
	#define APPVALUE_INT_ASYNC_SERVICES_DEFAULT		0
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Timeout to wait for a task gap. e.g. to wait for the gap to execute the online-change code.
 * </description>
 */
#define APPKEY_INT_WAIT_FOR_TASK_GAP				"WaitForTaskGapTimeout"
#ifndef APPVALUE_INT_WAIT_FOR_TASK_GAP_DEFAULT
	#define APPVALUE_INT_WAIT_FOR_TASK_GAP_DEFAULT	INT32_C(10000)
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	If this entry is set, every hardware exception leads to a stop of all applications!
 * </description>
 */
#define APPKEY_INT_GLOBAL_STOP_ON_HARDWARE_EXCEPTION				"Exception.Hardware.GlobalStop"
#ifndef APPVALUE_INT_GLOBAL_STOP_ON_HARDWARE_EXCEPTION_DEFAULT
	#define APPVALUE_INT_GLOBAL_STOP_ON_HARDWARE_EXCEPTION_DEFAULT	0
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Default timeout for the RUN-STOP transition of an application. This is the timeout that is controlled by the optional CmpSupervisor component!
 *	The value is in milliseconds.
 * </description>
 */
#define APPKEY_INT_RUN_STOP_TIMEOUT						"RunStopTimeoutMs"
#ifndef APPVALUE_INT_RUN_STOP_TIMEOUT_DEFAULT
	#define APPVALUE_INT_RUN_STOP_TIMEOUT_DEFAULT		INT32_C(10000)
#endif



/**
 * <category>Static defines</category>
 * <description>
 *	Defines specifies the synchronization mechanism of the online change code to the IEC tasks.
 *	CCO_DEFAULT defines the option, which mechanism is used to synchronize the online change code (copy code).</description>
 * <element name="CCO_SEMAPHORE" type="IN">OnlineChange code is synchronized via a semaphore</element>
 * <element name="CCO_TASK_GAP" type="IN">OnlineChange code is executed in the IEC task gap in the context of the scheduler tick (recommended machnism)</element>
 * <element name="CCO_INTERRUPT_LOCK" type="IN">OnlineChange code is synchronized via interrupt locks (most invasive mechanism)</element>
 * <element name="CCO_TASK_GAP_SEMAPHORE" type="IN">OnlineChange code is synchronized via a semaphore and is executed in the IEC task in the context of the scheduler tick</element>
 */
#define CCO_SEMAPHORE			1
#define CCO_TASK_GAP			2
#define CCO_INTERRUPT_LOCK		3
#define CCO_TASK_GAP_SEMAPHORE	4
#ifndef CCO_DEFAULT
	#define CCO_DEFAULT			CCO_SEMAPHORE
#endif


/**
 * <category>Operations</category>
 * <description>Operations of the application component. Can be disabled with the event CMPID_CmpMgr::EVT_CmpMgr_DisableOperation!</description>
 */
#define OP_APP_STOP					1
#define OP_APP_DOWNLOAD				2
#define OP_APP_ONLINECHANGE			3		
#define OP_APP_WRITE_VARIABLES		4
#define OP_APP_FORCE_VARIABLES		5
#define OP_APP_SET_BREAKPOINT		6
#define OP_APP_RESET				7
#define OP_APP_START				8
#define OP_APP_DELETE_APPLICATION	9


/**
 * <category>Application function pointer definitions</category>
 * <description>
 * </description>
 */
typedef void HUGEPTR(CDECL *PF_GLOBAL_INIT)(RTS_IEC_BOOL);
typedef void HUGEPTR(CDECL *PF_GLOBAL_EXIT)(void);
typedef void HUGEPTR(CDECL *PF_DOWNLOAD_POU)(void);
typedef void HUGEPTR(CDECL *PF_RELOC)(RTS_UI8**);
typedef void HUGEPTR(CDECL *PF_CODE_INIT)(void);
typedef void HUGEPTR(CDECL *PF_PROPERTY_CALL)(void *);



/**
 * <description>
 *	Security settings for the IEC application code and bootproject
 * </description>
 * <element name="DownloadMode_NoSecurity" type="OUT">No support of signed and/or encrypted code</element>
 * <element name="DownloadMode_ALL" type="OUT">All types of application code accepted [DEFAULT]</element>
 * <element name="DownloadMode_MIN_ENCRYPTED" type="OUT">At least encrypted application code accepted (prevention to transmit application code in plain text)</element>
 * <element name="DownloadMode_MIN_SIGNED" type="OUT">At least signed application code accepted (prevention of loading application out of untrusted sources)</element>
 * <element name="DownloadMode_SIGNED_AND_ENCRYPTED" type="OUT">Application code must be signed and encrypted [HIGHEST SECURITY LEVEL]</element>
 */
typedef enum
{
    DownloadMode_NoSecurity,
    DownloadMode_ALL,
    DownloadMode_MIN_ENCRYPTED,
    DownloadMode_MIN_SIGNED,
    DownloadMode_SIGNED_AND_ENCRYPTED
} SecurityAppDownloadMode;

/**
 * <category>SecuritySettings</category>
 * <description>All security settings of the application downloaded code and bootproject. Can be selected in CmpSecurityManager.
 *	NOTE:
 *		Security modes must be ordered in an descending sorting, that the setting with the highest security level is found at the beginning of the list!
 * </description>
 */
#define SECURITY_SETTINGS_CMPAPP			{ \
												{(RTS_I32)DownloadMode_SIGNED_AND_ENCRYPTED, 0, "DownloadMode_SIGNED_AND_ENCRYPTED", "Application code must be signed and encrypted [HIGHEST SECURITY LEVEL]"},\
												{(RTS_I32)DownloadMode_MIN_ENCRYPTED, 0, "DownloadMode_MIN_ENCRYPTED", "At least encrypted application code accepted (prevention to transmit application code in plain text)"},\
												{(RTS_I32)DownloadMode_MIN_SIGNED, 0, "DownloadMode_MIN_SIGNED", "At least signed application code accepted (prevention of loading application out of untrusted sources)"},\
												{(RTS_I32)DownloadMode_ALL, CMPSECMAN_FLAGS_DEFAULT, "DownloadMode_ALL", "All types of application code accepted"},\
												{(RTS_I32)DownloadMode_NoSecurity, 0, "DownloadMode_NoSecurity", "No support of signed and/or encrypted code"}\
											}

#define RTS_CMPAPP_SECURITY_ID_CODE				0



struct tagAPPLICATION;

/**
 * <category>Event parameter</category>
 * <element name="pApp" type="IN">Pointer to application description</element>
 */
typedef struct
{
	struct tagAPPLICATION* pApp;
} EVTPARAM_CmpApp;
#define EVTPARAMID_CmpApp						0x0001
#define EVTVERSION_CmpApp						0x0001

/**
 * <category>Event parameter</category>
 * <element name="pApp" type="IN">Pointer to application description</element>
 * <element name="usResetOption" type="IN">Reset option. See the category "Reset options" for detailed information</element>
 */
typedef struct
{
	struct tagAPPLICATION* pApp;
	RTS_UI16 usResetOption;
} EVTPARAM_CmpApp_Reset;
#define EVTPARAMID_CmpApp_Reset					0x0001
#define EVTVERSION_CmpApp_Reset					0x0002

/**
 * <category>Event parameter</category>
 * <element name="pApp" type="IN">Pointer to application description</element>
 * <element name="pszConfigApplication" type="IN">Pointer to the name of the config application</element>
 */
typedef struct
{
	struct tagAPPLICATION* pApp;
	char* pszConfigApplication;
} EVTPARAM_CmpAppConfig;

#define EVTPARAMID_CmpAppConfig					0x0001
#define EVTVERSION_CmpAppConfig					0x0001


/**
 * <category>Event parameter</category>
 * <element name="pApp" type="IN">Pointer to application description</element>
 * <element name="ulStopReason" type="IN">Stop reason. See category "Stop reason" for details</element>
 */
typedef struct
{
	struct tagAPPLICATION* pApp;
	unsigned long ulStopReason;
} EVTPARAM_CmpAppStop;
#define EVTPARAMID_CmpAppStop					0x0002
#define EVTVERSION_CmpAppStop					0x0001


/**
 * <category>Event parameter</category>
 * <element name="pApp" type="IN">Pointer to application description</element>
 * <element name="ulExitReason" type="IN">Exit reason. See category "Operation reason" for details</element>
 */
typedef struct
{
	struct tagAPPLICATION* pApp;
	RTS_UI32 ulExitReason;
} EVTPARAM_CmpAppExit;
#define EVTPARAMID_CmpAppExit					0x0001
#define EVTVERSION_CmpAppExit					0x0002


/**
 * <category>Event parameter</category>
 * <element name="pApp" type="IN">Pointer to application description</element>
 * <element name="ulDeleteReason" type="IN">Delete reason. See category "Operation reason" for details</element>
 */
typedef struct
{
	struct tagAPPLICATION* pApp;
	RTS_UI32 ulDeleteReason;
} EVTPARAM_CmpAppDelete;
#define EVTPARAMID_CmpAppDelete					0x0001
#define EVTVERSION_CmpAppDelete					0x0002


/**
 * <category>Event parameter</category>
 * <element name="pApp" type="IN">Pointer to application description</element>
 * <element name="bDeny" type="OUT">1=Start is denied, 0=start is executed</element>
 */
typedef struct
{
	struct tagAPPLICATION* pApp;
	int bDeny;
} EVTPARAM_CmpAppDenyStart;
#define EVTPARAMID_CmpAppDenyStart				0x0003
#define EVTVERSION_CmpAppDenyStart				0x0001

/**
 * <category>Event parameter</category>
 * <element name="pApp" type="IN">Pointer to application description</element>
 * <element name="ulStop" type="IN">Reason for the stop, see corresponding category</element>
 * <element name="bDeny" type="OUT">1=Stop is denied, 0=stop is executed</element>
 */
typedef struct
{
	struct tagAPPLICATION* pApp;
	unsigned long ulStopReason;
	int bDeny;
} EVTPARAM_CmpAppDenyStop;
#define EVTPARAMID_CmpAppDenyStop				0x0004
#define EVTVERSION_CmpAppDenyStop				0x0001

/**
 * <category>Event parameter</category>
 * <element name="nTotalBootApps" type="IN">Number of boot applications to be loaded</element>
 * <element name="nSuccessfullyLoadedBootApps" type="IN">Number of boot applications which could be loaded successfully</element>
 */
typedef struct
{
	int nTotalBootApps;
	int nSuccessfullyLoadedBootApps;
} EVTPARAM_CmpAppAllBootAppsLoaded;
#define EVTPARAMID_CmpAppAllBootAppsLoaded		0x0005
#define EVTVERSION_CmpAppAllBootAppsLoaded		0x0001

/**
 * <category>Event parameter</category>
 * <element name="pszAppName" type="IN">Name of the application</element>
 * <element name="bDeny" type="OUT">1=Load bootproject is denied, 0=loading bootproject is be executed</element>
 */
typedef struct
{
	char *pszAppName;
	int bDeny;
} EVTPARAM_CmpAppDenyLoadBootproject;
#define EVTPARAMID_CmpAppDenyLoadBootproject	0x0006
#define EVTVERSION_CmpAppDenyLoadBootproject	0x0001

/**
 * <category>Event parameter</category>
 * <element name="pszAppName" type="IN">Name of the application</element>
 */
typedef struct
{
	char *pszAppName;
} EVTPARAM_CmpAppPrepareLoadBootproject;
#define EVTPARAMID_CmpAppPrepareLoadBootproject	0x0007
#define EVTVERSION_CmpAppPrepareLoadBootproject	0x0001


/**
 * <category>Event parameter</category>
 * <element name="pApp" type="IN">Pointer to application object</element>
 * <element name="hIecTask" type="IN">Handle to IEC task</element>
 * <element name="ulException" type="IN">Exception number. See category "Exception code" in SysExceptItf.h</element>
 */
typedef struct
{
	struct tagAPPLICATION *pApp;
	RTS_HANDLE hIecTask;
	RTS_UI32 ulException;
} EVTPARAM_CmpAppException;
#define EVTPARAMID_CmpAppException				0x0008
#define EVTVERSION_CmpAppException				0x0001


/**
 * <category>Event parameter</category>
 * <element name="pszAppName" type="IN">Name of the application</element>
 */
typedef struct
{
	char *pszAppName;
} EVTPARAM_CmpAppRegisterBootproject;
#define EVTPARAMID_CmpAppRegisterBootproject	0x0009
#define EVTVERSION_CmpAppRegisterBootproject	0x0001

/**
 * <category>Event parameter</category>
 * <element name="pApp" type="IN">Pointer to application object. ulOpState contains the actual state!</element>
 * <element name="ulPrevOpState" type="IN">Previous operating state</element>
 */
typedef struct
{
	struct tagAPPLICATION *pApp;
	RTS_UI32 ulPrevOpState;
} EVTPARAM_CmpAppOperatingStateChanged;
#define EVTPARAMID_CmpAppOperatingStateChanged	0x000A
#define EVTVERSION_CmpAppOperatingStateChanged	0x0001

/**
 * <category>Event parameter</category>
 * <element name="pszArchiveName" type="IN">Name of the archive</element>
 * <element name="bBegin" type="IN">1: If source download started, 0: If source download ends</element>
 */
typedef struct
{
	char *pszArchiveName;
	char bBegin;
} EVTPARAM_CmpAppSourceDownload;
#define EVTPARAMID_CmpAppSourceDownload			0x000B
#define EVTVERSION_CmpAppSourceDownload			0x0001

/**
 * <category>Event parameter</category>
 * <element name="pApp" type="IN">Pointer to application object. ulOpState contains the actual state!</element>
 * <element name="ulSessionId" type="IN">Online sessionid on the deive. Can be used to get the actual logged in User on this channel!</element>
 * <element name="ulAppSessionId" type="IN">Online application sessionid that is provided during the client is logged in on the application</element>
 */
typedef struct
{
	struct tagAPPLICATION *pApp;
	RTS_UI32 ulSessionId;
	RTS_UI32 ulAppSessionId;
} EVTPARAM_CmpAppComm;
#define EVTPARAMID_CmpAppComm					0x000C
#define EVTVERSION_CmpAppComm					0x0002

/**
 * <category>Event parameter</category>
 * <element name="pApp" type="IN">Pointer to application object. ulOpState contains the actual state!</element>
 * <element name="bDeny" type="OUT">1: Operation is denied, 0: Operation can be executed</element>
 */
typedef struct
{
	struct tagAPPLICATION *pApp;
	int bDeny;
} EVTPARAM_CmpAppDeny;
#define EVTPARAMID_CmpAppDeny					0x000D
#define EVTVERSION_CmpAppDeny					0x0001

/**
 * <category>Event parameter</category>
 * <element name="pApp" type="IN">Pointer to application object. ulOpState contains the actual state!</element>
 * <element name="bShutdown" type="IN">1: Runtime is deleting the application during shutdown, 0: else</element>
 * <element name="bDeny" type="OUT">1: Operation is denied, 0: Operation can be executed</element>
 */
typedef struct
{
	struct tagAPPLICATION *pApp;
	int bShutdown;
	int bDeny;
} EVTPARAM_CmpAppDenyDelete;
#define EVTPARAMID_CmpAppDenyDelete				0x000E
#define EVTVERSION_CmpAppDenyDelete				0x0001

/**
 * <category>Event parameter</category>
 * <element name="pApp" type="IN">Pointer to application object. ulOpState contains the actual state!</element>
 * <element name="ulChannelId" type="IN">ChannelID of the actial online service</element>
 * <element name="ulToplevelTag" type="IN">ToplevelTag in the actial online service. NOTE: Highword must be the VendorID to have unique tags!</element>
 * <element name="pHeaderTag" type="IN">Header of the actual online service</element>
 * <element name="pReader" type="IN">Reader of the actual service to read OEM specific tags (some tags could be still consumed by the kernel)</element>
 * <element name="pWriter" type="IN">Writer of the actual service to send back a reply of the consumed OEM tag</element>
 * <element name="Result" type="OUT">Result of the tag handling. If an error is returned here, the download service will be cancelled!</element>
 */
typedef struct
{
	struct tagAPPLICATION *pApp;
	RTS_UI32 ulChannelId;
	RTS_UI32 ulToplevelTag;
	HEADER_TAG *pHeaderTag;
	BINTAGREADER *pReader;
	BINTAGWRITER *pWriter;
	RTS_RESULT Result;
} EVTPARAM_CmpApp_OEMServiceTag;
#define EVTPARAMID_CmpApp_OEMServiceTag			0x000F
#define EVTVERSION_CmpApp_OEMServiceTag			0x0001

struct T_FUNCTION_INFO;

/**
 * <category>Event parameter</category>
 * <element name="pApp" type="IN">Pointer to application object</element>
 * <element name="pInfo" type="IN">Pointer to function info.
 *	NOTE:
 *	The function pointer pointer can be retrieved with:
 *
 *	RTS_VOID_FCTPTR *ppfFunction = NULL;
 *	unsigned char *pucArea;
 *	RTS_RESULT Result = AppGetAreaPointer(pInfo->pApp, pInfo->usArea, &amp;pucArea);
 *	if (Result == ERR_OK)
 *		ppfFunction = (RTS_VOID_FCTPTR *)(pucArea + pInfo->ulOffset);
 * </element>
 * <element name="pszName" type="IN">Pointer to name of the function</element>
 */
typedef struct
{
	struct tagAPPLICATION *pApp;
	struct T_FUNCTION_INFO *pInfo;
	char *pszName;
} EVTPARAM_CmpApp_OEMRegisteredIecFunction;
#define EVTPARAMID_CmpApp_OEMRegisteredIecFunction		0x0010
#define EVTVERSION_CmpApp_OEMRegisteredIecFunction		0x0001


struct tagAREA_CALL_ENTRIES_TABLE;

/**
 * <category>Event parameter</category>
 * <element name="pTable" type="IN">Pointer to a table of POU entries which is being added</element>
 */
typedef struct
{
	struct tagAREA_CALL_ENTRIES_TABLE*	pTable;
} EVTPARAM_CmpApp_POUTable_Create;
#define EVTPARAMID_CmpApp_POUTable_Create             0x0011
#define EVTVERSION_CmpApp_POUTable_Create             0x0001

/**
 * <category>Event parameter</category>
 * <element name="pTable" type="IN">Pointer to a table of POU entries which is being built</element>
 */
typedef struct
{
	struct tagAREA_CALL_ENTRIES_TABLE*	pTable;
} EVTPARAM_CmpApp_POUTable_Build;
#define EVTPARAMID_CmpApp_POUTable_Build             0x0012
#define EVTVERSION_CmpApp_POUTable_Build             0x0001

/**
 * <category>Event parameter</category>
 * <element name="pTable" type="IN">Pointer to a table of POU entries which is being cleared</element>
 */
typedef struct
{
	struct tagAREA_CALL_ENTRIES_TABLE*	pTable;
} EVTPARAM_CmpApp_POUTable_Clear;
#define EVTPARAMID_CmpApp_POUTable_Clear             0x0013
#define EVTVERSION_CmpApp_POUTable_Clear             0x0001

/**
 * <category>Event parameter</category>
 * <element name="pTable" type="IN">Pointer to a table of POU entries which is being deleted</element>
 */
typedef struct
{
	struct tagAREA_CALL_ENTRIES_TABLE*	pTable;
} EVTPARAM_CmpApp_POUTable_Remove;
#define EVTPARAMID_CmpApp_POUTable_Remove             0x0014
#define EVTVERSION_CmpApp_POUTable_Remove             0x0001

struct tagPOU_CALL_ENTRY;

/**
 * <category>Event parameter</category>
 * <element name="pTable" type="IN">Pointer to a table of POU entries to which a new element is being added</element>
 * <element name="pElement" type="IN">Pointer to an element which is being added</element>
 * <element name="Result" type="OUT">Returns ERR_OK if the element can be added</element>
 */
typedef struct
{
	struct tagAREA_CALL_ENTRIES_TABLE*	pTable;
	struct tagPOU_CALL_ENTRY*			pElement;
	RTS_RESULT							Result;
} EVTPARAM_CmpApp_POUTable_AddElement;
#define EVTPARAMID_CmpApp_POUTable_AddElement             0x0015
#define EVTVERSION_CmpApp_POUTable_AddElement             0x0001

/**
 * <category>Event parameter</category>
 * <element name="pTable" type="IN">Pointer to a table of POU entries from which an element is being removed</element>
 * <element name="pElement" type="IN">Pointer to an element which is being removed</element>
 */
typedef struct
{
	struct tagAREA_CALL_ENTRIES_TABLE*	pTable;
	struct tagPOU_CALL_ENTRY*			pElement;
} EVTPARAM_CmpApp_POUTable_RemoveElement;
#define EVTPARAMID_CmpApp_POUTable_RemoveElement             0x0016
#define EVTVERSION_CmpApp_POUTable_RemoveElement             0x0001

/**
 * <category>Event parameter</category>
 * <element name="ulParam1" type="IN">Type of the COMM_CYCLE_HOOK. See CMItf.h, CM_HOOK_TYPE types.</element>
 * <element name="ulParam2" type="IN">Second parameter. Hook dependant, typically 0</element>
 */
typedef struct
{
	RTS_UINTPTR ulParam1;
	RTS_UINTPTR ulParam2;
} EVTPARAM_CmpApp_CommCycle;
#define EVTPARAMID_CmpApp_CommCycle				             0x0017
#define EVTVERSION_CmpApp_CommCycle				             0x0001

/**
 * <category>Event parameter</category>
 * <element name="pApp" type="IN">Pointer to application object. pApp->ulState contains the actual state! See category "Application state" for details.</element>
 * <element name="ulPrevState" type="IN">Previous application state</element>
 */
typedef struct
{
	struct tagAPPLICATION *pApp;
	RTS_UI32 ulPrevState;
} EVTPARAM_CmpApp_StateChanged;
#define EVTPARAMID_CmpApp_StateChanged						0x0018
#define EVTVERSION_CmpApp_StateChanged						0x0001

/**
 * <category>Event parameter</category>
 * <element name="pApp" type="IN">Pointer to application object. pApp->ulState contains the actual state! See category "Application state" for details.</element>
 * <element name="bBegin" type="IN">1=Start of the OnlineChange code execution; 0=End of the OnlineChange code execution</element>
 */
typedef struct
{
	struct tagAPPLICATION *pApp;
	RTS_UI32 bBegin;
} EVTPARAM_CmpApp_OnlineChangeExecution;
#define EVTPARAMID_CmpApp_OnlineChangeExecution				0x0019
#define EVTVERSION_CmpApp_OnlineChangeExecution				0x0001


/**
 * <category>Event parameter</category>
 * <element name="ulBlobID" type="IN">ID of Blob passed in from CompactBlobProvider Plugin</element>
 * <element name="ulBlobSize" type="IN">Size of blob data (payload without header)</element>
 * <element name="pData" type="IN">Pointer to blob data</element>
 */
typedef struct
{	
    RTS_UI32 ulBlobID;
    RTS_UI32 ulBlobSize;
    RTS_UINTPTR pData;
} EVTPARAM_CmpAppEmbedded_CDBlob;
#define EVTPARAMID_CmpAppEmbedded_CDBlob					0x001A
#define EVTVERSION_CmpAppEmbedded_CDBlob					0x0001

/**
 * <category>Event parameter</category>
 * <element name="pszBootprojectName" type="IN">Name of boot project</element>
 * <element name="uiBackupState" type="IN">State of retain backup (see category "Retain backup state"</element>
 */
typedef struct
{
	char *pszBootprojectName;
	RTS_UI16 uiBackupState;
} EVTPARAM_CmpAppRetainBackupState;
#define EVTPARAMID_CmpAppRetainBackupState					0x001B
#define EVTVERSION_CmpAppRetainBackupState					0x0001

/**
 * <category>Event parameter</category>
 * <element name="usResetOption" type="IN">Reset option. See the category "Reset options" for detailed information</element>
 */
typedef struct
{
	RTS_UI16 usResetOption;
} EVTPARAM_CmpAppResetAllApplications;
#define EVTPARAMID_CmpAppResetAllApplications				0x001C
#define EVTVERSION_CmpAppResetAllApplications				0x0001

/**
 * <category>Event parameter</category>
 * <element name="pApp" type="IN">Pointer to application description</element>
 * <element name="pfReloc" type="IN">Function pointer to generated relocation function</element>
 */
typedef struct
{
	struct tagAPPLICATION* pApp;
	PF_RELOC pfReloc;
} EVTPARAM_CmpAppPrepareCodeInit;
#define EVTPARAMID_CmpAppPrepareCodeInit					0x0001
#define EVTVERSION_CmpAppPrepareCodeInit					0x0002

/**
 * <category>Event parameter</category>
 * <element name="pApp" type="IN">Pointer to application description</element>
 * <element name="bAlloc" type="IN">1 to allocate area, 0 to free data</element>
 * <element name="usType" type="IN">range="[DA_NONE,DA_CODE,DA_CONSTANT,DA_DATA,DA_RETAIN,INVALID_DA_AREA]">Type of the area (see category Area Types)</element>
 * <element name="ulSize" type="IN">range="[0,VALID_SIZE,RTS_SIZE_MAX]">Requested size of the memory</element>
 * <element name="pArea" type="OUT">Pointer to the memory block. NULL if no memory is available</element>
 */
typedef struct
{
	RTS_UI32 bAlloc;
	struct tagAPPLICATION* pApp;
	RTS_UI16 usType;
	RTS_SIZE ulSize;
	RTS_UI8 *pArea;
	RTS_RESULT result;
} EVTPARAM_CmpAppArea;
#define EVTPARAMID_CmpAppArea				0x0001
#define EVTVERSION_CmpAppArea				0x0002

/**
 * <category>Events</category>
 * <description>Event is sent before start of the specified application</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpApp</param>
 */
#define EVT_PrepareStart					MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Events</category>
 * <description>Event is sent after start of the specified application</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpApp</param>
 */
#define EVT_StartDone						MAKE_EVENTID(EVTCLASS_INFO, 2)

/**
 * <category>Events</category>
 * <description>Event is sent before stop of the specified application</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppStop</param>
 */
#define EVT_PrepareStop						MAKE_EVENTID(EVTCLASS_INFO, 3)

/**
 * <category>Events</category>
 * <description>Event is sent after stop of the specified application</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppStop</param>
 */
#define EVT_StopDone						MAKE_EVENTID(EVTCLASS_INFO, 4)

/**
 * <category>Events</category>
 * <description>Event is sent before reset of the specified application, but after the stop of the application! So no IEC user code is executed at this event!</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpApp_Reset</param>
 */
#define EVT_PrepareReset					MAKE_EVENTID(EVTCLASS_INFO, 5)

/**
 * <category>Events</category>
 * <description>Event is sent after reset of the specified application</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpApp_Reset</param>
 */
#define EVT_ResetDone						MAKE_EVENTID(EVTCLASS_INFO, 6)

/**
 * <category>Events</category>
 * <description>Event is sent before online change of the specified application</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpApp</param>
 */
#define EVT_PrepareOnlineChange				MAKE_EVENTID(EVTCLASS_INFO, 7)

/**
 * <category>Events</category>
 * <description>Event is sent after online change of the specified application</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpApp</param>
 */
#define EVT_OnlineChangeDone				MAKE_EVENTID(EVTCLASS_INFO, 8)

/**
 * <category>Events</category>
 * <description>Event is sent before download of the specified application</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpApp</param>
 */
#define EVT_PrepareDownload					MAKE_EVENTID(EVTCLASS_INFO, 9)

/**
 * <category>Events</category>
 * <description>Event is sent after download of the specified application</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpApp</param>
 */
#define EVT_DownloadDone					MAKE_EVENTID(EVTCLASS_INFO, 10)

/**
 * <category>Events</category>
 * <description>Event is sent after CodeInit. Is called inside the task safe section 
 *	and only at online-change! (e.g. the copy code for online-change is executed here).</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpApp</param>
 */
#define EVT_CodeInitDone					MAKE_EVENTID(EVTCLASS_INFO, 11)

/**
 * <category>Events</category>
 * <description>Event is sent before an application is deleted. The application is stopped, if this event is posted.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppDelete</param>
 */
#define EVT_PrepareDelete					MAKE_EVENTID(EVTCLASS_INFO, 12)

/**
 * <category>Events</category>
 * <description>Event is sent after an application is deleted. The application is stopped, if this event is posted. 
 *	ATTENTION: Right after this event, the APPLICATION structure of the event parameter is deleted!</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppDelete</param>
 */
#define EVT_DeleteDone						MAKE_EVENTID(EVTCLASS_INFO, 13)

/**
 * <category>Events</category>
 * <description>Event is sent before an application executes its exit code (deleting the application, reinit at download or reset).
 *	The application is in stop, if this event is posted.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppExit</param>
 */
#define EVT_PrepareExit						MAKE_EVENTID(EVTCLASS_INFO, 14)

/**
 * <category>Events</category>
 * <description>Event is sent after an application executes its exit code (deleting the application, reinit at download or reset).
 *	The application is in stop, if this event is posted.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppExit</param>
 */
#define EVT_ExitDone						MAKE_EVENTID(EVTCLASS_INFO, 15)

/**
 * <category>Events</category>
 * <description>Event is sent after creating a bootproject of an application successfully</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpApp</param>
 */
#define EVT_CreateBootprojectDone			MAKE_EVENTID(EVTCLASS_INFO, 16)

/**
 * <category>Events</category>
 * <description>Event is sent to deny loading a bootproject of an application.
 * </description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppDenyLoadBootproject</param>
 */
#define EVT_DenyLoadBootproject				MAKE_EVENTID(EVTCLASS_INFO, 18)

/**
 * <category>Events</category>
 * <description>Event is sent before loading a bootproject of an application</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppPrepareLoadBootproject</param>
 */
#define EVT_PrepareLoadBootproject			MAKE_EVENTID(EVTCLASS_INFO, 19)

/**
 * <category>Events</category>
 * <description>Event is sent after loading a bootproject of an application successfully</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpApp</param>
 */
#define EVT_LoadBootprojectDone				MAKE_EVENTID(EVTCLASS_INFO, 17)

/**
 * <category>Events</category>
 * <description>Event is sent to deny starting a bootproject of an application.
 * </description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppDenyStart</param>
 */
#define EVT_DenyStartBootproject			MAKE_EVENTID(EVTCLASS_INFO, 20)

/**
 * <category>Events</category>
 * <description>Event is sent before starting a bootproject of an application</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpApp</param>
 */
#define EVT_PrepareStartBootproject			MAKE_EVENTID(EVTCLASS_INFO, 21)

/**
 * <category>Events</category>
 * <description>Event is sent after starting a bootproject of an application</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpApp</param>
 */
#define EVT_StartBootprojectDone			MAKE_EVENTID(EVTCLASS_INFO, 22)

/**
 * <category>Events</category>
 * <description>Event is sent to deny starting an application</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppDenyStart</param>
 */
#define EVT_DenyStart						MAKE_EVENTID(EVTCLASS_INFO, 23)

/**
 * <category>Events</category>
 * <description>Event is sent to deny stopping an application</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppDenyStop</param>
 */
#define EVT_DenyStop						MAKE_EVENTID(EVTCLASS_INFO, 24)

/**
 * <category>Events</category>
 * <description>Event is sent after all boot applications have been loaded</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppAllBootAppsLoaded</param>
 */
#define EVT_AllBootprojectsLoaded			MAKE_EVENTID(EVTCLASS_INFO, 25)

/**
 * <category>Events</category>
 * <description>Event is sent on Reset, after global exit and before global init.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppConfig</param>
 */
#define EVT_GlobalExitOnResetDone			MAKE_EVENTID(EVTCLASS_INFO, 26)

/**
 * <category>Events</category>
 * <description>Event is sent after an application has executed its exit code. The application is stopped, if this event is posted. The event has got the additional parameter szConfigApp</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppConfig</param>
 */
#define EVT_ExitDoneWithConfigAppInfo		MAKE_EVENTID(EVTCLASS_INFO, 27)

/**
 * <category>Events</category>
 * <description>Event is sent, if an exception occurred in the context of an application
 *	NOTE:
 *	In case of a retain mismatch, the RTSEXCPT_RETAIN_IDENTITY_MISMATCH is provided as exception code (see ulException in EVTPARAM_CmpAppException).
 * </description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppException</param>
 */
#define EVT_CmpApp_Exception				MAKE_EVENTID(EVTCLASS_EXCEPTION, 28)

/**
 * <category>Events</category>
 * <description>Event is sent, if a new bootproject is registered</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppRegisterBootproject</param>
 */
#define EVT_RegisterBootproject				MAKE_EVENTID(EVTCLASS_INFO, 29)

/**
 * <category>Events</category>
 * <description>Event is sent, if the bootproject file cannot be created.
 *	NOTE: EVT_CreateBootprojectFailed is sent additionally in this case!</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpApp</param>
 */
#define EVT_CreateBootprojectFileFailed		MAKE_EVENTID(EVTCLASS_ERROR, 30)

/**
 * <category>Events</category>
 * <description>Event is sent, if the creation of a bootproject failed. This can occur at creation of the bootproject
 *	implicit at download or explicit by the user.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpApp</param>
 */
#define EVT_CreateBootprojectFailed			MAKE_EVENTID(EVTCLASS_ERROR, 31)

/**
 * <category>Events</category>
 * <description>Event is sent, if the operating state has changed</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppOperatingStateChanged</param>
 */
#define EVT_OperatingStateChanged			MAKE_EVENTID(EVTCLASS_INFO, 32)

/**
 * <category>Events</category>
 * <description>Event is sent, if the project archive is downloaded (source download)</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppSourceDownload</param>
 */
#define EVT_SourceDownload					MAKE_EVENTID(EVTCLASS_INFO, 33)

/**
 * <category>Events</category>
 * <description>Event is sent, if a client login to the specified application</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppComm</param>
 */
#define EVT_Login							MAKE_EVENTID(EVTCLASS_INFO, 34)

/**
 * <category>Events</category>
 * <description>Event is sent, if a client logout of the specified application. The event is sent additionally, if a communication error occurred.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppComm</param>
 */
#define EVT_Logout							MAKE_EVENTID(EVTCLASS_INFO, 35)

/**
 * <category>Events</category>
 * <description>Event is sent to deny deleting an application</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppDenyDelete</param>
 */
#define EVT_DenyDelete						MAKE_EVENTID(EVTCLASS_INFO, 36)

/**
 * <category>Events</category>
 * <description>Event is sent to deny deleting a bootproject of an application</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppDenyDelete</param>
 */
#define EVT_DenyDeleteBootproject			MAKE_EVENTID(EVTCLASS_INFO, 37)

/**
 * <category>Events</category>
 * <description>Event is sent to handle own download/online-change service tags</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpApp_OEMServiceTag</param>
 */
#define EVT_OEMDownloadServiceTag			MAKE_EVENTID(EVTCLASS_INFO, 39)

/**
 * <category>Events</category>
 * <description>Event is sent to get all IEC-functions specified in CoDeSys with the following attribute:
 *		{attribute 'register_in_runtime'}
 *	NOTE:
 *	- Only IEC-functions can be registered
 *	- The function name must be unique!
 *  - The user have to handle the events EVT_PrepareExit and EVT_DeleteDone to check, if the application and so the IEC function will be removed!
 * </description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpApp_OEMRegisteredIecFunction</param>
 */
#define EVT_OEMRegisteredIecFunction		MAKE_EVENTID(EVTCLASS_INFO, 40)

/**
 * <category>Events</category>
 * <description>Event is fired on any change in the POU Tables Manager</description>
 * <param name="pEventParam" type="IN">EVT_POUTable_Changed</param>
 */
#define EVT_POUTable_Changed                MAKE_EVENTID(EVTCLASS_INFO, 41)

/**
 * <category>Events</category>
 * <description>Event is fired at every communication cycle (idle loop). This can be used in IEC-for background jobs.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpApp_CommCycle</param>
 */
#define EVT_CommCycle		                MAKE_EVENTID(EVTCLASS_INFO, 42)

/**
 * <category>Events</category>
 * <description>Event is fired, if the application state changed.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpApp_StateChanged</param>
 */
#define EVT_StateChanged	                MAKE_EVENTID(EVTCLASS_INFO, 43)

/**
 * <category>Events</category>
 * <description>Event is fired at the beginning and end of the atomic OnlineChange code execution
 *	NOTE:
 *	Be aware that you are in a very timecritical and realtime affected phase! Don't do blocking or time consuming operations here!!!
 * </description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpApp_OnlineChangeExecution</param>
 */
#define EVT_OnlineChangeExecution			MAKE_EVENTID(EVTCLASS_INFO, 44)

/**
 * <category>Events</category>
 * <description>Event is sent at the beginning of AppRunAfterDownloadCode before the first call of SysCpuCallIecFuncWithParams.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppPrepareCodeInit</param>
 */
#define EVT_PrepareCodeInit					MAKE_EVENTID(EVTCLASS_INFO, 45)


/**
 * <category>Events</category>
 * <description>Event is sent when compact download detects additional blob information</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppEmbedded_CDBlob</param>
 */
#define EVT_CDBlob							MAKE_EVENTID(EVTCLASS_INFO, 46)


/**
 * <category>Events</category>
 * <description>Event is sent when backup or restore of retains is served</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppRetainBackupState</param>
 */
#define EVT_RetainBackupState				MAKE_EVENTID(EVTCLASS_INFO, 47)

/**
 * <category>Events</category>
 * <description>Event is sent when AppResetAllApplications is called</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppResetAllApplications</param>
 */
#define EVT_ResetAllApplications_Prepare	MAKE_EVENTID(EVTCLASS_INFO, 48)

/**
 * <category>Events</category>
 * <description>Event is sent when AppResetAllApplications is finished</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppResetAllApplications</param>
 */
#define EVT_ResetAllApplications_Done		MAKE_EVENTID(EVTCLASS_INFO, 49)

/**
 * <category>Events</category>
 * <description>
 * This event allows to specify an area address in an OEM runtime component.
 * Overloading or modifying the system component SysMem can lead to problems, and is not needed any more when using this event.
 * For example, to specify an address for a separate %M area,
 *     - define a separate %M area in your device description with setting area\flags set to Memory =  0x10
 *     - In this event, check this area type with "IsArea(pParam->usType, DA_MEMORY)" and return your memory pointer in pArea.
 * The Event is sent before call to SysMemAllocArea. As parameter, a pointer to EVTPARAM_CmpAppArea is passed.
 * If structure member pArea is set to a value <> NULL, SysMemAllocArea (or other allocation function) is not called and this value is used for the area.
 * The Event is also sent before call to SysMemFreeArea, in case and pArea was allocated by the first call.
 * In this case, free the memory that was allocated in EVT_AllocArea.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppArea</param>
 */
#define EVT_AllocArea						MAKE_EVENTID(EVTCLASS_INFO, 50)


/**
 * <category>OperationID</category>
 * <description>Operation ID for the supervision of the RUN-STOP transition of an application</description>
 * <param name="RTS_OPID_Application_RunStop" type="IN">The OperationID is the ID of the application (see APPLICATION.iId for details)</param>
 * <param name="RTS_OPID_Application_RunStop_Description" type="IN"></param>
 */
#define RTS_OPID_Application_RunStop					-1
#define RTS_OPID_Application_RunStop_Description		"Supervision of the RUN to STOP transition of an application. OperationID is the ID of the application (see APPLICATION.iId for details)"


/**
 * <category>Application state</category>
 * <description>
 *	<ul>
 *		<li>AS_NONE: Unspecified state</li>
 *		<li>AS_RUN: Application in run</li>
 *		<li>AS_STOP: Application in stop</li>
 *		<li>AS_DEBUG_HALT_ON_BP: Application halted on breakpoint</li>
 *		<li>AS_DEBUG_STEP: Not used actually</li>
 *		<li>AS_SYSTEM_APPLICATION: State of a system application</li>
 *	</ul>
 * </description>
 */
#define AS_NONE					UINT32_C(0x00000000)
#define AS_RUN					UINT32_C(0x00000001)
#define AS_STOP					UINT32_C(0x00000002)
#define AS_DEBUG_HALT_ON_BP		UINT32_C(0x00000003)
#define AS_DEBUG_STEP			UINT32_C(0x00000004)
#define AS_SINGLE_CYCLE			UINT32_C(0x00000005)
#define AS_SYSTEM_APPLICATION	UINT32_C(0xFFFFFFFF)

/**
 * <category>Application operating state</category>
 * <description>
 *	<ul>
 *		<li>OS_NONE: Unspecified state (init state)</li>
 *		<li>OS_PROGRAM_LOADED: Application is completely loaded</li>
 *		<li>OS_DOWNLOAD: Application download in progress</li>
 *		<li>OS_ONLINE_CHANGE: Application online-change in progress</li>
 *		<li>OS_STORE_BOOTPROJECT: Store bootproject in progress</li>
 *		<li>OS_FORCE_ACTIVE: Force values is active on the application</li>
 *		<li>OS_EXCEPTION: Application is in exception state (an exception occurred in this application)</li>
 *		<li>OS_RUN_AFTER_DOWNLOAD: Download code at the end of download is in progress (initialization of the application)</li>
 *		<li>OS_STORE_BOOTPROJECT_ONLY: Only the bootproject is stored at download</li>
 *		<li>OS_EXIT: Application exit is still executed (application is no longer active)</li>
 *		<li>OS_DELETE: Application is deleted (object is available, but the content is stil deleted)</li>
 *		<li>OS_RESET: Application reset is in progress</li>
 *		<li>OS_RETAIN_MISMATCH: Retain mismatch occurred during loading the bootproject (retain data does not match to the application)</li>
 *		<li>OS_BOOTPROJECT_VALID: Bootproject available (bootproject matched to running application in RAM)</li>
 *		<li>OS_LOAD_BOOTPROJECT: Loading bootproject in progress</li>
 *		<li>OS_FLOW_ACTIVE: Flow control active</li>
 *		<li>OS_RESET_OUTPUTS: Forcing reset outputs if task cycle is called</li>
 *		<li>OS_COREDUMP_LOADED: This is never used in the runtime, but in the fake online app in CODESYS. So this is flag is included here to reserve its usage.</li>
 *      <li>OS_EXECUTIONPOINTS_ACTIVE: Executionpoints are active currently</li>
 *      <li>OS_COREDUMP_CREATING: A core dump is being created currently after the app crashed</li>
 *	</ul>
 * </description>
 */
#define OS_NONE						UINT32_C(0x00000000)
#define OS_PROGRAM_LOADED			UINT32_C(0x00000001)
#define OS_DOWNLOAD					UINT32_C(0x00000002)
#define OS_ONLINE_CHANGE			UINT32_C(0x00000004)
#define OS_STORE_BOOTPROJECT		UINT32_C(0x00000008)
#define OS_FORCE_ACTIVE				UINT32_C(0x00000010)
#define OS_EXCEPTION				UINT32_C(0x00000020)
#define OS_RUN_AFTER_DOWNLOAD		UINT32_C(0x00000040)
#define OS_STORE_BOOTPROJECT_ONLY	UINT32_C(0x00000080)
#define OS_EXIT						UINT32_C(0x00000100)
#define OS_DELETE					UINT32_C(0x00000200)
#define OS_RESET					UINT32_C(0x00000400)
#define OS_RETAIN_MISMATCH			UINT32_C(0x00000800)
#define OS_BOOTPROJECT_VALID		UINT32_C(0x00001000)
#define OS_LOAD_BOOTPROJECT			UINT32_C(0x00002000)
#define OS_FLOW_ACTIVE				UINT32_C(0x00004000)
/* OS_RUN_IN_FLASH became obsolete */
/* #define OS_RUN_IN_FLASH			UINT32_C(0x00008000) */
#define OS_RESET_OUTPUTS			UINT32_C(0x00010000)
#define OS_COREDUMP_LOADED			UINT32_C(0x00020000)
#define OS_EXECUTIONPOINTS_ACTIVE	UINT32_C(0x00040000)
#define OS_COREDUMP_CREATING		UINT32_C(0x00080000)
#define OS_SINGLE_CYCLE_ACTIVE		UINT32_C(0x00100000)
#define OS_DISABLE_RESET			UINT32_C(0x00200000)

#define APP_SET_OP_STATE(pApp, OpState)		(((APPLICATION *)pApp)->ulOpState |= OpState)
#define APP_RESET_OP_STATE(pApp, OpState)	(((APPLICATION *)pApp)->ulOpState &= ~OpState)
#define APP_HAS_OP_STATE(pApp, OpState)		(((APPLICATION *)pApp)->ulOpState & OpState)


/**
 * <category>Operation reason</category>
 * <description>
 *	Reason specifies the cause of the specific operation.
 * </description>
 *	<element name="APP_REASON_UNKNOWN" type="IN">Unknown reason</element>
 *	<element name="APP_REASON_SHUTDOWN" type="IN">Shutdown of the plc</element>
 *	<element name="APP_REASON_RESET" type="IN">Reset of the plc</element>
 *	<element name="APP_REASON_EXCEPTION" type="IN">Exception occurred</element>
 *	<element name="APP_REASON_USER" type="IN">User operation</element>
 *	<element name="APP_REASON_IECPROGRAM" type="IN">IEC program caused the action</element>
 *	<element name="APP_REASON_DELETE" type="IN">Reason is deletion of the application</element>
 *	<element name="APP_REASON_DEBUGGING" type="IN">Reason is debugging application</element>
 *	<element name="APP_REASON_RUNSTOP_SWITCH" type="IN">Reason is the RunStop switch</element>
 *	<element name="APP_REASON_REDUNDANCY_SYNC" type="IN">Reason is the synchronization at redundant systems</element>
 */
#define APP_REASON_UNKNOWN			0
#define APP_REASON_SHUTDOWN			1
#define APP_REASON_RESET			2
#define APP_REASON_EXCEPTION		3
#define APP_REASON_USER				4
#define APP_REASON_IECPROGRAM		5
#define APP_REASON_DELETE			6
#define APP_REASON_DEBUGGING		7
#define APP_REASON_RUNSTOP_SWITCH	8
#define APP_REASON_REDUNDANCY_SYNC	9

/**
 * <category>Start reason</category>
 * <description>
 *	Reason to set the application in run.
 * </description>
 *	<element name="APP_START_REASON_UNKNOWN" type="IN">Unknown reason</element>
 *	<element name="APP_START_REASON_USER" type="IN">User started the application</element>
 *	<element name="APP_START_REASON_RUNSTOP_SWITCH" type="IN">Application will be started because the RunStop switch is on start</element>
 */
#define APP_START_REASON_UNKNOWN			APP_REASON_UNKNOWN
#define APP_START_REASON_USER				APP_REASON_USER
#define APP_START_REASON_RUNSTOP_SWITCH		APP_REASON_RUNSTOP_SWITCH
#define APP_START_REASON_REDUNDANCY_SYNC	APP_REASON_REDUNDANCY_SYNC

/**
 * <category>Stop reason</category>
 * <description>
 *	Reason to set the application in stop.
 * </description>
 *	<element name="APP_STOP_REASON_UNKNOWN" type="IN">Unknown reason</element>
 *	<element name="APP_STOP_REASON_SHUTDOWN" type="IN">Shutdown of the plc</element>
 *	<element name="APP_STOP_REASON_RESET" type="IN">Reset will be done after stop the application</element>
 *	<element name="APP_STOP_REASON_EXCEPTION" type="IN">Exception occurred</element>
 *	<element name="APP_STOP_REASON_USER" type="IN">User stopped the application</element>
 *	<element name="APP_STOP_REASON_IECPROGRAM" type="IN">Stop is done out of the IEC program</element>
 *	<element name="APP_STOP_REASON_DELETE" type="IN">Application will be deleted after the stop</element>
 *	<element name="APP_STOP_REASON_DEBUGGING" type="IN">Application will be stopped because of debugging</element>
 *	<element name="APP_STOP_REASON_RUNSTOP_SWITCH" type="IN">Application will be stopped because the RunStop switch is on stop</element>
 */
#define APP_STOP_REASON_UNKNOWN			APP_REASON_UNKNOWN			
#define APP_STOP_REASON_SHUTDOWN		APP_REASON_SHUTDOWN		
#define APP_STOP_REASON_RESET			APP_REASON_RESET			
#define APP_STOP_REASON_EXCEPTION		APP_REASON_EXCEPTION		
#define APP_STOP_REASON_USER			APP_REASON_USER			
#define APP_STOP_REASON_IECPROGRAM		APP_REASON_IECPROGRAM		
#define APP_STOP_REASON_DELETE			APP_REASON_DELETE			
#define APP_STOP_REASON_DEBUGGING		APP_REASON_DEBUGGING		
#define APP_STOP_REASON_RUNSTOP_SWITCH	APP_REASON_RUNSTOP_SWITCH	
#define APP_STOP_REASON_REDUNDANCY_SYNC	APP_REASON_REDUNDANCY_SYNC

/**
 * <category>Exit reason</category>
 * <description>
 *	Reason to exit the application.
 * </description>
 *	<element name="APP_EXIT_REASON_UNKNOWN" type="IN">Unknown reason</element>
 *	<element name="APP_EXIT_REASON_SHUTDOWN" type="IN">Shutdown of the plc</element>
 *	<element name="APP_EXIT_REASON_RESET" type="IN">Reset of the plc</element>
 *	<element name="APP_EXIT_REASON_EXCEPTION" type="IN">Exception occurred during download of an application</element>
 *	<element name="APP_EXIT_REASON_DELETE" type="IN">Reason is deletion of the application</element>
 *	<element name="APP_EXIT_REASON_RUNSTOP_SWITCH" type="IN">Reason is the RunStop switch</element>
 *	<element name="APP_EXIT_REASON_REDUNDANCY_SYNC" type="IN">Reason is the synchronization at redundant systems</element>
 */
#define APP_EXIT_REASON_UNKNOWN			APP_REASON_UNKNOWN			
#define APP_EXIT_REASON_SHUTDOWN		APP_REASON_SHUTDOWN
#define APP_EXIT_REASON_RESET			APP_REASON_RESET			
#define APP_EXIT_REASON_EXCEPTION		APP_REASON_EXCEPTION		
#define APP_EXIT_REASON_DELETE			APP_REASON_DELETE			
#define APP_EXIT_REASON_RUNSTOP_SWITCH	APP_REASON_RUNSTOP_SWITCH
#define APP_EXIT_REASON_REDUNDANCY_SYNC	APP_REASON_REDUNDANCY_SYNC

/**
 * <category>Retain backup state</category>
 * <description>
 *	State values for event EVT_RetainBackupState/EVTPARAM_CmpAppRetainBackupState.uiBackupState.
 * </description>
 *	<element name="APP_RBS_UNKNOWN" type="IN">Unknown state</element>
 *	<element name="APP_RBS_BACKUP_PREPARE" type="IN">Preparation of file backup (gathering information)</element>
 *	<element name="APP_RBS_BACKUP_BEGIN" type="IN">File backup begin</element>
 *	<element name="APP_RBS_BACKUP_END" type="IN">File backup end</element>
 *	<element name="APP_RBS_RESTORE" type="IN">Restore retains from file</element>
 */
#define APP_RBS_UNKNOWN				0
#define APP_RBS_BACKUP_PREPARE		1
#define APP_RBS_BACKUP_BEGIN		2
#define APP_RBS_BACKUP_END			3
#define APP_RBS_RESTORE				4
 
/**
 * <category>Static defines</category>
 * <description>Predefined objects in the runtime</description>
 */
#define USERDB_OBJECT_PLCLOGIC					"Device.PlcLogic"
#define USERDB_OBJECT_PLCLOGIC_BACKUPRESTORE	"Device.PlcLogic.__Backup&Restore"
#define USERDB_OBJECT_CMODULE_INTEGRATION		"__C-ModuleIntegration__"

/* <SIL2/> 
 * <description>Typedef for Application info at download, containing GUIDs and Application name </description>
 */
typedef struct _APPLICATION_DOWNLOAD_INFO
{
	RTS_GUID guidCode;
	RTS_GUID guidData;
	char szApplicationName;
} APPLICATION_DOWNLOAD_INFO;

/* <SIL2/> 
 * <description>Typedef for external references</description>
 */
typedef struct _EXT_REF_INFO
{
	RTS_UI32 ulSignatureId;
	RTS_UI32 ulIdentifier;
	RTS_UI32 ulVersion;
	RTS_UI32 ulOffset;
	RTS_UI16 usArea;
	char szFunctionName;
} EXT_REF_INFO;

/* <SIL2/> 
 * <description>Typedef for global init information</description>
 */
typedef struct
{
	RTS_IEC_BOOL bInitRetains;
	RTS_IEC_BOOL bResult;
#ifndef RTS_SIXTEENBITBYTES
	RTS_IEC_BOOL bDummy1;
	RTS_IEC_BOOL bDummy2;
#endif
} GLOBALINIT_STRUCT;

#define APP_RELOC_CODE_VERSION2	0x03010000

/* <SIL2/> 
 * <description>Typedef for relocate Code information</description>
 */
typedef struct
{
	RTS_IEC_BYTE* dwAreaAbsolute;
	RTS_IEC_DWORD dwVersion;
	RTS_IEC_BYTE* dwAreaOffsets;
	RTS_IEC_BOOL bResult;
	RTS_IEC_BOOL bDummy1;
#ifndef RTS_SIXTEENBITBYTES
	RTS_IEC_BOOL bDummy2;
	RTS_IEC_BOOL bDummy3;
#endif
} RELOCATECODE_STRUCT2;

/* <SIL2/> 
 * <description>Typedef for download header information</description>
 */
typedef struct
{
	RTS_UI16 usAreas;
	RTS_UI16 usTasks;
	RTS_UI32 ulPOUs;
	RTS_UI32 ulExtRefs;
	unsigned char aucCodeId[16];
	unsigned char aucDataId[16];
} DOWNLOAD_HEADER;

/* <SIL2/> 
 * <description>Typedef for area information</description>
 */
typedef struct
{
	RTS_UI32 ulSize;
	RTS_UI16 usNum;
	RTS_UI16 usType;
} AREA_INFO;

typedef struct
{
	RTS_UI16 DUMMY;
	RTS_UI16 usArea;
	RTS_UI32 ulOffset;
} POU_INFO;

typedef struct
{
	RTS_UI16 DUMMY;
	RTS_UI16 usArea;
	RTS_UI32 ulOffset;
	RTS_UI32 ulSize;
} CODE_INFO;

typedef struct
{
	RTS_UI16 DUMMY;
	RTS_UI16 usArea;
	RTS_UI32 ulOffset;
	RTS_UI32 ulSignatureId;
	char szName[1];
} FUNCTION_INFO_OLD;

/* <SIL2/> */
typedef struct T_FUNCTION_INFO
{
	RTS_UI16 DUMMY;
	RTS_UI16 usArea;
	RTS_UI32 ulOffset;
	RTS_UI32 ulSignatureId;
	RTS_UI32 ulIdentifier;
	RTS_UI32 ulVersion;
} FUNCTION_INFO;

/* <SIL2/> */
typedef struct
{
	RTS_UI16 DUMMY;
	RTS_UI16 usArea;
	RTS_UI32 ulOffset;
} POU_REF;

/**
 * <description>
 *	<p>POU Descriptor.</p>
 *
 *	<p>This type might be extending in future somehow 
 *	that's why CODE_INFO etc. are not used here.</p></description>
 */
typedef struct tagPOU_DESCRIPTOR
{
	/* POU offset from the start of the code segment */
	RTS_SIZE	offset;

	/* POU size */
	RTS_SIZE	size;

} POU_DESCRIPTOR;

/**
 *	<description>Descriptor for a callable entity.</description>
 */
typedef struct tagPOU_CALL_ENTRY
{
	/* for intrusive doubly-linked list */
	struct tagPOU_CALL_ENTRY*	pNext;
	struct tagPOU_CALL_ENTRY* pPrev;

	/* POU information */
	POU_DESCRIPTOR						pou;

	/* Optional target specific object that can be */
	/* attached to this entry. */
	void*								pTargetSpecificObject;

} POU_CALL_ENTRY;


#ifndef APP_CALL_ENTRIES_POOL_COUNT
#	define APP_CALL_ENTRIES_POOL_COUNT 16384
#endif

/**
 * <description>
 *	<p>Table of POU entries.</p>
 *
 *	<p>The life-cycle of this object coincides with the life-cycle
 *	of the corresponding code area.</p></description>
 */
typedef struct tagAREA_CALL_ENTRIES_TABLE
{
	/* Handle to the Table Manager */
	RTS_HANDLE				hTablesManager;

	/* Link to the next table */
	struct tagAREA_CALL_ENTRIES_TABLE* pNext;

	/* Code area start address */
	RTS_UI8*				pCode;

	/* Code area size */
	RTS_SIZE				size;

	/* Entries list */
	POU_CALL_ENTRY*			pHead;
	POU_CALL_ENTRY*			pTail;

	/* Table size for quickening certain operations */
	RTS_SIZE				elementsCount;

	/* Elements allocator (dynamic memory pool) */
	RTS_HANDLE			hElementsPool;

	/* Table state flags */
	RTS_SIZE				flags;

	/* Optional target specific object that can be */
	/* attached to this table. */
	union
	{
		void*		pPtrValue;
		RTS_SIZE	value;
	}						targetSpecificObject;

} AREA_CALL_ENTRIES_TABLE;

#define	ACET_STATE_UNCERTAIN	0x0
#define ACET_STATE_READY			((RTS_SIZE)0x1)

#define ACET_IS_READY(pt)			(0 != ((pt)->flags & CET_STATE_READY))
#define ACET_IS_UNCERTAIN(pt)	(0 == ((pt)->flags & CET_STATE_READY))
#define ACET_SET_READY(pt)		(pt)->flags |= CET_STATE_READY
#define ACET_RESET_READY(pt)	(pt)->flags &= ~CET_STATE_READY


typedef enum
{
	DRT_AREA_OFFSET,
	DRT_PROPERTY,
	DRT_AREA_OFFSET_BIT
} DRT_DATAREFTYPE;

typedef struct tagAreaOffsetDataRef
{
	RTS_UI16 DUMMY;
	RTS_UI16 usArea;
	RTS_UI32 ulOffset;
	RTS_UI16 usSize;
} AreaOffsetDataRef;

typedef struct tagAreaOffsetBitDataRef
{
	RTS_UI16 usBit;
	RTS_UI16 usArea;
	RTS_UI32 ulOffset;
	RTS_UI16 usSize;
} AreaOffsetBitDataRef;

typedef struct tagPropertyDataRef
{
	RTS_UI16 DUMMY;
	RTS_UI16 usSize;
	RTS_UI16 usAreaInstance;
	RTS_UI16 usAreaProperty;
	RTS_UI32 ulOffsetInstance;				
	RTS_UI32 ulOffsetGet;
	RTS_UI32 ulOffsetSet;
} PropertyDataRef;

typedef struct tagVarDataRef
{	
	union
	{
		AreaOffsetDataRef areaoffsetRef;
		AreaOffsetBitDataRef areaoffsetBitRef;
		PropertyDataRef propertyRef;
	} DataRefUnion;

	DRT_DATAREFTYPE drtDataRefType;
} VarDataRef;

typedef struct tagVarValue
{
	RTS_UI16 bExtended;
	union
	{
		RTS_UI8 byValue[8];
		RTS_UI8 *pValue;
	} V;
} VarValue;

typedef struct tagVarDesc
{
	VarDataRef DataRef;
	VarValue Value;
} VarDesc;

/* <SIL2/> */
typedef struct _RTS_VERSION_STRUCT
{
	RTS_IEC_UINT uiMajor;
	RTS_IEC_UINT uiMinor;
	RTS_IEC_UINT uiServicePack;
	RTS_IEC_UINT uiPatch;
} RTS_VERSION_STRUCT;

/**
 * <category>Property keys</category>
 * <element name="TEXT_PROPERTY_PROJECT" type="IN">Project name</element>
 * <element name="TEXT_PROPERTY_TITLE" type="IN">Title</element>
 * <element name="TEXT_PROPERTY_AUTHOR" type="IN">Author</element>
 * <element name="TEXT_PROPERTY_DESCRIPTION" type="IN">Description</element>
 * <element name="VERSION_PROPERTY_PROJECTVERSION" type="IN">Project version</element>
 */
#define TEXT_PROPERTY_PROJECT				"Project"
#define TEXT_PROPERTY_TITLE					"Title"
#define TEXT_PROPERTY_AUTHOR				"Author"
#define TEXT_PROPERTY_DESCRIPTION			"Description"
#define VERSION_PROPERTY_PROJECTVERSION		"Version"


/**
 * <category>Project information</category>
 * <description>
 *	Contains the project information as specified in the project information dialog in CoDeSys. To use this, the checkbox 
 *	"Automatically generate POUs for property access" in the project information dialog be enabled.
 * </description>
 * <element name="stProjectName" type="OUT">Project name without ending</element>
 * <element name="stTitle" type="OUT">Title</element>
 * <element name="stVersion" type="OUT">Version as string in the format "x.x.x.x"</element>
 * <element name="stAuthor" type="OUT">Author</element>
 * <element name="stDescription" type="OUT">Description</element>
 */
typedef struct
{
	RTS_IEC_STRING stProjectName[81];
	RTS_IEC_STRING stTitle[81];
	RTS_IEC_STRING stVersion[81];
	RTS_IEC_STRING stAuthor[81];
	RTS_IEC_STRING stDescription[81];
} PROJECT_INFO;


/**
 * <category>Application information</category>
 * <description>
 *	Contains the application information as specified in the application property dialog in CoDeSys.
 * </description>
 * <element name="pstProjectName" type="OUT">Pointer project name</element>
 * <element name="pstAuthor" type="OUT">Pointer to author</element>
 * <element name="pstVersion" type="OUT">Pointer to version as string in the format "x.x.x.x"</element>
 * <element name="pstDescription" type="OUT">Pointer to description</element>
 * <element name="pstProfile" type="OUT">Pointer to used CoDeSys profile name</element>
 * <element name="dtLastChanges" type="OUT">Time and date of last modification of the application (UTC)</element>
 */
typedef struct
{
	RTS_IEC_STRING *pstProjectName;
	RTS_IEC_STRING *pstAuthor;
	RTS_IEC_STRING *pstVersion;
	RTS_IEC_STRING *pstDescription;
	RTS_IEC_STRING *pstProfile;
	RTS_IEC_DATE_AND_TIME dtLastChanges;
	RTS_IEC_STRING *pstCompilerVersion;
} APPLICATION_INFO;

typedef struct
{
	RTS_IEC_WSTRING *pwstProjectName;
	RTS_IEC_WSTRING *pwstAuthor;
	RTS_IEC_WSTRING *pwstVersion;
	RTS_IEC_WSTRING *pwstDescription;
	RTS_IEC_WSTRING *pwstProfile;
	RTS_IEC_DATE_AND_TIME dtLastChanges;
} APPLICATION_INFO_WCHAR;

typedef struct
{
	RTS_IEC_WSTRING wszKey[81];
	RTS_IEC_BOOL bBooleanProperty;
} BOOLEANPROPERTY;

typedef struct
{
	RTS_IEC_WSTRING wszKey[81];
	RTS_IEC_WSTRING wszTextProperty[81];
} TEXTPROPERTY;

typedef struct
{
	RTS_IEC_WSTRING wszKey[81];
	RTS_IEC_UDINT udiNumberProperty;
} NUMBERPROPERTY;

typedef struct
{
	RTS_IEC_WSTRING wszKey[81];
	RTS_IEC_UINT uiMajor;
	RTS_IEC_UINT uiMinor;
	RTS_IEC_UINT uiServicePack;
	RTS_IEC_UINT uiPatch;
} VERSIONPROPERTY;

/* FlowControl Flags */
#define FCF_DO			0x01
#define FCF_DOATBREAK	0x02

typedef struct
{
	unsigned char byPool[MEM_GET_STATIC_LEN_(0,0)];
	RTS_HANDLE hPool;
	unsigned char *pbyService;
	int iTaskIndex;
	RTS_BOOL bMemPoolService;
	RTS_UI32 uiFlags;
	RTS_BOOL bInCycle;
	RTS_BOOL bEnable;
} FlowControl;

typedef struct
{
	RTS_UI32	ulFirmCode;
	RTS_UI32	ulProductCode;
	RTS_UI32	ulEncryptionCode;
	RTS_UI32	ulCRC;
	RTS_UI8		ucKey[16];	
} EncryptionInfo;

typedef struct
{
    RTS_UI32 ui32Version;       /* Version of this structure. Has to be 1 for this specification  */
    RTS_UI8 aKey[32];           /* Symmetric key. AES 256. Part of the first online service. Array of 0 for all remaining services */
    RTS_UI8 aIV[16];            /* IV. AES has a block size of 128 bits. Use a new IV for every online service. */
    RTS_UI8 aHMAC[32];          /* Bytes containing HMAC of the encrypted service. */
} AppEncryptionInfo;

/**
 * <category>Application flags</category>
 * <description>
 *	Flags to specify properties of an application
 * </description>
 *	<element name="AF_SYSTEM_APPLICATION" type="IN">This is a system application</element>
 *	<element name="AF_IOCONFIG_BYTE_ADDRESSING" type="IN">Byte addressing for all IO channels is activated on the target.
 *		e.g. "%IW8" means byte 8 and not byte 16 in this case!</element>
 *	<element name="AF_IOCONFIG_BIT_WORD_ADDRESSING" type="IN">Bits are byte adressed.
 *		e.g. "%IX2.3" means bit 3 in word 2 instead of in byte 2!</element>
 *	<element name="AF_KEEP_AT_PARENT_ONLINE_CHANGE" type="IN">This application will survive an online change of the parent application (not a download!)</element>
 *	<element name="AF_ALLOW_SYMBOLIC_VARIABLE_ACCESS_IN_SYNC_WITH_IEC_TASK" type="IN">This application allows the syncronized 
 *      consistent access by CmpIecVarAccess online services (application accepts possible related jitter).</element>
 *	<element name="AF_SIGNED_APPLICATION" type="IN">The application was signed at download time. Only signed online changes are allowed in this application.</element>
 *	<element name="AF_ENCRYPTED_APPLICATION" type="IN">The application was encrypted at download time. Only encrypted online changes are allowed in this application.</element>
 *	<element name="AF_DEVICE_APPLICATION" type="IN">This is a device application.</element>
 *	<element name="AF_APPLICATION_STOP_PARENT_APPS_ON_EXCEPTION" type="IN">All parent applications shall be stopped in case of an exception.</element>
 */ 
#define AF_SYSTEM_APPLICATION										UINT32_C(0x00010000)
#define AF_IOCONFIG_BYTE_ADDRESSING									UINT32_C(0x00020000)
#define AF_IOCONFIG_BIT_WORD_ADDRESSING								UINT32_C(0x00040000)
#define AF_KEEP_AT_PARENT_ONLINE_CHANGE								UINT32_C(0x00080000)
#define AF_ALLOW_SYMBOLIC_VARIABLE_ACCESS_IN_SYNC_WITH_IEC_TASK		UINT32_C(0x00100000)
#define AF_SIGNED_APPLICATION                               		UINT32_C(0x00200000)
#define AF_ENCRYPTED_APPLICATION                               		UINT32_C(0x00400000)
#define AF_DEVICE_APPLICATION										UINT32_C(0x00800000)
#define AF_APPLICATION_STOP_PARENT_APPS_ON_EXCEPTION				UINT32_C(0x01000000)

/**
 * <category>Download flags</category>
 * <description>
 *	Download flags that are transmitted with each download.
 * </description>
 *	<element name="DLF_CONTINUEDOWNLOAD" type="IN">Continue download, if download is transmitted in several blocks</element>
 *	<element name="DLF_USEBOOTAPPFROMDOWNLOAD" type="IN">This flag indicates newer PS where the user can define whether a boot project shall be written
 *														(to switch on next flag)</element>
 *	<element name="DLF_WRITEBOOTAPPLICATION" type="IN">This flag indicates that a the boot application shall be written with download</element>
 */
#define DLF_CONTINUEDOWNLOAD		UINT32_C(0x00000001)
#define DLF_USEBOOTAPPFROMDOWNLOAD	UINT32_C(0x00000002)
#define DLF_WRITEBOOTAPPLICATION	UINT32_C(0x00000004)

/*
 * <description>Specifies how an area was allocated. Used to call the correct free method</description>
 */
typedef enum
{
	AAT_NONE,
	AAT_EVENT,
	AAT_ALLOCAREA,
	AAT_ALLOCDATA,
	AAT_ALLOCCODE,
	AAT_ALLOCRETAIN
} AreaAllocationType;

/**
 * <SIL2/>
 * <category>Application description</category>
 * <description>
 *	ATTENTION: Allways add new elements at the end of the structure!!! This structure will be referred
 *				to generated IEC task code!
 * </description>
 *	<element name="pAppParent" type="IN">Pointer to parent application</element>
 *	<element name="iId" type="IN">Id of the application. Is always unique.</element>
 *	<element name="CodeGuid" type="IN">Unique identifier of the IEC code</element>
 *	<element name="DataGuid" type="IN">Unique identifier of the IEC data</element>
 *	<element name="ulState" type="IN">State of the application (see corresponding category)</element>
 *	<element name="ulOpState" type="IN">Operating state of the application (see corresponding category)</element>
 *	<element name="hBootproject" type="IN">Handle to the bootproject. Is valid, if actually bootproject will be loaded</element>
 *	<element name="hDebugTask" type="IN">Handle of the debug task (if debugging is active)</element>
 *	<element name="pfGlobalInit" type="IN">Function pointer to the global init routine</element>
 *	<element name="pfGlobalExit" type="IN">Function pointer to the global exit routine</element>
 *	<element name="hForcePool" type="IN">Handle a pool of force entries</element>
 *	<element name="hBPPool" type="IN">Handle a pool of breakpoints</element>
 *	<element name="bPersistentForce" type="IN">Flag to detect, if persistent force is active</element>
 *	<element name="szName" type="IN">Application name</element>
 *	<element name="ulPSVersion" type="IN">Version number of programming system (set in download)</element>
 *	<element name="ulTargetSettingVersion" type="IN">Version number of Target settings used by PS (set in download)</element>
 *	<element name="szBootprojectName" type="IN">Bootproject name of the application</element>
 *	<element name="pcArea" type="IN">Pointer to data areas of this application</element>
 *	<element name="ausAreaType" type="IN">Area types. See category "Area Types" in SysMemItf.h.</element>
 *	<element name="aulAreaSize" type="IN">Area sizes</element>
 *	<element name="byForcePool" type="IN">Force pool. Only used, if CmpAppForce is available</element>
 *	<element name="byBPPool" type="IN">Breakpoint pool. Only used, if CmpAppBP is available</element>
 *	<element name="flowControl" type="IN">Flow control structure. Only used, if CmpAppBP is available and flow control is activated</element>
 *	<element name="SafedCodeGuid" type="IN">Safed GUID of IEC code from bootproject</element>
 *	<element name="SafedDataGuid" type="IN">Safed GUID of IEC data from bootproject</element>
 *	<element name="rtRetainType" type="IN">Retain type of retain application data</element>
 *	<element name="ulException" type="IN">Actual exception, if an exception occurred. In this case, ulOpState is set to OS_EXCEPTION.</element>
 *	<element name="ApplicationInfo" type="IN">Application info</element>
 *	<element name="pouMemorySegmentInfo" type="IN">POU reference to the memory segment info</element>
 *	<element name="pouAppInfo" type="IN">Data Location of the application content information</element>
 *	<element name="ulCRCBootproject" type="IN">CRC of trhe bootproject. It is used temporary at creating the bootproject to calculate the CRC during the complete store process.</element>
 *	<element name="aAreaCRC" type="IN">List of CRCs for every memory area. The CRC is calculated over the content of the area (e.g. if it is a retain area, the CRC is calculated
 *			over the names and types of the retain variables). Additionally the CRC contains the application name to be always unique over all applications!</element>
 *	<element name="hBPConditionPool" type="IN">Handle a pool of breakpoint conditions.</element>
 *  <element name="pouCodeLocationInfo" type="IN"></element>
 *  <element name="ulCRCExecutionpoints" type="IN"></element>
 *  <element name="bLeaveExecutionpointsActive" type="IN">If true, all Executionpoints in the application will remain active after the logout</element>
 *  <element name="iHasCModule" type="IN">Number of linked C-Integration modules</element>
 *  <element name="pVendorExtension" type="IN">Pointer to store vendor specific informations at an application</element>
 *  <element name="hDynamicModulePool" type="IN">A memory pool containing all names of linked modules from the C-Integration</element>
 *  <element name="ausAreaAllocationType" type="IN">Specifies how an area was allocated. Used to call the correct free method</element>
 *  <element name="pBPContext" type="IN">Low level context information of a breakpoint</element>
 *  <element name="ulCompilerVersion" type="IN">The version of the compiler with which the application was created (set in download for PS versions >= 3.5.12.0, default is 3.0.0.0)</element>
 */
typedef struct tagAPPLICATION
{
	struct tagAPPLICATION *pAppParent;
	RTS_I32 iId;
	
	RTS_GUID CodeGuid;
	RTS_GUID DataGuid;

	RTS_UI32 ulState;
	RTS_UI32 ulOpState;
	RTS_HANDLE hBootproject;
	RTS_HANDLE hDebugTask;
	PF_GLOBAL_INIT pfGlobalInit;
	PF_GLOBAL_EXIT pfGlobalExit;

	RTS_HANDLE hDummy;		/* Was previously hSessionIdPool, but is removed. Because of backward compatibility, it must be remaining here! */
	RTS_HANDLE hForcePool;
	RTS_HANDLE hBPPool;

	RTS_I32 bPersistentForce;

	char szName[MAX_LEN_APPLNAME+1]; /* an extra dummy byte to be compatible with the library */

	RTS_UI32 ulPSVersion;
	RTS_UI32 ulTargetSettingVersion;

	/* ATTENTION: The member variables above are exported via CmpApp.library in IEC! Don't do any changes in this area!!! */

	char szBootprojectName[MAX_PATH_LEN + MAX_LEN_APPLNAME]; /* moved here exactly because of the sentence above */

	RTS_UI8 *pcArea[APPL_NUM_OF_STATIC_AREAS];
	RTS_UI16 ausAreaType[APPL_NUM_OF_STATIC_AREAS];
	RTS_UI32 aulAreaSize[APPL_NUM_OF_STATIC_AREAS];

	RTS_UI8 byForcePool[MEM_GET_STATIC_LEN_(0,0)];
	RTS_UI8 byBPPool[MEM_GET_STATIC_LEN_(0,0)];
	FlowControl flowControl;
	
	RTS_GUID SafedCodeGuid;
	RTS_GUID SafedDataGuid;

	RetainType rtRetainType;

	RTS_UI32 ulException;
	RTS_I32 bInvalidateByRename;
	RTS_I32 bInvalidateBySetting;
	RTS_UINTPTR consistencyFlags;

	RTS_VOID_FCTPTR *ppfGetBooleanProperty;
	RTS_VOID_FCTPTR *ppfGetTextProperty;
	RTS_VOID_FCTPTR *ppfGetNumberProperty;
	RTS_VOID_FCTPTR *ppfGetVersionProperty;

	RTS_I32 bInitRetains;

	RTS_UI32 ulFlags;						/* Application flags. See corresponding category. */
	RTS_UI32 ulOffsetExtRefFunctionPointer; /* Area must be area 0! Offset must be valid for SystemApplications. The offset where to find the function to link functions*/ 

	APPLICATION_INFO ApplicationInfo;
	POU_REF pouMemorySegmentInfo;
	POU_REF pouAppInfo;
	RTS_UI32 ulCRCBootproject;
	RTS_UI32 aulAreaCRC[APPL_NUM_OF_STATIC_AREAS];
	RTS_HANDLE hBPConditionPool;
	RTS_HANDLE hBPInterpCodePool;
	POU_REF pouCodeLocationInfo;
	RTS_UI32 ulCRCExecutionpoints;
	RTS_I32 bLeaveExecutionpointsActive;
	
	RTS_I32 iHasCModule;
	void *pVendorExtension;
	RTS_HANDLE hDynamicModulePool;
	RTS_UI32 ulLastStateChange;
	AreaAllocationType ausAreaAllocationType[APPL_NUM_OF_STATIC_AREAS];
	RTS_HANDLE hTaskSync;
	RTS_I32 writeLocks;
	
	void *pBPContext;
	RTS_UI32 ulCompilerVersion;
	/* ATTENTION: Always append new elements at the end of this structure! */
} APPLICATION;


#define COMPACT_DOWNLOAD_HEADER_TAG			UINT32_C(0x1234ABCD)
#define COMPACT_DOWNLOAD_HEADER_VERSION		UINT32_C(0x00000001)

/**
 * <SIL2/>
 * <category>Compact download header</category>
 * <description>
 *	This header is sent right at the beginning of each compact download stream
 * </description>
 *	<element name="ulHeaderTag" type="IN">Header tag = COMPACT_DOWNLOAD_HEADER_TAG</element>
 *	<element name="ulHeaderVersion" type="IN">Header version = COMPACT_DOWNLOAD_HEADER_VERSION</element>
 *	<element name="ulHeaderSize" type="IN">Header size</element>
 *	<element name="ulTotalSize" type="IN">Header size including all download segments</element>
 *	<element name="ulDeviceType" type="IN">Device type of the selected device</element>
 *	<element name="ulDeviceId" type="IN">Device ID of the selected device</element>
 *	<element name="ulDeviceVersion" type="IN">Device version of the selected device</element>
 *	<element name="ulFlags" type="IN">Download flags (LOW Word), Application flags (HIGH Word). See corresponding categories.</element>
 *	<element name="ulCompilerVersion" type="IN">Compiler version of used CoDeSys version</element>
 *	<element name="ulCodeAreaSize" type="IN">Code area size</element>
 *	<element name="usCodeAreaIndex" type="IN">Code area index</element>
 *	<element name="usCodeAreaFlags" type="IN">Code area flags</element>
 *	<element name="ulOffsetCode" type="IN">Offset in bytes, where the code segment begins</element>
 *	<element name="ulSizeCode" type="IN">Size in bytes of the code segment</element>
 *	<element name="ulOffsetApplicationInfo" type="IN">Offset in bytes, where the application info segment begins</element>
 *	<element name="ulSizeApplicationInfo" type="IN">Size in bytes of the application info segment</element>
 *	<element name="ulOffsetAreaTable" type="IN">Offset in bytes, where the area table segment begins</element>
 *	<element name="ulSizeAreaTable" type="IN">Size in bytes of the area table segment</element>
 *	<element name="ulOffsetFunctionTable" type="IN">Offset in bytes, where the function table segment begins, Here the link function are specified:
 *																	- CodeInit
 *																	- GlobalInit
 *																	- GlobalExit
 *																	- Reloc
 *																	- DownloadCode
 *																	- TargetInfo
 *  </element>
 *	<element name="ulSizeFunctionTable" type="IN">Size in bytes of the function table segment</element>
 *	<element name="ulOffsetExternalFunctionTable" type="IN">Offset in bytes, where the external function table segment begins to link c functions against iec code</element>
 *	<element name="ulSizeExternalFunctionTable" type="IN">Size in bytes of the external function table segment</element>
 *	<element name="ulOffsetRegisterIecFunctionTable" type="IN">Offset in bytes, where the iec function table segment begins to link iec functions against the runtime system</element>
 *	<element name="ulSizeRegisterIecFunctionTable" type="IN">Size in bytes of the external function table segment</element>
 *	<element name="ulOffsetBlob" type="IN">Offset in bytes, where the optional blob segment begins</element>
 *	<element name="ulSizeBlob" type="IN">Size in bytes of the optional blob segment</element>
 *	<element name="ulCrc" type="IN">CRC32 of the complete download stream including the header with ulCRC written to 0!</element>
 */
typedef struct _COMPACT_CODE_HEADER
{
    RTS_UI32 ulHeaderTag;
    RTS_UI32 ulHeaderVersion;
    RTS_UI32 ulHeaderSize;
    RTS_UI32 ulSizeInArea;
    RTS_UI32 ulDeviceType;
    RTS_UI32 ulDeviceId;
    RTS_UI32 ulDeviceVersion;
    RTS_UI32 ulFlags;
    RTS_UI32 ulCompilerVersion;
    RTS_UI32 ulCodeAreaSize;
    RTS_UI16 usCodeAreaIndex;
    RTS_UI16 usCodeAreaFlags;
    RTS_UI32 ulOffsetCode;
    RTS_UI32 ulTotalSize;
    RTS_UI32 ulOffsetApplicationInfo;
    RTS_UI32 ulSizeApplicationInfo;
    RTS_UI32 ulOffsetAreaTable;
    RTS_UI32 ulSizeAreaTable;
    RTS_UI32 ulOffsetFunctionTable;
    RTS_UI32 ulSizeFunctionTable;
    RTS_UI32 ulOffsetExternalFunctionTable;
    RTS_UI32 ulSizeExternalFunctionTable;
    RTS_UI32 ulOffsetRegisterIecFunctionTable;
    RTS_UI32 ulSizeRegisterIecFunctionTable;
    RTS_UI32 ulOffsetBlob;
    RTS_UI32 ulSizeBlob;
    RTS_UI32 ulCrc;
} COMPACT_CODE_HEADER;


typedef struct _COMPACT_BLOB_HEADER
{
    RTS_UI32 ulBlobMagic;   /* must be BLOB_MAGIC */
    RTS_UI32 ulBlobID;      /* id from compact blob provider plugin */
    RTS_UI32 ulBlobSize;    /* size of payload */
} COMPACT_BLOB_HEADER;

#define BLOB_MAGIC 0xB70BC0DE

/*
 * <description>Commands controlling the downloading and loading of a user created dynamic runtime module (C-Integration)</description>
 */
typedef enum
{
	DRMC_Append = 0,
	DRMC_Create = 1,
	DRMC_Load	= 2
} DynamicRTSModuleCmd;

/*
 * <description>The type of a user created dynamic runtime module (C-Integration)</description>
 */
typedef enum
{
	DRMT_SourceModule = 0,
	DRMT_LibraryModule = 1
} DynamicRTSModuleType;

#define DEFAULT_CINTGR_POOL_SIZE	5
/**
 * <description>
 *	Contains information about the loaded modules from the C-Integration
 * </description>
 */
typedef struct
{
	char *name;
	char *filePath;
	char *libId;
	DynamicRTSModuleType type;
} DownloadedRtsModule;

/**
 * <category>Reset options</category>
 * <description>
 *	Warm reset. All gobal data except retain data is reset to their default values.
 * </description>
 */
#define RTS_RESET					0

/**
 * <category>Reset options</category>
 * <description>
 *	Cold reset. All gobal data AND retain data is reset to their default values.
 * </description>
 */
#define RTS_RESET_COLD				1

/**
 * <category>Reset options</category>
 * <description>
 *	Origin reset. Delete the application, delete all application files (bootproject, etc.),
 *	reset all gobal and retain data. After this command, the controller doesn't know anything about
 *	the application.</description>
 */
#define RTS_RESET_ORIGIN			2

/**
 * <category>Reset options</category>
 * <description>
 *	Origin reset device. Delete all applications, delete all application files (bootproject, etc.),
 *	reset all gobal and retain data. Clear $visu$ and $PlcLogic$ folders. After this command, the
 *	controller doesn't know anything about any application.</description>
 */
#define RTS_RESET_ORIGIN_DEVICE		3

/**
 * <category>Online services</category>
 * <description>
 * </description>
 */
#define SRV_LOGIN_APP					0x01
#define SRV_LOGOUT_APP					0x02
#define SRV_CREATEAPP					0x03
#define SRV_DELETEAPP					0x04
#define SRV_DOWNLOAD					0x05 
#define SRV_ONLINECHANGE				0x06
#define SRV_DEVICEDOWNLOAD				0x07
#define SRV_CREATEDEVAPP				0x08
#define SRV_START						0x10
#define SRV_STOP						0x11
#define SRV_RESET						0x12
#define SRV_SETBP						0x13
#define SRV_READ_STATUS					0x14
#define SRV_DELETEBP					0x15
#define SRV_READ_CALLSTACK				0x16
#define SRV_GET_AREAOFFSET				0x17
#define SRV_READ_APPLICATION_LIST		0x18
#define SRV_SETNEXTSTATEMENT			0x19
#define SRV_RELEASE_FORCELIST			0x20
#define SRV_UPLOAD_FORCELIST			0x21
#define SRV_SINGLE_CYCLE				0x22
#define SRV_CREATE_BOOTPROJECT			0x23
#define SRV_REINITAPP					0x24
#define SRV_READ_APPL_STATE_LIST		0x25
#define SRV_LOAD_BOOTAPPLICATION		0x26
#define SRV_REGISTER_BOOTAPPLICATION	0x27
#define SRV_APP_CHECK_FILE_CONSISTENCY	0x28
#define SRV_READ_APPLICATION_INFO		0x29
#define SRV_DOWNLOAD_COMPACT			0x30
#define SRV_READ_PROJECT_INFO			0x31
#define SRV_DEFINE_FLOW					0x32
#define SRV_READ_FLOW_VALUES			0x33
#define SRV_DOWNLOADENCRYPTED			0x34
#define SRV_READ_APPLICATION_CONTENT    0x35
#define SRV_SAVE_RETAINS				0x36
#define SRV_RESTORE_RETAINS				0x37
#define SRV_GET_AREA_ADDRESS			0x38
#define SRV_LEAVE_EXECPOINTS_ACTIVE		0x39
#define SRV_CLAIM_EXECPOINTS_FOR_APP	0x40



/**
 * <category>Online tags</category>
 * <description>
 * </description>
 */
#define TAG_DATA_AREA					0x01
#define TAG_CODE						0x02
#define TAG_CODE_SUBT					0x82
#define TAG_TASK_INFO					0x03
#define TAG_TASK_INFO_SUBT				0x83
#define TAG_USED_IO						0x04
#define TAG_EXT_REF						0x85
#define TAG_EXT_REF_SUBT				0x85
#define TAG_END_DL						0x06
#define TAG_END_DL_SUBT					0x86
#define TAG_APPLICATION_INFO			0x87
#define TAG_APPLICATION_INFO_SUBT		0x87
#define TAG_PROJECT_INFO				0x88
#define TAG_CUSTOM_DOWNLOAD				0x89
#define TAG_RESULT_CUSTOM_DOWNLOAD		0x07
#define TAG_SEQUENZNUMBER				0x09

#define TAG_POU							0xA0
#define TAG_POU_INFO					0x21
#define TAG_POU_CODE					0x22
#define TAG_POU_DESC					0x23
#define TAG_CODE_INFO					0x24
#define TAG_PERIODIC_TASK				0x30
#define TAG_FUNCTION_REF_OLD			0x50
#define TAG_FUNCTION_REF				0x80
#define TAG_FUNCTION_REF_HEADER			0x01
#define TAG_FUNCTION_REF_NAME			0x02
#define TAG_SYS_APPLICATION_REF_NAME	0x03
#define TAG_CODE_INIT					0x60
#define TAG_GLOBAL_INIT					0x61
#define TAG_RELOC						0x62
#define TAG_DOWNLOAD_POU				0x63
#define TAG_GLOBAL_EXIT					0x64
#define TAG_TARGET_INFO					0x65
#define TAG_PS_VERSION					0x66
#define TAG_TARGET_SETTING_VERSION		0x67
#define TAG_TARGET_PREV_AREA			0x68
#define TAG_TARGET_FUNC_REF_RES			0x69
#define TAG_DOWNLOAD_CODE				0x6A
#define TAG_MEMORY_SEGMENT_INFO			0x6B
#define TAG_OC_CONCURRENT_BEFORE		0x6C
#define TAG_OC2_REPEATABLE				0x6D
#define TAG_APPLICATION_FLAGS			0x6E
#define TAG_APPLICATION_CONTENT			0x6F
#define TAG_OC_CONCURRENT_AFTER			0x70
#define TAG_CODE_LOCATION_INFO			0x71
#define TAG_APPLICATION_DOWNLOAD_CRC    0x72
#define TAG_CPL_VERSION					0x73
#define TAG_ENCRYPTIONINFO				0x08

#define TAG_FUNCTION_IEC_SUBT			0x88
#define TAG_FUNCTION_IEC				0x88
#define TAG_FUNCTION_INFO				0x01
#define TAG_FUNCTION_NAME				0x02

#define TAG_DYNMOD_SUBT					0xB0
#define TAG_DYNMOD						0xB0
#define TAG_DYNMOD_CMD					0x01
#define TAG_DYNMOD_CODE					0x02
#define TAG_DYNMOD_NAME					0x04
#define TAG_DYNMOD_TYPE					0x05
#define TAG_DYNMOD_LIBID				0x06
#define TAG_DYNMOD_CMNAME				0x07

#define TAG_APPENCRYPTIONINFO			0x8A
#define TAG_APPENCRYPTIONINFO_DATA		0x01
#define TAG_APPENCRYPTIONINFO_SIGNATURE 0x02

#define TAG_APPL_BPINFO					0x12
#define TAG_APPL_CONDITION				0x13
#define TAG_APPL_FLOW_CONDITION_EXT     0x14
#define TAG_APPL_CONDITION_EXT			0x15
#define TAG_APPL_INTERP_CODE			0x16
#define TAG_APPL_EXECUTIONPOINT			0x17
#define TAG_APPL_EP_ACTIVE_STNG			0x18
#define TAG_APPL_EP_CRC					0x19
#define TAG_APPL_BPDATAINFO				0x1A

#define TAG_APPL_FLOWINFO				0x82
#define TAG_MON_VARS					0x15
#define TAG_FLOW_POSITION				0x16
#define TAG_FLOW_VALUE					0x83
#define TAG_FLOW_VALUE_INFO				0x13
#define READ_FLOW_REPLY					0x17
#define TAG_EMBEDDED_MONITORING2_EXP    0x18

#define TAG_BOOTPROJECT					0xB30
#define TAG_BOOTPROJECT2				0x81

#define TAG_BOOTPROJECT_APP_NAME		0x70
#define TAG_BOOTPROJECT_APP_GUIDS		0x71
#define TAG_BOOTPROJECT_PARENT_NAME		0x72
#define TAG_BOOTPROJECT_PARENT_GUIDS	0x73
#define TAG_BOOTPROJECT_SESSIONID		0x74
#define TAG_BOOTPROJECT_TARGETID		0x75
#define TAG_BOOTPROJECT_TARGETVERSION	0x76
#define TAG_BOOTPROJECT_TARGETTYPE		0x77

#define TAG_APPLICATION_NOT_CREATED		0x75

#define TAG_ARCHIVE_INFO				0x87

#define TAG_CHECK_SINGLE_CYCLE			0x01

#define TAG_APPL_LOGINTOAPP				0x01
#define TAG_APPL_LOGINTOAPP_SUBT		0x81
#define TAG_APPL_APPLICATIONDESC		0x81
#define TAG_APPL_APPLNAME				0x10
#define TAG_APPL_RIGHTS					0x11
#define TAG_APPL_PARENT_APPLNAME		0x12
#define TAG_APPL_RETAIN_FILENAME		0x13
#define TAG_APPL_RETAIN_STATE			0x14

#define TAG_PROJECT_NAME				0x01
#define TAG_VERSION						0x02
#define TAG_DATE_OF_LAST_MODIFICATION	0x03
#define TAG_AUTHOR						0x04
#define TAG_DESCRIPTION					0x05
#define TAG_PROFILE						0x06
#define TAG_TITLE						0x07
#define TAG_COMPILER_VERSION			0x08

#define TAG_APPL_SESSION_ID				0x00
#define TAG_APPL_RESET_OPTION			0x10
#define TAG_APPL_ID						0x11
#define TAG_APPL_APPLPERSISTENTINFO		0x12
#define TAG_APPL_AREA_INDEX				0x13
#define TAG_APPL_AREA_ADDRESS			0x14

#define TAG_APPLIST						0x01
#define TAG_APPLIST_WITHINFO			0x06
#define TAG_APPLIST_RESPONSE_SUBT		0x81
#define TAG_APPLIST_RESPONSE_STARTINDEX	0x02
#define TAG_APPLIST_RESPONSE_NAME		0x03
#define TAG_APPLIST_RESPONSE_STATEANDNAME	0x04

#define TAG_ERROR_RESPONSE				0x01

#define READ_STATUS_REPLY				0x82
#define READ_STATUS_RESULT				0x13
#define READ_STATUS_EXECUTIONPOSITION	0x14
#define READ_STATUS_BPHITCOUNT			0x15
#define READ_STATUS_INSTANCEPOSITION	0x16
#define READ_STATUS_DEBUGTASK			0x17
#define READ_STATUS_VERSION				0x18
#define READ_USER_NOTIFY				0x19
#define TAG_APPL_TASK_INDEX				0x1A
#define READ_STATUS_LAST_CHANGE			0x1B
#define READ_STATUS_DATABP_POSITION		0x1C
#define READ_STATUS_BPHITCOUNTEX		0x20
#define READ_STATUS_STACKPOINTER		0x21
#define TAG_OPERATION_MODE				0x32

#define SRV_SETNEXT_INFO				0x81
#define SRV_SETNEXT_APPLICATION			0x11
#define SRV_SETNEXT_POSITION			0x12
#define SRV_SETNEXT_REGISTERINFO		0x13

/**
 * <category>Online services</category>
 * <Description>
 *	ReadStatus service. Returns status information about the active Task of the current Application.
 *	TAG_APPL_TASK_INDEX may be optionally transferred preceding TAG_APPL_ID to request a specific task.
 * </Description>
 * <service name="SRV_READ_STATUS">
 *	<Request>
 *		<tag name="TAG_APPL_APPLICATIONDESC" required="mandatory">Top level tag</tag>
 *			<tag name="TAG_APPL_TASK_INDEX" required="optional">[RTS_UI32]: Task index</tag>
 *			<tag name="TAG_APPL_ID" required="mandatory">[RTS_UI32]: Session ID; triggers READ_STATUS_RESULT, READ_STATUS_EXECUTIONPOSITION, READ_STATUS_BPHITCOUNT, READ_STATUS_BPHITCOUNTEX</tag>
 *			<tag name="READ_STATUS_VERSION" required="optional">triggers READ_STATUS_INSTANCEPOSITION, READ_STATUS_DEBUGTASK</tag>
 *			<tag name="READ_USER_NOTIFY" required="optional">triggers READ_USER_NOTIFY</tag>
 *	</Request>
 *	<Response>
 *		<tag name="READ_STATUS_REPLY" required="mandatory">Top level tag may contain the following sub tags</tag>
 *			<tag name="READ_STATUS_RESULT" required="optional">[RTS_UI16, RTS_UI32, RTS_UI32]: Result code, App state, App OpState</tag>
 *			<tag name="READ_STATUS_EXECUTIONPOSITION" required="optional">[RTS_UI16, RTS_UI32]: Area, Offset of callstackEntry</tag>
 *			<tag name="READ_STATUS_DATABP_POSITION" required="optional">[RTS_UI16, RTS_UI32]: Area, Offset of reched data breakpoint</tag>
 *			<tag name="READ_STATUS_BPHITCOUNT" required="optional">[RTS_UI32]: HitCount</tag>
 *			<tag name="READ_STATUS_BPHITCOUNTEX" required="optional">[RTS_UI16, RTS_UI16, RTS_UI32, RTS_UI32]: Area, state, Offset, current hitcount of BP</tag>
 *			<tag name="READ_STATUS_INSTANCEPOSITION" required="optional">[RTS_UI16, RTS_UI32]: AreaInstance, OffsetInstance of callstackEntry</tag>
 *			<tag name="READ_STATUS_DEBUGTASK" required="optional">[RTS_UI16]: DebugTaskIdx</tag>
 *			<tag name="READ_USER_NOTIFY" required="optional">[...]: Response of SrvGetUserNotificationService2</tag>
 *		<tag name="TAG_OPERATION_MODE" required="optional">[RTS_UI32]: Device operation mode</tag>
 *	</Response>
 * </service>
 */
 
/**
 * <category>Online services</category>
 * <Description>
 *	ReadStatus service. Returns callstack information about the active Task of the current Application.
 *	TAG_APPL_TASK_INDEX may be optionally transferred preceding TAG_APPL_ID to request a specific task.
 * </Description>
 * <service name="SRV_READ_CALLSTACK">
 *	<Request>
 *		<tag name="TAG_APPL_APPLICATIONDESC" required="mandatory">Top level</tag>
 *			<tag name="TAG_APPL_TASK_INDEX" required="optional">[RTS_UI32]: Task index</tag>
 *			<tag name="TAG_APPL_ID" required="mandatory">[RTS_UI32]: Session ID</tag>
 *	</Request>
 *	<Response>
 *		<tag name="READ_STATUS_REPLY" required="mandatory">Top level tag may contain the following sub tags</tag>
 *			<tag name="READ_STATUS_STACKPOINTER" required="optional">[RTS_UINTPTR]: Stackpointer</tag>
 *			<tag name="READ_STATUS_EXECUTIONPOSITION" required="optional">[RTS_UI16, RTS_UI32]: Area, Offset of callstackEntry</tag>
 *			<tag name="READ_STATUS_INSTANCEPOSITION" required="optional">[RTS_UI16, RTS_UI32]: AreaInstance, OffsetInstance of callstackEntry</tag>
 *	</Response>
 * </service>
 */

 
/**
 * <category>Online reply tags</category>
 * <description>
 * </description>
 */
#define TAG_REPLY_EXTERNAL_REFERENCE_ERROR_LIST		0x01
#define TAG_REPLY_EXTERNAL_REFERENCE_RESULT			0x02
#define TAG_REPLY_SYS_APP_ERROR_LIST				0x03


/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <category>Application memory segment</category>
 * * <description>
 * *	Describes a memory segment of an application.
 * * </description>
 * * <element name="wType" type="IN">Type of the segment. See category "Area Types" in SysMemItf.h.</element>
 * * <element name="wArea" type="IN">Area in which the segment is residing</element>
 * * <element name="dwOffset" wType="IN">Offset in the area, in which the segment is residing</element>
 * * <element name="dwSize" wType="IN">Size of the segment in bytes</element>
 * * <element name="dwHighestUsedAddress" wType="IN">Highest used address in the segment (has no significance for input, output, memory)</element>
 */
typedef struct tagAPP_MEMORY_SEGMENT
{
	RTS_IEC_WORD wType;		
	RTS_IEC_WORD wArea;		
	RTS_IEC_DWORD dwOffset;		
	RTS_IEC_DWORD dwSize;		
	RTS_IEC_DWORD dwHighestUsedAddress;		
} APP_MEMORY_SEGMENT;

/**
 * <description>appcallgetproperty</description>
 */
typedef struct tagappcallgetproperty_struct
{
	RTS_IEC_BYTE *pInstance;			/* VAR_INPUT */	
	RTS_IEC_BYTE **ppGetMethod;			/* VAR_INPUT */	
	RTS_IEC_BYTE *pbyValue;				/* VAR_INPUT */	
	RTS_IEC_XWORD ulSize;				/* VAR_INPUT */	
	RTS_IEC_RESULT AppCallGetProperty;	/* VAR_OUTPUT */	
} appcallgetproperty_struct;

DEF_API(`void',`CDECL',`appcallgetproperty',`(appcallgetproperty_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD99D7FC0),0x03050B00)

/**
 * <description>appcallgetproperty2</description>
 */
typedef struct tagappcallgetproperty2_struct
{
	RTS_IEC_BYTE *pInstance;			/* VAR_INPUT */	
	RTS_IEC_BYTE **ppGetMethod;			/* VAR_INPUT */	
	RTS_IEC_BYTE **ppbyValue;			/* VAR_INPUT */	
	RTS_IEC_XWORD ulSize;				/* VAR_INPUT */	
	RTS_IEC_RESULT AppCallGetProperty2;	/* VAR_OUTPUT */	
} appcallgetproperty2_struct;

DEF_API(`void',`CDECL',`appcallgetproperty2',`(appcallgetproperty2_struct *p)',1,RTSITF_GET_SIGNATURE(0xD878B9FD, 0x689760F7),0x03050B00)

/**
 * <description>appcallgetproperty2release</description>
 */
typedef struct tagappcallgetproperty2release_struct
{
	RTS_IEC_BYTE *pbyValue;				/* VAR_INPUT */	
	RTS_IEC_RESULT AppCallGetProperty2Release;	/* VAR_OUTPUT */	
} appcallgetproperty2release_struct;

DEF_API(`void',`CDECL',`appcallgetproperty2release',`(appcallgetproperty2release_struct *p)',1,0x664A62E3,0x03050B00)

/**
 * <description>appcallsetproperty</description>
 */
typedef struct tagappcallsetproperty_struct
{
	RTS_IEC_BYTE *pInstance;			/* VAR_INPUT */	
	RTS_IEC_BYTE **ppSetMethod;			/* VAR_INPUT */	
	RTS_IEC_BYTE *pbyValue;				/* VAR_INPUT */	
	RTS_IEC_XWORD ulSize;				/* VAR_INPUT */	
	RTS_IEC_RESULT AppCallSetProperty;	/* VAR_OUTPUT */	
} appcallsetproperty_struct;

DEF_API(`void',`CDECL',`appcallsetproperty',`(appcallsetproperty_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF7790D93),0x03050B00)

/**
 * <description>appfindapplicationbyname</description>
 */
typedef struct tagappfindapplicationbyname_struct
{
	RTS_IEC_STRING *pszString;			/* VAR_INPUT */	/* Application name */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	APPLICATION *AppFindApplicationByName;	/* VAR_OUTPUT */	
} appfindapplicationbyname_struct;

DEF_API(`void',`CDECL',`appfindapplicationbyname',`(appfindapplicationbyname_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xDAD101B7),0x03050B00)

/**
 * <description>appgenerateexception</description>
 */
typedef struct tagappgenerateexception_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_DWORD ulException;			/* VAR_INPUT */	
	RTS_IEC_RESULT AppGenerateException;	/* VAR_OUTPUT */	
} appgenerateexception_struct;

DEF_API(`void',`CDECL',`appgenerateexception',`(appgenerateexception_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xCAFA8E41),0x03050B00)

/**
 * <description>appgetapplicationbyareaaddress</description>
 */
typedef struct tagappgetapplicationbyareaaddress_struct
{
	RTS_IEC_UDINT *pAddress;			/* VAR_INPUT */	
	APPLICATION *AppGetApplicationByAreaAddress;	/* VAR_OUTPUT */	
} appgetapplicationbyareaaddress_struct;

DEF_API(`void',`CDECL',`appgetapplicationbyareaaddress',`(appgetapplicationbyareaaddress_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x7EE9B1A3),0x03050B00)

/**
 * <description>appgetapplicationinfo</description>
 */
typedef struct tagappgetapplicationinfo_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	APPLICATION_INFO *AppGetApplicationInfo;	/* VAR_OUTPUT */	
} appgetapplicationinfo_struct;

DEF_API(`void',`CDECL',`appgetapplicationinfo',`(appgetapplicationinfo_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x49DD3432),0x03050B00)

/**
 * <description>appgetareaaddress</description>
 */
typedef struct tagappgetareaaddress_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_UINT uiType;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_BYTE *AppGetAreaAddress;	/* VAR_OUTPUT */	
} appgetareaaddress_struct;

DEF_API(`void',`CDECL',`appgetareaaddress',`(appgetareaaddress_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x6C9E6C94),0x03050B00)

/**
 * <description>appgetareaoffsetbyaddress</description>
 */
typedef struct tagappgetareaoffsetbyaddress_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_UXINT ulAddress;			/* VAR_INPUT */	
	RTS_IEC_WORD *pusArea;				/* VAR_INPUT */	
	RTS_IEC_XWORD *pulOffset;			/* VAR_INPUT */	
	RTS_IEC_RESULT AppGetAreaOffsetByAddress;	/* VAR_OUTPUT */	
} appgetareaoffsetbyaddress_struct;

DEF_API(`void',`CDECL',`appgetareaoffsetbyaddress',`(appgetareaoffsetbyaddress_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x356243D6),0x03050B00)

/**
 * <description>appgetareapointer</description>
 */
typedef struct tagappgetareapointer_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_DINT diArea;				/* VAR_INPUT */	
	RTS_IEC_BYTE **ppbyArea;			/* VAR_INPUT */	
	RTS_IEC_RESULT AppGetAreaPointer;	/* VAR_OUTPUT */	
} appgetareapointer_struct;

DEF_API(`void',`CDECL',`appgetareapointer',`(appgetareapointer_struct *p)',1,0x6AC4CD9A,0x03050B00)

/**
 * <description>appgetareasize</description>
 */
typedef struct tagappgetareasize_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_UINT uiType;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_XWORD AppGetAreaSize;		/* VAR_OUTPUT */	
} appgetareasize_struct;

DEF_API(`void',`CDECL',`appgetareasize',`(appgetareasize_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x362BAF2A),0x03050B00)

/**
 * <description>appgetcurrent</description>
 */
typedef struct tagappgetcurrent_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	APPLICATION *AppGetCurrent;			/* VAR_OUTPUT */	
} appgetcurrent_struct;

DEF_API(`void',`CDECL',`appgetcurrent',`(appgetcurrent_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x9EE77745),0x03050B00)

/**
 * <description>appgetfirstapp</description>
 */
typedef struct tagappgetfirstapp_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	APPLICATION *AppGetFirstApp;		/* VAR_OUTPUT */	
} appgetfirstapp_struct;

DEF_API(`void',`CDECL',`appgetfirstapp',`(appgetfirstapp_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x75BD6F20),0x03050B00)

/**
 * <description>appgetnextapp</description>
 */
typedef struct tagappgetnextapp_struct
{
	APPLICATION *pAppPrev;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	APPLICATION *AppGetNextApp;			/* VAR_OUTPUT */	
} appgetnextapp_struct;

DEF_API(`void',`CDECL',`appgetnextapp',`(appgetnextapp_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD98C0DF3),0x03050B00)

/**
 * <description>appgetprojectinformation</description>
 */
typedef struct tagappgetprojectinformation_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	PROJECT_INFO *pInfo;				/* VAR_INPUT */	
	RTS_IEC_RESULT AppGetProjectInformation;	/* VAR_OUTPUT */	
} appgetprojectinformation_struct;

DEF_API(`void',`CDECL',`appgetprojectinformation',`(appgetprojectinformation_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA736D4E6),0x03050B00)

/**
 * <description>appgetsegment</description>
 */
typedef struct tagappgetsegment_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_UINT uiType;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	APP_MEMORY_SEGMENT *AppGetSegment;	/* VAR_OUTPUT */	
} appgetsegment_struct;

DEF_API(`void',`CDECL',`appgetsegment',`(appgetsegment_struct *p)',1,0xE7291359,0x03050B00)

/**
 * <description>
 *	This function retuns the start address of an IEC segment. All segments resides within an area.
 *	This is used to get access for example to the beginning of the output processimage segment (%Q = AreaType.DA_OUTPUT).
 * </description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="wType" type="IN">Area type</param>
 * <param name="pResult" type="IN">Pointer to Result</param>
 * <result>Segment start address</result>
 */
typedef struct tagappgetsegmentaddress_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_WORD wType;					/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_BYTE *AppGetSegmentAddress;	/* VAR_OUTPUT */	
} appgetsegmentaddress_struct;

DEF_API(`void',`CDECL',`appgetsegmentaddress',`(appgetsegmentaddress_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA1837EC1),0x03050B00)

/**
 * <description>
 *	This function retuns the start size of an IEC segment. All segments resides within an area.
 *	This is used to get access for example to the size of the output processimage segment (%Q = AreaType.DA_OUTPUT).
 * </description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="wType" type="IN">Area type</param>
 * <param name="pResult" type="IN">Pointer to Result</param>
 * <result>Segment size</result>
 */
typedef struct tagappgetsegmentsize_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_WORD wType;					/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_UXINT AppGetSegmentSize;	/* VAR_OUTPUT */	
} appgetsegmentsize_struct;

DEF_API(`void',`CDECL',`appgetsegmentsize',`(appgetsegmentsize_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC1200062),0x03050B00)

/**
 * <description>appnumofactivesessions</description>
 */
typedef struct tagappnumofactivesessions_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_UDINT *pulNumSessions;		/* VAR_INPUT */	
	RTS_IEC_RESULT AppNumOfActiveSessions;	/* VAR_OUTPUT */	
} appnumofactivesessions_struct;

DEF_API(`void',`CDECL',`appnumofactivesessions',`(appnumofactivesessions_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x28A577B6),0x03050B00)

/**
 * <description>appregisterpropaccessfunctions</description>
 */
typedef struct tagappregisterpropaccessfunctions_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_BYTE **ppfGetBooleanProperty;	/* VAR_INPUT */	
	RTS_IEC_BYTE **ppfGetTextProperty;	/* VAR_INPUT */	
	RTS_IEC_BYTE **ppfGetNumberProperty;	/* VAR_INPUT */	
	RTS_IEC_BYTE **ppfGetVersionProperty;	/* VAR_INPUT */	
	RTS_IEC_RESULT AppRegisterPropAccessFunctions;	/* VAR_OUTPUT */	
} appregisterpropaccessfunctions_struct;

DEF_API(`void',`CDECL',`appregisterpropaccessfunctions',`(appregisterpropaccessfunctions_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF72A3B0A),0x03050B00)

/**
 * <description>appreset</description>
 */
typedef struct tagappreset_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_WORD usResetOption;			/* VAR_INPUT */	
	RTS_IEC_RESULT AppReset;			/* VAR_OUTPUT */	
} appreset_struct;

DEF_API(`void',`CDECL',`appreset',`(appreset_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x03B85B28),0x03050B00)

/**
 * <description>apprestoreretainsfromfile</description>
 */
typedef struct tagapprestoreretainsfromfile_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_STRING *pszFilName;			/* VAR_INPUT */	
	RTS_IEC_RESULT AppRestoreRetainsFromFile;	/* VAR_OUTPUT */	
} apprestoreretainsfromfile_struct;

DEF_API(`void',`CDECL',`apprestoreretainsfromfile',`(apprestoreretainsfromfile_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x32542AD7),0x03050B00)

/**
 * <description>appstartapplication</description>
 */
typedef struct tagappstartapplication_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_RESULT AppStartApplication;	/* VAR_OUTPUT */	
} appstartapplication_struct;

DEF_API(`void',`CDECL',`appstartapplication',`(appstartapplication_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x71CC8510),0x03050B00)

/**
 * <description>appstopapplication</description>
 */
typedef struct tagappstopapplication_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_RESULT AppStopApplication;	/* VAR_OUTPUT */	
} appstopapplication_struct;

DEF_API(`void',`CDECL',`appstopapplication',`(appstopapplication_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xEE13E070),0x03050B00)

/**
 * <description>appstoreretainsinfile</description>
 */
typedef struct tagappstoreretainsinfile_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_STRING *pszFilName;			/* VAR_INPUT */	
	RTS_IEC_RESULT AppStoreRetainsInFile;	/* VAR_OUTPUT */	
} appstoreretainsinfile_struct;

DEF_API(`void',`CDECL',`appstoreretainsinfile',`(appstoreretainsinfile_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xCBCA082E),0x03050B00)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <category>Application memory segment information</category>
 * <description>
 *	Describes all memory segments of an application.
 * </description>
 * <element name="diSegments" type="IN">Number of segments</element>
 * <element name="pmsList" type="IN">Pointer to memory segment list</element>
 */
typedef struct _APP_MEMORY_SEGMENT_INFO
{
	RTS_IEC_DINT diSegments;
	APP_MEMORY_SEGMENT *pmsList;
} APP_MEMORY_SEGMENT_INFO;

typedef struct 
{
	APPLICATION *pApp;
	RTS_IEC_RESULT *pBootprojectConsistency;
	RTS_IEC_RESULT *pArchiveConsistency;
	RTS_IEC_RESULT AppCheckFileConsistency;
} appcheckfileconsistency_struct;

DEF_API(`void',`CDECL',`appcheckfileconsistency',`(appcheckfileconsistency_struct *p)',1,0)

/**
 * <description>Creates an application specified by name</description>
 * <param name="pszAppName" type="IN">Pointer to name of the application</param>
 * <param name="pszAppParentName" type="IN">Pointer to name of the parent application (if a child application should be created). Can be NULL.</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the application description</result>
 */
DEF_ITF_API(`APPLICATION*', `CDECL', `AppCreateApplication', `(char* pszAppName, char* pszAppParentName, RTS_RESULT *pResult)')

/**
 * <description>Prepares a new download or online-change</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="bOnlineChange" type="IN">1=Online change, 0=Download</param>
 * <param name="bCreateBootproject" type="IN">1=Create implicitly a bootproject, 0=Create no bootproject</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppPrepareDownload', `(APPLICATION* pApp, int bOnlineChange, int bCreateBootproject)')

/**
 * <description>Append IEC code for each code fragment.
 *	NOTE: Actually only available for CmpAppEmbedded!	
 * </description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="pbyCode" type="IN">Pointer to code part</param>
 * <param name="ulCodeLen" type="IN">Code fragment length</param>
 * <param name="ulCodeOffset" type="IN">Code offset of the fragment, to write to</param>
 * <param name="bLoadBootproject" type="IN">1=Function is called at loading bootproject, 0=Else (e.g. at download sequence)</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppAppendCode', `(APPLICATION *pApp, RTS_UI8 *pbyCode, RTS_SIZE ulCodeLen, RTS_SIZE ulCodeOffset, int bLoadBootproject)')

/**
 * <description>Complete the download and init application.
 *	NOTE: Actually only available for CmpAppEmbedded!	
 * </description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="bOnlineChange" type="IN">1=Online change, 0=Download</param>
 * <param name="pWriter" type="IN">Pointer to the online writer. Can be NULL.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppCompleteDownload', `(APPLICATION* pApp, int bOnlineChange, BINTAGWRITER *pWriter)')

/**
 * <description>Retrieves an application by name</description>
 * <param name="pszAppName" type="IN" range="[NULL,VALID_APPNAME]">Pointer to name of the application</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Application successfully retrieved</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Parameter pszAppName may not be null</errorcode>
 * <result>Pointer to the application description, null if no App could not be found</result>
 */
DEF_ITF_API(`APPLICATION*', `CDECL', `AppFindApplicationByName', `(char *pszAppName, RTS_RESULT *pResult)')

/**
 * <description>Retrieves the number of active sessions for an application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="pulNumSessions" type="OUT">Pointer to variable for storing the number of active sessions</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Number of active sessions successfully retrieved</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Parameters pApp and pulNumSessions may not be null</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppNumOfActiveSessions', `(APPLICATION *pApp, RTS_UI32* pulNumSessions)')


/**
 * <description>Retrieves an application by name</description>
 * <param name="pszBootprojectName" type="IN">Pointer to name of the bootproject. Must not be the application name!</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the application description</result>
 */
DEF_ITF_API(`APPLICATION*', `CDECL', `AppFindApplicationByBootproject', `(char *pszBootprojectName, RTS_RESULT *pResult)')

/**
 * <description>Retrieves an application by session id. The session id is an unique id that is provided
 *	from the login service. There is a relation between the communication channel and the session id.</description>
 * <param name="ulSessionId" type="IN">SessionId from login service</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the application description</result>
 */
DEF_ITF_API(`APPLICATION*', `CDECL', `AppFindApplicationBySessionId', `(RTS_UI32 ulSessionId, RTS_RESULT *pResult)')

/**
 * <description>Retrieves an application by its id.</description>
 * <param name="iId" type="IN">Id of the application</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the application description</result>
 */
DEF_ITF_API(`APPLICATION*', `CDECL', `AppFindApplicationById', `(int iId, RTS_RESULT *pResult)')

/**
 * <description>Retrieves the number of registered and loaded applications.</description>
 * <result>Number of registered applications</result>
 */
DEF_ITF_API(`int',  `CDECL', `AppGetNumOfApplications', `(void)')

/**
 * <description>Retrieves an application description sepcified by index</description>
 * <param name="iIndex" type="IN" range="[0..APPL_NUM_OF_STATIC_APPLS-1,APPL_NUM_OF_STATIC_APPLS..INT_MAX]">Index of the application list.</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Application successfully retrieved</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Application with index iIndex not found</errorcode>
 * <result>Pointer to the application description</result>
 */
DEF_ITF_API(`APPLICATION*',  `CDECL', `AppGetApplicationByIndex', `(int iIndex, RTS_RESULT *pResult)')


/**
 * <description>Retrieves an application description which contains the specified memory address or NULL if failed (memory cannot be assiciated to an application)</description>
 * <param name="pAddress" type="IN">Pointer to memory</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the application description or NULL if memory pointer cannot be assiciated to an application</result>
 */
DEF_ITF_API(`APPLICATION *', `CDECL', `AppGetApplicationByAreaAddress', `(void *pAddress, RTS_RESULT *pResult)')

/**
 * <description>Retrieves the pointer to a memory area specified by index</description>
 * <param name="pApp" type="IN" range="[NULL,VALID_PAPP]">Pointer to the specified application description</param>
 * <param name="iArea" type="IN" range="[-1,VALID_AREA_TYPE,(APPL_NUM_OF_STATIC_AREAS - 1)]">Area index</param>
 * <param name="ppucArea" type="OUT">Pointer pointer to the area</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Pointer to Area successfully retrieved</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Parameter pApp may not be null, iArea may not be out of range: 0 - APPL_NUM_OF_STATIC_AREAS - 1</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Pointer to Area could not be retrieved</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppGetAreaPointer', `(APPLICATION *pApp, int iArea, unsigned char **ppucArea)')

/**
 * <description>Retrieves the pointer and size of a memory area specified by index</description>
 * <param name="pApp" type="IN" range="[NULL,VALID_PAPP]">Pointer to the specified application description</param>
 * <param name="iArea" type="IN" range="[-1,VALID_AREA_TYPE,(APPL_NUM_OF_STATIC_AREAS - 1)]">Area index</param>
 * <param name="ppucArea" type="OUT">Pointer pointer to the area. Can be NULL to get only the area size.</param>
 * <param name="pulSize" type="OUT">Pointer to size to return the area size. Can be NULL to get only the area address.</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Pointer to Area successfully retrieved</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Parameter pApp may not be null, iArea may not be out of range: 0 - APPL_NUM_OF_STATIC_AREAS - 1</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Pointer to Area could not be retrieved</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppGetAreaPointer2', `(APPLICATION *pApp, RTS_I32 iArea, RTS_UI8 **ppbyArea, RTS_SIZE *pulSize)')

/**
 * <description>Retrieves a pointer to the memory area specified by type and index</description>
 * <param name="pszAppName" type="IN">Application name</param>
 * <param name="iArea" type="IN">Area index</param>
 * <param name="usType" type="IN">Area type. See category "Area Types" in SysMemItf.h.</param>
 * <param name="ppucArea" type="OUT">Pointer pointer to the area</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppGetAreaPointerByType', `(char* pszAppName, int iArea, RTS_UI16 usType, unsigned char **ppucArea)')

/**
 * <description>Function checks, if the address is a part of the specified application (resides in an area)</description>
 * <param name="pApp" type="IN">Application</param>
 * <param name="pAddress" type="IN">Pointer to check. Can be a data pointer or a function pointer.</param>
 * <result>ERR_OK: pAddress is part of the specified application
 *		   ERR_FAILED: pAddress is not a part of the specified application
 * </result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppHasAddress', `(APPLICATION* pApp, RTS_VOID_FCTPTR pAddress)')

/**
 * <description>Returns the load state of an application</description>
 * <param name="pApp" type="IN" range="[NULL,VALID_PAPP]">Pointer to the specified application description</param>
 * <parampseudo name="pApp.ulOpState" type="IN" range="[OS_NONE,OS_PROGRAM_LOADED,OS_DOWNLOAD,OS_EXCEPTION]">Pointer to the specified application description</parampseudo>
 * <param name="pbProgramLoaded" type="OUT">Pointer to result. If the application contains
 *	a loaded project: *pbProgramLoaded is set to 1, else 0</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Load state of application successfully retrieved</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Parameter pApp and pbProgramLoaded may not be null</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppIsProgramLoaded', `(APPLICATION *pApp, int* pbProgramLoaded)')

/**
 * <description>Set the load state of an application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="bProgramLoaded" type="IN">1=Application is loaded, 0=Application is not loaded</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppSetProgramLoaded', `(APPLICATION *pApp, int bProgramLoaded)')

/**
 * <description>Activate a single cycle on the specified application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppSingleCycle', `(APPLICATION *pApp)')

/**
 * <description>Set the state of an application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="ulState" type="IN">State to set. See above for state specifications (prefix: AS_)</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppSetState', `(APPLICATION *pApp, unsigned long ulState)')

/**
 * <description>Returns the state of an application</description>
 * <param name="pApp" type="IN" range="[NULL,VALID_PAPP]">Pointer to the specified application description</param>
 * <parampseudo name="pApp.ulState" type="IN" range="[AS_NONE,AS_RUN]">Pointer to the specified application description</parampseudo>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">State of application successfully retrieved</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Parameter pApp may not be null</errorcode>
 * <result>State of the application. There could be several active states at the same time!
 *	See above for state specifications (prefix: AS_)</result>
 */
DEF_ITF_API(`unsigned long', `CDECL', `AppGetState', `(APPLICATION *pApp, RTS_RESULT *pResult)')

/**
 * <description>Set the operating state of an application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="ulOpState" type="IN">Operating state of an application. This is an information, which job or
 *	operating possibilities of the application are set actually. There could be several active opertating states 
 *	at the same time!</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppSetOperatingState', `(APPLICATION *pApp, unsigned long ulOpState)')

/**
 * <description>Reset a single operating state of an application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="ulOpState" type="IN">Operating state to reset</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppResetOperatingState', `(APPLICATION *pApp, unsigned long ulOpState)')

/**
 * <description>Get the operating state of an application</description>
 * <param name="pApp" type="IN" range="[VALID_PAPP,NULL]">Pointer to the specified application description</param>
 * <parampseudo name="pApp->ulOpState" type="IN" range="[OS_NONE,OS_PROGRAM_LOADED]">Application operating state</parampseudo>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Status retrieved successfully</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">pApp may not be null</errorcode>
 * <result>Operating state of an application</result>
 */
DEF_ITF_API(`unsigned long', `CDECL', `AppGetOperatingState', `(APPLICATION *pApp, RTS_RESULT *pResult)')

/**
 * <description>Sets the code id of the application. The code id is a unique number that
 *	specifies the code content of an application.</description>
 * <param name="pApp" type="IN" range="[NULL,VALID_PAPP]">Pointer to the specified application description</param>
 * <param name="pCodeGuid" type="IN" range="[NULL,VALID_PCODEGUID]">Pointer to code guid</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Code Guid was set successful</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Parameter may not be null</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppSetCodeGuid', `(APPLICATION *pApp, RTS_GUID *pCodeGuid)')

/**
 * <description>Retrieves the code id of the application. The code id is a unique number that
 *	specifies the code content of an application.</description>
 * <param name="pApp" type="IN" range="[NULL,VALID_PAPP]">Pointer to the specified application description</param>
 * <param name="pCodeGuid" type="OUT" range="[NULL,VALID_PCODEGUID]">Pointer to code guid</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Code Guid was set successfully</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Parameter may not be null</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppGetCodeGuid', `(APPLICATION *pApp, RTS_GUID *pCodeGuid)')

/**
 * <description>Sets the data id of the application. The data id is a unique number that
 *	specifies the data configuration of an application.</description>
 * <param name="pApp" type="IN" range="[NULL,VALID_PAPP]">Pointer to the specified application description</param>
 * <param name="pDataGuid" type="IN" range="[NULL,VALID_PDATAGUID]">Pointer to data guid</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Data Guid was set successful</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Parameter may not be null</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppSetDataGuid', `(APPLICATION *pApp, RTS_GUID *pDataGuid)')

/**
 * <description>Retrieves the data id of the application. The data id is a unique number that
 *	specifies the data configuration of an application.</description>
 * <param name="pApp" type="IN" range="[NULL,VALID_PAPP]">Pointer to the specified application description</param>
 * <param name="pDataGuid" type="OUT" range="[NULL,VALID_PDATAGUID]">Pointer to data guid</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Get data Guid was successfully</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Parameter may not be null</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppGetDataGuid', `(APPLICATION *pApp, RTS_GUID *pDataGuid)')

/**
 * <description>Retrieves the code and data guid of the bootproject of the given application.
 *	This function can be used to compare the guids of the loaded application with the bootproject.</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="pCodeGuid" type="OUT">Pointer to code guid</param>
 * <param name="pDataGuid" type="OUT">Pointer to data guid</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppGetBootprojectGuids', `(APPLICATION *pApp, RTS_GUID *pCodeGuid, RTS_GUID *pDataGuid)')

/**
 * <description>Exception handling of an application task. Must be called from another component, if an exception
 *	occurred in an IEC task. This routine is called typically by the CmpIecTask.</description>
 * <param name="pApp" type="IN">Pointer to the specified application description, in which the exception
 *	was generated.</param>
 * <param name="ulException" type="IN">Exception number to see, which exception was generated</param>
 * <param name="Context" type="IN">Context of the task. With this context it is possible to investigate
 *	the complete callstack to the code position, where the exception occurred</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppExceptionHandler', `(APPLICATION *pApp, RTS_UI32 ulException, RegContext Context)')

/**
 * <description>Executes a reset on the specified application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="usResetOption" type="IN">Reset option. See the category "Reset options" for detailed information</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppReset', `(APPLICATION* pApp, RTS_UI16 usResetOption, RTS_UI32 ulSessionId)')

/**
 * <description>Resets all applications</description>
 * <param name="usResetOption" type="IN">Reset option. See the category "Reset options" for detailed information</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppResetAllApplications', `(RTS_UI16 usResetOption)')

/**
 * <description>Load all registered bootprojects</description>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppLoadBootprojects', `(void)')

/**
 * <description>Start all registered bootprojects</description>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppStartBootprojects', `(void)')

/**
 * <description>Load a bootproject with the specified application name</description>
 * <param name="pszAppName" type="IN">Pointer to the NUL terminated application name</param>
 * <param name="pszFilePath" type="IN">File path for the bootproject</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppLoadBootproject', `(char *pszAppName, char *pszFilePath)')

/**
 * <description>Start all applications</description>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppStartApplications', `(void)')

/**
 * <description>Start an application</description>
 * <param name="pApp" type="IN">Pointer to the application</param>
 * <param name="ulStartReason" type="IN">Start reason, See corresponding category</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppStartApplication2', `(APPLICATION *pApp, RTS_UI32 ulStartReason)')

/**
 * <description>Start an application</description>
 * <param name="pApp" type="IN">Pointer to the application</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppStartApplication', `(APPLICATION *pApp)')

/**
 * <description>Stop all applications</description>
 * <param name="ulTimeoutMs" type="IN">Timeout in milliseconds to wait for stop. RTS_TIMEOUT_DEFAULT can be used as the default value</param>
 * <param name="ulStopReason" type="IN">Stop reason, See corresponding category</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppStopApplications', `(RTS_UI32 ulTimeoutMs, RTS_UI32 ulStopReason)')

/**
 * <description>Stop an application</description>
 * <param name="pApp" type="IN">Pointer to the application</param>
 * <param name="ulTimeoutMs" type="IN">Timeout in milliseconds to wait for stop. RTS_TIMEOUT_DEFAULT can be used as the default value</param>
 * <param name="ulStopReason" type="IN">Stop reason, See corresponding category</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppStopApplication', `(APPLICATION *pApp, RTS_UI32 ulTimeoutMs, RTS_UI32 ulStopReason)')

/**
 * <description>Exit an application (release all tasks, etc.). The application is not deleted!</description>
 * <param name="pApp" type="IN">Pointer to the application</param>
 * <param name="ulExitReason" type="IN">Reason for the exit, see category "Operation reason" for details</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppExitApplication', `(APPLICATION *pApp, RTS_UI32 ulExitReason)')

/**
 * <description>Exit an application (release all tasks, etc.). The application is not deleted!</description>
 * <param name="pApp" type="IN">Pointer to the application</param>
 * <param name="ulExitReason" type="IN">Reason for the exit, see category "Operation reason" for details</param>
 * <param name="ulTimeoutMs" type="IN">Timeout in milliseconds to to stop the application during exit. RTS_TIMEOUT_DEFAULT can be used as the default value</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppExitApplication2', `(APPLICATION *pApp, RTS_UI32 ulExitReason, RTS_UI32 ulTimeoutMs)')

/**
 * <description>Exit all applications (release all tasks, etc.). The applications are not deleted!</description>
 * <param name="ulExitReason" type="IN">Reason for the exit, see category "Operation reason" for details</param>
 * <param name="ulTimeoutMs" type="IN">Timeout in milliseconds to stop the application during exit. RTS_TIMEOUT_DEFAULT can be used as the default value</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppExitApplications', `(RTS_UI32 ulExitReason, RTS_UI32 ulTimeoutMs)')

/**
 * <description>Delete an application. Bootproject will not deleted!</description>
 * <param name="pApp" type="IN">Pointer to the application</param>
 * <param name="ulDeleteReason" type="IN">Reason for the delete, see category "Operation reason" for details</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppDeleteApplication', `(APPLICATION *pApp, RTS_UI32 ulDeleteReason)')

/**
 * <description>Delete all applications. Bootprojects will not be deleted!</description>
 * <param name="ulDeleteReason" type="IN">Reason for the delete, see category "Operation reason" for details</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppDeleteApplications', `(RTS_UI32 ulDeleteReason)')

/**
 * <description>Delete a bootproject (corresponding loaded application will not be affected or deleted!)</description>
 * <param name="pApp" type="IN">Pointer to the application</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppDeleteBootproject', `(APPLICATION *pApp)')

/**
 * <description>Add the peer address of an existing data server. This can be used from clients, that wants to
 *	get symbolic access to IEC variables. If the symbolic infromation is not available here on the controller,
 *	the registered data server can be used for that.</description>
 * <param name="ulSessionId" type="IN">SessionId of the communication channel</param>
 * <param name="pPeerAddr" type="IN">Pointer to the peer address of the data server</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppAddAddrDataSrv', `(RTS_UI32 ulSessionId, PEERADDRESS *pPeerAddr)')

/**
 * <description>Remove a peer address of an existing data server that will be shutdown</description>
 * <param name="ulSessionId" type="IN">SessionId of the communication channel</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppRemoveAddrDataSrv', `(RTS_UI32 ulSessionId)')

/**
 * <description>Retrieves the peer address of the first registered data server</description>
 * <param name="ppPeerAddr" type="OUT">Pointer pointer to the peer address</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to get the next peer addresse of a registered data server, RTS_INVALID_HANDLE if not available</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `AppGetFirstAddrDataSrv', `(PEERADDRESS **ppPeerAddr, RTS_RESULT *pResult)')

/**
 * <description>Retrieves the peer address of the first registered data server</description>
 * <param name="hAddr" type="IN">Handle, that was retrieved by the AppGetFirstAddrDataSrv() function</param>
 * <param name="ppPeerAddr" type="OUT">Pointer pointer to the peer address</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to get the next peer addresse of a registered data server, RTS_INVALID_HANDLE if not available</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `AppGetNextAddrDataSrv', `(RTS_HANDLE hAddr, PEERADDRESS **ppPeerAddr, RTS_RESULT *pResult)')

/**
 * <description>Begin a consistency sequence. This can be used to check, if any task of an IEC application
 *	(or its father application) was active during this sequence. A typical usage is the task consistent
 *	data monitoring during this sequence.
 * </description>
 * <param name="pApp" type="IN">Pointer to the application</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Return a handle to the consistency object</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `AppConsistencyCheckBegin', `(APPLICATION *pApp, RTS_RESULT *pResult)')

/**
 * <description>End a consistency sequence. This can be used to check, if any task of an IEC application
 *	(or its father application) was active during this consistency sequence.
 *	A typical usage is the task consistent data monitoring.
 * </description>
 * <param name="hConsistency" type="IN">Handle to the consistency object that is returned by AppConsistencyBegin()</param>
 * <result>ERR_OK: No task active during this consistency sequence,
 *		   ERR_FAILED: Any task of this application was active during this sequence</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppConsistencyCheckEnd', `(RTS_HANDLE hConsistency)')

/**
 * <description>Check all applications for consistency, that are called with AppConsistencyCheckBegin()</description>
 * <result>ERR_OK: No task active during this consistency sequence,
 *		   ERR_FAILED: Any task of an application was active during this sequence</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppConsistencyCheckAll', `(void)')

/**
 * <description>Retrieves the application info of the first application</description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the first application</result>
 */
DEF_ITF_API(`APPLICATION*', `CDECL', `AppGetFirstApp', `(RTS_RESULT *pResult)')

/**
 * <description>Retrieves the application info of the next application</description>
 * <param name="pAppPrev" type="IN">Pointer to the first application retrieved by the AppGetFirstApp()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the next application</result>
 */
DEF_ITF_API(`APPLICATION*', `CDECL', `AppGetNextApp', `(APPLICATION *pAppPrev, RTS_RESULT *pResult)')

/**
 * <description>Stores the retains of an application in a file</description>
 * <param name="pApp" type="IN">Pointer to application</param>
 * <param name="pszFilename" type="OUT">Name of retain file</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppStoreRetainsInFile', `(APPLICATION *pApp, RTS_IEC_STRING* pszFileName)')

/**
 * <description>Restores the retains of an application from a file</description>
 * <param name="pApp" type="IN">Pointer to application</param>
 * <param name="pszFilename" type="IN">Name of retain file</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppRestoreRetainsFromFile', `(APPLICATION *pApp, RTS_IEC_STRING* pszFileName)')

/**
 * <description>Restores the retains of an application from a file</description>
 * <param name="pApp" type="IN">Pointer to application</param>
 * <param name="pszFilename" type="IN">Name of retain file</param>
 * <param name="bGenerateException" type="IN">Select behaviour on retain mismatch: 1=Generate exception, 0=Only return error code</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppRestoreRetainsFromFile2', `(APPLICATION *pApp, RTS_IEC_STRING* pszFileName, int bGenerateException)')

/**
 * <description>Store retain areas the standard way for the next reboot or reload</description>
 * <param name="pApp" type="IN">Pointer to application</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppSaveRetainAreas', `(APPLICATION *pApp)')

/**
 * <description>Store retain areas the standard way for the next reboot or reload of all applications</description>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppSaveAllRetainAreas', `(void)')

/**
 * <description>Restore retain areas the standard way</description>
 * <param name="pApp" type="IN">Pointer to application</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppRestoreRetainAreas', `(APPLICATION *pApp)')

/**
 * <description>This function retuns the size of an application area</description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="usType" type="IN">Area type. See category "Area Types" in SysMemItf.h.</param>
 * <param name="pResult" type="OUT">Pointer to Result</param>
 * <result>Area size</result>
 */
DEF_ITF_API(`RTS_SIZE', `CDECL', `AppGetAreaSize', `(APPLICATION* pApp, RTS_UI16 usType, RTS_RESULT* pResult)')

/**
 * <description>This function retuns the start address of an application area</description>
 * <param name="pApp" type="IN" range="[NULL,VALID_PAPP]">Pointer to the specified application description</param>
 * <param name="usType" type="IN" range="[DA_NONE,VALID_DA,INVALID_DA]">Area type. See category "Area Types" in SysMemItf.h.</param>
 * <param name="pResult" type="OUT">Pointer to Result</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Areapointer successfully retrieved</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Parameter pApp may not be null</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_FAILED">No Area for given type found</errorcode> 
 * <result>Area start address</result>
 */
DEF_ITF_API(`RTS_UI8*', `CDECL', `AppGetAreaAddress', `(APPLICATION* pApp, RTS_UI16 usType, RTS_RESULT* pResult)')

/**
 * <description>This function retuns the segment info specified by type</description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="usType" type="IN">Area type. See category "Area Types" in SysMemItf.h.</param>
 * <param name="pResult" type="OUT">Pointer to Result</param>
 * <result>Pointer to segment info</result>
 */
DEF_ITF_API(`APP_MEMORY_SEGMENT *', `CDECL', `AppGetSegment', `(APPLICATION* pApp, RTS_UI16 usType, RTS_RESULT *pResult)')

/**
 * <description>This function retuns the segment info specified by address</description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="pAddress" type="IN">Pointer to segment data</param>
 * <param name="pResult" type="OUT">Pointer to Result</param>
 * <result>Pointer to segment info</result>
 */
DEF_ITF_API(`APP_MEMORY_SEGMENT *', `CDECL', `AppGetSegmentByAddress', `(APPLICATION* pApp, void *pAddress, RTS_RESULT *pResult)')

/**
 * <description>
 *	This function retuns the start size of an IEC segment. All segments resides within an area.
 *	This is used to get access for example to the size of the output processimage segment (%Q).
 * </description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="usType" type="IN">Area type. See category "Area Types" in SysMemItf.h.</param>
 * <param name="pResult" type="OUT">Pointer to Result</param>
 * <result>Segment size</result>
 */
DEF_ITF_API(`RTS_SIZE', `CDECL', `AppGetSegmentSize', `(APPLICATION* pApp, RTS_UI16 usType, RTS_RESULT* pResult)')

/**
 * <description>
 *	This function retuns the start address of an IEC segment. All segments resides within an area.
 *	This is used to get access for example to the beginning of the output processimage segment (%Q).
 * </description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="usType" type="IN">Area type. See category "Area Types" in SysMemItf.h.</param>
 * <param name="pResult" type="OUT">Pointer to Result</param>
 * <result>Segment start address</result>
 */
DEF_ITF_API(`RTS_UI8 HUGEPTR *', `CDECL', `AppGetSegmentAddress', `(APPLICATION* pApp, RTS_UI16 usType, RTS_RESULT* pResult)')

/**
 * <description>This function registers the properties access functions</description>
 * <param name="pApp" type="IN" range="[NULL,VALID_PAPP]">Pointer to Application</param>
 * <param name="ppfGetBooleanProperty" type="IN" range="[NULL,VALID_PPFBPROP]">Pointer to Pointer to Boolean Function</param>
 * <param name="ppfGetTextProperty" type="IN" range="[NULL,VALID_PPFTPROP]">Pointer to Pointer to Text Function</param>
 * <param name="ppfGetNumberProperty" type="IN" range="[NULL,VALID_PPFNPROP]">Pointer to Pointer to Number Function</param>
 * <param name="ppfGetVersionProperty" type="IN" range="[NULL,VALID_PPFNPROP]">Pointer to Pointer to Version Function</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Functions successfully registered</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Parameter pApp may not be null</errorcode>
 * <result>Error Code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppRegisterPropAccessFunctions', `(APPLICATION* pApp, RTS_VOID_FCTPTR *ppfGetBooleanProperty, RTS_VOID_FCTPTR *ppfGetTextProperty, RTS_VOID_FCTPTR *ppfGetNumberProperty, RTS_VOID_FCTPTR *ppfGetVersionProperty)')

/**
 * <description>This function returns the project information</description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="pfGetBooleanProperty" type="IN">Pointer to PROJECT_INFORMATION</param>
 * <result>Error Code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppGetProjectInformation', `(APPLICATION* pApp, PROJECT_INFO* pInfo)')

/**
 * <description>With this function you get access to the optional IEC function in the project, which contains boolean project infomration</description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="pBooleanProperty" type="INOUT">wszKey must be set with the key (RTS_IEC_WSTRING!), as defined in the project information dialog in CoDeSys.
 *	See category "Property keys" for predefined property keys.
 *	bBooleanProperty contains the bool property value.</param>
 * <result>Error Code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppGetBooleanProperty', `(APPLICATION *pApp, BOOLEANPROPERTY *pBooleanProperty)')

/**
 * <description>With this function you get access to the optional IEC function in the project, which contains text project infomration</description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="pTextProperty" type="INOUT">wszKey must be set with the key (RTS_IEC_WSTRING!), as defined in the project information dialog in CoDeSys.
 *	See category "Property keys" for predefined property keys.
 *	wszTextProperty contains the string property value.</param>
 * <result>Error Code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppGetTextProperty', `(APPLICATION *pApp, TEXTPROPERTY *pTextProperty)')

/**
 * <description>With this function you get access to the optional IEC function in the project, which contains text project infomration</description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="pNumberProperty" type="INOUT">wszKey must be set with the key (RTS_IEC_WSTRING!), as defined in the project information dialog in CoDeSys.
 *	See category "Property keys" for predefined property keys.
 *	udiNumberProperty contains the number property value.</param>
 * <result>Error Code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppGetNumberProperty', `(APPLICATION *pApp, NUMBERPROPERTY *pNumberProperty)')

/**
 * <description>With this function you get access to the optional IEC function in the project, which contains text project infomration</description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="pVersionProperty" type="INOUT">wszKey must be set with the key (RTS_IEC_WSTRING!), as defined in the project information dialog in CoDeSys.
 *	See category "Property keys" for predefined property keys.
 *	uiMajor, uiMinor, uiServicePack, uiPatch contains the version property values.</param>
 * <result>Error Code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppGetVersionProperty', `(APPLICATION *pApp, VERSIONPROPERTY *pVersionProperty)')

/**
 * <description>Get the current application, in which task context the caller is located</description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to application description</result>
 */
DEF_ITF_API(`APPLICATION*', `CDECL', `AppGetCurrent', `(RTS_RESULT *pResult)')

/**
 * <description>Check the consistency of the specified application to the files of bootproject and project archive</description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="pBootprojectConsistency" type="OUT">Pointer to result of the bootproject consistency.
 *		ERR_OK: Bootproject matches the specified application</param>
 * <param name="pArchiveConsistency" type="OUT">Pointer to result of the archive consistency.
 *		ERR_OK: Archive matches the specified application</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppCheckFileConsistency', `(APPLICATION *pApp, RTS_RESULT *pBootprojectConsistency, RTS_RESULT *pArchiveConsistency)')

/**
 * <description>Generate an exception on the specified application.
 *	NOTE: pApp can be NULL, so the current applicaiton in program download sequence is used!</description>
 * <param name="pApp" type="IN">Pointer to Application. Can be NULL!</param>
 * <param name="ulException" type="IN">Exception code. See SysExceptItf.h for details.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppGenerateException', `(APPLICATION *pApp, RTS_UI32 ulException)')

/**
 * <description>Function to register a bootproject to reload at the next startup</description>
 * <param name="pszAppName" type="IN">Name of the bootproject without ending or application name</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppRegisterBootproject', `(char *pszBootproject)')

/**
 * <description>Function to unregister a bootproject to avoid reload at the next startup</description>
 * <param name="pszAppName" type="IN">Name of the bootproject without ending or application name</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppUnregisterBootproject', `(char *pszBootproject)')

/**
 * <description>Function call a property of a function block to get the value</description>
 * <param name="pInstance" type="IN">Pointer to the FB instance</param>
 * <param name="ppGetMethod" type="IN">Pointer to the get method of the property (ADR(__get[PropertyName])</param>
 * <param name="pbyValue" type="IN">Pointer to a value buffer to return the value of the property</param>
 * <param name="ulSize" type="IN">Size in bytes of the property type</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppCallGetProperty', `(void *pInstance, RTS_VOID_FCTPTR *ppGetMethod, RTS_UI8 *pbyValue, RTS_SIZE ulSize)')

/**
 * <description>Function call a property of a function block to get the value
 * <p>The returned internal buffer must be released with AppCallGetProperty2Release.</p></description>
 * <param name="pInstance" type="IN">Pointer to the FB instance</param>
 * <param name="ppGetMethod" type="IN">Pointer to the get method of the property (ADR(__get[PropertyName])</param>
 * <param name="ppbyValue" type="IN">Pointer to a pointer to an internal buffer which holds the value of the property</param>
 * <param name="ulSize" type="IN">Size in bytes of the property type</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppCallGetProperty2', `(void *pInstance, RTS_VOID_FCTPTR *ppGetMethod, RTS_UI8 **ppbyValue, RTS_SIZE ulSize)')

/**
 * <description>Function call to release the internal buffer returned by AppCallGetProperty2</description>
 * <param name="pbyValue" type="IN">Pointer to the internal buffer from AppCallGetProperty2</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppCallGetProperty2Release', `(RTS_UI8 *pbyValue)')

/**
 * <description>Function call a property of a function block to set the value</description>
 * <param name="pInstance" type="IN">Pointer to the FB instance</param>
 * <param name="ppSetMethod" type="IN">Pointer to the set method of the property (ADR(__get[PropertyName])</param>
 * <param name="pbyValue" type="IN">Pointer to a value buffer to set the value of the property</param>
 * <param name="ulSize" type="IN">Size in bytes of the property type</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppCallSetProperty', `(void *pInstance, RTS_VOID_FCTPTR *ppSetMethod, RTS_UI8 *pbyValue, RTS_SIZE ulSize)')

/**
 * <description>Get area number and offset of an application specified by a memory address</description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="ulAddress" type="IN">Memory address</param>
 * <param name="pusArea" type="OUT">Pointer to return area number</param>
 * <param name="pulOffset" type="IN">Pointer to return area offset</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppGetAreaOffsetByAddress', `(APPLICATION *pApp, RTS_UINTPTR ulAddress, RTS_UI16 *pusArea, RTS_SIZE *pulOffset)')


/**
 * <description>Returns the application specified in an online service</description>
 * <param name="pduSendBuffer" type="IN">Pointer to the sent data unit</param>
 * <param name="preader" type="IN">Pointer to the reader</param>
 * <param name="pwriter" type="IN">Pointer to the writer</param>
 * <param name="ulSessionId" type="IN">Session id of the given service</param>
 * <result>Pointer to the application description</result>
 */
DEF_ITF_API(`APPLICATION*', `CDECL', `AppSrvGetApplication', `(PROTOCOL_DATA_UNIT *pduSendBuffer, BINTAGREADER *preader, BINTAGWRITER *pwriter, RTS_UI32 ulSessionId)')

/**
 * <description>Check the access rights to the specified object of the application</description>
 * <param name="pszApplication" type="IN">Name of the application</param>
 * <param name="pszObject" type="IN">Name of the object</param>
 * <param name="ulRequestedRights" type="IN">Requested rights on the object</param>
 * <param name="ulSessionId" type="IN">SessionID of the online service</param>
 * <param name="pWriter" type="IN">Pointer to the tag writer</param>
 * <result>Error code:
 *		ERR_OK: Has access rights
 *		ERR_FAILED: Operation failed
 *		ERR_NO_ACCESS_RIGHTS: No access rights to the object
 * </result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppHasAccessRights', `(char *pszApplication, char *pszObject, RTS_UI32 ulRequestedRights, RTS_UI32 ulSessionId, BINTAGWRITER *pWriter)')

/**
 * <description>Get the detail information of the specified application</description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to application info structure</result>
 */
DEF_ITF_API(`APPLICATION_INFO *', `CDECL', `AppGetApplicationInfo', `(APPLICATION *pApp, RTS_RESULT *pResult)')

/**
 * <description>Function to get the first configured bootproject.
 * <p>This pre-check may be called prior to the loading of any bootproject when functions like AppGetFirstApp, AppGetNextApp, AppGetNumOfApplications are not yet initialized.</p>
 * <p>To get the next bootpoject, call AppGetNextConfiguredBootproject with the returned iteration handle.</p>
 * <p>IMPLEMENTATION NOTE: This function may be called prior to CH_INIT_TASKS but after CH_INIT</p>
 * </description>
 * <param name="pszAppName" type="OUT">Pointer to the buffer for application name</param>
 * <param name="nMaxAppName" type="OUT">Buffer size</param>
 * <param name="bCheckFile" type="IN">If set the application file is checked and returned only if found</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">An application name is successfully found and returned.</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Invalid parameter (pointer NULL or length 0)</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_END_OF_OBJECT">No more entries found.</errorcode>
 * <result>Interation handle</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `AppGetFirstConfiguredBootproject', `(char *pszAppName, RTS_I32 nMaxAppName, RTS_BOOL bCheckFile, RTS_RESULT *pResult)')

/**
 * <description>Function to get the next configured bootproject.
 * <p>This function is called at first with the iteration handle of AppGetFirstConfiguredBootproject. The next call requires the iteration handle of the previous call of AppGetNextConfiguredBootproject.</p>
 * <p>For more information see AppGetFirstConfiguredBootproject.</p>
 * </description>
 * <param name="hPrev" type="IN">Iteration handle from previous call of either AppGetFirstConfiguredBootproject or AppGetNextConfiguredBootproject</param>
 * <param name="pszAppName" type="OUT">Pointer to the buffer for application name</param>
 * <param name="nMaxAppName" type="OUT">Buffer size</param>
 * <param name="bCheckFile" type="IN">If set the application file is checked and returned only if found</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">An application name is successfully found and returned.</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Invalid parameter (pointer NULL or length 0)</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_END_OF_OBJECT">No more entries found.</errorcode>
 * <result>Interation handle</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `AppGetNextConfiguredBootproject', `(RTS_HANDLE hPrev, char *pszAppName, RTS_I32 nMaxAppName, RTS_BOOL bCheckFile, RTS_RESULT *pResult)')

#ifdef __cplusplus
}
#endif
