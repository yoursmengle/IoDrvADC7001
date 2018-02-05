 /**
 * <interfacename>CmpMemGC</interfacename>
 * <description> 
 *	Interface of the garbage collector, that detects memory leaks and memory overwrite operations.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPMEMGCITF_H_
#define _CMPMEMGCITF_H_

#include "CmpStd.h"

 

 




#include "CMUtilsItf.h"
#include "CMUtilsHashItf.h"

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
RTS_SIZE CDECL MemGCGetSize(RTS_SIZE ulSize);
typedef RTS_SIZE (CDECL * PFMEMGCGETSIZE) (RTS_SIZE ulSize);
#if defined(CMPMEMGC_NOTIMPLEMENTED) || defined(MEMGCGETSIZE_NOTIMPLEMENTED)
	#define USE_MemGCGetSize
	#define EXT_MemGCGetSize
	#define GET_MemGCGetSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemGCGetSize(p0)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_MemGCGetSize  FALSE
	#define EXP_MemGCGetSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemGCGetSize
	#define EXT_MemGCGetSize
	#define GET_MemGCGetSize(fl)  CAL_CMGETAPI( "MemGCGetSize" ) 
	#define CAL_MemGCGetSize  MemGCGetSize
	#define CHK_MemGCGetSize  TRUE
	#define EXP_MemGCGetSize  CAL_CMEXPAPI( "MemGCGetSize" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMGC_EXTERNAL)
	#define USE_MemGCGetSize
	#define EXT_MemGCGetSize
	#define GET_MemGCGetSize(fl)  CAL_CMGETAPI( "MemGCGetSize" ) 
	#define CAL_MemGCGetSize  MemGCGetSize
	#define CHK_MemGCGetSize  TRUE
	#define EXP_MemGCGetSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemGCGetSize", (RTS_UINTPTR)MemGCGetSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemGCMemGCGetSize
	#define EXT_CmpMemGCMemGCGetSize
	#define GET_CmpMemGCMemGCGetSize  ERR_OK
	#define CAL_CmpMemGCMemGCGetSize pICmpMemGC->IMemGCGetSize
	#define CHK_CmpMemGCMemGCGetSize (pICmpMemGC != NULL)
	#define EXP_CmpMemGCMemGCGetSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemGCGetSize
	#define EXT_MemGCGetSize
	#define GET_MemGCGetSize(fl)  CAL_CMGETAPI( "MemGCGetSize" ) 
	#define CAL_MemGCGetSize pICmpMemGC->IMemGCGetSize
	#define CHK_MemGCGetSize (pICmpMemGC != NULL)
	#define EXP_MemGCGetSize  CAL_CMEXPAPI( "MemGCGetSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemGCGetSize  PFMEMGCGETSIZE pfMemGCGetSize;
	#define EXT_MemGCGetSize  extern PFMEMGCGETSIZE pfMemGCGetSize;
	#define GET_MemGCGetSize(fl)  s_pfCMGetAPI2( "MemGCGetSize", (RTS_VOID_FCTPTR *)&pfMemGCGetSize, (fl), 0, 0)
	#define CAL_MemGCGetSize  pfMemGCGetSize
	#define CHK_MemGCGetSize  (pfMemGCGetSize != NULL)
	#define EXP_MemGCGetSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemGCGetSize", (RTS_UINTPTR)MemGCGetSize, 0, 0) 
#endif




/**
 * <description>
 *	Routine to get total size of the currently allocated heap memory.
 * </description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Size of the memory in bytes that is currently allocated from the heap</result>
 */
