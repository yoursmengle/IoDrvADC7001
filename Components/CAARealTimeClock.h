/*****************************************************************************
*
*	Copyright:	© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		CAARealTimeClock.h
*	Version:		2.4
*	Purpose:		Interface to CAA Real Time Clock library.
*
******************************************************************************/

#ifdef CAALib

#include "CAADefines.h"
#include "CAAAsyncMan.h"

#ifdef CAA_RTCLK

#ifndef __CAA_RTCLK_H__
#define __CAA_RTCLK_H__

/**
 * <description>PROPERTY</description>
 */
#define RTCLK_TIMEZONESUPPORT ((CAA_ENUM)1)

/**
 * <description>PERIODE</description>
 */
#define	RTCLK_UNKNOWN	((CAA_ENUM)0)
#define	RTCLK_STANDARD	((CAA_ENUM)1)
#define	RTCLK_DAYLIGHT	((CAA_ENUM)2)

/**
 * <description>ERROR</description>
 */
#define	RTCLK_NO_ERROR			((CAA_ERROR)0)
#define	RTCLK_FIRST_ERROR		((CAA_ERROR)5700)
#define	RTCLK_TIME_OUT			((CAA_ERROR)5701)
#define	RTCLK_NOT_AVAILABLE		((CAA_ERROR)5702)
#define	RTCLK_TIME_NOT_VALID	((CAA_ERROR)5703)
#define	RTCLK_WRONG_PARAMETER	((CAA_ERROR)5704)
#define	RTCLK_ERROR_UNKNOWN		((CAA_ERROR)5705)
#define	RTCLK_NOT_IMPLEMENTED	((CAA_ERROR)5706)
#define	RTCLK_FIRST_MF			((CAA_ERROR)5725)
#define	RTCLK_LAST_ERROR		((CAA_ERROR)5749)

/**
 * <description>WEEKDAY</description>
 */
#define	RTCLK_SUNDAY	((CAA_ENUM)0)
#define	RTCLK_MONDAY	((CAA_ENUM)1)
#define	RTCLK_TUESDAY	((CAA_ENUM)2)
#define	RTCLK_WEDNESDAY	((CAA_ENUM)3)
#define	RTCLK_THURSDAY	((CAA_ENUM)4)
#define	RTCLK_FRIDAY	((CAA_ENUM)5)
#define	RTCLK_SATURDAY	((CAA_ENUM)6)

/**
 * <description>SYSTEMTIME</description>
 */
typedef struct tagSYSTEMTIME
{
	CAA_UINT uiYear;
	CAA_UINT uiMonth;
	CAA_ENUM eWeekday;
	CAA_UINT uiDay;
	CAA_UINT uiHour;
	CAA_UINT uiMinute;
	CAA_UINT uiSecond;
} RTCLK_SYSTEMTIME;

/**
 * <description>PERIODE_INFO</description>
 */
typedef struct tagPERIODE_INFO
{
	char cName[33];
	RTCLK_SYSTEMTIME stDate;
	CAA_INT iBias;
} RTCLK_PERIODE_INFO;

/**
 * <description>TIME_ZONE_INFO</description>
 */
typedef struct tagTIME_ZONE_INFO
{
	CAA_INT iBias;
	RTCLK_PERIODE_INFO sPeriode[2];
} RTCLK_TIME_ZONE_INFO;

typedef struct
{
	RTS_IEC_DATE_AND_TIME dtDateAndTime;
	RTS_IEC_INT eTimezone;
} RTCLK_WGetDateAndTimeParams;

typedef struct
{
	RTS_IEC_DATE_AND_TIME dtDateAndTime;
} RTCLK_WSetDateAndTimeParams;

typedef struct
{
	RTCLK_TIME_ZONE_INFO tziInfo;
} RTCLK_WGetTimeZoneInformationParams;

typedef struct
{
	RTCLK_TIME_ZONE_INFO tziInfo;
} RTCLK_WSetTimeZoneInformationParams;

