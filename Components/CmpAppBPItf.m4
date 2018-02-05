/**
 * <interfacename>CmpAppBP</interfacename>
 * <description> 
 *	This is the interface of the IEC application manager to handle breakpoints
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpAppBP')

REF_ITF(`CmpAppItf.m4')
REF_ITF(`CmpSrvItf.m4')
REF_ITF(`CmpIecTaskItf.m4')

#ifdef CMPAPP_NOTIMPLEMENTED
	#ifndef CMPAPPBP_NOTIMPLEMENTED
		#define CMPAPPBP_NOTIMPLEMENTED
	#endif
#endif

/**
 * <category>Compiler switch</category>
 * <description>
 *	Compiler switches to enable/disable single features in the component.
 * </description>
 * <element name="APPBP_DISABLE_FLOWCONTROL">Switch to disable the feature FlowControl. Can be used to reduce code size.</element>
 * <element name="APPBP_SHOW_ALWAYS_SOURCE_POSITION">Switch to enable showing the actual source position in the programing system for
 *				long running tasks. This makes only sense for very long running tasks that are used blocking calls or sleep functions.</element>
 */


/**
 * <category>Static defines</category>
 * <description>Length of breakpoint list that is allocated static in the application object</description>
 */
#ifndef APP_STATIC_BP_ENTRIES
	#define APP_STATIC_BP_ENTRIES			20
#endif

/**
 * <category>Static defines</category>
 * <description>Length of breakpoint list that is allocated static in the application object</description>
 */
#ifndef APP_STATIC_FLOW_ENTRIES
	#define APP_STATIC_FLOW_ENTRIES			20
#endif

/**
 * <category>Static defines</category>
 * <description>Maximum length of breakpoint opcode</description>
 */
#ifndef APP_MAX_BP_OPCODE_SIZE
	#define APP_MAX_BP_OPCODE_SIZE			8
#endif

/**
 * <category>Static defines</category>
 * <description>Maximum length of one breakpoint condition</description>
 */
#ifndef APP_MAX_BP_CONDITION_SIZE
	#define APP_MAX_BP_CONDITION_SIZE			300
#endif

/**
 * <category>Static defines</category>
 * <description>Maximum size of interpreter code for one breakpoint</description>
 */
#ifndef APP_MAX_BP_INTERP_CODE_SIZE
	#define APP_MAX_BP_INTERP_CODE_SIZE			1000
#endif

/**
 * <category>Static defines</category>
 * <description>Maximum length of flow service buffer to hold one complete flow service</description>
 */
#ifndef APPBP_MAX_FLOW_SERVICE_LEN
	#define APPBP_MAX_FLOW_SERVICE_LEN		10000
#endif

/**
 * <category>Static defines</category>
 * <description>Maximum size of the stack used in CmpMonitor2 for executing Executionpoints</description>
 */
#ifndef EXECUTIONPOINT_STACK_SIZE
	#define EXECUTIONPOINT_STACK_SIZE 4096
#endif


/**
 * <category>Code patch event flags</category>
 * <description>Flags of code patch event</description>
 * <element name="APPBP_FLAG_BEFORE_CODE_PATCH" type="IN">Is called before patching the code</element>
 * <element name="APPBP_FLAG_AFTER_CODE_PATCH" type="IN">Is called after patching the code</element>
 * <element name="APPBP_FLAG_CODE_PATCHED" type="OUT">The event handler mark this flag to specify, that the code is patched in the event handler! So no default patching is done.</element>
 */
#define APPBP_FLAG_BEFORE_CODE_PATCH	0x00000001
#define APPBP_FLAG_AFTER_CODE_PATCH		0x00000002
#define APPBP_FLAG_CODE_PATCHED			0x00000004

/**
 * <category>Event parameter</category>
 * <element name="pbyCodePosition" type="IN">Pointer to code position to patch</element>
 * <element name="pbyCode" type="IN">Pointer to code to patch</element>
 * <element name="nCodeLen" type="IN">Code length to patch</element>
 * <element name="flags" type="IN">Flags for code patch. See "Code patch event flags" for details.</element>
 */
