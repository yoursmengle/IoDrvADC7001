 /**
 * <interfacename>SysShm</interfacename>
 * <description> 
 *	<p>The SysShm interface is projected to handle access to shared memory.
 *	Shared memory could be physical memory (e.g. IO-cards) or a memory, that can be shared
 *	between several processes or tasks.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _SYSSHMITF_H_
#define _SYSSHMITF_H_

#include "CmpStd.h"

 

 




#include "CmpStd.h"

#ifndef SHM_NUM_OF_STATIC_OBJECTS		
	#define SHM_NUM_OF_STATIC_OBJECTS		5
#endif

/**
 * <category>Static defines</category>
 * <description>Text used as part of the name of a shared memory object, e.g. in IO drivers </description>
 */
#ifndef SHM_PCI_BUSNUMBER_STRING
	#define SHM_PCI_BUSNUMBER_STRING		"_PCIBusNr"
#endif

/**
 * <category>Static defines</category>
 * <description>A special text that can be used to inform that we don't have a PCI bus, 
 * but something to be mapped differently.
 * Example: non-PCI SJA1000 CAN controller under Windows CE
 * Here you have to specify 
 * [CmpSJACanDrv] 
 * 0.Name=NoPCIBus
 * </description>
 */
#ifndef SHM_NO_PCI_BUS_STRING
	#define SHM_NO_PCI_BUS_STRING		"NoPCIBus"
#endif


/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * Use MapPhysical Flag for memory mapping. Only used for WinCE.
 * 0: Do not use the flag
 * 1: Use the flag
 * </description>
 */
#define	SYSSHMKEY_INT_WINCE_MAP_PHYSICAL					"WinCE.MapPhysical"
#define	SYSSHMVALUE_INT_WINCE_DEFAULT_MAP_PHYSICAL			0

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * Do not use PAGE_PHYSICAL Flag for the call of VirtualAllocCopyEx in the memory mapping. Only used for WinCE.
 * 0: The PAGE_PHYSICAL Flag for VirtualAllocCopyEx is used if WinCE.MapPhysical is set
 * 1: The PAGE_PHYSICAL Flag for VirtualAllocCopyEx is not used also if WinCE.MapPhysical is set
 * </description>
 */
#define	SYSSHMKEY_INT_WINCE_DISABLE_MAP_PHYSICAL_IN_VIRTUALALLOCCOPYEX					"WinCE.DisableMapPhysicalInVirtualAllocCopyEx"
#define	SYSSHMVALUE_INT_WINCE_DEFAULT_DISABLE_MAP_PHYSICAL_IN_VIRTUALALLOCCOPYEX		0

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * Do not use PAGE_PHYSICAL access protection flag for the call of VirtualAllocCopyEx and VirtualCopy in the memory mapping.
 * Default: 0.
 * Only used for WinCE.
 * 0: Use the PAGE_NOCACHE access protection flag for VirtualAllocCopyEx and VirtualCopy.
 * 1: Do not use the PAGE_NOCACHE access protection flag for VirtualAllocCopyEx and VirtualCopy.
 * </description>
 */
#define	SYSSHMKEY_INT_WINCE_CACHED_MEM_MAPPING					"WinCE.CachedMemMapping"
#define	SYSSHMVALUE_INT_WINCE_DEFAULT_CACHED_MEM_MAPPING		0

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * Change the kernel memory's access permissions to "Full access" and its page attributes to "write-through/no write allocate" for direct kernel memory access from user space.
 * Default: 0.
 * Only used for WinCE.
 * 0: Do not set kernel memory attributes "full permission" and "write-through/no write-alloc".
 * 1: Set kernel memory attributes: "full permission" and "write-through/no write-alloc".
 * </description>
 */
#define	SYSSHMKEY_INT_WINCE_DIRECT_KERNELMEM_ACCESS					"WinCE.DirectKernelMemAccess"
#define	SYSSHMVALUE_INT_WINCE_DEFAULT_DIRECT_KERNELMEM_ACCESS		0

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * Use an Divisor to calculate the mapping address. Only used for WinCE.
 * 1: Default. Do not use 0
 * </description>
 */
#define	SYSSHMKEY_INT_WINCE_PHYSICAL_ADDRESS_DIVISOR				"WinCE.DividePhysicalAddressBy"
#define	SYSSHMVALUE_INT_WINCE_DEFAULT_PHYSICAL_ADDRESS_DIVISOR		1

/**
 * <category>Shared memory object</category>
 * <element name="pszName" type="IN">Name of the shared memory</element>
 * <element name="ulPhysicalAddress" type="IN">Physical memory address</element>
 * <element name="pMemory" type="IN">Pointer to the shared memory</element>
 * <element name="uiSize" type="IN">Size of the shared memory</element>
 * <element name="iRefCount" type="IN">Reference counter to store number of used clients</element>
 * <element name="ulHandle" type="IN">Operating system handle to the shared memory</element>
 */
typedef struct
{
	char* pszName;
	RTS_UINTPTR ulPhysicalAddress;
	void* pMemory;
	RTS_SIZE uiSize;
	int iRefCount;
	RTS_HANDLE ulHandle;
} SHM_OBJECT;

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Close a shared memory object specified by handle.
 * RETURN: Returns the runtime system error code (see CmpErrors_Itfs.library):
 */
typedef struct tagsyssharedmemoryclose_struct
{
	RTS_IEC_HANDLE hShm;				/* VAR_INPUT */	/* Handle to the shared memory */
	RTS_IEC_RESULT SysSharedMemoryClose;	/* VAR_OUTPUT */	
} syssharedmemoryclose_struct;

void CDECL CDECL_EXT syssharedmemoryclose(syssharedmemoryclose_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSSHAREDMEMORYCLOSE_IEC) (syssharedmemoryclose_struct *p);
#if defined(SYSSHM_NOTIMPLEMENTED) || defined(SYSSHAREDMEMORYCLOSE_NOTIMPLEMENTED)
	#define USE_syssharedmemoryclose
	#define EXT_syssharedmemoryclose
	#define GET_syssharedmemoryclose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syssharedmemoryclose(p0) 
	#define CHK_syssharedmemoryclose  FALSE
	#define EXP_syssharedmemoryclose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syssharedmemoryclose
	#define EXT_syssharedmemoryclose
	#define GET_syssharedmemoryclose(fl)  CAL_CMGETAPI( "syssharedmemoryclose" ) 
	#define CAL_syssharedmemoryclose  syssharedmemoryclose
	#define CHK_syssharedmemoryclose  TRUE
	#define EXP_syssharedmemoryclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryclose", (RTS_UINTPTR)syssharedmemoryclose, 1, RTSITF_GET_SIGNATURE(0, 0x93F75F86), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSSHM_EXTERNAL)
	#define USE_syssharedmemoryclose
	#define EXT_syssharedmemoryclose
	#define GET_syssharedmemoryclose(fl)  CAL_CMGETAPI( "syssharedmemoryclose" ) 
	#define CAL_syssharedmemoryclose  syssharedmemoryclose
	#define CHK_syssharedmemoryclose  TRUE
	#define EXP_syssharedmemoryclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryclose", (RTS_UINTPTR)syssharedmemoryclose, 1, RTSITF_GET_SIGNATURE(0, 0x93F75F86), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysShmsyssharedmemoryclose
	#define EXT_SysShmsyssharedmemoryclose
	#define GET_SysShmsyssharedmemoryclose  ERR_OK
	#define CAL_SysShmsyssharedmemoryclose  syssharedmemoryclose
	#define CHK_SysShmsyssharedmemoryclose  TRUE
	#define EXP_SysShmsyssharedmemoryclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryclose", (RTS_UINTPTR)syssharedmemoryclose, 1, RTSITF_GET_SIGNATURE(0, 0x93F75F86), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_syssharedmemoryclose
	#define EXT_syssharedmemoryclose
	#define GET_syssharedmemoryclose(fl)  CAL_CMGETAPI( "syssharedmemoryclose" ) 
	#define CAL_syssharedmemoryclose  syssharedmemoryclose
	#define CHK_syssharedmemoryclose  TRUE
	#define EXP_syssharedmemoryclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryclose", (RTS_UINTPTR)syssharedmemoryclose, 1, RTSITF_GET_SIGNATURE(0, 0x93F75F86), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_syssharedmemoryclose  PFSYSSHAREDMEMORYCLOSE_IEC pfsyssharedmemoryclose;
	#define EXT_syssharedmemoryclose  extern PFSYSSHAREDMEMORYCLOSE_IEC pfsyssharedmemoryclose;
	#define GET_syssharedmemoryclose(fl)  s_pfCMGetAPI2( "syssharedmemoryclose", (RTS_VOID_FCTPTR *)&pfsyssharedmemoryclose, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x93F75F86), 0x03050500)
	#define CAL_syssharedmemoryclose  pfsyssharedmemoryclose
	#define CHK_syssharedmemoryclose  (pfsyssharedmemoryclose != NULL)
	#define EXP_syssharedmemoryclose   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryclose", (RTS_UINTPTR)syssharedmemoryclose, 1, RTSITF_GET_SIGNATURE(0, 0x93F75F86), 0x03050500) 
#endif


/**
 * Create a new shared memory object specified by name.
 * NOTE:
 * If the shared memory object still exists, a valid handle is returned, but with the error code ERR_DUPLICATE.
 * RETURN: Handle to the shared memory object or RTS_INVALID_HANDLE if failed
 */
typedef struct tagsyssharedmemorycreate_struct
{
	RTS_IEC_STRING *pszName;			/* VAR_IN_OUT */	/* Name of the shared memory */
	RTS_IEC_UXINT ulPhysicalAddress;	/* VAR_INPUT */	/* Optional physical address. */
	RTS_IEC_UXINT *pulSize;				/* VAR_INPUT */	/* Pointer to requested size of the shared memory. */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors.library): */
	RTS_IEC_HANDLE SysSharedMemoryCreate;	/* VAR_OUTPUT */	
} syssharedmemorycreate_struct;

