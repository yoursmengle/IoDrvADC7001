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
#include "CAARealTimeClock.h"

#ifndef __CAA_DTU_H__
#define __CAA_DTU_H__

#ifdef CAA_DTU

#define	DTU_NO_ERROR		((CAA_ERROR)0)
#define	DTU_FIRST_ERROR		((CAA_ERROR)5750)
#define	DTU_TIME_OUT		((CAA_ERROR)5751)
#define	DTU_NOT_AVAILABLE	((CAA_ERROR)5752)
#define	DTU_INPUT_INVALID	((CAA_ERROR)5753)
#define	DTU_ERROR_UNKNOWN	((CAA_ERROR)5754)
#define	DTU_WRONG_PARAMETER	((CAA_ERROR)5755)
#define	DTU_TZI_NOT_SET		((CAA_ERROR)5756)
#define	DTU_FIRST_MF		((CAA_ERROR)5775)
#define	DTU_LAST_ERROR		((CAA_ERROR)5799)

typedef struct
{
	RTS_IEC_DATE_AND_TIME dtDateAndTime;
	RTS_IEC_INT eTimezone;
} DTU_WGetDateAndTimeParams;

typedef struct
{
	RTS_IEC_DATE_AND_TIME dtDateAndTime;
} DTU_WSetDateAndTimeParams;

typedef struct
{
	RTCLK_TIME_ZONE_INFO tziInfo;
} DTU_WGetTimeZoneInformationParams;

typedef struct
{
	RTCLK_TIME_ZONE_INFO tziInfo;
} DTU_WSetTimeZoneInformationParams;

typedef struct dtu_getdateandtime_v24_tag
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
	DTU_WGetDateAndTimeParams* pGetDateAndTimeParams;	/* VARS */
	ASM_STATE StateJob;						/* VARS */
	RTS_IEC_XWORD dwEtrigClass;				/* VARS */
} dtu_getdateandtime_typ;

typedef struct dtu_setdateandtime_v24_tag
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
	DTU_WSetDateAndTimeParams* pSetDateAndTimeParams;	/* VARS */
	ASM_STATE StateJob;						/* VARS */
	RTS_IEC_XWORD dwEtrigClass;				/* VARS */
} dtu_setdateandtime_typ;

typedef struct dtu_gettimezoneinformation_v24_tag
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
	DTU_WGetTimeZoneInformationParams* pGetTimeZoneInformationParams;	/* VARS */
	ASM_STATE StateJob;						/* VARS */
	RTS_IEC_XWORD dwEtrigClass;				/* VARS */
} dtu_gettimezoneinformation_typ;

typedef struct dtu_settimezoneinformation_v24_tag
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
	DTU_WSetTimeZoneInformationParams* pSetTimeZoneInformationParams;	/* VARS */
	ASM_STATE StateJob;						/* VARS */
	RTS_IEC_XWORD dwEtrigClass;				/* VARS */
} dtu_settimezoneinformation_typ;

#endif /* CAA_DTU */
#endif /* __CAA_DTU_H__ */
#endif /* CAALib */
