/**
 * <interfacename>CmpMemPoolHash</interfacename>
 * <description>
 *	Interface to get a hash table around a MemPool. Because of this, you can use a unique handle to a MemPool object instead of the pointer to the MemPool object!
 *	This is because is you release a MemPool object, reuse it for a new MemPool operation and release the old one a second time
 *
 *	Usage:
 *		 1. Creating a mempool hash table using static memory [recommended]:
 *
 *			 #define MY_NUM_OF_HASHENTRIES	10
 *			 RTS_UI8 s_hashTableBuffer[MEMPOOLHASH_GET_HASHTABLE_LEN( MY_NUM_OF_HASHENTRIES )];
 *
 *			 // Create mempool hash table
 *			 RTS_RESULT result
 *			 RTS_HANDLE hMemPool = CAL_MemPoolCreateStatic(...);
 *			 RTS_HANDLE hMemPoolHashTable = CAL_MemPoolCreateHashTable2(hMemPool, 10, s_hashTableBuffer, COMPONENT_NAME, &result);
 *
 *		 2. Creating a mempool hash table using dynamic memory:
 *
 *			 // Create mempool hash table
 *			 RTS_RESULT result
 *			 RTS_HANDLE hMemPool = CAL_MemPoolCreateStatic(...);
 *			 RTS_HANDLE hMemPoolHashTable = CAL_MemPoolCreateHashTable(hMemPool, 10, COMPONENT_NAME, &result);
 *
 *		// Delete hash table
 *		CAL_MemPoolDeleteHashTable(hMemPoolHashTable);
 *
		// Alloc a new MemPool block must be done in 2 steps:
 *		// Step1: Get handle/alloc new block out of the MemPool (instead of CAL_MemPoolGetBlock())!
 *		RTS_HANDLE hNewMemPoolBlock = CAL_MemPoolGetBlockHashed(hMemPoolHashTable, 1, &result);
 *
 *		// Step2: Get pointer MemPoolBlock (which is retrieved typically by CAL_MemPoolGetBlock())
 *		void *pMemPoolBlock = CAL_MemPoolGetBlockByHash(hMemPoolHashTable, hNewMemPoolBlock, &result)
 *	
 *		// Release a MemPool block must be done in 2 steps:
 *		// Step1: Remove a block from hash table and the MemPool iterator
 *	    CAL_MemPoolRemoveBlockHashed(hMemPoolHashTable, hNewMemPoolBlock);
 *
 *		// Step2: Release a MemPool block and put it back in the MemPool
 *	    CAL_MemPoolPutBlock(hMemPoolHashTable, pMemPoolBlock)
 *
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpMemPoolHash')
REF_ITF(`CMUtilsHashItf.m4')

#define MemPoolHashEntry	CMUtlHashEntry
#define MEMPOOLHASH_GET_HASHTABLE_LEN(numOfHashEntries)		((numOfHashEntries) * sizeof(MemPoolHashEntry**))

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>
 *  Must be called _after_ MemPoolCreateDynamic / MemPoolCreateStatic to create a hash table on top of a memory pool
 * </description>
 * <param name="hMemPool" type="IN">Handle to the mem pool created by MemPoolCreateDynamic / MemPoolCreateStatic</param>
 * <param name="sNumHashEntries" type="IN">Lenght of the hash table respectively the number of elements that can be stored in the hash table without any collision.
 *		NOTE:
 *		Hash table is allocated on heap via SysMemAllocData() within this function. If you would like to provide a static memory for the hash table. Use MemPoolCreateHashTable2() instead!
 * </param>
 * <param name="pszComponentName" type="IN">Pointer to the component name of the caller</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Hash table could be created</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOMEMORY">No memory to create the hash table</errorcode>  
 * <errorcode name="RTS_RESULT pResult" type="ERR_FAILED">Hash table failed to create</errorcode> 
 * <result>Handle to the create hash table around the mempool specified by hMemPool</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`MemPoolCreateHashTable',`(RTS_HANDLE hMemPool, RTS_SIZE sNumHashEntries, char *pszComponentName, RTS_RESULT *pResult)')

/**
 * <description>
 *  Must be called _after_ MemPoolCreateDynamic / MemPoolCreateStatic to create a hash table on top of a memory pool
 * </description>
 * <param name="hMemPool" type="IN">Handle to the mem pool created by MemPoolCreateDynamic / MemPoolCreateStatic</param>
 * <param name="sNumHashEntries" type="IN">Num of blocks that are managed in the hash table</param> 
 * <param name="pHashTableBuffer" type="IN">Pointer to the hash table (can be static memory). Length must be (sNumHashEntries * sizeof(RTS_UI8 *))!.
 *		NOTE:
 *		If pHashTableBuffer = NULL. the hash table will be allocated on heap via SysMemAllocData() within this function.
 * </param>
 * <param name="pszComponentName" type="IN">Pointer to the component name of the caller</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Hash table could be created</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOMEMORY">No memory to create the hash table</errorcode>  
 * <errorcode name="RTS_RESULT pResult" type="ERR_FAILED">Hash table failed to create</errorcode> 
 * <result>Handle to the create hash table around the mempool specified by hMemPool</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`MemPoolCreateHashTable2',`(RTS_HANDLE hMemPool, RTS_SIZE sNumHashEntries, RTS_UI8 *pHashTableBuffer, char *pszComponentName, RTS_RESULT *pResult)')

/**
 * <description>
 *  Must be called _before_ MemPoolDelete to release a hash table on top of a memory pool
 * </description>
 * <param name="hMemPoolHashTable" type="IN">Handle to the hash table created by MemPoolCreateHashTable()</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Hash table could be released</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Invalid hash table handle</errorcode> 
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Hash table failed to release</errorcode> 
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`MemPoolDeleteHashTable',`(RTS_HANDLE hMemPoolHashTable)')

/**
 * <description>
 *  Must be called instead of MemPoolGetBlock2! Returned the hash handle, that must be used instead of the MemPool handle directly!
 * </description>
 * <param name="hMemPool" type="IN">Handle to the mem pool created by MemPoolCreateDynamic / MemPoolCreateStatic</param>
 * <param name="nNumOfNewElements" type="IN">Number of new elements to extend in the underlying mem pool to get the new memory block</param> 
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">New hashed mempool block can be retrieved</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Invalid hash table handle</errorcode> 
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOMEMORY">There is no more memory left to get the hashed mempool block</errorcode>
 * <result>Handle to the new mempool block</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`MemPoolGetBlockHashed',`(RTS_HANDLE hMemPoolHashTable, RTS_UI32 nNumOfNewElements, RTS_RESULT *pResult)')

/**
 * <description>
 *  Must be called instead of MemPoolGetBlock2! Returned the hash handle, that must be used instead of the MemPool handle directly!
 *	NOTE:
 *  Instead of using MemPoolGetBlockHashed() you can specify the new hash entry outside by the caller (MemPoolHashEntry)! So we don't need to allocated
 *  new memory on the heap for a hash entry.
 * </description>
 * <param name="hMemPool" type="IN">Handle to the mem pool created by MemPoolCreateDynamic / MemPoolCreateStatic</param>
 * <param name="nNumOfNewElements" type="IN">Number of new elements to extend in the underlying mem pool to get the new memory block</param> 
 * <param name="offsetHashEntry" type="IN">Offset within the MemPoolBlock, where the member of MemPoolHashEntry is located
 *	NOTE:
 *		If offsetHashEntry = RTS_UI32_MAX, a new hash entry is allocated from heap via SysMemAllocData()!
 * </param> 
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">New hashed mempool block can be retrieved</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Invalid hash table handle</errorcode> 
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOMEMORY">There is no more memory left to get the hashed mempool block</errorcode>
 * <result>Handle to the new mempool block</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`MemPoolGetBlockHashed2',`(RTS_HANDLE hMemPoolHashTable, RTS_UI32 nNumOfNewElements, RTS_UI32 offsetHashEntry, RTS_RESULT *pResult)')

/**
 * <description>
 *  Must be called instead of MemPoolRemoveUsedBlock to remove a hashed memory block from hash table! MemPoolPutBlock() must be called as is.
 * </description>
 * <param name="hMemPool" type="IN">Handle to the mem pool created by MemPoolCreateDynamic / MemPoolCreateStatic</param>
 * <param name="hHash" type="IN">Handle to the hashed mempool object retrieved by MemPoolGetBlockHashed() or MemPoolGetBlockHashed2()</param> 
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Hashed mempool object could be removed</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Invalid hash table handle or hash mempool object</errorcode> 
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Hashed mempool object failed to remove</errorcode> 
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`MemPoolRemoveBlockHashed',`(RTS_HANDLE hMemPoolHashTable, RTS_HANDLE hHash)')

/**
 * <description>
 *  Can be used to get the mempool data pointer specified by ith hash. 
 * </description>
 * <param name="hMemPool" type="IN">Handle to the mem pool created by MemPoolCreateDynamic / MemPoolCreateStatic</param>
 * <param name="hHash" type="IN">Handle to the hashed mempool object retrieved by MemPoolGetBlockHashed() or MemPoolGetBlockHashed2()</param> 
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Data pointer could be retrieved because of its hash</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Invalid hash table handle or hash mempool object</errorcode> 
 * <errorcode name="RTS_RESULT pResult" type="ERR_NO_OBJECT">No data pointer found for this hash</errorcode>
 * <result>Pointer to the data of the hashed mempool object</result>
 */
 DEF_ITF_API(`void*',`CDECL',`MemPoolGetBlockByHash',`(RTS_HANDLE hMemPoolHashTable, RTS_HANDLE hHash, RTS_RESULT *pResult)')

#ifdef __cplusplus
}
#endif