void CDECL CDECL_EXT syssharedmemorycreate(syssharedmemorycreate_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSSHAREDMEMORYCREATE_IEC) (syssharedmemorycreate_struct *p);
#if defined(SYSSHM_NOTIMPLEMENTED) || defined(SYSSHAREDMEMORYCREATE_NOTIMPLEMENTED)
	#define USE_syssharedmemorycreate
	#define EXT_syssharedmemorycreate
	#define GET_syssharedmemorycreate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syssharedmemorycreate(p0) 
	#define CHK_syssharedmemorycreate  FALSE
	#define EXP_syssharedmemorycreate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syssharedmemorycreate
	#define EXT_syssharedmemorycreate
	#define GET_syssharedmemorycreate(fl)  CAL_CMGETAPI( "syssharedmemorycreate" ) 
	#define CAL_syssharedmemorycreate  syssharedmemorycreate
	#define CHK_syssharedmemorycreate  TRUE
	#define EXP_syssharedmemorycreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorycreate", (RTS_UINTPTR)syssharedmemorycreate, 1, RTSITF_GET_SIGNATURE(0, 0x9DA848E2), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSSHM_EXTERNAL)
	#define USE_syssharedmemorycreate
	#define EXT_syssharedmemorycreate
	#define GET_syssharedmemorycreate(fl)  CAL_CMGETAPI( "syssharedmemorycreate" ) 
	#define CAL_syssharedmemorycreate  syssharedmemorycreate
	#define CHK_syssharedmemorycreate  TRUE
	#define EXP_syssharedmemorycreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorycreate", (RTS_UINTPTR)syssharedmemorycreate, 1, RTSITF_GET_SIGNATURE(0, 0x9DA848E2), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysShmsyssharedmemorycreate
	#define EXT_SysShmsyssharedmemorycreate
	#define GET_SysShmsyssharedmemorycreate  ERR_OK
	#define CAL_SysShmsyssharedmemorycreate  syssharedmemorycreate
	#define CHK_SysShmsyssharedmemorycreate  TRUE
	#define EXP_SysShmsyssharedmemorycreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorycreate", (RTS_UINTPTR)syssharedmemorycreate, 1, RTSITF_GET_SIGNATURE(0, 0x9DA848E2), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_syssharedmemorycreate
	#define EXT_syssharedmemorycreate
	#define GET_syssharedmemorycreate(fl)  CAL_CMGETAPI( "syssharedmemorycreate" ) 
	#define CAL_syssharedmemorycreate  syssharedmemorycreate
	#define CHK_syssharedmemorycreate  TRUE
	#define EXP_syssharedmemorycreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorycreate", (RTS_UINTPTR)syssharedmemorycreate, 1, RTSITF_GET_SIGNATURE(0, 0x9DA848E2), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_syssharedmemorycreate  PFSYSSHAREDMEMORYCREATE_IEC pfsyssharedmemorycreate;
	#define EXT_syssharedmemorycreate  extern PFSYSSHAREDMEMORYCREATE_IEC pfsyssharedmemorycreate;
	#define GET_syssharedmemorycreate(fl)  s_pfCMGetAPI2( "syssharedmemorycreate", (RTS_VOID_FCTPTR *)&pfsyssharedmemorycreate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x9DA848E2), 0x03050500)
	#define CAL_syssharedmemorycreate  pfsyssharedmemorycreate
	#define CHK_syssharedmemorycreate  (pfsyssharedmemorycreate != NULL)
	#define EXP_syssharedmemorycreate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorycreate", (RTS_UINTPTR)syssharedmemorycreate, 1, RTSITF_GET_SIGNATURE(0, 0x9DA848E2), 0x03050500) 
#endif


/**
 * Delete a shared memory object specified by handle
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsyssharedmemorydelete_struct
{
	RTS_IEC_HANDLE hShm;				/* VAR_INPUT */	/* Handle to the shared memory */
	RTS_IEC_RESULT SysSharedMemoryDelete;	/* VAR_OUTPUT */	
} syssharedmemorydelete_struct;

void CDECL CDECL_EXT syssharedmemorydelete(syssharedmemorydelete_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSSHAREDMEMORYDELETE_IEC) (syssharedmemorydelete_struct *p);
#if defined(SYSSHM_NOTIMPLEMENTED) || defined(SYSSHAREDMEMORYDELETE_NOTIMPLEMENTED)
	#define USE_syssharedmemorydelete
	#define EXT_syssharedmemorydelete
	#define GET_syssharedmemorydelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syssharedmemorydelete(p0) 
	#define CHK_syssharedmemorydelete  FALSE
	#define EXP_syssharedmemorydelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syssharedmemorydelete
	#define EXT_syssharedmemorydelete
	#define GET_syssharedmemorydelete(fl)  CAL_CMGETAPI( "syssharedmemorydelete" ) 
	#define CAL_syssharedmemorydelete  syssharedmemorydelete
	#define CHK_syssharedmemorydelete  TRUE
	#define EXP_syssharedmemorydelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorydelete", (RTS_UINTPTR)syssharedmemorydelete, 1, RTSITF_GET_SIGNATURE(0, 0x83C20043), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSSHM_EXTERNAL)
	#define USE_syssharedmemorydelete
	#define EXT_syssharedmemorydelete
	#define GET_syssharedmemorydelete(fl)  CAL_CMGETAPI( "syssharedmemorydelete" ) 
	#define CAL_syssharedmemorydelete  syssharedmemorydelete
	#define CHK_syssharedmemorydelete  TRUE
	#define EXP_syssharedmemorydelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorydelete", (RTS_UINTPTR)syssharedmemorydelete, 1, RTSITF_GET_SIGNATURE(0, 0x83C20043), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysShmsyssharedmemorydelete
	#define EXT_SysShmsyssharedmemorydelete
	#define GET_SysShmsyssharedmemorydelete  ERR_OK
	#define CAL_SysShmsyssharedmemorydelete  syssharedmemorydelete
	#define CHK_SysShmsyssharedmemorydelete  TRUE
	#define EXP_SysShmsyssharedmemorydelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorydelete", (RTS_UINTPTR)syssharedmemorydelete, 1, RTSITF_GET_SIGNATURE(0, 0x83C20043), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_syssharedmemorydelete
	#define EXT_syssharedmemorydelete
	#define GET_syssharedmemorydelete(fl)  CAL_CMGETAPI( "syssharedmemorydelete" ) 
	#define CAL_syssharedmemorydelete  syssharedmemorydelete
	#define CHK_syssharedmemorydelete  TRUE
	#define EXP_syssharedmemorydelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorydelete", (RTS_UINTPTR)syssharedmemorydelete, 1, RTSITF_GET_SIGNATURE(0, 0x83C20043), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_syssharedmemorydelete  PFSYSSHAREDMEMORYDELETE_IEC pfsyssharedmemorydelete;
	#define EXT_syssharedmemorydelete  extern PFSYSSHAREDMEMORYDELETE_IEC pfsyssharedmemorydelete;
	#define GET_syssharedmemorydelete(fl)  s_pfCMGetAPI2( "syssharedmemorydelete", (RTS_VOID_FCTPTR *)&pfsyssharedmemorydelete, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x83C20043), 0x03050500)
	#define CAL_syssharedmemorydelete  pfsyssharedmemorydelete
	#define CHK_syssharedmemorydelete  (pfsyssharedmemorydelete != NULL)
	#define EXP_syssharedmemorydelete   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorydelete", (RTS_UINTPTR)syssharedmemorydelete, 1, RTSITF_GET_SIGNATURE(0, 0x83C20043), 0x03050500) 
#endif


/**
 * Get the pointer to the shared memory
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsyssharedmemorygetpointer_struct
{
	RTS_IEC_HANDLE hShm;				/* VAR_INPUT */	/* Handle to the shared memory */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors.library) */
	RTS_IEC_BYTE *SysSharedMemoryGetPointer;	/* VAR_OUTPUT */	
} syssharedmemorygetpointer_struct;

void CDECL CDECL_EXT syssharedmemorygetpointer(syssharedmemorygetpointer_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSSHAREDMEMORYGETPOINTER_IEC) (syssharedmemorygetpointer_struct *p);
#if defined(SYSSHM_NOTIMPLEMENTED) || defined(SYSSHAREDMEMORYGETPOINTER_NOTIMPLEMENTED)
	#define USE_syssharedmemorygetpointer
	#define EXT_syssharedmemorygetpointer
	#define GET_syssharedmemorygetpointer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syssharedmemorygetpointer(p0) 
	#define CHK_syssharedmemorygetpointer  FALSE
	#define EXP_syssharedmemorygetpointer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syssharedmemorygetpointer
	#define EXT_syssharedmemorygetpointer
	#define GET_syssharedmemorygetpointer(fl)  CAL_CMGETAPI( "syssharedmemorygetpointer" ) 
	#define CAL_syssharedmemorygetpointer  syssharedmemorygetpointer
	#define CHK_syssharedmemorygetpointer  TRUE
	#define EXP_syssharedmemorygetpointer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorygetpointer", (RTS_UINTPTR)syssharedmemorygetpointer, 1, RTSITF_GET_SIGNATURE(0, 0x94066BAD), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSSHM_EXTERNAL)
	#define USE_syssharedmemorygetpointer
	#define EXT_syssharedmemorygetpointer
	#define GET_syssharedmemorygetpointer(fl)  CAL_CMGETAPI( "syssharedmemorygetpointer" ) 
	#define CAL_syssharedmemorygetpointer  syssharedmemorygetpointer
	#define CHK_syssharedmemorygetpointer  TRUE
	#define EXP_syssharedmemorygetpointer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorygetpointer", (RTS_UINTPTR)syssharedmemorygetpointer, 1, RTSITF_GET_SIGNATURE(0, 0x94066BAD), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysShmsyssharedmemorygetpointer
	#define EXT_SysShmsyssharedmemorygetpointer
	#define GET_SysShmsyssharedmemorygetpointer  ERR_OK
	#define CAL_SysShmsyssharedmemorygetpointer  syssharedmemorygetpointer
	#define CHK_SysShmsyssharedmemorygetpointer  TRUE
	#define EXP_SysShmsyssharedmemorygetpointer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorygetpointer", (RTS_UINTPTR)syssharedmemorygetpointer, 1, RTSITF_GET_SIGNATURE(0, 0x94066BAD), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_syssharedmemorygetpointer
	#define EXT_syssharedmemorygetpointer
	#define GET_syssharedmemorygetpointer(fl)  CAL_CMGETAPI( "syssharedmemorygetpointer" ) 
	#define CAL_syssharedmemorygetpointer  syssharedmemorygetpointer
	#define CHK_syssharedmemorygetpointer  TRUE
	#define EXP_syssharedmemorygetpointer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorygetpointer", (RTS_UINTPTR)syssharedmemorygetpointer, 1, RTSITF_GET_SIGNATURE(0, 0x94066BAD), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_syssharedmemorygetpointer  PFSYSSHAREDMEMORYGETPOINTER_IEC pfsyssharedmemorygetpointer;
	#define EXT_syssharedmemorygetpointer  extern PFSYSSHAREDMEMORYGETPOINTER_IEC pfsyssharedmemorygetpointer;
	#define GET_syssharedmemorygetpointer(fl)  s_pfCMGetAPI2( "syssharedmemorygetpointer", (RTS_VOID_FCTPTR *)&pfsyssharedmemorygetpointer, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x94066BAD), 0x03050500)
	#define CAL_syssharedmemorygetpointer  pfsyssharedmemorygetpointer
	#define CHK_syssharedmemorygetpointer  (pfsyssharedmemorygetpointer != NULL)
	#define EXP_syssharedmemorygetpointer   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorygetpointer", (RTS_UINTPTR)syssharedmemorygetpointer, 1, RTSITF_GET_SIGNATURE(0, 0x94066BAD), 0x03050500) 
#endif


/**
 * *OBSOLETE FUNCTION*
 *  Opens an existing shared memory object specified by name. If shared memory does not exist, a new shared memory object is
 *	 created (backward compatibility)!
 */
typedef struct tagsyssharedmemoryopen_struct
{
	RTS_IEC_STRING *pszName;			/* VAR_IN_OUT */	/* Name of the shared memory */
	RTS_IEC_UXINT ulPhysicalAddress;	/* VAR_INPUT */	/* Optional physical address. */
	RTS_IEC_UXINT *pulSize;				/* VAR_INPUT */	/* Pointer to requested size of the shared memory. */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors.library): */
	RTS_IEC_HANDLE SysSharedMemoryOpen;	/* VAR_OUTPUT */	
} syssharedmemoryopen_struct;

