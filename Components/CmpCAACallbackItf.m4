/**
 * <interfacename>CmpCAACallback</interfacename>
 * <description> 
 *	<p></p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpCAACallback')

#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"

/**
 * <category>Static defines</category>
 * <description>Number of static events</description>
 */
#ifndef CB_NUM_OF_STATIC_EVENTS
	#define CB_NUM_OF_STATIC_EVENTS		0x10
#endif

#ifndef CB_EVENT_TASK_PRIORITY
	#define CB_EVENT_TASK_PRIORITY		TASKPRIO_SYSTEM_END - 1
#endif

/**
 * <category>Static defines</category>
 * <description>Number of static callbacks</description>
 */
#ifndef NUM_OF_STATIC_CALLBACKS
	#define NUM_OF_STATIC_CALLBACKS		0x20
#endif

/**
 * <category>Static defines</category>
 * <description>EventIds and their classes. End definition is the first ID,which does NOT belong to the interval</description>
 */
#define CLASS_ONLINE_EVENTS_START				1000
#define CLASS_ONLINE_EVENTS_END					1999

#define CLASS_INFOS_START						2000
#define CLASS_INFOS_END							2999

#define CLASS_WARNINGS_START					3000
#define CLASS_WARNINGS_END						3999

#define CLASS_RTS_ERRORS_START					4000
#define CLASS_RTS_ERRORS_END					4999

#define CLASS_SYSTEM_EXCETPTIONS_START			5000
#define CLASS_SYSTEM_EXCETPTIONS_END			5999

#define CLASS_INTERRUPTS_START					6000
#define CLASS_INTERRUPTS_END					6999

#define CLASS_IO_START							7000
#define CLASS_IO_END							7499

#define CLASS_FIELDBUS_START					8000
#define CLASS_FIELDBUS_END						9899

#define CLASS_TIMERS_START						9900
#define CLASS_TIMERS_END						9999

#define CLASS_MANUFACTURES_START				10000


/**
 * <category> Callback</category>
 * <description></description>
 *	<element name="Param1" type="IN">dwSpec. Event and EventClass encoded</element>
 *	<element name="Param2" type="IN">EventSource</element>
 *	<element name="Param3" type="IN">Parameter</element>
 *  <result>unused</result>
 */
typedef RTS_IEC_XWORD (*PFCALLBACK)(RTS_IEC_XWORD, RTS_IEC_XWORD, RTS_IEC_XWORD);

/**
 * <category>Error codes</category>
 * <description></description>
 *	<element name="CB_NO_ERROR" type="OUT">No error</element>
 *	<element name="CB_FIRST_ERROR" type="OUT">First error</element>
 *	<element name="CB_HANDLE_INVALID" type="OUT">The handle is invalid</element>
 *	<element name="CB_UNKNOWN_EVENT" type="OUT">The event is unknown</element>
 *	<element name="CB_CALLBACK_NOT_REMOVABLE" type="OUT">This callback can not be removed</element>
 *	<element name="CB_WRONG_ARGUMENT" type="OUT">The argument was wrong</element>
 *	<element name="CB_NO_MEMORY" type="OUT">Not enough memory</element>
 *	<element name="CB_EVENT_EXISTS" type="OUT">The event already exists</element>
 *	<element name="CB_CALL_CALLBACKS_FAILED" type="OUT">The call of one callback failed</element>
 *	<element name="CB_NO_SYSTEM_EVENT" type="OUT">The specified event is not an system event</element>
 *	<element name="CB_BUFFER_NOT_AVAILABLE" type="OUT">No buffer available</element>
 *	<element name="CB_SYSTEM_EVENT" type="OUT">The event, which should be sent or posted, is a system event</element>
 *	<element name="CB_FIRST_MF" type="OUT">First MF error</element>
 *	<element name="CB_LAST_ERROR" type="OUT">Last error</element>
 */

