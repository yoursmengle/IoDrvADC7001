/*****************************************************************************
*
*	Copyright:	© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		CAACanDmyDrv.c
*	Version:		2.4
*	Purpose:		Implementaion of CAA SJA Can Mini Driver
*
******************************************************************************/

#include "CAADefines.h"
/********** Includes *********/
#include "CmpSJACanDrvDep.h"

USEEXTERN_STMT

#define ASEM_CAN1_GREEN_LED		0x04000000							/* GPIO 8 */
#define ASEM_CAN1_RED_LED		0x00800000							/* GPIO 7 */
#define ASEM_CAN2_GREEN_LED		0x00100000							/* GPIO 6 */
#define ASEM_CAN2_RED_LED		0x00020000							/* GPIO 5 */

unsigned char SjaWriteRegister(int iDev, unsigned char* pucBase, unsigned long ulRegOffs, unsigned char c);
void HUGEPTR CDECL SJA_Interrupt_Handler(RTS_UINTPTR ulAdditionalInfo);

static CAA_ERROR CMD_Setup(CL2I_BYTE byNet);
static CAA_ERROR CMD_Init(CL2I_BYTE byNet, CL2I_WORD wBaudrate);
static CAA_BOOL  CMD_Send(CL2I_BYTE byNet, CAA_HANDLE hBlock, CL2I_BYTE byPrio, CAA_ERROR* peError);
static CAA_BOOL  CMD_Receive(CL2I_BYTE byNet, CAA_HANDLE hBlock, CAA_ERROR* peError);
static CAA_ERROR CMD_GetInfo(CL2I_BYTE byNet, CMD_INFO* pInfo);
static CAA_ERROR CMD_Dispose(CL2I_BYTE byNet);
static CAA_ERROR CMD_Identify(CL2I_BYTE byNet, CL2I_BYTE byCount);
static CAA_HANDLE CMD_SetBlock(CL2I_BYTE byNet, CL2I_BYTE byIndex, CAA_HANDLE hBlock, CAA_ERROR* peError);
static CAA_ERROR CMD_SetCycle(CL2I_BYTE byNet, CL2I_BYTE byIndex, CL2I_DWORD dwCycle);
static CAA_ERROR CMD_SetMask(CL2I_BYTE byNet, CL2I_BYTE byIndex, CL2I_DWORD dwValue, CL2I_DWORD dwMask);
static CAA_ERROR CMD_ResetAlarm(CL2I_BYTE byNet);
static CAA_ERROR CMD_SetStatus(CL2I_BYTE byNet, CL2I_BYTE byIndicator);

static CMD_CMDRV cmdInterface[] =
{
	{
		CMD_Setup,
		CMD_Init,
		CMD_Send,
		CMD_Receive,
		CMD_GetInfo,
		CMD_Dispose,
		CMD_Identify,
		CMD_SetBlock,
		CMD_SetCycle,
		CMD_SetMask,
		CMD_ResetAlarm,
		CMD_SetStatus
	}
};

#define SJA_NNET ((unsigned char)5)
#define SJA_NDRIVER  SJA_NNET

typedef union sja_btr0_tag
{
	struct
	{
		CL2I_BYTE SJW	: 2;	/* 7 Synchronization Jump Width*/
		CL2I_BYTE BRP	: 6;	/* 5 Baud Rate Prescaler*/
	} X;
	CL2I_BYTE B;
} SJA_BTR0tag;

typedef union sja_bt1_tag
{
	struct
	{
		CL2I_BYTE SAM		: 1;	/* 7 Sampling*/
		CL2I_BYTE TSEG2	: 3;	/* 6 Time Segment 2*/
		CL2I_BYTE TSEG1	: 4;	/* 3 Time Segment 1*/
	} X;
	CL2I_BYTE B;
} SJA_BTR1tag;

typedef struct sja_btr_tag
{
	unsigned char BTR0;
	unsigned char BTR1;
} SJA_BTR;

/*#define BTR(SJW,BRP,TS1,TS2) {{{(CL2I_BYTE)((SJW)-1), (CL2I_BYTE)((BRP)-1)}}, {{(CL2I_BYTE)0, (CL2I_BYTE)((TS2)-1), (CL2I_BYTE)((TS1)-1)}}}*/

static SJA_BTR btrv24[]={ /* 	SJW	BRP	TS1	TS2 for 24MHz CLK */
									{0x3b,0x2f}, /*   10 kBit 0 */
									{0x67,0x1b}, /*   20 kBit 1 */
									{0xe,0x1c}, /*   50 kBit 2 */
									{7,0x1b}, /*  100 kBit 3 */
									{5,0x1c}, /*  125 kBit 4 */
									{3,0x18}, /*  250 kBit 5 */
									{1,0x18}, /*  500 kBit 6 */
									{0x40,0x1b}, /*  800 kBit 7 */
									{0,0x18}  /* 1000 kBit 8 */
							};

static SJA_BTR btrv16[]={ 
									{0x31,0x1c}, /*   10 kBit 0 */
									{0x18,0x1c}, /*   20 kBit 1 */
									{9,0x1c}, /*   50 kBit 2 */
									{4,0x1c}, /*  100 kBit 3 */
									{3,0x1c}, /*  125 kBit 4 */
									{1,0x1c}, /*  250 kBit 5 */
									{0,0x1c}, /*  500 kBit 6 */
									{0,0x16}, /*  800 kBit 7 */
									{0,0x14}  /* 1000 kBit 8 */
		};

#define SJA_NBAUD (sizeof(btrv)/sizeof(SJA_BTR))

static DEV_INFO s_Can[SJA_NNET]; /*This has to be filled by a setup-routine.*/
static CL2I_INFO* s_pInfo[SJA_NNET];

static CMD_INFO cmdInfo;

static CL2I_BYTE s_byDriver[CL2_NNET];
static CL2I_BYTE s_byNet[SJA_NDRIVER];
static CAA_HANDLE s_hTxBlock[SJA_NDRIVER];

static int CheckForSJAAvailableHere(int iDev, unsigned char* pController);

void CmpSjaMpdSetRetainEvent(unsigned long ulBaseAddress, unsigned long ulSize);
RTS_I32 CmpSjaDisableChipTest(void);

/*unsigned long g_DebugSent;*/
/*unsigned long g_DebugTxInts;*/
/*unsigned long g_DebugErrI;*/
/*unsigned long g_DebugPassI;*/
/*unsigned long g_DebugWarnI;*/
unsigned long g_MBMFailed;
void SjaInitChipDescs(void)
{
	memset(s_Can,0,sizeof(s_Can));
	memset(s_pInfo,0,sizeof(s_pInfo));
	memset(&cmdInfo, 0, sizeof(cmdInfo));
	cmdInfo.byMaxPrio = 1;
}

int SjaAddChipDescription(DEV_INFO* pDesc)
{
	int i=0;

	while(i < SJA_NNET && s_Can[i].ulPhysAddr != 0)
	{
		i++;
	}

	if(i >= SJA_NNET)
		return -1; /*Could not add the chip: no free place in array found.*/

	/*Now the index in the array of controllers is valid.*/
	/*Copy the device to the array and do all the things to initialize it.*/
	memcpy(&s_Can[i],pDesc,sizeof(DEV_INFO));
	CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0x1234, "CmpSJACanDrv: AddChipDesc: VEN:%x,Dev:%x,SubVen:%x,SubDev:%x",pDesc->usVendorID,pDesc->usDeviceID,pDesc->usSubVendorID,pDesc->usSubDeviceID);

	/*If the chip is memory mapped, map it now.*/
	if(!s_Can[i].bMemoryMapped)
		s_Can[i].pCanRegs = (unsigned char*)(s_Can[i].ulPhysAddr);
	
	return i; /*Could not add the chip.*/
}

void SjaTurnOffLEDs(CL2I_BYTE byNet)
{
	if(s_Can[s_byDriver[byNet]].ulPhysAddr == 0)
		return;
	
	if (s_Can[s_byDriver[byNet]].usVendorID == VENDOR_ID && 
		s_Can[s_byDriver[byNet]].usDeviceID == DEVICE_ID_PCI_9030 &&
		s_Can[s_byDriver[byNet]].usSubVendorID == PCI_JANZ_SUBVENDOR_ID &&
		(s_Can[s_byDriver[byNet]].usSubDeviceID == PCI_JANZ_SUBSYSTEM_ID ||
		s_Can[s_byDriver[byNet]].usSubDeviceID == PCI_JANZ_SUBSYSTEM_ID_1_CHANNEL))
	{
		SjaWriteRegister(s_byDriver[byNet], s_Can[s_byDriver[byNet]].pCanRegs, 0x102, 0);
	}
	else if(s_Can[s_byDriver[byNet]].usVendorID == VENDOR_ID && 
			s_Can[s_byDriver[byNet]].usDeviceID == DEVICE_ID_PCI_9030 &&
			s_Can[s_byDriver[byNet]].usSubVendorID == SUBVENDOR_ID_ASEM &&
			(s_Can[s_byDriver[byNet]].usSubDeviceID == CAN_SUB_SYSTEM_ID_CONF1 ||
			s_Can[s_byDriver[byNet]].usSubDeviceID == CAN_SUB_SYSTEM_ID_CONF2 ||
			s_Can[s_byDriver[byNet]].usSubDeviceID == CAN_SUB_SYSTEM_ID_CONF3))
	{ /*We have an Asem card here.*/
		unsigned long* pulLed = (unsigned long*) (s_Can[s_byDriver[byNet]].pHelpCtrl + 0x54);
		
		*pulLed &= ~ASEM_CAN1_GREEN_LED;
		*pulLed &= ~ASEM_CAN1_RED_LED;
		*pulLed &= ~ASEM_CAN2_GREEN_LED;
		*pulLed &= ~ASEM_CAN2_RED_LED;
	}	
}

static CAA_BOOL LedGetState(CAA_BOOL xGreen, unsigned char usiState, unsigned long ulPhase)
{
	switch(usiState)
	{
		case 0x00 : /* off */
		{
			return CAA_FALSE;
		}
		case 0x01 : /* on */
		{
			return CAA_TRUE;
		}
		case 0x02 : /* flickering */
		{
			return (CAA_BOOL)((ulPhase % 2) ^ xGreen);
		}
		case 0x03 : /* blinking */
		{
			return ((CAA_BOOL)((ulPhase % 8) < 4) ^ xGreen);
		}
		case 0x04 : /* single flash */
		{
			return ((ulPhase - (xGreen ? 4 : 0)) % 24) < 4;
		}
		case 0x05 : /* double flash */
		{
			unsigned long udiPhaseTmp = (ulPhase - (xGreen ? 4 : 0)) % 32; 
			return ((udiPhaseTmp < 4) || (udiPhaseTmp >= 8 && udiPhaseTmp < 12));
		}
		case 0x06 : /* triple flash */
		{
			unsigned long udiPhaseTmp = (ulPhase - (xGreen ? 4 : 0)) % 40; 
			return ((udiPhaseTmp < 4) || (udiPhaseTmp >= 8 && udiPhaseTmp < 12) || (udiPhaseTmp >= 16 && udiPhaseTmp < 20));
		}
		case 0x07 : /* quadruple flash */
		{
			unsigned long udiPhaseTmp = (ulPhase - (xGreen ? 4 : 0)) % 48; 
			return ((udiPhaseTmp < 4) || (udiPhaseTmp >= 8 && udiPhaseTmp < 12) || (udiPhaseTmp >= 16 && udiPhaseTmp < 20) || (udiPhaseTmp >= 24 && udiPhaseTmp < 28));
		}
		default:
		{
			return CAA_FALSE;
		}
	}
}

