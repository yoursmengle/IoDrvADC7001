/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/

/**
 *  <name>Component SJA Can Mini Driver</name>
 *  <description> 
 *  </description>
 *  <copyright>
 *  (c) 2003-2017 3S-Smart Software Solutions
 *  </copyright>
 */
#ifndef _CMPSJACANDRVDEP_H_
#define _CMPSJACANDRVDEP_H_

#define COMPONENT_NAME "CmpSJACanDrv"COMPONENT_NAME_POSTFIX
#define COMPONENT_ID    ADDVENDORID(CMP_VENDORID, CMPID_CmpSJACanDrv)
#define COMPONENT_NAME_UNQUOTED CmpSJACanDrv






#define CMP_VERSION         UINT32_C(0x03050C00)
#define CMP_VERSION_STRING "3.5.12.0"
#define CMP_VERSION_RC      3,5,12,0
#define CMP_VENDORID       RTS_VENDORID_3S

#ifndef WIN32_RESOURCES

#include "CmpLogItf.h"
#include "CMUtilsItf.h"


#define SJA_SETTG_NUM_DEVICES		"NumDevices"
#define SJA_SETTG_DISABLE_RET		"DisableRetain"
#define SJA_SETTG_DISABLE_PCISCAN	"DisablePciScan"
#define SJA_SETTG_DISABLE_SJACHIPCHECK	"DisableSjaChipCheck"
#define SJA_SETTG_ADDR				"%d.Address"
#define SJA_SETTG_MEMMAP			"%d.MapAddress"
#define SJA_SETTG_INT				"%d.Interrupt"
#define SJA_SETTG_INTEDGE			"%d.IntEdgeTrig"
#define SJA_SETTG_XTAL				"%d.XtalFrequency"
#define SJA_SETTG_BUSTYPE			"%d.BusType"
#define SJA_SETTG_ALIGNMENT			"%d.Alignment"
#define SJA_SETTG_NAME				"%d.Name"
#define SJA_SETTG_OCTRL				"%d.OutputCtrl"
#define SJA_SETTG_PORTADDR			"%d.PortAddress"
#define SJA_SETTG_PORTVAL			"%d.PortValue"

#include "CmpStd.h"
#include "CmpItf.h"

#include "CAATypes.h"
#include "CAACanMiniDriver.h"
#include "SJACanDrv.h"

#define VENDOR_ID 0x10B5		/* PLX technology */
#define DEVICE_ID_PCI 0x9050	/* PCI card with PLX9050 */
#define DEVICE_ID_PCI_9056	0x9056	/* PCI card with PLX9056 */
#define DEVICE_ID_PCI_F3_ALTERA	0xE005
#define DEVICE_ID_PCIEX_A2_ALTERA	0x0004
#define SUBVENDOR_ID_AUTOMATA 0x1971		/* Automata chip */
#define SUBSYSTEM_ID_3450 0x3450	/* PCI subsystem ID defined for CAN card 70034500  1CAN  70034500 1N*/
#define SUBSYSTEM_ID_3451 0x3451	/* PCI subsystem ID defined for CAN card 70034510  2CAN  70062810 2N*/
#define SUBSYSTEM_ID_3455 0x3455	/* PCI subsystem ID defined for CAN card 70034550  2CAN + NV-RAM  70062800 2NNV*/
#define SUBSYSTEM_ID_3680 0x3680	/* PCI subsystem ID defined for F3 CANMaster 61KZ010298 & 61KZ010256*/
#define SUBSYSTEM_ID_395F 0x395F	/* PCI subsystem ID defined for A2 CANMaster 72011100 */

/* PCI card with PLX9051, dual CAN (on Kontron board with vendor ID 1014, PB) */
#define VENDOR_ID_IXXAT_2				0x10B5		/* PLX technology */
#define SUBVENDOR_ID_IXXAT_2			0x10B5		/* PLX technology */
#define DEVICE_ID_PCI_IXXAT_2			0x9051	
#define SUBSYSTEM_ID_IXXAT_2			0x2540

#define SUBVENDOR_ID_ESD			0x12FE
#define SUBSYSTEM_ID_ESD_PCI200		0x0004  // bridge: 9050
#define SUBSYSTEM_ID_ESD_CPCI200	0x010B  // bridge: 9030
#define SUBSYSTEM_ID_ESD_104200		0x0501  // bridge: 9030
#define SUBSYSTEM_ID_ESD_PCI266		0x0009  // bridge: 9056
#define SUBSYSTEM_ID_ESD_PEX266		0x0200  // bridge: 9056
#define SUBSYSTEM_ID_ESD_PMC266		0x000E	// bridge: 9056

#define DEVICE_ID_PCI_9030 0x9030	/* PCI card with PLX9030 */
#define SUBVENDOR_ID_ASEM 0x3000	/* Asem chip */