#define CB_NO_ERROR					((CAA_ERROR)0)
#define CB_FIRST_ERROR				((CAA_ERROR)20000)
#define CB_HANDLE_INVALID 			((CAA_ERROR)20001)
#define CB_UNKNOWN_EVENT 			((CAA_ERROR)20002)
#define CB_CALLBACK_NOT_REMOVABLE 	((CAA_ERROR)20003)
#define CB_WRONG_ARGUMENT 			((CAA_ERROR)20004)
#define CB_NO_MEMORY				((CAA_ERROR)20005)
#define CB_EVENT_EXISTS				((CAA_ERROR)20006)
#define CB_CALL_CALLBACKS_FAILED	((CAA_ERROR)20007)
#define CB_NO_SYSTEM_EVENT			((CAA_ERROR)20008)
#define CB_BUFFER_NOT_AVAILABLE		((CAA_ERROR)20009)
#define CB_SYSTEM_EVENT				((CAA_ERROR)20010)
#define CB_FIRST_MF					((CAA_ERROR)20050)
#define CB_LAST_ERROR				((CAA_ERROR)20099)

/**
 * <category> Events</category>
 * <description></description>
 *	<element name="CB_ALL_EVENTS" type="IN">All events</element>
 */
#define	CB_ALL_EVENTS					((CAA_ENUM)-1)
#define	CB_NO_EVENT						((CAA_ENUM)0)

	/* CB_ONLINE_EVENTS */
#define	CB_START						((CAA_ENUM)1000)
#define	CB_STOP							((CAA_ENUM)1001)
#define	CB_BEFORE_RESET					((CAA_ENUM)1002)
#define	CB_AFTER_RESET					((CAA_ENUM)1003)
#define	CB_SHUTDOWN						((CAA_ENUM)1004)
#define	CB_ONLINE_CHANGE				((CAA_ENUM)1005)
#define	CB_BEFORE_DOWNLOAD				((CAA_ENUM)1006)
#define	CB_TASKCODE_NOT_CALLED			((CAA_ENUM)1007)
#define	CB_TIMER						((CAA_ENUM)1008)
#define	CB_DEBUG_LOOP					((CAA_ENUM)1009)
#define	CB_SCHEDULE						((CAA_ENUM)1010)

	/* CB_RTS_ERRORS */
#define	CB_ERR_WATCHDOG					((CAA_ENUM)4000)
#define	CB_ERR_HARDWARE_WATCHDOG		((CAA_ENUM)4001)
#define	CB_ERR_FIELDBUS					((CAA_ENUM)4002)
#define	CB_ERR_IOUPDATE					((CAA_ENUM)4003)
#define	CB_ERR_POWERFAIL				((CAA_ENUM)4004)

	/* CB_SYSTEM_EXCEPTIONS */
#define	CB_EXCPT_ILLEGAL_INSTRUCTION	((CAA_ENUM)5000)
#define	CB_EXCPT_ACCESS_VIOLATION		((CAA_ENUM)5001)
#define	CB_EXCPT_PRIV_INSTRUCTION		((CAA_ENUM)5002)
#define	CB_EXCPT_IN_PAGE_ERROR			((CAA_ENUM)5003)
#define	CB_EXCPT_STACK_OVERFLOW			((CAA_ENUM)5004)
#define	CB_EXCPT_MISALIGNMENT			((CAA_ENUM)5005)
#define	CB_EXCPT_ARRAYBOUNDS			((CAA_ENUM)5006)
#define	CB_EXCPT_DIVIDEBYZERO			((CAA_ENUM)5007)
#define	CB_EXCPT_OVERFLOW				((CAA_ENUM)5008)
#define	CB_EXCPT_NONCONTINUABLE			((CAA_ENUM)5009)

#define	CB_EXCPT_NO_FPU_AVAILABLE		((CAA_ENUM)5500)
#define	CB_EXCPT_FPU_ERROR				((CAA_ENUM)5501)
#define	CB_EXCPT_FPU_DENORMAL_OPERAND	((CAA_ENUM)5502)
#define	CB_EXCPT_FPU_DIVIDEBYZERO		((CAA_ENUM)5503)
#define	CB_EXCPT_FPU_INVALID_OPERATION	((CAA_ENUM)5504)
#define	CB_EXCPT_FPU_OVERFLOW			((CAA_ENUM)5505)
#define	CB_EXCPT_FPU_STACK_CHECK		((CAA_ENUM)5506)

	/* CB_INTERRUPTS */
