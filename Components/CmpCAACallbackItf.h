 /**
 * <interfacename>CmpCAACallback</interfacename>
 * <description> 
 *	<p></p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPCAACALLBACKITF_H_
#define _CMPCAACALLBACKITF_H_

#include "CmpStd.h"

 

 




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
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

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

void CDECL CDECL_EXT cb_callfunctionbyindex(cb_callfunctionbyindex_struct *p);
typedef void (CDECL CDECL_EXT* PFCB_CALLFUNCTIONBYINDEX_IEC) (cb_callfunctionbyindex_struct *p);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_CALLFUNCTIONBYINDEX_NOTIMPLEMENTED)
	#define USE_cb_callfunctionbyindex
	#define EXT_cb_callfunctionbyindex
	#define GET_cb_callfunctionbyindex(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cb_callfunctionbyindex(p0) 
	#define CHK_cb_callfunctionbyindex  FALSE
	#define EXP_cb_callfunctionbyindex  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cb_callfunctionbyindex
	#define EXT_cb_callfunctionbyindex
	#define GET_cb_callfunctionbyindex(fl)  CAL_CMGETAPI( "cb_callfunctionbyindex" ) 
	#define CAL_cb_callfunctionbyindex  cb_callfunctionbyindex
	#define CHK_cb_callfunctionbyindex  TRUE
	#define EXP_cb_callfunctionbyindex  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_callfunctionbyindex", (RTS_UINTPTR)cb_callfunctionbyindex, 1, RTSITF_GET_SIGNATURE(0, 0x1530A820), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_cb_callfunctionbyindex
	#define EXT_cb_callfunctionbyindex
	#define GET_cb_callfunctionbyindex(fl)  CAL_CMGETAPI( "cb_callfunctionbyindex" ) 
	#define CAL_cb_callfunctionbyindex  cb_callfunctionbyindex
	#define CHK_cb_callfunctionbyindex  TRUE
	#define EXP_cb_callfunctionbyindex  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_callfunctionbyindex", (RTS_UINTPTR)cb_callfunctionbyindex, 1, RTSITF_GET_SIGNATURE(0, 0x1530A820), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackcb_callfunctionbyindex
	#define EXT_CmpCAACallbackcb_callfunctionbyindex
	#define GET_CmpCAACallbackcb_callfunctionbyindex  ERR_OK
	#define CAL_CmpCAACallbackcb_callfunctionbyindex  cb_callfunctionbyindex
	#define CHK_CmpCAACallbackcb_callfunctionbyindex  TRUE
	#define EXP_CmpCAACallbackcb_callfunctionbyindex  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_callfunctionbyindex", (RTS_UINTPTR)cb_callfunctionbyindex, 1, RTSITF_GET_SIGNATURE(0, 0x1530A820), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_cb_callfunctionbyindex
	#define EXT_cb_callfunctionbyindex
	#define GET_cb_callfunctionbyindex(fl)  CAL_CMGETAPI( "cb_callfunctionbyindex" ) 
	#define CAL_cb_callfunctionbyindex  cb_callfunctionbyindex
	#define CHK_cb_callfunctionbyindex  TRUE
	#define EXP_cb_callfunctionbyindex  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_callfunctionbyindex", (RTS_UINTPTR)cb_callfunctionbyindex, 1, RTSITF_GET_SIGNATURE(0, 0x1530A820), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_cb_callfunctionbyindex  PFCB_CALLFUNCTIONBYINDEX_IEC pfcb_callfunctionbyindex;
	#define EXT_cb_callfunctionbyindex  extern PFCB_CALLFUNCTIONBYINDEX_IEC pfcb_callfunctionbyindex;
	#define GET_cb_callfunctionbyindex(fl)  s_pfCMGetAPI2( "cb_callfunctionbyindex", (RTS_VOID_FCTPTR *)&pfcb_callfunctionbyindex, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x1530A820), 0x03050528)
	#define CAL_cb_callfunctionbyindex  pfcb_callfunctionbyindex
	#define CHK_cb_callfunctionbyindex  (pfcb_callfunctionbyindex != NULL)
	#define EXP_cb_callfunctionbyindex   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_callfunctionbyindex", (RTS_UINTPTR)cb_callfunctionbyindex, 1, RTSITF_GET_SIGNATURE(0, 0x1530A820), 0x03050528) 
#endif


/**
 * <description>cb_decodeclass</description>
 */
typedef struct tagcb_decodeclass_struct
{
	RTS_IEC_DWORD dwSpec;				/* VAR_INPUT */	/* a combination of eClass and eSource */
	CAA_ENUM CB_DecodeClass;			/* VAR_OUTPUT */	/* eClass */
} cb_decodeclass_struct;

void CDECL CDECL_EXT cb_decodeclass(cb_decodeclass_struct *p);
typedef void (CDECL CDECL_EXT* PFCB_DECODECLASS_IEC) (cb_decodeclass_struct *p);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_DECODECLASS_NOTIMPLEMENTED)
	#define USE_cb_decodeclass
	#define EXT_cb_decodeclass
	#define GET_cb_decodeclass(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cb_decodeclass(p0) 
	#define CHK_cb_decodeclass  FALSE
	#define EXP_cb_decodeclass  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cb_decodeclass
	#define EXT_cb_decodeclass
	#define GET_cb_decodeclass(fl)  CAL_CMGETAPI( "cb_decodeclass" ) 
	#define CAL_cb_decodeclass  cb_decodeclass
	#define CHK_cb_decodeclass  TRUE
	#define EXP_cb_decodeclass  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_decodeclass", (RTS_UINTPTR)cb_decodeclass, 1, RTSITF_GET_SIGNATURE(0, 0x1418632C), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_cb_decodeclass
	#define EXT_cb_decodeclass
	#define GET_cb_decodeclass(fl)  CAL_CMGETAPI( "cb_decodeclass" ) 
	#define CAL_cb_decodeclass  cb_decodeclass
	#define CHK_cb_decodeclass  TRUE
	#define EXP_cb_decodeclass  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_decodeclass", (RTS_UINTPTR)cb_decodeclass, 1, RTSITF_GET_SIGNATURE(0, 0x1418632C), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackcb_decodeclass
	#define EXT_CmpCAACallbackcb_decodeclass
	#define GET_CmpCAACallbackcb_decodeclass  ERR_OK
	#define CAL_CmpCAACallbackcb_decodeclass  cb_decodeclass
	#define CHK_CmpCAACallbackcb_decodeclass  TRUE
	#define EXP_CmpCAACallbackcb_decodeclass  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_decodeclass", (RTS_UINTPTR)cb_decodeclass, 1, RTSITF_GET_SIGNATURE(0, 0x1418632C), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_cb_decodeclass
	#define EXT_cb_decodeclass
	#define GET_cb_decodeclass(fl)  CAL_CMGETAPI( "cb_decodeclass" ) 
	#define CAL_cb_decodeclass  cb_decodeclass
	#define CHK_cb_decodeclass  TRUE
	#define EXP_cb_decodeclass  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_decodeclass", (RTS_UINTPTR)cb_decodeclass, 1, RTSITF_GET_SIGNATURE(0, 0x1418632C), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_cb_decodeclass  PFCB_DECODECLASS_IEC pfcb_decodeclass;
	#define EXT_cb_decodeclass  extern PFCB_DECODECLASS_IEC pfcb_decodeclass;
	#define GET_cb_decodeclass(fl)  s_pfCMGetAPI2( "cb_decodeclass", (RTS_VOID_FCTPTR *)&pfcb_decodeclass, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x1418632C), 0x03050528)
	#define CAL_cb_decodeclass  pfcb_decodeclass
	#define CHK_cb_decodeclass  (pfcb_decodeclass != NULL)
	#define EXP_cb_decodeclass   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_decodeclass", (RTS_UINTPTR)cb_decodeclass, 1, RTSITF_GET_SIGNATURE(0, 0x1418632C), 0x03050528) 
#endif


/**
 * <description>cb_decodeevent</description>
 */
typedef struct tagcb_decodeevent_struct
{
	RTS_IEC_DWORD dwSpec;				/* VAR_INPUT */	/* a combination of eEvent and eClass */
	CAA_ENUM CB_DecodeEvent;			/* VAR_OUTPUT */	/* eEvent */
} cb_decodeevent_struct;

void CDECL CDECL_EXT cb_decodeevent(cb_decodeevent_struct *p);
typedef void (CDECL CDECL_EXT* PFCB_DECODEEVENT_IEC) (cb_decodeevent_struct *p);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_DECODEEVENT_NOTIMPLEMENTED)
	#define USE_cb_decodeevent
	#define EXT_cb_decodeevent
	#define GET_cb_decodeevent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cb_decodeevent(p0) 
	#define CHK_cb_decodeevent  FALSE
	#define EXP_cb_decodeevent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cb_decodeevent
	#define EXT_cb_decodeevent
	#define GET_cb_decodeevent(fl)  CAL_CMGETAPI( "cb_decodeevent" ) 
	#define CAL_cb_decodeevent  cb_decodeevent
	#define CHK_cb_decodeevent  TRUE
	#define EXP_cb_decodeevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_decodeevent", (RTS_UINTPTR)cb_decodeevent, 1, RTSITF_GET_SIGNATURE(0, 0x2E4F9B09), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_cb_decodeevent
	#define EXT_cb_decodeevent
	#define GET_cb_decodeevent(fl)  CAL_CMGETAPI( "cb_decodeevent" ) 
	#define CAL_cb_decodeevent  cb_decodeevent
	#define CHK_cb_decodeevent  TRUE
	#define EXP_cb_decodeevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_decodeevent", (RTS_UINTPTR)cb_decodeevent, 1, RTSITF_GET_SIGNATURE(0, 0x2E4F9B09), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackcb_decodeevent
	#define EXT_CmpCAACallbackcb_decodeevent
	#define GET_CmpCAACallbackcb_decodeevent  ERR_OK
	#define CAL_CmpCAACallbackcb_decodeevent  cb_decodeevent
	#define CHK_CmpCAACallbackcb_decodeevent  TRUE
	#define EXP_CmpCAACallbackcb_decodeevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_decodeevent", (RTS_UINTPTR)cb_decodeevent, 1, RTSITF_GET_SIGNATURE(0, 0x2E4F9B09), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_cb_decodeevent
	#define EXT_cb_decodeevent
	#define GET_cb_decodeevent(fl)  CAL_CMGETAPI( "cb_decodeevent" ) 
	#define CAL_cb_decodeevent  cb_decodeevent
	#define CHK_cb_decodeevent  TRUE
	#define EXP_cb_decodeevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_decodeevent", (RTS_UINTPTR)cb_decodeevent, 1, RTSITF_GET_SIGNATURE(0, 0x2E4F9B09), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_cb_decodeevent  PFCB_DECODEEVENT_IEC pfcb_decodeevent;
	#define EXT_cb_decodeevent  extern PFCB_DECODEEVENT_IEC pfcb_decodeevent;
	#define GET_cb_decodeevent(fl)  s_pfCMGetAPI2( "cb_decodeevent", (RTS_VOID_FCTPTR *)&pfcb_decodeevent, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x2E4F9B09), 0x03050528)
	#define CAL_cb_decodeevent  pfcb_decodeevent
	#define CHK_cb_decodeevent  (pfcb_decodeevent != NULL)
	#define EXP_cb_decodeevent   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_decodeevent", (RTS_UINTPTR)cb_decodeevent, 1, RTSITF_GET_SIGNATURE(0, 0x2E4F9B09), 0x03050528) 
#endif


/**
 * <description>cb_encodespec</description>
 */
typedef struct tagcb_encodespec_struct
{
	CAA_ENUM eEvent;					/* VAR_INPUT */	
	CAA_ENUM eClass;					/* VAR_INPUT */	
	RTS_IEC_DWORD CB_EncodeSpec;		/* VAR_OUTPUT */	
} cb_encodespec_struct;