#define CAN_SUB_SYSTEM_ID_CONF1 0x1000	/* PCI subsystem ID defined for 1 CAN ch. */
#define CAN_SUB_SYSTEM_ID_CONF2 0x1001	/* PCI subsystem ID defined for 2 CAN ch + NVR */
#define CAN_SUB_SYSTEM_ID_CONF3 0x1002	/* PCI subsystem ID defined for 2 CAN ch */
#define CAN_SUB_SYSTEM_ID_CONF4 0x1003	/* PCI subsystem ID defined for future config. */

/*PCI Info for the PCAN*/
#define VENDOR_ID_PEAK 0x001C	/* Vendor ID Peak Systems */
#define DEVICE_ID_PEAK 0x0001	/* PCAN-PCI. */
#define DEVICE_ID_PEAK2 0x0002	/* PCAN-ExpressCard. */
#define DEVICE_ID_PEAK3 0x0003	/* PCAN-PCI Express. */
#define DEVICE_ID_PEAK4 0x0004	/* PCAN-compactPCI. */
#define DEVICE_ID_PEAK5 0x0005	/* PCAN-miniPCI. */
#define DEVICE_ID_PEAK6 0x0006	/* PCAN-PC/104-Plus. */
#define DEVICE_ID_PEAK7 0x0007	/* PCAN-PCI/104-Express. */
#define DEVICE_ID_PEAK8 0x0008	/* PCAN-miniPCI-Express. */
	
#define SUBSYSTEM_ID_IXXAT_PCI04 0x2540
#define SUBVENDOR_ID_IXXAT_PCI04 0x10B5

/* Janz SJA1000 PCI Card */
#define PCI_JANZ_SUBVENDOR_ID	0x13c3

/* 2 channels */
#define PCI_JANZ_SUBSYSTEM_ID	0x1a00 
#define PCI_JANZ_SUBSYSTEM_ID_1_CHANNEL	0x1900 
#define PCI_JANZ_SUBSYSTEM_ID_ONBOARD	0x1d00 

/*Grossenbacher CAN card (NUM)*/
#define PCI_VENDOR_ALTERA		0x1172
#define PCI_DEVICE_GROSSENB		0x1f32
#define PCI_SUBVENDOR_ALTERA	0x1172
#define PCI_SUBDEVICE_GROSSENB	0xcafe


/* PCI IDs of BELB */
#define PCI_VENDOR_BEH	0x10EE		/*it is the Xilinx vendor code (PCI core from Xilinx used)*/
#define PCI_DEVICE_BELB 0x0300		/*it's the device code for the whole BELB (not only CAN Board)*/

/*The master's register on the localbus of brunner.*/
#define BELBREG_MASTER_IRQ_ENABLE 0x008	 /* 16bit rw?, IRQ Enable Register */
#define belbIrqEnable 0x0000	/*varible required because register is writeonly?*/

/*The start of the slave registers on the localbus of brunner.*/
#define BELBREG_IRQLINE_SELECT     0x3F4  /* 16bit wo (write only), ??? */
#define belbIrq_CAN1	0x4000	 /* free defined, use e.g. 15th IRQ line for CAN0 */
#define belbIrq_CAN2	0x8000	 /* free defined, use e.g. 16th IRQ line for CAN1 */
#define belbIrq_IO		0x0001	 /* free defined, use e.g. 1st IRQ line for IO */

/* BELB slave registers
   see SPEC_BELB_DEV_GEN_V002__GenericDevice.pdf */
#define BELB_SLAVE_SIZE 0x400	   /* size of BELB slave device*/
#define BELB_SLAVE_COUNT 32
#define BELB_BAR1_MEMORY_SIZE (32 * 0x400) /* size of all BELB slaves together, all memory is contiguous */

#define BELBREG_DEV_TYPE    0x3FC  /* 16bit ro, Lower Byte is the Type, Higher Byte is the Version & Revision TODO*/
	#define BELB_DEV_TYPE_CAN 	0x1107	/* check only Lower Byte "0x07"   0x1207 is the current one?TODO 1access reads */
    #define BELB_DEV_TYPE_IN8 	0x3202
	#define BELB_DEV_TYPE_OUT8 	0x3203
	#define BELB_DEV_TYPE_IN16 	0x3202
	#define BELB_DEV_TYPE_RS232	0x3204
	#define BELB_DEV_TYPE_ARCNET 0x0

#define BELB_DEV_SIZE 0x400

/*PCI Info for the Advantech ADAM-5095 (to be used with ADAM 5560) 

	Base Address 1 for CAN 1 (in the ADAM it's IO port addressed)
	Base Address 2 for CAN 2 (in the ADAM it's IO port addressed)
*/

#define PCI_VENDOR_ADAM_5095		0x13fe
#define PCI_DEVICE_ADAM_5095		0x5095
#define PCI_SUBVENDOR_ADAM_5095		0
#define PCI_SUBDEVICE_ADAM_5095		0

