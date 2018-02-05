/**
 * <interfacename>CAA_DTUtil_Extern</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`CmpCAADTUtil')

#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAABehaviourModel.h"
#include "CAADTUtil.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Interface functions of CAA DTUtil*/
DEF_ITF_API(`CAA_ERROR',`CDECL',`DTU_WorkerInit',`(void)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`DTU_WorkerExit',`(void)')
DEF_ITF_API(`void',`CDECL',`DTU_GetDateAndTime',`(dtu_getdateandtime_typ* inst)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`DTU_GetDateAndTime_FB_Init',`(CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, dtu_getdateandtime_typ* inst)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`DTU_GetDateAndTime_FB_Exit',`(CAA_BOOL bInCopyCode, dtu_getdateandtime_typ* inst)')
DEF_ITF_API(`void',`CDECL',`DTU_SetDateAndTime',`(dtu_setdateandtime_typ* inst)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`DTU_SetDateAndTime_FB_Init',`(CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, dtu_setdateandtime_typ* inst)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`DTU_SetDateAndTime_FB_Exit',`(CAA_BOOL bInCopyCode, dtu_setdateandtime_typ* inst)')
DEF_ITF_API(`void',`CDECL',`DTU_GetTimeZoneInformation',`(dtu_gettimezoneinformation_typ* inst)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`DTU_GetTimeZoneInformation_FB_Init',`(CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, dtu_gettimezoneinformation_typ* inst)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`DTU_GetTimeZoneInformation_FB_Exit',`(CAA_BOOL bInCopyCode, dtu_gettimezoneinformation_typ* inst)')
DEF_ITF_API(`void',`CDECL',`DTU_SetTimeZoneInformation',`(dtu_settimezoneinformation_typ* inst)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`DTU_SetTimeZoneInformation_FB_Init',`(CAA_BOOL bInitRetains, CAA_BOOL bInCopyCode, dtu_settimezoneinformation_typ* inst)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`DTU_SetTimeZoneInformation_FB_Exit',`(CAA_BOOL bInCopyCode, dtu_settimezoneinformation_typ* inst)')
DEF_ITF_API(`unsigned long',`CDECL',`DTU_DateConcat',`(unsigned short usYear, unsigned short usMonth, unsigned short usDay, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`DTU_DateSplit',`(unsigned long ulDate, unsigned short* pusYear, unsigned short* pusMonth, unsigned short* pusDay)')
DEF_ITF_API(`unsigned long',`CDECL',`DTU_DTConcat',`(unsigned short usYear, unsigned short usMonth, unsigned short usDay, unsigned short usHour, unsigned short usMinute, unsigned short usSecond, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`DTU_DTSplit',`(unsigned long ulDateAndTime, unsigned short* pusYear, unsigned short* pusMonth, unsigned short* pusDay, unsigned short* pusHour, unsigned short* pusMinute, unsigned short* pusSecond)')
DEF_ITF_API(`unsigned long',`CDECL',`DTU_TODConcat',`(unsigned short usHour, unsigned short usMinute, unsigned short usSecond, unsigned short usMillisecond, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`DTU_TODSplit',`(unsigned long ulTime, unsigned short* pusHour, unsigned short* pusMinute, unsigned short* pusSecond, unsigned short* pusMillisecond)')
DEF_ITF_API(`CAA_ENUM',`CDECL',`DTU_GetDayOfWeek',`(unsigned long ulDate, CAA_ERROR* peError)')
DEF_ITF_API(`unsigned short',`CDECL',`DTU_GetSupplierVersion',`(CAA_BOOL xDummy)')

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>DTU_GETDATEANDTIME_PARAMS</description>
 */
typedef struct tagDTU_GETDATEANDTIME_PARAMS
{
	RTS_IEC_DATE_AND_TIME dtDateAndTime;
	CAA_ENUM eTimezone;
} DTU_GETDATEANDTIME_PARAMS;

/**
 * <description>DTU_SETDATEANDTIME_PARAMS</description>
 */
typedef struct tagDTU_SETDATEANDTIME_PARAMS
{
	RTS_IEC_DATE_AND_TIME dtDateAndTime;
} DTU_SETDATEANDTIME_PARAMS;

/**
 * <description>DTU_GETTIMEZONEINFORMATION_PARAMS</description>
 */
typedef struct tagDTU_GETTIMEZONEINFORMATION_PARAMS
{
	RTCLK_TIME_ZONE_INFO tziTimezone;
} DTU_GETTIMEZONEINFORMATION_PARAMS;

/**
 * <description>DTU_SETTIMEZONEINFORMATION_PARAMS</description>
 */
typedef struct tagDTU_SETTIMEZONEINFORMATION_PARAMS
{
	RTCLK_TIME_ZONE_INFO tziTimezone;
} DTU_SETTIMEZONEINFORMATION_PARAMS;

/**
 * <description>dtu_dateconcat</description>
 */
typedef struct tagdtu_dateconcat_struct
{
	RTS_IEC_UINT uiYear;				/* VAR_INPUT */	/* 1970 .. 2099 */
	RTS_IEC_UINT uiMonth;				/* VAR_INPUT */	/* 1 .. 12 */
	RTS_IEC_UINT uiDay;					/* VAR_INPUT */	/* 1 .. 31 */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	RTS_IEC_DATE DTU_DateConcat;		/* VAR_OUTPUT */	/* datDate */
} dtu_dateconcat_struct;

DEF_API(`void',`CDECL',`dtu_dateconcat',`(dtu_dateconcat_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x85BEB2FF),0x03050500)

/**
 * <description>dtu_datesplit</description>
 */
typedef struct tagdtu_datesplit_struct
{
	RTS_IEC_DATE datDate;				/* VAR_INPUT */	
	RTS_IEC_UINT *puiYear;				/* VAR_INPUT */	/* 1970 .. 2099 */
	RTS_IEC_UINT *puiMonth;				/* VAR_INPUT */	/* 1 .. 12 */
	RTS_IEC_UINT *puiDay;				/* VAR_INPUT */	/* 1 .. 31 */
	CAA_ERROR DTU_DateSplit;			/* VAR_OUTPUT */	
} dtu_datesplit_struct;

DEF_API(`void',`CDECL',`dtu_datesplit',`(dtu_datesplit_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4977970B),0x03050500)

/**
 * <description>dtu_dtconcat</description>
 */
typedef struct tagdtu_dtconcat_struct
{
	RTS_IEC_UINT uiYear;				/* VAR_INPUT */	/* 1970 .. 2099 */
	RTS_IEC_UINT uiMonth;				/* VAR_INPUT */	/* 1 .. 12 */
	RTS_IEC_UINT uiDay;					/* VAR_INPUT */	/* 1 .. 31 */
	RTS_IEC_UINT uiHour;				/* VAR_INPUT */	/* 0 .. 23 */
	RTS_IEC_UINT uiMinute;				/* VAR_INPUT */	/* 0 .. 59 */
	RTS_IEC_UINT uiSecond;				/* VAR_INPUT */	/* 0 .. 59 */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	RTS_IEC_DATE_AND_TIME DTU_DTConcat;	/* VAR_OUTPUT */	
} dtu_dtconcat_struct;

DEF_API(`void',`CDECL',`dtu_dtconcat',`(dtu_dtconcat_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xEB362791),0x03050500)

/**
 * <description>dtu_dtsplit</description>
 */
typedef struct tagdtu_dtsplit_struct
{
	RTS_IEC_DATE_AND_TIME dtDateAndTime;	/* VAR_INPUT */	
	RTS_IEC_UINT *puiYear;				/* VAR_INPUT */	/* 1970 .. 2099 */
	RTS_IEC_UINT *puiMonth;				/* VAR_INPUT */	/* 1 .. 12 */
	RTS_IEC_UINT *puiDay;				/* VAR_INPUT */	/* 1 .. 31 */
	RTS_IEC_UINT *puiHour;				/* VAR_INPUT */	/* 0 .. 23 */
	RTS_IEC_UINT *puiMinute;			/* VAR_INPUT */	/* 0 .. 59 */
	RTS_IEC_UINT *puiSecond;			/* VAR_INPUT */	/* 0 .. 59 */
	CAA_ERROR DTU_DTSplit;				/* VAR_OUTPUT */	
} dtu_dtsplit_struct;

DEF_API(`void',`CDECL',`dtu_dtsplit',`(dtu_dtsplit_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xEECCB7E8),0x03050500)

/**
 * <description>dtu_getdateandtime__main</description>
 */
typedef struct tagdtu_getdateandtime_struct
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
	CAA_ENUM ePeriode;					/* VAR_OUTPUT */	
	CAA_BOOL xPreviousExecute;			/* Local variable */	/* value of xExecute in previous cycle */
	CAA_BOOL xPreviousAbortInProgress;	/* Local variable */	/* value of xAbortInPrograss in previous cycle */
	CAA_BOOL xAbortInProgress;			/* Local variable */	/* TRUE: abort is processed
											FALSE: abort is done */
	RTS_IEC_INT iError;					/* Local variable */	/* Local library error ID is transfered to eError by the concrete implementation */
	CAA_HANDLE hJob;					/* Local variable */	/* specific vars */
	DTU_GETDATEANDTIME_PARAMS *pGetDateAndTimeParams;	/* Local variable */	
	ASM_STATE StateJob;					/* Local variable */	
	RTS_IEC_XWORD dwEtrigClass;			/* Local variable */	
} dtu_getdateandtime_struct;

/**
 * <description>dtu_getdateandtime_fb_init</description>
 */
typedef struct tagdtu_getdateandtime_fb_init_struct
{
	dtu_getdateandtime_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInitRetains;				/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Init;					/* VAR_OUTPUT */	
} dtu_getdateandtime_fb_init_struct;

DEF_API(`void',`CDECL',`dtu_getdateandtime__fb_init',`(dtu_getdateandtime_fb_init_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x6854C6A4),0x03050500)

/**
 * <description>dtu_getdateandtime_main</description>
 */
typedef struct tagdtu_getdateandtime_main_struct
{
	dtu_getdateandtime_struct *pInstance;	/* VAR_INPUT */	
} dtu_getdateandtime_main_struct;

DEF_API(`void',`CDECL',`dtu_getdateandtime__main',`(dtu_getdateandtime_main_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x62F3BD7B),0x03050500)

/**
 * <description>dtu_getdateandtime_fb_exit</description>
 */
typedef struct tagdtu_getdateandtime_fb_exit_struct
{
	dtu_getdateandtime_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Exit;					/* VAR_OUTPUT */	
} dtu_getdateandtime_fb_exit_struct;

DEF_API(`void',`CDECL',`dtu_getdateandtime__fb_exit',`(dtu_getdateandtime_fb_exit_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xAD882E4A),0x03050500)

/**
 * <description>dtu_getdayofweek</description>
 */
typedef struct tagdtu_getdayofweek_struct
{
	RTS_IEC_DATE dtDate;				/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_ENUM DTU_GetDayOfWeek;			/* VAR_OUTPUT */	/* eWeekday */
} dtu_getdayofweek_struct;

DEF_API(`void',`CDECL',`dtu_getdayofweek',`(dtu_getdayofweek_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x5765448B),0x03050500)

/**
 * <description>dtu_getsupplierversion</description>
 */
typedef struct tagdtu_getsupplierversion_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	RTS_IEC_WORD DTU_GetSupplierVersion;	/* VAR_OUTPUT */	
} dtu_getsupplierversion_struct;

DEF_API(`void',`CDECL',`dtu_getsupplierversion',`(dtu_getsupplierversion_struct *p)',1,0xD6C53158,0x03050500)

/**
 * <description>dtu_gettimezoneinformation__main</description>
 */
typedef struct tagdtu_gettimezoneinformation_struct
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
	DTU_GETTIMEZONEINFORMATION_PARAMS *pGetTimeZoneInformationParams;	/* Local variable */	
	ASM_STATE StateJob;					/* Local variable */	
	RTS_IEC_XWORD dwEtrigClass;			/* Local variable */	
} dtu_gettimezoneinformation_struct;

/**
 * <description>dtu_gettimezoneinformation_fb_init</description>
 */
typedef struct tagdtu_gettimezoneinformation_fb_init_struct
{
	dtu_gettimezoneinformation_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInitRetains;				/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Init;					/* VAR_OUTPUT */	
} dtu_gettimezoneinformation_fb_init_struct;

DEF_API(`void',`CDECL',`dtu_gettimezoneinformation__fb_init',`(dtu_gettimezoneinformation_fb_init_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x38F23BEC),0x03050500)

/**
 * <description>dtu_gettimezoneinformation_main</description>
 */
typedef struct tagdtu_gettimezoneinformation_main_struct
{
	dtu_gettimezoneinformation_struct *pInstance;	/* VAR_INPUT */	
} dtu_gettimezoneinformation_main_struct;

DEF_API(`void',`CDECL',`dtu_gettimezoneinformation__main',`(dtu_gettimezoneinformation_main_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xFE0E2F0A),0x03050500)

/**
 * <description>dtu_gettimezoneinformation_fb_exit</description>
 */
typedef struct tagdtu_gettimezoneinformation_fb_exit_struct
{
	dtu_gettimezoneinformation_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Exit;					/* VAR_OUTPUT */	
} dtu_gettimezoneinformation_fb_exit_struct;

DEF_API(`void',`CDECL',`dtu_gettimezoneinformation__fb_exit',`(dtu_gettimezoneinformation_fb_exit_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x5FBCC9DE),0x03050500)

/**
 * <description>dtu_setdateandtime__main</description>
 */
typedef struct tagdtu_setdateandtime_struct
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
	DTU_SETDATEANDTIME_PARAMS *pSetDateAndTimeParams;	/* Local variable */	
	ASM_STATE StateJob;					/* Local variable */	
	RTS_IEC_XWORD dwEtrigClass;			/* Local variable */	
} dtu_setdateandtime_struct;