void CDECL CDECL_EXT syssharedmemoryopen(syssharedmemoryopen_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSSHAREDMEMORYOPEN_IEC) (syssharedmemoryopen_struct *p);
#if defined(SYSSHM_NOTIMPLEMENTED) || defined(SYSSHAREDMEMORYOPEN_NOTIMPLEMENTED)
	#define USE_syssharedmemoryopen
	#define EXT_syssharedmemoryopen
	#define GET_syssharedmemoryopen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syssharedmemoryopen(p0) 
	#define CHK_syssharedmemoryopen  FALSE
	#define EXP_syssharedmemoryopen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syssharedmemoryopen
	#define EXT_syssharedmemoryopen
	#define GET_syssharedmemoryopen(fl)  CAL_CMGETAPI( "syssharedmemoryopen" ) 
	#define CAL_syssharedmemoryopen  syssharedmemoryopen
	#define CHK_syssharedmemoryopen  TRUE
	#define EXP_syssharedmemoryopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryopen", (RTS_UINTPTR)syssharedmemoryopen, 1, RTSITF_GET_SIGNATURE(0, 0x41FB9CC1), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSSHM_EXTERNAL)
	#define USE_syssharedmemoryopen
	#define EXT_syssharedmemoryopen
	#define GET_syssharedmemoryopen(fl)  CAL_CMGETAPI( "syssharedmemoryopen" ) 
	#define CAL_syssharedmemoryopen  syssharedmemoryopen
	#define CHK_syssharedmemoryopen  TRUE
	#define EXP_syssharedmemoryopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryopen", (RTS_UINTPTR)syssharedmemoryopen, 1, RTSITF_GET_SIGNATURE(0, 0x41FB9CC1), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysShmsyssharedmemoryopen
	#define EXT_SysShmsyssharedmemoryopen
	#define GET_SysShmsyssharedmemoryopen  ERR_OK
	#define CAL_SysShmsyssharedmemoryopen  syssharedmemoryopen
	#define CHK_SysShmsyssharedmemoryopen  TRUE
	#define EXP_SysShmsyssharedmemoryopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryopen", (RTS_UINTPTR)syssharedmemoryopen, 1, RTSITF_GET_SIGNATURE(0, 0x41FB9CC1), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_syssharedmemoryopen
	#define EXT_syssharedmemoryopen
	#define GET_syssharedmemoryopen(fl)  CAL_CMGETAPI( "syssharedmemoryopen" ) 
	#define CAL_syssharedmemoryopen  syssharedmemoryopen
	#define CHK_syssharedmemoryopen  TRUE
	#define EXP_syssharedmemoryopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryopen", (RTS_UINTPTR)syssharedmemoryopen, 1, RTSITF_GET_SIGNATURE(0, 0x41FB9CC1), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_syssharedmemoryopen  PFSYSSHAREDMEMORYOPEN_IEC pfsyssharedmemoryopen;
	#define EXT_syssharedmemoryopen  extern PFSYSSHAREDMEMORYOPEN_IEC pfsyssharedmemoryopen;
	#define GET_syssharedmemoryopen(fl)  s_pfCMGetAPI2( "syssharedmemoryopen", (RTS_VOID_FCTPTR *)&pfsyssharedmemoryopen, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x41FB9CC1), 0x03050500)
	#define CAL_syssharedmemoryopen  pfsyssharedmemoryopen
	#define CHK_syssharedmemoryopen  (pfsyssharedmemoryopen != NULL)
	#define EXP_syssharedmemoryopen   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryopen", (RTS_UINTPTR)syssharedmemoryopen, 1, RTSITF_GET_SIGNATURE(0, 0x41FB9CC1), 0x03050500) 
#endif


/**
 * Opens an existing shared memory object specified by name.
 *	NOTE:
 *	If shared memory object not exists, an error code is returned an it is not created!
 * RETURN: Handle to the shared memory object or RTS_INVALID_HANDLE if failed
 */
typedef struct tagsyssharedmemoryopen2_struct
{
	RTS_IEC_STRING *pszName;			/* VAR_IN_OUT */	/* Name of the shared memory */
	RTS_IEC_UXINT ulPhysicalAddress;	/* VAR_INPUT */	/* Optional physical address: */
	RTS_IEC_UXINT *pulSize;				/* VAR_INPUT */	/* Pointer to requested size of the shared memory. */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors.library): */
	RTS_IEC_HANDLE SysSharedMemoryOpen2;	/* VAR_OUTPUT */	
} syssharedmemoryopen2_struct;

void CDECL CDECL_EXT syssharedmemoryopen2(syssharedmemoryopen2_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSSHAREDMEMORYOPEN2_IEC) (syssharedmemoryopen2_struct *p);
#if defined(SYSSHM_NOTIMPLEMENTED) || defined(SYSSHAREDMEMORYOPEN2_NOTIMPLEMENTED)
	#define USE_syssharedmemoryopen2
	#define EXT_syssharedmemoryopen2
	#define GET_syssharedmemoryopen2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syssharedmemoryopen2(p0) 
	#define CHK_syssharedmemoryopen2  FALSE
	#define EXP_syssharedmemoryopen2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syssharedmemoryopen2
	#define EXT_syssharedmemoryopen2
	#define GET_syssharedmemoryopen2(fl)  CAL_CMGETAPI( "syssharedmemoryopen2" ) 
	#define CAL_syssharedmemoryopen2  syssharedmemoryopen2
	#define CHK_syssharedmemoryopen2  TRUE
	#define EXP_syssharedmemoryopen2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryopen2", (RTS_UINTPTR)syssharedmemoryopen2, 1, RTSITF_GET_SIGNATURE(0, 0x69CA7C0D), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSSHM_EXTERNAL)
	#define USE_syssharedmemoryopen2
	#define EXT_syssharedmemoryopen2
	#define GET_syssharedmemoryopen2(fl)  CAL_CMGETAPI( "syssharedmemoryopen2" ) 
	#define CAL_syssharedmemoryopen2  syssharedmemoryopen2
	#define CHK_syssharedmemoryopen2  TRUE
	#define EXP_syssharedmemoryopen2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryopen2", (RTS_UINTPTR)syssharedmemoryopen2, 1, RTSITF_GET_SIGNATURE(0, 0x69CA7C0D), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysShmsyssharedmemoryopen2
	#define EXT_SysShmsyssharedmemoryopen2
	#define GET_SysShmsyssharedmemoryopen2  ERR_OK
	#define CAL_SysShmsyssharedmemoryopen2  syssharedmemoryopen2
	#define CHK_SysShmsyssharedmemoryopen2  TRUE
	#define EXP_SysShmsyssharedmemoryopen2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryopen2", (RTS_UINTPTR)syssharedmemoryopen2, 1, RTSITF_GET_SIGNATURE(0, 0x69CA7C0D), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_syssharedmemoryopen2
	#define EXT_syssharedmemoryopen2
	#define GET_syssharedmemoryopen2(fl)  CAL_CMGETAPI( "syssharedmemoryopen2" ) 
	#define CAL_syssharedmemoryopen2  syssharedmemoryopen2
	#define CHK_syssharedmemoryopen2  TRUE
	#define EXP_syssharedmemoryopen2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryopen2", (RTS_UINTPTR)syssharedmemoryopen2, 1, RTSITF_GET_SIGNATURE(0, 0x69CA7C0D), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_syssharedmemoryopen2  PFSYSSHAREDMEMORYOPEN2_IEC pfsyssharedmemoryopen2;
	#define EXT_syssharedmemoryopen2  extern PFSYSSHAREDMEMORYOPEN2_IEC pfsyssharedmemoryopen2;
	#define GET_syssharedmemoryopen2(fl)  s_pfCMGetAPI2( "syssharedmemoryopen2", (RTS_VOID_FCTPTR *)&pfsyssharedmemoryopen2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x69CA7C0D), 0x03050500)
	#define CAL_syssharedmemoryopen2  pfsyssharedmemoryopen2
	#define CHK_syssharedmemoryopen2  (pfsyssharedmemoryopen2 != NULL)
	#define EXP_syssharedmemoryopen2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryopen2", (RTS_UINTPTR)syssharedmemoryopen2, 1, RTSITF_GET_SIGNATURE(0, 0x69CA7C0D), 0x03050500) 
#endif


/**
 * This function can be used to read a defined number of bytes from a Shared Memory, starting at a certain offset.
 * RETURN: Number of bytes read from the shared memory
 */
typedef struct tagsyssharedmemoryread_struct
{
	RTS_IEC_HANDLE hShm;				/* VAR_INPUT */	/* Handle to the shared memory */
	RTS_IEC_UXINT ulOffset;				/* VAR_INPUT */	/* Offset in the shared memory, where reading should start */
	RTS_IEC_BYTE *pbyData;				/* VAR_INPUT */	/* Pointer to buffer to read in data */
	RTS_IEC_UXINT ulSize;				/* VAR_INPUT */	/* Number of bytes to read */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors.library) */
	RTS_IEC_UXINT SysSharedMemoryRead;	/* VAR_OUTPUT */	
} syssharedmemoryread_struct;

void CDECL CDECL_EXT syssharedmemoryread(syssharedmemoryread_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSSHAREDMEMORYREAD_IEC) (syssharedmemoryread_struct *p);
#if defined(SYSSHM_NOTIMPLEMENTED) || defined(SYSSHAREDMEMORYREAD_NOTIMPLEMENTED)
	#define USE_syssharedmemoryread
	#define EXT_syssharedmemoryread
	#define GET_syssharedmemoryread(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syssharedmemoryread(p0) 
	#define CHK_syssharedmemoryread  FALSE
	#define EXP_syssharedmemoryread  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syssharedmemoryread
	#define EXT_syssharedmemoryread
	#define GET_syssharedmemoryread(fl)  CAL_CMGETAPI( "syssharedmemoryread" ) 
	#define CAL_syssharedmemoryread  syssharedmemoryread
	#define CHK_syssharedmemoryread  TRUE
	#define EXP_syssharedmemoryread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryread", (RTS_UINTPTR)syssharedmemoryread, 1, RTSITF_GET_SIGNATURE(0, 0x67AB02BB), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSSHM_EXTERNAL)
	#define USE_syssharedmemoryread
	#define EXT_syssharedmemoryread
	#define GET_syssharedmemoryread(fl)  CAL_CMGETAPI( "syssharedmemoryread" ) 
	#define CAL_syssharedmemoryread  syssharedmemoryread
	#define CHK_syssharedmemoryread  TRUE
	#define EXP_syssharedmemoryread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryread", (RTS_UINTPTR)syssharedmemoryread, 1, RTSITF_GET_SIGNATURE(0, 0x67AB02BB), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysShmsyssharedmemoryread
	#define EXT_SysShmsyssharedmemoryread
	#define GET_SysShmsyssharedmemoryread  ERR_OK
	#define CAL_SysShmsyssharedmemoryread  syssharedmemoryread
	#define CHK_SysShmsyssharedmemoryread  TRUE
	#define EXP_SysShmsyssharedmemoryread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryread", (RTS_UINTPTR)syssharedmemoryread, 1, RTSITF_GET_SIGNATURE(0, 0x67AB02BB), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_syssharedmemoryread
	#define EXT_syssharedmemoryread
	#define GET_syssharedmemoryread(fl)  CAL_CMGETAPI( "syssharedmemoryread" ) 
	#define CAL_syssharedmemoryread  syssharedmemoryread
	#define CHK_syssharedmemoryread  TRUE
	#define EXP_syssharedmemoryread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryread", (RTS_UINTPTR)syssharedmemoryread, 1, RTSITF_GET_SIGNATURE(0, 0x67AB02BB), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_syssharedmemoryread  PFSYSSHAREDMEMORYREAD_IEC pfsyssharedmemoryread;
	#define EXT_syssharedmemoryread  extern PFSYSSHAREDMEMORYREAD_IEC pfsyssharedmemoryread;
	#define GET_syssharedmemoryread(fl)  s_pfCMGetAPI2( "syssharedmemoryread", (RTS_VOID_FCTPTR *)&pfsyssharedmemoryread, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x67AB02BB), 0x03050500)
	#define CAL_syssharedmemoryread  pfsyssharedmemoryread
	#define CHK_syssharedmemoryread  (pfsyssharedmemoryread != NULL)
	#define EXP_syssharedmemoryread   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryread", (RTS_UINTPTR)syssharedmemoryread, 1, RTSITF_GET_SIGNATURE(0, 0x67AB02BB), 0x03050500) 
