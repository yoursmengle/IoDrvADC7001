/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		CAASegBufferMan.h
*	Version:		2.4
*	Purpose:		Interface to the CAA Segmented Buffer Manager.
*
******************************************************************************/

#ifdef CAALib

#include "CAADefines.h"

#ifdef CAA_SBM

#ifndef __CAA_SBM_H__
#define __CAA_SBM_H__

#include "CAATypes.h"

#define	SBM_NO_ERROR			((CAA_ERROR)0)
#define	SBM_FIRST_ERROR			((CAA_ERROR)6100)
#define	SBM_TIME_OUT			((CAA_ERROR)6101)
#define SBM_END_OF_BUFFER		((CAA_ERROR)6102)	
#define SBM_WRONG_PARAMETER		((CAA_ERROR)6103)
#define SBM_NO_MEMORY			((CAA_ERROR)6104)
#define SBM_NO_ENTRY			((CAA_ERROR)6105)
#define SBM_REFCOUNT_OVERFLOW	((CAA_ERROR)6130)
#define	SBM_FIRST_MF			((CAA_ERROR)6150)
#define	SBM_LAST_ERROR			((CAA_ERROR)6199)

typedef struct sbm_buffer_tag*  SBM_PBUFFER; /* Segmented Buffer Handle */
typedef struct sbm_queue_tag*   SBM_PQUEUE; /* Queue Handle */


#endif /*__CAA_FILE_H__*/
#endif /* CAA_FILE */
#endif /* CAALib */