typedef struct
{
	RTS_UI8 *pbyCodePosition;
	RTS_UI8 *pbyCode;
	RTS_I32 nCodeLen;
	RTS_UI32 flags;
} EVTPARAM_CmpAppBP_SavePatch;
#define EVTPARAMID_CmpAppBP_SavePatch		0x0001
#define EVTVERSION_CmpAppBP_SavePatch		0x0002

typedef struct
{
	RTS_UI8 *pbyCodePosition;
	RTS_UI8 *pbyCode;
	RTS_I32 nCodeLen;
	RTS_I32 bPatch;
} EVTPARAM_CmpAppBP_CodePatch;
#define EVTPARAMID_CmpAppBP_CodePatch		0x0001
#define EVTVERSION_CmpAppBP_CodePatch		0x0001


/**
 * <category>Events</category>
 * <description>Event is sent before and after patching the code for breakpoints/flowpoints</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppBP_SavePatch or for backward compatibility EVTPARAM_CmpAppBP_CodePatch</param>
 */
#define EVT_CmpAppBP_CodePatch				MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Events</category>
 * <description>Event is sent before and after patching the code for breakpoints/flowpoints</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpAppBP_SavePatch</param>
 */
#define EVT_CmpAppBP_CodeSave				MAKE_EVENTID(EVTCLASS_INFO, 2)


/**
 * <category>Breakpoint types</category>
 * <description>
 * </description>
 */
#define BP_PERMANENT		1
#define BP_TEMPORARY		2
#define BP_REPATCH			3
#define BP_FLOWREAD			4
#define BP_FLOWWRITE		5
#define BP_FLOWFORCE		6
#define BP_CODE_EXECUTIONPOINT	7
#define BP_SUSPEND_TASK		8
#define BP_DATA_BREAKPOINT	   	9
#define BP_DATA_EXECUTIONPOINT 10
#define BP_INVALID	0xFFFFFFFF


/**
 * <category>Breakpoint hitcount conditions</category>
 * <description>
 * </description>
 */
#define HIT_ALWAYS		0
#define HIT_EQUAL		1
#define HIT_MULTIPLEOF	2
#define HIT_GTOREQTO	3

#define BP_STATE_REACHED		1
#define BP_STATE_EXECUTED		2
#define BP_STATE_ACTIVE			4


struct DebugContext_;

/**
 * <category>Breakpoint handler</category>
 * <description>Breakpoint handler which is called if breakpoint is entered</description>
 * <param name="pDebugContext" type="INOUT">Pointer to debug context provided by AppDebugHandler</param>
 */
typedef RTS_RESULT (CDECL *APPBP_ENTER_BREAKPOINT_HANDLER)(struct DebugContext_ *pDebugContext);

/**
 * <category>Breakpoint handler</category>
 * <description>Breakpoint handler which is called if breakpoint is left</description>
 * <param name="pDebugContext" type="INOUT">Pointer to debug context provided by AppDebugHandler</param>
 */
typedef RTS_RESULT (CDECL *APPBP_LEAVE_BREAKPOINT_HANDLER)(struct DebugContext_ *pDebugContext);

/**
 * <category>Breakpoint description</category>
 * <description>
 *	Complete description of a breakpoint.
 * </description>
 * <element name="pApp" type="IN">Pointer to the specified application description</element>
 * <element name="ulSessionId" type="IN">Online SessionID from which the breakpoint is set</element>
 * <element name="usArea" type="IN">Area index</element>
 * <element name="ulOffset" type="IN">Offset within this area</element>
 * <element name="ulSuccOffset1" type="IN">Offset of the successor breakpoint 1</element>
 * <element name="ulSuccOffset2" type="IN">Offset of the successor breakpoint 2</element>
 * <element name="ulType" type="IN">Type of breakpoint. See "Breakpoint types" for details.</element>
 * <element name="iOpCodeSize" type="IN">Size of the opcode to patch as breakpoint</element>
 * <element name="abyOpCode" type="IN">Breakpoint opcode</element>
 * <element name="pfBpEnterHandler" type="IN">Function pointer to a callback that is called entering the breakpoint</element>
 * <element name="pfBpLeaveHandler" type="IN">Function pointer to a callback that is called leaving the breakpoint</element>
 */
