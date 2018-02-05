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


	
	
#ifndef _CMPMEMPOOLHASHITF_H_
#define _CMPMEMPOOLHASHITF_H_

#include "CmpStd.h"

 

 



#include "CMUtilsHashItf.h"

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
RTS_HANDLE CDECL MemPoolCreateHashTable(RTS_HANDLE hMemPool, RTS_SIZE sNumHashEntries, char *pszComponentName, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFMEMPOOLCREATEHASHTABLE) (RTS_HANDLE hMemPool, RTS_SIZE sNumHashEntries, char *pszComponentName, RTS_RESULT *pResult);
#if defined(CMPMEMPOOLHASH_NOTIMPLEMENTED) || defined(MEMPOOLCREATEHASHTABLE_NOTIMPLEMENTED)
	#define USE_MemPoolCreateHashTable
	#define EXT_MemPoolCreateHashTable
	#define GET_MemPoolCreateHashTable(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolCreateHashTable(p0,p1,p2,p3)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_MemPoolCreateHashTable  FALSE
	#define EXP_MemPoolCreateHashTable  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolCreateHashTable
	#define EXT_MemPoolCreateHashTable
	#define GET_MemPoolCreateHashTable(fl)  CAL_CMGETAPI( "MemPoolCreateHashTable" ) 
	#define CAL_MemPoolCreateHashTable  MemPoolCreateHashTable
	#define CHK_MemPoolCreateHashTable  TRUE
	#define EXP_MemPoolCreateHashTable  CAL_CMEXPAPI( "MemPoolCreateHashTable" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOLHASH_EXTERNAL)
	#define USE_MemPoolCreateHashTable
	#define EXT_MemPoolCreateHashTable
	#define GET_MemPoolCreateHashTable(fl)  CAL_CMGETAPI( "MemPoolCreateHashTable" ) 
	#define CAL_MemPoolCreateHashTable  MemPoolCreateHashTable
	#define CHK_MemPoolCreateHashTable  TRUE
	#define EXP_MemPoolCreateHashTable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolCreateHashTable", (RTS_UINTPTR)MemPoolCreateHashTable, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolHashMemPoolCreateHashTable
	#define EXT_CmpMemPoolHashMemPoolCreateHashTable
	#define GET_CmpMemPoolHashMemPoolCreateHashTable  ERR_OK
	#define CAL_CmpMemPoolHashMemPoolCreateHashTable pICmpMemPoolHash->IMemPoolCreateHashTable
	#define CHK_CmpMemPoolHashMemPoolCreateHashTable (pICmpMemPoolHash != NULL)
	#define EXP_CmpMemPoolHashMemPoolCreateHashTable  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolCreateHashTable
	#define EXT_MemPoolCreateHashTable
	#define GET_MemPoolCreateHashTable(fl)  CAL_CMGETAPI( "MemPoolCreateHashTable" ) 
	#define CAL_MemPoolCreateHashTable pICmpMemPoolHash->IMemPoolCreateHashTable
	#define CHK_MemPoolCreateHashTable (pICmpMemPoolHash != NULL)
	#define EXP_MemPoolCreateHashTable  CAL_CMEXPAPI( "MemPoolCreateHashTable" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolCreateHashTable  PFMEMPOOLCREATEHASHTABLE pfMemPoolCreateHashTable;
	#define EXT_MemPoolCreateHashTable  extern PFMEMPOOLCREATEHASHTABLE pfMemPoolCreateHashTable;
	#define GET_MemPoolCreateHashTable(fl)  s_pfCMGetAPI2( "MemPoolCreateHashTable", (RTS_VOID_FCTPTR *)&pfMemPoolCreateHashTable, (fl), 0, 0)
	#define CAL_MemPoolCreateHashTable  pfMemPoolCreateHashTable
	#define CHK_MemPoolCreateHashTable  (pfMemPoolCreateHashTable != NULL)
	#define EXP_MemPoolCreateHashTable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolCreateHashTable", (RTS_UINTPTR)MemPoolCreateHashTable, 0, 0) 
