/*****************************************************************************
*
*	Copyright:	© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		CAACanMiniDriver.h (cmd)
*	Version:		2.4
*	Purpose:		Interface to the CAA SJA CANbus Mini Driver.
*
******************************************************************************/
#ifdef CAALib

#include "CAADefines.h"

#ifdef CAA_CL2

#ifndef _SJACanMiniDriver_H_
#define _SJACanMiniDriver_H_

#include "CAACanL2I.h"
#include "CAACanMiniDriver.h"

#if 0
typedef union sja_fri_tag
{
	struct
	{
		CL2I_BYTE FF	: 1;	// 7 Frame Format
		CL2I_BYTE RTR	: 1;	// 6 Remote Transmission Request
		CL2I_BYTE DMY	: 2;	// 5
		CL2I_BYTE DLC	: 4;	// 3 Data Length Code
	} X;
	CL2I_BYTE B;
} SJA_FRI;

typedef struct sja_sff_tag
{
	CL2I_BYTE ID[2];			// 17 Identifier
	CL2I_BYTE DATA[8];		// 19 Data
} SJA_SFF;

typedef struct sja_eff_tag
{
	CL2I_BYTE ID[4];			// 17 Identifier
	CL2I_BYTE DATA[8];		// 21 Data
} SJA_EFF;

typedef struct sja_frd_tag
{
	SJA_FRI FRI;			// 16 Frame Information
	union
	{
		SJA_SFF S;		// 17 Standard Frame Data
		SJA_EFF E;		// 17 Extended Frame Data
	} FR;
} SJA_FRD;

typedef union sja_mod_tag
{
	struct
	{
		CL2I_BYTE DMY	: 3;
		CL2I_BYTE SLM	: 1;	// 4 Sleep Mode
		CL2I_BYTE AFM 	: 1;	// 3 Acceptance Filter Mode
		CL2I_BYTE STM	: 1;	// 2 Self Test Mode
		CL2I_BYTE LOM	: 1;	// 1 Listen Only Mode
		CL2I_BYTE RM	: 1;	// 0 Reset Mode
	} X;
	CL2I_BYTE B;
} SJA_MOD;

typedef union sja_cmr_tag
{
	struct
	{
		CL2I_BYTE DMY	: 3;
		CL2I_BYTE SRR	: 1;	// 4 Self Reception Request
		CL2I_BYTE CDO	: 1;	// 3 Clear Data Overrun
		CL2I_BYTE RRB	: 1;	// 2 Release Receive Buffer
		CL2I_BYTE AT	: 1;	// 1 Abort Transmision
		CL2I_BYTE TR	: 1;	// 0 Transmission Request
	} X;
	CL2I_BYTE B;
} SJA_CMR;

typedef union sja_sr_tag
{
	struct
	{
		CL2I_BYTE BS	: 1; 	// 7 Bus Status
		CL2I_BYTE ES	: 1;	// 6 Error Status
		CL2I_BYTE TS	: 1;	// 5 Transmit Status
		CL2I_BYTE RS	: 1;	// 4 Receive Status
		CL2I_BYTE TCS	: 1;	// 3 Transmit Complete Status
		CL2I_BYTE TBS	: 1;	// 2 Transmit Buffer Status
		CL2I_BYTE DOS	: 1;	// 1 Data Overrun Status
		CL2I_BYTE RBS	: 1;	// 0 Receive Buffer Status
	} X;
	CL2I_BYTE B;
} SJA_SR;

typedef union sja_ir_tag
{
	struct
	{
		CL2I_BYTE BEI	: 1;	// 7 Bus Error Interrupt
		CL2I_BYTE ALI	: 1;	// 6 Arbitration Lost Interrpt
		CL2I_BYTE EPI	: 1; 	// 5 Error Passive Interrupt
		CL2I_BYTE WUI	: 1;	// 4 Wake-Up Interrupt
		CL2I_BYTE DOI	: 1;	// 3 Data Overrun Interrupt
		CL2I_BYTE EI	: 1;	// 2 Error Warning Interrupt
		CL2I_BYTE TI	: 1; 	// 1 Transmit Interrupt
		CL2I_BYTE RI	: 1;	// 0 Receive Interrupt
	} X;
	CL2I_BYTE B;
} SJA_IR;

typedef union sja_ier_tag
{
	struct
	{
		CL2I_BYTE BEIE	: 1;	// 7 Bus Error Interrupt Enable
		CL2I_BYTE ALIE	: 1;	// 6 Arbitration Lost Interrupt Enable
		CL2I_BYTE EPIE	: 1; 	// 5 Error Passive Interrupt Enable
		CL2I_BYTE WUIE	: 1;	// 4 Wake-Up Interrupt Enable
		CL2I_BYTE DOIE	: 1;	// 3 Data Overrun Interrupt Enable
		CL2I_BYTE EIE	: 1;	// 2 Error Warning Interrupt Enable
		CL2I_BYTE TIE	: 1; 	// 1 Transmit Interrupt Enable
		CL2I_BYTE RIE	: 1;	// 0 Receive Interrupt  Enable
	} X;
	CL2I_BYTE B;
} SJA_IRE;

