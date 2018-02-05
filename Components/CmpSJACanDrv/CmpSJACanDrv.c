/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		SJA Can Mini Driver component
*	Version:
*	Description:
******************************************************************************/

#ifdef CAALib
#include "CAADefines.h"
#ifdef CAA_CL2

#include "CmpSJACanDrvDep.h"

int SjaAddChipDescription(DEV_INFO* pDesc);
void SjaInitChipDescs(void);
void SjaInitAllControllersForUse(void);
void SjaHandleLEDs(unsigned long* pulPhase);

static unsigned long s_ulPhase; 

static unsigned long s_ulNVRamAddress;
static unsigned long s_ulNVRamSize;
static RTS_HANDLE s_hEventRetainGet;

/* External API's */
USE_STMT

static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
#ifdef CPLUSPLUS
	if (cid == CLASSID_CCmpSJACanDrv)
	{
		CCmpSJACanDrv *pCCmpSJACanDrv = static_cast<CCmpSJACanDrv *>(new CCmpSJACanDrv());
		return (IBase*)pCCmpSJACanDrv->QueryInterface(pCCmpSJACanDrv, ITFID_IBase, pResult);
	}
#endif
	return NULL;
}

static RTS_RESULT CDECL DeleteInstance(IBase * hIBase)
{
#ifdef CPLUSPLUS
	IBase *pBase = (IBase *)hIBase;
	pBase->Release();
	return ERR_OK;
#else
	return ERR_NOTIMPLEMENTED;
#endif
}

DLL_DECL int CDECL ComponentEntry(INIT_STRUCT *pInitStruct)
/*	Used to exchange function pointers between component manager and components.
	Called at startup for each component.
	pInitStruct:			IN	Pointer to structure with:
		pfExportFunctions	OUT Pointer to function that exports component functions
		pfImportFunctions	OUT Pointer to function that imports functions from other components
		pfGetVersion		OUT Pointer to function to get component version
		pfRegisterAPI		IN	Pointer to component mangager function to register a api function
		pfGetAPI			IN	Pointer to component mangager function to get a api function
		pfCallHook			IN	Pointer to component mangager function to call a hook function
	Return					ERR_OK if library could be initialized, else error code
*/
{
	pInitStruct->CmpId = COMPONENT_ID;
	pInitStruct->pfExportFunctions = ExportFunctions;
	pInitStruct->pfImportFunctions = ImportFunctions;
	pInitStruct->pfGetVersion = CmpGetVersion;
	pInitStruct->pfHookFunction = HookFunction;
	pInitStruct->pfCreateInstance = CreateInstance;
	pInitStruct->pfDeleteInstance = DeleteInstance;

	s_pfCMRegisterAPI = pInitStruct->pfCMRegisterAPI;
	s_pfCMRegisterAPI2 = pInitStruct->pfCMRegisterAPI2;
	s_pfCMGetAPI = pInitStruct->pfCMGetAPI;
	s_pfCMGetAPI2 = pInitStruct->pfCMGetAPI2;
	s_pfCMRegisterClass = pInitStruct->pfCMRegisterClass;
	s_pfCMCreateInstance = pInitStruct->pfCMCreateInstance;
	s_pfCMCallHook = pInitStruct->pfCMCallHook;

	s_ulPhase = 0;
	s_hEventRetainGet = RTS_INVALID_HANDLE;
	s_ulNVRamAddress = 0;
	s_ulNVRamSize = 0;


#ifdef CPLUSPLUS
	INIT_LOCALS_STMT;
	if (pInitStruct->pfCMRegisterClass != NULL)
	{
		RTS_HANDLE hClass = pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CCmpSJACanDrv);
		if (hClass == RTS_INVALID_HANDLE)
			return ERR_FAILED;
	}
#endif
	return ERR_OK;
}

static int CDECL ExportFunctions(void)
/*	Export function pointers as api */
{
	/* Macro to export functions */
	EXPORT_STMT;
	return ERR_OK;
}

static int CDECL ImportFunctions(void)
/*	Get function pointers of other components */
{
	/* Macro to import functions */
	IMPORT_STMT;
	return ERR_OK;
}

static RTS_UI32 CDECL CmpGetVersion(void)
{
	return CMP_VERSION;
}

/* The eventhandler to set the retain memory in case we register one.*/
static void CDECL SJA_RetainSetEvent(EventParam* pEventParam)
{
	EVTPARAM_CmpRetainSRAM* pRetainPar = NULL;
	if(pEventParam)
		pRetainPar = (EVTPARAM_CmpRetainSRAM*)pEventParam->pParameter;	

	if(pRetainPar)
	{
		pRetainPar->pPhysicalAddress = (void*)s_ulNVRamAddress;
		pRetainPar->ulRetainSize = s_ulNVRamSize;
	}
}

void CmpSjaMpdSetRetainEvent(unsigned long ulBaseAddress, unsigned long ulSize)
{
	RTS_I32 iDisableRet = 0;
	CAL_SettgGetIntValue(COMPONENT_NAME,SJA_SETTG_DISABLE_RET,&iDisableRet,0,0);
	if(iDisableRet == 0)
		s_hEventRetainGet = CAL_EventOpen(EVT_RetainGetSRAM, CMPID_CmpRetain, NULL);
	if(s_hEventRetainGet != RTS_INVALID_HANDLE)
	{
		s_ulNVRamAddress = ulBaseAddress & 0xfffffff0;
		s_ulNVRamSize = ulSize;
		CAL_EventRegisterCallbackFunction(s_hEventRetainGet, SJA_RetainSetEvent, 0);
	}
}

RTS_I32 CmpSjaDisableChipTest(void)
{
	/* some FPGA based SJA can't do Pelican which is normally used to detect the SJA */
	RTS_I32 iDisableSjaCheck = 0;
	CAL_SettgGetIntValue(COMPONENT_NAME,SJA_SETTG_DISABLE_SJACHIPCHECK,&iDisableSjaCheck,0,0);
	return iDisableSjaCheck;
}