void SjaHandleLEDs(unsigned long* pulPhase)
{
	if (((cmdInfo.bySupport & CMD_SUPPORT_STATUSLED) == CMD_SUPPORT_STATUSLED) && (CHK_SysTimeGetMs))
	{
		RTS_UI32 ulMs = CAL_SysTimeGetMs();
		int iCtrl;

		for(iCtrl = 0; iCtrl < SJA_NNET; iCtrl++)
		{
			if(s_Can[iCtrl].ulPhysAddr == 0)
				continue;
	
			if ((ulMs - s_Can[iCtrl].ulLEDTimestamp) > 50)	/*Refresh LED state every 50ms*/
			{
				unsigned char usiIndicator = s_Can[iCtrl].byIndicator;
				unsigned char usiRedState = usiIndicator & 0x0f;
				unsigned char usiGreenState = (usiIndicator & 0xf0) >> 4;
				unsigned char xRedLed;
				unsigned char xGreenLed;
				
				s_Can[iCtrl].ulLEDTimestamp = ulMs;
				*pulPhase += 1;

				xRedLed = LedGetState(CAA_FALSE, usiRedState, *pulPhase);
				xGreenLed = LedGetState(CAA_TRUE, usiGreenState, *pulPhase);

				if (s_Can[iCtrl].usVendorID == VENDOR_ID && 
					s_Can[iCtrl].usDeviceID == DEVICE_ID_PCI_9030 &&
					s_Can[iCtrl].usSubVendorID == PCI_JANZ_SUBVENDOR_ID &&
					(s_Can[iCtrl].usSubDeviceID == PCI_JANZ_SUBSYSTEM_ID ||
					s_Can[iCtrl].usSubDeviceID == PCI_JANZ_SUBSYSTEM_ID_1_CHANNEL))
				{
					unsigned char ucVal = 0;

					if (xRedLed)
						ucVal += 1;

					if (xGreenLed)
						ucVal += 2;

					SjaWriteRegister(iCtrl, s_Can[iCtrl].pCanRegs, 0x102, ucVal);
				}
				else if(s_Can[iCtrl].usVendorID == VENDOR_ID && 
						s_Can[iCtrl].usDeviceID == DEVICE_ID_PCI_9030 &&
						s_Can[iCtrl].usSubVendorID == SUBVENDOR_ID_ASEM &&
						(s_Can[iCtrl].usSubDeviceID == CAN_SUB_SYSTEM_ID_CONF1 ||
						s_Can[iCtrl].usSubDeviceID == CAN_SUB_SYSTEM_ID_CONF2 ||
						s_Can[iCtrl].usSubDeviceID == CAN_SUB_SYSTEM_ID_CONF3))
				{ /*We have an Asem card here.*/
					unsigned long *pulLed = (unsigned long*)(s_Can[iCtrl].pHelpCtrl + 0x54);

					if(!s_Can[iCtrl].bIsSecondCtrl)
					{
						if (xRedLed)
							*pulLed = (*pulLed & ~ASEM_CAN1_GREEN_LED) | ASEM_CAN1_RED_LED;
						else
						{
							if (xGreenLed)
								*pulLed = (*pulLed & ~ASEM_CAN1_RED_LED) | ASEM_CAN1_GREEN_LED;
							else
								*pulLed = (*pulLed & ~ASEM_CAN1_RED_LED) & ~ASEM_CAN1_GREEN_LED;
						}
					}
					else
					{
						if (xRedLed)
							*pulLed = (*pulLed & ~ASEM_CAN2_GREEN_LED) | ASEM_CAN2_RED_LED;
						else
						{
							if (xGreenLed)
								*pulLed = (*pulLed & ~ASEM_CAN2_RED_LED) | ASEM_CAN2_GREEN_LED;
							else
								*pulLed = (*pulLed & ~ASEM_CAN2_RED_LED) & ~ASEM_CAN2_GREEN_LED;
						}
					}	 
				}
			}	
		}	
	}
}

