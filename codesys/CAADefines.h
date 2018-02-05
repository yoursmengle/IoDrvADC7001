/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		SysDefines.h
*	Version:		2.4
*	Purpose:		Parameter to system specific features.
*
******************************************************************************/
#ifndef __CAADEFINES_H__                                   
#define __CAADEFINES_H__                                   

/*Special CRITSEC Handling for Linux*/
#define CAA_CRITSEC RTS_HANDLE _sema;
#define CAA_MSR_SAVE
#define CAA_OPEN_CRITSEC()		CAL_SysSemCreate((RTS_RESULT*)0)
#define CAA_ENTER_CRITSEC(h)	(void)CAL_SysSemEnter(h)
#define CAA_EXIT_CRITSEC(h)		(void)CAL_SysSemLeave(h)
#define CAA_CLOSE_CRITSEC(h)	(void)CAL_SysSemDelete(h)

/*Generic CAA defines. Change the defines, before CAADefinesGeneric.h is included.*/
#include "CAADefinesGeneric.h"

#endif /* __CAADEFINES_H__ */