void CDECL CDECL_EXT cb_encodespec(cb_encodespec_struct *p);
typedef void (CDECL CDECL_EXT* PFCB_ENCODESPEC_IEC) (cb_encodespec_struct *p);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_ENCODESPEC_NOTIMPLEMENTED)
	#define USE_cb_encodespec
	#define EXT_cb_encodespec
	#define GET_cb_encodespec(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cb_encodespec(p0) 
	#define CHK_cb_encodespec  FALSE
	#define EXP_cb_encodespec  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cb_encodespec
	#define EXT_cb_encodespec
	#define GET_cb_encodespec(fl)  CAL_CMGETAPI( "cb_encodespec" ) 
	#define CAL_cb_encodespec  cb_encodespec
	#define CHK_cb_encodespec  TRUE
	#define EXP_cb_encodespec  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_encodespec", (RTS_UINTPTR)cb_encodespec, 1, RTSITF_GET_SIGNATURE(0, 0xB9DD619F), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_cb_encodespec
	#define EXT_cb_encodespec
	#define GET_cb_encodespec(fl)  CAL_CMGETAPI( "cb_encodespec" ) 
	#define CAL_cb_encodespec  cb_encodespec
	#define CHK_cb_encodespec  TRUE
	#define EXP_cb_encodespec  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_encodespec", (RTS_UINTPTR)cb_encodespec, 1, RTSITF_GET_SIGNATURE(0, 0xB9DD619F), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackcb_encodespec
	#define EXT_CmpCAACallbackcb_encodespec
	#define GET_CmpCAACallbackcb_encodespec  ERR_OK
	#define CAL_CmpCAACallbackcb_encodespec  cb_encodespec
	#define CHK_CmpCAACallbackcb_encodespec  TRUE
	#define EXP_CmpCAACallbackcb_encodespec  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_encodespec", (RTS_UINTPTR)cb_encodespec, 1, RTSITF_GET_SIGNATURE(0, 0xB9DD619F), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_cb_encodespec
	#define EXT_cb_encodespec
	#define GET_cb_encodespec(fl)  CAL_CMGETAPI( "cb_encodespec" ) 
	#define CAL_cb_encodespec  cb_encodespec
	#define CHK_cb_encodespec  TRUE
	#define EXP_cb_encodespec  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_encodespec", (RTS_UINTPTR)cb_encodespec, 1, RTSITF_GET_SIGNATURE(0, 0xB9DD619F), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_cb_encodespec  PFCB_ENCODESPEC_IEC pfcb_encodespec;
	#define EXT_cb_encodespec  extern PFCB_ENCODESPEC_IEC pfcb_encodespec;
	#define GET_cb_encodespec(fl)  s_pfCMGetAPI2( "cb_encodespec", (RTS_VOID_FCTPTR *)&pfcb_encodespec, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xB9DD619F), 0x03050528)
	#define CAL_cb_encodespec  pfcb_encodespec
	#define CHK_cb_encodespec  (pfcb_encodespec != NULL)
	#define EXP_cb_encodespec   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_encodespec", (RTS_UINTPTR)cb_encodespec, 1, RTSITF_GET_SIGNATURE(0, 0xB9DD619F), 0x03050528) 
#endif


/**
 * <description>cb_getcallback</description>
 */
typedef struct tagcb_getcallback_struct
{
	CAA_HANDLE hHandle;					/* VAR_INPUT */	/* handle of Callback */
	CB_CALLBACK *pCallback;				/* VAR_INPUT */	/* Adress of return value */
	CAA_ERROR CB_GetCallback;			/* VAR_OUTPUT */	/* eError */
} cb_getcallback_struct;

void CDECL CDECL_EXT cb_getcallback(cb_getcallback_struct *p);
typedef void (CDECL CDECL_EXT* PFCB_GETCALLBACK_IEC) (cb_getcallback_struct *p);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_GETCALLBACK_NOTIMPLEMENTED)
	#define USE_cb_getcallback
	#define EXT_cb_getcallback
	#define GET_cb_getcallback(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cb_getcallback(p0) 
	#define CHK_cb_getcallback  FALSE
	#define EXP_cb_getcallback  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cb_getcallback
	#define EXT_cb_getcallback
	#define GET_cb_getcallback(fl)  CAL_CMGETAPI( "cb_getcallback" ) 
	#define CAL_cb_getcallback  cb_getcallback
	#define CHK_cb_getcallback  TRUE
	#define EXP_cb_getcallback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_getcallback", (RTS_UINTPTR)cb_getcallback, 1, RTSITF_GET_SIGNATURE(0, 0x905F5B36), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_cb_getcallback
	#define EXT_cb_getcallback
	#define GET_cb_getcallback(fl)  CAL_CMGETAPI( "cb_getcallback" ) 
	#define CAL_cb_getcallback  cb_getcallback
	#define CHK_cb_getcallback  TRUE
	#define EXP_cb_getcallback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_getcallback", (RTS_UINTPTR)cb_getcallback, 1, RTSITF_GET_SIGNATURE(0, 0x905F5B36), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackcb_getcallback
	#define EXT_CmpCAACallbackcb_getcallback
	#define GET_CmpCAACallbackcb_getcallback  ERR_OK
	#define CAL_CmpCAACallbackcb_getcallback  cb_getcallback
	#define CHK_CmpCAACallbackcb_getcallback  TRUE
	#define EXP_CmpCAACallbackcb_getcallback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_getcallback", (RTS_UINTPTR)cb_getcallback, 1, RTSITF_GET_SIGNATURE(0, 0x905F5B36), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_cb_getcallback
	#define EXT_cb_getcallback
	#define GET_cb_getcallback(fl)  CAL_CMGETAPI( "cb_getcallback" ) 
	#define CAL_cb_getcallback  cb_getcallback
	#define CHK_cb_getcallback  TRUE
	#define EXP_cb_getcallback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_getcallback", (RTS_UINTPTR)cb_getcallback, 1, RTSITF_GET_SIGNATURE(0, 0x905F5B36), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_cb_getcallback  PFCB_GETCALLBACK_IEC pfcb_getcallback;
	#define EXT_cb_getcallback  extern PFCB_GETCALLBACK_IEC pfcb_getcallback;
	#define GET_cb_getcallback(fl)  s_pfCMGetAPI2( "cb_getcallback", (RTS_VOID_FCTPTR *)&pfcb_getcallback, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x905F5B36), 0x03050528)
	#define CAL_cb_getcallback  pfcb_getcallback
	#define CHK_cb_getcallback  (pfcb_getcallback != NULL)
	#define EXP_cb_getcallback   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_getcallback", (RTS_UINTPTR)cb_getcallback, 1, RTSITF_GET_SIGNATURE(0, 0x905F5B36), 0x03050528) 
#endif


/**
 * <description>cb_gethandleofcallback</description>
 */
typedef struct tagcb_gethandleofcallback_struct
{
	CAA_COUNT ctNumber;					/* VAR_INPUT */	/* number of Callback 1 <= ctNumber <= CB.GetNumberOfCallbacks */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE CB_GetHandleOfCallback;	/* VAR_OUTPUT */	/* hCallback */
} cb_gethandleofcallback_struct;

void CDECL CDECL_EXT cb_gethandleofcallback(cb_gethandleofcallback_struct *p);
typedef void (CDECL CDECL_EXT* PFCB_GETHANDLEOFCALLBACK_IEC) (cb_gethandleofcallback_struct *p);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_GETHANDLEOFCALLBACK_NOTIMPLEMENTED)
	#define USE_cb_gethandleofcallback
	#define EXT_cb_gethandleofcallback
	#define GET_cb_gethandleofcallback(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cb_gethandleofcallback(p0) 
	#define CHK_cb_gethandleofcallback  FALSE
	#define EXP_cb_gethandleofcallback  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cb_gethandleofcallback
	#define EXT_cb_gethandleofcallback
	#define GET_cb_gethandleofcallback(fl)  CAL_CMGETAPI( "cb_gethandleofcallback" ) 
	#define CAL_cb_gethandleofcallback  cb_gethandleofcallback
	#define CHK_cb_gethandleofcallback  TRUE
	#define EXP_cb_gethandleofcallback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_gethandleofcallback", (RTS_UINTPTR)cb_gethandleofcallback, 1, RTSITF_GET_SIGNATURE(0, 0xD679EC87), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_cb_gethandleofcallback
	#define EXT_cb_gethandleofcallback
	#define GET_cb_gethandleofcallback(fl)  CAL_CMGETAPI( "cb_gethandleofcallback" ) 
	#define CAL_cb_gethandleofcallback  cb_gethandleofcallback
	#define CHK_cb_gethandleofcallback  TRUE
	#define EXP_cb_gethandleofcallback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_gethandleofcallback", (RTS_UINTPTR)cb_gethandleofcallback, 1, RTSITF_GET_SIGNATURE(0, 0xD679EC87), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackcb_gethandleofcallback
	#define EXT_CmpCAACallbackcb_gethandleofcallback
	#define GET_CmpCAACallbackcb_gethandleofcallback  ERR_OK
	#define CAL_CmpCAACallbackcb_gethandleofcallback  cb_gethandleofcallback
	#define CHK_CmpCAACallbackcb_gethandleofcallback  TRUE
	#define EXP_CmpCAACallbackcb_gethandleofcallback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_gethandleofcallback", (RTS_UINTPTR)cb_gethandleofcallback, 1, RTSITF_GET_SIGNATURE(0, 0xD679EC87), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_cb_gethandleofcallback
	#define EXT_cb_gethandleofcallback
	#define GET_cb_gethandleofcallback(fl)  CAL_CMGETAPI( "cb_gethandleofcallback" ) 
	#define CAL_cb_gethandleofcallback  cb_gethandleofcallback
	#define CHK_cb_gethandleofcallback  TRUE
	#define EXP_cb_gethandleofcallback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_gethandleofcallback", (RTS_UINTPTR)cb_gethandleofcallback, 1, RTSITF_GET_SIGNATURE(0, 0xD679EC87), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_cb_gethandleofcallback  PFCB_GETHANDLEOFCALLBACK_IEC pfcb_gethandleofcallback;
	#define EXT_cb_gethandleofcallback  extern PFCB_GETHANDLEOFCALLBACK_IEC pfcb_gethandleofcallback;
	#define GET_cb_gethandleofcallback(fl)  s_pfCMGetAPI2( "cb_gethandleofcallback", (RTS_VOID_FCTPTR *)&pfcb_gethandleofcallback, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xD679EC87), 0x03050528)
	#define CAL_cb_gethandleofcallback  pfcb_gethandleofcallback
	#define CHK_cb_gethandleofcallback  (pfcb_gethandleofcallback != NULL)
	#define EXP_cb_gethandleofcallback   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_gethandleofcallback", (RTS_UINTPTR)cb_gethandleofcallback, 1, RTSITF_GET_SIGNATURE(0, 0xD679EC87), 0x03050528) 
#endif


/**
 * <description>cb_getnumberactivecallbacks</description>
 */
typedef struct tagcb_getnumberactivecallbacks_struct
{
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_COUNT CB_GetNumberActiveCallbacks;	/* VAR_OUTPUT */	/* ctNumCallbacks */
} cb_getnumberactivecallbacks_struct;

