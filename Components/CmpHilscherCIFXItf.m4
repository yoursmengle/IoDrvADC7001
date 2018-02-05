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

SET_INTERFACE_NAME(`CmpHilscherCIFX')

#include "CmpItf.h"
REF_ITF(`SysIntItf.m4')
REF_ITF(`CmpIoDrvItf.m4')

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
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

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

DEF_API(`void',`CDECL',`cifx_getbusactivationbeforereset',`(cifx_getbusactivationbeforereset_struct *p)',1,0x82ED5912,0x03050800)

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

DEF_API(`void',`CDECL',`cifx_resetconfigapplication',`(cifx_resetconfigapplication_struct *p)',1,0xEBA09E55,0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchannelbusstate',`(cifx_xchannelbusstate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x7438ED44),0x03050800)

/**
 * <description>cifx_xchannelclose</description>
 */
typedef struct tagcifx_xchannelclose_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelClose;	/* VAR_OUTPUT */	
} cifx_xchannelclose_struct;

DEF_API(`void',`CDECL',`cifx_xchannelclose',`(cifx_xchannelclose_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xEFA9701A),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchannelcommonstatusblock',`(cifx_xchannelcommonstatusblock_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0435FE4E),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchannelconfiglock',`(cifx_xchannelconfiglock_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4DC337D6),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchannelcontrolblock',`(cifx_xchannelcontrolblock_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xAC77B13A),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchanneldownload',`(cifx_xchanneldownload_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x35317A0D),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchannelextendedstatusblock',`(cifx_xchannelextendedstatusblock_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA2DF8FC9),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchannelfindfirstfile',`(cifx_xchannelfindfirstfile_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4D84CCEB),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchannelfindnextfile',`(cifx_xchannelfindnextfile_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xFF6C58F9),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchannelgetmbxstate',`(cifx_xchannelgetmbxstate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xE613E244),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchannelgetpacket',`(cifx_xchannelgetpacket_struct *p)',1,0,0x03050800)

/**
 *Sets the timeout of the packets sent to this channel
 */
typedef struct tagcifx_xchannelgetpackettimeout_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	/* Channel Handle */
	RTS_IEC_UDINT *ulTimeout;			/* VAR_INPUT */	/* Timeout in ms */
	RTS_IEC_RESULT CIFX_xChannelGetPacketTimeout;	/* VAR_OUTPUT */	
} cifx_xchannelgetpackettimeout_struct;

DEF_API(`void',`CDECL',`cifx_xchannelgetpackettimeout',`(cifx_xchannelgetpackettimeout_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0FB236A9),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchannelgetsendpacket',`(cifx_xchannelgetsendpacket_struct *p)',1,0,0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchannelhoststate',`(cifx_xchannelhoststate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x629A3BDA),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchannelinfo',`(cifx_xchannelinfo_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x8B453ECC),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchannelioinfo',`(cifx_xchannelioinfo_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xCB00EB62),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchannelioread',`(cifx_xchannelioread_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC8A4DFC7),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchannelioreadsenddata',`(cifx_xchannelioreadsenddata_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF2AE39F9),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchanneliowrite',`(cifx_xchanneliowrite_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xE8C87DDA),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchannelopen',`(cifx_xchannelopen_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x17CC3A73),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchannelopen2',`(cifx_xchannelopen2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x55FC024E),0x03050800)

/**
 * <description>cifx_xchannelplcactivateread</description>
 */
typedef struct tagcifx_xchannelplcactivateread_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiAreaNumber;		/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelPLCActivateRead;	/* VAR_OUTPUT */	
} cifx_xchannelplcactivateread_struct;

DEF_API(`void',`CDECL',`cifx_xchannelplcactivateread',`(cifx_xchannelplcactivateread_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC76B6902),0x03050800)

/**
 * <description>cifx_xchannelplcactivatewrite</description>
 */
typedef struct tagcifx_xchannelplcactivatewrite_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiAreaNumber;		/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xChannelPLCActivateWrite;	/* VAR_OUTPUT */	
} cifx_xchannelplcactivatewrite_struct;

