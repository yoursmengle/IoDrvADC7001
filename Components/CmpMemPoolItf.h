 /**
 * <interfacename>CmpMemPool</interfacename>
 * <description>
 *  <p>Interface of the memory pool manager to handle static and dynamic memory blocks</p>
 *
 *  <p>A MemPool has the following structure:</p>
 *  <pre>
 *. 
 *. -------------- Pool Control Block                -------------- Block Control Block
 *. |Blocksize   |  data size of single block        |nRefCount   |  Reference Counter
 *. |pBlocksInUse|  List of used blocks              |pBCB        |  Pointer to next BCB
 *. |pBCB        |  List of free blocks              |pPCB        |  Pointer to PCB
 *. |...         |                                   ------------
 *. -------------
 *.
 *.                      provided
 *.                      Memory Area
 *.                      .--------------------------.
 *.                      | PCB                      |
 *.   List of free Blocks|  Blocksize               |      List of used Blocks
 *.                      |  pBlocksInUse            |===========.
 *.         .=========== |  pBCB                    |           |
 *.         |            |......................... |           |
 *.         |            | BCB                      | &lt;=========
 *.         |            |                          | ---.
 *.         |            |......................... |    |
 *.         |            | DATA                     |    |
 *.         |            |                          |    |
 *.         |            |......................... |    |
 *.         |            | BCB                      | &lt;--'
 *.         |            |                          | ---.
 *.         |            |......................... |    |
 *.         |            | DATA                     |    |
 *.         |            |                          |    |
 *.         |            |......................... |    |
 *.         |            |                          | &lt;--'
 *.         |           ~~~                        ~~~
 *.         |
 *.         |           ~~~                        ~~~
 *.         '=========&gt;  |......................... |
 *.                      | BCB                      | ---.
 *.                      |                          |    |
 *.                      |......................... |    |
 *.                      | DATA                     |    |
 *.                      |                          |    |
 *.                      |......................... | &lt;--'
 *.                      | BCB                      | ---.
 *.                      |                          |    |
 *.                     ~~~                        ~~   ~~~
 *.
 *.                     ~~~                        ~~~
 *.                      |                          |
 *.                      |                          |
 *.                      .--------------------------.
 *.                      End of Memory Area
 *.
 *.
 * </pre>
 * 
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPMEMPOOLITF_H_
#define _CMPMEMPOOLITF_H_

#include "CmpStd.h"

 

 




/* Data types forward declarations */
typedef struct tagFBA_CHUNK FBA_CHUNK;
typedef struct tagRTS_FIXED_BLOCKS_POOL RTS_FIXED_BLOCKS_POOL;

#if !defined(MEMPOOL_8BYTE_ALIGNED) && defined(TRG_64BIT)
	#define MEMPOOL_8BYTE_ALIGNED
#endif

/**
 *	Returns the address of an instance of a structure given the type of the
 *	structure and the address of the field within the containing structure.
 */ 
#ifndef U_CONTAINING_RECORD
#	define U_CONTAINING_RECORD(address, type, field) ((type *)(void*)((char*)(void*)(address) - (RTS_SIZE)(/*lint -e413 */&((type *)0)->field)))
#endif

/**
 *  Block size should be not less than FBA_MIN_BLOCK,
 *  
 */
#ifdef MEMPOOL_8BYTE_ALIGNED 
#	define FBA_MIN_BLOCK 8
#else
#	define FBA_MIN_BLOCK ( (sizeof(RTS_SIZE) <= 2) ? 2 : sizeof(RTS_UINTPTR) )
#endif

#define ___FBA_ALIGN_SIZE___(sz) ((((sz) + (FBA_MIN_BLOCK - 1)) / FBA_MIN_BLOCK) * FBA_MIN_BLOCK)
#define FBA_ALIGN_SIZE(sz) ___FBA_ALIGN_SIZE___(sz)

#define FBA_ALIGN_MEM(p) (void*)((((RTS_UINTPTR)(p) + (FBA_MIN_BLOCK - 1)) / FBA_MIN_BLOCK) * FBA_MIN_BLOCK)

#define FBA_GET_STATIC_LEN(blk_num, blk_sz) ( (blk_num) * FBA_ALIGN_SIZE((blk_sz)) + sizeof(FBA_CHUNK) + FBA_MIN_BLOCK)


/* Init value to write over a deleted object */
#ifndef MEMPOOL_INIT_VALUE
#	define MEMPOOL_INIT_VALUE		0xAA
#endif

/**
 *  Memory chunk for managing allocations and de-allocations.
 *  
 *  Memory blocks are obtained from the area marked with the unallocated_block
 *  index (called 'right-hand area') until at least one block gets 
 *  returned by free(). Once it happens, the consecutive allocations are 
 *	performed from the 'left-hand area' containing returned blocks.
 *  
 *  Once the left-hand area is exhausted, allocations continue to be made
 *  from the right-hand area.
 */
struct tagFBA_CHUNK
{
	/* Memory blocks array starts here */
	RTS_UI8*	pData;

  /* Pointer to the next chunk (if memory space is extendable) */
  FBA_CHUNK*	pNext;

  /* Index of the first available block */
  RTS_SIZE		free_block;

  /* Index of the first unallocated block */
  RTS_SIZE		unallocated_block;
};


/**
 *  Allocator for small objects of a constant size.
 */
struct tagRTS_FIXED_BLOCKS_POOL
{
	/* address of the 1st chunk taken out of a static buffer */
	void*				pRootChunkStaticAddress;

	/* First chunk */
	FBA_CHUNK*	pRootChunk;

	/* Block size	*/
	RTS_SIZE	block_size;

	/* Maximum number of objects within one chunk */
	RTS_SIZE	max_blocks;

	/* Total memory size available for clients */
	/* if allocated_size == 0 */
	RTS_SIZE	total_size;

	/* Allocated memory size */
	RTS_SIZE	allocated_size;

	/* Pool state flags */
	RTS_SIZE	flags;
};

/* Pool was properly initialized */
#define FBA_FLAG_INITIALIZED	0x1

#define FixedBlocksPoolIsValid(pfmp) (NULL != (pfmp) && (0 != ((pfmp)->flags & FBA_FLAG_INITIALIZED)))



#ifdef RTS_MEMPOOL_VER2

/****************************************************************************/
/*	Pool of memory blocks of fixed size based on RTS_FIXED_BLOCKS_POOL		*/
/****************************************************************************/
typedef struct tagRTS_MEM_LIST_POOL RTS_MEM_LIST_POOL;
typedef struct tagRTS_MEM_LIST_POOL_BLOCK RTS_MEM_LIST_POOL_BLOCK;
typedef struct tagRTS_MEM_LIST_ELEMENT RTS_MEM_LIST_ELEMENT;

/**
 *  Single-linked list element.
 */
struct tagRTS_MEM_LIST_ELEMENT
{
	RTS_MEM_LIST_ELEMENT* next;
};

/**
 *  Memory block descriptor.
 */
struct tagRTS_MEM_LIST_POOL_BLOCK
{
	/* link to the containing list pool */
	RTS_MEM_LIST_POOL*		pPool;

	/* list node */
	RTS_MEM_LIST_ELEMENT	node;
};

/**
 *  Memory pool with an assosiated linked list that can be used as
 *  a container for objects allocated out of this or some other pool.
 */
struct tagRTS_MEM_LIST_POOL
{
	/* First element of the list */
	RTS_MEM_LIST_ELEMENT*				head;

	/* Last element of the list */
	RTS_MEM_LIST_ELEMENT*				tail;

	/* Blocks allocator */
	RTS_FIXED_BLOCKS_POOL				blocks_pool;

	/* Pool lock */
	union
	{
		RTS_HANDLE	hSem;
		RTS_UI32		mask;
	} lock;
};

/* Fix for the components which use RTS_PCB directly */
typedef RTS_MEM_LIST_POOL RTS_PCB;

typedef struct
{
	RTS_MEM_LIST_POOL_BLOCK* pHead;
	RTS_MEM_LIST_POOL_BLOCK* pNext;
} MemIterator;

static inline int MemPoolIteratorGetFirst(RTS_HANDLE hPool, MemIterator *pIt)
{
	RTS_MEM_LIST_POOL* pPool = RTS_INVALID_HANDLE != hPool ? (RTS_MEM_LIST_POOL*)hPool : NULL;
	
	pIt->pNext = NULL;
	pIt->pHead = NULL != pPool && pPool->head ? U_CONTAINING_RECORD(pPool->head, RTS_MEM_LIST_POOL_BLOCK, node) : NULL;	

	return (NULL != pIt->pHead);
}
	
static inline int MemPoolIteratorGetNext(MemIterator *pIt)
{
	RTS_MEM_LIST_ELEMENT* pElement = (NULL != pIt->pNext) ? pIt->pNext->node.next : &pIt->pHead->node;

	pIt->pNext = NULL != pElement ? U_CONTAINING_RECORD(pElement, RTS_MEM_LIST_POOL_BLOCK, node) : NULL;

	return NULL != pIt->pNext;
}
	
static inline void* MemPoolIteratorGetNextFromData(void *pData)
{
	RTS_MEM_LIST_ELEMENT* pNextElement = (NULL == pData) ? NULL : ((RTS_MEM_LIST_POOL_BLOCK*) ((RTS_UI8*)pData - sizeof(RTS_MEM_LIST_POOL_BLOCK)))->node.next;

	return (NULL != pNextElement) ? (U_CONTAINING_RECORD(pNextElement, RTS_MEM_LIST_POOL_BLOCK, node) + 1) : NULL;
}


#define MEMPOOL_IS_NOT_EMPTY(hPool) (NULL != ((RTS_MEM_LIST_POOL*)(hPool))->head)

#define MEMPOOL_IS_EMPTY(hPool) (NULL == ((RTS_MEM_LIST_POOL*)(hPool))->head)

#define MEMPOOL_HAS_FREE_BLOCKS(hPool) (((RTS_MEM_LIST_POOL*)(hPool))->blocks_pool.allocated_size < ((RTS_MEM_LIST_POOL*)(hPool))->blocks_pool.total_size)

#define MEM_GET_FIRST(ppool, pit) MemPoolIteratorGetFirst((ppool), (pit))

#define MEM_GET_NEXT(pit) MemPoolIteratorGetNext((pit))

/* pit is always a non-null value! */
#define MEM_GET_DATA(pit) ((NULL != (pit)->pNext) ? (pit)->pNext + 1 : NULL)

#define MEM_GET_NEXT_FROM_DATA(pdata) MemPoolIteratorGetNextFromData((pdata))

#define MEM_GET_STATIC_LEN_(Num, Size) ( (Num) * sizeof(RTS_MEM_LIST_POOL_BLOCK) + sizeof(RTS_MEM_LIST_POOL) + FBA_GET_STATIC_LEN((Num), (Size)))
#define MEM_GET_STATIC_LEN(Num, Struct) ( MEM_GET_STATIC_LEN_((Num), sizeof(Struct)) )

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif

#else


/**
 * <category>Compiler switch</category>
 * <description>
 *	Compiler switches configure the behaviour of the mempool.
 * </description>
 * <element name="MEMPOOL_DISABLE_HEAP_MEMORY">Switch to disable dynamic memory</element>
 */

#ifdef MEMPOOL_8BYTE_ALIGNED
	#define MEMPOOL_ALIGN_MODULO			8
#else
	#define MEMPOOL_ALIGN_MODULO			sizeof(void*)
#endif

#define MEM_GET_STATIC_LEN(Num, Struct)		(sizeof(RTS_PCB) + 2 * MEMPOOL_ALIGN_MODULO + (Num) * ALIGN_SIZE(sizeof(Struct), MEMPOOL_ALIGN_MODULO) + (Num) * sizeof(RTS_BCB))
#define MEM_GET_STATIC_LEN_(Num, Size)		(sizeof(RTS_PCB) + 2 * MEMPOOL_ALIGN_MODULO + (Num) * ALIGN_SIZE(Size, MEMPOOL_ALIGN_MODULO) + (Num) * sizeof(RTS_BCB))


/*
 * <SIL2/>
 * <description>Block Control Block</description>
 */
typedef struct RTS_BCBtag
{
	RTS_I32 nRefCount;			/* Reference counter for the block */
#if defined(MEMPOOL_8BYTE_ALIGNED)
	RTS_UI32 alignment;
#endif
	struct RTS_BCBtag *pBCB;	/* Pointer to next free or used block control block */
	struct RTS_PCBtag *pPCB;	/* Pointer to pool control block */
} RTS_BCB;

/*
 * <SIL2/>
 * <description>Pool Extension Block</description>
 */
typedef struct RTS_PEBtag
{
	RTS_I32 bDynamic;
#if defined(MEMPOOL_8BYTE_ALIGNED)
	RTS_UI32 alignment;
#endif
	struct RTS_PEBtag *pPEB;
} RTS_PEB;

/*
 * <SIL2/>
 * <description>Pool Control Block</description>
 */
typedef struct RTS_PCBtag
{
	RTS_SIZE ulBlockSize;
#if defined(MEMPOOL_8BYTE_ALIGNED)
	RTS_SIZE alignment;
#endif

	union
	{
		RTS_HANDLE	hSem;
		RTS_UINTPTR	mask;
	}	lock;

	struct RTS_PEBtag *pPEB; /* Pointer to next extension block */
	struct RTS_BCBtag *pBCB; /* Pointer to free block list */
	struct RTS_BCBtag *pBlocksInUse; /* Pointer to first block in use */
} RTS_PCB;

/* 
 * <SIL2/>
 * <description>Iterator</description>
*/

typedef struct
{
	RTS_BCB *pHead;
	RTS_BCB *pNext;
} MemIterator;

#define MEMPOOL_IS_NOT_EMPTY(pPool)		((((RTS_PCB *)pPool)->pBlocksInUse) != NULL)
#define MEMPOOL_IS_EMPTY(pPool)			((((RTS_PCB *)pPool)->pBlocksInUse) == NULL)
#define MEMPOOL_HAS_FREE_BLOCKS(pPool)	(((RTS_PCB *)pPool)->pPEB) != NULL || ((RTS_PCB *)pPool)->pBCB) != NULL)

#ifdef MEMPOOL_FUNCTIONS
	static int MEM_GET_FIRST(RTS_HANDLE hPool, MemIterator *pIt)
	{
		RTS_PCB *pPool = (RTS_PCB *)hPool;
		
		pIt->pNext = NULL;
		pIt->pHead = NULL;

		if (hPool != RTS_INVALID_HANDLE && pPool->pBlocksInUse != NULL)
		{
			pIt->pHead = pPool->pBlocksInUse;	
			return 1;
		}
		return 0;
	}
	static int MEM_GET_NEXT(MemIterator *pIt)
	{
		pIt->pNext = (NULL != pIt->pNext) ? pIt->pNext->pBCB : pIt->pHead;

		return pIt->pNext != NULL;
	}
	static void *MEM_GET_DATA(MemIterator *pIt)
	{
		return (pIt->pNext + 1);
	}	
	static void *MEM_GET_NEXT_FROM_DATA(void *pData)
	{
		RTS_BCB *pBCB = ((RTS_BCB*)((unsigned char *)pData - sizeof(RTS_BCB)))->pBCB;
		
		return (NULL != pBCB) ? pBCB + 1 : NULL;
	}
#elif defined(RTS_COMPACT_MICRO)
int MemPoolIteratorGetFirst(RTS_HANDLE hPool, MemIterator *pIt);
int MemPoolIteratorGetNext(MemIterator *pIt);
void* MemPoolIteratorGetNextFromData(void *pData);

	#define MEM_GET_FIRST(ppool, pit)		MemPoolIteratorGetFirst((ppool), (pit))
	#define MEM_GET_NEXT(pit)				MemPoolIteratorGetNext((pit))
	#define MEM_GET_DATA(pit)				(((MemIterator*)(pit))->pNext + 1)
	#define MEM_GET_NEXT_FROM_DATA(pdata)	MemPoolIteratorGetNextFromData((pdata))
#else
	#define MEM_GET_FIRST(pPool,pIt)		/*lint -e{506,522} */((((MemIterator*)pIt)->pHead = ((RTS_PCB *)pPool)->pBlocksInUse) != NULL ? ((((MemIterator*)pIt)->pNext = NULL) != NULL ? 0 : 1) : ((((MemIterator*)pIt)->pNext = NULL) != NULL ? 1 : 0))
	#define MEM_GET_NEXT(pIt)				/*lint -e{506} */((((MemIterator*)pIt)->pNext == NULL) ? (((MemIterator*)pIt)->pNext = ((MemIterator*)pIt)->pHead) : (((MemIterator*)pIt)->pNext = ((MemIterator*)pIt)->pNext->pBCB))
	#define MEM_GET_DATA(pIt)				(((MemIterator*)pIt)->pNext + 1)
	#define MEM_GET_NEXT_FROM_DATA(pData)	/*lint -e{506} */(((RTS_BCB*)((unsigned char *)pData - sizeof(RTS_BCB)))->pBCB == NULL ? NULL : ((RTS_BCB*)((unsigned char *)pData - sizeof(RTS_BCB)))->pBCB + 1)
#endif

#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>
 *	Create a dynamic pool (consists of heap memory)
 * </description>
 * <param name="pszComponentName" type="IN">Component name</param>
 * <param name="ulBlockSize" type="IN">Size of each memory block in the pool</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the memory pool</result>
 */