void SjaInitAllControllersForUse(void)
{
	/*This function is called after all the configuration is scanned and clear and 
	 does all the things to initialize the HW except the SJA itself.*/
	int iCtrl;
	unsigned short usPciWriteVal;
	unsigned long ulPciWriteVal;
	RTS_SIZE udiSize;
	RTS_RESULT Result;
	unsigned short* pus;
	SYS_INT_DESCRIPTION IntDesc;
	char szShmName[50];
	char szBusnumber[10];

	for(iCtrl = 0; iCtrl < SJA_NNET; iCtrl++)
	{
		if (s_Can[iCtrl].ulPhysAddr == 0)
			continue;
		
		s_Can[iCtrl].hInt = RTS_INVALID_HANDLE;

		/*We have a SJA controller here.*/
		if(s_Can[iCtrl].usVendorID == VENDOR_ID_PEAK && 
			(s_Can[iCtrl].usDeviceID == DEVICE_ID_PEAK || s_Can[iCtrl].usDeviceID == DEVICE_ID_PEAK2 || s_Can[iCtrl].usDeviceID == DEVICE_ID_PEAK3 ||
			s_Can[iCtrl].usDeviceID == DEVICE_ID_PEAK4 || s_Can[iCtrl].usDeviceID == DEVICE_ID_PEAK5 || s_Can[iCtrl].usDeviceID == DEVICE_ID_PEAK6 ||
			s_Can[iCtrl].usDeviceID == DEVICE_ID_PEAK7 || s_Can[iCtrl].usDeviceID == DEVICE_ID_PEAK8))
		{ 
			if(!s_Can[iCtrl].bIsSecondCtrl)
			{
				unsigned long ulTest;

				/*This is the first controller on a peak.*/
				CAL_SysPciReadValue(s_Can[iCtrl].ulBusNr,(unsigned short)s_Can[iCtrl].ulDevice,
									s_Can[iCtrl].ulFunction,0x44,(unsigned char*)&ulTest, sizeof(ulTest));
				usPciWriteVal = 0;
				CAL_SysPciWriteValue(s_Can[iCtrl].ulBusNr,(unsigned short)s_Can[iCtrl].ulDevice,
									s_Can[iCtrl].ulFunction,0x44,(unsigned char*)&usPciWriteVal,2);

				CAL_SysPciReadValue(s_Can[iCtrl].ulBusNr,(unsigned short)s_Can[iCtrl].ulDevice,
									s_Can[iCtrl].ulFunction,0x4,(unsigned char*)&usPciWriteVal, sizeof(usPciWriteVal));
				usPciWriteVal = 2;
				CAL_SysPciWriteValue(s_Can[iCtrl].ulBusNr,(unsigned short)s_Can[iCtrl].ulDevice,
									s_Can[iCtrl].ulFunction,0x4,(unsigned char*)&usPciWriteVal,2);
				
				/*The internal regs of the PSB. We must map this to init the card.*/
				udiSize = 64;
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "InternalRegs_Peak");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);
				s_Can[iCtrl].hShmHelpCtrl = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPysAddrHelp, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmHelpCtrl = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPysAddrHelp, &udiSize, &Result);
				s_Can[iCtrl].pHelpCtrl = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmHelpCtrl, &Result);			
				pus = (unsigned short*)&s_Can[iCtrl].pHelpCtrl[26];
				*pus = 5; /*Set the GPIO1 and 3 to inputs.*/
				if(s_Can[iCtrl].usSubDeviceID > 3)
					s_Can[iCtrl].pHelpCtrl[24] = 0; /*Enable both controller on the card.*/
				else
					s_Can[iCtrl].pHelpCtrl[24] = 4; /*Enable the first controller on the card.*/
				s_Can[iCtrl].pHelpCtrl[31] = 5; /*First activate SW and HW reset.*/
				s_Can[iCtrl].pHelpCtrl[31] = 4; /*Deactivate SW reset only.*/
				pus = (unsigned short*)&s_Can[iCtrl].pHelpCtrl[2];
				*pus = 0; /*Disable interrupts.*/
				s_Can[iCtrl].pHelpCtrl[0] |= 3; /*Clear any pending interrupts.*/

				/*Now map the memory.*/
				udiSize = 128;
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "SJA1000Ctrl");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);
				s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr,  &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr,  &udiSize, &Result);
				s_Can[iCtrl].pCanRegs = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmSja, &Result);			

				IntDesc.BusType = BT_PCI;
				IntDesc.InterruptMode = IM_LevelSensitive; /*IM_Level_Sensitiv as always on the PCI.*/
				IntDesc.busSpecific.pciInterrupt.ulBusNumber = s_Can[iCtrl].ulBusNr;
				IntDesc.busSpecific.pciInterrupt.ulDevciceNumber = s_Can[iCtrl].ulDevice;
				IntDesc.busSpecific.pciInterrupt.ulFunctionNumber = s_Can[iCtrl].ulFunction;
				IntDesc.busSpecific.pciInterrupt.ulIntLine = s_Can[iCtrl].ulIntVec;
				s_Can[iCtrl].hInt = CAL_SysIntOpen(s_Can[iCtrl].ulIntVec, &IntDesc, &Result);
				if(s_Can[iCtrl].hInt != RTS_INVALID_HANDLE)
				{
					Result = CAL_SysIntRegister(s_Can[iCtrl].hInt, SYS_INT_C, SJA_Interrupt_Handler, (RTS_UINTPTR)&s_Can[iCtrl]);
				}
				pus = (unsigned short*)&s_Can[iCtrl].pHelpCtrl[2];
				if(s_Can[iCtrl].usSubDeviceID >= 0x12)
				{
					*pus = 0xc3; /*Enable the interrupts on all 4 controllers.*/
					s_Can[iCtrl].pHelpCtrl[0] |= 0xc3; /*Clear any pending interrupts.*/
				}
				else if(s_Can[iCtrl].usSubDeviceID >= 0x10)
				{
					*pus = 0x43; /*Enable the interrupts on all 3 controllers.*/
					s_Can[iCtrl].pHelpCtrl[0] |= 0x43; /*Clear any pending interrupts.*/
				}
				else if(s_Can[iCtrl].usSubDeviceID > 3)
				{
					*pus = 3; /*Enable the interrupts on both controllers.*/
					s_Can[iCtrl].pHelpCtrl[0] |= 3; /*Clear any pending interrupts.*/
				}
				else
				{
					s_Can[iCtrl].pHelpCtrl[0] |= 2; /*Clear any pending interrupts.*/			
					*pus = 2; /*Enable the interrupts on the first controller.*/
				}
			}
			else
			{ /*For the second controller only do the mapping of the SJA.*/
				/*Now map the memory.*/
				udiSize = 128;
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "SJA1000Ctrl");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);
				s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				s_Can[iCtrl].pCanRegs = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmSja, &Result);			
			}
		}
		else if(s_Can[iCtrl].usVendorID == VENDOR_ID && 
			s_Can[iCtrl].usDeviceID == DEVICE_ID_PCI &&
			s_Can[iCtrl].usSubDeviceID == SUBSYSTEM_ID_IXXAT_PCI04 &&
			s_Can[iCtrl].usSubVendorID == SUBVENDOR_ID_IXXAT_PCI04)
		{
			if(!s_Can[iCtrl].bIsSecondCtrl)
			{
				ulPciWriteVal = 0xffffffff;
				CAL_SysPciWriteValue(s_Can[iCtrl].ulBusNr,s_Can[iCtrl].ulDevice,
									s_Can[iCtrl].ulFunction,0x10,(unsigned char*)&ulPciWriteVal,4);
				ulPciWriteVal = s_Can[iCtrl].ulPysAddrHelp & 0xffffff7f;
				CAL_SysPciWriteValue(s_Can[iCtrl].ulBusNr,s_Can[iCtrl].ulDevice,
									s_Can[iCtrl].ulFunction,0x10,(unsigned char*)&ulPciWriteVal,4);
				
				/*The internal regs of the PSB. We must map this to init the card.*/
				udiSize = 64;
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "InternalRegs_Ixxat");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);
				s_Can[iCtrl].hShmHelpCtrl = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPysAddrHelp, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmHelpCtrl = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPysAddrHelp, &udiSize, &Result);
				s_Can[iCtrl].pHelpCtrl = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmHelpCtrl, &Result);			

				/*Now map the memory.*/
				udiSize = 512;
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "SJA1000Ctrl");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);
				s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				s_Can[iCtrl].pCanRegs = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmSja, &Result);			

				IntDesc.BusType = BT_PCI;
				IntDesc.InterruptMode = IM_LevelSensitive; /*IM_Level_Sensitiv as always on the PCI.*/
				IntDesc.busSpecific.pciInterrupt.ulBusNumber = s_Can[iCtrl].ulBusNr;
				IntDesc.busSpecific.pciInterrupt.ulDevciceNumber = s_Can[iCtrl].ulDevice;
				IntDesc.busSpecific.pciInterrupt.ulFunctionNumber = s_Can[iCtrl].ulFunction;
				IntDesc.busSpecific.pciInterrupt.ulIntLine = s_Can[iCtrl].ulIntVec;
				s_Can[iCtrl].hInt = CAL_SysIntOpen(s_Can[iCtrl].ulIntVec, &IntDesc, &Result);
				if(s_Can[iCtrl].hInt != RTS_INVALID_HANDLE)
				{
					Result = CAL_SysIntRegister(s_Can[iCtrl].hInt, SYS_INT_C, SJA_Interrupt_Handler, (RTS_UINTPTR)&s_Can[iCtrl]);
				}

				/*Issue a hard reset on the controller.*/
				s_Can[iCtrl].pCanRegs[0x100] = 0;
				/*Enable the interrupts on the PLX.*/
				s_Can[iCtrl].pHelpCtrl[0x4c] |= 0x49;
			}
			else
			{ /*For the second controller only do the mapping of the SJA.*/
				udiSize = 512;
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "SJA1000Ctrl");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);
				s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				s_Can[iCtrl].pCanRegs = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmSja, &Result);			
				/*Issue a hard reset on the controller.*/
				s_Can[iCtrl].pCanRegs[0x100] = 0;
			}
		}
		else if((s_Can[iCtrl].usVendorID == VENDOR_ID || s_Can[iCtrl].usVendorID == PCI_VENDOR_ALTERA) && 
			(s_Can[iCtrl].usDeviceID == DEVICE_ID_PCI || 
			 s_Can[iCtrl].usDeviceID == DEVICE_ID_PCI_9030 ||
			 s_Can[iCtrl].usDeviceID == DEVICE_ID_PCI_F3_ALTERA ||
			 s_Can[iCtrl].usDeviceID == DEVICE_ID_PCIEX_A2_ALTERA) &&
			 s_Can[iCtrl].usSubVendorID == SUBVENDOR_ID_AUTOMATA &&
			(s_Can[iCtrl].usSubDeviceID == SUBSYSTEM_ID_3450 ||
				s_Can[iCtrl].usSubDeviceID == SUBSYSTEM_ID_3451 ||
				s_Can[iCtrl].usSubDeviceID == SUBSYSTEM_ID_3455 ||
				s_Can[iCtrl].usSubDeviceID == SUBSYSTEM_ID_3680 ||
				s_Can[iCtrl].usSubDeviceID == SUBSYSTEM_ID_395F))
		{ /*We have an Automata card here.*/
			if(!s_Can[iCtrl].bIsSecondCtrl)
			{
				udiSize = 32;
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "SJA1000Ctrl");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);
				s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				s_Can[iCtrl].pCanRegs = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmSja, &Result);			

				IntDesc.BusType = BT_PCI;
				IntDesc.InterruptMode = IM_LevelSensitive; /*IM_Level_Sensitiv as always on the PCI.*/
				IntDesc.busSpecific.pciInterrupt.ulBusNumber = s_Can[iCtrl].ulBusNr;
				IntDesc.busSpecific.pciInterrupt.ulDevciceNumber = s_Can[iCtrl].ulDevice;
				IntDesc.busSpecific.pciInterrupt.ulFunctionNumber = s_Can[iCtrl].ulFunction;
				IntDesc.busSpecific.pciInterrupt.ulIntLine = s_Can[iCtrl].ulIntVec;
				s_Can[iCtrl].hInt = CAL_SysIntOpen(s_Can[iCtrl].ulIntVec, &IntDesc, &Result);
				if(s_Can[iCtrl].hInt != RTS_INVALID_HANDLE)
				{
					Result = CAL_SysIntRegister(s_Can[iCtrl].hInt, SYS_INT_C, SJA_Interrupt_Handler, (RTS_UINTPTR)&s_Can[iCtrl]);
				}
			}
			else
			{ /*For the second controller only do the mapping of the SJA.*/
				udiSize = 32;
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "SJA1000Ctrl");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);
				s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				s_Can[iCtrl].pCanRegs = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmSja, &Result);			
			}
		}
		else if(s_Can[iCtrl].usVendorID == VENDOR_ID && 
			s_Can[iCtrl].usDeviceID == DEVICE_ID_PCI_9030 &&
			s_Can[iCtrl].usSubVendorID == SUBVENDOR_ID_ASEM &&
			(s_Can[iCtrl].usSubDeviceID == CAN_SUB_SYSTEM_ID_CONF1 ||
				s_Can[iCtrl].usSubDeviceID == CAN_SUB_SYSTEM_ID_CONF2 ||
				s_Can[iCtrl].usSubDeviceID == CAN_SUB_SYSTEM_ID_CONF3))
		{ /*We have an Asem card here.*/

			/*Activate LED support*/
			if (CHK_SysTimeGetMs)
				cmdInfo.bySupport |= CMD_SUPPORT_STATUSLED;

			if(!s_Can[iCtrl].bIsSecondCtrl)
			{
				udiSize = 0x100;

				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "SJA1000Ctrl");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);				

				/* CAN controller addressing */
				s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				s_Can[iCtrl].pCanRegs = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmSja, &Result);

				udiSize = 0x100;

				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "PlxRegs_ASEM");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);				

				s_Can[iCtrl].hShmHelpCtrl = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPysAddrHelp, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmHelpCtrl = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPysAddrHelp, &udiSize, &Result);
				s_Can[iCtrl].pHelpCtrl = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmHelpCtrl, &Result);

				IntDesc.BusType = BT_PCI;
				IntDesc.InterruptMode = IM_LevelSensitive; /*IM_Level_Sensitiv as always on the PCI.*/
				IntDesc.busSpecific.pciInterrupt.ulBusNumber = s_Can[iCtrl].ulBusNr;
				IntDesc.busSpecific.pciInterrupt.ulDevciceNumber = s_Can[iCtrl].ulDevice;
				IntDesc.busSpecific.pciInterrupt.ulFunctionNumber = s_Can[iCtrl].ulFunction;
				IntDesc.busSpecific.pciInterrupt.ulIntLine = s_Can[iCtrl].ulIntVec;
				s_Can[iCtrl].hInt = CAL_SysIntOpen(s_Can[iCtrl].ulIntVec, &IntDesc, &Result);
				if(s_Can[iCtrl].hInt != RTS_INVALID_HANDLE)
				{
					Result = CAL_SysIntRegister(s_Can[iCtrl].hInt, SYS_INT_C, SJA_Interrupt_Handler, (RTS_UINTPTR)&s_Can[iCtrl]);
				}
			}
			else
			{ /*For the second controller only do the mapping of the SJA.*/
				udiSize = 0x100;

				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "SJA1000Ctrl");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);				

				s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				s_Can[iCtrl].pCanRegs = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmSja, &Result);
				
				/*Same Pointer than the first controller*/
				s_Can[iCtrl].pHelpCtrl = s_Can[iCtrl-1].pHelpCtrl;
			}
		}
		else if(s_Can[iCtrl].usVendorID == VENDOR_ID && 
			s_Can[iCtrl].usDeviceID == DEVICE_ID_PCI_9030 &&
			s_Can[iCtrl].usSubVendorID == PCI_JANZ_SUBVENDOR_ID &&
			(s_Can[iCtrl].usSubDeviceID == PCI_JANZ_SUBSYSTEM_ID ||
			 s_Can[iCtrl].usSubDeviceID == PCI_JANZ_SUBSYSTEM_ID_1_CHANNEL ||
			 s_Can[iCtrl].usSubDeviceID == PCI_JANZ_SUBSYSTEM_ID_ONBOARD	))
		{ /*We have an Janz card here.*/

			/*Activate LED support*/
			if (s_Can[iCtrl].usSubDeviceID != PCI_JANZ_SUBSYSTEM_ID_ONBOARD)
			{
				if (CHK_SysTimeGetMs)
					cmdInfo.bySupport |= CMD_SUPPORT_STATUSLED;
			}

			if(!s_Can[iCtrl].bIsSecondCtrl)
			{
				udiSize = 512;
				
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "SJA1000Ctrl");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);

				/* CAN controller addressing */
				s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr,  &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				s_Can[iCtrl].pCanRegs = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmSja, &Result);
				
				udiSize = 64;

				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "InternalRegs_Janz");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);

				s_Can[iCtrl].hShmHelpCtrl = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPysAddrHelp, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmHelpCtrl = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPysAddrHelp, &udiSize, &Result);
				s_Can[iCtrl].pHelpCtrl = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmHelpCtrl, &Result);
				

				if(s_Can[iCtrl].usSubDeviceID == PCI_JANZ_SUBSYSTEM_ID_1_CHANNEL)
					s_Can[iCtrl].pHelpCtrl[3] = 1;
				else
					s_Can[iCtrl].pHelpCtrl[3] = 3;

				IntDesc.BusType = BT_PCI;
				IntDesc.InterruptMode = IM_LevelSensitive; /*IM_Level_Sensitiv as always on the PCI.*/
				IntDesc.busSpecific.pciInterrupt.ulBusNumber = s_Can[iCtrl].ulBusNr;
				IntDesc.busSpecific.pciInterrupt.ulDevciceNumber = s_Can[iCtrl].ulDevice;
				IntDesc.busSpecific.pciInterrupt.ulFunctionNumber = s_Can[iCtrl].ulFunction;
				IntDesc.busSpecific.pciInterrupt.ulIntLine = s_Can[iCtrl].ulIntVec;
				s_Can[iCtrl].hInt = CAL_SysIntOpen(s_Can[iCtrl].ulIntVec, &IntDesc, &Result);
				if(s_Can[iCtrl].hInt != RTS_INVALID_HANDLE)
				{
					Result = CAL_SysIntRegister(s_Can[iCtrl].hInt, SYS_INT_C, SJA_Interrupt_Handler, (RTS_UINTPTR)&s_Can[iCtrl]);
				}
			}
			else
			{ /*For the second controller only do the mapping of the SJA.*/
				udiSize = 512;
				
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "SJA1000Ctrl2");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);

				s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				s_Can[iCtrl].pCanRegs = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmSja, &Result);			
			}
		}
		else if(s_Can[iCtrl].usVendorID == PCI_VENDOR_ALTERA && 
			s_Can[iCtrl].usDeviceID == PCI_DEVICE_GROSSENB &&
			s_Can[iCtrl].usSubVendorID == PCI_SUBVENDOR_ALTERA &&
			s_Can[iCtrl].usSubDeviceID == PCI_SUBDEVICE_GROSSENB)
		{ 
			if(!s_Can[iCtrl].bIsSecondCtrl)
			{
				/*
					- BAR0:    128Byte Memory 
					- Offset 0x00    Debug-LED 
					- BAR1:    2MB Memory 
					- Offset D0000:    CAN1 
					- Offset D1000:    CAN2 
					- Offset D2000:    NvRAM Start 
					- Offset DFFFF:    NvRAM Ende 
					- Offset 0x100362:    Versionsregister 
					- Offset 0x100365:    Statusregister 

				*/
				unsigned char* pHelp;

				udiSize = 0x80 * 4; /*2MB. Not all required, but up to offest 0x100365.*/
				
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "SJA1000Altera");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);

				/* CAN controller addressing */
				s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryOpen(szShmName, s_Can[iCtrl].ulPhysAddr,  &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryCreate(szShmName, s_Can[iCtrl].ulPhysAddr,  &udiSize, &Result);
				s_Can[iCtrl].pCanRegs = (unsigned char*)CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmSja, &Result);
				
				udiSize = 128;
				
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "InternalRegs_Altera");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);

				s_Can[iCtrl].hShmHelpCtrl = CAL_SysSharedMemoryOpen(szShmName, s_Can[iCtrl].ulPysAddrHelp, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmHelpCtrl = CAL_SysSharedMemoryCreate(szShmName, s_Can[iCtrl].ulPysAddrHelp, &udiSize, &Result);
				s_Can[iCtrl].pHelpCtrl = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmHelpCtrl, &Result);
				

				IntDesc.BusType = BT_PCI;
				IntDesc.InterruptMode = IM_LevelSensitive; /*IM_Level_Sensitiv as always on the PCI.*/
				IntDesc.busSpecific.pciInterrupt.ulBusNumber = s_Can[iCtrl].ulBusNr;
				IntDesc.busSpecific.pciInterrupt.ulDevciceNumber = s_Can[iCtrl].ulDevice;
				IntDesc.busSpecific.pciInterrupt.ulFunctionNumber = s_Can[iCtrl].ulFunction;
				IntDesc.busSpecific.pciInterrupt.ulIntLine = s_Can[iCtrl].ulIntVec;
				s_Can[iCtrl].hInt = CAL_SysIntOpen(s_Can[iCtrl].ulIntVec, &IntDesc, &Result);
				if(s_Can[iCtrl].hInt != RTS_INVALID_HANDLE)
				{
					Result = CAL_SysIntRegister(s_Can[iCtrl].hInt, SYS_INT_C, SJA_Interrupt_Handler, (unsigned long)&s_Can[iCtrl]);
				}

				/*Enable the controllers*/
				pHelp = s_Can[iCtrl].pHelpCtrl;
				if(Result == ERR_OK)
				{
					/*Grossenbacher
					  FPGA Kniff -> Das Statusregister muss mindestens einmal ausgelesen werden,
					  um CAN oder NVRAM freizuschalten */
					pHelp[0x13] = pHelp[0x13];
				    pHelp[0x13] = 0x0f;
					if((pHelp[0x10] & 3) == 3 || (pHelp[0x10] & 3) == 1)
					{
						/*NVRAM is present*/
						CmpSjaMpdSetRetainEvent(s_Can[iCtrl].ulNvRamPhysAddr,s_Can[iCtrl].ulNvRamSize);
					}
				}
			}
			else
			{ /*For the second controller only do the mapping of the SJA.*/
				udiSize = 0x80 * 4;
				
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "SJA1000Altera");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);
				
				s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryOpen(szShmName, s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryCreate(szShmName, s_Can[iCtrl].ulPhysAddr,  &udiSize, &Result);
				s_Can[iCtrl].pCanRegs = (unsigned char*)CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmSja, &Result);	
				s_Can[iCtrl].pHelpCtrl = s_Can[iCtrl-1].pHelpCtrl;
			}
		}
		else if(s_Can[iCtrl].usVendorID == VENDOR_ID_IXXAT_2 && 
			s_Can[iCtrl].usDeviceID == DEVICE_ID_PCI_IXXAT_2 &&
			s_Can[iCtrl].usSubDeviceID == SUBSYSTEM_ID_IXXAT_2 &&
			s_Can[iCtrl].usSubVendorID == SUBVENDOR_ID_IXXAT_2)
		{
			/* board with vendor ID 1014, PB 
			always 2 channels, 2nd channel 512 bytes behind the first
			*/
			/* only do the mapping of the SJA */
			udiSize = 512;
			
			CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "SJA1000Ctrl");
			CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
			CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
			CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);
			
			s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
			if(Result == ERR_NO_OBJECT)
				s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
			s_Can[iCtrl].pCanRegs = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmSja, &Result);

			IntDesc.BusType = BT_PCI;
			IntDesc.InterruptMode = IM_LevelSensitive; /*IM_Level_Sensitiv as always on the PCI.*/
			IntDesc.busSpecific.pciInterrupt.ulBusNumber = s_Can[iCtrl].ulBusNr;
			IntDesc.busSpecific.pciInterrupt.ulDevciceNumber = s_Can[iCtrl].ulDevice;
			IntDesc.busSpecific.pciInterrupt.ulFunctionNumber = s_Can[iCtrl].ulFunction;
			IntDesc.busSpecific.pciInterrupt.ulIntLine = s_Can[iCtrl].ulIntVec;
			s_Can[iCtrl].hInt = CAL_SysIntOpen(s_Can[iCtrl].ulIntVec, &IntDesc, &Result);
			if(s_Can[iCtrl].hInt != RTS_INVALID_HANDLE)
			{
				Result = CAL_SysIntRegister(s_Can[iCtrl].hInt, SYS_INT_C, SJA_Interrupt_Handler, (RTS_UINTPTR)&s_Can[iCtrl]);
			}

			/*Issue a hard reset on the controller.*/
			s_Can[iCtrl].pCanRegs[0x100] = 0;
			
			/* 2nd channel 512 bytes behind the first */
			iCtrl++;
			s_Can[iCtrl].hShmSja = s_Can[iCtrl-1].hShmSja; 
			s_Can[iCtrl].pCanRegs = s_Can[iCtrl-1].pCanRegs + 0x200;

			IntDesc.BusType = BT_PCI;
			IntDesc.InterruptMode = IM_LevelSensitive; /*IM_Level_Sensitiv as always on the PCI.*/
			IntDesc.busSpecific.pciInterrupt.ulBusNumber = s_Can[iCtrl].ulBusNr;
			IntDesc.busSpecific.pciInterrupt.ulDevciceNumber = s_Can[iCtrl].ulDevice;
			IntDesc.busSpecific.pciInterrupt.ulFunctionNumber = s_Can[iCtrl].ulFunction;
			IntDesc.busSpecific.pciInterrupt.ulIntLine = s_Can[iCtrl].ulIntVec;
			s_Can[iCtrl].hInt = CAL_SysIntOpen(s_Can[iCtrl].ulIntVec, &IntDesc, &Result);
			if(s_Can[iCtrl].hInt != RTS_INVALID_HANDLE)
			{
				Result = CAL_SysIntRegister(s_Can[iCtrl].hInt, SYS_INT_C, SJA_Interrupt_Handler, (RTS_UINTPTR)&s_Can[iCtrl]);
			}

			/*Issue a hard reset on the controller.*/
			s_Can[iCtrl].pCanRegs[0x100] = 0;
		}
		else if(s_Can[iCtrl].usVendorID == VENDOR_ID && 
			s_Can[iCtrl].usDeviceID == DEVICE_ID_PCI &&
			s_Can[iCtrl].usSubDeviceID == SUBSYSTEM_ID_ESD_PCI200 &&
			s_Can[iCtrl].usSubVendorID == SUBVENDOR_ID_ESD)
		{
			if(!s_Can[iCtrl].bIsSecondCtrl)
			{
				/*The internal regs of the PSB. We must map this to init the card.*/
				udiSize = 128;
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "InternalRegs_Esd");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);
				s_Can[iCtrl].hShmHelpCtrl = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPysAddrHelp, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmHelpCtrl = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPysAddrHelp, &udiSize, &Result);
				s_Can[iCtrl].pHelpCtrl = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmHelpCtrl, &Result);			

				/*Now map the memory.*/
				udiSize = 4096;
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "SJA1000Ctrl");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);
				s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				s_Can[iCtrl].pCanRegs = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmSja, &Result);			

				IntDesc.BusType = BT_PCI;
				IntDesc.InterruptMode = IM_LevelSensitive; /*IM_Level_Sensitiv as always on the PCI.*/
				IntDesc.busSpecific.pciInterrupt.ulBusNumber = s_Can[iCtrl].ulBusNr;
				IntDesc.busSpecific.pciInterrupt.ulDevciceNumber = s_Can[iCtrl].ulDevice;
				IntDesc.busSpecific.pciInterrupt.ulFunctionNumber = s_Can[iCtrl].ulFunction;
				IntDesc.busSpecific.pciInterrupt.ulIntLine = s_Can[iCtrl].ulIntVec;
				s_Can[iCtrl].hInt = CAL_SysIntOpen(s_Can[iCtrl].ulIntVec, &IntDesc, &Result);
				if(s_Can[iCtrl].hInt != RTS_INVALID_HANDLE)
				{
					Result = CAL_SysIntRegister(s_Can[iCtrl].hInt, SYS_INT_C, SJA_Interrupt_Handler, (unsigned long)&s_Can[iCtrl]);
				}

				/*TODO: little oder big endian!?*/
				s_Can[iCtrl].pHelpCtrl[0x2B] |= 0x01; /* To little endian */
				s_Can[iCtrl].pHelpCtrl[0x4c] |= 0x41; /*Enable the interrupts on the PLX.*/
			}
			else
			{   
				/*test for second controller:*/
				int found = 0;

				udiSize = 4096;
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "SJA1000Ctrl");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);
				s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				s_Can[iCtrl].pCanRegs = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmSja, &Result);

				s_Can[iCtrl].pCanRegs[0] = 0x01;
				s_Can[iCtrl].pCanRegs[31] = 0x00;
				s_Can[iCtrl].pCanRegs[0] = 0x01;
				if(s_Can[iCtrl].pCanRegs[0] == 0x21) {
					s_Can[iCtrl].pCanRegs[0] = 0x1f;
					if(s_Can[iCtrl].pCanRegs[0] == 0x3f) {
						found = 1;      
					}
					s_Can[iCtrl].pCanRegs[0] = 0x01;
				}

				/* if not found, mark device to be unused: */
				if (found == 0) {
					s_Can[iCtrl].pCanRegs = NULL;
					s_Can[iCtrl].ulPhysAddr = 0;
					CAL_SysSharedMemoryClose(s_Can[iCtrl].hShmSja);
				}
			}

		/* esd CPCI200 / 104-200: */
		} else if(s_Can[iCtrl].usVendorID == VENDOR_ID && s_Can[iCtrl].usDeviceID == DEVICE_ID_PCI_9030 && s_Can[iCtrl].usSubVendorID == SUBVENDOR_ID_ESD &&
			((s_Can[iCtrl].usSubDeviceID == SUBSYSTEM_ID_ESD_CPCI200) || (s_Can[iCtrl].usSubDeviceID == SUBSYSTEM_ID_ESD_104200))
			)
		{
			if(!s_Can[iCtrl].bIsSecondCtrl)
			{
				/*The internal regs of the PSB. We must map this to init the card.*/
				udiSize = 256;
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "InternalRegs_Esd");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);
				s_Can[iCtrl].hShmHelpCtrl = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPysAddrHelp, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmHelpCtrl = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPysAddrHelp, &udiSize, &Result);
				s_Can[iCtrl].pHelpCtrl = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmHelpCtrl, &Result);			

				/*Now map the memory.*/
				udiSize = 4096;
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "SJA1000Ctrl");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);
				s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr,  &udiSize, &Result);
				s_Can[iCtrl].pCanRegs = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmSja, &Result);			

				IntDesc.BusType = BT_PCI;
				IntDesc.InterruptMode = IM_LevelSensitive; /*IM_Level_Sensitiv as always on the PCI.*/
				IntDesc.busSpecific.pciInterrupt.ulBusNumber = s_Can[iCtrl].ulBusNr;
				IntDesc.busSpecific.pciInterrupt.ulDevciceNumber = s_Can[iCtrl].ulDevice;
				IntDesc.busSpecific.pciInterrupt.ulFunctionNumber = s_Can[iCtrl].ulFunction;
				IntDesc.busSpecific.pciInterrupt.ulIntLine = s_Can[iCtrl].ulIntVec;
				s_Can[iCtrl].hInt = CAL_SysIntOpen(s_Can[iCtrl].ulIntVec, &IntDesc, &Result);
				if(s_Can[iCtrl].hInt != RTS_INVALID_HANDLE)
				{
					Result = CAL_SysIntRegister(s_Can[iCtrl].hInt, SYS_INT_C, SJA_Interrupt_Handler, (unsigned long)&s_Can[iCtrl]);
				}

				/*TODO: little oder big endian!?*/
				s_Can[iCtrl].pHelpCtrl[0x2B] |= 0x01; /* To little endian */
				s_Can[iCtrl].pHelpCtrl[0x4c] |= 0x41; /*Enable the interrupts on the PLX.*/
			}
			else
			{ 
				/*test for second controller:*/
				int found = 0;

				udiSize = 4096;
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "SJA1000Ctrl");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);
				s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				s_Can[iCtrl].pCanRegs = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmSja, &Result);

				s_Can[iCtrl].pCanRegs[0] = 0x01;
				s_Can[iCtrl].pCanRegs[31] = 0x00;
				s_Can[iCtrl].pCanRegs[0] = 0x01;
				if(s_Can[iCtrl].pCanRegs[0] == 0x21) {
					s_Can[iCtrl].pCanRegs[0] = 0x1f;
					if(s_Can[iCtrl].pCanRegs[0] == 0x3f) {
						found = 1;      
					}
					s_Can[iCtrl].pCanRegs[0] = 0x01;
				}

				/* if not found, mark device to be unused: */
				if (found == 0) {
					s_Can[iCtrl].pCanRegs = NULL;
					s_Can[iCtrl].ulPhysAddr = 0;
					CAL_SysSharedMemoryClose(s_Can[iCtrl].hShmSja);
				}
			}			

		/* esd PCI266/PEX266/PMC266: */
		} else if ((s_Can[iCtrl].usVendorID == VENDOR_ID && s_Can[iCtrl].usDeviceID == DEVICE_ID_PCI_9056 && s_Can[iCtrl].usSubVendorID == SUBVENDOR_ID_ESD) &&
			((s_Can[iCtrl].usSubDeviceID == SUBSYSTEM_ID_ESD_PCI266) || (s_Can[iCtrl].usSubDeviceID == SUBSYSTEM_ID_ESD_PEX266) || (s_Can[iCtrl].usSubDeviceID == SUBSYSTEM_ID_ESD_PMC266))
			)
		{
			if(!s_Can[iCtrl].bIsSecondCtrl)
			{
				/*The internal regs of the PSB. We must map this to init the card.*/
				udiSize = 256;
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "InternalRegs_Esd");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);
				s_Can[iCtrl].hShmHelpCtrl = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPysAddrHelp, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmHelpCtrl = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPysAddrHelp, &udiSize, &Result);
				s_Can[iCtrl].pHelpCtrl = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmHelpCtrl, &Result);			

				/*Now map the memory.*/
				udiSize = 4096;
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "SJA1000Ctrl");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);
				s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr,  &udiSize, &Result);
				s_Can[iCtrl].pCanRegs = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmSja, &Result);			

				IntDesc.BusType = BT_PCI;
				IntDesc.InterruptMode = IM_LevelSensitive; /*IM_Level_Sensitiv as always on the PCI.*/
				IntDesc.busSpecific.pciInterrupt.ulBusNumber = s_Can[iCtrl].ulBusNr;
				IntDesc.busSpecific.pciInterrupt.ulDevciceNumber = s_Can[iCtrl].ulDevice;
				IntDesc.busSpecific.pciInterrupt.ulFunctionNumber = s_Can[iCtrl].ulFunction;
				IntDesc.busSpecific.pciInterrupt.ulIntLine = s_Can[iCtrl].ulIntVec;
				s_Can[iCtrl].hInt = CAL_SysIntOpen(s_Can[iCtrl].ulIntVec, &IntDesc, &Result);
				if(s_Can[iCtrl].hInt != RTS_INVALID_HANDLE) {
					Result = CAL_SysIntRegister(s_Can[iCtrl].hInt, SYS_INT_C, SJA_Interrupt_Handler, (unsigned long)&s_Can[iCtrl]);
				}

				*(long*)(&s_Can[iCtrl].pHelpCtrl[0x68]) = 0x00000900; /*Enable the interrupts on the PLX.*/
			}
			else
			{
				/*test for second controller:*/
				int found = 0;

				udiSize = 4096;
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "SJA1000Ctrl");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);
				s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				s_Can[iCtrl].pCanRegs = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmSja, &Result);

				s_Can[iCtrl].pCanRegs[0] = 0x01;
				s_Can[iCtrl].pCanRegs[31] = 0x00;
				s_Can[iCtrl].pCanRegs[0] = 0x01;
				if(s_Can[iCtrl].pCanRegs[0] == 0x21) {
					s_Can[iCtrl].pCanRegs[0] = 0x1f;
					if(s_Can[iCtrl].pCanRegs[0] == 0x3f) {
						found = 1;      
					}
					s_Can[iCtrl].pCanRegs[0] = 0x01;
				}

				/* if not found, mark device to be unused:*/
				if (found == 0) {
					s_Can[iCtrl].pCanRegs = NULL;
					s_Can[iCtrl].ulPhysAddr = 0;
					CAL_SysSharedMemoryClose(s_Can[iCtrl].hShmSja);
				}
			}

		} 

		else if(s_Can[iCtrl].usVendorID == PCI_VENDOR_ADAM_5095 && /* Advantech */
			s_Can[iCtrl].usDeviceID == PCI_DEVICE_ADAM_5095 &&
			s_Can[iCtrl].usSubVendorID == PCI_SUBVENDOR_ADAM_5095 &&
			s_Can[iCtrl].usSubDeviceID == PCI_SUBDEVICE_ADAM_5095)
		{ 
			if(!s_Can[iCtrl].bIsSecondCtrl)
			{
				/*
					- BAR0:    
					- BAR1:    CAN1 
					- BAR2:    CAN2 
					- revision register  etc. 

				unsigned char* pHelp;
				*/

				/* udiSize = 4096; 1 page */
				
				/* CAN controller addressing is IO port on ADAM */
				s_Can[iCtrl].pCanRegs = (unsigned char*)s_Can[iCtrl].ulPhysAddr; /*Use the address directly.*/

				/*Check the availability of this controller.*/
				if(!CheckForSJAAvailableHere(iCtrl,s_Can[iCtrl].pCanRegs))
				{ /*This SJA is not available, it does not respond like a SJA should.*/
					s_Can[iCtrl].bDetected = 0;
				}
				else
				{ /*This SJA reacts o.k.*/
					s_Can[iCtrl].bDetected = 1;
				}
				
				/* if access to more PCI registers is needed
				udiSize = 128;
				
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "InternalRegs_Adam5095");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);

				s_Can[iCtrl].hShmHelpCtrl = CAL_SysSharedMemoryOpen(szShmName, s_Can[iCtrl].ulPysAddrHelp, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmHelpCtrl = CAL_SysSharedMemoryCreate(szShmName, s_Can[iCtrl].ulPysAddrHelp, &udiSize, &Result);
				s_Can[iCtrl].pHelpCtrl = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmHelpCtrl, &Result);
				*/

				IntDesc.BusType = BT_PCI;
				IntDesc.InterruptMode = IM_LevelSensitive; /*IM_Level_Sensitiv as always on the PCI.*/
				IntDesc.busSpecific.pciInterrupt.ulBusNumber = s_Can[iCtrl].ulBusNr;
				IntDesc.busSpecific.pciInterrupt.ulDevciceNumber = s_Can[iCtrl].ulDevice;
				IntDesc.busSpecific.pciInterrupt.ulFunctionNumber = s_Can[iCtrl].ulFunction;
				IntDesc.busSpecific.pciInterrupt.ulIntLine = s_Can[iCtrl].ulIntVec;
				s_Can[iCtrl].hInt = CAL_SysIntOpen(s_Can[iCtrl].ulIntVec, &IntDesc, &Result);
				if(s_Can[iCtrl].hInt != RTS_INVALID_HANDLE)
				{
					Result = CAL_SysIntRegister(s_Can[iCtrl].hInt, SYS_INT_C, SJA_Interrupt_Handler, (unsigned long)&s_Can[iCtrl]);
				}
			}
			else
			{ /*For the second controller only do the mapping of the SJA.
				udiSize = 4096;
				*/
				
				s_Can[iCtrl].pCanRegs = (unsigned char*)s_Can[iCtrl].ulPhysAddr; /*Use the address directly.*/
				s_Can[iCtrl].pHelpCtrl = s_Can[iCtrl-1].pHelpCtrl;
			}
		}
		else if(s_Can[iCtrl].usVendorID == PCI_VENDOR_PCM26D2CA && /* Advantech */
			(s_Can[iCtrl].usDeviceID == PCI_DEVICE_PCM26D2CA || s_Can[iCtrl].usDeviceID == PCI_DEVICE_PCM26D2CA_2) &&
			s_Can[iCtrl].usSubVendorID == PCI_SUBVENDOR_PCM26D2CA &&
			(s_Can[iCtrl].usSubDeviceID == PCI_SUBDEVICE_PCM26D2CA || s_Can[iCtrl].usSubDeviceID == PCI_SUBDEVICE_PCM26D2CA_2))
		{ 
			if(!s_Can[iCtrl].bIsSecondCtrl)
			{
				udiSize = 0x400;
				s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				s_Can[iCtrl].pCanRegs = (unsigned char*)CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmSja, &Result);

				/*Check the availability of this controller.*/
				if(!CheckForSJAAvailableHere(iCtrl,s_Can[iCtrl].pCanRegs))
				{ /*This SJA is not available, it does not respond like a SJA should.*/
					s_Can[iCtrl].bDetected = 0;
					CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0x1234, "CmpSJACanDrv: ***Error*** PCM26D2CA not correctly detected.");
				}
				else
				{ /*This SJA reacts o.k.*/
					s_Can[iCtrl].bDetected = 1;
					CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0x1234, "CmpSJACanDrv: PCM26D2CA correctly detected.");
				}
				
				/* if access to more PCI registers is needed
				udiSize = 128;
				
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), "InternalRegs_Adam5095");
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
				CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
				CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);

				s_Can[iCtrl].hShmHelpCtrl = CAL_SysSharedMemoryOpen(szShmName, s_Can[iCtrl].ulPysAddrHelp, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmHelpCtrl = CAL_SysSharedMemoryCreate(szShmName, s_Can[iCtrl].ulPysAddrHelp, &udiSize, &Result);
				s_Can[iCtrl].pHelpCtrl = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmHelpCtrl, &Result);
				*/

				if (!s_Can[iCtrl].bDetected) 
				{
					s_Can[iCtrl].pCanRegs = NULL;
					CAL_SysSharedMemoryClose(s_Can[iCtrl].hShmSja);
				}
				else
				{ /*Ok, connect the interrupt.*/
					IntDesc.BusType = BT_PCI;
					IntDesc.InterruptMode = IM_LevelSensitive; /*IM_Level_Sensitiv as always on the PCI.*/
					IntDesc.busSpecific.pciInterrupt.ulBusNumber = s_Can[iCtrl].ulBusNr;
					IntDesc.busSpecific.pciInterrupt.ulDevciceNumber = s_Can[iCtrl].ulDevice;
					IntDesc.busSpecific.pciInterrupt.ulFunctionNumber = s_Can[iCtrl].ulFunction;
					IntDesc.busSpecific.pciInterrupt.ulIntLine = s_Can[iCtrl].ulIntVec;
					s_Can[iCtrl].hInt = CAL_SysIntOpen(s_Can[iCtrl].ulIntVec, &IntDesc, &Result);
					if(s_Can[iCtrl].hInt != RTS_INVALID_HANDLE)
					{
						Result = CAL_SysIntRegister(s_Can[iCtrl].hInt, SYS_INT_C, SJA_Interrupt_Handler, (unsigned long)&s_Can[iCtrl]);
					}
				}
			}
			else
			{ /*For the second controller only do the mapping of the SJA.
				udiSize = 4096;
				*/
				udiSize = 0x400;
				s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				s_Can[iCtrl].pCanRegs = (unsigned char*)CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmSja, &Result);

				/*Check the availability of this controller.*/
				if(!CheckForSJAAvailableHere(iCtrl,s_Can[iCtrl].pCanRegs))
				{ /*This SJA is not available, it does not respond like a SJA should.*/
					s_Can[iCtrl].bDetected = 0;
					CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0x1234, "CmpSJACanDrv: ***Error*** PCM26D2CA 2nd not correctly detected.");
				}
				else
				{ /*This SJA reacts o.k.*/
					s_Can[iCtrl].bDetected = 1;
					CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0x1234, "CmpSJACanDrv: PCM26D2CA 2nd correctly detected.");
				}
				if (!s_Can[iCtrl].bDetected) 
				{
					s_Can[iCtrl].pCanRegs = NULL;
					CAL_SysSharedMemoryClose(s_Can[iCtrl].hShmSja);
				}
			}
		}

		else
		{ /*We have any other sja-controller here, maybe from a cfg-file.*/
			if(s_Can[iCtrl].bMemoryMapped)
			{
				udiSize = 32 * s_Can[iCtrl].iAlignment;
				CAL_CMUtlSafeStrCpy(szShmName, sizeof(szShmName), s_Can[iCtrl].szName);
				
				/* if the runtime config specifies
					[CmpSJACanDrv] 
					0.Name=NoPCIBus	
					then we will not map this as PCI memory
				*/
				if (strcmp(szShmName, SHM_NO_PCI_BUS_STRING) != 0)
				{
					CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), SHM_PCI_BUSNUMBER_STRING);
					CAL_CMUtlsnprintf(szBusnumber, sizeof(szBusnumber), "%ld", s_Can[iCtrl].ulBusNr); 
					CAL_CMUtlSafeStrCat(szShmName, sizeof(szShmName), szBusnumber);
				}
				s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryOpen(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				if(Result == ERR_NO_OBJECT)
					s_Can[iCtrl].hShmSja = CAL_SysSharedMemoryCreate(szShmName, (RTS_UINTPTR)s_Can[iCtrl].ulPhysAddr, &udiSize, &Result);
				s_Can[iCtrl].pCanRegs = CAL_SysSharedMemoryGetPointer(s_Can[iCtrl].hShmSja, &Result);			
			}
			else
				s_Can[iCtrl].pCanRegs = (unsigned char*)s_Can[iCtrl].ulPhysAddr; /*Use the address directly.*/

			/*Write to the boards portvalue.*/
			if(s_Can[iCtrl].ulPortAddr)
			{
				CAL_SysPortOut(s_Can[iCtrl].ulPortAddr,(unsigned char)s_Can[iCtrl].ulPortVal);
				CAL_SysPortIn(s_Can[iCtrl].ulPortAddr,NULL); /*Reading is for debugging only.*/
			}

			/*Check the availability of this controller.*/
			if(!CheckForSJAAvailableHere(iCtrl,s_Can[iCtrl].pCanRegs))
			{ /*This SJA is not available, it does not respond like a SJA should.*/
				s_Can[iCtrl].bDetected = 0;
			}
			else
			{ /*This SJA reacts o.k.*/
				s_Can[iCtrl].bDetected = 1;
			}

			/*Connect an interrupt. Only if the controller is available!*/
			if(s_Can[iCtrl].bDetected)
			{
				if(s_Can[iCtrl].ulBusType == BT_PCI)
				{
					IntDesc.BusType = BT_PCI;
					IntDesc.InterruptMode = s_Can[iCtrl].ulIntEdgeTrig; /*IM_Level_Sensitiv as always on the PCI.*/
					IntDesc.busSpecific.pciInterrupt.ulBusNumber = s_Can[iCtrl].ulBusNr;
					IntDesc.busSpecific.pciInterrupt.ulDevciceNumber = s_Can[iCtrl].ulDevice;
					IntDesc.busSpecific.pciInterrupt.ulFunctionNumber = s_Can[iCtrl].ulFunction;
					IntDesc.busSpecific.pciInterrupt.ulIntLine = s_Can[iCtrl].ulIntVec;
					s_Can[iCtrl].hInt = CAL_SysIntOpen(s_Can[iCtrl].ulIntVec, &IntDesc, &Result);
					if(s_Can[iCtrl].hInt != RTS_INVALID_HANDLE)
					{
						Result = CAL_SysIntRegister(s_Can[iCtrl].hInt, SYS_INT_C, SJA_Interrupt_Handler, (RTS_UINTPTR)&s_Can[iCtrl]);
					}
				}
				else
				{
					IntDesc.BusType = BT_ISA;
					IntDesc.InterruptMode = s_Can[iCtrl].ulIntEdgeTrig;
					IntDesc.busSpecific.isaInterrupt.ulIntLine = s_Can[iCtrl].ulIntVec;
					s_Can[iCtrl].hInt = CAL_SysIntOpen(s_Can[iCtrl].ulIntVec, &IntDesc, &Result);
					if(s_Can[iCtrl].hInt != RTS_INVALID_HANDLE)
					{
						Result = CAL_SysIntRegister(s_Can[iCtrl].hInt, SYS_INT_C, SJA_Interrupt_Handler, (RTS_UINTPTR)&s_Can[iCtrl]);
					}
				}
			}
		}
	}
}