#endif


/**
 * This function can be used to read “byte-wise” a defined number of bytes, starting at a certain offset.
 * RETURN: Number of bytes read from the shared memory
 */
typedef struct tagsyssharedmemoryreadbyte_struct
{
	RTS_IEC_HANDLE hShm;				/* VAR_INPUT */	/* Handle to the shared memory */
	RTS_IEC_UXINT ulOffset;				/* VAR_INPUT */	/* Offset in the shared memory, where reading should start */
	RTS_IEC_BYTE *pbyData;				/* VAR_INPUT */	/* Pointer to buffer to read in data */
	RTS_IEC_UXINT ulSize;				/* VAR_INPUT */	/* Number of bytes to read */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors.library) */
	RTS_IEC_UXINT SysSharedMemoryReadByte;	/* VAR_OUTPUT */	
} syssharedmemoryreadbyte_struct;

void CDECL CDECL_EXT syssharedmemoryreadbyte(syssharedmemoryreadbyte_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSSHAREDMEMORYREADBYTE_IEC) (syssharedmemoryreadbyte_struct *p);
#if defined(SYSSHM_NOTIMPLEMENTED) || defined(SYSSHAREDMEMORYREADBYTE_NOTIMPLEMENTED)
	#define USE_syssharedmemoryreadbyte
	#define EXT_syssharedmemoryreadbyte
	#define GET_syssharedmemoryreadbyte(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syssharedmemoryreadbyte(p0) 
	#define CHK_syssharedmemoryreadbyte  FALSE
	#define EXP_syssharedmemoryreadbyte  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syssharedmemoryreadbyte
	#define EXT_syssharedmemoryreadbyte
	#define GET_syssharedmemoryreadbyte(fl)  CAL_CMGETAPI( "syssharedmemoryreadbyte" ) 
	#define CAL_syssharedmemoryreadbyte  syssharedmemoryreadbyte
	#define CHK_syssharedmemoryreadbyte  TRUE
	#define EXP_syssharedmemoryreadbyte  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryreadbyte", (RTS_UINTPTR)syssharedmemoryreadbyte, 1, RTSITF_GET_SIGNATURE(0, 0x0E49748E), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSSHM_EXTERNAL)
	#define USE_syssharedmemoryreadbyte
	#define EXT_syssharedmemoryreadbyte
	#define GET_syssharedmemoryreadbyte(fl)  CAL_CMGETAPI( "syssharedmemoryreadbyte" ) 
	#define CAL_syssharedmemoryreadbyte  syssharedmemoryreadbyte
	#define CHK_syssharedmemoryreadbyte  TRUE
	#define EXP_syssharedmemoryreadbyte  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryreadbyte", (RTS_UINTPTR)syssharedmemoryreadbyte, 1, RTSITF_GET_SIGNATURE(0, 0x0E49748E), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysShmsyssharedmemoryreadbyte
	#define EXT_SysShmsyssharedmemoryreadbyte
	#define GET_SysShmsyssharedmemoryreadbyte  ERR_OK
	#define CAL_SysShmsyssharedmemoryreadbyte  syssharedmemoryreadbyte
	#define CHK_SysShmsyssharedmemoryreadbyte  TRUE
	#define EXP_SysShmsyssharedmemoryreadbyte  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryreadbyte", (RTS_UINTPTR)syssharedmemoryreadbyte, 1, RTSITF_GET_SIGNATURE(0, 0x0E49748E), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_syssharedmemoryreadbyte
	#define EXT_syssharedmemoryreadbyte
	#define GET_syssharedmemoryreadbyte(fl)  CAL_CMGETAPI( "syssharedmemoryreadbyte" ) 
	#define CAL_syssharedmemoryreadbyte  syssharedmemoryreadbyte
	#define CHK_syssharedmemoryreadbyte  TRUE
	#define EXP_syssharedmemoryreadbyte  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryreadbyte", (RTS_UINTPTR)syssharedmemoryreadbyte, 1, RTSITF_GET_SIGNATURE(0, 0x0E49748E), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_syssharedmemoryreadbyte  PFSYSSHAREDMEMORYREADBYTE_IEC pfsyssharedmemoryreadbyte;
	#define EXT_syssharedmemoryreadbyte  extern PFSYSSHAREDMEMORYREADBYTE_IEC pfsyssharedmemoryreadbyte;
	#define GET_syssharedmemoryreadbyte(fl)  s_pfCMGetAPI2( "syssharedmemoryreadbyte", (RTS_VOID_FCTPTR *)&pfsyssharedmemoryreadbyte, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x0E49748E), 0x03050500)
	#define CAL_syssharedmemoryreadbyte  pfsyssharedmemoryreadbyte
	#define CHK_syssharedmemoryreadbyte  (pfsyssharedmemoryreadbyte != NULL)
	#define EXP_syssharedmemoryreadbyte   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemoryreadbyte", (RTS_UINTPTR)syssharedmemoryreadbyte, 1, RTSITF_GET_SIGNATURE(0, 0x0E49748E), 0x03050500) 
#endif


/**
 * This function can be used to write a defined number of bytes to a Shared Memory area, starting at a certain offset address.
 * RETURN: Number of bytes written to the shared memory
 */
typedef struct tagsyssharedmemorywrite_struct
{
	RTS_IEC_HANDLE hShm;				/* VAR_INPUT */	/* Handle to the shared memory */
	RTS_IEC_UXINT ulOffset;				/* VAR_INPUT */	/* Offset in the shared memory */
	RTS_IEC_BYTE *pbyData;				/* VAR_INPUT */	/* Pointer to buffer with write data */
	RTS_IEC_UXINT ulSize;				/* VAR_INPUT */	/* Number of bytes to write */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors.library) */
	RTS_IEC_UXINT SysSharedMemoryWrite;	/* VAR_OUTPUT */	
} syssharedmemorywrite_struct;

void CDECL CDECL_EXT syssharedmemorywrite(syssharedmemorywrite_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSSHAREDMEMORYWRITE_IEC) (syssharedmemorywrite_struct *p);
#if defined(SYSSHM_NOTIMPLEMENTED) || defined(SYSSHAREDMEMORYWRITE_NOTIMPLEMENTED)
	#define USE_syssharedmemorywrite
	#define EXT_syssharedmemorywrite
	#define GET_syssharedmemorywrite(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syssharedmemorywrite(p0) 
	#define CHK_syssharedmemorywrite  FALSE
	#define EXP_syssharedmemorywrite  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syssharedmemorywrite
	#define EXT_syssharedmemorywrite
	#define GET_syssharedmemorywrite(fl)  CAL_CMGETAPI( "syssharedmemorywrite" ) 
	#define CAL_syssharedmemorywrite  syssharedmemorywrite
	#define CHK_syssharedmemorywrite  TRUE
	#define EXP_syssharedmemorywrite  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorywrite", (RTS_UINTPTR)syssharedmemorywrite, 1, RTSITF_GET_SIGNATURE(0, 0xE23019DB), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSSHM_EXTERNAL)
	#define USE_syssharedmemorywrite
	#define EXT_syssharedmemorywrite
	#define GET_syssharedmemorywrite(fl)  CAL_CMGETAPI( "syssharedmemorywrite" ) 
	#define CAL_syssharedmemorywrite  syssharedmemorywrite
	#define CHK_syssharedmemorywrite  TRUE
	#define EXP_syssharedmemorywrite  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorywrite", (RTS_UINTPTR)syssharedmemorywrite, 1, RTSITF_GET_SIGNATURE(0, 0xE23019DB), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysShmsyssharedmemorywrite
	#define EXT_SysShmsyssharedmemorywrite
	#define GET_SysShmsyssharedmemorywrite  ERR_OK
	#define CAL_SysShmsyssharedmemorywrite  syssharedmemorywrite
	#define CHK_SysShmsyssharedmemorywrite  TRUE
	#define EXP_SysShmsyssharedmemorywrite  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorywrite", (RTS_UINTPTR)syssharedmemorywrite, 1, RTSITF_GET_SIGNATURE(0, 0xE23019DB), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_syssharedmemorywrite
	#define EXT_syssharedmemorywrite
	#define GET_syssharedmemorywrite(fl)  CAL_CMGETAPI( "syssharedmemorywrite" ) 
	#define CAL_syssharedmemorywrite  syssharedmemorywrite
	#define CHK_syssharedmemorywrite  TRUE
	#define EXP_syssharedmemorywrite  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorywrite", (RTS_UINTPTR)syssharedmemorywrite, 1, RTSITF_GET_SIGNATURE(0, 0xE23019DB), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_syssharedmemorywrite  PFSYSSHAREDMEMORYWRITE_IEC pfsyssharedmemorywrite;
	#define EXT_syssharedmemorywrite  extern PFSYSSHAREDMEMORYWRITE_IEC pfsyssharedmemorywrite;
	#define GET_syssharedmemorywrite(fl)  s_pfCMGetAPI2( "syssharedmemorywrite", (RTS_VOID_FCTPTR *)&pfsyssharedmemorywrite, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xE23019DB), 0x03050500)
	#define CAL_syssharedmemorywrite  pfsyssharedmemorywrite
	#define CHK_syssharedmemorywrite  (pfsyssharedmemorywrite != NULL)
	#define EXP_syssharedmemorywrite   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorywrite", (RTS_UINTPTR)syssharedmemorywrite, 1, RTSITF_GET_SIGNATURE(0, 0xE23019DB), 0x03050500) 
#endif


/**
 * This function can be used to write a defined number of bytes in “byte-wise” manner to a Shared Memory area, starting at a certain offset address.
 * RETURN: Number of bytes written to the shared memory
 */
typedef struct tagsyssharedmemorywritebyte_struct
{
	RTS_IEC_HANDLE hShm;				/* VAR_INPUT */	/* Handle to the shared memory */
	RTS_IEC_UXINT ulOffset;				/* VAR_INPUT */	/* Offset in the shared memory */
	RTS_IEC_BYTE *pbyData;				/* VAR_INPUT */	/* Pointer to buffer with write data */
	RTS_IEC_UXINT ulSize;				/* VAR_INPUT */	/* Number of bytes to write */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors.library) */
	RTS_IEC_UXINT SysSharedMemoryWriteByte;	/* VAR_OUTPUT */	
} syssharedmemorywritebyte_struct;

