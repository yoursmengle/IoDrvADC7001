/*****************************************************************************
*
*	Copyright:	© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		CAACanMiniDriver.h (cmd)
*	Version:		2.4
*	Purpose:		Interface to the CAA CANbus Mini Driver.
*
******************************************************************************/

#ifndef __CAA_CMD_H__
#define __CAA_CMD_H__

#include "CAADefines.h"

#ifdef CAA_CL2

#include "CAATypes.h"
#include CL2I_INCLUDE

#define	CMD_NO_ERROR		((CAA_ERROR)0)
#define	CMD_SETUP_ERROR		((CAA_ERROR)1)
#define	CMD_WRONG_BAUD		((CAA_ERROR)2)
#define	CMD_WRONG_INDEX		((CAA_ERROR)3)
#define	CMD_WRONG_CYCLE		((CAA_ERROR)4)
#define	CMD_WRONG_VALUE		((CAA_ERROR)5)
#define	CMD_WRONG_MASK		((CAA_ERROR)6)
#define	CMD_WRONG_BLOCK		((CAA_ERROR)7)
#define	CMD_INFO_ERROR		((CAA_ERROR)8)
#define	CMD_NOT_IMPLEMENTED	((CAA_ERROR)9)
#define	CMD_TTL_ERROR   	((CAA_ERROR)10)
#define	CMD_BUS_ERROR   	((CAA_ERROR)11)

/* Return values receive */
#define CMD_NO_MORE_DATA 	CAA_FALSE
#define CMD_MORE_DATA 		CAA_TRUE

/* Return values send */
#define CMD_SND_OK 			CAA_TRUE
#define CMD_SND_NOT_OK 		CAA_FALSE

#define CMD_SUPPORT_IDENTITY    0x01
#define CMD_SUPPORT_SETBLOCK	0x02
#define CMD_SUPPORT_SETCYCLE	0x04
#define CMD_SUPPORT_SETMASK		0x08
#define CMD_SUPPORT_EXTCOBID	0x10
#define CMD_SUPPORT_RTRFRAME	0x20
#define CMD_SUPPORT_BUSALARM	0x40
#define CMD_SUPPORT_STATUSLED	0x80

/* CiA 303-3 ERR Led (Red) */
#define CMD_INDICATOR_ERR_OFF 0x00
#define CMD_INDICATOR_ERR_ON  0x01
#define CMD_INDICATOR_ERR_FLK 0x02 /* flickering */
#define CMD_INDICATOR_ERR_BLK 0x03 /* blinking */
#define CMD_INDICATOR_ERR_SFL 0x04 /* single flash */
#define CMD_INDICATOR_ERR_DFL 0x05 /* double flash */
#define CMD_INDICATOR_ERR_TFL 0x06 /* triple flash */
#define CMD_INDICATOR_ERR_QFL 0x07 /* quadruple flash */

/* CiA 303-3 RUN Led (Green) */
#define CMD_INDICATOR_RUN_OFF 0x00
#define CMD_INDICATOR_RUN_ON  0x10
#define CMD_INDICATOR_RUN_FLK 0x20 /* flickering */
#define CMD_INDICATOR_RUN_BLK 0x30 /* blinking */
#define CMD_INDICATOR_RUN_SFL 0x40 /* single flash */
#define CMD_INDICATOR_RUN_DFL 0x50 /* double flash */
#define CMD_INDICATOR_RUN_TFL 0x60 /* triple flash */
#define CMD_INDICATOR_RUN_QFL 0x70 /* quadruple flash */

/* config file entries */
#define CMD_CONFIGENTRY_TIMESTAMP "Timestamps" /* setting in config file for activating Timestamp support */

typedef struct cmd_info_tag
{
	CL2I_BYTE	bySupport;
	CL2I_BYTE	byMaxCycleIndex;
	CL2I_BYTE	byMaxMaskIndex;
	CL2I_BYTE	byMaxPrio;
    CL2I_BYTE   byNLed;
} CMD_INFO;

typedef struct cmd_cmdrv_tag
{
	CAA_ERROR	(*Setup)(CL2I_BYTE byNet);
	CAA_ERROR	(*Init)(CL2I_BYTE byNet, CL2I_WORD wBaudrate);
	CAA_BOOL	(*Send)(CL2I_BYTE byNet, CAA_HANDLE hBlock, CL2I_BYTE byPrio, CAA_ERROR* pError);
	CAA_BOOL	(*Receive)(CL2I_BYTE byNet, CAA_HANDLE hBlock, CAA_ERROR* pError);
	CAA_ERROR	(*GetInfo)(CL2I_BYTE byNet, CMD_INFO* pInfo);
	CAA_ERROR	(*Dispose)(CL2I_BYTE byNet);
	CAA_ERROR	(*Identify)(CL2I_BYTE byNet, CL2I_BYTE byCount);
	CAA_HANDLE	(*SetBlock)(CL2I_BYTE byNet, CL2I_BYTE byIndex, CAA_HANDLE hBlock, CAA_ERROR* peError);
	CAA_ERROR	(*SetCycle)(CL2I_BYTE byNet, CL2I_BYTE byIndex, CL2I_DWORD dwCycle);
	CAA_ERROR	(*SetMask)(CL2I_BYTE byNet, CL2I_BYTE byIndex, CL2I_DWORD dwValue, CL2I_DWORD dwMask);
	CAA_ERROR	(*ResetAlarm)(CL2I_BYTE byNet);
	CAA_ERROR	(*SetStatus)(CL2I_BYTE byNet, CL2I_BYTE byIndicator);
} CMD_CMDRV;

#endif /* __CAA_CMD_H__ */
#endif /* CAA_CL2 */