typedef union sja_ocr_tag
{
	struct
	{
		CL2I_BYTE OCTP1	: 1;	// 7 Output Control Transistor P1
		CL2I_BYTE OCTN1	: 1;	// 6 Output Control Transistor N1
		CL2I_BYTE OCPOL1	: 1; 	// 5 Output Control Plarity 1
		CL2I_BYTE OCTP0	: 1;	// 4 Output Control Transistor P0
		CL2I_BYTE OCTN0	: 1;	// 3 Output Control Transistor N0
		CL2I_BYTE OCPOL0	: 1; 	// 2 Output Control Plarity 0
		CL2I_BYTE OCMODE1	: 1;	// 1 Output Control Mode 1
		CL2I_BYTE OCMODE0	: 1;	// 0 Output Control Mode 0
	} X;
	CL2I_BYTE B;
} SJA_OCR;

typedef union sja_rtr_tag
{
	struct
	{
		CL2I_BYTE	ACR[4]; // 16 Acceptance Code Register
		CL2I_BYTE	AMR[4];	// 20 Acceptance Mask Register
	} ACC;
	SJA_FRD	FRD;		// 16 Frame Data
} SJA_RTR;

typedef union sja_cdr_tag
{
	struct
	{
		CL2I_BYTE CANMOD	: 1;	// 7 CAN mode 1=Pelican
		CL2I_BYTE CBP		: 1;	// 6 CAN Iput Bypass
		CL2I_BYTE RXINTEN	: 1;	// 5 Receive Interrupt Out Enable
		CL2I_BYTE DMY		: 1;
		CL2I_BYTE CLKOFF	: 1;	// 3 Clock Off
		CL2I_BYTE CD		: 3;	// 2 Clock Divider
	} X;
	CL2I_BYTE B;
} SJA_CDR;

typedef struct sja_chip_tag
{
	volatile SJA_MOD	MOD;		//  0 Mode
	volatile SJA_CMR	CMR;		//  1 Command
	volatile SJA_SR	SR;		//  2 Status
	volatile SJA_IR	IR;		//  3 Interrupt
	volatile SJA_IRE	IRE;		//  4 Interrupt Enable
	volatile CL2I_BYTE	dmy1;		//  5
	volatile SJA_BTR0	BTR0;		//  6 Bus timing 0
	volatile SJA_BTR1 BTR1;		//  7 Bus timing 1
	volatile SJA_OCR 	OCR;		//  8 Output Control
	volatile CL2I_BYTE	test;		//  9
	volatile CL2I_BYTE	dmy2;		// 10
	volatile CL2I_BYTE	ALC;		// 11 Arbitration Lost Capture
	volatile CL2I_BYTE	ECC;		// 12 Error Code Capture
	volatile CL2I_BYTE	EWLR;		// 13 Error Warning Limit Register
	volatile CL2I_BYTE	RXERR;	// 14 Receive Error Counter
	volatile CL2I_BYTE	TXERR;	// 15 Transmit Error Counter
	volatile SJA_RTR	RTR;		// 16 Rx/Tx Register, Acceptance Codes
	volatile CL2I_BYTE	RMC;		// 29 RX Message Counter
	volatile CL2I_BYTE	RBSA;		// 30 RX Buffer Start Address
	volatile SJA_CDR	CDR;		// 31 Clock Divider Register
//	CL2I_BYTE	RXF[64];	// 32 RX FIFO
//	CL2I_BYTE	TXB[13];	// 96 TX Buffer
} SJA_CHIP;

#define SJA_ADDR_0 ((SJA_CHIP*)0x60000000UL)
#define SJA_ADDR_1 ((SJA_CHIP*)0x60000100UL)

#endif /*if 0*/

/*All the definitions for SJA1000*/
#define SJA_CR_MODE     0
#define SJA_CMD		    1
#define SJA_SR			2    
#define SJA_IR          3
#define SJA_IRen        4
#define SJA_resv5       5
#define SJA_BTR0        6
#define SJA_BTR1        7
#define SJA_OC          8 
#define SJA_test        9
#define SJA_resv10      10 /*Bit7..0 : ID.10..3 */
#define SJA_ALC		    11 /*Arbitration lost capture*/
#define SJA_ERCC		12 /*Error code capture.*/
#define SJA_ERWL		13 /*Error warning limit.*/
#define SJA_RX_ERRCTR   14 
#define SJA_TX_ERRCTR   15
#define SJA_RX_FRAME_INFO	16
#define SJA_TX_FRAME_INFO	16