#endif




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
RTS_HANDLE CDECL MemPoolCreateHashTable2(RTS_HANDLE hMemPool, RTS_SIZE sNumHashEntries, RTS_UI8 *pHashTableBuffer, char *pszComponentName, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFMEMPOOLCREATEHASHTABLE2) (RTS_HANDLE hMemPool, RTS_SIZE sNumHashEntries, RTS_UI8 *pHashTableBuffer, char *pszComponentName, RTS_RESULT *pResult);
#if defined(CMPMEMPOOLHASH_NOTIMPLEMENTED) || defined(MEMPOOLCREATEHASHTABLE2_NOTIMPLEMENTED)
	#define USE_MemPoolCreateHashTable2
	#define EXT_MemPoolCreateHashTable2
	#define GET_MemPoolCreateHashTable2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolCreateHashTable2(p0,p1,p2,p3,p4)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_MemPoolCreateHashTable2  FALSE
	#define EXP_MemPoolCreateHashTable2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolCreateHashTable2
	#define EXT_MemPoolCreateHashTable2
	#define GET_MemPoolCreateHashTable2(fl)  CAL_CMGETAPI( "MemPoolCreateHashTable2" ) 
	#define CAL_MemPoolCreateHashTable2  MemPoolCreateHashTable2
	#define CHK_MemPoolCreateHashTable2  TRUE
	#define EXP_MemPoolCreateHashTable2  CAL_CMEXPAPI( "MemPoolCreateHashTable2" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOLHASH_EXTERNAL)
	#define USE_MemPoolCreateHashTable2
	#define EXT_MemPoolCreateHashTable2
	#define GET_MemPoolCreateHashTable2(fl)  CAL_CMGETAPI( "MemPoolCreateHashTable2" ) 
	#define CAL_MemPoolCreateHashTable2  MemPoolCreateHashTable2
	#define CHK_MemPoolCreateHashTable2  TRUE
	#define EXP_MemPoolCreateHashTable2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolCreateHashTable2", (RTS_UINTPTR)MemPoolCreateHashTable2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolHashMemPoolCreateHashTable2
	#define EXT_CmpMemPoolHashMemPoolCreateHashTable2
	#define GET_CmpMemPoolHashMemPoolCreateHashTable2  ERR_OK
	#define CAL_CmpMemPoolHashMemPoolCreateHashTable2 pICmpMemPoolHash->IMemPoolCreateHashTable2
	#define CHK_CmpMemPoolHashMemPoolCreateHashTable2 (pICmpMemPoolHash != NULL)
	#define EXP_CmpMemPoolHashMemPoolCreateHashTable2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolCreateHashTable2
	#define EXT_MemPoolCreateHashTable2
	#define GET_MemPoolCreateHashTable2(fl)  CAL_CMGETAPI( "MemPoolCreateHashTable2" ) 
	#define CAL_MemPoolCreateHashTable2 pICmpMemPoolHash->IMemPoolCreateHashTable2
	#define CHK_MemPoolCreateHashTable2 (pICmpMemPoolHash != NULL)
	#define EXP_MemPoolCreateHashTable2  CAL_CMEXPAPI( "MemPoolCreateHashTable2" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolCreateHashTable2  PFMEMPOOLCREATEHASHTABLE2 pfMemPoolCreateHashTable2;
	#define EXT_MemPoolCreateHashTable2  extern PFMEMPOOLCREATEHASHTABLE2 pfMemPoolCreateHashTable2;
	#define GET_MemPoolCreateHashTable2(fl)  s_pfCMGetAPI2( "MemPoolCreateHashTable2", (RTS_VOID_FCTPTR *)&pfMemPoolCreateHashTable2, (fl), 0, 0)
	#define CAL_MemPoolCreateHashTable2  pfMemPoolCreateHashTable2
	#define CHK_MemPoolCreateHashTable2  (pfMemPoolCreateHashTable2 != NULL)
	#define EXP_MemPoolCreateHashTable2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolCreateHashTable2", (RTS_UINTPTR)MemPoolCreateHashTable2, 0, 0) 
