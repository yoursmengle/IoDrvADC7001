/*****************************************************************************
*
*	Copyright:	© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		CAAMemBlockMan.h
*	Version:		2.4
*	Purpose:		Interface to the CAA Memory Block Manager.
*
******************************************************************************/

#include "CAADefines.h"

#ifdef CAA_MBM

#ifndef __CAA_MEMBLOCKMAN_H__
#define __CAA_MEMBLOCKMAN_H__

#include "CAATypes.h"

#define	MBM_NO_ERROR				((CAA_ERROR)0)
#define	MBM_FIRST_ERROR				((CAA_ERROR)30100)
/* #define MBM_TIME_OUT,			((CAA_ERROR)30101) */  
#define	MBM_UNKNOWN_EVENT 			((CAA_ERROR)30102)
#define	MBM_NOMORE_MEMORY 			((CAA_ERROR)30103)
#define	MBM_WRONG_PRIO				((CAA_ERROR)30104)
#define	MBM_EMPTY_LIST				((CAA_ERROR)30105)
#define	MBM_NO_EXIST_PRIO			((CAA_ERROR)30106)
#define	MBM_PRIO_EXIST				((CAA_ERROR)30107)
#define	MBM_PRIOS_EXCEED			((CAA_ERROR)30108)
#define	MBM_ALIGNMENT_ERROR			((CAA_ERROR)30109)
#define	MBM_BLOCKSIZE_TO_SMALL		((CAA_ERROR)30110)
#define	MBM_EMPTY_POOL				((CAA_ERROR)30111)
#define	MBM_EMPTY_EXCHANGE			((CAA_ERROR)30112)
#define	MBM_TIMEOUT					((CAA_ERROR)30113)
#define	MBM_WRONG_TIMEOUT			((CAA_ERROR)30114)
#define	MBM_REF_OVERFLOW			((CAA_ERROR)30115)
#define	MBM_WRONG_KEY				((CAA_ERROR)30116)
#define	MBM_HANDLE_INVALID 			((CAA_ERROR)30117)
#define	MBM_REFNOTZERO				((CAA_ERROR)30118)
#define	MBM_WRONG_NUM_OF_MSG		((CAA_ERROR)30119)
#define	MBM_BUFFER_TO_BIG			((CAA_ERROR)30120)
#define	MBM_WRONG_OP				((CAA_ERROR)30121)
#define	MBM_NOT_EMPTY				((CAA_ERROR)30122)
#define	MBM_NOT_FULL				((CAA_ERROR)30123)
#define	MBM_KEY_NOT_ENABLED			((CAA_ERROR)30124)
#define	MBM_KEY_NOT_AVAILABLE		((CAA_ERROR)30125)
#define	MBM_GEN_ERROR				((CAA_ERROR)30149)
#define	MBM_FIRST_MF				((CAA_ERROR)30150)
#define	MBM_LAST_ERROR				((CAA_ERROR)30199)


#endif /* __CAA_MEMBLOCKMAN_H__ */
#endif /* CAA_MBM */