void CDECL CDECL_EXT cb_getnumberactivecallbacks(cb_getnumberactivecallbacks_struct *p);
typedef void (CDECL CDECL_EXT* PFCB_GETNUMBERACTIVECALLBACKS_IEC) (cb_getnumberactivecallbacks_struct *p);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_GETNUMBERACTIVECALLBACKS_NOTIMPLEMENTED)
	#define USE_cb_getnumberactivecallbacks
	#define EXT_cb_getnumberactivecallbacks
	#define GET_cb_getnumberactivecallbacks(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cb_getnumberactivecallbacks(p0) 
	#define CHK_cb_getnumberactivecallbacks  FALSE
	#define EXP_cb_getnumberactivecallbacks  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cb_getnumberactivecallbacks
	#define EXT_cb_getnumberactivecallbacks
	#define GET_cb_getnumberactivecallbacks(fl)  CAL_CMGETAPI( "cb_getnumberactivecallbacks" ) 
	#define CAL_cb_getnumberactivecallbacks  cb_getnumberactivecallbacks
	#define CHK_cb_getnumberactivecallbacks  TRUE
	#define EXP_cb_getnumberactivecallbacks  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_getnumberactivecallbacks", (RTS_UINTPTR)cb_getnumberactivecallbacks, 1, RTSITF_GET_SIGNATURE(0, 0xC7BD39E8), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_cb_getnumberactivecallbacks
	#define EXT_cb_getnumberactivecallbacks
	#define GET_cb_getnumberactivecallbacks(fl)  CAL_CMGETAPI( "cb_getnumberactivecallbacks" ) 
	#define CAL_cb_getnumberactivecallbacks  cb_getnumberactivecallbacks
	#define CHK_cb_getnumberactivecallbacks  TRUE
	#define EXP_cb_getnumberactivecallbacks  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_getnumberactivecallbacks", (RTS_UINTPTR)cb_getnumberactivecallbacks, 1, RTSITF_GET_SIGNATURE(0, 0xC7BD39E8), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackcb_getnumberactivecallbacks
	#define EXT_CmpCAACallbackcb_getnumberactivecallbacks
	#define GET_CmpCAACallbackcb_getnumberactivecallbacks  ERR_OK
	#define CAL_CmpCAACallbackcb_getnumberactivecallbacks  cb_getnumberactivecallbacks
	#define CHK_CmpCAACallbackcb_getnumberactivecallbacks  TRUE
	#define EXP_CmpCAACallbackcb_getnumberactivecallbacks  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_getnumberactivecallbacks", (RTS_UINTPTR)cb_getnumberactivecallbacks, 1, RTSITF_GET_SIGNATURE(0, 0xC7BD39E8), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_cb_getnumberactivecallbacks
	#define EXT_cb_getnumberactivecallbacks
	#define GET_cb_getnumberactivecallbacks(fl)  CAL_CMGETAPI( "cb_getnumberactivecallbacks" ) 
	#define CAL_cb_getnumberactivecallbacks  cb_getnumberactivecallbacks
	#define CHK_cb_getnumberactivecallbacks  TRUE
	#define EXP_cb_getnumberactivecallbacks  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_getnumberactivecallbacks", (RTS_UINTPTR)cb_getnumberactivecallbacks, 1, RTSITF_GET_SIGNATURE(0, 0xC7BD39E8), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_cb_getnumberactivecallbacks  PFCB_GETNUMBERACTIVECALLBACKS_IEC pfcb_getnumberactivecallbacks;
	#define EXT_cb_getnumberactivecallbacks  extern PFCB_GETNUMBERACTIVECALLBACKS_IEC pfcb_getnumberactivecallbacks;
	#define GET_cb_getnumberactivecallbacks(fl)  s_pfCMGetAPI2( "cb_getnumberactivecallbacks", (RTS_VOID_FCTPTR *)&pfcb_getnumberactivecallbacks, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xC7BD39E8), 0x03050528)
	#define CAL_cb_getnumberactivecallbacks  pfcb_getnumberactivecallbacks
	#define CHK_cb_getnumberactivecallbacks  (pfcb_getnumberactivecallbacks != NULL)
	#define EXP_cb_getnumberactivecallbacks   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_getnumberactivecallbacks", (RTS_UINTPTR)cb_getnumberactivecallbacks, 1, RTSITF_GET_SIGNATURE(0, 0xC7BD39E8), 0x03050528) 
#endif


/**
 * <description>cb_ishandlevalid</description>
 */
typedef struct tagcb_ishandlevalid_struct
{
	CAA_HANDLE hHandle;					/* VAR_INPUT */	/* handle of Callback */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_BOOL CB_IsHandleValid;			/* VAR_OUTPUT */	/* xValid */
} cb_ishandlevalid_struct;

void CDECL CDECL_EXT cb_ishandlevalid(cb_ishandlevalid_struct *p);
typedef void (CDECL CDECL_EXT* PFCB_ISHANDLEVALID_IEC) (cb_ishandlevalid_struct *p);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_ISHANDLEVALID_NOTIMPLEMENTED)
	#define USE_cb_ishandlevalid
	#define EXT_cb_ishandlevalid
	#define GET_cb_ishandlevalid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cb_ishandlevalid(p0) 
	#define CHK_cb_ishandlevalid  FALSE
	#define EXP_cb_ishandlevalid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cb_ishandlevalid
	#define EXT_cb_ishandlevalid
	#define GET_cb_ishandlevalid(fl)  CAL_CMGETAPI( "cb_ishandlevalid" ) 
	#define CAL_cb_ishandlevalid  cb_ishandlevalid
	#define CHK_cb_ishandlevalid  TRUE
	#define EXP_cb_ishandlevalid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_ishandlevalid", (RTS_UINTPTR)cb_ishandlevalid, 1, RTSITF_GET_SIGNATURE(0, 0xA7565AFF), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_cb_ishandlevalid
	#define EXT_cb_ishandlevalid
	#define GET_cb_ishandlevalid(fl)  CAL_CMGETAPI( "cb_ishandlevalid" ) 
	#define CAL_cb_ishandlevalid  cb_ishandlevalid
	#define CHK_cb_ishandlevalid  TRUE
	#define EXP_cb_ishandlevalid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_ishandlevalid", (RTS_UINTPTR)cb_ishandlevalid, 1, RTSITF_GET_SIGNATURE(0, 0xA7565AFF), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackcb_ishandlevalid
	#define EXT_CmpCAACallbackcb_ishandlevalid
	#define GET_CmpCAACallbackcb_ishandlevalid  ERR_OK
	#define CAL_CmpCAACallbackcb_ishandlevalid  cb_ishandlevalid
	#define CHK_CmpCAACallbackcb_ishandlevalid  TRUE
	#define EXP_CmpCAACallbackcb_ishandlevalid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_ishandlevalid", (RTS_UINTPTR)cb_ishandlevalid, 1, RTSITF_GET_SIGNATURE(0, 0xA7565AFF), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_cb_ishandlevalid
	#define EXT_cb_ishandlevalid
	#define GET_cb_ishandlevalid(fl)  CAL_CMGETAPI( "cb_ishandlevalid" ) 
	#define CAL_cb_ishandlevalid  cb_ishandlevalid
	#define CHK_cb_ishandlevalid  TRUE
	#define EXP_cb_ishandlevalid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_ishandlevalid", (RTS_UINTPTR)cb_ishandlevalid, 1, RTSITF_GET_SIGNATURE(0, 0xA7565AFF), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_cb_ishandlevalid  PFCB_ISHANDLEVALID_IEC pfcb_ishandlevalid;
	#define EXT_cb_ishandlevalid  extern PFCB_ISHANDLEVALID_IEC pfcb_ishandlevalid;
	#define GET_cb_ishandlevalid(fl)  s_pfCMGetAPI2( "cb_ishandlevalid", (RTS_VOID_FCTPTR *)&pfcb_ishandlevalid, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xA7565AFF), 0x03050528)
	#define CAL_cb_ishandlevalid  pfcb_ishandlevalid
	#define CHK_cb_ishandlevalid  (pfcb_ishandlevalid != NULL)
	#define EXP_cb_ishandlevalid   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_ishandlevalid", (RTS_UINTPTR)cb_ishandlevalid, 1, RTSITF_GET_SIGNATURE(0, 0xA7565AFF), 0x03050528) 
#endif


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

void CDECL CDECL_EXT cb_postevent(cb_postevent_struct *p);
typedef void (CDECL CDECL_EXT* PFCB_POSTEVENT_IEC) (cb_postevent_struct *p);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_POSTEVENT_NOTIMPLEMENTED)
	#define USE_cb_postevent
	#define EXT_cb_postevent
	#define GET_cb_postevent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cb_postevent(p0) 
	#define CHK_cb_postevent  FALSE
	#define EXP_cb_postevent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cb_postevent
	#define EXT_cb_postevent
	#define GET_cb_postevent(fl)  CAL_CMGETAPI( "cb_postevent" ) 
	#define CAL_cb_postevent  cb_postevent
	#define CHK_cb_postevent  TRUE
	#define EXP_cb_postevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_postevent", (RTS_UINTPTR)cb_postevent, 1, RTSITF_GET_SIGNATURE(0, 0x7FD337BC), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_cb_postevent
	#define EXT_cb_postevent
	#define GET_cb_postevent(fl)  CAL_CMGETAPI( "cb_postevent" ) 
	#define CAL_cb_postevent  cb_postevent
	#define CHK_cb_postevent  TRUE
	#define EXP_cb_postevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_postevent", (RTS_UINTPTR)cb_postevent, 1, RTSITF_GET_SIGNATURE(0, 0x7FD337BC), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackcb_postevent
	#define EXT_CmpCAACallbackcb_postevent
	#define GET_CmpCAACallbackcb_postevent  ERR_OK
	#define CAL_CmpCAACallbackcb_postevent  cb_postevent
	#define CHK_CmpCAACallbackcb_postevent  TRUE
	#define EXP_CmpCAACallbackcb_postevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_postevent", (RTS_UINTPTR)cb_postevent, 1, RTSITF_GET_SIGNATURE(0, 0x7FD337BC), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_cb_postevent
	#define EXT_cb_postevent
	#define GET_cb_postevent(fl)  CAL_CMGETAPI( "cb_postevent" ) 
	#define CAL_cb_postevent  cb_postevent
	#define CHK_cb_postevent  TRUE
	#define EXP_cb_postevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_postevent", (RTS_UINTPTR)cb_postevent, 1, RTSITF_GET_SIGNATURE(0, 0x7FD337BC), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_cb_postevent  PFCB_POSTEVENT_IEC pfcb_postevent;
	#define EXT_cb_postevent  extern PFCB_POSTEVENT_IEC pfcb_postevent;
	#define GET_cb_postevent(fl)  s_pfCMGetAPI2( "cb_postevent", (RTS_VOID_FCTPTR *)&pfcb_postevent, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x7FD337BC), 0x03050528)
	#define CAL_cb_postevent  pfcb_postevent
	#define CHK_cb_postevent  (pfcb_postevent != NULL)
	#define EXP_cb_postevent   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_postevent", (RTS_UINTPTR)cb_postevent, 1, RTSITF_GET_SIGNATURE(0, 0x7FD337BC), 0x03050528) 
#endif


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

void CDECL CDECL_EXT cb_registercallback(cb_registercallback_struct *p);
typedef void (CDECL CDECL_EXT* PFCB_REGISTERCALLBACK_IEC) (cb_registercallback_struct *p);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_REGISTERCALLBACK_NOTIMPLEMENTED)
	#define USE_cb_registercallback
	#define EXT_cb_registercallback
	#define GET_cb_registercallback(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cb_registercallback(p0) 
	#define CHK_cb_registercallback  FALSE
	#define EXP_cb_registercallback  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cb_registercallback
	#define EXT_cb_registercallback
	#define GET_cb_registercallback(fl)  CAL_CMGETAPI( "cb_registercallback" ) 
	#define CAL_cb_registercallback  cb_registercallback
	#define CHK_cb_registercallback  TRUE
	#define EXP_cb_registercallback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_registercallback", (RTS_UINTPTR)cb_registercallback, 1, RTSITF_GET_SIGNATURE(0, 0x613062C9), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_cb_registercallback
	#define EXT_cb_registercallback
	#define GET_cb_registercallback(fl)  CAL_CMGETAPI( "cb_registercallback" ) 
	#define CAL_cb_registercallback  cb_registercallback
	#define CHK_cb_registercallback  TRUE
	#define EXP_cb_registercallback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_registercallback", (RTS_UINTPTR)cb_registercallback, 1, RTSITF_GET_SIGNATURE(0, 0x613062C9), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackcb_registercallback
	#define EXT_CmpCAACallbackcb_registercallback
	#define GET_CmpCAACallbackcb_registercallback  ERR_OK
	#define CAL_CmpCAACallbackcb_registercallback  cb_registercallback
	#define CHK_CmpCAACallbackcb_registercallback  TRUE
	#define EXP_CmpCAACallbackcb_registercallback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_registercallback", (RTS_UINTPTR)cb_registercallback, 1, RTSITF_GET_SIGNATURE(0, 0x613062C9), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_cb_registercallback
	#define EXT_cb_registercallback
	#define GET_cb_registercallback(fl)  CAL_CMGETAPI( "cb_registercallback" ) 
	#define CAL_cb_registercallback  cb_registercallback
	#define CHK_cb_registercallback  TRUE
	#define EXP_cb_registercallback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_registercallback", (RTS_UINTPTR)cb_registercallback, 1, RTSITF_GET_SIGNATURE(0, 0x613062C9), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_cb_registercallback  PFCB_REGISTERCALLBACK_IEC pfcb_registercallback;
	#define EXT_cb_registercallback  extern PFCB_REGISTERCALLBACK_IEC pfcb_registercallback;
	#define GET_cb_registercallback(fl)  s_pfCMGetAPI2( "cb_registercallback", (RTS_VOID_FCTPTR *)&pfcb_registercallback, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x613062C9), 0x03050528)
	#define CAL_cb_registercallback  pfcb_registercallback
	#define CHK_cb_registercallback  (pfcb_registercallback != NULL)
	#define EXP_cb_registercallback   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_registercallback", (RTS_UINTPTR)cb_registercallback, 1, RTSITF_GET_SIGNATURE(0, 0x613062C9), 0x03050528) 