RTS_HANDLE CDECL MemPoolCreateDynamic(char *pszComponentName, RTS_SIZE ulNumBlocks, RTS_SIZE ulBlockSize, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFMEMPOOLCREATEDYNAMIC) (char *pszComponentName, RTS_SIZE ulNumBlocks, RTS_SIZE ulBlockSize, RTS_RESULT *pResult);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLCREATEDYNAMIC_NOTIMPLEMENTED)
	#define USE_MemPoolCreateDynamic
	#define EXT_MemPoolCreateDynamic
	#define GET_MemPoolCreateDynamic(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolCreateDynamic(p0,p1,p2,p3)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_MemPoolCreateDynamic  FALSE
	#define EXP_MemPoolCreateDynamic  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolCreateDynamic
	#define EXT_MemPoolCreateDynamic
	#define GET_MemPoolCreateDynamic(fl)  CAL_CMGETAPI( "MemPoolCreateDynamic" ) 
	#define CAL_MemPoolCreateDynamic  MemPoolCreateDynamic
	#define CHK_MemPoolCreateDynamic  TRUE
	#define EXP_MemPoolCreateDynamic  CAL_CMEXPAPI( "MemPoolCreateDynamic" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolCreateDynamic
	#define EXT_MemPoolCreateDynamic
	#define GET_MemPoolCreateDynamic(fl)  CAL_CMGETAPI( "MemPoolCreateDynamic" ) 
	#define CAL_MemPoolCreateDynamic  MemPoolCreateDynamic
	#define CHK_MemPoolCreateDynamic  TRUE
	#define EXP_MemPoolCreateDynamic  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolCreateDynamic", (RTS_UINTPTR)MemPoolCreateDynamic, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolCreateDynamic
	#define EXT_CmpMemPoolMemPoolCreateDynamic
	#define GET_CmpMemPoolMemPoolCreateDynamic  ERR_OK
	#define CAL_CmpMemPoolMemPoolCreateDynamic pICmpMemPool->IMemPoolCreateDynamic
	#define CHK_CmpMemPoolMemPoolCreateDynamic (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolCreateDynamic  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolCreateDynamic
	#define EXT_MemPoolCreateDynamic
	#define GET_MemPoolCreateDynamic(fl)  CAL_CMGETAPI( "MemPoolCreateDynamic" ) 
	#define CAL_MemPoolCreateDynamic pICmpMemPool->IMemPoolCreateDynamic
	#define CHK_MemPoolCreateDynamic (pICmpMemPool != NULL)
	#define EXP_MemPoolCreateDynamic  CAL_CMEXPAPI( "MemPoolCreateDynamic" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolCreateDynamic  PFMEMPOOLCREATEDYNAMIC pfMemPoolCreateDynamic;
	#define EXT_MemPoolCreateDynamic  extern PFMEMPOOLCREATEDYNAMIC pfMemPoolCreateDynamic;
	#define GET_MemPoolCreateDynamic(fl)  s_pfCMGetAPI2( "MemPoolCreateDynamic", (RTS_VOID_FCTPTR *)&pfMemPoolCreateDynamic, (fl), 0, 0)
	#define CAL_MemPoolCreateDynamic  pfMemPoolCreateDynamic
	#define CHK_MemPoolCreateDynamic  (pfMemPoolCreateDynamic != NULL)
	#define EXP_MemPoolCreateDynamic  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolCreateDynamic", (RTS_UINTPTR)MemPoolCreateDynamic, 0, 0) 
#endif





/** 
 * <description>
 * <p>Create a memory pool from a static memory buffer.</p>
 * <p>The memory buffer don't has to be aligned in a specific way. Therefore,
 * not all of the memory in the buffer might be used. To get the appropriate
 * additional buffer, the caller is recommended to use the macro
 * MEM_GET_STATIC_LEN(Num, Struct) to get the size of the buffer</p>
 * <p>For example:</p>
 * <pre>
 * typedef struct
 * {
 *     ...
 * } myStruct_s;
 *
 * #define NUM_OF_STATIC_ELEMENTS 0x100
 *
 * RTS_UI8 s_byMyStaticPool[MEM_GET_STATIC_LEN(NUM_OF_STATIC_ELEMENTS, myStruct_s);
 * </pre>
 * </description>
 * <param name="ulBlockSize" type="IN" range="[BLOCKSIZE_ALIGNED1,BLOCKSIZE_ALIGNED2,BLOCKSIZE_ALIGNED4,BLOCKSIZE_ALIGNED8]">Size of each memory block in the pool, misaligned to 1, 2, 4 or 8 bytes</param>
 * <param name="ulMemSize" type="IN" range="[MEMSIZE_INVALID,MEMSIZE_ALIGNED1,MEMSIZE_ALIGNED2,MEMSIZE_ALIGNED4,MEMSIZE_ALIGNED8]">Complete size of the static memory, misaligned to 1, 2, 4 or 8 bytes</param>
 * <param name="pMemory" type="IN" range="[NULL,VALID_MEM]">Pointer to the static memory</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">MemPool created successfully</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">pMemory was NULL</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOMEMORY">ulMemSize was not large enough, to hold at leaset one block</errorcode>
 * <result>Handle to the memory pool</result>
 */
RTS_HANDLE CDECL MemPoolCreateStatic(RTS_SIZE ulBlockSize, RTS_SIZE ulMemSize, void* pMemory, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFMEMPOOLCREATESTATIC) (RTS_SIZE ulBlockSize, RTS_SIZE ulMemSize, void* pMemory, RTS_RESULT *pResult);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLCREATESTATIC_NOTIMPLEMENTED)
	#define USE_MemPoolCreateStatic
	#define EXT_MemPoolCreateStatic
	#define GET_MemPoolCreateStatic(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolCreateStatic(p0,p1,p2,p3)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_MemPoolCreateStatic  FALSE
	#define EXP_MemPoolCreateStatic  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolCreateStatic
	#define EXT_MemPoolCreateStatic
	#define GET_MemPoolCreateStatic(fl)  CAL_CMGETAPI( "MemPoolCreateStatic" ) 
	#define CAL_MemPoolCreateStatic  MemPoolCreateStatic
	#define CHK_MemPoolCreateStatic  TRUE
	#define EXP_MemPoolCreateStatic  CAL_CMEXPAPI( "MemPoolCreateStatic" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolCreateStatic
	#define EXT_MemPoolCreateStatic
	#define GET_MemPoolCreateStatic(fl)  CAL_CMGETAPI( "MemPoolCreateStatic" ) 
	#define CAL_MemPoolCreateStatic  MemPoolCreateStatic
	#define CHK_MemPoolCreateStatic  TRUE
	#define EXP_MemPoolCreateStatic  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolCreateStatic", (RTS_UINTPTR)MemPoolCreateStatic, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolCreateStatic
	#define EXT_CmpMemPoolMemPoolCreateStatic
	#define GET_CmpMemPoolMemPoolCreateStatic  ERR_OK
	#define CAL_CmpMemPoolMemPoolCreateStatic pICmpMemPool->IMemPoolCreateStatic
	#define CHK_CmpMemPoolMemPoolCreateStatic (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolCreateStatic  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolCreateStatic
	#define EXT_MemPoolCreateStatic
	#define GET_MemPoolCreateStatic(fl)  CAL_CMGETAPI( "MemPoolCreateStatic" ) 
	#define CAL_MemPoolCreateStatic pICmpMemPool->IMemPoolCreateStatic
	#define CHK_MemPoolCreateStatic (pICmpMemPool != NULL)
	#define EXP_MemPoolCreateStatic  CAL_CMEXPAPI( "MemPoolCreateStatic" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolCreateStatic  PFMEMPOOLCREATESTATIC pfMemPoolCreateStatic;
	#define EXT_MemPoolCreateStatic  extern PFMEMPOOLCREATESTATIC pfMemPoolCreateStatic;
	#define GET_MemPoolCreateStatic(fl)  s_pfCMGetAPI2( "MemPoolCreateStatic", (RTS_VOID_FCTPTR *)&pfMemPoolCreateStatic, (fl), 0, 0)
	#define CAL_MemPoolCreateStatic  pfMemPoolCreateStatic
	#define CHK_MemPoolCreateStatic  (pfMemPoolCreateStatic != NULL)
	#define EXP_MemPoolCreateStatic  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolCreateStatic", (RTS_UINTPTR)MemPoolCreateStatic, 0, 0) 
#endif




/**
 * <description>
 *	Extend dynamic an existing pool
 * </description>
 * <param name="hMemPool" type="IN">Handle to the pool</param>
 * <param name="pszComponentName" type="IN">Component name</param>
 * <param name="ulNumBlocks" type="IN">Number of blocks to extend</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL MemPoolExtendDynamic(RTS_HANDLE hMemPool, char *pszComponentName, RTS_SIZE ulNumBlocks);
typedef RTS_RESULT (CDECL * PFMEMPOOLEXTENDDYNAMIC) (RTS_HANDLE hMemPool, char *pszComponentName, RTS_SIZE ulNumBlocks);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLEXTENDDYNAMIC_NOTIMPLEMENTED)
	#define USE_MemPoolExtendDynamic
	#define EXT_MemPoolExtendDynamic
	#define GET_MemPoolExtendDynamic(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolExtendDynamic(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolExtendDynamic  FALSE
	#define EXP_MemPoolExtendDynamic  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolExtendDynamic
	#define EXT_MemPoolExtendDynamic
	#define GET_MemPoolExtendDynamic(fl)  CAL_CMGETAPI( "MemPoolExtendDynamic" ) 
	#define CAL_MemPoolExtendDynamic  MemPoolExtendDynamic
	#define CHK_MemPoolExtendDynamic  TRUE
	#define EXP_MemPoolExtendDynamic  CAL_CMEXPAPI( "MemPoolExtendDynamic" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolExtendDynamic
	#define EXT_MemPoolExtendDynamic
	#define GET_MemPoolExtendDynamic(fl)  CAL_CMGETAPI( "MemPoolExtendDynamic" ) 
	#define CAL_MemPoolExtendDynamic  MemPoolExtendDynamic
	#define CHK_MemPoolExtendDynamic  TRUE
	#define EXP_MemPoolExtendDynamic  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolExtendDynamic", (RTS_UINTPTR)MemPoolExtendDynamic, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolExtendDynamic
	#define EXT_CmpMemPoolMemPoolExtendDynamic
	#define GET_CmpMemPoolMemPoolExtendDynamic  ERR_OK
	#define CAL_CmpMemPoolMemPoolExtendDynamic pICmpMemPool->IMemPoolExtendDynamic
	#define CHK_CmpMemPoolMemPoolExtendDynamic (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolExtendDynamic  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolExtendDynamic
	#define EXT_MemPoolExtendDynamic
	#define GET_MemPoolExtendDynamic(fl)  CAL_CMGETAPI( "MemPoolExtendDynamic" ) 
	#define CAL_MemPoolExtendDynamic pICmpMemPool->IMemPoolExtendDynamic
	#define CHK_MemPoolExtendDynamic (pICmpMemPool != NULL)
	#define EXP_MemPoolExtendDynamic  CAL_CMEXPAPI( "MemPoolExtendDynamic" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolExtendDynamic  PFMEMPOOLEXTENDDYNAMIC pfMemPoolExtendDynamic;
	#define EXT_MemPoolExtendDynamic  extern PFMEMPOOLEXTENDDYNAMIC pfMemPoolExtendDynamic;
	#define GET_MemPoolExtendDynamic(fl)  s_pfCMGetAPI2( "MemPoolExtendDynamic", (RTS_VOID_FCTPTR *)&pfMemPoolExtendDynamic, (fl), 0, 0)
	#define CAL_MemPoolExtendDynamic  pfMemPoolExtendDynamic
	#define CHK_MemPoolExtendDynamic  (pfMemPoolExtendDynamic != NULL)
	#define EXP_MemPoolExtendDynamic  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolExtendDynamic", (RTS_UINTPTR)MemPoolExtendDynamic, 0, 0) 
#endif




/**
 * <description>
 *	Extend an existing pool with a static array
 * </description>
 * <param name="hMemPool" type="IN">Handle to the pool</param>
 * <param name="ulMemSize" type="IN">Complete size of the static memory</param>
 * <param name="pMemory" type="IN">Pointer to the static memory</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL MemPoolExtendStatic(RTS_HANDLE hMemPool, RTS_SIZE ulMemSize, void* pMemory);
typedef RTS_RESULT (CDECL * PFMEMPOOLEXTENDSTATIC) (RTS_HANDLE hMemPool, RTS_SIZE ulMemSize, void* pMemory);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLEXTENDSTATIC_NOTIMPLEMENTED)
	#define USE_MemPoolExtendStatic
	#define EXT_MemPoolExtendStatic
	#define GET_MemPoolExtendStatic(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolExtendStatic(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolExtendStatic  FALSE
	#define EXP_MemPoolExtendStatic  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolExtendStatic
	#define EXT_MemPoolExtendStatic
	#define GET_MemPoolExtendStatic(fl)  CAL_CMGETAPI( "MemPoolExtendStatic" ) 
	#define CAL_MemPoolExtendStatic  MemPoolExtendStatic
	#define CHK_MemPoolExtendStatic  TRUE
	#define EXP_MemPoolExtendStatic  CAL_CMEXPAPI( "MemPoolExtendStatic" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolExtendStatic
	#define EXT_MemPoolExtendStatic
	#define GET_MemPoolExtendStatic(fl)  CAL_CMGETAPI( "MemPoolExtendStatic" ) 
	#define CAL_MemPoolExtendStatic  MemPoolExtendStatic
	#define CHK_MemPoolExtendStatic  TRUE
	#define EXP_MemPoolExtendStatic  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolExtendStatic", (RTS_UINTPTR)MemPoolExtendStatic, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolExtendStatic
	#define EXT_CmpMemPoolMemPoolExtendStatic
	#define GET_CmpMemPoolMemPoolExtendStatic  ERR_OK
	#define CAL_CmpMemPoolMemPoolExtendStatic pICmpMemPool->IMemPoolExtendStatic
	#define CHK_CmpMemPoolMemPoolExtendStatic (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolExtendStatic  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolExtendStatic
	#define EXT_MemPoolExtendStatic
	#define GET_MemPoolExtendStatic(fl)  CAL_CMGETAPI( "MemPoolExtendStatic" ) 
	#define CAL_MemPoolExtendStatic pICmpMemPool->IMemPoolExtendStatic
	#define CHK_MemPoolExtendStatic (pICmpMemPool != NULL)
	#define EXP_MemPoolExtendStatic  CAL_CMEXPAPI( "MemPoolExtendStatic" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolExtendStatic  PFMEMPOOLEXTENDSTATIC pfMemPoolExtendStatic;
	#define EXT_MemPoolExtendStatic  extern PFMEMPOOLEXTENDSTATIC pfMemPoolExtendStatic;
	#define GET_MemPoolExtendStatic(fl)  s_pfCMGetAPI2( "MemPoolExtendStatic", (RTS_VOID_FCTPTR *)&pfMemPoolExtendStatic, (fl), 0, 0)
	#define CAL_MemPoolExtendStatic  pfMemPoolExtendStatic
	#define CHK_MemPoolExtendStatic  (pfMemPoolExtendStatic != NULL)
	#define EXP_MemPoolExtendStatic  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolExtendStatic", (RTS_UINTPTR)MemPoolExtendStatic, 0, 0) 
#endif




/**
 * <description>
 *	Create the internal sync object for synchronizing the pool.
 * </description>
 * <param name="hMemPool" type="IN">Handle to the pool</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL MemPoolCreateSyncObject(RTS_HANDLE hMemPool);
typedef RTS_RESULT (CDECL * PFMEMPOOLCREATESYNCOBJECT) (RTS_HANDLE hMemPool);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLCREATESYNCOBJECT_NOTIMPLEMENTED)
	#define USE_MemPoolCreateSyncObject
	#define EXT_MemPoolCreateSyncObject
	#define GET_MemPoolCreateSyncObject(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolCreateSyncObject(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolCreateSyncObject  FALSE
	#define EXP_MemPoolCreateSyncObject  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolCreateSyncObject
	#define EXT_MemPoolCreateSyncObject
	#define GET_MemPoolCreateSyncObject(fl)  CAL_CMGETAPI( "MemPoolCreateSyncObject" ) 
	#define CAL_MemPoolCreateSyncObject  MemPoolCreateSyncObject
	#define CHK_MemPoolCreateSyncObject  TRUE
	#define EXP_MemPoolCreateSyncObject  CAL_CMEXPAPI( "MemPoolCreateSyncObject" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolCreateSyncObject
	#define EXT_MemPoolCreateSyncObject
	#define GET_MemPoolCreateSyncObject(fl)  CAL_CMGETAPI( "MemPoolCreateSyncObject" ) 
	#define CAL_MemPoolCreateSyncObject  MemPoolCreateSyncObject
	#define CHK_MemPoolCreateSyncObject  TRUE
	#define EXP_MemPoolCreateSyncObject  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolCreateSyncObject", (RTS_UINTPTR)MemPoolCreateSyncObject, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolCreateSyncObject
	#define EXT_CmpMemPoolMemPoolCreateSyncObject
	#define GET_CmpMemPoolMemPoolCreateSyncObject  ERR_OK
	#define CAL_CmpMemPoolMemPoolCreateSyncObject pICmpMemPool->IMemPoolCreateSyncObject
	#define CHK_CmpMemPoolMemPoolCreateSyncObject (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolCreateSyncObject  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolCreateSyncObject
	#define EXT_MemPoolCreateSyncObject
	#define GET_MemPoolCreateSyncObject(fl)  CAL_CMGETAPI( "MemPoolCreateSyncObject" ) 
	#define CAL_MemPoolCreateSyncObject pICmpMemPool->IMemPoolCreateSyncObject
	#define CHK_MemPoolCreateSyncObject (pICmpMemPool != NULL)
	#define EXP_MemPoolCreateSyncObject  CAL_CMEXPAPI( "MemPoolCreateSyncObject" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolCreateSyncObject  PFMEMPOOLCREATESYNCOBJECT pfMemPoolCreateSyncObject;
	#define EXT_MemPoolCreateSyncObject  extern PFMEMPOOLCREATESYNCOBJECT pfMemPoolCreateSyncObject;
	#define GET_MemPoolCreateSyncObject(fl)  s_pfCMGetAPI2( "MemPoolCreateSyncObject", (RTS_VOID_FCTPTR *)&pfMemPoolCreateSyncObject, (fl), 0, 0)
	#define CAL_MemPoolCreateSyncObject  pfMemPoolCreateSyncObject
	#define CHK_MemPoolCreateSyncObject  (pfMemPoolCreateSyncObject != NULL)
	#define EXP_MemPoolCreateSyncObject  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolCreateSyncObject", (RTS_UINTPTR)MemPoolCreateSyncObject, 0, 0) 
#endif




/**
 * <description>
 *	Delete the internal sync object for synchronizing the pool.
 * </description>
 * <param name="hMemPool" type="IN">Handle to the pool</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL MemPoolDeleteSyncObject(RTS_HANDLE hMemPool);
typedef RTS_RESULT (CDECL * PFMEMPOOLDELETESYNCOBJECT) (RTS_HANDLE hMemPool);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLDELETESYNCOBJECT_NOTIMPLEMENTED)
	#define USE_MemPoolDeleteSyncObject
	#define EXT_MemPoolDeleteSyncObject
	#define GET_MemPoolDeleteSyncObject(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolDeleteSyncObject(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolDeleteSyncObject  FALSE
	#define EXP_MemPoolDeleteSyncObject  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolDeleteSyncObject
	#define EXT_MemPoolDeleteSyncObject
	#define GET_MemPoolDeleteSyncObject(fl)  CAL_CMGETAPI( "MemPoolDeleteSyncObject" ) 
	#define CAL_MemPoolDeleteSyncObject  MemPoolDeleteSyncObject
	#define CHK_MemPoolDeleteSyncObject  TRUE
	#define EXP_MemPoolDeleteSyncObject  CAL_CMEXPAPI( "MemPoolDeleteSyncObject" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolDeleteSyncObject
	#define EXT_MemPoolDeleteSyncObject
	#define GET_MemPoolDeleteSyncObject(fl)  CAL_CMGETAPI( "MemPoolDeleteSyncObject" ) 
	#define CAL_MemPoolDeleteSyncObject  MemPoolDeleteSyncObject
	#define CHK_MemPoolDeleteSyncObject  TRUE
	#define EXP_MemPoolDeleteSyncObject  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolDeleteSyncObject", (RTS_UINTPTR)MemPoolDeleteSyncObject, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolDeleteSyncObject
	#define EXT_CmpMemPoolMemPoolDeleteSyncObject
	#define GET_CmpMemPoolMemPoolDeleteSyncObject  ERR_OK
	#define CAL_CmpMemPoolMemPoolDeleteSyncObject pICmpMemPool->IMemPoolDeleteSyncObject
	#define CHK_CmpMemPoolMemPoolDeleteSyncObject (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolDeleteSyncObject  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolDeleteSyncObject
	#define EXT_MemPoolDeleteSyncObject
	#define GET_MemPoolDeleteSyncObject(fl)  CAL_CMGETAPI( "MemPoolDeleteSyncObject" ) 
	#define CAL_MemPoolDeleteSyncObject pICmpMemPool->IMemPoolDeleteSyncObject
	#define CHK_MemPoolDeleteSyncObject (pICmpMemPool != NULL)
	#define EXP_MemPoolDeleteSyncObject  CAL_CMEXPAPI( "MemPoolDeleteSyncObject" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolDeleteSyncObject  PFMEMPOOLDELETESYNCOBJECT pfMemPoolDeleteSyncObject;
	#define EXT_MemPoolDeleteSyncObject  extern PFMEMPOOLDELETESYNCOBJECT pfMemPoolDeleteSyncObject;
	#define GET_MemPoolDeleteSyncObject(fl)  s_pfCMGetAPI2( "MemPoolDeleteSyncObject", (RTS_VOID_FCTPTR *)&pfMemPoolDeleteSyncObject, (fl), 0, 0)
	#define CAL_MemPoolDeleteSyncObject  pfMemPoolDeleteSyncObject
	#define CHK_MemPoolDeleteSyncObject  (pfMemPoolDeleteSyncObject != NULL)
	#define EXP_MemPoolDeleteSyncObject  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolDeleteSyncObject", (RTS_UINTPTR)MemPoolDeleteSyncObject, 0, 0) 
#endif




/**
 * <description>
 *	Delete an existing pool
 * </description>
 * <param name="hMemPool" type="IN">Handle to the pool</param>
 * <param name="pszComponentName" type="IN">Component name</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL MemPoolDelete(RTS_HANDLE hMemPool, char *pszComponentName);
typedef RTS_RESULT (CDECL * PFMEMPOOLDELETE) (RTS_HANDLE hMemPool, char *pszComponentName);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLDELETE_NOTIMPLEMENTED)
	#define USE_MemPoolDelete
	#define EXT_MemPoolDelete
	#define GET_MemPoolDelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolDelete(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolDelete  FALSE
	#define EXP_MemPoolDelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolDelete
	#define EXT_MemPoolDelete
	#define GET_MemPoolDelete(fl)  CAL_CMGETAPI( "MemPoolDelete" ) 
	#define CAL_MemPoolDelete  MemPoolDelete
	#define CHK_MemPoolDelete  TRUE
	#define EXP_MemPoolDelete  CAL_CMEXPAPI( "MemPoolDelete" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolDelete
	#define EXT_MemPoolDelete
	#define GET_MemPoolDelete(fl)  CAL_CMGETAPI( "MemPoolDelete" ) 
	#define CAL_MemPoolDelete  MemPoolDelete
	#define CHK_MemPoolDelete  TRUE
	#define EXP_MemPoolDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolDelete", (RTS_UINTPTR)MemPoolDelete, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolDelete
	#define EXT_CmpMemPoolMemPoolDelete
	#define GET_CmpMemPoolMemPoolDelete  ERR_OK
	#define CAL_CmpMemPoolMemPoolDelete pICmpMemPool->IMemPoolDelete
	#define CHK_CmpMemPoolMemPoolDelete (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolDelete  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolDelete
	#define EXT_MemPoolDelete
	#define GET_MemPoolDelete(fl)  CAL_CMGETAPI( "MemPoolDelete" ) 
	#define CAL_MemPoolDelete pICmpMemPool->IMemPoolDelete
	#define CHK_MemPoolDelete (pICmpMemPool != NULL)
	#define EXP_MemPoolDelete  CAL_CMEXPAPI( "MemPoolDelete" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolDelete  PFMEMPOOLDELETE pfMemPoolDelete;
	#define EXT_MemPoolDelete  extern PFMEMPOOLDELETE pfMemPoolDelete;
	#define GET_MemPoolDelete(fl)  s_pfCMGetAPI2( "MemPoolDelete", (RTS_VOID_FCTPTR *)&pfMemPoolDelete, (fl), 0, 0)
	#define CAL_MemPoolDelete  pfMemPoolDelete
	#define CHK_MemPoolDelete  (pfMemPoolDelete != NULL)
	#define EXP_MemPoolDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolDelete", (RTS_UINTPTR)MemPoolDelete, 0, 0) 
#endif




/**
 * <description>
 *	Cleanup the pool (delete all allocated heap pool objects)
 * </description>
 * <param name="hMemPool" type="IN">Handle to the pool</param>
 * <param name="pszComponentName" type="IN">Component name</param>
 * <param name="bReleaseSemaphore" type="IN">1=Pool semaphore is released, 0=Only cleanup</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL MemPoolCleanup(RTS_HANDLE hMemPool, char *pszComponentName, int bReleaseSemaphore);
typedef RTS_RESULT (CDECL * PFMEMPOOLCLEANUP) (RTS_HANDLE hMemPool, char *pszComponentName, int bReleaseSemaphore);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLCLEANUP_NOTIMPLEMENTED)
	#define USE_MemPoolCleanup
	#define EXT_MemPoolCleanup
	#define GET_MemPoolCleanup(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolCleanup(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolCleanup  FALSE
	#define EXP_MemPoolCleanup  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolCleanup
	#define EXT_MemPoolCleanup
	#define GET_MemPoolCleanup(fl)  CAL_CMGETAPI( "MemPoolCleanup" ) 
	#define CAL_MemPoolCleanup  MemPoolCleanup
	#define CHK_MemPoolCleanup  TRUE
	#define EXP_MemPoolCleanup  CAL_CMEXPAPI( "MemPoolCleanup" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolCleanup
	#define EXT_MemPoolCleanup
	#define GET_MemPoolCleanup(fl)  CAL_CMGETAPI( "MemPoolCleanup" ) 
	#define CAL_MemPoolCleanup  MemPoolCleanup
	#define CHK_MemPoolCleanup  TRUE
	#define EXP_MemPoolCleanup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolCleanup", (RTS_UINTPTR)MemPoolCleanup, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolCleanup
	#define EXT_CmpMemPoolMemPoolCleanup
	#define GET_CmpMemPoolMemPoolCleanup  ERR_OK
	#define CAL_CmpMemPoolMemPoolCleanup pICmpMemPool->IMemPoolCleanup
	#define CHK_CmpMemPoolMemPoolCleanup (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolCleanup  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolCleanup
	#define EXT_MemPoolCleanup
	#define GET_MemPoolCleanup(fl)  CAL_CMGETAPI( "MemPoolCleanup" ) 
	#define CAL_MemPoolCleanup pICmpMemPool->IMemPoolCleanup
	#define CHK_MemPoolCleanup (pICmpMemPool != NULL)
	#define EXP_MemPoolCleanup  CAL_CMEXPAPI( "MemPoolCleanup" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolCleanup  PFMEMPOOLCLEANUP pfMemPoolCleanup;
	#define EXT_MemPoolCleanup  extern PFMEMPOOLCLEANUP pfMemPoolCleanup;
	#define GET_MemPoolCleanup(fl)  s_pfCMGetAPI2( "MemPoolCleanup", (RTS_VOID_FCTPTR *)&pfMemPoolCleanup, (fl), 0, 0)
	#define CAL_MemPoolCleanup  pfMemPoolCleanup
	#define CHK_MemPoolCleanup  (pfMemPoolCleanup != NULL)
	#define EXP_MemPoolCleanup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolCleanup", (RTS_UINTPTR)MemPoolCleanup, 0, 0) 
#endif






/** 
 * <description>
 * <p>Get one memory block out of the pool.</p>
 * <p>SIL2 Implementation: If pPCB is wrong, an Exception is generated!</p>
 * </description>
 * <param name="hMemPool" type="IN" range="[RTS_INVALID_HANDLE,VALID_MEMPOOLHANDLE,INVALID_MEMPOOLHANDLE]">Handle to the pool</param>
 * <parampseudo name="hMemPool.NumEntries" type="IN" range="[0..NUM_OF_STATIC_ELEMENTS-1,NUM_OF_STATIC_ELEMENTS..INT_MAX]">Number of already allocated entries from the pool</parampseudo>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <parampseudo name="bExceptionGenerated" type="OUT" range="[TRUE,FALSE]">specifies, if an exception was generated or not</parampseudo>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Retrieved free block from MemPool</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_INVALID_HANDLE">No free block found</errorcode> 
 * <result>Pointer to the memory block</result>
 */
void* CDECL MemPoolGetBlock(RTS_HANDLE hMemPool, RTS_RESULT *pResult);
typedef void* (CDECL * PFMEMPOOLGETBLOCK) (RTS_HANDLE hMemPool, RTS_RESULT *pResult);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLGETBLOCK_NOTIMPLEMENTED)
	#define USE_MemPoolGetBlock
	#define EXT_MemPoolGetBlock
	#define GET_MemPoolGetBlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolGetBlock(p0,p1)  (void*)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolGetBlock  FALSE
	#define EXP_MemPoolGetBlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolGetBlock
	#define EXT_MemPoolGetBlock
	#define GET_MemPoolGetBlock(fl)  CAL_CMGETAPI( "MemPoolGetBlock" ) 
	#define CAL_MemPoolGetBlock  MemPoolGetBlock
	#define CHK_MemPoolGetBlock  TRUE
	#define EXP_MemPoolGetBlock  CAL_CMEXPAPI( "MemPoolGetBlock" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolGetBlock
	#define EXT_MemPoolGetBlock
	#define GET_MemPoolGetBlock(fl)  CAL_CMGETAPI( "MemPoolGetBlock" ) 
	#define CAL_MemPoolGetBlock  MemPoolGetBlock
	#define CHK_MemPoolGetBlock  TRUE
	#define EXP_MemPoolGetBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolGetBlock", (RTS_UINTPTR)MemPoolGetBlock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolGetBlock
	#define EXT_CmpMemPoolMemPoolGetBlock
	#define GET_CmpMemPoolMemPoolGetBlock  ERR_OK
	#define CAL_CmpMemPoolMemPoolGetBlock pICmpMemPool->IMemPoolGetBlock
	#define CHK_CmpMemPoolMemPoolGetBlock (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolGetBlock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolGetBlock
	#define EXT_MemPoolGetBlock
	#define GET_MemPoolGetBlock(fl)  CAL_CMGETAPI( "MemPoolGetBlock" ) 
	#define CAL_MemPoolGetBlock pICmpMemPool->IMemPoolGetBlock
	#define CHK_MemPoolGetBlock (pICmpMemPool != NULL)
	#define EXP_MemPoolGetBlock  CAL_CMEXPAPI( "MemPoolGetBlock" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolGetBlock  PFMEMPOOLGETBLOCK pfMemPoolGetBlock;
	#define EXT_MemPoolGetBlock  extern PFMEMPOOLGETBLOCK pfMemPoolGetBlock;
	#define GET_MemPoolGetBlock(fl)  s_pfCMGetAPI2( "MemPoolGetBlock", (RTS_VOID_FCTPTR *)&pfMemPoolGetBlock, (fl), 0, 0)
	#define CAL_MemPoolGetBlock  pfMemPoolGetBlock
	#define CHK_MemPoolGetBlock  (pfMemPoolGetBlock != NULL)
	#define EXP_MemPoolGetBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolGetBlock", (RTS_UINTPTR)MemPoolGetBlock, 0, 0) 
#endif




/**
 * <description>
 *	Get one memory block out of the pool
 * </description>
 * <param name="hMemPool" type="IN">Handle to the pool</param>
 * <param name="bDynamic" type="IN">1=Block is created dynamically, if the pool is empty, 0=Only use of static pool memory</param>
 * <param name="pszComponentName" type="IN">Pointer to the component name for dynamic memory allocation</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the memory block</result>
 */
void* CDECL MemPoolGetBlock2(RTS_HANDLE hMemPool, int bDynamic, char *pszComponentName, RTS_RESULT *pResult);
typedef void* (CDECL * PFMEMPOOLGETBLOCK2) (RTS_HANDLE hMemPool, int bDynamic, char *pszComponentName, RTS_RESULT *pResult);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLGETBLOCK2_NOTIMPLEMENTED)
	#define USE_MemPoolGetBlock2
	#define EXT_MemPoolGetBlock2
	#define GET_MemPoolGetBlock2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolGetBlock2(p0,p1,p2,p3)  (void*)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolGetBlock2  FALSE
	#define EXP_MemPoolGetBlock2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolGetBlock2
	#define EXT_MemPoolGetBlock2
	#define GET_MemPoolGetBlock2(fl)  CAL_CMGETAPI( "MemPoolGetBlock2" ) 
	#define CAL_MemPoolGetBlock2  MemPoolGetBlock2
	#define CHK_MemPoolGetBlock2  TRUE
	#define EXP_MemPoolGetBlock2  CAL_CMEXPAPI( "MemPoolGetBlock2" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolGetBlock2
	#define EXT_MemPoolGetBlock2
	#define GET_MemPoolGetBlock2(fl)  CAL_CMGETAPI( "MemPoolGetBlock2" ) 
	#define CAL_MemPoolGetBlock2  MemPoolGetBlock2
	#define CHK_MemPoolGetBlock2  TRUE
	#define EXP_MemPoolGetBlock2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolGetBlock2", (RTS_UINTPTR)MemPoolGetBlock2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolGetBlock2
	#define EXT_CmpMemPoolMemPoolGetBlock2
	#define GET_CmpMemPoolMemPoolGetBlock2  ERR_OK
	#define CAL_CmpMemPoolMemPoolGetBlock2 pICmpMemPool->IMemPoolGetBlock2
	#define CHK_CmpMemPoolMemPoolGetBlock2 (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolGetBlock2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolGetBlock2
	#define EXT_MemPoolGetBlock2
	#define GET_MemPoolGetBlock2(fl)  CAL_CMGETAPI( "MemPoolGetBlock2" ) 
	#define CAL_MemPoolGetBlock2 pICmpMemPool->IMemPoolGetBlock2
	#define CHK_MemPoolGetBlock2 (pICmpMemPool != NULL)
	#define EXP_MemPoolGetBlock2  CAL_CMEXPAPI( "MemPoolGetBlock2" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolGetBlock2  PFMEMPOOLGETBLOCK2 pfMemPoolGetBlock2;
	#define EXT_MemPoolGetBlock2  extern PFMEMPOOLGETBLOCK2 pfMemPoolGetBlock2;
	#define GET_MemPoolGetBlock2(fl)  s_pfCMGetAPI2( "MemPoolGetBlock2", (RTS_VOID_FCTPTR *)&pfMemPoolGetBlock2, (fl), 0, 0)
	#define CAL_MemPoolGetBlock2  pfMemPoolGetBlock2
	#define CHK_MemPoolGetBlock2  (pfMemPoolGetBlock2 != NULL)
	#define EXP_MemPoolGetBlock2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolGetBlock2", (RTS_UINTPTR)MemPoolGetBlock2, 0, 0) 
#endif




/**
 * <description>
 *	Get one the pool control block of a specified pool
 * </description>
 * <param name="hMemPool" type="IN">Handle to the pool</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the pool control block</result>
 */
RTS_PCB* CDECL MemPoolGetPCB(RTS_HANDLE hMemPool, RTS_RESULT *pResult);
typedef RTS_PCB* (CDECL * PFMEMPOOLGETPCB) (RTS_HANDLE hMemPool, RTS_RESULT *pResult);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLGETPCB_NOTIMPLEMENTED)
	#define USE_MemPoolGetPCB
	#define EXT_MemPoolGetPCB
	#define GET_MemPoolGetPCB(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolGetPCB(p0,p1)  (RTS_PCB*)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolGetPCB  FALSE
	#define EXP_MemPoolGetPCB  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolGetPCB
	#define EXT_MemPoolGetPCB
	#define GET_MemPoolGetPCB(fl)  CAL_CMGETAPI( "MemPoolGetPCB" ) 
	#define CAL_MemPoolGetPCB  MemPoolGetPCB
	#define CHK_MemPoolGetPCB  TRUE
	#define EXP_MemPoolGetPCB  CAL_CMEXPAPI( "MemPoolGetPCB" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolGetPCB
	#define EXT_MemPoolGetPCB
	#define GET_MemPoolGetPCB(fl)  CAL_CMGETAPI( "MemPoolGetPCB" ) 
	#define CAL_MemPoolGetPCB  MemPoolGetPCB
	#define CHK_MemPoolGetPCB  TRUE
	#define EXP_MemPoolGetPCB  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolGetPCB", (RTS_UINTPTR)MemPoolGetPCB, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolGetPCB
	#define EXT_CmpMemPoolMemPoolGetPCB
	#define GET_CmpMemPoolMemPoolGetPCB  ERR_OK
	#define CAL_CmpMemPoolMemPoolGetPCB pICmpMemPool->IMemPoolGetPCB
	#define CHK_CmpMemPoolMemPoolGetPCB (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolGetPCB  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolGetPCB
	#define EXT_MemPoolGetPCB
	#define GET_MemPoolGetPCB(fl)  CAL_CMGETAPI( "MemPoolGetPCB" ) 
	#define CAL_MemPoolGetPCB pICmpMemPool->IMemPoolGetPCB
	#define CHK_MemPoolGetPCB (pICmpMemPool != NULL)
	#define EXP_MemPoolGetPCB  CAL_CMEXPAPI( "MemPoolGetPCB" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolGetPCB  PFMEMPOOLGETPCB pfMemPoolGetPCB;
	#define EXT_MemPoolGetPCB  extern PFMEMPOOLGETPCB pfMemPoolGetPCB;
	#define GET_MemPoolGetPCB(fl)  s_pfCMGetAPI2( "MemPoolGetPCB", (RTS_VOID_FCTPTR *)&pfMemPoolGetPCB, (fl), 0, 0)
	#define CAL_MemPoolGetPCB  pfMemPoolGetPCB
	#define CHK_MemPoolGetPCB  (pfMemPoolGetPCB != NULL)
	#define EXP_MemPoolGetPCB  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolGetPCB", (RTS_UINTPTR)MemPoolGetPCB, 0, 0) 
#endif




/**
 * <description>
 *	Put a memory block back into the pool (release). Now, the block is in the chain list of free blocks again. 
 * </description>
 * <param name="pBlock" type="IN" range="[NULL,VALID_BLOCK,INVALID_BLOCK]">Pointer to the memory block</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Successfully added Block to MemPool</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Could not add Block to MemPool, wrong pBlock</errorcode> 
 * <result>error code</result>
 */
RTS_RESULT CDECL MemPoolPutBlock(void* pBlock);
typedef RTS_RESULT (CDECL * PFMEMPOOLPUTBLOCK) (void* pBlock);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLPUTBLOCK_NOTIMPLEMENTED)
	#define USE_MemPoolPutBlock
	#define EXT_MemPoolPutBlock
	#define GET_MemPoolPutBlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolPutBlock(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolPutBlock  FALSE
	#define EXP_MemPoolPutBlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolPutBlock
	#define EXT_MemPoolPutBlock
	#define GET_MemPoolPutBlock(fl)  CAL_CMGETAPI( "MemPoolPutBlock" ) 
	#define CAL_MemPoolPutBlock  MemPoolPutBlock
	#define CHK_MemPoolPutBlock  TRUE
	#define EXP_MemPoolPutBlock  CAL_CMEXPAPI( "MemPoolPutBlock" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolPutBlock
	#define EXT_MemPoolPutBlock
	#define GET_MemPoolPutBlock(fl)  CAL_CMGETAPI( "MemPoolPutBlock" ) 
	#define CAL_MemPoolPutBlock  MemPoolPutBlock
	#define CHK_MemPoolPutBlock  TRUE
	#define EXP_MemPoolPutBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolPutBlock", (RTS_UINTPTR)MemPoolPutBlock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolPutBlock
	#define EXT_CmpMemPoolMemPoolPutBlock
	#define GET_CmpMemPoolMemPoolPutBlock  ERR_OK
	#define CAL_CmpMemPoolMemPoolPutBlock pICmpMemPool->IMemPoolPutBlock
	#define CHK_CmpMemPoolMemPoolPutBlock (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolPutBlock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolPutBlock
	#define EXT_MemPoolPutBlock
	#define GET_MemPoolPutBlock(fl)  CAL_CMGETAPI( "MemPoolPutBlock" ) 
	#define CAL_MemPoolPutBlock pICmpMemPool->IMemPoolPutBlock
	#define CHK_MemPoolPutBlock (pICmpMemPool != NULL)
	#define EXP_MemPoolPutBlock  CAL_CMEXPAPI( "MemPoolPutBlock" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolPutBlock  PFMEMPOOLPUTBLOCK pfMemPoolPutBlock;
	#define EXT_MemPoolPutBlock  extern PFMEMPOOLPUTBLOCK pfMemPoolPutBlock;
	#define GET_MemPoolPutBlock(fl)  s_pfCMGetAPI2( "MemPoolPutBlock", (RTS_VOID_FCTPTR *)&pfMemPoolPutBlock, (fl), 0, 0)
	#define CAL_MemPoolPutBlock  pfMemPoolPutBlock
	#define CHK_MemPoolPutBlock  (pfMemPoolPutBlock != NULL)
	#define EXP_MemPoolPutBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolPutBlock", (RTS_UINTPTR)MemPoolPutBlock, 0, 0) 
#endif




/**
 * <description>
 *	Add used block at the beginning of the pool. Now, the block is in the chain list of used blocks.
 * </description>
 * <param name="pBlock" type="IN" range="[NULL,VALID_BLOCK]">Pointer to the memory block</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Successfully added Block to MemPool</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Could not add Block to MemPool, wrong pBlock</errorcode> 
 * <result>error code</result>
 */
RTS_RESULT CDECL MemPoolAddUsedBlock(void* pBlock);
typedef RTS_RESULT (CDECL * PFMEMPOOLADDUSEDBLOCK) (void* pBlock);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLADDUSEDBLOCK_NOTIMPLEMENTED)
	#define USE_MemPoolAddUsedBlock
	#define EXT_MemPoolAddUsedBlock
	#define GET_MemPoolAddUsedBlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolAddUsedBlock(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolAddUsedBlock  FALSE
	#define EXP_MemPoolAddUsedBlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolAddUsedBlock
	#define EXT_MemPoolAddUsedBlock
	#define GET_MemPoolAddUsedBlock(fl)  CAL_CMGETAPI( "MemPoolAddUsedBlock" ) 
	#define CAL_MemPoolAddUsedBlock  MemPoolAddUsedBlock
	#define CHK_MemPoolAddUsedBlock  TRUE
	#define EXP_MemPoolAddUsedBlock  CAL_CMEXPAPI( "MemPoolAddUsedBlock" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolAddUsedBlock
	#define EXT_MemPoolAddUsedBlock
	#define GET_MemPoolAddUsedBlock(fl)  CAL_CMGETAPI( "MemPoolAddUsedBlock" ) 
	#define CAL_MemPoolAddUsedBlock  MemPoolAddUsedBlock
	#define CHK_MemPoolAddUsedBlock  TRUE
	#define EXP_MemPoolAddUsedBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolAddUsedBlock", (RTS_UINTPTR)MemPoolAddUsedBlock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolAddUsedBlock
	#define EXT_CmpMemPoolMemPoolAddUsedBlock
	#define GET_CmpMemPoolMemPoolAddUsedBlock  ERR_OK
	#define CAL_CmpMemPoolMemPoolAddUsedBlock pICmpMemPool->IMemPoolAddUsedBlock
	#define CHK_CmpMemPoolMemPoolAddUsedBlock (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolAddUsedBlock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolAddUsedBlock
	#define EXT_MemPoolAddUsedBlock
	#define GET_MemPoolAddUsedBlock(fl)  CAL_CMGETAPI( "MemPoolAddUsedBlock" ) 
	#define CAL_MemPoolAddUsedBlock pICmpMemPool->IMemPoolAddUsedBlock
	#define CHK_MemPoolAddUsedBlock (pICmpMemPool != NULL)
	#define EXP_MemPoolAddUsedBlock  CAL_CMEXPAPI( "MemPoolAddUsedBlock" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolAddUsedBlock  PFMEMPOOLADDUSEDBLOCK pfMemPoolAddUsedBlock;
	#define EXT_MemPoolAddUsedBlock  extern PFMEMPOOLADDUSEDBLOCK pfMemPoolAddUsedBlock;
	#define GET_MemPoolAddUsedBlock(fl)  s_pfCMGetAPI2( "MemPoolAddUsedBlock", (RTS_VOID_FCTPTR *)&pfMemPoolAddUsedBlock, (fl), 0, 0)
	#define CAL_MemPoolAddUsedBlock  pfMemPoolAddUsedBlock
	#define CHK_MemPoolAddUsedBlock  (pfMemPoolAddUsedBlock != NULL)
	#define EXP_MemPoolAddUsedBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolAddUsedBlock", (RTS_UINTPTR)MemPoolAddUsedBlock, 0, 0) 
#endif




/**
 * <description>
 *	Add used block at the end of the pool. Now, the block is in the chain list of used blocks.
 * </description>
 * <param name="pBlock" type="IN" range="[NULL,VALID_BLOCK]">Pointer to the memory block</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Successfully added Block to MemPool</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Could not add Block to MemPool, wrong pBlock</errorcode> 
 * <result>error code</result>
 */
RTS_RESULT CDECL MemPoolAppendUsedBlock(void* pBlock);
typedef RTS_RESULT (CDECL * PFMEMPOOLAPPENDUSEDBLOCK) (void* pBlock);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLAPPENDUSEDBLOCK_NOTIMPLEMENTED)
	#define USE_MemPoolAppendUsedBlock
	#define EXT_MemPoolAppendUsedBlock
	#define GET_MemPoolAppendUsedBlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolAppendUsedBlock(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolAppendUsedBlock  FALSE
	#define EXP_MemPoolAppendUsedBlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolAppendUsedBlock
	#define EXT_MemPoolAppendUsedBlock
	#define GET_MemPoolAppendUsedBlock(fl)  CAL_CMGETAPI( "MemPoolAppendUsedBlock" ) 
	#define CAL_MemPoolAppendUsedBlock  MemPoolAppendUsedBlock
	#define CHK_MemPoolAppendUsedBlock  TRUE
	#define EXP_MemPoolAppendUsedBlock  CAL_CMEXPAPI( "MemPoolAppendUsedBlock" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolAppendUsedBlock
	#define EXT_MemPoolAppendUsedBlock
	#define GET_MemPoolAppendUsedBlock(fl)  CAL_CMGETAPI( "MemPoolAppendUsedBlock" ) 
	#define CAL_MemPoolAppendUsedBlock  MemPoolAppendUsedBlock
	#define CHK_MemPoolAppendUsedBlock  TRUE
	#define EXP_MemPoolAppendUsedBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolAppendUsedBlock", (RTS_UINTPTR)MemPoolAppendUsedBlock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolAppendUsedBlock
	#define EXT_CmpMemPoolMemPoolAppendUsedBlock
	#define GET_CmpMemPoolMemPoolAppendUsedBlock  ERR_OK
	#define CAL_CmpMemPoolMemPoolAppendUsedBlock pICmpMemPool->IMemPoolAppendUsedBlock
	#define CHK_CmpMemPoolMemPoolAppendUsedBlock (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolAppendUsedBlock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolAppendUsedBlock
	#define EXT_MemPoolAppendUsedBlock
	#define GET_MemPoolAppendUsedBlock(fl)  CAL_CMGETAPI( "MemPoolAppendUsedBlock" ) 
	#define CAL_MemPoolAppendUsedBlock pICmpMemPool->IMemPoolAppendUsedBlock
	#define CHK_MemPoolAppendUsedBlock (pICmpMemPool != NULL)
	#define EXP_MemPoolAppendUsedBlock  CAL_CMEXPAPI( "MemPoolAppendUsedBlock" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolAppendUsedBlock  PFMEMPOOLAPPENDUSEDBLOCK pfMemPoolAppendUsedBlock;
	#define EXT_MemPoolAppendUsedBlock  extern PFMEMPOOLAPPENDUSEDBLOCK pfMemPoolAppendUsedBlock;
	#define GET_MemPoolAppendUsedBlock(fl)  s_pfCMGetAPI2( "MemPoolAppendUsedBlock", (RTS_VOID_FCTPTR *)&pfMemPoolAppendUsedBlock, (fl), 0, 0)
	#define CAL_MemPoolAppendUsedBlock  pfMemPoolAppendUsedBlock
	#define CHK_MemPoolAppendUsedBlock  (pfMemPoolAppendUsedBlock != NULL)
	#define EXP_MemPoolAppendUsedBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolAppendUsedBlock", (RTS_UINTPTR)MemPoolAppendUsedBlock, 0, 0) 
#endif




/**
 * <description>
 *	Insert used block right after the specified block or as a head element of an internal used blocks list.
 * </description>
 * <param name="pPrevBlock" type="IN" range="[NULL,VALID_PREVBLOCK,INVALID_PREVBLOCK]">Pointer to the predecessor block</param>
 * <param name="pBlock" type="IN" range="[NULL,VALID_BLOCK]">Pointer to the memory block</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Successfully inserted Block to MemPool</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Could not insert Block to MemPool because pBlock is NULL or pPrevBlock belongs to a different pool than pBlock</errorcode> 
 * <result>error code</result>
 */
RTS_RESULT CDECL MemPoolInsertUsedBlock(void* pPrevBlock, void* pBlock);
typedef RTS_RESULT (CDECL * PFMEMPOOLINSERTUSEDBLOCK) (void* pPrevBlock, void* pBlock);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLINSERTUSEDBLOCK_NOTIMPLEMENTED)
	#define USE_MemPoolInsertUsedBlock
	#define EXT_MemPoolInsertUsedBlock
	#define GET_MemPoolInsertUsedBlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolInsertUsedBlock(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolInsertUsedBlock  FALSE
	#define EXP_MemPoolInsertUsedBlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolInsertUsedBlock
	#define EXT_MemPoolInsertUsedBlock
	#define GET_MemPoolInsertUsedBlock(fl)  CAL_CMGETAPI( "MemPoolInsertUsedBlock" ) 
	#define CAL_MemPoolInsertUsedBlock  MemPoolInsertUsedBlock
	#define CHK_MemPoolInsertUsedBlock  TRUE
	#define EXP_MemPoolInsertUsedBlock  CAL_CMEXPAPI( "MemPoolInsertUsedBlock" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolInsertUsedBlock
	#define EXT_MemPoolInsertUsedBlock
	#define GET_MemPoolInsertUsedBlock(fl)  CAL_CMGETAPI( "MemPoolInsertUsedBlock" ) 
	#define CAL_MemPoolInsertUsedBlock  MemPoolInsertUsedBlock
	#define CHK_MemPoolInsertUsedBlock  TRUE
	#define EXP_MemPoolInsertUsedBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolInsertUsedBlock", (RTS_UINTPTR)MemPoolInsertUsedBlock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolInsertUsedBlock
	#define EXT_CmpMemPoolMemPoolInsertUsedBlock
	#define GET_CmpMemPoolMemPoolInsertUsedBlock  ERR_OK
	#define CAL_CmpMemPoolMemPoolInsertUsedBlock pICmpMemPool->IMemPoolInsertUsedBlock
	#define CHK_CmpMemPoolMemPoolInsertUsedBlock (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolInsertUsedBlock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolInsertUsedBlock
	#define EXT_MemPoolInsertUsedBlock
	#define GET_MemPoolInsertUsedBlock(fl)  CAL_CMGETAPI( "MemPoolInsertUsedBlock" ) 
	#define CAL_MemPoolInsertUsedBlock pICmpMemPool->IMemPoolInsertUsedBlock
	#define CHK_MemPoolInsertUsedBlock (pICmpMemPool != NULL)
	#define EXP_MemPoolInsertUsedBlock  CAL_CMEXPAPI( "MemPoolInsertUsedBlock" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolInsertUsedBlock  PFMEMPOOLINSERTUSEDBLOCK pfMemPoolInsertUsedBlock;
	#define EXT_MemPoolInsertUsedBlock  extern PFMEMPOOLINSERTUSEDBLOCK pfMemPoolInsertUsedBlock;
	#define GET_MemPoolInsertUsedBlock(fl)  s_pfCMGetAPI2( "MemPoolInsertUsedBlock", (RTS_VOID_FCTPTR *)&pfMemPoolInsertUsedBlock, (fl), 0, 0)
	#define CAL_MemPoolInsertUsedBlock  pfMemPoolInsertUsedBlock
	#define CHK_MemPoolInsertUsedBlock  (pfMemPoolInsertUsedBlock != NULL)
	#define EXP_MemPoolInsertUsedBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolInsertUsedBlock", (RTS_UINTPTR)MemPoolInsertUsedBlock, 0, 0) 
#endif




/**
 * <description>
 *	Remove used block from the pool. Now, the block is removed from the chain list of used blocks.
 * </description>
 * <param name="pBlock" type="IN" range="[NULL,VALID_BLOCK]">Pointer to the memory block</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Successfully removed Block from MemPool</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Could not remove Block from MemPool, wrong pBlock</errorcode> 
 * <result>error code</result>
 */
RTS_RESULT CDECL MemPoolRemoveUsedBlock(void* pBlock);
typedef RTS_RESULT (CDECL * PFMEMPOOLREMOVEUSEDBLOCK) (void* pBlock);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLREMOVEUSEDBLOCK_NOTIMPLEMENTED)
	#define USE_MemPoolRemoveUsedBlock
	#define EXT_MemPoolRemoveUsedBlock
	#define GET_MemPoolRemoveUsedBlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolRemoveUsedBlock(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolRemoveUsedBlock  FALSE
	#define EXP_MemPoolRemoveUsedBlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolRemoveUsedBlock
	#define EXT_MemPoolRemoveUsedBlock
	#define GET_MemPoolRemoveUsedBlock(fl)  CAL_CMGETAPI( "MemPoolRemoveUsedBlock" ) 
	#define CAL_MemPoolRemoveUsedBlock  MemPoolRemoveUsedBlock
	#define CHK_MemPoolRemoveUsedBlock  TRUE
	#define EXP_MemPoolRemoveUsedBlock  CAL_CMEXPAPI( "MemPoolRemoveUsedBlock" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolRemoveUsedBlock
	#define EXT_MemPoolRemoveUsedBlock
	#define GET_MemPoolRemoveUsedBlock(fl)  CAL_CMGETAPI( "MemPoolRemoveUsedBlock" ) 
	#define CAL_MemPoolRemoveUsedBlock  MemPoolRemoveUsedBlock
	#define CHK_MemPoolRemoveUsedBlock  TRUE
	#define EXP_MemPoolRemoveUsedBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolRemoveUsedBlock", (RTS_UINTPTR)MemPoolRemoveUsedBlock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolRemoveUsedBlock
	#define EXT_CmpMemPoolMemPoolRemoveUsedBlock
	#define GET_CmpMemPoolMemPoolRemoveUsedBlock  ERR_OK
	#define CAL_CmpMemPoolMemPoolRemoveUsedBlock pICmpMemPool->IMemPoolRemoveUsedBlock
	#define CHK_CmpMemPoolMemPoolRemoveUsedBlock (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolRemoveUsedBlock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolRemoveUsedBlock
	#define EXT_MemPoolRemoveUsedBlock
	#define GET_MemPoolRemoveUsedBlock(fl)  CAL_CMGETAPI( "MemPoolRemoveUsedBlock" ) 
	#define CAL_MemPoolRemoveUsedBlock pICmpMemPool->IMemPoolRemoveUsedBlock
	#define CHK_MemPoolRemoveUsedBlock (pICmpMemPool != NULL)
	#define EXP_MemPoolRemoveUsedBlock  CAL_CMEXPAPI( "MemPoolRemoveUsedBlock" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolRemoveUsedBlock  PFMEMPOOLREMOVEUSEDBLOCK pfMemPoolRemoveUsedBlock;
	#define EXT_MemPoolRemoveUsedBlock  extern PFMEMPOOLREMOVEUSEDBLOCK pfMemPoolRemoveUsedBlock;
	#define GET_MemPoolRemoveUsedBlock(fl)  s_pfCMGetAPI2( "MemPoolRemoveUsedBlock", (RTS_VOID_FCTPTR *)&pfMemPoolRemoveUsedBlock, (fl), 0, 0)
	#define CAL_MemPoolRemoveUsedBlock  pfMemPoolRemoveUsedBlock
	#define CHK_MemPoolRemoveUsedBlock  (pfMemPoolRemoveUsedBlock != NULL)
	#define EXP_MemPoolRemoveUsedBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolRemoveUsedBlock", (RTS_UINTPTR)MemPoolRemoveUsedBlock, 0, 0) 
#endif




/**
 * <description>
 *	Add used block the beginning of the specified pool. Now, the block is in the chain list of used blocks.
 * </description>
 * <param name="pBlock" type="IN">Pointer to the memory block</param>
 * <param name="hPool" type="IN">Handle to the pool</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL MemPoolAddUsedBlockToPool(void* pBlock, RTS_HANDLE hPool);
typedef RTS_RESULT (CDECL * PFMEMPOOLADDUSEDBLOCKTOPOOL) (void* pBlock, RTS_HANDLE hPool);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLADDUSEDBLOCKTOPOOL_NOTIMPLEMENTED)
	#define USE_MemPoolAddUsedBlockToPool
	#define EXT_MemPoolAddUsedBlockToPool
	#define GET_MemPoolAddUsedBlockToPool(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolAddUsedBlockToPool(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolAddUsedBlockToPool  FALSE
	#define EXP_MemPoolAddUsedBlockToPool  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolAddUsedBlockToPool
	#define EXT_MemPoolAddUsedBlockToPool
	#define GET_MemPoolAddUsedBlockToPool(fl)  CAL_CMGETAPI( "MemPoolAddUsedBlockToPool" ) 
	#define CAL_MemPoolAddUsedBlockToPool  MemPoolAddUsedBlockToPool
	#define CHK_MemPoolAddUsedBlockToPool  TRUE
	#define EXP_MemPoolAddUsedBlockToPool  CAL_CMEXPAPI( "MemPoolAddUsedBlockToPool" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolAddUsedBlockToPool
	#define EXT_MemPoolAddUsedBlockToPool
	#define GET_MemPoolAddUsedBlockToPool(fl)  CAL_CMGETAPI( "MemPoolAddUsedBlockToPool" ) 
	#define CAL_MemPoolAddUsedBlockToPool  MemPoolAddUsedBlockToPool
	#define CHK_MemPoolAddUsedBlockToPool  TRUE
	#define EXP_MemPoolAddUsedBlockToPool  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolAddUsedBlockToPool", (RTS_UINTPTR)MemPoolAddUsedBlockToPool, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolAddUsedBlockToPool
	#define EXT_CmpMemPoolMemPoolAddUsedBlockToPool
	#define GET_CmpMemPoolMemPoolAddUsedBlockToPool  ERR_OK
	#define CAL_CmpMemPoolMemPoolAddUsedBlockToPool pICmpMemPool->IMemPoolAddUsedBlockToPool
	#define CHK_CmpMemPoolMemPoolAddUsedBlockToPool (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolAddUsedBlockToPool  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolAddUsedBlockToPool
	#define EXT_MemPoolAddUsedBlockToPool
	#define GET_MemPoolAddUsedBlockToPool(fl)  CAL_CMGETAPI( "MemPoolAddUsedBlockToPool" ) 
	#define CAL_MemPoolAddUsedBlockToPool pICmpMemPool->IMemPoolAddUsedBlockToPool
	#define CHK_MemPoolAddUsedBlockToPool (pICmpMemPool != NULL)
	#define EXP_MemPoolAddUsedBlockToPool  CAL_CMEXPAPI( "MemPoolAddUsedBlockToPool" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolAddUsedBlockToPool  PFMEMPOOLADDUSEDBLOCKTOPOOL pfMemPoolAddUsedBlockToPool;
	#define EXT_MemPoolAddUsedBlockToPool  extern PFMEMPOOLADDUSEDBLOCKTOPOOL pfMemPoolAddUsedBlockToPool;
	#define GET_MemPoolAddUsedBlockToPool(fl)  s_pfCMGetAPI2( "MemPoolAddUsedBlockToPool", (RTS_VOID_FCTPTR *)&pfMemPoolAddUsedBlockToPool, (fl), 0, 0)
	#define CAL_MemPoolAddUsedBlockToPool  pfMemPoolAddUsedBlockToPool
	#define CHK_MemPoolAddUsedBlockToPool  (pfMemPoolAddUsedBlockToPool != NULL)
	#define EXP_MemPoolAddUsedBlockToPool  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolAddUsedBlockToPool", (RTS_UINTPTR)MemPoolAddUsedBlockToPool, 0, 0) 
#endif




/**
 * <description>
 *	Add the block to the end of the used block list of hPool
 * </description>
 * <param name="pBlock" type="IN">Pointer to the memory block</param>
 * <param name="hPool" type="IN">Handle to the pool</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL MemPoolAppendUsedBlockToPool(void* pBlock, RTS_HANDLE hPool);
typedef RTS_RESULT (CDECL * PFMEMPOOLAPPENDUSEDBLOCKTOPOOL) (void* pBlock, RTS_HANDLE hPool);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLAPPENDUSEDBLOCKTOPOOL_NOTIMPLEMENTED)
	#define USE_MemPoolAppendUsedBlockToPool
	#define EXT_MemPoolAppendUsedBlockToPool
	#define GET_MemPoolAppendUsedBlockToPool(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolAppendUsedBlockToPool(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolAppendUsedBlockToPool  FALSE
	#define EXP_MemPoolAppendUsedBlockToPool  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolAppendUsedBlockToPool
	#define EXT_MemPoolAppendUsedBlockToPool
	#define GET_MemPoolAppendUsedBlockToPool(fl)  CAL_CMGETAPI( "MemPoolAppendUsedBlockToPool" ) 
	#define CAL_MemPoolAppendUsedBlockToPool  MemPoolAppendUsedBlockToPool
	#define CHK_MemPoolAppendUsedBlockToPool  TRUE
	#define EXP_MemPoolAppendUsedBlockToPool  CAL_CMEXPAPI( "MemPoolAppendUsedBlockToPool" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolAppendUsedBlockToPool
	#define EXT_MemPoolAppendUsedBlockToPool
	#define GET_MemPoolAppendUsedBlockToPool(fl)  CAL_CMGETAPI( "MemPoolAppendUsedBlockToPool" ) 
	#define CAL_MemPoolAppendUsedBlockToPool  MemPoolAppendUsedBlockToPool
	#define CHK_MemPoolAppendUsedBlockToPool  TRUE
	#define EXP_MemPoolAppendUsedBlockToPool  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolAppendUsedBlockToPool", (RTS_UINTPTR)MemPoolAppendUsedBlockToPool, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolAppendUsedBlockToPool
	#define EXT_CmpMemPoolMemPoolAppendUsedBlockToPool
	#define GET_CmpMemPoolMemPoolAppendUsedBlockToPool  ERR_OK
	#define CAL_CmpMemPoolMemPoolAppendUsedBlockToPool pICmpMemPool->IMemPoolAppendUsedBlockToPool
	#define CHK_CmpMemPoolMemPoolAppendUsedBlockToPool (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolAppendUsedBlockToPool  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolAppendUsedBlockToPool
	#define EXT_MemPoolAppendUsedBlockToPool
	#define GET_MemPoolAppendUsedBlockToPool(fl)  CAL_CMGETAPI( "MemPoolAppendUsedBlockToPool" ) 
	#define CAL_MemPoolAppendUsedBlockToPool pICmpMemPool->IMemPoolAppendUsedBlockToPool
	#define CHK_MemPoolAppendUsedBlockToPool (pICmpMemPool != NULL)
	#define EXP_MemPoolAppendUsedBlockToPool  CAL_CMEXPAPI( "MemPoolAppendUsedBlockToPool" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolAppendUsedBlockToPool  PFMEMPOOLAPPENDUSEDBLOCKTOPOOL pfMemPoolAppendUsedBlockToPool;
	#define EXT_MemPoolAppendUsedBlockToPool  extern PFMEMPOOLAPPENDUSEDBLOCKTOPOOL pfMemPoolAppendUsedBlockToPool;
	#define GET_MemPoolAppendUsedBlockToPool(fl)  s_pfCMGetAPI2( "MemPoolAppendUsedBlockToPool", (RTS_VOID_FCTPTR *)&pfMemPoolAppendUsedBlockToPool, (fl), 0, 0)
	#define CAL_MemPoolAppendUsedBlockToPool  pfMemPoolAppendUsedBlockToPool
	#define CHK_MemPoolAppendUsedBlockToPool  (pfMemPoolAppendUsedBlockToPool != NULL)
	#define EXP_MemPoolAppendUsedBlockToPool  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolAppendUsedBlockToPool", (RTS_UINTPTR)MemPoolAppendUsedBlockToPool, 0, 0) 
#endif




/**
 * <description>
 *	Remove used block from the specified pool. Now, the block is removed from the chain list of used blocks.
 * </description>
 * <param name="pBlock" type="IN">Pointer to the memory block</param>
 * <param name="hPool" type="IN">Handle to the pool</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL MemPoolRemoveUsedBlockFromPool(void* pBlock, RTS_HANDLE hPool);
typedef RTS_RESULT (CDECL * PFMEMPOOLREMOVEUSEDBLOCKFROMPOOL) (void* pBlock, RTS_HANDLE hPool);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLREMOVEUSEDBLOCKFROMPOOL_NOTIMPLEMENTED)
	#define USE_MemPoolRemoveUsedBlockFromPool
	#define EXT_MemPoolRemoveUsedBlockFromPool
	#define GET_MemPoolRemoveUsedBlockFromPool(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolRemoveUsedBlockFromPool(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolRemoveUsedBlockFromPool  FALSE
	#define EXP_MemPoolRemoveUsedBlockFromPool  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolRemoveUsedBlockFromPool
	#define EXT_MemPoolRemoveUsedBlockFromPool
	#define GET_MemPoolRemoveUsedBlockFromPool(fl)  CAL_CMGETAPI( "MemPoolRemoveUsedBlockFromPool" ) 
	#define CAL_MemPoolRemoveUsedBlockFromPool  MemPoolRemoveUsedBlockFromPool
	#define CHK_MemPoolRemoveUsedBlockFromPool  TRUE
	#define EXP_MemPoolRemoveUsedBlockFromPool  CAL_CMEXPAPI( "MemPoolRemoveUsedBlockFromPool" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolRemoveUsedBlockFromPool
	#define EXT_MemPoolRemoveUsedBlockFromPool
	#define GET_MemPoolRemoveUsedBlockFromPool(fl)  CAL_CMGETAPI( "MemPoolRemoveUsedBlockFromPool" ) 
	#define CAL_MemPoolRemoveUsedBlockFromPool  MemPoolRemoveUsedBlockFromPool
	#define CHK_MemPoolRemoveUsedBlockFromPool  TRUE
	#define EXP_MemPoolRemoveUsedBlockFromPool  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolRemoveUsedBlockFromPool", (RTS_UINTPTR)MemPoolRemoveUsedBlockFromPool, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolRemoveUsedBlockFromPool
	#define EXT_CmpMemPoolMemPoolRemoveUsedBlockFromPool
	#define GET_CmpMemPoolMemPoolRemoveUsedBlockFromPool  ERR_OK
	#define CAL_CmpMemPoolMemPoolRemoveUsedBlockFromPool pICmpMemPool->IMemPoolRemoveUsedBlockFromPool
	#define CHK_CmpMemPoolMemPoolRemoveUsedBlockFromPool (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolRemoveUsedBlockFromPool  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolRemoveUsedBlockFromPool
	#define EXT_MemPoolRemoveUsedBlockFromPool
	#define GET_MemPoolRemoveUsedBlockFromPool(fl)  CAL_CMGETAPI( "MemPoolRemoveUsedBlockFromPool" ) 
	#define CAL_MemPoolRemoveUsedBlockFromPool pICmpMemPool->IMemPoolRemoveUsedBlockFromPool
	#define CHK_MemPoolRemoveUsedBlockFromPool (pICmpMemPool != NULL)
	#define EXP_MemPoolRemoveUsedBlockFromPool  CAL_CMEXPAPI( "MemPoolRemoveUsedBlockFromPool" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolRemoveUsedBlockFromPool  PFMEMPOOLREMOVEUSEDBLOCKFROMPOOL pfMemPoolRemoveUsedBlockFromPool;
	#define EXT_MemPoolRemoveUsedBlockFromPool  extern PFMEMPOOLREMOVEUSEDBLOCKFROMPOOL pfMemPoolRemoveUsedBlockFromPool;
	#define GET_MemPoolRemoveUsedBlockFromPool(fl)  s_pfCMGetAPI2( "MemPoolRemoveUsedBlockFromPool", (RTS_VOID_FCTPTR *)&pfMemPoolRemoveUsedBlockFromPool, (fl), 0, 0)
	#define CAL_MemPoolRemoveUsedBlockFromPool  pfMemPoolRemoveUsedBlockFromPool
	#define CHK_MemPoolRemoveUsedBlockFromPool  (pfMemPoolRemoveUsedBlockFromPool != NULL)
	#define EXP_MemPoolRemoveUsedBlockFromPool  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolRemoveUsedBlockFromPool", (RTS_UINTPTR)MemPoolRemoveUsedBlockFromPool, 0, 0) 
#endif




/**
 * <description>
 *	Lock the access to a pool to be threadsafe.
 * </description>
 * <param name="pBlock" type="IN">Pointer to the memory block</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL MemPoolLockBlock(void* pBlock);
typedef RTS_RESULT (CDECL * PFMEMPOOLLOCKBLOCK) (void* pBlock);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLLOCKBLOCK_NOTIMPLEMENTED)
	#define USE_MemPoolLockBlock
	#define EXT_MemPoolLockBlock
	#define GET_MemPoolLockBlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolLockBlock(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolLockBlock  FALSE
	#define EXP_MemPoolLockBlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolLockBlock
	#define EXT_MemPoolLockBlock
	#define GET_MemPoolLockBlock(fl)  CAL_CMGETAPI( "MemPoolLockBlock" ) 
	#define CAL_MemPoolLockBlock  MemPoolLockBlock
	#define CHK_MemPoolLockBlock  TRUE
	#define EXP_MemPoolLockBlock  CAL_CMEXPAPI( "MemPoolLockBlock" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolLockBlock
	#define EXT_MemPoolLockBlock
	#define GET_MemPoolLockBlock(fl)  CAL_CMGETAPI( "MemPoolLockBlock" ) 
	#define CAL_MemPoolLockBlock  MemPoolLockBlock
	#define CHK_MemPoolLockBlock  TRUE
	#define EXP_MemPoolLockBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolLockBlock", (RTS_UINTPTR)MemPoolLockBlock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolLockBlock
	#define EXT_CmpMemPoolMemPoolLockBlock
	#define GET_CmpMemPoolMemPoolLockBlock  ERR_OK
	#define CAL_CmpMemPoolMemPoolLockBlock pICmpMemPool->IMemPoolLockBlock
	#define CHK_CmpMemPoolMemPoolLockBlock (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolLockBlock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolLockBlock
	#define EXT_MemPoolLockBlock
	#define GET_MemPoolLockBlock(fl)  CAL_CMGETAPI( "MemPoolLockBlock" ) 
	#define CAL_MemPoolLockBlock pICmpMemPool->IMemPoolLockBlock
	#define CHK_MemPoolLockBlock (pICmpMemPool != NULL)
	#define EXP_MemPoolLockBlock  CAL_CMEXPAPI( "MemPoolLockBlock" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolLockBlock  PFMEMPOOLLOCKBLOCK pfMemPoolLockBlock;
	#define EXT_MemPoolLockBlock  extern PFMEMPOOLLOCKBLOCK pfMemPoolLockBlock;
	#define GET_MemPoolLockBlock(fl)  s_pfCMGetAPI2( "MemPoolLockBlock", (RTS_VOID_FCTPTR *)&pfMemPoolLockBlock, (fl), 0, 0)
	#define CAL_MemPoolLockBlock  pfMemPoolLockBlock
	#define CHK_MemPoolLockBlock  (pfMemPoolLockBlock != NULL)
	#define EXP_MemPoolLockBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolLockBlock", (RTS_UINTPTR)MemPoolLockBlock, 0, 0) 
#endif




/**
 * <description>
 *	Unlock the access to a pool.
 * </description>
 * <param name="pBlock" type="IN">Pointer to the memory block</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL MemPoolUnlockBlock(void* pBlock);
typedef RTS_RESULT (CDECL * PFMEMPOOLUNLOCKBLOCK) (void* pBlock);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLUNLOCKBLOCK_NOTIMPLEMENTED)
	#define USE_MemPoolUnlockBlock
	#define EXT_MemPoolUnlockBlock
	#define GET_MemPoolUnlockBlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolUnlockBlock(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolUnlockBlock  FALSE
	#define EXP_MemPoolUnlockBlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolUnlockBlock
	#define EXT_MemPoolUnlockBlock
	#define GET_MemPoolUnlockBlock(fl)  CAL_CMGETAPI( "MemPoolUnlockBlock" ) 
	#define CAL_MemPoolUnlockBlock  MemPoolUnlockBlock
	#define CHK_MemPoolUnlockBlock  TRUE
	#define EXP_MemPoolUnlockBlock  CAL_CMEXPAPI( "MemPoolUnlockBlock" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolUnlockBlock
	#define EXT_MemPoolUnlockBlock
	#define GET_MemPoolUnlockBlock(fl)  CAL_CMGETAPI( "MemPoolUnlockBlock" ) 
	#define CAL_MemPoolUnlockBlock  MemPoolUnlockBlock
	#define CHK_MemPoolUnlockBlock  TRUE
	#define EXP_MemPoolUnlockBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolUnlockBlock", (RTS_UINTPTR)MemPoolUnlockBlock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolUnlockBlock
	#define EXT_CmpMemPoolMemPoolUnlockBlock
	#define GET_CmpMemPoolMemPoolUnlockBlock  ERR_OK
	#define CAL_CmpMemPoolMemPoolUnlockBlock pICmpMemPool->IMemPoolUnlockBlock
	#define CHK_CmpMemPoolMemPoolUnlockBlock (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolUnlockBlock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolUnlockBlock
	#define EXT_MemPoolUnlockBlock
	#define GET_MemPoolUnlockBlock(fl)  CAL_CMGETAPI( "MemPoolUnlockBlock" ) 
	#define CAL_MemPoolUnlockBlock pICmpMemPool->IMemPoolUnlockBlock
	#define CHK_MemPoolUnlockBlock (pICmpMemPool != NULL)
	#define EXP_MemPoolUnlockBlock  CAL_CMEXPAPI( "MemPoolUnlockBlock" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolUnlockBlock  PFMEMPOOLUNLOCKBLOCK pfMemPoolUnlockBlock;
	#define EXT_MemPoolUnlockBlock  extern PFMEMPOOLUNLOCKBLOCK pfMemPoolUnlockBlock;
	#define GET_MemPoolUnlockBlock(fl)  s_pfCMGetAPI2( "MemPoolUnlockBlock", (RTS_VOID_FCTPTR *)&pfMemPoolUnlockBlock, (fl), 0, 0)
	#define CAL_MemPoolUnlockBlock  pfMemPoolUnlockBlock
	#define CHK_MemPoolUnlockBlock  (pfMemPoolUnlockBlock != NULL)
	#define EXP_MemPoolUnlockBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolUnlockBlock", (RTS_UINTPTR)MemPoolUnlockBlock, 0, 0) 
#endif




/**
 * <description>
 *	Lock the access to the complete pool. SIL2 Implementation is using INT Locks.
 * </description>
 * <param name="hMemPool" type="IN" range="[VALID_MEMPOOLHANDLE,NULL]">Handle to the memory pool</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Pool was sucessfully locked</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Parameter is wrong</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Pool could not be locked, SysInt or SysSem had problems</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">SysInt or SysSem are not implemented</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">Lock cannot be done before CH_INIT_SYSTEM, not relevant for SIL2</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL MemPoolLock(RTS_HANDLE hMemPool);
typedef RTS_RESULT (CDECL * PFMEMPOOLLOCK) (RTS_HANDLE hMemPool);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLLOCK_NOTIMPLEMENTED)
	#define USE_MemPoolLock
	#define EXT_MemPoolLock
	#define GET_MemPoolLock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolLock(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolLock  FALSE
	#define EXP_MemPoolLock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolLock
	#define EXT_MemPoolLock
	#define GET_MemPoolLock(fl)  CAL_CMGETAPI( "MemPoolLock" ) 
	#define CAL_MemPoolLock  MemPoolLock
	#define CHK_MemPoolLock  TRUE
	#define EXP_MemPoolLock  CAL_CMEXPAPI( "MemPoolLock" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolLock
	#define EXT_MemPoolLock
	#define GET_MemPoolLock(fl)  CAL_CMGETAPI( "MemPoolLock" ) 
	#define CAL_MemPoolLock  MemPoolLock
	#define CHK_MemPoolLock  TRUE
	#define EXP_MemPoolLock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolLock", (RTS_UINTPTR)MemPoolLock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolLock
	#define EXT_CmpMemPoolMemPoolLock
	#define GET_CmpMemPoolMemPoolLock  ERR_OK
	#define CAL_CmpMemPoolMemPoolLock pICmpMemPool->IMemPoolLock
	#define CHK_CmpMemPoolMemPoolLock (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolLock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolLock
	#define EXT_MemPoolLock
	#define GET_MemPoolLock(fl)  CAL_CMGETAPI( "MemPoolLock" ) 
	#define CAL_MemPoolLock pICmpMemPool->IMemPoolLock
	#define CHK_MemPoolLock (pICmpMemPool != NULL)
	#define EXP_MemPoolLock  CAL_CMEXPAPI( "MemPoolLock" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolLock  PFMEMPOOLLOCK pfMemPoolLock;
	#define EXT_MemPoolLock  extern PFMEMPOOLLOCK pfMemPoolLock;
	#define GET_MemPoolLock(fl)  s_pfCMGetAPI2( "MemPoolLock", (RTS_VOID_FCTPTR *)&pfMemPoolLock, (fl), 0, 0)
	#define CAL_MemPoolLock  pfMemPoolLock
	#define CHK_MemPoolLock  (pfMemPoolLock != NULL)
	#define EXP_MemPoolLock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolLock", (RTS_UINTPTR)MemPoolLock, 0, 0) 
#endif




/**
 * <description>
 *	Unlock the access to the complete pool. SIL2 Implementation is using INT Locks.
 * </description>
 * <param name="hMemPool" type="IN" range="[VALID_MEMPOOLHANDLE,NULL]">Handle to the memory pool</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Pool was sucessfully unlocked</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Parameter is wrong</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Pool could not be unlocked, SysInt or SysSem had problems</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">SysInt or SysSem are not implemented</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">Unlock cannot be done before CH_INIT_SYSTEM, not relevant for SIL2</errorcode>
 * <result>Error code</result>
 */
RTS_RESULT CDECL MemPoolUnlock(RTS_HANDLE hMemPool);
typedef RTS_RESULT (CDECL * PFMEMPOOLUNLOCK) (RTS_HANDLE hMemPool);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLUNLOCK_NOTIMPLEMENTED)
	#define USE_MemPoolUnlock
	#define EXT_MemPoolUnlock
	#define GET_MemPoolUnlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolUnlock(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolUnlock  FALSE
	#define EXP_MemPoolUnlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolUnlock
	#define EXT_MemPoolUnlock
	#define GET_MemPoolUnlock(fl)  CAL_CMGETAPI( "MemPoolUnlock" ) 
	#define CAL_MemPoolUnlock  MemPoolUnlock
	#define CHK_MemPoolUnlock  TRUE
	#define EXP_MemPoolUnlock  CAL_CMEXPAPI( "MemPoolUnlock" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolUnlock
	#define EXT_MemPoolUnlock
	#define GET_MemPoolUnlock(fl)  CAL_CMGETAPI( "MemPoolUnlock" ) 
	#define CAL_MemPoolUnlock  MemPoolUnlock
	#define CHK_MemPoolUnlock  TRUE
	#define EXP_MemPoolUnlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolUnlock", (RTS_UINTPTR)MemPoolUnlock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolUnlock
	#define EXT_CmpMemPoolMemPoolUnlock
	#define GET_CmpMemPoolMemPoolUnlock  ERR_OK
	#define CAL_CmpMemPoolMemPoolUnlock pICmpMemPool->IMemPoolUnlock
	#define CHK_CmpMemPoolMemPoolUnlock (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolUnlock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolUnlock
	#define EXT_MemPoolUnlock
	#define GET_MemPoolUnlock(fl)  CAL_CMGETAPI( "MemPoolUnlock" ) 
	#define CAL_MemPoolUnlock pICmpMemPool->IMemPoolUnlock
	#define CHK_MemPoolUnlock (pICmpMemPool != NULL)
	#define EXP_MemPoolUnlock  CAL_CMEXPAPI( "MemPoolUnlock" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolUnlock  PFMEMPOOLUNLOCK pfMemPoolUnlock;
	#define EXT_MemPoolUnlock  extern PFMEMPOOLUNLOCK pfMemPoolUnlock;
	#define GET_MemPoolUnlock(fl)  s_pfCMGetAPI2( "MemPoolUnlock", (RTS_VOID_FCTPTR *)&pfMemPoolUnlock, (fl), 0, 0)
	#define CAL_MemPoolUnlock  pfMemPoolUnlock
	#define CHK_MemPoolUnlock  (pfMemPoolUnlock != NULL)
	#define EXP_MemPoolUnlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolUnlock", (RTS_UINTPTR)MemPoolUnlock, 0, 0) 
#endif




/**
 * <description>
 *	Find a block specified by a value, that is stored in the block.
 * </description>
 * <param name="hMemPool" type="IN">Handle to the memory pool</param>
 * <param name="ulOffset" type="IN">Byte offset of the value in the block to find</param>
 * <param name="ulSize" type="IN">Size in bytes of the value to find in the block</param>
 * <param name="pToFind" type="IN">Pointer to the value to find in the block</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the memory block</result>
 */
void * CDECL MemPoolFindBlock(RTS_HANDLE hMemPool, RTS_SIZE ulOffset, RTS_SIZE ulSize, void *pToFind, RTS_RESULT *pResult);
typedef void * (CDECL * PFMEMPOOLFINDBLOCK) (RTS_HANDLE hMemPool, RTS_SIZE ulOffset, RTS_SIZE ulSize, void *pToFind, RTS_RESULT *pResult);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLFINDBLOCK_NOTIMPLEMENTED)
	#define USE_MemPoolFindBlock
	#define EXT_MemPoolFindBlock
	#define GET_MemPoolFindBlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolFindBlock(p0,p1,p2,p3,p4)  (void *)(RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolFindBlock  FALSE
	#define EXP_MemPoolFindBlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolFindBlock
	#define EXT_MemPoolFindBlock
	#define GET_MemPoolFindBlock(fl)  CAL_CMGETAPI( "MemPoolFindBlock" ) 
	#define CAL_MemPoolFindBlock  MemPoolFindBlock
	#define CHK_MemPoolFindBlock  TRUE
	#define EXP_MemPoolFindBlock  CAL_CMEXPAPI( "MemPoolFindBlock" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolFindBlock
	#define EXT_MemPoolFindBlock
	#define GET_MemPoolFindBlock(fl)  CAL_CMGETAPI( "MemPoolFindBlock" ) 
	#define CAL_MemPoolFindBlock  MemPoolFindBlock
	#define CHK_MemPoolFindBlock  TRUE
	#define EXP_MemPoolFindBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolFindBlock", (RTS_UINTPTR)MemPoolFindBlock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolFindBlock
	#define EXT_CmpMemPoolMemPoolFindBlock
	#define GET_CmpMemPoolMemPoolFindBlock  ERR_OK
	#define CAL_CmpMemPoolMemPoolFindBlock pICmpMemPool->IMemPoolFindBlock
	#define CHK_CmpMemPoolMemPoolFindBlock (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolFindBlock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolFindBlock
	#define EXT_MemPoolFindBlock
	#define GET_MemPoolFindBlock(fl)  CAL_CMGETAPI( "MemPoolFindBlock" ) 
	#define CAL_MemPoolFindBlock pICmpMemPool->IMemPoolFindBlock
	#define CHK_MemPoolFindBlock (pICmpMemPool != NULL)
	#define EXP_MemPoolFindBlock  CAL_CMEXPAPI( "MemPoolFindBlock" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolFindBlock  PFMEMPOOLFINDBLOCK pfMemPoolFindBlock;
	#define EXT_MemPoolFindBlock  extern PFMEMPOOLFINDBLOCK pfMemPoolFindBlock;
	#define GET_MemPoolFindBlock(fl)  s_pfCMGetAPI2( "MemPoolFindBlock", (RTS_VOID_FCTPTR *)&pfMemPoolFindBlock, (fl), 0, 0)
	#define CAL_MemPoolFindBlock  pfMemPoolFindBlock
	#define CHK_MemPoolFindBlock  (pfMemPoolFindBlock != NULL)
	#define EXP_MemPoolFindBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolFindBlock", (RTS_UINTPTR)MemPoolFindBlock, 0, 0) 
#endif




/**
 * <description>
 *	Check a pool memory block, if it is still valid and is not released.
 *	NOTE:
 *	If the check is successful, a lock is done on this pool!!! So you have to unlock this reference at the end of the usage with MemPoolUnlock()!
 * </description>
 * <param name="hMemPool" type="IN">Handle to the memory pool</param>
 * <param name="pBlock" type="IN">Pointer to the memory block</param>
 * <result>Error code</result>
 */
RTS_RESULT CDECL MemPoolIsValidBlock(RTS_HANDLE hMemPool, void *pBlock);
typedef RTS_RESULT (CDECL * PFMEMPOOLISVALIDBLOCK) (RTS_HANDLE hMemPool, void *pBlock);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLISVALIDBLOCK_NOTIMPLEMENTED)
	#define USE_MemPoolIsValidBlock
	#define EXT_MemPoolIsValidBlock
	#define GET_MemPoolIsValidBlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolIsValidBlock(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolIsValidBlock  FALSE
	#define EXP_MemPoolIsValidBlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolIsValidBlock
	#define EXT_MemPoolIsValidBlock
	#define GET_MemPoolIsValidBlock(fl)  CAL_CMGETAPI( "MemPoolIsValidBlock" ) 
	#define CAL_MemPoolIsValidBlock  MemPoolIsValidBlock
	#define CHK_MemPoolIsValidBlock  TRUE
	#define EXP_MemPoolIsValidBlock  CAL_CMEXPAPI( "MemPoolIsValidBlock" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolIsValidBlock
	#define EXT_MemPoolIsValidBlock
	#define GET_MemPoolIsValidBlock(fl)  CAL_CMGETAPI( "MemPoolIsValidBlock" ) 
	#define CAL_MemPoolIsValidBlock  MemPoolIsValidBlock
	#define CHK_MemPoolIsValidBlock  TRUE
	#define EXP_MemPoolIsValidBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolIsValidBlock", (RTS_UINTPTR)MemPoolIsValidBlock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolIsValidBlock
	#define EXT_CmpMemPoolMemPoolIsValidBlock
	#define GET_CmpMemPoolMemPoolIsValidBlock  ERR_OK
	#define CAL_CmpMemPoolMemPoolIsValidBlock pICmpMemPool->IMemPoolIsValidBlock
	#define CHK_CmpMemPoolMemPoolIsValidBlock (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolIsValidBlock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolIsValidBlock
	#define EXT_MemPoolIsValidBlock
	#define GET_MemPoolIsValidBlock(fl)  CAL_CMGETAPI( "MemPoolIsValidBlock" ) 
	#define CAL_MemPoolIsValidBlock pICmpMemPool->IMemPoolIsValidBlock
	#define CHK_MemPoolIsValidBlock (pICmpMemPool != NULL)
	#define EXP_MemPoolIsValidBlock  CAL_CMEXPAPI( "MemPoolIsValidBlock" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolIsValidBlock  PFMEMPOOLISVALIDBLOCK pfMemPoolIsValidBlock;
	#define EXT_MemPoolIsValidBlock  extern PFMEMPOOLISVALIDBLOCK pfMemPoolIsValidBlock;
	#define GET_MemPoolIsValidBlock(fl)  s_pfCMGetAPI2( "MemPoolIsValidBlock", (RTS_VOID_FCTPTR *)&pfMemPoolIsValidBlock, (fl), 0, 0)
	#define CAL_MemPoolIsValidBlock  pfMemPoolIsValidBlock
	#define CHK_MemPoolIsValidBlock  (pfMemPoolIsValidBlock != NULL)
	#define EXP_MemPoolIsValidBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolIsValidBlock", (RTS_UINTPTR)MemPoolIsValidBlock, 0, 0) 
#endif




/**
 * <description>
 *	Get the first memory block out of the pool. Can be used for explicite iteration routines.
 * </description>
 * <param name="hMemPool" type="IN">Handle to the memory pool</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to first memory block</result>
 */
void* CDECL MemPoolGetFirstBlock(RTS_HANDLE hMemPool, RTS_RESULT *pResult);
typedef void* (CDECL * PFMEMPOOLGETFIRSTBLOCK) (RTS_HANDLE hMemPool, RTS_RESULT *pResult);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLGETFIRSTBLOCK_NOTIMPLEMENTED)
	#define USE_MemPoolGetFirstBlock
	#define EXT_MemPoolGetFirstBlock
	#define GET_MemPoolGetFirstBlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolGetFirstBlock(p0,p1)  (void*)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolGetFirstBlock  FALSE
	#define EXP_MemPoolGetFirstBlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolGetFirstBlock
	#define EXT_MemPoolGetFirstBlock
	#define GET_MemPoolGetFirstBlock(fl)  CAL_CMGETAPI( "MemPoolGetFirstBlock" ) 
	#define CAL_MemPoolGetFirstBlock  MemPoolGetFirstBlock
	#define CHK_MemPoolGetFirstBlock  TRUE
	#define EXP_MemPoolGetFirstBlock  CAL_CMEXPAPI( "MemPoolGetFirstBlock" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolGetFirstBlock
	#define EXT_MemPoolGetFirstBlock
	#define GET_MemPoolGetFirstBlock(fl)  CAL_CMGETAPI( "MemPoolGetFirstBlock" ) 
	#define CAL_MemPoolGetFirstBlock  MemPoolGetFirstBlock
	#define CHK_MemPoolGetFirstBlock  TRUE
	#define EXP_MemPoolGetFirstBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolGetFirstBlock", (RTS_UINTPTR)MemPoolGetFirstBlock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolGetFirstBlock
	#define EXT_CmpMemPoolMemPoolGetFirstBlock
	#define GET_CmpMemPoolMemPoolGetFirstBlock  ERR_OK
	#define CAL_CmpMemPoolMemPoolGetFirstBlock pICmpMemPool->IMemPoolGetFirstBlock
	#define CHK_CmpMemPoolMemPoolGetFirstBlock (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolGetFirstBlock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolGetFirstBlock
	#define EXT_MemPoolGetFirstBlock
	#define GET_MemPoolGetFirstBlock(fl)  CAL_CMGETAPI( "MemPoolGetFirstBlock" ) 
	#define CAL_MemPoolGetFirstBlock pICmpMemPool->IMemPoolGetFirstBlock
	#define CHK_MemPoolGetFirstBlock (pICmpMemPool != NULL)
	#define EXP_MemPoolGetFirstBlock  CAL_CMEXPAPI( "MemPoolGetFirstBlock" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolGetFirstBlock  PFMEMPOOLGETFIRSTBLOCK pfMemPoolGetFirstBlock;
	#define EXT_MemPoolGetFirstBlock  extern PFMEMPOOLGETFIRSTBLOCK pfMemPoolGetFirstBlock;
	#define GET_MemPoolGetFirstBlock(fl)  s_pfCMGetAPI2( "MemPoolGetFirstBlock", (RTS_VOID_FCTPTR *)&pfMemPoolGetFirstBlock, (fl), 0, 0)
	#define CAL_MemPoolGetFirstBlock  pfMemPoolGetFirstBlock
	#define CHK_MemPoolGetFirstBlock  (pfMemPoolGetFirstBlock != NULL)
	#define EXP_MemPoolGetFirstBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolGetFirstBlock", (RTS_UINTPTR)MemPoolGetFirstBlock, 0, 0) 
#endif




/**
 * <description>
 *	Get the next memory block out of the pool. Can be used for explicite iteration routines.
 * </description>
 * <param name="hMemPool" type="IN">Handle to the memory pool</param>
 * <param name="pPrevBlock" type="IN">Pointer to previous memory block</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to next memory block</result>
 */
void* CDECL MemPoolGetNextBlock(RTS_HANDLE hMemPool, void *pPrevBlock, RTS_RESULT *pResult);
typedef void* (CDECL * PFMEMPOOLGETNEXTBLOCK) (RTS_HANDLE hMemPool, void *pPrevBlock, RTS_RESULT *pResult);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(MEMPOOLGETNEXTBLOCK_NOTIMPLEMENTED)
	#define USE_MemPoolGetNextBlock
	#define EXT_MemPoolGetNextBlock
	#define GET_MemPoolGetNextBlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemPoolGetNextBlock(p0,p1,p2)  (void*)ERR_NOTIMPLEMENTED
	#define CHK_MemPoolGetNextBlock  FALSE
	#define EXP_MemPoolGetNextBlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemPoolGetNextBlock
	#define EXT_MemPoolGetNextBlock
	#define GET_MemPoolGetNextBlock(fl)  CAL_CMGETAPI( "MemPoolGetNextBlock" ) 
	#define CAL_MemPoolGetNextBlock  MemPoolGetNextBlock
	#define CHK_MemPoolGetNextBlock  TRUE
	#define EXP_MemPoolGetNextBlock  CAL_CMEXPAPI( "MemPoolGetNextBlock" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_MemPoolGetNextBlock
	#define EXT_MemPoolGetNextBlock
	#define GET_MemPoolGetNextBlock(fl)  CAL_CMGETAPI( "MemPoolGetNextBlock" ) 
	#define CAL_MemPoolGetNextBlock  MemPoolGetNextBlock
	#define CHK_MemPoolGetNextBlock  TRUE
	#define EXP_MemPoolGetNextBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolGetNextBlock", (RTS_UINTPTR)MemPoolGetNextBlock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolMemPoolGetNextBlock
	#define EXT_CmpMemPoolMemPoolGetNextBlock
	#define GET_CmpMemPoolMemPoolGetNextBlock  ERR_OK
	#define CAL_CmpMemPoolMemPoolGetNextBlock pICmpMemPool->IMemPoolGetNextBlock
	#define CHK_CmpMemPoolMemPoolGetNextBlock (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolMemPoolGetNextBlock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemPoolGetNextBlock
	#define EXT_MemPoolGetNextBlock
	#define GET_MemPoolGetNextBlock(fl)  CAL_CMGETAPI( "MemPoolGetNextBlock" ) 
	#define CAL_MemPoolGetNextBlock pICmpMemPool->IMemPoolGetNextBlock
	#define CHK_MemPoolGetNextBlock (pICmpMemPool != NULL)
	#define EXP_MemPoolGetNextBlock  CAL_CMEXPAPI( "MemPoolGetNextBlock" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemPoolGetNextBlock  PFMEMPOOLGETNEXTBLOCK pfMemPoolGetNextBlock;
	#define EXT_MemPoolGetNextBlock  extern PFMEMPOOLGETNEXTBLOCK pfMemPoolGetNextBlock;
	#define GET_MemPoolGetNextBlock(fl)  s_pfCMGetAPI2( "MemPoolGetNextBlock", (RTS_VOID_FCTPTR *)&pfMemPoolGetNextBlock, (fl), 0, 0)
	#define CAL_MemPoolGetNextBlock  pfMemPoolGetNextBlock
	#define CHK_MemPoolGetNextBlock  (pfMemPoolGetNextBlock != NULL)
	#define EXP_MemPoolGetNextBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemPoolGetNextBlock", (RTS_UINTPTR)MemPoolGetNextBlock, 0, 0) 
#endif




/******************************************************************************/
/*								Allocator of memory blocks of fixed size										*/
/******************************************************************************/
/**
 * <description>
 *	Initializes a pool for allocating objects of fixed size
 * </description>
 * <param name="pPool" type="IN">Pointer to a pool object</param>
 * <param name="pRegion" type="IN">Pointer to a region of memory that will be used for allocation</param>
 * <param name="block_size" type="IN">Size (in bytes) of a memory block</param>
 * <param name="blocks_number" type="IN">Number of blocks that should be located in a contiguous chunk</param>   
 * <result>Error code</result>
 */
RTS_RESULT CDECL FixedBlocksPoolInit(RTS_FIXED_BLOCKS_POOL* pPool, RTS_MEM_REGION* pRegion, RTS_SIZE block_size, RTS_SIZE blocks_number);
typedef RTS_RESULT (CDECL * PFFIXEDBLOCKSPOOLINIT) (RTS_FIXED_BLOCKS_POOL* pPool, RTS_MEM_REGION* pRegion, RTS_SIZE block_size, RTS_SIZE blocks_number);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(FIXEDBLOCKSPOOLINIT_NOTIMPLEMENTED)
	#define USE_FixedBlocksPoolInit
	#define EXT_FixedBlocksPoolInit
	#define GET_FixedBlocksPoolInit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_FixedBlocksPoolInit(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_FixedBlocksPoolInit  FALSE
	#define EXP_FixedBlocksPoolInit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_FixedBlocksPoolInit
	#define EXT_FixedBlocksPoolInit
	#define GET_FixedBlocksPoolInit(fl)  CAL_CMGETAPI( "FixedBlocksPoolInit" ) 
	#define CAL_FixedBlocksPoolInit  FixedBlocksPoolInit
	#define CHK_FixedBlocksPoolInit  TRUE
	#define EXP_FixedBlocksPoolInit  CAL_CMEXPAPI( "FixedBlocksPoolInit" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_FixedBlocksPoolInit
	#define EXT_FixedBlocksPoolInit
	#define GET_FixedBlocksPoolInit(fl)  CAL_CMGETAPI( "FixedBlocksPoolInit" ) 
	#define CAL_FixedBlocksPoolInit  FixedBlocksPoolInit
	#define CHK_FixedBlocksPoolInit  TRUE
	#define EXP_FixedBlocksPoolInit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FixedBlocksPoolInit", (RTS_UINTPTR)FixedBlocksPoolInit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolFixedBlocksPoolInit
	#define EXT_CmpMemPoolFixedBlocksPoolInit
	#define GET_CmpMemPoolFixedBlocksPoolInit  ERR_OK
	#define CAL_CmpMemPoolFixedBlocksPoolInit pICmpMemPool->IFixedBlocksPoolInit
	#define CHK_CmpMemPoolFixedBlocksPoolInit (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolFixedBlocksPoolInit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_FixedBlocksPoolInit
	#define EXT_FixedBlocksPoolInit
	#define GET_FixedBlocksPoolInit(fl)  CAL_CMGETAPI( "FixedBlocksPoolInit" ) 
	#define CAL_FixedBlocksPoolInit pICmpMemPool->IFixedBlocksPoolInit
	#define CHK_FixedBlocksPoolInit (pICmpMemPool != NULL)
	#define EXP_FixedBlocksPoolInit  CAL_CMEXPAPI( "FixedBlocksPoolInit" ) 
#else /* DYNAMIC_LINK */
	#define USE_FixedBlocksPoolInit  PFFIXEDBLOCKSPOOLINIT pfFixedBlocksPoolInit;
	#define EXT_FixedBlocksPoolInit  extern PFFIXEDBLOCKSPOOLINIT pfFixedBlocksPoolInit;
	#define GET_FixedBlocksPoolInit(fl)  s_pfCMGetAPI2( "FixedBlocksPoolInit", (RTS_VOID_FCTPTR *)&pfFixedBlocksPoolInit, (fl), 0, 0)
	#define CAL_FixedBlocksPoolInit  pfFixedBlocksPoolInit
	#define CHK_FixedBlocksPoolInit  (pfFixedBlocksPoolInit != NULL)
	#define EXP_FixedBlocksPoolInit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FixedBlocksPoolInit", (RTS_UINTPTR)FixedBlocksPoolInit, 0, 0) 
#endif




/**
 * <description>
 *	Allocates a memory block out of the pool 
 * </description>
 * <param name="pPool" type="IN">Pointer to a pool object</param>
 * <param name="size" type="IN">Requested size of memory to be allocated. Should be less than the pPool block size</param>
 * <param name="pResult" type="OUT">Pointer to an error code</param>
 * <result>Pointer to the allocated block of memory</result>
 */
void* CDECL FixedBlocksPoolAlloc(RTS_FIXED_BLOCKS_POOL* pPool, RTS_SIZE size, RTS_RESULT* pResult);
typedef void* (CDECL * PFFIXEDBLOCKSPOOLALLOC) (RTS_FIXED_BLOCKS_POOL* pPool, RTS_SIZE size, RTS_RESULT* pResult);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(FIXEDBLOCKSPOOLALLOC_NOTIMPLEMENTED)
	#define USE_FixedBlocksPoolAlloc
	#define EXT_FixedBlocksPoolAlloc
	#define GET_FixedBlocksPoolAlloc(fl)  ERR_NOTIMPLEMENTED
	#define CAL_FixedBlocksPoolAlloc(p0,p1,p2)  (void*)ERR_NOTIMPLEMENTED
	#define CHK_FixedBlocksPoolAlloc  FALSE
	#define EXP_FixedBlocksPoolAlloc  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_FixedBlocksPoolAlloc
	#define EXT_FixedBlocksPoolAlloc
	#define GET_FixedBlocksPoolAlloc(fl)  CAL_CMGETAPI( "FixedBlocksPoolAlloc" ) 
	#define CAL_FixedBlocksPoolAlloc  FixedBlocksPoolAlloc
	#define CHK_FixedBlocksPoolAlloc  TRUE
	#define EXP_FixedBlocksPoolAlloc  CAL_CMEXPAPI( "FixedBlocksPoolAlloc" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_FixedBlocksPoolAlloc
	#define EXT_FixedBlocksPoolAlloc
	#define GET_FixedBlocksPoolAlloc(fl)  CAL_CMGETAPI( "FixedBlocksPoolAlloc" ) 
	#define CAL_FixedBlocksPoolAlloc  FixedBlocksPoolAlloc
	#define CHK_FixedBlocksPoolAlloc  TRUE
	#define EXP_FixedBlocksPoolAlloc  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FixedBlocksPoolAlloc", (RTS_UINTPTR)FixedBlocksPoolAlloc, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolFixedBlocksPoolAlloc
	#define EXT_CmpMemPoolFixedBlocksPoolAlloc
	#define GET_CmpMemPoolFixedBlocksPoolAlloc  ERR_OK
	#define CAL_CmpMemPoolFixedBlocksPoolAlloc pICmpMemPool->IFixedBlocksPoolAlloc
	#define CHK_CmpMemPoolFixedBlocksPoolAlloc (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolFixedBlocksPoolAlloc  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_FixedBlocksPoolAlloc
	#define EXT_FixedBlocksPoolAlloc
	#define GET_FixedBlocksPoolAlloc(fl)  CAL_CMGETAPI( "FixedBlocksPoolAlloc" ) 
	#define CAL_FixedBlocksPoolAlloc pICmpMemPool->IFixedBlocksPoolAlloc
	#define CHK_FixedBlocksPoolAlloc (pICmpMemPool != NULL)
	#define EXP_FixedBlocksPoolAlloc  CAL_CMEXPAPI( "FixedBlocksPoolAlloc" ) 
#else /* DYNAMIC_LINK */
	#define USE_FixedBlocksPoolAlloc  PFFIXEDBLOCKSPOOLALLOC pfFixedBlocksPoolAlloc;
	#define EXT_FixedBlocksPoolAlloc  extern PFFIXEDBLOCKSPOOLALLOC pfFixedBlocksPoolAlloc;
	#define GET_FixedBlocksPoolAlloc(fl)  s_pfCMGetAPI2( "FixedBlocksPoolAlloc", (RTS_VOID_FCTPTR *)&pfFixedBlocksPoolAlloc, (fl), 0, 0)
	#define CAL_FixedBlocksPoolAlloc  pfFixedBlocksPoolAlloc
	#define CHK_FixedBlocksPoolAlloc  (pfFixedBlocksPoolAlloc != NULL)
	#define EXP_FixedBlocksPoolAlloc  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FixedBlocksPoolAlloc", (RTS_UINTPTR)FixedBlocksPoolAlloc, 0, 0) 
#endif




/**
 * <description>
 *	Puts a memory block back to the pool.
 * </description>
 * <param name="pPool" type="IN">Pointer to a pool object</param>
 * <param name="pMem" type="IN">Pointer to a memory block to be returned to the pool</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL FixedBlocksPoolFree(RTS_FIXED_BLOCKS_POOL* pPool, void* pMem);
typedef RTS_RESULT (CDECL * PFFIXEDBLOCKSPOOLFREE) (RTS_FIXED_BLOCKS_POOL* pPool, void* pMem);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(FIXEDBLOCKSPOOLFREE_NOTIMPLEMENTED)
	#define USE_FixedBlocksPoolFree
	#define EXT_FixedBlocksPoolFree
	#define GET_FixedBlocksPoolFree(fl)  ERR_NOTIMPLEMENTED
	#define CAL_FixedBlocksPoolFree(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_FixedBlocksPoolFree  FALSE
	#define EXP_FixedBlocksPoolFree  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_FixedBlocksPoolFree
	#define EXT_FixedBlocksPoolFree
	#define GET_FixedBlocksPoolFree(fl)  CAL_CMGETAPI( "FixedBlocksPoolFree" ) 
	#define CAL_FixedBlocksPoolFree  FixedBlocksPoolFree
	#define CHK_FixedBlocksPoolFree  TRUE
	#define EXP_FixedBlocksPoolFree  CAL_CMEXPAPI( "FixedBlocksPoolFree" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_FixedBlocksPoolFree
	#define EXT_FixedBlocksPoolFree
	#define GET_FixedBlocksPoolFree(fl)  CAL_CMGETAPI( "FixedBlocksPoolFree" ) 
	#define CAL_FixedBlocksPoolFree  FixedBlocksPoolFree
	#define CHK_FixedBlocksPoolFree  TRUE
	#define EXP_FixedBlocksPoolFree  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FixedBlocksPoolFree", (RTS_UINTPTR)FixedBlocksPoolFree, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolFixedBlocksPoolFree
	#define EXT_CmpMemPoolFixedBlocksPoolFree
	#define GET_CmpMemPoolFixedBlocksPoolFree  ERR_OK
	#define CAL_CmpMemPoolFixedBlocksPoolFree pICmpMemPool->IFixedBlocksPoolFree
	#define CHK_CmpMemPoolFixedBlocksPoolFree (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolFixedBlocksPoolFree  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_FixedBlocksPoolFree
	#define EXT_FixedBlocksPoolFree
	#define GET_FixedBlocksPoolFree(fl)  CAL_CMGETAPI( "FixedBlocksPoolFree" ) 
	#define CAL_FixedBlocksPoolFree pICmpMemPool->IFixedBlocksPoolFree
	#define CHK_FixedBlocksPoolFree (pICmpMemPool != NULL)
	#define EXP_FixedBlocksPoolFree  CAL_CMEXPAPI( "FixedBlocksPoolFree" ) 
#else /* DYNAMIC_LINK */
	#define USE_FixedBlocksPoolFree  PFFIXEDBLOCKSPOOLFREE pfFixedBlocksPoolFree;
	#define EXT_FixedBlocksPoolFree  extern PFFIXEDBLOCKSPOOLFREE pfFixedBlocksPoolFree;
	#define GET_FixedBlocksPoolFree(fl)  s_pfCMGetAPI2( "FixedBlocksPoolFree", (RTS_VOID_FCTPTR *)&pfFixedBlocksPoolFree, (fl), 0, 0)
	#define CAL_FixedBlocksPoolFree  pfFixedBlocksPoolFree
	#define CHK_FixedBlocksPoolFree  (pfFixedBlocksPoolFree != NULL)
	#define EXP_FixedBlocksPoolFree  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FixedBlocksPoolFree", (RTS_UINTPTR)FixedBlocksPoolFree, 0, 0) 
#endif




/**
 * <description>
 *	Puts all the previously allocated memory blocks back to the pool.
 * </description>
 * <param name="pPool" type="IN">Pointer to a pool object</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL FixedBlocksPoolReclaim(RTS_FIXED_BLOCKS_POOL* pPool);
typedef RTS_RESULT (CDECL * PFFIXEDBLOCKSPOOLRECLAIM) (RTS_FIXED_BLOCKS_POOL* pPool);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(FIXEDBLOCKSPOOLRECLAIM_NOTIMPLEMENTED)
	#define USE_FixedBlocksPoolReclaim
	#define EXT_FixedBlocksPoolReclaim
	#define GET_FixedBlocksPoolReclaim(fl)  ERR_NOTIMPLEMENTED
	#define CAL_FixedBlocksPoolReclaim(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_FixedBlocksPoolReclaim  FALSE
	#define EXP_FixedBlocksPoolReclaim  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_FixedBlocksPoolReclaim
	#define EXT_FixedBlocksPoolReclaim
	#define GET_FixedBlocksPoolReclaim(fl)  CAL_CMGETAPI( "FixedBlocksPoolReclaim" ) 
	#define CAL_FixedBlocksPoolReclaim  FixedBlocksPoolReclaim
	#define CHK_FixedBlocksPoolReclaim  TRUE
	#define EXP_FixedBlocksPoolReclaim  CAL_CMEXPAPI( "FixedBlocksPoolReclaim" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_FixedBlocksPoolReclaim
	#define EXT_FixedBlocksPoolReclaim
	#define GET_FixedBlocksPoolReclaim(fl)  CAL_CMGETAPI( "FixedBlocksPoolReclaim" ) 
	#define CAL_FixedBlocksPoolReclaim  FixedBlocksPoolReclaim
	#define CHK_FixedBlocksPoolReclaim  TRUE
	#define EXP_FixedBlocksPoolReclaim  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FixedBlocksPoolReclaim", (RTS_UINTPTR)FixedBlocksPoolReclaim, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolFixedBlocksPoolReclaim
	#define EXT_CmpMemPoolFixedBlocksPoolReclaim
	#define GET_CmpMemPoolFixedBlocksPoolReclaim  ERR_OK
	#define CAL_CmpMemPoolFixedBlocksPoolReclaim pICmpMemPool->IFixedBlocksPoolReclaim
	#define CHK_CmpMemPoolFixedBlocksPoolReclaim (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolFixedBlocksPoolReclaim  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_FixedBlocksPoolReclaim
	#define EXT_FixedBlocksPoolReclaim
	#define GET_FixedBlocksPoolReclaim(fl)  CAL_CMGETAPI( "FixedBlocksPoolReclaim" ) 
	#define CAL_FixedBlocksPoolReclaim pICmpMemPool->IFixedBlocksPoolReclaim
	#define CHK_FixedBlocksPoolReclaim (pICmpMemPool != NULL)
	#define EXP_FixedBlocksPoolReclaim  CAL_CMEXPAPI( "FixedBlocksPoolReclaim" ) 
#else /* DYNAMIC_LINK */
	#define USE_FixedBlocksPoolReclaim  PFFIXEDBLOCKSPOOLRECLAIM pfFixedBlocksPoolReclaim;
	#define EXT_FixedBlocksPoolReclaim  extern PFFIXEDBLOCKSPOOLRECLAIM pfFixedBlocksPoolReclaim;
	#define GET_FixedBlocksPoolReclaim(fl)  s_pfCMGetAPI2( "FixedBlocksPoolReclaim", (RTS_VOID_FCTPTR *)&pfFixedBlocksPoolReclaim, (fl), 0, 0)
	#define CAL_FixedBlocksPoolReclaim  pfFixedBlocksPoolReclaim
	#define CHK_FixedBlocksPoolReclaim  (pfFixedBlocksPoolReclaim != NULL)
	#define EXP_FixedBlocksPoolReclaim  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FixedBlocksPoolReclaim", (RTS_UINTPTR)FixedBlocksPoolReclaim, 0, 0) 
#endif




/**
 * <description>
 *	Destroys a pool object.
 * </description>
 * <param name="pPool" type="IN">Pointer to a pool object</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL FixedBlocksPoolDestroy(RTS_FIXED_BLOCKS_POOL* pPool);
typedef RTS_RESULT (CDECL * PFFIXEDBLOCKSPOOLDESTROY) (RTS_FIXED_BLOCKS_POOL* pPool);
#if defined(CMPMEMPOOL_NOTIMPLEMENTED) || defined(FIXEDBLOCKSPOOLDESTROY_NOTIMPLEMENTED)
	#define USE_FixedBlocksPoolDestroy
	#define EXT_FixedBlocksPoolDestroy
	#define GET_FixedBlocksPoolDestroy(fl)  ERR_NOTIMPLEMENTED
	#define CAL_FixedBlocksPoolDestroy(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_FixedBlocksPoolDestroy  FALSE
	#define EXP_FixedBlocksPoolDestroy  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_FixedBlocksPoolDestroy
	#define EXT_FixedBlocksPoolDestroy
	#define GET_FixedBlocksPoolDestroy(fl)  CAL_CMGETAPI( "FixedBlocksPoolDestroy" ) 
	#define CAL_FixedBlocksPoolDestroy  FixedBlocksPoolDestroy
	#define CHK_FixedBlocksPoolDestroy  TRUE
	#define EXP_FixedBlocksPoolDestroy  CAL_CMEXPAPI( "FixedBlocksPoolDestroy" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMPOOL_EXTERNAL)
	#define USE_FixedBlocksPoolDestroy
	#define EXT_FixedBlocksPoolDestroy
	#define GET_FixedBlocksPoolDestroy(fl)  CAL_CMGETAPI( "FixedBlocksPoolDestroy" ) 
	#define CAL_FixedBlocksPoolDestroy  FixedBlocksPoolDestroy
	#define CHK_FixedBlocksPoolDestroy  TRUE
	#define EXP_FixedBlocksPoolDestroy  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FixedBlocksPoolDestroy", (RTS_UINTPTR)FixedBlocksPoolDestroy, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemPoolFixedBlocksPoolDestroy
	#define EXT_CmpMemPoolFixedBlocksPoolDestroy
	#define GET_CmpMemPoolFixedBlocksPoolDestroy  ERR_OK
	#define CAL_CmpMemPoolFixedBlocksPoolDestroy pICmpMemPool->IFixedBlocksPoolDestroy
	#define CHK_CmpMemPoolFixedBlocksPoolDestroy (pICmpMemPool != NULL)
	#define EXP_CmpMemPoolFixedBlocksPoolDestroy  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_FixedBlocksPoolDestroy
	#define EXT_FixedBlocksPoolDestroy
	#define GET_FixedBlocksPoolDestroy(fl)  CAL_CMGETAPI( "FixedBlocksPoolDestroy" ) 
	#define CAL_FixedBlocksPoolDestroy pICmpMemPool->IFixedBlocksPoolDestroy
	#define CHK_FixedBlocksPoolDestroy (pICmpMemPool != NULL)
	#define EXP_FixedBlocksPoolDestroy  CAL_CMEXPAPI( "FixedBlocksPoolDestroy" ) 
#else /* DYNAMIC_LINK */
	#define USE_FixedBlocksPoolDestroy  PFFIXEDBLOCKSPOOLDESTROY pfFixedBlocksPoolDestroy;
	#define EXT_FixedBlocksPoolDestroy  extern PFFIXEDBLOCKSPOOLDESTROY pfFixedBlocksPoolDestroy;
	#define GET_FixedBlocksPoolDestroy(fl)  s_pfCMGetAPI2( "FixedBlocksPoolDestroy", (RTS_VOID_FCTPTR *)&pfFixedBlocksPoolDestroy, (fl), 0, 0)
	#define CAL_FixedBlocksPoolDestroy  pfFixedBlocksPoolDestroy
	#define CHK_FixedBlocksPoolDestroy  (pfFixedBlocksPoolDestroy != NULL)
	#define EXP_FixedBlocksPoolDestroy  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FixedBlocksPoolDestroy", (RTS_UINTPTR)FixedBlocksPoolDestroy, 0, 0) 
#endif





#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFMEMPOOLCREATEDYNAMIC IMemPoolCreateDynamic;
 	PFMEMPOOLCREATESTATIC IMemPoolCreateStatic;
 	PFMEMPOOLEXTENDDYNAMIC IMemPoolExtendDynamic;
 	PFMEMPOOLEXTENDSTATIC IMemPoolExtendStatic;
 	PFMEMPOOLCREATESYNCOBJECT IMemPoolCreateSyncObject;
 	PFMEMPOOLDELETESYNCOBJECT IMemPoolDeleteSyncObject;
 	PFMEMPOOLDELETE IMemPoolDelete;
 	PFMEMPOOLCLEANUP IMemPoolCleanup;
 	PFMEMPOOLGETBLOCK IMemPoolGetBlock;
 	PFMEMPOOLGETBLOCK2 IMemPoolGetBlock2;
 	PFMEMPOOLGETPCB IMemPoolGetPCB;
 	PFMEMPOOLPUTBLOCK IMemPoolPutBlock;
 	PFMEMPOOLADDUSEDBLOCK IMemPoolAddUsedBlock;
 	PFMEMPOOLAPPENDUSEDBLOCK IMemPoolAppendUsedBlock;
 	PFMEMPOOLINSERTUSEDBLOCK IMemPoolInsertUsedBlock;
 	PFMEMPOOLREMOVEUSEDBLOCK IMemPoolRemoveUsedBlock;
 	PFMEMPOOLADDUSEDBLOCKTOPOOL IMemPoolAddUsedBlockToPool;
 	PFMEMPOOLAPPENDUSEDBLOCKTOPOOL IMemPoolAppendUsedBlockToPool;
 	PFMEMPOOLREMOVEUSEDBLOCKFROMPOOL IMemPoolRemoveUsedBlockFromPool;
 	PFMEMPOOLLOCKBLOCK IMemPoolLockBlock;
 	PFMEMPOOLUNLOCKBLOCK IMemPoolUnlockBlock;
 	PFMEMPOOLLOCK IMemPoolLock;
 	PFMEMPOOLUNLOCK IMemPoolUnlock;
 	PFMEMPOOLFINDBLOCK IMemPoolFindBlock;
 	PFMEMPOOLISVALIDBLOCK IMemPoolIsValidBlock;
 	PFMEMPOOLGETFIRSTBLOCK IMemPoolGetFirstBlock;
 	PFMEMPOOLGETNEXTBLOCK IMemPoolGetNextBlock;
 	PFFIXEDBLOCKSPOOLINIT IFixedBlocksPoolInit;
 	PFFIXEDBLOCKSPOOLALLOC IFixedBlocksPoolAlloc;
 	PFFIXEDBLOCKSPOOLFREE IFixedBlocksPoolFree;
 	PFFIXEDBLOCKSPOOLRECLAIM IFixedBlocksPoolReclaim;
 	PFFIXEDBLOCKSPOOLDESTROY IFixedBlocksPoolDestroy;
 } ICmpMemPool_C;

#ifdef CPLUSPLUS
class ICmpMemPool : public IBase
{
	public:
		virtual RTS_HANDLE CDECL IMemPoolCreateDynamic(char *pszComponentName, RTS_SIZE ulNumBlocks, RTS_SIZE ulBlockSize, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IMemPoolCreateStatic(RTS_SIZE ulBlockSize, RTS_SIZE ulMemSize, void* pMemory, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IMemPoolExtendDynamic(RTS_HANDLE hMemPool, char *pszComponentName, RTS_SIZE ulNumBlocks) =0;
		virtual RTS_RESULT CDECL IMemPoolExtendStatic(RTS_HANDLE hMemPool, RTS_SIZE ulMemSize, void* pMemory) =0;
		virtual RTS_RESULT CDECL IMemPoolCreateSyncObject(RTS_HANDLE hMemPool) =0;
		virtual RTS_RESULT CDECL IMemPoolDeleteSyncObject(RTS_HANDLE hMemPool) =0;
		virtual RTS_RESULT CDECL IMemPoolDelete(RTS_HANDLE hMemPool, char *pszComponentName) =0;
		virtual RTS_RESULT CDECL IMemPoolCleanup(RTS_HANDLE hMemPool, char *pszComponentName, int bReleaseSemaphore) =0;
		virtual void* CDECL IMemPoolGetBlock(RTS_HANDLE hMemPool, RTS_RESULT *pResult) =0;
		virtual void* CDECL IMemPoolGetBlock2(RTS_HANDLE hMemPool, int bDynamic, char *pszComponentName, RTS_RESULT *pResult) =0;
		virtual RTS_PCB* CDECL IMemPoolGetPCB(RTS_HANDLE hMemPool, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IMemPoolPutBlock(void* pBlock) =0;
		virtual RTS_RESULT CDECL IMemPoolAddUsedBlock(void* pBlock) =0;
		virtual RTS_RESULT CDECL IMemPoolAppendUsedBlock(void* pBlock) =0;
		virtual RTS_RESULT CDECL IMemPoolInsertUsedBlock(void* pPrevBlock, void* pBlock) =0;
		virtual RTS_RESULT CDECL IMemPoolRemoveUsedBlock(void* pBlock) =0;
		virtual RTS_RESULT CDECL IMemPoolAddUsedBlockToPool(void* pBlock, RTS_HANDLE hPool) =0;
		virtual RTS_RESULT CDECL IMemPoolAppendUsedBlockToPool(void* pBlock, RTS_HANDLE hPool) =0;
		virtual RTS_RESULT CDECL IMemPoolRemoveUsedBlockFromPool(void* pBlock, RTS_HANDLE hPool) =0;
		virtual RTS_RESULT CDECL IMemPoolLockBlock(void* pBlock) =0;
		virtual RTS_RESULT CDECL IMemPoolUnlockBlock(void* pBlock) =0;
		virtual RTS_RESULT CDECL IMemPoolLock(RTS_HANDLE hMemPool) =0;
		virtual RTS_RESULT CDECL IMemPoolUnlock(RTS_HANDLE hMemPool) =0;
		virtual void * CDECL IMemPoolFindBlock(RTS_HANDLE hMemPool, RTS_SIZE ulOffset, RTS_SIZE ulSize, void *pToFind, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IMemPoolIsValidBlock(RTS_HANDLE hMemPool, void *pBlock) =0;
		virtual void* CDECL IMemPoolGetFirstBlock(RTS_HANDLE hMemPool, RTS_RESULT *pResult) =0;
		virtual void* CDECL IMemPoolGetNextBlock(RTS_HANDLE hMemPool, void *pPrevBlock, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IFixedBlocksPoolInit(RTS_FIXED_BLOCKS_POOL* pPool, RTS_MEM_REGION* pRegion, RTS_SIZE block_size, RTS_SIZE blocks_number) =0;
		virtual void* CDECL IFixedBlocksPoolAlloc(RTS_FIXED_BLOCKS_POOL* pPool, RTS_SIZE size, RTS_RESULT* pResult) =0;
		virtual RTS_RESULT CDECL IFixedBlocksPoolFree(RTS_FIXED_BLOCKS_POOL* pPool, void* pMem) =0;
		virtual RTS_RESULT CDECL IFixedBlocksPoolReclaim(RTS_FIXED_BLOCKS_POOL* pPool) =0;
		virtual RTS_RESULT CDECL IFixedBlocksPoolDestroy(RTS_FIXED_BLOCKS_POOL* pPool) =0;
};
	#ifndef ITF_CmpMemPool
		#define ITF_CmpMemPool static ICmpMemPool *pICmpMemPool = NULL;
	#endif
	#define EXTITF_CmpMemPool
#else	/*CPLUSPLUS*/
	typedef ICmpMemPool_C		ICmpMemPool;
	#ifndef ITF_CmpMemPool
		#define ITF_CmpMemPool
	#endif
	#define EXTITF_CmpMemPool
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPMEMPOOLITF_H_*/