/*The only access of any SJA-Register is done here.*/
unsigned char SjaWriteRegister(int iDev, unsigned char* pucBase, unsigned long ulRegOffs, unsigned char c)
{
	if(s_Can[iDev].bMemoryMapped)
	{
		*(pucBase + ulRegOffs * s_Can[iDev].iAlignment) = c;
		return c;
	}

	CAL_SysPortOut((unsigned long)pucBase + ulRegOffs * s_Can[iDev].iAlignment,c);
	return c;
}

unsigned char SjaReadRegister(int iDev, unsigned char* pucBase, unsigned long ulRegOffs)
{
	unsigned char c;
	if(s_Can[iDev].bMemoryMapped)
	{
		c = *(pucBase + ulRegOffs * s_Can[iDev].iAlignment);
		return c;
	}
	c = CAL_SysPortIn((unsigned long)pucBase + ulRegOffs * s_Can[iDev].iAlignment,NULL);
	return c;
}
/*End access of the registers.*/
static CAA_ERROR CMD_Setup(CL2I_BYTE byNet)
{
	SJA_CHIP* pNet;
	unsigned char byCtrl = s_byDriver[byNet];

	pNet = s_Can[byCtrl].pCanRegs;
	if(!pNet)
	{
		return CMD_SETUP_ERROR;
	}

	/* Disable Interrupts */
	SjaWriteRegister(byCtrl,pNet,SJA_IRen,0);

	/* Enter Reset Mode */
	SjaWriteRegister(byCtrl,pNet,SJA_CR_MODE,1);

	/* Disable Interrupts */
	SjaWriteRegister(byCtrl,pNet,SJA_IRen,0);

	if(s_hTxBlock[byCtrl] != CAA_hINVALID)
	{
		CAL_CL2_MsgFree(byNet,s_hTxBlock[byCtrl]);
		s_hTxBlock[byCtrl] = CAA_hINVALID;
	}

	/* Enable Interrupts, for second controllers its ok to fail */
	CAL_SysIntDisable(s_Can[byCtrl].hInt); 
	CAL_SysIntEnable(s_Can[byCtrl].hInt); 

	/* Enter Reset Mode */
	SjaWriteRegister(byCtrl,pNet,SJA_CR_MODE,1);

	/* Disable Interrupts */
	SjaWriteRegister(byCtrl,pNet,SJA_IRen,0);

	/* Switch To Pelican */
	if(s_Can[byCtrl].bHasSubCtrl && (s_Can[byCtrl].usVendorID == VENDOR_ID_PEAK))
		SjaWriteRegister(byCtrl,pNet,SJA_CLK_DIV,0xC7); /*For the Peak second controller enable the clk-out.*/
	else
		SjaWriteRegister(byCtrl,pNet,SJA_CLK_DIV,0xC8);

	/* Open Acceptance Mask */
	SjaWriteRegister(byCtrl,pNet,SJA_ACC0,0x0);
	SjaWriteRegister(byCtrl,pNet,SJA_ACC1,0x0);
	SjaWriteRegister(byCtrl,pNet,SJA_ACC2,0x0);
	SjaWriteRegister(byCtrl,pNet,SJA_ACC3,0x0);

	SjaWriteRegister(byCtrl,pNet,SJA_ACCM0,0xff);
	SjaWriteRegister(byCtrl,pNet,SJA_ACCM1,0xff);
	SjaWriteRegister(byCtrl,pNet,SJA_ACCM2,0xff);
	SjaWriteRegister(byCtrl,pNet,SJA_ACCM3,0xff);

	/* Preset Bus-Timing-Register */
	SjaWriteRegister(byCtrl,pNet,SJA_BTR0,0x0);
	SjaWriteRegister(byCtrl,pNet,SJA_BTR1,0x0);

	/* Set Output Control */
	SjaWriteRegister(byCtrl,pNet,SJA_OC,(char)s_Can[byCtrl].ulOutputControl);

	/* -------- !!!!!!! Chip is in RESET MODE !!!!!!!! -------- */

	return CMD_NO_ERROR;
}

static CAA_ERROR CMD_Init(CL2I_BYTE byNet, CL2I_WORD wBaudrate)
{
	SJA_CHIP* pNet = s_Can[s_byDriver[byNet]].pCanRegs;
	CL2I_BYTE byBaud;
	char cBtr0,cBtr1;
	char cIntMask;

	if(!pNet)
	{
		return CMD_SETUP_ERROR;
	}

	/* Disable Interrupts */
	SjaWriteRegister(s_byDriver[byNet],pNet,SJA_IRen,0);

	if (!CheckForSJAAvailableHere(s_byDriver[byNet], pNet))
		return CMD_SETUP_ERROR;

	/* Reenter Reset Mode*/
	SjaWriteRegister(s_byDriver[byNet],pNet,SJA_CR_MODE,1);

	if(s_Can[s_byDriver[byNet]].ulXTalFrequency != 16000000 && 
		s_Can[s_byDriver[byNet]].ulXTalFrequency != 24000000)
		return CMD_SETUP_ERROR; /*We only have a setup table for 16 and 24 Mhz.*/

	if(wBaudrate == 10)
	{
		byBaud = 0;
	}
	else if(wBaudrate == 20)
	{
		byBaud = 1;
	}
	else if(wBaudrate == 50)
	{
		byBaud = 2;
	}
	else if(wBaudrate == 100)
	{
		byBaud = 3;
	}
	else if(wBaudrate == 125)
	{
		byBaud = 4;
	}
	else if(wBaudrate == 250)
	{
		byBaud = 5;
	}
	else if(wBaudrate == 500)
	{
		byBaud = 6;
	}
	else if(wBaudrate == 800)
	{
		byBaud = 7;
	}
	else if(wBaudrate == 1000)
	{
		byBaud = 8;
	}
	else
	{
		return CMD_WRONG_BAUD;
	}

	/* Set Bus-Timing-Register */
	if(s_Can[s_byDriver[byNet]].ulXTalFrequency == 16000000)
	{
		cBtr0=btrv16[byBaud].BTR0;
		cBtr1=btrv16[byBaud].BTR1;
	}
	else
	{
		cBtr0=btrv24[byBaud].BTR0;
		cBtr1=btrv24[byBaud].BTR1;
	}
	SjaWriteRegister(s_byDriver[byNet],pNet,SJA_BTR0,cBtr0);
	SjaWriteRegister(s_byDriver[byNet],pNet,SJA_BTR1,cBtr1);

	cIntMask = (char)(SJA_INT_BIT_BUSERROR | SJA_INT_BIT_ERRPASSIVE | SJA_INT_BIT_DATAOVERRUN |
				SJA_INT_BIT_ERRWARNING | SJA_INT_BIT_TXINT | SJA_INT_BIT_RXINT);
	SjaWriteRegister(s_byDriver[byNet],pNet,SJA_IRen,cIntMask);

	if (s_pInfo[s_byDriver[byNet]] == CAA_pNULL)
		return CMD_SETUP_ERROR;

	CAA_MEMSET(s_pInfo[s_byDriver[byNet]], 0, sizeof(CL2I_INFO));
	s_pInfo[s_byDriver[byNet]]->byBusState = (CL2I_BYTE)CL2_ERR_FREE;

	/* Leave Reset Mode */
	SjaWriteRegister(s_byDriver[byNet],pNet,SJA_CR_MODE,0);
 
	return CMD_NO_ERROR;
}