RTS_SIZE CDECL MemGCGetCurrentHeapSize(RTS_RESULT *pResult);
typedef RTS_SIZE (CDECL * PFMEMGCGETCURRENTHEAPSIZE) (RTS_RESULT *pResult);
#if defined(CMPMEMGC_NOTIMPLEMENTED) || defined(MEMGCGETCURRENTHEAPSIZE_NOTIMPLEMENTED)
	#define USE_MemGCGetCurrentHeapSize
	#define EXT_MemGCGetCurrentHeapSize
	#define GET_MemGCGetCurrentHeapSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemGCGetCurrentHeapSize(p0)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_MemGCGetCurrentHeapSize  FALSE
	#define EXP_MemGCGetCurrentHeapSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemGCGetCurrentHeapSize
	#define EXT_MemGCGetCurrentHeapSize
	#define GET_MemGCGetCurrentHeapSize(fl)  CAL_CMGETAPI( "MemGCGetCurrentHeapSize" ) 
	#define CAL_MemGCGetCurrentHeapSize  MemGCGetCurrentHeapSize
	#define CHK_MemGCGetCurrentHeapSize  TRUE
	#define EXP_MemGCGetCurrentHeapSize  CAL_CMEXPAPI( "MemGCGetCurrentHeapSize" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMGC_EXTERNAL)
	#define USE_MemGCGetCurrentHeapSize
	#define EXT_MemGCGetCurrentHeapSize
	#define GET_MemGCGetCurrentHeapSize(fl)  CAL_CMGETAPI( "MemGCGetCurrentHeapSize" ) 
	#define CAL_MemGCGetCurrentHeapSize  MemGCGetCurrentHeapSize
	#define CHK_MemGCGetCurrentHeapSize  TRUE
	#define EXP_MemGCGetCurrentHeapSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemGCGetCurrentHeapSize", (RTS_UINTPTR)MemGCGetCurrentHeapSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemGCMemGCGetCurrentHeapSize
	#define EXT_CmpMemGCMemGCGetCurrentHeapSize
	#define GET_CmpMemGCMemGCGetCurrentHeapSize  ERR_OK
	#define CAL_CmpMemGCMemGCGetCurrentHeapSize pICmpMemGC->IMemGCGetCurrentHeapSize
	#define CHK_CmpMemGCMemGCGetCurrentHeapSize (pICmpMemGC != NULL)
	#define EXP_CmpMemGCMemGCGetCurrentHeapSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemGCGetCurrentHeapSize
	#define EXT_MemGCGetCurrentHeapSize
	#define GET_MemGCGetCurrentHeapSize(fl)  CAL_CMGETAPI( "MemGCGetCurrentHeapSize" ) 
	#define CAL_MemGCGetCurrentHeapSize pICmpMemGC->IMemGCGetCurrentHeapSize
	#define CHK_MemGCGetCurrentHeapSize (pICmpMemGC != NULL)
	#define EXP_MemGCGetCurrentHeapSize  CAL_CMEXPAPI( "MemGCGetCurrentHeapSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemGCGetCurrentHeapSize  PFMEMGCGETCURRENTHEAPSIZE pfMemGCGetCurrentHeapSize;
	#define EXT_MemGCGetCurrentHeapSize  extern PFMEMGCGETCURRENTHEAPSIZE pfMemGCGetCurrentHeapSize;
	#define GET_MemGCGetCurrentHeapSize(fl)  s_pfCMGetAPI2( "MemGCGetCurrentHeapSize", (RTS_VOID_FCTPTR *)&pfMemGCGetCurrentHeapSize, (fl), 0, 0)
	#define CAL_MemGCGetCurrentHeapSize  pfMemGCGetCurrentHeapSize
	#define CHK_MemGCGetCurrentHeapSize  (pfMemGCGetCurrentHeapSize != NULL)
	#define EXP_MemGCGetCurrentHeapSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemGCGetCurrentHeapSize", (RTS_UINTPTR)MemGCGetCurrentHeapSize, 0, 0) 
#endif




/**
 * <description>
 *	Routine to add a new heap memblock to the garbage collector.	
 * </description>
 * <param name="pszComponentName" type="IN">Component name, that allocates the memory</param>
 * <param name="pMem" type="IN">Pointer to the memory block</param>
 * <param name="ulSizeGc" type="IN">Size of the memory block including the garbage collection overhead (see result of MemGCGetSize)</param>
 * <result>Pointer to the memory data block</result>
 */