#endif




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
RTS_RESULT CDECL MemPoolDeleteHashTable(RTS_HANDLE hMemPoolHashTable);
typedef RTS_RESULT (CDECL * PFMEMPOOLDELETEHASHTABLE) (RTS_HANDLE hMemPoolHashTable);
#if defined(CMPMEMPOOLHASH_NOTIMPLEMENTED) || defined(MEMPOOLDELETEHASHTABLE_NOTIMPLEMENTED)
	#define USE_MemPoolDeleteHashTable
	#define EXT_MemPoolDeleteHashTable
	#define GET_MemPoolDeleteHashTable(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolDeleteHashTable(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolDeleteHashTable  FALSE
	#define EXP_MemPoolDeleteHashTable  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolDeleteHashTable
	#define EXT_MemPoolDeleteHashTable
	#define GET_MemPoolDeleteHashTable(fl)  CAL_CMGETAPI( "MemPoolDeleteHashTable" ) 
	#define CAL_MemPoolDeleteHashTable  MemPoolDeleteHashTable
	#define CHK_MemPoolDeleteHashTable  TRUE
	#define EXP_MemPoolDeleteHashTable  CAL_CMEXPAPI( "MemPoolDeleteHashTable" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOLHASH_EXTERNAL)
	#define USE_MemPoolDeleteHashTable
	#define EXT_MemPoolDeleteHashTable
	#define GET_MemPoolDeleteHashTable(fl)  CAL_CMGETAPI( "MemPoolDeleteHashTable" ) 
	#define CAL_MemPoolDeleteHashTable  MemPoolDeleteHashTable
	#define CHK_MemPoolDeleteHashTable  TRUE
	#define EXP_MemPoolDeleteHashTable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolDeleteHashTable", (RTS_UINTPTR)MemPoolDeleteHashTable, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolHashMemPoolDeleteHashTable
	#define EXT_CmpMemPoolHashMemPoolDeleteHashTable
	#define GET_CmpMemPoolHashMemPoolDeleteHashTable  ERR_OK
	#define CAL_CmpMemPoolHashMemPoolDeleteHashTable pICmpMemPoolHash->IMemPoolDeleteHashTable
	#define CHK_CmpMemPoolHashMemPoolDeleteHashTable (pICmpMemPoolHash != NULL)
	#define EXP_CmpMemPoolHashMemPoolDeleteHashTable  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolDeleteHashTable
	#define EXT_MemPoolDeleteHashTable
	#define GET_MemPoolDeleteHashTable(fl)  CAL_CMGETAPI( "MemPoolDeleteHashTable" ) 
	#define CAL_MemPoolDeleteHashTable pICmpMemPoolHash->IMemPoolDeleteHashTable
	#define CHK_MemPoolDeleteHashTable (pICmpMemPoolHash != NULL)
	#define EXP_MemPoolDeleteHashTable  CAL_CMEXPAPI( "MemPoolDeleteHashTable" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolDeleteHashTable  PFMEMPOOLDELETEHASHTABLE pfMemPoolDeleteHashTable;
	#define EXT_MemPoolDeleteHashTable  extern PFMEMPOOLDELETEHASHTABLE pfMemPoolDeleteHashTable;
	#define GET_MemPoolDeleteHashTable(fl)  s_pfCMGetAPI2( "MemPoolDeleteHashTable", (RTS_VOID_FCTPTR *)&pfMemPoolDeleteHashTable, (fl), 0, 0)
	#define CAL_MemPoolDeleteHashTable  pfMemPoolDeleteHashTable
	#define CHK_MemPoolDeleteHashTable  (pfMemPoolDeleteHashTable != NULL)
	#define EXP_MemPoolDeleteHashTable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolDeleteHashTable", (RTS_UINTPTR)MemPoolDeleteHashTable, 0, 0) 