#define	CB_INTERRUPT_0					((CAA_ENUM)6000)
#define	CB_INTERRUPT_1					((CAA_ENUM)6001)
#define	CB_INTERRUPT_2					((CAA_ENUM)6002)
#define	CB_INTERRUPT_3					((CAA_ENUM)6003)
#define	CB_INTERRUPT_4					((CAA_ENUM)6004)
#define	CB_INTERRUPT_5					((CAA_ENUM)6005)
#define	CB_INTERRUPT_6					((CAA_ENUM)6006)
#define	CB_INTERRUPT_7					((CAA_ENUM)6007)
#define	CB_INTERRUPT_8					((CAA_ENUM)6008)
#define	CB_INTERRUPT_9					((CAA_ENUM)6009)
#define	CB_INTERRUPT_10					((CAA_ENUM)6010)
#define	CB_INTERRUPT_11					((CAA_ENUM)6011)
#define	CB_INTERRUPT_12					((CAA_ENUM)6012)
#define	CB_INTERRUPT_13					((CAA_ENUM)6013)
#define	CB_INTERRUPT_14					((CAA_ENUM)6014)
#define	CB_INTERRUPT_15					((CAA_ENUM)6015)
#define	CB_INTERRUPT_255				((CAA_ENUM)6255)

	/* CB_IO */
#define	CB_AFTER_READING_INPUTS			((CAA_ENUM)7000)
#define	CB_BEFORE_WRITING_OUTPUTS		((CAA_ENUM)7001)

/**
 * <category> Event classes</category>
 * <description></description>
 *	<element name="CB_ALL_CLASSES" type="IN">All event classes</element>
 */
#define	CB_ALL_CLASSES			((CAA_ENUM)-1)
#define	CB_NO_CLASS				((CAA_ENUM)0x0000)
#define	CB_ONLINE_EVENTS		((CAA_ENUM)0x0001)
#define	CB_INFOS				((CAA_ENUM)0x0002)
#define	CB_WARNINGS				((CAA_ENUM)0x0004)
#define	CB_RTS_ERRORS			((CAA_ENUM)0x0008)
#define	CB_SYSTEM_EXCEPTIONS	((CAA_ENUM)0x0010)
#define	CB_INTERRUPTS			((CAA_ENUM)0x0020)
#define	CB_IO					((CAA_ENUM)0x0040)
#define	CB_FIELDBUS				((CAA_ENUM)0x0080)
#define	CB_TIMERS				((CAA_ENUM)0x0100)
#define	CB_MANUF_SPEC			((CAA_ENUM)0x0200)


/**
 * <category> Event sources</category>
 * <description></description>
 *	<element name="CB_ALL_SOURCES" type="IN">All event sources</element>
 */
#define	CB_ALL_SOURCES			((CAA_ENUM)-1)
#define	CB_NO_SOURCE			((CAA_ENUM)0x0000)
#define	CB_RUNTIME				((CAA_ENUM)0x0001)
#define	CB_SYSTEM				((CAA_ENUM)0x0002)
#define	CB_IECTASK				((CAA_ENUM)0x0004)
#define	CB_IECPROGRAMM			((CAA_ENUM)0x0008)
#define	CB_DRIVER				((CAA_ENUM)0x0010)

/**
 * <category> Struct of a callback</category>
 * <description></description>
 *	<element name="CB_ALL_SOURCES" type="IN">All event sources</element>
 */
typedef struct CB_CALLBACKtag
{
	PFCALLBACK		pfCallback;
	CAA_ENUM		eEvent;
	CAA_ENUM		eClass;
	CAA_ENUM		eSource;
}CB_CALLBACK;

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>cb_callfunctionbyindex</description>
 */
typedef struct tagcb_callfunctionbyindex_struct
{
	CAA_PVOID pPOUFunc;					/* VAR_INPUT */	/* Pointer to function to call */
	RTS_IEC_XWORD dwParam1;				/* VAR_INPUT */	/* prameter 1 */
	RTS_IEC_XWORD dwParam2;				/* VAR_INPUT */	/* prameter 2 */
	RTS_IEC_XWORD dwParam3;				/* VAR_INPUT */	/* prameter 3 */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	RTS_IEC_XWORD CB_CallFunctionByIndex;	/* VAR_OUTPUT */	
} cb_callfunctionbyindex_struct;

