/**
 * <interfacename>SysMem</interfacename>
 * <description> 
 *	<p>The SysMem interface is projected to get access to heap memory or special
 *	memory areas for the plc program.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysMem')

#ifndef CDECL
	#define CDECL
#endif

/**
 * <category>Area Types</category>
 * <description>Application Area Type: None</description>
 */
#define DA_NONE			0x0000

/**
 * <category>Area Types</category>
 * <description>Application Area Type: Data</description>
 */
#define DA_DATA			0x0001

/**
 * <category>Area Types</category>
 * <description>Application Area Type: Constant</description>
 */
#define DA_CONSTANT		0x0002

/**
 * <category>Area Types</category>
 * <description>Application Area Type: Input</description>
 */
#define DA_INPUT		0x0004
/**
 * <category>Area Types</category>
 * <description>Application Area Type: Output</description>
 */
#define DA_OUTPUT		0x0008

/**
 * <category>Area Types</category>
 * <description>Application Area Type: Memory</description>
 */
#define DA_MEMORY		0x0010

/**
 * <category>Area Types</category>
 * <description>Application Area Type: Retain</description>
 */
#define DA_RETAIN		0x0020

/**
 * <category>Area Types</category>
 * <description>Application Area Type: Code</description>
 */
#define DA_CODE			0x0040

/* #define DA_AREA		0x0080	!RESERVED FOR INTERNAL USE IN CODESYS ONLY! */

/**
 * <category>Area Types</category>
 * <description>Application Area Type: Persistent</description>
 */
#define DA_PERSISTENT	0x0100

/**
 * <category>Area Types</category>
 * <description>Application Area Type: Non Safety data within Safity SIL2 systems</description>
 */
#define DA_NONSAFETY	0x0800

/**
 * <category>Area Types</category>
 * <description>Application Area Type: All</description>
 */
#define DA_ALL			0xFFFF

/**
 * <category>Area Types</category>
 * <description>Define for checking Area Types</description>
 */
#define IsArea(type, DA)	(type & DA)

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Settings to set the a special address for %M variables (markers)</description>
 */
#define CMPMEMKEY_MEMORYADDRESS	"WinCE.MemoryAddress"

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting for size of a special area (only one fixed big area for code and data)
 * Attention: only for use with Windows CE and versions &lt; 6
 * Attention: only for use together with a special device description with fixed size, e.g. 32 MB
 * Example:
 * <pre>
 *	&lt;ts:setting name="flags" type="integer" access="visible"&gt;
 *		&lt;ts:value&gt;0xfedf&lt;/ts:value&gt;
 *  &lt;/ts:setting&gt;
 *  &lt;ts:setting name="minimal-area-size" type="integer" access="visible"&gt;
 *		&lt;ts:value&gt;0x2000000&lt;/ts:value&gt;
 *  &lt;/ts:setting&gt;
 *  &lt;ts:setting name="maximal-area-size" type="integer" access="visible"&gt;
 *		&lt;ts:value&gt;0x2000000&lt;/ts:value&gt;
 *  &lt;/ts:setting&gt;
 *  &lt;ts:setting name="allocation-plus-in-percent" type="integer" access="visible"&gt;
 *		 &lt;ts:value&gt;0&lt;/ts:value&gt;
 *  &lt;/ts:setting&gt;
 * </pre>
 * </description>
 */
#define SYSMEMKEY_WINCE_CE5_BIGAREASIZE				"WinCE.CE5BigAreaSize"
#define SYSMEMKEY_WINCE_CE5_BIGAREASIZE_DEFAULT		0

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Avoid paging of all the RAM that is used by the process of the CoDeSys Runtime</description>
 */
#define SYSMEMKEY_INT_LINUX_MEMLOCK					"Linux.Memlock"
#define SYSMEMKEY_INT_LINUX_MEMLOCK_DEFAULT		1

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Specify the flags of a special (= not dynamically allocated) memory area</description>
 */
#define SYSMEMKEY_INT_VXWORKS_FLAGS         "VxWorks.Area.%u.Flags"
#define SYSMEMKEY_INT_VXWORKS_FLAGS_DEFAULT 0

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Specify the address of a special (= not dynamically allocated) memory area</description>
 */
