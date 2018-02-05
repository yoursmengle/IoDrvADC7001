 /**
 * <interfacename>CmpAppBP</interfacename>
 * <description> 
 *	This is the interface of the IEC application manager to handle breakpoints
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPAPPBPITF_H_
#define _CMPAPPBPITF_H_

#include "CmpStd.h"

 

 




#include "CmpAppItf.h"
#include "CmpSrvItf.h"
#include "CmpIecTaskItf.h"

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
RTS_RESULT CDECL AppBPInit(APPLICATION *pApp);
typedef RTS_RESULT (CDECL * PFAPPBPINIT) (APPLICATION *pApp);
#if defined(CMPAPPBP_NOTIMPLEMENTED) || defined(APPBPINIT_NOTIMPLEMENTED)
	#define USE_AppBPInit
	#define EXT_AppBPInit
	#define GET_AppBPInit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppBPInit(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppBPInit  FALSE
	#define EXP_AppBPInit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppBPInit
	#define EXT_AppBPInit
	#define GET_AppBPInit(fl)  CAL_CMGETAPI( "AppBPInit" ) 
	#define CAL_AppBPInit  AppBPInit
	#define CHK_AppBPInit  TRUE
	#define EXP_AppBPInit  CAL_CMEXPAPI( "AppBPInit" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPBP_EXTERNAL)
	#define USE_AppBPInit
	#define EXT_AppBPInit
	#define GET_AppBPInit(fl)  CAL_CMGETAPI( "AppBPInit" ) 
	#define CAL_AppBPInit  AppBPInit
	#define CHK_AppBPInit  TRUE
	#define EXP_AppBPInit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPInit", (RTS_UINTPTR)AppBPInit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppBPAppBPInit
	#define EXT_CmpAppBPAppBPInit
	#define GET_CmpAppBPAppBPInit  ERR_OK
	#define CAL_CmpAppBPAppBPInit pICmpAppBP->IAppBPInit
	#define CHK_CmpAppBPAppBPInit (pICmpAppBP != NULL)
	#define EXP_CmpAppBPAppBPInit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppBPInit
	#define EXT_AppBPInit
	#define GET_AppBPInit(fl)  CAL_CMGETAPI( "AppBPInit" ) 
	#define CAL_AppBPInit pICmpAppBP->IAppBPInit
	#define CHK_AppBPInit (pICmpAppBP != NULL)
	#define EXP_AppBPInit  CAL_CMEXPAPI( "AppBPInit" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppBPInit  PFAPPBPINIT pfAppBPInit;
	#define EXT_AppBPInit  extern PFAPPBPINIT pfAppBPInit;
	#define GET_AppBPInit(fl)  s_pfCMGetAPI2( "AppBPInit", (RTS_VOID_FCTPTR *)&pfAppBPInit, (fl), 0, 0)
	#define CAL_AppBPInit  pfAppBPInit
	#define CHK_AppBPInit  (pfAppBPInit != NULL)
	#define EXP_AppBPInit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPInit", (RTS_UINTPTR)AppBPInit, 0, 0) 
#endif




/**
 * <description>Exit breakpoint list on the specified application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppBPExit(APPLICATION *pApp);
typedef RTS_RESULT (CDECL * PFAPPBPEXIT) (APPLICATION *pApp);
#if defined(CMPAPPBP_NOTIMPLEMENTED) || defined(APPBPEXIT_NOTIMPLEMENTED)
	#define USE_AppBPExit
	#define EXT_AppBPExit
	#define GET_AppBPExit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppBPExit(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppBPExit  FALSE
	#define EXP_AppBPExit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppBPExit
	#define EXT_AppBPExit
	#define GET_AppBPExit(fl)  CAL_CMGETAPI( "AppBPExit" ) 
	#define CAL_AppBPExit  AppBPExit
	#define CHK_AppBPExit  TRUE
	#define EXP_AppBPExit  CAL_CMEXPAPI( "AppBPExit" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPBP_EXTERNAL)
	#define USE_AppBPExit
	#define EXT_AppBPExit
	#define GET_AppBPExit(fl)  CAL_CMGETAPI( "AppBPExit" ) 
	#define CAL_AppBPExit  AppBPExit
	#define CHK_AppBPExit  TRUE
	#define EXP_AppBPExit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPExit", (RTS_UINTPTR)AppBPExit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppBPAppBPExit
	#define EXT_CmpAppBPAppBPExit
	#define GET_CmpAppBPAppBPExit  ERR_OK
	#define CAL_CmpAppBPAppBPExit pICmpAppBP->IAppBPExit
	#define CHK_CmpAppBPAppBPExit (pICmpAppBP != NULL)
	#define EXP_CmpAppBPAppBPExit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppBPExit
	#define EXT_AppBPExit
	#define GET_AppBPExit(fl)  CAL_CMGETAPI( "AppBPExit" ) 
	#define CAL_AppBPExit pICmpAppBP->IAppBPExit
	#define CHK_AppBPExit (pICmpAppBP != NULL)
	#define EXP_AppBPExit  CAL_CMEXPAPI( "AppBPExit" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppBPExit  PFAPPBPEXIT pfAppBPExit;
	#define EXT_AppBPExit  extern PFAPPBPEXIT pfAppBPExit;
	#define GET_AppBPExit(fl)  s_pfCMGetAPI2( "AppBPExit", (RTS_VOID_FCTPTR *)&pfAppBPExit, (fl), 0, 0)
	#define CAL_AppBPExit  pfAppBPExit
	#define CHK_AppBPExit  (pfAppBPExit != NULL)
	#define EXP_AppBPExit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPExit", (RTS_UINTPTR)AppBPExit, 0, 0) 
#endif




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
RTS_UINTPTR CDECL AppDebugHandler(RTS_UINTPTR IP, RTS_UINTPTR SP, RTS_UINTPTR BP);
typedef RTS_UINTPTR (CDECL * PFAPPDEBUGHANDLER) (RTS_UINTPTR IP, RTS_UINTPTR SP, RTS_UINTPTR BP);
#if defined(CMPAPPBP_NOTIMPLEMENTED) || defined(APPDEBUGHANDLER_NOTIMPLEMENTED)
	#define USE_AppDebugHandler
	#define EXT_AppDebugHandler
	#define GET_AppDebugHandler(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppDebugHandler(p0,p1,p2)  (RTS_UINTPTR)ERR_NOTIMPLEMENTED
	#define CHK_AppDebugHandler  FALSE
	#define EXP_AppDebugHandler  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppDebugHandler
	#define EXT_AppDebugHandler
	#define GET_AppDebugHandler(fl)  CAL_CMGETAPI( "AppDebugHandler" ) 
	#define CAL_AppDebugHandler  AppDebugHandler
	#define CHK_AppDebugHandler  TRUE
	#define EXP_AppDebugHandler  CAL_CMEXPAPI( "AppDebugHandler" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPBP_EXTERNAL)
	#define USE_AppDebugHandler
	#define EXT_AppDebugHandler
	#define GET_AppDebugHandler(fl)  CAL_CMGETAPI( "AppDebugHandler" ) 
	#define CAL_AppDebugHandler  AppDebugHandler
	#define CHK_AppDebugHandler  TRUE
	#define EXP_AppDebugHandler  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppDebugHandler", (RTS_UINTPTR)AppDebugHandler, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppBPAppDebugHandler
	#define EXT_CmpAppBPAppDebugHandler
	#define GET_CmpAppBPAppDebugHandler  ERR_OK
	#define CAL_CmpAppBPAppDebugHandler pICmpAppBP->IAppDebugHandler
	#define CHK_CmpAppBPAppDebugHandler (pICmpAppBP != NULL)
	#define EXP_CmpAppBPAppDebugHandler  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppDebugHandler
	#define EXT_AppDebugHandler
	#define GET_AppDebugHandler(fl)  CAL_CMGETAPI( "AppDebugHandler" ) 
	#define CAL_AppDebugHandler pICmpAppBP->IAppDebugHandler
	#define CHK_AppDebugHandler (pICmpAppBP != NULL)
	#define EXP_AppDebugHandler  CAL_CMEXPAPI( "AppDebugHandler" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppDebugHandler  PFAPPDEBUGHANDLER pfAppDebugHandler;
	#define EXT_AppDebugHandler  extern PFAPPDEBUGHANDLER pfAppDebugHandler;
	#define GET_AppDebugHandler(fl)  s_pfCMGetAPI2( "AppDebugHandler", (RTS_VOID_FCTPTR *)&pfAppDebugHandler, (fl), 0, 0)
	#define CAL_AppDebugHandler  pfAppDebugHandler
	#define CHK_AppDebugHandler  (pfAppDebugHandler != NULL)
	#define EXP_AppDebugHandler  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppDebugHandler", (RTS_UINTPTR)AppDebugHandler, 0, 0) 
#endif




/**
 * <description>See AppDebugHandler. AppDebugHandler2 supports also data breakpoints</description>
 * <param name="pBPContext" type="IN">Low level register context of the breakpoint.</param>
 * <result>Return address, to which we would like to return right after leaving this function.
 *	NOTE: This must be adopted by the caller!</result>
 */
RTS_UINTPTR CDECL AppDebugHandler2(BreakpointContext *pBPContext);
typedef RTS_UINTPTR (CDECL * PFAPPDEBUGHANDLER2) (BreakpointContext *pBPContext);
#if defined(CMPAPPBP_NOTIMPLEMENTED) || defined(APPDEBUGHANDLER2_NOTIMPLEMENTED)
	#define USE_AppDebugHandler2
	#define EXT_AppDebugHandler2
	#define GET_AppDebugHandler2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppDebugHandler2(p0)  (RTS_UINTPTR)ERR_NOTIMPLEMENTED
	#define CHK_AppDebugHandler2  FALSE
	#define EXP_AppDebugHandler2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppDebugHandler2
	#define EXT_AppDebugHandler2
	#define GET_AppDebugHandler2(fl)  CAL_CMGETAPI( "AppDebugHandler2" ) 
	#define CAL_AppDebugHandler2  AppDebugHandler2
	#define CHK_AppDebugHandler2  TRUE
	#define EXP_AppDebugHandler2  CAL_CMEXPAPI( "AppDebugHandler2" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPBP_EXTERNAL)
	#define USE_AppDebugHandler2
	#define EXT_AppDebugHandler2
	#define GET_AppDebugHandler2(fl)  CAL_CMGETAPI( "AppDebugHandler2" ) 
	#define CAL_AppDebugHandler2  AppDebugHandler2
	#define CHK_AppDebugHandler2  TRUE
	#define EXP_AppDebugHandler2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppDebugHandler2", (RTS_UINTPTR)AppDebugHandler2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppBPAppDebugHandler2
	#define EXT_CmpAppBPAppDebugHandler2
	#define GET_CmpAppBPAppDebugHandler2  ERR_OK
	#define CAL_CmpAppBPAppDebugHandler2 pICmpAppBP->IAppDebugHandler2
	#define CHK_CmpAppBPAppDebugHandler2 (pICmpAppBP != NULL)
	#define EXP_CmpAppBPAppDebugHandler2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppDebugHandler2
	#define EXT_AppDebugHandler2
	#define GET_AppDebugHandler2(fl)  CAL_CMGETAPI( "AppDebugHandler2" ) 
	#define CAL_AppDebugHandler2 pICmpAppBP->IAppDebugHandler2
	#define CHK_AppDebugHandler2 (pICmpAppBP != NULL)
	#define EXP_AppDebugHandler2  CAL_CMEXPAPI( "AppDebugHandler2" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppDebugHandler2  PFAPPDEBUGHANDLER2 pfAppDebugHandler2;
	#define EXT_AppDebugHandler2  extern PFAPPDEBUGHANDLER2 pfAppDebugHandler2;
	#define GET_AppDebugHandler2(fl)  s_pfCMGetAPI2( "AppDebugHandler2", (RTS_VOID_FCTPTR *)&pfAppDebugHandler2, (fl), 0, 0)
	#define CAL_AppDebugHandler2  pfAppDebugHandler2
	#define CHK_AppDebugHandler2  (pfAppDebugHandler2 != NULL)
	#define EXP_AppDebugHandler2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppDebugHandler2", (RTS_UINTPTR)AppDebugHandler2, 0, 0) 
#endif




/**
 * <description>Retrieves the first breakpoint (if available)</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to first breakpoint</result>
 */
Breakpoint * CDECL AppBPGetFirst(APPLICATION *pApp, RTS_RESULT *pResult);
typedef Breakpoint * (CDECL * PFAPPBPGETFIRST) (APPLICATION *pApp, RTS_RESULT *pResult);
#if defined(CMPAPPBP_NOTIMPLEMENTED) || defined(APPBPGETFIRST_NOTIMPLEMENTED)
	#define USE_AppBPGetFirst
	#define EXT_AppBPGetFirst
	#define GET_AppBPGetFirst(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppBPGetFirst(p0,p1)  (Breakpoint *)ERR_NOTIMPLEMENTED
	#define CHK_AppBPGetFirst  FALSE
	#define EXP_AppBPGetFirst  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppBPGetFirst
	#define EXT_AppBPGetFirst
	#define GET_AppBPGetFirst(fl)  CAL_CMGETAPI( "AppBPGetFirst" ) 
	#define CAL_AppBPGetFirst  AppBPGetFirst
	#define CHK_AppBPGetFirst  TRUE
	#define EXP_AppBPGetFirst  CAL_CMEXPAPI( "AppBPGetFirst" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPBP_EXTERNAL)
	#define USE_AppBPGetFirst
	#define EXT_AppBPGetFirst
	#define GET_AppBPGetFirst(fl)  CAL_CMGETAPI( "AppBPGetFirst" ) 
	#define CAL_AppBPGetFirst  AppBPGetFirst
	#define CHK_AppBPGetFirst  TRUE
	#define EXP_AppBPGetFirst  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPGetFirst", (RTS_UINTPTR)AppBPGetFirst, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppBPAppBPGetFirst
	#define EXT_CmpAppBPAppBPGetFirst
	#define GET_CmpAppBPAppBPGetFirst  ERR_OK
	#define CAL_CmpAppBPAppBPGetFirst pICmpAppBP->IAppBPGetFirst
	#define CHK_CmpAppBPAppBPGetFirst (pICmpAppBP != NULL)
	#define EXP_CmpAppBPAppBPGetFirst  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppBPGetFirst
	#define EXT_AppBPGetFirst
	#define GET_AppBPGetFirst(fl)  CAL_CMGETAPI( "AppBPGetFirst" ) 
	#define CAL_AppBPGetFirst pICmpAppBP->IAppBPGetFirst
	#define CHK_AppBPGetFirst (pICmpAppBP != NULL)
	#define EXP_AppBPGetFirst  CAL_CMEXPAPI( "AppBPGetFirst" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppBPGetFirst  PFAPPBPGETFIRST pfAppBPGetFirst;
	#define EXT_AppBPGetFirst  extern PFAPPBPGETFIRST pfAppBPGetFirst;
	#define GET_AppBPGetFirst(fl)  s_pfCMGetAPI2( "AppBPGetFirst", (RTS_VOID_FCTPTR *)&pfAppBPGetFirst, (fl), 0, 0)
	#define CAL_AppBPGetFirst  pfAppBPGetFirst
	#define CHK_AppBPGetFirst  (pfAppBPGetFirst != NULL)
	#define EXP_AppBPGetFirst  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPGetFirst", (RTS_UINTPTR)AppBPGetFirst, 0, 0) 
#endif




/**
 * <description>Retrieves the next breakpoint (if available)</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="pPrevBreakpoint" type="IN">Pointer to previous breakpoint returned by previous calls of AppGetFirstBP or AppGetNextBP</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to next breakpoint</result>
 */
Breakpoint * CDECL AppBPGetNext(APPLICATION *pApp, Breakpoint *pPrevBreakpoint, RTS_RESULT *pResult);
typedef Breakpoint * (CDECL * PFAPPBPGETNEXT) (APPLICATION *pApp, Breakpoint *pPrevBreakpoint, RTS_RESULT *pResult);
#if defined(CMPAPPBP_NOTIMPLEMENTED) || defined(APPBPGETNEXT_NOTIMPLEMENTED)
	#define USE_AppBPGetNext
	#define EXT_AppBPGetNext
	#define GET_AppBPGetNext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppBPGetNext(p0,p1,p2)  (Breakpoint *)ERR_NOTIMPLEMENTED
	#define CHK_AppBPGetNext  FALSE
	#define EXP_AppBPGetNext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppBPGetNext
	#define EXT_AppBPGetNext
	#define GET_AppBPGetNext(fl)  CAL_CMGETAPI( "AppBPGetNext" ) 
	#define CAL_AppBPGetNext  AppBPGetNext
	#define CHK_AppBPGetNext  TRUE
	#define EXP_AppBPGetNext  CAL_CMEXPAPI( "AppBPGetNext" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPBP_EXTERNAL)
	#define USE_AppBPGetNext
	#define EXT_AppBPGetNext
	#define GET_AppBPGetNext(fl)  CAL_CMGETAPI( "AppBPGetNext" ) 
	#define CAL_AppBPGetNext  AppBPGetNext
	#define CHK_AppBPGetNext  TRUE
	#define EXP_AppBPGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPGetNext", (RTS_UINTPTR)AppBPGetNext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppBPAppBPGetNext
	#define EXT_CmpAppBPAppBPGetNext
	#define GET_CmpAppBPAppBPGetNext  ERR_OK
	#define CAL_CmpAppBPAppBPGetNext pICmpAppBP->IAppBPGetNext
	#define CHK_CmpAppBPAppBPGetNext (pICmpAppBP != NULL)
	#define EXP_CmpAppBPAppBPGetNext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppBPGetNext
	#define EXT_AppBPGetNext
	#define GET_AppBPGetNext(fl)  CAL_CMGETAPI( "AppBPGetNext" ) 
	#define CAL_AppBPGetNext pICmpAppBP->IAppBPGetNext
	#define CHK_AppBPGetNext (pICmpAppBP != NULL)
	#define EXP_AppBPGetNext  CAL_CMEXPAPI( "AppBPGetNext" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppBPGetNext  PFAPPBPGETNEXT pfAppBPGetNext;
	#define EXT_AppBPGetNext  extern PFAPPBPGETNEXT pfAppBPGetNext;
	#define GET_AppBPGetNext(fl)  s_pfCMGetAPI2( "AppBPGetNext", (RTS_VOID_FCTPTR *)&pfAppBPGetNext, (fl), 0, 0)
	#define CAL_AppBPGetNext  pfAppBPGetNext
	#define CHK_AppBPGetNext  (pfAppBPGetNext != NULL)
	#define EXP_AppBPGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPGetNext", (RTS_UINTPTR)AppBPGetNext, 0, 0) 