/**
 * <description>dtu_setdateandtime_fb_init</description>
 */
typedef struct tagdtu_setdateandtime_fb_init_struct
{
	dtu_setdateandtime_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInitRetains;				/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Init;					/* VAR_OUTPUT */	
} dtu_setdateandtime_fb_init_struct;

DEF_API(`void',`CDECL',`dtu_setdateandtime__fb_init',`(dtu_setdateandtime_fb_init_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0751D30F),0x03050500)

/**
 * <description>dtu_setdateandtime_main</description>
 */
typedef struct tagdtu_setdateandtime_main_struct
{
	dtu_setdateandtime_struct *pInstance;	/* VAR_INPUT */	
} dtu_setdateandtime_main_struct;

DEF_API(`void',`CDECL',`dtu_setdateandtime__main',`(dtu_setdateandtime_main_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xE8AC014D),0x03050500)

/**
 * <description>dtu_setdateandtime_fb_exit</description>
 */
typedef struct tagdtu_setdateandtime_fb_exit_struct
{
	dtu_setdateandtime_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Exit;					/* VAR_OUTPUT */	
} dtu_setdateandtime_fb_exit_struct;

DEF_API(`void',`CDECL',`dtu_setdateandtime__fb_exit',`(dtu_setdateandtime_fb_exit_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF99DA59E),0x03050500)

/**
 * <description>dtu_settimezoneinformation__main</description>
 */
typedef struct tagdtu_settimezoneinformation_struct
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
	DTU_SETTIMEZONEINFORMATION_PARAMS *pSetTimeZoneInformationParams;	/* Local variable */	
	ASM_STATE StateJob;					/* Local variable */	
	RTS_IEC_XWORD dwEtrigClass;			/* Local variable */	
} dtu_settimezoneinformation_struct;

/**
 * <description>dtu_settimezoneinformation_fb_init</description>
 */
typedef struct tagdtu_settimezoneinformation_fb_init_struct
{
	dtu_settimezoneinformation_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInitRetains;				/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Init;					/* VAR_OUTPUT */	
} dtu_settimezoneinformation_fb_init_struct;

DEF_API(`void',`CDECL',`dtu_settimezoneinformation__fb_init',`(dtu_settimezoneinformation_fb_init_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4088D487),0x03050500)

