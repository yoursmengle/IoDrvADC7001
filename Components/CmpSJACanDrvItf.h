 
	
	
#ifndef _CMPSJACANDRVITF_H_
#define _CMPSJACANDRVITF_H_

#include "CmpStd.h"

 

 




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

int CDECL SJA_CanMiniDriver_Setup(void);
typedef int (CDECL * PFSJA_CANMINIDRIVER_SETUP) (void);
#if defined(CMPSJACANDRV_NOTIMPLEMENTED) || defined(SJA_CANMINIDRIVER_SETUP_NOTIMPLEMENTED)
	#define USE_SJA_CanMiniDriver_Setup
	#define EXT_SJA_CanMiniDriver_Setup
	#define GET_SJA_CanMiniDriver_Setup(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SJA_CanMiniDriver_Setup()  (int)ERR_NOTIMPLEMENTED
	#define CHK_SJA_CanMiniDriver_Setup  FALSE
	#define EXP_SJA_CanMiniDriver_Setup  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SJA_CanMiniDriver_Setup
	#define EXT_SJA_CanMiniDriver_Setup
	#define GET_SJA_CanMiniDriver_Setup(fl)  CAL_CMGETAPI( "SJA_CanMiniDriver_Setup" ) 
	#define CAL_SJA_CanMiniDriver_Setup  SJA_CanMiniDriver_Setup
	#define CHK_SJA_CanMiniDriver_Setup  TRUE
	#define EXP_SJA_CanMiniDriver_Setup  CAL_CMEXPAPI( "SJA_CanMiniDriver_Setup" ) 
#elif defined(MIXED_LINK) && !defined(CMPSJACANDRV_EXTERNAL)
	#define USE_SJA_CanMiniDriver_Setup
	#define EXT_SJA_CanMiniDriver_Setup
	#define GET_SJA_CanMiniDriver_Setup(fl)  CAL_CMGETAPI( "SJA_CanMiniDriver_Setup" ) 
	#define CAL_SJA_CanMiniDriver_Setup  SJA_CanMiniDriver_Setup
	#define CHK_SJA_CanMiniDriver_Setup  TRUE
	#define EXP_SJA_CanMiniDriver_Setup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SJA_CanMiniDriver_Setup", (RTS_UINTPTR)SJA_CanMiniDriver_Setup, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSJACanDrvSJA_CanMiniDriver_Setup
	#define EXT_CmpSJACanDrvSJA_CanMiniDriver_Setup
	#define GET_CmpSJACanDrvSJA_CanMiniDriver_Setup  ERR_OK
	#define CAL_CmpSJACanDrvSJA_CanMiniDriver_Setup pICmpSJACanDrv->ISJA_CanMiniDriver_Setup
	#define CHK_CmpSJACanDrvSJA_CanMiniDriver_Setup (pICmpSJACanDrv != NULL)
	#define EXP_CmpSJACanDrvSJA_CanMiniDriver_Setup  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SJA_CanMiniDriver_Setup
	#define EXT_SJA_CanMiniDriver_Setup
	#define GET_SJA_CanMiniDriver_Setup(fl)  CAL_CMGETAPI( "SJA_CanMiniDriver_Setup" ) 
	#define CAL_SJA_CanMiniDriver_Setup pICmpSJACanDrv->ISJA_CanMiniDriver_Setup
	#define CHK_SJA_CanMiniDriver_Setup (pICmpSJACanDrv != NULL)
	#define EXP_SJA_CanMiniDriver_Setup  CAL_CMEXPAPI( "SJA_CanMiniDriver_Setup" ) 
#else /* DYNAMIC_LINK */
	#define USE_SJA_CanMiniDriver_Setup  PFSJA_CANMINIDRIVER_SETUP pfSJA_CanMiniDriver_Setup;
	#define EXT_SJA_CanMiniDriver_Setup  extern PFSJA_CANMINIDRIVER_SETUP pfSJA_CanMiniDriver_Setup;
	#define GET_SJA_CanMiniDriver_Setup(fl)  s_pfCMGetAPI2( "SJA_CanMiniDriver_Setup", (RTS_VOID_FCTPTR *)&pfSJA_CanMiniDriver_Setup, (fl), 0, 0)
	#define CAL_SJA_CanMiniDriver_Setup  pfSJA_CanMiniDriver_Setup
	#define CHK_SJA_CanMiniDriver_Setup  (pfSJA_CanMiniDriver_Setup != NULL)
	#define EXP_SJA_CanMiniDriver_Setup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SJA_CanMiniDriver_Setup", (RTS_UINTPTR)SJA_CanMiniDriver_Setup, 0, 0) 
#endif



