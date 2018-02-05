/**
 *  <name>Component SJA Can Mini Driver</name>
 *  <description> 
 *  </description>
 *  <copyright>
 *  (c) 2003-2017 3S-Smart Software Solutions
 *  </copyright>
 */
SET_COMPONENT_NAME(`CmpSJACanDrv')
COMPONENT_SOURCES(`CmpSJACanDrv.c', `SJACanDrv.c')

COMPONENT_VERSION(`0x03050C00')
COMPONENT_VENDORID(`RTS_VENDORID_3S')

CATEGORY(`Application.IO.IoDriver.CAN.SJA')

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




IMPLEMENT_ITF(`CmpSJACanDrvItf.m4')

USE_ITF(`CmpCAAMemBlockManItf.m4')
USE_ITF(`CmpCAACallbackItf.m4')
USE_ITF(`CmpCAACanL2Itf.m4')
USE_ITF(`SysPortItf.m4')
USE_ITF(`SysPciItf.m4')
USE_ITF(`SysShmItf.m4')
USE_ITF(`SysIntItf.m4')
USE_ITF(`CmpSettingsItf.m4')
USE_ITF(`CmpBelbItf.m4')
USE_ITF(`SysTimeItf.m4')
USE_ITF(`CmpEventMgrItf.m4')
USE_ITF(`CmpRetainItf.m4')
USE_ITF(`CMUtilsItf.m4')

OPTIONAL_IMPORTS(
SysPciGetCardInfo,
SysPciReadValue,
SysPciWriteValue,
SysTimeGetMs,
EventOpen,
EventClose,
EventUnregisterCallbackFunction,
EventRegisterCallbackFunction)

REQUIRED_IMPORTS(
SettgGetIntValue,
SettgGetStringValue,
MBM_MsgReceive,
MBM_MsgSend,
MBM_XChgCreateH,
MBM_XChgCreateP,
MBM_XChgDelete,
MBM_XChgGetSize,
CL2_CmdRegister,
CL2_CmdUnRegister,
CL2_MsgAlloc,
CL2_MsgFree,
CL2_MsgSendAcknIRQ,
CL2_MsgPutRQueue,
CL2_MsgClone,
CL2_MsgGetData,
MBM_MsgGetData,
SysPortOut,
SysPortIn,
SysSharedMemoryOpen,
SysSharedMemoryClose,
SysSharedMemoryGetPointer,
SysIntOpen,
SysIntRegister,
SysIntUnregister,
SysIntClose,
SysIntEnable,
SysIntDisable,
SysSharedMemoryCreate,
CMUtlSafeStrCpy,
CMUtlsnprintf,
CMUtlSafeStrCat)
