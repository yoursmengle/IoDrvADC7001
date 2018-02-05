SET_INTERFACE_NAME(`CmpCAARealTimeClock')

#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAARealTimeClock.h"
#include "CAABehaviourModel.h"
#include "CAAAsyncMan.h"
#include "CAAMemBlockMan.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Interface functions of CAA Real Time Clock*/
DEF_ITF_API(`CAA_ERROR',`CDECL',`RTCLK_WorkerInit',`(void)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`RTCLK_WorkerExit',`(void)')
DEF_ITF_API(`void',`CDECL',`RTCLK_GetDateAndTime',`(rtclk_getdateandtime_typ* inst)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`RTCLK_GetDateAndTime_FB_Init',`(CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, rtclk_getdateandtime_typ* inst)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`RTCLK_GetDateAndTime_FB_Exit',`(CAA_BOOL bInCopyCode, rtclk_getdateandtime_typ* inst)')
DEF_ITF_API(`void',`CDECL',`RTCLK_SetDateAndTime',`(rtclk_setdateandtime_typ* inst)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`RTCLK_SetDateAndTime_FB_Init',`(CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, rtclk_setdateandtime_typ* inst)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`RTCLK_SetDateAndTime_FB_Exit',`(CAA_BOOL bInCopyCode, rtclk_setdateandtime_typ* inst)')
DEF_ITF_API(`void',`CDECL',`RTCLK_GetTimeZoneInformation',`(rtclk_gettimezoneinformation_typ* inst)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`RTCLK_GetTimeZoneInformation_FB_Init',`(CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, rtclk_gettimezoneinformation_typ* inst)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`RTCLK_GetTimeZoneInformation_FB_Exit',`(CAA_BOOL bInCopyCode, rtclk_gettimezoneinformation_typ* inst)')
DEF_ITF_API(`void',`CDECL',`RTCLK_SetTimeZoneInformation',`(rtclk_settimezoneinformation_typ* inst)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`RTCLK_SetTimeZoneInformation_FB_Init',`(CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, rtclk_settimezoneinformation_typ* inst)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`RTCLK_SetTimeZoneInformation_FB_Exit',`(CAA_BOOL bInCopyCode, rtclk_settimezoneinformation_typ* inst)')
DEF_ITF_API(`unsigned short',`CDECL',`RTCLK_GetSupplierVersion',`(CAA_BOOL xDummy)')
DEF_ITF_API(`RTS_IEC_XWORD',`CDECL',`RTCLK_GetProperty',`(unsigned short usProperty)')

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>RTCLK_GETTIMEZONEINFORMATION_PARAMS</description>
 */
typedef struct tagRTCLK_GETTIMEZONEINFORMATION_PARAMS
{
	RTCLK_TIME_ZONE_INFO tziTimezone;
} RTCLK_GETTIMEZONEINFORMATION_PARAMS;

/**
 * <description>RTCLK_SETTIMEZONEINFORMATION_PARAMS</description>
 */
typedef struct tagRTCLK_SETTIMEZONEINFORMATION_PARAMS
{
	RTCLK_TIME_ZONE_INFO tziTimezone;
} RTCLK_SETTIMEZONEINFORMATION_PARAMS;

/**
 * <description>RTCLK_SETDATEANDTIME_PARAMS</description>
 */
typedef struct tagRTCLK_SETDATEANDTIME_PARAMS
{
	RTS_IEC_DATE_AND_TIME dtDateAndTime;
} RTCLK_SETDATEANDTIME_PARAMS;

/**
 * <description>RTCLK_GETDATEANDTIME_PARAMS</description>
 */
typedef struct tagRTCLK_GETDATEANDTIME_PARAMS
{
	RTS_IEC_DATE_AND_TIME dtDateAndTime;
	CAA_ENUM eTimezone;
} RTCLK_GETDATEANDTIME_PARAMS;

/**
 * <description>rtclk_getdateandtime__main</description>
 */
typedef struct tagrtclk_getdateandtime_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	CAA_BOOL xExecute;					/* VAR_INPUT */	/* Rising edge: Action start
							Falling edge: Resets outputs
							If a falling edge occurs before the function block has completed its action, the outputs operate
							in the usual manner and are only reset if either the action is completed or
							in the event of an error. In this case, the corresponding output values (xDone, xError, iError)
							are present at the outputs for exactly one cycle. */
	CAA_BOOL xDone;						/* VAR_OUTPUT */	/* Action successfully completed */
	CAA_BOOL xBusy;						/* VAR_OUTPUT */	/* Function block active */
	CAA_BOOL xError;					/* VAR_OUTPUT */	/* TRUE: error occurred, function block aborts action
							FALSE: no error */
	CAA_ERROR eError;					/* VAR_OUTPUT */	
	RTS_IEC_DATE_AND_TIME dtDateAndTime;	/* VAR_OUTPUT */	
	CAA_ENUM eTimezone;					/* VAR_OUTPUT */	
	CAA_BOOL xPreviousExecute;			/* Local variable */	/* value of xExecute in previous cycle */
	CAA_BOOL xPreviousAbortInProgress;	/* Local variable */	/* value of xAbortInPrograss in previous cycle */
	CAA_BOOL xAbortInProgress;			/* Local variable */	/* TRUE: abort is processed
											FALSE: abort is done */
	RTS_IEC_INT iError;					/* Local variable */	/* Local library error ID is transfered to eError by the concrete implementation */
	CAA_HANDLE hJob;					/* Local variable */	/* specific vars */
	RTCLK_GETDATEANDTIME_PARAMS *pGetDateAndTimeParams;	/* Local variable */	
	ASM_STATE StateJob;					/* Local variable */	
	RTS_IEC_XWORD dwEtrigClass;			/* Local variable */	
} rtclk_getdateandtime_struct;

/**
 * <description>rtclk_getdateandtime_main</description>
 */
typedef struct tagrtclk_getdateandtime_main_struct
{
	rtclk_getdateandtime_struct *pInstance;	/* VAR_INPUT */	
} rtclk_getdateandtime_main_struct;

DEF_API(`void',`CDECL',`rtclk_getdateandtime__main',`(rtclk_getdateandtime_main_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA101FA6A),0x03050528)

/**
 * <description>rtclk_getdateandtime_fb_init</description>
 */
typedef struct tagrtclk_getdateandtime_fb_init_struct
{
	rtclk_getdateandtime_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInitRetains;				/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Init;					/* VAR_OUTPUT */	
} rtclk_getdateandtime_fb_init_struct;

DEF_API(`void',`CDECL',`rtclk_getdateandtime__fb_init',`(rtclk_getdateandtime_fb_init_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD64C25C7),0x03050528)

/**
 * <description>rtclk_getdateandtime_fb_exit</description>
 */
typedef struct tagrtclk_getdateandtime_fb_exit_struct
{
	rtclk_getdateandtime_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Exit;					/* VAR_OUTPUT */	
} rtclk_getdateandtime_fb_exit_struct;

DEF_API(`void',`CDECL',`rtclk_getdateandtime__fb_exit',`(rtclk_getdateandtime_fb_exit_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA9565B5F),0x03050528)

/**
 * <description>rtclk_getproperty</description>
 */
typedef struct tagrtclk_getproperty_struct
{
	RTS_IEC_WORD wProperty;				/* VAR_INPUT */	/* property number */
	RTS_IEC_XWORD RTCLK_GetProperty;	/* VAR_OUTPUT */	
} rtclk_getproperty_struct;

DEF_API(`void',`CDECL',`rtclk_getproperty',`(rtclk_getproperty_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xCE228B87),0x03050528)

/**
 * <description>rtclk_getsupplierversion</description>
 */
typedef struct tagrtclk_getsupplierversion_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	RTS_IEC_WORD RTCLK_GetSupplierVersion;	/* VAR_OUTPUT */	
} rtclk_getsupplierversion_struct;

DEF_API(`void',`CDECL',`rtclk_getsupplierversion',`(rtclk_getsupplierversion_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x25593C3C),0x03050528)

/**
 * <description>rtclk_gettimezoneinformation__main</description>
 */
typedef struct tagrtclk_gettimezoneinformation_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	CAA_BOOL xExecute;					/* VAR_INPUT */	/* Rising edge: Action start
							Falling edge: Resets outputs
							If a falling edge occurs before the function block has completed its action, the outputs operate
							in the usual manner and are only reset if either the action is completed or
							in the event of an error. In this case, the corresponding output values (xDone, xError, iError)
							are present at the outputs for exactly one cycle. */
	CAA_BOOL xDone;						/* VAR_OUTPUT */	/* Action successfully completed */
	CAA_BOOL xBusy;						/* VAR_OUTPUT */	/* Function block active */
	CAA_BOOL xError;					/* VAR_OUTPUT */	/* TRUE: error occurred, function block aborts action
							FALSE: no error */
	CAA_ERROR eError;					/* VAR_OUTPUT */	
	RTCLK_TIME_ZONE_INFO tziInfo;		/* VAR_OUTPUT */	
	CAA_BOOL xPreviousExecute;			/* Local variable */	/* value of xExecute in previous cycle */
	CAA_BOOL xPreviousAbortInProgress;	/* Local variable */	/* value of xAbortInPrograss in previous cycle */
	CAA_BOOL xAbortInProgress;			/* Local variable */	/* TRUE: abort is processed
											FALSE: abort is done */
	RTS_IEC_INT iError;					/* Local variable */	/* Local library error ID is transfered to eError by the concrete implementation */
	CAA_HANDLE hJob;					/* Local variable */	/* specific vars */
	RTCLK_GETTIMEZONEINFORMATION_PARAMS *pGetTimeZoneInformationParams;	/* Local variable */	
	ASM_STATE StateJob;					/* Local variable */	
	RTS_IEC_XWORD dwEtrigClass;			/* Local variable */	
} rtclk_gettimezoneinformation_struct;

/**
 * <description>rtclk_gettimezoneinformation_main</description>
 */
typedef struct tagrtclk_gettimezoneinformation_main_struct
{
	rtclk_gettimezoneinformation_struct *pInstance;	/* VAR_INPUT */	
} rtclk_gettimezoneinformation_main_struct;

DEF_API(`void',`CDECL',`rtclk_gettimezoneinformation__main',`(rtclk_gettimezoneinformation_main_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x9FDA8153),0x03050528)

/**
 * <description>rtclk_gettimezoneinformation_fb_init</description>
 */
typedef struct tagrtclk_gettimezoneinformation_fb_init_struct
{
	rtclk_gettimezoneinformation_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInitRetains;				/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Init;					/* VAR_OUTPUT */	
} rtclk_gettimezoneinformation_fb_init_struct;

DEF_API(`void',`CDECL',`rtclk_gettimezoneinformation__fb_init',`(rtclk_gettimezoneinformation_fb_init_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC7722D11),0x03050528)

/**
 * <description>rtclk_gettimezoneinformation_fb_exit</description>
 */
typedef struct tagrtclk_gettimezoneinformation_fb_exit_struct
{
	rtclk_gettimezoneinformation_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Exit;					/* VAR_OUTPUT */	
} rtclk_gettimezoneinformation_fb_exit_struct;

DEF_API(`void',`CDECL',`rtclk_gettimezoneinformation__fb_exit',`(rtclk_gettimezoneinformation_fb_exit_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x578320C7),0x03050528)

/**
 * <description>rtclk_setdateandtime__main</description>
 */
typedef struct tagrtclk_setdateandtime_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	CAA_BOOL xExecute;					/* VAR_INPUT */	/* Rising edge: Action start
							Falling edge: Resets outputs
							If a falling edge occurs before the function block has completed its action, the outputs operate
							in the usual manner and are only reset if either the action is completed or
							in the event of an error. In this case, the corresponding output values (xDone, xError, iError)
							are present at the outputs for exactly one cycle. */
	RTS_IEC_DATE_AND_TIME dtDateAndTime;	/* VAR_INPUT */	
	CAA_BOOL xDone;						/* VAR_OUTPUT */	/* Action successfully completed */
	CAA_BOOL xBusy;						/* VAR_OUTPUT */	/* Function block active */
	CAA_BOOL xError;					/* VAR_OUTPUT */	/* TRUE: error occurred, function block aborts action
							FALSE: no error */
	CAA_ERROR eError;					/* VAR_OUTPUT */	
	CAA_BOOL xPreviousExecute;			/* Local variable */	/* value of xExecute in previous cycle */
	CAA_BOOL xPreviousAbortInProgress;	/* Local variable */	/* value of xAbortInPrograss in previous cycle */
	CAA_BOOL xAbortInProgress;			/* Local variable */	/* TRUE: abort is processed
											FALSE: abort is done */
	RTS_IEC_INT iError;					/* Local variable */	/* Local library error ID is transfered to eError by the concrete implementation */
	CAA_HANDLE hJob;					/* Local variable */	/* specific vars */
	RTCLK_SETDATEANDTIME_PARAMS *pSetDateAndTimeParams;	/* Local variable */	
	ASM_STATE StateJob;					/* Local variable */	
	RTS_IEC_XWORD dwEtrigClass;			/* Local variable */	
} rtclk_setdateandtime_struct;

/**
 * <description>rtclk_setdateandtime_main</description>
 */
typedef struct tagrtclk_setdateandtime_main_struct
{
	rtclk_setdateandtime_struct *pInstance;	/* VAR_INPUT */	
} rtclk_setdateandtime_main_struct;

DEF_API(`void',`CDECL',`rtclk_setdateandtime__main',`(rtclk_setdateandtime_main_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x11AD8AA3),0x03050528)

/**
 * <description>rtclk_setdateandtime_fb_init</description>
 */
typedef struct tagrtclk_setdateandtime_fb_init_struct
{
	rtclk_setdateandtime_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInitRetains;				/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Init;					/* VAR_OUTPUT */	
} rtclk_setdateandtime_fb_init_struct;

DEF_API(`void',`CDECL',`rtclk_setdateandtime__fb_init',`(rtclk_setdateandtime_fb_init_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA2DDB783),0x03050528)

/**
 * <description>rtclk_setdateandtime_fb_exit</description>
 */
typedef struct tagrtclk_setdateandtime_fb_exit_struct
{
	rtclk_setdateandtime_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Exit;					/* VAR_OUTPUT */	
} rtclk_setdateandtime_fb_exit_struct;

DEF_API(`void',`CDECL',`rtclk_setdateandtime__fb_exit',`(rtclk_setdateandtime_fb_exit_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xFABF672F),0x03050528)

/**
 * <description>rtclk_settimezoneinformation__main</description>
 */
typedef struct tagrtclk_settimezoneinformation_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	CAA_BOOL xExecute;					/* VAR_INPUT */	/* Rising edge: Action start
							Falling edge: Resets outputs
							If a falling edge occurs before the function block has completed its action, the outputs operate
							in the usual manner and are only reset if either the action is completed or
							in the event of an error. In this case, the corresponding output values (xDone, xError, iError)
							are present at the outputs for exactly one cycle. */
	RTCLK_TIME_ZONE_INFO tziInfo;		/* VAR_INPUT */	
	CAA_BOOL xDone;						/* VAR_OUTPUT */	/* Action successfully completed */
	CAA_BOOL xBusy;						/* VAR_OUTPUT */	/* Function block active */
	CAA_BOOL xError;					/* VAR_OUTPUT */	/* TRUE: error occurred, function block aborts action
							FALSE: no error */
	CAA_ERROR eError;					/* VAR_OUTPUT */	
	CAA_BOOL xPreviousExecute;			/* Local variable */	/* value of xExecute in previous cycle */
	CAA_BOOL xPreviousAbortInProgress;	/* Local variable */	/* value of xAbortInPrograss in previous cycle */
	CAA_BOOL xAbortInProgress;			/* Local variable */	/* TRUE: abort is processed
											FALSE: abort is done */
	RTS_IEC_INT iError;					/* Local variable */	/* Local library error ID is transfered to eError by the concrete implementation */
	CAA_HANDLE hJob;					/* Local variable */	/* specific vars */
	RTCLK_SETTIMEZONEINFORMATION_PARAMS *pSetTimeZoneInformationParams;	/* Local variable */	
	ASM_STATE StateJob;					/* Local variable */	
	RTS_IEC_XWORD dwEtrigClass;			/* Local variable */	
} rtclk_settimezoneinformation_struct;

/**
 * <description>rtclk_settimezoneinformation_main</description>
 */
typedef struct tagrtclk_settimezoneinformation_main_struct
{
	rtclk_settimezoneinformation_struct *pInstance;	/* VAR_INPUT */	
} rtclk_settimezoneinformation_main_struct;

DEF_API(`void',`CDECL',`rtclk_settimezoneinformation__main',`(rtclk_settimezoneinformation_main_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xE87F7BC1),0x03050528)

/**
 * <description>rtclk_settimezoneinformation_fb_init</description>
 */
typedef struct tagrtclk_settimezoneinformation_fb_init_struct
{
	rtclk_settimezoneinformation_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInitRetains;				/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Init;					/* VAR_OUTPUT */	
} rtclk_settimezoneinformation_fb_init_struct;

DEF_API(`void',`CDECL',`rtclk_settimezoneinformation__fb_init',`(rtclk_settimezoneinformation_fb_init_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xDDDC4554),0x03050528)

/**
 * <description>rtclk_settimezoneinformation_fb_exit</description>
 */
typedef struct tagrtclk_settimezoneinformation_fb_exit_struct
{
	rtclk_settimezoneinformation_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Exit;					/* VAR_OUTPUT */	
} rtclk_settimezoneinformation_fb_exit_struct;

DEF_API(`void',`CDECL',`rtclk_settimezoneinformation__fb_exit',`(rtclk_settimezoneinformation_fb_exit_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x2B8D8BD0),0x03050528)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