#endif


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

void CDECL CDECL_EXT cb_sendevent(cb_sendevent_struct *p);
typedef void (CDECL CDECL_EXT* PFCB_SENDEVENT_IEC) (cb_sendevent_struct *p);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_SENDEVENT_NOTIMPLEMENTED)
	#define USE_cb_sendevent
	#define EXT_cb_sendevent
	#define GET_cb_sendevent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cb_sendevent(p0) 
	#define CHK_cb_sendevent  FALSE
	#define EXP_cb_sendevent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cb_sendevent
	#define EXT_cb_sendevent
	#define GET_cb_sendevent(fl)  CAL_CMGETAPI( "cb_sendevent" ) 
	#define CAL_cb_sendevent  cb_sendevent
	#define CHK_cb_sendevent  TRUE
	#define EXP_cb_sendevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_sendevent", (RTS_UINTPTR)cb_sendevent, 1, RTSITF_GET_SIGNATURE(0, 0xFFACA896), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_cb_sendevent
	#define EXT_cb_sendevent
	#define GET_cb_sendevent(fl)  CAL_CMGETAPI( "cb_sendevent" ) 
	#define CAL_cb_sendevent  cb_sendevent
	#define CHK_cb_sendevent  TRUE
	#define EXP_cb_sendevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_sendevent", (RTS_UINTPTR)cb_sendevent, 1, RTSITF_GET_SIGNATURE(0, 0xFFACA896), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackcb_sendevent
	#define EXT_CmpCAACallbackcb_sendevent
	#define GET_CmpCAACallbackcb_sendevent  ERR_OK
	#define CAL_CmpCAACallbackcb_sendevent  cb_sendevent
	#define CHK_CmpCAACallbackcb_sendevent  TRUE
	#define EXP_CmpCAACallbackcb_sendevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_sendevent", (RTS_UINTPTR)cb_sendevent, 1, RTSITF_GET_SIGNATURE(0, 0xFFACA896), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_cb_sendevent
	#define EXT_cb_sendevent
	#define GET_cb_sendevent(fl)  CAL_CMGETAPI( "cb_sendevent" ) 
	#define CAL_cb_sendevent  cb_sendevent
	#define CHK_cb_sendevent  TRUE
	#define EXP_cb_sendevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_sendevent", (RTS_UINTPTR)cb_sendevent, 1, RTSITF_GET_SIGNATURE(0, 0xFFACA896), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_cb_sendevent  PFCB_SENDEVENT_IEC pfcb_sendevent;
	#define EXT_cb_sendevent  extern PFCB_SENDEVENT_IEC pfcb_sendevent;
	#define GET_cb_sendevent(fl)  s_pfCMGetAPI2( "cb_sendevent", (RTS_VOID_FCTPTR *)&pfcb_sendevent, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xFFACA896), 0x03050528)
	#define CAL_cb_sendevent  pfcb_sendevent
	#define CHK_cb_sendevent  (pfcb_sendevent != NULL)
	#define EXP_cb_sendevent   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_sendevent", (RTS_UINTPTR)cb_sendevent, 1, RTSITF_GET_SIGNATURE(0, 0xFFACA896), 0x03050528) 
#endif


/**
 * <description>cb_unregistercallback</description>
 */
typedef struct tagcb_unregistercallback_struct
{
	CAA_HANDLE hHandle;					/* VAR_INPUT */	/* handle of Callback */
	CAA_ERROR CB_UnregisterCallback;	/* VAR_OUTPUT */	/* eError */
} cb_unregistercallback_struct;

void CDECL CDECL_EXT cb_unregistercallback(cb_unregistercallback_struct *p);
typedef void (CDECL CDECL_EXT* PFCB_UNREGISTERCALLBACK_IEC) (cb_unregistercallback_struct *p);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_UNREGISTERCALLBACK_NOTIMPLEMENTED)
	#define USE_cb_unregistercallback
	#define EXT_cb_unregistercallback
	#define GET_cb_unregistercallback(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cb_unregistercallback(p0) 
	#define CHK_cb_unregistercallback  FALSE
	#define EXP_cb_unregistercallback  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cb_unregistercallback
	#define EXT_cb_unregistercallback
	#define GET_cb_unregistercallback(fl)  CAL_CMGETAPI( "cb_unregistercallback" ) 
	#define CAL_cb_unregistercallback  cb_unregistercallback
	#define CHK_cb_unregistercallback  TRUE
	#define EXP_cb_unregistercallback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_unregistercallback", (RTS_UINTPTR)cb_unregistercallback, 1, RTSITF_GET_SIGNATURE(0, 0x3065CDC4), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_cb_unregistercallback
	#define EXT_cb_unregistercallback
	#define GET_cb_unregistercallback(fl)  CAL_CMGETAPI( "cb_unregistercallback" ) 
	#define CAL_cb_unregistercallback  cb_unregistercallback
	#define CHK_cb_unregistercallback  TRUE
	#define EXP_cb_unregistercallback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_unregistercallback", (RTS_UINTPTR)cb_unregistercallback, 1, RTSITF_GET_SIGNATURE(0, 0x3065CDC4), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackcb_unregistercallback
	#define EXT_CmpCAACallbackcb_unregistercallback
	#define GET_CmpCAACallbackcb_unregistercallback  ERR_OK
	#define CAL_CmpCAACallbackcb_unregistercallback  cb_unregistercallback
	#define CHK_CmpCAACallbackcb_unregistercallback  TRUE
	#define EXP_CmpCAACallbackcb_unregistercallback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_unregistercallback", (RTS_UINTPTR)cb_unregistercallback, 1, RTSITF_GET_SIGNATURE(0, 0x3065CDC4), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_cb_unregistercallback
	#define EXT_cb_unregistercallback
	#define GET_cb_unregistercallback(fl)  CAL_CMGETAPI( "cb_unregistercallback" ) 
	#define CAL_cb_unregistercallback  cb_unregistercallback
	#define CHK_cb_unregistercallback  TRUE
	#define EXP_cb_unregistercallback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_unregistercallback", (RTS_UINTPTR)cb_unregistercallback, 1, RTSITF_GET_SIGNATURE(0, 0x3065CDC4), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_cb_unregistercallback  PFCB_UNREGISTERCALLBACK_IEC pfcb_unregistercallback;
	#define EXT_cb_unregistercallback  extern PFCB_UNREGISTERCALLBACK_IEC pfcb_unregistercallback;
	#define GET_cb_unregistercallback(fl)  s_pfCMGetAPI2( "cb_unregistercallback", (RTS_VOID_FCTPTR *)&pfcb_unregistercallback, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x3065CDC4), 0x03050528)
	#define CAL_cb_unregistercallback  pfcb_unregistercallback
	#define CHK_cb_unregistercallback  (pfcb_unregistercallback != NULL)
	#define EXP_cb_unregistercallback   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_unregistercallback", (RTS_UINTPTR)cb_unregistercallback, 1, RTSITF_GET_SIGNATURE(0, 0x3065CDC4), 0x03050528) 
#endif


/**
 * <description>cb_getsupplierversion</description>
 */
typedef struct tagcb_getsupplierversion_struct
{
	RTS_IEC_WORD CB_GetSupplierVersion;	/* VAR_OUTPUT */	
} cb_getsupplierversion_struct;

void CDECL CDECL_EXT cb_getsupplierversion(cb_getsupplierversion_struct *p);
typedef void (CDECL CDECL_EXT* PFCB_GETSUPPLIERVERSION_IEC) (cb_getsupplierversion_struct *p);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_GETSUPPLIERVERSION_NOTIMPLEMENTED)
	#define USE_cb_getsupplierversion
	#define EXT_cb_getsupplierversion
	#define GET_cb_getsupplierversion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cb_getsupplierversion(p0) 
	#define CHK_cb_getsupplierversion  FALSE
	#define EXP_cb_getsupplierversion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cb_getsupplierversion
	#define EXT_cb_getsupplierversion
	#define GET_cb_getsupplierversion(fl)  CAL_CMGETAPI( "cb_getsupplierversion" ) 
	#define CAL_cb_getsupplierversion  cb_getsupplierversion
	#define CHK_cb_getsupplierversion  TRUE
	#define EXP_cb_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_getsupplierversion", (RTS_UINTPTR)cb_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xFF6AD528), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_cb_getsupplierversion
	#define EXT_cb_getsupplierversion
	#define GET_cb_getsupplierversion(fl)  CAL_CMGETAPI( "cb_getsupplierversion" ) 
	#define CAL_cb_getsupplierversion  cb_getsupplierversion
	#define CHK_cb_getsupplierversion  TRUE
	#define EXP_cb_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_getsupplierversion", (RTS_UINTPTR)cb_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xFF6AD528), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackcb_getsupplierversion
	#define EXT_CmpCAACallbackcb_getsupplierversion
	#define GET_CmpCAACallbackcb_getsupplierversion  ERR_OK
	#define CAL_CmpCAACallbackcb_getsupplierversion  cb_getsupplierversion
	#define CHK_CmpCAACallbackcb_getsupplierversion  TRUE
	#define EXP_CmpCAACallbackcb_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_getsupplierversion", (RTS_UINTPTR)cb_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xFF6AD528), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_cb_getsupplierversion
	#define EXT_cb_getsupplierversion
	#define GET_cb_getsupplierversion(fl)  CAL_CMGETAPI( "cb_getsupplierversion" ) 
	#define CAL_cb_getsupplierversion  cb_getsupplierversion
	#define CHK_cb_getsupplierversion  TRUE
	#define EXP_cb_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_getsupplierversion", (RTS_UINTPTR)cb_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xFF6AD528), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_cb_getsupplierversion  PFCB_GETSUPPLIERVERSION_IEC pfcb_getsupplierversion;
	#define EXT_cb_getsupplierversion  extern PFCB_GETSUPPLIERVERSION_IEC pfcb_getsupplierversion;
	#define GET_cb_getsupplierversion(fl)  s_pfCMGetAPI2( "cb_getsupplierversion", (RTS_VOID_FCTPTR *)&pfcb_getsupplierversion, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xFF6AD528), 0x03050528)
	#define CAL_cb_getsupplierversion  pfcb_getsupplierversion
	#define CHK_cb_getsupplierversion  (pfcb_getsupplierversion != NULL)
	#define EXP_cb_getsupplierversion   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cb_getsupplierversion", (RTS_UINTPTR)cb_getsupplierversion, 1, RTSITF_GET_SIGNATURE(0, 0xFF6AD528), 0x03050528) 