#define SYSMEMKEY_INT_VXWORKS_ADDRESS         "VxWorks.Area.%u.Address"
#define SYSMEMKEY_INT_VXWORKS_ADDRESS_DEFAULT 0

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Specify the size of a special (= not dynamically allocated) memory area</description>
 */
#define SYSMEMKEY_INT_VXWORKS_SIZE         "VxWorks.Area.%u.Size"
#define SYSMEMKEY_INT_VXWORKS_SIZE_DEFAULT 0


/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Reserved function for the runtime system! Should not be used by an IEC application!
 */
typedef struct tagsysmemallocarea_struct
{
	RTS_IEC_STRING *szComponent;		/* VAR_INPUT */	
	RTS_IEC_WORD usType;				/* VAR_INPUT */	
	RTS_IEC_XWORD udiSize;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_BYTE *SysMemAllocArea;		/* VAR_OUTPUT */	
} sysmemallocarea_struct;

DEF_API(`void',`CDECL',`sysmemallocarea',`(sysmemallocarea_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x140ECCD0),0x03050C00)

/**
 * Reserved function for the runtime system! Should not be used by an IEC application!
 */
typedef struct tagsysmemalloccode_struct
{
	RTS_IEC_STRING *szComponent;		/* VAR_INPUT */	
	RTS_IEC_XWORD udiSize;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_BYTE *SysMemAllocCode;		/* VAR_OUTPUT */	
} sysmemalloccode_struct;

DEF_API(`void',`CDECL',`sysmemalloccode',`(sysmemalloccode_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB0EDB0B3),0x03050C00)

/**
 * Allocates data memory of the specified size
 * RETURN: Pointer to the memory block. 0 if no memory is not available
 */
typedef struct tagsysmemallocdata_struct
{
	RTS_IEC_STRING *szComponent;		/* VAR_INPUT */	/* Can be the library- or POU-name from IEC */
	RTS_IEC_XWORD udiSize;				/* VAR_INPUT */	/* Requested size of the memory block */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors_Itfs.library) */
	RTS_IEC_BYTE *SysMemAllocData;		/* VAR_OUTPUT */	
} sysmemallocdata_struct;

DEF_API(`void',`CDECL',`sysmemallocdata',`(sysmemallocdata_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xDF3F1AFF),0x03050C00)

/**
 * Compares the content of two buffers
 * RETURN: Returns 0 if the buffer contents are equal, else !=0
 */
typedef struct tagsysmemcmp_struct
{
	RTS_IEC_BYTE *pBuffer1;				/* VAR_INPUT */	/* Address of first memory area (buffer 1) */
	RTS_IEC_BYTE *pBuffer2;				/* VAR_INPUT */	/* Address of second memory area (buffer 2) */
	RTS_IEC_XWORD udiCount;				/* VAR_INPUT */	/* Number of bytes to be compared */
	RTS_IEC_DINT SysMemCmp;				/* VAR_OUTPUT */	
} sysmemcmp_struct;

DEF_API(`void',`CDECL',`sysmemcmp',`(sysmemcmp_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x40048CD7),0x03050C00)

/**
 * Copy the content from source (pSrc) to destination buffer (pDest)
 * RETURN: Pointer to the destination buffer, where the copy was done
 */
typedef struct tagsysmemcpy_struct
{
	RTS_IEC_BYTE *pDest;				/* VAR_INPUT */	/* Pointer to memory address to be copied to (target) */
	RTS_IEC_BYTE *pSrc;					/* VAR_INPUT */	/* Pointer to memory address to be copied from (source) */
	RTS_IEC_XWORD udiCount;				/* VAR_INPUT */	/* Number of bytes to be copied */
	RTS_IEC_BYTE *SysMemCpy;			/* VAR_OUTPUT */	
} sysmemcpy_struct;