void CDECL CDECL_EXT syssharedmemorywritebyte(syssharedmemorywritebyte_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSSHAREDMEMORYWRITEBYTE_IEC) (syssharedmemorywritebyte_struct *p);
#if defined(SYSSHM_NOTIMPLEMENTED) || defined(SYSSHAREDMEMORYWRITEBYTE_NOTIMPLEMENTED)
	#define USE_syssharedmemorywritebyte
	#define EXT_syssharedmemorywritebyte
	#define GET_syssharedmemorywritebyte(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syssharedmemorywritebyte(p0) 
	#define CHK_syssharedmemorywritebyte  FALSE
	#define EXP_syssharedmemorywritebyte  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syssharedmemorywritebyte
	#define EXT_syssharedmemorywritebyte
	#define GET_syssharedmemorywritebyte(fl)  CAL_CMGETAPI( "syssharedmemorywritebyte" ) 
	#define CAL_syssharedmemorywritebyte  syssharedmemorywritebyte
	#define CHK_syssharedmemorywritebyte  TRUE
	#define EXP_syssharedmemorywritebyte  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorywritebyte", (RTS_UINTPTR)syssharedmemorywritebyte, 1, RTSITF_GET_SIGNATURE(0, 0xF3240E6E), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSSHM_EXTERNAL)
	#define USE_syssharedmemorywritebyte
	#define EXT_syssharedmemorywritebyte
	#define GET_syssharedmemorywritebyte(fl)  CAL_CMGETAPI( "syssharedmemorywritebyte" ) 
	#define CAL_syssharedmemorywritebyte  syssharedmemorywritebyte
	#define CHK_syssharedmemorywritebyte  TRUE
	#define EXP_syssharedmemorywritebyte  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorywritebyte", (RTS_UINTPTR)syssharedmemorywritebyte, 1, RTSITF_GET_SIGNATURE(0, 0xF3240E6E), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysShmsyssharedmemorywritebyte
	#define EXT_SysShmsyssharedmemorywritebyte
	#define GET_SysShmsyssharedmemorywritebyte  ERR_OK
	#define CAL_SysShmsyssharedmemorywritebyte  syssharedmemorywritebyte
	#define CHK_SysShmsyssharedmemorywritebyte  TRUE
	#define EXP_SysShmsyssharedmemorywritebyte  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorywritebyte", (RTS_UINTPTR)syssharedmemorywritebyte, 1, RTSITF_GET_SIGNATURE(0, 0xF3240E6E), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_syssharedmemorywritebyte
	#define EXT_syssharedmemorywritebyte
	#define GET_syssharedmemorywritebyte(fl)  CAL_CMGETAPI( "syssharedmemorywritebyte" ) 
	#define CAL_syssharedmemorywritebyte  syssharedmemorywritebyte
	#define CHK_syssharedmemorywritebyte  TRUE
	#define EXP_syssharedmemorywritebyte  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorywritebyte", (RTS_UINTPTR)syssharedmemorywritebyte, 1, RTSITF_GET_SIGNATURE(0, 0xF3240E6E), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_syssharedmemorywritebyte  PFSYSSHAREDMEMORYWRITEBYTE_IEC pfsyssharedmemorywritebyte;
	#define EXT_syssharedmemorywritebyte  extern PFSYSSHAREDMEMORYWRITEBYTE_IEC pfsyssharedmemorywritebyte;
	#define GET_syssharedmemorywritebyte(fl)  s_pfCMGetAPI2( "syssharedmemorywritebyte", (RTS_VOID_FCTPTR *)&pfsyssharedmemorywritebyte, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xF3240E6E), 0x03050500)
	#define CAL_syssharedmemorywritebyte  pfsyssharedmemorywritebyte
	#define CHK_syssharedmemorywritebyte  (pfsyssharedmemorywritebyte != NULL)
	#define EXP_syssharedmemorywritebyte   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssharedmemorywritebyte", (RTS_UINTPTR)syssharedmemorywritebyte, 1, RTSITF_GET_SIGNATURE(0, 0xF3240E6E), 0x03050500) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/



#ifndef CDECL
	#define CDECL
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysSharedMemoryOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysSharedMemoryOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>
 *  Create a new shared memory object specified by name.
 *	IMPLEMENTATION NOTE:
 *	If the shared memory object still exists, a valid handle is returned, but with the error code ERR_DUPLICATE.
 * </description>
 * <param name="pszName" type="IN">Name of the shared memory</param>
 * <param name="ulPhysicalAddress" type="IN">Optional physical address:
 *	ulPhysicalAddress > 0: The shared memory will be mapped on this physical address
 *	ulPhysicalAddress = 0: A new shared memory will created without a specified physical address</param>
 * <param name="puiSize" type="INOUT">Pointer to requested size of the shared memory</param>
 * <param name="pResult" type="OUT">Pointer to error code:
 *	ERR_OK: Succeeded
 *	ERR_DUPLICATE: Shared memory object still exists. A valid handle to this object is returned here!
 *	ERR_NOMEMORY: No memory available on the heap to allocate a management structure
 *	ERR_FAILED: Failed to open the shared memory
 *	ERR_PARAMETER: If one of the parameter is invalid (pszName = NULL or puiSize = NULL)
 *	ERR_BUFFERSIZE: If shared memory with this name exist, but the requested size is different
 *		from the available size. In this case, *puiSize returns the available size,
 *		but return handle is RTS_INVALID_HANDLE.
 * </param>
 * <result>Handle to the shared memory object or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL SysSharedMemoryCreate(char *pszName, RTS_UINTPTR ulPhysicalAddress, RTS_SIZE *puiSize, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSSHAREDMEMORYCREATE) (char *pszName, RTS_UINTPTR ulPhysicalAddress, RTS_SIZE *puiSize, RTS_RESULT *pResult);
#if defined(SYSSHM_NOTIMPLEMENTED) || defined(SYSSHAREDMEMORYCREATE_NOTIMPLEMENTED)
	#define USE_SysSharedMemoryCreate
	#define EXT_SysSharedMemoryCreate
	#define GET_SysSharedMemoryCreate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysSharedMemoryCreate(p0,p1,p2,p3)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysSharedMemoryCreate  FALSE
	#define EXP_SysSharedMemoryCreate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysSharedMemoryCreate
	#define EXT_SysSharedMemoryCreate
	#define GET_SysSharedMemoryCreate(fl)  CAL_CMGETAPI( "SysSharedMemoryCreate" ) 
	#define CAL_SysSharedMemoryCreate  SysSharedMemoryCreate
	#define CHK_SysSharedMemoryCreate  TRUE
	#define EXP_SysSharedMemoryCreate  CAL_CMEXPAPI( "SysSharedMemoryCreate" ) 
#elif defined(MIXED_LINK) && !defined(SYSSHM_EXTERNAL)
	#define USE_SysSharedMemoryCreate
	#define EXT_SysSharedMemoryCreate
	#define GET_SysSharedMemoryCreate(fl)  CAL_CMGETAPI( "SysSharedMemoryCreate" ) 
	#define CAL_SysSharedMemoryCreate  SysSharedMemoryCreate
	#define CHK_SysSharedMemoryCreate  TRUE
	#define EXP_SysSharedMemoryCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSharedMemoryCreate", (RTS_UINTPTR)SysSharedMemoryCreate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysShmSysSharedMemoryCreate
	#define EXT_SysShmSysSharedMemoryCreate
	#define GET_SysShmSysSharedMemoryCreate  ERR_OK
	#define CAL_SysShmSysSharedMemoryCreate  ((ISysShm*)s_pfCMCreateInstance(CLASSID_CSysShm, NULL))->ISysSharedMemoryCreate
	#define CHK_SysShmSysSharedMemoryCreate	(s_pfCMCreateInstance != NULL && pISysShm != NULL)
	#define EXP_SysShmSysSharedMemoryCreate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysSharedMemoryCreate
	#define EXT_SysSharedMemoryCreate
	#define GET_SysSharedMemoryCreate(fl)  CAL_CMGETAPI( "SysSharedMemoryCreate" ) 
	#define CAL_SysSharedMemoryCreate  ((ISysShm*)s_pfCMCreateInstance(CLASSID_CSysShm, NULL))->ISysSharedMemoryCreate
	#define CHK_SysSharedMemoryCreate	(s_pfCMCreateInstance != NULL && pISysShm != NULL)
	#define EXP_SysSharedMemoryCreate  CAL_CMEXPAPI( "SysSharedMemoryCreate" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysSharedMemoryCreate  PFSYSSHAREDMEMORYCREATE pfSysSharedMemoryCreate;
	#define EXT_SysSharedMemoryCreate  extern PFSYSSHAREDMEMORYCREATE pfSysSharedMemoryCreate;
	#define GET_SysSharedMemoryCreate(fl)  s_pfCMGetAPI2( "SysSharedMemoryCreate", (RTS_VOID_FCTPTR *)&pfSysSharedMemoryCreate, (fl), 0, 0)
	#define CAL_SysSharedMemoryCreate  pfSysSharedMemoryCreate
	#define CHK_SysSharedMemoryCreate  (pfSysSharedMemoryCreate != NULL)
	#define EXP_SysSharedMemoryCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSharedMemoryCreate", (RTS_UINTPTR)SysSharedMemoryCreate, 0, 0) 
#endif




