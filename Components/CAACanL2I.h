/*****************************************************************************
*
*	Copyright:	© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		CL2I.h
*	Version:		2.4
*	Purpose:		Interface to the CAA CAN Low Level (Imp Dependend)
*
******************************************************************************/

#ifndef __CAA_CL2I_H__
#define __CAA_CL2I_H__

#ifdef CAALib

#include "CAADefines.h"

#ifdef CAA_CL2

#include "CAATypes.h"

typedef CAA_BYTE	CL2I_BYTE;		/*  8-bit (always)  IEC: USINT */
typedef CAA_WORD	CL2I_WORD;		/* 16-bit (always)  IEC: UINT  */
typedef CAA_DWORD	CL2I_DWORD;		/* 32-bit (always)  IEC: UDINT */

typedef CAA_UDINT	CL2I_COBID;
typedef CAA_BYTE	CL2I_DATA[8];

#define CL2I_GetCOBID_Id(a) ((CL2I_COBID)(a.D & 0x1FFFFFFF))
#define CL2I_GetCOBID_EID(a) ((CAA_BOOL)((a.D >> 29) & 0x1))
#define CL2I_GetCOBID_RTR(a) ((CAA_BOOL)((a.D >> 30) & 0x1))
#define CL2I_GetCOBID_TX(a) ((CAA_BOOL)((a.D >> 31) & 0x1))

#define CL2I_SetCOBID_Id(a, b)   (a.D = (a.D & ~0x1FFFFFFF) | ((CL2I_DWORD)(b) & 0x1FFFFFFF))
#define CL2I_SetCOBID_EID(a, b)  (a.D = (a.D & ~0x20000000) | ((CL2I_DWORD)(b)<<29 & 0x20000000))
#define CL2I_SetCOBID_RTR(a, b)  (a.D = (a.D & ~0x40000000) | ((CL2I_DWORD)(b)<<30 & 0x40000000))
#define CL2I_SetCOBID_TX(a, b)   (a.D = (a.D & ~0x80000000) | ((CL2I_DWORD)(b)<<31 & 0x80000000))

#define CL2I_GetBlockMask(p) ((CL2I_COBID)(((CL2I_BLOCK*)(p))->cobId.D))
#define CL2I_GetBlockId(p)   ((CL2I_COBID)((((CL2I_BLOCK*)(p))->cobId.D) & 0x1FFFFFFF))
#define CL2I_GetBlockEID(p)  ((CAA_BOOL)((((CL2I_BLOCK*)(p))->cobId.D)>>29 & 0x1))
#define CL2I_GetBlockRTR(p)  ((CAA_BOOL)((((CL2I_BLOCK*)(p))->cobId.D)>>30 & 0x1))
#define CL2I_GetBlockTX(p)   ((CAA_BOOL)((((CL2I_BLOCK*)(p))->cobId.D)>>31 & 0x1))
#define CL2I_GetBlockDLC(p)  ((CL2I_BYTE)((((CL2I_BLOCK*)(p))->byLen.B) & 0xF))
#define CL2I_GetBlockPrio(p) ((CL2I_BYTE)((((CL2I_BLOCK*)(p))->byLen.B)>>4 & 0x7))
#define CL2I_GetBlockSync(p) ((CL2I_BOOL)((((CL2I_BLOCK*)(p))->byLen.B)>>7 & 0x1))
#define CL2I_GetBlockDataPointer(p) ((CL2I_DATA*)((CL2I_BLOCK*)(p))->byData)
#define CL2I_GetBlockTSP(p)  ((CL2I_DWORD)(((CL2I_BLOCK*)(p))->dwTSP))
#define CL2I_GetBlockNet(p)  ((CL2I_BYTE)(((CL2I_BLOCK*)(p))->byNet))

#define CL2I_SetBlockMask(p, i) (((CL2I_BLOCK*)(p))->cobId.D = (CL2I_COBID)(i))
#define CL2I_SetBlockId(p, i)   (((CL2I_BLOCK*)(p))->cobId.D = (((CL2I_BLOCK*)(p))->cobId.D & ~0x1FFFFFFF) | ((CL2I_DWORD)(i) & 0x1FFFFFFF))
#define CL2I_SetBlockEID(p, b)  (((CL2I_BLOCK*)(p))->cobId.D = (((CL2I_BLOCK*)(p))->cobId.D & ~0x20000000) | ((CL2I_DWORD)(b)<<29 & 0x20000000))
#define CL2I_SetBlockRTR(p, b)  (((CL2I_BLOCK*)(p))->cobId.D = (((CL2I_BLOCK*)(p))->cobId.D & ~0x40000000) | ((CL2I_DWORD)(b)<<30 & 0x40000000))
#define CL2I_SetBlockTX(p, b)   (((CL2I_BLOCK*)(p))->cobId.D = (((CL2I_BLOCK*)(p))->cobId.D & ~0x80000000) | ((CL2I_DWORD)(b)<<31 & 0x80000000))
#define CL2I_SetBlockDLC(p, l)  (((CL2I_BLOCK*)(p))->byLen.B = (CL2I_BYTE)((((CL2I_BLOCK*)(p))->byLen.B & ~0x0F) | ((CL2I_BYTE)(l) & 0x0f)))
#define CL2I_SetBlockPrio(p, n) (((CL2I_BLOCK*)(p))->byLen.B = (CL2I_BYTE)((((CL2I_BLOCK*)(p))->byLen.B & ~0x70) | ((CL2I_BYTE)(n)<<4 & 0x70)))
#define CL2I_SetBlockSync(p, s) (((CL2I_BLOCK*)(p))->byLen.B = (CL2I_BYTE)((((CL2I_BLOCK*)(p))->byLen.B & ~0x80) | ((CL2I_BYTE)(s)<<7 & 0x80)))
#define CL2I_SetBlockTSP(p, n) (((CL2I_BLOCK*)(p))->dwTSP = (CL2I_DWORD)(n))
#define CL2I_SetBlockNet(p, n) (((CL2I_BLOCK*)(p))->byNet = (CL2I_BYTE)(n))