DEF_API(`void',`CDECL',`cb_callfunctionbyindex',`(cb_callfunctionbyindex_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x1530A820),0x03050528)

/**
 * <description>cb_decodeclass</description>
 */
typedef struct tagcb_decodeclass_struct
{
	RTS_IEC_DWORD dwSpec;				/* VAR_INPUT */	/* a combination of eClass and eSource */
	CAA_ENUM CB_DecodeClass;			/* VAR_OUTPUT */	/* eClass */
} cb_decodeclass_struct;

DEF_API(`void',`CDECL',`cb_decodeclass',`(cb_decodeclass_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x1418632C),0x03050528)

/**
 * <description>cb_decodeevent</description>
 */
typedef struct tagcb_decodeevent_struct
{
	RTS_IEC_DWORD dwSpec;				/* VAR_INPUT */	/* a combination of eEvent and eClass */
	CAA_ENUM CB_DecodeEvent;			/* VAR_OUTPUT */	/* eEvent */
} cb_decodeevent_struct;

DEF_API(`void',`CDECL',`cb_decodeevent',`(cb_decodeevent_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x2E4F9B09),0x03050528)

/**
 * <description>cb_encodespec</description>
 */
typedef struct tagcb_encodespec_struct
{
	CAA_ENUM eEvent;					/* VAR_INPUT */	
	CAA_ENUM eClass;					/* VAR_INPUT */	
	RTS_IEC_DWORD CB_EncodeSpec;		/* VAR_OUTPUT */	
} cb_encodespec_struct;

DEF_API(`void',`CDECL',`cb_encodespec',`(cb_encodespec_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB9DD619F),0x03050528)

/**
 * <description>cb_getcallback</description>
 */
typedef struct tagcb_getcallback_struct
{
	CAA_HANDLE hHandle;					/* VAR_INPUT */	/* handle of Callback */
	CB_CALLBACK *pCallback;				/* VAR_INPUT */	/* Adress of return value */
	CAA_ERROR CB_GetCallback;			/* VAR_OUTPUT */	/* eError */
} cb_getcallback_struct;

DEF_API(`void',`CDECL',`cb_getcallback',`(cb_getcallback_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x905F5B36),0x03050528)

/**
 * <description>cb_gethandleofcallback</description>
 */
typedef struct tagcb_gethandleofcallback_struct
{
	CAA_COUNT ctNumber;					/* VAR_INPUT */	/* number of Callback 1 <= ctNumber <= CB.GetNumberOfCallbacks */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE CB_GetHandleOfCallback;	/* VAR_OUTPUT */	/* hCallback */
} cb_gethandleofcallback_struct;

DEF_API(`void',`CDECL',`cb_gethandleofcallback',`(cb_gethandleofcallback_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD679EC87),0x03050528)

/**
 * <description>cb_getnumberactivecallbacks</description>
 */
typedef struct tagcb_getnumberactivecallbacks_struct
{
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_COUNT CB_GetNumberActiveCallbacks;	/* VAR_OUTPUT */	/* ctNumCallbacks */
} cb_getnumberactivecallbacks_struct;

DEF_API(`void',`CDECL',`cb_getnumberactivecallbacks',`(cb_getnumberactivecallbacks_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC7BD39E8),0x03050528)

/**
 * <description>cb_ishandlevalid</description>
 */
typedef struct tagcb_ishandlevalid_struct
{
	CAA_HANDLE hHandle;					/* VAR_INPUT */	/* handle of Callback */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_BOOL CB_IsHandleValid;			/* VAR_OUTPUT */	/* xValid */
} cb_ishandlevalid_struct;

DEF_API(`void',`CDECL',`cb_ishandlevalid',`(cb_ishandlevalid_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA7565AFF),0x03050528)

/**
 * <description>cb_postevent</description>
 */