/**
 * <description>
 *  Delete a shared memory object specified by handle
 * </description>
 * <param name="hShm" type="IN">Handle to the shared memory</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysSharedMemoryDelete(RTS_HANDLE hShm);
typedef RTS_RESULT (CDECL * PFSYSSHAREDMEMORYDELETE) (RTS_HANDLE hShm);
#if defined(SYSSHM_NOTIMPLEMENTED) || defined(SYSSHAREDMEMORYDELETE_NOTIMPLEMENTED)
	#define USE_SysSharedMemoryDelete
	#define EXT_SysSharedMemoryDelete
	#define GET_SysSharedMemoryDelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysSharedMemoryDelete(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysSharedMemoryDelete  FALSE
	#define EXP_SysSharedMemoryDelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysSharedMemoryDelete
	#define EXT_SysSharedMemoryDelete
	#define GET_SysSharedMemoryDelete(fl)  CAL_CMGETAPI( "SysSharedMemoryDelete" ) 
	#define CAL_SysSharedMemoryDelete  SysSharedMemoryDelete
	#define CHK_SysSharedMemoryDelete  TRUE
	#define EXP_SysSharedMemoryDelete  CAL_CMEXPAPI( "SysSharedMemoryDelete" ) 
#elif defined(MIXED_LINK) && !defined(SYSSHM_EXTERNAL)
	#define USE_SysSharedMemoryDelete
	#define EXT_SysSharedMemoryDelete
	#define GET_SysSharedMemoryDelete(fl)  CAL_CMGETAPI( "SysSharedMemoryDelete" ) 
	#define CAL_SysSharedMemoryDelete  SysSharedMemoryDelete
	#define CHK_SysSharedMemoryDelete  TRUE
	#define EXP_SysSharedMemoryDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSharedMemoryDelete", (RTS_UINTPTR)SysSharedMemoryDelete, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysShmSysSharedMemoryDelete
	#define EXT_SysShmSysSharedMemoryDelete
	#define GET_SysShmSysSharedMemoryDelete  ERR_OK
	#define CAL_SysShmSysSharedMemoryDelete(p0) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ISysShm*)p0)->ISysSharedMemoryDelete())
	#define CHK_SysShmSysSharedMemoryDelete  TRUE
	#define EXP_SysShmSysSharedMemoryDelete  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysSharedMemoryDelete
	#define EXT_SysSharedMemoryDelete
	#define GET_SysSharedMemoryDelete(fl)  CAL_CMGETAPI( "SysSharedMemoryDelete" ) 
	#define CAL_SysSharedMemoryDelete(p0) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ISysShm*)p0)->ISysSharedMemoryDelete())
	#define CHK_SysSharedMemoryDelete  TRUE
	#define EXP_SysSharedMemoryDelete  CAL_CMEXPAPI( "SysSharedMemoryDelete" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysSharedMemoryDelete  PFSYSSHAREDMEMORYDELETE pfSysSharedMemoryDelete;
	#define EXT_SysSharedMemoryDelete  extern PFSYSSHAREDMEMORYDELETE pfSysSharedMemoryDelete;
	#define GET_SysSharedMemoryDelete(fl)  s_pfCMGetAPI2( "SysSharedMemoryDelete", (RTS_VOID_FCTPTR *)&pfSysSharedMemoryDelete, (fl), 0, 0)
	#define CAL_SysSharedMemoryDelete  pfSysSharedMemoryDelete
	#define CHK_SysSharedMemoryDelete  (pfSysSharedMemoryDelete != NULL)
	#define EXP_SysSharedMemoryDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSharedMemoryDelete", (RTS_UINTPTR)SysSharedMemoryDelete, 0, 0) 
#endif




/**
 * <description>
 *  Opens an existing shared memory object specified by name.
 *	IMPLEMENTATION NOTE:
 *	If shared memory object not exists, an error code is returned an it is not created!
 * </description>
 * <param name="pszName" type="IN">Name of the shared memory</param>
 * <param name="ulPhysicalAddress" type="IN">Optional physical address:
 *	ulPhysicalAddress > 0: The shared memory will be mapped on this physical address
 *	ulPhysicalAddress = 0: An existing shared memory will be opened without a specified physical address</param>
 * <param name="puiSize" type="INOUT">Pointer to requested size of the shared memory.
 *				Size must match to the existing shared memory object size!</param>
 * <param name="pResult" type="OUT">Pointer to error code:
 *	ERR_OK: Succeeded
 *	ERR_NO_OBJECT: If shared memory does not exist.
 *	ERR_NOMEMORY: No memory available on the heap to allocate a management structure
 *	ERR_FAILED: Failed to open the shared memory
 *	ERR_PARAMETER: If one of the parameter is invalid (pszName = NULL or puiSize = NULL)
 *	ERR_BUFFERSIZE: If shared memory with this name exist, but the requested size is different
 *		from the available size. In this case, *puiSize returns the available size,
 *		but return handle is RTS_INVALID_HANDLE.
 * </param>
 * <result>Handle to the shared memory object or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL SysSharedMemoryOpen(char *pszName, RTS_UINTPTR ulPhysicalAddress, RTS_SIZE *puiSize, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSSHAREDMEMORYOPEN) (char *pszName, RTS_UINTPTR ulPhysicalAddress, RTS_SIZE *puiSize, RTS_RESULT *pResult);
#if defined(SYSSHM_NOTIMPLEMENTED) || defined(SYSSHAREDMEMORYOPEN_NOTIMPLEMENTED)
	#define USE_SysSharedMemoryOpen
	#define EXT_SysSharedMemoryOpen
	#define GET_SysSharedMemoryOpen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysSharedMemoryOpen(p0,p1,p2,p3)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysSharedMemoryOpen  FALSE
	#define EXP_SysSharedMemoryOpen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysSharedMemoryOpen
	#define EXT_SysSharedMemoryOpen
	#define GET_SysSharedMemoryOpen(fl)  CAL_CMGETAPI( "SysSharedMemoryOpen" ) 
	#define CAL_SysSharedMemoryOpen  SysSharedMemoryOpen
	#define CHK_SysSharedMemoryOpen  TRUE
	#define EXP_SysSharedMemoryOpen  CAL_CMEXPAPI( "SysSharedMemoryOpen" ) 
#elif defined(MIXED_LINK) && !defined(SYSSHM_EXTERNAL)
	#define USE_SysSharedMemoryOpen
	#define EXT_SysSharedMemoryOpen
	#define GET_SysSharedMemoryOpen(fl)  CAL_CMGETAPI( "SysSharedMemoryOpen" ) 
	#define CAL_SysSharedMemoryOpen  SysSharedMemoryOpen
	#define CHK_SysSharedMemoryOpen  TRUE
	#define EXP_SysSharedMemoryOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSharedMemoryOpen", (RTS_UINTPTR)SysSharedMemoryOpen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysShmSysSharedMemoryOpen
	#define EXT_SysShmSysSharedMemoryOpen
	#define GET_SysShmSysSharedMemoryOpen  ERR_OK
	#define CAL_SysShmSysSharedMemoryOpen  ((ISysShm*)s_pfCMCreateInstance(CLASSID_CSysShm, NULL))->ISysSharedMemoryOpen
	#define CHK_SysShmSysSharedMemoryOpen	(s_pfCMCreateInstance != NULL && pISysShm != NULL)
	#define EXP_SysShmSysSharedMemoryOpen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysSharedMemoryOpen
	#define EXT_SysSharedMemoryOpen
	#define GET_SysSharedMemoryOpen(fl)  CAL_CMGETAPI( "SysSharedMemoryOpen" ) 
	#define CAL_SysSharedMemoryOpen  ((ISysShm*)s_pfCMCreateInstance(CLASSID_CSysShm, NULL))->ISysSharedMemoryOpen
	#define CHK_SysSharedMemoryOpen	(s_pfCMCreateInstance != NULL && pISysShm != NULL)
	#define EXP_SysSharedMemoryOpen  CAL_CMEXPAPI( "SysSharedMemoryOpen" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysSharedMemoryOpen  PFSYSSHAREDMEMORYOPEN pfSysSharedMemoryOpen;
	#define EXT_SysSharedMemoryOpen  extern PFSYSSHAREDMEMORYOPEN pfSysSharedMemoryOpen;
	#define GET_SysSharedMemoryOpen(fl)  s_pfCMGetAPI2( "SysSharedMemoryOpen", (RTS_VOID_FCTPTR *)&pfSysSharedMemoryOpen, (fl), 0, 0)
	#define CAL_SysSharedMemoryOpen  pfSysSharedMemoryOpen
	#define CHK_SysSharedMemoryOpen  (pfSysSharedMemoryOpen != NULL)
	#define EXP_SysSharedMemoryOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSharedMemoryOpen", (RTS_UINTPTR)SysSharedMemoryOpen, 0, 0) 
#endif




/**
 * <description>
 *  Close a shared memory object specified by handle
 * </description>
 * <param name="hShm" type="IN">Handle to the shared memory</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysSharedMemoryClose(RTS_HANDLE hShm);
typedef RTS_RESULT (CDECL * PFSYSSHAREDMEMORYCLOSE) (RTS_HANDLE hShm);
#if defined(SYSSHM_NOTIMPLEMENTED) || defined(SYSSHAREDMEMORYCLOSE_NOTIMPLEMENTED)
	#define USE_SysSharedMemoryClose
	#define EXT_SysSharedMemoryClose
	#define GET_SysSharedMemoryClose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysSharedMemoryClose(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysSharedMemoryClose  FALSE
	#define EXP_SysSharedMemoryClose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysSharedMemoryClose
	#define EXT_SysSharedMemoryClose
	#define GET_SysSharedMemoryClose(fl)  CAL_CMGETAPI( "SysSharedMemoryClose" ) 
	#define CAL_SysSharedMemoryClose  SysSharedMemoryClose
	#define CHK_SysSharedMemoryClose  TRUE
	#define EXP_SysSharedMemoryClose  CAL_CMEXPAPI( "SysSharedMemoryClose" ) 
#elif defined(MIXED_LINK) && !defined(SYSSHM_EXTERNAL)
	#define USE_SysSharedMemoryClose
	#define EXT_SysSharedMemoryClose
	#define GET_SysSharedMemoryClose(fl)  CAL_CMGETAPI( "SysSharedMemoryClose" ) 
	#define CAL_SysSharedMemoryClose  SysSharedMemoryClose
	#define CHK_SysSharedMemoryClose  TRUE
	#define EXP_SysSharedMemoryClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSharedMemoryClose", (RTS_UINTPTR)SysSharedMemoryClose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysShmSysSharedMemoryClose
	#define EXT_SysShmSysSharedMemoryClose
	#define GET_SysShmSysSharedMemoryClose  ERR_OK
	#define CAL_SysShmSysSharedMemoryClose(p0) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ISysShm*)p0)->ISysSharedMemoryClose())
	#define CHK_SysShmSysSharedMemoryClose  TRUE
	#define EXP_SysShmSysSharedMemoryClose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysSharedMemoryClose
	#define EXT_SysSharedMemoryClose
	#define GET_SysSharedMemoryClose(fl)  CAL_CMGETAPI( "SysSharedMemoryClose" ) 
	#define CAL_SysSharedMemoryClose(p0) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ISysShm*)p0)->ISysSharedMemoryClose())
	#define CHK_SysSharedMemoryClose  TRUE
	#define EXP_SysSharedMemoryClose  CAL_CMEXPAPI( "SysSharedMemoryClose" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysSharedMemoryClose  PFSYSSHAREDMEMORYCLOSE pfSysSharedMemoryClose;
	#define EXT_SysSharedMemoryClose  extern PFSYSSHAREDMEMORYCLOSE pfSysSharedMemoryClose;
	#define GET_SysSharedMemoryClose(fl)  s_pfCMGetAPI2( "SysSharedMemoryClose", (RTS_VOID_FCTPTR *)&pfSysSharedMemoryClose, (fl), 0, 0)
	#define CAL_SysSharedMemoryClose  pfSysSharedMemoryClose
	#define CHK_SysSharedMemoryClose  (pfSysSharedMemoryClose != NULL)
	#define EXP_SysSharedMemoryClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSharedMemoryClose", (RTS_UINTPTR)SysSharedMemoryClose, 0, 0) 
#endif




/**
 * <description>
 *  Get the pointer to the shared memory
 * </description>
 * <param name="hShm" type="IN">Handle to the shared memory</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the shared memory for data access</result>
 */
void * CDECL SysSharedMemoryGetPointer(RTS_HANDLE hShm, RTS_RESULT *pResult);
typedef void * (CDECL * PFSYSSHAREDMEMORYGETPOINTER) (RTS_HANDLE hShm, RTS_RESULT *pResult);
#if defined(SYSSHM_NOTIMPLEMENTED) || defined(SYSSHAREDMEMORYGETPOINTER_NOTIMPLEMENTED)
	#define USE_SysSharedMemoryGetPointer
	#define EXT_SysSharedMemoryGetPointer
	#define GET_SysSharedMemoryGetPointer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysSharedMemoryGetPointer(p0,p1)  (void *)ERR_NOTIMPLEMENTED
	#define CHK_SysSharedMemoryGetPointer  FALSE
	#define EXP_SysSharedMemoryGetPointer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysSharedMemoryGetPointer
	#define EXT_SysSharedMemoryGetPointer
	#define GET_SysSharedMemoryGetPointer(fl)  CAL_CMGETAPI( "SysSharedMemoryGetPointer" ) 
	#define CAL_SysSharedMemoryGetPointer  SysSharedMemoryGetPointer
	#define CHK_SysSharedMemoryGetPointer  TRUE
	#define EXP_SysSharedMemoryGetPointer  CAL_CMEXPAPI( "SysSharedMemoryGetPointer" ) 
