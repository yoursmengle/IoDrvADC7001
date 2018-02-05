/*****************************************************************************
*
*	Copyright:	© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		sdo.h
*	Version:		2.4
*	Purpose:		Implementation of Client side CANopen service data object protocol.
*
******************************************************************************/

#ifdef CAALib

#include "CAADefines.h"

#ifdef CAA_CL2

#ifndef _CLIENT_SDO_H_
#define _CLIENT_SDO_H_

#define SDO_PRIO 1
#define DEFAULT_SDO_TIMEOUT			(1000000UL) /* 1 Sec Timeout in uSec */
#define SDO_EVENT			(8001)

#define	AUTO      (CAA_UINT)0
#define	EXPEDITED (CAA_UINT)1
#define	SEGMENTED (CAA_UINT)2
#define	BLOCK     (CAA_UINT)3

#define SDOABORT_NO_ERROR					((CAA_UDINT)0)
#define SDOABORT_TOGGLEBIT_ERROR			((CAA_UDINT)0x5030000)
#define SDOABORT_INVALID_CS					((CAA_UDINT)0x05040001)
#define SDOABORT_INVALID_SEQUENCE_NUMBER	((CAA_UDINT)0x05040002)
#define SDOABORT_INVALID_BLOCKSIZE			((CAA_UDINT)0x05040003)
#define SDOABORT_INVALID_CRC				((CAA_UDINT)0x05040004)
#define SDOABORT_OBJECT_NOT_EXISTING		((CAA_UDINT)0x06020000) 

#define	CS_NO_ERROR							((CAA_ERROR)0)
#define	CS_FIRST_ERROR						((CAA_ERROR)10400)
#define CS_TIME_OUT							((CAA_ERROR)10401)

#define CS_NOT_OPEN							((CAA_ERROR)10404)
#define CS_ALREADY_OPEN						((CAA_ERROR)10405)
#define CS_ALREADY_CLOSE					((CAA_ERROR)10406)
#define CS_REQUEST_ERROR					((CAA_ERROR)10407)
#define	CS_WRONG_PARAMETER					((CAA_ERROR)10408)
#define	CS_NODEID_UNKNOWN					((CAA_ERROR)10409)
#define	CS_SDO_CHANNEL_UNKNOWN				((CAA_ERROR)10410)
#define	CS_INTERNAL_ERROR					((CAA_ERROR)10411)
#define	CS_NOT_ENOUGH_MEMORY				((CAA_ERROR)10412)
#define	CS_ABORT_BY_SERVER					((CAA_ERROR)10413)
#define	CS_INVALID_SEQUENCE_NUMBER			((CAA_ERROR)10414)
#define	CS_INVALID_BLOCKSIZE				((CAA_ERROR)10415)
#define	CS_CRC_ERROR						((CAA_ERROR)10416)
#define CS_FIRST_MF							((CAA_ERROR)10450)
#define	CS_LAST_ERROR						((CAA_ERROR)10499)

typedef CAA_ENUM SDO_MODE;

/*obsolete structure for old SDORead with maximal datalength 64kb (Size is UINT datatype)*/
typedef struct sdo_read_tag
{
	CAA_USINT	usiNodeId;
	CAA_USINT	usiChannel;
	CAA_UINT	uiIndex;
	CAA_USINT	usiSubIndex;
	CAA_BOOL	xUseSpecificTimeout;
	CAA_BOOL	xBlockTransfer;
	CAA_USINT	usiPST; /*protocol switch threshold*/
	CAA_UINT	uiState;
	CAA_UINT	uiSize;
	CAA_BYTE*	pbyData;
	CAA_UDINT	udiAbortCode;
/* ----------------------------- */
	CAA_HANDLE	hDriver;
	CAA_HANDLE	hReceiver;
	CAA_UDINT	udiRxId;
	CAA_UDINT	udiTxId;
	CAA_UDINT	udiSegLen;
	CAA_UDINT	udiCurPos;
	CAA_TICK	tkCurrentTick;
	CAA_BOOL	xTimeout;
	CAA_USINT	usiSeqCnt;
	CAA_UINT	uiSDOState;
	CAA_TICK	tkTimeout;
/* ----------------------------- */
	CAA_COUNT	ctTimeout;
} SDO_READ;

