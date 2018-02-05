/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		CAABehaviourModel.h
*	Version:		2.4
*	Purpose:		Interface to CAA Behaviour Model library.
*
******************************************************************************/

#ifdef CAALib

#include "CAADefines.h"

#ifndef __CAA_CBM_H__
#define __CAA_CBM_H__

#include "CAATypes.h"
#include "CAABehaviourModel.h"

#ifdef CAA_CBM

#define CAL_CBM_Etrig_Update_Inputs(inst) do { \
	Etrig.cbm.data = inst; \
	Etrig.xExecute = inst->xExecute; \
	Etrig.xAbortInProgress = inst->xPreviousAbortInProgress; \
	Etrig.xPreviousExecute = inst->xPreviousExecute; \
	Etrig.xDone = inst->xDone; \
	Etrig.xBusy = inst->xBusy; \
	Etrig.xError = inst->xError; \
	Etrig.iError = inst->iError; \
	} while(0)

#define CAL_CBM_Etrig_Update_InputsP(inst) do { \
	pEtrig->cbm.data = inst; \
	pEtrig->xExecute = inst->xExecute; \
	pEtrig->xAbortInProgress = inst->xPreviousAbortInProgress; \
	pEtrig->xPreviousExecute = inst->xPreviousExecute; \
	pEtrig->xDone = inst->xDone; \
	pEtrig->xBusy = inst->xBusy; \
	pEtrig->xError = inst->xError; \
	pEtrig->iError = inst->iError; \
	} while(0)

#define CAL_CBM_Etrig_Update_Outputs(inst) \
	inst->xPreviousAbortInProgress = Etrig.xAbortInProgress; \
	inst->xPreviousExecute = Etrig.xPreviousExecute; \
	inst->xDone = Etrig.xDone; \
	inst->xBusy = Etrig.xBusy; \
	inst->xError = Etrig.xError; \
	inst->iError = Etrig.iError

#define CAL_CBM_Etrig_Update_OutputsP(inst) \
	inst->xPreviousAbortInProgress = pEtrig->xAbortInProgress; \
	inst->xPreviousExecute = pEtrig->xPreviousExecute; \
	inst->xDone = pEtrig->xDone; \
	inst->xBusy = pEtrig->xBusy; \
	inst->xError = pEtrig->xError; \
	inst->iError = pEtrig->iError

#define	CBM_NO_ERROR ((CAA_ERROR)0)
#define CBM_TIME_OUT ((CAA_ERROR)1)

typedef struct cbm_class_tag
{
	void (*start)(struct cbm_class_tag*);
	void (*cyclic)(struct cbm_class_tag*);
	void (*reset)(struct cbm_class_tag*);
	void (*abort)(struct cbm_class_tag*);
	void* data;
} CBM_CLASS;

typedef struct cbm_etrig_class_tag
{
	CBM_CLASS cbm;
	CAA_BOOL xExecute					: 1;
	CAA_BOOL xDone						: 1;
	CAA_BOOL xBusy						: 1;
	CAA_BOOL xError						: 1;
	CAA_BOOL xPreviousExecute			: 1;
	CAA_BOOL xPreviousAbortInProgress	: 1;
	CAA_BOOL xAbortInProgress			: 1;
	CAA_BOOL xDummy						: 1;
	CAA_INT  iError;
} CBM_ETRIG_CLASS;


#endif /* CAA_CBM */
#endif /* __CAA_CBM_H__ */
#endif /* CAALib */