#elif defined(MIXED_LINK) && !defined(SYSSHM_EXTERNAL)
	#define USE_SysSharedMemoryGetPointer
	#define EXT_SysSharedMemoryGetPointer
	#define GET_SysSharedMemoryGetPointer(fl)  CAL_CMGETAPI( "SysSharedMemoryGetPointer" ) 
	#define CAL_SysSharedMemoryGetPointer  SysSharedMemoryGetPointer
	#define CHK_SysSharedMemoryGetPointer  TRUE
	#define EXP_SysSharedMemoryGetPointer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSharedMemoryGetPointer", (RTS_UINTPTR)SysSharedMemoryGetPointer, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysShmSysSharedMemoryGetPointer
	#define EXT_SysShmSysSharedMemoryGetPointer
	#define GET_SysShmSysSharedMemoryGetPointer  ERR_OK
	#define CAL_SysShmSysSharedMemoryGetPointer(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysShm->ISysSharedMemoryGetPointer(p1) : ((ISysShm*)p0)->ISysSharedMemoryGetPointer(p1))
	#define CHK_SysShmSysSharedMemoryGetPointer  (pISysShm != NULL)
	#define EXP_SysShmSysSharedMemoryGetPointer  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysSharedMemoryGetPointer
	#define EXT_SysSharedMemoryGetPointer
	#define GET_SysSharedMemoryGetPointer(fl)  CAL_CMGETAPI( "SysSharedMemoryGetPointer" ) 
	#define CAL_SysSharedMemoryGetPointer(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysShm->ISysSharedMemoryGetPointer(p1) : ((ISysShm*)p0)->ISysSharedMemoryGetPointer(p1))
	#define CHK_SysSharedMemoryGetPointer  (pISysShm != NULL)
	#define EXP_SysSharedMemoryGetPointer  CAL_CMEXPAPI( "SysSharedMemoryGetPointer" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysSharedMemoryGetPointer  PFSYSSHAREDMEMORYGETPOINTER pfSysSharedMemoryGetPointer;
	#define EXT_SysSharedMemoryGetPointer  extern PFSYSSHAREDMEMORYGETPOINTER pfSysSharedMemoryGetPointer;
	#define GET_SysSharedMemoryGetPointer(fl)  s_pfCMGetAPI2( "SysSharedMemoryGetPointer", (RTS_VOID_FCTPTR *)&pfSysSharedMemoryGetPointer, (fl), 0, 0)
	#define CAL_SysSharedMemoryGetPointer  pfSysSharedMemoryGetPointer
	#define CHK_SysSharedMemoryGetPointer  (pfSysSharedMemoryGetPointer != NULL)
	#define EXP_SysSharedMemoryGetPointer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSharedMemoryGetPointer", (RTS_UINTPTR)SysSharedMemoryGetPointer, 0, 0) 
#endif




/**
 * <description>
 *	Routine to read values from shared memory,
 *	ulOffset: offset in the shared memory
 *	pbyData: Pointer to the buffer to read in values
 *	ulSize: number of bytes to read
 * </description>
 * <param name="hShm" type="IN">Handle to the shared memory</param>
 * <param name="ulOffset" type="IN">Offset in the shared memory</param>
 * <param name="pbyData" type="OUT">Pointer to buffer to read in data</param>
 * <param name="uiSize" type="IN">Number of bytes to read</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of bytes read from the shared memory</result>
 */
RTS_SIZE CDECL SysSharedMemoryRead(RTS_HANDLE hShm, RTS_SIZE ulOffset, unsigned char *pbyData, RTS_SIZE uiSize, RTS_RESULT *pResult);
typedef RTS_SIZE (CDECL * PFSYSSHAREDMEMORYREAD) (RTS_HANDLE hShm, RTS_SIZE ulOffset, unsigned char *pbyData, RTS_SIZE uiSize, RTS_RESULT *pResult);
#if defined(SYSSHM_NOTIMPLEMENTED) || defined(SYSSHAREDMEMORYREAD_NOTIMPLEMENTED)
	#define USE_SysSharedMemoryRead
	#define EXT_SysSharedMemoryRead
	#define GET_SysSharedMemoryRead(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysSharedMemoryRead(p0,p1,p2,p3,p4)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_SysSharedMemoryRead  FALSE
	#define EXP_SysSharedMemoryRead  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysSharedMemoryRead
	#define EXT_SysSharedMemoryRead
	#define GET_SysSharedMemoryRead(fl)  CAL_CMGETAPI( "SysSharedMemoryRead" ) 
	#define CAL_SysSharedMemoryRead  SysSharedMemoryRead
	#define CHK_SysSharedMemoryRead  TRUE
	#define EXP_SysSharedMemoryRead  CAL_CMEXPAPI( "SysSharedMemoryRead" ) 
#elif defined(MIXED_LINK) && !defined(SYSSHM_EXTERNAL)
	#define USE_SysSharedMemoryRead
	#define EXT_SysSharedMemoryRead
	#define GET_SysSharedMemoryRead(fl)  CAL_CMGETAPI( "SysSharedMemoryRead" ) 
	#define CAL_SysSharedMemoryRead  SysSharedMemoryRead
	#define CHK_SysSharedMemoryRead  TRUE
	#define EXP_SysSharedMemoryRead  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSharedMemoryRead", (RTS_UINTPTR)SysSharedMemoryRead, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysShmSysSharedMemoryRead
	#define EXT_SysShmSysSharedMemoryRead
	#define GET_SysShmSysSharedMemoryRead  ERR_OK
	#define CAL_SysShmSysSharedMemoryRead(p0,p1,p2,p3,p4)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysShm->ISysSharedMemoryRead(p1,p2,p3,p4) : ((ISysShm*)p0)->ISysSharedMemoryRead(p1,p2,p3,p4))
	#define CHK_SysShmSysSharedMemoryRead  (pISysShm != NULL)
	#define EXP_SysShmSysSharedMemoryRead  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysSharedMemoryRead
	#define EXT_SysSharedMemoryRead
	#define GET_SysSharedMemoryRead(fl)  CAL_CMGETAPI( "SysSharedMemoryRead" ) 
	#define CAL_SysSharedMemoryRead(p0,p1,p2,p3,p4)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysShm->ISysSharedMemoryRead(p1,p2,p3,p4) : ((ISysShm*)p0)->ISysSharedMemoryRead(p1,p2,p3,p4))
	#define CHK_SysSharedMemoryRead  (pISysShm != NULL)
	#define EXP_SysSharedMemoryRead  CAL_CMEXPAPI( "SysSharedMemoryRead" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysSharedMemoryRead  PFSYSSHAREDMEMORYREAD pfSysSharedMemoryRead;
	#define EXT_SysSharedMemoryRead  extern PFSYSSHAREDMEMORYREAD pfSysSharedMemoryRead;
	#define GET_SysSharedMemoryRead(fl)  s_pfCMGetAPI2( "SysSharedMemoryRead", (RTS_VOID_FCTPTR *)&pfSysSharedMemoryRead, (fl), 0, 0)
	#define CAL_SysSharedMemoryRead  pfSysSharedMemoryRead
	#define CHK_SysSharedMemoryRead  (pfSysSharedMemoryRead != NULL)
	#define EXP_SysSharedMemoryRead  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSharedMemoryRead", (RTS_UINTPTR)SysSharedMemoryRead, 0, 0) 
#endif




/**
 * <description>
 *	This function can be used to read "byte-wise" a defined number of bytes, starting at a certain offset.
 * </description>
 * <param name="hShm" type="IN">Handle to the shared memory</param>
 * <param name="ulOffset" type="IN">Offset in the shared memory</param>
 * <param name="pbyData" type="OUT">Pointer to buffer to read in data</param>
 * <param name="uiSize" type="IN">Number of bytes to read</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of bytes read from the shared memory</result>
 */
RTS_SIZE CDECL SysSharedMemoryReadByte(RTS_HANDLE hShm, RTS_SIZE ulOffset, unsigned char *pbyData, RTS_SIZE uiSize, RTS_RESULT *pResult);
typedef RTS_SIZE (CDECL * PFSYSSHAREDMEMORYREADBYTE) (RTS_HANDLE hShm, RTS_SIZE ulOffset, unsigned char *pbyData, RTS_SIZE uiSize, RTS_RESULT *pResult);
#if defined(SYSSHM_NOTIMPLEMENTED) || defined(SYSSHAREDMEMORYREADBYTE_NOTIMPLEMENTED)
	#define USE_SysSharedMemoryReadByte
	#define EXT_SysSharedMemoryReadByte
	#define GET_SysSharedMemoryReadByte(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysSharedMemoryReadByte(p0,p1,p2,p3,p4)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_SysSharedMemoryReadByte  FALSE
	#define EXP_SysSharedMemoryReadByte  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysSharedMemoryReadByte
	#define EXT_SysSharedMemoryReadByte
	#define GET_SysSharedMemoryReadByte(fl)  CAL_CMGETAPI( "SysSharedMemoryReadByte" ) 
	#define CAL_SysSharedMemoryReadByte  SysSharedMemoryReadByte
	#define CHK_SysSharedMemoryReadByte  TRUE
	#define EXP_SysSharedMemoryReadByte  CAL_CMEXPAPI( "SysSharedMemoryReadByte" ) 
#elif defined(MIXED_LINK) && !defined(SYSSHM_EXTERNAL)
	#define USE_SysSharedMemoryReadByte
	#define EXT_SysSharedMemoryReadByte
	#define GET_SysSharedMemoryReadByte(fl)  CAL_CMGETAPI( "SysSharedMemoryReadByte" ) 
	#define CAL_SysSharedMemoryReadByte  SysSharedMemoryReadByte
	#define CHK_SysSharedMemoryReadByte  TRUE
	#define EXP_SysSharedMemoryReadByte  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSharedMemoryReadByte", (RTS_UINTPTR)SysSharedMemoryReadByte, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysShmSysSharedMemoryReadByte
	#define EXT_SysShmSysSharedMemoryReadByte
	#define GET_SysShmSysSharedMemoryReadByte  ERR_OK
	#define CAL_SysShmSysSharedMemoryReadByte(p0,p1,p2,p3,p4)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysShm->ISysSharedMemoryReadByte(p1,p2,p3,p4) : ((ISysShm*)p0)->ISysSharedMemoryReadByte(p1,p2,p3,p4))
	#define CHK_SysShmSysSharedMemoryReadByte  (pISysShm != NULL)
	#define EXP_SysShmSysSharedMemoryReadByte  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysSharedMemoryReadByte
	#define EXT_SysSharedMemoryReadByte
	#define GET_SysSharedMemoryReadByte(fl)  CAL_CMGETAPI( "SysSharedMemoryReadByte" ) 
	#define CAL_SysSharedMemoryReadByte(p0,p1,p2,p3,p4)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysShm->ISysSharedMemoryReadByte(p1,p2,p3,p4) : ((ISysShm*)p0)->ISysSharedMemoryReadByte(p1,p2,p3,p4))
	#define CHK_SysSharedMemoryReadByte  (pISysShm != NULL)
	#define EXP_SysSharedMemoryReadByte  CAL_CMEXPAPI( "SysSharedMemoryReadByte" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysSharedMemoryReadByte  PFSYSSHAREDMEMORYREADBYTE pfSysSharedMemoryReadByte;
	#define EXT_SysSharedMemoryReadByte  extern PFSYSSHAREDMEMORYREADBYTE pfSysSharedMemoryReadByte;
	#define GET_SysSharedMemoryReadByte(fl)  s_pfCMGetAPI2( "SysSharedMemoryReadByte", (RTS_VOID_FCTPTR *)&pfSysSharedMemoryReadByte, (fl), 0, 0)
	#define CAL_SysSharedMemoryReadByte  pfSysSharedMemoryReadByte
	#define CHK_SysSharedMemoryReadByte  (pfSysSharedMemoryReadByte != NULL)
	#define EXP_SysSharedMemoryReadByte  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSharedMemoryReadByte", (RTS_UINTPTR)SysSharedMemoryReadByte, 0, 0) 
#endif




/**
 * <description>
 *	Routine to write values to shared memory,
 * </description>
 * <param name="hShm" type="IN">Handle to the shared memory</param>
 * <param name="ulOffset" type="IN">Offset in the shared memory</param>
 * <param name="pbyData" type="IN">Pointer to buffer with write data</param>
 * <param name="uiSize" type="IN">Number of bytes to write</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of bytes written to the shared memory</result>
 */