#endif




/**
 * <description>Delete all breakpoints of the specified application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="ulSessionId" type="IN">Session id of the communication channel</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppBPDeleteAll(APPLICATION *pApp, RTS_UI32 ulSessionId);
typedef RTS_RESULT (CDECL * PFAPPBPDELETEALL) (APPLICATION *pApp, RTS_UI32 ulSessionId);
#if defined(CMPAPPBP_NOTIMPLEMENTED) || defined(APPBPDELETEALL_NOTIMPLEMENTED)
	#define USE_AppBPDeleteAll
	#define EXT_AppBPDeleteAll
	#define GET_AppBPDeleteAll(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppBPDeleteAll(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppBPDeleteAll  FALSE
	#define EXP_AppBPDeleteAll  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppBPDeleteAll
	#define EXT_AppBPDeleteAll
	#define GET_AppBPDeleteAll(fl)  CAL_CMGETAPI( "AppBPDeleteAll" ) 
	#define CAL_AppBPDeleteAll  AppBPDeleteAll
	#define CHK_AppBPDeleteAll  TRUE
	#define EXP_AppBPDeleteAll  CAL_CMEXPAPI( "AppBPDeleteAll" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPBP_EXTERNAL)
	#define USE_AppBPDeleteAll
	#define EXT_AppBPDeleteAll
	#define GET_AppBPDeleteAll(fl)  CAL_CMGETAPI( "AppBPDeleteAll" ) 
	#define CAL_AppBPDeleteAll  AppBPDeleteAll
	#define CHK_AppBPDeleteAll  TRUE
	#define EXP_AppBPDeleteAll  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPDeleteAll", (RTS_UINTPTR)AppBPDeleteAll, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppBPAppBPDeleteAll
	#define EXT_CmpAppBPAppBPDeleteAll
	#define GET_CmpAppBPAppBPDeleteAll  ERR_OK
	#define CAL_CmpAppBPAppBPDeleteAll pICmpAppBP->IAppBPDeleteAll
	#define CHK_CmpAppBPAppBPDeleteAll (pICmpAppBP != NULL)
	#define EXP_CmpAppBPAppBPDeleteAll  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppBPDeleteAll
	#define EXT_AppBPDeleteAll
	#define GET_AppBPDeleteAll(fl)  CAL_CMGETAPI( "AppBPDeleteAll" ) 
	#define CAL_AppBPDeleteAll pICmpAppBP->IAppBPDeleteAll
	#define CHK_AppBPDeleteAll (pICmpAppBP != NULL)
	#define EXP_AppBPDeleteAll  CAL_CMEXPAPI( "AppBPDeleteAll" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppBPDeleteAll  PFAPPBPDELETEALL pfAppBPDeleteAll;
	#define EXT_AppBPDeleteAll  extern PFAPPBPDELETEALL pfAppBPDeleteAll;
	#define GET_AppBPDeleteAll(fl)  s_pfCMGetAPI2( "AppBPDeleteAll", (RTS_VOID_FCTPTR *)&pfAppBPDeleteAll, (fl), 0, 0)
	#define CAL_AppBPDeleteAll  pfAppBPDeleteAll
	#define CHK_AppBPDeleteAll  (pfAppBPDeleteAll != NULL)
	#define EXP_AppBPDeleteAll  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPDeleteAll", (RTS_UINTPTR)AppBPDeleteAll, 0, 0) 
#endif




/**
 * <description>Delete all breakpoints and executionpoints of the specified application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="ulSessionId" type="IN">Session id of the communication channel</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppBPDeleteAllWithExecutionpoints(APPLICATION *pApp, RTS_UI32 ulSessionId);
typedef RTS_RESULT (CDECL * PFAPPBPDELETEALLWITHEXECUTIONPOINTS) (APPLICATION *pApp, RTS_UI32 ulSessionId);
#if defined(CMPAPPBP_NOTIMPLEMENTED) || defined(APPBPDELETEALLWITHEXECUTIONPOINTS_NOTIMPLEMENTED)
	#define USE_AppBPDeleteAllWithExecutionpoints
	#define EXT_AppBPDeleteAllWithExecutionpoints
	#define GET_AppBPDeleteAllWithExecutionpoints(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppBPDeleteAllWithExecutionpoints(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppBPDeleteAllWithExecutionpoints  FALSE
	#define EXP_AppBPDeleteAllWithExecutionpoints  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppBPDeleteAllWithExecutionpoints
	#define EXT_AppBPDeleteAllWithExecutionpoints
	#define GET_AppBPDeleteAllWithExecutionpoints(fl)  CAL_CMGETAPI( "AppBPDeleteAllWithExecutionpoints" ) 
	#define CAL_AppBPDeleteAllWithExecutionpoints  AppBPDeleteAllWithExecutionpoints
	#define CHK_AppBPDeleteAllWithExecutionpoints  TRUE
	#define EXP_AppBPDeleteAllWithExecutionpoints  CAL_CMEXPAPI( "AppBPDeleteAllWithExecutionpoints" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPBP_EXTERNAL)
	#define USE_AppBPDeleteAllWithExecutionpoints
	#define EXT_AppBPDeleteAllWithExecutionpoints
	#define GET_AppBPDeleteAllWithExecutionpoints(fl)  CAL_CMGETAPI( "AppBPDeleteAllWithExecutionpoints" ) 
	#define CAL_AppBPDeleteAllWithExecutionpoints  AppBPDeleteAllWithExecutionpoints
	#define CHK_AppBPDeleteAllWithExecutionpoints  TRUE
	#define EXP_AppBPDeleteAllWithExecutionpoints  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPDeleteAllWithExecutionpoints", (RTS_UINTPTR)AppBPDeleteAllWithExecutionpoints, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppBPAppBPDeleteAllWithExecutionpoints
	#define EXT_CmpAppBPAppBPDeleteAllWithExecutionpoints
	#define GET_CmpAppBPAppBPDeleteAllWithExecutionpoints  ERR_OK
	#define CAL_CmpAppBPAppBPDeleteAllWithExecutionpoints pICmpAppBP->IAppBPDeleteAllWithExecutionpoints
	#define CHK_CmpAppBPAppBPDeleteAllWithExecutionpoints (pICmpAppBP != NULL)
	#define EXP_CmpAppBPAppBPDeleteAllWithExecutionpoints  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppBPDeleteAllWithExecutionpoints
	#define EXT_AppBPDeleteAllWithExecutionpoints
	#define GET_AppBPDeleteAllWithExecutionpoints(fl)  CAL_CMGETAPI( "AppBPDeleteAllWithExecutionpoints" ) 
	#define CAL_AppBPDeleteAllWithExecutionpoints pICmpAppBP->IAppBPDeleteAllWithExecutionpoints
	#define CHK_AppBPDeleteAllWithExecutionpoints (pICmpAppBP != NULL)
	#define EXP_AppBPDeleteAllWithExecutionpoints  CAL_CMEXPAPI( "AppBPDeleteAllWithExecutionpoints" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppBPDeleteAllWithExecutionpoints  PFAPPBPDELETEALLWITHEXECUTIONPOINTS pfAppBPDeleteAllWithExecutionpoints;
	#define EXT_AppBPDeleteAllWithExecutionpoints  extern PFAPPBPDELETEALLWITHEXECUTIONPOINTS pfAppBPDeleteAllWithExecutionpoints;
	#define GET_AppBPDeleteAllWithExecutionpoints(fl)  s_pfCMGetAPI2( "AppBPDeleteAllWithExecutionpoints", (RTS_VOID_FCTPTR *)&pfAppBPDeleteAllWithExecutionpoints, (fl), 0, 0)
	#define CAL_AppBPDeleteAllWithExecutionpoints  pfAppBPDeleteAllWithExecutionpoints
	#define CHK_AppBPDeleteAllWithExecutionpoints  (pfAppBPDeleteAllWithExecutionpoints != NULL)
	#define EXP_AppBPDeleteAllWithExecutionpoints  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPDeleteAllWithExecutionpoints", (RTS_UINTPTR)AppBPDeleteAllWithExecutionpoints, 0, 0) 
#endif





/**
 * <description>Leave a breakpoint and continue executing the specified application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppBPLeave(APPLICATION *pApp);
typedef RTS_RESULT (CDECL * PFAPPBPLEAVE) (APPLICATION *pApp);
#if defined(CMPAPPBP_NOTIMPLEMENTED) || defined(APPBPLEAVE_NOTIMPLEMENTED)
	#define USE_AppBPLeave
	#define EXT_AppBPLeave
	#define GET_AppBPLeave(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppBPLeave(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppBPLeave  FALSE
	#define EXP_AppBPLeave  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppBPLeave
	#define EXT_AppBPLeave
	#define GET_AppBPLeave(fl)  CAL_CMGETAPI( "AppBPLeave" ) 
	#define CAL_AppBPLeave  AppBPLeave
	#define CHK_AppBPLeave  TRUE
	#define EXP_AppBPLeave  CAL_CMEXPAPI( "AppBPLeave" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPBP_EXTERNAL)
	#define USE_AppBPLeave
	#define EXT_AppBPLeave
	#define GET_AppBPLeave(fl)  CAL_CMGETAPI( "AppBPLeave" ) 
	#define CAL_AppBPLeave  AppBPLeave
	#define CHK_AppBPLeave  TRUE
	#define EXP_AppBPLeave  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPLeave", (RTS_UINTPTR)AppBPLeave, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppBPAppBPLeave
	#define EXT_CmpAppBPAppBPLeave
	#define GET_CmpAppBPAppBPLeave  ERR_OK
	#define CAL_CmpAppBPAppBPLeave pICmpAppBP->IAppBPLeave
	#define CHK_CmpAppBPAppBPLeave (pICmpAppBP != NULL)
	#define EXP_CmpAppBPAppBPLeave  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppBPLeave
	#define EXT_AppBPLeave
	#define GET_AppBPLeave(fl)  CAL_CMGETAPI( "AppBPLeave" ) 
	#define CAL_AppBPLeave pICmpAppBP->IAppBPLeave
	#define CHK_AppBPLeave (pICmpAppBP != NULL)
	#define EXP_AppBPLeave  CAL_CMEXPAPI( "AppBPLeave" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppBPLeave  PFAPPBPLEAVE pfAppBPLeave;
	#define EXT_AppBPLeave  extern PFAPPBPLEAVE pfAppBPLeave;
	#define GET_AppBPLeave(fl)  s_pfCMGetAPI2( "AppBPLeave", (RTS_VOID_FCTPTR *)&pfAppBPLeave, (fl), 0, 0)
	#define CAL_AppBPLeave  pfAppBPLeave
	#define CHK_AppBPLeave  (pfAppBPLeave != NULL)
	#define EXP_AppBPLeave  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPLeave", (RTS_UINTPTR)AppBPLeave, 0, 0) 
#endif




/**
 * <description>Do one step to the next breakpoint</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppBPStep(APPLICATION *pApp);
typedef RTS_RESULT (CDECL * PFAPPBPSTEP) (APPLICATION *pApp);
#if defined(CMPAPPBP_NOTIMPLEMENTED) || defined(APPBPSTEP_NOTIMPLEMENTED)
	#define USE_AppBPStep
	#define EXT_AppBPStep
	#define GET_AppBPStep(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppBPStep(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppBPStep  FALSE
	#define EXP_AppBPStep  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppBPStep
	#define EXT_AppBPStep
	#define GET_AppBPStep(fl)  CAL_CMGETAPI( "AppBPStep" ) 
	#define CAL_AppBPStep  AppBPStep
	#define CHK_AppBPStep  TRUE
	#define EXP_AppBPStep  CAL_CMEXPAPI( "AppBPStep" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPBP_EXTERNAL)
	#define USE_AppBPStep
	#define EXT_AppBPStep
	#define GET_AppBPStep(fl)  CAL_CMGETAPI( "AppBPStep" ) 
	#define CAL_AppBPStep  AppBPStep
	#define CHK_AppBPStep  TRUE
	#define EXP_AppBPStep  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPStep", (RTS_UINTPTR)AppBPStep, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppBPAppBPStep
	#define EXT_CmpAppBPAppBPStep
	#define GET_CmpAppBPAppBPStep  ERR_OK
	#define CAL_CmpAppBPAppBPStep pICmpAppBP->IAppBPStep
	#define CHK_CmpAppBPAppBPStep (pICmpAppBP != NULL)
	#define EXP_CmpAppBPAppBPStep  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppBPStep
	#define EXT_AppBPStep
	#define GET_AppBPStep(fl)  CAL_CMGETAPI( "AppBPStep" ) 
	#define CAL_AppBPStep pICmpAppBP->IAppBPStep
	#define CHK_AppBPStep (pICmpAppBP != NULL)
	#define EXP_AppBPStep  CAL_CMEXPAPI( "AppBPStep" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppBPStep  PFAPPBPSTEP pfAppBPStep;
	#define EXT_AppBPStep  extern PFAPPBPSTEP pfAppBPStep;
	#define GET_AppBPStep(fl)  s_pfCMGetAPI2( "AppBPStep", (RTS_VOID_FCTPTR *)&pfAppBPStep, (fl), 0, 0)
	#define CAL_AppBPStep  pfAppBPStep
	#define CHK_AppBPStep  (pfAppBPStep != NULL)
	#define EXP_AppBPStep  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPStep", (RTS_UINTPTR)AppBPStep, 0, 0) 
#endif




/**
 * <description>Get the hit counter of the actual breakpoint</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="piHitCount" type="OUT">Pointer to the hit counter of the active breakpoint</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppBPGetHitCount(APPLICATION *pApp, int *piHitCount);
typedef RTS_RESULT (CDECL * PFAPPBPGETHITCOUNT) (APPLICATION *pApp, int *piHitCount);
#if defined(CMPAPPBP_NOTIMPLEMENTED) || defined(APPBPGETHITCOUNT_NOTIMPLEMENTED)
	#define USE_AppBPGetHitCount
	#define EXT_AppBPGetHitCount
	#define GET_AppBPGetHitCount(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppBPGetHitCount(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppBPGetHitCount  FALSE
	#define EXP_AppBPGetHitCount  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppBPGetHitCount
	#define EXT_AppBPGetHitCount
	#define GET_AppBPGetHitCount(fl)  CAL_CMGETAPI( "AppBPGetHitCount" ) 
	#define CAL_AppBPGetHitCount  AppBPGetHitCount
	#define CHK_AppBPGetHitCount  TRUE
	#define EXP_AppBPGetHitCount  CAL_CMEXPAPI( "AppBPGetHitCount" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPBP_EXTERNAL)
	#define USE_AppBPGetHitCount
	#define EXT_AppBPGetHitCount
	#define GET_AppBPGetHitCount(fl)  CAL_CMGETAPI( "AppBPGetHitCount" ) 
	#define CAL_AppBPGetHitCount  AppBPGetHitCount
	#define CHK_AppBPGetHitCount  TRUE
	#define EXP_AppBPGetHitCount  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPGetHitCount", (RTS_UINTPTR)AppBPGetHitCount, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppBPAppBPGetHitCount
	#define EXT_CmpAppBPAppBPGetHitCount
	#define GET_CmpAppBPAppBPGetHitCount  ERR_OK
	#define CAL_CmpAppBPAppBPGetHitCount pICmpAppBP->IAppBPGetHitCount
	#define CHK_CmpAppBPAppBPGetHitCount (pICmpAppBP != NULL)
	#define EXP_CmpAppBPAppBPGetHitCount  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppBPGetHitCount
	#define EXT_AppBPGetHitCount
	#define GET_AppBPGetHitCount(fl)  CAL_CMGETAPI( "AppBPGetHitCount" ) 
	#define CAL_AppBPGetHitCount pICmpAppBP->IAppBPGetHitCount
	#define CHK_AppBPGetHitCount (pICmpAppBP != NULL)
	#define EXP_AppBPGetHitCount  CAL_CMEXPAPI( "AppBPGetHitCount" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppBPGetHitCount  PFAPPBPGETHITCOUNT pfAppBPGetHitCount;
	#define EXT_AppBPGetHitCount  extern PFAPPBPGETHITCOUNT pfAppBPGetHitCount;
	#define GET_AppBPGetHitCount(fl)  s_pfCMGetAPI2( "AppBPGetHitCount", (RTS_VOID_FCTPTR *)&pfAppBPGetHitCount, (fl), 0, 0)
	#define CAL_AppBPGetHitCount  pfAppBPGetHitCount
	#define CHK_AppBPGetHitCount  (pfAppBPGetHitCount != NULL)
	#define EXP_AppBPGetHitCount  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPGetHitCount", (RTS_UINTPTR)AppBPGetHitCount, 0, 0) 
#endif




/**
 * <description>Update all breakpoints (repatch or not depends on the context)</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="ulTypeIn" type="IN">TypeIn it eh type of the currently reached breakpoint. If this 
 *	breakpoint is a repatch breakpoint, dont delete temporary breakpoints</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppBPUpdate(APPLICATION *pApp, RTS_SIZE ulTypeIn);
typedef RTS_RESULT (CDECL * PFAPPBPUPDATE) (APPLICATION *pApp, RTS_SIZE ulTypeIn);
#if defined(CMPAPPBP_NOTIMPLEMENTED) || defined(APPBPUPDATE_NOTIMPLEMENTED)
	#define USE_AppBPUpdate
	#define EXT_AppBPUpdate
	#define GET_AppBPUpdate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppBPUpdate(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppBPUpdate  FALSE
	#define EXP_AppBPUpdate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppBPUpdate
	#define EXT_AppBPUpdate
	#define GET_AppBPUpdate(fl)  CAL_CMGETAPI( "AppBPUpdate" ) 
	#define CAL_AppBPUpdate  AppBPUpdate
	#define CHK_AppBPUpdate  TRUE
	#define EXP_AppBPUpdate  CAL_CMEXPAPI( "AppBPUpdate" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPBP_EXTERNAL)
	#define USE_AppBPUpdate
	#define EXT_AppBPUpdate
	#define GET_AppBPUpdate(fl)  CAL_CMGETAPI( "AppBPUpdate" ) 
	#define CAL_AppBPUpdate  AppBPUpdate
	#define CHK_AppBPUpdate  TRUE
	#define EXP_AppBPUpdate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPUpdate", (RTS_UINTPTR)AppBPUpdate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppBPAppBPUpdate
	#define EXT_CmpAppBPAppBPUpdate
	#define GET_CmpAppBPAppBPUpdate  ERR_OK
	#define CAL_CmpAppBPAppBPUpdate pICmpAppBP->IAppBPUpdate
	#define CHK_CmpAppBPAppBPUpdate (pICmpAppBP != NULL)
	#define EXP_CmpAppBPAppBPUpdate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppBPUpdate
	#define EXT_AppBPUpdate
	#define GET_AppBPUpdate(fl)  CAL_CMGETAPI( "AppBPUpdate" ) 
	#define CAL_AppBPUpdate pICmpAppBP->IAppBPUpdate
	#define CHK_AppBPUpdate (pICmpAppBP != NULL)
	#define EXP_AppBPUpdate  CAL_CMEXPAPI( "AppBPUpdate" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppBPUpdate  PFAPPBPUPDATE pfAppBPUpdate;
	#define EXT_AppBPUpdate  extern PFAPPBPUPDATE pfAppBPUpdate;
	#define GET_AppBPUpdate(fl)  s_pfCMGetAPI2( "AppBPUpdate", (RTS_VOID_FCTPTR *)&pfAppBPUpdate, (fl), 0, 0)
	#define CAL_AppBPUpdate  pfAppBPUpdate
	#define CHK_AppBPUpdate  (pfAppBPUpdate != NULL)
	#define EXP_AppBPUpdate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPUpdate", (RTS_UINTPTR)AppBPUpdate, 0, 0) 
#endif




/**
 * <description>Retrieves the first callstack entry (if available). This is the most nested calling position
 *	from the callstack. A callstack is only available, if the application in in state stop!</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="pContext" type="OUT">Returns register context, e.g. the base pointer to find the next calstack entry</param>
 * <param name="pCallstackEntry" type="OUT">Pointer to the callstack entry</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppBPGetFirstCallstackEntry(APPLICATION *pApp, RegContext *pContext, CallstackEntry *pCallstackEntry);
typedef RTS_RESULT (CDECL * PFAPPBPGETFIRSTCALLSTACKENTRY) (APPLICATION *pApp, RegContext *pContext, CallstackEntry *pCallstackEntry);
#if defined(CMPAPPBP_NOTIMPLEMENTED) || defined(APPBPGETFIRSTCALLSTACKENTRY_NOTIMPLEMENTED)
	#define USE_AppBPGetFirstCallstackEntry
	#define EXT_AppBPGetFirstCallstackEntry
	#define GET_AppBPGetFirstCallstackEntry(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppBPGetFirstCallstackEntry(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppBPGetFirstCallstackEntry  FALSE
	#define EXP_AppBPGetFirstCallstackEntry  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppBPGetFirstCallstackEntry
	#define EXT_AppBPGetFirstCallstackEntry
	#define GET_AppBPGetFirstCallstackEntry(fl)  CAL_CMGETAPI( "AppBPGetFirstCallstackEntry" ) 
	#define CAL_AppBPGetFirstCallstackEntry  AppBPGetFirstCallstackEntry
	#define CHK_AppBPGetFirstCallstackEntry  TRUE
	#define EXP_AppBPGetFirstCallstackEntry  CAL_CMEXPAPI( "AppBPGetFirstCallstackEntry" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPBP_EXTERNAL)
	#define USE_AppBPGetFirstCallstackEntry
	#define EXT_AppBPGetFirstCallstackEntry
	#define GET_AppBPGetFirstCallstackEntry(fl)  CAL_CMGETAPI( "AppBPGetFirstCallstackEntry" ) 
	#define CAL_AppBPGetFirstCallstackEntry  AppBPGetFirstCallstackEntry
	#define CHK_AppBPGetFirstCallstackEntry  TRUE
	#define EXP_AppBPGetFirstCallstackEntry  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPGetFirstCallstackEntry", (RTS_UINTPTR)AppBPGetFirstCallstackEntry, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppBPAppBPGetFirstCallstackEntry
	#define EXT_CmpAppBPAppBPGetFirstCallstackEntry
	#define GET_CmpAppBPAppBPGetFirstCallstackEntry  ERR_OK
	#define CAL_CmpAppBPAppBPGetFirstCallstackEntry pICmpAppBP->IAppBPGetFirstCallstackEntry
	#define CHK_CmpAppBPAppBPGetFirstCallstackEntry (pICmpAppBP != NULL)
	#define EXP_CmpAppBPAppBPGetFirstCallstackEntry  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppBPGetFirstCallstackEntry
	#define EXT_AppBPGetFirstCallstackEntry
	#define GET_AppBPGetFirstCallstackEntry(fl)  CAL_CMGETAPI( "AppBPGetFirstCallstackEntry" ) 
	#define CAL_AppBPGetFirstCallstackEntry pICmpAppBP->IAppBPGetFirstCallstackEntry
	#define CHK_AppBPGetFirstCallstackEntry (pICmpAppBP != NULL)
	#define EXP_AppBPGetFirstCallstackEntry  CAL_CMEXPAPI( "AppBPGetFirstCallstackEntry" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppBPGetFirstCallstackEntry  PFAPPBPGETFIRSTCALLSTACKENTRY pfAppBPGetFirstCallstackEntry;
	#define EXT_AppBPGetFirstCallstackEntry  extern PFAPPBPGETFIRSTCALLSTACKENTRY pfAppBPGetFirstCallstackEntry;
	#define GET_AppBPGetFirstCallstackEntry(fl)  s_pfCMGetAPI2( "AppBPGetFirstCallstackEntry", (RTS_VOID_FCTPTR *)&pfAppBPGetFirstCallstackEntry, (fl), 0, 0)
	#define CAL_AppBPGetFirstCallstackEntry  pfAppBPGetFirstCallstackEntry
	#define CHK_AppBPGetFirstCallstackEntry  (pfAppBPGetFirstCallstackEntry != NULL)
	#define EXP_AppBPGetFirstCallstackEntry  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPGetFirstCallstackEntry", (RTS_UINTPTR)AppBPGetFirstCallstackEntry, 0, 0) 
#endif




/**
 * <description>Retrieves the first callstack entry (if available). This is the most nested calling position
 *	from the callstack. A callstack is only available, if the application in in state stop!</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="hIecTask"IN">Handle to the desired task</param>
 * <param name="pContext" type="OUT">Returns register context, e.g. the base pointer to find the next calstack entry</param>
 * <param name="pCallstackEntry" type="OUT">Pointer to the callstack entry</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppBPGetFirstCallstackEntry2(APPLICATION *pApp, RTS_HANDLE hIecTask, RegContext *pContext, CallstackEntry *pCallstackEntry);
typedef RTS_RESULT (CDECL * PFAPPBPGETFIRSTCALLSTACKENTRY2) (APPLICATION *pApp, RTS_HANDLE hIecTask, RegContext *pContext, CallstackEntry *pCallstackEntry);
#if defined(CMPAPPBP_NOTIMPLEMENTED) || defined(APPBPGETFIRSTCALLSTACKENTRY2_NOTIMPLEMENTED)
	#define USE_AppBPGetFirstCallstackEntry2
	#define EXT_AppBPGetFirstCallstackEntry2
	#define GET_AppBPGetFirstCallstackEntry2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppBPGetFirstCallstackEntry2(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppBPGetFirstCallstackEntry2  FALSE
	#define EXP_AppBPGetFirstCallstackEntry2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppBPGetFirstCallstackEntry2
	#define EXT_AppBPGetFirstCallstackEntry2
	#define GET_AppBPGetFirstCallstackEntry2(fl)  CAL_CMGETAPI( "AppBPGetFirstCallstackEntry2" ) 
	#define CAL_AppBPGetFirstCallstackEntry2  AppBPGetFirstCallstackEntry2
	#define CHK_AppBPGetFirstCallstackEntry2  TRUE
	#define EXP_AppBPGetFirstCallstackEntry2  CAL_CMEXPAPI( "AppBPGetFirstCallstackEntry2" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPBP_EXTERNAL)
	#define USE_AppBPGetFirstCallstackEntry2
	#define EXT_AppBPGetFirstCallstackEntry2
	#define GET_AppBPGetFirstCallstackEntry2(fl)  CAL_CMGETAPI( "AppBPGetFirstCallstackEntry2" ) 
	#define CAL_AppBPGetFirstCallstackEntry2  AppBPGetFirstCallstackEntry2
	#define CHK_AppBPGetFirstCallstackEntry2  TRUE
	#define EXP_AppBPGetFirstCallstackEntry2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPGetFirstCallstackEntry2", (RTS_UINTPTR)AppBPGetFirstCallstackEntry2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppBPAppBPGetFirstCallstackEntry2
	#define EXT_CmpAppBPAppBPGetFirstCallstackEntry2
	#define GET_CmpAppBPAppBPGetFirstCallstackEntry2  ERR_OK
	#define CAL_CmpAppBPAppBPGetFirstCallstackEntry2 pICmpAppBP->IAppBPGetFirstCallstackEntry2
	#define CHK_CmpAppBPAppBPGetFirstCallstackEntry2 (pICmpAppBP != NULL)
	#define EXP_CmpAppBPAppBPGetFirstCallstackEntry2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppBPGetFirstCallstackEntry2
	#define EXT_AppBPGetFirstCallstackEntry2
	#define GET_AppBPGetFirstCallstackEntry2(fl)  CAL_CMGETAPI( "AppBPGetFirstCallstackEntry2" ) 
	#define CAL_AppBPGetFirstCallstackEntry2 pICmpAppBP->IAppBPGetFirstCallstackEntry2
	#define CHK_AppBPGetFirstCallstackEntry2 (pICmpAppBP != NULL)
	#define EXP_AppBPGetFirstCallstackEntry2  CAL_CMEXPAPI( "AppBPGetFirstCallstackEntry2" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppBPGetFirstCallstackEntry2  PFAPPBPGETFIRSTCALLSTACKENTRY2 pfAppBPGetFirstCallstackEntry2;
	#define EXT_AppBPGetFirstCallstackEntry2  extern PFAPPBPGETFIRSTCALLSTACKENTRY2 pfAppBPGetFirstCallstackEntry2;
	#define GET_AppBPGetFirstCallstackEntry2(fl)  s_pfCMGetAPI2( "AppBPGetFirstCallstackEntry2", (RTS_VOID_FCTPTR *)&pfAppBPGetFirstCallstackEntry2, (fl), 0, 0)
	#define CAL_AppBPGetFirstCallstackEntry2  pfAppBPGetFirstCallstackEntry2
	#define CHK_AppBPGetFirstCallstackEntry2  (pfAppBPGetFirstCallstackEntry2 != NULL)
	#define EXP_AppBPGetFirstCallstackEntry2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPGetFirstCallstackEntry2", (RTS_UINTPTR)AppBPGetFirstCallstackEntry2, 0, 0) 
#endif




/**
 * <description>Retrieves the next callstack entry (if available). This is the less nested calling position
 *	from the previous call or the AppGetFirstCallstackEntry() function.</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="pContext" type="OUT">Returns register context, e.g. the base pointer to find the next calstack entry</param>
 * <param name="pCallstackEntry" type="OUT">Pointer to the callstack entry</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppBPGetNextCallstackEntry(APPLICATION *pApp, RegContext *pContext, CallstackEntry *pCallstackEntry);
typedef RTS_RESULT (CDECL * PFAPPBPGETNEXTCALLSTACKENTRY) (APPLICATION *pApp, RegContext *pContext, CallstackEntry *pCallstackEntry);
#if defined(CMPAPPBP_NOTIMPLEMENTED) || defined(APPBPGETNEXTCALLSTACKENTRY_NOTIMPLEMENTED)
	#define USE_AppBPGetNextCallstackEntry
	#define EXT_AppBPGetNextCallstackEntry
	#define GET_AppBPGetNextCallstackEntry(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppBPGetNextCallstackEntry(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppBPGetNextCallstackEntry  FALSE
	#define EXP_AppBPGetNextCallstackEntry  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppBPGetNextCallstackEntry
	#define EXT_AppBPGetNextCallstackEntry
	#define GET_AppBPGetNextCallstackEntry(fl)  CAL_CMGETAPI( "AppBPGetNextCallstackEntry" ) 
	#define CAL_AppBPGetNextCallstackEntry  AppBPGetNextCallstackEntry
	#define CHK_AppBPGetNextCallstackEntry  TRUE
	#define EXP_AppBPGetNextCallstackEntry  CAL_CMEXPAPI( "AppBPGetNextCallstackEntry" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPBP_EXTERNAL)
	#define USE_AppBPGetNextCallstackEntry
	#define EXT_AppBPGetNextCallstackEntry
	#define GET_AppBPGetNextCallstackEntry(fl)  CAL_CMGETAPI( "AppBPGetNextCallstackEntry" ) 
	#define CAL_AppBPGetNextCallstackEntry  AppBPGetNextCallstackEntry
	#define CHK_AppBPGetNextCallstackEntry  TRUE
	#define EXP_AppBPGetNextCallstackEntry  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPGetNextCallstackEntry", (RTS_UINTPTR)AppBPGetNextCallstackEntry, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppBPAppBPGetNextCallstackEntry
	#define EXT_CmpAppBPAppBPGetNextCallstackEntry
	#define GET_CmpAppBPAppBPGetNextCallstackEntry  ERR_OK
	#define CAL_CmpAppBPAppBPGetNextCallstackEntry pICmpAppBP->IAppBPGetNextCallstackEntry
	#define CHK_CmpAppBPAppBPGetNextCallstackEntry (pICmpAppBP != NULL)
	#define EXP_CmpAppBPAppBPGetNextCallstackEntry  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppBPGetNextCallstackEntry
	#define EXT_AppBPGetNextCallstackEntry
	#define GET_AppBPGetNextCallstackEntry(fl)  CAL_CMGETAPI( "AppBPGetNextCallstackEntry" ) 
	#define CAL_AppBPGetNextCallstackEntry pICmpAppBP->IAppBPGetNextCallstackEntry
	#define CHK_AppBPGetNextCallstackEntry (pICmpAppBP != NULL)
	#define EXP_AppBPGetNextCallstackEntry  CAL_CMEXPAPI( "AppBPGetNextCallstackEntry" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppBPGetNextCallstackEntry  PFAPPBPGETNEXTCALLSTACKENTRY pfAppBPGetNextCallstackEntry;
	#define EXT_AppBPGetNextCallstackEntry  extern PFAPPBPGETNEXTCALLSTACKENTRY pfAppBPGetNextCallstackEntry;
	#define GET_AppBPGetNextCallstackEntry(fl)  s_pfCMGetAPI2( "AppBPGetNextCallstackEntry", (RTS_VOID_FCTPTR *)&pfAppBPGetNextCallstackEntry, (fl), 0, 0)
	#define CAL_AppBPGetNextCallstackEntry  pfAppBPGetNextCallstackEntry
	#define CHK_AppBPGetNextCallstackEntry  (pfAppBPGetNextCallstackEntry != NULL)
	#define EXP_AppBPGetNextCallstackEntry  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPGetNextCallstackEntry", (RTS_UINTPTR)AppBPGetNextCallstackEntry, 0, 0) 
#endif




/**
 * <description>Retrieves the next callstack entry (if available). This is the less nested calling position
 *	from the previous call or the AppGetFirstCallstackEntry() function.</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="bIecCode" type="IN">Specifies, if callstack is searched in IecCode. If bIecCode is 0, we search in C-code! </param>
 * <param name="pContext" type="OUT">Returns register context, e.g. the base pointer to find the next calstack entry</param>
 * <param name="pCallstackEntry" type="OUT">Pointer to the callstack entry</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppBPGetNextCallstackEntry2(APPLICATION *pApp, int bIecCode, RegContext *pContext, CallstackEntry *pCallstackEntry);
typedef RTS_RESULT (CDECL * PFAPPBPGETNEXTCALLSTACKENTRY2) (APPLICATION *pApp, int bIecCode, RegContext *pContext, CallstackEntry *pCallstackEntry);
#if defined(CMPAPPBP_NOTIMPLEMENTED) || defined(APPBPGETNEXTCALLSTACKENTRY2_NOTIMPLEMENTED)
	#define USE_AppBPGetNextCallstackEntry2
	#define EXT_AppBPGetNextCallstackEntry2
	#define GET_AppBPGetNextCallstackEntry2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppBPGetNextCallstackEntry2(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppBPGetNextCallstackEntry2  FALSE
	#define EXP_AppBPGetNextCallstackEntry2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppBPGetNextCallstackEntry2
	#define EXT_AppBPGetNextCallstackEntry2
	#define GET_AppBPGetNextCallstackEntry2(fl)  CAL_CMGETAPI( "AppBPGetNextCallstackEntry2" ) 
	#define CAL_AppBPGetNextCallstackEntry2  AppBPGetNextCallstackEntry2
	#define CHK_AppBPGetNextCallstackEntry2  TRUE
	#define EXP_AppBPGetNextCallstackEntry2  CAL_CMEXPAPI( "AppBPGetNextCallstackEntry2" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPBP_EXTERNAL)
	#define USE_AppBPGetNextCallstackEntry2
	#define EXT_AppBPGetNextCallstackEntry2
	#define GET_AppBPGetNextCallstackEntry2(fl)  CAL_CMGETAPI( "AppBPGetNextCallstackEntry2" ) 
	#define CAL_AppBPGetNextCallstackEntry2  AppBPGetNextCallstackEntry2
	#define CHK_AppBPGetNextCallstackEntry2  TRUE
	#define EXP_AppBPGetNextCallstackEntry2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPGetNextCallstackEntry2", (RTS_UINTPTR)AppBPGetNextCallstackEntry2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppBPAppBPGetNextCallstackEntry2
	#define EXT_CmpAppBPAppBPGetNextCallstackEntry2
	#define GET_CmpAppBPAppBPGetNextCallstackEntry2  ERR_OK
	#define CAL_CmpAppBPAppBPGetNextCallstackEntry2 pICmpAppBP->IAppBPGetNextCallstackEntry2
	#define CHK_CmpAppBPAppBPGetNextCallstackEntry2 (pICmpAppBP != NULL)
	#define EXP_CmpAppBPAppBPGetNextCallstackEntry2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppBPGetNextCallstackEntry2
	#define EXT_AppBPGetNextCallstackEntry2
	#define GET_AppBPGetNextCallstackEntry2(fl)  CAL_CMGETAPI( "AppBPGetNextCallstackEntry2" ) 
	#define CAL_AppBPGetNextCallstackEntry2 pICmpAppBP->IAppBPGetNextCallstackEntry2
	#define CHK_AppBPGetNextCallstackEntry2 (pICmpAppBP != NULL)
	#define EXP_AppBPGetNextCallstackEntry2  CAL_CMEXPAPI( "AppBPGetNextCallstackEntry2" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppBPGetNextCallstackEntry2  PFAPPBPGETNEXTCALLSTACKENTRY2 pfAppBPGetNextCallstackEntry2;
	#define EXT_AppBPGetNextCallstackEntry2  extern PFAPPBPGETNEXTCALLSTACKENTRY2 pfAppBPGetNextCallstackEntry2;
	#define GET_AppBPGetNextCallstackEntry2(fl)  s_pfCMGetAPI2( "AppBPGetNextCallstackEntry2", (RTS_VOID_FCTPTR *)&pfAppBPGetNextCallstackEntry2, (fl), 0, 0)
	#define CAL_AppBPGetNextCallstackEntry2  pfAppBPGetNextCallstackEntry2
	#define CHK_AppBPGetNextCallstackEntry2  (pfAppBPGetNextCallstackEntry2 != NULL)
	#define EXP_AppBPGetNextCallstackEntry2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPGetNextCallstackEntry2", (RTS_UINTPTR)AppBPGetNextCallstackEntry2, 0, 0) 
#endif




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
RTS_RESULT CDECL AppBPServiceHandler2(RTS_UI32 ulChannelId, HEADER_TAG *pHeaderTag, PROTOCOL_DATA_UNIT pduData, PROTOCOL_DATA_UNIT *pduSendBuffer);
typedef RTS_RESULT (CDECL * PFAPPBPSERVICEHANDLER2) (RTS_UI32 ulChannelId, HEADER_TAG *pHeaderTag, PROTOCOL_DATA_UNIT pduData, PROTOCOL_DATA_UNIT *pduSendBuffer);
#if defined(CMPAPPBP_NOTIMPLEMENTED) || defined(APPBPSERVICEHANDLER2_NOTIMPLEMENTED)
	#define USE_AppBPServiceHandler2
	#define EXT_AppBPServiceHandler2
	#define GET_AppBPServiceHandler2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppBPServiceHandler2(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppBPServiceHandler2  FALSE
	#define EXP_AppBPServiceHandler2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppBPServiceHandler2
	#define EXT_AppBPServiceHandler2
	#define GET_AppBPServiceHandler2(fl)  CAL_CMGETAPI( "AppBPServiceHandler2" ) 
	#define CAL_AppBPServiceHandler2  AppBPServiceHandler2
	#define CHK_AppBPServiceHandler2  TRUE
	#define EXP_AppBPServiceHandler2  CAL_CMEXPAPI( "AppBPServiceHandler2" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPBP_EXTERNAL)
	#define USE_AppBPServiceHandler2
	#define EXT_AppBPServiceHandler2
	#define GET_AppBPServiceHandler2(fl)  CAL_CMGETAPI( "AppBPServiceHandler2" ) 
	#define CAL_AppBPServiceHandler2  AppBPServiceHandler2
	#define CHK_AppBPServiceHandler2  TRUE
	#define EXP_AppBPServiceHandler2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPServiceHandler2", (RTS_UINTPTR)AppBPServiceHandler2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppBPAppBPServiceHandler2
	#define EXT_CmpAppBPAppBPServiceHandler2
	#define GET_CmpAppBPAppBPServiceHandler2  ERR_OK
	#define CAL_CmpAppBPAppBPServiceHandler2 pICmpAppBP->IAppBPServiceHandler2
	#define CHK_CmpAppBPAppBPServiceHandler2 (pICmpAppBP != NULL)
	#define EXP_CmpAppBPAppBPServiceHandler2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppBPServiceHandler2
	#define EXT_AppBPServiceHandler2
	#define GET_AppBPServiceHandler2(fl)  CAL_CMGETAPI( "AppBPServiceHandler2" ) 
	#define CAL_AppBPServiceHandler2 pICmpAppBP->IAppBPServiceHandler2
	#define CHK_AppBPServiceHandler2 (pICmpAppBP != NULL)
	#define EXP_AppBPServiceHandler2  CAL_CMEXPAPI( "AppBPServiceHandler2" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppBPServiceHandler2  PFAPPBPSERVICEHANDLER2 pfAppBPServiceHandler2;
	#define EXT_AppBPServiceHandler2  extern PFAPPBPSERVICEHANDLER2 pfAppBPServiceHandler2;
	#define GET_AppBPServiceHandler2(fl)  s_pfCMGetAPI2( "AppBPServiceHandler2", (RTS_VOID_FCTPTR *)&pfAppBPServiceHandler2, (fl), 0, 0)
	#define CAL_AppBPServiceHandler2  pfAppBPServiceHandler2
	#define CHK_AppBPServiceHandler2  (pfAppBPServiceHandler2 != NULL)
	#define EXP_AppBPServiceHandler2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPServiceHandler2", (RTS_UINTPTR)AppBPServiceHandler2, 0, 0) 
#endif




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
RTS_RESULT CDECL AppBPSet(BreakpointDesc *pBpDesc, RTS_BOOL bPatchCode, Breakpoint** ppbpOut);
typedef RTS_RESULT (CDECL * PFAPPBPSET) (BreakpointDesc *pBpDesc, RTS_BOOL bPatchCode, Breakpoint** ppbpOut);
#if defined(CMPAPPBP_NOTIMPLEMENTED) || defined(APPBPSET_NOTIMPLEMENTED)
	#define USE_AppBPSet
	#define EXT_AppBPSet
	#define GET_AppBPSet(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppBPSet(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppBPSet  FALSE
	#define EXP_AppBPSet  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppBPSet
	#define EXT_AppBPSet
	#define GET_AppBPSet(fl)  CAL_CMGETAPI( "AppBPSet" ) 
	#define CAL_AppBPSet  AppBPSet
	#define CHK_AppBPSet  TRUE
	#define EXP_AppBPSet  CAL_CMEXPAPI( "AppBPSet" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPBP_EXTERNAL)
	#define USE_AppBPSet
	#define EXT_AppBPSet
	#define GET_AppBPSet(fl)  CAL_CMGETAPI( "AppBPSet" ) 
	#define CAL_AppBPSet  AppBPSet
	#define CHK_AppBPSet  TRUE
	#define EXP_AppBPSet  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPSet", (RTS_UINTPTR)AppBPSet, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppBPAppBPSet
	#define EXT_CmpAppBPAppBPSet
	#define GET_CmpAppBPAppBPSet  ERR_OK
	#define CAL_CmpAppBPAppBPSet pICmpAppBP->IAppBPSet
	#define CHK_CmpAppBPAppBPSet (pICmpAppBP != NULL)
	#define EXP_CmpAppBPAppBPSet  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppBPSet
	#define EXT_AppBPSet
	#define GET_AppBPSet(fl)  CAL_CMGETAPI( "AppBPSet" ) 
	#define CAL_AppBPSet pICmpAppBP->IAppBPSet
	#define CHK_AppBPSet (pICmpAppBP != NULL)
	#define EXP_AppBPSet  CAL_CMEXPAPI( "AppBPSet" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppBPSet  PFAPPBPSET pfAppBPSet;
	#define EXT_AppBPSet  extern PFAPPBPSET pfAppBPSet;
	#define GET_AppBPSet(fl)  s_pfCMGetAPI2( "AppBPSet", (RTS_VOID_FCTPTR *)&pfAppBPSet, (fl), 0, 0)
	#define CAL_AppBPSet  pfAppBPSet
	#define CHK_AppBPSet  (pfAppBPSet != NULL)
	#define EXP_AppBPSet  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPSet", (RTS_UINTPTR)AppBPSet, 0, 0) 
#endif




/**
 * <description>Delete a breakpoint
 *	ATTENTION ATTENTION ATTENTION:
 *	Only for internal use in the runtime system!! Don't use it in adaptations!
 * </description>
 * <param name="pbp" type="IN">Pointer to breakpoint retrieved by AppBPSet()</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AppBPDelete(Breakpoint *pbp);
typedef RTS_RESULT (CDECL * PFAPPBPDELETE) (Breakpoint *pbp);
#if defined(CMPAPPBP_NOTIMPLEMENTED) || defined(APPBPDELETE_NOTIMPLEMENTED)
	#define USE_AppBPDelete
	#define EXT_AppBPDelete
	#define GET_AppBPDelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AppBPDelete(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AppBPDelete  FALSE
	#define EXP_AppBPDelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AppBPDelete
	#define EXT_AppBPDelete
	#define GET_AppBPDelete(fl)  CAL_CMGETAPI( "AppBPDelete" ) 
	#define CAL_AppBPDelete  AppBPDelete
	#define CHK_AppBPDelete  TRUE
	#define EXP_AppBPDelete  CAL_CMEXPAPI( "AppBPDelete" ) 
#elif defined(MIXED_LINK) && !defined(CMPAPPBP_EXTERNAL)
	#define USE_AppBPDelete
	#define EXT_AppBPDelete
	#define GET_AppBPDelete(fl)  CAL_CMGETAPI( "AppBPDelete" ) 
	#define CAL_AppBPDelete  AppBPDelete
	#define CHK_AppBPDelete  TRUE
	#define EXP_AppBPDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPDelete", (RTS_UINTPTR)AppBPDelete, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAppBPAppBPDelete
	#define EXT_CmpAppBPAppBPDelete
	#define GET_CmpAppBPAppBPDelete  ERR_OK
	#define CAL_CmpAppBPAppBPDelete pICmpAppBP->IAppBPDelete
	#define CHK_CmpAppBPAppBPDelete (pICmpAppBP != NULL)
	#define EXP_CmpAppBPAppBPDelete  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AppBPDelete
	#define EXT_AppBPDelete
	#define GET_AppBPDelete(fl)  CAL_CMGETAPI( "AppBPDelete" ) 
	#define CAL_AppBPDelete pICmpAppBP->IAppBPDelete
	#define CHK_AppBPDelete (pICmpAppBP != NULL)
	#define EXP_AppBPDelete  CAL_CMEXPAPI( "AppBPDelete" ) 
#else /* DYNAMIC_LINK */
	#define USE_AppBPDelete  PFAPPBPDELETE pfAppBPDelete;
	#define EXT_AppBPDelete  extern PFAPPBPDELETE pfAppBPDelete;
	#define GET_AppBPDelete(fl)  s_pfCMGetAPI2( "AppBPDelete", (RTS_VOID_FCTPTR *)&pfAppBPDelete, (fl), 0, 0)
	#define CAL_AppBPDelete  pfAppBPDelete
	#define CHK_AppBPDelete  (pfAppBPDelete != NULL)
	#define EXP_AppBPDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AppBPDelete", (RTS_UINTPTR)AppBPDelete, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFAPPBPINIT IAppBPInit;
 	PFAPPBPEXIT IAppBPExit;
 	PFAPPDEBUGHANDLER IAppDebugHandler;
 	PFAPPDEBUGHANDLER2 IAppDebugHandler2;
 	PFAPPBPGETFIRST IAppBPGetFirst;
 	PFAPPBPGETNEXT IAppBPGetNext;
 	PFAPPBPDELETEALL IAppBPDeleteAll;
 	PFAPPBPDELETEALLWITHEXECUTIONPOINTS IAppBPDeleteAllWithExecutionpoints;
 	PFAPPBPLEAVE IAppBPLeave;
 	PFAPPBPSTEP IAppBPStep;
 	PFAPPBPGETHITCOUNT IAppBPGetHitCount;
 	PFAPPBPUPDATE IAppBPUpdate;
 	PFAPPBPGETFIRSTCALLSTACKENTRY IAppBPGetFirstCallstackEntry;
 	PFAPPBPGETFIRSTCALLSTACKENTRY2 IAppBPGetFirstCallstackEntry2;
 	PFAPPBPGETNEXTCALLSTACKENTRY IAppBPGetNextCallstackEntry;
 	PFAPPBPGETNEXTCALLSTACKENTRY2 IAppBPGetNextCallstackEntry2;
 	PFAPPBPSERVICEHANDLER2 IAppBPServiceHandler2;
 	PFAPPBPSET IAppBPSet;
 	PFAPPBPDELETE IAppBPDelete;
 } ICmpAppBP_C;