static CAA_BOOL CMD_Send(CL2I_BYTE byNet, CAA_HANDLE hBlock, CL2I_BYTE byPrio, CAA_ERROR* peError)
{
	SJA_CHIP*	pNet = s_Can[s_byDriver[byNet]].pCanRegs;
	CL2I_BLOCK* pBlock = (CL2I_BLOCK*)CAL_CL2_MsgGetData(hBlock);
	CAA_BOOL		xType;
	CL2I_BYTE	byBno;
	CL2I_BYTE*	pbySrc;
	CL2I_DWORD	dwId;
	CAA_BOOL 	xRtr;
	char cSr, byHelp;
#ifdef _WRITE_DATA_BY_ULONG_
	int iAlign = s_Can[s_byDriver[byNet]].iAlignment;
#endif
	CL2I_BYTE byModeReg;

	byPrio = byPrio;
	if(!pNet)
	{
		CAA_SET_RESULT(peError, CMD_SETUP_ERROR);
		return CMD_SND_NOT_OK;
	}
	CAA_SET_RESULT(peError, CMD_NO_ERROR);

	cSr = SjaReadRegister(s_byDriver[byNet],pNet,SJA_SR);

	if(s_hTxBlock[s_byDriver[byNet]] != CAA_hINVALID)
	{
		return CMD_SND_NOT_OK;
	}

	if(cSr & SJA_STAT_BS)
	{
		return CMD_SND_NOT_OK;
	}
	
	if(!(cSr & SJA_STAT_TXBUFFSTAT))
	{
		return CMD_SND_NOT_OK;
	}

	byModeReg = SjaReadRegister(s_byDriver[byNet],pNet,SJA_CR_MODE);
	if(byModeReg & 1)
		SjaWriteRegister(s_byDriver[byNet],pNet,SJA_CR_MODE,0); /*Leave Reset mode under any circumstances now.*/

	xRtr = (pBlock->cobId.X.RTR != 0);
	byBno = pBlock->byLen.X.DLC;
	xType = (pBlock->cobId.X.EID != 0);

	/* Copy COBID */
	byHelp = xType*0x80 + xRtr*0x40 + byBno;
	SjaWriteRegister(s_byDriver[byNet],pNet,SJA_TX_FRAME_INFO,byHelp);

	pbySrc=&(pBlock->byData[0]);
	if(xType)
	{
		dwId = (pBlock->cobId.X.ID) << 3;
		SjaWriteRegister(s_byDriver[byNet],pNet,SJA_EFF_TXID1,(unsigned char)(dwId / 0x1000000));
		SjaWriteRegister(s_byDriver[byNet],pNet,SJA_EFF_TXID2,(unsigned char)(dwId / 0x10000));
		SjaWriteRegister(s_byDriver[byNet],pNet,SJA_EFF_TXID3,(unsigned char)(dwId / 0x100));
		SjaWriteRegister(s_byDriver[byNet],pNet,SJA_EFF_TXID4,(unsigned char)(dwId % 0x100));
#ifndef _WRITE_DATA_BY_ULONG_
		if(byBno>8) byBno=8;
		while(byBno--)
		{
			SjaWriteRegister(s_byDriver[byNet],pNet,SJA_EFF_TXDATA1+byBno,pbySrc[byBno]);
		}
#else
		*(unsigned long*)&pNet[SJA_EFF_TXDATA1 * iAlign] = *(unsigned long*)pbySrc;
		*(unsigned long*)&pNet[SJA_EFF_TXDATA2 * iAlign] = *(unsigned long*)&pbySrc[4];
#endif
	}
	else 
	{
		dwId = (pBlock->cobId.X.ID) << 5;
		SjaWriteRegister(s_byDriver[byNet],pNet,SJA_SFF_TXID1,(unsigned char)(dwId / 0x100));
		SjaWriteRegister(s_byDriver[byNet],pNet,SJA_SFF_TXID2,(unsigned char)(dwId % 0x100));
#ifndef _WRITE_DATA_BY_ULONG_
		if(byBno>8) byBno=8;
		while(byBno--)
		{
			SjaWriteRegister(s_byDriver[byNet],pNet,SJA_SFF_TXDATA1+byBno,pbySrc[byBno]);
		}
#else
		*(unsigned long*)&pNet[SJA_SFF_TXDATA1 * iAlign] = *(unsigned long*)pbySrc;
		*(unsigned long*)&pNet[SJA_SFF_TXDATA2 * iAlign] = *(unsigned long*)&pbySrc[4];
#endif
	}

	s_hTxBlock[s_byDriver[byNet]] = hBlock;
	
	/* Trigger Transmision */
	/*g_DebugSent++;*/
	SjaWriteRegister(s_byDriver[byNet],pNet,SJA_CMD,CMD_TXREQUEST);
	return CMD_SND_OK;
}