#endif


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
CAA_ERROR CDECL CB_SendEvent(CAA_ENUM eEvent, CAA_ENUM eSource, RTS_IEC_XWORD dwParam);
typedef CAA_ERROR (CDECL * PFCB_SENDEVENT) (CAA_ENUM eEvent, CAA_ENUM eSource, RTS_IEC_XWORD dwParam);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_SENDEVENT_NOTIMPLEMENTED)
	#define USE_CB_SendEvent
	#define EXT_CB_SendEvent
	#define GET_CB_SendEvent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CB_SendEvent(p0,p1,p2)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CB_SendEvent  FALSE
	#define EXP_CB_SendEvent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CB_SendEvent
	#define EXT_CB_SendEvent
	#define GET_CB_SendEvent(fl)  CAL_CMGETAPI( "CB_SendEvent" ) 
	#define CAL_CB_SendEvent  CB_SendEvent
	#define CHK_CB_SendEvent  TRUE
	#define EXP_CB_SendEvent  CAL_CMEXPAPI( "CB_SendEvent" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_CB_SendEvent
	#define EXT_CB_SendEvent
	#define GET_CB_SendEvent(fl)  CAL_CMGETAPI( "CB_SendEvent" ) 
	#define CAL_CB_SendEvent  CB_SendEvent
	#define CHK_CB_SendEvent  TRUE
	#define EXP_CB_SendEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_SendEvent", (RTS_UINTPTR)CB_SendEvent, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackCB_SendEvent
	#define EXT_CmpCAACallbackCB_SendEvent
	#define GET_CmpCAACallbackCB_SendEvent  ERR_OK
	#define CAL_CmpCAACallbackCB_SendEvent pICmpCAACallback->ICB_SendEvent
	#define CHK_CmpCAACallbackCB_SendEvent (pICmpCAACallback != NULL)
	#define EXP_CmpCAACallbackCB_SendEvent  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CB_SendEvent
	#define EXT_CB_SendEvent
	#define GET_CB_SendEvent(fl)  CAL_CMGETAPI( "CB_SendEvent" ) 
	#define CAL_CB_SendEvent pICmpCAACallback->ICB_SendEvent
	#define CHK_CB_SendEvent (pICmpCAACallback != NULL)
	#define EXP_CB_SendEvent  CAL_CMEXPAPI( "CB_SendEvent" ) 
#else /* DYNAMIC_LINK */
	#define USE_CB_SendEvent  PFCB_SENDEVENT pfCB_SendEvent;
	#define EXT_CB_SendEvent  extern PFCB_SENDEVENT pfCB_SendEvent;
	#define GET_CB_SendEvent(fl)  s_pfCMGetAPI2( "CB_SendEvent", (RTS_VOID_FCTPTR *)&pfCB_SendEvent, (fl), 0, 0)
	#define CAL_CB_SendEvent  pfCB_SendEvent
	#define CHK_CB_SendEvent  (pfCB_SendEvent != NULL)
	#define EXP_CB_SendEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_SendEvent", (RTS_UINTPTR)CB_SendEvent, 0, 0) 
#endif




/**
 * <description>CB_PostEvent</description>
 * <param name="hEvent" type="IN"></param>
 * <param name="dwParam" type="IN"></param>
 * <result>Error code</result>
 */
CAA_ERROR CDECL CB_PostEvent(CAA_ENUM eEvent, CAA_ENUM eSource, RTS_IEC_XWORD dwParam);
typedef CAA_ERROR (CDECL * PFCB_POSTEVENT) (CAA_ENUM eEvent, CAA_ENUM eSource, RTS_IEC_XWORD dwParam);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_POSTEVENT_NOTIMPLEMENTED)
	#define USE_CB_PostEvent
	#define EXT_CB_PostEvent
	#define GET_CB_PostEvent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CB_PostEvent(p0,p1,p2)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CB_PostEvent  FALSE
	#define EXP_CB_PostEvent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CB_PostEvent
	#define EXT_CB_PostEvent
	#define GET_CB_PostEvent(fl)  CAL_CMGETAPI( "CB_PostEvent" ) 
	#define CAL_CB_PostEvent  CB_PostEvent
	#define CHK_CB_PostEvent  TRUE
	#define EXP_CB_PostEvent  CAL_CMEXPAPI( "CB_PostEvent" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_CB_PostEvent
	#define EXT_CB_PostEvent
	#define GET_CB_PostEvent(fl)  CAL_CMGETAPI( "CB_PostEvent" ) 
	#define CAL_CB_PostEvent  CB_PostEvent
	#define CHK_CB_PostEvent  TRUE
	#define EXP_CB_PostEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_PostEvent", (RTS_UINTPTR)CB_PostEvent, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackCB_PostEvent
	#define EXT_CmpCAACallbackCB_PostEvent
	#define GET_CmpCAACallbackCB_PostEvent  ERR_OK
	#define CAL_CmpCAACallbackCB_PostEvent pICmpCAACallback->ICB_PostEvent
	#define CHK_CmpCAACallbackCB_PostEvent (pICmpCAACallback != NULL)
	#define EXP_CmpCAACallbackCB_PostEvent  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CB_PostEvent
	#define EXT_CB_PostEvent
	#define GET_CB_PostEvent(fl)  CAL_CMGETAPI( "CB_PostEvent" ) 
	#define CAL_CB_PostEvent pICmpCAACallback->ICB_PostEvent
	#define CHK_CB_PostEvent (pICmpCAACallback != NULL)
	#define EXP_CB_PostEvent  CAL_CMEXPAPI( "CB_PostEvent" ) 
#else /* DYNAMIC_LINK */
	#define USE_CB_PostEvent  PFCB_POSTEVENT pfCB_PostEvent;
	#define EXT_CB_PostEvent  extern PFCB_POSTEVENT pfCB_PostEvent;
	#define GET_CB_PostEvent(fl)  s_pfCMGetAPI2( "CB_PostEvent", (RTS_VOID_FCTPTR *)&pfCB_PostEvent, (fl), 0, 0)
	#define CAL_CB_PostEvent  pfCB_PostEvent
	#define CHK_CB_PostEvent  (pfCB_PostEvent != NULL)
	#define EXP_CB_PostEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_PostEvent", (RTS_UINTPTR)CB_PostEvent, 0, 0) 
#endif




/**
 * <description>CB_RegisterCallback</description>
 * <param name="cbNew" type="IN"></param>
 * <param name="RegisterCallback" type="OUT"></param>
 * <result>CAA_HANDLE</result>
 */
CAA_HANDLE CDECL CB_RegisterCallback(CB_CALLBACK cbNew, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFCB_REGISTERCALLBACK) (CB_CALLBACK cbNew, CAA_ERROR* peError);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_REGISTERCALLBACK_NOTIMPLEMENTED)
	#define USE_CB_RegisterCallback
	#define EXT_CB_RegisterCallback
	#define GET_CB_RegisterCallback(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CB_RegisterCallback(p0,p1)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_CB_RegisterCallback  FALSE
	#define EXP_CB_RegisterCallback  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CB_RegisterCallback
	#define EXT_CB_RegisterCallback
	#define GET_CB_RegisterCallback(fl)  CAL_CMGETAPI( "CB_RegisterCallback" ) 
	#define CAL_CB_RegisterCallback  CB_RegisterCallback
	#define CHK_CB_RegisterCallback  TRUE
	#define EXP_CB_RegisterCallback  CAL_CMEXPAPI( "CB_RegisterCallback" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_CB_RegisterCallback
	#define EXT_CB_RegisterCallback
	#define GET_CB_RegisterCallback(fl)  CAL_CMGETAPI( "CB_RegisterCallback" ) 
	#define CAL_CB_RegisterCallback  CB_RegisterCallback
	#define CHK_CB_RegisterCallback  TRUE
	#define EXP_CB_RegisterCallback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_RegisterCallback", (RTS_UINTPTR)CB_RegisterCallback, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackCB_RegisterCallback
	#define EXT_CmpCAACallbackCB_RegisterCallback
	#define GET_CmpCAACallbackCB_RegisterCallback  ERR_OK
	#define CAL_CmpCAACallbackCB_RegisterCallback pICmpCAACallback->ICB_RegisterCallback
	#define CHK_CmpCAACallbackCB_RegisterCallback (pICmpCAACallback != NULL)
	#define EXP_CmpCAACallbackCB_RegisterCallback  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CB_RegisterCallback
	#define EXT_CB_RegisterCallback
	#define GET_CB_RegisterCallback(fl)  CAL_CMGETAPI( "CB_RegisterCallback" ) 
	#define CAL_CB_RegisterCallback pICmpCAACallback->ICB_RegisterCallback
	#define CHK_CB_RegisterCallback (pICmpCAACallback != NULL)
	#define EXP_CB_RegisterCallback  CAL_CMEXPAPI( "CB_RegisterCallback" ) 
#else /* DYNAMIC_LINK */
	#define USE_CB_RegisterCallback  PFCB_REGISTERCALLBACK pfCB_RegisterCallback;
	#define EXT_CB_RegisterCallback  extern PFCB_REGISTERCALLBACK pfCB_RegisterCallback;
	#define GET_CB_RegisterCallback(fl)  s_pfCMGetAPI2( "CB_RegisterCallback", (RTS_VOID_FCTPTR *)&pfCB_RegisterCallback, (fl), 0, 0)
	#define CAL_CB_RegisterCallback  pfCB_RegisterCallback
	#define CHK_CB_RegisterCallback  (pfCB_RegisterCallback != NULL)
	#define EXP_CB_RegisterCallback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_RegisterCallback", (RTS_UINTPTR)CB_RegisterCallback, 0, 0) 
#endif




/**
 * <description>CB_UnregisterCallback</description>
 * <param name="hHandle" type="IN"></param>
 * <param name="hCallback" type="IN"></param>
 * <result>Error code</result>
 */
CAA_ERROR CDECL CB_UnregisterCallback(CAA_HANDLE hCallback);
typedef CAA_ERROR (CDECL * PFCB_UNREGISTERCALLBACK) (CAA_HANDLE hCallback);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_UNREGISTERCALLBACK_NOTIMPLEMENTED)
	#define USE_CB_UnregisterCallback
	#define EXT_CB_UnregisterCallback
	#define GET_CB_UnregisterCallback(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CB_UnregisterCallback(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CB_UnregisterCallback  FALSE
	#define EXP_CB_UnregisterCallback  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CB_UnregisterCallback
	#define EXT_CB_UnregisterCallback
	#define GET_CB_UnregisterCallback(fl)  CAL_CMGETAPI( "CB_UnregisterCallback" ) 
	#define CAL_CB_UnregisterCallback  CB_UnregisterCallback
	#define CHK_CB_UnregisterCallback  TRUE
	#define EXP_CB_UnregisterCallback  CAL_CMEXPAPI( "CB_UnregisterCallback" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_CB_UnregisterCallback
	#define EXT_CB_UnregisterCallback
	#define GET_CB_UnregisterCallback(fl)  CAL_CMGETAPI( "CB_UnregisterCallback" ) 
	#define CAL_CB_UnregisterCallback  CB_UnregisterCallback
	#define CHK_CB_UnregisterCallback  TRUE
	#define EXP_CB_UnregisterCallback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_UnregisterCallback", (RTS_UINTPTR)CB_UnregisterCallback, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackCB_UnregisterCallback
	#define EXT_CmpCAACallbackCB_UnregisterCallback
	#define GET_CmpCAACallbackCB_UnregisterCallback  ERR_OK
	#define CAL_CmpCAACallbackCB_UnregisterCallback pICmpCAACallback->ICB_UnregisterCallback
	#define CHK_CmpCAACallbackCB_UnregisterCallback (pICmpCAACallback != NULL)
	#define EXP_CmpCAACallbackCB_UnregisterCallback  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CB_UnregisterCallback
	#define EXT_CB_UnregisterCallback
	#define GET_CB_UnregisterCallback(fl)  CAL_CMGETAPI( "CB_UnregisterCallback" ) 
	#define CAL_CB_UnregisterCallback pICmpCAACallback->ICB_UnregisterCallback
	#define CHK_CB_UnregisterCallback (pICmpCAACallback != NULL)
	#define EXP_CB_UnregisterCallback  CAL_CMEXPAPI( "CB_UnregisterCallback" ) 
#else /* DYNAMIC_LINK */
	#define USE_CB_UnregisterCallback  PFCB_UNREGISTERCALLBACK pfCB_UnregisterCallback;
	#define EXT_CB_UnregisterCallback  extern PFCB_UNREGISTERCALLBACK pfCB_UnregisterCallback;
	#define GET_CB_UnregisterCallback(fl)  s_pfCMGetAPI2( "CB_UnregisterCallback", (RTS_VOID_FCTPTR *)&pfCB_UnregisterCallback, (fl), 0, 0)
	#define CAL_CB_UnregisterCallback  pfCB_UnregisterCallback
	#define CHK_CB_UnregisterCallback  (pfCB_UnregisterCallback != NULL)
	#define EXP_CB_UnregisterCallback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_UnregisterCallback", (RTS_UINTPTR)CB_UnregisterCallback, 0, 0) 
