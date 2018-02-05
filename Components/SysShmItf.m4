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

SET_INTERFACE_NAME(`SysShm')

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

DEF_API(`void',`CDECL',`syssharedmemoryclose',`(syssharedmemoryclose_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x93F75F86),0x03050500)

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

DEF_API(`void',`CDECL',`syssharedmemorycreate',`(syssharedmemorycreate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x9DA848E2),0x03050500)

/**
 * Delete a shared memory object specified by handle
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsyssharedmemorydelete_struct
{
	RTS_IEC_HANDLE hShm;				/* VAR_INPUT */	/* Handle to the shared memory */
	RTS_IEC_RESULT SysSharedMemoryDelete;	/* VAR_OUTPUT */	
} syssharedmemorydelete_struct;

DEF_API(`void',`CDECL',`syssharedmemorydelete',`(syssharedmemorydelete_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x83C20043),0x03050500)

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

DEF_API(`void',`CDECL',`syssharedmemorygetpointer',`(syssharedmemorygetpointer_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x94066BAD),0x03050500)

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

DEF_API(`void',`CDECL',`syssharedmemoryopen',`(syssharedmemoryopen_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x41FB9CC1),0x03050500)

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

DEF_API(`void',`CDECL',`syssharedmemoryopen2',`(syssharedmemoryopen2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x69CA7C0D),0x03050500)

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

DEF_API(`void',`CDECL',`syssharedmemoryread',`(syssharedmemoryread_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x67AB02BB),0x03050500)

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

DEF_API(`void',`CDECL',`syssharedmemoryreadbyte',`(syssharedmemoryreadbyte_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0E49748E),0x03050500)

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

DEF_API(`void',`CDECL',`syssharedmemorywrite',`(syssharedmemorywrite_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xE23019DB),0x03050500)

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

DEF_API(`void',`CDECL',`syssharedmemorywritebyte',`(syssharedmemorywritebyte_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF3240E6E),0x03050500)

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
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysSharedMemoryCreate',`(char *pszName, RTS_UINTPTR ulPhysicalAddress, RTS_SIZE *puiSize, RTS_RESULT *pResult)')

/**
 * <description>
 *  Delete a shared memory object specified by handle
 * </description>
 * <param name="hShm" type="IN">Handle to the shared memory</param>
 * <result>error code</result>
 */
DEF_DELETEITF_API(`RTS_RESULT',`CDECL',`SysSharedMemoryDelete',`(RTS_HANDLE hShm)')

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
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysSharedMemoryOpen',`(char *pszName, RTS_UINTPTR ulPhysicalAddress, RTS_SIZE *puiSize, RTS_RESULT *pResult)')

/**
 * <description>
 *  Close a shared memory object specified by handle
 * </description>
 * <param name="hShm" type="IN">Handle to the shared memory</param>
 * <result>error code</result>
 */
DEF_DELETEITF_API(`RTS_RESULT',`CDECL',`SysSharedMemoryClose',`(RTS_HANDLE hShm)')

/**
 * <description>
 *  Get the pointer to the shared memory
 * </description>
 * <param name="hShm" type="IN">Handle to the shared memory</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the shared memory for data access</result>
 */
DEF_HANDLEITF_API(`void *',`CDECL',`SysSharedMemoryGetPointer',`(RTS_HANDLE hShm, RTS_RESULT *pResult)')

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
DEF_HANDLEITF_API(`RTS_SIZE',`CDECL',`SysSharedMemoryRead',`(RTS_HANDLE hShm, RTS_SIZE ulOffset, unsigned char *pbyData, RTS_SIZE uiSize, RTS_RESULT *pResult)')

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
DEF_HANDLEITF_API(`RTS_SIZE',`CDECL',`SysSharedMemoryReadByte',`(RTS_HANDLE hShm, RTS_SIZE ulOffset, unsigned char *pbyData, RTS_SIZE uiSize, RTS_RESULT *pResult)')

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
DEF_HANDLEITF_API(`RTS_SIZE',`CDECL',`SysSharedMemoryWrite',`(RTS_HANDLE hShm, RTS_SIZE ulOffset, unsigned char *pbyData, RTS_SIZE uiSize, RTS_RESULT *pResult)')

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
DEF_HANDLEITF_API(`RTS_SIZE',`CDECL',`SysSharedMemoryWriteByte',`(RTS_HANDLE hShm, RTS_SIZE ulOffset, unsigned char *pbyData, RTS_SIZE uiSize, RTS_RESULT *pResult)')

#ifdef __cplusplus
}
#endif
