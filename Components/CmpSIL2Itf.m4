/**
 * <interfacename>CmpSIL2</interfacename>
 * <description> 
 * <p>This is the interface of the SIL2 component. The CmpSIL2 is used to implement several
 *    savety related feates, which are (in this form) only necessary in safety PLCs, following
 *    the Safety SIL2 concept of 3S.</p>
 * <p>These features include the following:</p>
 * <ul>
 *   <li>Safe loading of a bootproject</li>
 *   <li>Selftest Hooks</li>
 *   <li>Switch between safe- and unsafe contexts</li>
 *   <li>Safe logger interface</li>
 *   <li>Check functions, to determine the current context and operation mode</li>
 *   <li>Control Flow</li>
 * </ul>
 * <p>1) Bootproject</p>
 * <p>In CoDeSys Control SIL2, the bootproject is always loaded from flash,
 *    and from there, only in the "compact download format", as it is used
 *    by CmpAppEmbedded. In a standard CoDeSys Control Runtime, the bootproject
 *    is implicitely loaded, by CmpApp/CmpAppEmbedded within an init hook, that
 *    is executed during the call of CMInit() at startup.</p>
 * <p>In CoDeSys Control SIL2, this implicite loading is deactivated. Instead, the
 *    OEM customer has to call SIL2AppBoot() after CMInit().</p>
 * <p>The reason for this constraint is, that the function SIL2AppBoot() can make
 *    sure that the application is loaded with the constraints that are defined
 *    for a CoDeSys Control SIL2 system. Additionally, it is more safe to load 
 *    the application after system startup is completed, because no unsafe init code
 *    is executed anymore after the application is loaded.</p>
 * <p>2) Selftest Hooks</p>
 * <p>Virtually every safety system needs some kind of self tests, which are either
 *    executed in every Safety Process Cycle, or within a specific time frame in
 *    the background.</p>
 * <p>While the selftests in the background need to be seperated into small chunks,
 *    which are executed in the COMM-Cycle (= Super Loop), the selftests at startup
 *    need to be executed at once, to prohibit the execution of the application when
 *    there is an error in the hardware or firmware.</p>
 * <p>3) Switches between safe, unsafe and system contexts</p>
 * <p>The current execution context is managed by the OEM customer. But, to have
 *    a clear interface to switch between the contexts in a higher level, and to
 *    be able to execute unsafe code when coming from a safe context.</p>
 * <p>4) Safe logger interface</p>
 * <p>The standard monitoring of CoDeSys as well as the standard logger are not safe.
 *    Therefore, they may not be usable for the Endcustomer in some circumstances.</p>
 * <p>To have a safe interface to transport messages and data from the CoDeSys Control
 *    Runtiem to the programming and debugging system, the component CmpSIL2 provides
 *    it's own logger interface, which secures the data from unintended modifications
 *    with a checksum.</p>
 * <p>4) Check functions</p>
 * <p>The CmpSIL2 interface specifies a few functions, which need to be implemented by
 *    the OEM customer to determine the current context or operation mode. This is mainly
 *    necessary to restrict the execution of several functions, but there might also
 *    be other use-cases in which those functions migth be helpful for the OEM himself.</p>
 * <p>5) Control Flow</p>
 * <p>The component CmpSIL2, provides a control flow logging mechanism, that is used
 *    for diagnostic purposes, to check the control flow of the IEC tasks, before they
 *    are passing their outputs to the I/O drivers.</p>
 * <p>This interface is generically designed, and may therefore also be used by the OEM
 *    customer, to log and check his own control flow of his subsystems.</p>
 * <pre>
 * Example usage:
 * SIL2_CONTROLFLOW s_IoMgrControlFlow[3];
 * SIL2ControlFlowLog(s_IoMgrControlFlow, 0); 
 * SIL2ControlFlowLog(s_IoMgrControlFlow, 1); 
 * SIL2ControlFlowLog(s_IoMgrControlFlow, 2); 
 * SIL2ControlFlowCheck(s_IoMgrControlFlow, 3);
 * </pre>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpSIL2')

typedef RTS_UI32 RTS_SIL2_EXCEPTION;
typedef RTS_UI32 RTS_SIL2_OPMODE;
typedef RTS_UI32 RTS_SIL2_ADDRESSSTATE;

/**
 * <category>Buffer sizes</category>
 * <description>Specifies the maximum logable string size.</description>
 */