#endif




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
RTS_IEC_XWORD CDECL CB_CallFunctionByIndex(CAA_PVOID pCallback, RTS_IEC_XWORD dwParam1, RTS_IEC_XWORD dwParam2, RTS_IEC_XWORD dwParam3, CAA_ERROR* peError);
typedef RTS_IEC_XWORD (CDECL * PFCB_CALLFUNCTIONBYINDEX) (CAA_PVOID pCallback, RTS_IEC_XWORD dwParam1, RTS_IEC_XWORD dwParam2, RTS_IEC_XWORD dwParam3, CAA_ERROR* peError);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_CALLFUNCTIONBYINDEX_NOTIMPLEMENTED)
	#define USE_CB_CallFunctionByIndex
	#define EXT_CB_CallFunctionByIndex
	#define GET_CB_CallFunctionByIndex(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CB_CallFunctionByIndex(p0,p1,p2,p3,p4)  (RTS_IEC_XWORD)ERR_NOTIMPLEMENTED
	#define CHK_CB_CallFunctionByIndex  FALSE
	#define EXP_CB_CallFunctionByIndex  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CB_CallFunctionByIndex
	#define EXT_CB_CallFunctionByIndex
	#define GET_CB_CallFunctionByIndex(fl)  CAL_CMGETAPI( "CB_CallFunctionByIndex" ) 
	#define CAL_CB_CallFunctionByIndex  CB_CallFunctionByIndex
	#define CHK_CB_CallFunctionByIndex  TRUE
	#define EXP_CB_CallFunctionByIndex  CAL_CMEXPAPI( "CB_CallFunctionByIndex" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_CB_CallFunctionByIndex
	#define EXT_CB_CallFunctionByIndex
	#define GET_CB_CallFunctionByIndex(fl)  CAL_CMGETAPI( "CB_CallFunctionByIndex" ) 
	#define CAL_CB_CallFunctionByIndex  CB_CallFunctionByIndex
	#define CHK_CB_CallFunctionByIndex  TRUE
	#define EXP_CB_CallFunctionByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_CallFunctionByIndex", (RTS_UINTPTR)CB_CallFunctionByIndex, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackCB_CallFunctionByIndex
	#define EXT_CmpCAACallbackCB_CallFunctionByIndex
	#define GET_CmpCAACallbackCB_CallFunctionByIndex  ERR_OK
	#define CAL_CmpCAACallbackCB_CallFunctionByIndex pICmpCAACallback->ICB_CallFunctionByIndex
	#define CHK_CmpCAACallbackCB_CallFunctionByIndex (pICmpCAACallback != NULL)
	#define EXP_CmpCAACallbackCB_CallFunctionByIndex  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CB_CallFunctionByIndex
	#define EXT_CB_CallFunctionByIndex
	#define GET_CB_CallFunctionByIndex(fl)  CAL_CMGETAPI( "CB_CallFunctionByIndex" ) 
	#define CAL_CB_CallFunctionByIndex pICmpCAACallback->ICB_CallFunctionByIndex
	#define CHK_CB_CallFunctionByIndex (pICmpCAACallback != NULL)
	#define EXP_CB_CallFunctionByIndex  CAL_CMEXPAPI( "CB_CallFunctionByIndex" ) 
#else /* DYNAMIC_LINK */
	#define USE_CB_CallFunctionByIndex  PFCB_CALLFUNCTIONBYINDEX pfCB_CallFunctionByIndex;
	#define EXT_CB_CallFunctionByIndex  extern PFCB_CALLFUNCTIONBYINDEX pfCB_CallFunctionByIndex;
	#define GET_CB_CallFunctionByIndex(fl)  s_pfCMGetAPI2( "CB_CallFunctionByIndex", (RTS_VOID_FCTPTR *)&pfCB_CallFunctionByIndex, (fl), 0, 0)
	#define CAL_CB_CallFunctionByIndex  pfCB_CallFunctionByIndex
	#define CHK_CB_CallFunctionByIndex  (pfCB_CallFunctionByIndex != NULL)
	#define EXP_CB_CallFunctionByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_CallFunctionByIndex", (RTS_UINTPTR)CB_CallFunctionByIndex, 0, 0) 
#endif




/**
 * <description>CB_EncodeSpec</description>
 * <param name="eEvent" type="IN"></param>
 * <param name="eClass" type="IN"></param>
 * <param name="EncodeSpec" type="OUT"></param>
 * <result>RTS_IEC_DWORD</result>
 */
RTS_IEC_DWORD CDECL CB_EncodeSpec(CAA_ENUM eEvent, CAA_ENUM eClass);
typedef RTS_IEC_DWORD (CDECL * PFCB_ENCODESPEC) (CAA_ENUM eEvent, CAA_ENUM eClass);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_ENCODESPEC_NOTIMPLEMENTED)
	#define USE_CB_EncodeSpec
	#define EXT_CB_EncodeSpec
	#define GET_CB_EncodeSpec(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CB_EncodeSpec(p0,p1)  (RTS_IEC_DWORD)ERR_NOTIMPLEMENTED
	#define CHK_CB_EncodeSpec  FALSE
	#define EXP_CB_EncodeSpec  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CB_EncodeSpec
	#define EXT_CB_EncodeSpec
	#define GET_CB_EncodeSpec(fl)  CAL_CMGETAPI( "CB_EncodeSpec" ) 
	#define CAL_CB_EncodeSpec  CB_EncodeSpec
	#define CHK_CB_EncodeSpec  TRUE
	#define EXP_CB_EncodeSpec  CAL_CMEXPAPI( "CB_EncodeSpec" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_CB_EncodeSpec
	#define EXT_CB_EncodeSpec
	#define GET_CB_EncodeSpec(fl)  CAL_CMGETAPI( "CB_EncodeSpec" ) 
	#define CAL_CB_EncodeSpec  CB_EncodeSpec
	#define CHK_CB_EncodeSpec  TRUE
	#define EXP_CB_EncodeSpec  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_EncodeSpec", (RTS_UINTPTR)CB_EncodeSpec, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackCB_EncodeSpec
	#define EXT_CmpCAACallbackCB_EncodeSpec
	#define GET_CmpCAACallbackCB_EncodeSpec  ERR_OK
	#define CAL_CmpCAACallbackCB_EncodeSpec pICmpCAACallback->ICB_EncodeSpec
	#define CHK_CmpCAACallbackCB_EncodeSpec (pICmpCAACallback != NULL)
	#define EXP_CmpCAACallbackCB_EncodeSpec  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CB_EncodeSpec
	#define EXT_CB_EncodeSpec
	#define GET_CB_EncodeSpec(fl)  CAL_CMGETAPI( "CB_EncodeSpec" ) 
	#define CAL_CB_EncodeSpec pICmpCAACallback->ICB_EncodeSpec
	#define CHK_CB_EncodeSpec (pICmpCAACallback != NULL)
	#define EXP_CB_EncodeSpec  CAL_CMEXPAPI( "CB_EncodeSpec" ) 
#else /* DYNAMIC_LINK */
	#define USE_CB_EncodeSpec  PFCB_ENCODESPEC pfCB_EncodeSpec;
	#define EXT_CB_EncodeSpec  extern PFCB_ENCODESPEC pfCB_EncodeSpec;
	#define GET_CB_EncodeSpec(fl)  s_pfCMGetAPI2( "CB_EncodeSpec", (RTS_VOID_FCTPTR *)&pfCB_EncodeSpec, (fl), 0, 0)
	#define CAL_CB_EncodeSpec  pfCB_EncodeSpec
	#define CHK_CB_EncodeSpec  (pfCB_EncodeSpec != NULL)
	#define EXP_CB_EncodeSpec  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_EncodeSpec", (RTS_UINTPTR)CB_EncodeSpec, 0, 0) 
#endif




/**
 * <description>CB_DecodeEvent</description>
 * <param name="dwSpec" type="IN"></param>
 * <param name="DecodeEvent" type="OUT"></param>
 * <result>CAA_ENUM</result>
 */
CAA_ENUM CDECL CB_DecodeEvent(RTS_IEC_DWORD dwSpec);
typedef CAA_ENUM (CDECL * PFCB_DECODEEVENT) (RTS_IEC_DWORD dwSpec);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_DECODEEVENT_NOTIMPLEMENTED)
	#define USE_CB_DecodeEvent
	#define EXT_CB_DecodeEvent
	#define GET_CB_DecodeEvent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CB_DecodeEvent(p0)  (CAA_ENUM)ERR_NOTIMPLEMENTED
	#define CHK_CB_DecodeEvent  FALSE
	#define EXP_CB_DecodeEvent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CB_DecodeEvent
	#define EXT_CB_DecodeEvent
	#define GET_CB_DecodeEvent(fl)  CAL_CMGETAPI( "CB_DecodeEvent" ) 
	#define CAL_CB_DecodeEvent  CB_DecodeEvent
	#define CHK_CB_DecodeEvent  TRUE
	#define EXP_CB_DecodeEvent  CAL_CMEXPAPI( "CB_DecodeEvent" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_CB_DecodeEvent
	#define EXT_CB_DecodeEvent
	#define GET_CB_DecodeEvent(fl)  CAL_CMGETAPI( "CB_DecodeEvent" ) 
	#define CAL_CB_DecodeEvent  CB_DecodeEvent
	#define CHK_CB_DecodeEvent  TRUE
	#define EXP_CB_DecodeEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_DecodeEvent", (RTS_UINTPTR)CB_DecodeEvent, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackCB_DecodeEvent
	#define EXT_CmpCAACallbackCB_DecodeEvent
	#define GET_CmpCAACallbackCB_DecodeEvent  ERR_OK
	#define CAL_CmpCAACallbackCB_DecodeEvent pICmpCAACallback->ICB_DecodeEvent
	#define CHK_CmpCAACallbackCB_DecodeEvent (pICmpCAACallback != NULL)
	#define EXP_CmpCAACallbackCB_DecodeEvent  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CB_DecodeEvent
	#define EXT_CB_DecodeEvent
	#define GET_CB_DecodeEvent(fl)  CAL_CMGETAPI( "CB_DecodeEvent" ) 
	#define CAL_CB_DecodeEvent pICmpCAACallback->ICB_DecodeEvent
	#define CHK_CB_DecodeEvent (pICmpCAACallback != NULL)
	#define EXP_CB_DecodeEvent  CAL_CMEXPAPI( "CB_DecodeEvent" ) 
#else /* DYNAMIC_LINK */
	#define USE_CB_DecodeEvent  PFCB_DECODEEVENT pfCB_DecodeEvent;
	#define EXT_CB_DecodeEvent  extern PFCB_DECODEEVENT pfCB_DecodeEvent;
	#define GET_CB_DecodeEvent(fl)  s_pfCMGetAPI2( "CB_DecodeEvent", (RTS_VOID_FCTPTR *)&pfCB_DecodeEvent, (fl), 0, 0)
	#define CAL_CB_DecodeEvent  pfCB_DecodeEvent
	#define CHK_CB_DecodeEvent  (pfCB_DecodeEvent != NULL)
	#define EXP_CB_DecodeEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_DecodeEvent", (RTS_UINTPTR)CB_DecodeEvent, 0, 0) 
#endif




/**
 * <description>CB_DecodeClass</description>
 * <param name="" type="IN"></param>
 * <param name="" type="OUT"></param>
 * <result>Error code</result>
 */