typedef struct sdo_read2_tag
{
	CAA_USINT	usiNodeId;
	CAA_USINT	usiChannel;
	CAA_UINT	uiIndex;
	CAA_USINT	usiSubIndex;
	CAA_BOOL	xUseSpecificTimeout; /* TRUE: ctTimeout will be used; ELSE: default timeout */
	CAA_BOOL	xBlockTransfer;
	CAA_USINT	usiPST; /* Protocol Switch Threshold in bytes (only for block transfer) */
	CAA_UINT	uiState;
	CAA_BOOL	xLegacyCRC; /* FALSE: Use default CANopen CRC for block transfer; TRUE: Use legacy CRC (used before 3.5 SP10). */
	CAA_BOOL	xDummy;
	CAA_UDINT	udiSize;
	CAA_BYTE*	pbyData;
	CAA_UDINT	udiAbortCode;
/* ----------------------------- */
	CAA_HANDLE	hDriver;
	CAA_HANDLE	hReceiver;
	CAA_UDINT	udiRxId;
	CAA_UDINT	udiTxId;
	CAA_UDINT	udiSegLen;
	CAA_UDINT	udiCurPos;
	CAA_TICK	tkCurrentTick;
	CAA_BOOL	xTimeout;
	CAA_USINT	usiSeqCnt;
	CAA_UINT	uiSDOState;
	CAA_TICK	tkTimeout;
/* ----------------------------- */
	CAA_COUNT	ctTimeout; /* Timeout in us */
} SDO_READ2;

/*obsolete structure for old SDOWrite with maximal datalength 64kb (Size is UINT datatype)*/
typedef struct sdo_write_tag
{
	CAA_USINT	usiNodeId;
	CAA_USINT	usiChannel;
	CAA_UINT	uiIndex;
	CAA_USINT	usiSubIndex;
	CAA_BOOL	xUseSpecificTimeout;
	CAA_ENUM	eMode;
	CAA_UINT	uiState;
	CAA_UINT	uiSize;
	CAA_BYTE*	pbyData;
	CAA_UDINT	udiAbortCode;
/* ----------------------------- */
	CAA_HANDLE	hDriver;
	CAA_HANDLE	hReceiver;
	CAA_UDINT	udiRxId;
	CAA_UDINT	udiTxId;
	CAA_UDINT	udiSeqCnt;
	CAA_UDINT	udiCurPos;
	CAA_TICK	tkCurrentTick;
	CAA_BOOL	xTimeout;
	CAA_USINT	usiBlkSize;
	CAA_UINT	uiSDOState;
	CAA_TICK	tkTimeout;
/* ----------------------------- */
	CAA_COUNT	ctTimeout;
} SDO_WRITE;

typedef struct sdo_write2_tag
{
	CAA_USINT	usiNodeId;
	CAA_USINT	usiChannel;
	CAA_UINT	uiIndex;
	CAA_USINT	usiSubIndex;
	CAA_BOOL	xUseSpecificTimeout; /* TRUE: ctTimeout will be used; ELSE: default timeout */
	CAA_ENUM	eMode;
	CAA_UINT	uiState;
	CAA_BOOL	xLegacyCRC; /* FALSE: Use default CANopen CRC for block transfer; TRUE: Use legacy CRC (used before 3.5 SP10). */
	CAA_BOOL	xDummy; 
	CAA_UDINT	udiSize;
	CAA_BYTE*	pbyData;
	CAA_UDINT	udiAbortCode;
/* ----------------------------- */
	CAA_HANDLE	hDriver;
	CAA_HANDLE	hReceiver;
	CAA_UDINT	udiRxId;
	CAA_UDINT	udiTxId;
	CAA_UDINT	udiSeqCnt;
	CAA_UDINT	udiCurPos;
	CAA_TICK	tkCurrentTick;
	CAA_BOOL	xTimeout;
	CAA_USINT	usiBlkSize;
	CAA_UINT	uiSDOState;
	CAA_TICK	tkTimeout;
/* ----------------------------- */
	CAA_COUNT	ctTimeout; /* Timeout in us */
} SDO_WRITE2;

typedef struct SDOChannelLimitParameter
{
	CAA_PVOID pNodeSet;
	CAA_UINT uiNoLimitationNodeID;
	CAA_USINT usiMaxActive;
}SDOChannelParameter;

#endif /* _CLIENT_SDO_H_ */
#endif /* CAA_CL2 */
#endif /* CAALib */