static CAA_BOOL CMD_Receive(CL2I_BYTE byNet, CAA_HANDLE hBlock, CAA_ERROR* peError)
{
	SJA_CHIP*	pNet = s_Can[s_byDriver[byNet]].pCanRegs;
	CL2I_BLOCK* pBlock = (CL2I_BLOCK*)CAL_CL2_MsgGetData(hBlock);
	CL2I_BYTE	*pbyDst;
	CAA_BOOL		xRtr;
	CL2I_BYTE	byLen;
	CL2I_DWORD	dwId;
	CAA_BOOL		xType;
	CL2I_BYTE	byBno;
	char cFI,cMsgCnt;

	if(!pNet)
	{
		CAA_SET_RESULT(peError, CMD_SETUP_ERROR);
		return CMD_SND_NOT_OK;
	}
	CAA_SET_RESULT(peError, CMD_NO_ERROR);

	if(pBlock)
	{
		pbyDst = &(pBlock->byData[0]);

		cFI = SjaReadRegister(s_byDriver[byNet],pNet,SJA_RX_FRAME_INFO);
		xType = (cFI & SJA_FINFO_FFEXT) != 0;
		byLen=cFI & SJA_FINFO_DLC;
		xRtr=(cFI & SJA_FINFO_RTR) != 0;
		byBno=(byLen>8) ? 8 : byLen;

		if(xType)
		{
			dwId = SjaReadRegister(s_byDriver[byNet],pNet,SJA_EFF_RXID1) * 0x1000000;
			dwId += SjaReadRegister(s_byDriver[byNet],pNet,SJA_EFF_RXID2) * 0x10000;
			dwId += SjaReadRegister(s_byDriver[byNet],pNet,SJA_EFF_RXID3) * 0x100;
			dwId += SjaReadRegister(s_byDriver[byNet],pNet,SJA_EFF_RXID4);
			dwId >>= 3;
			if(!xRtr && (byBno != 0))
			{
				while(byBno--)
				{
					pbyDst[byBno]=SjaReadRegister(s_byDriver[byNet],pNet,SJA_EFF_RXDATA1+byBno);
				}
			}
		}
		else 
		{
			dwId = SjaReadRegister(s_byDriver[byNet],pNet,SJA_SFF_RXID1) * 0x100;
			dwId += SjaReadRegister(s_byDriver[byNet],pNet,SJA_SFF_RXID2);
			dwId >>= 5;
			if(!xRtr && (byBno != 0))
			{
				while(byBno--)
				{
					pbyDst[byBno]=SjaReadRegister(s_byDriver[byNet],pNet,SJA_SFF_RXDATA1+byBno);
				}
			}
		}


		/* Release Receive Buffer */
		SjaWriteRegister(s_byDriver[byNet],pNet,SJA_CMD,CMD_RELRCVBUFF);

		pBlock->byLen.B = byLen;
		pBlock->byNet = byNet;
		pBlock->dwTSP = CAL_SysTimeGetMs();
		pBlock->cobId.D = dwId;
		pBlock->cobId.X.EID = xType;
		pBlock->cobId.X.RTR = xRtr;

		cMsgCnt = SjaReadRegister(s_byDriver[byNet],pNet,SJA_RX_MSG_CTR);
		
		return ((cMsgCnt > 0) ? CMD_MORE_DATA : CMD_NO_MORE_DATA);
	}
	else
	{
		/* Release Receive Buffer */
		SjaWriteRegister(s_byDriver[byNet],pNet,SJA_CMD,CMD_RELRCVBUFF);
		s_pInfo[s_byDriver[byNet]]->ctDataOverruns++;
		return CMD_NO_MORE_DATA;
	}
}

static CAA_ERROR CMD_GetInfo(CL2I_BYTE byNet, CMD_INFO* pInfo)
{
	if(pInfo)
	{
		memcpy((void*)pInfo, (void*)&cmdInfo, sizeof(CMD_INFO));
	}
	return CMD_NO_ERROR;
}

static CAA_ERROR CMD_Dispose(CL2I_BYTE byNet)
{ /*Called by unregister of CL2. This will leave the chip in reset mode.*/
	SjaTurnOffLEDs(byNet);
	return CMD_Setup(byNet);
}

static CAA_ERROR CMD_Identify(CL2I_BYTE byNet, CL2I_BYTE byCount)
{
	return CMD_NO_ERROR;
}

static CAA_HANDLE CMD_SetBlock(CL2I_BYTE byNet, CL2I_BYTE byIndex, CAA_HANDLE hBlock, CAA_ERROR* peError)
{
	return CAA_hINVALID;
}

static CAA_ERROR CMD_SetCycle(CL2I_BYTE byNet, CL2I_BYTE byIndex, CL2I_DWORD dwCycle)
{
	return CMD_NO_ERROR;
}

static CAA_ERROR CMD_SetMask(CL2I_BYTE byNet, CL2I_BYTE byIndex, CL2I_DWORD dwValue, CL2I_DWORD dwMask)
{
	return CMD_NO_ERROR;
}

static CAA_ERROR CMD_ResetAlarm(CL2I_BYTE byNet)
{
	SJA_CHIP*	pNet = s_Can[s_byDriver[byNet]].pCanRegs;
	CL2I_INFO* pInfo = s_pInfo[s_byDriver[byNet]];
	
	if(!pNet)
	{
		return CMD_SETUP_ERROR;
	}

	pInfo->uiBusAlarm = 0;
	SjaWriteRegister(s_byDriver[byNet],pNet,SJA_CR_MODE,0);

	return CMD_NO_ERROR;
}
static int s_bSetupDone;
int CAAFKT SJA_CanMiniDriver_Setup(void)
{
	CL2I_BYTE byDriver;
	CL2I_BYTE byNet;
	CL2I_BYTE byLastNet = 0;
	CAA_ERROR eError;

	s_bSetupDone = 1;

	for(byDriver=0; byDriver < SJA_NDRIVER; byDriver++)
	{
		if(s_Can[byDriver].pCanRegs == NULL ||
			s_Can[byDriver].ulPhysAddr == 0)
			continue;

		for(byNet=byLastNet; byNet < CL2_NNET; byNet++)
		{
			s_byDriver[byNet] = byDriver;
			s_byNet[byDriver] = byNet;
			eError = CAL_CL2_CmdRegister(byNet, &cmdInterface[0], CL2_NRXMSG, &s_pInfo[s_byDriver[byNet]]);
			if(eError == CL2_NO_ERROR)
			{
				byLastNet = byNet + 1;
				break;
			}
			else if(eError == CL2_INVALID_NETID)
			{
				s_pInfo[s_byDriver[byNet]] = CAA_pNULL;
				s_byDriver[byNet] = SJA_NDRIVER;
				s_byNet[byDriver] = SJA_NNET;
			}
			else
			{
				return 1;
			}
		}
	}
	return 0;
}

int CAAFKT SJA_CanMiniDriver_Dispose(void)
{ /*Called by the EXIT3-hook. Is used to unregister from CL2 and to disconnect the interrupt.*/
	CL2I_BYTE byDriver;
	int i;

	if(s_bSetupDone == 0)
		return 0;

	s_bSetupDone = 0;

	for(byDriver=0; byDriver < SJA_NDRIVER; byDriver++)
	{
		CAL_CL2_CmdUnRegister(s_byNet[byDriver]); /*This call will also lead to set the SJA to resetmode.*/
		s_byDriver[s_byNet[byDriver]] = SJA_NDRIVER;
		s_byNet[byDriver] = SJA_NNET;
	}

	for(i = 0; i < SJA_NNET; i++)
	{
		if(s_Can[i].ulPhysAddr == 0)
			continue;

		if(s_Can[i].hInt != RTS_INVALID_HANDLE)
		{
			CAL_SysIntDisable(s_Can[i].hInt);
			CAL_SysIntUnregister(s_Can[i].hInt,SJA_Interrupt_Handler);
			CAL_SysIntClose(s_Can[i].hInt);
		}

		if(s_Can[i].bMemMapHelpCtrl && s_Can[i].pHelpCtrl && s_Can[i].hShmHelpCtrl != RTS_INVALID_HANDLE)
		{
			CAL_SysSharedMemoryClose(s_Can[i].hShmHelpCtrl);
		}

		if(s_Can[i].bMemoryMapped && s_Can[i].pCanRegs && s_Can[i].hShmSja != RTS_INVALID_HANDLE)
		{
			CAL_SysSharedMemoryClose(s_Can[i].hShmSja);
		}
	}

	return 0;
}

DEV_INFO* CDECL SJA_GetDeviceDescription(int iDev)
{
	return &s_Can[iDev];
}

void CAAFKT SJA_CanMiniDriver_Handler(void);
void HUGEPTR CDECL SJA_Interrupt_Handler(RTS_UINTPTR ulAdditionalInfo)
{
	/*This handler is called like an IEC-function. Do not touch the parameter.*/
	unsigned char ucHelp;
	int i;

	for(i = 0; i < SJA_NNET; i++)
	{
		if(s_Can[i].ulPhysAddr == 0 || s_Can[i].pCanRegs == NULL)
			continue;

		if((s_Can[i].usDeviceID == DEVICE_ID_PEAK || s_Can[i].usDeviceID == DEVICE_ID_PEAK2 || s_Can[i].usDeviceID == DEVICE_ID_PEAK3 || s_Can[i].usDeviceID == DEVICE_ID_PEAK4 ||
			s_Can[i].usDeviceID == DEVICE_ID_PEAK5 || s_Can[i].usDeviceID == DEVICE_ID_PEAK6 || s_Can[i].usDeviceID == DEVICE_ID_PEAK7 || s_Can[i].usDeviceID == DEVICE_ID_PEAK8) && 
			s_Can[i].usVendorID == VENDOR_ID_PEAK &&
			!s_Can[i].bIsSecondCtrl)
		{
			/*This is a peak, we have to quit the interrupt in the PSB.*/
			if(s_Can[i].pHelpCtrl != NULL)
			{
				ucHelp = *(s_Can[i].pHelpCtrl);
				*(s_Can[i].pHelpCtrl) = ucHelp;
			}
		}
	}

	SJA_CanMiniDriver_Handler();
}

