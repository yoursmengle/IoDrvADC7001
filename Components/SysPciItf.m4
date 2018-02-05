/**
 * <interfacename>SysPci</interfacename>
 * <description> 
 *	<p>The SysPci interface is projected to get access to the PCI bus on a target. This interface
 *	can only be used on architectures with a PCI bus.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysPci')

#include "CmpStd.h"

#ifndef CDECL
	#define CDECL
#endif

/**
 * <category>Static defines</category>
 * <description>Type addresses</description>
 */
#ifndef PCI_TYPE0_ADDRESSES
	#define PCI_TYPE0_ADDRESSES             6
#endif
#ifndef PCI_TYPE1_ADDRESSES
	#define PCI_TYPE1_ADDRESSES             2
#endif

/**
 * <category>Static defines</category>
 * <description>Maxmimum number of PCI devices on the bus</description>
 */
#ifndef PCI_MAX_DEVICES
	#define PCI_MAX_DEVICES					32
#endif

/**
 * <category>Static defines</category>
 * <description>Maxmimum number of PCI busses on the target</description>
 */
#ifndef PCI_MAX_BUSSES
	#define PCI_MAX_BUSSES					20
#endif

/**
 * <category>Static defines</category>
 * <description>Invalid vendor id</description>
 */
#ifndef PCI_INVALID_VENDORID
	#define PCI_INVALID_VENDORID            0xFFFF
#endif

/**
 * <category>Static defines</category>
 * <description>Maximum number of functions</description>
 */
#ifndef PCI_MAX_FUNCTION
	#define PCI_MAX_FUNCTION                8
#endif

/**
 * <category>Static defines</category>
 * <description>Pci configuration definitions</description>
 */
#define	PCI_CFG_VENDOR_ID	0x00
#define	PCI_CFG_DEVICE_ID	0x02
#define	PCI_CFG_COMMAND		0x04
#define	PCI_CFG_STATUS		0x06
#define	PCI_CFG_REVISION	0x08
#define	PCI_CFG_PROGRAMMING_IF	0x09
#define	PCI_CFG_SUBCLASS	0x0a
#define	PCI_CFG_CLASS		0x0b
#define	PCI_CFG_CACHE_LINE_SIZE	0x0c
#define	PCI_CFG_LATENCY_TIMER	0x0d
#define	PCI_CFG_HEADER_TYPE	0x0e
#define	PCI_CFG_BIST		0x0f
#define	PCI_CFG_BASE_ADDRESS_0	0x10
#define	PCI_CFG_BASE_ADDRESS_1	0x14
#define	PCI_CFG_BASE_ADDRESS_2	0x18
#define	PCI_CFG_BASE_ADDRESS_3	0x1c
#define	PCI_CFG_BASE_ADDRESS_4	0x20
#define	PCI_CFG_BASE_ADDRESS_5	0x24
#define	PCI_CFG_CIS		0x28
#define	PCI_CFG_SUB_VENDOR_ID	0x2c
#define	PCI_CFG_SUB_SYSTEM_ID	0x2e
#define	PCI_CFG_EXPANSION_ROM	0x30
#define	PCI_CFG_RESERVED_0	0x35
#define	PCI_CFG_RESERVED_1	0x38
#define	PCI_CFG_DEV_INT_LINE	0x3c
#define	PCI_CFG_DEV_INT_PIN	0x3d
#define	PCI_CFG_MIN_GRANT	0x3e
#define	PCI_CFG_MAX_LATENCY	0x3f
#define PCI_CFG_SPECIAL_USE     0x41
#define PCI_CFG_MODE            0x43

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * Address Offset of PCI addresses. This may be used for some
 * VxWorks BSPs, which have 1:1 virt:phys mapping in gerneral,
 * but a special mapping for PCI addresses. The offset is just
 * added on the scanned PCI addresses.
 * </description>
 */
#define SYSPCIKEY_INT_VXWORKS_ADDRESSOFFSET "VxWorks.AddressOffset"
#ifndef SYSPCIVALUE_INT_VXWORKS_ADDRESSOFFSET_DEFAULT
  #define SYSPCIVALUE_INT_VXWORKS_ADDRESSOFFSET_DEFAULT 0x0
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * Domain Number of PCI bus. 
 * </description>
 */