static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{
	switch (ulHook)
	{
		case CH_INIT_SYSTEM:

			break;
		case CH_INIT3:
			{
				unsigned short iPci = 0;
				unsigned short iPciPeak = 0;
				unsigned short iPciBrunner = 0;
				unsigned short iPciPLX9030 = 0;
				unsigned short iPciPLX9056 = 0;
				unsigned short iPciAltera = 0;
				unsigned short iPciIxxat2 = 0;/* board vendor ID 1014, PB */
				unsigned short iPciAdvantech = 0;
				unsigned short iPciAdvantech2 = 0;
				unsigned short iPciAdvantech3 = 0;
				int iDevice;
				RTS_I32 iNumDevCfg = 0;
				int iDevCfg;
				unsigned long ulH;
				RTS_I32 iH;
				char szValName[30];
				PCI_INFO pcii;
				DEV_INFO devinfo;
				CAA_ERROR eError;
				RTS_I32 iLen;
				RTS_I32 iDisablePCIScan = 0;
				RTS_BOOL bFound = 0;

				/*Search for Pci devices.*/
				/*Do all special initialization for these devices.*/
				/*Call SjaAddChipDescription for each device that shall be used from on.*/
				CAL_SettgGetIntValue(COMPONENT_NAME,SJA_SETTG_DISABLE_PCISCAN,&iDisablePCIScan,0,0);
	
				SjaInitChipDescs();

				if (!iDisablePCIScan)
				{
					int Card1 = ERR_OK;
					int Card2 = ERR_OK;
					int Card3 = ERR_OK;

					for(iDevice = 0; iDevice < 31; iDevice++)
					{
						memset(&devinfo,0,sizeof(devinfo));
						bFound = 0;
						Card1=CAL_SysPciGetCardInfo(VENDOR_ID,DEVICE_ID_PCI,iPci,&pcii);
						if (Card1 != ERR_OK){
							Card2=CAL_SysPciGetCardInfo(PCI_VENDOR_ALTERA,DEVICE_ID_PCI_F3_ALTERA,iPci,&pcii);
							if (Card2 != ERR_OK)
								Card3=CAL_SysPciGetCardInfo(PCI_VENDOR_ALTERA,DEVICE_ID_PCIEX_A2_ALTERA,iPci,&pcii);
						}
						if((Card1 == ERR_OK) || (Card2 == ERR_OK) || (Card3 == ERR_OK))
						{ /*A Automata or a Ixxat card found.*/
							iPci++;
							bFound = 1;
		    				if(pcii.usSubVendorID == SUBVENDOR_ID_AUTOMATA &&
								(pcii.usSubSystemID == SUBSYSTEM_ID_3450 || 
								pcii.usSubSystemID == SUBSYSTEM_ID_3451 ||
								pcii.usSubSystemID == SUBSYSTEM_ID_3455 || 
								pcii.usSubSystemID == SUBSYSTEM_ID_3680 ||
								pcii.usSubSystemID == SUBSYSTEM_ID_395F)) 
							{
								/*We have an Automata card here.*/
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 1;
								devinfo.iAlignment = 1;
								devinfo.bIsSecondCtrl = 0;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0xfe; /*The one and only value for the automata.*/
								switch (devinfo.usDeviceID)
								{
									case DEVICE_ID_PCI:
										devinfo.ulPhysAddr = pcii.ulBaseAddresses[2] & 0xfffffff0;
									break;
									case DEVICE_ID_PCI_F3_ALTERA:
										devinfo.ulPhysAddr = pcii.ulBaseAddresses[1] & 0xfffffff0;
									break;
									case DEVICE_ID_PCIEX_A2_ALTERA:
										devinfo.ulPhysAddr = (pcii.ulBaseAddresses[1] & 0xfffffff0) + 0x10000;
									break;
								}
								SjaAddChipDescription(&devinfo);

								if(pcii.usSubSystemID == SUBSYSTEM_ID_3451 || 
								   pcii.usSubSystemID == SUBSYSTEM_ID_3455 ||
								   pcii.usSubSystemID == SUBSYSTEM_ID_3680)
								{ /*Second channel available.*/
									memset(&devinfo,0,sizeof(devinfo));
									devinfo.hInt = RTS_INVALID_HANDLE;
									devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
									devinfo.hShmSja = RTS_INVALID_HANDLE;
									devinfo.ulXTalFrequency = 16000000;
									devinfo.usDeviceID = pcii.usDeviceID;
									devinfo.usVendorID = pcii.usVendorID;
									devinfo.usSubDeviceID = pcii.usSubSystemID;
									devinfo.usSubVendorID = pcii.usSubVendorID;
									devinfo.bMemoryMapped = 1;
									devinfo.iAlignment = 1;
									devinfo.bIsSecondCtrl = 1;
									devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
									devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
									devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
									devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
									devinfo.ulIntVec = pcii.byInterrupt;
									devinfo.ulOutputControl = 0xfe; /*The one and only value for the automata.*/

									switch (devinfo.usDeviceID)
									{
										case DEVICE_ID_PCI:
											devinfo.ulPhysAddr = pcii.ulBaseAddresses[4] & 0xfffffff0;
										break;
										case DEVICE_ID_PCI_F3_ALTERA:
											devinfo.ulPhysAddr = pcii.ulBaseAddresses[2] & 0xfffffff0;
										break;
										//case DEVICE_ID_PCIEX_A2_ALTERA:
											//devinfo.ulPhysAddr = (pcii.ulBaseAddresses[1] & 0xfffffff0) + 0x10000;
										//break;
									}
									SjaAddChipDescription(&devinfo);
									
									
									/*In case we have a 3455, we can use up to 64K NV-Ram as retain memory.*/
									/*To obtain this, we store the first one in a static var and register for the event.
										(The event is posted by the CmpRetain to get the SRAM config.)*/
									if(pcii.usSubSystemID == SUBSYSTEM_ID_3455 && CHK_EventOpen)
									{
										RTS_I32 iDisableRet = 0;
										CAL_SettgGetIntValue(COMPONENT_NAME,SJA_SETTG_DISABLE_RET,&iDisableRet,0,0);
										if(iDisableRet == 0)
											s_hEventRetainGet = CAL_EventOpen(EVT_RetainGetSRAM, CMPID_CmpRetain, NULL);
										if(s_hEventRetainGet != RTS_INVALID_HANDLE)
										{
											s_ulNVRamAddress = pcii.ulBaseAddresses[5] & 0xfffffff0;
											s_ulNVRamSize = 0x10000;
											CAL_EventRegisterCallbackFunction(s_hEventRetainGet, SJA_RetainSetEvent, 0);
										}
									}
								}
							}
							else if(pcii.usSubSystemID == SUBSYSTEM_ID_IXXAT_PCI04 &&
								pcii.usSubVendorID == SUBVENDOR_ID_IXXAT_PCI04)
							{
								/*We have an Ixxat card here.*/
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 1;
								devinfo.iAlignment = 1;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0x5e; /*The one and only value for the ixxat.*/
								devinfo.ulPhysAddr = pcii.ulBaseAddresses[2] & 0xfffffff0;
								devinfo.bHasSubCtrl = 1;
								devinfo.bIsSecondCtrl = 0;
								devinfo.bMemMapHelpCtrl = 1;
								devinfo.ulPysAddrHelp = pcii.ulBaseAddresses[0];
								SjaAddChipDescription(&devinfo);								

								/*This card always has a second controller.*/
								memset(&devinfo,0,sizeof(devinfo));
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 1;
								devinfo.iAlignment = 1;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0x5e; /*The one and only value for the ixxat.*/
								devinfo.ulPhysAddr = (pcii.ulBaseAddresses[2] + 0x200) & 0xfffffff0;
								devinfo.bHasSubCtrl = 0;
								devinfo.bIsSecondCtrl = 1;
								devinfo.bMemMapHelpCtrl = 1;
								devinfo.ulPysAddrHelp = pcii.ulBaseAddresses[0];
								SjaAddChipDescription(&devinfo);
							}
							else if(pcii.usSubVendorID == SUBVENDOR_ID_ESD && (pcii.usSubSystemID == SUBSYSTEM_ID_ESD_PCI200))
							{
								/*We have an ESD PCI200 here.*/
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 1;
								devinfo.iAlignment = 1;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0xFB; /*The one and only value for the ESD.*/
								devinfo.ulPhysAddr = pcii.ulBaseAddresses[2] & 0xfffffff0;
								devinfo.bHasSubCtrl = 1;
								devinfo.bIsSecondCtrl = 0;
								devinfo.bMemMapHelpCtrl = 1;
								devinfo.ulPysAddrHelp = pcii.ulBaseAddresses[0];
								SjaAddChipDescription(&devinfo);								

								/* Second controller: */
								memset(&devinfo,0,sizeof(devinfo));
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 1;
								devinfo.iAlignment = 1;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0xFB; /*The one and only value for the ESD.*/
								devinfo.ulPhysAddr = (pcii.ulBaseAddresses[2] + 0x100) & 0xfffffff0;
								devinfo.bHasSubCtrl = 0;
								devinfo.bIsSecondCtrl = 1;
								devinfo.bMemMapHelpCtrl = 1;
								devinfo.ulPysAddrHelp = pcii.ulBaseAddresses[0];
								SjaAddChipDescription(&devinfo);
							}
						}
						else if(CAL_SysPciGetCardInfo(VENDOR_ID,DEVICE_ID_PCI_9030, iPciPLX9030,&pcii) == ERR_OK)
						{
							iPciPLX9030++;
							bFound = 1;
						
							if(pcii.usSubVendorID == PCI_JANZ_SUBVENDOR_ID &&
								(pcii.usSubSystemID == PCI_JANZ_SUBSYSTEM_ID ||
								pcii.usSubSystemID == PCI_JANZ_SUBSYSTEM_ID_1_CHANNEL ||
								pcii.usSubSystemID == PCI_JANZ_SUBSYSTEM_ID_ONBOARD)) 	 
							{
								/*We have an Janz card here.*/
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 1;
								devinfo.bMemMapHelpCtrl = 1;
								devinfo.iAlignment = 1;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0x1a; /*The one and only value for Janz.*/
								
								devinfo.ulPhysAddr = pcii.ulBaseAddresses[2] & 0xfffffff0;
								devinfo.ulPysAddrHelp = pcii.ulBaseAddresses[4];
								SjaAddChipDescription (&devinfo);

								if((pcii.usSubSystemID == PCI_JANZ_SUBSYSTEM_ID) || 
									(pcii.usSubSystemID == PCI_JANZ_SUBSYSTEM_ID_ONBOARD))
								{ /*Second channel available.*/
									memset(&devinfo,0,sizeof(devinfo));
									devinfo.hInt = RTS_INVALID_HANDLE;
									devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
									devinfo.hShmSja = RTS_INVALID_HANDLE;
									devinfo.ulXTalFrequency = 16000000;
									devinfo.usDeviceID = pcii.usDeviceID;
									devinfo.usVendorID = pcii.usVendorID;
									devinfo.usSubDeviceID = pcii.usSubSystemID;
									devinfo.usSubVendorID = pcii.usSubVendorID;
									devinfo.bMemoryMapped = 1;
									devinfo.bMemMapHelpCtrl = 1;
									devinfo.iAlignment = 1;
									devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
									devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
									devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
									devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
									devinfo.ulIntVec = pcii.byInterrupt;
									devinfo.ulOutputControl = 0x1a; /*The one and only value for the Janz.*/
									devinfo.bMemMapHelpCtrl = 0;

									devinfo.ulPhysAddr = (pcii.ulBaseAddresses[2] & 0xfffffff0) + 0x200;
									devinfo.bIsSecondCtrl = 1;

									if (pcii.usSubSystemID == PCI_JANZ_SUBSYSTEM_ID_ONBOARD)
										devinfo.ulPysAddrHelp = pcii.ulBaseAddresses[0];
									else
										devinfo.ulPysAddrHelp = 0;

									SjaAddChipDescription(&devinfo);
								}
							}
							else if(pcii.usSubVendorID == SUBVENDOR_ID_ASEM &&
								(pcii.usSubSystemID == CAN_SUB_SYSTEM_ID_CONF1 || 
								pcii.usSubSystemID == CAN_SUB_SYSTEM_ID_CONF2 ||
								pcii.usSubSystemID == CAN_SUB_SYSTEM_ID_CONF3)) 
							{
								/*We have an Asem card here.*/
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 1;
								devinfo.bMemMapHelpCtrl = 0; /*Mapped with first channel*/
								devinfo.iAlignment = 1;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0xfe; /*The one and only value for Asem.*/
								devinfo.ulPhysAddr = pcii.ulBaseAddresses[2] & 0xfffffff0;

								devinfo.ulPysAddrHelp = (pcii.ulBaseAddresses[0] & 0xfffffff0);
								SjaAddChipDescription (&devinfo);

								if(pcii.usSubSystemID >= CAN_SUB_SYSTEM_ID_CONF1)
								{ /*Second channel available.*/
									memset(&devinfo,0,sizeof(devinfo));
									devinfo.hInt = RTS_INVALID_HANDLE;
									devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
									devinfo.hShmSja = RTS_INVALID_HANDLE;
									devinfo.ulXTalFrequency = 16000000;
									devinfo.usDeviceID = pcii.usDeviceID;
									devinfo.usVendorID = pcii.usVendorID;
									devinfo.usSubDeviceID = pcii.usSubSystemID;
									devinfo.usSubVendorID = pcii.usSubVendorID;
									devinfo.bMemoryMapped = 1;
									devinfo.iAlignment = 1;
									devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
									devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
									devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
									devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
									devinfo.ulIntVec = pcii.byInterrupt;
									devinfo.ulOutputControl = 0xfe; /*The one and only value for the Asem.*/
									devinfo.ulPhysAddr = pcii.ulBaseAddresses[4] & 0xfffffff0;
									devinfo.bIsSecondCtrl = 1;
						
									SjaAddChipDescription(&devinfo);
								}
							}
		    				else if(pcii.usSubVendorID == SUBVENDOR_ID_AUTOMATA &&
								(pcii.usSubSystemID == SUBSYSTEM_ID_3450 || 
								pcii.usSubSystemID == SUBSYSTEM_ID_3451 ||
								pcii.usSubSystemID == SUBSYSTEM_ID_3455 ||
								pcii.usSubSystemID == SUBSYSTEM_ID_3680 ||
								pcii.usSubSystemID == SUBSYSTEM_ID_395F)) 
							{
								/*We have an Automata card here. New device ID, as they changed the from 9052 to 9030.*/
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 1;
								devinfo.iAlignment = 1;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0xfe; /*The one and only value for the automata.*/
								switch (devinfo.usDeviceID)
								{
									case DEVICE_ID_PCI_9030:
										devinfo.ulPhysAddr = pcii.ulBaseAddresses[2] & 0xfffffff0;
									break;
									case DEVICE_ID_PCI_F3_ALTERA:
										devinfo.ulPhysAddr = pcii.ulBaseAddresses[1] & 0xfffffff0;
									break;
									case DEVICE_ID_PCIEX_A2_ALTERA:
										devinfo.ulPhysAddr = (pcii.ulBaseAddresses[1] & 0xfffffff0) + 0x10000;
									break;
								}

								//devinfo.ulPhysAddr = pcii.ulBaseAddresses[2] & 0xfffffff0;
								SjaAddChipDescription(&devinfo);

								if(pcii.usSubSystemID == SUBSYSTEM_ID_3451 || 
								   pcii.usSubSystemID == SUBSYSTEM_ID_3455 ||
								   pcii.usSubSystemID == SUBSYSTEM_ID_3680)
								{ /*Second channel available.*/
									memset(&devinfo,0,sizeof(devinfo));
									devinfo.hInt = RTS_INVALID_HANDLE;
									devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
									devinfo.hShmSja = RTS_INVALID_HANDLE;
									devinfo.ulXTalFrequency = 16000000;
									devinfo.usDeviceID = pcii.usDeviceID;
									devinfo.usVendorID = pcii.usVendorID;
									devinfo.usSubDeviceID = pcii.usSubSystemID;
									devinfo.usSubVendorID = pcii.usSubVendorID;
									devinfo.bMemoryMapped = 1;
									devinfo.iAlignment = 1;
									devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
									devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
									devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
									devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
									devinfo.ulIntVec = pcii.byInterrupt;
									devinfo.ulOutputControl = 0xfe; /*The one and only value for the automata.*/
									devinfo.bIsSecondCtrl = 1;
									switch (devinfo.usDeviceID)
									{
										case DEVICE_ID_PCI_9030:
											devinfo.ulPhysAddr = pcii.ulBaseAddresses[4] & 0xfffffff0;
										break;
										case DEVICE_ID_PCI_F3_ALTERA:
											devinfo.ulPhysAddr = pcii.ulBaseAddresses[2] & 0xfffffff0;
										break;
										case DEVICE_ID_PCIEX_A2_ALTERA:
											devinfo.ulPhysAddr = (pcii.ulBaseAddresses[1] & 0xfffffff0) + 0x10000;
										break;
									}

								//	devinfo.ulPhysAddr = pcii.ulBaseAddresses[4] & 0xfffffff0;
									SjaAddChipDescription(&devinfo);								
								}
							}
							else if((pcii.usSubVendorID == SUBVENDOR_ID_ESD) && ((pcii.usSubSystemID == SUBSYSTEM_ID_ESD_CPCI200) || (pcii.usSubSystemID == SUBSYSTEM_ID_ESD_104200)))
							{
								/*We have an ESD CPCI200/104-200 here.*/
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 1;
								devinfo.iAlignment = 1;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0xFB; /*The one and only value for the ESD.*/
								devinfo.ulPhysAddr = pcii.ulBaseAddresses[2] & 0xfffffff0;
								devinfo.bHasSubCtrl = 1;
								devinfo.bIsSecondCtrl = 0;
								devinfo.bMemMapHelpCtrl = 1;
								devinfo.ulPysAddrHelp = pcii.ulBaseAddresses[0];
								SjaAddChipDescription(&devinfo);								

								/* Second controller: */
								memset(&devinfo,0,sizeof(devinfo));
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 1;
								devinfo.iAlignment = 1;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0xFB; /*The one and only value for the ESD.*/
								devinfo.ulPhysAddr = (pcii.ulBaseAddresses[2] + 0x100) & 0xfffffff0;
								devinfo.bHasSubCtrl = 0;
								devinfo.bIsSecondCtrl = 1;
								devinfo.bMemMapHelpCtrl = 1;
								devinfo.ulPysAddrHelp = pcii.ulBaseAddresses[0];
								SjaAddChipDescription(&devinfo);
							}
						}
						else if(CAL_SysPciGetCardInfo(VENDOR_ID_PEAK,DEVICE_ID_PEAK,iPciPeak,&pcii) == ERR_OK ||
								CAL_SysPciGetCardInfo(VENDOR_ID_PEAK,DEVICE_ID_PEAK2,iPciPeak,&pcii) == ERR_OK ||
								CAL_SysPciGetCardInfo(VENDOR_ID_PEAK,DEVICE_ID_PEAK3,iPciPeak,&pcii) == ERR_OK ||
								CAL_SysPciGetCardInfo(VENDOR_ID_PEAK,DEVICE_ID_PEAK4,iPciPeak,&pcii) == ERR_OK ||
								CAL_SysPciGetCardInfo(VENDOR_ID_PEAK,DEVICE_ID_PEAK5,iPciPeak,&pcii) == ERR_OK ||
								CAL_SysPciGetCardInfo(VENDOR_ID_PEAK,DEVICE_ID_PEAK6,iPciPeak,&pcii) == ERR_OK ||
								CAL_SysPciGetCardInfo(VENDOR_ID_PEAK,DEVICE_ID_PEAK7,iPciPeak,&pcii) == ERR_OK ||
								CAL_SysPciGetCardInfo(VENDOR_ID_PEAK,DEVICE_ID_PEAK8,iPciPeak,&pcii) == ERR_OK)
						{ /*A peak card found. TODO, but will not happen: heterogenous peak cards in one machine will not be all detected.*/
							iPciPeak++;
							bFound = 1;

							devinfo.hInt = RTS_INVALID_HANDLE;
							devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
							devinfo.hShmSja = RTS_INVALID_HANDLE;
							devinfo.ulXTalFrequency = 16000000;
							devinfo.usDeviceID = pcii.usDeviceID;
							devinfo.usVendorID = pcii.usVendorID;
							devinfo.usSubDeviceID = pcii.usSubSystemID;
							devinfo.usSubVendorID = pcii.usSubVendorID;
							devinfo.bMemoryMapped = 1;
							devinfo.iAlignment = 4;
							devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
							devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
							devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
							devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
							devinfo.ulIntVec = pcii.byInterrupt;
							devinfo.ulOutputControl = 0x1a; /*The one and only value for the Peak.*/
							devinfo.ulPhysAddr = pcii.ulBaseAddresses[1] & 0xfffffff0;
							
							if(pcii.usSubSystemID > 3)
								devinfo.bHasSubCtrl = 1;
							else
								devinfo.bHasSubCtrl = 0;

							devinfo.bIsSecondCtrl = 0;
							devinfo.bMemMapHelpCtrl = 1;
							devinfo.ulPysAddrHelp = pcii.ulBaseAddresses[0];
							SjaAddChipDescription(&devinfo);								
							if(pcii.usSubSystemID > 3)
							{ /*Second channel available.*/
								memset(&devinfo,0,sizeof(devinfo));
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 1;
								devinfo.iAlignment = 4;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0x1a; /*The one and only value for the Peak.*/
								devinfo.ulPhysAddr = (pcii.ulBaseAddresses[1] + 0x400) & 0xfffffff0;
								devinfo.bHasSubCtrl = 0;
								devinfo.bIsSecondCtrl = 1;
								devinfo.bMemMapHelpCtrl = 1;
								devinfo.ulPysAddrHelp = pcii.ulBaseAddresses[0];
								SjaAddChipDescription(&devinfo);								
							}
							if(pcii.usSubSystemID >= 0x10)
							{ /*Third channel available.*/
								memset(&devinfo,0,sizeof(devinfo));
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 1;
								devinfo.iAlignment = 4;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0x1a; /*The one and only value for the Peak.*/
								devinfo.ulPhysAddr = (pcii.ulBaseAddresses[1] + 0x800) & 0xfffffff0;
								devinfo.bHasSubCtrl = 0;
								devinfo.bIsSecondCtrl = 2;
								devinfo.bMemMapHelpCtrl = 1;
								devinfo.ulPysAddrHelp = pcii.ulBaseAddresses[0];
								SjaAddChipDescription(&devinfo);								
							}
							if(pcii.usSubSystemID >= 0x12)
							{ /*Fourth channel available.*/
								memset(&devinfo,0,sizeof(devinfo));
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 1;
								devinfo.iAlignment = 4;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0x1a; /*The one and only value for the Peak.*/
								devinfo.ulPhysAddr = (pcii.ulBaseAddresses[1] + 0xc00) & 0xfffffff0;
								devinfo.bHasSubCtrl = 0;
								devinfo.bIsSecondCtrl = 3;
								devinfo.bMemMapHelpCtrl = 1;
								devinfo.ulPysAddrHelp = pcii.ulBaseAddresses[0];
								SjaAddChipDescription(&devinfo);								
							}
						}
						else if(CAL_SysPciGetCardInfo(PCI_VENDOR_BEH,PCI_DEVICE_BELB,iPciBrunner,&pcii) == ERR_OK)
						{ /*A peak card found.*/
							iPciBrunner++;
							bFound = 1;

							devinfo.hInt = RTS_INVALID_HANDLE;
							devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
							devinfo.hShmSja = RTS_INVALID_HANDLE;
							devinfo.ulXTalFrequency = 24000000;
							devinfo.usDeviceID = pcii.usDeviceID;
							devinfo.usVendorID = pcii.usVendorID;
							devinfo.usSubDeviceID = pcii.usSubSystemID;
							devinfo.usSubVendorID = pcii.usSubVendorID;
							devinfo.bMemoryMapped = 1;
							devinfo.iAlignment = 4;
							devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
							devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
							devinfo.ulIntVec = pcii.byInterrupt;
							devinfo.ulOutputControl = 0x1a; /*The one and only value for the Peak.*/
							devinfo.ulPhysAddr = pcii.ulBaseAddresses[1] & 0xfffffff0;
							
							devinfo.bHasSubCtrl = 1;
							devinfo.bIsSecondCtrl = 0;
							devinfo.bMemMapHelpCtrl = 1;
							devinfo.ulPysAddrHelp = pcii.ulBaseAddresses[0];
							SjaAddChipDescription(&devinfo);

							{ /*Second channel always available.*/
								memset(&devinfo,0,sizeof(devinfo));
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 24000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 1;
								devinfo.iAlignment = 4;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0x1a; /*The one and only value for the Peak.*/
								devinfo.ulPhysAddr = pcii.ulBaseAddresses[1] & 0xfffffff0;
								devinfo.bHasSubCtrl = 0;
								devinfo.bIsSecondCtrl = 1;
								devinfo.bMemMapHelpCtrl = 1;
								devinfo.ulPysAddrHelp = pcii.ulBaseAddresses[0];
								SjaAddChipDescription(&devinfo);								
							}
						}
						else if(CAL_SysPciGetCardInfo(PCI_VENDOR_ALTERA,PCI_DEVICE_GROSSENB,iPciAltera,&pcii) == ERR_OK)
						{ /*Grossenbacher card (NUM-HW) found.*/
							iPciAltera++;
							bFound = 1;

							if(pcii.usSubVendorID == PCI_SUBVENDOR_ALTERA &&
								pcii.usSubSystemID == PCI_SUBDEVICE_GROSSENB)
							{
								/*We have an Grossenbacher card here.*/
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 1;
								devinfo.iAlignment = 4;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0x1a; /*Taken from the NUM cfgfile.*/
								devinfo.ulPhysAddr = pcii.ulBaseAddresses[1] & 0xfffffff0;
								devinfo.bHasSubCtrl = 1;
								devinfo.bIsSecondCtrl = 0;
								devinfo.bMemMapHelpCtrl = 1;
								devinfo.ulPysAddrHelp = pcii.ulBaseAddresses[0];

								devinfo.ulNvRamPhysAddr = pcii.ulBaseAddresses[2] + 0x2000;
								devinfo.ulNvRamSize = 0xE000;

								SjaAddChipDescription(&devinfo);

								/*This card always has a second controller.*/
								memset(&devinfo,0,sizeof(devinfo));
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 1;
								devinfo.iAlignment = 4;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0x1a; /*Taken from the NUM cfgfile.*/
								devinfo.ulPhysAddr = pcii.ulBaseAddresses[1] & 0xfffffff0;
								devinfo.ulPhysAddr += 0x200;
								devinfo.bHasSubCtrl = 0;
								devinfo.bIsSecondCtrl = 1;
								devinfo.bMemMapHelpCtrl = 1;
								devinfo.ulPysAddrHelp = pcii.ulBaseAddresses[0];
								SjaAddChipDescription(&devinfo);
							}
						}

						else if(CAL_SysPciGetCardInfo(VENDOR_ID_IXXAT_2,DEVICE_ID_PCI_IXXAT_2,iPciIxxat2,&pcii) == ERR_OK) 
						{
							iPciIxxat2++;
							bFound = 1;
							if (pcii.usDeviceID == DEVICE_ID_PCI_IXXAT_2 && pcii.usSubSystemID == SUBSYSTEM_ID_IXXAT_2)
							{
								/*We have an Ixxat card here.*/
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 1;
								devinfo.iAlignment = 1;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0x1a; /*The one and only value for the ixxat.*/
								devinfo.ulPhysAddr = pcii.ulBaseAddresses[2] & 0xfffffff0;
								devinfo.bHasSubCtrl = 1;
								devinfo.bIsSecondCtrl = 0;
								devinfo.bMemMapHelpCtrl = 1;
								devinfo.ulPysAddrHelp = pcii.ulBaseAddresses[0];
								SjaAddChipDescription(&devinfo);								

								/*This card always has a second controller.*/
								memset(&devinfo,0,sizeof(devinfo));
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 1;
								devinfo.iAlignment = 1;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0x1a; /*The one and only value for the ixxat.*/
								devinfo.ulPhysAddr = (pcii.ulBaseAddresses[2] + 0x200) & 0xfffffff0;
								devinfo.bHasSubCtrl = 0;
								devinfo.bIsSecondCtrl = 1;
								devinfo.bMemMapHelpCtrl = 1;
								devinfo.ulPysAddrHelp = pcii.ulBaseAddresses[0];
								SjaAddChipDescription(&devinfo);
							}
						}
						else if(CAL_SysPciGetCardInfo(VENDOR_ID,DEVICE_ID_PCI_9056, iPciPLX9056,&pcii) == ERR_OK)
						{
							iPciPLX9056++;
							bFound = 1;
							if((pcii.usSubVendorID == SUBVENDOR_ID_ESD) && 
								((pcii.usSubSystemID == SUBSYSTEM_ID_ESD_PCI266) || 
								(pcii.usSubSystemID == SUBSYSTEM_ID_ESD_PEX266) ||
								(pcii.usSubSystemID == SUBSYSTEM_ID_ESD_PMC266)
								))
							{
								/*We have an ESD PCI266/PEX266/PMC266 here.*/
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 1;
								devinfo.iAlignment = 1;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0xFB; /*The one and only value for the ESD.*/
								devinfo.ulPhysAddr = pcii.ulBaseAddresses[2] & 0xfffffff0;
								devinfo.bHasSubCtrl = 1;
								devinfo.bIsSecondCtrl = 0;
								devinfo.bMemMapHelpCtrl = 1;
								devinfo.ulPysAddrHelp = pcii.ulBaseAddresses[0];
								SjaAddChipDescription(&devinfo);								

								/* Second controller: */
								memset(&devinfo,0,sizeof(devinfo));
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 1;
								devinfo.iAlignment = 1;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0xFB; /*The one and only value for the ESD.*/
								devinfo.ulPhysAddr = (pcii.ulBaseAddresses[2] + 0x100) & 0xfffffff0;
								devinfo.bHasSubCtrl = 0;
								devinfo.bIsSecondCtrl = 1;
								devinfo.bMemMapHelpCtrl = 1;
								devinfo.ulPysAddrHelp = pcii.ulBaseAddresses[0];
								SjaAddChipDescription(&devinfo);
							}
						}

						else if(CAL_SysPciGetCardInfo(PCI_VENDOR_ADAM_5095,PCI_DEVICE_ADAM_5095,iPciAdvantech,&pcii) == ERR_OK)
						{ /*Advantech card (ADAM 5095 for use with 5560) found.*/
							iPciAdvantech++;
							bFound = 1;

							if(pcii.usSubVendorID == PCI_SUBVENDOR_ADAM_5095 &&
								pcii.usSubSystemID == PCI_SUBDEVICE_ADAM_5095)
							{
								/*We have an Advantech ADAM 5095 card here.*/
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 0;
								devinfo.iAlignment = 1;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0xfa;
								devinfo.ulPhysAddr = pcii.ulBaseAddresses[1] & 0xfffffff0;/* first controller */
								devinfo.bHasSubCtrl = 1;
								devinfo.bIsSecondCtrl = 0;
								devinfo.bMemMapHelpCtrl = 1;
								devinfo.ulPysAddrHelp = pcii.ulBaseAddresses[0];

								devinfo.ulNvRamPhysAddr = 0; 
								devinfo.ulNvRamSize = 0;

								SjaAddChipDescription(&devinfo);

								/*This card always has a second controller.*/
								memset(&devinfo,0,sizeof(devinfo));
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 0;
								devinfo.iAlignment = 1;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0xfa;
								devinfo.ulPhysAddr = pcii.ulBaseAddresses[2] & 0xfffffff0;/* second controller */
								devinfo.bHasSubCtrl = 0;
								devinfo.bIsSecondCtrl = 1;
								devinfo.bMemMapHelpCtrl = 1;
								devinfo.ulPysAddrHelp = pcii.ulBaseAddresses[0];
								SjaAddChipDescription(&devinfo);
							}
						}
						else if(CAL_SysPciGetCardInfo(PCI_VENDOR_PCM26D2CA,PCI_DEVICE_PCM26D2CA,iPciAdvantech2,&pcii) == ERR_OK)
						{ /*Advantech card (ADAM 5095 for use with 5560) found.*/
							iPciAdvantech2++;
							bFound = 1;

							if(pcii.usSubVendorID == PCI_SUBVENDOR_PCM26D2CA &&
								pcii.usSubSystemID == PCI_SUBDEVICE_PCM26D2CA)
							{
								CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0x1234, "CmpSJACanDrv: PCM26D2CA found.");
								/*We have an Advantech PCM26D2CA card here.*/
								memset(&devinfo,0,sizeof(devinfo));
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 1;
								devinfo.iAlignment = 4;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0xfa;
								devinfo.ulPhysAddr = pcii.ulBaseAddresses[0] & 0xfffffff0;/* first controller */
								devinfo.bHasSubCtrl = 1;
								devinfo.bIsSecondCtrl = 0;
								devinfo.bMemMapHelpCtrl = 1;
								devinfo.ulPysAddrHelp = 0; /*pcii.ulBaseAddresses[1];*/

								SjaAddChipDescription(&devinfo);

								/*This card always has a second controller.*/
								memset(&devinfo,0,sizeof(devinfo));
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 1;
								devinfo.iAlignment = 4;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0xfa;
								devinfo.ulPhysAddr = (pcii.ulBaseAddresses[0] & 0xfffffff0) + 0x400;/* second controller */
								devinfo.bHasSubCtrl = 0;
								devinfo.bIsSecondCtrl = 1;
								devinfo.bMemMapHelpCtrl = 1;
								devinfo.ulPysAddrHelp = 0; /*pcii.ulBaseAddresses[1];*/
								SjaAddChipDescription(&devinfo);
							}
						}
						else if(CAL_SysPciGetCardInfo(PCI_VENDOR_PCM26D2CA,PCI_DEVICE_PCM26D2CA_2,iPciAdvantech3,&pcii) == ERR_OK)
						{ /*Advantech card (ADAM 5095 for use with 5560) found.*/
							iPciAdvantech3++;
							bFound = 1;

							if(pcii.usSubVendorID == PCI_SUBVENDOR_PCM26D2CA &&
								pcii.usSubSystemID == PCI_SUBDEVICE_PCM26D2CA_2)
							{
								CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0x1234, "CmpSJACanDrv: PCM26D2CA_2 found.");
								/*We have an Advantech PCM26D2CA card here.*/
								memset(&devinfo,0,sizeof(devinfo));
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 1;
								devinfo.iAlignment = 4;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0xfa;
								devinfo.ulPhysAddr = pcii.ulBaseAddresses[0] & 0xfffffff0;/* first controller */
								devinfo.bHasSubCtrl = 1;
								devinfo.bIsSecondCtrl = 0;
								devinfo.bMemMapHelpCtrl = 1;
								devinfo.ulPysAddrHelp = 0; /*pcii.ulBaseAddresses[1];*/

								SjaAddChipDescription(&devinfo);

								/*This card always has a second controller.*/
								memset(&devinfo,0,sizeof(devinfo));
								devinfo.hInt = RTS_INVALID_HANDLE;
								devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
								devinfo.hShmSja = RTS_INVALID_HANDLE;
								devinfo.ulXTalFrequency = 16000000;
								devinfo.usDeviceID = pcii.usDeviceID;
								devinfo.usVendorID = pcii.usVendorID;
								devinfo.usSubDeviceID = pcii.usSubSystemID;
								devinfo.usSubVendorID = pcii.usSubVendorID;
								devinfo.bMemoryMapped = 1;
								devinfo.iAlignment = 4;
								devinfo.ulBusNr = (unsigned short)pcii.ulBusNr;
								devinfo.ulSlotNr = pcii.SlotNr.u.AsULONG;
								devinfo.ulDevice = pcii.SlotNr.u.bits.DeviceNumber;
								devinfo.ulFunction = pcii.SlotNr.u.bits.FunctionNumber;
								devinfo.ulIntVec = pcii.byInterrupt;
								devinfo.ulOutputControl = 0xfa;
								devinfo.ulPhysAddr = (pcii.ulBaseAddresses[0] & 0xfffffff0) + 0x400;/* second controller */
								devinfo.bHasSubCtrl = 0;
								devinfo.bIsSecondCtrl = 1;
								devinfo.bMemMapHelpCtrl = 1;
								devinfo.ulPysAddrHelp = 0; /*pcii.ulBaseAddresses[1];*/
								SjaAddChipDescription(&devinfo);
							}
						}

						else
						{
							if (!bFound)
								break; /*No card found.*/
						}
					}
				}

				/*Now search for all configured devices.(Read settings from cfg-file.)*/
				CAL_SettgGetIntValue(COMPONENT_NAME,SJA_SETTG_NUM_DEVICES,&iNumDevCfg,0,0);
				for(iDevCfg = 0; iDevCfg < iNumDevCfg; iDevCfg++)
				{
					memset(&devinfo,0,sizeof(devinfo));
					devinfo.hInt = RTS_INVALID_HANDLE;
					devinfo.hShmHelpCtrl = RTS_INVALID_HANDLE;
					devinfo.hShmSja = RTS_INVALID_HANDLE;

					CAL_CMUtlsnprintf(szValName, sizeof(szValName), SJA_SETTG_ADDR,iDevCfg);
					CAL_SettgGetIntValue(COMPONENT_NAME,szValName,&iH,0,0);
					ulH = (unsigned long)iH;
					devinfo.ulPhysAddr = ulH;

					CAL_CMUtlsnprintf(szValName, sizeof(szValName), SJA_SETTG_MEMMAP,iDevCfg);
					CAL_SettgGetIntValue(COMPONENT_NAME,szValName,&iH,0,0);
					ulH = (unsigned long)iH;
					devinfo.bMemoryMapped = (unsigned long)(ulH != 0);

					CAL_CMUtlsnprintf(szValName, sizeof(szValName), SJA_SETTG_INT,iDevCfg);
					CAL_SettgGetIntValue(COMPONENT_NAME,szValName,&iH,0,0);
					ulH = (unsigned long)iH;
					devinfo.ulIntVec = (unsigned short)ulH;

					/*0 is LevelSensitiv, 1 is Latched.*/
					CAL_CMUtlsnprintf(szValName, sizeof(szValName), SJA_SETTG_INTEDGE,iDevCfg);
					CAL_SettgGetIntValue(COMPONENT_NAME,szValName,&iH,0,0);
					ulH = (unsigned long)iH;
					devinfo.ulIntEdgeTrig = (unsigned short)ulH;

					CAL_CMUtlsnprintf(szValName, sizeof(szValName), SJA_SETTG_XTAL,iDevCfg);
					CAL_SettgGetIntValue(COMPONENT_NAME,szValName,&iH,16000000,0);
					ulH = (unsigned long)iH;
					devinfo.ulXTalFrequency = ulH;

					CAL_CMUtlsnprintf(szValName, sizeof(szValName), SJA_SETTG_BUSTYPE,iDevCfg);
					CAL_SettgGetIntValue(COMPONENT_NAME,szValName,&iH,3,0);
					ulH = (unsigned long)iH;
					devinfo.ulBusType = (unsigned short)ulH;

					CAL_CMUtlsnprintf(szValName, sizeof(szValName), SJA_SETTG_ALIGNMENT,iDevCfg);
					CAL_SettgGetIntValue(COMPONENT_NAME,szValName,&iH,1,0);
					devinfo.iAlignment = iH;

					CAL_CMUtlsnprintf(szValName, sizeof(szValName), SJA_SETTG_OCTRL,iDevCfg);
					CAL_SettgGetIntValue(COMPONENT_NAME,szValName,&iH,0x1a,0);
					ulH = (unsigned long)iH;
					devinfo.ulOutputControl = ulH;

					iLen = sizeof(devinfo.szName);
					CAL_CMUtlsnprintf(szValName, sizeof(szValName), SJA_SETTG_NAME,iDevCfg);
					CAL_SettgGetStringValue(COMPONENT_NAME,szValName,devinfo.szName,&iLen,"SjaDefName",0);
					devinfo.szName[sizeof(devinfo.szName)-1] = '\0';
					
					CAL_CMUtlsnprintf(szValName, sizeof(szValName), SJA_SETTG_PORTADDR,iDevCfg);
					CAL_SettgGetIntValue(COMPONENT_NAME,szValName,&iH,0x0,0);
					ulH = (unsigned long)iH;
					devinfo.ulPortAddr = ulH;

					CAL_CMUtlsnprintf(szValName, sizeof(szValName), SJA_SETTG_PORTVAL,iDevCfg);
					CAL_SettgGetIntValue(COMPONENT_NAME,szValName,&iH,0x0,0);
					ulH = (unsigned long)iH;
					devinfo.ulPortVal = ulH;

					SjaAddChipDescription(&devinfo);
				}

				
				/*Call init for all the registered devices.*/
				SjaInitAllControllersForUse();

				/*Now register all the nets at CL2.*/
				eError = SJA_CanMiniDriver_Setup();
				if(eError != CL2_NO_ERROR)
				{
					return ERR_PENDING;
				}
			}
			break;
		case CH_INIT_DONE:
			break;
		case CH_INIT_TASKS:
			break;
		case CH_INIT_COMM:
			break;

		/* Cyclic */
		case CH_COMM_CYCLE:
			{
				SjaHandleLEDs(&s_ulPhase);
				break;
			}
		case CH_EXIT_COMM:
			break;
		case CH_EXIT_TASKS:
			break;
		case CH_PRE_EXIT:
			break;
		case CH_EXIT3:
			SJA_CanMiniDriver_Dispose();
			break;
		case CH_EXIT:
		{
			EXIT_STMT;
			break;
		}
		case CH_EXIT_SYSTEM:
			break;
		default:
			break;
	}
	return 0;
}
				
#endif /* CAA_CL2 */
#endif /* CAALib */