typedef struct BreakpointDesc_
{
	APPLICATION *pApp;
	RTS_UI32 ulSessionId;
	RTS_UI16 usArea;
	RTS_SIZE ulOffset;
	RTS_SIZE ulSuccOffset1;
	RTS_SIZE ulSuccOffset2;
	RTS_UI32 ulType;
	RTS_I32 iOpCodeSize;
	RTS_UI8 abyOpCode[APP_MAX_BP_OPCODE_SIZE];
	APPBP_ENTER_BREAKPOINT_HANDLER pfBpEnterHandler;
	APPBP_LEAVE_BREAKPOINT_HANDLER pfBpLeaveHandler;
	RTS_UI16 usDataBPSize;
} BreakpointDesc;

/**
 * <category>Breakpoint context</category>
 * <description>
 *	Low level context information of a breakpoint
 * </description>
 * <element name="context" type="IN">Exception context, containing IP, BP, SP</element>
 * <element name="pRegBuff" type="IN">Pointer to start of saved registers</element>
 * <element name="pDataBPAddress" type="IN">Pointer to observed memory</element>
 * <element name="uiDataBPSize" type="IN">Size of the memory to be observed</element>
 */
typedef struct BreakpointContext_
{
	RegContext regContext;
	RTS_UINTPTR *pRegBuff;
	RTS_UINTPTR pDataBPAddress;
	RTS_UI32 uiDataBPSize;
}BreakpointContext;

typedef struct Breakpoint_
{
	BreakpointDesc BpDesc;
	RTS_I32 iBreakHitCount;
	RTS_I32 iCurrentHitCount;
	RTS_UI16 usHitCountCondition;
	RTS_UI16 usAreaInstance;
	RTS_SIZE ulOffsetInstance;
	RTS_SIZE ulStackPosInstance;
	RTS_UI32 ulTaskIndices;
	RTS_UI16 usState;
	RTS_UI16 usSizeCondition;
	RTS_UI16 usSizeInterpCode;
	RTS_UI8 abySafedCode[APP_MAX_BP_OPCODE_SIZE];
	RTS_UI8* pbyCondition;
	RTS_UI8* pbyInterpCode;
} Breakpoint;


typedef struct Flowpoint_
{
	RTS_SIZE ulOffset;
	RTS_SIZE ulSuccOffset1;
	RTS_SIZE ulSuccOffset2;
	RTS_UI32 ulType;
	RTS_UI32 ulSessionId;
	struct tagAPPLICATION *pApp;
	RTS_UI8* pMonitoringInfo;						/* union with ICurrentHitCount */
	RTS_UI32 ulMonitoringInfoSize;			/* union with IBreakHitCount  */
	RTS_UI16 usNotUsed;					/* union with usHitCountCondition */
	RTS_UI16 usAreaInstance;
	RTS_SIZE ulOffsetInstance;
	RTS_SIZE ulStackPosInstance;
	RTS_UI32 ulTaskIndices;
	RTS_I32 iOpCodeSize;
	RTS_UI16 bReached;
	RTS_UI16 usArea;
	RTS_I32 iPOUId;									/*identification of code piece*/
	RTS_I16 iKindOfFlow;							/*1 = first, 2 = last, 0 = other*/
	RTS_I16 iDummy;
	RTS_UI8 abyOpCode[APP_MAX_BP_OPCODE_SIZE];
	RTS_UI8 abySafedCode[APP_MAX_BP_OPCODE_SIZE];
} Flowpoint;


typedef struct DebugContext_
{
	Task_Desc *pTask;
	RTS_HANDLE hTask;
	APPLICATION *pApp;
	Breakpoint *pbp;
	RTS_UI32 ulType;
	RTS_BOOL bConditionOK;
	BreakpointContext BPContext;
	RTS_UINTPTR ReturnIP;
	Breakpoint bpHelp;
	RTS_BOOL bUpdateDone;
#ifndef APPBP_DISABLE_FLOWCONTROL
	Flowpoint* pFlowpoint;
#endif
	RTS_BOOL bFlowBreak;
	RTS_BOOL bFlowConditionOK;
} DebugContext;