typedef struct rtclk_getdateandtime_v24_tag
{
	CAA_BOOL xExecute;						/* VAR_INPUT */
	CAA_BOOL xDone;							/* VAR_OUTPUT */
	CAA_BOOL xBusy;							/* VAR_OUTPUT */
	CAA_BOOL xError;						/* VAR_OUTPUT */
	CAA_ERROR eError;						/* VAR_OUTPUT */
	RTS_IEC_DATE_AND_TIME dtDateAndTime;	/* VAR_OUTPUT */
	CAA_ENUM eTimezone;						/* VAR_OUTPUT */
	CAA_BOOL xPreviousExecute;				/* VARS */
	CAA_BOOL xPreviousAbortInProgress;		/* VARS */
	CAA_BOOL xAbortInProgress;				/* VARS */
	RTS_IEC_INT iError;						/* VARS */
	CAA_HANDLE hJob;						/* VARS */
	RTCLK_WGetDateAndTimeParams* pGetDateAndTimeParams;	/* VARS */
	ASM_STATE StateJob;						/* VARS */	
	RTS_IEC_XWORD dwEtrigClass;				/* VARS */
} rtclk_getdateandtime_typ;

typedef struct rtclk_setdateandtime_v24_tag
{
	CAA_BOOL xExecute;						/* VAR_INPUT */
	RTS_IEC_DATE_AND_TIME dtDateAndTime;	/* VAR_INPUT */
	CAA_BOOL xDone;							/* VAR_OUTPUT */
	CAA_BOOL xBusy;							/* VAR_OUTPUT */
	CAA_BOOL xError;						/* VAR_OUTPUT */
	CAA_ERROR eError;						/* VAR_OUTPUT */
	CAA_BOOL xPreviousExecute;				/* VARS */
	CAA_BOOL xPreviousAbortInProgress;		/* VARS */
	CAA_BOOL xAbortInProgress;				/* VARS */
	RTS_IEC_INT iError;						/* VARS */
	CAA_HANDLE hJob;						/* VARS */
	RTCLK_WSetDateAndTimeParams* pSetDateAndTimeParams;	/* VARS */
	ASM_STATE StateJob;						/* VARS */
	RTS_IEC_XWORD dwEtrigClass;				/* VARS */	
} rtclk_setdateandtime_typ;

typedef struct rtclk_gettimezoneinformation_v24_tag
{
	CAA_BOOL xExecute;						/* VAR_INPUT */
	CAA_BOOL xDone;							/* VAR_OUTPUT */
	CAA_BOOL xBusy;							/* VAR_OUTPUT */
	CAA_BOOL xError;						/* VAR_OUTPUT */
	CAA_ERROR eError;						/* VAR_OUTPUT */
	RTCLK_TIME_ZONE_INFO tziInfo;			/* VAR_OUTPUT */
	CAA_BOOL xPreviousExecute;				/* VARS */
	CAA_BOOL xPreviousAbortInProgress;		/* VARS */
	CAA_BOOL xAbortInProgress;				/* VARS */
	RTS_IEC_INT iError;						/* VARS */
	CAA_HANDLE hJob;						/* VARS */
	RTCLK_WGetTimeZoneInformationParams* pGetTimeZoneInformationParams;	/* VARS */
	ASM_STATE StateJob;						/* VARS */
	RTS_IEC_XWORD dwEtrigClass;				/* VARS */
} rtclk_gettimezoneinformation_typ;

typedef struct rtclk_settimezoneinformation_v24_tag
{
	CAA_BOOL xExecute;						/* VAR_INPUT */
	RTCLK_TIME_ZONE_INFO tziInfo;			/* VAR_OUTPUT */
	CAA_BOOL xDone;							/* VAR_OUTPUT */
	CAA_BOOL xBusy;							/* VAR_OUTPUT */
	CAA_BOOL xError;						/* VAR_OUTPUT */
	CAA_ERROR eError;						/* VAR_OUTPUT */
	CAA_BOOL xPreviousExecute;				/* VARS */
	CAA_BOOL xPreviousAbortInProgress;		/* VARS */
	CAA_BOOL xAbortInProgress;				/* VARS */
	RTS_IEC_INT iError;						/* VARS */
	CAA_HANDLE hJob;						/* VARS */
	RTCLK_WSetTimeZoneInformationParams* pSetTimeZoneInformationParams;	/* VARS */
	ASM_STATE StateJob;						/* VARS */
	RTS_IEC_XWORD dwEtrigClass;				/* VARS */	
} rtclk_settimezoneinformation_typ;


#endif /*__CAA_RTCLK_H__*/
#endif /* CAA_RTCLK */
#endif /* CAALib */

