/**
 * <interfacename>CmpMemGC</interfacename>
 * <description> 
 *	Interface of the garbage collector, that detects memory leaks and memory overwrite operations.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpMemGC')

REF_ITF(`CMUtilsItf.m4')
REF_ITF(`CMUtilsHashItf.m4')

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Enable CheckBounds check in comm cycle hook
 *	this leads to additional load if components or applications allocate a lot of dynamic memory
 *  (or if there is a memory leak somewhere)
 * </description>
 */
#define ENABLE_CYCLIC_MEMGC_CHECK							"EnableCyclicMemGcCheck"
#define ENABLE_CYCLIC_MEMGC_CHECK_DEFAULT					0


typedef struct GARBAGE_COLLECTORtag *PGARBAGE_COLLECTOR;

/**
 * <category>Garbage collector entry</category>
 * <description>Description of one memory entry in the garbage collector</description>
 * <param name="szComponent">Component name, that allocates this memory block</param>
 * <param name="pprev">Pointer to previous garbage memory</param>
 * <param name="pnext">Pointer to next garbage memory</param>
 * <param name="ulSize">Size of memory block</param>
 * <param name="Mem">Begin of data memory</param>
 */
typedef struct GARBAGE_COLLECTORtag
{
	RTS_STRING_CLASS componentName;
	PGARBAGE_COLLECTOR pprev;
	PGARBAGE_COLLECTOR pnext;
	RTS_SIZE ulSize;
#ifndef CMUTILSHASH_NOTIMPLEMENTED
    CMUtlHashEntry hashEntry;
#endif
	RTS_UI8 Mem;
} GARBAGE_COLLECTOR;

/**
 * <category>OperationID</category>
 * <description>Operation ID for the supervision of CmpMemGC</description>
 * <param name="OPID_CmpMemGC" type="IN"></param>
 * <param name="OPID_CmpMemGC_Description" type="IN"></param>
 */
#define RTS_OPID_CmpMemGC								1
#define RTS_OPID_CmpMemGC_Description					"CmpMemGC"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>
 *	Routine to get size of a new heap memblock with garbage collection.
 * </description>
 * <param name="ulSize" type="IN">Size of the memory block, that should be checked</param>
 * <result>Number of bytes to allocate included the garbage memory overhead</result>
 */
DEF_ITF_API(`RTS_SIZE',`CDECL',`MemGCGetSize',`(RTS_SIZE ulSize)')

/**
 * <description>
 *	Routine to get total size of the currently allocated heap memory.
 * </description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Size of the memory in bytes that is currently allocated from the heap</result>
 */
DEF_ITF_API(`RTS_SIZE',`CDECL',`MemGCGetCurrentHeapSize',`(RTS_RESULT *pResult)')

/**
 * <description>
 *	Routine to add a new heap memblock to the garbage collector.	
 * </description>
 * <param name="pszComponentName" type="IN">Component name, that allocates the memory</param>
 * <param name="pMem" type="IN">Pointer to the memory block</param>
 * <param name="ulSizeGc" type="IN">Size of the memory block including the garbage collection overhead (see result of MemGCGetSize)</param>
 * <result>Pointer to the memory data block</result>
 */
DEF_ITF_API(`void *',`CDECL',`MemGCAdd',`(char *pszComponentName, void *pMem, RTS_SIZE ulSizeGc)')

/**
 * <description>
 *	Routine to remove a heap memblock from the garbage collector.	
 * </description>
 * <param name="pszComponentName" type="IN">Component name, that allocates the memory</param>
 * <param name="pMem" type="IN">Pointer to the memory data block</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the memory block to free</result>
 */
DEF_ITF_API(`void *',`CDECL',`MemGCRemove',`(char *pszComponentName, void *pMem, RTS_RESULT *pResult)')

/**
 * <description>
 *	Routine to check all registered memory block bounds for overwrite actions.	
 * </description>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`MemGCCheckBoundsAll',`(void)')

/**
 * <description>
 *	Routine to find original heap memory pointer from garbage collector.
 * </description>
 * <param name="pMem" type="IN">Pointer to the memory data block</param>
 * <result>Pointer to the garabge collector entry</result>
 */
DEF_ITF_API(`GARBAGE_COLLECTOR *',`CDECL',`MemGCFindEntry',`(void *pMem)')

/**
 * <description>
 *	Routine to get the head node of the garbage collector to check for garbage memory.
 * </description>
 * <param name="ppHead" type="IN">Get first entry of the garbage collector list</param>
 * <result>Pointer to the garabge collector entry</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`MemGCGetHead',`(GARBAGE_COLLECTOR **ppHead)')

/**
 * <description>
 *	Routine to get the pointer to the real memory block.
 * </description>
 * <param name="pGarbage" type="IN">Garbage collector entry</param>
 * <result>Get memory block from the garbage collector entry</result>
 */
DEF_ITF_API(`void *',`CDECL',`MemGCGetMemBlock',`(GARBAGE_COLLECTOR *pGarbage)')

#ifdef __cplusplus
}
#endif