typedef struct tagcb_postevent_struct
{
	CAA_ENUM eEvent;					/* VAR_INPUT */	/* event number */
	CAA_ENUM eSource;					/* VAR_INPUT */	/* event source */
	RTS_IEC_XWORD dwParam;				/* VAR_INPUT */	/* parameter for called function */
	CAA_ERROR CB_PostEvent;				/* VAR_OUTPUT */	/* eError */
} cb_postevent_struct;

DEF_API(`void',`CDECL',`cb_postevent',`(cb_postevent_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x7FD337BC),0x03050528)

/**
 * <description>cb_registercallback</description>
 */
typedef struct tagcb_registercallback_struct
{
	CB_CALLBACK cbNew;					/* VAR_INPUT */	/* callback description */
	CAA_ERROR *peError;					/* VAR_INPUT */	/* the function with index iPOUIndex is called due to event e of class c from source s, if 
 (eEvent = CB.ALL_EVENTS OR eEvent = e) AND 
 ((eClass = CB.ALL_CLASSES) OR (eClass AND c) > 0) AND 
 (eSource = CB.ALL_SOURCES OR eSource = s) */
	CAA_HANDLE CB_RegisterCallback;		/* VAR_OUTPUT */	/* hCallback */
} cb_registercallback_struct;

DEF_API(`void',`CDECL',`cb_registercallback',`(cb_registercallback_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x613062C9),0x03050528)

/**
 * <description>cb_sendevent</description>
 */
typedef struct tagcb_sendevent_struct
{
	CAA_ENUM eEvent;					/* VAR_INPUT */	/* event number */
	CAA_ENUM eSource;					/* VAR_INPUT */	/* event source */
	RTS_IEC_XWORD dwParam;				/* VAR_INPUT */	/* parameter for called function */
	CAA_ERROR CB_SendEvent;				/* VAR_OUTPUT */	/* eError */
} cb_sendevent_struct;

DEF_API(`void',`CDECL',`cb_sendevent',`(cb_sendevent_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xFFACA896),0x03050528)

/**
 * <description>cb_unregistercallback</description>
 */
typedef struct tagcb_unregistercallback_struct
{
	CAA_HANDLE hHandle;					/* VAR_INPUT */	/* handle of Callback */
	CAA_ERROR CB_UnregisterCallback;	/* VAR_OUTPUT */	/* eError */
} cb_unregistercallback_struct;

DEF_API(`void',`CDECL',`cb_unregistercallback',`(cb_unregistercallback_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x3065CDC4),0x03050528)

/**
 * <description>cb_getsupplierversion</description>
 */
typedef struct tagcb_getsupplierversion_struct
{
	RTS_IEC_WORD CB_GetSupplierVersion;	/* VAR_OUTPUT */	
} cb_getsupplierversion_struct;