#ifndef CMPSIL2_LOGADD_MAX_STRLEN
	#define CMPSIL2_LOGADD_MAX_STRLEN 36
#endif

/**
 * <category>Buffer sizes</category>
 * <description>Specifies the maximum number of strings.</description>
 */
#ifndef CMPSIL2_LOGADD_MAX_ENTRIES
	#define CMPSIL2_LOGADD_MAX_ENTRIES 50
#endif

#define RTS_SIL2_OPMODE_SAFE 					0xAABB
#define RTS_SIL2_OPMODE_DEBUG 					0x7788

#define RTS_SIL2_ADDRESS_SAFE 					0xCCDD
#define RTS_SIL2_ADDRESS_UNSAFE					0x5566
#define RTS_SIL2_OPMODE_ERROR					0xFFFF

#define RTS_SIL2_CALLERCTX_SAFE					0xBBAA
#define RTS_SIL2_CALLERCTX_UNSAFE				0xDDCC
#define RTS_SIL2_CALLERCTX_SYSTEM				0xFFEE
#define RTS_SIL2_CALLERCTX_ERROR				0xFFFF

/**
 * <category>Exceptions</category>
 * <description>Exceptions: Runtime has encountered an error in safety mode and passes the info to an OEM Interface function</description>
 */
/* unspecified error */
#define RTS_SIL2_FAIL_GENERAL						0x01 	/* unspecified Error */

/* while loading bootproject*/
#define RTS_SIL2_EXCEPTION_LOADBOOTPROJECT			0x10	/* unspecified Error while Loading Bootproject */
#define RTS_SIL2_EXCEPTION_BOOTPROJECT_INVALID		0x11	/* Bootproject Format does not match */
#define RTS_SIL2_EXCEPTION_COMPACTPREPARECODE		0x12	/* Error while Loading Bootproject, Creating of IEC Application */
#define RTS_SIL2_EXCEPTION_COMPACTFINISH			0x13	/* Error while Setting up IEC Application, Calling IEC init Code (global init...) */
#define RTS_SIL2_EXCEPTION_EXTREFS					0x14	/* Error while Setting up external References */
#define RTS_SIL2_EXCEPTION_RUNAFTERDOWNLOAD			0x15	/* Error while SIL2AppRunAfterDownloadCode */
#define RTS_SIL2_EXCEPTION_MEMORY					0x16	/* Error regarding the Memory at Bootproject start */
#define RTS_SIL2_EXCEPTION_RUNTIME_INIT				0x17	/* Error while CMInit2 */


/* while operational */
#define RTS_SIL2_EXCEPTION_SCHED_WD					0x20	/* Scheduler Watchdog Exception */
#define RTS_SIL2_EXCEPTION_CRC_CYCLIC				0x21	/* Cyclic Check of CRC was wrong */
#define RTS_SIL2_EXCEPTION_CRC_COMPLETE				0x22	/* Complete Check of CRC was wrong */
#define RTS_SIL2_EXCEPTION_CRC_INIT					0x23	/* Init of CRC Check wrong */
#define RTS_SIL2_EXCEPTION_LIFE_COUNTER				0x24	/* Not all Components were called in safe Hook */
#define RTS_SIL2_EXCEPTION_CALLERCONTEXT			0x25	/* Caller Context Check was wrong */

/* By Default ignore the SIL2 attribute */
#ifndef RTS_SIL2_ATTRIBUTE
	#define RTS_SIL2_ATTRIBUTE
#endif

