 /**
 * <interfacename>SysPci</interfacename>
 * <description> 
 *	<p>The SysPci interface is projected to get access to the PCI bus on a target. This interface
 *	can only be used on architectures with a PCI bus.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _SYSPCIITF_H_
#define _SYSPCIITF_H_

#include "CmpStd.h"

 

 




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

void CDECL CDECL_EXT syspcigetcardinfo(syspcigetcardinfo_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSPCIGETCARDINFO_IEC) (syspcigetcardinfo_struct *p);
#if defined(SYSPCI_NOTIMPLEMENTED) || defined(SYSPCIGETCARDINFO_NOTIMPLEMENTED)
	#define USE_syspcigetcardinfo
	#define EXT_syspcigetcardinfo
	#define GET_syspcigetcardinfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syspcigetcardinfo(p0) 
	#define CHK_syspcigetcardinfo  FALSE
	#define EXP_syspcigetcardinfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syspcigetcardinfo
	#define EXT_syspcigetcardinfo
	#define GET_syspcigetcardinfo(fl)  CAL_CMGETAPI( "syspcigetcardinfo" ) 
	#define CAL_syspcigetcardinfo  syspcigetcardinfo
	#define CHK_syspcigetcardinfo  TRUE
	#define EXP_syspcigetcardinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspcigetcardinfo", (RTS_UINTPTR)syspcigetcardinfo, 1, RTSITF_GET_SIGNATURE(0, 0x4D7CD8E3), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSPCI_EXTERNAL)
	#define USE_syspcigetcardinfo
	#define EXT_syspcigetcardinfo
	#define GET_syspcigetcardinfo(fl)  CAL_CMGETAPI( "syspcigetcardinfo" ) 
	#define CAL_syspcigetcardinfo  syspcigetcardinfo
	#define CHK_syspcigetcardinfo  TRUE
	#define EXP_syspcigetcardinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspcigetcardinfo", (RTS_UINTPTR)syspcigetcardinfo, 1, RTSITF_GET_SIGNATURE(0, 0x4D7CD8E3), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysPcisyspcigetcardinfo
	#define EXT_SysPcisyspcigetcardinfo
	#define GET_SysPcisyspcigetcardinfo  ERR_OK
	#define CAL_SysPcisyspcigetcardinfo  syspcigetcardinfo
	#define CHK_SysPcisyspcigetcardinfo  TRUE
	#define EXP_SysPcisyspcigetcardinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspcigetcardinfo", (RTS_UINTPTR)syspcigetcardinfo, 1, RTSITF_GET_SIGNATURE(0, 0x4D7CD8E3), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_syspcigetcardinfo
	#define EXT_syspcigetcardinfo
	#define GET_syspcigetcardinfo(fl)  CAL_CMGETAPI( "syspcigetcardinfo" ) 
	#define CAL_syspcigetcardinfo  syspcigetcardinfo
	#define CHK_syspcigetcardinfo  TRUE
	#define EXP_syspcigetcardinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspcigetcardinfo", (RTS_UINTPTR)syspcigetcardinfo, 1, RTSITF_GET_SIGNATURE(0, 0x4D7CD8E3), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_syspcigetcardinfo  PFSYSPCIGETCARDINFO_IEC pfsyspcigetcardinfo;
	#define EXT_syspcigetcardinfo  extern PFSYSPCIGETCARDINFO_IEC pfsyspcigetcardinfo;
	#define GET_syspcigetcardinfo(fl)  s_pfCMGetAPI2( "syspcigetcardinfo", (RTS_VOID_FCTPTR *)&pfsyspcigetcardinfo, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x4D7CD8E3), 0x03050500)
	#define CAL_syspcigetcardinfo  pfsyspcigetcardinfo
	#define CHK_syspcigetcardinfo  (pfsyspcigetcardinfo != NULL)
	#define EXP_syspcigetcardinfo   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspcigetcardinfo", (RTS_UINTPTR)syspcigetcardinfo, 1, RTSITF_GET_SIGNATURE(0, 0x4D7CD8E3), 0x03050500) 
#endif


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

void CDECL CDECL_EXT syspcigetconfigentry(syspcigetconfigentry_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSPCIGETCONFIGENTRY_IEC) (syspcigetconfigentry_struct *p);
#if defined(SYSPCI_NOTIMPLEMENTED) || defined(SYSPCIGETCONFIGENTRY_NOTIMPLEMENTED)
	#define USE_syspcigetconfigentry
	#define EXT_syspcigetconfigentry
	#define GET_syspcigetconfigentry(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syspcigetconfigentry(p0) 
	#define CHK_syspcigetconfigentry  FALSE
	#define EXP_syspcigetconfigentry  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syspcigetconfigentry
	#define EXT_syspcigetconfigentry
	#define GET_syspcigetconfigentry(fl)  CAL_CMGETAPI( "syspcigetconfigentry" ) 
	#define CAL_syspcigetconfigentry  syspcigetconfigentry
	#define CHK_syspcigetconfigentry  TRUE
	#define EXP_syspcigetconfigentry  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspcigetconfigentry", (RTS_UINTPTR)syspcigetconfigentry, 1, RTSITF_GET_SIGNATURE(0, 0x1B98EF98), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSPCI_EXTERNAL)
	#define USE_syspcigetconfigentry
	#define EXT_syspcigetconfigentry
	#define GET_syspcigetconfigentry(fl)  CAL_CMGETAPI( "syspcigetconfigentry" ) 
	#define CAL_syspcigetconfigentry  syspcigetconfigentry
	#define CHK_syspcigetconfigentry  TRUE
	#define EXP_syspcigetconfigentry  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspcigetconfigentry", (RTS_UINTPTR)syspcigetconfigentry, 1, RTSITF_GET_SIGNATURE(0, 0x1B98EF98), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysPcisyspcigetconfigentry
	#define EXT_SysPcisyspcigetconfigentry
	#define GET_SysPcisyspcigetconfigentry  ERR_OK
	#define CAL_SysPcisyspcigetconfigentry  syspcigetconfigentry
	#define CHK_SysPcisyspcigetconfigentry  TRUE
	#define EXP_SysPcisyspcigetconfigentry  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspcigetconfigentry", (RTS_UINTPTR)syspcigetconfigentry, 1, RTSITF_GET_SIGNATURE(0, 0x1B98EF98), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_syspcigetconfigentry
	#define EXT_syspcigetconfigentry
	#define GET_syspcigetconfigentry(fl)  CAL_CMGETAPI( "syspcigetconfigentry" ) 
	#define CAL_syspcigetconfigentry  syspcigetconfigentry
	#define CHK_syspcigetconfigentry  TRUE
	#define EXP_syspcigetconfigentry  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspcigetconfigentry", (RTS_UINTPTR)syspcigetconfigentry, 1, RTSITF_GET_SIGNATURE(0, 0x1B98EF98), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_syspcigetconfigentry  PFSYSPCIGETCONFIGENTRY_IEC pfsyspcigetconfigentry;
	#define EXT_syspcigetconfigentry  extern PFSYSPCIGETCONFIGENTRY_IEC pfsyspcigetconfigentry;
	#define GET_syspcigetconfigentry(fl)  s_pfCMGetAPI2( "syspcigetconfigentry", (RTS_VOID_FCTPTR *)&pfsyspcigetconfigentry, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x1B98EF98), 0x03050500)
	#define CAL_syspcigetconfigentry  pfsyspcigetconfigentry
	#define CHK_syspcigetconfigentry  (pfsyspcigetconfigentry != NULL)
	#define EXP_syspcigetconfigentry   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspcigetconfigentry", (RTS_UINTPTR)syspcigetconfigentry, 1, RTSITF_GET_SIGNATURE(0, 0x1B98EF98), 0x03050500) 
#endif


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

void CDECL CDECL_EXT syspcireadvalue(syspcireadvalue_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSPCIREADVALUE_IEC) (syspcireadvalue_struct *p);
#if defined(SYSPCI_NOTIMPLEMENTED) || defined(SYSPCIREADVALUE_NOTIMPLEMENTED)
	#define USE_syspcireadvalue
	#define EXT_syspcireadvalue
	#define GET_syspcireadvalue(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syspcireadvalue(p0) 
	#define CHK_syspcireadvalue  FALSE
	#define EXP_syspcireadvalue  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syspcireadvalue
	#define EXT_syspcireadvalue
	#define GET_syspcireadvalue(fl)  CAL_CMGETAPI( "syspcireadvalue" ) 
	#define CAL_syspcireadvalue  syspcireadvalue
	#define CHK_syspcireadvalue  TRUE
	#define EXP_syspcireadvalue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspcireadvalue", (RTS_UINTPTR)syspcireadvalue, 1, RTSITF_GET_SIGNATURE(0, 0x622E6E70), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSPCI_EXTERNAL)
	#define USE_syspcireadvalue
	#define EXT_syspcireadvalue
	#define GET_syspcireadvalue(fl)  CAL_CMGETAPI( "syspcireadvalue" ) 
	#define CAL_syspcireadvalue  syspcireadvalue
	#define CHK_syspcireadvalue  TRUE
	#define EXP_syspcireadvalue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspcireadvalue", (RTS_UINTPTR)syspcireadvalue, 1, RTSITF_GET_SIGNATURE(0, 0x622E6E70), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysPcisyspcireadvalue
	#define EXT_SysPcisyspcireadvalue
	#define GET_SysPcisyspcireadvalue  ERR_OK
	#define CAL_SysPcisyspcireadvalue  syspcireadvalue
	#define CHK_SysPcisyspcireadvalue  TRUE
	#define EXP_SysPcisyspcireadvalue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspcireadvalue", (RTS_UINTPTR)syspcireadvalue, 1, RTSITF_GET_SIGNATURE(0, 0x622E6E70), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_syspcireadvalue
	#define EXT_syspcireadvalue
	#define GET_syspcireadvalue(fl)  CAL_CMGETAPI( "syspcireadvalue" ) 
	#define CAL_syspcireadvalue  syspcireadvalue
	#define CHK_syspcireadvalue  TRUE
	#define EXP_syspcireadvalue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspcireadvalue", (RTS_UINTPTR)syspcireadvalue, 1, RTSITF_GET_SIGNATURE(0, 0x622E6E70), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_syspcireadvalue  PFSYSPCIREADVALUE_IEC pfsyspcireadvalue;
	#define EXT_syspcireadvalue  extern PFSYSPCIREADVALUE_IEC pfsyspcireadvalue;
	#define GET_syspcireadvalue(fl)  s_pfCMGetAPI2( "syspcireadvalue", (RTS_VOID_FCTPTR *)&pfsyspcireadvalue, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x622E6E70), 0x03050500)
	#define CAL_syspcireadvalue  pfsyspcireadvalue
	#define CHK_syspcireadvalue  (pfsyspcireadvalue != NULL)
	#define EXP_syspcireadvalue   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspcireadvalue", (RTS_UINTPTR)syspcireadvalue, 1, RTSITF_GET_SIGNATURE(0, 0x622E6E70), 0x03050500) 
#endif


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

void CDECL CDECL_EXT syspcisetconfigentry(syspcisetconfigentry_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSPCISETCONFIGENTRY_IEC) (syspcisetconfigentry_struct *p);
#if defined(SYSPCI_NOTIMPLEMENTED) || defined(SYSPCISETCONFIGENTRY_NOTIMPLEMENTED)
	#define USE_syspcisetconfigentry
	#define EXT_syspcisetconfigentry
	#define GET_syspcisetconfigentry(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syspcisetconfigentry(p0) 
	#define CHK_syspcisetconfigentry  FALSE
	#define EXP_syspcisetconfigentry  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syspcisetconfigentry
	#define EXT_syspcisetconfigentry
	#define GET_syspcisetconfigentry(fl)  CAL_CMGETAPI( "syspcisetconfigentry" ) 
	#define CAL_syspcisetconfigentry  syspcisetconfigentry
	#define CHK_syspcisetconfigentry  TRUE
	#define EXP_syspcisetconfigentry  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspcisetconfigentry", (RTS_UINTPTR)syspcisetconfigentry, 1, RTSITF_GET_SIGNATURE(0, 0x7E2EC6CB), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSPCI_EXTERNAL)
	#define USE_syspcisetconfigentry
	#define EXT_syspcisetconfigentry
	#define GET_syspcisetconfigentry(fl)  CAL_CMGETAPI( "syspcisetconfigentry" ) 
	#define CAL_syspcisetconfigentry  syspcisetconfigentry
	#define CHK_syspcisetconfigentry  TRUE
	#define EXP_syspcisetconfigentry  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspcisetconfigentry", (RTS_UINTPTR)syspcisetconfigentry, 1, RTSITF_GET_SIGNATURE(0, 0x7E2EC6CB), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysPcisyspcisetconfigentry
	#define EXT_SysPcisyspcisetconfigentry
	#define GET_SysPcisyspcisetconfigentry  ERR_OK
	#define CAL_SysPcisyspcisetconfigentry  syspcisetconfigentry
	#define CHK_SysPcisyspcisetconfigentry  TRUE
	#define EXP_SysPcisyspcisetconfigentry  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspcisetconfigentry", (RTS_UINTPTR)syspcisetconfigentry, 1, RTSITF_GET_SIGNATURE(0, 0x7E2EC6CB), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_syspcisetconfigentry
	#define EXT_syspcisetconfigentry
	#define GET_syspcisetconfigentry(fl)  CAL_CMGETAPI( "syspcisetconfigentry" ) 
	#define CAL_syspcisetconfigentry  syspcisetconfigentry
	#define CHK_syspcisetconfigentry  TRUE
	#define EXP_syspcisetconfigentry  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspcisetconfigentry", (RTS_UINTPTR)syspcisetconfigentry, 1, RTSITF_GET_SIGNATURE(0, 0x7E2EC6CB), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_syspcisetconfigentry  PFSYSPCISETCONFIGENTRY_IEC pfsyspcisetconfigentry;
	#define EXT_syspcisetconfigentry  extern PFSYSPCISETCONFIGENTRY_IEC pfsyspcisetconfigentry;
	#define GET_syspcisetconfigentry(fl)  s_pfCMGetAPI2( "syspcisetconfigentry", (RTS_VOID_FCTPTR *)&pfsyspcisetconfigentry, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x7E2EC6CB), 0x03050500)
	#define CAL_syspcisetconfigentry  pfsyspcisetconfigentry
	#define CHK_syspcisetconfigentry  (pfsyspcisetconfigentry != NULL)
	#define EXP_syspcisetconfigentry   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspcisetconfigentry", (RTS_UINTPTR)syspcisetconfigentry, 1, RTSITF_GET_SIGNATURE(0, 0x7E2EC6CB), 0x03050500) 
#endif


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

void CDECL CDECL_EXT syspciwritevalue(syspciwritevalue_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSPCIWRITEVALUE_IEC) (syspciwritevalue_struct *p);
#if defined(SYSPCI_NOTIMPLEMENTED) || defined(SYSPCIWRITEVALUE_NOTIMPLEMENTED)
	#define USE_syspciwritevalue
	#define EXT_syspciwritevalue
	#define GET_syspciwritevalue(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syspciwritevalue(p0) 
	#define CHK_syspciwritevalue  FALSE
	#define EXP_syspciwritevalue  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syspciwritevalue
	#define EXT_syspciwritevalue
	#define GET_syspciwritevalue(fl)  CAL_CMGETAPI( "syspciwritevalue" ) 
	#define CAL_syspciwritevalue  syspciwritevalue
	#define CHK_syspciwritevalue  TRUE
	#define EXP_syspciwritevalue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspciwritevalue", (RTS_UINTPTR)syspciwritevalue, 1, RTSITF_GET_SIGNATURE(0, 0x2ABCA03C), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSPCI_EXTERNAL)
	#define USE_syspciwritevalue
	#define EXT_syspciwritevalue
	#define GET_syspciwritevalue(fl)  CAL_CMGETAPI( "syspciwritevalue" ) 
	#define CAL_syspciwritevalue  syspciwritevalue
	#define CHK_syspciwritevalue  TRUE
	#define EXP_syspciwritevalue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspciwritevalue", (RTS_UINTPTR)syspciwritevalue, 1, RTSITF_GET_SIGNATURE(0, 0x2ABCA03C), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysPcisyspciwritevalue
	#define EXT_SysPcisyspciwritevalue
	#define GET_SysPcisyspciwritevalue  ERR_OK
	#define CAL_SysPcisyspciwritevalue  syspciwritevalue
	#define CHK_SysPcisyspciwritevalue  TRUE
	#define EXP_SysPcisyspciwritevalue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspciwritevalue", (RTS_UINTPTR)syspciwritevalue, 1, RTSITF_GET_SIGNATURE(0, 0x2ABCA03C), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_syspciwritevalue
	#define EXT_syspciwritevalue
	#define GET_syspciwritevalue(fl)  CAL_CMGETAPI( "syspciwritevalue" ) 
	#define CAL_syspciwritevalue  syspciwritevalue
	#define CHK_syspciwritevalue  TRUE
	#define EXP_syspciwritevalue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspciwritevalue", (RTS_UINTPTR)syspciwritevalue, 1, RTSITF_GET_SIGNATURE(0, 0x2ABCA03C), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_syspciwritevalue  PFSYSPCIWRITEVALUE_IEC pfsyspciwritevalue;
	#define EXT_syspciwritevalue  extern PFSYSPCIWRITEVALUE_IEC pfsyspciwritevalue;
	#define GET_syspciwritevalue(fl)  s_pfCMGetAPI2( "syspciwritevalue", (RTS_VOID_FCTPTR *)&pfsyspciwritevalue, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x2ABCA03C), 0x03050500)
	#define CAL_syspciwritevalue  pfsyspciwritevalue
	#define CHK_syspciwritevalue  (pfsyspciwritevalue != NULL)
	#define EXP_syspciwritevalue   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syspciwritevalue", (RTS_UINTPTR)syspciwritevalue, 1, RTSITF_GET_SIGNATURE(0, 0x2ABCA03C), 0x03050500) 
#endif


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
RTS_RESULT CDECL SysPciGetCardInfo(unsigned short usVendorId, unsigned short usDeviceId, unsigned short usCardIndex, PCI_INFO *pPciInfo);
typedef RTS_RESULT (CDECL * PFSYSPCIGETCARDINFO) (unsigned short usVendorId, unsigned short usDeviceId, unsigned short usCardIndex, PCI_INFO *pPciInfo);
#if defined(SYSPCI_NOTIMPLEMENTED) || defined(SYSPCIGETCARDINFO_NOTIMPLEMENTED)
	#define USE_SysPciGetCardInfo
	#define EXT_SysPciGetCardInfo
	#define GET_SysPciGetCardInfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysPciGetCardInfo(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysPciGetCardInfo  FALSE
	#define EXP_SysPciGetCardInfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysPciGetCardInfo
	#define EXT_SysPciGetCardInfo
	#define GET_SysPciGetCardInfo(fl)  CAL_CMGETAPI( "SysPciGetCardInfo" ) 
	#define CAL_SysPciGetCardInfo  SysPciGetCardInfo
	#define CHK_SysPciGetCardInfo  TRUE
	#define EXP_SysPciGetCardInfo  CAL_CMEXPAPI( "SysPciGetCardInfo" ) 
#elif defined(MIXED_LINK) && !defined(SYSPCI_EXTERNAL)
	#define USE_SysPciGetCardInfo
	#define EXT_SysPciGetCardInfo
	#define GET_SysPciGetCardInfo(fl)  CAL_CMGETAPI( "SysPciGetCardInfo" ) 
	#define CAL_SysPciGetCardInfo  SysPciGetCardInfo
	#define CHK_SysPciGetCardInfo  TRUE
	#define EXP_SysPciGetCardInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysPciGetCardInfo", (RTS_UINTPTR)SysPciGetCardInfo, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysPciSysPciGetCardInfo
	#define EXT_SysPciSysPciGetCardInfo
	#define GET_SysPciSysPciGetCardInfo  ERR_OK
	#define CAL_SysPciSysPciGetCardInfo pISysPci->ISysPciGetCardInfo
	#define CHK_SysPciSysPciGetCardInfo (pISysPci != NULL)
	#define EXP_SysPciSysPciGetCardInfo  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysPciGetCardInfo
	#define EXT_SysPciGetCardInfo
	#define GET_SysPciGetCardInfo(fl)  CAL_CMGETAPI( "SysPciGetCardInfo" ) 
	#define CAL_SysPciGetCardInfo pISysPci->ISysPciGetCardInfo
	#define CHK_SysPciGetCardInfo (pISysPci != NULL)
	#define EXP_SysPciGetCardInfo  CAL_CMEXPAPI( "SysPciGetCardInfo" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysPciGetCardInfo  PFSYSPCIGETCARDINFO pfSysPciGetCardInfo;
	#define EXT_SysPciGetCardInfo  extern PFSYSPCIGETCARDINFO pfSysPciGetCardInfo;
	#define GET_SysPciGetCardInfo(fl)  s_pfCMGetAPI2( "SysPciGetCardInfo", (RTS_VOID_FCTPTR *)&pfSysPciGetCardInfo, (fl), 0, 0)
	#define CAL_SysPciGetCardInfo  pfSysPciGetCardInfo
	#define CHK_SysPciGetCardInfo  (pfSysPciGetCardInfo != NULL)
	#define EXP_SysPciGetCardInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysPciGetCardInfo", (RTS_UINTPTR)SysPciGetCardInfo, 0, 0) 
#endif




/**
 * <description>Get one PCI config entry</description>
 * <param name="usBus" type="IN">PCI bus number (index)</param>
 * <param name="usDevice" type="IN">PCI device number (index)</param>
 * <param name="usFunction" type="IN">PCI function number (index)</param>
 * <param name="pPciInfo" type="OUT">PCI entry</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysPciGetConfigEntry(unsigned short usBus, unsigned short usDevice, unsigned short usFunction, PCI_INFO *pPciInfo);
typedef RTS_RESULT (CDECL * PFSYSPCIGETCONFIGENTRY) (unsigned short usBus, unsigned short usDevice, unsigned short usFunction, PCI_INFO *pPciInfo);
#if defined(SYSPCI_NOTIMPLEMENTED) || defined(SYSPCIGETCONFIGENTRY_NOTIMPLEMENTED)
	#define USE_SysPciGetConfigEntry
	#define EXT_SysPciGetConfigEntry
	#define GET_SysPciGetConfigEntry(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysPciGetConfigEntry(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysPciGetConfigEntry  FALSE
	#define EXP_SysPciGetConfigEntry  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysPciGetConfigEntry
	#define EXT_SysPciGetConfigEntry
	#define GET_SysPciGetConfigEntry(fl)  CAL_CMGETAPI( "SysPciGetConfigEntry" ) 
	#define CAL_SysPciGetConfigEntry  SysPciGetConfigEntry
	#define CHK_SysPciGetConfigEntry  TRUE
	#define EXP_SysPciGetConfigEntry  CAL_CMEXPAPI( "SysPciGetConfigEntry" ) 
#elif defined(MIXED_LINK) && !defined(SYSPCI_EXTERNAL)
	#define USE_SysPciGetConfigEntry
	#define EXT_SysPciGetConfigEntry
	#define GET_SysPciGetConfigEntry(fl)  CAL_CMGETAPI( "SysPciGetConfigEntry" ) 
	#define CAL_SysPciGetConfigEntry  SysPciGetConfigEntry
	#define CHK_SysPciGetConfigEntry  TRUE
	#define EXP_SysPciGetConfigEntry  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysPciGetConfigEntry", (RTS_UINTPTR)SysPciGetConfigEntry, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysPciSysPciGetConfigEntry
	#define EXT_SysPciSysPciGetConfigEntry
	#define GET_SysPciSysPciGetConfigEntry  ERR_OK
	#define CAL_SysPciSysPciGetConfigEntry pISysPci->ISysPciGetConfigEntry
	#define CHK_SysPciSysPciGetConfigEntry (pISysPci != NULL)
	#define EXP_SysPciSysPciGetConfigEntry  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysPciGetConfigEntry
	#define EXT_SysPciGetConfigEntry
	#define GET_SysPciGetConfigEntry(fl)  CAL_CMGETAPI( "SysPciGetConfigEntry" ) 
	#define CAL_SysPciGetConfigEntry pISysPci->ISysPciGetConfigEntry
	#define CHK_SysPciGetConfigEntry (pISysPci != NULL)
	#define EXP_SysPciGetConfigEntry  CAL_CMEXPAPI( "SysPciGetConfigEntry" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysPciGetConfigEntry  PFSYSPCIGETCONFIGENTRY pfSysPciGetConfigEntry;
	#define EXT_SysPciGetConfigEntry  extern PFSYSPCIGETCONFIGENTRY pfSysPciGetConfigEntry;
	#define GET_SysPciGetConfigEntry(fl)  s_pfCMGetAPI2( "SysPciGetConfigEntry", (RTS_VOID_FCTPTR *)&pfSysPciGetConfigEntry, (fl), 0, 0)
	#define CAL_SysPciGetConfigEntry  pfSysPciGetConfigEntry
	#define CHK_SysPciGetConfigEntry  (pfSysPciGetConfigEntry != NULL)
	#define EXP_SysPciGetConfigEntry  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysPciGetConfigEntry", (RTS_UINTPTR)SysPciGetConfigEntry, 0, 0) 
#endif




/**
 * <description>Set one PCI config entry</description>
 * <param name="usBus" type="IN">PCI bus number (index)</param>
 * <param name="usDevice" type="IN">PCI device number (index)</param>
 * <param name="usFunction" type="IN">PCI function number (index)</param>
 * <param name="pPciInfo" type="IN">PCI entry</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysPciSetConfigEntry(unsigned short usBus, unsigned short usDevice, unsigned short usFunction, PCI_INFO *pPciInfo);
typedef RTS_RESULT (CDECL * PFSYSPCISETCONFIGENTRY) (unsigned short usBus, unsigned short usDevice, unsigned short usFunction, PCI_INFO *pPciInfo);
#if defined(SYSPCI_NOTIMPLEMENTED) || defined(SYSPCISETCONFIGENTRY_NOTIMPLEMENTED)
	#define USE_SysPciSetConfigEntry
	#define EXT_SysPciSetConfigEntry
	#define GET_SysPciSetConfigEntry(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysPciSetConfigEntry(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysPciSetConfigEntry  FALSE
	#define EXP_SysPciSetConfigEntry  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysPciSetConfigEntry
	#define EXT_SysPciSetConfigEntry
	#define GET_SysPciSetConfigEntry(fl)  CAL_CMGETAPI( "SysPciSetConfigEntry" ) 
	#define CAL_SysPciSetConfigEntry  SysPciSetConfigEntry
	#define CHK_SysPciSetConfigEntry  TRUE
	#define EXP_SysPciSetConfigEntry  CAL_CMEXPAPI( "SysPciSetConfigEntry" ) 
#elif defined(MIXED_LINK) && !defined(SYSPCI_EXTERNAL)
	#define USE_SysPciSetConfigEntry
	#define EXT_SysPciSetConfigEntry
	#define GET_SysPciSetConfigEntry(fl)  CAL_CMGETAPI( "SysPciSetConfigEntry" ) 
	#define CAL_SysPciSetConfigEntry  SysPciSetConfigEntry
	#define CHK_SysPciSetConfigEntry  TRUE
	#define EXP_SysPciSetConfigEntry  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysPciSetConfigEntry", (RTS_UINTPTR)SysPciSetConfigEntry, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysPciSysPciSetConfigEntry
	#define EXT_SysPciSysPciSetConfigEntry
	#define GET_SysPciSysPciSetConfigEntry  ERR_OK
	#define CAL_SysPciSysPciSetConfigEntry pISysPci->ISysPciSetConfigEntry
	#define CHK_SysPciSysPciSetConfigEntry (pISysPci != NULL)
	#define EXP_SysPciSysPciSetConfigEntry  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysPciSetConfigEntry
	#define EXT_SysPciSetConfigEntry
	#define GET_SysPciSetConfigEntry(fl)  CAL_CMGETAPI( "SysPciSetConfigEntry" ) 
	#define CAL_SysPciSetConfigEntry pISysPci->ISysPciSetConfigEntry
	#define CHK_SysPciSetConfigEntry (pISysPci != NULL)
	#define EXP_SysPciSetConfigEntry  CAL_CMEXPAPI( "SysPciSetConfigEntry" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysPciSetConfigEntry  PFSYSPCISETCONFIGENTRY pfSysPciSetConfigEntry;
	#define EXT_SysPciSetConfigEntry  extern PFSYSPCISETCONFIGENTRY pfSysPciSetConfigEntry;
	#define GET_SysPciSetConfigEntry(fl)  s_pfCMGetAPI2( "SysPciSetConfigEntry", (RTS_VOID_FCTPTR *)&pfSysPciSetConfigEntry, (fl), 0, 0)
	#define CAL_SysPciSetConfigEntry  pfSysPciSetConfigEntry
	#define CHK_SysPciSetConfigEntry  (pfSysPciSetConfigEntry != NULL)
	#define EXP_SysPciSetConfigEntry  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysPciSetConfigEntry", (RTS_UINTPTR)SysPciSetConfigEntry, 0, 0) 
#endif




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
RTS_RESULT CDECL SysPciWriteValue(unsigned short usBus, unsigned short usDevice, unsigned short usFunction, unsigned short usPciOffset, unsigned char *pbyData, unsigned short usSize);
typedef RTS_RESULT (CDECL * PFSYSPCIWRITEVALUE) (unsigned short usBus, unsigned short usDevice, unsigned short usFunction, unsigned short usPciOffset, unsigned char *pbyData, unsigned short usSize);
#if defined(SYSPCI_NOTIMPLEMENTED) || defined(SYSPCIWRITEVALUE_NOTIMPLEMENTED)
	#define USE_SysPciWriteValue
	#define EXT_SysPciWriteValue
	#define GET_SysPciWriteValue(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysPciWriteValue(p0,p1,p2,p3,p4,p5)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysPciWriteValue  FALSE
	#define EXP_SysPciWriteValue  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysPciWriteValue
	#define EXT_SysPciWriteValue
	#define GET_SysPciWriteValue(fl)  CAL_CMGETAPI( "SysPciWriteValue" ) 
	#define CAL_SysPciWriteValue  SysPciWriteValue
	#define CHK_SysPciWriteValue  TRUE
	#define EXP_SysPciWriteValue  CAL_CMEXPAPI( "SysPciWriteValue" ) 
#elif defined(MIXED_LINK) && !defined(SYSPCI_EXTERNAL)
	#define USE_SysPciWriteValue
	#define EXT_SysPciWriteValue
	#define GET_SysPciWriteValue(fl)  CAL_CMGETAPI( "SysPciWriteValue" ) 
	#define CAL_SysPciWriteValue  SysPciWriteValue
	#define CHK_SysPciWriteValue  TRUE
	#define EXP_SysPciWriteValue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysPciWriteValue", (RTS_UINTPTR)SysPciWriteValue, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysPciSysPciWriteValue
	#define EXT_SysPciSysPciWriteValue
	#define GET_SysPciSysPciWriteValue  ERR_OK
	#define CAL_SysPciSysPciWriteValue pISysPci->ISysPciWriteValue
	#define CHK_SysPciSysPciWriteValue (pISysPci != NULL)
	#define EXP_SysPciSysPciWriteValue  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysPciWriteValue
	#define EXT_SysPciWriteValue
	#define GET_SysPciWriteValue(fl)  CAL_CMGETAPI( "SysPciWriteValue" ) 
	#define CAL_SysPciWriteValue pISysPci->ISysPciWriteValue
	#define CHK_SysPciWriteValue (pISysPci != NULL)
	#define EXP_SysPciWriteValue  CAL_CMEXPAPI( "SysPciWriteValue" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysPciWriteValue  PFSYSPCIWRITEVALUE pfSysPciWriteValue;
	#define EXT_SysPciWriteValue  extern PFSYSPCIWRITEVALUE pfSysPciWriteValue;
	#define GET_SysPciWriteValue(fl)  s_pfCMGetAPI2( "SysPciWriteValue", (RTS_VOID_FCTPTR *)&pfSysPciWriteValue, (fl), 0, 0)
	#define CAL_SysPciWriteValue  pfSysPciWriteValue
	#define CHK_SysPciWriteValue  (pfSysPciWriteValue != NULL)
	#define EXP_SysPciWriteValue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysPciWriteValue", (RTS_UINTPTR)SysPciWriteValue, 0, 0) 
#endif




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
RTS_RESULT CDECL SysPciReadValue(unsigned short usBus, unsigned short usDevice, unsigned short usFunction, unsigned short usPciOffset, unsigned char *pbyData, unsigned short usSize);
typedef RTS_RESULT (CDECL * PFSYSPCIREADVALUE) (unsigned short usBus, unsigned short usDevice, unsigned short usFunction, unsigned short usPciOffset, unsigned char *pbyData, unsigned short usSize);
#if defined(SYSPCI_NOTIMPLEMENTED) || defined(SYSPCIREADVALUE_NOTIMPLEMENTED)
	#define USE_SysPciReadValue
	#define EXT_SysPciReadValue
	#define GET_SysPciReadValue(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysPciReadValue(p0,p1,p2,p3,p4,p5)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysPciReadValue  FALSE
	#define EXP_SysPciReadValue  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysPciReadValue
	#define EXT_SysPciReadValue
	#define GET_SysPciReadValue(fl)  CAL_CMGETAPI( "SysPciReadValue" ) 
	#define CAL_SysPciReadValue  SysPciReadValue
	#define CHK_SysPciReadValue  TRUE
	#define EXP_SysPciReadValue  CAL_CMEXPAPI( "SysPciReadValue" ) 
#elif defined(MIXED_LINK) && !defined(SYSPCI_EXTERNAL)
	#define USE_SysPciReadValue
	#define EXT_SysPciReadValue
	#define GET_SysPciReadValue(fl)  CAL_CMGETAPI( "SysPciReadValue" ) 
	#define CAL_SysPciReadValue  SysPciReadValue
	#define CHK_SysPciReadValue  TRUE
	#define EXP_SysPciReadValue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysPciReadValue", (RTS_UINTPTR)SysPciReadValue, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysPciSysPciReadValue
	#define EXT_SysPciSysPciReadValue
	#define GET_SysPciSysPciReadValue  ERR_OK
	#define CAL_SysPciSysPciReadValue pISysPci->ISysPciReadValue
	#define CHK_SysPciSysPciReadValue (pISysPci != NULL)
	#define EXP_SysPciSysPciReadValue  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysPciReadValue
	#define EXT_SysPciReadValue
	#define GET_SysPciReadValue(fl)  CAL_CMGETAPI( "SysPciReadValue" ) 
	#define CAL_SysPciReadValue pISysPci->ISysPciReadValue
	#define CHK_SysPciReadValue (pISysPci != NULL)
	#define EXP_SysPciReadValue  CAL_CMEXPAPI( "SysPciReadValue" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysPciReadValue  PFSYSPCIREADVALUE pfSysPciReadValue;
	#define EXT_SysPciReadValue  extern PFSYSPCIREADVALUE pfSysPciReadValue;
	#define GET_SysPciReadValue(fl)  s_pfCMGetAPI2( "SysPciReadValue", (RTS_VOID_FCTPTR *)&pfSysPciReadValue, (fl), 0, 0)
	#define CAL_SysPciReadValue  pfSysPciReadValue
	#define CHK_SysPciReadValue  (pfSysPciReadValue != NULL)
	#define EXP_SysPciReadValue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysPciReadValue", (RTS_UINTPTR)SysPciReadValue, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSYSPCIGETCARDINFO ISysPciGetCardInfo;
 	PFSYSPCIGETCONFIGENTRY ISysPciGetConfigEntry;
 	PFSYSPCISETCONFIGENTRY ISysPciSetConfigEntry;
 	PFSYSPCIWRITEVALUE ISysPciWriteValue;
 	PFSYSPCIREADVALUE ISysPciReadValue;
 } ISysPci_C;

#ifdef CPLUSPLUS
class ISysPci : public IBase
{
	public:
		virtual RTS_RESULT CDECL ISysPciGetCardInfo(unsigned short usVendorId, unsigned short usDeviceId, unsigned short usCardIndex, PCI_INFO *pPciInfo) =0;
		virtual RTS_RESULT CDECL ISysPciGetConfigEntry(unsigned short usBus, unsigned short usDevice, unsigned short usFunction, PCI_INFO *pPciInfo) =0;
		virtual RTS_RESULT CDECL ISysPciSetConfigEntry(unsigned short usBus, unsigned short usDevice, unsigned short usFunction, PCI_INFO *pPciInfo) =0;
		virtual RTS_RESULT CDECL ISysPciWriteValue(unsigned short usBus, unsigned short usDevice, unsigned short usFunction, unsigned short usPciOffset, unsigned char *pbyData, unsigned short usSize) =0;
		virtual RTS_RESULT CDECL ISysPciReadValue(unsigned short usBus, unsigned short usDevice, unsigned short usFunction, unsigned short usPciOffset, unsigned char *pbyData, unsigned short usSize) =0;
};
	#ifndef ITF_SysPci
		#define ITF_SysPci static ISysPci *pISysPci = NULL;
	#endif
	#define EXTITF_SysPci
#else	/*CPLUSPLUS*/
	typedef ISysPci_C		ISysPci;
	#ifndef ITF_SysPci
		#define ITF_SysPci
	#endif
	#define EXTITF_SysPci
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSPCIITF_H_*/