DEF_API(`void',`CDECL',`cifx_xchannelplcactivatewrite',`(cifx_xchannelplcactivatewrite_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD1C00795),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchannelplcisreadready',`(cifx_xchannelplcisreadready_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0E0405F5),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchannelplciswriteready',`(cifx_xchannelplciswriteready_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0B75BAF6),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchannelplcmemoryptr',`(cifx_xchannelplcmemoryptr_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA17F7B17),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchannelputpacket',`(cifx_xchannelputpacket_struct *p)',1,0,0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchannelreset',`(cifx_xchannelreset_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xED071562),0x03050800)

/**
 *Sets the timeout of the packets sent to this channel
 */
typedef struct tagcifx_xchannelsetpackettimeout_struct
{
	RTS_IEC_HANDLE hChannel;			/* VAR_INPUT */	/* Channel Handle, CAA_hINVALID sets the timout of all channels */
	RTS_IEC_UDINT ulTimeout;			/* VAR_INPUT */	/* Timeout in ms */
	RTS_IEC_RESULT CIFX_xChannelSetPacketTimeout;	/* VAR_OUTPUT */	
} cifx_xchannelsetpackettimeout_struct;

DEF_API(`void',`CDECL',`cifx_xchannelsetpackettimeout',`(cifx_xchannelsetpackettimeout_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x9C4E870E),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchannelupload',`(cifx_xchannelupload_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA44F115D),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchanneluserblock',`(cifx_xchanneluserblock_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x39A301B9),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xchannelwatchdog',`(cifx_xchannelwatchdog_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x40D3DF4B),0x03050800)

/**
 * <description>cifx_xdriverclose</description>
 */
typedef struct tagcifx_xdriverclose_struct
{
	RTS_IEC_HANDLE hDriver;				/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xDriverClose;	/* VAR_OUTPUT */	
} cifx_xdriverclose_struct;

