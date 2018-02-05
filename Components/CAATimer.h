/*****************************************************************************
*
*	Copyright:	© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		CAATimer.h
*	Version:		2.4
*	Purpose:		Interface to CAA Timer library.
*
******************************************************************************/

#ifdef CAALib

#include "CAADefines.h"

#ifndef __CAA_TIMER_H__
#define __CAA_TIMER_H__

#include "CAATypes.h"

#ifdef CAA_TMR

#define	TMR_NO_ERROR				((CAA_ERROR)0)
#define	TMR_FIRST_ERROR				((CAA_ERROR)5500)
#define	TMR_HANDLE_INVALID			((CAA_ERROR)5503)
#define	TMR_NO_MEMORY				((CAA_ERROR)5504)
#define	TMR_INTERVAL_NOT_SUPPORTED	((CAA_ERROR)5505)
#define	TMR_NOT_INITIALIZED			((CAA_ERROR)5506)
#define	TMR_FIRST_MF				((CAA_ERROR)5550)
#define	TMR_LAST_ERROR				((CAA_ERROR)5599)

typedef struct tmr_quality_tag
{
	CAA_TICK tkMax;
	RTS_IEC_UXINT udiResolution;
} TMR_QUALITY;

#define TMR_gc_PropHWTIMER			1
#define TMR_gc_PropSWTIMER			2
#define TMR_gc_PropMinClkRes		200

#endif /* CAA_TIMER */
#endif /* __CAA_TIMER_H__ */
#endif /* CAALib */