DEF_API(`void',`CDECL',`cb_getsupplierversion',`(cb_getsupplierversion_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xFF6AD528),0x03050528)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>CB_SendEvent</description>
 * <param name="eEvent" type="IN"></param>
 * <param name="eSource" type="IN"></param>
 * <param name="dwParam" type="IN"></param>
 * <param name="SendEvent" type="OUT"></param>
 * <result>Error code</result>
 */
DEF_ITF_API(`CAA_ERROR',`CDECL',`CB_SendEvent',`(CAA_ENUM eEvent, CAA_ENUM eSource, RTS_IEC_XWORD dwParam)')

/**
 * <description>CB_PostEvent</description>
 * <param name="hEvent" type="IN"></param>
 * <param name="dwParam" type="IN"></param>
 * <result>Error code</result>
 */
DEF_ITF_API(`CAA_ERROR',`CDECL',`CB_PostEvent',`(CAA_ENUM eEvent, CAA_ENUM eSource, RTS_IEC_XWORD dwParam)')

/**
 * <description>CB_RegisterCallback</description>
 * <param name="cbNew" type="IN"></param>
 * <param name="RegisterCallback" type="OUT"></param>
 * <result>CAA_HANDLE</result>
 */
DEF_ITF_API(`CAA_HANDLE',`CDECL',`CB_RegisterCallback',`(CB_CALLBACK cbNew, CAA_ERROR* peError)')

/**
 * <description>CB_UnregisterCallback</description>
 * <param name="hHandle" type="IN"></param>
 * <param name="hCallback" type="IN"></param>
 * <result>Error code</result>
 */
DEF_ITF_API(`CAA_ERROR',`CDECL',`CB_UnregisterCallback',`(CAA_HANDLE hCallback)')

/**
 * <description>CB_CallFunctionByIndex</description>
 * <param name="pPOUFunc" type="IN"></param>
 * <param name="dwParam1" type="IN"></param>
 * <param name="dwParam2" type="IN"></param>
 * <param name="dwParam3" type="IN"></param>
 * <param name="peError" type="IN">Error value</param>
 * <param name="CallFunctionByIndex" type="OUT"></param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_IEC_XWORD',`CDECL',`CB_CallFunctionByIndex',`(CAA_PVOID pCallback, RTS_IEC_XWORD dwParam1, RTS_IEC_XWORD dwParam2, RTS_IEC_XWORD dwParam3, CAA_ERROR* peError)')

/**
 * <description>CB_EncodeSpec</description>
 * <param name="eEvent" type="IN"></param>
 * <param name="eClass" type="IN"></param>
 * <param name="EncodeSpec" type="OUT"></param>
 * <result>RTS_IEC_DWORD</result>
 */
DEF_ITF_API(`RTS_IEC_DWORD',`CDECL',`CB_EncodeSpec',`(CAA_ENUM eEvent, CAA_ENUM eClass)')

/**
 * <description>CB_DecodeEvent</description>
 * <param name="dwSpec" type="IN"></param>
 * <param name="DecodeEvent" type="OUT"></param>
 * <result>CAA_ENUM</result>
 */
DEF_ITF_API(`CAA_ENUM',`CDECL',`CB_DecodeEvent',`(RTS_IEC_DWORD dwSpec)')

/**
 * <description>CB_DecodeClass</description>
 * <param name="" type="IN"></param>
 * <param name="" type="OUT"></param>
 * <result>Error code</result>
 */
DEF_ITF_API(`CAA_ENUM',`CDECL',`CB_DecodeClass',`(RTS_IEC_DWORD dwSpec)')

/**
 * <description>CB_IsHandleValid</description>
 * <param name="hHandle" type="IN"></param>
 * <param name="IsHandleValid" type="OUT"></param>
 * <result>CAA_BOOL</result>
 */
DEF_ITF_API(`RTS_IEC_BOOL',`CDECL',`CB_IsHandleValid',`(CAA_HANDLE hHandle, CAA_ERROR* peError)')

/**
 * <description>CB_GetHandleOfCallback</description>
 * <param name="ctNumber" type="IN"></param>
 * <param name="GetHandleOfCallback" type="OUT"></param>
 * <result>CAA_HANDLE</result>
 */
DEF_ITF_API(`CAA_HANDLE',`CDECL',`CB_GetHandleOfCallback',`(CAA_COUNT ctNumber, CAA_ERROR* peError)')

/**
 * <description>CB_GetNumberActiveCallbacks</description>
 * <param name="" type="IN"></param>
 * <param name="GetNumberActiveCallbacks" type="OUT"></param>
 * <result>Error code</result>
 */
DEF_ITF_API(`CAA_COUNT',`CDECL',`CB_GetNumberActiveCallbacks',`(CAA_ERROR* peError)')

/**
 * <description>CB_GetCallback</description>
 * <param name="hHandle" type="IN"></param>
 * <param name="pCallback" type="IN"></param>
 * <param name="GetCallback" type="OUT"></param>
 * <result>Error code</result>
 */
DEF_ITF_API(`CAA_ERROR',`CDECL',`CB_GetCallback',`(CAA_HANDLE hHandle, CB_CALLBACK* pCallback)')

/**
 * <description>CB_GetSupplierVersion</description>
 * <param name="xDummy" type="IN"></param>
 * <param name="GetSupplierVersion" type="OUT"></param>
 * <result>RTS_IEC_WORD</result>
 */
DEF_ITF_API(`RTS_IEC_WORD',`CDECL',`CB_GetSupplierVersion',`(CAA_BOOL xDummy)')

#ifdef __cplusplus
}
#endif