#define CL2I_GetMessagesSend(i) ((CL2I_DWORD)(((CL2I_INFO*)(i))->ctMessagesSend))
#define CL2I_GetMessagesReceived(i) ((CL2I_DWORD)(((CL2I_INFO*)(i))->ctMessagesReceived))
#define CL2I_GetMessagesLost(i) ((CL2I_DWORD)(((CL2I_INFO*)(i))->ctDataOverruns))
#define CL2I_GetRxErrors(i) ((CL2I_DWORD)(((CL2I_INFO*)(i))->ctRxErrors))
#define CL2I_GetTxErrors(i) ((CL2I_DWORD)(((CL2I_INFO*)(i))->ctTxErrors))           
#define CL2I_GetBusState(i) ((CL2I_BYTE)(((CL2I_INFO*)(i))->byBusState))           
#define CL2I_GetBusLoad(i) ((CL2I_BYTE)(((CL2I_INFO*)(i))->usiBusLoad))           
#define CL2I_GetBusAlarm(i) ((CL2I_WORD)(((CL2I_INFO*)(i))->uiBusAlarm))           

typedef union cl2i_cobid_tag
{
#ifndef RTS_16BIT
	struct
	{
#if CAA_BIG_ENDIAN
		CL2I_DWORD	TX	: 1;	/* 0 => Rx / 1 => Tx */
		CL2I_DWORD	RTR	: 1;	/* Remote Frame */
		CL2I_DWORD	EID	: 1; 	/* 0 => 11Bit Frame / 1 => 29Bit Frame */
		CL2I_DWORD	ID	: 29;	/* Identifier */
#else
		CL2I_DWORD	ID	: 29;	/* Identifier */
		CL2I_DWORD	EID	: 1; 	/* 0 => 11Bit Frame / 1 => 29Bit Frame */
		CL2I_DWORD	RTR	: 1;	/* Remote Frame */
		CL2I_DWORD	TX	: 1;	/* 0 => Rx / 1 => Tx */
#endif
	} X; /* do not use! This doesn't work on 16 bit plattforms. */
#endif
	CL2I_BYTE B[4];
	CL2I_WORD W[2];
	CL2I_DWORD D;
} CL2I_ID;

typedef union cmd_len_tag
{
#ifndef RTS_16BIT
	struct
	{
#if CAA_BIG_ENDIAN
		CL2I_BYTE	SYNC	: 1;	/* xEnableSyncWindow */
		CL2I_BYTE	PRIO	: 3;	/* Priority of the Message [0-7]*/
		CL2I_BYTE	DLC		: 4;	/* DLC Length of Frame */
#else
		CL2I_BYTE	DLC		: 4;	/* DLC Length of Frame */
		CL2I_BYTE	PRIO	: 3;	/* Priority of the Message [0-7]*/
		CL2I_BYTE	SYNC	: 1;	/* xEnableSyncWindow */
#endif
	} X;
#endif
	CL2I_BYTE B;
} CL2I_LEN;

typedef struct cl2i_block_tag
{
	CL2I_ID		cobId;
	CL2I_DATA	byData;
	CL2I_DWORD 	dwTSP;
	CL2I_LEN	byLen;
	CL2I_BYTE 	byNet;
} CL2I_BLOCK;

typedef struct cl2i_info_tag
{
	CL2I_DWORD	ctMessagesSend;
	CL2I_DWORD	ctMessagesReceived;
	CL2I_DWORD	ctRxErrors;
	CL2I_DWORD	ctTxErrors;
	CL2I_DWORD	ctDataOverruns;
	CL2I_WORD	uiBusAlarm;
	CL2I_BYTE	byBusState;
	CL2I_BYTE	usiBusLoad;
} CL2I_INFO;

typedef struct cl2i_arrayrecv_entry_tag
{
	CL2I_ID		cobId;
	CAA_HANDLE	hHandle;
} CL2I_ARRAYRECV_ENTRY;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* CAA_CL2 */
#endif /* CAALib */
#endif /* __CAA_CL2I_H__ */