/* Define the default list of components, that need a safety COMM-Cycle */
#ifndef RTS_SAFETY_COMPONENTS
	int CmpScheduleTimer__Entry(INIT_STRUCT *pInitStruct);
	int CmpSIL2__Entry(INIT_STRUCT *pInitStruct);
	int IoDrvUnsafeBridge__Entry(INIT_STRUCT *pInitStruct);
	#define RTS_SAFETY_COMPONENTS \
		{"CmpScheduleTimer", CmpScheduleTimer__Entry, 1}, \
		{"CmpSIL2", CmpSIL2__Entry, 1}, \
		{"IoDrvUnsafeBridge", IoDrvUnsafeBridge__Entry, 1}, \
		{NULL, NULL, 0}

#endif

/**
 * <SIL2/>
 * <category>Typedef</category>
 * <description><p>Buffertype for Control Flow mechanism</p>
 * </description>
 */
typedef struct SIL2_CONTROLFLOW
{
	RTS_UI32 uiPattern;
	RTS_UI32 uiCRC;
} SIL2_CONTROLFLOW;

#define SIL2_NUM_CONTROL_FLOW_POINTS 3

#ifdef RTS_SIL2
extern SIL2_CONTROLFLOW g_ControlFlowIecTasks[NUM_OF_STATIC_IEC_TASKS][SIL2_NUM_CONTROL_FLOW_POINTS];
#endif

/**
 * <SIL2/>
 * <category>Typedef</category>
 * <description><p>SIL2 life counter for safe comm cycle hook</p>
 * </description>
 */
#ifdef RTS_SIL2
extern RTS_UI32 g_RTS_SIL2_Cycle_LifeCounter_CmpSIL2;
#endif




#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OEM specific module */
RTS_RESULT CDECL CmpSIL2OEMInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL CmpSIL2OEMHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);



/**
 * <description>
 * <p>Function to load and start a Bootproject from Flash</p>
 * <p>Application Note: The caller must ensure that this function is called only within a safe context!</p>
 * <p>The SIL2 Component only loads bootprojects, which are in the "compact download format" format, and those only from flash.
 * This format includes an checksum to check the consistency of that bootproject.
 * Before loading the bootproject the CmpSIL2 checks this CRC to make sure that the bootproject was not corrupted after CoDeSys Programming System created it.
 * As the data-initialization is done from bootproject-code, the CRC also covers the data in the bootproject.
 * The main steps of loading the bootproject are:
 * </p>
 * <ul>
 *   <li>Create an application with the given name</li>
 *   <li>Get the Startaddress of the Bootproject in Flash</li>
 *   <li>Allocate Application Areas (Code - Flash, Data - SysMemAllocArea())</li>
 *   <li>Check the Bootproject (Bootproject Type, Target ID, Type, Version) and create GUIDs</li>
 *   <li>Call the Data-Initialization-Code from the bootproject (Relocation, Code Init, Download POU, Global Init, Global Exit) </li>
 *   <li>Set the Application State to loaded</li>
 *   <li>If everything is correct, start the Application</li>
 *	</ul>
 * <p>Function has no function parameter, but behavior is also dependant on state of bootproject</p>
 * </description> 
 * <parampseudo name="bExtFuncsAreValid" type="IN" range="[TRUE,FALSE]">Specifies if the application references an unsafe or non-existent external function.</parampseudo>
 * <parampseudo name="bAreaIsValid" type="IN" range="[TRUE,FALSE]">Specifies if the Areas of the bootapplication are valid or not.</parampseudo>
 * <parampseudo name="Bootproject.CRC" type="IN" range="[BOOTP_NO_PROJECT,BOOTP_VALID_CRC,BOOTP_INVALID_CRC]">Bootproject in flash, States: valid CRC, invalid CRC </parampseudo>
 * <parampseudo name="Bootproject.Code" type="IN" range="[INVALID_AREA,INVALID_DEV_VERSION,RELOC_VALID,RELOC_IDLE,RELOC_EXCEPTION,CODEINIT_VALID,CODEINIT_IDLE,CODEINIT_EXCEPTION,GLOBALINIT_VALID,GLOBALINIT_IDLE,GLOBALINIT_EXCEPTION,DOWNLOAD_POU_VALID,DOWNLOAD_POU_IDLE,DOWNLOAD_POU_EXCEPTION,GLOBALEXIT_VALID,GLOBALEXIT_IDLE,GLOBALEXIT_EXCEPTION]">valid Code, idle Code (harmless), invalid Code producing Exception</parampseudo>  
 * <parampseudo name="Bootproject.TargetType" type="IN" range="[INVALID_TARGET_TYPE,VALID_TARGET_TYPE]">Target Type</parampseudo>  
 * <parampseudo name="Bootproject.TargetID" type="IN" range="[INVALID_TARGET_ID,VALID_TARGET_ID]">Target ID</parampseudo>  
 * <parampseudo name="bExceptionGenerated" type="OUT" range="[FALSE,TRUE]">TRUE, when an exception occured, during execution</parampseudo>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Load Bootproject successful</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NO_OBJECT">No Bootproject in Flash</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Error while loading Bootapp (memory area could not be allocated, CRC was invalid, or an external function, which was referenced by the application, is not listed in the list of safe functions)</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_TYPE_MISMATCH">wrong DeviceType in Bootproject</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_ID_MISMATCH">wrong DeviceId in Bootproject</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_VERSION_MISMATCH">wrong DeviceVersion in Bootproject</errorcode>
 * <result>Result of loading bootproject</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SIL2AppBoot', `(void)')


/**
 * <description>sil2checkcallercontext</description>
 * <SIL2/>
 */