CAA_ENUM CDECL CB_DecodeClass(RTS_IEC_DWORD dwSpec);
typedef CAA_ENUM (CDECL * PFCB_DECODECLASS) (RTS_IEC_DWORD dwSpec);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_DECODECLASS_NOTIMPLEMENTED)
	#define USE_CB_DecodeClass
	#define EXT_CB_DecodeClass
	#define GET_CB_DecodeClass(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CB_DecodeClass(p0)  (CAA_ENUM)ERR_NOTIMPLEMENTED
	#define CHK_CB_DecodeClass  FALSE
	#define EXP_CB_DecodeClass  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CB_DecodeClass
	#define EXT_CB_DecodeClass
	#define GET_CB_DecodeClass(fl)  CAL_CMGETAPI( "CB_DecodeClass" ) 
	#define CAL_CB_DecodeClass  CB_DecodeClass
	#define CHK_CB_DecodeClass  TRUE
	#define EXP_CB_DecodeClass  CAL_CMEXPAPI( "CB_DecodeClass" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_CB_DecodeClass
	#define EXT_CB_DecodeClass
	#define GET_CB_DecodeClass(fl)  CAL_CMGETAPI( "CB_DecodeClass" ) 
	#define CAL_CB_DecodeClass  CB_DecodeClass
	#define CHK_CB_DecodeClass  TRUE
	#define EXP_CB_DecodeClass  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_DecodeClass", (RTS_UINTPTR)CB_DecodeClass, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackCB_DecodeClass
	#define EXT_CmpCAACallbackCB_DecodeClass
	#define GET_CmpCAACallbackCB_DecodeClass  ERR_OK
	#define CAL_CmpCAACallbackCB_DecodeClass pICmpCAACallback->ICB_DecodeClass
	#define CHK_CmpCAACallbackCB_DecodeClass (pICmpCAACallback != NULL)
	#define EXP_CmpCAACallbackCB_DecodeClass  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CB_DecodeClass
	#define EXT_CB_DecodeClass
	#define GET_CB_DecodeClass(fl)  CAL_CMGETAPI( "CB_DecodeClass" ) 
	#define CAL_CB_DecodeClass pICmpCAACallback->ICB_DecodeClass
	#define CHK_CB_DecodeClass (pICmpCAACallback != NULL)
	#define EXP_CB_DecodeClass  CAL_CMEXPAPI( "CB_DecodeClass" ) 
#else /* DYNAMIC_LINK */
	#define USE_CB_DecodeClass  PFCB_DECODECLASS pfCB_DecodeClass;
	#define EXT_CB_DecodeClass  extern PFCB_DECODECLASS pfCB_DecodeClass;
	#define GET_CB_DecodeClass(fl)  s_pfCMGetAPI2( "CB_DecodeClass", (RTS_VOID_FCTPTR *)&pfCB_DecodeClass, (fl), 0, 0)
	#define CAL_CB_DecodeClass  pfCB_DecodeClass
	#define CHK_CB_DecodeClass  (pfCB_DecodeClass != NULL)
	#define EXP_CB_DecodeClass  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_DecodeClass", (RTS_UINTPTR)CB_DecodeClass, 0, 0) 
#endif




/**
 * <description>CB_IsHandleValid</description>
 * <param name="hHandle" type="IN"></param>
 * <param name="IsHandleValid" type="OUT"></param>
 * <result>CAA_BOOL</result>
 */
RTS_IEC_BOOL CDECL CB_IsHandleValid(CAA_HANDLE hHandle, CAA_ERROR* peError);
typedef RTS_IEC_BOOL (CDECL * PFCB_ISHANDLEVALID) (CAA_HANDLE hHandle, CAA_ERROR* peError);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_ISHANDLEVALID_NOTIMPLEMENTED)
	#define USE_CB_IsHandleValid
	#define EXT_CB_IsHandleValid
	#define GET_CB_IsHandleValid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CB_IsHandleValid(p0,p1)  (RTS_IEC_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_CB_IsHandleValid  FALSE
	#define EXP_CB_IsHandleValid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CB_IsHandleValid
	#define EXT_CB_IsHandleValid
	#define GET_CB_IsHandleValid(fl)  CAL_CMGETAPI( "CB_IsHandleValid" ) 
	#define CAL_CB_IsHandleValid  CB_IsHandleValid
	#define CHK_CB_IsHandleValid  TRUE
	#define EXP_CB_IsHandleValid  CAL_CMEXPAPI( "CB_IsHandleValid" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_CB_IsHandleValid
	#define EXT_CB_IsHandleValid
	#define GET_CB_IsHandleValid(fl)  CAL_CMGETAPI( "CB_IsHandleValid" ) 
	#define CAL_CB_IsHandleValid  CB_IsHandleValid
	#define CHK_CB_IsHandleValid  TRUE
	#define EXP_CB_IsHandleValid  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_IsHandleValid", (RTS_UINTPTR)CB_IsHandleValid, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackCB_IsHandleValid
	#define EXT_CmpCAACallbackCB_IsHandleValid
	#define GET_CmpCAACallbackCB_IsHandleValid  ERR_OK
	#define CAL_CmpCAACallbackCB_IsHandleValid pICmpCAACallback->ICB_IsHandleValid
	#define CHK_CmpCAACallbackCB_IsHandleValid (pICmpCAACallback != NULL)
	#define EXP_CmpCAACallbackCB_IsHandleValid  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CB_IsHandleValid
	#define EXT_CB_IsHandleValid
	#define GET_CB_IsHandleValid(fl)  CAL_CMGETAPI( "CB_IsHandleValid" ) 
	#define CAL_CB_IsHandleValid pICmpCAACallback->ICB_IsHandleValid
	#define CHK_CB_IsHandleValid (pICmpCAACallback != NULL)
	#define EXP_CB_IsHandleValid  CAL_CMEXPAPI( "CB_IsHandleValid" ) 
#else /* DYNAMIC_LINK */
	#define USE_CB_IsHandleValid  PFCB_ISHANDLEVALID pfCB_IsHandleValid;
	#define EXT_CB_IsHandleValid  extern PFCB_ISHANDLEVALID pfCB_IsHandleValid;
	#define GET_CB_IsHandleValid(fl)  s_pfCMGetAPI2( "CB_IsHandleValid", (RTS_VOID_FCTPTR *)&pfCB_IsHandleValid, (fl), 0, 0)
	#define CAL_CB_IsHandleValid  pfCB_IsHandleValid
	#define CHK_CB_IsHandleValid  (pfCB_IsHandleValid != NULL)
	#define EXP_CB_IsHandleValid  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_IsHandleValid", (RTS_UINTPTR)CB_IsHandleValid, 0, 0) 
#endif




/**
 * <description>CB_GetHandleOfCallback</description>
 * <param name="ctNumber" type="IN"></param>
 * <param name="GetHandleOfCallback" type="OUT"></param>
 * <result>CAA_HANDLE</result>
 */
CAA_HANDLE CDECL CB_GetHandleOfCallback(CAA_COUNT ctNumber, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFCB_GETHANDLEOFCALLBACK) (CAA_COUNT ctNumber, CAA_ERROR* peError);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_GETHANDLEOFCALLBACK_NOTIMPLEMENTED)
	#define USE_CB_GetHandleOfCallback
	#define EXT_CB_GetHandleOfCallback
	#define GET_CB_GetHandleOfCallback(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CB_GetHandleOfCallback(p0,p1)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_CB_GetHandleOfCallback  FALSE
	#define EXP_CB_GetHandleOfCallback  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CB_GetHandleOfCallback
	#define EXT_CB_GetHandleOfCallback
	#define GET_CB_GetHandleOfCallback(fl)  CAL_CMGETAPI( "CB_GetHandleOfCallback" ) 
	#define CAL_CB_GetHandleOfCallback  CB_GetHandleOfCallback
	#define CHK_CB_GetHandleOfCallback  TRUE
	#define EXP_CB_GetHandleOfCallback  CAL_CMEXPAPI( "CB_GetHandleOfCallback" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_CB_GetHandleOfCallback
	#define EXT_CB_GetHandleOfCallback
	#define GET_CB_GetHandleOfCallback(fl)  CAL_CMGETAPI( "CB_GetHandleOfCallback" ) 
	#define CAL_CB_GetHandleOfCallback  CB_GetHandleOfCallback
	#define CHK_CB_GetHandleOfCallback  TRUE
	#define EXP_CB_GetHandleOfCallback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_GetHandleOfCallback", (RTS_UINTPTR)CB_GetHandleOfCallback, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackCB_GetHandleOfCallback
	#define EXT_CmpCAACallbackCB_GetHandleOfCallback
	#define GET_CmpCAACallbackCB_GetHandleOfCallback  ERR_OK
	#define CAL_CmpCAACallbackCB_GetHandleOfCallback pICmpCAACallback->ICB_GetHandleOfCallback
	#define CHK_CmpCAACallbackCB_GetHandleOfCallback (pICmpCAACallback != NULL)
	#define EXP_CmpCAACallbackCB_GetHandleOfCallback  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CB_GetHandleOfCallback
	#define EXT_CB_GetHandleOfCallback
	#define GET_CB_GetHandleOfCallback(fl)  CAL_CMGETAPI( "CB_GetHandleOfCallback" ) 
	#define CAL_CB_GetHandleOfCallback pICmpCAACallback->ICB_GetHandleOfCallback
	#define CHK_CB_GetHandleOfCallback (pICmpCAACallback != NULL)
	#define EXP_CB_GetHandleOfCallback  CAL_CMEXPAPI( "CB_GetHandleOfCallback" ) 
#else /* DYNAMIC_LINK */
	#define USE_CB_GetHandleOfCallback  PFCB_GETHANDLEOFCALLBACK pfCB_GetHandleOfCallback;
	#define EXT_CB_GetHandleOfCallback  extern PFCB_GETHANDLEOFCALLBACK pfCB_GetHandleOfCallback;
	#define GET_CB_GetHandleOfCallback(fl)  s_pfCMGetAPI2( "CB_GetHandleOfCallback", (RTS_VOID_FCTPTR *)&pfCB_GetHandleOfCallback, (fl), 0, 0)
	#define CAL_CB_GetHandleOfCallback  pfCB_GetHandleOfCallback
	#define CHK_CB_GetHandleOfCallback  (pfCB_GetHandleOfCallback != NULL)
	#define EXP_CB_GetHandleOfCallback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_GetHandleOfCallback", (RTS_UINTPTR)CB_GetHandleOfCallback, 0, 0) 
#endif




/**
 * <description>CB_GetNumberActiveCallbacks</description>
 * <param name="" type="IN"></param>
 * <param name="GetNumberActiveCallbacks" type="OUT"></param>
 * <result>Error code</result>
 */
CAA_COUNT CDECL CB_GetNumberActiveCallbacks(CAA_ERROR* peError);
typedef CAA_COUNT (CDECL * PFCB_GETNUMBERACTIVECALLBACKS) (CAA_ERROR* peError);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_GETNUMBERACTIVECALLBACKS_NOTIMPLEMENTED)
	#define USE_CB_GetNumberActiveCallbacks
	#define EXT_CB_GetNumberActiveCallbacks
	#define GET_CB_GetNumberActiveCallbacks(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CB_GetNumberActiveCallbacks(p0)  (CAA_COUNT)ERR_NOTIMPLEMENTED
	#define CHK_CB_GetNumberActiveCallbacks  FALSE
	#define EXP_CB_GetNumberActiveCallbacks  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CB_GetNumberActiveCallbacks
	#define EXT_CB_GetNumberActiveCallbacks
	#define GET_CB_GetNumberActiveCallbacks(fl)  CAL_CMGETAPI( "CB_GetNumberActiveCallbacks" ) 
	#define CAL_CB_GetNumberActiveCallbacks  CB_GetNumberActiveCallbacks
	#define CHK_CB_GetNumberActiveCallbacks  TRUE
	#define EXP_CB_GetNumberActiveCallbacks  CAL_CMEXPAPI( "CB_GetNumberActiveCallbacks" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_CB_GetNumberActiveCallbacks
	#define EXT_CB_GetNumberActiveCallbacks
	#define GET_CB_GetNumberActiveCallbacks(fl)  CAL_CMGETAPI( "CB_GetNumberActiveCallbacks" ) 
	#define CAL_CB_GetNumberActiveCallbacks  CB_GetNumberActiveCallbacks
	#define CHK_CB_GetNumberActiveCallbacks  TRUE
	#define EXP_CB_GetNumberActiveCallbacks  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_GetNumberActiveCallbacks", (RTS_UINTPTR)CB_GetNumberActiveCallbacks, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackCB_GetNumberActiveCallbacks
	#define EXT_CmpCAACallbackCB_GetNumberActiveCallbacks
	#define GET_CmpCAACallbackCB_GetNumberActiveCallbacks  ERR_OK
	#define CAL_CmpCAACallbackCB_GetNumberActiveCallbacks pICmpCAACallback->ICB_GetNumberActiveCallbacks
	#define CHK_CmpCAACallbackCB_GetNumberActiveCallbacks (pICmpCAACallback != NULL)
	#define EXP_CmpCAACallbackCB_GetNumberActiveCallbacks  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CB_GetNumberActiveCallbacks
	#define EXT_CB_GetNumberActiveCallbacks
	#define GET_CB_GetNumberActiveCallbacks(fl)  CAL_CMGETAPI( "CB_GetNumberActiveCallbacks" ) 
	#define CAL_CB_GetNumberActiveCallbacks pICmpCAACallback->ICB_GetNumberActiveCallbacks
	#define CHK_CB_GetNumberActiveCallbacks (pICmpCAACallback != NULL)
	#define EXP_CB_GetNumberActiveCallbacks  CAL_CMEXPAPI( "CB_GetNumberActiveCallbacks" ) 
