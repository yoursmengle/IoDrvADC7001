/*****************************************************************************
*
*	Copyright:	© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		CL2.h
*	Version:		2.4
*	Purpose:		Interface to the CAA CAN Low Level
*
******************************************************************************/

#ifdef CAALib

#include "CAADefines.h"

#ifdef CAA_CL2

#ifndef __CAA_CL2_H__
#define __CAA_CL2_H__

#define	CL2_NO_ERROR				((CAA_ERROR)0)
#define	CL2_FIRST_ERROR 			((CAA_ERROR)10200)
/* #define	CL2_TIME_OUT 			((CAA_ERROR)10201) */
#define	CL2_NO_29BIT_ID				((CAA_ERROR)10202)
#define	CL2_WRONG_BAUDRATE			((CAA_ERROR)10203)
#define	CL2_NO_MEMORY				((CAA_ERROR)10204)
#define	CL2_INVALID_NETID			((CAA_ERROR)10205)
#define	CL2_INVALID_PRIORITY		((CAA_ERROR)10206)
#define	CL2_INVALID_DRIVER_HANDLE	((CAA_ERROR)10207)
#define	CL2_INVALID_MESSAGE_HANDLE	((CAA_ERROR)10208)
#define	CL2_INVALID_ID_HANDLE		((CAA_ERROR)10209)
#define	CL2_NO_DRIVER				((CAA_ERROR)10210)
#define	CL2_SENDING_ERROR			((CAA_ERROR)10211)
#define	CL2_NO_SYNC_SERVICE			((CAA_ERROR)10212)
#define	CL2_NO_SYNC_PRODUCER		((CAA_ERROR)10213)
#define	CL2_NO_SYNC_CONSUMER		((CAA_ERROR)10214)
#define	CL2_NO_SYNC_EVENT			((CAA_ERROR)10215)
#define	CL2_NO_SYNC_WINDOW			((CAA_ERROR)10216)
#define	CL2_NO_SYNC_FOREWARNTIME	((CAA_ERROR)10217)
#define	CL2_NO_TIME_SERVICE			((CAA_ERROR)10218)
#define	CL2_NO_TIME_PRODUCER		((CAA_ERROR)10219)
#define	CL2_NO_TIME_CONSUMER		((CAA_ERROR)10220)
#define	CL2_NO_TIME_EVENT			((CAA_ERROR)10221)
#define	CL2_NO_TIME_FOREWARNTIME	((CAA_ERROR)10222)
#define	CL2_NO_UPDATE_OPERATION		((CAA_ERROR)10223)
#define	CL2_WRONG_PARAM				((CAA_ERROR)10224)
#define	CL2_INVALID_CYCLE_HANDLE	((CAA_ERROR)10225)
#define	CL2_NOT_SUPPORTED			((CAA_ERROR)10226)
#define	CL2_INVALID_HANDLE			((CAA_ERROR)10249)
#define	CL2_FIRST_MF				((CAA_ERROR)10250)
#define	CL2_LAST_ERROR				((CAA_ERROR)10299)

typedef enum CL2_BUSSTATEtag
{
	CL2_UNKNOWN,
	CL2_ERR_FREE,
	CL2_ACTIVE,
	CL2_WARNING,
	CL2_PASSIVE,
	CL2_BUSOFF
} CL2_BUSSTATE;

/* CiA 303-3 ERR Led (Red) */
typedef enum CL2_ERR_INDICATORtag
{
      CL2_ERR_OFF   = 0x00,
      CL2_ERR_ON    = 0x01, /* Bus off */
      CL2_ERR_FLK   = 0x02, /* flickering = LSS/Auto-bitrate detection */
      CL2_ERR_BLK   = 0x03, /* blinking = Invalid Configuration */
      CL2_ERR_SFL   = 0x04, /* single flash = Warning limit reached */
      CL2_ERR_DFL   = 0x05, /* double flash = Error control event */
      CL2_ERR_TFL   = 0x06, /* triple flash = Sync error */
      CL2_ERR_QFL   = 0x07, /* quadruple flash = Event timer error */
	  CL2_ERR_DIS	= 0x0f	/* disable err indicator control */
} CL2_ERR_INDICATOR;

/* CiA 303-3 RUN Led (Green) */
typedef enum CL2_RUN_INDICATORtag
{
      CL2_RUN_OFF   = 0x00,
      CL2_RUN_ON    = 0x10, /* Operational */
      CL2_RUN_FLK   = 0x20, /* flickering = LSS/Auto-bitrate detection */
      CL2_RUN_BLK   = 0x30, /* blinking = Preoperational */
      CL2_RUN_SFL   = 0x40, /* single flash = Stopped */
      CL2_RUN_DFL   = 0x50, /* double flash = Program/Firmeware download */
      CL2_RUN_TFL   = 0x60, /* triple flash = reserved */
      CL2_RUN_QFL   = 0x70, /* quadruple flash = reserved */
	  CL2_RUN_DIS	= 0xf0	/* disable run indicator control */
} CL2_RUN_INDICATOR;


#endif /* __CAA_CL2_H__ */
#endif /* CAA_CL2 */
#endif /* CAALib */
