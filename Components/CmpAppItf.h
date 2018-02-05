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


	
	
#ifndef _CMPAPPITF_H_
#define _CMPAPPITF_H_

#include "CmpStd.h"

 

 




#include "SysTaskItf.h"
#include "SysMemItf.h"
#include "SysFileItf.h"
#include "SysCpuHandlingItf.h"
#include "CmpMemPoolItf.h"
#include "CmpEventMgrItf.h"
#include "CmpCommunicationLibItf.h"
#include "CmpRetainItf.h"
#include "CmpSrvItf.h"

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
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

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

void CDECL CDECL_EXT appcallgetproperty(appcallgetproperty_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPCALLGETPROPERTY_IEC) (appcallgetproperty_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPCALLGETPROPERTY_NOTIMPLEMENTED)
	#define USE_appcallgetproperty
	#define EXT_appcallgetproperty
	#define GET_appcallgetproperty(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appcallgetproperty(p0) 
	#define CHK_appcallgetproperty  FALSE
	#define EXP_appcallgetproperty  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appcallgetproperty
	#define EXT_appcallgetproperty
	#define GET_appcallgetproperty(fl)  CAL_CMGETAPI( "appcallgetproperty" ) 
	#define CAL_appcallgetproperty  appcallgetproperty
	#define CHK_appcallgetproperty  TRUE
	#define EXP_appcallgetproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appcallgetproperty", (RTS_UINTPTR)appcallgetproperty, 1, RTSITF_GET_SIGNATURE(0, 0xD99D7FC0), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appcallgetproperty
	#define EXT_appcallgetproperty
	#define GET_appcallgetproperty(fl)  CAL_CMGETAPI( "appcallgetproperty" ) 
	#define CAL_appcallgetproperty  appcallgetproperty
	#define CHK_appcallgetproperty  TRUE
	#define EXP_appcallgetproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appcallgetproperty", (RTS_UINTPTR)appcallgetproperty, 1, RTSITF_GET_SIGNATURE(0, 0xD99D7FC0), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappcallgetproperty
	#define EXT_CmpAppappcallgetproperty
	#define GET_CmpAppappcallgetproperty  ERR_OK
	#define CAL_CmpAppappcallgetproperty  appcallgetproperty
	#define CHK_CmpAppappcallgetproperty  TRUE
	#define EXP_CmpAppappcallgetproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appcallgetproperty", (RTS_UINTPTR)appcallgetproperty, 1, RTSITF_GET_SIGNATURE(0, 0xD99D7FC0), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appcallgetproperty
	#define EXT_appcallgetproperty
	#define GET_appcallgetproperty(fl)  CAL_CMGETAPI( "appcallgetproperty" ) 
	#define CAL_appcallgetproperty  appcallgetproperty
	#define CHK_appcallgetproperty  TRUE
	#define EXP_appcallgetproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appcallgetproperty", (RTS_UINTPTR)appcallgetproperty, 1, RTSITF_GET_SIGNATURE(0, 0xD99D7FC0), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appcallgetproperty  PFAPPCALLGETPROPERTY_IEC pfappcallgetproperty;
	#define EXT_appcallgetproperty  extern PFAPPCALLGETPROPERTY_IEC pfappcallgetproperty;
	#define GET_appcallgetproperty(fl)  s_pfCMGetAPI2( "appcallgetproperty", (RTS_VOID_FCTPTR *)&pfappcallgetproperty, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xD99D7FC0), 0x03050B00)
	#define CAL_appcallgetproperty  pfappcallgetproperty
	#define CHK_appcallgetproperty  (pfappcallgetproperty != NULL)
	#define EXP_appcallgetproperty   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appcallgetproperty", (RTS_UINTPTR)appcallgetproperty, 1, RTSITF_GET_SIGNATURE(0, 0xD99D7FC0), 0x03050B00) 
#endif


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

void CDECL CDECL_EXT appcallgetproperty2(appcallgetproperty2_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPCALLGETPROPERTY2_IEC) (appcallgetproperty2_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPCALLGETPROPERTY2_NOTIMPLEMENTED)
	#define USE_appcallgetproperty2
	#define EXT_appcallgetproperty2
	#define GET_appcallgetproperty2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appcallgetproperty2(p0) 
	#define CHK_appcallgetproperty2  FALSE
	#define EXP_appcallgetproperty2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appcallgetproperty2
	#define EXT_appcallgetproperty2
	#define GET_appcallgetproperty2(fl)  CAL_CMGETAPI( "appcallgetproperty2" ) 
	#define CAL_appcallgetproperty2  appcallgetproperty2
	#define CHK_appcallgetproperty2  TRUE
	#define EXP_appcallgetproperty2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appcallgetproperty2", (RTS_UINTPTR)appcallgetproperty2, 1, RTSITF_GET_SIGNATURE(0xD878B9FD, 0x689760F7), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appcallgetproperty2
	#define EXT_appcallgetproperty2
	#define GET_appcallgetproperty2(fl)  CAL_CMGETAPI( "appcallgetproperty2" ) 
	#define CAL_appcallgetproperty2  appcallgetproperty2
	#define CHK_appcallgetproperty2  TRUE
	#define EXP_appcallgetproperty2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appcallgetproperty2", (RTS_UINTPTR)appcallgetproperty2, 1, RTSITF_GET_SIGNATURE(0xD878B9FD, 0x689760F7), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappcallgetproperty2
	#define EXT_CmpAppappcallgetproperty2
	#define GET_CmpAppappcallgetproperty2  ERR_OK
	#define CAL_CmpAppappcallgetproperty2  appcallgetproperty2
	#define CHK_CmpAppappcallgetproperty2  TRUE
	#define EXP_CmpAppappcallgetproperty2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appcallgetproperty2", (RTS_UINTPTR)appcallgetproperty2, 1, RTSITF_GET_SIGNATURE(0xD878B9FD, 0x689760F7), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appcallgetproperty2
	#define EXT_appcallgetproperty2
	#define GET_appcallgetproperty2(fl)  CAL_CMGETAPI( "appcallgetproperty2" ) 
	#define CAL_appcallgetproperty2  appcallgetproperty2
	#define CHK_appcallgetproperty2  TRUE
	#define EXP_appcallgetproperty2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appcallgetproperty2", (RTS_UINTPTR)appcallgetproperty2, 1, RTSITF_GET_SIGNATURE(0xD878B9FD, 0x689760F7), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appcallgetproperty2  PFAPPCALLGETPROPERTY2_IEC pfappcallgetproperty2;
	#define EXT_appcallgetproperty2  extern PFAPPCALLGETPROPERTY2_IEC pfappcallgetproperty2;
	#define GET_appcallgetproperty2(fl)  s_pfCMGetAPI2( "appcallgetproperty2", (RTS_VOID_FCTPTR *)&pfappcallgetproperty2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0xD878B9FD, 0x689760F7), 0x03050B00)
	#define CAL_appcallgetproperty2  pfappcallgetproperty2
	#define CHK_appcallgetproperty2  (pfappcallgetproperty2 != NULL)
	#define EXP_appcallgetproperty2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appcallgetproperty2", (RTS_UINTPTR)appcallgetproperty2, 1, RTSITF_GET_SIGNATURE(0xD878B9FD, 0x689760F7), 0x03050B00) 
#endif


/**
 * <description>appcallgetproperty2release</description>
 */
typedef struct tagappcallgetproperty2release_struct
{
	RTS_IEC_BYTE *pbyValue;				/* VAR_INPUT */	
	RTS_IEC_RESULT AppCallGetProperty2Release;	/* VAR_OUTPUT */	
} appcallgetproperty2release_struct;

void CDECL CDECL_EXT appcallgetproperty2release(appcallgetproperty2release_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPCALLGETPROPERTY2RELEASE_IEC) (appcallgetproperty2release_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPCALLGETPROPERTY2RELEASE_NOTIMPLEMENTED)
	#define USE_appcallgetproperty2release
	#define EXT_appcallgetproperty2release
	#define GET_appcallgetproperty2release(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appcallgetproperty2release(p0) 
	#define CHK_appcallgetproperty2release  FALSE
	#define EXP_appcallgetproperty2release  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appcallgetproperty2release
	#define EXT_appcallgetproperty2release
	#define GET_appcallgetproperty2release(fl)  CAL_CMGETAPI( "appcallgetproperty2release" ) 
	#define CAL_appcallgetproperty2release  appcallgetproperty2release
	#define CHK_appcallgetproperty2release  TRUE
	#define EXP_appcallgetproperty2release  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appcallgetproperty2release", (RTS_UINTPTR)appcallgetproperty2release, 1, 0x664A62E3, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appcallgetproperty2release
	#define EXT_appcallgetproperty2release
	#define GET_appcallgetproperty2release(fl)  CAL_CMGETAPI( "appcallgetproperty2release" ) 
	#define CAL_appcallgetproperty2release  appcallgetproperty2release
	#define CHK_appcallgetproperty2release  TRUE
	#define EXP_appcallgetproperty2release  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appcallgetproperty2release", (RTS_UINTPTR)appcallgetproperty2release, 1, 0x664A62E3, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappcallgetproperty2release
	#define EXT_CmpAppappcallgetproperty2release
	#define GET_CmpAppappcallgetproperty2release  ERR_OK
	#define CAL_CmpAppappcallgetproperty2release  appcallgetproperty2release
	#define CHK_CmpAppappcallgetproperty2release  TRUE
	#define EXP_CmpAppappcallgetproperty2release  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appcallgetproperty2release", (RTS_UINTPTR)appcallgetproperty2release, 1, 0x664A62E3, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appcallgetproperty2release
	#define EXT_appcallgetproperty2release
	#define GET_appcallgetproperty2release(fl)  CAL_CMGETAPI( "appcallgetproperty2release" ) 
	#define CAL_appcallgetproperty2release  appcallgetproperty2release
	#define CHK_appcallgetproperty2release  TRUE
	#define EXP_appcallgetproperty2release  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appcallgetproperty2release", (RTS_UINTPTR)appcallgetproperty2release, 1, 0x664A62E3, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appcallgetproperty2release  PFAPPCALLGETPROPERTY2RELEASE_IEC pfappcallgetproperty2release;
	#define EXT_appcallgetproperty2release  extern PFAPPCALLGETPROPERTY2RELEASE_IEC pfappcallgetproperty2release;
	#define GET_appcallgetproperty2release(fl)  s_pfCMGetAPI2( "appcallgetproperty2release", (RTS_VOID_FCTPTR *)&pfappcallgetproperty2release, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x664A62E3, 0x03050B00)
	#define CAL_appcallgetproperty2release  pfappcallgetproperty2release
	#define CHK_appcallgetproperty2release  (pfappcallgetproperty2release != NULL)
	#define EXP_appcallgetproperty2release   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appcallgetproperty2release", (RTS_UINTPTR)appcallgetproperty2release, 1, 0x664A62E3, 0x03050B00) 
#endif


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

void CDECL CDECL_EXT appcallsetproperty(appcallsetproperty_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPCALLSETPROPERTY_IEC) (appcallsetproperty_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPCALLSETPROPERTY_NOTIMPLEMENTED)
	#define USE_appcallsetproperty
	#define EXT_appcallsetproperty
	#define GET_appcallsetproperty(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appcallsetproperty(p0) 
	#define CHK_appcallsetproperty  FALSE
	#define EXP_appcallsetproperty  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appcallsetproperty
	#define EXT_appcallsetproperty
	#define GET_appcallsetproperty(fl)  CAL_CMGETAPI( "appcallsetproperty" ) 
	#define CAL_appcallsetproperty  appcallsetproperty
	#define CHK_appcallsetproperty  TRUE
	#define EXP_appcallsetproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appcallsetproperty", (RTS_UINTPTR)appcallsetproperty, 1, RTSITF_GET_SIGNATURE(0, 0xF7790D93), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appcallsetproperty
	#define EXT_appcallsetproperty
	#define GET_appcallsetproperty(fl)  CAL_CMGETAPI( "appcallsetproperty" ) 
	#define CAL_appcallsetproperty  appcallsetproperty
	#define CHK_appcallsetproperty  TRUE
	#define EXP_appcallsetproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appcallsetproperty", (RTS_UINTPTR)appcallsetproperty, 1, RTSITF_GET_SIGNATURE(0, 0xF7790D93), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappcallsetproperty
	#define EXT_CmpAppappcallsetproperty
	#define GET_CmpAppappcallsetproperty  ERR_OK
	#define CAL_CmpAppappcallsetproperty  appcallsetproperty
	#define CHK_CmpAppappcallsetproperty  TRUE
	#define EXP_CmpAppappcallsetproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appcallsetproperty", (RTS_UINTPTR)appcallsetproperty, 1, RTSITF_GET_SIGNATURE(0, 0xF7790D93), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appcallsetproperty
	#define EXT_appcallsetproperty
	#define GET_appcallsetproperty(fl)  CAL_CMGETAPI( "appcallsetproperty" ) 
	#define CAL_appcallsetproperty  appcallsetproperty
	#define CHK_appcallsetproperty  TRUE
	#define EXP_appcallsetproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appcallsetproperty", (RTS_UINTPTR)appcallsetproperty, 1, RTSITF_GET_SIGNATURE(0, 0xF7790D93), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appcallsetproperty  PFAPPCALLSETPROPERTY_IEC pfappcallsetproperty;
	#define EXT_appcallsetproperty  extern PFAPPCALLSETPROPERTY_IEC pfappcallsetproperty;
	#define GET_appcallsetproperty(fl)  s_pfCMGetAPI2( "appcallsetproperty", (RTS_VOID_FCTPTR *)&pfappcallsetproperty, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xF7790D93), 0x03050B00)
	#define CAL_appcallsetproperty  pfappcallsetproperty
	#define CHK_appcallsetproperty  (pfappcallsetproperty != NULL)
	#define EXP_appcallsetproperty   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appcallsetproperty", (RTS_UINTPTR)appcallsetproperty, 1, RTSITF_GET_SIGNATURE(0, 0xF7790D93), 0x03050B00) 
#endif


/**
 * <description>appfindapplicationbyname</description>
 */
typedef struct tagappfindapplicationbyname_struct
{
	RTS_IEC_STRING *pszString;			/* VAR_INPUT */	/* Application name */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	APPLICATION *AppFindApplicationByName;	/* VAR_OUTPUT */	
} appfindapplicationbyname_struct;

void CDECL CDECL_EXT appfindapplicationbyname(appfindapplicationbyname_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPFINDAPPLICATIONBYNAME_IEC) (appfindapplicationbyname_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPFINDAPPLICATIONBYNAME_NOTIMPLEMENTED)
	#define USE_appfindapplicationbyname
	#define EXT_appfindapplicationbyname
	#define GET_appfindapplicationbyname(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appfindapplicationbyname(p0) 
	#define CHK_appfindapplicationbyname  FALSE
	#define EXP_appfindapplicationbyname  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appfindapplicationbyname
	#define EXT_appfindapplicationbyname
	#define GET_appfindapplicationbyname(fl)  CAL_CMGETAPI( "appfindapplicationbyname" ) 
	#define CAL_appfindapplicationbyname  appfindapplicationbyname
	#define CHK_appfindapplicationbyname  TRUE
	#define EXP_appfindapplicationbyname  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appfindapplicationbyname", (RTS_UINTPTR)appfindapplicationbyname, 1, RTSITF_GET_SIGNATURE(0, 0xDAD101B7), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appfindapplicationbyname
	#define EXT_appfindapplicationbyname
	#define GET_appfindapplicationbyname(fl)  CAL_CMGETAPI( "appfindapplicationbyname" ) 
	#define CAL_appfindapplicationbyname  appfindapplicationbyname
	#define CHK_appfindapplicationbyname  TRUE
	#define EXP_appfindapplicationbyname  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appfindapplicationbyname", (RTS_UINTPTR)appfindapplicationbyname, 1, RTSITF_GET_SIGNATURE(0, 0xDAD101B7), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappfindapplicationbyname
	#define EXT_CmpAppappfindapplicationbyname
	#define GET_CmpAppappfindapplicationbyname  ERR_OK
	#define CAL_CmpAppappfindapplicationbyname  appfindapplicationbyname
	#define CHK_CmpAppappfindapplicationbyname  TRUE
	#define EXP_CmpAppappfindapplicationbyname  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appfindapplicationbyname", (RTS_UINTPTR)appfindapplicationbyname, 1, RTSITF_GET_SIGNATURE(0, 0xDAD101B7), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appfindapplicationbyname
	#define EXT_appfindapplicationbyname
	#define GET_appfindapplicationbyname(fl)  CAL_CMGETAPI( "appfindapplicationbyname" ) 
	#define CAL_appfindapplicationbyname  appfindapplicationbyname
	#define CHK_appfindapplicationbyname  TRUE
	#define EXP_appfindapplicationbyname  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appfindapplicationbyname", (RTS_UINTPTR)appfindapplicationbyname, 1, RTSITF_GET_SIGNATURE(0, 0xDAD101B7), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appfindapplicationbyname  PFAPPFINDAPPLICATIONBYNAME_IEC pfappfindapplicationbyname;
	#define EXT_appfindapplicationbyname  extern PFAPPFINDAPPLICATIONBYNAME_IEC pfappfindapplicationbyname;
	#define GET_appfindapplicationbyname(fl)  s_pfCMGetAPI2( "appfindapplicationbyname", (RTS_VOID_FCTPTR *)&pfappfindapplicationbyname, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xDAD101B7), 0x03050B00)
	#define CAL_appfindapplicationbyname  pfappfindapplicationbyname
	#define CHK_appfindapplicationbyname  (pfappfindapplicationbyname != NULL)
	#define EXP_appfindapplicationbyname   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appfindapplicationbyname", (RTS_UINTPTR)appfindapplicationbyname, 1, RTSITF_GET_SIGNATURE(0, 0xDAD101B7), 0x03050B00) 
#endif


/**
 * <description>appgenerateexception</description>
 */
typedef struct tagappgenerateexception_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_DWORD ulException;			/* VAR_INPUT */	
	RTS_IEC_RESULT AppGenerateException;	/* VAR_OUTPUT */	
} appgenerateexception_struct;

void CDECL CDECL_EXT appgenerateexception(appgenerateexception_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPGENERATEEXCEPTION_IEC) (appgenerateexception_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGENERATEEXCEPTION_NOTIMPLEMENTED)
	#define USE_appgenerateexception
	#define EXT_appgenerateexception
	#define GET_appgenerateexception(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appgenerateexception(p0) 
	#define CHK_appgenerateexception  FALSE
	#define EXP_appgenerateexception  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appgenerateexception
	#define EXT_appgenerateexception
	#define GET_appgenerateexception(fl)  CAL_CMGETAPI( "appgenerateexception" ) 
	#define CAL_appgenerateexception  appgenerateexception
	#define CHK_appgenerateexception  TRUE
	#define EXP_appgenerateexception  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgenerateexception", (RTS_UINTPTR)appgenerateexception, 1, RTSITF_GET_SIGNATURE(0, 0xCAFA8E41), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appgenerateexception
	#define EXT_appgenerateexception
	#define GET_appgenerateexception(fl)  CAL_CMGETAPI( "appgenerateexception" ) 
	#define CAL_appgenerateexception  appgenerateexception
	#define CHK_appgenerateexception  TRUE
	#define EXP_appgenerateexception  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgenerateexception", (RTS_UINTPTR)appgenerateexception, 1, RTSITF_GET_SIGNATURE(0, 0xCAFA8E41), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappgenerateexception
	#define EXT_CmpAppappgenerateexception
	#define GET_CmpAppappgenerateexception  ERR_OK
	#define CAL_CmpAppappgenerateexception  appgenerateexception
	#define CHK_CmpAppappgenerateexception  TRUE
	#define EXP_CmpAppappgenerateexception  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgenerateexception", (RTS_UINTPTR)appgenerateexception, 1, RTSITF_GET_SIGNATURE(0, 0xCAFA8E41), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appgenerateexception
	#define EXT_appgenerateexception
	#define GET_appgenerateexception(fl)  CAL_CMGETAPI( "appgenerateexception" ) 
	#define CAL_appgenerateexception  appgenerateexception
	#define CHK_appgenerateexception  TRUE
	#define EXP_appgenerateexception  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgenerateexception", (RTS_UINTPTR)appgenerateexception, 1, RTSITF_GET_SIGNATURE(0, 0xCAFA8E41), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appgenerateexception  PFAPPGENERATEEXCEPTION_IEC pfappgenerateexception;
	#define EXT_appgenerateexception  extern PFAPPGENERATEEXCEPTION_IEC pfappgenerateexception;
	#define GET_appgenerateexception(fl)  s_pfCMGetAPI2( "appgenerateexception", (RTS_VOID_FCTPTR *)&pfappgenerateexception, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xCAFA8E41), 0x03050B00)
	#define CAL_appgenerateexception  pfappgenerateexception
	#define CHK_appgenerateexception  (pfappgenerateexception != NULL)
	#define EXP_appgenerateexception   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgenerateexception", (RTS_UINTPTR)appgenerateexception, 1, RTSITF_GET_SIGNATURE(0, 0xCAFA8E41), 0x03050B00) 
#endif


/**
 * <description>appgetapplicationbyareaaddress</description>
 */
typedef struct tagappgetapplicationbyareaaddress_struct
{
	RTS_IEC_UDINT *pAddress;			/* VAR_INPUT */	
	APPLICATION *AppGetApplicationByAreaAddress;	/* VAR_OUTPUT */	
} appgetapplicationbyareaaddress_struct;

void CDECL CDECL_EXT appgetapplicationbyareaaddress(appgetapplicationbyareaaddress_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPGETAPPLICATIONBYAREAADDRESS_IEC) (appgetapplicationbyareaaddress_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETAPPLICATIONBYAREAADDRESS_NOTIMPLEMENTED)
	#define USE_appgetapplicationbyareaaddress
	#define EXT_appgetapplicationbyareaaddress
	#define GET_appgetapplicationbyareaaddress(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appgetapplicationbyareaaddress(p0) 
	#define CHK_appgetapplicationbyareaaddress  FALSE
	#define EXP_appgetapplicationbyareaaddress  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appgetapplicationbyareaaddress
	#define EXT_appgetapplicationbyareaaddress
	#define GET_appgetapplicationbyareaaddress(fl)  CAL_CMGETAPI( "appgetapplicationbyareaaddress" ) 
	#define CAL_appgetapplicationbyareaaddress  appgetapplicationbyareaaddress
	#define CHK_appgetapplicationbyareaaddress  TRUE
	#define EXP_appgetapplicationbyareaaddress  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetapplicationbyareaaddress", (RTS_UINTPTR)appgetapplicationbyareaaddress, 1, RTSITF_GET_SIGNATURE(0, 0x7EE9B1A3), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appgetapplicationbyareaaddress
	#define EXT_appgetapplicationbyareaaddress
	#define GET_appgetapplicationbyareaaddress(fl)  CAL_CMGETAPI( "appgetapplicationbyareaaddress" ) 
	#define CAL_appgetapplicationbyareaaddress  appgetapplicationbyareaaddress
	#define CHK_appgetapplicationbyareaaddress  TRUE
	#define EXP_appgetapplicationbyareaaddress  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetapplicationbyareaaddress", (RTS_UINTPTR)appgetapplicationbyareaaddress, 1, RTSITF_GET_SIGNATURE(0, 0x7EE9B1A3), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappgetapplicationbyareaaddress
	#define EXT_CmpAppappgetapplicationbyareaaddress
	#define GET_CmpAppappgetapplicationbyareaaddress  ERR_OK
	#define CAL_CmpAppappgetapplicationbyareaaddress  appgetapplicationbyareaaddress
	#define CHK_CmpAppappgetapplicationbyareaaddress  TRUE
	#define EXP_CmpAppappgetapplicationbyareaaddress  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetapplicationbyareaaddress", (RTS_UINTPTR)appgetapplicationbyareaaddress, 1, RTSITF_GET_SIGNATURE(0, 0x7EE9B1A3), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appgetapplicationbyareaaddress
	#define EXT_appgetapplicationbyareaaddress
	#define GET_appgetapplicationbyareaaddress(fl)  CAL_CMGETAPI( "appgetapplicationbyareaaddress" ) 
	#define CAL_appgetapplicationbyareaaddress  appgetapplicationbyareaaddress
	#define CHK_appgetapplicationbyareaaddress  TRUE
	#define EXP_appgetapplicationbyareaaddress  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetapplicationbyareaaddress", (RTS_UINTPTR)appgetapplicationbyareaaddress, 1, RTSITF_GET_SIGNATURE(0, 0x7EE9B1A3), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appgetapplicationbyareaaddress  PFAPPGETAPPLICATIONBYAREAADDRESS_IEC pfappgetapplicationbyareaaddress;
	#define EXT_appgetapplicationbyareaaddress  extern PFAPPGETAPPLICATIONBYAREAADDRESS_IEC pfappgetapplicationbyareaaddress;
	#define GET_appgetapplicationbyareaaddress(fl)  s_pfCMGetAPI2( "appgetapplicationbyareaaddress", (RTS_VOID_FCTPTR *)&pfappgetapplicationbyareaaddress, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x7EE9B1A3), 0x03050B00)
	#define CAL_appgetapplicationbyareaaddress  pfappgetapplicationbyareaaddress
	#define CHK_appgetapplicationbyareaaddress  (pfappgetapplicationbyareaaddress != NULL)
	#define EXP_appgetapplicationbyareaaddress   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetapplicationbyareaaddress", (RTS_UINTPTR)appgetapplicationbyareaaddress, 1, RTSITF_GET_SIGNATURE(0, 0x7EE9B1A3), 0x03050B00) 
#endif


/**
 * <description>appgetapplicationinfo</description>
 */
typedef struct tagappgetapplicationinfo_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	APPLICATION_INFO *AppGetApplicationInfo;	/* VAR_OUTPUT */	
} appgetapplicationinfo_struct;

void CDECL CDECL_EXT appgetapplicationinfo(appgetapplicationinfo_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPGETAPPLICATIONINFO_IEC) (appgetapplicationinfo_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETAPPLICATIONINFO_NOTIMPLEMENTED)
	#define USE_appgetapplicationinfo
	#define EXT_appgetapplicationinfo
	#define GET_appgetapplicationinfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appgetapplicationinfo(p0) 
	#define CHK_appgetapplicationinfo  FALSE
	#define EXP_appgetapplicationinfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appgetapplicationinfo
	#define EXT_appgetapplicationinfo
	#define GET_appgetapplicationinfo(fl)  CAL_CMGETAPI( "appgetapplicationinfo" ) 
	#define CAL_appgetapplicationinfo  appgetapplicationinfo
	#define CHK_appgetapplicationinfo  TRUE
	#define EXP_appgetapplicationinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetapplicationinfo", (RTS_UINTPTR)appgetapplicationinfo, 1, RTSITF_GET_SIGNATURE(0, 0x49DD3432), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appgetapplicationinfo
	#define EXT_appgetapplicationinfo
	#define GET_appgetapplicationinfo(fl)  CAL_CMGETAPI( "appgetapplicationinfo" ) 
	#define CAL_appgetapplicationinfo  appgetapplicationinfo
	#define CHK_appgetapplicationinfo  TRUE
	#define EXP_appgetapplicationinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetapplicationinfo", (RTS_UINTPTR)appgetapplicationinfo, 1, RTSITF_GET_SIGNATURE(0, 0x49DD3432), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappgetapplicationinfo
	#define EXT_CmpAppappgetapplicationinfo
	#define GET_CmpAppappgetapplicationinfo  ERR_OK
	#define CAL_CmpAppappgetapplicationinfo  appgetapplicationinfo
	#define CHK_CmpAppappgetapplicationinfo  TRUE
	#define EXP_CmpAppappgetapplicationinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetapplicationinfo", (RTS_UINTPTR)appgetapplicationinfo, 1, RTSITF_GET_SIGNATURE(0, 0x49DD3432), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appgetapplicationinfo
	#define EXT_appgetapplicationinfo
	#define GET_appgetapplicationinfo(fl)  CAL_CMGETAPI( "appgetapplicationinfo" ) 
	#define CAL_appgetapplicationinfo  appgetapplicationinfo
	#define CHK_appgetapplicationinfo  TRUE
	#define EXP_appgetapplicationinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetapplicationinfo", (RTS_UINTPTR)appgetapplicationinfo, 1, RTSITF_GET_SIGNATURE(0, 0x49DD3432), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appgetapplicationinfo  PFAPPGETAPPLICATIONINFO_IEC pfappgetapplicationinfo;
	#define EXT_appgetapplicationinfo  extern PFAPPGETAPPLICATIONINFO_IEC pfappgetapplicationinfo;
	#define GET_appgetapplicationinfo(fl)  s_pfCMGetAPI2( "appgetapplicationinfo", (RTS_VOID_FCTPTR *)&pfappgetapplicationinfo, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x49DD3432), 0x03050B00)
	#define CAL_appgetapplicationinfo  pfappgetapplicationinfo
	#define CHK_appgetapplicationinfo  (pfappgetapplicationinfo != NULL)
	#define EXP_appgetapplicationinfo   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetapplicationinfo", (RTS_UINTPTR)appgetapplicationinfo, 1, RTSITF_GET_SIGNATURE(0, 0x49DD3432), 0x03050B00) 
#endif


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

void CDECL CDECL_EXT appgetareaaddress(appgetareaaddress_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPGETAREAADDRESS_IEC) (appgetareaaddress_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETAREAADDRESS_NOTIMPLEMENTED)
	#define USE_appgetareaaddress
	#define EXT_appgetareaaddress
	#define GET_appgetareaaddress(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appgetareaaddress(p0) 
	#define CHK_appgetareaaddress  FALSE
	#define EXP_appgetareaaddress  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appgetareaaddress
	#define EXT_appgetareaaddress
	#define GET_appgetareaaddress(fl)  CAL_CMGETAPI( "appgetareaaddress" ) 
	#define CAL_appgetareaaddress  appgetareaaddress
	#define CHK_appgetareaaddress  TRUE
	#define EXP_appgetareaaddress  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetareaaddress", (RTS_UINTPTR)appgetareaaddress, 1, RTSITF_GET_SIGNATURE(0, 0x6C9E6C94), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appgetareaaddress
	#define EXT_appgetareaaddress
	#define GET_appgetareaaddress(fl)  CAL_CMGETAPI( "appgetareaaddress" ) 
	#define CAL_appgetareaaddress  appgetareaaddress
	#define CHK_appgetareaaddress  TRUE
	#define EXP_appgetareaaddress  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetareaaddress", (RTS_UINTPTR)appgetareaaddress, 1, RTSITF_GET_SIGNATURE(0, 0x6C9E6C94), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappgetareaaddress
	#define EXT_CmpAppappgetareaaddress
	#define GET_CmpAppappgetareaaddress  ERR_OK
	#define CAL_CmpAppappgetareaaddress  appgetareaaddress
	#define CHK_CmpAppappgetareaaddress  TRUE
	#define EXP_CmpAppappgetareaaddress  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetareaaddress", (RTS_UINTPTR)appgetareaaddress, 1, RTSITF_GET_SIGNATURE(0, 0x6C9E6C94), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appgetareaaddress
	#define EXT_appgetareaaddress
	#define GET_appgetareaaddress(fl)  CAL_CMGETAPI( "appgetareaaddress" ) 
	#define CAL_appgetareaaddress  appgetareaaddress
	#define CHK_appgetareaaddress  TRUE
	#define EXP_appgetareaaddress  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetareaaddress", (RTS_UINTPTR)appgetareaaddress, 1, RTSITF_GET_SIGNATURE(0, 0x6C9E6C94), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appgetareaaddress  PFAPPGETAREAADDRESS_IEC pfappgetareaaddress;
	#define EXT_appgetareaaddress  extern PFAPPGETAREAADDRESS_IEC pfappgetareaaddress;
	#define GET_appgetareaaddress(fl)  s_pfCMGetAPI2( "appgetareaaddress", (RTS_VOID_FCTPTR *)&pfappgetareaaddress, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x6C9E6C94), 0x03050B00)
	#define CAL_appgetareaaddress  pfappgetareaaddress
	#define CHK_appgetareaaddress  (pfappgetareaaddress != NULL)
	#define EXP_appgetareaaddress   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetareaaddress", (RTS_UINTPTR)appgetareaaddress, 1, RTSITF_GET_SIGNATURE(0, 0x6C9E6C94), 0x03050B00) 
#endif


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

void CDECL CDECL_EXT appgetareaoffsetbyaddress(appgetareaoffsetbyaddress_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPGETAREAOFFSETBYADDRESS_IEC) (appgetareaoffsetbyaddress_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETAREAOFFSETBYADDRESS_NOTIMPLEMENTED)
	#define USE_appgetareaoffsetbyaddress
	#define EXT_appgetareaoffsetbyaddress
	#define GET_appgetareaoffsetbyaddress(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appgetareaoffsetbyaddress(p0) 
	#define CHK_appgetareaoffsetbyaddress  FALSE
	#define EXP_appgetareaoffsetbyaddress  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appgetareaoffsetbyaddress
	#define EXT_appgetareaoffsetbyaddress
	#define GET_appgetareaoffsetbyaddress(fl)  CAL_CMGETAPI( "appgetareaoffsetbyaddress" ) 
	#define CAL_appgetareaoffsetbyaddress  appgetareaoffsetbyaddress
	#define CHK_appgetareaoffsetbyaddress  TRUE
	#define EXP_appgetareaoffsetbyaddress  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetareaoffsetbyaddress", (RTS_UINTPTR)appgetareaoffsetbyaddress, 1, RTSITF_GET_SIGNATURE(0, 0x356243D6), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appgetareaoffsetbyaddress
	#define EXT_appgetareaoffsetbyaddress
	#define GET_appgetareaoffsetbyaddress(fl)  CAL_CMGETAPI( "appgetareaoffsetbyaddress" ) 
	#define CAL_appgetareaoffsetbyaddress  appgetareaoffsetbyaddress
	#define CHK_appgetareaoffsetbyaddress  TRUE
	#define EXP_appgetareaoffsetbyaddress  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetareaoffsetbyaddress", (RTS_UINTPTR)appgetareaoffsetbyaddress, 1, RTSITF_GET_SIGNATURE(0, 0x356243D6), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappgetareaoffsetbyaddress
	#define EXT_CmpAppappgetareaoffsetbyaddress
	#define GET_CmpAppappgetareaoffsetbyaddress  ERR_OK
	#define CAL_CmpAppappgetareaoffsetbyaddress  appgetareaoffsetbyaddress
	#define CHK_CmpAppappgetareaoffsetbyaddress  TRUE
	#define EXP_CmpAppappgetareaoffsetbyaddress  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetareaoffsetbyaddress", (RTS_UINTPTR)appgetareaoffsetbyaddress, 1, RTSITF_GET_SIGNATURE(0, 0x356243D6), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appgetareaoffsetbyaddress
	#define EXT_appgetareaoffsetbyaddress
	#define GET_appgetareaoffsetbyaddress(fl)  CAL_CMGETAPI( "appgetareaoffsetbyaddress" ) 
	#define CAL_appgetareaoffsetbyaddress  appgetareaoffsetbyaddress
	#define CHK_appgetareaoffsetbyaddress  TRUE
	#define EXP_appgetareaoffsetbyaddress  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetareaoffsetbyaddress", (RTS_UINTPTR)appgetareaoffsetbyaddress, 1, RTSITF_GET_SIGNATURE(0, 0x356243D6), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appgetareaoffsetbyaddress  PFAPPGETAREAOFFSETBYADDRESS_IEC pfappgetareaoffsetbyaddress;
	#define EXT_appgetareaoffsetbyaddress  extern PFAPPGETAREAOFFSETBYADDRESS_IEC pfappgetareaoffsetbyaddress;
	#define GET_appgetareaoffsetbyaddress(fl)  s_pfCMGetAPI2( "appgetareaoffsetbyaddress", (RTS_VOID_FCTPTR *)&pfappgetareaoffsetbyaddress, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x356243D6), 0x03050B00)
	#define CAL_appgetareaoffsetbyaddress  pfappgetareaoffsetbyaddress
	#define CHK_appgetareaoffsetbyaddress  (pfappgetareaoffsetbyaddress != NULL)
	#define EXP_appgetareaoffsetbyaddress   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetareaoffsetbyaddress", (RTS_UINTPTR)appgetareaoffsetbyaddress, 1, RTSITF_GET_SIGNATURE(0, 0x356243D6), 0x03050B00) 
#endif


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

void CDECL CDECL_EXT appgetareapointer(appgetareapointer_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPGETAREAPOINTER_IEC) (appgetareapointer_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETAREAPOINTER_NOTIMPLEMENTED)
	#define USE_appgetareapointer
	#define EXT_appgetareapointer
	#define GET_appgetareapointer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appgetareapointer(p0) 
	#define CHK_appgetareapointer  FALSE
	#define EXP_appgetareapointer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appgetareapointer
	#define EXT_appgetareapointer
	#define GET_appgetareapointer(fl)  CAL_CMGETAPI( "appgetareapointer" ) 
	#define CAL_appgetareapointer  appgetareapointer
	#define CHK_appgetareapointer  TRUE
	#define EXP_appgetareapointer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetareapointer", (RTS_UINTPTR)appgetareapointer, 1, 0x6AC4CD9A, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appgetareapointer
	#define EXT_appgetareapointer
	#define GET_appgetareapointer(fl)  CAL_CMGETAPI( "appgetareapointer" ) 
	#define CAL_appgetareapointer  appgetareapointer
	#define CHK_appgetareapointer  TRUE
	#define EXP_appgetareapointer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetareapointer", (RTS_UINTPTR)appgetareapointer, 1, 0x6AC4CD9A, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappgetareapointer
	#define EXT_CmpAppappgetareapointer
	#define GET_CmpAppappgetareapointer  ERR_OK
	#define CAL_CmpAppappgetareapointer  appgetareapointer
	#define CHK_CmpAppappgetareapointer  TRUE
	#define EXP_CmpAppappgetareapointer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetareapointer", (RTS_UINTPTR)appgetareapointer, 1, 0x6AC4CD9A, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appgetareapointer
	#define EXT_appgetareapointer
	#define GET_appgetareapointer(fl)  CAL_CMGETAPI( "appgetareapointer" ) 
	#define CAL_appgetareapointer  appgetareapointer
	#define CHK_appgetareapointer  TRUE
	#define EXP_appgetareapointer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetareapointer", (RTS_UINTPTR)appgetareapointer, 1, 0x6AC4CD9A, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appgetareapointer  PFAPPGETAREAPOINTER_IEC pfappgetareapointer;
	#define EXT_appgetareapointer  extern PFAPPGETAREAPOINTER_IEC pfappgetareapointer;
	#define GET_appgetareapointer(fl)  s_pfCMGetAPI2( "appgetareapointer", (RTS_VOID_FCTPTR *)&pfappgetareapointer, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x6AC4CD9A, 0x03050B00)
	#define CAL_appgetareapointer  pfappgetareapointer
	#define CHK_appgetareapointer  (pfappgetareapointer != NULL)
	#define EXP_appgetareapointer   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetareapointer", (RTS_UINTPTR)appgetareapointer, 1, 0x6AC4CD9A, 0x03050B00) 
#endif


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

void CDECL CDECL_EXT appgetareasize(appgetareasize_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPGETAREASIZE_IEC) (appgetareasize_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETAREASIZE_NOTIMPLEMENTED)
	#define USE_appgetareasize
	#define EXT_appgetareasize
	#define GET_appgetareasize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appgetareasize(p0) 
	#define CHK_appgetareasize  FALSE
	#define EXP_appgetareasize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appgetareasize
	#define EXT_appgetareasize
	#define GET_appgetareasize(fl)  CAL_CMGETAPI( "appgetareasize" ) 
	#define CAL_appgetareasize  appgetareasize
	#define CHK_appgetareasize  TRUE
	#define EXP_appgetareasize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetareasize", (RTS_UINTPTR)appgetareasize, 1, RTSITF_GET_SIGNATURE(0, 0x362BAF2A), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appgetareasize
	#define EXT_appgetareasize
	#define GET_appgetareasize(fl)  CAL_CMGETAPI( "appgetareasize" ) 
	#define CAL_appgetareasize  appgetareasize
	#define CHK_appgetareasize  TRUE
	#define EXP_appgetareasize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetareasize", (RTS_UINTPTR)appgetareasize, 1, RTSITF_GET_SIGNATURE(0, 0x362BAF2A), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappgetareasize
	#define EXT_CmpAppappgetareasize
	#define GET_CmpAppappgetareasize  ERR_OK
	#define CAL_CmpAppappgetareasize  appgetareasize
	#define CHK_CmpAppappgetareasize  TRUE
	#define EXP_CmpAppappgetareasize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetareasize", (RTS_UINTPTR)appgetareasize, 1, RTSITF_GET_SIGNATURE(0, 0x362BAF2A), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appgetareasize
	#define EXT_appgetareasize
	#define GET_appgetareasize(fl)  CAL_CMGETAPI( "appgetareasize" ) 
	#define CAL_appgetareasize  appgetareasize
	#define CHK_appgetareasize  TRUE
	#define EXP_appgetareasize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetareasize", (RTS_UINTPTR)appgetareasize, 1, RTSITF_GET_SIGNATURE(0, 0x362BAF2A), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appgetareasize  PFAPPGETAREASIZE_IEC pfappgetareasize;
	#define EXT_appgetareasize  extern PFAPPGETAREASIZE_IEC pfappgetareasize;
	#define GET_appgetareasize(fl)  s_pfCMGetAPI2( "appgetareasize", (RTS_VOID_FCTPTR *)&pfappgetareasize, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x362BAF2A), 0x03050B00)
	#define CAL_appgetareasize  pfappgetareasize
	#define CHK_appgetareasize  (pfappgetareasize != NULL)
	#define EXP_appgetareasize   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetareasize", (RTS_UINTPTR)appgetareasize, 1, RTSITF_GET_SIGNATURE(0, 0x362BAF2A), 0x03050B00) 
#endif


/**
 * <description>appgetcurrent</description>
 */
typedef struct tagappgetcurrent_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	APPLICATION *AppGetCurrent;			/* VAR_OUTPUT */	
} appgetcurrent_struct;

void CDECL CDECL_EXT appgetcurrent(appgetcurrent_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPGETCURRENT_IEC) (appgetcurrent_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETCURRENT_NOTIMPLEMENTED)
	#define USE_appgetcurrent
	#define EXT_appgetcurrent
	#define GET_appgetcurrent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appgetcurrent(p0) 
	#define CHK_appgetcurrent  FALSE
	#define EXP_appgetcurrent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appgetcurrent
	#define EXT_appgetcurrent
	#define GET_appgetcurrent(fl)  CAL_CMGETAPI( "appgetcurrent" ) 
	#define CAL_appgetcurrent  appgetcurrent
	#define CHK_appgetcurrent  TRUE
	#define EXP_appgetcurrent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetcurrent", (RTS_UINTPTR)appgetcurrent, 1, RTSITF_GET_SIGNATURE(0, 0x9EE77745), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appgetcurrent
	#define EXT_appgetcurrent
	#define GET_appgetcurrent(fl)  CAL_CMGETAPI( "appgetcurrent" ) 
	#define CAL_appgetcurrent  appgetcurrent
	#define CHK_appgetcurrent  TRUE
	#define EXP_appgetcurrent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetcurrent", (RTS_UINTPTR)appgetcurrent, 1, RTSITF_GET_SIGNATURE(0, 0x9EE77745), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappgetcurrent
	#define EXT_CmpAppappgetcurrent
	#define GET_CmpAppappgetcurrent  ERR_OK
	#define CAL_CmpAppappgetcurrent  appgetcurrent
	#define CHK_CmpAppappgetcurrent  TRUE
	#define EXP_CmpAppappgetcurrent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetcurrent", (RTS_UINTPTR)appgetcurrent, 1, RTSITF_GET_SIGNATURE(0, 0x9EE77745), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appgetcurrent
	#define EXT_appgetcurrent
	#define GET_appgetcurrent(fl)  CAL_CMGETAPI( "appgetcurrent" ) 
	#define CAL_appgetcurrent  appgetcurrent
	#define CHK_appgetcurrent  TRUE
	#define EXP_appgetcurrent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetcurrent", (RTS_UINTPTR)appgetcurrent, 1, RTSITF_GET_SIGNATURE(0, 0x9EE77745), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appgetcurrent  PFAPPGETCURRENT_IEC pfappgetcurrent;
	#define EXT_appgetcurrent  extern PFAPPGETCURRENT_IEC pfappgetcurrent;
	#define GET_appgetcurrent(fl)  s_pfCMGetAPI2( "appgetcurrent", (RTS_VOID_FCTPTR *)&pfappgetcurrent, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x9EE77745), 0x03050B00)
	#define CAL_appgetcurrent  pfappgetcurrent
	#define CHK_appgetcurrent  (pfappgetcurrent != NULL)
	#define EXP_appgetcurrent   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetcurrent", (RTS_UINTPTR)appgetcurrent, 1, RTSITF_GET_SIGNATURE(0, 0x9EE77745), 0x03050B00) 
#endif


/**
 * <description>appgetfirstapp</description>
 */
typedef struct tagappgetfirstapp_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	APPLICATION *AppGetFirstApp;		/* VAR_OUTPUT */	
} appgetfirstapp_struct;

void CDECL CDECL_EXT appgetfirstapp(appgetfirstapp_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPGETFIRSTAPP_IEC) (appgetfirstapp_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETFIRSTAPP_NOTIMPLEMENTED)
	#define USE_appgetfirstapp
	#define EXT_appgetfirstapp
	#define GET_appgetfirstapp(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appgetfirstapp(p0) 
	#define CHK_appgetfirstapp  FALSE
	#define EXP_appgetfirstapp  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appgetfirstapp
	#define EXT_appgetfirstapp
	#define GET_appgetfirstapp(fl)  CAL_CMGETAPI( "appgetfirstapp" ) 
	#define CAL_appgetfirstapp  appgetfirstapp
	#define CHK_appgetfirstapp  TRUE
	#define EXP_appgetfirstapp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetfirstapp", (RTS_UINTPTR)appgetfirstapp, 1, RTSITF_GET_SIGNATURE(0, 0x75BD6F20), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appgetfirstapp
	#define EXT_appgetfirstapp
	#define GET_appgetfirstapp(fl)  CAL_CMGETAPI( "appgetfirstapp" ) 
	#define CAL_appgetfirstapp  appgetfirstapp
	#define CHK_appgetfirstapp  TRUE
	#define EXP_appgetfirstapp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetfirstapp", (RTS_UINTPTR)appgetfirstapp, 1, RTSITF_GET_SIGNATURE(0, 0x75BD6F20), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappgetfirstapp
	#define EXT_CmpAppappgetfirstapp
	#define GET_CmpAppappgetfirstapp  ERR_OK
	#define CAL_CmpAppappgetfirstapp  appgetfirstapp
	#define CHK_CmpAppappgetfirstapp  TRUE
	#define EXP_CmpAppappgetfirstapp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetfirstapp", (RTS_UINTPTR)appgetfirstapp, 1, RTSITF_GET_SIGNATURE(0, 0x75BD6F20), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appgetfirstapp
	#define EXT_appgetfirstapp
	#define GET_appgetfirstapp(fl)  CAL_CMGETAPI( "appgetfirstapp" ) 
	#define CAL_appgetfirstapp  appgetfirstapp
	#define CHK_appgetfirstapp  TRUE
	#define EXP_appgetfirstapp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetfirstapp", (RTS_UINTPTR)appgetfirstapp, 1, RTSITF_GET_SIGNATURE(0, 0x75BD6F20), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appgetfirstapp  PFAPPGETFIRSTAPP_IEC pfappgetfirstapp;
	#define EXT_appgetfirstapp  extern PFAPPGETFIRSTAPP_IEC pfappgetfirstapp;
	#define GET_appgetfirstapp(fl)  s_pfCMGetAPI2( "appgetfirstapp", (RTS_VOID_FCTPTR *)&pfappgetfirstapp, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x75BD6F20), 0x03050B00)
	#define CAL_appgetfirstapp  pfappgetfirstapp
	#define CHK_appgetfirstapp  (pfappgetfirstapp != NULL)
	#define EXP_appgetfirstapp   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetfirstapp", (RTS_UINTPTR)appgetfirstapp, 1, RTSITF_GET_SIGNATURE(0, 0x75BD6F20), 0x03050B00) 
#endif


/**
 * <description>appgetnextapp</description>
 */
typedef struct tagappgetnextapp_struct
{
	APPLICATION *pAppPrev;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	APPLICATION *AppGetNextApp;			/* VAR_OUTPUT */	
} appgetnextapp_struct;

void CDECL CDECL_EXT appgetnextapp(appgetnextapp_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPGETNEXTAPP_IEC) (appgetnextapp_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETNEXTAPP_NOTIMPLEMENTED)
	#define USE_appgetnextapp
	#define EXT_appgetnextapp
	#define GET_appgetnextapp(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appgetnextapp(p0) 
	#define CHK_appgetnextapp  FALSE
	#define EXP_appgetnextapp  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appgetnextapp
	#define EXT_appgetnextapp
	#define GET_appgetnextapp(fl)  CAL_CMGETAPI( "appgetnextapp" ) 
	#define CAL_appgetnextapp  appgetnextapp
	#define CHK_appgetnextapp  TRUE
	#define EXP_appgetnextapp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetnextapp", (RTS_UINTPTR)appgetnextapp, 1, RTSITF_GET_SIGNATURE(0, 0xD98C0DF3), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appgetnextapp
	#define EXT_appgetnextapp
	#define GET_appgetnextapp(fl)  CAL_CMGETAPI( "appgetnextapp" ) 
	#define CAL_appgetnextapp  appgetnextapp
	#define CHK_appgetnextapp  TRUE
	#define EXP_appgetnextapp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetnextapp", (RTS_UINTPTR)appgetnextapp, 1, RTSITF_GET_SIGNATURE(0, 0xD98C0DF3), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappgetnextapp
	#define EXT_CmpAppappgetnextapp
	#define GET_CmpAppappgetnextapp  ERR_OK
	#define CAL_CmpAppappgetnextapp  appgetnextapp
	#define CHK_CmpAppappgetnextapp  TRUE
	#define EXP_CmpAppappgetnextapp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetnextapp", (RTS_UINTPTR)appgetnextapp, 1, RTSITF_GET_SIGNATURE(0, 0xD98C0DF3), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appgetnextapp
	#define EXT_appgetnextapp
	#define GET_appgetnextapp(fl)  CAL_CMGETAPI( "appgetnextapp" ) 
	#define CAL_appgetnextapp  appgetnextapp
	#define CHK_appgetnextapp  TRUE
	#define EXP_appgetnextapp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetnextapp", (RTS_UINTPTR)appgetnextapp, 1, RTSITF_GET_SIGNATURE(0, 0xD98C0DF3), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appgetnextapp  PFAPPGETNEXTAPP_IEC pfappgetnextapp;
	#define EXT_appgetnextapp  extern PFAPPGETNEXTAPP_IEC pfappgetnextapp;
	#define GET_appgetnextapp(fl)  s_pfCMGetAPI2( "appgetnextapp", (RTS_VOID_FCTPTR *)&pfappgetnextapp, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xD98C0DF3), 0x03050B00)
	#define CAL_appgetnextapp  pfappgetnextapp
	#define CHK_appgetnextapp  (pfappgetnextapp != NULL)
	#define EXP_appgetnextapp   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetnextapp", (RTS_UINTPTR)appgetnextapp, 1, RTSITF_GET_SIGNATURE(0, 0xD98C0DF3), 0x03050B00) 
#endif


/**
 * <description>appgetprojectinformation</description>
 */
typedef struct tagappgetprojectinformation_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	PROJECT_INFO *pInfo;				/* VAR_INPUT */	
	RTS_IEC_RESULT AppGetProjectInformation;	/* VAR_OUTPUT */	
} appgetprojectinformation_struct;

void CDECL CDECL_EXT appgetprojectinformation(appgetprojectinformation_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPGETPROJECTINFORMATION_IEC) (appgetprojectinformation_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETPROJECTINFORMATION_NOTIMPLEMENTED)
	#define USE_appgetprojectinformation
	#define EXT_appgetprojectinformation
	#define GET_appgetprojectinformation(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appgetprojectinformation(p0) 
	#define CHK_appgetprojectinformation  FALSE
	#define EXP_appgetprojectinformation  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appgetprojectinformation
	#define EXT_appgetprojectinformation
	#define GET_appgetprojectinformation(fl)  CAL_CMGETAPI( "appgetprojectinformation" ) 
	#define CAL_appgetprojectinformation  appgetprojectinformation
	#define CHK_appgetprojectinformation  TRUE
	#define EXP_appgetprojectinformation  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetprojectinformation", (RTS_UINTPTR)appgetprojectinformation, 1, RTSITF_GET_SIGNATURE(0, 0xA736D4E6), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appgetprojectinformation
	#define EXT_appgetprojectinformation
	#define GET_appgetprojectinformation(fl)  CAL_CMGETAPI( "appgetprojectinformation" ) 
	#define CAL_appgetprojectinformation  appgetprojectinformation
	#define CHK_appgetprojectinformation  TRUE
	#define EXP_appgetprojectinformation  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetprojectinformation", (RTS_UINTPTR)appgetprojectinformation, 1, RTSITF_GET_SIGNATURE(0, 0xA736D4E6), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappgetprojectinformation
	#define EXT_CmpAppappgetprojectinformation
	#define GET_CmpAppappgetprojectinformation  ERR_OK
	#define CAL_CmpAppappgetprojectinformation  appgetprojectinformation
	#define CHK_CmpAppappgetprojectinformation  TRUE
	#define EXP_CmpAppappgetprojectinformation  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetprojectinformation", (RTS_UINTPTR)appgetprojectinformation, 1, RTSITF_GET_SIGNATURE(0, 0xA736D4E6), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appgetprojectinformation
	#define EXT_appgetprojectinformation
	#define GET_appgetprojectinformation(fl)  CAL_CMGETAPI( "appgetprojectinformation" ) 
	#define CAL_appgetprojectinformation  appgetprojectinformation
	#define CHK_appgetprojectinformation  TRUE
	#define EXP_appgetprojectinformation  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetprojectinformation", (RTS_UINTPTR)appgetprojectinformation, 1, RTSITF_GET_SIGNATURE(0, 0xA736D4E6), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appgetprojectinformation  PFAPPGETPROJECTINFORMATION_IEC pfappgetprojectinformation;
	#define EXT_appgetprojectinformation  extern PFAPPGETPROJECTINFORMATION_IEC pfappgetprojectinformation;
	#define GET_appgetprojectinformation(fl)  s_pfCMGetAPI2( "appgetprojectinformation", (RTS_VOID_FCTPTR *)&pfappgetprojectinformation, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xA736D4E6), 0x03050B00)
	#define CAL_appgetprojectinformation  pfappgetprojectinformation
	#define CHK_appgetprojectinformation  (pfappgetprojectinformation != NULL)
	#define EXP_appgetprojectinformation   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetprojectinformation", (RTS_UINTPTR)appgetprojectinformation, 1, RTSITF_GET_SIGNATURE(0, 0xA736D4E6), 0x03050B00) 
#endif


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

void CDECL CDECL_EXT appgetsegment(appgetsegment_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPGETSEGMENT_IEC) (appgetsegment_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETSEGMENT_NOTIMPLEMENTED)
	#define USE_appgetsegment
	#define EXT_appgetsegment
	#define GET_appgetsegment(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appgetsegment(p0) 
	#define CHK_appgetsegment  FALSE
	#define EXP_appgetsegment  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appgetsegment
	#define EXT_appgetsegment
	#define GET_appgetsegment(fl)  CAL_CMGETAPI( "appgetsegment" ) 
	#define CAL_appgetsegment  appgetsegment
	#define CHK_appgetsegment  TRUE
	#define EXP_appgetsegment  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetsegment", (RTS_UINTPTR)appgetsegment, 1, 0xE7291359, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appgetsegment
	#define EXT_appgetsegment
	#define GET_appgetsegment(fl)  CAL_CMGETAPI( "appgetsegment" ) 
	#define CAL_appgetsegment  appgetsegment
	#define CHK_appgetsegment  TRUE
	#define EXP_appgetsegment  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetsegment", (RTS_UINTPTR)appgetsegment, 1, 0xE7291359, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappgetsegment
	#define EXT_CmpAppappgetsegment
	#define GET_CmpAppappgetsegment  ERR_OK
	#define CAL_CmpAppappgetsegment  appgetsegment
	#define CHK_CmpAppappgetsegment  TRUE
	#define EXP_CmpAppappgetsegment  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetsegment", (RTS_UINTPTR)appgetsegment, 1, 0xE7291359, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appgetsegment
	#define EXT_appgetsegment
	#define GET_appgetsegment(fl)  CAL_CMGETAPI( "appgetsegment" ) 
	#define CAL_appgetsegment  appgetsegment
	#define CHK_appgetsegment  TRUE
	#define EXP_appgetsegment  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetsegment", (RTS_UINTPTR)appgetsegment, 1, 0xE7291359, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appgetsegment  PFAPPGETSEGMENT_IEC pfappgetsegment;
	#define EXT_appgetsegment  extern PFAPPGETSEGMENT_IEC pfappgetsegment;
	#define GET_appgetsegment(fl)  s_pfCMGetAPI2( "appgetsegment", (RTS_VOID_FCTPTR *)&pfappgetsegment, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xE7291359, 0x03050B00)
	#define CAL_appgetsegment  pfappgetsegment
	#define CHK_appgetsegment  (pfappgetsegment != NULL)
	#define EXP_appgetsegment   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetsegment", (RTS_UINTPTR)appgetsegment, 1, 0xE7291359, 0x03050B00) 
#endif


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

void CDECL CDECL_EXT appgetsegmentaddress(appgetsegmentaddress_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPGETSEGMENTADDRESS_IEC) (appgetsegmentaddress_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETSEGMENTADDRESS_NOTIMPLEMENTED)
	#define USE_appgetsegmentaddress
	#define EXT_appgetsegmentaddress
	#define GET_appgetsegmentaddress(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appgetsegmentaddress(p0) 
	#define CHK_appgetsegmentaddress  FALSE
	#define EXP_appgetsegmentaddress  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appgetsegmentaddress
	#define EXT_appgetsegmentaddress
	#define GET_appgetsegmentaddress(fl)  CAL_CMGETAPI( "appgetsegmentaddress" ) 
	#define CAL_appgetsegmentaddress  appgetsegmentaddress
	#define CHK_appgetsegmentaddress  TRUE
	#define EXP_appgetsegmentaddress  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetsegmentaddress", (RTS_UINTPTR)appgetsegmentaddress, 1, RTSITF_GET_SIGNATURE(0, 0xA1837EC1), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appgetsegmentaddress
	#define EXT_appgetsegmentaddress
	#define GET_appgetsegmentaddress(fl)  CAL_CMGETAPI( "appgetsegmentaddress" ) 
	#define CAL_appgetsegmentaddress  appgetsegmentaddress
	#define CHK_appgetsegmentaddress  TRUE
	#define EXP_appgetsegmentaddress  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetsegmentaddress", (RTS_UINTPTR)appgetsegmentaddress, 1, RTSITF_GET_SIGNATURE(0, 0xA1837EC1), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappgetsegmentaddress
	#define EXT_CmpAppappgetsegmentaddress
	#define GET_CmpAppappgetsegmentaddress  ERR_OK
	#define CAL_CmpAppappgetsegmentaddress  appgetsegmentaddress
	#define CHK_CmpAppappgetsegmentaddress  TRUE
	#define EXP_CmpAppappgetsegmentaddress  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetsegmentaddress", (RTS_UINTPTR)appgetsegmentaddress, 1, RTSITF_GET_SIGNATURE(0, 0xA1837EC1), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appgetsegmentaddress
	#define EXT_appgetsegmentaddress
	#define GET_appgetsegmentaddress(fl)  CAL_CMGETAPI( "appgetsegmentaddress" ) 
	#define CAL_appgetsegmentaddress  appgetsegmentaddress
	#define CHK_appgetsegmentaddress  TRUE
	#define EXP_appgetsegmentaddress  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetsegmentaddress", (RTS_UINTPTR)appgetsegmentaddress, 1, RTSITF_GET_SIGNATURE(0, 0xA1837EC1), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appgetsegmentaddress  PFAPPGETSEGMENTADDRESS_IEC pfappgetsegmentaddress;
	#define EXT_appgetsegmentaddress  extern PFAPPGETSEGMENTADDRESS_IEC pfappgetsegmentaddress;
	#define GET_appgetsegmentaddress(fl)  s_pfCMGetAPI2( "appgetsegmentaddress", (RTS_VOID_FCTPTR *)&pfappgetsegmentaddress, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xA1837EC1), 0x03050B00)
	#define CAL_appgetsegmentaddress  pfappgetsegmentaddress
	#define CHK_appgetsegmentaddress  (pfappgetsegmentaddress != NULL)
	#define EXP_appgetsegmentaddress   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetsegmentaddress", (RTS_UINTPTR)appgetsegmentaddress, 1, RTSITF_GET_SIGNATURE(0, 0xA1837EC1), 0x03050B00) 
#endif


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

void CDECL CDECL_EXT appgetsegmentsize(appgetsegmentsize_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPGETSEGMENTSIZE_IEC) (appgetsegmentsize_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETSEGMENTSIZE_NOTIMPLEMENTED)
	#define USE_appgetsegmentsize
	#define EXT_appgetsegmentsize
	#define GET_appgetsegmentsize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appgetsegmentsize(p0) 
	#define CHK_appgetsegmentsize  FALSE
	#define EXP_appgetsegmentsize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appgetsegmentsize
	#define EXT_appgetsegmentsize
	#define GET_appgetsegmentsize(fl)  CAL_CMGETAPI( "appgetsegmentsize" ) 
	#define CAL_appgetsegmentsize  appgetsegmentsize
	#define CHK_appgetsegmentsize  TRUE
	#define EXP_appgetsegmentsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetsegmentsize", (RTS_UINTPTR)appgetsegmentsize, 1, RTSITF_GET_SIGNATURE(0, 0xC1200062), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appgetsegmentsize
	#define EXT_appgetsegmentsize
	#define GET_appgetsegmentsize(fl)  CAL_CMGETAPI( "appgetsegmentsize" ) 
	#define CAL_appgetsegmentsize  appgetsegmentsize
	#define CHK_appgetsegmentsize  TRUE
	#define EXP_appgetsegmentsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetsegmentsize", (RTS_UINTPTR)appgetsegmentsize, 1, RTSITF_GET_SIGNATURE(0, 0xC1200062), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappgetsegmentsize
	#define EXT_CmpAppappgetsegmentsize
	#define GET_CmpAppappgetsegmentsize  ERR_OK
	#define CAL_CmpAppappgetsegmentsize  appgetsegmentsize
	#define CHK_CmpAppappgetsegmentsize  TRUE
	#define EXP_CmpAppappgetsegmentsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetsegmentsize", (RTS_UINTPTR)appgetsegmentsize, 1, RTSITF_GET_SIGNATURE(0, 0xC1200062), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appgetsegmentsize
	#define EXT_appgetsegmentsize
	#define GET_appgetsegmentsize(fl)  CAL_CMGETAPI( "appgetsegmentsize" ) 
	#define CAL_appgetsegmentsize  appgetsegmentsize
	#define CHK_appgetsegmentsize  TRUE
	#define EXP_appgetsegmentsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetsegmentsize", (RTS_UINTPTR)appgetsegmentsize, 1, RTSITF_GET_SIGNATURE(0, 0xC1200062), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appgetsegmentsize  PFAPPGETSEGMENTSIZE_IEC pfappgetsegmentsize;
	#define EXT_appgetsegmentsize  extern PFAPPGETSEGMENTSIZE_IEC pfappgetsegmentsize;
	#define GET_appgetsegmentsize(fl)  s_pfCMGetAPI2( "appgetsegmentsize", (RTS_VOID_FCTPTR *)&pfappgetsegmentsize, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xC1200062), 0x03050B00)
	#define CAL_appgetsegmentsize  pfappgetsegmentsize
	#define CHK_appgetsegmentsize  (pfappgetsegmentsize != NULL)
	#define EXP_appgetsegmentsize   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appgetsegmentsize", (RTS_UINTPTR)appgetsegmentsize, 1, RTSITF_GET_SIGNATURE(0, 0xC1200062), 0x03050B00) 
#endif


/**
 * <description>appnumofactivesessions</description>
 */
typedef struct tagappnumofactivesessions_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_UDINT *pulNumSessions;		/* VAR_INPUT */	
	RTS_IEC_RESULT AppNumOfActiveSessions;	/* VAR_OUTPUT */	
} appnumofactivesessions_struct;

void CDECL CDECL_EXT appnumofactivesessions(appnumofactivesessions_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPNUMOFACTIVESESSIONS_IEC) (appnumofactivesessions_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPNUMOFACTIVESESSIONS_NOTIMPLEMENTED)
	#define USE_appnumofactivesessions
	#define EXT_appnumofactivesessions
	#define GET_appnumofactivesessions(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appnumofactivesessions(p0) 
	#define CHK_appnumofactivesessions  FALSE
	#define EXP_appnumofactivesessions  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appnumofactivesessions
	#define EXT_appnumofactivesessions
	#define GET_appnumofactivesessions(fl)  CAL_CMGETAPI( "appnumofactivesessions" ) 
	#define CAL_appnumofactivesessions  appnumofactivesessions
	#define CHK_appnumofactivesessions  TRUE
	#define EXP_appnumofactivesessions  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appnumofactivesessions", (RTS_UINTPTR)appnumofactivesessions, 1, RTSITF_GET_SIGNATURE(0, 0x28A577B6), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appnumofactivesessions
	#define EXT_appnumofactivesessions
	#define GET_appnumofactivesessions(fl)  CAL_CMGETAPI( "appnumofactivesessions" ) 
	#define CAL_appnumofactivesessions  appnumofactivesessions
	#define CHK_appnumofactivesessions  TRUE
	#define EXP_appnumofactivesessions  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appnumofactivesessions", (RTS_UINTPTR)appnumofactivesessions, 1, RTSITF_GET_SIGNATURE(0, 0x28A577B6), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappnumofactivesessions
	#define EXT_CmpAppappnumofactivesessions
	#define GET_CmpAppappnumofactivesessions  ERR_OK
	#define CAL_CmpAppappnumofactivesessions  appnumofactivesessions
	#define CHK_CmpAppappnumofactivesessions  TRUE
	#define EXP_CmpAppappnumofactivesessions  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appnumofactivesessions", (RTS_UINTPTR)appnumofactivesessions, 1, RTSITF_GET_SIGNATURE(0, 0x28A577B6), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appnumofactivesessions
	#define EXT_appnumofactivesessions
	#define GET_appnumofactivesessions(fl)  CAL_CMGETAPI( "appnumofactivesessions" ) 
	#define CAL_appnumofactivesessions  appnumofactivesessions
	#define CHK_appnumofactivesessions  TRUE
	#define EXP_appnumofactivesessions  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appnumofactivesessions", (RTS_UINTPTR)appnumofactivesessions, 1, RTSITF_GET_SIGNATURE(0, 0x28A577B6), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appnumofactivesessions  PFAPPNUMOFACTIVESESSIONS_IEC pfappnumofactivesessions;
	#define EXT_appnumofactivesessions  extern PFAPPNUMOFACTIVESESSIONS_IEC pfappnumofactivesessions;
	#define GET_appnumofactivesessions(fl)  s_pfCMGetAPI2( "appnumofactivesessions", (RTS_VOID_FCTPTR *)&pfappnumofactivesessions, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x28A577B6), 0x03050B00)
	#define CAL_appnumofactivesessions  pfappnumofactivesessions
	#define CHK_appnumofactivesessions  (pfappnumofactivesessions != NULL)
	#define EXP_appnumofactivesessions   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appnumofactivesessions", (RTS_UINTPTR)appnumofactivesessions, 1, RTSITF_GET_SIGNATURE(0, 0x28A577B6), 0x03050B00) 
#endif


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

void CDECL CDECL_EXT appregisterpropaccessfunctions(appregisterpropaccessfunctions_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPREGISTERPROPACCESSFUNCTIONS_IEC) (appregisterpropaccessfunctions_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPREGISTERPROPACCESSFUNCTIONS_NOTIMPLEMENTED)
	#define USE_appregisterpropaccessfunctions
	#define EXT_appregisterpropaccessfunctions
	#define GET_appregisterpropaccessfunctions(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appregisterpropaccessfunctions(p0) 
	#define CHK_appregisterpropaccessfunctions  FALSE
	#define EXP_appregisterpropaccessfunctions  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appregisterpropaccessfunctions
	#define EXT_appregisterpropaccessfunctions
	#define GET_appregisterpropaccessfunctions(fl)  CAL_CMGETAPI( "appregisterpropaccessfunctions" ) 
	#define CAL_appregisterpropaccessfunctions  appregisterpropaccessfunctions
	#define CHK_appregisterpropaccessfunctions  TRUE
	#define EXP_appregisterpropaccessfunctions  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appregisterpropaccessfunctions", (RTS_UINTPTR)appregisterpropaccessfunctions, 1, RTSITF_GET_SIGNATURE(0, 0xF72A3B0A), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appregisterpropaccessfunctions
	#define EXT_appregisterpropaccessfunctions
	#define GET_appregisterpropaccessfunctions(fl)  CAL_CMGETAPI( "appregisterpropaccessfunctions" ) 
	#define CAL_appregisterpropaccessfunctions  appregisterpropaccessfunctions
	#define CHK_appregisterpropaccessfunctions  TRUE
	#define EXP_appregisterpropaccessfunctions  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appregisterpropaccessfunctions", (RTS_UINTPTR)appregisterpropaccessfunctions, 1, RTSITF_GET_SIGNATURE(0, 0xF72A3B0A), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappregisterpropaccessfunctions
	#define EXT_CmpAppappregisterpropaccessfunctions
	#define GET_CmpAppappregisterpropaccessfunctions  ERR_OK
	#define CAL_CmpAppappregisterpropaccessfunctions  appregisterpropaccessfunctions
	#define CHK_CmpAppappregisterpropaccessfunctions  TRUE
	#define EXP_CmpAppappregisterpropaccessfunctions  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appregisterpropaccessfunctions", (RTS_UINTPTR)appregisterpropaccessfunctions, 1, RTSITF_GET_SIGNATURE(0, 0xF72A3B0A), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appregisterpropaccessfunctions
	#define EXT_appregisterpropaccessfunctions
	#define GET_appregisterpropaccessfunctions(fl)  CAL_CMGETAPI( "appregisterpropaccessfunctions" ) 
	#define CAL_appregisterpropaccessfunctions  appregisterpropaccessfunctions
	#define CHK_appregisterpropaccessfunctions  TRUE
	#define EXP_appregisterpropaccessfunctions  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appregisterpropaccessfunctions", (RTS_UINTPTR)appregisterpropaccessfunctions, 1, RTSITF_GET_SIGNATURE(0, 0xF72A3B0A), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appregisterpropaccessfunctions  PFAPPREGISTERPROPACCESSFUNCTIONS_IEC pfappregisterpropaccessfunctions;
	#define EXT_appregisterpropaccessfunctions  extern PFAPPREGISTERPROPACCESSFUNCTIONS_IEC pfappregisterpropaccessfunctions;
	#define GET_appregisterpropaccessfunctions(fl)  s_pfCMGetAPI2( "appregisterpropaccessfunctions", (RTS_VOID_FCTPTR *)&pfappregisterpropaccessfunctions, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xF72A3B0A), 0x03050B00)
	#define CAL_appregisterpropaccessfunctions  pfappregisterpropaccessfunctions
	#define CHK_appregisterpropaccessfunctions  (pfappregisterpropaccessfunctions != NULL)
	#define EXP_appregisterpropaccessfunctions   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appregisterpropaccessfunctions", (RTS_UINTPTR)appregisterpropaccessfunctions, 1, RTSITF_GET_SIGNATURE(0, 0xF72A3B0A), 0x03050B00) 
#endif


/**
 * <description>appreset</description>
 */
typedef struct tagappreset_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_WORD usResetOption;			/* VAR_INPUT */	
	RTS_IEC_RESULT AppReset;			/* VAR_OUTPUT */	
} appreset_struct;

void CDECL CDECL_EXT appreset(appreset_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPRESET_IEC) (appreset_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPRESET_NOTIMPLEMENTED)
	#define USE_appreset
	#define EXT_appreset
	#define GET_appreset(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appreset(p0) 
	#define CHK_appreset  FALSE
	#define EXP_appreset  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appreset
	#define EXT_appreset
	#define GET_appreset(fl)  CAL_CMGETAPI( "appreset" ) 
	#define CAL_appreset  appreset
	#define CHK_appreset  TRUE
	#define EXP_appreset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appreset", (RTS_UINTPTR)appreset, 1, RTSITF_GET_SIGNATURE(0, 0x03B85B28), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appreset
	#define EXT_appreset
	#define GET_appreset(fl)  CAL_CMGETAPI( "appreset" ) 
	#define CAL_appreset  appreset
	#define CHK_appreset  TRUE
	#define EXP_appreset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appreset", (RTS_UINTPTR)appreset, 1, RTSITF_GET_SIGNATURE(0, 0x03B85B28), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappreset
	#define EXT_CmpAppappreset
	#define GET_CmpAppappreset  ERR_OK
	#define CAL_CmpAppappreset  appreset
	#define CHK_CmpAppappreset  TRUE
	#define EXP_CmpAppappreset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appreset", (RTS_UINTPTR)appreset, 1, RTSITF_GET_SIGNATURE(0, 0x03B85B28), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appreset
	#define EXT_appreset
	#define GET_appreset(fl)  CAL_CMGETAPI( "appreset" ) 
	#define CAL_appreset  appreset
	#define CHK_appreset  TRUE
	#define EXP_appreset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appreset", (RTS_UINTPTR)appreset, 1, RTSITF_GET_SIGNATURE(0, 0x03B85B28), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appreset  PFAPPRESET_IEC pfappreset;
	#define EXT_appreset  extern PFAPPRESET_IEC pfappreset;
	#define GET_appreset(fl)  s_pfCMGetAPI2( "appreset", (RTS_VOID_FCTPTR *)&pfappreset, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x03B85B28), 0x03050B00)
	#define CAL_appreset  pfappreset
	#define CHK_appreset  (pfappreset != NULL)
	#define EXP_appreset   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appreset", (RTS_UINTPTR)appreset, 1, RTSITF_GET_SIGNATURE(0, 0x03B85B28), 0x03050B00) 
#endif


/**
 * <description>apprestoreretainsfromfile</description>
 */
typedef struct tagapprestoreretainsfromfile_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_STRING *pszFilName;			/* VAR_INPUT */	
	RTS_IEC_RESULT AppRestoreRetainsFromFile;	/* VAR_OUTPUT */	
} apprestoreretainsfromfile_struct;

void CDECL CDECL_EXT apprestoreretainsfromfile(apprestoreretainsfromfile_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPRESTORERETAINSFROMFILE_IEC) (apprestoreretainsfromfile_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPRESTORERETAINSFROMFILE_NOTIMPLEMENTED)
	#define USE_apprestoreretainsfromfile
	#define EXT_apprestoreretainsfromfile
	#define GET_apprestoreretainsfromfile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_apprestoreretainsfromfile(p0) 
	#define CHK_apprestoreretainsfromfile  FALSE
	#define EXP_apprestoreretainsfromfile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_apprestoreretainsfromfile
	#define EXT_apprestoreretainsfromfile
	#define GET_apprestoreretainsfromfile(fl)  CAL_CMGETAPI( "apprestoreretainsfromfile" ) 
	#define CAL_apprestoreretainsfromfile  apprestoreretainsfromfile
	#define CHK_apprestoreretainsfromfile  TRUE
	#define EXP_apprestoreretainsfromfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"apprestoreretainsfromfile", (RTS_UINTPTR)apprestoreretainsfromfile, 1, RTSITF_GET_SIGNATURE(0, 0x32542AD7), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_apprestoreretainsfromfile
	#define EXT_apprestoreretainsfromfile
	#define GET_apprestoreretainsfromfile(fl)  CAL_CMGETAPI( "apprestoreretainsfromfile" ) 
	#define CAL_apprestoreretainsfromfile  apprestoreretainsfromfile
	#define CHK_apprestoreretainsfromfile  TRUE
	#define EXP_apprestoreretainsfromfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"apprestoreretainsfromfile", (RTS_UINTPTR)apprestoreretainsfromfile, 1, RTSITF_GET_SIGNATURE(0, 0x32542AD7), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppapprestoreretainsfromfile
	#define EXT_CmpAppapprestoreretainsfromfile
	#define GET_CmpAppapprestoreretainsfromfile  ERR_OK
	#define CAL_CmpAppapprestoreretainsfromfile  apprestoreretainsfromfile
	#define CHK_CmpAppapprestoreretainsfromfile  TRUE
	#define EXP_CmpAppapprestoreretainsfromfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"apprestoreretainsfromfile", (RTS_UINTPTR)apprestoreretainsfromfile, 1, RTSITF_GET_SIGNATURE(0, 0x32542AD7), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_apprestoreretainsfromfile
	#define EXT_apprestoreretainsfromfile
	#define GET_apprestoreretainsfromfile(fl)  CAL_CMGETAPI( "apprestoreretainsfromfile" ) 
	#define CAL_apprestoreretainsfromfile  apprestoreretainsfromfile
	#define CHK_apprestoreretainsfromfile  TRUE
	#define EXP_apprestoreretainsfromfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"apprestoreretainsfromfile", (RTS_UINTPTR)apprestoreretainsfromfile, 1, RTSITF_GET_SIGNATURE(0, 0x32542AD7), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_apprestoreretainsfromfile  PFAPPRESTORERETAINSFROMFILE_IEC pfapprestoreretainsfromfile;
	#define EXT_apprestoreretainsfromfile  extern PFAPPRESTORERETAINSFROMFILE_IEC pfapprestoreretainsfromfile;
	#define GET_apprestoreretainsfromfile(fl)  s_pfCMGetAPI2( "apprestoreretainsfromfile", (RTS_VOID_FCTPTR *)&pfapprestoreretainsfromfile, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x32542AD7), 0x03050B00)
	#define CAL_apprestoreretainsfromfile  pfapprestoreretainsfromfile
	#define CHK_apprestoreretainsfromfile  (pfapprestoreretainsfromfile != NULL)
	#define EXP_apprestoreretainsfromfile   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"apprestoreretainsfromfile", (RTS_UINTPTR)apprestoreretainsfromfile, 1, RTSITF_GET_SIGNATURE(0, 0x32542AD7), 0x03050B00) 
#endif


/**
 * <description>appstartapplication</description>
 */
typedef struct tagappstartapplication_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_RESULT AppStartApplication;	/* VAR_OUTPUT */	
} appstartapplication_struct;

void CDECL CDECL_EXT appstartapplication(appstartapplication_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPSTARTAPPLICATION_IEC) (appstartapplication_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPSTARTAPPLICATION_NOTIMPLEMENTED)
	#define USE_appstartapplication
	#define EXT_appstartapplication
	#define GET_appstartapplication(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appstartapplication(p0) 
	#define CHK_appstartapplication  FALSE
	#define EXP_appstartapplication  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appstartapplication
	#define EXT_appstartapplication
	#define GET_appstartapplication(fl)  CAL_CMGETAPI( "appstartapplication" ) 
	#define CAL_appstartapplication  appstartapplication
	#define CHK_appstartapplication  TRUE
	#define EXP_appstartapplication  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appstartapplication", (RTS_UINTPTR)appstartapplication, 1, RTSITF_GET_SIGNATURE(0, 0x71CC8510), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appstartapplication
	#define EXT_appstartapplication
	#define GET_appstartapplication(fl)  CAL_CMGETAPI( "appstartapplication" ) 
	#define CAL_appstartapplication  appstartapplication
	#define CHK_appstartapplication  TRUE
	#define EXP_appstartapplication  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appstartapplication", (RTS_UINTPTR)appstartapplication, 1, RTSITF_GET_SIGNATURE(0, 0x71CC8510), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappstartapplication
	#define EXT_CmpAppappstartapplication
	#define GET_CmpAppappstartapplication  ERR_OK
	#define CAL_CmpAppappstartapplication  appstartapplication
	#define CHK_CmpAppappstartapplication  TRUE
	#define EXP_CmpAppappstartapplication  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appstartapplication", (RTS_UINTPTR)appstartapplication, 1, RTSITF_GET_SIGNATURE(0, 0x71CC8510), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appstartapplication
	#define EXT_appstartapplication
	#define GET_appstartapplication(fl)  CAL_CMGETAPI( "appstartapplication" ) 
	#define CAL_appstartapplication  appstartapplication
	#define CHK_appstartapplication  TRUE
	#define EXP_appstartapplication  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appstartapplication", (RTS_UINTPTR)appstartapplication, 1, RTSITF_GET_SIGNATURE(0, 0x71CC8510), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appstartapplication  PFAPPSTARTAPPLICATION_IEC pfappstartapplication;
	#define EXT_appstartapplication  extern PFAPPSTARTAPPLICATION_IEC pfappstartapplication;
	#define GET_appstartapplication(fl)  s_pfCMGetAPI2( "appstartapplication", (RTS_VOID_FCTPTR *)&pfappstartapplication, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x71CC8510), 0x03050B00)
	#define CAL_appstartapplication  pfappstartapplication
	#define CHK_appstartapplication  (pfappstartapplication != NULL)
	#define EXP_appstartapplication   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appstartapplication", (RTS_UINTPTR)appstartapplication, 1, RTSITF_GET_SIGNATURE(0, 0x71CC8510), 0x03050B00) 
#endif


/**
 * <description>appstopapplication</description>
 */
typedef struct tagappstopapplication_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_RESULT AppStopApplication;	/* VAR_OUTPUT */	
} appstopapplication_struct;

void CDECL CDECL_EXT appstopapplication(appstopapplication_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPSTOPAPPLICATION_IEC) (appstopapplication_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPSTOPAPPLICATION_NOTIMPLEMENTED)
	#define USE_appstopapplication
	#define EXT_appstopapplication
	#define GET_appstopapplication(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appstopapplication(p0) 
	#define CHK_appstopapplication  FALSE
	#define EXP_appstopapplication  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appstopapplication
	#define EXT_appstopapplication
	#define GET_appstopapplication(fl)  CAL_CMGETAPI( "appstopapplication" ) 
	#define CAL_appstopapplication  appstopapplication
	#define CHK_appstopapplication  TRUE
	#define EXP_appstopapplication  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appstopapplication", (RTS_UINTPTR)appstopapplication, 1, RTSITF_GET_SIGNATURE(0, 0xEE13E070), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appstopapplication
	#define EXT_appstopapplication
	#define GET_appstopapplication(fl)  CAL_CMGETAPI( "appstopapplication" ) 
	#define CAL_appstopapplication  appstopapplication
	#define CHK_appstopapplication  TRUE
	#define EXP_appstopapplication  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appstopapplication", (RTS_UINTPTR)appstopapplication, 1, RTSITF_GET_SIGNATURE(0, 0xEE13E070), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappstopapplication
	#define EXT_CmpAppappstopapplication
	#define GET_CmpAppappstopapplication  ERR_OK
	#define CAL_CmpAppappstopapplication  appstopapplication
	#define CHK_CmpAppappstopapplication  TRUE
	#define EXP_CmpAppappstopapplication  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appstopapplication", (RTS_UINTPTR)appstopapplication, 1, RTSITF_GET_SIGNATURE(0, 0xEE13E070), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appstopapplication
	#define EXT_appstopapplication
	#define GET_appstopapplication(fl)  CAL_CMGETAPI( "appstopapplication" ) 
	#define CAL_appstopapplication  appstopapplication
	#define CHK_appstopapplication  TRUE
	#define EXP_appstopapplication  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appstopapplication", (RTS_UINTPTR)appstopapplication, 1, RTSITF_GET_SIGNATURE(0, 0xEE13E070), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appstopapplication  PFAPPSTOPAPPLICATION_IEC pfappstopapplication;
	#define EXT_appstopapplication  extern PFAPPSTOPAPPLICATION_IEC pfappstopapplication;
	#define GET_appstopapplication(fl)  s_pfCMGetAPI2( "appstopapplication", (RTS_VOID_FCTPTR *)&pfappstopapplication, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xEE13E070), 0x03050B00)
	#define CAL_appstopapplication  pfappstopapplication
	#define CHK_appstopapplication  (pfappstopapplication != NULL)
	#define EXP_appstopapplication   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appstopapplication", (RTS_UINTPTR)appstopapplication, 1, RTSITF_GET_SIGNATURE(0, 0xEE13E070), 0x03050B00) 
#endif


/**
 * <description>appstoreretainsinfile</description>
 */
typedef struct tagappstoreretainsinfile_struct
{
	APPLICATION *pApp;					/* VAR_INPUT */	
	RTS_IEC_STRING *pszFilName;			/* VAR_INPUT */	
	RTS_IEC_RESULT AppStoreRetainsInFile;	/* VAR_OUTPUT */	
} appstoreretainsinfile_struct;

void CDECL CDECL_EXT appstoreretainsinfile(appstoreretainsinfile_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPSTORERETAINSINFILE_IEC) (appstoreretainsinfile_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPSTORERETAINSINFILE_NOTIMPLEMENTED)
	#define USE_appstoreretainsinfile
	#define EXT_appstoreretainsinfile
	#define GET_appstoreretainsinfile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appstoreretainsinfile(p0) 
	#define CHK_appstoreretainsinfile  FALSE
	#define EXP_appstoreretainsinfile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appstoreretainsinfile
	#define EXT_appstoreretainsinfile
	#define GET_appstoreretainsinfile(fl)  CAL_CMGETAPI( "appstoreretainsinfile" ) 
	#define CAL_appstoreretainsinfile  appstoreretainsinfile
	#define CHK_appstoreretainsinfile  TRUE
	#define EXP_appstoreretainsinfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appstoreretainsinfile", (RTS_UINTPTR)appstoreretainsinfile, 1, RTSITF_GET_SIGNATURE(0, 0xCBCA082E), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appstoreretainsinfile
	#define EXT_appstoreretainsinfile
	#define GET_appstoreretainsinfile(fl)  CAL_CMGETAPI( "appstoreretainsinfile" ) 
	#define CAL_appstoreretainsinfile  appstoreretainsinfile
	#define CHK_appstoreretainsinfile  TRUE
	#define EXP_appstoreretainsinfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appstoreretainsinfile", (RTS_UINTPTR)appstoreretainsinfile, 1, RTSITF_GET_SIGNATURE(0, 0xCBCA082E), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappstoreretainsinfile
	#define EXT_CmpAppappstoreretainsinfile
	#define GET_CmpAppappstoreretainsinfile  ERR_OK
	#define CAL_CmpAppappstoreretainsinfile  appstoreretainsinfile
	#define CHK_CmpAppappstoreretainsinfile  TRUE
	#define EXP_CmpAppappstoreretainsinfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appstoreretainsinfile", (RTS_UINTPTR)appstoreretainsinfile, 1, RTSITF_GET_SIGNATURE(0, 0xCBCA082E), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_appstoreretainsinfile
	#define EXT_appstoreretainsinfile
	#define GET_appstoreretainsinfile(fl)  CAL_CMGETAPI( "appstoreretainsinfile" ) 
	#define CAL_appstoreretainsinfile  appstoreretainsinfile
	#define CHK_appstoreretainsinfile  TRUE
	#define EXP_appstoreretainsinfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appstoreretainsinfile", (RTS_UINTPTR)appstoreretainsinfile, 1, RTSITF_GET_SIGNATURE(0, 0xCBCA082E), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_appstoreretainsinfile  PFAPPSTORERETAINSINFILE_IEC pfappstoreretainsinfile;
	#define EXT_appstoreretainsinfile  extern PFAPPSTORERETAINSINFILE_IEC pfappstoreretainsinfile;
	#define GET_appstoreretainsinfile(fl)  s_pfCMGetAPI2( "appstoreretainsinfile", (RTS_VOID_FCTPTR *)&pfappstoreretainsinfile, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xCBCA082E), 0x03050B00)
	#define CAL_appstoreretainsinfile  pfappstoreretainsinfile
	#define CHK_appstoreretainsinfile  (pfappstoreretainsinfile != NULL)
	#define EXP_appstoreretainsinfile   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"appstoreretainsinfile", (RTS_UINTPTR)appstoreretainsinfile, 1, RTSITF_GET_SIGNATURE(0, 0xCBCA082E), 0x03050B00) 
#endif


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

void CDECL CDECL_EXT appcheckfileconsistency(appcheckfileconsistency_struct *p);
typedef void (CDECL CDECL_EXT* PFAPPCHECKFILECONSISTENCY_IEC) (appcheckfileconsistency_struct *p);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPCHECKFILECONSISTENCY_NOTIMPLEMENTED)
	#define USE_appcheckfileconsistency
	#define EXT_appcheckfileconsistency
	#define GET_appcheckfileconsistency(fl)  ERR_NOTIMPLEMENTED
	#define CAL_appcheckfileconsistency(p0) 
	#define CHK_appcheckfileconsistency  FALSE
	#define EXP_appcheckfileconsistency  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_appcheckfileconsistency
	#define EXT_appcheckfileconsistency
	#define GET_appcheckfileconsistency(fl)  CAL_CMGETAPI( "appcheckfileconsistency" ) 
	#define CAL_appcheckfileconsistency  appcheckfileconsistency
	#define CHK_appcheckfileconsistency  TRUE
	#define EXP_appcheckfileconsistency  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"appcheckfileconsistency", (RTS_UINTPTR)appcheckfileconsistency, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_appcheckfileconsistency
	#define EXT_appcheckfileconsistency
	#define GET_appcheckfileconsistency(fl)  CAL_CMGETAPI( "appcheckfileconsistency" ) 
	#define CAL_appcheckfileconsistency  appcheckfileconsistency
	#define CHK_appcheckfileconsistency  TRUE
	#define EXP_appcheckfileconsistency  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"appcheckfileconsistency", (RTS_UINTPTR)appcheckfileconsistency, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppappcheckfileconsistency
	#define EXT_CmpAppappcheckfileconsistency
	#define GET_CmpAppappcheckfileconsistency  ERR_OK
	#define CAL_CmpAppappcheckfileconsistency  appcheckfileconsistency
	#define CHK_CmpAppappcheckfileconsistency  TRUE
	#define EXP_CmpAppappcheckfileconsistency  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"appcheckfileconsistency", (RTS_UINTPTR)appcheckfileconsistency, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_appcheckfileconsistency
	#define EXT_appcheckfileconsistency
	#define GET_appcheckfileconsistency(fl)  CAL_CMGETAPI( "appcheckfileconsistency" ) 
	#define CAL_appcheckfileconsistency  appcheckfileconsistency
	#define CHK_appcheckfileconsistency  TRUE
	#define EXP_appcheckfileconsistency  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"appcheckfileconsistency", (RTS_UINTPTR)appcheckfileconsistency, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_appcheckfileconsistency  PFAPPCHECKFILECONSISTENCY_IEC pfappcheckfileconsistency;
	#define EXT_appcheckfileconsistency  extern PFAPPCHECKFILECONSISTENCY_IEC pfappcheckfileconsistency;
	#define GET_appcheckfileconsistency(fl)  s_pfCMGetAPI2( "appcheckfileconsistency", (RTS_VOID_FCTPTR *)&pfappcheckfileconsistency, (fl), 0, 0)
	#define CAL_appcheckfileconsistency  pfappcheckfileconsistency
	#define CHK_appcheckfileconsistency  (pfappcheckfileconsistency != NULL)
	#define EXP_appcheckfileconsistency   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"appcheckfileconsistency", (RTS_UINTPTR)appcheckfileconsistency, 1, 0) 
#endif


/**
 * <description>Creates an application specified by name</description>
 * <param name="pszAppName" type="IN">Pointer to name of the application</param>
 * <param name="pszAppParentName" type="IN">Pointer to name of the parent application (if a child application should be created). Can be NULL.</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the application description</result>
 */
APPLICATION* CDECL AppCreateApplication(char* pszAppName, char* pszAppParentName, RTS_RESULT *pResult);
typedef APPLICATION* (CDECL * PFAPPCREATEAPPLICATION) (char* pszAppName, char* pszAppParentName, RTS_RESULT *pResult);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPCREATEAPPLICATION_NOTIMPLEMENTED)
	#define USE_AppCreateApplication
	#define EXT_AppCreateApplication
	#define GET_AppCreateApplication(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppCreateApplication(p0,p1,p2)  (APPLICATION*)ERR_NOTIMPLEMENTED
	#define CHK_AppCreateApplication  FALSE
	#define EXP_AppCreateApplication  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppCreateApplication
	#define EXT_AppCreateApplication
	#define GET_AppCreateApplication(fl)  CAL_CMGETAPI( "AppCreateApplication" ) 
	#define CAL_AppCreateApplication  AppCreateApplication
	#define CHK_AppCreateApplication  TRUE
	#define EXP_AppCreateApplication  CAL_CMEXPAPI( "AppCreateApplication" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppCreateApplication
	#define EXT_AppCreateApplication
	#define GET_AppCreateApplication(fl)  CAL_CMGETAPI( "AppCreateApplication" ) 
	#define CAL_AppCreateApplication  AppCreateApplication
	#define CHK_AppCreateApplication  TRUE
	#define EXP_AppCreateApplication  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppCreateApplication", (RTS_UINTPTR)AppCreateApplication, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppCreateApplication
	#define EXT_CmpAppAppCreateApplication
	#define GET_CmpAppAppCreateApplication  ERR_OK
	#define CAL_CmpAppAppCreateApplication pICmpApp->IAppCreateApplication
	#define CHK_CmpAppAppCreateApplication (pICmpApp != NULL)
	#define EXP_CmpAppAppCreateApplication  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppCreateApplication
	#define EXT_AppCreateApplication
	#define GET_AppCreateApplication(fl)  CAL_CMGETAPI( "AppCreateApplication" ) 
	#define CAL_AppCreateApplication pICmpApp->IAppCreateApplication
	#define CHK_AppCreateApplication (pICmpApp != NULL)
	#define EXP_AppCreateApplication  CAL_CMEXPAPI( "AppCreateApplication" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppCreateApplication  PFAPPCREATEAPPLICATION pfAppCreateApplication;
	#define EXT_AppCreateApplication  extern PFAPPCREATEAPPLICATION pfAppCreateApplication;
	#define GET_AppCreateApplication(fl)  s_pfCMGetAPI2( "AppCreateApplication", (RTS_VOID_FCTPTR *)&pfAppCreateApplication, (fl), 0, 0)
	#define CAL_AppCreateApplication  pfAppCreateApplication
	#define CHK_AppCreateApplication  (pfAppCreateApplication != NULL)
	#define EXP_AppCreateApplication  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppCreateApplication", (RTS_UINTPTR)AppCreateApplication, 0, 0) 
#endif




/**
 * <description>Prepares a new download or online-change</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="bOnlineChange" type="IN">1=Online change, 0=Download</param>
 * <param name="bCreateBootproject" type="IN">1=Create implicitly a bootproject, 0=Create no bootproject</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppPrepareDownload(APPLICATION* pApp, int bOnlineChange, int bCreateBootproject);
typedef RTS_RESULT (CDECL * PFAPPPREPAREDOWNLOAD) (APPLICATION* pApp, int bOnlineChange, int bCreateBootproject);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPPREPAREDOWNLOAD_NOTIMPLEMENTED)
	#define USE_AppPrepareDownload
	#define EXT_AppPrepareDownload
	#define GET_AppPrepareDownload(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppPrepareDownload(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppPrepareDownload  FALSE
	#define EXP_AppPrepareDownload  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppPrepareDownload
	#define EXT_AppPrepareDownload
	#define GET_AppPrepareDownload(fl)  CAL_CMGETAPI( "AppPrepareDownload" ) 
	#define CAL_AppPrepareDownload  AppPrepareDownload
	#define CHK_AppPrepareDownload  TRUE
	#define EXP_AppPrepareDownload  CAL_CMEXPAPI( "AppPrepareDownload" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppPrepareDownload
	#define EXT_AppPrepareDownload
	#define GET_AppPrepareDownload(fl)  CAL_CMGETAPI( "AppPrepareDownload" ) 
	#define CAL_AppPrepareDownload  AppPrepareDownload
	#define CHK_AppPrepareDownload  TRUE
	#define EXP_AppPrepareDownload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppPrepareDownload", (RTS_UINTPTR)AppPrepareDownload, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppPrepareDownload
	#define EXT_CmpAppAppPrepareDownload
	#define GET_CmpAppAppPrepareDownload  ERR_OK
	#define CAL_CmpAppAppPrepareDownload pICmpApp->IAppPrepareDownload
	#define CHK_CmpAppAppPrepareDownload (pICmpApp != NULL)
	#define EXP_CmpAppAppPrepareDownload  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppPrepareDownload
	#define EXT_AppPrepareDownload
	#define GET_AppPrepareDownload(fl)  CAL_CMGETAPI( "AppPrepareDownload" ) 
	#define CAL_AppPrepareDownload pICmpApp->IAppPrepareDownload
	#define CHK_AppPrepareDownload (pICmpApp != NULL)
	#define EXP_AppPrepareDownload  CAL_CMEXPAPI( "AppPrepareDownload" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppPrepareDownload  PFAPPPREPAREDOWNLOAD pfAppPrepareDownload;
	#define EXT_AppPrepareDownload  extern PFAPPPREPAREDOWNLOAD pfAppPrepareDownload;
	#define GET_AppPrepareDownload(fl)  s_pfCMGetAPI2( "AppPrepareDownload", (RTS_VOID_FCTPTR *)&pfAppPrepareDownload, (fl), 0, 0)
	#define CAL_AppPrepareDownload  pfAppPrepareDownload
	#define CHK_AppPrepareDownload  (pfAppPrepareDownload != NULL)
	#define EXP_AppPrepareDownload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppPrepareDownload", (RTS_UINTPTR)AppPrepareDownload, 0, 0) 
#endif




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
RTS_RESULT CDECL AppAppendCode(APPLICATION *pApp, RTS_UI8 *pbyCode, RTS_SIZE ulCodeLen, RTS_SIZE ulCodeOffset, int bLoadBootproject);
typedef RTS_RESULT (CDECL * PFAPPAPPENDCODE) (APPLICATION *pApp, RTS_UI8 *pbyCode, RTS_SIZE ulCodeLen, RTS_SIZE ulCodeOffset, int bLoadBootproject);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPAPPENDCODE_NOTIMPLEMENTED)
	#define USE_AppAppendCode
	#define EXT_AppAppendCode
	#define GET_AppAppendCode(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppAppendCode(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppAppendCode  FALSE
	#define EXP_AppAppendCode  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppAppendCode
	#define EXT_AppAppendCode
	#define GET_AppAppendCode(fl)  CAL_CMGETAPI( "AppAppendCode" ) 
	#define CAL_AppAppendCode  AppAppendCode
	#define CHK_AppAppendCode  TRUE
	#define EXP_AppAppendCode  CAL_CMEXPAPI( "AppAppendCode" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppAppendCode
	#define EXT_AppAppendCode
	#define GET_AppAppendCode(fl)  CAL_CMGETAPI( "AppAppendCode" ) 
	#define CAL_AppAppendCode  AppAppendCode
	#define CHK_AppAppendCode  TRUE
	#define EXP_AppAppendCode  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppAppendCode", (RTS_UINTPTR)AppAppendCode, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppAppendCode
	#define EXT_CmpAppAppAppendCode
	#define GET_CmpAppAppAppendCode  ERR_OK
	#define CAL_CmpAppAppAppendCode pICmpApp->IAppAppendCode
	#define CHK_CmpAppAppAppendCode (pICmpApp != NULL)
	#define EXP_CmpAppAppAppendCode  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppAppendCode
	#define EXT_AppAppendCode
	#define GET_AppAppendCode(fl)  CAL_CMGETAPI( "AppAppendCode" ) 
	#define CAL_AppAppendCode pICmpApp->IAppAppendCode
	#define CHK_AppAppendCode (pICmpApp != NULL)
	#define EXP_AppAppendCode  CAL_CMEXPAPI( "AppAppendCode" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppAppendCode  PFAPPAPPENDCODE pfAppAppendCode;
	#define EXT_AppAppendCode  extern PFAPPAPPENDCODE pfAppAppendCode;
	#define GET_AppAppendCode(fl)  s_pfCMGetAPI2( "AppAppendCode", (RTS_VOID_FCTPTR *)&pfAppAppendCode, (fl), 0, 0)
	#define CAL_AppAppendCode  pfAppAppendCode
	#define CHK_AppAppendCode  (pfAppAppendCode != NULL)
	#define EXP_AppAppendCode  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppAppendCode", (RTS_UINTPTR)AppAppendCode, 0, 0) 
#endif




/**
 * <description>Complete the download and init application.
 *	NOTE: Actually only available for CmpAppEmbedded!	
 * </description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="bOnlineChange" type="IN">1=Online change, 0=Download</param>
 * <param name="pWriter" type="IN">Pointer to the online writer. Can be NULL.</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppCompleteDownload(APPLICATION* pApp, int bOnlineChange, BINTAGWRITER *pWriter);
typedef RTS_RESULT (CDECL * PFAPPCOMPLETEDOWNLOAD) (APPLICATION* pApp, int bOnlineChange, BINTAGWRITER *pWriter);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPCOMPLETEDOWNLOAD_NOTIMPLEMENTED)
	#define USE_AppCompleteDownload
	#define EXT_AppCompleteDownload
	#define GET_AppCompleteDownload(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppCompleteDownload(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppCompleteDownload  FALSE
	#define EXP_AppCompleteDownload  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppCompleteDownload
	#define EXT_AppCompleteDownload
	#define GET_AppCompleteDownload(fl)  CAL_CMGETAPI( "AppCompleteDownload" ) 
	#define CAL_AppCompleteDownload  AppCompleteDownload
	#define CHK_AppCompleteDownload  TRUE
	#define EXP_AppCompleteDownload  CAL_CMEXPAPI( "AppCompleteDownload" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppCompleteDownload
	#define EXT_AppCompleteDownload
	#define GET_AppCompleteDownload(fl)  CAL_CMGETAPI( "AppCompleteDownload" ) 
	#define CAL_AppCompleteDownload  AppCompleteDownload
	#define CHK_AppCompleteDownload  TRUE
	#define EXP_AppCompleteDownload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppCompleteDownload", (RTS_UINTPTR)AppCompleteDownload, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppCompleteDownload
	#define EXT_CmpAppAppCompleteDownload
	#define GET_CmpAppAppCompleteDownload  ERR_OK
	#define CAL_CmpAppAppCompleteDownload pICmpApp->IAppCompleteDownload
	#define CHK_CmpAppAppCompleteDownload (pICmpApp != NULL)
	#define EXP_CmpAppAppCompleteDownload  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppCompleteDownload
	#define EXT_AppCompleteDownload
	#define GET_AppCompleteDownload(fl)  CAL_CMGETAPI( "AppCompleteDownload" ) 
	#define CAL_AppCompleteDownload pICmpApp->IAppCompleteDownload
	#define CHK_AppCompleteDownload (pICmpApp != NULL)
	#define EXP_AppCompleteDownload  CAL_CMEXPAPI( "AppCompleteDownload" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppCompleteDownload  PFAPPCOMPLETEDOWNLOAD pfAppCompleteDownload;
	#define EXT_AppCompleteDownload  extern PFAPPCOMPLETEDOWNLOAD pfAppCompleteDownload;
	#define GET_AppCompleteDownload(fl)  s_pfCMGetAPI2( "AppCompleteDownload", (RTS_VOID_FCTPTR *)&pfAppCompleteDownload, (fl), 0, 0)
	#define CAL_AppCompleteDownload  pfAppCompleteDownload
	#define CHK_AppCompleteDownload  (pfAppCompleteDownload != NULL)
	#define EXP_AppCompleteDownload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppCompleteDownload", (RTS_UINTPTR)AppCompleteDownload, 0, 0) 
#endif




/**
 * <description>Retrieves an application by name</description>
 * <param name="pszAppName" type="IN" range="[NULL,VALID_APPNAME]">Pointer to name of the application</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Application successfully retrieved</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Parameter pszAppName may not be null</errorcode>
 * <result>Pointer to the application description, null if no App could not be found</result>
 */
APPLICATION* CDECL AppFindApplicationByName(char *pszAppName, RTS_RESULT *pResult);
typedef APPLICATION* (CDECL * PFAPPFINDAPPLICATIONBYNAME) (char *pszAppName, RTS_RESULT *pResult);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPFINDAPPLICATIONBYNAME_NOTIMPLEMENTED)
	#define USE_AppFindApplicationByName
	#define EXT_AppFindApplicationByName
	#define GET_AppFindApplicationByName(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppFindApplicationByName(p0,p1)  (APPLICATION*)ERR_NOTIMPLEMENTED
	#define CHK_AppFindApplicationByName  FALSE
	#define EXP_AppFindApplicationByName  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppFindApplicationByName
	#define EXT_AppFindApplicationByName
	#define GET_AppFindApplicationByName(fl)  CAL_CMGETAPI( "AppFindApplicationByName" ) 
	#define CAL_AppFindApplicationByName  AppFindApplicationByName
	#define CHK_AppFindApplicationByName  TRUE
	#define EXP_AppFindApplicationByName  CAL_CMEXPAPI( "AppFindApplicationByName" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppFindApplicationByName
	#define EXT_AppFindApplicationByName
	#define GET_AppFindApplicationByName(fl)  CAL_CMGETAPI( "AppFindApplicationByName" ) 
	#define CAL_AppFindApplicationByName  AppFindApplicationByName
	#define CHK_AppFindApplicationByName  TRUE
	#define EXP_AppFindApplicationByName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppFindApplicationByName", (RTS_UINTPTR)AppFindApplicationByName, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppFindApplicationByName
	#define EXT_CmpAppAppFindApplicationByName
	#define GET_CmpAppAppFindApplicationByName  ERR_OK
	#define CAL_CmpAppAppFindApplicationByName pICmpApp->IAppFindApplicationByName
	#define CHK_CmpAppAppFindApplicationByName (pICmpApp != NULL)
	#define EXP_CmpAppAppFindApplicationByName  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppFindApplicationByName
	#define EXT_AppFindApplicationByName
	#define GET_AppFindApplicationByName(fl)  CAL_CMGETAPI( "AppFindApplicationByName" ) 
	#define CAL_AppFindApplicationByName pICmpApp->IAppFindApplicationByName
	#define CHK_AppFindApplicationByName (pICmpApp != NULL)
	#define EXP_AppFindApplicationByName  CAL_CMEXPAPI( "AppFindApplicationByName" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppFindApplicationByName  PFAPPFINDAPPLICATIONBYNAME pfAppFindApplicationByName;
	#define EXT_AppFindApplicationByName  extern PFAPPFINDAPPLICATIONBYNAME pfAppFindApplicationByName;
	#define GET_AppFindApplicationByName(fl)  s_pfCMGetAPI2( "AppFindApplicationByName", (RTS_VOID_FCTPTR *)&pfAppFindApplicationByName, (fl), 0, 0)
	#define CAL_AppFindApplicationByName  pfAppFindApplicationByName
	#define CHK_AppFindApplicationByName  (pfAppFindApplicationByName != NULL)
	#define EXP_AppFindApplicationByName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppFindApplicationByName", (RTS_UINTPTR)AppFindApplicationByName, 0, 0) 
#endif




/**
 * <description>Retrieves the number of active sessions for an application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="pulNumSessions" type="OUT">Pointer to variable for storing the number of active sessions</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Number of active sessions successfully retrieved</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Parameters pApp and pulNumSessions may not be null</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppNumOfActiveSessions(APPLICATION *pApp, RTS_UI32* pulNumSessions);
typedef RTS_RESULT (CDECL * PFAPPNUMOFACTIVESESSIONS) (APPLICATION *pApp, RTS_UI32* pulNumSessions);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPNUMOFACTIVESESSIONS_NOTIMPLEMENTED)
	#define USE_AppNumOfActiveSessions
	#define EXT_AppNumOfActiveSessions
	#define GET_AppNumOfActiveSessions(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppNumOfActiveSessions(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppNumOfActiveSessions  FALSE
	#define EXP_AppNumOfActiveSessions  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppNumOfActiveSessions
	#define EXT_AppNumOfActiveSessions
	#define GET_AppNumOfActiveSessions(fl)  CAL_CMGETAPI( "AppNumOfActiveSessions" ) 
	#define CAL_AppNumOfActiveSessions  AppNumOfActiveSessions
	#define CHK_AppNumOfActiveSessions  TRUE
	#define EXP_AppNumOfActiveSessions  CAL_CMEXPAPI( "AppNumOfActiveSessions" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppNumOfActiveSessions
	#define EXT_AppNumOfActiveSessions
	#define GET_AppNumOfActiveSessions(fl)  CAL_CMGETAPI( "AppNumOfActiveSessions" ) 
	#define CAL_AppNumOfActiveSessions  AppNumOfActiveSessions
	#define CHK_AppNumOfActiveSessions  TRUE
	#define EXP_AppNumOfActiveSessions  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppNumOfActiveSessions", (RTS_UINTPTR)AppNumOfActiveSessions, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppNumOfActiveSessions
	#define EXT_CmpAppAppNumOfActiveSessions
	#define GET_CmpAppAppNumOfActiveSessions  ERR_OK
	#define CAL_CmpAppAppNumOfActiveSessions pICmpApp->IAppNumOfActiveSessions
	#define CHK_CmpAppAppNumOfActiveSessions (pICmpApp != NULL)
	#define EXP_CmpAppAppNumOfActiveSessions  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppNumOfActiveSessions
	#define EXT_AppNumOfActiveSessions
	#define GET_AppNumOfActiveSessions(fl)  CAL_CMGETAPI( "AppNumOfActiveSessions" ) 
	#define CAL_AppNumOfActiveSessions pICmpApp->IAppNumOfActiveSessions
	#define CHK_AppNumOfActiveSessions (pICmpApp != NULL)
	#define EXP_AppNumOfActiveSessions  CAL_CMEXPAPI( "AppNumOfActiveSessions" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppNumOfActiveSessions  PFAPPNUMOFACTIVESESSIONS pfAppNumOfActiveSessions;
	#define EXT_AppNumOfActiveSessions  extern PFAPPNUMOFACTIVESESSIONS pfAppNumOfActiveSessions;
	#define GET_AppNumOfActiveSessions(fl)  s_pfCMGetAPI2( "AppNumOfActiveSessions", (RTS_VOID_FCTPTR *)&pfAppNumOfActiveSessions, (fl), 0, 0)
	#define CAL_AppNumOfActiveSessions  pfAppNumOfActiveSessions
	#define CHK_AppNumOfActiveSessions  (pfAppNumOfActiveSessions != NULL)
	#define EXP_AppNumOfActiveSessions  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppNumOfActiveSessions", (RTS_UINTPTR)AppNumOfActiveSessions, 0, 0) 
#endif





/**
 * <description>Retrieves an application by name</description>
 * <param name="pszBootprojectName" type="IN">Pointer to name of the bootproject. Must not be the application name!</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the application description</result>
 */
APPLICATION* CDECL AppFindApplicationByBootproject(char *pszBootprojectName, RTS_RESULT *pResult);
typedef APPLICATION* (CDECL * PFAPPFINDAPPLICATIONBYBOOTPROJECT) (char *pszBootprojectName, RTS_RESULT *pResult);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPFINDAPPLICATIONBYBOOTPROJECT_NOTIMPLEMENTED)
	#define USE_AppFindApplicationByBootproject
	#define EXT_AppFindApplicationByBootproject
	#define GET_AppFindApplicationByBootproject(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppFindApplicationByBootproject(p0,p1)  (APPLICATION*)ERR_NOTIMPLEMENTED
	#define CHK_AppFindApplicationByBootproject  FALSE
	#define EXP_AppFindApplicationByBootproject  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppFindApplicationByBootproject
	#define EXT_AppFindApplicationByBootproject
	#define GET_AppFindApplicationByBootproject(fl)  CAL_CMGETAPI( "AppFindApplicationByBootproject" ) 
	#define CAL_AppFindApplicationByBootproject  AppFindApplicationByBootproject
	#define CHK_AppFindApplicationByBootproject  TRUE
	#define EXP_AppFindApplicationByBootproject  CAL_CMEXPAPI( "AppFindApplicationByBootproject" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppFindApplicationByBootproject
	#define EXT_AppFindApplicationByBootproject
	#define GET_AppFindApplicationByBootproject(fl)  CAL_CMGETAPI( "AppFindApplicationByBootproject" ) 
	#define CAL_AppFindApplicationByBootproject  AppFindApplicationByBootproject
	#define CHK_AppFindApplicationByBootproject  TRUE
	#define EXP_AppFindApplicationByBootproject  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppFindApplicationByBootproject", (RTS_UINTPTR)AppFindApplicationByBootproject, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppFindApplicationByBootproject
	#define EXT_CmpAppAppFindApplicationByBootproject
	#define GET_CmpAppAppFindApplicationByBootproject  ERR_OK
	#define CAL_CmpAppAppFindApplicationByBootproject pICmpApp->IAppFindApplicationByBootproject
	#define CHK_CmpAppAppFindApplicationByBootproject (pICmpApp != NULL)
	#define EXP_CmpAppAppFindApplicationByBootproject  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppFindApplicationByBootproject
	#define EXT_AppFindApplicationByBootproject
	#define GET_AppFindApplicationByBootproject(fl)  CAL_CMGETAPI( "AppFindApplicationByBootproject" ) 
	#define CAL_AppFindApplicationByBootproject pICmpApp->IAppFindApplicationByBootproject
	#define CHK_AppFindApplicationByBootproject (pICmpApp != NULL)
	#define EXP_AppFindApplicationByBootproject  CAL_CMEXPAPI( "AppFindApplicationByBootproject" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppFindApplicationByBootproject  PFAPPFINDAPPLICATIONBYBOOTPROJECT pfAppFindApplicationByBootproject;
	#define EXT_AppFindApplicationByBootproject  extern PFAPPFINDAPPLICATIONBYBOOTPROJECT pfAppFindApplicationByBootproject;
	#define GET_AppFindApplicationByBootproject(fl)  s_pfCMGetAPI2( "AppFindApplicationByBootproject", (RTS_VOID_FCTPTR *)&pfAppFindApplicationByBootproject, (fl), 0, 0)
	#define CAL_AppFindApplicationByBootproject  pfAppFindApplicationByBootproject
	#define CHK_AppFindApplicationByBootproject  (pfAppFindApplicationByBootproject != NULL)
	#define EXP_AppFindApplicationByBootproject  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppFindApplicationByBootproject", (RTS_UINTPTR)AppFindApplicationByBootproject, 0, 0) 
#endif




/**
 * <description>Retrieves an application by session id. The session id is an unique id that is provided
 *	from the login service. There is a relation between the communication channel and the session id.</description>
 * <param name="ulSessionId" type="IN">SessionId from login service</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the application description</result>
 */
APPLICATION* CDECL AppFindApplicationBySessionId(RTS_UI32 ulSessionId, RTS_RESULT *pResult);
typedef APPLICATION* (CDECL * PFAPPFINDAPPLICATIONBYSESSIONID) (RTS_UI32 ulSessionId, RTS_RESULT *pResult);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPFINDAPPLICATIONBYSESSIONID_NOTIMPLEMENTED)
	#define USE_AppFindApplicationBySessionId
	#define EXT_AppFindApplicationBySessionId
	#define GET_AppFindApplicationBySessionId(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppFindApplicationBySessionId(p0,p1)  (APPLICATION*)ERR_NOTIMPLEMENTED
	#define CHK_AppFindApplicationBySessionId  FALSE
	#define EXP_AppFindApplicationBySessionId  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppFindApplicationBySessionId
	#define EXT_AppFindApplicationBySessionId
	#define GET_AppFindApplicationBySessionId(fl)  CAL_CMGETAPI( "AppFindApplicationBySessionId" ) 
	#define CAL_AppFindApplicationBySessionId  AppFindApplicationBySessionId
	#define CHK_AppFindApplicationBySessionId  TRUE
	#define EXP_AppFindApplicationBySessionId  CAL_CMEXPAPI( "AppFindApplicationBySessionId" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppFindApplicationBySessionId
	#define EXT_AppFindApplicationBySessionId
	#define GET_AppFindApplicationBySessionId(fl)  CAL_CMGETAPI( "AppFindApplicationBySessionId" ) 
	#define CAL_AppFindApplicationBySessionId  AppFindApplicationBySessionId
	#define CHK_AppFindApplicationBySessionId  TRUE
	#define EXP_AppFindApplicationBySessionId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppFindApplicationBySessionId", (RTS_UINTPTR)AppFindApplicationBySessionId, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppFindApplicationBySessionId
	#define EXT_CmpAppAppFindApplicationBySessionId
	#define GET_CmpAppAppFindApplicationBySessionId  ERR_OK
	#define CAL_CmpAppAppFindApplicationBySessionId pICmpApp->IAppFindApplicationBySessionId
	#define CHK_CmpAppAppFindApplicationBySessionId (pICmpApp != NULL)
	#define EXP_CmpAppAppFindApplicationBySessionId  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppFindApplicationBySessionId
	#define EXT_AppFindApplicationBySessionId
	#define GET_AppFindApplicationBySessionId(fl)  CAL_CMGETAPI( "AppFindApplicationBySessionId" ) 
	#define CAL_AppFindApplicationBySessionId pICmpApp->IAppFindApplicationBySessionId
	#define CHK_AppFindApplicationBySessionId (pICmpApp != NULL)
	#define EXP_AppFindApplicationBySessionId  CAL_CMEXPAPI( "AppFindApplicationBySessionId" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppFindApplicationBySessionId  PFAPPFINDAPPLICATIONBYSESSIONID pfAppFindApplicationBySessionId;
	#define EXT_AppFindApplicationBySessionId  extern PFAPPFINDAPPLICATIONBYSESSIONID pfAppFindApplicationBySessionId;
	#define GET_AppFindApplicationBySessionId(fl)  s_pfCMGetAPI2( "AppFindApplicationBySessionId", (RTS_VOID_FCTPTR *)&pfAppFindApplicationBySessionId, (fl), 0, 0)
	#define CAL_AppFindApplicationBySessionId  pfAppFindApplicationBySessionId
	#define CHK_AppFindApplicationBySessionId  (pfAppFindApplicationBySessionId != NULL)
	#define EXP_AppFindApplicationBySessionId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppFindApplicationBySessionId", (RTS_UINTPTR)AppFindApplicationBySessionId, 0, 0) 
#endif




/**
 * <description>Retrieves an application by its id.</description>
 * <param name="iId" type="IN">Id of the application</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the application description</result>
 */
APPLICATION* CDECL AppFindApplicationById(int iId, RTS_RESULT *pResult);
typedef APPLICATION* (CDECL * PFAPPFINDAPPLICATIONBYID) (int iId, RTS_RESULT *pResult);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPFINDAPPLICATIONBYID_NOTIMPLEMENTED)
	#define USE_AppFindApplicationById
	#define EXT_AppFindApplicationById
	#define GET_AppFindApplicationById(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppFindApplicationById(p0,p1)  (APPLICATION*)ERR_NOTIMPLEMENTED
	#define CHK_AppFindApplicationById  FALSE
	#define EXP_AppFindApplicationById  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppFindApplicationById
	#define EXT_AppFindApplicationById
	#define GET_AppFindApplicationById(fl)  CAL_CMGETAPI( "AppFindApplicationById" ) 
	#define CAL_AppFindApplicationById  AppFindApplicationById
	#define CHK_AppFindApplicationById  TRUE
	#define EXP_AppFindApplicationById  CAL_CMEXPAPI( "AppFindApplicationById" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppFindApplicationById
	#define EXT_AppFindApplicationById
	#define GET_AppFindApplicationById(fl)  CAL_CMGETAPI( "AppFindApplicationById" ) 
	#define CAL_AppFindApplicationById  AppFindApplicationById
	#define CHK_AppFindApplicationById  TRUE
	#define EXP_AppFindApplicationById  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppFindApplicationById", (RTS_UINTPTR)AppFindApplicationById, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppFindApplicationById
	#define EXT_CmpAppAppFindApplicationById
	#define GET_CmpAppAppFindApplicationById  ERR_OK
	#define CAL_CmpAppAppFindApplicationById pICmpApp->IAppFindApplicationById
	#define CHK_CmpAppAppFindApplicationById (pICmpApp != NULL)
	#define EXP_CmpAppAppFindApplicationById  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppFindApplicationById
	#define EXT_AppFindApplicationById
	#define GET_AppFindApplicationById(fl)  CAL_CMGETAPI( "AppFindApplicationById" ) 
	#define CAL_AppFindApplicationById pICmpApp->IAppFindApplicationById
	#define CHK_AppFindApplicationById (pICmpApp != NULL)
	#define EXP_AppFindApplicationById  CAL_CMEXPAPI( "AppFindApplicationById" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppFindApplicationById  PFAPPFINDAPPLICATIONBYID pfAppFindApplicationById;
	#define EXT_AppFindApplicationById  extern PFAPPFINDAPPLICATIONBYID pfAppFindApplicationById;
	#define GET_AppFindApplicationById(fl)  s_pfCMGetAPI2( "AppFindApplicationById", (RTS_VOID_FCTPTR *)&pfAppFindApplicationById, (fl), 0, 0)
	#define CAL_AppFindApplicationById  pfAppFindApplicationById
	#define CHK_AppFindApplicationById  (pfAppFindApplicationById != NULL)
	#define EXP_AppFindApplicationById  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppFindApplicationById", (RTS_UINTPTR)AppFindApplicationById, 0, 0) 
#endif




/**
 * <description>Retrieves the number of registered and loaded applications.</description>
 * <result>Number of registered applications</result>
 */
int CDECL AppGetNumOfApplications(void);
typedef int (CDECL * PFAPPGETNUMOFAPPLICATIONS) (void);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETNUMOFAPPLICATIONS_NOTIMPLEMENTED)
	#define USE_AppGetNumOfApplications
	#define EXT_AppGetNumOfApplications
	#define GET_AppGetNumOfApplications(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetNumOfApplications()  (int)ERR_NOTIMPLEMENTED
	#define CHK_AppGetNumOfApplications  FALSE
	#define EXP_AppGetNumOfApplications  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetNumOfApplications
	#define EXT_AppGetNumOfApplications
	#define GET_AppGetNumOfApplications(fl)  CAL_CMGETAPI( "AppGetNumOfApplications" ) 
	#define CAL_AppGetNumOfApplications  AppGetNumOfApplications
	#define CHK_AppGetNumOfApplications  TRUE
	#define EXP_AppGetNumOfApplications  CAL_CMEXPAPI( "AppGetNumOfApplications" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetNumOfApplications
	#define EXT_AppGetNumOfApplications
	#define GET_AppGetNumOfApplications(fl)  CAL_CMGETAPI( "AppGetNumOfApplications" ) 
	#define CAL_AppGetNumOfApplications  AppGetNumOfApplications
	#define CHK_AppGetNumOfApplications  TRUE
	#define EXP_AppGetNumOfApplications  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetNumOfApplications", (RTS_UINTPTR)AppGetNumOfApplications, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetNumOfApplications
	#define EXT_CmpAppAppGetNumOfApplications
	#define GET_CmpAppAppGetNumOfApplications  ERR_OK
	#define CAL_CmpAppAppGetNumOfApplications pICmpApp->IAppGetNumOfApplications
	#define CHK_CmpAppAppGetNumOfApplications (pICmpApp != NULL)
	#define EXP_CmpAppAppGetNumOfApplications  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetNumOfApplications
	#define EXT_AppGetNumOfApplications
	#define GET_AppGetNumOfApplications(fl)  CAL_CMGETAPI( "AppGetNumOfApplications" ) 
	#define CAL_AppGetNumOfApplications pICmpApp->IAppGetNumOfApplications
	#define CHK_AppGetNumOfApplications (pICmpApp != NULL)
	#define EXP_AppGetNumOfApplications  CAL_CMEXPAPI( "AppGetNumOfApplications" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetNumOfApplications  PFAPPGETNUMOFAPPLICATIONS pfAppGetNumOfApplications;
	#define EXT_AppGetNumOfApplications  extern PFAPPGETNUMOFAPPLICATIONS pfAppGetNumOfApplications;
	#define GET_AppGetNumOfApplications(fl)  s_pfCMGetAPI2( "AppGetNumOfApplications", (RTS_VOID_FCTPTR *)&pfAppGetNumOfApplications, (fl), 0, 0)
	#define CAL_AppGetNumOfApplications  pfAppGetNumOfApplications
	#define CHK_AppGetNumOfApplications  (pfAppGetNumOfApplications != NULL)
	#define EXP_AppGetNumOfApplications  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetNumOfApplications", (RTS_UINTPTR)AppGetNumOfApplications, 0, 0) 
#endif




/**
 * <description>Retrieves an application description sepcified by index</description>
 * <param name="iIndex" type="IN" range="[0..APPL_NUM_OF_STATIC_APPLS-1,APPL_NUM_OF_STATIC_APPLS..INT_MAX]">Index of the application list.</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Application successfully retrieved</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Application with index iIndex not found</errorcode>
 * <result>Pointer to the application description</result>
 */
APPLICATION* CDECL AppGetApplicationByIndex(int iIndex, RTS_RESULT *pResult);
typedef APPLICATION* (CDECL * PFAPPGETAPPLICATIONBYINDEX) (int iIndex, RTS_RESULT *pResult);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETAPPLICATIONBYINDEX_NOTIMPLEMENTED)
	#define USE_AppGetApplicationByIndex
	#define EXT_AppGetApplicationByIndex
	#define GET_AppGetApplicationByIndex(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetApplicationByIndex(p0,p1)  (APPLICATION*)ERR_NOTIMPLEMENTED
	#define CHK_AppGetApplicationByIndex  FALSE
	#define EXP_AppGetApplicationByIndex  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetApplicationByIndex
	#define EXT_AppGetApplicationByIndex
	#define GET_AppGetApplicationByIndex(fl)  CAL_CMGETAPI( "AppGetApplicationByIndex" ) 
	#define CAL_AppGetApplicationByIndex  AppGetApplicationByIndex
	#define CHK_AppGetApplicationByIndex  TRUE
	#define EXP_AppGetApplicationByIndex  CAL_CMEXPAPI( "AppGetApplicationByIndex" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetApplicationByIndex
	#define EXT_AppGetApplicationByIndex
	#define GET_AppGetApplicationByIndex(fl)  CAL_CMGETAPI( "AppGetApplicationByIndex" ) 
	#define CAL_AppGetApplicationByIndex  AppGetApplicationByIndex
	#define CHK_AppGetApplicationByIndex  TRUE
	#define EXP_AppGetApplicationByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetApplicationByIndex", (RTS_UINTPTR)AppGetApplicationByIndex, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetApplicationByIndex
	#define EXT_CmpAppAppGetApplicationByIndex
	#define GET_CmpAppAppGetApplicationByIndex  ERR_OK
	#define CAL_CmpAppAppGetApplicationByIndex pICmpApp->IAppGetApplicationByIndex
	#define CHK_CmpAppAppGetApplicationByIndex (pICmpApp != NULL)
	#define EXP_CmpAppAppGetApplicationByIndex  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetApplicationByIndex
	#define EXT_AppGetApplicationByIndex
	#define GET_AppGetApplicationByIndex(fl)  CAL_CMGETAPI( "AppGetApplicationByIndex" ) 
	#define CAL_AppGetApplicationByIndex pICmpApp->IAppGetApplicationByIndex
	#define CHK_AppGetApplicationByIndex (pICmpApp != NULL)
	#define EXP_AppGetApplicationByIndex  CAL_CMEXPAPI( "AppGetApplicationByIndex" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetApplicationByIndex  PFAPPGETAPPLICATIONBYINDEX pfAppGetApplicationByIndex;
	#define EXT_AppGetApplicationByIndex  extern PFAPPGETAPPLICATIONBYINDEX pfAppGetApplicationByIndex;
	#define GET_AppGetApplicationByIndex(fl)  s_pfCMGetAPI2( "AppGetApplicationByIndex", (RTS_VOID_FCTPTR *)&pfAppGetApplicationByIndex, (fl), 0, 0)
	#define CAL_AppGetApplicationByIndex  pfAppGetApplicationByIndex
	#define CHK_AppGetApplicationByIndex  (pfAppGetApplicationByIndex != NULL)
	#define EXP_AppGetApplicationByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetApplicationByIndex", (RTS_UINTPTR)AppGetApplicationByIndex, 0, 0) 
#endif





/**
 * <description>Retrieves an application description which contains the specified memory address or NULL if failed (memory cannot be assiciated to an application)</description>
 * <param name="pAddress" type="IN">Pointer to memory</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the application description or NULL if memory pointer cannot be assiciated to an application</result>
 */
APPLICATION * CDECL AppGetApplicationByAreaAddress(void *pAddress, RTS_RESULT *pResult);
typedef APPLICATION * (CDECL * PFAPPGETAPPLICATIONBYAREAADDRESS) (void *pAddress, RTS_RESULT *pResult);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETAPPLICATIONBYAREAADDRESS_NOTIMPLEMENTED)
	#define USE_AppGetApplicationByAreaAddress
	#define EXT_AppGetApplicationByAreaAddress
	#define GET_AppGetApplicationByAreaAddress(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetApplicationByAreaAddress(p0,p1)  (APPLICATION *)ERR_NOTIMPLEMENTED
	#define CHK_AppGetApplicationByAreaAddress  FALSE
	#define EXP_AppGetApplicationByAreaAddress  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetApplicationByAreaAddress
	#define EXT_AppGetApplicationByAreaAddress
	#define GET_AppGetApplicationByAreaAddress(fl)  CAL_CMGETAPI( "AppGetApplicationByAreaAddress" ) 
	#define CAL_AppGetApplicationByAreaAddress  AppGetApplicationByAreaAddress
	#define CHK_AppGetApplicationByAreaAddress  TRUE
	#define EXP_AppGetApplicationByAreaAddress  CAL_CMEXPAPI( "AppGetApplicationByAreaAddress" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetApplicationByAreaAddress
	#define EXT_AppGetApplicationByAreaAddress
	#define GET_AppGetApplicationByAreaAddress(fl)  CAL_CMGETAPI( "AppGetApplicationByAreaAddress" ) 
	#define CAL_AppGetApplicationByAreaAddress  AppGetApplicationByAreaAddress
	#define CHK_AppGetApplicationByAreaAddress  TRUE
	#define EXP_AppGetApplicationByAreaAddress  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetApplicationByAreaAddress", (RTS_UINTPTR)AppGetApplicationByAreaAddress, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetApplicationByAreaAddress
	#define EXT_CmpAppAppGetApplicationByAreaAddress
	#define GET_CmpAppAppGetApplicationByAreaAddress  ERR_OK
	#define CAL_CmpAppAppGetApplicationByAreaAddress pICmpApp->IAppGetApplicationByAreaAddress
	#define CHK_CmpAppAppGetApplicationByAreaAddress (pICmpApp != NULL)
	#define EXP_CmpAppAppGetApplicationByAreaAddress  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetApplicationByAreaAddress
	#define EXT_AppGetApplicationByAreaAddress
	#define GET_AppGetApplicationByAreaAddress(fl)  CAL_CMGETAPI( "AppGetApplicationByAreaAddress" ) 
	#define CAL_AppGetApplicationByAreaAddress pICmpApp->IAppGetApplicationByAreaAddress
	#define CHK_AppGetApplicationByAreaAddress (pICmpApp != NULL)
	#define EXP_AppGetApplicationByAreaAddress  CAL_CMEXPAPI( "AppGetApplicationByAreaAddress" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetApplicationByAreaAddress  PFAPPGETAPPLICATIONBYAREAADDRESS pfAppGetApplicationByAreaAddress;
	#define EXT_AppGetApplicationByAreaAddress  extern PFAPPGETAPPLICATIONBYAREAADDRESS pfAppGetApplicationByAreaAddress;
	#define GET_AppGetApplicationByAreaAddress(fl)  s_pfCMGetAPI2( "AppGetApplicationByAreaAddress", (RTS_VOID_FCTPTR *)&pfAppGetApplicationByAreaAddress, (fl), 0, 0)
	#define CAL_AppGetApplicationByAreaAddress  pfAppGetApplicationByAreaAddress
	#define CHK_AppGetApplicationByAreaAddress  (pfAppGetApplicationByAreaAddress != NULL)
	#define EXP_AppGetApplicationByAreaAddress  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetApplicationByAreaAddress", (RTS_UINTPTR)AppGetApplicationByAreaAddress, 0, 0) 
#endif




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
RTS_RESULT CDECL AppGetAreaPointer(APPLICATION *pApp, int iArea, unsigned char **ppucArea);
typedef RTS_RESULT (CDECL * PFAPPGETAREAPOINTER) (APPLICATION *pApp, int iArea, unsigned char **ppucArea);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETAREAPOINTER_NOTIMPLEMENTED)
	#define USE_AppGetAreaPointer
	#define EXT_AppGetAreaPointer
	#define GET_AppGetAreaPointer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetAreaPointer(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppGetAreaPointer  FALSE
	#define EXP_AppGetAreaPointer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetAreaPointer
	#define EXT_AppGetAreaPointer
	#define GET_AppGetAreaPointer(fl)  CAL_CMGETAPI( "AppGetAreaPointer" ) 
	#define CAL_AppGetAreaPointer  AppGetAreaPointer
	#define CHK_AppGetAreaPointer  TRUE
	#define EXP_AppGetAreaPointer  CAL_CMEXPAPI( "AppGetAreaPointer" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetAreaPointer
	#define EXT_AppGetAreaPointer
	#define GET_AppGetAreaPointer(fl)  CAL_CMGETAPI( "AppGetAreaPointer" ) 
	#define CAL_AppGetAreaPointer  AppGetAreaPointer
	#define CHK_AppGetAreaPointer  TRUE
	#define EXP_AppGetAreaPointer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetAreaPointer", (RTS_UINTPTR)AppGetAreaPointer, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetAreaPointer
	#define EXT_CmpAppAppGetAreaPointer
	#define GET_CmpAppAppGetAreaPointer  ERR_OK
	#define CAL_CmpAppAppGetAreaPointer pICmpApp->IAppGetAreaPointer
	#define CHK_CmpAppAppGetAreaPointer (pICmpApp != NULL)
	#define EXP_CmpAppAppGetAreaPointer  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetAreaPointer
	#define EXT_AppGetAreaPointer
	#define GET_AppGetAreaPointer(fl)  CAL_CMGETAPI( "AppGetAreaPointer" ) 
	#define CAL_AppGetAreaPointer pICmpApp->IAppGetAreaPointer
	#define CHK_AppGetAreaPointer (pICmpApp != NULL)
	#define EXP_AppGetAreaPointer  CAL_CMEXPAPI( "AppGetAreaPointer" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetAreaPointer  PFAPPGETAREAPOINTER pfAppGetAreaPointer;
	#define EXT_AppGetAreaPointer  extern PFAPPGETAREAPOINTER pfAppGetAreaPointer;
	#define GET_AppGetAreaPointer(fl)  s_pfCMGetAPI2( "AppGetAreaPointer", (RTS_VOID_FCTPTR *)&pfAppGetAreaPointer, (fl), 0, 0)
	#define CAL_AppGetAreaPointer  pfAppGetAreaPointer
	#define CHK_AppGetAreaPointer  (pfAppGetAreaPointer != NULL)
	#define EXP_AppGetAreaPointer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetAreaPointer", (RTS_UINTPTR)AppGetAreaPointer, 0, 0) 
#endif




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
RTS_RESULT CDECL AppGetAreaPointer2(APPLICATION *pApp, RTS_I32 iArea, RTS_UI8 **ppbyArea, RTS_SIZE *pulSize);
typedef RTS_RESULT (CDECL * PFAPPGETAREAPOINTER2) (APPLICATION *pApp, RTS_I32 iArea, RTS_UI8 **ppbyArea, RTS_SIZE *pulSize);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETAREAPOINTER2_NOTIMPLEMENTED)
	#define USE_AppGetAreaPointer2
	#define EXT_AppGetAreaPointer2
	#define GET_AppGetAreaPointer2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetAreaPointer2(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppGetAreaPointer2  FALSE
	#define EXP_AppGetAreaPointer2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetAreaPointer2
	#define EXT_AppGetAreaPointer2
	#define GET_AppGetAreaPointer2(fl)  CAL_CMGETAPI( "AppGetAreaPointer2" ) 
	#define CAL_AppGetAreaPointer2  AppGetAreaPointer2
	#define CHK_AppGetAreaPointer2  TRUE
	#define EXP_AppGetAreaPointer2  CAL_CMEXPAPI( "AppGetAreaPointer2" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetAreaPointer2
	#define EXT_AppGetAreaPointer2
	#define GET_AppGetAreaPointer2(fl)  CAL_CMGETAPI( "AppGetAreaPointer2" ) 
	#define CAL_AppGetAreaPointer2  AppGetAreaPointer2
	#define CHK_AppGetAreaPointer2  TRUE
	#define EXP_AppGetAreaPointer2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetAreaPointer2", (RTS_UINTPTR)AppGetAreaPointer2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetAreaPointer2
	#define EXT_CmpAppAppGetAreaPointer2
	#define GET_CmpAppAppGetAreaPointer2  ERR_OK
	#define CAL_CmpAppAppGetAreaPointer2 pICmpApp->IAppGetAreaPointer2
	#define CHK_CmpAppAppGetAreaPointer2 (pICmpApp != NULL)
	#define EXP_CmpAppAppGetAreaPointer2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetAreaPointer2
	#define EXT_AppGetAreaPointer2
	#define GET_AppGetAreaPointer2(fl)  CAL_CMGETAPI( "AppGetAreaPointer2" ) 
	#define CAL_AppGetAreaPointer2 pICmpApp->IAppGetAreaPointer2
	#define CHK_AppGetAreaPointer2 (pICmpApp != NULL)
	#define EXP_AppGetAreaPointer2  CAL_CMEXPAPI( "AppGetAreaPointer2" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetAreaPointer2  PFAPPGETAREAPOINTER2 pfAppGetAreaPointer2;
	#define EXT_AppGetAreaPointer2  extern PFAPPGETAREAPOINTER2 pfAppGetAreaPointer2;
	#define GET_AppGetAreaPointer2(fl)  s_pfCMGetAPI2( "AppGetAreaPointer2", (RTS_VOID_FCTPTR *)&pfAppGetAreaPointer2, (fl), 0, 0)
	#define CAL_AppGetAreaPointer2  pfAppGetAreaPointer2
	#define CHK_AppGetAreaPointer2  (pfAppGetAreaPointer2 != NULL)
	#define EXP_AppGetAreaPointer2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetAreaPointer2", (RTS_UINTPTR)AppGetAreaPointer2, 0, 0) 
#endif




/**
 * <description>Retrieves a pointer to the memory area specified by type and index</description>
 * <param name="pszAppName" type="IN">Application name</param>
 * <param name="iArea" type="IN">Area index</param>
 * <param name="usType" type="IN">Area type. See category "Area Types" in SysMemItf.h.</param>
 * <param name="ppucArea" type="OUT">Pointer pointer to the area</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppGetAreaPointerByType(char* pszAppName, int iArea, RTS_UI16 usType, unsigned char **ppucArea);
typedef RTS_RESULT (CDECL * PFAPPGETAREAPOINTERBYTYPE) (char* pszAppName, int iArea, RTS_UI16 usType, unsigned char **ppucArea);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETAREAPOINTERBYTYPE_NOTIMPLEMENTED)
	#define USE_AppGetAreaPointerByType
	#define EXT_AppGetAreaPointerByType
	#define GET_AppGetAreaPointerByType(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetAreaPointerByType(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppGetAreaPointerByType  FALSE
	#define EXP_AppGetAreaPointerByType  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetAreaPointerByType
	#define EXT_AppGetAreaPointerByType
	#define GET_AppGetAreaPointerByType(fl)  CAL_CMGETAPI( "AppGetAreaPointerByType" ) 
	#define CAL_AppGetAreaPointerByType  AppGetAreaPointerByType
	#define CHK_AppGetAreaPointerByType  TRUE
	#define EXP_AppGetAreaPointerByType  CAL_CMEXPAPI( "AppGetAreaPointerByType" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetAreaPointerByType
	#define EXT_AppGetAreaPointerByType
	#define GET_AppGetAreaPointerByType(fl)  CAL_CMGETAPI( "AppGetAreaPointerByType" ) 
	#define CAL_AppGetAreaPointerByType  AppGetAreaPointerByType
	#define CHK_AppGetAreaPointerByType  TRUE
	#define EXP_AppGetAreaPointerByType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetAreaPointerByType", (RTS_UINTPTR)AppGetAreaPointerByType, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetAreaPointerByType
	#define EXT_CmpAppAppGetAreaPointerByType
	#define GET_CmpAppAppGetAreaPointerByType  ERR_OK
	#define CAL_CmpAppAppGetAreaPointerByType pICmpApp->IAppGetAreaPointerByType
	#define CHK_CmpAppAppGetAreaPointerByType (pICmpApp != NULL)
	#define EXP_CmpAppAppGetAreaPointerByType  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetAreaPointerByType
	#define EXT_AppGetAreaPointerByType
	#define GET_AppGetAreaPointerByType(fl)  CAL_CMGETAPI( "AppGetAreaPointerByType" ) 
	#define CAL_AppGetAreaPointerByType pICmpApp->IAppGetAreaPointerByType
	#define CHK_AppGetAreaPointerByType (pICmpApp != NULL)
	#define EXP_AppGetAreaPointerByType  CAL_CMEXPAPI( "AppGetAreaPointerByType" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetAreaPointerByType  PFAPPGETAREAPOINTERBYTYPE pfAppGetAreaPointerByType;
	#define EXT_AppGetAreaPointerByType  extern PFAPPGETAREAPOINTERBYTYPE pfAppGetAreaPointerByType;
	#define GET_AppGetAreaPointerByType(fl)  s_pfCMGetAPI2( "AppGetAreaPointerByType", (RTS_VOID_FCTPTR *)&pfAppGetAreaPointerByType, (fl), 0, 0)
	#define CAL_AppGetAreaPointerByType  pfAppGetAreaPointerByType
	#define CHK_AppGetAreaPointerByType  (pfAppGetAreaPointerByType != NULL)
	#define EXP_AppGetAreaPointerByType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetAreaPointerByType", (RTS_UINTPTR)AppGetAreaPointerByType, 0, 0) 
#endif




/**
 * <description>Function checks, if the address is a part of the specified application (resides in an area)</description>
 * <param name="pApp" type="IN">Application</param>
 * <param name="pAddress" type="IN">Pointer to check. Can be a data pointer or a function pointer.</param>
 * <result>ERR_OK: pAddress is part of the specified application
 *		   ERR_FAILED: pAddress is not a part of the specified application
 * </result>
 */
RTS_RESULT CDECL AppHasAddress(APPLICATION* pApp, RTS_VOID_FCTPTR pAddress);
typedef RTS_RESULT (CDECL * PFAPPHASADDRESS) (APPLICATION* pApp, RTS_VOID_FCTPTR pAddress);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPHASADDRESS_NOTIMPLEMENTED)
	#define USE_AppHasAddress
	#define EXT_AppHasAddress
	#define GET_AppHasAddress(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppHasAddress(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppHasAddress  FALSE
	#define EXP_AppHasAddress  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppHasAddress
	#define EXT_AppHasAddress
	#define GET_AppHasAddress(fl)  CAL_CMGETAPI( "AppHasAddress" ) 
	#define CAL_AppHasAddress  AppHasAddress
	#define CHK_AppHasAddress  TRUE
	#define EXP_AppHasAddress  CAL_CMEXPAPI( "AppHasAddress" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppHasAddress
	#define EXT_AppHasAddress
	#define GET_AppHasAddress(fl)  CAL_CMGETAPI( "AppHasAddress" ) 
	#define CAL_AppHasAddress  AppHasAddress
	#define CHK_AppHasAddress  TRUE
	#define EXP_AppHasAddress  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppHasAddress", (RTS_UINTPTR)AppHasAddress, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppHasAddress
	#define EXT_CmpAppAppHasAddress
	#define GET_CmpAppAppHasAddress  ERR_OK
	#define CAL_CmpAppAppHasAddress pICmpApp->IAppHasAddress
	#define CHK_CmpAppAppHasAddress (pICmpApp != NULL)
	#define EXP_CmpAppAppHasAddress  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppHasAddress
	#define EXT_AppHasAddress
	#define GET_AppHasAddress(fl)  CAL_CMGETAPI( "AppHasAddress" ) 
	#define CAL_AppHasAddress pICmpApp->IAppHasAddress
	#define CHK_AppHasAddress (pICmpApp != NULL)
	#define EXP_AppHasAddress  CAL_CMEXPAPI( "AppHasAddress" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppHasAddress  PFAPPHASADDRESS pfAppHasAddress;
	#define EXT_AppHasAddress  extern PFAPPHASADDRESS pfAppHasAddress;
	#define GET_AppHasAddress(fl)  s_pfCMGetAPI2( "AppHasAddress", (RTS_VOID_FCTPTR *)&pfAppHasAddress, (fl), 0, 0)
	#define CAL_AppHasAddress  pfAppHasAddress
	#define CHK_AppHasAddress  (pfAppHasAddress != NULL)
	#define EXP_AppHasAddress  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppHasAddress", (RTS_UINTPTR)AppHasAddress, 0, 0) 
#endif




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
RTS_RESULT CDECL AppIsProgramLoaded(APPLICATION *pApp, int* pbProgramLoaded);
typedef RTS_RESULT (CDECL * PFAPPISPROGRAMLOADED) (APPLICATION *pApp, int* pbProgramLoaded);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPISPROGRAMLOADED_NOTIMPLEMENTED)
	#define USE_AppIsProgramLoaded
	#define EXT_AppIsProgramLoaded
	#define GET_AppIsProgramLoaded(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppIsProgramLoaded(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppIsProgramLoaded  FALSE
	#define EXP_AppIsProgramLoaded  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppIsProgramLoaded
	#define EXT_AppIsProgramLoaded
	#define GET_AppIsProgramLoaded(fl)  CAL_CMGETAPI( "AppIsProgramLoaded" ) 
	#define CAL_AppIsProgramLoaded  AppIsProgramLoaded
	#define CHK_AppIsProgramLoaded  TRUE
	#define EXP_AppIsProgramLoaded  CAL_CMEXPAPI( "AppIsProgramLoaded" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppIsProgramLoaded
	#define EXT_AppIsProgramLoaded
	#define GET_AppIsProgramLoaded(fl)  CAL_CMGETAPI( "AppIsProgramLoaded" ) 
	#define CAL_AppIsProgramLoaded  AppIsProgramLoaded
	#define CHK_AppIsProgramLoaded  TRUE
	#define EXP_AppIsProgramLoaded  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppIsProgramLoaded", (RTS_UINTPTR)AppIsProgramLoaded, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppIsProgramLoaded
	#define EXT_CmpAppAppIsProgramLoaded
	#define GET_CmpAppAppIsProgramLoaded  ERR_OK
	#define CAL_CmpAppAppIsProgramLoaded pICmpApp->IAppIsProgramLoaded
	#define CHK_CmpAppAppIsProgramLoaded (pICmpApp != NULL)
	#define EXP_CmpAppAppIsProgramLoaded  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppIsProgramLoaded
	#define EXT_AppIsProgramLoaded
	#define GET_AppIsProgramLoaded(fl)  CAL_CMGETAPI( "AppIsProgramLoaded" ) 
	#define CAL_AppIsProgramLoaded pICmpApp->IAppIsProgramLoaded
	#define CHK_AppIsProgramLoaded (pICmpApp != NULL)
	#define EXP_AppIsProgramLoaded  CAL_CMEXPAPI( "AppIsProgramLoaded" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppIsProgramLoaded  PFAPPISPROGRAMLOADED pfAppIsProgramLoaded;
	#define EXT_AppIsProgramLoaded  extern PFAPPISPROGRAMLOADED pfAppIsProgramLoaded;
	#define GET_AppIsProgramLoaded(fl)  s_pfCMGetAPI2( "AppIsProgramLoaded", (RTS_VOID_FCTPTR *)&pfAppIsProgramLoaded, (fl), 0, 0)
	#define CAL_AppIsProgramLoaded  pfAppIsProgramLoaded
	#define CHK_AppIsProgramLoaded  (pfAppIsProgramLoaded != NULL)
	#define EXP_AppIsProgramLoaded  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppIsProgramLoaded", (RTS_UINTPTR)AppIsProgramLoaded, 0, 0) 
#endif




/**
 * <description>Set the load state of an application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="bProgramLoaded" type="IN">1=Application is loaded, 0=Application is not loaded</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppSetProgramLoaded(APPLICATION *pApp, int bProgramLoaded);
typedef RTS_RESULT (CDECL * PFAPPSETPROGRAMLOADED) (APPLICATION *pApp, int bProgramLoaded);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPSETPROGRAMLOADED_NOTIMPLEMENTED)
	#define USE_AppSetProgramLoaded
	#define EXT_AppSetProgramLoaded
	#define GET_AppSetProgramLoaded(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppSetProgramLoaded(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppSetProgramLoaded  FALSE
	#define EXP_AppSetProgramLoaded  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppSetProgramLoaded
	#define EXT_AppSetProgramLoaded
	#define GET_AppSetProgramLoaded(fl)  CAL_CMGETAPI( "AppSetProgramLoaded" ) 
	#define CAL_AppSetProgramLoaded  AppSetProgramLoaded
	#define CHK_AppSetProgramLoaded  TRUE
	#define EXP_AppSetProgramLoaded  CAL_CMEXPAPI( "AppSetProgramLoaded" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppSetProgramLoaded
	#define EXT_AppSetProgramLoaded
	#define GET_AppSetProgramLoaded(fl)  CAL_CMGETAPI( "AppSetProgramLoaded" ) 
	#define CAL_AppSetProgramLoaded  AppSetProgramLoaded
	#define CHK_AppSetProgramLoaded  TRUE
	#define EXP_AppSetProgramLoaded  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppSetProgramLoaded", (RTS_UINTPTR)AppSetProgramLoaded, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppSetProgramLoaded
	#define EXT_CmpAppAppSetProgramLoaded
	#define GET_CmpAppAppSetProgramLoaded  ERR_OK
	#define CAL_CmpAppAppSetProgramLoaded pICmpApp->IAppSetProgramLoaded
	#define CHK_CmpAppAppSetProgramLoaded (pICmpApp != NULL)
	#define EXP_CmpAppAppSetProgramLoaded  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppSetProgramLoaded
	#define EXT_AppSetProgramLoaded
	#define GET_AppSetProgramLoaded(fl)  CAL_CMGETAPI( "AppSetProgramLoaded" ) 
	#define CAL_AppSetProgramLoaded pICmpApp->IAppSetProgramLoaded
	#define CHK_AppSetProgramLoaded (pICmpApp != NULL)
	#define EXP_AppSetProgramLoaded  CAL_CMEXPAPI( "AppSetProgramLoaded" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppSetProgramLoaded  PFAPPSETPROGRAMLOADED pfAppSetProgramLoaded;
	#define EXT_AppSetProgramLoaded  extern PFAPPSETPROGRAMLOADED pfAppSetProgramLoaded;
	#define GET_AppSetProgramLoaded(fl)  s_pfCMGetAPI2( "AppSetProgramLoaded", (RTS_VOID_FCTPTR *)&pfAppSetProgramLoaded, (fl), 0, 0)
	#define CAL_AppSetProgramLoaded  pfAppSetProgramLoaded
	#define CHK_AppSetProgramLoaded  (pfAppSetProgramLoaded != NULL)
	#define EXP_AppSetProgramLoaded  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppSetProgramLoaded", (RTS_UINTPTR)AppSetProgramLoaded, 0, 0) 
#endif




/**
 * <description>Activate a single cycle on the specified application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppSingleCycle(APPLICATION *pApp);
typedef RTS_RESULT (CDECL * PFAPPSINGLECYCLE) (APPLICATION *pApp);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPSINGLECYCLE_NOTIMPLEMENTED)
	#define USE_AppSingleCycle
	#define EXT_AppSingleCycle
	#define GET_AppSingleCycle(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppSingleCycle(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppSingleCycle  FALSE
	#define EXP_AppSingleCycle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppSingleCycle
	#define EXT_AppSingleCycle
	#define GET_AppSingleCycle(fl)  CAL_CMGETAPI( "AppSingleCycle" ) 
	#define CAL_AppSingleCycle  AppSingleCycle
	#define CHK_AppSingleCycle  TRUE
	#define EXP_AppSingleCycle  CAL_CMEXPAPI( "AppSingleCycle" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppSingleCycle
	#define EXT_AppSingleCycle
	#define GET_AppSingleCycle(fl)  CAL_CMGETAPI( "AppSingleCycle" ) 
	#define CAL_AppSingleCycle  AppSingleCycle
	#define CHK_AppSingleCycle  TRUE
	#define EXP_AppSingleCycle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppSingleCycle", (RTS_UINTPTR)AppSingleCycle, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppSingleCycle
	#define EXT_CmpAppAppSingleCycle
	#define GET_CmpAppAppSingleCycle  ERR_OK
	#define CAL_CmpAppAppSingleCycle pICmpApp->IAppSingleCycle
	#define CHK_CmpAppAppSingleCycle (pICmpApp != NULL)
	#define EXP_CmpAppAppSingleCycle  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppSingleCycle
	#define EXT_AppSingleCycle
	#define GET_AppSingleCycle(fl)  CAL_CMGETAPI( "AppSingleCycle" ) 
	#define CAL_AppSingleCycle pICmpApp->IAppSingleCycle
	#define CHK_AppSingleCycle (pICmpApp != NULL)
	#define EXP_AppSingleCycle  CAL_CMEXPAPI( "AppSingleCycle" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppSingleCycle  PFAPPSINGLECYCLE pfAppSingleCycle;
	#define EXT_AppSingleCycle  extern PFAPPSINGLECYCLE pfAppSingleCycle;
	#define GET_AppSingleCycle(fl)  s_pfCMGetAPI2( "AppSingleCycle", (RTS_VOID_FCTPTR *)&pfAppSingleCycle, (fl), 0, 0)
	#define CAL_AppSingleCycle  pfAppSingleCycle
	#define CHK_AppSingleCycle  (pfAppSingleCycle != NULL)
	#define EXP_AppSingleCycle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppSingleCycle", (RTS_UINTPTR)AppSingleCycle, 0, 0) 
#endif




/**
 * <description>Set the state of an application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="ulState" type="IN">State to set. See above for state specifications (prefix: AS_)</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppSetState(APPLICATION *pApp, unsigned long ulState);
typedef RTS_RESULT (CDECL * PFAPPSETSTATE) (APPLICATION *pApp, unsigned long ulState);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPSETSTATE_NOTIMPLEMENTED)
	#define USE_AppSetState
	#define EXT_AppSetState
	#define GET_AppSetState(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppSetState(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppSetState  FALSE
	#define EXP_AppSetState  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppSetState
	#define EXT_AppSetState
	#define GET_AppSetState(fl)  CAL_CMGETAPI( "AppSetState" ) 
	#define CAL_AppSetState  AppSetState
	#define CHK_AppSetState  TRUE
	#define EXP_AppSetState  CAL_CMEXPAPI( "AppSetState" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppSetState
	#define EXT_AppSetState
	#define GET_AppSetState(fl)  CAL_CMGETAPI( "AppSetState" ) 
	#define CAL_AppSetState  AppSetState
	#define CHK_AppSetState  TRUE
	#define EXP_AppSetState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppSetState", (RTS_UINTPTR)AppSetState, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppSetState
	#define EXT_CmpAppAppSetState
	#define GET_CmpAppAppSetState  ERR_OK
	#define CAL_CmpAppAppSetState pICmpApp->IAppSetState
	#define CHK_CmpAppAppSetState (pICmpApp != NULL)
	#define EXP_CmpAppAppSetState  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppSetState
	#define EXT_AppSetState
	#define GET_AppSetState(fl)  CAL_CMGETAPI( "AppSetState" ) 
	#define CAL_AppSetState pICmpApp->IAppSetState
	#define CHK_AppSetState (pICmpApp != NULL)
	#define EXP_AppSetState  CAL_CMEXPAPI( "AppSetState" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppSetState  PFAPPSETSTATE pfAppSetState;
	#define EXT_AppSetState  extern PFAPPSETSTATE pfAppSetState;
	#define GET_AppSetState(fl)  s_pfCMGetAPI2( "AppSetState", (RTS_VOID_FCTPTR *)&pfAppSetState, (fl), 0, 0)
	#define CAL_AppSetState  pfAppSetState
	#define CHK_AppSetState  (pfAppSetState != NULL)
	#define EXP_AppSetState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppSetState", (RTS_UINTPTR)AppSetState, 0, 0) 
#endif




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
unsigned long CDECL AppGetState(APPLICATION *pApp, RTS_RESULT *pResult);
typedef unsigned long (CDECL * PFAPPGETSTATE) (APPLICATION *pApp, RTS_RESULT *pResult);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETSTATE_NOTIMPLEMENTED)
	#define USE_AppGetState
	#define EXT_AppGetState
	#define GET_AppGetState(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetState(p0,p1)  (unsigned long)ERR_NOTIMPLEMENTED
	#define CHK_AppGetState  FALSE
	#define EXP_AppGetState  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetState
	#define EXT_AppGetState
	#define GET_AppGetState(fl)  CAL_CMGETAPI( "AppGetState" ) 
	#define CAL_AppGetState  AppGetState
	#define CHK_AppGetState  TRUE
	#define EXP_AppGetState  CAL_CMEXPAPI( "AppGetState" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetState
	#define EXT_AppGetState
	#define GET_AppGetState(fl)  CAL_CMGETAPI( "AppGetState" ) 
	#define CAL_AppGetState  AppGetState
	#define CHK_AppGetState  TRUE
	#define EXP_AppGetState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetState", (RTS_UINTPTR)AppGetState, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetState
	#define EXT_CmpAppAppGetState
	#define GET_CmpAppAppGetState  ERR_OK
	#define CAL_CmpAppAppGetState pICmpApp->IAppGetState
	#define CHK_CmpAppAppGetState (pICmpApp != NULL)
	#define EXP_CmpAppAppGetState  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetState
	#define EXT_AppGetState
	#define GET_AppGetState(fl)  CAL_CMGETAPI( "AppGetState" ) 
	#define CAL_AppGetState pICmpApp->IAppGetState
	#define CHK_AppGetState (pICmpApp != NULL)
	#define EXP_AppGetState  CAL_CMEXPAPI( "AppGetState" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetState  PFAPPGETSTATE pfAppGetState;
	#define EXT_AppGetState  extern PFAPPGETSTATE pfAppGetState;
	#define GET_AppGetState(fl)  s_pfCMGetAPI2( "AppGetState", (RTS_VOID_FCTPTR *)&pfAppGetState, (fl), 0, 0)
	#define CAL_AppGetState  pfAppGetState
	#define CHK_AppGetState  (pfAppGetState != NULL)
	#define EXP_AppGetState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetState", (RTS_UINTPTR)AppGetState, 0, 0) 
#endif




/**
 * <description>Set the operating state of an application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="ulOpState" type="IN">Operating state of an application. This is an information, which job or
 *	operating possibilities of the application are set actually. There could be several active opertating states 
 *	at the same time!</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppSetOperatingState(APPLICATION *pApp, unsigned long ulOpState);
typedef RTS_RESULT (CDECL * PFAPPSETOPERATINGSTATE) (APPLICATION *pApp, unsigned long ulOpState);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPSETOPERATINGSTATE_NOTIMPLEMENTED)
	#define USE_AppSetOperatingState
	#define EXT_AppSetOperatingState
	#define GET_AppSetOperatingState(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppSetOperatingState(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppSetOperatingState  FALSE
	#define EXP_AppSetOperatingState  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppSetOperatingState
	#define EXT_AppSetOperatingState
	#define GET_AppSetOperatingState(fl)  CAL_CMGETAPI( "AppSetOperatingState" ) 
	#define CAL_AppSetOperatingState  AppSetOperatingState
	#define CHK_AppSetOperatingState  TRUE
	#define EXP_AppSetOperatingState  CAL_CMEXPAPI( "AppSetOperatingState" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppSetOperatingState
	#define EXT_AppSetOperatingState
	#define GET_AppSetOperatingState(fl)  CAL_CMGETAPI( "AppSetOperatingState" ) 
	#define CAL_AppSetOperatingState  AppSetOperatingState
	#define CHK_AppSetOperatingState  TRUE
	#define EXP_AppSetOperatingState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppSetOperatingState", (RTS_UINTPTR)AppSetOperatingState, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppSetOperatingState
	#define EXT_CmpAppAppSetOperatingState
	#define GET_CmpAppAppSetOperatingState  ERR_OK
	#define CAL_CmpAppAppSetOperatingState pICmpApp->IAppSetOperatingState
	#define CHK_CmpAppAppSetOperatingState (pICmpApp != NULL)
	#define EXP_CmpAppAppSetOperatingState  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppSetOperatingState
	#define EXT_AppSetOperatingState
	#define GET_AppSetOperatingState(fl)  CAL_CMGETAPI( "AppSetOperatingState" ) 
	#define CAL_AppSetOperatingState pICmpApp->IAppSetOperatingState
	#define CHK_AppSetOperatingState (pICmpApp != NULL)
	#define EXP_AppSetOperatingState  CAL_CMEXPAPI( "AppSetOperatingState" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppSetOperatingState  PFAPPSETOPERATINGSTATE pfAppSetOperatingState;
	#define EXT_AppSetOperatingState  extern PFAPPSETOPERATINGSTATE pfAppSetOperatingState;
	#define GET_AppSetOperatingState(fl)  s_pfCMGetAPI2( "AppSetOperatingState", (RTS_VOID_FCTPTR *)&pfAppSetOperatingState, (fl), 0, 0)
	#define CAL_AppSetOperatingState  pfAppSetOperatingState
	#define CHK_AppSetOperatingState  (pfAppSetOperatingState != NULL)
	#define EXP_AppSetOperatingState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppSetOperatingState", (RTS_UINTPTR)AppSetOperatingState, 0, 0) 
#endif




/**
 * <description>Reset a single operating state of an application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="ulOpState" type="IN">Operating state to reset</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppResetOperatingState(APPLICATION *pApp, unsigned long ulOpState);
typedef RTS_RESULT (CDECL * PFAPPRESETOPERATINGSTATE) (APPLICATION *pApp, unsigned long ulOpState);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPRESETOPERATINGSTATE_NOTIMPLEMENTED)
	#define USE_AppResetOperatingState
	#define EXT_AppResetOperatingState
	#define GET_AppResetOperatingState(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppResetOperatingState(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppResetOperatingState  FALSE
	#define EXP_AppResetOperatingState  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppResetOperatingState
	#define EXT_AppResetOperatingState
	#define GET_AppResetOperatingState(fl)  CAL_CMGETAPI( "AppResetOperatingState" ) 
	#define CAL_AppResetOperatingState  AppResetOperatingState
	#define CHK_AppResetOperatingState  TRUE
	#define EXP_AppResetOperatingState  CAL_CMEXPAPI( "AppResetOperatingState" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppResetOperatingState
	#define EXT_AppResetOperatingState
	#define GET_AppResetOperatingState(fl)  CAL_CMGETAPI( "AppResetOperatingState" ) 
	#define CAL_AppResetOperatingState  AppResetOperatingState
	#define CHK_AppResetOperatingState  TRUE
	#define EXP_AppResetOperatingState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppResetOperatingState", (RTS_UINTPTR)AppResetOperatingState, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppResetOperatingState
	#define EXT_CmpAppAppResetOperatingState
	#define GET_CmpAppAppResetOperatingState  ERR_OK
	#define CAL_CmpAppAppResetOperatingState pICmpApp->IAppResetOperatingState
	#define CHK_CmpAppAppResetOperatingState (pICmpApp != NULL)
	#define EXP_CmpAppAppResetOperatingState  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppResetOperatingState
	#define EXT_AppResetOperatingState
	#define GET_AppResetOperatingState(fl)  CAL_CMGETAPI( "AppResetOperatingState" ) 
	#define CAL_AppResetOperatingState pICmpApp->IAppResetOperatingState
	#define CHK_AppResetOperatingState (pICmpApp != NULL)
	#define EXP_AppResetOperatingState  CAL_CMEXPAPI( "AppResetOperatingState" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppResetOperatingState  PFAPPRESETOPERATINGSTATE pfAppResetOperatingState;
	#define EXT_AppResetOperatingState  extern PFAPPRESETOPERATINGSTATE pfAppResetOperatingState;
	#define GET_AppResetOperatingState(fl)  s_pfCMGetAPI2( "AppResetOperatingState", (RTS_VOID_FCTPTR *)&pfAppResetOperatingState, (fl), 0, 0)
	#define CAL_AppResetOperatingState  pfAppResetOperatingState
	#define CHK_AppResetOperatingState  (pfAppResetOperatingState != NULL)
	#define EXP_AppResetOperatingState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppResetOperatingState", (RTS_UINTPTR)AppResetOperatingState, 0, 0) 
#endif




/**
 * <description>Get the operating state of an application</description>
 * <param name="pApp" type="IN" range="[VALID_PAPP,NULL]">Pointer to the specified application description</param>
 * <parampseudo name="pApp->ulOpState" type="IN" range="[OS_NONE,OS_PROGRAM_LOADED]">Application operating state</parampseudo>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Status retrieved successfully</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">pApp may not be null</errorcode>
 * <result>Operating state of an application</result>
 */
unsigned long CDECL AppGetOperatingState(APPLICATION *pApp, RTS_RESULT *pResult);
typedef unsigned long (CDECL * PFAPPGETOPERATINGSTATE) (APPLICATION *pApp, RTS_RESULT *pResult);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETOPERATINGSTATE_NOTIMPLEMENTED)
	#define USE_AppGetOperatingState
	#define EXT_AppGetOperatingState
	#define GET_AppGetOperatingState(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetOperatingState(p0,p1)  (unsigned long)ERR_NOTIMPLEMENTED
	#define CHK_AppGetOperatingState  FALSE
	#define EXP_AppGetOperatingState  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetOperatingState
	#define EXT_AppGetOperatingState
	#define GET_AppGetOperatingState(fl)  CAL_CMGETAPI( "AppGetOperatingState" ) 
	#define CAL_AppGetOperatingState  AppGetOperatingState
	#define CHK_AppGetOperatingState  TRUE
	#define EXP_AppGetOperatingState  CAL_CMEXPAPI( "AppGetOperatingState" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetOperatingState
	#define EXT_AppGetOperatingState
	#define GET_AppGetOperatingState(fl)  CAL_CMGETAPI( "AppGetOperatingState" ) 
	#define CAL_AppGetOperatingState  AppGetOperatingState
	#define CHK_AppGetOperatingState  TRUE
	#define EXP_AppGetOperatingState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetOperatingState", (RTS_UINTPTR)AppGetOperatingState, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetOperatingState
	#define EXT_CmpAppAppGetOperatingState
	#define GET_CmpAppAppGetOperatingState  ERR_OK
	#define CAL_CmpAppAppGetOperatingState pICmpApp->IAppGetOperatingState
	#define CHK_CmpAppAppGetOperatingState (pICmpApp != NULL)
	#define EXP_CmpAppAppGetOperatingState  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetOperatingState
	#define EXT_AppGetOperatingState
	#define GET_AppGetOperatingState(fl)  CAL_CMGETAPI( "AppGetOperatingState" ) 
	#define CAL_AppGetOperatingState pICmpApp->IAppGetOperatingState
	#define CHK_AppGetOperatingState (pICmpApp != NULL)
	#define EXP_AppGetOperatingState  CAL_CMEXPAPI( "AppGetOperatingState" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetOperatingState  PFAPPGETOPERATINGSTATE pfAppGetOperatingState;
	#define EXT_AppGetOperatingState  extern PFAPPGETOPERATINGSTATE pfAppGetOperatingState;
	#define GET_AppGetOperatingState(fl)  s_pfCMGetAPI2( "AppGetOperatingState", (RTS_VOID_FCTPTR *)&pfAppGetOperatingState, (fl), 0, 0)
	#define CAL_AppGetOperatingState  pfAppGetOperatingState
	#define CHK_AppGetOperatingState  (pfAppGetOperatingState != NULL)
	#define EXP_AppGetOperatingState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetOperatingState", (RTS_UINTPTR)AppGetOperatingState, 0, 0) 
#endif




/**
 * <description>Sets the code id of the application. The code id is a unique number that
 *	specifies the code content of an application.</description>
 * <param name="pApp" type="IN" range="[NULL,VALID_PAPP]">Pointer to the specified application description</param>
 * <param name="pCodeGuid" type="IN" range="[NULL,VALID_PCODEGUID]">Pointer to code guid</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Code Guid was set successful</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Parameter may not be null</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppSetCodeGuid(APPLICATION *pApp, RTS_GUID *pCodeGuid);
typedef RTS_RESULT (CDECL * PFAPPSETCODEGUID) (APPLICATION *pApp, RTS_GUID *pCodeGuid);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPSETCODEGUID_NOTIMPLEMENTED)
	#define USE_AppSetCodeGuid
	#define EXT_AppSetCodeGuid
	#define GET_AppSetCodeGuid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppSetCodeGuid(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppSetCodeGuid  FALSE
	#define EXP_AppSetCodeGuid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppSetCodeGuid
	#define EXT_AppSetCodeGuid
	#define GET_AppSetCodeGuid(fl)  CAL_CMGETAPI( "AppSetCodeGuid" ) 
	#define CAL_AppSetCodeGuid  AppSetCodeGuid
	#define CHK_AppSetCodeGuid  TRUE
	#define EXP_AppSetCodeGuid  CAL_CMEXPAPI( "AppSetCodeGuid" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppSetCodeGuid
	#define EXT_AppSetCodeGuid
	#define GET_AppSetCodeGuid(fl)  CAL_CMGETAPI( "AppSetCodeGuid" ) 
	#define CAL_AppSetCodeGuid  AppSetCodeGuid
	#define CHK_AppSetCodeGuid  TRUE
	#define EXP_AppSetCodeGuid  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppSetCodeGuid", (RTS_UINTPTR)AppSetCodeGuid, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppSetCodeGuid
	#define EXT_CmpAppAppSetCodeGuid
	#define GET_CmpAppAppSetCodeGuid  ERR_OK
	#define CAL_CmpAppAppSetCodeGuid pICmpApp->IAppSetCodeGuid
	#define CHK_CmpAppAppSetCodeGuid (pICmpApp != NULL)
	#define EXP_CmpAppAppSetCodeGuid  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppSetCodeGuid
	#define EXT_AppSetCodeGuid
	#define GET_AppSetCodeGuid(fl)  CAL_CMGETAPI( "AppSetCodeGuid" ) 
	#define CAL_AppSetCodeGuid pICmpApp->IAppSetCodeGuid
	#define CHK_AppSetCodeGuid (pICmpApp != NULL)
	#define EXP_AppSetCodeGuid  CAL_CMEXPAPI( "AppSetCodeGuid" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppSetCodeGuid  PFAPPSETCODEGUID pfAppSetCodeGuid;
	#define EXT_AppSetCodeGuid  extern PFAPPSETCODEGUID pfAppSetCodeGuid;
	#define GET_AppSetCodeGuid(fl)  s_pfCMGetAPI2( "AppSetCodeGuid", (RTS_VOID_FCTPTR *)&pfAppSetCodeGuid, (fl), 0, 0)
	#define CAL_AppSetCodeGuid  pfAppSetCodeGuid
	#define CHK_AppSetCodeGuid  (pfAppSetCodeGuid != NULL)
	#define EXP_AppSetCodeGuid  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppSetCodeGuid", (RTS_UINTPTR)AppSetCodeGuid, 0, 0) 
#endif




/**
 * <description>Retrieves the code id of the application. The code id is a unique number that
 *	specifies the code content of an application.</description>
 * <param name="pApp" type="IN" range="[NULL,VALID_PAPP]">Pointer to the specified application description</param>
 * <param name="pCodeGuid" type="OUT" range="[NULL,VALID_PCODEGUID]">Pointer to code guid</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Code Guid was set successfully</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Parameter may not be null</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppGetCodeGuid(APPLICATION *pApp, RTS_GUID *pCodeGuid);
typedef RTS_RESULT (CDECL * PFAPPGETCODEGUID) (APPLICATION *pApp, RTS_GUID *pCodeGuid);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETCODEGUID_NOTIMPLEMENTED)
	#define USE_AppGetCodeGuid
	#define EXT_AppGetCodeGuid
	#define GET_AppGetCodeGuid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetCodeGuid(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppGetCodeGuid  FALSE
	#define EXP_AppGetCodeGuid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetCodeGuid
	#define EXT_AppGetCodeGuid
	#define GET_AppGetCodeGuid(fl)  CAL_CMGETAPI( "AppGetCodeGuid" ) 
	#define CAL_AppGetCodeGuid  AppGetCodeGuid
	#define CHK_AppGetCodeGuid  TRUE
	#define EXP_AppGetCodeGuid  CAL_CMEXPAPI( "AppGetCodeGuid" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetCodeGuid
	#define EXT_AppGetCodeGuid
	#define GET_AppGetCodeGuid(fl)  CAL_CMGETAPI( "AppGetCodeGuid" ) 
	#define CAL_AppGetCodeGuid  AppGetCodeGuid
	#define CHK_AppGetCodeGuid  TRUE
	#define EXP_AppGetCodeGuid  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetCodeGuid", (RTS_UINTPTR)AppGetCodeGuid, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetCodeGuid
	#define EXT_CmpAppAppGetCodeGuid
	#define GET_CmpAppAppGetCodeGuid  ERR_OK
	#define CAL_CmpAppAppGetCodeGuid pICmpApp->IAppGetCodeGuid
	#define CHK_CmpAppAppGetCodeGuid (pICmpApp != NULL)
	#define EXP_CmpAppAppGetCodeGuid  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetCodeGuid
	#define EXT_AppGetCodeGuid
	#define GET_AppGetCodeGuid(fl)  CAL_CMGETAPI( "AppGetCodeGuid" ) 
	#define CAL_AppGetCodeGuid pICmpApp->IAppGetCodeGuid
	#define CHK_AppGetCodeGuid (pICmpApp != NULL)
	#define EXP_AppGetCodeGuid  CAL_CMEXPAPI( "AppGetCodeGuid" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetCodeGuid  PFAPPGETCODEGUID pfAppGetCodeGuid;
	#define EXT_AppGetCodeGuid  extern PFAPPGETCODEGUID pfAppGetCodeGuid;
	#define GET_AppGetCodeGuid(fl)  s_pfCMGetAPI2( "AppGetCodeGuid", (RTS_VOID_FCTPTR *)&pfAppGetCodeGuid, (fl), 0, 0)
	#define CAL_AppGetCodeGuid  pfAppGetCodeGuid
	#define CHK_AppGetCodeGuid  (pfAppGetCodeGuid != NULL)
	#define EXP_AppGetCodeGuid  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetCodeGuid", (RTS_UINTPTR)AppGetCodeGuid, 0, 0) 
#endif




/**
 * <description>Sets the data id of the application. The data id is a unique number that
 *	specifies the data configuration of an application.</description>
 * <param name="pApp" type="IN" range="[NULL,VALID_PAPP]">Pointer to the specified application description</param>
 * <param name="pDataGuid" type="IN" range="[NULL,VALID_PDATAGUID]">Pointer to data guid</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Data Guid was set successful</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Parameter may not be null</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppSetDataGuid(APPLICATION *pApp, RTS_GUID *pDataGuid);
typedef RTS_RESULT (CDECL * PFAPPSETDATAGUID) (APPLICATION *pApp, RTS_GUID *pDataGuid);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPSETDATAGUID_NOTIMPLEMENTED)
	#define USE_AppSetDataGuid
	#define EXT_AppSetDataGuid
	#define GET_AppSetDataGuid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppSetDataGuid(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppSetDataGuid  FALSE
	#define EXP_AppSetDataGuid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppSetDataGuid
	#define EXT_AppSetDataGuid
	#define GET_AppSetDataGuid(fl)  CAL_CMGETAPI( "AppSetDataGuid" ) 
	#define CAL_AppSetDataGuid  AppSetDataGuid
	#define CHK_AppSetDataGuid  TRUE
	#define EXP_AppSetDataGuid  CAL_CMEXPAPI( "AppSetDataGuid" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppSetDataGuid
	#define EXT_AppSetDataGuid
	#define GET_AppSetDataGuid(fl)  CAL_CMGETAPI( "AppSetDataGuid" ) 
	#define CAL_AppSetDataGuid  AppSetDataGuid
	#define CHK_AppSetDataGuid  TRUE
	#define EXP_AppSetDataGuid  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppSetDataGuid", (RTS_UINTPTR)AppSetDataGuid, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppSetDataGuid
	#define EXT_CmpAppAppSetDataGuid
	#define GET_CmpAppAppSetDataGuid  ERR_OK
	#define CAL_CmpAppAppSetDataGuid pICmpApp->IAppSetDataGuid
	#define CHK_CmpAppAppSetDataGuid (pICmpApp != NULL)
	#define EXP_CmpAppAppSetDataGuid  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppSetDataGuid
	#define EXT_AppSetDataGuid
	#define GET_AppSetDataGuid(fl)  CAL_CMGETAPI( "AppSetDataGuid" ) 
	#define CAL_AppSetDataGuid pICmpApp->IAppSetDataGuid
	#define CHK_AppSetDataGuid (pICmpApp != NULL)
	#define EXP_AppSetDataGuid  CAL_CMEXPAPI( "AppSetDataGuid" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppSetDataGuid  PFAPPSETDATAGUID pfAppSetDataGuid;
	#define EXT_AppSetDataGuid  extern PFAPPSETDATAGUID pfAppSetDataGuid;
	#define GET_AppSetDataGuid(fl)  s_pfCMGetAPI2( "AppSetDataGuid", (RTS_VOID_FCTPTR *)&pfAppSetDataGuid, (fl), 0, 0)
	#define CAL_AppSetDataGuid  pfAppSetDataGuid
	#define CHK_AppSetDataGuid  (pfAppSetDataGuid != NULL)
	#define EXP_AppSetDataGuid  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppSetDataGuid", (RTS_UINTPTR)AppSetDataGuid, 0, 0) 
#endif




/**
 * <description>Retrieves the data id of the application. The data id is a unique number that
 *	specifies the data configuration of an application.</description>
 * <param name="pApp" type="IN" range="[NULL,VALID_PAPP]">Pointer to the specified application description</param>
 * <param name="pDataGuid" type="OUT" range="[NULL,VALID_PDATAGUID]">Pointer to data guid</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Get data Guid was successfully</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Parameter may not be null</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppGetDataGuid(APPLICATION *pApp, RTS_GUID *pDataGuid);
typedef RTS_RESULT (CDECL * PFAPPGETDATAGUID) (APPLICATION *pApp, RTS_GUID *pDataGuid);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETDATAGUID_NOTIMPLEMENTED)
	#define USE_AppGetDataGuid
	#define EXT_AppGetDataGuid
	#define GET_AppGetDataGuid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetDataGuid(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppGetDataGuid  FALSE
	#define EXP_AppGetDataGuid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetDataGuid
	#define EXT_AppGetDataGuid
	#define GET_AppGetDataGuid(fl)  CAL_CMGETAPI( "AppGetDataGuid" ) 
	#define CAL_AppGetDataGuid  AppGetDataGuid
	#define CHK_AppGetDataGuid  TRUE
	#define EXP_AppGetDataGuid  CAL_CMEXPAPI( "AppGetDataGuid" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetDataGuid
	#define EXT_AppGetDataGuid
	#define GET_AppGetDataGuid(fl)  CAL_CMGETAPI( "AppGetDataGuid" ) 
	#define CAL_AppGetDataGuid  AppGetDataGuid
	#define CHK_AppGetDataGuid  TRUE
	#define EXP_AppGetDataGuid  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetDataGuid", (RTS_UINTPTR)AppGetDataGuid, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetDataGuid
	#define EXT_CmpAppAppGetDataGuid
	#define GET_CmpAppAppGetDataGuid  ERR_OK
	#define CAL_CmpAppAppGetDataGuid pICmpApp->IAppGetDataGuid
	#define CHK_CmpAppAppGetDataGuid (pICmpApp != NULL)
	#define EXP_CmpAppAppGetDataGuid  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetDataGuid
	#define EXT_AppGetDataGuid
	#define GET_AppGetDataGuid(fl)  CAL_CMGETAPI( "AppGetDataGuid" ) 
	#define CAL_AppGetDataGuid pICmpApp->IAppGetDataGuid
	#define CHK_AppGetDataGuid (pICmpApp != NULL)
	#define EXP_AppGetDataGuid  CAL_CMEXPAPI( "AppGetDataGuid" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetDataGuid  PFAPPGETDATAGUID pfAppGetDataGuid;
	#define EXT_AppGetDataGuid  extern PFAPPGETDATAGUID pfAppGetDataGuid;
	#define GET_AppGetDataGuid(fl)  s_pfCMGetAPI2( "AppGetDataGuid", (RTS_VOID_FCTPTR *)&pfAppGetDataGuid, (fl), 0, 0)
	#define CAL_AppGetDataGuid  pfAppGetDataGuid
	#define CHK_AppGetDataGuid  (pfAppGetDataGuid != NULL)
	#define EXP_AppGetDataGuid  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetDataGuid", (RTS_UINTPTR)AppGetDataGuid, 0, 0) 
#endif




/**
 * <description>Retrieves the code and data guid of the bootproject of the given application.
 *	This function can be used to compare the guids of the loaded application with the bootproject.</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="pCodeGuid" type="OUT">Pointer to code guid</param>
 * <param name="pDataGuid" type="OUT">Pointer to data guid</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppGetBootprojectGuids(APPLICATION *pApp, RTS_GUID *pCodeGuid, RTS_GUID *pDataGuid);
typedef RTS_RESULT (CDECL * PFAPPGETBOOTPROJECTGUIDS) (APPLICATION *pApp, RTS_GUID *pCodeGuid, RTS_GUID *pDataGuid);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETBOOTPROJECTGUIDS_NOTIMPLEMENTED)
	#define USE_AppGetBootprojectGuids
	#define EXT_AppGetBootprojectGuids
	#define GET_AppGetBootprojectGuids(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetBootprojectGuids(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppGetBootprojectGuids  FALSE
	#define EXP_AppGetBootprojectGuids  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetBootprojectGuids
	#define EXT_AppGetBootprojectGuids
	#define GET_AppGetBootprojectGuids(fl)  CAL_CMGETAPI( "AppGetBootprojectGuids" ) 
	#define CAL_AppGetBootprojectGuids  AppGetBootprojectGuids
	#define CHK_AppGetBootprojectGuids  TRUE
	#define EXP_AppGetBootprojectGuids  CAL_CMEXPAPI( "AppGetBootprojectGuids" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetBootprojectGuids
	#define EXT_AppGetBootprojectGuids
	#define GET_AppGetBootprojectGuids(fl)  CAL_CMGETAPI( "AppGetBootprojectGuids" ) 
	#define CAL_AppGetBootprojectGuids  AppGetBootprojectGuids
	#define CHK_AppGetBootprojectGuids  TRUE
	#define EXP_AppGetBootprojectGuids  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetBootprojectGuids", (RTS_UINTPTR)AppGetBootprojectGuids, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetBootprojectGuids
	#define EXT_CmpAppAppGetBootprojectGuids
	#define GET_CmpAppAppGetBootprojectGuids  ERR_OK
	#define CAL_CmpAppAppGetBootprojectGuids pICmpApp->IAppGetBootprojectGuids
	#define CHK_CmpAppAppGetBootprojectGuids (pICmpApp != NULL)
	#define EXP_CmpAppAppGetBootprojectGuids  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetBootprojectGuids
	#define EXT_AppGetBootprojectGuids
	#define GET_AppGetBootprojectGuids(fl)  CAL_CMGETAPI( "AppGetBootprojectGuids" ) 
	#define CAL_AppGetBootprojectGuids pICmpApp->IAppGetBootprojectGuids
	#define CHK_AppGetBootprojectGuids (pICmpApp != NULL)
	#define EXP_AppGetBootprojectGuids  CAL_CMEXPAPI( "AppGetBootprojectGuids" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetBootprojectGuids  PFAPPGETBOOTPROJECTGUIDS pfAppGetBootprojectGuids;
	#define EXT_AppGetBootprojectGuids  extern PFAPPGETBOOTPROJECTGUIDS pfAppGetBootprojectGuids;
	#define GET_AppGetBootprojectGuids(fl)  s_pfCMGetAPI2( "AppGetBootprojectGuids", (RTS_VOID_FCTPTR *)&pfAppGetBootprojectGuids, (fl), 0, 0)
	#define CAL_AppGetBootprojectGuids  pfAppGetBootprojectGuids
	#define CHK_AppGetBootprojectGuids  (pfAppGetBootprojectGuids != NULL)
	#define EXP_AppGetBootprojectGuids  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetBootprojectGuids", (RTS_UINTPTR)AppGetBootprojectGuids, 0, 0) 
#endif




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
RTS_RESULT CDECL AppExceptionHandler(APPLICATION *pApp, RTS_UI32 ulException, RegContext Context);
typedef RTS_RESULT (CDECL * PFAPPEXCEPTIONHANDLER) (APPLICATION *pApp, RTS_UI32 ulException, RegContext Context);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPEXCEPTIONHANDLER_NOTIMPLEMENTED)
	#define USE_AppExceptionHandler
	#define EXT_AppExceptionHandler
	#define GET_AppExceptionHandler(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppExceptionHandler(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppExceptionHandler  FALSE
	#define EXP_AppExceptionHandler  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppExceptionHandler
	#define EXT_AppExceptionHandler
	#define GET_AppExceptionHandler(fl)  CAL_CMGETAPI( "AppExceptionHandler" ) 
	#define CAL_AppExceptionHandler  AppExceptionHandler
	#define CHK_AppExceptionHandler  TRUE
	#define EXP_AppExceptionHandler  CAL_CMEXPAPI( "AppExceptionHandler" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppExceptionHandler
	#define EXT_AppExceptionHandler
	#define GET_AppExceptionHandler(fl)  CAL_CMGETAPI( "AppExceptionHandler" ) 
	#define CAL_AppExceptionHandler  AppExceptionHandler
	#define CHK_AppExceptionHandler  TRUE
	#define EXP_AppExceptionHandler  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppExceptionHandler", (RTS_UINTPTR)AppExceptionHandler, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppExceptionHandler
	#define EXT_CmpAppAppExceptionHandler
	#define GET_CmpAppAppExceptionHandler  ERR_OK
	#define CAL_CmpAppAppExceptionHandler pICmpApp->IAppExceptionHandler
	#define CHK_CmpAppAppExceptionHandler (pICmpApp != NULL)
	#define EXP_CmpAppAppExceptionHandler  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppExceptionHandler
	#define EXT_AppExceptionHandler
	#define GET_AppExceptionHandler(fl)  CAL_CMGETAPI( "AppExceptionHandler" ) 
	#define CAL_AppExceptionHandler pICmpApp->IAppExceptionHandler
	#define CHK_AppExceptionHandler (pICmpApp != NULL)
	#define EXP_AppExceptionHandler  CAL_CMEXPAPI( "AppExceptionHandler" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppExceptionHandler  PFAPPEXCEPTIONHANDLER pfAppExceptionHandler;
	#define EXT_AppExceptionHandler  extern PFAPPEXCEPTIONHANDLER pfAppExceptionHandler;
	#define GET_AppExceptionHandler(fl)  s_pfCMGetAPI2( "AppExceptionHandler", (RTS_VOID_FCTPTR *)&pfAppExceptionHandler, (fl), 0, 0)
	#define CAL_AppExceptionHandler  pfAppExceptionHandler
	#define CHK_AppExceptionHandler  (pfAppExceptionHandler != NULL)
	#define EXP_AppExceptionHandler  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppExceptionHandler", (RTS_UINTPTR)AppExceptionHandler, 0, 0) 
#endif




/**
 * <description>Executes a reset on the specified application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="usResetOption" type="IN">Reset option. See the category "Reset options" for detailed information</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppReset(APPLICATION* pApp, RTS_UI16 usResetOption, RTS_UI32 ulSessionId);
typedef RTS_RESULT (CDECL * PFAPPRESET) (APPLICATION* pApp, RTS_UI16 usResetOption, RTS_UI32 ulSessionId);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPRESET_NOTIMPLEMENTED)
	#define USE_AppReset
	#define EXT_AppReset
	#define GET_AppReset(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppReset(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppReset  FALSE
	#define EXP_AppReset  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppReset
	#define EXT_AppReset
	#define GET_AppReset(fl)  CAL_CMGETAPI( "AppReset" ) 
	#define CAL_AppReset  AppReset
	#define CHK_AppReset  TRUE
	#define EXP_AppReset  CAL_CMEXPAPI( "AppReset" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppReset
	#define EXT_AppReset
	#define GET_AppReset(fl)  CAL_CMGETAPI( "AppReset" ) 
	#define CAL_AppReset  AppReset
	#define CHK_AppReset  TRUE
	#define EXP_AppReset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppReset", (RTS_UINTPTR)AppReset, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppReset
	#define EXT_CmpAppAppReset
	#define GET_CmpAppAppReset  ERR_OK
	#define CAL_CmpAppAppReset pICmpApp->IAppReset
	#define CHK_CmpAppAppReset (pICmpApp != NULL)
	#define EXP_CmpAppAppReset  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppReset
	#define EXT_AppReset
	#define GET_AppReset(fl)  CAL_CMGETAPI( "AppReset" ) 
	#define CAL_AppReset pICmpApp->IAppReset
	#define CHK_AppReset (pICmpApp != NULL)
	#define EXP_AppReset  CAL_CMEXPAPI( "AppReset" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppReset  PFAPPRESET pfAppReset;
	#define EXT_AppReset  extern PFAPPRESET pfAppReset;
	#define GET_AppReset(fl)  s_pfCMGetAPI2( "AppReset", (RTS_VOID_FCTPTR *)&pfAppReset, (fl), 0, 0)
	#define CAL_AppReset  pfAppReset
	#define CHK_AppReset  (pfAppReset != NULL)
	#define EXP_AppReset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppReset", (RTS_UINTPTR)AppReset, 0, 0) 
#endif




/**
 * <description>Resets all applications</description>
 * <param name="usResetOption" type="IN">Reset option. See the category "Reset options" for detailed information</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppResetAllApplications(RTS_UI16 usResetOption);
typedef RTS_RESULT (CDECL * PFAPPRESETALLAPPLICATIONS) (RTS_UI16 usResetOption);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPRESETALLAPPLICATIONS_NOTIMPLEMENTED)
	#define USE_AppResetAllApplications
	#define EXT_AppResetAllApplications
	#define GET_AppResetAllApplications(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppResetAllApplications(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppResetAllApplications  FALSE
	#define EXP_AppResetAllApplications  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppResetAllApplications
	#define EXT_AppResetAllApplications
	#define GET_AppResetAllApplications(fl)  CAL_CMGETAPI( "AppResetAllApplications" ) 
	#define CAL_AppResetAllApplications  AppResetAllApplications
	#define CHK_AppResetAllApplications  TRUE
	#define EXP_AppResetAllApplications  CAL_CMEXPAPI( "AppResetAllApplications" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppResetAllApplications
	#define EXT_AppResetAllApplications
	#define GET_AppResetAllApplications(fl)  CAL_CMGETAPI( "AppResetAllApplications" ) 
	#define CAL_AppResetAllApplications  AppResetAllApplications
	#define CHK_AppResetAllApplications  TRUE
	#define EXP_AppResetAllApplications  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppResetAllApplications", (RTS_UINTPTR)AppResetAllApplications, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppResetAllApplications
	#define EXT_CmpAppAppResetAllApplications
	#define GET_CmpAppAppResetAllApplications  ERR_OK
	#define CAL_CmpAppAppResetAllApplications pICmpApp->IAppResetAllApplications
	#define CHK_CmpAppAppResetAllApplications (pICmpApp != NULL)
	#define EXP_CmpAppAppResetAllApplications  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppResetAllApplications
	#define EXT_AppResetAllApplications
	#define GET_AppResetAllApplications(fl)  CAL_CMGETAPI( "AppResetAllApplications" ) 
	#define CAL_AppResetAllApplications pICmpApp->IAppResetAllApplications
	#define CHK_AppResetAllApplications (pICmpApp != NULL)
	#define EXP_AppResetAllApplications  CAL_CMEXPAPI( "AppResetAllApplications" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppResetAllApplications  PFAPPRESETALLAPPLICATIONS pfAppResetAllApplications;
	#define EXT_AppResetAllApplications  extern PFAPPRESETALLAPPLICATIONS pfAppResetAllApplications;
	#define GET_AppResetAllApplications(fl)  s_pfCMGetAPI2( "AppResetAllApplications", (RTS_VOID_FCTPTR *)&pfAppResetAllApplications, (fl), 0, 0)
	#define CAL_AppResetAllApplications  pfAppResetAllApplications
	#define CHK_AppResetAllApplications  (pfAppResetAllApplications != NULL)
	#define EXP_AppResetAllApplications  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppResetAllApplications", (RTS_UINTPTR)AppResetAllApplications, 0, 0) 
#endif




/**
 * <description>Load all registered bootprojects</description>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppLoadBootprojects(void);
typedef RTS_RESULT (CDECL * PFAPPLOADBOOTPROJECTS) (void);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPLOADBOOTPROJECTS_NOTIMPLEMENTED)
	#define USE_AppLoadBootprojects
	#define EXT_AppLoadBootprojects
	#define GET_AppLoadBootprojects(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppLoadBootprojects()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppLoadBootprojects  FALSE
	#define EXP_AppLoadBootprojects  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppLoadBootprojects
	#define EXT_AppLoadBootprojects
	#define GET_AppLoadBootprojects(fl)  CAL_CMGETAPI( "AppLoadBootprojects" ) 
	#define CAL_AppLoadBootprojects  AppLoadBootprojects
	#define CHK_AppLoadBootprojects  TRUE
	#define EXP_AppLoadBootprojects  CAL_CMEXPAPI( "AppLoadBootprojects" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppLoadBootprojects
	#define EXT_AppLoadBootprojects
	#define GET_AppLoadBootprojects(fl)  CAL_CMGETAPI( "AppLoadBootprojects" ) 
	#define CAL_AppLoadBootprojects  AppLoadBootprojects
	#define CHK_AppLoadBootprojects  TRUE
	#define EXP_AppLoadBootprojects  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppLoadBootprojects", (RTS_UINTPTR)AppLoadBootprojects, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppLoadBootprojects
	#define EXT_CmpAppAppLoadBootprojects
	#define GET_CmpAppAppLoadBootprojects  ERR_OK
	#define CAL_CmpAppAppLoadBootprojects pICmpApp->IAppLoadBootprojects
	#define CHK_CmpAppAppLoadBootprojects (pICmpApp != NULL)
	#define EXP_CmpAppAppLoadBootprojects  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppLoadBootprojects
	#define EXT_AppLoadBootprojects
	#define GET_AppLoadBootprojects(fl)  CAL_CMGETAPI( "AppLoadBootprojects" ) 
	#define CAL_AppLoadBootprojects pICmpApp->IAppLoadBootprojects
	#define CHK_AppLoadBootprojects (pICmpApp != NULL)
	#define EXP_AppLoadBootprojects  CAL_CMEXPAPI( "AppLoadBootprojects" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppLoadBootprojects  PFAPPLOADBOOTPROJECTS pfAppLoadBootprojects;
	#define EXT_AppLoadBootprojects  extern PFAPPLOADBOOTPROJECTS pfAppLoadBootprojects;
	#define GET_AppLoadBootprojects(fl)  s_pfCMGetAPI2( "AppLoadBootprojects", (RTS_VOID_FCTPTR *)&pfAppLoadBootprojects, (fl), 0, 0)
	#define CAL_AppLoadBootprojects  pfAppLoadBootprojects
	#define CHK_AppLoadBootprojects  (pfAppLoadBootprojects != NULL)
	#define EXP_AppLoadBootprojects  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppLoadBootprojects", (RTS_UINTPTR)AppLoadBootprojects, 0, 0) 
#endif




/**
 * <description>Start all registered bootprojects</description>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppStartBootprojects(void);
typedef RTS_RESULT (CDECL * PFAPPSTARTBOOTPROJECTS) (void);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPSTARTBOOTPROJECTS_NOTIMPLEMENTED)
	#define USE_AppStartBootprojects
	#define EXT_AppStartBootprojects
	#define GET_AppStartBootprojects(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppStartBootprojects()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppStartBootprojects  FALSE
	#define EXP_AppStartBootprojects  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppStartBootprojects
	#define EXT_AppStartBootprojects
	#define GET_AppStartBootprojects(fl)  CAL_CMGETAPI( "AppStartBootprojects" ) 
	#define CAL_AppStartBootprojects  AppStartBootprojects
	#define CHK_AppStartBootprojects  TRUE
	#define EXP_AppStartBootprojects  CAL_CMEXPAPI( "AppStartBootprojects" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppStartBootprojects
	#define EXT_AppStartBootprojects
	#define GET_AppStartBootprojects(fl)  CAL_CMGETAPI( "AppStartBootprojects" ) 
	#define CAL_AppStartBootprojects  AppStartBootprojects
	#define CHK_AppStartBootprojects  TRUE
	#define EXP_AppStartBootprojects  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppStartBootprojects", (RTS_UINTPTR)AppStartBootprojects, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppStartBootprojects
	#define EXT_CmpAppAppStartBootprojects
	#define GET_CmpAppAppStartBootprojects  ERR_OK
	#define CAL_CmpAppAppStartBootprojects pICmpApp->IAppStartBootprojects
	#define CHK_CmpAppAppStartBootprojects (pICmpApp != NULL)
	#define EXP_CmpAppAppStartBootprojects  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppStartBootprojects
	#define EXT_AppStartBootprojects
	#define GET_AppStartBootprojects(fl)  CAL_CMGETAPI( "AppStartBootprojects" ) 
	#define CAL_AppStartBootprojects pICmpApp->IAppStartBootprojects
	#define CHK_AppStartBootprojects (pICmpApp != NULL)
	#define EXP_AppStartBootprojects  CAL_CMEXPAPI( "AppStartBootprojects" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppStartBootprojects  PFAPPSTARTBOOTPROJECTS pfAppStartBootprojects;
	#define EXT_AppStartBootprojects  extern PFAPPSTARTBOOTPROJECTS pfAppStartBootprojects;
	#define GET_AppStartBootprojects(fl)  s_pfCMGetAPI2( "AppStartBootprojects", (RTS_VOID_FCTPTR *)&pfAppStartBootprojects, (fl), 0, 0)
	#define CAL_AppStartBootprojects  pfAppStartBootprojects
	#define CHK_AppStartBootprojects  (pfAppStartBootprojects != NULL)
	#define EXP_AppStartBootprojects  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppStartBootprojects", (RTS_UINTPTR)AppStartBootprojects, 0, 0) 
#endif




/**
 * <description>Load a bootproject with the specified application name</description>
 * <param name="pszAppName" type="IN">Pointer to the NUL terminated application name</param>
 * <param name="pszFilePath" type="IN">File path for the bootproject</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppLoadBootproject(char *pszAppName, char *pszFilePath);
typedef RTS_RESULT (CDECL * PFAPPLOADBOOTPROJECT) (char *pszAppName, char *pszFilePath);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPLOADBOOTPROJECT_NOTIMPLEMENTED)
	#define USE_AppLoadBootproject
	#define EXT_AppLoadBootproject
	#define GET_AppLoadBootproject(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppLoadBootproject(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppLoadBootproject  FALSE
	#define EXP_AppLoadBootproject  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppLoadBootproject
	#define EXT_AppLoadBootproject
	#define GET_AppLoadBootproject(fl)  CAL_CMGETAPI( "AppLoadBootproject" ) 
	#define CAL_AppLoadBootproject  AppLoadBootproject
	#define CHK_AppLoadBootproject  TRUE
	#define EXP_AppLoadBootproject  CAL_CMEXPAPI( "AppLoadBootproject" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppLoadBootproject
	#define EXT_AppLoadBootproject
	#define GET_AppLoadBootproject(fl)  CAL_CMGETAPI( "AppLoadBootproject" ) 
	#define CAL_AppLoadBootproject  AppLoadBootproject
	#define CHK_AppLoadBootproject  TRUE
	#define EXP_AppLoadBootproject  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppLoadBootproject", (RTS_UINTPTR)AppLoadBootproject, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppLoadBootproject
	#define EXT_CmpAppAppLoadBootproject
	#define GET_CmpAppAppLoadBootproject  ERR_OK
	#define CAL_CmpAppAppLoadBootproject pICmpApp->IAppLoadBootproject
	#define CHK_CmpAppAppLoadBootproject (pICmpApp != NULL)
	#define EXP_CmpAppAppLoadBootproject  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppLoadBootproject
	#define EXT_AppLoadBootproject
	#define GET_AppLoadBootproject(fl)  CAL_CMGETAPI( "AppLoadBootproject" ) 
	#define CAL_AppLoadBootproject pICmpApp->IAppLoadBootproject
	#define CHK_AppLoadBootproject (pICmpApp != NULL)
	#define EXP_AppLoadBootproject  CAL_CMEXPAPI( "AppLoadBootproject" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppLoadBootproject  PFAPPLOADBOOTPROJECT pfAppLoadBootproject;
	#define EXT_AppLoadBootproject  extern PFAPPLOADBOOTPROJECT pfAppLoadBootproject;
	#define GET_AppLoadBootproject(fl)  s_pfCMGetAPI2( "AppLoadBootproject", (RTS_VOID_FCTPTR *)&pfAppLoadBootproject, (fl), 0, 0)
	#define CAL_AppLoadBootproject  pfAppLoadBootproject
	#define CHK_AppLoadBootproject  (pfAppLoadBootproject != NULL)
	#define EXP_AppLoadBootproject  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppLoadBootproject", (RTS_UINTPTR)AppLoadBootproject, 0, 0) 
#endif




/**
 * <description>Start all applications</description>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppStartApplications(void);
typedef RTS_RESULT (CDECL * PFAPPSTARTAPPLICATIONS) (void);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPSTARTAPPLICATIONS_NOTIMPLEMENTED)
	#define USE_AppStartApplications
	#define EXT_AppStartApplications
	#define GET_AppStartApplications(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppStartApplications()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppStartApplications  FALSE
	#define EXP_AppStartApplications  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppStartApplications
	#define EXT_AppStartApplications
	#define GET_AppStartApplications(fl)  CAL_CMGETAPI( "AppStartApplications" ) 
	#define CAL_AppStartApplications  AppStartApplications
	#define CHK_AppStartApplications  TRUE
	#define EXP_AppStartApplications  CAL_CMEXPAPI( "AppStartApplications" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppStartApplications
	#define EXT_AppStartApplications
	#define GET_AppStartApplications(fl)  CAL_CMGETAPI( "AppStartApplications" ) 
	#define CAL_AppStartApplications  AppStartApplications
	#define CHK_AppStartApplications  TRUE
	#define EXP_AppStartApplications  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppStartApplications", (RTS_UINTPTR)AppStartApplications, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppStartApplications
	#define EXT_CmpAppAppStartApplications
	#define GET_CmpAppAppStartApplications  ERR_OK
	#define CAL_CmpAppAppStartApplications pICmpApp->IAppStartApplications
	#define CHK_CmpAppAppStartApplications (pICmpApp != NULL)
	#define EXP_CmpAppAppStartApplications  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppStartApplications
	#define EXT_AppStartApplications
	#define GET_AppStartApplications(fl)  CAL_CMGETAPI( "AppStartApplications" ) 
	#define CAL_AppStartApplications pICmpApp->IAppStartApplications
	#define CHK_AppStartApplications (pICmpApp != NULL)
	#define EXP_AppStartApplications  CAL_CMEXPAPI( "AppStartApplications" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppStartApplications  PFAPPSTARTAPPLICATIONS pfAppStartApplications;
	#define EXT_AppStartApplications  extern PFAPPSTARTAPPLICATIONS pfAppStartApplications;
	#define GET_AppStartApplications(fl)  s_pfCMGetAPI2( "AppStartApplications", (RTS_VOID_FCTPTR *)&pfAppStartApplications, (fl), 0, 0)
	#define CAL_AppStartApplications  pfAppStartApplications
	#define CHK_AppStartApplications  (pfAppStartApplications != NULL)
	#define EXP_AppStartApplications  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppStartApplications", (RTS_UINTPTR)AppStartApplications, 0, 0) 
#endif




/**
 * <description>Start an application</description>
 * <param name="pApp" type="IN">Pointer to the application</param>
 * <param name="ulStartReason" type="IN">Start reason, See corresponding category</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppStartApplication2(APPLICATION *pApp, RTS_UI32 ulStartReason);
typedef RTS_RESULT (CDECL * PFAPPSTARTAPPLICATION2) (APPLICATION *pApp, RTS_UI32 ulStartReason);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPSTARTAPPLICATION2_NOTIMPLEMENTED)
	#define USE_AppStartApplication2
	#define EXT_AppStartApplication2
	#define GET_AppStartApplication2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppStartApplication2(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppStartApplication2  FALSE
	#define EXP_AppStartApplication2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppStartApplication2
	#define EXT_AppStartApplication2
	#define GET_AppStartApplication2(fl)  CAL_CMGETAPI( "AppStartApplication2" ) 
	#define CAL_AppStartApplication2  AppStartApplication2
	#define CHK_AppStartApplication2  TRUE
	#define EXP_AppStartApplication2  CAL_CMEXPAPI( "AppStartApplication2" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppStartApplication2
	#define EXT_AppStartApplication2
	#define GET_AppStartApplication2(fl)  CAL_CMGETAPI( "AppStartApplication2" ) 
	#define CAL_AppStartApplication2  AppStartApplication2
	#define CHK_AppStartApplication2  TRUE
	#define EXP_AppStartApplication2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppStartApplication2", (RTS_UINTPTR)AppStartApplication2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppStartApplication2
	#define EXT_CmpAppAppStartApplication2
	#define GET_CmpAppAppStartApplication2  ERR_OK
	#define CAL_CmpAppAppStartApplication2 pICmpApp->IAppStartApplication2
	#define CHK_CmpAppAppStartApplication2 (pICmpApp != NULL)
	#define EXP_CmpAppAppStartApplication2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppStartApplication2
	#define EXT_AppStartApplication2
	#define GET_AppStartApplication2(fl)  CAL_CMGETAPI( "AppStartApplication2" ) 
	#define CAL_AppStartApplication2 pICmpApp->IAppStartApplication2
	#define CHK_AppStartApplication2 (pICmpApp != NULL)
	#define EXP_AppStartApplication2  CAL_CMEXPAPI( "AppStartApplication2" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppStartApplication2  PFAPPSTARTAPPLICATION2 pfAppStartApplication2;
	#define EXT_AppStartApplication2  extern PFAPPSTARTAPPLICATION2 pfAppStartApplication2;
	#define GET_AppStartApplication2(fl)  s_pfCMGetAPI2( "AppStartApplication2", (RTS_VOID_FCTPTR *)&pfAppStartApplication2, (fl), 0, 0)
	#define CAL_AppStartApplication2  pfAppStartApplication2
	#define CHK_AppStartApplication2  (pfAppStartApplication2 != NULL)
	#define EXP_AppStartApplication2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppStartApplication2", (RTS_UINTPTR)AppStartApplication2, 0, 0) 
#endif




/**
 * <description>Start an application</description>
 * <param name="pApp" type="IN">Pointer to the application</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppStartApplication(APPLICATION *pApp);
typedef RTS_RESULT (CDECL * PFAPPSTARTAPPLICATION) (APPLICATION *pApp);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPSTARTAPPLICATION_NOTIMPLEMENTED)
	#define USE_AppStartApplication
	#define EXT_AppStartApplication
	#define GET_AppStartApplication(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppStartApplication(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppStartApplication  FALSE
	#define EXP_AppStartApplication  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppStartApplication
	#define EXT_AppStartApplication
	#define GET_AppStartApplication(fl)  CAL_CMGETAPI( "AppStartApplication" ) 
	#define CAL_AppStartApplication  AppStartApplication
	#define CHK_AppStartApplication  TRUE
	#define EXP_AppStartApplication  CAL_CMEXPAPI( "AppStartApplication" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppStartApplication
	#define EXT_AppStartApplication
	#define GET_AppStartApplication(fl)  CAL_CMGETAPI( "AppStartApplication" ) 
	#define CAL_AppStartApplication  AppStartApplication
	#define CHK_AppStartApplication  TRUE
	#define EXP_AppStartApplication  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppStartApplication", (RTS_UINTPTR)AppStartApplication, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppStartApplication
	#define EXT_CmpAppAppStartApplication
	#define GET_CmpAppAppStartApplication  ERR_OK
	#define CAL_CmpAppAppStartApplication pICmpApp->IAppStartApplication
	#define CHK_CmpAppAppStartApplication (pICmpApp != NULL)
	#define EXP_CmpAppAppStartApplication  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppStartApplication
	#define EXT_AppStartApplication
	#define GET_AppStartApplication(fl)  CAL_CMGETAPI( "AppStartApplication" ) 
	#define CAL_AppStartApplication pICmpApp->IAppStartApplication
	#define CHK_AppStartApplication (pICmpApp != NULL)
	#define EXP_AppStartApplication  CAL_CMEXPAPI( "AppStartApplication" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppStartApplication  PFAPPSTARTAPPLICATION pfAppStartApplication;
	#define EXT_AppStartApplication  extern PFAPPSTARTAPPLICATION pfAppStartApplication;
	#define GET_AppStartApplication(fl)  s_pfCMGetAPI2( "AppStartApplication", (RTS_VOID_FCTPTR *)&pfAppStartApplication, (fl), 0, 0)
	#define CAL_AppStartApplication  pfAppStartApplication
	#define CHK_AppStartApplication  (pfAppStartApplication != NULL)
	#define EXP_AppStartApplication  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppStartApplication", (RTS_UINTPTR)AppStartApplication, 0, 0) 
#endif




/**
 * <description>Stop all applications</description>
 * <param name="ulTimeoutMs" type="IN">Timeout in milliseconds to wait for stop. RTS_TIMEOUT_DEFAULT can be used as the default value</param>
 * <param name="ulStopReason" type="IN">Stop reason, See corresponding category</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppStopApplications(RTS_UI32 ulTimeoutMs, RTS_UI32 ulStopReason);
typedef RTS_RESULT (CDECL * PFAPPSTOPAPPLICATIONS) (RTS_UI32 ulTimeoutMs, RTS_UI32 ulStopReason);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPSTOPAPPLICATIONS_NOTIMPLEMENTED)
	#define USE_AppStopApplications
	#define EXT_AppStopApplications
	#define GET_AppStopApplications(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppStopApplications(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppStopApplications  FALSE
	#define EXP_AppStopApplications  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppStopApplications
	#define EXT_AppStopApplications
	#define GET_AppStopApplications(fl)  CAL_CMGETAPI( "AppStopApplications" ) 
	#define CAL_AppStopApplications  AppStopApplications
	#define CHK_AppStopApplications  TRUE
	#define EXP_AppStopApplications  CAL_CMEXPAPI( "AppStopApplications" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppStopApplications
	#define EXT_AppStopApplications
	#define GET_AppStopApplications(fl)  CAL_CMGETAPI( "AppStopApplications" ) 
	#define CAL_AppStopApplications  AppStopApplications
	#define CHK_AppStopApplications  TRUE
	#define EXP_AppStopApplications  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppStopApplications", (RTS_UINTPTR)AppStopApplications, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppStopApplications
	#define EXT_CmpAppAppStopApplications
	#define GET_CmpAppAppStopApplications  ERR_OK
	#define CAL_CmpAppAppStopApplications pICmpApp->IAppStopApplications
	#define CHK_CmpAppAppStopApplications (pICmpApp != NULL)
	#define EXP_CmpAppAppStopApplications  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppStopApplications
	#define EXT_AppStopApplications
	#define GET_AppStopApplications(fl)  CAL_CMGETAPI( "AppStopApplications" ) 
	#define CAL_AppStopApplications pICmpApp->IAppStopApplications
	#define CHK_AppStopApplications (pICmpApp != NULL)
	#define EXP_AppStopApplications  CAL_CMEXPAPI( "AppStopApplications" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppStopApplications  PFAPPSTOPAPPLICATIONS pfAppStopApplications;
	#define EXT_AppStopApplications  extern PFAPPSTOPAPPLICATIONS pfAppStopApplications;
	#define GET_AppStopApplications(fl)  s_pfCMGetAPI2( "AppStopApplications", (RTS_VOID_FCTPTR *)&pfAppStopApplications, (fl), 0, 0)
	#define CAL_AppStopApplications  pfAppStopApplications
	#define CHK_AppStopApplications  (pfAppStopApplications != NULL)
	#define EXP_AppStopApplications  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppStopApplications", (RTS_UINTPTR)AppStopApplications, 0, 0) 
#endif




/**
 * <description>Stop an application</description>
 * <param name="pApp" type="IN">Pointer to the application</param>
 * <param name="ulTimeoutMs" type="IN">Timeout in milliseconds to wait for stop. RTS_TIMEOUT_DEFAULT can be used as the default value</param>
 * <param name="ulStopReason" type="IN">Stop reason, See corresponding category</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppStopApplication(APPLICATION *pApp, RTS_UI32 ulTimeoutMs, RTS_UI32 ulStopReason);
typedef RTS_RESULT (CDECL * PFAPPSTOPAPPLICATION) (APPLICATION *pApp, RTS_UI32 ulTimeoutMs, RTS_UI32 ulStopReason);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPSTOPAPPLICATION_NOTIMPLEMENTED)
	#define USE_AppStopApplication
	#define EXT_AppStopApplication
	#define GET_AppStopApplication(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppStopApplication(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppStopApplication  FALSE
	#define EXP_AppStopApplication  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppStopApplication
	#define EXT_AppStopApplication
	#define GET_AppStopApplication(fl)  CAL_CMGETAPI( "AppStopApplication" ) 
	#define CAL_AppStopApplication  AppStopApplication
	#define CHK_AppStopApplication  TRUE
	#define EXP_AppStopApplication  CAL_CMEXPAPI( "AppStopApplication" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppStopApplication
	#define EXT_AppStopApplication
	#define GET_AppStopApplication(fl)  CAL_CMGETAPI( "AppStopApplication" ) 
	#define CAL_AppStopApplication  AppStopApplication
	#define CHK_AppStopApplication  TRUE
	#define EXP_AppStopApplication  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppStopApplication", (RTS_UINTPTR)AppStopApplication, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppStopApplication
	#define EXT_CmpAppAppStopApplication
	#define GET_CmpAppAppStopApplication  ERR_OK
	#define CAL_CmpAppAppStopApplication pICmpApp->IAppStopApplication
	#define CHK_CmpAppAppStopApplication (pICmpApp != NULL)
	#define EXP_CmpAppAppStopApplication  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppStopApplication
	#define EXT_AppStopApplication
	#define GET_AppStopApplication(fl)  CAL_CMGETAPI( "AppStopApplication" ) 
	#define CAL_AppStopApplication pICmpApp->IAppStopApplication
	#define CHK_AppStopApplication (pICmpApp != NULL)
	#define EXP_AppStopApplication  CAL_CMEXPAPI( "AppStopApplication" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppStopApplication  PFAPPSTOPAPPLICATION pfAppStopApplication;
	#define EXT_AppStopApplication  extern PFAPPSTOPAPPLICATION pfAppStopApplication;
	#define GET_AppStopApplication(fl)  s_pfCMGetAPI2( "AppStopApplication", (RTS_VOID_FCTPTR *)&pfAppStopApplication, (fl), 0, 0)
	#define CAL_AppStopApplication  pfAppStopApplication
	#define CHK_AppStopApplication  (pfAppStopApplication != NULL)
	#define EXP_AppStopApplication  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppStopApplication", (RTS_UINTPTR)AppStopApplication, 0, 0) 
#endif




/**
 * <description>Exit an application (release all tasks, etc.). The application is not deleted!</description>
 * <param name="pApp" type="IN">Pointer to the application</param>
 * <param name="ulExitReason" type="IN">Reason for the exit, see category "Operation reason" for details</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppExitApplication(APPLICATION *pApp, RTS_UI32 ulExitReason);
typedef RTS_RESULT (CDECL * PFAPPEXITAPPLICATION) (APPLICATION *pApp, RTS_UI32 ulExitReason);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPEXITAPPLICATION_NOTIMPLEMENTED)
	#define USE_AppExitApplication
	#define EXT_AppExitApplication
	#define GET_AppExitApplication(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppExitApplication(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppExitApplication  FALSE
	#define EXP_AppExitApplication  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppExitApplication
	#define EXT_AppExitApplication
	#define GET_AppExitApplication(fl)  CAL_CMGETAPI( "AppExitApplication" ) 
	#define CAL_AppExitApplication  AppExitApplication
	#define CHK_AppExitApplication  TRUE
	#define EXP_AppExitApplication  CAL_CMEXPAPI( "AppExitApplication" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppExitApplication
	#define EXT_AppExitApplication
	#define GET_AppExitApplication(fl)  CAL_CMGETAPI( "AppExitApplication" ) 
	#define CAL_AppExitApplication  AppExitApplication
	#define CHK_AppExitApplication  TRUE
	#define EXP_AppExitApplication  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppExitApplication", (RTS_UINTPTR)AppExitApplication, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppExitApplication
	#define EXT_CmpAppAppExitApplication
	#define GET_CmpAppAppExitApplication  ERR_OK
	#define CAL_CmpAppAppExitApplication pICmpApp->IAppExitApplication
	#define CHK_CmpAppAppExitApplication (pICmpApp != NULL)
	#define EXP_CmpAppAppExitApplication  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppExitApplication
	#define EXT_AppExitApplication
	#define GET_AppExitApplication(fl)  CAL_CMGETAPI( "AppExitApplication" ) 
	#define CAL_AppExitApplication pICmpApp->IAppExitApplication
	#define CHK_AppExitApplication (pICmpApp != NULL)
	#define EXP_AppExitApplication  CAL_CMEXPAPI( "AppExitApplication" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppExitApplication  PFAPPEXITAPPLICATION pfAppExitApplication;
	#define EXT_AppExitApplication  extern PFAPPEXITAPPLICATION pfAppExitApplication;
	#define GET_AppExitApplication(fl)  s_pfCMGetAPI2( "AppExitApplication", (RTS_VOID_FCTPTR *)&pfAppExitApplication, (fl), 0, 0)
	#define CAL_AppExitApplication  pfAppExitApplication
	#define CHK_AppExitApplication  (pfAppExitApplication != NULL)
	#define EXP_AppExitApplication  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppExitApplication", (RTS_UINTPTR)AppExitApplication, 0, 0) 
#endif




/**
 * <description>Exit an application (release all tasks, etc.). The application is not deleted!</description>
 * <param name="pApp" type="IN">Pointer to the application</param>
 * <param name="ulExitReason" type="IN">Reason for the exit, see category "Operation reason" for details</param>
 * <param name="ulTimeoutMs" type="IN">Timeout in milliseconds to to stop the application during exit. RTS_TIMEOUT_DEFAULT can be used as the default value</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppExitApplication2(APPLICATION *pApp, RTS_UI32 ulExitReason, RTS_UI32 ulTimeoutMs);
typedef RTS_RESULT (CDECL * PFAPPEXITAPPLICATION2) (APPLICATION *pApp, RTS_UI32 ulExitReason, RTS_UI32 ulTimeoutMs);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPEXITAPPLICATION2_NOTIMPLEMENTED)
	#define USE_AppExitApplication2
	#define EXT_AppExitApplication2
	#define GET_AppExitApplication2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppExitApplication2(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppExitApplication2  FALSE
	#define EXP_AppExitApplication2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppExitApplication2
	#define EXT_AppExitApplication2
	#define GET_AppExitApplication2(fl)  CAL_CMGETAPI( "AppExitApplication2" ) 
	#define CAL_AppExitApplication2  AppExitApplication2
	#define CHK_AppExitApplication2  TRUE
	#define EXP_AppExitApplication2  CAL_CMEXPAPI( "AppExitApplication2" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppExitApplication2
	#define EXT_AppExitApplication2
	#define GET_AppExitApplication2(fl)  CAL_CMGETAPI( "AppExitApplication2" ) 
	#define CAL_AppExitApplication2  AppExitApplication2
	#define CHK_AppExitApplication2  TRUE
	#define EXP_AppExitApplication2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppExitApplication2", (RTS_UINTPTR)AppExitApplication2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppExitApplication2
	#define EXT_CmpAppAppExitApplication2
	#define GET_CmpAppAppExitApplication2  ERR_OK
	#define CAL_CmpAppAppExitApplication2 pICmpApp->IAppExitApplication2
	#define CHK_CmpAppAppExitApplication2 (pICmpApp != NULL)
	#define EXP_CmpAppAppExitApplication2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppExitApplication2
	#define EXT_AppExitApplication2
	#define GET_AppExitApplication2(fl)  CAL_CMGETAPI( "AppExitApplication2" ) 
	#define CAL_AppExitApplication2 pICmpApp->IAppExitApplication2
	#define CHK_AppExitApplication2 (pICmpApp != NULL)
	#define EXP_AppExitApplication2  CAL_CMEXPAPI( "AppExitApplication2" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppExitApplication2  PFAPPEXITAPPLICATION2 pfAppExitApplication2;
	#define EXT_AppExitApplication2  extern PFAPPEXITAPPLICATION2 pfAppExitApplication2;
	#define GET_AppExitApplication2(fl)  s_pfCMGetAPI2( "AppExitApplication2", (RTS_VOID_FCTPTR *)&pfAppExitApplication2, (fl), 0, 0)
	#define CAL_AppExitApplication2  pfAppExitApplication2
	#define CHK_AppExitApplication2  (pfAppExitApplication2 != NULL)
	#define EXP_AppExitApplication2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppExitApplication2", (RTS_UINTPTR)AppExitApplication2, 0, 0) 
#endif




/**
 * <description>Exit all applications (release all tasks, etc.). The applications are not deleted!</description>
 * <param name="ulExitReason" type="IN">Reason for the exit, see category "Operation reason" for details</param>
 * <param name="ulTimeoutMs" type="IN">Timeout in milliseconds to stop the application during exit. RTS_TIMEOUT_DEFAULT can be used as the default value</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppExitApplications(RTS_UI32 ulExitReason, RTS_UI32 ulTimeoutMs);
typedef RTS_RESULT (CDECL * PFAPPEXITAPPLICATIONS) (RTS_UI32 ulExitReason, RTS_UI32 ulTimeoutMs);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPEXITAPPLICATIONS_NOTIMPLEMENTED)
	#define USE_AppExitApplications
	#define EXT_AppExitApplications
	#define GET_AppExitApplications(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppExitApplications(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppExitApplications  FALSE
	#define EXP_AppExitApplications  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppExitApplications
	#define EXT_AppExitApplications
	#define GET_AppExitApplications(fl)  CAL_CMGETAPI( "AppExitApplications" ) 
	#define CAL_AppExitApplications  AppExitApplications
	#define CHK_AppExitApplications  TRUE
	#define EXP_AppExitApplications  CAL_CMEXPAPI( "AppExitApplications" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppExitApplications
	#define EXT_AppExitApplications
	#define GET_AppExitApplications(fl)  CAL_CMGETAPI( "AppExitApplications" ) 
	#define CAL_AppExitApplications  AppExitApplications
	#define CHK_AppExitApplications  TRUE
	#define EXP_AppExitApplications  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppExitApplications", (RTS_UINTPTR)AppExitApplications, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppExitApplications
	#define EXT_CmpAppAppExitApplications
	#define GET_CmpAppAppExitApplications  ERR_OK
	#define CAL_CmpAppAppExitApplications pICmpApp->IAppExitApplications
	#define CHK_CmpAppAppExitApplications (pICmpApp != NULL)
	#define EXP_CmpAppAppExitApplications  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppExitApplications
	#define EXT_AppExitApplications
	#define GET_AppExitApplications(fl)  CAL_CMGETAPI( "AppExitApplications" ) 
	#define CAL_AppExitApplications pICmpApp->IAppExitApplications
	#define CHK_AppExitApplications (pICmpApp != NULL)
	#define EXP_AppExitApplications  CAL_CMEXPAPI( "AppExitApplications" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppExitApplications  PFAPPEXITAPPLICATIONS pfAppExitApplications;
	#define EXT_AppExitApplications  extern PFAPPEXITAPPLICATIONS pfAppExitApplications;
	#define GET_AppExitApplications(fl)  s_pfCMGetAPI2( "AppExitApplications", (RTS_VOID_FCTPTR *)&pfAppExitApplications, (fl), 0, 0)
	#define CAL_AppExitApplications  pfAppExitApplications
	#define CHK_AppExitApplications  (pfAppExitApplications != NULL)
	#define EXP_AppExitApplications  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppExitApplications", (RTS_UINTPTR)AppExitApplications, 0, 0) 
#endif




/**
 * <description>Delete an application. Bootproject will not deleted!</description>
 * <param name="pApp" type="IN">Pointer to the application</param>
 * <param name="ulDeleteReason" type="IN">Reason for the delete, see category "Operation reason" for details</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppDeleteApplication(APPLICATION *pApp, RTS_UI32 ulDeleteReason);
typedef RTS_RESULT (CDECL * PFAPPDELETEAPPLICATION) (APPLICATION *pApp, RTS_UI32 ulDeleteReason);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPDELETEAPPLICATION_NOTIMPLEMENTED)
	#define USE_AppDeleteApplication
	#define EXT_AppDeleteApplication
	#define GET_AppDeleteApplication(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppDeleteApplication(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppDeleteApplication  FALSE
	#define EXP_AppDeleteApplication  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppDeleteApplication
	#define EXT_AppDeleteApplication
	#define GET_AppDeleteApplication(fl)  CAL_CMGETAPI( "AppDeleteApplication" ) 
	#define CAL_AppDeleteApplication  AppDeleteApplication
	#define CHK_AppDeleteApplication  TRUE
	#define EXP_AppDeleteApplication  CAL_CMEXPAPI( "AppDeleteApplication" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppDeleteApplication
	#define EXT_AppDeleteApplication
	#define GET_AppDeleteApplication(fl)  CAL_CMGETAPI( "AppDeleteApplication" ) 
	#define CAL_AppDeleteApplication  AppDeleteApplication
	#define CHK_AppDeleteApplication  TRUE
	#define EXP_AppDeleteApplication  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppDeleteApplication", (RTS_UINTPTR)AppDeleteApplication, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppDeleteApplication
	#define EXT_CmpAppAppDeleteApplication
	#define GET_CmpAppAppDeleteApplication  ERR_OK
	#define CAL_CmpAppAppDeleteApplication pICmpApp->IAppDeleteApplication
	#define CHK_CmpAppAppDeleteApplication (pICmpApp != NULL)
	#define EXP_CmpAppAppDeleteApplication  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppDeleteApplication
	#define EXT_AppDeleteApplication
	#define GET_AppDeleteApplication(fl)  CAL_CMGETAPI( "AppDeleteApplication" ) 
	#define CAL_AppDeleteApplication pICmpApp->IAppDeleteApplication
	#define CHK_AppDeleteApplication (pICmpApp != NULL)
	#define EXP_AppDeleteApplication  CAL_CMEXPAPI( "AppDeleteApplication" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppDeleteApplication  PFAPPDELETEAPPLICATION pfAppDeleteApplication;
	#define EXT_AppDeleteApplication  extern PFAPPDELETEAPPLICATION pfAppDeleteApplication;
	#define GET_AppDeleteApplication(fl)  s_pfCMGetAPI2( "AppDeleteApplication", (RTS_VOID_FCTPTR *)&pfAppDeleteApplication, (fl), 0, 0)
	#define CAL_AppDeleteApplication  pfAppDeleteApplication
	#define CHK_AppDeleteApplication  (pfAppDeleteApplication != NULL)
	#define EXP_AppDeleteApplication  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppDeleteApplication", (RTS_UINTPTR)AppDeleteApplication, 0, 0) 
#endif




/**
 * <description>Delete all applications. Bootprojects will not be deleted!</description>
 * <param name="ulDeleteReason" type="IN">Reason for the delete, see category "Operation reason" for details</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppDeleteApplications(RTS_UI32 ulDeleteReason);
typedef RTS_RESULT (CDECL * PFAPPDELETEAPPLICATIONS) (RTS_UI32 ulDeleteReason);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPDELETEAPPLICATIONS_NOTIMPLEMENTED)
	#define USE_AppDeleteApplications
	#define EXT_AppDeleteApplications
	#define GET_AppDeleteApplications(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppDeleteApplications(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppDeleteApplications  FALSE
	#define EXP_AppDeleteApplications  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppDeleteApplications
	#define EXT_AppDeleteApplications
	#define GET_AppDeleteApplications(fl)  CAL_CMGETAPI( "AppDeleteApplications" ) 
	#define CAL_AppDeleteApplications  AppDeleteApplications
	#define CHK_AppDeleteApplications  TRUE
	#define EXP_AppDeleteApplications  CAL_CMEXPAPI( "AppDeleteApplications" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppDeleteApplications
	#define EXT_AppDeleteApplications
	#define GET_AppDeleteApplications(fl)  CAL_CMGETAPI( "AppDeleteApplications" ) 
	#define CAL_AppDeleteApplications  AppDeleteApplications
	#define CHK_AppDeleteApplications  TRUE
	#define EXP_AppDeleteApplications  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppDeleteApplications", (RTS_UINTPTR)AppDeleteApplications, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppDeleteApplications
	#define EXT_CmpAppAppDeleteApplications
	#define GET_CmpAppAppDeleteApplications  ERR_OK
	#define CAL_CmpAppAppDeleteApplications pICmpApp->IAppDeleteApplications
	#define CHK_CmpAppAppDeleteApplications (pICmpApp != NULL)
	#define EXP_CmpAppAppDeleteApplications  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppDeleteApplications
	#define EXT_AppDeleteApplications
	#define GET_AppDeleteApplications(fl)  CAL_CMGETAPI( "AppDeleteApplications" ) 
	#define CAL_AppDeleteApplications pICmpApp->IAppDeleteApplications
	#define CHK_AppDeleteApplications (pICmpApp != NULL)
	#define EXP_AppDeleteApplications  CAL_CMEXPAPI( "AppDeleteApplications" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppDeleteApplications  PFAPPDELETEAPPLICATIONS pfAppDeleteApplications;
	#define EXT_AppDeleteApplications  extern PFAPPDELETEAPPLICATIONS pfAppDeleteApplications;
	#define GET_AppDeleteApplications(fl)  s_pfCMGetAPI2( "AppDeleteApplications", (RTS_VOID_FCTPTR *)&pfAppDeleteApplications, (fl), 0, 0)
	#define CAL_AppDeleteApplications  pfAppDeleteApplications
	#define CHK_AppDeleteApplications  (pfAppDeleteApplications != NULL)
	#define EXP_AppDeleteApplications  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppDeleteApplications", (RTS_UINTPTR)AppDeleteApplications, 0, 0) 
#endif




/**
 * <description>Delete a bootproject (corresponding loaded application will not be affected or deleted!)</description>
 * <param name="pApp" type="IN">Pointer to the application</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppDeleteBootproject(APPLICATION *pApp);
typedef RTS_RESULT (CDECL * PFAPPDELETEBOOTPROJECT) (APPLICATION *pApp);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPDELETEBOOTPROJECT_NOTIMPLEMENTED)
	#define USE_AppDeleteBootproject
	#define EXT_AppDeleteBootproject
	#define GET_AppDeleteBootproject(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppDeleteBootproject(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppDeleteBootproject  FALSE
	#define EXP_AppDeleteBootproject  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppDeleteBootproject
	#define EXT_AppDeleteBootproject
	#define GET_AppDeleteBootproject(fl)  CAL_CMGETAPI( "AppDeleteBootproject" ) 
	#define CAL_AppDeleteBootproject  AppDeleteBootproject
	#define CHK_AppDeleteBootproject  TRUE
	#define EXP_AppDeleteBootproject  CAL_CMEXPAPI( "AppDeleteBootproject" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppDeleteBootproject
	#define EXT_AppDeleteBootproject
	#define GET_AppDeleteBootproject(fl)  CAL_CMGETAPI( "AppDeleteBootproject" ) 
	#define CAL_AppDeleteBootproject  AppDeleteBootproject
	#define CHK_AppDeleteBootproject  TRUE
	#define EXP_AppDeleteBootproject  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppDeleteBootproject", (RTS_UINTPTR)AppDeleteBootproject, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppDeleteBootproject
	#define EXT_CmpAppAppDeleteBootproject
	#define GET_CmpAppAppDeleteBootproject  ERR_OK
	#define CAL_CmpAppAppDeleteBootproject pICmpApp->IAppDeleteBootproject
	#define CHK_CmpAppAppDeleteBootproject (pICmpApp != NULL)
	#define EXP_CmpAppAppDeleteBootproject  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppDeleteBootproject
	#define EXT_AppDeleteBootproject
	#define GET_AppDeleteBootproject(fl)  CAL_CMGETAPI( "AppDeleteBootproject" ) 
	#define CAL_AppDeleteBootproject pICmpApp->IAppDeleteBootproject
	#define CHK_AppDeleteBootproject (pICmpApp != NULL)
	#define EXP_AppDeleteBootproject  CAL_CMEXPAPI( "AppDeleteBootproject" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppDeleteBootproject  PFAPPDELETEBOOTPROJECT pfAppDeleteBootproject;
	#define EXT_AppDeleteBootproject  extern PFAPPDELETEBOOTPROJECT pfAppDeleteBootproject;
	#define GET_AppDeleteBootproject(fl)  s_pfCMGetAPI2( "AppDeleteBootproject", (RTS_VOID_FCTPTR *)&pfAppDeleteBootproject, (fl), 0, 0)
	#define CAL_AppDeleteBootproject  pfAppDeleteBootproject
	#define CHK_AppDeleteBootproject  (pfAppDeleteBootproject != NULL)
	#define EXP_AppDeleteBootproject  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppDeleteBootproject", (RTS_UINTPTR)AppDeleteBootproject, 0, 0) 
#endif




/**
 * <description>Add the peer address of an existing data server. This can be used from clients, that wants to
 *	get symbolic access to IEC variables. If the symbolic infromation is not available here on the controller,
 *	the registered data server can be used for that.</description>
 * <param name="ulSessionId" type="IN">SessionId of the communication channel</param>
 * <param name="pPeerAddr" type="IN">Pointer to the peer address of the data server</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppAddAddrDataSrv(RTS_UI32 ulSessionId, PEERADDRESS *pPeerAddr);
typedef RTS_RESULT (CDECL * PFAPPADDADDRDATASRV) (RTS_UI32 ulSessionId, PEERADDRESS *pPeerAddr);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPADDADDRDATASRV_NOTIMPLEMENTED)
	#define USE_AppAddAddrDataSrv
	#define EXT_AppAddAddrDataSrv
	#define GET_AppAddAddrDataSrv(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppAddAddrDataSrv(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppAddAddrDataSrv  FALSE
	#define EXP_AppAddAddrDataSrv  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppAddAddrDataSrv
	#define EXT_AppAddAddrDataSrv
	#define GET_AppAddAddrDataSrv(fl)  CAL_CMGETAPI( "AppAddAddrDataSrv" ) 
	#define CAL_AppAddAddrDataSrv  AppAddAddrDataSrv
	#define CHK_AppAddAddrDataSrv  TRUE
	#define EXP_AppAddAddrDataSrv  CAL_CMEXPAPI( "AppAddAddrDataSrv" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppAddAddrDataSrv
	#define EXT_AppAddAddrDataSrv
	#define GET_AppAddAddrDataSrv(fl)  CAL_CMGETAPI( "AppAddAddrDataSrv" ) 
	#define CAL_AppAddAddrDataSrv  AppAddAddrDataSrv
	#define CHK_AppAddAddrDataSrv  TRUE
	#define EXP_AppAddAddrDataSrv  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppAddAddrDataSrv", (RTS_UINTPTR)AppAddAddrDataSrv, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppAddAddrDataSrv
	#define EXT_CmpAppAppAddAddrDataSrv
	#define GET_CmpAppAppAddAddrDataSrv  ERR_OK
	#define CAL_CmpAppAppAddAddrDataSrv pICmpApp->IAppAddAddrDataSrv
	#define CHK_CmpAppAppAddAddrDataSrv (pICmpApp != NULL)
	#define EXP_CmpAppAppAddAddrDataSrv  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppAddAddrDataSrv
	#define EXT_AppAddAddrDataSrv
	#define GET_AppAddAddrDataSrv(fl)  CAL_CMGETAPI( "AppAddAddrDataSrv" ) 
	#define CAL_AppAddAddrDataSrv pICmpApp->IAppAddAddrDataSrv
	#define CHK_AppAddAddrDataSrv (pICmpApp != NULL)
	#define EXP_AppAddAddrDataSrv  CAL_CMEXPAPI( "AppAddAddrDataSrv" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppAddAddrDataSrv  PFAPPADDADDRDATASRV pfAppAddAddrDataSrv;
	#define EXT_AppAddAddrDataSrv  extern PFAPPADDADDRDATASRV pfAppAddAddrDataSrv;
	#define GET_AppAddAddrDataSrv(fl)  s_pfCMGetAPI2( "AppAddAddrDataSrv", (RTS_VOID_FCTPTR *)&pfAppAddAddrDataSrv, (fl), 0, 0)
	#define CAL_AppAddAddrDataSrv  pfAppAddAddrDataSrv
	#define CHK_AppAddAddrDataSrv  (pfAppAddAddrDataSrv != NULL)
	#define EXP_AppAddAddrDataSrv  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppAddAddrDataSrv", (RTS_UINTPTR)AppAddAddrDataSrv, 0, 0) 
#endif




/**
 * <description>Remove a peer address of an existing data server that will be shutdown</description>
 * <param name="ulSessionId" type="IN">SessionId of the communication channel</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppRemoveAddrDataSrv(RTS_UI32 ulSessionId);
typedef RTS_RESULT (CDECL * PFAPPREMOVEADDRDATASRV) (RTS_UI32 ulSessionId);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPREMOVEADDRDATASRV_NOTIMPLEMENTED)
	#define USE_AppRemoveAddrDataSrv
	#define EXT_AppRemoveAddrDataSrv
	#define GET_AppRemoveAddrDataSrv(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppRemoveAddrDataSrv(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppRemoveAddrDataSrv  FALSE
	#define EXP_AppRemoveAddrDataSrv  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppRemoveAddrDataSrv
	#define EXT_AppRemoveAddrDataSrv
	#define GET_AppRemoveAddrDataSrv(fl)  CAL_CMGETAPI( "AppRemoveAddrDataSrv" ) 
	#define CAL_AppRemoveAddrDataSrv  AppRemoveAddrDataSrv
	#define CHK_AppRemoveAddrDataSrv  TRUE
	#define EXP_AppRemoveAddrDataSrv  CAL_CMEXPAPI( "AppRemoveAddrDataSrv" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppRemoveAddrDataSrv
	#define EXT_AppRemoveAddrDataSrv
	#define GET_AppRemoveAddrDataSrv(fl)  CAL_CMGETAPI( "AppRemoveAddrDataSrv" ) 
	#define CAL_AppRemoveAddrDataSrv  AppRemoveAddrDataSrv
	#define CHK_AppRemoveAddrDataSrv  TRUE
	#define EXP_AppRemoveAddrDataSrv  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppRemoveAddrDataSrv", (RTS_UINTPTR)AppRemoveAddrDataSrv, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppRemoveAddrDataSrv
	#define EXT_CmpAppAppRemoveAddrDataSrv
	#define GET_CmpAppAppRemoveAddrDataSrv  ERR_OK
	#define CAL_CmpAppAppRemoveAddrDataSrv pICmpApp->IAppRemoveAddrDataSrv
	#define CHK_CmpAppAppRemoveAddrDataSrv (pICmpApp != NULL)
	#define EXP_CmpAppAppRemoveAddrDataSrv  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppRemoveAddrDataSrv
	#define EXT_AppRemoveAddrDataSrv
	#define GET_AppRemoveAddrDataSrv(fl)  CAL_CMGETAPI( "AppRemoveAddrDataSrv" ) 
	#define CAL_AppRemoveAddrDataSrv pICmpApp->IAppRemoveAddrDataSrv
	#define CHK_AppRemoveAddrDataSrv (pICmpApp != NULL)
	#define EXP_AppRemoveAddrDataSrv  CAL_CMEXPAPI( "AppRemoveAddrDataSrv" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppRemoveAddrDataSrv  PFAPPREMOVEADDRDATASRV pfAppRemoveAddrDataSrv;
	#define EXT_AppRemoveAddrDataSrv  extern PFAPPREMOVEADDRDATASRV pfAppRemoveAddrDataSrv;
	#define GET_AppRemoveAddrDataSrv(fl)  s_pfCMGetAPI2( "AppRemoveAddrDataSrv", (RTS_VOID_FCTPTR *)&pfAppRemoveAddrDataSrv, (fl), 0, 0)
	#define CAL_AppRemoveAddrDataSrv  pfAppRemoveAddrDataSrv
	#define CHK_AppRemoveAddrDataSrv  (pfAppRemoveAddrDataSrv != NULL)
	#define EXP_AppRemoveAddrDataSrv  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppRemoveAddrDataSrv", (RTS_UINTPTR)AppRemoveAddrDataSrv, 0, 0) 
#endif




/**
 * <description>Retrieves the peer address of the first registered data server</description>
 * <param name="ppPeerAddr" type="OUT">Pointer pointer to the peer address</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to get the next peer addresse of a registered data server, RTS_INVALID_HANDLE if not available</result>
 */
RTS_HANDLE CDECL AppGetFirstAddrDataSrv(PEERADDRESS **ppPeerAddr, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFAPPGETFIRSTADDRDATASRV) (PEERADDRESS **ppPeerAddr, RTS_RESULT *pResult);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETFIRSTADDRDATASRV_NOTIMPLEMENTED)
	#define USE_AppGetFirstAddrDataSrv
	#define EXT_AppGetFirstAddrDataSrv
	#define GET_AppGetFirstAddrDataSrv(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetFirstAddrDataSrv(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_AppGetFirstAddrDataSrv  FALSE
	#define EXP_AppGetFirstAddrDataSrv  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetFirstAddrDataSrv
	#define EXT_AppGetFirstAddrDataSrv
	#define GET_AppGetFirstAddrDataSrv(fl)  CAL_CMGETAPI( "AppGetFirstAddrDataSrv" ) 
	#define CAL_AppGetFirstAddrDataSrv  AppGetFirstAddrDataSrv
	#define CHK_AppGetFirstAddrDataSrv  TRUE
	#define EXP_AppGetFirstAddrDataSrv  CAL_CMEXPAPI( "AppGetFirstAddrDataSrv" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetFirstAddrDataSrv
	#define EXT_AppGetFirstAddrDataSrv
	#define GET_AppGetFirstAddrDataSrv(fl)  CAL_CMGETAPI( "AppGetFirstAddrDataSrv" ) 
	#define CAL_AppGetFirstAddrDataSrv  AppGetFirstAddrDataSrv
	#define CHK_AppGetFirstAddrDataSrv  TRUE
	#define EXP_AppGetFirstAddrDataSrv  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetFirstAddrDataSrv", (RTS_UINTPTR)AppGetFirstAddrDataSrv, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetFirstAddrDataSrv
	#define EXT_CmpAppAppGetFirstAddrDataSrv
	#define GET_CmpAppAppGetFirstAddrDataSrv  ERR_OK
	#define CAL_CmpAppAppGetFirstAddrDataSrv pICmpApp->IAppGetFirstAddrDataSrv
	#define CHK_CmpAppAppGetFirstAddrDataSrv (pICmpApp != NULL)
	#define EXP_CmpAppAppGetFirstAddrDataSrv  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetFirstAddrDataSrv
	#define EXT_AppGetFirstAddrDataSrv
	#define GET_AppGetFirstAddrDataSrv(fl)  CAL_CMGETAPI( "AppGetFirstAddrDataSrv" ) 
	#define CAL_AppGetFirstAddrDataSrv pICmpApp->IAppGetFirstAddrDataSrv
	#define CHK_AppGetFirstAddrDataSrv (pICmpApp != NULL)
	#define EXP_AppGetFirstAddrDataSrv  CAL_CMEXPAPI( "AppGetFirstAddrDataSrv" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetFirstAddrDataSrv  PFAPPGETFIRSTADDRDATASRV pfAppGetFirstAddrDataSrv;
	#define EXT_AppGetFirstAddrDataSrv  extern PFAPPGETFIRSTADDRDATASRV pfAppGetFirstAddrDataSrv;
	#define GET_AppGetFirstAddrDataSrv(fl)  s_pfCMGetAPI2( "AppGetFirstAddrDataSrv", (RTS_VOID_FCTPTR *)&pfAppGetFirstAddrDataSrv, (fl), 0, 0)
	#define CAL_AppGetFirstAddrDataSrv  pfAppGetFirstAddrDataSrv
	#define CHK_AppGetFirstAddrDataSrv  (pfAppGetFirstAddrDataSrv != NULL)
	#define EXP_AppGetFirstAddrDataSrv  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetFirstAddrDataSrv", (RTS_UINTPTR)AppGetFirstAddrDataSrv, 0, 0) 
#endif




/**
 * <description>Retrieves the peer address of the first registered data server</description>
 * <param name="hAddr" type="IN">Handle, that was retrieved by the AppGetFirstAddrDataSrv() function</param>
 * <param name="ppPeerAddr" type="OUT">Pointer pointer to the peer address</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to get the next peer addresse of a registered data server, RTS_INVALID_HANDLE if not available</result>
 */
RTS_HANDLE CDECL AppGetNextAddrDataSrv(RTS_HANDLE hAddr, PEERADDRESS **ppPeerAddr, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFAPPGETNEXTADDRDATASRV) (RTS_HANDLE hAddr, PEERADDRESS **ppPeerAddr, RTS_RESULT *pResult);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETNEXTADDRDATASRV_NOTIMPLEMENTED)
	#define USE_AppGetNextAddrDataSrv
	#define EXT_AppGetNextAddrDataSrv
	#define GET_AppGetNextAddrDataSrv(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetNextAddrDataSrv(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_AppGetNextAddrDataSrv  FALSE
	#define EXP_AppGetNextAddrDataSrv  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetNextAddrDataSrv
	#define EXT_AppGetNextAddrDataSrv
	#define GET_AppGetNextAddrDataSrv(fl)  CAL_CMGETAPI( "AppGetNextAddrDataSrv" ) 
	#define CAL_AppGetNextAddrDataSrv  AppGetNextAddrDataSrv
	#define CHK_AppGetNextAddrDataSrv  TRUE
	#define EXP_AppGetNextAddrDataSrv  CAL_CMEXPAPI( "AppGetNextAddrDataSrv" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetNextAddrDataSrv
	#define EXT_AppGetNextAddrDataSrv
	#define GET_AppGetNextAddrDataSrv(fl)  CAL_CMGETAPI( "AppGetNextAddrDataSrv" ) 
	#define CAL_AppGetNextAddrDataSrv  AppGetNextAddrDataSrv
	#define CHK_AppGetNextAddrDataSrv  TRUE
	#define EXP_AppGetNextAddrDataSrv  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetNextAddrDataSrv", (RTS_UINTPTR)AppGetNextAddrDataSrv, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetNextAddrDataSrv
	#define EXT_CmpAppAppGetNextAddrDataSrv
	#define GET_CmpAppAppGetNextAddrDataSrv  ERR_OK
	#define CAL_CmpAppAppGetNextAddrDataSrv pICmpApp->IAppGetNextAddrDataSrv
	#define CHK_CmpAppAppGetNextAddrDataSrv (pICmpApp != NULL)
	#define EXP_CmpAppAppGetNextAddrDataSrv  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetNextAddrDataSrv
	#define EXT_AppGetNextAddrDataSrv
	#define GET_AppGetNextAddrDataSrv(fl)  CAL_CMGETAPI( "AppGetNextAddrDataSrv" ) 
	#define CAL_AppGetNextAddrDataSrv pICmpApp->IAppGetNextAddrDataSrv
	#define CHK_AppGetNextAddrDataSrv (pICmpApp != NULL)
	#define EXP_AppGetNextAddrDataSrv  CAL_CMEXPAPI( "AppGetNextAddrDataSrv" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetNextAddrDataSrv  PFAPPGETNEXTADDRDATASRV pfAppGetNextAddrDataSrv;
	#define EXT_AppGetNextAddrDataSrv  extern PFAPPGETNEXTADDRDATASRV pfAppGetNextAddrDataSrv;
	#define GET_AppGetNextAddrDataSrv(fl)  s_pfCMGetAPI2( "AppGetNextAddrDataSrv", (RTS_VOID_FCTPTR *)&pfAppGetNextAddrDataSrv, (fl), 0, 0)
	#define CAL_AppGetNextAddrDataSrv  pfAppGetNextAddrDataSrv
	#define CHK_AppGetNextAddrDataSrv  (pfAppGetNextAddrDataSrv != NULL)
	#define EXP_AppGetNextAddrDataSrv  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetNextAddrDataSrv", (RTS_UINTPTR)AppGetNextAddrDataSrv, 0, 0) 
#endif




/**
 * <description>Begin a consistency sequence. This can be used to check, if any task of an IEC application
 *	(or its father application) was active during this sequence. A typical usage is the task consistent
 *	data monitoring during this sequence.
 * </description>
 * <param name="pApp" type="IN">Pointer to the application</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Return a handle to the consistency object</result>
 */
RTS_HANDLE CDECL AppConsistencyCheckBegin(APPLICATION *pApp, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFAPPCONSISTENCYCHECKBEGIN) (APPLICATION *pApp, RTS_RESULT *pResult);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPCONSISTENCYCHECKBEGIN_NOTIMPLEMENTED)
	#define USE_AppConsistencyCheckBegin
	#define EXT_AppConsistencyCheckBegin
	#define GET_AppConsistencyCheckBegin(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppConsistencyCheckBegin(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_AppConsistencyCheckBegin  FALSE
	#define EXP_AppConsistencyCheckBegin  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppConsistencyCheckBegin
	#define EXT_AppConsistencyCheckBegin
	#define GET_AppConsistencyCheckBegin(fl)  CAL_CMGETAPI( "AppConsistencyCheckBegin" ) 
	#define CAL_AppConsistencyCheckBegin  AppConsistencyCheckBegin
	#define CHK_AppConsistencyCheckBegin  TRUE
	#define EXP_AppConsistencyCheckBegin  CAL_CMEXPAPI( "AppConsistencyCheckBegin" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppConsistencyCheckBegin
	#define EXT_AppConsistencyCheckBegin
	#define GET_AppConsistencyCheckBegin(fl)  CAL_CMGETAPI( "AppConsistencyCheckBegin" ) 
	#define CAL_AppConsistencyCheckBegin  AppConsistencyCheckBegin
	#define CHK_AppConsistencyCheckBegin  TRUE
	#define EXP_AppConsistencyCheckBegin  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppConsistencyCheckBegin", (RTS_UINTPTR)AppConsistencyCheckBegin, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppConsistencyCheckBegin
	#define EXT_CmpAppAppConsistencyCheckBegin
	#define GET_CmpAppAppConsistencyCheckBegin  ERR_OK
	#define CAL_CmpAppAppConsistencyCheckBegin pICmpApp->IAppConsistencyCheckBegin
	#define CHK_CmpAppAppConsistencyCheckBegin (pICmpApp != NULL)
	#define EXP_CmpAppAppConsistencyCheckBegin  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppConsistencyCheckBegin
	#define EXT_AppConsistencyCheckBegin
	#define GET_AppConsistencyCheckBegin(fl)  CAL_CMGETAPI( "AppConsistencyCheckBegin" ) 
	#define CAL_AppConsistencyCheckBegin pICmpApp->IAppConsistencyCheckBegin
	#define CHK_AppConsistencyCheckBegin (pICmpApp != NULL)
	#define EXP_AppConsistencyCheckBegin  CAL_CMEXPAPI( "AppConsistencyCheckBegin" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppConsistencyCheckBegin  PFAPPCONSISTENCYCHECKBEGIN pfAppConsistencyCheckBegin;
	#define EXT_AppConsistencyCheckBegin  extern PFAPPCONSISTENCYCHECKBEGIN pfAppConsistencyCheckBegin;
	#define GET_AppConsistencyCheckBegin(fl)  s_pfCMGetAPI2( "AppConsistencyCheckBegin", (RTS_VOID_FCTPTR *)&pfAppConsistencyCheckBegin, (fl), 0, 0)
	#define CAL_AppConsistencyCheckBegin  pfAppConsistencyCheckBegin
	#define CHK_AppConsistencyCheckBegin  (pfAppConsistencyCheckBegin != NULL)
	#define EXP_AppConsistencyCheckBegin  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppConsistencyCheckBegin", (RTS_UINTPTR)AppConsistencyCheckBegin, 0, 0) 
#endif




/**
 * <description>End a consistency sequence. This can be used to check, if any task of an IEC application
 *	(or its father application) was active during this consistency sequence.
 *	A typical usage is the task consistent data monitoring.
 * </description>
 * <param name="hConsistency" type="IN">Handle to the consistency object that is returned by AppConsistencyBegin()</param>
 * <result>ERR_OK: No task active during this consistency sequence,
 *		   ERR_FAILED: Any task of this application was active during this sequence</result>
 */
RTS_RESULT CDECL AppConsistencyCheckEnd(RTS_HANDLE hConsistency);
typedef RTS_RESULT (CDECL * PFAPPCONSISTENCYCHECKEND) (RTS_HANDLE hConsistency);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPCONSISTENCYCHECKEND_NOTIMPLEMENTED)
	#define USE_AppConsistencyCheckEnd
	#define EXT_AppConsistencyCheckEnd
	#define GET_AppConsistencyCheckEnd(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppConsistencyCheckEnd(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppConsistencyCheckEnd  FALSE
	#define EXP_AppConsistencyCheckEnd  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppConsistencyCheckEnd
	#define EXT_AppConsistencyCheckEnd
	#define GET_AppConsistencyCheckEnd(fl)  CAL_CMGETAPI( "AppConsistencyCheckEnd" ) 
	#define CAL_AppConsistencyCheckEnd  AppConsistencyCheckEnd
	#define CHK_AppConsistencyCheckEnd  TRUE
	#define EXP_AppConsistencyCheckEnd  CAL_CMEXPAPI( "AppConsistencyCheckEnd" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppConsistencyCheckEnd
	#define EXT_AppConsistencyCheckEnd
	#define GET_AppConsistencyCheckEnd(fl)  CAL_CMGETAPI( "AppConsistencyCheckEnd" ) 
	#define CAL_AppConsistencyCheckEnd  AppConsistencyCheckEnd
	#define CHK_AppConsistencyCheckEnd  TRUE
	#define EXP_AppConsistencyCheckEnd  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppConsistencyCheckEnd", (RTS_UINTPTR)AppConsistencyCheckEnd, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppConsistencyCheckEnd
	#define EXT_CmpAppAppConsistencyCheckEnd
	#define GET_CmpAppAppConsistencyCheckEnd  ERR_OK
	#define CAL_CmpAppAppConsistencyCheckEnd pICmpApp->IAppConsistencyCheckEnd
	#define CHK_CmpAppAppConsistencyCheckEnd (pICmpApp != NULL)
	#define EXP_CmpAppAppConsistencyCheckEnd  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppConsistencyCheckEnd
	#define EXT_AppConsistencyCheckEnd
	#define GET_AppConsistencyCheckEnd(fl)  CAL_CMGETAPI( "AppConsistencyCheckEnd" ) 
	#define CAL_AppConsistencyCheckEnd pICmpApp->IAppConsistencyCheckEnd
	#define CHK_AppConsistencyCheckEnd (pICmpApp != NULL)
	#define EXP_AppConsistencyCheckEnd  CAL_CMEXPAPI( "AppConsistencyCheckEnd" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppConsistencyCheckEnd  PFAPPCONSISTENCYCHECKEND pfAppConsistencyCheckEnd;
	#define EXT_AppConsistencyCheckEnd  extern PFAPPCONSISTENCYCHECKEND pfAppConsistencyCheckEnd;
	#define GET_AppConsistencyCheckEnd(fl)  s_pfCMGetAPI2( "AppConsistencyCheckEnd", (RTS_VOID_FCTPTR *)&pfAppConsistencyCheckEnd, (fl), 0, 0)
	#define CAL_AppConsistencyCheckEnd  pfAppConsistencyCheckEnd
	#define CHK_AppConsistencyCheckEnd  (pfAppConsistencyCheckEnd != NULL)
	#define EXP_AppConsistencyCheckEnd  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppConsistencyCheckEnd", (RTS_UINTPTR)AppConsistencyCheckEnd, 0, 0) 
#endif




/**
 * <description>Check all applications for consistency, that are called with AppConsistencyCheckBegin()</description>
 * <result>ERR_OK: No task active during this consistency sequence,
 *		   ERR_FAILED: Any task of an application was active during this sequence</result>
 */
RTS_RESULT CDECL AppConsistencyCheckAll(void);
typedef RTS_RESULT (CDECL * PFAPPCONSISTENCYCHECKALL) (void);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPCONSISTENCYCHECKALL_NOTIMPLEMENTED)
	#define USE_AppConsistencyCheckAll
	#define EXT_AppConsistencyCheckAll
	#define GET_AppConsistencyCheckAll(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppConsistencyCheckAll()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppConsistencyCheckAll  FALSE
	#define EXP_AppConsistencyCheckAll  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppConsistencyCheckAll
	#define EXT_AppConsistencyCheckAll
	#define GET_AppConsistencyCheckAll(fl)  CAL_CMGETAPI( "AppConsistencyCheckAll" ) 
	#define CAL_AppConsistencyCheckAll  AppConsistencyCheckAll
	#define CHK_AppConsistencyCheckAll  TRUE
	#define EXP_AppConsistencyCheckAll  CAL_CMEXPAPI( "AppConsistencyCheckAll" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppConsistencyCheckAll
	#define EXT_AppConsistencyCheckAll
	#define GET_AppConsistencyCheckAll(fl)  CAL_CMGETAPI( "AppConsistencyCheckAll" ) 
	#define CAL_AppConsistencyCheckAll  AppConsistencyCheckAll
	#define CHK_AppConsistencyCheckAll  TRUE
	#define EXP_AppConsistencyCheckAll  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppConsistencyCheckAll", (RTS_UINTPTR)AppConsistencyCheckAll, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppConsistencyCheckAll
	#define EXT_CmpAppAppConsistencyCheckAll
	#define GET_CmpAppAppConsistencyCheckAll  ERR_OK
	#define CAL_CmpAppAppConsistencyCheckAll pICmpApp->IAppConsistencyCheckAll
	#define CHK_CmpAppAppConsistencyCheckAll (pICmpApp != NULL)
	#define EXP_CmpAppAppConsistencyCheckAll  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppConsistencyCheckAll
	#define EXT_AppConsistencyCheckAll
	#define GET_AppConsistencyCheckAll(fl)  CAL_CMGETAPI( "AppConsistencyCheckAll" ) 
	#define CAL_AppConsistencyCheckAll pICmpApp->IAppConsistencyCheckAll
	#define CHK_AppConsistencyCheckAll (pICmpApp != NULL)
	#define EXP_AppConsistencyCheckAll  CAL_CMEXPAPI( "AppConsistencyCheckAll" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppConsistencyCheckAll  PFAPPCONSISTENCYCHECKALL pfAppConsistencyCheckAll;
	#define EXT_AppConsistencyCheckAll  extern PFAPPCONSISTENCYCHECKALL pfAppConsistencyCheckAll;
	#define GET_AppConsistencyCheckAll(fl)  s_pfCMGetAPI2( "AppConsistencyCheckAll", (RTS_VOID_FCTPTR *)&pfAppConsistencyCheckAll, (fl), 0, 0)
	#define CAL_AppConsistencyCheckAll  pfAppConsistencyCheckAll
	#define CHK_AppConsistencyCheckAll  (pfAppConsistencyCheckAll != NULL)
	#define EXP_AppConsistencyCheckAll  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppConsistencyCheckAll", (RTS_UINTPTR)AppConsistencyCheckAll, 0, 0) 
#endif




/**
 * <description>Retrieves the application info of the first application</description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the first application</result>
 */
APPLICATION* CDECL AppGetFirstApp(RTS_RESULT *pResult);
typedef APPLICATION* (CDECL * PFAPPGETFIRSTAPP) (RTS_RESULT *pResult);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETFIRSTAPP_NOTIMPLEMENTED)
	#define USE_AppGetFirstApp
	#define EXT_AppGetFirstApp
	#define GET_AppGetFirstApp(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetFirstApp(p0)  (APPLICATION*)ERR_NOTIMPLEMENTED
	#define CHK_AppGetFirstApp  FALSE
	#define EXP_AppGetFirstApp  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetFirstApp
	#define EXT_AppGetFirstApp
	#define GET_AppGetFirstApp(fl)  CAL_CMGETAPI( "AppGetFirstApp" ) 
	#define CAL_AppGetFirstApp  AppGetFirstApp
	#define CHK_AppGetFirstApp  TRUE
	#define EXP_AppGetFirstApp  CAL_CMEXPAPI( "AppGetFirstApp" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetFirstApp
	#define EXT_AppGetFirstApp
	#define GET_AppGetFirstApp(fl)  CAL_CMGETAPI( "AppGetFirstApp" ) 
	#define CAL_AppGetFirstApp  AppGetFirstApp
	#define CHK_AppGetFirstApp  TRUE
	#define EXP_AppGetFirstApp  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetFirstApp", (RTS_UINTPTR)AppGetFirstApp, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetFirstApp
	#define EXT_CmpAppAppGetFirstApp
	#define GET_CmpAppAppGetFirstApp  ERR_OK
	#define CAL_CmpAppAppGetFirstApp pICmpApp->IAppGetFirstApp
	#define CHK_CmpAppAppGetFirstApp (pICmpApp != NULL)
	#define EXP_CmpAppAppGetFirstApp  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetFirstApp
	#define EXT_AppGetFirstApp
	#define GET_AppGetFirstApp(fl)  CAL_CMGETAPI( "AppGetFirstApp" ) 
	#define CAL_AppGetFirstApp pICmpApp->IAppGetFirstApp
	#define CHK_AppGetFirstApp (pICmpApp != NULL)
	#define EXP_AppGetFirstApp  CAL_CMEXPAPI( "AppGetFirstApp" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetFirstApp  PFAPPGETFIRSTAPP pfAppGetFirstApp;
	#define EXT_AppGetFirstApp  extern PFAPPGETFIRSTAPP pfAppGetFirstApp;
	#define GET_AppGetFirstApp(fl)  s_pfCMGetAPI2( "AppGetFirstApp", (RTS_VOID_FCTPTR *)&pfAppGetFirstApp, (fl), 0, 0)
	#define CAL_AppGetFirstApp  pfAppGetFirstApp
	#define CHK_AppGetFirstApp  (pfAppGetFirstApp != NULL)
	#define EXP_AppGetFirstApp  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetFirstApp", (RTS_UINTPTR)AppGetFirstApp, 0, 0) 
#endif




/**
 * <description>Retrieves the application info of the next application</description>
 * <param name="pAppPrev" type="IN">Pointer to the first application retrieved by the AppGetFirstApp()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the next application</result>
 */
APPLICATION* CDECL AppGetNextApp(APPLICATION *pAppPrev, RTS_RESULT *pResult);
typedef APPLICATION* (CDECL * PFAPPGETNEXTAPP) (APPLICATION *pAppPrev, RTS_RESULT *pResult);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETNEXTAPP_NOTIMPLEMENTED)
	#define USE_AppGetNextApp
	#define EXT_AppGetNextApp
	#define GET_AppGetNextApp(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetNextApp(p0,p1)  (APPLICATION*)ERR_NOTIMPLEMENTED
	#define CHK_AppGetNextApp  FALSE
	#define EXP_AppGetNextApp  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetNextApp
	#define EXT_AppGetNextApp
	#define GET_AppGetNextApp(fl)  CAL_CMGETAPI( "AppGetNextApp" ) 
	#define CAL_AppGetNextApp  AppGetNextApp
	#define CHK_AppGetNextApp  TRUE
	#define EXP_AppGetNextApp  CAL_CMEXPAPI( "AppGetNextApp" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetNextApp
	#define EXT_AppGetNextApp
	#define GET_AppGetNextApp(fl)  CAL_CMGETAPI( "AppGetNextApp" ) 
	#define CAL_AppGetNextApp  AppGetNextApp
	#define CHK_AppGetNextApp  TRUE
	#define EXP_AppGetNextApp  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetNextApp", (RTS_UINTPTR)AppGetNextApp, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetNextApp
	#define EXT_CmpAppAppGetNextApp
	#define GET_CmpAppAppGetNextApp  ERR_OK
	#define CAL_CmpAppAppGetNextApp pICmpApp->IAppGetNextApp
	#define CHK_CmpAppAppGetNextApp (pICmpApp != NULL)
	#define EXP_CmpAppAppGetNextApp  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetNextApp
	#define EXT_AppGetNextApp
	#define GET_AppGetNextApp(fl)  CAL_CMGETAPI( "AppGetNextApp" ) 
	#define CAL_AppGetNextApp pICmpApp->IAppGetNextApp
	#define CHK_AppGetNextApp (pICmpApp != NULL)
	#define EXP_AppGetNextApp  CAL_CMEXPAPI( "AppGetNextApp" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetNextApp  PFAPPGETNEXTAPP pfAppGetNextApp;
	#define EXT_AppGetNextApp  extern PFAPPGETNEXTAPP pfAppGetNextApp;
	#define GET_AppGetNextApp(fl)  s_pfCMGetAPI2( "AppGetNextApp", (RTS_VOID_FCTPTR *)&pfAppGetNextApp, (fl), 0, 0)
	#define CAL_AppGetNextApp  pfAppGetNextApp
	#define CHK_AppGetNextApp  (pfAppGetNextApp != NULL)
	#define EXP_AppGetNextApp  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetNextApp", (RTS_UINTPTR)AppGetNextApp, 0, 0) 
#endif




/**
 * <description>Stores the retains of an application in a file</description>
 * <param name="pApp" type="IN">Pointer to application</param>
 * <param name="pszFilename" type="OUT">Name of retain file</param>
 * <result>Error code</result>
 */
RTS_RESULT CDECL AppStoreRetainsInFile(APPLICATION *pApp, RTS_IEC_STRING* pszFileName);
typedef RTS_RESULT (CDECL * PFAPPSTORERETAINSINFILE) (APPLICATION *pApp, RTS_IEC_STRING* pszFileName);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPSTORERETAINSINFILE_NOTIMPLEMENTED)
	#define USE_AppStoreRetainsInFile
	#define EXT_AppStoreRetainsInFile
	#define GET_AppStoreRetainsInFile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppStoreRetainsInFile(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppStoreRetainsInFile  FALSE
	#define EXP_AppStoreRetainsInFile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppStoreRetainsInFile
	#define EXT_AppStoreRetainsInFile
	#define GET_AppStoreRetainsInFile(fl)  CAL_CMGETAPI( "AppStoreRetainsInFile" ) 
	#define CAL_AppStoreRetainsInFile  AppStoreRetainsInFile
	#define CHK_AppStoreRetainsInFile  TRUE
	#define EXP_AppStoreRetainsInFile  CAL_CMEXPAPI( "AppStoreRetainsInFile" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppStoreRetainsInFile
	#define EXT_AppStoreRetainsInFile
	#define GET_AppStoreRetainsInFile(fl)  CAL_CMGETAPI( "AppStoreRetainsInFile" ) 
	#define CAL_AppStoreRetainsInFile  AppStoreRetainsInFile
	#define CHK_AppStoreRetainsInFile  TRUE
	#define EXP_AppStoreRetainsInFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppStoreRetainsInFile", (RTS_UINTPTR)AppStoreRetainsInFile, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppStoreRetainsInFile
	#define EXT_CmpAppAppStoreRetainsInFile
	#define GET_CmpAppAppStoreRetainsInFile  ERR_OK
	#define CAL_CmpAppAppStoreRetainsInFile pICmpApp->IAppStoreRetainsInFile
	#define CHK_CmpAppAppStoreRetainsInFile (pICmpApp != NULL)
	#define EXP_CmpAppAppStoreRetainsInFile  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppStoreRetainsInFile
	#define EXT_AppStoreRetainsInFile
	#define GET_AppStoreRetainsInFile(fl)  CAL_CMGETAPI( "AppStoreRetainsInFile" ) 
	#define CAL_AppStoreRetainsInFile pICmpApp->IAppStoreRetainsInFile
	#define CHK_AppStoreRetainsInFile (pICmpApp != NULL)
	#define EXP_AppStoreRetainsInFile  CAL_CMEXPAPI( "AppStoreRetainsInFile" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppStoreRetainsInFile  PFAPPSTORERETAINSINFILE pfAppStoreRetainsInFile;
	#define EXT_AppStoreRetainsInFile  extern PFAPPSTORERETAINSINFILE pfAppStoreRetainsInFile;
	#define GET_AppStoreRetainsInFile(fl)  s_pfCMGetAPI2( "AppStoreRetainsInFile", (RTS_VOID_FCTPTR *)&pfAppStoreRetainsInFile, (fl), 0, 0)
	#define CAL_AppStoreRetainsInFile  pfAppStoreRetainsInFile
	#define CHK_AppStoreRetainsInFile  (pfAppStoreRetainsInFile != NULL)
	#define EXP_AppStoreRetainsInFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppStoreRetainsInFile", (RTS_UINTPTR)AppStoreRetainsInFile, 0, 0) 
#endif




/**
 * <description>Restores the retains of an application from a file</description>
 * <param name="pApp" type="IN">Pointer to application</param>
 * <param name="pszFilename" type="IN">Name of retain file</param>
 * <result>Error code</result>
 */
RTS_RESULT CDECL AppRestoreRetainsFromFile(APPLICATION *pApp, RTS_IEC_STRING* pszFileName);
typedef RTS_RESULT (CDECL * PFAPPRESTORERETAINSFROMFILE) (APPLICATION *pApp, RTS_IEC_STRING* pszFileName);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPRESTORERETAINSFROMFILE_NOTIMPLEMENTED)
	#define USE_AppRestoreRetainsFromFile
	#define EXT_AppRestoreRetainsFromFile
	#define GET_AppRestoreRetainsFromFile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppRestoreRetainsFromFile(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppRestoreRetainsFromFile  FALSE
	#define EXP_AppRestoreRetainsFromFile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppRestoreRetainsFromFile
	#define EXT_AppRestoreRetainsFromFile
	#define GET_AppRestoreRetainsFromFile(fl)  CAL_CMGETAPI( "AppRestoreRetainsFromFile" ) 
	#define CAL_AppRestoreRetainsFromFile  AppRestoreRetainsFromFile
	#define CHK_AppRestoreRetainsFromFile  TRUE
	#define EXP_AppRestoreRetainsFromFile  CAL_CMEXPAPI( "AppRestoreRetainsFromFile" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppRestoreRetainsFromFile
	#define EXT_AppRestoreRetainsFromFile
	#define GET_AppRestoreRetainsFromFile(fl)  CAL_CMGETAPI( "AppRestoreRetainsFromFile" ) 
	#define CAL_AppRestoreRetainsFromFile  AppRestoreRetainsFromFile
	#define CHK_AppRestoreRetainsFromFile  TRUE
	#define EXP_AppRestoreRetainsFromFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppRestoreRetainsFromFile", (RTS_UINTPTR)AppRestoreRetainsFromFile, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppRestoreRetainsFromFile
	#define EXT_CmpAppAppRestoreRetainsFromFile
	#define GET_CmpAppAppRestoreRetainsFromFile  ERR_OK
	#define CAL_CmpAppAppRestoreRetainsFromFile pICmpApp->IAppRestoreRetainsFromFile
	#define CHK_CmpAppAppRestoreRetainsFromFile (pICmpApp != NULL)
	#define EXP_CmpAppAppRestoreRetainsFromFile  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppRestoreRetainsFromFile
	#define EXT_AppRestoreRetainsFromFile
	#define GET_AppRestoreRetainsFromFile(fl)  CAL_CMGETAPI( "AppRestoreRetainsFromFile" ) 
	#define CAL_AppRestoreRetainsFromFile pICmpApp->IAppRestoreRetainsFromFile
	#define CHK_AppRestoreRetainsFromFile (pICmpApp != NULL)
	#define EXP_AppRestoreRetainsFromFile  CAL_CMEXPAPI( "AppRestoreRetainsFromFile" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppRestoreRetainsFromFile  PFAPPRESTORERETAINSFROMFILE pfAppRestoreRetainsFromFile;
	#define EXT_AppRestoreRetainsFromFile  extern PFAPPRESTORERETAINSFROMFILE pfAppRestoreRetainsFromFile;
	#define GET_AppRestoreRetainsFromFile(fl)  s_pfCMGetAPI2( "AppRestoreRetainsFromFile", (RTS_VOID_FCTPTR *)&pfAppRestoreRetainsFromFile, (fl), 0, 0)
	#define CAL_AppRestoreRetainsFromFile  pfAppRestoreRetainsFromFile
	#define CHK_AppRestoreRetainsFromFile  (pfAppRestoreRetainsFromFile != NULL)
	#define EXP_AppRestoreRetainsFromFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppRestoreRetainsFromFile", (RTS_UINTPTR)AppRestoreRetainsFromFile, 0, 0) 
#endif




/**
 * <description>Restores the retains of an application from a file</description>
 * <param name="pApp" type="IN">Pointer to application</param>
 * <param name="pszFilename" type="IN">Name of retain file</param>
 * <param name="bGenerateException" type="IN">Select behaviour on retain mismatch: 1=Generate exception, 0=Only return error code</param>
 * <result>Error code</result>
 */
RTS_RESULT CDECL AppRestoreRetainsFromFile2(APPLICATION *pApp, RTS_IEC_STRING* pszFileName, int bGenerateException);
typedef RTS_RESULT (CDECL * PFAPPRESTORERETAINSFROMFILE2) (APPLICATION *pApp, RTS_IEC_STRING* pszFileName, int bGenerateException);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPRESTORERETAINSFROMFILE2_NOTIMPLEMENTED)
	#define USE_AppRestoreRetainsFromFile2
	#define EXT_AppRestoreRetainsFromFile2
	#define GET_AppRestoreRetainsFromFile2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppRestoreRetainsFromFile2(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppRestoreRetainsFromFile2  FALSE
	#define EXP_AppRestoreRetainsFromFile2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppRestoreRetainsFromFile2
	#define EXT_AppRestoreRetainsFromFile2
	#define GET_AppRestoreRetainsFromFile2(fl)  CAL_CMGETAPI( "AppRestoreRetainsFromFile2" ) 
	#define CAL_AppRestoreRetainsFromFile2  AppRestoreRetainsFromFile2
	#define CHK_AppRestoreRetainsFromFile2  TRUE
	#define EXP_AppRestoreRetainsFromFile2  CAL_CMEXPAPI( "AppRestoreRetainsFromFile2" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppRestoreRetainsFromFile2
	#define EXT_AppRestoreRetainsFromFile2
	#define GET_AppRestoreRetainsFromFile2(fl)  CAL_CMGETAPI( "AppRestoreRetainsFromFile2" ) 
	#define CAL_AppRestoreRetainsFromFile2  AppRestoreRetainsFromFile2
	#define CHK_AppRestoreRetainsFromFile2  TRUE
	#define EXP_AppRestoreRetainsFromFile2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppRestoreRetainsFromFile2", (RTS_UINTPTR)AppRestoreRetainsFromFile2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppRestoreRetainsFromFile2
	#define EXT_CmpAppAppRestoreRetainsFromFile2
	#define GET_CmpAppAppRestoreRetainsFromFile2  ERR_OK
	#define CAL_CmpAppAppRestoreRetainsFromFile2 pICmpApp->IAppRestoreRetainsFromFile2
	#define CHK_CmpAppAppRestoreRetainsFromFile2 (pICmpApp != NULL)
	#define EXP_CmpAppAppRestoreRetainsFromFile2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppRestoreRetainsFromFile2
	#define EXT_AppRestoreRetainsFromFile2
	#define GET_AppRestoreRetainsFromFile2(fl)  CAL_CMGETAPI( "AppRestoreRetainsFromFile2" ) 
	#define CAL_AppRestoreRetainsFromFile2 pICmpApp->IAppRestoreRetainsFromFile2
	#define CHK_AppRestoreRetainsFromFile2 (pICmpApp != NULL)
	#define EXP_AppRestoreRetainsFromFile2  CAL_CMEXPAPI( "AppRestoreRetainsFromFile2" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppRestoreRetainsFromFile2  PFAPPRESTORERETAINSFROMFILE2 pfAppRestoreRetainsFromFile2;
	#define EXT_AppRestoreRetainsFromFile2  extern PFAPPRESTORERETAINSFROMFILE2 pfAppRestoreRetainsFromFile2;
	#define GET_AppRestoreRetainsFromFile2(fl)  s_pfCMGetAPI2( "AppRestoreRetainsFromFile2", (RTS_VOID_FCTPTR *)&pfAppRestoreRetainsFromFile2, (fl), 0, 0)
	#define CAL_AppRestoreRetainsFromFile2  pfAppRestoreRetainsFromFile2
	#define CHK_AppRestoreRetainsFromFile2  (pfAppRestoreRetainsFromFile2 != NULL)
	#define EXP_AppRestoreRetainsFromFile2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppRestoreRetainsFromFile2", (RTS_UINTPTR)AppRestoreRetainsFromFile2, 0, 0) 
#endif




/**
 * <description>Store retain areas the standard way for the next reboot or reload</description>
 * <param name="pApp" type="IN">Pointer to application</param>
 * <result>Error code</result>
 */
RTS_RESULT CDECL AppSaveRetainAreas(APPLICATION *pApp);
typedef RTS_RESULT (CDECL * PFAPPSAVERETAINAREAS) (APPLICATION *pApp);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPSAVERETAINAREAS_NOTIMPLEMENTED)
	#define USE_AppSaveRetainAreas
	#define EXT_AppSaveRetainAreas
	#define GET_AppSaveRetainAreas(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppSaveRetainAreas(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppSaveRetainAreas  FALSE
	#define EXP_AppSaveRetainAreas  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppSaveRetainAreas
	#define EXT_AppSaveRetainAreas
	#define GET_AppSaveRetainAreas(fl)  CAL_CMGETAPI( "AppSaveRetainAreas" ) 
	#define CAL_AppSaveRetainAreas  AppSaveRetainAreas
	#define CHK_AppSaveRetainAreas  TRUE
	#define EXP_AppSaveRetainAreas  CAL_CMEXPAPI( "AppSaveRetainAreas" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppSaveRetainAreas
	#define EXT_AppSaveRetainAreas
	#define GET_AppSaveRetainAreas(fl)  CAL_CMGETAPI( "AppSaveRetainAreas" ) 
	#define CAL_AppSaveRetainAreas  AppSaveRetainAreas
	#define CHK_AppSaveRetainAreas  TRUE
	#define EXP_AppSaveRetainAreas  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppSaveRetainAreas", (RTS_UINTPTR)AppSaveRetainAreas, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppSaveRetainAreas
	#define EXT_CmpAppAppSaveRetainAreas
	#define GET_CmpAppAppSaveRetainAreas  ERR_OK
	#define CAL_CmpAppAppSaveRetainAreas pICmpApp->IAppSaveRetainAreas
	#define CHK_CmpAppAppSaveRetainAreas (pICmpApp != NULL)
	#define EXP_CmpAppAppSaveRetainAreas  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppSaveRetainAreas
	#define EXT_AppSaveRetainAreas
	#define GET_AppSaveRetainAreas(fl)  CAL_CMGETAPI( "AppSaveRetainAreas" ) 
	#define CAL_AppSaveRetainAreas pICmpApp->IAppSaveRetainAreas
	#define CHK_AppSaveRetainAreas (pICmpApp != NULL)
	#define EXP_AppSaveRetainAreas  CAL_CMEXPAPI( "AppSaveRetainAreas" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppSaveRetainAreas  PFAPPSAVERETAINAREAS pfAppSaveRetainAreas;
	#define EXT_AppSaveRetainAreas  extern PFAPPSAVERETAINAREAS pfAppSaveRetainAreas;
	#define GET_AppSaveRetainAreas(fl)  s_pfCMGetAPI2( "AppSaveRetainAreas", (RTS_VOID_FCTPTR *)&pfAppSaveRetainAreas, (fl), 0, 0)
	#define CAL_AppSaveRetainAreas  pfAppSaveRetainAreas
	#define CHK_AppSaveRetainAreas  (pfAppSaveRetainAreas != NULL)
	#define EXP_AppSaveRetainAreas  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppSaveRetainAreas", (RTS_UINTPTR)AppSaveRetainAreas, 0, 0) 
#endif




/**
 * <description>Store retain areas the standard way for the next reboot or reload of all applications</description>
 * <result>Error code</result>
 */
RTS_RESULT CDECL AppSaveAllRetainAreas(void);
typedef RTS_RESULT (CDECL * PFAPPSAVEALLRETAINAREAS) (void);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPSAVEALLRETAINAREAS_NOTIMPLEMENTED)
	#define USE_AppSaveAllRetainAreas
	#define EXT_AppSaveAllRetainAreas
	#define GET_AppSaveAllRetainAreas(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppSaveAllRetainAreas()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppSaveAllRetainAreas  FALSE
	#define EXP_AppSaveAllRetainAreas  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppSaveAllRetainAreas
	#define EXT_AppSaveAllRetainAreas
	#define GET_AppSaveAllRetainAreas(fl)  CAL_CMGETAPI( "AppSaveAllRetainAreas" ) 
	#define CAL_AppSaveAllRetainAreas  AppSaveAllRetainAreas
	#define CHK_AppSaveAllRetainAreas  TRUE
	#define EXP_AppSaveAllRetainAreas  CAL_CMEXPAPI( "AppSaveAllRetainAreas" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppSaveAllRetainAreas
	#define EXT_AppSaveAllRetainAreas
	#define GET_AppSaveAllRetainAreas(fl)  CAL_CMGETAPI( "AppSaveAllRetainAreas" ) 
	#define CAL_AppSaveAllRetainAreas  AppSaveAllRetainAreas
	#define CHK_AppSaveAllRetainAreas  TRUE
	#define EXP_AppSaveAllRetainAreas  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppSaveAllRetainAreas", (RTS_UINTPTR)AppSaveAllRetainAreas, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppSaveAllRetainAreas
	#define EXT_CmpAppAppSaveAllRetainAreas
	#define GET_CmpAppAppSaveAllRetainAreas  ERR_OK
	#define CAL_CmpAppAppSaveAllRetainAreas pICmpApp->IAppSaveAllRetainAreas
	#define CHK_CmpAppAppSaveAllRetainAreas (pICmpApp != NULL)
	#define EXP_CmpAppAppSaveAllRetainAreas  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppSaveAllRetainAreas
	#define EXT_AppSaveAllRetainAreas
	#define GET_AppSaveAllRetainAreas(fl)  CAL_CMGETAPI( "AppSaveAllRetainAreas" ) 
	#define CAL_AppSaveAllRetainAreas pICmpApp->IAppSaveAllRetainAreas
	#define CHK_AppSaveAllRetainAreas (pICmpApp != NULL)
	#define EXP_AppSaveAllRetainAreas  CAL_CMEXPAPI( "AppSaveAllRetainAreas" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppSaveAllRetainAreas  PFAPPSAVEALLRETAINAREAS pfAppSaveAllRetainAreas;
	#define EXT_AppSaveAllRetainAreas  extern PFAPPSAVEALLRETAINAREAS pfAppSaveAllRetainAreas;
	#define GET_AppSaveAllRetainAreas(fl)  s_pfCMGetAPI2( "AppSaveAllRetainAreas", (RTS_VOID_FCTPTR *)&pfAppSaveAllRetainAreas, (fl), 0, 0)
	#define CAL_AppSaveAllRetainAreas  pfAppSaveAllRetainAreas
	#define CHK_AppSaveAllRetainAreas  (pfAppSaveAllRetainAreas != NULL)
	#define EXP_AppSaveAllRetainAreas  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppSaveAllRetainAreas", (RTS_UINTPTR)AppSaveAllRetainAreas, 0, 0) 
#endif




/**
 * <description>Restore retain areas the standard way</description>
 * <param name="pApp" type="IN">Pointer to application</param>
 * <result>Error code</result>
 */
RTS_RESULT CDECL AppRestoreRetainAreas(APPLICATION *pApp);
typedef RTS_RESULT (CDECL * PFAPPRESTORERETAINAREAS) (APPLICATION *pApp);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPRESTORERETAINAREAS_NOTIMPLEMENTED)
	#define USE_AppRestoreRetainAreas
	#define EXT_AppRestoreRetainAreas
	#define GET_AppRestoreRetainAreas(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppRestoreRetainAreas(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppRestoreRetainAreas  FALSE
	#define EXP_AppRestoreRetainAreas  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppRestoreRetainAreas
	#define EXT_AppRestoreRetainAreas
	#define GET_AppRestoreRetainAreas(fl)  CAL_CMGETAPI( "AppRestoreRetainAreas" ) 
	#define CAL_AppRestoreRetainAreas  AppRestoreRetainAreas
	#define CHK_AppRestoreRetainAreas  TRUE
	#define EXP_AppRestoreRetainAreas  CAL_CMEXPAPI( "AppRestoreRetainAreas" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppRestoreRetainAreas
	#define EXT_AppRestoreRetainAreas
	#define GET_AppRestoreRetainAreas(fl)  CAL_CMGETAPI( "AppRestoreRetainAreas" ) 
	#define CAL_AppRestoreRetainAreas  AppRestoreRetainAreas
	#define CHK_AppRestoreRetainAreas  TRUE
	#define EXP_AppRestoreRetainAreas  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppRestoreRetainAreas", (RTS_UINTPTR)AppRestoreRetainAreas, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppRestoreRetainAreas
	#define EXT_CmpAppAppRestoreRetainAreas
	#define GET_CmpAppAppRestoreRetainAreas  ERR_OK
	#define CAL_CmpAppAppRestoreRetainAreas pICmpApp->IAppRestoreRetainAreas
	#define CHK_CmpAppAppRestoreRetainAreas (pICmpApp != NULL)
	#define EXP_CmpAppAppRestoreRetainAreas  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppRestoreRetainAreas
	#define EXT_AppRestoreRetainAreas
	#define GET_AppRestoreRetainAreas(fl)  CAL_CMGETAPI( "AppRestoreRetainAreas" ) 
	#define CAL_AppRestoreRetainAreas pICmpApp->IAppRestoreRetainAreas
	#define CHK_AppRestoreRetainAreas (pICmpApp != NULL)
	#define EXP_AppRestoreRetainAreas  CAL_CMEXPAPI( "AppRestoreRetainAreas" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppRestoreRetainAreas  PFAPPRESTORERETAINAREAS pfAppRestoreRetainAreas;
	#define EXT_AppRestoreRetainAreas  extern PFAPPRESTORERETAINAREAS pfAppRestoreRetainAreas;
	#define GET_AppRestoreRetainAreas(fl)  s_pfCMGetAPI2( "AppRestoreRetainAreas", (RTS_VOID_FCTPTR *)&pfAppRestoreRetainAreas, (fl), 0, 0)
	#define CAL_AppRestoreRetainAreas  pfAppRestoreRetainAreas
	#define CHK_AppRestoreRetainAreas  (pfAppRestoreRetainAreas != NULL)
	#define EXP_AppRestoreRetainAreas  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppRestoreRetainAreas", (RTS_UINTPTR)AppRestoreRetainAreas, 0, 0) 
#endif




/**
 * <description>This function retuns the size of an application area</description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="usType" type="IN">Area type. See category "Area Types" in SysMemItf.h.</param>
 * <param name="pResult" type="OUT">Pointer to Result</param>
 * <result>Area size</result>
 */
RTS_SIZE CDECL AppGetAreaSize(APPLICATION* pApp, RTS_UI16 usType, RTS_RESULT* pResult);
typedef RTS_SIZE (CDECL * PFAPPGETAREASIZE) (APPLICATION* pApp, RTS_UI16 usType, RTS_RESULT* pResult);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETAREASIZE_NOTIMPLEMENTED)
	#define USE_AppGetAreaSize
	#define EXT_AppGetAreaSize
	#define GET_AppGetAreaSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetAreaSize(p0,p1,p2)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_AppGetAreaSize  FALSE
	#define EXP_AppGetAreaSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetAreaSize
	#define EXT_AppGetAreaSize
	#define GET_AppGetAreaSize(fl)  CAL_CMGETAPI( "AppGetAreaSize" ) 
	#define CAL_AppGetAreaSize  AppGetAreaSize
	#define CHK_AppGetAreaSize  TRUE
	#define EXP_AppGetAreaSize  CAL_CMEXPAPI( "AppGetAreaSize" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetAreaSize
	#define EXT_AppGetAreaSize
	#define GET_AppGetAreaSize(fl)  CAL_CMGETAPI( "AppGetAreaSize" ) 
	#define CAL_AppGetAreaSize  AppGetAreaSize
	#define CHK_AppGetAreaSize  TRUE
	#define EXP_AppGetAreaSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetAreaSize", (RTS_UINTPTR)AppGetAreaSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetAreaSize
	#define EXT_CmpAppAppGetAreaSize
	#define GET_CmpAppAppGetAreaSize  ERR_OK
	#define CAL_CmpAppAppGetAreaSize pICmpApp->IAppGetAreaSize
	#define CHK_CmpAppAppGetAreaSize (pICmpApp != NULL)
	#define EXP_CmpAppAppGetAreaSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetAreaSize
	#define EXT_AppGetAreaSize
	#define GET_AppGetAreaSize(fl)  CAL_CMGETAPI( "AppGetAreaSize" ) 
	#define CAL_AppGetAreaSize pICmpApp->IAppGetAreaSize
	#define CHK_AppGetAreaSize (pICmpApp != NULL)
	#define EXP_AppGetAreaSize  CAL_CMEXPAPI( "AppGetAreaSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetAreaSize  PFAPPGETAREASIZE pfAppGetAreaSize;
	#define EXT_AppGetAreaSize  extern PFAPPGETAREASIZE pfAppGetAreaSize;
	#define GET_AppGetAreaSize(fl)  s_pfCMGetAPI2( "AppGetAreaSize", (RTS_VOID_FCTPTR *)&pfAppGetAreaSize, (fl), 0, 0)
	#define CAL_AppGetAreaSize  pfAppGetAreaSize
	#define CHK_AppGetAreaSize  (pfAppGetAreaSize != NULL)
	#define EXP_AppGetAreaSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetAreaSize", (RTS_UINTPTR)AppGetAreaSize, 0, 0) 
#endif




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
RTS_UI8* CDECL AppGetAreaAddress(APPLICATION* pApp, RTS_UI16 usType, RTS_RESULT* pResult);
typedef RTS_UI8* (CDECL * PFAPPGETAREAADDRESS) (APPLICATION* pApp, RTS_UI16 usType, RTS_RESULT* pResult);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETAREAADDRESS_NOTIMPLEMENTED)
	#define USE_AppGetAreaAddress
	#define EXT_AppGetAreaAddress
	#define GET_AppGetAreaAddress(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetAreaAddress(p0,p1,p2)  (RTS_UI8*)ERR_NOTIMPLEMENTED
	#define CHK_AppGetAreaAddress  FALSE
	#define EXP_AppGetAreaAddress  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetAreaAddress
	#define EXT_AppGetAreaAddress
	#define GET_AppGetAreaAddress(fl)  CAL_CMGETAPI( "AppGetAreaAddress" ) 
	#define CAL_AppGetAreaAddress  AppGetAreaAddress
	#define CHK_AppGetAreaAddress  TRUE
	#define EXP_AppGetAreaAddress  CAL_CMEXPAPI( "AppGetAreaAddress" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetAreaAddress
	#define EXT_AppGetAreaAddress
	#define GET_AppGetAreaAddress(fl)  CAL_CMGETAPI( "AppGetAreaAddress" ) 
	#define CAL_AppGetAreaAddress  AppGetAreaAddress
	#define CHK_AppGetAreaAddress  TRUE
	#define EXP_AppGetAreaAddress  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetAreaAddress", (RTS_UINTPTR)AppGetAreaAddress, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetAreaAddress
	#define EXT_CmpAppAppGetAreaAddress
	#define GET_CmpAppAppGetAreaAddress  ERR_OK
	#define CAL_CmpAppAppGetAreaAddress pICmpApp->IAppGetAreaAddress
	#define CHK_CmpAppAppGetAreaAddress (pICmpApp != NULL)
	#define EXP_CmpAppAppGetAreaAddress  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetAreaAddress
	#define EXT_AppGetAreaAddress
	#define GET_AppGetAreaAddress(fl)  CAL_CMGETAPI( "AppGetAreaAddress" ) 
	#define CAL_AppGetAreaAddress pICmpApp->IAppGetAreaAddress
	#define CHK_AppGetAreaAddress (pICmpApp != NULL)
	#define EXP_AppGetAreaAddress  CAL_CMEXPAPI( "AppGetAreaAddress" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetAreaAddress  PFAPPGETAREAADDRESS pfAppGetAreaAddress;
	#define EXT_AppGetAreaAddress  extern PFAPPGETAREAADDRESS pfAppGetAreaAddress;
	#define GET_AppGetAreaAddress(fl)  s_pfCMGetAPI2( "AppGetAreaAddress", (RTS_VOID_FCTPTR *)&pfAppGetAreaAddress, (fl), 0, 0)
	#define CAL_AppGetAreaAddress  pfAppGetAreaAddress
	#define CHK_AppGetAreaAddress  (pfAppGetAreaAddress != NULL)
	#define EXP_AppGetAreaAddress  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetAreaAddress", (RTS_UINTPTR)AppGetAreaAddress, 0, 0) 
#endif




/**
 * <description>This function retuns the segment info specified by type</description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="usType" type="IN">Area type. See category "Area Types" in SysMemItf.h.</param>
 * <param name="pResult" type="OUT">Pointer to Result</param>
 * <result>Pointer to segment info</result>
 */
APP_MEMORY_SEGMENT * CDECL AppGetSegment(APPLICATION* pApp, RTS_UI16 usType, RTS_RESULT *pResult);
typedef APP_MEMORY_SEGMENT * (CDECL * PFAPPGETSEGMENT) (APPLICATION* pApp, RTS_UI16 usType, RTS_RESULT *pResult);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETSEGMENT_NOTIMPLEMENTED)
	#define USE_AppGetSegment
	#define EXT_AppGetSegment
	#define GET_AppGetSegment(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetSegment(p0,p1,p2)  (APP_MEMORY_SEGMENT *)ERR_NOTIMPLEMENTED
	#define CHK_AppGetSegment  FALSE
	#define EXP_AppGetSegment  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetSegment
	#define EXT_AppGetSegment
	#define GET_AppGetSegment(fl)  CAL_CMGETAPI( "AppGetSegment" ) 
	#define CAL_AppGetSegment  AppGetSegment
	#define CHK_AppGetSegment  TRUE
	#define EXP_AppGetSegment  CAL_CMEXPAPI( "AppGetSegment" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetSegment
	#define EXT_AppGetSegment
	#define GET_AppGetSegment(fl)  CAL_CMGETAPI( "AppGetSegment" ) 
	#define CAL_AppGetSegment  AppGetSegment
	#define CHK_AppGetSegment  TRUE
	#define EXP_AppGetSegment  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetSegment", (RTS_UINTPTR)AppGetSegment, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetSegment
	#define EXT_CmpAppAppGetSegment
	#define GET_CmpAppAppGetSegment  ERR_OK
	#define CAL_CmpAppAppGetSegment pICmpApp->IAppGetSegment
	#define CHK_CmpAppAppGetSegment (pICmpApp != NULL)
	#define EXP_CmpAppAppGetSegment  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetSegment
	#define EXT_AppGetSegment
	#define GET_AppGetSegment(fl)  CAL_CMGETAPI( "AppGetSegment" ) 
	#define CAL_AppGetSegment pICmpApp->IAppGetSegment
	#define CHK_AppGetSegment (pICmpApp != NULL)
	#define EXP_AppGetSegment  CAL_CMEXPAPI( "AppGetSegment" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetSegment  PFAPPGETSEGMENT pfAppGetSegment;
	#define EXT_AppGetSegment  extern PFAPPGETSEGMENT pfAppGetSegment;
	#define GET_AppGetSegment(fl)  s_pfCMGetAPI2( "AppGetSegment", (RTS_VOID_FCTPTR *)&pfAppGetSegment, (fl), 0, 0)
	#define CAL_AppGetSegment  pfAppGetSegment
	#define CHK_AppGetSegment  (pfAppGetSegment != NULL)
	#define EXP_AppGetSegment  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetSegment", (RTS_UINTPTR)AppGetSegment, 0, 0) 
#endif




/**
 * <description>This function retuns the segment info specified by address</description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="pAddress" type="IN">Pointer to segment data</param>
 * <param name="pResult" type="OUT">Pointer to Result</param>
 * <result>Pointer to segment info</result>
 */
APP_MEMORY_SEGMENT * CDECL AppGetSegmentByAddress(APPLICATION* pApp, void *pAddress, RTS_RESULT *pResult);
typedef APP_MEMORY_SEGMENT * (CDECL * PFAPPGETSEGMENTBYADDRESS) (APPLICATION* pApp, void *pAddress, RTS_RESULT *pResult);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETSEGMENTBYADDRESS_NOTIMPLEMENTED)
	#define USE_AppGetSegmentByAddress
	#define EXT_AppGetSegmentByAddress
	#define GET_AppGetSegmentByAddress(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetSegmentByAddress(p0,p1,p2)  (APP_MEMORY_SEGMENT *)ERR_NOTIMPLEMENTED
	#define CHK_AppGetSegmentByAddress  FALSE
	#define EXP_AppGetSegmentByAddress  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetSegmentByAddress
	#define EXT_AppGetSegmentByAddress
	#define GET_AppGetSegmentByAddress(fl)  CAL_CMGETAPI( "AppGetSegmentByAddress" ) 
	#define CAL_AppGetSegmentByAddress  AppGetSegmentByAddress
	#define CHK_AppGetSegmentByAddress  TRUE
	#define EXP_AppGetSegmentByAddress  CAL_CMEXPAPI( "AppGetSegmentByAddress" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetSegmentByAddress
	#define EXT_AppGetSegmentByAddress
	#define GET_AppGetSegmentByAddress(fl)  CAL_CMGETAPI( "AppGetSegmentByAddress" ) 
	#define CAL_AppGetSegmentByAddress  AppGetSegmentByAddress
	#define CHK_AppGetSegmentByAddress  TRUE
	#define EXP_AppGetSegmentByAddress  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetSegmentByAddress", (RTS_UINTPTR)AppGetSegmentByAddress, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetSegmentByAddress
	#define EXT_CmpAppAppGetSegmentByAddress
	#define GET_CmpAppAppGetSegmentByAddress  ERR_OK
	#define CAL_CmpAppAppGetSegmentByAddress pICmpApp->IAppGetSegmentByAddress
	#define CHK_CmpAppAppGetSegmentByAddress (pICmpApp != NULL)
	#define EXP_CmpAppAppGetSegmentByAddress  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetSegmentByAddress
	#define EXT_AppGetSegmentByAddress
	#define GET_AppGetSegmentByAddress(fl)  CAL_CMGETAPI( "AppGetSegmentByAddress" ) 
	#define CAL_AppGetSegmentByAddress pICmpApp->IAppGetSegmentByAddress
	#define CHK_AppGetSegmentByAddress (pICmpApp != NULL)
	#define EXP_AppGetSegmentByAddress  CAL_CMEXPAPI( "AppGetSegmentByAddress" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetSegmentByAddress  PFAPPGETSEGMENTBYADDRESS pfAppGetSegmentByAddress;
	#define EXT_AppGetSegmentByAddress  extern PFAPPGETSEGMENTBYADDRESS pfAppGetSegmentByAddress;
	#define GET_AppGetSegmentByAddress(fl)  s_pfCMGetAPI2( "AppGetSegmentByAddress", (RTS_VOID_FCTPTR *)&pfAppGetSegmentByAddress, (fl), 0, 0)
	#define CAL_AppGetSegmentByAddress  pfAppGetSegmentByAddress
	#define CHK_AppGetSegmentByAddress  (pfAppGetSegmentByAddress != NULL)
	#define EXP_AppGetSegmentByAddress  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetSegmentByAddress", (RTS_UINTPTR)AppGetSegmentByAddress, 0, 0) 
#endif




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
RTS_SIZE CDECL AppGetSegmentSize(APPLICATION* pApp, RTS_UI16 usType, RTS_RESULT* pResult);
typedef RTS_SIZE (CDECL * PFAPPGETSEGMENTSIZE) (APPLICATION* pApp, RTS_UI16 usType, RTS_RESULT* pResult);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETSEGMENTSIZE_NOTIMPLEMENTED)
	#define USE_AppGetSegmentSize
	#define EXT_AppGetSegmentSize
	#define GET_AppGetSegmentSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetSegmentSize(p0,p1,p2)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_AppGetSegmentSize  FALSE
	#define EXP_AppGetSegmentSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetSegmentSize
	#define EXT_AppGetSegmentSize
	#define GET_AppGetSegmentSize(fl)  CAL_CMGETAPI( "AppGetSegmentSize" ) 
	#define CAL_AppGetSegmentSize  AppGetSegmentSize
	#define CHK_AppGetSegmentSize  TRUE
	#define EXP_AppGetSegmentSize  CAL_CMEXPAPI( "AppGetSegmentSize" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetSegmentSize
	#define EXT_AppGetSegmentSize
	#define GET_AppGetSegmentSize(fl)  CAL_CMGETAPI( "AppGetSegmentSize" ) 
	#define CAL_AppGetSegmentSize  AppGetSegmentSize
	#define CHK_AppGetSegmentSize  TRUE
	#define EXP_AppGetSegmentSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetSegmentSize", (RTS_UINTPTR)AppGetSegmentSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetSegmentSize
	#define EXT_CmpAppAppGetSegmentSize
	#define GET_CmpAppAppGetSegmentSize  ERR_OK
	#define CAL_CmpAppAppGetSegmentSize pICmpApp->IAppGetSegmentSize
	#define CHK_CmpAppAppGetSegmentSize (pICmpApp != NULL)
	#define EXP_CmpAppAppGetSegmentSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetSegmentSize
	#define EXT_AppGetSegmentSize
	#define GET_AppGetSegmentSize(fl)  CAL_CMGETAPI( "AppGetSegmentSize" ) 
	#define CAL_AppGetSegmentSize pICmpApp->IAppGetSegmentSize
	#define CHK_AppGetSegmentSize (pICmpApp != NULL)
	#define EXP_AppGetSegmentSize  CAL_CMEXPAPI( "AppGetSegmentSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetSegmentSize  PFAPPGETSEGMENTSIZE pfAppGetSegmentSize;
	#define EXT_AppGetSegmentSize  extern PFAPPGETSEGMENTSIZE pfAppGetSegmentSize;
	#define GET_AppGetSegmentSize(fl)  s_pfCMGetAPI2( "AppGetSegmentSize", (RTS_VOID_FCTPTR *)&pfAppGetSegmentSize, (fl), 0, 0)
	#define CAL_AppGetSegmentSize  pfAppGetSegmentSize
	#define CHK_AppGetSegmentSize  (pfAppGetSegmentSize != NULL)
	#define EXP_AppGetSegmentSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetSegmentSize", (RTS_UINTPTR)AppGetSegmentSize, 0, 0) 
#endif




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
RTS_UI8 HUGEPTR * CDECL AppGetSegmentAddress(APPLICATION* pApp, RTS_UI16 usType, RTS_RESULT* pResult);
typedef RTS_UI8 HUGEPTR * (CDECL * PFAPPGETSEGMENTADDRESS) (APPLICATION* pApp, RTS_UI16 usType, RTS_RESULT* pResult);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETSEGMENTADDRESS_NOTIMPLEMENTED)
	#define USE_AppGetSegmentAddress
	#define EXT_AppGetSegmentAddress
	#define GET_AppGetSegmentAddress(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetSegmentAddress(p0,p1,p2)  (RTS_UI8 HUGEPTR *)ERR_NOTIMPLEMENTED
	#define CHK_AppGetSegmentAddress  FALSE
	#define EXP_AppGetSegmentAddress  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetSegmentAddress
	#define EXT_AppGetSegmentAddress
	#define GET_AppGetSegmentAddress(fl)  CAL_CMGETAPI( "AppGetSegmentAddress" ) 
	#define CAL_AppGetSegmentAddress  AppGetSegmentAddress
	#define CHK_AppGetSegmentAddress  TRUE
	#define EXP_AppGetSegmentAddress  CAL_CMEXPAPI( "AppGetSegmentAddress" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetSegmentAddress
	#define EXT_AppGetSegmentAddress
	#define GET_AppGetSegmentAddress(fl)  CAL_CMGETAPI( "AppGetSegmentAddress" ) 
	#define CAL_AppGetSegmentAddress  AppGetSegmentAddress
	#define CHK_AppGetSegmentAddress  TRUE
	#define EXP_AppGetSegmentAddress  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetSegmentAddress", (RTS_UINTPTR)AppGetSegmentAddress, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetSegmentAddress
	#define EXT_CmpAppAppGetSegmentAddress
	#define GET_CmpAppAppGetSegmentAddress  ERR_OK
	#define CAL_CmpAppAppGetSegmentAddress pICmpApp->IAppGetSegmentAddress
	#define CHK_CmpAppAppGetSegmentAddress (pICmpApp != NULL)
	#define EXP_CmpAppAppGetSegmentAddress  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetSegmentAddress
	#define EXT_AppGetSegmentAddress
	#define GET_AppGetSegmentAddress(fl)  CAL_CMGETAPI( "AppGetSegmentAddress" ) 
	#define CAL_AppGetSegmentAddress pICmpApp->IAppGetSegmentAddress
	#define CHK_AppGetSegmentAddress (pICmpApp != NULL)
	#define EXP_AppGetSegmentAddress  CAL_CMEXPAPI( "AppGetSegmentAddress" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetSegmentAddress  PFAPPGETSEGMENTADDRESS pfAppGetSegmentAddress;
	#define EXT_AppGetSegmentAddress  extern PFAPPGETSEGMENTADDRESS pfAppGetSegmentAddress;
	#define GET_AppGetSegmentAddress(fl)  s_pfCMGetAPI2( "AppGetSegmentAddress", (RTS_VOID_FCTPTR *)&pfAppGetSegmentAddress, (fl), 0, 0)
	#define CAL_AppGetSegmentAddress  pfAppGetSegmentAddress
	#define CHK_AppGetSegmentAddress  (pfAppGetSegmentAddress != NULL)
	#define EXP_AppGetSegmentAddress  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetSegmentAddress", (RTS_UINTPTR)AppGetSegmentAddress, 0, 0) 
#endif




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
RTS_RESULT CDECL AppRegisterPropAccessFunctions(APPLICATION* pApp, RTS_VOID_FCTPTR *ppfGetBooleanProperty, RTS_VOID_FCTPTR *ppfGetTextProperty, RTS_VOID_FCTPTR *ppfGetNumberProperty, RTS_VOID_FCTPTR *ppfGetVersionProperty);
typedef RTS_RESULT (CDECL * PFAPPREGISTERPROPACCESSFUNCTIONS) (APPLICATION* pApp, RTS_VOID_FCTPTR *ppfGetBooleanProperty, RTS_VOID_FCTPTR *ppfGetTextProperty, RTS_VOID_FCTPTR *ppfGetNumberProperty, RTS_VOID_FCTPTR *ppfGetVersionProperty);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPREGISTERPROPACCESSFUNCTIONS_NOTIMPLEMENTED)
	#define USE_AppRegisterPropAccessFunctions
	#define EXT_AppRegisterPropAccessFunctions
	#define GET_AppRegisterPropAccessFunctions(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppRegisterPropAccessFunctions(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppRegisterPropAccessFunctions  FALSE
	#define EXP_AppRegisterPropAccessFunctions  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppRegisterPropAccessFunctions
	#define EXT_AppRegisterPropAccessFunctions
	#define GET_AppRegisterPropAccessFunctions(fl)  CAL_CMGETAPI( "AppRegisterPropAccessFunctions" ) 
	#define CAL_AppRegisterPropAccessFunctions  AppRegisterPropAccessFunctions
	#define CHK_AppRegisterPropAccessFunctions  TRUE
	#define EXP_AppRegisterPropAccessFunctions  CAL_CMEXPAPI( "AppRegisterPropAccessFunctions" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppRegisterPropAccessFunctions
	#define EXT_AppRegisterPropAccessFunctions
	#define GET_AppRegisterPropAccessFunctions(fl)  CAL_CMGETAPI( "AppRegisterPropAccessFunctions" ) 
	#define CAL_AppRegisterPropAccessFunctions  AppRegisterPropAccessFunctions
	#define CHK_AppRegisterPropAccessFunctions  TRUE
	#define EXP_AppRegisterPropAccessFunctions  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppRegisterPropAccessFunctions", (RTS_UINTPTR)AppRegisterPropAccessFunctions, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppRegisterPropAccessFunctions
	#define EXT_CmpAppAppRegisterPropAccessFunctions
	#define GET_CmpAppAppRegisterPropAccessFunctions  ERR_OK
	#define CAL_CmpAppAppRegisterPropAccessFunctions pICmpApp->IAppRegisterPropAccessFunctions
	#define CHK_CmpAppAppRegisterPropAccessFunctions (pICmpApp != NULL)
	#define EXP_CmpAppAppRegisterPropAccessFunctions  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppRegisterPropAccessFunctions
	#define EXT_AppRegisterPropAccessFunctions
	#define GET_AppRegisterPropAccessFunctions(fl)  CAL_CMGETAPI( "AppRegisterPropAccessFunctions" ) 
	#define CAL_AppRegisterPropAccessFunctions pICmpApp->IAppRegisterPropAccessFunctions
	#define CHK_AppRegisterPropAccessFunctions (pICmpApp != NULL)
	#define EXP_AppRegisterPropAccessFunctions  CAL_CMEXPAPI( "AppRegisterPropAccessFunctions" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppRegisterPropAccessFunctions  PFAPPREGISTERPROPACCESSFUNCTIONS pfAppRegisterPropAccessFunctions;
	#define EXT_AppRegisterPropAccessFunctions  extern PFAPPREGISTERPROPACCESSFUNCTIONS pfAppRegisterPropAccessFunctions;
	#define GET_AppRegisterPropAccessFunctions(fl)  s_pfCMGetAPI2( "AppRegisterPropAccessFunctions", (RTS_VOID_FCTPTR *)&pfAppRegisterPropAccessFunctions, (fl), 0, 0)
	#define CAL_AppRegisterPropAccessFunctions  pfAppRegisterPropAccessFunctions
	#define CHK_AppRegisterPropAccessFunctions  (pfAppRegisterPropAccessFunctions != NULL)
	#define EXP_AppRegisterPropAccessFunctions  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppRegisterPropAccessFunctions", (RTS_UINTPTR)AppRegisterPropAccessFunctions, 0, 0) 
#endif




/**
 * <description>This function returns the project information</description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="pfGetBooleanProperty" type="IN">Pointer to PROJECT_INFORMATION</param>
 * <result>Error Code</result>
 */
RTS_RESULT CDECL AppGetProjectInformation(APPLICATION* pApp, PROJECT_INFO* pInfo);
typedef RTS_RESULT (CDECL * PFAPPGETPROJECTINFORMATION) (APPLICATION* pApp, PROJECT_INFO* pInfo);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETPROJECTINFORMATION_NOTIMPLEMENTED)
	#define USE_AppGetProjectInformation
	#define EXT_AppGetProjectInformation
	#define GET_AppGetProjectInformation(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetProjectInformation(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppGetProjectInformation  FALSE
	#define EXP_AppGetProjectInformation  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetProjectInformation
	#define EXT_AppGetProjectInformation
	#define GET_AppGetProjectInformation(fl)  CAL_CMGETAPI( "AppGetProjectInformation" ) 
	#define CAL_AppGetProjectInformation  AppGetProjectInformation
	#define CHK_AppGetProjectInformation  TRUE
	#define EXP_AppGetProjectInformation  CAL_CMEXPAPI( "AppGetProjectInformation" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetProjectInformation
	#define EXT_AppGetProjectInformation
	#define GET_AppGetProjectInformation(fl)  CAL_CMGETAPI( "AppGetProjectInformation" ) 
	#define CAL_AppGetProjectInformation  AppGetProjectInformation
	#define CHK_AppGetProjectInformation  TRUE
	#define EXP_AppGetProjectInformation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetProjectInformation", (RTS_UINTPTR)AppGetProjectInformation, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetProjectInformation
	#define EXT_CmpAppAppGetProjectInformation
	#define GET_CmpAppAppGetProjectInformation  ERR_OK
	#define CAL_CmpAppAppGetProjectInformation pICmpApp->IAppGetProjectInformation
	#define CHK_CmpAppAppGetProjectInformation (pICmpApp != NULL)
	#define EXP_CmpAppAppGetProjectInformation  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetProjectInformation
	#define EXT_AppGetProjectInformation
	#define GET_AppGetProjectInformation(fl)  CAL_CMGETAPI( "AppGetProjectInformation" ) 
	#define CAL_AppGetProjectInformation pICmpApp->IAppGetProjectInformation
	#define CHK_AppGetProjectInformation (pICmpApp != NULL)
	#define EXP_AppGetProjectInformation  CAL_CMEXPAPI( "AppGetProjectInformation" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetProjectInformation  PFAPPGETPROJECTINFORMATION pfAppGetProjectInformation;
	#define EXT_AppGetProjectInformation  extern PFAPPGETPROJECTINFORMATION pfAppGetProjectInformation;
	#define GET_AppGetProjectInformation(fl)  s_pfCMGetAPI2( "AppGetProjectInformation", (RTS_VOID_FCTPTR *)&pfAppGetProjectInformation, (fl), 0, 0)
	#define CAL_AppGetProjectInformation  pfAppGetProjectInformation
	#define CHK_AppGetProjectInformation  (pfAppGetProjectInformation != NULL)
	#define EXP_AppGetProjectInformation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetProjectInformation", (RTS_UINTPTR)AppGetProjectInformation, 0, 0) 
#endif




/**
 * <description>With this function you get access to the optional IEC function in the project, which contains boolean project infomration</description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="pBooleanProperty" type="INOUT">wszKey must be set with the key (RTS_IEC_WSTRING!), as defined in the project information dialog in CoDeSys.
 *	See category "Property keys" for predefined property keys.
 *	bBooleanProperty contains the bool property value.</param>
 * <result>Error Code</result>
 */
RTS_RESULT CDECL AppGetBooleanProperty(APPLICATION *pApp, BOOLEANPROPERTY *pBooleanProperty);
typedef RTS_RESULT (CDECL * PFAPPGETBOOLEANPROPERTY) (APPLICATION *pApp, BOOLEANPROPERTY *pBooleanProperty);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETBOOLEANPROPERTY_NOTIMPLEMENTED)
	#define USE_AppGetBooleanProperty
	#define EXT_AppGetBooleanProperty
	#define GET_AppGetBooleanProperty(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetBooleanProperty(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppGetBooleanProperty  FALSE
	#define EXP_AppGetBooleanProperty  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetBooleanProperty
	#define EXT_AppGetBooleanProperty
	#define GET_AppGetBooleanProperty(fl)  CAL_CMGETAPI( "AppGetBooleanProperty" ) 
	#define CAL_AppGetBooleanProperty  AppGetBooleanProperty
	#define CHK_AppGetBooleanProperty  TRUE
	#define EXP_AppGetBooleanProperty  CAL_CMEXPAPI( "AppGetBooleanProperty" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetBooleanProperty
	#define EXT_AppGetBooleanProperty
	#define GET_AppGetBooleanProperty(fl)  CAL_CMGETAPI( "AppGetBooleanProperty" ) 
	#define CAL_AppGetBooleanProperty  AppGetBooleanProperty
	#define CHK_AppGetBooleanProperty  TRUE
	#define EXP_AppGetBooleanProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetBooleanProperty", (RTS_UINTPTR)AppGetBooleanProperty, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetBooleanProperty
	#define EXT_CmpAppAppGetBooleanProperty
	#define GET_CmpAppAppGetBooleanProperty  ERR_OK
	#define CAL_CmpAppAppGetBooleanProperty pICmpApp->IAppGetBooleanProperty
	#define CHK_CmpAppAppGetBooleanProperty (pICmpApp != NULL)
	#define EXP_CmpAppAppGetBooleanProperty  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetBooleanProperty
	#define EXT_AppGetBooleanProperty
	#define GET_AppGetBooleanProperty(fl)  CAL_CMGETAPI( "AppGetBooleanProperty" ) 
	#define CAL_AppGetBooleanProperty pICmpApp->IAppGetBooleanProperty
	#define CHK_AppGetBooleanProperty (pICmpApp != NULL)
	#define EXP_AppGetBooleanProperty  CAL_CMEXPAPI( "AppGetBooleanProperty" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetBooleanProperty  PFAPPGETBOOLEANPROPERTY pfAppGetBooleanProperty;
	#define EXT_AppGetBooleanProperty  extern PFAPPGETBOOLEANPROPERTY pfAppGetBooleanProperty;
	#define GET_AppGetBooleanProperty(fl)  s_pfCMGetAPI2( "AppGetBooleanProperty", (RTS_VOID_FCTPTR *)&pfAppGetBooleanProperty, (fl), 0, 0)
	#define CAL_AppGetBooleanProperty  pfAppGetBooleanProperty
	#define CHK_AppGetBooleanProperty  (pfAppGetBooleanProperty != NULL)
	#define EXP_AppGetBooleanProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetBooleanProperty", (RTS_UINTPTR)AppGetBooleanProperty, 0, 0) 
#endif




/**
 * <description>With this function you get access to the optional IEC function in the project, which contains text project infomration</description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="pTextProperty" type="INOUT">wszKey must be set with the key (RTS_IEC_WSTRING!), as defined in the project information dialog in CoDeSys.
 *	See category "Property keys" for predefined property keys.
 *	wszTextProperty contains the string property value.</param>
 * <result>Error Code</result>
 */
RTS_RESULT CDECL AppGetTextProperty(APPLICATION *pApp, TEXTPROPERTY *pTextProperty);
typedef RTS_RESULT (CDECL * PFAPPGETTEXTPROPERTY) (APPLICATION *pApp, TEXTPROPERTY *pTextProperty);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETTEXTPROPERTY_NOTIMPLEMENTED)
	#define USE_AppGetTextProperty
	#define EXT_AppGetTextProperty
	#define GET_AppGetTextProperty(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetTextProperty(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppGetTextProperty  FALSE
	#define EXP_AppGetTextProperty  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetTextProperty
	#define EXT_AppGetTextProperty
	#define GET_AppGetTextProperty(fl)  CAL_CMGETAPI( "AppGetTextProperty" ) 
	#define CAL_AppGetTextProperty  AppGetTextProperty
	#define CHK_AppGetTextProperty  TRUE
	#define EXP_AppGetTextProperty  CAL_CMEXPAPI( "AppGetTextProperty" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetTextProperty
	#define EXT_AppGetTextProperty
	#define GET_AppGetTextProperty(fl)  CAL_CMGETAPI( "AppGetTextProperty" ) 
	#define CAL_AppGetTextProperty  AppGetTextProperty
	#define CHK_AppGetTextProperty  TRUE
	#define EXP_AppGetTextProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetTextProperty", (RTS_UINTPTR)AppGetTextProperty, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetTextProperty
	#define EXT_CmpAppAppGetTextProperty
	#define GET_CmpAppAppGetTextProperty  ERR_OK
	#define CAL_CmpAppAppGetTextProperty pICmpApp->IAppGetTextProperty
	#define CHK_CmpAppAppGetTextProperty (pICmpApp != NULL)
	#define EXP_CmpAppAppGetTextProperty  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetTextProperty
	#define EXT_AppGetTextProperty
	#define GET_AppGetTextProperty(fl)  CAL_CMGETAPI( "AppGetTextProperty" ) 
	#define CAL_AppGetTextProperty pICmpApp->IAppGetTextProperty
	#define CHK_AppGetTextProperty (pICmpApp != NULL)
	#define EXP_AppGetTextProperty  CAL_CMEXPAPI( "AppGetTextProperty" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetTextProperty  PFAPPGETTEXTPROPERTY pfAppGetTextProperty;
	#define EXT_AppGetTextProperty  extern PFAPPGETTEXTPROPERTY pfAppGetTextProperty;
	#define GET_AppGetTextProperty(fl)  s_pfCMGetAPI2( "AppGetTextProperty", (RTS_VOID_FCTPTR *)&pfAppGetTextProperty, (fl), 0, 0)
	#define CAL_AppGetTextProperty  pfAppGetTextProperty
	#define CHK_AppGetTextProperty  (pfAppGetTextProperty != NULL)
	#define EXP_AppGetTextProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetTextProperty", (RTS_UINTPTR)AppGetTextProperty, 0, 0) 
#endif




/**
 * <description>With this function you get access to the optional IEC function in the project, which contains text project infomration</description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="pNumberProperty" type="INOUT">wszKey must be set with the key (RTS_IEC_WSTRING!), as defined in the project information dialog in CoDeSys.
 *	See category "Property keys" for predefined property keys.
 *	udiNumberProperty contains the number property value.</param>
 * <result>Error Code</result>
 */
RTS_RESULT CDECL AppGetNumberProperty(APPLICATION *pApp, NUMBERPROPERTY *pNumberProperty);
typedef RTS_RESULT (CDECL * PFAPPGETNUMBERPROPERTY) (APPLICATION *pApp, NUMBERPROPERTY *pNumberProperty);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETNUMBERPROPERTY_NOTIMPLEMENTED)
	#define USE_AppGetNumberProperty
	#define EXT_AppGetNumberProperty
	#define GET_AppGetNumberProperty(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetNumberProperty(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppGetNumberProperty  FALSE
	#define EXP_AppGetNumberProperty  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetNumberProperty
	#define EXT_AppGetNumberProperty
	#define GET_AppGetNumberProperty(fl)  CAL_CMGETAPI( "AppGetNumberProperty" ) 
	#define CAL_AppGetNumberProperty  AppGetNumberProperty
	#define CHK_AppGetNumberProperty  TRUE
	#define EXP_AppGetNumberProperty  CAL_CMEXPAPI( "AppGetNumberProperty" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetNumberProperty
	#define EXT_AppGetNumberProperty
	#define GET_AppGetNumberProperty(fl)  CAL_CMGETAPI( "AppGetNumberProperty" ) 
	#define CAL_AppGetNumberProperty  AppGetNumberProperty
	#define CHK_AppGetNumberProperty  TRUE
	#define EXP_AppGetNumberProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetNumberProperty", (RTS_UINTPTR)AppGetNumberProperty, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetNumberProperty
	#define EXT_CmpAppAppGetNumberProperty
	#define GET_CmpAppAppGetNumberProperty  ERR_OK
	#define CAL_CmpAppAppGetNumberProperty pICmpApp->IAppGetNumberProperty
	#define CHK_CmpAppAppGetNumberProperty (pICmpApp != NULL)
	#define EXP_CmpAppAppGetNumberProperty  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetNumberProperty
	#define EXT_AppGetNumberProperty
	#define GET_AppGetNumberProperty(fl)  CAL_CMGETAPI( "AppGetNumberProperty" ) 
	#define CAL_AppGetNumberProperty pICmpApp->IAppGetNumberProperty
	#define CHK_AppGetNumberProperty (pICmpApp != NULL)
	#define EXP_AppGetNumberProperty  CAL_CMEXPAPI( "AppGetNumberProperty" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetNumberProperty  PFAPPGETNUMBERPROPERTY pfAppGetNumberProperty;
	#define EXT_AppGetNumberProperty  extern PFAPPGETNUMBERPROPERTY pfAppGetNumberProperty;
	#define GET_AppGetNumberProperty(fl)  s_pfCMGetAPI2( "AppGetNumberProperty", (RTS_VOID_FCTPTR *)&pfAppGetNumberProperty, (fl), 0, 0)
	#define CAL_AppGetNumberProperty  pfAppGetNumberProperty
	#define CHK_AppGetNumberProperty  (pfAppGetNumberProperty != NULL)
	#define EXP_AppGetNumberProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetNumberProperty", (RTS_UINTPTR)AppGetNumberProperty, 0, 0) 
#endif




/**
 * <description>With this function you get access to the optional IEC function in the project, which contains text project infomration</description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="pVersionProperty" type="INOUT">wszKey must be set with the key (RTS_IEC_WSTRING!), as defined in the project information dialog in CoDeSys.
 *	See category "Property keys" for predefined property keys.
 *	uiMajor, uiMinor, uiServicePack, uiPatch contains the version property values.</param>
 * <result>Error Code</result>
 */
RTS_RESULT CDECL AppGetVersionProperty(APPLICATION *pApp, VERSIONPROPERTY *pVersionProperty);
typedef RTS_RESULT (CDECL * PFAPPGETVERSIONPROPERTY) (APPLICATION *pApp, VERSIONPROPERTY *pVersionProperty);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETVERSIONPROPERTY_NOTIMPLEMENTED)
	#define USE_AppGetVersionProperty
	#define EXT_AppGetVersionProperty
	#define GET_AppGetVersionProperty(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetVersionProperty(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppGetVersionProperty  FALSE
	#define EXP_AppGetVersionProperty  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetVersionProperty
	#define EXT_AppGetVersionProperty
	#define GET_AppGetVersionProperty(fl)  CAL_CMGETAPI( "AppGetVersionProperty" ) 
	#define CAL_AppGetVersionProperty  AppGetVersionProperty
	#define CHK_AppGetVersionProperty  TRUE
	#define EXP_AppGetVersionProperty  CAL_CMEXPAPI( "AppGetVersionProperty" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetVersionProperty
	#define EXT_AppGetVersionProperty
	#define GET_AppGetVersionProperty(fl)  CAL_CMGETAPI( "AppGetVersionProperty" ) 
	#define CAL_AppGetVersionProperty  AppGetVersionProperty
	#define CHK_AppGetVersionProperty  TRUE
	#define EXP_AppGetVersionProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetVersionProperty", (RTS_UINTPTR)AppGetVersionProperty, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetVersionProperty
	#define EXT_CmpAppAppGetVersionProperty
	#define GET_CmpAppAppGetVersionProperty  ERR_OK
	#define CAL_CmpAppAppGetVersionProperty pICmpApp->IAppGetVersionProperty
	#define CHK_CmpAppAppGetVersionProperty (pICmpApp != NULL)
	#define EXP_CmpAppAppGetVersionProperty  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetVersionProperty
	#define EXT_AppGetVersionProperty
	#define GET_AppGetVersionProperty(fl)  CAL_CMGETAPI( "AppGetVersionProperty" ) 
	#define CAL_AppGetVersionProperty pICmpApp->IAppGetVersionProperty
	#define CHK_AppGetVersionProperty (pICmpApp != NULL)
	#define EXP_AppGetVersionProperty  CAL_CMEXPAPI( "AppGetVersionProperty" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetVersionProperty  PFAPPGETVERSIONPROPERTY pfAppGetVersionProperty;
	#define EXT_AppGetVersionProperty  extern PFAPPGETVERSIONPROPERTY pfAppGetVersionProperty;
	#define GET_AppGetVersionProperty(fl)  s_pfCMGetAPI2( "AppGetVersionProperty", (RTS_VOID_FCTPTR *)&pfAppGetVersionProperty, (fl), 0, 0)
	#define CAL_AppGetVersionProperty  pfAppGetVersionProperty
	#define CHK_AppGetVersionProperty  (pfAppGetVersionProperty != NULL)
	#define EXP_AppGetVersionProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetVersionProperty", (RTS_UINTPTR)AppGetVersionProperty, 0, 0) 
#endif




/**
 * <description>Get the current application, in which task context the caller is located</description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to application description</result>
 */
APPLICATION* CDECL AppGetCurrent(RTS_RESULT *pResult);
typedef APPLICATION* (CDECL * PFAPPGETCURRENT) (RTS_RESULT *pResult);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETCURRENT_NOTIMPLEMENTED)
	#define USE_AppGetCurrent
	#define EXT_AppGetCurrent
	#define GET_AppGetCurrent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetCurrent(p0)  (APPLICATION*)ERR_NOTIMPLEMENTED
	#define CHK_AppGetCurrent  FALSE
	#define EXP_AppGetCurrent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetCurrent
	#define EXT_AppGetCurrent
	#define GET_AppGetCurrent(fl)  CAL_CMGETAPI( "AppGetCurrent" ) 
	#define CAL_AppGetCurrent  AppGetCurrent
	#define CHK_AppGetCurrent  TRUE
	#define EXP_AppGetCurrent  CAL_CMEXPAPI( "AppGetCurrent" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetCurrent
	#define EXT_AppGetCurrent
	#define GET_AppGetCurrent(fl)  CAL_CMGETAPI( "AppGetCurrent" ) 
	#define CAL_AppGetCurrent  AppGetCurrent
	#define CHK_AppGetCurrent  TRUE
	#define EXP_AppGetCurrent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetCurrent", (RTS_UINTPTR)AppGetCurrent, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetCurrent
	#define EXT_CmpAppAppGetCurrent
	#define GET_CmpAppAppGetCurrent  ERR_OK
	#define CAL_CmpAppAppGetCurrent pICmpApp->IAppGetCurrent
	#define CHK_CmpAppAppGetCurrent (pICmpApp != NULL)
	#define EXP_CmpAppAppGetCurrent  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetCurrent
	#define EXT_AppGetCurrent
	#define GET_AppGetCurrent(fl)  CAL_CMGETAPI( "AppGetCurrent" ) 
	#define CAL_AppGetCurrent pICmpApp->IAppGetCurrent
	#define CHK_AppGetCurrent (pICmpApp != NULL)
	#define EXP_AppGetCurrent  CAL_CMEXPAPI( "AppGetCurrent" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetCurrent  PFAPPGETCURRENT pfAppGetCurrent;
	#define EXT_AppGetCurrent  extern PFAPPGETCURRENT pfAppGetCurrent;
	#define GET_AppGetCurrent(fl)  s_pfCMGetAPI2( "AppGetCurrent", (RTS_VOID_FCTPTR *)&pfAppGetCurrent, (fl), 0, 0)
	#define CAL_AppGetCurrent  pfAppGetCurrent
	#define CHK_AppGetCurrent  (pfAppGetCurrent != NULL)
	#define EXP_AppGetCurrent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetCurrent", (RTS_UINTPTR)AppGetCurrent, 0, 0) 
#endif




/**
 * <description>Check the consistency of the specified application to the files of bootproject and project archive</description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="pBootprojectConsistency" type="OUT">Pointer to result of the bootproject consistency.
 *		ERR_OK: Bootproject matches the specified application</param>
 * <param name="pArchiveConsistency" type="OUT">Pointer to result of the archive consistency.
 *		ERR_OK: Archive matches the specified application</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppCheckFileConsistency(APPLICATION *pApp, RTS_RESULT *pBootprojectConsistency, RTS_RESULT *pArchiveConsistency);
typedef RTS_RESULT (CDECL * PFAPPCHECKFILECONSISTENCY) (APPLICATION *pApp, RTS_RESULT *pBootprojectConsistency, RTS_RESULT *pArchiveConsistency);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPCHECKFILECONSISTENCY_NOTIMPLEMENTED)
	#define USE_AppCheckFileConsistency
	#define EXT_AppCheckFileConsistency
	#define GET_AppCheckFileConsistency(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppCheckFileConsistency(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppCheckFileConsistency  FALSE
	#define EXP_AppCheckFileConsistency  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppCheckFileConsistency
	#define EXT_AppCheckFileConsistency
	#define GET_AppCheckFileConsistency(fl)  CAL_CMGETAPI( "AppCheckFileConsistency" ) 
	#define CAL_AppCheckFileConsistency  AppCheckFileConsistency
	#define CHK_AppCheckFileConsistency  TRUE
	#define EXP_AppCheckFileConsistency  CAL_CMEXPAPI( "AppCheckFileConsistency" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppCheckFileConsistency
	#define EXT_AppCheckFileConsistency
	#define GET_AppCheckFileConsistency(fl)  CAL_CMGETAPI( "AppCheckFileConsistency" ) 
	#define CAL_AppCheckFileConsistency  AppCheckFileConsistency
	#define CHK_AppCheckFileConsistency  TRUE
	#define EXP_AppCheckFileConsistency  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppCheckFileConsistency", (RTS_UINTPTR)AppCheckFileConsistency, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppCheckFileConsistency
	#define EXT_CmpAppAppCheckFileConsistency
	#define GET_CmpAppAppCheckFileConsistency  ERR_OK
	#define CAL_CmpAppAppCheckFileConsistency pICmpApp->IAppCheckFileConsistency
	#define CHK_CmpAppAppCheckFileConsistency (pICmpApp != NULL)
	#define EXP_CmpAppAppCheckFileConsistency  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppCheckFileConsistency
	#define EXT_AppCheckFileConsistency
	#define GET_AppCheckFileConsistency(fl)  CAL_CMGETAPI( "AppCheckFileConsistency" ) 
	#define CAL_AppCheckFileConsistency pICmpApp->IAppCheckFileConsistency
	#define CHK_AppCheckFileConsistency (pICmpApp != NULL)
	#define EXP_AppCheckFileConsistency  CAL_CMEXPAPI( "AppCheckFileConsistency" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppCheckFileConsistency  PFAPPCHECKFILECONSISTENCY pfAppCheckFileConsistency;
	#define EXT_AppCheckFileConsistency  extern PFAPPCHECKFILECONSISTENCY pfAppCheckFileConsistency;
	#define GET_AppCheckFileConsistency(fl)  s_pfCMGetAPI2( "AppCheckFileConsistency", (RTS_VOID_FCTPTR *)&pfAppCheckFileConsistency, (fl), 0, 0)
	#define CAL_AppCheckFileConsistency  pfAppCheckFileConsistency
	#define CHK_AppCheckFileConsistency  (pfAppCheckFileConsistency != NULL)
	#define EXP_AppCheckFileConsistency  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppCheckFileConsistency", (RTS_UINTPTR)AppCheckFileConsistency, 0, 0) 
#endif




/**
 * <description>Generate an exception on the specified application.
 *	NOTE: pApp can be NULL, so the current applicaiton in program download sequence is used!</description>
 * <param name="pApp" type="IN">Pointer to Application. Can be NULL!</param>
 * <param name="ulException" type="IN">Exception code. See SysExceptItf.h for details.</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppGenerateException(APPLICATION *pApp, RTS_UI32 ulException);
typedef RTS_RESULT (CDECL * PFAPPGENERATEEXCEPTION) (APPLICATION *pApp, RTS_UI32 ulException);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGENERATEEXCEPTION_NOTIMPLEMENTED)
	#define USE_AppGenerateException
	#define EXT_AppGenerateException
	#define GET_AppGenerateException(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGenerateException(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppGenerateException  FALSE
	#define EXP_AppGenerateException  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGenerateException
	#define EXT_AppGenerateException
	#define GET_AppGenerateException(fl)  CAL_CMGETAPI( "AppGenerateException" ) 
	#define CAL_AppGenerateException  AppGenerateException
	#define CHK_AppGenerateException  TRUE
	#define EXP_AppGenerateException  CAL_CMEXPAPI( "AppGenerateException" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGenerateException
	#define EXT_AppGenerateException
	#define GET_AppGenerateException(fl)  CAL_CMGETAPI( "AppGenerateException" ) 
	#define CAL_AppGenerateException  AppGenerateException
	#define CHK_AppGenerateException  TRUE
	#define EXP_AppGenerateException  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGenerateException", (RTS_UINTPTR)AppGenerateException, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGenerateException
	#define EXT_CmpAppAppGenerateException
	#define GET_CmpAppAppGenerateException  ERR_OK
	#define CAL_CmpAppAppGenerateException pICmpApp->IAppGenerateException
	#define CHK_CmpAppAppGenerateException (pICmpApp != NULL)
	#define EXP_CmpAppAppGenerateException  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGenerateException
	#define EXT_AppGenerateException
	#define GET_AppGenerateException(fl)  CAL_CMGETAPI( "AppGenerateException" ) 
	#define CAL_AppGenerateException pICmpApp->IAppGenerateException
	#define CHK_AppGenerateException (pICmpApp != NULL)
	#define EXP_AppGenerateException  CAL_CMEXPAPI( "AppGenerateException" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGenerateException  PFAPPGENERATEEXCEPTION pfAppGenerateException;
	#define EXT_AppGenerateException  extern PFAPPGENERATEEXCEPTION pfAppGenerateException;
	#define GET_AppGenerateException(fl)  s_pfCMGetAPI2( "AppGenerateException", (RTS_VOID_FCTPTR *)&pfAppGenerateException, (fl), 0, 0)
	#define CAL_AppGenerateException  pfAppGenerateException
	#define CHK_AppGenerateException  (pfAppGenerateException != NULL)
	#define EXP_AppGenerateException  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGenerateException", (RTS_UINTPTR)AppGenerateException, 0, 0) 
#endif




/**
 * <description>Function to register a bootproject to reload at the next startup</description>
 * <param name="pszAppName" type="IN">Name of the bootproject without ending or application name</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppRegisterBootproject(char *pszBootproject);
typedef RTS_RESULT (CDECL * PFAPPREGISTERBOOTPROJECT) (char *pszBootproject);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPREGISTERBOOTPROJECT_NOTIMPLEMENTED)
	#define USE_AppRegisterBootproject
	#define EXT_AppRegisterBootproject
	#define GET_AppRegisterBootproject(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppRegisterBootproject(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppRegisterBootproject  FALSE
	#define EXP_AppRegisterBootproject  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppRegisterBootproject
	#define EXT_AppRegisterBootproject
	#define GET_AppRegisterBootproject(fl)  CAL_CMGETAPI( "AppRegisterBootproject" ) 
	#define CAL_AppRegisterBootproject  AppRegisterBootproject
	#define CHK_AppRegisterBootproject  TRUE
	#define EXP_AppRegisterBootproject  CAL_CMEXPAPI( "AppRegisterBootproject" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppRegisterBootproject
	#define EXT_AppRegisterBootproject
	#define GET_AppRegisterBootproject(fl)  CAL_CMGETAPI( "AppRegisterBootproject" ) 
	#define CAL_AppRegisterBootproject  AppRegisterBootproject
	#define CHK_AppRegisterBootproject  TRUE
	#define EXP_AppRegisterBootproject  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppRegisterBootproject", (RTS_UINTPTR)AppRegisterBootproject, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppRegisterBootproject
	#define EXT_CmpAppAppRegisterBootproject
	#define GET_CmpAppAppRegisterBootproject  ERR_OK
	#define CAL_CmpAppAppRegisterBootproject pICmpApp->IAppRegisterBootproject
	#define CHK_CmpAppAppRegisterBootproject (pICmpApp != NULL)
	#define EXP_CmpAppAppRegisterBootproject  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppRegisterBootproject
	#define EXT_AppRegisterBootproject
	#define GET_AppRegisterBootproject(fl)  CAL_CMGETAPI( "AppRegisterBootproject" ) 
	#define CAL_AppRegisterBootproject pICmpApp->IAppRegisterBootproject
	#define CHK_AppRegisterBootproject (pICmpApp != NULL)
	#define EXP_AppRegisterBootproject  CAL_CMEXPAPI( "AppRegisterBootproject" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppRegisterBootproject  PFAPPREGISTERBOOTPROJECT pfAppRegisterBootproject;
	#define EXT_AppRegisterBootproject  extern PFAPPREGISTERBOOTPROJECT pfAppRegisterBootproject;
	#define GET_AppRegisterBootproject(fl)  s_pfCMGetAPI2( "AppRegisterBootproject", (RTS_VOID_FCTPTR *)&pfAppRegisterBootproject, (fl), 0, 0)
	#define CAL_AppRegisterBootproject  pfAppRegisterBootproject
	#define CHK_AppRegisterBootproject  (pfAppRegisterBootproject != NULL)
	#define EXP_AppRegisterBootproject  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppRegisterBootproject", (RTS_UINTPTR)AppRegisterBootproject, 0, 0) 
#endif




/**
 * <description>Function to unregister a bootproject to avoid reload at the next startup</description>
 * <param name="pszAppName" type="IN">Name of the bootproject without ending or application name</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppUnregisterBootproject(char *pszBootproject);
typedef RTS_RESULT (CDECL * PFAPPUNREGISTERBOOTPROJECT) (char *pszBootproject);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPUNREGISTERBOOTPROJECT_NOTIMPLEMENTED)
	#define USE_AppUnregisterBootproject
	#define EXT_AppUnregisterBootproject
	#define GET_AppUnregisterBootproject(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppUnregisterBootproject(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppUnregisterBootproject  FALSE
	#define EXP_AppUnregisterBootproject  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppUnregisterBootproject
	#define EXT_AppUnregisterBootproject
	#define GET_AppUnregisterBootproject(fl)  CAL_CMGETAPI( "AppUnregisterBootproject" ) 
	#define CAL_AppUnregisterBootproject  AppUnregisterBootproject
	#define CHK_AppUnregisterBootproject  TRUE
	#define EXP_AppUnregisterBootproject  CAL_CMEXPAPI( "AppUnregisterBootproject" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppUnregisterBootproject
	#define EXT_AppUnregisterBootproject
	#define GET_AppUnregisterBootproject(fl)  CAL_CMGETAPI( "AppUnregisterBootproject" ) 
	#define CAL_AppUnregisterBootproject  AppUnregisterBootproject
	#define CHK_AppUnregisterBootproject  TRUE
	#define EXP_AppUnregisterBootproject  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppUnregisterBootproject", (RTS_UINTPTR)AppUnregisterBootproject, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppUnregisterBootproject
	#define EXT_CmpAppAppUnregisterBootproject
	#define GET_CmpAppAppUnregisterBootproject  ERR_OK
	#define CAL_CmpAppAppUnregisterBootproject pICmpApp->IAppUnregisterBootproject
	#define CHK_CmpAppAppUnregisterBootproject (pICmpApp != NULL)
	#define EXP_CmpAppAppUnregisterBootproject  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppUnregisterBootproject
	#define EXT_AppUnregisterBootproject
	#define GET_AppUnregisterBootproject(fl)  CAL_CMGETAPI( "AppUnregisterBootproject" ) 
	#define CAL_AppUnregisterBootproject pICmpApp->IAppUnregisterBootproject
	#define CHK_AppUnregisterBootproject (pICmpApp != NULL)
	#define EXP_AppUnregisterBootproject  CAL_CMEXPAPI( "AppUnregisterBootproject" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppUnregisterBootproject  PFAPPUNREGISTERBOOTPROJECT pfAppUnregisterBootproject;
	#define EXT_AppUnregisterBootproject  extern PFAPPUNREGISTERBOOTPROJECT pfAppUnregisterBootproject;
	#define GET_AppUnregisterBootproject(fl)  s_pfCMGetAPI2( "AppUnregisterBootproject", (RTS_VOID_FCTPTR *)&pfAppUnregisterBootproject, (fl), 0, 0)
	#define CAL_AppUnregisterBootproject  pfAppUnregisterBootproject
	#define CHK_AppUnregisterBootproject  (pfAppUnregisterBootproject != NULL)
	#define EXP_AppUnregisterBootproject  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppUnregisterBootproject", (RTS_UINTPTR)AppUnregisterBootproject, 0, 0) 
#endif




/**
 * <description>Function call a property of a function block to get the value</description>
 * <param name="pInstance" type="IN">Pointer to the FB instance</param>
 * <param name="ppGetMethod" type="IN">Pointer to the get method of the property (ADR(__get[PropertyName])</param>
 * <param name="pbyValue" type="IN">Pointer to a value buffer to return the value of the property</param>
 * <param name="ulSize" type="IN">Size in bytes of the property type</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppCallGetProperty(void *pInstance, RTS_VOID_FCTPTR *ppGetMethod, RTS_UI8 *pbyValue, RTS_SIZE ulSize);
typedef RTS_RESULT (CDECL * PFAPPCALLGETPROPERTY) (void *pInstance, RTS_VOID_FCTPTR *ppGetMethod, RTS_UI8 *pbyValue, RTS_SIZE ulSize);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPCALLGETPROPERTY_NOTIMPLEMENTED)
	#define USE_AppCallGetProperty
	#define EXT_AppCallGetProperty
	#define GET_AppCallGetProperty(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppCallGetProperty(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppCallGetProperty  FALSE
	#define EXP_AppCallGetProperty  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppCallGetProperty
	#define EXT_AppCallGetProperty
	#define GET_AppCallGetProperty(fl)  CAL_CMGETAPI( "AppCallGetProperty" ) 
	#define CAL_AppCallGetProperty  AppCallGetProperty
	#define CHK_AppCallGetProperty  TRUE
	#define EXP_AppCallGetProperty  CAL_CMEXPAPI( "AppCallGetProperty" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppCallGetProperty
	#define EXT_AppCallGetProperty
	#define GET_AppCallGetProperty(fl)  CAL_CMGETAPI( "AppCallGetProperty" ) 
	#define CAL_AppCallGetProperty  AppCallGetProperty
	#define CHK_AppCallGetProperty  TRUE
	#define EXP_AppCallGetProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppCallGetProperty", (RTS_UINTPTR)AppCallGetProperty, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppCallGetProperty
	#define EXT_CmpAppAppCallGetProperty
	#define GET_CmpAppAppCallGetProperty  ERR_OK
	#define CAL_CmpAppAppCallGetProperty pICmpApp->IAppCallGetProperty
	#define CHK_CmpAppAppCallGetProperty (pICmpApp != NULL)
	#define EXP_CmpAppAppCallGetProperty  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppCallGetProperty
	#define EXT_AppCallGetProperty
	#define GET_AppCallGetProperty(fl)  CAL_CMGETAPI( "AppCallGetProperty" ) 
	#define CAL_AppCallGetProperty pICmpApp->IAppCallGetProperty
	#define CHK_AppCallGetProperty (pICmpApp != NULL)
	#define EXP_AppCallGetProperty  CAL_CMEXPAPI( "AppCallGetProperty" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppCallGetProperty  PFAPPCALLGETPROPERTY pfAppCallGetProperty;
	#define EXT_AppCallGetProperty  extern PFAPPCALLGETPROPERTY pfAppCallGetProperty;
	#define GET_AppCallGetProperty(fl)  s_pfCMGetAPI2( "AppCallGetProperty", (RTS_VOID_FCTPTR *)&pfAppCallGetProperty, (fl), 0, 0)
	#define CAL_AppCallGetProperty  pfAppCallGetProperty
	#define CHK_AppCallGetProperty  (pfAppCallGetProperty != NULL)
	#define EXP_AppCallGetProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppCallGetProperty", (RTS_UINTPTR)AppCallGetProperty, 0, 0) 
#endif




/**
 * <description>Function call a property of a function block to get the value
 * <p>The returned internal buffer must be released with AppCallGetProperty2Release.</p></description>
 * <param name="pInstance" type="IN">Pointer to the FB instance</param>
 * <param name="ppGetMethod" type="IN">Pointer to the get method of the property (ADR(__get[PropertyName])</param>
 * <param name="ppbyValue" type="IN">Pointer to a pointer to an internal buffer which holds the value of the property</param>
 * <param name="ulSize" type="IN">Size in bytes of the property type</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppCallGetProperty2(void *pInstance, RTS_VOID_FCTPTR *ppGetMethod, RTS_UI8 **ppbyValue, RTS_SIZE ulSize);
typedef RTS_RESULT (CDECL * PFAPPCALLGETPROPERTY2) (void *pInstance, RTS_VOID_FCTPTR *ppGetMethod, RTS_UI8 **ppbyValue, RTS_SIZE ulSize);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPCALLGETPROPERTY2_NOTIMPLEMENTED)
	#define USE_AppCallGetProperty2
	#define EXT_AppCallGetProperty2
	#define GET_AppCallGetProperty2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppCallGetProperty2(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppCallGetProperty2  FALSE
	#define EXP_AppCallGetProperty2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppCallGetProperty2
	#define EXT_AppCallGetProperty2
	#define GET_AppCallGetProperty2(fl)  CAL_CMGETAPI( "AppCallGetProperty2" ) 
	#define CAL_AppCallGetProperty2  AppCallGetProperty2
	#define CHK_AppCallGetProperty2  TRUE
	#define EXP_AppCallGetProperty2  CAL_CMEXPAPI( "AppCallGetProperty2" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppCallGetProperty2
	#define EXT_AppCallGetProperty2
	#define GET_AppCallGetProperty2(fl)  CAL_CMGETAPI( "AppCallGetProperty2" ) 
	#define CAL_AppCallGetProperty2  AppCallGetProperty2
	#define CHK_AppCallGetProperty2  TRUE
	#define EXP_AppCallGetProperty2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppCallGetProperty2", (RTS_UINTPTR)AppCallGetProperty2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppCallGetProperty2
	#define EXT_CmpAppAppCallGetProperty2
	#define GET_CmpAppAppCallGetProperty2  ERR_OK
	#define CAL_CmpAppAppCallGetProperty2 pICmpApp->IAppCallGetProperty2
	#define CHK_CmpAppAppCallGetProperty2 (pICmpApp != NULL)
	#define EXP_CmpAppAppCallGetProperty2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppCallGetProperty2
	#define EXT_AppCallGetProperty2
	#define GET_AppCallGetProperty2(fl)  CAL_CMGETAPI( "AppCallGetProperty2" ) 
	#define CAL_AppCallGetProperty2 pICmpApp->IAppCallGetProperty2
	#define CHK_AppCallGetProperty2 (pICmpApp != NULL)
	#define EXP_AppCallGetProperty2  CAL_CMEXPAPI( "AppCallGetProperty2" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppCallGetProperty2  PFAPPCALLGETPROPERTY2 pfAppCallGetProperty2;
	#define EXT_AppCallGetProperty2  extern PFAPPCALLGETPROPERTY2 pfAppCallGetProperty2;
	#define GET_AppCallGetProperty2(fl)  s_pfCMGetAPI2( "AppCallGetProperty2", (RTS_VOID_FCTPTR *)&pfAppCallGetProperty2, (fl), 0, 0)
	#define CAL_AppCallGetProperty2  pfAppCallGetProperty2
	#define CHK_AppCallGetProperty2  (pfAppCallGetProperty2 != NULL)
	#define EXP_AppCallGetProperty2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppCallGetProperty2", (RTS_UINTPTR)AppCallGetProperty2, 0, 0) 
#endif




/**
 * <description>Function call to release the internal buffer returned by AppCallGetProperty2</description>
 * <param name="pbyValue" type="IN">Pointer to the internal buffer from AppCallGetProperty2</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppCallGetProperty2Release(RTS_UI8 *pbyValue);
typedef RTS_RESULT (CDECL * PFAPPCALLGETPROPERTY2RELEASE) (RTS_UI8 *pbyValue);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPCALLGETPROPERTY2RELEASE_NOTIMPLEMENTED)
	#define USE_AppCallGetProperty2Release
	#define EXT_AppCallGetProperty2Release
	#define GET_AppCallGetProperty2Release(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppCallGetProperty2Release(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppCallGetProperty2Release  FALSE
	#define EXP_AppCallGetProperty2Release  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppCallGetProperty2Release
	#define EXT_AppCallGetProperty2Release
	#define GET_AppCallGetProperty2Release(fl)  CAL_CMGETAPI( "AppCallGetProperty2Release" ) 
	#define CAL_AppCallGetProperty2Release  AppCallGetProperty2Release
	#define CHK_AppCallGetProperty2Release  TRUE
	#define EXP_AppCallGetProperty2Release  CAL_CMEXPAPI( "AppCallGetProperty2Release" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppCallGetProperty2Release
	#define EXT_AppCallGetProperty2Release
	#define GET_AppCallGetProperty2Release(fl)  CAL_CMGETAPI( "AppCallGetProperty2Release" ) 
	#define CAL_AppCallGetProperty2Release  AppCallGetProperty2Release
	#define CHK_AppCallGetProperty2Release  TRUE
	#define EXP_AppCallGetProperty2Release  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppCallGetProperty2Release", (RTS_UINTPTR)AppCallGetProperty2Release, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppCallGetProperty2Release
	#define EXT_CmpAppAppCallGetProperty2Release
	#define GET_CmpAppAppCallGetProperty2Release  ERR_OK
	#define CAL_CmpAppAppCallGetProperty2Release pICmpApp->IAppCallGetProperty2Release
	#define CHK_CmpAppAppCallGetProperty2Release (pICmpApp != NULL)
	#define EXP_CmpAppAppCallGetProperty2Release  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppCallGetProperty2Release
	#define EXT_AppCallGetProperty2Release
	#define GET_AppCallGetProperty2Release(fl)  CAL_CMGETAPI( "AppCallGetProperty2Release" ) 
	#define CAL_AppCallGetProperty2Release pICmpApp->IAppCallGetProperty2Release
	#define CHK_AppCallGetProperty2Release (pICmpApp != NULL)
	#define EXP_AppCallGetProperty2Release  CAL_CMEXPAPI( "AppCallGetProperty2Release" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppCallGetProperty2Release  PFAPPCALLGETPROPERTY2RELEASE pfAppCallGetProperty2Release;
	#define EXT_AppCallGetProperty2Release  extern PFAPPCALLGETPROPERTY2RELEASE pfAppCallGetProperty2Release;
	#define GET_AppCallGetProperty2Release(fl)  s_pfCMGetAPI2( "AppCallGetProperty2Release", (RTS_VOID_FCTPTR *)&pfAppCallGetProperty2Release, (fl), 0, 0)
	#define CAL_AppCallGetProperty2Release  pfAppCallGetProperty2Release
	#define CHK_AppCallGetProperty2Release  (pfAppCallGetProperty2Release != NULL)
	#define EXP_AppCallGetProperty2Release  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppCallGetProperty2Release", (RTS_UINTPTR)AppCallGetProperty2Release, 0, 0) 
#endif




/**
 * <description>Function call a property of a function block to set the value</description>
 * <param name="pInstance" type="IN">Pointer to the FB instance</param>
 * <param name="ppSetMethod" type="IN">Pointer to the set method of the property (ADR(__get[PropertyName])</param>
 * <param name="pbyValue" type="IN">Pointer to a value buffer to set the value of the property</param>
 * <param name="ulSize" type="IN">Size in bytes of the property type</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppCallSetProperty(void *pInstance, RTS_VOID_FCTPTR *ppSetMethod, RTS_UI8 *pbyValue, RTS_SIZE ulSize);
typedef RTS_RESULT (CDECL * PFAPPCALLSETPROPERTY) (void *pInstance, RTS_VOID_FCTPTR *ppSetMethod, RTS_UI8 *pbyValue, RTS_SIZE ulSize);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPCALLSETPROPERTY_NOTIMPLEMENTED)
	#define USE_AppCallSetProperty
	#define EXT_AppCallSetProperty
	#define GET_AppCallSetProperty(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppCallSetProperty(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppCallSetProperty  FALSE
	#define EXP_AppCallSetProperty  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppCallSetProperty
	#define EXT_AppCallSetProperty
	#define GET_AppCallSetProperty(fl)  CAL_CMGETAPI( "AppCallSetProperty" ) 
	#define CAL_AppCallSetProperty  AppCallSetProperty
	#define CHK_AppCallSetProperty  TRUE
	#define EXP_AppCallSetProperty  CAL_CMEXPAPI( "AppCallSetProperty" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppCallSetProperty
	#define EXT_AppCallSetProperty
	#define GET_AppCallSetProperty(fl)  CAL_CMGETAPI( "AppCallSetProperty" ) 
	#define CAL_AppCallSetProperty  AppCallSetProperty
	#define CHK_AppCallSetProperty  TRUE
	#define EXP_AppCallSetProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppCallSetProperty", (RTS_UINTPTR)AppCallSetProperty, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppCallSetProperty
	#define EXT_CmpAppAppCallSetProperty
	#define GET_CmpAppAppCallSetProperty  ERR_OK
	#define CAL_CmpAppAppCallSetProperty pICmpApp->IAppCallSetProperty
	#define CHK_CmpAppAppCallSetProperty (pICmpApp != NULL)
	#define EXP_CmpAppAppCallSetProperty  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppCallSetProperty
	#define EXT_AppCallSetProperty
	#define GET_AppCallSetProperty(fl)  CAL_CMGETAPI( "AppCallSetProperty" ) 
	#define CAL_AppCallSetProperty pICmpApp->IAppCallSetProperty
	#define CHK_AppCallSetProperty (pICmpApp != NULL)
	#define EXP_AppCallSetProperty  CAL_CMEXPAPI( "AppCallSetProperty" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppCallSetProperty  PFAPPCALLSETPROPERTY pfAppCallSetProperty;
	#define EXT_AppCallSetProperty  extern PFAPPCALLSETPROPERTY pfAppCallSetProperty;
	#define GET_AppCallSetProperty(fl)  s_pfCMGetAPI2( "AppCallSetProperty", (RTS_VOID_FCTPTR *)&pfAppCallSetProperty, (fl), 0, 0)
	#define CAL_AppCallSetProperty  pfAppCallSetProperty
	#define CHK_AppCallSetProperty  (pfAppCallSetProperty != NULL)
	#define EXP_AppCallSetProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppCallSetProperty", (RTS_UINTPTR)AppCallSetProperty, 0, 0) 
#endif




/**
 * <description>Get area number and offset of an application specified by a memory address</description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="ulAddress" type="IN">Memory address</param>
 * <param name="pusArea" type="OUT">Pointer to return area number</param>
 * <param name="pulOffset" type="IN">Pointer to return area offset</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppGetAreaOffsetByAddress(APPLICATION *pApp, RTS_UINTPTR ulAddress, RTS_UI16 *pusArea, RTS_SIZE *pulOffset);
typedef RTS_RESULT (CDECL * PFAPPGETAREAOFFSETBYADDRESS) (APPLICATION *pApp, RTS_UINTPTR ulAddress, RTS_UI16 *pusArea, RTS_SIZE *pulOffset);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETAREAOFFSETBYADDRESS_NOTIMPLEMENTED)
	#define USE_AppGetAreaOffsetByAddress
	#define EXT_AppGetAreaOffsetByAddress
	#define GET_AppGetAreaOffsetByAddress(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetAreaOffsetByAddress(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppGetAreaOffsetByAddress  FALSE
	#define EXP_AppGetAreaOffsetByAddress  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetAreaOffsetByAddress
	#define EXT_AppGetAreaOffsetByAddress
	#define GET_AppGetAreaOffsetByAddress(fl)  CAL_CMGETAPI( "AppGetAreaOffsetByAddress" ) 
	#define CAL_AppGetAreaOffsetByAddress  AppGetAreaOffsetByAddress
	#define CHK_AppGetAreaOffsetByAddress  TRUE
	#define EXP_AppGetAreaOffsetByAddress  CAL_CMEXPAPI( "AppGetAreaOffsetByAddress" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetAreaOffsetByAddress
	#define EXT_AppGetAreaOffsetByAddress
	#define GET_AppGetAreaOffsetByAddress(fl)  CAL_CMGETAPI( "AppGetAreaOffsetByAddress" ) 
	#define CAL_AppGetAreaOffsetByAddress  AppGetAreaOffsetByAddress
	#define CHK_AppGetAreaOffsetByAddress  TRUE
	#define EXP_AppGetAreaOffsetByAddress  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetAreaOffsetByAddress", (RTS_UINTPTR)AppGetAreaOffsetByAddress, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetAreaOffsetByAddress
	#define EXT_CmpAppAppGetAreaOffsetByAddress
	#define GET_CmpAppAppGetAreaOffsetByAddress  ERR_OK
	#define CAL_CmpAppAppGetAreaOffsetByAddress pICmpApp->IAppGetAreaOffsetByAddress
	#define CHK_CmpAppAppGetAreaOffsetByAddress (pICmpApp != NULL)
	#define EXP_CmpAppAppGetAreaOffsetByAddress  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetAreaOffsetByAddress
	#define EXT_AppGetAreaOffsetByAddress
	#define GET_AppGetAreaOffsetByAddress(fl)  CAL_CMGETAPI( "AppGetAreaOffsetByAddress" ) 
	#define CAL_AppGetAreaOffsetByAddress pICmpApp->IAppGetAreaOffsetByAddress
	#define CHK_AppGetAreaOffsetByAddress (pICmpApp != NULL)
	#define EXP_AppGetAreaOffsetByAddress  CAL_CMEXPAPI( "AppGetAreaOffsetByAddress" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetAreaOffsetByAddress  PFAPPGETAREAOFFSETBYADDRESS pfAppGetAreaOffsetByAddress;
	#define EXT_AppGetAreaOffsetByAddress  extern PFAPPGETAREAOFFSETBYADDRESS pfAppGetAreaOffsetByAddress;
	#define GET_AppGetAreaOffsetByAddress(fl)  s_pfCMGetAPI2( "AppGetAreaOffsetByAddress", (RTS_VOID_FCTPTR *)&pfAppGetAreaOffsetByAddress, (fl), 0, 0)
	#define CAL_AppGetAreaOffsetByAddress  pfAppGetAreaOffsetByAddress
	#define CHK_AppGetAreaOffsetByAddress  (pfAppGetAreaOffsetByAddress != NULL)
	#define EXP_AppGetAreaOffsetByAddress  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetAreaOffsetByAddress", (RTS_UINTPTR)AppGetAreaOffsetByAddress, 0, 0) 
#endif





/**
 * <description>Returns the application specified in an online service</description>
 * <param name="pduSendBuffer" type="IN">Pointer to the sent data unit</param>
 * <param name="preader" type="IN">Pointer to the reader</param>
 * <param name="pwriter" type="IN">Pointer to the writer</param>
 * <param name="ulSessionId" type="IN">Session id of the given service</param>
 * <result>Pointer to the application description</result>
 */
APPLICATION* CDECL AppSrvGetApplication(PROTOCOL_DATA_UNIT *pduSendBuffer, BINTAGREADER *preader, BINTAGWRITER *pwriter, RTS_UI32 ulSessionId);
typedef APPLICATION* (CDECL * PFAPPSRVGETAPPLICATION) (PROTOCOL_DATA_UNIT *pduSendBuffer, BINTAGREADER *preader, BINTAGWRITER *pwriter, RTS_UI32 ulSessionId);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPSRVGETAPPLICATION_NOTIMPLEMENTED)
	#define USE_AppSrvGetApplication
	#define EXT_AppSrvGetApplication
	#define GET_AppSrvGetApplication(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppSrvGetApplication(p0,p1,p2,p3)  (APPLICATION*)ERR_NOTIMPLEMENTED
	#define CHK_AppSrvGetApplication  FALSE
	#define EXP_AppSrvGetApplication  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppSrvGetApplication
	#define EXT_AppSrvGetApplication
	#define GET_AppSrvGetApplication(fl)  CAL_CMGETAPI( "AppSrvGetApplication" ) 
	#define CAL_AppSrvGetApplication  AppSrvGetApplication
	#define CHK_AppSrvGetApplication  TRUE
	#define EXP_AppSrvGetApplication  CAL_CMEXPAPI( "AppSrvGetApplication" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppSrvGetApplication
	#define EXT_AppSrvGetApplication
	#define GET_AppSrvGetApplication(fl)  CAL_CMGETAPI( "AppSrvGetApplication" ) 
	#define CAL_AppSrvGetApplication  AppSrvGetApplication
	#define CHK_AppSrvGetApplication  TRUE
	#define EXP_AppSrvGetApplication  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppSrvGetApplication", (RTS_UINTPTR)AppSrvGetApplication, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppSrvGetApplication
	#define EXT_CmpAppAppSrvGetApplication
	#define GET_CmpAppAppSrvGetApplication  ERR_OK
	#define CAL_CmpAppAppSrvGetApplication pICmpApp->IAppSrvGetApplication
	#define CHK_CmpAppAppSrvGetApplication (pICmpApp != NULL)
	#define EXP_CmpAppAppSrvGetApplication  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppSrvGetApplication
	#define EXT_AppSrvGetApplication
	#define GET_AppSrvGetApplication(fl)  CAL_CMGETAPI( "AppSrvGetApplication" ) 
	#define CAL_AppSrvGetApplication pICmpApp->IAppSrvGetApplication
	#define CHK_AppSrvGetApplication (pICmpApp != NULL)
	#define EXP_AppSrvGetApplication  CAL_CMEXPAPI( "AppSrvGetApplication" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppSrvGetApplication  PFAPPSRVGETAPPLICATION pfAppSrvGetApplication;
	#define EXT_AppSrvGetApplication  extern PFAPPSRVGETAPPLICATION pfAppSrvGetApplication;
	#define GET_AppSrvGetApplication(fl)  s_pfCMGetAPI2( "AppSrvGetApplication", (RTS_VOID_FCTPTR *)&pfAppSrvGetApplication, (fl), 0, 0)
	#define CAL_AppSrvGetApplication  pfAppSrvGetApplication
	#define CHK_AppSrvGetApplication  (pfAppSrvGetApplication != NULL)
	#define EXP_AppSrvGetApplication  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppSrvGetApplication", (RTS_UINTPTR)AppSrvGetApplication, 0, 0) 
#endif




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
RTS_RESULT CDECL AppHasAccessRights(char *pszApplication, char *pszObject, RTS_UI32 ulRequestedRights, RTS_UI32 ulSessionId, BINTAGWRITER *pWriter);
typedef RTS_RESULT (CDECL * PFAPPHASACCESSRIGHTS) (char *pszApplication, char *pszObject, RTS_UI32 ulRequestedRights, RTS_UI32 ulSessionId, BINTAGWRITER *pWriter);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPHASACCESSRIGHTS_NOTIMPLEMENTED)
	#define USE_AppHasAccessRights
	#define EXT_AppHasAccessRights
	#define GET_AppHasAccessRights(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppHasAccessRights(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppHasAccessRights  FALSE
	#define EXP_AppHasAccessRights  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppHasAccessRights
	#define EXT_AppHasAccessRights
	#define GET_AppHasAccessRights(fl)  CAL_CMGETAPI( "AppHasAccessRights" ) 
	#define CAL_AppHasAccessRights  AppHasAccessRights
	#define CHK_AppHasAccessRights  TRUE
	#define EXP_AppHasAccessRights  CAL_CMEXPAPI( "AppHasAccessRights" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppHasAccessRights
	#define EXT_AppHasAccessRights
	#define GET_AppHasAccessRights(fl)  CAL_CMGETAPI( "AppHasAccessRights" ) 
	#define CAL_AppHasAccessRights  AppHasAccessRights
	#define CHK_AppHasAccessRights  TRUE
	#define EXP_AppHasAccessRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppHasAccessRights", (RTS_UINTPTR)AppHasAccessRights, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppHasAccessRights
	#define EXT_CmpAppAppHasAccessRights
	#define GET_CmpAppAppHasAccessRights  ERR_OK
	#define CAL_CmpAppAppHasAccessRights pICmpApp->IAppHasAccessRights
	#define CHK_CmpAppAppHasAccessRights (pICmpApp != NULL)
	#define EXP_CmpAppAppHasAccessRights  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppHasAccessRights
	#define EXT_AppHasAccessRights
	#define GET_AppHasAccessRights(fl)  CAL_CMGETAPI( "AppHasAccessRights" ) 
	#define CAL_AppHasAccessRights pICmpApp->IAppHasAccessRights
	#define CHK_AppHasAccessRights (pICmpApp != NULL)
	#define EXP_AppHasAccessRights  CAL_CMEXPAPI( "AppHasAccessRights" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppHasAccessRights  PFAPPHASACCESSRIGHTS pfAppHasAccessRights;
	#define EXT_AppHasAccessRights  extern PFAPPHASACCESSRIGHTS pfAppHasAccessRights;
	#define GET_AppHasAccessRights(fl)  s_pfCMGetAPI2( "AppHasAccessRights", (RTS_VOID_FCTPTR *)&pfAppHasAccessRights, (fl), 0, 0)
	#define CAL_AppHasAccessRights  pfAppHasAccessRights
	#define CHK_AppHasAccessRights  (pfAppHasAccessRights != NULL)
	#define EXP_AppHasAccessRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppHasAccessRights", (RTS_UINTPTR)AppHasAccessRights, 0, 0) 
#endif




/**
 * <description>Get the detail information of the specified application</description>
 * <param name="pApp" type="IN">Pointer to Application</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to application info structure</result>
 */
APPLICATION_INFO * CDECL AppGetApplicationInfo(APPLICATION *pApp, RTS_RESULT *pResult);
typedef APPLICATION_INFO * (CDECL * PFAPPGETAPPLICATIONINFO) (APPLICATION *pApp, RTS_RESULT *pResult);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETAPPLICATIONINFO_NOTIMPLEMENTED)
	#define USE_AppGetApplicationInfo
	#define EXT_AppGetApplicationInfo
	#define GET_AppGetApplicationInfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetApplicationInfo(p0,p1)  (APPLICATION_INFO *)ERR_NOTIMPLEMENTED
	#define CHK_AppGetApplicationInfo  FALSE
	#define EXP_AppGetApplicationInfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetApplicationInfo
	#define EXT_AppGetApplicationInfo
	#define GET_AppGetApplicationInfo(fl)  CAL_CMGETAPI( "AppGetApplicationInfo" ) 
	#define CAL_AppGetApplicationInfo  AppGetApplicationInfo
	#define CHK_AppGetApplicationInfo  TRUE
	#define EXP_AppGetApplicationInfo  CAL_CMEXPAPI( "AppGetApplicationInfo" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetApplicationInfo
	#define EXT_AppGetApplicationInfo
	#define GET_AppGetApplicationInfo(fl)  CAL_CMGETAPI( "AppGetApplicationInfo" ) 
	#define CAL_AppGetApplicationInfo  AppGetApplicationInfo
	#define CHK_AppGetApplicationInfo  TRUE
	#define EXP_AppGetApplicationInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetApplicationInfo", (RTS_UINTPTR)AppGetApplicationInfo, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetApplicationInfo
	#define EXT_CmpAppAppGetApplicationInfo
	#define GET_CmpAppAppGetApplicationInfo  ERR_OK
	#define CAL_CmpAppAppGetApplicationInfo pICmpApp->IAppGetApplicationInfo
	#define CHK_CmpAppAppGetApplicationInfo (pICmpApp != NULL)
	#define EXP_CmpAppAppGetApplicationInfo  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetApplicationInfo
	#define EXT_AppGetApplicationInfo
	#define GET_AppGetApplicationInfo(fl)  CAL_CMGETAPI( "AppGetApplicationInfo" ) 
	#define CAL_AppGetApplicationInfo pICmpApp->IAppGetApplicationInfo
	#define CHK_AppGetApplicationInfo (pICmpApp != NULL)
	#define EXP_AppGetApplicationInfo  CAL_CMEXPAPI( "AppGetApplicationInfo" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetApplicationInfo  PFAPPGETAPPLICATIONINFO pfAppGetApplicationInfo;
	#define EXT_AppGetApplicationInfo  extern PFAPPGETAPPLICATIONINFO pfAppGetApplicationInfo;
	#define GET_AppGetApplicationInfo(fl)  s_pfCMGetAPI2( "AppGetApplicationInfo", (RTS_VOID_FCTPTR *)&pfAppGetApplicationInfo, (fl), 0, 0)
	#define CAL_AppGetApplicationInfo  pfAppGetApplicationInfo
	#define CHK_AppGetApplicationInfo  (pfAppGetApplicationInfo != NULL)
	#define EXP_AppGetApplicationInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetApplicationInfo", (RTS_UINTPTR)AppGetApplicationInfo, 0, 0) 
#endif




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
RTS_HANDLE CDECL AppGetFirstConfiguredBootproject(char *pszAppName, RTS_I32 nMaxAppName, RTS_BOOL bCheckFile, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFAPPGETFIRSTCONFIGUREDBOOTPROJECT) (char *pszAppName, RTS_I32 nMaxAppName, RTS_BOOL bCheckFile, RTS_RESULT *pResult);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETFIRSTCONFIGUREDBOOTPROJECT_NOTIMPLEMENTED)
	#define USE_AppGetFirstConfiguredBootproject
	#define EXT_AppGetFirstConfiguredBootproject
	#define GET_AppGetFirstConfiguredBootproject(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetFirstConfiguredBootproject(p0,p1,p2,p3)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_AppGetFirstConfiguredBootproject  FALSE
	#define EXP_AppGetFirstConfiguredBootproject  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetFirstConfiguredBootproject
	#define EXT_AppGetFirstConfiguredBootproject
	#define GET_AppGetFirstConfiguredBootproject(fl)  CAL_CMGETAPI( "AppGetFirstConfiguredBootproject" ) 
	#define CAL_AppGetFirstConfiguredBootproject  AppGetFirstConfiguredBootproject
	#define CHK_AppGetFirstConfiguredBootproject  TRUE
	#define EXP_AppGetFirstConfiguredBootproject  CAL_CMEXPAPI( "AppGetFirstConfiguredBootproject" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetFirstConfiguredBootproject
	#define EXT_AppGetFirstConfiguredBootproject
	#define GET_AppGetFirstConfiguredBootproject(fl)  CAL_CMGETAPI( "AppGetFirstConfiguredBootproject" ) 
	#define CAL_AppGetFirstConfiguredBootproject  AppGetFirstConfiguredBootproject
	#define CHK_AppGetFirstConfiguredBootproject  TRUE
	#define EXP_AppGetFirstConfiguredBootproject  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetFirstConfiguredBootproject", (RTS_UINTPTR)AppGetFirstConfiguredBootproject, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetFirstConfiguredBootproject
	#define EXT_CmpAppAppGetFirstConfiguredBootproject
	#define GET_CmpAppAppGetFirstConfiguredBootproject  ERR_OK
	#define CAL_CmpAppAppGetFirstConfiguredBootproject pICmpApp->IAppGetFirstConfiguredBootproject
	#define CHK_CmpAppAppGetFirstConfiguredBootproject (pICmpApp != NULL)
	#define EXP_CmpAppAppGetFirstConfiguredBootproject  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetFirstConfiguredBootproject
	#define EXT_AppGetFirstConfiguredBootproject
	#define GET_AppGetFirstConfiguredBootproject(fl)  CAL_CMGETAPI( "AppGetFirstConfiguredBootproject" ) 
	#define CAL_AppGetFirstConfiguredBootproject pICmpApp->IAppGetFirstConfiguredBootproject
	#define CHK_AppGetFirstConfiguredBootproject (pICmpApp != NULL)
	#define EXP_AppGetFirstConfiguredBootproject  CAL_CMEXPAPI( "AppGetFirstConfiguredBootproject" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetFirstConfiguredBootproject  PFAPPGETFIRSTCONFIGUREDBOOTPROJECT pfAppGetFirstConfiguredBootproject;
	#define EXT_AppGetFirstConfiguredBootproject  extern PFAPPGETFIRSTCONFIGUREDBOOTPROJECT pfAppGetFirstConfiguredBootproject;
	#define GET_AppGetFirstConfiguredBootproject(fl)  s_pfCMGetAPI2( "AppGetFirstConfiguredBootproject", (RTS_VOID_FCTPTR *)&pfAppGetFirstConfiguredBootproject, (fl), 0, 0)
	#define CAL_AppGetFirstConfiguredBootproject  pfAppGetFirstConfiguredBootproject
	#define CHK_AppGetFirstConfiguredBootproject  (pfAppGetFirstConfiguredBootproject != NULL)
	#define EXP_AppGetFirstConfiguredBootproject  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetFirstConfiguredBootproject", (RTS_UINTPTR)AppGetFirstConfiguredBootproject, 0, 0) 
#endif




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
RTS_HANDLE CDECL AppGetNextConfiguredBootproject(RTS_HANDLE hPrev, char *pszAppName, RTS_I32 nMaxAppName, RTS_BOOL bCheckFile, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFAPPGETNEXTCONFIGUREDBOOTPROJECT) (RTS_HANDLE hPrev, char *pszAppName, RTS_I32 nMaxAppName, RTS_BOOL bCheckFile, RTS_RESULT *pResult);
#if defined(CMPAPP_NOTIMPLEMENTED) || defined(APPGETNEXTCONFIGUREDBOOTPROJECT_NOTIMPLEMENTED)
	#define USE_AppGetNextConfiguredBootproject
	#define EXT_AppGetNextConfiguredBootproject
	#define GET_AppGetNextConfiguredBootproject(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppGetNextConfiguredBootproject(p0,p1,p2,p3,p4)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_AppGetNextConfiguredBootproject  FALSE
	#define EXP_AppGetNextConfiguredBootproject  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppGetNextConfiguredBootproject
	#define EXT_AppGetNextConfiguredBootproject
	#define GET_AppGetNextConfiguredBootproject(fl)  CAL_CMGETAPI( "AppGetNextConfiguredBootproject" ) 
	#define CAL_AppGetNextConfiguredBootproject  AppGetNextConfiguredBootproject
	#define CHK_AppGetNextConfiguredBootproject  TRUE
	#define EXP_AppGetNextConfiguredBootproject  CAL_CMEXPAPI( "AppGetNextConfiguredBootproject" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPP_EXTERNAL)
	#define USE_AppGetNextConfiguredBootproject
	#define EXT_AppGetNextConfiguredBootproject
	#define GET_AppGetNextConfiguredBootproject(fl)  CAL_CMGETAPI( "AppGetNextConfiguredBootproject" ) 
	#define CAL_AppGetNextConfiguredBootproject  AppGetNextConfiguredBootproject
	#define CHK_AppGetNextConfiguredBootproject  TRUE
	#define EXP_AppGetNextConfiguredBootproject  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetNextConfiguredBootproject", (RTS_UINTPTR)AppGetNextConfiguredBootproject, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppAppGetNextConfiguredBootproject
	#define EXT_CmpAppAppGetNextConfiguredBootproject
	#define GET_CmpAppAppGetNextConfiguredBootproject  ERR_OK
	#define CAL_CmpAppAppGetNextConfiguredBootproject pICmpApp->IAppGetNextConfiguredBootproject
	#define CHK_CmpAppAppGetNextConfiguredBootproject (pICmpApp != NULL)
	#define EXP_CmpAppAppGetNextConfiguredBootproject  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppGetNextConfiguredBootproject
	#define EXT_AppGetNextConfiguredBootproject
	#define GET_AppGetNextConfiguredBootproject(fl)  CAL_CMGETAPI( "AppGetNextConfiguredBootproject" ) 
	#define CAL_AppGetNextConfiguredBootproject pICmpApp->IAppGetNextConfiguredBootproject
	#define CHK_AppGetNextConfiguredBootproject (pICmpApp != NULL)
	#define EXP_AppGetNextConfiguredBootproject  CAL_CMEXPAPI( "AppGetNextConfiguredBootproject" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppGetNextConfiguredBootproject  PFAPPGETNEXTCONFIGUREDBOOTPROJECT pfAppGetNextConfiguredBootproject;
	#define EXT_AppGetNextConfiguredBootproject  extern PFAPPGETNEXTCONFIGUREDBOOTPROJECT pfAppGetNextConfiguredBootproject;
	#define GET_AppGetNextConfiguredBootproject(fl)  s_pfCMGetAPI2( "AppGetNextConfiguredBootproject", (RTS_VOID_FCTPTR *)&pfAppGetNextConfiguredBootproject, (fl), 0, 0)
	#define CAL_AppGetNextConfiguredBootproject  pfAppGetNextConfiguredBootproject
	#define CHK_AppGetNextConfiguredBootproject  (pfAppGetNextConfiguredBootproject != NULL)
	#define EXP_AppGetNextConfiguredBootproject  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppGetNextConfiguredBootproject", (RTS_UINTPTR)AppGetNextConfiguredBootproject, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFAPPCREATEAPPLICATION IAppCreateApplication;
 	PFAPPPREPAREDOWNLOAD IAppPrepareDownload;
 	PFAPPAPPENDCODE IAppAppendCode;
 	PFAPPCOMPLETEDOWNLOAD IAppCompleteDownload;
 	PFAPPFINDAPPLICATIONBYNAME IAppFindApplicationByName;
 	PFAPPNUMOFACTIVESESSIONS IAppNumOfActiveSessions;
 	PFAPPFINDAPPLICATIONBYBOOTPROJECT IAppFindApplicationByBootproject;
 	PFAPPFINDAPPLICATIONBYSESSIONID IAppFindApplicationBySessionId;
 	PFAPPFINDAPPLICATIONBYID IAppFindApplicationById;
 	PFAPPGETNUMOFAPPLICATIONS IAppGetNumOfApplications;
 	PFAPPGETAPPLICATIONBYINDEX IAppGetApplicationByIndex;
 	PFAPPGETAPPLICATIONBYAREAADDRESS IAppGetApplicationByAreaAddress;
 	PFAPPGETAREAPOINTER IAppGetAreaPointer;
 	PFAPPGETAREAPOINTER2 IAppGetAreaPointer2;
 	PFAPPGETAREAPOINTERBYTYPE IAppGetAreaPointerByType;
 	PFAPPHASADDRESS IAppHasAddress;
 	PFAPPISPROGRAMLOADED IAppIsProgramLoaded;
 	PFAPPSETPROGRAMLOADED IAppSetProgramLoaded;
 	PFAPPSINGLECYCLE IAppSingleCycle;
 	PFAPPSETSTATE IAppSetState;
 	PFAPPGETSTATE IAppGetState;
 	PFAPPSETOPERATINGSTATE IAppSetOperatingState;
 	PFAPPRESETOPERATINGSTATE IAppResetOperatingState;
 	PFAPPGETOPERATINGSTATE IAppGetOperatingState;
 	PFAPPSETCODEGUID IAppSetCodeGuid;
 	PFAPPGETCODEGUID IAppGetCodeGuid;
 	PFAPPSETDATAGUID IAppSetDataGuid;
 	PFAPPGETDATAGUID IAppGetDataGuid;
 	PFAPPGETBOOTPROJECTGUIDS IAppGetBootprojectGuids;
 	PFAPPEXCEPTIONHANDLER IAppExceptionHandler;
 	PFAPPRESET IAppReset;
 	PFAPPRESETALLAPPLICATIONS IAppResetAllApplications;
 	PFAPPLOADBOOTPROJECTS IAppLoadBootprojects;
 	PFAPPSTARTBOOTPROJECTS IAppStartBootprojects;
 	PFAPPLOADBOOTPROJECT IAppLoadBootproject;
 	PFAPPSTARTAPPLICATIONS IAppStartApplications;
 	PFAPPSTARTAPPLICATION2 IAppStartApplication2;
 	PFAPPSTARTAPPLICATION IAppStartApplication;
 	PFAPPSTOPAPPLICATIONS IAppStopApplications;
 	PFAPPSTOPAPPLICATION IAppStopApplication;
 	PFAPPEXITAPPLICATION IAppExitApplication;
 	PFAPPEXITAPPLICATION2 IAppExitApplication2;
 	PFAPPEXITAPPLICATIONS IAppExitApplications;
 	PFAPPDELETEAPPLICATION IAppDeleteApplication;
 	PFAPPDELETEAPPLICATIONS IAppDeleteApplications;
 	PFAPPDELETEBOOTPROJECT IAppDeleteBootproject;
 	PFAPPADDADDRDATASRV IAppAddAddrDataSrv;
 	PFAPPREMOVEADDRDATASRV IAppRemoveAddrDataSrv;
 	PFAPPGETFIRSTADDRDATASRV IAppGetFirstAddrDataSrv;
 	PFAPPGETNEXTADDRDATASRV IAppGetNextAddrDataSrv;
 	PFAPPCONSISTENCYCHECKBEGIN IAppConsistencyCheckBegin;
 	PFAPPCONSISTENCYCHECKEND IAppConsistencyCheckEnd;
 	PFAPPCONSISTENCYCHECKALL IAppConsistencyCheckAll;
 	PFAPPGETFIRSTAPP IAppGetFirstApp;
 	PFAPPGETNEXTAPP IAppGetNextApp;
 	PFAPPSTORERETAINSINFILE IAppStoreRetainsInFile;
 	PFAPPRESTORERETAINSFROMFILE IAppRestoreRetainsFromFile;
 	PFAPPRESTORERETAINSFROMFILE2 IAppRestoreRetainsFromFile2;
 	PFAPPSAVERETAINAREAS IAppSaveRetainAreas;
 	PFAPPSAVEALLRETAINAREAS IAppSaveAllRetainAreas;
 	PFAPPRESTORERETAINAREAS IAppRestoreRetainAreas;
 	PFAPPGETAREASIZE IAppGetAreaSize;
 	PFAPPGETAREAADDRESS IAppGetAreaAddress;
 	PFAPPGETSEGMENT IAppGetSegment;
 	PFAPPGETSEGMENTBYADDRESS IAppGetSegmentByAddress;
 	PFAPPGETSEGMENTSIZE IAppGetSegmentSize;
 	PFAPPGETSEGMENTADDRESS IAppGetSegmentAddress;
 	PFAPPREGISTERPROPACCESSFUNCTIONS IAppRegisterPropAccessFunctions;
 	PFAPPGETPROJECTINFORMATION IAppGetProjectInformation;
 	PFAPPGETBOOLEANPROPERTY IAppGetBooleanProperty;
 	PFAPPGETTEXTPROPERTY IAppGetTextProperty;
 	PFAPPGETNUMBERPROPERTY IAppGetNumberProperty;
 	PFAPPGETVERSIONPROPERTY IAppGetVersionProperty;
 	PFAPPGETCURRENT IAppGetCurrent;
 	PFAPPCHECKFILECONSISTENCY IAppCheckFileConsistency;
 	PFAPPGENERATEEXCEPTION IAppGenerateException;
 	PFAPPREGISTERBOOTPROJECT IAppRegisterBootproject;
 	PFAPPUNREGISTERBOOTPROJECT IAppUnregisterBootproject;
 	PFAPPCALLGETPROPERTY IAppCallGetProperty;
 	PFAPPCALLGETPROPERTY2 IAppCallGetProperty2;
 	PFAPPCALLGETPROPERTY2RELEASE IAppCallGetProperty2Release;
 	PFAPPCALLSETPROPERTY IAppCallSetProperty;
 	PFAPPGETAREAOFFSETBYADDRESS IAppGetAreaOffsetByAddress;
 	PFAPPSRVGETAPPLICATION IAppSrvGetApplication;
 	PFAPPHASACCESSRIGHTS IAppHasAccessRights;
 	PFAPPGETAPPLICATIONINFO IAppGetApplicationInfo;
 	PFAPPGETFIRSTCONFIGUREDBOOTPROJECT IAppGetFirstConfiguredBootproject;
 	PFAPPGETNEXTCONFIGUREDBOOTPROJECT IAppGetNextConfiguredBootproject;
 } ICmpApp_C;

#ifdef CPLUSPLUS
class ICmpApp : public IBase
{
	public:
		virtual APPLICATION* CDECL IAppCreateApplication(char* pszAppName, char* pszAppParentName, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IAppPrepareDownload(APPLICATION* pApp, int bOnlineChange, int bCreateBootproject) =0;
		virtual RTS_RESULT CDECL IAppAppendCode(APPLICATION *pApp, RTS_UI8 *pbyCode, RTS_SIZE ulCodeLen, RTS_SIZE ulCodeOffset, int bLoadBootproject) =0;
		virtual RTS_RESULT CDECL IAppCompleteDownload(APPLICATION* pApp, int bOnlineChange, BINTAGWRITER *pWriter) =0;
		virtual APPLICATION* CDECL IAppFindApplicationByName(char *pszAppName, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IAppNumOfActiveSessions(APPLICATION *pApp, RTS_UI32* pulNumSessions) =0;
		virtual APPLICATION* CDECL IAppFindApplicationByBootproject(char *pszBootprojectName, RTS_RESULT *pResult) =0;
		virtual APPLICATION* CDECL IAppFindApplicationBySessionId(RTS_UI32 ulSessionId, RTS_RESULT *pResult) =0;
		virtual APPLICATION* CDECL IAppFindApplicationById(int iId, RTS_RESULT *pResult) =0;
		virtual int CDECL IAppGetNumOfApplications(void) =0;
		virtual APPLICATION* CDECL IAppGetApplicationByIndex(int iIndex, RTS_RESULT *pResult) =0;
		virtual APPLICATION * CDECL IAppGetApplicationByAreaAddress(void *pAddress, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IAppGetAreaPointer(APPLICATION *pApp, int iArea, unsigned char **ppucArea) =0;
		virtual RTS_RESULT CDECL IAppGetAreaPointer2(APPLICATION *pApp, RTS_I32 iArea, RTS_UI8 **ppbyArea, RTS_SIZE *pulSize) =0;
		virtual RTS_RESULT CDECL IAppGetAreaPointerByType(char* pszAppName, int iArea, RTS_UI16 usType, unsigned char **ppucArea) =0;
		virtual RTS_RESULT CDECL IAppHasAddress(APPLICATION* pApp, RTS_VOID_FCTPTR pAddress) =0;
		virtual RTS_RESULT CDECL IAppIsProgramLoaded(APPLICATION *pApp, int* pbProgramLoaded) =0;
		virtual RTS_RESULT CDECL IAppSetProgramLoaded(APPLICATION *pApp, int bProgramLoaded) =0;
		virtual RTS_RESULT CDECL IAppSingleCycle(APPLICATION *pApp) =0;
		virtual RTS_RESULT CDECL IAppSetState(APPLICATION *pApp, unsigned long ulState) =0;
		virtual unsigned long CDECL IAppGetState(APPLICATION *pApp, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IAppSetOperatingState(APPLICATION *pApp, unsigned long ulOpState) =0;
		virtual RTS_RESULT CDECL IAppResetOperatingState(APPLICATION *pApp, unsigned long ulOpState) =0;
		virtual unsigned long CDECL IAppGetOperatingState(APPLICATION *pApp, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IAppSetCodeGuid(APPLICATION *pApp, RTS_GUID *pCodeGuid) =0;
		virtual RTS_RESULT CDECL IAppGetCodeGuid(APPLICATION *pApp, RTS_GUID *pCodeGuid) =0;
		virtual RTS_RESULT CDECL IAppSetDataGuid(APPLICATION *pApp, RTS_GUID *pDataGuid) =0;
		virtual RTS_RESULT CDECL IAppGetDataGuid(APPLICATION *pApp, RTS_GUID *pDataGuid) =0;
		virtual RTS_RESULT CDECL IAppGetBootprojectGuids(APPLICATION *pApp, RTS_GUID *pCodeGuid, RTS_GUID *pDataGuid) =0;
		virtual RTS_RESULT CDECL IAppExceptionHandler(APPLICATION *pApp, RTS_UI32 ulException, RegContext Context) =0;
		virtual RTS_RESULT CDECL IAppReset(APPLICATION* pApp, RTS_UI16 usResetOption, RTS_UI32 ulSessionId) =0;
		virtual RTS_RESULT CDECL IAppResetAllApplications(RTS_UI16 usResetOption) =0;
		virtual RTS_RESULT CDECL IAppLoadBootprojects(void) =0;
		virtual RTS_RESULT CDECL IAppStartBootprojects(void) =0;
		virtual RTS_RESULT CDECL IAppLoadBootproject(char *pszAppName, char *pszFilePath) =0;
		virtual RTS_RESULT CDECL IAppStartApplications(void) =0;
		virtual RTS_RESULT CDECL IAppStartApplication2(APPLICATION *pApp, RTS_UI32 ulStartReason) =0;
		virtual RTS_RESULT CDECL IAppStartApplication(APPLICATION *pApp) =0;
		virtual RTS_RESULT CDECL IAppStopApplications(RTS_UI32 ulTimeoutMs, RTS_UI32 ulStopReason) =0;
		virtual RTS_RESULT CDECL IAppStopApplication(APPLICATION *pApp, RTS_UI32 ulTimeoutMs, RTS_UI32 ulStopReason) =0;
		virtual RTS_RESULT CDECL IAppExitApplication(APPLICATION *pApp, RTS_UI32 ulExitReason) =0;
		virtual RTS_RESULT CDECL IAppExitApplication2(APPLICATION *pApp, RTS_UI32 ulExitReason, RTS_UI32 ulTimeoutMs) =0;
		virtual RTS_RESULT CDECL IAppExitApplications(RTS_UI32 ulExitReason, RTS_UI32 ulTimeoutMs) =0;
		virtual RTS_RESULT CDECL IAppDeleteApplication(APPLICATION *pApp, RTS_UI32 ulDeleteReason) =0;
		virtual RTS_RESULT CDECL IAppDeleteApplications(RTS_UI32 ulDeleteReason) =0;
		virtual RTS_RESULT CDECL IAppDeleteBootproject(APPLICATION *pApp) =0;
		virtual RTS_RESULT CDECL IAppAddAddrDataSrv(RTS_UI32 ulSessionId, PEERADDRESS *pPeerAddr) =0;
		virtual RTS_RESULT CDECL IAppRemoveAddrDataSrv(RTS_UI32 ulSessionId) =0;
		virtual RTS_HANDLE CDECL IAppGetFirstAddrDataSrv(PEERADDRESS **ppPeerAddr, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IAppGetNextAddrDataSrv(RTS_HANDLE hAddr, PEERADDRESS **ppPeerAddr, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IAppConsistencyCheckBegin(APPLICATION *pApp, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IAppConsistencyCheckEnd(RTS_HANDLE hConsistency) =0;
		virtual RTS_RESULT CDECL IAppConsistencyCheckAll(void) =0;
		virtual APPLICATION* CDECL IAppGetFirstApp(RTS_RESULT *pResult) =0;
		virtual APPLICATION* CDECL IAppGetNextApp(APPLICATION *pAppPrev, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IAppStoreRetainsInFile(APPLICATION *pApp, RTS_IEC_STRING* pszFileName) =0;
		virtual RTS_RESULT CDECL IAppRestoreRetainsFromFile(APPLICATION *pApp, RTS_IEC_STRING* pszFileName) =0;
		virtual RTS_RESULT CDECL IAppRestoreRetainsFromFile2(APPLICATION *pApp, RTS_IEC_STRING* pszFileName, int bGenerateException) =0;
		virtual RTS_RESULT CDECL IAppSaveRetainAreas(APPLICATION *pApp) =0;
		virtual RTS_RESULT CDECL IAppSaveAllRetainAreas(void) =0;
		virtual RTS_RESULT CDECL IAppRestoreRetainAreas(APPLICATION *pApp) =0;
		virtual RTS_SIZE CDECL IAppGetAreaSize(APPLICATION* pApp, RTS_UI16 usType, RTS_RESULT* pResult) =0;
		virtual RTS_UI8* CDECL IAppGetAreaAddress(APPLICATION* pApp, RTS_UI16 usType, RTS_RESULT* pResult) =0;
		virtual APP_MEMORY_SEGMENT * CDECL IAppGetSegment(APPLICATION* pApp, RTS_UI16 usType, RTS_RESULT *pResult) =0;
		virtual APP_MEMORY_SEGMENT * CDECL IAppGetSegmentByAddress(APPLICATION* pApp, void *pAddress, RTS_RESULT *pResult) =0;
		virtual RTS_SIZE CDECL IAppGetSegmentSize(APPLICATION* pApp, RTS_UI16 usType, RTS_RESULT* pResult) =0;
		virtual RTS_UI8 HUGEPTR * CDECL IAppGetSegmentAddress(APPLICATION* pApp, RTS_UI16 usType, RTS_RESULT* pResult) =0;
		virtual RTS_RESULT CDECL IAppRegisterPropAccessFunctions(APPLICATION* pApp, RTS_VOID_FCTPTR *ppfGetBooleanProperty, RTS_VOID_FCTPTR *ppfGetTextProperty, RTS_VOID_FCTPTR *ppfGetNumberProperty, RTS_VOID_FCTPTR *ppfGetVersionProperty) =0;
		virtual RTS_RESULT CDECL IAppGetProjectInformation(APPLICATION* pApp, PROJECT_INFO* pInfo) =0;
		virtual RTS_RESULT CDECL IAppGetBooleanProperty(APPLICATION *pApp, BOOLEANPROPERTY *pBooleanProperty) =0;
		virtual RTS_RESULT CDECL IAppGetTextProperty(APPLICATION *pApp, TEXTPROPERTY *pTextProperty) =0;
		virtual RTS_RESULT CDECL IAppGetNumberProperty(APPLICATION *pApp, NUMBERPROPERTY *pNumberProperty) =0;
		virtual RTS_RESULT CDECL IAppGetVersionProperty(APPLICATION *pApp, VERSIONPROPERTY *pVersionProperty) =0;
		virtual APPLICATION* CDECL IAppGetCurrent(RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IAppCheckFileConsistency(APPLICATION *pApp, RTS_RESULT *pBootprojectConsistency, RTS_RESULT *pArchiveConsistency) =0;
		virtual RTS_RESULT CDECL IAppGenerateException(APPLICATION *pApp, RTS_UI32 ulException) =0;
		virtual RTS_RESULT CDECL IAppRegisterBootproject(char *pszBootproject) =0;
		virtual RTS_RESULT CDECL IAppUnregisterBootproject(char *pszBootproject) =0;
		virtual RTS_RESULT CDECL IAppCallGetProperty(void *pInstance, RTS_VOID_FCTPTR *ppGetMethod, RTS_UI8 *pbyValue, RTS_SIZE ulSize) =0;
		virtual RTS_RESULT CDECL IAppCallGetProperty2(void *pInstance, RTS_VOID_FCTPTR *ppGetMethod, RTS_UI8 **ppbyValue, RTS_SIZE ulSize) =0;
		virtual RTS_RESULT CDECL IAppCallGetProperty2Release(RTS_UI8 *pbyValue) =0;
		virtual RTS_RESULT CDECL IAppCallSetProperty(void *pInstance, RTS_VOID_FCTPTR *ppSetMethod, RTS_UI8 *pbyValue, RTS_SIZE ulSize) =0;
		virtual RTS_RESULT CDECL IAppGetAreaOffsetByAddress(APPLICATION *pApp, RTS_UINTPTR ulAddress, RTS_UI16 *pusArea, RTS_SIZE *pulOffset) =0;
		virtual APPLICATION* CDECL IAppSrvGetApplication(PROTOCOL_DATA_UNIT *pduSendBuffer, BINTAGREADER *preader, BINTAGWRITER *pwriter, RTS_UI32 ulSessionId) =0;
		virtual RTS_RESULT CDECL IAppHasAccessRights(char *pszApplication, char *pszObject, RTS_UI32 ulRequestedRights, RTS_UI32 ulSessionId, BINTAGWRITER *pWriter) =0;
		virtual APPLICATION_INFO * CDECL IAppGetApplicationInfo(APPLICATION *pApp, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IAppGetFirstConfiguredBootproject(char *pszAppName, RTS_I32 nMaxAppName, RTS_BOOL bCheckFile, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IAppGetNextConfiguredBootproject(RTS_HANDLE hPrev, char *pszAppName, RTS_I32 nMaxAppName, RTS_BOOL bCheckFile, RTS_RESULT *pResult) =0;
};
	#ifndef ITF_CmpApp
		#define ITF_CmpApp static ICmpApp *pICmpApp = NULL;
	#endif
	#define EXTITF_CmpApp
#else	/*CPLUSPLUS*/
	typedef ICmpApp_C		ICmpApp;
	#ifndef ITF_CmpApp
		#define ITF_CmpApp
	#endif
	#define EXTITF_CmpApp
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPAPPITF_H_*/