typedef struct
{
	RTS_UI16 usArea;
	RTS_UI16 usAreaInstance;
	RTS_UI32 ulOffset;
	RTS_UI32 ulOffsetInstance;
} FLOW_BP_INFO;

#define FLOW_READ  1
#define FLOW_WRITE 2
#define FLOW_FORCE 3

typedef struct
{
	RTS_UI16 usKindOf;
	RTS_UI16 usSize;
	RTS_UI16 usId;
	RTS_I8 value[1];       /* write or force : value to write. read : value to read */
}FLOW_INFO;


typedef struct
{
	RTS_SIZE ulOffset;
	RTS_SIZE ulOffsetInstance;
	RTS_UI16 usArea;
	RTS_UI16 usAreaInstance;
} CallstackEntry;


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Init breakpoint list on the specified application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppBPInit', `(APPLICATION *pApp)')

/**
 * <description>Exit breakpoint list on the specified application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppBPExit', `(APPLICATION *pApp)')

/**
 * <description>Routine handle a debug breakpoint. This routine is typically called from the syscpudebughandler()
 *	method of the CmpCpuHandling component. This routine must handle the folliwinghave to handle</description>
 * <param name="IP" type="IN">Program counter or instruction pointer of breakpoint position, where the
 *	debug opcode is executed</param>
 * <param name="SP" type="IN">Actual stack pointer</param>
 * <param name="BP" type="IN">Frame pointer or base pointer to the stack, where the first entry function right after
 *	the debug code begins its stack usage</param>
 * <result>Return address, to which we would like to return right after leaving this function.
 *	NOTE: This must be adopted by the caller!</result>
 */