#define SYSPCIKEY_INT_LINUX_DOMAIN				"Linux.Domain"
#define SYSPCIVALUE_INT_LINUX_DOMAIN_DEFAULT	0x0

#ifndef NO_PRAGMA_PACK
	#pragma pack(1)
#endif

typedef struct tagPCI_SLOT_NUMBER_3S
{
    union
	{
        struct
	{
	#ifndef RTS_BIGENDIAN_BITORDER
            unsigned int DeviceNumber:5;
            unsigned int FunctionNumber:3;
            unsigned int Reserved:24;
	#else
            unsigned int Reserved:24;
            unsigned int FunctionNumber:3;
            unsigned int DeviceNumber:5;
	#endif
        } bits;
        RTS_UI32 AsULONG;
    } u;
} PCI_SLOT_NUMBER_3S, *PPCI_SLOT_NUMBER_3S;

#ifndef NO_PRAGMA_PACK
	#ifdef USE_PRAGMA_PACK_0
		#pragma pack(0)
	#else
		#pragma pack()
	#endif	
#endif

/**
 * <category>PCI_INFO</category>
 * <description>PCI information entry of one device.</description>
 * <param name="usVendorID" type="IN">Registered Vendor ID of card assigned by PCI SIG</param>
 * <param name="usDeviceID" type="IN">Device ID of card assigned by manufacturer</param>
 * <param name="usSubVendorID" type="IN">Registered subsystem vendor ID assigned by PCI SIG</param>
 * <param name="usSubSystemID" type="IN">Subsystem device ID assigned by manufacturer, if there are multiple subsystems on card.
 *										 The value 0 indicates that there are no subsystems.</param>
 * <param name="ulBusNr" type="IN">PCI bus number the PCI card is member of</param>
 * <param name="SlotNr" type="IN">PCI slot number (within bus) the PCI card is plugged in</param>
 * <param name="ulFunction" type="IN">PCI function number</param>
 * <param name="ulBaseAddresses" type="IN">Basis address register for reservation of I/O port addresses or I/O memory areas (Memory Mapped I/O); 
 *											Specific for particular card.</param>
 * <param name="byInterrupt" type="IN">Identifies the interrupt vector on the particular system</param>
 * <param name="DeviceSpecific" type="IN">According to PCI specification the 192 manufacture specific data bytes</param>
 */
typedef struct tagPCI_INFO
{
	RTS_UI16 usVendorID;
	RTS_UI16 usDeviceID;
    RTS_UI16 usSubVendorID;
    RTS_UI16 usSubSystemID;
	RTS_UI32 ulBusNr;
	PCI_SLOT_NUMBER_3S SlotNr;
	RTS_UI32 ulFunction;
	RTS_UI32 ulBaseAddresses[PCI_TYPE0_ADDRESSES];
	RTS_UI8 byInterrupt;
	RTS_UI8 DeviceSpecific[192];
} PCI_INFO;


/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Get PCI info of a specified card.
 * This function retrieves information on a PCI card that is identified by its vendor ID, its device ID and its card index.
 * Therefore, SysPciGetCardInfo returns a pointer to a variable of type PCI_INFO containing the information on the PCI card.
 * </description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsyspcigetcardinfo_struct
{
	RTS_IEC_WORD usVendorId;			/* VAR_INPUT */	/* <param name="usVendorId" type="IN">PCI vendor number</param> */
	RTS_IEC_WORD usDeviceId;			/* VAR_INPUT */	/* <param name="usDeviceId" type="IN">PCI device Id</param> */
	RTS_IEC_WORD usCardIndex;			/* VAR_INPUT */	/* <param name="usCardIndex" type="IN">Card index number</param> */
	PCI_INFO *pPciInfo;					/* VAR_INPUT */	/* <param name="pPciInfo" type="OUT">PCI entry</param> */
	RTS_IEC_RESULT SysPciGetCardInfo;	/* VAR_OUTPUT */	
} syspcigetcardinfo_struct;