DEF_API(`void',`CDECL',`sysmemcpy',`(sysmemcpy_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4B2D0668),0x03050C00)

/**
 * Routine to force swapping memory independant of the byteorder of the system!
 * RETURN: Number of bytes swapped:
 *	+ -1 = failed (size too large)
 *	+ >0 = Number of bytes swapped
 */
typedef struct tagsysmemforceswap_struct
{
	RTS_IEC_BYTE *pbyBuffer;			/* VAR_INPUT */	/* POINTER TO data TO swap. You can check, which order is selected by calling the routine with pbyBuffer=0 */
	RTS_IEC_UDINT udiSize;				/* VAR_INPUT */	/* Size of one element to swap */
	RTS_IEC_UDINT udiCount;				/* VAR_INPUT */	/* Number of elements to swap */
	RTS_IEC_DINT SysMemForceSwap;		/* VAR_OUTPUT */	
} sysmemforceswap_struct;

DEF_API(`void',`CDECL',`sysmemforceswap',`(sysmemforceswap_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x1718FBB3),0x03050C00)

/**
 * Reserved function for the runtime system! Should not be used by an IEC application!
 * RETURN: Error code
 */
typedef struct tagsysmemfreearea_struct
{
	RTS_IEC_STRING *szComponent;		/* VAR_INPUT */	
	RTS_IEC_BYTE *pMemory;				/* VAR_INPUT */	
	RTS_IEC_RESULT SysMemFreeArea;		/* VAR_OUTPUT */	
} sysmemfreearea_struct;

DEF_API(`void',`CDECL',`sysmemfreearea',`(sysmemfreearea_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x46CA745C),0x03050C00)

/**
 * Reserved function for the runtime system! Should not be used by an IEC application!
 * RETURN: Error code
 */
typedef struct tagsysmemfreecode_struct
{
	RTS_IEC_STRING *szComponent;		/* VAR_INPUT */	/* Component name */
	RTS_IEC_BYTE *pMemory;				/* VAR_INPUT */	/* POINTER TO code memory */
	RTS_IEC_RESULT SysMemFreeCode;		/* VAR_OUTPUT */	
} sysmemfreecode_struct;

DEF_API(`void',`CDECL',`sysmemfreecode',`(sysmemfreecode_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x92B98F40),0x03050C00)

/**
 * Release data memory
 * RETURN: Returns the runtime system error code (see CmpErrors_Itfs.library)
 */
typedef struct tagsysmemfreedata_struct
{
	RTS_IEC_STRING *szComponent;		/* VAR_INPUT */	/* Name of the component. Can be the library- or POU-name from IEC. */
	RTS_IEC_BYTE *pMemory;				/* VAR_INPUT */	/* Pointer to memory to be released */
	RTS_IEC_RESULT SysMemFreeData;		/* VAR_OUTPUT */	
} sysmemfreedata_struct;

DEF_API(`void',`CDECL',`sysmemfreedata',`(sysmemfreedata_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xFC9A307C),0x03050C00)

/**
 * Routine to get total size of the currently allocated heap memory
 * RETURN: Size of the memory in bytes that is currently allocated from the heap
 */
typedef struct tagsysmemgetcurrentheapsize_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors_Itfs.library) */
	RTS_IEC_XWORD SysMemGetCurrentHeapSize;	/* VAR_OUTPUT */
} sysmemgetcurrentheapsize_struct;

DEF_API(`void',`CDECL',`sysmemgetcurrentheapsize',`(sysmemgetcurrentheapsize_struct *p)',1,RTSITF_GET_SIGNATURE(0xFA1C1A89, 0x55C8863E),0x03050C00)

/**
 * Check if a pointer points to a valid address
 * RETURN: Returns the runtime system error code (see CmpErrors_Itfs.library):
 *	+ ERR_OK: Memory is valid
 *	+ ERR_FAILED: Memory is invalid. Cannot be accessed with the requested access mode bWrite
 */
typedef struct tagsysmemisvalidpointer_struct
{
	RTS_IEC_BYTE *ptr;					/* VAR_INPUT */	/* Pointer to the memory to be checked */
	RTS_IEC_XWORD udiSize;				/* VAR_INPUT */	/* Size of the memory to be checked */
	RTS_IEC_BOOL bWrite;				/* VAR_INPUT */	/* TRUE=Check, if memory can be written, FALSE=Check only for read access */
	RTS_IEC_RESULT SysMemIsValidPointer;	/* VAR_OUTPUT */	
} sysmemisvalidpointer_struct;

DEF_API(`void',`CDECL',`sysmemisvalidpointer',`(sysmemisvalidpointer_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x2B9D06D6),0x03050C00)

/**
 * Copy the content from source (pSrc) to destination buffer (pDest). This routine works for overlapping buffers too in opposite to SysMemCpy!
 * RETURN: Pointer to the destination buffer, where the move was done
 */
typedef struct tagsysmemmove_struct
{
	RTS_IEC_BYTE *pDest;				/* VAR_INPUT */	/* Pointer to memory address to be moved to (target) */
	RTS_IEC_BYTE *pSrc;					/* VAR_INPUT */	/* Pointer to memory address to be moved from (source) */
	RTS_IEC_XWORD udiCount;				/* VAR_INPUT */	/* Number of bytes to be moveed */
	RTS_IEC_BYTE *SysMemMove;			/* VAR_OUTPUT */	
} sysmemmove_struct;

DEF_API(`void',`CDECL',`sysmemmove',`(sysmemmove_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x9837ABBD),0x03050C00)

/**
 * Reallocate data memory with the specified size.
 * By use of this function the size of a memory block can be modified (reallocation). Therefor a pointer on the memory block to be
 * reallocated is passed to the function. The content of the memory block will not be modified. 
 * If the requested memory size cannot made available at the same place (address) , the function will allocate new memory space,
 * RETURN: Pointer to the memory block. 0 if no memory is not available
 */
typedef struct tagsysmemreallocdata_struct
{
	RTS_IEC_STRING *szComponent;		/* VAR_INPUT */	/* Name of the component. Can be the library- or POU-name from IEC. */
	RTS_IEC_BYTE *pMemory;				/* VAR_INPUT */	/* Pointer to memory to resize */
	RTS_IEC_XWORD udiSize;				/* VAR_INPUT */	/* Requested size of the memory */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors_Itfs.library) */
	RTS_IEC_BYTE *SysMemReallocData;	/* VAR_OUTPUT */	
} sysmemreallocdata_struct;

DEF_API(`void',`CDECL',`sysmemreallocdata',`(sysmemreallocdata_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x574ABCC0),0x03050C00)

/**
 * By use of this function a memory space is initialized with a specified value
 * RETURN: Pointer to the memory block which was initialized. 0 if the operation failed
 */
typedef struct tagsysmemset_struct
{
	RTS_IEC_BYTE *pDest;				/* VAR_INPUT */	/* Pointer to memory block to initialize */
	RTS_IEC_UDINT udiValue;				/* VAR_INPUT */	/* Value with which the memory is to be initialized */
	RTS_IEC_XWORD udiCount;				/* VAR_INPUT */	/* Number of bytes to be initialized in the memory block */
	RTS_IEC_BYTE *SysMemSet;			/* VAR_OUTPUT */	
} sysmemset_struct;

DEF_API(`void',`CDECL',`sysmemset',`(sysmemset_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x663CE5DB),0x03050C00)

/**
 * Routine to swap memory into littel endian. If little endian (intel) byteorder is received and platform has
 * big endian (motorola) byteorder. On little endian byteorder platforms, routine does nothing
 * RETURN: Number of bytes swapped:
 *	+ -1 = failed (iSize too large)
 *	+ 0 = no swapping necessary (little endian byteorder)
 *	+ >0 = Number of bytes swapped (big endian byteorder)
 */
typedef struct tagsysmemswap_struct
{
	RTS_IEC_BYTE *pbyBuffer;			/* VAR_INPUT */	/* Pointer to data to swap. You can check, which order is selected by calling the routine with pbyBuffer=0 */
	RTS_IEC_UDINT udiSize;				/* VAR_INPUT */	/* Size of one element to swap */
	RTS_IEC_UDINT udiCount;				/* VAR_INPUT */	/* Number of elements to swap */
	RTS_IEC_DINT SysMemSwap;			/* VAR_OUTPUT */	
} sysmemswap_struct;

DEF_API(`void',`CDECL',`sysmemswap',`(sysmemswap_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x77D02AA2),0x03050C00)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

/********** Functions **********/

/**
 * <description>Init routines for OS specific modules</description>
 * <param name="pInit" type="IN">Init Struct for OS specific modules</param>
 * <result>Result of Initialisation.</result>
 */
RTS_RESULT CDECL SysMemOSInit(INIT_STRUCT *pInit);
/**
 * <description>Hook Function for OS specific modules</description>
 * <param name="ulHook" type="IN">Hook Type for OS specific modules</param>
 * <param name="ulParam1" type="IN">First Hook Parameter for OS specific modules</param>
 * <param name="ulParam2" type="IN">Second Hook Parameter for OS specific modules</param>
 * <result>Result of OS Hook.</result>
 */
RTS_RESULT CDECL SysMemOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>Allocates data memory of the specified size.
 * IMPLEMENTATION NOTE:
 * New allocated memory must be initialized with 0!
 * </description>
 * <param name="pszComponentName" type="IN">Name of the component</param>
 * <param name="ulSize" type="IN">Requested size of the memory</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Memory could be allocated</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">If memory could not be allocated</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_OUT_OF_LIMITS">Memory could not be allocated because memory limit of the component has been reached</errorcode>
 * <result>Pointer to the memory block. NULL if no memory is available.</result>
 */
DEF_ITF_API(`void*',`CDECL',`SysMemAllocData',`(char *pszComponentName, RTS_SIZE ulSize, RTS_RESULT *pResult)')

/**
 * <description>Reallocate data memory with the specified size</description>
 * <param name="pszComponentName" type="IN">Name of the component</param>
 * <param name="pData" type="IN">Pointer to memory to resize</param>
 * <param name="ulSize" type="IN">Requested size of the memory</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the memory block. NULL if no memory is available.</result>
 */
DEF_ITF_API(`void*',`CDECL',`SysMemReallocData',`(char *pszComponentName, void* pData, RTS_SIZE ulSize, RTS_RESULT *pResult)')

/**
 * <description>Release data memory</description>
 * <param name="pszComponentName" type="IN">Name of the component</param>
 * <param name="pData" type="IN">Pointer to memory to be released. If pointer is NULL, ERR_PARAMETER is returned.</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Memory could be released</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Memory pointer is NULL</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMemFreeData',`(char *pszComponentName, void* pData)')

/**
 * <description>
 *	Allocates data area of an application.
 *	Can be used to set an application area to a specific memory.
 * IMPLEMENTATION NOTE:
 * New allocated memory must be initialized with 0, but _not_ the retain memory!
 * </description>
 * <param name="pszComponentName" type="IN" range="[NULL,VALID_COMPONENT_NAME]">Name of the component</param>
 * <param name="usType" type="IN" range="[DA_NONE,DA_CODE,DA_CONSTANT,DA_DATA,DA_RETAIN,INVALID_DA_AREA]">Type of the area (see category Area Types)</param>
 * <param name="ulSize" type="IN" range="[0,VALID_SIZE,RTS_SIZE_MAX]">Requested size of the memory</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="pResult" type="ERR_OK">Memory Area could be allocated</errorcode>
 * <errorcode name="pResult" type="ERR_FAILED">The requested Area could not be allocated - invalid combination of DA-Flags, or all areas of this type are already in use</errorcode>
 * <errorcode name="pResult" type="ERR_NOT_SUPPORTED">Allocation is not supported, it might be allocated dynamically</errorcode>
 * <errorcode name="pResult" type="ERR_OUT_OF_LIMITS">The requested area size was too large or too small</errorcode>
 * <errorcode name="pResult" type="ERR_APP_DONT_INIT_AREA">The returned area must not be initialized outside, because the content is handled inside this function!</errorcode>
 * <result>Pointer to the memory block. NULL if no memory is available (allocate area on heap).</result>
 */
DEF_ITF_API(`void*',`CDECL',`SysMemAllocArea',`(char *pszComponentName, unsigned short usType, RTS_SIZE ulSize, RTS_RESULT *pResult)')

/**
 * <description>
 * <p>Release data area of an application.</p>
 * <p>Note: On SIL2 Runtimes, this function may generate an exception, when called in SAFE-Mode.</p>
 * </description>
 * <param name="pszComponentName" type="IN" range="[NULL,VALID_COMPONENT_NAME]">Name of the component</param>
 * <param name="pData" type="IN" range="[NULL,VALID_AREA_POINTER,INVALID_AREA_POINTER]">Pointer to area to free</param>
 * <parampseudo name="OperationMode" type="IN" range="[RTS_SIL2_OPMODE_SAFE,RTS_SIL2_OPMODE_DEBUG]">Specifies the current operation mode of the PLC</parampseudo>
 * <parampseudo name="bExceptionGenerated" type="OUT" range="[TRUE,FALSE]">Specifies, if an exception occured, or not</parampseudo>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Memory Area could be freed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">The memory area could not be freed (wrong area pointer, or area is not allocated)</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Parameter pData was NULL</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMemFreeArea',`(char *pszComponentName, void* pData)')

/**
 * <description>
 *	Allocate code memory with the specified size (in the memory, code can be executed).
 *	NOTE: This routine can be used on architectures, where standard data memory is protected
 *	against code execution!
 * IMPLEMENTATION NOTE:
 * New allocated memory must be initialized with 0!
 * </description>
 * <param name="pszComponentName" type="IN">Name of the component</param>
 * <param name="ulSize" type="IN">Requested size of the memory</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the memory block. NULL if no memory is available.</result>
 */
DEF_ITF_API(`void*',`CDECL',`SysMemAllocCode',`(char *pszComponentName, RTS_SIZE ulSize, RTS_RESULT *pResult)')

/**
 * <description>
 *	Release code memory
 * </description>
 * <param name="pszComponentName" type="IN">Name of the component</param>
 * <param name="pData" type="IN">Pointer to memory to resize</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMemFreeCode',`(char *pszComponentName, void* pCode)')

/**
 * <description>
 *	Check if a pointer points to a valid address.
 * </description>
 * <param name="ptr" type="IN" range="[NULL,VALID_MEMORY,INVALID_MEMORY]">Pointer to the memory to be checked</param>
 * <param name="ulSize" type="IN" range="[0,VALID_SIZE]">Size of the memory to be checked</param>
 * <param name="bWrite" type="IN" range="[0,1]">1=Check, if memory can be written, 0=Check only for read access</param>
 * <result>Error code:
 * <ul>
 *		<li>ERR_OK: Memory is valid</li>
 *		<li>ERR_FAILED: Memory is invalid. Cannot be accessed with the requested access mode bWrite</li>
 * </ul>
 * </result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMemIsValidPointer',`(void* ptr, RTS_SIZE ulSize, int bWrite)')

/**
 * <description>
 *	Routine to swap memory. If little endian (intel) byteorder is received and platform has
 *	big endian (motorola) byteorder. On little endian byteorder platforms, routine does nothing.
 * </description>
 * <param name="pbyBuffer" type="IN">Pointer to data to swap. You can check, which order is selected by 
 *									calling the routine with pbyBuffer=NULL</param>
 * <param name="iSize" type="IN">Size of one element to swap</param>
 * <param name="iCount" type="IN">Number of elements to swap</param>
 * <result>	-1 = failed (iSize too large)
 *    		 0 = no swapping necessary (little endian byteorder)
 *			>0 = Number of bytes swapped (big endian byteorder)
 *			 1 = big endian byteorder, if pbyBuffer=NULL
 * </result>
 */
DEF_ITF_API(`int',`CDECL',`SysMemSwap',`(unsigned char *pbyBuffer, int iSize, int iCount)')

/**
 * <description>
 *	Routine to force swapping memory independant of the byteorder of the system!
 * </description>
 * <param name="pbyBuffer" type="IN">Pointer to data to swap. You can check, which order is selected by 
 *									calling the routine with pbyBuffer=NULL</param>
 * <param name="iSize" type="IN">Size of one element to swap</param>
 * <param name="iCount" type="IN">Number of elements to swap</param>
 * <result>	-1 = failed (iSize too large)
 *			>0 = Number of bytes swapped
 * </result>
 */
DEF_ITF_API(`int',`CDECL',`SysMemForceSwap',`(unsigned char *pbyBuffer, int iSize, int iCount)')

/**
 * <description>
 *	Routine to get total size of the currently allocated heap memory.
 * </description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="pResult" type="ERR_OK">Current heap size is available</errorcode>
 * <errorcode name="pResult" type="ERR_NOT_SUPPORTED">Determination of current heap size not supported. CmpMemGC is necessary!</errorcode>
 * <result>Size of the memory in bytes that is currently allocated from the heap</result>
 */
DEF_ITF_API(`RTS_SIZE',`CDECL',`SysMemGetCurrentHeapSize',`(RTS_RESULT *pResult)')

#ifdef __cplusplus
}
#endif