DEF_ITF_API(`RTS_UINTPTR', `CDECL', `AppDebugHandler', `(RTS_UINTPTR IP, RTS_UINTPTR SP, RTS_UINTPTR BP)')

/**
 * <description>See AppDebugHandler. AppDebugHandler2 supports also data breakpoints</description>
 * <param name="pBPContext" type="IN">Low level register context of the breakpoint.</param>
 * <result>Return address, to which we would like to return right after leaving this function.
 *	NOTE: This must be adopted by the caller!</result>
 */
DEF_ITF_API(`RTS_UINTPTR', `CDECL', `AppDebugHandler2', `(BreakpointContext *pBPContext)')

/**
 * <description>Retrieves the first breakpoint (if available)</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to first breakpoint</result>
 */
DEF_ITF_API(`Breakpoint *', `CDECL', `AppBPGetFirst', `(APPLICATION *pApp, RTS_RESULT *pResult)')

/**
 * <description>Retrieves the next breakpoint (if available)</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="pPrevBreakpoint" type="IN">Pointer to previous breakpoint returned by previous calls of AppGetFirstBP or AppGetNextBP</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to next breakpoint</result>
 */
DEF_ITF_API(`Breakpoint *', `CDECL', `AppBPGetNext', `(APPLICATION *pApp, Breakpoint *pPrevBreakpoint, RTS_RESULT *pResult)')

/**
 * <description>Delete all breakpoints of the specified application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="ulSessionId" type="IN">Session id of the communication channel</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppBPDeleteAll', `(APPLICATION *pApp, RTS_UI32 ulSessionId)')

/**
 * <description>Delete all breakpoints and executionpoints of the specified application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="ulSessionId" type="IN">Session id of the communication channel</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppBPDeleteAllWithExecutionpoints', `(APPLICATION *pApp, RTS_UI32 ulSessionId)')


/**
 * <description>Leave a breakpoint and continue executing the specified application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppBPLeave', `(APPLICATION *pApp)')

/**
 * <description>Do one step to the next breakpoint</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppBPStep', `(APPLICATION *pApp)')

/**
 * <description>Get the hit counter of the actual breakpoint</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="piHitCount" type="OUT">Pointer to the hit counter of the active breakpoint</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppBPGetHitCount', `(APPLICATION *pApp, int *piHitCount)')

/**
 * <description>Update all breakpoints (repatch or not depends on the context)</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="ulTypeIn" type="IN">TypeIn it eh type of the currently reached breakpoint. If this 
 *	breakpoint is a repatch breakpoint, dont delete temporary breakpoints</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppBPUpdate', `(APPLICATION *pApp, RTS_SIZE ulTypeIn)')

/**
 * <description>Retrieves the first callstack entry (if available). This is the most nested calling position
 *	from the callstack. A callstack is only available, if the application in in state stop!</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="pContext" type="OUT">Returns register context, e.g. the base pointer to find the next calstack entry</param>
 * <param name="pCallstackEntry" type="OUT">Pointer to the callstack entry</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppBPGetFirstCallstackEntry', `(APPLICATION *pApp, RegContext *pContext, CallstackEntry *pCallstackEntry)')

/**
 * <description>Retrieves the first callstack entry (if available). This is the most nested calling position
 *	from the callstack. A callstack is only available, if the application in in state stop!</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="hIecTask"IN">Handle to the desired task</param>
 * <param name="pContext" type="OUT">Returns register context, e.g. the base pointer to find the next calstack entry</param>
 * <param name="pCallstackEntry" type="OUT">Pointer to the callstack entry</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppBPGetFirstCallstackEntry2', `(APPLICATION *pApp, RTS_HANDLE hIecTask, RegContext *pContext, CallstackEntry *pCallstackEntry)')

/**
 * <description>Retrieves the next callstack entry (if available). This is the less nested calling position
 *	from the previous call or the AppGetFirstCallstackEntry() function.</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="pContext" type="OUT">Returns register context, e.g. the base pointer to find the next calstack entry</param>
 * <param name="pCallstackEntry" type="OUT">Pointer to the callstack entry</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppBPGetNextCallstackEntry', `(APPLICATION *pApp, RegContext *pContext, CallstackEntry *pCallstackEntry)')

/**
 * <description>Retrieves the next callstack entry (if available). This is the less nested calling position
 *	from the previous call or the AppGetFirstCallstackEntry() function.</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="bIecCode" type="IN">Specifies, if callstack is searched in IecCode. If bIecCode is 0, we search in C-code! </param>
 * <param name="pContext" type="OUT">Returns register context, e.g. the base pointer to find the next calstack entry</param>
 * <param name="pCallstackEntry" type="OUT">Pointer to the callstack entry</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppBPGetNextCallstackEntry2', `(APPLICATION *pApp, int bIecCode, RegContext *pContext, CallstackEntry *pCallstackEntry)')

/**
 * <description>Handler for all breakpoint services</description>
 * <param name="ulChannelId" type="IN">ChannelID of the communication channel</param>
 * <param name="pHeaderTag" type="IN">Pointer to the service header</param>
 * <param name="pduData" type="IN">Data unit of the received service</param>
 * <param name="pduSendBuffer" type="IN">Data unit for the service reply</param>
 * <result>Error code:
 *		ERR_OK: Service could be executed successfully.
 *		ERR_NOT_SUPPORTED: Service is not supported
 *		ERR_FAILED: Error during executing service
 * </result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppBPServiceHandler2', `(RTS_UI32 ulChannelId, HEADER_TAG *pHeaderTag, PROTOCOL_DATA_UNIT pduData, PROTOCOL_DATA_UNIT *pduSendBuffer)')

/**
 * <description>Set a breakpoint in the specified position.
 *	ATTENTION ATTENTION ATTENTION:
 *	Only for internal use in the runtime system!! Don't use it in adaptations!
 * </description>
 * <param name="pBpDesc" type="IN">Pointer to breakpoint description. See "Breakpoint description" for details</param>
 * <param name="bPatchCode" type="IN">1=Patch code immediately, 0=Only create the breakpoint object</param>
 * <param name="ppbpOut" type="OUT">Returns the new created breakpoint</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppBPSet', `(BreakpointDesc *pBpDesc, RTS_BOOL bPatchCode, Breakpoint** ppbpOut)')

/**
 * <description>Delete a breakpoint
 *	ATTENTION ATTENTION ATTENTION:
 *	Only for internal use in the runtime system!! Don't use it in adaptations!
 * </description>
 * <param name="pbp" type="IN">Pointer to breakpoint retrieved by AppBPSet()</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppBPDelete', `(Breakpoint *pbp)')

#ifdef __cplusplus
}
#endif