DEF_API(`void',`CDECL',`syspcigetcardinfo',`(syspcigetcardinfo_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4D7CD8E3),0x03050500)

/**
 * <description>Get one PCI config entry.
 * This function allows to read the configuration data of a PCI card. The data is stored in a structure of type PCI_INFO
 * and filled into the PCI bus. By means of the bus, device and function number SysPciGetConfigEntry identifies the associated
 * bus entry and returns a pointer to it.
 * </description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsyspcigetconfigentry_struct
{
	RTS_IEC_WORD usBus;					/* VAR_INPUT */	/* <param name="usBus" type="IN">PCI bus number (index)</param> */
	RTS_IEC_WORD usDevice;				/* VAR_INPUT */	/* <param name="usDevice" type="IN">PCI device number (index)</param> */
	RTS_IEC_WORD usFunction;			/* VAR_INPUT */	/* <param name="usFunction" type="IN">PCI function number (index)</param> */
	PCI_INFO *pPciInfo;					/* VAR_INPUT */	/* <param name="pPciInfo" type="OUT">Pointer to structure PCI_INFO containing information on the PCI card</param> */
	RTS_IEC_RESULT SysPciGetConfigEntry;	/* VAR_OUTPUT */	
} syspcigetconfigentry_struct;

DEF_API(`void',`CDECL',`syspcigetconfigentry',`(syspcigetconfigentry_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x1B98EF98),0x03050500)

/**
 * <description>Read one PCI config value
 * This function allows to read single configuration values of a PCI card by returning a pointer on the associated memory address (pbyData).
 * Thereby the associated bus entry is identified via the bus, device and function number. The component to be read out is indicated
 * by the PciOffset.
 * </description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsyspcireadvalue_struct
{
	RTS_IEC_WORD usBus;					/* VAR_INPUT */	/* <param name="usBus" type="IN">PCI bus number (index)</param> */
	RTS_IEC_WORD usDevice;				/* VAR_INPUT */	/* <param name="usDevice" type="IN">PCI device number (index)</param> */
	RTS_IEC_WORD usFunction;			/* VAR_INPUT */	/* <param name="usFunction" type="IN">PCI function number (index)</param> */
	RTS_IEC_WORD usPciOffset;			/* VAR_INPUT */	/* <param name="usPciOffset" type="IN">Offset in the PCI config</param> */
	RTS_IEC_BYTE *pbyData;				/* VAR_INPUT */	/* <param name="pbyData" type="OUT">Pointer to data to read to PCI</param> */
	RTS_IEC_WORD usSize;				/* VAR_INPUT */	/* <param name="usSize" type="IN">Size in byte of data to read</param> */
	RTS_IEC_RESULT SysPciReadValue;		/* VAR_OUTPUT */	
} syspcireadvalue_struct;

DEF_API(`void',`CDECL',`syspcireadvalue',`(syspcireadvalue_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x622E6E70),0x03050500)

/**
 * <description>Set one PCI config entry.
 * This function allows to write an entry to the PCI bus. The entry is a structure of type PCI-INFO and is transmitted to the
 * function SysPciSetConfigEntry via a pointer on it. The structure contains the configuration data of the PCI card being identified
 * by the bus, device and function number.
 * </description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsyspcisetconfigentry_struct
{
	RTS_IEC_WORD usBus;					/* VAR_INPUT */	/* <param name="usBus" type="IN">PCI bus number (index)</param> */
	RTS_IEC_WORD usDevice;				/* VAR_INPUT */	/* <param name="usDevice" type="IN">PCI device number (index)</param> */
	RTS_IEC_WORD usFunction;			/* VAR_INPUT */	/* <param name="usFunction" type="IN">PCI function number (index)</param> */
	PCI_INFO *pPciInfo;					/* VAR_INPUT */	/* <param name="pPciInfo" type="IN">Pointer to structure PCI_INFO containing information on the PCI card</param> */
	RTS_IEC_RESULT SysPciSetConfigEntry;	/* VAR_OUTPUT */	
} syspcisetconfigentry_struct;

DEF_API(`void',`CDECL',`syspcisetconfigentry',`(syspcisetconfigentry_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x7E2EC6CB),0x03050500)