#ifdef CPLUSPLUS
class ICmpAppBP : public IBase
{
	public:
		virtual RTS_RESULT CDECL IAppBPInit(APPLICATION *pApp) =0;
		virtual RTS_RESULT CDECL IAppBPExit(APPLICATION *pApp) =0;
		virtual RTS_UINTPTR CDECL IAppDebugHandler(RTS_UINTPTR IP, RTS_UINTPTR SP, RTS_UINTPTR BP) =0;
		virtual RTS_UINTPTR CDECL IAppDebugHandler2(BreakpointContext *pBPContext) =0;
		virtual Breakpoint * CDECL IAppBPGetFirst(APPLICATION *pApp, RTS_RESULT *pResult) =0;
		virtual Breakpoint * CDECL IAppBPGetNext(APPLICATION *pApp, Breakpoint *pPrevBreakpoint, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IAppBPDeleteAll(APPLICATION *pApp, RTS_UI32 ulSessionId) =0;
		virtual RTS_RESULT CDECL IAppBPDeleteAllWithExecutionpoints(APPLICATION *pApp, RTS_UI32 ulSessionId) =0;
		virtual RTS_RESULT CDECL IAppBPLeave(APPLICATION *pApp) =0;
		virtual RTS_RESULT CDECL IAppBPStep(APPLICATION *pApp) =0;
		virtual RTS_RESULT CDECL IAppBPGetHitCount(APPLICATION *pApp, int *piHitCount) =0;
		virtual RTS_RESULT CDECL IAppBPUpdate(APPLICATION *pApp, RTS_SIZE ulTypeIn) =0;
		virtual RTS_RESULT CDECL IAppBPGetFirstCallstackEntry(APPLICATION *pApp, RegContext *pContext, CallstackEntry *pCallstackEntry) =0;
		virtual RTS_RESULT CDECL IAppBPGetFirstCallstackEntry2(APPLICATION *pApp, RTS_HANDLE hIecTask, RegContext *pContext, CallstackEntry *pCallstackEntry) =0;
		virtual RTS_RESULT CDECL IAppBPGetNextCallstackEntry(APPLICATION *pApp, RegContext *pContext, CallstackEntry *pCallstackEntry) =0;
		virtual RTS_RESULT CDECL IAppBPGetNextCallstackEntry2(APPLICATION *pApp, int bIecCode, RegContext *pContext, CallstackEntry *pCallstackEntry) =0;
		virtual RTS_RESULT CDECL IAppBPServiceHandler2(RTS_UI32 ulChannelId, HEADER_TAG *pHeaderTag, PROTOCOL_DATA_UNIT pduData, PROTOCOL_DATA_UNIT *pduSendBuffer) =0;
		virtual RTS_RESULT CDECL IAppBPSet(BreakpointDesc *pBpDesc, RTS_BOOL bPatchCode, Breakpoint** ppbpOut) =0;
		virtual RTS_RESULT CDECL IAppBPDelete(Breakpoint *pbp) =0;
};
	#ifndef ITF_CmpAppBP
		#define ITF_CmpAppBP static ICmpAppBP *pICmpAppBP = NULL;
	#endif
	#define EXTITF_CmpAppBP
#else	/*CPLUSPLUS*/
	typedef ICmpAppBP_C		ICmpAppBP;
	#ifndef ITF_CmpAppBP
		#define ITF_CmpAppBP
	#endif
	#define EXTITF_CmpAppBP
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPAPPBPITF_H_*/