void CAAFKT SJA_CanMiniDriver_Handler(void)
{
	SJA_CHIP* pNet;
	char istate;
	char sstate;
	CAA_HANDLE hBlock;
	CAA_BOOL xReady;
	CL2I_BYTE byDummy;
	CL2I_BYTE byDriver;
	CL2I_INFO* pInfo;
		
	do
	{
		for(byDriver=0, xReady=1; byDriver < SJA_NDRIVER; byDriver++)
		{
			pNet = s_Can[byDriver].pCanRegs;
			pInfo = s_pInfo[byDriver];
					
			if(pNet && pInfo)
			{
				sstate = SjaReadRegister(byDriver,pNet,SJA_SR);
				/* Clear all CAN-IRQ except Rx-IRQ */
				istate = SjaReadRegister(byDriver,pNet,SJA_IR);

				pInfo->ctRxErrors = SjaReadRegister(byDriver,pNet,SJA_RX_ERRCTR);
				pInfo->ctTxErrors = SjaReadRegister(byDriver,pNet,SJA_TX_ERRCTR);
	
				while(istate != 0)
				{
					/* Transmit Interrupt */
					if(istate & SJA_INT_BIT_TXINT)
					{
						hBlock = s_hTxBlock[byDriver];
						pInfo->ctMessagesSend++;
						s_hTxBlock[byDriver] = CAA_hINVALID;
						CAL_CL2_MsgSendAcknIRQ(s_byNet[byDriver], hBlock);

						if (s_Can[byDriver].usVendorID == VENDOR_ID && 
							s_Can[byDriver].usDeviceID == DEVICE_ID_PCI_9030 &&
							s_Can[byDriver].usSubVendorID == PCI_JANZ_SUBVENDOR_ID &&
							s_Can[byDriver].usSubDeviceID == PCI_JANZ_SUBSYSTEM_ID_ONBOARD)
						{
							SjaWriteRegister(byDriver,pNet, 0x102, 1);
						}
	
						/*g_DebugTxInts++;*/
						if(pInfo->byBusState != (CL2I_BYTE)CL2_ERR_FREE)
							pInfo->byBusState = (CL2I_BYTE)CL2_ACTIVE;
					}

					/* Receive Interrupt */
					if(istate & SJA_INT_BIT_RXINT)
					{
						CAA_BOOL xRes;

						if (s_Can[byDriver].usVendorID == VENDOR_ID && 
							s_Can[byDriver].usDeviceID == DEVICE_ID_PCI_9030 &&
							s_Can[byDriver].usSubVendorID == PCI_JANZ_SUBVENDOR_ID &&
							s_Can[byDriver].usSubDeviceID == PCI_JANZ_SUBSYSTEM_ID_ONBOARD)
						{
							SjaWriteRegister(byDriver,pNet, 0x102, 2);
						}

						while((SjaReadRegister(byDriver,pNet,SJA_SR) & 1) == 1)
						{
							hBlock = CAL_CL2_MsgAlloc(s_byNet[byDriver], CAA_pNULL);
							xRes = CMD_Receive(s_byNet[byDriver], hBlock, CAA_pNULL);
							if(hBlock)
							{
								pInfo->ctMessagesReceived++;
								CAL_CL2_MsgPutRQueue(s_byNet[byDriver], hBlock);
							}
							else
								break;
						}
						if(pInfo->byBusState != (CL2I_BYTE)CL2_ERR_FREE)
							pInfo->byBusState = (CL2I_BYTE)CL2_ACTIVE;
					}

					/* Error Passive Interrupt */
					if(istate & SJA_INT_BIT_ERRPASSIVE)
					{
						/* activate capture mechanism again */
						/*g_DebugPassI++;*/
						byDummy = SjaReadRegister(byDriver,pNet,SJA_ERCC);
						if(s_hTxBlock[byDriver] != CAA_hINVALID)
						{
							CAL_CL2_MsgFree(s_byNet[byDriver], s_hTxBlock[byDriver]);
							s_hTxBlock[byDriver] = CAA_hINVALID;
						}
						/*if(sstate & SJA_STAT_BS)*/
						{
							SjaWriteRegister(byDriver,pNet,SJA_CR_MODE,1); /*Enter reset mode.*/
							
							pInfo->byBusState = (CL2I_BYTE)CL2_BUSOFF;
							pInfo->uiBusAlarm++;
							if(pInfo->uiBusAlarm == 0)
							{
								pInfo->uiBusAlarm = 1;
							}
						}
					}
	
					if(istate & SJA_INT_BIT_BUSERROR)
					{
						/* activate capture mechanism again */
						/*g_DebugErrI++;*/
						byDummy = SjaReadRegister(byDriver,pNet,SJA_TX_ERRCTR);
						if(s_hTxBlock[byDriver] != CAA_hINVALID)
						{
							CAL_CL2_MsgFree(s_byNet[byDriver], s_hTxBlock[byDriver]);
							s_hTxBlock[byDriver] = CAA_hINVALID;
						}
						if(sstate & SJA_STAT_BS)
						{
							SjaWriteRegister(byDriver,pNet,SJA_CR_MODE,1); /*Enter reset mode.*/

							pInfo->byBusState = (CL2I_BYTE)CL2_BUSOFF;
							pInfo->uiBusAlarm++;
							if(pInfo->uiBusAlarm == 0)
							{
								pInfo->uiBusAlarm = 1;
							}
						}
						if(sstate == 0x50)
						{
							if(byDummy > 126)
							{ /*If the transmit error counter is higher than the CAA-defined count, we assume busoff.*/
								SjaWriteRegister(byDriver,pNet,SJA_CR_MODE,1); /*Enter reset mode.*/
								pInfo->byBusState = (CL2I_BYTE)CL2_BUSOFF;
								pInfo->uiBusAlarm++;
								if(pInfo->uiBusAlarm == 0)
								{
									pInfo->uiBusAlarm = 1;
								}
							}
						}
					}

					/* Error Warning Interrupt */
					if(istate & SJA_INT_BIT_ERRWARNING)
					{
						/*g_DebugWarnI++;*/
						if(sstate & SJA_STAT_BS)
						{
							SjaWriteRegister(byDriver,pNet,SJA_CR_MODE,1); /*Enter reset mode.*/

							if(s_hTxBlock[byDriver] != CAA_hINVALID)
							{
								CAL_CL2_MsgFree(s_byNet[byDriver], s_hTxBlock[byDriver]);
								s_hTxBlock[byDriver] = CAA_hINVALID;
							}

							pInfo->byBusState = (CL2I_BYTE)CL2_BUSOFF;
							pInfo->uiBusAlarm++;
							if(pInfo->uiBusAlarm == 0)
							{
								pInfo->uiBusAlarm = 1;
							}
						}
						else if(sstate & SJA_STAT_ERR)
						{
							/*SjaWriteRegister(byDriver,pNet,SJA_CR_MODE,1);*/ /*Enter reset mode.*/
							pInfo->byBusState = (CL2I_BYTE)CL2_WARNING;
							if(s_hTxBlock[byDriver] != CAA_hINVALID)
							{
								CAL_CL2_MsgFree(s_byNet[byDriver], s_hTxBlock[byDriver]);
								s_hTxBlock[byDriver] = CAA_hINVALID;
							}
						}
						if((sstate & (SJA_STAT_ERR | SJA_STAT_BS)) == 0)
						{
							if(pInfo->byBusState != (CL2I_BYTE)CL2_ERR_FREE)
								pInfo->byBusState = (CL2I_BYTE)CL2_ACTIVE;
							CAL_CL2_MsgSendAcknIRQ(s_byNet[byDriver], CAA_hINVALID);
						}
					}
	
					/* Arbitration Lost Interrupt */
					if(istate & SJA_INT_BIT_ARBLOST)
					{
						/* activate capture mechanism again */
						byDummy = SjaReadRegister(byDriver,pNet,SJA_ALC);
					}

					/* Data Overrun */
					if (istate & SJA_INT_BIT_DATAOVERRUN)
					{
						pInfo->ctDataOverruns++;
						SjaWriteRegister(byDriver,pNet,SJA_CMD,CMD_CLEARDATAOVR);
					}

					istate = SjaReadRegister(byDriver,pNet,SJA_IR);
					sstate = SjaReadRegister(byDriver,pNet,SJA_SR);
				}
			}
		}
	} while(!xReady);
}

int SjaEnterResetMode(int iDev, unsigned char* pController, int iTries)
{
    int i = 0;
	SjaWriteRegister(iDev, pController,SJA_CR_MODE,0x01);
    while(i < iTries && (SjaReadRegister(iDev, pController, SJA_CR_MODE) & 0x01) != 0x01)
    { /* retry until reset is accepted!*/
        SjaWriteRegister(iDev, pController,SJA_CR_MODE,0x01);
        i++;
    }

    return (int)(i < iTries);
}

static int CheckForSJAAvailableHere(int iDev, unsigned char* pController)
{
	int iRes = 1;
	unsigned char n, i, j;
	unsigned char regbuff[32] = {0};

	if(!pController)
		return 0;

	if (CmpSjaDisableChipTest()) /* some FPGA based SJA can't do PeliCAN */
		return 1;

	/*First set the SJA to resetmode.*/
	if(!SjaEnterResetMode(iDev,pController,1000))
	{
		/*Entering restmdoe failed.*/
		iRes = 0;
		return iRes;
	}

	/*Set the SJA to basicmode.*/
	SjaWriteRegister(iDev, pController,SJA_CLK_DIV,(unsigned char)(SjaReadRegister(iDev, pController,SJA_CLK_DIV) & 0x7f));
	/*In BasicMode the CMD-registers reads always 0xff.*/
	if(SjaReadRegister(iDev, pController,SJA_CMD) != 0xff)
		return 0;

	/*Set the SJA to PeliCAN-mode.*/
	SjaWriteRegister(iDev, pController,SJA_CLK_DIV,(unsigned char)(SjaReadRegister(iDev,pController,SJA_CLK_DIV) | 0x80));
	/*In PeliCAN-mode the CMD-registers reads always 0x00.*/
	if(SjaReadRegister(iDev, pController,SJA_CMD) != 0x00)
		return 0;

	/*We leave the SJA in resetmode and in case we just wrote to an unknown hardware, we cannot make the writes undone.*/

	/*Now further checks as I learned from PCANView-code, supplied by PEAK.*/
    for (i = 6; i <= 23; i++)
    {
		if (i <= 8 || i == 13 || i >= 16) 
		{
            regbuff[i] = SjaReadRegister(iDev, pController,i); 
            SjaWriteRegister(iDev, pController,i, (unsigned char)(i + 5));
            n = SjaReadRegister(iDev,pController,i);
            if (n != i + 5) 
			{
                iRes = 0 ;
            }
        }
	}

	for (i = 6; i <= 23; i++)
    {
		if (i <= 8 || i == 13 || i >= 16) 
		{
            n = SjaReadRegister(iDev, pController,i);
            if (n != i + 5) 
			{
                iRes = 0 ;
            }
        }
	}

    /* restore registers up to 'i'*/
    for (j = 6; j <= i; j++)
        if (j <= 8 || j == 13 || j >= 16)
            SjaWriteRegister(iDev, pController,j, regbuff[j]);

	return iRes;
}

static CAA_ERROR CMD_SetStatus(CL2I_BYTE byNet, CL2I_BYTE byIndicator)
{
	/*Save Indicator, leds are driven by the CH_COMM_CYCLE hook*/
	s_Can[s_byDriver[byNet]].byIndicator = byIndicator;

	return CMD_NO_ERROR;
}