/**
 * <description>Write one PCI config value
 * This function allows to set single configuration values of a PCI card via a pointer on the corresponding memory address (pbyData).
 * Therefore the bus entry associated to the PCI card is identified via the bus, device and function number. The bus entry is a
 * structure of type PCI_INFO.  The component to be read out is indicated by PciOffset.
 * </description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsyspciwritevalue_struct
{
	RTS_IEC_WORD usBus;					/* VAR_INPUT */	/* <param name="usBus" type="IN">PCI bus number (index)</param> */
	RTS_IEC_WORD usDevice;				/* VAR_INPUT */	/* <param name="usDevice" type="IN">PCI device number (index)</param> */
	RTS_IEC_WORD usFunction;			/* VAR_INPUT */	/* <param name="usFunction" type="IN">PCI function number (index)</param> */
	RTS_IEC_WORD usPciOffset;			/* VAR_INPUT */	/* <param name="usPciOffset" type="IN">Offset in the PCI config entry</param> */
	RTS_IEC_BYTE *pbyData;				/* VAR_INPUT */	/* <param name="pbyData" type="IN">Pointer to data to write to PCI</param> */
	RTS_IEC_WORD usSize;				/* VAR_INPUT */	/* <param name="usSize" type="IN">Size in byte of data to write</param> */
	RTS_IEC_RESULT SysPciWriteValue;	/* VAR_OUTPUT */	
} syspciwritevalue_struct;

DEF_API(`void',`CDECL',`syspciwritevalue',`(syspciwritevalue_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x2ABCA03C),0x03050500)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysPciOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysPciOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>Get PCI info of a specified card</description>
 * <param name="usVendorId" type="IN">PCI vendor number</param>
 * <param name="usDeviceId" type="IN">PCI device Id</param>
 * <param name="usCardIndex" type="IN">Card index number</param>
 * <param name="pPciInfo" type="OUT">PCI entry</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysPciGetCardInfo',`(unsigned short usVendorId, unsigned short usDeviceId, unsigned short usCardIndex, PCI_INFO *pPciInfo)')

/**
 * <description>Get one PCI config entry</description>
 * <param name="usBus" type="IN">PCI bus number (index)</param>
 * <param name="usDevice" type="IN">PCI device number (index)</param>
 * <param name="usFunction" type="IN">PCI function number (index)</param>
 * <param name="pPciInfo" type="OUT">PCI entry</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysPciGetConfigEntry',`(unsigned short usBus, unsigned short usDevice, unsigned short usFunction, PCI_INFO *pPciInfo)')

/**
 * <description>Set one PCI config entry</description>
 * <param name="usBus" type="IN">PCI bus number (index)</param>
 * <param name="usDevice" type="IN">PCI device number (index)</param>
 * <param name="usFunction" type="IN">PCI function number (index)</param>
 * <param name="pPciInfo" type="IN">PCI entry</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysPciSetConfigEntry',`(unsigned short usBus, unsigned short usDevice, unsigned short usFunction, PCI_INFO *pPciInfo)')

/**
 * <description>Write one PCI config value</description>
 * <param name="usBus" type="IN">PCI bus number (index)</param>
 * <param name="usDevice" type="IN">PCI device number (index)</param>
 * <param name="usFunction" type="IN">PCI function number (index)</param>
 * <param name="usPciOffset" type="IN">Offset in the PCI config entry</param>
 * <param name="pbyData" type="IN">Pointer to data to write to PCI</param>
 * <param name="usSize" type="IN">Size in byte of data to write</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysPciWriteValue',`(unsigned short usBus, unsigned short usDevice, unsigned short usFunction, unsigned short usPciOffset, unsigned char *pbyData, unsigned short usSize)')

/**
 * <description>Read one PCI config value</description>
 * <param name="usBus" type="IN">PCI bus number (index)</param>
 * <param name="usDevice" type="IN">PCI device number (index)</param>
 * <param name="usFunction" type="IN">PCI function number (index)</param>
 * <param name="usPciOffset" type="IN">Offset in the PCI config entry</param>
 * <param name="pbyData" type="OUT">Pointer to data to read to PCI</param>
 * <param name="usSize" type="IN">Size in byte of data to read</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysPciReadValue',`(unsigned short usBus, unsigned short usDevice, unsigned short usFunction, unsigned short usPciOffset, unsigned char *pbyData, unsigned short usSize)')

#ifdef __cplusplus
}
#endif
