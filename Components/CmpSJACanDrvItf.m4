SET_INTERFACE_NAME(`CmpSJACanDrv')

#include "CmpItf.h"

typedef struct _devinfotag_
{
    unsigned char* pCanRegs; /*This may be a port address. See next member.*/
	int bMemoryMapped; /*Is the SJA memory mapped or portaddressed? (1 for memorymapped.)*/
	int iAlignment; /*Normally 1, the byteoffset to the next SJA-register.*/
	unsigned long ulXTalFrequency; /*The frequency for the clockinput of the SJA.*/
	unsigned long ulOutputControl; /*Configured output control value. Specific for the hardware.*/
	unsigned long ulPhysAddr; /*Physical address or portaddress of SJA.*/
	CAA_HANDLE hInt; /*Handle for the interrupt.*/

	/*Helpers for using the devices.*/
	CAA_HANDLE hShmSja; /*In case of mem mapped SJA registers this is the handle to the Shm.*/

	/*The following members are helpfull for Pci-devices.*/
	unsigned short usVendorID;
	unsigned short usDeviceID;
	unsigned short usSubVendorID;
	unsigned short usSubDeviceID;
	unsigned short ulBusNr;
	unsigned short ulDevice;
	unsigned short ulFunction;
	unsigned short ulIntVec;
	unsigned short ulIntEdgeTrig;
	unsigned short ulBusType;
	unsigned long ulSlotNr;
	int bHasSubCtrl;
	int bIsSecondCtrl;
	unsigned char* pHelpCtrl;
	unsigned long ulPysAddrHelp;
	int bMemMapHelpCtrl;
	CAA_HANDLE hShmHelpCtrl;
	unsigned long ulPortAddr;
	unsigned long ulPortVal;
	int bDetected;
	unsigned long ulNvRamPhysAddr;
	unsigned long ulNvRamSize;

	/*The name is only used for some platforms that need a string to map a memory. (Linux)*/
	char szName[20];
	unsigned long ulLEDTimestamp;
	CL2I_BYTE byIndicator;

}DEV_INFO;

#ifdef __cplusplus
extern "C" {
#endif

DEF_ITF_API(`int',`CDECL',`SJA_CanMiniDriver_Setup',`(void)')
DEF_ITF_API(`int',`CDECL',`SJA_CanMiniDriver_Dispose',`(void)')
DEF_ITF_API(`DEV_INFO*',`CDECL',`SJA_GetDeviceDescription',`(int iDev)')

#ifdef __cplusplus
}
#endif