#else /* DYNAMIC_LINK */
	#define USE_CB_GetNumberActiveCallbacks  PFCB_GETNUMBERACTIVECALLBACKS pfCB_GetNumberActiveCallbacks;
	#define EXT_CB_GetNumberActiveCallbacks  extern PFCB_GETNUMBERACTIVECALLBACKS pfCB_GetNumberActiveCallbacks;
	#define GET_CB_GetNumberActiveCallbacks(fl)  s_pfCMGetAPI2( "CB_GetNumberActiveCallbacks", (RTS_VOID_FCTPTR *)&pfCB_GetNumberActiveCallbacks, (fl), 0, 0)
	#define CAL_CB_GetNumberActiveCallbacks  pfCB_GetNumberActiveCallbacks
	#define CHK_CB_GetNumberActiveCallbacks  (pfCB_GetNumberActiveCallbacks != NULL)
	#define EXP_CB_GetNumberActiveCallbacks  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_GetNumberActiveCallbacks", (RTS_UINTPTR)CB_GetNumberActiveCallbacks, 0, 0) 
#endif




/**
 * <description>CB_GetCallback</description>
 * <param name="hHandle" type="IN"></param>
 * <param name="pCallback" type="IN"></param>
 * <param name="GetCallback" type="OUT"></param>
 * <result>Error code</result>
 */
CAA_ERROR CDECL CB_GetCallback(CAA_HANDLE hHandle, CB_CALLBACK* pCallback);
typedef CAA_ERROR (CDECL * PFCB_GETCALLBACK) (CAA_HANDLE hHandle, CB_CALLBACK* pCallback);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_GETCALLBACK_NOTIMPLEMENTED)
	#define USE_CB_GetCallback
	#define EXT_CB_GetCallback
	#define GET_CB_GetCallback(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CB_GetCallback(p0,p1)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CB_GetCallback  FALSE
	#define EXP_CB_GetCallback  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CB_GetCallback
	#define EXT_CB_GetCallback
	#define GET_CB_GetCallback(fl)  CAL_CMGETAPI( "CB_GetCallback" ) 
	#define CAL_CB_GetCallback  CB_GetCallback
	#define CHK_CB_GetCallback  TRUE
	#define EXP_CB_GetCallback  CAL_CMEXPAPI( "CB_GetCallback" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_CB_GetCallback
	#define EXT_CB_GetCallback
	#define GET_CB_GetCallback(fl)  CAL_CMGETAPI( "CB_GetCallback" ) 
	#define CAL_CB_GetCallback  CB_GetCallback
	#define CHK_CB_GetCallback  TRUE
	#define EXP_CB_GetCallback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_GetCallback", (RTS_UINTPTR)CB_GetCallback, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackCB_GetCallback
	#define EXT_CmpCAACallbackCB_GetCallback
	#define GET_CmpCAACallbackCB_GetCallback  ERR_OK
	#define CAL_CmpCAACallbackCB_GetCallback pICmpCAACallback->ICB_GetCallback
	#define CHK_CmpCAACallbackCB_GetCallback (pICmpCAACallback != NULL)
	#define EXP_CmpCAACallbackCB_GetCallback  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CB_GetCallback
	#define EXT_CB_GetCallback
	#define GET_CB_GetCallback(fl)  CAL_CMGETAPI( "CB_GetCallback" ) 
	#define CAL_CB_GetCallback pICmpCAACallback->ICB_GetCallback
	#define CHK_CB_GetCallback (pICmpCAACallback != NULL)
	#define EXP_CB_GetCallback  CAL_CMEXPAPI( "CB_GetCallback" ) 
#else /* DYNAMIC_LINK */
	#define USE_CB_GetCallback  PFCB_GETCALLBACK pfCB_GetCallback;
	#define EXT_CB_GetCallback  extern PFCB_GETCALLBACK pfCB_GetCallback;
	#define GET_CB_GetCallback(fl)  s_pfCMGetAPI2( "CB_GetCallback", (RTS_VOID_FCTPTR *)&pfCB_GetCallback, (fl), 0, 0)
	#define CAL_CB_GetCallback  pfCB_GetCallback
	#define CHK_CB_GetCallback  (pfCB_GetCallback != NULL)
	#define EXP_CB_GetCallback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_GetCallback", (RTS_UINTPTR)CB_GetCallback, 0, 0) 
#endif




/**
 * <description>CB_GetSupplierVersion</description>
 * <param name="xDummy" type="IN"></param>
 * <param name="GetSupplierVersion" type="OUT"></param>
 * <result>RTS_IEC_WORD</result>
 */
RTS_IEC_WORD CDECL CB_GetSupplierVersion(CAA_BOOL xDummy);
typedef RTS_IEC_WORD (CDECL * PFCB_GETSUPPLIERVERSION) (CAA_BOOL xDummy);
#if defined(CMPCAACALLBACK_NOTIMPLEMENTED) || defined(CB_GETSUPPLIERVERSION_NOTIMPLEMENTED)
	#define USE_CB_GetSupplierVersion
	#define EXT_CB_GetSupplierVersion
	#define GET_CB_GetSupplierVersion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CB_GetSupplierVersion(p0)  (RTS_IEC_WORD)ERR_NOTIMPLEMENTED
	#define CHK_CB_GetSupplierVersion  FALSE
	#define EXP_CB_GetSupplierVersion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CB_GetSupplierVersion
	#define EXT_CB_GetSupplierVersion
	#define GET_CB_GetSupplierVersion(fl)  CAL_CMGETAPI( "CB_GetSupplierVersion" ) 
	#define CAL_CB_GetSupplierVersion  CB_GetSupplierVersion
	#define CHK_CB_GetSupplierVersion  TRUE
	#define EXP_CB_GetSupplierVersion  CAL_CMEXPAPI( "CB_GetSupplierVersion" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACALLBACK_EXTERNAL)
	#define USE_CB_GetSupplierVersion
	#define EXT_CB_GetSupplierVersion
	#define GET_CB_GetSupplierVersion(fl)  CAL_CMGETAPI( "CB_GetSupplierVersion" ) 
	#define CAL_CB_GetSupplierVersion  CB_GetSupplierVersion
	#define CHK_CB_GetSupplierVersion  TRUE
	#define EXP_CB_GetSupplierVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_GetSupplierVersion", (RTS_UINTPTR)CB_GetSupplierVersion, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACallbackCB_GetSupplierVersion
	#define EXT_CmpCAACallbackCB_GetSupplierVersion
	#define GET_CmpCAACallbackCB_GetSupplierVersion  ERR_OK
	#define CAL_CmpCAACallbackCB_GetSupplierVersion pICmpCAACallback->ICB_GetSupplierVersion
	#define CHK_CmpCAACallbackCB_GetSupplierVersion (pICmpCAACallback != NULL)
	#define EXP_CmpCAACallbackCB_GetSupplierVersion  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CB_GetSupplierVersion
	#define EXT_CB_GetSupplierVersion
	#define GET_CB_GetSupplierVersion(fl)  CAL_CMGETAPI( "CB_GetSupplierVersion" ) 
	#define CAL_CB_GetSupplierVersion pICmpCAACallback->ICB_GetSupplierVersion
	#define CHK_CB_GetSupplierVersion (pICmpCAACallback != NULL)
	#define EXP_CB_GetSupplierVersion  CAL_CMEXPAPI( "CB_GetSupplierVersion" ) 
#else /* DYNAMIC_LINK */
	#define USE_CB_GetSupplierVersion  PFCB_GETSUPPLIERVERSION pfCB_GetSupplierVersion;
	#define EXT_CB_GetSupplierVersion  extern PFCB_GETSUPPLIERVERSION pfCB_GetSupplierVersion;
	#define GET_CB_GetSupplierVersion(fl)  s_pfCMGetAPI2( "CB_GetSupplierVersion", (RTS_VOID_FCTPTR *)&pfCB_GetSupplierVersion, (fl), 0, 0)
	#define CAL_CB_GetSupplierVersion  pfCB_GetSupplierVersion
	#define CHK_CB_GetSupplierVersion  (pfCB_GetSupplierVersion != NULL)
	#define EXP_CB_GetSupplierVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CB_GetSupplierVersion", (RTS_UINTPTR)CB_GetSupplierVersion, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFCB_SENDEVENT ICB_SendEvent;
 	PFCB_POSTEVENT ICB_PostEvent;
 	PFCB_REGISTERCALLBACK ICB_RegisterCallback;
 	PFCB_UNREGISTERCALLBACK ICB_UnregisterCallback;
 	PFCB_CALLFUNCTIONBYINDEX ICB_CallFunctionByIndex;
 	PFCB_ENCODESPEC ICB_EncodeSpec;
 	PFCB_DECODEEVENT ICB_DecodeEvent;
 	PFCB_DECODECLASS ICB_DecodeClass;
 	PFCB_ISHANDLEVALID ICB_IsHandleValid;
 	PFCB_GETHANDLEOFCALLBACK ICB_GetHandleOfCallback;
 	PFCB_GETNUMBERACTIVECALLBACKS ICB_GetNumberActiveCallbacks;
 	PFCB_GETCALLBACK ICB_GetCallback;
 	PFCB_GETSUPPLIERVERSION ICB_GetSupplierVersion;
 } ICmpCAACallback_C;

#ifdef CPLUSPLUS
class ICmpCAACallback : public IBase
{
	public:
		virtual CAA_ERROR CDECL ICB_SendEvent(CAA_ENUM eEvent, CAA_ENUM eSource, RTS_IEC_XWORD dwParam) =0;
		virtual CAA_ERROR CDECL ICB_PostEvent(CAA_ENUM eEvent, CAA_ENUM eSource, RTS_IEC_XWORD dwParam) =0;
		virtual CAA_HANDLE CDECL ICB_RegisterCallback(CB_CALLBACK cbNew, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL ICB_UnregisterCallback(CAA_HANDLE hCallback) =0;
		virtual RTS_IEC_XWORD CDECL ICB_CallFunctionByIndex(CAA_PVOID pCallback, RTS_IEC_XWORD dwParam1, RTS_IEC_XWORD dwParam2, RTS_IEC_XWORD dwParam3, CAA_ERROR* peError) =0;
		virtual RTS_IEC_DWORD CDECL ICB_EncodeSpec(CAA_ENUM eEvent, CAA_ENUM eClass) =0;
		virtual CAA_ENUM CDECL ICB_DecodeEvent(RTS_IEC_DWORD dwSpec) =0;
		virtual CAA_ENUM CDECL ICB_DecodeClass(RTS_IEC_DWORD dwSpec) =0;
		virtual RTS_IEC_BOOL CDECL ICB_IsHandleValid(CAA_HANDLE hHandle, CAA_ERROR* peError) =0;
		virtual CAA_HANDLE CDECL ICB_GetHandleOfCallback(CAA_COUNT ctNumber, CAA_ERROR* peError) =0;
		virtual CAA_COUNT CDECL ICB_GetNumberActiveCallbacks(CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL ICB_GetCallback(CAA_HANDLE hHandle, CB_CALLBACK* pCallback) =0;
		virtual RTS_IEC_WORD CDECL ICB_GetSupplierVersion(CAA_BOOL xDummy) =0;
};
	#ifndef ITF_CmpCAACallback
		#define ITF_CmpCAACallback static ICmpCAACallback *pICmpCAACallback = NULL;
	#endif
	#define EXTITF_CmpCAACallback
#else	/*CPLUSPLUS*/
	typedef ICmpCAACallback_C		ICmpCAACallback;
	#ifndef ITF_CmpCAACallback
		#define ITF_CmpCAACallback
	#endif
	#define EXTITF_CmpCAACallback
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCAACALLBACKITF_H_*/