int CDECL SJA_CanMiniDriver_Dispose(void);
typedef int (CDECL * PFSJA_CANMINIDRIVER_DISPOSE) (void);
#if defined(CMPSJACANDRV_NOTIMPLEMENTED) || defined(SJA_CANMINIDRIVER_DISPOSE_NOTIMPLEMENTED)
	#define USE_SJA_CanMiniDriver_Dispose
	#define EXT_SJA_CanMiniDriver_Dispose
	#define GET_SJA_CanMiniDriver_Dispose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SJA_CanMiniDriver_Dispose()  (int)ERR_NOTIMPLEMENTED
	#define CHK_SJA_CanMiniDriver_Dispose  FALSE
	#define EXP_SJA_CanMiniDriver_Dispose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SJA_CanMiniDriver_Dispose
	#define EXT_SJA_CanMiniDriver_Dispose
	#define GET_SJA_CanMiniDriver_Dispose(fl)  CAL_CMGETAPI( "SJA_CanMiniDriver_Dispose" ) 
	#define CAL_SJA_CanMiniDriver_Dispose  SJA_CanMiniDriver_Dispose
	#define CHK_SJA_CanMiniDriver_Dispose  TRUE
	#define EXP_SJA_CanMiniDriver_Dispose  CAL_CMEXPAPI( "SJA_CanMiniDriver_Dispose" ) 
#elif defined(MIXED_LINK) && !defined(CMPSJACANDRV_EXTERNAL)
	#define USE_SJA_CanMiniDriver_Dispose
	#define EXT_SJA_CanMiniDriver_Dispose
	#define GET_SJA_CanMiniDriver_Dispose(fl)  CAL_CMGETAPI( "SJA_CanMiniDriver_Dispose" ) 
	#define CAL_SJA_CanMiniDriver_Dispose  SJA_CanMiniDriver_Dispose
	#define CHK_SJA_CanMiniDriver_Dispose  TRUE
	#define EXP_SJA_CanMiniDriver_Dispose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SJA_CanMiniDriver_Dispose", (RTS_UINTPTR)SJA_CanMiniDriver_Dispose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSJACanDrvSJA_CanMiniDriver_Dispose
	#define EXT_CmpSJACanDrvSJA_CanMiniDriver_Dispose
	#define GET_CmpSJACanDrvSJA_CanMiniDriver_Dispose  ERR_OK
	#define CAL_CmpSJACanDrvSJA_CanMiniDriver_Dispose pICmpSJACanDrv->ISJA_CanMiniDriver_Dispose
	#define CHK_CmpSJACanDrvSJA_CanMiniDriver_Dispose (pICmpSJACanDrv != NULL)
	#define EXP_CmpSJACanDrvSJA_CanMiniDriver_Dispose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SJA_CanMiniDriver_Dispose
	#define EXT_SJA_CanMiniDriver_Dispose
	#define GET_SJA_CanMiniDriver_Dispose(fl)  CAL_CMGETAPI( "SJA_CanMiniDriver_Dispose" ) 
	#define CAL_SJA_CanMiniDriver_Dispose pICmpSJACanDrv->ISJA_CanMiniDriver_Dispose
	#define CHK_SJA_CanMiniDriver_Dispose (pICmpSJACanDrv != NULL)
	#define EXP_SJA_CanMiniDriver_Dispose  CAL_CMEXPAPI( "SJA_CanMiniDriver_Dispose" ) 
#else /* DYNAMIC_LINK */
	#define USE_SJA_CanMiniDriver_Dispose  PFSJA_CANMINIDRIVER_DISPOSE pfSJA_CanMiniDriver_Dispose;
	#define EXT_SJA_CanMiniDriver_Dispose  extern PFSJA_CANMINIDRIVER_DISPOSE pfSJA_CanMiniDriver_Dispose;
	#define GET_SJA_CanMiniDriver_Dispose(fl)  s_pfCMGetAPI2( "SJA_CanMiniDriver_Dispose", (RTS_VOID_FCTPTR *)&pfSJA_CanMiniDriver_Dispose, (fl), 0, 0)
	#define CAL_SJA_CanMiniDriver_Dispose  pfSJA_CanMiniDriver_Dispose
	#define CHK_SJA_CanMiniDriver_Dispose  (pfSJA_CanMiniDriver_Dispose != NULL)
	#define EXP_SJA_CanMiniDriver_Dispose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SJA_CanMiniDriver_Dispose", (RTS_UINTPTR)SJA_CanMiniDriver_Dispose, 0, 0) 
#endif



DEV_INFO* CDECL SJA_GetDeviceDescription(int iDev);
typedef DEV_INFO* (CDECL * PFSJA_GETDEVICEDESCRIPTION) (int iDev);
#if defined(CMPSJACANDRV_NOTIMPLEMENTED) || defined(SJA_GETDEVICEDESCRIPTION_NOTIMPLEMENTED)
	#define USE_SJA_GetDeviceDescription
	#define EXT_SJA_GetDeviceDescription
	#define GET_SJA_GetDeviceDescription(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SJA_GetDeviceDescription(p0)  (DEV_INFO*)ERR_NOTIMPLEMENTED
	#define CHK_SJA_GetDeviceDescription  FALSE
	#define EXP_SJA_GetDeviceDescription  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SJA_GetDeviceDescription
	#define EXT_SJA_GetDeviceDescription
	#define GET_SJA_GetDeviceDescription(fl)  CAL_CMGETAPI( "SJA_GetDeviceDescription" ) 
	#define CAL_SJA_GetDeviceDescription  SJA_GetDeviceDescription
	#define CHK_SJA_GetDeviceDescription  TRUE
	#define EXP_SJA_GetDeviceDescription  CAL_CMEXPAPI( "SJA_GetDeviceDescription" ) 
#elif defined(MIXED_LINK) && !defined(CMPSJACANDRV_EXTERNAL)
	#define USE_SJA_GetDeviceDescription
	#define EXT_SJA_GetDeviceDescription
	#define GET_SJA_GetDeviceDescription(fl)  CAL_CMGETAPI( "SJA_GetDeviceDescription" ) 
	#define CAL_SJA_GetDeviceDescription  SJA_GetDeviceDescription
	#define CHK_SJA_GetDeviceDescription  TRUE
	#define EXP_SJA_GetDeviceDescription  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SJA_GetDeviceDescription", (RTS_UINTPTR)SJA_GetDeviceDescription, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSJACanDrvSJA_GetDeviceDescription
	#define EXT_CmpSJACanDrvSJA_GetDeviceDescription
	#define GET_CmpSJACanDrvSJA_GetDeviceDescription  ERR_OK
	#define CAL_CmpSJACanDrvSJA_GetDeviceDescription pICmpSJACanDrv->ISJA_GetDeviceDescription
	#define CHK_CmpSJACanDrvSJA_GetDeviceDescription (pICmpSJACanDrv != NULL)
	#define EXP_CmpSJACanDrvSJA_GetDeviceDescription  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SJA_GetDeviceDescription
	#define EXT_SJA_GetDeviceDescription
	#define GET_SJA_GetDeviceDescription(fl)  CAL_CMGETAPI( "SJA_GetDeviceDescription" ) 
	#define CAL_SJA_GetDeviceDescription pICmpSJACanDrv->ISJA_GetDeviceDescription
	#define CHK_SJA_GetDeviceDescription (pICmpSJACanDrv != NULL)
	#define EXP_SJA_GetDeviceDescription  CAL_CMEXPAPI( "SJA_GetDeviceDescription" ) 
#else /* DYNAMIC_LINK */
	#define USE_SJA_GetDeviceDescription  PFSJA_GETDEVICEDESCRIPTION pfSJA_GetDeviceDescription;
	#define EXT_SJA_GetDeviceDescription  extern PFSJA_GETDEVICEDESCRIPTION pfSJA_GetDeviceDescription;
	#define GET_SJA_GetDeviceDescription(fl)  s_pfCMGetAPI2( "SJA_GetDeviceDescription", (RTS_VOID_FCTPTR *)&pfSJA_GetDeviceDescription, (fl), 0, 0)
	#define CAL_SJA_GetDeviceDescription  pfSJA_GetDeviceDescription
	#define CHK_SJA_GetDeviceDescription  (pfSJA_GetDeviceDescription != NULL)
	#define EXP_SJA_GetDeviceDescription  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SJA_GetDeviceDescription", (RTS_UINTPTR)SJA_GetDeviceDescription, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSJA_CANMINIDRIVER_SETUP ISJA_CanMiniDriver_Setup;
 	PFSJA_CANMINIDRIVER_DISPOSE ISJA_CanMiniDriver_Dispose;
 	PFSJA_GETDEVICEDESCRIPTION ISJA_GetDeviceDescription;
 } ICmpSJACanDrv_C;

#ifdef CPLUSPLUS
class ICmpSJACanDrv : public IBase
{
	public:
		virtual int CDECL ISJA_CanMiniDriver_Setup(void) =0;
		virtual int CDECL ISJA_CanMiniDriver_Dispose(void) =0;
		virtual DEV_INFO* CDECL ISJA_GetDeviceDescription(int iDev) =0;
};
	#ifndef ITF_CmpSJACanDrv
		#define ITF_CmpSJACanDrv static ICmpSJACanDrv *pICmpSJACanDrv = NULL;
	#endif
	#define EXTITF_CmpSJACanDrv
#else	/*CPLUSPLUS*/
	typedef ICmpSJACanDrv_C		ICmpSJACanDrv;
	#ifndef ITF_CmpSJACanDrv
		#define ITF_CmpSJACanDrv
	#endif
	#define EXTITF_CmpSJACanDrv
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPSJACANDRVITF_H_*/