#endif




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
RTS_HANDLE CDECL MemPoolGetBlockHashed(RTS_HANDLE hMemPoolHashTable, RTS_UI32 nNumOfNewElements, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFMEMPOOLGETBLOCKHASHED) (RTS_HANDLE hMemPoolHashTable, RTS_UI32 nNumOfNewElements, RTS_RESULT *pResult);
#if defined(CMPMEMPOOLHASH_NOTIMPLEMENTED) || defined(MEMPOOLGETBLOCKHASHED_NOTIMPLEMENTED)
	#define USE_MemPoolGetBlockHashed
	#define EXT_MemPoolGetBlockHashed
	#define GET_MemPoolGetBlockHashed(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolGetBlockHashed(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_MemPoolGetBlockHashed  FALSE
	#define EXP_MemPoolGetBlockHashed  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolGetBlockHashed
	#define EXT_MemPoolGetBlockHashed
	#define GET_MemPoolGetBlockHashed(fl)  CAL_CMGETAPI( "MemPoolGetBlockHashed" ) 
	#define CAL_MemPoolGetBlockHashed  MemPoolGetBlockHashed
	#define CHK_MemPoolGetBlockHashed  TRUE
	#define EXP_MemPoolGetBlockHashed  CAL_CMEXPAPI( "MemPoolGetBlockHashed" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOLHASH_EXTERNAL)
	#define USE_MemPoolGetBlockHashed
	#define EXT_MemPoolGetBlockHashed
	#define GET_MemPoolGetBlockHashed(fl)  CAL_CMGETAPI( "MemPoolGetBlockHashed" ) 
	#define CAL_MemPoolGetBlockHashed  MemPoolGetBlockHashed
	#define CHK_MemPoolGetBlockHashed  TRUE
	#define EXP_MemPoolGetBlockHashed  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolGetBlockHashed", (RTS_UINTPTR)MemPoolGetBlockHashed, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolHashMemPoolGetBlockHashed
	#define EXT_CmpMemPoolHashMemPoolGetBlockHashed
	#define GET_CmpMemPoolHashMemPoolGetBlockHashed  ERR_OK
	#define CAL_CmpMemPoolHashMemPoolGetBlockHashed pICmpMemPoolHash->IMemPoolGetBlockHashed
	#define CHK_CmpMemPoolHashMemPoolGetBlockHashed (pICmpMemPoolHash != NULL)
	#define EXP_CmpMemPoolHashMemPoolGetBlockHashed  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolGetBlockHashed
	#define EXT_MemPoolGetBlockHashed
	#define GET_MemPoolGetBlockHashed(fl)  CAL_CMGETAPI( "MemPoolGetBlockHashed" ) 
	#define CAL_MemPoolGetBlockHashed pICmpMemPoolHash->IMemPoolGetBlockHashed
	#define CHK_MemPoolGetBlockHashed (pICmpMemPoolHash != NULL)
	#define EXP_MemPoolGetBlockHashed  CAL_CMEXPAPI( "MemPoolGetBlockHashed" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolGetBlockHashed  PFMEMPOOLGETBLOCKHASHED pfMemPoolGetBlockHashed;
	#define EXT_MemPoolGetBlockHashed  extern PFMEMPOOLGETBLOCKHASHED pfMemPoolGetBlockHashed;
	#define GET_MemPoolGetBlockHashed(fl)  s_pfCMGetAPI2( "MemPoolGetBlockHashed", (RTS_VOID_FCTPTR *)&pfMemPoolGetBlockHashed, (fl), 0, 0)
	#define CAL_MemPoolGetBlockHashed  pfMemPoolGetBlockHashed
	#define CHK_MemPoolGetBlockHashed  (pfMemPoolGetBlockHashed != NULL)
	#define EXP_MemPoolGetBlockHashed  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolGetBlockHashed", (RTS_UINTPTR)MemPoolGetBlockHashed, 0, 0) 
#endif




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
RTS_HANDLE CDECL MemPoolGetBlockHashed2(RTS_HANDLE hMemPoolHashTable, RTS_UI32 nNumOfNewElements, RTS_UI32 offsetHashEntry, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFMEMPOOLGETBLOCKHASHED2) (RTS_HANDLE hMemPoolHashTable, RTS_UI32 nNumOfNewElements, RTS_UI32 offsetHashEntry, RTS_RESULT *pResult);
#if defined(CMPMEMPOOLHASH_NOTIMPLEMENTED) || defined(MEMPOOLGETBLOCKHASHED2_NOTIMPLEMENTED)
	#define USE_MemPoolGetBlockHashed2
	#define EXT_MemPoolGetBlockHashed2
	#define GET_MemPoolGetBlockHashed2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolGetBlockHashed2(p0,p1,p2,p3)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_MemPoolGetBlockHashed2  FALSE
	#define EXP_MemPoolGetBlockHashed2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolGetBlockHashed2
	#define EXT_MemPoolGetBlockHashed2
	#define GET_MemPoolGetBlockHashed2(fl)  CAL_CMGETAPI( "MemPoolGetBlockHashed2" ) 
	#define CAL_MemPoolGetBlockHashed2  MemPoolGetBlockHashed2
	#define CHK_MemPoolGetBlockHashed2  TRUE
	#define EXP_MemPoolGetBlockHashed2  CAL_CMEXPAPI( "MemPoolGetBlockHashed2" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOLHASH_EXTERNAL)
	#define USE_MemPoolGetBlockHashed2
	#define EXT_MemPoolGetBlockHashed2
	#define GET_MemPoolGetBlockHashed2(fl)  CAL_CMGETAPI( "MemPoolGetBlockHashed2" ) 
	#define CAL_MemPoolGetBlockHashed2  MemPoolGetBlockHashed2
	#define CHK_MemPoolGetBlockHashed2  TRUE
	#define EXP_MemPoolGetBlockHashed2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolGetBlockHashed2", (RTS_UINTPTR)MemPoolGetBlockHashed2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolHashMemPoolGetBlockHashed2
	#define EXT_CmpMemPoolHashMemPoolGetBlockHashed2
	#define GET_CmpMemPoolHashMemPoolGetBlockHashed2  ERR_OK
	#define CAL_CmpMemPoolHashMemPoolGetBlockHashed2 pICmpMemPoolHash->IMemPoolGetBlockHashed2
	#define CHK_CmpMemPoolHashMemPoolGetBlockHashed2 (pICmpMemPoolHash != NULL)
	#define EXP_CmpMemPoolHashMemPoolGetBlockHashed2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolGetBlockHashed2
	#define EXT_MemPoolGetBlockHashed2
	#define GET_MemPoolGetBlockHashed2(fl)  CAL_CMGETAPI( "MemPoolGetBlockHashed2" ) 
	#define CAL_MemPoolGetBlockHashed2 pICmpMemPoolHash->IMemPoolGetBlockHashed2
	#define CHK_MemPoolGetBlockHashed2 (pICmpMemPoolHash != NULL)
	#define EXP_MemPoolGetBlockHashed2  CAL_CMEXPAPI( "MemPoolGetBlockHashed2" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolGetBlockHashed2  PFMEMPOOLGETBLOCKHASHED2 pfMemPoolGetBlockHashed2;
	#define EXT_MemPoolGetBlockHashed2  extern PFMEMPOOLGETBLOCKHASHED2 pfMemPoolGetBlockHashed2;
	#define GET_MemPoolGetBlockHashed2(fl)  s_pfCMGetAPI2( "MemPoolGetBlockHashed2", (RTS_VOID_FCTPTR *)&pfMemPoolGetBlockHashed2, (fl), 0, 0)
	#define CAL_MemPoolGetBlockHashed2  pfMemPoolGetBlockHashed2
	#define CHK_MemPoolGetBlockHashed2  (pfMemPoolGetBlockHashed2 != NULL)
	#define EXP_MemPoolGetBlockHashed2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolGetBlockHashed2", (RTS_UINTPTR)MemPoolGetBlockHashed2, 0, 0) 
#endif




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
RTS_RESULT CDECL MemPoolRemoveBlockHashed(RTS_HANDLE hMemPoolHashTable, RTS_HANDLE hHash);
typedef RTS_RESULT (CDECL * PFMEMPOOLREMOVEBLOCKHASHED) (RTS_HANDLE hMemPoolHashTable, RTS_HANDLE hHash);
#if defined(CMPMEMPOOLHASH_NOTIMPLEMENTED) || defined(MEMPOOLREMOVEBLOCKHASHED_NOTIMPLEMENTED)
	#define USE_MemPoolRemoveBlockHashed
	#define EXT_MemPoolRemoveBlockHashed
	#define GET_MemPoolRemoveBlockHashed(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolRemoveBlockHashed(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolRemoveBlockHashed  FALSE
	#define EXP_MemPoolRemoveBlockHashed  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolRemoveBlockHashed
	#define EXT_MemPoolRemoveBlockHashed
	#define GET_MemPoolRemoveBlockHashed(fl)  CAL_CMGETAPI( "MemPoolRemoveBlockHashed" ) 
	#define CAL_MemPoolRemoveBlockHashed  MemPoolRemoveBlockHashed
	#define CHK_MemPoolRemoveBlockHashed  TRUE
	#define EXP_MemPoolRemoveBlockHashed  CAL_CMEXPAPI( "MemPoolRemoveBlockHashed" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOLHASH_EXTERNAL)
	#define USE_MemPoolRemoveBlockHashed
	#define EXT_MemPoolRemoveBlockHashed
	#define GET_MemPoolRemoveBlockHashed(fl)  CAL_CMGETAPI( "MemPoolRemoveBlockHashed" ) 
	#define CAL_MemPoolRemoveBlockHashed  MemPoolRemoveBlockHashed
	#define CHK_MemPoolRemoveBlockHashed  TRUE
	#define EXP_MemPoolRemoveBlockHashed  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolRemoveBlockHashed", (RTS_UINTPTR)MemPoolRemoveBlockHashed, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolHashMemPoolRemoveBlockHashed
	#define EXT_CmpMemPoolHashMemPoolRemoveBlockHashed
	#define GET_CmpMemPoolHashMemPoolRemoveBlockHashed  ERR_OK
	#define CAL_CmpMemPoolHashMemPoolRemoveBlockHashed pICmpMemPoolHash->IMemPoolRemoveBlockHashed
	#define CHK_CmpMemPoolHashMemPoolRemoveBlockHashed (pICmpMemPoolHash != NULL)
	#define EXP_CmpMemPoolHashMemPoolRemoveBlockHashed  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolRemoveBlockHashed
	#define EXT_MemPoolRemoveBlockHashed
	#define GET_MemPoolRemoveBlockHashed(fl)  CAL_CMGETAPI( "MemPoolRemoveBlockHashed" ) 
	#define CAL_MemPoolRemoveBlockHashed pICmpMemPoolHash->IMemPoolRemoveBlockHashed
	#define CHK_MemPoolRemoveBlockHashed (pICmpMemPoolHash != NULL)
	#define EXP_MemPoolRemoveBlockHashed  CAL_CMEXPAPI( "MemPoolRemoveBlockHashed" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolRemoveBlockHashed  PFMEMPOOLREMOVEBLOCKHASHED pfMemPoolRemoveBlockHashed;
	#define EXT_MemPoolRemoveBlockHashed  extern PFMEMPOOLREMOVEBLOCKHASHED pfMemPoolRemoveBlockHashed;
	#define GET_MemPoolRemoveBlockHashed(fl)  s_pfCMGetAPI2( "MemPoolRemoveBlockHashed", (RTS_VOID_FCTPTR *)&pfMemPoolRemoveBlockHashed, (fl), 0, 0)
	#define CAL_MemPoolRemoveBlockHashed  pfMemPoolRemoveBlockHashed
	#define CHK_MemPoolRemoveBlockHashed  (pfMemPoolRemoveBlockHashed != NULL)
	#define EXP_MemPoolRemoveBlockHashed  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolRemoveBlockHashed", (RTS_UINTPTR)MemPoolRemoveBlockHashed, 0, 0) 
#endif




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
 void* CDECL MemPoolGetBlockByHash(RTS_HANDLE hMemPoolHashTable, RTS_HANDLE hHash, RTS_RESULT *pResult);