DEF_API(`void',`CDECL',`cifx_xdriverclose',`(cifx_xdriverclose_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x39D218C1),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xdriverenumboards',`(cifx_xdriverenumboards_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x1910C175),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xdriverenumchannels',`(cifx_xdriverenumchannels_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x82DD213B),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xdrivergeterrordescription',`(cifx_xdrivergeterrordescription_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x81139BE6),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xdrivergetinformation',`(cifx_xdrivergetinformation_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x5DA7F834),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xdrivermemorypointer',`(cifx_xdrivermemorypointer_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x81B9C261),0x03050800)

/**
 * <description>cifx_xdriveropen</description>
 */
typedef struct tagcifx_xdriveropen_struct
{
	RTS_IEC_HANDLE *phDriver;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xDriverOpen;	/* VAR_OUTPUT */	
} cifx_xdriveropen_struct;

DEF_API(`void',`CDECL',`cifx_xdriveropen',`(cifx_xdriveropen_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x8142A227),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xmemcpy',`(cifx_xmemcpy_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF3616FD8),0x03050800)

/**
 * <description>cifx_xsysdeviceclose</description>
 */
typedef struct tagcifx_xsysdeviceclose_struct
{
	RTS_IEC_HANDLE hSysdevice;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xSysdeviceClose;	/* VAR_OUTPUT */	
} cifx_xsysdeviceclose_struct;

DEF_API(`void',`CDECL',`cifx_xsysdeviceclose',`(cifx_xsysdeviceclose_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x8F559F75),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xsysdevicedownload',`(cifx_xsysdevicedownload_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x291833D8),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xsysdevicefindfirstfile',`(cifx_xsysdevicefindfirstfile_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x603E3231),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xsysdevicefindnextfile',`(cifx_xsysdevicefindnextfile_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA726E94F),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xsysdevicegetmbxstate',`(cifx_xsysdevicegetmbxstate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x10E10C41),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xsysdevicegetpacket',`(cifx_xsysdevicegetpacket_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD58D738D),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xsysdeviceinfo',`(cifx_xsysdeviceinfo_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x16E358BD),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xsysdeviceopen',`(cifx_xsysdeviceopen_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x19F5F105),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xsysdeviceputpacket',`(cifx_xsysdeviceputpacket_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC1D8C9F0),0x03050800)

/**
 * <description>cifx_xsysdevicereset</description>
 */
typedef struct tagcifx_xsysdevicereset_struct
{
	RTS_IEC_HANDLE hSysdevice;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiTimeout;			/* VAR_INPUT */	
	RTS_IEC_RESULT CIFX_xSysdeviceReset;	/* VAR_OUTPUT */	
} cifx_xsysdevicereset_struct;

DEF_API(`void',`CDECL',`cifx_xsysdevicereset',`(cifx_xsysdevicereset_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD4E3E20F),0x03050800)

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

DEF_API(`void',`CDECL',`cifx_xsysdeviceupload',`(cifx_xsysdeviceupload_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4677B806),0x03050800)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_DriverOpen',`(	RTS_HANDLE* phDriver)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_DriverClose',`(RTS_HANDLE hDriver)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_DriverGetInformation',`( RTS_HANDLE	hDriver, RTS_UI32	ulSize, void* pDriverInfo)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_DriverGetErrorDescription',`(RTS_UI32 ulError, char* szBuffer, RTS_UI32 ulBufferLen)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_DriverEnumBoards',`(RTS_HANDLE	hDriver,	RTS_UI32	ulBoard,	RTS_UI32	ulSize,	void*			pvBoardInfo)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_DriverEnumChannels',`(	RTS_HANDLE	hDriver, RTS_UI32	ulBoard,	RTS_UI32	ulChannel,	RTS_UI32	ulSize,	void*			pvChannelInfo)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_DriverMemoryPointer',`(RTS_HANDLE	hDriver, RTS_UI32	ulBoard,	RTS_UI32	ulCmd,	void* pvMemoryInfo)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_SysDeviceOpen',`(RTS_HANDLE	hDriver, char*			szBoard,	RTS_HANDLE*	phSysdevice)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_SysDeviceClose',`(	RTS_HANDLE	hSysdevice)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_SysDeviceReset',`(	RTS_HANDLE	hSysdevice, RTS_UI32 ulTimeout)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_SysDeviceGetMBXState',`(RTS_HANDLE	hSysdevice,	RTS_UI32*	pulRecvPktCount, RTS_UI32*	pulSendPktCount)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_SysDevicePutPacket',`(RTS_HANDLE	hSysdevice,	CIFX_PACKET*	ptSendPkt,	RTS_UI32	ulTimeout)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_SysDeviceGetPacket',`(	RTS_HANDLE	hSysdevice,	RTS_UI32	ulSize,	CIFX_PACKET*	ptRecvPkt, RTS_UI32	ulTimeout)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_SysDeviceDownload',`(	RTS_HANDLE	hSysdevice,	RTS_UI32	ulChannel, RTS_UI32	ulMode,	char* szFileName, RTS_UI8*	pbyFileData, RTS_UI32	ulFileSize,	PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void*	pvUser)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_SysDeviceInfo',`(RTS_HANDLE	hSysdevice,	RTS_UI32	ulCmd, RTS_UI32	ulSize,	void*			pvInfo)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_SysDeviceFindFirstFile',`(RTS_HANDLE	hSysdevice,	RTS_UI32	ulChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback,	void* pUser)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_SysDeviceFindNextFile',`(RTS_HANDLE	hSysdevice,	RTS_UI32	ulChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback,	void* pUser)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_SysDeviceUpload',`(	RTS_HANDLE	hSysdevice,	RTS_UI32	ulChannel, RTS_UI32	ulMode,	char* szFileName, RTS_UI8*	pbyFileData, RTS_UI32*	pulFileSize,	PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void*	pvUser)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelOpen',`(RTS_HANDLE	hDriver, char*			szBoard, RTS_UI32	ulChannel, RTS_HANDLE*	phChannel)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelOpen2',`(RTS_HANDLE	hDriver, char* szBoard, RTS_UI32 ulChannel, RTS_HANDLE* phChannel, RTS_UI32 ulQueueMode)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelClose',`(RTS_HANDLE	hChannel)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelDownload',`(RTS_HANDLE	hChannel, RTS_UI32	ulMode, char* szFileName, RTS_UI8*	pbyFileData, RTS_UI32	ulFileSize,	PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelFindFirstFile',`(RTS_HANDLE	hChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void*	pvUser)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelFindNextFile',`(RTS_HANDLE	hChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void*	pvUser)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelUpload',`(RTS_HANDLE	hChannel, RTS_UI32	ulMode, char* szFileName, RTS_UI8*	pbyFileData, RTS_UI32*	pulFileSize,	PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelGetMBXState',`(RTS_HANDLE	hChannel, RTS_UI32*	pulRecvPktCount, RTS_UI32*	pulSendPktCount)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelPutPacket',`(RTS_HANDLE	hChannel, CIFX_PACKET*	ptSendPkt, RTS_UI32	ulTimeout)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelGetPacket',`(RTS_HANDLE	hChannel, RTS_UI32	ulSize, CIFX_PACKET*	ptRecvPkt, RTS_UI32	ulTimeout)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelReset',`(RTS_HANDLE	hChannel, RTS_UI32	ulResetMode, RTS_UI32	ulTimeout)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelGetSendPacket',`(RTS_HANDLE	hChannel, RTS_UI32	ulSize, CIFX_PACKET*	ptRecvPkt)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelConfigLock',`(RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32*	pulState, RTS_UI32	ulTimeout)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelInfo',`(RTS_HANDLE	hChannel, RTS_UI32	ulSize, void*			pvChannelInfo)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelIOInfo',`(RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32 ulArea, RTS_UI32	ulSize, void*	pvData)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelWatchdog',`(RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32*	pulTrigger)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelHoststate',`(RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32*	pulState, RTS_UI32	ulTimeout)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelBusstate',`(RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32*	pulState, RTS_UI32	ulTimeout)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelIORead',`(RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData, RTS_UI32	ulTimeout)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelIOWrite',`(	RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData, RTS_UI32	ulTimeout)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelIOReadSendData',`(RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelControlBlock',`(RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelCommonStatusBlock',`(RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelExtendedStatusBlock',`(	RTS_HANDLE	hChannel, RTS_UI32	ulCmd, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelUserBlock',`(RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber, RTS_UI32	ulCmd, RTS_UI32	ulOffset, RTS_UI32	ulDataLen, void*			pvData)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelPLCMemoryPtr',`(RTS_HANDLE hChannel,	RTS_UI32	ulCmd, void* pvMemoryInfo)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelPLCIsReadReady',`(RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber, RTS_UI32*	pulReadState)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelPLCIsWriteReady',`(	RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber, RTS_UI32*	pulWriteState)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelPLCActivateWrite',`(RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelPLCActivateRead',`(RTS_HANDLE	hChannel, RTS_UI32	ulAreaNumber)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelSetPacketTimeout',`(RTS_HANDLE	hChannel, RTS_UI32 ulTimeout)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ChannelGetPacketTimeout',`(RTS_HANDLE	hChannel, RTS_UI32* pulTimeout)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_ResetConfigApplication',`(RTS_UI32 ulModuleType, RTS_UI32 ulInstance, RTS_UI32 ulCommand)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`Cifx_GetBusActivationBeforeReset',`(RTS_UI32 ulModuleType, RTS_UI32 ulInstance, RTS_UI32* ulCmd)')

#ifdef __cplusplus
}
#endif