/*PCI Info for the Advantech PCM26D2CA (to be used with APAX5580 RTE) 
	Base Addr 0 : CAN 1 memory mapped.
	Base Addr 0 + 0x400: CAN2, memory mapped.
*/

#define PCI_VENDOR_PCM26D2CA		0x13fe
#define PCI_DEVICE_PCM26D2CA		0xc202
#define PCI_DEVICE_PCM26D2CA_2		0xc302
#define PCI_SUBVENDOR_PCM26D2CA		0x13fe
#define PCI_SUBDEVICE_PCM26D2CA		0xc202
#define PCI_SUBDEVICE_PCM26D2CA_2	0xc302








#include "CmpSJACanDrvItf.h"







#include "CmpCAAMemBlockManItf.h"


#include "CmpCAACallbackItf.h"


#include "CmpCAACanL2Itf.h"


#include "SysPortItf.h"


#include "SysPciItf.h"


#include "SysShmItf.h"


#include "SysIntItf.h"


#include "CmpSettingsItf.h"


#include "CmpBelbItf.h"


#include "SysTimeItf.h"


#include "CmpEventMgrItf.h"


#include "CmpRetainItf.h"


/*Obsolete include: CMUtilsItf.m4*/



    







      







     

    































     


































#ifdef CPLUSPLUS
    #define INIT_STMT \
    {\
        IBase *pIBase;\
        RTS_RESULT initResult;\
        if (pICmpLog == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpLog, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpLog = (ICmpLog *)pIBase->QueryInterface(pIBase, ITFID_ICmpLog, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
        if (pICMUtils == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCMUtils, &initResult); \
            if (pIBase != NULL) \
            { \
                pICMUtils = (ICMUtils *)pIBase->QueryInterface(pIBase, ITFID_ICMUtils, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
        /*Obsolete include CMUtils*/ \
		  if (pICmpRetain == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpRetain, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpRetain = (ICmpRetain *)pIBase->QueryInterface(pIBase, ITFID_ICmpRetain, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pICmpEventMgr == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpEventMgr, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpEventMgr = (ICmpEventMgr *)pIBase->QueryInterface(pIBase, ITFID_ICmpEventMgr, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pISysTime == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CSysTime, &initResult); \
            if (pIBase != NULL) \
            { \
                pISysTime = (ISysTime *)pIBase->QueryInterface(pIBase, ITFID_ISysTime, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pICmpBelb == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpBelb, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpBelb = (ICmpBelb *)pIBase->QueryInterface(pIBase, ITFID_ICmpBelb, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pICmpSettings == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpSettings, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpSettings = (ICmpSettings *)pIBase->QueryInterface(pIBase, ITFID_ICmpSettings, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pISysInt == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CSysInt, &initResult); \
            if (pIBase != NULL) \
            { \
                pISysInt = (ISysInt *)pIBase->QueryInterface(pIBase, ITFID_ISysInt, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pISysShm == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CSysShm, &initResult); \
            if (pIBase != NULL) \
            { \
                pISysShm = (ISysShm *)pIBase->QueryInterface(pIBase, ITFID_ISysShm, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pISysPci == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CSysPci, &initResult); \
            if (pIBase != NULL) \
            { \
                pISysPci = (ISysPci *)pIBase->QueryInterface(pIBase, ITFID_ISysPci, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pISysPort == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CSysPort, &initResult); \
            if (pIBase != NULL) \
            { \
                pISysPort = (ISysPort *)pIBase->QueryInterface(pIBase, ITFID_ISysPort, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pICmpCAACanL2 == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpCAACanL2, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpCAACanL2 = (ICmpCAACanL2 *)pIBase->QueryInterface(pIBase, ITFID_ICmpCAACanL2, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pICmpCAACallback == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpCAACallback, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpCAACallback = (ICmpCAACallback *)pIBase->QueryInterface(pIBase, ITFID_ICmpCAACallback, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pICmpCAAMemBlockMan == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpCAAMemBlockMan, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpCAAMemBlockMan = (ICmpCAAMemBlockMan *)pIBase->QueryInterface(pIBase, ITFID_ICmpCAAMemBlockMan, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
           \
    }
    #define INIT_LOCALS_STMT \
    {\
        pICmpLog = NULL; \
        pICMUtils = NULL; \
        /*Obsolete include CMUtils*/ \
		  pICmpRetain = NULL; \
          pICmpEventMgr = NULL; \
          pISysTime = NULL; \
          pICmpBelb = NULL; \
          pICmpSettings = NULL; \
          pISysInt = NULL; \
          pISysShm = NULL; \
          pISysPci = NULL; \
          pISysPort = NULL; \
          pICmpCAACanL2 = NULL; \
          pICmpCAACallback = NULL; \
          pICmpCAAMemBlockMan = NULL; \
           \
    }
    #define EXIT_STMT \
    {\
        IBase *pIBase;\
        RTS_RESULT exitResult;\
        if (pICmpLog != NULL) \
        { \
            pIBase = (IBase *)pICmpLog->QueryInterface(pICmpLog, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpLog = NULL; \
            } \
        } \
        if (pICMUtils != NULL) \
        { \
            pIBase = (IBase *)pICMUtils->QueryInterface(pICMUtils, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICMUtils = NULL; \
            } \
        } \
        /*Obsolete include CMUtils*/ \
		  if (pICmpRetain != NULL) \
        { \
            pIBase = (IBase *)pICmpRetain->QueryInterface(pICmpRetain, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpRetain = NULL; \
            } \
        } \
          if (pICmpEventMgr != NULL) \
        { \
            pIBase = (IBase *)pICmpEventMgr->QueryInterface(pICmpEventMgr, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpEventMgr = NULL; \
            } \
        } \
          if (pISysTime != NULL) \
        { \
            pIBase = (IBase *)pISysTime->QueryInterface(pISysTime, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pISysTime = NULL; \
            } \
        } \
          if (pICmpBelb != NULL) \
        { \
            pIBase = (IBase *)pICmpBelb->QueryInterface(pICmpBelb, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpBelb = NULL; \
            } \
        } \
          if (pICmpSettings != NULL) \
        { \
            pIBase = (IBase *)pICmpSettings->QueryInterface(pICmpSettings, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpSettings = NULL; \
            } \
        } \
          if (pISysInt != NULL) \
        { \
            pIBase = (IBase *)pISysInt->QueryInterface(pISysInt, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pISysInt = NULL; \
            } \
        } \
          if (pISysShm != NULL) \
        { \
            pIBase = (IBase *)pISysShm->QueryInterface(pISysShm, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pISysShm = NULL; \
            } \
        } \
          if (pISysPci != NULL) \
        { \
            pIBase = (IBase *)pISysPci->QueryInterface(pISysPci, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pISysPci = NULL; \
            } \
        } \
          if (pISysPort != NULL) \
        { \
            pIBase = (IBase *)pISysPort->QueryInterface(pISysPort, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pISysPort = NULL; \
            } \
        } \
          if (pICmpCAACanL2 != NULL) \
        { \
            pIBase = (IBase *)pICmpCAACanL2->QueryInterface(pICmpCAACanL2, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpCAACanL2 = NULL; \
            } \
        } \
          if (pICmpCAACallback != NULL) \
        { \
            pIBase = (IBase *)pICmpCAACallback->QueryInterface(pICmpCAACallback, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpCAACallback = NULL; \
            } \
        } \
          if (pICmpCAAMemBlockMan != NULL) \
        { \
            pIBase = (IBase *)pICmpCAAMemBlockMan->QueryInterface(pICmpCAAMemBlockMan, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpCAAMemBlockMan = NULL; \
            } \
        } \
           \
    }
#else
    #define INIT_STMT
    #define INIT_LOCALS_STMT
    #define EXIT_STMT
#endif



#if defined(STATIC_LINK)
    #define IMPORT_STMT
#else
    #define IMPORT_STMT \
    {\
        RTS_RESULT importResult = ERR_OK;\
        RTS_RESULT TempResult = ERR_OK;\
        INIT_STMT   \
        TempResult = GET_LogAdd(CM_IMPORT_OPTIONAL_FUNCTION); \
        TempResult = GET_CMUtlMemCpy(CM_IMPORT_OPTIONAL_FUNCTION); \
        if (ERR_OK == importResult ) importResult = GET_CMUtlSafeStrCat(0);\
          if (ERR_OK == importResult ) importResult = GET_CMUtlsnprintf(0);\
          if (ERR_OK == importResult ) importResult = GET_CMUtlSafeStrCpy(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSharedMemoryCreate(0);\
          if (ERR_OK == importResult ) importResult = GET_SysIntDisable(0);\
          if (ERR_OK == importResult ) importResult = GET_SysIntEnable(0);\
          if (ERR_OK == importResult ) importResult = GET_SysIntClose(0);\
          if (ERR_OK == importResult ) importResult = GET_SysIntUnregister(0);\
          if (ERR_OK == importResult ) importResult = GET_SysIntRegister(0);\
          if (ERR_OK == importResult ) importResult = GET_SysIntOpen(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSharedMemoryGetPointer(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSharedMemoryClose(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSharedMemoryOpen(0);\
          if (ERR_OK == importResult ) importResult = GET_SysPortIn(0);\
          if (ERR_OK == importResult ) importResult = GET_SysPortOut(0);\
          if (ERR_OK == importResult ) importResult = GET_MBM_MsgGetData(0);\
          if (ERR_OK == importResult ) importResult = GET_CL2_MsgGetData(0);\
          if (ERR_OK == importResult ) importResult = GET_CL2_MsgClone(0);\
          if (ERR_OK == importResult ) importResult = GET_CL2_MsgPutRQueue(0);\
          if (ERR_OK == importResult ) importResult = GET_CL2_MsgSendAcknIRQ(0);\
          if (ERR_OK == importResult ) importResult = GET_CL2_MsgFree(0);\
          if (ERR_OK == importResult ) importResult = GET_CL2_MsgAlloc(0);\
          if (ERR_OK == importResult ) importResult = GET_CL2_CmdUnRegister(0);\
          if (ERR_OK == importResult ) importResult = GET_CL2_CmdRegister(0);\
          if (ERR_OK == importResult ) importResult = GET_MBM_XChgGetSize(0);\
          if (ERR_OK == importResult ) importResult = GET_MBM_XChgDelete(0);\
          if (ERR_OK == importResult ) importResult = GET_MBM_XChgCreateP(0);\
          if (ERR_OK == importResult ) importResult = GET_MBM_XChgCreateH(0);\
          if (ERR_OK == importResult ) importResult = GET_MBM_MsgSend(0);\
          if (ERR_OK == importResult ) importResult = GET_MBM_MsgReceive(0);\
          if (ERR_OK == importResult ) importResult = GET_SettgGetStringValue(0);\
          if (ERR_OK == importResult ) importResult = GET_SettgGetIntValue(0);\
          if (ERR_OK == importResult ) TempResult = GET_EventRegisterCallbackFunction(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_EventUnregisterCallbackFunction(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_EventClose(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_EventOpen(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysTimeGetMs(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysPciWriteValue(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysPciReadValue(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysPciGetCardInfo(CM_IMPORT_OPTIONAL_FUNCTION);\
           \
        /* To make LINT happy */\
        TempResult = TempResult;\
        if (ERR_OK != importResult) return importResult;\
    }
#endif



#ifndef CMPSJACANDRV_DISABLE_EXTREF
#define EXPORT_EXTREF_STMT \
              
#else
#define EXPORT_EXTREF_STMT
#endif
#ifndef CMPSJACANDRV_DISABLE_EXTREF2
#define EXPORT_EXTREF2_STMT \
              
#else
#define EXPORT_EXTREF2_STMT
#endif
#if !defined(STATIC_LINK) && !defined(CPLUSPLUS) && !defined(CPLUSPLUS_ONLY)
#define EXPORT_CMPITF_STMT \
    {\
        { (RTS_VOID_FCTPTR)SJA_GetDeviceDescription, "SJA_GetDeviceDescription", 0, 0 },\
          { (RTS_VOID_FCTPTR)SJA_CanMiniDriver_Dispose, "SJA_CanMiniDriver_Dispose", 0, 0 },\
          { (RTS_VOID_FCTPTR)SJA_CanMiniDriver_Setup, "SJA_CanMiniDriver_Setup", 0, 0 },\
          \
        { ((RTS_VOID_FCTPTR)(void *)0), "", 0, 0 }\
    }
#else
#define EXPORT_CMPITF_STMT \
    {\
        { ((RTS_VOID_FCTPTR)(void *)0), "", 0, 0 }\
    }
#endif
#define EXPORT_CPP_STMT


#if defined(STATIC_LINK)
    #define EXPORT_STMT\
    {\
        RTS_RESULT ExpResult;\
        if (NULL == s_pfCMRegisterAPI)\
            return ERR_NOTINITIALIZED;\
        ExpResult = s_pfCMRegisterAPI(s_ExternalsTable, 0, 1, COMPONENT_ID);\
        if (ERR_OK != ExpResult)\
            return ExpResult;\
    }
#else
    #define EXPORT_STMT\
    {\
        RTS_RESULT ExpResult;\
        if (NULL == s_pfCMRegisterAPI)\
            return ERR_NOTINITIALIZED;\
        ExpResult = s_pfCMRegisterAPI(s_ExternalsTable, 0, 1, COMPONENT_ID);\
        if (ERR_OK != ExpResult)\
            return ExpResult;\
        ExpResult = s_pfCMRegisterAPI(s_ItfTable, 0, 0, COMPONENT_ID);\
        if (ERR_OK != ExpResult)\
            return ExpResult;\
    }
#endif

#define USE_STMT \
    /*lint -save --e{528} --e{551} */ \
    static volatile PF_REGISTER_API s_pfCMRegisterAPI; \
    static volatile PF_REGISTER_API2 s_pfCMRegisterAPI2; \
    static volatile PF_GET_API s_pfCMGetAPI; \
    static volatile PF_GET_API2 s_pfCMGetAPI2; \
    static volatile PF_REGISTER_CLASS s_pfCMRegisterClass; \
    static volatile PF_CREATEINSTANCE s_pfCMCreateInstance; \
    static volatile PF_CALL_HOOK s_pfCMCallHook; \
    static const CMP_EXT_FUNCTION_REF s_ExternalsTable[] =\
    {\
        EXPORT_EXTREF_STMT\
        EXPORT_EXTREF2_STMT\
        { ((RTS_VOID_FCTPTR)(void *)0), "", 0, 0 }\
    };\
    static const CMP_EXT_FUNCTION_REF s_ItfTable[] = EXPORT_CMPITF_STMT; \
    /*lint -restore */  \
    static int CDECL ExportFunctions(void); \
    static int CDECL ImportFunctions(void); \
    static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult); \
    static RTS_RESULT CDECL DeleteInstance(IBase *pIBase); \
    static RTS_UI32 CDECL CmpGetVersion(void); \
    static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2); \
    ITF_CmpLog   \
    ITF_CMUtils  \
    USE_CMUtlMemCpy  \
    USE_LogAdd \
	ITF_CmpCAAMemBlockMan     \
	ITF_CmpCAACallback     \
	ITF_CmpCAACanL2     \
	ITF_SysPort     \
	ITF_SysPci     \
	ITF_SysShm     \
	ITF_SysInt     \
	ITF_CmpSettings     \
	ITF_CmpBelb     \
	ITF_SysTime     \
	ITF_CmpEventMgr     \
	ITF_CmpRetain     \
	/*obsolete entry ITF_CMUtils*/       \
    USE_SysPciGetCardInfo      \
    USE_SysPciReadValue      \
    USE_SysPciWriteValue      \
    USE_SysTimeGetMs      \
    USE_EventOpen      \
    USE_EventClose      \
    USE_EventUnregisterCallbackFunction      \
    USE_EventRegisterCallbackFunction      \
    USE_SettgGetIntValue      \
    USE_SettgGetStringValue      \
    USE_MBM_MsgReceive      \
    USE_MBM_MsgSend      \
    USE_MBM_XChgCreateH      \
    USE_MBM_XChgCreateP      \
    USE_MBM_XChgDelete      \
    USE_MBM_XChgGetSize      \
    USE_CL2_CmdRegister      \
    USE_CL2_CmdUnRegister      \
    USE_CL2_MsgAlloc      \
    USE_CL2_MsgFree      \
    USE_CL2_MsgSendAcknIRQ      \
    USE_CL2_MsgPutRQueue      \
    USE_CL2_MsgClone      \
    USE_CL2_MsgGetData      \
    USE_MBM_MsgGetData      \
    USE_SysPortOut      \
    USE_SysPortIn      \
    USE_SysSharedMemoryOpen      \
    USE_SysSharedMemoryClose      \
    USE_SysSharedMemoryGetPointer      \
    USE_SysIntOpen      \
    USE_SysIntRegister      \
    USE_SysIntUnregister      \
    USE_SysIntClose      \
    USE_SysIntEnable      \
    USE_SysIntDisable      \
    USE_SysSharedMemoryCreate      \
    USE_CMUtlSafeStrCpy      \
    USE_CMUtlsnprintf      \
    USE_CMUtlSafeStrCat     
#define USEIMPORT_STMT \
    /*lint -save --e{551} */ \
    static volatile PF_REGISTER_API s_pfCMRegisterAPI; \
    static volatile PF_REGISTER_API2 s_pfCMRegisterAPI2; \
    static volatile PF_GET_API s_pfCMGetAPI; \
    static volatile PF_GET_API2 s_pfCMGetAPI2; \
    static volatile PF_REGISTER_CLASS s_pfCMRegisterClass; \
    static volatile PF_CREATEINSTANCE s_pfCMCreateInstance; \
    static volatile PF_CALL_HOOK s_pfCMCallHook; \
    /*lint -restore */  \
    ITF_CmpLog   \
    ITF_CMUtils  \
    USE_CMUtlMemCpy  \
    USE_LogAdd \
	ITF_CmpCAAMemBlockMan    \
	ITF_CmpCAACallback    \
	ITF_CmpCAACanL2    \
	ITF_SysPort    \
	ITF_SysPci    \
	ITF_SysShm    \
	ITF_SysInt    \
	ITF_CmpSettings    \
	ITF_CmpBelb    \
	ITF_SysTime    \
	ITF_CmpEventMgr    \
	ITF_CmpRetain    \
	/*obsolete entry ITF_CMUtils*/      \
    USE_SysPciGetCardInfo      \
    USE_SysPciReadValue      \
    USE_SysPciWriteValue      \
    USE_SysTimeGetMs      \
    USE_EventOpen      \
    USE_EventClose      \
    USE_EventUnregisterCallbackFunction      \
    USE_EventRegisterCallbackFunction      \
    USE_SettgGetIntValue      \
    USE_SettgGetStringValue      \
    USE_MBM_MsgReceive      \
    USE_MBM_MsgSend      \
    USE_MBM_XChgCreateH      \
    USE_MBM_XChgCreateP      \
    USE_MBM_XChgDelete      \
    USE_MBM_XChgGetSize      \
    USE_CL2_CmdRegister      \
    USE_CL2_CmdUnRegister      \
    USE_CL2_MsgAlloc      \
    USE_CL2_MsgFree      \
    USE_CL2_MsgSendAcknIRQ      \
    USE_CL2_MsgPutRQueue      \
    USE_CL2_MsgClone      \
    USE_CL2_MsgGetData      \
    USE_MBM_MsgGetData      \
    USE_SysPortOut      \
    USE_SysPortIn      \
    USE_SysSharedMemoryOpen      \
    USE_SysSharedMemoryClose      \
    USE_SysSharedMemoryGetPointer      \
    USE_SysIntOpen      \
    USE_SysIntRegister      \
    USE_SysIntUnregister      \
    USE_SysIntClose      \
    USE_SysIntEnable      \
    USE_SysIntDisable      \
    USE_SysSharedMemoryCreate      \
    USE_CMUtlSafeStrCpy      \
    USE_CMUtlsnprintf      \
    USE_CMUtlSafeStrCat     
#define USEEXTERN_STMT \
    EXT_CMUtlMemCpy  \
    EXT_LogAdd \
	EXTITF_CmpCAAMemBlockMan    \
	EXTITF_CmpCAACallback    \
	EXTITF_CmpCAACanL2    \
	EXTITF_SysPort    \
	EXTITF_SysPci    \
	EXTITF_SysShm    \
	EXTITF_SysInt    \
	EXTITF_CmpSettings    \
	EXTITF_CmpBelb    \
	EXTITF_SysTime    \
	EXTITF_CmpEventMgr    \
	EXTITF_CmpRetain    \
	/*obsolete entry EXTITF_CMUtils*/      \
    EXT_SysPciGetCardInfo  \
    EXT_SysPciReadValue  \
    EXT_SysPciWriteValue  \
    EXT_SysTimeGetMs  \
    EXT_EventOpen  \
    EXT_EventClose  \
    EXT_EventUnregisterCallbackFunction  \
    EXT_EventRegisterCallbackFunction  \
    EXT_SettgGetIntValue  \
    EXT_SettgGetStringValue  \
    EXT_MBM_MsgReceive  \
    EXT_MBM_MsgSend  \
    EXT_MBM_XChgCreateH  \
    EXT_MBM_XChgCreateP  \
    EXT_MBM_XChgDelete  \
    EXT_MBM_XChgGetSize  \
    EXT_CL2_CmdRegister  \
    EXT_CL2_CmdUnRegister  \
    EXT_CL2_MsgAlloc  \
    EXT_CL2_MsgFree  \
    EXT_CL2_MsgSendAcknIRQ  \
    EXT_CL2_MsgPutRQueue  \
    EXT_CL2_MsgClone  \
    EXT_CL2_MsgGetData  \
    EXT_MBM_MsgGetData  \
    EXT_SysPortOut  \
    EXT_SysPortIn  \
    EXT_SysSharedMemoryOpen  \
    EXT_SysSharedMemoryClose  \
    EXT_SysSharedMemoryGetPointer  \
    EXT_SysIntOpen  \
    EXT_SysIntRegister  \
    EXT_SysIntUnregister  \
    EXT_SysIntClose  \
    EXT_SysIntEnable  \
    EXT_SysIntDisable  \
    EXT_SysSharedMemoryCreate  \
    EXT_CMUtlSafeStrCpy  \
    EXT_CMUtlsnprintf  \
    EXT_CMUtlSafeStrCat 
#ifndef COMPONENT_NAME
    #error COMPONENT_NAME is not defined. This prevents the component from being linked statically. Use SET_COMPONENT_NAME(<name_of_your_component>) to set the name of the component in your .m4 component description.
#endif




#if defined(STATIC_LINK) || defined(MIXED_LINK) || defined(DYNAMIC_LINK) || defined(CPLUSPLUS_STATIC_LINK)
    #define ComponentEntry CmpSJACanDrv__Entry
#endif


#ifdef CPLUSPLUS

class CCmpSJACanDrv : public ICmpSJACanDrv 
{
    public:
        CCmpSJACanDrv() : hCmpSJACanDrv(RTS_INVALID_HANDLE), iRefCount(0)
        {
        }
        virtual ~CCmpSJACanDrv()
        {
        }
        virtual unsigned long AddRef(IBase *pIBase = NULL)
        {
            iRefCount++;
            return iRefCount;
        }
        virtual unsigned long Release(IBase *pIBase = NULL)
        {
            iRefCount--;
            if (iRefCount == 0)
            {
                delete this;
                return 0;
            }
            return iRefCount;
        }

        
        virtual void* QueryInterface(IBase *pIBase, ITFID iid, RTS_RESULT *pResult)
        {
            void *pItf;
            if (iid == ITFID_IBase)
                pItf = dynamic_cast<IBase *>((ICmpSJACanDrv *)this);            
            else if (iid == ITFID_ICmpSJACanDrv)
                pItf = dynamic_cast<ICmpSJACanDrv *>(this); 
            else
            {
                if (pResult != NULL)
                    *pResult = ERR_NOTIMPLEMENTED;
                return NULL;
            }
            if (pResult != (RTS_RESULT *)1)
                (reinterpret_cast<IBase *>(pItf))->AddRef();
            if (pResult != NULL && pResult != (RTS_RESULT *)1)
                *pResult = ERR_OK;
            return pItf;
        }
        virtual int CDECL ISJA_CanMiniDriver_Setup(void);
        virtual int CDECL ISJA_CanMiniDriver_Dispose(void);
        virtual DEV_INFO* CDECL ISJA_GetDeviceDescription(int iDev);

    public:
        RTS_HANDLE hCmpSJACanDrv;
        int iRefCount;
};

#endif /*CPLUSPLUS*/
#ifdef RTS_COMPACT_MICRO
/* CmpSJACanDrv Declarations for uRTS */
/* This header is included only to have the CMP_EXT_FUNCTION_REF type definition. */
/* In final version this type could be moved to CmpItf.h, if we will use */
/* the same structure for representing an export entry. */
#include <_OptionalIncludes/Profiles/uRTS/CMMicro.h>

/* Undefine these macros if they were previously defined */

#ifdef USE_HOOK_FUNCTION
#undef USE_HOOK_FUNCTION
#endif

#ifdef USE_CMEXPORTFUNCTIONS
#undef USE_CMEXPORTFUNCTIONS
#endif

#ifdef USE_EXPORT_EXTREF
#undef USE_EXPORT_EXTREF
#endif

#ifdef USE_EXPORT_CMPITF
#undef USE_EXPORT_CMPITF
#endif

#ifdef USE_ENTRY_LINKAGE
#undef USE_ENTRY_LINKAGE
#endif

#ifdef IMPLEMENT_EXPORT_FUNCTIONS
#undef IMPLEMENT_EXPORT_FUNCTIONS
#endif

#ifdef IMPLEMENT_IMPORT_FUNCTIONS
#undef IMPLEMENT_IMPORT_FUNCTIONS
#endif

#ifdef IMPLEMENT_GETVERSION_FUNCTIONS
#undef IMPLEMENT_GETVERSION_FUNCTIONS
#endif

#ifdef EXPORT_STMT
#undef EXPORT_STMT
#endif

#ifdef USEEXTERN_STMT
#undef USEEXTERN_STMT
#endif

#ifdef USE_STMT
#undef USE_STMT
#endif

#ifdef USEIMPORT_STMT
#undef USEIMPORT_STMT
#endif

/* This wrapper is only required in uRTS */
#define USE_HOOK_FUNCTION	RTS_RESULT CmpSJACanDrv_HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)\
{\
	return HookFunction(ulHook, ulParam1, ulParam2);\
}

/******************************************************************************/
/* No s_pfCMExportFunctions in uRTS */
#define USE_CMEXPORTFUNCTIONS

/* Exports table to IEC */
#define USE_EXPORT_EXTREF const CMP_EXT_FUNCTION_REF CmpSJACanDrv_ExternalsTable[] = \
	{\
		EXPORT_EXTREF_STMT\
		EXPORT_EXTREF2_STMT\
		{ ((RTS_VOID_FCTPTR)(void *)0), "", 0 }\
	};

/* No component interface exports in uRTS */
#define USE_EXPORT_CMPITF

/* No dynamic linkage in uRTS */
#define USE_ENTRY_LINKAGE

/* No ExportFunctions() routine in uRTS */
#define IMPLEMENT_EXPORT_FUNCTIONS

/* No ImportFunctions() routine in uRTS */
#define IMPLEMENT_IMPORT_FUNCTIONS

/* No CmpGetVersion() routine in uRTS */
#define IMPLEMENT_GETVERSION_FUNCTIONS

/* No usage of externals from the component secondary C-modules in uRTS */
#define USEEXTERN_STMT

/* No need for export calling to the Component Manager in uRTS */
#define EXPORT_STMT

/* No need for importing from secondary C-modules */
#define USEIMPORT_STMT

/* Instantiation macro for a root component C-module */
#define USE_STMT\
	static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);\
		USE_EXPORT_EXTREF;\
		USE_EXPORT_CMPITF;\
		USE_HOOK_FUNCTION;\
		USE_CMEXPORTFUNCTIONS;\


/******************************************************************************/
#endif

#endif /*WIN32_RESOURCES*/
#endif /*_DEP_H_*/