typedef struct tagsil2checkcallercontext_struct
{
	RTS_IEC_UDINT udiCallerContextExpected;	/* VAR_INPUT */
	RTS_IEC_RESULT SIL2CheckCallerContext;	/* VAR_OUTPUT */
} sil2checkcallercontext_struct;

/**
 * <description>
 * <p>Function to check the current Caller Context of the Runtime</p>
 * <p>Expected Context is checked vs the current context, and an exception is thrown if they are different.</p>
 * </description> 
 * <param name="ulCallerContextExpected" type="IN" range="[RTS_SIL2_CALLERCTX_SAFE,RTS_SIL2_CALLERCTX_UNSAFE,RTS_SIL2_CALLERCTX_ERROR]">Expected Context, that is checked against current context.</param>
 * <parampseudo name="bSafeContext" type="IN" range="[TRUE,FALSE]">Specifies if the context is safe or unsafe.</parampseudo>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Context is ok</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Context could not be checked successfully, an internal error occured.</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_EXCEPTION">Contexts are different</errorcode> 
 * <result>Returns if comparision was ok or not, or if problem occured.</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SIL2CheckCallerContext', `(RTS_UI32 ulCallerContextExpected)')
DEF_API(`void',`CDECL',`sil2checkcallercontext',`(sil2checkcallercontext_struct *p)',1,0x829BB451,0x03050400)


/**
 * <description>
 * <p>Function to copy the current CodeGuid to a given location (by Pointer)</p>
 * <p>Size is always 16 BYTES! The caller must provided this much space.</p>
 * </description> 
 * <param name="pDstCodeGuid" type="IN" range="[NULL,VALID_PDSTCODEGUID]">Pointer where the guid should be copied to.</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Copy was ok</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Could not get requested Guid.</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Pointer invalid</errorcode>
 * <SIL2/>
 */
typedef struct tagsil2copycodeguid_struct
{
	RTS_IEC_BYTE *pDstCodeGuid;			/* VAR_INPUT */
	RTS_IEC_RESULT SIL2CopyCodeGuid;	/* VAR_OUTPUT */
} sil2copycodeguid_struct;