/**
 * <description>dtu_settimezoneinformation_main</description>
 */
typedef struct tagdtu_settimezoneinformation_main_struct
{
	dtu_settimezoneinformation_struct *pInstance;	/* VAR_INPUT */	
} dtu_settimezoneinformation_main_struct;

DEF_API(`void',`CDECL',`dtu_settimezoneinformation__main',`(dtu_settimezoneinformation_main_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xCDAC022F),0x03050500)

/**
 * <description>dtu_settimezoneinformation_fb_exit</description>
 */
typedef struct tagdtu_settimezoneinformation_fb_exit_struct
{
	dtu_settimezoneinformation_struct *pInstance;	/* VAR_INPUT */	
	CAA_BOOL bInCopyCode;				/* VAR_INPUT */	
	CAA_BOOL FB_Exit;					/* VAR_OUTPUT */	
} dtu_settimezoneinformation_fb_exit_struct;

DEF_API(`void',`CDECL',`dtu_settimezoneinformation__fb_exit',`(dtu_settimezoneinformation_fb_exit_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xCAE0874A),0x03050500)

/**
 * <description>dtu_todconcat</description>
 */
typedef struct tagdtu_todconcat_struct
{
	RTS_IEC_UINT uiHour;				/* VAR_INPUT */	/* 0..23 */
	RTS_IEC_UINT uiMinute;				/* VAR_INPUT */	/* 0..59 */
	RTS_IEC_UINT uiSecond;				/* VAR_INPUT */	/* 0..59 */
	RTS_IEC_UINT uiMillisecond;			/* VAR_INPUT */	/* 0..999 */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	RTS_IEC_TIME_OF_DAY DTU_TODConcat;	/* VAR_OUTPUT */	/* todTime */
} dtu_todconcat_struct;

DEF_API(`void',`CDECL',`dtu_todconcat',`(dtu_todconcat_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB369CA69),0x03050500)

/**
 * <description>dtu_todsplit</description>
 */
typedef struct tagdtu_todsplit_struct
{
	RTS_IEC_TIME_OF_DAY todTime;		/* VAR_INPUT */	
	RTS_IEC_UINT *puiHour;				/* VAR_INPUT */	/* 0..23 */
	RTS_IEC_UINT *puiMinute;			/* VAR_INPUT */	/* 0..59 */
	RTS_IEC_UINT *puiSecond;			/* VAR_INPUT */	/* 0..59 */
	RTS_IEC_UINT *puiMillisecond;		/* VAR_INPUT */	/* 0..999 */
	CAA_ERROR DTU_TODSplit;				/* VAR_OUTPUT */	
} dtu_todsplit_struct;

DEF_API(`void',`CDECL',`dtu_todsplit',`(dtu_todsplit_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x96C543F6),0x03050500)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/