RTS_SIZE CDECL SysSharedMemoryWrite(RTS_HANDLE hShm, RTS_SIZE ulOffset, unsigned char *pbyData, RTS_SIZE uiSize, RTS_RESULT *pResult);
typedef RTS_SIZE (CDECL * PFSYSSHAREDMEMORYWRITE) (RTS_HANDLE hShm, RTS_SIZE ulOffset, unsigned char *pbyData, RTS_SIZE uiSize, RTS_RESULT *pResult);
#if defined(SYSSHM_NOTIMPLEMENTED) || defined(SYSSHAREDMEMORYWRITE_NOTIMPLEMENTED)
	#define USE_SysSharedMemoryWrite
	#define EXT_SysSharedMemoryWrite
	#define GET_SysSharedMemoryWrite(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysSharedMemoryWrite(p0,p1,p2,p3,p4)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_SysSharedMemoryWrite  FALSE
	#define EXP_SysSharedMemoryWrite  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysSharedMemoryWrite
	#define EXT_SysSharedMemoryWrite
	#define GET_SysSharedMemoryWrite(fl)  CAL_CMGETAPI( "SysSharedMemoryWrite" ) 
	#define CAL_SysSharedMemoryWrite  SysSharedMemoryWrite
	#define CHK_SysSharedMemoryWrite  TRUE
	#define EXP_SysSharedMemoryWrite  CAL_CMEXPAPI( "SysSharedMemoryWrite" ) 
#elif defined(MIXED_LINK) && !defined(SYSSHM_EXTERNAL)
	#define USE_SysSharedMemoryWrite
	#define EXT_SysSharedMemoryWrite
	#define GET_SysSharedMemoryWrite(fl)  CAL_CMGETAPI( "SysSharedMemoryWrite" ) 
	#define CAL_SysSharedMemoryWrite  SysSharedMemoryWrite
	#define CHK_SysSharedMemoryWrite  TRUE
	#define EXP_SysSharedMemoryWrite  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSharedMemoryWrite", (RTS_UINTPTR)SysSharedMemoryWrite, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysShmSysSharedMemoryWrite
	#define EXT_SysShmSysSharedMemoryWrite
	#define GET_SysShmSysSharedMemoryWrite  ERR_OK
	#define CAL_SysShmSysSharedMemoryWrite(p0,p1,p2,p3,p4)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysShm->ISysSharedMemoryWrite(p1,p2,p3,p4) : ((ISysShm*)p0)->ISysSharedMemoryWrite(p1,p2,p3,p4))
	#define CHK_SysShmSysSharedMemoryWrite  (pISysShm != NULL)
	#define EXP_SysShmSysSharedMemoryWrite  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysSharedMemoryWrite
	#define EXT_SysSharedMemoryWrite
	#define GET_SysSharedMemoryWrite(fl)  CAL_CMGETAPI( "SysSharedMemoryWrite" ) 
	#define CAL_SysSharedMemoryWrite(p0,p1,p2,p3,p4)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysShm->ISysSharedMemoryWrite(p1,p2,p3,p4) : ((ISysShm*)p0)->ISysSharedMemoryWrite(p1,p2,p3,p4))
	#define CHK_SysSharedMemoryWrite  (pISysShm != NULL)
	#define EXP_SysSharedMemoryWrite  CAL_CMEXPAPI( "SysSharedMemoryWrite" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysSharedMemoryWrite  PFSYSSHAREDMEMORYWRITE pfSysSharedMemoryWrite;
	#define EXT_SysSharedMemoryWrite  extern PFSYSSHAREDMEMORYWRITE pfSysSharedMemoryWrite;
	#define GET_SysSharedMemoryWrite(fl)  s_pfCMGetAPI2( "SysSharedMemoryWrite", (RTS_VOID_FCTPTR *)&pfSysSharedMemoryWrite, (fl), 0, 0)
	#define CAL_SysSharedMemoryWrite  pfSysSharedMemoryWrite
	#define CHK_SysSharedMemoryWrite  (pfSysSharedMemoryWrite != NULL)
	#define EXP_SysSharedMemoryWrite  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSharedMemoryWrite", (RTS_UINTPTR)SysSharedMemoryWrite, 0, 0) 
#endif




/**
 * <description>
 *	This function can be used to write a defined number of bytes in "byte-wise" manner to a Shared Memory area, starting at a certain offset address.
 * </description>
 * <param name="hShm" type="IN">Handle to the shared memory</param>
 * <param name="ulOffset" type="IN">Offset in the shared memory</param>
 * <param name="pbyData" type="IN">Pointer to buffer with write data</param>
 * <param name="uiSize" type="IN">Number of bytes to write</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of bytes written to the shared memory</result>
 */
RTS_SIZE CDECL SysSharedMemoryWriteByte(RTS_HANDLE hShm, RTS_SIZE ulOffset, unsigned char *pbyData, RTS_SIZE uiSize, RTS_RESULT *pResult);
typedef RTS_SIZE (CDECL * PFSYSSHAREDMEMORYWRITEBYTE) (RTS_HANDLE hShm, RTS_SIZE ulOffset, unsigned char *pbyData, RTS_SIZE uiSize, RTS_RESULT *pResult);
#if defined(SYSSHM_NOTIMPLEMENTED) || defined(SYSSHAREDMEMORYWRITEBYTE_NOTIMPLEMENTED)
	#define USE_SysSharedMemoryWriteByte
	#define EXT_SysSharedMemoryWriteByte
	#define GET_SysSharedMemoryWriteByte(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysSharedMemoryWriteByte(p0,p1,p2,p3,p4)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_SysSharedMemoryWriteByte  FALSE
	#define EXP_SysSharedMemoryWriteByte  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysSharedMemoryWriteByte
	#define EXT_SysSharedMemoryWriteByte
	#define GET_SysSharedMemoryWriteByte(fl)  CAL_CMGETAPI( "SysSharedMemoryWriteByte" ) 
	#define CAL_SysSharedMemoryWriteByte  SysSharedMemoryWriteByte
	#define CHK_SysSharedMemoryWriteByte  TRUE
	#define EXP_SysSharedMemoryWriteByte  CAL_CMEXPAPI( "SysSharedMemoryWriteByte" ) 
#elif defined(MIXED_LINK) && !defined(SYSSHM_EXTERNAL)
	#define USE_SysSharedMemoryWriteByte
	#define EXT_SysSharedMemoryWriteByte
	#define GET_SysSharedMemoryWriteByte(fl)  CAL_CMGETAPI( "SysSharedMemoryWriteByte" ) 
	#define CAL_SysSharedMemoryWriteByte  SysSharedMemoryWriteByte
	#define CHK_SysSharedMemoryWriteByte  TRUE
	#define EXP_SysSharedMemoryWriteByte  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSharedMemoryWriteByte", (RTS_UINTPTR)SysSharedMemoryWriteByte, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysShmSysSharedMemoryWriteByte
	#define EXT_SysShmSysSharedMemoryWriteByte
	#define GET_SysShmSysSharedMemoryWriteByte  ERR_OK
	#define CAL_SysShmSysSharedMemoryWriteByte(p0,p1,p2,p3,p4)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysShm->ISysSharedMemoryWriteByte(p1,p2,p3,p4) : ((ISysShm*)p0)->ISysSharedMemoryWriteByte(p1,p2,p3,p4))
	#define CHK_SysShmSysSharedMemoryWriteByte  (pISysShm != NULL)
	#define EXP_SysShmSysSharedMemoryWriteByte  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysSharedMemoryWriteByte
	#define EXT_SysSharedMemoryWriteByte
	#define GET_SysSharedMemoryWriteByte(fl)  CAL_CMGETAPI( "SysSharedMemoryWriteByte" ) 
	#define CAL_SysSharedMemoryWriteByte(p0,p1,p2,p3,p4)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysShm->ISysSharedMemoryWriteByte(p1,p2,p3,p4) : ((ISysShm*)p0)->ISysSharedMemoryWriteByte(p1,p2,p3,p4))
	#define CHK_SysSharedMemoryWriteByte  (pISysShm != NULL)
	#define EXP_SysSharedMemoryWriteByte  CAL_CMEXPAPI( "SysSharedMemoryWriteByte" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysSharedMemoryWriteByte  PFSYSSHAREDMEMORYWRITEBYTE pfSysSharedMemoryWriteByte;
	#define EXT_SysSharedMemoryWriteByte  extern PFSYSSHAREDMEMORYWRITEBYTE pfSysSharedMemoryWriteByte;
	#define GET_SysSharedMemoryWriteByte(fl)  s_pfCMGetAPI2( "SysSharedMemoryWriteByte", (RTS_VOID_FCTPTR *)&pfSysSharedMemoryWriteByte, (fl), 0, 0)
	#define CAL_SysSharedMemoryWriteByte  pfSysSharedMemoryWriteByte
	#define CHK_SysSharedMemoryWriteByte  (pfSysSharedMemoryWriteByte != NULL)
	#define EXP_SysSharedMemoryWriteByte  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysSharedMemoryWriteByte", (RTS_UINTPTR)SysSharedMemoryWriteByte, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSYSSHAREDMEMORYCREATE ISysSharedMemoryCreate;
 	PFSYSSHAREDMEMORYDELETE ISysSharedMemoryDelete;
 	PFSYSSHAREDMEMORYOPEN ISysSharedMemoryOpen;
 	PFSYSSHAREDMEMORYCLOSE ISysSharedMemoryClose;
 	PFSYSSHAREDMEMORYGETPOINTER ISysSharedMemoryGetPointer;
 	PFSYSSHAREDMEMORYREAD ISysSharedMemoryRead;
 	PFSYSSHAREDMEMORYREADBYTE ISysSharedMemoryReadByte;
 	PFSYSSHAREDMEMORYWRITE ISysSharedMemoryWrite;
 	PFSYSSHAREDMEMORYWRITEBYTE ISysSharedMemoryWriteByte;
 } ISysShm_C;

#ifdef CPLUSPLUS
class ISysShm : public IBase
{
	public:
		virtual RTS_HANDLE CDECL ISysSharedMemoryCreate(char *pszName, RTS_UINTPTR ulPhysicalAddress, RTS_SIZE *puiSize, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISysSharedMemoryDelete(void) =0;
		virtual RTS_HANDLE CDECL ISysSharedMemoryOpen(char *pszName, RTS_UINTPTR ulPhysicalAddress, RTS_SIZE *puiSize, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISysSharedMemoryClose(void) =0;
		virtual void * CDECL ISysSharedMemoryGetPointer(RTS_RESULT *pResult) =0;
		virtual RTS_SIZE CDECL ISysSharedMemoryRead(RTS_SIZE ulOffset, unsigned char *pbyData, RTS_SIZE uiSize, RTS_RESULT *pResult) =0;
		virtual RTS_SIZE CDECL ISysSharedMemoryReadByte(RTS_SIZE ulOffset, unsigned char *pbyData, RTS_SIZE uiSize, RTS_RESULT *pResult) =0;
		virtual RTS_SIZE CDECL ISysSharedMemoryWrite(RTS_SIZE ulOffset, unsigned char *pbyData, RTS_SIZE uiSize, RTS_RESULT *pResult) =0;
		virtual RTS_SIZE CDECL ISysSharedMemoryWriteByte(RTS_SIZE ulOffset, unsigned char *pbyData, RTS_SIZE uiSize, RTS_RESULT *pResult) =0;
};
	#ifndef ITF_SysShm
		#define ITF_SysShm static ISysShm *pISysShm = NULL;
	#endif
	#define EXTITF_SysShm
#else	/*CPLUSPLUS*/
	typedef ISysShm_C		ISysShm;
	#ifndef ITF_SysShm
		#define ITF_SysShm
	#endif
	#define EXTITF_SysShm
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSSHMITF_H_*/