DEF_API(`void',`CDECL',`sil2copycodeguid',`(sil2copycodeguid_struct *p)',1,0x638D4565,0x03050400)

/**
 * <description>
 * <p>Function to copy the current DataGuid to a given location (by Pointer)</p>
 * <p>Size is always 16 BYTES! The caller must provided this much space.</p>
 * </description> 
 * <param name="pDstCodeGuid" type="IN" range="[NULL,VALID_PDSTDATAGUID]">Pointer where the guid should be copied to.</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Copy was ok</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Could not get requested Guid.</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Pointer invalid</errorcode>
 * <SIL2/>
 */
typedef struct tagsil2copydataguid_struct
{
	RTS_IEC_BYTE *pDstDataGuid;			/* VAR_INPUT */
	RTS_IEC_RESULT SIL2CopyDataGuid;	/* VAR_OUTPUT */
} sil2copydataguid_struct;

DEF_API(`void',`CDECL',`sil2copydataguid',`(sil2copydataguid_struct *p)',1,0x44F9CD8A,0x03050400)



/**
 * <description>
 * <p>Function to set Runtime to DebugMode</p>
 * <p>This function is called from save context after receiving an "EnterDebugMode" online service to set runtime to debug mode</p>
 * <p>As this function is only called from within save context no further check is required</p>
 * </description> 
 * <parampseudo name="SIL2OpMode" type="IN" range="[RTS_SIL2_OPMODE_SAFE,RTS_SIL2_OPMODE_DEBUG]">Specifies the current operation mode of the PLC</parampseudo>
 * <parampseudo name="SIL2PollOnlineService" type="IN" range="[TRUE,FALSE]">Specifies if the function PollOnlineServices is called or not</parampseudo>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Runtime could be set to Debugmode</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NO_CHANGE">Runtime was already set to Debugmode</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Runtime could not be set to Debugmode</errorcode>
 * <result>Result of Setting Mode</result>
 * <SIL2/>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SIL2OEMEnterDebugMode', `(void)')

/**
 * <description>sil2oemexception</description>
 * <SIL2/>
 */
typedef struct tagsil2oemexception_struct
{
	RTS_IEC_UDINT udiException;			/* VAR_INPUT */
	RTS_IEC_RESULT SIL2OEMException;	/* VAR_OUTPUT */
} sil2oemexception_struct;

/**
 * <description>
 * <p>Function to set Runtime into Exception-Mode</p> 
 * <p>Whenever the runtime detects invalid behaviour, values or states, it calls this function with a specific Exception Code.</p>
 * <p>Depending on the implementation this function may not return!</p>
 * </description> 
 * <param name="Exception" type="IN" range="[RTS_SIL2_EXCEPTION_LOADBOOTPROJECT,RTS_SIL2_EXCEPTION_BOOTPROJECT_INVALID,RTS_SIL2_EXCEPTION_COMPACTPREPARECODE,RTS_SIL2_EXCEPTION_COMPACTFINISH,RTS_SIL2_EXCEPTION_EXTREFS,RTS_SIL2_EXCEPTION_RUNAFTERDOWNLOAD,RTS_SIL2_EXCEPTION_MEMORY,RTS_SIL2_EXCEPTION_RUNTIME_INIT,RTS_SIL2_EXCEPTION_SCHED_WD,RTS_SIL2_EXCEPTION_CRC_CYCLIC,RTS_SIL2_EXCEPTION_CRC_COMPLETE,RTS_SIL2_EXCEPTION_CRC_INIT,RTS_SIL2_EXCEPTION_LIFE_COUNTER,RTS_SIL2_EXCEPTION_CALLERCONTEXT]">Exception Code</param>
 * <parampseudo name="bExceptionGenerated" type="OUT" range="[FALSE,TRUE]">TRUE, when an exception occured, during execution</parampseudo>  
 */
DEF_ITF_API(`void', `CDECL', `SIL2OEMException', `(RTS_SIL2_EXCEPTION Exception)')
DEF_API(`void',`CDECL',`sil2oemexception',`(sil2oemexception_struct *p)',1,0xA54830DE,0x03050400)

/**
 * <description>sil2addlog</description>
 * <SIL2/>
 */
typedef struct tagsil2addlog_struct
{
	RTS_IEC_STRING sMessage[81];		/* VAR_INPUT */
	RTS_IEC_UDINT udiLogId;				/* VAR_INPUT */
	RTS_IEC_RESULT SIL2AddLog;			/* VAR_OUTPUT */
} sil2addlog_struct;

/**
 * <description>
 * <p>Function to add a secure Logentry</p> 
 * <p>These secure logentries don't use the standard Logging mechanism! With this function it is possible to add secure messages to a Messagequeue within CmpSIL2.
 *    This Messagequeue can be fetched by an Onlineservice from the SIL2 Programmingsystemplugin. The messages are stored and transmitted with a CRC to provide a secure logging.
 *    The maximal length of the string is restricted (CMPSIL2_LOGADD_MAX_STRLEN). 
 * </p>
 *
 * </description> 
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Entry could not be added to log</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Message pointer was NULL, or message was longer than CMPSIL2_LOGADD_MAX_STRLEN</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Entry could be added to log correctly</errorcode> 
 * <param name="pszMessage" type="IN" range="[NULL,VALID_STRING,LONG_STRING]">String containing the message, must not be longer than CMPSIL2_LOGADD_MAX_STRLEN</param>
 * <param name="ulLogId" type="IN" range="[RTS_RANGE_OF_ULONG]">Id for own Identification purposes</param>
 * <result>Result of adding secure Logentry</result> 
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SIL2AddLog', `(char* pszMessage,RTS_UI32 ulLogId)')
DEF_API(`void',`CDECL',`sil2addlog',`(sil2addlog_struct *p)',1,0x742BC625,0x03050400)

/**
 * <description>sil2oemgetoperationmode</description>
 * <SIL2/>
 */
typedef struct tagsil2oemgetoperationmode_struct
{
	RTS_IEC_UDINT SIL2OEMGetOperationMode;	/* VAR_OUTPUT */
} sil2oemgetoperationmode_struct;

/**
 * <description>
 * <p>Function to get the Operationmode of the Runtime</p>
 * <p>Returns RTS_SIL2_OPMODE_DEBUG or RTS_SIL2_OPMODE_SAFE depending on Operationmode, returns RTS_SIL2_OPMODE_ERROR if error occured or if in unknown state</p>
 * </description> 
 * <parampseudo name="SIL2OpMode" type="IN" range="[RTS_SIL2_OPMODE_SAFE,RTS_SIL2_OPMODE_DEBUG]">Specifies the current operation mode of the PLC</parampseudo>
 * <result>Returns SIL2 Operation Mode: RTS_SIL2_OPMODE_DEBUG or RTS_SIL2_OPMODE_SAFE if operation was successful, RTS_SIL2_OPMODE_ERROR if error occured or if in unknown state!</result>
 */
DEF_ITF_API(`RTS_SIL2_OPMODE', `CDECL', `SIL2OEMGetOperationMode', `(void)')
DEF_API(`void',`CDECL',`sil2oemgetoperationmode',`(sil2oemgetoperationmode_struct *p)',1,0xB292F534,0x03050400)


/**
 * <description>sil2oemgetcallercontext</description>
 * <SIL2/>
 */
typedef struct tagsil2oemgetcallercontext_struct
{
	RTS_IEC_UDINT SIL2OEMGetCallerContext;	/* VAR_OUTPUT */
} sil2oemgetcallercontext_struct;

/**
 * <description>
 * <p>Function to get the current Caller Context of the Runtime</p>
 * <p>Expected return the current context, and an exception is thrown if they are different.</p>
 * </description> 
 * <parampseudo name="bDebugMode" type="IN" range="[TRUE,FALSE]">Specifies if run in debug mode or not.</parampseudo>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Context is ok</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Context could not be checked successfully, an internal error occured.</errorcode>
 * <result>Returns if comparision was ok or not.</result>
 */                                                                                                                                                                                             
DEF_ITF_API(`RTS_UI32', `CDECL', `SIL2OEMGetCallerContext', `(void)')
DEF_API(`void',`CDECL',`sil2oemgetcallercontext',`(sil2oemgetcallercontext_struct *p)',1,0x2A37A2FD,0x03050400)

/**
 * <description>sil2oemgetmemorystate</description>
 * <SIL2/>
 */
typedef struct tagsil2oemgetmemorystate_struct
{
	RTS_IEC_BYTE *pAddress;				/* VAR_INPUT */
	RTS_IEC_UDINT udiLength;			/* VAR_INPUT */
	RTS_IEC_UDINT SIL2OEMGetMemoryState;	/* VAR_OUTPUT */
} sil2oemgetmemorystate_struct;

/**
 * <description>
 * <p>Function to get the MemoryState (safe/unsafe) for a specific Memoryrange </p>
 * <p>The Addressrange where pAddress points to with the length of ulLength is checked and the corresponding RTS_SIL2_ADDRESSSTATE is returned: RTS_SIL2_ADDRESS_SAFE or RTS_SIL2_ADDRESS_UNSAFE</p>
 * </description> 
 * <param name="pAddress" type="IN" range="[NULL,SAFE_POINTER,UNSAFE_POINTER]">Pointer to Addressrange to check for Addressstate</param>
 * <param name="ulLength" type="IN" range="[0,VALID_POINTER_SIZE,ULONG_MAX]">Length of Addressrange to check for Addressstate</param>
 * <errorcode name="RTS_SIL2_ADDRESSSTATE Result" type="RTS_SIL2_ADDRESS_SAFE">This Addressrange is in Safe Range</errorcode>
 * <errorcode name="RTS_SIL2_ADDRESSSTATE Result" type="RTS_SIL2_ADDRESS_UNSAFE">This Addressrange is in Unsafe Range</errorcode>
 * <result>Result for Memoryaddress check</result>
 */
DEF_ITF_API(`RTS_SIL2_ADDRESSSTATE', `CDECL', `SIL2OEMGetMemoryState', `(RTS_UI8 *pAddress, RTS_UI32 ulLength)')
DEF_API(`void',`CDECL',`sil2oemgetmemorystate',`(sil2oemgetmemorystate_struct *p)',1,0x2FE5CB14,0x03050400)

/**
 * <description>sil2oemstackisvalid</description>
 * <SIL2/>
 */
typedef struct tagsil2oemstackisvalid_struct
{
	RTS_IEC_RESULT SIL2OEMStackIsValid;	/* VAR_OUTPUT */
} sil2oemstackisvalid_struct;

/**
 * <description>
 * <p>Function to check if Stack is Valid</p>
 * <p>This function is called before entering the Safemode, it returns ERR_OK if the stack is valid, and ERR_FAILED if an error occured or was detected!</p>
 * </description> 
 * <parampseudo name="bStackIsValid" type="IN" range="[FALSE,TRUE]">Define if the current stack is valid.</parampseudo>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Check stack was successful</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Check stack was not successful</errorcode>
 * <result>Result of Stackcheck</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SIL2OEMStackIsValid', `(void)')
DEF_API(`void',`CDECL',`sil2oemstackisvalid',`(sil2oemstackisvalid_struct *p)',1,0x56A27207,0x03050400)

/**
 * <description>
 * <p>Function to delegate a Non-Safety Job</p>
 * <p>This function can be used to delegate a non-safety job from within the safe-context to be executed from the Unsafe context</p>
 * <p>The function pfNonSafetyJob has to be called from Unsafe Context with pParam as argument</p>
 * </description> 
 * <param name="pfNonSafetyJob" type="IN" range="[NULL,VALID_NONSAFETY_FUNCTION]">Function Pointer to NonSafety Job</param>
 * <param name="pParam" type="IN" range="[NULL,VALID_POINTER]">Pointer to Parameter for NonSafety Job</param>
 * <parampseudo name="uiCallerCtx" type="IN" range="[RTS_SIL2_CALLERCTX_SAFE,RTS_SIL2_CALLERCTX_UNSAFE]">Specifies the context of the caller</parampseudo>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Job was done correctly</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Job could not be done</errorcode>
 * <result>Result of delegating a Non-Safety Job</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SIL2OEMExecuteNonSafetyJob', `(void (*pfNonSafetyJob)(void * pParam),void * pParam)')

/**
 * <description>sil2executenonsafetyjob</description>
 * <SIL2/>
 */
typedef struct tagsil2executenonsafetyjob_struct
{
	RTS_IEC_BYTE *pfNonSafetyJob;		/* VAR_INPUT */
	RTS_IEC_BYTE *pParam;			/* VAR_INPUT */
	RTS_IEC_ULINT ulSize;			/* VAR_INPUT */
	RTS_IEC_RESULT SIL2ExecuteNonSafetyJob;	/* VAR_OUTPUT */
} sil2executenonsafetyjob_struct;

/**
 * <description>
 * <p>Function to delegate a Non-Safety Job</p>
 * <p>This function behaves the exact same way as SIL2OEMExecuteNonSafetyJob(), but
 * it provides also the size of the parameter to the function. This way, the OEM customer
 * is able to copy the parameter temporarily to a shared memory, message box or a different stack.</p>
 * </description> 
 * <param name="pfNonSafetyJob" type="IN" range="[NULL,VALID_NONSAFETY_FUNCTION]">Function Pointer to NonSafety Job</param>
 * <param name="pParam" type="IN" range="[NULL,VALID_POINTER]">Pointer to Parameter for NonSafety Job</param>
 * <param name="iSize" type="IN" range="[0..VALID_PARAM_SIZE]">Size of Parameter for NonSafety Job</param>
 * <parampseudo name="uiCallerCtx" type="IN" range="[RTS_SIL2_CALLERCTX_SAFE,RTS_SIL2_CALLERCTX_UNSAFE]">Specifies the context of the caller</parampseudo>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Job was done correctly</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">A parameter was passed, but the size is 0 or parameter is NULL and size > 0</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Job could not be done</errorcode>
 * <result>Result of delegating a Non-Safety Job</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SIL2OEMExecuteNonSafetyJob2', `(void (*pfNonSafetyJob)(void * pParam),void * pParam,RTS_SIZE iSize)')
DEF_API(`void',`CDECL',`sil2executenonsafetyjob',`(sil2executenonsafetyjob_struct *p)',1,0x142EECAE,0x03050400)


/**
 * <description>
 * <p>Function to log the program flow</p>
 * <p>The caller is responsible for providing buffer for storing the control flow data. After having logged, the function
 * SIL2ControlFlowCheck can be used to check if all control positions have been logged in the correct order. </p>
 * <p>The Log IDs may not be out of range of the specified log buffer.</p>
 * </description> 
 * <param name="pControlFlow" type="IN" range="[NULL,VALID_CONTROLFLOW_BUFFER]">Buffer to store control flow data in</param>
 * <param name="uiCurrID" type="IN" range="[0..NUM_OF_CONTROLFLOW_LOGENTRIES]">Current Log Nr</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">successfully added logentry to control flow</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOBUFFER">pControlFlow was NULL</errorcode> 
 * <result>Result of Log to control-flow</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SIL2ControlFlowLog', `(SIL2_CONTROLFLOW* pControlFlow, RTS_UI8 uiCurrID)')

/**
 * <description>
 * <p>Function to check the previously logged program flow</p>
 * <p>The caller is responsible for providing buffer for storing the control flow data. After having logged, the function
 * SIL2ControlFlowCheck can be used to check if all control positions have been logged in the correct order. </p>
 * <p>The number of IDs may not be out of range of the specified log buffer.</p>
 * </description> 
 * <param name="pControlFlow" type="IN" range="[NULL,VALID_CONTROLFLOW_BUFFER,INVALID_CONTROLFLOW_BUFFER]">Buffer to store control flow data in</param>
 * <param name="uiTotalNr" type="IN" range="[0,NUM_OF_CONTROLFLOW_LOGENTRIES]">Nr of Logs expected or to check</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">all logentries were added in the correct order, check successfull</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_OUT_OF_LIMITS">uiTotalNr exceeds buffersize</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOBUFFER">pControlFlow is NULL</errorcode> 
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">check failed, order wrong or not all logentries correct</errorcode>
 * <result>Result of control-flow check</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SIL2ControlFlowCheck', `(SIL2_CONTROLFLOW* pControlFlow, RTS_UI8 uiTotalNr)')

#ifdef __cplusplus
}
#endif