void * CDECL MemGCAdd(char *pszComponentName, void *pMem, RTS_SIZE ulSizeGc);
typedef void * (CDECL * PFMEMGCADD) (char *pszComponentName, void *pMem, RTS_SIZE ulSizeGc);
#if defined(CMPMEMGC_NOTIMPLEMENTED) || defined(MEMGCADD_NOTIMPLEMENTED)
	#define USE_MemGCAdd
	#define EXT_MemGCAdd
	#define GET_MemGCAdd(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemGCAdd(p0,p1,p2)  (void *)(RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_MemGCAdd  FALSE
	#define EXP_MemGCAdd  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemGCAdd
	#define EXT_MemGCAdd
	#define GET_MemGCAdd(fl)  CAL_CMGETAPI( "MemGCAdd" ) 
	#define CAL_MemGCAdd  MemGCAdd
	#define CHK_MemGCAdd  TRUE
	#define EXP_MemGCAdd  CAL_CMEXPAPI( "MemGCAdd" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMGC_EXTERNAL)
	#define USE_MemGCAdd
	#define EXT_MemGCAdd
	#define GET_MemGCAdd(fl)  CAL_CMGETAPI( "MemGCAdd" ) 
	#define CAL_MemGCAdd  MemGCAdd
	#define CHK_MemGCAdd  TRUE
	#define EXP_MemGCAdd  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemGCAdd", (RTS_UINTPTR)MemGCAdd, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemGCMemGCAdd
	#define EXT_CmpMemGCMemGCAdd
	#define GET_CmpMemGCMemGCAdd  ERR_OK
	#define CAL_CmpMemGCMemGCAdd pICmpMemGC->IMemGCAdd
	#define CHK_CmpMemGCMemGCAdd (pICmpMemGC != NULL)
	#define EXP_CmpMemGCMemGCAdd  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemGCAdd
	#define EXT_MemGCAdd
	#define GET_MemGCAdd(fl)  CAL_CMGETAPI( "MemGCAdd" ) 
	#define CAL_MemGCAdd pICmpMemGC->IMemGCAdd
	#define CHK_MemGCAdd (pICmpMemGC != NULL)
	#define EXP_MemGCAdd  CAL_CMEXPAPI( "MemGCAdd" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemGCAdd  PFMEMGCADD pfMemGCAdd;
	#define EXT_MemGCAdd  extern PFMEMGCADD pfMemGCAdd;
	#define GET_MemGCAdd(fl)  s_pfCMGetAPI2( "MemGCAdd", (RTS_VOID_FCTPTR *)&pfMemGCAdd, (fl), 0, 0)
	#define CAL_MemGCAdd  pfMemGCAdd
	#define CHK_MemGCAdd  (pfMemGCAdd != NULL)
	#define EXP_MemGCAdd  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemGCAdd", (RTS_UINTPTR)MemGCAdd, 0, 0) 
#endif




/**
 * <description>
 *	Routine to remove a heap memblock from the garbage collector.	
 * </description>
 * <param name="pszComponentName" type="IN">Component name, that allocates the memory</param>
 * <param name="pMem" type="IN">Pointer to the memory data block</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the memory block to free</result>
 */
void * CDECL MemGCRemove(char *pszComponentName, void *pMem, RTS_RESULT *pResult);
typedef void * (CDECL * PFMEMGCREMOVE) (char *pszComponentName, void *pMem, RTS_RESULT *pResult);
#if defined(CMPMEMGC_NOTIMPLEMENTED) || defined(MEMGCREMOVE_NOTIMPLEMENTED)
	#define USE_MemGCRemove
	#define EXT_MemGCRemove
	#define GET_MemGCRemove(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemGCRemove(p0,p1,p2)  (void *)(RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_MemGCRemove  FALSE
	#define EXP_MemGCRemove  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemGCRemove
	#define EXT_MemGCRemove
	#define GET_MemGCRemove(fl)  CAL_CMGETAPI( "MemGCRemove" ) 
	#define CAL_MemGCRemove  MemGCRemove
	#define CHK_MemGCRemove  TRUE
	#define EXP_MemGCRemove  CAL_CMEXPAPI( "MemGCRemove" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMGC_EXTERNAL)
	#define USE_MemGCRemove
	#define EXT_MemGCRemove
	#define GET_MemGCRemove(fl)  CAL_CMGETAPI( "MemGCRemove" ) 
	#define CAL_MemGCRemove  MemGCRemove
	#define CHK_MemGCRemove  TRUE
	#define EXP_MemGCRemove  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemGCRemove", (RTS_UINTPTR)MemGCRemove, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemGCMemGCRemove
	#define EXT_CmpMemGCMemGCRemove
	#define GET_CmpMemGCMemGCRemove  ERR_OK
	#define CAL_CmpMemGCMemGCRemove pICmpMemGC->IMemGCRemove
	#define CHK_CmpMemGCMemGCRemove (pICmpMemGC != NULL)
	#define EXP_CmpMemGCMemGCRemove  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemGCRemove
	#define EXT_MemGCRemove
	#define GET_MemGCRemove(fl)  CAL_CMGETAPI( "MemGCRemove" ) 
	#define CAL_MemGCRemove pICmpMemGC->IMemGCRemove
	#define CHK_MemGCRemove (pICmpMemGC != NULL)
	#define EXP_MemGCRemove  CAL_CMEXPAPI( "MemGCRemove" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemGCRemove  PFMEMGCREMOVE pfMemGCRemove;
	#define EXT_MemGCRemove  extern PFMEMGCREMOVE pfMemGCRemove;
	#define GET_MemGCRemove(fl)  s_pfCMGetAPI2( "MemGCRemove", (RTS_VOID_FCTPTR *)&pfMemGCRemove, (fl), 0, 0)
	#define CAL_MemGCRemove  pfMemGCRemove
	#define CHK_MemGCRemove  (pfMemGCRemove != NULL)
	#define EXP_MemGCRemove  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemGCRemove", (RTS_UINTPTR)MemGCRemove, 0, 0) 
#endif




/**
 * <description>
 *	Routine to check all registered memory block bounds for overwrite actions.	
 * </description>
 * <result>Error code</result>
 */
RTS_RESULT CDECL MemGCCheckBoundsAll(void);
typedef RTS_RESULT (CDECL * PFMEMGCCHECKBOUNDSALL) (void);
#if defined(CMPMEMGC_NOTIMPLEMENTED) || defined(MEMGCCHECKBOUNDSALL_NOTIMPLEMENTED)
	#define USE_MemGCCheckBoundsAll
	#define EXT_MemGCCheckBoundsAll
	#define GET_MemGCCheckBoundsAll(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemGCCheckBoundsAll()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MemGCCheckBoundsAll  FALSE
	#define EXP_MemGCCheckBoundsAll  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemGCCheckBoundsAll
	#define EXT_MemGCCheckBoundsAll
	#define GET_MemGCCheckBoundsAll(fl)  CAL_CMGETAPI( "MemGCCheckBoundsAll" ) 
	#define CAL_MemGCCheckBoundsAll  MemGCCheckBoundsAll
	#define CHK_MemGCCheckBoundsAll  TRUE
	#define EXP_MemGCCheckBoundsAll  CAL_CMEXPAPI( "MemGCCheckBoundsAll" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMGC_EXTERNAL)
	#define USE_MemGCCheckBoundsAll
	#define EXT_MemGCCheckBoundsAll
	#define GET_MemGCCheckBoundsAll(fl)  CAL_CMGETAPI( "MemGCCheckBoundsAll" ) 
	#define CAL_MemGCCheckBoundsAll  MemGCCheckBoundsAll
	#define CHK_MemGCCheckBoundsAll  TRUE
	#define EXP_MemGCCheckBoundsAll  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemGCCheckBoundsAll", (RTS_UINTPTR)MemGCCheckBoundsAll, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemGCMemGCCheckBoundsAll
	#define EXT_CmpMemGCMemGCCheckBoundsAll
	#define GET_CmpMemGCMemGCCheckBoundsAll  ERR_OK
	#define CAL_CmpMemGCMemGCCheckBoundsAll pICmpMemGC->IMemGCCheckBoundsAll
	#define CHK_CmpMemGCMemGCCheckBoundsAll (pICmpMemGC != NULL)
	#define EXP_CmpMemGCMemGCCheckBoundsAll  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemGCCheckBoundsAll
	#define EXT_MemGCCheckBoundsAll
	#define GET_MemGCCheckBoundsAll(fl)  CAL_CMGETAPI( "MemGCCheckBoundsAll" ) 
	#define CAL_MemGCCheckBoundsAll pICmpMemGC->IMemGCCheckBoundsAll
	#define CHK_MemGCCheckBoundsAll (pICmpMemGC != NULL)
	#define EXP_MemGCCheckBoundsAll  CAL_CMEXPAPI( "MemGCCheckBoundsAll" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemGCCheckBoundsAll  PFMEMGCCHECKBOUNDSALL pfMemGCCheckBoundsAll;
	#define EXT_MemGCCheckBoundsAll  extern PFMEMGCCHECKBOUNDSALL pfMemGCCheckBoundsAll;
	#define GET_MemGCCheckBoundsAll(fl)  s_pfCMGetAPI2( "MemGCCheckBoundsAll", (RTS_VOID_FCTPTR *)&pfMemGCCheckBoundsAll, (fl), 0, 0)
	#define CAL_MemGCCheckBoundsAll  pfMemGCCheckBoundsAll
	#define CHK_MemGCCheckBoundsAll  (pfMemGCCheckBoundsAll != NULL)
	#define EXP_MemGCCheckBoundsAll  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemGCCheckBoundsAll", (RTS_UINTPTR)MemGCCheckBoundsAll, 0, 0) 
#endif




/**
 * <description>
 *	Routine to find original heap memory pointer from garbage collector.
 * </description>
 * <param name="pMem" type="IN">Pointer to the memory data block</param>
 * <result>Pointer to the garabge collector entry</result>
 */
GARBAGE_COLLECTOR * CDECL MemGCFindEntry(void *pMem);
typedef GARBAGE_COLLECTOR * (CDECL * PFMEMGCFINDENTRY) (void *pMem);
#if defined(CMPMEMGC_NOTIMPLEMENTED) || defined(MEMGCFINDENTRY_NOTIMPLEMENTED)
	#define USE_MemGCFindEntry
	#define EXT_MemGCFindEntry
	#define GET_MemGCFindEntry(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemGCFindEntry(p0)  (GARBAGE_COLLECTOR *)ERR_NOTIMPLEMENTED
	#define CHK_MemGCFindEntry  FALSE
	#define EXP_MemGCFindEntry  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemGCFindEntry
	#define EXT_MemGCFindEntry
	#define GET_MemGCFindEntry(fl)  CAL_CMGETAPI( "MemGCFindEntry" ) 
	#define CAL_MemGCFindEntry  MemGCFindEntry
	#define CHK_MemGCFindEntry  TRUE
	#define EXP_MemGCFindEntry  CAL_CMEXPAPI( "MemGCFindEntry" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMGC_EXTERNAL)
	#define USE_MemGCFindEntry
	#define EXT_MemGCFindEntry
	#define GET_MemGCFindEntry(fl)  CAL_CMGETAPI( "MemGCFindEntry" ) 
	#define CAL_MemGCFindEntry  MemGCFindEntry
	#define CHK_MemGCFindEntry  TRUE
	#define EXP_MemGCFindEntry  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemGCFindEntry", (RTS_UINTPTR)MemGCFindEntry, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemGCMemGCFindEntry
	#define EXT_CmpMemGCMemGCFindEntry
	#define GET_CmpMemGCMemGCFindEntry  ERR_OK
	#define CAL_CmpMemGCMemGCFindEntry pICmpMemGC->IMemGCFindEntry
	#define CHK_CmpMemGCMemGCFindEntry (pICmpMemGC != NULL)
	#define EXP_CmpMemGCMemGCFindEntry  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemGCFindEntry
	#define EXT_MemGCFindEntry
	#define GET_MemGCFindEntry(fl)  CAL_CMGETAPI( "MemGCFindEntry" ) 
	#define CAL_MemGCFindEntry pICmpMemGC->IMemGCFindEntry
	#define CHK_MemGCFindEntry (pICmpMemGC != NULL)
	#define EXP_MemGCFindEntry  CAL_CMEXPAPI( "MemGCFindEntry" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemGCFindEntry  PFMEMGCFINDENTRY pfMemGCFindEntry;
	#define EXT_MemGCFindEntry  extern PFMEMGCFINDENTRY pfMemGCFindEntry;
	#define GET_MemGCFindEntry(fl)  s_pfCMGetAPI2( "MemGCFindEntry", (RTS_VOID_FCTPTR *)&pfMemGCFindEntry, (fl), 0, 0)
	#define CAL_MemGCFindEntry  pfMemGCFindEntry
	#define CHK_MemGCFindEntry  (pfMemGCFindEntry != NULL)
	#define EXP_MemGCFindEntry  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemGCFindEntry", (RTS_UINTPTR)MemGCFindEntry, 0, 0) 
#endif




/**
 * <description>
 *	Routine to get the head node of the garbage collector to check for garbage memory.
 * </description>
 * <param name="ppHead" type="IN">Get first entry of the garbage collector list</param>
 * <result>Pointer to the garabge collector entry</result>
 */
RTS_RESULT CDECL MemGCGetHead(GARBAGE_COLLECTOR **ppHead);
typedef RTS_RESULT (CDECL * PFMEMGCGETHEAD) (GARBAGE_COLLECTOR **ppHead);
#if defined(CMPMEMGC_NOTIMPLEMENTED) || defined(MEMGCGETHEAD_NOTIMPLEMENTED)
	#define USE_MemGCGetHead
	#define EXT_MemGCGetHead
	#define GET_MemGCGetHead(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemGCGetHead(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MemGCGetHead  FALSE
	#define EXP_MemGCGetHead  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemGCGetHead
	#define EXT_MemGCGetHead
	#define GET_MemGCGetHead(fl)  CAL_CMGETAPI( "MemGCGetHead" ) 
	#define CAL_MemGCGetHead  MemGCGetHead
	#define CHK_MemGCGetHead  TRUE
	#define EXP_MemGCGetHead  CAL_CMEXPAPI( "MemGCGetHead" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMGC_EXTERNAL)
	#define USE_MemGCGetHead
	#define EXT_MemGCGetHead
	#define GET_MemGCGetHead(fl)  CAL_CMGETAPI( "MemGCGetHead" ) 
	#define CAL_MemGCGetHead  MemGCGetHead
	#define CHK_MemGCGetHead  TRUE
	#define EXP_MemGCGetHead  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemGCGetHead", (RTS_UINTPTR)MemGCGetHead, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemGCMemGCGetHead
	#define EXT_CmpMemGCMemGCGetHead
	#define GET_CmpMemGCMemGCGetHead  ERR_OK
	#define CAL_CmpMemGCMemGCGetHead pICmpMemGC->IMemGCGetHead
	#define CHK_CmpMemGCMemGCGetHead (pICmpMemGC != NULL)
	#define EXP_CmpMemGCMemGCGetHead  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemGCGetHead
	#define EXT_MemGCGetHead
	#define GET_MemGCGetHead(fl)  CAL_CMGETAPI( "MemGCGetHead" ) 
	#define CAL_MemGCGetHead pICmpMemGC->IMemGCGetHead
	#define CHK_MemGCGetHead (pICmpMemGC != NULL)
	#define EXP_MemGCGetHead  CAL_CMEXPAPI( "MemGCGetHead" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemGCGetHead  PFMEMGCGETHEAD pfMemGCGetHead;
	#define EXT_MemGCGetHead  extern PFMEMGCGETHEAD pfMemGCGetHead;
	#define GET_MemGCGetHead(fl)  s_pfCMGetAPI2( "MemGCGetHead", (RTS_VOID_FCTPTR *)&pfMemGCGetHead, (fl), 0, 0)
	#define CAL_MemGCGetHead  pfMemGCGetHead
	#define CHK_MemGCGetHead  (pfMemGCGetHead != NULL)
	#define EXP_MemGCGetHead  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemGCGetHead", (RTS_UINTPTR)MemGCGetHead, 0, 0) 
#endif




/**
 * <description>
 *	Routine to get the pointer to the real memory block.
 * </description>
 * <param name="pGarbage" type="IN">Garbage collector entry</param>
 * <result>Get memory block from the garbage collector entry</result>
 */
void * CDECL MemGCGetMemBlock(GARBAGE_COLLECTOR *pGarbage);
typedef void * (CDECL * PFMEMGCGETMEMBLOCK) (GARBAGE_COLLECTOR *pGarbage);
#if defined(CMPMEMGC_NOTIMPLEMENTED) || defined(MEMGCGETMEMBLOCK_NOTIMPLEMENTED)
	#define USE_MemGCGetMemBlock
	#define EXT_MemGCGetMemBlock
	#define GET_MemGCGetMemBlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MemGCGetMemBlock(p0)  (void *)(RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_MemGCGetMemBlock  FALSE
	#define EXP_MemGCGetMemBlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MemGCGetMemBlock
	#define EXT_MemGCGetMemBlock
	#define GET_MemGCGetMemBlock(fl)  CAL_CMGETAPI( "MemGCGetMemBlock" ) 
	#define CAL_MemGCGetMemBlock  MemGCGetMemBlock
	#define CHK_MemGCGetMemBlock  TRUE
	#define EXP_MemGCGetMemBlock  CAL_CMEXPAPI( "MemGCGetMemBlock" ) 
#elif defined(MIXED_LINK) && !defined(CMPMEMGC_EXTERNAL)
	#define USE_MemGCGetMemBlock
	#define EXT_MemGCGetMemBlock
	#define GET_MemGCGetMemBlock(fl)  CAL_CMGETAPI( "MemGCGetMemBlock" ) 
	#define CAL_MemGCGetMemBlock  MemGCGetMemBlock
	#define CHK_MemGCGetMemBlock  TRUE
	#define EXP_MemGCGetMemBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemGCGetMemBlock", (RTS_UINTPTR)MemGCGetMemBlock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMemGCMemGCGetMemBlock
	#define EXT_CmpMemGCMemGCGetMemBlock
	#define GET_CmpMemGCMemGCGetMemBlock  ERR_OK
	#define CAL_CmpMemGCMemGCGetMemBlock pICmpMemGC->IMemGCGetMemBlock
	#define CHK_CmpMemGCMemGCGetMemBlock (pICmpMemGC != NULL)
	#define EXP_CmpMemGCMemGCGetMemBlock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MemGCGetMemBlock
	#define EXT_MemGCGetMemBlock
	#define GET_MemGCGetMemBlock(fl)  CAL_CMGETAPI( "MemGCGetMemBlock" ) 
	#define CAL_MemGCGetMemBlock pICmpMemGC->IMemGCGetMemBlock
	#define CHK_MemGCGetMemBlock (pICmpMemGC != NULL)
	#define EXP_MemGCGetMemBlock  CAL_CMEXPAPI( "MemGCGetMemBlock" ) 
#else /* DYNAMIC_LINK */
	#define USE_MemGCGetMemBlock  PFMEMGCGETMEMBLOCK pfMemGCGetMemBlock;
	#define EXT_MemGCGetMemBlock  extern PFMEMGCGETMEMBLOCK pfMemGCGetMemBlock;
	#define GET_MemGCGetMemBlock(fl)  s_pfCMGetAPI2( "MemGCGetMemBlock", (RTS_VOID_FCTPTR *)&pfMemGCGetMemBlock, (fl), 0, 0)
	#define CAL_MemGCGetMemBlock  pfMemGCGetMemBlock
	#define CHK_MemGCGetMemBlock  (pfMemGCGetMemBlock != NULL)
	#define EXP_MemGCGetMemBlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MemGCGetMemBlock", (RTS_UINTPTR)MemGCGetMemBlock, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFMEMGCGETSIZE IMemGCGetSize;
 	PFMEMGCGETCURRENTHEAPSIZE IMemGCGetCurrentHeapSize;
 	PFMEMGCADD IMemGCAdd;
 	PFMEMGCREMOVE IMemGCRemove;
 	PFMEMGCCHECKBOUNDSALL IMemGCCheckBoundsAll;
 	PFMEMGCFINDENTRY IMemGCFindEntry;
 	PFMEMGCGETHEAD IMemGCGetHead;
 	PFMEMGCGETMEMBLOCK IMemGCGetMemBlock;
 } ICmpMemGC_C;

#ifdef CPLUSPLUS
class ICmpMemGC : public IBase
{
	public:
		virtual RTS_SIZE CDECL IMemGCGetSize(RTS_SIZE ulSize) =0;
		virtual RTS_SIZE CDECL IMemGCGetCurrentHeapSize(RTS_RESULT *pResult) =0;
		virtual void * CDECL IMemGCAdd(char *pszComponentName, void *pMem, RTS_SIZE ulSizeGc) =0;
		virtual void * CDECL IMemGCRemove(char *pszComponentName, void *pMem, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IMemGCCheckBoundsAll(void) =0;
		virtual GARBAGE_COLLECTOR * CDECL IMemGCFindEntry(void *pMem) =0;
		virtual RTS_RESULT CDECL IMemGCGetHead(GARBAGE_COLLECTOR **ppHead) =0;
		virtual void * CDECL IMemGCGetMemBlock(GARBAGE_COLLECTOR *pGarbage) =0;
};
	#ifndef ITF_CmpMemGC
		#define ITF_CmpMemGC static ICmpMemGC *pICmpMemGC = NULL;
	#endif
	#define EXTITF_CmpMemGC
#else	/*CPLUSPLUS*/
	typedef ICmpMemGC_C		ICmpMemGC;
	#ifndef ITF_CmpMemGC
		#define ITF_CmpMemGC
	#endif
	#define EXTITF_CmpMemGC
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPMEMGCITF_H_*/
