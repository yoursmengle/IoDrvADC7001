/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		CAACallback.h
*	Version:		2.4
*	Purpose:		Interface to the CAA callback handler.
*
******************************************************************************/

#ifdef CAALib

#include "CAADefines.h"

#ifdef CAA_ASM

#ifndef __CAA_ASYNCMAN_H__
#define __CAA_ASYNCMAN_H__

#define ASM_NO_ERROR			((CAA_ERROR)0)
#define ASM_FIRST_ERROR			((CAA_ERROR)5800)
/* #define ASM_TIME_OUT			((CAA_ERROR)5801) */
#define ASM_HANDLE_INVALID		((CAA_ERROR)5802)
#define ASM_WRONG_ARGUMENT		((CAA_ERROR)5803)
#define ASM_NO_WORKER			((CAA_ERROR)5804)
#define ASM_WORKER_REGISTERED	((CAA_ERROR)5805)
#define ASM_ID_INVALID			((CAA_ERROR)5806)
#define ASM_WRONG_STATE			((CAA_ERROR)5807)
#define ASM_STATE_INVALID		((CAA_ERROR)5808)
#define ASM_NO_MEMORY			((CAA_ERROR)5809)
#define ASM_NO_JOB_IN_QUEUE		((CAA_ERROR)5810)
#define ASM_NO_JOB_AVAILABLE	((CAA_ERROR)5811)
#define ASM_ALL_TASK_STARTED	((CAA_ERROR)5812)
#define ASM_TASK_NOT_CREATED	((CAA_ERROR)5813)
#define ASM_FIRST_MF			((CAA_ERROR)5820)
#define ASM_LAST_ERROR			((CAA_ERROR)5850)

#define	ASM_DORMANT				((CAA_ENUM)0)
#define	ASM_BUSY				((CAA_ENUM)1)
#define	ASM_DONE				((CAA_ENUM)2)
#define	ASM_ABORTED				((CAA_ENUM)3)
#define	ASM_STATE_ERROR			((CAA_ENUM)4)

typedef struct ASM_STATEtag
{
	CAA_ERROR			eError;
	CAA_ENUM			eState;
	CAA_USINT		usiProgress;
} ASM_STATE;

typedef struct ASM_IWORKERtag
{
	CAA_ERROR	(*pfExec)(CAA_HANDLE hJob);
	CAA_ERROR	(*pfAbort)(CAA_HANDLE hJob);
	CAA_ERROR	(*pfGetState)(CAA_HANDLE hJob);
	CAA_ERROR	(*pfDispose)(CAA_HANDLE hJob);
	CAA_SIZE	(*pfGetParamSize)(CAA_UDINT udiId);
} ASM_IWORKER;

typedef struct ASM_IWORKER2tag
{
	CAA_ERROR		(*pfExec)(CAA_HANDLE hJob);
	CAA_ERROR		(*pfAbort)(CAA_HANDLE hJob);
	CAA_ERROR		(*pfGetState)(CAA_HANDLE hJob);
	CAA_ERROR		(*pfDispose)(CAA_HANDLE hJob);
	CAA_SIZE		(*pfGetParamSize)(CAA_UDINT udiId);
	CAA_HANDLE		(*pfGetJobGroup)(CAA_UDINT udiId, CAA_HANDLE hJob);
} ASM_IWORKER2;

#define ASM_JOB_NOT_STARTED 0
#define ASM_JOB_DONE		100

#define ASM_SET_ID(LibId, FuncId)	(((LibId) * 0x10000) + (FuncId))

#endif /*__CAA_ASYNCMAN_H__*/
#endif /* CAA_ASM */
#endif /* CAALib */
