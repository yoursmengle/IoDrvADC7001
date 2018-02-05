 /**
 * <interfacename>CmpHeapAlloc</interfacename>
 * <description>
 *  <p>Allocator for the heap management on limited targets.</p>
 *	<p>This allocator implements a well-known buddy algorithm.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */
 

	
	
#ifndef _CMPHEAPPOOLITF_H_
#define _CMPHEAPPOOLITF_H_

#include "CmpStd.h"

 

 



 
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
RTS_HANDLE CDECL HeapPoolInit(RTS_MEM_REGION* pRegionsList, RTS_RESULT* pResult);
typedef RTS_HANDLE (CDECL * PFHEAPPOOLINIT) (RTS_MEM_REGION* pRegionsList, RTS_RESULT* pResult);
#if defined(CMPHEAPPOOL_NOTIMPLEMENTED) || defined(HEAPPOOLINIT_NOTIMPLEMENTED)
	#define USE_HeapPoolInit
	#define EXT_HeapPoolInit
	#define GET_HeapPoolInit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_HeapPoolInit(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_HeapPoolInit  FALSE
	#define EXP_HeapPoolInit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_HeapPoolInit
	#define EXT_HeapPoolInit
	#define GET_HeapPoolInit(fl)  CAL_CMGETAPI( "HeapPoolInit" ) 
	#define CAL_HeapPoolInit  HeapPoolInit
	#define CHK_HeapPoolInit  TRUE
	#define EXP_HeapPoolInit  CAL_CMEXPAPI( "HeapPoolInit" ) 
#elif defined(MIXED_LINK) && !defined(CMPHEAPPOOL_EXTERNAL)
	#define USE_HeapPoolInit
	#define EXT_HeapPoolInit
	#define GET_HeapPoolInit(fl)  CAL_CMGETAPI( "HeapPoolInit" ) 
	#define CAL_HeapPoolInit  HeapPoolInit
	#define CHK_HeapPoolInit  TRUE
	#define EXP_HeapPoolInit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"HeapPoolInit", (RTS_UINTPTR)HeapPoolInit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHeapPoolHeapPoolInit
	#define EXT_CmpHeapPoolHeapPoolInit
	#define GET_CmpHeapPoolHeapPoolInit  ERR_OK
	#define CAL_CmpHeapPoolHeapPoolInit pICmpHeapPool->IHeapPoolInit
	#define CHK_CmpHeapPoolHeapPoolInit (pICmpHeapPool != NULL)
	#define EXP_CmpHeapPoolHeapPoolInit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_HeapPoolInit
	#define EXT_HeapPoolInit
	#define GET_HeapPoolInit(fl)  CAL_CMGETAPI( "HeapPoolInit" ) 
	#define CAL_HeapPoolInit pICmpHeapPool->IHeapPoolInit
	#define CHK_HeapPoolInit (pICmpHeapPool != NULL)
	#define EXP_HeapPoolInit  CAL_CMEXPAPI( "HeapPoolInit" ) 
#else /* DYNAMIC_LINK */
	#define USE_HeapPoolInit  PFHEAPPOOLINIT pfHeapPoolInit;
	#define EXT_HeapPoolInit  extern PFHEAPPOOLINIT pfHeapPoolInit;
	#define GET_HeapPoolInit(fl)  s_pfCMGetAPI2( "HeapPoolInit", (RTS_VOID_FCTPTR *)&pfHeapPoolInit, (fl), 0, 0)
	#define CAL_HeapPoolInit  pfHeapPoolInit
	#define CHK_HeapPoolInit  (pfHeapPoolInit != NULL)
	#define EXP_HeapPoolInit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"HeapPoolInit", (RTS_UINTPTR)HeapPoolInit, 0, 0) 
#endif




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
void* CDECL HeapPoolAlloc(RTS_HANDLE hPool, RTS_SIZE size, RTS_RESULT* pResult);
typedef void* (CDECL * PFHEAPPOOLALLOC) (RTS_HANDLE hPool, RTS_SIZE size, RTS_RESULT* pResult);
#if defined(CMPHEAPPOOL_NOTIMPLEMENTED) || defined(HEAPPOOLALLOC_NOTIMPLEMENTED)
	#define USE_HeapPoolAlloc
	#define EXT_HeapPoolAlloc
	#define GET_HeapPoolAlloc(fl)  ERR_NOTIMPLEMENTED
	#define CAL_HeapPoolAlloc(p0,p1,p2)  (void*)ERR_NOTIMPLEMENTED
	#define CHK_HeapPoolAlloc  FALSE
	#define EXP_HeapPoolAlloc  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_HeapPoolAlloc
	#define EXT_HeapPoolAlloc
	#define GET_HeapPoolAlloc(fl)  CAL_CMGETAPI( "HeapPoolAlloc" ) 
	#define CAL_HeapPoolAlloc  HeapPoolAlloc
	#define CHK_HeapPoolAlloc  TRUE
	#define EXP_HeapPoolAlloc  CAL_CMEXPAPI( "HeapPoolAlloc" ) 
#elif defined(MIXED_LINK) && !defined(CMPHEAPPOOL_EXTERNAL)
	#define USE_HeapPoolAlloc
	#define EXT_HeapPoolAlloc
	#define GET_HeapPoolAlloc(fl)  CAL_CMGETAPI( "HeapPoolAlloc" ) 
	#define CAL_HeapPoolAlloc  HeapPoolAlloc
	#define CHK_HeapPoolAlloc  TRUE
	#define EXP_HeapPoolAlloc  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"HeapPoolAlloc", (RTS_UINTPTR)HeapPoolAlloc, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHeapPoolHeapPoolAlloc
	#define EXT_CmpHeapPoolHeapPoolAlloc
	#define GET_CmpHeapPoolHeapPoolAlloc  ERR_OK
	#define CAL_CmpHeapPoolHeapPoolAlloc pICmpHeapPool->IHeapPoolAlloc
	#define CHK_CmpHeapPoolHeapPoolAlloc (pICmpHeapPool != NULL)
	#define EXP_CmpHeapPoolHeapPoolAlloc  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_HeapPoolAlloc
	#define EXT_HeapPoolAlloc
	#define GET_HeapPoolAlloc(fl)  CAL_CMGETAPI( "HeapPoolAlloc" ) 
	#define CAL_HeapPoolAlloc pICmpHeapPool->IHeapPoolAlloc
	#define CHK_HeapPoolAlloc (pICmpHeapPool != NULL)
	#define EXP_HeapPoolAlloc  CAL_CMEXPAPI( "HeapPoolAlloc" ) 
#else /* DYNAMIC_LINK */
	#define USE_HeapPoolAlloc  PFHEAPPOOLALLOC pfHeapPoolAlloc;
	#define EXT_HeapPoolAlloc  extern PFHEAPPOOLALLOC pfHeapPoolAlloc;
	#define GET_HeapPoolAlloc(fl)  s_pfCMGetAPI2( "HeapPoolAlloc", (RTS_VOID_FCTPTR *)&pfHeapPoolAlloc, (fl), 0, 0)
	#define CAL_HeapPoolAlloc  pfHeapPoolAlloc
	#define CHK_HeapPoolAlloc  (pfHeapPoolAlloc != NULL)
	#define EXP_HeapPoolAlloc  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"HeapPoolAlloc", (RTS_UINTPTR)HeapPoolAlloc, 0, 0) 
#endif




/**
 * <description>
 *	Puts a memory block back to the pool and performs defragmentation.
 * </description>
 * <param name="hPool" type="IN">Handle to a pool object</param>
 * <param name="pMem" type="IN">Pointer to a memory block to be returned to the pool</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL HeapPoolFree(RTS_HANDLE hPool, void* pMem);
typedef RTS_RESULT (CDECL * PFHEAPPOOLFREE) (RTS_HANDLE hPool, void* pMem);
#if defined(CMPHEAPPOOL_NOTIMPLEMENTED) || defined(HEAPPOOLFREE_NOTIMPLEMENTED)
	#define USE_HeapPoolFree
	#define EXT_HeapPoolFree
	#define GET_HeapPoolFree(fl)  ERR_NOTIMPLEMENTED
	#define CAL_HeapPoolFree(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_HeapPoolFree  FALSE
	#define EXP_HeapPoolFree  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_HeapPoolFree
	#define EXT_HeapPoolFree
	#define GET_HeapPoolFree(fl)  CAL_CMGETAPI( "HeapPoolFree" ) 
	#define CAL_HeapPoolFree  HeapPoolFree
	#define CHK_HeapPoolFree  TRUE
	#define EXP_HeapPoolFree  CAL_CMEXPAPI( "HeapPoolFree" ) 
#elif defined(MIXED_LINK) && !defined(CMPHEAPPOOL_EXTERNAL)
	#define USE_HeapPoolFree
	#define EXT_HeapPoolFree
	#define GET_HeapPoolFree(fl)  CAL_CMGETAPI( "HeapPoolFree" ) 
	#define CAL_HeapPoolFree  HeapPoolFree
	#define CHK_HeapPoolFree  TRUE
	#define EXP_HeapPoolFree  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"HeapPoolFree", (RTS_UINTPTR)HeapPoolFree, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpHeapPoolHeapPoolFree
	#define EXT_CmpHeapPoolHeapPoolFree
	#define GET_CmpHeapPoolHeapPoolFree  ERR_OK
	#define CAL_CmpHeapPoolHeapPoolFree pICmpHeapPool->IHeapPoolFree
	#define CHK_CmpHeapPoolHeapPoolFree (pICmpHeapPool != NULL)
	#define EXP_CmpHeapPoolHeapPoolFree  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_HeapPoolFree
	#define EXT_HeapPoolFree
	#define GET_HeapPoolFree(fl)  CAL_CMGETAPI( "HeapPoolFree" ) 
	#define CAL_HeapPoolFree pICmpHeapPool->IHeapPoolFree
	#define CHK_HeapPoolFree (pICmpHeapPool != NULL)
	#define EXP_HeapPoolFree  CAL_CMEXPAPI( "HeapPoolFree" ) 
#else /* DYNAMIC_LINK */
	#define USE_HeapPoolFree  PFHEAPPOOLFREE pfHeapPoolFree;
	#define EXT_HeapPoolFree  extern PFHEAPPOOLFREE pfHeapPoolFree;
	#define GET_HeapPoolFree(fl)  s_pfCMGetAPI2( "HeapPoolFree", (RTS_VOID_FCTPTR *)&pfHeapPoolFree, (fl), 0, 0)
	#define CAL_HeapPoolFree  pfHeapPoolFree
	#define CHK_HeapPoolFree  (pfHeapPoolFree != NULL)
	#define EXP_HeapPoolFree  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"HeapPoolFree", (RTS_UINTPTR)HeapPoolFree, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif




typedef struct
{
	IBase_C *pBase;
	PFHEAPPOOLINIT IHeapPoolInit;
 	PFHEAPPOOLALLOC IHeapPoolAlloc;
 	PFHEAPPOOLFREE IHeapPoolFree;
 } ICmpHeapPool_C;

#ifdef CPLUSPLUS
class ICmpHeapPool : public IBase
{
	public:
		virtual RTS_HANDLE CDECL IHeapPoolInit(RTS_MEM_REGION* pRegionsList, RTS_RESULT* pResult) =0;
		virtual void* CDECL IHeapPoolAlloc(RTS_HANDLE hPool, RTS_SIZE size, RTS_RESULT* pResult) =0;
		virtual RTS_RESULT CDECL IHeapPoolFree(RTS_HANDLE hPool, void* pMem) =0;
};
	#ifndef ITF_CmpHeapPool
		#define ITF_CmpHeapPool static ICmpHeapPool *pICmpHeapPool = NULL;
	#endif
	#define EXTITF_CmpHeapPool
#else	/*CPLUSPLUS*/
	typedef ICmpHeapPool_C		ICmpHeapPool;
	#ifndef ITF_CmpHeapPool
		#define ITF_CmpHeapPool
	#endif
	#define EXTITF_CmpHeapPool
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPHEAPPOOLITF_H_*/