typedef void* (CDECL * PFMEMPOOLGETBLOCKBYHASH) (RTS_HANDLE hMemPoolHashTable, RTS_HANDLE hHash, RTS_RESULT *pResult);
#if defined(CMPMEMPOOLHASH_NOTIMPLEMENTED) || defined(MEMPOOLGETBLOCKBYHASH_NOTIMPLEMENTED)
	#define USE_MemPoolGetBlockByHash
	#define EXT_MemPoolGetBlockByHash
	#define GET_MemPoolGetBlockByHash(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolGetBlockByHash(p0,p1,p2)  (void*)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolGetBlockByHash  FALSE
	#define EXP_MemPoolGetBlockByHash  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolGetBlockByHash
	#define EXT_MemPoolGetBlockByHash
	#define GET_MemPoolGetBlockByHash(fl)  CAL_CMGETAPI( "MemPoolGetBlockByHash" ) 
	#define CAL_MemPoolGetBlockByHash  MemPoolGetBlockByHash
	#define CHK_MemPoolGetBlockByHash  TRUE
	#define EXP_MemPoolGetBlockByHash  CAL_CMEXPAPI( "MemPoolGetBlockByHash" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOLHASH_EXTERNAL)
	#define USE_MemPoolGetBlockByHash
	#define EXT_MemPoolGetBlockByHash
	#define GET_MemPoolGetBlockByHash(fl)  CAL_CMGETAPI( "MemPoolGetBlockByHash" ) 
	#define CAL_MemPoolGetBlockByHash  MemPoolGetBlockByHash
	#define CHK_MemPoolGetBlockByHash  TRUE
	#define EXP_MemPoolGetBlockByHash  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolGetBlockByHash", (RTS_UINTPTR)MemPoolGetBlockByHash, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolHashMemPoolGetBlockByHash
	#define EXT_CmpMemPoolHashMemPoolGetBlockByHash
	#define GET_CmpMemPoolHashMemPoolGetBlockByHash  ERR_OK
	#define CAL_CmpMemPoolHashMemPoolGetBlockByHash pICmpMemPoolHash->IMemPoolGetBlockByHash
	#define CHK_CmpMemPoolHashMemPoolGetBlockByHash (pICmpMemPoolHash != NULL)
	#define EXP_CmpMemPoolHashMemPoolGetBlockByHash  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolGetBlockByHash
	#define EXT_MemPoolGetBlockByHash
	#define GET_MemPoolGetBlockByHash(fl)  CAL_CMGETAPI( "MemPoolGetBlockByHash" ) 
	#define CAL_MemPoolGetBlockByHash pICmpMemPoolHash->IMemPoolGetBlockByHash
	#define CHK_MemPoolGetBlockByHash (pICmpMemPoolHash != NULL)
	#define EXP_MemPoolGetBlockByHash  CAL_CMEXPAPI( "MemPoolGetBlockByHash" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolGetBlockByHash  PFMEMPOOLGETBLOCKBYHASH pfMemPoolGetBlockByHash;
	#define EXT_MemPoolGetBlockByHash  extern PFMEMPOOLGETBLOCKBYHASH pfMemPoolGetBlockByHash;
	#define GET_MemPoolGetBlockByHash(fl)  s_pfCMGetAPI2( "MemPoolGetBlockByHash", (RTS_VOID_FCTPTR *)&pfMemPoolGetBlockByHash, (fl), 0, 0)
	#define CAL_MemPoolGetBlockByHash  pfMemPoolGetBlockByHash
	#define CHK_MemPoolGetBlockByHash  (pfMemPoolGetBlockByHash != NULL)
	#define EXP_MemPoolGetBlockByHash  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolGetBlockByHash", (RTS_UINTPTR)MemPoolGetBlockByHash, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFMEMPOOLCREATEHASHTABLE IMemPoolCreateHashTable;
 	PFMEMPOOLCREATEHASHTABLE2 IMemPoolCreateHashTable2;
 	PFMEMPOOLDELETEHASHTABLE IMemPoolDeleteHashTable;
 	PFMEMPOOLGETBLOCKHASHED IMemPoolGetBlockHashed;
 	PFMEMPOOLGETBLOCKHASHED2 IMemPoolGetBlockHashed2;
 	PFMEMPOOLREMOVEBLOCKHASHED IMemPoolRemoveBlockHashed;
 	PFMEMPOOLGETBLOCKBYHASH IMemPoolGetBlockByHash;
 } ICmpMemPoolHash_C;

#ifdef CPLUSPLUS
class ICmpMemPoolHash : public IBase
{
	public:
		virtual RTS_HANDLE CDECL IMemPoolCreateHashTable(RTS_HANDLE hMemPool, RTS_SIZE sNumHashEntries, char *pszComponentName, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IMemPoolCreateHashTable2(RTS_HANDLE hMemPool, RTS_SIZE sNumHashEntries, RTS_UI8 *pHashTableBuffer, char *pszComponentName, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IMemPoolDeleteHashTable(RTS_HANDLE hMemPoolHashTable) =0;
		virtual RTS_HANDLE CDECL IMemPoolGetBlockHashed(RTS_HANDLE hMemPoolHashTable, RTS_UI32 nNumOfNewElements, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IMemPoolGetBlockHashed2(RTS_HANDLE hMemPoolHashTable, RTS_UI32 nNumOfNewElements, RTS_UI32 offsetHashEntry, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IMemPoolRemoveBlockHashed(RTS_HANDLE hMemPoolHashTable, RTS_HANDLE hHash) =0;
		virtual void* CDECL IMemPoolGetBlockByHash(RTS_HANDLE hMemPoolHashTable, RTS_HANDLE hHash, RTS_RESULT *pResult) =0;
};
	#ifndef ITF_CmpMemPoolHash
		#define ITF_CmpMemPoolHash static ICmpMemPoolHash *pICmpMemPoolHash = NULL;
	#endif
	#define EXTITF_CmpMemPoolHash
#else	/*CPLUSPLUS*/
	typedef ICmpMemPoolHash_C		ICmpMemPoolHash;
	#ifndef ITF_CmpMemPoolHash
		#define ITF_CmpMemPoolHash
	#endif
	#define EXTITF_CmpMemPoolHash
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPMEMPOOLHASHITF_H_*/
