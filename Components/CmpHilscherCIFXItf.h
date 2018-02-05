 /**
 * <interfacename>CmpHilscherCIFX</interfacename>
 * <description>
 *	Interface for accessing Hilscher NetX cards.
 *
 *	Hilscher PC cards (CIFX) must be typically loaded with two firmware parts which are provided by Hilscher:
 *		1. Bootloader:
 *			Has mostly the ending .bin (e.g. NETX100-BSL.bin)	
 *		2. Firmware file:
 *			This file contains the fieldbus specific stack.
 *			Mostly this file has the format cifx_ _ _.nxf. e.g. "cifxdpm.nxf" for a Profibus DP Master or "cifxdps.nxf" for a Profibus DP Slave firmware.
 *
 *	The configuration of the bootloader and firmware files can be done in several ways. A Hilscher Card is addressed here via its Card Index or Slot Number and
 *	optional the so called channel. Some Hilscher Cards has one or optional two separate channels on the NetX to support multi fieldbus strands.
 *  In the following examples, the devicenumber [n] starts with 0!
 *	All of these configurations must be done under the section:
 *		[CmpHilscherCIFX]
 *
 *	1. Global configuiration for all cards:
 *		The bootloader can be configured for all cards the folllowing way:
 *			BootloaderFile=./HilscherCIFX/Firmware/NETX100-BSL.bin
 *
 *	2. Configuration via Card Index:
 *		A card index is the logical number of the card beginning with 0.
 *		- Bootloader:
 *			Device.n.BootloaderFile=./HilscherCIFX/Firmware/NETX100-BSL.bin
 *		- Firmware: 
 *			Device.n.FirmwareFile=./HilscherCIFX/Firmware/cifxdpm.nxf
 *		  or with specified channel:
 *			Device.n.Channel.0.FirmwareFile=./HilscherCIFX/Firmware/cifxdpm.nxf
 *
 *	3. Dynamic configuration out of IO-Configuration in the programming system:
 *		For this you have to specify first if all the following settings for a card:
 *		- Globally for all cards:
 *			DynamicFirmware=1
 *		- or per single card with:
 *			Device.n.DynamicFirmware=1
 *
 *		To specify the firmware matching to the corresponding fieldbus type there are 3 options:
  *		1. Default firmware:
 *			You can specify the path to all firmware files:
 *				FirmwareFilePath=./HilscherCIFX/Firmware
 *			With this we try to match the bustype to the default firmware (e.g. "ProfibusMaster" -> cifxdpm.nxf)!
 *
 *		2. You can specify a firmware matching to the corresponding fieldbus by its name (only one firmware for a fieldbus type can be configured for all cards):
 *				FirmwareFile.0=ProfinetMaster, ./HilscherCIFX/Firmware/cifxpnm.nxf
 *			or specify the corresponding device number (so different firmwares per device can be configured):
 *				Device.n.FirmwareFile.0=ProfinetMaster, ./HilscherCIFX/Firmware/cifxpnm.nxf
 *				Device.n.FirmwareFile.1.1=EthernetIPMaster, ./HilscherCIFX/Firmware/cifxeim.nxf
 *			For the list of possible fieldbus type names see the defines CIFX_NAME_XXX.
 *
 *		3. You can specify a firmware matching to the corresponding fieldbus by its name as a key with a list of filenames and versions.
 *			The version is optained via EVT_CIFX_GETFIRMWARE/EVTPARAM_CIFX_GetFirmware. 
 *			In case the version is set in the event callback, it is matched with a list of elements, configured as:
 *				<MasterName>.n=<FirmwareName>, [<FirmwareVersion>]
 *				Example:
 *				ProfibusMaster.0=cifxdpm.nxf, 0x01020304
 *				ProfibusMaster.1=cifxdpm2.nxf, 0x01020306
 *				ProfinetMaster.0=cifXpnm.nxf, 0x01020304
 *				ProfinetMaster.1=cifXpnm2.nxf, 0x01020306
 *			For the list of possible fieldbus type names see the defines CIFX_NAME_XXX. The path is taken from the FirmwareFilePath configuiration.

 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPHILSCHERCIFXITF_H_
#define _CMPHILSCHERCIFXITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "SysIntItf.h"
#include "CmpIoDrvItf.h"

#ifndef APIENTRY 
    #define APIENTRY 
#endif 

#include "CAATypes.h"

#ifdef CIFX_LIB
	#include <cifx/cifXUser.h>
#else
 #ifdef PATHS_RELATIVE
	#include "./CmpHilscherCIFX/Source/cifXUser.h"
	#include "./CmpHilscherCIFX/Source/OS_Includes.h"
 #else
	#include "cifXUser.h"
	#include "OS_Includes.h"
 #endif
#endif

/**
 * <category>Compiler switch</category>
 * <description>
 *	Compiler switches to enable/disable single features in the component.
 * </description>
 * <element name="CIFX_TOOLKIT_DMA">Switch to enable DMA transfer mode</element>
 * <element name="CIFX_TOOLKIT_ENABLE_DSR_LOCK">Interrupt lock must be enabled to use interrupt mode to synchronize the interrupt handler against the DSR task!
 *	If not, you got race conditions on multicore CPUs!</element>
 * <element name="CIFX_TOOLKIT_3S">Switch to build the component with the hilscher toolkit source based on the 3S-OS-Abstraction layer</element>
 * <element name="CIFX_LIB">Switch to build the component based on the cifX ibrary from hilscher</element>
 */
#define CIFX_TOOLKIT_ENABLE_DSR_LOCK


#ifndef CIFX_MAX_ID
	#define CIFX_MAX_ID 0x100
#endif

#ifndef CIFX_QUEUE_MAX_PACKETS
	#define CIFX_QUEUE_MAX_PACKETS	100
#endif

#ifndef CIFX_QUEUE_FREE_TIMEOUT
	#define CIFX_QUEUE_FREE_TIMEOUT	2000
#endif

#ifndef CIFX_GET_PACKET_TIMEOUT
	#define CIFX_GET_PACKET_TIMEOUT 20
#endif

#ifndef MAX_CIFX_BOARDS
	#define MAX_CIFX_BOARDS 10
#endif

#ifndef CIFX_MAX_OPEN_CHANNELS
	#define CIFX_MAX_OPEN_CHANNELS	10
#endif

#ifndef MAX_RESET_CHANNELS
	#define MAX_RESET_CHANNELS	10
#endif

/**
* Definition of the supported fieldbus firmware names 
*/
#define CIFX_NAME_PROFIBUS_MASTER		"ProfibusMaster"
#define CIFX_NAME_PROFIBUS_SLAVE		"ProfibusSlave"
#define CIFX_NAME_CANOPEN_MASTER		"CANopenMaster"
#define CIFX_NAME_PROFINET_MASTER		"ProfinetMaster"
#define CIFX_NAME_PROFINET_SLAVE		"ProfinetSlave"
#define CIFX_NAME_DEVICENET_MASTER		"DeviceNetMaster"
#define	CIFX_NAME_ETHERNETIP_MASTER		"EthernetIPMaster"

/**
* The macro CIFX_PACKETDPMTASK_SLEEP should not be defined, because sending messages via NetX are event triggered now.
* Only for backward compatibility, the macro is used.
*/

#ifndef CIFX_RECVPKTTASK_SLEEP
	#define CIFX_RECVPKTTASK_SLEEP(hTask) CAL_SysTaskWaitSleep(hTask, 1);
#endif


/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting prefix for devices.</description>
 */
#define CMPHILSCHERCIFX_STRING_DEVICE								"Device"

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting prefix for channels.</description>
 */
#define CMPHILSCHERCIFX_STRING_CHANNEL								"Channel"

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting prefix for slots.</description>
 */
#define CMPHILSCHERCIFX_STRING_SLOT									"Slot"

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting to define the alias name of a board.</description>
 */
#define CMPHILSCHERCIFX_STRING_ALIAS								"Alias"
#define CMPHILSCHERCIFX_STRING_ALIAS_DEFAULT						""

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Setting to define the trace level of the cifx toolkit.</description>
 */
#define CMPHILSCHERCIFX_INT_TRACELEVEL								"TraceLevel"
#define CMPHILSCHERCIFX_INT_TRACELEVEL_DEFAULT						TRACE_LEVEL_ERROR

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Setting to define, if the NetX is used interrupt driven. SysInt must be supported in this case!</description>
 */
#define CMPHILSCHERCIFX_INTERRUPT_MODE								"InterruptMode"
#ifndef CMPHILSCHERCIFX_INT_INTERRUPT_MODE_DEFAULT
	#define CMPHILSCHERCIFX_INT_INTERRUPT_MODE_DEFAULT				0
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Setting to define, if the NetX is using DMA mode.
 *	NOTE:
 *	- Compiler Switch CIFX_TOOLKIT_DMA must be set additionally (see above)!
 *	- In OS adaptation layer: OS_MemAllocDMABuffer and OS_MemFreeDMABuffer must be supported!
 *	- If DMA mode is off, the IoDrvCifxProfibus uses a buffered memory to update shared memory instead of DMA.
 * </description>
 */
#define CMPHILSCHERCIFX_DMA_MODE									"DMAMode"
#ifndef CMPHILSCHERCIFX_INT_DMA_MODE_DEFAULT
	#ifdef CIFX_TOOLKIT_DMA
		#define CMPHILSCHERCIFX_INT_DMA_MODE_DEFAULT				1
	#else
		#define CMPHILSCHERCIFX_INT_DMA_MODE_DEFAULT				0
	#endif
#endif


/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting to define the bootloader file.
 *
 * Example:
 *		BootloaderFile=NETX100-BSL.bin
 *	or
 *		Device.0.BootloaderFile=NETX100-BSL.bin
 * </description>
 */
#define CMPHILSCHERCIFX_STRING_BOOTLOADER_FILE						"BootloaderFile"
#ifndef CMPHILSCHERCIFX_STRING_BOOTLOADER_FILE_DEFAULT
	#define CMPHILSCHERCIFX_STRING_BOOTLOADER_FILE_DEFAULT			"./NETX100-BSL.bin"
#endif
/* Old style (backward compatible) */
#define CMPHILSCHERCIFX_STRING_BOOTLOADER_FILE_PATH					"BootloaderFilePath"
#define CMPHILSCHERCIFX_STRING_BOOTLOADER_FILE_PATH_DEFAULT			CMPHILSCHERCIFX_STRING_BOOTLOADER_FILE_DEFAULT


/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting to define the base firmware file path.
 *
 * Example:
 *		Device.0.BaseFirmwareFile=C0201040.nxf
 * </description>
 */
#define CMPHILSCHERCIFX_STRING_BASEFIRMWARE_FILE					"BaseFirmwareFile"

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting to define the path for all firmware files.
 *
 * Example:
 *		FirmwareFilePath=./HilscherCIFX/Firmware
 * </description>
 */
#define CMPHILSCHERCIFX_STRING_FIRMWARE_FILE_PATH					"FirmwareFilePath"
#ifndef CMPHILSCHERCIFX_STRING_FIRMWARE_FILE_PATH_DEFAULT
	#define CMPHILSCHERCIFX_STRING_FIRMWARE_FILE_PATH_DEFAULT		""
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting to define the firmware of a device, channel or slot.
 *
 * Example:
 *		Device.0.FirmwareFile=cifx2dpm.nxf
 *  or
 *		Device.0.Channel.0.FirmwareFile=cifx2dpm.nxf
 * </description>
 */
#define CMPHILSCHERCIFX_STRING_FIRMWARE								"FirmwareFile"
#define CMPHILSCHERCIFX_STRING_FIRMWARE_DEFAULT						""
#define CMPHILSCHERCIFX_STRING_CHANNEL_FIRMWARE						CMPHILSCHERCIFX_STRING_FIRMWARE
#define CMPHILSCHERCIFX_STRING_CHANNEL_FIRMWARE_DEFAULT				CMPHILSCHERCIFX_STRING_FIRMWARE_DEFAULT

/**
 * <category>Settings</category>
 * <type>int</type>
 * <description>Setting to enable dynamic firmware loading matching to IO-configuration out of CODESYS.
 *
 * Example:
 *		Global for all cards: DynamicFirmware=1
 *	or
 *		Device.0.DynamicFirmware=1
 * </description>
 */
#define CMPHILSCHERCIFX_INT_ENABLE_DYNAMIC_FIRMWARE					"DynamicFirmware"
#ifndef CMPHILSCHERCIFX_INT_ENABLE_DYNAMIC_FIRMWARE_DEFAULT
	#define CMPHILSCHERCIFX_INT_ENABLE_DYNAMIC_FIRMWARE_DEFAULT		0
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting to define the firmware of one channel.</description>
 */
#define CMPHILSCHERCIFX_STRING_CHANNEL_CONFIGURATION				"ConfigurationFile"
#define CMPHILSCHERCIFX_STRING_CHANNEL_CONFIGURATION_DEFAULT		"./config.dbm"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Setting to define the DPM address of the NetX device. The address is the physical address of the DPM or if necessary the still mapped address.
 * NOTE:
 *	The setting must be specified with the device prefix and number.
 *
 * Example:
 *		Device.0.DPMAddress=0x12345678
 * </description>
 */
#define CMPHILSCHERCIFX_KEY_INT_DPM_ADDRESS							"DPMAddress"
#define CMPHILSCHERCIFX_VALUE_INT_DPM_ADDRESS_DEFAULT				0

/**
 * <category>Settings</category>
 * <type>int</type>
 * <description>Setting to define the priority of the dsr task (not used yet.</description>
 */
#define CMPHILSCHERCIFX_INT_CHANNEL_DSR_TASK_PRIORITY				"DSRTaskPriority"
#ifndef CMPHILSCHERCIFX_INT_CHANNEL_DSR_TASK_PRIORITY_DEFAULT
	#define CMPHILSCHERCIFX_INT_CHANNEL_DSR_TASK_PRIORITY_DEFAULT	TASKPRIO_SYSTEM_END
#endif

/**
 * <category>Settings</category>
 * <type>int</type>
 * <description>Setting to define the priority of the background task. Default is TASKPRIO_HIGH_BASE (see SysTaskItf).</description>
 */
#define CMPHILSCHERCIFX_INT_DPM_TASK_PRIORITY						"DPMTaskPriority"
#ifndef CMPHILSCHERCIFX_INT_DPM_TASK_PRIORITY_DEFAULT
	#define CMPHILSCHERCIFX_INT_DPM_TASK_PRIORITY_DEFAULT			TASKPRIO_HIGH_BASE
#endif

/**
 * <category>Settings</category>
 * <type>int</type>
 * <description>Setting to activate all log messages</description>
 */
#define CMPHILSCHERCIFX_INT_ACTIVATE_CYCLIC_MSG						"ActivateCyclicMessages"
#ifndef CMPHILSCHERCIFX_INT_ACTIVATE_CYCLIC_MSG_DEFAULT
	#define CMPHILSCHERCIFX_INT_ACTIVATE_CYCLIC_MSG_DEFAULT			0
#endif

/**
 * <category>Settings</category>
 * <type>int</type>
 * <description>Set the receive timeout of the GetPacket Task</description>
 */
#define CMPHILSCHERCIFX_INT_RECV_TIMEOUT										"ReceiveTimeout"
#ifndef CMPHILSCHERCIFX_INT_RECV_TIMEOUT_DEFAULT
	#define CMPHILSCHERCIFX_INT_RECV_TIMEOUT_DEFAULT						0
#endif

/**
 * <category>Settings</category>
 * <type>int</type>
 * <description>Create a seperate task to receive packets from the netX dpm.</description>
 */
#define CMPHILSCHERCIFX_INT_RECV_PKT_IN_OWN_TASK							"RecvPktInOwnTask"
#ifndef CMPHILSCHERCIFX_INT_RECV_PKT_IN_OWN_TASK_DEFAULT
	#define CMPHILSCHERCIFX_INT_RECV_PKT_IN_OWN_TASK_DEFAULT				0
#endif


/**
 * <category>Settings</category>
 * <type>int</type>
 * <description>Create a seperate task to receive packets from the netX dpm.
 * ATTENTION: The hilscher Toolkit must be implemented with interrupts and the ReceiveTimeout must be != 0. If not
 * an endless loop occurs.</description>
 */
#define CMPHILSCHERCIFX_INT_RECV_PKT_TASK_PRIORITY							"RecvPktTaskPriority"
#ifndef CMPHILSCHERCIFX_INT_RECV_PKT_TASK_PRIORITY_DEFAULT
	#define CMPHILSCHERCIFX_INT_RECV_PKT_TASK_PRIORITY_DEFAULT				TASKPRIO_HIGH_BASE
#endif



/**
 * <category>Defines</category>
 * <description>
	Defines for different queueing mechanism
	CIFX_QUEUE_FIFO: Fifo queue
	CIFX_QUEUE_SRCID: Packet with the same SrcId are returned.
   </description>
*/
#define CIFX_QUEUE_FIFO			0
#define CIFX_QUEUE_SRCID			1

/**
 * <category>Device information</category>
 * <description>
 *	Contains all relevant information for a single NetX device.
 * </description>
 * <element name="hInt" type="IN">Handle to interrupt</element>
 * <element name="hShmBoard" type="IN">Handle to mapped DPM</element>
 * <element name="hDsrEventhInt" type="IN">Handle to Dsr event</element>
 * <element name="hDsrTask" type="IN">Handle to Dsr task</element>
 * <element name="pDeviceInstance" type="IN">Handle to device instance (Hilscher toolkit device instance)</element>
 * <element name="ulDevNr" type="IN">Device number</element>
 * <element name="ulChannel" type="IN">Channel number</element>
 * <element name="ulSlotNr" type="IN">Slot number</element>
 * <element name="ulBaseAddresses" type="IN">PCI base addresses</element>
 * <element name="ulBusNr" type="IN">PCI bus number</element>
 * <element name="ulDevice" type="IN">PCI device number</element>
 * <element name="ulFunction" type="IN">PCI function number</element>
 * <element name="usCommand" type="IN">Command ID</element>
 * <element name="usVendorID" type="IN">PCI Vendor ID</element>
 * <element name="usDeviceID" type="IN">PCI Device ID</element>
 * <element name="usSubVendorID" type="IN">PCI SubVendor ID</element>
 * <element name="usSubDeviceID" type="IN">PCI SubDevice ID</element>
 * <element name="usBusType" type="IN">PCI bus type</element>
 * <element name="usConnectorType" type="IN">Connector type of the fieldbus that should run on the CIFX card. E.g. CT_PROFIBUS_MASTER to load a Profibus Firmware
 *		on the NetX. See category "Connector types" in CmpIoDrvItf.h for detailed information.</element>
 * <element name="byIntVec" type="IN">PCI interrupt vector</element>
 * <element name="ulIntAll" type="IN">PCI interrupt mask</element>
 * <element name="bDynamicFirmware" type="IN">Is dynamic firmware configured</element>
 */
typedef struct _DEV_INFO
{
	RTS_HANDLE		hInt;
	RTS_HANDLE		hShmBoard;
	RTS_HANDLE		hDsrEvent;
	RTS_HANDLE		hDsrTask;
	void* pDeviceInstance;
	RTS_UI32		ulDevNr;
	RTS_UI32		ulChannel;
	RTS_UI32		ulSlotNr;
	RTS_UI32		ulBaseAddresses[5];
	RTS_UI32		ulBusNr;
	RTS_UI32		ulDevice;
	RTS_UI32		ulFunction;
	RTS_UI16		usCommand;
	RTS_UI16		usVendorID;
	RTS_UI16		usDeviceID;
	RTS_UI16		usSubVendorID;
	RTS_UI16		usSubDeviceID;
	RTS_UI16		usBusType;
	RTS_UI16		usConnectorType;
	RTS_UI8			byIntVec;
	RTS_UINTPTR		ulIntAll;
	RTS_I32			bDynamicFirmware;
	RTS_I32			iDSRtoCall;
} DEV_INFO;


typedef struct _CCBListEntrytag
{
	struct _CCBListEntrytag* pNext;
	void* pCCB;
}CCBListEntry;


/**
 * <description>
 *	CIFX Channel control block.
 * </description>
 * <element name="hChannel" type="IN">Handle to channel</element>
 * <element name="ulQueueMode" type="IN">Queue mode</element>
 * <element name="hRxQueue" type="IN">Handle to Rx Queue</element>
 * <element name="hIndicationQueue" type="IN">Handle to Indication Queue</element>
 * <element name="ulMsgCount" type="IN">Message Count</element>
 * <element name="ulAppId" type="IN">Application ID</element>
 * <element name="ulAppRegDone" type="IN">Flag if application service registered</element>
 * <element name="ulSessionId" type="IN">Session ID</element>
 * <element name="hMsgAppReg" type="IN">Handle to registered application service</element>
 * <element name="ulPacketTimeout" type="IN">Packet timeout</element>
 * <element name="hSem" type="IN">Handle to semaphore </element>
 * <element name="tList" type="IN">CCB List Entry</element>
 * <element name="ulLostMsgCounter" type="IN">Number of lost messages</element>
 * <element name="ulRecvTimeout" type="IN">Receive timeout</element>
 * <element name="hRecvTask" type="IN">Handle to receiving task</element>
 * <element name="hTxPool" type="IN">Handle to Tx pool</element>
 * <element name="hTxQueue" type="IN">Handle to Tx Queue</element>
 * <element name="hRxPool" type="IN">Handle to Rx pool</element>
 */
/*CAUTION: CCB is also used in IEC ==> only compatible changes allowed.*/

typedef struct
{
	CIFXHANDLE		hChannel;
	RTS_IEC_UDINT	ulQueueMode;
	CAA_HANDLE		hRxQueue;			/* Flat or FIFO */
	CAA_HANDLE		hIndicationQueue;	/*only for QueueMode SrcId*/
	RTS_UI32	ulMsgCount;
	RTS_UI32	ulAppId;
	RTS_UI32	ulAppRegDone;
	RTS_UI32	ulSessionId;
	CAA_HANDLE		hMsgAppReg;
	RTS_UI32	ulPacketTimeout;
	RTS_HANDLE		hSem;
	CCBListEntry	tList;
	RTS_UI32	ulLostMsgCounter;
	RTS_UI32	ulRecvTimeout;
	RTS_HANDLE		hRecvTask;
	CAA_HANDLE		hTxPool;
	CAA_HANDLE		hTxQueue;
	CAA_HANDLE		hRxPool;
} CCB;

typedef struct
{
	CCB*			pCCB;
	RTS_UI32	ulSessionId;
	RTS_UI32	ulSendErrorCounter;
	RTS_UI32	ulSrcId;
	RTS_UI32	ulTimestamp;
	CIFX_PACKET		tPkt;
} PCB;

/**
 * <category>Defines</category>
 * <description>
	Number of Channel Control Blocks
   </description>
 */
#ifndef CIFX_QUEUE_NUMBER_CCB
	#define CIFX_QUEUE_NUMBER_CCB	2
#endif


/**
 * <category>Event parameter</category>
 * <element name="hPkt" type="OUT">Msg Handle of the Packet</element>
 * <element name="ulPutInQueue" type="OUT">If this value is unequal 0, the hMsg is stored in the Indication queue (default). Otherwise not.</element>
 * <element name="ulGenerateAsyncEvent" type="OUT">If this value is unequal 0, the hMsg is send in an asynchronous event(0 is default). Otherwise not. If both values are 0, the hMsg is released.</element>
 * <element name="eAsyncEvent" type="OUT">CAA event, which should be send asynchronous.</element>
 */
typedef struct
{
	CAA_HANDLE hPkt;
	RTS_UI32 ulPutInQueue;
	RTS_UI32 ulGenerateAsyncEvent;
	CAA_ENUM eAsyncEvent;	
} CIFX_IndicationParam;

/**
 * <category>Event parameter</category>
 * <element name="hPkt" type="OUT">Msg Handle of the Packet</element>
 * <element name="ulPutInQueue" type="OUT">If this value is unequal 0, the hMsg is stored in the Indication queue (default). Otherwise not.</element>
 * <element name="ulGenerateAsyncEvent" type="OUT">If this value is unequal 0, the hMsg is send in an asynchronous event(0 is default). Otherwise not. If both values are 0, the hMsg is released.</element>
 * <element name="eAsyncEvent" type="OUT">CAA event, which should be send asynchronous.</element>
 */
typedef struct
{
	CAA_HANDLE hPkt;
	RTS_UI32 ulPutInQueue;
	RTS_UI32 ulGenerateAsyncEvent;
	CAA_ENUM eAsyncEvent;	
} CIFX_ConfirmationParam;

/* Only for backward compatibility. Can be removed later on */
#define EVTPARAMID_CmpHilscherCIFX			0x0001
#define EVTVERSION_CmpHilscherCIFX			0x0001

/**
 * <category>Event parameter</category>
 * <element name="ulStep" type="OUT">Actual download step</element>
 * <element name="ulMaxStep" type="OUT">Maximal number of steps</element>
 * <element name="pvUser" type="OUT">User data</element>
 * <element name="lError" type="OUT">cifx error code, if download fails</element>
 * <element name="bFinished" type="OUT">Finish flag, TRUE if download is finished</element>
 */
typedef struct
{
	RTS_UI32 ulStep;
	RTS_UI32 ulMaxStep;
	void* pvUser;
	long lError;
	char bFinished;
} EVTPARAM_LoadProgress;
#define EVTPARAMID_CIFX_LoadProgress		0x0001
#define EVTVERSION_CIFX_LoadProgress		0x0001

/**
 * <category>Event parameter</category>
 * <element name="ptRecvPkt" type="OUT">Pointer to the unhandled packet</element>
 * <element name="pvUser" type="OUT">User data</element>
 */
typedef struct
{
	CIFX_PACKET* ptRecvPkt;
	void* pvUser;
} EVTPARAM_PacketUnhandled;
#define EVTPARAMID_CIFX_PacketUnhandled		0x0001
#define EVTVERSION_CIFX_PacketUnhandled		0x0001

/**
 * <category>Event parameter</category>
 * <element name="pDevInfo" type="IN">Device info</element>
 * <element name="pfIntHandler" type="IN">Function pointer to CIFX interrupt handler
 *	NOTE:
 *	pDevInfo->pDeviceInstance must be provided as the parameter ulAdditionalInfo for the interrupt handler, if interrupt handler is 
 *	handled directly in the event!!
 * </element>
 * <element name="Result" type="OUT">With the result, the behaviour of the kernel can be managed in the event handler:
 *		ERR_OK: Interrupt is registered and enabled by the event handler itself
 *		ERR_NOTIMPLEMENTED: [default] Interrupt will be registered and enabled by the kernel via SysInt component
 *		ERR_FAILED: Interrupt will not be activated by the kernel via SysInt component, because a serious error occurred!
 * </element>
 */
typedef struct
{
	DEV_INFO *pDevInfo;
	SYS_INT_INTHANDLER pfCifxIntHandler;
	RTS_RESULT Result;
} EVTPARAM_CIFX_InterruptInfo;
#define EVTPARAMID_CIFX_InterruptInfo			0x0002
#define EVTVERSION_CIFX_InterruptInfo			0x0001

/**
 * <category>Event parameter</category>
 * <element name="DPMAddress" type="IN">Physical address of the DPM</element>
 * <element name="iDevice" type="IN">Index of device. Starts with 0</element>
 */
typedef struct
{
	RTS_SIZE DPMAddress;
	RTS_I32 iDevice;
} EVTPARAM_CIFX_ConfigureDPM;
#define EVTPARAMID_CIFX_ConfigureDPM			0x0003
#define EVTVERSION_CIFX_ConfigureDPM			0x0001

/**
 * <category>Event parameter</category>
 * <element name="pDevInfo" type="IN">Pointer to device info of the device</element>
 * <element name="pszFile" type="OUT">Pointer to return firmware filename (including path, relative or absolute)</element>
 * <element name="iLen" type="IN">Max lenght of pszFile</element>
 * <element name="result" type="OUT">Error code of the operation</element>
 * <element name="firmwareVersion" type="OUT">Optional version to select from configured firmware files (see Dynamic configuration 3.3 above)</element>
 */
typedef struct
{
	DEV_INFO *pDevInfo;
	char *pszFile;
	RTS_I32 iLen;
	RTS_RESULT result;
	RTS_UI32 firmwareVersion;
} EVTPARAM_CIFX_GetFirmware;
#define EVTPARAMID_CIFX_GetFirmware				0x0004
#define EVTVERSION_CIFX_GetFirmware				0x0002

/**
 * <category>Event parameter</category>
 * <element name="pConnector" type="IN">Pointer to connector of the driver instance</element>
 * <element name="ulBoard" type="IN">Board number (index 0 based)</element>
 * <element name="ulSlot" type="IN">Optional slot number. Default=0</element>
 * <element name="ulChannel" type="IN">Channel number of a multi channel NetX or 0 for a single channel NetX.</element>
 * <element name="result" type="OUT">Error code of the operation</element>
 */
typedef struct
{
	IoConfigConnector *pConnector;
	RTS_UI32 ulBoard;
	RTS_UI32 ulSlot;
	RTS_UI32 ulChannel;
	RTS_RESULT result;
} EVTPARAM_CIFX_LoadFirmware;
#define EVTPARAMID_CIFX_LoadFirmware			0x0005
#define EVTVERSION_CIFX_LoadFirmware			0x0001


/**
 * <category>Event parameter</category>
 * <element name="hDriver" type="IN">Handle of the driver instance</element>
 * <element name="szBoard" type="IN">Board name</element>
 * <element name="ulChannel" type="IN">Channel number of a multi channel NetX or 0 for a single channel NetX.</element>
 * <element name="pCCB" type="IN">Pointer to channel control block.</element>
 * <element name="result" type="OUT">Error code of the operation</element>
 */
typedef struct
{
	CIFXHANDLE hDriver;
	char* szBoard;
	RTS_UI32 ulChannel;
	CCB* pCCB;
	RTS_RESULT result;
} EVTPARAM_CIFX_xChannelOpen;
#define EVTPARAMID_CIFX_xChannelOpen			0x0006
#define EVTVERSION_CIFX_xChannelOpen			0x0001


/**
 * <category>Event parameter</category>
 * <element name="phChannel" type="IN">Pointer to communication control block.</element>
 * <element name="result" type="OUT">Error code of the operation</element>
 */
typedef struct
{
	CCB* pCCB;
	RTS_RESULT result;
} EVTPARAM_CIFX_xChannelClose;
#define EVTPARAMID_CIFX_xChannelClose			0x0007
#define EVTVERSION_CIFX_xChannelClose			0x0001 


/**
 * <category>Events</category>
 * <description>
	Event is sent on a file download to cifx, but only if no other callback is defined.
	(See cifx Device Driver Manual)
   </description>
 * <param name="pEventParam" type="IN">EVTPARAM_LoadProgress</param>
 */
#define EVT_DOWNLOAD_PROGRESS				MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Events</category>
 * <description>
	Event is sent on a file upload from cifx, but only if no other callback is defined.
	(See cifx Device Driver Manual)
   </description>
 * <param name="pEventParam" type="IN">EVTPARAM_LoadProgress</param>
 */
#define EVT_UPLOAD_PROGRESS					MAKE_EVENTID(EVTCLASS_INFO, 2)

/**
 * <category>Events</category>
 * <description>
	Event is sent if the cifx is bussy and cannot handle a packet, but only if no other callback is defined.
	(See cifx Device Driver Manual)
   </description>
 * <param name="pEventParam" type="IN">EVTPARAM_PacketUnhandled</param>
 */
#define EVT_PACKET_UNHANDLED				MAKE_EVENTID(EVTCLASS_INFO, 3)

/**
 * <category>Events</category>
 * <description>
 *	Event is sent when an indication was passed to the runtime system (cifx application). The user can decide, what should happen with the Indication.
 *	On default it is stored in the Indication Queue and the user can get the packet with the ChannelGetPacket service (ulPutInQueue != 0). If ulPutInQueue is 0, the packet
 *	is not stored in a queue. If the user sets the parameter ulGenerateAsyncEvent to 1, a asynchronous CAA_CB event, set in parameter eAsyncEvent (Source: CB_DRIVER) is generated. 
 *  As an parameter hMsg is passed to the callback.
 *	IMPORTANT: If the user wants to use the packet in an asynchronous event, he has to call MBM_MsgAddRef for hMsg in the EVT_PACKET_INDICATION callback. In addition to that 
 *  the user has to call MBM_MsgRelease in the async event callback. Otherwise the hMsg is already released, when the async callback is called or there is a memory leak.
 *  </description>
 * <param name="pEventParam" type="IN">CIFX_IndicationParam</param>
 */
#define EVT_PACKET_INDICATION				MAKE_EVENTID(EVTCLASS_INFO, 4)

/**
 * <category>Events</category>
 * <description>
	Event is sent, when all cards are detected.
   </description>
 * <param name="pEventParam" type="IN">No Parameters, pEventParam = 0</param>
 */
#define EVT_CARDS_INIT_DONE					MAKE_EVENTID(EVTCLASS_INFO, 5)

/**
 * <category>Events</category>
 * <description>
 *	Event is sent when an confirmation was passed to the runtime system (cifx application). The user can decide, what should happen with the Indication.
 *	On default it is stored in the confirmation Queue and the user can get the packet with the ChannelGetPacket service (ulPutInQueue != 0). If ulPutInQueue is 0, the packet
 *	is not stored in a queue. If the user sets the parameter ulGenerateAsyncEvent to 1, a asynchronous CAA_CB event, set in parameter eAsyncEvent (Source: CB_DRIVER) is generated. 
 *  As an parameter hMsg is passed to the callback.
 *	IMPORTANT: If the user wants to use the packet in an asynchronous event, he has to call MBM_MsgAddRef for hMsg in the EVT_PACKET_INDICATION callback. In addition to that 
 *  the user has to call MBM_MsgRelease in the async event callback. Otherwise the hMsg is already released, when the async callback is called or there is a memory leak.
 *  </description>
 * <param name="pEventParam" type="IN">CIFX_ConfirmationParam</param>
 */
#define EVT_PACKET_CONFIRMATION				MAKE_EVENTID(EVTCLASS_INFO, 6)

/**
 * <category>Events</category>
 * <description>
 *	Event is sent right before the interrupt for the specified card is enabled to do device or system specific stuff.
 *  </description>
 * <param name="pEventParam" type="IN">EVTPARAM_CIFX_InterruptInfo</param>
 */
#define EVT_CIFX_INTERRUPTS_ENABLE			MAKE_EVENTID(EVTCLASS_INFO, 7)

/**
 * <category>Events</category>
 * <description>
 *	Event is sent right before the interrupt for the specified card is disabled to do device or system specific stuff.
 *  </description>
 * <param name="pEventParam" type="IN">EVTPARAM_CIFX_InterruptInfo</param>
 */
#define EVT_CIFX_INTERRUPTS_DISABLE			MAKE_EVENTID(EVTCLASS_INFO, 8)

/**
 * <category>Events</category>
 * <description>
 *	Event is sent to configure the DPM address of the card. In this case it is assumed, that it is no PCI card.
 *  </description>
 * <param name="pEventParam" type="IN">EVTPARAM_CIFX_ConfigureDPM</param>
 */
#define EVT_CIFX_CONFIGURE_DPM				MAKE_EVENTID(EVTCLASS_INFO, 9)

/**
 * <category>Events</category>
 * <description>
 *	Event is sent to configure the correct firmware to the corresponding card.
 *	Optionally a firmware version can be returned to select from configured firmware files. See EVTPARAM_CIFX_GetFirmware.
 *  </description>
 * <param name="pEventParam" type="IN">EVTPARAM_CIFX_GetFirmware</param>
 */
#define EVT_CIFX_GETFIRMWARE				MAKE_EVENTID(EVTCLASS_INFO, 10)


/* Events that are fired out of the NetX IEC drivers */

/**
 * <category>Events</category>
 * <description>
 *	Event is sent to (re)initialize the card and to load the firmware.
 *  </description>
 * <param name="pEventParam" type="IN">EVTPARAM_CIFX_LoadFirmware</param>
 */
#define EVT_CIFX_LOADFIRMWARE				MAKE_EVENTID(EVTCLASS_INFO, 11)


/**
 * <category>Events</category>
 * <description>
 *	Event is sent to provide communication channel for other customer-specific components.
 *  </description>
 * <param name="pEventParam" type="IN">EVTPARAM_CIFX_xChannelOpen</param>
 */
#define EVT_CIFX_XCHANNEL_OPEN				MAKE_EVENTID(EVTCLASS_INFO, 12)


/**
 * <category>Events</category>
 * <description>
 *	Event is sent to inform other customer-specific components that a communication channel will be closed now.
 *  </description>
 * <param name="pEventParam" type="IN">EVTPARAM_CIFX_xChannelClose</param>
 */
#define EVT_CIFX_XCHANNEL_CLOSE				MAKE_EVENTID(EVTCLASS_INFO, 13)



#define CIFX_DIRECTORY_ENTRY	CIFX_DIRECTORYENTRY


/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>CIFX_SYSTEM_INFO_BLOCK</description>
 */
typedef struct tagCIFX_SYSTEM_INFO_BLOCK
{
	RTS_IEC_BYTE abyCookie[4];		
	RTS_IEC_UDINT ulDpmTotalSize;		
	RTS_IEC_UDINT ulDeviceNumber;		
	RTS_IEC_UDINT ulSerialNumber;		
	RTS_IEC_UINT auiHwOptions[4];		
	RTS_IEC_UINT uiManufacturer;		
	RTS_IEC_UINT uiProductionDate;		
	RTS_IEC_UDINT ulLicenseFlags1;		
	RTS_IEC_UDINT ulLicenseFlags2;		
	RTS_IEC_UINT uiNetXLicenseId;		
	RTS_IEC_UINT uiNetXLicenseFlags;		
	RTS_IEC_UINT uiDeviceClass;		
	RTS_IEC_BYTE byHwRevision;		
	RTS_IEC_BYTE byHwCompatibility;		
	RTS_IEC_UINT auiReserved[2];		
} CIFX_SYSTEM_INFO_BLOCK;

/**
 *Problem alignment /gerade addrs auf ARM), byte order bei PPC
 *{attribute 'pack_mode' := '1'} //test
 */
typedef struct tagCIFX_BOARD_INFORMATION
{
	RTS_IEC_DINT diBoardError;		/* !< Global Board error. Set when device specific data must NOT be used */
	RTS_IEC_BYTE abBoardName[16];		/* !< Global board name */
	RTS_IEC_BYTE abBoardAlias[16];		/* !< Global board alias name */
	RTS_IEC_UDINT udiBoardID;		/* !< Unique board ID, driver created */
	RTS_IEC_UDINT udiSystemError;		/* !< System error */
	RTS_IEC_UDINT udiPhysicalAddress;		/* !< Physical memory address */
	RTS_IEC_UDINT udiIrqNumber;		/* !< Hardware interrupt number */
	RTS_IEC_BYTE byIrqEnabled;		/* !< Hardware interrupt enable flag */
	RTS_IEC_UDINT udiChannelCnt;		/* !< Number of available channels */
	RTS_IEC_UDINT udiDpmTotalSize;		/* !< Dual-Port memory size in bytes */
	CIFX_SYSTEM_INFO_BLOCK tSystemInfo;		/* !< System information */
} CIFX_BOARD_INFORMATION;

/**
 * <description>CIFX_CHANNEL_INFORMATION</description>
 */
typedef struct tagCIFX_CHANNEL_INFORMATION
{
	RTS_IEC_BYTE abyBoardName[16];		/* !< Global board name */
	RTS_IEC_BYTE abyBoardAlias[16];		/* !< Global board alias name */
	RTS_IEC_UDINT udiDeviceNumber;		/* !< Global board device number */
	RTS_IEC_UDINT udiSerialNumber;		/* !< Global board serial number */
	RTS_IEC_UINT uiFWMajor;		/* !< Major Version of Channel Firmware */
	RTS_IEC_UINT uiFWMinor;		/* !< Minor Version of Channel Firmware */
	RTS_IEC_UINT uiFWRevision;		/* !< Revision of Channel Firmware */
	RTS_IEC_UINT uiFWBuild;		/* !< Build number of Channel Firmware */
	RTS_IEC_BYTE byFWNameLength;		/* !< Length  of FW Name */
	RTS_IEC_BYTE abyFWName[63];		/* !< Firmware Name */
	RTS_IEC_UINT uiFWYear;		/* !< Build Year of Firmware */
	RTS_IEC_BYTE byFWMonth;		/* !< Build Month of Firmware (1..12) */
	RTS_IEC_BYTE byFWDay;		/* !< Build Day of Firmware (1..31) */
	RTS_IEC_UDINT udiChannelError;		/* !< Channel error */
	RTS_IEC_UDINT udiOpenCnt;		/* !< Channel open counter */
	RTS_IEC_UDINT udiPutPacketCnt;		/* !< Number of put packet commands */
	RTS_IEC_UDINT udiGetPacketCnt;		/* !< Number of get packet commands */
	RTS_IEC_UDINT udiMailboxSize;		/* !< Mailbox packet size in bytes */
	RTS_IEC_UDINT udiIOInAreaCnt;		/* !< Number of IO IN areas */
	RTS_IEC_UDINT udiIOOutAreaCnt;		/* !< Number of IO OUT areas */
	RTS_IEC_UDINT udiHskSize;		/* !< Size of the handshake cells */
	RTS_IEC_UDINT udiNetxFlags;		/* !< Actual netX state flags */
	RTS_IEC_UDINT udiHostFlags;		/* !< Actual Host flags */
	RTS_IEC_UDINT udiHostCOSFlags;		/* !< Actual Host COS flags */
	RTS_IEC_UDINT udiDeviceCOSFlags;		/* !< Actual Device COS flags */
} CIFX_CHANNEL_INFORMATION;

/**
 * <description>cifx_getbusactivationbeforereset</description>
 */
typedef struct tagcifx_getbusactivationbeforereset_struct
{
	RTS_IEC_UDINT ulModuleType;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiInstance;			/* VAR_INPUT */	
	RTS_IEC_UDINT *pudiCmd;				/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_GetBusActivationBeforeReset;	/* VAR_OUTPUT */	
} cifx_getbusactivationbeforereset_struct;

void CDECL CDECL_EXT cifx_getbusactivationbeforereset(cifx_getbusactivationbeforereset_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_GETBUSACTIVATIONBEFORERESET_IEC) (cifx_getbusactivationbeforereset_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_GETBUSACTIVATIONBEFORERESET_NOTIMPLEMENTED)
	#define USE_cifx_getbusactivationbeforereset
	#define EXT_cifx_getbusactivationbeforereset
	#define GET_cifx_getbusactivationbeforereset(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_getbusactivationbeforereset(p0) 
	#define CHK_cifx_getbusactivationbeforereset  FALSE
	#define EXP_cifx_getbusactivationbeforereset  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_getbusactivationbeforereset
	#define EXT_cifx_getbusactivationbeforereset
	#define GET_cifx_getbusactivationbeforereset(fl)  CAL_CMGETAPI( "cifx_getbusactivationbeforereset" ) 
	#define CAL_cifx_getbusactivationbeforereset  cifx_getbusactivationbeforereset
	#define CHK_cifx_getbusactivationbeforereset  TRUE
	#define EXP_cifx_getbusactivationbeforereset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_getbusactivationbeforereset", (RTS_UINTPTR)cifx_getbusactivationbeforereset, 1, 0x82ED5912, 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_getbusactivationbeforereset
	#define EXT_cifx_getbusactivationbeforereset
	#define GET_cifx_getbusactivationbeforereset(fl)  CAL_CMGETAPI( "cifx_getbusactivationbeforereset" ) 
	#define CAL_cifx_getbusactivationbeforereset  cifx_getbusactivationbeforereset
	#define CHK_cifx_getbusactivationbeforereset  TRUE
	#define EXP_cifx_getbusactivationbeforereset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_getbusactivationbeforereset", (RTS_UINTPTR)cifx_getbusactivationbeforereset, 1, 0x82ED5912, 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_getbusactivationbeforereset
	#define EXT_CmpHilscherCIFXcifx_getbusactivationbeforereset
	#define GET_CmpHilscherCIFXcifx_getbusactivationbeforereset  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_getbusactivationbeforereset  cifx_getbusactivationbeforereset
	#define CHK_CmpHilscherCIFXcifx_getbusactivationbeforereset  TRUE
	#define EXP_CmpHilscherCIFXcifx_getbusactivationbeforereset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_getbusactivationbeforereset", (RTS_UINTPTR)cifx_getbusactivationbeforereset, 1, 0x82ED5912, 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_getbusactivationbeforereset
	#define EXT_cifx_getbusactivationbeforereset
	#define GET_cifx_getbusactivationbeforereset(fl)  CAL_CMGETAPI( "cifx_getbusactivationbeforereset" ) 
	#define CAL_cifx_getbusactivationbeforereset  cifx_getbusactivationbeforereset
	#define CHK_cifx_getbusactivationbeforereset  TRUE
	#define EXP_cifx_getbusactivationbeforereset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_getbusactivationbeforereset", (RTS_UINTPTR)cifx_getbusactivationbeforereset, 1, 0x82ED5912, 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_getbusactivationbeforereset  PFCIFX_GETBUSACTIVATIONBEFORERESET_IEC pfcifx_getbusactivationbeforereset;
	#define EXT_cifx_getbusactivationbeforereset  extern PFCIFX_GETBUSACTIVATIONBEFORERESET_IEC pfcifx_getbusactivationbeforereset;
	#define GET_cifx_getbusactivationbeforereset(fl)  s_pfCMGetAPI2( "cifx_getbusactivationbeforereset", (RTS_VOID_FCTPTR *)&pfcifx_getbusactivationbeforereset, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x82ED5912, 0x03050800)
	#define CAL_cifx_getbusactivationbeforereset  pfcifx_getbusactivationbeforereset
	#define CHK_cifx_getbusactivationbeforereset  (pfcifx_getbusactivationbeforereset != NULL)
	#define EXP_cifx_getbusactivationbeforereset   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_getbusactivationbeforereset", (RTS_UINTPTR)cifx_getbusactivationbeforereset, 1, 0x82ED5912, 0x03050800) 
#endif


/**
 * <description>cifx_resetconfigapplication</description>
 */
typedef struct tagcifx_resetconfigapplication_struct
{
	RTS_IEC_UDINT ulModuleType;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiInstance;			/* VAR_INPUT */	
	RTS_IEC_UDINT ulCommand;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_ResetConfigApplication;	/* VAR_OUTPUT */	
} cifx_resetconfigapplication_struct;

void CDECL CDECL_EXT cifx_resetconfigapplication(cifx_resetconfigapplication_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_RESETCONFIGAPPLICATION_IEC) (cifx_resetconfigapplication_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_RESETCONFIGAPPLICATION_NOTIMPLEMENTED)
	#define USE_cifx_resetconfigapplication
	#define EXT_cifx_resetconfigapplication
	#define GET_cifx_resetconfigapplication(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_resetconfigapplication(p0) 
	#define CHK_cifx_resetconfigapplication  FALSE
	#define EXP_cifx_resetconfigapplication  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_resetconfigapplication
	#define EXT_cifx_resetconfigapplication
	#define GET_cifx_resetconfigapplication(fl)  CAL_CMGETAPI( "cifx_resetconfigapplication" ) 
	#define CAL_cifx_resetconfigapplication  cifx_resetconfigapplication
	#define CHK_cifx_resetconfigapplication  TRUE
	#define EXP_cifx_resetconfigapplication  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_resetconfigapplication", (RTS_UINTPTR)cifx_resetconfigapplication, 1, 0xEBA09E55, 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_resetconfigapplication
	#define EXT_cifx_resetconfigapplication
	#define GET_cifx_resetconfigapplication(fl)  CAL_CMGETAPI( "cifx_resetconfigapplication" ) 
	#define CAL_cifx_resetconfigapplication  cifx_resetconfigapplication
	#define CHK_cifx_resetconfigapplication  TRUE
	#define EXP_cifx_resetconfigapplication  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_resetconfigapplication", (RTS_UINTPTR)cifx_resetconfigapplication, 1, 0xEBA09E55, 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_resetconfigapplication
	#define EXT_CmpHilscherCIFXcifx_resetconfigapplication
	#define GET_CmpHilscherCIFXcifx_resetconfigapplication  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_resetconfigapplication  cifx_resetconfigapplication
	#define CHK_CmpHilscherCIFXcifx_resetconfigapplication  TRUE
	#define EXP_CmpHilscherCIFXcifx_resetconfigapplication  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_resetconfigapplication", (RTS_UINTPTR)cifx_resetconfigapplication, 1, 0xEBA09E55, 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_resetconfigapplication
	#define EXT_cifx_resetconfigapplication
	#define GET_cifx_resetconfigapplication(fl)  CAL_CMGETAPI( "cifx_resetconfigapplication" ) 
	#define CAL_cifx_resetconfigapplication  cifx_resetconfigapplication
	#define CHK_cifx_resetconfigapplication  TRUE
	#define EXP_cifx_resetconfigapplication  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_resetconfigapplication", (RTS_UINTPTR)cifx_resetconfigapplication, 1, 0xEBA09E55, 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_resetconfigapplication  PFCIFX_RESETCONFIGAPPLICATION_IEC pfcifx_resetconfigapplication;
	#define EXT_cifx_resetconfigapplication  extern PFCIFX_RESETCONFIGAPPLICATION_IEC pfcifx_resetconfigapplication;
	#define GET_cifx_resetconfigapplication(fl)  s_pfCMGetAPI2( "cifx_resetconfigapplication", (RTS_VOID_FCTPTR *)&pfcifx_resetconfigapplication, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xEBA09E55, 0x03050800)
	#define CAL_cifx_resetconfigapplication  pfcifx_resetconfigapplication
	#define CHK_cifx_resetconfigapplication  (pfcifx_resetconfigapplication != NULL)
	#define EXP_cifx_resetconfigapplication   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_resetconfigapplication", (RTS_UINTPTR)cifx_resetconfigapplication, 1, 0xEBA09E55, 0x03050800) 
#endif


/**
 * <description>cifx_xchannelbusstate</description>
 */
typedef struct tagcifx_xchannelbusstate_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiCmd;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pudiState;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiTimeout;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelBusState;	/* VAR_OUTPUT */	
} cifx_xchannelbusstate_struct;

void CDECL CDECL_EXT cifx_xchannelbusstate(cifx_xchannelbusstate_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELBUSSTATE_IEC) (cifx_xchannelbusstate_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELBUSSTATE_NOTIMPLEMENTED)
	#define USE_cifx_xchannelbusstate
	#define EXT_cifx_xchannelbusstate
	#define GET_cifx_xchannelbusstate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelbusstate(p0) 
	#define CHK_cifx_xchannelbusstate  FALSE
	#define EXP_cifx_xchannelbusstate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelbusstate
	#define EXT_cifx_xchannelbusstate
	#define GET_cifx_xchannelbusstate(fl)  CAL_CMGETAPI( "cifx_xchannelbusstate" ) 
	#define CAL_cifx_xchannelbusstate  cifx_xchannelbusstate
	#define CHK_cifx_xchannelbusstate  TRUE
	#define EXP_cifx_xchannelbusstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelbusstate", (RTS_UINTPTR)cifx_xchannelbusstate, 1, RTSITF_GET_SIGNATURE(0, 0x7438ED44), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelbusstate
	#define EXT_cifx_xchannelbusstate
	#define GET_cifx_xchannelbusstate(fl)  CAL_CMGETAPI( "cifx_xchannelbusstate" ) 
	#define CAL_cifx_xchannelbusstate  cifx_xchannelbusstate
	#define CHK_cifx_xchannelbusstate  TRUE
	#define EXP_cifx_xchannelbusstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelbusstate", (RTS_UINTPTR)cifx_xchannelbusstate, 1, RTSITF_GET_SIGNATURE(0, 0x7438ED44), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelbusstate
	#define EXT_CmpHilscherCIFXcifx_xchannelbusstate
	#define GET_CmpHilscherCIFXcifx_xchannelbusstate  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelbusstate  cifx_xchannelbusstate
	#define CHK_CmpHilscherCIFXcifx_xchannelbusstate  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelbusstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelbusstate", (RTS_UINTPTR)cifx_xchannelbusstate, 1, RTSITF_GET_SIGNATURE(0, 0x7438ED44), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelbusstate
	#define EXT_cifx_xchannelbusstate
	#define GET_cifx_xchannelbusstate(fl)  CAL_CMGETAPI( "cifx_xchannelbusstate" ) 
	#define CAL_cifx_xchannelbusstate  cifx_xchannelbusstate
	#define CHK_cifx_xchannelbusstate  TRUE
	#define EXP_cifx_xchannelbusstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelbusstate", (RTS_UINTPTR)cifx_xchannelbusstate, 1, RTSITF_GET_SIGNATURE(0, 0x7438ED44), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelbusstate  PFCIFX_XCHANNELBUSSTATE_IEC pfcifx_xchannelbusstate;
	#define EXT_cifx_xchannelbusstate  extern PFCIFX_XCHANNELBUSSTATE_IEC pfcifx_xchannelbusstate;
	#define GET_cifx_xchannelbusstate(fl)  s_pfCMGetAPI2( "cifx_xchannelbusstate", (RTS_VOID_FCTPTR *)&pfcifx_xchannelbusstate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x7438ED44), 0x03050800)
	#define CAL_cifx_xchannelbusstate  pfcifx_xchannelbusstate
	#define CHK_cifx_xchannelbusstate  (pfcifx_xchannelbusstate != NULL)
	#define EXP_cifx_xchannelbusstate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelbusstate", (RTS_UINTPTR)cifx_xchannelbusstate, 1, RTSITF_GET_SIGNATURE(0, 0x7438ED44), 0x03050800) 
#endif


/**
 * <description>cifx_xchannelclose</description>
 */
typedef struct tagcifx_xchannelclose_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelClose;	/* VAR_OUTPUT */	
} cifx_xchannelclose_struct;

void CDECL CDECL_EXT cifx_xchannelclose(cifx_xchannelclose_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELCLOSE_IEC) (cifx_xchannelclose_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELCLOSE_NOTIMPLEMENTED)
	#define USE_cifx_xchannelclose
	#define EXT_cifx_xchannelclose
	#define GET_cifx_xchannelclose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelclose(p0) 
	#define CHK_cifx_xchannelclose  FALSE
	#define EXP_cifx_xchannelclose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelclose
	#define EXT_cifx_xchannelclose
	#define GET_cifx_xchannelclose(fl)  CAL_CMGETAPI( "cifx_xchannelclose" ) 
	#define CAL_cifx_xchannelclose  cifx_xchannelclose
	#define CHK_cifx_xchannelclose  TRUE
	#define EXP_cifx_xchannelclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelclose", (RTS_UINTPTR)cifx_xchannelclose, 1, RTSITF_GET_SIGNATURE(0, 0xEFA9701A), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelclose
	#define EXT_cifx_xchannelclose
	#define GET_cifx_xchannelclose(fl)  CAL_CMGETAPI( "cifx_xchannelclose" ) 
	#define CAL_cifx_xchannelclose  cifx_xchannelclose
	#define CHK_cifx_xchannelclose  TRUE
	#define EXP_cifx_xchannelclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelclose", (RTS_UINTPTR)cifx_xchannelclose, 1, RTSITF_GET_SIGNATURE(0, 0xEFA9701A), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelclose
	#define EXT_CmpHilscherCIFXcifx_xchannelclose
	#define GET_CmpHilscherCIFXcifx_xchannelclose  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelclose  cifx_xchannelclose
	#define CHK_CmpHilscherCIFXcifx_xchannelclose  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelclose", (RTS_UINTPTR)cifx_xchannelclose, 1, RTSITF_GET_SIGNATURE(0, 0xEFA9701A), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelclose
	#define EXT_cifx_xchannelclose
	#define GET_cifx_xchannelclose(fl)  CAL_CMGETAPI( "cifx_xchannelclose" ) 
	#define CAL_cifx_xchannelclose  cifx_xchannelclose
	#define CHK_cifx_xchannelclose  TRUE
	#define EXP_cifx_xchannelclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelclose", (RTS_UINTPTR)cifx_xchannelclose, 1, RTSITF_GET_SIGNATURE(0, 0xEFA9701A), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelclose  PFCIFX_XCHANNELCLOSE_IEC pfcifx_xchannelclose;
	#define EXT_cifx_xchannelclose  extern PFCIFX_XCHANNELCLOSE_IEC pfcifx_xchannelclose;
	#define GET_cifx_xchannelclose(fl)  s_pfCMGetAPI2( "cifx_xchannelclose", (RTS_VOID_FCTPTR *)&pfcifx_xchannelclose, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xEFA9701A), 0x03050800)
	#define CAL_cifx_xchannelclose  pfcifx_xchannelclose
	#define CHK_cifx_xchannelclose  (pfcifx_xchannelclose != NULL)
	#define EXP_cifx_xchannelclose   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelclose", (RTS_UINTPTR)cifx_xchannelclose, 1, RTSITF_GET_SIGNATURE(0, 0xEFA9701A), 0x03050800) 
#endif


/**
 * <description>cifx_xchannelcommonstatusblock</description>
 */
typedef struct tagcifx_xchannelcommonstatusblock_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiCmd;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiOffset;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiDataLen;			/* VAR_INPUT */	
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelCommonStatusBlock;	/* VAR_OUTPUT */	
} cifx_xchannelcommonstatusblock_struct;

void CDECL CDECL_EXT cifx_xchannelcommonstatusblock(cifx_xchannelcommonstatusblock_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELCOMMONSTATUSBLOCK_IEC) (cifx_xchannelcommonstatusblock_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELCOMMONSTATUSBLOCK_NOTIMPLEMENTED)
	#define USE_cifx_xchannelcommonstatusblock
	#define EXT_cifx_xchannelcommonstatusblock
	#define GET_cifx_xchannelcommonstatusblock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelcommonstatusblock(p0) 
	#define CHK_cifx_xchannelcommonstatusblock  FALSE
	#define EXP_cifx_xchannelcommonstatusblock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelcommonstatusblock
	#define EXT_cifx_xchannelcommonstatusblock
	#define GET_cifx_xchannelcommonstatusblock(fl)  CAL_CMGETAPI( "cifx_xchannelcommonstatusblock" ) 
	#define CAL_cifx_xchannelcommonstatusblock  cifx_xchannelcommonstatusblock
	#define CHK_cifx_xchannelcommonstatusblock  TRUE
	#define EXP_cifx_xchannelcommonstatusblock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelcommonstatusblock", (RTS_UINTPTR)cifx_xchannelcommonstatusblock, 1, RTSITF_GET_SIGNATURE(0, 0x0435FE4E), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelcommonstatusblock
	#define EXT_cifx_xchannelcommonstatusblock
	#define GET_cifx_xchannelcommonstatusblock(fl)  CAL_CMGETAPI( "cifx_xchannelcommonstatusblock" ) 
	#define CAL_cifx_xchannelcommonstatusblock  cifx_xchannelcommonstatusblock
	#define CHK_cifx_xchannelcommonstatusblock  TRUE
	#define EXP_cifx_xchannelcommonstatusblock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelcommonstatusblock", (RTS_UINTPTR)cifx_xchannelcommonstatusblock, 1, RTSITF_GET_SIGNATURE(0, 0x0435FE4E), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelcommonstatusblock
	#define EXT_CmpHilscherCIFXcifx_xchannelcommonstatusblock
	#define GET_CmpHilscherCIFXcifx_xchannelcommonstatusblock  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelcommonstatusblock  cifx_xchannelcommonstatusblock
	#define CHK_CmpHilscherCIFXcifx_xchannelcommonstatusblock  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelcommonstatusblock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelcommonstatusblock", (RTS_UINTPTR)cifx_xchannelcommonstatusblock, 1, RTSITF_GET_SIGNATURE(0, 0x0435FE4E), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelcommonstatusblock
	#define EXT_cifx_xchannelcommonstatusblock
	#define GET_cifx_xchannelcommonstatusblock(fl)  CAL_CMGETAPI( "cifx_xchannelcommonstatusblock" ) 
	#define CAL_cifx_xchannelcommonstatusblock  cifx_xchannelcommonstatusblock
	#define CHK_cifx_xchannelcommonstatusblock  TRUE
	#define EXP_cifx_xchannelcommonstatusblock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelcommonstatusblock", (RTS_UINTPTR)cifx_xchannelcommonstatusblock, 1, RTSITF_GET_SIGNATURE(0, 0x0435FE4E), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelcommonstatusblock  PFCIFX_XCHANNELCOMMONSTATUSBLOCK_IEC pfcifx_xchannelcommonstatusblock;
	#define EXT_cifx_xchannelcommonstatusblock  extern PFCIFX_XCHANNELCOMMONSTATUSBLOCK_IEC pfcifx_xchannelcommonstatusblock;
	#define GET_cifx_xchannelcommonstatusblock(fl)  s_pfCMGetAPI2( "cifx_xchannelcommonstatusblock", (RTS_VOID_FCTPTR *)&pfcifx_xchannelcommonstatusblock, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x0435FE4E), 0x03050800)
	#define CAL_cifx_xchannelcommonstatusblock  pfcifx_xchannelcommonstatusblock
	#define CHK_cifx_xchannelcommonstatusblock  (pfcifx_xchannelcommonstatusblock != NULL)
	#define EXP_cifx_xchannelcommonstatusblock   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelcommonstatusblock", (RTS_UINTPTR)cifx_xchannelcommonstatusblock, 1, RTSITF_GET_SIGNATURE(0, 0x0435FE4E), 0x03050800) 
#endif


/**
 * <description>cifx_xchannelconfiglock</description>
 */
typedef struct tagcifx_xchannelconfiglock_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiCmd;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pudiState;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiTimeout;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelConfigLock;	/* VAR_OUTPUT */	
} cifx_xchannelconfiglock_struct;

void CDECL CDECL_EXT cifx_xchannelconfiglock(cifx_xchannelconfiglock_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELCONFIGLOCK_IEC) (cifx_xchannelconfiglock_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELCONFIGLOCK_NOTIMPLEMENTED)
	#define USE_cifx_xchannelconfiglock
	#define EXT_cifx_xchannelconfiglock
	#define GET_cifx_xchannelconfiglock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelconfiglock(p0) 
	#define CHK_cifx_xchannelconfiglock  FALSE
	#define EXP_cifx_xchannelconfiglock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelconfiglock
	#define EXT_cifx_xchannelconfiglock
	#define GET_cifx_xchannelconfiglock(fl)  CAL_CMGETAPI( "cifx_xchannelconfiglock" ) 
	#define CAL_cifx_xchannelconfiglock  cifx_xchannelconfiglock
	#define CHK_cifx_xchannelconfiglock  TRUE
	#define EXP_cifx_xchannelconfiglock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelconfiglock", (RTS_UINTPTR)cifx_xchannelconfiglock, 1, RTSITF_GET_SIGNATURE(0, 0x4DC337D6), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelconfiglock
	#define EXT_cifx_xchannelconfiglock
	#define GET_cifx_xchannelconfiglock(fl)  CAL_CMGETAPI( "cifx_xchannelconfiglock" ) 
	#define CAL_cifx_xchannelconfiglock  cifx_xchannelconfiglock
	#define CHK_cifx_xchannelconfiglock  TRUE
	#define EXP_cifx_xchannelconfiglock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelconfiglock", (RTS_UINTPTR)cifx_xchannelconfiglock, 1, RTSITF_GET_SIGNATURE(0, 0x4DC337D6), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelconfiglock
	#define EXT_CmpHilscherCIFXcifx_xchannelconfiglock
	#define GET_CmpHilscherCIFXcifx_xchannelconfiglock  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelconfiglock  cifx_xchannelconfiglock
	#define CHK_CmpHilscherCIFXcifx_xchannelconfiglock  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelconfiglock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelconfiglock", (RTS_UINTPTR)cifx_xchannelconfiglock, 1, RTSITF_GET_SIGNATURE(0, 0x4DC337D6), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelconfiglock
	#define EXT_cifx_xchannelconfiglock
	#define GET_cifx_xchannelconfiglock(fl)  CAL_CMGETAPI( "cifx_xchannelconfiglock" ) 
	#define CAL_cifx_xchannelconfiglock  cifx_xchannelconfiglock
	#define CHK_cifx_xchannelconfiglock  TRUE
	#define EXP_cifx_xchannelconfiglock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelconfiglock", (RTS_UINTPTR)cifx_xchannelconfiglock, 1, RTSITF_GET_SIGNATURE(0, 0x4DC337D6), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelconfiglock  PFCIFX_XCHANNELCONFIGLOCK_IEC pfcifx_xchannelconfiglock;
	#define EXT_cifx_xchannelconfiglock  extern PFCIFX_XCHANNELCONFIGLOCK_IEC pfcifx_xchannelconfiglock;
	#define GET_cifx_xchannelconfiglock(fl)  s_pfCMGetAPI2( "cifx_xchannelconfiglock", (RTS_VOID_FCTPTR *)&pfcifx_xchannelconfiglock, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x4DC337D6), 0x03050800)
	#define CAL_cifx_xchannelconfiglock  pfcifx_xchannelconfiglock
	#define CHK_cifx_xchannelconfiglock  (pfcifx_xchannelconfiglock != NULL)
	#define EXP_cifx_xchannelconfiglock   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelconfiglock", (RTS_UINTPTR)cifx_xchannelconfiglock, 1, RTSITF_GET_SIGNATURE(0, 0x4DC337D6), 0x03050800) 
#endif


/**
 * <description>cifx_xchannelcontrolblock</description>
 */
typedef struct tagcifx_xchannelcontrolblock_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiCmd;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiOffset;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiDataLen;			/* VAR_INPUT */	
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelControlBlock;	/* VAR_OUTPUT */	
} cifx_xchannelcontrolblock_struct;

void CDECL CDECL_EXT cifx_xchannelcontrolblock(cifx_xchannelcontrolblock_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELCONTROLBLOCK_IEC) (cifx_xchannelcontrolblock_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELCONTROLBLOCK_NOTIMPLEMENTED)
	#define USE_cifx_xchannelcontrolblock
	#define EXT_cifx_xchannelcontrolblock
	#define GET_cifx_xchannelcontrolblock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelcontrolblock(p0) 
	#define CHK_cifx_xchannelcontrolblock  FALSE
	#define EXP_cifx_xchannelcontrolblock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelcontrolblock
	#define EXT_cifx_xchannelcontrolblock
	#define GET_cifx_xchannelcontrolblock(fl)  CAL_CMGETAPI( "cifx_xchannelcontrolblock" ) 
	#define CAL_cifx_xchannelcontrolblock  cifx_xchannelcontrolblock
	#define CHK_cifx_xchannelcontrolblock  TRUE
	#define EXP_cifx_xchannelcontrolblock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelcontrolblock", (RTS_UINTPTR)cifx_xchannelcontrolblock, 1, RTSITF_GET_SIGNATURE(0, 0xAC77B13A), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelcontrolblock
	#define EXT_cifx_xchannelcontrolblock
	#define GET_cifx_xchannelcontrolblock(fl)  CAL_CMGETAPI( "cifx_xchannelcontrolblock" ) 
	#define CAL_cifx_xchannelcontrolblock  cifx_xchannelcontrolblock
	#define CHK_cifx_xchannelcontrolblock  TRUE
	#define EXP_cifx_xchannelcontrolblock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelcontrolblock", (RTS_UINTPTR)cifx_xchannelcontrolblock, 1, RTSITF_GET_SIGNATURE(0, 0xAC77B13A), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelcontrolblock
	#define EXT_CmpHilscherCIFXcifx_xchannelcontrolblock
	#define GET_CmpHilscherCIFXcifx_xchannelcontrolblock  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelcontrolblock  cifx_xchannelcontrolblock
	#define CHK_CmpHilscherCIFXcifx_xchannelcontrolblock  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelcontrolblock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelcontrolblock", (RTS_UINTPTR)cifx_xchannelcontrolblock, 1, RTSITF_GET_SIGNATURE(0, 0xAC77B13A), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelcontrolblock
	#define EXT_cifx_xchannelcontrolblock
	#define GET_cifx_xchannelcontrolblock(fl)  CAL_CMGETAPI( "cifx_xchannelcontrolblock" ) 
	#define CAL_cifx_xchannelcontrolblock  cifx_xchannelcontrolblock
	#define CHK_cifx_xchannelcontrolblock  TRUE
	#define EXP_cifx_xchannelcontrolblock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelcontrolblock", (RTS_UINTPTR)cifx_xchannelcontrolblock, 1, RTSITF_GET_SIGNATURE(0, 0xAC77B13A), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelcontrolblock  PFCIFX_XCHANNELCONTROLBLOCK_IEC pfcifx_xchannelcontrolblock;
	#define EXT_cifx_xchannelcontrolblock  extern PFCIFX_XCHANNELCONTROLBLOCK_IEC pfcifx_xchannelcontrolblock;
	#define GET_cifx_xchannelcontrolblock(fl)  s_pfCMGetAPI2( "cifx_xchannelcontrolblock", (RTS_VOID_FCTPTR *)&pfcifx_xchannelcontrolblock, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xAC77B13A), 0x03050800)
	#define CAL_cifx_xchannelcontrolblock  pfcifx_xchannelcontrolblock
	#define CHK_cifx_xchannelcontrolblock  (pfcifx_xchannelcontrolblock != NULL)
	#define EXP_cifx_xchannelcontrolblock   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelcontrolblock", (RTS_UINTPTR)cifx_xchannelcontrolblock, 1, RTSITF_GET_SIGNATURE(0, 0xAC77B13A), 0x03050800) 
#endif


/**
 * <description>cifx_xchanneldownload</description>
 */
typedef struct tagcifx_xchanneldownload_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiMode;				/* VAR_INPUT */	
	RTS_IEC_BYTE *szFileName;			/* VAR_INPUT */	
	RTS_IEC_BYTE *pbyFileData;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiFileSize;			/* VAR_INPUT */	
	RTS_IEC_BYTE *pCallbackUserData;	/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelDownload;	/* VAR_OUTPUT */	
} cifx_xchanneldownload_struct;

void CDECL CDECL_EXT cifx_xchanneldownload(cifx_xchanneldownload_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELDOWNLOAD_IEC) (cifx_xchanneldownload_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELDOWNLOAD_NOTIMPLEMENTED)
	#define USE_cifx_xchanneldownload
	#define EXT_cifx_xchanneldownload
	#define GET_cifx_xchanneldownload(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchanneldownload(p0) 
	#define CHK_cifx_xchanneldownload  FALSE
	#define EXP_cifx_xchanneldownload  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchanneldownload
	#define EXT_cifx_xchanneldownload
	#define GET_cifx_xchanneldownload(fl)  CAL_CMGETAPI( "cifx_xchanneldownload" ) 
	#define CAL_cifx_xchanneldownload  cifx_xchanneldownload
	#define CHK_cifx_xchanneldownload  TRUE
	#define EXP_cifx_xchanneldownload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchanneldownload", (RTS_UINTPTR)cifx_xchanneldownload, 1, RTSITF_GET_SIGNATURE(0, 0x35317A0D), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchanneldownload
	#define EXT_cifx_xchanneldownload
	#define GET_cifx_xchanneldownload(fl)  CAL_CMGETAPI( "cifx_xchanneldownload" ) 
	#define CAL_cifx_xchanneldownload  cifx_xchanneldownload
	#define CHK_cifx_xchanneldownload  TRUE
	#define EXP_cifx_xchanneldownload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchanneldownload", (RTS_UINTPTR)cifx_xchanneldownload, 1, RTSITF_GET_SIGNATURE(0, 0x35317A0D), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchanneldownload
	#define EXT_CmpHilscherCIFXcifx_xchanneldownload
	#define GET_CmpHilscherCIFXcifx_xchanneldownload  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchanneldownload  cifx_xchanneldownload
	#define CHK_CmpHilscherCIFXcifx_xchanneldownload  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchanneldownload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchanneldownload", (RTS_UINTPTR)cifx_xchanneldownload, 1, RTSITF_GET_SIGNATURE(0, 0x35317A0D), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchanneldownload
	#define EXT_cifx_xchanneldownload
	#define GET_cifx_xchanneldownload(fl)  CAL_CMGETAPI( "cifx_xchanneldownload" ) 
	#define CAL_cifx_xchanneldownload  cifx_xchanneldownload
	#define CHK_cifx_xchanneldownload  TRUE
	#define EXP_cifx_xchanneldownload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchanneldownload", (RTS_UINTPTR)cifx_xchanneldownload, 1, RTSITF_GET_SIGNATURE(0, 0x35317A0D), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchanneldownload  PFCIFX_XCHANNELDOWNLOAD_IEC pfcifx_xchanneldownload;
	#define EXT_cifx_xchanneldownload  extern PFCIFX_XCHANNELDOWNLOAD_IEC pfcifx_xchanneldownload;
	#define GET_cifx_xchanneldownload(fl)  s_pfCMGetAPI2( "cifx_xchanneldownload", (RTS_VOID_FCTPTR *)&pfcifx_xchanneldownload, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x35317A0D), 0x03050800)
	#define CAL_cifx_xchanneldownload  pfcifx_xchanneldownload
	#define CHK_cifx_xchanneldownload  (pfcifx_xchanneldownload != NULL)
	#define EXP_cifx_xchanneldownload   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchanneldownload", (RTS_UINTPTR)cifx_xchanneldownload, 1, RTSITF_GET_SIGNATURE(0, 0x35317A0D), 0x03050800) 
#endif


/**
 * <description>cifx_xchannelextendedstatusblock</description>
 */
typedef struct tagcifx_xchannelextendedstatusblock_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiCmd;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiOffset;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiDataLen;			/* VAR_INPUT */	
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelExtendedStatusBlock;	/* VAR_OUTPUT */	
} cifx_xchannelextendedstatusblock_struct;

void CDECL CDECL_EXT cifx_xchannelextendedstatusblock(cifx_xchannelextendedstatusblock_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELEXTENDEDSTATUSBLOCK_IEC) (cifx_xchannelextendedstatusblock_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELEXTENDEDSTATUSBLOCK_NOTIMPLEMENTED)
	#define USE_cifx_xchannelextendedstatusblock
	#define EXT_cifx_xchannelextendedstatusblock
	#define GET_cifx_xchannelextendedstatusblock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelextendedstatusblock(p0) 
	#define CHK_cifx_xchannelextendedstatusblock  FALSE
	#define EXP_cifx_xchannelextendedstatusblock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelextendedstatusblock
	#define EXT_cifx_xchannelextendedstatusblock
	#define GET_cifx_xchannelextendedstatusblock(fl)  CAL_CMGETAPI( "cifx_xchannelextendedstatusblock" ) 
	#define CAL_cifx_xchannelextendedstatusblock  cifx_xchannelextendedstatusblock
	#define CHK_cifx_xchannelextendedstatusblock  TRUE
	#define EXP_cifx_xchannelextendedstatusblock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelextendedstatusblock", (RTS_UINTPTR)cifx_xchannelextendedstatusblock, 1, RTSITF_GET_SIGNATURE(0, 0xA2DF8FC9), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelextendedstatusblock
	#define EXT_cifx_xchannelextendedstatusblock
	#define GET_cifx_xchannelextendedstatusblock(fl)  CAL_CMGETAPI( "cifx_xchannelextendedstatusblock" ) 
	#define CAL_cifx_xchannelextendedstatusblock  cifx_xchannelextendedstatusblock
	#define CHK_cifx_xchannelextendedstatusblock  TRUE
	#define EXP_cifx_xchannelextendedstatusblock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelextendedstatusblock", (RTS_UINTPTR)cifx_xchannelextendedstatusblock, 1, RTSITF_GET_SIGNATURE(0, 0xA2DF8FC9), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelextendedstatusblock
	#define EXT_CmpHilscherCIFXcifx_xchannelextendedstatusblock
	#define GET_CmpHilscherCIFXcifx_xchannelextendedstatusblock  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelextendedstatusblock  cifx_xchannelextendedstatusblock
	#define CHK_CmpHilscherCIFXcifx_xchannelextendedstatusblock  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelextendedstatusblock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelextendedstatusblock", (RTS_UINTPTR)cifx_xchannelextendedstatusblock, 1, RTSITF_GET_SIGNATURE(0, 0xA2DF8FC9), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelextendedstatusblock
	#define EXT_cifx_xchannelextendedstatusblock
	#define GET_cifx_xchannelextendedstatusblock(fl)  CAL_CMGETAPI( "cifx_xchannelextendedstatusblock" ) 
	#define CAL_cifx_xchannelextendedstatusblock  cifx_xchannelextendedstatusblock
	#define CHK_cifx_xchannelextendedstatusblock  TRUE
	#define EXP_cifx_xchannelextendedstatusblock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelextendedstatusblock", (RTS_UINTPTR)cifx_xchannelextendedstatusblock, 1, RTSITF_GET_SIGNATURE(0, 0xA2DF8FC9), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelextendedstatusblock  PFCIFX_XCHANNELEXTENDEDSTATUSBLOCK_IEC pfcifx_xchannelextendedstatusblock;
	#define EXT_cifx_xchannelextendedstatusblock  extern PFCIFX_XCHANNELEXTENDEDSTATUSBLOCK_IEC pfcifx_xchannelextendedstatusblock;
	#define GET_cifx_xchannelextendedstatusblock(fl)  s_pfCMGetAPI2( "cifx_xchannelextendedstatusblock", (RTS_VOID_FCTPTR *)&pfcifx_xchannelextendedstatusblock, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xA2DF8FC9), 0x03050800)
	#define CAL_cifx_xchannelextendedstatusblock  pfcifx_xchannelextendedstatusblock
	#define CHK_cifx_xchannelextendedstatusblock  (pfcifx_xchannelextendedstatusblock != NULL)
	#define EXP_cifx_xchannelextendedstatusblock   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelextendedstatusblock", (RTS_UINTPTR)cifx_xchannelextendedstatusblock, 1, RTSITF_GET_SIGNATURE(0, 0xA2DF8FC9), 0x03050800) 
#endif


/**
 * <description>cifx_xchannelfindfirstfile</description>
 */
typedef struct tagcifx_xchannelfindfirstfile_struct
{
	RTS_IEC_HANDLE udiChannel;			/* VAR_INPUT */	
	CIFX_DIRECTORY_ENTRY *ptDirectoryInfo;	/* VAR_INPUT */	
	RTS_IEC_BYTE *pCallbackUserData;	/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelFindFirstFile;	/* VAR_OUTPUT */	
} cifx_xchannelfindfirstfile_struct;

void CDECL CDECL_EXT cifx_xchannelfindfirstfile(cifx_xchannelfindfirstfile_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELFINDFIRSTFILE_IEC) (cifx_xchannelfindfirstfile_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELFINDFIRSTFILE_NOTIMPLEMENTED)
	#define USE_cifx_xchannelfindfirstfile
	#define EXT_cifx_xchannelfindfirstfile
	#define GET_cifx_xchannelfindfirstfile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelfindfirstfile(p0) 
	#define CHK_cifx_xchannelfindfirstfile  FALSE
	#define EXP_cifx_xchannelfindfirstfile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelfindfirstfile
	#define EXT_cifx_xchannelfindfirstfile
	#define GET_cifx_xchannelfindfirstfile(fl)  CAL_CMGETAPI( "cifx_xchannelfindfirstfile" ) 
	#define CAL_cifx_xchannelfindfirstfile  cifx_xchannelfindfirstfile
	#define CHK_cifx_xchannelfindfirstfile  TRUE
	#define EXP_cifx_xchannelfindfirstfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelfindfirstfile", (RTS_UINTPTR)cifx_xchannelfindfirstfile, 1, RTSITF_GET_SIGNATURE(0, 0x4D84CCEB), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelfindfirstfile
	#define EXT_cifx_xchannelfindfirstfile
	#define GET_cifx_xchannelfindfirstfile(fl)  CAL_CMGETAPI( "cifx_xchannelfindfirstfile" ) 
	#define CAL_cifx_xchannelfindfirstfile  cifx_xchannelfindfirstfile
	#define CHK_cifx_xchannelfindfirstfile  TRUE
	#define EXP_cifx_xchannelfindfirstfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelfindfirstfile", (RTS_UINTPTR)cifx_xchannelfindfirstfile, 1, RTSITF_GET_SIGNATURE(0, 0x4D84CCEB), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelfindfirstfile
	#define EXT_CmpHilscherCIFXcifx_xchannelfindfirstfile
	#define GET_CmpHilscherCIFXcifx_xchannelfindfirstfile  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelfindfirstfile  cifx_xchannelfindfirstfile
	#define CHK_CmpHilscherCIFXcifx_xchannelfindfirstfile  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelfindfirstfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelfindfirstfile", (RTS_UINTPTR)cifx_xchannelfindfirstfile, 1, RTSITF_GET_SIGNATURE(0, 0x4D84CCEB), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelfindfirstfile
	#define EXT_cifx_xchannelfindfirstfile
	#define GET_cifx_xchannelfindfirstfile(fl)  CAL_CMGETAPI( "cifx_xchannelfindfirstfile" ) 
	#define CAL_cifx_xchannelfindfirstfile  cifx_xchannelfindfirstfile
	#define CHK_cifx_xchannelfindfirstfile  TRUE
	#define EXP_cifx_xchannelfindfirstfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelfindfirstfile", (RTS_UINTPTR)cifx_xchannelfindfirstfile, 1, RTSITF_GET_SIGNATURE(0, 0x4D84CCEB), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelfindfirstfile  PFCIFX_XCHANNELFINDFIRSTFILE_IEC pfcifx_xchannelfindfirstfile;
	#define EXT_cifx_xchannelfindfirstfile  extern PFCIFX_XCHANNELFINDFIRSTFILE_IEC pfcifx_xchannelfindfirstfile;
	#define GET_cifx_xchannelfindfirstfile(fl)  s_pfCMGetAPI2( "cifx_xchannelfindfirstfile", (RTS_VOID_FCTPTR *)&pfcifx_xchannelfindfirstfile, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x4D84CCEB), 0x03050800)
	#define CAL_cifx_xchannelfindfirstfile  pfcifx_xchannelfindfirstfile
	#define CHK_cifx_xchannelfindfirstfile  (pfcifx_xchannelfindfirstfile != NULL)
	#define EXP_cifx_xchannelfindfirstfile   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelfindfirstfile", (RTS_UINTPTR)cifx_xchannelfindfirstfile, 1, RTSITF_GET_SIGNATURE(0, 0x4D84CCEB), 0x03050800) 
#endif


/**
 * <description>cifx_xchannelfindnextfile</description>
 */
typedef struct tagcifx_xchannelfindnextfile_struct
{
	RTS_IEC_HANDLE udiChannel;			/* VAR_INPUT */	
	CIFX_DIRECTORY_ENTRY *ptDirectoryInfo;	/* VAR_INPUT */	
	RTS_IEC_BYTE *pCallbackUserData;	/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelFindNextFile;	/* VAR_OUTPUT */	
} cifx_xchannelfindnextfile_struct;

void CDECL CDECL_EXT cifx_xchannelfindnextfile(cifx_xchannelfindnextfile_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELFINDNEXTFILE_IEC) (cifx_xchannelfindnextfile_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELFINDNEXTFILE_NOTIMPLEMENTED)
	#define USE_cifx_xchannelfindnextfile
	#define EXT_cifx_xchannelfindnextfile
	#define GET_cifx_xchannelfindnextfile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelfindnextfile(p0) 
	#define CHK_cifx_xchannelfindnextfile  FALSE
	#define EXP_cifx_xchannelfindnextfile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelfindnextfile
	#define EXT_cifx_xchannelfindnextfile
	#define GET_cifx_xchannelfindnextfile(fl)  CAL_CMGETAPI( "cifx_xchannelfindnextfile" ) 
	#define CAL_cifx_xchannelfindnextfile  cifx_xchannelfindnextfile
	#define CHK_cifx_xchannelfindnextfile  TRUE
	#define EXP_cifx_xchannelfindnextfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelfindnextfile", (RTS_UINTPTR)cifx_xchannelfindnextfile, 1, RTSITF_GET_SIGNATURE(0, 0xFF6C58F9), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelfindnextfile
	#define EXT_cifx_xchannelfindnextfile
	#define GET_cifx_xchannelfindnextfile(fl)  CAL_CMGETAPI( "cifx_xchannelfindnextfile" ) 
	#define CAL_cifx_xchannelfindnextfile  cifx_xchannelfindnextfile
	#define CHK_cifx_xchannelfindnextfile  TRUE
	#define EXP_cifx_xchannelfindnextfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelfindnextfile", (RTS_UINTPTR)cifx_xchannelfindnextfile, 1, RTSITF_GET_SIGNATURE(0, 0xFF6C58F9), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelfindnextfile
	#define EXT_CmpHilscherCIFXcifx_xchannelfindnextfile
	#define GET_CmpHilscherCIFXcifx_xchannelfindnextfile  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelfindnextfile  cifx_xchannelfindnextfile
	#define CHK_CmpHilscherCIFXcifx_xchannelfindnextfile  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelfindnextfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelfindnextfile", (RTS_UINTPTR)cifx_xchannelfindnextfile, 1, RTSITF_GET_SIGNATURE(0, 0xFF6C58F9), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelfindnextfile
	#define EXT_cifx_xchannelfindnextfile
	#define GET_cifx_xchannelfindnextfile(fl)  CAL_CMGETAPI( "cifx_xchannelfindnextfile" ) 
	#define CAL_cifx_xchannelfindnextfile  cifx_xchannelfindnextfile
	#define CHK_cifx_xchannelfindnextfile  TRUE
	#define EXP_cifx_xchannelfindnextfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelfindnextfile", (RTS_UINTPTR)cifx_xchannelfindnextfile, 1, RTSITF_GET_SIGNATURE(0, 0xFF6C58F9), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelfindnextfile  PFCIFX_XCHANNELFINDNEXTFILE_IEC pfcifx_xchannelfindnextfile;
	#define EXT_cifx_xchannelfindnextfile  extern PFCIFX_XCHANNELFINDNEXTFILE_IEC pfcifx_xchannelfindnextfile;
	#define GET_cifx_xchannelfindnextfile(fl)  s_pfCMGetAPI2( "cifx_xchannelfindnextfile", (RTS_VOID_FCTPTR *)&pfcifx_xchannelfindnextfile, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xFF6C58F9), 0x03050800)
	#define CAL_cifx_xchannelfindnextfile  pfcifx_xchannelfindnextfile
	#define CHK_cifx_xchannelfindnextfile  (pfcifx_xchannelfindnextfile != NULL)
	#define EXP_cifx_xchannelfindnextfile   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelfindnextfile", (RTS_UINTPTR)cifx_xchannelfindnextfile, 1, RTSITF_GET_SIGNATURE(0, 0xFF6C58F9), 0x03050800) 
#endif


/**
 * <description>cifx_xchannelgetmbxstate</description>
 */
typedef struct tagcifx_xchannelgetmbxstate_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT *pudiRecvPktCount;	/* VAR_INPUT */	
	RTS_IEC_UDINT *pudiSendPktCount;	/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelGetMBXState;	/* VAR_OUTPUT */	
} cifx_xchannelgetmbxstate_struct;

void CDECL CDECL_EXT cifx_xchannelgetmbxstate(cifx_xchannelgetmbxstate_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELGETMBXSTATE_IEC) (cifx_xchannelgetmbxstate_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELGETMBXSTATE_NOTIMPLEMENTED)
	#define USE_cifx_xchannelgetmbxstate
	#define EXT_cifx_xchannelgetmbxstate
	#define GET_cifx_xchannelgetmbxstate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelgetmbxstate(p0) 
	#define CHK_cifx_xchannelgetmbxstate  FALSE
	#define EXP_cifx_xchannelgetmbxstate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelgetmbxstate
	#define EXT_cifx_xchannelgetmbxstate
	#define GET_cifx_xchannelgetmbxstate(fl)  CAL_CMGETAPI( "cifx_xchannelgetmbxstate" ) 
	#define CAL_cifx_xchannelgetmbxstate  cifx_xchannelgetmbxstate
	#define CHK_cifx_xchannelgetmbxstate  TRUE
	#define EXP_cifx_xchannelgetmbxstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelgetmbxstate", (RTS_UINTPTR)cifx_xchannelgetmbxstate, 1, RTSITF_GET_SIGNATURE(0, 0xE613E244), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelgetmbxstate
	#define EXT_cifx_xchannelgetmbxstate
	#define GET_cifx_xchannelgetmbxstate(fl)  CAL_CMGETAPI( "cifx_xchannelgetmbxstate" ) 
	#define CAL_cifx_xchannelgetmbxstate  cifx_xchannelgetmbxstate
	#define CHK_cifx_xchannelgetmbxstate  TRUE
	#define EXP_cifx_xchannelgetmbxstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelgetmbxstate", (RTS_UINTPTR)cifx_xchannelgetmbxstate, 1, RTSITF_GET_SIGNATURE(0, 0xE613E244), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelgetmbxstate
	#define EXT_CmpHilscherCIFXcifx_xchannelgetmbxstate
	#define GET_CmpHilscherCIFXcifx_xchannelgetmbxstate  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelgetmbxstate  cifx_xchannelgetmbxstate
	#define CHK_CmpHilscherCIFXcifx_xchannelgetmbxstate  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelgetmbxstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelgetmbxstate", (RTS_UINTPTR)cifx_xchannelgetmbxstate, 1, RTSITF_GET_SIGNATURE(0, 0xE613E244), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelgetmbxstate
	#define EXT_cifx_xchannelgetmbxstate
	#define GET_cifx_xchannelgetmbxstate(fl)  CAL_CMGETAPI( "cifx_xchannelgetmbxstate" ) 
	#define CAL_cifx_xchannelgetmbxstate  cifx_xchannelgetmbxstate
	#define CHK_cifx_xchannelgetmbxstate  TRUE
	#define EXP_cifx_xchannelgetmbxstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelgetmbxstate", (RTS_UINTPTR)cifx_xchannelgetmbxstate, 1, RTSITF_GET_SIGNATURE(0, 0xE613E244), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelgetmbxstate  PFCIFX_XCHANNELGETMBXSTATE_IEC pfcifx_xchannelgetmbxstate;
	#define EXT_cifx_xchannelgetmbxstate  extern PFCIFX_XCHANNELGETMBXSTATE_IEC pfcifx_xchannelgetmbxstate;
	#define GET_cifx_xchannelgetmbxstate(fl)  s_pfCMGetAPI2( "cifx_xchannelgetmbxstate", (RTS_VOID_FCTPTR *)&pfcifx_xchannelgetmbxstate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xE613E244), 0x03050800)
	#define CAL_cifx_xchannelgetmbxstate  pfcifx_xchannelgetmbxstate
	#define CHK_cifx_xchannelgetmbxstate  (pfcifx_xchannelgetmbxstate != NULL)
	#define EXP_cifx_xchannelgetmbxstate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelgetmbxstate", (RTS_UINTPTR)cifx_xchannelgetmbxstate, 1, RTSITF_GET_SIGNATURE(0, 0xE613E244), 0x03050800) 
#endif


/**
 * <description>cifx_xchannelgetpacket</description>
 */
typedef struct tagcifx_xchannelgetpacket_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiSize;				/* VAR_INPUT */	
	CIFX_PACKET *pRecvPkt;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiTimeout;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelGetPacket;	/* VAR_OUTPUT */	
} cifx_xchannelgetpacket_struct;

void CDECL CDECL_EXT cifx_xchannelgetpacket(cifx_xchannelgetpacket_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELGETPACKET_IEC) (cifx_xchannelgetpacket_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELGETPACKET_NOTIMPLEMENTED)
	#define USE_cifx_xchannelgetpacket
	#define EXT_cifx_xchannelgetpacket
	#define GET_cifx_xchannelgetpacket(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelgetpacket(p0) 
	#define CHK_cifx_xchannelgetpacket  FALSE
	#define EXP_cifx_xchannelgetpacket  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelgetpacket
	#define EXT_cifx_xchannelgetpacket
	#define GET_cifx_xchannelgetpacket(fl)  CAL_CMGETAPI( "cifx_xchannelgetpacket" ) 
	#define CAL_cifx_xchannelgetpacket  cifx_xchannelgetpacket
	#define CHK_cifx_xchannelgetpacket  TRUE
	#define EXP_cifx_xchannelgetpacket  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelgetpacket", (RTS_UINTPTR)cifx_xchannelgetpacket, 1, 0, 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelgetpacket
	#define EXT_cifx_xchannelgetpacket
	#define GET_cifx_xchannelgetpacket(fl)  CAL_CMGETAPI( "cifx_xchannelgetpacket" ) 
	#define CAL_cifx_xchannelgetpacket  cifx_xchannelgetpacket
	#define CHK_cifx_xchannelgetpacket  TRUE
	#define EXP_cifx_xchannelgetpacket  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelgetpacket", (RTS_UINTPTR)cifx_xchannelgetpacket, 1, 0, 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelgetpacket
	#define EXT_CmpHilscherCIFXcifx_xchannelgetpacket
	#define GET_CmpHilscherCIFXcifx_xchannelgetpacket  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelgetpacket  cifx_xchannelgetpacket
	#define CHK_CmpHilscherCIFXcifx_xchannelgetpacket  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelgetpacket  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelgetpacket", (RTS_UINTPTR)cifx_xchannelgetpacket, 1, 0, 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelgetpacket
	#define EXT_cifx_xchannelgetpacket
	#define GET_cifx_xchannelgetpacket(fl)  CAL_CMGETAPI( "cifx_xchannelgetpacket" ) 
	#define CAL_cifx_xchannelgetpacket  cifx_xchannelgetpacket
	#define CHK_cifx_xchannelgetpacket  TRUE
	#define EXP_cifx_xchannelgetpacket  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelgetpacket", (RTS_UINTPTR)cifx_xchannelgetpacket, 1, 0, 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelgetpacket  PFCIFX_XCHANNELGETPACKET_IEC pfcifx_xchannelgetpacket;
	#define EXT_cifx_xchannelgetpacket  extern PFCIFX_XCHANNELGETPACKET_IEC pfcifx_xchannelgetpacket;
	#define GET_cifx_xchannelgetpacket(fl)  s_pfCMGetAPI2( "cifx_xchannelgetpacket", (RTS_VOID_FCTPTR *)&pfcifx_xchannelgetpacket, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0x03050800)
	#define CAL_cifx_xchannelgetpacket  pfcifx_xchannelgetpacket
	#define CHK_cifx_xchannelgetpacket  (pfcifx_xchannelgetpacket != NULL)
	#define EXP_cifx_xchannelgetpacket   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelgetpacket", (RTS_UINTPTR)cifx_xchannelgetpacket, 1, 0, 0x03050800) 
#endif


/**
 *Sets the timeout of the packets sent to this channel
 */
typedef struct tagcifx_xchannelgetpackettimeout_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	/* Channel Handle */
	RTS_IEC_UDINT *ulTimeout;			/* VAR_INPUT */	/* Timeout in ms */
	RTS_IEC_RESULT CIFX_xChannelGetPacketTimeout;	/* VAR_OUTPUT */	
} cifx_xchannelgetpackettimeout_struct;

void CDECL CDECL_EXT cifx_xchannelgetpackettimeout(cifx_xchannelgetpackettimeout_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELGETPACKETTIMEOUT_IEC) (cifx_xchannelgetpackettimeout_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELGETPACKETTIMEOUT_NOTIMPLEMENTED)
	#define USE_cifx_xchannelgetpackettimeout
	#define EXT_cifx_xchannelgetpackettimeout
	#define GET_cifx_xchannelgetpackettimeout(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelgetpackettimeout(p0) 
	#define CHK_cifx_xchannelgetpackettimeout  FALSE
	#define EXP_cifx_xchannelgetpackettimeout  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelgetpackettimeout
	#define EXT_cifx_xchannelgetpackettimeout
	#define GET_cifx_xchannelgetpackettimeout(fl)  CAL_CMGETAPI( "cifx_xchannelgetpackettimeout" ) 
	#define CAL_cifx_xchannelgetpackettimeout  cifx_xchannelgetpackettimeout
	#define CHK_cifx_xchannelgetpackettimeout  TRUE
	#define EXP_cifx_xchannelgetpackettimeout  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelgetpackettimeout", (RTS_UINTPTR)cifx_xchannelgetpackettimeout, 1, RTSITF_GET_SIGNATURE(0, 0x0FB236A9), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelgetpackettimeout
	#define EXT_cifx_xchannelgetpackettimeout
	#define GET_cifx_xchannelgetpackettimeout(fl)  CAL_CMGETAPI( "cifx_xchannelgetpackettimeout" ) 
	#define CAL_cifx_xchannelgetpackettimeout  cifx_xchannelgetpackettimeout
	#define CHK_cifx_xchannelgetpackettimeout  TRUE
	#define EXP_cifx_xchannelgetpackettimeout  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelgetpackettimeout", (RTS_UINTPTR)cifx_xchannelgetpackettimeout, 1, RTSITF_GET_SIGNATURE(0, 0x0FB236A9), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelgetpackettimeout
	#define EXT_CmpHilscherCIFXcifx_xchannelgetpackettimeout
	#define GET_CmpHilscherCIFXcifx_xchannelgetpackettimeout  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelgetpackettimeout  cifx_xchannelgetpackettimeout
	#define CHK_CmpHilscherCIFXcifx_xchannelgetpackettimeout  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelgetpackettimeout  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelgetpackettimeout", (RTS_UINTPTR)cifx_xchannelgetpackettimeout, 1, RTSITF_GET_SIGNATURE(0, 0x0FB236A9), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelgetpackettimeout
	#define EXT_cifx_xchannelgetpackettimeout
	#define GET_cifx_xchannelgetpackettimeout(fl)  CAL_CMGETAPI( "cifx_xchannelgetpackettimeout" ) 
	#define CAL_cifx_xchannelgetpackettimeout  cifx_xchannelgetpackettimeout
	#define CHK_cifx_xchannelgetpackettimeout  TRUE
	#define EXP_cifx_xchannelgetpackettimeout  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelgetpackettimeout", (RTS_UINTPTR)cifx_xchannelgetpackettimeout, 1, RTSITF_GET_SIGNATURE(0, 0x0FB236A9), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelgetpackettimeout  PFCIFX_XCHANNELGETPACKETTIMEOUT_IEC pfcifx_xchannelgetpackettimeout;
	#define EXT_cifx_xchannelgetpackettimeout  extern PFCIFX_XCHANNELGETPACKETTIMEOUT_IEC pfcifx_xchannelgetpackettimeout;
	#define GET_cifx_xchannelgetpackettimeout(fl)  s_pfCMGetAPI2( "cifx_xchannelgetpackettimeout", (RTS_VOID_FCTPTR *)&pfcifx_xchannelgetpackettimeout, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x0FB236A9), 0x03050800)
	#define CAL_cifx_xchannelgetpackettimeout  pfcifx_xchannelgetpackettimeout
	#define CHK_cifx_xchannelgetpackettimeout  (pfcifx_xchannelgetpackettimeout != NULL)
	#define EXP_cifx_xchannelgetpackettimeout   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelgetpackettimeout", (RTS_UINTPTR)cifx_xchannelgetpackettimeout, 1, RTSITF_GET_SIGNATURE(0, 0x0FB236A9), 0x03050800) 
#endif


/**
 * <description>cifx_xchannelgetsendpacket</description>
 */
typedef struct tagcifx_xchannelgetsendpacket_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiSize;				/* VAR_INPUT */	
	CIFX_PACKET *pRecvPkt;				/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelGetSendPacket;	/* VAR_OUTPUT */	
} cifx_xchannelgetsendpacket_struct;

void CDECL CDECL_EXT cifx_xchannelgetsendpacket(cifx_xchannelgetsendpacket_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELGETSENDPACKET_IEC) (cifx_xchannelgetsendpacket_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELGETSENDPACKET_NOTIMPLEMENTED)
	#define USE_cifx_xchannelgetsendpacket
	#define EXT_cifx_xchannelgetsendpacket
	#define GET_cifx_xchannelgetsendpacket(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelgetsendpacket(p0) 
	#define CHK_cifx_xchannelgetsendpacket  FALSE
	#define EXP_cifx_xchannelgetsendpacket  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelgetsendpacket
	#define EXT_cifx_xchannelgetsendpacket
	#define GET_cifx_xchannelgetsendpacket(fl)  CAL_CMGETAPI( "cifx_xchannelgetsendpacket" ) 
	#define CAL_cifx_xchannelgetsendpacket  cifx_xchannelgetsendpacket
	#define CHK_cifx_xchannelgetsendpacket  TRUE
	#define EXP_cifx_xchannelgetsendpacket  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelgetsendpacket", (RTS_UINTPTR)cifx_xchannelgetsendpacket, 1, 0, 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelgetsendpacket
	#define EXT_cifx_xchannelgetsendpacket
	#define GET_cifx_xchannelgetsendpacket(fl)  CAL_CMGETAPI( "cifx_xchannelgetsendpacket" ) 
	#define CAL_cifx_xchannelgetsendpacket  cifx_xchannelgetsendpacket
	#define CHK_cifx_xchannelgetsendpacket  TRUE
	#define EXP_cifx_xchannelgetsendpacket  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelgetsendpacket", (RTS_UINTPTR)cifx_xchannelgetsendpacket, 1, 0, 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelgetsendpacket
	#define EXT_CmpHilscherCIFXcifx_xchannelgetsendpacket
	#define GET_CmpHilscherCIFXcifx_xchannelgetsendpacket  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelgetsendpacket  cifx_xchannelgetsendpacket
	#define CHK_CmpHilscherCIFXcifx_xchannelgetsendpacket  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelgetsendpacket  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelgetsendpacket", (RTS_UINTPTR)cifx_xchannelgetsendpacket, 1, 0, 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelgetsendpacket
	#define EXT_cifx_xchannelgetsendpacket
	#define GET_cifx_xchannelgetsendpacket(fl)  CAL_CMGETAPI( "cifx_xchannelgetsendpacket" ) 
	#define CAL_cifx_xchannelgetsendpacket  cifx_xchannelgetsendpacket
	#define CHK_cifx_xchannelgetsendpacket  TRUE
	#define EXP_cifx_xchannelgetsendpacket  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelgetsendpacket", (RTS_UINTPTR)cifx_xchannelgetsendpacket, 1, 0, 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelgetsendpacket  PFCIFX_XCHANNELGETSENDPACKET_IEC pfcifx_xchannelgetsendpacket;
	#define EXT_cifx_xchannelgetsendpacket  extern PFCIFX_XCHANNELGETSENDPACKET_IEC pfcifx_xchannelgetsendpacket;
	#define GET_cifx_xchannelgetsendpacket(fl)  s_pfCMGetAPI2( "cifx_xchannelgetsendpacket", (RTS_VOID_FCTPTR *)&pfcifx_xchannelgetsendpacket, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0x03050800)
	#define CAL_cifx_xchannelgetsendpacket  pfcifx_xchannelgetsendpacket
	#define CHK_cifx_xchannelgetsendpacket  (pfcifx_xchannelgetsendpacket != NULL)
	#define EXP_cifx_xchannelgetsendpacket   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelgetsendpacket", (RTS_UINTPTR)cifx_xchannelgetsendpacket, 1, 0, 0x03050800) 
#endif


/**
 * <description>cifx_xchannelhoststate</description>
 */
typedef struct tagcifx_xchannelhoststate_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiCmd;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pudiState;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiTimeout;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelHostState;	/* VAR_OUTPUT */	
} cifx_xchannelhoststate_struct;

void CDECL CDECL_EXT cifx_xchannelhoststate(cifx_xchannelhoststate_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELHOSTSTATE_IEC) (cifx_xchannelhoststate_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELHOSTSTATE_NOTIMPLEMENTED)
	#define USE_cifx_xchannelhoststate
	#define EXT_cifx_xchannelhoststate
	#define GET_cifx_xchannelhoststate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelhoststate(p0) 
	#define CHK_cifx_xchannelhoststate  FALSE
	#define EXP_cifx_xchannelhoststate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelhoststate
	#define EXT_cifx_xchannelhoststate
	#define GET_cifx_xchannelhoststate(fl)  CAL_CMGETAPI( "cifx_xchannelhoststate" ) 
	#define CAL_cifx_xchannelhoststate  cifx_xchannelhoststate
	#define CHK_cifx_xchannelhoststate  TRUE
	#define EXP_cifx_xchannelhoststate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelhoststate", (RTS_UINTPTR)cifx_xchannelhoststate, 1, RTSITF_GET_SIGNATURE(0, 0x629A3BDA), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelhoststate
	#define EXT_cifx_xchannelhoststate
	#define GET_cifx_xchannelhoststate(fl)  CAL_CMGETAPI( "cifx_xchannelhoststate" ) 
	#define CAL_cifx_xchannelhoststate  cifx_xchannelhoststate
	#define CHK_cifx_xchannelhoststate  TRUE
	#define EXP_cifx_xchannelhoststate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelhoststate", (RTS_UINTPTR)cifx_xchannelhoststate, 1, RTSITF_GET_SIGNATURE(0, 0x629A3BDA), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelhoststate
	#define EXT_CmpHilscherCIFXcifx_xchannelhoststate
	#define GET_CmpHilscherCIFXcifx_xchannelhoststate  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelhoststate  cifx_xchannelhoststate
	#define CHK_CmpHilscherCIFXcifx_xchannelhoststate  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelhoststate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelhoststate", (RTS_UINTPTR)cifx_xchannelhoststate, 1, RTSITF_GET_SIGNATURE(0, 0x629A3BDA), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelhoststate
	#define EXT_cifx_xchannelhoststate
	#define GET_cifx_xchannelhoststate(fl)  CAL_CMGETAPI( "cifx_xchannelhoststate" ) 
	#define CAL_cifx_xchannelhoststate  cifx_xchannelhoststate
	#define CHK_cifx_xchannelhoststate  TRUE
	#define EXP_cifx_xchannelhoststate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelhoststate", (RTS_UINTPTR)cifx_xchannelhoststate, 1, RTSITF_GET_SIGNATURE(0, 0x629A3BDA), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelhoststate  PFCIFX_XCHANNELHOSTSTATE_IEC pfcifx_xchannelhoststate;
	#define EXT_cifx_xchannelhoststate  extern PFCIFX_XCHANNELHOSTSTATE_IEC pfcifx_xchannelhoststate;
	#define GET_cifx_xchannelhoststate(fl)  s_pfCMGetAPI2( "cifx_xchannelhoststate", (RTS_VOID_FCTPTR *)&pfcifx_xchannelhoststate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x629A3BDA), 0x03050800)
	#define CAL_cifx_xchannelhoststate  pfcifx_xchannelhoststate
	#define CHK_cifx_xchannelhoststate  (pfcifx_xchannelhoststate != NULL)
	#define EXP_cifx_xchannelhoststate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelhoststate", (RTS_UINTPTR)cifx_xchannelhoststate, 1, RTSITF_GET_SIGNATURE(0, 0x629A3BDA), 0x03050800) 
#endif


/**
 * <description>cifx_xchannelinfo</description>
 */
typedef struct tagcifx_xchannelinfo_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiSize;				/* VAR_INPUT */	
	CIFX_CHANNEL_INFORMATION *pChannelinfo;	/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelInfo;	/* VAR_OUTPUT */	
} cifx_xchannelinfo_struct;

void CDECL CDECL_EXT cifx_xchannelinfo(cifx_xchannelinfo_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELINFO_IEC) (cifx_xchannelinfo_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELINFO_NOTIMPLEMENTED)
	#define USE_cifx_xchannelinfo
	#define EXT_cifx_xchannelinfo
	#define GET_cifx_xchannelinfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelinfo(p0) 
	#define CHK_cifx_xchannelinfo  FALSE
	#define EXP_cifx_xchannelinfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelinfo
	#define EXT_cifx_xchannelinfo
	#define GET_cifx_xchannelinfo(fl)  CAL_CMGETAPI( "cifx_xchannelinfo" ) 
	#define CAL_cifx_xchannelinfo  cifx_xchannelinfo
	#define CHK_cifx_xchannelinfo  TRUE
	#define EXP_cifx_xchannelinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelinfo", (RTS_UINTPTR)cifx_xchannelinfo, 1, RTSITF_GET_SIGNATURE(0, 0x8B453ECC), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelinfo
	#define EXT_cifx_xchannelinfo
	#define GET_cifx_xchannelinfo(fl)  CAL_CMGETAPI( "cifx_xchannelinfo" ) 
	#define CAL_cifx_xchannelinfo  cifx_xchannelinfo
	#define CHK_cifx_xchannelinfo  TRUE
	#define EXP_cifx_xchannelinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelinfo", (RTS_UINTPTR)cifx_xchannelinfo, 1, RTSITF_GET_SIGNATURE(0, 0x8B453ECC), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelinfo
	#define EXT_CmpHilscherCIFXcifx_xchannelinfo
	#define GET_CmpHilscherCIFXcifx_xchannelinfo  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelinfo  cifx_xchannelinfo
	#define CHK_CmpHilscherCIFXcifx_xchannelinfo  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelinfo", (RTS_UINTPTR)cifx_xchannelinfo, 1, RTSITF_GET_SIGNATURE(0, 0x8B453ECC), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelinfo
	#define EXT_cifx_xchannelinfo
	#define GET_cifx_xchannelinfo(fl)  CAL_CMGETAPI( "cifx_xchannelinfo" ) 
	#define CAL_cifx_xchannelinfo  cifx_xchannelinfo
	#define CHK_cifx_xchannelinfo  TRUE
	#define EXP_cifx_xchannelinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelinfo", (RTS_UINTPTR)cifx_xchannelinfo, 1, RTSITF_GET_SIGNATURE(0, 0x8B453ECC), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelinfo  PFCIFX_XCHANNELINFO_IEC pfcifx_xchannelinfo;
	#define EXT_cifx_xchannelinfo  extern PFCIFX_XCHANNELINFO_IEC pfcifx_xchannelinfo;
	#define GET_cifx_xchannelinfo(fl)  s_pfCMGetAPI2( "cifx_xchannelinfo", (RTS_VOID_FCTPTR *)&pfcifx_xchannelinfo, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x8B453ECC), 0x03050800)
	#define CAL_cifx_xchannelinfo  pfcifx_xchannelinfo
	#define CHK_cifx_xchannelinfo  (pfcifx_xchannelinfo != NULL)
	#define EXP_cifx_xchannelinfo   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelinfo", (RTS_UINTPTR)cifx_xchannelinfo, 1, RTSITF_GET_SIGNATURE(0, 0x8B453ECC), 0x03050800) 
#endif


/**
 * <description>cifx_xchannelioinfo</description>
 */
typedef struct tagcifx_xchannelioinfo_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiCmd;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiArea;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiSize;				/* VAR_INPUT */	
	CIFX_CHANNEL_INFORMATION *pChannelinfo;	/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelIOInfo;	/* VAR_OUTPUT */	
} cifx_xchannelioinfo_struct;

void CDECL CDECL_EXT cifx_xchannelioinfo(cifx_xchannelioinfo_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELIOINFO_IEC) (cifx_xchannelioinfo_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELIOINFO_NOTIMPLEMENTED)
	#define USE_cifx_xchannelioinfo
	#define EXT_cifx_xchannelioinfo
	#define GET_cifx_xchannelioinfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelioinfo(p0) 
	#define CHK_cifx_xchannelioinfo  FALSE
	#define EXP_cifx_xchannelioinfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelioinfo
	#define EXT_cifx_xchannelioinfo
	#define GET_cifx_xchannelioinfo(fl)  CAL_CMGETAPI( "cifx_xchannelioinfo" ) 
	#define CAL_cifx_xchannelioinfo  cifx_xchannelioinfo
	#define CHK_cifx_xchannelioinfo  TRUE
	#define EXP_cifx_xchannelioinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelioinfo", (RTS_UINTPTR)cifx_xchannelioinfo, 1, RTSITF_GET_SIGNATURE(0, 0xCB00EB62), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelioinfo
	#define EXT_cifx_xchannelioinfo
	#define GET_cifx_xchannelioinfo(fl)  CAL_CMGETAPI( "cifx_xchannelioinfo" ) 
	#define CAL_cifx_xchannelioinfo  cifx_xchannelioinfo
	#define CHK_cifx_xchannelioinfo  TRUE
	#define EXP_cifx_xchannelioinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelioinfo", (RTS_UINTPTR)cifx_xchannelioinfo, 1, RTSITF_GET_SIGNATURE(0, 0xCB00EB62), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelioinfo
	#define EXT_CmpHilscherCIFXcifx_xchannelioinfo
	#define GET_CmpHilscherCIFXcifx_xchannelioinfo  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelioinfo  cifx_xchannelioinfo
	#define CHK_CmpHilscherCIFXcifx_xchannelioinfo  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelioinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelioinfo", (RTS_UINTPTR)cifx_xchannelioinfo, 1, RTSITF_GET_SIGNATURE(0, 0xCB00EB62), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelioinfo
	#define EXT_cifx_xchannelioinfo
	#define GET_cifx_xchannelioinfo(fl)  CAL_CMGETAPI( "cifx_xchannelioinfo" ) 
	#define CAL_cifx_xchannelioinfo  cifx_xchannelioinfo
	#define CHK_cifx_xchannelioinfo  TRUE
	#define EXP_cifx_xchannelioinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelioinfo", (RTS_UINTPTR)cifx_xchannelioinfo, 1, RTSITF_GET_SIGNATURE(0, 0xCB00EB62), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelioinfo  PFCIFX_XCHANNELIOINFO_IEC pfcifx_xchannelioinfo;
	#define EXT_cifx_xchannelioinfo  extern PFCIFX_XCHANNELIOINFO_IEC pfcifx_xchannelioinfo;
	#define GET_cifx_xchannelioinfo(fl)  s_pfCMGetAPI2( "cifx_xchannelioinfo", (RTS_VOID_FCTPTR *)&pfcifx_xchannelioinfo, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xCB00EB62), 0x03050800)
	#define CAL_cifx_xchannelioinfo  pfcifx_xchannelioinfo
	#define CHK_cifx_xchannelioinfo  (pfcifx_xchannelioinfo != NULL)
	#define EXP_cifx_xchannelioinfo   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelioinfo", (RTS_UINTPTR)cifx_xchannelioinfo, 1, RTSITF_GET_SIGNATURE(0, 0xCB00EB62), 0x03050800) 
#endif


/**
 * <description>cifx_xchannelioread</description>
 */
typedef struct tagcifx_xchannelioread_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiAreaNumber;		/* VAR_INPUT */	
	RTS_IEC_UDINT udiOffset;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiDataLen;			/* VAR_INPUT */	
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiTimeout;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelIORead;	/* VAR_OUTPUT */	
} cifx_xchannelioread_struct;

void CDECL CDECL_EXT cifx_xchannelioread(cifx_xchannelioread_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELIOREAD_IEC) (cifx_xchannelioread_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELIOREAD_NOTIMPLEMENTED)
	#define USE_cifx_xchannelioread
	#define EXT_cifx_xchannelioread
	#define GET_cifx_xchannelioread(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelioread(p0) 
	#define CHK_cifx_xchannelioread  FALSE
	#define EXP_cifx_xchannelioread  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelioread
	#define EXT_cifx_xchannelioread
	#define GET_cifx_xchannelioread(fl)  CAL_CMGETAPI( "cifx_xchannelioread" ) 
	#define CAL_cifx_xchannelioread  cifx_xchannelioread
	#define CHK_cifx_xchannelioread  TRUE
	#define EXP_cifx_xchannelioread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelioread", (RTS_UINTPTR)cifx_xchannelioread, 1, RTSITF_GET_SIGNATURE(0, 0xC8A4DFC7), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelioread
	#define EXT_cifx_xchannelioread
	#define GET_cifx_xchannelioread(fl)  CAL_CMGETAPI( "cifx_xchannelioread" ) 
	#define CAL_cifx_xchannelioread  cifx_xchannelioread
	#define CHK_cifx_xchannelioread  TRUE
	#define EXP_cifx_xchannelioread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelioread", (RTS_UINTPTR)cifx_xchannelioread, 1, RTSITF_GET_SIGNATURE(0, 0xC8A4DFC7), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelioread
	#define EXT_CmpHilscherCIFXcifx_xchannelioread
	#define GET_CmpHilscherCIFXcifx_xchannelioread  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelioread  cifx_xchannelioread
	#define CHK_CmpHilscherCIFXcifx_xchannelioread  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelioread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelioread", (RTS_UINTPTR)cifx_xchannelioread, 1, RTSITF_GET_SIGNATURE(0, 0xC8A4DFC7), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelioread
	#define EXT_cifx_xchannelioread
	#define GET_cifx_xchannelioread(fl)  CAL_CMGETAPI( "cifx_xchannelioread" ) 
	#define CAL_cifx_xchannelioread  cifx_xchannelioread
	#define CHK_cifx_xchannelioread  TRUE
	#define EXP_cifx_xchannelioread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelioread", (RTS_UINTPTR)cifx_xchannelioread, 1, RTSITF_GET_SIGNATURE(0, 0xC8A4DFC7), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelioread  PFCIFX_XCHANNELIOREAD_IEC pfcifx_xchannelioread;
	#define EXT_cifx_xchannelioread  extern PFCIFX_XCHANNELIOREAD_IEC pfcifx_xchannelioread;
	#define GET_cifx_xchannelioread(fl)  s_pfCMGetAPI2( "cifx_xchannelioread", (RTS_VOID_FCTPTR *)&pfcifx_xchannelioread, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xC8A4DFC7), 0x03050800)
	#define CAL_cifx_xchannelioread  pfcifx_xchannelioread
	#define CHK_cifx_xchannelioread  (pfcifx_xchannelioread != NULL)
	#define EXP_cifx_xchannelioread   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelioread", (RTS_UINTPTR)cifx_xchannelioread, 1, RTSITF_GET_SIGNATURE(0, 0xC8A4DFC7), 0x03050800) 
#endif


/**
 * <description>cifx_xchannelioreadsenddata</description>
 */
typedef struct tagcifx_xchannelioreadsenddata_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiAreaNumber;		/* VAR_INPUT */	
	RTS_IEC_UDINT udiOffset;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiDataLen;			/* VAR_INPUT */	
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelIOReadSendData;	/* VAR_OUTPUT */	
} cifx_xchannelioreadsenddata_struct;

void CDECL CDECL_EXT cifx_xchannelioreadsenddata(cifx_xchannelioreadsenddata_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELIOREADSENDDATA_IEC) (cifx_xchannelioreadsenddata_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELIOREADSENDDATA_NOTIMPLEMENTED)
	#define USE_cifx_xchannelioreadsenddata
	#define EXT_cifx_xchannelioreadsenddata
	#define GET_cifx_xchannelioreadsenddata(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelioreadsenddata(p0) 
	#define CHK_cifx_xchannelioreadsenddata  FALSE
	#define EXP_cifx_xchannelioreadsenddata  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelioreadsenddata
	#define EXT_cifx_xchannelioreadsenddata
	#define GET_cifx_xchannelioreadsenddata(fl)  CAL_CMGETAPI( "cifx_xchannelioreadsenddata" ) 
	#define CAL_cifx_xchannelioreadsenddata  cifx_xchannelioreadsenddata
	#define CHK_cifx_xchannelioreadsenddata  TRUE
	#define EXP_cifx_xchannelioreadsenddata  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelioreadsenddata", (RTS_UINTPTR)cifx_xchannelioreadsenddata, 1, RTSITF_GET_SIGNATURE(0, 0xF2AE39F9), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelioreadsenddata
	#define EXT_cifx_xchannelioreadsenddata
	#define GET_cifx_xchannelioreadsenddata(fl)  CAL_CMGETAPI( "cifx_xchannelioreadsenddata" ) 
	#define CAL_cifx_xchannelioreadsenddata  cifx_xchannelioreadsenddata
	#define CHK_cifx_xchannelioreadsenddata  TRUE
	#define EXP_cifx_xchannelioreadsenddata  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelioreadsenddata", (RTS_UINTPTR)cifx_xchannelioreadsenddata, 1, RTSITF_GET_SIGNATURE(0, 0xF2AE39F9), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelioreadsenddata
	#define EXT_CmpHilscherCIFXcifx_xchannelioreadsenddata
	#define GET_CmpHilscherCIFXcifx_xchannelioreadsenddata  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelioreadsenddata  cifx_xchannelioreadsenddata
	#define CHK_CmpHilscherCIFXcifx_xchannelioreadsenddata  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelioreadsenddata  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelioreadsenddata", (RTS_UINTPTR)cifx_xchannelioreadsenddata, 1, RTSITF_GET_SIGNATURE(0, 0xF2AE39F9), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelioreadsenddata
	#define EXT_cifx_xchannelioreadsenddata
	#define GET_cifx_xchannelioreadsenddata(fl)  CAL_CMGETAPI( "cifx_xchannelioreadsenddata" ) 
	#define CAL_cifx_xchannelioreadsenddata  cifx_xchannelioreadsenddata
	#define CHK_cifx_xchannelioreadsenddata  TRUE
	#define EXP_cifx_xchannelioreadsenddata  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelioreadsenddata", (RTS_UINTPTR)cifx_xchannelioreadsenddata, 1, RTSITF_GET_SIGNATURE(0, 0xF2AE39F9), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelioreadsenddata  PFCIFX_XCHANNELIOREADSENDDATA_IEC pfcifx_xchannelioreadsenddata;
	#define EXT_cifx_xchannelioreadsenddata  extern PFCIFX_XCHANNELIOREADSENDDATA_IEC pfcifx_xchannelioreadsenddata;
	#define GET_cifx_xchannelioreadsenddata(fl)  s_pfCMGetAPI2( "cifx_xchannelioreadsenddata", (RTS_VOID_FCTPTR *)&pfcifx_xchannelioreadsenddata, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xF2AE39F9), 0x03050800)
	#define CAL_cifx_xchannelioreadsenddata  pfcifx_xchannelioreadsenddata
	#define CHK_cifx_xchannelioreadsenddata  (pfcifx_xchannelioreadsenddata != NULL)
	#define EXP_cifx_xchannelioreadsenddata   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelioreadsenddata", (RTS_UINTPTR)cifx_xchannelioreadsenddata, 1, RTSITF_GET_SIGNATURE(0, 0xF2AE39F9), 0x03050800) 
#endif


/**
 * <description>cifx_xchanneliowrite</description>
 */
typedef struct tagcifx_xchanneliowrite_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiAreaNumber;		/* VAR_INPUT */	
	RTS_IEC_UDINT udiOffset;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiDataLen;			/* VAR_INPUT */	
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiTimeout;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelIOWrite;	/* VAR_OUTPUT */	
} cifx_xchanneliowrite_struct;

void CDECL CDECL_EXT cifx_xchanneliowrite(cifx_xchanneliowrite_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELIOWRITE_IEC) (cifx_xchanneliowrite_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELIOWRITE_NOTIMPLEMENTED)
	#define USE_cifx_xchanneliowrite
	#define EXT_cifx_xchanneliowrite
	#define GET_cifx_xchanneliowrite(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchanneliowrite(p0) 
	#define CHK_cifx_xchanneliowrite  FALSE
	#define EXP_cifx_xchanneliowrite  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchanneliowrite
	#define EXT_cifx_xchanneliowrite
	#define GET_cifx_xchanneliowrite(fl)  CAL_CMGETAPI( "cifx_xchanneliowrite" ) 
	#define CAL_cifx_xchanneliowrite  cifx_xchanneliowrite
	#define CHK_cifx_xchanneliowrite  TRUE
	#define EXP_cifx_xchanneliowrite  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchanneliowrite", (RTS_UINTPTR)cifx_xchanneliowrite, 1, RTSITF_GET_SIGNATURE(0, 0xE8C87DDA), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchanneliowrite
	#define EXT_cifx_xchanneliowrite
	#define GET_cifx_xchanneliowrite(fl)  CAL_CMGETAPI( "cifx_xchanneliowrite" ) 
	#define CAL_cifx_xchanneliowrite  cifx_xchanneliowrite
	#define CHK_cifx_xchanneliowrite  TRUE
	#define EXP_cifx_xchanneliowrite  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchanneliowrite", (RTS_UINTPTR)cifx_xchanneliowrite, 1, RTSITF_GET_SIGNATURE(0, 0xE8C87DDA), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchanneliowrite
	#define EXT_CmpHilscherCIFXcifx_xchanneliowrite
	#define GET_CmpHilscherCIFXcifx_xchanneliowrite  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchanneliowrite  cifx_xchanneliowrite
	#define CHK_CmpHilscherCIFXcifx_xchanneliowrite  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchanneliowrite  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchanneliowrite", (RTS_UINTPTR)cifx_xchanneliowrite, 1, RTSITF_GET_SIGNATURE(0, 0xE8C87DDA), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchanneliowrite
	#define EXT_cifx_xchanneliowrite
	#define GET_cifx_xchanneliowrite(fl)  CAL_CMGETAPI( "cifx_xchanneliowrite" ) 
	#define CAL_cifx_xchanneliowrite  cifx_xchanneliowrite
	#define CHK_cifx_xchanneliowrite  TRUE
	#define EXP_cifx_xchanneliowrite  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchanneliowrite", (RTS_UINTPTR)cifx_xchanneliowrite, 1, RTSITF_GET_SIGNATURE(0, 0xE8C87DDA), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchanneliowrite  PFCIFX_XCHANNELIOWRITE_IEC pfcifx_xchanneliowrite;
	#define EXT_cifx_xchanneliowrite  extern PFCIFX_XCHANNELIOWRITE_IEC pfcifx_xchanneliowrite;
	#define GET_cifx_xchanneliowrite(fl)  s_pfCMGetAPI2( "cifx_xchanneliowrite", (RTS_VOID_FCTPTR *)&pfcifx_xchanneliowrite, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xE8C87DDA), 0x03050800)
	#define CAL_cifx_xchanneliowrite  pfcifx_xchanneliowrite
	#define CHK_cifx_xchanneliowrite  (pfcifx_xchanneliowrite != NULL)
	#define EXP_cifx_xchanneliowrite   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchanneliowrite", (RTS_UINTPTR)cifx_xchanneliowrite, 1, RTSITF_GET_SIGNATURE(0, 0xE8C87DDA), 0x03050800) 
#endif


/**
 * <description>cifx_xchannelopen</description>
 */
typedef struct tagcifx_xchannelopen_struct
{
	RTS_IEC_HANDLE hDriver;				/* VAR_INPUT */	
	RTS_IEC_BYTE *szBoard;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiChannel;			/* VAR_INPUT */	
	RTS_IEC_HANDLE *phChannel;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelOpen;	/* VAR_OUTPUT */	
} cifx_xchannelopen_struct;

void CDECL CDECL_EXT cifx_xchannelopen(cifx_xchannelopen_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELOPEN_IEC) (cifx_xchannelopen_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELOPEN_NOTIMPLEMENTED)
	#define USE_cifx_xchannelopen
	#define EXT_cifx_xchannelopen
	#define GET_cifx_xchannelopen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelopen(p0) 
	#define CHK_cifx_xchannelopen  FALSE
	#define EXP_cifx_xchannelopen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelopen
	#define EXT_cifx_xchannelopen
	#define GET_cifx_xchannelopen(fl)  CAL_CMGETAPI( "cifx_xchannelopen" ) 
	#define CAL_cifx_xchannelopen  cifx_xchannelopen
	#define CHK_cifx_xchannelopen  TRUE
	#define EXP_cifx_xchannelopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelopen", (RTS_UINTPTR)cifx_xchannelopen, 1, RTSITF_GET_SIGNATURE(0, 0x17CC3A73), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelopen
	#define EXT_cifx_xchannelopen
	#define GET_cifx_xchannelopen(fl)  CAL_CMGETAPI( "cifx_xchannelopen" ) 
	#define CAL_cifx_xchannelopen  cifx_xchannelopen
	#define CHK_cifx_xchannelopen  TRUE
	#define EXP_cifx_xchannelopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelopen", (RTS_UINTPTR)cifx_xchannelopen, 1, RTSITF_GET_SIGNATURE(0, 0x17CC3A73), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelopen
	#define EXT_CmpHilscherCIFXcifx_xchannelopen
	#define GET_CmpHilscherCIFXcifx_xchannelopen  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelopen  cifx_xchannelopen
	#define CHK_CmpHilscherCIFXcifx_xchannelopen  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelopen", (RTS_UINTPTR)cifx_xchannelopen, 1, RTSITF_GET_SIGNATURE(0, 0x17CC3A73), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelopen
	#define EXT_cifx_xchannelopen
	#define GET_cifx_xchannelopen(fl)  CAL_CMGETAPI( "cifx_xchannelopen" ) 
	#define CAL_cifx_xchannelopen  cifx_xchannelopen
	#define CHK_cifx_xchannelopen  TRUE
	#define EXP_cifx_xchannelopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelopen", (RTS_UINTPTR)cifx_xchannelopen, 1, RTSITF_GET_SIGNATURE(0, 0x17CC3A73), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelopen  PFCIFX_XCHANNELOPEN_IEC pfcifx_xchannelopen;
	#define EXT_cifx_xchannelopen  extern PFCIFX_XCHANNELOPEN_IEC pfcifx_xchannelopen;
	#define GET_cifx_xchannelopen(fl)  s_pfCMGetAPI2( "cifx_xchannelopen", (RTS_VOID_FCTPTR *)&pfcifx_xchannelopen, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x17CC3A73), 0x03050800)
	#define CAL_cifx_xchannelopen  pfcifx_xchannelopen
	#define CHK_cifx_xchannelopen  (pfcifx_xchannelopen != NULL)
	#define EXP_cifx_xchannelopen   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelopen", (RTS_UINTPTR)cifx_xchannelopen, 1, RTSITF_GET_SIGNATURE(0, 0x17CC3A73), 0x03050800) 
#endif


/**
 * <description>cifx_xchannelopen2</description>
 */
typedef struct tagcifx_xchannelopen2_struct
{
	RTS_IEC_HANDLE hDriver;				/* VAR_INPUT */	
	RTS_IEC_BYTE *szBoard;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiChannel;			/* VAR_INPUT */	
	RTS_IEC_HANDLE *phChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiQueueMode;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelOpen2;	/* VAR_OUTPUT */	
} cifx_xchannelopen2_struct;

void CDECL CDECL_EXT cifx_xchannelopen2(cifx_xchannelopen2_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELOPEN2_IEC) (cifx_xchannelopen2_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELOPEN2_NOTIMPLEMENTED)
	#define USE_cifx_xchannelopen2
	#define EXT_cifx_xchannelopen2
	#define GET_cifx_xchannelopen2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelopen2(p0) 
	#define CHK_cifx_xchannelopen2  FALSE
	#define EXP_cifx_xchannelopen2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelopen2
	#define EXT_cifx_xchannelopen2
	#define GET_cifx_xchannelopen2(fl)  CAL_CMGETAPI( "cifx_xchannelopen2" ) 
	#define CAL_cifx_xchannelopen2  cifx_xchannelopen2
	#define CHK_cifx_xchannelopen2  TRUE
	#define EXP_cifx_xchannelopen2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelopen2", (RTS_UINTPTR)cifx_xchannelopen2, 1, RTSITF_GET_SIGNATURE(0, 0x55FC024E), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelopen2
	#define EXT_cifx_xchannelopen2
	#define GET_cifx_xchannelopen2(fl)  CAL_CMGETAPI( "cifx_xchannelopen2" ) 
	#define CAL_cifx_xchannelopen2  cifx_xchannelopen2
	#define CHK_cifx_xchannelopen2  TRUE
	#define EXP_cifx_xchannelopen2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelopen2", (RTS_UINTPTR)cifx_xchannelopen2, 1, RTSITF_GET_SIGNATURE(0, 0x55FC024E), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelopen2
	#define EXT_CmpHilscherCIFXcifx_xchannelopen2
	#define GET_CmpHilscherCIFXcifx_xchannelopen2  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelopen2  cifx_xchannelopen2
	#define CHK_CmpHilscherCIFXcifx_xchannelopen2  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelopen2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelopen2", (RTS_UINTPTR)cifx_xchannelopen2, 1, RTSITF_GET_SIGNATURE(0, 0x55FC024E), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelopen2
	#define EXT_cifx_xchannelopen2
	#define GET_cifx_xchannelopen2(fl)  CAL_CMGETAPI( "cifx_xchannelopen2" ) 
	#define CAL_cifx_xchannelopen2  cifx_xchannelopen2
	#define CHK_cifx_xchannelopen2  TRUE
	#define EXP_cifx_xchannelopen2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelopen2", (RTS_UINTPTR)cifx_xchannelopen2, 1, RTSITF_GET_SIGNATURE(0, 0x55FC024E), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelopen2  PFCIFX_XCHANNELOPEN2_IEC pfcifx_xchannelopen2;
	#define EXT_cifx_xchannelopen2  extern PFCIFX_XCHANNELOPEN2_IEC pfcifx_xchannelopen2;
	#define GET_cifx_xchannelopen2(fl)  s_pfCMGetAPI2( "cifx_xchannelopen2", (RTS_VOID_FCTPTR *)&pfcifx_xchannelopen2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x55FC024E), 0x03050800)
	#define CAL_cifx_xchannelopen2  pfcifx_xchannelopen2
	#define CHK_cifx_xchannelopen2  (pfcifx_xchannelopen2 != NULL)
	#define EXP_cifx_xchannelopen2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelopen2", (RTS_UINTPTR)cifx_xchannelopen2, 1, RTSITF_GET_SIGNATURE(0, 0x55FC024E), 0x03050800) 
#endif


/**
 * <description>cifx_xchannelplcactivateread</description>
 */
typedef struct tagcifx_xchannelplcactivateread_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiAreaNumber;		/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelPLCActivateRead;	/* VAR_OUTPUT */	
} cifx_xchannelplcactivateread_struct;

void CDECL CDECL_EXT cifx_xchannelplcactivateread(cifx_xchannelplcactivateread_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELPLCACTIVATEREAD_IEC) (cifx_xchannelplcactivateread_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELPLCACTIVATEREAD_NOTIMPLEMENTED)
	#define USE_cifx_xchannelplcactivateread
	#define EXT_cifx_xchannelplcactivateread
	#define GET_cifx_xchannelplcactivateread(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelplcactivateread(p0) 
	#define CHK_cifx_xchannelplcactivateread  FALSE
	#define EXP_cifx_xchannelplcactivateread  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelplcactivateread
	#define EXT_cifx_xchannelplcactivateread
	#define GET_cifx_xchannelplcactivateread(fl)  CAL_CMGETAPI( "cifx_xchannelplcactivateread" ) 
	#define CAL_cifx_xchannelplcactivateread  cifx_xchannelplcactivateread
	#define CHK_cifx_xchannelplcactivateread  TRUE
	#define EXP_cifx_xchannelplcactivateread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplcactivateread", (RTS_UINTPTR)cifx_xchannelplcactivateread, 1, RTSITF_GET_SIGNATURE(0, 0xC76B6902), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelplcactivateread
	#define EXT_cifx_xchannelplcactivateread
	#define GET_cifx_xchannelplcactivateread(fl)  CAL_CMGETAPI( "cifx_xchannelplcactivateread" ) 
	#define CAL_cifx_xchannelplcactivateread  cifx_xchannelplcactivateread
	#define CHK_cifx_xchannelplcactivateread  TRUE
	#define EXP_cifx_xchannelplcactivateread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplcactivateread", (RTS_UINTPTR)cifx_xchannelplcactivateread, 1, RTSITF_GET_SIGNATURE(0, 0xC76B6902), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelplcactivateread
	#define EXT_CmpHilscherCIFXcifx_xchannelplcactivateread
	#define GET_CmpHilscherCIFXcifx_xchannelplcactivateread  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelplcactivateread  cifx_xchannelplcactivateread
	#define CHK_CmpHilscherCIFXcifx_xchannelplcactivateread  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelplcactivateread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplcactivateread", (RTS_UINTPTR)cifx_xchannelplcactivateread, 1, RTSITF_GET_SIGNATURE(0, 0xC76B6902), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelplcactivateread
	#define EXT_cifx_xchannelplcactivateread
	#define GET_cifx_xchannelplcactivateread(fl)  CAL_CMGETAPI( "cifx_xchannelplcactivateread" ) 
	#define CAL_cifx_xchannelplcactivateread  cifx_xchannelplcactivateread
	#define CHK_cifx_xchannelplcactivateread  TRUE
	#define EXP_cifx_xchannelplcactivateread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplcactivateread", (RTS_UINTPTR)cifx_xchannelplcactivateread, 1, RTSITF_GET_SIGNATURE(0, 0xC76B6902), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelplcactivateread  PFCIFX_XCHANNELPLCACTIVATEREAD_IEC pfcifx_xchannelplcactivateread;
	#define EXT_cifx_xchannelplcactivateread  extern PFCIFX_XCHANNELPLCACTIVATEREAD_IEC pfcifx_xchannelplcactivateread;
	#define GET_cifx_xchannelplcactivateread(fl)  s_pfCMGetAPI2( "cifx_xchannelplcactivateread", (RTS_VOID_FCTPTR *)&pfcifx_xchannelplcactivateread, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xC76B6902), 0x03050800)
	#define CAL_cifx_xchannelplcactivateread  pfcifx_xchannelplcactivateread
	#define CHK_cifx_xchannelplcactivateread  (pfcifx_xchannelplcactivateread != NULL)
	#define EXP_cifx_xchannelplcactivateread   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplcactivateread", (RTS_UINTPTR)cifx_xchannelplcactivateread, 1, RTSITF_GET_SIGNATURE(0, 0xC76B6902), 0x03050800) 
#endif


/**
 * <description>cifx_xchannelplcactivatewrite</description>
 */
typedef struct tagcifx_xchannelplcactivatewrite_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiAreaNumber;		/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelPLCActivateWrite;	/* VAR_OUTPUT */	
} cifx_xchannelplcactivatewrite_struct;

void CDECL CDECL_EXT cifx_xchannelplcactivatewrite(cifx_xchannelplcactivatewrite_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELPLCACTIVATEWRITE_IEC) (cifx_xchannelplcactivatewrite_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELPLCACTIVATEWRITE_NOTIMPLEMENTED)
	#define USE_cifx_xchannelplcactivatewrite
	#define EXT_cifx_xchannelplcactivatewrite
	#define GET_cifx_xchannelplcactivatewrite(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelplcactivatewrite(p0) 
	#define CHK_cifx_xchannelplcactivatewrite  FALSE
	#define EXP_cifx_xchannelplcactivatewrite  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelplcactivatewrite
	#define EXT_cifx_xchannelplcactivatewrite
	#define GET_cifx_xchannelplcactivatewrite(fl)  CAL_CMGETAPI( "cifx_xchannelplcactivatewrite" ) 
	#define CAL_cifx_xchannelplcactivatewrite  cifx_xchannelplcactivatewrite
	#define CHK_cifx_xchannelplcactivatewrite  TRUE
	#define EXP_cifx_xchannelplcactivatewrite  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplcactivatewrite", (RTS_UINTPTR)cifx_xchannelplcactivatewrite, 1, RTSITF_GET_SIGNATURE(0, 0xD1C00795), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelplcactivatewrite
	#define EXT_cifx_xchannelplcactivatewrite
	#define GET_cifx_xchannelplcactivatewrite(fl)  CAL_CMGETAPI( "cifx_xchannelplcactivatewrite" ) 
	#define CAL_cifx_xchannelplcactivatewrite  cifx_xchannelplcactivatewrite
	#define CHK_cifx_xchannelplcactivatewrite  TRUE
	#define EXP_cifx_xchannelplcactivatewrite  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplcactivatewrite", (RTS_UINTPTR)cifx_xchannelplcactivatewrite, 1, RTSITF_GET_SIGNATURE(0, 0xD1C00795), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelplcactivatewrite
	#define EXT_CmpHilscherCIFXcifx_xchannelplcactivatewrite
	#define GET_CmpHilscherCIFXcifx_xchannelplcactivatewrite  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelplcactivatewrite  cifx_xchannelplcactivatewrite
	#define CHK_CmpHilscherCIFXcifx_xchannelplcactivatewrite  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelplcactivatewrite  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplcactivatewrite", (RTS_UINTPTR)cifx_xchannelplcactivatewrite, 1, RTSITF_GET_SIGNATURE(0, 0xD1C00795), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelplcactivatewrite
	#define EXT_cifx_xchannelplcactivatewrite
	#define GET_cifx_xchannelplcactivatewrite(fl)  CAL_CMGETAPI( "cifx_xchannelplcactivatewrite" ) 
	#define CAL_cifx_xchannelplcactivatewrite  cifx_xchannelplcactivatewrite
	#define CHK_cifx_xchannelplcactivatewrite  TRUE
	#define EXP_cifx_xchannelplcactivatewrite  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplcactivatewrite", (RTS_UINTPTR)cifx_xchannelplcactivatewrite, 1, RTSITF_GET_SIGNATURE(0, 0xD1C00795), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelplcactivatewrite  PFCIFX_XCHANNELPLCACTIVATEWRITE_IEC pfcifx_xchannelplcactivatewrite;
	#define EXT_cifx_xchannelplcactivatewrite  extern PFCIFX_XCHANNELPLCACTIVATEWRITE_IEC pfcifx_xchannelplcactivatewrite;
	#define GET_cifx_xchannelplcactivatewrite(fl)  s_pfCMGetAPI2( "cifx_xchannelplcactivatewrite", (RTS_VOID_FCTPTR *)&pfcifx_xchannelplcactivatewrite, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xD1C00795), 0x03050800)
	#define CAL_cifx_xchannelplcactivatewrite  pfcifx_xchannelplcactivatewrite
	#define CHK_cifx_xchannelplcactivatewrite  (pfcifx_xchannelplcactivatewrite != NULL)
	#define EXP_cifx_xchannelplcactivatewrite   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplcactivatewrite", (RTS_UINTPTR)cifx_xchannelplcactivatewrite, 1, RTSITF_GET_SIGNATURE(0, 0xD1C00795), 0x03050800) 
#endif


/**
 * <description>cifx_xchannelplcisreadready</description>
 */
typedef struct tagcifx_xchannelplcisreadready_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiAreaNumber;		/* VAR_INPUT */	
	RTS_IEC_UDINT *pudiReadState;		/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelPLCIsReadReady;	/* VAR_OUTPUT */	
} cifx_xchannelplcisreadready_struct;

void CDECL CDECL_EXT cifx_xchannelplcisreadready(cifx_xchannelplcisreadready_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELPLCISREADREADY_IEC) (cifx_xchannelplcisreadready_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELPLCISREADREADY_NOTIMPLEMENTED)
	#define USE_cifx_xchannelplcisreadready
	#define EXT_cifx_xchannelplcisreadready
	#define GET_cifx_xchannelplcisreadready(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelplcisreadready(p0) 
	#define CHK_cifx_xchannelplcisreadready  FALSE
	#define EXP_cifx_xchannelplcisreadready  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelplcisreadready
	#define EXT_cifx_xchannelplcisreadready
	#define GET_cifx_xchannelplcisreadready(fl)  CAL_CMGETAPI( "cifx_xchannelplcisreadready" ) 
	#define CAL_cifx_xchannelplcisreadready  cifx_xchannelplcisreadready
	#define CHK_cifx_xchannelplcisreadready  TRUE
	#define EXP_cifx_xchannelplcisreadready  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplcisreadready", (RTS_UINTPTR)cifx_xchannelplcisreadready, 1, RTSITF_GET_SIGNATURE(0, 0x0E0405F5), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelplcisreadready
	#define EXT_cifx_xchannelplcisreadready
	#define GET_cifx_xchannelplcisreadready(fl)  CAL_CMGETAPI( "cifx_xchannelplcisreadready" ) 
	#define CAL_cifx_xchannelplcisreadready  cifx_xchannelplcisreadready
	#define CHK_cifx_xchannelplcisreadready  TRUE
	#define EXP_cifx_xchannelplcisreadready  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplcisreadready", (RTS_UINTPTR)cifx_xchannelplcisreadready, 1, RTSITF_GET_SIGNATURE(0, 0x0E0405F5), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelplcisreadready
	#define EXT_CmpHilscherCIFXcifx_xchannelplcisreadready
	#define GET_CmpHilscherCIFXcifx_xchannelplcisreadready  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelplcisreadready  cifx_xchannelplcisreadready
	#define CHK_CmpHilscherCIFXcifx_xchannelplcisreadready  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelplcisreadready  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplcisreadready", (RTS_UINTPTR)cifx_xchannelplcisreadready, 1, RTSITF_GET_SIGNATURE(0, 0x0E0405F5), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelplcisreadready
	#define EXT_cifx_xchannelplcisreadready
	#define GET_cifx_xchannelplcisreadready(fl)  CAL_CMGETAPI( "cifx_xchannelplcisreadready" ) 
	#define CAL_cifx_xchannelplcisreadready  cifx_xchannelplcisreadready
	#define CHK_cifx_xchannelplcisreadready  TRUE
	#define EXP_cifx_xchannelplcisreadready  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplcisreadready", (RTS_UINTPTR)cifx_xchannelplcisreadready, 1, RTSITF_GET_SIGNATURE(0, 0x0E0405F5), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelplcisreadready  PFCIFX_XCHANNELPLCISREADREADY_IEC pfcifx_xchannelplcisreadready;
	#define EXT_cifx_xchannelplcisreadready  extern PFCIFX_XCHANNELPLCISREADREADY_IEC pfcifx_xchannelplcisreadready;
	#define GET_cifx_xchannelplcisreadready(fl)  s_pfCMGetAPI2( "cifx_xchannelplcisreadready", (RTS_VOID_FCTPTR *)&pfcifx_xchannelplcisreadready, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x0E0405F5), 0x03050800)
	#define CAL_cifx_xchannelplcisreadready  pfcifx_xchannelplcisreadready
	#define CHK_cifx_xchannelplcisreadready  (pfcifx_xchannelplcisreadready != NULL)
	#define EXP_cifx_xchannelplcisreadready   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplcisreadready", (RTS_UINTPTR)cifx_xchannelplcisreadready, 1, RTSITF_GET_SIGNATURE(0, 0x0E0405F5), 0x03050800) 
#endif


/**
 * <description>cifx_xchannelplciswriteready</description>
 */
typedef struct tagcifx_xchannelplciswriteready_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiAreaNumber;		/* VAR_INPUT */	
	RTS_IEC_UDINT *pudiWriteState;		/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelPLCIsWriteReady;	/* VAR_OUTPUT */	
} cifx_xchannelplciswriteready_struct;

void CDECL CDECL_EXT cifx_xchannelplciswriteready(cifx_xchannelplciswriteready_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELPLCISWRITEREADY_IEC) (cifx_xchannelplciswriteready_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELPLCISWRITEREADY_NOTIMPLEMENTED)
	#define USE_cifx_xchannelplciswriteready
	#define EXT_cifx_xchannelplciswriteready
	#define GET_cifx_xchannelplciswriteready(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelplciswriteready(p0) 
	#define CHK_cifx_xchannelplciswriteready  FALSE
	#define EXP_cifx_xchannelplciswriteready  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelplciswriteready
	#define EXT_cifx_xchannelplciswriteready
	#define GET_cifx_xchannelplciswriteready(fl)  CAL_CMGETAPI( "cifx_xchannelplciswriteready" ) 
	#define CAL_cifx_xchannelplciswriteready  cifx_xchannelplciswriteready
	#define CHK_cifx_xchannelplciswriteready  TRUE
	#define EXP_cifx_xchannelplciswriteready  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplciswriteready", (RTS_UINTPTR)cifx_xchannelplciswriteready, 1, RTSITF_GET_SIGNATURE(0, 0x0B75BAF6), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelplciswriteready
	#define EXT_cifx_xchannelplciswriteready
	#define GET_cifx_xchannelplciswriteready(fl)  CAL_CMGETAPI( "cifx_xchannelplciswriteready" ) 
	#define CAL_cifx_xchannelplciswriteready  cifx_xchannelplciswriteready
	#define CHK_cifx_xchannelplciswriteready  TRUE
	#define EXP_cifx_xchannelplciswriteready  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplciswriteready", (RTS_UINTPTR)cifx_xchannelplciswriteready, 1, RTSITF_GET_SIGNATURE(0, 0x0B75BAF6), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelplciswriteready
	#define EXT_CmpHilscherCIFXcifx_xchannelplciswriteready
	#define GET_CmpHilscherCIFXcifx_xchannelplciswriteready  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelplciswriteready  cifx_xchannelplciswriteready
	#define CHK_CmpHilscherCIFXcifx_xchannelplciswriteready  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelplciswriteready  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplciswriteready", (RTS_UINTPTR)cifx_xchannelplciswriteready, 1, RTSITF_GET_SIGNATURE(0, 0x0B75BAF6), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelplciswriteready
	#define EXT_cifx_xchannelplciswriteready
	#define GET_cifx_xchannelplciswriteready(fl)  CAL_CMGETAPI( "cifx_xchannelplciswriteready" ) 
	#define CAL_cifx_xchannelplciswriteready  cifx_xchannelplciswriteready
	#define CHK_cifx_xchannelplciswriteready  TRUE
	#define EXP_cifx_xchannelplciswriteready  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplciswriteready", (RTS_UINTPTR)cifx_xchannelplciswriteready, 1, RTSITF_GET_SIGNATURE(0, 0x0B75BAF6), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelplciswriteready  PFCIFX_XCHANNELPLCISWRITEREADY_IEC pfcifx_xchannelplciswriteready;
	#define EXT_cifx_xchannelplciswriteready  extern PFCIFX_XCHANNELPLCISWRITEREADY_IEC pfcifx_xchannelplciswriteready;
	#define GET_cifx_xchannelplciswriteready(fl)  s_pfCMGetAPI2( "cifx_xchannelplciswriteready", (RTS_VOID_FCTPTR *)&pfcifx_xchannelplciswriteready, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x0B75BAF6), 0x03050800)
	#define CAL_cifx_xchannelplciswriteready  pfcifx_xchannelplciswriteready
	#define CHK_cifx_xchannelplciswriteready  (pfcifx_xchannelplciswriteready != NULL)
	#define EXP_cifx_xchannelplciswriteready   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplciswriteready", (RTS_UINTPTR)cifx_xchannelplciswriteready, 1, RTSITF_GET_SIGNATURE(0, 0x0B75BAF6), 0x03050800) 
#endif


/**
 * <description>cifx_xchannelplcmemoryptr</description>
 */
typedef struct tagcifx_xchannelplcmemoryptr_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiCmd;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pMemoryInfo;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelPLCMemoryPtr;	/* VAR_OUTPUT */	
} cifx_xchannelplcmemoryptr_struct;

void CDECL CDECL_EXT cifx_xchannelplcmemoryptr(cifx_xchannelplcmemoryptr_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELPLCMEMORYPTR_IEC) (cifx_xchannelplcmemoryptr_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELPLCMEMORYPTR_NOTIMPLEMENTED)
	#define USE_cifx_xchannelplcmemoryptr
	#define EXT_cifx_xchannelplcmemoryptr
	#define GET_cifx_xchannelplcmemoryptr(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelplcmemoryptr(p0) 
	#define CHK_cifx_xchannelplcmemoryptr  FALSE
	#define EXP_cifx_xchannelplcmemoryptr  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelplcmemoryptr
	#define EXT_cifx_xchannelplcmemoryptr
	#define GET_cifx_xchannelplcmemoryptr(fl)  CAL_CMGETAPI( "cifx_xchannelplcmemoryptr" ) 
	#define CAL_cifx_xchannelplcmemoryptr  cifx_xchannelplcmemoryptr
	#define CHK_cifx_xchannelplcmemoryptr  TRUE
	#define EXP_cifx_xchannelplcmemoryptr  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplcmemoryptr", (RTS_UINTPTR)cifx_xchannelplcmemoryptr, 1, RTSITF_GET_SIGNATURE(0, 0xA17F7B17), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelplcmemoryptr
	#define EXT_cifx_xchannelplcmemoryptr
	#define GET_cifx_xchannelplcmemoryptr(fl)  CAL_CMGETAPI( "cifx_xchannelplcmemoryptr" ) 
	#define CAL_cifx_xchannelplcmemoryptr  cifx_xchannelplcmemoryptr
	#define CHK_cifx_xchannelplcmemoryptr  TRUE
	#define EXP_cifx_xchannelplcmemoryptr  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplcmemoryptr", (RTS_UINTPTR)cifx_xchannelplcmemoryptr, 1, RTSITF_GET_SIGNATURE(0, 0xA17F7B17), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelplcmemoryptr
	#define EXT_CmpHilscherCIFXcifx_xchannelplcmemoryptr
	#define GET_CmpHilscherCIFXcifx_xchannelplcmemoryptr  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelplcmemoryptr  cifx_xchannelplcmemoryptr
	#define CHK_CmpHilscherCIFXcifx_xchannelplcmemoryptr  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelplcmemoryptr  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplcmemoryptr", (RTS_UINTPTR)cifx_xchannelplcmemoryptr, 1, RTSITF_GET_SIGNATURE(0, 0xA17F7B17), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelplcmemoryptr
	#define EXT_cifx_xchannelplcmemoryptr
	#define GET_cifx_xchannelplcmemoryptr(fl)  CAL_CMGETAPI( "cifx_xchannelplcmemoryptr" ) 
	#define CAL_cifx_xchannelplcmemoryptr  cifx_xchannelplcmemoryptr
	#define CHK_cifx_xchannelplcmemoryptr  TRUE
	#define EXP_cifx_xchannelplcmemoryptr  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplcmemoryptr", (RTS_UINTPTR)cifx_xchannelplcmemoryptr, 1, RTSITF_GET_SIGNATURE(0, 0xA17F7B17), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelplcmemoryptr  PFCIFX_XCHANNELPLCMEMORYPTR_IEC pfcifx_xchannelplcmemoryptr;
	#define EXT_cifx_xchannelplcmemoryptr  extern PFCIFX_XCHANNELPLCMEMORYPTR_IEC pfcifx_xchannelplcmemoryptr;
	#define GET_cifx_xchannelplcmemoryptr(fl)  s_pfCMGetAPI2( "cifx_xchannelplcmemoryptr", (RTS_VOID_FCTPTR *)&pfcifx_xchannelplcmemoryptr, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xA17F7B17), 0x03050800)
	#define CAL_cifx_xchannelplcmemoryptr  pfcifx_xchannelplcmemoryptr
	#define CHK_cifx_xchannelplcmemoryptr  (pfcifx_xchannelplcmemoryptr != NULL)
	#define EXP_cifx_xchannelplcmemoryptr   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelplcmemoryptr", (RTS_UINTPTR)cifx_xchannelplcmemoryptr, 1, RTSITF_GET_SIGNATURE(0, 0xA17F7B17), 0x03050800) 
#endif


/**
 * <description>cifx_xchannelputpacket</description>
 */
typedef struct tagcifx_xchannelputpacket_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	CIFX_PACKET *pSendPacket;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiTimeout;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelPutPacket;	/* VAR_OUTPUT */	
} cifx_xchannelputpacket_struct;

void CDECL CDECL_EXT cifx_xchannelputpacket(cifx_xchannelputpacket_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELPUTPACKET_IEC) (cifx_xchannelputpacket_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELPUTPACKET_NOTIMPLEMENTED)
	#define USE_cifx_xchannelputpacket
	#define EXT_cifx_xchannelputpacket
	#define GET_cifx_xchannelputpacket(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelputpacket(p0) 
	#define CHK_cifx_xchannelputpacket  FALSE
	#define EXP_cifx_xchannelputpacket  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelputpacket
	#define EXT_cifx_xchannelputpacket
	#define GET_cifx_xchannelputpacket(fl)  CAL_CMGETAPI( "cifx_xchannelputpacket" ) 
	#define CAL_cifx_xchannelputpacket  cifx_xchannelputpacket
	#define CHK_cifx_xchannelputpacket  TRUE
	#define EXP_cifx_xchannelputpacket  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelputpacket", (RTS_UINTPTR)cifx_xchannelputpacket, 1, 0, 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelputpacket
	#define EXT_cifx_xchannelputpacket
	#define GET_cifx_xchannelputpacket(fl)  CAL_CMGETAPI( "cifx_xchannelputpacket" ) 
	#define CAL_cifx_xchannelputpacket  cifx_xchannelputpacket
	#define CHK_cifx_xchannelputpacket  TRUE
	#define EXP_cifx_xchannelputpacket  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelputpacket", (RTS_UINTPTR)cifx_xchannelputpacket, 1, 0, 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelputpacket
	#define EXT_CmpHilscherCIFXcifx_xchannelputpacket
	#define GET_CmpHilscherCIFXcifx_xchannelputpacket  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelputpacket  cifx_xchannelputpacket
	#define CHK_CmpHilscherCIFXcifx_xchannelputpacket  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelputpacket  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelputpacket", (RTS_UINTPTR)cifx_xchannelputpacket, 1, 0, 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelputpacket
	#define EXT_cifx_xchannelputpacket
	#define GET_cifx_xchannelputpacket(fl)  CAL_CMGETAPI( "cifx_xchannelputpacket" ) 
	#define CAL_cifx_xchannelputpacket  cifx_xchannelputpacket
	#define CHK_cifx_xchannelputpacket  TRUE
	#define EXP_cifx_xchannelputpacket  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelputpacket", (RTS_UINTPTR)cifx_xchannelputpacket, 1, 0, 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelputpacket  PFCIFX_XCHANNELPUTPACKET_IEC pfcifx_xchannelputpacket;
	#define EXT_cifx_xchannelputpacket  extern PFCIFX_XCHANNELPUTPACKET_IEC pfcifx_xchannelputpacket;
	#define GET_cifx_xchannelputpacket(fl)  s_pfCMGetAPI2( "cifx_xchannelputpacket", (RTS_VOID_FCTPTR *)&pfcifx_xchannelputpacket, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0x03050800)
	#define CAL_cifx_xchannelputpacket  pfcifx_xchannelputpacket
	#define CHK_cifx_xchannelputpacket  (pfcifx_xchannelputpacket != NULL)
	#define EXP_cifx_xchannelputpacket   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelputpacket", (RTS_UINTPTR)cifx_xchannelputpacket, 1, 0, 0x03050800) 
#endif


/**
 * <description>cifx_xchannelreset</description>
 */
typedef struct tagcifx_xchannelreset_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiResetMode;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiTimeout;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelReset;	/* VAR_OUTPUT */	
} cifx_xchannelreset_struct;

void CDECL CDECL_EXT cifx_xchannelreset(cifx_xchannelreset_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELRESET_IEC) (cifx_xchannelreset_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELRESET_NOTIMPLEMENTED)
	#define USE_cifx_xchannelreset
	#define EXT_cifx_xchannelreset
	#define GET_cifx_xchannelreset(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelreset(p0) 
	#define CHK_cifx_xchannelreset  FALSE
	#define EXP_cifx_xchannelreset  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelreset
	#define EXT_cifx_xchannelreset
	#define GET_cifx_xchannelreset(fl)  CAL_CMGETAPI( "cifx_xchannelreset" ) 
	#define CAL_cifx_xchannelreset  cifx_xchannelreset
	#define CHK_cifx_xchannelreset  TRUE
	#define EXP_cifx_xchannelreset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelreset", (RTS_UINTPTR)cifx_xchannelreset, 1, RTSITF_GET_SIGNATURE(0, 0xED071562), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelreset
	#define EXT_cifx_xchannelreset
	#define GET_cifx_xchannelreset(fl)  CAL_CMGETAPI( "cifx_xchannelreset" ) 
	#define CAL_cifx_xchannelreset  cifx_xchannelreset
	#define CHK_cifx_xchannelreset  TRUE
	#define EXP_cifx_xchannelreset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelreset", (RTS_UINTPTR)cifx_xchannelreset, 1, RTSITF_GET_SIGNATURE(0, 0xED071562), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelreset
	#define EXT_CmpHilscherCIFXcifx_xchannelreset
	#define GET_CmpHilscherCIFXcifx_xchannelreset  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelreset  cifx_xchannelreset
	#define CHK_CmpHilscherCIFXcifx_xchannelreset  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelreset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelreset", (RTS_UINTPTR)cifx_xchannelreset, 1, RTSITF_GET_SIGNATURE(0, 0xED071562), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelreset
	#define EXT_cifx_xchannelreset
	#define GET_cifx_xchannelreset(fl)  CAL_CMGETAPI( "cifx_xchannelreset" ) 
	#define CAL_cifx_xchannelreset  cifx_xchannelreset
	#define CHK_cifx_xchannelreset  TRUE
	#define EXP_cifx_xchannelreset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelreset", (RTS_UINTPTR)cifx_xchannelreset, 1, RTSITF_GET_SIGNATURE(0, 0xED071562), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelreset  PFCIFX_XCHANNELRESET_IEC pfcifx_xchannelreset;
	#define EXT_cifx_xchannelreset  extern PFCIFX_XCHANNELRESET_IEC pfcifx_xchannelreset;
	#define GET_cifx_xchannelreset(fl)  s_pfCMGetAPI2( "cifx_xchannelreset", (RTS_VOID_FCTPTR *)&pfcifx_xchannelreset, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xED071562), 0x03050800)
	#define CAL_cifx_xchannelreset  pfcifx_xchannelreset
	#define CHK_cifx_xchannelreset  (pfcifx_xchannelreset != NULL)
	#define EXP_cifx_xchannelreset   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelreset", (RTS_UINTPTR)cifx_xchannelreset, 1, RTSITF_GET_SIGNATURE(0, 0xED071562), 0x03050800) 
#endif


/**
 *Sets the timeout of the packets sent to this channel
 */
typedef struct tagcifx_xchannelsetpackettimeout_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	/* Channel Handle, CAA_hINVALID sets the timout of all channels */
	RTS_IEC_UDINT ulTimeout;			/* VAR_INPUT */	/* Timeout in ms */
	RTS_IEC_RESULT CIFX_xChannelSetPacketTimeout;	/* VAR_OUTPUT */	
} cifx_xchannelsetpackettimeout_struct;

void CDECL CDECL_EXT cifx_xchannelsetpackettimeout(cifx_xchannelsetpackettimeout_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELSETPACKETTIMEOUT_IEC) (cifx_xchannelsetpackettimeout_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELSETPACKETTIMEOUT_NOTIMPLEMENTED)
	#define USE_cifx_xchannelsetpackettimeout
	#define EXT_cifx_xchannelsetpackettimeout
	#define GET_cifx_xchannelsetpackettimeout(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelsetpackettimeout(p0) 
	#define CHK_cifx_xchannelsetpackettimeout  FALSE
	#define EXP_cifx_xchannelsetpackettimeout  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelsetpackettimeout
	#define EXT_cifx_xchannelsetpackettimeout
	#define GET_cifx_xchannelsetpackettimeout(fl)  CAL_CMGETAPI( "cifx_xchannelsetpackettimeout" ) 
	#define CAL_cifx_xchannelsetpackettimeout  cifx_xchannelsetpackettimeout
	#define CHK_cifx_xchannelsetpackettimeout  TRUE
	#define EXP_cifx_xchannelsetpackettimeout  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelsetpackettimeout", (RTS_UINTPTR)cifx_xchannelsetpackettimeout, 1, RTSITF_GET_SIGNATURE(0, 0x9C4E870E), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelsetpackettimeout
	#define EXT_cifx_xchannelsetpackettimeout
	#define GET_cifx_xchannelsetpackettimeout(fl)  CAL_CMGETAPI( "cifx_xchannelsetpackettimeout" ) 
	#define CAL_cifx_xchannelsetpackettimeout  cifx_xchannelsetpackettimeout
	#define CHK_cifx_xchannelsetpackettimeout  TRUE
	#define EXP_cifx_xchannelsetpackettimeout  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelsetpackettimeout", (RTS_UINTPTR)cifx_xchannelsetpackettimeout, 1, RTSITF_GET_SIGNATURE(0, 0x9C4E870E), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelsetpackettimeout
	#define EXT_CmpHilscherCIFXcifx_xchannelsetpackettimeout
	#define GET_CmpHilscherCIFXcifx_xchannelsetpackettimeout  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelsetpackettimeout  cifx_xchannelsetpackettimeout
	#define CHK_CmpHilscherCIFXcifx_xchannelsetpackettimeout  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelsetpackettimeout  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelsetpackettimeout", (RTS_UINTPTR)cifx_xchannelsetpackettimeout, 1, RTSITF_GET_SIGNATURE(0, 0x9C4E870E), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelsetpackettimeout
	#define EXT_cifx_xchannelsetpackettimeout
	#define GET_cifx_xchannelsetpackettimeout(fl)  CAL_CMGETAPI( "cifx_xchannelsetpackettimeout" ) 
	#define CAL_cifx_xchannelsetpackettimeout  cifx_xchannelsetpackettimeout
	#define CHK_cifx_xchannelsetpackettimeout  TRUE
	#define EXP_cifx_xchannelsetpackettimeout  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelsetpackettimeout", (RTS_UINTPTR)cifx_xchannelsetpackettimeout, 1, RTSITF_GET_SIGNATURE(0, 0x9C4E870E), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelsetpackettimeout  PFCIFX_XCHANNELSETPACKETTIMEOUT_IEC pfcifx_xchannelsetpackettimeout;
	#define EXT_cifx_xchannelsetpackettimeout  extern PFCIFX_XCHANNELSETPACKETTIMEOUT_IEC pfcifx_xchannelsetpackettimeout;
	#define GET_cifx_xchannelsetpackettimeout(fl)  s_pfCMGetAPI2( "cifx_xchannelsetpackettimeout", (RTS_VOID_FCTPTR *)&pfcifx_xchannelsetpackettimeout, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x9C4E870E), 0x03050800)
	#define CAL_cifx_xchannelsetpackettimeout  pfcifx_xchannelsetpackettimeout
	#define CHK_cifx_xchannelsetpackettimeout  (pfcifx_xchannelsetpackettimeout != NULL)
	#define EXP_cifx_xchannelsetpackettimeout   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelsetpackettimeout", (RTS_UINTPTR)cifx_xchannelsetpackettimeout, 1, RTSITF_GET_SIGNATURE(0, 0x9C4E870E), 0x03050800) 
#endif


/**
 * <description>cifx_xchannelupload</description>
 */
typedef struct tagcifx_xchannelupload_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiMode;				/* VAR_INPUT */	
	RTS_IEC_BYTE *szFileName;			/* VAR_INPUT */	
	RTS_IEC_BYTE *pbyFileData;			/* VAR_INPUT */	
	RTS_IEC_UDINT *pudiFileSize;		/* VAR_INPUT */	
	RTS_IEC_BYTE *pCallbackUserData;	/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelUpload;	/* VAR_OUTPUT */	
} cifx_xchannelupload_struct;

void CDECL CDECL_EXT cifx_xchannelupload(cifx_xchannelupload_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELUPLOAD_IEC) (cifx_xchannelupload_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELUPLOAD_NOTIMPLEMENTED)
	#define USE_cifx_xchannelupload
	#define EXT_cifx_xchannelupload
	#define GET_cifx_xchannelupload(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelupload(p0) 
	#define CHK_cifx_xchannelupload  FALSE
	#define EXP_cifx_xchannelupload  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelupload
	#define EXT_cifx_xchannelupload
	#define GET_cifx_xchannelupload(fl)  CAL_CMGETAPI( "cifx_xchannelupload" ) 
	#define CAL_cifx_xchannelupload  cifx_xchannelupload
	#define CHK_cifx_xchannelupload  TRUE
	#define EXP_cifx_xchannelupload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelupload", (RTS_UINTPTR)cifx_xchannelupload, 1, RTSITF_GET_SIGNATURE(0, 0xA44F115D), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelupload
	#define EXT_cifx_xchannelupload
	#define GET_cifx_xchannelupload(fl)  CAL_CMGETAPI( "cifx_xchannelupload" ) 
	#define CAL_cifx_xchannelupload  cifx_xchannelupload
	#define CHK_cifx_xchannelupload  TRUE
	#define EXP_cifx_xchannelupload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelupload", (RTS_UINTPTR)cifx_xchannelupload, 1, RTSITF_GET_SIGNATURE(0, 0xA44F115D), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelupload
	#define EXT_CmpHilscherCIFXcifx_xchannelupload
	#define GET_CmpHilscherCIFXcifx_xchannelupload  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelupload  cifx_xchannelupload
	#define CHK_CmpHilscherCIFXcifx_xchannelupload  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelupload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelupload", (RTS_UINTPTR)cifx_xchannelupload, 1, RTSITF_GET_SIGNATURE(0, 0xA44F115D), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelupload
	#define EXT_cifx_xchannelupload
	#define GET_cifx_xchannelupload(fl)  CAL_CMGETAPI( "cifx_xchannelupload" ) 
	#define CAL_cifx_xchannelupload  cifx_xchannelupload
	#define CHK_cifx_xchannelupload  TRUE
	#define EXP_cifx_xchannelupload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelupload", (RTS_UINTPTR)cifx_xchannelupload, 1, RTSITF_GET_SIGNATURE(0, 0xA44F115D), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelupload  PFCIFX_XCHANNELUPLOAD_IEC pfcifx_xchannelupload;
	#define EXT_cifx_xchannelupload  extern PFCIFX_XCHANNELUPLOAD_IEC pfcifx_xchannelupload;
	#define GET_cifx_xchannelupload(fl)  s_pfCMGetAPI2( "cifx_xchannelupload", (RTS_VOID_FCTPTR *)&pfcifx_xchannelupload, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xA44F115D), 0x03050800)
	#define CAL_cifx_xchannelupload  pfcifx_xchannelupload
	#define CHK_cifx_xchannelupload  (pfcifx_xchannelupload != NULL)
	#define EXP_cifx_xchannelupload   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelupload", (RTS_UINTPTR)cifx_xchannelupload, 1, RTSITF_GET_SIGNATURE(0, 0xA44F115D), 0x03050800) 
#endif


/**
 * <description>cifx_xchanneluserblock</description>
 */
typedef struct tagcifx_xchanneluserblock_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiAreaNumber;		/* VAR_INPUT */	
	RTS_IEC_UDINT udiCmd;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiOffset;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiDataLen;			/* VAR_INPUT */	
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelUserBlock;	/* VAR_OUTPUT */	
} cifx_xchanneluserblock_struct;

void CDECL CDECL_EXT cifx_xchanneluserblock(cifx_xchanneluserblock_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELUSERBLOCK_IEC) (cifx_xchanneluserblock_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELUSERBLOCK_NOTIMPLEMENTED)
	#define USE_cifx_xchanneluserblock
	#define EXT_cifx_xchanneluserblock
	#define GET_cifx_xchanneluserblock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchanneluserblock(p0) 
	#define CHK_cifx_xchanneluserblock  FALSE
	#define EXP_cifx_xchanneluserblock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchanneluserblock
	#define EXT_cifx_xchanneluserblock
	#define GET_cifx_xchanneluserblock(fl)  CAL_CMGETAPI( "cifx_xchanneluserblock" ) 
	#define CAL_cifx_xchanneluserblock  cifx_xchanneluserblock
	#define CHK_cifx_xchanneluserblock  TRUE
	#define EXP_cifx_xchanneluserblock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchanneluserblock", (RTS_UINTPTR)cifx_xchanneluserblock, 1, RTSITF_GET_SIGNATURE(0, 0x39A301B9), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchanneluserblock
	#define EXT_cifx_xchanneluserblock
	#define GET_cifx_xchanneluserblock(fl)  CAL_CMGETAPI( "cifx_xchanneluserblock" ) 
	#define CAL_cifx_xchanneluserblock  cifx_xchanneluserblock
	#define CHK_cifx_xchanneluserblock  TRUE
	#define EXP_cifx_xchanneluserblock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchanneluserblock", (RTS_UINTPTR)cifx_xchanneluserblock, 1, RTSITF_GET_SIGNATURE(0, 0x39A301B9), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchanneluserblock
	#define EXT_CmpHilscherCIFXcifx_xchanneluserblock
	#define GET_CmpHilscherCIFXcifx_xchanneluserblock  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchanneluserblock  cifx_xchanneluserblock
	#define CHK_CmpHilscherCIFXcifx_xchanneluserblock  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchanneluserblock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchanneluserblock", (RTS_UINTPTR)cifx_xchanneluserblock, 1, RTSITF_GET_SIGNATURE(0, 0x39A301B9), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchanneluserblock
	#define EXT_cifx_xchanneluserblock
	#define GET_cifx_xchanneluserblock(fl)  CAL_CMGETAPI( "cifx_xchanneluserblock" ) 
	#define CAL_cifx_xchanneluserblock  cifx_xchanneluserblock
	#define CHK_cifx_xchanneluserblock  TRUE
	#define EXP_cifx_xchanneluserblock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchanneluserblock", (RTS_UINTPTR)cifx_xchanneluserblock, 1, RTSITF_GET_SIGNATURE(0, 0x39A301B9), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchanneluserblock  PFCIFX_XCHANNELUSERBLOCK_IEC pfcifx_xchanneluserblock;
	#define EXT_cifx_xchanneluserblock  extern PFCIFX_XCHANNELUSERBLOCK_IEC pfcifx_xchanneluserblock;
	#define GET_cifx_xchanneluserblock(fl)  s_pfCMGetAPI2( "cifx_xchanneluserblock", (RTS_VOID_FCTPTR *)&pfcifx_xchanneluserblock, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x39A301B9), 0x03050800)
	#define CAL_cifx_xchanneluserblock  pfcifx_xchanneluserblock
	#define CHK_cifx_xchanneluserblock  (pfcifx_xchanneluserblock != NULL)
	#define EXP_cifx_xchanneluserblock   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchanneluserblock", (RTS_UINTPTR)cifx_xchanneluserblock, 1, RTSITF_GET_SIGNATURE(0, 0x39A301B9), 0x03050800) 
#endif


/**
 * <description>cifx_xchannelwatchdog</description>
 */
typedef struct tagcifx_xchannelwatchdog_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiCmd;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pudiTrigger;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelWatchdog;	/* VAR_OUTPUT */	
} cifx_xchannelwatchdog_struct;

void CDECL CDECL_EXT cifx_xchannelwatchdog(cifx_xchannelwatchdog_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XCHANNELWATCHDOG_IEC) (cifx_xchannelwatchdog_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XCHANNELWATCHDOG_NOTIMPLEMENTED)
	#define USE_cifx_xchannelwatchdog
	#define EXT_cifx_xchannelwatchdog
	#define GET_cifx_xchannelwatchdog(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xchannelwatchdog(p0) 
	#define CHK_cifx_xchannelwatchdog  FALSE
	#define EXP_cifx_xchannelwatchdog  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xchannelwatchdog
	#define EXT_cifx_xchannelwatchdog
	#define GET_cifx_xchannelwatchdog(fl)  CAL_CMGETAPI( "cifx_xchannelwatchdog" ) 
	#define CAL_cifx_xchannelwatchdog  cifx_xchannelwatchdog
	#define CHK_cifx_xchannelwatchdog  TRUE
	#define EXP_cifx_xchannelwatchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelwatchdog", (RTS_UINTPTR)cifx_xchannelwatchdog, 1, RTSITF_GET_SIGNATURE(0, 0x40D3DF4B), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xchannelwatchdog
	#define EXT_cifx_xchannelwatchdog
	#define GET_cifx_xchannelwatchdog(fl)  CAL_CMGETAPI( "cifx_xchannelwatchdog" ) 
	#define CAL_cifx_xchannelwatchdog  cifx_xchannelwatchdog
	#define CHK_cifx_xchannelwatchdog  TRUE
	#define EXP_cifx_xchannelwatchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelwatchdog", (RTS_UINTPTR)cifx_xchannelwatchdog, 1, RTSITF_GET_SIGNATURE(0, 0x40D3DF4B), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xchannelwatchdog
	#define EXT_CmpHilscherCIFXcifx_xchannelwatchdog
	#define GET_CmpHilscherCIFXcifx_xchannelwatchdog  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xchannelwatchdog  cifx_xchannelwatchdog
	#define CHK_CmpHilscherCIFXcifx_xchannelwatchdog  TRUE
	#define EXP_CmpHilscherCIFXcifx_xchannelwatchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelwatchdog", (RTS_UINTPTR)cifx_xchannelwatchdog, 1, RTSITF_GET_SIGNATURE(0, 0x40D3DF4B), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xchannelwatchdog
	#define EXT_cifx_xchannelwatchdog
	#define GET_cifx_xchannelwatchdog(fl)  CAL_CMGETAPI( "cifx_xchannelwatchdog" ) 
	#define CAL_cifx_xchannelwatchdog  cifx_xchannelwatchdog
	#define CHK_cifx_xchannelwatchdog  TRUE
	#define EXP_cifx_xchannelwatchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelwatchdog", (RTS_UINTPTR)cifx_xchannelwatchdog, 1, RTSITF_GET_SIGNATURE(0, 0x40D3DF4B), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xchannelwatchdog  PFCIFX_XCHANNELWATCHDOG_IEC pfcifx_xchannelwatchdog;
	#define EXT_cifx_xchannelwatchdog  extern PFCIFX_XCHANNELWATCHDOG_IEC pfcifx_xchannelwatchdog;
	#define GET_cifx_xchannelwatchdog(fl)  s_pfCMGetAPI2( "cifx_xchannelwatchdog", (RTS_VOID_FCTPTR *)&pfcifx_xchannelwatchdog, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x40D3DF4B), 0x03050800)
	#define CAL_cifx_xchannelwatchdog  pfcifx_xchannelwatchdog
	#define CHK_cifx_xchannelwatchdog  (pfcifx_xchannelwatchdog != NULL)
	#define EXP_cifx_xchannelwatchdog   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xchannelwatchdog", (RTS_UINTPTR)cifx_xchannelwatchdog, 1, RTSITF_GET_SIGNATURE(0, 0x40D3DF4B), 0x03050800) 
#endif


/**
 * <description>cifx_xdriverclose</description>
 */
typedef struct tagcifx_xdriverclose_struct
{
	RTS_IEC_HANDLE hDriver;				/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xDriverClose;	/* VAR_OUTPUT */	
} cifx_xdriverclose_struct;

void CDECL CDECL_EXT cifx_xdriverclose(cifx_xdriverclose_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XDRIVERCLOSE_IEC) (cifx_xdriverclose_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XDRIVERCLOSE_NOTIMPLEMENTED)
	#define USE_cifx_xdriverclose
	#define EXT_cifx_xdriverclose
	#define GET_cifx_xdriverclose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xdriverclose(p0) 
	#define CHK_cifx_xdriverclose  FALSE
	#define EXP_cifx_xdriverclose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xdriverclose
	#define EXT_cifx_xdriverclose
	#define GET_cifx_xdriverclose(fl)  CAL_CMGETAPI( "cifx_xdriverclose" ) 
	#define CAL_cifx_xdriverclose  cifx_xdriverclose
	#define CHK_cifx_xdriverclose  TRUE
	#define EXP_cifx_xdriverclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdriverclose", (RTS_UINTPTR)cifx_xdriverclose, 1, RTSITF_GET_SIGNATURE(0, 0x39D218C1), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xdriverclose
	#define EXT_cifx_xdriverclose
	#define GET_cifx_xdriverclose(fl)  CAL_CMGETAPI( "cifx_xdriverclose" ) 
	#define CAL_cifx_xdriverclose  cifx_xdriverclose
	#define CHK_cifx_xdriverclose  TRUE
	#define EXP_cifx_xdriverclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdriverclose", (RTS_UINTPTR)cifx_xdriverclose, 1, RTSITF_GET_SIGNATURE(0, 0x39D218C1), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xdriverclose
	#define EXT_CmpHilscherCIFXcifx_xdriverclose
	#define GET_CmpHilscherCIFXcifx_xdriverclose  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xdriverclose  cifx_xdriverclose
	#define CHK_CmpHilscherCIFXcifx_xdriverclose  TRUE
	#define EXP_CmpHilscherCIFXcifx_xdriverclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdriverclose", (RTS_UINTPTR)cifx_xdriverclose, 1, RTSITF_GET_SIGNATURE(0, 0x39D218C1), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xdriverclose
	#define EXT_cifx_xdriverclose
	#define GET_cifx_xdriverclose(fl)  CAL_CMGETAPI( "cifx_xdriverclose" ) 
	#define CAL_cifx_xdriverclose  cifx_xdriverclose
	#define CHK_cifx_xdriverclose  TRUE
	#define EXP_cifx_xdriverclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdriverclose", (RTS_UINTPTR)cifx_xdriverclose, 1, RTSITF_GET_SIGNATURE(0, 0x39D218C1), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xdriverclose  PFCIFX_XDRIVERCLOSE_IEC pfcifx_xdriverclose;
	#define EXT_cifx_xdriverclose  extern PFCIFX_XDRIVERCLOSE_IEC pfcifx_xdriverclose;
	#define GET_cifx_xdriverclose(fl)  s_pfCMGetAPI2( "cifx_xdriverclose", (RTS_VOID_FCTPTR *)&pfcifx_xdriverclose, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x39D218C1), 0x03050800)
	#define CAL_cifx_xdriverclose  pfcifx_xdriverclose
	#define CHK_cifx_xdriverclose  (pfcifx_xdriverclose != NULL)
	#define EXP_cifx_xdriverclose   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdriverclose", (RTS_UINTPTR)cifx_xdriverclose, 1, RTSITF_GET_SIGNATURE(0, 0x39D218C1), 0x03050800) 
#endif


/**
 * <description>cifx_xdriverenumboards</description>
 */
typedef struct tagcifx_xdriverenumboards_struct
{
	RTS_IEC_HANDLE hDriver;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiBoard;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiSize;				/* VAR_INPUT */	
	CIFX_BOARD_INFORMATION *pBoardInfo;	/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xDriverEnumBoards;	/* VAR_OUTPUT */	
} cifx_xdriverenumboards_struct;

void CDECL CDECL_EXT cifx_xdriverenumboards(cifx_xdriverenumboards_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XDRIVERENUMBOARDS_IEC) (cifx_xdriverenumboards_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XDRIVERENUMBOARDS_NOTIMPLEMENTED)
	#define USE_cifx_xdriverenumboards
	#define EXT_cifx_xdriverenumboards
	#define GET_cifx_xdriverenumboards(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xdriverenumboards(p0) 
	#define CHK_cifx_xdriverenumboards  FALSE
	#define EXP_cifx_xdriverenumboards  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xdriverenumboards
	#define EXT_cifx_xdriverenumboards
	#define GET_cifx_xdriverenumboards(fl)  CAL_CMGETAPI( "cifx_xdriverenumboards" ) 
	#define CAL_cifx_xdriverenumboards  cifx_xdriverenumboards
	#define CHK_cifx_xdriverenumboards  TRUE
	#define EXP_cifx_xdriverenumboards  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdriverenumboards", (RTS_UINTPTR)cifx_xdriverenumboards, 1, RTSITF_GET_SIGNATURE(0, 0x1910C175), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xdriverenumboards
	#define EXT_cifx_xdriverenumboards
	#define GET_cifx_xdriverenumboards(fl)  CAL_CMGETAPI( "cifx_xdriverenumboards" ) 
	#define CAL_cifx_xdriverenumboards  cifx_xdriverenumboards
	#define CHK_cifx_xdriverenumboards  TRUE
	#define EXP_cifx_xdriverenumboards  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdriverenumboards", (RTS_UINTPTR)cifx_xdriverenumboards, 1, RTSITF_GET_SIGNATURE(0, 0x1910C175), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xdriverenumboards
	#define EXT_CmpHilscherCIFXcifx_xdriverenumboards
	#define GET_CmpHilscherCIFXcifx_xdriverenumboards  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xdriverenumboards  cifx_xdriverenumboards
	#define CHK_CmpHilscherCIFXcifx_xdriverenumboards  TRUE
	#define EXP_CmpHilscherCIFXcifx_xdriverenumboards  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdriverenumboards", (RTS_UINTPTR)cifx_xdriverenumboards, 1, RTSITF_GET_SIGNATURE(0, 0x1910C175), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xdriverenumboards
	#define EXT_cifx_xdriverenumboards
	#define GET_cifx_xdriverenumboards(fl)  CAL_CMGETAPI( "cifx_xdriverenumboards" ) 
	#define CAL_cifx_xdriverenumboards  cifx_xdriverenumboards
	#define CHK_cifx_xdriverenumboards  TRUE
	#define EXP_cifx_xdriverenumboards  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdriverenumboards", (RTS_UINTPTR)cifx_xdriverenumboards, 1, RTSITF_GET_SIGNATURE(0, 0x1910C175), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xdriverenumboards  PFCIFX_XDRIVERENUMBOARDS_IEC pfcifx_xdriverenumboards;
	#define EXT_cifx_xdriverenumboards  extern PFCIFX_XDRIVERENUMBOARDS_IEC pfcifx_xdriverenumboards;
	#define GET_cifx_xdriverenumboards(fl)  s_pfCMGetAPI2( "cifx_xdriverenumboards", (RTS_VOID_FCTPTR *)&pfcifx_xdriverenumboards, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x1910C175), 0x03050800)
	#define CAL_cifx_xdriverenumboards  pfcifx_xdriverenumboards
	#define CHK_cifx_xdriverenumboards  (pfcifx_xdriverenumboards != NULL)
	#define EXP_cifx_xdriverenumboards   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdriverenumboards", (RTS_UINTPTR)cifx_xdriverenumboards, 1, RTSITF_GET_SIGNATURE(0, 0x1910C175), 0x03050800) 
#endif


/**
 * <description>cifx_xdriverenumchannels</description>
 */
typedef struct tagcifx_xdriverenumchannels_struct
{
	RTS_IEC_HANDLE hDriver;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiBoard;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiSize;				/* VAR_INPUT */	
	CIFX_CHANNEL_INFORMATION *pChannelinfo;	/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xDriverEnumChannels;	/* VAR_OUTPUT */	
} cifx_xdriverenumchannels_struct;

void CDECL CDECL_EXT cifx_xdriverenumchannels(cifx_xdriverenumchannels_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XDRIVERENUMCHANNELS_IEC) (cifx_xdriverenumchannels_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XDRIVERENUMCHANNELS_NOTIMPLEMENTED)
	#define USE_cifx_xdriverenumchannels
	#define EXT_cifx_xdriverenumchannels
	#define GET_cifx_xdriverenumchannels(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xdriverenumchannels(p0) 
	#define CHK_cifx_xdriverenumchannels  FALSE
	#define EXP_cifx_xdriverenumchannels  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xdriverenumchannels
	#define EXT_cifx_xdriverenumchannels
	#define GET_cifx_xdriverenumchannels(fl)  CAL_CMGETAPI( "cifx_xdriverenumchannels" ) 
	#define CAL_cifx_xdriverenumchannels  cifx_xdriverenumchannels
	#define CHK_cifx_xdriverenumchannels  TRUE
	#define EXP_cifx_xdriverenumchannels  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdriverenumchannels", (RTS_UINTPTR)cifx_xdriverenumchannels, 1, RTSITF_GET_SIGNATURE(0, 0x82DD213B), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xdriverenumchannels
	#define EXT_cifx_xdriverenumchannels
	#define GET_cifx_xdriverenumchannels(fl)  CAL_CMGETAPI( "cifx_xdriverenumchannels" ) 
	#define CAL_cifx_xdriverenumchannels  cifx_xdriverenumchannels
	#define CHK_cifx_xdriverenumchannels  TRUE
	#define EXP_cifx_xdriverenumchannels  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdriverenumchannels", (RTS_UINTPTR)cifx_xdriverenumchannels, 1, RTSITF_GET_SIGNATURE(0, 0x82DD213B), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xdriverenumchannels
	#define EXT_CmpHilscherCIFXcifx_xdriverenumchannels
	#define GET_CmpHilscherCIFXcifx_xdriverenumchannels  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xdriverenumchannels  cifx_xdriverenumchannels
	#define CHK_CmpHilscherCIFXcifx_xdriverenumchannels  TRUE
	#define EXP_CmpHilscherCIFXcifx_xdriverenumchannels  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdriverenumchannels", (RTS_UINTPTR)cifx_xdriverenumchannels, 1, RTSITF_GET_SIGNATURE(0, 0x82DD213B), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xdriverenumchannels
	#define EXT_cifx_xdriverenumchannels
	#define GET_cifx_xdriverenumchannels(fl)  CAL_CMGETAPI( "cifx_xdriverenumchannels" ) 
	#define CAL_cifx_xdriverenumchannels  cifx_xdriverenumchannels
	#define CHK_cifx_xdriverenumchannels  TRUE
	#define EXP_cifx_xdriverenumchannels  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdriverenumchannels", (RTS_UINTPTR)cifx_xdriverenumchannels, 1, RTSITF_GET_SIGNATURE(0, 0x82DD213B), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xdriverenumchannels  PFCIFX_XDRIVERENUMCHANNELS_IEC pfcifx_xdriverenumchannels;
	#define EXT_cifx_xdriverenumchannels  extern PFCIFX_XDRIVERENUMCHANNELS_IEC pfcifx_xdriverenumchannels;
	#define GET_cifx_xdriverenumchannels(fl)  s_pfCMGetAPI2( "cifx_xdriverenumchannels", (RTS_VOID_FCTPTR *)&pfcifx_xdriverenumchannels, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x82DD213B), 0x03050800)
	#define CAL_cifx_xdriverenumchannels  pfcifx_xdriverenumchannels
	#define CHK_cifx_xdriverenumchannels  (pfcifx_xdriverenumchannels != NULL)
	#define EXP_cifx_xdriverenumchannels   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdriverenumchannels", (RTS_UINTPTR)cifx_xdriverenumchannels, 1, RTSITF_GET_SIGNATURE(0, 0x82DD213B), 0x03050800) 
#endif


/**
 * <description>cifx_xdrivergeterrordescription</description>
 */
typedef struct tagcifx_xdrivergeterrordescription_struct
{
	RTS_IEC_DINT diError;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pszBuffer;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiBufferLen;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xDriverGetErrorDescription;	/* VAR_OUTPUT */	
} cifx_xdrivergeterrordescription_struct;

void CDECL CDECL_EXT cifx_xdrivergeterrordescription(cifx_xdrivergeterrordescription_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XDRIVERGETERRORDESCRIPTION_IEC) (cifx_xdrivergeterrordescription_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XDRIVERGETERRORDESCRIPTION_NOTIMPLEMENTED)
	#define USE_cifx_xdrivergeterrordescription
	#define EXT_cifx_xdrivergeterrordescription
	#define GET_cifx_xdrivergeterrordescription(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xdrivergeterrordescription(p0) 
	#define CHK_cifx_xdrivergeterrordescription  FALSE
	#define EXP_cifx_xdrivergeterrordescription  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xdrivergeterrordescription
	#define EXT_cifx_xdrivergeterrordescription
	#define GET_cifx_xdrivergeterrordescription(fl)  CAL_CMGETAPI( "cifx_xdrivergeterrordescription" ) 
	#define CAL_cifx_xdrivergeterrordescription  cifx_xdrivergeterrordescription
	#define CHK_cifx_xdrivergeterrordescription  TRUE
	#define EXP_cifx_xdrivergeterrordescription  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdrivergeterrordescription", (RTS_UINTPTR)cifx_xdrivergeterrordescription, 1, RTSITF_GET_SIGNATURE(0, 0x81139BE6), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xdrivergeterrordescription
	#define EXT_cifx_xdrivergeterrordescription
	#define GET_cifx_xdrivergeterrordescription(fl)  CAL_CMGETAPI( "cifx_xdrivergeterrordescription" ) 
	#define CAL_cifx_xdrivergeterrordescription  cifx_xdrivergeterrordescription
	#define CHK_cifx_xdrivergeterrordescription  TRUE
	#define EXP_cifx_xdrivergeterrordescription  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdrivergeterrordescription", (RTS_UINTPTR)cifx_xdrivergeterrordescription, 1, RTSITF_GET_SIGNATURE(0, 0x81139BE6), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xdrivergeterrordescription
	#define EXT_CmpHilscherCIFXcifx_xdrivergeterrordescription
	#define GET_CmpHilscherCIFXcifx_xdrivergeterrordescription  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xdrivergeterrordescription  cifx_xdrivergeterrordescription
	#define CHK_CmpHilscherCIFXcifx_xdrivergeterrordescription  TRUE
	#define EXP_CmpHilscherCIFXcifx_xdrivergeterrordescription  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdrivergeterrordescription", (RTS_UINTPTR)cifx_xdrivergeterrordescription, 1, RTSITF_GET_SIGNATURE(0, 0x81139BE6), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xdrivergeterrordescription
	#define EXT_cifx_xdrivergeterrordescription
	#define GET_cifx_xdrivergeterrordescription(fl)  CAL_CMGETAPI( "cifx_xdrivergeterrordescription" ) 
	#define CAL_cifx_xdrivergeterrordescription  cifx_xdrivergeterrordescription
	#define CHK_cifx_xdrivergeterrordescription  TRUE
	#define EXP_cifx_xdrivergeterrordescription  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdrivergeterrordescription", (RTS_UINTPTR)cifx_xdrivergeterrordescription, 1, RTSITF_GET_SIGNATURE(0, 0x81139BE6), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xdrivergeterrordescription  PFCIFX_XDRIVERGETERRORDESCRIPTION_IEC pfcifx_xdrivergeterrordescription;
	#define EXT_cifx_xdrivergeterrordescription  extern PFCIFX_XDRIVERGETERRORDESCRIPTION_IEC pfcifx_xdrivergeterrordescription;
	#define GET_cifx_xdrivergeterrordescription(fl)  s_pfCMGetAPI2( "cifx_xdrivergeterrordescription", (RTS_VOID_FCTPTR *)&pfcifx_xdrivergeterrordescription, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x81139BE6), 0x03050800)
	#define CAL_cifx_xdrivergeterrordescription  pfcifx_xdrivergeterrordescription
	#define CHK_cifx_xdrivergeterrordescription  (pfcifx_xdrivergeterrordescription != NULL)
	#define EXP_cifx_xdrivergeterrordescription   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdrivergeterrordescription", (RTS_UINTPTR)cifx_xdrivergeterrordescription, 1, RTSITF_GET_SIGNATURE(0, 0x81139BE6), 0x03050800) 
#endif


/**
 * <description>cifx_xdrivergetinformation</description>
 */
typedef struct tagcifx_xdrivergetinformation_struct
{
	RTS_IEC_HANDLE hDriver;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiSize;				/* VAR_INPUT */	
	CIFX_BOARD_INFORMATION *pDriverInfo;	/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xDriverGetInformation;	/* VAR_OUTPUT */	
} cifx_xdrivergetinformation_struct;

void CDECL CDECL_EXT cifx_xdrivergetinformation(cifx_xdrivergetinformation_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XDRIVERGETINFORMATION_IEC) (cifx_xdrivergetinformation_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XDRIVERGETINFORMATION_NOTIMPLEMENTED)
	#define USE_cifx_xdrivergetinformation
	#define EXT_cifx_xdrivergetinformation
	#define GET_cifx_xdrivergetinformation(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xdrivergetinformation(p0) 
	#define CHK_cifx_xdrivergetinformation  FALSE
	#define EXP_cifx_xdrivergetinformation  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xdrivergetinformation
	#define EXT_cifx_xdrivergetinformation
	#define GET_cifx_xdrivergetinformation(fl)  CAL_CMGETAPI( "cifx_xdrivergetinformation" ) 
	#define CAL_cifx_xdrivergetinformation  cifx_xdrivergetinformation
	#define CHK_cifx_xdrivergetinformation  TRUE
	#define EXP_cifx_xdrivergetinformation  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdrivergetinformation", (RTS_UINTPTR)cifx_xdrivergetinformation, 1, RTSITF_GET_SIGNATURE(0, 0x5DA7F834), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xdrivergetinformation
	#define EXT_cifx_xdrivergetinformation
	#define GET_cifx_xdrivergetinformation(fl)  CAL_CMGETAPI( "cifx_xdrivergetinformation" ) 
	#define CAL_cifx_xdrivergetinformation  cifx_xdrivergetinformation
	#define CHK_cifx_xdrivergetinformation  TRUE
	#define EXP_cifx_xdrivergetinformation  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdrivergetinformation", (RTS_UINTPTR)cifx_xdrivergetinformation, 1, RTSITF_GET_SIGNATURE(0, 0x5DA7F834), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xdrivergetinformation
	#define EXT_CmpHilscherCIFXcifx_xdrivergetinformation
	#define GET_CmpHilscherCIFXcifx_xdrivergetinformation  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xdrivergetinformation  cifx_xdrivergetinformation
	#define CHK_CmpHilscherCIFXcifx_xdrivergetinformation  TRUE
	#define EXP_CmpHilscherCIFXcifx_xdrivergetinformation  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdrivergetinformation", (RTS_UINTPTR)cifx_xdrivergetinformation, 1, RTSITF_GET_SIGNATURE(0, 0x5DA7F834), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xdrivergetinformation
	#define EXT_cifx_xdrivergetinformation
	#define GET_cifx_xdrivergetinformation(fl)  CAL_CMGETAPI( "cifx_xdrivergetinformation" ) 
	#define CAL_cifx_xdrivergetinformation  cifx_xdrivergetinformation
	#define CHK_cifx_xdrivergetinformation  TRUE
	#define EXP_cifx_xdrivergetinformation  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdrivergetinformation", (RTS_UINTPTR)cifx_xdrivergetinformation, 1, RTSITF_GET_SIGNATURE(0, 0x5DA7F834), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xdrivergetinformation  PFCIFX_XDRIVERGETINFORMATION_IEC pfcifx_xdrivergetinformation;
	#define EXT_cifx_xdrivergetinformation  extern PFCIFX_XDRIVERGETINFORMATION_IEC pfcifx_xdrivergetinformation;
	#define GET_cifx_xdrivergetinformation(fl)  s_pfCMGetAPI2( "cifx_xdrivergetinformation", (RTS_VOID_FCTPTR *)&pfcifx_xdrivergetinformation, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x5DA7F834), 0x03050800)
	#define CAL_cifx_xdrivergetinformation  pfcifx_xdrivergetinformation
	#define CHK_cifx_xdrivergetinformation  (pfcifx_xdrivergetinformation != NULL)
	#define EXP_cifx_xdrivergetinformation   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdrivergetinformation", (RTS_UINTPTR)cifx_xdrivergetinformation, 1, RTSITF_GET_SIGNATURE(0, 0x5DA7F834), 0x03050800) 
#endif


/**
 * <description>cifx_xdrivermemorypointer</description>
 */
typedef struct tagcifx_xdrivermemorypointer_struct
{
	RTS_IEC_HANDLE hDriver;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiBoard;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiCmd;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pMemoryInfo;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xDriverMemoryPointer;	/* VAR_OUTPUT */	
} cifx_xdrivermemorypointer_struct;

void CDECL CDECL_EXT cifx_xdrivermemorypointer(cifx_xdrivermemorypointer_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XDRIVERMEMORYPOINTER_IEC) (cifx_xdrivermemorypointer_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XDRIVERMEMORYPOINTER_NOTIMPLEMENTED)
	#define USE_cifx_xdrivermemorypointer
	#define EXT_cifx_xdrivermemorypointer
	#define GET_cifx_xdrivermemorypointer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xdrivermemorypointer(p0) 
	#define CHK_cifx_xdrivermemorypointer  FALSE
	#define EXP_cifx_xdrivermemorypointer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xdrivermemorypointer
	#define EXT_cifx_xdrivermemorypointer
	#define GET_cifx_xdrivermemorypointer(fl)  CAL_CMGETAPI( "cifx_xdrivermemorypointer" ) 
	#define CAL_cifx_xdrivermemorypointer  cifx_xdrivermemorypointer
	#define CHK_cifx_xdrivermemorypointer  TRUE
	#define EXP_cifx_xdrivermemorypointer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdrivermemorypointer", (RTS_UINTPTR)cifx_xdrivermemorypointer, 1, RTSITF_GET_SIGNATURE(0, 0x81B9C261), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xdrivermemorypointer
	#define EXT_cifx_xdrivermemorypointer
	#define GET_cifx_xdrivermemorypointer(fl)  CAL_CMGETAPI( "cifx_xdrivermemorypointer" ) 
	#define CAL_cifx_xdrivermemorypointer  cifx_xdrivermemorypointer
	#define CHK_cifx_xdrivermemorypointer  TRUE
	#define EXP_cifx_xdrivermemorypointer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdrivermemorypointer", (RTS_UINTPTR)cifx_xdrivermemorypointer, 1, RTSITF_GET_SIGNATURE(0, 0x81B9C261), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xdrivermemorypointer
	#define EXT_CmpHilscherCIFXcifx_xdrivermemorypointer
	#define GET_CmpHilscherCIFXcifx_xdrivermemorypointer  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xdrivermemorypointer  cifx_xdrivermemorypointer
	#define CHK_CmpHilscherCIFXcifx_xdrivermemorypointer  TRUE
	#define EXP_CmpHilscherCIFXcifx_xdrivermemorypointer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdrivermemorypointer", (RTS_UINTPTR)cifx_xdrivermemorypointer, 1, RTSITF_GET_SIGNATURE(0, 0x81B9C261), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xdrivermemorypointer
	#define EXT_cifx_xdrivermemorypointer
	#define GET_cifx_xdrivermemorypointer(fl)  CAL_CMGETAPI( "cifx_xdrivermemorypointer" ) 
	#define CAL_cifx_xdrivermemorypointer  cifx_xdrivermemorypointer
	#define CHK_cifx_xdrivermemorypointer  TRUE
	#define EXP_cifx_xdrivermemorypointer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdrivermemorypointer", (RTS_UINTPTR)cifx_xdrivermemorypointer, 1, RTSITF_GET_SIGNATURE(0, 0x81B9C261), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xdrivermemorypointer  PFCIFX_XDRIVERMEMORYPOINTER_IEC pfcifx_xdrivermemorypointer;
	#define EXT_cifx_xdrivermemorypointer  extern PFCIFX_XDRIVERMEMORYPOINTER_IEC pfcifx_xdrivermemorypointer;
	#define GET_cifx_xdrivermemorypointer(fl)  s_pfCMGetAPI2( "cifx_xdrivermemorypointer", (RTS_VOID_FCTPTR *)&pfcifx_xdrivermemorypointer, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x81B9C261), 0x03050800)
	#define CAL_cifx_xdrivermemorypointer  pfcifx_xdrivermemorypointer
	#define CHK_cifx_xdrivermemorypointer  (pfcifx_xdrivermemorypointer != NULL)
	#define EXP_cifx_xdrivermemorypointer   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdrivermemorypointer", (RTS_UINTPTR)cifx_xdrivermemorypointer, 1, RTSITF_GET_SIGNATURE(0, 0x81B9C261), 0x03050800) 
#endif


/**
 * <description>cifx_xdriveropen</description>
 */
typedef struct tagcifx_xdriveropen_struct
{
	RTS_IEC_HANDLE *phDriver;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xDriverOpen;	/* VAR_OUTPUT */	
} cifx_xdriveropen_struct;

void CDECL CDECL_EXT cifx_xdriveropen(cifx_xdriveropen_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XDRIVEROPEN_IEC) (cifx_xdriveropen_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XDRIVEROPEN_NOTIMPLEMENTED)
	#define USE_cifx_xdriveropen
	#define EXT_cifx_xdriveropen
	#define GET_cifx_xdriveropen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xdriveropen(p0) 
	#define CHK_cifx_xdriveropen  FALSE
	#define EXP_cifx_xdriveropen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xdriveropen
	#define EXT_cifx_xdriveropen
	#define GET_cifx_xdriveropen(fl)  CAL_CMGETAPI( "cifx_xdriveropen" ) 
	#define CAL_cifx_xdriveropen  cifx_xdriveropen
	#define CHK_cifx_xdriveropen  TRUE
	#define EXP_cifx_xdriveropen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdriveropen", (RTS_UINTPTR)cifx_xdriveropen, 1, RTSITF_GET_SIGNATURE(0, 0x8142A227), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xdriveropen
	#define EXT_cifx_xdriveropen
	#define GET_cifx_xdriveropen(fl)  CAL_CMGETAPI( "cifx_xdriveropen" ) 
	#define CAL_cifx_xdriveropen  cifx_xdriveropen
	#define CHK_cifx_xdriveropen  TRUE
	#define EXP_cifx_xdriveropen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdriveropen", (RTS_UINTPTR)cifx_xdriveropen, 1, RTSITF_GET_SIGNATURE(0, 0x8142A227), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xdriveropen
	#define EXT_CmpHilscherCIFXcifx_xdriveropen
	#define GET_CmpHilscherCIFXcifx_xdriveropen  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xdriveropen  cifx_xdriveropen
	#define CHK_CmpHilscherCIFXcifx_xdriveropen  TRUE
	#define EXP_CmpHilscherCIFXcifx_xdriveropen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdriveropen", (RTS_UINTPTR)cifx_xdriveropen, 1, RTSITF_GET_SIGNATURE(0, 0x8142A227), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xdriveropen
	#define EXT_cifx_xdriveropen
	#define GET_cifx_xdriveropen(fl)  CAL_CMGETAPI( "cifx_xdriveropen" ) 
	#define CAL_cifx_xdriveropen  cifx_xdriveropen
	#define CHK_cifx_xdriveropen  TRUE
	#define EXP_cifx_xdriveropen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdriveropen", (RTS_UINTPTR)cifx_xdriveropen, 1, RTSITF_GET_SIGNATURE(0, 0x8142A227), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xdriveropen  PFCIFX_XDRIVEROPEN_IEC pfcifx_xdriveropen;
	#define EXT_cifx_xdriveropen  extern PFCIFX_XDRIVEROPEN_IEC pfcifx_xdriveropen;
	#define GET_cifx_xdriveropen(fl)  s_pfCMGetAPI2( "cifx_xdriveropen", (RTS_VOID_FCTPTR *)&pfcifx_xdriveropen, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x8142A227), 0x03050800)
	#define CAL_cifx_xdriveropen  pfcifx_xdriveropen
	#define CHK_cifx_xdriveropen  (pfcifx_xdriveropen != NULL)
	#define EXP_cifx_xdriveropen   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xdriveropen", (RTS_UINTPTR)cifx_xdriveropen, 1, RTSITF_GET_SIGNATURE(0, 0x8142A227), 0x03050800) 
#endif


/**
 * <description>
 *	Copy the content from source (pSrc) to destination buffer (pDest).
 * </description>
 * <result><p>RESULT: Pointer to the destination buffer, where the copy was done.</p><result>
 */
typedef struct tagcifx_xmemcpy_struct
{
	RTS_IEC_BYTE *pDest;				/* VAR_INPUT */	/* <param name="pDest" type="IN">Pointer to memory address to be copied to (target)</param> */
	RTS_IEC_BYTE *pSrc;					/* VAR_INPUT */	/* <param name="pSrc" type="IN">Pointer to memory address to be copied from (source)</param> */
	RTS_IEC_UDINT udiCount;				/* VAR_INPUT */	/* <param name="udiCount" type="IN">Number of bytes to be copied</param> */
	RTS_IEC_BYTE *CIFX_xMemCpy;			/* VAR_OUTPUT */	
} cifx_xmemcpy_struct;

void CDECL CDECL_EXT cifx_xmemcpy(cifx_xmemcpy_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XMEMCPY_IEC) (cifx_xmemcpy_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XMEMCPY_NOTIMPLEMENTED)
	#define USE_cifx_xmemcpy
	#define EXT_cifx_xmemcpy
	#define GET_cifx_xmemcpy(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xmemcpy(p0) 
	#define CHK_cifx_xmemcpy  FALSE
	#define EXP_cifx_xmemcpy  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xmemcpy
	#define EXT_cifx_xmemcpy
	#define GET_cifx_xmemcpy(fl)  CAL_CMGETAPI( "cifx_xmemcpy" ) 
	#define CAL_cifx_xmemcpy  cifx_xmemcpy
	#define CHK_cifx_xmemcpy  TRUE
	#define EXP_cifx_xmemcpy  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xmemcpy", (RTS_UINTPTR)cifx_xmemcpy, 1, RTSITF_GET_SIGNATURE(0, 0xF3616FD8), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xmemcpy
	#define EXT_cifx_xmemcpy
	#define GET_cifx_xmemcpy(fl)  CAL_CMGETAPI( "cifx_xmemcpy" ) 
	#define CAL_cifx_xmemcpy  cifx_xmemcpy
	#define CHK_cifx_xmemcpy  TRUE
	#define EXP_cifx_xmemcpy  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xmemcpy", (RTS_UINTPTR)cifx_xmemcpy, 1, RTSITF_GET_SIGNATURE(0, 0xF3616FD8), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xmemcpy
	#define EXT_CmpHilscherCIFXcifx_xmemcpy
	#define GET_CmpHilscherCIFXcifx_xmemcpy  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xmemcpy  cifx_xmemcpy
	#define CHK_CmpHilscherCIFXcifx_xmemcpy  TRUE
	#define EXP_CmpHilscherCIFXcifx_xmemcpy  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xmemcpy", (RTS_UINTPTR)cifx_xmemcpy, 1, RTSITF_GET_SIGNATURE(0, 0xF3616FD8), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xmemcpy
	#define EXT_cifx_xmemcpy
	#define GET_cifx_xmemcpy(fl)  CAL_CMGETAPI( "cifx_xmemcpy" ) 
	#define CAL_cifx_xmemcpy  cifx_xmemcpy
	#define CHK_cifx_xmemcpy  TRUE
	#define EXP_cifx_xmemcpy  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xmemcpy", (RTS_UINTPTR)cifx_xmemcpy, 1, RTSITF_GET_SIGNATURE(0, 0xF3616FD8), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xmemcpy  PFCIFX_XMEMCPY_IEC pfcifx_xmemcpy;
	#define EXT_cifx_xmemcpy  extern PFCIFX_XMEMCPY_IEC pfcifx_xmemcpy;
	#define GET_cifx_xmemcpy(fl)  s_pfCMGetAPI2( "cifx_xmemcpy", (RTS_VOID_FCTPTR *)&pfcifx_xmemcpy, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xF3616FD8), 0x03050800)
	#define CAL_cifx_xmemcpy  pfcifx_xmemcpy
	#define CHK_cifx_xmemcpy  (pfcifx_xmemcpy != NULL)
	#define EXP_cifx_xmemcpy   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xmemcpy", (RTS_UINTPTR)cifx_xmemcpy, 1, RTSITF_GET_SIGNATURE(0, 0xF3616FD8), 0x03050800) 
#endif


/**
 * <description>cifx_xsysdeviceclose</description>
 */
typedef struct tagcifx_xsysdeviceclose_struct
{
	RTS_IEC_HANDLE hSysdevice;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xSysdeviceClose;	/* VAR_OUTPUT */	
} cifx_xsysdeviceclose_struct;

void CDECL CDECL_EXT cifx_xsysdeviceclose(cifx_xsysdeviceclose_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XSYSDEVICECLOSE_IEC) (cifx_xsysdeviceclose_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XSYSDEVICECLOSE_NOTIMPLEMENTED)
	#define USE_cifx_xsysdeviceclose
	#define EXT_cifx_xsysdeviceclose
	#define GET_cifx_xsysdeviceclose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xsysdeviceclose(p0) 
	#define CHK_cifx_xsysdeviceclose  FALSE
	#define EXP_cifx_xsysdeviceclose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xsysdeviceclose
	#define EXT_cifx_xsysdeviceclose
	#define GET_cifx_xsysdeviceclose(fl)  CAL_CMGETAPI( "cifx_xsysdeviceclose" ) 
	#define CAL_cifx_xsysdeviceclose  cifx_xsysdeviceclose
	#define CHK_cifx_xsysdeviceclose  TRUE
	#define EXP_cifx_xsysdeviceclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceclose", (RTS_UINTPTR)cifx_xsysdeviceclose, 1, RTSITF_GET_SIGNATURE(0, 0x8F559F75), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xsysdeviceclose
	#define EXT_cifx_xsysdeviceclose
	#define GET_cifx_xsysdeviceclose(fl)  CAL_CMGETAPI( "cifx_xsysdeviceclose" ) 
	#define CAL_cifx_xsysdeviceclose  cifx_xsysdeviceclose
	#define CHK_cifx_xsysdeviceclose  TRUE
	#define EXP_cifx_xsysdeviceclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceclose", (RTS_UINTPTR)cifx_xsysdeviceclose, 1, RTSITF_GET_SIGNATURE(0, 0x8F559F75), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xsysdeviceclose
	#define EXT_CmpHilscherCIFXcifx_xsysdeviceclose
	#define GET_CmpHilscherCIFXcifx_xsysdeviceclose  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xsysdeviceclose  cifx_xsysdeviceclose
	#define CHK_CmpHilscherCIFXcifx_xsysdeviceclose  TRUE
	#define EXP_CmpHilscherCIFXcifx_xsysdeviceclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceclose", (RTS_UINTPTR)cifx_xsysdeviceclose, 1, RTSITF_GET_SIGNATURE(0, 0x8F559F75), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xsysdeviceclose
	#define EXT_cifx_xsysdeviceclose
	#define GET_cifx_xsysdeviceclose(fl)  CAL_CMGETAPI( "cifx_xsysdeviceclose" ) 
	#define CAL_cifx_xsysdeviceclose  cifx_xsysdeviceclose
	#define CHK_cifx_xsysdeviceclose  TRUE
	#define EXP_cifx_xsysdeviceclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceclose", (RTS_UINTPTR)cifx_xsysdeviceclose, 1, RTSITF_GET_SIGNATURE(0, 0x8F559F75), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xsysdeviceclose  PFCIFX_XSYSDEVICECLOSE_IEC pfcifx_xsysdeviceclose;
	#define EXT_cifx_xsysdeviceclose  extern PFCIFX_XSYSDEVICECLOSE_IEC pfcifx_xsysdeviceclose;
	#define GET_cifx_xsysdeviceclose(fl)  s_pfCMGetAPI2( "cifx_xsysdeviceclose", (RTS_VOID_FCTPTR *)&pfcifx_xsysdeviceclose, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x8F559F75), 0x03050800)
	#define CAL_cifx_xsysdeviceclose  pfcifx_xsysdeviceclose
	#define CHK_cifx_xsysdeviceclose  (pfcifx_xsysdeviceclose != NULL)
	#define EXP_cifx_xsysdeviceclose   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceclose", (RTS_UINTPTR)cifx_xsysdeviceclose, 1, RTSITF_GET_SIGNATURE(0, 0x8F559F75), 0x03050800) 
#endif


/**
 * <description>cifx_xsysdevicedownload</description>
 */
typedef struct tagcifx_xsysdevicedownload_struct
{
	RTS_IEC_HANDLE hSysdevice;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiMode;				/* VAR_INPUT */	
	RTS_IEC_BYTE *szFileName;			/* VAR_INPUT */	
	RTS_IEC_BYTE *pbyFileData;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiFileSize;			/* VAR_INPUT */	
	RTS_IEC_BYTE *pCallbackUserData;	/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xSysdeviceDownload;	/* VAR_OUTPUT */	
} cifx_xsysdevicedownload_struct;

void CDECL CDECL_EXT cifx_xsysdevicedownload(cifx_xsysdevicedownload_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XSYSDEVICEDOWNLOAD_IEC) (cifx_xsysdevicedownload_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XSYSDEVICEDOWNLOAD_NOTIMPLEMENTED)
	#define USE_cifx_xsysdevicedownload
	#define EXT_cifx_xsysdevicedownload
	#define GET_cifx_xsysdevicedownload(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xsysdevicedownload(p0) 
	#define CHK_cifx_xsysdevicedownload  FALSE
	#define EXP_cifx_xsysdevicedownload  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xsysdevicedownload
	#define EXT_cifx_xsysdevicedownload
	#define GET_cifx_xsysdevicedownload(fl)  CAL_CMGETAPI( "cifx_xsysdevicedownload" ) 
	#define CAL_cifx_xsysdevicedownload  cifx_xsysdevicedownload
	#define CHK_cifx_xsysdevicedownload  TRUE
	#define EXP_cifx_xsysdevicedownload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicedownload", (RTS_UINTPTR)cifx_xsysdevicedownload, 1, RTSITF_GET_SIGNATURE(0, 0x291833D8), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xsysdevicedownload
	#define EXT_cifx_xsysdevicedownload
	#define GET_cifx_xsysdevicedownload(fl)  CAL_CMGETAPI( "cifx_xsysdevicedownload" ) 
	#define CAL_cifx_xsysdevicedownload  cifx_xsysdevicedownload
	#define CHK_cifx_xsysdevicedownload  TRUE
	#define EXP_cifx_xsysdevicedownload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicedownload", (RTS_UINTPTR)cifx_xsysdevicedownload, 1, RTSITF_GET_SIGNATURE(0, 0x291833D8), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xsysdevicedownload
	#define EXT_CmpHilscherCIFXcifx_xsysdevicedownload
	#define GET_CmpHilscherCIFXcifx_xsysdevicedownload  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xsysdevicedownload  cifx_xsysdevicedownload
	#define CHK_CmpHilscherCIFXcifx_xsysdevicedownload  TRUE
	#define EXP_CmpHilscherCIFXcifx_xsysdevicedownload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicedownload", (RTS_UINTPTR)cifx_xsysdevicedownload, 1, RTSITF_GET_SIGNATURE(0, 0x291833D8), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xsysdevicedownload
	#define EXT_cifx_xsysdevicedownload
	#define GET_cifx_xsysdevicedownload(fl)  CAL_CMGETAPI( "cifx_xsysdevicedownload" ) 
	#define CAL_cifx_xsysdevicedownload  cifx_xsysdevicedownload
	#define CHK_cifx_xsysdevicedownload  TRUE
	#define EXP_cifx_xsysdevicedownload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicedownload", (RTS_UINTPTR)cifx_xsysdevicedownload, 1, RTSITF_GET_SIGNATURE(0, 0x291833D8), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xsysdevicedownload  PFCIFX_XSYSDEVICEDOWNLOAD_IEC pfcifx_xsysdevicedownload;
	#define EXT_cifx_xsysdevicedownload  extern PFCIFX_XSYSDEVICEDOWNLOAD_IEC pfcifx_xsysdevicedownload;
	#define GET_cifx_xsysdevicedownload(fl)  s_pfCMGetAPI2( "cifx_xsysdevicedownload", (RTS_VOID_FCTPTR *)&pfcifx_xsysdevicedownload, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x291833D8), 0x03050800)
	#define CAL_cifx_xsysdevicedownload  pfcifx_xsysdevicedownload
	#define CHK_cifx_xsysdevicedownload  (pfcifx_xsysdevicedownload != NULL)
	#define EXP_cifx_xsysdevicedownload   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicedownload", (RTS_UINTPTR)cifx_xsysdevicedownload, 1, RTSITF_GET_SIGNATURE(0, 0x291833D8), 0x03050800) 
#endif


/**
 * <description>cifx_xsysdevicefindfirstfile</description>
 */
typedef struct tagcifx_xsysdevicefindfirstfile_struct
{
	RTS_IEC_HANDLE hSysdevice;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiChannel;			/* VAR_INPUT */	
	CIFX_DIRECTORY_ENTRY *ptDirectoryInfo;	/* VAR_INPUT */	
	RTS_IEC_BYTE *pCallbackUserData;	/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xSysdeviceFindFirstFile;	/* VAR_OUTPUT */	
} cifx_xsysdevicefindfirstfile_struct;

void CDECL CDECL_EXT cifx_xsysdevicefindfirstfile(cifx_xsysdevicefindfirstfile_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XSYSDEVICEFINDFIRSTFILE_IEC) (cifx_xsysdevicefindfirstfile_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XSYSDEVICEFINDFIRSTFILE_NOTIMPLEMENTED)
	#define USE_cifx_xsysdevicefindfirstfile
	#define EXT_cifx_xsysdevicefindfirstfile
	#define GET_cifx_xsysdevicefindfirstfile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xsysdevicefindfirstfile(p0) 
	#define CHK_cifx_xsysdevicefindfirstfile  FALSE
	#define EXP_cifx_xsysdevicefindfirstfile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xsysdevicefindfirstfile
	#define EXT_cifx_xsysdevicefindfirstfile
	#define GET_cifx_xsysdevicefindfirstfile(fl)  CAL_CMGETAPI( "cifx_xsysdevicefindfirstfile" ) 
	#define CAL_cifx_xsysdevicefindfirstfile  cifx_xsysdevicefindfirstfile
	#define CHK_cifx_xsysdevicefindfirstfile  TRUE
	#define EXP_cifx_xsysdevicefindfirstfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicefindfirstfile", (RTS_UINTPTR)cifx_xsysdevicefindfirstfile, 1, RTSITF_GET_SIGNATURE(0, 0x603E3231), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xsysdevicefindfirstfile
	#define EXT_cifx_xsysdevicefindfirstfile
	#define GET_cifx_xsysdevicefindfirstfile(fl)  CAL_CMGETAPI( "cifx_xsysdevicefindfirstfile" ) 
	#define CAL_cifx_xsysdevicefindfirstfile  cifx_xsysdevicefindfirstfile
	#define CHK_cifx_xsysdevicefindfirstfile  TRUE
	#define EXP_cifx_xsysdevicefindfirstfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicefindfirstfile", (RTS_UINTPTR)cifx_xsysdevicefindfirstfile, 1, RTSITF_GET_SIGNATURE(0, 0x603E3231), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xsysdevicefindfirstfile
	#define EXT_CmpHilscherCIFXcifx_xsysdevicefindfirstfile
	#define GET_CmpHilscherCIFXcifx_xsysdevicefindfirstfile  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xsysdevicefindfirstfile  cifx_xsysdevicefindfirstfile
	#define CHK_CmpHilscherCIFXcifx_xsysdevicefindfirstfile  TRUE
	#define EXP_CmpHilscherCIFXcifx_xsysdevicefindfirstfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicefindfirstfile", (RTS_UINTPTR)cifx_xsysdevicefindfirstfile, 1, RTSITF_GET_SIGNATURE(0, 0x603E3231), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xsysdevicefindfirstfile
	#define EXT_cifx_xsysdevicefindfirstfile
	#define GET_cifx_xsysdevicefindfirstfile(fl)  CAL_CMGETAPI( "cifx_xsysdevicefindfirstfile" ) 
	#define CAL_cifx_xsysdevicefindfirstfile  cifx_xsysdevicefindfirstfile
	#define CHK_cifx_xsysdevicefindfirstfile  TRUE
	#define EXP_cifx_xsysdevicefindfirstfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicefindfirstfile", (RTS_UINTPTR)cifx_xsysdevicefindfirstfile, 1, RTSITF_GET_SIGNATURE(0, 0x603E3231), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xsysdevicefindfirstfile  PFCIFX_XSYSDEVICEFINDFIRSTFILE_IEC pfcifx_xsysdevicefindfirstfile;
	#define EXT_cifx_xsysdevicefindfirstfile  extern PFCIFX_XSYSDEVICEFINDFIRSTFILE_IEC pfcifx_xsysdevicefindfirstfile;
	#define GET_cifx_xsysdevicefindfirstfile(fl)  s_pfCMGetAPI2( "cifx_xsysdevicefindfirstfile", (RTS_VOID_FCTPTR *)&pfcifx_xsysdevicefindfirstfile, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x603E3231), 0x03050800)
	#define CAL_cifx_xsysdevicefindfirstfile  pfcifx_xsysdevicefindfirstfile
	#define CHK_cifx_xsysdevicefindfirstfile  (pfcifx_xsysdevicefindfirstfile != NULL)
	#define EXP_cifx_xsysdevicefindfirstfile   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicefindfirstfile", (RTS_UINTPTR)cifx_xsysdevicefindfirstfile, 1, RTSITF_GET_SIGNATURE(0, 0x603E3231), 0x03050800) 
#endif


/**
 * <description>cifx_xsysdevicefindnextfile</description>
 */
typedef struct tagcifx_xsysdevicefindnextfile_struct
{
	RTS_IEC_HANDLE hSysdevice;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiChannel;			/* VAR_INPUT */	
	CIFX_DIRECTORY_ENTRY *ptDirectoryInfo;	/* VAR_INPUT */	
	RTS_IEC_BYTE *pCallbackUserData;	/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xSysdeviceFindNextFile;	/* VAR_OUTPUT */	
} cifx_xsysdevicefindnextfile_struct;

void CDECL CDECL_EXT cifx_xsysdevicefindnextfile(cifx_xsysdevicefindnextfile_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XSYSDEVICEFINDNEXTFILE_IEC) (cifx_xsysdevicefindnextfile_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XSYSDEVICEFINDNEXTFILE_NOTIMPLEMENTED)
	#define USE_cifx_xsysdevicefindnextfile
	#define EXT_cifx_xsysdevicefindnextfile
	#define GET_cifx_xsysdevicefindnextfile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xsysdevicefindnextfile(p0) 
	#define CHK_cifx_xsysdevicefindnextfile  FALSE
	#define EXP_cifx_xsysdevicefindnextfile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xsysdevicefindnextfile
	#define EXT_cifx_xsysdevicefindnextfile
	#define GET_cifx_xsysdevicefindnextfile(fl)  CAL_CMGETAPI( "cifx_xsysdevicefindnextfile" ) 
	#define CAL_cifx_xsysdevicefindnextfile  cifx_xsysdevicefindnextfile
	#define CHK_cifx_xsysdevicefindnextfile  TRUE
	#define EXP_cifx_xsysdevicefindnextfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicefindnextfile", (RTS_UINTPTR)cifx_xsysdevicefindnextfile, 1, RTSITF_GET_SIGNATURE(0, 0xA726E94F), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xsysdevicefindnextfile
	#define EXT_cifx_xsysdevicefindnextfile
	#define GET_cifx_xsysdevicefindnextfile(fl)  CAL_CMGETAPI( "cifx_xsysdevicefindnextfile" ) 
	#define CAL_cifx_xsysdevicefindnextfile  cifx_xsysdevicefindnextfile
	#define CHK_cifx_xsysdevicefindnextfile  TRUE
	#define EXP_cifx_xsysdevicefindnextfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicefindnextfile", (RTS_UINTPTR)cifx_xsysdevicefindnextfile, 1, RTSITF_GET_SIGNATURE(0, 0xA726E94F), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xsysdevicefindnextfile
	#define EXT_CmpHilscherCIFXcifx_xsysdevicefindnextfile
	#define GET_CmpHilscherCIFXcifx_xsysdevicefindnextfile  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xsysdevicefindnextfile  cifx_xsysdevicefindnextfile
	#define CHK_CmpHilscherCIFXcifx_xsysdevicefindnextfile  TRUE
	#define EXP_CmpHilscherCIFXcifx_xsysdevicefindnextfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicefindnextfile", (RTS_UINTPTR)cifx_xsysdevicefindnextfile, 1, RTSITF_GET_SIGNATURE(0, 0xA726E94F), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xsysdevicefindnextfile
	#define EXT_cifx_xsysdevicefindnextfile
	#define GET_cifx_xsysdevicefindnextfile(fl)  CAL_CMGETAPI( "cifx_xsysdevicefindnextfile" ) 
	#define CAL_cifx_xsysdevicefindnextfile  cifx_xsysdevicefindnextfile
	#define CHK_cifx_xsysdevicefindnextfile  TRUE
	#define EXP_cifx_xsysdevicefindnextfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicefindnextfile", (RTS_UINTPTR)cifx_xsysdevicefindnextfile, 1, RTSITF_GET_SIGNATURE(0, 0xA726E94F), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xsysdevicefindnextfile  PFCIFX_XSYSDEVICEFINDNEXTFILE_IEC pfcifx_xsysdevicefindnextfile;
	#define EXT_cifx_xsysdevicefindnextfile  extern PFCIFX_XSYSDEVICEFINDNEXTFILE_IEC pfcifx_xsysdevicefindnextfile;
	#define GET_cifx_xsysdevicefindnextfile(fl)  s_pfCMGetAPI2( "cifx_xsysdevicefindnextfile", (RTS_VOID_FCTPTR *)&pfcifx_xsysdevicefindnextfile, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xA726E94F), 0x03050800)
	#define CAL_cifx_xsysdevicefindnextfile  pfcifx_xsysdevicefindnextfile
	#define CHK_cifx_xsysdevicefindnextfile  (pfcifx_xsysdevicefindnextfile != NULL)
	#define EXP_cifx_xsysdevicefindnextfile   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicefindnextfile", (RTS_UINTPTR)cifx_xsysdevicefindnextfile, 1, RTSITF_GET_SIGNATURE(0, 0xA726E94F), 0x03050800) 
#endif


/**
 * <description>cifx_xsysdevicegetmbxstate</description>
 */
typedef struct tagcifx_xsysdevicegetmbxstate_struct
{
	RTS_IEC_HANDLE hSysdevice;			/* VAR_INPUT */	
	RTS_IEC_UDINT *pudiRecvPktCount;	/* VAR_INPUT */	
	RTS_IEC_UDINT *pudiSendPktCount;	/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xSysdeviceGetMBXState;	/* VAR_OUTPUT */	
} cifx_xsysdevicegetmbxstate_struct;

void CDECL CDECL_EXT cifx_xsysdevicegetmbxstate(cifx_xsysdevicegetmbxstate_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XSYSDEVICEGETMBXSTATE_IEC) (cifx_xsysdevicegetmbxstate_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XSYSDEVICEGETMBXSTATE_NOTIMPLEMENTED)
	#define USE_cifx_xsysdevicegetmbxstate
	#define EXT_cifx_xsysdevicegetmbxstate
	#define GET_cifx_xsysdevicegetmbxstate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xsysdevicegetmbxstate(p0) 
	#define CHK_cifx_xsysdevicegetmbxstate  FALSE
	#define EXP_cifx_xsysdevicegetmbxstate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xsysdevicegetmbxstate
	#define EXT_cifx_xsysdevicegetmbxstate
	#define GET_cifx_xsysdevicegetmbxstate(fl)  CAL_CMGETAPI( "cifx_xsysdevicegetmbxstate" ) 
	#define CAL_cifx_xsysdevicegetmbxstate  cifx_xsysdevicegetmbxstate
	#define CHK_cifx_xsysdevicegetmbxstate  TRUE
	#define EXP_cifx_xsysdevicegetmbxstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicegetmbxstate", (RTS_UINTPTR)cifx_xsysdevicegetmbxstate, 1, RTSITF_GET_SIGNATURE(0, 0x10E10C41), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xsysdevicegetmbxstate
	#define EXT_cifx_xsysdevicegetmbxstate
	#define GET_cifx_xsysdevicegetmbxstate(fl)  CAL_CMGETAPI( "cifx_xsysdevicegetmbxstate" ) 
	#define CAL_cifx_xsysdevicegetmbxstate  cifx_xsysdevicegetmbxstate
	#define CHK_cifx_xsysdevicegetmbxstate  TRUE
	#define EXP_cifx_xsysdevicegetmbxstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicegetmbxstate", (RTS_UINTPTR)cifx_xsysdevicegetmbxstate, 1, RTSITF_GET_SIGNATURE(0, 0x10E10C41), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xsysdevicegetmbxstate
	#define EXT_CmpHilscherCIFXcifx_xsysdevicegetmbxstate
	#define GET_CmpHilscherCIFXcifx_xsysdevicegetmbxstate  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xsysdevicegetmbxstate  cifx_xsysdevicegetmbxstate
	#define CHK_CmpHilscherCIFXcifx_xsysdevicegetmbxstate  TRUE
	#define EXP_CmpHilscherCIFXcifx_xsysdevicegetmbxstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicegetmbxstate", (RTS_UINTPTR)cifx_xsysdevicegetmbxstate, 1, RTSITF_GET_SIGNATURE(0, 0x10E10C41), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xsysdevicegetmbxstate
	#define EXT_cifx_xsysdevicegetmbxstate
	#define GET_cifx_xsysdevicegetmbxstate(fl)  CAL_CMGETAPI( "cifx_xsysdevicegetmbxstate" ) 
	#define CAL_cifx_xsysdevicegetmbxstate  cifx_xsysdevicegetmbxstate
	#define CHK_cifx_xsysdevicegetmbxstate  TRUE
	#define EXP_cifx_xsysdevicegetmbxstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicegetmbxstate", (RTS_UINTPTR)cifx_xsysdevicegetmbxstate, 1, RTSITF_GET_SIGNATURE(0, 0x10E10C41), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xsysdevicegetmbxstate  PFCIFX_XSYSDEVICEGETMBXSTATE_IEC pfcifx_xsysdevicegetmbxstate;
	#define EXT_cifx_xsysdevicegetmbxstate  extern PFCIFX_XSYSDEVICEGETMBXSTATE_IEC pfcifx_xsysdevicegetmbxstate;
	#define GET_cifx_xsysdevicegetmbxstate(fl)  s_pfCMGetAPI2( "cifx_xsysdevicegetmbxstate", (RTS_VOID_FCTPTR *)&pfcifx_xsysdevicegetmbxstate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x10E10C41), 0x03050800)
	#define CAL_cifx_xsysdevicegetmbxstate  pfcifx_xsysdevicegetmbxstate
	#define CHK_cifx_xsysdevicegetmbxstate  (pfcifx_xsysdevicegetmbxstate != NULL)
	#define EXP_cifx_xsysdevicegetmbxstate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicegetmbxstate", (RTS_UINTPTR)cifx_xsysdevicegetmbxstate, 1, RTSITF_GET_SIGNATURE(0, 0x10E10C41), 0x03050800) 
#endif


/**
 * <description>cifx_xsysdevicegetpacket</description>
 */
typedef struct tagcifx_xsysdevicegetpacket_struct
{
	RTS_IEC_HANDLE hSysdevice;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiSize;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pRecvPacket;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiTimeout;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xSysdeviceGetPacket;	/* VAR_OUTPUT */	
} cifx_xsysdevicegetpacket_struct;

void CDECL CDECL_EXT cifx_xsysdevicegetpacket(cifx_xsysdevicegetpacket_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XSYSDEVICEGETPACKET_IEC) (cifx_xsysdevicegetpacket_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XSYSDEVICEGETPACKET_NOTIMPLEMENTED)
	#define USE_cifx_xsysdevicegetpacket
	#define EXT_cifx_xsysdevicegetpacket
	#define GET_cifx_xsysdevicegetpacket(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xsysdevicegetpacket(p0) 
	#define CHK_cifx_xsysdevicegetpacket  FALSE
	#define EXP_cifx_xsysdevicegetpacket  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xsysdevicegetpacket
	#define EXT_cifx_xsysdevicegetpacket
	#define GET_cifx_xsysdevicegetpacket(fl)  CAL_CMGETAPI( "cifx_xsysdevicegetpacket" ) 
	#define CAL_cifx_xsysdevicegetpacket  cifx_xsysdevicegetpacket
	#define CHK_cifx_xsysdevicegetpacket  TRUE
	#define EXP_cifx_xsysdevicegetpacket  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicegetpacket", (RTS_UINTPTR)cifx_xsysdevicegetpacket, 1, RTSITF_GET_SIGNATURE(0, 0xD58D738D), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xsysdevicegetpacket
	#define EXT_cifx_xsysdevicegetpacket
	#define GET_cifx_xsysdevicegetpacket(fl)  CAL_CMGETAPI( "cifx_xsysdevicegetpacket" ) 
	#define CAL_cifx_xsysdevicegetpacket  cifx_xsysdevicegetpacket
	#define CHK_cifx_xsysdevicegetpacket  TRUE
	#define EXP_cifx_xsysdevicegetpacket  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicegetpacket", (RTS_UINTPTR)cifx_xsysdevicegetpacket, 1, RTSITF_GET_SIGNATURE(0, 0xD58D738D), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xsysdevicegetpacket
	#define EXT_CmpHilscherCIFXcifx_xsysdevicegetpacket
	#define GET_CmpHilscherCIFXcifx_xsysdevicegetpacket  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xsysdevicegetpacket  cifx_xsysdevicegetpacket
	#define CHK_CmpHilscherCIFXcifx_xsysdevicegetpacket  TRUE
	#define EXP_CmpHilscherCIFXcifx_xsysdevicegetpacket  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicegetpacket", (RTS_UINTPTR)cifx_xsysdevicegetpacket, 1, RTSITF_GET_SIGNATURE(0, 0xD58D738D), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xsysdevicegetpacket
	#define EXT_cifx_xsysdevicegetpacket
	#define GET_cifx_xsysdevicegetpacket(fl)  CAL_CMGETAPI( "cifx_xsysdevicegetpacket" ) 
	#define CAL_cifx_xsysdevicegetpacket  cifx_xsysdevicegetpacket
	#define CHK_cifx_xsysdevicegetpacket  TRUE
	#define EXP_cifx_xsysdevicegetpacket  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicegetpacket", (RTS_UINTPTR)cifx_xsysdevicegetpacket, 1, RTSITF_GET_SIGNATURE(0, 0xD58D738D), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xsysdevicegetpacket  PFCIFX_XSYSDEVICEGETPACKET_IEC pfcifx_xsysdevicegetpacket;
	#define EXT_cifx_xsysdevicegetpacket  extern PFCIFX_XSYSDEVICEGETPACKET_IEC pfcifx_xsysdevicegetpacket;
	#define GET_cifx_xsysdevicegetpacket(fl)  s_pfCMGetAPI2( "cifx_xsysdevicegetpacket", (RTS_VOID_FCTPTR *)&pfcifx_xsysdevicegetpacket, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xD58D738D), 0x03050800)
	#define CAL_cifx_xsysdevicegetpacket  pfcifx_xsysdevicegetpacket
	#define CHK_cifx_xsysdevicegetpacket  (pfcifx_xsysdevicegetpacket != NULL)
	#define EXP_cifx_xsysdevicegetpacket   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicegetpacket", (RTS_UINTPTR)cifx_xsysdevicegetpacket, 1, RTSITF_GET_SIGNATURE(0, 0xD58D738D), 0x03050800) 
#endif


/**
 * <description>cifx_xsysdeviceinfo</description>
 */
typedef struct tagcifx_xsysdeviceinfo_struct
{
	RTS_IEC_HANDLE hSysdevice;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiCmd;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiSize;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pInfo;				/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xSysdeviceInfo;	/* VAR_OUTPUT */	
} cifx_xsysdeviceinfo_struct;

void CDECL CDECL_EXT cifx_xsysdeviceinfo(cifx_xsysdeviceinfo_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XSYSDEVICEINFO_IEC) (cifx_xsysdeviceinfo_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XSYSDEVICEINFO_NOTIMPLEMENTED)
	#define USE_cifx_xsysdeviceinfo
	#define EXT_cifx_xsysdeviceinfo
	#define GET_cifx_xsysdeviceinfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xsysdeviceinfo(p0) 
	#define CHK_cifx_xsysdeviceinfo  FALSE
	#define EXP_cifx_xsysdeviceinfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xsysdeviceinfo
	#define EXT_cifx_xsysdeviceinfo
	#define GET_cifx_xsysdeviceinfo(fl)  CAL_CMGETAPI( "cifx_xsysdeviceinfo" ) 
	#define CAL_cifx_xsysdeviceinfo  cifx_xsysdeviceinfo
	#define CHK_cifx_xsysdeviceinfo  TRUE
	#define EXP_cifx_xsysdeviceinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceinfo", (RTS_UINTPTR)cifx_xsysdeviceinfo, 1, RTSITF_GET_SIGNATURE(0, 0x16E358BD), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xsysdeviceinfo
	#define EXT_cifx_xsysdeviceinfo
	#define GET_cifx_xsysdeviceinfo(fl)  CAL_CMGETAPI( "cifx_xsysdeviceinfo" ) 
	#define CAL_cifx_xsysdeviceinfo  cifx_xsysdeviceinfo
	#define CHK_cifx_xsysdeviceinfo  TRUE
	#define EXP_cifx_xsysdeviceinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceinfo", (RTS_UINTPTR)cifx_xsysdeviceinfo, 1, RTSITF_GET_SIGNATURE(0, 0x16E358BD), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xsysdeviceinfo
	#define EXT_CmpHilscherCIFXcifx_xsysdeviceinfo
	#define GET_CmpHilscherCIFXcifx_xsysdeviceinfo  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xsysdeviceinfo  cifx_xsysdeviceinfo
	#define CHK_CmpHilscherCIFXcifx_xsysdeviceinfo  TRUE
	#define EXP_CmpHilscherCIFXcifx_xsysdeviceinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceinfo", (RTS_UINTPTR)cifx_xsysdeviceinfo, 1, RTSITF_GET_SIGNATURE(0, 0x16E358BD), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xsysdeviceinfo
	#define EXT_cifx_xsysdeviceinfo
	#define GET_cifx_xsysdeviceinfo(fl)  CAL_CMGETAPI( "cifx_xsysdeviceinfo" ) 
	#define CAL_cifx_xsysdeviceinfo  cifx_xsysdeviceinfo
	#define CHK_cifx_xsysdeviceinfo  TRUE
	#define EXP_cifx_xsysdeviceinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceinfo", (RTS_UINTPTR)cifx_xsysdeviceinfo, 1, RTSITF_GET_SIGNATURE(0, 0x16E358BD), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xsysdeviceinfo  PFCIFX_XSYSDEVICEINFO_IEC pfcifx_xsysdeviceinfo;
	#define EXT_cifx_xsysdeviceinfo  extern PFCIFX_XSYSDEVICEINFO_IEC pfcifx_xsysdeviceinfo;
	#define GET_cifx_xsysdeviceinfo(fl)  s_pfCMGetAPI2( "cifx_xsysdeviceinfo", (RTS_VOID_FCTPTR *)&pfcifx_xsysdeviceinfo, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x16E358BD), 0x03050800)
	#define CAL_cifx_xsysdeviceinfo  pfcifx_xsysdeviceinfo
	#define CHK_cifx_xsysdeviceinfo  (pfcifx_xsysdeviceinfo != NULL)
	#define EXP_cifx_xsysdeviceinfo   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceinfo", (RTS_UINTPTR)cifx_xsysdeviceinfo, 1, RTSITF_GET_SIGNATURE(0, 0x16E358BD), 0x03050800) 
#endif


/**
 * <description>cifx_xsysdeviceopen</description>
 */
typedef struct tagcifx_xsysdeviceopen_struct
{
	RTS_IEC_HANDLE hDriver;				/* VAR_INPUT */	
	RTS_IEC_BYTE *szBoard;				/* VAR_INPUT */	
	RTS_IEC_HANDLE *phSysdevice;		/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xSysdeviceOpen;	/* VAR_OUTPUT */	
} cifx_xsysdeviceopen_struct;

void CDECL CDECL_EXT cifx_xsysdeviceopen(cifx_xsysdeviceopen_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XSYSDEVICEOPEN_IEC) (cifx_xsysdeviceopen_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XSYSDEVICEOPEN_NOTIMPLEMENTED)
	#define USE_cifx_xsysdeviceopen
	#define EXT_cifx_xsysdeviceopen
	#define GET_cifx_xsysdeviceopen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xsysdeviceopen(p0) 
	#define CHK_cifx_xsysdeviceopen  FALSE
	#define EXP_cifx_xsysdeviceopen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xsysdeviceopen
	#define EXT_cifx_xsysdeviceopen
	#define GET_cifx_xsysdeviceopen(fl)  CAL_CMGETAPI( "cifx_xsysdeviceopen" ) 
	#define CAL_cifx_xsysdeviceopen  cifx_xsysdeviceopen
	#define CHK_cifx_xsysdeviceopen  TRUE
	#define EXP_cifx_xsysdeviceopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceopen", (RTS_UINTPTR)cifx_xsysdeviceopen, 1, RTSITF_GET_SIGNATURE(0, 0x19F5F105), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xsysdeviceopen
	#define EXT_cifx_xsysdeviceopen
	#define GET_cifx_xsysdeviceopen(fl)  CAL_CMGETAPI( "cifx_xsysdeviceopen" ) 
	#define CAL_cifx_xsysdeviceopen  cifx_xsysdeviceopen
	#define CHK_cifx_xsysdeviceopen  TRUE
	#define EXP_cifx_xsysdeviceopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceopen", (RTS_UINTPTR)cifx_xsysdeviceopen, 1, RTSITF_GET_SIGNATURE(0, 0x19F5F105), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xsysdeviceopen
	#define EXT_CmpHilscherCIFXcifx_xsysdeviceopen
	#define GET_CmpHilscherCIFXcifx_xsysdeviceopen  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xsysdeviceopen  cifx_xsysdeviceopen
	#define CHK_CmpHilscherCIFXcifx_xsysdeviceopen  TRUE
	#define EXP_CmpHilscherCIFXcifx_xsysdeviceopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceopen", (RTS_UINTPTR)cifx_xsysdeviceopen, 1, RTSITF_GET_SIGNATURE(0, 0x19F5F105), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xsysdeviceopen
	#define EXT_cifx_xsysdeviceopen
	#define GET_cifx_xsysdeviceopen(fl)  CAL_CMGETAPI( "cifx_xsysdeviceopen" ) 
	#define CAL_cifx_xsysdeviceopen  cifx_xsysdeviceopen
	#define CHK_cifx_xsysdeviceopen  TRUE
	#define EXP_cifx_xsysdeviceopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceopen", (RTS_UINTPTR)cifx_xsysdeviceopen, 1, RTSITF_GET_SIGNATURE(0, 0x19F5F105), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xsysdeviceopen  PFCIFX_XSYSDEVICEOPEN_IEC pfcifx_xsysdeviceopen;
	#define EXT_cifx_xsysdeviceopen  extern PFCIFX_XSYSDEVICEOPEN_IEC pfcifx_xsysdeviceopen;
	#define GET_cifx_xsysdeviceopen(fl)  s_pfCMGetAPI2( "cifx_xsysdeviceopen", (RTS_VOID_FCTPTR *)&pfcifx_xsysdeviceopen, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x19F5F105), 0x03050800)
	#define CAL_cifx_xsysdeviceopen  pfcifx_xsysdeviceopen
	#define CHK_cifx_xsysdeviceopen  (pfcifx_xsysdeviceopen != NULL)
	#define EXP_cifx_xsysdeviceopen   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceopen", (RTS_UINTPTR)cifx_xsysdeviceopen, 1, RTSITF_GET_SIGNATURE(0, 0x19F5F105), 0x03050800) 
#endif


/**
 * <description>cifx_xsysdeviceputpacket</description>
 */
typedef struct tagcifx_xsysdeviceputpacket_struct
{
	RTS_IEC_HANDLE hSysdevice;			/* VAR_INPUT */	
	RTS_IEC_BYTE *pSendPacket;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiTimeout;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xSysdevicePutPacket;	/* VAR_OUTPUT */	
} cifx_xsysdeviceputpacket_struct;

void CDECL CDECL_EXT cifx_xsysdeviceputpacket(cifx_xsysdeviceputpacket_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XSYSDEVICEPUTPACKET_IEC) (cifx_xsysdeviceputpacket_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XSYSDEVICEPUTPACKET_NOTIMPLEMENTED)
	#define USE_cifx_xsysdeviceputpacket
	#define EXT_cifx_xsysdeviceputpacket
	#define GET_cifx_xsysdeviceputpacket(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xsysdeviceputpacket(p0) 
	#define CHK_cifx_xsysdeviceputpacket  FALSE
	#define EXP_cifx_xsysdeviceputpacket  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xsysdeviceputpacket
	#define EXT_cifx_xsysdeviceputpacket
	#define GET_cifx_xsysdeviceputpacket(fl)  CAL_CMGETAPI( "cifx_xsysdeviceputpacket" ) 
	#define CAL_cifx_xsysdeviceputpacket  cifx_xsysdeviceputpacket
	#define CHK_cifx_xsysdeviceputpacket  TRUE
	#define EXP_cifx_xsysdeviceputpacket  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceputpacket", (RTS_UINTPTR)cifx_xsysdeviceputpacket, 1, RTSITF_GET_SIGNATURE(0, 0xC1D8C9F0), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xsysdeviceputpacket
	#define EXT_cifx_xsysdeviceputpacket
	#define GET_cifx_xsysdeviceputpacket(fl)  CAL_CMGETAPI( "cifx_xsysdeviceputpacket" ) 
	#define CAL_cifx_xsysdeviceputpacket  cifx_xsysdeviceputpacket
	#define CHK_cifx_xsysdeviceputpacket  TRUE
	#define EXP_cifx_xsysdeviceputpacket  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceputpacket", (RTS_UINTPTR)cifx_xsysdeviceputpacket, 1, RTSITF_GET_SIGNATURE(0, 0xC1D8C9F0), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xsysdeviceputpacket
	#define EXT_CmpHilscherCIFXcifx_xsysdeviceputpacket
	#define GET_CmpHilscherCIFXcifx_xsysdeviceputpacket  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xsysdeviceputpacket  cifx_xsysdeviceputpacket
	#define CHK_CmpHilscherCIFXcifx_xsysdeviceputpacket  TRUE
	#define EXP_CmpHilscherCIFXcifx_xsysdeviceputpacket  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceputpacket", (RTS_UINTPTR)cifx_xsysdeviceputpacket, 1, RTSITF_GET_SIGNATURE(0, 0xC1D8C9F0), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xsysdeviceputpacket
	#define EXT_cifx_xsysdeviceputpacket
	#define GET_cifx_xsysdeviceputpacket(fl)  CAL_CMGETAPI( "cifx_xsysdeviceputpacket" ) 
	#define CAL_cifx_xsysdeviceputpacket  cifx_xsysdeviceputpacket
	#define CHK_cifx_xsysdeviceputpacket  TRUE
	#define EXP_cifx_xsysdeviceputpacket  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceputpacket", (RTS_UINTPTR)cifx_xsysdeviceputpacket, 1, RTSITF_GET_SIGNATURE(0, 0xC1D8C9F0), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xsysdeviceputpacket  PFCIFX_XSYSDEVICEPUTPACKET_IEC pfcifx_xsysdeviceputpacket;
	#define EXT_cifx_xsysdeviceputpacket  extern PFCIFX_XSYSDEVICEPUTPACKET_IEC pfcifx_xsysdeviceputpacket;
	#define GET_cifx_xsysdeviceputpacket(fl)  s_pfCMGetAPI2( "cifx_xsysdeviceputpacket", (RTS_VOID_FCTPTR *)&pfcifx_xsysdeviceputpacket, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xC1D8C9F0), 0x03050800)
	#define CAL_cifx_xsysdeviceputpacket  pfcifx_xsysdeviceputpacket
	#define CHK_cifx_xsysdeviceputpacket  (pfcifx_xsysdeviceputpacket != NULL)
	#define EXP_cifx_xsysdeviceputpacket   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceputpacket", (RTS_UINTPTR)cifx_xsysdeviceputpacket, 1, RTSITF_GET_SIGNATURE(0, 0xC1D8C9F0), 0x03050800) 
#endif


/**
 * <description>cifx_xsysdevicereset</description>
 */
typedef struct tagcifx_xsysdevicereset_struct
{
	RTS_IEC_HANDLE hSysdevice;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiTimeout;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xSysdeviceReset;	/* VAR_OUTPUT */	
} cifx_xsysdevicereset_struct;

void CDECL CDECL_EXT cifx_xsysdevicereset(cifx_xsysdevicereset_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XSYSDEVICERESET_IEC) (cifx_xsysdevicereset_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XSYSDEVICERESET_NOTIMPLEMENTED)
	#define USE_cifx_xsysdevicereset
	#define EXT_cifx_xsysdevicereset
	#define GET_cifx_xsysdevicereset(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xsysdevicereset(p0) 
	#define CHK_cifx_xsysdevicereset  FALSE
	#define EXP_cifx_xsysdevicereset  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xsysdevicereset
	#define EXT_cifx_xsysdevicereset
	#define GET_cifx_xsysdevicereset(fl)  CAL_CMGETAPI( "cifx_xsysdevicereset" ) 
	#define CAL_cifx_xsysdevicereset  cifx_xsysdevicereset
	#define CHK_cifx_xsysdevicereset  TRUE
	#define EXP_cifx_xsysdevicereset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicereset", (RTS_UINTPTR)cifx_xsysdevicereset, 1, RTSITF_GET_SIGNATURE(0, 0xD4E3E20F), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xsysdevicereset
	#define EXT_cifx_xsysdevicereset
	#define GET_cifx_xsysdevicereset(fl)  CAL_CMGETAPI( "cifx_xsysdevicereset" ) 
	#define CAL_cifx_xsysdevicereset  cifx_xsysdevicereset
	#define CHK_cifx_xsysdevicereset  TRUE
	#define EXP_cifx_xsysdevicereset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicereset", (RTS_UINTPTR)cifx_xsysdevicereset, 1, RTSITF_GET_SIGNATURE(0, 0xD4E3E20F), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xsysdevicereset
	#define EXT_CmpHilscherCIFXcifx_xsysdevicereset
	#define GET_CmpHilscherCIFXcifx_xsysdevicereset  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xsysdevicereset  cifx_xsysdevicereset
	#define CHK_CmpHilscherCIFXcifx_xsysdevicereset  TRUE
	#define EXP_CmpHilscherCIFXcifx_xsysdevicereset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicereset", (RTS_UINTPTR)cifx_xsysdevicereset, 1, RTSITF_GET_SIGNATURE(0, 0xD4E3E20F), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xsysdevicereset
	#define EXT_cifx_xsysdevicereset
	#define GET_cifx_xsysdevicereset(fl)  CAL_CMGETAPI( "cifx_xsysdevicereset" ) 
	#define CAL_cifx_xsysdevicereset  cifx_xsysdevicereset
	#define CHK_cifx_xsysdevicereset  TRUE
	#define EXP_cifx_xsysdevicereset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicereset", (RTS_UINTPTR)cifx_xsysdevicereset, 1, RTSITF_GET_SIGNATURE(0, 0xD4E3E20F), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xsysdevicereset  PFCIFX_XSYSDEVICERESET_IEC pfcifx_xsysdevicereset;
	#define EXT_cifx_xsysdevicereset  extern PFCIFX_XSYSDEVICERESET_IEC pfcifx_xsysdevicereset;
	#define GET_cifx_xsysdevicereset(fl)  s_pfCMGetAPI2( "cifx_xsysdevicereset", (RTS_VOID_FCTPTR *)&pfcifx_xsysdevicereset, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xD4E3E20F), 0x03050800)
	#define CAL_cifx_xsysdevicereset  pfcifx_xsysdevicereset
	#define CHK_cifx_xsysdevicereset  (pfcifx_xsysdevicereset != NULL)
	#define EXP_cifx_xsysdevicereset   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdevicereset", (RTS_UINTPTR)cifx_xsysdevicereset, 1, RTSITF_GET_SIGNATURE(0, 0xD4E3E20F), 0x03050800) 
#endif


/**
 * <description>cifx_xsysdeviceupload</description>
 */
typedef struct tagcifx_xsysdeviceupload_struct
{
	RTS_IEC_HANDLE hSysdevice;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiMode;				/* VAR_INPUT */	
	RTS_IEC_BYTE *szFileName;			/* VAR_INPUT */	
	RTS_IEC_BYTE *pbyFileData;			/* VAR_INPUT */	
	RTS_IEC_UDINT *pudiFileSize;		/* VAR_INPUT */	
	RTS_IEC_BYTE *pCallbackUserData;	/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xSysdeviceUpload;	/* VAR_OUTPUT */	
} cifx_xsysdeviceupload_struct;

void CDECL CDECL_EXT cifx_xsysdeviceupload(cifx_xsysdeviceupload_struct *p);
typedef void (CDECL CDECL_EXT* PFCIFX_XSYSDEVICEUPLOAD_IEC) (cifx_xsysdeviceupload_struct *p);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_XSYSDEVICEUPLOAD_NOTIMPLEMENTED)
	#define USE_cifx_xsysdeviceupload
	#define EXT_cifx_xsysdeviceupload
	#define GET_cifx_xsysdeviceupload(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cifx_xsysdeviceupload(p0) 
	#define CHK_cifx_xsysdeviceupload  FALSE
	#define EXP_cifx_xsysdeviceupload  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cifx_xsysdeviceupload
	#define EXT_cifx_xsysdeviceupload
	#define GET_cifx_xsysdeviceupload(fl)  CAL_CMGETAPI( "cifx_xsysdeviceupload" ) 
	#define CAL_cifx_xsysdeviceupload  cifx_xsysdeviceupload
	#define CHK_cifx_xsysdeviceupload  TRUE
	#define EXP_cifx_xsysdeviceupload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceupload", (RTS_UINTPTR)cifx_xsysdeviceupload, 1, RTSITF_GET_SIGNATURE(0, 0x4677B806), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_cifx_xsysdeviceupload
	#define EXT_cifx_xsysdeviceupload
	#define GET_cifx_xsysdeviceupload(fl)  CAL_CMGETAPI( "cifx_xsysdeviceupload" ) 
	#define CAL_cifx_xsysdeviceupload  cifx_xsysdeviceupload
	#define CHK_cifx_xsysdeviceupload  TRUE
	#define EXP_cifx_xsysdeviceupload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceupload", (RTS_UINTPTR)cifx_xsysdeviceupload, 1, RTSITF_GET_SIGNATURE(0, 0x4677B806), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXcifx_xsysdeviceupload
	#define EXT_CmpHilscherCIFXcifx_xsysdeviceupload
	#define GET_CmpHilscherCIFXcifx_xsysdeviceupload  ERR_OK
	#define CAL_CmpHilscherCIFXcifx_xsysdeviceupload  cifx_xsysdeviceupload
	#define CHK_CmpHilscherCIFXcifx_xsysdeviceupload  TRUE
	#define EXP_CmpHilscherCIFXcifx_xsysdeviceupload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceupload", (RTS_UINTPTR)cifx_xsysdeviceupload, 1, RTSITF_GET_SIGNATURE(0, 0x4677B806), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_cifx_xsysdeviceupload
	#define EXT_cifx_xsysdeviceupload
	#define GET_cifx_xsysdeviceupload(fl)  CAL_CMGETAPI( "cifx_xsysdeviceupload" ) 
	#define CAL_cifx_xsysdeviceupload  cifx_xsysdeviceupload
	#define CHK_cifx_xsysdeviceupload  TRUE
	#define EXP_cifx_xsysdeviceupload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceupload", (RTS_UINTPTR)cifx_xsysdeviceupload, 1, RTSITF_GET_SIGNATURE(0, 0x4677B806), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_cifx_xsysdeviceupload  PFCIFX_XSYSDEVICEUPLOAD_IEC pfcifx_xsysdeviceupload;
	#define EXT_cifx_xsysdeviceupload  extern PFCIFX_XSYSDEVICEUPLOAD_IEC pfcifx_xsysdeviceupload;
	#define GET_cifx_xsysdeviceupload(fl)  s_pfCMGetAPI2( "cifx_xsysdeviceupload", (RTS_VOID_FCTPTR *)&pfcifx_xsysdeviceupload, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x4677B806), 0x03050800)
	#define CAL_cifx_xsysdeviceupload  pfcifx_xsysdeviceupload
	#define CHK_cifx_xsysdeviceupload  (pfcifx_xsysdeviceupload != NULL)
	#define EXP_cifx_xsysdeviceupload   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cifx_xsysdeviceupload", (RTS_UINTPTR)cifx_xsysdeviceupload, 1, RTSITF_GET_SIGNATURE(0, 0x4677B806), 0x03050800) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

RTS_RESULT CDECL Cifx_DriverOpen(	RTS_HANDLE* phDriver);
typedef RTS_RESULT (CDECL * PFCIFX_DRIVEROPEN) (	RTS_HANDLE* phDriver);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_DRIVEROPEN_NOTIMPLEMENTED)
	#define USE_Cifx_DriverOpen
	#define EXT_Cifx_DriverOpen
	#define GET_Cifx_DriverOpen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_DriverOpen(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_DriverOpen  FALSE
	#define EXP_Cifx_DriverOpen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_DriverOpen
	#define EXT_Cifx_DriverOpen
	#define GET_Cifx_DriverOpen(fl)  CAL_CMGETAPI( "Cifx_DriverOpen" ) 
	#define CAL_Cifx_DriverOpen  Cifx_DriverOpen
	#define CHK_Cifx_DriverOpen  TRUE
	#define EXP_Cifx_DriverOpen  CAL_CMEXPAPI( "Cifx_DriverOpen" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_DriverOpen
	#define EXT_Cifx_DriverOpen
	#define GET_Cifx_DriverOpen(fl)  CAL_CMGETAPI( "Cifx_DriverOpen" ) 
	#define CAL_Cifx_DriverOpen  Cifx_DriverOpen
	#define CHK_Cifx_DriverOpen  TRUE
	#define EXP_Cifx_DriverOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_DriverOpen", (RTS_UINTPTR)Cifx_DriverOpen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_DriverOpen
	#define EXT_CmpHilscherCIFXCifx_DriverOpen
	#define GET_CmpHilscherCIFXCifx_DriverOpen  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_DriverOpen pICmpHilscherCIFX->ICifx_DriverOpen
	#define CHK_CmpHilscherCIFXCifx_DriverOpen (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_DriverOpen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_DriverOpen
	#define EXT_Cifx_DriverOpen
	#define GET_Cifx_DriverOpen(fl)  CAL_CMGETAPI( "Cifx_DriverOpen" ) 
	#define CAL_Cifx_DriverOpen pICmpHilscherCIFX->ICifx_DriverOpen
	#define CHK_Cifx_DriverOpen (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_DriverOpen  CAL_CMEXPAPI( "Cifx_DriverOpen" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_DriverOpen  PFCIFX_DRIVEROPEN pfCifx_DriverOpen;
	#define EXT_Cifx_DriverOpen  extern PFCIFX_DRIVEROPEN pfCifx_DriverOpen;
	#define GET_Cifx_DriverOpen(fl)  s_pfCMGetAPI2( "Cifx_DriverOpen", (RTS_VOID_FCTPTR *)&pfCifx_DriverOpen, (fl), 0, 0)
	#define CAL_Cifx_DriverOpen  pfCifx_DriverOpen
	#define CHK_Cifx_DriverOpen  (pfCifx_DriverOpen != NULL)
	#define EXP_Cifx_DriverOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_DriverOpen", (RTS_UINTPTR)Cifx_DriverOpen, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_DriverClose(RTS_HANDLE hDriver);
typedef RTS_RESULT (CDECL * PFCIFX_DRIVERCLOSE) (RTS_HANDLE hDriver);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_DRIVERCLOSE_NOTIMPLEMENTED)
	#define USE_Cifx_DriverClose
	#define EXT_Cifx_DriverClose
	#define GET_Cifx_DriverClose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_DriverClose(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_DriverClose  FALSE
	#define EXP_Cifx_DriverClose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_DriverClose
	#define EXT_Cifx_DriverClose
	#define GET_Cifx_DriverClose(fl)  CAL_CMGETAPI( "Cifx_DriverClose" ) 
	#define CAL_Cifx_DriverClose  Cifx_DriverClose
	#define CHK_Cifx_DriverClose  TRUE
	#define EXP_Cifx_DriverClose  CAL_CMEXPAPI( "Cifx_DriverClose" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_DriverClose
	#define EXT_Cifx_DriverClose
	#define GET_Cifx_DriverClose(fl)  CAL_CMGETAPI( "Cifx_DriverClose" ) 
	#define CAL_Cifx_DriverClose  Cifx_DriverClose
	#define CHK_Cifx_DriverClose  TRUE
	#define EXP_Cifx_DriverClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_DriverClose", (RTS_UINTPTR)Cifx_DriverClose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_DriverClose
	#define EXT_CmpHilscherCIFXCifx_DriverClose
	#define GET_CmpHilscherCIFXCifx_DriverClose  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_DriverClose pICmpHilscherCIFX->ICifx_DriverClose
	#define CHK_CmpHilscherCIFXCifx_DriverClose (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_DriverClose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_DriverClose
	#define EXT_Cifx_DriverClose
	#define GET_Cifx_DriverClose(fl)  CAL_CMGETAPI( "Cifx_DriverClose" ) 
	#define CAL_Cifx_DriverClose pICmpHilscherCIFX->ICifx_DriverClose
	#define CHK_Cifx_DriverClose (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_DriverClose  CAL_CMEXPAPI( "Cifx_DriverClose" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_DriverClose  PFCIFX_DRIVERCLOSE pfCifx_DriverClose;
	#define EXT_Cifx_DriverClose  extern PFCIFX_DRIVERCLOSE pfCifx_DriverClose;
	#define GET_Cifx_DriverClose(fl)  s_pfCMGetAPI2( "Cifx_DriverClose", (RTS_VOID_FCTPTR *)&pfCifx_DriverClose, (fl), 0, 0)
	#define CAL_Cifx_DriverClose  pfCifx_DriverClose
	#define CHK_Cifx_DriverClose  (pfCifx_DriverClose != NULL)
	#define EXP_Cifx_DriverClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_DriverClose", (RTS_UINTPTR)Cifx_DriverClose, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_DriverGetInformation( RTS_HANDLE	hDriver, RTS_UI32	ulSize, void* pDriverInfo);
typedef RTS_RESULT (CDECL * PFCIFX_DRIVERGETINFORMATION) ( RTS_HANDLE	hDriver, RTS_UI32	ulSize, void* pDriverInfo);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_DRIVERGETINFORMATION_NOTIMPLEMENTED)
	#define USE_Cifx_DriverGetInformation
	#define EXT_Cifx_DriverGetInformation
	#define GET_Cifx_DriverGetInformation(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_DriverGetInformation(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_DriverGetInformation  FALSE
	#define EXP_Cifx_DriverGetInformation  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_DriverGetInformation
	#define EXT_Cifx_DriverGetInformation
	#define GET_Cifx_DriverGetInformation(fl)  CAL_CMGETAPI( "Cifx_DriverGetInformation" ) 
	#define CAL_Cifx_DriverGetInformation  Cifx_DriverGetInformation
	#define CHK_Cifx_DriverGetInformation  TRUE
	#define EXP_Cifx_DriverGetInformation  CAL_CMEXPAPI( "Cifx_DriverGetInformation" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_DriverGetInformation
	#define EXT_Cifx_DriverGetInformation
	#define GET_Cifx_DriverGetInformation(fl)  CAL_CMGETAPI( "Cifx_DriverGetInformation" ) 
	#define CAL_Cifx_DriverGetInformation  Cifx_DriverGetInformation
	#define CHK_Cifx_DriverGetInformation  TRUE
	#define EXP_Cifx_DriverGetInformation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_DriverGetInformation", (RTS_UINTPTR)Cifx_DriverGetInformation, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_DriverGetInformation
	#define EXT_CmpHilscherCIFXCifx_DriverGetInformation
	#define GET_CmpHilscherCIFXCifx_DriverGetInformation  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_DriverGetInformation pICmpHilscherCIFX->ICifx_DriverGetInformation
	#define CHK_CmpHilscherCIFXCifx_DriverGetInformation (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_DriverGetInformation  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_DriverGetInformation
	#define EXT_Cifx_DriverGetInformation
	#define GET_Cifx_DriverGetInformation(fl)  CAL_CMGETAPI( "Cifx_DriverGetInformation" ) 
	#define CAL_Cifx_DriverGetInformation pICmpHilscherCIFX->ICifx_DriverGetInformation
	#define CHK_Cifx_DriverGetInformation (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_DriverGetInformation  CAL_CMEXPAPI( "Cifx_DriverGetInformation" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_DriverGetInformation  PFCIFX_DRIVERGETINFORMATION pfCifx_DriverGetInformation;
	#define EXT_Cifx_DriverGetInformation  extern PFCIFX_DRIVERGETINFORMATION pfCifx_DriverGetInformation;
	#define GET_Cifx_DriverGetInformation(fl)  s_pfCMGetAPI2( "Cifx_DriverGetInformation", (RTS_VOID_FCTPTR *)&pfCifx_DriverGetInformation, (fl), 0, 0)
	#define CAL_Cifx_DriverGetInformation  pfCifx_DriverGetInformation
	#define CHK_Cifx_DriverGetInformation  (pfCifx_DriverGetInformation != NULL)
	#define EXP_Cifx_DriverGetInformation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_DriverGetInformation", (RTS_UINTPTR)Cifx_DriverGetInformation, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_DriverGetErrorDescription(RTS_UI32 ulError, char* szBuffer, RTS_UI32 ulBufferLen);
typedef RTS_RESULT (CDECL * PFCIFX_DRIVERGETERRORDESCRIPTION) (RTS_UI32 ulError, char* szBuffer, RTS_UI32 ulBufferLen);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_DRIVERGETERRORDESCRIPTION_NOTIMPLEMENTED)
	#define USE_Cifx_DriverGetErrorDescription
	#define EXT_Cifx_DriverGetErrorDescription
	#define GET_Cifx_DriverGetErrorDescription(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_DriverGetErrorDescription(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_DriverGetErrorDescription  FALSE
	#define EXP_Cifx_DriverGetErrorDescription  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_DriverGetErrorDescription
	#define EXT_Cifx_DriverGetErrorDescription
	#define GET_Cifx_DriverGetErrorDescription(fl)  CAL_CMGETAPI( "Cifx_DriverGetErrorDescription" ) 
	#define CAL_Cifx_DriverGetErrorDescription  Cifx_DriverGetErrorDescription
	#define CHK_Cifx_DriverGetErrorDescription  TRUE
	#define EXP_Cifx_DriverGetErrorDescription  CAL_CMEXPAPI( "Cifx_DriverGetErrorDescription" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_DriverGetErrorDescription
	#define EXT_Cifx_DriverGetErrorDescription
	#define GET_Cifx_DriverGetErrorDescription(fl)  CAL_CMGETAPI( "Cifx_DriverGetErrorDescription" ) 
	#define CAL_Cifx_DriverGetErrorDescription  Cifx_DriverGetErrorDescription
	#define CHK_Cifx_DriverGetErrorDescription  TRUE
	#define EXP_Cifx_DriverGetErrorDescription  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_DriverGetErrorDescription", (RTS_UINTPTR)Cifx_DriverGetErrorDescription, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_DriverGetErrorDescription
	#define EXT_CmpHilscherCIFXCifx_DriverGetErrorDescription
	#define GET_CmpHilscherCIFXCifx_DriverGetErrorDescription  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_DriverGetErrorDescription pICmpHilscherCIFX->ICifx_DriverGetErrorDescription
	#define CHK_CmpHilscherCIFXCifx_DriverGetErrorDescription (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_DriverGetErrorDescription  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_DriverGetErrorDescription
	#define EXT_Cifx_DriverGetErrorDescription
	#define GET_Cifx_DriverGetErrorDescription(fl)  CAL_CMGETAPI( "Cifx_DriverGetErrorDescription" ) 
	#define CAL_Cifx_DriverGetErrorDescription pICmpHilscherCIFX->ICifx_DriverGetErrorDescription
	#define CHK_Cifx_DriverGetErrorDescription (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_DriverGetErrorDescription  CAL_CMEXPAPI( "Cifx_DriverGetErrorDescription" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_DriverGetErrorDescription  PFCIFX_DRIVERGETERRORDESCRIPTION pfCifx_DriverGetErrorDescription;
	#define EXT_Cifx_DriverGetErrorDescription  extern PFCIFX_DRIVERGETERRORDESCRIPTION pfCifx_DriverGetErrorDescription;
	#define GET_Cifx_DriverGetErrorDescription(fl)  s_pfCMGetAPI2( "Cifx_DriverGetErrorDescription", (RTS_VOID_FCTPTR *)&pfCifx_DriverGetErrorDescription, (fl), 0, 0)
	#define CAL_Cifx_DriverGetErrorDescription  pfCifx_DriverGetErrorDescription
	#define CHK_Cifx_DriverGetErrorDescription  (pfCifx_DriverGetErrorDescription != NULL)
	#define EXP_Cifx_DriverGetErrorDescription  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_DriverGetErrorDescription", (RTS_UINTPTR)Cifx_DriverGetErrorDescription, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_DriverEnumBoards(RTS_HANDLE	hDriver,	RTS_UI32	ulBoard,	RTS_UI32	ulSize,	void*			pvBoardInfo);
typedef RTS_RESULT (CDECL * PFCIFX_DRIVERENUMBOARDS) (RTS_HANDLE	hDriver,	RTS_UI32	ulBoard,	RTS_UI32	ulSize,	void*			pvBoardInfo);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_DRIVERENUMBOARDS_NOTIMPLEMENTED)
	#define USE_Cifx_DriverEnumBoards
	#define EXT_Cifx_DriverEnumBoards
	#define GET_Cifx_DriverEnumBoards(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_DriverEnumBoards(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_DriverEnumBoards  FALSE
	#define EXP_Cifx_DriverEnumBoards  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_DriverEnumBoards
	#define EXT_Cifx_DriverEnumBoards
	#define GET_Cifx_DriverEnumBoards(fl)  CAL_CMGETAPI( "Cifx_DriverEnumBoards" ) 
	#define CAL_Cifx_DriverEnumBoards  Cifx_DriverEnumBoards
	#define CHK_Cifx_DriverEnumBoards  TRUE
	#define EXP_Cifx_DriverEnumBoards  CAL_CMEXPAPI( "Cifx_DriverEnumBoards" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_DriverEnumBoards
	#define EXT_Cifx_DriverEnumBoards
	#define GET_Cifx_DriverEnumBoards(fl)  CAL_CMGETAPI( "Cifx_DriverEnumBoards" ) 
	#define CAL_Cifx_DriverEnumBoards  Cifx_DriverEnumBoards
	#define CHK_Cifx_DriverEnumBoards  TRUE
	#define EXP_Cifx_DriverEnumBoards  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_DriverEnumBoards", (RTS_UINTPTR)Cifx_DriverEnumBoards, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_DriverEnumBoards
	#define EXT_CmpHilscherCIFXCifx_DriverEnumBoards
	#define GET_CmpHilscherCIFXCifx_DriverEnumBoards  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_DriverEnumBoards pICmpHilscherCIFX->ICifx_DriverEnumBoards
	#define CHK_CmpHilscherCIFXCifx_DriverEnumBoards (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_DriverEnumBoards  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_DriverEnumBoards
	#define EXT_Cifx_DriverEnumBoards
	#define GET_Cifx_DriverEnumBoards(fl)  CAL_CMGETAPI( "Cifx_DriverEnumBoards" ) 
	#define CAL_Cifx_DriverEnumBoards pICmpHilscherCIFX->ICifx_DriverEnumBoards
	#define CHK_Cifx_DriverEnumBoards (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_DriverEnumBoards  CAL_CMEXPAPI( "Cifx_DriverEnumBoards" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_DriverEnumBoards  PFCIFX_DRIVERENUMBOARDS pfCifx_DriverEnumBoards;
	#define EXT_Cifx_DriverEnumBoards  extern PFCIFX_DRIVERENUMBOARDS pfCifx_DriverEnumBoards;
	#define GET_Cifx_DriverEnumBoards(fl)  s_pfCMGetAPI2( "Cifx_DriverEnumBoards", (RTS_VOID_FCTPTR *)&pfCifx_DriverEnumBoards, (fl), 0, 0)
	#define CAL_Cifx_DriverEnumBoards  pfCifx_DriverEnumBoards
	#define CHK_Cifx_DriverEnumBoards  (pfCifx_DriverEnumBoards != NULL)
	#define EXP_Cifx_DriverEnumBoards  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_DriverEnumBoards", (RTS_UINTPTR)Cifx_DriverEnumBoards, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_DriverEnumChannels(	RTS_HANDLE	hDriver, RTS_UI32	ulBoard,	RTS_UI32	ulChannel,	RTS_UI32	ulSize,	void*			pvChannelInfo);
typedef RTS_RESULT (CDECL * PFCIFX_DRIVERENUMCHANNELS) (	RTS_HANDLE	hDriver, RTS_UI32	ulBoard,	RTS_UI32	ulChannel,	RTS_UI32	ulSize,	void*			pvChannelInfo);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_DRIVERENUMCHANNELS_NOTIMPLEMENTED)
	#define USE_Cifx_DriverEnumChannels
	#define EXT_Cifx_DriverEnumChannels
	#define GET_Cifx_DriverEnumChannels(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_DriverEnumChannels(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_DriverEnumChannels  FALSE
	#define EXP_Cifx_DriverEnumChannels  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_DriverEnumChannels
	#define EXT_Cifx_DriverEnumChannels
	#define GET_Cifx_DriverEnumChannels(fl)  CAL_CMGETAPI( "Cifx_DriverEnumChannels" ) 
	#define CAL_Cifx_DriverEnumChannels  Cifx_DriverEnumChannels
	#define CHK_Cifx_DriverEnumChannels  TRUE
	#define EXP_Cifx_DriverEnumChannels  CAL_CMEXPAPI( "Cifx_DriverEnumChannels" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_DriverEnumChannels
	#define EXT_Cifx_DriverEnumChannels
	#define GET_Cifx_DriverEnumChannels(fl)  CAL_CMGETAPI( "Cifx_DriverEnumChannels" ) 
	#define CAL_Cifx_DriverEnumChannels  Cifx_DriverEnumChannels
	#define CHK_Cifx_DriverEnumChannels  TRUE
	#define EXP_Cifx_DriverEnumChannels  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_DriverEnumChannels", (RTS_UINTPTR)Cifx_DriverEnumChannels, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_DriverEnumChannels
	#define EXT_CmpHilscherCIFXCifx_DriverEnumChannels
	#define GET_CmpHilscherCIFXCifx_DriverEnumChannels  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_DriverEnumChannels pICmpHilscherCIFX->ICifx_DriverEnumChannels
	#define CHK_CmpHilscherCIFXCifx_DriverEnumChannels (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_DriverEnumChannels  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_DriverEnumChannels
	#define EXT_Cifx_DriverEnumChannels
	#define GET_Cifx_DriverEnumChannels(fl)  CAL_CMGETAPI( "Cifx_DriverEnumChannels" ) 
	#define CAL_Cifx_DriverEnumChannels pICmpHilscherCIFX->ICifx_DriverEnumChannels
	#define CHK_Cifx_DriverEnumChannels (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_DriverEnumChannels  CAL_CMEXPAPI( "Cifx_DriverEnumChannels" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_DriverEnumChannels  PFCIFX_DRIVERENUMCHANNELS pfCifx_DriverEnumChannels;
	#define EXT_Cifx_DriverEnumChannels  extern PFCIFX_DRIVERENUMCHANNELS pfCifx_DriverEnumChannels;
	#define GET_Cifx_DriverEnumChannels(fl)  s_pfCMGetAPI2( "Cifx_DriverEnumChannels", (RTS_VOID_FCTPTR *)&pfCifx_DriverEnumChannels, (fl), 0, 0)
	#define CAL_Cifx_DriverEnumChannels  pfCifx_DriverEnumChannels
	#define CHK_Cifx_DriverEnumChannels  (pfCifx_DriverEnumChannels != NULL)
	#define EXP_Cifx_DriverEnumChannels  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_DriverEnumChannels", (RTS_UINTPTR)Cifx_DriverEnumChannels, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_DriverMemoryPointer(RTS_HANDLE	hDriver, RTS_UI32	ulBoard,	RTS_UI32	ulCmd,	void* pvMemoryInfo);
typedef RTS_RESULT (CDECL * PFCIFX_DRIVERMEMORYPOINTER) (RTS_HANDLE	hDriver, RTS_UI32	ulBoard,	RTS_UI32	ulCmd,	void* pvMemoryInfo);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_DRIVERMEMORYPOINTER_NOTIMPLEMENTED)
	#define USE_Cifx_DriverMemoryPointer
	#define EXT_Cifx_DriverMemoryPointer
	#define GET_Cifx_DriverMemoryPointer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_DriverMemoryPointer(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_DriverMemoryPointer  FALSE
	#define EXP_Cifx_DriverMemoryPointer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_DriverMemoryPointer
	#define EXT_Cifx_DriverMemoryPointer
	#define GET_Cifx_DriverMemoryPointer(fl)  CAL_CMGETAPI( "Cifx_DriverMemoryPointer" ) 
	#define CAL_Cifx_DriverMemoryPointer  Cifx_DriverMemoryPointer
	#define CHK_Cifx_DriverMemoryPointer  TRUE
	#define EXP_Cifx_DriverMemoryPointer  CAL_CMEXPAPI( "Cifx_DriverMemoryPointer" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_DriverMemoryPointer
	#define EXT_Cifx_DriverMemoryPointer
	#define GET_Cifx_DriverMemoryPointer(fl)  CAL_CMGETAPI( "Cifx_DriverMemoryPointer" ) 
	#define CAL_Cifx_DriverMemoryPointer  Cifx_DriverMemoryPointer
	#define CHK_Cifx_DriverMemoryPointer  TRUE
	#define EXP_Cifx_DriverMemoryPointer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_DriverMemoryPointer", (RTS_UINTPTR)Cifx_DriverMemoryPointer, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_DriverMemoryPointer
	#define EXT_CmpHilscherCIFXCifx_DriverMemoryPointer
	#define GET_CmpHilscherCIFXCifx_DriverMemoryPointer  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_DriverMemoryPointer pICmpHilscherCIFX->ICifx_DriverMemoryPointer
	#define CHK_CmpHilscherCIFXCifx_DriverMemoryPointer (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_DriverMemoryPointer  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_DriverMemoryPointer
	#define EXT_Cifx_DriverMemoryPointer
	#define GET_Cifx_DriverMemoryPointer(fl)  CAL_CMGETAPI( "Cifx_DriverMemoryPointer" ) 
	#define CAL_Cifx_DriverMemoryPointer pICmpHilscherCIFX->ICifx_DriverMemoryPointer
	#define CHK_Cifx_DriverMemoryPointer (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_DriverMemoryPointer  CAL_CMEXPAPI( "Cifx_DriverMemoryPointer" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_DriverMemoryPointer  PFCIFX_DRIVERMEMORYPOINTER pfCifx_DriverMemoryPointer;
	#define EXT_Cifx_DriverMemoryPointer  extern PFCIFX_DRIVERMEMORYPOINTER pfCifx_DriverMemoryPointer;
	#define GET_Cifx_DriverMemoryPointer(fl)  s_pfCMGetAPI2( "Cifx_DriverMemoryPointer", (RTS_VOID_FCTPTR *)&pfCifx_DriverMemoryPointer, (fl), 0, 0)
	#define CAL_Cifx_DriverMemoryPointer  pfCifx_DriverMemoryPointer
	#define CHK_Cifx_DriverMemoryPointer  (pfCifx_DriverMemoryPointer != NULL)
	#define EXP_Cifx_DriverMemoryPointer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_DriverMemoryPointer", (RTS_UINTPTR)Cifx_DriverMemoryPointer, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_SysDeviceOpen(RTS_HANDLE	hDriver, char*			szBoard,	RTS_HANDLE*	phSysdevice);
typedef RTS_RESULT (CDECL * PFCIFX_SYSDEVICEOPEN) (RTS_HANDLE	hDriver, char*			szBoard,	RTS_HANDLE*	phSysdevice);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_SYSDEVICEOPEN_NOTIMPLEMENTED)
	#define USE_Cifx_SysDeviceOpen
	#define EXT_Cifx_SysDeviceOpen
	#define GET_Cifx_SysDeviceOpen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_SysDeviceOpen(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_SysDeviceOpen  FALSE
	#define EXP_Cifx_SysDeviceOpen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_SysDeviceOpen
	#define EXT_Cifx_SysDeviceOpen
	#define GET_Cifx_SysDeviceOpen(fl)  CAL_CMGETAPI( "Cifx_SysDeviceOpen" ) 
	#define CAL_Cifx_SysDeviceOpen  Cifx_SysDeviceOpen
	#define CHK_Cifx_SysDeviceOpen  TRUE
	#define EXP_Cifx_SysDeviceOpen  CAL_CMEXPAPI( "Cifx_SysDeviceOpen" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_SysDeviceOpen
	#define EXT_Cifx_SysDeviceOpen
	#define GET_Cifx_SysDeviceOpen(fl)  CAL_CMGETAPI( "Cifx_SysDeviceOpen" ) 
	#define CAL_Cifx_SysDeviceOpen  Cifx_SysDeviceOpen
	#define CHK_Cifx_SysDeviceOpen  TRUE
	#define EXP_Cifx_SysDeviceOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_SysDeviceOpen", (RTS_UINTPTR)Cifx_SysDeviceOpen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_SysDeviceOpen
	#define EXT_CmpHilscherCIFXCifx_SysDeviceOpen
	#define GET_CmpHilscherCIFXCifx_SysDeviceOpen  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_SysDeviceOpen pICmpHilscherCIFX->ICifx_SysDeviceOpen
	#define CHK_CmpHilscherCIFXCifx_SysDeviceOpen (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_SysDeviceOpen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_SysDeviceOpen
	#define EXT_Cifx_SysDeviceOpen
	#define GET_Cifx_SysDeviceOpen(fl)  CAL_CMGETAPI( "Cifx_SysDeviceOpen" ) 
	#define CAL_Cifx_SysDeviceOpen pICmpHilscherCIFX->ICifx_SysDeviceOpen
	#define CHK_Cifx_SysDeviceOpen (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_SysDeviceOpen  CAL_CMEXPAPI( "Cifx_SysDeviceOpen" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_SysDeviceOpen  PFCIFX_SYSDEVICEOPEN pfCifx_SysDeviceOpen;
	#define EXT_Cifx_SysDeviceOpen  extern PFCIFX_SYSDEVICEOPEN pfCifx_SysDeviceOpen;
	#define GET_Cifx_SysDeviceOpen(fl)  s_pfCMGetAPI2( "Cifx_SysDeviceOpen", (RTS_VOID_FCTPTR *)&pfCifx_SysDeviceOpen, (fl), 0, 0)
	#define CAL_Cifx_SysDeviceOpen  pfCifx_SysDeviceOpen
	#define CHK_Cifx_SysDeviceOpen  (pfCifx_SysDeviceOpen != NULL)
	#define EXP_Cifx_SysDeviceOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_SysDeviceOpen", (RTS_UINTPTR)Cifx_SysDeviceOpen, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_SysDeviceClose(	RTS_HANDLE	hSysdevice);
typedef RTS_RESULT (CDECL * PFCIFX_SYSDEVICECLOSE) (	RTS_HANDLE	hSysdevice);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_SYSDEVICECLOSE_NOTIMPLEMENTED)
	#define USE_Cifx_SysDeviceClose
	#define EXT_Cifx_SysDeviceClose
	#define GET_Cifx_SysDeviceClose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_SysDeviceClose(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_SysDeviceClose  FALSE
	#define EXP_Cifx_SysDeviceClose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_SysDeviceClose
	#define EXT_Cifx_SysDeviceClose
	#define GET_Cifx_SysDeviceClose(fl)  CAL_CMGETAPI( "Cifx_SysDeviceClose" ) 
	#define CAL_Cifx_SysDeviceClose  Cifx_SysDeviceClose
	#define CHK_Cifx_SysDeviceClose  TRUE
	#define EXP_Cifx_SysDeviceClose  CAL_CMEXPAPI( "Cifx_SysDeviceClose" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_SysDeviceClose
	#define EXT_Cifx_SysDeviceClose
	#define GET_Cifx_SysDeviceClose(fl)  CAL_CMGETAPI( "Cifx_SysDeviceClose" ) 
	#define CAL_Cifx_SysDeviceClose  Cifx_SysDeviceClose
	#define CHK_Cifx_SysDeviceClose  TRUE
	#define EXP_Cifx_SysDeviceClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_SysDeviceClose", (RTS_UINTPTR)Cifx_SysDeviceClose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_SysDeviceClose
	#define EXT_CmpHilscherCIFXCifx_SysDeviceClose
	#define GET_CmpHilscherCIFXCifx_SysDeviceClose  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_SysDeviceClose pICmpHilscherCIFX->ICifx_SysDeviceClose
	#define CHK_CmpHilscherCIFXCifx_SysDeviceClose (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_SysDeviceClose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_SysDeviceClose
	#define EXT_Cifx_SysDeviceClose
	#define GET_Cifx_SysDeviceClose(fl)  CAL_CMGETAPI( "Cifx_SysDeviceClose" ) 
	#define CAL_Cifx_SysDeviceClose pICmpHilscherCIFX->ICifx_SysDeviceClose
	#define CHK_Cifx_SysDeviceClose (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_SysDeviceClose  CAL_CMEXPAPI( "Cifx_SysDeviceClose" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_SysDeviceClose  PFCIFX_SYSDEVICECLOSE pfCifx_SysDeviceClose;
	#define EXT_Cifx_SysDeviceClose  extern PFCIFX_SYSDEVICECLOSE pfCifx_SysDeviceClose;
	#define GET_Cifx_SysDeviceClose(fl)  s_pfCMGetAPI2( "Cifx_SysDeviceClose", (RTS_VOID_FCTPTR *)&pfCifx_SysDeviceClose, (fl), 0, 0)
	#define CAL_Cifx_SysDeviceClose  pfCifx_SysDeviceClose
	#define CHK_Cifx_SysDeviceClose  (pfCifx_SysDeviceClose != NULL)
	#define EXP_Cifx_SysDeviceClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_SysDeviceClose", (RTS_UINTPTR)Cifx_SysDeviceClose, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_SysDeviceReset(	RTS_HANDLE	hSysdevice, RTS_UI32 ulTimeout);
typedef RTS_RESULT (CDECL * PFCIFX_SYSDEVICERESET) (	RTS_HANDLE	hSysdevice, RTS_UI32 ulTimeout);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_SYSDEVICERESET_NOTIMPLEMENTED)
	#define USE_Cifx_SysDeviceReset
	#define EXT_Cifx_SysDeviceReset
	#define GET_Cifx_SysDeviceReset(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_SysDeviceReset(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_SysDeviceReset  FALSE
	#define EXP_Cifx_SysDeviceReset  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_SysDeviceReset
	#define EXT_Cifx_SysDeviceReset
	#define GET_Cifx_SysDeviceReset(fl)  CAL_CMGETAPI( "Cifx_SysDeviceReset" ) 
	#define CAL_Cifx_SysDeviceReset  Cifx_SysDeviceReset
	#define CHK_Cifx_SysDeviceReset  TRUE
	#define EXP_Cifx_SysDeviceReset  CAL_CMEXPAPI( "Cifx_SysDeviceReset" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_SysDeviceReset
	#define EXT_Cifx_SysDeviceReset
	#define GET_Cifx_SysDeviceReset(fl)  CAL_CMGETAPI( "Cifx_SysDeviceReset" ) 
	#define CAL_Cifx_SysDeviceReset  Cifx_SysDeviceReset
	#define CHK_Cifx_SysDeviceReset  TRUE
	#define EXP_Cifx_SysDeviceReset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_SysDeviceReset", (RTS_UINTPTR)Cifx_SysDeviceReset, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_SysDeviceReset
	#define EXT_CmpHilscherCIFXCifx_SysDeviceReset
	#define GET_CmpHilscherCIFXCifx_SysDeviceReset  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_SysDeviceReset pICmpHilscherCIFX->ICifx_SysDeviceReset
	#define CHK_CmpHilscherCIFXCifx_SysDeviceReset (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_SysDeviceReset  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_SysDeviceReset
	#define EXT_Cifx_SysDeviceReset
	#define GET_Cifx_SysDeviceReset(fl)  CAL_CMGETAPI( "Cifx_SysDeviceReset" ) 
	#define CAL_Cifx_SysDeviceReset pICmpHilscherCIFX->ICifx_SysDeviceReset
	#define CHK_Cifx_SysDeviceReset (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_SysDeviceReset  CAL_CMEXPAPI( "Cifx_SysDeviceReset" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_SysDeviceReset  PFCIFX_SYSDEVICERESET pfCifx_SysDeviceReset;
	#define EXT_Cifx_SysDeviceReset  extern PFCIFX_SYSDEVICERESET pfCifx_SysDeviceReset;
	#define GET_Cifx_SysDeviceReset(fl)  s_pfCMGetAPI2( "Cifx_SysDeviceReset", (RTS_VOID_FCTPTR *)&pfCifx_SysDeviceReset, (fl), 0, 0)
	#define CAL_Cifx_SysDeviceReset  pfCifx_SysDeviceReset
	#define CHK_Cifx_SysDeviceReset  (pfCifx_SysDeviceReset != NULL)
	#define EXP_Cifx_SysDeviceReset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_SysDeviceReset", (RTS_UINTPTR)Cifx_SysDeviceReset, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_SysDeviceGetMBXState(RTS_HANDLE	hSysdevice,	RTS_UI32*	pulRecvPktCount, RTS_UI32*	pulSendPktCount);
typedef RTS_RESULT (CDECL * PFCIFX_SYSDEVICEGETMBXSTATE) (RTS_HANDLE	hSysdevice,	RTS_UI32*	pulRecvPktCount, RTS_UI32*	pulSendPktCount);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_SYSDEVICEGETMBXSTATE_NOTIMPLEMENTED)
	#define USE_Cifx_SysDeviceGetMBXState
	#define EXT_Cifx_SysDeviceGetMBXState
	#define GET_Cifx_SysDeviceGetMBXState(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_SysDeviceGetMBXState(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_SysDeviceGetMBXState  FALSE
	#define EXP_Cifx_SysDeviceGetMBXState  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_SysDeviceGetMBXState
	#define EXT_Cifx_SysDeviceGetMBXState
	#define GET_Cifx_SysDeviceGetMBXState(fl)  CAL_CMGETAPI( "Cifx_SysDeviceGetMBXState" ) 
	#define CAL_Cifx_SysDeviceGetMBXState  Cifx_SysDeviceGetMBXState
	#define CHK_Cifx_SysDeviceGetMBXState  TRUE
	#define EXP_Cifx_SysDeviceGetMBXState  CAL_CMEXPAPI( "Cifx_SysDeviceGetMBXState" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_SysDeviceGetMBXState
	#define EXT_Cifx_SysDeviceGetMBXState
	#define GET_Cifx_SysDeviceGetMBXState(fl)  CAL_CMGETAPI( "Cifx_SysDeviceGetMBXState" ) 
	#define CAL_Cifx_SysDeviceGetMBXState  Cifx_SysDeviceGetMBXState
	#define CHK_Cifx_SysDeviceGetMBXState  TRUE
	#define EXP_Cifx_SysDeviceGetMBXState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_SysDeviceGetMBXState", (RTS_UINTPTR)Cifx_SysDeviceGetMBXState, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_SysDeviceGetMBXState
	#define EXT_CmpHilscherCIFXCifx_SysDeviceGetMBXState
	#define GET_CmpHilscherCIFXCifx_SysDeviceGetMBXState  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_SysDeviceGetMBXState pICmpHilscherCIFX->ICifx_SysDeviceGetMBXState
	#define CHK_CmpHilscherCIFXCifx_SysDeviceGetMBXState (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_SysDeviceGetMBXState  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_SysDeviceGetMBXState
	#define EXT_Cifx_SysDeviceGetMBXState
	#define GET_Cifx_SysDeviceGetMBXState(fl)  CAL_CMGETAPI( "Cifx_SysDeviceGetMBXState" ) 
	#define CAL_Cifx_SysDeviceGetMBXState pICmpHilscherCIFX->ICifx_SysDeviceGetMBXState
	#define CHK_Cifx_SysDeviceGetMBXState (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_SysDeviceGetMBXState  CAL_CMEXPAPI( "Cifx_SysDeviceGetMBXState" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_SysDeviceGetMBXState  PFCIFX_SYSDEVICEGETMBXSTATE pfCifx_SysDeviceGetMBXState;
	#define EXT_Cifx_SysDeviceGetMBXState  extern PFCIFX_SYSDEVICEGETMBXSTATE pfCifx_SysDeviceGetMBXState;
	#define GET_Cifx_SysDeviceGetMBXState(fl)  s_pfCMGetAPI2( "Cifx_SysDeviceGetMBXState", (RTS_VOID_FCTPTR *)&pfCifx_SysDeviceGetMBXState, (fl), 0, 0)
	#define CAL_Cifx_SysDeviceGetMBXState  pfCifx_SysDeviceGetMBXState
	#define CHK_Cifx_SysDeviceGetMBXState  (pfCifx_SysDeviceGetMBXState != NULL)
	#define EXP_Cifx_SysDeviceGetMBXState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_SysDeviceGetMBXState", (RTS_UINTPTR)Cifx_SysDeviceGetMBXState, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_SysDevicePutPacket(RTS_HANDLE	hSysdevice,	CIFX_PACKET*	ptSendPkt,	RTS_UI32	ulTimeout);
typedef RTS_RESULT (CDECL * PFCIFX_SYSDEVICEPUTPACKET) (RTS_HANDLE	hSysdevice,	CIFX_PACKET*	ptSendPkt,	RTS_UI32	ulTimeout);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_SYSDEVICEPUTPACKET_NOTIMPLEMENTED)
	#define USE_Cifx_SysDevicePutPacket
	#define EXT_Cifx_SysDevicePutPacket
	#define GET_Cifx_SysDevicePutPacket(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_SysDevicePutPacket(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_SysDevicePutPacket  FALSE
	#define EXP_Cifx_SysDevicePutPacket  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_SysDevicePutPacket
	#define EXT_Cifx_SysDevicePutPacket
	#define GET_Cifx_SysDevicePutPacket(fl)  CAL_CMGETAPI( "Cifx_SysDevicePutPacket" ) 
	#define CAL_Cifx_SysDevicePutPacket  Cifx_SysDevicePutPacket
	#define CHK_Cifx_SysDevicePutPacket  TRUE
	#define EXP_Cifx_SysDevicePutPacket  CAL_CMEXPAPI( "Cifx_SysDevicePutPacket" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_SysDevicePutPacket
	#define EXT_Cifx_SysDevicePutPacket
	#define GET_Cifx_SysDevicePutPacket(fl)  CAL_CMGETAPI( "Cifx_SysDevicePutPacket" ) 
	#define CAL_Cifx_SysDevicePutPacket  Cifx_SysDevicePutPacket
	#define CHK_Cifx_SysDevicePutPacket  TRUE
	#define EXP_Cifx_SysDevicePutPacket  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_SysDevicePutPacket", (RTS_UINTPTR)Cifx_SysDevicePutPacket, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_SysDevicePutPacket
	#define EXT_CmpHilscherCIFXCifx_SysDevicePutPacket
	#define GET_CmpHilscherCIFXCifx_SysDevicePutPacket  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_SysDevicePutPacket pICmpHilscherCIFX->ICifx_SysDevicePutPacket
	#define CHK_CmpHilscherCIFXCifx_SysDevicePutPacket (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_SysDevicePutPacket  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_SysDevicePutPacket
	#define EXT_Cifx_SysDevicePutPacket
	#define GET_Cifx_SysDevicePutPacket(fl)  CAL_CMGETAPI( "Cifx_SysDevicePutPacket" ) 
	#define CAL_Cifx_SysDevicePutPacket pICmpHilscherCIFX->ICifx_SysDevicePutPacket
	#define CHK_Cifx_SysDevicePutPacket (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_SysDevicePutPacket  CAL_CMEXPAPI( "Cifx_SysDevicePutPacket" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_SysDevicePutPacket  PFCIFX_SYSDEVICEPUTPACKET pfCifx_SysDevicePutPacket;
	#define EXT_Cifx_SysDevicePutPacket  extern PFCIFX_SYSDEVICEPUTPACKET pfCifx_SysDevicePutPacket;
	#define GET_Cifx_SysDevicePutPacket(fl)  s_pfCMGetAPI2( "Cifx_SysDevicePutPacket", (RTS_VOID_FCTPTR *)&pfCifx_SysDevicePutPacket, (fl), 0, 0)
	#define CAL_Cifx_SysDevicePutPacket  pfCifx_SysDevicePutPacket
	#define CHK_Cifx_SysDevicePutPacket  (pfCifx_SysDevicePutPacket != NULL)
	#define EXP_Cifx_SysDevicePutPacket  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_SysDevicePutPacket", (RTS_UINTPTR)Cifx_SysDevicePutPacket, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_SysDeviceGetPacket(	RTS_HANDLE	hSysdevice,	RTS_UI32	ulSize,	CIFX_PACKET*	ptRecvPkt, RTS_UI32	ulTimeout);
typedef RTS_RESULT (CDECL * PFCIFX_SYSDEVICEGETPACKET) (	RTS_HANDLE	hSysdevice,	RTS_UI32	ulSize,	CIFX_PACKET*	ptRecvPkt, RTS_UI32	ulTimeout);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_SYSDEVICEGETPACKET_NOTIMPLEMENTED)
	#define USE_Cifx_SysDeviceGetPacket
	#define EXT_Cifx_SysDeviceGetPacket
	#define GET_Cifx_SysDeviceGetPacket(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_SysDeviceGetPacket(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_SysDeviceGetPacket  FALSE
	#define EXP_Cifx_SysDeviceGetPacket  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_SysDeviceGetPacket
	#define EXT_Cifx_SysDeviceGetPacket
	#define GET_Cifx_SysDeviceGetPacket(fl)  CAL_CMGETAPI( "Cifx_SysDeviceGetPacket" ) 
	#define CAL_Cifx_SysDeviceGetPacket  Cifx_SysDeviceGetPacket
	#define CHK_Cifx_SysDeviceGetPacket  TRUE
	#define EXP_Cifx_SysDeviceGetPacket  CAL_CMEXPAPI( "Cifx_SysDeviceGetPacket" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_SysDeviceGetPacket
	#define EXT_Cifx_SysDeviceGetPacket
	#define GET_Cifx_SysDeviceGetPacket(fl)  CAL_CMGETAPI( "Cifx_SysDeviceGetPacket" ) 
	#define CAL_Cifx_SysDeviceGetPacket  Cifx_SysDeviceGetPacket
	#define CHK_Cifx_SysDeviceGetPacket  TRUE
	#define EXP_Cifx_SysDeviceGetPacket  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_SysDeviceGetPacket", (RTS_UINTPTR)Cifx_SysDeviceGetPacket, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_SysDeviceGetPacket
	#define EXT_CmpHilscherCIFXCifx_SysDeviceGetPacket
	#define GET_CmpHilscherCIFXCifx_SysDeviceGetPacket  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_SysDeviceGetPacket pICmpHilscherCIFX->ICifx_SysDeviceGetPacket
	#define CHK_CmpHilscherCIFXCifx_SysDeviceGetPacket (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_SysDeviceGetPacket  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_SysDeviceGetPacket
	#define EXT_Cifx_SysDeviceGetPacket
	#define GET_Cifx_SysDeviceGetPacket(fl)  CAL_CMGETAPI( "Cifx_SysDeviceGetPacket" ) 
	#define CAL_Cifx_SysDeviceGetPacket pICmpHilscherCIFX->ICifx_SysDeviceGetPacket
	#define CHK_Cifx_SysDeviceGetPacket (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_SysDeviceGetPacket  CAL_CMEXPAPI( "Cifx_SysDeviceGetPacket" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_SysDeviceGetPacket  PFCIFX_SYSDEVICEGETPACKET pfCifx_SysDeviceGetPacket;
	#define EXT_Cifx_SysDeviceGetPacket  extern PFCIFX_SYSDEVICEGETPACKET pfCifx_SysDeviceGetPacket;
	#define GET_Cifx_SysDeviceGetPacket(fl)  s_pfCMGetAPI2( "Cifx_SysDeviceGetPacket", (RTS_VOID_FCTPTR *)&pfCifx_SysDeviceGetPacket, (fl), 0, 0)
	#define CAL_Cifx_SysDeviceGetPacket  pfCifx_SysDeviceGetPacket
	#define CHK_Cifx_SysDeviceGetPacket  (pfCifx_SysDeviceGetPacket != NULL)
	#define EXP_Cifx_SysDeviceGetPacket  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_SysDeviceGetPacket", (RTS_UINTPTR)Cifx_SysDeviceGetPacket, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_SysDeviceDownload(	RTS_HANDLE	hSysdevice,	RTS_UI32	ulChannel, RTS_UI32	ulMode,	char* szFileName, RTS_UI8*	pbyFileData, RTS_UI32	ulFileSize,	PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void*	pvUser);
typedef RTS_RESULT (CDECL * PFCIFX_SYSDEVICEDOWNLOAD) (	RTS_HANDLE	hSysdevice,	RTS_UI32	ulChannel, RTS_UI32	ulMode,	char* szFileName, RTS_UI8*	pbyFileData, RTS_UI32	ulFileSize,	PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void*	pvUser);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_SYSDEVICEDOWNLOAD_NOTIMPLEMENTED)
	#define USE_Cifx_SysDeviceDownload
	#define EXT_Cifx_SysDeviceDownload
	#define GET_Cifx_SysDeviceDownload(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_SysDeviceDownload(p0,p1,p2,p3,p4,p5,p6,p7,p8)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_SysDeviceDownload  FALSE
	#define EXP_Cifx_SysDeviceDownload  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_SysDeviceDownload
	#define EXT_Cifx_SysDeviceDownload
	#define GET_Cifx_SysDeviceDownload(fl)  CAL_CMGETAPI( "Cifx_SysDeviceDownload" ) 
	#define CAL_Cifx_SysDeviceDownload  Cifx_SysDeviceDownload
	#define CHK_Cifx_SysDeviceDownload  TRUE
	#define EXP_Cifx_SysDeviceDownload  CAL_CMEXPAPI( "Cifx_SysDeviceDownload" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_SysDeviceDownload
	#define EXT_Cifx_SysDeviceDownload
	#define GET_Cifx_SysDeviceDownload(fl)  CAL_CMGETAPI( "Cifx_SysDeviceDownload" ) 
	#define CAL_Cifx_SysDeviceDownload  Cifx_SysDeviceDownload
	#define CHK_Cifx_SysDeviceDownload  TRUE
	#define EXP_Cifx_SysDeviceDownload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_SysDeviceDownload", (RTS_UINTPTR)Cifx_SysDeviceDownload, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_SysDeviceDownload
	#define EXT_CmpHilscherCIFXCifx_SysDeviceDownload
	#define GET_CmpHilscherCIFXCifx_SysDeviceDownload  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_SysDeviceDownload pICmpHilscherCIFX->ICifx_SysDeviceDownload
	#define CHK_CmpHilscherCIFXCifx_SysDeviceDownload (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_SysDeviceDownload  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_SysDeviceDownload
	#define EXT_Cifx_SysDeviceDownload
	#define GET_Cifx_SysDeviceDownload(fl)  CAL_CMGETAPI( "Cifx_SysDeviceDownload" ) 
	#define CAL_Cifx_SysDeviceDownload pICmpHilscherCIFX->ICifx_SysDeviceDownload
	#define CHK_Cifx_SysDeviceDownload (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_SysDeviceDownload  CAL_CMEXPAPI( "Cifx_SysDeviceDownload" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_SysDeviceDownload  PFCIFX_SYSDEVICEDOWNLOAD pfCifx_SysDeviceDownload;
	#define EXT_Cifx_SysDeviceDownload  extern PFCIFX_SYSDEVICEDOWNLOAD pfCifx_SysDeviceDownload;
	#define GET_Cifx_SysDeviceDownload(fl)  s_pfCMGetAPI2( "Cifx_SysDeviceDownload", (RTS_VOID_FCTPTR *)&pfCifx_SysDeviceDownload, (fl), 0, 0)
	#define CAL_Cifx_SysDeviceDownload  pfCifx_SysDeviceDownload
	#define CHK_Cifx_SysDeviceDownload  (pfCifx_SysDeviceDownload != NULL)
	#define EXP_Cifx_SysDeviceDownload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_SysDeviceDownload", (RTS_UINTPTR)Cifx_SysDeviceDownload, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_SysDeviceInfo(RTS_HANDLE	hSysdevice,	RTS_UI32	ulCmd, RTS_UI32	ulSize,	void*			pvInfo);
typedef RTS_RESULT (CDECL * PFCIFX_SYSDEVICEINFO) (RTS_HANDLE	hSysdevice,	RTS_UI32	ulCmd, RTS_UI32	ulSize,	void*			pvInfo);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_SYSDEVICEINFO_NOTIMPLEMENTED)
	#define USE_Cifx_SysDeviceInfo
	#define EXT_Cifx_SysDeviceInfo
	#define GET_Cifx_SysDeviceInfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_SysDeviceInfo(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_SysDeviceInfo  FALSE
	#define EXP_Cifx_SysDeviceInfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_SysDeviceInfo
	#define EXT_Cifx_SysDeviceInfo
	#define GET_Cifx_SysDeviceInfo(fl)  CAL_CMGETAPI( "Cifx_SysDeviceInfo" ) 
	#define CAL_Cifx_SysDeviceInfo  Cifx_SysDeviceInfo
	#define CHK_Cifx_SysDeviceInfo  TRUE
	#define EXP_Cifx_SysDeviceInfo  CAL_CMEXPAPI( "Cifx_SysDeviceInfo" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_SysDeviceInfo
	#define EXT_Cifx_SysDeviceInfo
	#define GET_Cifx_SysDeviceInfo(fl)  CAL_CMGETAPI( "Cifx_SysDeviceInfo" ) 
	#define CAL_Cifx_SysDeviceInfo  Cifx_SysDeviceInfo
	#define CHK_Cifx_SysDeviceInfo  TRUE
	#define EXP_Cifx_SysDeviceInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_SysDeviceInfo", (RTS_UINTPTR)Cifx_SysDeviceInfo, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_SysDeviceInfo
	#define EXT_CmpHilscherCIFXCifx_SysDeviceInfo
	#define GET_CmpHilscherCIFXCifx_SysDeviceInfo  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_SysDeviceInfo pICmpHilscherCIFX->ICifx_SysDeviceInfo
	#define CHK_CmpHilscherCIFXCifx_SysDeviceInfo (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_SysDeviceInfo  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_SysDeviceInfo
	#define EXT_Cifx_SysDeviceInfo
	#define GET_Cifx_SysDeviceInfo(fl)  CAL_CMGETAPI( "Cifx_SysDeviceInfo" ) 
	#define CAL_Cifx_SysDeviceInfo pICmpHilscherCIFX->ICifx_SysDeviceInfo
	#define CHK_Cifx_SysDeviceInfo (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_SysDeviceInfo  CAL_CMEXPAPI( "Cifx_SysDeviceInfo" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_SysDeviceInfo  PFCIFX_SYSDEVICEINFO pfCifx_SysDeviceInfo;
	#define EXT_Cifx_SysDeviceInfo  extern PFCIFX_SYSDEVICEINFO pfCifx_SysDeviceInfo;
	#define GET_Cifx_SysDeviceInfo(fl)  s_pfCMGetAPI2( "Cifx_SysDeviceInfo", (RTS_VOID_FCTPTR *)&pfCifx_SysDeviceInfo, (fl), 0, 0)
	#define CAL_Cifx_SysDeviceInfo  pfCifx_SysDeviceInfo
	#define CHK_Cifx_SysDeviceInfo  (pfCifx_SysDeviceInfo != NULL)
	#define EXP_Cifx_SysDeviceInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_SysDeviceInfo", (RTS_UINTPTR)Cifx_SysDeviceInfo, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_SysDeviceFindFirstFile(RTS_HANDLE	hSysdevice,	RTS_UI32	ulChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback,	void* pUser);
typedef RTS_RESULT (CDECL * PFCIFX_SYSDEVICEFINDFIRSTFILE) (RTS_HANDLE	hSysdevice,	RTS_UI32	ulChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback,	void* pUser);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_SYSDEVICEFINDFIRSTFILE_NOTIMPLEMENTED)
	#define USE_Cifx_SysDeviceFindFirstFile
	#define EXT_Cifx_SysDeviceFindFirstFile
	#define GET_Cifx_SysDeviceFindFirstFile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_SysDeviceFindFirstFile(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_SysDeviceFindFirstFile  FALSE
	#define EXP_Cifx_SysDeviceFindFirstFile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_SysDeviceFindFirstFile
	#define EXT_Cifx_SysDeviceFindFirstFile
	#define GET_Cifx_SysDeviceFindFirstFile(fl)  CAL_CMGETAPI( "Cifx_SysDeviceFindFirstFile" ) 
	#define CAL_Cifx_SysDeviceFindFirstFile  Cifx_SysDeviceFindFirstFile
	#define CHK_Cifx_SysDeviceFindFirstFile  TRUE
	#define EXP_Cifx_SysDeviceFindFirstFile  CAL_CMEXPAPI( "Cifx_SysDeviceFindFirstFile" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_SysDeviceFindFirstFile
	#define EXT_Cifx_SysDeviceFindFirstFile
	#define GET_Cifx_SysDeviceFindFirstFile(fl)  CAL_CMGETAPI( "Cifx_SysDeviceFindFirstFile" ) 
	#define CAL_Cifx_SysDeviceFindFirstFile  Cifx_SysDeviceFindFirstFile
	#define CHK_Cifx_SysDeviceFindFirstFile  TRUE
	#define EXP_Cifx_SysDeviceFindFirstFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_SysDeviceFindFirstFile", (RTS_UINTPTR)Cifx_SysDeviceFindFirstFile, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_SysDeviceFindFirstFile
	#define EXT_CmpHilscherCIFXCifx_SysDeviceFindFirstFile
	#define GET_CmpHilscherCIFXCifx_SysDeviceFindFirstFile  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_SysDeviceFindFirstFile pICmpHilscherCIFX->ICifx_SysDeviceFindFirstFile
	#define CHK_CmpHilscherCIFXCifx_SysDeviceFindFirstFile (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_SysDeviceFindFirstFile  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_SysDeviceFindFirstFile
	#define EXT_Cifx_SysDeviceFindFirstFile
	#define GET_Cifx_SysDeviceFindFirstFile(fl)  CAL_CMGETAPI( "Cifx_SysDeviceFindFirstFile" ) 
	#define CAL_Cifx_SysDeviceFindFirstFile pICmpHilscherCIFX->ICifx_SysDeviceFindFirstFile
	#define CHK_Cifx_SysDeviceFindFirstFile (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_SysDeviceFindFirstFile  CAL_CMEXPAPI( "Cifx_SysDeviceFindFirstFile" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_SysDeviceFindFirstFile  PFCIFX_SYSDEVICEFINDFIRSTFILE pfCifx_SysDeviceFindFirstFile;
	#define EXT_Cifx_SysDeviceFindFirstFile  extern PFCIFX_SYSDEVICEFINDFIRSTFILE pfCifx_SysDeviceFindFirstFile;
	#define GET_Cifx_SysDeviceFindFirstFile(fl)  s_pfCMGetAPI2( "Cifx_SysDeviceFindFirstFile", (RTS_VOID_FCTPTR *)&pfCifx_SysDeviceFindFirstFile, (fl), 0, 0)
	#define CAL_Cifx_SysDeviceFindFirstFile  pfCifx_SysDeviceFindFirstFile
	#define CHK_Cifx_SysDeviceFindFirstFile  (pfCifx_SysDeviceFindFirstFile != NULL)
	#define EXP_Cifx_SysDeviceFindFirstFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_SysDeviceFindFirstFile", (RTS_UINTPTR)Cifx_SysDeviceFindFirstFile, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_SysDeviceFindNextFile(RTS_HANDLE	hSysdevice,	RTS_UI32	ulChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback,	void* pUser);
typedef RTS_RESULT (CDECL * PFCIFX_SYSDEVICEFINDNEXTFILE) (RTS_HANDLE	hSysdevice,	RTS_UI32	ulChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback,	void* pUser);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_SYSDEVICEFINDNEXTFILE_NOTIMPLEMENTED)
	#define USE_Cifx_SysDeviceFindNextFile
	#define EXT_Cifx_SysDeviceFindNextFile
	#define GET_Cifx_SysDeviceFindNextFile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_SysDeviceFindNextFile(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_SysDeviceFindNextFile  FALSE
	#define EXP_Cifx_SysDeviceFindNextFile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_SysDeviceFindNextFile
	#define EXT_Cifx_SysDeviceFindNextFile
	#define GET_Cifx_SysDeviceFindNextFile(fl)  CAL_CMGETAPI( "Cifx_SysDeviceFindNextFile" ) 
	#define CAL_Cifx_SysDeviceFindNextFile  Cifx_SysDeviceFindNextFile
	#define CHK_Cifx_SysDeviceFindNextFile  TRUE
	#define EXP_Cifx_SysDeviceFindNextFile  CAL_CMEXPAPI( "Cifx_SysDeviceFindNextFile" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_SysDeviceFindNextFile
	#define EXT_Cifx_SysDeviceFindNextFile
	#define GET_Cifx_SysDeviceFindNextFile(fl)  CAL_CMGETAPI( "Cifx_SysDeviceFindNextFile" ) 
	#define CAL_Cifx_SysDeviceFindNextFile  Cifx_SysDeviceFindNextFile
	#define CHK_Cifx_SysDeviceFindNextFile  TRUE
	#define EXP_Cifx_SysDeviceFindNextFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_SysDeviceFindNextFile", (RTS_UINTPTR)Cifx_SysDeviceFindNextFile, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_SysDeviceFindNextFile
	#define EXT_CmpHilscherCIFXCifx_SysDeviceFindNextFile
	#define GET_CmpHilscherCIFXCifx_SysDeviceFindNextFile  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_SysDeviceFindNextFile pICmpHilscherCIFX->ICifx_SysDeviceFindNextFile
	#define CHK_CmpHilscherCIFXCifx_SysDeviceFindNextFile (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_SysDeviceFindNextFile  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_SysDeviceFindNextFile
	#define EXT_Cifx_SysDeviceFindNextFile
	#define GET_Cifx_SysDeviceFindNextFile(fl)  CAL_CMGETAPI( "Cifx_SysDeviceFindNextFile" ) 
	#define CAL_Cifx_SysDeviceFindNextFile pICmpHilscherCIFX->ICifx_SysDeviceFindNextFile
	#define CHK_Cifx_SysDeviceFindNextFile (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_SysDeviceFindNextFile  CAL_CMEXPAPI( "Cifx_SysDeviceFindNextFile" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_SysDeviceFindNextFile  PFCIFX_SYSDEVICEFINDNEXTFILE pfCifx_SysDeviceFindNextFile;
	#define EXT_Cifx_SysDeviceFindNextFile  extern PFCIFX_SYSDEVICEFINDNEXTFILE pfCifx_SysDeviceFindNextFile;
	#define GET_Cifx_SysDeviceFindNextFile(fl)  s_pfCMGetAPI2( "Cifx_SysDeviceFindNextFile", (RTS_VOID_FCTPTR *)&pfCifx_SysDeviceFindNextFile, (fl), 0, 0)
	#define CAL_Cifx_SysDeviceFindNextFile  pfCifx_SysDeviceFindNextFile
	#define CHK_Cifx_SysDeviceFindNextFile  (pfCifx_SysDeviceFindNextFile != NULL)
	#define EXP_Cifx_SysDeviceFindNextFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_SysDeviceFindNextFile", (RTS_UINTPTR)Cifx_SysDeviceFindNextFile, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_SysDeviceUpload(	RTS_HANDLE	hSysdevice,	RTS_UI32	ulChannel, RTS_UI32	ulMode,	char* szFileName, RTS_UI8*	pbyFileData, RTS_UI32*	pulFileSize,	PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void*	pvUser);
typedef RTS_RESULT (CDECL * PFCIFX_SYSDEVICEUPLOAD) (	RTS_HANDLE	hSysdevice,	RTS_UI32	ulChannel, RTS_UI32	ulMode,	char* szFileName, RTS_UI8*	pbyFileData, RTS_UI32*	pulFileSize,	PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void*	pvUser);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_SYSDEVICEUPLOAD_NOTIMPLEMENTED)
	#define USE_Cifx_SysDeviceUpload
	#define EXT_Cifx_SysDeviceUpload
	#define GET_Cifx_SysDeviceUpload(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_SysDeviceUpload(p0,p1,p2,p3,p4,p5,p6,p7,p8)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_SysDeviceUpload  FALSE
	#define EXP_Cifx_SysDeviceUpload  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_SysDeviceUpload
	#define EXT_Cifx_SysDeviceUpload
	#define GET_Cifx_SysDeviceUpload(fl)  CAL_CMGETAPI( "Cifx_SysDeviceUpload" ) 
	#define CAL_Cifx_SysDeviceUpload  Cifx_SysDeviceUpload
	#define CHK_Cifx_SysDeviceUpload  TRUE
	#define EXP_Cifx_SysDeviceUpload  CAL_CMEXPAPI( "Cifx_SysDeviceUpload" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_SysDeviceUpload
	#define EXT_Cifx_SysDeviceUpload
	#define GET_Cifx_SysDeviceUpload(fl)  CAL_CMGETAPI( "Cifx_SysDeviceUpload" ) 
	#define CAL_Cifx_SysDeviceUpload  Cifx_SysDeviceUpload
	#define CHK_Cifx_SysDeviceUpload  TRUE
	#define EXP_Cifx_SysDeviceUpload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_SysDeviceUpload", (RTS_UINTPTR)Cifx_SysDeviceUpload, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_SysDeviceUpload
	#define EXT_CmpHilscherCIFXCifx_SysDeviceUpload
	#define GET_CmpHilscherCIFXCifx_SysDeviceUpload  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_SysDeviceUpload pICmpHilscherCIFX->ICifx_SysDeviceUpload
	#define CHK_CmpHilscherCIFXCifx_SysDeviceUpload (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_SysDeviceUpload  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_SysDeviceUpload
	#define EXT_Cifx_SysDeviceUpload
	#define GET_Cifx_SysDeviceUpload(fl)  CAL_CMGETAPI( "Cifx_SysDeviceUpload" ) 
	#define CAL_Cifx_SysDeviceUpload pICmpHilscherCIFX->ICifx_SysDeviceUpload
	#define CHK_Cifx_SysDeviceUpload (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_SysDeviceUpload  CAL_CMEXPAPI( "Cifx_SysDeviceUpload" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_SysDeviceUpload  PFCIFX_SYSDEVICEUPLOAD pfCifx_SysDeviceUpload;
	#define EXT_Cifx_SysDeviceUpload  extern PFCIFX_SYSDEVICEUPLOAD pfCifx_SysDeviceUpload;
	#define GET_Cifx_SysDeviceUpload(fl)  s_pfCMGetAPI2( "Cifx_SysDeviceUpload", (RTS_VOID_FCTPTR *)&pfCifx_SysDeviceUpload, (fl), 0, 0)
	#define CAL_Cifx_SysDeviceUpload  pfCifx_SysDeviceUpload
	#define CHK_Cifx_SysDeviceUpload  (pfCifx_SysDeviceUpload != NULL)
	#define EXP_Cifx_SysDeviceUpload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_SysDeviceUpload", (RTS_UINTPTR)Cifx_SysDeviceUpload, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelOpen(RTS_HANDLE	hDriver, char*			szBoard, RTS_UI32	ulChannel, RTS_HANDLE*	phChannel);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELOPEN) (RTS_HANDLE	hDriver, char*			szBoard, RTS_UI32	ulChannel, RTS_HANDLE*	phChannel);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELOPEN_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelOpen
	#define EXT_Cifx_ChannelOpen
	#define GET_Cifx_ChannelOpen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelOpen(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelOpen  FALSE
	#define EXP_Cifx_ChannelOpen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelOpen
	#define EXT_Cifx_ChannelOpen
	#define GET_Cifx_ChannelOpen(fl)  CAL_CMGETAPI( "Cifx_ChannelOpen" ) 
	#define CAL_Cifx_ChannelOpen  Cifx_ChannelOpen
	#define CHK_Cifx_ChannelOpen  TRUE
	#define EXP_Cifx_ChannelOpen  CAL_CMEXPAPI( "Cifx_ChannelOpen" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelOpen
	#define EXT_Cifx_ChannelOpen
	#define GET_Cifx_ChannelOpen(fl)  CAL_CMGETAPI( "Cifx_ChannelOpen" ) 
	#define CAL_Cifx_ChannelOpen  Cifx_ChannelOpen
	#define CHK_Cifx_ChannelOpen  TRUE
	#define EXP_Cifx_ChannelOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelOpen", (RTS_UINTPTR)Cifx_ChannelOpen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelOpen
	#define EXT_CmpHilscherCIFXCifx_ChannelOpen
	#define GET_CmpHilscherCIFXCifx_ChannelOpen  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelOpen pICmpHilscherCIFX->ICifx_ChannelOpen
	#define CHK_CmpHilscherCIFXCifx_ChannelOpen (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelOpen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelOpen
	#define EXT_Cifx_ChannelOpen
	#define GET_Cifx_ChannelOpen(fl)  CAL_CMGETAPI( "Cifx_ChannelOpen" ) 
	#define CAL_Cifx_ChannelOpen pICmpHilscherCIFX->ICifx_ChannelOpen
	#define CHK_Cifx_ChannelOpen (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelOpen  CAL_CMEXPAPI( "Cifx_ChannelOpen" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelOpen  PFCIFX_CHANNELOPEN pfCifx_ChannelOpen;
	#define EXT_Cifx_ChannelOpen  extern PFCIFX_CHANNELOPEN pfCifx_ChannelOpen;
	#define GET_Cifx_ChannelOpen(fl)  s_pfCMGetAPI2( "Cifx_ChannelOpen", (RTS_VOID_FCTPTR *)&pfCifx_ChannelOpen, (fl), 0, 0)
	#define CAL_Cifx_ChannelOpen  pfCifx_ChannelOpen
	#define CHK_Cifx_ChannelOpen  (pfCifx_ChannelOpen != NULL)
	#define EXP_Cifx_ChannelOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelOpen", (RTS_UINTPTR)Cifx_ChannelOpen, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelOpen2(RTS_HANDLE	hDriver, char* szBoard, RTS_UI32 ulChannel, RTS_HANDLE* phChannel, RTS_UI32 ulQueueMode);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELOPEN2) (RTS_HANDLE	hDriver, char* szBoard, RTS_UI32 ulChannel, RTS_HANDLE* phChannel, RTS_UI32 ulQueueMode);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELOPEN2_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelOpen2
	#define EXT_Cifx_ChannelOpen2
	#define GET_Cifx_ChannelOpen2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelOpen2(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelOpen2  FALSE
	#define EXP_Cifx_ChannelOpen2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelOpen2
	#define EXT_Cifx_ChannelOpen2
	#define GET_Cifx_ChannelOpen2(fl)  CAL_CMGETAPI( "Cifx_ChannelOpen2" ) 
	#define CAL_Cifx_ChannelOpen2  Cifx_ChannelOpen2
	#define CHK_Cifx_ChannelOpen2  TRUE
	#define EXP_Cifx_ChannelOpen2  CAL_CMEXPAPI( "Cifx_ChannelOpen2" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelOpen2
	#define EXT_Cifx_ChannelOpen2
	#define GET_Cifx_ChannelOpen2(fl)  CAL_CMGETAPI( "Cifx_ChannelOpen2" ) 
	#define CAL_Cifx_ChannelOpen2  Cifx_ChannelOpen2
	#define CHK_Cifx_ChannelOpen2  TRUE
	#define EXP_Cifx_ChannelOpen2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelOpen2", (RTS_UINTPTR)Cifx_ChannelOpen2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelOpen2
	#define EXT_CmpHilscherCIFXCifx_ChannelOpen2
	#define GET_CmpHilscherCIFXCifx_ChannelOpen2  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelOpen2 pICmpHilscherCIFX->ICifx_ChannelOpen2
	#define CHK_CmpHilscherCIFXCifx_ChannelOpen2 (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelOpen2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelOpen2
	#define EXT_Cifx_ChannelOpen2
	#define GET_Cifx_ChannelOpen2(fl)  CAL_CMGETAPI( "Cifx_ChannelOpen2" ) 
	#define CAL_Cifx_ChannelOpen2 pICmpHilscherCIFX->ICifx_ChannelOpen2
	#define CHK_Cifx_ChannelOpen2 (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelOpen2  CAL_CMEXPAPI( "Cifx_ChannelOpen2" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelOpen2  PFCIFX_CHANNELOPEN2 pfCifx_ChannelOpen2;
	#define EXT_Cifx_ChannelOpen2  extern PFCIFX_CHANNELOPEN2 pfCifx_ChannelOpen2;
	#define GET_Cifx_ChannelOpen2(fl)  s_pfCMGetAPI2( "Cifx_ChannelOpen2", (RTS_VOID_FCTPTR *)&pfCifx_ChannelOpen2, (fl), 0, 0)
	#define CAL_Cifx_ChannelOpen2  pfCifx_ChannelOpen2
	#define CHK_Cifx_ChannelOpen2  (pfCifx_ChannelOpen2 != NULL)
	#define EXP_Cifx_ChannelOpen2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelOpen2", (RTS_UINTPTR)Cifx_ChannelOpen2, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelClose(RTS_HANDLE	hChannel);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELCLOSE) (RTS_HANDLE	hChannel);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELCLOSE_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelClose
	#define EXT_Cifx_ChannelClose
	#define GET_Cifx_ChannelClose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelClose(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelClose  FALSE
	#define EXP_Cifx_ChannelClose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelClose
	#define EXT_Cifx_ChannelClose
	#define GET_Cifx_ChannelClose(fl)  CAL_CMGETAPI( "Cifx_ChannelClose" ) 
	#define CAL_Cifx_ChannelClose  Cifx_ChannelClose
	#define CHK_Cifx_ChannelClose  TRUE
	#define EXP_Cifx_ChannelClose  CAL_CMEXPAPI( "Cifx_ChannelClose" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelClose
	#define EXT_Cifx_ChannelClose
	#define GET_Cifx_ChannelClose(fl)  CAL_CMGETAPI( "Cifx_ChannelClose" ) 
	#define CAL_Cifx_ChannelClose  Cifx_ChannelClose
	#define CHK_Cifx_ChannelClose  TRUE
	#define EXP_Cifx_ChannelClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelClose", (RTS_UINTPTR)Cifx_ChannelClose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelClose
	#define EXT_CmpHilscherCIFXCifx_ChannelClose
	#define GET_CmpHilscherCIFXCifx_ChannelClose  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelClose pICmpHilscherCIFX->ICifx_ChannelClose
	#define CHK_CmpHilscherCIFXCifx_ChannelClose (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelClose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelClose
	#define EXT_Cifx_ChannelClose
	#define GET_Cifx_ChannelClose(fl)  CAL_CMGETAPI( "Cifx_ChannelClose" ) 
	#define CAL_Cifx_ChannelClose pICmpHilscherCIFX->ICifx_ChannelClose
	#define CHK_Cifx_ChannelClose (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelClose  CAL_CMEXPAPI( "Cifx_ChannelClose" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelClose  PFCIFX_CHANNELCLOSE pfCifx_ChannelClose;
	#define EXT_Cifx_ChannelClose  extern PFCIFX_CHANNELCLOSE pfCifx_ChannelClose;
	#define GET_Cifx_ChannelClose(fl)  s_pfCMGetAPI2( "Cifx_ChannelClose", (RTS_VOID_FCTPTR *)&pfCifx_ChannelClose, (fl), 0, 0)
	#define CAL_Cifx_ChannelClose  pfCifx_ChannelClose
	#define CHK_Cifx_ChannelClose  (pfCifx_ChannelClose != NULL)
	#define EXP_Cifx_ChannelClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelClose", (RTS_UINTPTR)Cifx_ChannelClose, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelDownload(RTS_HANDLE	hChannel, RTS_UI32	ulMode, char* szFileName, RTS_UI8*	pbyFileData, RTS_UI32	ulFileSize,	PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELDOWNLOAD) (RTS_HANDLE	hChannel, RTS_UI32	ulMode, char* szFileName, RTS_UI8*	pbyFileData, RTS_UI32	ulFileSize,	PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELDOWNLOAD_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelDownload
	#define EXT_Cifx_ChannelDownload
	#define GET_Cifx_ChannelDownload(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelDownload(p0,p1,p2,p3,p4,p5,p6,p7)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelDownload  FALSE
	#define EXP_Cifx_ChannelDownload  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelDownload
	#define EXT_Cifx_ChannelDownload
	#define GET_Cifx_ChannelDownload(fl)  CAL_CMGETAPI( "Cifx_ChannelDownload" ) 
	#define CAL_Cifx_ChannelDownload  Cifx_ChannelDownload
	#define CHK_Cifx_ChannelDownload  TRUE
	#define EXP_Cifx_ChannelDownload  CAL_CMEXPAPI( "Cifx_ChannelDownload" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelDownload
	#define EXT_Cifx_ChannelDownload
	#define GET_Cifx_ChannelDownload(fl)  CAL_CMGETAPI( "Cifx_ChannelDownload" ) 
	#define CAL_Cifx_ChannelDownload  Cifx_ChannelDownload
	#define CHK_Cifx_ChannelDownload  TRUE
	#define EXP_Cifx_ChannelDownload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelDownload", (RTS_UINTPTR)Cifx_ChannelDownload, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelDownload
	#define EXT_CmpHilscherCIFXCifx_ChannelDownload
	#define GET_CmpHilscherCIFXCifx_ChannelDownload  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelDownload pICmpHilscherCIFX->ICifx_ChannelDownload
	#define CHK_CmpHilscherCIFXCifx_ChannelDownload (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelDownload  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelDownload
	#define EXT_Cifx_ChannelDownload
	#define GET_Cifx_ChannelDownload(fl)  CAL_CMGETAPI( "Cifx_ChannelDownload" ) 
	#define CAL_Cifx_ChannelDownload pICmpHilscherCIFX->ICifx_ChannelDownload
	#define CHK_Cifx_ChannelDownload (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelDownload  CAL_CMEXPAPI( "Cifx_ChannelDownload" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelDownload  PFCIFX_CHANNELDOWNLOAD pfCifx_ChannelDownload;
	#define EXT_Cifx_ChannelDownload  extern PFCIFX_CHANNELDOWNLOAD pfCifx_ChannelDownload;
	#define GET_Cifx_ChannelDownload(fl)  s_pfCMGetAPI2( "Cifx_ChannelDownload", (RTS_VOID_FCTPTR *)&pfCifx_ChannelDownload, (fl), 0, 0)
	#define CAL_Cifx_ChannelDownload  pfCifx_ChannelDownload
	#define CHK_Cifx_ChannelDownload  (pfCifx_ChannelDownload != NULL)
	#define EXP_Cifx_ChannelDownload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelDownload", (RTS_UINTPTR)Cifx_ChannelDownload, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelFindFirstFile(RTS_HANDLE	hChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void*	pvUser);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELFINDFIRSTFILE) (RTS_HANDLE	hChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void*	pvUser);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELFINDFIRSTFILE_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelFindFirstFile
	#define EXT_Cifx_ChannelFindFirstFile
	#define GET_Cifx_ChannelFindFirstFile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelFindFirstFile(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelFindFirstFile  FALSE
	#define EXP_Cifx_ChannelFindFirstFile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelFindFirstFile
	#define EXT_Cifx_ChannelFindFirstFile
	#define GET_Cifx_ChannelFindFirstFile(fl)  CAL_CMGETAPI( "Cifx_ChannelFindFirstFile" ) 
	#define CAL_Cifx_ChannelFindFirstFile  Cifx_ChannelFindFirstFile
	#define CHK_Cifx_ChannelFindFirstFile  TRUE
	#define EXP_Cifx_ChannelFindFirstFile  CAL_CMEXPAPI( "Cifx_ChannelFindFirstFile" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelFindFirstFile
	#define EXT_Cifx_ChannelFindFirstFile
	#define GET_Cifx_ChannelFindFirstFile(fl)  CAL_CMGETAPI( "Cifx_ChannelFindFirstFile" ) 
	#define CAL_Cifx_ChannelFindFirstFile  Cifx_ChannelFindFirstFile
	#define CHK_Cifx_ChannelFindFirstFile  TRUE
	#define EXP_Cifx_ChannelFindFirstFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelFindFirstFile", (RTS_UINTPTR)Cifx_ChannelFindFirstFile, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelFindFirstFile
	#define EXT_CmpHilscherCIFXCifx_ChannelFindFirstFile
	#define GET_CmpHilscherCIFXCifx_ChannelFindFirstFile  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelFindFirstFile pICmpHilscherCIFX->ICifx_ChannelFindFirstFile
	#define CHK_CmpHilscherCIFXCifx_ChannelFindFirstFile (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelFindFirstFile  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelFindFirstFile
	#define EXT_Cifx_ChannelFindFirstFile
	#define GET_Cifx_ChannelFindFirstFile(fl)  CAL_CMGETAPI( "Cifx_ChannelFindFirstFile" ) 
	#define CAL_Cifx_ChannelFindFirstFile pICmpHilscherCIFX->ICifx_ChannelFindFirstFile
	#define CHK_Cifx_ChannelFindFirstFile (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelFindFirstFile  CAL_CMEXPAPI( "Cifx_ChannelFindFirstFile" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelFindFirstFile  PFCIFX_CHANNELFINDFIRSTFILE pfCifx_ChannelFindFirstFile;
	#define EXT_Cifx_ChannelFindFirstFile  extern PFCIFX_CHANNELFINDFIRSTFILE pfCifx_ChannelFindFirstFile;
	#define GET_Cifx_ChannelFindFirstFile(fl)  s_pfCMGetAPI2( "Cifx_ChannelFindFirstFile", (RTS_VOID_FCTPTR *)&pfCifx_ChannelFindFirstFile, (fl), 0, 0)
	#define CAL_Cifx_ChannelFindFirstFile  pfCifx_ChannelFindFirstFile
	#define CHK_Cifx_ChannelFindFirstFile  (pfCifx_ChannelFindFirstFile != NULL)
	#define EXP_Cifx_ChannelFindFirstFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelFindFirstFile", (RTS_UINTPTR)Cifx_ChannelFindFirstFile, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelFindNextFile(RTS_HANDLE	hChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void*	pvUser);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELFINDNEXTFILE) (RTS_HANDLE	hChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void*	pvUser);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELFINDNEXTFILE_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelFindNextFile
	#define EXT_Cifx_ChannelFindNextFile
	#define GET_Cifx_ChannelFindNextFile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelFindNextFile(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelFindNextFile  FALSE
	#define EXP_Cifx_ChannelFindNextFile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelFindNextFile
	#define EXT_Cifx_ChannelFindNextFile
	#define GET_Cifx_ChannelFindNextFile(fl)  CAL_CMGETAPI( "Cifx_ChannelFindNextFile" ) 
	#define CAL_Cifx_ChannelFindNextFile  Cifx_ChannelFindNextFile
	#define CHK_Cifx_ChannelFindNextFile  TRUE
	#define EXP_Cifx_ChannelFindNextFile  CAL_CMEXPAPI( "Cifx_ChannelFindNextFile" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelFindNextFile
	#define EXT_Cifx_ChannelFindNextFile
	#define GET_Cifx_ChannelFindNextFile(fl)  CAL_CMGETAPI( "Cifx_ChannelFindNextFile" ) 
	#define CAL_Cifx_ChannelFindNextFile  Cifx_ChannelFindNextFile
	#define CHK_Cifx_ChannelFindNextFile  TRUE
	#define EXP_Cifx_ChannelFindNextFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelFindNextFile", (RTS_UINTPTR)Cifx_ChannelFindNextFile, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelFindNextFile
	#define EXT_CmpHilscherCIFXCifx_ChannelFindNextFile
	#define GET_CmpHilscherCIFXCifx_ChannelFindNextFile  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelFindNextFile pICmpHilscherCIFX->ICifx_ChannelFindNextFile
	#define CHK_CmpHilscherCIFXCifx_ChannelFindNextFile (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelFindNextFile  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelFindNextFile
	#define EXT_Cifx_ChannelFindNextFile
	#define GET_Cifx_ChannelFindNextFile(fl)  CAL_CMGETAPI( "Cifx_ChannelFindNextFile" ) 
	#define CAL_Cifx_ChannelFindNextFile pICmpHilscherCIFX->ICifx_ChannelFindNextFile
	#define CHK_Cifx_ChannelFindNextFile (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelFindNextFile  CAL_CMEXPAPI( "Cifx_ChannelFindNextFile" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelFindNextFile  PFCIFX_CHANNELFINDNEXTFILE pfCifx_ChannelFindNextFile;
	#define EXT_Cifx_ChannelFindNextFile  extern PFCIFX_CHANNELFINDNEXTFILE pfCifx_ChannelFindNextFile;
	#define GET_Cifx_ChannelFindNextFile(fl)  s_pfCMGetAPI2( "Cifx_ChannelFindNextFile", (RTS_VOID_FCTPTR *)&pfCifx_ChannelFindNextFile, (fl), 0, 0)
	#define CAL_Cifx_ChannelFindNextFile  pfCifx_ChannelFindNextFile
	#define CHK_Cifx_ChannelFindNextFile  (pfCifx_ChannelFindNextFile != NULL)
	#define EXP_Cifx_ChannelFindNextFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelFindNextFile", (RTS_UINTPTR)Cifx_ChannelFindNextFile, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelUpload(RTS_HANDLE	hChannel, RTS_UI32	ulMode, char* szFileName, RTS_UI8*	pbyFileData, RTS_UI32*	pulFileSize,	PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELUPLOAD) (RTS_HANDLE	hChannel, RTS_UI32	ulMode, char* szFileName, RTS_UI8*	pbyFileData, RTS_UI32*	pulFileSize,	PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELUPLOAD_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelUpload
	#define EXT_Cifx_ChannelUpload
	#define GET_Cifx_ChannelUpload(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelUpload(p0,p1,p2,p3,p4,p5,p6,p7)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelUpload  FALSE
	#define EXP_Cifx_ChannelUpload  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelUpload
	#define EXT_Cifx_ChannelUpload
	#define GET_Cifx_ChannelUpload(fl)  CAL_CMGETAPI( "Cifx_ChannelUpload" ) 
	#define CAL_Cifx_ChannelUpload  Cifx_ChannelUpload
	#define CHK_Cifx_ChannelUpload  TRUE
	#define EXP_Cifx_ChannelUpload  CAL_CMEXPAPI( "Cifx_ChannelUpload" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelUpload
	#define EXT_Cifx_ChannelUpload
	#define GET_Cifx_ChannelUpload(fl)  CAL_CMGETAPI( "Cifx_ChannelUpload" ) 
	#define CAL_Cifx_ChannelUpload  Cifx_ChannelUpload
	#define CHK_Cifx_ChannelUpload  TRUE
	#define EXP_Cifx_ChannelUpload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelUpload", (RTS_UINTPTR)Cifx_ChannelUpload, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelUpload
	#define EXT_CmpHilscherCIFXCifx_ChannelUpload
	#define GET_CmpHilscherCIFXCifx_ChannelUpload  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelUpload pICmpHilscherCIFX->ICifx_ChannelUpload
	#define CHK_CmpHilscherCIFXCifx_ChannelUpload (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelUpload  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelUpload
	#define EXT_Cifx_ChannelUpload
	#define GET_Cifx_ChannelUpload(fl)  CAL_CMGETAPI( "Cifx_ChannelUpload" ) 
	#define CAL_Cifx_ChannelUpload pICmpHilscherCIFX->ICifx_ChannelUpload
	#define CHK_Cifx_ChannelUpload (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelUpload  CAL_CMEXPAPI( "Cifx_ChannelUpload" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelUpload  PFCIFX_CHANNELUPLOAD pfCifx_ChannelUpload;
	#define EXT_Cifx_ChannelUpload  extern PFCIFX_CHANNELUPLOAD pfCifx_ChannelUpload;
	#define GET_Cifx_ChannelUpload(fl)  s_pfCMGetAPI2( "Cifx_ChannelUpload", (RTS_VOID_FCTPTR *)&pfCifx_ChannelUpload, (fl), 0, 0)
	#define CAL_Cifx_ChannelUpload  pfCifx_ChannelUpload
	#define CHK_Cifx_ChannelUpload  (pfCifx_ChannelUpload != NULL)
	#define EXP_Cifx_ChannelUpload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelUpload", (RTS_UINTPTR)Cifx_ChannelUpload, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelGetMBXState(RTS_HANDLE	hChannel, RTS_UI32*	pulRecvPktCount, RTS_UI32*	pulSendPktCount);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELGETMBXSTATE) (RTS_HANDLE	hChannel, RTS_UI32*	pulRecvPktCount, RTS_UI32*	pulSendPktCount);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELGETMBXSTATE_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelGetMBXState
	#define EXT_Cifx_ChannelGetMBXState
	#define GET_Cifx_ChannelGetMBXState(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelGetMBXState(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelGetMBXState  FALSE
	#define EXP_Cifx_ChannelGetMBXState  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelGetMBXState
	#define EXT_Cifx_ChannelGetMBXState
	#define GET_Cifx_ChannelGetMBXState(fl)  CAL_CMGETAPI( "Cifx_ChannelGetMBXState" ) 
	#define CAL_Cifx_ChannelGetMBXState  Cifx_ChannelGetMBXState
	#define CHK_Cifx_ChannelGetMBXState  TRUE
	#define EXP_Cifx_ChannelGetMBXState  CAL_CMEXPAPI( "Cifx_ChannelGetMBXState" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelGetMBXState
	#define EXT_Cifx_ChannelGetMBXState
	#define GET_Cifx_ChannelGetMBXState(fl)  CAL_CMGETAPI( "Cifx_ChannelGetMBXState" ) 
	#define CAL_Cifx_ChannelGetMBXState  Cifx_ChannelGetMBXState
	#define CHK_Cifx_ChannelGetMBXState  TRUE
	#define EXP_Cifx_ChannelGetMBXState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelGetMBXState", (RTS_UINTPTR)Cifx_ChannelGetMBXState, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelGetMBXState
	#define EXT_CmpHilscherCIFXCifx_ChannelGetMBXState
	#define GET_CmpHilscherCIFXCifx_ChannelGetMBXState  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelGetMBXState pICmpHilscherCIFX->ICifx_ChannelGetMBXState
	#define CHK_CmpHilscherCIFXCifx_ChannelGetMBXState (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelGetMBXState  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelGetMBXState
	#define EXT_Cifx_ChannelGetMBXState
	#define GET_Cifx_ChannelGetMBXState(fl)  CAL_CMGETAPI( "Cifx_ChannelGetMBXState" ) 
	#define CAL_Cifx_ChannelGetMBXState pICmpHilscherCIFX->ICifx_ChannelGetMBXState
	#define CHK_Cifx_ChannelGetMBXState (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelGetMBXState  CAL_CMEXPAPI( "Cifx_ChannelGetMBXState" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelGetMBXState  PFCIFX_CHANNELGETMBXSTATE pfCifx_ChannelGetMBXState;
	#define EXT_Cifx_ChannelGetMBXState  extern PFCIFX_CHANNELGETMBXSTATE pfCifx_ChannelGetMBXState;
	#define GET_Cifx_ChannelGetMBXState(fl)  s_pfCMGetAPI2( "Cifx_ChannelGetMBXState", (RTS_VOID_FCTPTR *)&pfCifx_ChannelGetMBXState, (fl), 0, 0)
	#define CAL_Cifx_ChannelGetMBXState  pfCifx_ChannelGetMBXState
	#define CHK_Cifx_ChannelGetMBXState  (pfCifx_ChannelGetMBXState != NULL)
	#define EXP_Cifx_ChannelGetMBXState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelGetMBXState", (RTS_UINTPTR)Cifx_ChannelGetMBXState, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelPutPacket(RTS_HANDLE	hChannel, CIFX_PACKET*	ptSendPkt, RTS_UI32	ulTimeout);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELPUTPACKET) (RTS_HANDLE	hChannel, CIFX_PACKET*	ptSendPkt, RTS_UI32	ulTimeout);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELPUTPACKET_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelPutPacket
	#define EXT_Cifx_ChannelPutPacket
	#define GET_Cifx_ChannelPutPacket(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelPutPacket(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelPutPacket  FALSE
	#define EXP_Cifx_ChannelPutPacket  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelPutPacket
	#define EXT_Cifx_ChannelPutPacket
	#define GET_Cifx_ChannelPutPacket(fl)  CAL_CMGETAPI( "Cifx_ChannelPutPacket" ) 
	#define CAL_Cifx_ChannelPutPacket  Cifx_ChannelPutPacket
	#define CHK_Cifx_ChannelPutPacket  TRUE
	#define EXP_Cifx_ChannelPutPacket  CAL_CMEXPAPI( "Cifx_ChannelPutPacket" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelPutPacket
	#define EXT_Cifx_ChannelPutPacket
	#define GET_Cifx_ChannelPutPacket(fl)  CAL_CMGETAPI( "Cifx_ChannelPutPacket" ) 
	#define CAL_Cifx_ChannelPutPacket  Cifx_ChannelPutPacket
	#define CHK_Cifx_ChannelPutPacket  TRUE
	#define EXP_Cifx_ChannelPutPacket  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelPutPacket", (RTS_UINTPTR)Cifx_ChannelPutPacket, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelPutPacket
	#define EXT_CmpHilscherCIFXCifx_ChannelPutPacket
	#define GET_CmpHilscherCIFXCifx_ChannelPutPacket  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelPutPacket pICmpHilscherCIFX->ICifx_ChannelPutPacket
	#define CHK_CmpHilscherCIFXCifx_ChannelPutPacket (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelPutPacket  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelPutPacket
	#define EXT_Cifx_ChannelPutPacket
	#define GET_Cifx_ChannelPutPacket(fl)  CAL_CMGETAPI( "Cifx_ChannelPutPacket" ) 
	#define CAL_Cifx_ChannelPutPacket pICmpHilscherCIFX->ICifx_ChannelPutPacket
	#define CHK_Cifx_ChannelPutPacket (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelPutPacket  CAL_CMEXPAPI( "Cifx_ChannelPutPacket" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelPutPacket  PFCIFX_CHANNELPUTPACKET pfCifx_ChannelPutPacket;
	#define EXT_Cifx_ChannelPutPacket  extern PFCIFX_CHANNELPUTPACKET pfCifx_ChannelPutPacket;
	#define GET_Cifx_ChannelPutPacket(fl)  s_pfCMGetAPI2( "Cifx_ChannelPutPacket", (RTS_VOID_FCTPTR *)&pfCifx_ChannelPutPacket, (fl), 0, 0)
	#define CAL_Cifx_ChannelPutPacket  pfCifx_ChannelPutPacket
	#define CHK_Cifx_ChannelPutPacket  (pfCifx_ChannelPutPacket != NULL)
	#define EXP_Cifx_ChannelPutPacket  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelPutPacket", (RTS_UINTPTR)Cifx_ChannelPutPacket, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelGetPacket(RTS_HANDLE	hChannel, RTS_UI32	ulSize, CIFX_PACKET*	ptRecvPkt, RTS_UI32	ulTimeout);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELGETPACKET) (RTS_HANDLE	hChannel, RTS_UI32	ulSize, CIFX_PACKET*	ptRecvPkt, RTS_UI32	ulTimeout);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELGETPACKET_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelGetPacket
	#define EXT_Cifx_ChannelGetPacket
	#define GET_Cifx_ChannelGetPacket(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelGetPacket(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelGetPacket  FALSE
	#define EXP_Cifx_ChannelGetPacket  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelGetPacket
	#define EXT_Cifx_ChannelGetPacket
	#define GET_Cifx_ChannelGetPacket(fl)  CAL_CMGETAPI( "Cifx_ChannelGetPacket" ) 
	#define CAL_Cifx_ChannelGetPacket  Cifx_ChannelGetPacket
	#define CHK_Cifx_ChannelGetPacket  TRUE
	#define EXP_Cifx_ChannelGetPacket  CAL_CMEXPAPI( "Cifx_ChannelGetPacket" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelGetPacket
	#define EXT_Cifx_ChannelGetPacket
	#define GET_Cifx_ChannelGetPacket(fl)  CAL_CMGETAPI( "Cifx_ChannelGetPacket" ) 
	#define CAL_Cifx_ChannelGetPacket  Cifx_ChannelGetPacket
	#define CHK_Cifx_ChannelGetPacket  TRUE
	#define EXP_Cifx_ChannelGetPacket  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelGetPacket", (RTS_UINTPTR)Cifx_ChannelGetPacket, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelGetPacket
	#define EXT_CmpHilscherCIFXCifx_ChannelGetPacket
	#define GET_CmpHilscherCIFXCifx_ChannelGetPacket  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelGetPacket pICmpHilscherCIFX->ICifx_ChannelGetPacket
	#define CHK_CmpHilscherCIFXCifx_ChannelGetPacket (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelGetPacket  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelGetPacket
	#define EXT_Cifx_ChannelGetPacket
	#define GET_Cifx_ChannelGetPacket(fl)  CAL_CMGETAPI( "Cifx_ChannelGetPacket" ) 
	#define CAL_Cifx_ChannelGetPacket pICmpHilscherCIFX->ICifx_ChannelGetPacket
	#define CHK_Cifx_ChannelGetPacket (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelGetPacket  CAL_CMEXPAPI( "Cifx_ChannelGetPacket" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelGetPacket  PFCIFX_CHANNELGETPACKET pfCifx_ChannelGetPacket;
	#define EXT_Cifx_ChannelGetPacket  extern PFCIFX_CHANNELGETPACKET pfCifx_ChannelGetPacket;
	#define GET_Cifx_ChannelGetPacket(fl)  s_pfCMGetAPI2( "Cifx_ChannelGetPacket", (RTS_VOID_FCTPTR *)&pfCifx_ChannelGetPacket, (fl), 0, 0)
	#define CAL_Cifx_ChannelGetPacket  pfCifx_ChannelGetPacket
	#define CHK_Cifx_ChannelGetPacket  (pfCifx_ChannelGetPacket != NULL)
	#define EXP_Cifx_ChannelGetPacket  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelGetPacket", (RTS_UINTPTR)Cifx_ChannelGetPacket, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelReset(RTS_HANDLE	hChannel, RTS_UI32	ulResetMode, RTS_UI32	ulTimeout);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELRESET) (RTS_HANDLE	hChannel, RTS_UI32	ulResetMode, RTS_UI32	ulTimeout);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELRESET_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelReset
	#define EXT_Cifx_ChannelReset
	#define GET_Cifx_ChannelReset(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelReset(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelReset  FALSE
	#define EXP_Cifx_ChannelReset  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelReset
	#define EXT_Cifx_ChannelReset
	#define GET_Cifx_ChannelReset(fl)  CAL_CMGETAPI( "Cifx_ChannelReset" ) 
	#define CAL_Cifx_ChannelReset  Cifx_ChannelReset
	#define CHK_Cifx_ChannelReset  TRUE
	#define EXP_Cifx_ChannelReset  CAL_CMEXPAPI( "Cifx_ChannelReset" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelReset
	#define EXT_Cifx_ChannelReset
	#define GET_Cifx_ChannelReset(fl)  CAL_CMGETAPI( "Cifx_ChannelReset" ) 
	#define CAL_Cifx_ChannelReset  Cifx_ChannelReset
	#define CHK_Cifx_ChannelReset  TRUE
	#define EXP_Cifx_ChannelReset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelReset", (RTS_UINTPTR)Cifx_ChannelReset, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelReset
	#define EXT_CmpHilscherCIFXCifx_ChannelReset
	#define GET_CmpHilscherCIFXCifx_ChannelReset  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelReset pICmpHilscherCIFX->ICifx_ChannelReset
	#define CHK_CmpHilscherCIFXCifx_ChannelReset (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelReset  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelReset
	#define EXT_Cifx_ChannelReset
	#define GET_Cifx_ChannelReset(fl)  CAL_CMGETAPI( "Cifx_ChannelReset" ) 
	#define CAL_Cifx_ChannelReset pICmpHilscherCIFX->ICifx_ChannelReset
	#define CHK_Cifx_ChannelReset (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelReset  CAL_CMEXPAPI( "Cifx_ChannelReset" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelReset  PFCIFX_CHANNELRESET pfCifx_ChannelReset;
	#define EXT_Cifx_ChannelReset  extern PFCIFX_CHANNELRESET pfCifx_ChannelReset;
	#define GET_Cifx_ChannelReset(fl)  s_pfCMGetAPI2( "Cifx_ChannelReset", (RTS_VOID_FCTPTR *)&pfCifx_ChannelReset, (fl), 0, 0)
	#define CAL_Cifx_ChannelReset  pfCifx_ChannelReset
	#define CHK_Cifx_ChannelReset  (pfCifx_ChannelReset != NULL)
	#define EXP_Cifx_ChannelReset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelReset", (RTS_UINTPTR)Cifx_ChannelReset, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelGetSendPacket(RTS_HANDLE	hChannel, RTS_UI32	ulSize, CIFX_PACKET*	ptRecvPkt);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELGETSENDPACKET) (RTS_HANDLE	hChannel, RTS_UI32	ulSize, CIFX_PACKET*	ptRecvPkt);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELGETSENDPACKET_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelGetSendPacket
	#define EXT_Cifx_ChannelGetSendPacket
	#define GET_Cifx_ChannelGetSendPacket(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelGetSendPacket(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelGetSendPacket  FALSE
	#define EXP_Cifx_ChannelGetSendPacket  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelGetSendPacket
	#define EXT_Cifx_ChannelGetSendPacket
	#define GET_Cifx_ChannelGetSendPacket(fl)  CAL_CMGETAPI( "Cifx_ChannelGetSendPacket" ) 
	#define CAL_Cifx_ChannelGetSendPacket  Cifx_ChannelGetSendPacket
	#define CHK_Cifx_ChannelGetSendPacket  TRUE
	#define EXP_Cifx_ChannelGetSendPacket  CAL_CMEXPAPI( "Cifx_ChannelGetSendPacket" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelGetSendPacket
	#define EXT_Cifx_ChannelGetSendPacket
	#define GET_Cifx_ChannelGetSendPacket(fl)  CAL_CMGETAPI( "Cifx_ChannelGetSendPacket" ) 
	#define CAL_Cifx_ChannelGetSendPacket  Cifx_ChannelGetSendPacket
	#define CHK_Cifx_ChannelGetSendPacket  TRUE
	#define EXP_Cifx_ChannelGetSendPacket  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelGetSendPacket", (RTS_UINTPTR)Cifx_ChannelGetSendPacket, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelGetSendPacket
	#define EXT_CmpHilscherCIFXCifx_ChannelGetSendPacket
	#define GET_CmpHilscherCIFXCifx_ChannelGetSendPacket  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelGetSendPacket pICmpHilscherCIFX->ICifx_ChannelGetSendPacket
	#define CHK_CmpHilscherCIFXCifx_ChannelGetSendPacket (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelGetSendPacket  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelGetSendPacket
	#define EXT_Cifx_ChannelGetSendPacket
	#define GET_Cifx_ChannelGetSendPacket(fl)  CAL_CMGETAPI( "Cifx_ChannelGetSendPacket" ) 
	#define CAL_Cifx_ChannelGetSendPacket pICmpHilscherCIFX->ICifx_ChannelGetSendPacket
	#define CHK_Cifx_ChannelGetSendPacket (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelGetSendPacket  CAL_CMEXPAPI( "Cifx_ChannelGetSendPacket" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelGetSendPacket  PFCIFX_CHANNELGETSENDPACKET pfCifx_ChannelGetSendPacket;
	#define EXT_Cifx_ChannelGetSendPacket  extern PFCIFX_CHANNELGETSENDPACKET pfCifx_ChannelGetSendPacket;
	#define GET_Cifx_ChannelGetSendPacket(fl)  s_pfCMGetAPI2( "Cifx_ChannelGetSendPacket", (RTS_VOID_FCTPTR *)&pfCifx_ChannelGetSendPacket, (fl), 0, 0)
	#define CAL_Cifx_ChannelGetSendPacket  pfCifx_ChannelGetSendPacket
	#define CHK_Cifx_ChannelGetSendPacket  (pfCifx_ChannelGetSendPacket != NULL)
	#define EXP_Cifx_ChannelGetSendPacket  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelGetSendPacket", (RTS_UINTPTR)Cifx_ChannelGetSendPacket, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelConfigLock(RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32*	pulState, RTS_UI32	ulTimeout);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELCONFIGLOCK) (RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32*	pulState, RTS_UI32	ulTimeout);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELCONFIGLOCK_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelConfigLock
	#define EXT_Cifx_ChannelConfigLock
	#define GET_Cifx_ChannelConfigLock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelConfigLock(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelConfigLock  FALSE
	#define EXP_Cifx_ChannelConfigLock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelConfigLock
	#define EXT_Cifx_ChannelConfigLock
	#define GET_Cifx_ChannelConfigLock(fl)  CAL_CMGETAPI( "Cifx_ChannelConfigLock" ) 
	#define CAL_Cifx_ChannelConfigLock  Cifx_ChannelConfigLock
	#define CHK_Cifx_ChannelConfigLock  TRUE
	#define EXP_Cifx_ChannelConfigLock  CAL_CMEXPAPI( "Cifx_ChannelConfigLock" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelConfigLock
	#define EXT_Cifx_ChannelConfigLock
	#define GET_Cifx_ChannelConfigLock(fl)  CAL_CMGETAPI( "Cifx_ChannelConfigLock" ) 
	#define CAL_Cifx_ChannelConfigLock  Cifx_ChannelConfigLock
	#define CHK_Cifx_ChannelConfigLock  TRUE
	#define EXP_Cifx_ChannelConfigLock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelConfigLock", (RTS_UINTPTR)Cifx_ChannelConfigLock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelConfigLock
	#define EXT_CmpHilscherCIFXCifx_ChannelConfigLock
	#define GET_CmpHilscherCIFXCifx_ChannelConfigLock  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelConfigLock pICmpHilscherCIFX->ICifx_ChannelConfigLock
	#define CHK_CmpHilscherCIFXCifx_ChannelConfigLock (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelConfigLock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelConfigLock
	#define EXT_Cifx_ChannelConfigLock
	#define GET_Cifx_ChannelConfigLock(fl)  CAL_CMGETAPI( "Cifx_ChannelConfigLock" ) 
	#define CAL_Cifx_ChannelConfigLock pICmpHilscherCIFX->ICifx_ChannelConfigLock
	#define CHK_Cifx_ChannelConfigLock (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelConfigLock  CAL_CMEXPAPI( "Cifx_ChannelConfigLock" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelConfigLock  PFCIFX_CHANNELCONFIGLOCK pfCifx_ChannelConfigLock;
	#define EXT_Cifx_ChannelConfigLock  extern PFCIFX_CHANNELCONFIGLOCK pfCifx_ChannelConfigLock;
	#define GET_Cifx_ChannelConfigLock(fl)  s_pfCMGetAPI2( "Cifx_ChannelConfigLock", (RTS_VOID_FCTPTR *)&pfCifx_ChannelConfigLock, (fl), 0, 0)
	#define CAL_Cifx_ChannelConfigLock  pfCifx_ChannelConfigLock
	#define CHK_Cifx_ChannelConfigLock  (pfCifx_ChannelConfigLock != NULL)
	#define EXP_Cifx_ChannelConfigLock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelConfigLock", (RTS_UINTPTR)Cifx_ChannelConfigLock, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelInfo(RTS_HANDLE	hChannel, RTS_UI32	ulSize, void*			pvChannelInfo);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELINFO) (RTS_HANDLE	hChannel, RTS_UI32	ulSize, void*			pvChannelInfo);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELINFO_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelInfo
	#define EXT_Cifx_ChannelInfo
	#define GET_Cifx_ChannelInfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelInfo(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelInfo  FALSE
	#define EXP_Cifx_ChannelInfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelInfo
	#define EXT_Cifx_ChannelInfo
	#define GET_Cifx_ChannelInfo(fl)  CAL_CMGETAPI( "Cifx_ChannelInfo" ) 
	#define CAL_Cifx_ChannelInfo  Cifx_ChannelInfo
	#define CHK_Cifx_ChannelInfo  TRUE
	#define EXP_Cifx_ChannelInfo  CAL_CMEXPAPI( "Cifx_ChannelInfo" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelInfo
	#define EXT_Cifx_ChannelInfo
	#define GET_Cifx_ChannelInfo(fl)  CAL_CMGETAPI( "Cifx_ChannelInfo" ) 
	#define CAL_Cifx_ChannelInfo  Cifx_ChannelInfo
	#define CHK_Cifx_ChannelInfo  TRUE
	#define EXP_Cifx_ChannelInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelInfo", (RTS_UINTPTR)Cifx_ChannelInfo, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelInfo
	#define EXT_CmpHilscherCIFXCifx_ChannelInfo
	#define GET_CmpHilscherCIFXCifx_ChannelInfo  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelInfo pICmpHilscherCIFX->ICifx_ChannelInfo
	#define CHK_CmpHilscherCIFXCifx_ChannelInfo (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelInfo  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelInfo
	#define EXT_Cifx_ChannelInfo
	#define GET_Cifx_ChannelInfo(fl)  CAL_CMGETAPI( "Cifx_ChannelInfo" ) 
	#define CAL_Cifx_ChannelInfo pICmpHilscherCIFX->ICifx_ChannelInfo
	#define CHK_Cifx_ChannelInfo (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelInfo  CAL_CMEXPAPI( "Cifx_ChannelInfo" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelInfo  PFCIFX_CHANNELINFO pfCifx_ChannelInfo;
	#define EXT_Cifx_ChannelInfo  extern PFCIFX_CHANNELINFO pfCifx_ChannelInfo;
	#define GET_Cifx_ChannelInfo(fl)  s_pfCMGetAPI2( "Cifx_ChannelInfo", (RTS_VOID_FCTPTR *)&pfCifx_ChannelInfo, (fl), 0, 0)
	#define CAL_Cifx_ChannelInfo  pfCifx_ChannelInfo
	#define CHK_Cifx_ChannelInfo  (pfCifx_ChannelInfo != NULL)
	#define EXP_Cifx_ChannelInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelInfo", (RTS_UINTPTR)Cifx_ChannelInfo, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelIOInfo(RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32 ulArea, RTS_UI32	ulSize, void*	pvData);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELIOINFO) (RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32 ulArea, RTS_UI32	ulSize, void*	pvData);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELIOINFO_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelIOInfo
	#define EXT_Cifx_ChannelIOInfo
	#define GET_Cifx_ChannelIOInfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelIOInfo(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelIOInfo  FALSE
	#define EXP_Cifx_ChannelIOInfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelIOInfo
	#define EXT_Cifx_ChannelIOInfo
	#define GET_Cifx_ChannelIOInfo(fl)  CAL_CMGETAPI( "Cifx_ChannelIOInfo" ) 
	#define CAL_Cifx_ChannelIOInfo  Cifx_ChannelIOInfo
	#define CHK_Cifx_ChannelIOInfo  TRUE
	#define EXP_Cifx_ChannelIOInfo  CAL_CMEXPAPI( "Cifx_ChannelIOInfo" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelIOInfo
	#define EXT_Cifx_ChannelIOInfo
	#define GET_Cifx_ChannelIOInfo(fl)  CAL_CMGETAPI( "Cifx_ChannelIOInfo" ) 
	#define CAL_Cifx_ChannelIOInfo  Cifx_ChannelIOInfo
	#define CHK_Cifx_ChannelIOInfo  TRUE
	#define EXP_Cifx_ChannelIOInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelIOInfo", (RTS_UINTPTR)Cifx_ChannelIOInfo, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelIOInfo
	#define EXT_CmpHilscherCIFXCifx_ChannelIOInfo
	#define GET_CmpHilscherCIFXCifx_ChannelIOInfo  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelIOInfo pICmpHilscherCIFX->ICifx_ChannelIOInfo
	#define CHK_CmpHilscherCIFXCifx_ChannelIOInfo (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelIOInfo  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelIOInfo
	#define EXT_Cifx_ChannelIOInfo
	#define GET_Cifx_ChannelIOInfo(fl)  CAL_CMGETAPI( "Cifx_ChannelIOInfo" ) 
	#define CAL_Cifx_ChannelIOInfo pICmpHilscherCIFX->ICifx_ChannelIOInfo
	#define CHK_Cifx_ChannelIOInfo (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelIOInfo  CAL_CMEXPAPI( "Cifx_ChannelIOInfo" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelIOInfo  PFCIFX_CHANNELIOINFO pfCifx_ChannelIOInfo;
	#define EXT_Cifx_ChannelIOInfo  extern PFCIFX_CHANNELIOINFO pfCifx_ChannelIOInfo;
	#define GET_Cifx_ChannelIOInfo(fl)  s_pfCMGetAPI2( "Cifx_ChannelIOInfo", (RTS_VOID_FCTPTR *)&pfCifx_ChannelIOInfo, (fl), 0, 0)
	#define CAL_Cifx_ChannelIOInfo  pfCifx_ChannelIOInfo
	#define CHK_Cifx_ChannelIOInfo  (pfCifx_ChannelIOInfo != NULL)
	#define EXP_Cifx_ChannelIOInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelIOInfo", (RTS_UINTPTR)Cifx_ChannelIOInfo, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelWatchdog(RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32*	pulTrigger);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELWATCHDOG) (RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32*	pulTrigger);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELWATCHDOG_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelWatchdog
	#define EXT_Cifx_ChannelWatchdog
	#define GET_Cifx_ChannelWatchdog(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelWatchdog(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelWatchdog  FALSE
	#define EXP_Cifx_ChannelWatchdog  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelWatchdog
	#define EXT_Cifx_ChannelWatchdog
	#define GET_Cifx_ChannelWatchdog(fl)  CAL_CMGETAPI( "Cifx_ChannelWatchdog" ) 
	#define CAL_Cifx_ChannelWatchdog  Cifx_ChannelWatchdog
	#define CHK_Cifx_ChannelWatchdog  TRUE
	#define EXP_Cifx_ChannelWatchdog  CAL_CMEXPAPI( "Cifx_ChannelWatchdog" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelWatchdog
	#define EXT_Cifx_ChannelWatchdog
	#define GET_Cifx_ChannelWatchdog(fl)  CAL_CMGETAPI( "Cifx_ChannelWatchdog" ) 
	#define CAL_Cifx_ChannelWatchdog  Cifx_ChannelWatchdog
	#define CHK_Cifx_ChannelWatchdog  TRUE
	#define EXP_Cifx_ChannelWatchdog  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelWatchdog", (RTS_UINTPTR)Cifx_ChannelWatchdog, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelWatchdog
	#define EXT_CmpHilscherCIFXCifx_ChannelWatchdog
	#define GET_CmpHilscherCIFXCifx_ChannelWatchdog  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelWatchdog pICmpHilscherCIFX->ICifx_ChannelWatchdog
	#define CHK_CmpHilscherCIFXCifx_ChannelWatchdog (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelWatchdog  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelWatchdog
	#define EXT_Cifx_ChannelWatchdog
	#define GET_Cifx_ChannelWatchdog(fl)  CAL_CMGETAPI( "Cifx_ChannelWatchdog" ) 
	#define CAL_Cifx_ChannelWatchdog pICmpHilscherCIFX->ICifx_ChannelWatchdog
	#define CHK_Cifx_ChannelWatchdog (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelWatchdog  CAL_CMEXPAPI( "Cifx_ChannelWatchdog" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelWatchdog  PFCIFX_CHANNELWATCHDOG pfCifx_ChannelWatchdog;
	#define EXT_Cifx_ChannelWatchdog  extern PFCIFX_CHANNELWATCHDOG pfCifx_ChannelWatchdog;
	#define GET_Cifx_ChannelWatchdog(fl)  s_pfCMGetAPI2( "Cifx_ChannelWatchdog", (RTS_VOID_FCTPTR *)&pfCifx_ChannelWatchdog, (fl), 0, 0)
	#define CAL_Cifx_ChannelWatchdog  pfCifx_ChannelWatchdog
	#define CHK_Cifx_ChannelWatchdog  (pfCifx_ChannelWatchdog != NULL)
	#define EXP_Cifx_ChannelWatchdog  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelWatchdog", (RTS_UINTPTR)Cifx_ChannelWatchdog, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelHoststate(RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32*	pulState, RTS_UI32	ulTimeout);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELHOSTSTATE) (RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32*	pulState, RTS_UI32	ulTimeout);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELHOSTSTATE_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelHoststate
	#define EXT_Cifx_ChannelHoststate
	#define GET_Cifx_ChannelHoststate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelHoststate(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelHoststate  FALSE
	#define EXP_Cifx_ChannelHoststate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelHoststate
	#define EXT_Cifx_ChannelHoststate
	#define GET_Cifx_ChannelHoststate(fl)  CAL_CMGETAPI( "Cifx_ChannelHoststate" ) 
	#define CAL_Cifx_ChannelHoststate  Cifx_ChannelHoststate
	#define CHK_Cifx_ChannelHoststate  TRUE
	#define EXP_Cifx_ChannelHoststate  CAL_CMEXPAPI( "Cifx_ChannelHoststate" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelHoststate
	#define EXT_Cifx_ChannelHoststate
	#define GET_Cifx_ChannelHoststate(fl)  CAL_CMGETAPI( "Cifx_ChannelHoststate" ) 
	#define CAL_Cifx_ChannelHoststate  Cifx_ChannelHoststate
	#define CHK_Cifx_ChannelHoststate  TRUE
	#define EXP_Cifx_ChannelHoststate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelHoststate", (RTS_UINTPTR)Cifx_ChannelHoststate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelHoststate
	#define EXT_CmpHilscherCIFXCifx_ChannelHoststate
	#define GET_CmpHilscherCIFXCifx_ChannelHoststate  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelHoststate pICmpHilscherCIFX->ICifx_ChannelHoststate
	#define CHK_CmpHilscherCIFXCifx_ChannelHoststate (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelHoststate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelHoststate
	#define EXT_Cifx_ChannelHoststate
	#define GET_Cifx_ChannelHoststate(fl)  CAL_CMGETAPI( "Cifx_ChannelHoststate" ) 
	#define CAL_Cifx_ChannelHoststate pICmpHilscherCIFX->ICifx_ChannelHoststate
	#define CHK_Cifx_ChannelHoststate (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelHoststate  CAL_CMEXPAPI( "Cifx_ChannelHoststate" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelHoststate  PFCIFX_CHANNELHOSTSTATE pfCifx_ChannelHoststate;
	#define EXT_Cifx_ChannelHoststate  extern PFCIFX_CHANNELHOSTSTATE pfCifx_ChannelHoststate;
	#define GET_Cifx_ChannelHoststate(fl)  s_pfCMGetAPI2( "Cifx_ChannelHoststate", (RTS_VOID_FCTPTR *)&pfCifx_ChannelHoststate, (fl), 0, 0)
	#define CAL_Cifx_ChannelHoststate  pfCifx_ChannelHoststate
	#define CHK_Cifx_ChannelHoststate  (pfCifx_ChannelHoststate != NULL)
	#define EXP_Cifx_ChannelHoststate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelHoststate", (RTS_UINTPTR)Cifx_ChannelHoststate, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelBusstate(RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32*	pulState, RTS_UI32	ulTimeout);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELBUSSTATE) (RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32*	pulState, RTS_UI32	ulTimeout);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELBUSSTATE_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelBusstate
	#define EXT_Cifx_ChannelBusstate
	#define GET_Cifx_ChannelBusstate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelBusstate(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelBusstate  FALSE
	#define EXP_Cifx_ChannelBusstate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelBusstate
	#define EXT_Cifx_ChannelBusstate
	#define GET_Cifx_ChannelBusstate(fl)  CAL_CMGETAPI( "Cifx_ChannelBusstate" ) 
	#define CAL_Cifx_ChannelBusstate  Cifx_ChannelBusstate
	#define CHK_Cifx_ChannelBusstate  TRUE
	#define EXP_Cifx_ChannelBusstate  CAL_CMEXPAPI( "Cifx_ChannelBusstate" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelBusstate
	#define EXT_Cifx_ChannelBusstate
	#define GET_Cifx_ChannelBusstate(fl)  CAL_CMGETAPI( "Cifx_ChannelBusstate" ) 
	#define CAL_Cifx_ChannelBusstate  Cifx_ChannelBusstate
	#define CHK_Cifx_ChannelBusstate  TRUE
	#define EXP_Cifx_ChannelBusstate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelBusstate", (RTS_UINTPTR)Cifx_ChannelBusstate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelBusstate
	#define EXT_CmpHilscherCIFXCifx_ChannelBusstate
	#define GET_CmpHilscherCIFXCifx_ChannelBusstate  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelBusstate pICmpHilscherCIFX->ICifx_ChannelBusstate
	#define CHK_CmpHilscherCIFXCifx_ChannelBusstate (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelBusstate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelBusstate
	#define EXT_Cifx_ChannelBusstate
	#define GET_Cifx_ChannelBusstate(fl)  CAL_CMGETAPI( "Cifx_ChannelBusstate" ) 
	#define CAL_Cifx_ChannelBusstate pICmpHilscherCIFX->ICifx_ChannelBusstate
	#define CHK_Cifx_ChannelBusstate (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelBusstate  CAL_CMEXPAPI( "Cifx_ChannelBusstate" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelBusstate  PFCIFX_CHANNELBUSSTATE pfCifx_ChannelBusstate;
	#define EXT_Cifx_ChannelBusstate  extern PFCIFX_CHANNELBUSSTATE pfCifx_ChannelBusstate;
	#define GET_Cifx_ChannelBusstate(fl)  s_pfCMGetAPI2( "Cifx_ChannelBusstate", (RTS_VOID_FCTPTR *)&pfCifx_ChannelBusstate, (fl), 0, 0)
	#define CAL_Cifx_ChannelBusstate  pfCifx_ChannelBusstate
	#define CHK_Cifx_ChannelBusstate  (pfCifx_ChannelBusstate != NULL)
	#define EXP_Cifx_ChannelBusstate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelBusstate", (RTS_UINTPTR)Cifx_ChannelBusstate, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelIORead(RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData, RTS_UI32	ulTimeout);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELIOREAD) (RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData, RTS_UI32	ulTimeout);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELIOREAD_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelIORead
	#define EXT_Cifx_ChannelIORead
	#define GET_Cifx_ChannelIORead(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelIORead(p0,p1,p2,p3,p4,p5)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelIORead  FALSE
	#define EXP_Cifx_ChannelIORead  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelIORead
	#define EXT_Cifx_ChannelIORead
	#define GET_Cifx_ChannelIORead(fl)  CAL_CMGETAPI( "Cifx_ChannelIORead" ) 
	#define CAL_Cifx_ChannelIORead  Cifx_ChannelIORead
	#define CHK_Cifx_ChannelIORead  TRUE
	#define EXP_Cifx_ChannelIORead  CAL_CMEXPAPI( "Cifx_ChannelIORead" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelIORead
	#define EXT_Cifx_ChannelIORead
	#define GET_Cifx_ChannelIORead(fl)  CAL_CMGETAPI( "Cifx_ChannelIORead" ) 
	#define CAL_Cifx_ChannelIORead  Cifx_ChannelIORead
	#define CHK_Cifx_ChannelIORead  TRUE
	#define EXP_Cifx_ChannelIORead  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelIORead", (RTS_UINTPTR)Cifx_ChannelIORead, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelIORead
	#define EXT_CmpHilscherCIFXCifx_ChannelIORead
	#define GET_CmpHilscherCIFXCifx_ChannelIORead  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelIORead pICmpHilscherCIFX->ICifx_ChannelIORead
	#define CHK_CmpHilscherCIFXCifx_ChannelIORead (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelIORead  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelIORead
	#define EXT_Cifx_ChannelIORead
	#define GET_Cifx_ChannelIORead(fl)  CAL_CMGETAPI( "Cifx_ChannelIORead" ) 
	#define CAL_Cifx_ChannelIORead pICmpHilscherCIFX->ICifx_ChannelIORead
	#define CHK_Cifx_ChannelIORead (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelIORead  CAL_CMEXPAPI( "Cifx_ChannelIORead" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelIORead  PFCIFX_CHANNELIOREAD pfCifx_ChannelIORead;
	#define EXT_Cifx_ChannelIORead  extern PFCIFX_CHANNELIOREAD pfCifx_ChannelIORead;
	#define GET_Cifx_ChannelIORead(fl)  s_pfCMGetAPI2( "Cifx_ChannelIORead", (RTS_VOID_FCTPTR *)&pfCifx_ChannelIORead, (fl), 0, 0)
	#define CAL_Cifx_ChannelIORead  pfCifx_ChannelIORead
	#define CHK_Cifx_ChannelIORead  (pfCifx_ChannelIORead != NULL)
	#define EXP_Cifx_ChannelIORead  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelIORead", (RTS_UINTPTR)Cifx_ChannelIORead, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelIOWrite(	RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData, RTS_UI32	ulTimeout);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELIOWRITE) (	RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData, RTS_UI32	ulTimeout);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELIOWRITE_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelIOWrite
	#define EXT_Cifx_ChannelIOWrite
	#define GET_Cifx_ChannelIOWrite(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelIOWrite(p0,p1,p2,p3,p4,p5)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelIOWrite  FALSE
	#define EXP_Cifx_ChannelIOWrite  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelIOWrite
	#define EXT_Cifx_ChannelIOWrite
	#define GET_Cifx_ChannelIOWrite(fl)  CAL_CMGETAPI( "Cifx_ChannelIOWrite" ) 
	#define CAL_Cifx_ChannelIOWrite  Cifx_ChannelIOWrite
	#define CHK_Cifx_ChannelIOWrite  TRUE
	#define EXP_Cifx_ChannelIOWrite  CAL_CMEXPAPI( "Cifx_ChannelIOWrite" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelIOWrite
	#define EXT_Cifx_ChannelIOWrite
	#define GET_Cifx_ChannelIOWrite(fl)  CAL_CMGETAPI( "Cifx_ChannelIOWrite" ) 
	#define CAL_Cifx_ChannelIOWrite  Cifx_ChannelIOWrite
	#define CHK_Cifx_ChannelIOWrite  TRUE
	#define EXP_Cifx_ChannelIOWrite  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelIOWrite", (RTS_UINTPTR)Cifx_ChannelIOWrite, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelIOWrite
	#define EXT_CmpHilscherCIFXCifx_ChannelIOWrite
	#define GET_CmpHilscherCIFXCifx_ChannelIOWrite  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelIOWrite pICmpHilscherCIFX->ICifx_ChannelIOWrite
	#define CHK_CmpHilscherCIFXCifx_ChannelIOWrite (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelIOWrite  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelIOWrite
	#define EXT_Cifx_ChannelIOWrite
	#define GET_Cifx_ChannelIOWrite(fl)  CAL_CMGETAPI( "Cifx_ChannelIOWrite" ) 
	#define CAL_Cifx_ChannelIOWrite pICmpHilscherCIFX->ICifx_ChannelIOWrite
	#define CHK_Cifx_ChannelIOWrite (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelIOWrite  CAL_CMEXPAPI( "Cifx_ChannelIOWrite" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelIOWrite  PFCIFX_CHANNELIOWRITE pfCifx_ChannelIOWrite;
	#define EXT_Cifx_ChannelIOWrite  extern PFCIFX_CHANNELIOWRITE pfCifx_ChannelIOWrite;
	#define GET_Cifx_ChannelIOWrite(fl)  s_pfCMGetAPI2( "Cifx_ChannelIOWrite", (RTS_VOID_FCTPTR *)&pfCifx_ChannelIOWrite, (fl), 0, 0)
	#define CAL_Cifx_ChannelIOWrite  pfCifx_ChannelIOWrite
	#define CHK_Cifx_ChannelIOWrite  (pfCifx_ChannelIOWrite != NULL)
	#define EXP_Cifx_ChannelIOWrite  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelIOWrite", (RTS_UINTPTR)Cifx_ChannelIOWrite, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelIOReadSendData(RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELIOREADSENDDATA) (RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELIOREADSENDDATA_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelIOReadSendData
	#define EXT_Cifx_ChannelIOReadSendData
	#define GET_Cifx_ChannelIOReadSendData(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelIOReadSendData(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelIOReadSendData  FALSE
	#define EXP_Cifx_ChannelIOReadSendData  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelIOReadSendData
	#define EXT_Cifx_ChannelIOReadSendData
	#define GET_Cifx_ChannelIOReadSendData(fl)  CAL_CMGETAPI( "Cifx_ChannelIOReadSendData" ) 
	#define CAL_Cifx_ChannelIOReadSendData  Cifx_ChannelIOReadSendData
	#define CHK_Cifx_ChannelIOReadSendData  TRUE
	#define EXP_Cifx_ChannelIOReadSendData  CAL_CMEXPAPI( "Cifx_ChannelIOReadSendData" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelIOReadSendData
	#define EXT_Cifx_ChannelIOReadSendData
	#define GET_Cifx_ChannelIOReadSendData(fl)  CAL_CMGETAPI( "Cifx_ChannelIOReadSendData" ) 
	#define CAL_Cifx_ChannelIOReadSendData  Cifx_ChannelIOReadSendData
	#define CHK_Cifx_ChannelIOReadSendData  TRUE
	#define EXP_Cifx_ChannelIOReadSendData  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelIOReadSendData", (RTS_UINTPTR)Cifx_ChannelIOReadSendData, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelIOReadSendData
	#define EXT_CmpHilscherCIFXCifx_ChannelIOReadSendData
	#define GET_CmpHilscherCIFXCifx_ChannelIOReadSendData  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelIOReadSendData pICmpHilscherCIFX->ICifx_ChannelIOReadSendData
	#define CHK_CmpHilscherCIFXCifx_ChannelIOReadSendData (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelIOReadSendData  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelIOReadSendData
	#define EXT_Cifx_ChannelIOReadSendData
	#define GET_Cifx_ChannelIOReadSendData(fl)  CAL_CMGETAPI( "Cifx_ChannelIOReadSendData" ) 
	#define CAL_Cifx_ChannelIOReadSendData pICmpHilscherCIFX->ICifx_ChannelIOReadSendData
	#define CHK_Cifx_ChannelIOReadSendData (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelIOReadSendData  CAL_CMEXPAPI( "Cifx_ChannelIOReadSendData" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelIOReadSendData  PFCIFX_CHANNELIOREADSENDDATA pfCifx_ChannelIOReadSendData;
	#define EXT_Cifx_ChannelIOReadSendData  extern PFCIFX_CHANNELIOREADSENDDATA pfCifx_ChannelIOReadSendData;
	#define GET_Cifx_ChannelIOReadSendData(fl)  s_pfCMGetAPI2( "Cifx_ChannelIOReadSendData", (RTS_VOID_FCTPTR *)&pfCifx_ChannelIOReadSendData, (fl), 0, 0)
	#define CAL_Cifx_ChannelIOReadSendData  pfCifx_ChannelIOReadSendData
	#define CHK_Cifx_ChannelIOReadSendData  (pfCifx_ChannelIOReadSendData != NULL)
	#define EXP_Cifx_ChannelIOReadSendData  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelIOReadSendData", (RTS_UINTPTR)Cifx_ChannelIOReadSendData, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelControlBlock(RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELCONTROLBLOCK) (RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELCONTROLBLOCK_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelControlBlock
	#define EXT_Cifx_ChannelControlBlock
	#define GET_Cifx_ChannelControlBlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelControlBlock(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelControlBlock  FALSE
	#define EXP_Cifx_ChannelControlBlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelControlBlock
	#define EXT_Cifx_ChannelControlBlock
	#define GET_Cifx_ChannelControlBlock(fl)  CAL_CMGETAPI( "Cifx_ChannelControlBlock" ) 
	#define CAL_Cifx_ChannelControlBlock  Cifx_ChannelControlBlock
	#define CHK_Cifx_ChannelControlBlock  TRUE
	#define EXP_Cifx_ChannelControlBlock  CAL_CMEXPAPI( "Cifx_ChannelControlBlock" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelControlBlock
	#define EXT_Cifx_ChannelControlBlock
	#define GET_Cifx_ChannelControlBlock(fl)  CAL_CMGETAPI( "Cifx_ChannelControlBlock" ) 
	#define CAL_Cifx_ChannelControlBlock  Cifx_ChannelControlBlock
	#define CHK_Cifx_ChannelControlBlock  TRUE
	#define EXP_Cifx_ChannelControlBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelControlBlock", (RTS_UINTPTR)Cifx_ChannelControlBlock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelControlBlock
	#define EXT_CmpHilscherCIFXCifx_ChannelControlBlock
	#define GET_CmpHilscherCIFXCifx_ChannelControlBlock  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelControlBlock pICmpHilscherCIFX->ICifx_ChannelControlBlock
	#define CHK_CmpHilscherCIFXCifx_ChannelControlBlock (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelControlBlock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelControlBlock
	#define EXT_Cifx_ChannelControlBlock
	#define GET_Cifx_ChannelControlBlock(fl)  CAL_CMGETAPI( "Cifx_ChannelControlBlock" ) 
	#define CAL_Cifx_ChannelControlBlock pICmpHilscherCIFX->ICifx_ChannelControlBlock
	#define CHK_Cifx_ChannelControlBlock (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelControlBlock  CAL_CMEXPAPI( "Cifx_ChannelControlBlock" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelControlBlock  PFCIFX_CHANNELCONTROLBLOCK pfCifx_ChannelControlBlock;
	#define EXT_Cifx_ChannelControlBlock  extern PFCIFX_CHANNELCONTROLBLOCK pfCifx_ChannelControlBlock;
	#define GET_Cifx_ChannelControlBlock(fl)  s_pfCMGetAPI2( "Cifx_ChannelControlBlock", (RTS_VOID_FCTPTR *)&pfCifx_ChannelControlBlock, (fl), 0, 0)
	#define CAL_Cifx_ChannelControlBlock  pfCifx_ChannelControlBlock
	#define CHK_Cifx_ChannelControlBlock  (pfCifx_ChannelControlBlock != NULL)
	#define EXP_Cifx_ChannelControlBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelControlBlock", (RTS_UINTPTR)Cifx_ChannelControlBlock, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelCommonStatusBlock(RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELCOMMONSTATUSBLOCK) (RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELCOMMONSTATUSBLOCK_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelCommonStatusBlock
	#define EXT_Cifx_ChannelCommonStatusBlock
	#define GET_Cifx_ChannelCommonStatusBlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelCommonStatusBlock(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelCommonStatusBlock  FALSE
	#define EXP_Cifx_ChannelCommonStatusBlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelCommonStatusBlock
	#define EXT_Cifx_ChannelCommonStatusBlock
	#define GET_Cifx_ChannelCommonStatusBlock(fl)  CAL_CMGETAPI( "Cifx_ChannelCommonStatusBlock" ) 
	#define CAL_Cifx_ChannelCommonStatusBlock  Cifx_ChannelCommonStatusBlock
	#define CHK_Cifx_ChannelCommonStatusBlock  TRUE
	#define EXP_Cifx_ChannelCommonStatusBlock  CAL_CMEXPAPI( "Cifx_ChannelCommonStatusBlock" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelCommonStatusBlock
	#define EXT_Cifx_ChannelCommonStatusBlock
	#define GET_Cifx_ChannelCommonStatusBlock(fl)  CAL_CMGETAPI( "Cifx_ChannelCommonStatusBlock" ) 
	#define CAL_Cifx_ChannelCommonStatusBlock  Cifx_ChannelCommonStatusBlock
	#define CHK_Cifx_ChannelCommonStatusBlock  TRUE
	#define EXP_Cifx_ChannelCommonStatusBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelCommonStatusBlock", (RTS_UINTPTR)Cifx_ChannelCommonStatusBlock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelCommonStatusBlock
	#define EXT_CmpHilscherCIFXCifx_ChannelCommonStatusBlock
	#define GET_CmpHilscherCIFXCifx_ChannelCommonStatusBlock  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelCommonStatusBlock pICmpHilscherCIFX->ICifx_ChannelCommonStatusBlock
	#define CHK_CmpHilscherCIFXCifx_ChannelCommonStatusBlock (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelCommonStatusBlock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelCommonStatusBlock
	#define EXT_Cifx_ChannelCommonStatusBlock
	#define GET_Cifx_ChannelCommonStatusBlock(fl)  CAL_CMGETAPI( "Cifx_ChannelCommonStatusBlock" ) 
	#define CAL_Cifx_ChannelCommonStatusBlock pICmpHilscherCIFX->ICifx_ChannelCommonStatusBlock
	#define CHK_Cifx_ChannelCommonStatusBlock (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelCommonStatusBlock  CAL_CMEXPAPI( "Cifx_ChannelCommonStatusBlock" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelCommonStatusBlock  PFCIFX_CHANNELCOMMONSTATUSBLOCK pfCifx_ChannelCommonStatusBlock;
	#define EXT_Cifx_ChannelCommonStatusBlock  extern PFCIFX_CHANNELCOMMONSTATUSBLOCK pfCifx_ChannelCommonStatusBlock;
	#define GET_Cifx_ChannelCommonStatusBlock(fl)  s_pfCMGetAPI2( "Cifx_ChannelCommonStatusBlock", (RTS_VOID_FCTPTR *)&pfCifx_ChannelCommonStatusBlock, (fl), 0, 0)
	#define CAL_Cifx_ChannelCommonStatusBlock  pfCifx_ChannelCommonStatusBlock
	#define CHK_Cifx_ChannelCommonStatusBlock  (pfCifx_ChannelCommonStatusBlock != NULL)
	#define EXP_Cifx_ChannelCommonStatusBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelCommonStatusBlock", (RTS_UINTPTR)Cifx_ChannelCommonStatusBlock, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelExtendedStatusBlock(	RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELEXTENDEDSTATUSBLOCK) (	RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELEXTENDEDSTATUSBLOCK_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelExtendedStatusBlock
	#define EXT_Cifx_ChannelExtendedStatusBlock
	#define GET_Cifx_ChannelExtendedStatusBlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelExtendedStatusBlock(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelExtendedStatusBlock  FALSE
	#define EXP_Cifx_ChannelExtendedStatusBlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelExtendedStatusBlock
	#define EXT_Cifx_ChannelExtendedStatusBlock
	#define GET_Cifx_ChannelExtendedStatusBlock(fl)  CAL_CMGETAPI( "Cifx_ChannelExtendedStatusBlock" ) 
	#define CAL_Cifx_ChannelExtendedStatusBlock  Cifx_ChannelExtendedStatusBlock
	#define CHK_Cifx_ChannelExtendedStatusBlock  TRUE
	#define EXP_Cifx_ChannelExtendedStatusBlock  CAL_CMEXPAPI( "Cifx_ChannelExtendedStatusBlock" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelExtendedStatusBlock
	#define EXT_Cifx_ChannelExtendedStatusBlock
	#define GET_Cifx_ChannelExtendedStatusBlock(fl)  CAL_CMGETAPI( "Cifx_ChannelExtendedStatusBlock" ) 
	#define CAL_Cifx_ChannelExtendedStatusBlock  Cifx_ChannelExtendedStatusBlock
	#define CHK_Cifx_ChannelExtendedStatusBlock  TRUE
	#define EXP_Cifx_ChannelExtendedStatusBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelExtendedStatusBlock", (RTS_UINTPTR)Cifx_ChannelExtendedStatusBlock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelExtendedStatusBlock
	#define EXT_CmpHilscherCIFXCifx_ChannelExtendedStatusBlock
	#define GET_CmpHilscherCIFXCifx_ChannelExtendedStatusBlock  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelExtendedStatusBlock pICmpHilscherCIFX->ICifx_ChannelExtendedStatusBlock
	#define CHK_CmpHilscherCIFXCifx_ChannelExtendedStatusBlock (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelExtendedStatusBlock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelExtendedStatusBlock
	#define EXT_Cifx_ChannelExtendedStatusBlock
	#define GET_Cifx_ChannelExtendedStatusBlock(fl)  CAL_CMGETAPI( "Cifx_ChannelExtendedStatusBlock" ) 
	#define CAL_Cifx_ChannelExtendedStatusBlock pICmpHilscherCIFX->ICifx_ChannelExtendedStatusBlock
	#define CHK_Cifx_ChannelExtendedStatusBlock (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelExtendedStatusBlock  CAL_CMEXPAPI( "Cifx_ChannelExtendedStatusBlock" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelExtendedStatusBlock  PFCIFX_CHANNELEXTENDEDSTATUSBLOCK pfCifx_ChannelExtendedStatusBlock;
	#define EXT_Cifx_ChannelExtendedStatusBlock  extern PFCIFX_CHANNELEXTENDEDSTATUSBLOCK pfCifx_ChannelExtendedStatusBlock;
	#define GET_Cifx_ChannelExtendedStatusBlock(fl)  s_pfCMGetAPI2( "Cifx_ChannelExtendedStatusBlock", (RTS_VOID_FCTPTR *)&pfCifx_ChannelExtendedStatusBlock, (fl), 0, 0)
	#define CAL_Cifx_ChannelExtendedStatusBlock  pfCifx_ChannelExtendedStatusBlock
	#define CHK_Cifx_ChannelExtendedStatusBlock  (pfCifx_ChannelExtendedStatusBlock != NULL)
	#define EXP_Cifx_ChannelExtendedStatusBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelExtendedStatusBlock", (RTS_UINTPTR)Cifx_ChannelExtendedStatusBlock, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelUserBlock(RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber, RTS_UI32	ulCmd, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELUSERBLOCK) (RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber, RTS_UI32	ulCmd, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELUSERBLOCK_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelUserBlock
	#define EXT_Cifx_ChannelUserBlock
	#define GET_Cifx_ChannelUserBlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelUserBlock(p0,p1,p2,p3,p4,p5)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelUserBlock  FALSE
	#define EXP_Cifx_ChannelUserBlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelUserBlock
	#define EXT_Cifx_ChannelUserBlock
	#define GET_Cifx_ChannelUserBlock(fl)  CAL_CMGETAPI( "Cifx_ChannelUserBlock" ) 
	#define CAL_Cifx_ChannelUserBlock  Cifx_ChannelUserBlock
	#define CHK_Cifx_ChannelUserBlock  TRUE
	#define EXP_Cifx_ChannelUserBlock  CAL_CMEXPAPI( "Cifx_ChannelUserBlock" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelUserBlock
	#define EXT_Cifx_ChannelUserBlock
	#define GET_Cifx_ChannelUserBlock(fl)  CAL_CMGETAPI( "Cifx_ChannelUserBlock" ) 
	#define CAL_Cifx_ChannelUserBlock  Cifx_ChannelUserBlock
	#define CHK_Cifx_ChannelUserBlock  TRUE
	#define EXP_Cifx_ChannelUserBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelUserBlock", (RTS_UINTPTR)Cifx_ChannelUserBlock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelUserBlock
	#define EXT_CmpHilscherCIFXCifx_ChannelUserBlock
	#define GET_CmpHilscherCIFXCifx_ChannelUserBlock  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelUserBlock pICmpHilscherCIFX->ICifx_ChannelUserBlock
	#define CHK_CmpHilscherCIFXCifx_ChannelUserBlock (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelUserBlock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelUserBlock
	#define EXT_Cifx_ChannelUserBlock
	#define GET_Cifx_ChannelUserBlock(fl)  CAL_CMGETAPI( "Cifx_ChannelUserBlock" ) 
	#define CAL_Cifx_ChannelUserBlock pICmpHilscherCIFX->ICifx_ChannelUserBlock
	#define CHK_Cifx_ChannelUserBlock (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelUserBlock  CAL_CMEXPAPI( "Cifx_ChannelUserBlock" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelUserBlock  PFCIFX_CHANNELUSERBLOCK pfCifx_ChannelUserBlock;
	#define EXT_Cifx_ChannelUserBlock  extern PFCIFX_CHANNELUSERBLOCK pfCifx_ChannelUserBlock;
	#define GET_Cifx_ChannelUserBlock(fl)  s_pfCMGetAPI2( "Cifx_ChannelUserBlock", (RTS_VOID_FCTPTR *)&pfCifx_ChannelUserBlock, (fl), 0, 0)
	#define CAL_Cifx_ChannelUserBlock  pfCifx_ChannelUserBlock
	#define CHK_Cifx_ChannelUserBlock  (pfCifx_ChannelUserBlock != NULL)
	#define EXP_Cifx_ChannelUserBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelUserBlock", (RTS_UINTPTR)Cifx_ChannelUserBlock, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelPLCMemoryPtr(RTS_HANDLE hChannel,	RTS_UI32	ulCmd, void* pvMemoryInfo);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELPLCMEMORYPTR) (RTS_HANDLE hChannel,	RTS_UI32	ulCmd, void* pvMemoryInfo);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELPLCMEMORYPTR_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelPLCMemoryPtr
	#define EXT_Cifx_ChannelPLCMemoryPtr
	#define GET_Cifx_ChannelPLCMemoryPtr(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelPLCMemoryPtr(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelPLCMemoryPtr  FALSE
	#define EXP_Cifx_ChannelPLCMemoryPtr  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelPLCMemoryPtr
	#define EXT_Cifx_ChannelPLCMemoryPtr
	#define GET_Cifx_ChannelPLCMemoryPtr(fl)  CAL_CMGETAPI( "Cifx_ChannelPLCMemoryPtr" ) 
	#define CAL_Cifx_ChannelPLCMemoryPtr  Cifx_ChannelPLCMemoryPtr
	#define CHK_Cifx_ChannelPLCMemoryPtr  TRUE
	#define EXP_Cifx_ChannelPLCMemoryPtr  CAL_CMEXPAPI( "Cifx_ChannelPLCMemoryPtr" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelPLCMemoryPtr
	#define EXT_Cifx_ChannelPLCMemoryPtr
	#define GET_Cifx_ChannelPLCMemoryPtr(fl)  CAL_CMGETAPI( "Cifx_ChannelPLCMemoryPtr" ) 
	#define CAL_Cifx_ChannelPLCMemoryPtr  Cifx_ChannelPLCMemoryPtr
	#define CHK_Cifx_ChannelPLCMemoryPtr  TRUE
	#define EXP_Cifx_ChannelPLCMemoryPtr  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelPLCMemoryPtr", (RTS_UINTPTR)Cifx_ChannelPLCMemoryPtr, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelPLCMemoryPtr
	#define EXT_CmpHilscherCIFXCifx_ChannelPLCMemoryPtr
	#define GET_CmpHilscherCIFXCifx_ChannelPLCMemoryPtr  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelPLCMemoryPtr pICmpHilscherCIFX->ICifx_ChannelPLCMemoryPtr
	#define CHK_CmpHilscherCIFXCifx_ChannelPLCMemoryPtr (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelPLCMemoryPtr  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelPLCMemoryPtr
	#define EXT_Cifx_ChannelPLCMemoryPtr
	#define GET_Cifx_ChannelPLCMemoryPtr(fl)  CAL_CMGETAPI( "Cifx_ChannelPLCMemoryPtr" ) 
	#define CAL_Cifx_ChannelPLCMemoryPtr pICmpHilscherCIFX->ICifx_ChannelPLCMemoryPtr
	#define CHK_Cifx_ChannelPLCMemoryPtr (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelPLCMemoryPtr  CAL_CMEXPAPI( "Cifx_ChannelPLCMemoryPtr" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelPLCMemoryPtr  PFCIFX_CHANNELPLCMEMORYPTR pfCifx_ChannelPLCMemoryPtr;
	#define EXT_Cifx_ChannelPLCMemoryPtr  extern PFCIFX_CHANNELPLCMEMORYPTR pfCifx_ChannelPLCMemoryPtr;
	#define GET_Cifx_ChannelPLCMemoryPtr(fl)  s_pfCMGetAPI2( "Cifx_ChannelPLCMemoryPtr", (RTS_VOID_FCTPTR *)&pfCifx_ChannelPLCMemoryPtr, (fl), 0, 0)
	#define CAL_Cifx_ChannelPLCMemoryPtr  pfCifx_ChannelPLCMemoryPtr
	#define CHK_Cifx_ChannelPLCMemoryPtr  (pfCifx_ChannelPLCMemoryPtr != NULL)
	#define EXP_Cifx_ChannelPLCMemoryPtr  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelPLCMemoryPtr", (RTS_UINTPTR)Cifx_ChannelPLCMemoryPtr, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelPLCIsReadReady(RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber, RTS_UI32*	pulReadState);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELPLCISREADREADY) (RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber, RTS_UI32*	pulReadState);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELPLCISREADREADY_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelPLCIsReadReady
	#define EXT_Cifx_ChannelPLCIsReadReady
	#define GET_Cifx_ChannelPLCIsReadReady(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelPLCIsReadReady(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelPLCIsReadReady  FALSE
	#define EXP_Cifx_ChannelPLCIsReadReady  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelPLCIsReadReady
	#define EXT_Cifx_ChannelPLCIsReadReady
	#define GET_Cifx_ChannelPLCIsReadReady(fl)  CAL_CMGETAPI( "Cifx_ChannelPLCIsReadReady" ) 
	#define CAL_Cifx_ChannelPLCIsReadReady  Cifx_ChannelPLCIsReadReady
	#define CHK_Cifx_ChannelPLCIsReadReady  TRUE
	#define EXP_Cifx_ChannelPLCIsReadReady  CAL_CMEXPAPI( "Cifx_ChannelPLCIsReadReady" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelPLCIsReadReady
	#define EXT_Cifx_ChannelPLCIsReadReady
	#define GET_Cifx_ChannelPLCIsReadReady(fl)  CAL_CMGETAPI( "Cifx_ChannelPLCIsReadReady" ) 
	#define CAL_Cifx_ChannelPLCIsReadReady  Cifx_ChannelPLCIsReadReady
	#define CHK_Cifx_ChannelPLCIsReadReady  TRUE
	#define EXP_Cifx_ChannelPLCIsReadReady  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelPLCIsReadReady", (RTS_UINTPTR)Cifx_ChannelPLCIsReadReady, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelPLCIsReadReady
	#define EXT_CmpHilscherCIFXCifx_ChannelPLCIsReadReady
	#define GET_CmpHilscherCIFXCifx_ChannelPLCIsReadReady  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelPLCIsReadReady pICmpHilscherCIFX->ICifx_ChannelPLCIsReadReady
	#define CHK_CmpHilscherCIFXCifx_ChannelPLCIsReadReady (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelPLCIsReadReady  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelPLCIsReadReady
	#define EXT_Cifx_ChannelPLCIsReadReady
	#define GET_Cifx_ChannelPLCIsReadReady(fl)  CAL_CMGETAPI( "Cifx_ChannelPLCIsReadReady" ) 
	#define CAL_Cifx_ChannelPLCIsReadReady pICmpHilscherCIFX->ICifx_ChannelPLCIsReadReady
	#define CHK_Cifx_ChannelPLCIsReadReady (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelPLCIsReadReady  CAL_CMEXPAPI( "Cifx_ChannelPLCIsReadReady" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelPLCIsReadReady  PFCIFX_CHANNELPLCISREADREADY pfCifx_ChannelPLCIsReadReady;
	#define EXT_Cifx_ChannelPLCIsReadReady  extern PFCIFX_CHANNELPLCISREADREADY pfCifx_ChannelPLCIsReadReady;
	#define GET_Cifx_ChannelPLCIsReadReady(fl)  s_pfCMGetAPI2( "Cifx_ChannelPLCIsReadReady", (RTS_VOID_FCTPTR *)&pfCifx_ChannelPLCIsReadReady, (fl), 0, 0)
	#define CAL_Cifx_ChannelPLCIsReadReady  pfCifx_ChannelPLCIsReadReady
	#define CHK_Cifx_ChannelPLCIsReadReady  (pfCifx_ChannelPLCIsReadReady != NULL)
	#define EXP_Cifx_ChannelPLCIsReadReady  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelPLCIsReadReady", (RTS_UINTPTR)Cifx_ChannelPLCIsReadReady, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelPLCIsWriteReady(	RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber, RTS_UI32*	pulWriteState);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELPLCISWRITEREADY) (	RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber, RTS_UI32*	pulWriteState);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELPLCISWRITEREADY_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelPLCIsWriteReady
	#define EXT_Cifx_ChannelPLCIsWriteReady
	#define GET_Cifx_ChannelPLCIsWriteReady(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelPLCIsWriteReady(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelPLCIsWriteReady  FALSE
	#define EXP_Cifx_ChannelPLCIsWriteReady  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelPLCIsWriteReady
	#define EXT_Cifx_ChannelPLCIsWriteReady
	#define GET_Cifx_ChannelPLCIsWriteReady(fl)  CAL_CMGETAPI( "Cifx_ChannelPLCIsWriteReady" ) 
	#define CAL_Cifx_ChannelPLCIsWriteReady  Cifx_ChannelPLCIsWriteReady
	#define CHK_Cifx_ChannelPLCIsWriteReady  TRUE
	#define EXP_Cifx_ChannelPLCIsWriteReady  CAL_CMEXPAPI( "Cifx_ChannelPLCIsWriteReady" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelPLCIsWriteReady
	#define EXT_Cifx_ChannelPLCIsWriteReady
	#define GET_Cifx_ChannelPLCIsWriteReady(fl)  CAL_CMGETAPI( "Cifx_ChannelPLCIsWriteReady" ) 
	#define CAL_Cifx_ChannelPLCIsWriteReady  Cifx_ChannelPLCIsWriteReady
	#define CHK_Cifx_ChannelPLCIsWriteReady  TRUE
	#define EXP_Cifx_ChannelPLCIsWriteReady  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelPLCIsWriteReady", (RTS_UINTPTR)Cifx_ChannelPLCIsWriteReady, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelPLCIsWriteReady
	#define EXT_CmpHilscherCIFXCifx_ChannelPLCIsWriteReady
	#define GET_CmpHilscherCIFXCifx_ChannelPLCIsWriteReady  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelPLCIsWriteReady pICmpHilscherCIFX->ICifx_ChannelPLCIsWriteReady
	#define CHK_CmpHilscherCIFXCifx_ChannelPLCIsWriteReady (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelPLCIsWriteReady  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelPLCIsWriteReady
	#define EXT_Cifx_ChannelPLCIsWriteReady
	#define GET_Cifx_ChannelPLCIsWriteReady(fl)  CAL_CMGETAPI( "Cifx_ChannelPLCIsWriteReady" ) 
	#define CAL_Cifx_ChannelPLCIsWriteReady pICmpHilscherCIFX->ICifx_ChannelPLCIsWriteReady
	#define CHK_Cifx_ChannelPLCIsWriteReady (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelPLCIsWriteReady  CAL_CMEXPAPI( "Cifx_ChannelPLCIsWriteReady" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelPLCIsWriteReady  PFCIFX_CHANNELPLCISWRITEREADY pfCifx_ChannelPLCIsWriteReady;
	#define EXT_Cifx_ChannelPLCIsWriteReady  extern PFCIFX_CHANNELPLCISWRITEREADY pfCifx_ChannelPLCIsWriteReady;
	#define GET_Cifx_ChannelPLCIsWriteReady(fl)  s_pfCMGetAPI2( "Cifx_ChannelPLCIsWriteReady", (RTS_VOID_FCTPTR *)&pfCifx_ChannelPLCIsWriteReady, (fl), 0, 0)
	#define CAL_Cifx_ChannelPLCIsWriteReady  pfCifx_ChannelPLCIsWriteReady
	#define CHK_Cifx_ChannelPLCIsWriteReady  (pfCifx_ChannelPLCIsWriteReady != NULL)
	#define EXP_Cifx_ChannelPLCIsWriteReady  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelPLCIsWriteReady", (RTS_UINTPTR)Cifx_ChannelPLCIsWriteReady, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelPLCActivateWrite(RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELPLCACTIVATEWRITE) (RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELPLCACTIVATEWRITE_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelPLCActivateWrite
	#define EXT_Cifx_ChannelPLCActivateWrite
	#define GET_Cifx_ChannelPLCActivateWrite(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelPLCActivateWrite(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelPLCActivateWrite  FALSE
	#define EXP_Cifx_ChannelPLCActivateWrite  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelPLCActivateWrite
	#define EXT_Cifx_ChannelPLCActivateWrite
	#define GET_Cifx_ChannelPLCActivateWrite(fl)  CAL_CMGETAPI( "Cifx_ChannelPLCActivateWrite" ) 
	#define CAL_Cifx_ChannelPLCActivateWrite  Cifx_ChannelPLCActivateWrite
	#define CHK_Cifx_ChannelPLCActivateWrite  TRUE
	#define EXP_Cifx_ChannelPLCActivateWrite  CAL_CMEXPAPI( "Cifx_ChannelPLCActivateWrite" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelPLCActivateWrite
	#define EXT_Cifx_ChannelPLCActivateWrite
	#define GET_Cifx_ChannelPLCActivateWrite(fl)  CAL_CMGETAPI( "Cifx_ChannelPLCActivateWrite" ) 
	#define CAL_Cifx_ChannelPLCActivateWrite  Cifx_ChannelPLCActivateWrite
	#define CHK_Cifx_ChannelPLCActivateWrite  TRUE
	#define EXP_Cifx_ChannelPLCActivateWrite  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelPLCActivateWrite", (RTS_UINTPTR)Cifx_ChannelPLCActivateWrite, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelPLCActivateWrite
	#define EXT_CmpHilscherCIFXCifx_ChannelPLCActivateWrite
	#define GET_CmpHilscherCIFXCifx_ChannelPLCActivateWrite  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelPLCActivateWrite pICmpHilscherCIFX->ICifx_ChannelPLCActivateWrite
	#define CHK_CmpHilscherCIFXCifx_ChannelPLCActivateWrite (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelPLCActivateWrite  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelPLCActivateWrite
	#define EXT_Cifx_ChannelPLCActivateWrite
	#define GET_Cifx_ChannelPLCActivateWrite(fl)  CAL_CMGETAPI( "Cifx_ChannelPLCActivateWrite" ) 
	#define CAL_Cifx_ChannelPLCActivateWrite pICmpHilscherCIFX->ICifx_ChannelPLCActivateWrite
	#define CHK_Cifx_ChannelPLCActivateWrite (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelPLCActivateWrite  CAL_CMEXPAPI( "Cifx_ChannelPLCActivateWrite" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelPLCActivateWrite  PFCIFX_CHANNELPLCACTIVATEWRITE pfCifx_ChannelPLCActivateWrite;
	#define EXT_Cifx_ChannelPLCActivateWrite  extern PFCIFX_CHANNELPLCACTIVATEWRITE pfCifx_ChannelPLCActivateWrite;
	#define GET_Cifx_ChannelPLCActivateWrite(fl)  s_pfCMGetAPI2( "Cifx_ChannelPLCActivateWrite", (RTS_VOID_FCTPTR *)&pfCifx_ChannelPLCActivateWrite, (fl), 0, 0)
	#define CAL_Cifx_ChannelPLCActivateWrite  pfCifx_ChannelPLCActivateWrite
	#define CHK_Cifx_ChannelPLCActivateWrite  (pfCifx_ChannelPLCActivateWrite != NULL)
	#define EXP_Cifx_ChannelPLCActivateWrite  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelPLCActivateWrite", (RTS_UINTPTR)Cifx_ChannelPLCActivateWrite, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelPLCActivateRead(RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELPLCACTIVATEREAD) (RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELPLCACTIVATEREAD_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelPLCActivateRead
	#define EXT_Cifx_ChannelPLCActivateRead
	#define GET_Cifx_ChannelPLCActivateRead(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelPLCActivateRead(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelPLCActivateRead  FALSE
	#define EXP_Cifx_ChannelPLCActivateRead  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelPLCActivateRead
	#define EXT_Cifx_ChannelPLCActivateRead
	#define GET_Cifx_ChannelPLCActivateRead(fl)  CAL_CMGETAPI( "Cifx_ChannelPLCActivateRead" ) 
	#define CAL_Cifx_ChannelPLCActivateRead  Cifx_ChannelPLCActivateRead
	#define CHK_Cifx_ChannelPLCActivateRead  TRUE
	#define EXP_Cifx_ChannelPLCActivateRead  CAL_CMEXPAPI( "Cifx_ChannelPLCActivateRead" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelPLCActivateRead
	#define EXT_Cifx_ChannelPLCActivateRead
	#define GET_Cifx_ChannelPLCActivateRead(fl)  CAL_CMGETAPI( "Cifx_ChannelPLCActivateRead" ) 
	#define CAL_Cifx_ChannelPLCActivateRead  Cifx_ChannelPLCActivateRead
	#define CHK_Cifx_ChannelPLCActivateRead  TRUE
	#define EXP_Cifx_ChannelPLCActivateRead  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelPLCActivateRead", (RTS_UINTPTR)Cifx_ChannelPLCActivateRead, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelPLCActivateRead
	#define EXT_CmpHilscherCIFXCifx_ChannelPLCActivateRead
	#define GET_CmpHilscherCIFXCifx_ChannelPLCActivateRead  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelPLCActivateRead pICmpHilscherCIFX->ICifx_ChannelPLCActivateRead
	#define CHK_CmpHilscherCIFXCifx_ChannelPLCActivateRead (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelPLCActivateRead  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelPLCActivateRead
	#define EXT_Cifx_ChannelPLCActivateRead
	#define GET_Cifx_ChannelPLCActivateRead(fl)  CAL_CMGETAPI( "Cifx_ChannelPLCActivateRead" ) 
	#define CAL_Cifx_ChannelPLCActivateRead pICmpHilscherCIFX->ICifx_ChannelPLCActivateRead
	#define CHK_Cifx_ChannelPLCActivateRead (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelPLCActivateRead  CAL_CMEXPAPI( "Cifx_ChannelPLCActivateRead" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelPLCActivateRead  PFCIFX_CHANNELPLCACTIVATEREAD pfCifx_ChannelPLCActivateRead;
	#define EXT_Cifx_ChannelPLCActivateRead  extern PFCIFX_CHANNELPLCACTIVATEREAD pfCifx_ChannelPLCActivateRead;
	#define GET_Cifx_ChannelPLCActivateRead(fl)  s_pfCMGetAPI2( "Cifx_ChannelPLCActivateRead", (RTS_VOID_FCTPTR *)&pfCifx_ChannelPLCActivateRead, (fl), 0, 0)
	#define CAL_Cifx_ChannelPLCActivateRead  pfCifx_ChannelPLCActivateRead
	#define CHK_Cifx_ChannelPLCActivateRead  (pfCifx_ChannelPLCActivateRead != NULL)
	#define EXP_Cifx_ChannelPLCActivateRead  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelPLCActivateRead", (RTS_UINTPTR)Cifx_ChannelPLCActivateRead, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelSetPacketTimeout(RTS_HANDLE	hChannel, RTS_UI32 ulTimeout);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELSETPACKETTIMEOUT) (RTS_HANDLE	hChannel, RTS_UI32 ulTimeout);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELSETPACKETTIMEOUT_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelSetPacketTimeout
	#define EXT_Cifx_ChannelSetPacketTimeout
	#define GET_Cifx_ChannelSetPacketTimeout(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelSetPacketTimeout(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelSetPacketTimeout  FALSE
	#define EXP_Cifx_ChannelSetPacketTimeout  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelSetPacketTimeout
	#define EXT_Cifx_ChannelSetPacketTimeout
	#define GET_Cifx_ChannelSetPacketTimeout(fl)  CAL_CMGETAPI( "Cifx_ChannelSetPacketTimeout" ) 
	#define CAL_Cifx_ChannelSetPacketTimeout  Cifx_ChannelSetPacketTimeout
	#define CHK_Cifx_ChannelSetPacketTimeout  TRUE
	#define EXP_Cifx_ChannelSetPacketTimeout  CAL_CMEXPAPI( "Cifx_ChannelSetPacketTimeout" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelSetPacketTimeout
	#define EXT_Cifx_ChannelSetPacketTimeout
	#define GET_Cifx_ChannelSetPacketTimeout(fl)  CAL_CMGETAPI( "Cifx_ChannelSetPacketTimeout" ) 
	#define CAL_Cifx_ChannelSetPacketTimeout  Cifx_ChannelSetPacketTimeout
	#define CHK_Cifx_ChannelSetPacketTimeout  TRUE
	#define EXP_Cifx_ChannelSetPacketTimeout  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelSetPacketTimeout", (RTS_UINTPTR)Cifx_ChannelSetPacketTimeout, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelSetPacketTimeout
	#define EXT_CmpHilscherCIFXCifx_ChannelSetPacketTimeout
	#define GET_CmpHilscherCIFXCifx_ChannelSetPacketTimeout  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelSetPacketTimeout pICmpHilscherCIFX->ICifx_ChannelSetPacketTimeout
	#define CHK_CmpHilscherCIFXCifx_ChannelSetPacketTimeout (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelSetPacketTimeout  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelSetPacketTimeout
	#define EXT_Cifx_ChannelSetPacketTimeout
	#define GET_Cifx_ChannelSetPacketTimeout(fl)  CAL_CMGETAPI( "Cifx_ChannelSetPacketTimeout" ) 
	#define CAL_Cifx_ChannelSetPacketTimeout pICmpHilscherCIFX->ICifx_ChannelSetPacketTimeout
	#define CHK_Cifx_ChannelSetPacketTimeout (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelSetPacketTimeout  CAL_CMEXPAPI( "Cifx_ChannelSetPacketTimeout" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelSetPacketTimeout  PFCIFX_CHANNELSETPACKETTIMEOUT pfCifx_ChannelSetPacketTimeout;
	#define EXT_Cifx_ChannelSetPacketTimeout  extern PFCIFX_CHANNELSETPACKETTIMEOUT pfCifx_ChannelSetPacketTimeout;
	#define GET_Cifx_ChannelSetPacketTimeout(fl)  s_pfCMGetAPI2( "Cifx_ChannelSetPacketTimeout", (RTS_VOID_FCTPTR *)&pfCifx_ChannelSetPacketTimeout, (fl), 0, 0)
	#define CAL_Cifx_ChannelSetPacketTimeout  pfCifx_ChannelSetPacketTimeout
	#define CHK_Cifx_ChannelSetPacketTimeout  (pfCifx_ChannelSetPacketTimeout != NULL)
	#define EXP_Cifx_ChannelSetPacketTimeout  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelSetPacketTimeout", (RTS_UINTPTR)Cifx_ChannelSetPacketTimeout, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ChannelGetPacketTimeout(RTS_HANDLE	hChannel, RTS_UI32* pulTimeout);
typedef RTS_RESULT (CDECL * PFCIFX_CHANNELGETPACKETTIMEOUT) (RTS_HANDLE	hChannel, RTS_UI32* pulTimeout);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_CHANNELGETPACKETTIMEOUT_NOTIMPLEMENTED)
	#define USE_Cifx_ChannelGetPacketTimeout
	#define EXT_Cifx_ChannelGetPacketTimeout
	#define GET_Cifx_ChannelGetPacketTimeout(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ChannelGetPacketTimeout(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ChannelGetPacketTimeout  FALSE
	#define EXP_Cifx_ChannelGetPacketTimeout  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ChannelGetPacketTimeout
	#define EXT_Cifx_ChannelGetPacketTimeout
	#define GET_Cifx_ChannelGetPacketTimeout(fl)  CAL_CMGETAPI( "Cifx_ChannelGetPacketTimeout" ) 
	#define CAL_Cifx_ChannelGetPacketTimeout  Cifx_ChannelGetPacketTimeout
	#define CHK_Cifx_ChannelGetPacketTimeout  TRUE
	#define EXP_Cifx_ChannelGetPacketTimeout  CAL_CMEXPAPI( "Cifx_ChannelGetPacketTimeout" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ChannelGetPacketTimeout
	#define EXT_Cifx_ChannelGetPacketTimeout
	#define GET_Cifx_ChannelGetPacketTimeout(fl)  CAL_CMGETAPI( "Cifx_ChannelGetPacketTimeout" ) 
	#define CAL_Cifx_ChannelGetPacketTimeout  Cifx_ChannelGetPacketTimeout
	#define CHK_Cifx_ChannelGetPacketTimeout  TRUE
	#define EXP_Cifx_ChannelGetPacketTimeout  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelGetPacketTimeout", (RTS_UINTPTR)Cifx_ChannelGetPacketTimeout, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ChannelGetPacketTimeout
	#define EXT_CmpHilscherCIFXCifx_ChannelGetPacketTimeout
	#define GET_CmpHilscherCIFXCifx_ChannelGetPacketTimeout  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ChannelGetPacketTimeout pICmpHilscherCIFX->ICifx_ChannelGetPacketTimeout
	#define CHK_CmpHilscherCIFXCifx_ChannelGetPacketTimeout (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ChannelGetPacketTimeout  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ChannelGetPacketTimeout
	#define EXT_Cifx_ChannelGetPacketTimeout
	#define GET_Cifx_ChannelGetPacketTimeout(fl)  CAL_CMGETAPI( "Cifx_ChannelGetPacketTimeout" ) 
	#define CAL_Cifx_ChannelGetPacketTimeout pICmpHilscherCIFX->ICifx_ChannelGetPacketTimeout
	#define CHK_Cifx_ChannelGetPacketTimeout (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ChannelGetPacketTimeout  CAL_CMEXPAPI( "Cifx_ChannelGetPacketTimeout" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ChannelGetPacketTimeout  PFCIFX_CHANNELGETPACKETTIMEOUT pfCifx_ChannelGetPacketTimeout;
	#define EXT_Cifx_ChannelGetPacketTimeout  extern PFCIFX_CHANNELGETPACKETTIMEOUT pfCifx_ChannelGetPacketTimeout;
	#define GET_Cifx_ChannelGetPacketTimeout(fl)  s_pfCMGetAPI2( "Cifx_ChannelGetPacketTimeout", (RTS_VOID_FCTPTR *)&pfCifx_ChannelGetPacketTimeout, (fl), 0, 0)
	#define CAL_Cifx_ChannelGetPacketTimeout  pfCifx_ChannelGetPacketTimeout
	#define CHK_Cifx_ChannelGetPacketTimeout  (pfCifx_ChannelGetPacketTimeout != NULL)
	#define EXP_Cifx_ChannelGetPacketTimeout  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ChannelGetPacketTimeout", (RTS_UINTPTR)Cifx_ChannelGetPacketTimeout, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_ResetConfigApplication(RTS_UI32 ulModuleType, RTS_UI32 ulInstance, RTS_UI32 ulCommand);
typedef RTS_RESULT (CDECL * PFCIFX_RESETCONFIGAPPLICATION) (RTS_UI32 ulModuleType, RTS_UI32 ulInstance, RTS_UI32 ulCommand);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_RESETCONFIGAPPLICATION_NOTIMPLEMENTED)
	#define USE_Cifx_ResetConfigApplication
	#define EXT_Cifx_ResetConfigApplication
	#define GET_Cifx_ResetConfigApplication(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_ResetConfigApplication(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_ResetConfigApplication  FALSE
	#define EXP_Cifx_ResetConfigApplication  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_ResetConfigApplication
	#define EXT_Cifx_ResetConfigApplication
	#define GET_Cifx_ResetConfigApplication(fl)  CAL_CMGETAPI( "Cifx_ResetConfigApplication" ) 
	#define CAL_Cifx_ResetConfigApplication  Cifx_ResetConfigApplication
	#define CHK_Cifx_ResetConfigApplication  TRUE
	#define EXP_Cifx_ResetConfigApplication  CAL_CMEXPAPI( "Cifx_ResetConfigApplication" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_ResetConfigApplication
	#define EXT_Cifx_ResetConfigApplication
	#define GET_Cifx_ResetConfigApplication(fl)  CAL_CMGETAPI( "Cifx_ResetConfigApplication" ) 
	#define CAL_Cifx_ResetConfigApplication  Cifx_ResetConfigApplication
	#define CHK_Cifx_ResetConfigApplication  TRUE
	#define EXP_Cifx_ResetConfigApplication  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ResetConfigApplication", (RTS_UINTPTR)Cifx_ResetConfigApplication, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_ResetConfigApplication
	#define EXT_CmpHilscherCIFXCifx_ResetConfigApplication
	#define GET_CmpHilscherCIFXCifx_ResetConfigApplication  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_ResetConfigApplication pICmpHilscherCIFX->ICifx_ResetConfigApplication
	#define CHK_CmpHilscherCIFXCifx_ResetConfigApplication (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_ResetConfigApplication  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_ResetConfigApplication
	#define EXT_Cifx_ResetConfigApplication
	#define GET_Cifx_ResetConfigApplication(fl)  CAL_CMGETAPI( "Cifx_ResetConfigApplication" ) 
	#define CAL_Cifx_ResetConfigApplication pICmpHilscherCIFX->ICifx_ResetConfigApplication
	#define CHK_Cifx_ResetConfigApplication (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_ResetConfigApplication  CAL_CMEXPAPI( "Cifx_ResetConfigApplication" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_ResetConfigApplication  PFCIFX_RESETCONFIGAPPLICATION pfCifx_ResetConfigApplication;
	#define EXT_Cifx_ResetConfigApplication  extern PFCIFX_RESETCONFIGAPPLICATION pfCifx_ResetConfigApplication;
	#define GET_Cifx_ResetConfigApplication(fl)  s_pfCMGetAPI2( "Cifx_ResetConfigApplication", (RTS_VOID_FCTPTR *)&pfCifx_ResetConfigApplication, (fl), 0, 0)
	#define CAL_Cifx_ResetConfigApplication  pfCifx_ResetConfigApplication
	#define CHK_Cifx_ResetConfigApplication  (pfCifx_ResetConfigApplication != NULL)
	#define EXP_Cifx_ResetConfigApplication  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_ResetConfigApplication", (RTS_UINTPTR)Cifx_ResetConfigApplication, 0, 0) 
#endif




RTS_RESULT CDECL Cifx_GetBusActivationBeforeReset(RTS_UI32 ulModuleType, RTS_UI32 ulInstance, RTS_UI32* ulCmd);
typedef RTS_RESULT (CDECL * PFCIFX_GETBUSACTIVATIONBEFORERESET) (RTS_UI32 ulModuleType, RTS_UI32 ulInstance, RTS_UI32* ulCmd);
#if defined(CMPHILSCHERCIFX_NOTIMPLEMENTED) || defined(CIFX_GETBUSACTIVATIONBEFORERESET_NOTIMPLEMENTED)
	#define USE_Cifx_GetBusActivationBeforeReset
	#define EXT_Cifx_GetBusActivationBeforeReset
	#define GET_Cifx_GetBusActivationBeforeReset(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Cifx_GetBusActivationBeforeReset(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_Cifx_GetBusActivationBeforeReset  FALSE
	#define EXP_Cifx_GetBusActivationBeforeReset  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Cifx_GetBusActivationBeforeReset
	#define EXT_Cifx_GetBusActivationBeforeReset
	#define GET_Cifx_GetBusActivationBeforeReset(fl)  CAL_CMGETAPI( "Cifx_GetBusActivationBeforeReset" ) 
	#define CAL_Cifx_GetBusActivationBeforeReset  Cifx_GetBusActivationBeforeReset
	#define CHK_Cifx_GetBusActivationBeforeReset  TRUE
	#define EXP_Cifx_GetBusActivationBeforeReset  CAL_CMEXPAPI( "Cifx_GetBusActivationBeforeReset" ) 
#elif defined(MIXED_LINK) && !defined(CMPHILSCHERCIFX_EXTERNAL)
	#define USE_Cifx_GetBusActivationBeforeReset
	#define EXT_Cifx_GetBusActivationBeforeReset
	#define GET_Cifx_GetBusActivationBeforeReset(fl)  CAL_CMGETAPI( "Cifx_GetBusActivationBeforeReset" ) 
	#define CAL_Cifx_GetBusActivationBeforeReset  Cifx_GetBusActivationBeforeReset
	#define CHK_Cifx_GetBusActivationBeforeReset  TRUE
	#define EXP_Cifx_GetBusActivationBeforeReset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_GetBusActivationBeforeReset", (RTS_UINTPTR)Cifx_GetBusActivationBeforeReset, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHilscherCIFXCifx_GetBusActivationBeforeReset
	#define EXT_CmpHilscherCIFXCifx_GetBusActivationBeforeReset
	#define GET_CmpHilscherCIFXCifx_GetBusActivationBeforeReset  ERR_OK
	#define CAL_CmpHilscherCIFXCifx_GetBusActivationBeforeReset pICmpHilscherCIFX->ICifx_GetBusActivationBeforeReset
	#define CHK_CmpHilscherCIFXCifx_GetBusActivationBeforeReset (pICmpHilscherCIFX != NULL)
	#define EXP_CmpHilscherCIFXCifx_GetBusActivationBeforeReset  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Cifx_GetBusActivationBeforeReset
	#define EXT_Cifx_GetBusActivationBeforeReset
	#define GET_Cifx_GetBusActivationBeforeReset(fl)  CAL_CMGETAPI( "Cifx_GetBusActivationBeforeReset" ) 
	#define CAL_Cifx_GetBusActivationBeforeReset pICmpHilscherCIFX->ICifx_GetBusActivationBeforeReset
	#define CHK_Cifx_GetBusActivationBeforeReset (pICmpHilscherCIFX != NULL)
	#define EXP_Cifx_GetBusActivationBeforeReset  CAL_CMEXPAPI( "Cifx_GetBusActivationBeforeReset" ) 
#else /* DYNAMIC_LINK */
	#define USE_Cifx_GetBusActivationBeforeReset  PFCIFX_GETBUSACTIVATIONBEFORERESET pfCifx_GetBusActivationBeforeReset;
	#define EXT_Cifx_GetBusActivationBeforeReset  extern PFCIFX_GETBUSACTIVATIONBEFORERESET pfCifx_GetBusActivationBeforeReset;
	#define GET_Cifx_GetBusActivationBeforeReset(fl)  s_pfCMGetAPI2( "Cifx_GetBusActivationBeforeReset", (RTS_VOID_FCTPTR *)&pfCifx_GetBusActivationBeforeReset, (fl), 0, 0)
	#define CAL_Cifx_GetBusActivationBeforeReset  pfCifx_GetBusActivationBeforeReset
	#define CHK_Cifx_GetBusActivationBeforeReset  (pfCifx_GetBusActivationBeforeReset != NULL)
	#define EXP_Cifx_GetBusActivationBeforeReset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Cifx_GetBusActivationBeforeReset", (RTS_UINTPTR)Cifx_GetBusActivationBeforeReset, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFCIFX_DRIVEROPEN ICifx_DriverOpen;
 	PFCIFX_DRIVERCLOSE ICifx_DriverClose;
 	PFCIFX_DRIVERGETINFORMATION ICifx_DriverGetInformation;
 	PFCIFX_DRIVERGETERRORDESCRIPTION ICifx_DriverGetErrorDescription;
 	PFCIFX_DRIVERENUMBOARDS ICifx_DriverEnumBoards;
 	PFCIFX_DRIVERENUMCHANNELS ICifx_DriverEnumChannels;
 	PFCIFX_DRIVERMEMORYPOINTER ICifx_DriverMemoryPointer;
 	PFCIFX_SYSDEVICEOPEN ICifx_SysDeviceOpen;
 	PFCIFX_SYSDEVICECLOSE ICifx_SysDeviceClose;
 	PFCIFX_SYSDEVICERESET ICifx_SysDeviceReset;
 	PFCIFX_SYSDEVICEGETMBXSTATE ICifx_SysDeviceGetMBXState;
 	PFCIFX_SYSDEVICEPUTPACKET ICifx_SysDevicePutPacket;
 	PFCIFX_SYSDEVICEGETPACKET ICifx_SysDeviceGetPacket;
 	PFCIFX_SYSDEVICEDOWNLOAD ICifx_SysDeviceDownload;
 	PFCIFX_SYSDEVICEINFO ICifx_SysDeviceInfo;
 	PFCIFX_SYSDEVICEFINDFIRSTFILE ICifx_SysDeviceFindFirstFile;
 	PFCIFX_SYSDEVICEFINDNEXTFILE ICifx_SysDeviceFindNextFile;
 	PFCIFX_SYSDEVICEUPLOAD ICifx_SysDeviceUpload;
 	PFCIFX_CHANNELOPEN ICifx_ChannelOpen;
 	PFCIFX_CHANNELOPEN2 ICifx_ChannelOpen2;
 	PFCIFX_CHANNELCLOSE ICifx_ChannelClose;
 	PFCIFX_CHANNELDOWNLOAD ICifx_ChannelDownload;
 	PFCIFX_CHANNELFINDFIRSTFILE ICifx_ChannelFindFirstFile;
 	PFCIFX_CHANNELFINDNEXTFILE ICifx_ChannelFindNextFile;
 	PFCIFX_CHANNELUPLOAD ICifx_ChannelUpload;
 	PFCIFX_CHANNELGETMBXSTATE ICifx_ChannelGetMBXState;
 	PFCIFX_CHANNELPUTPACKET ICifx_ChannelPutPacket;
 	PFCIFX_CHANNELGETPACKET ICifx_ChannelGetPacket;
 	PFCIFX_CHANNELRESET ICifx_ChannelReset;
 	PFCIFX_CHANNELGETSENDPACKET ICifx_ChannelGetSendPacket;
 	PFCIFX_CHANNELCONFIGLOCK ICifx_ChannelConfigLock;
 	PFCIFX_CHANNELINFO ICifx_ChannelInfo;
 	PFCIFX_CHANNELIOINFO ICifx_ChannelIOInfo;
 	PFCIFX_CHANNELWATCHDOG ICifx_ChannelWatchdog;
 	PFCIFX_CHANNELHOSTSTATE ICifx_ChannelHoststate;
 	PFCIFX_CHANNELBUSSTATE ICifx_ChannelBusstate;
 	PFCIFX_CHANNELIOREAD ICifx_ChannelIORead;
 	PFCIFX_CHANNELIOWRITE ICifx_ChannelIOWrite;
 	PFCIFX_CHANNELIOREADSENDDATA ICifx_ChannelIOReadSendData;
 	PFCIFX_CHANNELCONTROLBLOCK ICifx_ChannelControlBlock;
 	PFCIFX_CHANNELCOMMONSTATUSBLOCK ICifx_ChannelCommonStatusBlock;
 	PFCIFX_CHANNELEXTENDEDSTATUSBLOCK ICifx_ChannelExtendedStatusBlock;
 	PFCIFX_CHANNELUSERBLOCK ICifx_ChannelUserBlock;
 	PFCIFX_CHANNELPLCMEMORYPTR ICifx_ChannelPLCMemoryPtr;
 	PFCIFX_CHANNELPLCISREADREADY ICifx_ChannelPLCIsReadReady;
 	PFCIFX_CHANNELPLCISWRITEREADY ICifx_ChannelPLCIsWriteReady;
 	PFCIFX_CHANNELPLCACTIVATEWRITE ICifx_ChannelPLCActivateWrite;
 	PFCIFX_CHANNELPLCACTIVATEREAD ICifx_ChannelPLCActivateRead;
 	PFCIFX_CHANNELSETPACKETTIMEOUT ICifx_ChannelSetPacketTimeout;
 	PFCIFX_CHANNELGETPACKETTIMEOUT ICifx_ChannelGetPacketTimeout;
 	PFCIFX_RESETCONFIGAPPLICATION ICifx_ResetConfigApplication;
 	PFCIFX_GETBUSACTIVATIONBEFORERESET ICifx_GetBusActivationBeforeReset;
 } ICmpHilscherCIFX_C;

#ifdef CPLUSPLUS
class ICmpHilscherCIFX : public IBase
{
	public:
		virtual RTS_RESULT CDECL ICifx_DriverOpen(RTS_HANDLE* phDriver) =0;
		virtual RTS_RESULT CDECL ICifx_DriverClose(RTS_HANDLE hDriver) =0;
		virtual RTS_RESULT CDECL ICifx_DriverGetInformation(RTS_HANDLE	hDriver, RTS_UI32	ulSize, void* pDriverInfo) =0;
		virtual RTS_RESULT CDECL ICifx_DriverGetErrorDescription(RTS_UI32 ulError, char* szBuffer, RTS_UI32 ulBufferLen) =0;
		virtual RTS_RESULT CDECL ICifx_DriverEnumBoards(RTS_HANDLE	hDriver, RTS_UI32	ulBoard, RTS_UI32	ulSize, void*			pvBoardInfo) =0;
		virtual RTS_RESULT CDECL ICifx_DriverEnumChannels(RTS_HANDLE	hDriver, RTS_UI32	ulBoard, RTS_UI32	ulChannel, RTS_UI32	ulSize, void*			pvChannelInfo) =0;
		virtual RTS_RESULT CDECL ICifx_DriverMemoryPointer(RTS_HANDLE	hDriver, RTS_UI32	ulBoard, RTS_UI32	ulCmd, void* pvMemoryInfo) =0;
		virtual RTS_RESULT CDECL ICifx_SysDeviceOpen(RTS_HANDLE	hDriver, char*			szBoard, RTS_HANDLE*	phSysdevice) =0;
		virtual RTS_RESULT CDECL ICifx_SysDeviceClose(RTS_HANDLE	hSysdevice) =0;
		virtual RTS_RESULT CDECL ICifx_SysDeviceReset(RTS_HANDLE	hSysdevice, RTS_UI32 ulTimeout) =0;
		virtual RTS_RESULT CDECL ICifx_SysDeviceGetMBXState(RTS_HANDLE	hSysdevice, RTS_UI32*	pulRecvPktCount, RTS_UI32*	pulSendPktCount) =0;
		virtual RTS_RESULT CDECL ICifx_SysDevicePutPacket(RTS_HANDLE	hSysdevice, CIFX_PACKET*	ptSendPkt, RTS_UI32	ulTimeout) =0;
		virtual RTS_RESULT CDECL ICifx_SysDeviceGetPacket(RTS_HANDLE	hSysdevice, RTS_UI32	ulSize, CIFX_PACKET*	ptRecvPkt, RTS_UI32	ulTimeout) =0;
		virtual RTS_RESULT CDECL ICifx_SysDeviceDownload(RTS_HANDLE	hSysdevice, RTS_UI32	ulChannel, RTS_UI32	ulMode, char* szFileName, RTS_UI8*	pbyFileData, RTS_UI32	ulFileSize, PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void*	pvUser) =0;
		virtual RTS_RESULT CDECL ICifx_SysDeviceInfo(RTS_HANDLE	hSysdevice, RTS_UI32	ulCmd, RTS_UI32	ulSize, void*			pvInfo) =0;
		virtual RTS_RESULT CDECL ICifx_SysDeviceFindFirstFile(RTS_HANDLE	hSysdevice, RTS_UI32	ulChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pUser) =0;
		virtual RTS_RESULT CDECL ICifx_SysDeviceFindNextFile(RTS_HANDLE	hSysdevice, RTS_UI32	ulChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pUser) =0;
		virtual RTS_RESULT CDECL ICifx_SysDeviceUpload(RTS_HANDLE	hSysdevice, RTS_UI32	ulChannel, RTS_UI32	ulMode, char* szFileName, RTS_UI8*	pbyFileData, RTS_UI32*	pulFileSize, PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void*	pvUser) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelOpen(RTS_HANDLE	hDriver, char*			szBoard, RTS_UI32	ulChannel, RTS_HANDLE*	phChannel) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelOpen2(RTS_HANDLE	hDriver, char* szBoard, RTS_UI32 ulChannel, RTS_HANDLE* phChannel, RTS_UI32 ulQueueMode) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelClose(RTS_HANDLE	hChannel) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelDownload(RTS_HANDLE	hChannel, RTS_UI32	ulMode, char* szFileName, RTS_UI8*	pbyFileData, RTS_UI32	ulFileSize, PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelFindFirstFile(RTS_HANDLE	hChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void*	pvUser) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelFindNextFile(RTS_HANDLE	hChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void*	pvUser) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelUpload(RTS_HANDLE	hChannel, RTS_UI32	ulMode, char* szFileName, RTS_UI8*	pbyFileData, RTS_UI32*	pulFileSize, PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelGetMBXState(RTS_HANDLE	hChannel, RTS_UI32*	pulRecvPktCount, RTS_UI32*	pulSendPktCount) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelPutPacket(RTS_HANDLE	hChannel, CIFX_PACKET*	ptSendPkt, RTS_UI32	ulTimeout) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelGetPacket(RTS_HANDLE	hChannel, RTS_UI32	ulSize, CIFX_PACKET*	ptRecvPkt, RTS_UI32	ulTimeout) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelReset(RTS_HANDLE	hChannel, RTS_UI32	ulResetMode, RTS_UI32	ulTimeout) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelGetSendPacket(RTS_HANDLE	hChannel, RTS_UI32	ulSize, CIFX_PACKET*	ptRecvPkt) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelConfigLock(RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32*	pulState, RTS_UI32	ulTimeout) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelInfo(RTS_HANDLE	hChannel, RTS_UI32	ulSize, void*			pvChannelInfo) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelIOInfo(RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32 ulArea, RTS_UI32	ulSize, void*	pvData) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelWatchdog(RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32*	pulTrigger) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelHoststate(RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32*	pulState, RTS_UI32	ulTimeout) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelBusstate(RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32*	pulState, RTS_UI32	ulTimeout) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelIORead(RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData, RTS_UI32	ulTimeout) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelIOWrite(RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData, RTS_UI32	ulTimeout) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelIOReadSendData(RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelControlBlock(RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelCommonStatusBlock(RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelExtendedStatusBlock(RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelUserBlock(RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber, RTS_UI32	ulCmd, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelPLCMemoryPtr(RTS_HANDLE hChannel, RTS_UI32	ulCmd, void* pvMemoryInfo) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelPLCIsReadReady(RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber, RTS_UI32*	pulReadState) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelPLCIsWriteReady(RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber, RTS_UI32*	pulWriteState) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelPLCActivateWrite(RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelPLCActivateRead(RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelSetPacketTimeout(RTS_HANDLE	hChannel, RTS_UI32 ulTimeout) =0;
		virtual RTS_RESULT CDECL ICifx_ChannelGetPacketTimeout(RTS_HANDLE	hChannel, RTS_UI32* pulTimeout) =0;
		virtual RTS_RESULT CDECL ICifx_ResetConfigApplication(RTS_UI32 ulModuleType, RTS_UI32 ulInstance, RTS_UI32 ulCommand) =0;
		virtual RTS_RESULT CDECL ICifx_GetBusActivationBeforeReset(RTS_UI32 ulModuleType, RTS_UI32 ulInstance, RTS_UI32* ulCmd) =0;
};
	#ifndef ITF_CmpHilscherCIFX
		#define ITF_CmpHilscherCIFX static ICmpHilscherCIFX *pICmpHilscherCIFX = NULL;
	#endif
	#define EXTITF_CmpHilscherCIFX
#else	/*CPLUSPLUS*/
	typedef ICmpHilscherCIFX_C		ICmpHilscherCIFX;
	#ifndef ITF_CmpHilscherCIFX
		#define ITF_CmpHilscherCIFX
	#endif
	#define EXTITF_CmpHilscherCIFX
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPHILSCHERCIFXITF_H_*/
