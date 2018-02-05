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
 *. |...         |                                   `------------'
 *. `-------------
 *.
 *.                      provided
 *.                      Memory Area
 *.                      .--------------------------.
 *.                      | PCB                      |
 *.   List of free Blocks|  Blocksize               |      List of used Blocks
 *.                      |  pBlocksInUse            |===========.
 *.         .=========== |  pBCB                    |           |
 *.         |            |......................... |           |
 *.         |            | BCB                      | &lt;========='
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

SET_INTERFACE_NAME(`CmpMemPool')

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
DEF_ITF_API(`RTS_HANDLE',`CDECL',`MemPoolCreateDynamic',`(char *pszComponentName, RTS_SIZE ulNumBlocks, RTS_SIZE ulBlockSize, RTS_RESULT *pResult)')


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
DEF_ITF_API(`RTS_HANDLE',`CDECL',`MemPoolCreateStatic',`(RTS_SIZE ulBlockSize, RTS_SIZE ulMemSize, void* pMemory, RTS_RESULT *pResult)')

/**
 * <description>
 *	Extend dynamic an existing pool
 * </description>
 * <param name="hMemPool" type="IN">Handle to the pool</param>
 * <param name="pszComponentName" type="IN">Component name</param>
 * <param name="ulNumBlocks" type="IN">Number of blocks to extend</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`MemPoolExtendDynamic',`(RTS_HANDLE hMemPool, char *pszComponentName, RTS_SIZE ulNumBlocks)')

/**
 * <description>
 *	Extend an existing pool with a static array
 * </description>
 * <param name="hMemPool" type="IN">Handle to the pool</param>
 * <param name="ulMemSize" type="IN">Complete size of the static memory</param>
 * <param name="pMemory" type="IN">Pointer to the static memory</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`MemPoolExtendStatic',`(RTS_HANDLE hMemPool, RTS_SIZE ulMemSize, void* pMemory)')

/**
 * <description>
 *	Create the internal sync object for synchronizing the pool.
 * </description>
 * <param name="hMemPool" type="IN">Handle to the pool</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`MemPoolCreateSyncObject',`(RTS_HANDLE hMemPool)')

/**
 * <description>
 *	Delete the internal sync object for synchronizing the pool.
 * </description>
 * <param name="hMemPool" type="IN">Handle to the pool</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`MemPoolDeleteSyncObject',`(RTS_HANDLE hMemPool)')

/**
 * <description>
 *	Delete an existing pool
 * </description>
 * <param name="hMemPool" type="IN">Handle to the pool</param>
 * <param name="pszComponentName" type="IN">Component name</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`MemPoolDelete',`(RTS_HANDLE hMemPool, char *pszComponentName)')

/**
 * <description>
 *	Cleanup the pool (delete all allocated heap pool objects)
 * </description>
 * <param name="hMemPool" type="IN">Handle to the pool</param>
 * <param name="pszComponentName" type="IN">Component name</param>
 * <param name="bReleaseSemaphore" type="IN">1=Pool semaphore is released, 0=Only cleanup</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`MemPoolCleanup',`(RTS_HANDLE hMemPool, char *pszComponentName, int bReleaseSemaphore)')



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
DEF_ITF_API(`void*',`CDECL',`MemPoolGetBlock',`(RTS_HANDLE hMemPool, RTS_RESULT *pResult)')

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
DEF_ITF_API(`void*',`CDECL',`MemPoolGetBlock2',`(RTS_HANDLE hMemPool, int bDynamic, char *pszComponentName, RTS_RESULT *pResult)')

/**
 * <description>
 *	Get one the pool control block of a specified pool
 * </description>
 * <param name="hMemPool" type="IN">Handle to the pool</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the pool control block</result>
 */
DEF_ITF_API(`RTS_PCB*',`CDECL',`MemPoolGetPCB',`(RTS_HANDLE hMemPool, RTS_RESULT *pResult)')

/**
 * <description>
 *	Put a memory block back into the pool (release). Now, the block is in the chain list of free blocks again. 
 * </description>
 * <param name="pBlock" type="IN" range="[NULL,VALID_BLOCK,INVALID_BLOCK]">Pointer to the memory block</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Successfully added Block to MemPool</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Could not add Block to MemPool, wrong pBlock</errorcode> 
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`MemPoolPutBlock',`(void* pBlock)')

/**
 * <description>
 *	Add used block at the beginning of the pool. Now, the block is in the chain list of used blocks.
 * </description>
 * <param name="pBlock" type="IN" range="[NULL,VALID_BLOCK]">Pointer to the memory block</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Successfully added Block to MemPool</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Could not add Block to MemPool, wrong pBlock</errorcode> 
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`MemPoolAddUsedBlock',`(void* pBlock)')

/**
 * <description>
 *	Add used block at the end of the pool. Now, the block is in the chain list of used blocks.
 * </description>
 * <param name="pBlock" type="IN" range="[NULL,VALID_BLOCK]">Pointer to the memory block</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Successfully added Block to MemPool</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Could not add Block to MemPool, wrong pBlock</errorcode> 
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`MemPoolAppendUsedBlock',`(void* pBlock)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`MemPoolInsertUsedBlock',`(void* pPrevBlock, void* pBlock)')

/**
 * <description>
 *	Remove used block from the pool. Now, the block is removed from the chain list of used blocks.
 * </description>
 * <param name="pBlock" type="IN" range="[NULL,VALID_BLOCK]">Pointer to the memory block</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Successfully removed Block from MemPool</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Could not remove Block from MemPool, wrong pBlock</errorcode> 
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`MemPoolRemoveUsedBlock',`(void* pBlock)')

/**
 * <description>
 *	Add used block the beginning of the specified pool. Now, the block is in the chain list of used blocks.
 * </description>
 * <param name="pBlock" type="IN">Pointer to the memory block</param>
 * <param name="hPool" type="IN">Handle to the pool</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`MemPoolAddUsedBlockToPool',`(void* pBlock, RTS_HANDLE hPool)')

/**
 * <description>
 *	Add the block to the end of the used block list of hPool
 * </description>
 * <param name="pBlock" type="IN">Pointer to the memory block</param>
 * <param name="hPool" type="IN">Handle to the pool</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`MemPoolAppendUsedBlockToPool',`(void* pBlock, RTS_HANDLE hPool)')

/**
 * <description>
 *	Remove used block from the specified pool. Now, the block is removed from the chain list of used blocks.
 * </description>
 * <param name="pBlock" type="IN">Pointer to the memory block</param>
 * <param name="hPool" type="IN">Handle to the pool</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`MemPoolRemoveUsedBlockFromPool',`(void* pBlock, RTS_HANDLE hPool)')

/**
 * <description>
 *	Lock the access to a pool to be threadsafe.
 * </description>
 * <param name="pBlock" type="IN">Pointer to the memory block</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`MemPoolLockBlock',`(void* pBlock)')

/**
 * <description>
 *	Unlock the access to a pool.
 * </description>
 * <param name="pBlock" type="IN">Pointer to the memory block</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`MemPoolUnlockBlock',`(void* pBlock)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`MemPoolLock',`(RTS_HANDLE hMemPool)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`MemPoolUnlock',`(RTS_HANDLE hMemPool)')

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
DEF_ITF_API(`void *',`CDECL',`MemPoolFindBlock',`(RTS_HANDLE hMemPool, RTS_SIZE ulOffset, RTS_SIZE ulSize, void *pToFind, RTS_RESULT *pResult)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`MemPoolIsValidBlock',`(RTS_HANDLE hMemPool, void *pBlock)')

/**
 * <description>
 *	Get the first memory block out of the pool. Can be used for explicite iteration routines.
 * </description>
 * <param name="hMemPool" type="IN">Handle to the memory pool</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to first memory block</result>
 */
DEF_ITF_API(`void*',`CDECL',`MemPoolGetFirstBlock',`(RTS_HANDLE hMemPool, RTS_RESULT *pResult)')

/**
 * <description>
 *	Get the next memory block out of the pool. Can be used for explicite iteration routines.
 * </description>
 * <param name="hMemPool" type="IN">Handle to the memory pool</param>
 * <param name="pPrevBlock" type="IN">Pointer to previous memory block</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to next memory block</result>
 */
DEF_ITF_API(`void*',`CDECL',`MemPoolGetNextBlock',`(RTS_HANDLE hMemPool, void *pPrevBlock, RTS_RESULT *pResult)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`FixedBlocksPoolInit',`(RTS_FIXED_BLOCKS_POOL* pPool, RTS_MEM_REGION* pRegion, RTS_SIZE block_size, RTS_SIZE blocks_number)')

/**
 * <description>
 *	Allocates a memory block out of the pool 
 * </description>
 * <param name="pPool" type="IN">Pointer to a pool object</param>
 * <param name="size" type="IN">Requested size of memory to be allocated. Should be less than the pPool block size</param>
 * <param name="pResult" type="OUT">Pointer to an error code</param>
 * <result>Pointer to the allocated block of memory</result>
 */
DEF_ITF_API(`void*',`CDECL',`FixedBlocksPoolAlloc',`(RTS_FIXED_BLOCKS_POOL* pPool, RTS_SIZE size, RTS_RESULT* pResult)')

/**
 * <description>
 *	Puts a memory block back to the pool.
 * </description>
 * <param name="pPool" type="IN">Pointer to a pool object</param>
 * <param name="pMem" type="IN">Pointer to a memory block to be returned to the pool</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`FixedBlocksPoolFree',`(RTS_FIXED_BLOCKS_POOL* pPool, void* pMem)')

/**
 * <description>
 *	Puts all the previously allocated memory blocks back to the pool.
 * </description>
 * <param name="pPool" type="IN">Pointer to a pool object</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`FixedBlocksPoolReclaim',`(RTS_FIXED_BLOCKS_POOL* pPool)')

/**
 * <description>
 *	Destroys a pool object.
 * </description>
 * <param name="pPool" type="IN">Pointer to a pool object</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`FixedBlocksPoolDestroy',`(RTS_FIXED_BLOCKS_POOL* pPool)')


#ifdef __cplusplus
}
#endif
