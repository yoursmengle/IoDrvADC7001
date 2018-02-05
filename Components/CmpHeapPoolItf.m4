/**
 * <interfacename>CmpHeapAlloc</interfacename>
 * <description>
 *  <p>Allocator for the heap management on limited targets.</p>
 *	<p>This allocator implements a well-known buddy algorithm.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */
 
SET_INTERFACE_NAME(`CmpHeapPool')
 
#include "CmpItf.h" 

#ifndef RTS_MEM_REGION_DEFINED
#define RTS_MEM_REGION_DEFINED

/**
 *	<description>
 *	 Abstract Memory Region.
 *	</description>
 */  
typedef struct tagRTS_MEM_REGION
{
	/* base address of the region */
	RTS_UINTPTR base;

	/* region size */
	RTS_SIZE		size;

} RTS_MEM_REGION;


#endif

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * <description>
 *	Initializes a buddies pool: builds up sets of blocks with sizes of power of
 *	2 using a list of memory regions supplied with the second parameter.
 * </description>
 * <param name="pRegionsList" type="IN">Array of memory regions in which the last element should be of size 0</param>
 * <param name="pResult" type="OUT">Pointer to an error code</param>
 * <result>Handle to the pool or RTS_INVALID_HANDLE</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`HeapPoolInit',`(RTS_MEM_REGION* pRegionsList, RTS_RESULT* pResult)')

/** 
 * <description>
 *	Allocates a memory block out of the pool
 * </description>
 * <param name="hPool" type="IN">Handle to a pool object</param>
 * <param name="size" type="IN">Requested size of memory to be allocated</param>
 * <param name="pResult" type="OUT">Pointer to an error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Memory block has been allocated successfully</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOMEMORY">Memory block could not be allocated, not enough memory</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_FAILED">Memory corrupted inside the pool</errorcode>
 * <result>Pointer to the allocated block of memory</result>
 */
DEF_ITF_API(`void*',`CDECL',`HeapPoolAlloc',`(RTS_HANDLE hPool, RTS_SIZE size, RTS_RESULT* pResult)')

/**
 * <description>
 *	Puts a memory block back to the pool and performs defragmentation.
 * </description>
 * <param name="hPool" type="IN">Handle to a pool object</param>
 * <param name="pMem" type="IN">Pointer to a memory block to be returned to the pool</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`HeapPoolFree',`(RTS_HANDLE hPool, void* pMem)')

#ifdef __cplusplus
}
#endif