/*Standard frame format*/
#define SJA_SFF_RXID1	17
#define SJA_SFF_RXID2	18
#define SJA_SFF_RXDATA1	19
#define SJA_SFF_RXDATA2	20
#define SJA_SFF_RXDATA3	21
#define SJA_SFF_RXDATA4	22
#define SJA_SFF_RXDATA5	23
#define SJA_SFF_RXDATA6	24
#define SJA_SFF_RXDATA7	25
#define SJA_SFF_RXDATA8	26

#define SJA_SFF_TXID1	17
#define SJA_SFF_TXID2	18
#define SJA_SFF_TXDATA1	19
#define SJA_SFF_TXDATA2	20
#define SJA_SFF_TXDATA3	21
#define SJA_SFF_TXDATA4	22
#define SJA_SFF_TXDATA5	23
#define SJA_SFF_TXDATA6	24
#define SJA_SFF_TXDATA7	25
#define SJA_SFF_TXDATA8	26

/*Extended frame format (29bit)*/
#define SJA_EFF_RXID1	17
#define SJA_EFF_RXID2	18
#define SJA_EFF_RXID3	19
#define SJA_EFF_RXID4	20
#define SJA_EFF_RXDATA1	21
#define SJA_EFF_RXDATA2	22
#define SJA_EFF_RXDATA3	23
#define SJA_EFF_RXDATA4	24
#define SJA_EFF_RXDATA5	25
#define SJA_EFF_RXDATA6	26
#define SJA_EFF_RXDATA7	27
#define SJA_EFF_RXDATA8	28

#define SJA_EFF_TXID1	17
#define SJA_EFF_TXID2	18
#define SJA_EFF_TXID3	19
#define SJA_EFF_TXID4	20
#define SJA_EFF_TXDATA1	21
#define SJA_EFF_TXDATA2	22
#define SJA_EFF_TXDATA3	23
#define SJA_EFF_TXDATA4	24
#define SJA_EFF_TXDATA5	25
#define SJA_EFF_TXDATA6	26
#define SJA_EFF_TXDATA7	27
#define SJA_EFF_TXDATA8	28

#define SJA_RX_MSG_CTR	29
#define SJA_RXBUFF_START	30
#define SJA_CLK_DIV		31 /*This is the register to switch between PeliCAN and Basic.*/

/*The acceptance codes are only valid in reset mode.*/
#define SJA_ACC0	16
#define SJA_ACC1	17
#define SJA_ACC2	18
#define SJA_ACC3	19
/*The acceptance masks are only valid in reset mode.*/
#define SJA_ACCM0	20
#define SJA_ACCM1	21
#define SJA_ACCM2	22
#define SJA_ACCM3	23

/*The commands for the controller.*/
#define CMD_TXREQUEST   1
#define CMD_TXABORT     2
#define CMD_RELRCVBUFF  4
#define CMD_CLEARDATAOVR 8
#define CMD_SLEEPMODE   16

/*The interrupt bits in the interrupt mask.*/
/*Bit7 Bus Error Interrupt Enable. */
#define SJA_INT_BIT_BUSERROR		0x80
/*Bit6 Arbitration Lost Interrupt Enable. */
#define SJA_INT_BIT_ARBLOST			0x40
/*Bit5 Error Passive Interrupt Enable. */
#define SJA_INT_BIT_ERRPASSIVE		0x20
/*Bit4 Wake-Up Interrupt Enable. */
#define SJA_INT_BIT_WAKEUP			0x10
/*Bit3 Data Overrun Interrupt Enable. */
#define SJA_INT_BIT_DATAOVERRUN		0x08
/*Bit2 Error Warning Interrupt Enable. */
#define SJA_INT_BIT_ERRWARNING		0x04
/*Bit1 Transmit Interrupt Enable. */
#define SJA_INT_BIT_TXINT			0x02
/*Bit0 Receive Interrupt  Enable. */
#define SJA_INT_BIT_RXINT			0x01

/*The status registers of the SJA.*/
/*Bit7 Bus Status. */
#define SJA_STAT_BS			0x80
/*Bit6 Error Status. */
#define SJA_STAT_ERR		0x40
/*Bit5 Transmit Status. */
#define SJA_STAT_TX			0x20
/*Bit4 Receive Status. */
#define SJA_STAT_RX			0x10
/*Bit3 Transmit Complete Status. */
#define SJA_STAT_TXCOMPLETE	0x08
/*Bit2 Transmit Buffer Status. */
#define SJA_STAT_TXBUFFSTAT	0x04
/*Bit1 Data Overrun Status. */
#define SJA_STAT_DATAOVR	0x02
/*Bit0 Receive Buffer Status. */
#define SJA_STAT_RXBUFFSTAT	0x01

/*The frame information bits.*/
#define SJA_FINFO_FFEXT	0x80
#define SJA_FINFO_RTR	0x40
#define SJA_FINFO_DLC	0x0F


typedef unsigned char SJA_CHIP;

#endif /* _SJACanMiniDriver_H_ */
#endif /* CAA_CL2 */
#endif /* CAALib */
